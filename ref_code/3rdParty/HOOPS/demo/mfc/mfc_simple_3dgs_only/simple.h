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
// $Header: /files/homes/master/cvs/hoops_master/mfc_simple/simple.h,v 1.4 2008-02-06 01:14:38 jason Exp $
//

// simple.h : main header file for the SIMPLE application
//

#if !defined(AFX_SIMPLE_H__F2580797_CACF_11D3_ABF4_0050046769B1__INCLUDED_)
#define AFX_SIMPLE_H__F2580797_CACF_11D3_ABF4_0050046769B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "hc.h"

#	pragma warning(disable: 4996)	// standard string functions considered unsafe

// some structures/macros we use 
typedef struct {float x, y, z;} HPoint;
#define streq(a,b)      (!strcmp(a,b))

/////////////////////////////////////////////////////////////////////////////
// CSimpleApp:
// See simple.cpp for the implementation of this class
//

class CSimpleApp : public CWinApp
{
private:
	char	m_sDriverType[16];
	int		m_iCounter;

public:
	CSimpleApp();
	const char	*GetDriverType()	{return m_sDriverType;};
	int	IncrementCounter() {return m_iCounter++;};
	int	DecrementCounter() {return m_iCounter--;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSimpleApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLE_H__F2580797_CACF_11D3_ABF4_0050046769B1__INCLUDED_)
