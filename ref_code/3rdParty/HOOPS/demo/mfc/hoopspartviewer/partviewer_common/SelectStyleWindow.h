#if !defined(AFX_SELECTSTYLEWINDOW_H__2235D0FA_DD29_468B_9864_3978A89A18A6__INCLUDED_)
#define AFX_SELECTSTYLEWINDOW_H__2235D0FA_DD29_468B_9864_3978A89A18A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectStyleWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectStyleWindow window
class HoopsStyleViewer;
class HoopsStyleSelector;
class HoopsStyle;
class CStyleDialog;
class HoopsStyleLibrary;
class SelectStyleWindow : public CWnd
{
// Construction
public:
	SelectStyleWindow(CStyleDialog *owner, HBaseView *view);
	void UpdateWindow(bool noset = true);
	int GetPosition();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectStyleWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~SelectStyleWindow();
	HoopsStyle * GetCurrentStyle();
	int GetStyleNum();
	void Scroll(int s);
	void RefreshStyleList();

	HoopsStyleLibrary *GetStyleLibrary();
 	// Generated message map functions
    	HoopsStyle * GetStyleByName(const char *name);
	void SetStyle (HoopsStyle *style);
	int GetNumStyles();

protected:
 	HoopsStyleViewer *m_pStyleViewer;
	CStyleDialog * m_pOwnerDialog;
	HC_KEY m_ViewKey;
	HoopsStyleSelector *m_pStyleSelector;
	HBaseView *m_pHView;
 
	//{{AFX_MSG(SelectStyleWindow)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTSTYLEWINDOW_H__2235D0FA_DD29_468B_9864_3978A89A18A6__INCLUDED_)
