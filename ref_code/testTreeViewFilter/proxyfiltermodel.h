#ifndef PROXYFILTERMODEL_H
#define PROXYFILTERMODEL_H

#include <QSortFilterProxyModel>

class ProxyFilterModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	ProxyFilterModel(QObject *parent);
	~ProxyFilterModel();
	bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
	bool ShowThis(const QModelIndex index) const;
private:
	
};

#endif // PROXYFILTERMODEL_H
