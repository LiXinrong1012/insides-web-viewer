//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpCameraZoomBox.cpp,v 1.30 2007-06-01 23:37:59 reuben Exp $
//

// HOpCameraZoomBox.cpp : implementation of the HOpCameraZoomBox class
//

//#if STDAFX
#include "stdafx.h"
//#endif

#include "HSInclude.h"
#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HSOpCameraZoomBox.h"

#include "HSolidView.h"

#include "HTools.h"
#include "HUtility.h"
#include "HSUtility.h"

#include <math.h>
#include <string.h>
#include "HBhvBehaviorManager.h"

#include "hc.h"


/////////////////////////////////////////////////////////////////////////////
// HSOpCameraZoomBox
//
// Operator for modifying the scene's camera based on user defined screen-space
// window
//
// Left button down - find first position
//
// Mouse motion while button down - rubber band box is inserted in "?window space" 
// segment. This segment has a stretched camera from (-1, 1, -1, 1) i.e. the 
// segment's camera is set so that object space is equal to window space.
//
// Mouse up - set camera target, position and field to box defined by first point and 
// current mouse position.


HSOpCameraZoomBox::HSOpCameraZoomBox(HBaseView* view, int DoRepeat, int DoCapture) : HOpCameraZoomBox (view, DoRepeat, DoCapture)
{
	m_bIsPrevRendermode = false;
}

 

 
/////////////////////////////////////////////////////////////////////////////
// HOpCameraZoomBox message handlers





int HSOpCameraZoomBox::OnLButtonUp(HEventInfo &event)
{
	if (GetView()->GetModel()->GetBhvBehaviorManager()->IsPlaying() && 
		GetView()->GetModel()->GetBhvBehaviorManager()->GetCameraUpdated()) {
		HOpConstructRectangle::OnLButtonUp(event);
		return (HOP_OK);
	}

#if defined(ACIS) || defined(GRANITE) || defined(HOOPS_ONLY)
	if (GetView()->GetRenderMode() == HRenderHiddenLine)
	{
		m_bIsPrevRendermode = true;
		m_hPrevRendermode = HRenderHiddenLine;
		GetView()->SetRenderMode(HRenderHiddenLineFast);
	}
	if (GetView()->GetRenderMode() == HRenderBRepHiddenLine)
	{
		m_bIsPrevRendermode = true;
		m_hPrevRendermode = HRenderBRepHiddenLine;
		GetView()->SetRenderMode(HRenderBRepHiddenLineFast);
	}
#endif

	HOpCameraZoomBox::OnLButtonUp(event);

#if defined(ACIS) || defined(GRANITE) || defined(HOOPS_ONLY)
	if( m_bIsPrevRendermode )
	{
		m_bIsPrevRendermode = false;
		GetView()->SetRenderMode(m_hPrevRendermode);
		GetView()->Update();
	}
#endif	// (ACIS || GRANITE)

	return(HOP_READY);
}

// center current field about the selected point 
int HSOpCameraZoomBox::OnLButtonDblClk(HEventInfo &event)
{
	SetNewPoint(event.GetMouseWindowPos());

	HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
		HPoint new_point(GetNewPoint());
		HC_Compute_Coordinates (".", "outer window", &new_point, "world", &new_point);
		HC_Set_Camera_Target(new_point.x, new_point.y, new_point.z);
		SetNewPoint(new_point);
	}HC_Close_Segment();
	
	if (GetView()->GetRenderMode()==HRenderHiddenLine)		
		((HSolidView *)GetView())->UpdateHiddenLine(); 
	
	GetView()->Update(); // update the display

	return HBaseOperator::OnLButtonDblClk(event);
}
