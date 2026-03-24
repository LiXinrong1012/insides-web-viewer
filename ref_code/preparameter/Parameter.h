#pragma once
#include "expressionparser.h"
#include "expression.h"
#include <string>

class FunctionsManager;

class Parameter : public ExpressionParser
{
public:
	virtual string GetTypeName() { return "PARAMETER"; };

	Parameter();
	Parameter(Parameter & f);
	~Parameter();
	
	// eval 返回计算后的参数值
	double		eval (  );
	
	// 如果 fmap  = NULL，则初始化的是参数，可以是数学函数表达式，但不能是其他参数的函数
	// 如果 fmap != NULL，则可以是其他参数的函数，用于初始化模型
	int		strToPara (const string& strFun, map<string, Parameter *> *fmap  = NULL );		// 用于参数化建模

	
	string getExpression() { return m_strExpression; } ;


private:
	string m_strExpression ;
	map<string, Parameter*>*	m_existParaMap  ;

	static map<string, double>*	table;		// 用于存储常数

	void	InitialConstant() ;

protected:
	Expression* _expr;

public:
	Expression&	GetExpr();

protected:
	/* DealWithName 用来处理名字, 名字可以是 Marker, basic Function, user defined function */
	virtual int		dealWithName ( Expression& ret, const std::string& name ) ;

private:
	void		SetRelNode ( Expression& ept );
	Parameter*	GetExistParaPt	( string ename ) ;

protected:
	string		m_strErr ;	// return error message

	FunctionsManager* _functionManager;

public:
	int		changeConstValue ( double val ) ;
	string  getErrorMsg () { return m_strErr; } ; 
};