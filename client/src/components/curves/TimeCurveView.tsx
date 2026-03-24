import { useEffect, useState, useCallback } from "react";

interface ResultItem { entity_id: string; entity_name: string; }

export default function TimeCurveView() {
  const [items, setItems] = useState<ResultItem[]>([]);
  const [selectedIds, setSelectedIds] = useState<string[]>([]);

  const fetchItems = useCallback(async () => {
    try { const r = await fetch("/api/results/items"); const d = await r.json(); setItems(d.items || []); } catch { setItems([]); }
  }, []);

  useEffect(() => { fetchItems(); }, [fetchItems]);

  const handleSample = async () => {
    await fetch("/api/results/load?generate_sample=true", { method: "POST" });
    await fetchItems();
  };

  const toggleItem = (id: string) => setSelectedIds((p) => p.includes(id) ? p.filter((x) => x !== id) : [...p, id]);

  // Simple SVG plot instead of CDN Plotly
  const [plotData, setPlotData] = useState<{ id: string; times: number[]; values: number[] }[]>([]);

  useEffect(() => {
    if (selectedIds.length === 0) { setPlotData([]); return; }
    Promise.all(selectedIds.map(async (id) => {
      const r = await fetch(`/api/results/timeseries/${id}`);
      const d = await r.json();
      return { id, times: d.times, values: d.values };
    })).then(setPlotData).catch(() => setPlotData([]));
  }, [selectedIds]);

  return (
    <div style={{ display: "flex", height: "100%", background: "var(--bg-secondary)" }}>
      <div style={{ width: 150, borderRight: "1px solid var(--border)", display: "flex", flexDirection: "column", flexShrink: 0 }}>
        <div style={{ padding: "4px 6px", background: "var(--bg-tertiary)", fontSize: 11, fontWeight: 600, display: "flex", justifyContent: "space-between", alignItems: "center", color: "var(--text-primary)" }}>
          <span>Results</span>
          <button onClick={handleSample} style={{ padding: "1px 6px", background: "var(--accent)", color: "#fff", border: "none", borderRadius: 2, fontSize: 10, cursor: "pointer" }}>Sample</button>
        </div>
        <div style={{ flex: 1, overflow: "auto", padding: 4 }}>
          {items.length === 0 ? <div style={{ padding: 8, color: "var(--text-secondary)", fontSize: 11, textAlign: "center" }}>No results</div> :
            items.map((it) => (
              <label key={it.entity_id} style={{ display: "flex", alignItems: "center", gap: 4, padding: "2px 0", cursor: "pointer", fontSize: 11, color: "var(--text-primary)" }}>
                <input type="checkbox" checked={selectedIds.includes(it.entity_id)} onChange={() => toggleItem(it.entity_id)} />
                {it.entity_name}
              </label>
            ))}
        </div>
      </div>
      <div style={{ flex: 1, position: "relative" }}>
        {plotData.length === 0 ? (
          <div style={{ display: "flex", alignItems: "center", justifyContent: "center", height: "100%", color: "var(--text-secondary)" }}>Select items to plot</div>
        ) : (
          <SVGPlot data={plotData} />
        )}
      </div>
    </div>
  );
}

const COLORS = ["#4fc3f7", "#81c784", "#ffb74d", "#ef5350", "#ba68c8", "#fff176", "#4dd0e1"];

function SVGPlot({ data }: { data: { id: string; times: number[]; values: number[] }[] }) {
  const margin = { top: 20, right: 20, bottom: 35, left: 55 };
  const W = 600, H = 300;
  const iw = W - margin.left - margin.right;
  const ih = H - margin.top - margin.bottom;

  let tMin = Infinity, tMax = -Infinity, vMin = Infinity, vMax = -Infinity;
  for (const d of data) {
    for (const t of d.times) { tMin = Math.min(tMin, t); tMax = Math.max(tMax, t); }
    for (const v of d.values) { vMin = Math.min(vMin, v); vMax = Math.max(vMax, v); }
  }
  if (tMax === tMin) tMax = tMin + 1;
  if (vMax === vMin) { vMin -= 1; vMax += 1; }
  const pad = (vMax - vMin) * 0.05;
  vMin -= pad; vMax += pad;

  const sx = (t: number) => margin.left + ((t - tMin) / (tMax - tMin)) * iw;
  const sy = (v: number) => margin.top + (1 - (v - vMin) / (vMax - vMin)) * ih;

  return (
    <svg viewBox={`0 0 ${W} ${H}`} style={{ width: "100%", height: "100%" }} preserveAspectRatio="xMidYMid meet">
      <rect width={W} height={H} fill="var(--bg-primary)" />
      {/* Grid */}
      {Array.from({ length: 6 }, (_, i) => {
        const y = margin.top + (ih * i) / 5;
        const val = vMax - ((vMax - vMin) * i) / 5;
        return <g key={`gy${i}`}><line x1={margin.left} y1={y} x2={W - margin.right} y2={y} stroke="var(--border)" strokeWidth={0.5} />
          <text x={margin.left - 4} y={y + 4} fill="var(--text-secondary)" fontSize={9} textAnchor="end">{val.toFixed(2)}</text></g>;
      })}
      {Array.from({ length: 6 }, (_, i) => {
        const x = margin.left + (iw * i) / 5;
        const val = tMin + ((tMax - tMin) * i) / 5;
        return <g key={`gx${i}`}><line x1={x} y1={margin.top} x2={x} y2={H - margin.bottom} stroke="var(--border)" strokeWidth={0.5} />
          <text x={x} y={H - margin.bottom + 14} fill="var(--text-secondary)" fontSize={9} textAnchor="middle">{val.toFixed(2)}</text></g>;
      })}
      {/* Curves */}
      {data.map((d, ci) => {
        const pts = d.times.map((t, i) => `${sx(t)},${sy(d.values[i])}`).join(" ");
        return <g key={d.id}>
          <polyline points={pts} fill="none" stroke={COLORS[ci % COLORS.length]} strokeWidth={1.5} />
          <text x={W - margin.right - 4} y={margin.top + 14 + ci * 14} fill={COLORS[ci % COLORS.length]} fontSize={10} textAnchor="end">{d.id}</text>
        </g>;
      })}
      <text x={W / 2} y={H - 4} fill="var(--text-secondary)" fontSize={10} textAnchor="middle">Time</text>
    </svg>
  );
}
