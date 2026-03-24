#include "testsearchwidget.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testSearchWidget w;
	w.show();
	return a.exec();
}
