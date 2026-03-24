#if !defined(AFX_TEXTINPUT_H__9620F9F8_09C1_49DF_8DD6_EC62F6D924AC__INCLUDED_)
#define AFX_TEXTINPUT_H__9620F9F8_09C1_49DF_8DD6_EC62F6D924AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextInput dialog

class CTextInput : public CDialog
{
// Construction
public:
	CTextInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextInput)
	enum { IDD = IDD_TEXT_INPUT_DIALOG };
	CString	m_TextField;
	CString	m_InfoText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 
	// Generated message map functions
	//{{AFX_MSG(CTextInput)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTINPUT_H__9620F9F8_09C1_49DF_8DD6_EC62F6D924AC__INCLUDED_)
