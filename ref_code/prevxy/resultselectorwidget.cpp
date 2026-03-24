#include "resultselectorwidget.h"
#include "ui_resultselectorwidget.h"

#include "base/Console.h"
#include "base/activeviewobject.h"

#include "precore/projectselector.h"
#include "precore/BaseItem.h"
#include "precore/BaseItemHelper.h"
#include "precore/modeldocument.h"
#include "precore/ResultDocument.h"
#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"
#include "precore/document.h"
#include "precore/precore_data.h"

#include "edcompile/tdytypeinfomanager.h"

#include "addcustomcurvedialog.h"

using namespace INSIDES;


///////////////////////////////////////////////////////////////////////////
ResultSelectorWidget::ResultSelectorWidget(QWidget *parent)
	: QWidget(parent)
	,_parentView(NULL)
	,_IsOperatingUI(false)
{
	ui = new Ui::ResultSelectorWidget();
	ui->setupUi(this);

	QButtonGroup* group = new QButtonGroup(this);
	group->addButton(ui->xRBtn);
	group->addButton(ui->yRBtn);
	ui->xRBtn->setChecked(true);

	//this->setStyle(QString::fromUtf8("border:1px solid black"));
	ui->customBtn->setIcon(QIcon(":/resources/menu/a037x16x16.png"));
	ui->customYBtn->setIcon(QIcon(":/resources/menu/a037x16x16.png"));
	connect(ui->customBtn,SIGNAL(clicked()),this,SLOT(onCustomBtnClicked()));
	connect(ui->customYBtn,SIGNAL(clicked()),this,SLOT(onCustomBtnClicked()));

	_xCustomDialog = new AddCustomCurveDialog();
	connect(_xCustomDialog,SIGNAL(useCustomData()),this,SLOT(setCheckBoxChecked()));
	_yCustomDialog = new AddCustomCurveDialog();
	connect(_yCustomDialog,SIGNAL(useCustomData()),this,SLOT(setCheckBoxChecked()));

	clearAll();

	connect(ui->cbItem,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onCurrentItemChanged()));
	connect(ui->cbSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(oncbSelectionChanged()));
	connect(ui->cbSubSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onSubsectionChanged()));

	connect(ui->cbYItem,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onCurrentYItemChanged()));
	connect(ui->cbYSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(oncbYSelectionChanged()));
	connect(ui->cbYSubSection,SIGNAL(currentIndexChanged (int)),
		this,SLOT(onSubsectionYChanged()));

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
	delete _xCustomDialog;
	delete _yCustomDialog;
}

void ResultSelectorWidget::ss_onSetClicked_projected( BaseItem* item )
{
	if(_parentView)
		if(Base::ActiveViewObject::instance()->activeView()!=_parentView)
			return;

	QVariant var( (qlonglong)(item));
	int index=ui->cbItem->findData(var);

	if(ui->xRBtn->isChecked())
	{
		if(index!=-1)
			ui->cbItem->setCurrentIndex(index);
	}
	else
		if(index!=-1)
			ui->cbYItem->setCurrentIndex(index);
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
//	emit newResultLoaded();
}

void ResultSelectorWidget::setDefaultName( XYItemTitle& itemTitle )
{
	QString n,m;
	if(itemTitle.type == XYItemTitle::Normal)
	{
		QString baseitemName=itemTitle.itemContent;
		BaseItem* item=myDocument()->findItem(baseitemName);
		if(!item || !myResultDocument()->getResults())
			return;

		IResultItem* resultItem=myResultDocument()->getResults()->findResultItem(item).data();
		if(!resultItem)
			return;

		IResults* results=myResultDocument()->getResults();
		n=resultItem->connectedItem()->getKeyName();
	}
	else
		n = "custom";

	if(itemTitle.yType == XYItemTitle::Normal)
	{
		QString baseitemName=itemTitle.itemYContent;
		BaseItem* item=myDocument()->findItem(baseitemName);
		if(!item || !myResultDocument()->getResults())
			return;

		IResultItem* resultItem=myResultDocument()->getResults()->findResultItem(item).data();
		if(!resultItem)
			return;

		IResults* results=myResultDocument()->getResults();
		m=resultItem->connectedItem()->getKeyName();
	}
	else
		m = "custom";

	itemTitle.name=n + "-" + m;
}

void ResultSelectorWidget::protected_onOK()
{
	XYItemTitle title;
	
	xContent(title);
	yContent(title);

	setDefaultName(title);
	emit itemAdding(title);
}

IResultItem* ResultSelectorWidget::getCurrentBaseItem(QComboBox* box)
{
	int index=box->currentIndex();
	if(index!=-1){
		QVariant var=box->itemData(index);
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

void ResultSelectorWidget::onCurrentYItemChanged()
{
	if(_IsOperatingUI)
		return;

	_IsOperatingUI=true;
	updateYSections();
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
	IResultItem* item=getCurrentBaseItem(ui->cbItem);
	if(!item || !item->connectedItem()){
		ui->cbSubSection->setHidden(true);
		ui->cbSubsubSection->setHidden(true);
		ui->cbIndex->setHidden(true);
		ui->customBtn->setHidden(true);
		ui->customCheckBox->setHidden(true);
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

void ResultSelectorWidget::updateYIndexStatus()
{
	IResultItem* item=getCurrentBaseItem(ui->cbYItem);
	if(!item || !item->connectedItem()){
		ui->cbYSubSection->setHidden(true);
		ui->cbYSubsubSection->setHidden(true);
		ui->cbYIndex->setHidden(true);
		ui->customYBtn->setHidden(true);
		ui->customYCheckBox->setHidden(true);
		return;
	}

	if(item->connectedItem()->getCategory()==TDY_PRE_CATE_FEMPART)
	{
		int secIndex=ui->cbYSection->currentIndex();
		if(secIndex==0)
			ui->cbYIndex->setHidden(true);
		else{
			ui->cbYIndex->setHidden(false);
			ui->cbYIndex->clear();

			FlexResultItem* flexResultItem=(FlexResultItem*)item;
			if(secIndex==1){
				int nodeCount=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetNodeCnt();
				for(int i=0;i<nodeCount;++i){
					PP_NODE* node=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetNode(i);
					ui->cbYIndex->addItem(QString("%1").arg(node->NID));
				}
			}
			else if(secIndex==2){
				int elemCount=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetElementCnt();
				for(int i=0;i<elemCount;++i){
					PP_ELEMENT* elem=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetElement(i);
					ui->cbYIndex->addItem(QString("%1").arg(elem->EID));
				}
			}
		}
	}
	else{
		ui->cbYIndex->setHidden(true);
		ui->cbYIndex->clear();
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
	ui->customBtn->setVisible(true);
	ui->customCheckBox->setVisible(true);

	ui->cbYItem->setVisible(true);
	ui->cbYSection->setVisible(true);
	ui->cbYSubSection->setVisible(true);
	ui->customYBtn->setVisible(true);
	ui->customYCheckBox->setVisible(true);

	ui->btnOK->setVisible(true);

	IResults::ResultMap& allRes=res->getResults();
	for(IResults::ResultMap::Iterator b=allRes.begin();
		b!=allRes.end();++b){
			BaseItem* item=b.key();
			QIcon icon=BaseItemHelper::getBaseItemIcon(item);
			QVariant var((qlonglong)b.key());
			ui->cbItem->addItem(icon,item->getFullName(),var);
			ui->cbYItem->addItem(icon,item->getFullName(),var);
	}
	if(ui->cbItem->count()>0)
		ui->cbItem->setCurrentIndex(0);

	if(ui->cbYItem->count()>0)
		ui->cbYItem->setCurrentIndex(0);

	updateSections();
	updateYSections();
}

void ResultSelectorWidget::updateSections()
{
	IResultItem* resItem=getCurrentBaseItem(ui->cbItem);
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

void ResultSelectorWidget::updateYSections()
{
	IResultItem* resItem=getCurrentBaseItem(ui->cbYItem);
	if(resItem){
		int sectionCount=resItem->sectionCount();
		ui->cbYSection->clear();
		for(int i=0;i<sectionCount;++i){
			QString secName=resItem->sectionName(i);
			ui->cbYSection->addItem(secName);
		}

		if(_resultItemSelect.sectionIndex!=-1 && _resultItemSelect.sectionIndex<sectionCount)
			ui->cbYSection->setCurrentIndex(_resultItemSelect.sectionIndex);
	}

	updateYSubsections();
}

void ResultSelectorWidget::updateSubsections()
{
	IResultItem* item=getCurrentBaseItem(ui->cbItem);
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

void ResultSelectorWidget::updateYSubsections()
{
	IResultItem* item=getCurrentBaseItem(ui->cbYItem);
	if(!item){
		ui->cbYSubSection->clear();
		return;
	}

	if(ui->cbYSection->currentIndex()!=-1)
		_resultItemSelect.sectionIndex=ui->cbYSection->currentIndex();

	int subSectionCount=item->subSectionCount(ui->cbYSection->currentIndex());
	ui->cbYSubSection->clear();
	for(int i=0;i<subSectionCount;++i){
		QString secName=item->subSectionName(ui->cbYSection->currentIndex(),i);
		ui->cbYSubSection->addItem(secName);
	}

	if(_resultItemSelect.subSectionIndex!=-1 && _resultItemSelect.subSectionIndex<ui->cbYSubSection->count())
		ui->cbYSubSection->setCurrentIndex(_resultItemSelect.subSectionIndex);

	updateYSubsubsections();
	updateYIndexStatus();
}

void ResultSelectorWidget::updateSubsubsections()
{
	IResultItem* item=getCurrentBaseItem(ui->cbItem);
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

void ResultSelectorWidget::updateYSubsubsections()
{
	IResultItem* item=getCurrentBaseItem(ui->cbYItem);
	if(!item )
		return;

	if(ui->cbYSubSection->currentIndex()!=-1)
		_resultItemSelect.subSectionIndex=ui->cbYSubSection->currentIndex();

	int subSectionCount=item->subsubSectionCount(ui->cbYSection->currentIndex(),
		ui->cbYSubSection->currentIndex());
	if(subSectionCount==0){
		ui->cbYSubsubSection->hide();
		return;
	}

	ui->cbYSubsubSection->show();
	ui->cbYSubsubSection->clear();
	for(int i=0;i<subSectionCount;++i){
		QString secName=item->subsubSectionName(ui->cbYSection->currentIndex(),ui->cbYSubSection->currentIndex(),i);
		ui->cbYSubsubSection->addItem(secName);
	}

	if(_resultItemSelect.subsubSectionIndex!=-1 && _resultItemSelect.subsubSectionIndex<ui->cbYSubsubSection->count())
		ui->cbYSubsubSection->setCurrentIndex(_resultItemSelect.subsubSectionIndex);
}

//Î´Ê¹ÓÃ
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
	ui->customBtn->setVisible(false);
	ui->customCheckBox->setVisible(false);

	ui->cbYItem->setVisible(false);
	ui->cbYSection->setVisible(false);
	ui->cbYSubSection->setVisible(false);
	ui->cbYSubsubSection->setVisible(false);
	ui->cbYIndex->setVisible(false);
	ui->customYBtn->setVisible(false);
	ui->customYCheckBox->setVisible(false);

	ui->btnOK->setVisible(false);
}

QString ResultSelectorWidget::getCurrentItemName(QComboBox* box) const
{
	int index=box->currentIndex();
	if(index!=-1){
		QVariant var=box->itemData(index);
		BaseItem* item=(BaseItem*)var.toLongLong();
		if(item)
			return item->getFullName();
	}
	return QString();
}

void ResultSelectorWidget::onCustomBtnClicked()
{
	QToolButton* btn = (QToolButton*)sender();
	if(btn == ui->customBtn)
		_xCustomDialog->show();
	if(btn == ui->customYBtn)
		_yCustomDialog->show();
}

void ResultSelectorWidget::setCheckBoxChecked()
{
	AddCustomCurveDialog* dlg = (AddCustomCurveDialog*)sender();
	if(dlg == _xCustomDialog)
		ui->customCheckBox->setChecked(true);

	if(dlg == _yCustomDialog)
		ui->customYCheckBox->setChecked(true);
}

void ResultSelectorWidget::xContent(XYItemTitle& title)
{
	if (ui->customCheckBox->isChecked())
	{
		title.itemContent = _xCustomDialog->getCustomText();
		title.type = XYItemTitle::Custom;
	}
	else
	{
		title.type = XYItemTitle::Normal;
		title.itemContent=getCurrentItemName(ui->cbItem);
		title.secIndex=ui->cbSection->currentIndex();
		title.subsecIndex=ui->cbSubSection->currentIndex();
		title.subsubsecIndex=ui->cbSubsubSection->currentIndex();
		title.nodeElemIndex=ui->cbIndex->currentIndex();
	}
}

void ResultSelectorWidget::yContent(XYItemTitle& title)
{
	if(ui->customYCheckBox->isChecked())
	{
		title.itemYContent = _yCustomDialog->getCustomText();
		title.yType = XYItemTitle::Custom;
	}
	else
	{
		title.yType = XYItemTitle::Normal;
		title.itemYContent=getCurrentItemName(ui->cbYItem);
		title.secYIndex=ui->cbYSection->currentIndex();
		title.subsecYIndex=ui->cbYSubSection->currentIndex();
		title.subsubsecYIndex=ui->cbYSubsubSection->currentIndex();
		title.nodeElemYIndex=ui->cbYIndex->currentIndex();
	}
}



