#pragma once
#include "expression.h"
#include <map>

class  Parameter ;

class BaseFunction 
{
public:
	BaseFunction()	{ m_iNumOfPara = 1; };
	~BaseFunction() {};

public:
	int					m_iNumOfPara  ;
	string				m_strFuncName ;

public:
	virtual Expression	FuncLink	( Expression Exprs[], const int nPara ) throw(ErrNotPermitted)  ;

	virtual double		EvalValue	( BasicExpression& a  )   { return 0 ;} ;
};

/* 一下这段代码定义出一个基本函数库 */  
template<typename T> BaseFunction* createFunc()  { return new T;}

typedef map<string, BaseFunction*> map_Func ;
 
class FuncFactory
{
public:
	FuncFactory() {};
	~FuncFactory(){};
public:
	static BaseFunction* getFunction( string const& s )
	{
		map_Func::iterator it = getMap()->find(s) ;
		if ( it == getMap()->end() ) 
			return NULL ;
		return it->second ;
	}

	static bool find ( string const& s )
	{
		map_Func::iterator it = getMap()->find(s) ;
		if ( it == getMap()->end() )
			return false ;
		else
			return true ;
	}

protected:
	static map_Func* getMap() 
	{
		if ( !mapF ) mapF = new map_Func ;
		return mapF ;
	}

private:
	static map_Func* mapF ;
};

template<typename T>
struct FuncRegister : public FuncFactory
{
	FuncRegister()
	{
		BaseFunction* func = createFunc<T>() ;		
		getMap()->insert(std::make_pair(func->m_strFuncName, func)) ;
	}
};

#define REGISTER_DEC_FUNC(NAME) \
	static FuncRegister<NAME> reg_FUNCTION_##NAME

#define REGISTER_DEF_FUNC(NAME) \
	FuncRegister<NAME> NAME::reg_FUNCTION_##NAME