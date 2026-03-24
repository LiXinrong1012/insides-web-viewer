/*
#include "errortablemodel.h"
#include "edcore/errormanager.h"

#include <QSortFilterProxyModel>

using namespace Parse;

ErrorTableModel::ErrorTableModel(QObject *parent)
	:QAbstractTableModel(parent)
	,_proxyModel(NULL)
{
	
}


int ErrorTableModel::rowCount(const QModelIndex &parent)const
{
	return 0;
	//return myProject()->getErrorItemManager()->count();
}

int ErrorTableModel::columnCount(const QModelIndex &parent)const
{
	return 5;
}

QVariant ErrorTableModel::data(const QModelIndex &index, int role)const
{
	if (!index.isValid())
		return QVariant();

	int row=index.row();
	int column=index.column();

	INSProject *project=myProject();	
	if(row>=project->getErrorItemManager()->count())
		return QVariant();

	if(role==Qt::DisplayRole)
	{
		const ErrorItem& tmpItem=*project->getErrorItemManager()->item(row);
		switch(column){
		case 0:
			return tmpItem.errorID;
			break;
		case 1:
			return tmpItem.fileName;
			break;
		case 2:
			return tr("line ")+QString::number(tmpItem.lineIndex+1)+tr(" and column ")+QString::number(tmpItem.columnIndex+2);
			break;
		case 3:
			return tmpItem.errorInfo;
			break;
		case 4:
			return tmpItem.possibleSolution;
			break;

		}
		return QString("%1-%2").arg(index.row()).arg(index.column());
	}
	return QVariant();
}

QVariant ErrorTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if(role==Qt::DisplayRole){
		if(orientation==Qt::Horizontal){
			switch(section){
			case 0:
				return tr("ID");
				break;
			case 1:
				return tr("File");
				break;
			case 2:
				return tr("Position");
				break;
			case 3:
				return tr("Description");
				break;
			case 4:
				return tr("Advice");
				break;
			default:
				return QVariant();
			}
		}
	}
	return QVariant();
}

void ErrorTableModel::onErrorListUpdated()
{
	reset();
	
}

void ErrorTableModel::showErrorMessage( QModelIndex index )
{
	QModelIndex realModel=_proxyModel->mapToSource(index);
	const Parse::ErrorItem* item = myProject()->getErrorItemManager()->item(realModel.row());
	myProject()->notifyGotoPosition(item->fileName,item->lineIndex,item->columnIndex);
}
*/