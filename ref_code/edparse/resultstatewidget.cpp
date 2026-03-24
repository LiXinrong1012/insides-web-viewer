#include "resultstatewidget.h"

ResultStateWidget::ResultStateWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setNoResult();
}

ResultStateWidget::~ResultStateWidget()
{
}

void ResultStateWidget::hideAll()
{
	ui._stateNoResult->hide();
	ui._stateResult->hide();
	ui._stateRunning->hide();
}

void ResultStateWidget::setNoResult()
{
	hideAll();
	ui._stateNoResult->show();
}

void ResultStateWidget::setHasResult()
{
	hideAll();
	ui._stateResult->show();
}

void ResultStateWidget::setRunningProgress( int progress )
{
	ui._stateRunning->setValue(progress);
}

void ResultStateWidget::startRunning()
{
	hideAll();
	ui._stateRunning->show();
}

void ResultStateWidget::endRunning()
{
	hideAll();
	ui._stateResult->show();
}
