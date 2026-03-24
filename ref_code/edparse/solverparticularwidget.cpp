#include "solverparticularwidget.h"
#include "ui_solverparticularwidget.h"

SolverParticularWidget::SolverParticularWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::SolverParticularWidget();
	ui->setupUi(this);
}

SolverParticularWidget::~SolverParticularWidget()
{
	delete ui;
}

