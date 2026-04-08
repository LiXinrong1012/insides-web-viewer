"""Convert MNFPart (from topo_0.xml) into a Three.js buffer geometry dict.

The MNFPart already holds rest node coordinates and triangle connectivity.
We compute smooth vertex normals with vectorized numpy ops so this stays
snappy even for ~16k-node parts.
"""

from typing import Any, Dict

import numpy as np


def compute_vertex_normals(positions: np.ndarray, triangles: np.ndarray) -> np.ndarray:
    """Area-weighted smooth vertex normals.

    positions: (N, 3) float
    triangles: (M, 3) int (0-based)
    returns: (N, 3) float32, unit length
    """
    if triangles.shape[0] == 0:
        return np.zeros_like(positions, dtype=np.float32)

    v0 = positions[triangles[:, 0]]
    v1 = positions[triangles[:, 1]]
    v2 = positions[triangles[:, 2]]
    face_normals = np.cross(v1 - v0, v2 - v0)  # area-weighted

    normals = np.zeros_like(positions, dtype=np.float64)
    np.add.at(normals, triangles[:, 0], face_normals)
    np.add.at(normals, triangles[:, 1], face_normals)
    np.add.at(normals, triangles[:, 2], face_normals)

    lengths = np.linalg.norm(normals, axis=1, keepdims=True)
    lengths[lengths == 0] = 1.0
    normals /= lengths
    return normals.astype(np.float32)


def mnf_rest_to_geometry(part) -> Dict[str, Any]:
    """Build the rest geometry dict for an MNFPart."""
    positions = np.asarray(part.rest_nodes, dtype=np.float32)
    triangles = np.asarray(part.triangles, dtype=np.int32)

    normals = compute_vertex_normals(positions, triangles)

    return {
        "positions": positions.flatten().tolist(),
        "normals": normals.flatten().tolist(),
        "indices": triangles.flatten().tolist(),
        "vertex_count": int(positions.shape[0]),
        "triangle_count": int(triangles.shape[0]),
    }
