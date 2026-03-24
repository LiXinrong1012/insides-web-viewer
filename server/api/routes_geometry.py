"""Geometry API: serve 3D mesh data for the viewer."""

from typing import Any, Dict, List

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
    """Get all renderable items in the scene with shape details."""
    doc = get_document()
    items: List[Dict[str, Any]] = []
    # Collect instance positions for resolving part placements
    instance_positions: Dict[str, List[float]] = {}
    _collect_instance_positions(doc.assembly, instance_positions)
    _collect_renderable(doc.assembly, items, instance_positions)
    return {"items": items}


def _collect_instance_positions(item: Any, positions: Dict[str, List[float]]) -> None:
    """Build a map of instance keyname → CENTER position."""
    from ..models.base_item import ItemCategory

    if item.category == ItemCategory.INSTANCE:
        center = _extract_vector(item.properties, "CENTER", [0, 0, 0])
        positions[item.keyname] = center

    for child in item.children:
        _collect_instance_positions(child, positions)


def _collect_renderable(
    item: Any,
    items: List[Dict[str, Any]],
    instance_positions: Dict[str, List[float]],
) -> None:
    """Recursively collect renderable items with full shape info."""
    from ..models.base_item import ItemCategory

    if item.category == ItemCategory.SHAPE:
        shape_type = item.properties.get("_shape_type", "box").lower()
        rgb = _extract_rgb(item.properties)
        radius = _float_prop(item.properties, "RADIUS", 0.05)
        height = _float_prop(item.properties, "HEIGHT", 0.5)

        # Find parent part to get instance position
        position = [0, 0, 0]
        parent = _find_parent_part_instance(item, instance_positions)
        if parent:
            position = parent

        entry = {
            "id": item.id,
            "keyname": item.keyname,
            "category": "SHAPE",
            "position": position,
            "geometry": shape_type,
            "radius": radius,
            "height": height,
            "color": rgb,
        }

        if shape_type == "stl":
            stl_path = item.properties.get("STL", "")
            if isinstance(stl_path, str) and stl_path and Path(stl_path).is_file():
                try:
                    mesh_data = parse_stl_file(stl_path)
                    entry["mesh"] = mesh_data
                except Exception:
                    pass

        items.append(entry)

    elif item.category in (ItemCategory.RIGID_PART, ItemCategory.FEM_PART):
        has_graphics = any(c.category == ItemCategory.SHAPE for c in item.children)
        if item.category == ItemCategory.FEM_PART and not has_graphics:
            position = _extract_vector(item.properties, "QG", [0, 0, 0])
            # Try to resolve instance position
            for inst in _find_instances(get_document().assembly):
                part_ref = inst.properties.get("PART", "")
                if isinstance(part_ref, str) and part_ref.upper() == item.keyname.upper():
                    position = _extract_vector(inst.properties, "CENTER", [0, 0, 0])
                    break
            entry = {
                "id": item.id,
                "keyname": item.keyname,
                "category": "FEM_PART",
                "position": position,
                "geometry": "fem_mesh",
                "color": [100, 180, 255],
            }
            # Load MNF mesh if available
            mnf_file = item.properties.get("_mnf_file", "")
            if mnf_file:
                mnf_path = Path(mnf_file)
                mnf_dir = mnf_path.parent / mnf_path.stem
                xml_path = mnf_dir / f"{mnf_path.stem}.xml"
                if xml_path.is_file():
                    try:
                        mnf_data = parse_mnf_xml(str(mnf_file))
                        mesh = mnf_to_geometry(mnf_data)
                        entry["mesh"] = mesh
                    except Exception:
                        pass
            items.append(entry)
        elif not has_graphics:
            position = _extract_vector(item.properties, "QG", [0, 0, 0])
            items.append({
                "id": item.id, "keyname": item.keyname,
                "category": item.category.name, "position": position,
                "geometry": "box", "radius": 0.1, "height": 0.2,
                "color": [128, 128, 200],
            })

    elif item.category == ItemCategory.INSTANCE:
        position = _extract_vector(item.properties, "CENTER", [0, 0, 0])
        # Don't render instance directly — the part's GRAPHIC children handle it

    for child in item.children:
        _collect_renderable(child, items, instance_positions)


def _find_parent_part_instance(
    item: Any, instance_positions: Dict[str, List[float]]
) -> List[float]:
    """Find the instance position for a shape's parent part."""
    from .routes_model import get_document
    from ..models.base_item import ItemCategory

    doc = get_document()
    part_name = _find_part_keyname_for_shape(item, doc.assembly)
    if part_name:
        for inst in _find_instances(doc.assembly):
            part_ref = inst.properties.get("PART", "")
            if isinstance(part_ref, str) and part_ref.upper() == part_name.upper():
                return _extract_vector(inst.properties, "CENTER", [0, 0, 0])
    return [0, 0, 0]


def _find_part_keyname_for_shape(shape_item: Any, assembly: Any) -> str:
    """Find which part definition contains this shape."""
    from ..models.base_item import ItemCategory

    def _search(node: Any) -> str:
        if node.category in (ItemCategory.RIGID_PART, ItemCategory.FEM_PART):
            for child in node.children:
                if child.id == shape_item.id:
                    return node.keyname
        for child in node.children:
            result = _search(child)
            if result:
                return result
        return ""

    return _search(assembly)


def _find_instances(assembly: Any) -> list:
    """Find all INSTANCE items in the tree."""
    from ..models.base_item import ItemCategory

    result = []

    def _search(node: Any) -> None:
        if node.category == ItemCategory.INSTANCE:
            result.append(node)
        for child in node.children:
            _search(child)

    _search(assembly)
    return result


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
