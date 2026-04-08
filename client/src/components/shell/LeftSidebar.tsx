import { useLayoutStore, type LeftTabId } from "../../store";
import ModelTree from "../tree/ModelTree";
import PropertyPanel from "../tree/PropertyPanel";
import TDYEditor from "../editor/TDYEditor";
import SolverPanel from "../solver/SolverPanel";
import TimeCurveView from "../curves/TimeCurveView";
import DataTableView from "../tables/DataTableView";

const TABS: { id: LeftTabId; label: string }[] = [
  { id: "tree", label: "Model" },
  { id: "editor", label: "TDY" },
  { id: "solver", label: "Solver" },
  { id: "curves", label: "Curves" },
  { id: "table", label: "Table" },
];

export default function LeftSidebar() {
  const current = useLayoutStore((s) => s.leftTab);
  const setTab = useLayoutStore((s) => s.setLeftTab);

  return (
    <div style={S.root} data-testid="left-sidebar">
      <div style={S.tabBar} role="tablist">
        {TABS.map((t) => (
          <button
            key={t.id}
            role="tab"
            aria-selected={current === t.id}
            data-testid={`left-tab-${t.id}`}
            style={{
              ...S.tab,
              ...(current === t.id ? S.tabActive : {}),
            }}
            onClick={() => setTab(t.id)}
          >
            {t.label}
          </button>
        ))}
      </div>
      <div style={S.body}>
        {current === "tree" && (
          <div style={S.splitCol}>
            <div style={{ flex: 1.4, minHeight: 0, overflow: "hidden" }}>
              <ModelTree />
            </div>
            <div style={S.splitSep} />
            <div style={{ flex: 1, minHeight: 0, overflow: "hidden" }}>
              <PropertyPanel />
            </div>
          </div>
        )}
        {current === "editor" && <TDYEditor />}
        {current === "solver" && <SolverPanel />}
        {current === "curves" && <TimeCurveView />}
        {current === "table" && <DataTableView />}
      </div>
    </div>
  );
}

const S: Record<string, React.CSSProperties> = {
  root: {
    display: "flex",
    flexDirection: "column",
    height: "100%",
    background: "var(--bg-secondary)",
    borderRight: "1px solid var(--border)",
    minWidth: 0,
  },
  tabBar: {
    display: "flex",
    flexShrink: 0,
    background: "var(--bg-tertiary)",
    borderBottom: "1px solid var(--border)",
  },
  tab: {
    flex: 1,
    padding: "8px 6px",
    background: "transparent",
    color: "var(--text-secondary)",
    border: "none",
    borderRight: "1px solid var(--border)",
    cursor: "pointer",
    fontSize: 12,
    fontWeight: 500,
    letterSpacing: 0.3,
  },
  tabActive: {
    background: "var(--bg-secondary)",
    color: "var(--accent)",
    borderBottom: "2px solid var(--accent)",
  },
  body: {
    flex: 1,
    minHeight: 0,
    overflow: "hidden",
    display: "flex",
    flexDirection: "column",
  },
  splitCol: {
    display: "flex",
    flexDirection: "column",
    height: "100%",
    minHeight: 0,
  },
  splitSep: {
    height: 1,
    background: "var(--border)",
    flexShrink: 0,
  },
};
