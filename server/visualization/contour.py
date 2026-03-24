"""Scalar field to RGB color mapping for contour/cloud visualization."""

from typing import Any, Dict, List, Tuple

import numpy as np


def jet_colormap(t: float) -> Tuple[int, int, int]:
    """Map normalized value [0,1] to RGB using jet colormap. Returns (r,g,b) in [0,255]."""
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


def scalar_to_vertex_colors(values: np.ndarray, vmin: float = None, vmax: float = None) -> Dict[str, Any]:
    """Map scalar values per vertex to RGB colors using jet colormap.
    Returns {"colors": [r,g,b,...] as floats [0,1], "vmin": float, "vmax": float}
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

    return {"colors": colors.flatten().tolist(), "vmin": vmin, "vmax": vmax}


def generate_legend_data(vmin: float, vmax: float, steps: int = 10) -> List[Dict[str, Any]]:
    """Generate legend entries for the colorbar."""
    entries = []
    for i in range(steps + 1):
        t = i / steps
        value = vmin + t * (vmax - vmin)
        r, g, b = jet_colormap(t)
        entries.append({"value": value, "color": [r, g, b]})
    return entries
