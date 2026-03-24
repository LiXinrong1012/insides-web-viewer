#ifndef ORIGINALDATAMODEL_H
#define ORIGINALDATAMODEL_H

#include <QAbstractTableModel>

class OriginalDataModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	OriginalDataModel(QObject *parent);
	~OriginalDataModel();

	int rowCount(const QModelIndex &)const{return 4;}
	int columnCount(const QModelIndex &)const{return 2;}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole ) const ;

private:
	
};

#endif // ORIGINALDATAMODEL_H
