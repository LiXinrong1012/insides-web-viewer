"""Tests for TDY parser, expression evaluator, and model builder."""

import math

from server.parsers.expression_parser import ExpressionParser, TDYParameters
from server.parsers.model_builder import ModelBuilder
from server.parsers.tdy_ast import AssemblyItem, KeyValueItem, LineItem
from server.parsers.tdy_parser import TDYParser


# --- Expression Parser Tests ---

class TestExpressionParser:
    def test_number(self):
        ep = ExpressionParser()
        assert ep.evaluate("42") == 42.0
        assert ep.evaluate("3.14") == 3.14
        assert ep.evaluate("1e-6") == 1e-6

    def test_arithmetic(self):
        ep = ExpressionParser()
        assert ep.evaluate("2 + 3") == 5.0
        assert ep.evaluate("10 - 4") == 6.0
        assert ep.evaluate("3 * 4") == 12.0
        assert ep.evaluate("10 / 4") == 2.5

    def test_precedence(self):
        ep = ExpressionParser()
        assert ep.evaluate("2 + 3 * 4") == 14.0
        assert ep.evaluate("(2 + 3) * 4") == 20.0

    def test_power(self):
        ep = ExpressionParser()
        assert ep.evaluate("2 ^ 3") == 8.0
        assert ep.evaluate("0.02 ^ 3") == 0.02 ** 3

    def test_unary_minus(self):
        ep = ExpressionParser()
        assert ep.evaluate("-5") == -5.0
        assert ep.evaluate("-2 + 3") == 1.0

    def test_variables(self):
        ep = ExpressionParser({"L": 1.0, "N_ELEM": 20.0})
        assert ep.evaluate("L / N_ELEM") == 0.05
        assert ep.evaluate("L * 2") == 2.0

    def test_functions(self):
        ep = ExpressionParser()
        assert abs(ep.evaluate("SIN(0)")) < 1e-10
        assert abs(ep.evaluate("COS(0)") - 1.0) < 1e-10
        assert abs(ep.evaluate("SQRT(4)") - 2.0) < 1e-10
        assert abs(ep.evaluate("ABS(-5)") - 5.0) < 1e-10

    def test_quoted_string(self):
        ep = ExpressionParser({"L": 1.0, "N": 20.0})
        assert ep.evaluate('"L/N"') == 0.05

    def test_complex_expression(self):
        ep = ExpressionParser({"b": 0.02, "h": 0.02})
        result = ep.evaluate("b * h ^ 3 / 12")
        expected = 0.02 * (0.02 ** 3) / 12
        assert abs(result - expected) < 1e-15


# --- TDYParameters Tests ---

class TestTDYParameters:
    def test_add_and_get(self):
        params = TDYParameters()
        params.add("L", "1.0")
        params.add("N", "20")
        assert params.has_key("L")
        assert params.get_value("L") == 1.0
        assert params.get_value("N") == 20.0

    def test_expression_evaluation(self):
        params = TDYParameters()
        params.add("L", "1.0")
        params.add("N_ELEM", "20")
        params.add("dx", '"L/N_ELEM"')
        val = params.get_value("dx")
        assert val is not None
        assert abs(val - 0.05) < 1e-10

    def test_recursive_resolution(self):
        params = TDYParameters()
        params.add("a", "2")
        params.add("b", "3")
        params.add("c", '"a + b"')
        assert params.get_value("c") == 5.0


# --- TDY Parser Tests ---

class TestTDYParser:
    def test_simple_keyword(self):
        parser = TDYParser()
        root = parser.parse("PARAMETER / 1\n, L = 1.0\n, N = 20\n")
        assert len(root.children) == 1
        item = root.children[0]
        assert item.keyname == "PARAMETER"
        assert item.main_id == "1"
        kv_l = item.get_keyvalue("L")
        assert kv_l is not None
        assert kv_l.values == ["1.0"]
        kv_n = item.get_keyvalue("N")
        assert kv_n is not None
        assert kv_n.values == ["20"]

    def test_nested_block(self):
        tdy = """
FEMPART / BEAM {
    MATERIAL / 1, ISOELASTIC, E = 210e9, MU = 0.3
    FNODE6 / 1, QG = 0, 0, 0
    FNODE6 / 2, QG = 1, 0, 0
}
"""
        parser = TDYParser()
        root = parser.parse(tdy)
        assert len(root.children) == 1
        fem = root.children[0]
        assert isinstance(fem, AssemblyItem)
        assert fem.keyname == "FEMPART"
        assert fem.main_label == "BEAM"
        assert len(fem.children) == 3  # MATERIAL + 2 FNODE6

        mat = fem.children[0]
        assert mat.keyname == "MATERIAL"
        assert mat.main_id == "1"
        kv_e = mat.get_keyvalue("E")
        assert kv_e is not None
        assert kv_e.values == ["210e9"]

    def test_comments(self):
        tdy = """! This is a comment
PARAMETER / 1
, L = 1.0  ! inline comment
"""
        parser = TDYParser()
        root = parser.parse(tdy)
        assert len(root.children) == 1
        item = root.children[0]
        assert item.keyname == "PARAMETER"

    def test_block_comment(self):
        tdy = """/* block comment */
PARAMETER / 1, L = 1.0
"""
        parser = TDYParser()
        root = parser.parse(tdy)
        assert len(root.children) == 1

    def test_quoted_values(self):
        tdy = 'FNODE6 / 1, QG = "0*dx", 0, 0\n'
        parser = TDYParser()
        root = parser.parse(tdy)
        item = root.children[0]
        kv = item.get_keyvalue("QG")
        assert kv is not None
        assert kv.values[0] == '"0*dx"'
        assert kv.values[1] == "0"
        assert kv.values[2] == "0"

    def test_multiple_items(self):
        tdy = """
PARAMETER / 1, L = 1.0
INSTANCE / 1, INS_BEAM, PART = BEAM
MARKER / 1, MK_FIX, GROUND, NODE = 1
JOINT / 1, FIXED, I = INS_BEAM.MK_FIX, J = MK_GND
END
"""
        parser = TDYParser()
        root = parser.parse(tdy)
        assert len(root.children) == 4
        assert root.children[0].keyname == "PARAMETER"
        assert root.children[1].keyname == "INSTANCE"
        assert root.children[2].keyname == "MARKER"
        # GROUND is 3rd property; after extracting 1→mainID and MK_FIX→mainLabel, GROUND remains
        assert root.children[2].has_property("GROUND")
        assert root.children[3].keyname == "JOINT"
        # FIXED becomes mainLabel after ID extraction (1→mainID, FIXED→mainLabel)
        assert root.children[3].main_label == "FIXED"

    def test_properties(self):
        tdy = "JOINT / 1, FIXED, I = MK1, J = MK2\n"
        parser = TDYParser()
        root = parser.parse(tdy)
        joint = root.children[0]
        assert joint.keyname == "JOINT"
        assert joint.main_id == "1"
        # FIXED is extracted as main_label (second property after numeric ID)
        assert joint.main_label == "FIXED"

    def test_end_removed(self):
        tdy = "PARAMETER / 1, L = 1.0\nEND\n"
        parser = TDYParser()
        root = parser.parse(tdy)
        assert len(root.children) == 1


# --- Model Builder Tests ---

class TestModelBuilder:
    def test_basic_model(self):
        tdy = """
PARAMETER / 1
, L = 1.0
, N = 20

RIGIDPART / Body1 {
    RIGID6 / 1, MASS = 10, QG = 0, 0, 0
    MARKER / 1, MK_A, QG = 0, 0, 0
}

INSTANCE / 1, INS_Body1, PART = Body1
MARKER / 2, MK_GND, GROUND, QG = 0, 0, 0
JOINT / 1, FIXED, I = INS_Body1.MK_A, J = MK_GND
SFORCE / 1, I = INS_Body1.MK_A, J = MK_GND
REQUEST / 1
END
"""
        parser = TDYParser()
        ast_root = parser.parse(tdy)

        builder = ModelBuilder()
        assembly = builder.build(ast_root, "TestModel")

        assert assembly.keyname == "TestModel"

        # Check parameters
        params_folder = assembly.get_folder("Parameters")
        assert params_folder is not None
        assert len(params_folder.children) >= 1
        assert builder.parameters.has_key("L")
        assert builder.parameters.get_value("L") == 1.0

        # Check parts
        parts_folder = assembly.get_folder("Parts")
        assert parts_folder is not None
        assert len(parts_folder.children) == 1
        assert parts_folder.children[0].keyname == "Body1"

        # Check instances
        inst_folder = assembly.get_folder("Instances")
        assert inst_folder is not None
        assert len(inst_folder.children) == 1

        # Check constraints
        const_folder = assembly.get_folder("Constraints")
        assert const_folder is not None
        assert len(const_folder.children) == 1

        # Check loads
        loads_folder = assembly.get_folder("Loads")
        assert loads_folder is not None
        assert len(loads_folder.children) == 1

        # Check ground markers
        ground_folder = assembly.get_folder("Ground")
        assert ground_folder is not None
        assert len(ground_folder.children) >= 1

        # Check requests
        req_folder = assembly.get_folder("Requests")
        assert req_folder is not None
        assert len(req_folder.children) == 1

    def test_fem_part(self):
        tdy = """
FEMPART / Beam {
    MATERIAL / 1, ISOELASTIC, E = 210e9
    SECTION / 1, BEAM, A = 0.01
    FNODE6 / 1, QG = 0, 0, 0
    TBEAM / 1, N1 = 1, N2 = 2
}
"""
        parser = TDYParser()
        ast_root = parser.parse(tdy)
        builder = ModelBuilder()
        assembly = builder.build(ast_root)

        parts = assembly.get_folder("Parts")
        assert parts is not None
        assert len(parts.children) == 1
        fem = parts.children[0]
        assert fem.keyname == "Beam"
        # FEM part should have children (material, section, nodes, elements)
        assert len(fem.children) >= 4

    def test_nested_assembly(self):
        tdy = """
ASSEMBLY / SubAsm {
    RIGIDPART / Part1 {
        RIGID6 / 1, MASS = 5
    }
}
"""
        parser = TDYParser()
        ast_root = parser.parse(tdy)
        builder = ModelBuilder()
        assembly = builder.build(ast_root)

        asm_folder = assembly.get_folder("Assemblies")
        assert asm_folder is not None
        assert len(asm_folder.children) == 1
        sub = asm_folder.children[0]
        assert sub.keyname == "SubAsm"

    def test_contact(self):
        tdy = "CONTACT_RIGID_RIGID / 1, I = P1, J = P2\n"
        parser = TDYParser()
        ast_root = parser.parse(tdy)
        builder = ModelBuilder()
        assembly = builder.build(ast_root)

        contacts = assembly.get_folder("Contacts")
        assert contacts is not None
        assert len(contacts.children) == 1
