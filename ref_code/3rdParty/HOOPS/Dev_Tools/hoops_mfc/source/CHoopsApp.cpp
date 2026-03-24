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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mfc/source/CHoopsApp.cpp,v 1.6 2006-08-07 20:38:44 stage Exp $
//

// CHoopsApp.cpp : Defines the class behaviors for the application.
// 

#include "stdafx.h"
#include "CHoopsApp.h"


#include "HDB.h"

#include "assert.h"


/////////////////////////////////////////////////////////////////////////////
// CHoopsApp

BEGIN_MESSAGE_MAP(CHoopsApp, CWinApp)
	//{{AFX_MSG_MAP(CHoopsApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHoopsApp construction

CHoopsApp::CHoopsApp()
{
	m_pHoopsDB = NULL;
    m_pCTDriver = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CHoopsApp initialization

BOOL CHoopsApp::InitInstance()
{
	return CWinApp::InitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// CHoopsApp commands

int CHoopsApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}


