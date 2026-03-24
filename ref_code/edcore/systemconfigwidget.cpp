#include "systemconfigwidget.h"
#include "ui_systemconfigwidget.h"

SystemConfigWidget::SystemConfigWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::SystemConfigWidget();
	ui->setupUi(this);
}

SystemConfigWidget::~SystemConfigWidget()
{
	delete ui;
}

bool SystemConfigWidget::isAutoUpdate()
{
	return ui->autoUpdateCheckBox->isChecked();
}

void SystemConfigWidget::setAutoUpdate(bool b)
{
	ui->autoUpdateCheckBox->setChecked(b);
}

