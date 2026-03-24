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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpCameraOrbit.h,v 1.9 2006-08-07 20:38:55 stage Exp $
//

// HOpCameraOrbit.h : interface of the HOpCameraOrbit class
// orbits the camera of current view usual a virtual trackball
// interface

#ifndef _HSOPCAMERAORBIT_H
#define _HSOPCAMERAORBIT_H

#include "HOpCameraOrbit.h"


class HSOpCameraOrbit : public HOpCameraOrbit
{

private:
	bool m_bIsPrevRendermode;
	HRenderMode m_hPrevRendermode;

public:
	bool	m_bSingleClick;
	HSOpCameraOrbit (HBaseView* view, int DoRepeat=0, int DoCapture=1);
 	int OnLButtonUp (HEventInfo &event);
	int OnLButtonDownAndMove(HEventInfo &event);
	int OnLButtonDown(HEventInfo &event);
};
#endif
