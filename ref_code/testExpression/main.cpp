
#include <QtCore/QCoreApplication>

#include "preparameter/expression.h"
#include "preparameter/expressionparser.h"
#include "preparameter/Parameter.h"

#include "preparameter/BasicMathFunc.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	string t1("1+2*sin(2)");
	Expression expression;
	ExpressionParser parser;
	Parameter para;
	parser.Parse(expression,t1.c_str(),&para);

	double va=expression->eval();

	cout<<va<<endl;
	

	return a.exec();
}
