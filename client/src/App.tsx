import { useEffect, useRef, useState } from "react";
import RibbonBar from "./components/shell/RibbonBar";
import LeftSidebar from "./components/shell/LeftSidebar";
import SceneView from "./components/viewer3d/SceneView";

const MIN_LEFT = 260;
const MAX_LEFT_RATIO = 0.6;
const DEFAULT_LEFT_RATIO = 0.28;

export default function App() {
  const containerRef = useRef<HTMLDivElement>(null);
  const [leftWidth, setLeftWidth] = useState<number>(() =>
    Math.max(MIN_LEFT, Math.floor(window.innerWidth * DEFAULT_LEFT_RATIO)),
  );
  const dragRef = useRef<{ startX: number; startW: number } | null>(null);

  useEffect(() => {
    const onMove = (e: MouseEvent) => {
      if (!dragRef.current || !containerRef.current) return;
      const containerW = containerRef.current.clientWidth;
      const dx = e.clientX - dragRef.current.startX;
      const next = Math.max(
        MIN_LEFT,
        Math.min(Math.floor(containerW * MAX_LEFT_RATIO), dragRef.current.startW + dx),
      );
      setLeftWidth(next);
    };
    const onUp = () => {
      dragRef.current = null;
      document.body.style.cursor = "";
    };
    window.addEventListener("mousemove", onMove);
    window.addEventListener("mouseup", onUp);
    return () => {
      window.removeEventListener("mousemove", onMove);
      window.removeEventListener("mouseup", onUp);
    };
  }, []);

  return (
    <div style={{ display: "flex", flexDirection: "column", height: "100vh", minHeight: 0 }}>
      <RibbonBar />
      <div ref={containerRef} style={{ flex: 1, minHeight: 0, display: "flex", position: "relative" }}>
        <div style={{ width: leftWidth, flexShrink: 0, minWidth: MIN_LEFT, overflow: "hidden" }}>
          <LeftSidebar />
        </div>
        <div
          style={{
            width: 4,
            cursor: "col-resize",
            background: "var(--border)",
            flexShrink: 0,
          }}
          onMouseDown={(e) => {
            dragRef.current = { startX: e.clientX, startW: leftWidth };
            document.body.style.cursor = "col-resize";
          }}
          title="Drag to resize"
          data-testid="left-resizer"
        />
        <div style={{ flex: 1, minWidth: 0, position: "relative" }}>
          <SceneView />
        </div>
      </div>
    </div>
  );
}
