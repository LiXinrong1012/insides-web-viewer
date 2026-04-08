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

## Phase 7: STL 刚体 + MNF 柔性体网格可视化 ✅ (已完成)

**日期**: 2026-03-25

**完成内容**:

### 7.1 STL 刚体网格渲染
- 解析器修复: 从 key-value 对 (`STL = path`) 检测 STL 形状类型
- 后端: STL 文件从磁盘加载,解析为 positions/normals/indices 缓冲数据
- 后端: mesh 数据内联在 `/api/geometry/scene` 响应中返回
- 前端: `THREE.BufferGeometry` 从缓冲数据创建, 双面 MeshPhongMaterial
- 前端: 自动适配相机到场景包围盒

### 7.2 MNF 柔性体网格渲染
- 新建 `server/visualization/mnf_parser.py`: 解析 MNF XML + 二进制文件
  - 节点坐标 (从 `<NODE>` 元素)
  - 表面三角面片 (从 `<FACE>` 元素, 支持三角形和四边形拆分)
  - 模态振型 (从 `.dat` 二进制文件, 6 DOF/节点: dx,dy,dz,ax,ay,az)
- MNF 网格转 Three.js BufferGeometry (含法向量计算)
- FEM_PART 项自动加载关联的 MNF 网格

### 7.3 应力/位移云图可视化
- 新建 `server/visualization/contour.py`: Jet 色谱映射
- `GET /api/geometry/contour/{id}?mode=7&component=magnitude` 返回逐顶点 RGB
- `GET /api/geometry/modes/{id}` 列出可用模态
- 支持分量: magnitude, dx, dy, dz, ax, ay, az
- 前端: Contour/Clear 按钮, 顶点着色, ContourLegend 色标条

### 7.4 实例位置与姿态变换 (核心修复)
- **Rodriguez 旋转向量**: PHI = [px, py, pz], ||PHI|| = 旋转角, PHI/||PHI|| = 旋转轴
- 后端: 传递 INSTANCE.PHI 旋转向量到前端
- 前端: `phiToQuaternion()` 将 Rodriguez 向量转为 Three.js 四元数
- **层级装配体变换组合**: 子装配体内零件的 CENTER/PHI 是局部坐标
  - `world_pos = asm_R * local_pos + asm_center`
  - `world_R = asm_R * local_R`
- **Instance-driven 渲染**: 每个 INSTANCE 生成独立渲染项
  - 同一零件多次实例化正确显示 (如螺栓 x24, 电机 x6)
  - 总渲染项: 57 → 270

**验证**: 实际 TDY 模型 (55 STL 刚体 + 2 MNF 柔性体, 5 个子装配体) 正确显示

**关键文件**:
- `server/visualization/mnf_parser.py` — MNF XML 解析器
- `server/visualization/contour.py` — Jet 色谱映射
- `server/api/routes_geometry.py` — 场景 API (层级变换组合, instance-driven)
- `client/src/components/viewer3d/SceneView.tsx` — Three.js 渲染 (BufferGeometry + 四元数旋转)
- `client/src/components/viewer3d/ContourLegend.tsx` — 色标条

**测试**: 44 tests passed (新增 11 个: STL 2, MNF 5, Contour 4)

---

## 环境配置 (已更新)

### Conda 环境
```
环境名: insides_web
Python: 3.11
Node.js: v25.7.0 (通过 conda install nodejs)
路径: D:\Users\xrli0\anaconda3\envs\insides_web
```

### 启动命令
```bash
# 后端
cd D:\research\insides-web-viewer
conda activate insides_web
set PYTHONIOENCODING=utf-8
python -m uvicorn server.main:app --reload --port 8000

# 前端
cd D:\research\insides-web-viewer\client
npm run dev
```

### 测试
```bash
conda activate insides_web
pytest tests/ -v   # 44 passed
```

---

## 代码统计 (已更新)

| 类别 | 文件数 | 行数 |
|------|--------|------|
| Python 后端 | ~23 | ~3200 |
| TypeScript 前端 | ~16 | ~1700 |
| 测试 | 6 | ~550 |
| **合计** | **~45** | **~5450** |

---

## 待办 (后续阶段)

- [ ] Phase 9: Undo/Redo 完善
- [ ] Phase 9: 多文档支持
- [ ] Phase 9: 设置持久化 (localStorage)
- [ ] Phase 9: 部署打包 (production build)
- [ ] Phase 9: 相机预设 (iso / top / front / side)
- [x] ~~Phase 8: 真实 .res 二进制结果读取~~ (2026-04-07)
- [x] ~~Phase 8: 时变位移 + 应力云图动画播放~~ (2026-04-07)
- [x] ~~Phase 8: UX 重构 (左 tabs + 右 3D, 多 MNF stress, Space 隐藏)~~ (2026-04-07)
- [x] ~~Phase 8: 一次性 loadcase 加载 (TDY + tree + results)~~ (2026-04-08)
- [x] ~~FEM 网格可视化~~ (Phase 7)
- [x] ~~结果云图~~ (Phase 7)
- [ ] XY 参数图
- [ ] 结果后处理: 应力/应变/位移时间历程曲线

---

## Phase 8: 真实结果动画 + UX 大改造 ✅ (2026-04-07 / 04-08)

**起因**：用户拿 `E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined` 真实样例
（500 帧钻头仿真，17 MNF 柔性体 + 53 刚体 + 64 颗螺钉）跑起来，发现 Phase 7
的"结果读取"只是 `TODO` 占位，MVP 的 UX 也不适合实际使用。本阶段把
"打开 loadcase → 播放动画"链路做成真正可用。**下次 agent 必读本节**。

### 1. INSIDES 结果文件格式 (必读)

C++ 参考实现在 `viewer/ref_code/importtdyresult/TDYResults.cpp:71-136` 和
`importtdybase/basetdyresult.cpp:195-329`。

```
<loadcase>/
├── main.tdy                    ← TDY 源码 (~100 KB, parser 输入)
├── m_*.stl                     ← 每 instance 一份 STL, 局部坐标
├── modal/<Part>/modes_set/     ← MNF XML + 二进制模态振型 (Phase 7 用)
└── result/
    ├── overview.xml            ← 每帧 {id, time, startpos, length, resfile}
    ├── topo_0.xml              ← 拓扑 + 每帧二进制布局 (~40 MB)
    └── result_{1,135,269,403}.res   ← 原始 float64 数据，~2 GB 每段
```

**二进制布局**（所有浮点 **float64 little-endian**）：
- `overview.xml` 给出 frame → (`resfile`, `startpos`, `length`) 切片
- `topo_0.xml` 里每个 `<RIGIDPART>` / `<MNFPART>` 有 `<PartVariables>` 和
  `<NodeVariables>`，每个 `<PartVariable name="..." offset="..." size="..."
  NumberOfComponents="..."/>` 声明 frame-local 字节偏移
- `RIGIDPART` 常见变量：`position(3), phi(3), velocity(3), omega(3)` —
  phi 是 Rodriguez 旋转向量 (`||phi|| = angle`, `phi/||phi|| = axis`)
- `MNFPART` 常见 `NodeVariables`：
  - `position` (3 × N × 8) — **世界坐标**的节点位置
  - `Up_Local` (3 × N × 8) — 局部位移
  - `Mises Stress` (1 × N × 8) — **节点 von Mises 应力**
- `MNFPart.rest_nodes` 在 topo 的 `<NODE>` 段，也是世界坐标

验证：`PART3_INS1` 16283 nodes × 3 × 8 = 390792 → 正好 `NodeVariable.size`。

样例规模：502 帧、70 instance (53 rigid + 17 mnf)、9 秒物理时间。

### 2. 后端实现 (`server/results/`)

| 文件 | 职责 | 核心函数 |
|---|---|---|
| `overview_parser.py` | 解析 `overview.xml` | `parse_overview() → List[FrameMeta]` |
| `topo_parser.py` | `ET.iterparse` 流式解析 `topo_0.xml` | `parse_topo() → Topo{rigid_parts, mnf_parts}` |
| `res_reader.py` | `np.memmap` + 按 `(startpos+offset, size)` 切片 | `ResReader.read_mnf_node_variable(frame, part, name)` |
| `result_manager.py` | Singleton：topo + frames + reader + scene builder | `open() / get_all_mnf_positions_bin() / build_scene_items() / get_rigid_transforms()` |

- `np.memmap` 一个文件一份，零内存占用（四个 `.res` ≈ 8 GB）
- `build_scene_items()` 直接从 topo 构建场景（不依赖 main.tdy 的 doc），
  对无 STL 的 rigid 直接 skip emit（避免 `BC_ADAPTER_INS1` 的 box fallback
  穿插到电池盖板里）
- 按 part family (`PART3_INS1..PART3_INS6 → PART3`) 哈希到 HSL pastel 色，
  同族同色

### 3. 性能关键：二进制帧端点

**原本的坑**：`get_all_mnf_positions()` 返回 JSON，每帧 17 MB，
`numpy.tolist()` + `json.dumps` **1.8 秒 / 帧** → 播放 0.55 fps。

**修复**：新增 `GET /api/results/frame/{i}/all_mnf_positions.bin`，直接
`np.tobytes()` 拼自定义 little-endian blob：

```
uint32  magic = 0x4D4E4650 ("MNFP")
uint32  part_count
每 part:
  uint16  name_len
  bytes   name (utf-8)
  uint32  num_nodes
  float32 positions[num_nodes * 3]
```

前端 `fetchAllMnfPositionsBin()` 用 `ArrayBuffer` **零拷贝**解析成
`Map<partName, Float32Array>`，直接 `posAttr.array.set(...)` 写 GPU。

**结果**：1820 ms → **22–49 ms / 帧** (~70× 加速)，payload 17 MB → 3.2 MB。

### 4. 前端播放架构 (踩坑史)

**坑 A: 刚体不动**
- 根因：`loadScene` 和 `updateFrame` 两个 effect 在 `animLoaded` flip 时并发。
  loadScene 先清 map → 等 HTTP → populate。updateFrame 拿到 rigid transforms
  时 map 仍空，全部 `.get()` 返回 `undefined`，**第一次更新完全丢失**。
- 修复：
  - `loadScene` 用 promise 链序列化 (`loadingPromiseRef`)
  - `sceneVersionRef` 哨兵：fetch 返回后若场景已被重建则丢弃结果
  - `loadScene` 完成后主动 `requestRender(currentFrame)` 刷一次
  - 删掉 `handleOpenLoadcase` 里的显式 `loadScene`（只走 effect 一条路径）

**坑 B: "只看到几帧"跳帧**
- 根因：播放循环原来在 `TimelinePanel`，用 rAF 驱动 `setFrame(next)`。
  SceneView `updateFrame` 有 `fetchingRef` 守门，fetch 在飞就立即 return 并
  记 `pendingKey`。rAF 一直以 wallclock 速度打卡 → 很多 setFrame 都被压成
  pendingKey → finally 段检测到 pendingKey != key → 直接**跳到最新帧**，
  中间全部 skip。
- 修复：把播放循环**搬到 SceneView**，每帧 `await performUpdate` 再 advance。
  scrubbing（非播放）路径仍保留 coalesce-to-latest。

```ts
// 正确的播放循环 (SceneView.tsx, 别再改回 rAF)
useEffect(() => {
  if (!animLoaded || !isPlaying) return;
  let cancelled = false;
  const run = async () => {
    while (!cancelled) {
      const state = useAnimationStore.getState();
      if (!state.isPlaying) return;
      const frame = state.currentFrame;
      await performUpdate(frame);          // ← 等这一帧真正刷到 GPU
      if (cancelled) return;
      const waitMs = Math.max(0, 1000 / state.playbackFps - 2);
      if (waitMs > 0) await new Promise(r => setTimeout(r, waitMs));
      if (cancelled) return;
      if (frame >= state.frameCount - 1) {
        state.setPlaying(false); state.setFrame(0); return;
      }
      state.setFrame(frame + 1);
    }
  };
  run();
  return () => { cancelled = true; };
}, [animLoaded, isPlaying, playbackFps, performUpdate]);
```

**坑 C: 光照"绑"在模型坐标系上**
- 根因：`updateFrame` 只写 `BufferAttribute.position`，**不更新**
  `BufferAttribute.normal`。法线停留在 rest-pose 朝向 → 模型绕 Z 轴旋转时
  shader 用过期法线算光照 → 明暗面跟着模型转。
- 修复：**MNF 材质 `flatShading: true`**。fragment shader 用 `dFdx`/`dFdy`
  屏幕空间导数派生法线，永远正确。**零开销**。
- 为啥不回传法线？试过服务端 `_compute_vertex_normals_fast` + `np.bincount`，
  packet 加倍到 6.5 MB，服务端算法线 ~100 ms/frame → 总延迟 150 ms → 帧率
  减半。flatShading 完胜。
- **刚体 STL 保持 `flatShading: false`** —— 它们用 `mesh.quaternion` 转，
  normalMatrix 会自动跟进，smooth 着色更好看。

**坑 D: Colormap 在深色背景下发黑**
- 原 jet 最低端纯深蓝 `#000080`，和 `#1a1a2e` 背景几乎重叠
- 换成 **viridis**（matplotlib 默认），紫 → 青 → 黄，全程亮度 > 0.27，
  感知均匀、色盲友好。11 个 LUT 采样在 `SceneView.viridis()` 里线性插值

**坑 E: 首次帧延迟 (客户端缓存)**
- `mnfCacheRef: Map<frame, Map<partName, Float32Array>>` LRU，容量 200 帧
- `rigidCacheRef`: 容量 600 帧
- `inflightMnfRef` / `inflightRigidRef` 防重复 fetch
- 每帧渲染完 `prefetchAhead(frame, 6)` 启动未来 6 帧的后台 fetch
- 第一遍播放冷启 ~25 ms/帧，第二遍起 100% 命中

### 5. UX 大重构

- **布局**：移除 `react-mosaic-component`。固定两栏 + 可拖拽分隔条：
  左 ~28% `LeftSidebar`（Model / TDY / Solver / Curves / Table 5 个 tab），
  右 ~72% 常驻 `SceneView`
- **ModelTree**：`useEffect(() => { if (tree) return; fetchModelTree().then(setTree) }, [tree, setTree])` —
  **只在 tree 为空时 fetch 一次**，避免 tab 切换 re-mount 触发
  `setTree()` 新对象引用 → loadScene → 场景闪烁
- **visibility store**：`useVisibilityStore`，按 `keyname.toUpperCase()` 作
  hidden key。results 模式下 scene id 和 tree id 是两套空间，keyname 是
  唯一交集。SceneView 全局 `keydown` 监听 Space → 读
  `useModelStore.selectedKeyname` → toggle
- **多 MNF 应力**：`activeMnfPart: string | null` → `activeMnfParts: string[]`，
  TimelinePanel chip 列表 + `+ Add part…` 下拉。SceneView 用所有 active
  parts 的**统一全局 min/max** 上色
- **空白点击清选**：SceneView click raycast miss → `selectItem(null, null)`
- **Play/Pause 按钮**：绿 `PLAY` / 红 `PAUSE` 大按钮，避免和 `▶` Next 撞脸
- **五盏灯光 rig**：AmbientLight(0.55) + HemisphereLight(0.55) + Key + Fill +
  Rim，背面不再全黑

### 6. 一次性 loadcase 加载 (2026-04-08)

替换 `POST /api/results/open`（只开 result 目录）为
`POST /api/results/open_loadcase`（入参 `{ loadcase_dir }`）：

1. 定位 `<loadcase>/main.tdy`（fallback 到任意 `*.tdy`）
2. 读文本 + `TDYParser` + `ModelBuilder` → 填 `get_document().assembly`
3. 若 `<loadcase>/result/overview.xml` 存在，调 `result_manager.open()`
4. 一次返回 `{ tdy_path, tdy_text, tree, parser_errors, result }`

前端 `handleOpenLoadcase`：
- `tree` → `useModelStore.setTree`（ModelTree 自动渲染 612 节点）
- `tdy_text` → `useModelStore.setTdySource(text, path)` → 触发
  `TDYEditor useEffect` 同步到 textarea
- `result` → `useAnimationStore.setLoaded({...})` → 触发动画

### 7. 受影响文件总览

**新增 (15)**：
- 后端：`server/results/{overview_parser,topo_parser,res_reader,result_manager}.py`
- 后端：`server/visualization/mnf_rest_mesh.py`
- 前端：`client/src/components/shell/LeftSidebar.tsx`
- 前端：`client/src/components/viewer3d/TimelinePanel.tsx`
- 前端：`client/playwright.config.ts` + `client/tests/e2e/animation.spec.ts`
- 测试：`tests/test_{overview_parser,topo_parser,res_reader,result_manager_api}.py`

**删除**：`server/results/tdy_results.py` (被 `result_manager.py` 取代)

**大改**：
- `server/api/routes_results.py` — 新的 `/open_loadcase /status /topo /frames
  /frame/{i}/rigid_transforms /frame/{i}/part/{name} /frame/{i}/all_mnf_positions.bin /mesh/{name}`
- `server/api/routes_geometry.py` — `/scene` 结果模式分支
- `client/src/App.tsx` — 两栏布局
- `client/src/store.ts` — useLayoutStore / useVisibilityStore / useAnimationStore
  多部件 + `tdySource` / `tdySourceVersion`
- `client/src/components/viewer3d/SceneView.tsx` — 播放循环 + 缓存 +
  prefetch + Space + multi-stress + viridis + flatShading
- `client/src/components/tree/ModelTree.tsx` — visibility + 单次 fetch
- `client/src/components/editor/TDYEditor.tsx` — 订阅 `tdySource`
- `client/src/services/api.ts` — 新 API + 二进制 parser

### 8. 测试状态

- **pytest**: `63 passed, 7 skipped`（新增 25 个 result 相关测试）
- **tsc + vite build**: 无错误，gzip bundle ~191 KB
- **Playwright e2e** (`animation.spec.ts`)：遍历 11 帧截图 + 数值断言
  螺钉 INS1 从 frame 0 到 250 位移 > 0.01 m，实测 **0.095 m** ✓

### 9. 启动命令 (copy-paste 即可)

```bash
# 后端（一个窗口）
cd D:/__insides_dev/viewer/insides_web
PYTHONIOENCODING=utf-8 /c/Users/XinrongLI/.conda/envs/insides_web/python.exe \
    -m uvicorn server.main:app --port 8000 --host 127.0.0.1

# 前端（另一个窗口）
cd D:/__insides_dev/viewer/insides_web/client
npm run dev -- --port 5173 --host 127.0.0.1
```

浏览器 → http://127.0.0.1:5173 → 右上 **`Load Loadcase`** → 输入
`E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined` → 回车。

立即看到：左侧 Model 树 612 节点、TDY 标签页 98 KB 源码、3D 视图多彩钻头、
底部 TimelinePanel 502 帧滑块。点 PLAY 流畅播放。

### 10. 下次 agent 必看清单

1. **数据 pipeline 唯一真相源**：`topo_0.xml` 的 `<PartVariables>` /
   `<NodeVariables>` 声明每帧字节布局。**永远**从 `topo_parser.py` 读，
   不要自己猜偏移。
2. **`.res` 全是 float64**，写 GPU 时 `astype(np.float32)`。
3. **MNF `rest_nodes` 和 `position` 都是世界坐标**；刚体 STL 是局部坐标。
4. **BC_ADAPTER_INS1 没 STL**（`NumberOfGraphics="0"`），build_scene_items
   显式 skip。不要再加"fallback box"。
5. **MNF 部件必须 `flatShading: true`**，否则光照跟着模型转。
6. **播放循环在 SceneView**，不在 TimelinePanel。**必须**
   `await performUpdate` 再 advance。不要回退到 rAF + `setFrame(next)`，
   那会复活跳帧 bug。
7. **帧缓存 + prefetch-ahead** 是流畅播放的关键。
8. **Space 键**被 SceneView 的全局 keydown handler 拦截做隐藏/恢复。想加
   "空格播放"快捷键记得避开这个冲突。
9. **TDYEditor 用 `tdySourceVersion`** 触发同步，不直接 watch `tdySource`，
   因为用户在 textarea 输入会产生新 text，不能再被 store 回写覆盖。
10. **ModelTree 单次 fetch 守护**：`if (tree) return;` —— 不要删，否则
    tab 切换会触发场景闪烁。
11. **后端重启方式**（没有 `--reload`）：
    ```bash
    netstat -ano | grep ":8000.*LISTENING" | awk '{print $5}' | xargs -I{} taskkill //F //PID {}
    sleep 1
    # 然后重新启动（见 9）
    ```
12. **Window debug handles**（在浏览器 console 里）：
    - `__animStore.getState()` — 动画状态
    - `__visStore.getState()` — 隐藏零件
    - `__modelStore.getState()` — tree / selection
    - `__rigidMeshes.current.get("HEXAGON_...")` — 某刚体的 THREE.Mesh
    - `__mnfMeshes.current.get("PART3_INS1")`
    - `__sceneRef.current.{scene,camera,controls}`
    - `__openLoadcase(dir)` — 编程式触发 Load
