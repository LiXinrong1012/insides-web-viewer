//
// Copyright (c) 2002 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/Hoops3dStreamCtrl.cpp,v 1.211 2010-06-22 23:57:28 boni Exp $
//

#include "stdafx.h"
#include "Hoops3dStream.h"
#include "Hoops3dStreamCtrl.h"
#include "HBaseView.h"
#include "HBaseModel.h"
#include "HEventInfo.h"
#include "HEventManager.h"
#include "HBaseOperator.h"
#include "HOpCameraOrbit.h"
#include "HOpCameraPan.h"
#include "HOpCameraZoom.h"
#include "HOpCameraWalk.h"
#include "HOpCameraManipulate.h"
#include "HOpCameraZoomBox.h"
#include "HOpObjectAnnotate.h"
#include "HOpMarkupFreehand.h"
#include "HOpConstructCircle.h"
#include "HOpConstructCuboid.h"
#include "HOpConstructPolyline.h"
#include "HOpConstructRectangle.h"
#include "HOpCreateCone.h"
#include "HOpCreateCuttingPlane.h"
#include "HOpCreateCylinder.h"
#include "HOpCreateNurbs3D.h"
#include "HOpCreateNurbsCurve.h"
#include "HOpCreateSphere.h"
#include "HOpMarkupAnnotate.h"
#include "HOpMarkupPostIt.h"
#include "HOpMarkupCircle.h"
#include "HOpMarkupMeasure.h"
#include "HOpMarkupRectangle.h"
#include "HOpMoveHandle.h"
#include "HOpNavCube.h"
#include "HOpObjectClash.h"
#include "HOpObjectRotate.h"
#include "HOpSelectAperture.h"
#include "HOpSelectArea.h"
#include "HOpSelectPolygon.h"
#include "HOpSelectPolyline.h"
#include "HBhvBehaviorManager.h"
#include "HBhvTimeline.h"
#include "HBhvAnimation.h"
#include "HSelectionSet.h"
#include "HUndoManager.h"
#include "HConstantFramerate.h"
#include "HStream.h"
#include "hc.h"
#include "Hdb.h"
#include "AppearanceDlg.h"
#include "vlist.h"
#include "DataLoader.h"
#include "HMySelectionSet.h"
#include "hic.h"

#include "HCtrlView.h"
#include "HConstantFramerate.h"
#include "HCtrlDB.h"
#include "AboutDlg.h"

#include "HIOUtilityGDIOutput.h"

#include "HUtilityGeometryCreation.h"
#include "HMarkupManager.h"
#include "HUtilityXMLParser.h"
#include "HUtilityLocaleString.h"
 
#include "HUtilityXMLParser.h"
#include <wchar.h>

#define AXIS_WIDTH 110					 
#define AXIS_HEIGHT 90					 

#define PROCESS_MESSGAGE_TIMER	10
#define FRAMERATE_TIMER			1
#define STREAM_TIMER			2
#define LOAD_TIMER				3
#define TICK_TIMER				4

static HCtrlDB * pDB = 0;

bool blockit = false;

HANDLE hMutex; 

HHOOK CHoops3dStreamCtrl::hHook = 0;
bool CHoops3dStreamCtrl::menuActive = false;

#ifndef _UNICODE
#define CtU(x,y)     (strcpy(y, x), y)
#define UtC(x,y)     (strcpy(y, x), y)
#define UtC2(x,y,z)     (memcpy(y, x,z), y[z] = 0, y)
#else
#define CtU(x,y)     (mbstowcs(y, x, strlen(x) + 1), y)
#define UtC(x,y)     (wcstombs(y, x, 1000), y)
#define UtC2(x,y,z)     (wcstombs(y, x, z), y[z] = 0, y)
#endif

		     
#define BOOL2bool(TRUE_Or_FALSE)	\
	(( TRUE_Or_FALSE == TRUE ) ? true : false)

#define bool2BOOL(true_or_false)	\
	(( true_or_false == true ) ? TRUE : FALSE )


/*
static TCHAR * CtU(const char *x,TCHAR *y) 
{
    mbstowcs(y, x, strlen(x)); 
    return y;
}

static char * UtC(TCHAR *x,char *y) 
{
    wcstombs(y, x, 1000); 
    return y;
}
static char * UtC(TCHAR *x,char *y, int maxsize) 
{
    wcstombs(y, x, maxsize); 
    y[maxsize] = 0;
    return y;
}
*/
/*!
	Constructor
*/ 
CHoops3dStreamCtrl::CHoops3dStreamCtrl()
{
		m_bWindowOnly = TRUE;
		m_bFileOpenActive = false;

		m_bIs2dModel = false;
		m_bNoOrbit = false;
 		m_pView = 0;
		m_pModel = 0;
		m_pHDB = 0;
		m_text = true;
		m_lines = false;
		m_faces = true;
		m_FrameRate = 0.05f;
		strcpy(m_DriverType, "opengl");
		strcpy(m_TransparencyOptions,"style = blended, hsr algorithm = depth peeling,depth peeling options=(layers= 1)");
		m_bSegmentDL = false;
		m_bStaticModel = false;
		m_AntialiasingLevel = 4;
		m_CullingThreshold = 1;
		m_MaximumThreshold = 150;
		m_FramerateType = FramerateTarget;
		m_bMetaPrint = FALSE;
		m_bFastPrint = TRUE;
		m_MetafileType = EMF;
		m_bClipboardTruecolor = true;

		m_Filename = 0;
		m_bFilenameChanged = false;		
		m_bEmbed = false;
 		m_bCameraRestored = false;
 		m_bUseAntialiasing = false;
		m_pDataLoader = 0;
		m_window_bottom_color.Set(1.0f, 1.0f, 1.0f);
		m_window_top_color.Set(1.0f, 1.0f, 1.0f);
		m_ambient_color.Set(0.3f, 0.3f, 0.3f);
		m_bAllowMenu				= true;
		m_bUseHardwareAntialiasing	= true;
		m_CookieSelected			= 0;
		m_CookieDeSelectedAll		= 0;
		m_bAllowEntitySelection = true;
		m_iPrintFlag				= 1;

		InitModel();
		pDB->AddRef();
				
		hMutex = CreateMutex(NULL,FALSE,_T("streammutex"));   
		m_bJustCreated = true;
		m_StoredAxisMode = AxisOn;
		m_bSoftwareRendering = false;
		m_FileTypeList = new_vlist(malloc,free);
		m_ConfigurationList= new_vlist(malloc,free);
		strcpy(m_ConfigFile,"");
		strcpy(m_DefaultConfigFile,"");
		m_bShadowMode = false;
		m_bDataNavigatorMode = true;
		m_bContinuousPlay = false;
		m_bFlushOnLoad = true;

		LastKey = 0;
		/* test */
		strcpy(String1,"");
		strcpy(String2,"");
		strcpy(String3,"");
		Int1 = 0;	
}


/*!
	Destructor
*/ 

CHoops3dStreamCtrl::~CHoops3dStreamCtrl()
{
    if (m_pDataLoader && m_pDataLoader->m_ParsingThread)
    {    
	::TerminateThread((HANDLE)m_pDataLoader->m_ParsingThread,0);
	Sleep(1000);
    }

	if( m_pView )
	{
		if( m_CookieSelected != 0)
		{
			m_pView->UnSetSignalNotify( m_CookieSelected );
			m_CookieSelected = 0;
		}
		if( m_CookieDeSelectedAll != 0)
		{
			m_pView->UnSetSignalNotify( m_CookieDeSelectedAll );
			m_CookieDeSelectedAll = 0;
		}

		delete m_pView;
		m_pView = 0;
	}

	delete m_pDataLoader;
	m_pDataLoader = 0;

	delete m_pModel;
	m_pModel = 0;
	
	if (pDB)	
	{
		pDB->ReleaseRef ();
		if (!pDB->GetRefCount())
		{
			delete pDB;
			pDB = 0;
		}
	}
	SysFreeString(m_Filename);
	START_LIST_ITERATION(char, m_FileTypeList)
	    delete temp;
	END_LIST_ITERATION(m_FileTypeList);
	delete_vlist(m_FileTypeList);
	START_LIST_ITERATION(HUtilityXMLTag, m_ConfigurationList)
	    delete temp;
	END_LIST_ITERATION(m_ConfigurationList);
	delete_vlist(m_ConfigurationList);
}
 

/*!
	Setup HOOPS 3DGS and Model
	
*/ 
void CHoops3dStreamCtrl::InitModel()
{

	if (!pDB) 
	{
		pDB = new HCtrlDB();
	 	pDB->Init();
	}

 	if (!m_pModel)
	{
		m_pModel       = new HBaseModel ();
		m_pModel->Init();
	}
}



void CHoops3dStreamCtrl::MakePalette()
{
		HDC	cdc = GetDC();

		m_pPalette = 0;
        int rc = GetDeviceCaps(cdc,RASTERCAPS);
    
        if (rc & RC_PALETTE) {
 
//            HPalette *m_pPalette = new CPalette;

            LPLOGPALETTE 		Palette;
            int		            nStaticColors;
	        DWORD	            *dword_ptr;
	        int		            nColors;
            int                 i;

	        /* Get the static colors from the system palette */
	        nStaticColors = GetDeviceCaps (cdc,NUMCOLORS);
	        nColors = GetDeviceCaps (cdc, SIZEPALETTE);

	        Palette = (LPLOGPALETTE) malloc (sizeof(LOGPALETTE) + sizeof (PALETTEENTRY) * nColors);
	        Palette->palVersion = 0x300;
	        Palette->palNumEntries = nColors;

            nColors = GetSystemPaletteEntries (cdc, 0, nColors, Palette->palPalEntry);

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
	        m_pPalette = CreatePalette ( Palette );
	        free (Palette);

	        UnrealizeObject(m_pPalette);
	        SelectPalette (cdc,m_pPalette, FALSE);
	        RealizePalette (cdc);

        }

        ReleaseDC (cdc);




}

void CHoops3dStreamCtrl::set_menu_active(bool active)
{	
	menuActive = active;
}

void CHoops3dStreamCtrl::create_mouse_hook(HINSTANCE hinst)
{
	WaitForSingleObject(hMutex,INFINITE);

	if (CHoops3dStreamCtrl::hHook == 0)
	{		
		hHook = SetWindowsHookEx(WH_MOUSE,mouse_hook_callback,hinst,0);
	}

	ReleaseMutex(hMutex);	
}

#ifndef WM_XBUTTONDOWN
#define WM_XBUTTONDOWN                  0x020B
#endif 

#ifndef WM_XBUTTONUP
#define WM_XBUTTONUP                    0x020C
#endif

LRESULT CALLBACK CHoops3dStreamCtrl::mouse_hook_callback(int code,WPARAM wParam, LPARAM lParam)
{
	LRESULT result = CallNextHookEx(hHook,code,wParam,lParam);

	if (wParam == WM_XBUTTONDOWN || wParam == WM_XBUTTONUP)
	{
		// block the message
		if (menuActive)		
			return 1;		
	}		

	return result;
}

/*!
	Creates new Control Window
	Main Initialization
*/ 
HWND CHoops3dStreamCtrl::Create( HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName, DWORD dwStyle, DWORD dwExStyle, UINT nID )
{

	CWindowImpl<CHoops3dStreamCtrl>::Create(hWndParent, rcPos, szWindowName, dwStyle,dwExStyle, nID); 		 

	

	MakePalette();
    if (!m_pView)
	{
		m_pView = (HCtrlView *) new HCtrlView(m_pModel, NULL, m_DriverType, NULL, (void *)m_hWnd, m_pPalette);
		if (m_bUseHardwareAntialiasing)
			m_pView->SetHardwareAntialiasing(m_AntialiasingLevel);
 		m_pView->Init();
   		m_pView->ReconfigureView (m_hWnd, m_pPalette, m_DriverType);
 		m_pView->SetSmoothTransition(true);
		m_pView->SetWindowColor(m_window_top_color, m_window_bottom_color);
	}
	else
	{
		if (m_bUseHardwareAntialiasing)
			m_pView->SetHardwareAntialiasing(m_AntialiasingLevel);
 		 m_pView->ReconfigureView (m_hWnd, m_pPalette, m_DriverType);
		 m_pView->SetWindowColor(m_window_top_color, m_window_bottom_color);
	
	}
	m_pView->SetCullingThreshold(m_CullingThreshold);
	m_pView->SetTransparency(m_TransparencyOptions,true);
 	if (!m_pDataLoader)
		m_pDataLoader = new CDataLoader(this);
	m_pDataLoader->Init(m_pView);

 	RestoreCamera();

	SetDirty(true);
 
	HC_Open_Segment_By_Key(m_pView->GetViewKey());
		HC_Set_Driver_Options("no special events, no update interrupts");
		HC_Set_Driver_Options("selection proximity = 0.1");
		if (m_bUseHardwareAntialiasing)
		{
			char text[4096];
 			sprintf(text, "anti-alias = %d", m_AntialiasingLevel);
			HC_Set_Driver_Options(text);
 			HC_Set_Rendering_Options("anti-alias = (screen, text, no lines)");
		}
	HC_Close_Segment();

	LocalSetOperator(new HOpCameraManipulate(m_pView));

	Set2dModel(m_bIs2dModel);
	SetNoOrbit(m_bNoOrbit);
 


	for (int i=0;i<NUM_MARKUP_LAYERS;i++)
		m_activelayerkeys[i] = 1;	
	
	if (m_bFilenameChanged)
		StartDownload();

	SetTimer(TICK_TIMER,5);
	HC_Open_Segment_By_Key(m_pView->GetSceneKey());
		HC_Set_Rendering_Options("color interpolation");
	HC_Close_Segment();

	m_pView->SetBackplaneCulling(false);
	m_pView->SetPolygonHandednessMode(HandednessLeft);
  	m_pView->SetViewUpdateMode(Continuous);
	HPoint shadowcolor(0.2f,0.2f,0.2f);
	HPoint markupcolor(0.2f,0.2f,0.2f);
	m_pView->SetShadowResolution(64);
	m_pView->SetShadowBlurring(4);
	m_pView->SetShadowColor(shadowcolor);
	m_pView->GetMarkupManager()->SetMarkupColor(markupcolor);
	m_pView->SetDisplayListMode(true);


	m_pView->SetDisplayListType(DisplayListGeometry);



	m_pView->SetHandedness(HandednessRight);
	m_pView->GetSelection()->SetAllowEntitySelection(m_bAllowEntitySelection);

	// subscribe to selection events
	m_CookieSelected = m_pView->SetSignalNotify(HSignalSelected, CHoops3dStreamCtrl::signal_selected, this);
	m_CookieDeSelectedAll = m_pView->SetSignalNotify(HSignalDeSelectedAll, CHoops3dStreamCtrl::signal_deselected_all, this);

	m_pView->GetModel()->GetBhvBehaviorManager()->SetContinuousPlay(m_bContinuousPlay);
	SetShadowMode(m_bShadowMode);
	m_bJustCreated = false;       

	HC_Open_Segment_By_Key(m_pView->GetCuttingPlanesKey());
		HC_Open_Segment("plane1");
		if (HC_Show_Existence("modelling matrix"))
			HC_UnSet_Modelling_Matrix();
	HC_Close_Segment();

	    HC_Open_Segment("plane2");
	    if (HC_Show_Existence("modelling matrix"))
		HC_UnSet_Modelling_Matrix();
	HC_Rotate_Object(90,0,0);
	HC_Close_Segment();
	HC_Open_Segment("plane3");
	    if (HC_Show_Existence("modelling matrix"))
		HC_UnSet_Modelling_Matrix();
	HC_Rotate_Object(0,0,90);
	HC_Close_Segment();
	HC_Close_Segment();

	HOpMoveHandle *handleoperator = new HOpMoveHandle(m_pView, false);
	
 	m_pView->SetHandleOperator(handleoperator);

	HSelectionSet *selection =  m_pView->GetSelection();
	delete selection;
	selection = (HMySelectionSet *)new HMySelectionSet(m_pView, m_pDataLoader);
	selection->Init();
	m_pView->SetSelection(selection);
	((HMySelectionSet *)selection)->SetModelStructureFilter("");
 	m_bFirstRun = true;

	/* This will load any hio plugins found in the user's path */
	(void)HDB::GetHIOManager();

	create_mouse_hook((HINSTANCE)GetWindowLongPtr(GWLP_HINSTANCE));

 	return (m_hWnd);	
}

/*!
	executes a HOOPS update directed either to a metafile or to the screen depending on the 
	control state

*/ 
HRESULT CHoops3dStreamCtrl::OnDraw(ATL_DRAWINFO& di)
{
    // execute a HOOPS update if we have a valid HBaseView object
    
    static bool running = false;
    if (!running)
    {
	running = true;

	WaitForSingleObject(hMutex,INFINITE);   
	if (m_pView)
	{
	    m_cx = (int)fabs((float)(di.prcBounds->right - di.prcBounds->left));
	    m_cy = (int)fabs((float)(di.prcBounds->bottom - di.prcBounds->top));
 	    if (GetDeviceCaps(di.hdcDraw, TECHNOLOGY) == DT_METAFILE || m_iPrintFlag == 1)
 			DrawToMetafile (m_hWnd, di.hdcDraw);
	    else
	    {
			m_iPrintFlag = 1;
			if (m_hWnd)
			{
			    
			    
				if (m_pView->GetViewKey() != -1)
				{
					HC_Control_Update_By_Key (m_pView->GetViewKey(), "redraw everything");
					m_pView->Update();
				}
			    
			}
	    }
		if (m_bFirstRun)
		{
		    ConfigureFromFile();
		    m_bFirstRun = false;
		}
	    
	}
	else
	{
	    RECT& rc = *(RECT*)di.prcBounds;
	    Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	}
	
	ReleaseMutex(hMutex);
	running = false;
    }
    
    return S_OK;
}


/*! 
    Calls the OnLButtonDown method of the view's current HOOPS/MVO HBaseOperator object.  The GUI specific flags are
    mapped to HOOPS/MVO abstracted flags use the MapFlags method 
*/

LRESULT CHoops3dStreamCtrl::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_pView->SceneDetached() && m_bUIActive)
	{
		WaitForSingleObject(hMutex,INFINITE);		
		
		HEventInfo      event(m_pView);
		//HBaseOperator * op = m_pView->GetCurrentOperator();
		int xPos = 	GET_X_LPARAM(lParam);
		int yPos = 	GET_Y_LPARAM(lParam);
		
		HC_KEY key = -1;
		int offset1,offset2,offset3;
		
		HPoint localpixels, localwindow;
		localpixels.Set((float)xPos,(float) yPos, 0);
		
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
		HC_Compute_Coordinates(".", "local pixels", &localpixels, "local window", &localwindow);
		HC_Close_Segment();
		HC_Open_Segment_By_Key(m_pView->GetViewKey());
		HC_Set_Driver_Options("selection proximity = 0.0");
		if ( HC_Compute_Selection(".",".","v", localwindow.x, localwindow.y))
		{	
			HC_Show_Selection_Element (&key, &offset1, &offset2, &offset3);
			
		}
		HC_Close_Segment();
		
		if (key != -1)
		{
			char type[MVO_BUFFER_SIZE];
			HC_Show_Key_Type(key, type);
			if (strcmp(type,"segment") != 0)
				key = HC_KShow_Owner_By_Key(key);
			HUtility::UnwindIncludes(key);
			if (HUtility::IsModelKey(m_pView->GetModelKey(),key))
				m_pView->FitSelection(key);
		}
		else
			m_pView->ZoomToExtents();
		
		m_pView->Update();
		
		DefWindowProc(uMsg, wParam, lParam);

		ReleaseMutex(hMutex);
	}
	return 0;
}
 


/*! 
    Calls the OnLButtonDown method of the view's current HOOPS/MVO HBaseOperator object.  The GUI specific flags are
    mapped to HOOPS/MVO abstracted flags use the MapFlags method 
*/

LRESULT CHoops3dStreamCtrl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_pView->SceneDetached() && m_bUIActive)
	{
		WaitForSingleObject(hMutex,INFINITE);
				
		HEventInfo      event(m_pView);
		HBaseOperator * op = m_pView->GetCurrentOperator();
	 	int xPos = 	GET_X_LPARAM(lParam);
		int yPos = 	GET_Y_LPARAM(lParam);
		if (op) {
			SetCapture();
			::SetFocus(m_hWnd);
			event.SetPoint(HE_LButtonDown,xPos,yPos,MapFlags(wParam));
	 		HLISTENER_EVENT(HMouseListener, m_pView->GetEventManager(), OnLButtonDown(event))
		}
		DefWindowProc(uMsg, wParam, lParam);

		ReleaseMutex(hMutex);
	}
	return 0;
}


 
/*! 
    MouseWheel Zooming

*/
LRESULT CHoops3dStreamCtrl::OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) 
{
	if (!m_pView->SceneDetached() && m_bUIActive)
	{
		WaitForSingleObject(hMutex,INFINITE);

		HEventInfo	event(m_pView);
		HBaseOperator *op = m_pView->GetCurrentOperator();
		int zDelta = (short) HIWORD(wParam);    // wheel rotation

		if (op && zDelta) 
		{			
			HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			{
				float width, height;
				HPoint target, position, up;
				char proj[32];
				HC_Show_Net_Camera(&position, &target, &up, &width, &height, proj);

				if (proj[0]=='p')
				{
					HPoint delta;
					delta.Set(position.x-target.x, position.y-target.y, position.z-target.z);
					HC_Set_Camera_Position(position.x + (delta.x * 30 / zDelta), 
						position.y + (delta.y * 30 / zDelta), 
						position.z + (delta.z * 30 / zDelta));
				}
				else
				{
					double scaleFactor = pow(1.01, (double)zDelta/4.0);
					HC_Set_Camera_Field(width * scaleFactor, height * scaleFactor);
				}
			}
			HC_Close_Segment();
			m_pView->Update();
		}
	DefWindowProc(uMsg, wParam, lParam);

	ReleaseMutex(hMutex);

	}
	return 0;
}



/*! 
    Calls the OnLButtonUp method of the view's current HOOPS/MVO HBaseOperator object.  The GUI specific flags are
    mapped to HOOPS/MVO abstracted flags use the MapFlags method 
*/
LRESULT CHoops3dStreamCtrl::OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_pView->SceneDetached() && m_bUIActive)

	{

	WaitForSingleObject(hMutex,INFINITE);

	HEventInfo      event(m_pView);
	HBaseOperator * op = m_pView->GetCurrentOperator();
 	int xPos = 	GET_X_LPARAM(lParam);
	int yPos = 	GET_Y_LPARAM(lParam);

	if (op) {
		ReleaseCapture();

		event.SetPoint(HE_LButtonUp,xPos,yPos,MapFlags(wParam));
 		HLISTENER_EVENT(HMouseListener, m_pView->GetEventManager(), OnLButtonUp(event))
  
	}
	DefWindowProc(uMsg, wParam, lParam);

	ReleaseMutex(hMutex);

	}
	return 0;
}

/*! 
    Calls the OnLButtonUp method of the view's current HOOPS/MVO HBaseOperator object.  The GUI specific flags are
    mapped to HOOPS/MVO abstracted flags use the MapFlags method 
*/
LRESULT CHoops3dStreamCtrl::OnRButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_pView->SceneDetached() && m_bUIActive && !m_bAllowMenu)

	{

	WaitForSingleObject(hMutex,INFINITE);

	HEventInfo      event(m_pView);
	HBaseOperator * op = m_pView->GetCurrentOperator();
 	int xPos = 	GET_X_LPARAM(lParam);
	int yPos = 	GET_Y_LPARAM(lParam);

	if (op) {
		ReleaseCapture();

		event.SetPoint(HE_RButtonUp,xPos,yPos,MapFlags(wParam));
 		HLISTENER_EVENT(HMouseListener, m_pView->GetEventManager(), OnRButtonUp(event))
  
	}
	DefWindowProc(uMsg, wParam, lParam);

	ReleaseMutex(hMutex);

	}
	return 0;
}


/*! 
    Calls the OnMouseMove method of the view's current HOOPS/MVO HBaseOperator object.  The GUI specific flags are
    mapped to HOOPS/MVO abstracted flags use the MapFlags method 
*/

LRESULT CHoops3dStreamCtrl::OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_pView->SceneDetached() && m_bUIActive)
	{
 	DefWindowProc(uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT CHoops3dStreamCtrl::OnXMLParsingComplete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Fire_OnModelStructureParsed();
	m_pDataLoader->m_ParsingThread = 0;
	return 0;
}


/*! 
    Calls the OnMouseMove method of the view's current HOOPS/MVO HBaseOperator object.  The GUI specific flags are
    mapped to HOOPS/MVO abstracted flags use the MapFlags method 
*/

LRESULT CHoops3dStreamCtrl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (!m_pView->SceneDetached() && m_bUIActive)
    {

	WaitForSingleObject(hMutex,INFINITE);
	
	HEventInfo      event(m_pView);
	HBaseOperator * op = m_pView->GetCurrentOperator();
	int xPos = 	GET_X_LPARAM(lParam);
	int yPos = 	GET_Y_LPARAM(lParam);
	
	if (op) {
	    event.SetPoint(HE_MouseMove,xPos,yPos,MapFlags(wParam));
	    HLISTENER_EVENT(HMouseListener, m_pView->GetEventManager(), OnMouseMove(event))
	}	
	DefWindowProc(uMsg, wParam, lParam);

	ReleaseMutex(hMutex);

    }
    return 0;
}

/*! 
		Right Click Menu 
*/
LRESULT CHoops3dStreamCtrl::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_pView->SceneDetached() && m_bUIActive)
	{
		WaitForSingleObject(hMutex,INFINITE);

	    if (!m_bAllowMenu)
	    {

		HEventInfo      event(m_pView);
		HBaseOperator * op = m_pView->GetCurrentOperator();
	 	int xPos = 	GET_X_LPARAM(lParam);
		int yPos = 	GET_Y_LPARAM(lParam);
		if (op) 
		{
			SetCapture();
			::SetFocus(m_hWnd);
			event.SetPoint(HE_RButtonDown,xPos,yPos,MapFlags(wParam));
	 		HLISTENER_EVENT(HMouseListener, m_pView->GetEventManager(), OnRButtonDown(event))
		}
		DefWindowProc(uMsg, wParam, lParam);

		ReleaseMutex(hMutex);

		return 0;	

	    }

 
 	int xPos = 	GET_X_LPARAM(lParam);
	int yPos = 	GET_Y_LPARAM(lParam);

	RECT rect;

    GetWindowRect(&rect);

	rect.left += xPos;
	rect.top += yPos;

    HMENU menu = LoadMenu (_Module.GetResourceInstance( ) ,MAKEINTRESOURCE(IDR_VIEW_POPUP));
	menu = GetSubMenu(menu,0);

  

	const char *m_operator = m_pView->GetCurrentOperator()->GetName();

	EnableMenuItem(menu, ID_ORBIT, MF_ENABLED);
	EnableMenuItem(menu, ID_SMOOTH_SHADED, MF_ENABLED);
	EnableMenuItem(menu, ID_FLAT_SHADED, MF_ENABLED);
	EnableMenuItem(menu, ID_HIDDEN_LINE, MF_ENABLED);
	EnableMenuItem(menu, ID_SHADOW_SMOOTH, MF_ENABLED);
	EnableMenuItem(menu, ID_ANTIALIASING, MF_ENABLED);
	EnableMenuItem(menu, ID_FILEOPEN, MF_ENABLED);

	if (m_bIs2dModel)
	{
	    EnableMenuItem(menu, ID_ORBIT, MF_GRAYED);
	    EnableMenuItem(menu, ID_SMOOTH_SHADED, MF_GRAYED);
	    EnableMenuItem(menu, ID_FLAT_SHADED, MF_GRAYED);
	    EnableMenuItem(menu, ID_HIDDEN_LINE, MF_GRAYED);
	    EnableMenuItem(menu, ID_SHADOW_SMOOTH, MF_GRAYED);
	    EnableMenuItem(menu, ID_ANTIALIASING, MF_GRAYED);
	    
	}
 
    if (m_bNoOrbit)
		EnableMenuItem(menu, ID_ORBIT, MF_GRAYED);
	
	
	if (streq(m_operator, "HOpCameraOrbit"))
		CheckMenuItem(menu,ID_ORBIT, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_ORBIT, MF_BYCOMMAND | MF_UNCHECKED);

	if (streq(m_operator, "HOpCameraPan"))
		CheckMenuItem(menu,ID_PAN, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_PAN, MF_BYCOMMAND | MF_UNCHECKED);

	if (streq(m_operator, "HOpCameraZoom"))
		CheckMenuItem(menu,ID_ZOOM_DIRECT, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_ZOOM_DIRECT, MF_BYCOMMAND | MF_UNCHECKED);

	if (streq(m_operator, "HOpCameraZoomBox"))
		CheckMenuItem(menu,ID_ZOOM_WINDOW, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_ZOOM_WINDOW, MF_BYCOMMAND | MF_UNCHECKED);

	if (streq(m_operator, "HOpObjectAnnotate"))
		CheckMenuItem(menu,ID_ANNOTATE, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_ANNOTATE, MF_BYCOMMAND | MF_UNCHECKED);

	if (streq(m_operator, "HOpMarkupPostIt"))
		CheckMenuItem(menu,ID_ADDNOTE, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_ADDNOTE, MF_BYCOMMAND | MF_UNCHECKED);

	if (streq(m_operator, "HOpMarkupFreehand"))
		CheckMenuItem(menu,ID_TOOLS_REDLINE, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_TOOLS_REDLINE, MF_BYCOMMAND | MF_UNCHECKED);
  
	
	if (m_bUseAntialiasing)
		CheckMenuItem(menu,ID_ANTIALIASING, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_ANTIALIASING, MF_BYCOMMAND | MF_UNCHECKED);

	
	if (m_pView->GetSmoothTransition())
		CheckMenuItem(menu,ID_TOOLS_SMOOTHTRANSITION, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_TOOLS_SMOOTHTRANSITION, MF_BYCOMMAND | MF_UNCHECKED);
	
	if (m_pView->GetRenderMode () == HRenderGouraud)
		CheckMenuItem(menu,ID_SMOOTH_SHADED, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_SMOOTH_SHADED, MF_BYCOMMAND | MF_UNCHECKED);


	if (m_pView->GetRenderMode () == HRenderFlat)
		CheckMenuItem(menu,ID_FLAT_SHADED, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_FLAT_SHADED, MF_BYCOMMAND | MF_UNCHECKED);


	if (m_pView->GetRenderMode () == HRenderWireframe)
		CheckMenuItem(menu,ID_WIREFRAME, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_WIREFRAME, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_pView->GetRenderMode () == HRenderHiddenLine || m_pView->GetRenderMode () == HRenderHiddenLineHOOPS ||
		m_pView->GetRenderMode () == HRenderHiddenLineFast)
		CheckMenuItem(menu,ID_HIDDEN_LINE, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_HIDDEN_LINE, MF_BYCOMMAND | MF_UNCHECKED);
 
	if (m_pView->GetShadowMode()!=HShadowNone)
 		CheckMenuItem(menu,ID_SHADOW_SMOOTH, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(menu,ID_SHADOW_SMOOTH, MF_BYCOMMAND | MF_UNCHECKED);
 
	if (m_text)
        CheckMenuItem(menu,ID_TOOLS_VISIBILITY_TEXT, MF_BYCOMMAND | MF_CHECKED);  
    else
        CheckMenuItem(menu,ID_TOOLS_VISIBILITY_TEXT, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_lines)
		CheckMenuItem(menu,ID_TOOLS_VISIBILITY_LINES, MF_BYCOMMAND | MF_CHECKED);  
    else
        CheckMenuItem(menu,ID_TOOLS_VISIBILITY_LINES, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_faces)
		CheckMenuItem(menu,ID_TOOLS_VISIBILITY_FACES, MF_BYCOMMAND | MF_CHECKED);  
    else
        CheckMenuItem(menu,ID_TOOLS_VISIBILITY_FACES, MF_BYCOMMAND | MF_UNCHECKED);


	blockit = true;

	set_menu_active(true); 
	TrackPopupMenu(menu,TPM_LEFTALIGN,rect.left,rect.top,0,m_hWnd,0); 
	set_menu_active(false);

	}
	else
		DefWindowProc(uMsg, wParam, lParam);

	ReleaseMutex(hMutex);

 	return 0;
}
 

/*! 
	frees the blocking of the constant framerate detail increment

*/
LRESULT CHoops3dStreamCtrl::OnExitMenuLoop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	blockit = false;
	return 0;
}


/*! Maps the MFC button and Shift/Control state to abstracted HOOPS/MVO values */
unsigned long CHoops3dStreamCtrl::MapFlags( unsigned long state )
{
	unsigned long flags=0;

	// map the qt events state to MVO
	if(state & MK_LBUTTON) flags|=MVO_LBUTTON;
	if(state & MK_RBUTTON) flags|=MVO_RBUTTON;
	if(state & MK_MBUTTON) flags|=MVO_MBUTTON;
	if(state & MK_SHIFT) flags|=MVO_SHIFT;
	if(state & MK_CONTROL) flags|=MVO_CONTROL;

	return flags;
}

/*!
	Property:
	Returns current m_bFlushOnLoad
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_FlushOnLoad(BOOL *pVal)
{
	*pVal = BOOL(m_bFlushOnLoad);
	return S_OK;
}


/*!
	Property:
	Sets m_bFlushOnLoad
*/ 
STDMETHODIMP CHoops3dStreamCtrl::put_FlushOnLoad(BOOL newVal)
{
	m_bFlushOnLoad = BOOL2bool(newVal);
	return S_OK;
}


/*!
	Property:
	Returns current filename
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_Filename(BSTR *pVal)
{
 	*pVal = CComBSTR(m_Filename).Copy();
 
  	return S_OK;
}


/*!
	Property:
	Sets current filename
	Initiates file streaming unless the file is local, then put_LocalFilename is invoked.
*/ 
STDMETHODIMP CHoops3dStreamCtrl::put_Filename(BSTR newVal)
{
	if (newVal)
	{
		BhvRewind();
		wchar_t waddress[4096];

		m_bFilenameChanged = true;
		SysReAllocString(&m_Filename, newVal);
		_tcscpy(waddress, m_Filename);
		if (!m_bFileOpenActive)
			FullyQualifyUnicodeUrl (waddress);
		SysReAllocStringLen(&m_Filename,0,_tcslen(waddress));
		_tcscpy(m_Filename,waddress);
		SetDirty(true);

		if (m_pView){
			if(m_bFlushOnLoad){
				m_pView->FlushProgressBar();
				m_pView->Flush();
				m_pView->GetModel()->Flush();
			}

			if(!m_pView->SceneDetached())
				SendOnDataChange();

			/* If we're opening a local file, don't bother downloading it first. */
			if(_tcsstr(m_Filename, _T("file://")) || m_bFileOpenActive){
				put_LocalFilename(newVal);
			} else {
				StartDownload();
			}
		}

	}

	return S_OK;
}

/*!
	Property:
	Sets current filename
	Load the file with out streaming (only if file is on local disk)
*/ 
STDMETHODIMP CHoops3dStreamCtrl::put_LocalFilename(BSTR newVal)
{
	if (newVal)
	{
		BhvRewind();

 		SysReAllocString(&m_Filename, newVal);
		wcscpy(m_Filename, newVal);

		m_bFilenameChanged = true;
		SetDirty(true);

		TCHAR error_msg[256] = {_T("")};
		TCHAR error_fmt[] = {_T("An error occured reading %s\nThe error code was %s.")};
		m_pView->SetHasCamera(false);
		HFileInputResult result = m_pView->GetModel()->Read(reinterpret_cast<const unsigned short *>(newVal));
		switch(result){
			case InputOK:
				{
				HC_Open_Segment_By_Key(m_pView->GetModelKey());		

				HC_POINTER_SIZED_INT    value = 0;

				if (HC_Show_Existence("user value"))
					HC_Show_User_Value(&value);

				HC_Close_Segment();

				if (value == 1)
					m_pView->GetModel()->SetBRepGeometry(true);
				else if (value == 2)
					m_pView->GetModel()->SetFEAGeometry(true);
				else if (value == 3)
					m_pView->GetModel()->SetVectorGeometry(true);

				if (!m_pView->GetHasCamera())
					m_pView->FitWorld();
				
				m_pView->GetModel()->CleanIncludes();
				m_pView->GetModel()->SetStaticModel(m_bStaticModel);
 				if (m_bSegmentDL)
					m_pView->SetDisplayListType(DisplayListSegment);
				SetFramerateMode(true);	
				m_pView->Update();
				}break;
			case InputVersionMismatch:
				wsprintf(error_msg, error_fmt, m_Filename, _T("InputVersionMismatch"));
				break;
			case InputFail:
				wsprintf(error_msg, error_fmt, m_Filename, _T("InputFail"));
				break;
			case InputNotHandled:
				wsprintf(error_msg, error_fmt, m_Filename, _T("InputNotHandled"));
				break;
			case InputBadFileName:
				wsprintf(error_msg, error_fmt, m_Filename, _T("InputBadFileName"));
				break;
			case InputBadOptions:
				wsprintf(error_msg, error_fmt, m_Filename, _T("InputBadOptions"));
				break;
			default:
				wsprintf(error_msg, error_fmt, m_Filename, _T("Unknown error"));
				break;
		}

		if(result != InputOK){
			::MessageBox(NULL, error_msg, _T("ERROR!"), MB_OK);
		}
	}

	return S_OK;
}

/*!
	Start Model Download
*/ 
void CHoops3dStreamCtrl::StartDownload()
{
	Fire_OnBeginLoad();
	
	if (m_pModel && m_pView && !m_pView->SceneDetached())
	{

		if (m_pView->GetShadowMode() == HShadowSoft)
			m_pView->SetShadowMode(HShadowNone);
		if (!m_bJustCreated)
		{
			Set2dModel(false);
			SetNoOrbit(false);
		}
		else
		{
			Set2dModel(m_bIs2dModel);
			SetNoOrbit(m_bNoOrbit);
		}

		m_bFilenameChanged = false;
		m_pDataLoader->Init(m_pView);

		if (m_pDataLoader->StartDownload(m_Filename))
		{	
			SetTimer(LOAD_TIMER,750);
			CBindStatusCallback2<CHoops3dStreamCtrl>::Download ( this, &CHoops3dStreamCtrl::OnData, m_Filename, 0, FALSE );
		}
	}
}


/*!	
	New Data Callback
*/ 
void CHoops3dStreamCtrl::OnData (CBindStatusCallback<CHoops3dStreamCtrl>* pbsc, BYTE* pBytes, DWORD dwSize)
{
	if (!m_pDataLoader->OnData(pBytes, dwSize))
	{	
			pbsc->m_spBinding->Abort();
	}
}

/*! 
	Switch to Camera Orbit Operator 
*/
LRESULT CHoops3dStreamCtrl::OnOrbit(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	LocalSetOperator(new HOpCameraManipulate(m_pView));
	return 0;
}

/*! 
	Show the file open dialog 
*/
LRESULT CHoops3dStreamCtrl::OnFileOpen(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	ShowFileOpenDialog();
	return 0;
}

/*! 
	Switch to Camera Zoom Operator 
*/
LRESULT CHoops3dStreamCtrl::OnZoom(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	LocalSetOperator(new HOpCameraZoom(m_pView));

	return 0;

}

/*! 
	Switch to Camera Pan Operator 
*/
LRESULT CHoops3dStreamCtrl::OnPan(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{

	
	LocalSetOperator(new HOpCameraPan(m_pView));
	return 0;

}

/*! 
	Switch to Camera Zoom Operator
*/
LRESULT CHoops3dStreamCtrl::OnZoomWindow(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	LocalSetOperator(new HOpCameraZoomBox(m_pView));
 	return 0;
}



void CHoops3dStreamCtrl::LocalSetOperator(HBaseOperator * NewOperator)
{
	HBaseOperator * op = m_pView->GetOperator();
	delete op;
	m_pView->SetOperator(NewOperator);
}


/*! 
	ResetScene
*/
LRESULT CHoops3dStreamCtrl::OnReset(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	WaitForSingleObject(hMutex,INFINITE);

 	m_pView->FitWorld();
	m_pView->Update();

	ReleaseMutex(hMutex);

	return 0;
}

/*! 
	Show Copyright Info
*/
LRESULT CHoops3dStreamCtrl::OnAboutBox(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{

	CAboutDlg myDlg;
	myDlg.DoModal();
 	return 0;
}

  	 
/*! 
	Change Window Background Color
*/
LRESULT CHoops3dStreamCtrl::OnWindowColor(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	
	ShowOptionsDialog();
 	return 0;
}



/*! 
	Switch to Annotation Operator
*/
LRESULT CHoops3dStreamCtrl::OnAnnotate(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	LocalSetOperator(new HOpObjectAnnotate(m_pView));
 	return 0;
}

/*! 
	Switch to Add Note Operator
*/
LRESULT CHoops3dStreamCtrl::OnAddNote(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
//	LocalSetOperator(new HOpAddNote(m_pView));
 	return 0;
}

/*! 
	Switch to Redline Operator
*/
LRESULT CHoops3dStreamCtrl::OnRedline(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	LocalSetOperator(new HOpMarkupFreehand(m_pView));
 	return 0;
}


/*! 
	Activate Smooth Transition
*/
LRESULT CHoops3dStreamCtrl::OnSmoothTransition(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	if (m_pView->GetSmoothTransition())
		m_pView->SetSmoothTransition(false);
	else
		m_pView->SetSmoothTransition(true);
	return 0;
}



/*! 
	Switch to Smooth Shaded View Mode
*/
LRESULT CHoops3dStreamCtrl::OnSmoothShaded(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	SetRenderModeGouraud();
	return 0;
}


/*! 
	Switch to Flat Shaded View Mode
*/
LRESULT CHoops3dStreamCtrl::OnFlatShaded(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	SetRenderModeFlat();
	return 0;
}



/*! 
	Switch to Wireframe View Mode
*/
LRESULT CHoops3dStreamCtrl::OnWireframe(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	SetRenderModeWireframe();
	return 0;
}



/*! 
	Switch to Hidden Line View Mode
*/
LRESULT CHoops3dStreamCtrl::OnHiddenLine(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{

	SetRenderModeHiddenLine();
	return 0;
}


/*! 
	Switch Shadows On/Off
*/
LRESULT CHoops3dStreamCtrl::OnShadowSmooth(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	if (m_pView->GetShadowMode() == HShadowNone)
		m_pView->SetShadowMode(HShadowSoft);
	else
		m_pView->SetShadowMode(HShadowNone);

	m_pView->Update();
	return 0;
}

/*! 
	Test visibility of spcific geometry type
	\param geom geomety type (ascii)

*/
bool CHoops3dStreamCtrl::IsVisible(char *geom)
{

	char res[255];
	HC_Open_Segment_By_Key(m_pView->GetSceneKey());
	HC_Show_One_Net_Visibility(geom, res);
	HC_Close_Segment();

	if (strcmp(res,"on") == 0)
		return true;
	else
		return false;
}

/*! 
	Retrieve view object
*/
HCtrlView* CHoops3dStreamCtrl::GetHoopsView()
{
	return m_pView;
}



 
static CHoops3dStreamCtrl *hctrl; 
 

static void event_checker(HIC_Rendition const *nr)
{
	
	MSG msg;
	if (hctrl->m_hWnd != 0)
	{		
		int state = GetAsyncKeyState(VK_LBUTTON);
		if (state & 32768)				
		{
			hctrl->GetHoopsView()->GetConstantFrameRateObject()->InitiateDelay();
 
			if (PeekMessage (&msg, hctrl->m_hWnd, WM_MOUSEMOVE, WM_MOUSEMOVE, PM_NOREMOVE))
			{
 				hctrl->GetHoopsView()->SetUpdateInterrupted(true);
			}
			else
				hctrl->GetHoopsView()->SetUpdateInterrupted(2);
  
			HIC_Abort_Update(nr);
 
		}		
		
		state = GetAsyncKeyState(VK_MBUTTON);
		if (state & 32768)				
		{
			HIC_Abort_Update(nr);
			hctrl->GetHoopsView()->SetUpdateInterrupted(true);
		}		
		
		if (PeekMessage (&msg, hctrl->m_hWnd, WM_MOUSEWHEEL, WM_MOUSEWHEEL, PM_NOREMOVE))
		{
			HIC_Abort_Update(nr);
			hctrl->GetHoopsView()->SetUpdateInterrupted(true);
		}
	}
		int state = GetAsyncKeyState(VK_RBUTTON);
		if (state & 32768)				
		{
			hctrl->GetHoopsView()->GetConstantFrameRateObject()->InitiateDelay();
 			hctrl->GetHoopsView()->SetUpdateInterrupted(2);
			HIC_Abort_Update(nr);
		}		
	
}


/*! 
	Timer for constant framerate detail increase and HNet processing
*/

LRESULT CHoops3dStreamCtrl::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	static bool running = false;
	if (!running)
	{
		running = true;
		WaitForSingleObject(hMutex,INFINITE);   
		
		
		if (wParam == TICK_TIMER)
		{
			float time;
			HC_Show_Time( &time );			
			HDB::GetHTManager()->Tick( time );
		}
		else if (wParam == LOAD_TIMER)
		{
			SetTimer(LOAD_TIMER,25);
			if (!m_pDataLoader->ProcessNextChunk())
			{
				KillTimer(LOAD_TIMER);
				Fire_OnEndLoad();
				Set2dModel(m_bIs2dModel);
				SetShadowMode(m_bShadowMode);
	
				if (!m_pView->GetHasCamera())
					m_pView->FitWorld();
				m_pView->FlushProgressBar();
				m_pView->Update();
				m_pView->GetModel()->GetBhvBehaviorManager()->SetContinuousPlay(m_bContinuousPlay);
				m_pView->GetModel()->SetStaticModel(m_bStaticModel);
				if (m_bSegmentDL)
					m_pView->SetDisplayListType(DisplayListSegment);
				SetFramerateMode(true);	

 
			}
			
		}
		if (wParam == FRAMERATE_TIMER)
		{
			
			//		    KillTimer(wParam);
			HConstantFrameRate *cframerate = m_pView->GetConstantFrameRateObject();
			if (cframerate->GetActive() && !blockit)
			{	
				
				hctrl = this;
				m_pView->SetEventCheckerCallback(event_checker);
				if (m_pView->GetIdleTime() > 0.3f  && !cframerate->GetActivityType() && 
					!m_pView->GetModel()->GetBhvBehaviorManager()->IsPlaying())
				{
					cframerate->IncreaseDetailTemp();
					SetTimer(FRAMERATE_TIMER,10);
				}
				else
					SetTimer(FRAMERATE_TIMER,500);
				
				cframerate->SetActivityType(NoActivity);
				
			}					
		}
		
		ReleaseMutex(hMutex);
		running = false;
	
	}
	
	return 0;
}

/*! 
	Convert BSTR to character
*/
void CHoops3dStreamCtrl::ConvertToChar(char *mbstr, const wchar_t *wcstr, size_t count)
{
	if (wcstr)
		wcstombs(mbstr, wcstr, count); 
	else
		strcpy(mbstr,"");
}

/*! 
	Convert character to BSTR
*/
void CHoops3dStreamCtrl::ConvertToBSTR(wchar_t *wcstr, const char *mbstr, size_t count)
{
	//wcstr = new wchar_t[sizeof(wchar_t) * count];
	if (mbstr && mbstr[0])
		mbstowcs(wcstr, mbstr, count); 
}

/*! 
	Handle OnKeyDown Message
*/



/*! 
	Handle OnKeyUp Message
*/
LRESULT CHoops3dStreamCtrl::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pView)
	{
		HEventInfo	event(m_pView);
		HBaseOperator *op = m_pView->GetCurrentOperator();

		if (op)
		{
						
			unsigned short ascii_key;
			BYTE keys[256];

			GetKeyboardState( keys );

			ToAscii((int) wParam, MapVirtualKey((int)wParam, 0), keys, &ascii_key, 0);
	
			//event.SetKey(HE_KeyUp, ascii_key, LOWORD(lParam), MapFlags(HIWORD(lParam)));
			event.SetKey(HE_KeyUp, ascii_key, LOWORD(lParam), 0);
			op->OnKeyUp(event);
		}
	}
	return 0;

}

/*!
	Property:
	Returns download status
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_DLinProgress(BOOL *pVal)
{
	if(m_pDataLoader)
		*pVal = !m_pDataLoader->GetDownloadComplete();
	else
		*pVal = true;
	return S_OK;
}

/*!
	Property:
	Returns size of already downloaded HSF data
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_DownloadDataReceived(long *pVal)
{
	if(m_pDataLoader)
 		*pVal = m_pDataLoader->GetDownloadDataReceived();
	else
		*pVal = 0;
	return S_OK;
}

/*!
	Property:
	Returns total size of HSF data
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_DownloadDataMax(long *pVal)
{
	if(m_pDataLoader)
 		*pVal = m_pDataLoader->GetDownloadDataTotalSize();
	else
		*pVal = 0;
	return S_OK;
}
 
			
/*!
	 Initiates abortion of download in progress
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::AbortDownload()
{
	m_pDataLoader->AbortDownload();
	return S_OK;
}


bool CHoops3dStreamCtrl::Print()
{ 

	PRINTDLG pd;
	ZeroMemory(&pd, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.hwndOwner   = 0;
	pd.hDevMode    = NULL;      // Don't forget to free or store hDevMode.
	pd.hDevNames   = NULL;      // Don't forget to free or store hDevNames.
	pd.Flags       = PD_RETURNDC;
	pd.nCopies     = 1;
	pd.nFromPage   = 0xFFFF; 
	pd.nToPage     = 0xFFFF; 
	pd.nMinPage    = 1; 
	pd.nMaxPage    = 0xFFFF; 
	
    if (!PrintDlg(&pd))
        return 0;
	//int err = CommDlgExtendedError();
    HDC hPDC = pd.hDC;	
    DOCINFO di;
    di.cbSize       = sizeof (DOCINFO);
    di.lpszDocName  = _T("Printout");
    di.lpszOutput   = NULL;
	
	StartDoc(hPDC, &di);
	StartPage(hPDC);
	
	//    if (m_bMetaPrint)
	//        PrintAsMetafile (hPDC);
	//    else
//	PrintNormal (hPDC, false);    

 	GDIExportInformation pinfo;

	pinfo.deviceContext = pd.hDC;
	pinfo.attribDC = pd.hDC;
	if (m_pView->GetRenderMode() == HRenderHiddenLineFast || m_pView->GetRenderMode() == HRenderHiddenLine)
	    pinfo.rasterOutput = false;
	else
	    pinfo.rasterOutput = true;

	pinfo.clipBoard= false;
	// only really used when it's a print preview
	pinfo.windowID = (void *)::GetDesktopWindow();

	HOutputHandlerOptions options;
	options.m_pExtendedData = (void *)&pinfo;

	HOutputHandler * handler = new HIOUtilityGDIOutput;

	// if none found quit
	if(!handler) 
		return 0;
	
	m_pView->FileOutput("", handler, &options);
	
	EndPage (hPDC);
    EndDoc (hPDC);
	
	
    //BOOL bStatus = DeleteDC (hPDC);
	return true;
}
  
/*!
	Printing
*/ 
LRESULT CHoops3dStreamCtrl::OnPrint(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{ 
	Print();
	return true;
}


/*!
	Copy to Clipboard
*/ 
LRESULT CHoops3dStreamCtrl::OnCopy(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	CopyToClipboard();
	return 0;
}



/*!
	Property:
	Switch to Orbit Operator
 
*/ 
/*!
	Property:
	Retrieve current operator name
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_CurrentOperator(BSTR *pVal)
{
 	if (m_pView)
	{
 	HBaseOperator * op = m_pView->GetCurrentOperator();
	const char *oname = op->GetName();

  
 	SysReAllocStringLen(pVal,0,strlen(oname));
	mbstowcs(*pVal,oname,strlen(oname));
	}
	else
		*pVal = SysAllocString(L"");

	return S_OK;
}


/*!
	Property:
	Reset Scene
  
*/ 
STDMETHODIMP CHoops3dStreamCtrl::FitWorld()
{
 	m_pView->FitWorld();
	m_pView->Update();

	return S_OK;
}


/*!
	Handle OnDestroy Message cleanup
 
*/ 
LRESULT CHoops3dStreamCtrl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
 
	// get rid of the client dialog if it exists

	if (m_pView)
	{
	    HPoint					window_color;
	    
		HC_Open_Segment_By_Key(m_pView->GetViewKey());
		HC_UnSet_Color();
		HC_Close_Segment();
	    m_pView->DetachScene();
	}

	return 0;
}





/*!
	Property:
	Setup Camera by passing position/target/up-vector
  
*/ 
STDMETHODIMP CHoops3dStreamCtrl::SetCamera(float px, float py, float pz, float tx, float ty, float tz, float ux, float uy, float uz, float width, float height)
{
 	HPoint pos, tar, up;
 	pos.Set(px,py,pz);
	tar.Set(tx,ty,tz);
	up.Set(ux,uy,uz);
 
	m_pView->DoSmoothTransition(true);
	HC_Open_Segment_By_Key(m_pView->GetSceneKey());
		HC_Set_Camera (&pos, &tar, &up, width, height, "perspective");
	HC_Close_Segment();

   	m_pView->DoSmoothTransition(false);
 	m_pView->CameraPositionChanged( true, m_pView->GetSmoothTransition());
	m_pView->Update();

	return S_OK;
}


/*!
	Property:
	Retrieve camera parameters
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_CameraParameters(BSTR *pVal)
{
 	char sname[4096];
	HPoint position, target, up;
	float width, height;
	char projection[256];

	HC_Open_Segment_By_Key(m_pView->GetSceneKey());
 				HC_Show_Net_Camera(&position, &target, &up, 
					&width, &height, projection);	
	HC_Close_Segment();

	sprintf(sname, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
				position.x, position.y, position.z, 
				target.x, target.y, target.z,
				up.x, up.y, up.z, 
				width, height);
  
	if (!pVal)
		*pVal = SysAllocString(L"empty");

	SysReAllocStringLen(pVal,0,strlen(sname));
	mbstowcs(*pVal,sname,strlen(sname));

	return S_OK;
}

/*!
	Save persistent data
 
*/  
HRESULT CHoops3dStreamCtrl::IPersistStreamInit_Load(LPSTREAM pStm, const ATL_PROPMAP_ENTRY* pMap)
{
    if (NULL == pStm) return E_POINTER;
HRESULT hr;
    // Load the properties described in the PROP_MAP
//	HRESULT hr = IPersistStreamInitImpl<CHoops3dStreamCtrl>::IPersistStreamInit_Load(pStm, pMap);
//    if (FAILED (hr)) return hr;

  		char filename[4096];    
        int len;
        ULONG cbRead;

 		hr = pStm->Read(&m_bEmbed, sizeof(m_bEmbed), &cbRead);
		if (m_bEmbed)
			ReadFileFromArchive(pStm);
  
		bool cam = false;
		
		hr = pStm->Read(&cam, sizeof(cam), &cbRead);
		if (cam)
		{
			
			hr = pStm->Read(&m_camPosition, sizeof(m_camPosition), &cbRead);
			hr = pStm->Read(&m_camTarget, sizeof(m_camTarget), &cbRead);
			hr = pStm->Read(&m_camUp, sizeof(m_camUp), &cbRead);
			hr = pStm->Read(&m_camWidth, sizeof(float), &cbRead);
			hr = pStm->Read(&m_camHeight, sizeof(float), &cbRead);
			int plen;
			hr = pStm->Read(&plen, sizeof(plen), &cbRead);
			hr = pStm->Read(&m_camProjection, plen+1, &cbRead);
			m_bCameraRestored = true;
		}
		hr = pStm->Read(&len, sizeof(len), &cbRead);
		hr = pStm->Read(filename, len, &cbRead);
        hr = pStm->Read(&m_sizeExtent.cx, sizeof(m_sizeExtent.cx), &cbRead);
        hr = pStm->Read(&m_sizeExtent.cy, sizeof(m_sizeExtent.cy), &cbRead);

         if (FAILED (hr)) {
            hr = E_UNEXPECTED;
         
        }

		if (SUCCEEDED(hr)){
			if (len > 0 && !m_bEmbed)
 			put_Filename(CComBSTR(filename));

			m_bRequiresSave = FALSE;
		}
    return hr;
}

/*!
	Restore persistent data
*/ 
HRESULT CHoops3dStreamCtrl::IPersistStreamInit_Save(LPSTREAM pStm, BOOL fClearDirty, const ATL_PROPMAP_ENTRY* pMap)
{
	if (NULL == pStm) return E_POINTER;
 
   HRESULT hr;
		int len;
  		char filename[4096];

		if (m_Filename)
		{
			ConvertToChar(filename,m_Filename,4096);
			len = strlen(filename)+1;
		}
		else
			len = 0;

        // Write it to the stream
        ULONG cbWritten;
 		hr = pStm->Write(&m_bEmbed, sizeof(m_bEmbed), &cbWritten);
		if (m_bEmbed)
			WriteFileToArchive(pStm);

		bool cam = false;
		if (m_pView)
			cam = true;
		
		hr = pStm->Write(&cam, sizeof(cam), &cbWritten);
		if (m_pView)
		{
			HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Show_Net_Camera(&m_camPosition, &m_camTarget, &m_camUp, 
				&m_camWidth, &m_camHeight, m_camProjection);	
			HC_Close_Segment();
			hr = pStm->Write(&m_camPosition, sizeof(m_camPosition), &cbWritten);
			hr = pStm->Write(&m_camTarget, sizeof(m_camTarget), &cbWritten);
			hr = pStm->Write(&m_camUp, sizeof(m_camUp), &cbWritten);
			hr = pStm->Write(&m_camWidth, sizeof(float), &cbWritten);
			hr = pStm->Write(&m_camHeight, sizeof(float), &cbWritten);
			int plen = strlen(m_camProjection);
			hr = pStm->Write(&plen, sizeof(plen), &cbWritten);
			hr = pStm->Write(&m_camProjection, plen+1, &cbWritten);
		}
        hr = pStm->Write(&len, sizeof(len), &cbWritten);
        hr = pStm->Write(filename, len, &cbWritten);
        hr = pStm->Write(&m_sizeExtent.cx, sizeof(m_sizeExtent.cx), &cbWritten);
        hr = pStm->Write(&m_sizeExtent.cx, sizeof(m_sizeExtent.cy), &cbWritten);

  
        if (FAILED (hr)) {
            hr = E_UNEXPECTED;
          
        }
	
    return hr;
}



/*!
	Write persistent data to archive
  
*/ 
void CHoops3dStreamCtrl::WriteFileToArchive (LPSTREAM pStm)
{
    // Get the system temp directory
    TCHAR path [MAX_PATH];
    TCHAR filename [MAX_PATH];

    GetTempPath(MAX_PATH, path);
    GetTempFileName(path, _T(""), 0, filename);
    _tcsncpy(filename + (_tcsclen(filename) - 3), _T("hsf"), 3);   
//    m_pModel->Write(filename, NULL);

	HStreamFileToolkit * tk = new HStreamFileToolkit();
	tk->Restart();
	HC_Open_Segment_By_Key(m_pModel->GetModelKey());    
  	tk->SetWriteFlags(TK_Suppress_LOD);
	//TK_Status status = HTK_Write_Stream_File (UtC(filename,ctemp), tk); 
	HTK_Write_Stream_File (UtC(filename,ctemp), tk); 
	HC_Close_Segment();

	delete tk;
    
    int     nBufferLength;
    char *  pBuffer = 0;

         // Read the metafile into some global memory
		FILE *fhandle = fopen(UtC(filename,ctemp),"rb");
		fseek(fhandle,0,SEEK_END);
        nBufferLength = ftell(fhandle);
		fseek(fhandle,0,SEEK_SET);
        pBuffer = (char *) new char [nBufferLength];
		fread(pBuffer,1, nBufferLength,fhandle);
		fclose (fhandle);

        ULONG cbWritten;
        HRESULT hr = pStm->Write(&nBufferLength, sizeof(nBufferLength), &cbWritten);
        hr = pStm->Write(pBuffer, nBufferLength, &cbWritten);
     
	  delete [] pBuffer;
   	ReleaseMutex(hMutex);

}


/*!
	Property:
	read persistent data from archive
 
*/ 
void CHoops3dStreamCtrl::ReadFileFromArchive (LPSTREAM pStm)
{   
	OutputDebugString(_T("CHoopsControl : ReadFileFromArchive\n"));

	int     nBufferLength;
	char *  pBuffer;
	ULONG cbRead;


	HRESULT hr = pStm->Read(&nBufferLength, sizeof(nBufferLength), &cbRead);

	if (nBufferLength > 0) {
		pBuffer = (char *) new char [nBufferLength];
		hr = pStm->Read(pBuffer, nBufferLength, &cbRead);
		// Write it out to a temporary file
		TCHAR path [MAX_PATH];
		TCHAR filename [MAX_PATH];

		GetTempPath(MAX_PATH, path);
		GetTempFileName(path, _T(""), 0, filename);

		// Replace the extension with .hmf
		_tcsncpy(filename + (_tcsclen(filename) - 3), _T("hsf"), 3);

		FILE *fhandle = fopen(UtC(filename,ctemp),"wb");
		fseek(fhandle,0,SEEK_SET);
		fwrite(pBuffer,1,nBufferLength, fhandle);
		fclose(fhandle);    
		delete [] pBuffer;
		
		InitModel();
		// read the file into the Model Object
		m_pModel->Read(reinterpret_cast<const char *>(filename));
	}
}


bool CHoops3dStreamCtrl::SaveFile( LPCTSTR csFilePathName )
{
	int width = 500, height = 500;
	int dpi = 75;

	HC_Control_Update_By_Key (m_pView->GetViewKey(), "redraw everything");
	m_pView->Update();

	char extension[MVO_BUFFER_SIZE];
	HUtility::FindFileNameExtension(H_ASCII_TEXT(csFilePathName), extension);

	if (streq(extension, "htm") || streq(extension, "html") )
	{
		width = 70;
		height = 70;
	}

	if (streq(extension,"emf"))
	{
		// ...TODO...
	}
#ifdef HOOPS_LEAD_TOOLS
	else if ( streq(extension, "jpeg") || 
		streq(extension, "jpg") || 
		streq(extension, "bmp") || 
		streq(extension, "tif") || 
		streq(extension, "tiff") )
#else
	else if ( streq(extension, "tif") ) 
#endif
	{
		// Image output uses physical size, not pixel size
		width  = (int) (width/(float)dpi*2.54f);
		height = (int) (height/(float)dpi*2.54f);
	}
	else if (streq(extension, "cgm") || streq(extension, "ps") || streq(extension, "hp"))
	{
		// if this is hard-copy output, we want the size to be adjusted from pixels to cm
		// assume 75 dpi resolution
		width  = (int) (width/(float)dpi*2.54f);
		height = (int) (height/(float)dpi*2.54f);
	}


	if(_tcscmp(csFilePathName, _T("")))
	{
		bool result = true;
		if (streq(extension, "hsf")) // Write HOOPS Stream File
		{
			HC_Open_Segment_By_Key(m_pView->GetModelKey());
			HStreamFileToolkit *mytool = new HStreamFileToolkit;

			// save the camera position
			//mytool->SetPrewalkHandler(new TK_My_Initial_View(this));

			HBhvUtility::SetupAnimationWriteFromHSF(mytool, m_pView->GetModel());

			int sflags = 0;

			// This is a paradox here, the flags passed as argument to Write_Stream function make
			// no sense if we use our own toolkit. These flags need to be set on the toolkit itself
			mytool->SetWriteFlags(sflags);


			if (HTK_Write_Stream_File(H_ASCII_TEXT(csFilePathName),mytool) == TK_Error)
				result = false;

			delete mytool;
			HC_Close_Segment();
		}
		else if (streq(extension, "bhv"))
		{
			HBhvBehaviorManager *pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
			pBehaviorManager->WriteToFile(H_ASCII_TEXT(csFilePathName));
		}
		else
		{
			HOutputHandlerOptions options;

			options.ImageDpi(dpi);
			options.WindowWidth(width);
			options.WindowHeight(height);
			options.PaperWidth(width);
			options.PaperHeight(height);

			m_pModel->WriteWithOptions(H_ASCII_TEXT(csFilePathName), m_pView, &options);
		}

	}
	return true;
}



/*!
	Property:
	Retrieve embed property
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::get_Embed(BOOL *pVal)
{
 	*pVal = m_bEmbed;
	return S_OK;
}

/*!
	Property:
	set camera parameters
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::put_Embed(BOOL newVal)
{
 	m_bEmbed = (newVal != 0);
	SetDirty(true);
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::put_SegmentDL(BOOL newVal)
{
 	m_bSegmentDL = (newVal != 0);
	SetDirty(true);
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::get_SegmentDL(BOOL *pVal)
{
    *pVal = m_bSegmentDL;
 	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::put_StaticModel(BOOL newVal)
{
 	m_bStaticModel = (newVal != 0);
	SetDirty(true);
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_StaticModel(BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::put_AntialiasingLevel(int newVal)
{
 	m_AntialiasingLevel = newVal;
	SetDirty(true);
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_AntialiasingLevel(int *newVal)
{
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::get_NoOrbit(BOOL *pVal)
{
 	*pVal = m_bNoOrbit;
	return S_OK;
}

/*!
	Property:
	set camera parameters
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::put_NoOrbit(BOOL newVal)
{
 	SetNoOrbit((newVal != 0));
	SetDirty(true);
	return S_OK;
}

 


/*!
	Property:
	Restore camera to default values
 
*/ 
bool CHoops3dStreamCtrl::RestoreCamera()
{
	if (m_bCameraRestored && m_pView)
	{		
		m_bCameraRestored = false;
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
		HC_Set_Camera(&m_camPosition, &m_camTarget, &m_camUp, m_camWidth, m_camHeight, m_camProjection);
		HC_Close_Segment();
		m_pView->CameraPositionChanged( true, m_pView->GetSmoothTransition());
		m_pView->Update();
		m_pDataLoader->SetRestoreCamera(false);
 		return true;
	}
	else
		return false;
}


#include "wininet.h"
#include "oleidl.h"
//
// Helper Functions
// 

bool CHoops3dStreamCtrl::BreakUrl (	const char *   urlname,
                                 char *   scheme,
                                 char *   hostname,
                                 char *   path, bool   &bIsLocalFile)
{
	OutputDebugString(_T("CHoopsDataLoader : BreakUrl\n"));

    URL_COMPONENTS  urlComp;
	char port[4096];

    urlComp.dwStructSize        = sizeof(URL_COMPONENTS);
    urlComp.lpszScheme          = NULL;
    urlComp.dwSchemeLength      = 1;
    urlComp.lpszHostName        = NULL;
    urlComp.dwHostNameLength    = 1;
    urlComp.lpszUserName        = NULL;
    urlComp.dwUserNameLength    = 0;
    urlComp.lpszPassword        = NULL;
    urlComp.dwPasswordLength    = 0;
    urlComp.lpszUrlPath         = NULL;
    urlComp.dwUrlPathLength     = 1;
    urlComp.lpszExtraInfo       = NULL;
    urlComp.dwExtraInfoLength   = 0;
    urlComp.nScheme             = INTERNET_SCHEME_DEFAULT;
    urlComp.nPort               = 0;

    BOOL    bSuccess;
    bSuccess = InternetCrackUrl (CtU(urlname, stemp), 0, 0, &urlComp);
   
   
    if (bSuccess) {
        if (urlComp.nScheme == INTERNET_SCHEME_PARTIAL)
            return FALSE;
        else if (urlComp.nScheme == INTERNET_SCHEME_UNKNOWN) {
            strcpy(hostname, "");
 			strcpy(scheme,UtC2(urlComp.lpszScheme, ctemp, urlComp.dwSchemeLength));
 			strcpy(path, urlname);
             bIsLocalFile = true;
        }
        else {
			char portToken[64];

			if (urlComp.nPort > 0)
				sprintf(portToken, ":%d", urlComp.nPort);
			else
				portToken[0] = 0;
  
			strcpy(port, portToken);
 		
  			strcpy(scheme, UtC2(urlComp.lpszScheme, ctemp, urlComp.dwSchemeLength));	
			
			
			scheme[urlComp.dwSchemeLength] = 0;
			strcat(scheme, "://");	
		
			if (urlComp.dwHostNameLength && urlComp.lpszHostName)
			{
 				strcpy(hostname, UtC2(urlComp.lpszHostName, ctemp, urlComp.dwHostNameLength));
				hostname[urlComp.dwHostNameLength] = 0;
				strcat(hostname, port);	
			}
			else
				strcpy(hostname, "");

 			strcpy(path, UtC2(urlComp.lpszUrlPath, ctemp, urlComp.dwUrlPathLength));

            bIsLocalFile = (urlComp.nScheme == INTERNET_SCHEME_FILE);
        }
    }
    else {
        // must be a unknown internet scheme.
        // assume its a filename without any path info.
        strcpy(scheme,"");
        strcpy(hostname,"");
  		strcpy(path, urlname);
         bIsLocalFile = true;
    }

     return true;
}

bool CHoops3dStreamCtrl::BreakUnicodeUrl (	const wchar_t *   urlname,
                                 wchar_t *   scheme,
                                 wchar_t *   hostname,
                                 wchar_t *   path, bool   &bIsLocalFile)
{
	OutputDebugString(_T("CHoopsDataLoader : BreakUrl\n"));

    URL_COMPONENTS  urlComp;
	wchar_t port[4096];

    urlComp.dwStructSize        = sizeof(URL_COMPONENTS);
    urlComp.lpszScheme          = NULL;
    urlComp.dwSchemeLength      = 1;
    urlComp.lpszHostName        = NULL;
    urlComp.dwHostNameLength    = 1;
    urlComp.lpszUserName        = NULL;
    urlComp.dwUserNameLength    = 0;
    urlComp.lpszPassword        = NULL;
    urlComp.dwPasswordLength    = 0;
    urlComp.lpszUrlPath         = NULL;
    urlComp.dwUrlPathLength     = 1;
    urlComp.lpszExtraInfo       = NULL;
    urlComp.dwExtraInfoLength   = 0;
    urlComp.nScheme             = INTERNET_SCHEME_DEFAULT;
    urlComp.nPort               = 0;

    BOOL    bSuccess;
    bSuccess = InternetCrackUrlW (urlname, 0, 0, &urlComp);
   
   
    if (bSuccess) {
        if (urlComp.nScheme == INTERNET_SCHEME_PARTIAL)
            return FALSE;
        else if (urlComp.nScheme == INTERNET_SCHEME_UNKNOWN) {
            wcscpy(hostname, L"");
			wcscpy(scheme,urlComp.lpszScheme);
 			wcscpy(path, urlname);
             bIsLocalFile = true;
        }
        else {
			wchar_t portToken[64];

			if (urlComp.nPort > 0)
				swprintf(portToken, L":%d", urlComp.nPort);
			else
				portToken[0] = 0;
  
			wcscpy(port, portToken);
 		
  			wcscpy(scheme, urlComp.lpszScheme);	
			
			
			scheme[urlComp.dwSchemeLength] = 0;
			wcscat(scheme, L"://");	
		
			if (urlComp.dwHostNameLength && urlComp.lpszHostName)
			{
 				wcscpy(hostname, urlComp.lpszHostName);
				hostname[urlComp.dwHostNameLength] = 0;
				wcscat(hostname, port);	
			}
			else
				wcscpy(hostname, L"");

 			wcscpy(path, urlComp.lpszUrlPath);

            bIsLocalFile = (urlComp.nScheme == INTERNET_SCHEME_FILE);
        }
    }
    else {
        // must be a unknown internet scheme.
        // assume its a filename without any path info.
        wcscpy(scheme,L"");
        wcscpy(hostname,L"");
  		wcscpy(path, urlname);
         bIsLocalFile = true;
    }

     return true;
}



bool CHoops3dStreamCtrl::ContainerIsIE (void)
{
 
    bool    bResult = true;
    HRESULT hr      = S_FALSE;

     
    IServiceProvider *  pServiceProvider = NULL;   
    IOleClientSite *    pClientSite;
    GetClientSite(&pClientSite);
    
    if (!pClientSite)
        return false;
    
    if (FAILED (hr = pClientSite->QueryInterface (IID_IServiceProvider, (void**) &pServiceProvider))) {
        pClientSite->Release ();
        return false;
    }

    // Now query the IOleContainer interface for the IWebBrowserApp interface
    if (FAILED (hr = pServiceProvider->QueryService (IID_IWebBrowserApp, IID_IWebBrowserApp, (void **)&m_pInternetExplorer))) {
        bResult = false;
    }

    //if (pClientSite)
    //    pClientSite->Release ();

    if (pServiceProvider)
        pServiceProvider->Release ();
    
    return bResult;
}




bool CHoops3dStreamCtrl::FullyQualifyUrl (char *urlname)
{
  
    // The urlname can be
    // 1. fully qualified url: http://www.techsoft.com/gasket.hmf               - no need to change
    // 2. A filename in the same location as the html page: gasket.hmf          - get location of current html
    // 3. A relative path from the location of the html page: ../hmf/gasket.hmf - get location of current html and combine
    // 4. A virtual path from the root of the web server: /hmf/gasket.hmf       - get hostname and combine to form url

    // m_bIsLocal       true            false
    // m_urlname        filename        urlname
    //                  no download     download required
    // 




    // fully qualified urlname:
    // container: IE
    //      * http://www.techsoft.com/gasket.hmf
    //      * gasket.hmf
    //      * ../hmf/gasket.hmf
    //      * /hmf/gasket.hmf
    //
    // container: Link in Document
    //      * http://www.techsoft.com/gasket.hmf
    //      * gasket.hmf
    //      * ../hmf/gasket.hmf
    //      * /hmf/gasket.hmf
    //      * ftp://ftp.techsoft.com/gasket.hmf


    // if container is web browser
    //    
    char      scheme[4096];
    char      hostname[4096];
    char      path[4096];
    bool        bIsLocalFile;
   

    if (!BreakUrl (urlname, scheme, hostname, path, bIsLocalFile))
        return false;

    if (ContainerIsIE()) {
        if (strcmp(hostname,"") == 0) {
            // file must be in reference to the currently loaded page
            BSTR    bstrUrl = NULL;
            char currentPageUrl[4096];
            char currentScheme[4096];
            char currentHost[4096];
            char currentPath[4096];
            bool    bCurrentIsLocal;

            m_pInternetExplorer->get_LocationURL (&bstrUrl);
 			ConvertToChar(currentPageUrl,bstrUrl,4096);

            // Search for "///" and remove one of the '/'
            char * nPos = strstr(currentPageUrl, "///");
             if (nPos >0)
			 {
				 int end = strlen(currentPageUrl);
				 for (int i=0;i<(end - (nPos-currentPageUrl));i++)
					 nPos[i] = nPos[i+1];
			 }
 
            if (!BreakUrl (currentPageUrl, currentScheme, currentHost, currentPath, bCurrentIsLocal))
                return false;

            if (strstr(urlname, "/") || strstr(urlname, "\\"))
			{
 				strcat(currentScheme, currentHost);
				strcat(currentScheme, urlname);
				strcpy(urlname, currentScheme);

			}
            else {
                 // urlname given is relative to the current page.
                // Remove the currently pointed to file from the url and
                // replace it with the urlname
                char * nPos = 0;
				char *temp =currentPath;
 				do {	
					nPos = temp;
					temp = strstr(temp,"/");
					if (temp)
						temp++;
				}while (temp);


                if (nPos == currentPath)
				{
					nPos = 0;
					temp =currentPath;
					do {	
						nPos = temp;
						temp = strstr(temp,"\\");
						if (temp)
							temp++;
					}while (temp);
					
 					if (nPos == currentPath)
					{
						char urlname2[4096];
						strcpy(urlname2, urlname);
						strcpy(urlname, currentScheme);
						strcat(urlname, currentHost);
						strcat(urlname, urlname);
 						goto endbreak;
					}
				}
//				nPos++;
				nPos[0] = 0;
				strcat(currentPath, urlname);
				strcpy(urlname, currentScheme);
				strcat(urlname, currentHost);
				strcat(urlname, currentPath);
endbreak:		;   
			
            }
        }
    }

//    ResolveRelativePath (urlname);


	// Decode the url
    DWORD bufferlength = 1024;
    TCHAR szBuffer[1024];
    InternetCanonicalizeUrl((LPCTSTR)urlname, szBuffer, &bufferlength, ICU_DECODE | ICU_NO_ENCODE);
    UtC(szBuffer, urlname);    

    return true;
}
 
bool CHoops3dStreamCtrl::FullyQualifyUnicodeUrl (wchar_t *urlname)
{
  
    // The urlname can be
    // 1. fully qualified url: http://www.techsoft.com/gasket.hmf               - no need to change
    // 2. A filename in the same location as the html page: gasket.hmf          - get location of current html
    // 3. A relative path from the location of the html page: ../hmf/gasket.hmf - get location of current html and combine
    // 4. A virtual path from the root of the web server: /hmf/gasket.hmf       - get hostname and combine to form url

    // m_bIsLocal       true            false
    // m_urlname        filename        urlname
    //                  no download     download required
    // 




    // fully qualified urlname:
    // container: IE
    //      * http://www.techsoft.com/gasket.hmf
    //      * gasket.hmf
    //      * ../hmf/gasket.hmf
    //      * /hmf/gasket.hmf
    //
    // container: Link in Document
    //      * http://www.techsoft.com/gasket.hmf
    //      * gasket.hmf
    //      * ../hmf/gasket.hmf
    //      * /hmf/gasket.hmf
    //      * ftp://ftp.techsoft.com/gasket.hmf


    // if container is web browser
    //    
    wchar_t      scheme[4096];
    wchar_t      hostname[4096];
    wchar_t      path[4096];
    bool        bIsLocalFile;
   

    if (!BreakUnicodeUrl (urlname, scheme, hostname, path, bIsLocalFile))
        return false;

    if (ContainerIsIE()) {
        if (wcscmp(hostname,L"") == 0) {
            // file must be in reference to the currently loaded page
            BSTR    bstrUrl = NULL;
            wchar_t currentPageUrl[4096];
            wchar_t currentScheme[4096];
            wchar_t currentHost[4096];
            wchar_t currentPath[4096];
            bool    bCurrentIsLocal;

            m_pInternetExplorer->get_LocationURL (&bstrUrl);
// 			ConvertToChar(currentPageUrl,bstrUrl,4096);
			wcscpy(currentPageUrl,bstrUrl);

            // Search for "///" and remove one of the '/'
            wchar_t * nPos = wcsstr(currentPageUrl, L"///");
             if (nPos >0)
			 {
				 int end = wcslen(currentPageUrl);
				 for (int i=0;i<(end - (nPos-currentPageUrl));i++)
					 nPos[i] = nPos[i+1];
			 }
 
            if (!BreakUnicodeUrl (currentPageUrl, currentScheme, currentHost, currentPath, bCurrentIsLocal))
                return false;

            if (wcsstr(urlname, L"/") || wcsstr(urlname, L"\\"))
			{
 				wcscat(currentScheme, currentHost);
				wcscat(currentScheme, urlname);
				wcscpy(urlname, currentScheme);

			}
            else {
                 // urlname given is relative to the current page.
                // Remove the currently pointed to file from the url and
                // replace it with the urlname
                wchar_t * nPos = 0;
				wchar_t *temp =currentPath;
 				do {	
					nPos = temp;
					temp = wcsstr(temp,L"/");
					if (temp)
						temp++;
				}while (temp);


                if (nPos == currentPath)
				{
					nPos = 0;
					temp =currentPath;
					do {	
						nPos = temp;
						temp = wcsstr(temp,L"\\");
						if (temp)
							temp++;
					}while (temp);
					
 					if (nPos == currentPath)
					{
						wchar_t urlname2[4096];
						wcscpy(urlname2, urlname);
						wcscpy(urlname, currentScheme);
						wcscat(urlname, currentHost);
						wcscat(urlname, urlname);
 						goto endbreak;
					}
				}
//				nPos++;
				nPos[0] = 0;
				wcscat(currentPath, urlname);
				wcscpy(urlname, currentScheme);
				wcscat(urlname, currentHost);
				wcscat(urlname, currentPath);
endbreak:		;   
			
            }
        }
    }

//    ResolveRelativePath (urlname);


	// Decode the url
    DWORD bufferlength = 1024;
    wchar_t szBuffer[1024];
    InternetCanonicalizeUrlW((LPCTSTR)urlname, szBuffer, &bufferlength, ICU_DECODE | ICU_NO_ENCODE);
    //UtC(szBuffer, urlname);    
	wcscpy(urlname,szBuffer);

    return true;
}




STDMETHODIMP CHoops3dStreamCtrl::get_FileType(BSTR *pVal)
{
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::put_FileType(BSTR newVal)
{
	if (newVal)
	{
		char temp[4096];
		ConvertToChar(temp,newVal,4096);
		if (strcmp("2dmodel",temp) == 0)
			Set2dModel(true);
		else
			Set2dModel(false);
	}
 	
	return S_OK;
	
}

STDMETHODIMP CHoops3dStreamCtrl::get_AllowMenu(BOOL *pVal)
{
 
	*pVal = m_bAllowMenu;
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::put_AllowMenu(BOOL newVal)
{
 	 m_bAllowMenu = (newVal != 0);  	
	return S_OK;
	
}


void CHoops3dStreamCtrl::Set2dModel(bool modeltype)
{
	m_bIs2dModel = modeltype;
	
	
	if (m_pView)
	{
		if (m_bIs2dModel)
		{
			LocalSetOperator(new HOpCameraManipulate(m_pView, 0,1, new HOpCameraPan(m_pView), new HOpCameraPan(m_pView),
			    new HOpCameraZoom(m_pView),0,true));	

 			m_pView->SetProjMode(ProjOrthographic);
//			m_pView->RenderWireframe();
			m_bFastPrint = false;
			m_pView->SetAxisMode(AxisOff);
		}
		else
		{
			LocalSetOperator(new HOpCameraManipulate(m_pView));
// 			m_pView->SetProjMode(ProjPerspective);
			m_pView->RenderGouraud();
			m_bFastPrint = true;
			m_pView->SetAxisMode(m_StoredAxisMode);
		 
		}
	}
}

void CHoops3dStreamCtrl::SetNoOrbit(bool noorbit)
{
	m_bNoOrbit = noorbit;
	if (m_pView)
	{
		if (m_bNoOrbit && (strcmp(m_pView->GetOperator()->GetName(), "HOpCameraOrbit") == 0 ||
		    strcmp(m_pView->GetOperator()->GetName(), "HOpCameraManipulate") == 0))
			LocalSetOperator(new HOpCameraZoom(m_pView));
	}
}

// Not for doxygen.  Draws the scene into a Windows metafile.  The type of metafile is determined by m_metafile_type.  This method is called by 
// internal 
void CHoops3dStreamCtrl::DrawToMetafile (HWND hWnd, HDC hDC)
{
	if (hWnd == NULL)
	{
		OutputDebugString(_T("CHoopsControl : DrawToMetafile - No Window Handle\n"));
	}
	else
		OutputDebugString(_T("CHoopsControl : DrawToMetafile\n"));

    char    szTemp[256];
    long    debug_flags = DEBUG_CLIPBOARD_MODE;
   
	float	slx = -1.0;
	float	srx =  1.0;
	float	sly = -1.0;
	float	sry =  1.0;
    
	HWND nhWnd = hWnd;

	if (hWnd == NULL) {

		nhWnd = ::GetDesktopWindow();

		RECT rect;
		::GetClientRect(nhWnd, &rect);

		int Wx = rect.right - rect.left;
		int Wy = rect.bottom - rect.top;
		
		float car = (float) m_cx / (float) m_cy;
		float war = (float) Wx / (float) Wy;

		float n = war / car;

		slx = slx / n;
		srx = srx / n;
 
	}

	char	szSubScreen[256];
	sprintf(szSubScreen, "subscreen=(%f, %f, %f, %f)", slx, srx, sly, sry);

	HC_Open_Segment ("?driver/msw/clipboard"); 

	HandednessMode mode = m_pView->GetHandedness();

		if(mode == HandednessLeft)
			HC_Set_Handedness("left");	
		else if(mode == HandednessRight)
			HC_Set_Handedness("right");	

 		if (hWnd)
		{
//		rgb = m_pView->GetWindowColor();		
//        HC_Set_Color_By_Value ("windows", "RGB", rgb.x, rgb.y, rgb.z);
		}
      
        sprintf (szTemp, "use window ID = %u", nhWnd);
		HC_Set_Driver_Options (szTemp);

        sprintf (szTemp, "use window ID2 = %u", hDC);
		HC_Set_Driver_Options (szTemp);

        debug_flags |= DEBUG_NO_WINDOWS_HOOK;

        if (m_bClipboardTruecolor)
            debug_flags = debug_flags | DEBUG_FORCE_FULL_COLOR;

        if (m_bFastPrint)
            debug_flags |= DEBUG_SFB_COPY_TO_CLIPBOARD;

        sprintf (szTemp, "debug = %u", debug_flags);
		HC_Set_Driver_Options (szTemp);

        sprintf (szTemp, "%s, %s, %s",
                         "disable input",
                         "no subscreen stretching",
						 szSubScreen);
		HC_Set_Driver_Options (szTemp);

        char    hsra[512];
        char    hlr_options[256];
        BOOL    hlr = false, no_hsra = false;

	    // Check to see if Driver Segment is using the Hidden Line hsra 
		if (hWnd)
		{
		HC_Open_Segment_By_Key(m_pView->GetViewKey());

			HRenderMode rndrmode = m_pView->GetRenderMode();
			if (rndrmode == HRenderHiddenLine || rndrmode == HRenderHiddenLineFast)
			{
				HC_Show_One_Net_Rendering_Optio ("hidden line removal options", hlr_options);
                hlr = true;
            }

			HC_Show_One_Net_Heuristic("hidden surfaces", hsra);
			if (streq(hsra, "no") || streq(hsra, "off"))
				no_hsra = true;

		HC_Close_Segment();
		}

//		if (disable_painters_in_metafile)  // use to be a #define called DISABLE_PAINTERS_IN_METAFILE
		if (1)  // use to be a #define called DISABLE_PAINTERS_IN_METAFILE
		{
			// Forcing the hsr algorithm to szb
			HC_Set_Rendering_Options ("technology = software frame buffer, hsra = szb");
		}
		else 
		{
			// The following is disabled as painters algorithm has a problem and hangs
			// when we do not have a valid window handle while in MSWord
			if (hlr) {
				OutputDebugString(_T("hlr\n"));
				sprintf(szTemp, "hsra = hidden line, hidden line removal options = (%s)", hlr_options);
				HC_Set_Rendering_Options(szTemp);
			}
			else if (no_hsra) 
			{
				HC_Set_Heuristics("no hidden surfaces");
			}
			else if (m_bFastPrint) 
			{
				OutputDebugString(_T("szb\n"));
				HC_Set_Rendering_Options ("technology = software frame buffer, hsra = szb");
			}
			else 
			{
				OutputDebugString(_T("painters\n"));
				sprintf (szTemp, "hsr algorithm = painters, debug = %u", DEBUG_NO_PAINTERS_PANELLING);
				HC_Set_Rendering_Options (szTemp);
			}
		}

		HC_Include_Segment_By_Key (m_pView->GetSceneKey());
		HPoint rgbtop, rgbbottom;
		char color[MVO_BUFFER_SIZE];
		m_pView->GetWindowColor(rgbtop, rgbbottom);
		HCLOCALE(sprintf(color, "windows=(r=%f g=%f b=%f), window contrast = (r=%f g=%f b=%f)", rgbtop.x, rgbtop.y, rgbtop.z, rgbbottom.x, rgbbottom.y, rgbbottom.z));
		HC_Set_Window_Pattern("Down");
		HC_Set_Color(color);
		HC_Set_Window_Frame("off");


	HC_Close_Segment ();

	HC_Update_One_Display ("?driver/msw/clipboard");
	HC_Delete_Segment ("?driver/msw/clipboard");
}


void CHoops3dStreamCtrl::FixGuid(char *in1, char *in2, wchar_t *out1, wchar_t *out2)
{
	char res[256];
	strcpy(res, "{");
	strcat(res, in2);
	strcat(res, "}");
	mbstowcs(out2, res, strlen(res)+1);
	mbstowcs(out1, in1, strlen(in1)+1);
}







STDMETHODIMP CHoops3dStreamCtrl::SetBackgroundColors(float r_top, float g_top, float b_top, float r_bottom, float g_bottom, float b_bottom, int percentage)
{
	m_window_top_color.Set(r_top, g_top, b_top);
	m_window_bottom_color.Set(r_bottom, g_bottom, b_bottom);
	if (m_pView)
	{
		m_pView->SetWindowColor(m_window_top_color, m_window_bottom_color);
		HC_Control_Update_By_Key (m_pView->GetViewKey(), "redraw everything");
		m_pView->Update();	
	}

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::SetAmbientColor(float r, float g, float b)
{
	m_ambient_color.Set(r, g, b);
 	if (m_pView)
	{
		char text[4096];
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
		sprintf(text, "ambient = r = %f g = %f b = %f",r,g,b);
		HC_Set_Color(text);
		HC_Close_Segment();		
 		m_pView->Update();	
	}

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::SetOperator(BSTR operator_name)
{
	char op_name[4096];
 	ConvertToChar(op_name,operator_name,4096);

	if (strcmp("HOpCameraManipulate", op_name) == 0) 
	{
	    if (m_bIs2dModel)
			LocalSetOperator(new HOpCameraManipulate(m_pView, 0,1, new HOpCameraPan(m_pView), new HOpCameraPan(m_pView),
			    new HOpCameraZoom(m_pView),0,true));	
	    else
		LocalSetOperator(new HOpCameraManipulate(m_pView));
	}
	else if (strcmp("HOpCameraOrbit", op_name) == 0)			LocalSetOperator(new HOpCameraManipulate(m_pView));
	else if (strcmp("HOpCameraPan", op_name) == 0)				LocalSetOperator(new HOpCameraPan(m_pView));
	else if (strcmp("HOpCameraWalk", op_name) == 0)				LocalSetOperator(new HOpCameraWalk(m_pView));
	else if (strcmp("HOpCameraZoom", op_name) == 0)				LocalSetOperator(new HOpCameraZoom(m_pView));
	else if (strcmp("HOpCameraZoomBox", op_name) == 0)			LocalSetOperator(new HOpCameraZoomBox(m_pView));
	else if (strcmp("HOpConstructCircle", op_name) == 0)			LocalSetOperator(new HOpConstructCircle(m_pView));
	else if (strcmp("HOpConstructCuboid", op_name) == 0)			LocalSetOperator(new HOpConstructCuboid(m_pView));
	else if (strcmp("HOpConstructPolyline", op_name) == 0)			LocalSetOperator(new HOpConstructPolyline(m_pView));
	else if (strcmp("HOpConstructRectangle", op_name) == 0)			LocalSetOperator(new HOpConstructRectangle(m_pView));
	else if (strcmp("HOpCreateCone", op_name) == 0)				LocalSetOperator(new HOpCreateCone(m_pView));
	else if (strcmp("HOpCreateCuttingPlane", op_name) == 0)			LocalSetOperator(new HOpCreateCuttingPlane(m_pView));
	else if (strcmp("HOpCreateCylinder", op_name) == 0)			LocalSetOperator(new HOpCreateCylinder(m_pView));
	else if (strcmp("HOpCreateNurbs3D", op_name) == 0)			LocalSetOperator(new HOpCreateNurbs3D(m_pView));
	else if (strcmp("HOpCreateNurbsCurve", op_name) == 0)			LocalSetOperator(new HOpCreateNurbsCurve(m_pView));
	else if (strcmp("HOpCreateSphere", op_name) == 0)			LocalSetOperator(new HOpCreateSphere(m_pView));
	else if (strcmp("HOpMarkupAnnotate", op_name) == 0)			LocalSetOperator(new HOpMarkupAnnotate(m_pView));
	else if (strcmp("HOpMarkupPostIt", op_name) == 0)			LocalSetOperator(new HOpMarkupPostIt(m_pView));
	else if (strcmp("HOpMarkupCircle", op_name) == 0)			LocalSetOperator(new HOpMarkupCircle(m_pView));
	else if (strcmp("HOpMarkupFreehand", op_name) == 0)			LocalSetOperator(new HOpMarkupFreehand(m_pView));
	else if (strcmp("HOpMarkupMeasure", op_name) == 0)			LocalSetOperator(new HOpMarkupMeasure(m_pView));
	else if (strcmp("HOpMarkupRectangle", op_name) == 0)			LocalSetOperator(new HOpMarkupRectangle(m_pView));
	else if (strcmp("HOpMoveHandle", op_name) == 0)				LocalSetOperator(new HOpMoveHandle(m_pView));
	else if (strcmp("HOpNavCube", op_name) == 0)				LocalSetOperator(new HOpNavCube(m_pView));
	else if (strcmp("HOpObjectAnnotate", op_name) == 0)			LocalSetOperator(new HOpObjectAnnotate(m_pView));
	else if (strcmp("HOpObjectClash", op_name) == 0)			LocalSetOperator(new HOpObjectClash(m_pView));
	else if (strcmp("HOpObjectRotate", op_name) == 0)			LocalSetOperator(new HOpObjectRotate(m_pView));
	else if (strcmp("HOpObjectTranslate", op_name) == 0)			LocalSetOperator(new HOpObjectTranslate(m_pView));
	else if (strcmp("HOpSelectAperture", op_name) == 0)			LocalSetOperator(new HOpSelectAperture(m_pView));
	else if (strcmp("HOpSelectArea", op_name) == 0)				LocalSetOperator(new HOpSelectArea(m_pView));
	else if (strcmp("HOpSelectPolygon", op_name) == 0)			LocalSetOperator(new HOpSelectPolygon(m_pView));
	else if (strcmp("HOpSelectPolyline", op_name) == 0)			LocalSetOperator(new HOpSelectPolyline(m_pView));
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetRenderMode(BSTR rendermode)
{
	if (m_pView)
	{
	        char rendermode_char[4096];
	        ConvertToChar(rendermode_char,rendermode,4096);

		if (strcmp(rendermode_char, "shaded") == 0)
		    SetRenderModeShaded();
		else if (strcmp(rendermode_char, "flat") == 0)
		    SetRenderModeFlat();
		else if (strcmp(rendermode_char, "gouraud") == 0)
		    SetRenderModeGouraud();
		else if (strcmp(rendermode_char, "gouraud with edges") == 0)
		    SetRenderModeGouraudWithEdges();
		else if (strcmp(rendermode_char, "wireframe") == 0)
		    SetRenderModeWireframe();
		else if (strcmp(rendermode_char, "hidden line") == 0)
		    SetRenderModeHiddenLine();
	
	}
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::SetRenderModeShaded()
{
	if (m_pView)
	{
		m_pView->SetRenderMode(HRenderShaded, true);
 		m_bFastPrint = true;
		m_pView->Update();
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetRenderModeFlat()
{
	
	if (m_pView)
	{
		m_pView->RenderFlat();
		m_pView->Update();
		m_bFastPrint = true;
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetRenderModeGouraud()
{
	if (m_pView && m_pModel)
	{
		
		HBaseModel * model = m_pView->GetModel();
		
		if (!model->IsVectorGeometry())
		{
			m_pView->RenderGouraud();
			
			HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Visibility("faces=on, edges=off, lines = off, lights = (faces=on,edges=off)");
			HC_Close_Segment();
			m_pView->Update();	
			m_bFastPrint = true;
			
		}	
	}
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::SetRenderModeGouraudWithEdges()
{
	if(m_pView)
	{
		m_pView->SetRenderMode(HRenderGouraudWithEdges);
		m_pView->Update();
	}
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::SetRenderModeWireframe()
{
	if (m_pView && m_pModel)
	{
 		HBaseModel * model = m_pView->GetModel();
		
		m_pView->RenderWireframe();
		
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
		if (model->IsBRepGeometry())
			HC_Set_Visibility("edges = (everything = off), lines = on");
		else
			HC_Set_Visibility("edges = on, lines = on");
		HC_Close_Segment();
		
		m_pView->Update();	
		m_bFastPrint = false;
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetRenderModeHiddenLine()
{
	if (m_pModel && m_pView)
	{
		m_pView->RenderHiddenLineFast();
 		m_pView->Update();
		m_bFastPrint = true;	
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::InsertCuttingPlane()
{
	LocalSetOperator(new HOpMoveHandle(m_pView, false));
 	HUtilityGeometryCreation::CreateCuttingPlane(m_pView);
	HUtilityGeomHandle::SetupObject(m_pView->GetCuttingPlanesKey(), m_pView);
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetViewAxis(float fx, float fy, float fz,
											 float tx, float ty, float tz)
{
	HVector front(fx, fy, fz), top(tx, ty, tz);
	m_pView->SetViewAxis(&front,  &top);	
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetCameraToPlaneXY()
{
	m_pView->SetViewMode(HViewXY);
	m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetCameraToPlaneXZ()
{
	m_pView->SetViewMode(HViewXZ);	
    m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetCameraToPlaneYZ()
{
	m_pView->SetViewMode(HViewYZ);
    m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetCameraToPlaneZX()
{
	m_pView->SetViewMode(HViewZX);
    m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetCameraToPlaneZY()
{
	m_pView->SetViewMode(HViewZY);
    m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetCameraToPlaneYX()
{
	m_pView->SetViewMode(HViewYX);
    m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetCameraToIsometric()
{
	m_pView->SetViewMode(HViewIso);
	m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SaveRestoreMarkup(int layernum)
{
	if (m_pView && layernum < NUM_MARKUP_LAYERS)
	{
		HMarkupManager *markup;	
		
		if ((GetAsyncKeyState(VK_SHIFT) & 32768))
		{
			if ((markup = m_pView->GetMarkupManager()))
				m_activelayerkeys[layernum] = markup->GetCurrentLayerKey();
			
			// now redline information, just want to store the camera position.
			if (m_activelayerkeys[layernum] == -1)
				m_activelayerkeys[layernum] = markup->OpenLayer("");
		}
		else
		{
			if ((markup = m_pView->GetMarkupManager()) && m_activelayerkeys[layernum] != -1)
			{
				char segpath[2048], activelayer[1024];
				HC_Show_Segment(m_activelayerkeys[layernum], segpath);
				HC_Parse_String(segpath, "/", -1, activelayer);
				markup->OpenLayer(activelayer, true);
			}
		}
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetProjectionModePerspective()
{
	if (m_pView)
	{
		m_pView->SetProjMode(ProjPerspective);
		m_pView->Update();
	}
	
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetProjectionModeOrthographic()
{
	if (m_pView)
	{
		m_pView->SetProjMode(ProjOrthographic);
		m_pView->Update();
	}
	
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetShadowMode(BOOL onoff)
{
	if (m_pView)
	{
		
		if (onoff)
			m_pView->SetShadowMode(HShadowSoft);
		else
			m_pView->SetShadowMode(HShadowNone);

		m_pView->Update();
	}
	m_bShadowMode = BOOL2bool(onoff);
	
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::AntialiasScene()
{
	if (m_pView)
	{
		m_pView->RenderAntialiasing();
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetPolygonHandednessLeft()
{
	if (m_pView)
	{
		m_pView->SetPolygonHandednessMode(HandednessLeft);
		m_pView->Update();	
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetPolygonHandednessRight()
{
	if (m_pView)
	{
		m_pView->SetPolygonHandednessMode(HandednessRight);
		m_pView->Update();	
	}
	
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetPolygonHandednessNone()
{
	if (m_pView)
	{
		m_pView->SetPolygonHandednessMode(HandednessNone);
		m_pView->Update();	
	}
	
	return S_OK;
}




STDMETHODIMP CHoops3dStreamCtrl::SetBackplaneCullingMode(BOOL onoff)
{
	if (m_pView)
	{
		
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
		
		if (!onoff) 
			m_pView->SetBackplaneCulling(false);
		else 
			m_pView->SetBackplaneCulling(true);
		
		HC_Close_Segment();	
		
		m_pView->Update();	
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetFramerateMode(BOOL onoff)
{	
	if (m_pView)
	{
		HConstantFrameRate *cframerate = m_pView->GetConstantFrameRateObject();
		if (onoff)
		{
			m_pView->SetFramerateMode(m_FramerateType, m_FrameRate, m_MaximumThreshold);
 		}
		else
		{
			m_pView->SetFramerateMode(FramerateOff, m_FrameRate);
		}
	}

	return S_OK;
}



STDMETHODIMP CHoops3dStreamCtrl::OpenSceneSegment()
{	
	if (m_pView)
		HC_Open_Segment_By_Key (m_pView->GetSceneKey());
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::OpenModelSegment()
{
	if (m_pView && m_pModel)
		HC_Open_Segment_By_Key (m_pModel->GetModelKey());

	return S_OK;
}






STDMETHODIMP CHoops3dStreamCtrl::Update()
{
	if (m_pView && !m_pView->SceneDetached())
		m_pView->Update();
 	return S_OK;
}



STDMETHODIMP CHoops3dStreamCtrl::get_ControlActive(BOOL *pVal)
{
	if (m_pView)
		*pVal = true;
	else
		*pVal = false;
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::BhvPlay()
{

	m_pView->SetShadowMode(HShadowNone);


	HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
	if (pBehaviorManager->IsAtFinalTick())
		pBehaviorManager->Rewind();

	pBehaviorManager->Play();

 
	HC_Open_Segment_By_Key(m_pView->GetSceneKey());
	HC_Set_Rendering_Options("color interpolation");
	HC_Close_Segment();
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::BhvActivateAllAnimations()
{

	HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
	pBehaviorManager->ActivateAllAnimations();
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::BhvDeactivateAllAnimations()
{

	HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
	pBehaviorManager->DeactivateAllAnimations();
 	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::BhvActivateAnimation(BSTR animationname, BOOL allowPartial)
{
	if (m_pView)
	{
		char animationname_char[4096];
		ConvertToChar(animationname_char,animationname,4096);
		HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
		pBehaviorManager->ActivateAnimationByName(animationname_char, BOOL2bool(allowPartial));
	}
 
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::BhvStartAnimation(BSTR animationname)
{
	if (m_pView)
	{
		char animationname_char[4096];
		ConvertToChar(animationname_char,animationname,4096);
		HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
		HBhvAnimation *anim = pBehaviorManager->FindAnimationByName(animationname_char);
		pBehaviorManager->ScheduleAnimation(anim, pBehaviorManager->GetCurrentTick());
	}
 
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::BhvStopAnimation(BSTR animationname)
{
	if (m_pView)
	{
		char animationname_char[4096];
		ConvertToChar(animationname_char,animationname,4096);
		HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
		HBhvAnimation *anim = pBehaviorManager->FindAnimationByName(animationname_char);

		pBehaviorManager->RemoveScheduledAnimation(anim);

	}
 
 	return S_OK;
}



STDMETHODIMP CHoops3dStreamCtrl::BhvRewindAnimation(BSTR animationname)
{
	if (m_pView)
	{
		char animationname_char[4096];
		ConvertToChar(animationname_char,animationname,4096);
		HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
		HBhvAnimation *anim = pBehaviorManager->FindAnimationByName(animationname_char);

		HBhvTimeline *ti = anim->GetTimeline();
		ti->SetStartTick( pBehaviorManager->GetCurrentTick() + anim->GetDelay());
		ti->SetCurrentRelativeTick(0);
		anim->SetExecuteOnce(true);
 
	}
 
 	return S_OK;
}

 


STDMETHODIMP CHoops3dStreamCtrl::BhvSetInfinitePlay(BOOL onoff)
{	

	if (m_pView)
	{	  
		HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
		if (onoff)
		        pBehaviorManager->SetInfinitePlay(true);
		else
		        pBehaviorManager->SetInfinitePlay(false);
	}
 
	return S_OK;
}



STDMETHODIMP CHoops3dStreamCtrl::BhvDeactivateAnimation(BSTR animationname, BOOL allowPartial)
{
	if (m_pView)
	{
		char animationname_char[4096];
		ConvertToChar(animationname_char,animationname,4096);
		HBhvBehaviorManager * pBehaviorManager = m_pView->GetModel()->GetBhvBehaviorManager();
		pBehaviorManager->DeactivateAnimationByName(animationname_char, BOOL2bool(allowPartial));
	}
 
 	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::FlushScene()
{

    if (m_pView)
    {
	m_pView->FlushScene();
	m_pView->Update();
    }
    return S_OK;
}




LRESULT CHoops3dStreamCtrl::OnBhvPlay(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	BhvPlay();
 	return 0;
}


STDMETHODIMP CHoops3dStreamCtrl::get_IsPlaying(BOOL *pVal)
{
	if (m_pView)
	{
		if (m_pView->GetModel()->GetBhvBehaviorManager()->IsPlaying())
			*pVal = true;
		else
			*pVal = false;
	}
	else
		*pVal = false;
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::BhvPause()
{
	if (m_pView)
	{	

	if (!m_pView->GetModel()->GetBhvBehaviorManager()->IsPlaying())
	{
		m_pView->SetShadowMode(HShadowNone);
		m_pView->GetModel()->GetBhvBehaviorManager()->Continue();
	}
	else
	{
		m_pView->GetModel()->GetBhvBehaviorManager()->Stop();
		SetShadowMode(m_bShadowMode);

	}

	//	m_pView->GetModel()->GetBhvBehaviorManager()->Stop();  
	}
	return S_OK;
}

LRESULT CHoops3dStreamCtrl::OnBhvPause(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	BhvPause();
 	return 0;
}



STDMETHODIMP CHoops3dStreamCtrl::BhvRewind()
{
	if (m_pView)	
		m_pView->GetModel()->GetBhvBehaviorManager()->Rewind();  	
	return S_OK;
}
 
LRESULT CHoops3dStreamCtrl::OnBhvRewind(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	BhvRewind();
 	return 0;
}


 
  
STDMETHODIMP CHoops3dStreamCtrl::get_Antialiasing(BOOL *pVal)
{
 	*pVal = m_bUseAntialiasing;
	return S_OK;
}

/*!
	Property:
	set camera parameters
 
*/ 
STDMETHODIMP CHoops3dStreamCtrl::put_Antialiasing(BOOL newVal)
{
	m_bUseAntialiasing = (newVal != 0);
	SetFramerateMode(true);
   	SetDirty(true);
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::put_HardwareAntialiasing(BOOL newVal)
{
	m_bUseHardwareAntialiasing = (newVal != 0);
    	SetDirty(true);
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_HardwareAntialiasing(BOOL *pVal)
{
 	*pVal = m_bUseHardwareAntialiasing;
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::put_AxisMode(BOOL newVal)
{
	if (newVal)
	    m_StoredAxisMode = AxisOn;
	else
	    m_StoredAxisMode = AxisOff;

	if (m_pView)
	{	
	    m_pView->SetAxisMode(m_StoredAxisMode);
	    m_pView->Update();
	}
     	SetDirty(true);
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_AxisMode(BOOL *pVal)
{
	if (m_StoredAxisMode == AxisOn)
 	    *pVal = true;
	else
 	    *pVal = false;
	return S_OK;
}

/* test - warren */
/*STDMETHODIMP CHoops3dStreamCtrl::put_Test(BOOL newVal)
{
	m_window_bottom_color.Set(0, 1.0f, 0);
	m_window_top_color.Set(0, 0, 1.0f);
	
	if (m_pView)
	{	
		m_pView->SetWindowColor(m_window_top_color, m_window_bottom_color);
 		HC_Control_Update_By_Key (m_pView->GetViewKey(), "redraw everything");
		m_pView->Update();
	}
     	SetDirty(true);
	return S_OK;
}*/
STDMETHODIMP CHoops3dStreamCtrl::get_Key(LONG *pVal)
{
	*pVal = LastKey;
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::get_String1(BSTR *pVal)
{
	*pVal = CComBSTR(String1).Copy();
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_String2(BSTR *pVal)
{
	*pVal = CComBSTR(String2).Copy();
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_String3(BSTR *pVal)
{
	*pVal = CComBSTR(String3).Copy();
	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_Int1(int *pVal)
{
	*pVal = Int1;
	return S_OK;
}

LRESULT CHoops3dStreamCtrl::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
 	if (m_pView)
	{
		HEventInfo	event(m_pView);
		HBaseOperator *op = m_pView->GetCurrentOperator();

		if (op)
		{
			
			//unsigned short ascii_key=0;
			BYTE keys[256];

			GetKeyboardState( keys );
						
			//event.SetKey(HE_KeyDown, wParam, LOWORD(lParam), MapFlags(HIWORD(lParam)));
			event.SetKey(HE_KeyDown, wParam, LOWORD(lParam), 0);
			op->OnKeyDown(event);
			
		}
	}
	return 0;

}


HRESULT CHoops3dStreamCtrl::ShowFileDialog(TCHAR * ret_filename_buff, unsigned int buff_size, HWND owner)
{
	if(!buff_size)
		return S_FALSE;
	
	char filterChar[8000];
	strcpy(filterChar,"");
	
	START_LIST_ITERATION(char, m_FileTypeList)
	    strcat(filterChar, temp);
	    strcat(filterChar, "|");
	END_LIST_ITERATION(m_FileTypeList);
	strcat(filterChar,"All Files (*.*)|*.*||");

	
	TCHAR szFilter[4096];
	CtU(filterChar, szFilter);
//	TCHAR szFilter[4096] = _T("HOOPS Stream Files (*.hsf)|*.hsf|HOOPS ASCII Metafiles (*.hmf)|*.hmf|All Files (*.*)|*.*||");
	ret_filename_buff[0] = _T('\0');
	
	int slen = _tcslen(szFilter);
	for (int i=0;i<slen;i++)
	{
		if (szFilter[i] == '|')
			szFilter[i] = 0;
	}
	
	OPENFILENAME of;
	of.lStructSize = sizeof(OPENFILENAME);
	of.hwndOwner = owner;
	of.hInstance = 0;
 	of.lpstrFilter = szFilter;
	of.lpstrCustomFilter = 0;
	of.nFilterIndex = 0;
	of.lpstrFile = ret_filename_buff;
	of.nMaxFile = buff_size;
	of.lpstrFileTitle = 0;
	of.lpstrInitialDir = 0;
	of.lpstrTitle =0;
	of.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	of.lpstrDefExt = 0;
	of.lCustData = 0;
 
	
	if (GetOpenFileName(&of))
		return S_OK;
	else
		return S_FALSE;
}




HRESULT CHoops3dStreamCtrl::ShowFileDialog2(TCHAR * ret_filename_buff, unsigned int buff_size, HWND owner)
{
	if(!buff_size)
		return S_FALSE;

	
 	TCHAR szFilter[4096] = _T("HOOPS Stream Files (*.hsf)|*.hsf|HOOPS ASCII Metafiles (*.hmf)|*.hmf|All Files (*.*)|*.*||");
	ret_filename_buff[0] = _T('\0');
	
	int slen = _tcslen(szFilter);
	for (int i=0;i<slen;i++)
	{
		if (szFilter[i] == '|')
			szFilter[i] = 0;
	}
	
	OPENFILENAME of;
	of.lStructSize = sizeof(OPENFILENAME);
	of.hwndOwner = owner;
	of.hInstance = 0;
 	of.lpstrFilter = szFilter;
	of.lpstrCustomFilter = 0;
	of.nFilterIndex = 0;
	of.lpstrFile = ret_filename_buff;
	of.nMaxFile = buff_size;
	of.lpstrFileTitle = 0;
	of.lpstrInitialDir = 0;
	of.lpstrTitle =0;
	of.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	of.lpstrDefExt = 0;
	of.lCustData = 0;
 
	
	if (GetOpenFileName(&of))
		return S_OK;
	else
		return S_FALSE;
}



HRESULT CHoops3dStreamCtrl::ShowFileSaveDialog(TCHAR * ret_filename_buff, unsigned int buff_size, HWND owner)
{
	if(!buff_size)
		return S_FALSE;
	
	TCHAR szFilter[] = _T("HTML Page (*.html)|*.html|HOOPS Stream File (*.hsf)|*.hsf|HOOPS Animation File (*.bhv)|*.bhv|HOOPS Metafile (*.hmf)|*.hmf|TIFF Image File (*.tif)|*.tif|Postscript File (*.ps)|*.ps|HPGL/2 Plot File (*.hp)|*.hp|CGM File (*.cgm)|*.cgm||");
	TCHAR def_file_ext[10] = _T(".hsf");
	ret_filename_buff[0] = 0;
	
	int slen = _tcslen(szFilter);
	for (int i=0;i<slen;i++)
	{
		if (szFilter[i] == '|')
			szFilter[i] = 0;
	}
	
	OPENFILENAME of;
	of.lStructSize = sizeof(OPENFILENAME);
	of.hwndOwner = owner;
	of.hInstance = 0;
 	of.lpstrFilter = szFilter;
	of.lpstrCustomFilter = 0;
	of.nFilterIndex = 0;
	of.lpstrFile = ret_filename_buff;
	of.nMaxFile = buff_size;
	of.lpstrFileTitle = 0;
	of.lpstrInitialDir = 0;
	of.lpstrTitle =0;
	of.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	of.lpstrDefExt = def_file_ext;
	of.lCustData = 0;
	
	if (GetSaveFileName(&of))
		return S_OK;
	else
		return S_FALSE;
}



STDMETHODIMP CHoops3dStreamCtrl::ShowFileOpenDialog()
{
	USES_CONVERSION;
	TCHAR newfile[MVO_BUFFER_SIZE];

	m_bFileOpenActive = true;
	if(ShowFileDialog(newfile, MVO_BUFFER_SIZE) == S_OK){
		put_Filename(T2OLE(newfile));
	}
	m_bFileOpenActive = false;

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::ShowFileSaveDialog()
{
	TCHAR newfile[MVO_BUFFER_SIZE];
	if(ShowFileSaveDialog(newfile, MVO_BUFFER_SIZE) == S_OK)
	{
		if( !SaveFile(newfile) )
			return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::ShowPrintDialog()
{
	Print();
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::ShowPageSetupDialog()
{
	PAGESETUPDLG ps_dlg;
	ZeroMemory(&ps_dlg, sizeof(PAGESETUPDLG));
	ps_dlg.lStructSize = sizeof(PAGESETUPDLG);
	ps_dlg.hwndOwner   = 0;
	ps_dlg.hDevMode    = NULL;
	ps_dlg.hDevNames   = NULL;
	ps_dlg.Flags       = 0;
	
    if (!PageSetupDlg(&ps_dlg))
        return S_FALSE;
	
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::CopyToClipboard()
{
	// Clean clipboard of contents and copy.
	if (OpenClipboard()) {
		EmptyClipboard();
		CloseClipboard();
	}

	HDC	hDC = GetDC();
	GDIExportInformation pinfo;

	pinfo.deviceContext = hDC;
	pinfo.windowID = (void *)m_hWnd;
	pinfo.rasterOutput = m_bFastPrint;
	pinfo.clipBoard= true;

	HOutputHandlerOptions options;
	options.m_pExtendedData = (void *)&pinfo;

	HOutputHandler * handler = new HIOUtilityGDIOutput;

	// if none found quit
	if(!handler) 
		return 0;
	
	m_pView->FileOutput("test.emf", handler, &options);

	return S_OK;
}




void CHoops3dStreamCtrl::GetArrayFromVariant(VARIANT * varKeys, float **arrayfloat, int **arrayint, char **arraychar, int &length)
{
	if(arrayfloat)
		GetArrayFromVariant2(varKeys,(void **)arrayfloat,"float",length);
	else if(arrayint)
		GetArrayFromVariant2(varKeys,(void **)arrayint,"int",length);
	else if(arraychar)
		GetArrayFromVariant2(varKeys,(void **)arraychar,"char",length);

	/* Now wraps to GetArrayFromVariant2.
	 * The following code is the old version.
	 */

#if 0
 	length = 0;
 	VARIANT jArray; 
	VariantInit(&jArray);   
	
	if ((varKeys->vt & VT_TYPEMASK) == VT_DISPATCH) { 
        IDispatch* disp = 
		(varKeys->vt & VT_BYREF ? *varKeys->ppdispVal : varKeys->pdispVal); 

	    DISPID DISPID_GET_SAFEARRAY(-2700L); 
	    DISPPARAMS dispParams = {NULL, NULL, 0, 0}; 
	    HRESULT hr = disp->Invoke(DISPID_GET_SAFEARRAY, IID_NULL, 
                              LOCALE_USER_DEFAULT, 
                              DISPATCH_PROPERTYGET, &dispParams, 
                              &jArray, 
                              NULL, NULL); 

	    if (SUCCEEDED(hr)) 
		{
		    length = jArray.parray->rgsabound[0].cElements;
		    if (arrayfloat)
			*arrayfloat = new float[length];
		    else if (arrayint)
			*arrayint = new int[length];
		    else if (arraychar)
			*arraychar = new char[length];

		    for (int i=0;i<length;i++)
		    {		    
				VARIANT *res = (VARIANT *)jArray.parray->pvData+i;
				if (arrayfloat)
					(*arrayfloat)[i] =  res->dblVal;
				else if (arrayint)
					(*arrayint)[i] =  res->intVal;
				else if (arraychar)
					(*arraychar)[i] =  res->bVal;
			}

		}
	}
#endif
}
 
/* This is an improved version of the above function, which now wraps to this function.
 * Type is a string defining what sort of data type to use ("char,int,short,float,double,etc")
 * Length is returned.
 */
void CHoops3dStreamCtrl::GetArrayFromVariant2(VARIANT * varKeys, void **ret_array, char *type, int &length)
{
 	length = 0;
	int newlength;

 	VARIANT jArray; 
	VariantInit(&jArray);   
	
	if ((varKeys->vt & VT_TYPEMASK) == VT_DISPATCH) { 
        IDispatch* disp = 
		(varKeys->vt & VT_BYREF ? *varKeys->ppdispVal : varKeys->pdispVal); 

	    DISPID DISPID_GET_SAFEARRAY(-2700L); 

	    DISPPARAMS dispParams = {NULL, NULL, 0, 0}; 

	    HRESULT hr = disp->Invoke(DISPID_GET_SAFEARRAY, IID_NULL, 
                              LOCALE_USER_DEFAULT, 
                              DISPATCH_PROPERTYGET, &dispParams, 
                              &jArray, 
                              NULL, NULL); 

	    if (SUCCEEDED(hr)) 
		{   
		    newlength = jArray.parray->rgsabound[0].cElements;
		    if (strcmp(type,"char") == 0)
				*ret_array = new char[newlength];
			else if (strcmp(type,"short") == 0)
				*ret_array = new short[newlength];
			else if (strcmp(type,"int") == 0)
				*ret_array = new int[newlength];
			else if (strcmp(type,"float") == 0)
				*ret_array = new float[newlength];
			else if (strcmp(type,"double") == 0)
				*ret_array = new double[newlength];
			else
				return;

			/* This copies values from the javascript array to the user array.
			 * Javascript arrays are optimized such that the "best fit" type will
			 * be used to store data. Thus, 1.00 will be stored as an int, not a float.
			 * Because of this, we need to check what the type is (res->vt) and then copy
			 * values over from the correct location (otherwise we get incorrect values).
			 */
		    for (int i=0;i<newlength;i++)
		    {		    
				VARIANT *res = (VARIANT *)jArray.parray->pvData+i;
				if (strcmp(type,"char") == 0)
				{
					switch(res->vt)
					{
						case VT_I2:	
						case VT_I4: (*(char **) ret_array)[i] = res->bVal; break;
						case VT_R4:
						case VT_R8: (*(char **) ret_array)[i] = res->fltVal; break;
					}
				}
				else if (strcmp(type,"short") == 0)
				{
					switch(res->vt)
					{
						case VT_I2:	
						case VT_I4: (*(short **) ret_array)[i] = res->iVal; break;
						case VT_R4:
						case VT_R8: (*(short **) ret_array)[i] = res->fltVal; break;
					}
				}
				else if (strcmp(type,"int") == 0)
				{
					switch(res->vt)
					{
						case VT_I2:	
						case VT_I4: (*(int **) ret_array)[i] = res->intVal; break;
						case VT_R4:
						case VT_R8: (*(int **) ret_array)[i] = res->fltVal; break;
					}
				}
				else if (strcmp(type,"float") == 0)
				{
					switch(res->vt)
					{
						case VT_I2:	
						case VT_I4: (*(float **) ret_array)[i] = res->intVal; break;
						case VT_R4:
						case VT_R8: (*(float **) ret_array)[i] = res->fltVal; break;
					}
				}
				else if (strcmp(type,"double") == 0)
				{
					switch(res->vt)
					{
						case VT_I2:	
						case VT_I4: (*(double **) ret_array)[i] = res->intVal; break;
						case VT_R4:
						case VT_R8: (*(double **) ret_array)[i] = res->dblVal; break;
					}
				}
			}

			length = newlength;
		}
	} 	    
}


void CHoops3dStreamCtrl::GetPointArrayFromVariant(VARIANT * varKeys, HPoint **arrayfloat, int &length)
{
    int len;
    //GetArrayFromVariant(varKeys, (float **)arrayfloat, 0, 0,len);
	GetArrayFromVariant2(varKeys, (void **)arrayfloat, "float", len);
    length = len/3;
}

void CHoops3dStreamCtrl::GetFloatArrayFromVariant(VARIANT * varKeys, float **arrayfloat, int &length)
{
	//GetArrayFromVariant(varKeys, (float **)arrayfloat, 0, 0,length);
	GetArrayFromVariant2(varKeys, (void **)arrayfloat, "float", length);
}

void CHoops3dStreamCtrl::GetIntegerArrayFromVariant(VARIANT * varKeys, int **arrayint, int &length)
{
    //GetArrayFromVariant(varKeys, 0, arrayint, 0,length);
	GetArrayFromVariant2(varKeys, (void **) arrayint, "int" , length);
}

void CHoops3dStreamCtrl::GetShortArrayFromVariant(VARIANT * varKeys, short **arrayshort, int &length)
{
	GetArrayFromVariant2(varKeys, (void **) arrayshort, "short", length);
}
 
void CHoops3dStreamCtrl::GetByteArrayFromVariant(VARIANT * varKeys, char **arraybyte, int &length)
{
    //GetArrayFromVariant(varKeys, 0, 0, arraybyte, length);
	GetArrayFromVariant2(varKeys, (void **) arraybyte, "char", length);
}


/*!
  Receive the MVO event HSignalSelected event here and call the appropriate handler
*/
bool CHoops3dStreamCtrl::signal_selected(int signal, void * signal_data, void *user_data)
{
	return ((CHoops3dStreamCtrl*)user_data)->OnSignalSelected();
}
/*!
  Receive the MVO event HSignalDeSelectedAll event here and call the appropriate handler
*/
bool CHoops3dStreamCtrl::signal_deselected_all(int signal, void * signal_data, void *user_data)
{
	return ((CHoops3dStreamCtrl*)user_data)->OnSignalDeSelectedAll();
}



/*!
  HSignalSelected MVO event handler. Update any dialog bars we have
  \return bool
*/
bool CHoops3dStreamCtrl::OnSignalSelected()
{
	HSelectionSet* sel_set = (HSelectionSet *)m_pView->GetSelection();
	if(sel_set && sel_set->GetSize() > 0)
	{
		HC_KEY selkey = sel_set->GetAt(0);
		char key_str[MVO_BUFFER_SIZE];
		sprintf(key_str, "%p", (void*)selkey);
		Fire_OnSelect(A2BSTR(key_str));
	}
	return true;
}

/*!
  HSignalDeSelectedAll MVO event handler. Update any dialog bars we have
  \return bool
*/
bool CHoops3dStreamCtrl::OnSignalDeSelectedAll()
{
	return true;
}

static void generate_xml_segment_tree(HC_KEY parent_seg, HUtilityXMLGenerator* xmlgen, bool do_recurse)
{

	HC_KEY	child_seg_key;
    char	type[MVO_BUFFER_SIZE];
	char	pathname[MVO_SEGMENT_PATHNAME_BUFFER]; 
	char	seg_name[MVO_SEGMENT_PATHNAME_BUFFER];
	char	user_data[MVO_BUFFER_SIZE];

	// open the segment and add it's name and key to the ree
	HC_Open_Segment_By_Key(parent_seg);

	 	HUtilityXMLTag xmlt;
		xmlt.SetTagname("tree");

		HC_Show_Segment(parent_seg, pathname);
		HC_Parse_String(pathname, "/", -1, seg_name);

		xmlt.AddProperty("text", seg_name, true);

		sprintf(user_data,"%p", (void*)parent_seg);
		xmlt.AddProperty("userData", user_data, true);

		xmlt.SetOpen(true);
   		xmlgen->AddTag(&xmlt);

		HC_Begin_Contents_Search (".", "segment, includes");
		if (do_recurse) 
		{
			while (HC_Find_Contents (type, &child_seg_key) ) 
			{
				if (strstr("include", type))
					child_seg_key = HC_KShow_Include_Segment(child_seg_key);

				generate_xml_segment_tree(child_seg_key, xmlgen, do_recurse);
			}
		}
		HC_End_Contents_Search ();

  		xmlgen->CloseTag(&xmlt);
	HC_Close_Segment();
}

// uses standard apis to generate a temp prt file name in a temp
// direction - aka gsfCE17.prt
static void generate_temp_filename(TCHAR * retFilename)
{
	TCHAR temp_dir[_MAX_DIR];
	DWORD dir_len = GetTempPath( _MAX_DIR,  temp_dir );
	assert( dir_len != 0);	assert( dir_len <= _MAX_DIR);
	UINT res = GetTempFileName( temp_dir, _T("HOOPS"), 0, retFilename);
	assert( res != 0);
	// change the extension from .tmp to .xml
	int fname_len = _tcslen( retFilename );
	retFilename[fname_len-3] = _T('x');
	retFilename[fname_len-2] = _T('m'); 
	retFilename[fname_len-1] = _T('l'); 
}

// level = -2 will generate xml for all nodes
// level = -1 will generate top level tree
// level = id will generate xml for all children of given id
STDMETHODIMP CHoops3dStreamCtrl::GenerateNavigationInfo(int level, BSTR *filepath)
{
	if( !m_pDataLoader->GetTreeControlXML() )
		return S_FALSE;
	
	// create a temporary file for the output
	TCHAR temp_ouput_file[_MAX_DIR];
	generate_temp_filename(temp_ouput_file);

	FILE * tmp_xml = _tfopen(temp_ouput_file, _T("w+t"));
	if( level >= -1 )
	{
		char * data = 0;
		m_pDataLoader->GetXMLForItemChildren(level, data);
		if(data)
		{
			fprintf(tmp_xml, "%s", data);
			delete[] data;
		}
	}
	else
	{
		if( m_pDataLoader->GetTreeControlXML() )
			fprintf(tmp_xml, "%s", m_pDataLoader->GetTreeControlXML());
	}

	fflush(tmp_xml);
	fclose(tmp_xml);


//	HUtilityXMLGenerator xmlgen;
//	xmlgen.Reset();
//
//	generate_xml_segment_tree(m_pModel->GetModelKey(), &xmlgen, true);
//	xmlgen.Finalize();
//
//
//	FILE * tmp_xml = _tfopen(temp_ouput_file, _T("w+t"));
//	_ftprintf(tmp_xml, _T("%s"), H_TEXT(xmlgen.GetBuffer()));
//	fflush(tmp_xml);
//	fclose(tmp_xml);

	*filepath = CComBSTR(temp_ouput_file).Copy();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::GenerateNavigationInfoFromNodePath(BSTR nodepath, BSTR *filepath)
{
	if( !m_pDataLoader->GetTreeControlXML() )
		return S_FALSE;

	USES_CONVERSION;

	// create a temporary file for the output
	TCHAR temp_ouput_file[_MAX_DIR];
	generate_temp_filename(temp_ouput_file);

	FILE * tmp_xml = _tfopen(temp_ouput_file, _T("w+t"));

	char * data = 0;
	m_pDataLoader->GetXMLForItemChildren(OLE2A(nodepath), data);
	if(data)
	{
		fprintf(tmp_xml, "%s", data);
		delete[] data;
	}

	
	fflush(tmp_xml);
	fclose(tmp_xml);



	*filepath = CComBSTR(temp_ouput_file).Copy();

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::Select(BSTR key)
{
    if (m_pView)
    {	
		USES_CONVERSION;
		
		if(!key)
			return S_OK;
		
		TCHAR * pVal_W = OLE2T(key);
		
		HC_KEY sel_key;
		_stscanf(pVal_W, _T("%p"), &sel_key );
		HSelectionSet* sel_set = (HSelectionSet *)m_pView->GetSelection();
		sel_set->DeSelectAll();
		sel_set->Select(sel_key, 0, 0);
		m_pView->Update();
    }
    
    return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SelectFromIdentifier(int identifier)
{
    if (m_pView)
    {	
		HC_KEY sel_key;
		if (m_pView->GetModel()->GetStreamFileTK()->IndexToKey(identifier, sel_key) != TK_NotFound)
		{
			if (sel_key != -1)
			{	    
				
				HSelectionSet* sel_set = (HSelectionSet *)m_pView->GetSelection();
				sel_set->DeSelectAll();
				sel_set->Select(sel_key, 0, 0);
			}
			
			m_pView->Update();
		}
    }
    
    return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SelectFromPath(BSTR path)
{
    if (m_pView)
    {	

	    char path_char[4096];
	    ConvertToChar(path_char,path,4096);
	    if (strcmp(path_char,"") != 0)
	    {	    
	    ModelStructureObject *mso = m_pDataLoader->FindModelStructureObject(m_pDataLoader->GetModelStructureObjectTree(), path_char+1);
	    if (mso && mso->GetTypePointer() && mso->GetTypePointer()->GetSelectable())
	    {
		if (mso->m_Identifier != -1 || mso->m_IdentifierList)
		{		
		    if (mso->m_Identifier != -1)
		    {		    
			HC_KEY sel_key;
			if (m_pView->GetModel()->GetStreamFileTK()->IndexToKey(mso->m_Identifier, sel_key) != TK_NotFound)
			{
			    if (sel_key != -1)
			    {	    
				
				HSelectionSet* sel_set = (HSelectionSet *)m_pView->GetSelection();
				sel_set->DeSelectAll();
				sel_set->Select(sel_key, 0, 0);
			    }
			    
			    m_pView->Update();
			}
		    }
		    else
		    {
			vlist_t *childrenlist = mso->m_IdentifierList;	
 			HSelectionSet* sel_set = (HSelectionSet *)m_pView->GetSelection();
			sel_set->DeSelectAll();			
			START_LIST_ITERATION(char, childrenlist)
			    HC_KEY sel_key;
 					
			int identifier = atoi(temp);
			if (m_pView->GetModel()->GetStreamFileTK()->IndexToKey(identifier, sel_key) != TK_NotFound)
			{
			    if (sel_key != -1)
			    {	    
				
				HSelectionSet* sel_set = (HSelectionSet *)m_pView->GetSelection();
				sel_set->Select(sel_key, 0, 0);
			    }
			    
			    m_pView->Update();
			}
			END_LIST_ITERATION(childrenlist);			
			
		    }
		}
		else	
		{
		    HSelectionSet* sel_set = (HSelectionSet *)m_pView->GetSelection();		    
		    sel_set->DeSelectAll();
		    mso->SelectAllChildItemsRecursive(m_pView);		
		    m_pView->Update();
		    
		}
		
	    }
	 }
    }
    
    return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::FilterIdentifier(int oldidentifier, int *newidentifier)
{
    if (m_pView)
    {	
//	*newidentifier = m_pDataLoader->FilterIdentifier(oldidentifier, m_ModelStructureFilter);
    }
    
    return S_OK;
}




STDMETHODIMP CHoops3dStreamCtrl::put_AllowEntitySelection(BOOL newVal)
{

	m_bAllowEntitySelection = (newVal != 0);
    	SetDirty(true);
 	if (m_pView)	
	    m_pView->GetSelection()->SetAllowEntitySelection(m_bAllowEntitySelection);
	

	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_AllowEntitySelection(BOOL *pVal)
{
 	if (m_pView)
	    m_bAllowEntitySelection = m_pView->GetSelection()->GetAllowEntitySelection();
	    
	    *pVal = m_bAllowEntitySelection;
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::ShowCuttingPlane(BSTR name, BOOL onoff)
{
    char name_char[4096];
    ConvertToChar(name_char,name,4096);

    if (onoff && !m_pView->GetCuttingPlanesExist(name_char))
    {
		HC_KEY key = HUtilityGeometryCreation::CreateCuttingPlane(m_pView,name_char);
		HUtilityGeomHandle::SetupCuttingPlaneManipulator(key, m_pView);
		m_pView->Update();	
    }
    else
    {
		HC_Open_Segment_By_Key(m_pView->GetCuttingPlanesKey());
		HC_Open_Segment(name_char);
		HUtilityGeomHandle::ClearAllHandles(0);
		if (!(GetAsyncKeyState(VK_SHIFT) & 32768))
			HC_Flush_Contents ("...", "geometry");
		HC_Close_Segment();
		HC_Close_Segment();
		m_pView->Update();
    }

    HUtilityGeometryCreation::AdjustCuttingPlaneRendering(m_pView);
    return S_OK;
   
}

STDMETHODIMP CHoops3dStreamCtrl::get_CuttingPlaneStatus(BSTR name, BOOL *pVal)
{
	USES_CONVERSION;
	if(m_pView->GetCuttingPlanesExist(OLE2CA(name)))
		*pVal = TRUE;
	else
		*pVal = FALSE;

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::put_BhvContinuousPlay(BOOL newVal)
{

	m_bContinuousPlay = (newVal != 0);
     	SetDirty(true);
 	if (m_pView)	
		m_pView->GetModel()->GetBhvBehaviorManager()->SetContinuousPlay(m_bContinuousPlay);
 	

	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_BhvContinuousPlay(BOOL *pVal)
{
 	if (m_pView)
	   m_bContinuousPlay = m_pView->GetModel()->GetBhvBehaviorManager()->GetContinuousPlay();
	 
	*pVal = m_bContinuousPlay;
	return S_OK;
}


static void projmode_enum2char(ProjMode proj_mode, char * ret_str)
{
	if( proj_mode == ProjUnknown )
		strcpy(ret_str, "unknown");
	else if( proj_mode == ProjPerspective )
		strcpy(ret_str, "perspective");
	else if( proj_mode == ProjOrthographic )
		strcpy(ret_str, "orthographic");
	else if( proj_mode == ProjStretched )
		strcpy(ret_str, "stretched");
	else
	{
		// should never be here
		strcpy(ret_str, "");
	}
}

static ProjMode projmode_tchar2enum(TCHAR *proj_mode)
{
	if( !_tcsicmp(proj_mode, _T("unknown")) ) 
		return ProjUnknown;
	else if( !_tcsicmp(proj_mode,_T("perspective")) )
		return ProjPerspective;
	else if( !_tcsicmp(proj_mode,_T("orthographic")) )
		return ProjOrthographic;
	else if( !_tcsicmp(proj_mode,_T("stretched")) )
		return ProjStretched;
	else
	{
		// should never be here
		return ProjOrthographic;
	}
}

STDMETHODIMP CHoops3dStreamCtrl::get_ProjectionMode(BSTR *pVal)
{
	char str_proj_mode[MVO_BUFFER_SIZE];
	if(m_pView)
		projmode_enum2char(m_pView->GetProjMode(), str_proj_mode);
	else
		strcpy(str_proj_mode, "");

 	*pVal = CComBSTR(str_proj_mode).Copy();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::put_ProjectionMode(BSTR newVal)
{
	USES_CONVERSION;
	ProjMode mode = projmode_tchar2enum(OLE2T(newVal));
	m_pView->SetProjMode(mode);
	m_pView->Update();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::Run(BSTR command)
{
	USES_CONVERSION;
	if( !stricmp(OLE2A(command), "FILEOPEN") ) 
		ShowFileOpenDialog();
	else if( !stricmp(OLE2A(command), "PRINT") ) 
		ShowPrintDialog();
	else if( !stricmp(OLE2A(command), "SELECT") ) 
		SetOperator(A2OLE("HOpSelectAperture"));

	else if( !stricmp(OLE2A(command), "ORBIT") ) 
		SetOperator(A2OLE("HOpCameraManipulate"));
	else if( !stricmp(OLE2A(command), "PAN") ) 
		SetOperator(A2OLE("HOpCameraPan"));
	else if( !stricmp(OLE2A(command), "ZOOM") ) 
		SetOperator(A2OLE("HOpCameraZoom"));
	else if( !stricmp(OLE2A(command), "ZOOMWINDOW") ) 
		SetOperator(A2OLE("HOpCameraZoomBox"));
	else if( !stricmp(OLE2A(command), "WALK") ) 
		SetOperator(A2OLE("HOpCameraWalk"));
	else if( !stricmp(OLE2A(command), "MEASURE") ) 
	{
		m_pView->SetDefaultSelectionProximity(0.1f);
		SetOperator(A2OLE("HOpMarkupMeasure"));
	}


	else if( !stricmp(OLE2A(command), "SHADED") )
		SetRenderMode(A2OLE("shaded"));
	else if( !stricmp(OLE2A(command), "WIREFRAME") )
		SetRenderMode(A2OLE("wireframe"));
	else if( !stricmp(OLE2A(command), "HIDDENLINE") )
		SetRenderMode(A2OLE("hidden line"));
	else if( !stricmp(OLE2A(command), "SHADED_WITH_EDGES") )
		SetRenderMode(A2OLE("gouraud with edges"));

	else if( !stricmp(OLE2A(command), "FITWORLD") )
		FitWorld();
	else if( !stricmp(OLE2A(command), "BACK") )
	{
		if(m_pView)
		{
 			m_pView->GetUndoManager()->Undo();
		}
	}
	else if( !stricmp(OLE2A(command), "FORWARD") )
	{
		if(m_pView)
			m_pView->GetUndoManager()->Redo();
	}
	else if( !stricmp(OLE2A(command), "HOME") )
	{
		if(m_pView)
			m_pView->ZoomToInitialCamera();
	}

	else if( !stricmp(OLE2A(command), "BHV_PLAY") )
		BhvPlay();
	else if( !stricmp(OLE2A(command), "BHV_PAUSE") )
		BhvPause();
	else if( !stricmp(OLE2A(command), "BHV_STOP") )
		BhvRewind();

	else if( !stricmp(OLE2A(command), "VIEW_XY") )
		SetCameraToPlaneXY();
	else if( !stricmp(OLE2A(command), "VIEW_YX") )
		SetCameraToPlaneYX();
	else if( !stricmp(OLE2A(command), "VIEW_XZ") )
		SetCameraToPlaneXZ();
	else if( !stricmp(OLE2A(command), "VIEW_ZX") )
		SetCameraToPlaneZX();
	else if( !stricmp(OLE2A(command), "VIEW_YZ") )
		SetCameraToPlaneYZ();
	else if( !stricmp(OLE2A(command), "VIEW_ZY") )
		SetCameraToPlaneZY();
	else if( !stricmp(OLE2A(command), "VIEW_ISOMETRIC") )
		SetCameraToIsometric();

	else if( !stricmp(OLE2A(command), "EXIT") )
		exit(0);


	return S_OK;
}




STDMETHODIMP CHoops3dStreamCtrl::get_ModelStructureTypeList(BSTR *pVal)
{
    if (m_pDataLoader)
    {
	char typestring[4096];
	strcpy(typestring,"");
	vlist_t * typelist = m_pDataLoader->GetModelStructureTypeList();
	START_LIST_ITERATION(ModelStructureType, typelist)
	    strcat(typestring,temp->GetName());
	    if (vlist_peek_cursor_next(typelist))
		strcat(typestring,",");
	END_LIST_ITERATION(typelist)	
	SysReAllocStringLen(pVal,0,strlen(typestring));
	mbstowcs(*pVal,typestring,strlen(typestring));
    }
    else
        *pVal = SysAllocString(L"empty");
 	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::KeyToIndex(BSTR key, int* pIndex)
{
	*pIndex = -1;
    if (m_pView)
    {	
		USES_CONVERSION;
		
		if(!key)
			return S_OK;
		
		TCHAR * pVal_W = OLE2T(key);
		
		HC_KEY sel_key;
		_stscanf(pVal_W, _T("%p"), &sel_key );

		if (m_pView->GetModel()->GetStreamFileTK()->KeyToIndex(sel_key, *pIndex) == TK_NotFound)
			return S_FALSE;
    }
    
    return S_OK;
}
 

STDMETHODIMP CHoops3dStreamCtrl::put_ModelStructureFilter(BSTR newVal)
{
    char temp[4096];
    ConvertToChar(temp,newVal,256);
    ((HMySelectionSet *)m_pView->GetSelection())->SetModelStructureFilter(temp);
    return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::GetPathFromIndex(int index, BSTR *pPath)
{
	if(index == ~0 || *pPath == 0)
		return S_OK;
	char path[MVO_BUFFER_SIZE];

	if( m_pDataLoader )
	{
		m_pDataLoader->GetPathFromIdentifier(index, path);
	 	*pPath = CComBSTR(path).Copy();
	}

	return S_OK;
}



STDMETHODIMP CHoops3dStreamCtrl::put_SoftwareRendering(BOOL newVal)
{
    m_bSoftwareRendering = BOOL2bool(newVal);
	
    if (m_pView)
    {    
		m_pView->ReconfigureView (m_hWnd, NULL,0);
		
		if (newVal)
		{	
			char driver_options[4096];
			long debug_flags = 0;;
			debug_flags |= DEBUG_FORCE_SOFTWARE;
			
			sprintf (driver_options, "debug = %u", debug_flags);
			
			HC_Open_Segment_By_Key(m_pView->GetViewKey());
			HC_Set_Driver_Options(driver_options);
			HC_Close_Segment();
		}
    }
    return S_OK;
}
		

STDMETHODIMP CHoops3dStreamCtrl::get_SoftwareRendering(BOOL *pVal)
{
	*pVal = m_bSoftwareRendering;
	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::get_SmoothTransitionMode(BOOL *pVal)
{
	if(m_pView)
		*pVal = bool2BOOL(m_pView->GetSmoothTransition());

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::put_SmoothTransitionMode(BOOL newVal)
{
	if (m_pView)
	{
		m_pView->SetSmoothTransition(BOOL2bool(newVal));
		m_pView->Update();
	}

	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::put_DataNavigatorMode(BOOL newVal)
{
 	m_bDataNavigatorMode = BOOL2bool(newVal);
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::get_DataNavigatorMode(BOOL *pVal)
{
	if(m_pView)
		*pVal = bool2BOOL(m_bDataNavigatorMode);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::get_UndoAvailable(BOOL *pVal)
{
	if(m_pView)
		*pVal = m_pView->GetUndoManager()->Undo(1,true);

	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::get_RedoAvailable(BOOL *pVal)
{
	if(m_pView)
		*pVal = m_pView->GetUndoManager()->Redo(1,true);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetSelectionFaceColor(float r, float g, float b, float a)
{
	if(m_pView)
	{
		HSelectionSet* sel_set = m_pView->GetSelection();
		if(sel_set)
		{
			HPixelRGBA color;
			color.Setf(r, g, b, a);
			sel_set->SetSelectionFaceColor(color);
		}
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetSelectionEdgeColor(float r, float g, float b, float a)
{
	if(m_pView)
	{
		HSelectionSet* sel_set = m_pView->GetSelection();
		if(sel_set)
		{
			HPixelRGBA color;
			color.Setf(r, g, b, a);
			sel_set->SetSelectionEdgeColor(color);
		}
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::SetSelectionMarkerColor(float r, float g, float b, float a)
{
	if(m_pView)
	{
		HSelectionSet* sel_set = m_pView->GetSelection();
		if(sel_set)
		{
			HPixelRGBA color;
			color.Setf(r, g, b, a);
			sel_set->SetSelectionMarkerColor(color);
		}
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::AddFileType(BSTR filetype)
{

	char filetype_char[4096];
	ConvertToChar(filetype_char,filetype,4096);

	char *ft = new char[strlen(filetype_char)+1];
	strcpy(ft, filetype_char);
	vlist_add_last(m_FileTypeList, ft);
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::put_ConfigFile(BSTR newVal)
{
	if (newVal)
	{
 		ConvertToChar(m_ConfigFile,newVal,4096); 		 
	} 	
	return S_OK;
	
}
STDMETHODIMP CHoops3dStreamCtrl::put_DefaultConfigFile(BSTR newVal)
{
	if (newVal)
	{
 		ConvertToChar(m_DefaultConfigFile,newVal,4096); 		 
	} 	
	return S_OK;
	
}

STDMETHODIMP CHoops3dStreamCtrl::put_FramerateType(BSTR newVal)
{
	if (newVal)
	{
		char text[4096];
 		ConvertToChar(text,newVal,4096); 
		if (strcmp(text, "FramerateFixed") == 0)
			m_FramerateType = FramerateFixed;
		else if (strcmp(text, "FramerateTarget") == 0)
			m_FramerateType = FramerateTarget;
		else
			m_FramerateType = FramerateOff;

	} 	
	return S_OK;
	
}

STDMETHODIMP CHoops3dStreamCtrl::get_FramerateType(BSTR *pVal)
{
	return S_OK;
	
}


STDMETHODIMP CHoops3dStreamCtrl::put_CullingThreshold(int newVal)
{
	m_CullingThreshold = newVal;
	if (m_pView)
		m_pView->SetCullingThreshold(newVal);
	return S_OK;

}

STDMETHODIMP CHoops3dStreamCtrl::get_CullingThreshold(int *pVal)
{
	return S_OK;
	
}
STDMETHODIMP CHoops3dStreamCtrl::put_MaximumThreshold(int newVal)
{
	m_MaximumThreshold = newVal;
	return S_OK;

}

STDMETHODIMP CHoops3dStreamCtrl::get_MaximumThreshold(int *pVal)
{
	return S_OK;
	
}

STDMETHODIMP CHoops3dStreamCtrl::put_FrameRate(float newVal)
{
	m_FrameRate = newVal;
	if (m_pView)
		SetFramerateMode(true);
 	return S_OK;

}

STDMETHODIMP CHoops3dStreamCtrl::get_FrameRate(float *pVal)
{
	return S_OK;
	
}


STDMETHODIMP CHoops3dStreamCtrl::get_DriverType(BSTR *newVal)
{
 	return S_OK;
	
}

STDMETHODIMP CHoops3dStreamCtrl::put_DriverType(BSTR newVal)
{
	if (newVal)
	{		
 		ConvertToChar(m_DriverType,newVal,4096); 
	} 	
	return S_OK;
	
}


STDMETHODIMP CHoops3dStreamCtrl::put_TransparencyOptions(BSTR newVal)
{
	if (newVal)
	{		
 		ConvertToChar(m_TransparencyOptions,newVal,4096); 
	} 	
	if (m_pView)
		m_pView->SetTransparency(m_TransparencyOptions,true);
	return S_OK;
	
}


STDMETHODIMP CHoops3dStreamCtrl::get_TransparencyOptions(BSTR *newVal)
{
 	return S_OK;
	
}


STDMETHODIMP CHoops3dStreamCtrl::get_ConfigFile(BSTR *newVal)
{
 	return S_OK;
	
}
STDMETHODIMP CHoops3dStreamCtrl::get_DefaultConfigFile(BSTR *newVal)
{
 	return S_OK;
	
}

STDMETHODIMP CHoops3dStreamCtrl::ShowOptionsDialog()
{
    
    
    HPixelRGBA col;
    CAppearanceDlg appDlg;
    HSelectionSet* sel_set = m_pView->GetSelection();

	col.Set(0,0,0,0);

    if(sel_set)
    {	
		sel_set->GetSelectionFaceColor(col);
    }
    
    
    appDlg.m_bottom_color = RGB(m_window_bottom_color.x*255.0f, m_window_bottom_color.y*255.0f, m_window_bottom_color.z*255.0f);
    appDlg.m_top_color = RGB(m_window_top_color.x*255.0f, m_window_top_color.y*255.0f, m_window_top_color.z*255.0f);
    appDlg.m_selection_color = RGB(col.r(),col.g(), col.b());
    appDlg.m_bForceSoftware = m_bSoftwareRendering;
    
    if (strcmp(m_DefaultConfigFile,"")!= 0)
    {   
	char text[4096];
	vlist_t *defaultconfiglist = new_vlist(malloc,free);		
	if (ReadConfigFile(m_DefaultConfigFile, defaultconfiglist) == S_OK)
	{	    
 	    HPoint p1;
	    if (GetConfigProperty("SelectionColor", "polygons", text, defaultconfiglist))
	    {
		float r,g,b,a;
		 HUtilityXMLParser::GetRBGA(text, r,g,b,a);
	         appDlg.m_default_selection_color = RGB(r*255.0f,g*255.0f,b*255.0f);
	    }
	    if (GetConfigProperty("BackgroundColor", "top", text, defaultconfiglist))
	    {
	         HUtilityXMLParser::GetFloatPoint(text, p1);
		appDlg.m_default_top_color = RGB(p1.x*255.0f, p1.y*255.0f, p1.z*255.0f);
	    }
	    if (GetConfigProperty("BackgroundColor", "bottom", text, defaultconfiglist))
	    {
	         HUtilityXMLParser::GetFloatPoint(text, p1);
		 appDlg.m_default_bottom_color = RGB(p1.x*255.0f, p1.y*255.0f, p1.z*255.0f);
	    }
	    if (GetConfigProperty("SoftwareRendering", "Value", text, defaultconfiglist))
	    {	       
		appDlg.m_bDefaultForceSoftware = BOOL2bool(atoi(text));
	    }

	}
	START_LIST_ITERATION(HUtilityXMLTag, defaultconfiglist);
	    delete temp;
	END_LIST_ITERATION(defaultconfiglist);
	delete_vlist(defaultconfiglist);
    }

    if (appDlg.DoModal() == IDOK)
    {
	m_window_top_color.Set(static_cast<float>(GetRValue(appDlg.m_top_color))/255.0f,
	    static_cast<float>(GetGValue(appDlg.m_top_color))/255.0f,
	    static_cast<float>(GetBValue(appDlg.m_top_color))/255.0f);
	m_window_bottom_color.Set(static_cast<float>(GetRValue(appDlg.m_bottom_color))/255.0f,
	    static_cast<float>(GetGValue(appDlg.m_bottom_color))/255.0f,
	    static_cast<float>(GetBValue(appDlg.m_bottom_color))/255.0f);
	m_pView->SetWindowColor(m_window_top_color, m_window_bottom_color);
	SetSelectionEdgeColor(static_cast<float>(GetRValue(appDlg.m_selection_color))/255.0,
	    static_cast<float>(GetGValue(appDlg.m_selection_color))/255.0f,
	    static_cast<float>(GetBValue(appDlg.m_selection_color))/255.0f,0.0f);
	SetSelectionFaceColor(static_cast<float>(GetRValue(appDlg.m_selection_color))/255.0,
	    static_cast<float>(GetGValue(appDlg.m_selection_color))/255.0f,
	    static_cast<float>(GetBValue(appDlg.m_selection_color))/255.0f,0.0f);
	SetSelectionMarkerColor(static_cast<float>(GetRValue(appDlg.m_selection_color))/255.0,
	    static_cast<float>(GetGValue(appDlg.m_selection_color))/255.0f,
	    static_cast<float>(GetBValue(appDlg.m_selection_color))/255.0f,0.0f);
 	put_SoftwareRendering(appDlg.m_bForceSoftware);
	HC_Control_Update_By_Key (m_pView->GetViewKey(), "redraw everything");
	m_pView->Update();	
	SerializeConfiguration();
	

    }
    return S_OK;
    
    
    
}
  

bool CHoops3dStreamCtrl::ReadConfigFile(char *ConfigFile, struct vlist_s *ConfigurationList)
{


	START_LIST_ITERATION(HUtilityXMLTag, ConfigurationList)
	    delete temp;
	END_LIST_ITERATION(ConfigurationList);
	vlist_flush(ConfigurationList);


	int size = 10000;
 	FILE *fp;

	char *buffer = new char[size];
 	int c = 0;
	fp=fopen(ConfigFile, "r");
	if (!fp)
	{
	    delete [] buffer;
	    return S_FALSE;
	}
	while (1)
	{
		int rr = fread( &buffer[c], 1, 1, fp);
		if (!rr)
			break;
 		c++;
		if (c >=size)
		{
			size+=1000;
			char *temp = new char[size];
			memcpy(temp, buffer, c);
			delete [] buffer;
			buffer = temp;
		}
 
	}
	fclose(fp);
	buffer[c + 1] = 0;
	
	HUtilityXMLParser xp;
 	xp.SetupParseBuffer(buffer);
 	xp.SetTagCallback(0, CHoops3dStreamCtrl::XMLCallback, ConfigurationList);
	xp.ProcessXMLData();
	
 	delete [] buffer;

	return S_OK;
	
}

bool CHoops3dStreamCtrl::GetConfigProperty(char *tagname, char *propertyname, char *result, vlist_s *configurationlist)
{
	vlist_t *clist;
	if (!configurationlist)
	    clist = m_ConfigurationList;
	else
	    clist = configurationlist;
	
	START_LIST_ITERATION(HUtilityXMLTag, clist)
	    if (strcmp(tagname, temp->GetTagname()) == 0)
	    {
		return (temp->GetProperty(propertyname, result));
  		    
	    }
 	END_LIST_ITERATION(clist);
	return false;
}

HUtilityXMLTag * CHoops3dStreamCtrl::GetConfigTag(char *tagname)
{
	START_LIST_ITERATION(HUtilityXMLTag, m_ConfigurationList)
	    if (strcmp(tagname, temp->GetTagname()) == 0)
		return temp;	   
 	END_LIST_ITERATION(m_ConfigurationList);
	return 0;
}


STDMETHODIMP CHoops3dStreamCtrl::ConfigureFromFile()
{
    char text[4096];
    HPoint p1,p2;
    float r,g,b,a;
    if (strcmp(m_ConfigFile,"") != 0 && ReadConfigFile(m_ConfigFile, m_ConfigurationList) == S_OK)
    {
 	if (GetConfigProperty("SoftwareRendering", "Value", text))
	    put_SoftwareRendering(atoi(text));
	
	if (GetConfigProperty("SelectionColor", "polygons", text))
	{	
	    HUtilityXMLParser::GetRBGA(text, r,g,b,a);
	    SetSelectionFaceColor(r,g,b,a);
	}
	
	if (GetConfigProperty("SelectionColor", "lines", text))
	{	
	    HUtilityXMLParser::GetRBGA(text, r,g,b,a);
	    SetSelectionEdgeColor(r,g,b,a);
	}
	
	if (GetConfigProperty("SelectionColor", "markers", text))
	{	
	    HUtilityXMLParser::GetRBGA(text, r,g,b,a);
	    SetSelectionMarkerColor(r,g,b,a);
	}
	
	if (GetConfigProperty("BackgroundColor", "top", text))	
	    HUtilityXMLParser::GetFloatPoint(text, p1);
	else
	    p1.Set(0,0,0);

	if (GetConfigProperty("BackgroundColor", "bottom", text))
	    HUtilityXMLParser::GetFloatPoint(text, p2);
	else
	    p2.Set(1,1,1);

 	if (!GetConfigProperty("BackgroundColor", "percentage", text))
 	    strcpy(text,"100");
	SetBackgroundColors(p1.x,p1.y,p1.z, p2.z, p2.y, p2.z,atoi(text));

	
	if (GetConfigProperty("AmbientColor", "Value", text))
	{
	    HUtilityXMLParser::GetFloatPoint(text, p1);
	    SetAmbientColor(p1.x,p1.y,p1.z);
	}

	if (GetConfigProperty("ShadowMode", "Value", text))
	    SetShadowMode(atoi(text));
	
	if (GetConfigProperty("AxisTriadMode", "Value", text))
	    put_AxisMode(atoi(text));
	
	if (GetConfigProperty("SmoothTransitionMode", "Value", text))	    
	    put_SmoothTransitionMode(atoi(text));

	if (GetConfigProperty("DataNavigatorMode", "Value", text))	    
	    put_DataNavigatorMode(atoi(text));
	
	
	START_LIST_ITERATION(char, m_FileTypeList)
	    delete temp;
	END_LIST_ITERATION(m_FileTypeList);
	vlist_flush(m_FileTypeList);
	
	HUtilityXMLTag *tag = GetConfigTag("FileExtensions");
	if (tag)
	{	
	    tag->StartListItemsQuery();
	    
	    while (1)
	    {
		char *text;
 		if (!tag->GetNextListItem(&text))
			break;
 		char *text2 = new char[strlen(text)+1];
		strcpy(text2,text+1);
		text2[strlen(text2) - 1] = 0;
		vlist_add_last(m_FileTypeList, text2);
	    }
	}
    }
    

    return S_OK;
        
}

void CHoops3dStreamCtrl::SerializeConfiguration()
{
    if (strcmp(m_ConfigFile,"")!=0)
    {    
	char text[4096];
	HUtilityXMLGenerator xmlgen;
	xmlgen.Reset();
	
 	START_LIST_ITERATION(HUtilityXMLTag, m_ConfigurationList)
	    if (strcmp(temp->GetTagname(), "Configuration") == 0)
		temp->SetOpen(true);
	    else
		temp->SetOpen(false);   
	    if (strcmp(temp->GetTagname(), "SoftwareRendering") == 0)
 		temp->AddPropertyInt("Value", m_bSoftwareRendering);
	    else if (strcmp(temp->GetTagname(), "SelectionColor") == 0)
	    {
		HSelectionSet* sel_set = m_pView->GetSelection();
		HPixelRGBA col;
		if(sel_set)
		{	
		    sel_set->GetSelectionFaceColor(col);
		    sprintf(text, "%1.1f %1.1f %1.1f %1.1f", col.r() /255.0f, col.g() /255.0f, col.b() /255.0f, col.a() /255.0f);
		    temp->AddProperty("polygons", text, true);
		    sel_set->GetSelectionEdgeColor(col);
		    sprintf(text, "%1.1f %1.1f %1.1f %1.1f", col.r() /255.0f, col.g() /255.0f, col.b() /255.0f, col.a() /255.0f);
		    temp->AddProperty("lines", text, true);
		    sel_set->GetSelectionMarkerColor(col);
		    sprintf(text, "%1.1f %1.1f %1.1f %1.1f", col.r() /255.0f, col.g() /255.0f, col.b() /255.0f, col.a() /255.0f);
		    temp->AddProperty("markers", text, true);
		}
	    }
	    else if (strcmp(temp->GetTagname(), "BackgroundColor") == 0)
	    {
		HPoint top, bottom;
		int percentage;
		m_pView->GetWindowColor(top, bottom, percentage);
		sprintf(text, "%1.1f %1.1f %1.1f", top.x, top.y, top.z);
		temp->AddProperty("top", text, true);
		sprintf(text, "%1.1f %1.1f %1.1f", bottom.x, bottom.y, bottom.z);
		temp->AddProperty("bottom", text, true);
		temp->AddPropertyInt("percentage", percentage);
	    }
	    else if (strcmp(temp->GetTagname(), "AmbientColor") == 0)
	    {
		HPoint top; 	 
		sprintf(text, "%1.1f %1.1f %1.1f", m_ambient_color.x, m_ambient_color.y, m_ambient_color.z);
		temp->AddProperty("Value", text, true);
	    }
	    else if (strcmp(temp->GetTagname(), "ShadowMode") == 0)
	    {
		if (m_pView->GetShadowMode() != HShadowNone)	    
		    temp->AddPropertyInt("Value", 1);
		else
		    temp->AddPropertyInt("Value", 0);
	    }
	    else if (strcmp(temp->GetTagname(), "AxisTriadMode") == 0)	    	 
	    {
		if (m_StoredAxisMode)
		    temp->AddPropertyInt("Value", 1);
		else
		    temp->AddPropertyInt("Value", 0);
	    }
	    else if (strcmp(temp->GetTagname(), "SmoothTransitionMode") == 0)	    	 
	    {
		temp->AddPropertyInt("Value", m_pView->GetSmoothTransition());
	    }
	    else if (strcmp(temp->GetTagname(), "DataNavigatorMode") == 0)	    	 
	    {
		temp->AddPropertyInt("Value", m_bDataNavigatorMode);
	    }
	    else if (strcmp(temp->GetTagname(), "FileExtensions") == 0)	    	 
	    {
		HUtilityXMLTag *tag = temp;
		
		tag->CleanListItems();
		START_LIST_ITERATION(char, m_FileTypeList);
		    sprintf(text, "\"%s\"", temp);
		    tag->AddListItem(text);
		END_LIST_ITERATION(m_FileTypeList);
		    
	    }

  	    xmlgen.AddTag(temp);
	END_LIST_ITERATION(m_ConfigurationList);
	GetConfigTag("Configuration");
	xmlgen.CloseTag(GetConfigTag("Configuration"));
	
	FILE *fhandle = fopen(m_ConfigFile,"wb");
	fseek(fhandle,0,SEEK_SET);
	fwrite(xmlgen.GetBuffer(),1,xmlgen.GetBufferSize(), fhandle);
	fclose(fhandle);    
    }



}
void *CHoops3dStreamCtrl::XMLCallback(HUtilityXMLTag *xt, bool open, void *m_pExtraData)
{

    HUtilityXMLTag *tag;
    if (!open)
    {
	tag = xt->Clone();
	if (strcmp(tag->GetTagname(), "Configuration") == 0)
		vlist_add_first((vlist_t *)m_pExtraData, tag);
	else
	    vlist_add_last((vlist_t *)m_pExtraData, tag);
    }

    return 0;    
}

STDMETHODIMP CHoops3dStreamCtrl::get_HasModelStructureInfo(BOOL *pVal)
{
	if( m_pDataLoader->GetTreeControlXML() )
		*pVal = TRUE;
	else
		*pVal = FALSE;

	return S_OK;
}

/* New functions! */
/* HC_Insert function */
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Circle(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, long *retkey)
{
 	if (m_pView)
	{
	    HPoint p1(p1_x, p1_y, p1_z), p2(p2_x, p2_y, p2_z), p3(p3_x, p3_y, p3_z);
 	    *retkey = LastKey = HC_KInsert_Circle(&p1,&p2,&p3);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Circle_By_Radius(float c_x, float c_y, float c_z, float radius, float n_x, float n_y, float n_z, long *retkey)
{
	if (m_pView)
	{
	    HPoint c(c_x, c_y, c_z), n(n_x, n_y, n_z);
 	    *retkey = LastKey = HC_KInsert_Circle_By_Radius(&c,radius,&n);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Circular_Arc(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, long *retkey)
{
 	if (m_pView)
	{
	    HPoint p1(p1_x, p1_y, p1_z), p2(p2_x, p2_y, p2_z), p3(p3_x, p3_y, p3_z);
 	    *retkey = LastKey = HC_KInsert_Circular_Arc(&p1,&p2,&p3);
	} 	    
   
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Circular_Chord(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, long *retkey)
{
 	if (m_pView)
	{
	    HPoint p1(p1_x, p1_y, p1_z), p2(p2_x, p2_y, p2_z), p3(p3_x, p3_y, p3_z);
 	    *retkey = LastKey = HC_KInsert_Circular_Chord(&p1,&p2,&p3);
	} 	    
   
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Circular_Wedge(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, long *retkey)
{
 	if (m_pView)
	{
	    HPoint p1(p1_x, p1_y, p1_z), p2(p2_x, p2_y, p2_z), p3(p3_x, p3_y, p3_z);
 	    *retkey = LastKey = HC_KInsert_Circular_Wedge(&p1,&p2,&p3);
	} 	    
   
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Cutting_Plane(float a, float b, float c, float d, long *retkey)
{
 	if (m_pView)
	{
  	    *retkey = LastKey = HC_KInsert_Cutting_Plane(a,b,c,d);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Cutting_Section(int count, VARIANT *planes_var, long *retkey)
{
 	if (m_pView)
	{
		int dummy;
		float *planes = 0;

		GetFloatArrayFromVariant(planes_var, &planes, dummy); 
  	    *retkey = LastKey = HC_KInsert_Cutting_Section(count,planes);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Cylinder(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float r, BSTR cap, long *retkey)
{
 	if (m_pView)
	{
	    char cap_char[4096];
	    ConvertToChar(cap_char,cap,4096);
	    HPoint p1(p1_x, p1_y, p1_z), p2(p2_x, p2_y, p2_z);
  	    *retkey = LastKey = HC_KInsert_Cylinder(&p1, &p2, r, cap_char);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Distant_Light(float di, float dj, float dk, long *retkey)
{
 	if (m_pView)
	{
  	    *retkey = LastKey = HC_KInsert_Distant_Light(di,dj,dk);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Ellipse(float c_x, float c_y, float c_z, float major_x, float major_y, float major_z, float minor_x, float minor_y, float minor_z, long *retkey)
{
 	if (m_pView)
	{
	    HPoint p1(c_x, c_y, c_z), p2(major_x, major_y, major_z), p3(minor_x, minor_y, minor_z);
 	    *retkey = LastKey = HC_KInsert_Ellipse(&p1,&p2,&p3);
	} 	    
   
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Elliptical_Arc(float c_x, float c_y, float c_z, float major_x, float major_y, float major_z, float minor_x, float minor_y, float minor_z, float start, float end, long *retkey)
{
 	if (m_pView)
	{
	    HPoint p1(c_x, c_y, c_z), p2(major_x, major_y, major_z), p3(minor_x, minor_y, minor_z);
 	    *retkey = LastKey = HC_KInsert_Elliptical_Arc(&p1,&p2,&p3,start, end);
	} 	    
   
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Grid(BSTR type, float o_x, float o_y, float o_z, float ref1_x, float ref1_y, float ref1_z, float ref2_x, float ref2_y, float ref2_z, int count1, int count2, long *retkey)
{
 	if (m_pView)
	{
	    char type_char[4096];
	    ConvertToChar(type_char,type,4096);
	    HPoint org(o_x, o_y, o_z), ref1(ref1_x, ref1_y, ref1_z), ref2(ref2_x, ref2_y, ref2_z);
 	    *retkey = LastKey = HC_KInsert_Grid(type_char, &org, &ref1, &ref2, count1, count2);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Image(float x, float y, float z, BSTR format, int width, int height, VARIANT *pixeldata_var, long *retkey)
{
 	if (m_pView)
	{
	    char format_char[4096];
	    ConvertToChar(format_char,format,4096);
	    char *pixeldata;
	    int pnum;
 	    GetByteArrayFromVariant(pixeldata_var, &pixeldata, pnum); 
	    *retkey = LastKey = HC_KInsert_Image(x,y,z, format_char,width, height, pixeldata);
	} 	    
   
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Ink(float x, float y, float z, long *retkey)
{
 	if (m_pView)
	{
  	    *retkey = LastKey = HC_KInsert_Ink(x,y,z);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Line(float xa, float ya, float za,float xb, float yb, float zb, long *retkey)
{
 	if (m_pView)
	{
  	    *retkey = LastKey = HC_KInsert_Line(xa,ya,za,xb,yb,zb);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Local_Light(float x, float y, float z, long *retkey)
{
 	if (m_pView)
	{
  	    *retkey = LastKey = HC_KInsert_Local_Light(x,y,z);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Spot_Light(float p_x, float p_y, float p_z, float t_x, float t_y, float t_z, BSTR list, long *retkey)
{
 	if (m_pView)
	{
	    char list_char[4096];
	    ConvertToChar(list_char,list,4096);
	    HPoint p1(p_x, p_y, p_z), p2(t_x, t_y, t_z);
  	    *retkey = LastKey = HC_KInsert_Spot_Light(&p1, &p2, list_char);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Marker(float x, float y, float z, long *retkey)
{
 	if (m_pView)
	{
  	    *retkey = LastKey = HC_KInsert_Marker(x,y,z);
	} 	    
   
 	return S_OK;
}
STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Mesh(int rows, int columns, VARIANT *pointsvar, long *retkey)
{
 	if (m_pView)
	{
	    HPoint *points = 0;
	    int pnum;	
 	    GetPointArrayFromVariant(pointsvar, &points, pnum); 
 	    *retkey = LastKey = HC_KInsert_Mesh(rows, columns, points);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_NURBS_Curve(int degree, int cpcount, VARIANT *cpoints_var, VARIANT *weights_var, VARIANT *knots_var, float start_u, float end_u, long *retkey)
{
 	if (m_pView)
	{
	    HPoint *cpoints = 0;
	    float *weights = 0;
	    float *knots = 0;
	    int dummy;
 	    GetPointArrayFromVariant(cpoints_var, &cpoints, dummy); 
	    GetFloatArrayFromVariant(weights_var, &weights, dummy); 
	    GetFloatArrayFromVariant(knots_var, &knots, dummy); 
	    *retkey = LastKey = HC_KInsert_NURBS_Curve(degree, cpcount, cpoints, weights, knots, start_u, end_u);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_NURBS_Surface(int u_degree, int v_degree, int u_count, int v_count, VARIANT *points_var, VARIANT *weights_var, VARIANT *u_knots_var, VARIANT *v_knots_var, long *retkey)
{
    /*
 	if (m_pView)
	{
	    HPoint *points = 0;
	    float *weights = 0;
	    float *uknots = 0;
	    float *vknots = 0;
  	    GetPointArrayFromVariant(cpoints_var, &cpoints, dummy); 
	    GetFloatArrayFromVariant(weights_var, &weights, dummy); 
	    GetFloatArrayFromVariant(knots_var, &knots, dummy); 
	    HC_Insert_NURBS_Curve(degree, cpcount, cpoints, weights, knots, start_u, end_u);
	} 	    
   */
 	return S_OK;
	
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Polycylinder(int pcount, VARIANT * points_var, int r_count, VARIANT *radii_var, BSTR capping, long *retkey)
{
 	if (m_pView)
	{
	    HPoint *points = 0;
	    int dummy;
	    float *radii = 0;
	    char capping_char[4096];
	    ConvertToChar(capping_char,capping,4096);

 	    GetPointArrayFromVariant(points_var, &points, dummy); 
	    GetFloatArrayFromVariant(radii_var, &radii, dummy); 
	    *retkey = LastKey = HC_KInsert_PolyCylinder(pcount, points, r_count, radii, capping_char);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Polygon(int count, VARIANT *points_var, long *retkey)
{
	if (m_pView)
	{
	    HPoint *points = 0;
	    int dummy;
 	    GetPointArrayFromVariant(points_var, &points, dummy); 
	    *retkey = LastKey = HC_KInsert_Polygon(count, points);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Polyline(int count, VARIANT *points_var, long *retkey)
{
	if (m_pView)
	{
	    HPoint *points = 0;
	    int dummy;
 	    GetPointArrayFromVariant(points_var, &points, dummy); 
	    *retkey = LastKey = HC_KInsert_Polyline(count, points);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Shell(int npoints, VARIANT * pointsvar, int flen, VARIANT *facesvar, long *retkey)
{
 	if (m_pView)
	{
	    HPoint *points = 0;
	    int dummy;
	    int *flist = 0;
 	    GetPointArrayFromVariant(pointsvar, &points, dummy); 
	    GetIntegerArrayFromVariant(facesvar, &flist, dummy); 
	    *retkey = LastKey = HC_KInsert_Shell(npoints, points, flen, flist);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Shell_By_Tristrips(int pcount, VARIANT *points_var, int tlen, VARIANT *tlist_var, int flen, VARIANT *flist_var, long *retkey)
{
	if (m_pView)
	{
	    HPoint *points = 0;
	    int dummy;
	    int *flist = 0;
		int *tlist = 0;

 	    GetPointArrayFromVariant(points_var, &points, dummy); 
		GetIntegerArrayFromVariant(tlist_var, &tlist, dummy); 
	    GetIntegerArrayFromVariant(flist_var, &flist, dummy); 
	    *retkey = LastKey = HC_KInsert_Shell_By_Tristrips(pcount, points, tlen, tlist, flen, flist);
	} 	    
   
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Shell_From_Region(long key1, int region, BSTR options, long *retkey)
{
	if (m_pView)
	{
		char options_char[4096];
	    ConvertToChar(options_char,options,4096);
  	    *retkey = LastKey = HC_KInsert_Shell_From_Region(key1,region,options_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Sphere( float c_x, float c_y, float c_z, float radius, float a_x, float a_y, float a_z, float o_x, float o_y, float o_z, long *retkey)
{
	if (m_pView)
	{
		HPoint c(c_x,c_y,c_z), a(a_x,a_y,a_z), o(o_x,o_y,o_z);
  	    *retkey = LastKey = HC_KInsert_Sphere(&c,radius,&a,&o);
	}

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Text(float x, float y, float z, BSTR text, long *retkey)
{
 	if (m_pView)
	{
		char text_char[4096];
	    ConvertToChar(text_char,text,4096);
  	    *retkey = LastKey = HC_KInsert_Text(x,y,z,text_char);
	} 	    

 	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Text_With_Encoding(float x, float y, float z, BSTR encoding, VARIANT *text, long *retkey)
{
	if (m_pView)
	{
		char encoding_char[4096];
		short *text_char;
		int dummy;

		ConvertToChar(encoding_char,encoding,4096);
		GetShortArrayFromVariant(text,&text_char,dummy);
  	    *retkey = LastKey = HC_KInsert_Text_With_Encoding(x,y,z,encoding_char,(char *)text_char);
	} 	    

 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Insert_Unicode_Text(float x, float y, float z, VARIANT *text, long *retkey)
{
	if (m_pView)
	{
		short *text_char;
		int dummy;

		GetShortArrayFromVariant(text,&text_char,dummy);
  	    *retkey = LastKey = HC_KInsert_Unicode_Text(x,y,z,(unsigned short *) text_char);
	} 	    

 	return S_OK;
}


/*! HOOPS/3dGS Open_Segment function */
STDMETHODIMP CHoops3dStreamCtrl::HATL_Open_Segment(BSTR segment, long *retkey)
{
	if (m_pView)
	{
		char segment_char[4096];
		ConvertToChar(segment_char,segment,4096);
		*retkey = LastKey = HC_KOpen_Segment(segment_char);
	}
 
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Close_Segment()
{
	if (m_pView)
		HC_Close_Segment();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Open_Geometry(HC_KEY key)
{
	if (m_pView)
		HC_Open_Geometry(key);
 
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Close_Geometry()
{
	if (m_pView)
		HC_Close_Geometry();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Open_Edge(int offset1, int offset2)
{
	if (m_pView)
		HC_Open_Edge(offset1, offset2);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Close_Edge()
{
	if (m_pView)
		HC_Close_Edge();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Open_Face(int offset)
{
	if (m_pView)
		HC_Open_Face(offset);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Close_Face()
{
	if (m_pView)
		HC_Close_Face();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Include_Segment(BSTR segment, long *retkey)
{
	if (m_pView)
	{
		char segment_char[4096];
		ConvertToChar(segment_char,segment,4096);
		*retkey = LastKey = HC_KInclude_Segment(segment_char);
	}
 
 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Delete_By_Key(HC_KEY key)
{
 	if (m_pView)
		HC_Delete_By_Key(key);

 	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Flush_Contents(BSTR segment, BSTR filter)
{
	if (m_pView)
	{
		char segment_char[4096];
		char filter_char[4096];
		ConvertToChar(segment_char,segment,4096);
		ConvertToChar(filter_char,filter,4096);
		HC_Flush_Contents(segment_char, filter_char);
	}

 	return S_OK;
}

/* -------------------------------- Set functions -------------------------------- */
STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera(float p_x, float p_y, float p_z, float t_x, float t_y, float t_z, float u_x, float u_y, float u_z, float width, float height, BSTR projection)
{
	if (m_pView)
	{
		HPoint position(p_x,p_y,p_z), target(t_x,t_y,t_z), up(u_x,u_y,u_z);
		char projection_char[4096];

		ConvertToChar(projection_char,projection,4096);
		HC_Set_Camera(&position, &target, &up, width, height, projection_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera_By_Volume(BSTR projection, float xmin, float xmax, float ymin, float ymax)
{
	if (m_pView)
	{
		char projection_char[4096];

		ConvertToChar(projection_char,projection,4096);
		HC_Set_Camera_By_Volume(projection_char, xmin, xmax, ymin, ymax);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera_Field(float width, float height)
{
	if (m_pView)
		HC_Set_Camera_Field(width, height);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera_Near_Limit(float wlimit)
{
	if (m_pView)
		HC_Set_Camera_Near_Limit(wlimit);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera_Position(float p_x, float p_y, float p_z)
{
	if (m_pView)
		HC_Set_Camera_Position(p_x, p_y, p_z);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera_Projection(BSTR projection)
{
	if (m_pView)
	{
		char projection_char[4096];
		ConvertToChar(projection_char, projection, 4096);
		HC_Set_Camera_Projection(projection_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera_Target(float t_x, float t_y, float t_z)
{
	if (m_pView)
		HC_Set_Camera_Target(t_x, t_y, t_z);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Camera_Up_Vector(float u_x, float u_y, float u_z)
{
	if (m_pView)
		HC_Set_Camera_Up_Vector(u_x, u_y, u_z);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Circular_Center(float x, float y, float z)
{
	if (m_pView)
		HC_Set_Circular_Center(x,y,z);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Circular_Center_By_Key(HC_KEY key, float x, float y, float z)
{
	if (m_pView)
		HC_Set_Circular_Center_By_Key(key, x,y,z);

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Color(BSTR col)
{
	if (m_pView)
	{
 		char col_char[4096];
		ConvertToChar(col_char,col,4096);
		HC_Set_Color(col_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Color_By_FIndex(BSTR types, float findex)
{
	if (m_pView)
	{
		char types_char[4096];
		ConvertToChar(types_char,types,4096);
		HC_Set_Color_By_Index(types_char, findex);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Color_By_Index(BSTR types, int index)
{
	if (m_pView)
	{
 		char types_char[4096];
		ConvertToChar(types_char,types,4096);
		HC_Set_Color_By_Index(types_char, index);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Color_By_Value(BSTR types, BSTR colspace, float a, float b, float c)
{
	if (m_pView)
	{
		char types_char[4096];
		char colspace_char[4096];

		ConvertToChar(types_char,types,4096);
		ConvertToChar(colspace_char,colspace,4096);
		HC_Set_Color_By_Value(types_char, colspace_char, a, b, c);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Color_Map(BSTR col)
{
	if (m_pView)
	{
 		char col_char[4096];
		ConvertToChar(col_char,col,4096);
		HC_Set_Color_Map(col_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Color_Map_By_Value(BSTR col, int count, VARIANT *values_var)
{
	if (m_pView)
	{
 		char col_char[4096];
		HPoint *values;

		ConvertToChar(col_char,col,4096);
		GetPointArrayFromVariant(values_var, &values, count);
		HC_Set_Color_Map_By_Value(col_char, count, values);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Conditions(BSTR conditions)
{
	if (m_pView)
	{
 		char conditions_char[4096];
		ConvertToChar(conditions_char,conditions,4096);
		HC_Set_Conditions(conditions_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Driver_Options(BSTR driver_options)
{
	if (m_pView)
	{
 		char driver_options_char[4096];
		ConvertToChar(driver_options_char,driver_options,4096);
		HC_Set_Driver_Options(driver_options_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Edge_Pattern(BSTR pattern)
{
	if (m_pView)
	{
 		char pattern_char[4096];
		ConvertToChar(pattern_char,pattern,4096);
		HC_Set_Edge_Pattern(pattern_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Edge_Weight(float weight)
{
	if (m_pView)
		HC_Set_Edge_Weight(weight);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Face_Pattern(BSTR pattern)
{
	if (m_pView)
	{
 		char pattern_char[4096];
		ConvertToChar(pattern_char,pattern,4096);
		HC_Set_Face_Pattern(pattern_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Faces(int first_face, int face_count)
{
	if (m_pView)
		HC_Set_Faces(first_face, face_count);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Handedness(BSTR handedness)
{
	if (m_pView)
	{
 		char handedness_char[4096];
		ConvertToChar(handedness_char,handedness,4096);
		HC_Set_Handedness(handedness_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Heuristics(BSTR heuristics)
{
	if (m_pView)
	{
 		char heuristics_char[4096];
		ConvertToChar(heuristics_char,heuristics,4096);
		HC_Set_Heuristics(heuristics_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Line_Pattern(BSTR pattern)
{
	if (m_pView)
	{
 		char pattern_char[4096];
		ConvertToChar(pattern_char,pattern,4096);
		HC_Set_Line_Pattern(pattern_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Line_Weight(float weight)
{
	if (m_pView)
		HC_Set_Line_Weight(weight);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Marker_Size(float weight)
{
	if (m_pView)
		HC_Set_Marker_Size(weight);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Marker_Symbol(BSTR symbol)
{
	if (m_pView)
	{
 		char symbol_char[4096];
		ConvertToChar(symbol_char,symbol,4096);
		HC_Set_Marker_Symbol(symbol_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Modelling_Matrix(VARIANT *matrix_var)
{
	if (m_pView)
	{
 		float *matrix;
		int dummy;
		
		GetFloatArrayFromVariant(matrix_var,&matrix,dummy);
		HC_Set_Modelling_Matrix(matrix);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Normal(float x, float y, float z)
{
	if (m_pView)
		HC_Set_Normal(x,y,z);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Parameter(int number, VARIANT *parameters_var)
{
	if (m_pView)
	{
 		float *parameters;

		GetFloatArrayFromVariant(parameters_var,&parameters,number);
		HC_Set_Parameter(number, parameters);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Polygonal_Clip_Region(int count, VARIANT *points_var, BSTR options)
{
	if (m_pView)
	{
 		HPoint *points;
		char options_char[4096];

		GetPointArrayFromVariant(points_var,&points,count);
		ConvertToChar(options_char,options,4096);
		HC_Set_Polygonal_Clip_Region(count, points,options_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Priority(HC_KEY key, long priority)
{
	if (m_pView)
		HC_Set_Priority(key, priority);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Region(int region)
{
	if (m_pView)
		HC_Set_Region(region);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Rendering_Options(BSTR rendering_options)
{
	if (m_pView)
	{
		char rendering_options_char[4096];
		ConvertToChar(rendering_options_char,rendering_options,4096);
		HC_Set_Rendering_Options(rendering_options_char);
	}
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Selectability(BSTR list)
{
	if (m_pView)
	{
		char list_char[4096];
		ConvertToChar(list_char,list,4096);
		HC_Set_Selectability(list_char);
	}
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Streaming_Mode (BSTR flag)
{
	if (m_pView)
	{
		char flag_char[4096];
		ConvertToChar(flag_char,flag,4096);
		HC_Set_Selectability(flag_char);
	}
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Text_Alignment(BSTR locater)
{
	if (m_pView)
	{
		char locater_char[4096];
		ConvertToChar(locater_char,locater,4096);
		HC_Set_Selectability(locater_char);
	}
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Text_Font(BSTR text_font)
{
	if (m_pView)
	{
		char text_font_char[4096];
		ConvertToChar(text_font_char,text_font,4096);
		HC_Set_Text_Font(text_font_char);
	}
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Text_Path(float x, float y, float z)
{
	if (m_pView)
		HC_Set_Text_Path(x,y,z);
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Text_Region(int pCount, VARIANT *points_var, BSTR options)
{
	if (m_pView)
	{
		HPoint *points;
		int dummy;
		char options_char[4096];

		GetPointArrayFromVariant(points_var,&points,dummy);
		ConvertToChar(options_char,options,4096);
		HC_Set_Text_Region(pCount, points, options_char);
	}
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Text_Spacing(float spacing)
{
	if (m_pView)
		HC_Set_Text_Spacing(spacing);
 
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Texture_Matrix(VARIANT *matrix_var)
{
	if (m_pView)
	{
 		float *matrix;
		int dummy;
		
		GetFloatArrayFromVariant(matrix_var,&matrix,dummy);
		HC_Set_Texture_Matrix(matrix);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Trim_Operation(int index, BSTR operation)
{
	if (m_pView)
	{
		char operation_char[4096];		
		ConvertToChar(operation_char, operation, 4096);
		HC_Set_Trim_Operation(index, operation_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Unicode_Options(VARIANT *options_var)
{
	if (m_pView)
	{
		short *options;
		int dummy;

		GetShortArrayFromVariant(options_var,&options,dummy);
		HC_Set_Unicode_Options((unsigned short *)options);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_User_Index(int index, VARIANT *data_var)
{
	if (m_pView)
	{
		char *data;
		int dummy;

		GetByteArrayFromVariant(data_var,&data,dummy);
		HC_Set_User_Index(index, (void *) data);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_User_Options(BSTR list)
{
	if (m_pView)
	{
 		char list_char[4096];
		ConvertToChar(list_char,list,4096);
		HC_Set_User_Options(list_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Variable_Edge_Weight(BSTR weight)
{
	if (m_pView)
	{
 		char weight_char[4096];
		ConvertToChar(weight_char,weight,4096);
		HC_Set_Variable_Edge_Weight(weight_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Variable_Line_Weight(BSTR weight)
{
	if (m_pView)
	{
 		char weight_char[4096];
		ConvertToChar(weight_char,weight,4096);
		HC_Set_Variable_Line_Weight(weight_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Variable_Marker_Size(BSTR weight)
{
	if (m_pView)
	{
 		char weight_char[4096];
		ConvertToChar(weight_char,weight,4096);
		HC_Set_Variable_Marker_Size(weight_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Visibility(BSTR vis)
{
	if (m_pView)
	{
 		char vis_char[4096];
		ConvertToChar(vis_char,vis,4096);
		HC_Set_Visibility(vis_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Window(float left, float right, float bottom, float top)
{
	if (m_pView)
		HC_Set_Window(left, right, bottom, top);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Window_Frame(BSTR flag)
{
	if (m_pView)
	{
 		char flag_char[4096];
		ConvertToChar(flag_char,flag,4096);
		HC_Set_Window_Frame(flag_char);
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Set_Window_Pattern(BSTR pattern)
{
	if (m_pView)
	{
 		char pattern_char[4096];
		ConvertToChar(pattern_char,pattern,4096);
		HC_Set_Window_Pattern(pattern_char);
	}
	return S_OK;
}

/* -------------------------------- UnSet functions -------------------------------- */
STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Camera()
{
	if (m_pView)
		HC_UnSet_Camera();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Color()
{
	if (m_pView)
		HC_UnSet_Color();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Color_Map()
{
	if (m_pView)
		HC_UnSet_Color_Map();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Driver_Options()
{
	if (m_pView)
		HC_UnSet_Driver_Options();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Edge_Pattern()
{
	if (m_pView)
		HC_UnSet_Edge_Pattern();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Edge_Weight()
{
	if (m_pView)
		HC_UnSet_Edge_Weight();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Face_Pattern()
{
	if (m_pView)
		HC_UnSet_Face_Pattern();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Handedness()
{
	if (m_pView)
		HC_UnSet_Handedness();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Heuristics()
{
	if (m_pView)
		HC_UnSet_Heuristics();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Line_Pattern()
{
	if (m_pView)
		HC_UnSet_Line_Pattern();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Line_Weight()
{
	if (m_pView)
		HC_UnSet_Line_Weight();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Marker_Size()
{
	if (m_pView)
		HC_UnSet_Marker_Size();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Marker_Symbol()
{
	if (m_pView)
		HC_UnSet_Marker_Symbol();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Modelling_Matrix()
{
	if (m_pView)
		HC_UnSet_Modelling_Matrix();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Normal()
{
	if (m_pView)
		HC_UnSet_Normal();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_Color(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_Color(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_Driver_Option(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_Driver_Option(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_Heuristic(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_Heuristic(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_Rendering_Option(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_Rendering_Option(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_Selectability(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_Selectability(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_Text_Font(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_Text_Font(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_User_Index(long which)
{
	if (m_pView)
		HC_UnSet_One_User_Index(which);

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_User_Option(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_User_Option(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_One_Visibility(BSTR which)
{
	if (m_pView)
	{
		char which_char[4096];
		ConvertToChar(which_char,which,4096);
		HC_UnSet_One_Visibility(which_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Parameter()
{
	if (m_pView)
		HC_UnSet_Parameter();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Rendering_Options()
{
	if (m_pView)
		HC_UnSet_Rendering_Options();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Selectability()
{
	if (m_pView)
		HC_UnSet_Selectability();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Streaming_Mode()
{
	if (m_pView)
		HC_UnSet_Streaming_Mode();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Text_Alignment()
{
	if (m_pView)
		HC_UnSet_Text_Alignment();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Text_Font()
{
	if (m_pView)
		HC_UnSet_Text_Font();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Text_Path()
{
	if (m_pView)
		HC_UnSet_Text_Path();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Text_Spacing()
{
	if (m_pView)
		HC_UnSet_Text_Spacing();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Texture_Matrix()
{
	if (m_pView)
		HC_UnSet_Texture_Matrix();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_User_Options()
{
	if (m_pView)
		HC_UnSet_User_Options();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Visibility()
{
	if (m_pView)
		HC_UnSet_Visibility();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Window()
{
	if (m_pView)
		HC_UnSet_Window();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Window_Frame()
{
	if (m_pView)
		HC_UnSet_Window_Frame();

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_UnSet_Window_Pattern()
{
	if (m_pView)
		HC_UnSet_Window_Pattern();

	return S_OK;
}


/* Define functions */
STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_Alias(BSTR name, BSTR expansion)
{
	if (m_pView)
	{
		char name_char[4096];
		char expansion_char[4096];

		ConvertToChar(name_char, name, 4096);
		ConvertToChar(expansion_char, expansion, 4096);
		HC_Define_Alias(name_char, expansion_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_Color_Name(BSTR name, BSTR er_name, BSTR ish_name, BSTR definition)
{
	if (m_pView)
	{
		char name_char[4096];
		char er_name_char[4096];
		char ish_name_char[4096];
		char definition_char[4096];

		ConvertToChar(name_char, name, 4096);
		ConvertToChar(er_name_char, er_name, 4096);
		ConvertToChar(ish_name_char, ish_name, 4096);
		ConvertToChar(definition_char, definition, 4096);
		HC_Define_Color_Name(name_char, er_name_char, ish_name_char, definition_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_Font(BSTR name, BSTR options, int data_length, VARIANT *data_var)
{
	if (m_pView)
	{
		char name_char[4096];
		char options_char[4096];
		char *data;

		ConvertToChar(name_char, name, 4096);
		ConvertToChar(options_char, options, 4096);
		GetByteArrayFromVariant(data_var, &data, data_length);
		HC_Define_Font(name_char, options_char, data_length, data);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_Glyph(BSTR name, int data_size, BSTR data)
{
	if (m_pView)
	{
		char name_char[4096];
		char data_char[4096];

		ConvertToChar(name_char, name, 4096);
		ConvertToChar(data_char, data, 4096);
		HC_Define_Glyph(name_char, data_size, data_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_Line_Style(BSTR name, BSTR definition)
{
	if (m_pView)
	{
		char name_char[4096];
		char definition_char[4096];

		ConvertToChar(name_char, name, 4096);
		ConvertToChar(definition_char, definition, 4096);
		HC_Define_Line_Style(name_char, definition_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_Local_Texture(BSTR name, BSTR definition)
{
	if (m_pView)
	{
		char name_char[4096];
		char definition_char[4096];

		ConvertToChar(name_char, name, 4096);
		ConvertToChar(definition_char, definition, 4096);
		HC_Define_Local_Texture(name_char, definition_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_System_Options(BSTR list)
{
	if (m_pView)
	{
		char list_char[4096];

		ConvertToChar(list_char, list, 4096);
		HC_Define_System_Options(list_char);
	}

	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Define_Texture(BSTR name, BSTR definition)
{
	if (m_pView)
	{
		char name_char[4096];
		char definition_char[4096];

		ConvertToChar(name_char, name, 4096);
		ConvertToChar(definition_char, definition, 4096);
		HC_Define_Local_Texture(name_char, definition_char);
	}

	return S_OK;
}


/* Show Functions */
STDMETHODIMP CHoops3dStreamCtrl::HATL_Show_Alias(BSTR alias, /*[out, retval]*/BSTR *expansion)
{
	if (m_pView)
	{
		char alias_char[4096];
		ConvertToChar(alias_char, alias, 4096);
		HC_Show_Alias(alias_char, String1);
		*expansion = CComBSTR(String1).Copy();
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Show_Button(/*[out, retval]*/BSTR *button)
{
	if (m_pView)
	{
		HC_Show_Button(String1);
		*button = CComBSTR(String1).Copy();
	}
	return S_OK;
}

STDMETHODIMP CHoops3dStreamCtrl::HATL_Show_Button_Source()
{
	if (m_pView)
		HC_Show_Button_Source(String1,String2,&Int1);

	return S_OK;
}


STDMETHODIMP CHoops3dStreamCtrl::HATL_Show_Color(/*[out, retval]*/BSTR *color_spec)
{
	if (m_pView)
	{
		HC_Show_Color(String1);
		*color_spec = CComBSTR(String1).Copy();
	}
	return S_OK;
}

LRESULT CHoops3dStreamCtrl::OnToolsOptimizemodel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pView){
		HC_Open_Segment_By_Key(m_pView->GetModelKey());{
			HC_Optimize_Segment_Tree(".","");
		}HC_Close_Segment();
	}
	return 0;
}

LRESULT CHoops3dStreamCtrl::OnToolsSaveas(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pView)
	{
		wchar_t filename[1024];
		ShowFileSaveDialog(filename, 1024);
		SaveFile(filename);
	}
	return 0;
}


LRESULT CHoops3dStreamCtrl::OnToolsVisibilityText(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	if (m_pView)
	{
		HC_Open_Segment_By_Key (m_pView->GetSceneKey());
			if (m_text)
			{
				m_text = false;
				HC_Set_Visibility ("text = off");
			}
			else
			{
				m_text = true;
				HC_Set_Visibility ("text = on");
			}
		HC_Close_Segment ();

		HSelectionSet * selection=m_pView->GetSelection();
		if(selection)
			selection->UpdateHighlighting();

		m_pView->Update();	
	}
	return 0;
}
LRESULT CHoops3dStreamCtrl::OnToolsVisibilityLines(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	if (m_pView)
	{
		HC_Open_Segment_By_Key (m_pView->GetSceneKey());
			if (m_lines)
			{
				m_lines = false;
				HC_Set_Visibility ("lines = off");
			}
			else
			{
				m_lines = true;
				HC_Set_Visibility ("lines = on");
			}
		HC_Close_Segment ();

		HSelectionSet * selection=m_pView->GetSelection();
		if(selection)
			selection->UpdateHighlighting();

		m_pView->Update();	
	}
	return 0;
}

LRESULT CHoops3dStreamCtrl::OnToolsVisibilityFaces(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
{
	if (m_pView)
	{
		HC_Open_Segment_By_Key (m_pView->GetSceneKey());
			if (m_faces)
			{
				m_faces = false;
				HC_Set_Visibility ("faces = off");
			}
			else
			{
				m_faces = true;
				HC_Set_Visibility ("faces = on");
			}
		HC_Close_Segment ();

		HSelectionSet * selection=m_pView->GetSelection();
		if(selection)
			selection->UpdateHighlighting();

		m_pView->Update();	
	}
	return 0;
}
