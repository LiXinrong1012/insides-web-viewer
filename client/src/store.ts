import { create } from "zustand";
import { type TreeNode } from "./services/api";

interface ModelState {
  tree: TreeNode | null;
  selectedItemId: number | null;
  filePath: string | null;
  setTree: (tree: TreeNode) => void;
  selectItem: (id: number | null) => void;
  setFilePath: (path: string | null) => void;
}

export const useModelStore = create<ModelState>((set) => ({
  tree: null,
  selectedItemId: null,
  filePath: null,
  setTree: (tree) => set({ tree }),
  selectItem: (id) => set({ selectedItemId: id }),
  setFilePath: (path) => set({ filePath: path }),
}));

export type ViewId = "tree" | "3d" | "curves" | "table" | "editor" | "solver";

interface ViewState {
  activeView: ViewId;
  setActiveView: (id: ViewId) => void;
}

export const useViewStore = create<ViewState>((set) => ({
  activeView: "tree",
  setActiveView: (id) => set({ activeView: id }),
}));

export type Theme = "dark" | "light";

interface ThemeState {
  theme: Theme;
  toggleTheme: () => void;
}

export const useThemeStore = create<ThemeState>((set) => ({
  theme: "dark",
  toggleTheme: () =>
    set((s) => {
      const next = s.theme === "dark" ? "light" : "dark";
      document.documentElement.setAttribute("data-theme", next);
      return { theme: next };
    }),
}));
