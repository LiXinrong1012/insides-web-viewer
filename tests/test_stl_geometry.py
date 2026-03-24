"""Tests for STL mesh loading in scene API."""
import os
import pytest
from server.visualization.mesh_processor import parse_stl_file


STL_PATH = r"D:\research\smee\pob_tdy\m_C01141396.stl"


@pytest.mark.skipif(not os.path.exists(STL_PATH), reason="STL test file not available")
def test_parse_stl_file():
    result = parse_stl_file(STL_PATH)
    assert result["vertex_count"] > 0
    assert result["triangle_count"] > 0
    assert len(result["positions"]) == result["vertex_count"] * 3
    assert len(result["normals"]) == result["vertex_count"] * 3
    assert len(result["indices"]) == result["vertex_count"]


@pytest.mark.skipif(not os.path.exists(STL_PATH), reason="STL test file not available")
def test_stl_positions_are_floats():
    result = parse_stl_file(STL_PATH)
    for v in result["positions"][:9]:
        assert isinstance(v, float)
