// Visualize.h : interface of the CVisualizeApp class, derived from CHoopsApp
// This is the main header for the application

#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef _CVisualizeApp_H__
#define _CVisualizeApp_H__

#include "hc.h"
#include "CHoopsApp.h"


class HDB;


/////////////////////////////////////////////////////////////////////////////
// CVisualizeApp:
// See CVisualizeApp.cpp for the implementation of this class
//

class CVisualizeApp : public CHoopsApp
{

protected:



public:
	CVisualizeApp();


  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizeApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVisualizeApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// _CVisualizeApp_H__
