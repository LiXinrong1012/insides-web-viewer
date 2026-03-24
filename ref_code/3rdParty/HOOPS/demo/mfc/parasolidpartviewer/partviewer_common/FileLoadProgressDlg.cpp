// FileLoadProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileLoadProgressDlg.h"
#include "HUtilityLocaleString.h"
#include "Windows.h"
#include "utf_utils.h"


// CFileLoadProgressDlg dialog

IMPLEMENT_DYNAMIC(CFileLoadProgressDlg, CDialog)

CFileLoadProgressDlg::CFileLoadProgressDlg(HInputHandler * handler, CWnd* pParent /*=NULL*/)
	: CDialog(CFileLoadProgressDlg::IDD, 0)
{
	m_handler = handler;	
	m_View = (CSolidHoopsView *)pParent;
	if (m_handler) {
		m_handler->SetInputProgressNoticeCallback(this);
		m_handler->SetInputInformationNoticeCallback(this);
		m_handler->SetInputPercentProgressNoticeCallback(this);
 	}
}

CFileLoadProgressDlg::~CFileLoadProgressDlg()
{
	if (m_handler) {
		m_handler->SetInputProgressNoticeCallback(0);
		m_handler->SetInputInformationNoticeCallback(0);
		m_handler->SetInputPercentProgressNoticeCallback(0);
	}
}


BOOL CFileLoadProgressDlg::OnInitDialog(){
	CenterWindow();
	return CDialog::OnInitDialog();
}

void CFileLoadProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_FILE_LOAD_PROGRESS_PROGRESS, m_ProgressCtrl);
	DDX_Control(pDX, IDD_FILE_LOAD_PROGRESS_OUTPUT, m_edit);
}


BEGIN_MESSAGE_MAP(CFileLoadProgressDlg, CDialog)
	ON_BN_CLICKED(IDD_FILE_LOAD_PROGRESS_OK, CFileLoadProgressDlg::OnOK)
END_MESSAGE_MAP()

void CFileLoadProgressDlg::SetProgress(float progress){
	SetWindowText(H_TEXT(H_FORMAT_TEXT("Loading File... (%d%%)", (int)(progress * 100))));	
 }

void CFileLoadProgressDlg::SetLocalProgress(float progress){
	m_ProgressCtrl.SetPos((int)(progress * 100));
	UpdateWindow();
 }

void CFileLoadProgressDlg::Output(CString output) {
	/* Magic trick to automagically scroll to the bottom... */
 	m_edit.HideSelection(FALSE,FALSE);
	m_edit.ReplaceSel(output);
	m_edit.ReplaceSel(_T("\x0d\x0a"));
	m_edit.SetSel(m_edit.GetTextLength(),-1);
 }


 
void CFileLoadProgressDlg::Notice(char const * msg) {
	Notice((wchar_t const*)H_WCS(msg).encodedText());
}

void CFileLoadProgressDlg::Notice(wchar_t const * msg) {
	Output(msg);
	UpdateWindow();
}

void CFileLoadProgressDlg::Notice(float percent) {
	ShowWindow(SW_NORMAL);
	SetProgress(percent);
	SetLocalProgress(percent);
	UpdateWindow();
}
