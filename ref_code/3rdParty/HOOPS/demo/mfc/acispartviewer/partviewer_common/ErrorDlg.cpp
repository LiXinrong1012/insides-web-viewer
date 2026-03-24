// ErrorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ErrorDlg.h"
#include "HErrorManager.h"
#include "HUtilityLocaleString.h"
#include "CSolidHoopsApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorDlg dialog

CErrorDlg::CErrorDlg(CWnd* pParent /*=NULL*/, HErrorNode *node)
	: CDialog(CErrorDlg::IDD, pParent)
{
	m_ErrorNode = node;
	//{{AFX_DATA_INIT(CErrorDlg)
	m_SuppressAllCategory = FALSE;
	m_bSuppressDialog = FALSE;
	m_Error_Message = _T("");
	m_Error_Stack = _T("");
	m_HasQuit = false;
	//}}AFX_DATA_INIT
}


void CErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorDlg)
	DDX_Check(pDX, IDC_SUPPRESS_ALL_CATEGORY, m_SuppressAllCategory);
	DDX_Check(pDX, IDC_SUPPRESS_DIALOG, m_bSuppressDialog);
	DDX_Text(pDX, IDC_RICHEDIT_ERROR_MESSAGE, m_Error_Message);
	DDX_Text(pDX, IDC_RICHEDIT_ERROR_STACK, m_Error_Stack);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErrorDlg, CDialog)
	//{{AFX_MSG_MAP(CErrorDlg)
	ON_BN_CLICKED(IDCONTINUEANDSUPPRESS, OnContinueandsuppress)
	ON_BN_CLICKED(IDEXITAPPLICATION, OnExitapplication)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorDlg message handlers

BOOL CErrorDlg::OnInitDialog() 
{
	int i;
	char text[MVO_BUFFER_SIZE];
	char text2[MVO_BUFFER_SIZE];
	CDialog::OnInitDialog();
	CDialog *cbox =(CDialog *)GetDlgItem(IDC_ERROR_SEVERITY);
	switch(m_ErrorNode->m_severity)
	{
	case 0:
		strcpy(text, "Info");
 		break;
	case 1:
		strcpy(text, "Warning");
 		break;
	case 2:
		strcpy(text, "Error");
 		break;
	case 3:
		strcpy(text, "Fatal Error");
 		break;

	}
	
	SetWindowText(H_UNICODE_TEXT(text));
	cbox->SetWindowText(H_UNICODE_TEXT(text));
	sprintf(text2, "Block all %ss", text);
	cbox =(CDialog *)GetDlgItem(IDC_SUPPRESS_ALL_CATEGORY);
	cbox->SetWindowText(H_UNICODE_TEXT(text2));


	cbox =(CDialog *)GetDlgItem(IDC_ERROR_CATEGORY);
	sprintf(text, "%d", m_ErrorNode->m_category);
	cbox->SetWindowText(H_UNICODE_TEXT(text));
	cbox =(CDialog *)GetDlgItem(IDC_ERROR_SPECIFIC);
	sprintf(text, "%d", m_ErrorNode->m_specific);
	cbox->SetWindowText(H_UNICODE_TEXT(text));
	

	char errormessage[MVO_BUFFER_SIZE];
	strcpy(errormessage,"");
	for (i=0;i<m_ErrorNode->m_messagelength;i++)
	{
		strcat(errormessage,m_ErrorNode->m_message[i]);
		strcat(errormessage,"\n");
  
	}
	m_Error_Message = H_UNICODE_TEXT(errormessage);
	
	char errorstack[MVO_BUFFER_SIZE];
	strcpy(errorstack,"");

 	for (i=0;i<m_ErrorNode->m_stacklength;i++)
	{
		strcat(errorstack,m_ErrorNode->m_stack[i]);
		strcat(errorstack,"\n");

	}
	m_Error_Stack = H_UNICODE_TEXT(errorstack);

	UpdateData(false);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CErrorDlg::OnContinueandsuppress() 
{
	UpdateData(true);
	if (m_SuppressAllCategory)
		HErrorManager::SuppressError(m_ErrorNode->m_severity, 0,0);

	HErrorManager::SetShowDialog(!m_bSuppressDialog);

	HErrorManager::SuppressError(m_ErrorNode->m_severity, m_ErrorNode->m_category, m_ErrorNode->m_specific);
	// TODO: Add your control notification handler code here
	CDialog::OnOK();	
}

void CErrorDlg::OnExitapplication() 
{
	m_HasQuit = true;
	CDialog::OnOK();
}

void CErrorDlg::OnOK() 
{
	UpdateData(true);
	if (m_SuppressAllCategory)
		HErrorManager::SuppressError(m_ErrorNode->m_severity, 0,0);
	HErrorManager::SetShowDialog(!m_bSuppressDialog);

	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
