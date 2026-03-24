import { useRef } from "react";
import { uploadModel } from "../../services/api";
import { useModelStore, useThemeStore } from "../../store";

export default function RibbonBar() {
  const fileInput = useRef<HTMLInputElement>(null);
  const setTree = useModelStore((s) => s.setTree);
  const setFilePath = useModelStore((s) => s.setFilePath);
  const filePath = useModelStore((s) => s.filePath);
  const { theme, toggleTheme } = useThemeStore();

  const handleOpen = () => fileInput.current?.click();

  const handleFileChange = async (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0];
    if (!file) return;
    const result = await uploadModel(file);
    setTree(result.tree);
    setFilePath(result.filename);
    e.target.value = "";
  };

  return (
    <div style={S.bar}>
      <div style={S.logo}>INSIDES</div>
      <div style={S.group}>
        <button style={S.btn} onClick={handleOpen}>Open TDY</button>
        <input ref={fileInput} type="file" accept=".tdy,.xml" style={{ display: "none" }} onChange={handleFileChange} />
      </div>
      <div style={{ flex: 1 }} />
      <div style={{ color: "var(--text-secondary)", fontSize: 12 }}>{filePath ?? "No file loaded"}</div>
      <button style={S.themeBtn} onClick={toggleTheme} title="Toggle theme">
        {theme === "dark" ? "\u2600\ufe0f" : "\u{1f319}"}
      </button>
    </div>
  );
}

const S: Record<string, React.CSSProperties> = {
  bar: {
    display: "flex", alignItems: "center", height: 40,
    background: "var(--bg-tertiary)", borderBottom: "1px solid var(--border)",
    padding: "0 12px", gap: 12, flexShrink: 0,
  },
  logo: { fontWeight: 700, fontSize: 14, color: "var(--accent)", letterSpacing: 2 },
  group: { display: "flex", gap: 6 },
  btn: {
    padding: "4px 12px", background: "var(--accent)", color: "#fff",
    border: "none", borderRadius: 3, cursor: "pointer", fontSize: 12,
  },
  themeBtn: {
    padding: "4px 8px", background: "transparent", border: "1px solid var(--border)",
    borderRadius: 3, cursor: "pointer", fontSize: 14, marginLeft: 8,
  },
};
