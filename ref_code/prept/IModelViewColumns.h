#pragma once

#include <QList>

class TreeItemProperty;
class ITreeItemPropertyFunc;
class QTreeView;
class QTableView;
class QAbstractItemView;
class QAbstractItemModel;




/*!
*	针对ComTreeModel和ModelSearchTableModel一些共有的方法
*	进行封装。
*	@author	Jerry He
*	@date	2014.7.16
*/
class IModelColumns
{
public:
	IModelColumns(void);

	TreeItemProperty* getColumnDataType( int columnIndex );

protected:
	QList<TreeItemProperty*>		_currTreeItemPropertyList;
	QList<ITreeItemPropertyFunc*>	_currentPropertiesParents;
	QList<int>						_currentPropertiesIndex;

	void updateColumns();
};



/*!
*	针对ComTreeView和ModelSearchTableView共有的方法进行封装。
*	@author	Jerry He
*	@date	2014.7.16
*/
class IViewColumns
{
public:
	IViewColumns();

protected:
	void updateHeaderWidth(QTreeView* view,QAbstractItemModel* model,IModelColumns* colModel);
	void updateHeaderWidth(QTableView* view,QAbstractItemModel* model,IModelColumns* colModel);
	void updateHeaderDelegate(QAbstractItemView* view,QAbstractItemModel* model,IModelColumns* colModel);
};
