"""Results API: query time series, frame data, and manage result items."""

from fastapi import APIRouter, HTTPException

from ..results.tdy_results import results_store

router = APIRouter(prefix="/api/results", tags=["results"])


@router.get("/items")
async def list_result_items():
    """List all available result items."""
    return {"items": results_store.list_items(), "frame_count": results_store.frame_count}


@router.get("/timeseries/{entity_id}")
async def get_time_series(entity_id: str, section: str = "Value"):
    """Get time series data for a result item."""
    data = results_store.get_time_series(entity_id, section)
    if data is None:
        raise HTTPException(404, f"No results for {entity_id}/{section}")
    return data


@router.get("/frame/{frame_index}")
async def get_frame(frame_index: int):
    """Get all result data for a specific time frame."""
    data = results_store.get_frame_data(frame_index)
    if data is None:
        raise HTTPException(404, f"Frame {frame_index} not found")
    return data


@router.post("/load")
async def load_results(model_dir: str = "", generate_sample: bool = False):
    """Load results from a directory or generate sample data."""
    if generate_sample:
        results_store.generate_sample_results()
        return {
            "loaded": True,
            "source": "sample",
            "frame_count": results_store.frame_count,
            "item_count": len(results_store.items),
        }

    if not model_dir:
        raise HTTPException(400, "model_dir is required")

    ok = results_store.load_from_directory(model_dir)
    return {
        "loaded": ok,
        "source": model_dir,
        "frame_count": results_store.frame_count,
        "item_count": len(results_store.items),
    }


@router.get("/status")
async def results_status():
    """Get results loading status."""
    return {
        "loaded": results_store.loaded,
        "frame_count": results_store.frame_count,
        "item_count": len(results_store.items),
        "time_range": [results_store.time_list[0], results_store.time_list[-1]]
            if results_store.time_list else [0, 0],
    }
