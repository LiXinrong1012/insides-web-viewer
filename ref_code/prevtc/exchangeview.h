#ifndef EXCHANGEVIEW_H
#define EXCHANGEVIEW_H

#include <QObject>
#include <QtPlugin>

#include "include/IExchangeView.h"

/*!
	@brief   原作转变视图，现已废弃
	@date    2015.6.29
	@author  Jianjun
*/
class ExchangeView : public QObject, public IExchangeView
{
	Q_OBJECT
	Q_INTERFACES(IExchangeView)

public:
	virtual QString getKeyname();
	virtual void registerView();
	virtual Qtitan::RibbonPage* createRibbonPage(Qtitan::RibbonBar* ribbonBar);

private:
	
};

#endif // EXCHANGEVIEW_H
