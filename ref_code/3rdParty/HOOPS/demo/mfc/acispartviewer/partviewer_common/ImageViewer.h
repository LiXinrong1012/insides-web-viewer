#if !defined(AFX_IMAGEVIEWER_H__4B705CB7_7230_43D4_B4EE_8CF99600D781__INCLUDED_)
#define AFX_IMAGEVIEWER_H__4B705CB7_7230_43D4_B4EE_8CF99600D781__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageViewer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageViewer window
class CStyleDialog;
class HoopsTexture;

class CImageViewer : public CWnd
{
// Construction
public:
	CImageViewer(CStyleDialog *sd);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageViewer)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageViewer();

	void SetImage(HoopsTexture *tex);

	// Generated message map functions
protected:
	CStyleDialog * m_pOwnerDialog;
	HC_KEY thiskey;
	//{{AFX_MSG(CImageViewer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEWER_H__4B705CB7_7230_43D4_B4EE_8CF99600D781__INCLUDED_)
