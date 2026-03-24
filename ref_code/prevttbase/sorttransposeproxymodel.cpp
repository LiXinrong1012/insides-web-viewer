#include "sorttransposeproxymodel.h"
#include "sorttableview.h"

#include <QtGui>

#define INS_TABLE_SORT_BY_LENGTH 1000

SortTransposeProxyModel::SortTransposeProxyModel()
	: QSortFilterProxyModel()
	,_enableMySort(false)
	,_isTranspose(false)
	,_component(0)
{
}

SortTransposeProxyModel::~SortTransposeProxyModel()
{
}

bool SortTransposeProxyModel::lessThan( const QModelIndex & left, const QModelIndex & right ) const
{
	if(_enableMySort)
	{
		//从0开始，逗号分割，得到相应子列
		if (_component != INS_TABLE_SORT_BY_LENGTH)
		{
			QString s1,s2;
			
			s1=this->sourceModel()->data(left,Qt::DisplayRole).toString();
			s2=this->sourceModel()->data(right,Qt::DisplayRole).toString();

			if (s1.split(",",QString::SkipEmptyParts).count()>_component)
			{
				double d1=s1.split(",")[_component].trimmed().toDouble();
				double d2=s2.split(",")[_component].trimmed().toDouble();
				return  d1<d2;
			}
			else
				return false;
		}
		else
		{
			QString s1,s2;
			
			s1=this->sourceModel()->data(left,Qt::DisplayRole).toString();
			s2=this->sourceModel()->data(right,Qt::DisplayRole).toString();
			
			if (s1.split(",",QString::SkipEmptyParts).count()>0)
			{

				double d1=0,d2=0;
				for (int i=0;i<s1.split(",").count();i++)
				{
					d1+= s1.split(",")[i].trimmed().toDouble();
					d2+= s2.split(",")[i].trimmed().toDouble();
				}

				return d1<d2;
			}
			else
				return false;
		}
	}
	else
		return QSortFilterProxyModel::lessThan(left,right);
}

void SortTransposeProxyModel::updateComponent( int component )
{
	_component = component;
	_enableMySort=true;
}

QVariant SortTransposeProxyModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
{
	if(role == Qt::BackgroundColorRole )
	{
		if(index.row()%2 == 0)
		{
			QColor color;
			color.setRgb(220,230,241);
			return color;
		}
		else if(index.row()%5 == 1)
			return QColor(Qt::white);
	}
	if(_isTranspose)
		return sourceModel()->data(mapToSource(index), role);
	else if(!_enableMySort)
		return sourceModel()->data(mapToSource(index),role);

	return QSortFilterProxyModel::data(index,role);
}

QVariant SortTransposeProxyModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
{
	if(_isTranspose)
	{
		if (orientation == Qt::Horizontal)
			return this->sourceModel()->headerData(section,Qt::Vertical,role);
		else
			return this->sourceModel()->headerData(section,Qt::Horizontal,role);
	}
	else
	{
		if (orientation == Qt::Vertical)
			return this->sourceModel()->headerData(section,Qt::Vertical,role);
		else
			return this->sourceModel()->headerData(section,Qt::Horizontal,role);
	}
}

int SortTransposeProxyModel::columnCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	if(!_isTranspose)
		return this->sourceModel()->columnCount();
	else
		return this->sourceModel()->rowCount();
}

int SortTransposeProxyModel::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	if(_isTranspose)
		return this->sourceModel()->columnCount();
	else
		return this->sourceModel()->rowCount();
}

QModelIndex SortTransposeProxyModel::mapFromSource( const QModelIndex & sourceIndex ) const
{
	if(_isTranspose)
		return index(sourceIndex.column(), sourceIndex.row());
	else if(!_enableMySort)
		return index(sourceIndex.row(),sourceIndex.column());
	
	return QSortFilterProxyModel::mapFromSource(sourceIndex);
}

QModelIndex SortTransposeProxyModel::mapToSource( const QModelIndex & proxyIndex ) const
{
	QAbstractItemModel* m = this->sourceModel();
	if(!proxyIndex.isValid() || !m)
		return QModelIndex();

	if(_isTranspose)
		return m->index(proxyIndex.column(), proxyIndex.row());

	if(_enableMySort)
		return QSortFilterProxyModel::mapToSource(proxyIndex);
		
	return m->index(proxyIndex.row(), proxyIndex.column());
}

QModelIndex SortTransposeProxyModel::index( int r, int c, const QModelIndex &index/*=QModelIndex()*/ ) const
{
	if(_isTranspose)
		return createIndex(r,c);	
	else
		return QSortFilterProxyModel::index(r,c,index);
}

QModelIndex SortTransposeProxyModel::parent( const QModelIndex& ) const
{
	return QModelIndex();
}

