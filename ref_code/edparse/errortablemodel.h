/*
#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QMessageBox>
#include <QtCore>

#include "edcore/mainitem.h"

class QSortFilterProxyModel;

class ErrorTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	ErrorTableModel(QObject *parent=0);

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void setProxyModel(QSortFilterProxyModel* model){_proxyModel=model;}

	public slots:
		void onErrorListUpdated();
		void showErrorMessage( QModelIndex index );

private:

	//Parse::ErrorItemManager*	_errorItemManager;
	QSortFilterProxyModel*		_proxyModel;
};





#endif


*/