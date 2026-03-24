// VisualizeView.cpp :implementation of the CVisualizeView class
//

// Standard includes
#include "StdAfx.h"
#include "Resource.h"
#include <afxtempl.h>

#include "hc.h"
#include "hic.h"
#include "HStream.h"
#include "HOpcodeHandler.h"
#include "HVisualizeSelectionSet.h"

#include "Visualize.h"
#include "VisualizeView.h"
#include "VisualizeDoc.h"
#include "CHoopsFrm.h"

// HOOPS/MVO includes
#include "HVisualizeView.h"
#include "HVisualizeModel.h"
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
#include "HEventInfo.h"
#include "HModelInfo.h"
#include "HOpCreateCone.h"
#include "HOpCreateSphere.h"
#include "HOpCreateCylinder.h"

#include "HOpcodeShell.h"
#include "MainFrm.h"

#include "HVisualizeSelectionSet.h"
#include "HUtility.h"

#include "HConstantFramerate.h"
#include "HOpCameraWalk.h"
#include "HUtilityLocaleString.h"

extern CVisualizeApp theApp;


#define H_TIMER_ID_CONST_FRAMERATE		9


/////////////////////////////////////////////////////////////////////////////
// CVisualizeView

IMPLEMENT_DYNCREATE(CVisualizeView, CHoopsView)

CVisualizeView::CVisualizeView()
{

}

CVisualizeView::~CVisualizeView()
{
	delete m_pHView;
}


BEGIN_MESSAGE_MAP(CVisualizeView, CHoopsView)
	//{{AFX_MSG_MAP(CVisualizeView)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_COMMAND(ID_ZOOM_TO_EXTENTS, OnZoomToExtents)
	ON_COMMAND(ID_ZOOM_TO_WINDOW, OnZoomToWindow)
	ON_COMMAND(ID_ORBIT, OnOrbit)
	ON_COMMAND(ID_PAN, OnPan)
	ON_COMMAND(ID_WINDOW_SELECT, OnWindowSelect)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SELECT, OnUpdateWindowSelect)
	ON_COMMAND(ID_SELECTION_DELETESELECTION, OnSelectionDeleteselection)
	ON_UPDATE_COMMAND_UI(ID_SELECTION_DELETESELECTION, OnUpdateSelectionDeleteselection)
	ON_COMMAND(ID_CREATE_SPHERE, OnCreateSphere)
	ON_UPDATE_COMMAND_UI(ID_CREATE_SPHERE, OnUpdateCreateSphere)
	ON_COMMAND(ID_CREATE_CONE, OnCreateCone)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CONE, OnUpdateCreateCone)
	ON_COMMAND(ID_CREATE_CYLINDER, OnCreateCylinder)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CYLINDER, OnUpdateCreateCylinder)
	ON_UPDATE_COMMAND_UI(ID_ORBIT, OnUpdateOrbit)
	ON_UPDATE_COMMAND_UI(ID_PAN, OnUpdatePan)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_TO_WINDOW, OnUpdateZoomToWindow)
	ON_COMMAND(ID_TOOLS_RENDERMODE_GOURAUDSHADED, OnToolsRendermodeGouraudshaded)
	ON_COMMAND(ID_TOOLS_RENDERMODE_HIDDENLINE, OnToolsRendermodeHiddenline)
	ON_COMMAND(ID_TOOLS_RENDERMODE_WIREFRAME, OnToolsRendermodeWireframe)
	ON_COMMAND(ID_LOAD_PART_AND_MAKE_LODS, OnBuildLODS)
	ON_COMMAND(ID_LOD1, OnLOD1)
	ON_COMMAND(ID_LOD2, OnLOD2)
	ON_COMMAND(ID_LODOriginal, OnLODOriginal)
	ON_COMMAND(ID_LODEXAMPLE_ENABLEFRAMERATE, OnEnableFramerate)
	ON_COMMAND(ID_LODEXAMPLE_DISABLEFRAMERATE, OnDisableFramerate)
	ON_COMMAND(ID_WALKOPERATOR, OnWalkOperator)
 	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_WIREFRAME, OnUpdateToolsRendermodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_GOURAUDSHADED, OnUpdateToolsRendermodeGouraudshaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_HIDDENLINE, OnUpdateToolsRendermodeHiddenline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVisualizeView diagnostics

#ifdef _DEBUG
void CVisualizeView::AssertValid() const
{
	CHoopsView::AssertValid();
}

void CVisualizeView::Dump(CDumpContext& dc) const
{
	CHoopsView::Dump(dc);
}
#endif //_DEBUG


void CVisualizeView::LocalSetOperator(HBaseOperator * NewOperator) 
{
	HBaseOperator * op = GetSolidView()->GetOperator();

	if (op)
	    delete op;

    GetSolidView()->SetOperator(NewOperator);
}


 

/////////////////////////////////////////////////////////////////////////////
// CVisualizeView message handlers

void CVisualizeView::OnFileSaveAs() 
{
	CString filter;
	CString  vanilla_filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";

	CString solid_mod_filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";
	filter = solid_mod_filter;
	vanilla_filter = solid_mod_filter;
	TCHAR def_file_ext[] = _T(".hsf");

	if (!((HVisualizeModel *)(m_pHView->GetModel()))->IsSolidModel())
		filter = vanilla_filter;
	else
		filter = solid_mod_filter;

 		
	CFileDialog my_dlg(FALSE, def_file_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);
	if (my_dlg.DoModal() != IDOK)
		return;

	SaveFile( my_dlg.GetPathName());
}


bool CVisualizeView::SaveFile( LPCTSTR csFilePathName )
{
	assert( CString(csFilePathName).IsEmpty() == FALSE );

	int width = 500, height = 500;
	CVisualizeDoc * pDoc = (CVisualizeDoc *)GetDocument();

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

			if (((HVisualizeModel *)m_pHView->GetModel())->IsSolidModel())
			{
				HC_Set_User_Value(1L);
			}
 			if (HTK_Write_Stream_File(csFilePathName,mytool) == TK_Error)
				result = false;

			delete mytool;
		HC_Close_Segment();
		}
		else
			((HVisualizeModel*)pDoc->m_pHoopsModel)->Write(H_ASCII_TEXT(csFilePathName), m_pHView, 0, width, height);

	
		AfxGetApp()->AddToRecentFileList(csFilePathName);

	}
	return true;
}


// resets the camera to view the world space extents of the model
void CVisualizeView::OnZoomToExtents() 
{
	m_pHView->ZoomToExtents();
    m_pHView->Update();
}

void CVisualizeView::OnZoom() 
{
    LocalSetOperator(new HOpCameraZoom(m_pHView));
	((HOpCameraZoom *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}


void CVisualizeView::OnZoomToWindow() 
{
    LocalSetOperator(new HOpCameraZoomBox(m_pHView));
	((HOpCameraZoomBox *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CVisualizeView::OnOrbit() 
{
    LocalSetOperator(new HOpCameraOrbit(m_pHView));
	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CVisualizeView::OnPan() 
{
    LocalSetOperator(new HOpCameraPan(m_pHView));
}

void CVisualizeView::OnWindowSelect() 
{
    LocalSetOperator(new HOpSelectArea(m_pHView));
}

void CVisualizeView::OnSelectionDeleteselection() 
{
	m_pHView->DeleteSelectionList(true);
	m_pHView->Update();	
}

void CVisualizeView::OnUpdateSelectionDeleteselection(CCmdUI* pCmdUI) 
{
	HVisualizeSelectionSet* sel_set = (HVisualizeSelectionSet*) m_pHView->GetSelection();
	if(sel_set->GetSize() > 0)
		pCmdUI->Enable(1);
    else
        pCmdUI->Enable(0);
}


void CVisualizeView::OnUpdateGouraud(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderGouraud)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CVisualizeView::OnUpdateHiddenLine(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CVisualizeView::OnUpdateOrbit(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraOrbit"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CVisualizeView::OnUpdatePan(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraPan"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CVisualizeView::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(),"HOpCameraZoom"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CVisualizeView::OnUpdateZoomToWindow(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraZoomBox"))
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CVisualizeView::OnUpdateWindowSelect(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpSelectArea"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CVisualizeView::OnCreateSphere() 
{
    LocalSetOperator(new HOpCreateSphere(m_pHView));		
}

void CVisualizeView::OnUpdateCreateSphere(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateSphere"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CVisualizeView::OnCreateCone() 
{
    LocalSetOperator(new HOpCreateCone(m_pHView));
}


void CVisualizeView::OnCreateCylinder() 
{
    LocalSetOperator(new HOpCreateCylinder(m_pHView));		
}


void CVisualizeView::OnUpdateCreateCone(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCone"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CVisualizeView::OnUpdateCreateCylinder(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCylinder"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CVisualizeView::OnBuildLODS() 
{
	((HVisualizeView *)m_pHView)->OnBuildLODS();
}

void CVisualizeView::OnLODOriginal() 
{
	((HVisualizeView *)m_pHView)->OnLODOriginal();
}


void CVisualizeView::OnLOD1() 
{
	((HVisualizeView *)m_pHView)->OnLOD1();
}

void CVisualizeView::OnLOD2() 
{
	((HVisualizeView *)m_pHView)->OnLOD2();
}

void CVisualizeView::OnEnableFramerate() 
{
    ((HVisualizeView *)m_pHView)->OnEnableFramerate();

	SetTimer(H_TIMER_ID_CONST_FRAMERATE, 200, 0);
}

void CVisualizeView::OnDisableFramerate() 
{
	((HVisualizeView *)m_pHView)->OnDisableFramerate();
}


void CVisualizeView::OnWalkOperator() 
{
	LocalSetOperator(new HOpCameraWalk(m_pHView));
}

CVisualizeView * CVisualizeView::pThisView = 0;
//void CVisualizeView::event_checker(struct ht_net_rendition *nr)
void CVisualizeView::event_checker(HIC_Rendition const *nr)
{
	
	MSG msg;
	if (pThisView->m_hWnd != 0)
	{		
		int state = GetAsyncKeyState(VK_LBUTTON);
		if (state & 32768)				
		{
			pThisView->m_pHView->GetConstantFrameRateObject()->InitiateDelay();
 
			if (PeekMessage (&msg, pThisView->m_hWnd, WM_MOUSEMOVE, WM_MOUSEMOVE, PM_NOREMOVE))
			{
 				pThisView->m_pHView->SetUpdateInterrupted(true);
			}
			else
				pThisView->m_pHView->SetUpdateInterrupted(2);
  
			HIC_Abort_Update(nr);
 
		}		
		
		state = GetAsyncKeyState(VK_MBUTTON);
		if (state & 32768)				
		{
			HIC_Abort_Update(nr);
			pThisView->m_pHView->SetUpdateInterrupted(true);
		}		
		
		if (PeekMessage (&msg, pThisView->m_hWnd, WM_MOUSEWHEEL, WM_MOUSEWHEEL, PM_NOREMOVE))
		{
			HIC_Abort_Update(nr);
			pThisView->m_pHView->SetUpdateInterrupted(true);
		}
	}
		int state = GetAsyncKeyState(VK_RBUTTON);
		if (state & 32768)				
		{
			pThisView->m_pHView->GetConstantFrameRateObject()->InitiateDelay();
 			pThisView->m_pHView->SetUpdateInterrupted(2);
			HIC_Abort_Update(nr);
		}		
	
}



void CVisualizeView::OnTimer(UINT nIDEvent) 
{

	if (nIDEvent == H_TIMER_ID_CONST_FRAMERATE)		//we like to temporary increase the detail level
	{								//this means of course that timer id 1 is reserved
		KillTimer(nIDEvent);
		HConstantFrameRate *cframerate = m_pHView->GetConstantFrameRateObject();

		// if constant framerate is active
 		if (cframerate->GetActive())
		{	
			pThisView = this;

			// if there has been no activity for at least .3 seconds, then we bump up the detail level
  			if (m_pHView->GetIdleTime() > 0.3f  && !cframerate->GetActivityType())
  				cframerate->IncreaseDetailTemp();

			// reset the timer
   			SetTimer(H_TIMER_ID_CONST_FRAMERATE,200,0);
		}					

		// clear out the flag that indicates something has changed
		cframerate->SetActivityType(NoActivity);	
	}
}

// this functions creates a new HVisualizeView Object, and initializes its camera,
// render mode, query dialog, and operator
void CVisualizeView::OnInitialUpdate() 
{
	char        szTemp[256];
   
	// we must call the base class initialization first to get the proper palette for this view
	// (either the same palette is shared among all views, or this view has a unique palette)
	CHoopsView::OnInitialUpdate();
	
	// create the the Hoops View object to be associated with this MFC View
	// as well as a generic HOOPS segment hierarchy

	CVisualizeDoc * pDoc = (CVisualizeDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	HBaseModel * hmodel = pDoc->GetHoopsModel();

	// create the HOOPS ParaView object corresponding with this MFC View, passing in the 
	// Model Object, the MFC View's window handle, and palette

	m_pHView = new HVisualizeView(hmodel, 0, "opengl", 0, (void *) m_hWnd, (void *)(HPALETTE)*(GetPalette()));

	// initialize and set the default conditions viz. operator, rendermode etc.
 	((HVisualizeView *)m_pHView)->Init();

   
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


	m_pHView->RenderGouraud();  // set the render mode to gouraud


	m_pHView->FitWorld();		// fit the camera to the scene extents
	m_pHView->CameraPositionChanged();

	//we need to adjust the axis window outside the mvo class as the calculation of the window
	//extents is mfc specific
 	AdjustAxisWindow();

	m_pHView->SetEventCheckerCallback(event_checker);
}


void CVisualizeView::OnToolsRendermodeGouraudshaded() 
{
 	m_pHView->SetRenderMode(HRenderGouraud, true);
	m_pHView->Update();
}

void CVisualizeView::OnUpdateToolsRendermodeGouraudshaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderGouraud)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}


void CVisualizeView::OnToolsRendermodeHiddenline() 
{
 	m_pHView->SetRenderMode(HRenderHiddenLine, true);
	m_pHView->Update();
}

void CVisualizeView::OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine || m_pHView->GetRenderMode() == HRenderHiddenLineHOOPS)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CVisualizeView::OnToolsRendermodeWireframe() 
{
 	m_pHView->SetRenderMode(HRenderWireframe, true);
	m_pHView->Update();
}

void CVisualizeView::OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderWireframe)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CVisualizeView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (!bActivate)
	{
 		HOpCameraOrbit *op = (HOpCameraOrbit *)m_pHView->GetOperator();
		if (strcmp(op->GetName(),"HOpCameraOrbit")==0)
			op->m_Angle1 = op->m_Angle2 = op->m_Angle3 = 0;			

		if( GetFirstUpdate() == true)
 			m_pHView->Update();
	}

	CVisualizeView *act = (CVisualizeView *)pActivateView;
	CVisualizeView *deact = (CVisualizeView *)pDeactiveView;

	UNREFERENCED(act);
	UNREFERENCED(deact);

	CHoopsView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}





