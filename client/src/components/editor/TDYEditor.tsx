import { useEffect, useRef, useState, useCallback } from "react";

interface CompileResult {
  success: boolean;
  errors: { message: string; row: number; col: number; severity: string }[];
  parameters: { key: string; value: string }[];
  item_count: number;
}

export default function TDYEditor() {
  const textareaRef = useRef<HTMLTextAreaElement>(null);
  const lineNumRef = useRef<HTMLDivElement>(null);
  const [text, setText] = useState(SAMPLE_TDY);
  const [result, setResult] = useState<CompileResult | null>(null);
  const [compiling, setCompiling] = useState(false);

  const compile = useCallback(async () => {
    setCompiling(true);
    try {
      const res = await fetch("/api/editor/compile", {
        method: "POST", headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ text, filename: "editor.tdy" }),
      });
      setResult(await res.json());
    } catch { setResult(null); }
    setCompiling(false);
  }, [text]);

  useEffect(() => { const t = setTimeout(compile, 800); return () => clearTimeout(t); }, [text, compile]);

  const handleScroll = () => {
    if (textareaRef.current && lineNumRef.current)
      lineNumRef.current.scrollTop = textareaRef.current.scrollTop;
  };

  const lineCount = text.split("\n").length;

  return (
    <div style={{ display: "flex", flexDirection: "column", height: "100%", background: "var(--bg-primary)" }}>
      <div style={{ display: "flex", alignItems: "center", padding: "4px 8px", background: "var(--bg-tertiary)", borderBottom: "1px solid var(--border)", flexShrink: 0 }}>
        <button style={{ padding: "3px 10px", background: "var(--accent)", color: "#fff", border: "none", borderRadius: 3, cursor: "pointer", fontSize: 12 }} onClick={compile} disabled={compiling}>
          {compiling ? "Compiling..." : "Compile"}
        </button>
        {result && (
          <span style={{ color: result.success ? "var(--success)" : "var(--error)", marginLeft: 8, fontSize: 12 }}>
            {result.success ? `OK (${result.item_count} items, ${result.parameters.length} params)` : `${result.errors.length} error(s)`}
          </span>
        )}
      </div>
      <div style={{ display: "flex", flex: 1, overflow: "hidden" }}>
        <div ref={lineNumRef} style={{ width: 40, background: "var(--bg-primary)", borderRight: "1px solid var(--border)", overflow: "hidden", paddingTop: 4, flexShrink: 0 }}>
          {Array.from({ length: lineCount }, (_, i) => (
            <div key={i} style={{ height: 18, lineHeight: "18px", textAlign: "right", paddingRight: 8, color: "var(--text-secondary)", fontSize: 12, fontFamily: "monospace" }}>{i + 1}</div>
          ))}
        </div>
        <textarea ref={textareaRef} value={text} onChange={(e) => setText(e.target.value)} onScroll={handleScroll} spellCheck={false}
          style={{ flex: 1, background: "var(--bg-primary)", color: "var(--text-primary)", border: "none", outline: "none", resize: "none", padding: "4px 8px", fontSize: 13, fontFamily: "monospace", lineHeight: "18px", tabSize: 4 }} />
      </div>
      {result && result.errors.length > 0 && (
        <div style={{ maxHeight: 80, overflow: "auto", borderTop: "1px solid var(--error)", flexShrink: 0 }}>
          <div style={{ padding: "2px 8px", background: "var(--bg-tertiary)", color: "var(--error)", fontSize: 11, fontWeight: 600 }}>Errors</div>
          {result.errors.map((e, i) => (
            <div key={i} style={{ padding: "2px 8px", fontSize: 12, color: "var(--text-primary)", borderBottom: "1px solid var(--border)" }}>
              <span style={{ color: "var(--error)", marginRight: 8, fontSize: 11 }}>Ln {e.row + 1}:{e.col + 1}</span>{e.message}
            </div>
          ))}
        </div>
      )}
      {result && result.parameters.length > 0 && (
        <div style={{ maxHeight: 70, overflow: "auto", borderTop: "1px solid var(--border)", flexShrink: 0 }}>
          <div style={{ padding: "2px 8px", background: "var(--bg-tertiary)", color: "var(--success)", fontSize: 11, fontWeight: 600 }}>Parameters</div>
          {result.parameters.map((p, i) => (
            <div key={i} style={{ padding: "1px 8px", fontSize: 12, display: "flex", gap: 12 }}>
              <span style={{ color: "var(--accent)", minWidth: 80 }}>{p.key}</span>
              <span style={{ color: "var(--text-secondary)" }}>{p.value}</span>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}

const SAMPLE_TDY = `! Sample TDY — Open a real model with "Open TDY"
PARAMETER / 1
, L = 1.0
, N = 20

RIGIDPART / Body1 {
    RIGID6 / 1, MASS = 10, QG = 0, 0, 0
    MARKER / 1, MK_A, QG = 0, 0, 0
    GRAPHIC / 1, SPHERE, RADIUS = 0.05, RGB = 255, 50, 50
}

INSTANCE / 1, INS_Body1, PART = Body1, CENTER = 0, 0, 0
END
`;
