#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(TableSetting& setting,QWidget *parent)
	: QDialog(parent)
	,_setting(&setting)
{
	ui = new Ui::SettingDialog();
	ui->setupUi(this);

	ui->doubleCountSpinBox->setValue(_setting->doubleCount);

	connect(ui->cancelPushButton,SIGNAL(clicked()),this,SLOT(onCancel()));
	connect(ui->savePushButton,SIGNAL(clicked()),this,SLOT(onSave()));
}

SettingDialog::~SettingDialog()
{
	delete ui;
}

void SettingDialog::onSave()
{
	_setting->doubleCount = ui->doubleCountSpinBox->value();
	this->close();
}

void SettingDialog::onCancel()
{
	this->close();
}

