// CSpheresApp.cpp : Defines the class behaviors for the application.
//

#include "StdAfx.h"
#include "Resource.h"

#include "Spheres.h"
#include "SpheresDoc.h"
#include "SpheresView.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "HSpheresView.h"


#include "HDB.h"
#include "CTDriver.h"
#include "HIOUtilitySpheres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSpheresApp

BEGIN_MESSAGE_MAP(CSpheresApp, CHoopsApp)
	//{{AFX_MSG_MAP(CSpheresApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpheresApp construction

CSpheresApp::CSpheresApp()
{
//	HC_Define_System_Options("no warnings, no info, no errors, no message limit");

	m_pHoopsDB = NULL;
	m_pCTDriver = NULL;
	m_pIOUtilitySpheres = NULL;
}

CSpheresApp::~CSpheresApp()
{
	delete m_pIOUtilitySpheres;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSpheresApp object

CSpheresApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSpheresApp initialization

BOOL CSpheresApp::InitInstance()
{
	m_pHoopsDB = new HDB;
	m_pHoopsDB->Init();

	//m_pCTDriver must be started after m_pHoopsDB is created
	m_pCTDriver = new CTDriver( 10 );
	m_pCTDriver->StartTimer();

	m_pIOUtilitySpheres = new HIOUtilitySpheres();
	HIORegisterInputType("sph",   m_pIOUtilitySpheres);
	HIORegisterOutputType("sph",  m_pIOUtilitySpheres);


	// Standard initialization
	// If you are planning to use this source code in Visual Studio 6.0 or 
	// earlier versions, you should uncomment the following
//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	LoadStdProfileSettings();   // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_HOOPSTYPE,
		RUNTIME_CLASS(CSpheresDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSpheresView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window using our custom HOOPS Frame
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew )
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// Dispatch commands specified on the command line	
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();


	TCHAR fontDirectory[MAX_PATH+32];
    ::GetWindowsDirectory(fontDirectory, MAX_PATH);
    _tcscat(fontDirectory, _T("\\Fonts"));
    char buf[MAX_PATH+64];
    sprintf(buf, "font directory = %s", fontDirectory);
    HC_Define_System_Options(buf);


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CSpheresApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHoopsApp commands

int CSpheresApp::ExitInstance() 
{
	// m_pCTDriver must be deleted before m_pHoopsDB
	H_SAFE_DELETE(m_pCTDriver);
	H_SAFE_DELETE(m_pHoopsDB);
	H_SAFE_DELETE(m_pIOUtilitySpheres);

	return CHoopsApp::ExitInstance();
}


