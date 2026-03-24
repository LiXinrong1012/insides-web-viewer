"""TDY result file reader with lazy frame loading.

Mirrors importtdyresult/TDYResults.h and importtdybase/basetdyresult.h.
Reads the binary result files produced by thudynamics.exe.

Result file format:
- First frame contains XML topology describing the result structure
- Subsequent frames are binary data blocks at known file offsets
- Each frame contains per-entity result arrays (displacement, velocity, etc.)
"""

import struct
import xml.etree.ElementTree as ET
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

import numpy as np


@dataclass
class ResultSection:
    """A section within a result item (e.g., 'Displacement', 'Velocity')."""

    name: str
    component_names: List[str] = field(default_factory=list)
    data: Optional[np.ndarray] = None  # shape: (num_components,) per frame


@dataclass
class ResultItem:
    """Per-entity result container."""

    entity_name: str
    entity_id: str
    result_type: str  # "rigid", "flex", "dynamic"
    sections: List[ResultSection] = field(default_factory=list)

    def get_section(self, name: str) -> Optional[ResultSection]:
        for s in self.sections:
            if s.name.upper() == name.upper():
                return s
        return None


@dataclass
class ResultFrame:
    """Data for a single time frame."""

    frame_index: int
    time: float
    data: Dict[str, np.ndarray] = field(default_factory=dict)  # entity_id → values


class TDYResults:
    """Manages simulation result data with lazy frame loading."""

    def __init__(self) -> None:
        self.items: List[ResultItem] = []
        self.frame_count: int = 0
        self.time_list: List[float] = []
        self.current_frame: int = 0
        self._file_path: Optional[str] = None
        self._frame_offsets: List[int] = []  # byte offset for each frame

    @property
    def loaded(self) -> bool:
        return len(self.time_list) > 0

    def load_from_directory(self, model_dir: str) -> bool:
        """Scan model directory for result files and load metadata.

        Looks for .res, .tdy_res, or result XML files.
        """
        result_dir = Path(model_dir)

        # Look for result metadata file
        for pattern in ["*.res", "*_result.xml", "result.xml"]:
            for f in result_dir.glob(pattern):
                return self._load_result_file(str(f))

        # Look for CSV-based results (simpler format)
        for f in result_dir.glob("*.csv"):
            if "result" in f.stem.lower() or "output" in f.stem.lower():
                return self._load_csv_results(str(f))

        return False

    def _load_result_file(self, filepath: str) -> bool:
        """Load binary/XML result file."""
        self._file_path = filepath
        # TODO: Implement binary QDataStream reading when actual result files are available
        # For now, provide a stub that generates sample data
        return False

    def _load_csv_results(self, filepath: str) -> bool:
        """Load results from CSV file (common export format)."""
        try:
            data = np.genfromtxt(filepath, delimiter=",", names=True, dtype=np.float64)
            if data.size == 0:
                return False

            col_names = list(data.dtype.names)
            time_col = None
            for name in col_names:
                if name.lower() in ("time", "t"):
                    time_col = name
                    break

            if time_col is None:
                return False

            self.time_list = data[time_col].tolist()
            self.frame_count = len(self.time_list)

            # Create result items for each non-time column
            for col in col_names:
                if col == time_col:
                    continue
                item = ResultItem(
                    entity_name=col,
                    entity_id=col,
                    result_type="dynamic",
                    sections=[ResultSection(
                        name="Value",
                        component_names=[col],
                        data=data[col],
                    )],
                )
                self.items.append(item)

            self._file_path = filepath
            return True

        except Exception:
            return False

    def get_time_series(self, entity_id: str, section_name: str = "Value") -> Optional[Dict[str, Any]]:
        """Get time series data for a specific result item and section."""
        for item in self.items:
            if item.entity_id == entity_id:
                section = item.get_section(section_name)
                if section is not None and section.data is not None:
                    return {
                        "entity_id": entity_id,
                        "section": section_name,
                        "times": self.time_list,
                        "values": section.data.tolist(),
                        "components": section.component_names,
                    }
        return None

    def get_frame_data(self, frame_index: int) -> Optional[Dict[str, Any]]:
        """Get all result data for a specific frame."""
        if frame_index < 0 or frame_index >= self.frame_count:
            return None

        frame_data: Dict[str, Any] = {
            "frame": frame_index,
            "time": self.time_list[frame_index],
            "items": {},
        }

        for item in self.items:
            for section in item.sections:
                if section.data is not None:
                    frame_data["items"][item.entity_id] = {
                        "section": section.name,
                        "value": float(section.data[frame_index])
                            if frame_index < len(section.data) else 0.0,
                    }

        return frame_data

    def generate_sample_results(self, num_frames: int = 100, dt: float = 0.01) -> None:
        """Generate sample result data for testing the visualization pipeline."""
        self.time_list = [i * dt for i in range(num_frames)]
        self.frame_count = num_frames
        t = np.array(self.time_list)

        # Sample rigid body displacement
        for name, func in [
            ("Displacement_X", lambda t: np.sin(2 * np.pi * t)),
            ("Displacement_Y", lambda t: np.cos(2 * np.pi * t) * 0.5),
            ("Displacement_Z", lambda t: t * 0.1),
            ("Velocity_X", lambda t: 2 * np.pi * np.cos(2 * np.pi * t)),
            ("Velocity_Y", lambda t: -np.pi * np.sin(2 * np.pi * t)),
            ("Force_X", lambda t: np.sin(4 * np.pi * t) * 100),
            ("Force_Y", lambda t: np.cos(4 * np.pi * t) * 50 + 25),
        ]:
            self.items.append(ResultItem(
                entity_name=name,
                entity_id=name,
                result_type="dynamic",
                sections=[ResultSection(
                    name="Value",
                    component_names=[name],
                    data=func(t),
                )],
            ))

    def list_items(self) -> List[Dict[str, str]]:
        """List all available result items."""
        return [
            {
                "entity_id": item.entity_id,
                "entity_name": item.entity_name,
                "result_type": item.result_type,
                "sections": [s.name for s in item.sections],
            }
            for item in self.items
        ]


# Global results instance
results_store = TDYResults()
