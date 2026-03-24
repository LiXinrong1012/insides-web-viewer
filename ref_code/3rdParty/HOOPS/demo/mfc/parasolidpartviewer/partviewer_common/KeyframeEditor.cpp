// KeyframeEditor.cpp : implementation file
//

#include "stdafx.h"
#ifndef GRANITE
#include <afxpriv.h>
#endif
#include "KeyframeEditor.h"
#include "AviOptionsDlg.h"
 
#include "HBaseView.h"
#include "HBaseModel.h"
#include "HBhvBehaviorManager.h"
#include "HIMManager.h"
#include "HBhvAnimation.h"
#include "HBhvInterpolator.h"
#include "HBhvTimeline.h"
#include "HUtilityGeomHandle.h"
#include "HSOpMoveHandle.h"
#include "HSSelectionSet.h"
#include "HSOpCameraWalk.h"
#include "CSolidHoopsFrm.h"
#include "CSolidHoopsView.h"
#include "XMLEditorDlg.h"
#include "HUtilityXMLParser.h"
#include "vlist.h"
#include "HUtilityLocaleString.h"
#include "HIOManager.h"

#define NUMBOXHOR 1000
#define NUMBOXVERT 50

#define BOXY 11

#define XSTART 130
#define YSTART 40

static int xend, yend;





/////////////////////////////////////////////////////////////////////////////
// CKeyframeEditor dialog


CKeyframeEditor::CKeyframeEditor(CWnd* pParent /*=NULL*/, HBaseView *view)
	: CDialog(CKeyframeEditor::IDD, pParent)
{
	m_pSolidHoopsView = (CSolidHoopsView *)pParent;
	m_anirange[0] = 0;
	m_anirange[1] = 0;
	m_anirangesav[0] = -1;
	m_anirangesav[1] = -1;
	m_pHView = view;
	m_lbuttondown = false;
	m_animationnum = 0;
	m_boxx = 8;
 	for (int i=0;i<256;i++)
		m_animationlist[i] = 0;
 	m_cameratype = 0;
	m_update_view = true;
	m_framerange[0] = 0;
	m_framerange[1] = 0;
	m_bDragMode = false;
	m_LatestDrag = -1;
	m_FirstDragX = -1;
	m_FirstDragY = -1;
	m_bRecordMode = false;


 
}


void CKeyframeEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyframeEditor)
	DDX_Control(pDX, IDC_SCROLLBAR2, m_VerticalScrollbar);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_HorizontalScrollbar);
 	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CDlgToolBar

BEGIN_MESSAGE_MAP(CDlgToolBar, CToolBar)
	//{{AFX_MSG_MAP(CDlgToolBar)
#ifndef GRANITE
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
                

BEGIN_MESSAGE_MAP(CKeyframeEditor, CDialog)
	//{{AFX_MSG_MAP(CKeyframeEditor)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_ACTIVATE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
 	ON_COMMAND(IDC_DELETE_ANIMATIONS, OnDeleteAnimations)
	ON_COMMAND(IDC_DELETE_KEYFRAMES, OnDeleteKeyframes)
	ON_COMMAND(IDC_DUPLICATE_LAST, OnDuplicateLast)
	ON_COMMAND(IDC_DUPLICATE_NEXT, OnDuplicateNext)
	ON_COMMAND(IDC_BUTTON_COPY, OnButtonCopy)
 	ON_BN_CLICKED(IDC_BUTTON_PASTE, OnButtonPaste)
 	ON_BN_CLICKED(IDC_MAKE_CAMERA_KEYFRAME, OnMakeCameraKeyframe)
	ON_BN_CLICKED(IDC_MAKE_LINEAR, OnMakeLinear)
	ON_BN_CLICKED(IDC_MAKE_SPLINE, OnMakeSpline)
	ON_BN_CLICKED(IDC_MANIPULATOR, OnManipulator)
	ON_BN_CLICKED(IDC_MAKE_ATTSWITCH_KFR, OnMakeAttswitchKfr)
	ON_BN_CLICKED(IDC_ACTIVATE_SELECTION, OnActivateSelection)
	ON_BN_CLICKED(IDC_AXIS_ROT_KEYFRAME, OnAxisRotKeyframe)
	ON_BN_CLICKED(IDC_BHV_RELOAD, OnBhvReload)
	ON_BN_CLICKED(IDC_BHV_WALK, OnBhvWalk)
	ON_CBN_SELCHANGE(IDC_ZOOMCOMBO, OnSelchangeZoomcombo)
	ON_CBN_SELCHANGE(IDC_TEXTZOOM, OnSelchangeTextzoom)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BHV_EDITXML, OnBhvEditxml)
 	ON_COMMAND(IDC_BHV_DRAGMODE, OnBhvDragmode)
	ON_UPDATE_COMMAND_UI(IDC_BHV_DRAGMODE, OnUpdateBhvDragmode)
	ON_COMMAND(IDC_BHV_CAMERA_POS_MODE, OnBhvCameraPosMode)
	ON_UPDATE_COMMAND_UI(IDC_BHV_CAMERA_POS_MODE, OnUpdateBhvCameraPosMode)
	ON_COMMAND(IDC_BHV_CAMERA_TARGET_MODE, OnBhvCameraTargetMode)
	ON_UPDATE_COMMAND_UI(IDC_BHV_CAMERA_TARGET_MODE, OnUpdateBhvCameraTargetMode)
	ON_COMMAND(IDC_BHV_UPDATE_VIEW, OnBhvUpdateView)
	ON_UPDATE_COMMAND_UI(IDC_BHV_UPDATE_VIEW, OnUpdateBhvUpdateView)
	ON_COMMAND(IDC_BHV_MAGNIFY_1X, OnBhvMagnify1x)
	ON_UPDATE_COMMAND_UI(IDC_BHV_MAGNIFY_1X, OnUpdateBhvMagnify1x)
	ON_COMMAND(IDC_BHV_MAGNIFY_2X, OnBhvMagnify2x)
	ON_UPDATE_COMMAND_UI(IDC_BHV_MAGNIFY_2X, OnUpdateBhvMagnify2x)
	ON_COMMAND(IDC_BHV_MAGNIFY_4X, OnBhvMagnify4x)
	ON_UPDATE_COMMAND_UI(IDC_BHV_MAGNIFY_4X, OnUpdateBhvMagnify4x)
	ON_COMMAND(IIDC_BHV_MAGNIFY_8X, OnBhvMagnify8x)
	ON_UPDATE_COMMAND_UI(IIDC_BHV_MAGNIFY_8X, OnUpdateBhvMagnify8x)
	ON_COMMAND(IDC_BHV_AUTOMATIC_RECORD, OnBhvAutomaticRecord)
	ON_COMMAND(IDC_BHV_RECORD_CAMERA, OnBhvRecordCamera)
	ON_UPDATE_COMMAND_UI(IDC_BHV_AUTOMATIC_RECORD, OnUpdateBhvAutomaticRecord)
	ON_UPDATE_COMMAND_UI(IDC_BHV_RECORD_CAMERA, OnUpdateBhvRecordCamera)
	ON_COMMAND(IDC_BHV_DRAW_CURVE, OnBhvDrawCurve)
	ON_COMMAND(IDC_BHV_DRAW_CURVE_ROT, OnBhvDrawCurveRot)
	ON_COMMAND(IDC_BUTTON_PASTE, OnButtonPaste)
	ON_COMMAND(IDC_MAKE_CAMERA_KEYFRAME, OnMakeCameraKeyframe)
	ON_COMMAND(IDC_MAKE_ATTSWITCH_KFR, OnMakeAttswitchKfr)
	ON_COMMAND(IDC_AXIS_ROT_KEYFRAME, OnAxisRotKeyframe)
	ON_COMMAND(IDC_MAKE_LINEAR, OnMakeLinear)
	ON_COMMAND(IDC_MAKE_SPLINE, OnMakeSpline)
	ON_COMMAND(IDC_BHV_EDITXML, OnBhvEditxml)
	ON_COMMAND(IDC_MAKE_COLLISION, OnMakeCollision)
	ON_COMMAND(IDC_EXPORT_AVI, OnExportAVI)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CKeyframeEditor::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
//	rect.SetRect(100,100,150,150);
	if (m_VerticalScrollbar.m_hWnd)
		m_VerticalScrollbar.SetWindowPos(0, cx - 30, YSTART ,20,cy-80,SWP_NOOWNERZORDER);
	if (m_HorizontalScrollbar.m_hWnd)
		m_HorizontalScrollbar.SetWindowPos(0, XSTART, cy -30 ,cx-180,20,SWP_NOOWNERZORDER);
	InvalidateBoxes();
	xend = XSTART + cx-180;
	yend = YSTART + cy- 80;

		CDC *dc= GetDC();		
	DrawNewBoxes(dc);
	ReleaseDC(dc);

	// TODO: Add your message handler code here
	
}

void CKeyframeEditor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	DrawNewBoxes(&dc);
	// Do not call CDialog::OnPaint() for painting messages
}



void CKeyframeEditor::DrawBox(CDC *dc, int xpos, int ypos, int r, int g, int b)
{
//	CBrush brushblack(RGB(0, 0, 0));
	CBrush brushwhite(RGB(r, g, b));
	CBrush* pOldBrush;
//	if (filled)
 		pOldBrush = dc->SelectObject(&brushwhite);
//	else
 //		pOldBrush = dc->SelectObject(&brushblack);

	dc->Rectangle(XSTART + xpos*m_boxx+1, YSTART + ypos*BOXY+1, XSTART + xpos*m_boxx + m_boxx-1, YSTART + ypos*BOXY + BOXY-1);
	
//	dc->SelectObject(pOldBrush);

}
//		DrawOuterBox(dc, pBehaviorManager->GetCurrentTick() - hpos, (yend - YSTART)/BOXY-1);
void CKeyframeEditor::DrawBox(CDC *dc, int xpos, int ypos, int length, int r, int g, int b)
{
//	CBrush brushblack(RGB(0, 0, 0));
	CBrush brushwhite(RGB(r, g, b));
	CBrush* pOldBrush;
//	if (filled)
 		pOldBrush = dc->SelectObject(&brushwhite);
//	else
 //		pOldBrush = dc->SelectObject(&brushblack);

	
	int x1 = XSTART + xpos*m_boxx+1;
	int y1 =  YSTART + ypos*BOXY+1;
	int x2 =  XSTART + xpos*m_boxx + (m_boxx * length) + 2;
	int y2 = YSTART + ypos*BOXY + BOXY-1;
	if (x2<XSTART)
		return;
	if (x1 < XSTART)
		x1 = XSTART;
	if (x1>xend)
		return;

	if (y1>xend)
		return;
	if (y1<YSTART)
		return;

	if (x2>xend)
		x2 = xend;

	dc->Rectangle(x1, y1, x2, y2);
 	
//	dc->SelectObject(pOldBrush);

}
//		DrawOuterBox(dc, pBehaviorManager->GetCurrentTick() - hpos, (yend - YSTART)/BOXY-1);


void CKeyframeEditor::DrawOuterBox(CDC *dc, int xpos, int xpos2, int ypos, int ypos2)
{
 
	int hpos, vpos;
	if (m_HorizontalScrollbar.m_hWnd)
	{
		hpos = m_HorizontalScrollbar.GetScrollPos();
		vpos = m_VerticalScrollbar.GetScrollPos();
	}
	else
	{
		hpos = 0;
		vpos = 0;
	}	
	xpos -= hpos;	
	xpos2 -= hpos;	
	ypos -= vpos;	
	ypos2 -= vpos;	
	if ((xpos<0 && xpos2<0) || (xpos>=((xend - XSTART)/m_boxx -1) && xpos2>=((xend - XSTART)/m_boxx -1)))
		return;
	if ((ypos<0 && ypos2<0) || (ypos>=((yend - YSTART)/BOXY -1) && ypos2>=((yend - YSTART)/BOXY -1)))
		return;

	if (xpos > ((xend - XSTART)/m_boxx -1))
		xpos = (xend - XSTART)/m_boxx -1;
	if (xpos<0)
		xpos = 0;

	if (xpos2 > ((xend - XSTART)/m_boxx -1))
		xpos2 = (xend - XSTART)/m_boxx -1;
	if (xpos2<0)
		xpos2 = 0;
  


	if (ypos > ((yend - YSTART)/BOXY -1))
		ypos = (yend - YSTART)/BOXY -1;
	if (ypos<0)
		ypos = 0;

	if (ypos2 > ((yend - YSTART)/BOXY -1))
		ypos2 = (yend - YSTART)/BOXY -1;
	if (ypos2<0)
		ypos2 = 0;


	POINT p[5] = {XSTART + xpos*m_boxx, YSTART + ypos *BOXY, 
				 XSTART + xpos2*m_boxx + m_boxx - 1 , YSTART + ypos * BOXY,
				 XSTART + xpos2*m_boxx + m_boxx - 1, YSTART + ypos2 *BOXY + BOXY - 1,
				 XSTART + xpos*m_boxx, YSTART + ypos2*BOXY + BOXY - 1,
				XSTART + xpos*m_boxx, YSTART + ypos * BOXY};

	
	dc->Polyline(p,5);
  
}


 




int CKeyframeEditor::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here


	return 0;
}



BOOL CKeyframeEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		m_HorizontalScrollbar.SetScrollRange(0,NUMBOXHOR);
	m_VerticalScrollbar.SetScrollRange(0,NUMBOXVERT);
		CDC *dc= GetDC();		
	DrawNewBoxes(dc);
	ReleaseDC(dc);
//	SetTimer(1,1000,0);
	UpdateButtonStates();

 

 
 
//	m_wndToolBar.CreateEx(this, WS_CHILD | WS_VISIBLE );

//    m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
//		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY);

 m_wndToolBar.Create(this);
 m_wndToolBar.LoadToolBar(IDR_TOOLBAR_KEYFRAME);
 m_wndToolBar.ShowWindow(SW_SHOW);
 m_wndToolBar.SetBarStyle(CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY );
 RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
 
//	m_wndToolBar.SetWindowText("Standard");
//	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
//		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);


	OnManipulator();
	InvalidateBoxes();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKeyframeEditor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
 
	switch (nSBCode)
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos(nPos);	
 		break;
	case SB_RIGHT:
 		break;
	case SB_LEFT:
		pScrollBar->SetScrollPos(0);	
		break;
	case SB_PAGELEFT:    // Scroll one page left.
		{  
			int hpos = m_HorizontalScrollbar.GetScrollPos();
    	    		int max = m_HorizontalScrollbar.GetScrollLimit();
					(void) max;
			int curpos = max(0, hpos - 20);
			pScrollBar->SetScrollPos(curpos);	
 			
		}
		break;
	case SB_PAGERIGHT:    // Scroll one page left.
		{
			int hpos = m_HorizontalScrollbar.GetScrollPos();
    	    		int max = m_HorizontalScrollbar.GetScrollLimit();
			int curpos = min(max, hpos +20);
			pScrollBar->SetScrollPos(curpos);	
			
		}
		break;					
	}

    

	CDC *dc= GetDC();		
	InvalidateBoxes();

	DrawNewBoxes(dc);
	ReleaseDC(dc);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CKeyframeEditor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK )
		pScrollBar->SetScrollPos(nPos);
	InvalidateBoxes();

	CDC *dc= GetDC();		
	DrawNewBoxes(dc);
	ReleaseDC(dc);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CKeyframeEditor::GetScrollbarPosition(int &hpos, int &vpos)
{
	if (m_HorizontalScrollbar.m_hWnd)
	{
		hpos = m_HorizontalScrollbar.GetScrollPos();
		vpos = m_VerticalScrollbar.GetScrollPos();
	}
	else
	{
		hpos = 0;
		vpos = 0;
	}

}

int CKeyframeEditor::CalculateKeyframeFromMousePosition(int mousex)
{
    int hpos, vpos;
    GetScrollbarPosition(hpos,vpos);
    return (mousex - XSTART) / m_boxx + hpos;

}

int CKeyframeEditor::CalculateYFromMousePosition(int mousey)
{
    int hpos, vpos;
    GetScrollbarPosition(hpos,vpos);
    return ((mousey - YSTART) / BOXY + vpos);
} 

bool CKeyframeEditor::IsInTextField(int posx, int posy)
{
    if (posx < XSTART && posy >=YSTART)
	return true;
    else
	return false;
}
bool CKeyframeEditor::IsInEditor(int posx, int posy)
{
    if (posx > XSTART && posy >=YSTART)
	return true;
    else
	return false;
}
bool CKeyframeEditor::IsAboveEditor(int posx, int posy)
{
    if (posx > XSTART && posy <=YSTART)
	return true;
    else
	return false;
}

void CKeyframeEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	 
	int x =CalculateKeyframeFromMousePosition(point.x);
	int y = CalculateYFromMousePosition(point.y);
	m_FirstDragX = -1;
	m_FirstDragY = -1;
	m_LatestDrag = -1;

	if (IsInTextField(point.x, point.y))
	{
		m_anirange[0] = y;
		m_anirange[1] = y;
		if (m_anirange[0] < m_animationnum)
		{
			HBhvAnimation *anim = m_animationlist[m_anirange[0]];
			if (anim->GetTarget()->GetCameraType() == NoCamera)
			{
 				HUtilityGeomHandle::ClearAllHandles(m_pHView);
				HC_KEY key = anim->GetTarget()->GetTargetKey();
				((HSOpMoveHandle *)m_pHView->GetHandleOperator())->Reset(key);
				HUtilityGeomHandle::SetupManipulator(key, m_pHView, false, false, false);
 				m_pHView->Update();
				Invalidate();
			}
		}

		InvalidateBoxes();
	}
	else if (IsAboveEditor(point.x, point.y))
	{
 			HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
 			pBehaviorManager->SetCurrentTick((float)x);
			m_framerange[0] = x;
			m_framerange[1] = x;
			InvalidateBoxes();	
	}
	else
	{


	m_lbuttondown = true;

	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	
	if (IsInEditor(point.x, point.y))
	{
		InvalidateBoxes();
 		pBehaviorManager->SetCurrentTick((float)x);
 		if (!m_bDragMode)
		{
		m_framerange[0] = x;

		    m_framerange[1] = x;
		m_anirange[0] = y;
		m_anirange[1] = y;
		}
// 		DrawBox(dc, x - hpos, y - vpos, false);
		if (m_bDragMode)
		{
		    m_LatestDrag = x;
		    m_FirstDragX = x;
		    m_FirstDragY = y;
		}

	}
	}
	CDialog::OnLButtonDown(nFlags, point);
  

}

#ifdef _M_AMD64
void CKeyframeEditor::OnTimer(UINT_PTR nIDEvent)
#else
void CKeyframeEditor::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
//	InvalidateBoxes();	
	CDialog::OnTimer(nIDEvent);
}


void CKeyframeEditor::OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized )
{
	InvalidateBoxes();
	CDialog::OnActivate(nState, pWndOther, bMinimized);
}
void CKeyframeEditor::PlayToTick() 
{
		HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();

		if (m_update_view)
		{
			pBehaviorManager->ScheduleAllAnimations();
//			for (int i=0; i<= pBehaviorManager->GetCurrentTick(); i++)
				pBehaviorManager->ExecuteAnimations(pBehaviorManager->GetCurrentTick(), 0);
// 				pBehaviorManager->ExecuteAnimations(i, 0,true);	
			m_pHView->Update();
		}
}
 
void CKeyframeEditor::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	if (m_lbuttondown)
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();

	{
		m_lbuttondown = false;
		HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
		pBehaviorManager->SetCurrentTick((float)m_framerange[0]);
		UpdateData(true);
		PlayToTick();
	}
 	CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();
	frame->GetBhvToolbar()->m_wndBhvSlider.SetPos((int)pBehaviorManager->GetCurrentTickByPercentage());
 	CDialog::OnLButtonUp(nFlags, point);
}

void CKeyframeEditor::OnMouseMove(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    if (m_lbuttondown)
    {
	
	int x =CalculateKeyframeFromMousePosition(point.x);
	int y = CalculateYFromMousePosition(point.y);
	
	if (IsInEditor(point.x, point.y))
	{
	   	    
	    if (!m_bDragMode)
	    {	    
	    m_framerange[1] = x;
	    m_anirange[1] = y;	
	    }
	     
		if (m_LatestDrag!= -1)
		{
		    if (GetAsyncKeyState(VK_CONTROL) & 32768)
			AdjustKeyframe(m_FirstDragX, m_FirstDragY, x - m_LatestDrag, true, true);
		    else
		    {		    
		        if (GetAsyncKeyState(VK_SHIFT) & 32768)
			    AdjustKeyframe(m_FirstDragX, m_FirstDragY, x - m_LatestDrag, false, false);
			else
			    AdjustKeyframe(m_FirstDragX, m_FirstDragY, x - m_LatestDrag, true, false);
		    }


		    m_FirstDragX+=(x- m_LatestDrag);
			m_LatestDrag = x;
		}
	    
	    InvalidateBoxes();
	}
    }
    CDialog::OnMouseMove(nFlags, point);
}

void CKeyframeEditor::OnDeleteAnimations() 
{
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
		if (i<m_animationnum)
		{
			pBehaviorManager->DeleteAnimation(m_animationlist[i]);
 			m_animationlist[i] = 0;
		}
	}
	InvalidateBoxes();

}

void CKeyframeEditor::OnDeleteKeyframes() 
{
	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
	
		if (i<m_animationnum)
		{
			for (int j=(int)m_framerange[0];j<=(int)m_framerange[1];j++)
				m_animationlist[i]->DeleteKeyframe(j);
			if (m_animationlist[i]->GetTimeline()->GetTimelineArrayLength() == 0)
				OnDeleteAnimations();
		}
	}

	InvalidateBoxes();
	
}

void CKeyframeEditor::AdjustKeyframe(int x,int y, int delta, bool doall, bool relative) 
{
    if (delta>0)
	delta = delta;
	if (y<m_anirange[0] || y>m_anirange[1] || (m_anirange[0] == m_anirange[1]))
	{
		if (m_animationlist[y])
  			m_animationlist[y]->AdjustKeyframe(x,delta, doall, relative);
	}

	else
	{	

 	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
		if (i<m_animationnum)
		{
  			m_animationlist[i]->AdjustKeyframe(x,delta, doall, relative);
		}
	}
	}
	
	InvalidateBoxes();
	
}

void CKeyframeEditor::OnDuplicateLast() 
{
	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
	
		if (i<m_animationnum)
		{
			for (int j=m_framerange[0];j<=m_framerange[1];j++)
				m_animationlist[i]->DuplicateNextOrPrevious(j, false);
		}
	}
	InvalidateBoxes();
	
}

void CKeyframeEditor::OnDuplicateNext() 
{
	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
	
		if (i<m_animationnum)
		{
			for (int j=m_framerange[0];j<=m_framerange[1];j++)
				m_animationlist[i]->DuplicateNextOrPrevious(j, true);
		}
	}
	InvalidateBoxes();
	
}

void CKeyframeEditor::OnButtonCopy() 
{
	m_framerangesav[0] = m_framerange[0];
	m_framerangesav[1] = m_framerange[1];
	m_anirangesav[0] = m_anirange[0];
	m_anirangesav[1] = m_anirange[1];
	
}

void CKeyframeEditor::OnButtonPaste() 
{
    if (m_anirangesav[0] > -1)
    {
	for (int i=m_anirangesav[0];i<=m_anirangesav[1];i++)
	{
	    
	    if (m_animationlist[i])
	    {	    
		if (i<m_animationnum)
		{
		    for (int j=m_framerange[0];j<=(m_framerange[0] + (abs(m_framerangesav[1] - m_framerangesav[0])));j++)
			m_animationlist[i]->Duplicate(j, m_framerangesav[0] + (j - m_framerange[0]));
		}
	    }
	}
    }
    InvalidateBoxes();
    
    
}
 

void GetCameraFromMatrix(float *matrix, HPoint *position, HPoint *target, HPoint *up_vector)
{
//Target remains unchanged
//    HPoint view_vector;
//    view_vector.Set(position.x-target.x, position.y-target.y, position.z-target.z);

    position->x = matrix[12];
    position->y = matrix[13];
    position->z = matrix[14];

	target->x = matrix[8] + matrix[12];
	target->y = matrix[9] + matrix[13];
	target->z = matrix[10] + matrix[14];


    up_vector->x = matrix[4];
    up_vector->y = matrix[5];
    up_vector->z = matrix[6];


}



void GetMatrixFromCamera(HPoint position, HPoint target, HPoint up_vector, float *matrix)
{
    HPoint view_vector, view_vector2;
    view_vector.Set(target.x-position.x, target.y-position.y, target.z-position.z);
    view_vector2 = view_vector;
 
    HC_Compute_Normalized_Vector(&view_vector, &view_vector);
    HC_Compute_Normalized_Vector(&up_vector, &up_vector);

    HPoint cross1;

    HC_Compute_Cross_Product(&up_vector, &view_vector, &cross1);

    matrix[0] = cross1.x;
    matrix[1] = cross1.y;
    matrix[2] = cross1.z;
    matrix[3] = 0.0f;

    HPoint cross2;

    HC_Compute_Cross_Product(&view_vector, &cross1, &cross2);

    matrix[4] = cross2.x;
    matrix[5] = cross2.y;
    matrix[6] = cross2.z;
    matrix[7] = 0.0f;

    matrix[8] = view_vector.x;
    matrix[9] = view_vector.y;
    matrix[10] = view_vector.z;
    matrix[11] = 0.0f;
    
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1.0f;
}



void CKeyframeEditor::OnMakeCameraKeyframe() 
{



	static int ipcounter=0;
	HPoint p,t,u;
	float fx, fy;
	char proj[4096];
  	UpdateData(true);
 	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());		
		HC_Show_Net_Camera_Position(&p.x, &p.y, &p.z);
 		HC_Show_Net_Camera_Target(&t.x, &t.y, &t.z);
		HC_Show_Net_Camera_Up_Vector(&u.x, &u.y, &u.z);
		HC_Show_Net_Camera_Field(&fx,&fy);	
		HC_Show_Net_Camera_Projection(proj);
		HC_Close_Segment();
	HPoint p2, t2, u2;
 
	char targetname[MVO_BUFFER_SIZE];	
	char ipc[256];
 	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	sprintf(ipc, "%d", pBehaviorManager->GetFreeName());

	HC_Show_Segment(m_pHView->GetSceneKey(), targetname);
	HBhvTargetObject::CreateTargetString("SPATH", targetname, targetname);
	if (m_cameratype == 0)
		strcat(targetname,"/POSITION");
	else
		strcat(targetname,"/TARGET");
	HBhvAnimation *animation = pBehaviorManager->FindAnimation(targetname, "QuatRot");
	float matrix[16];
	float fquat[4];
	HQuat quat;
	if (animation == 0)
	{
		HBhvInterpolatorQuatSquad *i = new HBhvInterpolatorQuatSquad(0, ipc);
		HQuat parray(0,0,0,1);
 		int tline = 0;
 	 	i->Insert(parray, 0);
  		HBhvTimeline *t = new HBhvTimeline(0);
		t->SetTimeline(&tline , 1);
		animation = pBehaviorManager->AddAnimation(ipc, targetname, t, i);
 		animation->GetTarget()->SetPivot(0,0,0);
	}

	bool replace;
	int pos;
	
	pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);
 
	HPoint translation;
	translation.Set(0,0,0);
 	GetMatrixFromCamera(p, t, u, matrix);
	HUtility::MatrixToQuaternion(matrix, fquat);
	quat.Set(fquat[0], fquat[1], fquat[2], fquat[3]);

 	if (replace)
		((HBhvInterpolatorQuatSquad *)(animation->GetInterpolator()))->Replace(quat, pos);
	else
		((HBhvInterpolatorQuatSquad *)(animation->GetInterpolator()))->Insert(quat, pos);


	animation = pBehaviorManager->FindAnimation(targetname, "Pos");
	sprintf(ipc, "%d", pBehaviorManager->GetFreeName());
	if (animation == 0)
	{
		HBhvInterpolatorPosition *i = new HBhvInterpolatorPosition(0, ipc);
		HPoint parray(0,0,0);
 		int tline = 0;
 	 	i->InsertCurve(parray);
//		(parray, 1);
 		HBhvTimeline *t = new HBhvTimeline(0);
		t->SetTimeline(&tline , 1);
		animation = pBehaviorManager->AddAnimation(ipc, targetname, t, i);
	}

 	pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);
 
	if (m_cameratype == 1)
	{
 		if (replace)
			((HBhvInterpolatorPosition *)(animation->GetInterpolator()))->ReplaceCurve(t, pos);
		else
			((HBhvInterpolatorPosition *)(animation->GetInterpolator()))->InsertCurve(t, pos);
	}
	else
	{
 	if (replace)
		((HBhvInterpolatorPosition *)(animation->GetInterpolator()))->ReplaceCurve(p, pos);
	else
		((HBhvInterpolatorPosition *)(animation->GetInterpolator()))->InsertCurve(p, pos);
	}


	animation = pBehaviorManager->FindAnimation(targetname, "Scale");
	sprintf(ipc, "%d", pBehaviorManager->GetFreeName());
	if (animation == 0)
	{
		HBhvInterpolatorScale *i = new HBhvInterpolatorScale(0, ipc);
		HPoint parray(0,0,0);
 		int tline = 0;
 	 	i->Insert(parray, 0);
 		HBhvTimeline *t = new HBhvTimeline(0);
		t->SetTimeline(&tline , 1);
		animation = pBehaviorManager->AddAnimation(ipc, targetname, t, i);
	}

 	pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);
	 
	HPoint scale;
	
	HPoint lv(t.x - p.x, t.y - p.y, t.z - p.z);
	if (proj[0] == 'p')
	{
	    scale.x =	(float)HC_Compute_Vector_Length(&lv);
	    scale.y = 0;
	}
	else
	    scale.Set(fx,fy);	
 	if (replace)
		((HBhvInterpolatorScale *)(animation->GetInterpolator()))->Replace(scale, pos);
	else
		((HBhvInterpolatorScale*)(animation->GetInterpolator()))->Insert(scale, pos);
	InvalidateBoxes();

	if (GetRecordMode())
	{		
	    HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	    pBehaviorManager->SetCurrentTick(pBehaviorManager->GetCurrentTick()+10);
	    UpdateBhvState(true);
	    PlayToTick();
	}

	
}
	// TODO: Add your control notification handler code here
	


void CKeyframeEditor::OnMakeLinear() 
{
	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
		if (i<m_animationnum)
		{
			for (int j=m_framerange[0];j<=m_framerange[1];j++)
			{
				int anum;
				HKeyframe *kp;
 				if (m_animationlist[i]->GetInterpolator(j, anum, &kp))
				{				 
					int t1 = kp->m_type;
 					if (t1 == HANIChannel)
					{
						HKeyframeChannel *cp = (HKeyframeChannel *)kp;
						int t2 = ((HKeyframeChannel *)kp)->m_channeltype;
						if (t2 != 	HANILinear)
						{
							HKeyframeChannelLinear *lp = new HKeyframeChannelLinear;
  							lp->m_cp = cp->m_cp;
// 							(HKeyframeChannel)*lp = (HKeyframe)*cp;
							HBhvInterpolator *interp = m_animationlist[i]->GetInterpolator();
							interp->Replace(lp, anum);
						}
					}
 					else if (t1 == HANIRotation)
					{
						HKeyframeQuatSquad *cp = (HKeyframeQuatSquad *)kp;
						if (!cp->m_bLinear)
						{							
							cp->m_bLinear = true;
						}
					}
				}
			}
		}
	}
	InvalidateBoxes();
	
}

void CKeyframeEditor::OnMakeFollowPath() 
{
	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
		if (i<m_animationnum)
		{
			for (int j=m_framerange[0];j<=m_framerange[1];j++)
			{
				int anum;
				HKeyframe *kp;
 				if (m_animationlist[i]->GetInterpolator(j, anum, &kp))
				{				 
					int t1 = kp->m_type;
 					if (t1 == HANIChannel)
					{
						HKeyframeChannel *cp = (HKeyframeChannel *)kp;
						int t2 = ((HKeyframeChannel *)kp)->m_channeltype;
						bool linear = false;
						if (t2 == HANIFollowPath)
						{
							HKeyframeChannelFollowPath *fp = (HKeyframeChannelFollowPath *)cp;
							if (fp->m_bLinear)
								linear = true;
						}
						else
						{
							if (t2 == 	HANILinear)
								linear = true;
						}
						HKeyframeChannelFollowPath *lp = new HKeyframeChannelFollowPath;
  						lp->m_cp = cp->m_cp;
						lp->m_bLinear = linear;
 						HBhvInterpolator *interp = m_animationlist[i]->GetInterpolator();
						interp->Replace(lp, anum);						
					} 					
				}
			}
		}
	}
	InvalidateBoxes();
	
}

									
				 

void CKeyframeEditor::OnMakeSpline() 
{	
	for (int i=m_anirange[0];i<=m_anirange[1];i++)
	{
		if (i<m_animationnum)
		{
			for (int j=m_framerange[0];j<=m_framerange[1];j++)
			{
				int anum;
				HKeyframe *kp;
 				if (m_animationlist[i]->GetInterpolator(j, anum, &kp))
				{				 
					int t1 = kp->m_type;
 					if (t1 == HANIChannel)
					{
						HKeyframeChannel *cp = (HKeyframeChannel *)kp;
						int t2 = ((HKeyframeChannel *)kp)->m_channeltype;
						if (t2 == 	HANILinear)
						{
							HKeyframeChannelCurve *lp = new HKeyframeChannelCurve;
  							lp->m_cp = cp->m_cp;
// 							(HKeyframeChannel)*lp = (HKeyframe)*cp;
							HBhvInterpolator *interp = m_animationlist[i]->GetInterpolator();
							interp->Replace(lp, anum);
						}
					}
					else if (t1 == HANIRotation)
					{
						HKeyframeQuatSquad *cp = (HKeyframeQuatSquad *)kp;
						if (cp->m_bLinear)
						{							
							cp->m_bLinear = false;
						
						}
					}
				}
			}
		}
	}
	InvalidateBoxes();

}


void CKeyframeEditor::OnManipulator() 
{

 

	HSOpMoveHandle * handleoperator = (HSOpMoveHandle *)m_pHView->GetHandleOperator();
	handleoperator->SetKeyframeEditor(this);
	handleoperator->SetOwnerDialog(this);

/*
	HBaseOperator * op = m_pHView->GetOperator();

	HSOpMoveHandle *mh = new HSOpMoveHandle(m_pHView, (CSolidHoopsView *)GetParent());
	mh->SetOwnerDialog(this);
	m_pHView->SetOperator(mh);
	delete op;
*/
	UpdateButtonStates();
	
}

void CKeyframeEditor::OnMakeAttswitchKfr() 
{
	int				numSolidSelections, numHoopsSelections;
  	HSSelectionSet* selection = 0;

	selection = (HSSelectionSet *)m_pHView->GetSelection();

	numHoopsSelections = selection->GetSize();
	numSolidSelections = selection->GetSolidListSize();

	HC_KEY key;
	if (numHoopsSelections == 0 || numHoopsSelections >1)
		return;
	else
		 key = selection->GetAt(0);

	HC_KEY targetkey = ((HSOpMoveHandle *)m_pHView->GetHandleOperator())->GetObjectKey();
 
	if (targetkey == -1)
		return;
 
	char targetname[MVO_BUFFER_SIZE];	
	char objectname[256];
 	char attswitchname[256];
 	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	HC_Show_Segment(targetkey, targetname);
	HC_Show_Segment(key, attswitchname);
	HBhvTargetObject::CreateTargetString("SPATH", targetname, targetname);
//	HBhvTargetObject::CreateTargetString("SPATH", attswitchname, attswitchname_temp);
//	HBhvTargetObject::ResolveTarget(attswitchname_temp, attswitchname, dummy, m_pHView->GetModel(), dummytype);							 
 
	sprintf(objectname, "%d", pBehaviorManager->GetFreeName());
	
	HBhvAnimation *animation = pBehaviorManager->FindAnimation(targetname, "AttSwitch");
	if (animation == 0)
	{
		HBhvInterpolatorAttSwitch *i = new HBhvInterpolatorAttSwitch(0, objectname);
		HBhvTimeline *t = new HBhvTimeline(0);
		animation = pBehaviorManager->AddAnimation(objectname, targetname, t, i);			
	}
		
		bool replace;
		int pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);		
		if (replace)
			((HBhvInterpolatorAttSwitch *)(animation->GetInterpolator()))->Replace(attswitchname, pos);
		else
			((HBhvInterpolatorAttSwitch *)(animation->GetInterpolator()))->Insert(attswitchname, pos);

	InvalidateBoxes();

}

	


void CKeyframeEditor::OnActivateSelection() 
{
	int				numSolidSelections, numHoopsSelections;
  	HSSelectionSet* selection = 0;

	selection = (HSSelectionSet *)m_pHView->GetSelection();

	numHoopsSelections = selection->GetSize();
	numSolidSelections = selection->GetSolidListSize();

	HC_KEY key;
	if (numHoopsSelections == 0 || numHoopsSelections >1)
		return;
	else
		 key = selection->GetAt(0);
	selection->DeSelectAll();

//	if (strcmp(m_pHView->GetOperator()->GetName(), "HSOpMoveHandle") != 0)
		OnManipulator();
	((HSOpMoveHandle *)m_pHView->GetHandleOperator())->GetObjectKey();
 	
	HUtilityGeomHandle::ClearAllHandles(m_pHView);
	((HSOpMoveHandle *)m_pHView->GetHandleOperator())->Reset();
	HUtilityGeomHandle::SetupManipulator(key, m_pHView, false, false, false);
 
 	m_pHView->Update();
		
}

void CKeyframeEditor::OnAxisRotKeyframe() 
{

	HC_KEY targetkey = ((HSOpMoveHandle *)m_pHView->GetHandleOperator())->GetObjectKey();
 
	if (targetkey == -1)
		return;

	char targetname[MVO_BUFFER_SIZE];	
	char objectname[256];
 	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	HC_Show_Segment(targetkey, targetname);
	HBhvTargetObject::CreateTargetString("SPATH", targetname, targetname);
 
	sprintf(objectname, "%d", pBehaviorManager->GetFreeName());
	
	HBhvAnimation *animation = pBehaviorManager->FindAnimation(targetname, "AxisRot");
	if (animation == 0)
	{
		HBhvInterpolatorAxisRotate *i = new HBhvInterpolatorAxisRotate(0, objectname);
		HBhvTimeline *t = new HBhvTimeline(0);
		animation = pBehaviorManager->AddAnimation(objectname, targetname, t, i);			
	}
		
		bool replace;
		int pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);		
		if (replace)
			((HBhvInterpolatorAxisRotate *)(animation->GetInterpolator()))->Replace(0, pos);
		else
			((HBhvInterpolatorAxisRotate *)(animation->GetInterpolator()))->Insert(0, pos);

	InvalidateBoxes();	
}

void CKeyframeEditor::OnBhvReload() 
{
	HBhvBehaviorManager::ReadFromFile(m_pHView->GetModel(), (wchar_t*)0 );
 	InvalidateBoxes();	
	
}

void CKeyframeEditor::OnBhvWalk() 
{
    if (m_bDragMode)
    m_bDragMode = false;
    else
    m_bDragMode = true;
    return;
}


void CKeyframeEditor::UpdateButtonStates()
{
    /*
	if (streq(m_pHView->GetOperator()->GetName(), "HSOpMoveHandle"))
     	((CButton *)GetDlgItem(IDC_MANIPULATOR))->SetState(true);
	else
     	((CButton *)GetDlgItem(IDC_MANIPULATOR))->SetState(false);

	if (streq(m_pHView->GetOperator()->GetName(), "HSOpCameraWalk"))
     	((CButton *)GetDlgItem(IDC_BHV_WALK))->SetState(true);
	else
     	((CButton *)GetDlgItem(IDC_BHV_WALK))->SetState(false);
	*/
}

void CKeyframeEditor::UpdateBhvState(bool inv)
{
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();

	m_framerange[0] = m_framerange[1] = (int)pBehaviorManager->GetCurrentTick();
	if (inv)
		InvalidateBoxes();

 
}


void CKeyframeEditor::DrawNewBoxes(CDC *dc)
{

	int hpos, vpos;
	GetScrollbarPosition(hpos, vpos);


 	CBrush brushwhite(RGB(255, 255,255));
	dc->SelectObject(&brushwhite);
 
	dc->Rectangle(XSTART, YSTART, xend, yend);
	

 
	CFont font, fontbold;
	font.CreateFont(14,0,0,0,FW_NORMAL, FALSE, FALSE, 0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,  DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	fontbold.CreateFont(14,0,0,0,FW_BOLD, FALSE, FALSE, 0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,  DEFAULT_PITCH | FF_SWISS, _T("Arial"));
 

	CFont* def_font = dc->SelectObject(&font);
	(void) def_font;

 	dc->SetTextColor(RGB(0,0,0));
 	dc->SetBkColor(RGB(236,233,216));
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	vlist_s *alist = pBehaviorManager->GetAnimationList();
 	vlist_reset_cursor(alist);
	HBhvAnimation *animation = 0;
	int counter = 0;
	for (int i=XSTART;i<xend;i+=(m_boxx*5))
	{
			RECT r;
			r.bottom = YSTART - BOXY - 4;
			r.left = i;
			r.right = i;
			r.top = YSTART - BOXY - 4;
			char text[4096];
			int res = CalculateKeyframeFromMousePosition(i);
			sprintf(text, "%d", res);
 
			dc->DrawText(text,&r,DT_NOCLIP);

	}
	    
 	while (1)
	{
 		if (!(animation = (HBhvAnimation *)vlist_peek_cursor(alist)))
			break;

		m_animationlist[counter] = animation;
		if (counter>=vpos && counter <= (vpos+(yend - YSTART)/BOXY-1))
		{
			RECT r;
			r.bottom = (counter - vpos) *BOXY + YSTART;
			r.left = 3;
			r.right = 3;
			r.top = (counter - vpos) *BOXY + YSTART;
			char tname[MVO_BUFFER_SIZE];
			HC_Parse_String(animation->GetTarget()->GetPath(), "/", -1, tname);
			strcat(tname, " - ");
			strcat(tname, animation->GetInterpolator()->GetType());
			if (counter == m_anirange[0] && m_animationlist[counter] == animation)
				dc->SelectObject(&fontbold);
			else
				dc->SelectObject(&font);
			dc->DrawText(tname, &r, DT_NOCLIP);

 			HBhvTimeline *t1 = animation->GetTimeline();
			int *timelinearray = 0;
			if (t1->GetTimelineArrayLength())
				timelinearray = t1->GetTimelineArray();

 
			int i;
			for (i=0;i<t1->GetTimelineArrayLength()-1;i++)
			{
				int dummy;
				HKeyframe *kp;

				if (animation->GetInterpolator(timelinearray[i], dummy, &kp))
				{				
					int t1 = kp->m_type;
					int t2 = -1;
					bool linear = false;
					if (t1 == HANIChannel)
						t2 = ((HKeyframeChannel *)kp)->m_channeltype;
					if (t1 == HANIRotation)
					{
						t2 = ((HKeyframeRotation *)kp)->m_rotationtype;
						linear = ((HKeyframeRotation *)kp)->m_bLinear;

					}
									
					if ((HANIKeyframeType)t1 == HANIChannel && (HANIChannelType)t2 == HANILinear)					
						DrawBox(dc, timelinearray[i] - hpos, counter - vpos, (timelinearray[i+1] - timelinearray[i]), 255,128,128);
					else if ((HANIKeyframeType)t1 == HANIRotation && (HANIRotationType)t2 == HANIQuatSquadRotation && linear)					
						DrawBox(dc, timelinearray[i] - hpos, counter - vpos, (timelinearray[i+1] - timelinearray[i]), 255,128,128);
					else
						DrawBox(dc, timelinearray[i] - hpos, counter - vpos, (timelinearray[i+1] - timelinearray[i]), 128,128,255);
				}
//				DrawBox(dc, timelinearray[i] - hpos, counter - vpos, (timelinearray[i+1] - timelinearray[i]), 200,200,200);

			}
			
			for (i=0;i<t1->GetTimelineArrayLength();i++)
			{
				if (timelinearray[i]>=hpos && timelinearray[i]<(hpos+(xend - XSTART)/m_boxx-1))
					DrawBox(dc, timelinearray[i] - hpos, counter - vpos, 128,128,128);
			}
	

		}
		counter++;
		vlist_advance_cursor(alist);	

	}
	m_animationnum = counter;

	
//	if (pBehaviorManager->GetCurrentTick()>=hpos && pBehaviorManager->GetCurrentTick()<(hpos+(xend - XSTART)/m_boxx-1))
		DrawOuterBox(dc, m_framerange[0], m_framerange[1], m_anirange[0], m_anirange[1]);


}

void CKeyframeEditor::OnSelchangeZoomcombo() 
{
	CComboBox *cbox =(CComboBox *)GetDlgItem(IDC_ZOOMCOMBO);
	int sel = cbox->GetCurSel();
	switch(sel)
	{
	case 0:
		m_boxx = 8;
	break;
	case 1:
		m_boxx = 6;
	break;
	case 2:
		m_boxx = 4;
	break;
	case 3:
		m_boxx = 2;
	break;
	}
	InvalidateBoxes();

}

void CKeyframeEditor::OnSelchangeTextzoom() 
{
	CComboBox *cbox =(CComboBox *)GetDlgItem(IDC_TEXTZOOM);
	int sel = cbox->GetCurSel();
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	HC_Open_Segment("cameratext");
	HC_Set_Camera_Field(2,2);
		HC_Set_Camera_Projection("perspective");
		HC_Set_Handedness("left");
	switch(sel)
	{
	case 0:
		 HC_Set_Camera_Position(0,0,-1);
		 HC_Set_Camera_Target(0,0,4);
	break;
	case 1:
		 HC_Set_Camera_Position(0,0,-3);
		 HC_Set_Camera_Target(0,0,2);
	break;
	}
 
	HC_Close_Segment();
	HC_Close_Segment();
	m_pHView->Update();
	
}

void CKeyframeEditor::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKeyframeEditor::OnBhvEditxml() 
{
	HUtilityXMLGenerator xmlgen;
	xmlgen.Reset();
	m_pHView->GetModel()->GetBhvBehaviorManager()->Serialize(&xmlgen);
	xmlgen.Finalize();
	XMLEditorDlg my_dlg(this, xmlgen.GetBuffer());
 
	if (my_dlg.DoModal() == IDOK)
	{
		m_pHView->GetModel()->GetBhvBehaviorManager()->ProcessXMLData(m_pHView->GetModel(), H_ASCII_TEXT(my_dlg.m_richedit));
	}
	InvalidateBoxes();


/*
 	static XMLEditorDlg my_dlg(this, xmlgen.GetBuffer());
	my_dlg.Create(IDD_XML_DISPLAY);
	my_dlg.ShowWindow(SW_SHOW); 
*/
}

HBhvAnimation * CKeyframeEditor::GetActiveAnimation() 
{
	if (m_anirange[0] < m_animationnum)
		return	m_animationlist[m_anirange[0]];
	else
		return 0;
}

void CKeyframeEditor::InvalidateBoxes() 
{
    RECT rect;
    rect.bottom = yend;
    rect.top = YSTART - BOXY - 4;
    rect.left = 0;
    rect.right = xend;    
    InvalidateRect(&rect);
    
}

 

void CKeyframeEditor::OnTesterid() 
{
	// TODO: Add your command handler code here
	
}




 
 

LRESULT CDlgToolBar::OnIdleUpdateCmdUI(WPARAM wParam,LPARAM lParam)
      {
         if (IsWindowVisible())
         {
            CFrameWnd* pParent = (CFrameWnd*)GetParent();
            if (pParent)
               OnUpdateCmdUI(pParent, (BOOL)wParam);
         }
         return 0L;
      }


void CKeyframeEditor::OnBhvDragmode() 
{
    if (m_bDragMode)
    m_bDragMode = false;
    else
    m_bDragMode = true;
    return;
	
}

void CKeyframeEditor::OnUpdateBhvDragmode(CCmdUI* pCmdUI) 
{
    if(m_bDragMode)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
	
}

void CKeyframeEditor::OnBhvCameraPosMode() 
{
 	m_cameratype = 0;
	
}

void CKeyframeEditor::OnUpdateBhvCameraPosMode(CCmdUI* pCmdUI) 
{
    if(m_cameratype == 0)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CKeyframeEditor::OnBhvCameraTargetMode() 
{
 	m_cameratype = 1;
	
}

void CKeyframeEditor::OnUpdateBhvCameraTargetMode(CCmdUI* pCmdUI) 
{
    if(m_cameratype == 1)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}

void CKeyframeEditor::OnBhvUpdateView() 
{
    if (m_update_view)
	m_update_view = false;
    else
	m_update_view = true;
	
}

void CKeyframeEditor::OnUpdateBhvUpdateView(CCmdUI* pCmdUI) 
{
    if(m_update_view == 1)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}

void CKeyframeEditor::OnBhvMagnify1x() 
{
    m_boxx = 8;	
    InvalidateBoxes();

}

void CKeyframeEditor::OnUpdateBhvMagnify1x(CCmdUI* pCmdUI) 
{
    if(m_boxx == 8)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}

void CKeyframeEditor::OnBhvMagnify2x() 
{
   m_boxx = 6;	
    InvalidateBoxes();
	
}

void CKeyframeEditor::OnUpdateBhvMagnify2x(CCmdUI* pCmdUI) 
{
    if(m_boxx == 6)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}

void CKeyframeEditor::OnBhvMagnify4x() 
{
   m_boxx = 4;	
    InvalidateBoxes();
	
}

void CKeyframeEditor::OnUpdateBhvMagnify4x(CCmdUI* pCmdUI) 
{
    if(m_boxx == 4)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}

void CKeyframeEditor::OnBhvMagnify8x() 
{
   m_boxx = 2;	
    InvalidateBoxes();
	
}

void CKeyframeEditor::OnUpdateBhvMagnify8x(CCmdUI* pCmdUI) 
{
    if(m_boxx == 2)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}


BOOL CKeyframeEditor::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
    ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

    // if there is a top level routing frame then let it handle the message
    if (GetRoutingFrame() != NULL) return FALSE;

    // to be thorough we will need to handle UNICODE versions of the message also !!
    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
    TCHAR szFullText[512];
    CString strTipText;
    UINT_PTR nID = pNMHDR->idFrom;

    if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
        pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
    {
        // idFrom is actually the HWND of the tool 
        nID = ::GetDlgCtrlID((HWND)nID);
    }

    if (nID != 0) // will be zero on a separator
    {
#ifndef GRANITE
        AfxLoadString(nID, szFullText);
#endif
        strTipText=szFullText;

#ifndef _UNICODE
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
            lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
        }
        else
        {
            _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#else
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
            _wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
        }
        else
        {
            lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#endif

        *pResult = 0;

        // bring the tooltip window above other popup windows
        ::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
            SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);
        
        return TRUE;
    }

    return FALSE;
}




void CKeyframeEditor::OnBhvAutomaticRecord() 
{
     if (m_bRecordMode)
    m_bRecordMode = false;
    else
    m_bRecordMode = true;
	
}

void CKeyframeEditor::OnBhvRecordCamera() 
{
	if (m_pHView->GetRecordMode())
		m_pHView->SetRecordCamera(false);
	else
		m_pHView->SetRecordCamera(true);
	UpdateBhvState(true);
}

void CKeyframeEditor::OnUpdateBhvRecordCamera(CCmdUI* pCmdUI) 
{
    if(m_pHView->GetRecordMode())
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}

void CKeyframeEditor::OnUpdateBhvAutomaticRecord(CCmdUI* pCmdUI) 
{
    if(m_bRecordMode)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
	
}

void CKeyframeEditor::OnBhvDrawCurve() 
{
    if (GetActiveAnimation())
    {    
	
	HBhvBehaviorManager *bhvmanager = m_pHView->GetModel()->GetBhvBehaviorManager();
	HBhvAnimation *ani = bhvmanager->FindAnimation(GetActiveAnimation()->GetTarget()->GetPath(), "Pos");
	
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	HC_Open_Segment("tempplot");
	HC_Flush_Contents(".", "everything");
	if (!GetAsyncKeyState(VK_SHIFT))
	    ani->PlotCurve(false);
	HC_Close_Segment();
	HC_Close_Segment();
	m_pHView->Update();
    }
    // TODO: Add your command handler code here
    
}

void CKeyframeEditor::OnBhvDrawCurveRot() 
{ 
    
    if (GetActiveAnimation())
    {
	HBhvBehaviorManager *bhvmanager = m_pHView->GetModel()->GetBhvBehaviorManager();		
	HBhvAnimation *ani = bhvmanager->FindAnimation(GetActiveAnimation()->GetTarget()->GetPath(), "Pos");
	
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	HC_Open_Segment("tempplot");
	HC_Flush_Contents(".", "everything");
	if (!GetAsyncKeyState(VK_SHIFT))
	    ani->PlotCurve(true);
	HC_Close_Segment();
	HC_Close_Segment();
	m_pHView->Update();
    }
    
}

int CKeyframeEditor::KeyframeEditorExistsQuery(bool &res)
{
    res = true;
    return HLISTENER_CONSUME_EVENT;
}


int CKeyframeEditor::KeyframeAddedEvent()
{
	if (GetRecordMode())
	{		
	    HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	    pBehaviorManager->SetCurrentTick(pBehaviorManager->GetCurrentTick()+10);
	    UpdateBhvState(true);
	    PlayToTick();
	}
    InvalidateBoxes();
    return HLISTENER_PASS_EVENT;
}


void CKeyframeEditor::OnMakeCollision() 
{
    for (int i=m_anirange[0];i<=m_anirange[1];i++)
    {
	
	if (m_animationlist[i])
	{
	    
		HBhvTargetObject *tob = m_animationlist[i]->GetTarget();

		bool col = tob->GetCollision();
		tob->SetCollision(!col);
	}
    }
    InvalidateBoxes();
}




void CKeyframeEditor::OnCancel()
{
    ;
}

/* If we ever fix the HOutputHandler/HInputHandler problems, this should be removed. */
typedef	struct AVIExportInfo {

	int starttick;		//!< Starttick for animation.
	int endtick;		//!< Endtick for animation.
	int resolution;		//!< The number of frames per second.
} AVIExportInfo;	//!< AVIExportInformation  Typedef for AVIExportInfo

void CKeyframeEditor::OnExportAVI() 
{
    
    HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
    CAviOptionsDlg my_dlg(this);
    
	
    pBehaviorManager->ScheduleAllAnimations(true);
    my_dlg.m_AVIEndTick = pBehaviorManager->GetLastTick();
    if (my_dlg.DoModal() == IDOK)
    {
		
		CString filter;
		CString def_ext;
		
		filter = "AVI FIle (*.avi)|*.avi||";
		def_ext = ".avi";
		
		TCHAR cur_dir[MVO_BUFFER_SIZE];
		GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
		CFileDialog my_ddlg(FALSE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
			filter , NULL);
		
		my_ddlg.m_ofn.lpstrInitialDir = cur_dir;
		
		CString TextureSourceShortName;
		if (my_ddlg.DoModal() == IDOK)
		{
			HOutputHandler *avioutput =  HIOManager::GetCurrentHIOManager()->GetOutputHandler("avi");		
			if (avioutput)
			{			
				CString aviname = my_ddlg.GetPathName();
				
				AVIExportInfo einfo;
				HOutputHandlerOptions options;
				options.m_Window_Width  =  my_dlg.m_AVIWidth;
				options.m_Window_Height =  my_dlg.m_AVIHeight;
				options.m_pExtendedData = &einfo;
				options.m_pHBaseView = m_pHView;
				
				einfo.starttick = my_dlg.m_AVIStartTick;;
				einfo.endtick = my_dlg.m_AVIEndTick;
				einfo.resolution = my_dlg.m_AVIResolution;
				if(avioutput->FileOutputByKey(H_ASCII_TEXT(aviname), -1, &options) != OutputOK){
					AfxMessageBox(_T("AVI Output handler returned an error..."));
				}
			}
			else {
				AfxMessageBox(_T("Sorry! No AVI output handler was found."));
			}
						
		}
	}
}
	








