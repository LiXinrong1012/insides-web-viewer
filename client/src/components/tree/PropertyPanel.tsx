import { useEffect, useState } from "react";
import { fetchItem } from "../../services/api";
import { useModelStore } from "../../store";

export default function PropertyPanel() {
  const selectedId = useModelStore((s) => s.selectedItemId);
  const [item, setItem] = useState<Record<string, unknown> | null>(null);

  useEffect(() => {
    if (selectedId === null) { setItem(null); return; }
    fetchItem(selectedId).then(setItem).catch(() => setItem(null));
  }, [selectedId]);

  if (!item) {
    return <div style={S.empty}>Select an item to view properties</div>;
  }

  const entries = Object.entries(item).filter(([k]) => k !== "children");

  return (
    <div style={S.container}>
      <table style={{ width: "100%", borderCollapse: "collapse" }}>
        <tbody>
          {entries.map(([key, value]) => (
            <tr key={key}>
              <td style={S.key}>{key}</td>
              <td style={S.value}>{JSON.stringify(value)}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

const S: Record<string, React.CSSProperties> = {
  container: { overflow: "auto", height: "100%", padding: 8, background: "var(--bg-secondary)", color: "var(--text-primary)" },
  empty: { padding: 20, color: "var(--text-secondary)", textAlign: "center", background: "var(--bg-secondary)", height: "100%" },
  key: { padding: "3px 8px", color: "var(--text-secondary)", fontSize: 12, whiteSpace: "nowrap", verticalAlign: "top", borderBottom: "1px solid var(--border)" },
  value: { padding: "3px 8px", fontSize: 12, wordBreak: "break-all", borderBottom: "1px solid var(--border)", color: "var(--text-primary)" },
};
