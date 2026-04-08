"""Parse topo_0.xml — per-frame binary layout for all instances.

Each <RIGIDPART> / <MNFPART> declares:
- GlobalName (matches instance name used by the solver / scene graph)
- NODES + ELEMENTS (for MNFPART, the rest geometry)
- PartVariables and NodeVariables with frame-local byte offsets, component
  counts, and total sizes.

All result values in the .res binaries are float64 (double) — confirmed by
PART3_INS1 where NodeVariable "position" has size 390792 = 16283 × 3 × 8.
"""

from dataclasses import dataclass, field
from typing import Dict, List, Optional
from xml.etree import ElementTree as ET

import numpy as np


BYTES_PER_DOUBLE = 8


@dataclass
class PartVariable:
    name: str
    offset: int       # frame-local byte offset
    components: int
    size: int         # total bytes for this variable within one frame


@dataclass
class RigidPart:
    name: str
    stl_files: List[str] = field(default_factory=list)  # relative file names
    part_variables: Dict[str, PartVariable] = field(default_factory=dict)


@dataclass
class MNFPart:
    name: str
    num_nodes: int
    num_elements: int
    rest_nodes: np.ndarray            # (N, 3) float32 from <NODES>
    triangles: np.ndarray             # (M, 3) int32 — 0-based node indices
    part_variables: Dict[str, PartVariable] = field(default_factory=dict)
    node_variables: Dict[str, PartVariable] = field(default_factory=dict)


@dataclass
class Topo:
    frame_length: int = 0
    rigid_parts: List[RigidPart] = field(default_factory=list)
    mnf_parts: List[MNFPart] = field(default_factory=list)

    def find_rigid(self, name: str) -> Optional[RigidPart]:
        up = name.upper()
        for p in self.rigid_parts:
            if p.name.upper() == up:
                return p
        return None

    def find_mnf(self, name: str) -> Optional[MNFPart]:
        up = name.upper()
        for p in self.mnf_parts:
            if p.name.upper() == up:
                return p
        return None


def parse_topo(topo_path: str) -> Topo:
    """Parse topo_0.xml and return fully populated Topo."""
    topo = Topo()

    # Stream parse for memory efficiency (topo_0.xml can be >40 MB).
    context = ET.iterparse(topo_path, events=("end",))
    for _, elem in context:
        if elem.tag == "RIGIDPART":
            topo.rigid_parts.append(_parse_rigid_part(elem))
            elem.clear()
        elif elem.tag == "MNFPART":
            topo.mnf_parts.append(_parse_mnf_part(elem))
            elem.clear()

    # Compute frame length as max(offset + size) across all variables.
    max_end = 0
    for rp in topo.rigid_parts:
        for v in rp.part_variables.values():
            max_end = max(max_end, v.offset + v.size)
    for mp in topo.mnf_parts:
        for v in mp.part_variables.values():
            max_end = max(max_end, v.offset + v.size)
        for v in mp.node_variables.values():
            max_end = max(max_end, v.offset + v.size)
    topo.frame_length = max_end

    return topo


def _parse_variables(parent: ET.Element, tag: str) -> Dict[str, PartVariable]:
    """Read a <PartVariables> / <NodeVariables> / <ElementVariables> container."""
    container = parent.find(tag)
    out: Dict[str, PartVariable] = {}
    if container is None:
        return out
    child_tag = tag[:-1]  # "PartVariables" → "PartVariable"
    for v in container.findall(child_tag):
        out[v.attrib["name"]] = PartVariable(
            name=v.attrib["name"],
            offset=int(v.attrib["offset"]),
            components=int(v.attrib["NumberOfComponents"]),
            size=int(v.attrib["size"]),
        )
    return out


def _parse_rigid_part(elem: ET.Element) -> RigidPart:
    name = elem.attrib.get("GlobalName") or elem.attrib.get("name", "")
    stl_files: List[str] = []
    graphics = elem.find("GRAPHICS")
    if graphics is not None:
        for g in graphics.findall("GRAPHIC"):
            if g.attrib.get("type", "").upper() == "STL":
                files = g.attrib.get("FILES", "")
                if files:
                    stl_files.append(files)
    return RigidPart(
        name=name,
        stl_files=stl_files,
        part_variables=_parse_variables(elem, "PartVariables"),
    )


def _parse_mnf_part(elem: ET.Element) -> MNFPart:
    name = elem.attrib.get("GlobalName") or elem.attrib.get("name", "")
    num_nodes = int(elem.attrib.get("NumberOfNodes", 0))
    num_elements = int(elem.attrib.get("NumberOfElements", 0))

    rest_nodes = np.zeros((num_nodes, 3), dtype=np.float32)
    nodes_section = elem.find("NODES")
    max_id = 0
    if nodes_section is not None:
        for n in nodes_section.findall("NODE"):
            nid = int(n.attrib["id"])
            if n.text:
                parts = n.text.strip().split(",")
                if len(parts) >= 3:
                    if nid - 1 < num_nodes:
                        rest_nodes[nid - 1] = (
                            float(parts[0]),
                            float(parts[1]),
                            float(parts[2]),
                        )
                    max_id = max(max_id, nid)

    # Triangles: <ELEMENT type="TRIP">a,b,c</ELEMENT> — convert to 0-based.
    triangles_list: List[List[int]] = []
    elems_section = elem.find("ELEMENTS")
    if elems_section is not None:
        for e in elems_section.findall("ELEMENT"):
            if e.attrib.get("type", "").upper() != "TRIP":
                continue
            if e.text:
                ids = [int(x) for x in e.text.strip().split(",")]
                if len(ids) >= 3:
                    triangles_list.append([ids[0] - 1, ids[1] - 1, ids[2] - 1])
    triangles = (
        np.array(triangles_list, dtype=np.int32)
        if triangles_list
        else np.zeros((0, 3), dtype=np.int32)
    )

    return MNFPart(
        name=name,
        num_nodes=num_nodes,
        num_elements=num_elements,
        rest_nodes=rest_nodes,
        triangles=triangles,
        part_variables=_parse_variables(elem, "PartVariables"),
        node_variables=_parse_variables(elem, "NodeVariables"),
    )
