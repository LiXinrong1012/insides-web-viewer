import { useEffect, useRef, useCallback, useState } from "react";
import * as THREE from "three";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";
import { useModelStore, useAnimationStore, useVisibilityStore } from "../../store";
import ContourLegend from "./ContourLegend";
import TimelinePanel from "./TimelinePanel";
import {
  fetchAllMnfPositionsBin,
  fetchFrames,
  fetchMnfFrame,
  fetchResultStatus,
  fetchRigidTransforms,
  fetchTopo,
  openLoadcase,
  type MnfFramePart,
} from "../../services/api";

interface SceneItem {
  id: number;
  keyname: string;
  category: string;
  position: number[];
  phi?: number[];
  geometry: string;
  radius?: number;
  height?: number;
  color?: number[];
  part_name?: string;
  mesh?: {
    positions: number[];
    normals: number[];
    indices: number[];
  };
}

function phiToQuaternion(phi: number[]): THREE.Quaternion {
  const px = phi[0], py = phi[1], pz = phi[2];
  const angle = Math.sqrt(px * px + py * py + pz * pz);
  if (angle < 1e-10) return new THREE.Quaternion();
  const axis = new THREE.Vector3(px / angle, py / angle, pz / angle);
  return new THREE.Quaternion().setFromAxisAngle(axis, angle);
}

/** Viridis colormap — perceptually uniform, bright throughout so it reads
 *  clearly on the dark scene background (jet's deep blue tended to look
 *  almost black under the ambient light).  Values sampled from the canonical
 *  matplotlib viridis LUT at 17 stops; we linearly interpolate in between.
 */
const VIRIDIS: [number, number, number][] = [
  [0.267, 0.005, 0.329], [0.283, 0.131, 0.449], [0.254, 0.265, 0.530],
  [0.207, 0.372, 0.553], [0.164, 0.471, 0.558], [0.128, 0.567, 0.551],
  [0.135, 0.659, 0.518], [0.267, 0.749, 0.441], [0.478, 0.821, 0.318],
  [0.741, 0.873, 0.150], [0.993, 0.906, 0.144],
];
function viridis(t: number): [number, number, number] {
  t = Math.max(0, Math.min(1, t));
  const n = VIRIDIS.length - 1;
  const x = t * n;
  const i = Math.floor(x);
  const f = x - i;
  const a = VIRIDIS[i];
  const b = VIRIDIS[Math.min(n, i + 1)];
  return [
    a[0] + (b[0] - a[0]) * f,
    a[1] + (b[1] - a[1]) * f,
    a[2] + (b[2] - a[2]) * f,
  ];
}

interface LegendEntry { value: number; color: number[] }
type LegendBlock = { title: string; entries: LegendEntry[] };

export default function SceneView() {
  const canvasRef = useRef<HTMLDivElement>(null);
  const sceneRef = useRef<{
    scene: THREE.Scene;
    camera: THREE.PerspectiveCamera;
    renderer: THREE.WebGLRenderer;
    controls: OrbitControls;
  } | null>(null);
  // Maps from part keyname to THREE.Mesh so we can update per-frame.
  const rigidMeshes = useRef<Map<string, THREE.Mesh>>(new Map());
  const mnfMeshes = useRef<Map<string, THREE.Mesh>>(new Map());

  const viewBoundsRef = useRef<{ center: THREE.Vector3; dist: number } | null>(null);
  const [info, setInfo] = useState("Ready");
  const [legends, setLegends] = useState<LegendBlock[]>([]);
  const [resultsStatus, setResultsStatus] = useState<string>("");

  const tree = useModelStore((s) => s.tree);
  const selectedKeyname = useModelStore((s) => s.selectedKeyname);
  const visVersion = useVisibilityStore((s) => s.version);

  // Animation store
  const animLoaded = useAnimationStore((s) => s.loaded);
  const currentFrame = useAnimationStore((s) => s.currentFrame);
  const activeMnfParts = useAnimationStore((s) => s.activeMnfParts);
  const colorField = useAnimationStore((s) => s.colorField);
  const setAnimLoaded = useAnimationStore((s) => s.setLoaded);

  // ---------- scene bootstrap ----------
  useEffect(() => {
    if (!canvasRef.current) return;
    const container = canvasRef.current;
    const w = container.clientWidth || 400;
    const h = container.clientHeight || 300;

    const scene = new THREE.Scene();
    scene.background = new THREE.Color(0x1a1a2e);

    const camera = new THREE.PerspectiveCamera(60, w / h, 0.01, 1000);
    camera.position.set(2, 1.5, 2);
    camera.lookAt(0, 0, 0);

    const renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(w, h);
    renderer.setPixelRatio(window.devicePixelRatio);
    container.innerHTML = "";
    container.appendChild(renderer.domElement);

    // Balanced 3-light rig: hemisphere (sky + ground fill) + key + opposing
    // fill to keep the back side lit.  Everything is unshadowed so we never
    // get the hard "half the model is black" look the default rig produced.
    scene.add(new THREE.AmbientLight(0xffffff, 0.55));
    scene.add(new THREE.HemisphereLight(0xcfd8ff, 0x2a2a30, 0.55));

    const key = new THREE.DirectionalLight(0xffffff, 0.75);
    key.position.set(5, 10, 7);
    scene.add(key);

    const fill = new THREE.DirectionalLight(0xffffff, 0.55);
    fill.position.set(-6, -4, -8);
    scene.add(fill);

    const rim = new THREE.DirectionalLight(0xffe4b5, 0.35);
    rim.position.set(0, -8, 4);
    scene.add(rim);

    scene.add(new THREE.GridHelper(4, 20, 0x333355, 0x222244));
    scene.add(new THREE.AxesHelper(1));

    const controls = new OrbitControls(camera, renderer.domElement);
    controls.enableDamping = true;
    controls.dampingFactor = 0.05;

    sceneRef.current = { scene, camera, renderer, controls };

    let animId: number;
    const animate = () => {
      animId = requestAnimationFrame(animate);
      controls.update();
      renderer.render(scene, camera);
    };
    animate();

    const resizeObs = new ResizeObserver(() => {
      const nw = container.clientWidth;
      const nh = container.clientHeight;
      if (nw > 0 && nh > 0) {
        camera.aspect = nw / nh;
        camera.updateProjectionMatrix();
        renderer.setSize(nw, nh);
      }
    });
    resizeObs.observe(container);

    // Click picking
    const raycaster = new THREE.Raycaster();
    const mouse = new THREE.Vector2();
    const handleClick = (e: MouseEvent) => {
      const rect = renderer.domElement.getBoundingClientRect();
      mouse.x = ((e.clientX - rect.left) / rect.width) * 2 - 1;
      mouse.y = -((e.clientY - rect.top) / rect.height) * 2 + 1;
      raycaster.setFromCamera(mouse, camera);
      const meshes: THREE.Mesh[] = [];
      scene.traverse((o) => {
        const m = o as THREE.Mesh;
        if (m.isMesh && m.visible) meshes.push(m);
      });
      const hits = raycaster.intersectObjects(meshes, false);
      if (hits.length > 0) {
        const ud = hits[0].object.userData;
        const keyname: string | undefined = ud?.partName || ud?.keyname;
        if (keyname) {
          useModelStore.getState().selectItem(ud.itemId ?? null, keyname);
          setInfo(`Selected: ${keyname}`);
          return;
        }
      }
      // Empty-space click clears the selection.
      useModelStore.getState().selectItem(null, null);
      setInfo("Selection cleared");
    };
    renderer.domElement.addEventListener("click", handleClick);

    return () => {
      cancelAnimationFrame(animId);
      resizeObs.disconnect();
      renderer.domElement.removeEventListener("click", handleClick);
      renderer.dispose();
    };
  }, []);

  // ---------- frame cache + prefetch ----------
  // Cache of decoded MNF positions (one entry per frame).  Using a Map to
  // preserve LRU order via delete-then-set.
  const MNF_CACHE_MAX = 200;
  const mnfCacheRef = useRef<Map<number, Map<string, MnfFramePart>>>(new Map());
  const rigidCacheRef = useRef<Map<number, { name: string; position: number[]; phi: number[] }[]>>(new Map());
  const inflightMnfRef = useRef<Map<number, Promise<Map<string, MnfFramePart>>>>(new Map());
  const inflightRigidRef = useRef<Map<number, Promise<{ name: string; position: number[]; phi: number[] }[]>>>(new Map());

  const getMnfFrame = useCallback(async (frame: number): Promise<Map<string, MnfFramePart>> => {
    const cache = mnfCacheRef.current;
    const hit = cache.get(frame);
    if (hit) {
      // Refresh LRU
      cache.delete(frame);
      cache.set(frame, hit);
      return hit;
    }
    const pending = inflightMnfRef.current.get(frame);
    if (pending) return pending;
    const p = fetchAllMnfPositionsBin(frame)
      .then((m) => {
        cache.set(frame, m);
        while (cache.size > MNF_CACHE_MAX) {
          const firstKey = cache.keys().next().value;
          if (firstKey === undefined) break;
          cache.delete(firstKey);
        }
        return m;
      })
      .finally(() => {
        inflightMnfRef.current.delete(frame);
      });
    inflightMnfRef.current.set(frame, p);
    return p;
  }, []);

  const getRigidFrame = useCallback(async (frame: number) => {
    const cache = rigidCacheRef.current;
    const hit = cache.get(frame);
    if (hit) return hit;
    const pending = inflightRigidRef.current.get(frame);
    if (pending) return pending;
    const p = fetchRigidTransforms(frame)
      .then((r) => {
        cache.set(frame, r.items as any);
        if (cache.size > 600) {
          const firstKey = cache.keys().next().value;
          if (firstKey !== undefined) cache.delete(firstKey);
        }
        return r.items as any;
      })
      .finally(() => {
        inflightRigidRef.current.delete(frame);
      });
    inflightRigidRef.current.set(frame, p);
    return p;
  }, []);

  const clearFrameCaches = useCallback(() => {
    mnfCacheRef.current.clear();
    rigidCacheRef.current.clear();
    inflightMnfRef.current.clear();
    inflightRigidRef.current.clear();
  }, []);

  // Kick off ahead-of-time fetches for a small window of future frames.
  const prefetchAhead = useCallback((frame: number, ahead = 4) => {
    const state = useAnimationStore.getState();
    const max = state.frameCount;
    if (max === 0) return;
    for (let k = 1; k <= ahead; k++) {
      const f = frame + k;
      if (f >= max) break;
      if (!mnfCacheRef.current.has(f) && !inflightMnfRef.current.has(f)) {
        getMnfFrame(f).catch(() => {});
      }
      if (!rigidCacheRef.current.has(f) && !inflightRigidRef.current.has(f)) {
        getRigidFrame(f).catch(() => {});
      }
    }
  }, [getMnfFrame, getRigidFrame]);

  // ---------- loadScene (serialized) ----------
  const sceneVersionRef = useRef<number>(0);
  const loadingPromiseRef = useRef<Promise<void> | null>(null);

  const loadSceneInternal = useCallback(async (): Promise<void> => {
    const refs = sceneRef.current;
    if (!refs) return;
    const { scene } = refs;
    sceneVersionRef.current += 1;
    const myVersion = sceneVersionRef.current;
    // Any existing cached frame data may belong to a different scene layout.
    clearFrameCaches();

    // Dispose existing meshes
    const old: THREE.Mesh[] = [];
    scene.traverse((o) => {
      if ((o as THREE.Mesh).isMesh) old.push(o as THREE.Mesh);
    });
    old.forEach((m) => {
      scene.remove(m);
      m.geometry?.dispose();
      (m.material as THREE.Material)?.dispose();
    });
    rigidMeshes.current.clear();
    mnfMeshes.current.clear();

    let items: SceneItem[] = [];
    let source = "tdy";
    try {
      const res = await fetch("/api/geometry/scene");
      const data = await res.json();
      items = data.items || [];
      source = data.source || "tdy";
    } catch {
      setInfo("No model loaded");
      return;
    }

    // If a newer load has started, abort
    if (myVersion !== sceneVersionRef.current) return;

    for (const item of items) {
      let geometry: THREE.BufferGeometry;
      const r = item.radius ?? 0.05;
      const h = item.height ?? 0.5;

      if (item.mesh && item.mesh.positions.length > 0) {
        geometry = new THREE.BufferGeometry();
        const pos = new Float32Array(item.mesh.positions);
        const norm = new Float32Array(item.mesh.normals);
        const idx = new Uint32Array(item.mesh.indices);
        geometry.setAttribute("position", new THREE.BufferAttribute(pos, 3));
        geometry.setAttribute("normal", new THREE.BufferAttribute(norm, 3));
        geometry.setIndex(new THREE.BufferAttribute(idx, 1));
      } else if (item.geometry === "none") {
        continue; // skip emit
      } else {
        switch (item.geometry) {
          case "sphere":
            geometry = new THREE.SphereGeometry(r, 16, 12);
            break;
          case "cylinder":
            geometry = new THREE.CylinderGeometry(r, r, h, 20);
            break;
          case "marker":
            geometry = new THREE.SphereGeometry(0.02, 8, 6);
            break;
          default:
            geometry = new THREE.BoxGeometry(r * 2, r * 2, r * 2);
        }
      }

      const rgb = item.color || [128, 128, 128];
      const color = new THREE.Color(rgb[0] / 255, rgb[1] / 255, rgb[2] / 255);

      const isMnf = item.category === "MNF_PART";
      const material = new THREE.MeshPhongMaterial({
        color,
        side: THREE.DoubleSide,
        shininess: 18,
        specular: new THREE.Color(0x222222),
        // MNF parts update their `position` attribute every frame without
        // touching `normal`, so the stored normals become stale after a
        // rotation.  `flatShading` makes the fragment shader derive normals
        // from screen-space derivatives, which is always correct and free.
        flatShading: isMnf,
      });

      const mesh = new THREE.Mesh(geometry, material);
      const p = item.position || [0, 0, 0];
      mesh.position.set(p[0], p[1], p[2]);

      if (item.phi && (item.phi[0] !== 0 || item.phi[1] !== 0 || item.phi[2] !== 0)) {
        mesh.quaternion.copy(phiToQuaternion(item.phi));
      }

      mesh.userData = {
        itemId: item.id,
        keyname: item.keyname,
        category: item.category,
        partName: item.part_name || item.keyname,
      };
      scene.add(mesh);

      if (source === "results") {
        if (item.category === "RIGID_PART") {
          rigidMeshes.current.set(item.keyname, mesh);
        } else if (item.category === "MNF_PART") {
          mnfMeshes.current.set(item.keyname, mesh);
        }
      }
    }

    if (myVersion !== sceneVersionRef.current) return;

    // Auto-fit camera to the full scene bbox (not just one MNF part).
    const box = new THREE.Box3();
    scene.children.forEach((c) => {
      if ((c as THREE.Mesh).isMesh) box.expandByObject(c);
    });
    if (!box.isEmpty()) {
      const center = box.getCenter(new THREE.Vector3());
      const size = box.getSize(new THREE.Vector3());
      const maxDim = Math.max(size.x, size.y, size.z);
      const dist = maxDim * 1.6;
      refs.camera.position.set(
        center.x + dist * 0.7,
        center.y + dist * 0.4,
        center.z + dist * 0.7,
      );
      refs.controls.target.copy(center);
      refs.camera.near = Math.max(maxDim * 0.001, 0.001);
      refs.camera.far = Math.max(maxDim * 100, 100);
      refs.camera.updateProjectionMatrix();
      viewBoundsRef.current = { center: center.clone(), dist };
    }

    // Apply current visibility state
    applyVisibility();

    setInfo(`${items.length} objects (${source})`);
  }, []);

  const loadScene = useCallback((): Promise<void> => {
    // Serialize: if a load is in-flight, chain the next one after it.
    const prev = loadingPromiseRef.current ?? Promise.resolve();
    const next = prev.then(() => loadSceneInternal()).catch(() => {});
    loadingPromiseRef.current = next;
    return next;
  }, [loadSceneInternal]);

  // ---------- visibility sync ----------
  const applyVisibility = useCallback(() => {
    const hidden = useVisibilityStore.getState().hiddenKeys;
    const refs = sceneRef.current;
    if (!refs) return;
    refs.scene.traverse((o) => {
      const m = o as THREE.Mesh;
      if (!m.isMesh) return;
      const kn: string | undefined = m.userData?.partName || m.userData?.keyname;
      if (!kn) return;
      m.visible = !hidden.has(kn.toUpperCase());
    });
  }, []);

  useEffect(() => {
    applyVisibility();
  }, [visVersion, applyVisibility]);

  // ---------- Space key hide/show ----------
  useEffect(() => {
    const handler = (e: KeyboardEvent) => {
      if (e.code !== "Space") return;
      // Skip if focus is in an input / textarea
      const target = e.target as HTMLElement | null;
      const tag = (target?.tagName || "").toLowerCase();
      if (tag === "input" || tag === "textarea" || tag === "select") return;
      const key = useModelStore.getState().selectedKeyname;
      if (!key) return;
      e.preventDefault();
      useVisibilityStore.getState().toggle(key);
    };
    window.addEventListener("keydown", handler);
    return () => window.removeEventListener("keydown", handler);
  }, []);

  // Populate the stores from current backend status.  Used on mount so the
  // frontend picks up an already-open result set after a page reload.
  const syncFromBackend = useCallback(async () => {
    try {
      const status = await fetchResultStatus();
      if (!status.loaded) return false;
      // Pull the tree that the backend already has in-memory too.
      try {
        const treeRes = await fetch("/api/model/tree");
        if (treeRes.ok) {
          const tree = await treeRes.json();
          useModelStore.getState().setTree(tree);
        }
      } catch {
        /* ignore */
      }
      const frames = await fetchFrames();
      const topo = await fetchTopo();
      setAnimLoaded({
        frameCount: status.frame_count ?? frames.frame_count,
        times: frames.times,
        mnfParts: topo.mnf.map((p) => p.name),
      });
      setResultsStatus(
        `loaded: ${status.frame_count} frames, ${status.mnf_parts} MNF parts`,
      );
      return true;
    } catch {
      return false;
    }
  }, [setAnimLoaded]);

  // On initial mount, probe the backend status.  This covers the case where
  // the server already has a result set open (page refresh, backend restart
  // with existing state) so the TimelinePanel isn't stuck at "no results".
  const syncedRef = useRef(false);
  useEffect(() => {
    if (syncedRef.current) return;
    syncedRef.current = true;
    syncFromBackend();
  }, [syncFromBackend]);

  // ---------- loadcase open handler ----------
  // Opens a whole loadcase directory: parses main.tdy → tree + editor,
  // opens result/ subdir → animation state.  One round trip.
  const setTreeFn = useModelStore((s) => s.setTree);
  const setFilePathFn = useModelStore((s) => s.setFilePath);
  const setTdySourceFn = useModelStore((s) => s.setTdySource);

  const handleOpenLoadcase = useCallback(
    async (loadcaseDir: string) => {
      try {
        setResultsStatus("loading...");
        const info = await openLoadcase(loadcaseDir);
        // 1) Drive the model tree + TDY editor
        setTreeFn(info.tree);
        setFilePathFn(info.tdy_path);
        setTdySourceFn(info.tdy_text, info.tdy_path);
        // 2) Results are optional — only set animation state if they loaded
        if (info.result.loaded && info.result.frame_count) {
          const frames = await fetchFrames();
          const topo = await fetchTopo();
          setAnimLoaded({
            frameCount: info.result.frame_count,
            times: frames.times,
            mnfParts: topo.mnf.map((p) => p.name),
          });
          setResultsStatus(
            `${info.tdy_filename} · ${info.result.frame_count} frames · ${info.result.mnf_parts ?? 0} MNF parts`,
          );
        } else {
          setResultsStatus(
            info.result.error
              ? `${info.tdy_filename} · result error: ${info.result.error}`
              : `${info.tdy_filename} (no result/ subdir)`,
          );
        }
      } catch (err: any) {
        setResultsStatus(`error: ${err?.message || err}`);
      }
    },
    [setAnimLoaded, setTreeFn, setFilePathFn, setTdySourceFn],
  );

  // ---------- per-frame update (serialized) ----------
  // We serialize through a single running promise — every requested frame is
  // actually rendered, in order.  For interactive scrubbing we use a separate
  // "coalesce to latest" path.
  const currentRenderRef = useRef<Promise<void>>(Promise.resolve());
  const latestRequestRef = useRef<number>(-1);
  const lastRenderedFrameRef = useRef<number>(-1);

  const performUpdate = useCallback(async (frame: number): Promise<void> => {
    const refs = sceneRef.current;
    if (!refs) return;
    const state = useAnimationStore.getState();
    if (!state.loaded) return;
    const startVersion = sceneVersionRef.current;
    const partsKey = state.activeMnfParts.join(",");
    const key = `${frame}|${partsKey}|${state.colorField}`;
    try {
      // Cached / in-flight aware — these return instantly on cache hit.
      const [rigidItems, positionsByName] = await Promise.all([
        getRigidFrame(frame).catch(() => [] as any[]),
        getMnfFrame(frame).catch(() => new Map<string, MnfFramePart>()),
      ]);
      if (sceneVersionRef.current !== startVersion) return;

      for (const entry of rigidItems) {
        const mesh = rigidMeshes.current.get(entry.name);
        if (!mesh) continue;
        mesh.position.set(entry.position[0], entry.position[1], entry.position[2]);
        mesh.quaternion.copy(phiToQuaternion(entry.phi));
      }

      positionsByName.forEach((payload, name) => {
        const mesh = mnfMeshes.current.get(name);
        if (!mesh) return;
        const posAttr = mesh.geometry.getAttribute("position") as THREE.BufferAttribute;
        if (!posAttr || posAttr.array.length !== payload.positions.length) return;
        (posAttr.array as Float32Array).set(payload.positions);
        posAttr.needsUpdate = true;
        // flatShading derives normals in the fragment shader, so we don't
        // need to touch the normal attribute.
      });

      // Kick off prefetch of upcoming frames (no await).
      prefetchAhead(frame, 6);

      // Multi-part Mises stress coloring
      const activeParts = state.activeMnfParts;
      const wantMises = state.colorField === "mises";
      const newLegends: LegendBlock[] = [];

      // First clear mises color on any MNF mesh NOT in activeParts
      mnfMeshes.current.forEach((mesh, name) => {
        if (activeParts.includes(name)) return;
        if (mesh.geometry.getAttribute("color")) {
          mesh.geometry.deleteAttribute("color");
          const mat = mesh.material as THREE.MeshPhongMaterial;
          mat.vertexColors = false;
          mat.needsUpdate = true;
        }
      });

      if (wantMises && activeParts.length > 0) {
        // Fetch mises for each active part in parallel
        const results = await Promise.all(
          activeParts.map((p) =>
            fetchMnfFrame(frame, p, "mises").catch(() => null),
          ),
        );
        if (sceneVersionRef.current !== startVersion) return;

        // Compute global range across all active parts
        let gMin = Infinity, gMax = -Infinity;
        for (const data of results) {
          if (!data || !data.mises) continue;
          const mn = data.mises_min ?? Math.min(...data.mises);
          const mx = data.mises_max ?? Math.max(...data.mises);
          if (mn < gMin) gMin = mn;
          if (mx > gMax) gMax = mx;
        }
        if (!(gMax - gMin > 1e-12)) {
          gMin = 0; gMax = 1;
        }
        const rng = gMax - gMin;

        for (let i = 0; i < activeParts.length; i++) {
          const part = activeParts[i];
          const data = results[i];
          const mesh = mnfMeshes.current.get(part);
          if (!mesh || !data || !data.mises) continue;
          const mises = data.mises;
          const colors = new Float32Array(mises.length * 3);
          const degenerate = !(rng > 1e-12);
          for (let j = 0; j < mises.length; j++) {
            const t = degenerate ? 0 : (mises[j] - gMin) / rng;
            if (degenerate) {
              colors[j * 3] = 120 / 255;
              colors[j * 3 + 1] = 180 / 255;
              colors[j * 3 + 2] = 230 / 255;
              continue;
            }
            const [r, g, b] = viridis(t);
            colors[j * 3] = r;
            colors[j * 3 + 1] = g;
            colors[j * 3 + 2] = b;
          }
          mesh.geometry.setAttribute("color", new THREE.BufferAttribute(colors, 3));
          const mat = mesh.material as THREE.MeshPhongMaterial;
          mat.vertexColors = true;
          mat.color.set(0xffffff);
          mat.needsUpdate = true;
        }

        // One legend using the global range
        const entries: LegendEntry[] = [];
        for (let i = 0; i <= 10; i++) {
          const t = i / 10;
          const value = gMin + t * rng;
          const [r, g, b] = viridis(t);
          entries.push({
            value,
            color: [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)],
          });
        }
        newLegends.push({
          title: `Mises [Pa]: ${activeParts.join(", ")}`,
          entries,
        });
      }

      setLegends(newLegends);

      lastRenderedFrameRef.current = frame;
      const node = document.querySelector("[data-scene-ready]");
      if (node) node.setAttribute("data-scene-ready", key);
    } catch {
      /* ignore transient render errors */
    }
  }, [getMnfFrame, getRigidFrame, prefetchAhead]);

  // Scrub / state-change path: when the user drags the slider or toggles the
  // color field, coalesce to the latest requested frame (OK to drop stale
  // intermediate frames here).
  const requestRender = useCallback((frame: number) => {
    latestRequestRef.current = frame;
    currentRenderRef.current = currentRenderRef.current
      .then(async () => {
        // If newer frames arrived while we were queued, coalesce to the
        // latest — but only when NOT playing.  The playback loop runs its
        // own sequential dispatch below.
        const state = useAnimationStore.getState();
        const target = state.isPlaying ? frame : latestRequestRef.current;
        if (lastRenderedFrameRef.current === target) return;
        await performUpdate(target);
      })
      .catch(() => {});
    return currentRenderRef.current;
  }, [performUpdate]);

  // Trigger a render whenever non-playback state changes.
  useEffect(() => {
    if (!animLoaded) return;
    requestRender(currentFrame);
  }, [animLoaded, currentFrame, activeMnfParts, colorField, requestRender]);

  // Playback loop — lives here (not in TimelinePanel) so it can advance
  // only after the previous frame is actually applied to the GPU.  This
  // guarantees every frame is shown; the playback wall-clock naturally
  // matches whatever throughput the fetch+render pipeline can sustain.
  const isPlaying = useAnimationStore((s) => s.isPlaying);
  const playbackFps = useAnimationStore((s) => s.playbackFps);
  useEffect(() => {
    if (!animLoaded || !isPlaying) return;
    let cancelled = false;

    const run = async () => {
      while (!cancelled) {
        const state = useAnimationStore.getState();
        if (!state.isPlaying) return;
        const frame = state.currentFrame;
        if (frame >= state.frameCount - 1) {
          state.setPlaying(false);
          state.setFrame(0);
          return;
        }
        // Render the CURRENT frame fully before advancing.
        await performUpdate(frame);
        if (cancelled) return;
        // Target frame period — we may already have exceeded it if the
        // fetch+render was slow, in which case we skip the wait.
        const stepSec = 1 / Math.max(1, playbackFps);
        const waitMs = Math.max(0, stepSec * 1000 - 2);
        if (waitMs > 0) {
          await new Promise((r) => setTimeout(r, waitMs));
        }
        if (cancelled) return;
        useAnimationStore.getState().setFrame(frame + 1);
      }
    };
    run();
    return () => {
      cancelled = true;
    };
  }, [animLoaded, isPlaying, playbackFps, performUpdate]);

  // Load scene when model tree changes OR when animation just loaded.
  useEffect(() => {
    if (!tree) return;
    loadScene().then(() => {
      if (useAnimationStore.getState().loaded) {
        requestRender(useAnimationStore.getState().currentFrame);
      }
    });
  }, [tree, loadScene, requestRender]);

  useEffect(() => {
    if (!animLoaded) return;
    loadScene().then(() => {
      requestRender(useAnimationStore.getState().currentFrame);
    });
  }, [animLoaded, loadScene, requestRender]);

  // Expose helpers for Playwright / DevTools
  useEffect(() => {
    (window as any).__openLoadcase = handleOpenLoadcase;
    (window as any).__openResults = handleOpenLoadcase; // back-compat
    (window as any).__animStore = useAnimationStore;
    (window as any).__visStore = useVisibilityStore;
    (window as any).__modelStore = useModelStore;
    (window as any).__sceneRef = sceneRef;
    (window as any).__rigidMeshes = rigidMeshes;
    (window as any).__mnfMeshes = mnfMeshes;
    return () => {
      delete (window as any).__openLoadcase;
      delete (window as any).__openResults;
      delete (window as any).__animStore;
      delete (window as any).__visStore;
      delete (window as any).__modelStore;
      delete (window as any).__sceneRef;
      delete (window as any).__rigidMeshes;
      delete (window as any).__mnfMeshes;
    };
  }, [handleOpenLoadcase]);

  // Highlight selected mesh with emissive outline (subtle)
  useEffect(() => {
    const refs = sceneRef.current;
    if (!refs) return;
    refs.scene.traverse((o) => {
      const m = o as THREE.Mesh;
      if (!m.isMesh) return;
      const mat = m.material as THREE.MeshPhongMaterial;
      if (!mat || typeof mat.emissive === "undefined") return;
      const kn: string | undefined = m.userData?.partName || m.userData?.keyname;
      if (kn && selectedKeyname && kn.toUpperCase() === selectedKeyname.toUpperCase()) {
        mat.emissive.setRGB(0.3, 0.25, 0.0);
      } else {
        mat.emissive.setRGB(0, 0, 0);
      }
      mat.needsUpdate = true;
    });
  }, [selectedKeyname]);

  return (
    <div
      style={{ position: "relative", width: "100%", height: "100%", background: "var(--scene-bg)" }}
      data-scene-ready="-1"
      tabIndex={0}
    >
      <div ref={canvasRef} style={{ width: "100%", height: "100%" }} />
      <div
        style={{
          position: "absolute",
          bottom: 54,
          left: 8,
          color: "var(--text-secondary)",
          fontSize: 11,
          pointerEvents: "none",
        }}
      >
        {info} · {resultsStatus}
      </div>
      <div style={{ position: "absolute", top: 4, right: 4, display: "flex", gap: 4 }}>
        <button
          style={btnStyle}
          onClick={() => {
            const dir = prompt(
              "Loadcase directory (contains main.tdy and result/):",
              "E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined",
            );
            if (dir) handleOpenLoadcase(dir);
          }}
          data-testid="load-results"
        >
          Load Loadcase
        </button>
        <button style={btnStyle} onClick={() => loadScene()}>
          Refresh
        </button>
        <button
          style={btnStyle}
          onClick={() => useVisibilityStore.getState().reset()}
          title="Show all hidden parts"
        >
          Show All
        </button>
        <button
          style={btnStyle}
          onClick={() => {
            if (sceneRef.current) {
              const bounds = viewBoundsRef.current;
              if (bounds) {
                const { center, dist } = bounds;
                sceneRef.current.camera.position.set(
                  center.x + dist * 0.7,
                  center.y + dist * 0.4,
                  center.z + dist * 0.7,
                );
                sceneRef.current.controls.target.copy(center);
              } else {
                sceneRef.current.camera.position.set(2, 1.5, 2);
                sceneRef.current.controls.target.set(0, 0, 0);
              }
            }
          }}
        >
          Reset View
        </button>
      </div>
      {legends.map((lb, i) => (
        <div key={i} style={{ position: "absolute", top: 40 + i * 180, right: 4 }}>
          <ContourLegend entries={lb.entries} title={lb.title} />
        </div>
      ))}
      <TimelinePanel />
    </div>
  );
}

const btnStyle: React.CSSProperties = {
  padding: "2px 8px",
  background: "rgba(45,45,48,0.85)",
  color: "#ccc",
  border: "1px solid #555",
  borderRadius: 3,
  cursor: "pointer",
  fontSize: 11,
};
