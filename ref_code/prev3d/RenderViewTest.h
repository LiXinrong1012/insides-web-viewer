#pragma once

#include "prev3d/prev3d_global.h"
#include "base/view.h"


class PREV3D_EXPORT RenderViewTest :
	public Base::View
{
public:
	RenderViewTest(void);
	~RenderViewTest(void);

	static QString getClassTypeName();

	virtual QString getViewType()const;
	virtual QWidget* getWidget();
	virtual QWidget* getActualWidget();

	//virtual QList<QAction*>	getActionList();


private:
	QWidget* _widget;
	QWidget* _actualWidget;
	QList<QAction* > _actionList;

};