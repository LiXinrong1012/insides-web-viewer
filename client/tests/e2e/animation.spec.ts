import { expect, test } from "@playwright/test";
import path from "node:path";
import fs from "node:fs";
import { fileURLToPath } from "node:url";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const RESULT_DIR = "E:/zky2026_v2/loadcases/45DTPIASM/B_rot_combined/result";
const SCREENSHOT_DIR = path.resolve(__dirname, "screenshots");
const FRAMES_TO_CAPTURE = [0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 501];

test.beforeAll(() => {
  fs.mkdirSync(SCREENSHOT_DIR, { recursive: true });
});

test("MNF result animation — capture frames and verify playback", async ({ page }) => {
  page.on("console", (msg) => {
    const t = msg.type();
    if (t === "error" || t === "warning") {
      console.log(`[browser ${t}]`, msg.text());
    }
  });
  page.on("pageerror", (err) => console.log("[pageerror]", err.message));

  await page.goto("/");
  await page.waitForSelector("canvas", { timeout: 30_000 });

  // Open the result directory via the React-exposed window hook
  const openResult = await page.evaluate(async (dir) => {
    const fn = (window as any).__openResults;
    if (!fn) return { ok: false, error: "no __openResults hook" };
    try { await fn(dir); return { ok: true }; }
    catch (e: any) { return { ok: false, error: String(e?.message || e) }; }
  }, RESULT_DIR);
  expect(openResult.ok, openResult.error).toBe(true);

  await page.waitForFunction(
    () => {
      const store = (window as any).__animStore;
      return store && store.getState().loaded && store.getState().frameCount > 0;
    },
    null,
    { timeout: 60_000 },
  );

  const frameCount = await page.evaluate(
    () => (window as any).__animStore.getState().frameCount,
  );
  expect(frameCount).toBe(502);

  // Wait until the scene has rigid meshes loaded (previously the backend skipped BC_ADAPTER).
  await page.waitForFunction(
    () => {
      const rm = (window as any).__rigidMeshes;
      return rm && rm.current && rm.current.size >= 52;
    },
    null,
    { timeout: 60_000 },
  );

  // Enable Mises coloring via store
  await page.evaluate(() => (window as any).__animStore.getState().setColorField("mises"));

  const samplePositions: Record<number, number[]> = {};

  for (const targetIdx of FRAMES_TO_CAPTURE) {
    const idx = Math.min(targetIdx, frameCount - 1);
    await page.evaluate((i) => {
      (window as any).__animStore.getState().setFrame(i);
    }, idx);

    await page.waitForFunction(
      (expected) => {
        const el = document.querySelector("[data-scene-ready]");
        const v = el?.getAttribute("data-scene-ready") || "";
        return v.startsWith(expected + "|");
      },
      String(idx),
      { timeout: 45_000 },
    );
    await page.waitForTimeout(350);

    // Grab sample rigid body positions to verify motion
    const sample = await page.evaluate(() => {
      const rm = (window as any).__rigidMeshes?.current as Map<string, any> | undefined;
      if (!rm) return null;
      const pick = [
        "HEXAGON_SOCKET_BUTTON_HEAD_SCREWS_GB_BS_EN_ISO_7380_M12_X_20_20N_INS1",
      ];
      const out: Record<string, number[]> = {};
      for (const k of pick) {
        const m = rm.get(k);
        if (m) out[k] = [m.position.x, m.position.y, m.position.z];
      }
      return out;
    });

    const shot = path.join(SCREENSHOT_DIR, `frame_${String(idx).padStart(4, "0")}.png`);
    await page.screenshot({ path: shot, fullPage: false });
    const stat = fs.statSync(shot);
    expect(stat.size).toBeGreaterThan(5_000);

    console.log(`frame ${idx}:`, JSON.stringify(sample));
    const key = "HEXAGON_SOCKET_BUTTON_HEAD_SCREWS_GB_BS_EN_ISO_7380_M12_X_20_20N_INS1";
    if (sample && sample[key]) {
      samplePositions[idx] = sample[key];
    }
  }

  // Assert the screw moved across the captured frames.
  const samples = Object.values(samplePositions);
  expect(samples.length).toBeGreaterThan(1);
  let maxSpread = 0;
  for (let i = 1; i < samples.length; i++) {
    const dx = samples[i][0] - samples[0][0];
    const dy = samples[i][1] - samples[0][1];
    const d = Math.sqrt(dx * dx + dy * dy);
    if (d > maxSpread) maxSpread = d;
  }
  console.log("maxSpread over captured frames:", maxSpread);
  expect(maxSpread).toBeGreaterThan(0.01);
});
