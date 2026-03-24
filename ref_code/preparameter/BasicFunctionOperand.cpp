#include "BasicFunctionOperand.h"

map_Func* FuncFactory::mapF = NULL ;

Expression	BaseFunction::FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted) 
{
	Expression ret;
	ret->SetCoeff(1);
	ret->SetExponent(1);
	ret->SetOpType(OPT_FUNCTION) ;
	ret->SetVarName(m_strFuncName) ;
	ret->setFunction(this);
	for ( int i = 0; i < nPara; i++ )	ret->AddNode(Exprs[i]) ;
	return ret;
} 