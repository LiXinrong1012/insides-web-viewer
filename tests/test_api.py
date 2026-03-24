"""API integration tests."""

import pytest
from httpx import AsyncClient, ASGITransport

from server.main import app


@pytest.fixture
def anyio_backend():
    return "asyncio"


@pytest.mark.anyio
async def test_health():
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://test") as ac:
        resp = await ac.get("/api/health")
    assert resp.status_code == 200
    data = resp.json()
    assert data["status"] == "ok"


@pytest.mark.anyio
async def test_model_tree():
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://test") as ac:
        resp = await ac.get("/api/model/tree")
    assert resp.status_code == 200
    tree = resp.json()
    assert tree["keyname"] == "Model"
    assert tree["category"] == "ASSEMBLY"
    assert len(tree["children"]) == 11


@pytest.mark.anyio
async def test_upload_and_get_item():
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://test") as ac:
        # Upload a dummy TDY file
        resp = await ac.post(
            "/api/model/open",
            files={"file": ("test.tdy", b"ASSEMBLY test_model\nEND", "text/plain")},
        )
        assert resp.status_code == 200
        data = resp.json()
        assert data["filename"] == "test.tdy"
        tree = data["tree"]

        # Get root item
        resp2 = await ac.get(f"/api/model/item/{tree['id']}")
        assert resp2.status_code == 200

        # Get non-existent item
        resp3 = await ac.get("/api/model/item/999999")
        assert resp3.status_code == 404
