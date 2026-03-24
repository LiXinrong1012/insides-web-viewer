#ifndef MODELVIEWMODEL_H
#define MODELVIEWMODEL_H

#include "edparse/edparse_global.h"
#include <QAbstractItemModel>

namespace INSEditor{
	class Entity;
	namespace Parse
	{
		class AssemblyItem;
	}
}

using INSEditor::Entity;
using INSEditor::Parse::AssemblyItem;

/*!
	@brief   该类为模型结构树的模型部分
	@date    2015.6.17
	@author  Jianjun
*/
class EDPARSE_EXPORT ModelViewModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	ModelViewModel(QObject *parent);
	~ModelViewModel();

	///重写QAbstractItemModel虚函数部分
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual QModelIndex parent(const QModelIndex &index) const;
	virtual QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const;
	
	///设置rootItem
	void setRootItem(AssemblyItem* rt);

	///获取rootItem
	const AssemblyItem* getRootItem(){return _rootItem;}

public slots:
	///当有entity激活时调用
	void onEntityActivated(INSEditor::Parse::AssemblyItem* item,const QString& fileName);

	///当模型item点击时调用
	void onModelItemClicked(const QModelIndex & current);

	///当编译项改变时调用
	void onCompileItemChanged(const QString& fileName,AssemblyItem* fileItem);

private:
	///根节点rootItem
	const AssemblyItem *_rootItem;

	///编译的模型树全名
	QString		_entityFullName;

private:
	
};

#endif // MODELVIEWMODEL_H
