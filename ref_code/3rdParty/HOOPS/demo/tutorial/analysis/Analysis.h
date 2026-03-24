// Analysis.h : interface of the CAnalysisApp class, derived from CHoopsApp
// This is the main header for the application


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef _CAnalysisApp_H__
#define _CAnalysisApp_H__

#include "hc.h"
#include "CHoopsApp.h"


class HDB;


/////////////////////////////////////////////////////////////////////////////
// CAnalysisApp:
// See CAnalysisApp.cpp for the implementation of this class
//

class CAnalysisApp : public CHoopsApp
{

protected:



public:
	CAnalysisApp();


  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnalysisApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// _CAnalysisApp_H__
