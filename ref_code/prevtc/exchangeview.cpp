#include "exchangeview.h"

#include "base/ViewFactory.h"
#include "itemcurveview.h"

#include "base/licenses.h"

Q_EXPORT_PLUGIN2(iexchangeview, ExchangeView);



QString ExchangeView::getKeyname()
{
	return "Time Curve";
}

class MyCurveViewProducer:public Base::AbstractProducer
{
public:
	virtual void* Produce(void){
		return new ItemCurveView();
	}
};

void ExchangeView::registerView()
{
	if(Base::L::co("insviewer-prevtc","2.0")){
		static QString itemCurveViewName("Time Curve View");
		static MyCurveViewProducer producer;
		Base::ViewFactory::instance()->AddProducer(itemCurveViewName,&producer);
	}
}

Qtitan::RibbonPage* ExchangeView::createRibbonPage( Qtitan::RibbonBar* ribbonBar )
{
	return NULL;
}
