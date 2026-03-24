#include "activeviewobject.h"
#include "Console.h"
#include "view.h"

#include <QApplication>

namespace Base{

ActiveViewObject::ActiveViewObject(QObject *parent)
	: QObject(parent)
	,_activeView(NULL)
	,_layoutManager(NULL)
	,_modelStatus(MODEL_STATUS_MODEL)
{
	qApp->installEventFilter(this);
}

ActiveViewObject::~ActiveViewObject()
{
}

ActiveViewObject* ActiveViewObject::instance()
{
	static ActiveViewObject _instance;
	return &_instance;

}

void ActiveViewObject::setActiveView( View* view )
{
	if(view==_activeView)
		return;

	_activeView=view;

	emit activeViewChanged(_activeView);

#ifdef _DEBUG
	//Base::Console().Message("Active view changed.");
#endif
}



void ActiveViewObject::setSelect( long key,int count,const int* faces,const int* vertex1,const int* vertex2 )
{
	emit sigSetSelect(key,count,faces,vertex1,vertex2);
}

void ActiveViewObject::setModelStatus( int modelStatus )
{
	if(_modelStatus==modelStatus)
		return;
	_modelStatus=modelStatus;
	notifyModelStatusChanged();
}

bool ActiveViewObject::eventFilter( QObject * watched, QEvent * event )
{
	if(_activeView){
		//Base::Console().Log("active here");
		_activeView->onEventFilter(watched,event);
	}

	return QObject::eventFilter(watched,event);
}


}