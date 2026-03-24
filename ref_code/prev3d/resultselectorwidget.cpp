#include "resultselectorwidget.h"
#include "ui_resultselectorwidget.h"

#include "base/Console.h"

#include "precore/projectselector.h"
#include "precore/BaseItem.h"
#include "precore/BaseItemHelper.h"

#include "precore/ResultDocument.h"
#include "precore/IResultItem.h"



ResultSelectorWidget::ResultSelectorWidget(QWidget *parent)
	: QWidget(parent)
	,_lastSubIndex(0)
{
	ui = new Ui::ResultSelectorWidget();
	ui->setupUi(this);

	myProjectSelector()->attachSupplier(this);	
	setSupplierName("ResultSelector");

	connect(ui->cbItem,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onCurrentItemChanged()));

	connect(ui->cbSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(oncbSelectionChanged()));


	onResultsImported();
}

ResultSelectorWidget::~ResultSelectorWidget()
{
	myProjectSelector()->disattachSupplier(this);

	delete ui;
}

void ResultSelectorWidget::ss_onSetClicked_projected( BaseItem* item )
{
	QVariant var( (qlonglong)(item));
	int index=ui->cbItem->findData(var);

	if(index!=-1)
		ui->cbItem->setCurrentIndex(index);
}
void ResultSelectorWidget::ss_onSetSelection_protected( const BaseItemSelection& items)
{
	if(items.size()==0)
		return;

	ss_onSetClicked_projected(items[0]);
}

void ResultSelectorWidget::onOK()
{
	protected_onOK();
}

void ResultSelectorWidget::onResultsImported()
{
	ResultDocument* resDoc=myResultDocument();
	IResults* res=resDoc->getResults();
	if(!res){
		ui->cbItem->clear();
		return;
	}

	IResults::ResultMap& allRes=res->getResults();
	for(IResults::ResultMap::Iterator b=allRes.begin();
		b!=allRes.end();++b){
			BaseItem* item=b.key();
			QIcon icon=BaseItemHelper::getBaseItemIcon(item);
			QVariant var((qlonglong)b.key());
			ui->cbItem->addItem(icon,item->getFullName(),var);
	}
}

void ResultSelectorWidget::protected_onOK()
{
	Base::Console().Warning("No implementation");
}

void ResultSelectorWidget::onCurrentItemChanged()
{
	IResultItem* resItem=getCurrentBaseItem();
	if(resItem){
		_disableSubSection=true;
		int sectionCount=resItem->sectionCount();
		ui->cbSection->clear();
		for(int i=0;i<sectionCount;++i){
			QString secName=resItem->sectionName(i);
			ui->cbSection->addItem(secName);
		}
		_disableSubSection=false;

		if(_lastSubIndex<sectionCount)
			ui->cbSection->setCurrentIndex(_lastSubIndex);
	}

	emit selectionIndexChanged();
}

IResultItem* ResultSelectorWidget::getCurrentBaseItem()
{
	int index=ui->cbItem->currentIndex();
	if(index!=-1){
		QVariant var=ui->cbItem->itemData(index);
		BaseItem* item=(BaseItem*)var.toLongLong();

		IResults* res=myResultDocument()->getResults();
		IResults::ResultMap::Iterator f=res->getResults().find(item);
		if(f==res->getResults().end())
			return NULL;

		return f.value().data();
	}
	return NULL;
}

void ResultSelectorWidget::oncbSelectionChanged()
{
	if(_disableSubSection)
		return;

	if(ui->cbSection->currentIndex()!=-1)
		_lastSubIndex=ui->cbSection->currentIndex();

	emit selectionIndexChanged();
}



