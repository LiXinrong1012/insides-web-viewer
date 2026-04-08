import { defineConfig } from "@playwright/test";

/**
 * Spawns both the FastAPI backend and the Vite dev server, then runs E2E
 * screenshot tests against the live UI.  Running this requires the
 * `insides_web` conda env on PATH (or adjust BACKEND_CMD below).
 */
const PY =
  process.env.INSIDES_WEB_PYTHON ||
  "C:/Users/XinrongLI/.conda/envs/insides_web/python.exe";
const BACKEND_CMD =
  process.env.BACKEND_CMD ||
  `${PY} -m uvicorn server.main:app --port 8000`;

export default defineConfig({
  testDir: "./tests/e2e",
  timeout: 300_000,
  expect: { timeout: 15_000 },
  fullyParallel: false,
  workers: 1,
  retries: 0,
  reporter: [["list"]],
  use: {
    baseURL: "http://127.0.0.1:5173",
    viewport: { width: 1400, height: 900 },
    headless: true,
    trace: "retain-on-failure",
  },
  // Backend + dev server are expected to already be running (see scripts).
});
