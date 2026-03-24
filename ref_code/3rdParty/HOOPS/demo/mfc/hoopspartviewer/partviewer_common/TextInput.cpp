// TextInput.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TextInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextInput dialog


CTextInput::CTextInput(CWnd* pParent /*=NULL*/)
	: CDialog(CTextInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextInput)
	m_TextField = _T("");
	m_InfoText = _T("");
	//}}AFX_DATA_INIT
}


void CTextInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextInput)
	DDX_Text(pDX, IDC_TEXT_FIELD, m_TextField);
	DDX_Text(pDX, IDC_TEXT_INPUT_TEXT, m_InfoText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextInput, CDialog)
	//{{AFX_MSG_MAP(CTextInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextInput message handlers

BOOL CTextInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
