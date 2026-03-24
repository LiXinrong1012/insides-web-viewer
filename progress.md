# INSIDES Web Viewer — 开发进展记录

## 项目概述

将 TDYPre 桌面应用 (C++/Qt4/VS2010) 改写为 Python + Web 技术栈。

| 属性 | 值 |
|------|-----|
| 仓库路径 | `D:\__insides_dev\viewer\insides_web\` |
| 后端 | FastAPI + Python 3.11 (conda env: `insides_web`) |
| 前端 | React 18 + TypeScript + Vite |
| 3D | Three.js (npm 本地包) |
| 测试 | pytest (33 tests, 全部通过) |

---

## Phase 0: 基础搭建 ✅ (已完成)

**日期**: 2026-03-24

**完成内容**:
- FastAPI 应用骨架 (`server/main.py`)
- Pydantic 数据模型: `BaseItem`, `Assembly`, `ModelDocument` (含 Undo/Redo)
- REST API: `/api/health`, `/api/model/open`, `/api/model/tree`, `/api/model/item/{id}`
- React + Vite 前端脚手架
- react-mosaic 可拖拽面板布局 (7 个面板)
- Zustand 状态管理
- 9 个测试通过 (模型单元测试 + API 集成测试)

**关键文件**:
- `server/models/base_item.py` — 核心数据模型
- `server/models/model_document.py` — 文档管理
- `server/api/routes_model.py` — 模型 CRUD API
- `client/src/App.tsx` — 主布局

---

## Phase 1: TDY 解析 + 模型树 ✅ (已完成)

**日期**: 2026-03-24

**完成内容**:
- TDY 递归下降解析器 (移植自 C++ `edcompile/modelparser.cpp`)
  - 字符级状态机: 关键字、属性、键值对、嵌套块、注释、引号
  - INCLUDE 文件展开
  - ID/Label 自动提取
- 数学表达式求值器 (移植自 `preparameter/expressionparser.h`)
  - 运算符优先级: `+`, `-`, `*`, `/`, `^`, 括号
  - 内置函数: SIN, COS, SQRT, ABS, STEP 等
  - 变量引用 + 递归解析
- TDYParameters 参数管理 (惰性求值 + 缓存)
- 模型构建器: AST → BaseItem 树
  - 73+ 关键字注册 (含后续补充的 INTPAR, MOTION, OUTPUT_REQUEST)
  - 处理 RIGIDPART, FEMPART, ASSEMBLY, INSTANCE, MARKER, JOINT, SFORCE, CONTACT 等
- 24 个新测试通过

**关键文件**:
- `server/parsers/tdy_parser.py` — 递归下降解析器
- `server/parsers/tdy_ast.py` — AST 数据结构
- `server/parsers/expression_parser.py` — 表达式求值 + TDYParameters
- `server/parsers/model_builder.py` — AST → 模型树 (关键字处理器)

---

## Phase 2: TDY 编辑器 ✅ (已完成)

**日期**: 2026-03-24

**完成内容**:
- 编译/验证 API 端点 (`POST /api/editor/compile`)
- 关键字自动补全端点 (`GET /api/editor/completions`)
- 前端代码编辑器 (textarea + 行号 + 实时编译)
- 错误面板 (行列定位)
- 参数面板 (显示解析出的参数及其值)

**关键文件**:
- `server/api/routes_editor.py` — 编辑器 API
- `client/src/components/editor/TDYEditor.tsx` — 编辑器组件

---

## Phase 3: 3D 可视化 ✅ (已完成)

**日期**: 2026-03-24

**完成内容**:
- 服务端网格处理: STL 解析 (二进制+ASCII), FEM 网格转换
- 基本体生成: Box, Cylinder, Sphere (用于 GRAPHIC 元素)
- 场景 API (`GET /api/geometry/scene`) — 返回所有可渲染对象
- Three.js 3D 场景 (npm 本地包，非 CDN)
  - OrbitControls (轨道/平移/缩放)
  - 光照: 环境光 + 两个方向光
  - 网格 + 坐标轴辅助
  - 光线投射拾取 (点击选择)
  - 自适应窗口大小
- GRAPHIC 形状类型识别 (SPHERE/CYLINDER/BOX)
- RGB 颜色传递
- INSTANCE CENTER 位置解析

**关键文件**:
- `server/visualization/mesh_processor.py` — 网格处理
- `server/api/routes_geometry.py` — 几何 API (含场景收集)
- `client/src/components/viewer3d/SceneView.tsx` — Three.js 渲染器

---

## Phase 4: 求解器集成 ✅ (已完成)

**日期**: 2026-03-24

**完成内容**:
- SolverManager: subprocess 管理 thudynamics.exe
- 进程输出解析 (时间步进、CPU 时间)
- WebSocket 进度端点 (`/api/solver/ws`)
- REST 控制 API: start, stop, status, logs
- 前端求解器面板: 启动/停止, 进度条, 日志查看

**关键文件**:
- `server/solver/solver_manager.py` — 求解器进程管理
- `server/api/routes_solver.py` — 求解器 API + WebSocket
- `client/src/components/solver/SolverPanel.tsx` — 控制面板

---

## Phase 5: 结果加载 + 时间曲线 ✅ (已完成)

**日期**: 2026-03-24

**完成内容**:
- TDYResults: 结果数据管理 (帧列表, 惰性加载框架)
- CSV 结果导入
- 示例数据生成 (用于测试)
- REST API: items 列表, timeseries, frame 数据
- SVG 内联绘图 (替代 CDN Plotly，消除网络依赖)
- 结果选择器面板

**关键文件**:
- `server/results/tdy_results.py` — 结果读取器
- `server/api/routes_results.py` — 结果 API
- `client/src/components/curves/TimeCurveView.tsx` — 时间曲线 (SVG)

---

## Phase 6: 数据表格 ✅ (已完成)

**日期**: 2026-03-24

**完成内容**:
- 帧同步数据表格
- 动画播放 (Play/Pause + 帧滑块)
- 排序表头

**关键文件**:
- `client/src/components/tables/DataTableView.tsx` — 数据表格

---

## Bug Fix: Three.js + 暗色主题 + 模型显示 ✅ (已完成)

**日期**: 2026-03-24

**问题**:
1. Three.js CDN 加载失败 (网络不通)
2. react-mosaic 默认白色背景覆盖了暗色样式
3. double_pendulum 模型的 INTPAR/MOTION/OUTPUT_REQUEST 关键字未注册
4. GRAPHIC 形状类型 (SPHERE/CYLINDER) 未从 main_label 识别

**修复**:
1. Three.js 改为 npm 本地安装 (`npm install three @types/three`)
2. 全面 CSS 变量化: `var(--bg-primary)`, `var(--text-primary)` 等
3. react-mosaic 所有层级添加 `!important` 暗色覆盖
4. 暗色/明亮双主题切换 (`data-theme="dark"/"light"`)
5. 注册 INTPAR, MOTION, OUTPUT_REQUEST 关键字
6. 在 `_process_part_child` 和 `_handle_graphic` 中从 `main_label` 检测形状类型

**验证**: double_pendulum 模型成功解析并 3D 显示 (红球+蓝柱+绿柱)

---

## 环境配置

### Conda 环境
```
环境名: insides_web
Python: 3.11.15
路径: C:\Users\XinrongLI\.conda\envs\insides_web
```

### Node.js
```
Node: v24.14.0
npm: 11.9.0
安装方式: winget install OpenJS.NodeJS.LTS
```

### 启动命令
```bash
# 后端
cd D:\__insides_dev\viewer\insides_web
conda activate insides_web
python -m uvicorn server.main:app --reload --port 8000

# 前端
cd D:\__insides_dev\viewer\insides_web\client
npm run dev
```

### 测试
```bash
cd D:\__insides_dev\viewer\insides_web
conda activate insides_web
python -m pytest tests/ -v   # 33 passed
```

---

## 代码统计

| 类别 | 文件数 | 行数 |
|------|--------|------|
| Python 后端 | ~20 | ~2500 |
| TypeScript 前端 | ~15 | ~1500 |
| 测试 | 3 | ~400 |
| **合计** | **~38** | **~4400** |

---

## 待办 (后续阶段)

- [ ] Phase 7: Undo/Redo 完善
- [ ] Phase 7: 多文档支持
- [ ] Phase 7: 设置持久化 (localStorage)
- [ ] Phase 7: 性能优化 (WebWorkers, 虚拟滚动, LOD)
- [ ] Phase 7: 部署打包 (production build)
- [ ] QDataStream 二进制结果文件读取 (需要实际结果文件测试)
- [ ] FEM 网格可视化 (需要含 FEM 的测试模型)
- [ ] 结果云图 (标量→顶点颜色映射)
- [ ] XY 参数图
- [ ] 动画播放 (3D 帧同步)
