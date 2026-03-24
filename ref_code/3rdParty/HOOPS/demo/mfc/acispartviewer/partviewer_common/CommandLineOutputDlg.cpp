#include "stdafx.h"
#include "Windows.h"

#include "CommandLineOutputDlg.h"

#include "utf_utils.h"


IMPLEMENT_DYNAMIC(CCommandLineOutputDlg, CDialog)

BEGIN_MESSAGE_MAP(CCommandLineOutputDlg, CDialog)
	ON_BN_CLICKED(IDC_COMMAND_LINE_OUTPUT_OK, CCommandLineOutputDlg::OnOK)
END_MESSAGE_MAP()

CCommandLineOutputDlg::CCommandLineOutputDlg ( CWnd * pParent /*=NULL*/ ) : CDialog(CCommandLineOutputDlg::IDD, 0) {
	m_quit = false;
}

CCommandLineOutputDlg::~CCommandLineOutputDlg () {}

BOOL CCommandLineOutputDlg::OnInitDialog () {
	CenterWindow();
	return CDialog::OnInitDialog();
}

void CCommandLineOutputDlg::DoDataExchange ( CDataExchange * pDX ) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_COMMAND_LINE_OUTPUT, m_edit);
}

void CCommandLineOutputDlg::OnOK () {
	DestroyWindow();
	if (m_quit)
		PostQuitMessage(0);
}

void CCommandLineOutputDlg::OnCancel () {
	DestroyWindow();
	if (m_quit)
		PostQuitMessage(0);
}

void CCommandLineOutputDlg::OnClose () {
	if (m_quit)
		PostQuitMessage(0);
	// inherited OnClose will destroy window for us
	CDialog::OnClose();
}

void CCommandLineOutputDlg::Output ( CString output ) {
	m_edit.HideSelection(FALSE, FALSE);
	m_edit.ReplaceSel(output);
	m_edit.ReplaceSel(_T("\x0d\x0a"));
	m_edit.SetSel(m_edit.GetTextLength(), -1);
}

void CCommandLineOutputDlg::Notice ( char const * msg ) {
	Notice(static_cast<wchar_t const *>(H_WCS(msg).encodedText()));
}

void CCommandLineOutputDlg::Notice ( wchar_t const * msg ) {
	Output(msg);
	UpdateWindow();
}

void CCommandLineOutputDlg::SetAutoQuit ( bool quit ) {
	m_quit = quit;
}
