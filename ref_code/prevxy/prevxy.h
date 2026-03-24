#ifndef PREVXY_H
#define PREVXY_H

#include <QObject>
#include <QtPlugin>

#include "prevxy_global.h"
#include "include/IExchangeView.h"

/*!
	@brief  实现view接口
	@date   2015.7.3
	@author Jerry
*/
class  PrevXY :public QObject, public IExchangeView
{
	Q_OBJECT
		Q_INTERFACES(IExchangeView)
public:
	///获得关键名
	virtual QString getKeyname();

	///注册视图
	virtual void registerView();

	///创建绑带页
	virtual Qtitan::RibbonPage* createRibbonPage(Qtitan::RibbonBar* ribbonBar);

private:

};

#endif // PREVXY_H
