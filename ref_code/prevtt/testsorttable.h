#ifndef TESTSORTTABLE_H
#define TESTSORTTABLE_H

#include <QtGui/QDialog>
#include "ui_testsorttable.h"

class testSortTable : public QDialog
{
	Q_OBJECT

public:
	testSortTable(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testSortTable();

	private slots:

	void onContextMenu(const QPoint & pos);
private:
	Ui::testSortTableClass ui;
};

#endif // TESTSORTTABLE_H
