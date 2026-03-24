// MainFrm.h : interface of the CMainFrame class, derived from CHoopsFrame
// Adds application specific frame creation  (to install the app toolbars, etc...)

#ifndef _CMainFrame__H_
#define _CMainFrame__H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MainFrm.h : header file
//

#include "CHoopsFrm.h"
#include "afxext.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame frame

class CMainFrame : public CHoopsFrame
{
protected:

// Attributes
public:

// Operations
public:
	CMainFrame();           // protected constructor used by dynamic creation

	DECLARE_DYNAMIC(CMainFrame)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMainFrame();

	// Generated message map functions
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif	// _CMainFrame__H_
