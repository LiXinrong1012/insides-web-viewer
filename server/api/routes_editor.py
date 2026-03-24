"""Editor API: compile, validate, and get completions for TDY files."""

from typing import Any, Dict, List, Optional

from fastapi import APIRouter
from pydantic import BaseModel

from ..parsers.expression_parser import TDYParameters
from ..parsers.model_builder import ModelBuilder
from ..parsers.tdy_parser import TDYParser

router = APIRouter(prefix="/api/editor", tags=["editor"])

# TDY keywords for autocomplete (from the 73 registered keywords)
TDY_KEYWORDS = [
    "ASSEMBLY", "CONTACT_FEM_SHAPE", "CONTACT_FEM_SHAPE2", "CONTACT_FEM_SHAPE_MODI",
    "CONTACT_G2G", "CONTACT_G2G_FLEX", "CONTACT_G2G_MNF", "CONTACT_G2G_RIGID",
    "CONTACT_RIGID_RIGID", "CONTACT_SET_SHAPE", "CONTACT_SPH_RCT", "CONTACT_SPH_SPLINE",
    "CABLE", "EBEAM", "EXTERNAL", "FEMPART", "FIELD", "FLEXGEARPART",
    "FNODE3", "FNODE6", "FQUATNODE", "GFORCE", "GRAPHIC", "INCLUDE",
    "INSTANCE", "JOINT", "JOINT_GEAR", "MARKER", "MATERIAL", "MNFGEARPART",
    "MNFPART", "PARAMETER", "PLATE", "QUAD", "REQUEST", "RIGID6",
    "RIGIDGEAR6", "RIGIDGEARPART", "RIGIDPART", "SECTION", "SET",
    "SFORCE", "SFORCE_GEAR", "SHELL", "SLIDINGFRICTION7", "SLIDINGJOINT7",
    "SPRINGDAMPER", "TBEAM", "THELEN2003MUSCLE", "VBEAM", "VCABLE",
    "VFEMPART", "VFNODE3", "VFNODE6", "VFORCE", "VTORQUE", "BUSHING", "BEAMFORCE",
]

# Common key-value names
TDY_KEYVALUE_NAMES = [
    "A", "CENTER", "E", "EULER321G", "I", "IP", "IYY", "IZZ", "J",
    "MASS", "MU", "N1", "N2", "NODE", "OG", "OR", "PART", "PARA_NAME",
    "PARA_VALUE", "PHI", "QG", "QR", "RHO", "RM", "THETA", "THETAG",
    "VALID", "VG", "VR", "XAXIS", "YAXIS", "ZAXIS",
]

# Property flags
TDY_PROPERTIES = [
    "BEAM", "BOX", "BUSHING", "CABLE", "CONVEL", "CYLINDER", "CYLINDRICAL",
    "FIXED", "FLOATING", "GROUND", "HOOKE", "ISOELASTIC", "PLATE",
    "REVOLUTE", "SHELL", "SPHERE", "SPHERICAL", "STL", "TRANSLATIONAL",
]


class CompileRequest(BaseModel):
    text: str
    filename: str = "<editor>"


class CompileError(BaseModel):
    message: str
    row: int
    col: int
    severity: str = "error"


class CompileResponse(BaseModel):
    success: bool
    errors: List[CompileError]
    parameters: List[Dict[str, str]]
    item_count: int


@router.post("/compile", response_model=CompileResponse)
async def compile_tdy(req: CompileRequest):
    """Parse and validate TDY text, return errors and parameters."""
    parser = TDYParser(expand_include=False)
    ast_root = parser.parse(req.text, req.filename)

    builder = ModelBuilder()
    assembly = builder.build(ast_root)

    errors = [
        CompileError(message=e.message, row=e.loc.row, col=e.loc.col, severity=e.severity)
        for e in parser.errors
    ]

    params = [{"key": k, "value": v} for k, v in builder.parameters.items()]

    # Count total items
    def count_items(item: Any) -> int:
        n = 1
        for c in getattr(item, "children", []):
            n += count_items(c)
        return n

    return CompileResponse(
        success=len(errors) == 0,
        errors=errors,
        parameters=params,
        item_count=count_items(assembly),
    )


@router.get("/completions")
async def get_completions():
    """Return keyword, key-value, and property completions for the editor."""
    return {
        "keywords": TDY_KEYWORDS,
        "keyvalues": TDY_KEYVALUE_NAMES,
        "properties": TDY_PROPERTIES,
    }
