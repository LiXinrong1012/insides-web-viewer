#include "view.h"

#include "activeviewobject.h"

namespace Base{


View::View(QObject* parent)
	:QObject(parent)
{

}

View::~View()
{
	if(ActiveViewObject::instance()->activeView()==this)
		ActiveViewObject::instance()->setActiveView(NULL);
}

QList<QAction*> View::getActionList()
{
	return QList<QAction*>();
}

Qtitan::RibbonPage* View::getRibbonPage()
{
	return NULL;
}

void View::updateRibbonPage()
{

}


}	//end namespace Base