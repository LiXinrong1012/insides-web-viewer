// SpheresView.h : interface of the CSpheresView class, derived from CHoopsView
// Adds application specific members such as a QueryDialog and UI update/message maps

#if !defined(AFX_CSpheresView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CSpheresView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// SpheresView.h : header file
//

#include "CHoopsView.h"

class HSpheresView;
class HStreamFileToolkit;


////////////////////////////////////////////////////////////////////////////////
// CSpheresView view

class CSpheresView : public CHoopsView
{
protected:

	CSpheresView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSpheresView)

// Attributes
public:

 // Operations
public:
	HSpheresView* GetSolidView() { return (HSpheresView*)m_pHView; }

	// set current operator
	void LocalSetOperator(HBaseOperator *NewOperator);

	void LoadFile( LPCTSTR csFilePathName );
	bool SaveFile( LPCTSTR csFilePathName );

	// HNet


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpheresView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

private:


// Implementation
protected:
	virtual ~CSpheresView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	int FindMenuItem(CMenu* Menu, LPCTSTR MenuString);


	// Generated message map functions
protected:
	//{{AFX_MSG(CSpheresView)
	afx_msg void OnFileSaveAs();
	afx_msg void OnZoom();
	afx_msg void OnZoomToExtents();
	afx_msg void OnZoomToWindow();
	afx_msg void OnOrbit();
	afx_msg void OnPan();
	afx_msg void OnAnnotate();  //!< Activate the HOpMarkupAnnotate operator
	afx_msg void OnRotate();    //!< Activete the HOpObjectRotate operator
	afx_msg void OnChangeMaterial();  //!< change the material property of the selected objects
	afx_msg void OnWindowSelect();
	afx_msg void OnUpdateShaded(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHiddenLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrbit(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToWindow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToExtents(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeShaded();      //!< Set the render mode to smooth (gouraud) shading
	afx_msg void OnToolsRendermodePhongshaded(); //!< Set the render mode to phong shading
	afx_msg void OnToolsRendermodeHiddenline();  //!< Set the render mode to hidden line removal
	afx_msg void OnToolsRendermodeWireframe();   //!< Set the render mode to wireframe
	afx_msg void OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsRendermodeShaded(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI);
	afx_msg void OnCreateCone();
	afx_msg void OnCreateCylinder();
	afx_msg void OnCreateSphere();
	afx_msg void OnUpdateCreateCone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateCylinder(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateSphere(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void load(const char * filename);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSpheresView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
