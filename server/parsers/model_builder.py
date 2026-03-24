"""Converts parsed TDY AST into BaseItem/Assembly model tree.

Mirrors importtdy2/ImportTDYImp.cpp and import_items.cpp.
Maps each TDY keyword to a handler that creates the appropriate BaseItem.
"""

from typing import Callable, Dict, List, Optional

from ..models.base_item import Assembly, BaseItem, ItemCategory
from .expression_parser import TDYParameters
from .tdy_ast import AssemblyItem as ASTAssembly
from .tdy_ast import KeyValueItem, LineItem

# Handler signature: (builder, ast_item, parent_model_item) -> None
Handler = Callable[["ModelBuilder", LineItem, BaseItem], None]


def _update_key_values(model_item: BaseItem, ast_item: LineItem) -> None:
    """Copy all key-value pairs from AST item to model item properties."""
    for kv in ast_item.key_values:
        if len(kv.values) == 1:
            model_item.properties[kv.keyname] = kv.values[0]
        elif len(kv.values) > 1:
            model_item.properties[kv.keyname] = kv.values
    # Also store properties as flags
    for prop in ast_item.properties:
        model_item.properties[prop.name] = True


# --- Handlers for each keyword type ---

def _handle_parameter(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """PARAMETER keyword → add parameters to TDYParameters store."""
    item = BaseItem(keyname=ast_item.main_label or ast_item.main_id or "Parameters", category=ItemCategory.PARAMETER)
    _update_key_values(item, ast_item)
    # Register all key-values as parameters
    for kv in ast_item.key_values:
        val = kv.values[0] if kv.values else ""
        builder.parameters.add_or_replace(kv.keyname, val)
    _add_to_folder(parent, "Parameters", item)


def _handle_assembly(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """ASSEMBLY keyword → create nested Assembly."""
    asm = Assembly(keyname=ast_item.main_label or ast_item.main_id or "Assembly")
    asm.category = ItemCategory.ASSEMBLY
    _update_key_values(asm, ast_item)
    _add_to_folder(parent, "Assemblies", asm)
    # Recursively process children
    if isinstance(ast_item, ASTAssembly):
        builder.process_children(ast_item, asm)


def _handle_rigid_part(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """RIGIDPART → create rigid part."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or ast_item.keyname,
        category=ItemCategory.RIGID_PART,
    )
    _update_key_values(item, ast_item)
    if isinstance(ast_item, ASTAssembly):
        # Process sub-items (RIGID6, MARKER, GRAPHIC, etc.)
        for child in ast_item.children:
            _process_part_child(builder, child, item)
    _add_to_folder(parent, "Parts", item)


def _handle_fem_part(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """FEMPART/VFEMPART/MNFPART → create FEM part."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or ast_item.keyname,
        category=ItemCategory.FEM_PART,
    )
    _update_key_values(item, ast_item)
    item.properties["_part_type"] = ast_item.keyname.upper()
    if isinstance(ast_item, ASTAssembly):
        for child in ast_item.children:
            _process_part_child(builder, child, item)
    _add_to_folder(parent, "Parts", item)


def _process_part_child(builder: "ModelBuilder", ast_item: LineItem, part: BaseItem) -> None:
    """Process children of a part (nodes, elements, materials, etc.)."""
    kw = ast_item.keyname.upper()
    child = BaseItem(keyname=ast_item.main_label or ast_item.main_id or kw)

    # Set category based on keyword
    if kw in ("FNODE6", "FNODE3", "VFNODE3", "VFNODE6", "FQUATNODE"):
        child.category = ItemCategory.MARKER
        child.properties["_node_type"] = kw
    elif kw in ("TBEAM", "EBEAM", "QUAD", "SHELL", "PLATE", "CABLE", "VCABLE", "VBEAM"):
        child.category = ItemCategory.SET
        child.properties["_element_type"] = kw
    elif kw in ("MATERIAL", "SECTION"):
        child.category = ItemCategory.PARAMETER
    elif kw == "RIGID6" or kw == "RIGIDGEAR6":
        child.category = ItemCategory.PARAMETER
    elif kw == "MARKER":
        child.category = ItemCategory.MARKER
    elif kw == "GRAPHIC":
        child.category = ItemCategory.SHAPE
        # Detect shape type from main_label or remaining properties
        shape_types = {"BOX", "CYLINDER", "SPHERE", "STL"}
        if ast_item.main_label and ast_item.main_label.upper() in shape_types:
            child.properties["_shape_type"] = ast_item.main_label.upper()
        else:
            for prop in ast_item.properties:
                if prop.name.upper() in shape_types:
                    child.properties["_shape_type"] = prop.name.upper()
                    break
    else:
        child.category = ItemCategory.UNKNOWN

    _update_key_values(child, ast_item)
    part.add_child(child)


def _handle_instance(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """INSTANCE → create instance reference."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or "Instance",
        category=ItemCategory.INSTANCE,
    )
    _update_key_values(item, ast_item)
    _add_to_folder(parent, "Instances", item)


def _handle_marker(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """MARKER → create marker (may be GROUND)."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or "Marker",
        category=ItemCategory.MARKER,
    )
    _update_key_values(item, ast_item)
    is_ground = ast_item.has_property("GROUND")
    if is_ground:
        item.properties["_is_ground"] = True
        _add_to_folder(parent, "Ground", item)
    else:
        _add_to_folder(parent, "Markers", item)


def _handle_joint(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """JOINT → create constraint."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or "Joint",
        category=ItemCategory.JOINT,
    )
    _update_key_values(item, ast_item)
    # Joint type comes from main_label (e.g., FIXED, CYLINDRICAL, HOOKE)
    if ast_item.main_label and not ast_item.main_label.isdigit():
        item.properties["_joint_type"] = ast_item.main_label
    # Also check remaining properties
    for prop in ast_item.properties:
        item.properties["_joint_type"] = prop.name
        break
    _add_to_folder(parent, "Constraints", item)


def _handle_load(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """SPRINGDAMPER/SFORCE/VFORCE/etc. → create load."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or ast_item.keyname,
        category=ItemCategory.LOAD,
    )
    _update_key_values(item, ast_item)
    item.properties["_load_type"] = ast_item.keyname.upper()
    _add_to_folder(parent, "Loads", item)


def _handle_contact(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """CONTACT_* → create contact."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or ast_item.keyname,
        category=ItemCategory.CONTACT,
    )
    _update_key_values(item, ast_item)
    item.properties["_contact_type"] = ast_item.keyname.upper()
    _add_to_folder(parent, "Contacts", item)


def _handle_request(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """REQUEST → create output request."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or "Request",
        category=ItemCategory.REQUEST,
    )
    _update_key_values(item, ast_item)
    _add_to_folder(parent, "Requests", item)


def _handle_set(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """SET → create node/element set."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or "Set",
        category=ItemCategory.SET,
    )
    _update_key_values(item, ast_item)
    _add_to_folder(parent, "Sets", item)


def _handle_graphic(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """GRAPHIC → create shape."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or "Graphic",
        category=ItemCategory.SHAPE,
    )
    _update_key_values(item, ast_item)
    # Determine shape type from main_label or remaining properties
    shape_types = {"BOX", "CYLINDER", "SPHERE", "STL"}
    if ast_item.main_label and ast_item.main_label.upper() in shape_types:
        item.properties["_shape_type"] = ast_item.main_label.upper()
    else:
        for prop in ast_item.properties:
            if prop.name.upper() in shape_types:
                item.properties["_shape_type"] = prop.name.upper()
                break
    parent.add_child(item)


def _handle_external(builder: "ModelBuilder", ast_item: LineItem, parent: BaseItem) -> None:
    """EXTERNAL → external assembly reference."""
    item = BaseItem(
        keyname=ast_item.main_label or ast_item.main_id or "External",
        category=ItemCategory.ASSEMBLY,
    )
    _update_key_values(item, ast_item)
    _add_to_folder(parent, "Assemblies", item)


def _add_to_folder(parent: BaseItem, folder_name: str, item: BaseItem) -> None:
    """Add item to a named folder within parent (create folder if needed)."""
    if isinstance(parent, Assembly):
        folder = parent.get_folder(folder_name)
        if folder is not None:
            folder.add_child(item)
            return
    # Fallback: add directly to parent
    parent.add_child(item)


# --- Keyword → handler mapping (73 keywords) ---

_KEYWORD_HANDLERS: Dict[str, Handler] = {}


def _register(keywords: List[str], handler: Handler) -> None:
    for kw in keywords:
        _KEYWORD_HANDLERS[kw.upper()] = handler


# Part types
_register(["RIGIDPART", "RIGIDGEARPART"], _handle_rigid_part)
_register(["FEMPART", "VFEMPART", "MNFPART", "MNFGEARPART", "FLEXGEARPART"], _handle_fem_part)

# Assembly/Instance
_register(["ASSEMBLY"], _handle_assembly)
_register(["EXTERNAL"], _handle_external)
_register(["INSTANCE"], _handle_instance)

# Parameters
_register(["PARAMETER", "INTPAR"], _handle_parameter)

# Geometry
_register(["MARKER"], _handle_marker)
_register(["GRAPHIC"], _handle_graphic)

# Queries/Sets
_register(["REQUEST", "OUTPUT_REQUEST"], _handle_request)
_register(["SET"], _handle_set)

# Constraints
_register(["JOINT", "JOINT_GEAR", "SLIDINGJOINT7"], _handle_joint)

# Loads
_register([
    "SPRINGDAMPER", "SFORCE", "SFORCE_GEAR", "VFORCE", "GFORCE",
    "VTORQUE", "BUSHING", "BEAMFORCE", "CONTACT_SPH_RCT", "FIELD",
    "CONTACT_SPH_SPLINE", "SLIDINGFRICTION7", "THELEN2003MUSCLE",
    "MOTION",
], _handle_load)

# Contacts
_register([
    "CONTACT_RIGID_RIGID", "CONTACT_G2G_RIGID", "CONTACT_FEM_SHAPE",
    "CONTACT_FEM_SHAPE2", "CONTACT_SET_SHAPE", "CONTACT_FEM_SHAPE_MODI",
    "CONTACT_G2G", "CONTACT_G2G_MNF", "CONTACT_G2G_FLEX",
], _handle_contact)

# Part internals (RIGID6, FEM nodes/elements) — handled within parts
_register(["RIGID6", "RIGIDGEAR6"], _handle_parameter)


class ModelBuilder:
    """Converts parsed AST into model tree."""

    def __init__(self) -> None:
        self.parameters = TDYParameters()
        self.errors: List[str] = []

    def build(self, ast_root: ASTAssembly, model_name: str = "Model") -> Assembly:
        """Build a model Assembly from a parsed AST root."""
        assembly = Assembly.create_default(model_name)
        self.process_children(ast_root, assembly)
        return assembly

    def process_children(self, ast_parent: ASTAssembly, model_parent: BaseItem) -> None:
        """Walk AST children and dispatch to handlers."""
        for child in ast_parent.children:
            kw = child.keyname.upper()
            handler = _KEYWORD_HANDLERS.get(kw)
            if handler is not None:
                handler(self, child, model_parent)
            elif kw and kw not in ("END",):
                # Unknown keyword — store as generic item
                item = BaseItem(
                    keyname=child.main_label or child.main_id or kw,
                    category=ItemCategory.UNKNOWN,
                )
                _update_key_values(item, child)
                model_parent.add_child(item)
