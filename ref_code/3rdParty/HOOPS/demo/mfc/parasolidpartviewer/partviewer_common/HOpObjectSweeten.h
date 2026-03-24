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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HOpObjectSweeten.h,v 1.8 2006-08-07 20:38:55 stage Exp $
//

// HOpObjectSweeten.h : interface of the HOpObjectSweeten class, derived from HOpSelect
// Handles area selection

#ifndef _HOPOBJECTSWEETEN_H
#define _HOPOBJECTSWEETEN_H

#include "HTools.h"
#include "HOpConstructRectangle.h" 

class HOpObjectSweeten : public HOpConstructRectangle
{
public:
    HOpObjectSweeten(HBaseView* view, int DoRepeat=0, int DoCapture=1);
	~HOpObjectSweeten();
	const char * GetName();

    virtual int OnLButtonUp(HEventInfo &event);  
	
	HBaseOperator * Clone();
};

#endif
