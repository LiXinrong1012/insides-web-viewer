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

export interface TreeNode {
  id: number;
  keyname: string;
  category: string;
  active: boolean;
  visible: boolean;
  collapsed: boolean;
  children: TreeNode[];
}
