#include "comtreeview.h"
#include "comtreemodel.h"
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui>
#include "precore/UAPI.h"
#include "precore/modeldocument.h"
#include "precore/projectselector.h"
#include "precore/TypeDataManager.h"
#include "base/CMDialogFactory.h"
#include "base/Console.h"
#include "base/TreeItemPropertyManager.h"

#include "precore/appearance.h"



using namespace std;
using namespace Base;



QWidget* TreeItemDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
	QSpinBox *editor = new QSpinBox(parent);
	editor->setMinimum(0);
	editor->setMaximum(100);

	return editor;
}

void TreeItemDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();

	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

void TreeItemDelegate::setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const
{
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();
	int value = spinBox->value();

	model->setData(index, value, Qt::EditRole);
}

TreeItemDelegate::TreeItemDelegate( QObject* parent /*= NULL*/ )
	:QItemDelegate(parent)
{

}

void TreeItemDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

ComTreeView::ComTreeView(QWidget *parent)
	: QTreeView(parent)
	,ModelDocumentListener(0)
{

	setSelectionBehavior(SelectRows);
	setSelectionMode(ExtendedSelection);
	setExpandsOnDoubleClick(false);

	connect(this,SIGNAL(doubleClicked(const QModelIndex&)),
		this, SLOT(onDoubleClicked(const QModelIndex&)));

	connect(this,SIGNAL(clicked(const QModelIndex&)),
		this, SLOT(onClicked(const QModelIndex&)));

	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(onContextMenu(const QPoint&)));



	// Alternating row colors look bad on Maemo
	this->setAlternatingRowColors(false);
	//this->expandAll();
	this->setHeaderHidden(false);
	this->header()->setStretchLastSection(false);
		this->header()->setMovable(true);


	ModelDocument* doc=myDocument();
	ComTreeView* view=this;

	_editAppearanceAction=new QAction("Appearance",this);
	connect(_editAppearanceAction,SIGNAL(triggered()),this,SLOT(onEditAppearance()));

	_showPropertiesAction=new QAction("Properties",this);
	connect(_showPropertiesAction,SIGNAL(triggered()),this,SLOT(onShowProperties()));


	_setVisual=new QAction("Show",this);
	connect(_setVisual,SIGNAL(triggered()),this,SLOT(onSetVisual()));

	_setInvisual=new QAction("Hide",this);
	connect(_setInvisual,SIGNAL(triggered()),this,SLOT(onSetInvisual()));

	_setUndefined=new QAction("Follow parent",this);
	connect(_setUndefined,SIGNAL(triggered()),this,SLOT(onSetVisualFollowParent()));

	myProjectSelector()->attachSupplier(this);
	myDocument()->attachListener(this);
}

ComTreeView::~ComTreeView()
{
	myProjectSelector()->disattachSupplier(this);
	myDocument()->disattachListener(this);
}

void ComTreeView::slot_SelectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
	QModelIndexList selectionIndexlist=this->selectedIndexes();
	QAbstractItemModel* model=this->model();
	QList<TreeItemClass*> emitItems;
	foreach(QModelIndex index,selectionIndexlist){
		TreeItemClass* item=static_cast<TreeItemClass*>(index.internalPointer());
		if(item)
			emitItems.push_back(item);
	}

	ss_notifySetSelection(emitItems);
}
void ComTreeView::slot_CurrentChanged( const QModelIndex & current, const QModelIndex & previous )
{

}




void ComTreeView::onContextMenu( const QPoint& pos )
{
	QModelIndex index=this->selectionModel()->currentIndex();
	if(!index.isValid())
		return;
	if(index.column()==0)
	{
		QMenu myMenu;
		myMenu.addAction(_editAppearanceAction);
		myMenu.addAction(_showPropertiesAction);

		//QAction* selectedItem = myMenu.exec(globalPos);
		QAction* selectedItem = myMenu.exec(QCursor::pos());
	}
	else if(index.column()==1)
	{
		QMenu myMenu;
		myMenu.addAction(_setVisual);
		myMenu.addAction(_setInvisual);
		myMenu.addAction(_setUndefined);

		QAction* selectedItem = myMenu.exec(QCursor::pos());
	}

}

void ComTreeView::onRemoveItem()
{
	QList<TreeItemClass*> entites;
	index2Items(selectedIndexes(),entites);
	if(entites.size()>0){
		ModelDocument* doc=myDocument();
		PRE_Remove_Item(doc,entites[0]);
	}
}

void ComTreeView::index2Items( QModelIndexList l, QList<TreeItemClass*>& entities )
{
	foreach(QModelIndex index,l){
		TreeItemClass* curveEntity=static_cast<TreeItemClass*>(index.internalPointer());
		if(curveEntity)
			entities.push_back(curveEntity);
	}
}

void ComTreeView::onEditAppearance()
{

}

void ComTreeView::onModify()
{
	//QList<TreeItemClass*> entites;
	//index2Items(selectedIndexes(),entites);
	//if(entites.size()>0){
	//	PreDocument* doc=myDocument();
	//	TreeItemClass* entity=entites[0];

	//	TypeDataManager* manager=TypeDataManager::instance();
	//	TypeData* data=manager->getTypeData(entity->getCategory());
	//	if(!data)
	//		return;

	//	BaseCMDialog* dlg=(BaseCMDialog*)Base::CMFactory()->Produce(string("Modify")+data->name.toStdString());
	//	if(dlg)
	//	{
	//		dlg->setInputItem(entity);
	//		dlg->updateControls();
	//		dlg->show();
	//	}
	//}
}

void ComTreeView::onShowProperties()
{

}



TreeItemClass* ComTreeView::getSelectedCoreItem()
{
	QList<TreeItemClass*> entites;
	index2Items(selectedIndexes(),entites);
	if(entites.size()>0)
		return entites[0];
	return NULL;
}

QList<TreeItemClass*> ComTreeView::getSelectedCoreItems()
{
	QList<TreeItemClass*> entites;
	index2Items(selectedIndexes(),entites);
	return entites;
}

void ComTreeView::ss_onSetSelection_protected( const QList<BaseItem*>& selection )
{

}

void ComTreeView::restoreCollapseStatus(QModelIndex index)
{
	ComTreeModel* model=(ComTreeModel*)this->model();
	if(!model)
		return;
	int row=model->rowCount(index);
	BaseItem* item=model->nodeFromIndex(index);
	if(item && !item->getCollapsed())
		expand(index);

	for(int i=0;i<row;++i){
		restoreCollapseStatus(model->index(i,0,index));
	}
}

void ComTreeView::reset()
{
	QAbstractItemView::reset();
	restoreCollapseStatus();
}

void ComTreeView::saveCollapseStatus( QModelIndex index/*=QModelIndex()*/ )
{
	ComTreeModel* model=(ComTreeModel*)this->model();
	BaseItem* item=model->nodeFromIndex(index);
	int row=model->rowCount(index);
	if(item && row!=0){
		bool b=isExpanded(index);
		item->setCollapsed(!isExpanded(index));
	}

	for(int i=0;i<row;++i){
		saveCollapseStatus(model->index(i,0,index));
	}
}


TreeItemClass* ComTreeView::getCurrentItem() const
{
	QModelIndex index=selectionModel()->currentIndex();
	BaseItem* item=((ComTreeModel*)this->model())->nodeFromIndex(index);
	return item;
}



void ComTreeView::onDoubleClicked( const QModelIndex & index )
{
	if(index.column()==0)
		onModify();

}

void ComTreeView::onClicked( const QModelIndex & index )
{
	// 触发点击事件
	TreeItemClass* item=static_cast<TreeItemClass*>(index.internalPointer());
	if(item)
		ss_notifySetClicked(item);


}

void ComTreeView::onStructChanged()
{
	ComTreeModel* model=(ComTreeModel*)this->model();
	if(!model)
		return;

	int columnSize=model->columnCount(QModelIndex());
	for(int i=0;i<columnSize-1;++i){
		TreeItemProperty* pro=model->getColumnDataType(i);
		this->setColumnWidth(i+1,pro->width);
	}
	this->setColumnWidth(0,TreeItemPropertyManager::instance()->getFirstColumnWidth());

	// 设置代理
	for(int i=0;i<columnSize-1;++i){
		TreeItemProperty* pro=model->getColumnDataType(i);
		if(pro->editable){
			switch(pro->type){
			case QVariant::Bool:
				//setItemDelegateForColumn(i+1,new CheckBoxDelegate2(true,this));
				//break;
			default:
				{
					QAbstractItemDelegate* de=TreeItemPropertyManager::instance()->getItemDelegate(pro->type);
					if(de){
						setItemDelegateForColumn(i+1,de);
					}
				}
				break;
			}
		}
	}

}

void ComTreeView::onColumnSizeChanged( int index,int oldSize,int newSize )
{
	ComTreeModel* model=(ComTreeModel*)this->model();
	if(!model)
		return;

	if(index==0){
		TreeItemPropertyManager::instance()->setFirstColumnWidth(newSize);
		return;
	}

	if(index<=this->model()->columnCount(QModelIndex())){
		TreeItemProperty* pro=model->getColumnDataType(index-1);
		pro->width=newSize;
	}
}

void ComTreeView::doc_BeginRootItemChanging( BaseItem* currentRoot,BaseItem* old )
{
	saveCollapseStatus();
}

void ComTreeView::doc_BeginSavingDocument()
{
	saveCollapseStatus();
}

void ComTreeView::setModel( QAbstractItemModel* model )
{
	QTreeView::setModel(model);

	QItemSelectionModel* interModel=this->selectionModel();
	connect(interModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), 
		this, SLOT(slot_SelectionChanged(const QItemSelection &, const QItemSelection &)));

	connect(interModel, SIGNAL(currentChanged ( const QModelIndex&, const QModelIndex&)), 
		this, SLOT(slot_CurrentChanged(const QModelIndex &, const QModelIndex &)));

	connect(this->header(),SIGNAL(sectionResized(int,int, int)),
		this,SLOT(onColumnSizeChanged(int,int,int)));

	ComTreeModel* comModel=(ComTreeModel*)model;
	connect(comModel,SIGNAL(structChanged()),this,SLOT(onStructChanged()));

	connect(comModel,SIGNAL(viewModelBeginChanging()),
		this,SLOT(saveCollapseStatus()));

	connect(comModel,SIGNAL(viewModelChanged()),
		this,SLOT(restoreCollapseStatus()));

}



