// Soccer.h : interface of the CSoccerApp class, derived from CHoopsApp
// This is the main header for the application


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef _CSoccerApp_H__
#define _CSoccerApp_H__

#include "hc.h"
#include "CHoopsApp.h"


class HDB;


/////////////////////////////////////////////////////////////////////////////
// CSoccerApp:
// See CSoccerApp.cpp for the implementation of this class
//

class CSoccerApp : public CHoopsApp
{

protected:

public:
	CSoccerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoccerApp)
	public:
	/*! Initialize any global application data */
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSoccerApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// _CSoccerApp_H__
