#include "OmniControlOperator.h"
#include "HOpCameraOrbit.h"
#include "HOpCameraPan.h"
#include "HOpSelectAperture.h"
#include "HOpCameraZoom.h"

#include "PreHQWidget.h"
#include "HSelectionSet.h"
#include "base/Console.h"

#include <QWeakPointer>


OmniControlOperator::OmniControlOperator( HBaseView* view, int DoRepeat/*=0*/, int DoCapture/*=1*/ )
	:HBaseOperator(view,DoRepeat,DoCapture)
{
	_OpCameraOrbit=new HOpCameraOrbit(view,DoRepeat,DoCapture);
	_OpCameraPan=new HOpCameraPan(view,DoRepeat,DoCapture);
	_OpSelectAperture=new HOpSelectAperture(view,DoRepeat,DoCapture);
	_OpCameraZoom=new HOpCameraZoom(view,DoRepeat,DoCapture);
}


OmniControlOperator::~OmniControlOperator(void)
{
	delete _OpCameraZoom;
	delete _OpCameraPan;
	delete _OpCameraOrbit;
	delete _OpSelectAperture;
}

HBaseOperator * OmniControlOperator::Clone()
{
	return new OmniControlOperator(m_pView,m_doRepeat,m_doCapture);
}

int OmniControlOperator::OnLButtonDown( HEventInfo &event )
{
	_OpSelectAperture->OnLButtonDown(event);
	return _OpCameraOrbit->OnLButtonDown(event);
}

int OmniControlOperator::OnLButtonDownAndMove( HEventInfo &event )
{
	return _OpCameraOrbit->OnLButtonDownAndMove(event);
}

int OmniControlOperator::OnLButtonUp( HEventInfo &event )
{
	return _OpCameraOrbit->OnLButtonUp(event);
}

int OmniControlOperator::OnMButtonDown( HEventInfo &hevent )
{
	return _OpCameraPan->OnLButtonDown(hevent);
}

int OmniControlOperator::OnMButtonDownAndMove( HEventInfo &hevent )
{
	return _OpCameraPan->OnLButtonDownAndMove(hevent);
}

int OmniControlOperator::OnMButtonUp( HEventInfo &hevent )
{
	return _OpCameraPan->OnLButtonUp(hevent);
}

//////////////////////////////

TimeTranslateOperator::TimeTranslateOperator( HBaseView* view,PreHQWidget* w, int DoRepeat/*=0*/, int DoCapture/*=1*/ )
	:HOpObjectTranslate(view,DoRepeat,DoCapture)
	,_view(view)
	,_widget(w)
{

}

int TimeTranslateOperator::OnLButtonDownAndMove( HEventInfo &event )
{
	if(!_view->GetSelection()->IsSelected(_widget->getTimeKey()))
		return 0;
	return HOpObjectTranslate::OnLButtonDownAndMove(event);
}

int TimeTranslateOperator::OnLButtonUp( HEventInfo &hevent )
{
	if(_view->GetSelection()->IsSelected(_widget->getTimeKey()))
		_widget->setTimePostion(hevent.GetMouseWindowPos().x*0.5,hevent.GetMouseWindowPos().y*0.5);
	
	return HOpObjectTranslate::OnLButtonUp(hevent);
}
