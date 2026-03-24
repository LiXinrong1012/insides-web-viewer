
#include <QtCore/QCoreApplication>

#include <QtCore>

#include "../precore/itemlist.h"
#include "../precore/precore_data.h"
#include "../pp_xml/BulkProp.h"

#include <iostream>
#include <string>
using namespace std;


int main(int argc, char *argv[])
{
	pp::BulkProp props;
	props.SetString("NAME","HAHAH123");
	props.SetString("Pos","1,\" \"2,3");
	props.SetLong("COUNT",10);

	qDebug()<<props.Composite()<<endl;

	pp::BulkProp prop2;
	prop2.Parse(props.Composite());
	qDebug()<<prop2.GetString("Pos")<<endl;


	QCoreApplication a(argc, argv);

	return a.exec();
}
