#pragma once

#include "base\view.h"
#include <QWidget>
#include <QAction>
#include <QList>

/*!
	@brief   继承view 实现视图为多项表格视图
	@date    2015.7.2
	@author  Jerry
*/
class VInteractiveTableView :
	public Base::View
{
	Q_OBJECT

public:
	VInteractiveTableView(QObject* parent=0);
	~VInteractiveTableView(void);

	///获得类类型名称
	static QString getClassTypeName();

	///获得视图类型
	virtual QString getViewType()const;

	///获得widget 
	virtual QWidget* getWidget();
	
	///获得真正的widget
	virtual QWidget* getActualWidget();

	///获得action列表
	virtual QList<QAction*>	getActionList();

	///保存状态
	virtual bool saveState(QDataStream& out);

	///加载状态
	virtual bool loadState(QDataStream& in,qint64 dataSize);

private:
	///初始action列表
	void initActionList();

private:
	///用于存储main分隔条
	QWidget*			_widget;

	///用于存储真正的表格widget
	QWidget*			_actualWidget;

	///action列表
	QList<QAction*>		_actionList;

};

