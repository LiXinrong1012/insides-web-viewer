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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpCameraPan.h,v 1.9 2006-08-07 20:38:55 stage Exp $
//

// HOpCameraPan.h : interface of the HOpCameraPan class
// pans the camera of current view

#ifndef _HSOPCAMERAPAN_H
#define _HSOPCAMERAPAN_H


#include "HOpCameraPan.h"

class HSOpCameraPan : public HOpCameraPan
{
private:
	bool m_bIsPrevRendermode;
	HRenderMode m_hPrevRendermode;

public:

    HSOpCameraPan(HBaseView* view, int DoRepeat=0, int DoCapture=1);
 
	int OnLButtonDownAndMove(HEventInfo &event);
    int OnLButtonUp (HEventInfo &event);

 
};

#endif
