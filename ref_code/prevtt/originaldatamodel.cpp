#include "originaldatamodel.h"

OriginalDataModel::OriginalDataModel(QObject *parent)
	: QAbstractTableModel(parent)
{

}

OriginalDataModel::~OriginalDataModel()
{

}

QVariant OriginalDataModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
{
	if(role==Qt::DisplayRole)
	{
		int row=index.row();
		int column=index.column();

		if(column==0)
			return QString("%1,%2,%3").arg(row).arg(3).arg(column);
		else
			return QString("%1,%2,%3").arg(10-row).arg(3).arg(column);
	}
	return QVariant();
}
