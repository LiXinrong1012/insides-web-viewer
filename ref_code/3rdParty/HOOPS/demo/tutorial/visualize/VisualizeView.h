// VisualizeView.h : interface of the CVisualizeView class, derived from CHoopsView
// Adds application specific members such as a QueryDialog and UI update/message maps

#if !defined(AFX_CVisualizeView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CVisualizeView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// VisualizeView.h : header file
//

#include "CHoopsView.h"

class HVisualizeView;
class HStreamFileToolkit;


////////////////////////////////////////////////////////////////////////////////
// CVisualizeView view

class CVisualizeView : public CHoopsView
{
protected:

	CVisualizeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVisualizeView)

// Attributes
public:

 // Operations
public:
	HVisualizeView* GetSolidView() { return (HVisualizeView*)m_pHView; }

	// set current operator
	void LocalSetOperator(HBaseOperator *NewOperator);

	void LoadFile( LPCTSTR csFilePathName );
	bool SaveFile( LPCTSTR csFilePathName );

	// HNet


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

private:


// Implementation
protected:
	virtual ~CVisualizeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	int FindMenuItem(CMenu* Menu, LPCTSTR MenuString);


	// Generated message map functions
protected:
	//{{AFX_MSG(CVisualizeView)
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
	afx_msg void OnBuildLODS();        //!< Create Levels of Detail for the model
	afx_msg void OnLOD1();             //!< Clamp to LOD level 1
	afx_msg void OnLOD2();             //!< Clamp to LOD level 2
	afx_msg void OnLODOriginal();      //!< Draw the original, full resolution model
	afx_msg void OnEnableFramerate();  //!< Enable constant framerate logic
	afx_msg void OnDisableFramerate(); //!< Disable constant framerate logic
	afx_msg void OnUpdateCreateSphere(CCmdUI* pCmdUI);
	afx_msg void OnCreateCone();
	afx_msg void OnCreateCylinder();
	afx_msg void OnUpdateCreateCone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateCylinder(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent); 
	afx_msg void OnWalkOperator();     //!< Set the current operator to HOpCameraWalk
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void load(const char * filename);

	static CVisualizeView * pThisView;
	
	//static void event_checker(struct ht_net_rendition *nr);
	static void event_checker(HIC_Rendition const *nr);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVisualizeView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
