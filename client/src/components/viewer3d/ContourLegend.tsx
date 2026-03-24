interface LegendEntry {
  value: number;
  color: number[];
}

interface ContourLegendProps {
  entries: LegendEntry[];
  title?: string;
}

export default function ContourLegend({ entries, title }: ContourLegendProps) {
  if (!entries || entries.length === 0) return null;

  return (
    <div style={{
      position: "absolute", right: 12, top: 40, width: 80,
      background: "rgba(30,30,30,0.9)", borderRadius: 4, padding: "6px 8px",
      color: "#ccc", fontSize: 10, pointerEvents: "none",
    }}>
      {title && <div style={{ textAlign: "center", marginBottom: 4, fontSize: 9, fontWeight: "bold" }}>{title}</div>}
      <div style={{ display: "flex", flexDirection: "column-reverse" }}>
        {entries.map((e, i) => (
          <div key={i} style={{ display: "flex", alignItems: "center", gap: 4 }}>
            <div style={{
              width: 16, height: entries.length > 8 ? 12 : 16,
              background: `rgb(${e.color[0]},${e.color[1]},${e.color[2]})`,
              flexShrink: 0, borderRadius: 1,
            }} />
            <span style={{ fontSize: 8, whiteSpace: "nowrap" }}>
              {e.value.toExponential(2)}
            </span>
          </div>
        ))}
      </div>
    </div>
  );
}
