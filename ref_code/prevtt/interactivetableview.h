#pragma once

#include "base\view.h"
#include <QWidget>
#include <QAction>
#include <QList>

class InteractiveTableWidget;

/*!
	@brief   继承view 实现视图为表格视图
	@date    2015.7.1
	@author  Jerry
*/
class InteractiveTableView :
	public Base::View
{
	Q_OBJECT

public:
	InteractiveTableView(QObject* parent=0);
	~InteractiveTableView(void);

	///获得类类型名字
	static QString getClassTypeName();

	///获得视图类型
	virtual QString getViewType()const;

	///获得widget
	virtual QWidget* getWidget();

	///获得真正的widget
	virtual QWidget* getActualWidget();

	///获得actioon列表
	virtual QList<QAction*>	getActionList();

	///保存状态
	virtual bool saveState(QDataStream& out);

	///加载状态
	virtual bool loadState(QDataStream& in, qint64 dataSize);

protected slots:
	///显示或隐藏选择条
	void hideShowSelector();

private:
	///初始化所有action
	void initActionList();

private:
	///用于存储main 分隔条
	QWidget*			_widget;

	///存储真正的tableWidget
	QWidget*			_actualWidget;

	///存储所有action
	QList<QAction*>		_actionList;

	///存储真正的tableWidget
	InteractiveTableWidget* _tableWidget;

};

