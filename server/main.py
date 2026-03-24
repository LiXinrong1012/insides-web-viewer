"""FastAPI application entry point for INSIDES Web Viewer."""

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from fastapi.staticfiles import StaticFiles

from .api.routes_editor import router as editor_router
from .api.routes_geometry import router as geometry_router
from .api.routes_model import router as model_router
from .api.routes_results import router as results_router
from .api.routes_solver import router as solver_router
from .config import settings

app = FastAPI(title=settings.app_name, debug=settings.debug)

# CORS for React dev server
app.add_middleware(
    CORSMiddleware,
    allow_origins=settings.cors_origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# API routes
app.include_router(model_router)
app.include_router(editor_router)
app.include_router(geometry_router)
app.include_router(results_router)
app.include_router(solver_router)


@app.get("/api/health")
async def health():
    return {"status": "ok", "app": settings.app_name}


# Serve React build in production
# app.mount("/", StaticFiles(directory="client/dist", html=True), name="static")
