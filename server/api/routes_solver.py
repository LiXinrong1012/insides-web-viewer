"""Solver control API + WebSocket for real-time progress."""

from fastapi import APIRouter, WebSocket, WebSocketDisconnect

from ..solver.solver_manager import SolverManager, SolverProgress, solver_manager

router = APIRouter(prefix="/api/solver", tags=["solver"])


@router.get("/status")
async def solver_status():
    """Get current solver state."""
    p = solver_manager.progress
    return {
        "state": p.state,
        "cpu_time": p.cpu_time,
        "sim_time": p.sim_time,
        "max_time": p.max_time,
        "percentage": p.percentage,
        "error_message": p.error_message,
        "log_count": len(p.log_lines),
    }


@router.post("/start")
async def start_solver(model_dir: str, tdy_file: str = "main.tdy"):
    """Start the solver."""
    ok = await solver_manager.start(model_dir, tdy_file)
    return {"started": ok, "state": solver_manager.progress.state}


@router.post("/stop")
async def stop_solver():
    """Stop the solver."""
    await solver_manager.stop()
    return {"state": solver_manager.progress.state}


@router.get("/logs")
async def get_logs(last_n: int = 100):
    """Get recent solver log lines."""
    lines = solver_manager.progress.log_lines
    return {"lines": lines[-last_n:]}


@router.websocket("/ws")
async def solver_websocket(ws: WebSocket):
    """WebSocket endpoint for real-time solver progress updates."""
    await ws.accept()

    import asyncio
    import json

    update_queue: asyncio.Queue = asyncio.Queue()

    def on_progress(progress: SolverProgress):
        try:
            update_queue.put_nowait({
                "state": progress.state,
                "cpu_time": progress.cpu_time,
                "sim_time": progress.sim_time,
                "max_time": progress.max_time,
                "percentage": progress.percentage,
                "error_message": progress.error_message,
            })
        except asyncio.QueueFull:
            pass

    solver_manager.add_listener(on_progress)
    try:
        # Send initial state
        await ws.send_json({
            "state": solver_manager.progress.state,
            "percentage": solver_manager.progress.percentage,
        })

        while True:
            try:
                data = await asyncio.wait_for(update_queue.get(), timeout=5.0)
                await ws.send_json(data)
            except asyncio.TimeoutError:
                # Send heartbeat
                await ws.send_json({"heartbeat": True})
            except WebSocketDisconnect:
                break
    finally:
        solver_manager.remove_listener(on_progress)
