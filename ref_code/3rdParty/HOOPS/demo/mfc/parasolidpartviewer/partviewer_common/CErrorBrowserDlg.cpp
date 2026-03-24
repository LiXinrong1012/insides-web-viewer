// ErrorBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CErrorBrowserDlg.h"
#include "HErrorManager.h"
#include "hc.h"
#include "HUtilityLocaleString.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorBrowserDlg dialog

CErrorBrowserDlg::CErrorBrowserDlg(CWnd* pParent /*=NULL*/, HBaseView * View)
: CDialog(CErrorBrowserDlg::IDD, pParent)
{
	m_dialogactive=false;	

	//{{AFX_DATA_INIT(XMLEditorDlg)
	m_richedit = _T("");
	//}}AFX_DATA_INIT

}

CErrorBrowserDlg::~CErrorBrowserDlg()
{
}

void CErrorBrowserDlg::ShowError(HErrorNode *node)
{

	if (!node)
		m_richedit = _T("");
	else
	{	
 
		char text[MVO_BUFFER_SIZE];
		char text2[MVO_BUFFER_SIZE];
		switch(node->m_severity)
		{
		case 0:
			strcpy(text2,"Info");
			break;
		case 1:
			strcpy(text2,"Warning");
			break;
		case 2:
			strcpy(text2,"Error");
			break;
		case 3:
			strcpy(text2,"Fatal Error");
			break;
		}
		
		float ct;
		HC_Show_Time(&ct);
		float diff = ct - node->m_time;
		
		if (diff < 1)
			sprintf(text, "%s %d/%d", text2, node->m_category, node->m_specific);
		else
		{
			int r = diff;
			sprintf(text, "%s %d/%d (%d sec ago)", text2, node->m_category, node->m_specific, r);
		}
		
		
		
		
		int i;
		for (i=0;i<node->m_messagelength;i++)
		{
			strcat(text, "\n");
			strcat(text, node->m_message[i]);
		}
		strcat(text, "\n\nStack:");
		for (i=0;i<node->m_stacklength;i++)
		{
			strcat(text, "\n");
			strcat(text, node->m_stack[i]);
			
		}
		m_richedit = H_UNICODE_TEXT(text);
	}
	UpdateData(false);
 

}

 void CErrorBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorBrowserDlg)
	DDX_Control(pDX, IDC_ERROR_LIST, m_ErrorList);
  	DDX_Text(pDX, IDC_ERROR_INFO_BOX, m_richedit);
	//}}AFX_DATA_MAP
}

void CErrorBrowserDlg::RefreshErrorList()
{
	m_ErrorList.ResetContent();
	HErrorManager::BeginErrorIteration();
	while (1)
	{	
		HErrorNode *node = HErrorManager::GetNextError();
		if (!node)
			break;
		char text[MVO_BUFFER_SIZE];
		sprintf(text, "%d/%d/%d %s", node->m_severity, node->m_category, node->m_specific, node->m_message[0]);
		m_ErrorList.AddString(H_UNICODE_TEXT(text));
	}

 }

BEGIN_MESSAGE_MAP(CErrorBrowserDlg, CDialog)
	//{{AFX_MSG_MAP(CErrorBrowserDlg)
	ON_LBN_SELCHANGE(IDC_ERROR_LIST, OnSelchangeErrorList)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CLEAR_ERROR_LIST, OnClearErrorList)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_UNBLOCK_ERRORS, OnUnblockErrors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorBrowserDlg message handlers

void CErrorBrowserDlg::OnSelchangeErrorList() 
{

	RefreshAll(false);
	// TODO: Add your control notification handler code here
	
}

void CErrorBrowserDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	RefreshAll();
	// TODO: Add your message handler code here
	
}

void CErrorBrowserDlg::RefreshAll(bool refresherrorlist)
{
	int sel = m_ErrorList.GetCurSel();
	HErrorNode *node = 0;

	if (sel!= LB_ERR)
	{	
		HErrorManager::BeginErrorIteration();
		for (int i=0;i<sel+1;i++)
			node = HErrorManager::GetNextError();
	}
	else
		node = HErrorManager::GetLastError();
	 
	ShowError(node);
	
	if (refresherrorlist)
		RefreshErrorList();
}
void CErrorBrowserDlg::OnClearErrorList() 
{
	HErrorManager::Flush();
	RefreshAll();
	// TODO: Add your control notification handler code here
	
}

void CErrorBrowserDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy); 
	if (cx<241)
		cx = 241;
	
	if (m_dialogactive)
	{
		m_ErrorList.SetWindowPos(0, 0,0,cx - 50,cy - 290, SWP_NOMOVE | SWP_NOREPOSITION);   	
		CWnd *wnd = GetDlgItem(IDC_ERRORLIST_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 40,cy - 265, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_ERRORBROWSERWRAP);
		wnd->SetWindowPos(0, 0,0,cx - 25,cy - 20, SWP_NOMOVE | SWP_NOREPOSITION);   


/*		CWnd *wnd = GetDlgItem(IDC_SEGBROWSERWRAP);
		wnd->SetWindowPos(0, 0,0,cx - 30,cy - 50, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_BROWSER_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 48,cy - 240, SWP_NOMOVE | SWP_NOREPOSITION);   
		m_TopInfoList.SetWindowPos(0, 0,0,cx - 60,75, SWP_NOMOVE | SWP_NOREPOSITION);   	
		wnd = GetDlgItem(IDC_INFO_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 48,100, SWP_NOMOVE | SWP_NOREPOSITION);   
		CRect r;
 		m_SegmentBrowserSwitch.SetWindowPos(0, 10,cy-30,0,0,SWP_NOSIZE);
 		m_TopologyBrowserSwitch.SetWindowPos(0, 130,cy-30,0,0,SWP_NOSIZE);

 		m_SearchButton.SetWindowPos(0, 130,cy-68,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_SEARCHEDIT);

 		wnd->SetWindowPos(0, 20,cy-68,0,0,SWP_NOSIZE);

		wnd = GetDlgItem(IDC_GEOMETRY_SEARCH);
 		wnd->SetWindowPos(0, 180,cy-72,0,0,SWP_NOSIZE);

		wnd = GetDlgItem(IDC_ATTRIBUTE_SEARCH);
 		wnd->SetWindowPos(0, 180,cy-55,0,0,SWP_NOSIZE);
*/
 		
	}
	
}

BOOL CErrorBrowserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_dialogactive=true;	
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CErrorBrowserDlg::OnClose() 
{
	m_dialogactive=false;	
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CErrorBrowserDlg::OnUnblockErrors() 
{

	HErrorManager::AllowAllErrors();
	// TODO: Add your control notification handler code here
	
}
