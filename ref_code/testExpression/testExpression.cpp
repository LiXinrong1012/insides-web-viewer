
#include <QtCore/QCoreApplication>

#include "preparameter/expression.h"
#include "preparameter/expressionparser.h"
#include "preparameter/Parameter.h"

#include "preparameter/BasicMathFunc.h"

#include "prevtc/resultexpressionparser.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	string t1("1+2*sin(2)");
	Expression expression;
	//Parameter para;

	ResultExpressionParser resultParser;
	resultParser.Parse(expression,t1.c_str());
	double va=expression->eval();

	cout<<va<<endl;
	

	return a.exec();
}
