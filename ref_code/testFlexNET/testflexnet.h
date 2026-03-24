#ifndef TESTFLEXNET_H
#define TESTFLEXNET_H

#include <QtGui/QDialog>
#include "ui_testflexnet.h"

class testFlexNET : public QDialog
{
	Q_OBJECT

public:
	testFlexNET(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testFlexNET();

private:
	Ui::testFlexNETClass ui;
};

#endif // TESTFLEXNET_H
