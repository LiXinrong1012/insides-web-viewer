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
// $Header: /files/homes/master/cvs/hoops_master/mfc_simple/MainFrm.cpp,v 1.3 2006-08-07 20:38:55 stage Exp $
//

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "simple.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bSharedPalette = true;
	m_pPalette = NULL;
}

CMainFrame::~CMainFrame()
{
	// if it exists delete the shared palette 
	if (m_pPalette)
		delete m_pPalette;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

    // Create Common Palette that is to be shared
    if (m_bSharedPalette) 
	{
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

	        ReleaseDC (cdc);
        }
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

