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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsFrm.cpp,v 1.87 2010-12-13 20:25:22 nathan Exp $
//

// CSolidHoopsFrm.cpp : implementation file
//

#include "StdAfx.h"
#include "Resource.h"
#include "HSInclude.h"

#include "CSolidHoopsFrm.h"
#include "CSolidHoopsView.h"
#include "CSolidHoopsDoc.h"
#include "HSolidView.h"
#include "HSolidModel.h"

#ifndef HOOPS_ONLY
#include "CBinaryFileToolkit.h"
#include "PlainTopolBrowserDlg.h"
#endif // HOOPS_ONLY

#ifdef ACIS
#include "ASTopolBrowserDlg.h"
#endif // ACIS



#ifdef INTEROP
#include "InterOpPartBrowserDlg.h"
#endif // INTEROP

#include "HUIUtilityMFC.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMyHoopsFrm

IMPLEMENT_DYNAMIC(CSolidHoopsFrame, CHoopsFrame)

CSolidHoopsFrame::CSolidHoopsFrame()
{
	m_pDlgBarSegmentBrowser = 0;
	m_pDlgBarModelBrowser = 0;
	m_pDlgBarErrorBrowser = 0;
	m_pDlgBarTopologyBrowser = 0;
	m_pDlgBarKeyframeEditor = 0;
	m_pDlgBarClashBrowser = 0;
	m_pDlgBarClashSelect = 0;
	m_pDlgBarCMMDisplay = 0;
	m_pDlgBarInterOpPartBrowser = 0;
}

CSolidHoopsFrame::~CSolidHoopsFrame()
{
	H_SAFE_DELETE(m_pDlgBarSegmentBrowser);
	H_SAFE_DELETE(m_pDlgBarModelBrowser);
	H_SAFE_DELETE(m_pDlgBarErrorBrowser);
	H_SAFE_DELETE(m_pDlgBarTopologyBrowser);
	H_SAFE_DELETE(m_pDlgBarKeyframeEditor);
	H_SAFE_DELETE(m_pDlgBarClashBrowser);
	H_SAFE_DELETE(m_pDlgBarClashSelect);
	H_SAFE_DELETE(m_pDlgBarCMMDisplay);
	H_SAFE_DELETE(m_pDlgBarInterOpPartBrowser);
}


BEGIN_MESSAGE_MAP(CSolidHoopsFrame, CHoopsFrame)
	//{{AFX_MSG_MAP(CSolidHoopsFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TOOLBAR_STATUS_BAR, OnViewToolbarStatus)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_STATUS_BAR, OnUpdateViewToolbarStatus)

	ON_COMMAND(ID_TOOLBAR_POINT_CLOUD, OnViewToolbarPointCloud)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_POINT_CLOUD, OnUpdateViewToolbarPointCloud)

	ON_COMMAND(ID_VIEW_TOOLBAR_MARKUP_TEXT, OnViewToolbarMarkupText)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_MARKUP_TEXT, OnUpdateViewToolbarMarkupText)
	ON_COMMAND(ID_VIEW_TOOLBAR_STANDARD_VIEWS, OnViewToolbarStandardViews)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_STANDARD_VIEWS, OnUpdateViewToolbarStandardViews)
	ON_COMMAND(ID_VIEW_TOOLBAR_TOOLS, OnViewToolbarTools)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_TOOLS, OnUpdateViewToolbarTools)
	ON_COMMAND(ID_SEGMENTBROWSER, OnSegmentbrowser)
	ON_COMMAND(ID_CMM_DISPLAY, OnCMMDisplay)
	ON_COMMAND(ID_MODELBROWSER, OnModelbrowser)
	ON_COMMAND(ID_ERRORBROWSER, OnErrorbrowser)
	ON_UPDATE_COMMAND_UI(ID_SEGMENTBROWSER, OnUpdateSegmentbrowser)
	ON_UPDATE_COMMAND_UI(ID_CMM_DISPLAY, OnUpdateCMMDisplay)
	ON_UPDATE_COMMAND_UI(ID_MODELBROWSER, OnUpdateModelbrowser)
	ON_UPDATE_COMMAND_UI(ID_ERRORBROWSER, OnUpdateErrorbrowser)
	ON_COMMAND(ID_TOPOLBROWSER, OnTopolbrowser)
	ON_COMMAND(ID_TOOLS_KEYFRAMEEDITOR, OnToolsKeyframeeditor)
	ON_COMMAND(ID_TOOLS_CLASHBROWSER, OnToolsClashBrowser)
	ON_COMMAND(ID_BUTTON_CMM_TOGGLE_DISPLAY, OnCMMDisplay)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CMM_TOGGLE_DISPLAY, OnUpdateCMMDisplay)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_KEYFRAMEEDITOR, OnUpdateToolsKeyframeeditor)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CLASHBROWSER, OnUpdateToolsClashBrowser)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CMM_TOGGLE_DISPLAY, OnUpdateCMMDisplay)
	ON_WM_MDIACTIVATE()
	ON_WM_MDIACTIVATE()
	ON_COMMAND(ID_VIEW_TOOLBAR_ANIMATION, OnViewToolbarAnimation)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_ANIMATION, OnUpdateViewToolbarAnimation)
	ON_WM_INITMENU()
	ON_WM_EXITMENULOOP()

	//}}AFX_MSG_MAP
#ifdef HOOPS_ONLY
	ON_COMMAND(ID_VIEW_TOOLBAR_HOOPS_ONLY, OnViewToolbarHoopsOnly)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_HOOPS_ONLY, OnUpdateViewToolbarHoopsOnly)
#endif
	ON_COMMAND(ID_TOOLBAR_CAE, CSolidHoopsFrame::OnToolbarCAE)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_CAE, CSolidHoopsFrame::OnUpdateToolbarCAE)
	ON_COMMAND(ID_TOOLBAR_CMM, CSolidHoopsFrame::OnToolbarCMM)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_CMM, CSolidHoopsFrame::OnUpdateToolbarCMM)

	ON_COMMAND(ID_IOPPARTBROWSER, OnInterOpPartBrowser)
	ON_UPDATE_COMMAND_UI(ID_IOPPARTBROWSER, OnUpdateInterOpPartBrowser)

END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CPointCloudToolBar, CToolBar)
	//{{AFX_MSG_MAP(CCMMToolBar)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPointCloudToolBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(nSBCode != SB_THUMBPOSITION && nSBCode != SB_THUMBTRACK){
		return;
	};
	

	CSolidHoopsView * pView = 0;

	if(m_frame && m_frame->GetActiveFrame() && m_frame->GetActiveFrame()->GetActiveView()){
		pView = (CSolidHoopsView *)(m_frame->GetActiveFrame()->GetActiveView());
	}
	else {
		return;
	}

	if (m_wndBhvSlider2.m_hWnd == pScrollBar->m_hWnd)
	{
		pView->GetHoopsView()->SetSplatSize(nPos);
	}
	else
	{
		if(nPos > 0){ 
			HC_Open_Segment_By_Key(pView->GetHoopsView()->GetSceneKey());
				HC_Set_Rendering_Options(H_FORMAT_TEXT("vertex decimation = %f", ((float)nPos/100.0) ));
			HC_Close_Segment();
		}
	}

	HC_Control_Update_By_Key(pView->GetHoopsView()->GetViewKey(), "redraw everything");

	pView->GetHoopsView()->ForceUpdate();
}

BEGIN_MESSAGE_MAP(CCMMToolBar, CToolBar)
	//{{AFX_MSG_MAP(CCMMToolBar)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCMMToolBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSolidHoopsView * pView = 0;

	if(m_frame && m_frame->GetActiveFrame() && m_frame->GetActiveFrame()->GetActiveView()){
		pView = (CSolidHoopsView *)(m_frame->GetActiveFrame()->GetActiveView());
	}
	else {
		return;
	}

	if (pView && (streq (pView->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ))){
		switch(nSBCode)
		{
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
		case SB_RIGHT:
		case SB_LEFT:
		case SB_PAGELEFT:
		case SB_PAGERIGHT:{
			pView->OnCMMHScroll((float)nPos);
		}break;

		default:break;
		}
	}
}

BEGIN_MESSAGE_MAP(CBehaviorToolBar, CToolBar)
	//{{AFX_MSG_MAP(CBehaviorToolBar)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CBehaviorToolBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CMDIChildWnd *pChild = 
             (CMDIChildWnd *) m_frame->GetActiveFrame();

 	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();
	if (view && (streq (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ))) 
		view->OnBehaviorHScroll(nSBCode, nPos, pScrollBar);
}

#include "HErrorManager.h"
#include "CErrorBrowserDlg.h"
#include "ErrorDlg.h"
#include "HObjects.h"
#include "HEventManager.h"
/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsFrame message handlers
void CSolidHoopsFrame::OnInitMenu(CMenu *menu)
{
 	
	CMDIChildWnd *pChildFrm = MDIGetActive();
	if (pChildFrm)
	{
		CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
		if(pActiveView && (strcmp (pActiveView->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 )) 		{
			pActiveView->GetHoopsView()->GetConstantFrameRateObject()->SetDisableIncreaseTemp(true);
		}
	}
 
}

void CSolidHoopsFrame::OnExitMenuLoop(BOOL b)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	if (pChildFrm)
	{
		CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
		if(pActiveView && (strcmp (pActiveView->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 )) 
		{
			pActiveView->GetHoopsView()->GetConstantFrameRateObject()->SetDisableIncreaseTemp(false);
		}
	}
}


void CSolidHoopsFrame::ErrorCallback(HErrorNode *node, void *data)
{
	bool hasQuit = false;
	CSolidHoopsFrame *frame = (CSolidHoopsFrame *)data;
//	if( !frame->m_pDlgBarErrorBrowser || !frame->m_pDlgBarErrorBrowser->IsWindowVisible() )
//		frame->OnErrorbrowser();
		
	CMDIChildWnd *pChildFrm = frame->MDIGetActive();
	CSolidHoopsView *pActiveView = 0;
	if (pChildFrm)
	{	
		pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();

	if (pActiveView->GetErrorBrowserDialog() && frame->m_pDlgBarErrorBrowser)
	{
 		((CErrorBrowserDlg *)pActiveView->GetErrorBrowserDialog())->RefreshAll();
	}

//	((CErrorBrowserDlg *)pActiveView->GetErrorBrowserDialog())->ShowError(node);
	}
	if (HErrorManager::GetShowDialog() && !hasQuit)
	{
		if (!pActiveView)
		{
			CErrorDlg my_dlg(frame, node);
			my_dlg.DoModal();			
			hasQuit = my_dlg.m_HasQuit;
		}

		else
		{
 			CErrorDlg my_dlg(pActiveView, node);
			my_dlg.DoModal();
			hasQuit = my_dlg.m_HasQuit;
		}
		if(hasQuit){
			HErrorManager::Cleanup();
			PostQuitMessage(1);
		}
	}
}

int CSolidHoopsFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHoopsFrame::OnCreate(lpCreateStruct) == -1)
		return -1;

	CreateToolBars();
	DocToolBars();

	HErrorManager::SetErrorCallback(ErrorCallback, this);
	CClientDC DC(GetDesktopWindow());
    long logical_pixels = DC.GetDeviceCaps(LOGPIXELSX);
    if(logical_pixels <100){
        gSmallFont.CreatePointFont(67,_T("DEFAULT"),NULL);  
    } else {   
        gSmallFont.CreatePointFont(50,_T("DEFAULT"),NULL); 
    }   

	return 0;
}

void CSolidHoopsFrame::DocToolBars()
{
	DockControlBar(&m_wndMainToolBar);
	DockControlBarLeftOf(&m_wndToolBarTools, &m_wndMainToolBar);
	DockControlBarLeftOf(&m_wndToolBarUndo, &m_wndMainToolBar);

	DockControlBar(&m_wndToolBarBehavior);
	DockControlBarLeftOf(&m_wndToolBarStandardViews, &m_wndToolBarBehavior);
	DockControlBarLeftOf(&m_wndToolBarMarkupText, &m_wndToolBarBehavior);
	DockControlBarLeftOf(&m_wndToolBarLayoutLoad, &m_wndToolBarStandardViews);

#ifdef HOOPS_ONLY
	DockControlBarLeftOf(&m_wndToolBarHoopsOnly, &m_wndToolBarBehavior);
#endif

	DockControlBarLeftOf(&m_wndToolBarCMM, &m_wndToolBarStandardViews);
	DockControlBarLeftOf(&m_wndPointCloudToolBar, &m_wndToolBarStandardViews);
	DockControlBarLeftOf(&m_wndToolBarCAE, &m_wndToolBarStandardViews);
}

void CSolidHoopsFrame::CreateToolBars()
{
	INITCOMMONCONTROLSEX InitCtrlEx;
	// Ensure that the common control DLL is loaded. 
	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC  = ICC_BAR_CLASSES | ICC_COOL_CLASSES | ICC_PROGRESS_CLASS | ICC_STANDARD_CLASSES | ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);

	EnableDocking(CBRS_ALIGN_ANY);
	CreateMainToolBar(true);
	CreateUndoToolBar(true);
	CreateBehaviorToolBar(true);
	CreateToolsToolBar(true);
	CreateHoopsOnlyToolsToolBar(true);
	CreateStandardViewsToolsToolBar(true);
	CreateMarkupTextToolBar(true);
	CreatePointCloudToolBar(false);
	CreateCMMToolBar(false);
	CreateCAEToolBar(false);
	CreateStatusBar(false);
	CreateLayOutLoadToolBar(true);
}

UINT CSolidHoopsFrame::GetMainToolbarID()
{
#ifdef ACIS
	UINT toolbar_id = IDR_MAINFRAME1;
#endif // ACIS
#ifdef HOOPS_ONLY
	UINT toolbar_id = IDR_MAINFRAME3;
#endif // HOOPS_ONLY
	return toolbar_id;
}

void CSolidHoopsFrame::CreateStatusBar(bool visible)
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		abort();      // fail to create
	}
	ShowControlBar(&m_wndStatusBar, visible, FALSE);
}

void CSolidHoopsFrame::CreateUndoToolBar(bool visible)
{
	if (!m_wndToolBarUndo.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarUndo.LoadToolBar(IDR_TOOLBAR_UNDO))
	{
		TRACE0("Failed to create toolbar: Undo\n");
		abort();      // fail to create
	}
	m_wndToolBarUndo.SetWindowText(_T("Undo Control"));
	m_wndToolBarUndo.SetBarStyle(m_wndMainToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarUndo.EnableDocking(CBRS_ALIGN_ANY);
#ifdef HOOPS_QA
	m_wndToolBarUndo.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndToolBarUndo, visible, FALSE);
}

void CSolidHoopsFrame::CreateLayOutLoadToolBar(bool visible)
{
	if (!m_wndToolBarLayoutLoad.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarLayoutLoad.LoadToolBar(IDR_TOOLBAR_LAYOUTS))
	{
		TRACE0("Failed to create toolbar: LayoutLoad\n");
		abort();      // fail to create
	}
	m_wndToolBarLayoutLoad.SetWindowText(_T("Layout Control"));
	m_wndToolBarLayoutLoad.SetBarStyle(m_wndMainToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarLayoutLoad.EnableDocking(CBRS_ALIGN_ANY);
#ifdef HOOPS_QA
	m_wndToolBarLayoutLoad.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndToolBarLayoutLoad, visible, FALSE);
}

void CSolidHoopsFrame::CreateMainToolBar(bool visible)
{

	if (!m_wndMainToolBar.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) 
		|| !m_wndMainToolBar.LoadToolBar(GetMainToolbarID()))
	{
		TRACE0("Failed to create toolbar\n");
		abort();      // fail to create
	}
	m_wndMainToolBar.SetWindowText(_T("Standard"));
	m_wndMainToolBar.SetBarStyle(m_wndMainToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndMainToolBar.EnableDocking(CBRS_ALIGN_ANY);
#ifdef HOOPS_QA
	m_wndMainToolBar.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndMainToolBar, visible, FALSE);
}


void CSolidHoopsFrame::CreateMarkupTextToolBar(bool visible)
{
	if (!m_wndToolBarMarkupText.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarMarkupText.LoadToolBar(IDR_TOOLBAR_MARKUP_TEXT))
	{
		TRACE0("Failed to create toolbar: Markup-Text\n");
		abort();      // fail to create
	}
	m_wndToolBarMarkupText.SetWindowText(_T("Markup and Text"));
	m_wndToolBarMarkupText.SetBarStyle(m_wndMainToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarMarkupText.EnableDocking(CBRS_ALIGN_ANY);

#ifdef HOOPS_QA
	m_wndToolBarMarkupText.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndToolBarMarkupText, visible, FALSE);
}

void CSolidHoopsFrame::CreateBehaviorToolBar(bool visible)
{
	if (!m_wndToolBarBehavior.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarBehavior.LoadToolBar(IDR_TOOLBAR_BEHAVIOR))
	{
		TRACE0("Failed to create toolbar: Behavior\n");
		abort();      // fail to create
	}
	m_wndToolBarBehavior.SetWindowText(_T("Behavior Control"));
	m_wndToolBarBehavior.SetBarStyle(m_wndMainToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarBehavior.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
    int index = 0;
    while(m_wndToolBarBehavior.GetItemID(index) != ID_PLACEHOLDER_BHV_SLIDER) index++;

 	RECT rect;
    m_wndToolBarBehavior.SetButtonInfo(index, ID_PLACEHOLDER_BHV_SLIDER, TBBS_SEPARATOR, 100);
    m_wndToolBarBehavior.GetItemRect(index, &rect);
	rect.right += 1;

    // then .Create the combo box and show it
    if (!m_wndToolBarBehavior.m_wndBhvSlider.Create(WS_CHILD|WS_VISIBLE | TBS_HORZ,      
                                        rect, &m_wndToolBarBehavior, ID_BHV_SLIDER))
         abort();

	
	m_wndToolBarBehavior.m_frame = this;
	m_wndToolBarBehavior.m_wndBhvSlider.SetPageSize(20);
    m_wndToolBarBehavior.m_wndBhvSlider.ShowWindow(SW_SHOW);

    m_wndToolBarBehavior.SetButtonInfo(index, ID_PLACEHOLDER_BHV_SLIDER2, TBBS_SEPARATOR, 100);
    m_wndToolBarBehavior.GetItemRect(index, &rect);
#ifdef HOOPS_QA
	m_wndToolBarBehavior.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndToolBarBehavior, visible, FALSE);
}

void CSolidHoopsFrame::CreateCMMToolBar(bool visible)
{
	if (!m_wndToolBarCMM.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarCMM.LoadToolBar(IDR_TOOLBAR_CMM))
	{
		TRACE0("Failed to create toolbar: Hoops Only\n");
		abort();      // fail to create
	}
	m_wndToolBarCMM.SetWindowText(_T("CMM Tools"));
	m_wndToolBarCMM.SetBarStyle(m_wndToolBarCMM.GetBarStyle() |	CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarCMM.EnableDocking(CBRS_ALIGN_ANY);
    int index = 0;
    while(m_wndToolBarCMM.GetItemID(index) != ID_PLACEHOLDER_CMM_SLIDER) ++index;

	RECT rect;
    m_wndToolBarCMM.GetItemRect(index, &rect);
	rect.left += 8;
	rect.right = rect.left + 100;
    m_wndToolBarCMM.m_wndBhvSlider.Create(WS_CHILD|WS_VISIBLE | TBS_HORZ, rect, &m_wndToolBarCMM, ID_PLACEHOLDER_CMM_SLIDER);
	m_wndToolBarCMM.m_frame = this;
	m_wndToolBarCMM.SetButtonInfo(index, ID_PLACEHOLDER_CMM_SLIDER, TBBS_SEPARATOR, rect.right - rect.left + 8);
	ShowControlBar(&m_wndToolBarCMM, visible, FALSE);
}

void CSolidHoopsFrame::CreateCAEToolBar(bool visible)
{
	if (!m_wndToolBarCAE.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarCAE.LoadToolBar(IDR_TOOLBAR_CAE))
	{
		TRACE0("Failed to create toolbar: Hoops Only\n");
		abort();      // fail to create
	}

	m_wndToolBarCAE.SetWindowText(_T("CAE Tools"));
	m_wndToolBarCAE.SetBarStyle(m_wndToolBarCAE.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarCAE.EnableDocking(CBRS_ALIGN_ANY);
	ShowControlBar(&m_wndToolBarCAE, visible, FALSE);
}

void CSolidHoopsFrame::CreatePointCloudToolBar(bool visible)
{
	if (!m_wndPointCloudToolBar.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndPointCloudToolBar.LoadToolBar(IDR_POINT_CLOUD_TOOLBAR))
	{
		TRACE0("Failed to create m_wndLaserToolBar\n");
		abort();      // fail to create
	}

    int index = 0;
    while(m_wndPointCloudToolBar.GetItemID(index) != ID_POINT_CLOUD_SLIDER_PLACE_HOLDER) ++index;
	RECT rect;
	m_wndPointCloudToolBar.GetItemRect(index, &rect);
	rect.left -= 4;
	rect.right = rect.left + 100;
    m_wndPointCloudToolBar.m_wndBhvSlider.Create(WS_CHILD|WS_VISIBLE|TBS_HORZ, rect, &m_wndPointCloudToolBar, ID_POINT_CLOUD_SLIDER_PLACE_HOLDER);
	m_wndPointCloudToolBar.m_wndBhvSlider.SetRange(1, 100);
	m_wndPointCloudToolBar.m_wndBhvSlider.SetPos(100);
	m_wndPointCloudToolBar.SetButtonInfo(index, ID_POINT_CLOUD_SLIDER_PLACE_HOLDER, TBBS_SEPARATOR, rect.right - rect.left + 8);
	m_wndPointCloudToolBar.m_frame = this;


    int index2 = 0;
    while(m_wndPointCloudToolBar.GetItemID(index2) != ID_POINT_CLOUD_SLIDER2_PLACE_HOLDER) ++index2;

	m_wndPointCloudToolBar.GetItemRect(index2, &rect);
	rect.left -= 4;
	rect.right = rect.left + 100;
    m_wndPointCloudToolBar.m_wndBhvSlider2.Create(WS_CHILD|WS_VISIBLE|TBS_HORZ, rect, &m_wndPointCloudToolBar, ID_POINT_CLOUD_SLIDER_PLACE_HOLDER);
	m_wndPointCloudToolBar.m_wndBhvSlider2.SetRange(1, 100);
	m_wndPointCloudToolBar.m_wndBhvSlider2.SetPos(1);

	m_wndPointCloudToolBar.SetButtonInfo(index2, ID_POINT_CLOUD_SLIDER2_PLACE_HOLDER, TBBS_SEPARATOR, rect.right - rect.left + 8);
	m_wndPointCloudToolBar.m_frame = this;





	m_wndPointCloudToolBar.EnableDocking(CBRS_ALIGN_ANY);
	ShowControlBar(&m_wndPointCloudToolBar, visible, FALSE);
}


void CSolidHoopsFrame::CreateToolsToolBar(bool visible)
{
	if (!m_wndToolBarTools.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarTools.LoadToolBar(IDR_TOOLBAR_TOOLS))
	{
		TRACE0("Failed to create toolbar: Tools\n");
		abort();      // fail to create
	}
	m_wndToolBarTools.SetWindowText(_T("Tools"));
	m_wndToolBarTools.SetBarStyle(m_wndMainToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarTools.EnableDocking(CBRS_ALIGN_ANY);
#ifdef HOOPS_QA
	m_wndToolBarTools.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndToolBarTools, visible, FALSE);
}

void CSolidHoopsFrame::CreateHoopsOnlyToolsToolBar(bool visible)
{
#ifdef HOOPS_ONLY
	// create the 'HOOPS Only' toolbar
	if (!m_wndToolBarHoopsOnly.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarHoopsOnly.LoadToolBar(IDR_TOOLBAR_HOOPS_ONLY))
	{
		TRACE0("Failed to create toolbar: Hoops Only\n");
		abort();      // fail to create
	}
	m_wndToolBarHoopsOnly.SetWindowText(_T("Object Tools"));
	m_wndToolBarHoopsOnly.SetBarStyle(m_wndToolBarHoopsOnly.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarHoopsOnly.EnableDocking(CBRS_ALIGN_ANY);
#ifdef HOOPS_ONLY
	m_wndToolBarHoopsOnly.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndToolBarHoopsOnly, visible, FALSE);
#endif
}

void CSolidHoopsFrame::CreateStandardViewsToolsToolBar(bool visible)
{
	// create the 'Standard Views' toolbar
	if (!m_wndToolBarStandardViews.CreateEx(this, 0, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarStandardViews.LoadToolBar(IDR_TOOLBAR_STANDARD_VIEWS))
	{
		TRACE0("Failed to create toolbar: Standard Views\n");
		abort();      // fail to create
	}
	m_wndToolBarStandardViews.SetWindowText(_T("Standard Views"));
	m_wndToolBarStandardViews.SetBarStyle(m_wndMainToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarStandardViews.EnableDocking(CBRS_ALIGN_ANY);
#ifdef HOOPS_QA
	m_wndToolBarStandardViews.EnableToolTips(false);
#endif
	ShowControlBar(&m_wndToolBarStandardViews, visible, FALSE);
}


void CSolidHoopsFrame::OnViewToolbarStandardViews() 
{
	if( (m_wndToolBarStandardViews.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarStandardViews, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarStandardViews, TRUE, FALSE);
	
}

void CSolidHoopsFrame::OnUpdateViewToolbarStandardViews(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarStandardViews.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


void CSolidHoopsFrame::OnViewToolbarTools() 
{
	if( (m_wndToolBarTools.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarTools, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarTools, TRUE, FALSE);
}

void CSolidHoopsFrame::OnUpdateViewToolbarTools(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarTools.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsFrame::OnViewToolbarStatus() 
{
	if( (m_wndStatusBar.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndStatusBar, FALSE, FALSE);
	else
		ShowControlBar(&m_wndStatusBar, TRUE, FALSE);
}

void CSolidHoopsFrame::OnUpdateViewToolbarStatus(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndStatusBar.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsFrame::OnViewToolbarPointCloud() 
{
	if( (m_wndPointCloudToolBar.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndPointCloudToolBar, FALSE, FALSE);
	else
		ShowControlBar(&m_wndPointCloudToolBar, TRUE, FALSE);
}

void CSolidHoopsFrame::OnUpdateViewToolbarPointCloud(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndPointCloudToolBar.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


void CSolidHoopsFrame::OnViewToolbarUndo()
{
	if( (m_wndToolBarTools.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarUndo, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarUndo, TRUE, FALSE);
}

void CSolidHoopsFrame::OnUpdateViewToolbarUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarUndo.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsFrame::OnViewToolbarLayoutLoad()
{
	if( (m_wndToolBarTools.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarLayoutLoad, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarLayoutLoad, TRUE, FALSE);
}

void CSolidHoopsFrame::OnUpdateViewToolbarLayoutLoad(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarLayoutLoad.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


#ifdef HOOPS_ONLY
void CSolidHoopsFrame::OnViewToolbarHoopsOnly() 
{
	if( (m_wndToolBarHoopsOnly.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarHoopsOnly, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarHoopsOnly, TRUE, FALSE);
	
}

void CSolidHoopsFrame::OnUpdateViewToolbarHoopsOnly(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarHoopsOnly.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
#endif
void CSolidHoopsFrame::OnViewToolbarCAE() 
{
	if( (m_wndToolBarCAE.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarCAE, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarCAE, TRUE, FALSE);
	
}

void CSolidHoopsFrame::OnUpdateViewToolbarCAE(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarCAE.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsFrame::OnViewToolbarMarkupText() 
{
	if( (m_wndToolBarMarkupText.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarMarkupText, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarMarkupText, TRUE, FALSE);
	
}

void CSolidHoopsFrame::OnUpdateViewToolbarMarkupText(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarMarkupText.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


/*!
  Shows/hides/creates a docking dialog bar
  \param bShow		- show or hide
  \param pDialogBar	- which dialogbar
  \param pDialog	- what dialog it holds (child dialog)
  \param csTitle	- the title for dialog bar
  \param resourceId	- resource id of the child dialog
*/
void CSolidHoopsFrame::ShowDockingDialogBar(BOOL bShow, CDockingDialogBar*& pDialogBar, CDialog * pDialog, CString csTitle, UINT resourceId, int dockingstyle, int dockingposition)
{
	// don't want to show and we haven't got it anyway
	if( !bShow && !pDialogBar )
		return;

	// don't have one - create it
	if( !pDialogBar )
	{
		pDialogBar = new CDockingDialogBar();
		pDialogBar->Create(this, pDialog, csTitle, resourceId);
		pDialogBar->SetBarStyle( pDialogBar->GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
		pDialogBar->EnableDocking(dockingstyle);
		DockControlBar(pDialogBar, dockingposition);
	}

	assert( pDialogBar );
	if( bShow )
		this->ShowControlBar( pDialogBar, TRUE, FALSE);
	else
		this->ShowControlBar( pDialogBar, FALSE, FALSE);
}


/*!
  Kills docking dialog bar
  \param pDialogBar
*/
void CSolidHoopsFrame::KillDockingDialogBar( CDockingDialogBar*& pDialogBar )
{
	if( pDialogBar )
	{	
		ShowControlBar( pDialogBar, FALSE, FALSE);
 		delete pDialogBar;
		pDialogBar = 0;
	}
}



/*!
  Creates/shows/hides a segment browser dialog bar
  \param bShow
*/
void CSolidHoopsFrame::ShowKeyframeEditorDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if(pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarKeyframeEditor, pActiveView->GetKeyframeEditorDialog(), "Keyframe Editor", IDD_KEYFRAME, CBRS_ALIGN_BOTTOM, AFX_IDW_DOCKBAR_BOTTOM);
}

void CSolidHoopsFrame::ShowClashBrowserDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if(pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarClashBrowser, pActiveView->GetClashBrowserDialog(), "Clash Browser", IDD_CLASHDLG, CBRS_ALIGN_BOTTOM, AFX_IDW_DOCKBAR_BOTTOM);
}
void CSolidHoopsFrame::ShowClashSelectDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if(pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarClashSelect, pActiveView->GetClashSelectDialog(), "Clash Select", IDD_CLASH_SELECT_DLG,  CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
}

/*!
  Creates/shows/hides a segment browser dialog bar
  \param bShow
*/
void CSolidHoopsFrame::ShowSegmentBrowserDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if(pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarSegmentBrowser, pActiveView->GetSegmentBrowserDialog(), "Segment Browser", IDD_SEGMENTBROWSER, CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
}

/*!
Creates/shows/hides a model browser dialog bar
\param bShow
*/
void CSolidHoopsFrame::ShowModelBrowserDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if(pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarModelBrowser, pActiveView->GetModelBrowserDialog(), "Model Browser", IDD_MODELBROWSER, CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
}

/*!
  Creates/shows/hides a segment browser dialog bar
  \param bShow
*/
void CSolidHoopsFrame::ShowErrorBrowserDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if(pActiveView)
	{
		ShowDockingDialogBar(bShow, m_pDlgBarErrorBrowser, pActiveView->GetErrorBrowserDialog(), "Error Browser", IDD_ERRORBROWSER, CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
//		((CErrorBrowserDlg *)pActiveView->GetErrorBrowserDialog())->RefreshAll();
	}

}

/*!
  Creates/shows/hides a topology browser dialog bar
  \param bShow
*/
void CSolidHoopsFrame::ShowTopologyBrowserDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
#ifdef ACIS
	UINT topol_dlg_res_id = IDD_TOPOLBROWSER1;
#endif // ACIS
#ifdef HOOPS_ONLY
	UINT topol_dlg_res_id = 0;
#endif // HOOPS_ONLY
	if(pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarTopologyBrowser, pActiveView->GetTopologyBrowserDialog(), "Topology Browser", topol_dlg_res_id, CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
}

/*!
  Creates/shows/hides a segment browser dialog bar
  \param bShow
*/
void CSolidHoopsFrame::ShowCMMDisplayDialogBar(BOOL bShow)
{
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert( pChildFrm );
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if(pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarCMMDisplay, pActiveView->GetCMMDisplayDialog(), "CMM Display", IDD_CMM_DISPLAY, CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
}

/*!
  Event recieved by the view class when the active view is changed. We update the child dialogs in 
  the dialog bars
  \param bActivate		- view being activated or deactivated
  \param pActivateView	- the one being activated
  \param pDeactiveView	- the one being deactivate
*/
void CSolidHoopsFrame::OnActivateView(BOOL bActivate, CSolidHoopsView* pActivateView, CSolidHoopsView* pDeactiveView)
{
	if( bActivate )
	{

	CMenu *Menu = GetMenu();
#ifdef _DEBUG

	CAppSettings::ShowDebugMenu = true;
#endif

	if (!CAppSettings::ShowDebugMenu)
	{
		int count = Menu->GetMenuItemCount();
		for (int i = 0; i < count; i++)
		{
			CString str;
			if (Menu->GetMenuString(i, str, MF_BYPOSITION) && 
				(_tcscmp(str, _T("DEBUG")) == 0))
				Menu->DeleteMenu(i,MF_BYPOSITION);
			if (Menu->GetMenuString(i, str, MF_BYPOSITION) && 
				(_tcscmp(str, _T("Dynamic Debug")) == 0))
				Menu->DeleteMenu(i,MF_BYPOSITION);
		}
	}	  
		// if we are getting activated and we have dialogbars, let's change
		// the dialogs in them 
		if( pActivateView )
		{

			if( m_pDlgBarKeyframeEditor && m_pDlgBarKeyframeEditor->IsWindowVisible() )
				m_pDlgBarKeyframeEditor->ChangeDialog( pActivateView->GetKeyframeEditorDialog(), IDD_KEYFRAME );

			if( m_pDlgBarClashBrowser && m_pDlgBarClashBrowser->IsWindowVisible() )
				m_pDlgBarClashBrowser->ChangeDialog( pActivateView->GetClashBrowserDialog(), IDD_CLASHDLG );
			if( m_pDlgBarClashSelect && m_pDlgBarClashSelect->IsWindowVisible() )
				m_pDlgBarClashSelect->ChangeDialog( pActivateView->GetClashSelectDialog(), IDD_CLASH_SELECT_DLG );


			// update the segment browser dialogbar
			// must update even if not visible, or will display the wrong view when re-enabled
			if( m_pDlgBarSegmentBrowser ) // && (m_pDlgBarSegmentBrowser->IsWindowVisible() || (m_pDlgBarTopologyBrowser &&  m_pDlgBarTopologyBrowser->IsWindowVisible())))
				m_pDlgBarSegmentBrowser->ChangeDialog( pActivateView->GetSegmentBrowserDialog(), IDD_SEGMENTBROWSER );
			if( m_pDlgBarCMMDisplay ) // && (m_pDlgBarSegmentBrowser->IsWindowVisible() || (m_pDlgBarTopologyBrowser &&  m_pDlgBarTopologyBrowser->IsWindowVisible())))
				m_pDlgBarCMMDisplay->ChangeDialog( pActivateView->GetCMMDisplayDialog(), IDD_CMM_DISPLAY );

			// update the Model browser dialogbar
			if( m_pDlgBarModelBrowser && (m_pDlgBarModelBrowser->IsWindowVisible() 
			|| (m_pDlgBarSegmentBrowser &&  m_pDlgBarSegmentBrowser->IsWindowVisible())
		    || (m_pDlgBarTopologyBrowser &&  m_pDlgBarTopologyBrowser->IsWindowVisible()) )
			)
				m_pDlgBarModelBrowser->ChangeDialog( pActivateView->GetModelBrowserDialog(), IDD_MODELBROWSER );

			if( m_pDlgBarErrorBrowser && m_pDlgBarErrorBrowser->IsWindowVisible())
				m_pDlgBarErrorBrowser->ChangeDialog( pActivateView->GetErrorBrowserDialog(), IDD_ERRORBROWSER );

			// update the topology browser dialogbar
			// must update even if not visible, or will display the wrong view when re-enabled
			if( m_pDlgBarTopologyBrowser ) // && (m_pDlgBarTopologyBrowser->IsWindowVisible() || (m_pDlgBarSegmentBrowser &&  m_pDlgBarSegmentBrowser->IsWindowVisible())))
			{
#ifdef ACIS
	UINT topol_dlg_res_id = IDD_TOPOLBROWSER1;
#endif // ACIS
#ifdef HOOPS_ONLY
	UINT topol_dlg_res_id = 0;
#endif // HOOPS_ONLY

				m_pDlgBarTopologyBrowser->ChangeDialog( pActivateView->GetTopologyBrowserDialog(), topol_dlg_res_id );
			}

			if (m_pDlgBarInterOpPartBrowser)
				m_pDlgBarInterOpPartBrowser->ChangeDialog(pActivateView->GetInterOpPartBrowserDialog(), IDD_IOPPARTBROWSER);
		}
	}
	
}

/*!
  Event recieved by the view after it is killed. We kill any dialogbars if this is the last view
  \param pDestroyedView - pointer to destroyed view
*/
void CSolidHoopsFrame::ViewDestoryed(CSolidHoopsView* pDestroyedView )
{
	// if this the last child view, destroy the dialogbars
	if( !MDIGetActive() )
	{
		KillDockingDialogBar( m_pDlgBarSegmentBrowser );
		KillDockingDialogBar( m_pDlgBarCMMDisplay );
		KillDockingDialogBar( m_pDlgBarModelBrowser);
		KillDockingDialogBar( m_pDlgBarErrorBrowser );
		KillDockingDialogBar( m_pDlgBarTopologyBrowser );
		KillDockingDialogBar( m_pDlgBarKeyframeEditor );
 		KillDockingDialogBar( m_pDlgBarClashBrowser );
 		KillDockingDialogBar( m_pDlgBarClashSelect );
 		KillDockingDialogBar( m_pDlgBarInterOpPartBrowser );
 	}
}

/*!
  Toggle display segment browser
*/
void CSolidHoopsFrame::OnSegmentbrowser() 
{
	if( m_pDlgBarSegmentBrowser && m_pDlgBarSegmentBrowser->IsWindowVisible() )
		ShowSegmentBrowserDialogBar( FALSE );
	else
		ShowSegmentBrowserDialogBar( TRUE );
}

/*!
  Toggle display segment browser
*/
void CSolidHoopsFrame::OnCMMDisplay() 
{
	if( m_pDlgBarCMMDisplay && m_pDlgBarCMMDisplay->IsWindowVisible() )
		ShowCMMDisplayDialogBar( FALSE );
	else
		ShowCMMDisplayDialogBar( TRUE );
}

void CSolidHoopsFrame::OnUpdateSegmentbrowser(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();

	if (view && (strcmp (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 ))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);

	if( m_pDlgBarSegmentBrowser && m_pDlgBarSegmentBrowser->IsWindowVisible() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsFrame::OnUpdateCMMDisplay(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();

	if (view && (strcmp (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 ))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);

	if( m_pDlgBarCMMDisplay && m_pDlgBarCMMDisplay->IsWindowVisible() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

/*!
Toggle display model browser
*/
void CSolidHoopsFrame::OnModelbrowser() 
{
	if( m_pDlgBarModelBrowser && m_pDlgBarModelBrowser->IsWindowVisible() )
		ShowModelBrowserDialogBar( FALSE );
	else
		ShowModelBrowserDialogBar( TRUE );
}

void CSolidHoopsFrame::OnUpdateModelbrowser(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();

	if (view && (strcmp (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 ))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);

	if( m_pDlgBarModelBrowser && m_pDlgBarModelBrowser->IsWindowVisible() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

/*!
  Toggle display segment browser
*/
void CSolidHoopsFrame::OnErrorbrowser() 
{
	if( m_pDlgBarErrorBrowser && m_pDlgBarErrorBrowser->IsWindowVisible() )
		ShowErrorBrowserDialogBar( FALSE );
	else
		ShowErrorBrowserDialogBar( TRUE );
}

void CSolidHoopsFrame::OnUpdateErrorbrowser(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();

	if (view && (strcmp (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 ))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
	
	if( m_pDlgBarErrorBrowser && m_pDlgBarErrorBrowser->IsWindowVisible() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


/*!
  Toggle display topology browser
*/
void CSolidHoopsFrame::OnTopolbrowser() 
{
	if( m_pDlgBarTopologyBrowser && m_pDlgBarTopologyBrowser->IsWindowVisible() )
		ShowTopologyBrowserDialogBar( FALSE );
	else
		ShowTopologyBrowserDialogBar( TRUE );
}

void CSolidHoopsFrame::OnToolsKeyframeeditor() 
{
	if( m_pDlgBarKeyframeEditor && m_pDlgBarKeyframeEditor->IsWindowVisible() )
		ShowKeyframeEditorDialogBar( FALSE );
	else
		ShowKeyframeEditorDialogBar( TRUE );
	
}

void CSolidHoopsFrame::OnToolsClashBrowser() 
{
	if( m_pDlgBarClashBrowser && m_pDlgBarClashBrowser->IsWindowVisible() )
		ShowClashBrowserDialogBar( FALSE );
	else
		ShowClashBrowserDialogBar( TRUE );
	
}

void CSolidHoopsFrame::OnUpdateToolsKeyframeeditor(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();

	if (view && (strcmp (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 ))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);

	if( m_pDlgBarKeyframeEditor && m_pDlgBarKeyframeEditor->IsWindowVisible() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}	
void CSolidHoopsFrame::OnUpdateToolsClashBrowser(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();

	if (view && (strcmp (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 ))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);

	if( m_pDlgBarClashBrowser && m_pDlgBarClashBrowser->IsWindowVisible() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}	



void CSolidHoopsFrame::OnViewToolbarAnimation() 
{
	if( (m_wndToolBarBehavior.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarBehavior, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarBehavior, TRUE, FALSE);
	
}

void CSolidHoopsFrame::OnUpdateViewToolbarAnimation(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarBehavior.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);	
}


BOOL CSolidHoopsFrame::PreCreateWindow(CREATESTRUCT& cs) 
{

	// override the default main window location and size if required
	if( CAppSettings::OverrideDefaultAppWindowPosition )
	{
		char cx[256], cy[256], cw[256], ch[256];
		int x, y, w, h;
		x = y = w = h = -1;

		HUtilityAsciiStr app_window_pos(CAppSettings::AppWindowPosition);

		HC_Parse_String(app_window_pos, ",", 0, cx);
		HC_Parse_String(app_window_pos, ",", 1, cy);
		HC_Parse_String(app_window_pos, ",", 2, cw);
		HC_Parse_String(app_window_pos, ",", 3, ch);
		x = atoi(cx);
		y = atoi(cy);
		w = atoi(cw);
		h = atoi(ch);

		// if negative, we will use the default
		if(x >= 0)
		    cs.x = x;
		if(y >= 0)
		    cs.y = y; 
		if(w >= 0)
		    cs.cx = w;
		if(h >= 0)
		    cs.cy = h; 

	}
    
	return CHoopsFrame::PreCreateWindow(cs);
}


void CSolidHoopsFrame::OnToolbarCAE()
{
	if( (m_wndToolBarCAE.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarCAE, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarCAE, TRUE, FALSE);
}

void CSolidHoopsFrame::OnUpdateToolbarCAE(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarCAE.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);	
}

void CSolidHoopsFrame::OnToolbarCMM()
{
	if( (m_wndToolBarCMM.GetStyle() & WS_VISIBLE) != 0)
		ShowControlBar(&m_wndToolBarCMM, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBarCMM, TRUE, FALSE);
}

void CSolidHoopsFrame::OnUpdateToolbarCMM(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	if( (m_wndToolBarCMM.GetStyle() & WS_VISIBLE) != 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);	
}

void CSolidHoopsFrame::ShowInterOpPartBrowserDialogBar ( BOOL bShow ) {
	CMDIChildWnd *pChildFrm = MDIGetActive();
	assert(pChildFrm);
	CSolidHoopsView *pActiveView = (CSolidHoopsView *)pChildFrm->GetActiveView();
	assert(pActiveView);
	if (pActiveView)
		ShowDockingDialogBar(bShow, m_pDlgBarInterOpPartBrowser, pActiveView->GetInterOpPartBrowserDialog(), "InterOp Part Browser", IDD_IOPPARTBROWSER, CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
}

void CSolidHoopsFrame::OnInterOpPartBrowser () {
	if (m_pDlgBarInterOpPartBrowser && m_pDlgBarInterOpPartBrowser->IsWindowVisible())
		ShowInterOpPartBrowserDialogBar(FALSE);
	else
		ShowInterOpPartBrowserDialogBar(TRUE);
}

void CSolidHoopsFrame::OnUpdateInterOpPartBrowser ( CCmdUI * pCmdUI ) {
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
	CSolidHoopsView * view = (CSolidHoopsView *)pChild->GetActiveView();

	if (view && streq(view->GetRuntimeClass()->m_lpszClassName, "CSolidHoopsView"))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);

	if (m_pDlgBarInterOpPartBrowser && m_pDlgBarInterOpPartBrowser->IsWindowVisible())
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
