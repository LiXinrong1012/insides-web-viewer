#include "sourcedatamodel.h"

#include "base/Console.h"
#include "base/activeviewobject.h"

#include "precore/BaseItem.h"
#include "precore/precore_data.h"
#include "precore/FEMPartBaseItem.h"
#include "precore/IResultItem.h"
#include "precore/ModelDocument.h"
#include "precore/FlexResultItem.h"
#include "precore/DynamicResultItem.h"
#include "precore/precore_data.h"

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

	int len1=doubleCount + 4;//20
	int len2=doubleCount;//13
	if(len==1)
		return QString("%1").arg(d[0],len1,'e',len2);

	QString a=QString("%1").arg(d[0],len1,'e',len2);
	for(int i=1;i<len;++i)
		a=a+QString(",    %1").arg(d[i],len1,'e',len2);
	return a;
}

SourceDataModel::SourceDataModel(QObject *parent)
	: QAbstractTableModel(parent)
	,_doubleCount(5)
{
}

SourceDataModel::~SourceDataModel()
{
}

int SourceDataModel::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	int t=getReulstType();
	if(t==0)
		return 0;

	IResultItem* tmpResultItem=_resultItem.data();

	switch(t){
	case TDY_POST_ITEMCLASS_FLEX:
		{
			if(_sectionIndex==0)
				return 1;
		/*	if(_sectionIndex != 1)
				return 1;*/
			FlexResultItem* flexResult=(FlexResultItem*)tmpResultItem;
				
			return flexResult->getSection(_sectionIndex)->numOfNodeOrElement;
		}
		break;
	case TDY_POST_ITEMCLASS_DYNAMICRIGID:
		{
			DynamicResultItem* dynamicResultItem=(DynamicResultItem*)tmpResultItem;
			return dynamicResultItem->getPieceCount();
		}
	default:
			return 1;
	}
	return 0;
}

int SourceDataModel::columnCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	int t=getReulstType();
	if(t==0)
		return 0;

	IResultItem* tmpResultItem=_resultItem.data();
	switch(t){
	case TDY_POST_ITEMCLASS_FLEX:
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

QVariant SourceDataModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
{
	if(!index.isValid())
		return QVariant();

	int row=index.row();
	int column=index.column();

	int t=getReulstType();
	if(t==0){
		Console().Error("Result type shouldn't be zero.");
		return QVariant();
	}
	if(role == Qt::DisplayRole)
	{
		IResultItem* tmpResultItem=_resultItem.data();
		switch(t){
		case TDY_POST_ITEMCLASS_FLEX:
			{
				if(_sectionIndex==0){//ÓÒ±ßµÄÏÂÀ­¿ò
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
		case TDY_POST_ITEMCLASS_DYNAMICRIGID:
			{
				IResultItem* resItem=tmpResultItem;
				IResultItem::Precision* data=resItem->getData(column);
				int rCount=resItem->subSectionCount(column);

				return dataArray2QString(data+row*resItem->getDataLength(),rCount,_doubleCount);
			}
		default:
			{
				IResultItem* resItem=tmpResultItem;
				IResultItem::Precision* data=resItem->getData(column);
				int rCount=resItem->subSectionCount(column);

				return dataArray2QString(data,rCount,_doubleCount);
			}
		}
	}
	return QVariant();
}

bool SourceDataModel::updateTitle()
{
	_resultItem=getRelatedResultItem(_itemTitle.itemName);
	_sectionIndex=_itemTitle.secIndex;
	if(!_resultItem)
		return false;
	return true;
}

QWeakPointer<IResultItem> SourceDataModel::getRelatedResultItem( const QString& itemname )
{
	BaseItem* item=myDocument()->findItem(itemname);
	if(!item)
		return QWeakPointer<IResultItem>();

	if(myResultDocument()->getResults())
		return myResultDocument()->getResults()->findResultItem(item);

	return QWeakPointer<IResultItem>();
}
void SourceDataModel::onItemAdding( TableItemTitle itemTitle )
{
	_itemTitle=itemTitle;
	if(!updateTitle())
		return;

	reset();
	emit newDataAdded();
}

int SourceDataModel::getReulstType()const
{
	if(!_resultItem)
		return 0;
	//return _resultItem.data()->connectedItem()->getCategory();
	return _resultItem.data()->getClassType();
}

void SourceDataModel::clearData()
{
	_resultItem=QWeakPointer<IResultItem>();
}

QVariant SourceDataModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
{
	if(role!=Qt::DisplayRole)
		return QVariant();

	int t=getReulstType();
	
	if(t==0)
		return QVariant();

	IResultItem* tmpResultItem=_resultItem.data();
	if(orientation==Qt::Horizontal){
		if(t==TDY_POST_ITEMCLASS_FLEX){
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
		if(t==TDY_POST_ITEMCLASS_FLEX)
		{
			if(_sectionIndex==0)
				return tmpResultItem->connectedItem()->getKeyName();
		}
		else
			return tmpResultItem->connectedItem()->getKeyName();

		return QString("%1").arg(section+1);
	}
	return QVariant();
}

void SourceDataModel::onResetLayout()
{
	emit layoutChanged();
}

void SourceDataModel::onNotifyUpdate( TableItemTitle ItemTitle )
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

void SourceDataModel::onResultDeleted()
{
	this->clearData();
	reset();
}

void SourceDataModel::setItemTitle( const TableItemTitle& title )
{
	_itemTitle=title;
	updateTitle();
	reset();
	emit newDataAdded();
}


