// SoccerView.h : interface of the CSoccerView class, derived from CHoopsView
// Adds application specific members such as a QueryDialog and UI update/message maps

#if !defined(AFX_CSoccerView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CSoccerView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// SoccerView.h : header file
//

#include "CHoopsView.h"

class HSoccerView;
class HStreamFileToolkit;


////////////////////////////////////////////////////////////////////////////////
// CSoccerView view

class CSoccerView : public CHoopsView
{
protected:

	CSoccerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSoccerView)

// Attributes
public:

 // Operations
public:
	/*! return a pointer to the HSoccerView object associated with this MFC view object */
	HSoccerView* GetSolidView() { return (HSoccerView*)m_pHView; }

	/*! Local utlility function to set the current operator */
	void LocalSetOperator(HBaseOperator *NewOperator);

	/*! Loads in a file */
	void LoadFile( LPCTSTR csFilePathName );

	/*! Saves a file */
	bool SaveFile( LPCTSTR csFilePathName );

	// HNet


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoccerView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

	//}}AFX_VIRTUAL

private:


// Implementation
protected:
	virtual ~CSoccerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	int FindMenuItem(CMenu* Menu, LPCTSTR MenuString);


	// Generated message map functions
protected:
	//{{AFX_MSG(CSoccerView)
	afx_msg void OnFileSaveAs();
	/*! Set the current operator to the HOpCameraZoom */
	afx_msg void OnZoom();
	/*! Reset the camera to view the scene extents */
	afx_msg void OnZoomToExtents();
	/*! Set the current operator to the HOpCameraZoomBox */
	afx_msg void OnZoomToWindow();
	/*! Set the current operator to the HOpCameraOrbit */
	afx_msg void OnOrbit();
	/*! Set the current operator to the HOpCameraPan */
	afx_msg void OnPan();
	/*! Set the current operator to the HOpSelectArea */
	afx_msg void OnWindowSelect();
	/*! Set the current operator to the HOpSelectAperture */
	afx_msg void OnApertureSelect();
	afx_msg void OnUpdateGouraud(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHiddenLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrbit(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToWindow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToExtents(CCmdUI* pCmdUI);
	/*! Set rendermode to gouraud */
	afx_msg void OnToolsRendermodeGouraudshaded();
	/*! Set rendermode to hidden line */
	afx_msg void OnToolsRendermodeHiddenline();
	/*! Set rendermode to wireframe */
	afx_msg void OnToolsRendermodeWireframe();
	afx_msg void OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsRendermodeGouraudshaded(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI);
	/*! Sets the current operator to HOpCreateCone */
	afx_msg void OnCreateCone();
	/*! Sets the current operator to HOpCreateCylinder */
	afx_msg void OnCreateCylinder();
	/*! Sets the current operator to HOpCreateSphere */
	afx_msg void OnCreateSphere();
	/*! Sets the current operator to HOpCreateRectangle */
	afx_msg void OnCreateRectangle();
	afx_msg void OnUpdateCreateCone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateCylinder(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateSphere(CCmdUI* pCmdUI);
	/*! Delete the selected layers */
	afx_msg void OnDeleteLayers();
	afx_msg virtual void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg virtual void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg virtual void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	/*! utility function for file loading */
	void load(const char * filename);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSoccerView_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
