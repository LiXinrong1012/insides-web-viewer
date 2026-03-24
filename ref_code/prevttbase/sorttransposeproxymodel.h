#ifndef PROXYDATAMODEL_H
#define PROXYDATAMODEL_H

#include <QSortFilterProxyModel>

class SortTableView;

/*!
	@brief   排序转换代理MODEL，用于排序转换，服务于两种表格
	@date    2015.7.1
	@author  Jianjun
*/
class SortTransposeProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	SortTransposeProxyModel();
	~SortTransposeProxyModel();

	///重写实现虚方法表格数据实现
	virtual QVariant	data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

	///重写实现虚方法表头数据实现
	virtual QVariant	headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

	///重写实现虚方法列数实现
	virtual int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;

	///重写实现虚方法行数实现
	virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;

	///重写实现虚方法从源映射
	virtual QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const;

	///重写实现虚方法映射到源
	virtual QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const;

	///重写实现虚方法获取索引项
	virtual QModelIndex index(int r, int c, const QModelIndex &index=QModelIndex()) const;

	///重写实现虚方法获取父索引
	virtual QModelIndex parent(const QModelIndex&) const;

	///设置是否转置
	void setIsTranspose(bool b){_isTranspose = b;}

	///是否处于转制状态
	bool isTranspose(){return _isTranspose;}

	//设置是否排序
	void setEnableMySort(bool b){_enableMySort = b;}

	///是否处于排序状态
	bool isEnableMySort(){return _enableMySort;}

public slots:
	///更新排序方式 
	void updateComponent(int component);

protected:	
	///重写实现排序的规则
	virtual bool lessThan(const QModelIndex & left, const QModelIndex & right ) const;

private:
	///是否可排序 
	bool _enableMySort;

	///存储由哪种方式进行排序
	int _component;

	///是否转制
	bool _isTranspose;
};

#endif // PROXYDATAMODEL_H
