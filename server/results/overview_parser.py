"""Parse overview.xml — frame index for INSIDES result files.

Mirrors ref_code/importtdyresult/TDYResults.cpp parsing of the <Simulation>
element: one <Frame> per time step, with the byte offset (startpos) and length
of the corresponding block inside a .res binary file.
"""

from dataclasses import dataclass
from pathlib import Path
from typing import List
from xml.etree import ElementTree as ET


@dataclass
class FrameMeta:
    frame_id: int
    time: float
    topo_file: str
    res_file: str
    startpos: int
    length: int


def parse_overview(overview_path: str) -> List[FrameMeta]:
    """Parse overview.xml and return the frame list in file order."""
    tree = ET.parse(overview_path)
    root = tree.getroot()
    frames: List[FrameMeta] = []
    for elem in root.findall("Frame"):
        frames.append(
            FrameMeta(
                frame_id=int(elem.attrib["id"]),
                time=float(elem.attrib["time"]),
                topo_file=elem.attrib.get("topofile", ""),
                res_file=elem.attrib.get("resfile", ""),
                startpos=int(elem.attrib["startpos"]),
                length=int(elem.attrib["length"]),
            )
        )
    return frames


def resolve_res_path(result_dir: str, frame: FrameMeta) -> Path:
    """Return absolute path to the .res file that holds this frame's data."""
    return Path(result_dir) / frame.res_file
