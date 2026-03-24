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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/LodSlider.h,v 1.6 2006-08-07 20:38:55 stage Exp $
//

#if !defined(AFX_LODSLIDER_H__B45B181B_242E_11D3_BA3D_0050046769C0__INCLUDED_)
#define AFX_LODSLIDER_H__B45B181B_242E_11D3_BA3D_0050046769C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LodSlider.h : header file
//

//#include "LodDialog.h"

class CLodDialog;

/////////////////////////////////////////////////////////////////////////////
// LodSlider window

class LodSlider : public CSliderCtrl
{
// Construction
public:
//	LodSlider();

	LodSlider(CLodDialog * lod_dialog);

// Attributes
public:

	CLodDialog * ld;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LodSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~LodSlider();

	// Generated message map functions
protected:
	//{{AFX_MSG(LodSlider)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LODSLIDER_H__B45B181B_242E_11D3_BA3D_0050046769C0__INCLUDED_)
