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
// $Header: /files/homes/master/cvs/hoops_master/mfc_simple/simpleView.cpp,v 1.4 2006-08-07 20:38:55 stage Exp $
//

// simpleView.cpp : implementation of the CSimpleView class
//

#include "stdafx.h"
#include "simple.h"

#include "simpleDoc.h"
#include "simpleView.h"
#include "MainFrm.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSimpleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimpleView

IMPLEMENT_DYNCREATE(CSimpleView, CView)

BEGIN_MESSAGE_MAP(CSimpleView, CView)
	//{{AFX_MSG_MAP(CSimpleView)
	ON_WM_PAINT()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VIEW_WIREFRAME, OnViewWireframe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAME, OnUpdateViewWireframe)
	ON_COMMAND(ID_VIEW_SHADED, OnViewShaded)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHADED, OnUpdateViewShaded)
	ON_COMMAND(ID_VIEW_HIDDENLINE, OnViewHiddenline)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HIDDENLINE, OnUpdateViewHiddenline)
	ON_COMMAND(ID_RUN_MY_CODE, OnRunMyCode)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleView construction/destruction

CSimpleView::CSimpleView()
{
	m_bFastPrint = true;
	m_bOperatorStarted = false;
	m_bClipboardPrinting = false;
	m_MetafileType = EMF;
	m_bClipboardTruecolor = true;
	m_lDriverKey = 0L;
	m_lSceneKey = 0L;
	m_pViewPalette = NULL;
}

CSimpleView::~CSimpleView()
{
	// delete the color palette, the driver instance and decrement the driver instance counter
	HC_Delete_Segment(m_sDriverSegment);
	theApp.DecrementCounter();

	if (m_pViewPalette)
		delete m_pViewPalette;
}

BOOL CSimpleView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC|CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW);
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleView drawing

void CSimpleView::OnDraw(CDC* pDC)
{
	CSimpleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleView printing

BOOL CSimpleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSimpleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSimpleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleView diagnostics

#ifdef _DEBUG
void CSimpleView::AssertValid() const
{
	CView::AssertValid();
}

void CSimpleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpleDoc* CSimpleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleDoc)));
	return (CSimpleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleView message handlers

void CSimpleView::OnInitialUpdate() 
{
    CView::OnInitialUpdate();

    CSimpleDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    // Setup the view to be associated with a HOOPS driver segment.
    CMainFrame * pAppFrame = (CMainFrame *)AfxGetMainWnd();

    if (!pAppFrame->SharedPalette())
        InitializePalette ();

    CPalette * pPalette = GetPalette();

    int count = theApp.IncrementCounter();

    sprintf (m_sDriverSegment, "/driver/%s/window%d", theApp.GetDriverType(), count);

    m_lDriverKey = HC_KOpen_Segment (m_sDriverSegment);

		char        szTemp[256];
		long        debug_flags = DEBUG_NO_WINDOWS_HOOK;

		sprintf (szTemp, "disable input, use window id = %u, debug = %u", m_hWnd, debug_flags);

        HC_Set_Driver_Options (szTemp);

        sprintf (szTemp, "use colormap id = %u", (long)(HPALETTE)(*pPalette));
        HC_Set_Driver_Options (szTemp);


        if (!strcmp (theApp.GetDriverType(), "opengl")) {
            HC_Set_Rendering_Options ("hsr algorithm = hardware z-buffer,  technology = standard");
            HC_Set_Driver_Options("double-buffering");
        }
        else {
            HC_Set_Rendering_Options ("hsra = software z buffer, technology = sfb");
		    HC_Set_Driver_Options("fixed colors = 125");
        }
	
        HC_Set_Color ("windows=white");
        HC_Set_Window_Frame ("off");
   
        m_lSceneKey = HC_KOpen_Segment ("Scene");

		  HC_Include_Segment(pDoc->GetModelSegment());
		  HC_Set_Visibility("vertices=off");
		  FitWorld();

    	HC_Close_Segment ();
       
    HC_Close_Segment ();
	HC_Update_Display();
}


void CSimpleView::FitWorld() 
{
    float min[3];
	float max[3];

	HC_Compute_Circumcuboid (".", &min, &max);

	//order the points
	if (min[0] > max[0]) {
		float tmp;
		tmp = min[0]; min[0] = max[0]; max[0] = tmp;
	}
	if (min[1] > max[1]) {
		float tmp;
		tmp = min[1]; min[1] = max[1]; max[1] = tmp;
	}
	if (min[2] > max[2]) {
		float tmp;
		tmp = min[2]; min[2] = max[2]; max[2] = tmp;
	}
    
	// compute the length of the bbox diagonal vector
	// this will be used to make the camera field a bit larger
	// to ensure that objects between the camera position and target
	// will still not get clipped (this is for perspective viewing mode)

	float diagonalVector[3];
	float center[3];
	float diagonalLength;

	diagonalVector[0] = max[0] - min[0];
	diagonalVector[1] = max[1] - min[1];
	diagonalVector[2] = max[2] - min[2];

	diagonalLength = (float) sqrt(
		diagonalVector[0] * diagonalVector[0] +
		diagonalVector[1] * diagonalVector[1] +
		diagonalVector[2] * diagonalVector[2]);

	center[0] = 0.5F * (min[0] + max[0]);
	center[1] = 0.5F * (min[1] + max[1]);
	center[2] = 0.5F * (min[2] + max[2]);

	float position[3], target[3], up[3];
	float fieldx, fieldy;
	char proj[32];

	HC_Show_Net_Camera(&position, &target, &up, &fieldx, &fieldy, proj);

	// now we determine the new camera definition
	float new_position[3], new_target[3], new_up[3];
	float new_fieldx, new_fieldy;

	if( diagonalLength != 0 ) {

			new_target[0] = center[0];
			new_target[1] = center[1];
			new_target[2] = center[2];

			float viewingVector[3];
			viewingVector[0] = position[0] - target[0];
			viewingVector[1] = position[1] - target[1];
			viewingVector[2] = position[2] - target[2];

			HC_Compute_Normalized_Vector (&viewingVector, &viewingVector);

			// reset camera position to lie on the viewing vector, at a distance of
			// 2.5 * diagonal length away from the center of the scene centroid
			new_position[0] = center[0] + 2.5f * viewingVector[0] * diagonalLength;
			new_position[1] = center[1] + 2.5f * viewingVector[1] * diagonalLength;
			new_position[2] = center[2] + 2.5f * viewingVector[2] * diagonalLength;

			// set the camera field to be the diagonal length of the scene's bounding box
			new_fieldx = diagonalLength;
			new_fieldy = diagonalLength;

			new_up[0] = up[0];
			new_up[1] = up[1];
			new_up[2] = up[2];
		}
		else
		{
			// in this case only change the target
			new_target[0] = center[0];
			new_target[1] = center[1];
			new_target[2] = center[2];

			new_position[0] = position[0];
			new_position[1] = position[1];
			new_position[2] = position[2];

			new_up[0] = up[0];
			new_up[1] = up[1];
			new_up[2] = up[2];

			new_fieldx = fieldx;
			new_fieldy = fieldy;
		}
	    

		HC_Set_Camera(&new_position, &new_target, &new_up, new_fieldx, new_fieldy, proj);
		HC_Insert_Distant_Light (	new_position[0] - new_target[0],
									new_position[1] - new_target[1],
									new_position[2] - new_target[2]);


    return;
}

void CSimpleView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	HC_Control_Update (m_sDriverSegment, "redraw everything");
	HC_Update_Display ();
}


// initialize this view's unique palette (meaning that we aren't sharing a palette among
// all views, which should be quite rare)  
void CSimpleView::InitializePalette()
{
    if (m_pViewPalette != NULL) {
        delete m_pViewPalette;
        m_pViewPalette = NULL;
    }

    // Setup the Palette

    CSimpleDoc * pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    CMainFrame * pAppFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
    ASSERT(pAppFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)));

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

CPalette* CSimpleView::GetPalette()
{
    CMainFrame* pAppFrame = (CMainFrame *)AfxGetMainWnd();

    if (pAppFrame->SharedPalette())
        return (pAppFrame->GetSharedPalette());
    else
        return m_pViewPalette;
}

void CSimpleView::OnEditCopy() 
{
	BeginWaitCursor();

	// Clean clipboard of contents and copy.
	if (OpenClipboard()) {
		EmptyClipboard();
		CloseClipboard();
	}

	CDC * hDC = GetDC();

	CMetaFileDC     hMfDC;

	hMfDC.CreateEnhanced(hDC, NULL, NULL, NULL);
	ReleaseDC (hDC);

	char driver[256];
	sprintf(driver, "/driver/msw/clipboard");

	HC_Open_Segment (driver);
		// first let's do the generic print driver set up
		char szTemp[256];

		sprintf (szTemp, "use window ID = %u", m_hWnd);
		HC_Set_Driver_Options (szTemp);

		sprintf (szTemp, "use window ID2 = %u", hMfDC.GetSafeHdc());
		HC_Set_Driver_Options (szTemp);

		long debug_flags = 0;
		debug_flags |= DEBUG_CLIPBOARD_MODE;
		debug_flags |= DEBUG_FORCE_FULL_COLOR;

		if (GetRenderMode() == SHADED)
			debug_flags |= DEBUG_SFB_COPY_TO_CLIPBOARD;

		sprintf (szTemp, "debug = %u", debug_flags);
		HC_Set_Driver_Options (szTemp);

		sprintf (szTemp, "special events, disable input=all, subscreen stretching, subscreen = (-1.0, 1.0, -1.0, 1.0)");
		HC_Set_Driver_Options ( szTemp);

		HPoint	window_color;
		window_color.x = 1.0;
		window_color.y = 1.0;
		window_color.z = 1.0;

		HC_Set_Color_By_Value("windows", "RGB", window_color.x, window_color.y, window_color.z);

		// now depending on the rendermode we take three different approaches to printing
		int renderMode = GetRenderMode();
		if (renderMode == SHADED)
		{
			HC_Set_Rendering_Options("hsra = szb, technology = sfb");
		}
		else if (renderMode == HIDDENLINE) //non rasterOutput path
		{
			char string[1024], hlr[2048];
			HC_Show_One_Net_Rendering_Optio("hidden line removal options", string);
			sprintf(hlr, "hsra=hidden line, hlro=(%s)", string);
			HC_Set_Rendering_Options("hsra=hidden line, hlro=(visibility=off)");
		}
		else if (renderMode == WIREFRAME) 
		{
			HC_Set_Heuristics("no hidden surfaces");
		}

		HC_Include_Segment_By_Key(m_lSceneKey);

	HC_Close_Segment();

	HC_Control_Update (driver, "redraw everything");
	HC_Update_Display ();
	HC_Delete_Segment (driver);


	HENHMETAFILE    hEmf;

	hEmf = hMfDC.CloseEnhanced ();

	if (hEmf == NULL) 
	{
		MessageBox ("Error creating enhanced metafile for clipboard", "Copy to Clipboard Error", MB_OK);
		EndWaitCursor();
		return;	
	}

	if (OpenClipboard()) 
	{
			SetClipboardData (CF_ENHMETAFILE, hEmf);
		CloseClipboard();
	}

	DeleteEnhMetaFile(hEmf);
	EndWaitCursor();

	return;
}


void CSimpleView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	char driver[256];
	sprintf(driver, "/driver/msw/printer");

	HC_Open_Segment (driver);
		// first let's do the generic print driver set up
		char szTemp[256];

		sprintf (szTemp, "use window ID = %u", ::GetDesktopWindow());
		HC_Set_Driver_Options (szTemp);

		HC_Set_Window_Frame ("off");
		sprintf (szTemp, "use window ID2 = %u", pDC->m_hAttribDC);
		HC_Set_Driver_Options (szTemp);

		sprintf (szTemp, "output format = %u", pDC->m_hDC);
		HC_Set_Driver_Options (szTemp);

		long debug_flags = 0;
		debug_flags |= DEBUG_PRINTING_MODE;
		debug_flags |= DEBUG_PRINT_NOT_FRAMEBUFFER_MODE;
		debug_flags |= DEBUG_PRINT_NOT_RASTER_REDUCTION;

		sprintf (szTemp, "debug = %u", debug_flags);
		HC_Set_Driver_Options (szTemp);

		float SubscreenXmin, SubscreenXmax, SubscreenYmin, SubscreenYmax;
		SubscreenXmin = -1.0f;
		SubscreenXmax = 1.0f;
		SubscreenYmin =  -1.0f;
		SubscreenYmax = 1.0f;
		sprintf (szTemp, "special events, disable input=all, subscreen stretching, subscreen = (%f, %f, %f, %f)",  SubscreenXmin, SubscreenXmax, SubscreenYmin, SubscreenYmax);
		HC_Set_Driver_Options ( szTemp);

		int renderMode = GetRenderMode();

		// now depending on the rendermode we take three different approaches to printing
		if (renderMode == SHADED)
		{
			char					buffer[1024];
			HPoint					window_color;
			HC_KEY					image_key;

			//let's determine the size of the page we are printing to so that we can create an
			//approriately sized image
			int w=pDC->GetDeviceCaps(HORZRES);
			int h=pDC->GetDeviceCaps(VERTRES);
			float aspect_ratio = (float)h/(float)w;

			float resolution_w = (float)pDC->GetDeviceCaps(LOGPIXELSX);
			float page_width = (float)w/resolution_w;
			float resolution_h = (float)pDC->GetDeviceCaps(LOGPIXELSY);
			float page_height = (float)h/resolution_h;
			
			//let's our stretch blit image 100 dpi
			int image_dpi=100;
			int iwidth = (int) (page_width*image_dpi*0.5*(SubscreenXmax-SubscreenXmin)) ;
			int iheight =(int)(page_height*image_dpi*0.5*(SubscreenYmax-SubscreenYmin));

			//prepare image for rendering
			HC_Open_Segment ("?driver/null/1");
				image_key = HC_KInsert_Image(0.0, 0.0, 0.0, "rgb, name=background", iwidth, iheight, NULL);
			HC_Close_Segment ();

			window_color.x = 1.0;
			window_color.y = 1.0;
			window_color.z = 1.0;

			// prepare data to render
			HC_Open_Segment ("?driver/image/1");
				HC_Set_Color_By_Value("windows", "RGB", window_color.x, window_color.y, window_color.z);
				sprintf (buffer, "use window id = %ld", image_key);
				HC_Set_Driver_Options (buffer);
				HC_Set_Rendering_Options("hsra = szb");
				HC_Set_Window_Frame("off");
				HC_Include_Segment_By_Key (m_lSceneKey);
				HC_Set_Visibility("lines=off, text=off");
				HC_Set_Rendering_Options("attribute lock= (visibility=(lines, text))");
			HC_Close_Segment ();

			//create the image
			HC_Update_Display ();

			// put this image in the background
			HC_Set_Color("windows=background");
			HC_Set_Rendering_Options("hsra=hidden line, hlro=(visibility=off)");
		}
		else if (renderMode == HIDDENLINE) //non rasterOutput path
		{
			char string[1024], hlr[2048];
			HC_Show_One_Net_Rendering_Optio("hidden line removal options", string);
			sprintf(hlr, "hsra=hidden line, hlro=(%s)", string);
			HC_Set_Rendering_Options("hsra=hidden line, hlro=(visibility=off)");
		}
		else if (renderMode == WIREFRAME) 
		{
			HC_Set_Heuristics("no hidden surfaces");
		}

		HC_Include_Segment_By_Key(m_lSceneKey);


	HC_Close_Segment();

	HC_Control_Update (driver, "redraw everything");
	HC_Update_Display ();
	HC_Delete_Segment (driver);

	if (renderMode == SHADED)
	{
		HC_Delete_Segment ("?driver/null/1");
		HC_Delete_Segment ("?driver/image/1");
		HC_UnDefine_Texture("background");
	}
}

void CSimpleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
}


BOOL CSimpleView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CSimpleView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnLButtonDown(nFlags, point);

	m_bOperatorStarted=true;

	m_ptFirstPoint.x = (float) point.x;
	m_ptFirstPoint.y = (float) point.y;
	m_ptFirstPoint.z = 0.0;

	HC_Open_Segment(m_sDriverSegment);
		HC_Compute_Coordinates(".", "local pixels", &m_ptFirstPoint, "local window", &m_ptFirstPoint);
	HC_Close_Segment();

	float tmp,vl;

	// map screen mouse points to sphere mouse points
	tmp = (m_ptFirstPoint.x * m_ptFirstPoint.x + m_ptFirstPoint.y * m_ptFirstPoint.y);
	vl = (float)sqrt(tmp);

	// remember screen mouse position
	m_ptRealOld.x = m_ptFirstPoint.x;
	m_ptRealOld.y = m_ptFirstPoint.y;

	if (vl > 1.0f) 
	{
		m_ptFirstPoint.x /= vl;
		m_ptFirstPoint.y /= vl;
		m_ptFirstPoint.z = 0.0;
	}
	else
		m_ptFirstPoint.z = (float) sqrt (1.0f - tmp);

	return;
}



void CSimpleView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnLButtonUp(nFlags, point);
	m_bOperatorStarted = false;

	return;
}

void CSimpleView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CView::OnMouseMove(nFlags, point);

	if (m_bOperatorStarted)
	{	
		HPoint axis, vtmp, real_new, newPoint;	
		float theta, dist, tmp, vl, angle1, angle2, angle3;

		newPoint.x = (float) point.x;
		newPoint.y = (float) point.y;
		newPoint.z = 0.0;

		HC_Open_Segment(m_sDriverSegment);
			HC_Compute_Coordinates(".", "local pixels", &newPoint, "local window", &newPoint);
		HC_Close_Segment();
		
		// remember the real mouse positions
		real_new.x = newPoint.x;
		real_new.y = newPoint.y;

		// map screen mouse points to sphere mouse points
		tmp = newPoint.x * newPoint.x + newPoint.y * newPoint.y;
		vl = (float)sqrt(tmp);

		if (vl > 1.0f) 
		{
			newPoint.x /= vl;
			newPoint.y /= vl;
			newPoint.z = 0.0f;
		}
		else
			newPoint.z = (float)sqrt(1.0f - tmp);

		// get the axis of rotation
		HC_Compute_Cross_Product (&m_ptFirstPoint, &newPoint, &axis);
		
		// this is for screen mouse based movement
		vtmp.x = real_new.x - m_ptRealOld.x;
		vtmp.y = real_new.y - m_ptRealOld.y;
		dist = (float)sqrt(vtmp.x * vtmp.x + vtmp.y * vtmp.y) * 90.0f;
		
		if ((axis.x != 0.0 || axis.y != 0.0 || axis.z != 0)){

			HC_Compute_Normalized_Vector(&axis, &axis);
			HC_Open_Segment_By_Key(m_lSceneKey);
		
				// project axis of rotation onto yz plane 
				vtmp.x = 0.0;
				vtmp.y = axis.y;
				vtmp.z = axis.z;

				// calculate angle of x orbit
				tmp = (float)HC_Compute_Dot_Product(&axis, &vtmp);
				if(fabs(tmp) > 1.001f || fabs(tmp) < 0.999f)		
					theta = (float)acos(tmp);
				else
					theta = 0.0f;
			
				if (axis.x < 0.0)
					angle2= -theta * dist;
				else
					angle2=theta * dist;
				
				// project axis of rotation onto xz plane 
				vtmp.x = axis.x;
				vtmp.y = 0.0;
				vtmp.z = axis.z;

				// calculate angle of y orbit
				tmp = (float)HC_Compute_Dot_Product(&axis, &vtmp);
				if (fabs(tmp) > 1.001f || fabs(tmp) < 0.999f)		
					theta = (float)acos(tmp);
				else
					theta = 0.0f;
				
				if (axis.y < 0.0)
					angle1=theta * dist;
				else
					angle1=-theta * dist;
			
				// project axis of rotation onto xy plane 
				vtmp.x = axis.x;
				vtmp.y = axis.y;
				vtmp.z = 0.0;

				// calculate angle of z orbit
				tmp = (float)HC_Compute_Dot_Product(&axis, &vtmp);
				if(fabs(tmp) > 1.001f || fabs(tmp) < 0.999f)		
					theta = (float)acos(tmp);
				else
					theta = 0.0f;

				if (axis.z < 0.0)
					angle3=theta * dist;
				else
					angle3=-theta * dist;

 				HC_Orbit_Camera(angle1,0);
 				HC_Orbit_Camera(0,angle2);
				HC_Roll_Camera(angle3);

 			HC_Close_Segment();
		}

		// update sphere space mouse
		m_ptFirstPoint.x = newPoint.x;
		m_ptFirstPoint.y = newPoint.y;
		m_ptFirstPoint.z = newPoint.z;

		// update screen space mouse
		m_ptRealOld.x = real_new.x;
		m_ptRealOld.y = real_new.y;
		
		HC_Update_Display();
	}

	return;
}

void CSimpleView::OnViewWireframe() 
{
	HC_Open_Segment_By_Key(m_lDriverKey);
 		HC_Set_Heuristics("no hidden surfaces");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(m_lSceneKey);
		HC_Set_Visibility("faces = off, edges=on, lights=off");
	HC_Close_Segment();
	HC_Update_Display();

}

void CSimpleView::OnUpdateViewWireframe(CCmdUI* pCmdUI) 
{
	int hlr = GetRenderMode();

	if (hlr == WIREFRAME)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);

}

void CSimpleView::OnViewShaded() 
{
	HC_Open_Segment_By_Key(m_lDriverKey);
        if (!strcmp (theApp.GetDriverType(), "opengl")) {
            HC_Set_Rendering_Options ("hsr algorithm = hardware z-buffer");
        }
        else {
            HC_Set_Rendering_Options ("hsra = software z buffer");
        }
		HC_Set_Heuristics("hidden surfaces");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(m_lSceneKey);
		HC_Set_Visibility("faces = on, edges=off, lights=on");
	HC_Close_Segment();

	HC_Update_Display();
}

void CSimpleView::OnUpdateViewShaded(CCmdUI* pCmdUI) 
{
	int hlr = GetRenderMode();

	if (hlr == SHADED)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CSimpleView::OnViewHiddenline() 
{
	HC_Open_Segment_By_Key(m_lDriverKey);
        HC_Set_Rendering_Options ("hsr algorithm = hidden line, hlro=(visibility=off)");
 		HC_Set_Heuristics("hidden surfaces");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(m_lSceneKey);
		HC_Set_Visibility("faces = on, edges=on, lights=off");
	HC_Close_Segment();
	HC_Update_Display();
	
}

void CSimpleView::OnUpdateViewHiddenline(CCmdUI* pCmdUI) 
{
	int hlr = GetRenderMode();

	if (hlr == HIDDENLINE)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


int CSimpleView::GetRenderMode()
{
	// This function uses the following logic to determine what render mode
	// we are in.  If hidden surfaces are turned off then we are in wireframe
	// mode.  If hidden surfaces are turned on, and the hsra is hidden line
	// then we are in 'hidden line' mode.  If the hsra has a 'z buffer' in it
	// then it is either hardware z buffer or software z buffer both of which
	// are shaded modes

	char hsralg[1024], hs[512];
	int hsra;

	HC_Open_Segment(m_sDriverSegment);
		HC_Show_One_Net_Heuristic("hidden surfaces", hs);

		if ((strstr (hs, "no") || strstr (hs, "off")))
			hsra = WIREFRAME;
		else
		{
			HC_Show_One_Net_Rendering_Optio("hidden surface removal algorithm", hsralg);
			if (strstr(hsralg, "hidden line"))
				hsra = HIDDENLINE;
			else if (strstr(hsralg, "z buffer"))
				hsra=SHADED;
		}
	HC_Close_Segment();

	return hsra;
}

void CSimpleView::OnRunMyCode() 
{
	// this is a function in which developers can
	// write their own simple HOOPS functions
	AfxMessageBox("I love HOOPS!!!!!");		
}
