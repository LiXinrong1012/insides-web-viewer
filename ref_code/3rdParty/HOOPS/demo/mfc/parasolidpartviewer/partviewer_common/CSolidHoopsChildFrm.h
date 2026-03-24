#if !defined(AFX_CSOLIDHOOPSCHILDFRM_H__3620ACD9_BAC6_48F1_86DE_315167B99027__INCLUDED_)
#define AFX_CSOLIDHOOPSCHILDFRM_H__3620ACD9_BAC6_48F1_86DE_315167B99027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSolidHoopsChildFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsChildFrame frame

class CSolidHoopsChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CSolidHoopsChildFrame)
protected:
	CSolidHoopsChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

	int GetViewNum(){ return m_ViewNum; };
	void SetViewNum(int new_num){ m_ViewNum = new_num; };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSolidHoopsChildFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSolidHoopsChildFrame();

	CSplitterWnd    m_wndSplitter;
	BOOL			m_bCreated;
	int				m_ViewNum;

	// Generated message map functions
	//{{AFX_MSG(CSolidHoopsChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpmmi);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOLIDHOOPSCHILDFRM_H__3620ACD9_BAC6_48F1_86DE_315167B99027__INCLUDED_)
