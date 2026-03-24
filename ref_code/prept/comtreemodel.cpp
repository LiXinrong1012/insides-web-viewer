#include "comtreemodel.h"
#include <QPixmap>
#include <QIcon>
#include <QFont>
#include <cassert>


#include "base/Console.h"
#include "base/PixmapManager.h"
#include "base/view.h"
#include "base/activeviewobject.h"
#include "base/TreeItemPropertyManager.h"

#include "precore/itemlist.h"
#include "precore/TypeDataManager.h"
#include "precore/modeldocument.h"
#include "precore/appearance.h"


using namespace Base;




static QFont _fontStrikeOut;
static BaseItem _tmpBaseItem;


////////////////////////////////////////////////////////////////////////////////
ComTreeModel::ComTreeModel(QObject *parent)
	: QAbstractItemModel(parent)
	,ModelDocumentListener(0)
{
	// to-do:初始化用户需要显示的条目。
	updateCurrentItems();

	_rootNode=NULL;
	_fontStrikeOut.setStrikeOut(true);

	connect(ActiveViewObject::instance(),SIGNAL(activeViewChanged(View*)),
		this,SLOT(onActiveViewChanged(View*)));
	connect(ActiveViewObject::instance(),SIGNAL(modelStatusChanged(int)),
		this,SLOT(onModelStatusChanged(int)));

	ModelDocument* doc=myDocument();
	doc->attachListener(this);
}

ComTreeModel::~ComTreeModel()
{
	myDocument()->disattachListener(this);
}

void ComTreeModel::setRootNode(ItemClass *node)
{
	_rootNode=node;
	resetModel();
}

QModelIndex ComTreeModel::index(int row, int column,
	const QModelIndex &parent) const
{
	ItemClass *parentNode = nodeFromIndex(parent);
	if (parent.isValid()&& parent.column() != 0)
		return QModelIndex();

	if(!parentNode){
		//assert(row==0);
		//assert(column==0);
		//assert(_rootNode);
		//return QModelIndex();
		//return createIndex(row,column,_rootNode);
		return createIndex(row,column,_rootNode);
	}
	return createIndex(row, column, parentNode->child(row));
}

QModelIndex ComTreeModel::parent(const QModelIndex &child) const
{
	ItemClass *node = nodeFromIndex(child);
	if (!node)
		return QModelIndex();
	int a=node->count();

	ItemClass *parentNode = node->getParent();
	if (!parentNode || node==myDocument()->getActiveItem())
		return QModelIndex();
	ItemClass *grandparentNode = parentNode->getParent();
	if (!grandparentNode)
		return createIndex(0,0,parentNode);

	int size=grandparentNode->count();
	int i;
	for(i=0;i<size;i++)
		if(grandparentNode->child(i)==parentNode)
			break;
	return createIndex(i, 0, parentNode);
}

int ComTreeModel::rowCount(const QModelIndex &parent) const
{
	ItemClass *parentNode = nodeFromIndex(parent);
	if (!parentNode){
		if(_rootNode)
			return 1;
		else
			return 0;
	}
	return ( (parentNode!=_rootNode)&&(parentNode->isPartOrAssembly())|| parentNode->isExternal() )?
		0:parentNode->count();
}

int ComTreeModel::columnCount(const QModelIndex & /* parent */) const
{
	return _currentPropertiesParents.size()+1;
}

Qt::ItemFlags ComTreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	int section=index.column();
	if(section==0)
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	else
		return (_currTreeItemPropertyList[section-1]->editable)?(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable):
		(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

////////////////////////////////////////////////////////////////////////////////
QVariant ComTreeModel::data(const QModelIndex &index, int role) const
{
	ItemClass *node = nodeFromIndex(index);
	if (!node)
		return QVariant();

	if(index.column()==0)
	{
		switch(role)
		{
		case Qt::DisplayRole:
			return node->getDisplayText();
		case Qt::DecorationRole:
			{
				TypeData* typeData=TypeDataManager::instance()->getTypeData(node->getCategory());
				if(typeData){
					if(node->isInstance())
						return *PixmapManager()->get(typeData->insIcon);
					else
						return *PixmapManager()->get(typeData->icon);
				}
			}
			break;
		case Qt::ForegroundRole:
			if(node->getIncluded())
				return QColor("grey");
			break;
		case Qt::FontRole:
			if(!node->getActive()){

				return _fontStrikeOut;
			}
			break;
			//case Qt::CheckStateRole:
			//	return Qt::Checked;
			//	break;
		}
	}
	else{
		int columnIndex=index.column();
		if( (role== Qt::DisplayRole) || (role==Qt::EditRole) )
			return _currentPropertiesParents[index.column()-1]->getData(node,_currentPropertiesIndex[index.column()-1]);
		else if(role==Qt::BackgroundRole){
			if(_currTreeItemPropertyList[columnIndex-1]->type==QVariant::Color)
				return _currentPropertiesParents[columnIndex-1]->getData(node,_currentPropertiesIndex[columnIndex-1]);
		}
	}

	return QVariant();
}

QVariant ComTreeModel::headerData(int section,
	Qt::Orientation orientation,
	int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		if (section == 0) {
			return tr("items");
		}
		else{
			return _currTreeItemPropertyList[section-1]->getDisplayName();
		}
	}
	return QVariant();
}

ItemClass *ComTreeModel::nodeFromIndex(const QModelIndex &index) const
{
	if (index.isValid()) {
		return static_cast<ItemClass *>(index.internalPointer());
	} else {
		return NULL;
	}
}

void ComTreeModel::refrushModel()
{
	emit layoutChanged();
}

void ComTreeModel::refrushData( ItemClass* node )
{

}

void ComTreeModel::doc_RootItemChanged( BaseItem* itemAfter,BaseItem* itemBefore )
{
	setRootNode(itemAfter);
	resetModel()	;
}

void ComTreeModel::resetModel()
{
	reset();

}

void ComTreeModel::doc_ItemAdded( BaseItem* item,bool isIncludingChildren )
{
	QModelIndex index=indexFromNode(item->getParent());
	if(index.isValid()){
		beginInsertRows(index,item->row(),item->row()+1);
		//dataChanged(index,index);
		endInsertRows();
	}
}

void ComTreeModel::doc_ItemModified( BaseItem* item,bool isIncludingChildren )
{
	QModelIndex index=indexFromNode(item);
	if(index.isValid())
		dataChanged(index,index);
}

void ComTreeModel::doc_BeginItemRemoving( BaseItem* item )
{
	QModelIndex index=indexFromNode(item->getParent());
	if(index.isValid()){
		int row=item->row();
		beginRemoveRows(index,row,row+1);
	}
}

void ComTreeModel::doc_ItemRemoved( BaseItem* parent,BaseItem* item )
{
	endRemoveRows();
}

void ComTreeModel::doc_ModelReseted( BaseItem* rootItem )
{
	setRootNode(rootItem);
	//resetModel();
	updateCurrentItems();
}

void ComTreeModel::doc_BeginRootItemChanging( BaseItem* currentRoot,BaseItem* newRoot )
{

}

QModelIndex ComTreeModel::indexFromNode( const ItemClass* node ) const
{
	if(!node)
		return QModelIndex();
	if(node==_rootNode)
		return index(0,0,QModelIndex());

	QModelIndex parentIndex=indexFromNode(node->getParent());
	if(!parentIndex.isValid())
		return QModelIndex();

	int n=rowCount(parentIndex);
	int i;
	for(i=0;i<n;++i){
		if(nodeFromIndex(index(i,0,parentIndex))==node)
			break;
	}
	if(i==n)
		return QModelIndex();
	else
		return index(i,0,parentIndex);
}



void ComTreeModel::doc_ParametersChanged( BaseItem* parametersItem )
{
	resetModel();
}



void ComTreeModel::onActiveViewChanged( View* view )
{
	emit viewModelBeginChanging();

	updateCurrentItems();

	emit viewModelChanged();
}

void ComTreeModel::onModelStatusChanged(int s)
{
	View* v=ActiveViewObject::instance()->activeView();
	onActiveViewChanged(v);
}

void ComTreeModel::updateCurrentItems()
{
	updateColumns();

	resetModel();
	emit structChanged();
}

bool ComTreeModel::setData( const QModelIndex & index, const QVariant & value, int role /*= Qt::EditRole*/ )
{
	if(role==Qt::EditRole){
		ItemClass *node = nodeFromIndex(index);
		if (!node)
			return QAbstractItemModel::setData(index,value,role);

		return _currentPropertiesParents[index.column()-1]->setData(node,
			_currentPropertiesIndex[index.column()-1],value);
	}
	return false;
}

void ComTreeModel::updateHeaderStruct()
{
	updateCurrentItems();	
}

