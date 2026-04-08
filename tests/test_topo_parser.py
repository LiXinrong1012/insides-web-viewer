"""Tests for topo_0.xml parser."""

from pathlib import Path

import numpy as np
import pytest

from server.results.topo_parser import parse_topo


SAMPLE = Path("E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined/result/topo_0.xml")

pytestmark = pytest.mark.skipif(
    not SAMPLE.is_file(), reason=f"sample topo not available: {SAMPLE}"
)


@pytest.fixture(scope="module")
def topo():
    return parse_topo(str(SAMPLE))


def test_total_instance_count(topo):
    total = len(topo.rigid_parts) + len(topo.mnf_parts)
    assert total == 70


def test_mnf_part_count(topo):
    # Sample: 6 × PART3, 6 × PART4, 2 × PART5, 1 × PART, 1 × P_4_75 + others
    assert len(topo.mnf_parts) >= 15


def test_part3_ins1_geometry(topo):
    p = topo.find_mnf("PART3_INS1")
    assert p is not None
    assert p.num_nodes == 16283
    assert p.num_elements == 27290
    assert p.rest_nodes.shape == (16283, 3)
    assert p.triangles.shape[0] == 27290
    assert p.triangles.shape[1] == 3
    assert p.triangles.min() >= 0
    assert p.triangles.max() < 16283


def test_part3_ins1_node_variables(topo):
    p = topo.find_mnf("PART3_INS1")
    pos = p.node_variables["position"]
    assert pos.components == 3
    assert pos.size == 16283 * 3 * 8
    up = p.node_variables["Up_Local"]
    assert up.size == 16283 * 3 * 8
    mises = p.node_variables["Mises Stress"]
    assert mises.components == 1
    assert mises.size == 16283 * 8


def test_rigid_part_variables(topo):
    p = topo.find_rigid("BC_ADAPTER_INS1")
    assert p is not None
    assert "position" in p.part_variables
    assert p.part_variables["position"].components == 3
    assert p.part_variables["position"].size == 24
    assert "phi" in p.part_variables


def test_frame_length_positive(topo):
    # Must cover the biggest variable end offset
    assert topo.frame_length > 0


def test_rest_nodes_match_reference(topo):
    p = topo.find_mnf("PART3_INS1")
    # Node 1 in the XML: 0.0549893,-0.0125692,0.104464
    np.testing.assert_allclose(
        p.rest_nodes[0], [0.0549893, -0.0125692, 0.104464], rtol=1e-5
    )
