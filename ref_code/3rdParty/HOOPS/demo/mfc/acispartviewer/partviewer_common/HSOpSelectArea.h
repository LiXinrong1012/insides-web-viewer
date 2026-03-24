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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpSelectArea.h,v 1.7 2006-08-07 20:38:55 stage Exp $
//

// HOpSelectAperture.h : interface of the HOpSelectAperture class, derived from HOpSelect
// Handles aperture selection

#ifndef _HSOPSELECTAREA_H
#define _HSOPSELECTAREA_H

#include "HOpSelectArea.h"

class HSOpSelectArea : public HOpSelectArea
{

public:

    HSOpSelectArea(HBaseView* view, int DoRepeat = 0, int DoCapture = 1);
 
    virtual int OnLButtonUp(HEventInfo &event);
 
};

#endif
