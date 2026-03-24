//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/mfc_simple/simpleView.h,v 1.5 2010-11-02 00:42:06 heppe Exp $
//

// simpleView.h : interface of the CSimpleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEVIEW_H__F25807A1_CACF_11D3_ABF4_0050046769B1__INCLUDED_)
#define AFX_SIMPLEVIEW_H__F25807A1_CACF_11D3_ABF4_0050046769B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// used for the copy to clipboard code
#define WMF             0
#define EMF             1

// different rendermode
#define SHADED		0
#define WIREFRAME	1
#define HIDDENLINE	2


// msw printer driver specific driver_option debug flags
#define DEBUG_PRINT_NOT_FRAMEBUFFER_MODE	0x00020000
#define DEBUG_PRINT_NOT_RASTER_REDUCTION  	0x00200000


// msw driver options debug
#define DEBUG_NO_WINDOWS_HOOK		0x00000040
#define DEBUG_FORCE_FULL_COLOR		0x00000010
#define DEBUG_SFB_COPY_TO_CLIPBOARD	0x00004000
#define DEBUG_NO_RASTERS_IN_PRINTING	0x00020000
#define DEBUG_PRINTING_MODE         0x00040000
#define DEBUG_CLIPBOARD_MODE        0x00080000

// rendering options debug
#define DEBUG_NO_PAINTERS_PANELLING	0x00000008


class CSimpleView : public CView
{
private:
	bool	m_bOperatorStarted;
	bool	m_bFastPrint;
	bool	m_bClipboardPrinting;
	bool	m_bClipboardTruecolor;
	int		m_MetafileType;
	long	m_lDriverKey;
	long	m_lSceneKey;
	char	m_sDriverSegment[1024];
	CPalette	*m_pViewPalette;
	HPoint	m_ptFirstPoint;
	HPoint  m_ptRealOld;

protected: // create from serialization only
	CSimpleView();
	DECLARE_DYNCREATE(CSimpleView)

// Attributes
public:
	CSimpleDoc* GetDocument();
	CPalette	*GetPalette();
	void	InitializePalette();
	void	FitWorld();
	int		GetRenderMode();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	virtual void PostNcDestroy() {
		CView::PostNcDestroy();
		HC_Reset_System ();
	};

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleView)
	afx_msg void OnPaint();
	afx_msg void OnEditCopy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnViewWireframe();
	afx_msg void OnUpdateViewWireframe(CCmdUI* pCmdUI);
	afx_msg void OnViewShaded();
	afx_msg void OnUpdateViewShaded(CCmdUI* pCmdUI);
	afx_msg void OnViewHiddenline();
	afx_msg void OnUpdateViewHiddenline(CCmdUI* pCmdUI);
	afx_msg void OnRunMyCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in simpleView.cpp
inline CSimpleDoc* CSimpleView::GetDocument()
   { return (CSimpleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEVIEW_H__F25807A1_CACF_11D3_ABF4_0050046769B1__INCLUDED_)
