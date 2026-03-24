"""Tests for contour colormap."""
import numpy as np
from server.visualization.contour import jet_colormap, scalar_to_vertex_colors, generate_legend_data


def test_jet_colormap_range():
    """Jet colormap should return values in [0, 255]."""
    for t in [0.0, 0.25, 0.5, 0.75, 1.0]:
        r, g, b = jet_colormap(t)
        assert 0 <= r <= 255
        assert 0 <= g <= 255
        assert 0 <= b <= 255


def test_jet_colormap_blue_to_red():
    """Low values should be blue-ish, high values red-ish."""
    r0, g0, b0 = jet_colormap(0.0)
    assert b0 > r0  # blue dominant at low end
    r1, g1, b1 = jet_colormap(1.0)
    assert r1 > b1  # red dominant at high end


def test_scalar_to_vertex_colors():
    values = np.array([0.0, 0.5, 1.0])
    result = scalar_to_vertex_colors(values)
    assert len(result["colors"]) == 9  # 3 vertices * 3 components
    assert result["vmin"] == 0.0
    assert result["vmax"] == 1.0


def test_generate_legend():
    legend = generate_legend_data(0.0, 100.0, steps=5)
    assert len(legend) == 6  # steps + 1
    assert legend[0]["value"] == 0.0
    assert legend[-1]["value"] == 100.0
