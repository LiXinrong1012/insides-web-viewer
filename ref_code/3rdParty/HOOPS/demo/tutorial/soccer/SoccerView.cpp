// SoccerView.cpp :implementation of the CSoccerView class
//

// Standard includes
#include "StdAfx.h"
#include "Resource.h"
#include <afxtempl.h>

#include "hc.h"
#include "HStream.h"
#include "HOpcodeHandler.h"
#include "HSoccerSelectionSet.h"

#include "Soccer.h"
#include "SoccerView.h"
#include "SoccerDoc.h"
#include "CHoopsFrm.h"

// HOOPS/MVO includes
#include "HSoccerView.h"
#include "HSoccerModel.h"
#include "HGlobals.h"
#include "vlist.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HOpCameraPan.h"
#include "HOpCameraZoom.h"
#include "HOpCameraOrbit.h"
#include "HOpCameraZoomBox.h"
#include "HOpSelectArea.h"
#include "HOpSelectAperture.h"
#include "HEventInfo.h"
#include "HModelInfo.h"
#include "HOpCreateCone.h"
#include "HOpCreateSphere.h"
#include "HOpCreateCylinder.h"
#include "HOpCreateRectangle.h"

#include "HOpcodeShell.h"
#include "MainFrm.h"

#include "HSoccerSelectionSet.h"
#include "HUtility.h"
#include "vlist.h"
#include "HSnapGrid.h"
#include "HUtilityLocaleString.h"

extern CSoccerApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CSoccerView

IMPLEMENT_DYNCREATE(CSoccerView, CHoopsView)

CSoccerView::CSoccerView()
{
}

CSoccerView::~CSoccerView()
{	
	H_SAFE_DELETE(m_pHView);
}


BEGIN_MESSAGE_MAP(CSoccerView, CHoopsView)
	//{{AFX_MSG_MAP(CSoccerView)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_COMMAND(ID_ZOOM_TO_EXTENTS, OnZoomToExtents)
	ON_COMMAND(ID_ZOOM_TO_WINDOW, OnZoomToWindow)
	ON_COMMAND(ID_ORBIT, OnOrbit)
	ON_COMMAND(ID_PAN, OnPan)
	ON_COMMAND(ID_WINDOW_SELECT, OnWindowSelect)
	ON_COMMAND(ID_APERTURE_SELECT, OnApertureSelect)
	ON_COMMAND(ID_CREATE_CONE, OnCreateCone)
	ON_COMMAND(ID_CREATE_CYLINDER, OnCreateCylinder)
	ON_COMMAND(ID_CREATE_SPHERE, OnCreateSphere)
	ON_COMMAND(ID_CREATE_RECTANGLE, OnCreateRectangle)
	ON_UPDATE_COMMAND_UI(ID_ORBIT, OnUpdateOrbit)
	ON_UPDATE_COMMAND_UI(ID_PAN, OnUpdatePan)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SELECT, OnUpdateWindowSelect)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_TO_WINDOW, OnUpdateZoomToWindow)
	ON_COMMAND(ID_TOOLS_RENDERMODE_GOURAUDSHADED, OnToolsRendermodeGouraudshaded)
	ON_COMMAND(ID_TOOLS_RENDERMODE_HIDDENLINE, OnToolsRendermodeHiddenline)
	ON_COMMAND(ID_TOOLS_RENDERMODE_WIREFRAME, OnToolsRendermodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_WIREFRAME, OnUpdateToolsRendermodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_GOURAUDSHADED, OnUpdateToolsRendermodeGouraudshaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_HIDDENLINE, OnUpdateToolsRendermodeHiddenline)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DELETE_LAYERS, OnDeleteLayers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSoccerView diagnostics

#ifdef _DEBUG
void CSoccerView::AssertValid() const
{
	CHoopsView::AssertValid();
}

void CSoccerView::Dump(CDumpContext& dc) const
{
	CHoopsView::Dump(dc);
}
#endif //_DEBUG


void CSoccerView::LocalSetOperator(HBaseOperator * NewOperator) 
{
	HBaseOperator * op = GetSolidView()->GetOperator();

	if (op)
	    delete op;

	// turn off the snap mode
	((HSoccerView *)m_pHView)->SetSnap(false);

    GetSolidView()->SetOperator(NewOperator);
}


 

/////////////////////////////////////////////////////////////////////////////
// CSoccerView message handlers

void CSoccerView::OnFileSaveAs() 
{
	CString filter;
	CString  vanilla_filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";

	CString solid_mod_filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";
	filter = solid_mod_filter;
	vanilla_filter = solid_mod_filter;
	TCHAR def_file_ext[10] = _T(".hsf");

	if (!((HSoccerModel *)(m_pHView->GetModel()))->IsSolidModel())
		filter = vanilla_filter;
	else
		filter = solid_mod_filter;

 		
	CFileDialog my_dlg(FALSE, def_file_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);
	if (my_dlg.DoModal() != IDOK)
		return;

	SaveFile( my_dlg.GetPathName());
}


bool CSoccerView::SaveFile( LPCTSTR csFilePathName )
{
	assert( CString(csFilePathName).IsEmpty() == FALSE );

	int width = 500, height = 500;
	CSoccerDoc * pDoc = (CSoccerDoc *)GetDocument();

	HC_Control_Update_By_Key (m_pHView->GetViewKey(), "redraw everything");
	m_pHView->Update();

	char extension[1024]; 
	unsigned int i;

	extension[0]='\0';
	HC_Parse_String(H_ASCII_TEXT (csFilePathName), ".", -1, extension);

	// make it lower case
	for(i = 0; i < strlen(extension); i++)
     	extension[i] = (char) tolower(extension[i]);


	if (!streq(H_ASCII_TEXT(csFilePathName), ""))
	{
		char		extension[1024]; 
		unsigned	int i;
		bool		result = true;

		extension[0]='\0';
		HC_Parse_String(H_ASCII_TEXT(csFilePathName), ".", -1, extension);

		for(i = 0; i < strlen(extension); i++)
		    extension[i] = (char) tolower(extension[i]);

		if (streq(extension, "hsf")) // Write HOOPS Stream File
		{
			HC_Open_Segment_By_Key(m_pHView->GetModel()->GetModelKey());
			HStreamFileToolkit *mytool = new HStreamFileToolkit;

			if (((HSoccerModel *)m_pHView->GetModel())->IsSolidModel())
			{
				HC_Set_User_Value(1L);
			}
 			if (HTK_Write_Stream_File(csFilePathName,mytool) == TK_Error)
				result = false;

			delete mytool;
		HC_Close_Segment();
		}
		else
			((HSoccerModel*)pDoc->m_pHoopsModel)->Write(H_ASCII_TEXT(csFilePathName), m_pHView, 0, width, height);

	
		AfxGetApp()->AddToRecentFileList(csFilePathName);

	}
	return true;
}


// resets the camera to view the world space extents of the model
void CSoccerView::OnZoomToExtents() 
{
	m_pHView->ZoomToExtents();
    m_pHView->Update();
}

void CSoccerView::OnZoom() 
{
    LocalSetOperator(new HOpCameraZoom(m_pHView));
	((HOpCameraZoom *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}


void CSoccerView::OnZoomToWindow() 
{
    LocalSetOperator(new HOpCameraZoomBox(m_pHView));
	((HOpCameraZoomBox *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CSoccerView::OnOrbit() 
{
    LocalSetOperator(new HOpCameraOrbit(m_pHView));
	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CSoccerView::OnPan() 
{
    LocalSetOperator(new HOpCameraPan(m_pHView));
}

void CSoccerView::OnWindowSelect() 
{
    LocalSetOperator(new HOpSelectArea(m_pHView));
}

void CSoccerView::OnApertureSelect() 
{
    LocalSetOperator(new HOpSelectAperture(m_pHView));
}


void CSoccerView::OnUpdateGouraud(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderGouraud)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSoccerView::OnUpdateHiddenLine(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CSoccerView::OnUpdateOrbit(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraOrbit"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSoccerView::OnUpdatePan(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraPan"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSoccerView::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(),"HOpCameraZoom"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CSoccerView::OnUpdateZoomToWindow(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraZoomBox"))
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CSoccerView::OnUpdateWindowSelect(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpSelectArea"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSoccerView::OnCreateCone() 
{
    LocalSetOperator(new HOpCreateCone(m_pHView));
}

void CSoccerView::OnCreateRectangle() 
{
    LocalSetOperator(new HOpCreateRectangle(m_pHView));	

	// turn on snapping for this operator
	((HSoccerView *)m_pHView)->SetSnap(true);
}


void CSoccerView::OnCreateCylinder() 
{
    LocalSetOperator(new HOpCreateCylinder(m_pHView));		
}

void CSoccerView::OnCreateSphere() 
{
    LocalSetOperator(new HOpCreateSphere(m_pHView));		
}

void CSoccerView::OnUpdateCreateCone(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCone"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CSoccerView::OnUpdateCreateCylinder(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCylinder"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CSoccerView::OnUpdateCreateSphere(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateSphere"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}


// this functions creates a new HSoccerView Object, and initializes the view's camera,
// render mode and operator
void CSoccerView::OnInitialUpdate() 
{
	char        szTemp[256];
   
	// we must call the base class initialization first to get the proper palette for this view
	// (either the same palette is shared among all views, or this view has a unique palette)
	CHoopsView::OnInitialUpdate();
	
	// create the the Hoops View object to be associated with this MFC View
	// as well as a generic HOOPS segment hierarchy

	CSoccerDoc * pDoc = (CSoccerDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	HBaseModel * hmodel = pDoc->GetHoopsModel();

	// create the HOOPS ParaView object corresponding with this MFC View, passing in the 
	// Model Object, the MFC View's window handle, and palette
	m_pHView = new HSoccerView(hmodel, 0, "opengl", 0, (void *) m_hWnd, (void *)(HPALETTE)*(GetPalette()));

	// initialize and set the default conditions viz. operator, rendermode etc.
 	m_pHView->Init();
   
	// set the DEBUG_NO_WINDOWS_HOOK debug bit since the app will manage 
	// all palette and update messages
    long debug_flags = DEBUG_NO_WINDOWS_HOOK;

    sprintf (szTemp, "debug = %u", debug_flags);

	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options(szTemp);
		HC_Set_Driver_Options("special events, update interrupts");
		HC_Control_Update(".", "redraw everything");
	HC_Close_Segment();


	LocalSetOperator(new HOpCameraOrbit(m_pHView));	

	// set wireframe render mode
	m_pHView->RenderWireframe();

	// fit the camera to the scene extents
	m_pHView->FitWorld();		
	m_pHView->CameraPositionChanged();

	//we need to adjust the axis window outside the mvo class as the calculation of the window
	//extents is mfc specific
 	AdjustAxisWindow();

	((HSoccerView *)m_pHView)->ProcessText();
}


void CSoccerView::OnToolsRendermodeGouraudshaded() 
{
 	m_pHView->SetRenderMode(HRenderGouraud, true);
	m_pHView->Update();
}

void CSoccerView::OnUpdateToolsRendermodeGouraudshaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderGouraud)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}


void CSoccerView::OnToolsRendermodeHiddenline() 
{
 	m_pHView->SetRenderMode(HRenderHiddenLine, true);
	m_pHView->Update();
}

void CSoccerView::OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine || m_pHView->GetRenderMode() == HRenderHiddenLineHOOPS)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSoccerView::OnToolsRendermodeWireframe() 
{
 	m_pHView->SetRenderMode(HRenderWireframe, true);
	m_pHView->Update();
}

void CSoccerView::OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderWireframe)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}


void CSoccerView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (!bActivate)
	{
 		HOpCameraOrbit *op = (HOpCameraOrbit *)m_pHView->GetOperator();
		if (strcmp(op->GetName(),"HOpCameraOrbit")==0)
			op->m_Angle1 = op->m_Angle2 = op->m_Angle3 = 0;			

		if( GetFirstUpdate() == true)
 			m_pHView->Update();
	}

	CSoccerView *act = (CSoccerView *)pActivateView;
	CSoccerView *deact = (CSoccerView *)pDeactiveView;

	UNREFERENCED(act);
	UNREFERENCED(deact);

	CHoopsView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CSoccerView::OnDeleteLayers() 
{
	((HSoccerView *)m_pHView)->DeleteLayers();
}



void CSoccerView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_pHView)
	{
		HPoint temp_point;
		HSnapGrid * grid = ((HSoccerView *)m_pHView)->GetSnapGrid();
		
		// check if there's a grid, and whether we want to snap to it
		if (grid && ((HSoccerView *)m_pHView)->GetSnap())
		{
			// setup the HEventInfo structure
			HEventInfo	event(m_pHView);
			event.SetPoint(HE_LButtonDown, point.x, point.y, MapFlags(nFlags));

			// get the world coordinates of the point
			temp_point = event.GetMouseWorldPos();

			// get the snapped version of the point
			grid->GetSnappedWorldPos(temp_point);
			
			// convert the point back to pixel space
			HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
				HC_Compute_Coordinates(".", "world", &temp_point, "local pixels", &temp_point);
			HC_Close_Segment();

			// setup CPoint again
			point = CPoint(temp_point.x, temp_point.y);
		}
		CHoopsView::OnLButtonDown(nFlags, point);
	}
}


void CSoccerView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_pHView)
	{
		HPoint temp_point;

		HSnapGrid * grid = ((HSoccerView *)m_pHView)->GetSnapGrid();
		
		// check if there's a grid, and whether we want to snap to it
		if (grid && ((HSoccerView *)m_pHView)->GetSnap())
		{
			// setup the HEventInfo structure
			HEventInfo	event(m_pHView);
			event.SetPoint(HE_LButtonUp, point.x, point.y, MapFlags(nFlags));

			// get the world coordinates of the point
			temp_point = event.GetMouseWorldPos();

			// get the snapped version of the point
			grid->GetSnappedWorldPos(temp_point);
			
			HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
				HC_Compute_Coordinates(".", "world", &temp_point, "local pixels", &temp_point);
			HC_Close_Segment();

			// setup CPoint again
			point = CPoint(temp_point.x, temp_point.y);
		}

		CHoopsView::OnLButtonUp(nFlags, point);
		
	}
}


void CSoccerView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_pHView)
	{
		HPoint temp_point;

		HSnapGrid * grid = ((HSoccerView *)m_pHView)->GetSnapGrid();
		
		// check if there's a grid, and whether we want to snap to it
		if (grid && ((HSoccerView *)m_pHView)->GetSnap())
		{
			// setup the HEventInfo structure
			HEventInfo	event(m_pHView);
			event.SetPoint(HE_MouseMove, point.x, point.y, MapFlags(nFlags));

			// get the world coordinates of the point
			temp_point = event.GetMouseWorldPos();

			// get the snapped version of the point
			grid->GetSnappedWorldPos(temp_point);
			
			HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
				HC_Compute_Coordinates(".", "world", &temp_point, "local pixels", &temp_point);
			HC_Close_Segment();

			// setup CPoint again
			point = CPoint(temp_point.x, temp_point.y);
		}

		CHoopsView::OnMouseMove(nFlags, point);
		
	}
}





