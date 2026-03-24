#include "expression.h"
#include <string>
#include <sstream>
#include <strstream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include "BasicFunctionOperand.h"
#include "Parameter.h"

#define RCS4 "$Id: expression.cxx,v 1.27 2006/07/30 05:36:39 liberti Exp liberti $"

using namespace std;

////////////// MEMCHECK debug ////////////////////
#ifdef MEMDEBUG
vector<pair<void*,pair<int,int*> > > memcheckdebug;
vector<pair<void*,pair<int,int*> > >::iterator memcheckdebugit;
pair<void*, pair<int, int*> > memcheckdebugpair;
int memcheckdebugcounter = 0;
#endif
///////////// END MEMCHECK debug ////////////////

////////////// auxiliary functions ///////////////

//#define PEV3PI 3.1415926535897932385
#define NOTVARNAME "_var_not_found_"
#define VNAMEIDXCHAR ""


///////////// classes ////////////////

//新增的方法


void Operand::SetPt(void * p)
{
	mpt = p;
}

void * Operand::GetPt()
{
	return mpt;
}

bool Operand::IsPointer() const
{
	return (oplabel == POINTER);
}
bool Operand::IsNotPointer() const
{
	return (oplabel != POINTER);
}
// constructors
Operand::Operand() : 
oplabel(OPT_CONST), constant(0), varindex(NOVARIABLE), 
coefficient(1), exponent(1), dependency(0), 
depconstant(NULL), depcoefficient(NULL), depexponent(NULL) 
,baseFunction(NULL)
{ }

Operand::Operand(double t) : 
oplabel(OPT_CONST), constant(t), varindex(NOVARIABLE),
coefficient(1), exponent(1), dependency(0),
baseFunction(NULL),
depconstant(NULL), depcoefficient(NULL), depexponent(NULL) { }

Operand::Operand(const Int t) : 
oplabel(OPT_CONST), constant(t), varindex(NOVARIABLE),
coefficient(1), exponent(1), dependency(0),
baseFunction(NULL),
depconstant(NULL), depcoefficient(NULL), depexponent(NULL) { }

Operand::Operand(const Int t, const bool isvar) :   
coefficient(1), exponent(1), dependency(0),
baseFunction(NULL),
depconstant(NULL), depcoefficient(NULL), depexponent(NULL) 
{ 
	if (isvar) 
	{
		// make it a variable
		oplabel = VAR;
		constant = 0;
		varindex = t;
	} 
	else
	{
		// make it an operator label
		oplabel = (int) t;
		constant = 0;
		varindex = NOVARIABLE;
	}
}

// create an (empty) operator or a variable leaf and set coefficient
Operand::Operand(const double c, const Int t, string vn) : 
coefficient(c), exponent(1) ,
baseFunction(NULL)
{ 
	// make it a variable
	oplabel = VAR;
	constant = 0;
	varindex = t;
	varname = vn;
	dependency = 0;
	depconstant = NULL;
	depcoefficient = NULL;
	depexponent = NULL;
}

// copy constructor
Operand::Operand(Operand& t) : 
oplabel(t.oplabel), constant(t.constant), depconstant(t.depconstant), 
varindex(t.varindex), varname(t.varname), coefficient(t.coefficient), 
depcoefficient(t.depcoefficient), exponent(t.exponent), 
depexponent(t.depexponent), dependency(t.dependency),mpt(t.mpt)
,baseFunction(t.baseFunction)
{

}

// destructor
Operand::~Operand() { }

// Operand class methods:

// get operator type
int		Operand::GetOpType(void) const { return oplabel; }

// get variable name
string Operand::GetVarName(void) const { return varname; }

// get constant value - in CONSTs, multiply by coeff. and raise 
// to exponent, first
double Operand::GetValue(void) const 
{ 
	double ret = 0;
	if (oplabel == OPT_CONST && dependency == 0)
	{
		if (exponent == 1) 
			ret = coefficient * constant;
		else if (exponent == 2)
			ret = coefficient * constant * constant;
		else
			ret = coefficient * pow(constant, exponent);
	} 
	else if (oplabel == OPT_CONST && dependency == 1 && depconstant)
	{
		ret = *depconstant;
	}
	else 
	{
		ret = constant; 
	}
	return ret;
}

// get variable index
Int Operand::GetVarIndex(void) const { return varindex; }



// set operator type
void Operand::SetOpType(const int t) { oplabel = t; }

int Operand::SetConstValue( double val )
{
	if ( GetOpType() != OPT_CONST ) 
		return 1 ;
	else
	{
		constant = val ;
		return 0 ;
	}
}

// set constant value
void Operand::SetValue(const double t) { constant = t; }

// set variable index
void Operand::SetVarIndex(const Int t) { varindex = t; }

// set variable name
void Operand::SetVarName(const string vn) { varname = vn; }

// is operand a constant?
bool Operand::IsConstant(void) const
{
	return (GetOpType() == OPT_CONST);
}

// is operand a variable?
bool Operand::IsVariable(void) const
{
	return (GetOpType() == VAR);
}

// is operand a leaf node?
bool Operand::IsLeaf(void) const
{
	return (IsConstant() || IsVariable() || IsPointer());
}

void Operand::SetCoeff(const double coeff) 
{
	coefficient = coeff;
}

double Operand::GetCoeff(void) const 
{
	if (dependency == 2 && depcoefficient)
	{
		return *depcoefficient;
	} 
	else
	{
		return coefficient;
	}
}

void Operand::SetExponent(const double expon) 
{
	exponent = expon;
}

double Operand::GetExponent(void) const 
{
	if (dependency == 3 && depexponent)
	{
		return *depexponent;
	} 
	else
	{
		return exponent;
	}
}

// is operand a zero constant?
bool Operand::IsZero(void) const 
{
	if (GetOpType() == OPT_CONST)
	{
		double c = GetValue();
		if (fabs(c) < Ev3NearZero()) 
		{
			return true;
		} 
		else 
		{
			return false;
		}
	} 
	else
	{
		return false;
	}
}

// is operand a constant having value v?
bool Operand::HasValue(double v) const
{
	if (GetOpType() == OPT_CONST)
	{
		double c = GetValue();
		double t1 = v + Ev3NearZero();
		double t2 = v - Ev3NearZero();
		if (c < t1 && c > t2) 
		{
			return true;
		} 
		else 
		{
			return false;
		}
	} 
	else 
	{
		return false;
	}
}  

// create empty
BasicExpression::BasicExpression() { }

// create a constant leaf
BasicExpression::BasicExpression(const double t) : Operand(t) { }

// create a constant (integer-valued) leaf
BasicExpression::BasicExpression(const Int t) : Operand(t) { }

// create an (empty) operator or a variable leaf
BasicExpression::BasicExpression(const Int t, const bool isvar) : 
Operand(t, isvar) { }

// create a variable leaf and set coefficient
BasicExpression::BasicExpression(const double c, const Int t, string vn) : 
Operand(c, t, vn) { }

// user-defined copy constructor with two options
BasicExpression::BasicExpression(const Expression& t, const bool iscopy) :
Operand(t.GetPointee()) 
{
	Int s = t->GetSize();
	if (iscopy) {
		// create a _copy_ of t, subnode by subnode
		for (int i = 0; i < s; i++) {
			nodes.push_back(t->GetCopyOfNode(i));
		}
	} else {
		// create a copy of the pointers in t
		for (int i = 0; i < s; i++) {
			nodes.push_back(t->GetNode(i));
		}
	}
}

// copy constructor
BasicExpression::BasicExpression(BasicExpression& t) : Operand(t) 
{ 
	Int s = t.GetSize();
	// necessary for constructs "(BasicExpression) e =" where e already 
	// existed prior to assignment  
	// -- segvs (?)
	for(int i = 0; i < GetSize(); i++) 
	{
		//RecursiveDestroy(GetNodePtr(i));
	}
	DeleteAllNodes(); 
	// create a copy of the subnode pointers in t
	for (int i = 0; i < s; i++) 
	{
		nodes.push_back(t.GetNode(i));
	}
}

// destructor
BasicExpression::~BasicExpression() { }

// BasicExpression class methods:

void BasicExpression::Zero(void)
{
	// -- segvs (?)
	for(int i = 0; i < GetSize(); i++) 
	{
		RecursiveDestroy(GetNodePtr(i));
	}
	DeleteAllNodes();
	SetCoeff(1.0);
	SetExponent(1.0);
	SetValue(0.0);
	SetOpType(OPT_CONST);
}

void BasicExpression::One(void)
{
	// -- segvs (?)
	for(int i = 0; i < GetSize(); i++)
	{
		RecursiveDestroy(GetNodePtr(i));
	}
	DeleteAllNodes();
	SetCoeff(1.0);
	SetExponent(1.0);
	SetValue(1.0);
	SetOpType(OPT_CONST);
}

// is expression this == expression t?
bool BasicExpression::IsEqualTo(const Expression& t) const 
{
	if (IsEqualToNoCoeff(t))
	{
		if (GetCoeff() == t->GetCoeff() && GetExponent() == t->GetExponent())
			return true;
		else
			return false;
	} 
	else 
		return false;
}

// taken and adapted from operator ==
bool BasicExpression::IsEqualToNoCoeff(const Expression& t) const 
{
	// fast checks
	if (IsLeaf() && t->IsLeaf())
	{
		if (GetOpType() == t->GetOpType()) 
		{
			if (GetOpType() == OPT_CONST)
			{
				if  ( GetValue() == t->GetValue() )
					return true;
				else
					return false ;
				// if both are constants, they're always equal up to coefficient
				// return true;
			} 
			else if (GetOpType() == VAR && GetVarIndex() == t->GetVarIndex() &&
				GetExponent() == t->GetExponent())
				return true;
			else
				return false;
		} 
		else
			return false;
	} 
	else if ((!IsLeaf()) && (!t->IsLeaf())) 
	{
		// both BasicExpressions are not leaves, recurse using PRECISE
		// (i.e. not up to coefficient) form
		if (GetSize() != t->GetSize()) 
			return false;
		if (GetOpType() != t->GetOpType())
			return false;
		Int i;
		bool ret = true;
		for (i = 0; i < GetSize(); i++) 
		{
			if (!(GetNode(i)->IsEqualTo(t->GetNode(i))))
			{
				ret = false;
				break;
			}
		}
		if (ret) 
		{
			return true;
		}
		return false;
	}
	else
		return false;
}

//这个是在程序中需要调用的计算函数
double BasicExpression::eval( )
{
	// evaluate expression
	if ( GetOpType() == OPT_CONST )
	{
		return GetValue();
	}
// 	else if ( GetOpType() == OPT_PARAS )
// 	{
// 		double ret = 0.0 ; 
// 		ret = (((Function*)(GetNode(0)->GetPt()))->GetExpr())->eval( t, NULL, NULL, NULL, NULL, func, NULL ) ;
// 		ret *= GetCoeff();	// 不能忘记了乘系数
// 		return ret ;
// 	}
	else if ( GetOpType() == OPT_FUNCTION )
	{
		string str = GetVarName() ;
		BaseFunction* pFunc = getFunction();//Parameter::m_FuncLib)->getFunction(str);
		if ( pFunc != NULL   )
			return pFunc->EvalValue(*this) ;
		else
			return 0 ;
	}
 	else if ( GetOpType() == OPT_PARAS )
 	{
 		double ret = 0.0 ; 
 		ret = (((Parameter*)(GetNode(0)->GetPt()))->GetExpr())->eval( ) ;
 		ret *= GetCoeff();	// 不能忘记了乘系数
 		return ret ;
 	}
	else
	{ 
		double ret = 0.0 ; 
		double tmp = 0.0;
		int op = GetOpType();
		if (GetSize() == 0) 
		{  
			throw ErrNotPermitted(5, "BasicExpression", "Eval", GetVarName(), 
				"non-leaf expressions without subnodes", 
				HELPURL);
		}
		switch(op) 
		{
		case SUM:
			for(int i = 0; i < GetSize(); i++)
			{
				ret += GetNode(i)->eval();
			}
			ret *= GetCoeff();
			break;
		case OPT_DIFFERENCE:
			for(int i = 0; i < GetSize(); i++) 
			{
				ret -= GetNode(i)->eval();
			}
			ret *= GetCoeff();
			break;
		case PRODUCT:
			ret = 1;
			for(int i = 0; i < GetSize(); i++) 
			{
				ret *= GetNode(i)->eval();
			}
			ret *= GetCoeff();
			break;
		case FRACTION:
			if (GetSize() != 2)
			{
				cerr << "BasicExpression::Eval: in [GetSize()!=2]: "
					<< "fractions should have just 2 operands, but going ahead "
					<< "anyway...\n";
				//throw ErrNotPermitted(1, "BasicExpression", "Eval", "GetSize()!=2", 
				//"fractions should have just 2 operands", 
				//HELPURL);
			}
			for(int i = 0; i < GetSize(); i++)
			{
				tmp = GetNode(i)->eval();
				if (i > 0 && tmp == 0) 
				{
					cerr << "BasicExpression::Eval: division by zero not allowed (node "
						<< i << " evaluates to 0), setting to a large value" << endl;
					//throw ErrDivideByZero(2, "BasicExpression", "Eval", "divisor==0", 
					//"division by zero not allowed", HELPURL);
					tmp = Ev3NearZero();
				}
				if (i == 0) 
					ret = tmp;
				else 
					ret /= tmp;
			}
			ret *= GetCoeff();
			break;
		case POWER:
			if (GetSize() != 2)
			{
				cerr << "BasicExpression::Eval: in [GetSize()!=2]: "
					<< "powers should have just 2 operands, but going ahead "
					<< "anyway...\n";
				//throw ErrNotPermitted(3, "BasicExpression", "Eval", "GetSize()!=2", 
				//"powers should have just 2 operands", 
				//HELPURL);
			}
			ret = GetNode(0)->eval();
			for(int i = 1; i < GetSize(); i++)
			{
				ret = pow(ret, GetNode(i)->eval());
			}
			ret *= GetCoeff();
			break;
			// for all unary functions - should check that GetSize() == 1
		case PLUS:
			ret = GetCoeff() * GetNode(0)->eval();
			break;
		case MINUS:
			ret = -GetCoeff() * GetNode(0)->eval();
			break;
		default:
			ret = 0.0;//永远不应该执行到这里
		}
		return ret;
	}
}

void BasicExpression::ConsolidateProductCoeffs(void) 
{
	if (GetOpType() == PRODUCT)
	{
		Int i;
		double tc = GetCoeff();
		for (i = 0; i < GetSize(); i++)
		{
			tc *= GetNode(i)->GetCoeff();
			GetNode(i)->SetCoeff(1);
		}
		if (fabs(tc) < Ev3NearZero())
		{
			Zero();
		} 
		else 
		{
			SetCoeff(tc);
		}
	}
}

void BasicExpression::DistributeCoeffOverSum(void)
{
	if (GetOpType() == SUM) 
	{
		double tc = GetCoeff();
		if (tc != 1) 
		{
			SetCoeff(1);
			Int i;
			for(i = 0; i < GetSize(); i++) 
			{
				GetNode(i)->SetCoeff(tc * GetNode(i)->GetCoeff());
				GetNode(i)->DistributeCoeffOverSum();
			}
		}
	}
}

void BasicExpression::DistributeCoeffOverProduct(void) 
{
	if (GetOpType() == PRODUCT) 
	{
		double tc = GetCoeff();
		if (tc != 1) 
		{
			SetCoeff(1);
			Int i;
			for(i = 0; i < GetSize(); i++) 
			{
				GetNode(i)->SetCoeff(tc * GetNode(i)->GetCoeff());
				GetNode(i)->DistributeCoeffOverProduct();
			}
		}
	}
}

// recursive destroy - deleted all the tree and nodes in a tree - use
// with caution
void RecursiveDestroy(Expression* a) 
{
	int i;
	for(i = 0; i < (*a)->GetSize(); i++) 
	{
		RecursiveDestroy((*a)->GetNodePtr(i));
	}
	a->Destroy();
}