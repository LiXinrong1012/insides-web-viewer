
#pragma once

#include "Resource.h"
#include "HIOManager.h"

class CSolidHoopsView;
class CFileLoadProgressDlg : public CDialog, public HIONoticeCallback, public HIOPercentNoticeCallback
{
	DECLARE_DYNAMIC(CFileLoadProgressDlg)

public:
	CFileLoadProgressDlg(HInputHandler * handler, CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileLoadProgressDlg();

	enum { IDD = IDD_FILE_LOAD_PROGRESS };
 
	void Output(CString output);
	void Notice(char const * msg);
	void Notice(wchar_t const * msg);
	void Notice(float percent);

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CProgressCtrl m_ProgressCtrl;
	CRichEditCtrl m_edit;	
	HInputHandler * m_handler;
	CSolidHoopsView *m_View;
	void SetProgress(float);
	void SetLocalProgress(float);

	DECLARE_MESSAGE_MAP()
};
