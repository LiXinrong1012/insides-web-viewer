#ifndef TESTMODELTREE_H
#define TESTMODELTREE_H

#include <QtGui/QMainWindow>
#include "ui_testmodeltree.h"

class testModelTree : public QMainWindow
{
	Q_OBJECT

public:
	testModelTree(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testModelTree();

private:
	Ui::testModelTreeClass ui;
};

#endif // TESTMODELTREE_H
