#include "timecurveresultselectorwidget.h"
#include "ui_resultselectorwidget.h"

#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"
#include "precore/ResultDocument.h"

#include "precore/BaseItem.h"
#include "precore/precore_data.h"

TimeCurveResultSelectorWidget::TimeCurveResultSelectorWidget(QWidget *parent)
	: ResultSelectorWidget(parent)
{
	connect(this,SIGNAL(selectionIndexChanged()),
		this, SLOT(onSubItemChanged()));

	connect(ui->cbSubSection,SIGNAL(currentIndexChanged(int)),
		this,SLOT(onSubsubItemChanged()));

}

TimeCurveResultSelectorWidget::~TimeCurveResultSelectorWidget()
{

}

void TimeCurveResultSelectorWidget::protected_onOK()
{

}

void TimeCurveResultSelectorWidget::onSubItemChanged()
{
	IResultItem* item=getCurrentBaseItem();
	if(!item || !item->connectedItem()){
		ui->cbSubSection->setHidden(true);
		ui->cbSubsubSection->setHidden(true);
		return;
	}

	int subSectionCount=item->subSectionCount(ui->cbSection->currentIndex());
	ui->cbSubSection->clear();
	for(int i=0;i<subSectionCount;++i){
		QString secName=item->subSectionName(ui->cbSection->currentIndex(),i);
		ui->cbSubSection->addItem(secName);
	}

	onSubsubItemChanged();
}

void TimeCurveResultSelectorWidget::onSubsubItemChanged()
{
	IResultItem* item=getCurrentBaseItem();
	if(!item )
		return;

	int subSectionCount=item->subsubSectionCount(ui->cbSection->currentIndex(),
		ui->cbSubSection->currentIndex());

	ui->cbSubsubSection->clear();
	for(int i=0;i<subSectionCount;++i){
		QString secName=item->subsubSectionName(ui->cbSection->currentIndex(),
			ui->cbSubSection->currentIndex(),i);
		ui->cbSubsubSection->addItem(secName);
	}
}
