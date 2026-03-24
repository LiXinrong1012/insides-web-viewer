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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/QueryDialog.h,v 1.6 2006-08-07 20:38:55 stage Exp $
//

// QueryDialog.h : interface of the CQueryDialog class, derived from CDialog
// Manages creation and updating of the Model QueryDialog

#if !defined(AFX_QUERYDIALOG_H__BE106C43_3076_11D2_A557_00A0C989307C__INCLUDED_)
#define AFX_QUERYDIALOG_H__BE106C43_3076_11D2_A557_00A0C989307C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "resource.h"
// QueryDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog

class CQueryDialog : public CDialog
{
// Construction
public:
	CQueryDialog(CWnd* pParent = 0);   // standard constructor
	void SetText(char* querytext);
// Dialog Data
	//{{AFX_DATA(CQueryDialog)
	enum { IDD = IDD_QUERYDIALOG };
	CString	m_QueryTextValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryDialog)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYDIALOG_H__BE106C43_3076_11D2_A557_00A0C989307C__INCLUDED_)
