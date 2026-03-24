#include "link.h"
#include <cmath>

/************** expression creation (no change to args) ***************/

// BIG FAT WARNING: when you change these operators, also please
// change their "-Link" counterparts!
// power:
Expression operator ^ (Expression a, Expression t) 
{
	// make a preliminary check
	Expression ret;
	if (a->GetCoeff() == 0)
	{
		// *this is zero, just return zero
		Expression zero(0.0);
		return zero;
	}

	if (t->HasValue(0.0))
	{
		// exponent is 0, just return 1
		Expression one(1.0);
		return one;
	} 
	else if (t->HasValue(1.0))
	{
		// exponent is 1, just return a
		ret.SetToCopyOf(a);
		return ret;
	} 

	if (a->HasValue(0.0))
	{
		// base is zero, return 0
		Expression zero(0.0);
		return zero;
	} 
	else if (a->HasValue(1.0)) 
	{
		// base is one, return 1
		Expression one(1.0);
		return one;
	}

	// go for it
	if (a->IsLeaf() && a->GetOpType() == OPT_CONST &&
		t->IsLeaf() && t->GetOpType() == OPT_CONST)
	{
		// constant to constant
		ret.SetToCopyOf(a);
		ret->SetValue(pow(ret->GetValue(), t->GetValue()));
		ret->SetCoeff(1);
		ret->SetExponent(1);
		return ret;
	}
	else if (a->IsLeaf() && a->GetOpType() == VAR &&
		t->IsLeaf() && t->GetOpType() == OPT_CONST) 
	{
		// variable to constant
		ret.SetToCopyOf(a);
		ret->SetExponent(ret->GetExponent() * t->GetValue());
		return ret;
	} 
	else 
	{
		ret->SetCoeff(1);
		ret->SetExponent(1);
		ret->SetOpType(POWER);
		ret->AddCopyOfNode(a);
		ret->AddCopyOfNode(t);
		return ret;
	}
}

/***************** expression creation (affects arguments) ***********/
// sums:
Expression SumLink(Expression a, Expression b) throw(ErrNotPermitted)
{
	if( a->IsPointer() || b->IsPointer() )
	{
		string varname ;
		if ( a->IsPointer() ) 
			varname = a->GetVarName() ;
		else if ( b->IsPointer() )
			varname = b->GetVarName() ;

		unsigned long mycode(0);
		string myif("unknown variable: " + varname);
		string myscope("SumLink");
		string myop("");
		string mydesc("");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}

	// make a preliminary check
	if (a->GetCoeff() == 0 || a->HasValue(0))
		return b;
	if (b->GetCoeff() == 0 || b->HasValue(0))
		return a;  
	if (!(a->IsConstant() && b->IsConstant()) && a->IsEqualToNoCoeff(b)) 
	{
		a->SetCoeff(a->GetCoeff() + b->GetCoeff());
		if (fabs(a->GetCoeff()) < Ev3NearZero())
		{
			// simplify to zero - for differences
			Expression zero(0.0);
			return zero;
		} else
			return a;
	}
	// go for it
	if (a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST)
	{
		// a, b are numbers - add them
		a->SetValue(a->GetValue() + b->GetValue());
		a->SetCoeff(1);
		a->SetExponent(1);
		return a;
	} 
	else if (a->IsLeaf() && a->GetOpType() == VAR &&
		b->IsLeaf() && b->GetOpType() == VAR &&
		a->GetVarIndex() == b->GetVarIndex() &&
		a->GetExponent() == b->GetExponent()) 
	{
		// a, b are the same variable - add coefficients
		a->SetCoeff(a->GetCoeff() + b->GetCoeff());
		return a;
	} 
	else if (a->GetOpType() == SUM && b->GetOpType() != SUM)
	{    
		// a is a sum and b isn't - just add the term b
		a->DistributeCoeffOverSum();
		Int i = 0;
		bool couldsimplify = false;
		Expression tmp;
		// if t is a leaf and there is a like leaf in this,
		// just add it to the value/coefficient
		if (b->IsLeaf() && b->GetOpType() == OPT_CONST) 
		{
			// b is a constant
			for (i = 0; i < a->GetSize(); i++) 
			{
				tmp = a->GetNode(i);
				if (tmp->IsLeaf() && tmp->GetOpType() == OPT_CONST)
				{
					tmp->SetValue(tmp->GetValue() + b->GetValue() / a->GetCoeff());
					tmp->SetCoeff(1);
					tmp->SetExponent(1); // NB: changing tmp should also change a
					couldsimplify = true;
					break;
				}
			}
		} 
		else if (b->GetOpType() == VAR)
		{
			// b is a variable
			for (i = 0; i < a->GetSize(); i++) 
			{
				if (a->GetNode(i)->IsLeaf() && a->GetNode(i)->GetOpType() == VAR &&
					b->GetVarIndex() == a->GetNode(i)->GetVarIndex() &&
					b->GetExponent() == a->GetNode(i)->GetExponent()) 
				{
					double tc = a->GetNode(i)->GetCoeff() + b->GetCoeff()/a->GetCoeff();
					// warning: tc could be zero, but it would be cumbersome
					// to simplify it here - do it in SimplifyConstant
					a->GetNode(i)->SetCoeff(tc);
					couldsimplify = true;
					break;
				}
			}
		} 
		else if (!b->IsLeaf()) 
		{
			// a is a sum, b is a nonleaf, look for a subnode of a similar to b
			for (i = 0; i < a->GetSize(); i++) 
			{
				if (a->GetNode(i)->IsEqualTo(b))
				{
					// found one, add coefficients - notice, as above, coeff could
					// be zero, but deal with that case in SimplifyConstant
					a->GetNode(i)->SetCoeff(a->GetNode(i)->GetCoeff() + b->GetCoeff());
					couldsimplify = true;
					break;
				}
			}
		}
		if (!couldsimplify) 
		{
			// either could not simplify in steps above, or b is an operator
			a->AddNode(b);
		}
		return a;
	} 
	else if (a->GetOpType() == SUM && b->GetOpType() == SUM)
	{    
		// a, b are sums - add terms of b to a
		b->DistributeCoeffOverSum();
		Int i = 0;
		int s = b->GetSize();
		for (i = 0; i < s; i++) 
		{
			a = SumLink(a, b->GetNode(i));
		}
		return a;
	} 
	else if (a->GetOpType() != SUM && b->GetOpType() == SUM)
	{
		// a is not a sum but b is - transform this into a sum
		b = SumLink(b, a);
		return b;
	} 
	else 
	{
		// all other cases - make new node on top of the addends
		Expression ret;
		ret->SetOpType(SUM);
		ret->SetCoeff(1);
		ret->SetExponent(1);
		ret->AddNode(a);
		ret->AddNode(b);
		return ret;
	}
}


// product
Expression ProductLink(Expression a, Expression t) throw(ErrNotPermitted)
{
	if( a->IsPointer() || t->IsPointer() )
	{
		string varname ;
		if ( a->IsPointer() ) 
			varname = a->GetVarName() ;
		else if ( t->IsPointer() )
			varname = t->GetVarName() ;

		unsigned long mycode(0);
		string myif("unknown variable: " + varname);
		string myscope("ProductLink");
		string myop("");
		string mydesc("");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}

	// make a preliminary check
	if (a->GetCoeff() == 0 || t->GetCoeff() == 0 || 
		a->HasValue(0) || t->HasValue(0)) 
	{
		Expression zero(0.0);
		return zero;
	}
	if (a->HasValue(1))
		return t;
	if (t->HasValue(1))
		return a; 
 	if (!(a->IsConstant() && t->IsConstant()) && a->IsEqualToNoCoeff(t))
 	{
 		Expression two(2.0);
 		a->SetCoeff(a->GetCoeff() * t->GetCoeff());
 		return a^two;
 	}

	// go for it
	if (a->GetOpType() == OPT_CONST && t->GetOpType() == OPT_CONST) 
	{
		// a, t are numbers - multiply them
		a->SetValue(a->GetValue() * t->GetValue());
		a->SetCoeff(1);
		a->SetExponent(1);
		return a;
	} 
	else if (a->IsLeaf() && a->GetOpType() == VAR &&
		t->IsLeaf() && t->GetOpType() == VAR &&
		a->GetVarIndex() == t->GetVarIndex()) 
	{
		// a, t are the same variable - multiply coefficients
		// and add exponents
		a->SetCoeff(a->GetCoeff() * t->GetCoeff());
		a->SetExponent(a->GetExponent() + t->GetExponent());
		return a;
	}
	else if (t->IsConstant())
	{
		// t is constant, set coeff of a
		a->SetCoeff(a->GetCoeff() * t->GetValue());
		a->DistributeCoeffOverSum();
		return a;
	} 
	else if (a->IsConstant()) 
	{
		// a is constant, set coeff of t
		t->SetCoeff(t->GetCoeff() * a->GetValue());
		t->DistributeCoeffOverSum();
		return t;
	} 
	else if (a->GetOpType() == PRODUCT && t->GetOpType() != PRODUCT)
	{
		// a is a product and t isn't - just multiply the term t
		Int i = 0;
		bool couldsimplify = false;
		if (t->IsLeaf() && t->GetOpType() == VAR)
		{
			// t is a variable
			Expression tmp;
			for (i = 0; i < a->GetSize(); i++) 
			{
				tmp = a->GetNode(i);
				if (tmp->IsLeaf() && tmp->GetOpType() == VAR &&
					t->GetVarIndex() == tmp->GetVarIndex())
				{
					// found same variable in a, multiply coeffs and add exponents
					tmp->SetCoeff(tmp->GetCoeff() * t->GetCoeff());	
					tmp->SetExponent(tmp->GetExponent() + t->GetExponent());
					couldsimplify = true;
					break;
				}
			}
		} 
		// here we shan't try to simplify f*f <-- f^2 (f nonleaf) 
		// because a product of nonleaves is easier to manipulate than 
		// a power (as it adds a depth level)
		if (!couldsimplify)
		{
			// either could not simplify in steps above, or t is an operator
			a->AddNode(t);
		}
		return a;
	} 
	else if (a->GetOpType() == PRODUCT && t->GetOpType() == PRODUCT) 
	{
		// a, t are products - multiply terms of t to a
		t->DistributeCoeffOverProduct();
		Int i = 0;
		Int s = t->GetSize();
		for (i = 0; i < s; i++) 
		{
			a = ProductLink(a, t->GetNode(i));
		}
		return a;
	} 
	else if (a->GetOpType() != PRODUCT && t->GetOpType() == PRODUCT) 
	{
		// a is not a products but t is - transform this into a product
		t = ProductLink(t, a);
		return t;
	} 
	else
	{
		// all other cases - make new node on top of the addends
		Expression ret;
		ret->SetCoeff(1);
		ret->SetExponent(1);
		ret->SetOpType(PRODUCT);
		ret->AddNode(a);
		ret->AddNode(t);
		return ret;
	}
}

// fractions:
Expression FractionLink(Expression a, Expression t) throw(ErrDivideByZero) 
{
	if( a->IsPointer() || t->IsPointer() )
	{
		string varname ;
		if ( a->IsPointer() ) 
			varname = a->GetVarName() ;
		else if ( t->IsPointer() )
			varname = t->GetVarName() ;

		unsigned long mycode(0);
		string myif("unknown variable: " + varname);
		string myscope("FractionLink");
		string myop("");
		string mydesc("");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// make a preliminary check
	if (t->GetCoeff() == 0) 
	{
		// divide by zero
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("FractionLink");
		string myop("t.GetCoeff()==0");
		string mydesc("Divisor cannot be zero");
		string myinfo(HELPURL);
		string mydiv(NONE);
		throw ErrDivideByZero(mycode,myif,myscope,myop,mydesc,myinfo,mydiv);
	}
	if (a->GetCoeff() == 0 || a->HasValue(0)) 
	{
		// dividend has zero coeff, return zero
		Expression zero(0.0);
		return zero;
	}
	if (t->HasValue(1))
		return a;
	if (!(a->IsConstant() && t->IsConstant()) && a->IsEqualToNoCoeff(t)) 
	{
		// dividend = divisor, return ratio of coefficients
		Expression one(1.0);
		one->SetCoeff(a->GetCoeff() / t->GetCoeff());
		return one;
	}
	// go for it
	if (a->GetOpType() == OPT_CONST && t->GetOpType() == OPT_CONST)
	{
		// a, t are numbers - divide them
		if (t->GetValue() == 0) {
			unsigned long mycode(0);
			string myif("Expression Building");
			string myscope("FractionLink");
			string myop("t.GetValue()==0");
			string mydesc("Divisor cannot be zero");
			string myinfo(HELPURL);
			string mydiv(NONE);
			throw ErrDivideByZero(mycode,myif,myscope,myop,mydesc,myinfo,mydiv);
		}
		else 
		{
			a->SetValue(a->GetValue() / t->GetValue());
			a->SetCoeff(1);
			a->SetExponent(1);
			return a;
		}
	} 
	else if (t->HasValue(1)) 
	{
		// divide by constant 1, don't do anything
		return a;
	} 
	else if (t->IsConstant())
	{
		// t is constant, set coeff of a
		a->SetCoeff(a->GetCoeff() / t->GetValue());
		a->DistributeCoeffOverSum();
		return a;
	}
	else if (a->IsVariable() && t->IsVariable() &&
		a->GetVarIndex() == t->GetVarIndex())
	{
		// cx^e / dx^f = (c/d)x^(e-f)
		double te = a->GetExponent() - t->GetExponent();
		double tc = a->GetCoeff() / t->GetCoeff();
		if (fabs(te) < Ev3NearZero()) 
		{
			Expression c(tc);
			return tc;
		}
		a->SetCoeff(tc);
		a->SetExponent(te);
		return a;
	} 
	else if (a->IsVariable() && t->GetOpType() == PRODUCT) 
	{
		// a is a variable, t is a product - see if a appears in t
		// and cancel common term
		// first simplify coeffs of divisor
		t->ConsolidateProductCoeffs();
		// denominator
		if (fabs(t->GetCoeff()) < Ev3NearZero()) 
		{
			// divide by zero
			unsigned long mycode(22);
			string myif("Expression Building");
			string myscope("FractionLink");
			string myop("t->GetCoeff()");
			string mydesc("Divisor cannot be zero");
			string myinfo(HELPURL);
			string mydiv(NONE);
			throw ErrDivideByZero(mycode,myif,myscope,myop,mydesc,myinfo,mydiv);
		}
		if (fabs(a->GetCoeff()) < Ev3NearZero())
		{
			Expression zero(0.0);
			return zero;
		}
		double accumulatedcoeff = a->GetCoeff() / t->GetCoeff();
		a->SetCoeff(1.0);
		t->SetCoeff(1.0);
		// now try simplification
		Int i;
		for (i = 0; i < t->GetSize(); i++)
		{
			if (t->GetNode(i)->GetOpType() == VAR && 
				a->GetVarIndex() == t->GetNode(i)->GetVarIndex())
			{
				double te = a->GetExponent() - t->GetNode(i)->GetExponent();
				if (fabs(te) < Ev3NearZero()) 
				{
					// exponents are the same, just cancel
					a->One();
					t->DeleteNode(i);
				} 
				else if (te > 0)
				{
					// numerator remains, cancel denominator
					a->SetExponent(te);
					t->DeleteNode(i);
				} 
				else if (te < 0)
				{
					// numerator goes to one, denominator remains
					a->One();
					t->GetNode(i)->SetExponent(-te);
				}
				// exit loop
				break;
			}
		}
		// check that denominator (t) has more than one operands;
		// if not, bring up a rank level
		if (t->GetSize() == 1)
		{
			t = t->GetNode(0);
		}
		// build ratio
		Expression ret;
		ret->SetOpType(FRACTION);
		ret->SetCoeff(accumulatedcoeff);
		ret->SetExponent(1);
		ret->AddNode(a);
		ret->AddNode(t);  
		return ret;
	} 
	else if (t->IsVariable() && a->GetOpType() == PRODUCT)
	{
		// t is a variable, a is a product - see if t appears in a
		// and cancel common term
		// first simplify coeffs of divisor
		a->ConsolidateProductCoeffs();
		// denominator - already checked
		if (fabs(a->GetCoeff()) < Ev3NearZero()) 
		{
			Expression zero(0.0);
			return zero;
		}
		double accumulatedcoeff = a->GetCoeff() / t->GetCoeff();
		a->SetCoeff(1.0);
		t->SetCoeff(1.0);
		// now try simplification
		Int i;
		for (i = 0; i < a->GetSize(); i++)
		{
			if (a->GetNode(i)->GetOpType() == VAR && 
				t->GetVarIndex() == a->GetNode(i)->GetVarIndex()) 
			{
				double te = a->GetNode(i)->GetExponent() - t->GetExponent();
				if (fabs(te) < Ev3NearZero()) 
				{
					// exponents are the same, just cancel
					t->One();
					a->DeleteNode(i);
				} 
				else if (te > 0)
				{
					// numerator remains, cancel denominator
					t->One();
					a->GetNode(i)->SetExponent(te);
				} 
				else if (te < 0) 
				{
					// numerator goes to one, denominator remains
					t->SetExponent(-te);
					a->DeleteNode(i);
				}
				// exit loop
				break;
			}
		}
		// check that numerator (a) has more than one operands;
		// if not, bring up a rank level
		if (a->GetSize() == 1)
		{
			a = a->GetNode(0);
		}
		// build ratio
		Expression ret;
		ret->SetOpType(FRACTION);
		ret->SetCoeff(accumulatedcoeff);
		ret->SetExponent(1);
		ret->AddNode(a);
		ret->AddNode(t);  
		return ret;
	} 
	else if (a->GetOpType() == PRODUCT && t->GetOpType() == PRODUCT)
	{
		// a, t are products, try to cancel common terms
		Int i = 0, j = 0;
		double accumulatedcoeff;
		// first simplify coefficients of operands
		a->ConsolidateProductCoeffs();
		t->ConsolidateProductCoeffs();
		// denominator
		if (fabs(t->GetCoeff()) < Ev3NearZero())
		{
			// divide by zero
			unsigned long mycode(21);
			string myif("Expression Building");
			string myscope("FractionLink");
			string myop("t->GetCoeff()");
			string mydesc("Divisor cannot be zero");
			string myinfo(HELPURL);
			string mydiv(NONE);
			throw ErrDivideByZero(mycode,myif,myscope,myop,mydesc,myinfo,mydiv);
		}
		if (fabs(a->GetCoeff()) < Ev3NearZero())
		{
			Expression zero(0.0);
			return zero;
		}
		// save ratio of coeffs of products
		accumulatedcoeff = a->GetCoeff() / t->GetCoeff();
		a->SetCoeff(1.0);
		t->SetCoeff(1.0);
		// now try simplification
		i = 0;
		bool isnumeratorempty = false;
		bool isdenominatorempty = false;
		int szi = a->GetSize();
		int szj = t->GetSize();
		while(!isnumeratorempty && !isdenominatorempty && i < szi)
		{
			j = 0;
			while(!isnumeratorempty && !isdenominatorempty && j < szj)
			{
				if (a->GetNode(i)->IsEqualTo(t->GetNode(j)))
				{
					// found like terms i and j
					a->DeleteNode(i);
					szi--;
					if(szi == 0)
					{
						isnumeratorempty = true;
						a->One();
					}
					t->DeleteNode(j);
					szj--;
					if (szj == 0)
					{
						isdenominatorempty = true;
						t->One();
					}
					i--;   // cancel the effect of the later i++
					break; // go to outer cycle
				}
				else
				{
					j++;
				}
			}	
			i++;
		}
		if (t->HasValue(1))
		{
			// denominator is 1, return a
			a->SetCoeff(accumulatedcoeff);
			return a;
		}
		// now construct fraction
		// check that numerator, denominator have more than one operands;
		// if not, bring up a rank level
		if (a->GetSize() == 1) 
		{
			a = a->GetNode(0);
		}
		if (t->GetSize() == 1)
		{
			t = t->GetNode(0);
		}
		Expression ret;
		ret->SetCoeff(accumulatedcoeff); // already contains coeffs of a, t
		ret->SetExponent(1);
		ret->SetOpType(FRACTION);
		ret->AddNode(a);
		ret->AddNode(t);
		return ret;
	} 
	else 
	{
		Expression ret;
		ret->SetCoeff(a->GetCoeff() / t->GetCoeff());
		a->SetCoeff(1);
		t->SetCoeff(1);
		ret->SetExponent(1);
		ret->SetOpType(FRACTION);
		ret->AddNode(a);
		ret->AddNode(t);
		return ret;
	}
}    

// unary minus:
Expression MinusLink(Expression a) throw(ErrNotPermitted)
{
	if( a->IsPointer()  )
	{
		string varname ;
		varname = a->GetVarName() ;

		unsigned long mycode(0);
		string myif("unknown variable: " + varname);
		string myscope("MinusLink");
		string myop("");
		string mydesc("");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}

	
	if (a->GetOpType() == OPT_CONST) 
	{
		a->SetValue(- a->GetValue());
		a->SetCoeff(1);
		a->SetExponent(1);    
	}
	else 
	{
		a->SetCoeff(- a->GetCoeff());
	}
	return a;
}

// binary minus:
Expression DifferenceLink(Expression a, Expression b) throw(ErrNotPermitted)
{
	if( a->IsPointer() || b->IsPointer() )
	{
		string varname ;
		if ( a->IsPointer() ) 
			varname = a->GetVarName() ;
		else if ( b->IsPointer() )
			varname = b->GetVarName() ;

		unsigned long mycode(0);
		string myif("unknown variable: " + varname);
		string myscope("DifferenceLink");
		string myop("");
		string mydesc("");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}

	if (a->HasValue(0))
		return MinusLink(b);
	if (b->HasValue(0))
		return a;
	return SumLink(a, MinusLink(b));
}

// power:
Expression PowerLink(Expression a, Expression t) throw(ErrNotPermitted)
{
	if( a->IsPointer() || t->IsPointer() )
	{
		string varname ;
		if ( a->IsPointer() ) 
			varname = a->GetVarName() ;
		else if ( t->IsPointer() )
			varname = t->GetVarName() ;

		unsigned long mycode(0);
		string myif("unknown variable: " + varname);
		string myscope("PowerLink");
		string myop("");
		string mydesc("");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
		
	
	// make a preliminary check
	if (a->GetCoeff() == 0) 
	{
		// *this is zero, just return zero
		Expression zero(0.0);
		return zero;
	}
	if (t->HasValue(0.0))
	{
		// exponent is 0, just return 1
		Expression one(1.0);
		return one;
	} else if (t->HasValue(1.0)) 
	{
		// exponent is 1, just return a
		return a;
	} 
	if (a->HasValue(0.0)) 
	{
		// base is zero, return 0
		Expression zero(0.0);
		return zero;
	} 
	else if (a->HasValue(1.0))
	{
		// base is one, return 1
		Expression one(1.0);
		return one;
	}
	// go for it
	if (a->GetOpType() == OPT_CONST && t->GetOpType() == OPT_CONST) 
	{
		// constant to constant
		a->SetValue(pow(a->GetValue(), t->GetValue()));
		a->SetCoeff(1);
		a->SetExponent(1);
		return a;
	} 
	else if (a->GetOpType() == VAR && t->GetOpType() == OPT_CONST) 
	{
		// variable to constant
		a->SetExponent(a->GetExponent() * t->GetValue());
		return a;
	}
	else 
	{
		Expression ret;
		ret->SetCoeff(1);
		ret->SetExponent(1);
		ret->SetOpType(POWER);
		ret->AddNode(a);
		ret->AddNode(t);
		return ret;
	}
}

// Expression LogLink(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("LogLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// make a preliminary check
// 	if (a->IsZero()) {
// 		// *this is zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("LogLink");
// 		string myop("IsZero()");
// 		string mydesc("log(0) is undefined");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if (a->GetValue() < 0) {
// 		// argument is < zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("LogLink");
// 		string myop("value <= 0");
// 		string mydesc("log(<=0) is undefined");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	} 
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		assert(t >= 0);
// 		a->SetCoeff(1);    
// 		a->SetValue(log(t));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(LOG);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression ExpLink(Expression a) throw(ErrNotPermitted){
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("ExpLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		a->SetCoeff(1);
// 		a->SetValue(exp(a->GetValue()));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(EXP);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression SinLink(Expression a) throw(ErrNotPermitted){
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("SinLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		a->SetCoeff(1);
// 		a->SetValue(sin(a->GetValue()));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(SIN);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression CosLink(Expression a) throw(ErrNotPermitted){
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("CosLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		a->SetCoeff(1);
// 		a->SetValue(cos(a->GetValue()));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(COS);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression TanLink(Expression a) throw(ErrNotPermitted){
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("TanLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	//没有检测给定的值是否接近pi/2
// 	if (a->GetOpType() == OPT_CONST) {
// 		a->SetCoeff(1);
// 		a->SetValue(tan(a->GetValue()));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(TAN);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression CotLink(Expression a)  throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("CotLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// make a preliminary check
// 	if (a->IsZero()) {
// 		// *this is zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("CotLink");
// 		string myop("IsZero()");
// 		string mydesc("cot(0) is undefined");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if ( a->GetOpType() == OPT_CONST) {
// 		double t = tan(a->GetValue());
// 		assert(t != 0);
// 		a->SetCoeff(1);
// 		a->SetValue(1 / t);
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(COT);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression SinhLink(Expression a) throw(ErrNotPermitted){
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("SinhLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		a->SetCoeff(1);
// 		a->SetValue(sinh(a->GetValue()));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(SINH);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression CoshLink(Expression a) throw(ErrNotPermitted){
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("CoshLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		a->SetCoeff(1);
// 		a->SetValue(cosh(a->GetValue()));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(COSH);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression TanhLink(Expression a) throw(ErrNotPermitted){
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("TanhLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		a->SetCoeff(1);
// 		a->SetValue(tanh(a->GetValue()));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(TANH);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression CothLink(Expression a)  throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("CothLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// make a preliminary check
// 	if (a->IsZero()) {
// 		// *this is zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("CothLink");
// 		string myop("IsZero()");
// 		string mydesc("coth(0) is undefined");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = tanh(a->GetValue());
// 		assert(t != 0);
// 		a->SetCoeff(1);
// 		a->SetValue(1 / t);
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(COTH);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression SqrtLink(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("SqrtLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// make a preliminary check
// 	if (a->GetValue() < 0 && !a->HasValue(0)) {
// 		// argument is < zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("SqrtLink");
// 		string myop("value < 0");
// 		string mydesc("sqrt(<0) is complex, can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	} 
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		assert(t >= 0);
// 		a->SetCoeff(1);
// 		a->SetValue(sqrt(t));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(SQRT);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression AsinLink(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AsinLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// make a preliminary check
// 	if (a->GetValue() <= -1|| a->GetValue() >= 1) {
// 		// argument is < zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AsinLink");
// 		string myop("value < -1 || value > 1");
// 		string mydesc("asin(<-1 || >1) can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	} 
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		a->SetCoeff(1);
// 		a->SetValue(asin(t));
// 		a->SetExponent(1);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(ASIN);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression AcosLink(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AcosLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// make a preliminary check
// 	if (a->GetValue() <= -1 || a->GetValue() >= 1) {
// 		// argument is < zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AcosLink");
// 		string myop("value < -1 || value > 1");
// 		string mydesc("acos(<-1 || >1) can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	} 
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		a->SetCoeff(1);
// 		a->SetValue(acos(t));
// 		a->SetExponent(1);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(ACOS);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression AtanLink(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AtanLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		a->SetCoeff(1);
// 		a->SetValue(atan(t));
// 		a->SetExponent(1);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(ATAN);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression SignLink(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("SignLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		a->SetCoeff(1);
// 		if(a->GetValue() == 0)
// 			a->SetValue(0);
// 		else if(a->GetValue() > 0)
// 			a->SetValue(1);
// 		else
// 			a->SetValue(-1);
// 		a->SetExponent(1);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(SIGN);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression Log10Link(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("Log10Link");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	// make a preliminary check
// 	if (a->IsZero()) {
// 		// *this is zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("Log10Link");
// 		string myop("IsZero()");
// 		string mydesc("log10(0) is undefined");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if (a->GetValue() < 0) {
// 		// argument is < zero, can't do
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("Log10Link");
// 		string myop("value <= 0");
// 		string mydesc("log(<=0) is undefined");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	} 
// 	// go for it
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		assert(t >= 0);
// 		a->SetCoeff(1);    
// 		a->SetValue(log10(t));
// 		a->SetExponent(1);
// 		a->SetOpType(OPT_CONST);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(LOG10);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression AbsLink(Expression a) throw(ErrNotPermitted) {
// 	if(a->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AbsLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if (a->GetOpType() == OPT_CONST) {
// 		double t = a->GetValue();
// 		a->SetCoeff(1);
// 		if(a->GetValue() < 0)
// 			a->SetValue(-(a->GetValue()));
// 		a->SetExponent(1);
// 		return a;
// 	} else {
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(ABS);
// 		ret->AddNode(a);
// 		return ret;
// 	}
// }
// 
// Expression MaxLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("MaxLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST){
// 		return a->GetValue() > b->GetValue() ? a: b;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(MAX);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// 
// Expression MinLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("MinLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST){
// 		return a->GetValue() > b->GetValue() ? b: a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(MIN);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// 
// Expression ModLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("ModLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST){
// 		double av = a->GetValue();
// 		double bv = b->GetValue();
// 		a->SetCoeff(1);
// 		a->SetExponent(1);
// 		a->SetValue(av - int(av/bv)*bv);
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(MOD);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// 
// Expression AndLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AndLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST){
// 		a->SetValue(a->GetValue() && b->GetValue());
// 		a->SetCoeff(1);
// 		a->SetExponent(1);
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(AND);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// 
// Expression OrLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("OrLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST){
// 		a->SetValue(a->GetValue() || b->GetValue());
// 		a->SetCoeff(1);
// 		a->SetExponent(1);
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(OR);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// 
// Expression EqLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("EqLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsConstant() && b->IsConstant()){
// 		a->SetValue(a->HasValue(b->GetValue()));
// 		a->SetExponent(1);
// 		a->SetCoeff(1);		
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(EQ);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// 
// Expression NeLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("NeLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsConstant() && b->IsConstant()){
// 		a->SetValue(!(a->HasValue(b->GetValue())));
// 		a->SetExponent(1);
// 		a->SetCoeff(1);		
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(NE);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// Expression LtLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("LtLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsConstant() && b->IsConstant()){
// 		a->SetValue(a->GetValue() < b->GetValue());
// 		a->SetExponent(1);
// 		a->SetCoeff(1);		
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(LT);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// 
// Expression GtLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("GtLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsConstant() && b->IsConstant()){
// 		a->SetValue(a->GetValue() > b->GetValue());
// 		a->SetExponent(1);
// 		a->SetCoeff(1);		
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(GT);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// Expression LeLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("LeLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsConstant() && b->IsConstant()){
// 		a->SetValue(a->GetValue() <= b->GetValue());
// 		a->SetExponent(1);
// 		a->SetCoeff(1);		
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(LE);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// Expression GeLink(Expression a, Expression b) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("GeLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsConstant() && b->IsConstant()){
// 		a->SetValue(a->GetValue() >= b->GetValue());
// 		a->SetExponent(1);
// 		a->SetCoeff(1);		
// 		return a;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(GE);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		return ret;
// 	}
// }
// Expression DVACCWxyzLink(Expression a, Expression b, Expression c, int type) throw(ErrNotPermitted) {
// 	if(type != DX && type != DY && type != DZ &&
// 		type != VX && type != VY && type != VZ &&
// 		type != ACCX && type != ACCY && type != ACCZ &&
// 		type != WX && type != WY && type != WZ){
// 			unsigned long mycode(0);
// 			string myif("Expression Building");
// 			string myscope("AVACCWxyzLink");	
// 			string myop("Wrong operand");
// 			string mydesc("Wrong operand, can't do");
// 			string myinfo(HELPURL);
// 			throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsNotMarker() || b->IsNotMarker()|| c->IsNotMarker()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AVACCWxyzLink");	
// 		string myop("Not Marker");
// 		string mydesc("Not Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 
// 	Expression ret;
// 	ret->SetCoeff(1);
// 	ret->SetExponent(1);
// 	ret->SetOpType(type);
// 	ret->AddNode(a);
// 	ret->AddNode(b);
// 	ret->AddNode(c);
// 	return ret;
// }
// 
// Expression AxyzLink(Expression a, Expression b, int type) throw(ErrNotPermitted) {
// 	if(type != AX && type != AY && type != AZ){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AxyzLink");	
// 		string myop("Wrong operand");
// 		string mydesc("Wrong operand, can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 	if(a->IsNotMarker() || b->IsNotMarker()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("AxyzLink");	
// 		string myop("Not Marker");
// 		string mydesc("Not Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 
// 	Expression ret;
// 	ret->SetCoeff(1);
// 	ret->SetExponent(1);
// 	ret->SetOpType(type);
// 	ret->AddNode(a);
// 	ret->AddNode(b);
// 	return ret;
// }
// 
// Expression IfLink(Expression a, Expression b, Expression c, Expression d) throw(ErrNotPermitted) {
// 	if(a->IsPointer() || b->IsPointer() || c->IsPointer() || d->IsPointer()){
// 		unsigned long mycode(0);
// 		string myif("Expression Building");
// 		string myscope("IfLink");
// 		string myop("Marker");
// 		string mydesc("Marker can't do");
// 		string myinfo(HELPURL);
// 		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 
// 	if(a->IsConstant()){
// 		double res = a->GetValue();
// 		if(res < 0)
// 			return b;
// 		else if(res > 0)
// 			return d;
// 		else
// 			return c;
// 	}else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(OPT_IF);
// 		ret->AddNode(a);
// 		ret->AddNode(b);
// 		ret->AddNode(c);
// 		ret->AddNode(d);
// 		return ret;
// 	}
// }
// 
// Expression StepLink(Expression x, Expression x0, Expression h0, Expression x1, Expression h1)throw(ErrNotPermitted){
// 	if(x->IsPointer() || x0->IsPointer() || h0->IsPointer() 
// 		|| x1->IsPointer() || h1->IsPointer()){
// 			unsigned long mycode(0);
// 			string myif("Expression Building");
// 			string myscope("StepLink");
// 			string myop("Marker");
// 			string mydesc("Marker can't do");
// 			string myinfo(HELPURL);
// 			throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
// 	}
// 
// 	if(x->IsConstant() && x0->IsConstant() && (x->GetValue() <= x0->GetValue()))
// 		return h0;
// 	else if(x->IsConstant() && x1->IsConstant() && (x->GetValue() >= x1->GetValue()))
// 		return h1;
// 	else if(x->IsConstant() && x0->IsConstant() && x1->IsConstant() &&
// 		h0->IsConstant() && h1->IsConstant() && 
// 		(x->GetValue() > x0->GetValue()) && (x->GetValue() < x1->GetValue())){
// 			double a = h1->GetValue() - h0->GetValue();
// 			double delta = (x->GetValue()-x0->GetValue())/(x1->GetValue()-x0->GetValue());
// 			x->SetCoeff(1);
// 			x->SetExponent(1);
// 			x->SetValue(h0->GetValue() + a * delta * delta * (3.0 - 2.0*delta ));
// 			return x;
// 	}
// 	else{
// 		Expression ret;
// 		ret->SetCoeff(1);
// 		ret->SetExponent(1);
// 		ret->SetOpType(OPT_STEP);
// 		ret->AddNode(x);
// 		ret->AddNode(x0);
// 		ret->AddNode(h0);
// 		ret->AddNode(x1);
// 		ret->AddNode(h1);
// 		return ret;
// 	}
// }