#ifndef ITEMXYVIEW_H
#define ITEMXYVIEW_H

#include <QObject>
#include "base/view.h"

namespace Base{
	class View;
}

/*!
	@brief   实现view接口
	@date    2015.7.3
	@author  Jerry
*/
class ItemXYView : public Base::View
{
	Q_OBJECT

public:
	ItemXYView();
	~ItemXYView();

	///获得类类型名字
	static QString getClassTypeName();

	///获得视图类型
	virtual QString getViewType()const;

	///获得widget
	virtual QWidget* getWidget();

	///获得所有action列表
	virtual QList<QAction*>	getActionList();

	///保存状态
	virtual bool saveState(QDataStream& out);

	///加载状态
	virtual bool loadState(QDataStream& in, qint64 dataSize);

private:
	///初始化action列表
	void initActionList();

private:
	///存储widget 
	QWidget* _widget;

	///存储真正的widget
	QWidget* _actualWidget;

	///存储所有的action
	QList<QAction* > _actionList;

};

#endif // ITEMXYVIEW_H
