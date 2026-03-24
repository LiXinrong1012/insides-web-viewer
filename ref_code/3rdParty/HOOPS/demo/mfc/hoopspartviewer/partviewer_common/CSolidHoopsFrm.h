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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsFrm.h,v 1.43 2010-06-07 08:46:38 ashish Exp $
//

// CSolidHoopsFrm.h : interface of the CSolidHoopsFrame class, derived from CHoopsFrame
// Adds application specific frame creation  (to install the app toolbars, etc...)

#pragma once

#include "CHoopsFrm.h"
#include "afxext.h"

class CDockingDialogBar;
class CSolidHoopsView;
class CSolidHoopsFrame;
class HErrorNode;

class CBehaviorToolBar : public CToolBar 
{
public:
	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_wndBhvSlider;

	CSolidHoopsFrame *m_frame;
	DECLARE_MESSAGE_MAP()

};

class CCMMToolBar : public CToolBar 
{
public:
	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_wndBhvSlider;
	CSolidHoopsFrame *m_frame;
	DECLARE_MESSAGE_MAP()
};

class CPointCloudToolBar : public CToolBar 
{
public:

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_wndBhvSlider;
	CSliderCtrl m_wndBhvSlider2;
 
	CHoopsFrame * m_frame;

	DECLARE_MESSAGE_MAP()
};

class CSolidHoopsFrame : public CHoopsFrame
{
	DECLARE_DYNAMIC(CSolidHoopsFrame)
	DECLARE_MESSAGE_MAP()
public:
	void ShowSegmentBrowserDialogBar(BOOL bShow = TRUE);
	void ShowCMMDisplayDialogBar(BOOL bShow = TRUE);
	void ShowModelBrowserDialogBar(BOOL bShow = TRUE);
	void ShowErrorBrowserDialogBar(BOOL bShow = TRUE);
	void ShowTopologyBrowserDialogBar(BOOL bShow = TRUE);
	void ShowKeyframeEditorDialogBar(BOOL bShow = TRUE);
	void ShowClashBrowserDialogBar(BOOL bShow = TRUE);
	void ShowClashSelectDialogBar(BOOL bShow = TRUE);
 	void ShowInterOpPartBrowserDialogBar(BOOL bShow = TRUE);
 	void OnActivateView(BOOL bActivate, CSolidHoopsView* pActivateView, CSolidHoopsView* pDeactiveView);
	void ViewDestoryed(CSolidHoopsView* pDestroyedView );
	CStatusBar*	GetStatusBar() {return &m_wndStatusBar;};
	CBehaviorToolBar * GetBhvToolbar() { return &m_wndToolBarBehavior; }

	/* TODO: According to MFC, this should be protected, but we're calling the constructor
	   directly in CSolidHoopsApp.cpp... */
	CSolidHoopsFrame();           // protected constructor used by dynamic creation

	/* TODO: These should be protected, but CSegmentBrowserDlg::OnTopologyBrowserSwitch is 
	   calling these directly.  */
	afx_msg void OnSegmentbrowser();
	afx_msg void OnTopolbrowser();
	afx_msg void OnInterOpPartBrowser();

protected:
	static void ErrorCallback(HErrorNode *node, void *data);

	UINT GetMainToolbarID();
	CToolBar m_wndMainToolBar;
	CToolBar m_wndToolBarTools;
	CToolBar m_wndToolBarMarkupText;
	CToolBar m_wndToolBarStandardViews;
	CToolBar m_wndToolBarCAE;
	CToolBar m_wndToolBarUndo;
	CToolBar m_wndToolBarLayoutLoad;
	CCMMToolBar m_wndToolBarCMM;
	CBehaviorToolBar m_wndToolBarBehavior;
	CPointCloudToolBar m_wndPointCloudToolBar;

	CDockingDialogBar * m_pDlgBarSegmentBrowser;	// segment browser
	CDockingDialogBar * m_pDlgBarModelBrowser;		// model browser
	CDockingDialogBar * m_pDlgBarErrorBrowser;		// error browser
	CDockingDialogBar * m_pDlgBarTopologyBrowser;	// topology browser
	CDockingDialogBar * m_pDlgBarKeyframeEditor;	// keyframe editor
	CDockingDialogBar * m_pDlgBarClashBrowser;	// keyframe editor
	CDockingDialogBar * m_pDlgBarClashSelect;	// keyframe editor
	CDockingDialogBar * m_pDlgBarCMMDisplay;
	CDockingDialogBar * m_pDlgBarInterOpPartBrowser;	// assembly structure browser

	CFont gSmallFont;

	//{{AFX_VIRTUAL(CSolidHoopsFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	virtual ~CSolidHoopsFrame();

	//{{AFX_MSG(CSolidHoopsFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnViewToolbarMarkupText();
	afx_msg void OnUpdateViewToolbarMarkupText(CCmdUI* pCmdUI);

	afx_msg void OnViewToolbarStatus();
	afx_msg void OnUpdateViewToolbarStatus(CCmdUI* pCmdUI);

	afx_msg void OnViewToolbarPointCloud();
	afx_msg void OnUpdateViewToolbarPointCloud(CCmdUI* pCmdUI);

	afx_msg void OnViewToolbarStandardViews();
	afx_msg void OnUpdateViewToolbarStandardViews(CCmdUI* pCmdUI);

	afx_msg void OnViewToolbarTools();
	afx_msg void OnUpdateViewToolbarTools(CCmdUI* pCmdUI);

	afx_msg void OnViewToolbarUndo();
	afx_msg void OnUpdateViewToolbarUndo(CCmdUI* pCmdUI);

	afx_msg void OnViewToolbarLayoutLoad();
	afx_msg void OnUpdateViewToolbarLayoutLoad(CCmdUI* pCmdUI);

	afx_msg void OnCMMDisplay();
	afx_msg void OnUpdateCMMDisplay(CCmdUI* pCmdUI);

	afx_msg void OnModelbrowser();
	afx_msg void OnUpdateModelbrowser(CCmdUI* pCmdUI);

	afx_msg void OnErrorbrowser();
	afx_msg void OnUpdateErrorbrowser(CCmdUI* pCmdUI);
	
	afx_msg void OnToolsKeyframeeditor();
	afx_msg void OnUpdateToolsKeyframeeditor(CCmdUI* pCmdUI);

	afx_msg void OnToolsClashBrowser();
	afx_msg void OnUpdateToolsClashBrowser(CCmdUI* pCmdUI);

	afx_msg void OnViewToolbarAnimation();
	afx_msg void OnUpdateViewToolbarAnimation(CCmdUI* pCmdUI);

	afx_msg void OnUpdateInterOpPartBrowser(CCmdUI* pCmdUI);

	afx_msg void OnUpdateSegmentbrowser(CCmdUI* pCmdUI);
	virtual void OnInitMenu(CMenu *menu);
	virtual void OnExitMenuLoop(BOOL b);
#ifdef HOOPS_ONLY
	CToolBar m_wndToolBarHoopsOnly;
	afx_msg void OnViewToolbarHoopsOnly();
	afx_msg void OnUpdateViewToolbarHoopsOnly(CCmdUI* pCmdUI);
#endif
	afx_msg void OnViewToolbarCAE();
	afx_msg void OnUpdateViewToolbarCAE(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarCMM();
	afx_msg void OnUpdateViewToolbarCMM(CCmdUI* pCmdUI);
	afx_msg void OnToolbarCMM();
	afx_msg void OnUpdateToolbarCMM(CCmdUI *pCmdUI);
	afx_msg void OnToolbarCAE();
	afx_msg void OnUpdateToolbarCAE(CCmdUI *pCmdUI);
	//}}AFX_MSG

private:

	void ShowDockingDialogBar(BOOL bShow, CDockingDialogBar*& pDialogBar, CDialog * pDialog, CString csTitle, UINT resourceId, int dockingstyle, int dockingposition = 0);
	void KillDockingDialogBar( CDockingDialogBar*& pDialogBar );
	void CreateToolBars();
	void DocToolBars();
	void CreateStandardViewsToolsToolBar(bool visible);
	void CreateHoopsOnlyToolsToolBar(bool visible);
	void CreateMarkupTextToolBar(bool visible);
	void CreateMainToolBar(bool visible);
	void CreateCMMToolBar(bool visible);
	void CreateCAEToolBar(bool visible);
	void CreateStatusBar(bool visible);
	void CreateUndoToolBar(bool visible);
	void CreateBehaviorToolBar(bool visible);
	void CreateToolsToolBar(bool visible);
	void CreatePointCloudToolBar(bool visible);
	void CreateLayOutLoadToolBar(bool visible);
};
