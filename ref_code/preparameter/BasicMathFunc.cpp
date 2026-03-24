#include "BasicMathFunc.h"
#include <time.h>

REGISTER_DEF_FUNC(LOGFunction) ;
Expression	LOGFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("LogLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// make a preliminary check
	if (a->IsZero()) 
	{
		// *this is zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("LogLink");
		string myop("IsZero()");
		string mydesc("log(0) is undefined");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if (a->GetValue() < 0) 
	{
		// argument is < zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("LogLink");
		string myop("value <= 0");
		string mydesc("log(<=0) is undefined");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	} 
	// go for it
	if (a->GetOpType() == OPT_CONST) 
	{
		double t = a->GetValue();
		assert(t >= 0);
		a->SetCoeff(1);    
		a->SetValue(log(t));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		LOGFunction::EvalValue	( BasicExpression& a ) 
{
	double ret, tmp ;

	tmp = (a.GetNode(0))->eval() ;
	if (tmp < 0)
	{
		cerr << "BasicExpression::Eval: log of negative not allowed ("
			<< "argument evaluates to < 0), taking absolute value" << endl;
		//throw ErrNotPermitted(6, "BasicExpression", "Eval", "log arg < 0", 
		//"log of negative not allowed", HELPURL);
		tmp = -tmp;
	}
	else if (tmp == 0)
	{
		cerr << "BasicExpression::Eval: log of zero not allowed ("
			<< "argument evaluates to 0), setting to large negative value" 
			<< endl;
		//throw ErrNotPermitted(7, "BasicExpression", "Eval", "log arg == 0", 
		//"log of zero not allowed", HELPURL);
		tmp = Ev3NearZero();
	}
	ret = (a.GetCoeff()) * log(tmp);

	return ret ;
}


REGISTER_DEF_FUNC(LOG10Function) ;
Expression	LOG10Function::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("Log10Link");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}

	// make a preliminary check
	if (a->IsZero())
	{
		// *this is zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("Log10Link");
		string myop("IsZero()");
		string mydesc("log10(0) is undefined");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if (a->GetValue() < 0)
	{
		// argument is < zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("Log10Link");
		string myop("value <= 0");
		string mydesc("log(<=0) is undefined");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	} 
	// go for it
	if (a->GetOpType() == OPT_CONST)
	{
		double t = a->GetValue();
		assert(t >= 0);
		a->SetCoeff(1);    
		a->SetValue(log10(t));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		LOG10Function::EvalValue	( BasicExpression& a ) 
{
	double ret, tmp ;

	tmp = (a.GetNode(0))->eval();

	if (tmp < 0) 
	{
		cerr << "BasicExpression::Eval: log10 of negative not allowed ("
			<< "argument evaluates to < 0), taking absolute value" << endl;
		//throw ErrNotPermitted(6, "BasicExpression", "Eval", "log arg < 0", 
		//"log of negative not allowed", HELPURL);
		tmp = -tmp;
	} 
	else if (tmp == 0) 
	{
		cerr << "BasicExpression::Eval: log10 of zero not allowed ("
			<< "argument evaluates to 0), setting to large negative value" 
			<< endl;
		//throw ErrNotPermitted(7, "BasicExpression", "Eval", "log arg == 0", 
		//"log of zero not allowed", HELPURL);
		tmp = Ev3NearZero();
	}

	ret = (a.GetCoeff()) * log10(tmp);

	return ret ;
}

REGISTER_DEF_FUNC(EXPFunction) ;
Expression	EXPFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("ExpLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if (a->GetOpType() == OPT_CONST)
	{
		a->SetCoeff(1);
		a->SetValue(exp(a->GetValue()));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		EXPFunction::EvalValue	( BasicExpression& a ) 
{
	return (a.GetCoeff()) * exp((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(SINFunction) ;
Expression	SINFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("SinLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if (a->GetOpType() == OPT_CONST)
	{
		a->SetCoeff(1);
		a->SetValue(sin(a->GetValue()));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		SINFunction::EvalValue	( BasicExpression& a )
									 
{
	return (a.GetCoeff()) * sin((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(COSFunction) ;
Expression	COSFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("CosLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if (a->GetOpType() == OPT_CONST) 
	{
		a->SetCoeff(1);
		a->SetValue(cos(a->GetValue()));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		COSFunction::EvalValue	( BasicExpression& a )
									 
{
	return (a.GetCoeff()) * cos((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(TANFunction) ;
Expression	TANFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("TanLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	//没有检测给定的值是否接近pi/2
	if (a->GetOpType() == OPT_CONST) 
	{
		a->SetCoeff(1);
		a->SetValue(tan(a->GetValue()));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	}
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		TANFunction::EvalValue	( BasicExpression& a )							 
{
	return (a.GetCoeff()) * tan((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(COTFunction) ;
Expression	COTFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("CotLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// make a preliminary check
	if (a->IsZero())
	{
		// *this is zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("CotLink");
		string myop("IsZero()");
		string mydesc("cot(0) is undefined");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if ( a->GetOpType() == OPT_CONST) 
	{
		double t = tan(a->GetValue());
		assert(t != 0);
		a->SetCoeff(1);
		a->SetValue(1 / t);
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}	

double		COTFunction::EvalValue	( BasicExpression& a )
									 
{
	return (a.GetCoeff()) / tan((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(SINHFunction) ;
Expression	SINHFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("SinhLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if (a->GetOpType() == OPT_CONST) 
	{
		a->SetCoeff(1);
		a->SetValue(sinh(a->GetValue()));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		SINHFunction::EvalValue	( BasicExpression& a )
									 
{
	return (a.GetCoeff()) * sinh((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(COSHFunction) ;
Expression	COSHFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("CoshLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if (a->GetOpType() == OPT_CONST) 
	{
		a->SetCoeff(1);
		a->SetValue(cosh(a->GetValue()));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	}
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		COSHFunction::EvalValue	( BasicExpression& a )
									 
{
	return (a.GetCoeff()) * cosh((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(TANHFunction) ;
Expression	TANHFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("TanhLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if (a->GetOpType() == OPT_CONST) 
	{
		a->SetCoeff(1);
		a->SetValue(tanh(a->GetValue()));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		TANHFunction::EvalValue	( BasicExpression& a )
									 
{
	return (a.GetCoeff()) * tanh((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(COTHFunction) ;
Expression	COTHFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("CothLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// make a preliminary check
	if (a->IsZero())
	{
		// *this is zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("CothLink");
		string myop("IsZero()");
		string mydesc("coth(0) is undefined");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// go for it
	if (a->GetOpType() == OPT_CONST)
	{
		double t = tanh(a->GetValue());
		assert(t != 0);
		a->SetCoeff(1);
		a->SetValue(1 / t);
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	}
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		COTHFunction::EvalValue	( BasicExpression& a )
									 
{
	return (a.GetCoeff()) / tanh((a.GetNode(0))->eval());
}

REGISTER_DEF_FUNC(SQRTFunction) ;
Expression	SQRTFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("SqrtLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// make a preliminary check
	if (a->GetValue() < 0 && !a->HasValue(0)) 
	{
		// argument is < zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("SqrtLink");
		string myop("value < 0");
		string mydesc("sqrt(<0) is complex, can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	} 
	// go for it
	if (a->GetOpType() == OPT_CONST)
	{
		double t = a->GetValue();
		assert(t >= 0);
		a->SetCoeff(1);
		a->SetValue(sqrt(t));
		a->SetExponent(1);
		a->SetOpType(OPT_CONST);
		return a;
	} 
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		SQRTFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, tmp ;
	tmp = (a.GetNode(0))->eval();

	if (tmp < 0) 
	{
		cerr << "BasicExpression::Eval: sqrt of negative not allowed, "
			<< "taking absolute value" << endl;
		//throw ErrNotPermitted(9, "BasicExpression", "Eval", "sqrt arg < 0", 
		//"sqrt of negative not allowed", HELPURL);
		tmp = -tmp;
	}

	ret = (a.GetCoeff()) * sqrt(tmp);
	return ret ;
}

REGISTER_DEF_FUNC(ASINFunction) ;
Expression	ASINFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("AsinLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// make a preliminary check
	if (a->GetValue() <= -1|| a->GetValue() >= 1)
	{
		// argument is < zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("AsinLink");
		string myop("value < -1 || value > 1");
		string mydesc("asin(<-1 || >1) can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	} 
	// go for it
	if (a->GetOpType() == OPT_CONST) 
	{
		double t = a->GetValue();
		a->SetCoeff(1);
		a->SetValue(asin(t));
		a->SetExponent(1);
		return a;
	}
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		ASINFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, tmp ;

	tmp = (a.GetNode(0))->eval();
	if (tmp < -1 || tmp > 1)
	{
		cerr << "BasicExpression::Eval: asin not allowed, "
			<< "taking 0 value" << endl;
		//throw ErrNotPermitted(9, "BasicExpression", "Eval", "sqrt arg < 0", 
		//"sqrt of negative not allowed", HELPURL);
		tmp = 0;
	}

	ret = (a.GetCoeff()) * asin(tmp);

	return ret ;
}

REGISTER_DEF_FUNC(ACOSFunction) ;
Expression	ACOSFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("AcosLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	// make a preliminary check
	if (a->GetValue() <= -1 || a->GetValue() >= 1) 
	{
		// argument is < zero, can't do
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("AcosLink");
		string myop("value < -1 || value > 1");
		string mydesc("acos(<-1 || >1) can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	} 
	// go for it
	if (a->GetOpType() == OPT_CONST) 
	{
		double t = a->GetValue();
		a->SetCoeff(1);
		a->SetValue(acos(t));
		a->SetExponent(1);
		return a;
	}
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		ACOSFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, tmp ;

	tmp = (a.GetNode(0))->eval();
	if (tmp < -1 || tmp > 1) 
	{
		cerr << "BasicExpression::Eval: acos not allowed, "
			<< "taking 0 value" << endl;
		//throw ErrNotPermitted(9, "BasicExpression", "Eval", "sqrt arg < 0", 
		//"sqrt of negative not allowed", HELPURL);
		tmp = 0;
	}
	ret =  (a.GetCoeff())* acos(tmp);

	return ret ;
}

REGISTER_DEF_FUNC(ATANFunction) ;
Expression	ATANFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("AtanLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if (a->GetOpType() == OPT_CONST)
	{
		double t = a->GetValue();
		a->SetCoeff(1);
		a->SetValue(atan(t));
		a->SetExponent(1);
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		ATANFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, tmp ;

	tmp =  (a.GetNode(0))->eval();
	ret =  (a.GetCoeff()) * atan(tmp);

	return ret ;
}


REGISTER_DEF_FUNC(ATAN2Function) ;
Expression	ATAN2Function::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	if ( nPara != 2 )
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("Atan2Link");
		string myop("Marker");
		string mydesc("need two parameters");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	else
	{
		for ( int i = 0; i < nPara; i++ )
		{
			Expression& a = Exprs[i] ;

			if(a->IsPointer())
			{
				unsigned long mycode(0);
				string myif("Expression Building");
				string myscope("Atan2Link");
				string myop("Marker");
				string mydesc("Marker can't do");
				string myinfo(HELPURL);
				throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
			}
			if (a->GetOpType() == OPT_CONST)
			{
				double t = a->GetValue();
				a->SetCoeff(1);
				a->SetValue(atan(t));
				a->SetExponent(1);
			}
		}
	}

	return BaseFunction::FuncLink(Exprs, nPara) ;
}

double		ATAN2Function::EvalValue	( BasicExpression& a )

{
	double ret, y, x ;

	y =  (a.GetNode(0))->eval();
	x =  (a.GetNode(1))->eval();
	ret =  (a.GetCoeff()) * atan2(y, x);

	return ret ;
}

REGISTER_DEF_FUNC(SIGNFunction) ;
Expression	SIGNFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("SignLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if (a->GetOpType() == OPT_CONST) 
	{
		double t = a->GetValue();
		a->SetCoeff(1);
		if(a->GetValue() == 0)
			a->SetValue(0);
		else if(a->GetValue() > 0)
			a->SetValue(1);
		else
			a->SetValue(-1);
		a->SetExponent(1);
		return a;
	} 
	else 
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		SIGNFunction::EvalValue	( BasicExpression& a )
									 
{
	double tmp, ret ;

	tmp =  (a.GetNode(0))->eval();

	if(tmp > 0.0)
		ret = 1.0;
	else if (tmp < 0.0)
		ret = -1.0;
	else
		ret = 0.0;
	ret *= (a.GetCoeff()) ;
	
	return ret ;
}

REGISTER_DEF_FUNC(ABSFunction) ;
Expression	ABSFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;

	if(a->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("AbsLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if (a->GetOpType() == OPT_CONST) 
	{
		double t = a->GetValue();
		a->SetCoeff(1);
		if(a->GetValue() < 0)
			a->SetValue(-(a->GetValue()));
		a->SetExponent(1);
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		ABSFunction::EvalValue	( BasicExpression& a )
									 
{
	double tmp, ret ;

	tmp = (a.GetNode(0))->eval();
	ret = tmp>0.0 ? tmp: -tmp;
	ret *= (a.GetCoeff()) ;

	return ret ;
}

/* 二元函数 */
REGISTER_DEF_FUNC(MAXFunction) ;
Expression	MAXFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("MaxLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST)
	{
		return a->GetValue() > b->GetValue() ? a: b;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		MAXFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret  = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret = ret>ret2 ? ret: ret2;
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(MINFunction) ;
Expression	MINFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("MinLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST)
	{
		return a->GetValue() > b->GetValue() ? b: a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		MINFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret  = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret = ret>ret2 ? ret2: ret;
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(MODFunction) ;
Expression	MODFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("ModLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST)
	{
		double av = a->GetValue();
		double bv = b->GetValue();
		a->SetCoeff(1);
		a->SetExponent(1);
		a->SetValue(av - int(av/bv)*bv);
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		MODFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();

	if ( ret > 0 && ret2 > 0 )
		ret  = ret - int(ret/ret2)*ret2;

	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(ANDFunction) ;
Expression	ANDFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("AndLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST)
	{
		a->SetValue(a->GetValue() && b->GetValue());
		a->SetCoeff(1);
		a->SetExponent(1);
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		ANDFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret  = ( ret && ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(ORFunction) ;
Expression	ORFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("OrLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->GetOpType() == OPT_CONST && b->GetOpType() == OPT_CONST)
	{
		a->SetValue(a->GetValue() || b->GetValue());
		a->SetCoeff(1);
		a->SetExponent(1);
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		ORFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret  = ( ret || ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(EQFunction) ;
Expression	EQFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("EqLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->IsConstant() && b->IsConstant())
	{
		a->SetValue(a->HasValue(b->GetValue()));
		a->SetExponent(1);
		a->SetCoeff(1);		
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		EQFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret  = ( ret == ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(NEFunction) ;
Expression	NEFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("NeLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->IsConstant() && b->IsConstant())
	{
		a->SetValue(!(a->HasValue(b->GetValue())));
		a->SetExponent(1);
		a->SetCoeff(1);		
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		NEFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret  = ( ret != ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(LTFunction) ;
Expression	LTFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("LtLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->IsConstant() && b->IsConstant())
	{
		a->SetValue(a->GetValue() < b->GetValue());
		a->SetExponent(1);
		a->SetCoeff(1);		
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		LTFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret = ( ret < ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(LEFunction) ;
Expression	LEFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("LeLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}

	if(a->IsConstant() && b->IsConstant())
	{
		a->SetValue(a->GetValue() <= b->GetValue());
		a->SetExponent(1);
		a->SetCoeff(1);		
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		LEFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret = ( ret <= ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}	

REGISTER_DEF_FUNC(GTFunction) ;
Expression	GTFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("GtLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->IsConstant() && b->IsConstant())
	{
		a->SetValue(a->GetValue() > b->GetValue());
		a->SetExponent(1);
		a->SetCoeff(1);		
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		GTFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret = ( ret > ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(GEFunction) ;
Expression	GEFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;

	if(a->IsPointer() || b->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("GeLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	if(a->IsConstant() && b->IsConstant())
	{
		a->SetValue(a->GetValue() >= b->GetValue());
		a->SetExponent(1);
		a->SetCoeff(1);		
		return a;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		GEFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, ret2 ;

	ret	 = (a.GetNode(0))->eval();
	ret2 = (a.GetNode(1))->eval();
	ret = ( ret >= ret2 ) ; 
	ret *= (a.GetCoeff());

	return ret ;
}

REGISTER_DEF_FUNC(IFFunction) ;
Expression	IFFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	Expression& a = Exprs[0] ;
	Expression& b = Exprs[1] ;
	Expression& c = Exprs[2] ;
	Expression& d = Exprs[3] ;

	if(a->IsPointer() || b->IsPointer() || c->IsPointer() || d->IsPointer())
	{
		unsigned long mycode(0);
		string myif("Expression Building");
		string myscope("IfLink");
		string myop("Marker");
		string mydesc("Marker can't do");
		string myinfo(HELPURL);
		throw ErrNotPermitted(mycode,myif,myscope,myop,mydesc,myinfo);
	}
	 
	if(a->IsConstant())
	{
		double res = a->GetValue();
		if(res < 0)
			return b;
		else if(res > 0)
			return d;
		else
			return c;
	}
	else
	{
		return BaseFunction::FuncLink(Exprs, nPara) ;
	}
}

double		IFFunction::EvalValue	( BasicExpression& a )
									 
{
	double ret, val ;

	val = (a.GetNode(0))->eval();

	if( val < 0)
		ret = (a.GetNode(1))->eval();
	else if( val > 0)
		ret = (a.GetNode(3))->eval();
	else
		ret = (a.GetNode(2))->eval();

	ret *= a.GetCoeff() ;

	return ret ;
}

REGISTER_DEF_FUNC(RANDFunction) ;
Expression	RANDFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	if ( nPara != 1 && nPara !=  2 )
		cerr << "error: " << "RAND function need 1 or 2 parameters." << endl ;

	for ( int i = 0; i < nPara; i++ )
	{
		if (Exprs[i]->GetOpType() != OPT_CONST)
		{
			cerr << "error: " << "Parameter of RAND must be constant!" << endl ;
			break ;
		} 
	}
	
	return BaseFunction::FuncLink(Exprs, nPara) ;
}

double		RANDFunction::EvalValue	( BasicExpression& a )
									 
{
	srand( time_t(NULL) );

	double ran = double(rand())/ ( RAND_MAX+1 ) ;
	double minval = 0, maxval ;
	if ( a.GetSize() == 2 )
	{
		 minval = (a.GetNode(0))->eval();
		 maxval = (a.GetNode(1))->eval();
	}
	else if ( a.GetSize() == 1 )
		maxval = (a.GetNode(0))->eval();

	return a.GetCoeff() * ( ran * ( maxval - minval ) + minval ) ;
}
