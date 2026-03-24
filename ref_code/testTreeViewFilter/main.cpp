#include "testtreeviewfilter.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testTreeViewFilter w;
	w.show();
	return a.exec();
}
