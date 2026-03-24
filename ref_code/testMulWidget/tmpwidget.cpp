#include "tmpwidget.h"
#include "ui_tmpwidget.h"

TmpWidget::TmpWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::TmpWidget();
	ui->setupUi(this);
}

TmpWidget::~TmpWidget()
{
	delete ui;
}

