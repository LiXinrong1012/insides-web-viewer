#include "ftpconfigdialog.h"
#include "ui_ftpconfigdialog.h"

#include <QMessageBox>

FtpConfigDialog::FtpConfigDialog(QWidget *parent,const FtpConfig& config)
	: QDialog(parent)
	,_okBtnClicked(false)
{
	ui = new Ui::FtpConfigDialog();
	ui->setupUi(this);

	ui->hostLineEdit->setText(config._host);
	ui->userIdLineEdit->setText(config._userId);
	ui->passwordLineEdit->setText(config._password);
	ui->ftpRootLineEdit->setText(config._ftpRootDir);

	connect(ui->okBtn,SIGNAL(clicked()),this,SLOT(onOkBtnClicked()));
}

FtpConfigDialog::~FtpConfigDialog()
{
	delete ui;
}

FtpConfig FtpConfigDialog::getConfig()
{
	FtpConfig config(ui->hostLineEdit->text()
		,ui->userIdLineEdit->text()
		,ui->passwordLineEdit->text()
		,ui->ftpRootLineEdit->text());

	return config;
}

void FtpConfigDialog::onOkBtnClicked()
{
	if(ui->hostLineEdit->text().isEmpty())
	{
		QMessageBox::information(this,"Error","The host is empty,save faild.");
		ui->hostLineEdit->setFocus();
		return;
	}

	_okBtnClicked = true;
	this->close();
}

