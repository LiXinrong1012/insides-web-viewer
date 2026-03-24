#ifndef RESULTEXPRESSIONPARSER_H
#define RESULTEXPRESSIONPARSER_H

#include "prevtc_global.h"

#include "preparameter/expressionparser.h"
#include "preparameter/functionsmanager.h"

#include <list>
#include <QString>
#include <QList>

class TestMyClass
{
public:
	int value;

	TestMyClass():value(0){}
};

namespace INSIDES{
	class IResultItem;
}

/*!
	Used to parse expression about results.
	@author	Jerry He
	@date	2014.10.11
*/
class ResultExpressionParser : public ExpressionParser
{
public:
	ResultExpressionParser();
	~ResultExpressionParser();

	// eval 返回计算后的参数值
	double		eval (  );

	/// 设置表达式并计算
	bool setExpressionStr(const string& input);

	/// 设置结果数据位置
	void setPos(int currentIndex);

	///设置时间
	void setTime(double time){m_time=time;}

	///获得表达式
	string getExpressionStr() { return m_strExpression; } ;

public:
	TestMyClass		_myClass;

protected:
	/* DealWithName 用来处理名字, 名字可以是 Marker, basic Function, user defined function */
	virtual int		dealWithName ( Expression& ret, const std::string& name ) ;

	///获得错误信息
	virtual string  getErrorMessage() const; ; 

	///清除所有结果条目
	void clear();

	///通过条目名获得对应结果条目
	INSIDES::IResultItem* getRelatedResultItem(const QString& itemName);

protected:
	typedef QList<INSIDES::IResultItem*>	ResultItemList;
	Expression								_expr;
	string									m_strExpression ;
	string									m_strErr ;	// return error message
	ResultItemList							_relatedResultItems;
	double									m_time;					

private:
	///初始常量
	void	InitialConstant() ;

private:
	/// 用于存储常数
	static map<string, double>	_constTable;	

	///函数管理？
	static FunctionsManager		_functionManager;

	///是否已初始化
	static bool					_initialized;
};

#endif // RESULTEXPRESSIONPARSER_H
