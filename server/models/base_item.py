"""Core data model mirroring precore/BaseItem.h and precore/Assembly.h."""

import itertools
from enum import IntEnum
from typing import Any, Dict, List, Optional

from pydantic import BaseModel, Field


class ItemCategory(IntEnum):
    """Maps to BaseItem category values from the C++ codebase."""

    UNKNOWN = 0
    FOLDER = 1
    RIGID_PART = 2
    FEM_PART = 3
    ASSEMBLY = 4
    CONSTRAINT = 5
    LOAD = 6
    CONTACT = 7
    MARKER = 8
    INSTANCE = 9
    REQUEST = 10
    SET = 11
    GROUND = 12
    PARAMETER = 13
    STL = 14
    SHAPE = 15
    MOTION = 16
    JOINT = 17
    INTPAR = 18


_id_counter = itertools.count(1)


class BaseItem(BaseModel):
    """Tree node representing any model entity (part, constraint, load, etc.)."""

    id: int = Field(default_factory=lambda: next(_id_counter))
    keyname: str = ""
    category: ItemCategory = ItemCategory.UNKNOWN
    properties: Dict[str, Any] = Field(default_factory=dict)
    active: bool = True
    visible: bool = True
    collapsed: bool = False
    children: List["BaseItem"] = Field(default_factory=list)

    def find_by_id(self, item_id: int) -> Optional["BaseItem"]:
        if self.id == item_id:
            return self
        for child in self.children:
            found = child.find_by_id(item_id)
            if found is not None:
                return found
        return None

    def find_by_keyname(self, keyname: str) -> Optional["BaseItem"]:
        if self.keyname == keyname:
            return self
        for child in self.children:
            found = child.find_by_keyname(keyname)
            if found is not None:
                return found
        return None

    def add_child(self, item: "BaseItem") -> None:
        self.children.append(item)

    def remove_child(self, item_id: int) -> bool:
        for i, child in enumerate(self.children):
            if child.id == item_id:
                self.children.pop(i)
                return True
        return False

    def to_tree_dict(self) -> Dict[str, Any]:
        """Lightweight dict for tree display (no deep properties)."""
        return {
            "id": self.id,
            "keyname": self.keyname,
            "category": self.category.name,
            "active": self.active,
            "visible": self.visible,
            "collapsed": self.collapsed,
            "children": [c.to_tree_dict() for c in self.children],
        }


BaseItem.model_rebuild()


class Assembly(BaseItem):
    """Root container with default folder structure, mirroring precore/Assembly.h."""

    category: ItemCategory = ItemCategory.ASSEMBLY

    @classmethod
    def create_default(cls, keyname: str = "Model") -> "Assembly":
        asm = cls(keyname=keyname)
        folders = [
            ("Parameters", ItemCategory.FOLDER),
            ("Parts", ItemCategory.FOLDER),
            ("Assemblies", ItemCategory.FOLDER),
            ("Constraints", ItemCategory.FOLDER),
            ("Loads", ItemCategory.FOLDER),
            ("Contacts", ItemCategory.FOLDER),
            ("Instances", ItemCategory.FOLDER),
            ("Requests", ItemCategory.FOLDER),
            ("Sets", ItemCategory.FOLDER),
            ("Markers", ItemCategory.FOLDER),
            ("Ground", ItemCategory.GROUND),
        ]
        for name, cat in folders:
            asm.add_child(BaseItem(keyname=name, category=cat))
        return asm

    def get_folder(self, name: str) -> Optional[BaseItem]:
        for child in self.children:
            if child.keyname == name:
                return child
        return None
