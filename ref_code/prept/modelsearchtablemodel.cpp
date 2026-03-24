#include "modelsearchtablemodel.h"

#include "base/TreeItemPropertyManager.h"
#include "base/PixmapManager.h"
#include "base/activeviewobject.h"
#include "base/Console.h"

#include "precore/TypeDataManager.h"
#include "precore/BaseItem.h"
#include "precore/modeldocument.h"

using namespace Base;



static QFont _fontStrikeOut;

ModelSearchTableModel::ModelSearchTableModel(QObject *parent)
	: 	QAbstractTableModel (parent)
	,ModelDocumentListener(0)
{
	updateColumns();

	connect(ActiveViewObject::instance(),SIGNAL(activeViewChanged(View*)),
		this,SLOT(onActiveViewChanged(View*)));
	connect(ActiveViewObject::instance(),SIGNAL(modelStatusChanged(int)),
		this,SLOT(onModelStatusChanged(int)));

	myDocument()->attachListener(this);
}

ModelSearchTableModel::~ModelSearchTableModel()
{
	myDocument()->disattachListener(this);
}

int ModelSearchTableModel::rowCount( const QModelIndex & parent /*= QModelIndex()*/ ) const
{
	return _itemlist.size();
}

int ModelSearchTableModel::columnCount( const QModelIndex & parent /*= QModelIndex()*/ ) const
{
	return _currentPropertiesParents.size()+1;
}


BaseItem *ModelSearchTableModel::nodeFromIndex(const QModelIndex &index) const
{
	if (index.isValid()) {
		return _itemlist[index.row()];
	} 
	
	return NULL;
}

QVariant ModelSearchTableModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
{
	BaseItem *node = nodeFromIndex(index);
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
				if(typeData)
					return *PixmapManager()->get(typeData->icon);
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

bool ModelSearchTableModel::setData( const QModelIndex & index, const QVariant & value, int role /*= Qt::EditRole*/ )
{
	if(role==Qt::EditRole){
		BaseItem *node = nodeFromIndex(index);
		if (!node)
			return QAbstractItemModel::setData(index,value,role);

		return _currentPropertiesParents[index.column()-1]->setData(node,
			_currentPropertiesIndex[index.column()-1],value);
	}
	return false;
}

Qt::ItemFlags ModelSearchTableModel::flags( const QModelIndex &index ) const
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

QVariant ModelSearchTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
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


void ModelSearchTableModel::doc_ModelReseted( BaseItem* rootItem )
{
	_itemlist.clear();
	updateAll();
}

void ModelSearchTableModel::doc_RootItemChanged( BaseItem* currentRoot,BaseItem* oldRoot )
{
	_itemlist.clear();
	updateAll();
}

void ModelSearchTableModel::onActiveViewChanged( View* view )
{
	updateAll();
}

void ModelSearchTableModel::onModelStatusChanged( int )
{
	updateAll();
}

void ModelSearchTableModel::updateAll()
{
	updateColumns();
	reset();
	emit structChanged();
}

void ModelSearchTableModel::updateSearchResult(const QList<BaseItem*>& vec)
{
	Console().Log("updateSearchResult %d",vec.size());
	_itemlist=vec;
	reset();
}
