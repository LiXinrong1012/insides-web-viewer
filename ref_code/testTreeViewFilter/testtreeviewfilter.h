#ifndef TESTTREEVIEWFILTER_H
#define TESTTREEVIEWFILTER_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include <QtCore>
#include "ui_testtreeviewfilter.h"

class ProxyFilterModel;

class testTreeViewFilter : public QMainWindow
{
	Q_OBJECT

public:
	testTreeViewFilter(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testTreeViewFilter();

public slots:
	void filterChanged();
private:
	Ui::testTreeViewFilterClass ui;

	QStandardItemModel*	_model;
	ProxyFilterModel*	_proxy;
};

#endif // TESTTREEVIEWFILTER_H
