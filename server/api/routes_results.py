"""Results API: open a result directory, query per-frame data for animation."""

from typing import List

from fastapi import APIRouter, HTTPException
from fastapi.responses import Response
from pydantic import BaseModel

from ..results.result_manager import result_manager

router = APIRouter(prefix="/api/results", tags=["results"])


class OpenRequest(BaseModel):
    result_dir: str


class OpenLoadcaseRequest(BaseModel):
    loadcase_dir: str


@router.post("/open")
async def open_results(req: OpenRequest):
    """Open a directory containing overview.xml, topo_0.xml, and result_*.res."""
    try:
        info = result_manager.open(req.result_dir)
    except FileNotFoundError as exc:
        raise HTTPException(404, str(exc))
    except ValueError as exc:
        raise HTTPException(400, str(exc))
    return info


@router.post("/open_loadcase")
async def open_loadcase(req: OpenLoadcaseRequest):
    """One-shot "open a loadcase directory" flow.

    The loadcase dir is expected to contain:
      - main.tdy              (TDY source driving the model tree / editor)
      - result/overview.xml   (result metadata)
      - result/topo_0.xml
      - result/result_*.res

    Returns the parsed tree + raw TDY text + result info in a single call so
    the frontend can populate tree, TDY editor, and animation state together.
    """
    from pathlib import Path as _P

    from .routes_model import get_document
    from ..parsers.model_builder import ModelBuilder
    from ..parsers.tdy_parser import TDYParser

    path = _P(req.loadcase_dir)
    if not path.is_dir():
        raise HTTPException(404, f"loadcase dir not found: {path}")

    # Locate the TDY source file (prefer main.tdy, fall back to any *.tdy)
    tdy_path = path / "main.tdy"
    if not tdy_path.is_file():
        cands = sorted(path.glob("*.tdy"))
        if not cands:
            raise HTTPException(404, f"no .tdy file found in {path}")
        tdy_path = cands[0]

    tdy_text = tdy_path.read_text(encoding="utf-8", errors="replace")

    # Parse into the in-memory document so /api/model/tree reflects it.
    parser = TDYParser()
    ast_root = parser.parse(tdy_text, str(tdy_path))
    builder = ModelBuilder()
    doc = get_document()
    doc.file_path = str(tdy_path)
    doc.assembly = builder.build(ast_root, tdy_path.stem)
    doc.modified = False

    # Open result/ subdir — tolerate missing (e.g. user only wants the model)
    result_dir = path / "result"
    result_info: dict = {"loaded": False}
    if (result_dir / "overview.xml").is_file():
        try:
            result_info = result_manager.open(str(result_dir))
            result_info["loaded"] = True
        except Exception as exc:
            result_info = {"loaded": False, "error": str(exc)}

    return {
        "loadcase_dir": str(path),
        "tdy_path": str(tdy_path),
        "tdy_filename": tdy_path.name,
        "tdy_text": tdy_text,
        "tree": doc.get_tree(),
        "parser_errors": [str(e) for e in parser.errors],
        "result": result_info,
    }


@router.post("/close")
async def close_results():
    result_manager.close()
    return {"loaded": False}


@router.get("/status")
async def results_status():
    return result_manager.status()


@router.get("/topo")
async def results_topo():
    return result_manager.topo_summary()


@router.get("/frames")
async def list_frames():
    if not result_manager.loaded:
        return {"frames": [], "frame_count": 0}
    return {
        "frame_count": len(result_manager.frames),
        "times": [f.time for f in result_manager.frames],
    }


@router.get("/frame/{frame_index}/rigid_transforms")
async def rigid_transforms(frame_index: int):
    if not result_manager.loaded:
        raise HTTPException(400, "no results loaded")
    try:
        return {"frame": frame_index, "items": result_manager.get_rigid_transforms(frame_index)}
    except IndexError as exc:
        raise HTTPException(404, str(exc))


@router.get("/frame/{frame_index}/all_mnf_positions")
async def all_mnf_positions(frame_index: int):
    if not result_manager.loaded:
        raise HTTPException(400, "no results loaded")
    try:
        return result_manager.get_all_mnf_positions(frame_index)
    except IndexError as exc:
        raise HTTPException(404, str(exc))


@router.get("/frame/{frame_index}/all_mnf_positions.bin")
async def all_mnf_positions_bin(frame_index: int):
    """Binary version — float32 packed, ~4× faster than JSON for animation."""
    if not result_manager.loaded:
        raise HTTPException(400, "no results loaded")
    try:
        blob = result_manager.get_all_mnf_positions_bin(frame_index)
    except IndexError as exc:
        raise HTTPException(404, str(exc))
    return Response(content=blob, media_type="application/octet-stream")


@router.get("/frame/{frame_index}/part/{part_name}")
async def mnf_frame(frame_index: int, part_name: str, fields: str = "position"):
    if not result_manager.loaded:
        raise HTTPException(400, "no results loaded")
    field_list: List[str] = [f.strip() for f in fields.split(",") if f.strip()]
    try:
        return result_manager.get_mnf_frame(frame_index, part_name, field_list)
    except KeyError as exc:
        raise HTTPException(404, str(exc))
    except IndexError as exc:
        raise HTTPException(404, str(exc))


@router.get("/mesh/{part_name}")
async def mnf_rest_mesh(part_name: str):
    if not result_manager.loaded:
        raise HTTPException(400, "no results loaded")
    try:
        return result_manager.get_mnf_rest_mesh(part_name)
    except KeyError as exc:
        raise HTTPException(404, str(exc))
