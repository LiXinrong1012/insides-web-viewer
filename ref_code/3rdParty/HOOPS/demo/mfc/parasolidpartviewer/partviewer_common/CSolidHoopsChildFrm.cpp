// CSolidHoopsChildFrm.cpp : implementation file
//

#include "StdAfx.h"
#include "CSolidHoopsChildFrm.h"
#include "CSolidHoopsApp.h"
#include "CSolidHoopsView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsChildFrame

IMPLEMENT_DYNCREATE(CSolidHoopsChildFrame, CMDIChildWnd)

CSolidHoopsChildFrame::CSolidHoopsChildFrame()
{
	m_bCreated = false;
	m_ViewNum = 0;
}

CSolidHoopsChildFrame::~CSolidHoopsChildFrame()
{
}


BEGIN_MESSAGE_MAP(CSolidHoopsChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSolidHoopsChildFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsChildFrame message handlers
BOOL CSolidHoopsChildFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// Increase the window size at this point. This is done during HNet integration. We want 
	// the HNetClientDialog to completely fit the view by default - Rajesh B (2-Aug-01)
	cs.cy = 550;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////
// Important to handle this in order to set size
// of window larger than whole screen.
//
void CSolidHoopsChildFrame::OnGetMinMaxInfo(MINMAXINFO* lpmmi)
{
	RECT  lpRect;
	CSize sz;

	this->GetParentFrame()->GetWindowRect(&lpRect);
	sz.cx = lpRect.right - lpRect.left + 10; // The 10 adds room for window borders on each side
	sz.cy = lpRect.bottom - lpRect.top;
	lpmmi->ptMaxSize = CPoint(sz);
	lpmmi->ptMaxTrackSize = CPoint(sz);
	CMDIChildWnd::OnGetMinMaxInfo(lpmmi);
}

int CSolidHoopsChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// the HNetClient dialog docks on child frame
	EnableDocking(CBRS_ALIGN_ANY);
	
	return 0;
}

BOOL CSolidHoopsChildFrame::OnCreateClient(LPCREATESTRUCT  lpcs , CCreateContext* pContext)
{
	this->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}
   
void CSolidHoopsChildFrame::OnSize(UINT nType, int cx, int cy) 
{	
	CMDIChildWnd::OnSize(nType, cx, cy);
}

// override this to add the driver type to the current title
void CSolidHoopsChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWnd::OnUpdateFrameTitle( bAddToTitle );

#ifndef HOOPS_QA
	// append the driver type to the current title
	CSolidHoopsView* pView = (CSolidHoopsView*) GetTopWindow( );
	
	if( pView )
	{
		ASSERT_VALID(pView);
		HBaseView * pHView = pView->GetHoopsView();

		if( pHView )
		{
			CString driver(pHView->GetDriverType());
			CString title;
			GetWindowText(title);
			SetWindowText(title + "(" + driver + ")");
		}
	}
#endif // HOOPS_QA
}
