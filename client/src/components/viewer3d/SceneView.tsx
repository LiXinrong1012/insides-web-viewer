import { useEffect, useRef, useCallback, useState } from "react";
import * as THREE from "three";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";
import { useModelStore } from "../../store";
import ContourLegend from "./ContourLegend";

interface SceneItem {
  id: number;
  keyname: string;
  category: string;
  position: number[];
  phi?: number[];  // Rodriguez rotation vector
  geometry: string;
  radius?: number;
  height?: number;
  color?: number[];
  mesh?: {
    positions: number[];
    normals: number[];
    indices: number[];
  };
}

/** Convert Rodriguez rotation vector to Three.js Quaternion.
 *  phi = [px, py, pz] where magnitude = angle (radians), direction = axis.
 */
function phiToQuaternion(phi: number[]): THREE.Quaternion {
  const px = phi[0], py = phi[1], pz = phi[2];
  const angle = Math.sqrt(px * px + py * py + pz * pz);
  if (angle < 1e-10) {
    return new THREE.Quaternion(); // identity
  }
  const axis = new THREE.Vector3(px / angle, py / angle, pz / angle);
  return new THREE.Quaternion().setFromAxisAngle(axis, angle);
}

export default function SceneView() {
  const canvasRef = useRef<HTMLDivElement>(null);
  const sceneRef = useRef<{
    scene: THREE.Scene;
    camera: THREE.PerspectiveCamera;
    renderer: THREE.WebGLRenderer;
    controls: OrbitControls;
  } | null>(null);
  const viewBoundsRef = useRef<{ center: THREE.Vector3; dist: number } | null>(null);
  const [info, setInfo] = useState("Ready");
  const [contour, setContour] = useState<{ entries: any[]; title: string } | null>(null);
  const [femPartIds, setFemPartIds] = useState<number[]>([]);
  const tree = useModelStore((s) => s.tree);

  // Initialize scene
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

    scene.add(new THREE.AmbientLight(0x404040, 0.8));
    const dir1 = new THREE.DirectionalLight(0xffffff, 0.9);
    dir1.position.set(5, 10, 7);
    scene.add(dir1);
    const dir2 = new THREE.DirectionalLight(0x8888ff, 0.3);
    dir2.position.set(-5, -3, -5);
    scene.add(dir2);

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
      camera.aspect = nw / nh;
      camera.updateProjectionMatrix();
      renderer.setSize(nw, nh);
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
      const meshes = scene.children.filter((c): c is THREE.Mesh => (c as THREE.Mesh).isMesh);
      const hits = raycaster.intersectObjects(meshes);
      if (hits.length > 0) {
        const ud = hits[0].object.userData;
        if (ud?.itemId) {
          useModelStore.getState().selectItem(ud.itemId);
          setInfo(`Selected: ${ud.keyname || ud.itemId}`);
        }
      }
    };
    renderer.domElement.addEventListener("click", handleClick);

    return () => {
      cancelAnimationFrame(animId);
      resizeObs.disconnect();
      renderer.domElement.removeEventListener("click", handleClick);
      renderer.dispose();
    };
  }, []);

  // Load scene when tree changes
  const loadScene = useCallback(async () => {
    const refs = sceneRef.current;
    if (!refs) return;
    const { scene } = refs;

    // Remove old meshes
    const old = scene.children.filter((c): c is THREE.Mesh => (c as THREE.Mesh).isMesh);
    old.forEach((m) => { scene.remove(m); m.geometry?.dispose(); (m.material as THREE.Material)?.dispose(); });

    try {
      const res = await fetch("/api/geometry/scene");
      const data = await res.json();
      const items: SceneItem[] = data.items || [];

      for (const item of items) {
        let geometry: THREE.BufferGeometry;
        const r = item.radius ?? 0.05;
        const h = item.height ?? 0.5;

        if (item.mesh && item.mesh.positions.length > 0) {
          // Buffer geometry from mesh data (STL or FEM)
          geometry = new THREE.BufferGeometry();
          const pos = new Float32Array(item.mesh.positions);
          const norm = new Float32Array(item.mesh.normals);
          const idx = new Uint32Array(item.mesh.indices);
          geometry.setAttribute("position", new THREE.BufferAttribute(pos, 3));
          geometry.setAttribute("normal", new THREE.BufferAttribute(norm, 3));
          geometry.setIndex(new THREE.BufferAttribute(idx, 1));
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

        const material = item.mesh
          ? new THREE.MeshPhongMaterial({
              color,
              side: THREE.DoubleSide,
              shininess: 40,
            })
          : new THREE.MeshPhongMaterial({
              color,
              transparent: item.category === "MARKER",
              opacity: item.category === "MARKER" ? 0.5 : 1.0,
              shininess: 60,
            });

        const mesh = new THREE.Mesh(geometry, material);
        const p = item.position || [0, 0, 0];
        // TDY uses X,Y,Z directly (no axis swap needed)
        mesh.position.set(p[0], p[1], p[2]);

        // Apply Rodriguez rotation from PHI vector
        if (item.phi && (item.phi[0] !== 0 || item.phi[1] !== 0 || item.phi[2] !== 0)) {
          mesh.quaternion.copy(phiToQuaternion(item.phi));
        }

        mesh.userData = { itemId: item.id, keyname: item.keyname };
        scene.add(mesh);
      }

      const femIds = items.filter(i => i.category === "FEM_PART" && i.mesh).map(i => i.id);
      setFemPartIds(femIds);

      // Auto-fit camera to scene bounds
      const box = new THREE.Box3();
      scene.children.forEach((c) => {
        if ((c as THREE.Mesh).isMesh) box.expandByObject(c);
      });
      if (!box.isEmpty()) {
        const center = box.getCenter(new THREE.Vector3());
        const size = box.getSize(new THREE.Vector3());
        const maxDim = Math.max(size.x, size.y, size.z);
        const dist = maxDim * 1.5;
        refs.camera.position.set(
          center.x + dist * 0.6,
          center.y + dist * 0.5,
          center.z + dist * 0.6
        );
        refs.controls.target.copy(center);
        refs.camera.near = Math.max(maxDim * 0.001, 0.001);
        refs.camera.far = Math.max(maxDim * 100, 100);
        refs.camera.updateProjectionMatrix();
        viewBoundsRef.current = { center: center.clone(), dist };
      }

      setInfo(`${items.length} objects`);
    } catch {
      setInfo("No model loaded");
    }
  }, []);

  const applyContour = useCallback(async (itemId: number, mode: number = 7) => {
    const refs = sceneRef.current;
    if (!refs) return;
    try {
      const res = await fetch(`/api/geometry/contour/${itemId}?mode=${mode}&component=magnitude`);
      if (!res.ok) return;
      const data = await res.json();

      const mesh = refs.scene.children.find(
        (c) => (c as THREE.Mesh).userData?.itemId === itemId
      ) as THREE.Mesh | undefined;

      if (mesh && data.colors) {
        const colors = new Float32Array(data.colors);
        mesh.geometry.setAttribute("color", new THREE.BufferAttribute(colors, 3));
        const mat = mesh.material as THREE.MeshPhongMaterial;
        mat.vertexColors = true;
        mat.color.set(0xffffff);
        mat.needsUpdate = true;
      }
      setContour({ entries: data.legend, title: `Mode ${mode} Disp.` });
    } catch { /* silently fail */ }
  }, []);

  const clearContour = useCallback(() => {
    const refs = sceneRef.current;
    if (!refs) return;
    refs.scene.children.forEach((c) => {
      const m = c as THREE.Mesh;
      if (m.isMesh && m.geometry?.getAttribute("color")) {
        m.geometry.deleteAttribute("color");
        const mat = m.material as THREE.MeshPhongMaterial;
        mat.vertexColors = false;
        mat.needsUpdate = true;
      }
    });
    setContour(null);
  }, []);

  useEffect(() => {
    if (tree) loadScene();
  }, [tree, loadScene]);

  return (
    <div style={{ position: "relative", width: "100%", height: "100%", background: "var(--scene-bg)" }}>
      <div ref={canvasRef} style={{ width: "100%", height: "100%" }} />
      <div style={{ position: "absolute", bottom: 4, left: 8, color: "var(--text-secondary)", fontSize: 11, pointerEvents: "none" }}>
        {info}
      </div>
      <div style={{ position: "absolute", top: 4, right: 4, display: "flex", gap: 4 }}>
        {femPartIds.length > 0 && (
          <>
            <button style={btnStyle} onClick={() => applyContour(femPartIds[0])}>
              Contour
            </button>
            {contour && (
              <button style={btnStyle} onClick={clearContour}>
                Clear
              </button>
            )}
          </>
        )}
        <button style={btnStyle} onClick={loadScene}>Refresh</button>
        <button style={btnStyle} onClick={() => {
          if (sceneRef.current) {
            const bounds = viewBoundsRef.current;
            if (bounds) {
              const { center, dist } = bounds;
              sceneRef.current.camera.position.set(
                center.x + dist * 0.6,
                center.y + dist * 0.5,
                center.z + dist * 0.6
              );
              sceneRef.current.controls.target.copy(center);
            } else {
              sceneRef.current.camera.position.set(2, 1.5, 2);
              sceneRef.current.controls.target.set(0, 0, 0);
            }
          }
        }}>Reset View</button>
      </div>
      {contour && <ContourLegend entries={contour.entries} title={contour.title} />}
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
