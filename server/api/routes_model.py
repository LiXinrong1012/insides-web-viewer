"""Model CRUD API endpoints."""

from pathlib import Path

from fastapi import APIRouter, HTTPException, UploadFile

from ..config import settings
from ..models.base_item import BaseItem, ItemCategory
from ..models.model_document import ModelDocument

router = APIRouter(prefix="/api/model", tags=["model"])

# In-memory document store (single-user for Phase 0)
_document = ModelDocument()


def get_document() -> ModelDocument:
    return _document


@router.post("/open")
async def open_model(file: UploadFile):
    """Upload and open a TDY model file."""
    if not file.filename:
        raise HTTPException(400, "No file provided")

    # Save uploaded file
    settings.upload_dir.mkdir(parents=True, exist_ok=True)
    dest = settings.upload_dir / file.filename
    content = await file.read()
    dest.write_bytes(content)

    # Parse TDY file and build model tree
    doc = get_document()
    doc.file_path = str(dest)

    from ..parsers.tdy_parser import TDYParser
    from ..parsers.model_builder import ModelBuilder

    parser = TDYParser()
    ast_root = parser.parse(content.decode("utf-8"), str(dest))

    builder = ModelBuilder()
    model_name = Path(file.filename).stem
    doc.assembly = builder.build(ast_root, model_name)
    doc.modified = False

    return {
        "filename": file.filename,
        "size": len(content),
        "tree": doc.get_tree(),
        "errors": [str(e) for e in parser.errors],
        "parameters": builder.parameters.items(),
    }


@router.get("/tree")
async def get_model_tree():
    """Get the model tree structure."""
    doc = get_document()
    return doc.get_tree()


@router.get("/item/{item_id}")
async def get_item(item_id: int):
    """Get a specific item by ID."""
    doc = get_document()
    item = doc.find_item(item_id)
    if item is None:
        raise HTTPException(404, f"Item {item_id} not found")
    return item.model_dump()


@router.post("/item/{parent_id}/add")
async def add_item(parent_id: int, keyname: str, category: str):
    """Add a child item to a parent."""
    doc = get_document()
    try:
        cat = ItemCategory[category.upper()]
    except KeyError:
        raise HTTPException(400, f"Unknown category: {category}")

    item = BaseItem(keyname=keyname, category=cat)
    if not doc.insert_child(parent_id, item):
        raise HTTPException(404, f"Parent {parent_id} not found")
    return item.model_dump()


@router.delete("/item/{item_id}")
async def remove_item(item_id: int):
    """Remove an item from the model."""
    doc = get_document()
    if not doc.remove_item(item_id):
        raise HTTPException(404, f"Item {item_id} not found")
    return {"removed": item_id}


@router.get("/status")
async def model_status():
    """Get document status."""
    doc = get_document()
    return {
        "file_path": doc.file_path,
        "modified": doc.modified,
        "can_undo": doc.undo_stack.can_undo,
        "can_redo": doc.undo_stack.can_redo,
    }
