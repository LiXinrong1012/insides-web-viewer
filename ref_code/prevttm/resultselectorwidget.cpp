#include "resultselectorwidget.h"
#include "ui_resultselectorwidget.h"

#include "base/Console.h"
#include "base/activeviewobject.h"

#include "precore/projectselector.h"
#include "precore/BaseItem.h"
#include "precore/BaseItemHelper.h"

#include "precore/ResultDocument.h"
#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"

#include "precore/precore_data.h"



ResultSelectorWidget::ResultSelectorWidget(QWidget *parent)
	: QWidget(parent)
	,_parentView(NULL)
	,_IsOperatingUI(false)
{
	ui = new Ui::ResultSelectorWidget();
	ui->setupUi(this);

	clearAll();

	connect(ui->cbItem,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onCurrentItemChanged()));

	connect(ui->cbSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(oncbSelectionChanged()));


	res_ResultsLoaded(myResultDocument()->getResults());

	myResultDocument()->attachListener(this);
}

ResultSelectorWidget::~ResultSelectorWidget()
{
	myResultDocument()->disattachListener(this);

	delete ui;
}

void ResultSelectorWidget::setCurrentBaseItem( BaseItem* item )
{
	QVariant var( (qlonglong)(item));
	int index=ui->cbItem->findData(var);

	if(index!=-1)
		ui->cbItem->setCurrentIndex(index);
}


void ResultSelectorWidget::res_ResultsLoaded(IResults* results)
{
	_IsOperatingUI=true;
	updateItems();
	_IsOperatingUI=false;

	TableItemTitle title=getTableItemTitle();
	emit notifyUpdate(title);
}


TableItemTitle ResultSelectorWidget::getTableItemTitle()
{
	TableItemTitle title;
	title.itemName=getCurrentItemName();
	title.secIndex=ui->cbSection->currentIndex();

	return title;
}

void ResultSelectorWidget::emit_itemAdding()
{
	TableItemTitle title=getTableItemTitle();
	emit itemAdding(title);
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

void ResultSelectorWidget::onCurrentItemChanged()
{
	if(_IsOperatingUI)
		return;

	_IsOperatingUI=true;

	updateSections();

	_IsOperatingUI=false;

	emit_itemAdding();
}


void ResultSelectorWidget::oncbSelectionChanged()
{
	if(_IsOperatingUI)
		return;

	_IsOperatingUI=true;

	_IsOperatingUI=false;

	emit_itemAdding();
}



void ResultSelectorWidget::updateItems()
{
	ResultDocument* resDoc=myResultDocument();
	IResults* res=resDoc->getResults();
	if(!res){
		clearAll();
		return;
	}
	ui->cbItem->setVisible(true);
	ui->cbSection->setVisible(true);

	IResults::ResultMap& allRes=res->getResults();
	for(IResults::ResultMap::Iterator b=allRes.begin();
		b!=allRes.end();++b){
			BaseItem* item=b.key();
			QIcon icon=BaseItemHelper::getBaseItemIcon(item);
			QVariant var((qlonglong)b.key());
			ui->cbItem->addItem(icon,item->getFullName(),var);
	}
	if(ui->cbItem->count()>0)
		ui->cbItem->setCurrentIndex(0);

	updateSections();
}

void ResultSelectorWidget::updateSections()
{
	IResultItem* resItem=getCurrentBaseItem();
	if(resItem){
		BaseItem* baseItem=resItem->connectedItem();
		if(baseItem && baseItem->getCategory()==TDY_PRE_CATE_FEMPART){
			ui->cbSection->setVisible(true);
			int sectionCount=resItem->sectionCount();
			ui->cbSection->clear();
			for(int i=0;i<sectionCount;++i){
				QString secName=resItem->sectionName(i);
				ui->cbSection->addItem(secName);
			}

			if(_resultItemSelect.sectionIndex!=-1 && _resultItemSelect.sectionIndex<sectionCount)
				ui->cbSection->setCurrentIndex(_resultItemSelect.sectionIndex);
			return;
		}
	}
	ui->cbSection->setVisible(false);
}



void ResultSelectorWidget::res_ResultsDeleted()
{
	clearAll();
	emit resultDeleted();
}

void ResultSelectorWidget::clearAll()
{
	ui->cbItem->setVisible(false);
	ui->cbSection->setVisible(false);
}

QString ResultSelectorWidget::getCurrentItemName() const
{
	int index=ui->cbItem->currentIndex();
	if(index!=-1){
		QVariant var=ui->cbItem->itemData(index);
		BaseItem* item=(BaseItem*)var.toLongLong();
		if(item)
			return item->getFullName();
	}
	return QString();
}

