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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpMeasureDistance.h,v 1.9 2006-08-07 20:38:55 stage Exp $
//

// HSOpMeasureDistance.h : interface of the HPQuery class, derived from HBaseOperator
// dynamically querys model using left button down and drag 

#ifndef _HSOpMeasureDistance_H
#define _HSOpMeasureDistance_H

#include "HBaseOperator.h" 

#if IS_QT
class MyHQSolidWidget;
#else
class CSolidHoopsView;
#endif


class HSOpMeasureDistance : public HBaseOperator
{
private:

#if IS_QT
	MyHQSolidWidget * DialogMaker;
#else
	CSolidHoopsView* m_SolidHoopsView;
#endif

	void normalize_vector(double* vector);

public:

    HSOpMeasureDistance(HBaseView* view, int DoRepeat=0, int DoCapture=1);
	~HSOpMeasureDistance( void );
    const char * GetName();

    int OnLButtonDown(HEventInfo &event);
    int OnLButtonUp(HEventInfo &event);
	int OnLButtonDownAndMove(HEventInfo &event);

#ifdef IS_QT
	void SetDialogMaker(MyHQSolidWidget* app);
#else
	void SetSolidHoopsView(CSolidHoopsView* view);
#endif

	bool DoQuery(bool first=false);
	bool DoQueryPlain(bool first = false);

	HC_KEY	m_lPolyline;		// key for HOOPS polyline
	HPoint	m_ptLast;
	HPoint*	m_pPolyline;		// pointer to array of points for HOOPS Polyline in World Space
	int		m_iPolylineCount;	// number of points in the Polyline
	double	first_pick[3];
	HPoint	first_pick2;

};
#endif



