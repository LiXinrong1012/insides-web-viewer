// AnalysisView.h : interface of the CAnalysisView class, derived from CHoopsView
// Adds application specific members such as a QueryDialog and UI update/message maps

#if !defined(AFX_CAnalysisView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CAnalysisView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// AnalysisView.h : header file
//

#include "CHoopsView.h"

class HAnalysisView;
class HStreamFileToolkit;


////////////////////////////////////////////////////////////////////////////////
// CAnalysisView view

/*!
	Custom CHoopsView object which provides tutorial-specific GUI members and message maps 
*/
class CAnalysisView : public CHoopsView
{
protected:

	CAnalysisView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAnalysisView)

// Attributes
public:

	bool	m_bDisplayIsolines;  //!< indicates whether isolines are currently being displayed
	bool    m_bDisplayEdges;  //!< indicates whether edges are currently being displayed
	bool	m_bColorInterpolation;  //!< indicates whether color interpolation is currently enabled

 // Operations
public:
	HAnalysisView* GetSolidView() { return (HAnalysisView*)m_pHView; }

	// set current operator
	void LocalSetOperator(HBaseOperator *NewOperator);

	void LoadFile( LPCTSTR csFilePathName );
	bool SaveFile( LPCTSTR csFilePathName );

	void CleanUp();



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

private:

// Implementation
protected:
	virtual ~CAnalysisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	int FindMenuItem(CMenu* Menu, LPCTSTR MenuString);


	// Generated message map functions
protected:
	//{{AFX_MSG(CAnalysisView)
	afx_msg void OnFileSaveAs();
	afx_msg void OnZoom();
	afx_msg void OnZoomToExtents();
	afx_msg void OnZoomToWindow();
	afx_msg void OnOrbit();
	afx_msg void OnPan();
	afx_msg void OnWindowSelect();
	afx_msg void OnSelectionDeleteselection();
	afx_msg void OnUpdateSelectionDeleteselection(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGouraud(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHiddenLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrbit(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToWindow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToExtents(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeGouraudshaded();
	afx_msg void OnToolsRendermodeHiddenline();
	afx_msg void OnToolsRendermodeWireframe();
	afx_msg void OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsRendermodeGouraudshaded(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI);
	afx_msg void OnCreateSphere();
	afx_msg void OnUpdateCreateSphere(CCmdUI* pCmdUI);
	afx_msg void OnCreateCone();
	afx_msg void OnCreateCylinder();
	afx_msg void OnUpdateCreateCone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateCylinder(CCmdUI* pCmdUI);
	afx_msg void OnMapData();
	afx_msg void OnUpdateMapData(CCmdUI* pCmdUI);
	afx_msg void OnDisplayIsolines();
	afx_msg void OnUpdateDisplayIsolines(CCmdUI* pCmdUI);
	afx_msg void OnDisplayEdges();
	afx_msg void OnUpdateDisplayEdges(CCmdUI* pCmdUI);
	afx_msg void OnColorInterpolation();
	afx_msg void OnUpdateColorInterpolation(CCmdUI* pCmdUI);
	afx_msg void OnDisplayQuadInterpolate();
	afx_msg void OnAnimateColormap();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void load(const char * filename);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAnalysisView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
