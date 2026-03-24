#include "solutionpropertywidget.h"
#include "ui_solutionpropertywidget.h"

SolutionPropertyWidget::SolutionPropertyWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::SolutionPropertyWidget();
	ui->setupUi(this);
}

SolutionPropertyWidget::~SolutionPropertyWidget()
{
	delete ui;
}

