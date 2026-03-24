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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/BusyDlg.h,v 1.6 2006-08-07 20:38:55 stage Exp $
//

#if !defined(AFX_BUSYDLG_H__12A2E957_CE50_11D3_8192_0050042DF1E4__INCLUDED_)
#define AFX_BUSYDLG_H__12A2E957_CE50_11D3_8192_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BusyDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CBusyDlg dialog

class CBusyDlg : public CDialog
{
// Construction
public:
	CBusyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBusyDlg)
	enum { IDD = IDD_BUSYDLG };
 	//}}AFX_DATA

 // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBusyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBusyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUSYDLG_H__12A2E957_CE50_11D3_8192_0050042DF1E4__INCLUDED_)
