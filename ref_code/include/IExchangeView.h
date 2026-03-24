#pragma once

#include <QString>
#include <QList>

namespace Qtitan{
	class RibbonBar;
	class RibbonPage;
}

class IExchangeView
{
public:

	virtual ~IExchangeView(void) { }

	virtual QString getKeyname()=0;
	virtual void registerView()=0;
	virtual Qtitan::RibbonPage* createRibbonPage(Qtitan::RibbonBar* ribbonBar)=0;
};

Q_DECLARE_INTERFACE(IExchangeView,
	"com.jerryhe.tdypre.iexchangeview/1.0");
