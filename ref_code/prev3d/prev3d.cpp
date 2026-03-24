#include "prev3d.h"

#include "base/ViewFactory.h"
#include "RenderView.h"
#include "base/licenses.h"



using namespace Qtitan;

Q_EXPORT_PLUGIN2(IExchangeView, prev3d);


class MyViewProducer:public Base::AbstractProducer
{
public:
	virtual void* Produce(void){
		return new RenderView();
	}
};



QString prev3d::getKeyname()
{
	return "Render View2";
}

void prev3d::registerView()
{
	if(Base::L::co("insviewer-prev3d","2.0"))
	{
		static QString itemViewName("Render View");
		static MyViewProducer producer;
		Base::ViewFactory::instance()->AddProducer(itemViewName,&producer);
	}
}

Qtitan::RibbonPage* prev3d::createRibbonPage( Qtitan::RibbonBar* ribbonBar )
{
	if(Base::L::co("insviewer-prev3d","2.0"))
	{
		return RenderView::getPre3DRibbonPage()->initPage(ribbonBar);
		
	}

	return NULL;
}

