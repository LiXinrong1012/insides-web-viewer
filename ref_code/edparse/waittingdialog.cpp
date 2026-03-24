#include "waittingdialog.h"
#include "ui_waittingdialog.h"

WaittingDialog::WaittingDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::WaittingDialog();
	ui->setupUi(this);

	connect(ui->okBtn,SIGNAL(clicked()),this,SLOT(onOkBtnClicked()));
}

WaittingDialog::~WaittingDialog()
{
	delete ui;
}

void WaittingDialog::onOkBtnClicked()
{
	this->close();
}

void WaittingDialog::setBtnEnable( bool b )
{
	ui->okBtn->setEnabled(b);
}

