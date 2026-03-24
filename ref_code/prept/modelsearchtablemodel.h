#ifndef MODELSEARCHTABLEMODEL_H
#define MODELSEARCHTABLEMODEL_H

#include "precore/precore_global.h"
#include <QAbstractTableModel >

#include "precore/modeldocumentlistener.h"

#include "IModelViewColumns.h"

#include "mtsearchengine/mtsearchengine.h"


namespace Base{class View;}
using Base::View;

namespace INSIDES
{
	class BaseItem;
}

using namespace INSIDES;

class ModelSearchTableModel : public 	QAbstractTableModel 
	, public ModelDocumentListener
	, public IModelColumns
{
	Q_OBJECT

public:
	ModelSearchTableModel(QObject *parent);
	~ModelSearchTableModel();

	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
	virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role) const;



	BaseItem* getItem(int row){return _itemlist[row];}

public slots:
	void updateSearchResult(const QList<BaseItem*>& vec);

signals:
	void structChanged();

protected slots:
	void onActiveViewChanged(View* view);
	void onModelStatusChanged(int );

protected:
	/// 当模型被重致后发送
	void doc_ModelReseted(BaseItem* rootItem);
	/// 显示的根节点改变后发送
	void doc_RootItemChanged(BaseItem* currentRoot,BaseItem* oldRoot);

private:
	QList<BaseItem*>	_itemlist;

	BaseItem *nodeFromIndex(const QModelIndex &index) const;
	void updateAll();
};


#endif // MODELSEARCHTABLEMODEL_H
