"""Tests for overview.xml parser (frame metadata)."""

from pathlib import Path

import pytest

from server.results.overview_parser import FrameMeta, parse_overview


SAMPLE_DIR = Path("E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined/result")
OVERVIEW = SAMPLE_DIR / "overview.xml"


pytestmark = pytest.mark.skipif(
    not OVERVIEW.is_file(), reason=f"sample overview not available: {OVERVIEW}"
)


def test_parses_all_frames():
    frames = parse_overview(str(OVERVIEW))
    assert len(frames) == 502
    assert all(isinstance(f, FrameMeta) for f in frames)


def test_first_frame_metadata():
    frames = parse_overview(str(OVERVIEW))
    f0 = frames[0]
    assert f0.frame_id == 1
    assert f0.time == pytest.approx(0.0)
    assert f0.res_file == "result_1.res"
    assert f0.startpos == 0
    assert f0.length == 15624808
    assert f0.topo_file == "topo_0.xml"


def test_frame_time_monotonic():
    frames = parse_overview(str(OVERVIEW))
    times = [f.time for f in frames]
    assert times[1] == pytest.approx(1e-5)
    for i in range(1, len(times)):
        assert times[i] > times[i - 1]


def test_frames_distributed_across_res_files():
    frames = parse_overview(str(OVERVIEW))
    files = {f.res_file for f in frames}
    assert files == {
        "result_1.res",
        "result_135.res",
        "result_269.res",
        "result_403.res",
    }


def test_frame_135_resets_startpos():
    frames = parse_overview(str(OVERVIEW))
    by_id = {f.frame_id: f for f in frames}
    assert by_id[135].res_file == "result_135.res"
    assert by_id[135].startpos == 0
