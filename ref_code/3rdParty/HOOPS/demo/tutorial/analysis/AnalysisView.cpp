// AnalysisView.cpp :implementation of the CAnalysisView class
//

// Standard includes
#include "StdAfx.h"
#include "Resource.h"
#include <afxtempl.h>

#include "hc.h"
#include "HStream.h"
#include "HOpcodeHandler.h"
#include "HAnalysisSelectionSet.h"

#include "Analysis.h"
#include "AnalysisView.h"
#include "AnalysisDoc.h"
#include "CHoopsFrm.h"

// HOOPS/MVO includes
#include "HAnalysisView.h"
#include "HAnalysisModel.h"
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
#include "HUtilityLocaleString.h"
#include "HOpCreateCone.h"
#include "HOpCreateSphere.h"
#include "HOpCreateCylinder.h"


#include "HOpcodeShell.h"
#include "MainFrm.h"

#include "HAnalysisSelectionSet.h"
#include "HUtility.h"



extern CAnalysisApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CAnalysisView

IMPLEMENT_DYNCREATE(CAnalysisView, CHoopsView)

CAnalysisView::CAnalysisView()
{
	m_bDisplayIsolines = false;
	m_bColorInterpolation = true;
	m_bDisplayEdges = false;
}

CAnalysisView::~CAnalysisView()
{
	CleanUp();
}

void CAnalysisView::CleanUp()
{
	delete m_pHView;
	m_pHView = 0;
}


BEGIN_MESSAGE_MAP(CAnalysisView, CHoopsView)
	//{{AFX_MSG_MAP(CAnalysisView)
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
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_WIREFRAME, OnUpdateToolsRendermodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_GOURAUDSHADED, OnUpdateToolsRendermodeGouraudshaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_HIDDENLINE, OnUpdateToolsRendermodeHiddenline)
	ON_COMMAND(ID_MAP_DATA, OnMapData)
	ON_COMMAND(ID_DISPLAY_ISOLINES, OnDisplayIsolines)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_ISOLINES, OnUpdateDisplayIsolines)
	ON_COMMAND(ID_DISPLAY_EDGES, OnDisplayEdges)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_EDGES, OnUpdateDisplayEdges)
	ON_COMMAND(ID_COLOR_INTERPOLATION, OnColorInterpolation)
	ON_UPDATE_COMMAND_UI(ID_COLOR_INTERPOLATION, OnUpdateColorInterpolation)
	ON_COMMAND(ID_QUAD_INTERPOLATE, OnDisplayQuadInterpolate)
	ON_COMMAND(ID_ANIMATE_COLORMAP, OnAnimateColormap)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAnalysisView diagnostics

#ifdef _DEBUG
void CAnalysisView::AssertValid() const
{
	CHoopsView::AssertValid();
}

void CAnalysisView::Dump(CDumpContext& dc) const
{
	CHoopsView::Dump(dc);
}
#endif //_DEBUG


void CAnalysisView::LocalSetOperator(HBaseOperator * NewOperator) 
{
	HBaseOperator * op = GetSolidView()->GetOperator();

	if (op)
	    delete op;

    GetSolidView()->SetOperator(NewOperator);
}


 

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView message handlers

void CAnalysisView::OnFileSaveAs() 
{
	CString filter;
	CString  vanilla_filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";

	CString solid_mod_filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";
	filter = solid_mod_filter;
	vanilla_filter = solid_mod_filter;
	char def_file_ext[10] = ".hsf";

	if (!((HAnalysisModel *)(m_pHView->GetModel()))->IsSolidModel())
		filter = vanilla_filter;
	else
		filter = solid_mod_filter;

 		
	CFileDialog my_dlg(FALSE, H_TEXT(def_file_ext), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);
	if (my_dlg.DoModal() != IDOK)
		return;

	SaveFile( my_dlg.GetPathName());
}


bool CAnalysisView::SaveFile( LPCTSTR csFilePathName )
{
	assert( CString(csFilePathName).IsEmpty() == FALSE );

	int width = 500, height = 500;
	CAnalysisDoc * pDoc = (CAnalysisDoc *)GetDocument();

	HC_Control_Update_By_Key (m_pHView->GetViewKey(), "redraw everything");
	m_pHView->Update();

	char extension[1024]; 
	unsigned int i;

	extension[0]='\0';
	HC_Parse_String(H_ASCII_TEXT(csFilePathName), ".", -1, extension);

	// make it lower case
	for(i = 0; i < strlen(extension); i++)
     	extension[i] = (char) tolower(extension[i]);


	if(_tcscmp(csFilePathName, _T("")))
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

			if (((HAnalysisModel *)m_pHView->GetModel())->IsSolidModel())
			{
				HC_Set_User_Value(1L);
			}
 			if (HTK_Write_Stream_File(H_ASCII_TEXT(csFilePathName),mytool) == TK_Error)
				result = false;

			delete mytool;
		HC_Close_Segment();
		}
		else
			((HAnalysisModel*)pDoc->m_pHoopsModel)->Write(H_ASCII_TEXT(csFilePathName), m_pHView, 0, width, height);

	
		AfxGetApp()->AddToRecentFileList(csFilePathName);

	}
	return true;
}


// resets the camera to view the world space extents of the model
void CAnalysisView::OnZoomToExtents() 
{
	m_pHView->ZoomToExtents();
    m_pHView->Update();
}

void CAnalysisView::OnZoom() 
{
    LocalSetOperator(new HOpCameraZoom(m_pHView));
	((HOpCameraZoom *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}


void CAnalysisView::OnZoomToWindow() 
{
    LocalSetOperator(new HOpCameraZoomBox(m_pHView));
	((HOpCameraZoomBox *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CAnalysisView::OnOrbit() 
{
    LocalSetOperator(new HOpCameraOrbit(m_pHView));
	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CAnalysisView::OnPan() 
{
    LocalSetOperator(new HOpCameraPan(m_pHView));
}

void CAnalysisView::OnWindowSelect() 
{
    LocalSetOperator(new HOpSelectArea(m_pHView));
}

void CAnalysisView::OnSelectionDeleteselection() 
{
	m_pHView->DeleteSelectionList(true);
	m_pHView->Update();	
}

void CAnalysisView::OnUpdateSelectionDeleteselection(CCmdUI* pCmdUI) 
{
	HAnalysisSelectionSet* sel_set = (HAnalysisSelectionSet*) m_pHView->GetSelection();
	if(sel_set->GetSize() > 0)
		pCmdUI->Enable(1);
    else
        pCmdUI->Enable(0);
}


void CAnalysisView::OnUpdateGouraud(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderGouraud)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CAnalysisView::OnUpdateHiddenLine(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CAnalysisView::OnUpdateOrbit(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraOrbit"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CAnalysisView::OnUpdatePan(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraPan"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CAnalysisView::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(),"HOpCameraZoom"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CAnalysisView::OnUpdateZoomToWindow(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCameraZoomBox"))
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CAnalysisView::OnUpdateWindowSelect(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpSelectArea"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CAnalysisView::OnCreateSphere() 
{
    LocalSetOperator(new HOpCreateSphere(m_pHView));		
}

void CAnalysisView::OnUpdateCreateSphere(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateSphere"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}

void CAnalysisView::OnCreateCone() 
{
    LocalSetOperator(new HOpCreateCone(m_pHView));
}


void CAnalysisView::OnCreateCylinder() 
{
    LocalSetOperator(new HOpCreateCylinder(m_pHView));		
}

void CAnalysisView::OnMapData() 
{
    bool result = ((HAnalysisView *)m_pHView)->MapSelectionSet();
	if ( !result )
		AfxMessageBox(_T("You must first select a shell.")) ;
}

void CAnalysisView::OnDisplayIsolines() 
{
	if (m_bDisplayIsolines == false)
	{
		m_bDisplayIsolines = true;
		((HAnalysisView *)m_pHView)->SetColorIndexInterpolation(true, true);
	}
	else
	{
		m_bDisplayIsolines = false;
		((HAnalysisView *)m_pHView)->SetColorIndexInterpolation(true, false);
	}
}



void CAnalysisView::OnUpdateDisplayIsolines(CCmdUI* pCmdUI) 
{
	if ( m_bDisplayIsolines )
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}


void CAnalysisView::OnDisplayEdges() 
{
	if (m_bDisplayEdges == false)
	{
		m_bDisplayEdges = true;
		((HAnalysisView *)m_pHView)->SetVisibilityEdges(true);
	}
	else
	{
		m_bDisplayEdges = false;
		((HAnalysisView *)m_pHView)->SetVisibilityEdges(false);
	}

	m_pHView->Update();
}

void CAnalysisView::OnUpdateDisplayEdges(CCmdUI* pCmdUI) 
{
	if (m_bDisplayEdges)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}


void CAnalysisView::OnColorInterpolation() 
{
	if (m_bColorInterpolation == false)
	{
		m_bColorInterpolation = true;
		((HAnalysisView *)m_pHView)->SetColorInterpolation(true);
	}
	else
	{
		m_bColorInterpolation = false;
		((HAnalysisView *)m_pHView)->SetColorInterpolation(false);
	}
}

void CAnalysisView::OnUpdateColorInterpolation(CCmdUI* pCmdUI) 
{
	if ( m_bColorInterpolation )
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}

void CAnalysisView::OnDisplayQuadInterpolate()
{
    bool result = ((HAnalysisView *)m_pHView)->QuadInterpolateSelectionSet();
	if ( !result )
		AfxMessageBox(_T("You must first select a shell.")) ;
}


void CAnalysisView::OnAnimateColormap()
{
	bool result = ((HAnalysisView *)m_pHView)->AnimateSelectionSet();
	if ( !result )
		AfxMessageBox(_T("Must map data to create artificial color index array first.")) ;
}


void CAnalysisView::OnUpdateCreateCone(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCone"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CAnalysisView::OnUpdateCreateCylinder(CCmdUI* pCmdUI) 
{
	if (streq(m_pHView->GetOperator()->GetName(), "HOpCreateCylinder"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);


}


// this functions creates a new HAnalysisView Object, and initializes its camera,
// render mode, query dialog, and operator
void CAnalysisView::OnInitialUpdate() 
{
	char        szTemp[256];
   
	// we must call the base class initialization first to get the proper palette for this view
	// (either the same palette is shared among all views, or this view has a unique palette)
	CHoopsView::OnInitialUpdate();
	
	// create the the Hoops View object to be associated with this MFC View
	// as well as a generic HOOPS segment hierarchy

	CAnalysisDoc * pDoc = (CAnalysisDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	HBaseModel * hmodel = pDoc->GetHoopsModel();

	// create the HOOPS ParaView object corresponding with this MFC View, passing in the 
	// Model Object, the MFC View's window handle, and palette

	m_pHView = new HAnalysisView(hmodel, 0, "opengl", 0, (void *) m_hWnd, (void *)(HPALETTE)*(GetPalette()));

	// initialize and set the default conditions viz. operator, rendermode etc.
 	((HAnalysisView *)m_pHView)->Init();

   
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
	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
	m_pHView->RenderGouraud();  // set the render mode to gouraud


	m_pHView->FitWorld();		// fit the camera to the scene extents
	m_pHView->CameraPositionChanged();

	//we need to adjust the axis window outside the mvo class as the calculation of the window
	//extents is mfc specific
 	AdjustAxisWindow();

}

void CAnalysisView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// The default color of lines and edges is white, need to re-set them to
	// a different color so that they will be visibile when printed.  Since
	// the color is set in the parent segment, the new color setting will only
	// affect geometry which has not got a color set explicitly.

	HC_Open_Segment_By_Key(GetSceneKey());
	  HC_Set_Color_By_Index("edges, lines, text", 4);
	HC_Close_Segment();
	
	CHoopsView::OnPrint(pDC, pInfo);

	// reset edge/line colors back to their orignial state
   	HC_Open_Segment_By_Key(GetSceneKey());
	  HC_Set_Color_By_Index("edges, lines, text", 1);
	HC_Close_Segment();

	m_pHView->Update();	
}


void CAnalysisView::OnToolsRendermodeGouraudshaded() 
{
 	m_pHView->SetRenderMode(HRenderGouraud, true);
	m_pHView->Update();
}

void CAnalysisView::OnUpdateToolsRendermodeGouraudshaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderGouraud)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}


void CAnalysisView::OnToolsRendermodeHiddenline() 
{
 	m_pHView->SetRenderMode(HRenderHiddenLine, true);
	m_pHView->Update();
}

void CAnalysisView::OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine || m_pHView->GetRenderMode() == HRenderHiddenLineHOOPS)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CAnalysisView::OnToolsRendermodeWireframe() 
{
 	m_pHView->SetRenderMode(HRenderWireframe, true);
	m_pHView->Update();
}

void CAnalysisView::OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetRenderMode() == HRenderWireframe)
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CAnalysisView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (!bActivate)
	{
 		HOpCameraOrbit *op = (HOpCameraOrbit *)m_pHView->GetOperator();
		if (strcmp(op->GetName(),"HOpCameraOrbit")==0)
			op->m_Angle1 = op->m_Angle2 = op->m_Angle3 = 0;			

		if( GetFirstUpdate() == true)
 			m_pHView->Update();
	}

	CAnalysisView *act = (CAnalysisView *)pActivateView;
	CAnalysisView *deact = (CAnalysisView *)pDeactiveView;

	CHoopsView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}





