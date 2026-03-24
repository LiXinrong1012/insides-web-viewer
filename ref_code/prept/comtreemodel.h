#ifndef COMTREEMODEL_H
#define COMTREEMODEL_H

#include <QAbstractItemModel>
#include <QScopedPointer>
#include <QWeakPointer>

#include "precore/modeldocumentlistener.h"

#include "IModelViewColumns.h"


namespace Base{ class View; }

using Base::View;

class ITreeItemProperties;
class TreeItemProperty;
class ITreeItemPropertyFunc;

namespace INSIDES
{
	class BaseItem;
	class ModelDocument;
	class AppearanceItem;
}

using namespace INSIDES;



typedef INSIDES::BaseItem ItemClass;


class ComTreeModel : public QAbstractItemModel
	, public ModelDocumentListener
	, public IModelColumns
{
	Q_OBJECT

public:
	ComTreeModel(QObject *parent=0);
	~ComTreeModel();

	void refrushModel();
	void refrushData(ItemClass* node);
	void resetModel();


	void setRootNode(ItemClass *node);


	QModelIndex index(int row, int column,
		const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex &child) const;

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role) const;
	ItemClass *nodeFromIndex(const QModelIndex &index) const;
	QModelIndex indexFromNode(const ItemClass* node)const;
	
	void updateHeaderStruct();
signals:
	/// 当数据结构变化时发出
	void structChanged();

	void viewModelBeginChanging();
	void viewModelChanged();

protected:

	/// 当节点将要添加时发送
	//void doc_BeginItemAdding(BaseItem* item,BaseItem* parent,int pos);

	/// 当节点添加后发送
	void doc_ItemAdded(BaseItem* item,bool isIncludingChildren);
	/// 当节点更改后发送
	void doc_ItemModified(BaseItem* item,bool isIncludingChildren);
	/// 当节点将要删除时发送
	void doc_BeginItemRemoving(BaseItem* item);
	/// 当节点删除后发送
	void doc_ItemRemoved(BaseItem* parent,BaseItem* item);
	/// 当模型被重致后发送
	void doc_ModelReseted(BaseItem* rootItem);
	/// 显示的根节点改变后发送
	void doc_BeginRootItemChanging(BaseItem* currentRoot,BaseItem* newRoot);
	/// 显示的根节点改变后发送
	void doc_RootItemChanged(BaseItem* currentRoot,BaseItem* oldRoot);
	/// 参数条目改变时发送
	void doc_ParametersChanged(BaseItem* parametersItem);

	/// 开始保存文档时发送
	//void doc_BeginSavingDocument();

	/// 结果保存文档时发送
	//void doc_EndSavingDocument();


protected slots:
	void onActiveViewChanged(View* view);
	void onModelStatusChanged(int );

protected:
	void updateCurrentItems();
	void updateTreeItems();

private:

	ItemClass *_rootNode;


};


#endif // COMTREEMODEL_H
