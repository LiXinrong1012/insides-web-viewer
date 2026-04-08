import { useEffect, useState } from "react";
import { fetchModelTree, type TreeNode } from "../../services/api";
import { useModelStore, useVisibilityStore } from "../../store";

function TreeItem({ node, depth }: { node: TreeNode; depth: number }) {
  const [expanded, setExpanded] = useState(!node.collapsed);
  const selectedId = useModelStore((s) => s.selectedItemId);
  const selectItem = useModelStore((s) => s.selectItem);
  // Subscribing to `version` makes this component re-render whenever the
  // visibility set changes, without us having to store a computed flag.
  useVisibilityStore((s) => s.version);
  const isHidden = useVisibilityStore.getState().isHidden;
  const hasChildren = node.children.length > 0;
  const isSelected = selectedId === node.id;
  const hidden = isHidden(node.keyname);

  return (
    <div>
      <div
        onClick={() => selectItem(node.id, node.keyname)}
        style={{
          display: "flex",
          alignItems: "center",
          height: 24,
          paddingLeft: depth * 16 + 4,
          background: isSelected ? "var(--bg-hover)" : "transparent",
          cursor: "pointer",
          userSelect: "none",
          gap: 4,
          opacity: hidden ? 0.45 : 1,
        }}
      >
        {hasChildren ? (
          <span style={S.arrow} onClick={(e) => { e.stopPropagation(); setExpanded(!expanded); }}>
            {expanded ? "\u25be" : "\u25b8"}
          </span>
        ) : <span style={S.arrow}>{"\u00a0"}</span>}
        <span style={{ fontSize: 12, flexShrink: 0 }}>{categoryIcon(node.category)}</span>
        <span
          style={{
            fontSize: 12,
            whiteSpace: "nowrap",
            color: "var(--text-primary)",
            textDecoration: hidden ? "line-through" : "none",
          }}
        >
          {node.keyname}
        </span>
      </div>
      {expanded && node.children.map((c) => <TreeItem key={c.id} node={c} depth={depth + 1} />)}
    </div>
  );
}

function categoryIcon(cat: string): string {
  const icons: Record<string, string> = {
    ASSEMBLY: "\u{1f4e6}", FOLDER: "\u{1f4c1}", RIGID_PART: "\u{1f529}",
    FEM_PART: "\u{1f537}", CONSTRAINT: "\u{1f517}", LOAD: "\u26a1",
    CONTACT: "\u{1f4a5}", MARKER: "\u{1f4cd}", GROUND: "\u{1f30d}",
    JOINT: "\u{1f517}", PARAMETER: "\u{1f522}", SHAPE: "\u{1f534}",
    INSTANCE: "\u{1f4cb}", REQUEST: "\u{1f4ca}", SET: "\u{1f4c2}",
  };
  return icons[cat] ?? "\u{1f4c4}";
}

export default function ModelTree() {
  const tree = useModelStore((s) => s.tree);
  const setTree = useModelStore((s) => s.setTree);

  // Only fetch once per session.  Re-mounting the tab (e.g. switching tabs)
  // must not refetch and trigger a full scene reload — that caused visible
  // flickering during playback.
  useEffect(() => {
    if (tree) return;
    fetchModelTree().then(setTree).catch(() => {});
  }, [tree, setTree]);

  if (!tree) {
    return <div style={S.empty}>Open a TDY file to view model tree</div>;
  }
  return (
    <div style={S.container} data-testid="model-tree">
      <TreeItem node={tree} depth={0} />
    </div>
  );
}

const S: Record<string, React.CSSProperties> = {
  container: { overflow: "auto", height: "100%", padding: "4px 0", background: "var(--bg-secondary)", color: "var(--text-primary)" },
  arrow: { width: 14, textAlign: "center", fontSize: 10, color: "var(--text-secondary)", cursor: "pointer", flexShrink: 0 },
  empty: { padding: 20, color: "var(--text-secondary)", textAlign: "center", background: "var(--bg-secondary)", height: "100%" },
};
