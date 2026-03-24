#include "filetablemodel.h"

FileTableModel::FileTableModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

FileTableModel::~FileTableModel()
{
}

int FileTableModel::rowCount( const QModelIndex &parent ) const
{
	return _files.count();
}

int FileTableModel::columnCount( const QModelIndex &parent ) const
{
	return 1;
}

QVariant FileTableModel::data( const QModelIndex &index, int role ) const
{
	if (!index.isValid())
		return QVariant();

	int row=index.row();
	int column=index.column();

	if(role==Qt::DisplayRole)
	{
		switch(column){
		case 0:
			return _files[row];
			break;
		}
	}
	return QVariant();
}

QVariant FileTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if(role==Qt::DisplayRole){
		if(orientation==Qt::Horizontal){
			switch(section){
			case 0:
				return tr("Need to update Files");
				break;
		
			default:
				return QVariant();
			}
		}
	}
	return QVariant();
}

void FileTableModel::resetTable( const QStringList& list )
{
	_files = list ;
	this->reset();
}

