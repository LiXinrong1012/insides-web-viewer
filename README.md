# INSIDES Web Viewer

A Python + React web application for multi-body dynamics simulation pre-processing and result visualization. This is a modern rewrite of the legacy TDYPre desktop application (C++/Qt4).

![Python](https://img.shields.io/badge/Python-3.11-blue)
![React](https://img.shields.io/badge/React-18-61dafb)
![Three.js](https://img.shields.io/badge/Three.js-0.183-black)
![FastAPI](https://img.shields.io/badge/FastAPI-0.135-009688)
![Tests](https://img.shields.io/badge/Tests-33%20passed-brightgreen)

## Features

- **TDY Model Parser** — Recursive descent parser for INSIDES TDY simulation input files (73+ keywords)
- **Expression Evaluator** — Mathematical expressions with variables, functions (SIN, COS, SQRT, STEP...), and recursive parameter resolution
- **3D Viewer** — Three.js scene with orbit controls, picking, and automatic shape rendering (Sphere, Cylinder, Box) from GRAPHIC definitions
- **Model Tree** — Hierarchical tree view of the simulation model (parts, constraints, loads, markers, instances)
- **TDY Editor** — Code editor with real-time compilation, error markers, and parameter display
- **Solver Integration** — Launch and monitor `thudynamics.exe` with WebSocket progress streaming
- **Time Curves** — SVG-based time-domain result plotting
- **Data Table** — Frame-synchronized result data with animation playback
- **Dark/Light Theme** — Full dark and light mode support

## Screenshot

After loading the `double_pendulum` test model:
- Left: Model tree showing 3 rigid parts (SLIDER, LINK1, LINK2), joints, loads, markers
- Center: 3D view with red sphere (slider), blue cylinder (link1), green cylinder (link2)
- Right: TDY editor, time curves, solver panel, data table

## Quick Start

### Prerequisites

- **Python 3.11+** (via [Anaconda](https://www.anaconda.com/) or [Miniconda](https://docs.conda.io/en/latest/miniconda.html))
- **Node.js 18+** (via [nodejs.org](https://nodejs.org/) or `winget install OpenJS.NodeJS.LTS`)

### Setup

```bash
# Clone
git clone https://github.com/LiXinrong1012/insides-web-viewer.git
cd insides-web-viewer

# Create Python environment
conda create -n insides_web python=3.11 -y
conda activate insides_web
pip install fastapi uvicorn[standard] pydantic pydantic-settings python-multipart numpy pytest httpx

# Install frontend dependencies
cd client
npm install
cd ..
```

### Run

```bash
# Terminal 1: Backend
conda activate insides_web
python -m uvicorn server.main:app --reload --port 8000

# Terminal 2: Frontend
cd client
npm run dev
```

Open **http://localhost:5173** in your browser.

### Test

```bash
conda activate insides_web
python -m pytest tests/ -v
```

## Architecture

```
insides-web-viewer/
├── server/                     # FastAPI Backend (Python)
│   ├── main.py                 # Application entry point
│   ├── config.py               # Settings (solver path, MKL path, CORS)
│   ├── models/                 # Data models
│   │   ├── base_item.py        # BaseItem/Assembly tree (Pydantic)
│   │   └── model_document.py   # Document manager + Undo/Redo
│   ├── parsers/                # TDY file processing
│   │   ├── tdy_parser.py       # Recursive descent parser
│   │   ├── tdy_ast.py          # AST node types
│   │   ├── expression_parser.py# Math expression evaluator
│   │   └── model_builder.py    # AST → model tree (73 keyword handlers)
│   ├── visualization/          # 3D geometry processing
│   │   └── mesh_processor.py   # STL parser, FEM mesh, primitive shapes
│   ├── results/                # Simulation results
│   │   └── tdy_results.py      # Result reader (CSV, binary, sample)
│   ├── solver/                 # Solver integration
│   │   └── solver_manager.py   # Process management + output parsing
│   └── api/                    # REST + WebSocket endpoints
│       ├── routes_model.py     # Model CRUD
│       ├── routes_editor.py    # Compile + completions
│       ├── routes_geometry.py  # 3D scene data
│       ├── routes_results.py   # Time series + frame data
│       └── routes_solver.py    # Solver control + WebSocket
├── client/                     # React Frontend (TypeScript)
│   └── src/
│       ├── App.tsx             # Mosaic panel layout (7 panels)
│       ├── store.ts            # Zustand state (model, view, theme)
│       └── components/
│           ├── shell/          # RibbonBar (toolbar + theme toggle)
│           ├── tree/           # ModelTree + PropertyPanel
│           ├── viewer3d/       # Three.js SceneView
│           ├── editor/         # TDYEditor (code + compile)
│           ├── curves/         # TimeCurveView (SVG plots)
│           ├── tables/         # DataTableView (frame sync)
│           └── solver/         # SolverPanel (start/stop/logs)
└── tests/                      # pytest (33 tests)
```

## Tech Stack

| Layer | Technology |
|-------|-----------|
| Backend | FastAPI + Pydantic v2 + NumPy |
| Frontend | React 18 + TypeScript + Vite |
| 3D | Three.js (npm) |
| Layout | react-mosaic |
| State | Zustand |
| Solver IPC | subprocess + asyncio + WebSocket |

## API Endpoints

| Method | Path | Description |
|--------|------|-------------|
| GET | `/api/health` | Health check |
| POST | `/api/model/open` | Upload and parse TDY file |
| GET | `/api/model/tree` | Get model tree |
| GET | `/api/model/item/{id}` | Get item properties |
| POST | `/api/editor/compile` | Compile TDY text |
| GET | `/api/editor/completions` | Keyword completions |
| GET | `/api/geometry/scene` | Get 3D scene objects |
| GET | `/api/results/items` | List result items |
| GET | `/api/results/timeseries/{id}` | Get time series |
| POST | `/api/solver/start` | Start solver |
| WS | `/api/solver/ws` | Solver progress stream |

Full interactive API docs at **http://localhost:8000/docs** (Swagger UI).

## TDY File Format

INSIDES uses a hierarchical keyword-based input format:

```
PARAMETER / 1
, L = 1.0
, N = 20

RIGIDPART / Body1 {
    RIGID6 / 1, MASS = 10, QG = 0, 0, 0
    MARKER / 1, MK_A, QG = 0, 0, 0
    GRAPHIC / 1, SPHERE, RADIUS = 0.05, RGB = 255, 50, 50
}

INSTANCE / 1, INS_Body1, PART = Body1, CENTER = 0, 0, 0
JOINT / 1, FIXED, I = INS_Body1.MK_A, J = MK_GND
END
```

## License

This project is part of the INSIDES multi-body dynamics simulation framework.
