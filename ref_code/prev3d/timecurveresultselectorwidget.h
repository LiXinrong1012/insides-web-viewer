#ifndef TIMECURVERESULTSELECTORWIDGET_H
#define TIMECURVERESULTSELECTORWIDGET_H

#include "prev3d/ResultSelectorWidget.h"

/*!
*	This widget is used to select item data that will be 
*	inserted into curve plot or anything else.
*	@author	Jerry He
*	@date	2014.5.9
*/
class PREV3D_EXPORT TimeCurveResultSelectorWidget : public ResultSelectorWidget
{
	Q_OBJECT

public:
	TimeCurveResultSelectorWidget(QWidget *parent);
	~TimeCurveResultSelectorWidget();

signals:
	void itemAdding(QVector<double>& xlist,QVector<double>& ylist, const QString& title);

protected slots:
	void onSubItemChanged();
	void onSubsubItemChanged();

protected:
	virtual void protected_onOK();

private:
	
};

#endif // TIMECURVERESULTSELECTORWIDGET_H
