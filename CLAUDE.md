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
  - `server/visualization/mesh_processor.py` - STL 解析、基本体生成
  - `server/visualization/mnf_parser.py` - MNF XML + 二进制模态数据解析
  - `server/visualization/contour.py` - Jet 色谱映射
  - `server/api/routes_geometry.py` - 场景 API (层级变换组合)
  - `server/parsers/model_builder.py` - TDY AST → 模型树 (73+ 关键字)
- `client/` - React + TypeScript + Vite 前端 (Three.js, Zustand, react-mosaic)
  - `client/src/components/viewer3d/SceneView.tsx` - Three.js 3D 渲染
  - `client/src/components/viewer3d/ContourLegend.tsx` - 云图色标条
- `tests/` - pytest 测试套件 (44 tests)
- `ref_code/` - C++/Qt4 原始参考代码（TDYPre）
- `ref_code_freecad/` - FreeCAD 后处理参考代码

## 关键技术细节

### 变换系统
- INSTANCE.PHI 是 Rodriguez 旋转向量: ||PHI|| = 角度(弧度), PHI/||PHI|| = 旋转轴
- 子装配体内零件使用局部坐标，需与父装配体变换组合
- 前端用 Three.js Quaternion 应用旋转

### 渲染架构
- Instance-driven: 每个 INSTANCE 生成独立渲染项（支持多实例化）
- STL 网格: 二进制/ASCII 解析 → BufferGeometry
- MNF 柔性体: XML 节点/面片 + 二进制模态振型 → 网格 + 云图

## 测试

```bash
conda activate insides_web
pytest  # 44 passed
```

## 编码规范

- Python: ruff (line-length=88, target=py311)
- Commit: conventional commits 风格
- 后端运行前设置 `PYTHONIOENCODING=utf-8`
