// Spheres.h : interface of the CSpheresApp class, derived from CHoopsApp
// This is the main header for the application


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef _CSpheresApp_H__
#define _CSpheresApp_H__

#include "hc.h"
#include "CHoopsApp.h"


class HDB;
class HIOUtilitySpheres;

/////////////////////////////////////////////////////////////////////////////
// CSpheresApp:
// See CSpheresApp.cpp for the implementation of this class
//

class CSpheresApp : public CHoopsApp
{

protected:

	HIOUtilitySpheres * m_pIOUtilitySpheres;

public:
	CSpheresApp();
	~CSpheresApp();

  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpheresApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpheresApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// _CSpheresApp_H__
