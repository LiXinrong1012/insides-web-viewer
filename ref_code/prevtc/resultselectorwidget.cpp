#include "resultselectorwidget.h"
#include "ui_resultselectorwidget.h"

#include "base/Console.h"
#include "base/activeviewobject.h"
#include "base/MultiProgressOperator.h"

#include "precore/projectselector.h"
#include "precore/BaseItem.h"
#include "precore/BaseItemHelper.h"
#include "precore/modeldocument.h"

#include "precore/ResultDocument.h"
#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"

#include "precore/precore_data.h"

#include <QTimer>
#include <QThread>

using namespace INSIDES;


QDataStream& operator << (QDataStream& out,const CurveItemTitle& item)
{
	out<<item.itemContent
		<<item.secIndex
		<<item.subsecIndex
		<<item.subsubsecIndex
		<<item.nodeElemIndex
		<<item.name
		<<(qint32)(item.type)
		<<item.xs
		<<item.ys;
	return out;
}

QDataStream& operator >> (QDataStream& in, CurveItemTitle& item)
{
	qint32 tmpType;
	in>>item.itemContent
		>>item.secIndex
		>>item.subsecIndex
		>>item.subsubsecIndex
		>>item.nodeElemIndex
		>>item.name
		>>tmpType;
	in
		>>item.xs
		>>item.ys
		;
	item.type=(CurveItemTitle::Type)tmpType;

	return in;
}

///////////////////////////////////////////////////////////////////////////
ResultSelectorWidget::ResultSelectorWidget(QWidget *parent)
	: QWidget(parent)
	,_parentView(NULL)
	,_IsOperatingUI(false)
{
	ui = new Ui::ResultSelectorWidget();
	ui->setupUi(this);
	//this->setStyle(QString::fromUtf8("border:1px solid black"));

	clearAll();

	connect(ui->cbItem,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onCurrentItemChanged()));

	connect(ui->cbSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(oncbSelectionChanged()));

	connect(ui->cbSubSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onSubsectionChanged()));


	res_ResultsLoaded(myResultDocument()->getResults());

	myProjectSelector()->attachSupplier(this);
	setSupplierName("ResultSelector");
	myResultDocument()->attachListener(this);
}

ResultSelectorWidget::~ResultSelectorWidget()
{
	myProjectSelector()->disattachSupplier(this);
	myResultDocument()->disattachListener(this);

	delete ui;
}

void ResultSelectorWidget::ss_onSetClicked_projected( BaseItem* item )
{
	if(!ui->cbGlobalSelection->isChecked()){
		if(_parentView){
			if(Base::ActiveViewObject::instance()->activeView()!=_parentView)
				return;
		}
	}
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

void ResultSelectorWidget::res_ResultsLoaded(IResults* results)
{
	_IsOperatingUI=true;
	clearAll();
	updateItems();
	_IsOperatingUI=false;
	emit newResultLoaded();
}

void ResultSelectorWidget::setDefaultName( CurveItemTitle& itemTitle )
{
	QString baseitemName=itemTitle.itemContent;
	BaseItem* item=myDocument()->findItem(baseitemName);
	if(!item || !myResultDocument()->getResults())
		return;
		
	IResultItem* resultItem=myResultDocument()->getResults()->findResultItem(item).data();
	if(!resultItem)
		return;

	int secIndex=itemTitle.secIndex;
	int subsecIndex=itemTitle.subsecIndex;
	int subsubsecIndex=itemTitle.subsubsecIndex;
	int nodeElemIndex=itemTitle.nodeElemIndex;

	IResults* results=myResultDocument()->getResults();

	QString itemName=resultItem->connectedItem()->getKeyName();
	QString sectionName=resultItem->sectionName(secIndex);
	QString subSectionName=resultItem->subSectionName(secIndex,subsecIndex);
	QString subsubSectionName=resultItem->subsubSectionName(secIndex,subsecIndex,subsubsecIndex);
	QString indexName;

	QString curveFormat=ui->txtLabelFormat->text();
	curveFormat=curveFormat.replace("{1}",itemName);
	if(!sectionName.isEmpty())
		curveFormat=curveFormat.replace("{2}",sectionName);
	if(!subSectionName.isEmpty())
		curveFormat=curveFormat.replace("{3}",subSectionName);
	if(!subsubSectionName.isEmpty())
		curveFormat=curveFormat.replace("{4}",subsubSectionName);
	if(!indexName.isEmpty())
		curveFormat=curveFormat.replace("{5}",indexName);

	itemTitle.name=curveFormat;
}

void ResultSelectorWidget::protected_onOK()
{
	CurveItemTitle title;
	title.itemContent=getCurrentItemName();
	title.secIndex=ui->cbSection->currentIndex();
	title.subsecIndex=ui->cbSubSection->currentIndex();
	title.subsubsecIndex=ui->cbSubsubSection->currentIndex();
	title.nodeElemIndex=ui->cbIndex->currentIndex();

	setDefaultName(title);

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
}


void ResultSelectorWidget::oncbSelectionChanged()
{
	if(_IsOperatingUI)
		return;

	_IsOperatingUI=true;

	updateSubsections();
	//updateSections();

	_IsOperatingUI=false;
}

void ResultSelectorWidget::onSubsectionChanged()
{
	if(_IsOperatingUI)
		return;

	_IsOperatingUI=true;
	updateSubsubsections();
	_IsOperatingUI=false;
}

void ResultSelectorWidget::updateIndexStatus()
{
	IResultItem* item=getCurrentBaseItem();
	if(!item || !item->connectedItem()){
		ui->cbSubSection->setHidden(true);
		ui->cbSubsubSection->setHidden(true);
		ui->cbIndex->setHidden(true);
		return;
	}

	if(item->connectedItem()->getCategory()==TDY_PRE_CATE_FEMPART)
	{
		int secIndex=ui->cbSection->currentIndex();
		if(secIndex==0)
			ui->cbIndex->setHidden(true);
		else{
			ui->cbIndex->setHidden(false);
			ui->cbIndex->clear();

			FlexResultItem* flexResultItem=(FlexResultItem*)item;
			if(secIndex==1){
				int nodeCount=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetNodeCnt();
				for(int i=0;i<nodeCount;++i){
					PP_NODE* node=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetNode(i);
					ui->cbIndex->addItem(QString("%1").arg(node->NID));
				}
			}
			else if(secIndex==2){
				int elemCount=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetElementCnt();
				for(int i=0;i<elemCount;++i){
					PP_ELEMENT* elem=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetElement(i);
					ui->cbIndex->addItem(QString("%1").arg(elem->EID));
				}
			}
		}
	}
	else{
		ui->cbIndex->setHidden(true);
		ui->cbIndex->clear();
	}
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
	ui->cbSubSection->setVisible(true);

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
		int sectionCount=resItem->sectionCount();
		ui->cbSection->clear();
		for(int i=0;i<sectionCount;++i){
			QString secName=resItem->sectionName(i);
			ui->cbSection->addItem(secName);
		}

		if(_resultItemSelect.sectionIndex!=-1 && _resultItemSelect.sectionIndex<sectionCount)
			ui->cbSection->setCurrentIndex(_resultItemSelect.sectionIndex);
	}

	updateSubsections();
}

void ResultSelectorWidget::updateSubsections()
{
	IResultItem* item=getCurrentBaseItem();
	if(!item){
		ui->cbSubSection->clear();
		return;
	}

	if(ui->cbSection->currentIndex()!=-1)
		_resultItemSelect.sectionIndex=ui->cbSection->currentIndex();

	int subSectionCount=item->subSectionCount(ui->cbSection->currentIndex());
	ui->cbSubSection->clear();
	for(int i=0;i<subSectionCount;++i){
		QString secName=item->subSectionName(ui->cbSection->currentIndex(),i);
		ui->cbSubSection->addItem(secName);
	}

	if(_resultItemSelect.subSectionIndex!=-1 && _resultItemSelect.subSectionIndex<ui->cbSubSection->count())
		ui->cbSubSection->setCurrentIndex(_resultItemSelect.subSectionIndex);

	updateSubsubsections();
	updateIndexStatus();
}

void ResultSelectorWidget::updateSubsubsections()
{
	IResultItem* item=getCurrentBaseItem();
	if(!item )
		return;

	if(ui->cbSubSection->currentIndex()!=-1)
		_resultItemSelect.subSectionIndex=ui->cbSubSection->currentIndex();

	int subSectionCount=item->subsubSectionCount(ui->cbSection->currentIndex(),
		ui->cbSubSection->currentIndex());
	if(subSectionCount==0){
		ui->cbSubsubSection->hide();
		return;
	}

	ui->cbSubsubSection->show();
	ui->cbSubsubSection->clear();
	for(int i=0;i<subSectionCount;++i){
		QString secName=item->subsubSectionName(ui->cbSection->currentIndex(),
			ui->cbSubSection->currentIndex(),i);
		ui->cbSubsubSection->addItem(secName);
	}

	if(_resultItemSelect.subsubSectionIndex!=-1 && _resultItemSelect.subsubSectionIndex<ui->cbSubsubSection->count())
		ui->cbSubsubSection->setCurrentIndex(_resultItemSelect.subsubSectionIndex);
}

void ResultSelectorWidget::res_ResultsDeleted()
{
	clearAll();
}

void ResultSelectorWidget::clearAll()
{
	ui->cbItem->setVisible(false);
	ui->cbSection->setVisible(false);
	ui->cbSubSection->setVisible(false);
	ui->cbSubsubSection->setVisible(false);
	ui->cbIndex->setVisible(false);
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



