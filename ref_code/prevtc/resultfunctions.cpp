#include "resultfunctions.h"
#include "resultexpressionparser.h"

#include "base/Console.h"

#include "precore/IResultItem.h"
#include "precore/DynamicResultItem.h"
#include "precore/precore_data.h"


using namespace INSIDES;
using namespace Base;


Expression ResultCompFunction::FuncLink( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	return BaseFunction::FuncLink(Exprs, nPara) ;
}

double ResultCompFunction::EvalValue( BasicExpression& a )
{
	Expression a1=a.GetNode(0);

	IResultItem* resultItem=(IResultItem*)a1->GetPt();
	if(!resultItem){
		Console().Error("Find no result item in function.");
		return 0.0;
	}
	
	int i1=a.GetNode(1)->eval();
	int i2=a.GetNode(2)->eval();
	double* d=resultItem->getData(i1,i2);
	if(d)
		return d[0];
	return 0.0;
}

////////////////////////////////////////////////////////////////////////////////
Expression TimeFunction::FuncLink( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	return BaseFunction::FuncLink(Exprs,nPara);
}

double TimeFunction::EvalValue( BasicExpression& a )
{
	double* value=(double*)a.GetPt();
	return value[0];
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Expression ContactCompFunction::FuncLink( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)
{
	return BaseFunction::FuncLink(Exprs, nPara) ;
}

double ContactCompFunction::EvalValue( BasicExpression& a )
{
	Expression a1=a.GetNode(0);

	IResultItem* resultItem=(IResultItem*)a1->GetPt();
	if(!resultItem || resultItem->getClassType()!=TDY_POST_ITEMCLASS_DYNAMICRIGID){
		Console().Error("Error in contact_comp");
		return 0.0;
	}

	int i1=a.GetNode(1)->eval();
	int i2=a.GetNode(2)->eval();
	int i3=a.GetNode(3)->eval();
	DynamicResultItem* dynamicResultItem=(DynamicResultItem*)resultItem;
	if(dynamicResultItem->getPieceCount()<=i3)
		return 0;

	double* d=resultItem->getData(i1,i2);
	if(d)
		return d[i3*resultItem->getDataLength()];
	return 0.0;
}
