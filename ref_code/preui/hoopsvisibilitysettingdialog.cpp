#include "hoopsvisibilitysettingdialog.h"
#include "ui_hoopsvisibilitysettingdialog.h"

HoopsVisibilitySettingDialog::HoopsVisibilitySettingDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::HoopsVisibilitySettingDialog();
	ui->setupUi(this);
}

HoopsVisibilitySettingDialog::~HoopsVisibilitySettingDialog()
{
	delete ui;
}

