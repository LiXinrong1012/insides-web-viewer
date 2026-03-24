#ifndef TESTMULWIDGET_H
#define TESTMULWIDGET_H

#include <QtGui/QMainWindow>
#include "ui_testmulwidget.h"

class testMulWidget : public QMainWindow
{
	Q_OBJECT

public:
	testMulWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testMulWidget();

protected slots:
	void onNew();

	void onSaveState();
	void onLoadState();

private:
	Ui::testMulWidgetClass ui;
};

#endif // TESTMULWIDGET_H
