#include "testparadlg.h"
#include "ui_testparadlg.h"

TestParaDlg::TestParaDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::TestParaDlg();
	ui->setupUi(this);
}

TestParaDlg::~TestParaDlg()
{
	delete ui;
}

