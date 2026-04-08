const API_BASE = "/api";

export async function fetchHealth(): Promise<{ status: string; app: string }> {
  const res = await fetch(`${API_BASE}/health`);
  return res.json();
}

export async function fetchModelTree(): Promise<TreeNode> {
  const res = await fetch(`${API_BASE}/model/tree`);
  return res.json();
}

export async function fetchItem(id: number): Promise<Record<string, unknown>> {
  const res = await fetch(`${API_BASE}/model/item/${id}`);
  return res.json();
}

export async function uploadModel(file: File): Promise<{ filename: string; size: number; tree: TreeNode }> {
  const form = new FormData();
  form.append("file", file);
  const res = await fetch(`${API_BASE}/model/open`, { method: "POST", body: form });
  return res.json();
}

// ---------- Results / animation ----------

export interface ResultOpenResponse {
  result_dir: string;
  frame_count: number;
  time_range: [number, number];
  rigid_parts: number;
  mnf_parts: number;
}

export interface ResultStatus {
  loaded: boolean;
  frame_count?: number;
  time_range?: [number, number];
  rigid_parts?: number;
  mnf_parts?: number;
  result_dir?: string;
}

export async function fetchResultStatus(): Promise<ResultStatus> {
  const res = await fetch(`${API_BASE}/results/status`);
  return res.json();
}

export interface OpenLoadcaseResponse {
  loadcase_dir: string;
  tdy_path: string;
  tdy_filename: string;
  tdy_text: string;
  tree: TreeNode;
  parser_errors: string[];
  result: {
    loaded: boolean;
    frame_count?: number;
    time_range?: [number, number];
    rigid_parts?: number;
    mnf_parts?: number;
    error?: string;
  };
}

export async function openLoadcase(loadcaseDir: string): Promise<OpenLoadcaseResponse> {
  const res = await fetch(`${API_BASE}/results/open_loadcase`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ loadcase_dir: loadcaseDir }),
  });
  if (!res.ok) {
    const body = await res.text();
    throw new Error(`open_loadcase failed: ${res.status} ${body}`);
  }
  return res.json();
}

export async function openResults(resultDir: string): Promise<ResultOpenResponse> {
  const res = await fetch(`${API_BASE}/results/open`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ result_dir: resultDir }),
  });
  if (!res.ok) throw new Error(`open results failed: ${res.status}`);
  return res.json();
}

export async function fetchFrames(): Promise<{ frame_count: number; times: number[] }> {
  const res = await fetch(`${API_BASE}/results/frames`);
  return res.json();
}

export async function fetchTopo(): Promise<{
  rigid: { name: string; variables: string[] }[];
  mnf: {
    name: string;
    num_nodes: number;
    num_triangles: number;
    node_variables: string[];
    part_variables: string[];
  }[];
}> {
  const res = await fetch(`${API_BASE}/results/topo`);
  return res.json();
}

export interface RigidTransformItem {
  name: string;
  position: number[];
  phi: number[];
}

export async function fetchRigidTransforms(frame: number): Promise<{
  frame: number;
  items: RigidTransformItem[];
}> {
  const res = await fetch(`${API_BASE}/results/frame/${frame}/rigid_transforms`);
  return res.json();
}

export interface MnfFrameData {
  frame: number;
  time: number;
  part: string;
  num_nodes: number;
  positions?: number[];
  mises?: number[];
  mises_min?: number;
  mises_max?: number;
}

export interface AllMnfPositions {
  frame: number;
  parts: Record<string, { num_nodes: number; positions: number[] }>;
}

export async function fetchAllMnfPositions(frame: number): Promise<AllMnfPositions> {
  const res = await fetch(`${API_BASE}/results/frame/${frame}/all_mnf_positions`);
  if (!res.ok) throw new Error(`all_mnf fetch failed: ${res.status}`);
  return res.json();
}

export interface MnfFramePart {
  positions: Float32Array;
}

/** Binary-packed per-frame positions.  Normals are computed on the GPU via
 *  `flatShading` so we don't need to ship them.
 * Layout (LE, magic 0x4D4E4650 = "MNFP"):
 *   uint32 magic
 *   uint32 part_count
 *   for each part:
 *     uint16 name_len
 *     bytes  name (utf-8)
 *     uint32 num_nodes
 *     float32 positions[num_nodes * 3]
 */
export async function fetchAllMnfPositionsBin(
  frame: number,
): Promise<Map<string, MnfFramePart>> {
  const res = await fetch(`${API_BASE}/results/frame/${frame}/all_mnf_positions.bin`);
  if (!res.ok) throw new Error(`all_mnf bin fetch failed: ${res.status}`);
  const buf = await res.arrayBuffer();
  const view = new DataView(buf);
  const td = new TextDecoder("utf-8");
  let off = 0;
  const magic = view.getUint32(off, true); off += 4;
  if (magic !== 0x4d4e4650) {
    throw new Error(`bad magic: 0x${magic.toString(16)}`);
  }
  const partCount = view.getUint32(off, true); off += 4;
  const out = new Map<string, MnfFramePart>();
  for (let i = 0; i < partCount; i++) {
    const nameLen = view.getUint16(off, true); off += 2;
    const name = td.decode(new Uint8Array(buf, off, nameLen)); off += nameLen;
    const numNodes = view.getUint32(off, true); off += 4;
    const floats = numNodes * 3;
    let positions: Float32Array;
    if (off % 4 === 0) {
      positions = new Float32Array(buf, off, floats);
    } else {
      positions = new Float32Array(floats);
      const tmp = new DataView(buf, off, floats * 4);
      for (let j = 0; j < floats; j++) positions[j] = tmp.getFloat32(j * 4, true);
    }
    off += floats * 4;
    out.set(name, { positions });
  }
  return out;
}

export async function fetchMnfFrame(
  frame: number,
  partName: string,
  fields: string,
): Promise<MnfFrameData> {
  const res = await fetch(
    `${API_BASE}/results/frame/${frame}/part/${encodeURIComponent(partName)}?fields=${fields}`,
  );
  if (!res.ok) throw new Error(`mnf frame fetch failed: ${res.status}`);
  return res.json();
}

export interface TreeNode {
  id: number;
  keyname: string;
  category: string;
  active: boolean;
  visible: boolean;
  collapsed: boolean;
  children: TreeNode[];
}
