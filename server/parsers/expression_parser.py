"""Mathematical expression parser for TDY parameter evaluation.

Mirrors preparameter/expressionparser.h and preparameter/Parameter.h.

Grammar:
    expr    : term (('+' | '-') term)*
    term    : power (('*' | '/') power)*
    power   : unary ('^' unary)*
    unary   : '-' unary | primary
    primary : NUMBER | NAME | NAME '(' args ')' | '(' expr ')'
    args    : expr (',' expr)*
"""

import math
import re
from typing import Callable, Dict, List, Optional, Union

# Built-in functions
_BUILTINS: Dict[str, Callable] = {
    "SIN": lambda x: math.sin(x),
    "COS": lambda x: math.cos(x),
    "TAN": lambda x: math.tan(x),
    "ASIN": lambda x: math.asin(x),
    "ACOS": lambda x: math.acos(x),
    "ATAN": lambda x: math.atan(x),
    "ATAN2": lambda y, x: math.atan2(y, x),
    "ABS": lambda x: abs(x),
    "SQRT": lambda x: math.sqrt(x),
    "EXP": lambda x: math.exp(x),
    "LOG": lambda x: math.log(x),
    "LOG10": lambda x: math.log10(x),
    "MAX": lambda *a: max(a),
    "MIN": lambda *a: min(a),
    "PI": lambda: math.pi,
    "STEP": lambda x, x0, h0, x1, h1: h0 + (h1 - h0) * max(0.0, min(1.0, (x - x0) / (x1 - x0))) if x1 != x0 else h1,
}

# Token types
_TK_NUMBER = "NUMBER"
_TK_NAME = "NAME"
_TK_OP = "OP"
_TK_LPAREN = "("
_TK_RPAREN = ")"
_TK_COMMA = ","
_TK_EOF = "EOF"

_TOKEN_RE = re.compile(
    r"""
    (?P<NUMBER>[0-9]*\.?[0-9]+(?:[eE][+-]?[0-9]+)?) |
    (?P<NAME>[a-zA-Z_][a-zA-Z0-9_]*) |
    (?P<OP>[+\-*/^]) |
    (?P<LPAREN>\() |
    (?P<RPAREN>\)) |
    (?P<COMMA>,) |
    (?P<WS>\s+)
    """,
    re.VERBOSE,
)


class ExpressionError(Exception):
    pass


class _Tokenizer:
    def __init__(self, text: str) -> None:
        self.tokens: List[tuple] = []
        self.pos = 0
        for m in _TOKEN_RE.finditer(text):
            if m.lastgroup == "WS":
                continue
            if m.lastgroup == "NUMBER":
                self.tokens.append((_TK_NUMBER, float(m.group())))
            elif m.lastgroup == "NAME":
                self.tokens.append((_TK_NAME, m.group()))
            elif m.lastgroup == "OP":
                self.tokens.append((_TK_OP, m.group()))
            elif m.lastgroup == "LPAREN":
                self.tokens.append((_TK_LPAREN, "("))
            elif m.lastgroup == "RPAREN":
                self.tokens.append((_TK_RPAREN, ")"))
            elif m.lastgroup == "COMMA":
                self.tokens.append((_TK_COMMA, ","))
        self.tokens.append((_TK_EOF, None))

    def peek(self) -> tuple:
        return self.tokens[self.pos]

    def advance(self) -> tuple:
        tok = self.tokens[self.pos]
        if self.pos < len(self.tokens) - 1:
            self.pos += 1
        return tok

    def expect(self, kind: str) -> tuple:
        tok = self.advance()
        if tok[0] != kind:
            raise ExpressionError(f"Expected {kind}, got {tok}")
        return tok


class ExpressionParser:
    """Evaluates mathematical expressions with variable substitution."""

    def __init__(self, variables: Optional[Dict[str, float]] = None) -> None:
        self.variables: Dict[str, float] = variables or {}

    def evaluate(self, text: str) -> float:
        """Evaluate an expression string to a float."""
        # Strip surrounding quotes if present
        text = text.strip()
        if text.startswith('"') and text.endswith('"'):
            text = text[1:-1]
        if not text:
            return 0.0

        # Try direct numeric
        try:
            return float(text)
        except ValueError:
            pass

        tokenizer = _Tokenizer(text)
        result = self._expr(tokenizer)

        # Check we consumed everything
        if tokenizer.peek()[0] != _TK_EOF:
            raise ExpressionError(f"Unexpected token: {tokenizer.peek()}")

        return result

    def _expr(self, t: _Tokenizer) -> float:
        """expr : term (('+' | '-') term)*"""
        left = self._term(t)
        while t.peek() == (_TK_OP, "+") or t.peek() == (_TK_OP, "-"):
            op = t.advance()[1]
            right = self._term(t)
            if op == "+":
                left += right
            else:
                left -= right
        return left

    def _term(self, t: _Tokenizer) -> float:
        """term : power (('*' | '/') power)*"""
        left = self._power(t)
        while t.peek() == (_TK_OP, "*") or t.peek() == (_TK_OP, "/"):
            op = t.advance()[1]
            right = self._power(t)
            if op == "*":
                left *= right
            else:
                if right == 0:
                    raise ExpressionError("Division by zero")
                left /= right
        return left

    def _power(self, t: _Tokenizer) -> float:
        """power : unary ('^' unary)*"""
        base = self._unary(t)
        while t.peek() == (_TK_OP, "^"):
            t.advance()
            exp = self._unary(t)
            base = base ** exp
        return base

    def _unary(self, t: _Tokenizer) -> float:
        """unary : '-' unary | primary"""
        if t.peek() == (_TK_OP, "-"):
            t.advance()
            return -self._unary(t)
        if t.peek() == (_TK_OP, "+"):
            t.advance()
            return self._unary(t)
        return self._primary(t)

    def _primary(self, t: _Tokenizer) -> float:
        """primary : NUMBER | NAME | NAME '(' args ')' | '(' expr ')'"""
        tok = t.peek()

        if tok[0] == _TK_NUMBER:
            t.advance()
            return tok[1]

        if tok[0] == _TK_NAME:
            t.advance()
            name = tok[1]

            # Function call
            if t.peek()[0] == _TK_LPAREN:
                t.advance()  # consume (
                args: List[float] = []
                if t.peek()[0] != _TK_RPAREN:
                    args.append(self._expr(t))
                    while t.peek()[0] == _TK_COMMA:
                        t.advance()
                        args.append(self._expr(t))
                t.expect(_TK_RPAREN)

                func = _BUILTINS.get(name.upper())
                if func is not None:
                    return func(*args)
                raise ExpressionError(f"Unknown function: {name}")

            # Zero-arg builtin (like PI)
            func = _BUILTINS.get(name.upper())
            if func is not None:
                try:
                    return func()
                except TypeError:
                    pass

            # Variable lookup (case-insensitive)
            name_upper = name.upper()
            # Try with $ prefix stripped
            lookup_name = name_upper.lstrip("$")
            for var_name, var_val in self.variables.items():
                if var_name.upper() == lookup_name:
                    return var_val
            raise ExpressionError(f"Unknown variable: {name}")

        if tok[0] == _TK_LPAREN:
            t.advance()
            result = self._expr(t)
            t.expect(_TK_RPAREN)
            return result

        raise ExpressionError(f"Unexpected token: {tok}")


class TDYParameters:
    """Parameter store with expression evaluation.

    Mirrors pretdy/TDYParameters.h.
    """

    def __init__(self) -> None:
        self._params: Dict[str, str] = {}  # keyname → raw string value
        self._cache: Dict[str, float] = {}  # keyname → evaluated value

    def add(self, keyname: str, value: str) -> None:
        self._params[keyname] = value
        self._cache.pop(keyname, None)

    def add_or_replace(self, keyname: str, value: str) -> None:
        self._params[keyname] = value
        self._cache.pop(keyname, None)

    def has_key(self, keyname: str) -> bool:
        return keyname in self._params

    def get_raw(self, keyname: str) -> Optional[str]:
        return self._params.get(keyname)

    def get_value(self, expr_str: str) -> Optional[float]:
        """Evaluate expression string with all parameters as variables."""
        # Build variable map from cached values
        variables: Dict[str, float] = {}
        for key in self._params:
            val = self._resolve(key, set())
            if val is not None:
                variables[key] = val

        parser = ExpressionParser(variables)
        try:
            return parser.evaluate(expr_str)
        except ExpressionError:
            return None

    def _resolve(self, keyname: str, visited: set) -> Optional[float]:
        """Recursively resolve a parameter value."""
        if keyname in self._cache:
            return self._cache[keyname]
        if keyname in visited:
            return None  # circular reference
        visited.add(keyname)

        raw = self._params.get(keyname)
        if raw is None:
            return None

        # Try direct numeric
        try:
            val = float(raw.strip().strip('"'))
            self._cache[keyname] = val
            return val
        except ValueError:
            pass

        # Need to evaluate — resolve dependencies first
        variables: Dict[str, float] = {}
        for dep_key in self._params:
            if dep_key != keyname:
                dep_val = self._resolve(dep_key, visited)
                if dep_val is not None:
                    variables[dep_key] = dep_val

        parser = ExpressionParser(variables)
        try:
            val = parser.evaluate(raw)
            self._cache[keyname] = val
            return val
        except ExpressionError:
            return None

    @property
    def count(self) -> int:
        return len(self._params)

    def items(self) -> List[tuple]:
        return list(self._params.items())
