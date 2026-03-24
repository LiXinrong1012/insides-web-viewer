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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/FramerateDialog.h,v 1.9 2007-03-19 17:21:01 guido Exp $
//

#if !defined(AFX_FRAMERATEDIALOG_H__C826A563_B85D_11D3_8176_0050042DF1E4__INCLUDED_)
#define AFX_FRAMERATEDIALOG_H__C826A563_B85D_11D3_8176_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameRateDialog.h : header file
//
#include "HSolidView.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CFrameRateDialog dialog
class HConstantFrameRate;
class CFrameRateDialog : public CDialog
{
// Construction
public:
	CFrameRateDialog(CWnd* pParent = NULL,HConstantFrameRate *	cframerate=0);   // standard constructor
	int m_levels;
	float m_falloff;
// Dialog Data
	//{{AFX_DATA(CFrameRateDialog)
	enum { IDD = IDD_FRAMERATEDIALOG };
	BOOL	m_bconstantframerate;
	BOOL	m_buselod;
	UINT	m_min_framerate;
	BOOL	m_bthreshold;
	int		m_increase;
	BOOL	m_bboundingboxes;
	float	m_ScreenExtent;
	float	m_DistanceWeight;
	float	m_DivergenceWeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameRateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HConstantFrameRate *m_pCFR;
	void EnableItems();
	// Generated message map functions
	//{{AFX_MSG(CFrameRateDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckConstantframerate();
	afx_msg void OnCheckUselod();
	afx_msg void OnRadioAllowIncreasealways();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMERATEDIALOG_H__C826A563_B85D_11D3_8176_0050042DF1E4__INCLUDED_)
