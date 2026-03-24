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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/LodPage.h,v 1.13 2007-03-19 17:21:51 guido Exp $
//

#if !defined(AFX_LODPAGE_H__28514FF1_36CA_11D4_8204_0050042DF1E4__INCLUDED_)
#define AFX_LODPAGE_H__28514FF1_36CA_11D4_8204_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
// LodPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLodPage dialog
class HSolidView;
class HConstantFrameRate;
class CLodPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CLodPage)

// Construction
public:
	CLodPage(HSolidView *view = 0);
	~CLodPage();
	HSolidView *m_pHView;
	HConstantFrameRate *m_pCFR;
  	// Dialog Data
	//{{AFX_DATA(CLodPage)
	enum { IDD = IDD_DETAILDIALOG };
	int		m_clampvalue;
	CString	m_maxclamp;
	BOOL	m_HighQualityLod;
	//}}AFX_DATA
	void  ApplyData(bool SetClamp = true);
 	bool m_init;
 	virtual void OnOK();
 	virtual void OnCancel();
	bool m_bShowDelayDialog;
	int m_levels;
	float m_falloff;
	int m_clamp;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLodPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
 
// Implementation
protected:
 
 	// Generated message map functions
	//{{AFX_MSG(CLodPage)
 	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDoclamp();
	afx_msg void OnHighQualityLods();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LODPAGE_H__28514FF1_36CA_11D4_8204_0050042DF1E4__INCLUDED_)
