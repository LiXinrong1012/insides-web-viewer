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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/DetailPropertySheet.h,v 1.10 2006-08-07 20:38:55 stage Exp $
//

#if !defined(AFX_DETAILPROPERTYSHEET_H__28514FF2_36CA_11D4_8204_0050042DF1E4__INCLUDED_)
#define AFX_DETAILPROPERTYSHEET_H__28514FF2_36CA_11D4_8204_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DetailPropertySheet.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDetailPropertySheet

class HSolidView;
class CDetailPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDetailPropertySheet)

// Construction
public:
	CDetailPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDetailPropertySheet(LPCTSTR pszCaption, HSolidView *view = 0,CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	HSolidView *m_pHView;
	int m_levels;
	float m_falloff;
	int m_clamp;
	bool m_lod;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDetailPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDetailPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnApply();
	afx_msg void OnOK();
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILPROPERTYSHEET_H__28514FF2_36CA_11D4_8204_0050042DF1E4__INCLUDED_)



