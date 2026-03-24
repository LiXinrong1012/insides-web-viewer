#include "testsorttable.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testSortTable w;
	w.show();
	return a.exec();
}
