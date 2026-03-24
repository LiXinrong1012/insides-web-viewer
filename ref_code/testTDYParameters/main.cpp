
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QtCore>
#include <iostream>
#include <string>

using namespace std;

#include "pretdy/TDYParameters.h"

struct MyClass
{
	QString aaa;
	int aakj;

};
void Write()
{
	QFile file("D:/file.dat");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	out << QString("the answer is");
	out << (qint32)42;
	file.close();

}

void Read()
{
	QFile file("D:/file.dat");
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	QString str;
	qint32 aa;
	in>>str>>aa;
	qDebug("%d",aa);
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Write();
	Read();

	TDYParameters* paras=new TDYParameters();
	TDYParameterItem item;
	item.keyname="A";
	item.strPara="sin(PI/3)";
	paras->add(item);
	item.keyname="B";
	item.strPara="2*$A";
	paras->add(item);

	cout<<paras->getValue("A")<<endl;
	cout<<paras->getValue("B")<<endl;
	cout<<paras->getValue("A+B")<<endl;

	return a.exec();
}
