// SpheresView.cpp :implementation of the CSpheresView class
//

// Standard includes
#include "StdAfx.h"
#include "Resource.h"
#include <afxtempl.h>

#include "hc.h"
#include "HStream.h"
#include "HOpcodeHandler.h"
#include "HSpheresSelectionSet.h"

#include "Spheres.h"
#include "SpheresView.h"
#include "SpheresDoc.h"
#include "CHoopsFrm.h"

// HOOPS/MVO includes
#include "HSpheresView.h"
#include "HSpheresModel.h"
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
#include "HOpObjectRotate.h"
#include "HOpMarkupAnnotate.h"
#include "HEventInfo.h"
#include "HModelInfo.h"
#include "HOpCreateCone.h"
#include "HMyCreateSphere.h"
#include "HOpCreateCylinder.h"


#include "HOpcodeShell.h"
#include "MainFrm.h"

#include "HSpheresSelectionSet.h"
#include "HUtility.h"
#include "HUtilityLocaleString.h"



extern CSpheresApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CSpheresView

IMPLEMENT_DYNCREATE(CSpheresView, CHoopsView)

CSpheresView::CSpheresView()
{
}

CSpheresView::~CSpheresView()
{
	H_SAFE_DELETE(m_pHView);
}


BEGIN_MESSAGE_MAP(CSpheresView, CHoopsView)
	//{{AFX_MSG_MAP(CSpheresView)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_COMMAND(ID_ZOOM_TO_EXTENTS, OnZoomToExtents)
	ON_COMMAND(ID_ZOOM_TO_WINDOW, OnZoomToWindow)
	ON_COMMAND(ID_ORBIT, OnOrbit)
	ON_COMMAND(ID_PAN, OnPan)
	ON_COMMAND(ID_ANNOTATE, OnAnnotate)
	ON_COMMAND(ID_ROTATE, OnRotate)
	ON_COMMAND(ID_CHANGE_MATERIAL, OnChangeMaterial)
	ON_COMMAND(ID_WINDOW_SELECT, OnWindowSelect)
	ON_COMMAND(ID_CREATE_CONE, OnCreateCone)
	ON_COMMAND(ID_CREATE_CYLINDER, OnCreateCylinder)
	ON_COMMAND(ID_CREATE_SPHERE, OnCreateSphere)
	ON_UPDATE_COMMAND_UI(ID_ORBIT, OnUpdateOrbit)
	ON_UPDATE_COMMAND_UI(ID_PAN, OnUpdatePan)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, OnUpdateRotate)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SELECT, OnUpdateWindowSelect)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_TO_WINDOW, OnUpdateZoomToWindow)
	ON_COMMAND(ID_TOOLS_RENDERMODE_SHADED, OnToolsRendermodeShaded)
	ON_COMMAND(ID_TOOLS_RENDERMODE_HIDDENLINE, OnToolsRendermodeHiddenline)
	ON_COMMAND(ID_TOOLS_RENDERMODE_WIREFRAME, OnToolsRendermodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_WIREFRAME, OnUpdateToolsRendermodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_SHADED, OnUpdateToolsRendermodeShaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_HIDDENLINE, OnUpdateToolsRendermodeHiddenline)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSpheresView diagnostics

#ifdef _DEBUG
void CSpheresView::AssertValid() const
{
	CHoopsView::AssertValid();
}

void CSpheresView::Dump(CDumpContext& dc) const
{
	CHoopsView::Dump(dc);
}
#endif //_DEBUG


void CSpheresView::LocalSetOperator(HBaseOperator * NewOperator) 
{
	HBaseOperator * op = GetSolidView()->GetOperator();

	if (op)
	    delete op;

    GetSolidView()->SetOperator(NewOperator);
}


 

/////////////////////////////////////////////////////////////////////////////
// CSpheresView message handlers

void CSpheresView::OnFileSaveAs() 
{
	CString filter;
	CString  vanilla_filter = "Sphere File (*.sph)|*.sph|HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";

	CString solid_mod_filter = "Sphere File (*.sph)|*.sph|HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";
	filter = solid_mod_filter;
	vanilla_filter = solid_mod_filter;
	TCHAR def_file_ext[] = _T(".sph");

	if (!((HSpheresModel *)(m_pHView->GetModel()))->IsSolidModel())
		filter = vanilla_filter;
	else
		filter = solid_mod_filter;

 		
	CFileDialog my_dlg(FALSE, def_file_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);
	if (my_dlg.DoModal() != IDOK)
		return;

	SaveFile( my_dlg.GetPathName());
}


bool CSpheresView::SaveFile( LPCTSTR csFilePathName )
{
	assert( CString(csFilePathName).IsEmpty() == FALSE );

	int width = 500, height = 500;
	CSpheresDoc * pDoc = (CSpheresDoc *)GetDocument();

	HC_Control_Update_By_Key (m_pHView->GetViewKey(), "redraw everything");
	m_pHView->Update();

	char extension[1024]; 
	unsigned int i;

	extension[0]='\0';
	HC_Parse_String(H_ASCII_TEXT(csFilePathName), ".", -1, extension);

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

			if (((HSpheresModel *)m_pHView->GetModel())->IsSolidModel())
			{
				HC_Set_User_Value(1L);
			}
 			if (HTK_Write_Stream_File(csFilePathName,mytool) == TK_Error)
				result = false;

			delete mytool;
		HC_Close_Segment();
		}
		else
			((HSpheresModel*)pDoc->m_pHoopsModel)->Write(H_ASCII_TEXT(csFilePathName), m_pHView, 0, width, height);

	
		AfxGetApp()->AddToRecentFileList(csFilePathName);

	}
	return true;
}


// resets the camera to view the world space extents of the model
void CSpheresView::OnZoomToExtents() 
{
	m_pHView->ZoomToExtents();
    m_pHView->Update();
}

void CSpheresView::OnZoom() 
{
    LocalSetOperator(new HOpCameraZoom(m_pHView));
	((HOpCameraZoom *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}


void CSpheresView::OnZoomToWindow() 
{
    LocalSetOperator(new HOpCameraZoomBox(m_pHView));
	((HOpCameraZoomBox *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CSpheresView::OnOrbit() 
{
    LocalSetOperator(new HOpCameraOrbit(m_pHView));
	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CSpheresView::OnPan() 
{
    LocalSetOperator(new HOpCameraPan(m_pHView));
}

void CSpheresView::OnAnnotate() 
{
    LocalSetOperator(new HOpMarkupAnnotate(m_pHView));
}

void CSpheresView::OnRotate() 
{
    LocalSetOperator(new HOpObjectRotate(m_pHView));
}

void CSpheresView::OnChangeMaterial() 
{
    ((HSpheresView *)m_pHView)->ChangeMaterial();
}

void CSpheresView::OnWindowSelect() 
{
    LocalSetOperator(new HOpSelectArea(m_pHView));
}


void CSpheresView::OnUpdateShaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderShaded)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}



void CSpheresView::OnUpdateHiddenLine(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CSpheresView::OnUpdateOrbit(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraOrbit"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSpheresView::OnUpdatePan(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraPan"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSpheresView::OnUpdateRotate(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpObjectRotate"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSpheresView::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(),"HOpCameraZoom"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CSpheresView::OnUpdateZoomToWindow(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraZoomBox"))
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CSpheresView::OnUpdateWindowSelect(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpSelectArea"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSpheresView::OnCreateCone() 
{
    LocalSetOperator(new HOpCreateCone(m_pHView));
}


void CSpheresView::OnCreateCylinder() 
{
    LocalSetOperator(new HOpCreateCylinder(m_pHView));		
}

void CSpheresView::OnCreateSphere() 
{
    LocalSetOperator(new HMyCreateSphere(m_pHView, 0, 1, 50));		
}

void CSpheresView::OnUpdateCreateCone(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCone"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CSpheresView::OnUpdateCreateCylinder(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCylinder"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CSpheresView::OnUpdateCreateSphere(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HMyCreateSphere"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}


// this functions creates a new HSpheresView Object, and initializes its camera,
// render mode, query dialog, and operator
void CSpheresView::OnInitialUpdate() 
{
	char        szTemp[256];
   
	// we must call the base class initialization first to get the proper palette for this view
	// (either the same palette is shared among all views, or this view has a unique palette)
	CHoopsView::OnInitialUpdate();
	
	// create the the Hoops View object to be associated with this MFC View
	// as well as a generic HOOPS segment hierarchy

	CSpheresDoc * pDoc = (CSpheresDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	HBaseModel * hmodel = pDoc->GetHoopsModel();

	// create the HOOPS ParaView object corresponding with this MFC View, passing in the 
	// Model Object, the MFC View's window handle, and palette

	m_pHView = new HSpheresView(hmodel, 0, "opengl", 0, (void *) m_hWnd, (void *)(HPALETTE)*(GetPalette()));

	// initialize and set the default conditions viz. operator, rendermode etc.
 	((HSpheresView *)m_pHView)->Init();

   
	// set the DEBUG_NO_WINDOWS_HOOK debug bit since the app will manage 
	// all palette and update messages
    long        debug_flags = DEBUG_NO_WINDOWS_HOOK | DEBUG_STARTUP_CLEAR_BLACK;


    sprintf (szTemp, "debug = %u", debug_flags);

	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options(szTemp);
		HC_Set_Driver_Options("special events, update interrupts");
		HC_Control_Update(".", "redraw everything");
	HC_Close_Segment();

	LocalSetOperator(new HOpCameraOrbit(m_pHView));	
	
	// fit the camera to the scene extents
	m_pHView->FitWorld();		
	m_pHView->CameraPositionChanged();

	// set the render mode to 'shaded'
	m_pHView->RenderShaded();  

	//we need to adjust the axis window outside the mvo class as the calculation of the window
	//extents is mfc specific
 	AdjustAxisWindow();

	m_pHView->SetShadowMode( HShadowSoft );
}


void CSpheresView::OnToolsRendermodeShaded() 
{
 	m_pHView->SetRenderMode(HRenderShaded, true);
	m_pHView->Update();
}

void CSpheresView::OnUpdateToolsRendermodeShaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderShaded)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}



void CSpheresView::OnToolsRendermodeHiddenline() 
{
 	m_pHView->SetRenderMode(HRenderHiddenLineFast, true);
	m_pHView->Update();
}

void CSpheresView::OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine || m_pHView->GetRenderMode() == HRenderHiddenLineHOOPS)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSpheresView::OnToolsRendermodeWireframe() 
{
 	m_pHView->SetRenderMode(HRenderWireframe, true);
	m_pHView->Update();
}

void CSpheresView::OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderWireframe)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}


void CSpheresView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (!bActivate)
	{
 		HOpCameraOrbit *op = (HOpCameraOrbit *)m_pHView->GetOperator();
		if (strcmp(op->GetName(),"HOpCameraOrbit")==0)
			op->m_Angle1 = op->m_Angle2 = op->m_Angle3 = 0;			

		if( GetFirstUpdate() == true)
 			m_pHView->Update();
	}

	CSpheresView *act = (CSpheresView *)pActivateView;
	CSpheresView *deact = (CSpheresView *)pDeactiveView;

	UNREFERENCED(act);
	UNREFERENCED(deact);

	CHoopsView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}





