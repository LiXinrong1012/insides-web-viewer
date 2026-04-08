"""Read per-frame variable data from INSIDES .res binary files.

Each .res file is a concatenation of fixed-size frame blocks. A frame block
layout is described by topo_0.xml: every RIGIDPART / MNFPART declares its
PartVariables / NodeVariables with a frame-local byte offset and size. All
values are double-precision (float64).

This module uses numpy memory maps to avoid pulling multi-GB result files into
RAM.
"""

from pathlib import Path
from typing import Dict

import numpy as np

from .overview_parser import FrameMeta
from .topo_parser import MNFPart, PartVariable, RigidPart, Topo


class ResReader:
    def __init__(self, result_dir: str, frames: list, topo: Topo) -> None:
        self.result_dir = Path(result_dir)
        self.frames = frames  # List[FrameMeta] sorted in file order
        self.topo = topo
        self._mmaps: Dict[str, np.memmap] = {}
        self._frame_index: Dict[int, FrameMeta] = {f.frame_id: f for f in frames}

    def _mmap(self, res_file: str) -> np.memmap:
        m = self._mmaps.get(res_file)
        if m is None:
            path = self.result_dir / res_file
            if not path.is_file():
                raise FileNotFoundError(f"Result binary not found: {path}")
            m = np.memmap(str(path), dtype=np.uint8, mode="r")
            self._mmaps[res_file] = m
        return m

    def close(self) -> None:
        for m in self._mmaps.values():
            try:
                del m
            except Exception:
                pass
        self._mmaps.clear()

    # ---- low-level access -------------------------------------------------

    def _read_raw(self, frame: FrameMeta, variable: PartVariable) -> np.ndarray:
        mm = self._mmap(frame.res_file)
        abs_off = frame.startpos + variable.offset
        end = abs_off + variable.size
        if end > len(mm):
            raise ValueError(
                f"variable {variable.name} exceeds file: end={end}, "
                f"file_size={len(mm)}"
            )
        raw = np.asarray(mm[abs_off:end]).view(np.float64).copy()
        if variable.components > 1:
            raw = raw.reshape(-1, variable.components)
        return raw

    # ---- high-level API ---------------------------------------------------

    def read_rigid(self, frame_id: int, part: RigidPart, variable_name: str) -> np.ndarray:
        frame = self._frame_index[frame_id]
        var = part.part_variables.get(variable_name)
        if var is None:
            raise KeyError(f"Rigid part {part.name} has no variable {variable_name}")
        return self._read_raw(frame, var)

    def read_rigid_transform(self, frame_id: int, part: RigidPart) -> Dict[str, np.ndarray]:
        """Return {"position": (3,), "phi": (3,)} for a rigid body at a frame."""
        return {
            "position": self.read_rigid(frame_id, part, "position").reshape(-1),
            "phi": self.read_rigid(frame_id, part, "phi").reshape(-1),
        }

    def read_mnf_node_variable(
        self, frame_id: int, part: MNFPart, variable_name: str
    ) -> np.ndarray:
        frame = self._frame_index[frame_id]
        var = part.node_variables.get(variable_name)
        if var is None:
            raise KeyError(f"MNF part {part.name} has no node variable {variable_name}")
        data = self._read_raw(frame, var)
        if variable_name.lower() == "position":
            return data.reshape(part.num_nodes, 3)
        if var.components == 1:
            return data.reshape(-1)
        return data

    def read_mnf_part_variable(
        self, frame_id: int, part: MNFPart, variable_name: str
    ) -> np.ndarray:
        frame = self._frame_index[frame_id]
        var = part.part_variables.get(variable_name)
        if var is None:
            raise KeyError(f"MNF part {part.name} has no part variable {variable_name}")
        return self._read_raw(frame, var)
