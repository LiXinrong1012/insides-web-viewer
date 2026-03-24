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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpCameraPan.cpp,v 1.16 2007-06-04 18:33:12 reuben Exp $
//

// HOpCameraPan.cpp : implementation of the HOpCameraPan class
//

//#if STDAFX
#include "stdafx.h"
//#endif

#include "HSInclude.h"
#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HSOpCameraPan.h"

#include "HSolidView.h"

#include "HTools.h"
#include <string.h>
#include <math.h>
#include "hc.h"


/////////////////////////////////////////////////////////////////////////////
// HSOpCameraPan
//
// Operator for panning the scene's camera based on the user dragging the mouse
// with the left button down
//
// Left button down - find first position and bounds object with box
//
// Mouse motion while down - pans camera based on difference between previous and 
// current world space point
//



HSOpCameraPan::HSOpCameraPan(HBaseView* view, int DoRepeat,int DoCapture) : HOpCameraPan(view, DoRepeat, DoCapture)
{
	m_bIsPrevRendermode = false;
}
 

int HSOpCameraPan::OnLButtonDownAndMove(HEventInfo &event)
{

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

	return HOpCameraPan::OnLButtonDownAndMove(event);
}
 


 
int HSOpCameraPan::OnLButtonUp(HEventInfo &event)
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

    return(HOP_READY);
}
