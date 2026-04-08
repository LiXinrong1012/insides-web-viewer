"""Tests for ResultManager singleton and /api/results endpoints."""

from pathlib import Path

import numpy as np
import pytest
from fastapi.testclient import TestClient

from server.main import app
from server.results.result_manager import result_manager


RESULT_DIR = Path("E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined/result")

pytestmark = pytest.mark.skipif(
    not (RESULT_DIR / "overview.xml").is_file(),
    reason=f"sample result not available: {RESULT_DIR}",
)


@pytest.fixture(scope="module")
def client():
    c = TestClient(app)
    r = c.post("/api/results/open", json={"result_dir": str(RESULT_DIR)})
    assert r.status_code == 200, r.text
    yield c
    c.post("/api/results/close")


def test_open_populates_manager(client):
    assert result_manager.loaded
    assert len(result_manager.frames) == 502
    assert result_manager.topo is not None


def test_status_endpoint(client):
    r = client.get("/api/results/status")
    assert r.status_code == 200
    s = r.json()
    assert s["loaded"] is True
    assert s["frame_count"] == 502
    assert s["time_range"][0] == pytest.approx(0.0)


def test_topo_endpoint(client):
    r = client.get("/api/results/topo")
    assert r.status_code == 200
    t = r.json()
    mnf_names = [p["name"] for p in t["mnf"]]
    assert "PART3_INS1" in mnf_names
    part3 = next(p for p in t["mnf"] if p["name"] == "PART3_INS1")
    assert part3["num_nodes"] == 16283
    assert part3["num_triangles"] == 27290
    assert "position" in part3["node_variables"]
    assert "Mises Stress" in part3["node_variables"]


def test_rigid_transforms(client):
    r = client.get("/api/results/frame/0/rigid_transforms")
    assert r.status_code == 200
    data = r.json()
    assert len(data["items"]) == len(result_manager.topo.rigid_parts)
    for entry in data["items"]:
        assert len(entry["position"]) == 3
        assert len(entry["phi"]) == 3


def test_mnf_frame_position_only(client):
    r = client.get("/api/results/frame/0/part/PART3_INS1?fields=position")
    assert r.status_code == 200
    data = r.json()
    assert data["num_nodes"] == 16283
    assert len(data["positions"]) == 16283 * 3
    assert "mises" not in data


def test_mnf_frame_mises(client):
    r = client.get("/api/results/frame/0/part/PART3_INS1?fields=position,mises")
    assert r.status_code == 200
    data = r.json()
    assert len(data["mises"]) == 16283
    assert data["mises_min"] >= 0
    assert data["mises_max"] >= data["mises_min"]


def test_mnf_rest_mesh(client):
    r = client.get("/api/results/mesh/PART3_INS1")
    assert r.status_code == 200
    data = r.json()
    assert len(data["positions"]) == 16283 * 3
    assert len(data["indices"]) == 27290 * 3
    assert data["triangle_count"] == 27290


def test_scene_endpoint_uses_results(client):
    r = client.get("/api/geometry/scene")
    assert r.status_code == 200
    data = r.json()
    assert data.get("source") == "results"
    items = data["items"]
    # 70 instances total, minus one RIGID without STL (BC_ADAPTER_INS1) → 69.
    assert len(items) == 69
    # BC_ADAPTER_INS1 (no graphics) must NOT be rendered to avoid z-clipping.
    assert not any(i["keyname"] == "BC_ADAPTER_INS1" for i in items)
    mnf_items = [i for i in items if i["category"] == "MNF_PART"]
    rigid_items = [i for i in items if i["category"] == "RIGID_PART"]
    assert len(mnf_items) == 17
    assert len(rigid_items) == 52
    assert any(i["keyname"] == "PART3_INS1" for i in mnf_items)
    part3 = next(i for i in mnf_items if i["keyname"] == "PART3_INS1")
    assert part3["mesh"] is not None
    assert len(part3["mesh"]["positions"]) == 16283 * 3
    # Every rendered rigid part must have a real mesh (no box fallbacks).
    for ri in rigid_items:
        assert ri["mesh"] is not None, f"rigid {ri['keyname']} missing mesh"


def test_mnf_frame_motion_between_frames(client):
    r0 = client.get("/api/results/frame/0/part/PART3_INS1?fields=position").json()
    r250 = client.get("/api/results/frame/250/part/PART3_INS1?fields=position").json()
    p0 = np.array(r0["positions"])
    p250 = np.array(r250["positions"])
    assert not np.allclose(p0, p250, atol=1e-6)
