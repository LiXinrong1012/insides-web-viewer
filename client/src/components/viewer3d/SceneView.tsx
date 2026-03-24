import { useEffect, useRef, useCallback, useState } from "react";
import * as THREE from "three";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";
import { useModelStore } from "../../store";

interface SceneItem {
  id: number;
  keyname: string;
  category: string;
  position: number[];
  geometry: string;
  radius?: number;
  height?: number;
  color?: number[];
}

export default function SceneView() {
  const canvasRef = useRef<HTMLDivElement>(null);
  const sceneRef = useRef<{
    scene: THREE.Scene;
    camera: THREE.PerspectiveCamera;
    renderer: THREE.WebGLRenderer;
    controls: OrbitControls;
  } | null>(null);
  const [info, setInfo] = useState("Ready");
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

        const rgb = item.color || [128, 128, 128];
        const color = new THREE.Color(rgb[0] / 255, rgb[1] / 255, rgb[2] / 255);

        const material = new THREE.MeshPhongMaterial({
          color,
          transparent: item.category === "MARKER",
          opacity: item.category === "MARKER" ? 0.5 : 1.0,
          shininess: 60,
        });

        const mesh = new THREE.Mesh(geometry, material);
        const p = item.position || [0, 0, 0];
        mesh.position.set(p[0], p[2], -p[1]); // TDY: X,Y,Z → Three.js: X,Z,-Y
        mesh.userData = { itemId: item.id, keyname: item.keyname };
        scene.add(mesh);
      }
      setInfo(`${items.length} objects`);
    } catch {
      setInfo("No model loaded");
    }
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
        <button style={btnStyle} onClick={loadScene}>Refresh</button>
        <button style={btnStyle} onClick={() => {
          if (sceneRef.current) {
            sceneRef.current.camera.position.set(2, 1.5, 2);
            sceneRef.current.controls.target.set(0, 0, 0);
          }
        }}>Reset View</button>
      </div>
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
