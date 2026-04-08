"""Tests for .res binary reader."""

from pathlib import Path

import numpy as np
import pytest

from server.results.overview_parser import parse_overview
from server.results.res_reader import ResReader
from server.results.topo_parser import parse_topo


RESULT_DIR = Path("E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined/result")

pytestmark = pytest.mark.skipif(
    not (RESULT_DIR / "overview.xml").is_file(),
    reason=f"sample result not available: {RESULT_DIR}",
)


@pytest.fixture(scope="module")
def reader():
    frames = parse_overview(str(RESULT_DIR / "overview.xml"))
    topo = parse_topo(str(RESULT_DIR / "topo_0.xml"))
    return ResReader(str(RESULT_DIR), frames, topo), frames, topo


def test_read_mnf_position_frame1_matches_rest(reader):
    r, _, topo = reader
    part = topo.find_mnf("PART3_INS1")
    pos = r.read_mnf_node_variable(1, part, "position")
    assert pos.shape == (16283, 3)
    assert pos.dtype == np.float64
    # Frame 1 is t=0 — positions should essentially equal rest_nodes
    diff = np.abs(pos - part.rest_nodes).max()
    assert diff < 1e-3, f"max |pos - rest| = {diff}"


def test_read_mnf_mises_non_negative(reader):
    r, _, topo = reader
    part = topo.find_mnf("PART3_INS1")
    m = r.read_mnf_node_variable(1, part, "Mises Stress")
    assert m.shape == (16283,)
    assert np.isfinite(m).all()
    assert (m >= 0).all()


def test_read_mnf_position_midframe_changes(reader):
    r, _, topo = reader
    part = topo.find_mnf("PART3_INS1")
    pos_start = r.read_mnf_node_variable(1, part, "position")
    pos_mid = r.read_mnf_node_variable(250, part, "position")
    assert pos_mid.shape == pos_start.shape
    assert not np.allclose(pos_start, pos_mid, atol=1e-6), (
        "expected motion/deformation between frame 1 and frame 250"
    )
    # Positions must stay finite and bounded
    assert np.isfinite(pos_mid).all()
    assert np.abs(pos_mid).max() < 10.0  # model is in meters, << 10 m


def test_read_rigid_transform(reader):
    r, _, topo = reader
    part = topo.rigid_parts[0]
    t = r.read_rigid_transform(1, part)
    assert t["position"].shape == (3,)
    assert t["phi"].shape == (3,)
    assert np.isfinite(t["position"]).all()
    assert np.isfinite(t["phi"]).all()


def test_crosses_res_file_boundary(reader):
    # Frame 135 is the first frame in result_135.res (startpos=0).
    r, frames, topo = reader
    fmap = {f.frame_id: f for f in frames}
    assert fmap[135].res_file == "result_135.res"
    assert fmap[135].startpos == 0
    part = topo.find_mnf("PART3_INS1")
    pos = r.read_mnf_node_variable(135, part, "position")
    assert pos.shape == (16283, 3)
    assert np.isfinite(pos).all()
