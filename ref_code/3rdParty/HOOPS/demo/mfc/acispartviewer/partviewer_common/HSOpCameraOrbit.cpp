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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpCameraOrbit.cpp,v 1.21 2007-10-16 18:59:57 stage Exp $
//

// HOpCameraOrbit.cpp : implementation of the HOpCameraOrbit class
//

//#if STDAFX 
#include "stdafx.h"
//#endif

#include <assert.h>

#include "HSInclude.h"

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HSOpCameraOrbit.h"
#include "HSolidView.h"
#include "HEventListener.h"
#include "HEventManager.h"

#include "HTools.h"
#include "HUtility.h"
#include "hc.h"

#include "csolidhoopsapp.h"

#include <math.h>
#include <string.h>

extern CSolidHoopsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// HSOpCameraOrbit
//
// Operator for orbiting the scene's camera based on the user dragging the mouse
// with the left button down
//
// Left button down - find first position and bounds object with box
//
// Mouse motion while down - orbits camera based on mouse movement by mapping 
// the drag vector onto a virtual sphere and determine the corresponding orbit
// parameters
//
// Mouse up - removes object bounding box



HSOpCameraOrbit::HSOpCameraOrbit(HBaseView* view, int DoRepeat,int DoCapture) : HOpCameraOrbit(view, DoRepeat, DoCapture)
{
	m_bSingleClick = false;
	m_bIsPrevRendermode = false;
}

int HSOpCameraOrbit::OnLButtonDown(HEventInfo &event)
{
	m_bSingleClick = true;

	return HOpCameraOrbit::OnLButtonDown(event);
}

int HSOpCameraOrbit::OnLButtonDownAndMove(HEventInfo &event)
{
	m_bSingleClick = false;

#if defined(ACIS) || defined(GRANITE) || defined (HOOPS_ONLY)
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

	HOpCameraOrbit::OnLButtonDownAndMove(event);
	return (HOP_OK);
}
 
int HSOpCameraOrbit::OnLButtonUp(HEventInfo &event)
{
	if(!OperatorStarted()) 
		return HBaseOperator::OnLButtonDownAndMove(event);


#if defined(ACIS) || defined(GRANITE) || defined(HOOPS_ONLY)
	if( m_bIsPrevRendermode )
	{
		m_bIsPrevRendermode = false;
		GetView()->SetRenderMode(m_hPrevRendermode);
	}
#endif

	GetView()->CameraPositionChanged( true, true );

  	GetView()->Update();
    SetOperatorStarted(false); 
	return (HOP_OK);

}

