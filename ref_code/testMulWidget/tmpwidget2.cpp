#include "tmpwidget2.h"
#include "ui_tmpwidget2.h"

TmpWidget2::TmpWidget2(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::TmpWidget2();
	ui->setupUi(this);
}

TmpWidget2::~TmpWidget2()
{
	delete ui;
}

