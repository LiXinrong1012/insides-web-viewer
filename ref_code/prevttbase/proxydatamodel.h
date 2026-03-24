#ifndef PROXYDATAMODEL_H
#define PROXYDATAMODEL_H

#include <QSortFilterProxyModel>

class InteractiveTableModel;
class ExchangeModel;

class ProxyDataModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	ProxyDataModel(QObject *parent,InteractiveTableModel* sourceModel);
	~ProxyDataModel();

	virtual QVariant	data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual QVariant	headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;

	public slots:
		void updateComponent(int component);

protected:	
	virtual bool lessThan(const QModelIndex & left, const QModelIndex & right ) const;

private:
	InteractiveTableModel* _sourceModel;
	ExchangeModel* _sourceExchangeModel;
	bool _enableMySort;
	///记录是否为真正的Model还是exchangeModel;
	bool _isRealModel;
	bool _modelType;
	int _component;
	///是否转制
	bool _isChange;
};

#endif // PROXYDATAMODEL_H
