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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HMyQuery.h,v 1.2 2006-08-07 20:38:58 stage Exp $
//


// HMyQuery.h : interface of the HMyQuery class, derived from HBaseOperator
// dynamically querys model using left button down and drag 

#ifndef _HMYQUERY_H
#define _HMYQUERY_H

#include "HBaseOperator.h"

class MyHQWidget;


class HMyQuery : public HBaseOperator
{
private:
	MyHQWidget * DialogMaker;

public:

    HMyQuery(HBaseView* view, int DoRepeat=0, int DoCapture=1);
	~HMyQuery( void );
    void GetName(char *name);

    int OnLButtonDown(HEventInfo &event);
    int OnLButtonUp(HEventInfo &event);
	int OnMouseMove(HEventInfo &event);
	void SetDialogMaker(MyHQWidget* app);
	bool DoQuery();

};

#endif


