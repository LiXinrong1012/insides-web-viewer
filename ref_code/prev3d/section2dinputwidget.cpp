#include "section2dinputwidget.h"
#include "ui_section2dinputwidget.h"

Section2DInputWidget::Section2DInputWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::Section2DInputWidget();
	ui->setupUi(this);
}

Section2DInputWidget::~Section2DInputWidget()
{
	delete ui;
}

