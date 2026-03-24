#if !defined(AFX_MAINSTYLEWINDOW_H__DE507B0E_A6B9_48D5_9D34_E16844934CC7__INCLUDED_)
#define AFX_MAINSTYLEWINDOW_H__DE507B0E_A6B9_48D5_9D34_E16844934CC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainStyleWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MainStyleWindow window

class HoopsStyleViewer;
class HoopsStyle;
class HoopsStyleLibrary;

class MainStyleWindow : public CWnd
{
// Construction
public:
	MainStyleWindow(HoopsStyleLibrary *slib);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainStyleWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MainStyleWindow();
	void SetStyle(HoopsStyle *style) ;
	HoopsStyle * GetStyle();
	HoopsStyleViewer *GetStyleViewer() { return m_pStyleViewer; }
	void UpdateWindow();

	// Generated message map functions
protected:
	HoopsStyleViewer *m_pStyleViewer;
	HoopsStyleLibrary *m_pStyleLibrary;
	HC_KEY thiskey;
	//{{AFX_MSG(MainStyleWindow)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSTYLEWINDOW_H__DE507B0E_A6B9_48D5_9D34_E16844934CC7__INCLUDED_)
