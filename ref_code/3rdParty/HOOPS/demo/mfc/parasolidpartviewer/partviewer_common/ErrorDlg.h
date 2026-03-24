#if !defined(AFX_ERRORDLG_H__38E48C83_EBBB_4104_B180_01C631AB7AFD__INCLUDED_)
#define AFX_ERRORDLG_H__38E48C83_EBBB_4104_B180_01C631AB7AFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorDlg.h : header file
//

class HErrorNode;
/////////////////////////////////////////////////////////////////////////////
// CErrorDlg dialog

class CErrorDlg : public CDialog
{
// Construction
public:
	CErrorDlg(CWnd* pParent = NULL, HErrorNode *node = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CErrorDlg)
	enum { IDD = IDD_ERROR_DISPLAY };
	BOOL	m_SuppressAllCategory;
	BOOL	m_bSuppressDialog;
	bool	m_HasQuit;
	CString	m_Error_Message;
	CString	m_Error_Stack;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HErrorNode *m_ErrorNode;
	// Generated message map functions
	//{{AFX_MSG(CErrorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnContinueandsuppress();
	afx_msg void OnExitapplication();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORDLG_H__38E48C83_EBBB_4104_B180_01C631AB7AFD__INCLUDED_)
