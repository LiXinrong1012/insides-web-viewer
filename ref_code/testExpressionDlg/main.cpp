#include "testexpressiondlg.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testExpressionDlg w;
	w.show();
	return a.exec();
}
