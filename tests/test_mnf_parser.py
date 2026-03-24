"""Tests for MNF XML parser."""
import os
import pytest
from server.visualization.mnf_parser import parse_mnf_xml, mnf_to_geometry


MNF_PATH = r"D:\freecad\temp\Res\C03005536_res\modes_set.mnf"


@pytest.mark.skipif(not os.path.exists(MNF_PATH), reason="MNF test file not available")
def test_parse_mnf_xml():
    result = parse_mnf_xml(MNF_PATH)
    assert result["num_nodes"] == 5687
    assert result["num_faces"] == 7722
    assert result["num_modes"] == 38
    assert len(result["nodes"]) == 5687


@pytest.mark.skipif(not os.path.exists(MNF_PATH), reason="MNF test file not available")
def test_mnf_nodes_have_positions():
    result = parse_mnf_xml(MNF_PATH)
    node = result["nodes"][0]
    assert len(node) == 4  # (id, x, y, z)
    assert isinstance(node[1], float)


@pytest.mark.skipif(not os.path.exists(MNF_PATH), reason="MNF test file not available")
def test_mnf_faces_are_triangles():
    result = parse_mnf_xml(MNF_PATH)
    for face in result["faces"][:10]:
        assert len(face) == 3
        for idx in face:
            assert 0 <= idx < result["num_nodes"]


@pytest.mark.skipif(not os.path.exists(MNF_PATH), reason="MNF test file not available")
def test_mnf_mode_shapes():
    result = parse_mnf_xml(MNF_PATH)
    assert result["mode_shapes"] is not None
    assert 7 in result["mode_shapes"]
    shape = result["mode_shapes"][7]
    assert shape.shape == (5687, 6)


@pytest.mark.skipif(not os.path.exists(MNF_PATH), reason="MNF test file not available")
def test_mnf_to_geometry():
    mnf_data = parse_mnf_xml(MNF_PATH)
    geo = mnf_to_geometry(mnf_data)
    assert geo["vertex_count"] == 5687
    assert geo["triangle_count"] == 7722
    assert len(geo["positions"]) == 5687 * 3
    assert len(geo["normals"]) == 5687 * 3
