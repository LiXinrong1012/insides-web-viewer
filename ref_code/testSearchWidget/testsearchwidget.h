#ifndef TESTSEARCHWIDGET_H
#define TESTSEARCHWIDGET_H

#include <QtGui/QDialog>
#include "ui_testsearchwidget.h"
#include "edparse/searchkeywidget.h"

class testSearchWidget : public QDialog
{
	Q_OBJECT

public:
	testSearchWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testSearchWidget();
	public slots:
		void onBtnClicked();

private:
	Ui::testSearchWidgetClass ui;
	SearchKeyWidget *s;
};

#endif // TESTSEARCHWIDGET_H
