#pragma once

#include "Resource.h"

class CCommandLineOutputDlg : public CDialog {
	DECLARE_DYNAMIC(CCommandLineOutputDlg)

public:
	CCommandLineOutputDlg ( CWnd * pParent = NULL );   // standard constructor
	virtual ~CCommandLineOutputDlg ();

	enum { IDD = IDD_COMMAND_LINE_OUTPUT_WINDOW };

	void Output ( CString output );
	
	void Notice ( char const * msg );
	void Notice ( wchar_t const * msg );

	void SetAutoQuit ( bool quit );

protected:
	BOOL OnInitDialog ();
	virtual void DoDataExchange ( CDataExchange * pDX );    // DDX/DDV support
	virtual void OnOK ();
	virtual void OnCancel ();
	virtual void OnClose ();
	
	CRichEditCtrl m_edit;
	bool m_quit;

	DECLARE_MESSAGE_MAP()
};