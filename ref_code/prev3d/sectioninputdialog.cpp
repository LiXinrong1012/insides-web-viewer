#include "sectioninputdialog.h"
#include "ui_sectioninputdialog.h"

SectionInputDialog::SectionInputDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::SectionInputDialog();
	ui->setupUi(this);
}

SectionInputDialog::~SectionInputDialog()
{
	delete ui;
}

void SectionInputDialog::onOK()
{
	ui->widget->onOKClicked();
	this->accept();
}

QList<double> SectionInputDialog::getSection1DPoints()
{
	return ui->widget->get1DSectionPoints();
}

QList<double> SectionInputDialog::getSection1DParameters()
{
	return ui->widget->get1DParameters();
}

