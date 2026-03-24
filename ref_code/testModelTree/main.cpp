#include "testmodeltree.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testModelTree w;
	w.show();
	return a.exec();
}
