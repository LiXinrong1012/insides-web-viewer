#if !defined(AFX_USERPASSWORDDLG_H__7A35E821_ED6B_4F2C_9D2C_9D25A1B9B48C__INCLUDED_)
#define AFX_USERPASSWORDDLG_H__7A35E821_ED6B_4F2C_9D2C_9D25A1B9B48C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserPasswordDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg dialog

class CPasswordDlg : public CDialog
{
// Construction
public:
	CPasswordDlg(CString csRealm, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPasswordDlg)
	enum { IDD = IDD_PASSWORD_PROMPT_DIALOG};
	CString	m_csPassword;
	CString	m_csRealm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPasswordDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CUserPasswordDlg dialog

class CUserPasswordDlg : public CDialog
{
// Construction
public:
	CUserPasswordDlg(CString csRealm, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserPasswordDlg)
	enum { IDD = IDD_USER_PASSWORD_PROMPT_DIALOG};
	CString	m_csPassword;
	CString	m_csUser;
	CString	m_csRealm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserPasswordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserPasswordDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERPASSWORDDLG_H__7A35E821_ED6B_4F2C_9D2C_9D25A1B9B48C__INCLUDED_)
