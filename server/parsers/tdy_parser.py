"""TDY recursive descent parser, mirroring edcompile/modelparser.cpp.

Parses TDY text into an AssemblyItem tree. The grammar is:

    file        : item*
    item        : KEYWORD '/' properties_and_keyvalues ['{' item* '}']
    properties  : (IDENT | NUMBER) (',' (IDENT | NUMBER))*
    keyvalue    : KEY '=' value (',' value)*
    value       : NUMBER | IDENT | QUOTED_STRING
    comment     : '!' text_to_eol | '//' text_to_eol | '/*' text '*/'
"""

from pathlib import Path
from typing import List, Optional

from .tdy_ast import (
    AssemblyItem,
    CommentItem,
    KeyValueItem,
    LineItem,
    PropertyItem,
    SourceLocation,
)


class CompileError:
    """A parse/compile error with location."""

    __slots__ = ("message", "loc", "severity")

    def __init__(self, message: str, loc: SourceLocation, severity: str = "error") -> None:
        self.message = message
        self.loc = loc
        self.severity = severity

    def __repr__(self) -> str:
        return f"{self.severity}: {self.loc}: {self.message}"


class TDYParser:
    """Recursive descent parser for TDY files."""

    def __init__(self, expand_include: bool = True) -> None:
        self.expand_include = expand_include
        self.include_folders: List[str] = []
        self.errors: List[CompileError] = []

    def parse_file(self, filepath: str) -> AssemblyItem:
        """Parse a TDY file from disk."""
        path = Path(filepath)
        text = path.read_text(encoding="utf-8")
        file_dir = str(path.parent)
        if file_dir not in self.include_folders:
            self.include_folders.insert(0, file_dir)
        return self.parse(text, filepath)

    def parse(self, text: str, filename: str = "<string>") -> AssemblyItem:
        """Parse TDY text into an AssemblyItem tree."""
        root = AssemblyItem("", SourceLocation(0, 0, filename))
        self._parse_into(text, filename, root)
        return root

    def _parse_into(self, text: str, filename: str, root: AssemblyItem) -> None:
        """Core parser: character-by-character state machine.

        State: current_parent, current_item, current_kv, in_quote, buf
        - When we see KEYWORD / ..., we create a new LineItem
        - When we see KEY = val, we create KeyValueItem on current_item
        - Comma and newline separate values/properties
        - { converts LineItem to AssemblyItem, } closes it
        """
        pos = 0
        length = len(text)
        row = 0
        col = 0

        current_parent: AssemblyItem = root
        current_item: Optional[LineItem] = None
        current_kv: Optional[KeyValueItem] = None
        in_quote = False
        buf = ""

        def loc() -> SourceLocation:
            return SourceLocation(row, col, filename)

        def flush_buf() -> str:
            nonlocal buf
            val = buf.strip()
            buf = ""
            return val

        def finalize_current_item() -> None:
            """Finalize and add current_item to current_parent."""
            nonlocal current_item, current_kv
            if current_item is not None:
                # Remove trailing END from last keyvalue
                if current_kv and current_kv.values:
                    if current_kv.values[-1].upper() == "END":
                        current_kv.values.pop()
                self._extract_id_label(current_item)
                current_parent.add_child(current_item)
                current_item = None
                current_kv = None

        def store_value(val: str) -> None:
            """Store a value as property or kv-value depending on state."""
            nonlocal current_kv
            if not val:
                return
            if val.upper() == "END" and current_kv is None and current_item is not None:
                return  # Skip standalone END
            if current_kv is not None:
                current_kv.values.append(val)
            elif current_item is not None:
                prop = PropertyItem(val, loc())
                current_item.properties.append(prop)
                current_item.all_items.append(prop)

        while pos < length:
            ch = text[pos]
            pos += 1

            # Track position
            if ch == "\n":
                if in_quote:
                    buf += ch
                    row += 1
                    col = 0
                    continue
                # Newline acts as value separator
                val = flush_buf()
                store_value(val)
                row += 1
                col = 0
                continue

            if ch == "\r":
                continue

            col += 1

            # Inside quoted string
            if in_quote:
                if ch == '"':
                    in_quote = False
                    val = '"' + buf + '"'
                    buf = ""
                    if current_kv is not None:
                        current_kv.values.append(val)
                    elif current_item is not None:
                        prop = PropertyItem(val, loc())
                        current_item.properties.append(prop)
                        current_item.all_items.append(prop)
                else:
                    buf += ch
                continue

            # Whitespace
            if ch in (" ", "\t"):
                continue

            # Comma
            if ch == ",":
                val = flush_buf()
                store_value(val)
                continue

            # Forward slash
            if ch == "/":
                if pos < length and text[pos] == "/":
                    # Line comment //
                    pos += 1
                    comment_text = self._read_to_eol(text, pos, length)
                    pos += len(comment_text)
                    c = CommentItem("//" + comment_text, loc())
                    if current_item is not None:
                        current_item.comments.append(c)
                        current_item.all_items.append(c)
                    else:
                        current_parent.add_comment(c)
                    # newline will be consumed next iteration
                    continue
                if pos < length and text[pos] == "*":
                    # Block comment
                    pos += 1
                    comment_text, rows_consumed = self._read_block_comment(text, pos, length)
                    pos += len(comment_text) + 2
                    row += rows_consumed
                    c = CommentItem("/*" + comment_text + "*/", loc())
                    if current_item is not None:
                        current_item.comments.append(c)
                        current_item.all_items.append(c)
                    else:
                        current_parent.add_comment(c)
                    continue

                # Slash separator: KEYWORD / ...
                keyword = flush_buf()
                if keyword:
                    if keyword.upper() == "INCLUDE" and self.expand_include:
                        inc_line = self._read_to_eol(text, pos, length).strip()
                        pos += len(self._read_to_eol(text, pos, length))
                        self._handle_include(inc_line, filename, current_parent)
                        continue
                    # Finalize any previous item before starting new one
                    finalize_current_item()
                    current_item = LineItem(keyword, loc())
                    current_kv = None
                continue

            # Quote
            if ch == '"':
                in_quote = True
                buf = ""
                continue

            # Equals
            if ch == "=":
                key = flush_buf()
                if key and current_item is not None:
                    kv = KeyValueItem(key, loc())
                    current_item.key_values.append(kv)
                    current_item.all_items.append(kv)
                    current_kv = kv
                continue

            # Open brace
            if ch == "{":
                val = flush_buf()
                store_value(val)
                if current_item is not None:
                    # Convert to AssemblyItem
                    asm = AssemblyItem(current_item.keyname, current_item.loc)
                    asm.main_id = current_item.main_id
                    asm.main_label = current_item.main_label
                    asm.key_values = current_item.key_values
                    asm.properties = current_item.properties
                    asm.comments = current_item.comments
                    asm.all_items = current_item.all_items
                    self._extract_id_label(asm)
                    current_parent.add_child(asm)
                    current_parent = asm
                    current_item = None
                    current_kv = None
                continue

            # Close brace
            if ch == "}":
                val = flush_buf()
                store_value(val)
                finalize_current_item()
                if current_parent.parent is not None:
                    current_parent = current_parent.parent  # type: ignore
                continue

            # Exclamation — line comment
            if ch == "!":
                val = flush_buf()
                store_value(val)
                comment_text = self._read_to_eol(text, pos, length)
                pos += len(comment_text)
                c = CommentItem("!" + comment_text, loc())
                if current_item is not None:
                    current_item.comments.append(c)
                    current_item.all_items.append(c)
                else:
                    current_parent.add_comment(c)
                continue

            # Regular character
            buf += ch

        # End of file
        val = flush_buf()
        if val and val.upper() != "END":
            store_value(val)
        finalize_current_item()

    def _extract_id_label(self, item: LineItem) -> None:
        """Extract main_id and main_label from properties.

        Rules:
        1. If first property is numeric → main_id, remove it
        2. If next property exists → main_label, remove it
        3. Otherwise → main_label = first property
        """
        if item.main_id or item.main_label:
            return  # already set

        props = item.properties[:]
        if not props:
            item.main_id = item.keyname
            item.main_label = item.keyname
            return

        first = props[0].name
        if self._is_numeric(first):
            item.main_id = first
            item.properties.remove(props[0])
            if len(props) > 1:
                item.main_label = props[1].name
                item.properties.remove(props[1])
            else:
                item.main_label = first
        else:
            item.main_label = first
            item.main_id = first
            item.properties.remove(props[0])

    @staticmethod
    def _is_numeric(s: str) -> bool:
        try:
            float(s)
            return True
        except ValueError:
            return False

    @staticmethod
    def _read_to_eol(text: str, pos: int, length: int) -> str:
        end = text.find("\n", pos)
        if end == -1:
            return text[pos:]
        return text[pos:end]

    @staticmethod
    def _read_block_comment(text: str, pos: int, length: int) -> tuple:
        rows = 0
        start = pos
        while pos < length - 1:
            if text[pos] == "\n":
                rows += 1
            if text[pos] == "*" and text[pos + 1] == "/":
                return text[start:pos], rows
            pos += 1
        return text[start:], rows

    def _handle_include(self, inc_line: str, current_file: str, parent: AssemblyItem) -> None:
        fname = inc_line.strip().strip('"').strip("'")
        if not fname:
            return
        full_path = self._resolve_include(fname, current_file)
        if full_path is None:
            self.errors.append(
                CompileError(f"Include file not found: {fname}", SourceLocation(filename=current_file))
            )
            return
        try:
            text = Path(full_path).read_text(encoding="utf-8")
            self._parse_into(text, full_path, parent)
        except Exception as e:
            self.errors.append(
                CompileError(f"Error reading include file: {e}", SourceLocation(filename=current_file))
            )

    def _resolve_include(self, fname: str, current_file: str) -> Optional[str]:
        current_dir = str(Path(current_file).parent)
        candidate = Path(current_dir) / fname
        if candidate.exists():
            return str(candidate)
        for folder in self.include_folders:
            candidate = Path(folder) / fname
            if candidate.exists():
                return str(candidate)
        return None
