"""Singleton orchestrator: open a result directory and serve frame queries.

Replaces the TODO stub in tdy_results.py.  Mirrors ref_code/TDYResults.cpp's
role — loads overview.xml + topo_0.xml once, keeps a ResReader around for
lazy on-demand .res reads, and exposes a small query API used by
server/api/routes_results.py.
"""

from pathlib import Path
from threading import Lock
from typing import Dict, List, Optional

import numpy as np

from .overview_parser import FrameMeta, parse_overview
from .res_reader import ResReader
from .topo_parser import MNFPart, RigidPart, Topo, parse_topo


def _compute_vertex_normals_fast(positions: np.ndarray, triangles: np.ndarray) -> np.ndarray:
    """Area-weighted vertex normals, fully vectorized via np.bincount.

    positions: (N, 3) float32 world coordinates.
    triangles: (M, 3) int32 vertex indices (0-based).
    Returns (N, 3) float32 unit-length normals.

    ~10× faster than the equivalent np.add.at formulation because bincount
    has a tight C loop for scatter-add.
    """
    n = positions.shape[0]
    if triangles.shape[0] == 0 or n == 0:
        return np.zeros((n, 3), dtype=np.float32)

    # Per-triangle face normal (not unit length — weighted by area × 2).
    v0 = positions[triangles[:, 0]]
    v1 = positions[triangles[:, 1]]
    v2 = positions[triangles[:, 2]]
    face = np.cross(v1 - v0, v2 - v0).astype(np.float32, copy=False)

    # Scatter-add each face normal to all 3 of its corners in one shot.
    idx_flat = triangles.reshape(-1)
    # face_repeat shape: (M*3, 3)
    face_repeat = np.repeat(face, 3, axis=0)

    normals = np.empty((n, 3), dtype=np.float32)
    for c in range(3):
        normals[:, c] = np.bincount(
            idx_flat, weights=face_repeat[:, c], minlength=n
        )[:n]

    length = np.linalg.norm(normals, axis=1, keepdims=True)
    length[length == 0] = 1.0
    normals /= length
    return normals


class ResultManager:
    def __init__(self) -> None:
        self.result_dir: Optional[str] = None
        self.frames: List[FrameMeta] = []
        self.topo: Optional[Topo] = None
        self.reader: Optional[ResReader] = None
        self._lock = Lock()

    # ---- lifecycle --------------------------------------------------------

    @property
    def loaded(self) -> bool:
        return self.topo is not None and self.reader is not None

    def open(self, result_dir: str) -> Dict[str, object]:
        """Open a directory with overview.xml + topo_*.xml + result_*.res."""
        with self._lock:
            path = Path(result_dir)
            overview = path / "overview.xml"
            if not overview.is_file():
                raise FileNotFoundError(f"overview.xml not found in {path}")

            frames = parse_overview(str(overview))
            if not frames:
                raise ValueError("overview.xml has no frames")

            topo_name = frames[0].topo_file or "topo_0.xml"
            topo_path = path / topo_name
            if not topo_path.is_file():
                raise FileNotFoundError(f"{topo_name} not found in {path}")

            topo = parse_topo(str(topo_path))
            reader = ResReader(str(path), frames, topo)

            # Release previous reader if any
            if self.reader is not None:
                self.reader.close()

            self.result_dir = str(path)
            self.frames = frames
            self.topo = topo
            self.reader = reader

            return {
                "result_dir": str(path),
                "frame_count": len(frames),
                "time_range": [frames[0].time, frames[-1].time],
                "rigid_parts": len(topo.rigid_parts),
                "mnf_parts": len(topo.mnf_parts),
            }

    def close(self) -> None:
        with self._lock:
            if self.reader is not None:
                self.reader.close()
            self.result_dir = None
            self.frames = []
            self.topo = None
            self.reader = None

    # ---- queries ----------------------------------------------------------

    def status(self) -> Dict[str, object]:
        if not self.loaded:
            return {"loaded": False, "frame_count": 0}
        return {
            "loaded": True,
            "result_dir": self.result_dir,
            "frame_count": len(self.frames),
            "time_range": [self.frames[0].time, self.frames[-1].time],
            "rigid_parts": len(self.topo.rigid_parts),
            "mnf_parts": len(self.topo.mnf_parts),
        }

    def topo_summary(self) -> Dict[str, object]:
        if not self.loaded:
            return {"rigid": [], "mnf": []}
        rigid = [
            {
                "name": p.name,
                "variables": list(p.part_variables.keys()),
            }
            for p in self.topo.rigid_parts
        ]
        mnf = [
            {
                "name": p.name,
                "num_nodes": p.num_nodes,
                "num_triangles": int(p.triangles.shape[0]),
                "node_variables": list(p.node_variables.keys()),
                "part_variables": list(p.part_variables.keys()),
            }
            for p in self.topo.mnf_parts
        ]
        return {"rigid": rigid, "mnf": mnf}

    def _frame_id(self, index: int) -> int:
        if index < 0 or index >= len(self.frames):
            raise IndexError(f"frame index {index} out of range")
        return self.frames[index].frame_id

    def get_rigid_transforms(self, frame_index: int) -> List[Dict[str, object]]:
        if not self.loaded:
            return []
        fid = self._frame_id(frame_index)
        out: List[Dict[str, object]] = []
        for rp in self.topo.rigid_parts:
            try:
                t = self.reader.read_rigid_transform(fid, rp)
                out.append(
                    {
                        "name": rp.name,
                        "position": t["position"].tolist(),
                        "phi": t["phi"].tolist(),
                    }
                )
            except KeyError:
                continue
        return out

    def get_mnf_frame(
        self,
        frame_index: int,
        part_name: str,
        fields: List[str],
    ) -> Dict[str, object]:
        if not self.loaded:
            raise RuntimeError("results not loaded")
        part = self.topo.find_mnf(part_name)
        if part is None:
            raise KeyError(f"MNF part {part_name} not found")
        fid = self._frame_id(frame_index)

        out: Dict[str, object] = {
            "frame": frame_index,
            "frame_id": fid,
            "time": self.frames[frame_index].time,
            "part": part.name,
            "num_nodes": part.num_nodes,
        }

        if "position" in fields:
            pos = self.reader.read_mnf_node_variable(fid, part, "position")
            out["positions"] = pos.astype(np.float32).flatten().tolist()

        if "mises" in fields:
            m = self.reader.read_mnf_node_variable(fid, part, "Mises Stress")
            out["mises"] = m.astype(np.float32).tolist()
            out["mises_min"] = float(m.min())
            out["mises_max"] = float(m.max())

        return out

    @staticmethod
    def _color_for(name: str) -> List[int]:
        """Deterministic pastel colour keyed by part family.

        Instances of the same part (e.g. PART3_INS1..PART3_INS6) get the
        same colour so visual grouping is obvious, while different families
        (PART3 vs PART4 vs screws) are clearly distinct.
        """
        # "PART3_INS2" → "PART3"; keeps screws / nuts / etc with their full
        # base name.
        up = name.upper()
        family = up.rsplit("_INS", 1)[0] if "_INS" in up else up
        h = 0
        for ch in family:
            h = (h * 131 + ord(ch)) & 0xFFFFFFFF
        # HSL → RGB with fixed S/L for consistent brightness
        hue = (h % 360) / 360.0
        s = 0.55
        l = 0.62
        c = (1 - abs(2 * l - 1)) * s
        x = c * (1 - abs(((hue * 6) % 2) - 1))
        m = l - c / 2
        if hue < 1 / 6:   r, g, b = c, x, 0
        elif hue < 2 / 6: r, g, b = x, c, 0
        elif hue < 3 / 6: r, g, b = 0, c, x
        elif hue < 4 / 6: r, g, b = 0, x, c
        elif hue < 5 / 6: r, g, b = x, 0, c
        else:             r, g, b = c, 0, x
        return [int((r + m) * 255), int((g + m) * 255), int((b + m) * 255)]

    def build_scene_items(self, model_dir: Optional[str] = None) -> List[Dict[str, object]]:
        """Build the scene graph directly from topo_0.xml.

        RIGIDPART items reference an STL file that lives in ``model_dir`` (the
        parent of the result directory by default).  MNFPART items embed their
        rest geometry (nodes + triangles).  The initial transform is taken
        from frame 0 so the scene is consistent with frame playback.
        """
        if not self.loaded:
            return []
        if model_dir is None:
            model_dir = str(Path(self.result_dir).parent)

        items: List[Dict[str, object]] = []

        # Import lazily to avoid circular deps
        from ..visualization.mesh_processor import parse_stl_file
        from ..visualization.mnf_rest_mesh import mnf_rest_to_geometry

        fid0 = self.frames[0].frame_id

        for rp in self.topo.rigid_parts:
            try:
                tr = self.reader.read_rigid_transform(fid0, rp)
                position = tr["position"].tolist()
                phi = tr["phi"].tolist()
            except Exception:
                position = [0, 0, 0]
                phi = [0, 0, 0]

            mesh = None
            for stl_name in rp.stl_files:
                candidate = Path(model_dir) / stl_name
                # Case-insensitive fallback since STL is declared uppercase
                if not candidate.is_file():
                    parent = Path(model_dir)
                    if parent.is_dir():
                        lower = stl_name.lower()
                        for f in parent.iterdir():
                            if f.name.lower() == lower:
                                candidate = f
                                break
                if candidate.is_file():
                    try:
                        mesh = parse_stl_file(str(candidate))
                        break
                    except Exception:
                        continue

            if mesh is None:
                # Skip rigid bodies with no graphics declaration.  Emitting a
                # fallback box placed at the part's frame-0 origin tends to
                # clip through neighbouring real geometry (e.g. BC_ADAPTER
                # under the battery cover).  We'd rather not render anything.
                continue
            items.append(
                {
                    "id": len(items) + 1,
                    "keyname": rp.name,
                    "category": "RIGID_PART",
                    "position": position,
                    "phi": phi,
                    "geometry": "stl",
                    "color": self._color_for(rp.name),
                    "mesh": mesh,
                    "part_name": rp.name,
                }
            )

        for mp in self.topo.mnf_parts:
            mesh = mnf_rest_to_geometry(mp)
            # MNF node positions are stored in world coordinates already; the
            # rest nodes in topo are also world coordinates.  No per-part
            # transform is needed — the frame positions drive deformation.
            items.append(
                {
                    "id": len(items) + 1,
                    "keyname": mp.name,
                    "category": "MNF_PART",
                    "position": [0, 0, 0],
                    "phi": [0, 0, 0],
                    "geometry": "mnf_mesh",
                    "color": self._color_for(mp.name),
                    "mesh": mesh,
                    "part_name": mp.name,
                    "num_nodes": mp.num_nodes,
                }
            )

        return items

    def get_all_mnf_positions_bin(self, frame_index: int) -> bytes:
        """Pack every MNF part's position vector for one frame into a single
        little-endian binary blob.  The frontend uses flat shading with
        derivative-based normals, so we don't need to ship normals.

        Layout:
            uint32  magic  (0x4D4E4650 = "MNFP")
            uint32  part_count
            for each part:
                uint16   name_len
                bytes    name (utf-8)
                uint32   num_nodes
                float32  positions[num_nodes * 3]
        """
        if not self.loaded:
            raise RuntimeError("results not loaded")
        fid = self._frame_id(frame_index)

        import struct
        chunks: List[bytes] = []
        chunks.append(struct.pack("<II", 0x4D4E4650, len(self.topo.mnf_parts)))
        for mp in self.topo.mnf_parts:
            try:
                pos = self.reader.read_mnf_node_variable(fid, mp, "position")
            except Exception:
                continue
            name_b = mp.name.encode("utf-8")
            chunks.append(struct.pack("<H", len(name_b)))
            chunks.append(name_b)
            chunks.append(struct.pack("<I", mp.num_nodes))
            chunks.append(pos.astype(np.float32, copy=False).tobytes(order="C"))
        return b"".join(chunks)

    def get_all_mnf_positions(self, frame_index: int) -> Dict[str, object]:
        """Read NodeVariable 'position' for every MNFPART at one frame.

        Returns float32-encoded positions per part — used by the frontend to
        animate every flexible body simultaneously without 17 separate HTTP
        requests.
        """
        if not self.loaded:
            raise RuntimeError("results not loaded")
        fid = self._frame_id(frame_index)
        out: Dict[str, object] = {"frame": frame_index, "parts": {}}
        for mp in self.topo.mnf_parts:
            try:
                pos = self.reader.read_mnf_node_variable(fid, mp, "position")
            except Exception:
                continue
            out["parts"][mp.name] = {
                "num_nodes": mp.num_nodes,
                "positions": pos.astype(np.float32).flatten().tolist(),
            }
        return out

    def get_mnf_rest_mesh(self, part_name: str) -> Dict[str, object]:
        if not self.loaded:
            raise RuntimeError("results not loaded")
        part = self.topo.find_mnf(part_name)
        if part is None:
            raise KeyError(f"MNF part {part_name} not found")
        return {
            "name": part.name,
            "num_nodes": part.num_nodes,
            "positions": part.rest_nodes.flatten().tolist(),
            "indices": part.triangles.flatten().tolist(),
            "triangle_count": int(part.triangles.shape[0]),
        }


# Global singleton used by API routes
result_manager = ResultManager()
