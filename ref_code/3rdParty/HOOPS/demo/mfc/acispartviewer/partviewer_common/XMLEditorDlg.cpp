// XMLEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "XMLEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XMLEditorDlg dialog


XMLEditorDlg::XMLEditorDlg(CWnd* pParent /*=NULL*/, char *initialtext, char *windowtext)
	: CDialog(XMLEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(XMLEditorDlg)
	m_richedit = initialtext;
	if (windowtext)
		m_windowtext = windowtext;
	else
		m_windowtext = "";
	//}}AFX_DATA_INIT
}


void XMLEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XMLEditorDlg)
	DDX_Text(pDX, IDC_RICHEDIT1, m_richedit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XMLEditorDlg, CDialog)
	//{{AFX_MSG_MAP(XMLEditorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XMLEditorDlg message handlers

BOOL XMLEditorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
		CRichEditCtrl *cbox = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT1);
	// TODO: Add extra initialization here

	cbox->LimitText(1048576);
	UpdateData(false);
	if (m_windowtext != "")
		SetWindowText(m_windowtext);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void XMLEditorDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	CDialog::OnOK();
}





/////////////////////////////////////////////////////////////////////////////
// XMLEditorDlg dialog


XMLEditorDlg2::XMLEditorDlg2(CWnd* pParent /*=NULL*/, char *initialtext, char *windowtext )
	: CDialog(XMLEditorDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(XMLEditorDlg)
	m_richedit = initialtext;
	if (windowtext)
		m_windowtext = windowtext;
	else
		m_windowtext = "";
	//}}AFX_DATA_INIT
}


void XMLEditorDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XMLEditorDlg)
	DDX_Text(pDX, IDC_RICHEDIT2, m_richedit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XMLEditorDlg2, CDialog)
	//{{AFX_MSG_MAP(XMLEditorDlg2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XMLEditorDlg message handlers

BOOL XMLEditorDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(false);
	if (m_windowtext != "")
		SetWindowText( m_windowtext);
	

	
 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void XMLEditorDlg2::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	CDialog::OnOK();
}
