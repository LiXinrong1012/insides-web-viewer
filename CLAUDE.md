# INSIDES Web Viewer

TDYPre 桌面应用（C++/Qt4）的现代 Web 重写版，用于多体动力学仿真前处理和结果可视化。

## 环境配置

### Python 后端

- **Conda 环境**: `insides_web` (Python 3.11)
- **创建环境**: `conda create -n insides_web python=3.11`
- **安装依赖**: `conda activate insides_web && pip install -r requirements.txt`

### 前端

- **Node.js**: 通过 conda 安装 (`conda install -c conda-forge nodejs`)
- **包管理**: npm
- **安装依赖**: `cd client && npm install`

## 启动服务

### 后端 (Terminal 1)

```bash
conda activate insides_web
cd D:\research\insides-web-viewer
set PYTHONIOENCODING=utf-8
python -m uvicorn server.main:app --reload --port 8000
```

### 前端 (Terminal 2)

```bash
cd D:\research\insides-web-viewer\client
npm run dev
```

- 后端: http://localhost:8000
- 前端: http://localhost:5173 (代理 /api → localhost:8000)

## 项目结构

- `server/` - FastAPI 后端 (解析器、模型、3D、求解器、结果、API)
- `client/` - React + TypeScript + Vite 前端 (Three.js, Zustand, react-mosaic)
- `tests/` - pytest 测试套件
- `ref_code/` - C++/Qt4 原始参考代码（TDYPre）

## 测试

```bash
conda activate insides_web
pytest
```

## 编码规范

- Python: ruff (line-length=88, target=py311)
- Commit: conventional commits 风格
- 后端运行前设置 `PYTHONIOENCODING=utf-8`
