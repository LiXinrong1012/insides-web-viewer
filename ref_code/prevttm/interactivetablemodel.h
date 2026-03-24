#ifndef INTERACTIVETABLEMODEL_H
#define INTERACTIVETABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QWeakPointer>

#include "prevttbase/resultselectorwidget.h"
namespace INSIDES{
	class IResultItem;
}


/*!
*	多项显示交互式数据表格的模型。
*	目前主要有二种显示模式：
*	1. 显示刚体的数据，此种情形下，可能添加数个刚体。
*	2. 显示某个FEMPart的Part或者节点或者单元的数据。
*	@author Jerry He
*	@date	2014.4.23
*/
class InteractiveTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	InteractiveTableModel(QObject *parent);
	~InteractiveTableModel();

	///行数
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;

	///列数
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const ;

	///单元格数据
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;

	///静养数据
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

	///重置布局
	void resetLayout();

	/// 删除所有数据
	void clearData();

	///获得条目信息
	TableItemTitle getItemTitle()const{return _itemTitle;}

	///设置条目信息
	void setItemTitle(const TableItemTitle& title);

	///获得结果类型
	int getReulstType()const;

	///获得结果条目
	IResultItem* getResultItem(int index){return _resultItemList[index].data();}

	///获得选择的索引值
	int getSectionIndex()const{return _sectionIndex;}

	///设置表格展示的条目列表
	void setBaseItemList(const QList<BaseItem*>& baseItemList);

	///获得表格展示的条目列表
	QList<BaseItem*> getBaseItemList()const;

	///设置数据到帧数
	void setDataToFrame(int frameIndex);

	///获得有效小数位
	int getDoubleCount(){return _doubleCount;}

	///设置有效的小数点位数
	void setDoubleCount(int count){_doubleCount = count;}

signals:
	///有新的数据添加时发出
	void newDataAdded();

public slots:
	///添加新的数据时调用 
	void onItemAdding(TableItemTitle ItemTitle);

	///当通知更新的调用
	void onNotifyUpdate(TableItemTitle ItemTitle);

	///当结果发删除后调用
	void onResultDeleted();

	///重置布局槽
	void onResetLayout();

private:
	///更新条目信息
	bool updateTitle();

	///更新行数和列数
	void updateRowColumnCount();

	///通过itemName 获得相关的结果条目
	QWeakPointer<IResultItem> getRelatedResultItem( const QString& itemname );

	///返回条目行数
	int itemRowCount() const;

	///返回条目列数
	int itemColumnCount() const;

	///条目信息
	TableItemTitle		_itemTitle;

	///存储显示的条目列表
	QList<BaseItem*>		_baseItemList;

	///结果条目列表 
	QList<QWeakPointer<IResultItem> >	_resultItemList;

	///选择的项
	int					_sectionIndex;

	///行数
	int					_itemRowCount;

	///列数
	int					_itemColumnCount;

	///小数点的有效位数
	int					_doubleCount;
};

#endif // INTERACTIVETABLEMODEL_H
