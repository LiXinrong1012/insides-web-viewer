#if !defined(AFX_XMLEDITORDLG_H__CDDD6225_C23D_4F04_AAA3_3B8DAF2AB025__INCLUDED_)
#define AFX_XMLEDITORDLG_H__CDDD6225_C23D_4F04_AAA3_3B8DAF2AB025__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMLEditorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// XMLEditorDlg dialog

class XMLEditorDlg : public CDialog
{
// Construction
public:
	XMLEditorDlg(CWnd* pParent = NULL, char *initialtext = 0, char *windowtext = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(XMLEditorDlg)
	enum { IDD = IDD_XML_DISPLAY };
	CString	m_richedit;
	CString m_windowtext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(XMLEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(XMLEditorDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class XMLEditorDlg2 : public CDialog
{
// Construction
public:
	XMLEditorDlg2(CWnd* pParent = NULL, char *initialtext = 0, char *windowtext = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(XMLEditorDlg)
	enum { IDD = IDD_XML_DISPLAY2 };
	CString	m_richedit;
	CString m_windowtext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(XMLEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(XMLEditorDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLEDITORDLG_H__CDDD6225_C23D_4F04_AAA3_3B8DAF2AB025__INCLUDED_)
