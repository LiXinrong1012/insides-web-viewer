#if !defined(AFX_ERRORBROWSERDLG_H__5B118EC3_86EF_4D34_8037_7A3A8CA43624__INCLUDED_)
#define AFX_ERRORBROWSERDLG_H__5B118EC3_86EF_4D34_8037_7A3A8CA43624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorBrowserDlg.h : header file
//

class HBaseView;
class HErrorNode;
/////////////////////////////////////////////////////////////////////////////
// CErrorBrowserDlg dialog

class CErrorBrowserDlg : public CDialog
{
// Construction
public:
 	CErrorBrowserDlg(CWnd* pParent = NULL,HBaseView * View = 0);   // standard constructor
	~CErrorBrowserDlg();
	void RefreshErrorList();
	void RefreshAll(bool errorlist = true);



// Dialog Data
	//{{AFX_DATA(CErrorBrowserDlg)
	enum { IDD = IDD_ERRORBROWSER };
	CListBox	m_ErrorList;
 	CString	m_richedit;
	//}}AFX_DATA

	void ShowError(HErrorNode *node);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorBrowserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	bool m_dialogactive;
	// Generated message map functions
	//{{AFX_MSG(CErrorBrowserDlg)
	afx_msg void OnSelchangeErrorList();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClearErrorList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnUnblockErrors();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORBROWSERDLG_H__5B118EC3_86EF_4D34_8037_7A3A8CA43624__INCLUDED_)
