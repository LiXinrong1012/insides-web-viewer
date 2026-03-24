#include "testexpressiondlg.h"

#include "parameterswidget.h"
#include "testparadlg.h"

testExpressionDlg::testExpressionDlg(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	//_testParameter.add("A","1");
//	_testParameter.add("B","sin(PI)");
	//_testParameter.add("C","2*$A");
}

testExpressionDlg::~testExpressionDlg()
{

}

void testExpressionDlg::onOpen()
{
	TestParaDlg dlg(this);
//	QList<TDYParameterItem> items=_testParameter.getAll();
	// °Ñitems´«¸ødlg
	dlg.exec();
}


