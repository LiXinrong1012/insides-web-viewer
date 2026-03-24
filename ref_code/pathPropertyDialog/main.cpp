#include "pathpropertydialog.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PathPropertyDialog w;
	w.show();
	return a.exec();
}
