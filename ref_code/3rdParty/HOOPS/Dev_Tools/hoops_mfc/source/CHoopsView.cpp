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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mfc/source/CHoopsView.cpp,v 1.166 2010-12-02 18:00:07 reuben Exp $
//

// CHoopsView.cpp : implementation of the CHoopsView class
//

#include "stdafx.h"

#include "CHoopsApp.h"
#include "CHoopsDoc.h"
#include "CHoopsView.h"
#include "CHoopsFrm.h"
#include "CTDriver.h"
#include "HDB.h"
#include "HSelectionSet.h"
#include "HIOUtilityGDIOutput.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HOpNavCube.h"
#include "HBaseView.h"
#include "HTManager.h"
#include "HEventManager.h"
#include "HEventListener.h"
#include "HConstantFrameRate.h"
#include <math.h>



/////////////////////////////////////////////////////////////////////////////
// CHoopsView

IMPLEMENT_DYNCREATE(CHoopsView, CView)

BEGIN_MESSAGE_MAP(CHoopsView, CView)
	//{{AFX_MSG_MAP(CHoopsView)
	ON_WM_PAINT()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_DISPLAYCHANGE, OnAFXDisplayChange)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

#ifdef DIRECT_INPUT_SUPPORT
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


enum VectorType {
	BothVectors = 0,
	BothZeroVectors,
	TranslationVector, 
	RotationVector,
};

class DIDeviceInfo
{
public:
	DIDEVICEINSTANCE     DIDevInstance;
	LPDIRECTINPUTDEVICE8 pUsbHidDevice;
	DIDEVCAPS            diDevCaps;
	HANDLE				 hUsbHidDeviceEvent;
	DIJOYSTATE			 lastJoyState;
	VectorType			 lastVectorType;
};

class DIDevice{
public:
	LPDIRECTINPUT8  g_pDI;
};

 
void HandleAxesState( CHoopsView*, DIJOYSTATE js );
void CombineDataStreams( CHoopsView*, DIJOYSTATE &js );
#endif

/////////////////////////////////////////////////////////////////////////////
// CHoopsView construction/destruction

CHoopsView::CHoopsView()
{
    m_pViewPalette = NULL;
	m_bFastPrint = true;
	m_bMetaPrint = false;
	m_MetafileType = EMF;
	m_bClipboardTruecolor = true;
	m_pHView = NULL;
	m_ViewKey = 0L;
	m_SceneKey = 0L;

#ifdef DIRECT_INPUT_SUPPORT
	dev_handle = new DIDevice();
	g_pDevice = new DIDeviceInfo();
	m_bUsingDI8Joystick = true;
#else
	dev_handle = 0;
	g_pDevice = 0;
	m_bUsingDI8Joystick = false;
#endif
	
}

CHoopsView::~CHoopsView()
{
	// delete the palette object if appropriate
    delete m_pViewPalette;
	delete g_pDevice;
	delete dev_handle;
}


void CHoopsView::OnDraw(CDC* pDC)
{
	CHoopsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CHoopsView printing

BOOL CHoopsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// I am not sure when and why MFC default has changed to show two pages
	// ...at present we have only one page in HOOPS though
	// Rajesh B (03-Mar-05)
	pInfo->m_nNumPreviewPages = 1;

	return DoPreparePrinting(pInfo);
}

void CHoopsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

void CHoopsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHoopsView diagnostics

#ifdef _DEBUG
void CHoopsView::AssertValid() const
{
	CView::AssertValid();
}

void CHoopsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


CHoopsDoc* CHoopsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHoopsDoc)));
	return (CHoopsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHoopsView message handlers


void CHoopsView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CHoopsDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CHoopsFrame * pAppFrame = (CHoopsFrame *)AfxGetMainWnd();

#ifdef DIRECT_INPUT_SUPPORT
	if(m_bUsingDI8Joystick)
		InitDI8();
	if(m_bUsingDI8Joystick)
		SetTimer( 0, 1000 / 30, NULL );
#endif

    if (!pAppFrame->IsPaletteShared())
        InitializePalette ();


}
	
void CHoopsView::OnSize(UINT, int x , int y)
{
	if (m_pHView)
	{
		m_pHView->SetXYSizeOverride(x,y);
		//m_pHView->Notify( HSignalResize );
	}
}


void CHoopsView::AdjustAxisWindow()
{
	m_pHView->AdjustAxisWindow( 125 );
}


void CHoopsView::GetIntRectangle( HIntRectangle *rectangle )
{
	RECT rect;

	GetClientRect(&rect);
	rectangle->left = rect.left;
	rectangle->top = rect.top;
	rectangle->right = rect.right;
	rectangle->bottom = rect.bottom;
}
	


void CHoopsView::OnPaint() 
{
	HIntRectangle rectangle; 
    
	// execute a HOOPS update if we have a valid HBaseView object
	if (m_pHView && m_pHView->GetViewActive() && !m_pHView->GetSuppressUpdate())
	{
		HC_Control_Update_By_Key (GetViewKey(), "redraw everything");
		m_pHView->GetConstantFrameRateObject()->SetActivityType(GeneralActivity);

		GetIntRectangle( &rectangle );
		m_pHView->Notify( HSignalPaint, &rectangle );
		m_pHView->ResetIdleTime();

		if (!m_pHView->GetFirstUpdate())
			m_pHView->ForceUpdate();
		else
			m_pHView->Update();
	}

	CPaintDC dc(this); // Calls CWnd::BeginPaint on ctor, CWnd::EndPaint on dtor
}


 


void CHoopsView::InitializePalette()
{
    if (m_pViewPalette != NULL) {
        delete m_pViewPalette;
        m_pViewPalette = NULL;
    }

    // Setup the Palette

    CHoopsDoc * pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    CHoopsFrame * pAppFrame = (CHoopsFrame *)AfxGetApp()->m_pMainWnd;
    ASSERT(pAppFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd)));

    CClientDC docDC(pAppFrame);

    int rc = docDC.GetDeviceCaps(RASTERCAPS);

    if (rc & RC_PALETTE) {

        ASSERT (GetSystemPaletteUse (docDC.GetSafeHdc()) == SYSPAL_STATIC );

        m_pViewPalette = new CPalette;

        LPLOGPALETTE 		Palette;
        int		            nStaticColors;
	    DWORD	            *dword_ptr;
	    int		            nColors;
        int                 i;

	    // Get the static colors from the system palette 
	    nStaticColors = docDC.GetDeviceCaps(NUMCOLORS);
	    nColors = docDC.GetDeviceCaps(SIZEPALETTE);

	    Palette = (LPLOGPALETTE) malloc (sizeof(LOGPALETTE) + sizeof (PALETTEENTRY) * nColors);
	    Palette->palVersion = 0x300;
	    Palette->palNumEntries = nColors;


	    nColors = GetSystemPaletteEntries (docDC.GetSafeHdc(), 0, nColors, Palette->palPalEntry);

	    for (i=0; i<nColors; i++) {
	        Palette->palPalEntry[i].peFlags = PC_NOCOLLAPSE;
	    }

	    
	    // Set the peFlags of the lower static colors to reserved and the
	    // logical color array to the system colors
	     
	    nStaticColors = nStaticColors / 2;
	    for (i = 0; i < nStaticColors; i++) {
	        dword_ptr = (DWORD *)&Palette->palPalEntry[i];
	        *dword_ptr = i;
	        Palette->palPalEntry[i].peFlags = PC_EXPLICIT;
	    }

	    // Set the peFlags of the upper static colors to reserved 
	    for (i = nColors - nStaticColors; i < nColors; i++) {
	        dword_ptr = (DWORD *)&Palette->palPalEntry[i];
	        *dword_ptr = i;
	        Palette->palPalEntry[i].peFlags = PC_EXPLICIT;
	    }
	    m_pViewPalette->CreatePalette(Palette);
	    free (Palette);

	    m_pViewPalette->UnrealizeObject();
	    docDC.SelectPalette (m_pViewPalette, FALSE);
	    docDC.RealizePalette ();
    }
}


CPalette* CHoopsView::GetPalette()
{
    CHoopsFrame* pAppFrame = (CHoopsFrame *)AfxGetMainWnd();

    if (pAppFrame->IsPaletteShared())
        return (pAppFrame->GetSharedPalette());
    else
        return m_pViewPalette;
}

void CHoopsView::OnEditCopy() 
{
	GDIExportInformation options;
	char info[4096];

	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
	HC_Show_Device_Info(".", "size", info);
	HC_Close_Segment();

	sscanf(info, "%f, %f", &options.m_Window_Width, &options.m_Window_Height);

	options.deviceContext = GetDC()->GetSafeHdc();
	options.attribDC = GetDC()->m_hAttribDC;
	options.windowID = (void*)m_hWnd;
	options.rasterOutput = m_bFastPrint;
	options.clipBoard= true;
	options.m_Paper_Width=options.m_Window_Width;
	options.m_Paper_Height=options.m_Window_Height;

	EditCopy(&options);
}

void CHoopsView::EditCopy(GDIExportInformation * options)
{
	BeginWaitCursor();

	if (OpenClipboard()) {
		EmptyClipboard();
		CloseClipboard();
	}

	HIOUtilityGDIOutput handler;
	m_pHView->FileOutput("", &handler, options);

	EndWaitCursor();
}

void CHoopsView::OnNcDestroy()
{
    CView::OnNcDestroy();
}

void CHoopsView::PostNcDestroy()
{
    CView::PostNcDestroy();
}

void CHoopsView::SaveEMF(const char *filename, HOutputHandlerOptions * in_options) 
{
	BeginWaitCursor();

	// Clean clipboard of contents and copy.
	if (OpenClipboard()) {
		EmptyClipboard();
		CloseClipboard();
	}	

	GDIExportInformation options;
	if(in_options){
		options.Init(in_options);
	} else {
		options.m_bUseWindowColor = true;
		/* Size of the window devidec by standard screen resolution (72 dpi) */
		RECT win_rect;
		GetWindowRect(&win_rect);
		options.m_Paper_Width = win_rect.right - win_rect.left;
		options.m_Paper_Height = win_rect.bottom - win_rect.top;
		options.m_Paper_Width /= 72.0;
		options.m_Paper_Height /= 72.0;
		options.m_Window_Width = options.m_Paper_Width;
		options.m_Window_Height = options.m_Paper_Height;
	}

	CDC	*hDC = GetDC();	
	options.deviceContext = hDC->GetSafeHdc();
	options.attribDC = hDC->m_hAttribDC;
	options.windowID = (void*)m_hWnd;
	options.rasterOutput = m_bFastPrint;
	options.clipBoard= true;	

	HOutputHandler * handler = new HIOUtilityGDIOutput;

	// if none found quit
	if(!handler) 
		return;
	
	m_pHView->FileOutput(filename, handler, &options);

	EndWaitCursor();
}

/* The following is a workaround for a bug that appeared in windows 98 (and probably 
 * ME as well).  MS was not bashing the floating point unit state in their standard
 * print preview dialog.  These macros are used to save and restore before and after. 
 * This code was contributed by one of our customers */
#define H_X86_MASK_EXCEPTIONS(dwOldMode) \
    __asm fnstcw WORD PTR dwOldMode \
    __asm mov eax, dwOldMode \
    __asm or eax, 0x3f \
    __asm mov WORD PTR dwOldMode+2, ax \
    __asm fldcw WORD PTR dwOldMode+2

#define H_X86_RESTORE_MASK(dwOldMode) \
    __asm fnclex \
    __asm fldcw WORD PTR dwOldMode



void CHoopsView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
#ifndef _WIN64
	int mode;
	H_X86_MASK_EXCEPTIONS(mode);
#endif

	GDIExportInformation * options = (GDIExportInformation*)pInfo->m_lpUserData;
	GDIExportInformation static_options;
	if(!options){
		options = &static_options;
	}

	options->deviceContext = pDC->m_hDC;
	options->attribDC = pDC->m_hAttribDC;
	options->rasterOutput = m_bFastPrint;
	options->clipBoard= false;
	// only really used when it's a print preview
	options->windowID = (void*)::GetDesktopWindow();

	// For print previews, use only up to 50 dpi.  We use to hardcode this to
	// 72 dpi, but that lead to problems (black splotches in the model) when
	// the partviewer wasn't maximised.
	// For real printing, use user specified raster resolution.
	if(pInfo->m_bPreview){ 
		if(options->m_Paper_Dpi > 50)
			options->m_Paper_Dpi = 50;
		if(options->m_Image_Dpi > 50)
			options->m_Image_Dpi = 50;
	}
	else{
		double printerdpi = MAX(pDC->GetDeviceCaps(LOGPIXELSY), pDC->GetDeviceCaps(LOGPIXELSX));
		options->m_Image_Dpi = options->m_Paper_Dpi = MIN(printerdpi, options->m_Paper_Dpi);
	}

	options->m_Paper_Width = pDC->GetDeviceCaps(PHYSICALWIDTH); 
	options->m_Paper_Width -= pDC->GetDeviceCaps(PHYSICALOFFSETX);
	options->m_Paper_Width /= (float)pDC->GetDeviceCaps(LOGPIXELSX);

	options->m_Paper_Height = pDC->GetDeviceCaps(PHYSICALHEIGHT);
	options->m_Paper_Height -= pDC->GetDeviceCaps(PHYSICALOFFSETY);
	options->m_Paper_Height /= (float)pDC->GetDeviceCaps(LOGPIXELSY);

	HIOUtilityGDIOutput handler;
	m_pHView->FileOutput("", &handler, options);
	
	if(options ==  &static_options){
		options = 0;
	}

#ifndef _WIN64
	H_X86_RESTORE_MASK(mode);
#endif

}
#undef H_X86_MASK_EXCEPTIONS
#undef H_X86_RESTORE_MASK



BOOL CHoopsView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC|CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW);
	return CView::PreCreateWindow(cs);
}

#ifdef _UNICODE
BOOL CHoopsView::Create(wchar_t const * lpszClassName, wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{	
	dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
	return CWnd::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
BOOL CHoopsView::Create(unsigned short const * lpszClassName, unsigned short const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{	
	dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
	return CWnd::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#else
BOOL CHoopsView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{	
	dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#endif


unsigned long CHoopsView::MapFlags( unsigned long state )
{
	unsigned long flags=0;

	/*map the mfc events state to MVO*/
	if(state & MK_LBUTTON) flags|=MVO_LBUTTON;
	if(state & MK_RBUTTON) flags|=MVO_RBUTTON;
	if(state & MK_MBUTTON) flags|=MVO_MBUTTON;
	if(state & MK_SHIFT) flags|=MVO_SHIFT;
	if(state & MK_CONTROL) flags|=MVO_CONTROL;
	
	return flags;
}



unsigned long CHoopsView::MapKeyFlags(BYTE * virtual_key_states)
{

    unsigned long status = 0;

    if ((virtual_key_states[VK_SHIFT] & 0x80) != 0)
        status |= MVO_SHIFT;
    if ((virtual_key_states[VK_CONTROL] & 0x80) != 0)
        status |= MVO_CONTROL;
    if ((virtual_key_states[VK_MENU] & 0x80) != 0)
        status |= MVO_ALT;
    if ((virtual_key_states[VK_LSHIFT] & 0x80) != 0)
        status |= MVO_LEFT_SHIFT;
    if ((virtual_key_states[VK_LCONTROL] & 0x80) != 0)
        status |= MVO_LEFT_CONTROL;
    if ((virtual_key_states[VK_LMENU] & 0x80) != 0)
        status |= MVO_LEFT_ALT;
    if ((virtual_key_states[VK_RSHIFT] & 0x80) != 0)
        status |= MVO_RIGHT_SHIFT;
    if ((virtual_key_states[VK_RCONTROL] & 0x80) != 0)
        status |= MVO_RIGHT_CONTROL;
    if ((virtual_key_states[VK_RMENU] & 0x80) != 0)
        status |= MVO_RIGHT_ALT;
    
    return status;
}



void CHoopsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{   

	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		HBaseOperator *op = m_pHView->GetCurrentOperator();
		unsigned int nExtraFlags = 0;

		if (op)
		{
			
			unsigned short ascii_key=0;
			BYTE keys[256];
			GetKeyboardState( keys );

			switch (nChar) {

				case VK_NUMPAD0:
				case VK_NUMPAD1:
				case VK_NUMPAD2:
				case VK_NUMPAD3:
				case VK_NUMPAD4:
				case VK_NUMPAD5:
				case VK_NUMPAD6:
				case VK_NUMPAD7:
				case VK_NUMPAD8:
				case VK_NUMPAD9: {
					ascii_key = '0' + nChar - VK_NUMPAD0;
				}   break;

				case VK_LEFT:
				case VK_UP:
				case VK_RIGHT:
				case VK_DOWN:
				{
					nExtraFlags = 1 << (13 + nChar-VK_LEFT);
					//fall through to default case
				}
				default: {
					if(!ToUnicode(nChar, MapVirtualKey(nChar, 0), keys, (LPWSTR)&ascii_key, 1,0))
						ascii_key = nChar;
				 }			
			}

		
			event.SetKey(HE_KeyDown, ascii_key, nRepCnt, 
				((nFlags&(1<<13))?MVO_ALT:0) | MapKeyFlags(keys) | nExtraFlags);
//			op->OnKeyDown(event);
	 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnKeyDown(event))
			
		}
		else
			CView::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}




void CHoopsView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		HBaseOperator *op = m_pHView->GetCurrentOperator();

		if (op)
		{
						
			unsigned short ascii_key;
			BYTE keys[256];
			GetKeyboardState( keys );

			switch (nChar) {

				case VK_NUMPAD0:
				case VK_NUMPAD1:
				case VK_NUMPAD2:
				case VK_NUMPAD3:
				case VK_NUMPAD4:
				case VK_NUMPAD5:
				case VK_NUMPAD6:
				case VK_NUMPAD7:
				case VK_NUMPAD8:
				case VK_NUMPAD9: {
					ascii_key = '0' + nChar - VK_NUMPAD0;
				}   break;

				default: {
					if(!ToUnicode(nChar, MapVirtualKey(nChar, 0), keys, (LPWSTR)&ascii_key, 1,0))
						ascii_key = nChar;
				}			
			}
	
			event.SetKey(HE_KeyUp, ascii_key, nRepCnt, ((nFlags&(1<<13))?MVO_ALT:0)|MapKeyFlags(keys));
//			op->OnKeyUp(event);
	 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnKeyUp(event))

		}
		else
			CView::OnKeyUp(nChar, nRepCnt, nFlags);
	}
}



void CHoopsView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
 		event.SetPoint(HE_LButtonDblClk, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnLButtonDblClk(event))

	}
}



void CHoopsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		event.SetPoint(HE_LButtonDown, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnLButtonDown(event))

		HBaseOperator *op = m_pHView->GetCurrentOperator();

//this logic needs to be reconsidered for multiple operators
		if (op) 
		{			
 			if (op->Capture()) 
				SetCapture();
		}
		else 
			CView::OnLButtonDown(nFlags, point);
	}
}


void CHoopsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		event.SetPoint(HE_LButtonUp, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnLButtonUp(event))

		HBaseOperator *op = m_pHView->GetCurrentOperator();

 		if (op) 
		{			
 			if (op->Capture()) 
				ReleaseCapture();
		}
		else 
			CView::OnLButtonUp(nFlags, point);
	}
}


void CHoopsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_pHView && m_pHView->GetViewActive())
	{

		HEventInfo	event(m_pHView);

		event.SetPoint(HE_MouseMove, point.x, point.y, MapFlags(nFlags));
 	        HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMouseMove(event))
	}
	else
 		CView::OnMouseMove(nFlags, point);
}


void CHoopsView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	if (m_pHView)
	{

		HEventInfo	event(m_pHView);
		event.SetPoint(HE_RButtonDblClk, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnRButtonDblClk(event))
	}
	else
 		CView::OnRButtonDblClk(nFlags, point);

	
}


void CHoopsView::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		event.SetPoint(HE_RButtonDown, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnRButtonDown(event))

		HBaseOperator *op = m_pHView->GetCurrentOperator();

 		if (op) 
		{			
 			if (op->Capture()) 
				SetCapture();
		}
		else 
			CView::OnRButtonDown(nFlags, point);
	}
}

void CHoopsView::OnMButtonDown(UINT nFlags, CPoint point) 
{	
	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		event.SetPoint(HE_RButtonDown, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMButtonDown(event))

		HBaseOperator *op = m_pHView->GetCurrentOperator();

 		if (op) 
		{			
 			if (op->Capture()) 
				SetCapture();
		}
		else 
			CView::OnMButtonDown(nFlags, point);
	}
}

void CHoopsView::OnMButtonUp(UINT nFlags, CPoint point) 
{	
	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		event.SetPoint(HE_RButtonDown, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMButtonUp(event))

		HBaseOperator *op = m_pHView->GetCurrentOperator();

 		if (op) 
		{			
 			if (op->Capture()) 
				ReleaseCapture();
		}
		else 
			CView::OnMButtonUp(nFlags, point);
	}
}

void CHoopsView::OnRButtonUp(UINT nFlags, CPoint point) 
{
if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		event.SetPoint(HE_RButtonUp, point.x, point.y, MapFlags(nFlags));
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnRButtonUp(event))

		HBaseOperator *op = m_pHView->GetCurrentOperator();

 		if (op) 
		{			
 			if (op->Capture()) 
				ReleaseCapture();
		}
		else 
			CView::OnRButtonUp(nFlags, point);
	}
}





#if (_MSC_VER < 1400)
void CHoopsView::OnTimer(UINT nIDEvent)
#else
void CHoopsView::OnTimer(UINT_PTR nIDEvent)
#endif
{
 	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
		HBaseOperator *op = m_pHView->GetCurrentOperator();
		
#ifdef DIRECT_INPUT_SUPPORT
		if(m_bUsingDI8Joystick)
			this->UpdateDI8State(0);
#endif

		if (op)
		{
			event.SetTimer(HE_Timer, nIDEvent);
			op->OnTimer(event);
		}
		else
			CView::OnTimer(nIDEvent);
	}
}


BOOL CHoopsView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) 
{
    
    RECT windowRect;

	if (m_pHView)
	{
		HEventInfo	event(m_pHView);
 	        GetWindowRect(&windowRect);    
	         event.SetPoint(HE_MouseWheel, point.x - windowRect.left, point.y - windowRect.top, MapFlags(nFlags));
		event.SetMouseWheelDelta(zDelta);
 		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMouseWheel(event))

	}

	return true;
}


HC_KEY CHoopsView::GetViewKey() 
{ 
	if (m_pHView)
		return m_pHView->GetViewKey();
	else 
		return m_ViewKey;
}


HC_KEY CHoopsView::GetSceneKey() 
{ 
	if (m_pHView)
		return m_pHView->GetSceneKey();
	else 
		return m_SceneKey;
}


 

void CHoopsView::OnDisplayChanged(int xres, int yres, int depth)
{
	return;
}

LRESULT CHoopsView::OnAFXDisplayChange( WPARAM wparam, LPARAM lparam)
{
	DefWindowProc( WM_DISPLAYCHANGE, wparam, lparam);

	OnDisplayChanged((int)lparam%0x10000, (int)lparam/0x10000, (int)wparam);

	return TRUE;
}

BOOL CHoopsView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// we are having problems with cursor not getting restored to standard 
	// Just force the cursor to restore to standard here. Derived class can 
	// still set their own cursors and should not call the base class function.
	// Rajesh B (23-May-03)
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

	// let the processing continue - a child window may want to set one of its own
	return FALSE;
}


bool CHoopsView::GetKeyState(unsigned int key, int &flags)
{
	unsigned char state[256];
	flags = 0;
  	GetKeyboardState(state);
	if (state[VK_LSHIFT] >=128)
		flags |= MVO_LEFT_SHIFT;
 	if (state[VK_SHIFT] >=128)
		flags |= MVO_SHIFT;
	if (state[VK_RSHIFT] >=128)
		flags |= MVO_RIGHT_SHIFT;
	if (state[VK_CONTROL] >=128)
		flags |= MVO_CONTROL;
	if (state[VK_LMENU] >=128 || state[VK_RMENU] >=128)
		flags |= MVO_ALT;
	if (state[key] >=128)
		return true;
	else
		return false;
}

BOOL CHoopsView::OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	switch(message)
	{
	case WM_INPUTLANGCHANGE:{
		// Extract the language from the message and select the locale.
		LCID lcidNew = MAKELCID( lParam, SORT_DEFAULT );
		::SetThreadLocale( lcidNew );
		return TRUE;
	}break;

	case WM_INPUTLANGCHANGEREQUEST:{
        if(GetKeyboardLayout(0) == (HKL)lParam)
            return 0;

        UINT count = GetKeyboardLayoutList(0, NULL);

        if(count == 0)
			return 0;

        HKL* lpList = new HKL[count];

        count = GetKeyboardLayoutList(count, lpList);
        BOOL bFound = FALSE;
        for(UINT i = 0; i < count; ++i){
            if((HKL)lParam == lpList[i]){
                bFound = TRUE;
                break;
            }
        }

        delete [] lpList;
        lpList = NULL;

        if(!bFound)
        {
            LoadKeyboardLayout(H_TEXT(H_FORMAT_TEXT("%08x",lParam)),KLF_ACTIVATE);
        }
        else
        {
             ActivateKeyboardLayout((HKL)lParam, 0);
        }
		return TRUE;
	}break;
	case WM_POWERBROADCAST:
		{
			HC_Control_Update_By_Key(m_pHView->GetViewKey(),"reset device");
			return TRUE;
		}

	default:break;
		
	}
	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

#ifdef DIRECT_INPUT_SUPPORT
//Joystick code
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

/*
 * Defines, constants
 */
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define ALL_ZERO(x,y,z) (((x)==0)&&((y)==0)&&((z)==0))


/* 
 * Forward declarations of functions
 */
BOOL	CALLBACK	EnumAxesCB( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext );
BOOL	CALLBACK	EnumDevicesCB( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
VOID				FreeDI8(void);
HRESULT				UpdateDI8State( unsigned long );
VOID				FreeDI8Device(DIDeviceInfo *pdinfo );


void CombineDataStreams( CHoopsView* view, DIJOYSTATE &js )
/*
 * As mentioned at the top, one of the peculiar characteristics of DI event mode
 * is that the translation and rotation vectors usually arrive separately.  This is 
 * probably because they arrive on the USB bus separately.  Somewhat misleadingly, 
 * in this circumstance, the other vector is zeroed out.  I suppose there isn't any other
 * choice since we tell DI that we have 6 axes, but only update 3 at a time.
 * 
 * Sometimes you do get all 6 axes updated together.  When this happens, one of the 
 * vectors often seems to be approximately doubled, as if the values of that vector
 * were accumulated with the previous or next value from the device.  This may be
 * an artifact of the USB bus polling scheme.  Make sure your code doesn't have problems
 * with spikes like this.
 *
 * You can use the two vectors as they arrive separately, or use a heuristic
 * such as this to combine them.  If you were polling, instead of using event
 * mode, you would get all 6 at once.
 *
 * To reassemble a full 6DOF vector we have to figure out what changed.
 * This function always returns a valid state of each vector.  It reuses the data
 * for the last vector if it has to.
 *
 * We may have received a new translation vector or a new rotation vector from HID.
 * In addition, the timer code (or other polling code) could send an all zero event.
 * 
 * Four cases:  
 * 1) Both T and R have data in them: use the data as is.
 * 2) Both T and R vectors are zero: the user let go.
 * 3) Non-zero data in the T vector:  it's a translation vector
 *    If get two of these in a row, there is no rotation vector, zero it out.
 * 4) Non-zero data in the R vector: it's a rotation vector
 *    If get two of these in a row, there is no translation vector, zero it out.
 * If the last vector type was not the same as the current type, reuse the data from the last event.
 * 
 */
{
	DIDeviceInfo *pdinfo = view->g_pDevice;

	/*
	 * 1) Both T and R vectors have data in them:  use the data as is.
	 * No changes necessary.  Just keep the state.
	 */
	if (!ALL_ZERO(js.lX, js.lY, js.lZ) && !ALL_ZERO(js.lRx, js.lRy, js.lRz))
	{
		pdinfo->lastVectorType = BothVectors;
		memcpy( &pdinfo->lastJoyState, &js, sizeof(DIJOYSTATE) );
		// OutputDebugString("\nUnusual, but got 2 new vectors\n");
	}

	/*
	 * 2) Both T and R vectors are zero: the user let go.
	 * No changes necessary.  Just keep the state.
	 */
	else if (ALL_ZERO(js.lX, js.lY, js.lZ) && ALL_ZERO(js.lRx, js.lRy, js.lRz))
	{
		pdinfo->lastVectorType = BothZeroVectors;
		memcpy( &pdinfo->lastJoyState, &js, sizeof(DIJOYSTATE) );
		// OutputDebugString("\nZero event\n");
	}

	/*
     * 3) Non-zero data in the T vector:  it's a translation vector
     *    If get two of these in a row, there is no rotation vector, zero it out.
	 * If the last vector type was not the same as the current type, reuse the data from the last event.
	 */
	else if (!ALL_ZERO(js.lX, js.lY, js.lZ) && ALL_ZERO(js.lRx, js.lRy, js.lRz))
	{
		if (pdinfo->lastVectorType == TranslationVector)
		{
			// Two in a row, therefore RotationVector is zero
			js.lRx = js.lRy = js.lRz = 0;
			// OutputDebugString("\nTranslation vector only, zeroing rotation vector\n");
		}
		else 
		{
			// Alternating T and R vectors, reuse the last RotationVector
			pdinfo->lastVectorType = TranslationVector;
			js.lRx = pdinfo->lastJoyState.lRx;
			js.lRy = pdinfo->lastJoyState.lRy;
			js.lRz = pdinfo->lastJoyState.lRz;
			// OutputDebugString("\nTranslation vector alternating with rotation vector\n");
		}
		// Save the state
		memcpy( &pdinfo->lastJoyState, &js, sizeof(DIJOYSTATE) );
	}


	/*
     * 4) Non-zero data in the R vector:  it's a rotation vector
     *    If get two of these in a row, there is no translation vector, zero it out.
	 * If the last vector type was not the same as the current type, reuse the data from the last event.
	 */
	else if (ALL_ZERO(js.lX, js.lY, js.lZ) && !ALL_ZERO(js.lRx, js.lRy, js.lRz))
	{
		if (pdinfo->lastVectorType == RotationVector)
		{
			// Two in a row, therefore TranslationVector is zero
			js.lX = js.lY = js.lZ = 0;
			// OutputDebugString("\nRotation vector only, zeroing translation vector\n");
		}
		else 
		{
			// Alternating T and R vectors, reuse the last TranslationVector
			pdinfo->lastVectorType = RotationVector;
			js.lX = pdinfo->lastJoyState.lX;
			js.lY = pdinfo->lastJoyState.lY;
			js.lZ = pdinfo->lastJoyState.lZ;
			// OutputDebugString("\nRotation vector alternating with translation vector\n");
		}
		// Save the state
		memcpy( &pdinfo->lastJoyState, &js, sizeof(DIJOYSTATE) );
	}
}


/*---------------------------------------------------------------------------*/
VOID FreeDI8Device( DIDeviceInfo *pdinfo )
/*
  Free up a device.
-----------------------------------------------------------------------------*/
{
	// Release the event
	if ( pdinfo->pUsbHidDevice )
		pdinfo->pUsbHidDevice->SetEventNotification( NULL );

    // Unacquire the device one last time just in case 
    // the app tried to exit while the device is still acquired.
    if( pdinfo->pUsbHidDevice ) 
        pdinfo->pUsbHidDevice->Unacquire();
    
    // Release any DirectInput objects.
    SAFE_RELEASE( pdinfo->pUsbHidDevice );

	free (pdinfo);
	pdinfo = NULL;
}

/*---------------------------------------------------------------------------*/
VOID FreeDI8( )
/*
  Shutdown DI
-----------------------------------------------------------------------------*/
{
    //SAFE_RELEASE( g_pDI );
}

BOOL CALLBACK EnumDevicesCB( const DIDEVICEINSTANCE* pdidInstance,
                             VOID* pContext )
/*
  Called once for each enumerated UsbHidDevice. If we find one, create a
  device interface on it so we can play with it.
-----------------------------------------------------------------------------*/
{
	int newIndex;
    HRESULT hr;
	CHoopsView* m_pHView = (CHoopsView*)pContext;
	GUID guid = pdidInstance->guidProduct;
#   define LOGITECH_3DX_VID    0x046d  // Vendor ID for Logitech/3Dx

    /* Check to see if this is a 3Dx device.  Look at the VendorID before stopping the enumeration. */
	if ( (guid.Data1 & 0x0000ffff) != LOGITECH_3DX_VID)
		return DIENUM_CONTINUE;

	/* Filter out LOGI mice and such */
	else if (pdidInstance->wUsagePage != 0x0001 || pdidInstance->wUsage != 0x0008)
		return DIENUM_CONTINUE;



	newIndex = 0;
    m_pHView->g_pDevice = (DIDeviceInfo*)malloc( sizeof(DIDeviceInfo) );

	/* Set state variables to known values */
	ZeroMemory( &m_pHView->g_pDevice->lastJoyState, sizeof(DIJOYSTATE) );
	m_pHView->g_pDevice->lastVectorType = BothZeroVectors;

	/* 
	 * Save the DIDEVICEINSTANCE struct for later display.
	 * This isn't necessary.  The demo just does it to display the info in the dlg box.
	 */
	m_pHView->g_pDevice->DIDevInstance = *pdidInstance;

	/* Obtain an interface to the enumerated device. */
    hr = m_pHView->dev_handle->g_pDI->CreateDevice( pdidInstance->guidInstance, &m_pHView->g_pDevice->pUsbHidDevice, NULL );

    /* 
	 * If it failed, then we can't use this UsbHidDevice. (Maybe the user unplugged
     * it while we were in the middle of enumerating it.)
	 */
    if( FAILED(hr) ) 
	{
		free (m_pHView->g_pDevice);
        return DIENUM_CONTINUE;
	}

	m_pHView->g_nDevices++;
    return DIENUM_CONTINUE;
}



BOOL CALLBACK EnumAxesCB( const DIDEVICEOBJECTINSTANCE* pdidoi,
                          VOID* pContext )
/*
   Callback function for enumerating the axes on a UsbHidDevice
-----------------------------------------------------------------------------*/
{
	DIDeviceInfo *pDIDeviceInfo = (DIDeviceInfo *)pContext;


	/*
	 * Recent 3Dx USB device descriptors indicate that the device axes return relative data
	 * even though the device is really an absolute device.
	 * HID ignores this, but apparently DI uses it.
	 * Changing the axis handling to return RELATIVE values gives us back what we want (displacement
	 * values rather than accumulated values).  If older USB devices were to be supported, this handling
	 * would have to be changed to DIPROPAXISMODE_ABS.  
	 *
	 * In this mode, DI sets the notification event even though the values haven't changed.
	 */
    DIPROPDWORD dipdw;
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD); 
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
    dipdw.diph.dwHow        = DIPH_DEVICE; 
    dipdw.diph.dwObj        = 0; // set for whole device not an axis (really only needs to be done once)
    dipdw.dwData            = DIPROPAXISMODE_REL;

	if( FAILED( pDIDeviceInfo->pUsbHidDevice->SetProperty( DIPROP_AXISMODE, &dipdw.diph ) ) )
		return DIENUM_STOP;

	dipdw.dwData            = 10;

	if( FAILED( pDIDeviceInfo->pUsbHidDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
		return DIENUM_STOP;
	
    return DIENUM_CONTINUE;
}

void HandleAxesState(CHoopsView* view, DIJOYSTATE js )
/*
 * All this example does to handle an event is to display the info.
 * You'd probably do much more!
 *---------------------------------------------------------------------------*/
{
	// Knowing the peculiar characteristics of the USB/HID/DI implementation, combine all 6 DOFs
	CombineDataStreams(view, js );

	HEventInfo	translate_event(view->m_pHView);
	translate_event.SetType(HE_JoyStickTranslate);
	translate_event.SetWorldPos(HE_JoyStickTranslate, HPoint(-js.lX, -js.lZ, -js.lY), 0);
 	HLISTENER_EVENT(HJoyStickListener, view->m_pHView->GetEventManager(), OnJoyStickTranslation(translate_event))

	HEventInfo	rotate_event(view->m_pHView);
	rotate_event.SetType(HE_JoyStickRotate);
	rotate_event.SetWorldPos(HE_JoyStickRotate, HPoint(js.lRx, js.lRy, js.lRz), 0);
 	HLISTENER_EVENT(HJoyStickListener, view->m_pHView->GetEventManager(), OnJoyStickRotation(rotate_event))

}

HRESULT CHoopsView::UpdateDI8State( unsigned long devIndex )
/*
   Get the input device's state and display it.
-----------------------------------------------------------------------------*/
{
    HRESULT     hr;
    DIJOYSTATE  js;           // DInput UsbHidSpaceball state 
	DIDeviceInfo dinfo = *g_pDevice;

    if( NULL == dinfo.pUsbHidDevice ) 
        return S_OK;

    /* 
	 * Poll the device to read the current state.  This should not be necessary
	 * but is advised by DI documentation and should not take a significant amount
	 * of time.  (This could be where we get the double vector events.)
     */
    hr = dinfo.pUsbHidDevice->Poll(); 
    if( FAILED(hr) )  
    {
		//OutputDebugString("Poll failed\n");

        // DInput is telling us that the input stream has been
        // interrupted. We aren't tracking any state between polls, so
        // we don't have any special reset that needs to be done. We
        // just re-acquire and try again.
        hr = dinfo.pUsbHidDevice->Acquire();
        while( hr == DIERR_INPUTLOST ) 
            hr = dinfo.pUsbHidDevice->Acquire();

        // hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
        // may occur when the app is minimized or in the process of 
        // switching, so just try again later 
        return S_OK; 
    }

    // Get the input's device state
    if( FAILED( hr = dinfo.pUsbHidDevice->GetDeviceState( sizeof(DIJOYSTATE), &js ) ) )
	{
		//OutputDebugString("GetDeviceState failed\n");
        return hr; // The device should have been acquired during the Poll()
	}

    // Display UsbHidDevice state to dialog
	HandleAxesState( this, js );

	DIDEVICEOBJECTDATA rgdod[10]; 
	DWORD dwItems = 10; 
	hr = dinfo.pUsbHidDevice->GetDeviceData( 
		sizeof(DIDEVICEOBJECTDATA), 
		rgdod, 
		&dwItems, 
		0); 
	if (SUCCEEDED(hr)) { 
		// dwItems = Number of elements read (could be zero).
		if (hr == DI_BUFFEROVERFLOW) { 
		// Buffer had overflowed. 
		} 
		for(int i = 0; i < (int)dwItems; i++){
			HEventInfo	button1_event(this->m_pHView);
			button1_event.SetType(HE_JoyStickButton);

			switch(rgdod[i].dwOfs){
				case DIJOFS_BUTTON0:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_1);
					break;
				case DIJOFS_BUTTON1:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_2);
					break;
				case DIJOFS_BUTTON2:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_3);
					break;
				case DIJOFS_BUTTON3:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_4);
					break;
				case DIJOFS_BUTTON4:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_5);
					break;
				case DIJOFS_BUTTON5:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_6);
					break;
				case DIJOFS_BUTTON6:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_7);
					break;
				case DIJOFS_BUTTON7:
					button1_event.SetFlags(MVO_JOYSTICK_BUTTON_8);
					break;
			}

			if(button1_event.GetFlags() != 0)
				HLISTENER_EVENT(HJoyStickListener, this->m_pHView->GetEventManager(), OnJoyStickButton(button1_event))
		}
	} 

    return S_OK;
}

HRESULT CHoopsView::InitDI8( void )
/*
  Initialize the DirectInput variables.
-----------------------------------------------------------------------------*/
{
    HRESULT hr;
	g_nDevices = 0;

    // Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    // Create a DInput object
    if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
                                         IID_IDirectInput8, (VOID**)&(dev_handle->g_pDI), NULL ) ) )
	{
		m_bUsingDI8Joystick = false;
        return hr;
	}

    // Look for all 3Dx HID devices.
    if( FAILED( hr = dev_handle->g_pDI->EnumDevices( DIDEVTYPE_HID, 
                                         EnumDevicesCB,
										 this, DIEDFL_ATTACHEDONLY ) ) ){
		m_bUsingDI8Joystick = false;
        return hr;
	}

    // Make sure we got an HID device
    if( g_nDevices == 0 )
    {
		m_bUsingDI8Joystick = false;
		return S_OK;
    }


	/* Set the data format to "simple joystick" - a predefined data format 
	 *
	 * A data format specifies which controls on a device we are interested in,
	 * and how they should be reported. This tells DInput that we will be
	 * passing a DIJOYSTATE structure to IDirectInputDevice::GetDeviceState().
	 * This is a fine format to use for the 3Dx Devoce as it has 6 DOF and upto
	 * 32 buttons.
	 */
	if( FAILED( hr = g_pDevice->pUsbHidDevice->SetDataFormat( &c_dfDIJoystick ) ) ){
		m_bUsingDI8Joystick = false;
		return hr;
	}

	/* Set the cooperative level to let DInput know how this device should
	 * interact with the system and with other DInput applications.
	 * You probably don't want the dialog box to be the target of the events.
	 */
	if( FAILED( hr = g_pDevice->pUsbHidDevice->SetCooperativeLevel( AfxGetApp()->m_pMainWnd->GetSafeHwnd(), 
			   DISCL_EXCLUSIVE | DISCL_FOREGROUND    // normal use:  get events when have focus
			 //DISCL_NONEXCLUSIVE | DISCL_BACKGROUND /* get events all the time */
			 ) ) ){
		m_bUsingDI8Joystick = false;
		return hr;
	}

	/* Determine how many axis the UsbHidDevice has (so we don't error out setting
	 * properties for unavailable axis)
	 */
	g_pDevice->diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if ( FAILED( hr = g_pDevice->pUsbHidDevice->GetCapabilities(&g_pDevice->diDevCaps) ) ){
		m_bUsingDI8Joystick = false;
		return hr;
	}

	/* Enumerate the axes of the UsbHidDevice and set the range of each axis and
	 * make sure the axes are set to ABSOLUTE mode.
	 */
	if ( FAILED( hr = g_pDevice->pUsbHidDevice->EnumObjects( EnumAxesCB, 
		(VOID*)g_pDevice, DIDFT_AXIS ) ) ){
		m_bUsingDI8Joystick = false;
		return hr;
	}



    return S_OK;
}
#endif

