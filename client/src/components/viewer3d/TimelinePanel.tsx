import { useAnimationStore, type ColorField } from "../../store";

/** Timeline overlay for MNF result animation: play/pause, slider, FPS, color field, multi-part.
 *  NOTE: The actual playback loop lives in SceneView — it advances only after
 *  each frame has been rendered to the GPU, so we never skip frames just
 *  because the network is slow.
 */
export default function TimelinePanel() {
  const loaded = useAnimationStore((s) => s.loaded);
  const frameCount = useAnimationStore((s) => s.frameCount);
  const times = useAnimationStore((s) => s.times);
  const currentFrame = useAnimationStore((s) => s.currentFrame);
  const isPlaying = useAnimationStore((s) => s.isPlaying);
  const playbackFps = useAnimationStore((s) => s.playbackFps);
  const colorField = useAnimationStore((s) => s.colorField);
  const activeMnfParts = useAnimationStore((s) => s.activeMnfParts);
  const availableMnfParts = useAnimationStore((s) => s.availableMnfParts);
  const setFrame = useAnimationStore((s) => s.setFrame);
  const stepFrame = useAnimationStore((s) => s.stepFrame);
  const togglePlay = useAnimationStore((s) => s.togglePlay);
  const setPlaybackFps = useAnimationStore((s) => s.setPlaybackFps);
  const setColorField = useAnimationStore((s) => s.setColorField);
  const addMnfPart = useAnimationStore((s) => s.addMnfPart);
  const removeMnfPart = useAnimationStore((s) => s.removeMnfPart);

  if (!loaded) {
    return (
      <div style={containerStyle} data-testid="timeline-panel">
        <span style={{ color: "#999", fontSize: 11 }}>No results loaded</span>
      </div>
    );
  }

  const time = times[currentFrame] ?? 0;
  const candidatesToAdd = availableMnfParts.filter((p) => !activeMnfParts.includes(p));

  return (
    <div style={containerStyle} data-testid="timeline-panel" data-frame={currentFrame}>
      <button style={btn} onClick={() => setFrame(0)} title="First frame" data-testid="tl-first">⏮</button>
      <button style={btn} onClick={() => stepFrame(-1)} title="Previous frame" data-testid="tl-prev">‹</button>
      <button
        style={playBtn(isPlaying)}
        onClick={togglePlay}
        title={isPlaying ? "Pause" : "Play"}
        data-testid="tl-play"
      >
        {isPlaying ? "PAUSE" : "PLAY"}
      </button>
      <button style={btn} onClick={() => stepFrame(1)} title="Next frame" data-testid="tl-next">›</button>
      <button style={btn} onClick={() => setFrame(frameCount - 1)} title="Last frame" data-testid="tl-last">⏭</button>

      <input
        type="range"
        min={0}
        max={Math.max(0, frameCount - 1)}
        value={currentFrame}
        onChange={(e) => setFrame(parseInt(e.target.value, 10))}
        style={{ flex: 1, minWidth: 120 }}
        data-testid="tl-slider"
      />
      <span style={label} data-testid="tl-frame-label">{currentFrame + 1} / {frameCount}</span>
      <span style={label}>t={time.toFixed(4)}s</span>

      <label style={label}>
        fps
        <input
          type="number"
          min={1}
          max={60}
          value={playbackFps}
          onChange={(e) => setPlaybackFps(parseInt(e.target.value, 10) || 15)}
          style={{ width: 42, marginLeft: 4 }}
        />
      </label>

      <select
        value={colorField}
        onChange={(e) => setColorField(e.target.value as ColorField)}
        style={select}
        data-testid="tl-color-field"
      >
        <option value="none">No color</option>
        <option value="mises">Mises Stress</option>
      </select>

      <span style={label}>Stress parts:</span>
      <div style={{ display: "flex", gap: 3, flexWrap: "wrap", maxWidth: 320 }} data-testid="tl-active-parts">
        {activeMnfParts.length === 0 && <span style={{ color: "#666", fontSize: 10 }}>(none)</span>}
        {activeMnfParts.map((p) => (
          <span key={p} style={chip}>
            {p}
            <button
              style={chipX}
              onClick={() => removeMnfPart(p)}
              title="Remove"
              data-testid={`tl-remove-${p}`}
            >
              ×
            </button>
          </span>
        ))}
      </div>
      <select
        value=""
        onChange={(e) => {
          if (e.target.value) {
            addMnfPart(e.target.value);
            e.target.value = "";
          }
        }}
        style={{ ...select, maxWidth: 130 }}
        data-testid="tl-add-part"
      >
        <option value="">+ Add part…</option>
        {candidatesToAdd.map((p) => (
          <option key={p} value={p}>{p}</option>
        ))}
      </select>
    </div>
  );
}

const containerStyle: React.CSSProperties = {
  position: "absolute",
  bottom: 8,
  left: 8,
  right: 8,
  display: "flex",
  alignItems: "center",
  gap: 6,
  padding: "6px 10px",
  background: "rgba(20,20,30,0.85)",
  border: "1px solid #555",
  borderRadius: 4,
  color: "#ddd",
  fontSize: 11,
  pointerEvents: "auto",
  zIndex: 10,
};

const btn: React.CSSProperties = {
  padding: "2px 6px",
  minWidth: 24,
  background: "#2d2d30",
  color: "#ddd",
  border: "1px solid #555",
  borderRadius: 3,
  cursor: "pointer",
  fontSize: 14,
  lineHeight: 1,
};

const playBtn = (isPlaying: boolean): React.CSSProperties => ({
  padding: "3px 12px",
  minWidth: 60,
  background: isPlaying ? "#c94a4a" : "#2d8a3e",
  color: "#fff",
  border: "1px solid #111",
  borderRadius: 3,
  cursor: "pointer",
  fontSize: 11,
  fontWeight: 700,
  letterSpacing: 1,
  margin: "0 4px",
  boxShadow: "0 1px 2px rgba(0,0,0,0.4)",
});

const label: React.CSSProperties = {
  color: "#aaa",
  fontSize: 11,
  whiteSpace: "nowrap",
};

const select: React.CSSProperties = {
  background: "#2d2d30",
  color: "#ddd",
  border: "1px solid #555",
  borderRadius: 3,
  fontSize: 11,
  padding: "2px 4px",
};

const chip: React.CSSProperties = {
  display: "inline-flex",
  alignItems: "center",
  gap: 2,
  padding: "1px 4px",
  background: "#234",
  color: "#cde",
  border: "1px solid #456",
  borderRadius: 3,
  fontSize: 10,
};

const chipX: React.CSSProperties = {
  background: "transparent",
  color: "#cde",
  border: "none",
  cursor: "pointer",
  fontSize: 12,
  padding: "0 2px",
};
