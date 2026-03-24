#include "testmulwidget.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testMulWidget w;
	w.show();
	return a.exec();
}
