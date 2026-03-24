"""Solver process manager: launch, monitor, and control thudynamics.exe.

Mirrors inssolver/socketmessage.h and solverapp/localserver.h.
Uses subprocess + asyncio instead of QLocalSocket.
"""

import asyncio
import enum
import os
import subprocess
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable, List, Optional

from ..config import settings


class SolverState(str, enum.Enum):
    IDLE = "idle"
    STARTING = "starting"
    RUNNING = "running"
    PAUSED = "paused"
    FINISHED = "finished"
    ERROR = "error"


@dataclass
class SolverProgress:
    state: SolverState = SolverState.IDLE
    cpu_time: float = 0.0
    sim_time: float = 0.0
    max_time: float = 0.0
    percentage: float = 0.0
    log_lines: List[str] = field(default_factory=list)
    error_message: str = ""


class SolverManager:
    """Manages a single solver process."""

    def __init__(self) -> None:
        self.progress = SolverProgress()
        self._process: Optional[subprocess.Popen] = None
        self._task: Optional[asyncio.Task] = None
        self._listeners: List[Callable[[SolverProgress], None]] = []

    @property
    def is_running(self) -> bool:
        return self.progress.state in (SolverState.STARTING, SolverState.RUNNING)

    def add_listener(self, callback: Callable[[SolverProgress], None]) -> None:
        self._listeners.append(callback)

    def remove_listener(self, callback: Callable[[SolverProgress], None]) -> None:
        self._listeners.remove(callback)

    def _notify(self) -> None:
        for listener in self._listeners:
            try:
                listener(self.progress)
            except Exception:
                pass

    async def start(self, model_dir: str, tdy_filename: str = "main.tdy") -> bool:
        """Launch the solver process."""
        if self.is_running:
            return False

        solver_bin = settings.solver_bin
        mkl_dir = settings.mkl_dll_dir

        if not solver_bin.exists():
            self.progress.state = SolverState.ERROR
            self.progress.error_message = f"Solver not found: {solver_bin}"
            self._notify()
            return False

        self.progress = SolverProgress(state=SolverState.STARTING)
        self._notify()

        # Build PATH with solver dir and MKL dir
        solver_dir = str(solver_bin.parent)
        env = os.environ.copy()
        env["PATH"] = f"{solver_dir};{mkl_dir};{env.get('PATH', '')}"

        try:
            self._process = subprocess.Popen(
                [str(solver_bin), tdy_filename],
                cwd=model_dir,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                env=env,
                bufsize=1,
            )
            self.progress.state = SolverState.RUNNING
            self._notify()

            # Start monitoring in background
            self._task = asyncio.create_task(self._monitor_output())
            return True

        except Exception as e:
            self.progress.state = SolverState.ERROR
            self.progress.error_message = str(e)
            self._notify()
            return False

    async def stop(self) -> None:
        """Terminate the solver process."""
        if self._process and self._process.poll() is None:
            self._process.terminate()
            try:
                self._process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                self._process.kill()
        self.progress.state = SolverState.IDLE
        self._notify()

    async def _monitor_output(self) -> None:
        """Read solver stdout line by line and parse progress."""
        if self._process is None or self._process.stdout is None:
            return

        loop = asyncio.get_event_loop()
        while self._process.poll() is None:
            try:
                line_bytes = await loop.run_in_executor(
                    None, self._process.stdout.readline
                )
                if not line_bytes:
                    break
                line = line_bytes.decode("utf-8", errors="replace").rstrip()
                self._parse_output_line(line)
                self.progress.log_lines.append(line)
                # Keep last 1000 lines
                if len(self.progress.log_lines) > 1000:
                    self.progress.log_lines = self.progress.log_lines[-500:]
                self._notify()
            except Exception:
                break

        # Process finished
        return_code = self._process.returncode if self._process else -1
        if return_code == 0:
            self.progress.state = SolverState.FINISHED
            self.progress.percentage = 100.0
        else:
            self.progress.state = SolverState.ERROR
            self.progress.error_message = f"Process exited with code {return_code}"
        self._notify()

    def _parse_output_line(self, line: str) -> None:
        """Parse solver output for progress info."""
        lower = line.lower()
        # Look for time step info: "Time = 0.001 / 1.0"
        if "time" in lower and "/" in line:
            try:
                parts = line.split("=")[-1].strip().split("/")
                if len(parts) == 2:
                    current = float(parts[0].strip())
                    total = float(parts[1].strip())
                    self.progress.sim_time = current
                    self.progress.max_time = total
                    if total > 0:
                        self.progress.percentage = (current / total) * 100
            except (ValueError, IndexError):
                pass
        # Look for CPU time
        if "cpu" in lower:
            try:
                parts = line.split("=")
                if len(parts) >= 2:
                    self.progress.cpu_time = float(parts[-1].strip().split()[0])
            except (ValueError, IndexError):
                pass


# Global singleton
solver_manager = SolverManager()
