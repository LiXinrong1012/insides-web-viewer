"""Document manager mirroring precore/modeldocument.h."""

from __future__ import annotations

from typing import Any

from .base_item import Assembly, BaseItem


class UndoStack:
    """Simple undo/redo stack for model operations."""

    def __init__(self, max_size: int = 100) -> None:
        self._undo: list[dict[str, Any]] = []
        self._redo: list[dict[str, Any]] = []
        self._max_size = max_size

    def push(self, command: dict[str, Any]) -> None:
        self._undo.append(command)
        if len(self._undo) > self._max_size:
            self._undo.pop(0)
        self._redo.clear()

    def undo(self) -> dict[str, Any] | None:
        if not self._undo:
            return None
        cmd = self._undo.pop()
        self._redo.append(cmd)
        return cmd

    def redo(self) -> dict[str, Any] | None:
        if not self._redo:
            return None
        cmd = self._redo.pop()
        self._undo.append(cmd)
        return cmd

    @property
    def can_undo(self) -> bool:
        return len(self._undo) > 0

    @property
    def can_redo(self) -> bool:
        return len(self._redo) > 0


class ModelDocument:
    """Manages the model assembly tree with undo/redo support."""

    def __init__(self) -> None:
        self.assembly: Assembly = Assembly.create_default()
        self.undo_stack = UndoStack()
        self.file_path: str | None = None
        self.modified: bool = False

    def reset(self, keyname: str = "Model") -> None:
        self.assembly = Assembly.create_default(keyname)
        self.undo_stack = UndoStack()
        self.file_path = None
        self.modified = False

    def find_item(self, item_id: int) -> BaseItem | None:
        return self.assembly.find_by_id(item_id)

    def insert_child(self, parent_id: int, item: BaseItem) -> bool:
        parent = self.find_item(parent_id)
        if parent is None:
            return False
        parent.add_child(item)
        self.modified = True
        self.undo_stack.push(
            {"action": "insert", "parent_id": parent_id, "item_id": item.id}
        )
        return True

    def remove_item(self, item_id: int) -> bool:
        def _remove_recursive(node: BaseItem) -> bool:
            if node.remove_child(item_id):
                return True
            for child in node.children:
                if _remove_recursive(child):
                    return True
            return False

        removed = _remove_recursive(self.assembly)
        if removed:
            self.modified = True
            self.undo_stack.push({"action": "remove", "item_id": item_id})
        return removed

    def get_tree(self) -> dict:
        return self.assembly.to_tree_dict()
