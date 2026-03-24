#include "proxydatamodel.h"
#include "exchange.h"
#include "interactivetableview.h"
#include "originaldatamodel.h"

#include <QtGui>

#define INS_TABLE_SORT_BY_LENGTH 1000

ProxyDataModel::ProxyDataModel(QObject *parent,InteractiveTableModel* sourceModel)
	: QSortFilterProxyModel(parent)
	,_sourceModel(sourceModel)
	,_enableMySort(false)
	,_isRealModel(true)
	,_modelType(false)
	,_isChange(false)
{
	setSourceModel(sourceModel);
}

ProxyDataModel::~ProxyDataModel()
{

}


bool ProxyDataModel::lessThan( const QModelIndex & left, const QModelIndex & right ) const
{
	if(_enableMySort)
	{
		if (_component == 0 || _component == 1 || _component == 2)
		{
			QString s1,s2;
			if(_isRealModel)
			{
				s1=_sourceModel->data(left,Qt::DisplayRole).toString();
				s2=_sourceModel->data(right,Qt::DisplayRole).toString();
			}
			else
			{
				s1=_sourceExchangeModel->data(left,Qt::DisplayRole).toString();
				s2=_sourceExchangeModel->data(right,Qt::DisplayRole).toString();
			}

			if (s1.split(",").count()>_component)
			{
				double d1=s1.split(",")[_component].trimmed().toDouble();
				double d2=s2.split(",")[_component].trimmed().toDouble();
				return d1<d2;
			}
			else
				return false;
		}
		if (_component == INS_TABLE_SORT_BY_LENGTH)
		{
			QString s1,s2;
			if(_isRealModel)
			{
				s1=_sourceModel->data(left,Qt::DisplayRole).toString();
				s2=_sourceModel->data(right,Qt::DisplayRole).toString();
			}
			else
			{
				s1=_sourceExchangeModel->data(left,Qt::DisplayRole).toString();
				s2=_sourceExchangeModel->data(right,Qt::DisplayRole).toString();
			}
			if (s1.split(",").count()>0)
			{

				double d1=0,d2=0;
				if (d1>0)
				{
					for (int i=0;i<s1.split(",").count();i++)
					{
						d1+= s1.split(",")[i].trimmed().toDouble();
						d2+= s2.split(",")[i].trimmed().toDouble();
					}
				}
				return d1<d2;
			}
			else
				return false;
		}
		else
			return false;
		
	}
	else{
		return QSortFilterProxyModel::lessThan(left,right);
	}

}

void ProxyDataModel::updateComponent( int component )
{
	_component = component;
	_enableMySort=true;
	this->reset();
}

QVariant ProxyDataModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
{
	return index.data();
}

QVariant ProxyDataModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
{
	return QVariant();
}

int ProxyDataModel::columnCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	if(!_isChange)
		return _sourceModel->columnCount();
	else
		return _sourceModel->rowCount();
}

int ProxyDataModel::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	if(_isChange)
		return _sourceModel->columnCount();
	else
		return _sourceModel->rowCount();
}
