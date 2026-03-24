#include "prevtt.h"

#include "base/ViewFactory.h"
#include "base/licenses.h"

#include "interactivetableview.h"


Q_EXPORT_PLUGIN2(IExchangeView, prevtt);


class MyViewProducer:public Base::AbstractProducer
{
public:
	virtual void* Produce(void){
		return new InteractiveTableView();
	}
};

QString prevtt::getKeyname()
{
	return "Interactive Table";
}

void prevtt::registerView()
{
	if(Base::L::co("insviewer-prevtt","2.0"))
	{
		static QString itemCurveViewName("Interactive Table");
		static MyViewProducer producer;
		Base::ViewFactory::instance()->AddProducer(itemCurveViewName,&producer);
	}
}

Qtitan::RibbonPage* prevtt::createRibbonPage( Qtitan::RibbonBar* ribbonBar )
{
	return NULL;
}
