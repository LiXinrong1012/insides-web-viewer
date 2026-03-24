#ifndef COUTOURDISPLAYSELECTORWIDGET_H
#define COUTOURDISPLAYSELECTORWIDGET_H

#include "prev3d/TimeCurveResultSelectorWidget.h"

class PREV3D_EXPORT ContourDisplaySelectorWidget : public TimeCurveResultSelectorWidget
{
	Q_OBJECT

public:
	ContourDisplaySelectorWidget(QWidget *parent);
	~ContourDisplaySelectorWidget();

signals:
	void contourItemAdding(IResultItem* resultItem,int secIndex,int subSecIndex,int subsubSecIndex,
		bool onlyUseCurrent);

protected:
	virtual void protected_onOK();

private:
	
};

#endif // COUTOURDISPLAYSELECTORWIDGET_H
