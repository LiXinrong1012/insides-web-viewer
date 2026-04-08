import { create } from "zustand";
import { type TreeNode } from "./services/api";

// ---------- Model tree / selection ----------

interface ModelState {
  tree: TreeNode | null;
  selectedItemId: number | null;
  selectedKeyname: string | null;   // unifies tree nodes and scene meshes
  filePath: string | null;
  tdySource: string | null;         // raw TDY text shown in the editor
  tdySourceVersion: number;         // bumps so the editor can sync on change
  setTree: (tree: TreeNode) => void;
  selectItem: (id: number | null, keyname?: string | null) => void;
  setFilePath: (path: string | null) => void;
  setTdySource: (text: string | null, path?: string | null) => void;
}

export const useModelStore = create<ModelState>((set, get) => ({
  tree: null,
  selectedItemId: null,
  selectedKeyname: null,
  filePath: null,
  tdySource: null,
  tdySourceVersion: 0,
  setTree: (tree) => set({ tree }),
  selectItem: (id, keyname) => set({ selectedItemId: id, selectedKeyname: keyname ?? null }),
  setFilePath: (path) => set({ filePath: path }),
  setTdySource: (text, path) =>
    set({
      tdySource: text,
      filePath: path ?? get().filePath,
      tdySourceVersion: get().tdySourceVersion + 1,
    }),
}));

// ---------- Layout / sidebar tabs ----------

export type LeftTabId = "tree" | "editor" | "solver" | "curves" | "table";

interface LayoutState {
  leftTab: LeftTabId;
  setLeftTab: (id: LeftTabId) => void;
}

export const useLayoutStore = create<LayoutState>((set) => ({
  leftTab: "tree",
  setLeftTab: (id) => set({ leftTab: id }),
}));

// ---------- Visibility (hide/show 3D parts by keyname) ----------

interface VisibilityState {
  hiddenKeys: Set<string>;
  version: number;                 // bump so subscribers can react
  isHidden: (key: string | null | undefined) => boolean;
  toggle: (key: string | null | undefined) => void;
  show: (key: string) => void;
  hide: (key: string) => void;
  reset: () => void;
}

export const useVisibilityStore = create<VisibilityState>((set, get) => ({
  hiddenKeys: new Set<string>(),
  version: 0,
  isHidden: (key) => !!key && get().hiddenKeys.has(key.toUpperCase()),
  toggle: (key) => {
    if (!key) return;
    const k = key.toUpperCase();
    const next = new Set(get().hiddenKeys);
    if (next.has(k)) next.delete(k);
    else next.add(k);
    set({ hiddenKeys: next, version: get().version + 1 });
  },
  show: (key) => {
    const k = key.toUpperCase();
    const cur = get().hiddenKeys;
    if (!cur.has(k)) return;
    const next = new Set(cur);
    next.delete(k);
    set({ hiddenKeys: next, version: get().version + 1 });
  },
  hide: (key) => {
    const k = key.toUpperCase();
    const cur = get().hiddenKeys;
    if (cur.has(k)) return;
    const next = new Set(cur);
    next.add(k);
    set({ hiddenKeys: next, version: get().version + 1 });
  },
  reset: () => set({ hiddenKeys: new Set(), version: get().version + 1 }),
}));

// ---------- Theme ----------

export type Theme = "dark" | "light";

interface ThemeState {
  theme: Theme;
  toggleTheme: () => void;
}

// ---------- Animation (MNF result playback) ----------

export type ColorField = "none" | "mises";

interface AnimationState {
  loaded: boolean;
  frameCount: number;
  times: number[];
  currentFrame: number;
  isPlaying: boolean;
  playbackFps: number;               // target frames/sec for playback
  colorField: ColorField;
  activeMnfParts: string[];          // ordered, multi-select
  availableMnfParts: string[];
  setLoaded(info: { frameCount: number; times: number[]; mnfParts: string[] }): void;
  setFrame(i: number): void;
  stepFrame(delta: number): void;
  togglePlay(): void;
  setPlaying(p: boolean): void;
  setPlaybackFps(f: number): void;
  setColorField(f: ColorField): void;
  addMnfPart(name: string): void;
  removeMnfPart(name: string): void;
  setActiveMnfParts(names: string[]): void;
  reset(): void;
}

export const useAnimationStore = create<AnimationState>((set, get) => ({
  loaded: false,
  frameCount: 0,
  times: [],
  currentFrame: 0,
  isPlaying: false,
  playbackFps: 30,
  colorField: "none",
  activeMnfParts: [],
  availableMnfParts: [],
  setLoaded: (info) =>
    set({
      loaded: true,
      frameCount: info.frameCount,
      times: info.times,
      currentFrame: 0,
      availableMnfParts: info.mnfParts,
      activeMnfParts: info.mnfParts.slice(0, 1),
    }),
  setFrame: (i) => {
    const n = get().frameCount;
    if (n === 0) return;
    const clamped = Math.max(0, Math.min(n - 1, i));
    set({ currentFrame: clamped });
  },
  stepFrame: (delta) => {
    const { currentFrame } = get();
    get().setFrame(currentFrame + delta);
  },
  togglePlay: () => set((s) => ({ isPlaying: !s.isPlaying })),
  setPlaying: (p) => set({ isPlaying: p }),
  setPlaybackFps: (f) => set({ playbackFps: Math.max(1, Math.min(60, f)) }),
  setColorField: (f) => set({ colorField: f }),
  addMnfPart: (name) => {
    const cur = get().activeMnfParts;
    if (cur.includes(name)) return;
    set({ activeMnfParts: [...cur, name] });
  },
  removeMnfPart: (name) => {
    const cur = get().activeMnfParts;
    if (!cur.includes(name)) return;
    set({ activeMnfParts: cur.filter((n) => n !== name) });
  },
  setActiveMnfParts: (names) => set({ activeMnfParts: names }),
  reset: () =>
    set({
      loaded: false,
      frameCount: 0,
      times: [],
      currentFrame: 0,
      isPlaying: false,
      colorField: "none",
      activeMnfParts: [],
      availableMnfParts: [],
    }),
}));

export const useThemeStore = create<ThemeState>((set) => ({
  theme: "dark",
  toggleTheme: () =>
    set((s) => {
      const next = s.theme === "dark" ? "light" : "dark";
      document.documentElement.setAttribute("data-theme", next);
      return { theme: next };
    }),
}));
