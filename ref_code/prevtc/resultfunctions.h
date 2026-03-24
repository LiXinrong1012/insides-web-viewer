#ifndef RESULTFUNCTIONS_H
#define RESULTFUNCTIONS_H

#include "preparameter/BasicFunctionOperand.h"

/*!
	@brief   以下三个类，暂不清楚为何意
	@date    2015.6.29
	@author  Jerry
*/
class ResultCompFunction: public BaseFunction
{
public:
	ResultCompFunction(){m_iNumOfPara=5;m_strFuncName="RESULT_COMP";}

	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)  ;
	virtual double		EvalValue	( BasicExpression& a  );
};

class ContactCompFunction : public BaseFunction
{
public:
	ContactCompFunction(){m_iNumOfPara=5;m_strFuncName="CONTACT_COMP";}
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)  ;
	virtual double		EvalValue	( BasicExpression& a  );
};

class TimeFunction : public BaseFunction
{
public:
	TimeFunction(){m_iNumOfPara=0;m_strFuncName="TIME";}

	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)  ;
	virtual double		EvalValue	( BasicExpression& a  );
};

#endif // RESULTFUNCTIONS_H
