#ifndef PREVOSG_H
#define PREVOSG_H

#include <QObject>
#include <QtPlugin>

#include "include/IExchangeView.h"

class  prevosg : public QObject, public IExchangeView
{
	Q_OBJECT
		Q_INTERFACES(IExchangeView)

public:
	virtual QString getKeyname();
	virtual void registerView();
	virtual Qtitan::RibbonPage* createRibbonPage(Qtitan::RibbonBar* ribbonBar);
private:

};

#endif // PREVOSG_H
