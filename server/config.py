from pathlib import Path
from typing import List

from pydantic_settings import BaseSettings


class Settings(BaseSettings):
    app_name: str = "INSIDES Web Viewer"
    debug: bool = False

    # Paths
    upload_dir: Path = Path("uploads")
    solver_bin: Path = Path(
        r"D:\__insides_dev\insides_drill\out\build\x64-Release\src\INSIDES\thudynamics.exe"
    )
    mkl_dll_dir: Path = Path(r"D:\__insides_dev\insides_all_platform\bin\win64")

    # Server
    host: str = "0.0.0.0"
    port: int = 8000
    cors_origins: List[str] = ["http://localhost:5173"]

    model_config = {"env_prefix": "INSIDES_"}


settings = Settings()
