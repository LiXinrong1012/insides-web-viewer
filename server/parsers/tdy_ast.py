"""TDY parse tree (AST) data structures, mirroring edcompile/mainitem.h."""

from typing import Any, Dict, List, Optional


class SourceLocation:
    """Tracks position in source file for error reporting."""

    __slots__ = ("row", "col", "filename")

    def __init__(self, row: int = 0, col: int = 0, filename: str = "") -> None:
        self.row = row
        self.col = col
        self.filename = filename

    def __repr__(self) -> str:
        return f"{self.filename}:{self.row + 1}:{self.col + 1}"


class KeyValueItem:
    """A key=value pair: KEY = val1, val2, val3."""

    __slots__ = ("keyname", "values", "loc")

    def __init__(self, keyname: str, loc: Optional[SourceLocation] = None) -> None:
        self.keyname = keyname
        self.values: List[str] = []
        self.loc = loc or SourceLocation()

    def __repr__(self) -> str:
        vals = ", ".join(self.values)
        return f"{self.keyname} = {vals}"


class PropertyItem:
    """A bare property flag (positional argument after /)."""

    __slots__ = ("name", "loc")

    def __init__(self, name: str, loc: Optional[SourceLocation] = None) -> None:
        self.name = name
        self.loc = loc or SourceLocation()

    def __repr__(self) -> str:
        return self.name


class CommentItem:
    """A comment (line or block)."""

    __slots__ = ("text", "loc")

    def __init__(self, text: str, loc: Optional[SourceLocation] = None) -> None:
        self.text = text
        self.loc = loc or SourceLocation()


class LineItem:
    """A single keyword occurrence: KEYWORD / ID, prop1, key1=val1."""

    __slots__ = (
        "keyname",
        "main_id",
        "main_label",
        "key_values",
        "properties",
        "comments",
        "all_items",
        "parent",
        "loc",
    )

    def __init__(self, keyname: str = "", loc: Optional[SourceLocation] = None) -> None:
        self.keyname = keyname
        self.main_id = ""
        self.main_label = ""
        self.key_values: List[KeyValueItem] = []
        self.properties: List[PropertyItem] = []
        self.comments: List[CommentItem] = []
        self.all_items: List[Any] = []  # mixed: KV, Property, Comment in parse order
        self.parent: Optional["AssemblyItem"] = None
        self.loc = loc or SourceLocation()

    def get_keyvalue(self, name: str) -> Optional[KeyValueItem]:
        name_upper = name.upper()
        for kv in self.key_values:
            if kv.keyname.upper() == name_upper:
                return kv
        return None

    def has_property(self, name: str) -> bool:
        name_upper = name.upper()
        return any(p.name.upper() == name_upper for p in self.properties)

    def get_full_name(self) -> str:
        parts = []
        node: Optional[LineItem] = self
        while node is not None:
            label = node.main_label or node.main_id or node.keyname
            if label:
                parts.append(label)
            node = node.parent
        return ".".join(reversed(parts))

    def to_dict(self) -> Dict[str, Any]:
        """Convert to a serializable dict with all key-value pairs."""
        d: Dict[str, Any] = {
            "keyname": self.keyname,
            "id": self.main_id,
            "label": self.main_label,
        }
        for kv in self.key_values:
            d[kv.keyname] = kv.values if len(kv.values) > 1 else (kv.values[0] if kv.values else "")
        for prop in self.properties:
            d[prop.name] = True
        return d

    def __repr__(self) -> str:
        return f"LineItem({self.keyname}/{self.main_id})"


class AssemblyItem(LineItem):
    """A keyword block with children: KEYWORD / ID { children... }."""

    __slots__ = ("children", "all_children")

    def __init__(self, keyname: str = "", loc: Optional[SourceLocation] = None) -> None:
        super().__init__(keyname, loc)
        self.children: List[LineItem] = []
        self.all_children: List[Any] = []  # includes comments

    def add_child(self, item: LineItem) -> None:
        item.parent = self
        self.children.append(item)
        self.all_children.append(item)

    def add_comment(self, comment: CommentItem) -> None:
        self.all_children.append(comment)

    def find_children_by_keyword(self, keyword: str) -> List[LineItem]:
        kw_upper = keyword.upper()
        return [c for c in self.children if c.keyname.upper() == kw_upper]

    def __repr__(self) -> str:
        return f"AssemblyItem({self.keyname}/{self.main_id}, {len(self.children)} children)"
