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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSQueryAdvanced.h,v 1.6 2007-12-06 01:46:58 chad Exp $
//

// HSQueryAdvanced.h : interface of the HSQueryAdvanced class, derived from HBaseOperator
// dynamically querys model using left button down and drag 

#ifndef _HSQueryAdvanced_H
#define _HSQueryAdvanced_H

#include "HBaseOperator.h" 

#if IS_QT
class MyHQSolidWidget;
#else
class CSolidHoopsView;
#endif


class HSQueryAdvanced : public HBaseOperator
{
private:

#if IS_QT
	MyHQSolidWidget * DialogMaker;
#else
	CSolidHoopsView* m_SolidHoopsView;
#endif

	void normalize_vector(double* vector);

public:

    HSQueryAdvanced(HBaseView* view, int DoRepeat=0, int DoCapture=1);
	~HSQueryAdvanced( void );
    const char * GetName();

    int OnLButtonDown(HEventInfo &event);
    int OnLButtonUp(HEventInfo &event);
	int OnLButtonDownAndMove(HEventInfo &event);

#ifdef IS_QT
	void SetDialogMaker(MyHQSolidWidget* app);
#else
	void SetSolidHoopsView(CSolidHoopsView* view);
#endif

	bool DoQuery();
	bool DoQueryHoops();

	void highlight_face(HC_KEY key, int o1, int o2, int o3);


};
#endif



