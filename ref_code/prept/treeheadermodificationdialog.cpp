#include "treeheadermodificationdialog.h"
#include "ui_treeheadermodificationdialog.h"

#include "base/TreeItemPropertyManager.h"
#include "precore/modeldocument.h"

#include "comtreemodel.h"


using namespace INSIDES;


TreeHeaderModificationDialog::TreeHeaderModificationDialog(QWidget *parent,ComTreeModel* treeModel)
	: QDialog(parent)
	,_treeModel(treeModel)
{
	ui = new Ui::TreeHeaderModificationDialog();
	ui->setupUi(this);

	connect(ui->lwViews,SIGNAL(currentRowChanged (int)),
		this,SLOT(updateItems()));
	connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(onAdd()));
	connect(ui->btnRemove,SIGNAL(clicked()),this,SLOT(onRemove()));
	connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(onOK()));
	connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(reject()));

	TreeItemPropertyManager* manager=TreeItemPropertyManager::instance();
	_displayItemList=manager->getSelectedItems();
	updateViews();
	updateDisplayedItems();
}

TreeHeaderModificationDialog::~TreeHeaderModificationDialog()
{
	delete ui;
}

void TreeHeaderModificationDialog::updateViews()
{
	ui->lwViews->clear();
	TreeItemPropertyManager* manager=TreeItemPropertyManager::instance();
	int n=manager->getCount();
	for(int i=0;i<n;++i){
		const TreeItemPropertyGroup* pros=manager->getGroup(i);
		ui->lwViews->addItem(pros->getKeyname());
	}
	ui->lwViews->update();
	ui->lwViews->setCurrentRow(0);
}

void TreeHeaderModificationDialog::updateItems()
{
	TreeItemPropertyManager* manager=TreeItemPropertyManager::instance();
	int viewId=ui->lwViews->currentRow();
	if(viewId==-1)
		return;

	ui->lwItems->clear();
	const TreeItemPropertyGroup* props=manager->getGroup(viewId);
	int n=props->getCount();
	for(int i=0;i<n;++i){
		ui->lwItems->addItem(props->getProperty(i)->name);
	}
	ui->lwItems->update();
}

void TreeHeaderModificationDialog::updateDisplayedItems()
{
	ui->lwDisplayItems->clear();
	for(int i=0;i<_displayItemList.size();++i){
		ui->lwDisplayItems->addItem(_displayItemList[i]);
	}
	ui->lwDisplayItems->update();
}

void TreeHeaderModificationDialog::onAdd()
{
	QListWidgetItem* item=ui->lwItems->currentItem();
	if(!item)
		return;
	_displayItemList.push_back(item->text());
	updateDisplayedItems();
}

void TreeHeaderModificationDialog::onRemove()
{
	QListWidgetItem* item=ui->lwDisplayItems->currentItem();
	if(!item)
		return;
	_displayItemList.removeOne(item->text());
	updateDisplayedItems();
}

void TreeHeaderModificationDialog::onMoveUp()
{

}

void TreeHeaderModificationDialog::onMoveDown()
{

}

void TreeHeaderModificationDialog::onOK()
{
	TreeItemPropertyManager* manager=TreeItemPropertyManager::instance();
	manager->setSelectedItems(_displayItemList);
	// update view
	_treeModel->updateHeaderStruct();
}

