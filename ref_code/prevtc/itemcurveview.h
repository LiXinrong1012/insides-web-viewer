#ifndef ITEMCURVEVIEW_H
#define ITEMCURVEVIEW_H

#include "Base/view.h"

/*!
	@brief   曲线视图框架
	@date    2015.6.29
	@author  Jianjun
*/
class ItemCurveView : public Base::View
{
	Q_OBJECT

public:
	ItemCurveView();
	~ItemCurveView();

	static QString getClassTypeName();

	virtual QString getViewType()const;
	virtual QWidget* getWidget();

	virtual QList<QAction*>	getActionList();

	virtual bool saveState(QDataStream& out);
	virtual bool loadState(QDataStream& in, qint64 dataSize);
	

private:
	QWidget* _widget;
	QWidget* _actualWidget;
	QList<QAction* > _actionList;

	///初始化action
	void initActionList();
};

#endif // ITEMCURVEVIEW_H
