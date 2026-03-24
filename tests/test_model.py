"""Tests for the model data structures and API."""

from server.models.base_item import Assembly, BaseItem, ItemCategory
from server.models.model_document import ModelDocument


def test_assembly_default_folders():
    asm = Assembly.create_default("TestModel")
    assert asm.keyname == "TestModel"
    assert asm.category == ItemCategory.ASSEMBLY
    folder_names = [c.keyname for c in asm.children]
    assert "Parts" in folder_names
    assert "Constraints" in folder_names
    assert "Loads" in folder_names
    assert "Ground" in folder_names


def test_find_by_id():
    asm = Assembly.create_default()
    parts_folder = asm.get_folder("Parts")
    assert parts_folder is not None
    found = asm.find_by_id(parts_folder.id)
    assert found is parts_folder


def test_add_remove_child():
    asm = Assembly.create_default()
    parts = asm.get_folder("Parts")
    assert parts is not None
    part = BaseItem(keyname="RigidBody1", category=ItemCategory.RIGID_PART)
    parts.add_child(part)
    assert len(parts.children) == 1
    assert parts.children[0].keyname == "RigidBody1"
    parts.remove_child(part.id)
    assert len(parts.children) == 0


def test_model_document_crud():
    doc = ModelDocument()
    parts = doc.assembly.get_folder("Parts")
    assert parts is not None

    item = BaseItem(keyname="Part1", category=ItemCategory.RIGID_PART)
    assert doc.insert_child(parts.id, item)
    assert doc.modified
    assert doc.find_item(item.id) is item

    assert doc.remove_item(item.id)
    assert doc.find_item(item.id) is None


def test_model_document_reset():
    doc = ModelDocument()
    doc.modified = True
    doc.file_path = "test.tdy"
    doc.reset("NewModel")
    assert doc.assembly.keyname == "NewModel"
    assert not doc.modified
    assert doc.file_path is None


def test_tree_dict():
    asm = Assembly.create_default("Root")
    tree = asm.to_tree_dict()
    assert tree["keyname"] == "Root"
    assert tree["category"] == "ASSEMBLY"
    assert len(tree["children"]) == 11
