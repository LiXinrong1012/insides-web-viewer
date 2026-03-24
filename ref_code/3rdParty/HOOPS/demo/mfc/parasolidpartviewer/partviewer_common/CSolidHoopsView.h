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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsView.h,v 1.218.2.1 2010-11-28 22:01:23 richard Exp $
//

// CSolidHoopsView.h : interface of the CSolidHoopsView class, derived from CHoopsView
// Adds application specific members such as a QueryDialog and UI update/message maps

#if !defined(AFX_CSOLIDHOOPSVIEW_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CSOLIDHOOPSVIEW_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSolidHoopsView.h : header file
//

#include "HStream.h"
#include "CHoopsView.h"
#include "CAppSettings.h"
#include "HConstantFramerate.h"

class CQueryDialog;
class CStyleDialog;
class CLodDialog;
class HSolidView;
class CSegmentBrowserDlg;
class CModelBrowserDlg;
class CErrorBrowserDlg;
class CKeyframeEditor;
class ClashDlg;
class ClashSelect;
class CCMMDisplay;
class HBaseOperator;
class HSOpMoveHandle;
class HOpMoveHandle;
class HSubwindow;
class HDWGLayoutLoadUtility;

#ifndef HOOPS_ONLY
class CTopolBrowserDlg;
#ifdef INTEROP
class CInterOpPartBrowserDlg;
#endif // INTEROP
#endif // HOOPS_ONLY

struct vlist_s;
struct vhash_s;


////////////////////////////////////////////////////////////////////////////////
// CSolidHoopsView view

class CSolidHoopsView : public CHoopsView, public HJoyStickListener
{
protected:
	CSolidHoopsView();           // protected constructor used by dynamic creation
	virtual void OnPaint();
	DECLARE_DYNCREATE(CSolidHoopsView)

    bool        m_edges;
    bool        m_lights;
	bool		m_grids;
	bool		m_text;
	bool		m_images;
	bool		m_hidden_lines_visible;
	bool		m_color_int;
	bool		m_color_index_int;
	bool		m_curvature_set;
	float		m_oldpos[3*3];
	bool		m_bHSFVersionMismatch;
	float		m_default_transmission;

	//HStreamFileReadingThread is a friend that communicates back and forth with this
	//class via the following two variables, m_cease and m_stream_lock
	bool		m_cease;

	friend unsigned int HStreamFileReadingThread(void *pParam);
	friend unsigned int HMainWorkerThread(void *pParam);
	HDWGLayoutLoadUtility * m_pLayoutLoadUtility;

public:
	HANDLE m_hStreamBufferAccessEvent;
	CQueryDialog*	m_query_dialog;
	CQueryDialog*	m_advanced_query_dialog;
	CStyleDialog*	m_style_dialog;
	CLodDialog*		m_lod_dialog;


	long m_CookieSelected;					// cookie for HSignalSelected signal subscription
	long m_CookieDeSelectedAll;				// cookie for HSignalDeSelectedAll signal subscription

 // Operations
public:

	void SetTransparency();
	void SetViewAxis();

	void SetMarkupColor(COLORREF new_color, bool emit_message = true);
	void SetWalkOperator();

 	// MVO event handlers
	static bool signal_selected(int signal, void *signal_data, void *user_data);
	bool OnSignalSelected();

	static bool signal_deselected_all(int signal, void *signal_data, void *user_data);
	bool OnSignalDeSelectedAll();

	void	SetQueryDialogText(char *text);
	void	SetAdvancedQueryDialogText(char *text);
	void	ShowQueryDialog(int showFlag);
	void	ShowAdvancedQueryDialog(int showFlag);
	void	SetStyleDialogText(char *text);
	void	ShowStyleDialog(int showFlag);

	void	EnableFrameRate(bool onoff = true);
	bool	IsFrameRateEnabled();

	void SetSceneFont(CString csFontName, CString csFontSize, CString csFontUnits);

	HSolidView* GetSolidView() { return (HSolidView*)m_pHView; }

	// set current operator
	void LocalSetOperator(HBaseOperator *NewOperator);

	void LoadFile( LPCTSTR csFilePathName, HStreamFileToolkit* tk);
	bool SaveFile( LPCTSTR csFilePathName );

	bool	m_bCameraBeforeBoundingBox;
	bool	m_bBoundingBox;
	bool	m_has_initial_view;
	
	void StartThreadedLoading();
	void StopThreadedLoading();


	void GetShells(HC_KEY key, vlist_s* retSelectedShells, bool do_recurse = true);

	void OnBehaviorHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnCMMHScroll(float);
	void UpdateBhvWindows(bool inv);
 
	// QA functions 
	//  Convert modeller NURBS data to HOOPS NURBS data
	void ExtractNURBSSurfaces(bool non_rational, bool trimmed, bool use_polyline);
	void ExtractNURBSCurves(bool non_rational, bool cubic, double tolerance = 1e-06);
	//   Merge face shells in one shell and different regions
	void ConvertFaceShellsToRegions();

	bool	GetSegmentBrowserState()	{ return m_pDlgSegmentBrowser!=0; };
	void	RefreshSegmentBrowser();
	CDialog * GetSegmentBrowserDialog();
	CDialog * GetErrorBrowserDialog();
	CDialog * GetTopologyBrowserDialog();
	CDialog * GetModelBrowserDialog();
	CDialog * GetKeyframeEditorDialog(bool create = true);
	CDialog * GetClashBrowserDialog(bool create = true);
	CDialog * GetClashSelectDialog(bool create = true);
	CDialog * GetCMMDisplayDialog(bool create = true);
	CDialog * GetInterOpPartBrowserDialog();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSolidHoopsView)
	public:
		virtual void OnInitialUpdate();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnSaveMarkup();
	virtual void OnEditMarkup();
 
	protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnNcDestroy();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// 3DMouse/Joystick events
	virtual int OnJoyStickRotation( HEventInfo &hevent);
	virtual int OnJoyStickTranslation( HEventInfo &hevent);
	virtual int OnJoyStickButton( HEventInfo &hevent);

	void HandleSpecialSelection();

	
private:
	virtual void MakeAndSetThumbnail(HStreamFileToolkit * mytool);

	class Verticals{
	public:
		class CAE{
		public:
			/*! Set/unset the visibility of the legend. */
			static void LegendVisibility(HBaseView * const pView, bool const onoff);
			/*! Get the visibility of the legend. */
			static bool LegendVisibility(HBaseView * const pView);

			/*! Generate fake CEA data for all the shells in the selection set. */
			static void MapSelectionSet(HBaseView * const pView);
			/*! Generate fake CEA data on the shell with the givin key. */
			static void MapData(HC_KEY const key);

			/*! Return true if color index interpolation is enabled. */
			static bool IndexInterpolation(HBaseView * const pView);
			/*! Set/unset color index interpolation. */
			static void IndexInterpolation(HBaseView * const pView, bool const onoff);

			/*! Return true if color interpolation is enabled. */
			static bool ColorInterpolation(HBaseView * const pView);
			/*! Set/unset color interpolation. */
			static void ColorInterpolation(HBaseView * const pView, bool const onoff);

			/*! Return true if color index interpolation = isolines. */
			static bool IsolineInterpolation(HBaseView * const pView);
			/*! Set/unset isoline color index interpolation. */
			static void IsolineInterpolation(HBaseView * const pView, bool const onoff);

			/*! Quad interpolate all the shells in the selection set. */
			static void QuadInterpolateSelectionSet(HBaseView * const pView);
			/*! Quad interpolate the shell with the givin key. */
			static void QuadInterpolateData(HC_KEY const key);

		private:
			/*! Animate the fake mapped data on all the shells in the selection set. */
			static void AnimateSelectionSet(HBaseView * const pView);

		};

		class CMM{
		public:
			/*! Set/unset collision detection on an animation. */
			static void EnableCollision(HBaseView * const m_pHView, bool const onoff);
			/*! Return true if collision detection is enabled. */
			static bool EnableCollision(HBaseView * const m_pHView);

			/*! Toggle the visibiliy of the cmm collision display. */
			static void DisplayVisibility(HBaseView * const m_pHView, bool const onoff);
			/*! Return true if the display is currently visible. */
			static bool DisplayVisibility(HBaseView * const m_pHView);
			
			/*! Set/unset the position change path lines visibility. */
			static void PositionVisibility(HBaseView * const m_pHView, bool const onoff);
			/*! return true if the position change path lines are visible. */
			static bool PositionVisibility(HBaseView * const m_pHView);
		};
	};
	unsigned long	m_StreamedSoFar;
	unsigned long	m_UpdatesSoFar;

	bool			m_bCfrActive;
	bool			m_bScanColorized;
	HPoint			m_PositionOnRightClick;
	HC_KEY			m_KeyUnderCursor;
	CSegmentBrowserDlg * m_pDlgSegmentBrowser;
	CModelBrowserDlg * m_pDlgModelBrowser;
	CErrorBrowserDlg * m_pDlgErrorBrowser;
	bool			m_bInSpecialSelection;
#ifndef HOOPS_ONLY
	CTopolBrowserDlg * m_pDlgTopologyBrowser;
#ifdef INTEROP
	CInterOpPartBrowserDlg * m_pDlgInterOpPartBrowser;
#endif // INTEROP
#endif // HOOPS_ONLY
	bool using_modelling_kernel;
	CKeyframeEditor * m_pDlgKeyframeEditor;
	ClashDlg * m_pDlgClashBrowser;
	ClashSelect * m_pDlgClashSelect;
	CCMMDisplay * m_pDlgCMMDisplay;

	float m_WalkSpeed;
	static void event_checker(HIC_Rendition const *nr);
// Implementation
protected:
	virtual ~CSolidHoopsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void ViewReady();

	int FindMenuItem(CMenu* Menu, LPCTSTR MenuString);

	// used to setup views when there are split-views
	void SetupViews();

	virtual void OnDisplayChanged(int xres, int yres, int depth);
  
	// Generated message map functions
protected:
	//{{AFX_MSG(CSolidHoopsView)
	afx_msg void OnFileSaveAs();
 	afx_msg void OnQuery();
	afx_msg void OnSubtract();
	afx_msg void OnUnion();
	afx_msg void OnZoom();
	afx_msg void OnZoomToExtents();
	afx_msg void OnZoomToWindow();
	afx_msg void OnOrbit();
	afx_msg void OnTurntable();
	afx_msg void OnPan();
 	afx_msg void OnApertureSelect();
	afx_msg void OnWindowSelect();
	afx_msg void OnIntersect();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnToolsTransparency();
 	afx_msg void OnToolsVisibilityVertices();
	afx_msg void OnUpdateToolsVisibilityVertices(CCmdUI* pCmdUI);
	afx_msg void OnToolsVisibilityEdges();
	afx_msg void OnUpdateToolsVisibilityEdges(CCmdUI* pCmdUI);
	afx_msg void OnToolsVisibilityFaces();
	afx_msg void OnUpdateToolsVisibilityFaces(CCmdUI* pCmdUI);
	afx_msg void OnToolsVisibilityMarkers();
	afx_msg void OnUpdateToolsVisibilityMarkers(CCmdUI* pCmdUI);
	afx_msg void OnLights();
	afx_msg void OnUpdateLights(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInstance(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAssembly(CCmdUI* pCmdUI);
	afx_msg void OnCurvature();
	afx_msg void OnUpdateCurvature(CCmdUI* pCmdUI);
	afx_msg void OnVertex();
 
	afx_msg void OnUpdateVertex(CCmdUI* pCmdUI);
	afx_msg void OnColorIndexInterpolation();
	afx_msg void OnDummy();
	afx_msg void OnColorInterpolation();
	afx_msg void OnUpdateColorIndexInterpolation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorInterpolation(CCmdUI* pCmdUI);
	afx_msg void OnOrthographic();
	afx_msg void OnUpdateOrthographic(CCmdUI* pCmdUI);
	afx_msg void OnPerspective();
	afx_msg void OnUpdatePerspective(CCmdUI* pCmdUI);
	afx_msg	void OnLevelOfDetail();
	afx_msg void OnUpdateLevelOfDetail(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrbit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTurntable(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToWindow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateApertureSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQuery(CCmdUI* pCmdUI);
	afx_msg void OnXyPlane();
	afx_msg void OnUpdateXyPlane(CCmdUI* pCmdUI);
	afx_msg void OnXzPlane();
	afx_msg void OnUpdateXzPlane(CCmdUI* pCmdUI);
	afx_msg void OnYzPlane();
	afx_msg void OnUpdateYzPlane(CCmdUI* pCmdUI);
	afx_msg void OnAnnotateModel();
	afx_msg void OnUpdateAnnotateModel(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeFlatshaded();
	afx_msg void OnUpdateToolsRendermodeFlatshaded(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeGouraudshaded();
	afx_msg void OnUpdateToolsRendermodeGouraudshaded(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeHiddenline();
	afx_msg void OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeBRepHiddenline();
	afx_msg void OnUpdateToolsRendermodeBRepHiddenline(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeBRepWireframe();
	afx_msg void OnUpdateToolsRendermodeBRepWireframe(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeFakeHiddenLine();
	afx_msg void OnUpdateToolsRendermodeFakeHiddenLine(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodePhongshaded();
	afx_msg void OnUpdateToolsRendermodePhongshaded(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeWireframe();
	afx_msg void OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeTriangulation();
	afx_msg void OnUpdateToolsRendermodeTriangulation(CCmdUI* pCmdUI);	
	afx_msg void OnToolsRendermodeSilhouette();
	afx_msg void OnUpdateToolsRendermodeSilhouette(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeWireframeWithSilhouette();
	afx_msg void OnUpdateToolsRendermodeWireframeWithSilhouette(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeGoochShaded();
	afx_msg void OnUpdateToolsRendermodeGoochShaded(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsRendermodeWireframeWithLines(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeShadedWithLines();
	afx_msg void OnUpdateToolsRendermodeShadedWithLines(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeLOD1();
	afx_msg void OnToolsRendermodeLOD2();
	afx_msg void OnToolsRendermodeShadedWireframe();
	afx_msg void OnUpdateToolsRendermodeShadedWireframe(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeVertices();
	afx_msg void OnUpdateToolsRendermodeVertices(CCmdUI* pCmdUI);
	afx_msg void OnToolsRendermodeShadedVertices();
	afx_msg void OnUpdateToolsRendermodeShadedVertices(CCmdUI* pCmdUI);
	afx_msg void OnShaded();
	afx_msg void OnUpdateShaded(CCmdUI* pCmdUI);
	afx_msg void OnHiddenLineButton();
	afx_msg void OnUpdateHiddenLineButton(CCmdUI* pCmdUI);
	afx_msg void OnToolsTextFontsArial();
	afx_msg void OnToolsTextFontsCave();
	afx_msg void OnToolsTextFontsRoman();
	afx_msg void OnToolsTextTransformsCharacterpositiononly();
	afx_msg void OnToolsTextTransformsOff();
	afx_msg void OnToolsTextTransformsOn();
	afx_msg void OnCreateCuttingPlane();
	afx_msg void OnUpdateCreateCuttingPlane(CCmdUI* pCmdUI);
	afx_msg void OnModelAnnotate();
	afx_msg void OnUpdateModelAnnotate(CCmdUI* pCmdUI);
	afx_msg void OnRotate();
	afx_msg void OnUpdateRotate(CCmdUI* pCmdUI);
	afx_msg void OnSelectionDeleteselection();
	afx_msg void OnUpdateSelectionDeleteselection(CCmdUI* pCmdUI);
	afx_msg void OnSelectionFocus();
	afx_msg void OnUpdateSelectionFocus(CCmdUI* pCmdUI);
	afx_msg void OnViewAnimate();
	afx_msg void OnUpdateViewAnimate(CCmdUI* pCmdUI);
	afx_msg	void OnUpdateSegmentBrowserButton(CCmdUI* pCmdUI);
	afx_msg void OnToolsVisibilityCuttinglines();
	afx_msg void OnToolsVisibilityHiddenlines();
	afx_msg void OnToolsVisibilityText();
	afx_msg void OnToolsVisibilityImages();
	afx_msg void OnToolsVisibilityGrids();
	afx_msg void OnViewDisplaylists();
	afx_msg void OnUpdateViewDisplaylists(CCmdUI* pCmdUI);
	afx_msg void OnViewLevelofdetail();
	afx_msg void OnUpdateViewLevelofdetail(CCmdUI* pCmdUI);
	afx_msg void OnViewLevelofdetailoptions();
	afx_msg void OnViewPolygonhandednessLeft();
	afx_msg void OnUpdateViewPolygonhandednessLeft(CCmdUI* pCmdUI);
	afx_msg void OnViewPolygonhandednessNone();
	afx_msg void OnUpdateViewPolygonhandednessNone(CCmdUI* pCmdUI);
	afx_msg void OnViewPolygonhandednessRight();
	afx_msg void OnUpdateViewPolygonhandednessRight(CCmdUI* pCmdUI);
	afx_msg void OnFrameRateoptions();
	afx_msg void OnMeasuredistance();
	afx_msg void OnUpdateMeasuredistance(CCmdUI* pCmdUI);
	afx_msg void OnFlushHardwareResources();
	afx_msg void OnUpdateFlushHardwareResources(CCmdUI* pCmdUI);
	afx_msg void OnRelinquishMemory();
	afx_msg void OnUpdateRelinquishMemory(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent); 
 	afx_msg void OnZoomToSelection();
	afx_msg void OnUpdateZoomToSelection(CCmdUI* pCmdUI);
 	afx_msg void OnFacesaslines();
	afx_msg void OnUpdateFacesaslines(CCmdUI* pCmdUI);
	afx_msg void OnDemoanimation();
	afx_msg void OnViewWindowColor();
	afx_msg void OnInstance();
	afx_msg void OnAssembly();
	afx_msg void OnTranslate();
	afx_msg void OnUpdateTranslate(CCmdUI* pCmdUI);
	afx_msg void OnFileLoad();
	afx_msg LRESULT OnNewStreamFileBuffer(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReadingThreadCompletedLight(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT OnKillReadingThread(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReadingThreadCompleted(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadedLoadingCompleted(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWalk();
	afx_msg void OnSweeten();
	afx_msg void OnUpdateSweeten(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWalk(CCmdUI* pCmdUI);
	afx_msg void OnLodLevelLevel1();
	afx_msg void OnUpdateLodLevelLevel1(CCmdUI* pCmdUI);
	afx_msg void OnLodLevelOriginal();
	afx_msg void OnUpdateLodLevelOriginal(CCmdUI* pCmdUI);
	afx_msg void OnLodLevelLevel2();
	afx_msg void OnUpdateLodLevelLevel2(CCmdUI* pCmdUI);
	afx_msg void OnViewcube();
	afx_msg void OnUpdateViewcube(CCmdUI* pCmdUI);
	afx_msg void OnManipulateSmoothtransition();
	afx_msg void OnUpdateManipulateSmoothtransition(CCmdUI* pCmdUI);
	afx_msg void OnEditColor();
	afx_msg void OnEditLights();
	afx_msg void OnIsoPlane();
	afx_msg void OnUpdateIsoPlane(CCmdUI* pCmdUI);
	afx_msg void OnViewCoordinatesystemLefthanded();
	afx_msg void OnViewCoordinatesystemRighthanded();
	afx_msg void OnUpdateViewCoordinatesystemLefthanded(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewCoordinatesystemRighthanded(CCmdUI* pCmdUI);
	afx_msg void OnRedline();
	afx_msg void OnUpdateAnimate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRedline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewWindowcolor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomToExtents(CCmdUI* pCmdUI);
	afx_msg void OnUpdateComputeSampleData(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFramerateoptions(CCmdUI* pCmdUI);	
	afx_msg void OnUpdateFileLoad(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTopolbrowser(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModelBrowser(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditColor(CCmdUI* pCmdUI);
	afx_msg void OnRedlineRectangle();
	afx_msg void OnUpdateRedlineRectangle(CCmdUI* pCmdUI);
	afx_msg void OnRedlineCircle();
	afx_msg void OnUpdateRedlineCircle(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnMarkupCircle();
	afx_msg void OnUpdateMarkupCircle(CCmdUI* pCmdUI);
	afx_msg void OnMarkupFreehand();
	afx_msg void OnUpdateMarkupFreehand(CCmdUI* pCmdUI);
	afx_msg void OnMarkupRectangle();
	afx_msg void OnUpdateMarkupRectangle(CCmdUI* pCmdUI);
	afx_msg void OnZxPlane();
	afx_msg void OnUpdateZxPlane(CCmdUI* pCmdUI);
	afx_msg void OnZyPlane();
	afx_msg void OnUpdateZyPlane(CCmdUI* pCmdUI);
	afx_msg void OnYxPlane();
	afx_msg void OnUpdateYxPlane(CCmdUI* pCmdUI);
	afx_msg void OnIsometric();
	afx_msg void OnSEIsometric();
	afx_msg void OnSWIsometric();
	afx_msg void OnNEIsometric();
	afx_msg void OnNWIsometric();
	afx_msg void OnUpdateIsometric(CCmdUI* pCmdUI);
	afx_msg void OnMarkupAnnotate();
	afx_msg void OnUpdateMarkupAnnotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstantspin(CCmdUI* pCmdUI);
	afx_msg void OnAnnotate();
	afx_msg void OnUpdateAnnotate(CCmdUI* pCmdUI);
	afx_msg void OnViewAntialiasing();
	afx_msg void OnUpdateViewAntialiasing(CCmdUI* pCmdUI);
	afx_msg void OnViewBackplaneculling();
	afx_msg void OnUpdateViewBackplaneculling(CCmdUI* pCmdUI);
	afx_msg void OnToolsVisibilityLines();
	afx_msg void OnUpdateToolsVisibilityLines(CCmdUI* pCmdUI);
	afx_msg void OnToolsVisibilityHoopsEdges();
	afx_msg void OnUpdateToolsVisibilityHoopsEdges(CCmdUI* pCmdUI);
	afx_msg void OnCappingPlanes();
	afx_msg void OnUpdateCappingPlanes(CCmdUI* pCmdUI);
	afx_msg void OnCappingLines();
	afx_msg void OnUpdateCappingLines(CCmdUI* pCmdUI);
	afx_msg void OnViewSoftShadow();
	afx_msg void OnUpdateViewSoftShadow(CCmdUI* pCmdUI);
	afx_msg void OnBehaviorPlay();
	afx_msg void OnUpdateBehaviorPlay(CCmdUI* pCmdUI);
	afx_msg void OnBehaviorRewind();
	afx_msg void OnUpdateBehaviorRewind(CCmdUI* pCmdUI);
 	afx_msg void OnStepBack();
	afx_msg void OnStepForward();
 	afx_msg void OnTextTransforms();
	afx_msg void OnUpdateTextTransforms(CCmdUI* pCmdUI);
	afx_msg void OnBehaviorContinuousPlay();
	afx_msg void OnUpdateBehaviorContinuousPlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStepForward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStepBack(CCmdUI* pCmdUI);
	afx_msg void OnMaterialProperties();
	afx_msg void OnUpdateMaterialProperties(CCmdUI* pCmdUI);
	afx_msg void OnCreateCuttingPlane2();
	afx_msg void OnUpdateCreateCuttingPlane2(CCmdUI* pCmdUI);
	afx_msg void OnCreateCuttingPlane3();
	afx_msg void OnUpdateCreateCuttingPlane3(CCmdUI* pCmdUI);
	afx_msg void OnToolsSelect();
	afx_msg void OnToolsActivatemanipulator();
	afx_msg void OnToolsDeleteEntity();
	afx_msg void OnToolsSetNoteText();
	afx_msg void OnToolsActivatemanipulator2();
	afx_msg void OnToolsDeactivatemanipulator();
	afx_msg void OnToolsDeactivateallmanipulatos();
	afx_msg void OnToolsSnapshot();
	afx_msg void OnToolsMagnifier();
	afx_msg void OnToolsPointer();
	afx_msg void OnToolsSubwindowSyncFromCamera();
	afx_msg void OnToolsSubwindowSynctocamera();
	afx_msg void OnToolsSubwindowFreeze();
	afx_msg void OnToolsSubwindowUnfreeze();
	afx_msg void OnToolsLightsInsertlocallight();
	afx_msg void OnToolsLightsInsertdistantlight();
	afx_msg void OnToolsLightsInsertspotlight();
	afx_msg void OnToolsManipulatorActivateparent();
	afx_msg void OnToolsManipulatorCombineselected();
	afx_msg void OnViewCameraNearLimit();
	afx_msg void OnToolsLightsLightGeometryOff();
	afx_msg void OnToolsLightsLightGeometryOn();
	afx_msg void OnToolsVisibilityMarkersOnly();
	afx_msg void OnUpdateToolsVisibilityMarkersOnly(CCmdUI* pCmdUI);
	afx_msg void OnPolygonSelect();
	afx_msg void OnUpdatePolygonSelect(CCmdUI* pCmdUI);
	afx_msg void OnPolylineSelect();
	afx_msg void OnUpdatePolylineSelect(CCmdUI* pCmdUI);
	afx_msg void OnCreateCreatetwosidedsection();
	afx_msg void OnUpdateCreateCreatetwosidedsection(CCmdUI* pCmdUI);
	afx_msg void OnCreateCreateSlice();
	afx_msg void OnUpdateCreateCreateSlice(CCmdUI* pCmdUI);
	afx_msg void OnCreateCreatethreesidedsection();
	afx_msg void OnUpdateCreateCreatethreesidedsection(CCmdUI* pCmdUI);
	afx_msg void OnSelectionClosestdistance();
	afx_msg void OnEditCopy();
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnHome();
	afx_msg void OnUpdateHome(CCmdUI* pCmdUI);

	afx_msg void OnPreviousLayout();
	afx_msg void OnUpdatePreviousLayout(CCmdUI* pCmdUI);
	afx_msg void OnNextLayout();
	afx_msg void OnUpdateNextLayout(CCmdUI* pCmdUI);

	afx_msg void OnTestCreatebilinearshell();
	afx_msg void OnTestCreatebilinearshell2();
	afx_msg void OnExtraSlot1();
	afx_msg void OnExtraSlot2();
	afx_msg void OnExtraSlot3();
	afx_msg void OnExtraSlot4();
	afx_msg void OnExtraSlot5();
	afx_msg void OnDynamicExtraSlot1();
	afx_msg void OnDynamicExtraSlot2();
	afx_msg void OnDynamicExtraSlot3();
	afx_msg void OnDynamicExtraSlot4();
	afx_msg void OnDynamicExtraSlot5();
	afx_msg void OnToolsLodgeneration();

	afx_msg void OnVerticalCAEToggleLegend();
	afx_msg void OnVerticalCAEMapData();
	afx_msg void OnVerticalCAEColorIndex();
	afx_msg void OnVerticalCAEColorInterpolation();
	afx_msg void OnVerticalCAEIsolines();
	afx_msg void OnVerticalCAEQuadInterpolation();

	afx_msg void OnUpdateVerticalCAEToggleLegend(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVerticalCAEColorIndex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVerticalCAEColorInterpolation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVerticalCAEIsolines(CCmdUI* pCmdUI);

	afx_msg void OnVerticalCMMToggleCollision();
	afx_msg void OnUpdateVerticalCMMToggleCollision(CCmdUI* pCmdUI);
	afx_msg void OnVerticalCMMToggleVisibility();
	afx_msg void OnUpdateVerticalCMMToggleVisibility(CCmdUI* pCmdUI);
	afx_msg void OnVerticalCMMHidePositions();
	afx_msg void OnUpdateVerticalCMMHidePositions(CCmdUI* pCmdUI);
	afx_msg void OnColorizeScan();
	afx_msg void OnUpdateColorizeScan(CCmdUI* pCmdUI);
 	afx_msg void OnToggleSplat();
	afx_msg void OnUpdateToggleSplat(CCmdUI* pCmdUI);
	afx_msg void OnToggleSplatSymbol();
	afx_msg void OnUpdateToggleSplatSymbol(CCmdUI* pCmdUI);
	//}}AFX_MSG
#ifdef ACIS
	afx_msg void OnUpdateCreateTorus(CCmdUI* pCmdUI);
#endif
#ifdef HOOPS_ONLY
	afx_msg void OnCreateCone();
	afx_msg void OnUpdateCreateCone(CCmdUI* pCmdUI);
	afx_msg void OnCreateCylinder();
	afx_msg void OnUpdateCreateCylinder(CCmdUI* pCmdUI);
	afx_msg void OnCreateSphere();
	afx_msg void OnUpdateCreateSphere(CCmdUI* pCmdUI);
	afx_msg void OnCreateNurbscurve();
	afx_msg void OnUpdateCreateNurbscurve(CCmdUI* pCmdUI);
 	afx_msg void OnClashDetection();
	afx_msg void OnUpdateClashDetection(CCmdUI* pCmdUI);
	afx_msg void OnViewAnimateObject();
	afx_msg void OnUpdateViewAnimateObject(CCmdUI* pCmdUI);
	afx_msg void OnSegmentSelectLevel();
	afx_msg void OnUpdateSegmentSelectLevel(CCmdUI* pCmdUI);
	afx_msg void OnEntitySelectLevel();
	afx_msg void OnUpdateEntitySelectLevel(CCmdUI* pCmdUI);
	afx_msg void OnSubentitySelectLevel();
	afx_msg void OnUpdateSubentitySelectLevel(CCmdUI* pCmdUI);
	afx_msg void OnSubentityFaces();
	afx_msg void OnSubentityEdges();
	afx_msg void OnSubentityVertices();
#else
 	afx_msg void OnUpdateSubtract(CCmdUI* pCmdUI);
 	afx_msg void OnUpdateUnion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIntersect(CCmdUI* pCmdUI);
	afx_msg void OnFace();
	afx_msg void OnUpdateFace(CCmdUI* pCmdUI);
	afx_msg void OnEdge();
	afx_msg void OnUpdateEdge(CCmdUI* pCmdUI);
	afx_msg void OnBody();
	afx_msg void OnUpdateBody(CCmdUI* pCmdUI);
	afx_msg void OnOptimize();
	afx_msg void OnUpdateOptimize(CCmdUI* pCmdUI);

#endif // HOOPS_ONLY
	DECLARE_MESSAGE_MAP()

	bool SetColor( HC_KEY key, float r, float g, float b);
	void Color(HC_KEY key, char* seg_path, HC_KEY include_key, HC_KEY includer_key, 
				float r, float g, float b, bool recurse = false, bool emit_message = true);

	void load(const char * filename);

	void SetCoordinateSystemHandedness(HandednessMode right_or_left, bool emit_message = true);
	void SetWindowColor(COLORREF new_top_color, COLORREF new_bottom_color, bool emit_message = true);
	void SetPolygonHandedness(ModelHandedness new_handedness);
	void SetShadowColor(COLORREF new_color);
	void SetupOutputOptions(HOutputHandlerOptions & options, /*HOutputHandlerStyle*/ int style);

public:

#ifdef HOOPS_ONLY
	afx_msg void OnBooleantypeIntersection();
	afx_msg void OnBooleantypeSubtract();
	afx_msg void OnBooleantypeUnion();
#endif //HOOPS_ONLY

	afx_msg void OnMaterialSelector();
	afx_msg void OnClashdetectionStartclashcalculation();
	afx_msg void OnToolsClashdetectionClashbrowser();
	afx_msg void OnToolsShadereditor();

    void InitMaterialLibrary();
	bool m_bMaterialLibraryInitialized;

};


 
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOLIDHOOPSVIEW_H__FCA603FB_1694_11D2_B736_00805F85736F__INCLUDED_)
