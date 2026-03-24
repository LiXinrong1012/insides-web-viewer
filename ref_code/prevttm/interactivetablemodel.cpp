#include "interactivetablemodel.h"

#include "base/Console.h"
#include "base/activeviewobject.h"

#include "precore/BaseItem.h"
#include "precore/precore_data.h"
#include "precore/FEMPartBaseItem.h"
#include "precore/IResultItem.h"
#include "precore/ModelDocument.h"
#include "precore/FlexResultItem.h"

#include "prefem/JMesh.h"
#include "prefem/JMeshGroup.h"
#include "prefem/prefem_def.h"
#include "prefem/MeshGlobal.h"

#include <QStringBuilder>

using namespace Base;

static QString dataArray2QString(double* d,int len,int doubleCount)
{
	if(len==0)
		return QString();

	static int len1=0;//20
	int len2=doubleCount;//13
	QString testString = QString("%1").arg(d[0],len1,'e',len2);
	QString testString2 = QString("%1").arg(d[0],len1,'e',len2);
	if(len==1)
		return QString("%1").arg(d[0],len1,'e',len2);

	QString a=QString("%1").arg(d[0],len1,'e',len2);
	for(int i=1;i<len;++i)
		a=a+QString(",    %1").arg(d[i],len1,'e',len2);
	return a;
}

InteractiveTableModel::InteractiveTableModel(QObject *parent)
	: QAbstractTableModel(parent)
	,_doubleCount(13)
{
}

InteractiveTableModel::~InteractiveTableModel()
{
}

int InteractiveTableModel::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	return itemRowCount()*_resultItemList.size();
}

int InteractiveTableModel::itemRowCount() const
{
	int t=getReulstType();
	if(t==0)
		return 0;

	IResultItem* tmpResultItem=_resultItemList[0].data();

	switch(t){
	case TDY_PRE_CATE_FEMPART:
		{
			if(_sectionIndex==0)
				return 1;

			FlexResultItem* flexResult=(FlexResultItem*)tmpResultItem;
			return flexResult->getSection(_sectionIndex)->numOfNodeOrElement;
		}
		break;
	default:
			return 1;
	}
	return 0;
}

int InteractiveTableModel::columnCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	return itemColumnCount();
}

int InteractiveTableModel::itemColumnCount() const
{
	int t=getReulstType();
	if(t==0)
		return 0;

	IResultItem* tmpResultItem=_resultItemList[0].data();
	switch(t){
	case TDY_PRE_CATE_FEMPART:
		{
			if(_sectionIndex==0)
				return tmpResultItem->subSectionCount(0);

			FlexResultItem* flexResult=(FlexResultItem*)tmpResultItem;
				
			return flexResult->subSectionCount(_sectionIndex)+1;
		}
		break;
	default:
			return tmpResultItem->sectionCount();
	}
	return 0;
}

QVariant InteractiveTableModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
{
	if(!index.isValid())
		return QVariant();
	if(role!=Qt::DisplayRole)
		return QVariant();

	int Grow=index.row();
	int column=index.column();
	int itemIndex=Grow/_itemRowCount;
	int row=Grow%_itemRowCount;

	int t=getReulstType();
	if(t==0){
		Console().Error("Result type shouldn't be zero.");
		return QVariant();
	}

	IResultItem* tmpResultItem=_resultItemList[itemIndex].data();
	switch(t){
	case TDY_PRE_CATE_FEMPART:
		{
			if(_sectionIndex==0){
				IResultItem::Precision* data=tmpResultItem->getData(0,column);
				int rCount=tmpResultItem->subsubSectionCount(0,column);
				return dataArray2QString(data,rCount,_doubleCount);
			}			
			
			FlexResultItem* flexResult=(FlexResultItem*)tmpResultItem;
			if(column==0){	//ID
				if(_sectionIndex==1){
					FEMPartBaseItem* flexResultItem=flexResult->getFEMBaseItem();
					return int(flexResultItem->getFEMPart()->m_Mesh.GetNode(row)->NID);
				}
				else{
					FEMPartBaseItem* flexResultItem=flexResult->getFEMBaseItem();
					JMeshGroup* meshGroup=flexResultItem->getFEMPart()->m_Group.getGroupList()[_sectionIndex-2];
					int elemIndex=meshGroup->getElems()[row];
					return int(flexResultItem->getFEMPart()->m_Mesh.GetElement(elemIndex)->EID);
				}
			}

			//int tmpCount=0;
			//if(_sectionIndex==1) // node variables
			//	tmpCount=flexResult->getNodeCount();
			//else if(_sectionIndex==2)
			//	tmpCount=flexResult->getElementCount();

			//if(tmpCount==0){
			//	Console().Error("Unknown fempart result section.");
			//	return QVariant();
			//}
				
			int rCount=flexResult->subsubSectionCount(_sectionIndex,column-1);
			//IResultItem::Precision* data=flexResult->getData(_sectionIndex,column-1);
			//data+=rCount*row;

			IResultItem::Precision* data=flexResult->getNodeElemData(_sectionIndex,column-1,row);
			return dataArray2QString(data,rCount,_doubleCount);
		}
		break;
	default:
		{
			IResultItem* resItem=tmpResultItem;
			IResultItem::Precision* data=resItem->getData(column);
			int rCount=resItem->subSectionCount(column);

			return dataArray2QString(data,rCount,_doubleCount);
		}
	}
	return 0;
}

bool InteractiveTableModel::updateTitle()
{
	_sectionIndex=_itemTitle.secIndex;
	updateRowColumnCount();
	return true;
}

QWeakPointer<IResultItem> InteractiveTableModel::getRelatedResultItem( const QString& itemname )
{
	BaseItem* item=myDocument()->findItem(itemname);
	if(!item)
		return QWeakPointer<IResultItem>();

	if(myResultDocument()->getResults())
		return myResultDocument()->getResults()->findResultItem(item);

	return QWeakPointer<IResultItem>();
}
void InteractiveTableModel::onItemAdding( TableItemTitle itemTitle )
{
	_itemTitle=itemTitle;
	if(!updateTitle())
		return;

	reset();
	emit newDataAdded();
	return;
}

int InteractiveTableModel::getReulstType()const
{
	if(_resultItemList.size()==0)
		return 0;
	IResultItem* resultItem = _resultItemList[0].data();
	if(resultItem)
	{
		BaseItem* item = resultItem->connectedItem();
		return item->getCategory();
	}
	else
		return 0;
}

void InteractiveTableModel::clearData()
{
	_resultItemList.clear();
	updateRowColumnCount();
}

QVariant InteractiveTableModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
{
	if(role!=Qt::DisplayRole)
		return QVariant();

	int t=getReulstType();
	if(t==0)
		return QVariant();

	if(orientation==Qt::Horizontal){
		IResultItem* tmpResultItem=_resultItemList[0].data();
		if(t==TDY_PRE_CATE_FEMPART){
			if(_sectionIndex==0 ){
				return tmpResultItem->subSectionName(_sectionIndex,section);
			}
			else{
				if(section==0)
					return "ID";
				return tmpResultItem->subSectionName(_sectionIndex,section-1);
			}
		}
		else
			return tmpResultItem->sectionName(section);

		return "Error";
	}
	else if(orientation==Qt::Vertical){
		int itemIndex=section/_itemRowCount;
		IResultItem* tmpResultItem=_resultItemList[itemIndex].data();
		if(t==TDY_PRE_CATE_FEMPART)
		{
			if(_sectionIndex==0)
				return tmpResultItem->connectedItem()->getFullName();
		}
		else
			return tmpResultItem->connectedItem()->getFullName();

		return tmpResultItem->connectedItem()->getFullName();
	}
	return QVariant();
}

void InteractiveTableModel::resetLayout()
{
	emit layoutChanged();
}


void InteractiveTableModel::onNotifyUpdate( TableItemTitle ItemTitle )
{
	if(!updateTitle()){
		_itemTitle=ItemTitle;
		if(!updateTitle())
			return;
	}

	reset();
	emit newDataAdded();
	return;
}

void InteractiveTableModel::onResultDeleted()
{
	this->clearData();
	reset();
}

void InteractiveTableModel::setItemTitle( const TableItemTitle& title )
{
	_itemTitle=title;
	updateTitle();
	reset();
	emit newDataAdded();
}

void InteractiveTableModel::updateRowColumnCount()
{
	_itemRowCount=itemRowCount();
	_itemColumnCount=itemColumnCount();
}

void InteractiveTableModel::setBaseItemList( const QList<BaseItem*>& baseItemList )
{
	int count=baseItemList.size();
	IResults* results=myResultDocument()->getResults();
	if(!results || !count)
		return;

	int tmpType=baseItemList[0]->getCategory();
	_baseItemList.clear();
	_resultItemList.clear();
	for(int i=0;i<count;++i)
	{
		BaseItem* item=baseItemList[i];
		if(item->getCategory()==tmpType)
		{
			QWeakPointer<IResultItem> resultItem=results->findResultItem(item);
			if(!resultItem.isNull())
			{
				_baseItemList.push_back(item);
				_resultItemList.push_back(resultItem);
			}
		}
	}
	updateRowColumnCount();
	reset();
		
	emit newDataAdded();
}

void InteractiveTableModel::setDataToFrame( int frameIndex )
{
	for(int i=0;i<_resultItemList.size();++i)
		_resultItemList[i].data()->setPos(frameIndex);
}

void InteractiveTableModel::onResetLayout()
{
	emit layoutChanged();
}


