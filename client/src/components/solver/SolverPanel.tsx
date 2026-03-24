import { useEffect, useRef, useState, useCallback } from "react";

interface SolverStatus { state: string; cpu_time: number; sim_time: number; max_time: number; percentage: number; error_message: string; }

export default function SolverPanel() {
  const [status] = useState<SolverStatus>({ state: "idle", cpu_time: 0, sim_time: 0, max_time: 0, percentage: 0, error_message: "" });
  const [logs, setLogs] = useState<string[]>([]);
  const [modelDir, setModelDir] = useState("");
  const [tdyFile, setTdyFile] = useState("main.tdy");
  const logEndRef = useRef<HTMLDivElement>(null);

  useEffect(() => { logEndRef.current?.scrollIntoView({ behavior: "smooth" }); }, [logs]);

  useEffect(() => {
    if (status.state !== "running") return;
    const iv = setInterval(async () => {
      const r = await fetch("/api/solver/logs?last_n=200"); const d = await r.json(); setLogs(d.lines);
    }, 1000);
    return () => clearInterval(iv);
  }, [status.state]);

  const start = useCallback(async () => {
    if (!modelDir) return;
    await fetch(`/api/solver/start?model_dir=${encodeURIComponent(modelDir)}&tdy_file=${encodeURIComponent(tdyFile)}`, { method: "POST" });
  }, [modelDir, tdyFile]);

  const stop = useCallback(async () => { await fetch("/api/solver/stop", { method: "POST" }); }, []);
  const isRunning = status.state === "running" || status.state === "starting";

  return (
    <div style={{ display: "flex", flexDirection: "column", height: "100%", background: "var(--bg-primary)" }}>
      <div style={{ padding: 8, borderBottom: "1px solid var(--border)", display: "flex", flexDirection: "column", gap: 4 }}>
        <label style={{ fontSize: 12, color: "var(--text-secondary)", display: "flex", alignItems: "center", gap: 6 }}>
          Dir: <input style={inputS} value={modelDir} onChange={(e) => setModelDir(e.target.value)} placeholder="D:\path\to\model" />
        </label>
        <label style={{ fontSize: 12, color: "var(--text-secondary)", display: "flex", alignItems: "center", gap: 6 }}>
          File: <input style={inputS} value={tdyFile} onChange={(e) => setTdyFile(e.target.value)} />
        </label>
        <div style={{ display: "flex", gap: 6, marginTop: 4 }}>
          <button style={{ ...btnS, background: "#388e3c" }} onClick={start} disabled={isRunning}>Start</button>
          <button style={{ ...btnS, background: "#d32f2f" }} onClick={stop} disabled={!isRunning}>Stop</button>
        </div>
      </div>
      <div style={{ display: "flex", alignItems: "center", gap: 8, padding: "4px 8px", background: "var(--bg-tertiary)" }}>
        <span style={{ padding: "1px 6px", borderRadius: 2, fontSize: 11, fontWeight: 600, color: "#fff", background: status.state === "running" ? "#388e3c" : status.state === "error" ? "#d32f2f" : "var(--border)" }}>{status.state.toUpperCase()}</span>
        <div style={{ flex: 1, height: 6, background: "var(--border)", borderRadius: 3, overflow: "hidden" }}>
          <div style={{ height: "100%", background: "var(--accent)", width: `${status.percentage}%`, transition: "width 0.3s" }} />
        </div>
        <span style={{ fontSize: 11, color: "var(--text-secondary)" }}>{status.percentage.toFixed(1)}%</span>
      </div>
      {status.error_message && <div style={{ padding: "4px 8px", fontSize: 12, color: "var(--error)" }}>{status.error_message}</div>}
      <div style={{ flex: 1, overflow: "auto", padding: "4px 8px", fontFamily: "monospace", fontSize: 11 }}>
        {logs.map((l, i) => <div key={i} style={{ color: "var(--text-primary)", lineHeight: "16px", whiteSpace: "pre" }}>{l}</div>)}
        <div ref={logEndRef} />
      </div>
    </div>
  );
}

const inputS: React.CSSProperties = { flex: 1, background: "var(--bg-secondary)", border: "1px solid var(--border)", color: "var(--text-primary)", padding: "2px 6px", fontSize: 12, borderRadius: 2 };
const btnS: React.CSSProperties = { padding: "3px 12px", color: "#fff", border: "none", borderRadius: 3, cursor: "pointer", fontSize: 12 };
