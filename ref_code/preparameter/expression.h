#pragma once

#include "exceptions.h"
#include "common.h"
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "tree.h"

#define RCS5 "$Id: expression.h,v 1.25 2006/07/30 05:36:41 liberti Exp liberti $"

using namespace std;

class FunctionsManager;
class BaseFunction;

////////////// MEMCHECK debug ////////////////////
#ifdef MEMDEBUG
extern vector<pair<void*,pair<int,int*> > > memcheckdebug;
extern vector<pair<void*,pair<int,int*> > >::iterator memcheckdebugit;
extern pair<void*, pair<int, int*> > memcheckdebugpair;
extern int memcheckdebugcounter;
#endif
///////////// END MEMCHECK debug ////////////////

// algebraic expression operand
class Operand 
{
	//新增添的方法
public:
	void *mpt;//当类型为Marker节点的时候存储Marker的指针

	void SetPt(void * p);
	void *GetPt();

	bool IsPointer() const;
	bool IsNotPointer() const;

protected:
	// one of the OperatorTypes above
	int oplabel;

	// if oplabel == VAR, the name of the variable
	string varname;//存储function的名字

	// 0 if no dependency, 1 if constant, 2 if coefficient, 3 if exponent
	int dependency;

public:
	// if oplabel == OPT_CONST, the value of the constant
	double constant;

protected:
	// dependency for constants (added for MORON - see ../PROGNOTES)
	double* depconstant;

	// if oplabel == VAR, the index of the variable - should start from 1
	Int varindex;//time时为-1，marker时为对应体在relNode中的索引

protected:
	// we allow multiplication for a constant coefficient in each Operand
	double coefficient;

	// dependency for coefficients (added for MORON - see ../PROGNOTES)
	double* depcoefficient;

	// we allow a real constant exponent in each Operand
	// THIS HAS MEANING ONLY IF operand IS A LEAF!!!
	double exponent;

	// dependency for exponents (added for MORON - see ../PROGNOTES)
	double* depexponent;

	// interval associated to the values of this node (used in FBBT)
	double lb;
	double ub;

	BaseFunction* baseFunction;

public:

	// constructors
	Operand();
	Operand(const double t);
	Operand(const Int t);
	Operand(const Int t, const bool isvar);
	// create a variable leaf and set coefficient
	Operand(const double c, const Int t, string vn);

	// copy constructor
	Operand(Operand& t);

	// destructor
	~Operand();

	// Operand class methods:
	// get constant value - in CONSTs it multiplies by coefficient and
	// raises to exponent
	double GetValue(void) const;

	// get variable index
	Int GetVarIndex(void) const;

	// get the coefficient
	double GetCoeff(void) const;

	// get the exponent
	double GetExponent(void) const;

	// set operator type
	void SetOpType(const int t);

	// 更改常数值
	int SetConstValue(double val ) ;

	// get operator type
	int		GetOpType(void) const;
	string  GetVarName(void) const;

	// set constant value
	void SetValue(const double t);  

	// set variable index (start from 1 and add by steps of 1 when creating new
	// variables)
	void SetVarIndex(const Int t);

	// set variable name
	void SetVarName(const string vn);

	// set the exponent
	void SetExponent(const double expon);

	// set the coefficient
	void SetCoeff(const double coeff);

	// is operand a constant?
	bool IsConstant(void) const;

	// is operand a variable?
	bool IsVariable(void) const;

	// is operand a leaf node?
	bool IsLeaf(void) const;

	// is operand a zero constant?
	//只在判断值是否在零附近时用。
	bool IsZero(void) const;

	// is operand a constant == v?
	bool HasValue(double v) const;

	BaseFunction* getFunction()const{return baseFunction;}
	void setFunction(BaseFunction* func){baseFunction=func;}
};

class BasicExpression;

typedef Pointer<BasicExpression> Expression;

class BasicExpression : public Operand, public Tree<BasicExpression>
{

public:
	// constructors

	// create empty
	BasicExpression();

	// create a constant leaf
	BasicExpression(const double t);

	// create a constant (integer-valued) leaf
	BasicExpression(const Int t);

	// create an (empty) operator or a variable leaf
	BasicExpression(const Int t, const bool isvar);

	// create a variable leaf and set coefficient
	BasicExpression(const double c, const Int t, string vn);

	// user-defined copy constructor with two options (to make a copy)
	BasicExpression(const Expression& t, const bool iscopy);

	// copy constructor
	BasicExpression(BasicExpression& t);

	// destructor
	~BasicExpression();

	// sets an expression to zero (deleting all existing subnodes)
	void Zero(void);

	// sets an expression to one (deleting all existing subnodes)
	void One(void);

	// is expression this == expression t?
	// (note that this half-replicates Tree::operator==,
	//  but I couldn't think of any other convenient way to fit in
	//  the operand data in == and still use the Tree's ==)
	bool IsEqualTo(const Expression& t) const;
	//bool operator == (const BasicExpression& t) const;

	// this returns true if args are equal up to top node coefficient
	bool IsEqualToNoCoeff(const Expression& t) const;

	//计算函数，用mode确定计算的方式
	//EVAL_B_MODE是计算b时用的方式，需要指定全部的q
	//EVAL_A_MODE是计算A时用的方式，需要指定所用的q
	double eval( );

	// in a product, multiply all coeffs. of the operands, set result
	// as coeff of whole product, reset all operand coffs at 1; if
	// resulting global coeff is zero, delete all nodes and set 
	// this to zero constant.
	// don't do anything on other operators
	void ConsolidateProductCoeffs(void);

	// in a sum or product, if coeff of sum operand is not 1, distribute it
	// to the operands and set whole coeff to 1
	void DistributeCoeffOverSum(void);
	void DistributeCoeffOverProduct(void);
};

// destroys the whole tree and all nodes, be careful
void RecursiveDestroy(Expression* a);