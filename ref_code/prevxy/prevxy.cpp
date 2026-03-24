#include "prevxy.h"

#include "base/ViewFactory.h"
#include "base/licenses.h"

#include "itemxyview.h"

using namespace Qtitan;

Q_EXPORT_PLUGIN2(IExchangeView, PrevXY);

static QString itemViewName("XY Plot View");

class MyViewProducer:public Base::AbstractProducer
{
public:
	virtual void* Produce(void){
		return new ItemXYView();
	}
};


QString PrevXY::getKeyname()
{
	return itemViewName;
}

void PrevXY::registerView()
{
	if(Base::L::co("insviewer-prevtc","2.0"))
	{
		static MyViewProducer producer;
		Base::ViewFactory::instance()->AddProducer(itemViewName,&producer);
	}
}

Qtitan::RibbonPage* PrevXY::createRibbonPage( Qtitan::RibbonBar* ribbonBar )
{
	return NULL;
}

