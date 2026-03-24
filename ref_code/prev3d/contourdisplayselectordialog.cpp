#include "contourdisplayselectordialog.h"
#include "ui_contourdisplayselectordialog.h"

ContourDisplaySelectorDialog::ContourDisplaySelectorDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::ContourDisplaySelectorDialog();
	ui->setupUi(this);
}

ContourDisplaySelectorDialog::~ContourDisplaySelectorDialog()
{
	delete ui;
}

ContourDisplaySelectorWidget* ContourDisplaySelectorDialog::getWidget()
{
	return ui->widget;
}

