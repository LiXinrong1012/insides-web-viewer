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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/LodSlider.cpp,v 1.7 2006-08-07 20:38:55 stage Exp $
//

// LodSlider.cpp : implementation file
//

#include "stdafx.h"
#include "LodSlider.h"
#include "LodDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LodSlider

LodSlider::LodSlider(CLodDialog * lod_dialog)
{
	ld = lod_dialog;
}


LodSlider::~LodSlider()
{
}


BEGIN_MESSAGE_MAP(LodSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(LodSlider)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LodSlider message handlers


void LodSlider::OnMouseMove(UINT nFlags, CPoint point) 
{
	CSliderCtrl::OnMouseMove(nFlags, point);

	if (nFlags & MK_LBUTTON)
	{
		ld->m_threshold_display = GetPos();
		ld->UpdateData(FALSE);

		ld->m_pHView->SetLodThreshold(ld->m_threshold_display);
		ld->m_pHView->Update();
	}
}

void LodSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CSliderCtrl::OnLButtonDown(nFlags, point);

	ld->m_threshold_display = GetPos();
	ld->UpdateData(FALSE);

	ld->m_pHView->SetLodThreshold(ld->m_threshold_display);
	ld->m_pHView->Update();
}
