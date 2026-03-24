#include "prevosg.h"

#include "base/ViewFactory.h"
#include "RenderView.h"
#include "base/licenses.h"



Q_EXPORT_PLUGIN2(IExchangeView, prevosg);

static QString itemViewName("OSG Reader View");

class OSGViewProducer:public Base::AbstractProducer
{
public:
	virtual void* Produce(void)
	{
		return new RenderView();
	}
};


QString prevosg::getKeyname()
{
	return itemViewName;
}


void prevosg::registerView()
{
	if(Base::L::co("insviewer-prevtc","2.0"))
	{
		static OSGViewProducer producer;
		Base::ViewFactory::instance()->AddProducer(itemViewName,&producer);
	}
}

Qtitan::RibbonPage* prevosg::createRibbonPage( Qtitan::RibbonBar* ribbonBar )
{
	return NULL;
}