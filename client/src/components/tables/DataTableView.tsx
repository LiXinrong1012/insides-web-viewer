import { useEffect, useState, useCallback } from "react";

interface ResultItem { entity_id: string; entity_name: string; }
interface FrameData { frame: number; time: number; items: Record<string, { section: string; value: number }>; }

export default function DataTableView() {
  const [items, setItems] = useState<ResultItem[]>([]);
  const [frameIndex, setFrameIndex] = useState(0);
  const [frameCount, setFrameCount] = useState(0);
  const [frameData, setFrameData] = useState<FrameData | null>(null);
  const [playing, setPlaying] = useState(false);

  const fetchItems = useCallback(async () => {
    try { const r = await fetch("/api/results/items"); const d = await r.json(); setItems(d.items || []); setFrameCount(d.frame_count || 0); } catch { setItems([]); }
  }, []);
  useEffect(() => { fetchItems(); }, [fetchItems]);

  useEffect(() => {
    if (frameCount === 0) return;
    fetch(`/api/results/frame/${frameIndex}`).then((r) => r.json()).then(setFrameData).catch(() => setFrameData(null));
  }, [frameIndex, frameCount]);

  useEffect(() => {
    if (!playing || frameCount === 0) return;
    const iv = setInterval(() => setFrameIndex((p) => (p + 1) % frameCount), 50);
    return () => clearInterval(iv);
  }, [playing, frameCount]);

  return (
    <div style={{ display: "flex", flexDirection: "column", height: "100%", background: "var(--bg-primary)" }}>
      <div style={{ display: "flex", alignItems: "center", gap: 6, padding: "4px 8px", background: "var(--bg-tertiary)", borderBottom: "1px solid var(--border)", flexShrink: 0 }}>
        <button style={btnS} onClick={fetchItems}>Refresh</button>
        {frameCount > 0 && <>
          <button style={btnS} onClick={() => setPlaying(!playing)}>{playing ? "Pause" : "Play"}</button>
          <input type="range" min={0} max={frameCount - 1} value={frameIndex} onChange={(e) => { setPlaying(false); setFrameIndex(Number(e.target.value)); }} style={{ flex: 1 }} />
          <span style={{ fontSize: 11, color: "var(--text-secondary)", whiteSpace: "nowrap" }}>
            {frameIndex + 1}/{frameCount}{frameData ? ` t=${frameData.time.toFixed(4)}` : ""}
          </span>
        </>}
      </div>
      <div style={{ flex: 1, overflow: "auto" }}>
        {items.length === 0 ? <div style={{ padding: 20, color: "var(--text-secondary)", textAlign: "center", fontSize: 12 }}>No results. Click "Sample" in Curves panel.</div> :
          <table style={{ width: "100%", borderCollapse: "collapse" }}>
            <thead><tr>
              <th style={thS}>Entity</th><th style={thS}>Value</th>
            </tr></thead>
            <tbody>{items.map((it) => {
              const fd = frameData?.items[it.entity_id];
              return <tr key={it.entity_id}>
                <td style={tdS}>{it.entity_name}</td>
                <td style={{ ...tdS, fontFamily: "monospace", textAlign: "right" }}>{fd ? fd.value.toFixed(6) : "-"}</td>
              </tr>;
            })}</tbody>
          </table>}
      </div>
    </div>
  );
}

const btnS: React.CSSProperties = { padding: "2px 8px", background: "var(--accent)", color: "#fff", border: "none", borderRadius: 2, fontSize: 11, cursor: "pointer" };
const thS: React.CSSProperties = { padding: "4px 8px", background: "var(--bg-tertiary)", color: "var(--text-secondary)", fontSize: 11, fontWeight: 600, textAlign: "left", borderBottom: "1px solid var(--border)", position: "sticky", top: 0 };
const tdS: React.CSSProperties = { padding: "3px 8px", fontSize: 12, borderBottom: "1px solid var(--border)", color: "var(--text-primary)" };
