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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mfc/source/CHoopsFrm.cpp,v 1.22 2009-08-03 18:32:12 boni Exp $
//

// CHoopsFrm.cpp : implementation of the CHoopsFrame class
//

#include "stdafx.h"
#include <afxwin.h>
#include "CHoopsApp.h"
#include "CHoopsFrm.h"
#include "CHoopsView.h"

#define BIT(v, mask)	(((v) & (mask)) != 0)
#ifndef ABS
# define ABS(a)			((a) < 0 ? -(a) : (a))
#endif

/////////////////////////////////////////////////////////////////////////////
// CHoopsFrame

#ifdef HOOPS_MFC_SDI
IMPLEMENT_DYNCREATE(CHoopsFrame, CFrameWnd)
#else
IMPLEMENT_DYNAMIC(CHoopsFrame, CMDIFrameWnd)
#endif



BEGIN_MESSAGE_MAP(CHoopsFrame, CBaseHoopsFrameWnd)
	//{{AFX_MSG_MAP(CHoopsFrame)
	ON_WM_CREATE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_MOVE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHoopsFrame construction/destruction

CHoopsFrame::CHoopsFrame()
{
	// member initialization
    m_bSharePalette = TRUE;
    m_pPalette = NULL;
	                   
}

CHoopsFrame::CHoopsFrame(BOOL share)
{
	// set the user-specified palette sharing mode
    if (share == TRUE)
        m_bSharePalette = TRUE;
    else
        m_bSharePalette = FALSE;

    m_pPalette = NULL;	
}


CHoopsFrame::~CHoopsFrame()
{
	// delete the shared palette 
	if (m_pPalette)
		delete m_pPalette;
}

int CHoopsFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBaseHoopsFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    // Create Common Palette that is to be shared
    if (m_bSharePalette) {

        CDC * cdc = GetDC();
        ASSERT (cdc);

        int rc = cdc->GetDeviceCaps(RASTERCAPS);
    
        if (rc & RC_PALETTE) {
            ASSERT (GetSystemPaletteUse (cdc->m_hDC ) == SYSPAL_STATIC );

            m_pPalette = new CPalette;

            LPLOGPALETTE 		Palette;
            int		            nStaticColors;
	        DWORD	            *dword_ptr;
	        int		            nColors;
            int                 i;

	        /* Get the static colors from the system palette */
	        nStaticColors = cdc->GetDeviceCaps (NUMCOLORS);
	        nColors = cdc->GetDeviceCaps (SIZEPALETTE);

	        Palette = (LPLOGPALETTE) malloc (sizeof(LOGPALETTE) + sizeof (PALETTEENTRY) * nColors);
	        Palette->palVersion = 0x300;
	        Palette->palNumEntries = nColors;

            nColors = GetSystemPaletteEntries (cdc->m_hDC, 0, nColors, Palette->palPalEntry);

	        for (i=0; i<nColors; i++) {
	            Palette->palPalEntry[i].peFlags = PC_NOCOLLAPSE;
	        }

	       /*
	        * Set the peFlags of the lower static colors to reserved and the
	        * logical color array to the system colors
	        */
	        nStaticColors = nStaticColors / 2;
	        for (i = 0; i < nStaticColors; i++) {
	            dword_ptr = (DWORD *)&Palette->palPalEntry[i];
	            *dword_ptr = i;
	            Palette->palPalEntry[i].peFlags = PC_EXPLICIT;
	        }

	        /* Set the peFlags of the upper static colors to reserved */
	        for (i = nColors - nStaticColors; i < nColors; i++) {
	            /* We are going to use a rather nasty mapping logic here */
	            dword_ptr = (DWORD *)&Palette->palPalEntry[i];
	            *dword_ptr = i;
	            Palette->palPalEntry[i].peFlags = PC_EXPLICIT;
	        }
	        m_pPalette->CreatePalette ( Palette );
	        free (Palette);

	        m_pPalette->UnrealizeObject();
	        cdc->SelectPalette (m_pPalette, FALSE);
	        cdc->RealizePalette ();

        }

        ReleaseDC (cdc);
    }

	return 0;
}


BOOL CHoopsFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CBaseHoopsFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHoopsFrame diagnostics

#ifdef _DEBUG
void CHoopsFrame::AssertValid() const
{
	CBaseHoopsFrameWnd::AssertValid();
}

void CHoopsFrame::Dump(CDumpContext& dc) const
{
	CBaseHoopsFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHoopsFrame message handlers

//
void CHoopsFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	 // always realize the palette for the active view
#ifdef HOOPS_MFC_SDI
    CFrameWnd* pChildWnd = GetActiveFrame();
#else
    CMDIChildWnd* pChildWnd = MDIGetActive();
#endif
	
    if (pChildWnd == NULL)
        return; // no active child frame
    CView* pView = pChildWnd->GetActiveView();
    ASSERT (pView != NULL);

    // notify all child windows that the palette has changed
    SendMessageToDescendants(WM_DOREALIZE, (WPARAM)pView->m_hWnd);
}



BOOL CHoopsFrame::OnQueryNewPalette() 
{

	 // always realize the palette for the active view
#ifdef HOOPS_MFC_SDI
    CFrameWnd* pChildWnd = GetActiveFrame();
#else
    CMDIChildWnd* pChildWnd = MDIGetActive();
#endif

	if (pChildWnd == NULL)
		return FALSE; // no active child frame (no new palette)
	CView* pView = pChildWnd->GetActiveView();
	ASSERT(pView != NULL);

	// just notify the target view
   	pView->SendMessage(WM_DOREALIZE, (WPARAM)pView->m_hWnd);
	return TRUE;
}


void CHoopsFrame::SetPaletteShared(BOOL share)
{
    if (share)
        m_bSharePalette = TRUE;
    else
        m_bSharePalette = FALSE;
}


void CHoopsFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}


/* This big ugly hack is needed for hardware-accelerated dual-monitor systems
 * until we figure out a way to detect specifically when the app has moved from one monitor to
 * the other, we have to set the dirty bit whenever we move.  We can't trust the contents
 * of the back buffer. */
void CHoopsFrame::OnMove(int x, int y) 
{
	CBaseHoopsFrameWnd::OnMove(x, y);

#if 0
	CWinApp *app = AfxGetApp();
	if( !app )
		return;

	POSITION template_pos = app->GetFirstDocTemplatePosition();
	while (template_pos != NULL) 
	{		
		CDocTemplate *p_doctemplate = app->GetNextDocTemplate(template_pos);
		
		if( p_doctemplate)
		{
			POSITION doc_pos = p_doctemplate->GetFirstDocPosition();
			while( doc_pos != NULL )
			{
				CDocument* pDoc = p_doctemplate->GetNextDoc(doc_pos);
				if( pDoc )
				{
					POSITION view_pos = pDoc->GetFirstViewPosition();
					while( view_pos != NULL )
					{
						CHoopsView* pView = (CHoopsView*) (pDoc->GetNextView(view_pos));
						if( pView )
						{
							HBaseView* pBaseView = pView->GetHoopsView();
							const char *path = pBaseView->GetDriverPath();
							if( strstr( path, "opengl" ))
								HC_Control_Update( path, "redraw everything" ); 
						}
					}
				}
			}
		}	
	}
#endif
}

BOOL CHoopsFrame::OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	switch(message)
	{
	case WM_POWERBROADCAST:
		{
			switch(wParam)
			{
			case PBT_APMQUERYSUSPEND:
				// allow the suspend to happen
				*pResult = TRUE;
				return TRUE;
				
			case PBT_APMRESUMESUSPEND:
				// notify all child windows that we are resuming from a standby
				SendMessageToDescendants(WM_POWERBROADCAST, wParam, lParam);
				break;
			}
		}
	}

	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}



// Global object handles full-screen mode
CFullScreenHandler FullScreenHandler;

CFullScreenHandler::CFullScreenHandler()
{
    m_rcRestore.SetRectEmpty();
}

CFullScreenHandler::~CFullScreenHandler()
{
}

//////////////////
// Resize frame so view's client area fills the entire screen. Use
// GetSystemMetrics to get the screen size — the rest is pixel
// arithmetic.
//
void CFullScreenHandler::Maximize(CFrameWnd* pFrame, CWnd* pView)
{
    // get view rectangle
    if (pView) {
        CRect rcv;
        pView->GetWindowRect(&rcv);

        // This call returns the size of the remaining client area beyond the toolbars
		CRect client;
		pFrame->RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, AFX_IDW_PANE_FIRST, CWnd::reposQuery , &client); 

        pFrame->GetWindowRect(m_rcRestore); // save for restore
        

		CRect rcf;
		m_styleRestore = pFrame->GetStyle();

        // The size of a full screen
		HMONITOR hMonitor = MonitorFromWindow(pView->m_hWnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi;
		mi.cbSize = sizeof(mi);
		GetMonitorInfo(hMonitor, &mi);
		CRect rc(mi.rcMonitor);

		// The size of the FULL client area in screen coordinates
		pFrame->GetClientRect(&rcf);
		pFrame->ClientToScreen(rcf);

		// Use the screen coordinates of the top-left corner of the full client area
		// as an offset for the real client area, to get the real client area in 
		// screen coordinates
		client.top += rcf.top;
		client.bottom += rcf.top;
		client.left += rcf.left;
		client.right += rcf.left;

		// Expand the size of the fullscreen so that only the REAL client area
		// is visible on the screen (move outwards by whatever the size of the toolbars
		// and the window borders is).
		rc.left -= (client.left - m_rcRestore.left);
		rc.right += (m_rcRestore.right - client.right);// + (client.left = m_rcRestore.left);
		rc.top -= (client.top - m_rcRestore.top);
		rc.bottom += (m_rcRestore.bottom - client.bottom) + (client.top - m_rcRestore.top);

		// Store this maximum size so we can use it in GetMinMax.
		m_MaxSize = rc;

#ifdef HOOPS_MFC_SDI
    CFrameWnd* pChildWnd = pFrame->GetActiveFrame();
#else
    CMDIChildWnd* pChildWnd = ((CHoopsFrame*)pFrame)->MDIGetActive();
#endif
	if (pChildWnd == NULL)
		return ; // no active child frame 
			
		pFrame->SetWindowPos(NULL, rc.left, rc.top,
			rc.right-rc.left, rc.bottom-rc.top, SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_FRAMECHANGED|SWP_SHOWWINDOW);

		pFrame->ModifyStyle(WS_CAPTION|WS_MAXIMIZE|WS_THICKFRAME|WS_BORDER,0,0);

#ifndef HOOPS_MFC_SDI
		if(!BIT(pChildWnd->GetStyle(), WS_MAXIMIZE)){
			m_maximized = false;
			pChildWnd->MDIMaximize();
		}
		else{
			m_maximized = true;
		}
#endif

    }
}

void CFullScreenHandler::Restore(CFrameWnd* pFrame)
{
    const CRect& rc = m_rcRestore;
	pFrame->ModifyStyle(0,WS_CAPTION,0);
	pFrame->ModifyStyle(0,WS_THICKFRAME,0);
#ifdef HOOPS_MFC_SDI
    CFrameWnd* pChildWnd = pFrame->GetActiveFrame();
#else
    CMDIChildWnd* pChildWnd = ((CHoopsFrame*)pFrame)->MDIGetActive();
#endif
	if (pChildWnd == NULL)
		return ; // no active child frame 
	
	
#ifndef HOOPS_MFC_SDI
	if(!m_maximized){
		pChildWnd->MDIRestore();
	}
#endif
	
	
    pFrame->SetWindowPos(&CWnd::wndBottom, rc.left, rc.top,
        rc.Width(), rc.Height(), NULL);
	pFrame->SetWindowPos(&CWnd::wndTop, rc.left, rc.top,
        rc.Width(), rc.Height(), SWP_NOMOVE|SWP_SHOWWINDOW|SWP_DRAWFRAME|SWP_FRAMECHANGED);
    m_rcRestore.SetRectEmpty();

	
}

CSize CFullScreenHandler::GetMaxSize(CWnd* pView)
{
	if(!InFullScreenMode()){
		HMONITOR		hMonitor = MonitorFromWindow(pView->m_hWnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO		mi;
		mi.cbSize = sizeof(mi);
		GetMonitorInfo(hMonitor, &mi);
		CRect rc(0,0, mi.rcMonitor.right-mi.rcMonitor.left, mi.rcMonitor.bottom-mi.rcMonitor.top);
		return rc.Size();
	}
	else
		return m_MaxSize.Size();
}



/////////////////
// Important to handle this in order to set size
// of window larger than whole screen.
//
void CHoopsFrame::OnGetMinMaxInfo(MINMAXINFO* lpmmi)
{
   CSize sz = FullScreenHandler.GetMaxSize(this);
   lpmmi->ptMaxSize = CPoint(sz);
   lpmmi->ptMaxTrackSize = CPoint(sz);
   CWnd::OnGetMinMaxInfo(lpmmi);
}

//////////////////
// View full screen mode. Calls CFullScreenHandler to do the work.
//
void CHoopsFrame::OnViewFullScreen()
{
	CWinApp *app = AfxGetApp();
	if( !app )
		return;

	POSITION template_pos = app->GetFirstDocTemplatePosition();
	while (template_pos != NULL) 
	{		
		CDocTemplate *p_doctemplate = app->GetNextDocTemplate(template_pos);
		
		if( p_doctemplate)
		{
			POSITION doc_pos = p_doctemplate->GetFirstDocPosition();
			while( doc_pos != NULL )
			{
				CDocument* pDoc = p_doctemplate->GetNextDoc(doc_pos);
				if( pDoc )
				{
					POSITION view_pos = pDoc->GetFirstViewPosition();
					while( view_pos != NULL )
					{
						CHoopsView* pView = (CHoopsView*) (pDoc->GetNextView(view_pos));
						if( pView )
						{
							HBaseView* pBaseView = pView->GetHoopsView();
							(void)pBaseView;
							
							if (FullScreenHandler.InFullScreenMode()){
								FullScreenHandler.Restore(this);
								return;
							}
							
							else {
								FullScreenHandler.Maximize(this, pView);
								return;
							}

						}
					}
				}
			}
		}	
	}




   
}