#include "prevtt.h"

#include "base/ViewFactory.h"
#include "base/licenses.h"

#include "VInteractiveTableView.h"

Q_EXPORT_PLUGIN2(IExchangeView, prevtt);


class MyViewProducer:public Base::AbstractProducer
{
public:
	virtual void* Produce(void){
		return new VInteractiveTableView();
	}
};

QString prevtt::getKeyname()
{
	return "Multiple Interactive Table";
}

void prevtt::registerView()
{
	if(Base::L::co("insviewer-prevttm","2.0"))
	{
		static QString itemCurveViewName("Multiple Interactive Table");
		static MyViewProducer producer;
		Base::ViewFactory::instance()->AddProducer(itemCurveViewName,&producer);
	}
}

Qtitan::RibbonPage* prevtt::createRibbonPage( Qtitan::RibbonBar* ribbonBar )
{
	return NULL;
}
