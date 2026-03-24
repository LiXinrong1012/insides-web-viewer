#include "solveconfigwidget.h"
#include "ui_solveconfigwidget.h"

SolveConfigWidget::SolveConfigWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::SolveConfigWidget();
	ui->setupUi(this);
}

SolveConfigWidget::~SolveConfigWidget()
{
	delete ui;
}

int SolveConfigWidget::getLogsSpinBoxValue()
{
	return ui->logsSpinBox->value();
}

void SolveConfigWidget::setLogsSpinBoxValue(int value)
{
	ui->logsSpinBox->setValue(value);
}

int SolveConfigWidget::getTreeSpinBoxValue()
{
	return ui->treeSpinBox->value();
}

void SolveConfigWidget::setTreeSpinBoxValue(int value)
{
	ui->treeSpinBox->setValue(value);
}

int SolveConfigWidget::getMaxSolveNumber()
{
	return ui->maxSolveSpinBox->value();
}

void SolveConfigWidget::setMaxSolveNumber(int value)
{
	ui->maxSolveSpinBox->setValue(value);
}

bool SolveConfigWidget::isShowSolver()
{
	return ui->isShowSolverCheckBox->isChecked();
}

void SolveConfigWidget::setIsShowSolver(bool b )
{
	ui->isShowSolverCheckBox->setChecked(b);
}

