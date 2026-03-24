"""Mesh processing: STL parsing, FEM mesh → Three.js geometry buffers.

Converts mesh data to indexed buffer geometry format compatible with Three.js.
Output format: {positions: float32[], normals: float32[], indices: uint32[]}
"""

import struct
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

import numpy as np


def parse_stl_binary(data: bytes) -> Dict[str, Any]:
    """Parse a binary STL file into buffer geometry."""
    header = data[:80]
    num_triangles = struct.unpack("<I", data[80:84])[0]

    # Each triangle: normal(3f), v1(3f), v2(3f), v3(3f), attr(H) = 50 bytes
    positions = np.zeros((num_triangles * 3, 3), dtype=np.float32)
    normals = np.zeros((num_triangles * 3, 3), dtype=np.float32)

    offset = 84
    for i in range(num_triangles):
        nx, ny, nz = struct.unpack_from("<3f", data, offset)
        offset += 12
        for j in range(3):
            x, y, z = struct.unpack_from("<3f", data, offset)
            offset += 12
            idx = i * 3 + j
            positions[idx] = [x, y, z]
            normals[idx] = [nx, ny, nz]
        offset += 2  # attribute byte count

    indices = np.arange(num_triangles * 3, dtype=np.uint32)

    return {
        "positions": positions.flatten().tolist(),
        "normals": normals.flatten().tolist(),
        "indices": indices.tolist(),
        "vertex_count": num_triangles * 3,
        "triangle_count": num_triangles,
    }


def parse_stl_ascii(text: str) -> Dict[str, Any]:
    """Parse an ASCII STL file into buffer geometry."""
    positions: List[float] = []
    normals: List[float] = []
    current_normal = [0.0, 0.0, 0.0]

    for line in text.splitlines():
        line = line.strip()
        if line.startswith("facet normal"):
            parts = line.split()
            current_normal = [float(parts[2]), float(parts[3]), float(parts[4])]
        elif line.startswith("vertex"):
            parts = line.split()
            positions.extend([float(parts[1]), float(parts[2]), float(parts[3])])
            normals.extend(current_normal)

    num_verts = len(positions) // 3
    return {
        "positions": positions,
        "normals": normals,
        "indices": list(range(num_verts)),
        "vertex_count": num_verts,
        "triangle_count": num_verts // 3,
    }


def parse_stl_file(filepath: str) -> Dict[str, Any]:
    """Auto-detect STL format and parse."""
    data = Path(filepath).read_bytes()
    # Check if ASCII STL
    try:
        text = data.decode("ascii")
        if text.strip().startswith("solid") and "facet" in text:
            return parse_stl_ascii(text)
    except UnicodeDecodeError:
        pass
    return parse_stl_binary(data)


def fem_mesh_to_geometry(
    nodes: Dict[int, Tuple[float, float, float]],
    elements: List[Dict[str, Any]],
) -> Dict[str, Any]:
    """Convert FEM node/element data to Three.js buffer geometry.

    Args:
        nodes: {node_id: (x, y, z)}
        elements: [{"type": "TBEAM"/"QUAD"/"SHELL", "nodes": [n1, n2, ...]}]

    Returns indexed buffer geometry.
    """
    positions: List[float] = []
    indices: List[int] = []
    node_id_to_idx: Dict[int, int] = {}

    # Build vertex array from nodes
    for node_id, (x, y, z) in sorted(nodes.items()):
        node_id_to_idx[node_id] = len(positions) // 3
        positions.extend([x, y, z])

    # Build index array from elements
    for elem in elements:
        elem_nodes = elem.get("nodes", [])
        elem_type = elem.get("type", "").upper()

        if elem_type in ("TBEAM", "EBEAM", "CABLE", "VCABLE", "VBEAM"):
            # Line element: 2 nodes → visualize as line
            if len(elem_nodes) >= 2:
                i0 = node_id_to_idx.get(elem_nodes[0])
                i1 = node_id_to_idx.get(elem_nodes[1])
                if i0 is not None and i1 is not None:
                    indices.extend([i0, i1])

        elif elem_type in ("QUAD", "SHELL", "PLATE"):
            # Quad element: 4 nodes → 2 triangles
            if len(elem_nodes) >= 4:
                idx = [node_id_to_idx.get(n) for n in elem_nodes[:4]]
                if all(i is not None for i in idx):
                    indices.extend([idx[0], idx[1], idx[2]])
                    indices.extend([idx[0], idx[2], idx[3]])

        elif len(elem_nodes) == 3:
            # Triangle
            idx = [node_id_to_idx.get(n) for n in elem_nodes]
            if all(i is not None for i in idx):
                indices.extend(idx)

    # Compute flat normals for triangle faces
    normals = [0.0] * len(positions)
    for i in range(0, len(indices) - 2, 3):
        i0, i1, i2 = indices[i], indices[i + 1], indices[i + 2]
        p0 = np.array(positions[i0 * 3 : i0 * 3 + 3])
        p1 = np.array(positions[i1 * 3 : i1 * 3 + 3])
        p2 = np.array(positions[i2 * 3 : i2 * 3 + 3])
        edge1 = p1 - p0
        edge2 = p2 - p0
        normal = np.cross(edge1, edge2)
        norm_len = np.linalg.norm(normal)
        if norm_len > 0:
            normal = normal / norm_len
        for vi in [i0, i1, i2]:
            normals[vi * 3] += normal[0]
            normals[vi * 3 + 1] += normal[1]
            normals[vi * 3 + 2] += normal[2]

    # Normalize accumulated normals
    for i in range(0, len(normals), 3):
        n = np.array(normals[i : i + 3])
        norm_len = np.linalg.norm(n)
        if norm_len > 0:
            normals[i] = n[0] / norm_len
            normals[i + 1] = n[1] / norm_len
            normals[i + 2] = n[2] / norm_len

    return {
        "positions": positions,
        "normals": normals,
        "indices": indices,
        "vertex_count": len(positions) // 3,
        "triangle_count": len(indices) // 3,
    }


def create_box_geometry(dx: float, dy: float, dz: float) -> Dict[str, Any]:
    """Create a box centered at origin."""
    hx, hy, hz = dx / 2, dy / 2, dz / 2
    # 8 vertices, 12 triangles (6 faces × 2)
    v = [
        [-hx, -hy, -hz], [hx, -hy, -hz], [hx, hy, -hz], [-hx, hy, -hz],
        [-hx, -hy, hz], [hx, -hy, hz], [hx, hy, hz], [-hx, hy, hz],
    ]
    faces = [
        [0, 1, 2, 3], [4, 7, 6, 5],  # front, back
        [0, 3, 7, 4], [1, 5, 6, 2],  # left, right
        [3, 2, 6, 7], [0, 4, 5, 1],  # top, bottom
    ]
    face_normals = [
        [0, 0, -1], [0, 0, 1], [-1, 0, 0], [1, 0, 0], [0, 1, 0], [0, -1, 0],
    ]
    positions: List[float] = []
    normals: List[float] = []
    indices: List[int] = []

    for fi, face in enumerate(faces):
        base = len(positions) // 3
        for vi in face:
            positions.extend(v[vi])
            normals.extend(face_normals[fi])
        indices.extend([base, base + 1, base + 2, base, base + 2, base + 3])

    return {"positions": positions, "normals": normals, "indices": indices,
            "vertex_count": len(positions) // 3, "triangle_count": len(indices) // 3}


def create_cylinder_geometry(radius: float, height: float, segments: int = 24) -> Dict[str, Any]:
    """Create a cylinder along Y axis."""
    positions: List[float] = []
    normals: List[float] = []
    indices: List[int] = []
    half_h = height / 2

    for i in range(segments):
        angle0 = 2 * np.pi * i / segments
        angle1 = 2 * np.pi * (i + 1) / segments
        c0, s0 = np.cos(angle0), np.sin(angle0)
        c1, s1 = np.cos(angle1), np.sin(angle1)

        base = len(positions) // 3
        # Side quad as 2 triangles
        for x, z, nx, nz in [(c0 * radius, s0 * radius, c0, s0),
                               (c1 * radius, s1 * radius, c1, s1)]:
            positions.extend([x, -half_h, z])
            normals.extend([nx, 0, nz])
            positions.extend([x, half_h, z])
            normals.extend([nx, 0, nz])
        indices.extend([base, base + 2, base + 3, base, base + 3, base + 1])

    return {"positions": positions, "normals": normals, "indices": indices,
            "vertex_count": len(positions) // 3, "triangle_count": len(indices) // 3}


def create_sphere_geometry(radius: float, w_segments: int = 16, h_segments: int = 12) -> Dict[str, Any]:
    """Create a UV sphere."""
    positions: List[float] = []
    normals: List[float] = []
    indices: List[int] = []

    for j in range(h_segments + 1):
        phi = np.pi * j / h_segments
        for i in range(w_segments + 1):
            theta = 2 * np.pi * i / w_segments
            x = radius * np.sin(phi) * np.cos(theta)
            y = radius * np.cos(phi)
            z = radius * np.sin(phi) * np.sin(theta)
            positions.extend([x, y, z])
            n_len = np.sqrt(x * x + y * y + z * z)
            if n_len > 0:
                normals.extend([x / n_len, y / n_len, z / n_len])
            else:
                normals.extend([0, 1, 0])

    stride = w_segments + 1
    for j in range(h_segments):
        for i in range(w_segments):
            a = j * stride + i
            b = a + stride
            indices.extend([a, b, a + 1, b, b + 1, a + 1])

    return {"positions": positions, "normals": normals, "indices": indices,
            "vertex_count": len(positions) // 3, "triangle_count": len(indices) // 3}
