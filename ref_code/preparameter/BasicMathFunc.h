#pragma once 
#include "BasicFunctionOperand.h"

class  LOGFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(LOGFunction) ;

public:
	LOGFunction()  { m_iNumOfPara = 1, m_strFuncName = "LOG" ;};
	~LOGFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a  ) 	;
};

class  LOG10Function : public BaseFunction
{
	REGISTER_DEC_FUNC(LOG10Function) ;

public:
	LOG10Function()  { m_iNumOfPara = 1, m_strFuncName = "LOG10" ; };
	~LOG10Function() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  EXPFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(EXPFunction) ;
public:
	EXPFunction()  { m_iNumOfPara = 1, m_strFuncName = "EXP" ; };
	~EXPFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a  ) 	;
};


class  SINFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(SINFunction) ;
public:
	SINFunction()  { m_iNumOfPara = 1, m_strFuncName = "SIN" ; };
	~SINFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara )	;
	virtual double		EvalValue	( BasicExpression& a  ) 	;
};


class  RANDFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(RANDFunction) ;
public:
	RANDFunction()  { m_iNumOfPara = 2, m_strFuncName = "RAND" ; };
	~RANDFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  COSFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(COSFunction) ;
public:
	COSFunction()  { m_iNumOfPara = 1, m_strFuncName = "COS" ; };
	~COSFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  TANFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(TANFunction) ;
public:
	TANFunction()  { m_iNumOfPara = 1, m_strFuncName = "TAN" ; };
	~TANFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  COTFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(COTFunction) ;
public:
	COTFunction()  { m_iNumOfPara = 1, m_strFuncName = "COT" ; };
	~COTFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  SINHFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(SINHFunction) ;
public:
	SINHFunction()  { m_iNumOfPara = 1, m_strFuncName = "SINH" ; };
	~SINHFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  COSHFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(COSHFunction) ;
public:
	COSHFunction()  { m_iNumOfPara = 1, m_strFuncName = "COSH" ; };
	~COSHFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  TANHFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(TANHFunction) ;
public:
	TANHFunction()  { m_iNumOfPara = 1, m_strFuncName = "TANH" ; };
	~TANHFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};



class  COTHFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(COTHFunction) ;
public:
	COTHFunction()  { m_iNumOfPara = 1, m_strFuncName = "COTH" ; };
	~COTHFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  SQRTFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(SQRTFunction) ;
public:
	SQRTFunction()  { m_iNumOfPara = 1, m_strFuncName = "SQRT" ; };
	~SQRTFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};



class  ASINFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(ASINFunction) ;
public:
	ASINFunction()  { m_iNumOfPara = 1, m_strFuncName = "ASIN" ; };
	~ASINFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};



class  ACOSFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(ACOSFunction) ;
public:
	ACOSFunction()  { m_iNumOfPara = 1, m_strFuncName = "ACOS" ; };
	~ACOSFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  ATANFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(ATANFunction) ;
public:
	ATANFunction()  { m_iNumOfPara = 1, m_strFuncName = "ATAN" ; };
	~ATANFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  ATAN2Function : public BaseFunction
{
	REGISTER_DEC_FUNC(ATAN2Function) ;
public:
	ATAN2Function()  { m_iNumOfPara = 2, m_strFuncName = "ATAN2" ; };
	~ATAN2Function() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};

class  SIGNFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(SIGNFunction) ;
public:
	SIGNFunction()  { m_iNumOfPara = 1, m_strFuncName = "SIGN" ; };
	~SIGNFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  ABSFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(ABSFunction) ;
public:
	ABSFunction()  { m_iNumOfPara = 1, m_strFuncName = "ABS" ; };
	~ABSFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


/* ¶þÔªº¯Êý */
class  MAXFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(MAXFunction) ;
public:
	MAXFunction()  { m_iNumOfPara = 2, m_strFuncName = "MAX" ; };
	~MAXFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  MINFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(MINFunction) ;
public:
	MINFunction()  { m_iNumOfPara = 2, m_strFuncName = "MIN" ; };
	~MINFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  MODFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(MODFunction) ;
public:
	MODFunction()  { m_iNumOfPara = 2, m_strFuncName = "MOD" ; };
	~MODFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  ANDFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(ANDFunction) ;
public:
	ANDFunction()  { m_iNumOfPara = 2, m_strFuncName = "AND" ; };
	~ANDFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  ORFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(ORFunction) ;
public:
	ORFunction()  { m_iNumOfPara = 2, m_strFuncName = "OR" ; };
	~ORFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) 	;
};


class  EQFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(EQFunction) ;
public:
	EQFunction()  { m_iNumOfPara = 2, m_strFuncName = "EQ" ; };
	~EQFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) ;
};


class  NEFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(NEFunction) ;
public:
	NEFunction()  { m_iNumOfPara = 2, m_strFuncName = "NE" ; };
	~NEFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) ;
};


class  LTFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(LTFunction) ;
public:
	LTFunction()  { m_iNumOfPara = 2, m_strFuncName = "LT" ; };
	~LTFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) ;
};


class  LEFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(LEFunction) ;
public:
	LEFunction()  { m_iNumOfPara = 2, m_strFuncName = "LE" ; };
	~LEFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) ;
};


class  GTFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(GTFunction) ;
public:
	GTFunction()  { m_iNumOfPara = 2, m_strFuncName = "GT" ; };
	~GTFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) ;
};


class  GEFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(GEFunction) ;
public:
	GEFunction()  { m_iNumOfPara = 2, m_strFuncName = "GE" ; };
	~GEFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) ;
};


class  IFFunction : public BaseFunction
{
	REGISTER_DEC_FUNC(IFFunction) ;
public:
	IFFunction()  { m_iNumOfPara = 4, m_strFuncName = "IF" ; };
	~IFFunction() {} ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)	;
	virtual double		EvalValue	( BasicExpression& a ) ;
};