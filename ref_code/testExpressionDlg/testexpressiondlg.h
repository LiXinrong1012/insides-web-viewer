#ifndef TESTEXPRESSIONDLG_H
#define TESTEXPRESSIONDLG_H

#include <QtGui/QMainWindow>
#include "ui_testexpressiondlg.h"
namespace Ui {class testExpressionDlg;};

class testExpressionDlg : public QMainWindow
{
	Q_OBJECT

public:
	testExpressionDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testExpressionDlg();


public slots:
	void onOpen();

private:
	Ui::testExpressionDlg ui;
};

#endif // TESTEXPRESSIONDLG_H
