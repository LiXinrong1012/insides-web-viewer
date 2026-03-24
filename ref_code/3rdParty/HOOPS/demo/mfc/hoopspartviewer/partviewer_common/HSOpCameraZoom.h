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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpCameraZoom.h,v 1.9 2006-08-07 20:38:55 stage Exp $
//

// HPanCamera.h : interface of the HPanCamera class
// zooms the camera of current view in realtime

#ifndef _HSOPCAMERAZOOM_H
#define _HSOPCAMERAZOOM_H

#include "HOpCameraZoom.h"

class HSOpCameraZoom : public HOpCameraZoom
{
private:
	bool m_bIsPrevRendermode;
	HRenderMode m_hPrevRendermode;

public:

    HSOpCameraZoom (HBaseView* view, int DoRepeat=0, int DoCapture=1);
 
	int OnLButtonDownAndMove(HEventInfo &event);
	int OnLButtonUp (HEventInfo &event);
 
};

#endif
