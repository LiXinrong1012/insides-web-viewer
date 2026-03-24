#ifndef INTERACTIVETABLEMODEL_H
#define INTERACTIVETABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QWeakPointer>

#include "prevttbase/resultselectorwidget.h"

namespace INSIDES{
class IResultItem;
}

using namespace INSIDES;

/*!
	@biref   源model类实现
	@date    2015.7.1
	@author  Jerry
*/
class SourceDataModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	SourceDataModel(QObject *parent);
	~SourceDataModel();

	///行数
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;

	///列数
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const ;

	///单元格数据
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;

	///表头数据
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

	/// 删除所有数据
	void clearData();

	///获得条目信息
	TableItemTitle getItemTitle()const{return _itemTitle;}

	///设置条目信息
	void setItemTitle(const TableItemTitle& title);

	///获得结果类型
	int getReulstType()const;

	///获得结果条目
	IResultItem* getResultItem(){return _resultItem.data();}

	///获得选择索引项
	int getSectionIndex()const{return _sectionIndex;}

	///获得小数点位数
	int getDoubleCount(){return _doubleCount;}const

	///设置小数点位数
	void setDoubleCount(int count){_doubleCount = count;}

public slots:
	///当有新数据添加时调用
	void onItemAdding(TableItemTitle ItemTitle);

	///通知更新
	void onNotifyUpdate(TableItemTitle ItemTitle);

	///当结果删除后调用
	void onResultDeleted();

	///重置布局
	void onResetLayout();

signals:
	///新的数据添加后发出
	void newDataAdded();

private:
	///更新条目信息
	bool updateTitle();

	///获得相关的结果条目
	QWeakPointer<IResultItem> getRelatedResultItem( const QString& itemname );

private:
	///条目信息
	TableItemTitle		_itemTitle;

	///结果条目
	QWeakPointer<IResultItem>		_resultItem;

	///选择索引项
	int					_sectionIndex;

	///小数位
	int					_doubleCount;
};

#endif // INTERACTIVETABLEMODEL_H
