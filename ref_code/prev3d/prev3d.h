#ifndef PREV3D_H
#define PREV3D_H

#include <QObject>
#include <QtPlugin>

#include "include/IExchangeView.h"

class prev3d : public QObject, public IExchangeView
{
	Q_OBJECT
		Q_INTERFACES(IExchangeView)

public:
	virtual QString getKeyname();
	virtual void registerView();
	virtual Qtitan::RibbonPage* createRibbonPage(Qtitan::RibbonBar* ribbonBar);

private:

};

#endif // PREV3D_H
