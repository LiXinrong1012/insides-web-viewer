"""Parse MNF XML format: extract nodes, surface faces, and mode shapes."""

import struct
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

import numpy as np


def parse_mnf_xml(mnf_file_path: str) -> Dict[str, Any]:
    """Parse an MNF XML + binary data file pair.

    Args:
        mnf_file_path: Path to the .mnf file. The actual data is in
            a sibling directory with the same stem.
    """
    mnf_path = Path(mnf_file_path)
    mnf_dir = mnf_path.parent / mnf_path.stem
    xml_path = mnf_dir / f"{mnf_path.stem}.xml"
    dat_path = mnf_dir / f"{mnf_path.stem}.dat"

    if not xml_path.is_file():
        raise FileNotFoundError(f"MNF XML not found: {xml_path}")

    tree = ET.parse(str(xml_path))
    root = tree.getroot()

    num_nodes = int(root.attrib.get("NumOfNodes", 0))
    num_modes = int(root.attrib.get("NumOfModes", 0))
    num_faces = int(root.attrib.get("NumOfFaces", 0))

    nodes = _parse_nodes(root)
    faces = _parse_faces(root)
    mode_shapes = _parse_mode_shapes(root, num_nodes, num_modes, dat_path) if dat_path.is_file() else None

    return {
        "num_nodes": len(nodes),
        "num_faces": len(faces),
        "num_modes": num_modes,
        "nodes": nodes,
        "faces": faces,
        "mode_shapes": mode_shapes,
    }


def _parse_nodes(root):
    nodes_section = root.find("NODES")
    if nodes_section is None:
        return []
    nodes = []
    for node_elem in nodes_section.findall("NODE"):
        node_id = int(node_elem.attrib["ID"])
        pos_elem = node_elem.find("Position")
        if pos_elem is not None and pos_elem.text:
            pos_text = pos_elem.text.strip()
        else:
            pos_text = node_elem.text.strip() if node_elem.text else "0,0,0"
        coords = [float(v) for v in pos_text.split(",") if v.strip()]
        if len(coords) < 3:
            coords.extend([0.0] * (3 - len(coords)))
        nodes.append((node_id, coords[0], coords[1], coords[2]))
    return nodes


def _parse_faces(root):
    faces_section = root.find("FACES")
    if faces_section is None:
        return []
    faces = []
    for face_elem in faces_section.findall("FACE"):
        num_n = int(face_elem.attrib.get("NumOfNodes", 3))
        text = face_elem.text.strip() if face_elem.text else ""
        idxs = [int(v) for v in text.split(",")]
        if num_n == 3:
            faces.append(idxs[:3])
        elif num_n == 4:
            faces.append([idxs[0], idxs[1], idxs[2]])
            faces.append([idxs[0], idxs[2], idxs[3]])
    return faces


def _parse_mode_shapes(root, num_nodes, num_modes, dat_path):
    modes_section = root.find("MODES")
    if modes_section is None:
        return None
    dat_data = dat_path.read_bytes()
    mode_shapes = {}
    for mode_elem in modes_section.findall("MODE"):
        mode_num = int(mode_elem.attrib["ModeNumber"])
        offset = int(mode_elem.attrib["offset"])
        length = int(mode_elem.attrib["length"])
        expected = num_nodes * 6 * 8  # 6 doubles per node
        if offset + expected <= len(dat_data):
            arr = np.frombuffer(dat_data, dtype=np.float64, count=num_nodes * 6, offset=offset)
            mode_shapes[mode_num] = arr.reshape(num_nodes, 6)
    return mode_shapes


def mnf_to_geometry(mnf_data: Dict[str, Any]) -> Dict[str, Any]:
    """Convert parsed MNF data to Three.js buffer geometry."""
    nodes = mnf_data["nodes"]
    faces = mnf_data["faces"]
    if not nodes or not faces:
        return {"positions": [], "normals": [], "indices": [], "vertex_count": 0, "triangle_count": 0}

    positions = np.zeros((len(nodes), 3), dtype=np.float32)
    for i, (nid, x, y, z) in enumerate(nodes):
        positions[i] = [x, y, z]

    indices = []
    for face in faces:
        if all(0 <= idx < len(nodes) for idx in face):
            indices.extend(face)

    # Compute smooth normals
    normals = np.zeros_like(positions)
    for i in range(0, len(indices) - 2, 3):
        i0, i1, i2 = indices[i], indices[i+1], indices[i+2]
        e1 = positions[i1] - positions[i0]
        e2 = positions[i2] - positions[i0]
        n = np.cross(e1, e2)
        nl = np.linalg.norm(n)
        if nl > 0:
            n /= nl
        normals[i0] += n
        normals[i1] += n
        normals[i2] += n

    norms = np.linalg.norm(normals, axis=1, keepdims=True)
    norms[norms == 0] = 1.0
    normals /= norms

    return {
        "positions": positions.flatten().tolist(),
        "normals": normals.flatten().tolist(),
        "indices": indices,
        "vertex_count": len(nodes),
        "triangle_count": len(indices) // 3,
    }
