// UserPasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "UserPasswordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg dialog


CPasswordDlg::CPasswordDlg(CString csRealm, CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
{
	m_csRealm = csRealm;
	//{{AFX_DATA_INIT(CPasswordDlg)
	m_csPassword = _T("");
	//}}AFX_DATA_INIT
}


void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordDlg)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_REALM, m_csRealm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CPasswordDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CUserPasswordDlg dialog


CUserPasswordDlg::CUserPasswordDlg(CString csRealm, CWnd* pParent /*=NULL*/)
	: CDialog(CUserPasswordDlg::IDD, pParent)
{
	m_csRealm = csRealm;
	//{{AFX_DATA_INIT(CUserPasswordDlg)
	m_csPassword = _T("");
	m_csUser = _T("");
	//}}AFX_DATA_INIT
}


void CUserPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserPasswordDlg)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	DDX_Text(pDX, IDC_REALM, m_csRealm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CUserPasswordDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserPasswordDlg message handlers
