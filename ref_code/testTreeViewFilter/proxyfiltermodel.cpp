#include "proxyfiltermodel.h"

ProxyFilterModel::ProxyFilterModel(QObject *parent)
	: QSortFilterProxyModel(parent)
{

}

ProxyFilterModel::~ProxyFilterModel()
{

}


//SubClass of QSortFilterProxyModel
bool ProxyFilterModel::filterAcceptsRow(int sourceRow,
	const QModelIndex &sourceParent) const
{
	QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
	return ShowThis(index);
}


bool ProxyFilterModel::ShowThis(const QModelIndex index) const
{
	bool retVal = false;
	{
		QModelIndex useIndex = sourceModel()->index(index.row(), 0, index.parent());
		QString type = sourceModel()->data(useIndex, Qt::DisplayRole).toString();
		//if ( ! type.contains(filterRegExp()))
		if ( -1== type.indexOf(filterRegExp()))
		{
			retVal = false;
		}
		else
		{
			retVal = true;
		}
	}
	return retVal;
}
//
//bool ProxyFilterModel::ShowThis(const QModelIndex index) const
//{
//	bool retVal = false;
//	//Gives you the info for number of childs with a parent
//	if ( sourceModel()->rowCount(index) > 0 )
//	{
//		for( int nChild = 0; nChild < sourceModel()->rowCount(index); nChild++)
//		{
//			QModelIndex childIndex = sourceModel()->index(nChild,0,index);
//			if ( ! childIndex.isValid() )
//				break;
//			retVal = ShowThis(childIndex);
//			if (retVal)
//			{
//				break;
//			}
//		}
//	}
//	else
//	{
//		QModelIndex useIndex = sourceModel()->index(index.row(), 0, index.parent());
//		QString type = sourceModel()->data(useIndex, Qt::DisplayRole).toString();
//		//if ( ! type.contains(filterRegExp()))
//		if ( -1== type.indexOf(filterRegExp()))
//		{
//			retVal = false;
//		}
//		else
//		{
//			retVal = true;
//		}
//	}
//	return retVal;
//}