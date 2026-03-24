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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/LodDialog.h,v 1.6 2006-08-07 20:38:55 stage Exp $
//

#if !defined(AFX_LODDIALOG_H__B45B1813_242E_11D3_BA3D_0050046769C0__INCLUDED_)
#define AFX_LODDIALOG_H__B45B1813_242E_11D3_BA3D_0050046769C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LodDialog.h : header file
//
#include "resource.h"
#include "LodSlider.h"
#include "HBaseView.h"

/////////////////////////////////////////////////////////////////////////////
// CLodDialog dialog

class CLodDialog : public CDialog
{
// Construction
public:
	CLodDialog(CWnd* pParent = NULL, HBaseView * view = NULL);   // standard constructor

	virtual ~CLodDialog();


// Dialog Data
	//{{AFX_DATA(CLodDialog)
	enum { IDD = IDD_LOD };
	LodSlider*	m_threshold;
	int		m_threshold_display;
	//}}AFX_DATA

	HBaseView *	m_pHView;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLodDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLodDialog)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LODDIALOG_H__B45B1813_242E_11D3_BA3D_0050046769C0__INCLUDED_)
