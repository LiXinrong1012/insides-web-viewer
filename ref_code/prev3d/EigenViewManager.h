#pragma once

#include "prev3d/BaseResultViewManager.h"
#include "precore/ResultDocument.h"

class PREV3D_EXPORT EigenViewManager :
	public BaseResultViewManager, public IResultListener
{
public:
	EigenViewManager(PreHQWidget* w);
	virtual ~EigenViewManager(void);

	virtual void reset();	//重置并刷新显示。
	virtual void redraw();

protected:
	/// invoked after result data has changed.
	virtual void onResultCurrentFrameChanged();

	void drawEigen();


		
};

