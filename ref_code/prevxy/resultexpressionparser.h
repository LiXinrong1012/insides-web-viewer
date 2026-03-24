#ifndef RESULTEXPRESSIONPARSER_H
#define RESULTEXPRESSIONPARSER_H

#include "prevxy_global.h"
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

	///获得表达式内容
	string getExpressionStr() { return m_strExpression; } ;

public:
	///测试类
	TestMyClass		_myClass;

protected:
	/* DealWithName 用来处理名字, 名字可以是 Marker, basic Function, user defined function */
	virtual int		dealWithName ( Expression& ret, const std::string& name ) ;

	///获得错误信息
	virtual string  getErrorMessage() const; ; 

	///清除所有
	void clear();

	///获得相关的结果条目
	INSIDES::IResultItem* getRelatedResultItem(const QString& itemName);

protected:
	///结果列表
	typedef QList<INSIDES::IResultItem*> ResultItemList;

	///表达式
	Expression		_expr;

	///用来存放表达式内容
	string		m_strExpression ;

	// return error message
	string		m_strErr ;	

	///结果条目列表
	ResultItemList	_relatedResultItems;

	///用来记录当前时间
	double		m_time;

private:
	///初始化常数
	void	InitialConstant() ;

private:
	// 用于存储常数
	static map<string, double>	_constTable;		

	///函数管理 ？
	static FunctionsManager		_functionManager;

	///是否已进行初始化
	static bool					_initialized;

private:
	
};

#endif // RESULTEXPRESSIONPARSER_H
