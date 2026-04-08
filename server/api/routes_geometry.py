"""Geometry API: serve 3D mesh data for the viewer."""

from typing import Any, Dict, List

import numpy as np
from fastapi import APIRouter, HTTPException

from pathlib import Path

from ..visualization.mesh_processor import (
    create_box_geometry,
    create_cylinder_geometry,
    create_sphere_geometry,
    parse_stl_file,
)
from ..visualization.mnf_parser import parse_mnf_xml, mnf_to_geometry
from .routes_model import get_document

router = APIRouter(prefix="/api/geometry", tags=["geometry"])


@router.get("/part/{item_id}")
async def get_part_geometry(item_id: int):
    """Get 3D geometry for a model item."""
    doc = get_document()
    item = doc.find_item(item_id)
    if item is None:
        raise HTTPException(404, f"Item {item_id} not found")

    props = item.properties
    shape_type = props.get("_shape_type", "").upper()

    if shape_type == "BOX":
        return create_box_geometry(
            _float_prop(props, "DX", 1.0),
            _float_prop(props, "DY", 1.0),
            _float_prop(props, "DZ", 1.0),
        )
    elif shape_type == "CYLINDER":
        return create_cylinder_geometry(
            _float_prop(props, "RADIUS", 0.5),
            _float_prop(props, "HEIGHT", 1.0),
        )
    elif shape_type == "SPHERE":
        return create_sphere_geometry(_float_prop(props, "RADIUS", 0.5))

    return create_box_geometry(1.0, 1.0, 1.0)


@router.get("/scene")
async def get_scene():
    """Get all renderable items in the scene with shape details.

    When a result directory has been opened, the scene is built directly from
    topo_0.xml so that part/instance names match the .res data stream.  Otherwise
    it falls back to the main.tdy document tree.
    """
    from ..results.result_manager import result_manager

    if result_manager.loaded:
        return {"items": result_manager.build_scene_items(), "source": "results"}

    doc = get_document()
    # Build world transforms for all instances (with hierarchy composition)
    world_instances = _build_instance_world_transforms(doc.assembly)

    # Build a map of part_name → part BaseItem for quick lookup
    part_map: Dict[str, Any] = {}
    _collect_parts(doc.assembly, part_map)

    # Generate renderable items: one per instance
    items: List[Dict[str, Any]] = []
    for wi in world_instances:
        part_name = wi["part_name"]
        part = part_map.get(part_name)
        if part is None:
            continue
        _render_part_instance(part, wi["center"], wi["phi"], items)

    return {"items": items, "source": "tdy"}


def _rodrigues_matrix(phi: List[float]) -> np.ndarray:
    """Convert Rodriguez rotation vector to 3x3 rotation matrix."""
    px, py, pz = phi[0], phi[1], phi[2]
    theta = np.sqrt(px*px + py*py + pz*pz)
    if theta < 1e-10:
        return np.eye(3)
    k = np.array([px, py, pz]) / theta
    K = np.array([[0, -k[2], k[1]], [k[2], 0, -k[0]], [-k[1], k[0], 0]])
    return np.cos(theta) * np.eye(3) + (1 - np.cos(theta)) * np.outer(k, k) + np.sin(theta) * K


def _compose_transforms(
    parent: Dict[str, List[float]], child: Dict[str, List[float]]
) -> Dict[str, List[float]]:
    """Compose parent and child transforms: world = parent * child.

    world_pos = parent_center + parent_R * child_center
    world_R = parent_R * child_R (converted back to rotation vector)
    """
    p_center = np.array(parent["center"])
    p_phi = parent["phi"]
    c_center = np.array(child["center"])
    c_phi = child["phi"]

    R_parent = _rodrigues_matrix(p_phi)
    R_child = _rodrigues_matrix(c_phi)

    # Compose position: parent + parent_rotation * child_local
    world_center = p_center + R_parent @ c_center

    # Compose rotation: R_world = R_parent * R_child
    R_world = R_parent @ R_child
    # Convert back to rotation vector using Rodrigues inverse
    world_phi = _rotation_matrix_to_rotvec(R_world)

    return {
        "center": world_center.tolist(),
        "phi": world_phi.tolist(),
    }


def _rotation_matrix_to_rotvec(R: np.ndarray) -> np.ndarray:
    """Convert 3x3 rotation matrix to Rodriguez rotation vector."""
    # Use scipy-like approach: angle from trace, axis from skew-symmetric part
    cos_angle = (np.trace(R) - 1.0) / 2.0
    cos_angle = np.clip(cos_angle, -1.0, 1.0)
    angle = np.arccos(cos_angle)
    if abs(angle) < 1e-10:
        return np.zeros(3)
    if abs(angle - np.pi) < 1e-6:
        # Near 180 degrees: find axis from R + I
        RpI = R + np.eye(3)
        # Use the column with largest norm
        col = np.argmax(np.sum(RpI**2, axis=0))
        axis = RpI[:, col]
        axis = axis / np.linalg.norm(axis)
        return axis * angle
    # General case: axis from skew-symmetric part
    axis = np.array([R[2,1] - R[1,2], R[0,2] - R[2,0], R[1,0] - R[0,1]])
    axis = axis / (2.0 * np.sin(angle))
    return axis * angle


def _build_instance_world_transforms(root: Any) -> List[Dict[str, Any]]:
    """Build a list of (part_name, world_transform) for ALL instances.

    Handles nested assemblies: composes parent assembly transform with
    child part/assembly transforms. One part may appear multiple times
    with different transforms (multiple instances of the same part).

    Returns: [{part_name: str, center: [x,y,z], phi: [px,py,pz]}, ...]
    """
    from ..models.base_item import ItemCategory

    # Step 1: Collect assembly-level instance transforms
    # assembly_name → list of {center, phi} (may be instanced multiple times)
    asm_instances: Dict[str, List[Dict[str, List[float]]]] = {}
    # part instances within each assembly context
    # (parent_asm_name, part_name) → list of local {center, phi}
    part_instances_local: List[Dict[str, Any]] = []

    def _walk(node: Any, parent_asm: str = "") -> None:
        if node.category == ItemCategory.INSTANCE:
            center = _extract_vector(node.properties, "CENTER", [0, 0, 0])
            phi = _extract_vector(node.properties, "PHI", [0, 0, 0])
            transform = {"center": center, "phi": phi}

            asm_ref = node.properties.get("ASSEMBLY", "")
            part_ref = node.properties.get("PART", "")

            if isinstance(asm_ref, str) and asm_ref:
                key = asm_ref.upper()
                asm_instances.setdefault(key, []).append(transform)
            elif isinstance(part_ref, str) and part_ref:
                part_instances_local.append({
                    "part_name": part_ref.upper(),
                    "parent_asm": parent_asm,
                    "local_transform": transform,
                })

        asm_name = ""
        if node.category == ItemCategory.ASSEMBLY and node.keyname != "Model":
            asm_name = node.keyname

        for child in node.children:
            _walk(child, asm_name or parent_asm)

    _walk(root)

    # Step 2: For each part instance, compute world transform
    result: List[Dict[str, Any]] = []
    identity = {"center": [0, 0, 0], "phi": [0, 0, 0]}

    for pi in part_instances_local:
        parent_asm = pi["parent_asm"]
        local_t = pi["local_transform"]

        if parent_asm and parent_asm.upper() in asm_instances:
            # This part is inside an assembly that is instanced (possibly multiple times)
            for asm_t in asm_instances[parent_asm.upper()]:
                world_t = _compose_transforms(asm_t, local_t)
                result.append({
                    "part_name": pi["part_name"],
                    "center": world_t["center"],
                    "phi": world_t["phi"],
                })
        else:
            # Top-level part instance - already in world coordinates
            result.append({
                "part_name": pi["part_name"],
                "center": local_t["center"],
                "phi": local_t["phi"],
            })

    return result


def _collect_parts(node: Any, part_map: Dict[str, Any]) -> None:
    """Recursively collect all RIGID_PART and FEM_PART items by keyname."""
    from ..models.base_item import ItemCategory
    if node.category in (ItemCategory.RIGID_PART, ItemCategory.FEM_PART):
        part_map[node.keyname.upper()] = node
    for child in node.children:
        _collect_parts(child, part_map)


def _render_part_instance(
    part: Any, position: List[float], phi: List[float], items: List[Dict[str, Any]]
) -> None:
    """Render a single part instance at the given world transform."""
    from ..models.base_item import ItemCategory

    # Check for GRAPHIC/SHAPE children
    shapes = [c for c in part.children if c.category == ItemCategory.SHAPE]

    if shapes:
        for shape in shapes:
            shape_type = shape.properties.get("_shape_type", "box").lower()
            rgb = _extract_rgb(shape.properties)
            radius = _float_prop(shape.properties, "RADIUS", 0.05)
            height = _float_prop(shape.properties, "HEIGHT", 0.5)

            entry = {
                "id": shape.id,
                "keyname": part.keyname,
                "category": "SHAPE",
                "position": position,
                "phi": phi,
                "geometry": shape_type,
                "radius": radius,
                "height": height,
                "color": rgb,
            }

            if shape_type == "stl":
                stl_path = shape.properties.get("STL", "")
                if isinstance(stl_path, str) and stl_path and Path(stl_path).is_file():
                    try:
                        entry["mesh"] = parse_stl_file(stl_path)
                    except Exception:
                        pass

            items.append(entry)

    elif part.category == ItemCategory.FEM_PART:
        entry = {
            "id": part.id,
            "keyname": part.keyname,
            "category": "FEM_PART",
            "position": position,
            "phi": phi,
            "geometry": "fem_mesh",
            "color": [100, 180, 255],
        }
        mnf_file = part.properties.get("_mnf_file", "")
        if mnf_file:
            mnf_path = Path(mnf_file)
            mnf_dir = mnf_path.parent / mnf_path.stem
            xml_path = mnf_dir / f"{mnf_path.stem}.xml"
            if xml_path.is_file():
                try:
                    mnf_data = parse_mnf_xml(str(mnf_file))
                    entry["mesh"] = mnf_to_geometry(mnf_data)
                except Exception:
                    pass
        items.append(entry)

    else:
        # Fallback box for parts without graphics
        items.append({
            "id": part.id, "keyname": part.keyname,
            "category": part.category.name, "position": position,
            "phi": phi, "geometry": "box", "radius": 0.1, "height": 0.2,
            "color": [128, 128, 200],
        })




def _extract_rgb(props: Dict) -> List[int]:
    """Extract RGB color from properties."""
    rgb = props.get("RGB", None)
    if rgb and isinstance(rgb, list):
        try:
            return [int(float(v)) for v in rgb[:3]]
        except (ValueError, TypeError):
            pass
    return [128, 128, 128]


def _float_prop(props: Dict, key: str, default: float = 0.0) -> float:
    val = props.get(key, default)
    if isinstance(val, list):
        val = val[0] if val else default
    try:
        return float(val)
    except (ValueError, TypeError):
        return default


def _extract_vector(props: Dict, key: str, default: List[float]) -> List[float]:
    val = props.get(key, default)
    if isinstance(val, list):
        try:
            return [float(v) for v in val[:3]]
        except (ValueError, TypeError):
            return default
    return default


@router.get("/contour/{item_id}")
async def get_contour(item_id: int, mode: int = 7, component: str = "magnitude"):
    """Get contour color data for a FEM part's mode shape."""
    doc = get_document()
    item = doc.find_item(item_id)
    if item is None:
        raise HTTPException(404, f"Item {item_id} not found")

    mnf_file = item.properties.get("_mnf_file", "")
    if not mnf_file:
        raise HTTPException(400, "Item has no MNF file")

    from ..visualization.mnf_parser import parse_mnf_xml
    from ..visualization.contour import scalar_to_vertex_colors, generate_legend_data

    mnf_data = parse_mnf_xml(str(mnf_file))
    if mnf_data["mode_shapes"] is None or mode not in mnf_data["mode_shapes"]:
        raise HTTPException(400, f"Mode {mode} not available")

    shape = mnf_data["mode_shapes"][mode]  # (num_nodes, 6): dx,dy,dz,ax,ay,az
    comp_map = {"dx": 0, "dy": 1, "dz": 2, "ax": 3, "ay": 4, "az": 5}
    if component == "magnitude":
        values = np.sqrt(shape[:, 0]**2 + shape[:, 1]**2 + shape[:, 2]**2)
    elif component in comp_map:
        values = shape[:, comp_map[component]]
    else:
        raise HTTPException(400, f"Unknown component: {component}")

    color_data = scalar_to_vertex_colors(values)
    legend = generate_legend_data(color_data["vmin"], color_data["vmax"])

    return {
        "colors": color_data["colors"],
        "vmin": color_data["vmin"],
        "vmax": color_data["vmax"],
        "legend": legend,
        "mode": mode,
        "component": component,
    }


@router.get("/modes/{item_id}")
async def get_modes(item_id: int):
    """List available modes for a FEM part."""
    doc = get_document()
    item = doc.find_item(item_id)
    if item is None:
        raise HTTPException(404, f"Item {item_id} not found")
    mnf_file = item.properties.get("_mnf_file", "")
    if not mnf_file:
        return {"modes": []}
    from ..visualization.mnf_parser import parse_mnf_xml
    try:
        mnf_data = parse_mnf_xml(str(mnf_file))
        modes = sorted(mnf_data["mode_shapes"].keys()) if mnf_data["mode_shapes"] else []
        return {"modes": modes}
    except Exception:
        return {"modes": []}
