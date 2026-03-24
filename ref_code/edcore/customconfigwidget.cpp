#include "customconfigwidget.h"
#include "ui_customconfigwidget.h"

CustomConfigWidget::CustomConfigWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::CustomConfigWidget();
	ui->setupUi(this);
}

CustomConfigWidget::~CustomConfigWidget()
{
	delete ui;
}

bool CustomConfigWidget::isShowLastFiles()
{
	return ui->showLastFilesCheckBox->isChecked();
}

void CustomConfigWidget::setIsShowLastFiles(bool b)
{
	ui->showLastFilesCheckBox->setChecked(b);
}

bool CustomConfigWidget::isCreateModelTree()
{
	return ui->createModelTreeCheckBox->isChecked();
}

void CustomConfigWidget::setIsCreateModelTree(bool b)
{
	ui->createModelTreeCheckBox->setChecked(b);
}

bool CustomConfigWidget::isAutoShowHelp()
{
	return ui->autoHelpCheckBox->isChecked();
}

void CustomConfigWidget::setIsAutoShowHelp( bool b )
{
	ui->autoHelpCheckBox->setChecked(b);
}

