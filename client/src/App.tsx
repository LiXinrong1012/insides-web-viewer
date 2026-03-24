import { Mosaic, MosaicWindow } from "react-mosaic-component";
import "react-mosaic-component/react-mosaic-component.css";
import RibbonBar from "./components/shell/RibbonBar";
import ModelTree from "./components/tree/ModelTree";
import PropertyPanel from "./components/tree/PropertyPanel";
import SceneView from "./components/viewer3d/SceneView";
import TimeCurveView from "./components/curves/TimeCurveView";
import TDYEditor from "./components/editor/TDYEditor";
import SolverPanel from "./components/solver/SolverPanel";
import DataTableView from "./components/tables/DataTableView";

type PanelId = "tree" | "properties" | "3d" | "curves" | "editor" | "solver" | "table";

const PANEL_TITLES: Record<PanelId, string> = {
  tree: "Model Tree",
  properties: "Properties",
  "3d": "3D Viewer",
  curves: "Time Curves",
  editor: "TDY Editor",
  solver: "Solver",
  table: "Data Table",
};

const PANEL_COMPONENTS: Record<PanelId, React.FC> = {
  tree: ModelTree,
  properties: PropertyPanel,
  "3d": SceneView,
  curves: TimeCurveView,
  editor: TDYEditor,
  solver: SolverPanel,
  table: DataTableView,
};

const INITIAL_LAYOUT = {
  direction: "row" as const,
  first: {
    direction: "column" as const,
    first: "tree" as PanelId,
    second: "properties" as PanelId,
    splitPercentage: 60,
  },
  second: {
    direction: "column" as const,
    first: "3d" as PanelId,
    second: {
      direction: "row" as const,
      first: {
        direction: "column" as const,
        first: "editor" as PanelId,
        second: "curves" as PanelId,
        splitPercentage: 55,
      },
      second: {
        direction: "column" as const,
        first: "solver" as PanelId,
        second: "table" as PanelId,
        splitPercentage: 50,
      },
      splitPercentage: 55,
    },
    splitPercentage: 55,
  },
  splitPercentage: 20,
};

export default function App() {
  return (
    <div style={{ display: "flex", flexDirection: "column", height: "100vh" }}>
      <RibbonBar />
      <div style={{ flex: 1, position: "relative" }}>
        <Mosaic<PanelId>
          renderTile={(id, path) => {
            const Component = PANEL_COMPONENTS[id];
            return (
              <MosaicWindow<PanelId>
                path={path}
                title={PANEL_TITLES[id]}
                toolbarControls={<div />}
              >
                <Component />
              </MosaicWindow>
            );
          }}
          initialValue={INITIAL_LAYOUT}
          className="mosaic-blueprint-theme bp5-dark"
        />
      </div>
    </div>
  );
}
