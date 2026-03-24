#pragma once

#include "prev3d/prev3d_global.h"
#include "hbaseoperator.h"
#include "HOpObjectTranslate.h"

class HOpCameraPan;
class HOpCameraOrbit;
class HOpSelectAperture;
class HOpCameraZoom;
class PreHQWidget;
class HBaseView;

/*!
*	代表一个自定义的视图鼠标控制操作，
*	其中：
		-左键用来旋转和拾取；
		-中键用来缩放和平衡；
		-右键不关联操作；
*	@author Jerry He
*	@date	2014.5.23
*/
class PREV3D_EXPORT OmniControlOperator :
	public HBaseOperator
{
public:
	OmniControlOperator(HBaseView* view, int DoRepeat=0, int DoCapture=1);
	virtual ~OmniControlOperator(void);

	virtual HBaseOperator * Clone();              
	virtual int OnLButtonDown (HEventInfo &event);
	virtual int OnLButtonDownAndMove(HEventInfo &event);
	virtual int OnLButtonUp (HEventInfo &event);

	virtual int OnMButtonDown(HEventInfo &hevent);
	virtual int OnMButtonDownAndMove(HEventInfo &hevent);
	virtual int OnMButtonUp(HEventInfo &hevent);


private:
	HOpCameraPan*	_OpCameraPan;
	HOpCameraOrbit* _OpCameraOrbit;
	HOpCameraZoom*	_OpCameraZoom;
	HOpSelectAperture*	_OpSelectAperture;
};

class PREV3D_EXPORT TimeTranslateOperator : public HOpObjectTranslate
{
public:
	TimeTranslateOperator(HBaseView* view, PreHQWidget* w,int DoRepeat=0, int DoCapture=1);
	~TimeTranslateOperator(){};

	int OnLButtonDownAndMove(HEventInfo &event);
	int OnLButtonUp(HEventInfo &hevent);

private:
	HBaseView* _view;
	PreHQWidget* _widget;
	float selectX,selectY;
	float downX,downY;

};