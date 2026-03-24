#pragma once
#include "expression.h"
#pragma warning( disable : 4290 )

// All these functions contain tricks to simplify the operands. This
// means that both the operands may be changed, and indeed that the
// return value is often one of the changed operands.  To make sure
// you are not changing the operands, use the CopyOf function or the
// Copy() method in Pointer class; or use the equivalent operators below
// in order not to touch the argument expressions.

/* 6个基本数学函数 */
// these are equivalent to the above but they don't change the arguments
Expression operator ^ (Expression a, Expression b);
// add a link of b to a, return link to created expression
Expression SumLink(Expression a, Expression b) throw(ErrNotPermitted);
// add a link of b to a with coeff -1, return link of a
Expression DifferenceLink(Expression a, Expression b)throw(ErrNotPermitted);
// multiply a by a link of b, return link of a
Expression ProductLink(Expression a, Expression b)throw(ErrNotPermitted);
// divide a by a link of b, return link of a
Expression FractionLink(Expression a, Expression b) throw(ErrDivideByZero);
// raise a to power b, return link of a
Expression PowerLink(Expression a, Expression b) throw(ErrNotPermitted);
// change sign to coeff of a, return link of a
Expression MinusLink(Expression a) throw(ErrNotPermitted);