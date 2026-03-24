#ifndef PREVTT_H
#define PREVTT_H

#include <QObject>
#include <QtPlugin>

#include "include/IExchangeView.h"

/*!
	@brief   实现view接口
	@date    2015.7.1
	@author  Jerry
*/
class prevtt : public QObject, public IExchangeView
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

#endif // PREVTT_H
