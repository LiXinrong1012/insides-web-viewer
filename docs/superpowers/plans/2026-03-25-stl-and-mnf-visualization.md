# STL Rigid Body & MNF Flexible Body Visualization

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Render STL-represented rigid bodies as full triangle meshes and MNF flexible bodies with surface mesh + mode shape / contour visualization in the web viewer.

**Architecture:** Backend parses STL files from disk and MNF XML+binary for mesh geometry. The `/api/geometry/scene` endpoint returns mesh buffer data (positions/normals/indices) inline for each renderable item. Frontend creates Three.js `BufferGeometry` from this data. Contour maps use per-vertex coloring with a jet colormap and an on-screen legend.

**Tech Stack:** Python (FastAPI, numpy, xml.etree), TypeScript (React, Three.js), existing mesh_processor.py utilities.

---

## File Structure

| File | Responsibility |
|------|---------------|
| `server/visualization/mesh_processor.py` (modify) | Add `parse_stl_file_to_geometry()` wrapper, keep existing STL parsers |
| `server/visualization/mnf_parser.py` (create) | Parse MNF XML: nodes, faces, mode shapes from XML+binary |
| `server/visualization/contour.py` (create) | Scalar→RGB mapping (jet colormap), legend data generation |
| `server/api/routes_geometry.py` (modify) | Serve STL mesh + MNF mesh inline in scene data; add contour endpoint |
| `server/parsers/model_builder.py` (modify) | Extract STL filename and MNF_FILE path from GRAPHIC/MNF6 keywords |
| `client/src/components/viewer3d/SceneView.tsx` (modify) | Render buffer geometries from mesh data, apply per-vertex colors |
| `client/src/components/viewer3d/ContourLegend.tsx` (create) | Color bar overlay showing min/max/colormap |
| `tests/test_stl_geometry.py` (create) | STL loading + scene API tests |
| `tests/test_mnf_parser.py` (create) | MNF XML parsing tests |

---

### Task 1: Extract STL filename in parser

**Files:**
- Modify: `server/parsers/model_builder.py:100-115`

- [ ] **Step 1: Fix GRAPHIC handler to capture STL filename**

In `_process_part_child`, when shape_type is STL, the `STL` key-value already gets stored via `_update_key_values`. But the parser stores it as property `STL=path` in `key_values`. We need to ensure the STL path is accessible as `properties["STL"]`. Check that the existing `_update_key_values` call at line 114 already handles this — it should, since `STL = D:\path\file.stl` is a key-value pair.

Actually, looking at the TDY format: `Graphic/1, CM = Origin, STL = D:\research\smee\pob_tdy\m_C01141396.stl`

The parser sees `STL` as a key with value being the path. `_update_key_values` stores it as `properties["STL"] = "D:\\research\\..."`. This already works. But we also need `_shape_type` to be set to `"STL"`.

The current code checks `ast_item.main_label` and `ast_item.properties` for shape types, but `STL` comes as a **key-value** (`STL = path`), not a property flag. Fix this:

```python
elif kw == "GRAPHIC":
    child.category = ItemCategory.SHAPE
    shape_types = {"BOX", "CYLINDER", "SPHERE", "STL"}
    if ast_item.main_label and ast_item.main_label.upper() in shape_types:
        child.properties["_shape_type"] = ast_item.main_label.upper()
    else:
        for prop in ast_item.properties:
            if prop.name.upper() in shape_types:
                child.properties["_shape_type"] = prop.name.upper()
                break
        # Also check key-values (STL = filepath is a KV, not a property flag)
        if "_shape_type" not in child.properties:
            for kv in ast_item.key_values:
                if kv.keyname.upper() in shape_types:
                    child.properties["_shape_type"] = kv.keyname.upper()
                    break
```

Apply the same fix to `_handle_graphic` (lines 202-218) which has identical logic.

- [ ] **Step 2: Verify with existing TDY file**

Run: `PYTHONIOENCODING=utf-8 conda run -n insides_web python -c "from server.parsers.tdy_parser import TDYParser; from server.parsers.model_builder import ModelBuilder; p=TDYParser(); ast=p.parse_file('uploads/main.tdy'); b=ModelBuilder(); m=b.build(ast); items=[]; [items.append((c.keyname, c.properties.get('_shape_type','?'), c.properties.get('STL','?')[:40] if isinstance(c.properties.get('STL',''),str) else '?')) for c in _find_shapes(m)]; print(items[:5])"`

Expected: Shape items with `_shape_type='STL'` and `STL='D:\research\smee\...'`

- [ ] **Step 3: Commit**

```bash
git add server/parsers/model_builder.py
git commit -m "fix: detect STL shape type from key-value pairs in GRAPHIC"
```

---

### Task 2: Extract MNF_FILE path from MNFPART/MNF6

**Files:**
- Modify: `server/parsers/model_builder.py:68-79`

- [ ] **Step 1: Store MNF_FILE path on FEM_PART item**

The MNFPART block contains a child `MNF6` with `MNF_FILE = path`. The current `_handle_fem_part` processes children via `_process_part_child`, which stores MNF6 as a PARAMETER child. The MNF_FILE is stored on the MNF6 child item, but we need it on the FEM_PART parent for easy access.

After processing children, hoist MNF_FILE up:

```python
def _handle_fem_part(builder, ast_item, parent):
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or ast_item.keyname,
        category=ItemCategory.FEM_PART,
    )
    _update_key_values(item, ast_item)
    item.properties["_part_type"] = ast_item.keyname.upper()
    if isinstance(ast_item, ASTAssembly):
        for child in ast_item.children:
            _process_part_child(builder, child, item)
        # Hoist MNF_FILE from MNF6 child to part level
        for child_item in item.children:
            mnf_file = child_item.properties.get("MNF_FILE")
            if mnf_file:
                item.properties["_mnf_file"] = mnf_file
                break
    _add_to_folder(parent, "Parts", item)
```

- [ ] **Step 2: Commit**

```bash
git add server/parsers/model_builder.py
git commit -m "feat: hoist MNF_FILE path to FEM_PART item for mesh loading"
```

---

### Task 3: Serve STL mesh data in scene API

**Files:**
- Modify: `server/api/routes_geometry.py:69-123`

- [ ] **Step 1: Add STL mesh loading to _collect_renderable**

When a SHAPE item has `_shape_type == "STL"` and a valid STL path, load the mesh and include buffer data in the response:

```python
from ..visualization.mesh_processor import parse_stl_file

# In _collect_renderable, inside the SHAPE branch:
if item.category == ItemCategory.SHAPE:
    shape_type = item.properties.get("_shape_type", "box").lower()
    ...

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

    # For STL: include mesh buffer data
    if shape_type == "stl":
        stl_path = item.properties.get("STL", "")
        if stl_path and Path(stl_path).is_file():
            try:
                mesh_data = parse_stl_file(str(stl_path))
                entry["mesh"] = mesh_data
            except Exception:
                pass  # Fall back to default box

    items.append(entry)
```

- [ ] **Step 2: Add Path import and test**

Add `from pathlib import Path` at top of routes_geometry.py.

- [ ] **Step 3: Commit**

```bash
git add server/api/routes_geometry.py
git commit -m "feat: serve STL mesh buffer data inline in scene response"
```

---

### Task 4: Render STL meshes in Three.js

**Files:**
- Modify: `client/src/components/viewer3d/SceneView.tsx:125-159`

- [ ] **Step 1: Add mesh buffer geometry handler**

In the `loadScene` function, add a case for items that have `mesh` data:

```typescript
interface SceneItem {
  id: number;
  keyname: string;
  category: string;
  position: number[];
  geometry: string;
  radius?: number;
  height?: number;
  color?: number[];
  mesh?: {
    positions: number[];
    normals: number[];
    indices: number[];
  };
}

// In the for-loop over items:
for (const item of items) {
  let geometry: THREE.BufferGeometry;
  const r = item.radius ?? 0.05;
  const h = item.height ?? 0.5;

  if (item.mesh) {
    // Buffer geometry from mesh data (STL or FEM)
    geometry = new THREE.BufferGeometry();
    const pos = new Float32Array(item.mesh.positions);
    const norm = new Float32Array(item.mesh.normals);
    const idx = new Uint32Array(item.mesh.indices);
    geometry.setAttribute("position", new THREE.BufferAttribute(pos, 3));
    geometry.setAttribute("normal", new THREE.BufferAttribute(norm, 3));
    geometry.setIndex(new THREE.BufferAttribute(idx, 1));
  } else {
    switch (item.geometry) {
      case "sphere":
        geometry = new THREE.SphereGeometry(r, 16, 12);
        break;
      case "cylinder":
        geometry = new THREE.CylinderGeometry(r, r, h, 20);
        break;
      case "marker":
        geometry = new THREE.SphereGeometry(0.02, 8, 6);
        break;
      default:
        geometry = new THREE.BoxGeometry(r * 2, r * 2, r * 2);
    }
  }
  // ... rest of material/mesh creation
}
```

- [ ] **Step 2: Use MeshStandardMaterial for better mesh appearance**

For mesh items, use double-sided rendering and better material:

```typescript
const material = item.mesh
  ? new THREE.MeshPhongMaterial({
      color,
      side: THREE.DoubleSide,
      shininess: 40,
      flatShading: false,
    })
  : new THREE.MeshPhongMaterial({
      color,
      transparent: item.category === "MARKER",
      opacity: item.category === "MARKER" ? 0.5 : 1.0,
      shininess: 60,
    });
```

- [ ] **Step 3: Auto-fit camera to scene bounds**

After loading all meshes, compute bounding box and fit camera:

```typescript
// After the for-loop:
const box = new THREE.Box3();
scene.children.forEach((c) => {
  if ((c as THREE.Mesh).isMesh) box.expandByObject(c);
});
if (!box.isEmpty()) {
  const center = box.getCenter(new THREE.Vector3());
  const size = box.getSize(new THREE.Vector3());
  const maxDim = Math.max(size.x, size.y, size.z);
  const dist = maxDim * 1.5;
  refs.camera.position.set(center.x + dist * 0.6, center.y + dist * 0.5, center.z + dist * 0.6);
  refs.controls.target.copy(center);
  refs.camera.near = maxDim * 0.001;
  refs.camera.far = maxDim * 100;
  refs.camera.updateProjectionMatrix();
}
```

- [ ] **Step 4: Commit**

```bash
git add client/src/components/viewer3d/SceneView.tsx
git commit -m "feat: render STL mesh buffer geometries in 3D viewer with auto-fit camera"
```

---

### Task 5: MNF XML parser

**Files:**
- Create: `server/visualization/mnf_parser.py`

- [ ] **Step 1: Implement MNF XML parser**

```python
"""Parse MNF XML format: extract nodes, surface faces, and mode shapes."""

import struct
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

import numpy as np


def parse_mnf_xml(mnf_file_path: str) -> Dict[str, Any]:
    """Parse an MNF XML + binary data file pair.

    The MNF format consists of:
    - modes_set.xml: metadata (node positions, face connectivity, mode shape offsets)
    - modes_set.dat: binary data (node positions, mode shapes, etc.)

    Args:
        mnf_file_path: Path to the .mnf file. The actual data is in
            a sibling directory with the same stem (e.g., modes_set/modes_set.xml).

    Returns:
        Dict with keys: nodes, faces, num_modes, mode_shapes (optional)
    """
    mnf_path = Path(mnf_file_path)
    # MNF directory: same stem as .mnf file, in same parent
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

    # Parse nodes: ID, position
    nodes = _parse_nodes(root, num_nodes, dat_path)

    # Parse faces: triangulated surface
    faces = _parse_faces(root, num_faces)

    # Parse mode shapes (for deformation visualization)
    mode_shapes = None
    if dat_path.is_file():
        mode_shapes = _parse_mode_shapes(root, num_nodes, num_modes, dat_path)

    return {
        "num_nodes": len(nodes),
        "num_faces": len(faces),
        "num_modes": num_modes,
        "nodes": nodes,          # List of (id, x, y, z)
        "faces": faces,          # List of [n0, n1, n2] (local_idx based)
        "mode_shapes": mode_shapes,  # Optional: {mode_num: ndarray(num_nodes, 6)}
    }


def _parse_nodes(root: ET.Element, num_nodes: int, dat_path: Path) -> List[Tuple[int, float, float, float]]:
    """Parse node IDs and positions from XML NODE elements."""
    nodes_section = root.find("NODES")
    if nodes_section is None:
        return []

    nodes = []
    for node_elem in nodes_section.findall("NODE"):
        node_id = int(node_elem.attrib["ID"])
        pos_text = node_elem.text.strip() if node_elem.text else "0,0,0"
        coords = [float(v) for v in pos_text.split(",")]
        nodes.append((node_id, coords[0], coords[1], coords[2]))

    return nodes


def _parse_faces(root: ET.Element, num_faces: int) -> List[List[int]]:
    """Parse surface face connectivity from XML FACE elements."""
    faces_section = root.find("FACES")
    if faces_section is None:
        return []

    faces = []
    for face_elem in faces_section.findall("FACE"):
        num_nodes = int(face_elem.attrib.get("NumOfNodes", 3))
        node_text = face_elem.text.strip() if face_elem.text else ""
        node_indices = [int(v) for v in node_text.split(",")]

        if num_nodes == 3:
            faces.append(node_indices[:3])
        elif num_nodes == 4:
            # Split quad into 2 triangles
            faces.append([node_indices[0], node_indices[1], node_indices[2]])
            faces.append([node_indices[0], node_indices[2], node_indices[3]])

    return faces


def _parse_mode_shapes(
    root: ET.Element, num_nodes: int, num_modes: int, dat_path: Path
) -> Optional[Dict[int, np.ndarray]]:
    """Parse mode shape data from binary file.

    Each mode has 6 components per node (dx, dy, dz, ax, ay, az).
    """
    modes_section = root.find("MODES")
    if modes_section is None:
        return None

    mode_shapes = {}
    dat_data = dat_path.read_bytes()

    for mode_elem in modes_section.findall("MODE"):
        mode_num = int(mode_elem.attrib["ModeNumber"])
        offset = int(mode_elem.attrib["offset"])
        length = int(mode_elem.attrib["length"])

        # 6 doubles per node
        expected_length = num_nodes * 6 * 8
        if offset + expected_length <= len(dat_data):
            arr = np.frombuffer(dat_data, dtype=np.float64, count=num_nodes * 6, offset=offset)
            mode_shapes[mode_num] = arr.reshape(num_nodes, 6)

    return mode_shapes


def mnf_to_geometry(mnf_data: Dict[str, Any]) -> Dict[str, Any]:
    """Convert parsed MNF data to Three.js buffer geometry.

    Uses the surface faces (already triangulated) and node positions.
    """
    nodes = mnf_data["nodes"]
    faces = mnf_data["faces"]

    if not nodes or not faces:
        return {"positions": [], "normals": [], "indices": [], "vertex_count": 0, "triangle_count": 0}

    # Build position array indexed by local_idx (0-based)
    max_local_idx = max(len(nodes) - 1, 0)
    positions = np.zeros((len(nodes), 3), dtype=np.float32)
    for i, (node_id, x, y, z) in enumerate(nodes):
        positions[i] = [x, y, z]

    # Build index array from faces (faces use local_idx)
    indices = []
    for face in faces:
        if all(0 <= idx < len(nodes) for idx in face):
            indices.extend(face)

    # Compute normals
    normals = np.zeros_like(positions)
    for i in range(0, len(indices) - 2, 3):
        i0, i1, i2 = indices[i], indices[i + 1], indices[i + 2]
        p0, p1, p2 = positions[i0], positions[i1], positions[i2]
        edge1 = p1 - p0
        edge2 = p2 - p0
        normal = np.cross(edge1, edge2)
        norm_len = np.linalg.norm(normal)
        if norm_len > 0:
            normal = normal / norm_len
        normals[i0] += normal
        normals[i1] += normal
        normals[i2] += normal

    # Normalize
    norms = np.linalg.norm(normals, axis=1, keepdims=True)
    norms[norms == 0] = 1.0
    normals = normals / norms

    return {
        "positions": positions.flatten().tolist(),
        "normals": normals.flatten().tolist(),
        "indices": indices,
        "vertex_count": len(nodes),
        "triangle_count": len(indices) // 3,
    }
```

- [ ] **Step 2: Commit**

```bash
git add server/visualization/mnf_parser.py
git commit -m "feat: add MNF XML parser for flexible body mesh extraction"
```

---

### Task 6: Serve MNF mesh in scene API

**Files:**
- Modify: `server/api/routes_geometry.py:100-116`

- [ ] **Step 1: Add FEM_PART mesh loading**

In `_collect_renderable`, when a FEM_PART has `_mnf_file`, load and serve the mesh:

```python
from ..visualization.mnf_parser import parse_mnf_xml, mnf_to_geometry

# In the FEM_PART/RIGID_PART branch:
elif item.category in (ItemCategory.RIGID_PART, ItemCategory.FEM_PART):
    has_graphics = any(c.category == ItemCategory.SHAPE for c in item.children)

    if item.category == ItemCategory.FEM_PART and not has_graphics:
        # Try to load MNF mesh
        mnf_file = item.properties.get("_mnf_file", "")
        position = _extract_vector(item.properties, "QG", [0, 0, 0])
        entry = {
            "id": item.id,
            "keyname": item.keyname,
            "category": "FEM_PART",
            "position": position,
            "geometry": "fem_mesh",
            "color": [100, 180, 255],
        }
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
        # Fallback box for rigid parts without graphics
        position = _extract_vector(item.properties, "QG", [0, 0, 0])
        items.append({
            "id": item.id,
            "keyname": item.keyname,
            "category": item.category.name,
            "position": position,
            "geometry": "box",
            "radius": 0.1,
            "height": 0.2,
            "color": [128, 128, 200],
        })
```

- [ ] **Step 2: Commit**

```bash
git add server/api/routes_geometry.py
git commit -m "feat: serve MNF flexible body mesh data in scene API"
```

---

### Task 7: Contour colormap module

**Files:**
- Create: `server/visualization/contour.py`

- [ ] **Step 1: Implement jet colormap and scalar-to-color mapping**

```python
"""Scalar field to RGB color mapping for contour/cloud visualization."""

from typing import Any, Dict, List, Tuple

import numpy as np


def jet_colormap(t: float) -> Tuple[int, int, int]:
    """Map a normalized value [0,1] to RGB using jet colormap.

    Returns (r, g, b) each in [0, 255].
    """
    t = max(0.0, min(1.0, t))

    if t < 0.125:
        r, g, b = 0.0, 0.0, 0.5 + 4.0 * t
    elif t < 0.375:
        r, g, b = 0.0, 4.0 * (t - 0.125), 1.0
    elif t < 0.625:
        r, g, b = 4.0 * (t - 0.375), 1.0, 1.0 - 4.0 * (t - 0.375)
    elif t < 0.875:
        r, g, b = 1.0, 1.0 - 4.0 * (t - 0.625), 0.0
    else:
        r, g, b = 1.0 - 4.0 * (t - 0.875), 0.0, 0.0

    return (int(r * 255), int(g * 255), int(b * 255))


def scalar_to_vertex_colors(
    values: np.ndarray,
    vmin: float = None,
    vmax: float = None,
) -> Dict[str, Any]:
    """Map scalar values per vertex to RGB colors using jet colormap.

    Args:
        values: 1D array of scalar values, one per vertex
        vmin, vmax: optional range (auto-computed if None)

    Returns:
        {"colors": [r,g,b, r,g,b, ...] as floats [0,1], "vmin": float, "vmax": float}
    """
    if vmin is None:
        vmin = float(np.min(values))
    if vmax is None:
        vmax = float(np.max(values))

    rng = vmax - vmin
    if rng < 1e-30:
        rng = 1.0

    colors = np.zeros((len(values), 3), dtype=np.float32)
    for i, v in enumerate(values):
        t = (v - vmin) / rng
        r, g, b = jet_colormap(t)
        colors[i] = [r / 255.0, g / 255.0, b / 255.0]

    return {
        "colors": colors.flatten().tolist(),
        "vmin": vmin,
        "vmax": vmax,
    }


def generate_legend_data(vmin: float, vmax: float, steps: int = 10) -> List[Dict[str, Any]]:
    """Generate legend entries for the colorbar.

    Returns list of {"value": float, "color": [r,g,b]} from min to max.
    """
    entries = []
    for i in range(steps + 1):
        t = i / steps
        value = vmin + t * (vmax - vmin)
        r, g, b = jet_colormap(t)
        entries.append({"value": value, "color": [r, g, b]})
    return entries
```

- [ ] **Step 2: Commit**

```bash
git add server/visualization/contour.py
git commit -m "feat: add jet colormap and scalar-to-vertex-color mapping"
```

---

### Task 8: Contour API endpoint for MNF mode shapes

**Files:**
- Modify: `server/api/routes_geometry.py`

- [ ] **Step 1: Add contour endpoint**

```python
@router.get("/contour/{item_id}")
async def get_contour(item_id: int, mode: int = 7, component: str = "magnitude"):
    """Get contour color data for a FEM part's mode shape.

    Args:
        item_id: FEM_PART item ID
        mode: mode number (default 7 = first elastic mode)
        component: "dx", "dy", "dz", "magnitude" (displacement), "ax", "ay", "az"
    """
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
```

- [ ] **Step 2: Commit**

```bash
git add server/api/routes_geometry.py
git commit -m "feat: add contour endpoint for MNF mode shape visualization"
```

---

### Task 9: Frontend contour legend component

**Files:**
- Create: `client/src/components/viewer3d/ContourLegend.tsx`

- [ ] **Step 1: Implement color bar overlay**

```tsx
interface LegendEntry {
  value: number;
  color: number[];
}

interface ContourLegendProps {
  entries: LegendEntry[];
  title?: string;
}

export default function ContourLegend({ entries, title }: ContourLegendProps) {
  if (!entries || entries.length === 0) return null;

  return (
    <div style={{
      position: "absolute", right: 12, top: 40, width: 40,
      background: "rgba(30,30,30,0.85)", borderRadius: 4, padding: "4px 6px",
      color: "#ccc", fontSize: 10, pointerEvents: "none",
    }}>
      {title && <div style={{ textAlign: "center", marginBottom: 2, fontSize: 9 }}>{title}</div>}
      <div style={{ display: "flex", flexDirection: "column-reverse" }}>
        {entries.map((e, i) => (
          <div key={i} style={{ display: "flex", alignItems: "center", gap: 3 }}>
            <div style={{
              width: 14, height: entries.length > 8 ? 10 : 14,
              background: `rgb(${e.color[0]},${e.color[1]},${e.color[2]})`,
              flexShrink: 0,
            }} />
            <span style={{ fontSize: 8, whiteSpace: "nowrap" }}>
              {e.value.toExponential(2)}
            </span>
          </div>
        ))}
      </div>
    </div>
  );
}
```

- [ ] **Step 2: Commit**

```bash
git add client/src/components/viewer3d/ContourLegend.tsx
git commit -m "feat: add ContourLegend color bar overlay component"
```

---

### Task 10: Wire contour rendering into SceneView

**Files:**
- Modify: `client/src/components/viewer3d/SceneView.tsx`

- [ ] **Step 1: Add contour state and fetch logic**

Add state for active contour and a function to apply vertex colors:

```typescript
const [contour, setContour] = useState<{entries: any[], title: string} | null>(null);

const applyContour = useCallback(async (itemId: number, mode: number = 7) => {
  const refs = sceneRef.current;
  if (!refs) return;

  try {
    const res = await fetch(`/api/geometry/contour/${itemId}?mode=${mode}&component=magnitude`);
    const data = await res.json();

    // Find the mesh in scene by itemId
    const mesh = refs.scene.children.find(
      (c) => (c as THREE.Mesh).userData?.itemId === itemId
    ) as THREE.Mesh | undefined;

    if (mesh && data.colors) {
      const colors = new Float32Array(data.colors);
      mesh.geometry.setAttribute("color", new THREE.BufferAttribute(colors, 3));
      (mesh.material as THREE.MeshPhongMaterial).vertexColors = true;
      (mesh.material as THREE.MeshPhongMaterial).needsUpdate = true;
    }

    setContour({ entries: data.legend, title: `Mode ${mode}` });
  } catch {
    // silently fail
  }
}, []);
```

- [ ] **Step 2: Add contour controls in the toolbar**

Add buttons next to Refresh/Reset for contour mode toggling.

- [ ] **Step 3: Render ContourLegend**

```tsx
import ContourLegend from "./ContourLegend";

// In the return JSX:
{contour && <ContourLegend entries={contour.entries} title={contour.title} />}
```

- [ ] **Step 4: Commit**

```bash
git add client/src/components/viewer3d/SceneView.tsx
git commit -m "feat: add contour rendering with vertex colors and legend overlay"
```

---

### Task 11: Fix instance position resolution

**Files:**
- Modify: `server/api/routes_geometry.py:126-154`

- [ ] **Step 1: Fix _find_parent_part_instance to properly resolve positions**

The current implementation is broken (has `pass` and `break`). Replace with working logic:

```python
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
```

- [ ] **Step 2: Also resolve FEM_PART instance positions**

For FEM_PARTs, search instances the same way:

```python
# In _collect_renderable, FEM_PART branch:
# After getting mnf_file
position = _extract_vector(item.properties, "QG", [0, 0, 0])
# Also check instance CENTER
for inst in _find_instances(doc.assembly):
    part_ref = inst.properties.get("PART", "")
    if isinstance(part_ref, str) and part_ref.upper() == item.keyname.upper():
        position = _extract_vector(inst.properties, "CENTER", [0, 0, 0])
        break
```

- [ ] **Step 3: Commit**

```bash
git add server/api/routes_geometry.py
git commit -m "fix: properly resolve instance positions for parts and shapes"
```

---

### Task 12: Integration test

**Files:**
- Create: `tests/test_stl_geometry.py`
- Create: `tests/test_mnf_parser.py`

- [ ] **Step 1: Write STL test**

```python
"""Tests for STL mesh loading in scene API."""
import pytest
from server.visualization.mesh_processor import parse_stl_file

def test_parse_stl_binary_file():
    """Test that a real STL file parses correctly."""
    import os
    stl_path = r"D:\research\smee\pob_tdy\m_C01141396.stl"
    if not os.path.exists(stl_path):
        pytest.skip("STL test file not available")
    result = parse_stl_file(stl_path)
    assert result["vertex_count"] > 0
    assert result["triangle_count"] > 0
    assert len(result["positions"]) == result["vertex_count"] * 3
```

- [ ] **Step 2: Write MNF test**

```python
"""Tests for MNF XML parser."""
import pytest
from server.visualization.mnf_parser import parse_mnf_xml, mnf_to_geometry

def test_parse_mnf_xml():
    """Test MNF XML parsing with real file."""
    import os
    mnf_path = r"D:\freecad\temp\Res\C03005536_res\modes_set.mnf"
    if not os.path.exists(mnf_path):
        pytest.skip("MNF test file not available")
    result = parse_mnf_xml(mnf_path)
    assert result["num_nodes"] > 0
    assert result["num_faces"] > 0
    assert len(result["nodes"]) == result["num_nodes"]

def test_mnf_to_geometry():
    """Test MNF to Three.js geometry conversion."""
    import os
    mnf_path = r"D:\freecad\temp\Res\C03005536_res\modes_set.mnf"
    if not os.path.exists(mnf_path):
        pytest.skip("MNF test file not available")
    mnf_data = parse_mnf_xml(mnf_path)
    geo = mnf_to_geometry(mnf_data)
    assert geo["vertex_count"] > 0
    assert geo["triangle_count"] > 0
```

- [ ] **Step 3: Run tests**

Run: `conda run -n insides_web pytest tests/test_stl_geometry.py tests/test_mnf_parser.py -v`

- [ ] **Step 4: Commit**

```bash
git add tests/test_stl_geometry.py tests/test_mnf_parser.py
git commit -m "test: add STL and MNF parser integration tests"
```
