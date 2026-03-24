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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsView.cpp,v 1.955.2.5 2011-01-14 21:50:08 heppe Exp $
//

// CSolidHoopsView.cpp :implementation of the CSolidHoopsView class
//

// Standard includes
#include "StdAfx.h"
#include "Resource.h"
#include "HSInclude.h"
#include <afxtempl.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

// HOOPS/3dGS includes
#include "hc.h"
#include "hic.h"


// HOOPS/MVO Includes
#include "HGlobals.h"
#include "vlist.h"
#include "vhash.h"
#include "HEventInfo.h"
#include "HBaseView.h"
#include "HModelInfo.h"
#include "HSolidView.h"

#include "HBaseOperator.h"
#include "HOpCameraWalk.h"
#include "HOpObjectAnnotate.h"
#include "HOpMarkupPostIt.h"
#include "HOpMarkupCircle.h"
#include "HOpMarkupRectangle.h"
#include "HOpMarkupFreehand.h"
#include "HOpMarkupMeasure.h"
#include "HOpCreateCuttingPlane.h"
#include "HOpMoveHandle.h"
#include "HSOpMoveHandle.h"
#include "HOpNavCube.h"
#include "HConstantFrameRate.h"
#include "HOpSelectPolygon.h"
#include "HOpSelectPolyline.h"
#include "HSelectionItem.h"
#include "HOpCameraOrbitTurntable.h"
#include "HOpMarkupAnnotate.h"

#include "HMarkupManager.h"
#include "HUtilityGeometryCreation.h"
#include "HUtility.h"
#include "HBhvBehaviorManager.h"
#include "HBhvUtility.h"
#include "HObjects.h"
#include "HUtilityLocaleString.h"

#include "HUndoManager.h"

#ifdef HOOPS_ONLY
#include "HOpSelectAperture.h"
#include "HOpSelectArea.h"
#include "HTCObjectRotate.h"
#include "HOpCreateCone.h"
#include "HOpCreateSphere.h"
#include "HOpCreateCylinder.h"
#include "HOpCreateNurbsCurve.h"
#include "HOpCreateNurbs3D.h"
#include "HOpObjectClash.h"
#include "HOpObjectRotate.h"
#include "HOpCreateBoolean.h"
#include "AdvancedMaterialDlg.h" 

#endif // HOOPS_ONLY

// HOOPS/MFC includes
#include "CHoopsFrm.h"

#include "HSSelectionSet.h"
#include "CSolidHoopsApp.h"
#include "CSolidHoopsView.h"
#include "CSolidHoopsDoc.h"
#include "CSolidHoopsChildFrm.h"
#include "CSolidHoopsFrm.h"
#include "OpcodeHandlers.h"
#include "HMaterialLibrary.h"

#include "HSolidView.h"
#include "HSolidModel.h"
#include "HUtilitySubwindow.h"
#include "HUtilitySubwindow2.h"
#include "HIOUtilityGDIOutput.h"
#include "HIOUtilityHOOPS.h"
#include "HIOUtilityPDF.h"
#include "HIOUtilityPointCloud.h"
#include "PDFExportDlg.h"

#ifndef HOOPS_ONLY
#include "HSOpObjectTranslate.h"
#include "HSOpSelectAperture.h"
#include "HSOpSelectArea.h"
#include "PlainTopolBrowserDlg.h"
#include "HSPlainSelectionSet.h"
#endif // HOOPS_ONLY

// overridden operators
#include "HSOpCameraPan.h"
#include "HSOpCameraZoom.h"
#include "HSOpCameraOrbit.h"
#include "HSOpCameraZoomBox.h"
#include "HSOpCameraWalk.h"
#include "HOpCameraManipulate.h"
#include "HSQuery.h"
#include "HSQueryAdvanced.h"
#include "varray.h"

// dialogs and stuff
#include "LodDialog.h"
#include "QueryDialog.h"
#include "StyleDialog.h"
#include "busyloddlg.h"
#include "frameratedialog.h"
#include "FrameratePage.h"
#include "DetailPropertySheet.h"
#include "lodpage.h"
#include "EditLightsDlg.h"
#include "HStreamProgressDlg.h"
#include "CSegmentBrowserDlg.h"
#include "CModelBrowserDlg.h"
#include "CErrorBrowserDlg.h"
#include "KeyframeEditor.h"
#include "ClashDlg.h"
#include "ClashSelect.h"
#include "MaterialPropertiesDlg.h"
#include "PresetViewDlg.h"
 
#include "StreamingThread.h"
#include "HSUtility.h"
#include "HEventManager.h"
#ifndef HOOPS_ONLY
#include "BusyDlg.h"
#include "CBinaryFileToolkit.h"
#include "TopolBrowserDlg.h"
#endif // HOOPS_ONLY

#include "HIOUtilityDwfExport.h"
#include "DWFExportOptionsDlg.h"

// HOOPS/Net includes
#include "HSharedKey.h"

#ifdef PARASOLID
#include "PSTopolBrowserDlg.h"
#include "HSParasolidSelectionSet.h"
#endif // PARASOLID

#ifdef ACIS
#include "ASTopolBrowserDlg.h"
#include "HSAcisSelectionSet.h"
#endif // ACIS

#ifdef GRANITE
#include "GSTopolBrowserDlg.h"
#include "HSGraniteSelectionSet.h"
#endif // GRANITE

#ifdef INTEROP
#ifndef _DEBUG
#define DISABLE_FILE_SAVE
#endif // _DEBUG
#include "InterOpPartBrowserDlg.h"
#include "InterOpFileIO.h"
#endif // INTEROP

#include "TextInput.h"
#include "HDispatchXML.h"
#include "CTDriver.h"

// DWG layout loading toolbar
#include "HDWGLayoutLoadUtility.h"

// Other driver debug flags
#define DEBUG_FORCE_SOFTWARE				0x01000000
 
#define MAX_BOOLEAN_TOOLS 1024
#define H_STREAM_BUFFER_SIZE	4*8192 //1024// 4k

#define H_TIMER_ID_BUFFER_POLLER		11
#define H_TIMER_BHV_UPDATE				13
#define H_VIEW_POINTER_INDEX			4155

#define UINT2bool(__uint__val)  (__uint__val > 0) ?  true: false


extern CSolidHoopsApp theApp;

CRITICAL_SECTION sweeten_lock;

// Event handle for the main thread and stream reading thread
// to sync the reading and parsing of buffers

CList<HC_KEY, HC_KEY> sweeten_list;

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsView



static void set_thread_name (int id, char const * name) {
#ifdef _M_IX86
	struct threadname_info {
		DWORD	type;		// must be 0x1000
		LPCSTR	name;		// pointer to name (in user addr space)
		DWORD	threadid;	// thread ID (-1=caller thread)
		DWORD	flags;		// reserved for future use, must be zero

		threadname_info (DWORD id, LPCSTR string) : type (0x1000), name (string), threadid (id), flags (0) {}
	};

	threadname_info	info ((DWORD)id, (LPCSTR)name);

	__try {
		RaiseException (0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info);
	}
	__except(EXCEPTION_CONTINUE_EXECUTION) {}
#endif
}



unsigned int HLoadingThread(LPVOID pParam)
{
 
	set_thread_name (-1, "HLoadingThread");

	CSolidHoopsView *view = (CSolidHoopsView *)pParam;
	CSolidHoopsDoc * doc = (CSolidHoopsDoc *)view->GetDocument();

	HInputHandlerOptions opt;	
	opt.m_tk = doc->GetHoopsModel()->GetStreamFileTK();
	opt.m_pHBaseView = view->GetHoopsView();

	view->GetHoopsView()->SetSuppressUpdate(true);
	view->GetHoopsView()->SetSuppressUpdateTick(true);


	HC_Define_System_Options("update control=thread=off");
	HFileInputResult const result = ((HSolidModel *)doc->GetHoopsModel())->Read(doc->filename,opt.m_pHBaseView);
	HC_Define_System_Options("update control=thread");

	view->GetHoopsView()->SetSuppressUpdateTick(false);
	view->GetHoopsView()->SetSuppressUpdate(false);

	wchar_t message[MVO_BUFFER_SIZE+1] = {L""};
	switch(result){
		case InputOK:
			/* Do nothing. */
		break;
		case InputVersionMismatch:
			swprintf(message, MVO_BUFFER_SIZE, L"InputVersionMismatch was returned while reading\n%s.", doc->filename);
		break;
		case InputFail:
			swprintf(message, MVO_BUFFER_SIZE, L"InputFail was returned while reading\n%s.", doc->filename);
		break;
		case InputNotHandled:
			swprintf(message, MVO_BUFFER_SIZE, L"InputNotHandled was returned while reading\n%s.", doc->filename);
		break;
		case InputBadFileName:
			swprintf(message, MVO_BUFFER_SIZE, L"InputBadFileName was returned while reading\n%s.", doc->filename);
		break;
		case InputBadOptions:
			swprintf(message, MVO_BUFFER_SIZE, L"InputBadOptions was returned while reading\n%s.", doc->filename);
		break;
		default:
			swprintf(message, MVO_BUFFER_SIZE, L"An unknown error was returned while reading\n%s.", doc->filename);
		break;
	}
	
	if(result != InputOK){
		MessageBox(0, H_TEXT(message), _T("ERROR!"), MB_OK);
	}

	((CWnd *)view)->PostMessage(WM_THREADED_LOADING_COMPLETED, 0, 0);
	return 0;
}



IMPLEMENT_DYNCREATE(CSolidHoopsView, CHoopsView)

CSolidHoopsView::CSolidHoopsView()
{
	m_hStreamBufferAccessEvent = 0;
	m_edges					= false;
	m_lights				= true;
	m_curvature_set			= false;
	m_grids					= true;
	m_text					= true;
	m_hidden_lines_visible	= false;
	m_color_index_int		= false;
	m_color_int				= false;
	m_lod_dialog			= 0;
	m_query_dialog			= 0;
	m_advanced_query_dialog	= 0;
	m_style_dialog			= 0;
	m_bHSFVersionMismatch	= false;
	m_default_transmission	= 0.7f;
	m_images = true;
	m_bCameraBeforeBoundingBox= false;
	m_bBoundingBox			= false;
	m_has_initial_view		= false;
	m_bScanColorized		= false;

	m_pDlgSegmentBrowser = 0;
	m_pDlgModelBrowser = 0;
	m_pDlgErrorBrowser = 0;
	m_pDlgCMMDisplay = 0;
#ifndef HOOPS_ONLY
	m_pDlgTopologyBrowser = 0;
#ifdef INTEROP
	m_pDlgInterOpPartBrowser = 0;
#endif // INTEROP
#endif // HOOPS_ONLY
	using_modelling_kernel = false;
	m_pDlgKeyframeEditor = 0;
	m_pDlgClashBrowser = 0;
	m_pDlgClashSelect = 0;

	m_CookieSelected				= 0;
	m_CookieDeSelectedAll			= 0;
	m_cease = false;
	m_bInSpecialSelection = false;
	m_WalkSpeed = 0.0f;

	m_pLayoutLoadUtility = 0;
	m_bMaterialLibraryInitialized = false;

}

CSolidHoopsView::~CSolidHoopsView()
{
 
	if (m_pDlgSegmentBrowser)		
		m_pDlgSegmentBrowser->DestroyWindow();
	delete m_pDlgSegmentBrowser;
	//H_SAFE_DELETE( m_pDlgSegmentBrowser );

	if (m_pDlgModelBrowser)		
		m_pDlgModelBrowser->DestroyWindow();
	delete m_pDlgModelBrowser;
	//H_SAFE_DELETE( m_pDlgModelBrowser );

	if (m_pDlgErrorBrowser)		
		m_pDlgErrorBrowser->DestroyWindow();
	delete m_pDlgErrorBrowser;
	//H_SAFE_DELETE( m_pDlgErrorBrowser );

#ifndef HOOPS_ONLY
	if (m_pDlgTopologyBrowser)		
		m_pDlgTopologyBrowser->DestroyWindow();
	delete m_pDlgTopologyBrowser;
	//H_SAFE_DELETE( m_pDlgTopologyBrowser );
#ifdef INTEROP
	if (m_pDlgInterOpPartBrowser)		
		m_pDlgInterOpPartBrowser->DestroyWindow();
	delete m_pDlgInterOpPartBrowser;
	//H_SAFE_DELETE(m_pDlgInterOpPartBrowser);
#endif // INTEROP
#endif // HOOPS_ONLY

	if (m_pDlgKeyframeEditor)		
		m_pDlgKeyframeEditor->DestroyWindow();
	delete m_pDlgKeyframeEditor;
	//H_SAFE_DELETE( m_pDlgKeyframeEditor );

	if (m_pDlgClashBrowser)		
		m_pDlgClashBrowser->DestroyWindow();
	delete m_pDlgClashBrowser;
	//H_SAFE_DELETE( m_pDlgClashBrowser );

	if (m_pDlgClashSelect)		
		m_pDlgClashSelect->DestroyWindow();
	delete m_pDlgClashSelect;
	//H_SAFE_DELETE( m_pDlgClashSelect );

	if (m_pDlgCMMDisplay)		
		m_pDlgCMMDisplay->DestroyWindow();
	delete m_pDlgCMMDisplay;
	//H_SAFE_DELETE( m_pDlgCMMDisplay );


	if( m_CookieSelected != 0)
	{
		m_pHView->UnSetSignalNotify( m_CookieSelected );
		m_CookieSelected = 0;
	}
	if( m_CookieDeSelectedAll != 0)
	{
		m_pHView->UnSetSignalNotify( m_CookieDeSelectedAll );
		m_CookieDeSelectedAll = 0;
	}

	
	if (m_pHView)
	{

	    m_pHView->SetSuppressUpdate(true);

	    HSOpMoveHandle *temp = (HSOpMoveHandle *)m_pHView->GetHandleOperator();
	    
	    H_SAFE_DELETE(temp);
 	    
	    delete m_pHView;
	}


	if (m_query_dialog)		
		m_query_dialog->DestroyWindow();
	delete m_query_dialog;

	if (m_advanced_query_dialog)
		m_advanced_query_dialog->DestroyWindow();
	delete m_advanced_query_dialog;

	if (m_style_dialog)
		m_style_dialog->DestroyWindow();
	delete m_style_dialog;

	if (m_lod_dialog)
		m_lod_dialog->DestroyWindow();
	delete m_lod_dialog;

	if(m_pLayoutLoadUtility)
		delete m_pLayoutLoadUtility;

}


BEGIN_MESSAGE_MAP(CSolidHoopsView, CHoopsView)
	//{{AFX_MSG_MAP(CSolidHoopsView)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSaveAs)
 	ON_COMMAND(ID_QUERY, OnQuery)
	ON_COMMAND(ID_SUBTRACT, OnSubtract)
	ON_COMMAND(ID_UNION, OnUnion)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_COMMAND(ID_ZOOM_TO_EXTENTS, OnZoomToExtents)
	ON_COMMAND(ID_ZOOM_TO_WINDOW, OnZoomToWindow)
	ON_COMMAND(ID_BUTTON_TURNTABLE, OnTurntable)	
	ON_COMMAND(ID_ORBIT, OnOrbit)
	ON_COMMAND(ID_PAN, OnPan)
 	ON_COMMAND(ID_APERTURE_SELECT, OnApertureSelect)
	ON_COMMAND(ID_WINDOW_SELECT, OnWindowSelect)
	ON_COMMAND(ID_INTERSECT, OnIntersect)
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDBLCLK()
	ON_COMMAND(ID_TOOLS_TRANSPARENCY, OnToolsTransparency)
	ON_COMMAND(ID_TOOLS_VISIBILITY_VERTICES, OnToolsVisibilityVertices)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBILITY_VERTICES, OnUpdateToolsVisibilityVertices)
	ON_COMMAND(ID_TOOLS_VISIBILITY_BREP_EDGES, OnToolsVisibilityEdges)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBILITY_BREP_EDGES, OnUpdateToolsVisibilityEdges)
	ON_COMMAND(ID_TOOLS_VISIBILITY_FACES, OnToolsVisibilityFaces)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBILITY_FACES, OnUpdateToolsVisibilityFaces)
	ON_COMMAND(ID_TOOLS_VISIBILITY_MARKERS, OnToolsVisibilityMarkers)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBILITY_MARKERS, OnUpdateToolsVisibilityMarkers)
	ON_COMMAND(ID_LIGHTS, OnLights)
	ON_UPDATE_COMMAND_UI(ID_LIGHTS, OnUpdateLights)
	ON_UPDATE_COMMAND_UI(ID_INSTANCE, OnUpdateInstance)
	ON_UPDATE_COMMAND_UI(ID_ASSEMBLY, OnUpdateAssembly)
	ON_COMMAND(ID_CURVATURE, OnCurvature)
	ON_UPDATE_COMMAND_UI(ID_CURVATURE, OnUpdateCurvature)
	ON_COMMAND(ID_VERTEX, OnVertex)
	ON_UPDATE_COMMAND_UI(ID_VERTEX, OnUpdateVertex)
	ON_COMMAND(ID_COLOR_INDEX_INTERPOLATION, OnColorIndexInterpolation)
	ON_COMMAND(ID_COLOR_INTERPOLATION, OnColorInterpolation)
	ON_UPDATE_COMMAND_UI(ID_COLOR_INDEX_INTERPOLATION, OnUpdateColorIndexInterpolation)
	ON_UPDATE_COMMAND_UI(ID_COLOR_INTERPOLATION, OnUpdateColorInterpolation)
	ON_COMMAND(ID_ORTHOGRAPHIC, OnOrthographic)
	ON_UPDATE_COMMAND_UI(ID_ORTHOGRAPHIC, OnUpdateOrthographic)
	ON_COMMAND(ID_PERSPECTIVE, OnPerspective)
	ON_UPDATE_COMMAND_UI(ID_PERSPECTIVE, OnUpdatePerspective)
	ON_COMMAND(ID_LEVEL_OF_DETAIL, OnLevelOfDetail)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_OF_DETAIL, OnUpdateLevelOfDetail)
	ON_UPDATE_COMMAND_UI(ID_ORBIT, OnUpdateOrbit)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TURNTABLE, OnUpdateTurntable)
	ON_UPDATE_COMMAND_UI(ID_PAN, OnUpdatePan)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SELECT, OnUpdateWindowSelect)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_TO_WINDOW, OnUpdateZoomToWindow)
	ON_UPDATE_COMMAND_UI(ID_APERTURE_SELECT, OnUpdateApertureSelect)
	ON_UPDATE_COMMAND_UI(ID_QUERY, OnUpdateQuery)
	ON_COMMAND(ID_XY_PLANE, OnXyPlane)
	ON_UPDATE_COMMAND_UI(ID_XY_PLANE, OnUpdateXyPlane)
	ON_COMMAND(ID_XZ_PLANE, OnXzPlane)
	ON_UPDATE_COMMAND_UI(ID_XZ_PLANE, OnUpdateXzPlane)
	ON_COMMAND(ID_YZ_PLANE, OnYzPlane)
	ON_UPDATE_COMMAND_UI(ID_YZ_PLANE, OnUpdateYzPlane)
	ON_COMMAND(ID_ANNOTATE_OBJECT, OnAnnotateModel)
	ON_UPDATE_COMMAND_UI(ID_ANNOTATE_OBJECT, OnUpdateAnnotateModel)
	ON_COMMAND(ID_TOOLS_RENDERMODE_FLATSHADED, OnToolsRendermodeFlatshaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_FLATSHADED, OnUpdateToolsRendermodeFlatshaded)
	ON_COMMAND(ID_TOOLS_RENDERMODE_GOURAUDSHADED, OnToolsRendermodeGouraudshaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_GOURAUDSHADED, OnUpdateToolsRendermodeGouraudshaded)
	ON_COMMAND(ID_TOOLS_RENDERMODE_HIDDENLINE, OnToolsRendermodeHiddenline)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_HIDDENLINE, OnUpdateToolsRendermodeHiddenline)
	ON_COMMAND(ID_TOOLS_RENDERMODE_BREPHIDDENLINE, OnToolsRendermodeBRepHiddenline)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_BREPHIDDENLINE, OnUpdateToolsRendermodeBRepHiddenline)
	ON_COMMAND(ID_TOOLS_RENDERMODE_BREPWIREFRAME, OnToolsRendermodeBRepWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_BREPWIREFRAME, OnUpdateToolsRendermodeBRepWireframe)
	ON_COMMAND(ID_TOOLS_RENDERMODE_FAKEHIDDENLINE, OnToolsRendermodeFakeHiddenLine)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_FAKEHIDDENLINE, OnUpdateToolsRendermodeFakeHiddenLine)
	ON_COMMAND(ID_TOOLS_RENDERMODE_PHONGSHADED, OnToolsRendermodePhongshaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_PHONGSHADED, OnUpdateToolsRendermodePhongshaded)
	ON_COMMAND(ID_TOOLS_RENDERMODE_WIREFRAME, OnToolsRendermodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_WIREFRAME, OnUpdateToolsRendermodeWireframe)
	ON_COMMAND(ID_TOOLS_RENDERMODE_TRIANGULATION, OnToolsRendermodeTriangulation)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_TRIANGULATION, OnUpdateToolsRendermodeTriangulation)
	ON_COMMAND(ID_TOOLS_RENDERMODE_SILHOUETTE, OnToolsRendermodeSilhouette)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_SILHOUETTE, OnUpdateToolsRendermodeSilhouette)
	ON_COMMAND(ID_TOOLS_RENDERMODE_WIREFRAMEWITHSILHOUETTE, OnToolsRendermodeWireframeWithSilhouette)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_WIREFRAMEWITHSILHOUETTE, OnUpdateToolsRendermodeWireframeWithSilhouette)
	ON_COMMAND(ID_TOOLS_RENDERMODE_GOOCHSHADED, OnToolsRendermodeGoochShaded)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_GOOCHSHADED, OnUpdateToolsRendermodeGoochShaded)
	ON_COMMAND(ID_TOOLS_RENDERMODE_SHADEDWITHLINES, OnToolsRendermodeShadedWithLines)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_SHADEDWITHLINES, OnUpdateToolsRendermodeShadedWithLines)
	ON_COMMAND(ID_TOOLS_RENDERMODE_SHADEDWIREFRAME, OnToolsRendermodeShadedWireframe)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_SHADEDWIREFRAME, OnUpdateToolsRendermodeShadedWireframe)
	ON_COMMAND(ID_TOOLS_RENDERMODE_VERTICES, OnToolsRendermodeVertices)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_VERTICES, OnUpdateToolsRendermodeVertices)
	ON_COMMAND(ID_TOOLS_RENDERMODE_SHADEDVERTICES, OnToolsRendermodeShadedVertices)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RENDERMODE_SHADEDVERTICES, OnUpdateToolsRendermodeShadedVertices)
	ON_COMMAND(ID_SHADED, OnShaded)
	ON_UPDATE_COMMAND_UI(ID_SHADED, OnUpdateShaded)
	ON_COMMAND(ID_HIDDENLINE, OnHiddenLineButton)
	ON_UPDATE_COMMAND_UI(ID_HIDDENLINE, OnUpdateHiddenLineButton)
	ON_COMMAND(ID_TOOLS_TEXT_FONTS_ARIAL, OnToolsTextFontsArial)
	ON_COMMAND(ID_TOOLS_TEXT_FONTS_CAVE, OnToolsTextFontsCave)
	ON_COMMAND(ID_TOOLS_TEXT_FONTS_ROMAN, OnToolsTextFontsRoman)
	ON_COMMAND(ID_TOOLS_TEXT_TRANSFORMS_CHARACTERPOSITIONONLY, OnToolsTextTransformsCharacterpositiononly)
	ON_COMMAND(ID_TOOLS_TEXT_TRANSFORMS_OFF, OnToolsTextTransformsOff)
	ON_COMMAND(ID_TOOLS_TEXT_TRANSFORMS_ON, OnToolsTextTransformsOn)
	ON_COMMAND(ID_CREATE_CUTTING_PLANE, OnCreateCuttingPlane)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CUTTING_PLANE, OnUpdateCreateCuttingPlane)
	ON_COMMAND(ID_ROTATE, OnRotate)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, OnUpdateRotate)
	ON_COMMAND(ID_SELECTION_DELETESELECTION, OnSelectionDeleteselection)
	ON_UPDATE_COMMAND_UI(ID_SELECTION_DELETESELECTION, OnUpdateSelectionDeleteselection)
	ON_COMMAND(ID_SELECTION_FOCUS, OnSelectionFocus)
	ON_UPDATE_COMMAND_UI(ID_SELECTION_FOCUS, OnUpdateSelectionFocus)
	ON_COMMAND(ID_VIEW_ANIMATE, OnViewAnimate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATE, OnUpdateViewAnimate)
	ON_UPDATE_COMMAND_UI(ID_SEGMENTBROWSER, OnUpdateSegmentBrowserButton)
	ON_COMMAND(ID_TOOLS_VISIBILITY_HIDDENLINES, OnToolsVisibilityHiddenlines)
	ON_COMMAND(ID_TOOLS_VISIBILITY_TEXT, OnToolsVisibilityText)
	ON_COMMAND(ID_TOOLS_VISIBILITY_IMAGES, OnToolsVisibilityImages)
	ON_COMMAND(ID_TOOLS_VISIBILITY_GRIDS, OnToolsVisibilityGrids)
	ON_COMMAND(ID_VIEW_DISPLAYLISTS, OnViewDisplaylists)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DISPLAYLISTS, OnUpdateViewDisplaylists)
	ON_COMMAND(ID_VIEW_LEVELOFDETAIL, OnViewLevelofdetail)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LEVELOFDETAIL, OnUpdateViewLevelofdetail)
	ON_COMMAND(ID_VIEW_LEVELOFDETAILOPTIONS, OnViewLevelofdetailoptions)
	ON_COMMAND(ID_VIEW_POLYGONHANDEDNESS_LEFT, OnViewPolygonhandednessLeft)
	ON_UPDATE_COMMAND_UI(ID_VIEW_POLYGONHANDEDNESS_LEFT, OnUpdateViewPolygonhandednessLeft)
	ON_COMMAND(ID_VIEW_POLYGONHANDEDNESS_NONE, OnViewPolygonhandednessNone)
	ON_UPDATE_COMMAND_UI(ID_VIEW_POLYGONHANDEDNESS_NONE, OnUpdateViewPolygonhandednessNone)
	ON_COMMAND(ID_VIEW_POLYGONHANDEDNESS_RIGHT, OnViewPolygonhandednessRight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_POLYGONHANDEDNESS_RIGHT, OnUpdateViewPolygonhandednessRight)
	ON_COMMAND(ID_FRAMERATEOPTIONS, OnFrameRateoptions)
	ON_COMMAND(ID_MEASURE, OnMeasuredistance)
	ON_UPDATE_COMMAND_UI(ID_MEASURE, OnUpdateMeasuredistance)
	ON_COMMAND(ID_FLUSH_HARDWARE_RESOURCES, OnFlushHardwareResources)
	ON_UPDATE_COMMAND_UI(ID_FLUSH_HARDWARE_RESOURCES, OnUpdateFlushHardwareResources)
	ON_COMMAND(ID_RELINQUISH_MEMORY, OnRelinquishMemory)
	ON_UPDATE_COMMAND_UI(ID_RELINQUISH_MEMORY, OnUpdateRelinquishMemory)
	ON_COMMAND(ID_ZOOM_TO_SELECTION, OnZoomToSelection)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_TO_SELECTION, OnUpdateZoomToSelection)
  	ON_COMMAND(ID_FACESASLINES, OnFacesaslines)
	ON_UPDATE_COMMAND_UI(ID_FACESASLINES, OnUpdateFacesaslines)
	ON_COMMAND(ID_DEMOANIMATION, OnDemoanimation)
	ON_COMMAND(ID_VIEW_WINDOW_COLOR, OnViewWindowColor)
	ON_COMMAND(ID_INSTANCE, OnInstance)
	ON_COMMAND(ID_ASSEMBLY, OnAssembly)
	ON_COMMAND(ID_TRANSLATE, OnTranslate)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATE, OnUpdateTranslate)
	ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
	ON_MESSAGE(WM_NEW_STREAM_FILE_BUFFER,OnNewStreamFileBuffer)
	ON_MESSAGE(WM_READING_THREAD_COMPLETED,OnReadingThreadCompleted)
 	ON_MESSAGE(WM_THREADED_LOADING_COMPLETED,OnThreadedLoadingCompleted)
 	ON_COMMAND(ID_WALK, OnWalk)
	ON_COMMAND(ID_SWEETEN, OnSweeten)
	ON_UPDATE_COMMAND_UI(ID_SWEETEN, OnUpdateSweeten)
	ON_UPDATE_COMMAND_UI(ID_WALK, OnUpdateWalk)
	ON_COMMAND(ID_LOD_LEVEL_LEVEL1, OnLodLevelLevel1)
	ON_UPDATE_COMMAND_UI(ID_LOD_LEVEL_LEVEL1, OnUpdateLodLevelLevel1)
	ON_COMMAND(ID_LOD_LEVEL_ORIGINAL, OnLodLevelOriginal)
	ON_UPDATE_COMMAND_UI(ID_LOD_LEVEL_ORIGINAL, OnUpdateLodLevelOriginal)
	ON_COMMAND(ID_LOD_LEVEL_LEVEL2, OnLodLevelLevel2)
	ON_UPDATE_COMMAND_UI(ID_LOD_LEVEL_LEVEL2, OnUpdateLodLevelLevel2)
	ON_COMMAND(ID_VIEWCUBE, OnViewcube)
	ON_UPDATE_COMMAND_UI(ID_VIEWCUBE, OnUpdateViewcube)
	ON_COMMAND(ID_MANIPULATE_SMOOTHTRANSITION, OnManipulateSmoothtransition)
	ON_UPDATE_COMMAND_UI(ID_MANIPULATE_SMOOTHTRANSITION, OnUpdateManipulateSmoothtransition)
	ON_COMMAND(ID_EDIT_COLOR, OnEditColor)
	ON_COMMAND(ID_EDIT_LIGHTS, OnEditLights)
	ON_COMMAND(ID_ISO_PLANE, OnIsoPlane)
	ON_UPDATE_COMMAND_UI(ID_ISO_PLANE, OnUpdateIsoPlane)
	ON_COMMAND(ID_VIEW_COORDINATESYSTEM_LEFTHANDED, OnViewCoordinatesystemLefthanded)
	ON_COMMAND(ID_VIEW_COORDINATESYSTEM_RIGHTHANDED, OnViewCoordinatesystemRighthanded)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COORDINATESYSTEM_LEFTHANDED, OnUpdateViewCoordinatesystemLefthanded)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COORDINATESYSTEM_RIGHTHANDED, OnUpdateViewCoordinatesystemRighthanded)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATE, OnUpdateAnimate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WINDOW_COLOR, OnUpdateViewWindowcolor)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_TO_EXTENTS, OnUpdateZoomToExtents)
	ON_UPDATE_COMMAND_UI(ID_COMPUTE_SAMPLE_DATA, OnUpdateComputeSampleData)
	ON_UPDATE_COMMAND_UI(ID_FRAMERATEOPTIONS, OnUpdateFramerateoptions)
	ON_UPDATE_COMMAND_UI(ID_FILE_LOAD, OnUpdateFileLoad)
	ON_UPDATE_COMMAND_UI(ID_TOPOLBROWSER, OnUpdateTopolbrowser)
	ON_UPDATE_COMMAND_UI(ID_MODELBROWSER, OnUpdateModelBrowser)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COLOR, OnUpdateEditColor)
	ON_COMMAND(ID_REDLINE_RECTANGLE, OnRedlineRectangle)
	ON_UPDATE_COMMAND_UI(ID_REDLINE_RECTANGLE, OnUpdateRedlineRectangle)
	ON_COMMAND(ID_REDLINE_CIRCLE, OnRedlineCircle)
	ON_UPDATE_COMMAND_UI(ID_REDLINE_CIRCLE, OnUpdateRedlineCircle)
	ON_WM_DESTROY()
	ON_COMMAND(ID_MARKUP_CIRCLE, OnMarkupCircle)
	ON_UPDATE_COMMAND_UI(ID_MARKUP_CIRCLE, OnUpdateMarkupCircle)
	ON_COMMAND(ID_MARKUP_FREEHAND, OnMarkupFreehand)
	ON_UPDATE_COMMAND_UI(ID_MARKUP_FREEHAND, OnUpdateMarkupFreehand)
	ON_COMMAND(ID_MARKUP_RECTANGLE, OnMarkupRectangle)
	ON_UPDATE_COMMAND_UI(ID_MARKUP_RECTANGLE, OnUpdateMarkupRectangle)
	ON_COMMAND(ID_ZX_PLANE, OnZxPlane)
	ON_UPDATE_COMMAND_UI(ID_ZX_PLANE, OnUpdateZxPlane)
	ON_COMMAND(ID_ZY_PLANE, OnZyPlane)
	ON_UPDATE_COMMAND_UI(ID_ZY_PLANE, OnUpdateZyPlane)
	ON_COMMAND(ID_YX_PLANE, OnYxPlane)
	ON_UPDATE_COMMAND_UI(ID_YX_PLANE, OnUpdateYxPlane)
	ON_COMMAND(ID_ISOMETRIC, OnIsometric)
	ON_UPDATE_COMMAND_UI(ID_ISOMETRIC, OnUpdateIsometric)
	ON_COMMAND(ID_MARKUP_ANNOTATE, OnMarkupAnnotate)
	ON_UPDATE_COMMAND_UI(ID_MARKUP_ANNOTATE, OnUpdateMarkupAnnotate)
	ON_UPDATE_COMMAND_UI(ID_CONSTANTSPIN, OnUpdateConstantspin)
	ON_COMMAND(ID_ANNOTATE, OnAnnotate)
	ON_UPDATE_COMMAND_UI(ID_ANNOTATE, OnUpdateAnnotate)
	ON_COMMAND(ID_VIEW_ANTIALIASING, OnViewAntialiasing)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANTIALIASING, OnUpdateViewAntialiasing)
	ON_COMMAND(ID_VIEW_BACKPLANECULLING, OnViewBackplaneculling)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BACKPLANECULLING, OnUpdateViewBackplaneculling)
    	ON_COMMAND(ID_TOOLS_VISIBILITY_LINES, OnToolsVisibilityLines)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBILITY_LINES, OnUpdateToolsVisibilityLines)
	ON_COMMAND(ID_TOOLS_VISIBILITY_HOOPS_EDGES, OnToolsVisibilityHoopsEdges)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBILITY_HOOPS_EDGES, OnUpdateToolsVisibilityHoopsEdges)
	ON_COMMAND(ID_CAPPING_PLANES, OnCappingPlanes)
	ON_UPDATE_COMMAND_UI(ID_CAPPING_PLANES, OnUpdateCappingPlanes)
	ON_COMMAND(ID_CAPPING_LINES, OnCappingLines)
	ON_UPDATE_COMMAND_UI(ID_CAPPING_LINES, OnUpdateCappingLines)
	ON_COMMAND(ID_VIEW_SOFT_SHADOW, OnViewSoftShadow)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SOFT_SHADOW, OnUpdateViewSoftShadow)
	ON_COMMAND(ID_BEHAVIOR_PLAY, OnBehaviorPlay)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_PLAY, OnUpdateBehaviorPlay)
	ON_COMMAND(ID_BEHAVIOR_REWIND, OnBehaviorRewind)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_REWIND, OnUpdateBehaviorRewind)
	ON_COMMAND(ID_STEP_BACK, OnStepBack)
	ON_COMMAND(ID_STEP_FORWARD, OnStepForward)
	ON_COMMAND(ID_TEXT_TRANSFORMS, OnTextTransforms)
	ON_UPDATE_COMMAND_UI(ID_TEXT_TRANSFORMS, OnUpdateTextTransforms)
	ON_COMMAND(ID_BEHAVIOR_CONTINUOUS_PLAY, OnBehaviorContinuousPlay)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CONTINUOUS_PLAY, OnUpdateBehaviorContinuousPlay)
	ON_UPDATE_COMMAND_UI(ID_STEP_FORWARD, OnUpdateStepForward)
	ON_UPDATE_COMMAND_UI(ID_STEP_BACK, OnUpdateStepBack)
	ON_COMMAND(ID_MATERIAL_PROPERTIES, OnMaterialProperties)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_PROPERTIES, OnUpdateMaterialProperties)
	ON_COMMAND(ID_CREATE_CUTTING_PLANE2, OnCreateCuttingPlane2)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CUTTING_PLANE2, OnUpdateCreateCuttingPlane2)
	ON_COMMAND(ID_CREATE_CUTTING_PLANE3, OnCreateCuttingPlane3)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CUTTING_PLANE3, OnUpdateCreateCuttingPlane3)
	ON_COMMAND(ID_TOOLS_SELECT, OnToolsSelect)
	ON_COMMAND(ID_TOOLS_ACTIVATEMANIPULATOR, OnToolsActivatemanipulator)
	ON_COMMAND(ID_TOOLS_DELETE_ENTITY, OnToolsDeleteEntity)
	ON_COMMAND(ID_TOOLS_SET_NOTE_TEXT, OnToolsSetNoteText)
	ON_COMMAND(ID_TOOLS_ACTIVATEMANIPULATOR2, OnToolsActivatemanipulator2)
	ON_COMMAND(ID_TOOLS_DEACTIVATEMANIPULATOR, OnToolsDeactivatemanipulator)
	ON_COMMAND(ID_TOOLS_DEACTIVATEALLMANIPULATOS, OnToolsDeactivateallmanipulatos)
	ON_COMMAND(ID_TOOLS_SNAPSHOT, OnToolsSnapshot)
	ON_COMMAND(ID_TOOLS_MAGNIFIER, OnToolsMagnifier)
	ON_COMMAND(ID_TOOLS_POINTER, OnToolsPointer)
	ON_COMMAND(ID_TOOLS_SUBWINDOW_SYNC_FROM_CAMERA, OnToolsSubwindowSyncFromCamera)
	ON_COMMAND(ID_TOOLS_SUBWINDOW_SYNCTOCAMERA, OnToolsSubwindowSynctocamera)
	ON_COMMAND(ID_TOOLS_SUBWINDOW_FREEZE, OnToolsSubwindowFreeze)
	ON_COMMAND(ID_TOOLS_SUBWINDOW_UNFREEZE, OnToolsSubwindowUnfreeze)
	ON_COMMAND(ID_TOOLS_LIGHTS_INSERTLOCALLIGHT, OnToolsLightsInsertlocallight)
	ON_COMMAND(ID_TOOLS_LIGHTS_INSERTDISTANTLIGHT, OnToolsLightsInsertdistantlight)
	ON_COMMAND(ID_TOOLS_LIGHTS_INSERTSPOTLIGHT, OnToolsLightsInsertspotlight)
	ON_COMMAND(ID_TOOLS_MANIPULATOR_ACTIVATEPARENT, OnToolsManipulatorActivateparent)
	ON_COMMAND(ID_TOOLS_MANIPULATOR_COMBINESELECTED, OnToolsManipulatorCombineselected)
	ON_COMMAND(ID_VIEW_CAMERA_NEAR_LIMIT, OnViewCameraNearLimit)
	ON_COMMAND(ID_TOOLS_LIGHTS_LIGHT_GEOMETRY_OFF, OnToolsLightsLightGeometryOff)
	ON_COMMAND(ID_TOOLS_LIGHTS_LIGHT_GEOMETRY_ON, OnToolsLightsLightGeometryOn)
	ON_COMMAND(ID_TOOLS_VISIBILITY_MARKERS_ONLY, OnToolsVisibilityMarkersOnly)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBILITY_MARKERS_ONLY, OnUpdateToolsVisibilityMarkersOnly)
	ON_COMMAND(ID_POLYGON_SELECT, OnPolygonSelect)
	ON_UPDATE_COMMAND_UI(ID_POLYGON_SELECT, OnUpdatePolygonSelect)
	ON_COMMAND(ID_POLYLINE_SELECT, OnPolylineSelect)
	ON_UPDATE_COMMAND_UI(ID_POLYLINE_SELECT, OnUpdatePolylineSelect)
	ON_COMMAND(ID_CREATE_CREATETWOSIDEDSECTION, OnCreateCreatetwosidedsection)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CREATETWOSIDEDSECTION, OnUpdateCreateCreatetwosidedsection)
	ON_COMMAND(ID_CREATE_CREATETHREESIDEDSECTION, OnCreateCreatethreesidedsection)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CREATETHREESIDEDSECTION, OnUpdateCreateCreatethreesidedsection)
	ON_COMMAND(ID_SELECTION_CLOSESTDISTANCE, OnSelectionClosestdistance)
	ON_COMMAND(ID_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, OnUpdateUndo)
	ON_COMMAND(ID_REDO, OnRedo)
	ON_UPDATE_COMMAND_UI(ID_REDO, OnUpdateRedo)
	ON_COMMAND(ID_HOME, OnHome)

	ON_COMMAND(ID_PREV_LAYOUT, OnPreviousLayout)
	ON_UPDATE_COMMAND_UI(ID_PREV_LAYOUT, OnUpdatePreviousLayout)
	ON_COMMAND(ID_NEXT_LAYOUT, OnNextLayout)
	ON_UPDATE_COMMAND_UI(ID_NEXT_LAYOUT, OnUpdateNextLayout)

	ON_COMMAND(ID_CREATE_CREATESLICE, OnCreateCreateSlice)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CREATESLICE, OnUpdateCreateCreateSlice)

	ON_COMMAND(ID_BUTTON_CAE_TOGGLE_LEGEND, OnVerticalCAEToggleLegend)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CAE_TOGGLE_LEGEND, OnUpdateVerticalCAEToggleLegend)
	ON_COMMAND(ID_BUTTON_CAE_MAP_DATA, OnVerticalCAEMapData)
	ON_COMMAND(ID_BUTTON_CAE_COLOR_INDEX, OnVerticalCAEColorIndex)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CAE_COLOR_INDEX, OnUpdateVerticalCAEColorIndex)
	ON_COMMAND(ID_BUTTON_CAE_COLOR_INTERPOLATION, OnVerticalCAEColorInterpolation)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CAE_COLOR_INTERPOLATION, OnUpdateVerticalCAEColorInterpolation)
	ON_COMMAND(ID_BUTTON_CAE_ISOLINES, OnVerticalCAEIsolines)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CAE_ISOLINES, OnUpdateVerticalCAEIsolines)
	ON_COMMAND(ID_BUTTON_QUAD_INTERPOLATION, OnVerticalCAEQuadInterpolation)

	ON_COMMAND(ID_BUTTON_CMM_TOGGLE_COLLISION, OnVerticalCMMToggleCollision)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CMM_TOGGLE_COLLISION, OnUpdateVerticalCMMToggleCollision)
	ON_COMMAND(ID_BUTTON_CMM_RESET_VISIBILITY, OnVerticalCMMToggleVisibility)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CMM_RESET_VISIBILITY, OnUpdateVerticalCMMToggleVisibility)
	ON_COMMAND(ID_BUTTON_CMM_HIDE_POSITIONS, OnVerticalCMMHidePositions)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CMM_HIDE_POSITIONS, OnUpdateVerticalCMMHidePositions)

	ON_UPDATE_COMMAND_UI(ID_HOME, OnUpdateHome)
	ON_COMMAND(ID_EXTRA_SLOT1, OnExtraSlot1)
	ON_COMMAND(ID_EXTRA_SLOT2, OnExtraSlot2)
	ON_COMMAND(ID_EXTRA_SLOT3, OnExtraSlot3)
	ON_COMMAND(ID_EXTRA_SLOT4, OnExtraSlot4)
	ON_COMMAND(ID_EXTRA_SLOT5, OnExtraSlot5)
	ON_COMMAND(ID_DYNAMIC_EXTRA_SLOT1, OnDynamicExtraSlot1)
	ON_COMMAND(ID_DYNAMIC_EXTRA_SLOT2, OnDynamicExtraSlot2)
	ON_COMMAND(ID_DYNAMIC_EXTRA_SLOT3, OnDynamicExtraSlot3)
	ON_COMMAND(ID_DYNAMIC_EXTRA_SLOT4, OnDynamicExtraSlot4)
	ON_COMMAND(ID_DYNAMIC_EXTRA_SLOT5, OnDynamicExtraSlot5)
	ON_WM_LBUTTONDBLCLK()
 	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MANIPULATE_SMOOTHTRANSITION, OnManipulateSmoothtransition)
	ON_UPDATE_COMMAND_UI(ID_MANIPULATE_SMOOTHTRANSITION, OnUpdateManipulateSmoothtransition)
	ON_COMMAND(ID_SAVEMARKUP, OnSaveMarkup)
	ON_COMMAND(ID_EDITMARKUP, OnEditMarkup)
	ON_COMMAND(ID_WALK, OnWalk)
	ON_UPDATE_COMMAND_UI(ID_WALK, OnUpdateWalk)
	ON_COMMAND(ID_TOOLS_LODGENERATION, OnToolsLodgeneration)
	//}}AFX_MSG_MAP
#ifdef HOOPS_ONLY
	ON_COMMAND(ID_CREATE_CONE, OnCreateCone)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CONE, OnUpdateCreateCone)
	ON_COMMAND(ID_CREATE_CYLINDER, OnCreateCylinder)
	ON_UPDATE_COMMAND_UI(ID_CREATE_CYLINDER, OnUpdateCreateCylinder)
	ON_COMMAND(ID_CREATE_SPHERE, OnCreateSphere)
	ON_UPDATE_COMMAND_UI(ID_CREATE_SPHERE, OnUpdateCreateSphere)
	ON_COMMAND(ID_CREATE_NURBSCURVE, OnCreateNurbscurve)
	ON_UPDATE_COMMAND_UI(ID_CREATE_NURBSCURVE, OnUpdateCreateNurbscurve)
  	ON_COMMAND(ID_CLASH_DETECTION, OnClashDetection)
	ON_UPDATE_COMMAND_UI(ID_CLASH_DETECTION, OnUpdateClashDetection)
	ON_COMMAND(ID_VIEW_ANIMATEOBJECT, OnViewAnimateObject)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATEOBJECT, OnUpdateViewAnimateObject)
	ON_COMMAND(ID_SEGMENT_SELECT_LEVEL, OnSegmentSelectLevel)
	ON_UPDATE_COMMAND_UI(ID_SEGMENT_SELECT_LEVEL, OnUpdateSegmentSelectLevel)
	ON_COMMAND(ID_ENTITY_SELECT_LEVEL, OnEntitySelectLevel)
	ON_UPDATE_COMMAND_UI(ID_ENTITY_SELECT_LEVEL, OnUpdateEntitySelectLevel)
	ON_COMMAND(ID_SUBENTITY_SELECT_LEVEL, OnSubentitySelectLevel)
	ON_UPDATE_COMMAND_UI(ID_SUBENTITY_SELECT_LEVEL, OnUpdateSubentitySelectLevel)
	ON_COMMAND(ID_SUBENTITY_FACES, OnSubentityFaces)
	ON_COMMAND(ID_SUBENTITY_EDGES, OnSubentityEdges)
	ON_COMMAND(ID_SUBENTITY_VERTICES, OnSubentityVertices)
	ON_COMMAND(ID_BOOLEANTYPE_INTERSECTION, OnBooleantypeIntersection)
	ON_COMMAND(ID_BOOLEANTYPE_SUBTRACT, OnBooleantypeSubtract)
	ON_COMMAND(ID_BOOLEANTYPE_UNION, OnBooleantypeUnion)
#else
	ON_UPDATE_COMMAND_UI(ID_SUBTRACT, OnUpdateSubtract)
 	ON_UPDATE_COMMAND_UI(ID_UNION, OnUpdateUnion)
	ON_UPDATE_COMMAND_UI(ID_INTERSECT, OnUpdateIntersect)
	ON_COMMAND(ID_FACE, OnFace)
	ON_UPDATE_COMMAND_UI(ID_FACE, OnUpdateFace)
	ON_COMMAND(ID_EDGE, OnEdge)
	ON_UPDATE_COMMAND_UI(ID_EDGE, OnUpdateEdge)
	ON_COMMAND(ID_BODY, OnBody)
	ON_UPDATE_COMMAND_UI(ID_BODY, OnUpdateBody)
	ON_COMMAND(ID_OPTIMIZE, OnOptimize)
	ON_UPDATE_COMMAND_UI(ID_OPTIMIZE, OnUpdateOptimize)
#endif // HOOPS_ONLY

	ON_COMMAND(ID_POINT_CLOUD_SPLAT_SYMBOL, OnToggleSplatSymbol)
	ON_UPDATE_COMMAND_UI(ID_POINT_CLOUD_SPLAT_SYMBOL, OnUpdateToggleSplatSymbol)
	ON_COMMAND(ID_BUTTON_LOD_TEXT, OnDummy)
	ON_COMMAND(ID_BUTTON_SPLAT_TEXT, OnDummy)

	ON_COMMAND(ID_POINT_CLOUD_SPLAT_RENDERING, OnToggleSplat)
	ON_UPDATE_COMMAND_UI(ID_POINT_CLOUD_SPLAT_RENDERING, OnUpdateToggleSplat)
	ON_COMMAND(ID_MATERIAL_SELECTOR, &CSolidHoopsView::OnMaterialSelector)
	ON_COMMAND(ID_CLASHDETECTION_STARTCLASHCALCULATION, &CSolidHoopsView::OnClashdetectionStartclashcalculation)
	ON_COMMAND(ID_TOOLS_CLASHDETECTION_CLASHBROWSER, &CSolidHoopsView::OnToolsClashdetectionClashbrowser)
	ON_COMMAND(ID_TOOLS_SHADEREDITOR, &CSolidHoopsView::OnToolsShadereditor)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsView diagnostics

void CSolidHoopsView::ViewReady()
{
	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	HBaseModel * hmodel = pDoc->GetHoopsModel();

	m_pHView->SetSuppressUpdate(true);
	
	m_pHView->SetSplatRendering(BOOL2bool(CAppSettings::bSplatRendering));
	
	m_pHView->SetFastMarkerDrawing(CAppSettings::bFastMarkers);

	HC_Open_Segment_By_Key(m_pHView->GetShadowMapSegmentKey()); {
		char opt[MVO_BUFFER_SIZE];

		sprintf(opt, "shadow map=(%s, resolution=%d, samples=%d, %s jitter)", 
			CAppSettings::bShadowMap ? "on" : "off",
			CAppSettings::nSMResolution, CAppSettings::nSMSamples, CAppSettings::Jitter ? "" : "no" );

		HC_Set_Rendering_Options(opt);
	} HC_Close_Segment ();

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey()); {
		if(CAppSettings::bShadowMap)
			HC_Set_Visibility ("shadows = (emitting, casting, receiving)");

		char opt[MVO_BUFFER_SIZE]="";
		char refl_opt[MVO_BUFFER_SIZE];

		sprintf(opt, "simple reflection=(%s, opacity=%f, fading= %s, ", 
			CAppSettings::bReflectionPlane ? "on" : "off", 
			CAppSettings::ReflectionOpacity, CAppSettings::bReflectionFading ? "on" : "off");

		if(CAppSettings::ReflectionUseAttenuation)
			sprintf(refl_opt, "attenuation = (hither=%f, yon=%f), ",
				CAppSettings::ReflectionHither, CAppSettings::ReflectionYon);
		else
			sprintf(refl_opt, "no attenuation, ");
		strcat(opt, refl_opt);

		if(CAppSettings::ReflectionUseBlur)
			sprintf(refl_opt, "blur=%d)", CAppSettings::ReflectionBlur);
		else 
			sprintf(refl_opt, "no blur)");
		strcat(opt, refl_opt);		

		HC_Set_Rendering_Options(opt);
	} HC_Close_Segment();

	m_pHView->SetShadowLightDirection(CAppSettings::UseLightVector, &CAppSettings::LightVector);
	m_pHView->SetShadowIgnoresTransparency(CAppSettings::IgnoreTransparency);
	m_pHView->SetShadowMode(CAppSettings::ShadowMode);
	m_pHView->SetOcclusionCullingMode(CAppSettings::OcclusionCulling, true);
 	m_pHView->SetLineAntialiasing(CAppSettings::LineAntialiasing);
	m_pHView->SetTextAntialiasing(CAppSettings::TextAntialiasing);
	SetTransparency();

	//Turn on static model and display lists last, and in that order
	hmodel->SetStaticModel(CAppSettings::StaticModel);

	hmodel->SetLMVModel(CAppSettings::LMVModel);
	
	if (CAppSettings::bRestoreAnnotations)
		m_pHView->SetAnnotationResize(true);



	if(CAppSettings::DisplayList == DisplayListOff)
		m_pHView->SetDisplayListMode(false);
	else 
	{
		m_pHView->SetDisplayListType(CAppSettings::DisplayList);
		m_pHView->SetDisplayListMode(true);
	}

	// Check whether this file contains layout, if yes, load them (applicable to dwg files, and hsfs saved from
	// dwg files)
	bool is_layouts = false;
	is_layouts = HDWGLayoutLoadUtility::CheckForLayoutSegmentInThisModel(m_pHView->GetModelKey());
	if(is_layouts)
	{
		m_pLayoutLoadUtility = new HDWGLayoutLoadUtility(m_pHView);
		m_pLayoutLoadUtility->LoadLayoutList();
	}
	
	m_pHView->SetSuppressUpdate(false);
 }

#ifdef _DEBUG
void CSolidHoopsView::AssertValid() const
{
	CHoopsView::AssertValid();
}

void CSolidHoopsView::Dump(CDumpContext& dc) const
{
	CHoopsView::Dump(dc);
}
#endif //_DEBUG



void CSolidHoopsView::LocalSetOperator(HBaseOperator * NewOperator) 
{
	HBaseOperator * op = GetSolidView()->GetOperator();
	if (op && strcmp(op->GetName(), "HOpCameraWalk") == 0)
		m_WalkSpeed = ((HOpCameraWalk *)op)->GetSpeed();

    GetSolidView()->SetOperator(NewOperator);
	delete op;

	if (m_pDlgKeyframeEditor)
		m_pDlgKeyframeEditor->UpdateButtonStates();
 }


 

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsView message handlers

void CSolidHoopsView::OnFileSaveAs() 
{
#ifdef DISABLE_FILE_SAVE
	AfxMessageBox( _T("File Save has been disabled in this demo.\t\n"), MB_ICONINFORMATION | MB_OK );
	return;
#endif

	CString filter = _T("");
	CString def_ext = _T(".hsf");

#ifdef PARASOLID
	if (((HSolidModel *)(m_pHView->GetModel()))->m_bSolidModel) {
		filter = _T("Parasolid Part file (*.x_t)|*.x_t|ParaHOOPS Stream File (*.psf)|*.psf|");
		def_ext = _T(".x_t");
	}
#endif // PARASOLID

#ifdef ACIS
	if (((HSolidModel *)(m_pHView->GetModel()))->m_bSolidModel) {
		filter = _T("Acis Part file (*.sat)|*.sat|AcisHOOPS Stream File (*.asf)|*.asf|");
		def_ext = _T(".sat");
	}
#endif // ACIS

#ifdef GRANITE
	filter = _T("ProE file (*.prt;*.prt.*)|*.prt;*.prt.*|ProE Assembly (*.asm;*.asm.*)|*.asm;*.asm.*|GraniteHOOPS Stream File (*.gsf)|*.gsf|");
	def_ext = _T(".prt");
#endif // GRANITE


	// this adds file types that have HIO handlers and appear in ProcessFilters()
	CSolidHoopsApp::ProcessFilters(&filter, HDB::GetHIOManager()->GetOutputHandlerTypes());

	filter += _T("HOOPS Animation File (*.bhv)|*.bhv|EMF Enhanced Metafile (*.emf)|*.emf|");
	filter += _T("|");

	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	CFileDialog my_dlg(FALSE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);
	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

	if (my_dlg.DoModal() != IDOK)
		return;
	m_pHView->GetSelection()->DeSelectAll();
	SaveFile( my_dlg.GetPathName());
	CString pathname = my_dlg.GetPathName();
	int end = pathname.ReverseFind('\\');
	pathname.Truncate(end);
	SetCurrentDirectory(pathname);
}


void CSolidHoopsView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	GDIExportInformation options;
	SetupOutputOptions(options, HOutputHandlerStyleHardcopy);

	HC_Open_Segment_By_Key(m_pHView->GetViewKey());{
		VCharArray info(500);
		HC_Show_Device_Info(".", "pixels", info);
		float width = 0, height = 0;
		sscanf(info, "%f,%f", &width, &height);
		options.WindowWidth(width);
		options.WindowHeight(height);
		options.ImageDpi(1);
	}HC_Close_Segment();

	pInfo->m_lpUserData = &options;
	CHoopsView::OnPrint(pDC, pInfo);
}

void CSolidHoopsView::SetupOutputOptions(HOutputHandlerOptions & options, /*HOutputHandlerStyle*/ int style)
{
	switch(style){
	case HOutputHandlerStyleModel:
	case HOutputHandlerStyleDontCare:
	case HOutputHandlerStyleHTML:
	case HOutputHandlerStyleImage:
	{
		if(CAppSettings::ImageOpt == HUseWindowSize){
			VCharArray width_str(128), height_str(128), temp(128), xpixels_str(128);
			HC_Open_Segment_By_Key(m_pHView->GetViewKey());
				/* Get the size in milimeters. */
				HC_Show_Device_Info(".", "size", temp);
				HC_Parse_String(temp, ",", 0, width_str);
				HC_Parse_String(temp, ",", 1, height_str);

				/* Get the pixels in the x direction so we can find DPI. */
				HC_Show_Device_Info(".", "pixels", temp);
				HC_Parse_String(temp, ",", 0, xpixels_str);
			HC_Close_Segment();

			/* Save off the window width and height in inches. */
			options.WindowWidth(atof(width_str)/2.54f);
			options.WindowHeight(atof(height_str)/2.54f);

			/* DPI = xpixels / width in inches; */
			options.ImageDpi(atoi(xpixels_str) / options.WindowWidth());		
		}
		else if(CAppSettings::ImageOpt == HSpecifyImageSize){
			options.WindowWidth(CAppSettings::OutputWidth / 100.0);
			options.WindowHeight(CAppSettings::OutputHeight / 100.0);
			options.ImageDpi(100);

		}
		else {
			MessageBox(
				_T("FIXME: There's an unhandled type in CAppSettings::ImageOpt"),
				_T("FIXME!"),
				MB_OK);

		}
	}break;
	case HOutputHandlerStyleHardcopy:
	{
		if(CAppSettings::DocOpt == HWYSIWYG){
			/* This is the case where we're fitting the hoops window on the
			 * page without changing the aspect ratio. */
			VCharArray width_str(128), height_str(128), temp(128), xpixels_str(128);
			HC_Open_Segment_By_Key(m_pHView->GetViewKey());
				/* Get the size in milimeters. */
				HC_Show_Device_Info(".", "size", temp);
				HC_Parse_String(temp, ",", 0, width_str);
				HC_Parse_String(temp, ",", 1, height_str);

				/* Get the pixels in the x direction so we can find DPI. */
				HC_Show_Device_Info(".", "pixels", temp);
				HC_Parse_String(temp, ",", 0, xpixels_str);
			HC_Close_Segment();

			/* Save off the window width and height in inches. */
			options.WindowWidth(atof(width_str)/2.54f);
			options.WindowHeight(atof(height_str)/2.54f);

			/* DPI = xpixels / width in inches; */
			options.ImageDpi(atoi(xpixels_str) / options.WindowWidth());		
		}
		else if(CAppSettings::DocOpt == HUseWholePage){
			/* This is the case where we're going to expand the window in such a way
			 * that everything that is visible in the HOOPS view will be visible on
			 * the page, but additionally, we're expanding the window so the whole
			 * page will be used. */
			options.WindowWidth(CAppSettings::PaperWidth / 100.0);
			options.WindowHeight(CAppSettings::PaperHeight / 100.0);
			options.ImageDpi(100);

		}
		else {
			MessageBox(
				_T("FIXME: There's an unhandled type in CAppSettings::ImageOpt"),
				_T("FIXME!"),
				MB_OK);

		}
	}break;
	default:
	{
		MessageBox(
			_T("FIXME: There's an unhandled type in SetupOutputOptions"),
			_T("FIXME!"),
			MB_OK);
	}break;
	}

	options.PaperWidth(CAppSettings::PaperWidth);
	options.PaperHeight(CAppSettings::PaperHeight);
	options.PaperDpi(CAppSettings::DPI);

	if(CAppSettings::DocOpt == HWYSIWYG){
		options.UseSubscreen(true);
	}
	else if(CAppSettings::DocOpt == HUseWholePage){
		options.UseSubscreen(false);
	}
	else {
		MessageBox(
			_T("FIXME: There's an unhandled type in CAppSettings::DocOpt"),
			_T("FIXME!"),
			MB_OK);
	}

	options.UseWindowColor(CAppSettings::bUseWindowColor);
	options.ForceGrayscale(CAppSettings::ForceGrayscale);
	options.ConserveMemory(CAppSettings::bConserveMemory);
	options.View(m_pHView);
}

void CSolidHoopsView::OnEditCopy() 
{
	GDIExportInformation options;

	SetupOutputOptions(options, HOutputHandlerStyleImage);

	options.deviceContext = GetDC()->GetSafeHdc();
	options.attribDC = GetDC()->m_hAttribDC;
	options.windowID = (void*)m_hWnd;
	options.rasterOutput = m_bFastPrint;
	options.clipBoard= true;

	EditCopy(&options);
}

class MyPDFOptions : public HPDFOptions
{
	CSolidHoopsView * m_pView;
public:
	MyPDFOptions(HOutputHandlerOptions const & o, CSolidHoopsView * v) : HPDFOptions(), m_pView(v)
	{
		Init(&o);
	}

	bool PopulateOptions()
	{
		HPDFOptions::PopulateOptions(); // This will fill in default values;
		U3dOptions().ExportAnnotations(true);
		U3dOptions().ExportLines(true);
		
		NativeFileName((wchar_t const*)H_WCS(m_pView->GetDocument()->GetPathName()).encodedText());
		CPDFExportDlg dlg((wchar_t const*)H_WCS(m_pView->GetDocument()->GetPathName()).encodedText());
		came_from_adobe(dlg.came_from_adobe());
		if(dlg.DoModal(this) != IDOK)
			return false;
		return true;
	}
};

/* We could use _wunlink and _wrename, but that sometimes will delete
   the real file, make a backup, and leave to real file (if the user
   cancels for example).  Making a real copy is the simplest way (and
   hopefully won't be too slow. */
static void backup_file( LPCTSTR csFilePathName )
{
	H_WCS backup_name(csFilePathName);
	backup_name.append("~");

	FILE * in = wfopen(csFilePathName, L"rb");
	FILE * out = 0;
	if(in) {
		/* If there's no in file, there's nothing to backup so don't open
		   the backup file as the data will be blown away. */
		out = wfopen(backup_name.encodedText(), L"wb");
	}
	
	if(in && out){
		char buffer[1024*8];
		size_t count = fread(buffer, 1, sizeof(buffer), in);
		while(count > 0){
			fwrite(buffer, 1, count, out);
			count = fread(buffer, 1, sizeof(buffer), in);
		}
	}

	if(in)
		fclose(in);
	if(out)
		fclose(out);
}

void CSolidHoopsView::MakeAndSetThumbnail(HStreamFileToolkit * mytool)
{
	HC_Open_Segment("/");{
		HC_KEY tmpseg = HC_KOpen_Segment("");{
			// http://msdn.microsoft.com/en-us/library/bb761846(VS.85).aspx suggest size should be 160
			// but we're going to make it 255.
			int const size = 255;
			HC_KEY image_key = HC_KInsert_Image(0, 0, 0, "rgba", size, size, 0);
			HUtility::MakeViewSnapshot(m_pHView, image_key);
			unsigned char const * rgba_image = 0;
			HC_Show_Geometry_Pointer(image_key, "rgba rasters", &rgba_image);
			unsigned char * rgb_image = new unsigned char[size * size * 3];
			for(int i = 0; i < size * size; ++i){
				rgb_image[3*i + 0] = rgba_image[4*i + 0]; 
				rgb_image[3*i + 1] = rgba_image[4*i + 1]; 
				rgb_image[3*i + 2] = rgba_image[4*i + 2]; 
			}
			mytool->SetThumbnail(TKO_Thumbnail_RGB, size, size, rgb_image);
			delete [] rgb_image;
		}HC_Close_Segment();
		HC_Delete_By_Key(tmpseg);
	}HC_Close_Segment();
}

bool CSolidHoopsView::SaveFile( LPCTSTR csFilePathName )
{
	assert( CString(csFilePathName).IsEmpty() == FALSE );

	int sflags = 0;
	HFileOutputResult result = OutputFail;
	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	HSolidModel* pSolidModel = ((HSolidModel *)m_pHView->GetModel());

	HC_Control_Update_By_Key (m_pHView->GetViewKey(), "redraw everything");
	m_pHView->Update();

	TCHAR extension[MVO_BUFFER_SIZE];
	HUtility::FindFileNameExtension(csFilePathName, extension);

	HOutputHandlerOptions options;

 	if (_tcsieq(extension, _T("emf")))
	{
		SetupOutputOptions(options, HOutputHandlerStyleImage);
		options.UseWindowColor(true);
		backup_file(csFilePathName);
		SaveEMF(H_ASCII_TEXT(csFilePathName), &options);
		AfxGetApp()->AddToRecentFileList(csFilePathName);
		return true;
	}

	if(_tcsicmp(csFilePathName, _T("")))
	{
		if (_tcsieq(extension, _T("hsf")) ||
			_tcsieq(extension, _T("html")) ||
			_tcsieq(extension, _T("htm")) ||
			_tcsieq(extension, _T(KERN_STREAM_FILE)) ||
			_tcsieq(extension, _T("hsf+"))) // Write HOOPS Stream File	
		{
			HC_Open_Segment_By_Key(m_pHView->GetModelKey());
			HStreamFileToolkit *mytool = new HStreamFileToolkit;

			if(_tcsieq(extension, _T("html")) || _tcsieq(extension, _T("htm"))){
				SetupOutputOptions(options, HOutputHandlerStyleHTML);
				options.WindowWidth(70);
				options.WindowHeight(70);
			} else {
				SetupOutputOptions(options, HOutputHandlerStyleModel);
			}
			options.ExtendedData(mytool);
			options.Version(mytool->GetTargetVersion());
			mytool->SetPrewalkHandler(new PartviewerHSFExtras(this));
			if (HDB::GetMaterialLibrary() != NULL) {
				HMaterialLibrary *hmat = HDB::GetMaterialLibrary(); 
				hmat->SetWriteFlags( (CAppSettings::EmbedMaterials ? 
					HMaterialLibrary::Embedded : HMaterialLibrary::Write_Flags_Default) ) ;
				mytool->SetPrewalkHandler(new HTK_Material_Composite(hmat, m_pHView->GetModelKey()));
			}
			if(CAppSettings::EmbedHSFThumbnail){
				MakeAndSetThumbnail(mytool);
			}

 			HBhvUtility::SetupAnimationWriteFromHSF(mytool, m_pHView->GetModel());

#ifndef HOOPS_ONLY
			if( pSolidModel->m_bSolidModel )
			{
				HC_Set_User_Value(1L);

				if (CAppSettings::bExportTopolInfo || _tcsieq(extension, _T(KERN_STREAM_FILE)) || _tcsieq(extension, _T("hsf+")))
				{ 
 					mytool->SetOpcodeHandler (TKE_Circle,			    new TK_PSCircle (TKE_Circle));
					mytool->SetOpcodeHandler (TKE_Circular_Arc,         new TK_PSCircle (TKE_Circular_Arc));
					mytool->SetOpcodeHandler (TKE_Circular_Chord,       new TK_PSCircle (TKE_Circular_Chord));
					mytool->SetOpcodeHandler (TKE_Circular_Wedge,       new TK_PSCircle (TKE_Circular_Wedge));
					mytool->SetOpcodeHandler (TKE_Ellipse,              new TK_PSEllipse (TKE_Ellipse));
					mytool->SetOpcodeHandler (TKE_Elliptical_Arc,       new TK_PSEllipse (TKE_Elliptical_Arc));
					mytool->SetOpcodeHandler (TKE_Line,                 new TK_PSLine);
					mytool->SetOpcodeHandler (TKE_Polyline,             new TK_PSPolypoint (TKE_Polyline));
					mytool->SetOpcodeHandler (TKE_PolyPolyline,         new TK_PSPolyPolypoint (TKE_PolyPolyline));
					mytool->SetOpcodeHandler (TKE_Close_Segment,		new TK_PSClose_Segment);
					mytool->SetOpcodeHandler (TKE_Marker,				new TK_PSPoint(TKE_Marker));
					mytool->SetOpcodeHandler (TKE_NURBS_Curve,			new TK_PSNURBS_Curve);

					mytool->SetPrewalkHandler(new TK_PSComment(pSolidModel));
#ifdef PARASOLID
					if (_tcsieq(extension, _T("psf")))
						mytool->SetPostwalkHandler (new TK_PSUser_Data(&pSolidModel->m_mi, pSolidModel->GetPartition(),1));
					else
						mytool->SetPostwalkHandler (new TK_PSUser_Data(&pSolidModel->m_mi, pSolidModel->GetPartition(),0));
#endif // PARASOLID
#ifndef HOOPS_ONLY
					if (_tcsieq(extension, _T("hsf+")))
					{
					    pSolidModel->SetupModelStructureWriteFromHSF(mytool);
					    sflags |= TK_Force_Tags;
					}
#endif // HOOPS_ONLY

#ifdef ACIS
					if (_tcsieq(extension, _T("asf")))
						mytool->SetPostwalkHandler (new TK_PSUser_Data(pSolidModel, &pSolidModel->m_mi, pSolidModel->GetEntityList(),1));
					else
						mytool->SetPostwalkHandler (new TK_PSUser_Data(pSolidModel, &pSolidModel->m_mi, pSolidModel->GetEntityList(), 0));
#endif // ACIS
#ifdef GRANITE
					if (_tcsieq(extension, _T("gsf")))
						mytool->SetPostwalkHandler (new TK_PSUser_Data(&pSolidModel->m_mi, pSolidModel->GetComponentList(),1));
					else
						mytool->SetPostwalkHandler (new TK_PSUser_Data(&pSolidModel->m_mi, pSolidModel->GetComponentList(), 0));
#endif // GRANITE

				}
				else if (!CAppSettings::bExportLines) 
				{
					mytool->SetOpcodeHandler (TKE_Circle,0);
					mytool->SetOpcodeHandler (TKE_Circular_Arc,0);
					mytool->SetOpcodeHandler (TKE_Circular_Chord,0);
					mytool->SetOpcodeHandler (TKE_Circular_Wedge,0);
					mytool->SetOpcodeHandler (TKE_Ellipse,0);
					mytool->SetOpcodeHandler (TKE_Elliptical_Arc,0);
					mytool->SetOpcodeHandler (TKE_Line,0);
					mytool->SetOpcodeHandler (TKE_Polyline,0);
					mytool->SetOpcodeHandler (TKE_PolyPolyline,0);
					HC_UnSet_User_Value();
				}
			

			}
#endif // HOOPS_ONLY

  
			if (!CAppSettings::bCompressVertices)
				sflags |= TK_Full_Resolution_Vertices;
			else
				mytool->SetNumVertexBits(CAppSettings::NumVertexBits);

			if (!CAppSettings::bCompressNormals)
				sflags |= TK_Full_Resolution_Normals;
			else
				mytool->SetNumNormalBits(CAppSettings::NumNormalBits);

			if (!CAppSettings::bCompressParameters)
				sflags |= TK_Full_Resolution_Parameters;
			else
				mytool->SetNumParameterBits(CAppSettings::NumParameterBits);


			if (CAppSettings::bExportDictionary == true)
				sflags |= TK_Generate_Dictionary;


			if (CAppSettings::bEnableInstancing == false)
				sflags |= TK_Disable_Instancing;

			if (CAppSettings::bSaveLogFile == true)
				mytool->SetLogging(true);
			else
				mytool->SetLogging(false);

			if (CAppSettings::bCompressConnectivity == true)
				sflags |= TK_Connectivity_Compression;

			if (!CAppSettings::EnableTristrips)
				sflags |= TK_Disable_Tristrips;

   
			// This is a paradox here, the flags passed as argument to Write_Stream function make
			// no sense if we use our own toolkit. These flags need to be set on the toolkit itself
			mytool->SetWriteFlags(sflags);

			// Anything <= 0 for export version means use the default.
			if( CAppSettings::HsfExportVersion > 0 )
			{
				mytool->SetTargetVersion(CAppSettings::HsfExportVersion);
				options.m_Version = mytool->GetTargetVersion();
			}


			HStreamProgressDlg*  progress_bar = new HStreamProgressDlg(mytool, HStreamWrite );
			progress_bar->Create(this, _T("Writing Stream File"), TRUE);
		
			HOutputHandler* hio_hsf = HDB::GetHIOManager()->GetOutputHandler("hsf");
		
			if(_tcsieq(extension, _T("html"))){
				HOutputHandler * extra_handler = HDB::GetHIOManager()->GetOutputHandler("html");
				if(extra_handler){
					backup_file(csFilePathName);
					result = extra_handler->FileOutputByKey(csFilePathName, m_pHView->GetModelKey(), &options);
					if(result == OutputOK){
						TCHAR hsf_name[MVO_BUFFER_SIZE];
						TCHAR FileName[MVO_BUFFER_SIZE];
						_tcscpy(FileName, (csFilePathName));
						size_t n = _tcslen(FileName);
						while (n && FileName[n] != _T('.')) n--;
						_tcsncpy(hsf_name, FileName, n);
						hsf_name[n] = _T('\0');
						_tcscat(hsf_name, _T(".hsf"));
						backup_file(hsf_name);
						result = hio_hsf->FileOutputByKey(hsf_name, m_pHView->GetModelKey(), &options);
					}
				}
			}
			else
			{
				backup_file(csFilePathName);
				result = hio_hsf->FileOutputByKey( csFilePathName, m_pHView->GetModelKey(), &options);
			}

			// delete the partially written file if user cancelled
			if( progress_bar->Cancelled() )
			{
				DeleteFile(csFilePathName);
				result = OutputOK;
			}

			// NOTE: delete progress bar before mytool because it is holding the reference
			delete progress_bar;
			delete mytool;
			
			HC_Close_Segment();
		}
		else if (_tcsieq(extension, _T("bhv")))
		{
			SetupOutputOptions(options, HOutputHandlerStyleDontCare);
			HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
 			backup_file(csFilePathName);
			pBehaviorManager->WriteToFile((csFilePathName));
			return true;
		}
		else if (_tcsieq(extension, _T("dwf")))
		{
			SetupOutputOptions(options, HOutputHandlerStyleHardcopy);
			CDWFExportOptionsDlg dwf_opts_dlg( &options );
			if (dwf_opts_dlg.DoModal() == IDOK)
			{
				char modelName[MVO_BUFFER_SIZE];
				if(options.m_b3dOutput==true)
					strcpy(modelName, "HOOPS 3D Partviewer: 3D Model");
				else
					strcpy(modelName, "HOOPS 3D Partviewer: 2D Model");
				options.m_pDWFModelName = modelName;

				backup_file(csFilePathName);
				result = pDoc->m_pHoopsModel->WriteWithOptions((csFilePathName), m_pHView, &options );
			}
		}
		else if (_tcsieq(extension, _T("pdf")))
		{
			SetupOutputOptions(options, HOutputHandlerStyleHardcopy);
			MyPDFOptions pdf_export_opts(options, this);
			pdf_export_opts.m_pPRCAsmModelFile = ((HSolidModel *)pDoc->m_pHoopsModel)->m_pPRCAsmModelFile;
			backup_file(csFilePathName);
			result = pDoc->m_pHoopsModel->WriteWithOptions(csFilePathName, m_pHView, &pdf_export_opts );
			TCHAR const * fn = 0;
			if(_tcsrchr(csFilePathName, _T('\\')))
				fn = _tcsrchr(csFilePathName, _T('\\')) +1;
			else if(_tcsrchr(csFilePathName, _T('/')))
				fn = _tcsrchr(csFilePathName, _T('/')) +1;
			else
				fn = csFilePathName;
		}
		else if (_tcsieq(extension, _T("iges")) || _tcsieq(extension, _T("step")) || _tcsieq(extension, _T("x_t")))
		{
			options.m_pExtendedData = ((HSolidModel *)pDoc->m_pHoopsModel)->m_pPRCAsmModelFile;
			backup_file(csFilePathName);
			result = pSolidModel->WriteWithOptions(csFilePathName, m_pHView, &options);
		}
		else  // call overloaded WriteWithOptions in HSolidModel to handle solid modeller types
		{
			SetupOutputOptions(options, HOutputHandlerStyleImage);
			backup_file(csFilePathName);
			result = pSolidModel->WriteWithOptions((csFilePathName), m_pHView, &options);
		}
	
		if(result == OutputOK){
			if ( !(_tcsieq(extension, _T("emf")) || _tcsieq(extension, _T("hpgl")) || _tcsieq(extension, _T("htm")) || 
				_tcsieq(extension, _T("html")) || _tcsieq(extension, _T("cgm")) || _tcsieq(extension, _T("pdf")) || 
				_tcsieq(extension, _T("ps"))))
				AfxGetApp()->AddToRecentFileList(csFilePathName);
		}
		else {
			H_WCS msg;
			msg.format(L"Saving %ls failed.", H_UNICODE_TEXT(csFilePathName));
			MessageBoxW(msg.encodedText(), _T("Error!"), MB_OK);
		}
	}
	return result == OutputOK;
}

// resets the camera to view the world space extents of the model
void CSolidHoopsView::OnZoomToExtents() 
{
	m_pHView->ZoomToExtents();
	if (m_pHView->GetRenderMode()==HRenderHiddenLine)		
		((HSolidView *)m_pHView)->UpdateHiddenLine(); 

    m_pHView->Update();

}


void CSolidHoopsView::OnQuery()
{
	bool advanced = false;

	//If one of the dialogs is visible, use it.  If not, let the shift key decide
	if (m_advanced_query_dialog->IsWindowVisible())
		advanced = true;
	else if (m_query_dialog->IsWindowVisible())
		advanced = false;
	else if (GetAsyncKeyState(VK_SHIFT) & 32768)
		advanced = true;

	if (advanced)
		LocalSetOperator(new HSQueryAdvanced(m_pHView));
	else
		LocalSetOperator(new HSQuery(m_pHView));
	((HSQuery*)m_pHView->GetOperator())->SetSolidHoopsView(this);
}


void CSolidHoopsView::OnUpdateQuery(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (1);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(),"Query"))
		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
}


void CSolidHoopsView::OnSubtract() 
{
#ifdef PARASOLID
    GetSolidView()->BooleanOperation(PK_boolean_subtract_c);
#endif // PARASOLID
#ifdef ACIS
	GetSolidView()->BooleanOperation(HA_OPERATION_SUBTRACT);
#endif // ACIS
#ifdef GRANITE
	GetSolidView()->BooleanOperation(KINTERSECT_SUBTRACT);
#endif // GRANITE

}

void CSolidHoopsView::OnUnion() 
{
#ifdef PARASOLID
	GetSolidView()->BooleanOperation(PK_boolean_unite_c);
#endif // PARASOLID
#ifdef ACIS
	GetSolidView()->BooleanOperation(HA_OPERATION_UNITE);
#endif // ACIS
#ifdef GRANITE
	GetSolidView()->BooleanOperation(KINTERSECT_ADD);
#endif // GRANITE

}


void CSolidHoopsView::OnIntersect() 
{
#ifdef PARASOLID
	GetSolidView()->BooleanOperation(PK_boolean_intersect_c);
#endif // PARASOLID
#ifdef ACIS
	GetSolidView()->BooleanOperation(HA_OPERATION_INTERSECT);
#endif // ACIS
#ifdef GRANITE
	GetSolidView()->BooleanOperation(KINTERSECT_CUT);
#endif // GRANITE
}

 
void CSolidHoopsView::OnZoom() 
{         
    LocalSetOperator(new HSOpCameraZoom(m_pHView));  
}

void CSolidHoopsView::OnZoomToWindow() 
{
    LocalSetOperator(new HSOpCameraZoomBox(m_pHView));
	((HOpCameraZoomBox *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CSolidHoopsView::OnOrbit() 
{

    LocalSetOperator(new HOpCameraManipulate(m_pHView, 0,1, new HSOpCameraOrbit(m_pHView), new HSOpCameraPan(m_pHView),
			    new HSOpCameraZoom(m_pHView), 0,false));	
 //	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
}

void CSolidHoopsView::OnTurntable() 
{
    LocalSetOperator(new HOpCameraOrbitTurntable(m_pHView));	
}



void CSolidHoopsView::OnPan() 
{      
	LocalSetOperator(new HSOpCameraPan(m_pHView));      
}



void CSolidHoopsView::OnApertureSelect() 
{
#if defined(HOOPS_ONLY)
	LocalSetOperator(new HOpSelectAperture(m_pHView));
#else
	LocalSetOperator(new HSOpSelectAperture(m_pHView));
#endif // HOOPS_ONLY
}

void CSolidHoopsView::OnWindowSelect() 
{
#if defined(HOOPS_ONLY)
    LocalSetOperator(new HOpSelectArea(m_pHView));
#else
    LocalSetOperator(new HSOpSelectArea(m_pHView));
#endif // HOOPS_ONLY
}


// FindMenuItem() will find a menu item string from the specified
// popup menu and returns its position (0-based) in the specified 
// popup menu. It returns -1 if no such menu item string is found.
int CSolidHoopsView::FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
   ASSERT(Menu);
   ASSERT(::IsMenu(Menu->GetSafeHmenu()));

   int count = Menu->GetMenuItemCount();
   for (int i = 0; i < count; i++)
   {
      CString str;
      if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         (_tcscmp(str, MenuString) == 0))
         return i;
   }

   return -1;
}

void CSolidHoopsView::OnMButtonDblClk(UINT nFlags, CPoint point) 
{

    
    HC_KEY key = -1;
    int offset1,offset2,offset3;

    HPoint localpixels, localwindow;
    localpixels.Set((float)point.x,(float) point.y, 0);
 
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());

    HC_Compute_Coordinates(".", "local pixels", &localpixels, "local window", &localwindow);
    HC_Close_Segment();
    HC_Open_Segment_By_Key(m_pHView->GetViewKey());
    if ( HC_Compute_Selection(".","./scene/overwrite","v", localwindow.x, localwindow.y))
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
    if (HUtility::IsModelKey(m_pHView->GetModelKey(),key))
        m_pHView->FitSelection(key);
    }
    else
	m_pHView->ZoomToExtents();

    m_pHView->Update();
    
	CView::OnMButtonDblClk(nFlags, point);


}
 

// OnRButtonDown activates the popup menu which enables visibility and selection control
void CSolidHoopsView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_pHView->GetConstantFrameRateObject()->SetDisableIncreaseTemp(true);
 
	HBaseOperator *op = m_pHView->GetCurrentOperator();

	if (op)
	{
		if (op->OperatorStarted())
		{
			CHoopsView::OnRButtonDown(nFlags, point);
			return;
		}
	}

	CMenu parent_menu;	
    CMenu * popup_menu;
	CRect   rect;
    CPoint  new_menu_position;

 	HSolidView * pHView = GetSolidView();

	int pos;
	(void) pos;

#ifdef PARASOLID
	UINT popup_menu_id = IDR_VIEW_POPUP;
#endif // PARASOLID
#ifdef ACIS
	UINT popup_menu_id = IDR_VIEW_POPUP1;
#endif // ACIS
#ifdef GRANITE
	UINT popup_menu_id = IDR_VIEW_POPUP2;
#endif // GRANITE
#ifdef HOOPS_ONLY
	UINT popup_menu_id = IDR_VIEW_POPUP3;
#endif // HOOPS_ONLY

    parent_menu.LoadMenu (popup_menu_id);
    // Get a pointer to the menu
	popup_menu = parent_menu.GetSubMenu (0);

	KERN_CLASS_TYPEDEF class_type;
	class_type = ((HSSelectionSet *)pHView->GetSelection())->GetSelectLevel();

#ifdef PARASOLID
	// For Parasolid x_t files, we support precise hidden line. So, rename the 
	// hidden line menu to precise hidden line
	if (((HSolidModel *)(pHView->GetModel()))->m_bSolidModel)
	{
		int pos_hid = FindMenuItem(popup_menu, _T("&Render Mode"));
		if (pos_hid != -1)
		{
		   CMenu* rend_submenu = popup_menu->GetSubMenu(pos_hid);

		   pos_hid = FindMenuItem(rend_submenu, _T("Hidden Line"));
		   if (pos_hid > -1)
		   {
				UINT id = rend_submenu->GetMenuItemID(pos_hid);
				rend_submenu->ModifyMenu(id, MF_BYCOMMAND, id, _T("Precise Hidden Line"));
		   }
		}
	}
#endif // PARASOLID


#ifndef _DEBUG

 // now, look for "Selection level" menu.
   pos = FindMenuItem(popup_menu, _T("Window"));
   popup_menu->DeleteMenu(pos, MF_BYPOSITION);
   popup_menu->DeleteMenu(pos, MF_BYPOSITION);

#endif
 
     // Display the menu at the mouse click position.
 
    GetWindowRect(&rect);

    // Transform the screen coordinate point to a window-relative point.
    new_menu_position = CPoint (rect.left + point.x, rect.top + point.y);
	if (pHView->GetVisibilityMarkersOnly())
#if defined(ACIS) || defined(PARASOLID)
		popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_VERTICES, MF_BYCOMMAND | MF_CHECKED);
#else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_MARKERS_ONLY, MF_BYCOMMAND | MF_CHECKED);  
#endif
    else
#if defined(ACIS) || defined(PARASOLID)
		popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_VERTICES, MF_BYCOMMAND | MF_UNCHECKED);
#else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_MARKERS_ONLY, MF_BYCOMMAND | MF_UNCHECKED);
#endif
#if !defined(ACIS) && !defined(PARASOLID)
	if (pHView->GetVisibilityVertices())
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_VERTICES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_VERTICES, MF_BYCOMMAND | MF_UNCHECKED);
#endif


	if (pHView->GetVisibilityFaces())
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_FACES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_FACES, MF_BYCOMMAND | MF_UNCHECKED);

	if (pHView->GetVisibilityEdges())
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_HOOPS_EDGES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_HOOPS_EDGES, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_edges)
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_BREP_EDGES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_BREP_EDGES, MF_BYCOMMAND | MF_UNCHECKED);

	if (pHView->GetVisibilityLines())
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_LINES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_LINES, MF_BYCOMMAND | MF_UNCHECKED);

#if 0
	if (pHView->GetVisibilityMarkers())
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_MARKERS, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_MARKERS, MF_BYCOMMAND | MF_UNCHECKED);
#endif

	if (m_lights)
        popup_menu->CheckMenuItem(ID_LIGHTS, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_LIGHTS, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_text)
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_TEXT, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_TEXT, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_images)
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_IMAGES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_IMAGES, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_grids)
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_GRIDS, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_GRIDS, MF_BYCOMMAND | MF_UNCHECKED);


	if (pHView->GetCPFaceVisibility())
        popup_menu->CheckMenuItem(ID_CAPPING_PLANES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_CAPPING_PLANES, MF_BYCOMMAND | MF_UNCHECKED);

	if (pHView->GetCPLineVisibility())
        popup_menu->CheckMenuItem(ID_CAPPING_LINES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_CAPPING_LINES, MF_BYCOMMAND | MF_UNCHECKED);


	if ((m_pHView->GetRenderMode() != HRenderHiddenLine) && (m_pHView->GetRenderMode() != HRenderHiddenLineHOOPS)
		&& (m_pHView->GetRenderMode() != HRenderBRepHiddenLine) && (m_pHView->GetRenderMode() != HRenderBRepHiddenLineFast))
        popup_menu->EnableMenuItem(ID_TOOLS_VISIBILITY_HIDDENLINES, MF_GRAYED); 

	if (m_hidden_lines_visible)
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_HIDDENLINES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_VISIBILITY_HIDDENLINES, MF_BYCOMMAND | MF_UNCHECKED);


	if (m_pHView->GetRenderMode() == HRenderFlat)
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_FLATSHADED, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_FLATSHADED, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_pHView->GetRenderMode() == HRenderGouraud)
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_GOURAUDSHADED, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_GOURAUDSHADED, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_pHView->GetRenderMode() == HRenderTriangulation)
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_TRIANGULATION, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_TRIANGULATION, MF_BYCOMMAND | MF_UNCHECKED);

   	if (m_pHView->GetRenderMode() == HRenderPhong)
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_PHONGSHADED, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_PHONGSHADED, MF_BYCOMMAND | MF_UNCHECKED);
	
	if (m_pHView->GetRenderMode() == HRenderWireframe)
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_WIREFRAME, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_WIREFRAME, MF_BYCOMMAND | MF_UNCHECKED);	

	if (m_pHView->GetRenderMode() == HRenderGouraudWithLines) 
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDWITHLINES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDWITHLINES, MF_BYCOMMAND | MF_UNCHECKED);	

	if ((m_pHView->GetRenderMode() == HRenderHiddenLine))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_HIDDENLINE, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_HIDDENLINE, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderSilhouette))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SILHOUETTE, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SILHOUETTE, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderWireframeWithSilhouette))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_WIREFRAMEWITHSILHOUETTE, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_WIREFRAMEWITHSILHOUETTE, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderGoochShaded))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_GOOCHSHADED, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_GOOCHSHADED, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderShadedWireframe))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDWIREFRAME, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDWIREFRAME, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderShadedWireframe))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDWIREFRAME, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDWIREFRAME, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderBRepHiddenLine))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_BREPHIDDENLINE, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_BREPHIDDENLINE, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderBRepWireframe))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_BREPWIREFRAME, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_BREPWIREFRAME, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderFakeHiddenLine))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_FAKEHIDDENLINE, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_FAKEHIDDENLINE, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderVertices))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_VERTICES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_VERTICES, MF_BYCOMMAND | MF_UNCHECKED);

	if ((m_pHView->GetRenderMode() == HRenderShadedVertices))
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDVERTICES, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TOOLS_RENDERMODE_SHADEDVERTICES, MF_BYCOMMAND | MF_UNCHECKED);


	if (m_color_index_int)
        popup_menu->CheckMenuItem(ID_COLOR_INDEX_INTERPOLATION, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_COLOR_INDEX_INTERPOLATION, MF_BYCOMMAND | MF_UNCHECKED);

	if (m_color_int)
        popup_menu->CheckMenuItem(ID_COLOR_INTERPOLATION, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_COLOR_INTERPOLATION, MF_BYCOMMAND | MF_UNCHECKED);


	char transforms[MVO_BUFFER_SIZE];
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		//HC_Show_One_Text_Font("name", name);
		HC_Show_One_Net_Text_Font("transforms", transforms);
	HC_Close_Segment();

	if (streq("on", transforms))
        popup_menu->CheckMenuItem(ID_TEXT_TRANSFORMS, MF_BYCOMMAND | MF_CHECKED);  
    else
        popup_menu->CheckMenuItem(ID_TEXT_TRANSFORMS, MF_BYCOMMAND | MF_UNCHECKED);

//	if (streq("roman", name))
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_FONTS_ROMAN, MF_BYCOMMAND | MF_CHECKED);  
//    else
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_FONTS_ROMAN, MF_BYCOMMAND | MF_UNCHECKED);
//
//	if (streq("cave.pfa", name))
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_FONTS_CAVE, MF_BYCOMMAND | MF_CHECKED);  
//    else
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_FONTS_CAVE, MF_BYCOMMAND | MF_UNCHECKED);
//
//	if (streq("arial.ttf", name))
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_FONTS_ARIAL, MF_BYCOMMAND | MF_CHECKED);  
//    else
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_FONTS_ARIAL, MF_BYCOMMAND | MF_UNCHECKED);
//
//	if (streq("on", transforms))
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_TRANSFORMS_ON, MF_BYCOMMAND | MF_CHECKED);  
//    else
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_TRANSFORMS_ON, MF_BYCOMMAND | MF_UNCHECKED);
//
//	if (streq("character position only", transforms))
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_TRANSFORMS_CHARACTERPOSITIONONLY, MF_BYCOMMAND | MF_CHECKED);  
//    else
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_TRANSFORMS_CHARACTERPOSITIONONLY, MF_BYCOMMAND | MF_UNCHECKED);
//
//		if (streq("off", transforms))
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_TRANSFORMS_OFF, MF_BYCOMMAND | MF_CHECKED);  
//    else
//        popup_menu->CheckMenuItem(ID_TOOLS_TEXT_TRANSFORMS_OFF, MF_BYCOMMAND | MF_UNCHECKED);

    popup_menu->CheckMenuItem(ID_EDGE, MF_BYCOMMAND | MF_UNCHECKED);
	popup_menu->CheckMenuItem(ID_FACE, MF_BYCOMMAND | MF_UNCHECKED);
	popup_menu->CheckMenuItem(ID_BODY, MF_BYCOMMAND | MF_UNCHECKED);


#ifdef HOOPS_ONLY
	if	(class_type == SEGMENT_TYPE)
		popup_menu->CheckMenuItem(ID_SEGMENT_SELECT_LEVEL, MF_BYCOMMAND | MF_CHECKED);
	else
		popup_menu->CheckMenuItem(ID_SEGMENT_SELECT_LEVEL, MF_BYCOMMAND | MF_UNCHECKED);

	if	(class_type == ENTITY_TYPE)
		popup_menu->CheckMenuItem(ID_ENTITY_SELECT_LEVEL, MF_BYCOMMAND | MF_CHECKED);
	else
		popup_menu->CheckMenuItem(ID_ENTITY_SELECT_LEVEL, MF_BYCOMMAND | MF_UNCHECKED);

	if	(class_type == SUBENTITY_TYPE)
	{
		popup_menu->CheckMenuItem(ID_SUBENTITY_SELECT_LEVEL, MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		popup_menu->CheckMenuItem(ID_SUBENTITY_SELECT_LEVEL, MF_BYCOMMAND | MF_UNCHECKED);
		popup_menu->EnableMenuItem(ID_SUBENTITY_FACES, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_SUBENTITY_EDGES, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_SUBENTITY_VERTICES, MF_GRAYED);
	}

	if	(pHView->GetSelection()->GetSubentityFaceSelection())
		popup_menu->CheckMenuItem(ID_SUBENTITY_FACES, MF_BYCOMMAND | MF_CHECKED);
	else
		popup_menu->CheckMenuItem(ID_SUBENTITY_FACES, MF_BYCOMMAND | MF_UNCHECKED);

	if	(pHView->GetSelection()->GetSubentityEdgeSelection())
		popup_menu->CheckMenuItem(ID_SUBENTITY_EDGES, MF_BYCOMMAND | MF_CHECKED);
	else
		popup_menu->CheckMenuItem(ID_SUBENTITY_EDGES, MF_BYCOMMAND | MF_UNCHECKED);

	if	(pHView->GetSelection()->GetSubentityVertexSelection())
		popup_menu->CheckMenuItem(ID_SUBENTITY_VERTICES, MF_BYCOMMAND | MF_CHECKED);
	else
		popup_menu->CheckMenuItem(ID_SUBENTITY_VERTICES, MF_BYCOMMAND | MF_UNCHECKED);
#else
	if (class_type == KERN_EDGE_TYPE)	
		popup_menu->CheckMenuItem(ID_EDGE, MF_BYCOMMAND | MF_CHECKED);
	else if (class_type == KERN_FACE_TYPE)	
		popup_menu->CheckMenuItem(ID_FACE, MF_BYCOMMAND | MF_CHECKED);
	else if (class_type == KERN_BODY_TYPE)	
		popup_menu->CheckMenuItem(ID_BODY, MF_BYCOMMAND | MF_CHECKED);
	else if (class_type == KERN_VERTEX_TYPE)	
		popup_menu->CheckMenuItem(ID_VERTEX, MF_BYCOMMAND | MF_CHECKED);
#ifdef PARASOLID
	else if (class_type == PK_CLASS_assembly)	
		popup_menu->CheckMenuItem(ID_ASSEMBLY, MF_BYCOMMAND | MF_CHECKED);
#endif // PARASOLID
#ifdef ACIS
	else if (class_type == KERN_INSTANCE_TYPE)	
		popup_menu->CheckMenuItem(ID_ASSEMBLY, MF_BYCOMMAND | MF_CHECKED);
#endif // ACIS

#ifdef INTEROP
	InterOpFileIO *iop_fio = ((HSolidModel *)m_pHView->GetModel())->GetInterOpFileIOHandler();
	if (iop_fio->GetConvertAsmParts() == false) {
		// i.e., we did an EBOM XML import, so assmebly selection won't work
		popup_menu->EnableMenuItem(ID_ASSEMBLY, MF_GRAYED);
	}
#endif // INTEROP

#endif // HOOPS_ONLY

	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidData)
	{
		popup_menu->EnableMenuItem(ID_VERTEX, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_EDGE, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_FACE, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_BODY, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_ASSEMBLY, MF_GRAYED);
#ifdef PARASOLID
		popup_menu->EnableMenuItem(ID_ASSEMBLY, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_INSTANCE, MF_GRAYED);
#endif // PARASOLID
		popup_menu->EnableMenuItem(ID_OPTIMIZE, MF_GRAYED);
	}
	if (m_pHView->GetRenderMode() == HRenderHiddenLine || ((HSolidModel *)(m_pHView->GetModel()))->m_bPlainSolidModel)
		popup_menu->EnableMenuItem(ID_OPTIMIZE, MF_GRAYED);

 	if (!(pHView->GetOptimizations()))
		popup_menu->CheckMenuItem(ID_OPTIMIZE, MF_BYCOMMAND | MF_CHECKED);

 	if (pHView->GetOptimizations())
 		popup_menu->EnableMenuItem(ID_FACE, MF_GRAYED);
	
	HSSelectionSet* selection = (HSSelectionSet*) (m_pHView->GetSelection());
	if (selection->GetFacesAsLines())
         popup_menu->CheckMenuItem(ID_FACESASLINES, MF_BYCOMMAND | MF_CHECKED);  
    else
         popup_menu->CheckMenuItem(ID_FACESASLINES, MF_BYCOMMAND | MF_UNCHECKED);  
 

	if(CAppSettings::DisableEditing)
	{	
		popup_menu->EnableMenuItem(ID_TOOLS_LIGHTS_INSERTLOCALLIGHT, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_TOOLS_LIGHTS_INSERTSPOTLIGHT, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_TOOLS_LIGHTS_INSERTDISTANTLIGHT, MF_GRAYED);
	}
 
    
    m_PositionOnRightClick.Set((float)point.x,(float) point.y, 0);
    HUtility::ConvertLocalPixelsToLocalWindow(m_pHView, &m_PositionOnRightClick);    
   
    m_KeyUnderCursor = HUtility::SelectUnderCursor(m_pHView,m_PositionOnRightClick.x,m_PositionOnRightClick.y,false);
	if( m_KeyUnderCursor >= 0 ) {
		HC_KEY keys[1000];
		int count;

		HC_Show_Selection_Keys( &count, keys );
		HC_Open_Segment_By_Key( keys[1] );
			m_KeyUnderCursor = HC_KShow_Original_Key( m_KeyUnderCursor );
		HC_Close_Segment();
	}
   
	if (m_KeyUnderCursor == -1 || CAppSettings::DisableEditing)
    {    
		popup_menu->EnableMenuItem(ID_TOOLS_SELECT, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_TOOLS_ACTIVATEMANIPULATOR, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_TOOLS_ACTIVATEMANIPULATOR2, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_TOOLS_DEACTIVATEMANIPULATOR, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_TOOLS_TRANSPARENCY, MF_GRAYED);
    }
    else
    {
		HC_Open_Segment_By_Key(HUtility::GrabSegment(m_KeyUnderCursor));

	    char oname[4096];
	    HC_KEY tempkey = HObjectManager::FindHObjectSegment(HUtility::GrabSegment(m_KeyUnderCursor), oname);
//	    popup_menu->AppendMenu(MF_SEPARATOR,0,"" );
	    if (strcmp(oname, "Annotation") == 0)	    	    
	    {	    
 			popup_menu->AppendMenu(0,ID_TOOLS_DELETE_ENTITY,_T("Delete Note") );
			popup_menu->AppendMenu(0,ID_TOOLS_SET_NOTE_TEXT,_T("Edit Note") );
			m_KeyUnderCursor = tempkey;
	    }	     
	    else
 		popup_menu->AppendMenu(0,ID_TOOLS_DELETE_ENTITY,_T("Delete") );


	    if (HUtility::SegmentExists("cpbox"))
	    {	    
		popup_menu->EnableMenuItem(ID_TOOLS_ACTIVATEMANIPULATOR, MF_GRAYED);
		popup_menu->EnableMenuItem(ID_TOOLS_ACTIVATEMANIPULATOR2, MF_GRAYED);
	    }else
	    {
		popup_menu->EnableMenuItem(ID_TOOLS_DEACTIVATEMANIPULATOR, MF_GRAYED);

	    }

		//check to see if object is transparent in any way
		{
			float color[3];
			HC_KEY keys[1000];
			int count;

			HC_Show_Selection_Keys( &count, keys );

			HC_PShow_Net_Explicit_Color(count, keys, "faces", "transmission", &color[0], 0, 0);

			if(color[0] == 0 && color[1] == 0 && color[2] == 0)
				popup_menu->CheckMenuItem(ID_TOOLS_TRANSPARENCY, MF_BYCOMMAND | MF_UNCHECKED);  
			else
				popup_menu->CheckMenuItem(ID_TOOLS_TRANSPARENCY, MF_BYCOMMAND | MF_CHECKED);  
		}
	    HC_Close_Segment();

    }
    popup_menu->TrackPopupMenu( TPM_LEFTALIGN , 
                                new_menu_position.x, 
                                new_menu_position.y, 
                                (CWnd *)this);  

	CView::OnRButtonDown(nFlags, point);
	m_pHView->GetConstantFrameRateObject()->SetDisableIncreaseTemp(false);

}


void CSolidHoopsView::OnToolsVisibilityEdges()
{
	HSolidModel * model = (HSolidModel *)(m_pHView->GetModel());

    // the modeling kernel's concept of edges are being represented in the HOOPS
	// database by HOOPS polylines, etc... The visiblity of these HOOPS
	// primitives are controlled using the 'line' identifier, while the 'edge' 
	// identifier in HOOPS is reserved for HOOPS shells/mesh face boundaries

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
        if (m_edges) 
		{
            m_edges = false;
			if (model->IsBRepGeometry())
				HC_Set_Visibility ("lines = off");
			else
	            HC_Set_Visibility ("lines = off, edges = off");
        }
        else 
		{
            m_edges = true;
			if (model->IsBRepGeometry())
				HC_Set_Visibility ("lines = on");
			else
				HC_Set_Visibility ("lines = on, edges = on");  
        }
    HC_Close_Segment ();

	HSelectionSet * selection=m_pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	m_pHView->Update();	


#ifndef HOOPS_ONLY
	if(m_pDlgTopologyBrowser && m_pDlgTopologyBrowser->IsWindowVisible())
		m_pDlgTopologyBrowser->UpdateTopolBrowserCheckboxes();
#endif // HOOPS_ONLY

}

void CSolidHoopsView::OnUpdateToolsVisibilityEdges(CCmdUI* pCmdUI)
{
    if (m_edges)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsVisibilityHoopsEdges() 
{
	HSolidView * pHView = GetSolidView();
	pHView->SetVisibilityEdges(!pHView->GetVisibilityEdges());
	HSelectionSet * selection=pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

    m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsVisibilityHoopsEdges(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		GetSolidView()->GetVisibilityEdges() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsView::OnToolsVisibilityFaces()
{
	HSolidView * pHView = GetSolidView();
	pHView->SetVisibilityFaces(!pHView->GetVisibilityFaces());

	HSelectionSet * selection=pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	pHView->Update();	
}


void CSolidHoopsView::OnUpdateToolsVisibilityFaces(CCmdUI* pCmdUI)
{
    if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		GetSolidView()->GetVisibilityFaces())
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnLights()
{
    HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
        if (m_lights) 
		{
            m_lights = false;
            HC_Set_Visibility ("lights = off");
			m_bFastPrint = false;
        }
        else 
		{
            m_lights = true;
            HC_Set_Visibility ("lights = (faces = on, edges = off, markers = off)");
			m_bFastPrint = true;
        }
    HC_Close_Segment ();

	m_pHView->Update();	
}

void CSolidHoopsView::OnUpdateLights(CCmdUI* pCmdUI)
{
    if (m_lights)
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsVisibilityMarkers()
{
	HSolidView * pHView = GetSolidView();
	pHView->SetVisibilityMarkers(!pHView->GetVisibilityMarkers());
	HSelectionSet * selection=pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	pHView->Update();	
}

void CSolidHoopsView::OnUpdateToolsVisibilityMarkers(CCmdUI* pCmdUI)
{
    if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		GetSolidView()->GetVisibilityMarkers())
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);
}

#ifndef HOOPS_ONLY
void CSolidHoopsView::OnBody() 
{
	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	sel_set->DeSelectAll();
	sel_set->SetSelectLevel(KERN_BODY_TYPE);

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		HC_Set_Selectability("faces = on, lines = on, edges = off, markers = on");
#ifdef ACIS
		HC_Set_Selectability("edges = on");
#endif
	HC_Close_Segment();
	
}

void CSolidHoopsView::OnUpdateBody(CCmdUI* pCmdUI) 
{
	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidData)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		KERN_CLASS_TYPEDEF class_type;
		class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == KERN_BODY_TYPE)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
 	
}

void CSolidHoopsView::OnEdge() 
{
	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	sel_set->DeSelectAll();
	sel_set->SetSelectLevel(KERN_EDGE_TYPE);

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		HC_Set_Selectability("faces = off, lines = on, edges = off, markers = off");
#ifdef ACIS
		HC_Set_Selectability("edges = on");
#endif
	HC_Close_Segment();
}

void CSolidHoopsView::OnUpdateEdge(CCmdUI* pCmdUI) 
{	
	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidData)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		KERN_CLASS_TYPEDEF class_type;
		class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == KERN_EDGE_TYPE)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
}

void CSolidHoopsView::OnFace() 
{	
	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	sel_set->DeSelectAll();
	sel_set->SetSelectLevel(KERN_FACE_TYPE);

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		HC_Set_Selectability("faces = on, lines = off, edges = off, markers = off");
	HC_Close_Segment();
}

void CSolidHoopsView::OnUpdateFace(CCmdUI* pCmdUI) 
{
	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();

	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidData || 	
		(((HSolidView *)m_pHView)->GetOptimizations()))
  		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		KERN_CLASS_TYPEDEF class_type;
		class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == KERN_FACE_TYPE)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
}

void CSolidHoopsView::OnUpdateSubtract(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (0);	
}

 
void CSolidHoopsView::OnUpdateUnion(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (0);	
}

void CSolidHoopsView::OnUpdateIntersect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (0);	
}

void CSolidHoopsView::OnOptimize() 
{
#ifndef HOOPS_ONLY
	bool  current = GetSolidView()->GetOptimizations();
	KERN_CLASS_TYPEDEF class_type;
	
	CBusyDlg *	busy = new CBusyDlg();
 	busy->Create(IDD_BUSYDLG);
	busy->ShowWindow(SW_SHOW);
	
	if (!current) {
		class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == KERN_FACE_TYPE) {
			OnBody();
		}
	}

	((HSolidView *)m_pHView)->SetOptimizations(!current);
	

	if(m_pDlgTopologyBrowser && m_pDlgTopologyBrowser->IsWindowVisible())
		m_pDlgTopologyBrowser->UpdateTopolBrowserCheckboxes();

	delete busy;
#endif // HOOPS_ONLY
}


void CSolidHoopsView::OnUpdateOptimize(CCmdUI* pCmdUI) 
{
	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidModel || m_pHView->GetRenderMode() == HRenderHiddenLine || 
		((HSolidModel *)(m_pHView->GetModel()))->m_bPlainSolidModel)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);
	
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		((HSolidView *)m_pHView)->GetOptimizations())
		pCmdUI->SetCheck (0);
	else
		pCmdUI->SetCheck (1);

}
#endif // HOOPS_ONLY

void CSolidHoopsView::OnCurvature() 
{
	int size, n;
	HC_KEY key = 0;
	char keytype[MVO_BUFFER_SIZE]; 
	HSSelectionSet* selection = GetSolidView()->GetSolidSelection();
	size = selection->GetSize();
	double max_curv = -10000000.0;
	double min_curv =10000000.0;
	double delta_curv = 0;
	double curv_offset = 0;
	double curv_mult = 0;
	double curv_sum = 0;
	int point_index = 0;
	int point_offset = 0;
	int temp_point_count = 0;
	int point_count = 0;
	int temp_flist_count = 0;
	int max_flist_count = 0;
	int point_count2 = 0;
	int flist_count2 = 0;
	float* points = 0;
	int* flist = 0;
	double curv1 = 0.0;
	double curv2 = 0.0;
	double* curvatures1;
	double* curvatures2;
	float* findices = 0;
#ifdef ACIS
	FACE* face;
	SPAposition p (0,0,0);
	SPAposition p2(0,0,0);
	SPAunit_vector dir1;
	SPAunit_vector dir2;
#endif

	for (n = 0; n < size; n++)
	{
		// count to see how much space we'll need to allocate
		key = selection->GetAt(n);

		HC_Show_Key_Type(key, keytype);

		if ((key != 0) && (streq(keytype, "segment")))
		{

			HC_Open_Segment_By_Key(key);

#ifdef ACIS
				BODY* body;
				body = (BODY*)HA_Compute_Entity_Pointer(key, BODY_TYPE);
				// todo: more stuff here
#endif
			HC_Close_Segment();
			
		}
		else if ((key != 0) && (streq(keytype, "shell")))
		{
			HC_Show_Shell_Size(key, &temp_point_count, &temp_flist_count);
			assert(temp_point_count > 0);
			assert(temp_flist_count > 0);
			if (temp_flist_count > max_flist_count)
				max_flist_count = temp_flist_count;
			point_count += temp_point_count;
		}
	}
	points = new float[3*point_count];
	flist = new int[max_flist_count];
	curvatures1 = new double[point_count];
	curvatures2 = new double[point_count];
	findices = new float[point_count];
	point_offset = 0; // starting over again
	for (n = 0; n < size; n++)
	{
		key = selection->GetAt(n);

		HC_Show_Key_Type(key, keytype);

		if ((key != 0) && (streq(keytype, "segment")))
		{

			HC_Open_Segment_By_Key(key);

#ifdef ACIS
				BODY* body;
				body = (BODY*)HA_Compute_Entity_Pointer(key, BODY_TYPE);
				// todo: more stuff here
#endif

			HC_Close_Segment();
			
		}
		else if ((key != 0) && (streq(keytype, "shell")))
		{
#ifdef ACIS
			face = (FACE*)HA_Compute_Entity_Pointer(key, FACE_TYPE);
			assert(face);
#endif

#ifdef PARASOLID
		PK_FACE_t face;
		PK_SURF_t surface;
		PK_ERROR_t error;
		PK_VECTOR_t p;
		PK_VECTOR1_t normal;
		PK_VECTOR1_t dir1;
		PK_VECTOR1_t dir2;
		PK_UV_t uv;


			face = HP_Compute_TagID(key, PK_CLASS_face);
			error = PK_FACE_ask_surf(face, &surface);
#endif  // PARASOLID
			HC_Show_Shell_Size(key, &temp_point_count, &temp_flist_count);
			assert(temp_point_count > 0);
			assert(temp_point_count <= (point_count - point_offset));
			assert(temp_flist_count > 0);
			assert(temp_flist_count <= max_flist_count);
			HC_Show_Shell(key, &point_count2, points+point_offset*3, &flist_count2, flist);
			assert(temp_point_count == point_count2);
			assert(temp_flist_count == flist_count2);

			for (point_index = point_offset; point_index < (point_offset + temp_point_count); point_index++)
			{
#ifdef ACIS
				p.set_x((double)points[point_index*3]);
				p.set_y((double)points[point_index*3+1]);
				p.set_z((double)points[point_index*3+2]);

				SURFACE* Surface = face->geometry();
				Surface->equation().point_prin_curv(p, dir1, curv1, dir2, curv2);

#endif // ACIS
#ifdef PARASOLID
				p.coord[0] = points[point_index*3];
				p.coord[1] = points[point_index*3+1];
				p.coord[2] = points[point_index*3+2];

				PK_GEOM_range_vector_o_t   options;
				PK_range_result_t          range_result;
				PK_range_1_r_t             range;
				PK_ERROR_code_t	error;

				PK_GEOM_range_vector_o_m(options);
				error = PK_GEOM_range_vector(surface, p, &options, &range_result, &range);
				
				PK_VECTOR_t		point_on_surface;

				point_on_surface = range.end.vector;
				
				error = PK_SURF_parameterise_vector(surface, point_on_surface, &uv);
				error = PK_SURF_eval_curvature(surface, uv, &normal, &dir1, &dir2, &curv1, &curv2);
#endif // PARASOLID
				curvatures1[point_index] = curv1;
				curvatures2[point_index] = curv2;

				curv_sum = curv1 + curv2;

				if (curv_sum > max_curv) max_curv = curv_sum;
				if (curv_sum < min_curv) min_curv = curv_sum;
			}
			point_offset += temp_point_count;
		}
	}


	// OK, now we know the full range of curvatures for the selection.
	// scale the findices based on this range of curvature.

	delta_curv = max_curv - min_curv;
	if (delta_curv < 0.00001)
		curv_mult = 1.0;
	else
		curv_mult = 6.0/delta_curv; // indexing into a color map of six
	curv_offset = -min_curv;

	for (point_index = 0; point_index < point_count; point_index++)
	{
		// this is a value between 2 and 8, the places in the color map which represent the color ramp
		findices[point_index] = (float)((curvatures1[point_index]+curvatures2[point_index]+curv_offset)*curv_mult+2.0f/*offset into color map*/);
	}
	point_offset = 0; //reset points offset, starting all over again

	for (n = 0; n < size; n++)
	{
		key = selection->GetAt(n);

		HC_Show_Key_Type(key, keytype);

		if ((key != 0) && (streq(keytype, "segment")))
		{
			HC_Open_Segment_By_Key(key);

#ifdef ACIS
				BODY* body;
				body = (BODY*)HA_Compute_Entity_Pointer(key, BODY_TYPE);
				// todo: more stuff here
#endif

			HC_Close_Segment();
			
		}
		else if ((key != 0) && (streq(keytype, "shell")))
		{
			
			HC_Show_Shell_Size(key, &temp_point_count, &temp_flist_count);

			HC_MSet_Vertex_Colors_By_FIndex(key, "faces", 0, temp_point_count, findices+point_offset);
			point_offset += temp_point_count;
		}
	}
	delete findices;
	delete points;
	delete curvatures1;
	delete curvatures2;
	delete flist;

	m_curvature_set = true;

	// set color interpolation and color index interpolation to false before calling the OnColorXXX fcns
	// so that they'll be sure to turn them on!
	m_color_int = false;
	m_color_index_int = false;

	OnColorInterpolation();
	OnColorIndexInterpolation();

	m_pHView->GetSelection()->DeSelectAll();
	m_pHView->Update(); 
}

void CSolidHoopsView::OnUpdateCurvature(CCmdUI* pCmdUI) 
{
#ifdef PARASOLID
	if (((HSSelectionSet *)m_pHView->GetSelection())->GetSelectLevel() == PK_CLASS_face)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	
#endif // PARASOLID

#ifdef ACIS
	// ACIS implementation is complete but memory leaks in ACIS kernel are to severe to enable this
	// feature by default
	pCmdUI->Enable (0);
#endif

#ifdef GRANITE
	// TODO_IMPLEMENT - Not yet in specifications for Granite
	pCmdUI->Enable (0);
#endif // GRANITE

}



void CSolidHoopsView::OnVertex() 
{
#ifdef GRANITE
	// granite has no support for vertices
	assert(0);
#endif // GRANITE

#if defined(ACIS) || defined(PARASOLID)

	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	sel_set->DeSelectAll();
	sel_set->SetSelectLevel(KERN_VERTEX_TYPE);

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		HC_Set_Selectability("faces = off, lines = off, edges = off, markers = on");
	HC_Close_Segment();
#endif

}

void CSolidHoopsView::OnUpdateVertex(CCmdUI* pCmdUI) 
{
#ifdef GRANITE
	// granite has no support for vertices
	assert(0);
#endif // GRANITE

#if defined(ACIS) || defined(PARASOLID)

	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidModel)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		KERN_CLASS_TYPEDEF class_type;
		class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == KERN_VERTEX_TYPE)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
#endif

}

void CSolidHoopsView::OnColorIndexInterpolation() 
{
	bool index_interpolation = Verticals::CAE::IndexInterpolation(m_pHView);
	Verticals::CAE::IndexInterpolation(m_pHView, !index_interpolation);
	m_pHView->Update();
}


void CSolidHoopsView::OnUpdateColorIndexInterpolation(CCmdUI* pCmdUI) 
{
	if (m_color_index_int)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);

}


void CSolidHoopsView::OnColorInterpolation() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		if (m_color_int)
		{
			m_color_int = false;
			HC_Set_Rendering_Options("no color interpolation");
		}
		else
		{
			m_color_int = true;
			HC_Set_Rendering_Options("color interpolation");
		}
	HC_Close_Segment();

	m_pHView->Update();
}


void CSolidHoopsView::OnUpdateColorInterpolation(CCmdUI* pCmdUI) 
{
	if (m_color_int)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnOrthographic() 
{
	m_pHView->SetProjMode(ProjOrthographic);
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateOrthographic(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetProjMode() == ProjOrthographic)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnPerspective() 
{
	m_pHView->SetProjMode(ProjPerspective);
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdatePerspective(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetProjMode() == ProjPerspective)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnLevelOfDetail() 
{

	// toggle on off	
	if(m_pHView->GetLodMode())
		m_pHView->SetLodMode(false);
	else
		m_pHView->SetLodMode(true);
		
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateLevelOfDetail(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetLodMode())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


#ifdef ACIS
void CSolidHoopsView::OnUpdateCreateTorus(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCreateTorus"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}
#endif



void CSolidHoopsView::OnUpdateOrbit(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCameraOrbit") || streq(m_pHView->GetOperator()->GetName(), "HOpCameraManipulate"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnUpdateTurntable(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCameraOrbitTurntable"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnUpdatePan(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCameraPan"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(),"HOpCameraZoom"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);	
}

void CSolidHoopsView::OnUpdateZoomToWindow(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCameraZoomBox"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);	
}

void CSolidHoopsView::OnUpdateWindowSelect(CCmdUI* pCmdUI) 
{
//	HSolidModel * model = (HSolidModel *)(m_pHView->GetModel());
 
//	if (model->m_solid_model == true)
//		{
		if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
			streq(m_pHView->GetOperator()->GetName(), "HOpSelectArea"))
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
//		}
//	else
//		pCmdUI->Enable(0);
}

void CSolidHoopsView::OnUpdateApertureSelect(CCmdUI* pCmdUI) 
{
//	HSolidModel * model = (HSolidModel *)(m_pHView->GetModel());
 
//	if (model->m_solid_model == true)
//		{
		if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
			streq(m_pHView->GetOperator()->GetName(), "HOpSelectAperture"))
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);	
//	}
//	else
//		pCmdUI->Enable(0);
}

 

void CSolidHoopsView::SetQueryDialogText(char *text)
{
	m_query_dialog->SetText(text);
}
void CSolidHoopsView::SetAdvancedQueryDialogText(char *text)
{
	m_advanced_query_dialog->SetText(text);
}
void CSolidHoopsView::ShowQueryDialog(int showFlag)
{
	m_query_dialog->ShowWindow(showFlag);
}
void CSolidHoopsView::ShowAdvancedQueryDialog(int showFlag)
{
	m_advanced_query_dialog->ShowWindow(showFlag);
}

void CSolidHoopsView::ShowStyleDialog(int showFlag)
{
	if (!m_style_dialog)
	{    
		m_style_dialog = new CStyleDialog(m_pHView);
		m_style_dialog->Create(IDD_STYLEDIALOG);
	}

	m_style_dialog->ShowWindow(showFlag);
}

 


// set the XY plane view mode
void CSolidHoopsView::OnXyPlane() 
{
	m_pHView->SetViewMode(HViewFront);
}

void CSolidHoopsView::OnUpdateXyPlane(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewXY)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


// set the XZ plane view mode
void CSolidHoopsView::OnXzPlane() 
{
	m_pHView->SetViewMode(HViewTop);
}

void CSolidHoopsView::OnUpdateXzPlane(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewXZ)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


// set the YZ plane view mode
void CSolidHoopsView::OnYzPlane() 
{
	m_pHView->SetViewMode(HViewLeft);

}

void CSolidHoopsView::OnUpdateYzPlane(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewYZ)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);	
}


void CSolidHoopsView::OnIsoPlane() 
{
	m_pHView->SetViewMode(HViewIso);
}

void CSolidHoopsView::OnUpdateIsoPlane(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewIso)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::event_checker(HIC_Rendition const *nr)
{

	MSG msg;
	CSolidHoopsView * pCurrentView = (CSolidHoopsView*)HIC_Show_User_Index(nr, H_VIEW_POINTER_INDEX);
	if (pCurrentView && pCurrentView->m_hWnd != 0)
	{		
		int state = GetAsyncKeyState(VK_LBUTTON);
		if (state & 32768)				
		{
			pCurrentView->m_pHView->GetConstantFrameRateObject()->InitiateDelay();
 
 			pCurrentView->m_pHView->SetUpdateInterrupted(true);


  
			HIC_Abort_Update(nr);
 
		}		
		
		state = GetAsyncKeyState(VK_MBUTTON);
		if (state & 32768)				
		{
			HIC_Abort_Update(nr);
			pCurrentView->m_pHView->SetUpdateInterrupted(true);
		}		
		
		if (PeekMessage (&msg, pCurrentView->m_hWnd, WM_MOUSEWHEEL, WM_MOUSEWHEEL, PM_NOREMOVE))
		{
			HIC_Abort_Update(nr);
			pCurrentView->m_pHView->SetUpdateInterrupted(true);
		}
	}
		int state = GetAsyncKeyState(VK_RBUTTON);
		if (state & 32768)				
		{
			pCurrentView->m_pHView->GetConstantFrameRateObject()->InitiateDelay();
 			pCurrentView->m_pHView->SetUpdateInterrupted(2);
			HIC_Abort_Update(nr);
		}		
	
}


//Since we specify the Event Type as HE_JoyStickTranslate or HE_JoyStickRotate, 
//we can safely reuse the MouseWorldPos HPoint to hold our Translation/Rotation 
//float values here.

int CSolidHoopsView::OnJoyStickRotation( HEventInfo &hevent){
	HPoint rotate = hevent.GetJoystickRotation();

	//The scene_scale was determined by using the bounding sphere radius
	//of the city.hsf model.  The 2048.0 for rotation and 2.5 scale values
	//for translation were tuned by hand using the raw device values with the 
	//city.hsf model.  


	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Pan_Camera(-rotate.z /2048.0, rotate.x / 2048.0);
		HC_Roll_Camera(-rotate.y / 2048.0);
		m_pHView->Update();
	HC_Close_Segment();
	return 0;
}

int CSolidHoopsView::OnJoyStickTranslation( HEventInfo &hevent){
	HPoint xlate = hevent.GetJoystickTranslation();
	float center[3];
	float radius, scene_scale;


	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Show_Bounding_Sphere(center, &radius);
		scene_scale = radius / 81456.38;
		HC_Dolly_Camera(xlate.x / 2.5 * scene_scale, xlate.y / 2.5 * scene_scale, xlate.z / 2.5* scene_scale);
		m_pHView->Update();
	HC_Close_Segment();
	return 0;
}

int CSolidHoopsView::OnJoyStickButton(HEventInfo &hevent){
	TCHAR temp[MVO_BUFFER_SIZE];
	if (hevent.GetFlags() == MVO_JOYSTICK_BUTTON_1){
		_stprintf(temp, _T("3D Mouse Button 1"));
		AfxMessageBox(temp);
	}
	else if(hevent.GetFlags() == MVO_JOYSTICK_BUTTON_2){
		_stprintf(temp, _T("3D Mouse Button 2"));
		AfxMessageBox(temp);
	}
	else if(hevent.GetFlags() == MVO_JOYSTICK_BUTTON_3){
		_stprintf(temp, _T("3D Mouse Button 3"));
		AfxMessageBox(temp);
	}
	else if(hevent.GetFlags() == MVO_JOYSTICK_BUTTON_4){
		_stprintf(temp, _T("3D Mouse Button 4"));
		AfxMessageBox(temp);
	}
	else if(hevent.GetFlags() == MVO_JOYSTICK_BUTTON_5){
		_stprintf(temp, _T("3D Mouse Button 5"));
		AfxMessageBox(temp);
	}
	else if(hevent.GetFlags() == MVO_JOYSTICK_BUTTON_6){
		_stprintf(temp, _T("3D Mouse Button 6"));
		AfxMessageBox(temp);
	}
	else if(hevent.GetFlags() == MVO_JOYSTICK_BUTTON_7){
		_stprintf(temp, _T("3D Mouse Button 7"));
		AfxMessageBox(temp);
	}
	else if(hevent.GetFlags() == MVO_JOYSTICK_BUTTON_8){
		_stprintf(temp, _T("3D Mouse Button 8"));
		AfxMessageBox(temp);
	}
	return 0;
}

void CSolidHoopsView::StartThreadedLoading()
{
	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	ASSERT_VALID(pDoc);
// 	HC_Delete_By_Key(m_pHView->GetIncludeLinkKey());
// 	m_pHView->SetIncludeLinkKey(-1);
	TCHAR extension[MVO_BUFFER_SIZE];
	HUtility::FindFileNameExtension(pDoc->filename, extension);

	// in case we have a Pro/E file which ends with a number, e.g., *.prt.1 or *.xas.1
	if ( extension[0] >= _T('0') && extension[0] <= _T('9') ) { 
		int offset;
		if (_tcslen(extension) == 1)
			offset = -2;
		else
			offset = -(int)_tcslen(extension);
		/* TODO: Fix this */
		//HC_Parse_String(H_ASCII_TEXT(pDoc->filename), ".", offset, extension);
	}

	/* make it lower case */

	// Don't create this dialog if we are importing via InterOp or a modelling kernel
	if (_tcsicmp(extension, _T("catpart"))	&& _tcsicmp(extension, _T("catproduct"))	&& _tcsicmp(extension, _T("cgr")) &&
		_tcsicmp(extension, _T("model"))	&& _tcsicmp(extension, _T("session"))		&& _tcsicmp(extension, _T("exp")) &&
		_tcsicmp(extension, _T("prt"))		&& _tcsicmp(extension, _T("xpr"))			&&
		_tcsicmp(extension, _T("asm"))		&& _tcsicmp(extension, _T("xas"))			&&
		_tcsicmp(extension, _T("igs"))		&& _tcsicmp(extension, _T("iges"))			&&
		_tcsicmp(extension, _T("stp"))		&& _tcsicmp(extension, _T("step"))			&&
		_tcsicmp(extension, _T("vda"))		&& 
		_tcsicmp(extension, _T("x_t"))		&& _tcsicmp(extension, _T("x_b"))			&&
		_tcsicmp(extension, _T("sat"))		&& _tcsicmp(extension, _T("sab")))
	{
		pDoc->m_ProgressDlg = new CFileLoadProgressDlg(HDB::GetHIOManager()->GetInputHandler(extension),this);
		pDoc->m_ProgressDlg->Create(IDD_FILE_LOAD_PROGRESS);
		pDoc->m_ProgressDlg->ShowWindow(SW_SHOW);
	}
	else
		using_modelling_kernel = true;

	if (_tcseq(extension, _T("dwg")))
		HLoadingThread(this);
	else
		AfxBeginThread(HLoadingThread, this, THREAD_PRIORITY_NORMAL, 0, 0);
}

void CSolidHoopsView::StopThreadedLoading()
{
	HC_Open_Segment_By_Key(m_pHView->GetOverwriteKey());
	HC_Open_Segment("selectionconditionincluder");
// 	m_pHView->SetIncludeLinkKey(HC_KInclude_Segment_By_Key(m_pHView->GetModelKey()));
	HC_Close_Segment();
	HC_Close_Segment();
 
}
	 
#include "HDebugZBuffer.h"

#define	DEBUG_MARKER_SIZE_CLAMP_TO_HW_MAX	0x00000010
#define	DEBUG_MARKER_POINTSMOOTH_CIRCLES	0x00000020
#define DEBUG_STARTUP_CLEAR_BLACK			0x00004000

// this functions creates a new HSolidView Object, and initializes its camera,
// render mode, query dialog, and operator
void CSolidHoopsView::OnInitialUpdate() 
{
	char        driver_opts[MVO_BUFFER_SIZE],
		rendering_opts[MVO_BUFFER_SIZE]={0};


	// we must call the base class initialization first to get the proper palette for this view
	// (either the same palette is shared among all views, or this view has a unique palette)
	CHoopsView::OnInitialUpdate();

	// create the the Hoops View object to be associated with this MFC View
	// as well as a generic HOOPS segment hierarchy

	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	HBaseModel * hmodel = pDoc->GetHoopsModel();

	// create the HOOPS ParaView object corresponding with this MFC View, passing in the 
	// Model Object, the MFC View's window handle, and palette

	m_pHView = new HSolidView(hmodel, 0, H_ASCII_TEXT(CAppSettings::HoopsDriver), 0, (void *) m_hWnd, (void *)(HPALETTE)*(GetPalette()));

	// initialize and set the initial operator to OrbitCamera

	((HSolidView *)m_pHView)->Init();

	// do all the setup with no updates 
	m_pHView->SetSuppressUpdate(true); 


	LocalSetOperator(new HOpCameraManipulate(m_pHView, 0,1, new HSOpCameraOrbit(m_pHView), new HSOpCameraPan(m_pHView),
		new HSOpCameraZoom(m_pHView),0,false));	
	m_pHView->SetAxisManipulateOperator(new HOpCameraManipulate(m_pHView, 0,1, new HSOpCameraOrbit(m_pHView), new HSOpCameraPan(m_pHView),
		new HSOpCameraZoom(m_pHView),0, false));
	HSOpMoveHandle *handleoperator = new HSOpMoveHandle(m_pHView, this, false);
	m_pHView->SetHandleOperator(handleoperator);
	m_pHView->GetEventManager()->RegisterHandler((HObjectManipulationListener *)handleoperator, HObjectManipulationListener::GetType(), HLISTENER_PRIORITY_NORMAL);
	m_pHView->GetEventManager()->RegisterHandler((HJoyStickListener *)this, HJoyStickListener::GetType(), HLISTENER_PRIORITY_NORMAL);
	m_pHView->GetHObjectManager()->AddHObject(new HEdgeVertexSelectionObject(m_pHView));
   
	m_pHView->SetKeyStateCallback(CHoopsView::GetKeyState);
	m_pHView->GetModel()->GetBhvBehaviorManager()->SetUpdateCamera(CAppSettings::UpdateCamera);

	// set the DEBUG_NO_WINDOWS_HOOK debug bit since the app will manage 
	// all palette and update messages

	// DEBUG_STARTUP_CLEAR_BLACK = 0x00004000 make ogl clear black and is
	// NOP on other drivers
	long        debug_flags = DEBUG_NO_WINDOWS_HOOK | DEBUG_STARTUP_CLEAR_BLACK;

	// use soft ogl if set
	if( CAppSettings::bDriverForceSoftware )
		debug_flags |= DEBUG_FORCE_SOFTWARE;

	sprintf (driver_opts, "debug = %u", debug_flags);

	// set anti-aliasing if set
	if( CAppSettings::bAntiAliasing)
		sprintf(driver_opts, "%s, anti-alias=%d ",driver_opts, CAppSettings::AntialiasingLevel);

	if( CAppSettings::bDriverDisplayStats)
		sprintf(driver_opts, "%s, display stats, display time stats, display memory stats",driver_opts);

	if( CAppSettings::StereoMode)
		sprintf(driver_opts, "%s, stereo", driver_opts);

	sprintf(driver_opts, "%s, quick moves preference = %s", 
		driver_opts, H_ASCII_TEXT(CAppSettings::csQuickMovesType));

	HCLOCALE(sprintf(driver_opts, 
		"%s, ambient occlusion = (%s, strength = %f, quality = %s), fast silhouette edges = (%s, tolerance = %f, %s heavy exterior)",
		driver_opts, (CAppSettings::UseFastAmbient ? "on" : "off") , CAppSettings::FastAmbientStrength, 
		(CAppSettings::HQAmbientOcclusion ? "nicest" : "fast"),
		(CAppSettings::UseFastSilhouette ? "on" : "off"), CAppSettings::FastSilhouetteTolerance,
		(CAppSettings::HeavyExteriorSilhouette ? "" : "no")	));

	m_pHView->SetDoubleBuffering(CAppSettings::DoubleBuffer);

	HC_Open_Segment_By_Key(m_pHView->GetViewKey()); {
		HC_Set_User_Index(H_VIEW_POINTER_INDEX, this);  /* This is used in the event_checker for constant framerate. */
		HC_Set_Driver_Options(driver_opts);
		sprintf(driver_opts, "bloom = (%s, strength=%f, blur=%d, shape=%s)", 
			(CAppSettings::UseBloom ? "on" : "off"), 
			CAppSettings::BloomStrength, 
			CAppSettings::BloomBlur,
			(CAppSettings::BloomShape == RadialBloom ? "radial" : "star")); 		
		HC_Set_Driver_Options(driver_opts);
		// antialiasing needs rendering option in addition to driver option
		if(CAppSettings::bAntiAliasing)
			HC_Set_Rendering_Options("anti-alias = (screen = on)");

		// Don't
		//force HOOPS to iterate through fonts to avoid delay the first time fonts are actually used
		//HC_Begin_Font_Search(".","generic");
		//HC_End_Font_Search();

		// On opengl use alternate definitions for these line styles
		// these styles fit in 16 bits and the standard definitions do not
		// this match > Hoops 12.0 behavior but is not visually correct
		if (streq(m_pHView->GetDriverType(), "opengl"))	{

			HC_Define_Line_Style("-.", "18 dash, 6 blank, 4 dash, 4 blank");
			HC_Define_Line_Style("1", "18 dash, 6 blank, 4 dash, 4 blank");

			HC_Define_Line_Style("-..", "14 dash, 4 blank, 4 dash, 2 blank, 4 dash, 4 blank");
			HC_Define_Line_Style("4", "14 dash, 4 blank, 4 dash, 2 blank, 4 dash, 4 blank");

			HC_Define_Line_Style("-...", "12 dash, 2 blank, 4 dash, 2 blank, 4 dash, 2 blank, 4 dash, 2 blank");
			HC_Define_Line_Style("5", "12 dash, 2 blank, 4 dash, 2 blank, 4 dash, 2 blank, 4 dash, 2 blank");

			HC_Define_Line_Style("phantom", "81 dash, 9 blank, 18 dash, 9 blank, 18 dash, 9 blank");
			HC_Define_Line_Style("8", "81 dash, 9 blank, 18 dash, 9 blank, 18 dash, 9 blank");
		}


		HC_Set_Driver_Options("special events, update interrupts");
		HC_Control_Update(".", "redraw everything");
	} HC_Close_Segment();


	// set the display lists mode
	// NOTE: Do this as early as possible (possibly before any Update is triggered)


	if (!CAppSettings::bLightScaling)
		m_pHView->SetLightScaling(0);
	else
		m_pHView->SetLightScaling(CAppSettings::LightScaleFactor/100000.f);

	m_pHView->SetLightFollowsCamera(CAppSettings::LightFollowsCamera);
	//m_pHView->SetLightCount(CAppSettings::LightCount); //defer until after camera is all set up
	m_pHView->SetVisibilitySelectionMode(CAppSettings::VisibilitySelection);
	m_pHView->SetDynamicHighlighting(CAppSettings::DynamicHighlighting);
	m_pHView->SetDetailSelection(CAppSettings::DetailSelection);
	m_pHView->SetRelatedSelectionLimit(CAppSettings::RelatedSelectionLimit);
	m_pHView->SetTransparentSelectionBoxMode(CAppSettings::bUseSelectBox);
	m_pHView->SetFastFitWorld(true);
	m_pHView->SetForceFastHiddenLine(CAppSettings::HiddenLineMode==FastHiddenLine);
	m_pHView->SetSpritingMode(CAppSettings::Spriting);
	m_pHView->SetAllowInteractiveCutGeometry(CAppSettings::UpdateCutGeometry);
	m_pHView->SetAllowInteractiveShadows(CAppSettings::UpdateShadows);
	m_pHView->SetBackplaneCulling(CAppSettings::bBackplaneCulling);
	m_pHView->SetOcclusionCullingMode(CAppSettings::OcclusionCulling, true, 
			CAppSettings::OcclusionThreshold);
	
	m_pHView->SetDisplayListType(DisplayListOff);
	
	if(CAppSettings::UseFramerate)
	{
		if (!pDoc->IsFileReadDeferedForView() || CAppSettings::CurrentFramerateMode == FramerateFixed)
		{
			m_pHView->SetFramerateMode(CAppSettings::CurrentFramerateMode, CAppSettings::FramerateTime,
				CAppSettings::MaxThreshold, UINT2bool(CAppSettings::UseLods), CAppSettings::DetailSteps, 
				CAppSettings::HardCutoff);
		}
	}
	else if (CAppSettings::CullingThresholdSet)
	{
		m_pHView->SetFramerateMode(FramerateOff);
		m_pHView->SetCullingThreshold(CAppSettings::CullingThreshold);
	}
	else
	{
	 	m_pHView->SetFramerateMode(FramerateOff);
		m_pHView->SetCullingThreshold(0);
	}

	m_pHView->SetSmoothTransition(false);
	m_pHView->SetShadowRenderingMode(CAppSettings::ShadowRenderingMode);
	SetViewAxis();
	SetTransparency();

	m_pHView->SetViewMode(HViewIsoFrontRightTop);		// fit the camera to the scene extents
	m_pHView->SetAxisMode( ((CAppSettings::bDisplayAxisTriad) ? AxisOn : AxisOff) );
 	SetWindowColor(CAppSettings::WindowBackgroundTopColor, CAppSettings::WindowBackgroundBottomColor);
	HPoint FakeHLRColor;
    FakeHLRColor.Set(
	static_cast<float>(GetRValue(CAppSettings::FakeHLRColor))/255.0f,
	static_cast<float>(GetGValue(CAppSettings::FakeHLRColor))/255.0f,
	static_cast<float>(GetBValue(CAppSettings::FakeHLRColor))/255.0f);
	m_pHView->SetFakeHLRColor(FakeHLRColor);
	m_pHView->SetProjMode(CAppSettings::ProjectionMode);
	m_pHView->SetSmoothTransition(CAppSettings::bSmoothTransition);
	m_pHView->SetHandedness((CAppSettings::bWorldHandedness ? HandednessRight : HandednessLeft), true);
	m_pHView->SetSmoothTransitionDuration(0.5f);
	m_pHView->GetUndoManager()->Flush();			//don't care about this initial camera change
	m_pHView->SetDisplayHandlesOnDblClk(!CAppSettings::DisableEditing);


	// The state of world today with coordinate system handedness is 
	// 1. We are going to only set it on the view and not the model in all our partviewers. 
	// 2. It is going to be right handed
	// Rajesh B (08-Apr-2003)
	SetCoordinateSystemHandedness( HandednessRight, true );

	// The state of world today with polygon handedness is 
	// 1. Since we are using display lists by default, we want this setting.
	// 2. We will have it only on the view key. If required, model could have it's own
	// Rajesh B (11-Apr-2003)
	m_pHView->SetPolygonHandednessMode( HandednessLeft );

	m_pHView->GetHighlightSelection()->SetGrayScale(CAppSettings::bGrayScaleSelection);
	m_pHView->GetHighlightSelection()->SetAllowDisplacement(CAppSettings::bDisplaceSelection);

	// set the selection color
	HSelectionSet* sel_set = m_pHView->GetSelection();
	assert(sel_set);
	HPixelRGBA sel_col;
	int sel_alpha = (int)(CAppSettings::SelectionColorTransparency*2.56f);		// settings is a %, scale it to 256
	sel_col.Set(GetRValue(CAppSettings::PolygonSelectionColor), GetGValue(CAppSettings::PolygonSelectionColor), GetBValue(CAppSettings::PolygonSelectionColor), sel_alpha);
	sel_set->SetSelectionFaceColor(sel_col);
	sel_col.Set(GetRValue(CAppSettings::LineSelectionColor), GetGValue(CAppSettings::LineSelectionColor), GetBValue(CAppSettings::LineSelectionColor), sel_alpha);
	sel_set->SetSelectionEdgeColor(sel_col);
	sel_col.Set(GetRValue(CAppSettings::MarkerSelectionColor), GetGValue(CAppSettings::MarkerSelectionColor), GetBValue(CAppSettings::MarkerSelectionColor), sel_alpha);
	sel_set->SetSelectionMarkerColor(sel_col);

	// set markup color and weight
	SetMarkupColor(CAppSettings::MarkupColor);

	SetShadowColor(CAppSettings::ShadowColor);

	m_pHView->GetMarkupManager()->SetMarkupWeight(CAppSettings::MarkupWeight/100.0f);
	m_pHView->SetShadowResolution(CAppSettings::ShadowRes);
	m_pHView->SetShadowBlurring(CAppSettings::ShadowBlur);

	// set the color index interpolation settings
	m_pHView->SetColorInterpolation(CAppSettings::bCiByValue);
	m_pHView->SetColorIndexInterpolation(CAppSettings::bCiByColormapIndex, CAppSettings::bCiIsolines);
	m_pHView->GetSelection()->SetGrayScale(CAppSettings::bGrayScaleSelection);
	m_pHView->GetSelection()->SetAllowDisplacement(CAppSettings::bDisplaceSelection);
	m_pHView->GetSelection()->SetHighlightMode(CAppSettings::HighlightMode);
	m_pHView->GetHighlightSelection()->SetHighlightMode(CAppSettings::HighlightMode);
	m_pHView->GetSelection()->SetHighlightTransparency(CAppSettings::TransparencyLevel);
	m_pHView->GetSelection()->SetReferenceSelectionType(CAppSettings::csRefSelType == "Spriting" ? RefSelSpriting : RefSelDefault);

	// set the rendermode
	m_pHView->SetRenderMode(CAppSettings::RenderMode, true);

	m_pHView->SetEventCheckerCallback(event_checker);

	//we need to adjust the axis window outside the mvo class as the calculation of the window
	//extents is mfc specific
 
	// initialize the QueryDialog and AdvancedQueryDialog
	m_query_dialog = new CQueryDialog();
	m_query_dialog->Create(IDD_QUERYDIALOG);
	m_query_dialog->SetText("No entities currently under cursor.");
	m_advanced_query_dialog = new CQueryDialog();
	m_advanced_query_dialog->Create(IDD_QUERY_ADVANCED_DLG);
	m_advanced_query_dialog->SetText("No entities currently under cursor.");

	((HSolidView *)m_pHView)->SetShowCollisions(CAppSettings::ShowCollisions);


	HStreamFileToolkit * tk = hmodel->GetStreamFileTK();
	if( tk )
	{
		// NOTE: I am setting these opcode handlers here, even if it is not a stream file. Who knows if we are in a 
		// collaborative session and someone loads an hsf file - Rajesh B
		// install our custom TK_Initial_View opcode handler so that we set the initial view appropriately
		tk->SetPrewalkHandler(new PartviewerHSFExtras(this));
		tk->SetOpcodeHandler(TKE_View, new PartviewerHSFExtras(this));
		if(CAppSettings::EmbedHSFThumbnail){
			MakeAndSetThumbnail(tk);
		}

		if (!HDB::GetMaterialLibrary())
			HDB::SetMaterialLibrary(new HMaterialLibrary);
		tk->SetOpcodeHandler (TKE_Material, new HTK_PartviewerMaterialHandler (this, HDB::GetMaterialLibrary()));

		//want to read the Autodek Image XRef Opcode
		tk->SetOpcodeHandler (0xE0,			    new W3D_Image);

		// set defaults on stream toolkit
		int sflags = 0;

		if (!CAppSettings::bCompressVertices)
			sflags |= TK_Full_Resolution_Vertices;
		else
			tk->SetNumVertexBits(CAppSettings::NumVertexBits);

		if (!CAppSettings::bCompressNormals)
			sflags |= TK_Full_Resolution_Normals;
		else
			tk->SetNumNormalBits(CAppSettings::NumNormalBits);

		if (!CAppSettings::bCompressParameters)
			sflags |= TK_Full_Resolution_Parameters;
		else
			tk->SetNumParameterBits(CAppSettings::NumParameterBits);


		if (CAppSettings::bExportDictionary == true)
			sflags |= TK_Generate_Dictionary;


		if (CAppSettings::bEnableInstancing == false)
			sflags |= TK_Disable_Instancing;

		if (CAppSettings::bCompressConnectivity == true)
			sflags |= TK_Connectivity_Compression;

		if (CAppSettings::bSaveLogFile == true)
			tk->SetLogging(true);
		else
			tk->SetLogging(false);

		// This is a paradox here, the flags passed as argument to Write_Stream function make
		// no sense if we use our own toolkit. These flags need to be set on the toolkit itself
		tk->SetWriteFlags(sflags);

		// Anything <= 0 for export version means use the default.
		if( CAppSettings::HsfExportVersion > 0 )
			tk->SetTargetVersion(CAppSettings::HsfExportVersion);
	}


	// if we're streaming an .hsf file, we need to start the file reading thread so that
	// reading is performed asynchronously

	if (pDoc->IsFileReadDeferedForView())
		LoadFile(pDoc->filename, hmodel->GetStreamFileTK());
	else
	{
		m_pHView->SetLineAntialiasing(CAppSettings::LineAntialiasing);
		m_pHView->SetTextAntialiasing(CAppSettings::TextAntialiasing);

		m_pHView->EmitSegment(hmodel->GetModelKey(), true);
		SetupViews();
		if (CAppSettings::UseFramerate && CAppSettings::CurrentFramerateMode==FramerateTarget)
			EnableFrameRate();
		
		ViewReady();
	}

	SetSceneFont( CAppSettings::FontName, CAppSettings::FontSize, CAppSettings::FontUnits );

	// subscribe to selection events
	m_CookieSelected = m_pHView->SetSignalNotify(HSignalSelected, CSolidHoopsView::signal_selected, this);
	m_CookieDeSelectedAll = m_pHView->SetSignalNotify(HSignalDeSelectedAll, CSolidHoopsView::signal_deselected_all, this);

	CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();
	frame->GetBhvToolbar()->m_wndBhvSlider.SetPos(0);


	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
	HC_Open_Segment("plane2");
	HC_Rotate_Object(90,0,0);
	HC_Close_Segment();
	HC_Open_Segment("plane3");
	HC_Rotate_Object(0,0,90);
	HC_Close_Segment();
	HC_Close_Segment();

	//apply hiding of overlapped text (or not)
	m_pHView->SetHideOverlappedText(CAppSettings::bHideOverlappedText);

	HC_Open_Segment_By_Key(m_pHView->GetShadowMapSegmentKey()); {
		if(CAppSettings::bShadowMap)
			sprintf(rendering_opts, "shadow map=(on, resolution=%d, samples=%d, %s jitter, %s)", 
			CAppSettings::nSMResolution, CAppSettings::nSMSamples,
			(CAppSettings::Jitter ? "" : "no"), 
			(CAppSettings::ViewDependentShadowMap ? "view dependent" : "view independent"));
		else 
			sprintf(rendering_opts, "no shadow map");
		HC_Set_Rendering_Options(rendering_opts);
	} HC_Close_Segment();

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey()); {
		HC_Set_Variable_Edge_Weight(H_ASCII_TEXT(CAppSettings::LineWeight));
		HC_Set_Variable_Line_Weight(H_ASCII_TEXT(CAppSettings::LineWeight));

		//apply stereo mode
		if(CAppSettings::StereoMode)
		{
			HCLOCALE (sprintf(rendering_opts, "stereo, stereo separation = %f", CAppSettings::StereoSeparation/10000.f));
			HC_Set_Rendering_Options(rendering_opts);
		}

		HCLOCALE (sprintf(rendering_opts, "simple shadow = (opacity = %f)", CAppSettings::ShadowOpacity));
		HC_Set_Rendering_Options(rendering_opts);

		char gooch_color_map[4096];
		sprintf(gooch_color_map, "(R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f)", 
			GetRValue(CAppSettings::GoochColor1)/255.0f, 
			GetGValue(CAppSettings::GoochColor1)/255.0f,
			GetBValue(CAppSettings::GoochColor1)/255.0f,
			GetRValue(CAppSettings::GoochColor2)/255.0f, 
			GetGValue(CAppSettings::GoochColor2)/255.0f,
			GetBValue(CAppSettings::GoochColor2)/255.0f,
			GetRValue(CAppSettings::GoochColor3)/255.0f, 
			GetGValue(CAppSettings::GoochColor3)/255.0f,
			GetBValue(CAppSettings::GoochColor3)/255.0f,
			GetRValue(CAppSettings::GoochColor4)/255.0f, 
			GetGValue(CAppSettings::GoochColor4)/255.0f,
			GetBValue(CAppSettings::GoochColor4)/255.0f,
			GetRValue(CAppSettings::GoochColor5)/255.0f, 
			GetGValue(CAppSettings::GoochColor5)/255.0f,
			GetBValue(CAppSettings::GoochColor5)/255.0f,
			GetRValue(CAppSettings::GoochColor6)/255.0f, 
			GetGValue(CAppSettings::GoochColor6)/255.0f,
			GetBValue(CAppSettings::GoochColor6)/255.0f);
		CAppSettings::GoochColorMap = gooch_color_map;	

		HC_Open_Segment("./overwrite/lights/gooch_color_map_segment");
			HC_Set_Color_Map(H_ASCII_TEXT(CAppSettings::GoochColorMap));
		HC_Close_Segment();

		HCLOCALE(sprintf(rendering_opts, "gooch options = (diffuse weight = %f, color range=(0.0, %f), color map segment = `./overwrite/lights/gooch_color_map_segment`)",
			CAppSettings::GoochWeight, CAppSettings::GoochColorHigh));
		HC_Set_Rendering_Options(rendering_opts);
		
		//set camera near limit
		HC_Set_Camera_Near_Limit(CAppSettings::NearCameraLimit/100000.f);

		//Apply curve geometry options
		char curve_opt[4096]; 

		HCLOCALE (sprintf(curve_opt, "general curve = (budget = %d, continued budget = %d, maximum deviation = %f, maximum angle = %f, maximum length = %f, %s view independent)", 
			CAppSettings::Budget, CAppSettings::ContinuedBudget, CAppSettings::MaxDeviation/10000.f, 
			CAppSettings::MaxAngle/10000.f, CAppSettings::MaxLength/10000.f, CAppSettings::bViewIndependent?"":"no"));

		HC_Set_Rendering_Options(curve_opt);

		m_pHView->SetReflectionPlane(CAppSettings::bReflectionPlane, CAppSettings::ReflectionOpacity, 
		CAppSettings::bReflectionFading, CAppSettings::ReflectionUseAttenuation,
		CAppSettings::ReflectionHither, CAppSettings::ReflectionYon,
		CAppSettings::ReflectionUseBlur, CAppSettings::ReflectionBlur);

		char ambient_color[MVO_BUFFER_SIZE];
		if(CAppSettings::HemisphericAmbient)
		{
			float r1, g1, b1, r2, g2, b2;
			char ropt[MVO_BUFFER_SIZE];

			//darken all colors by about 75%
			r1=(GetRValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
			g1=(GetGValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
			b1=(GetBValue(CAppSettings::AmbientTopColor)>>2)/255.0f;

			r2=(GetRValue(CAppSettings::AmbientBottomColor)>>2)/255.0f;
			g2=(GetGValue(CAppSettings::AmbientBottomColor)>>2)/255.0f;
			b2=(GetBValue(CAppSettings::AmbientBottomColor)>>2)/255.0f;

			sprintf(ambient_color, "ambient up=(R=%f G=%f B=%f), ambient down=(R=%f G=%f B=%f)", 
				r1, g1, b1, r2, g2, b2);
			
			HC_Set_Color(ambient_color);
			HC_Define_System_Options("disable ambient material");

			if(CAppSettings::UseAmbientUpVector)
			{
				HCLOCALE (sprintf(ropt, "ambient up vector = (%f, %f, %f)",
				CAppSettings::AmbientUpVector.x, CAppSettings::AmbientUpVector.y, 
				CAppSettings::AmbientUpVector.z));
				HC_Set_Rendering_Options(ropt);
			}
			else
			{
				HC_Set_Rendering_Options("no ambient up vector");
			}

		}
		else
		{
			float r1, g1, b1;

			//darken all colors by about 75%
			r1=(GetRValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
			g1=(GetGValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
			b1=(GetBValue(CAppSettings::AmbientTopColor)>>2)/255.0f;

			HCLOCALE (sprintf(ambient_color, "ambient=(R=%f G=%f B=%f)", r1, g1, b1));
			HC_Set_Color(ambient_color);
			HC_Set_Rendering_Options("no ambient up vector");
			HC_Define_System_Options("no disable ambient material");
		}


		//Apply Greeking Settings
		char cGreekingSettings[2048]="no greeking limit";
		if(CAppSettings::bUseGreeking)
		{
			CString csGreekingSettings;
			csGreekingSettings.Format(_T("greeking mode= %s, greeking limit= %f %s"), 
				CAppSettings::GreekingMode,	CAppSettings::GreekingLimit/1000.f, 
				CAppSettings::GreekingUnits);
			strcpy(cGreekingSettings, H_ASCII_TEXT(csGreekingSettings));
		}
		HC_Set_Text_Font(cGreekingSettings);
	} HC_Close_Segment();

	//new HDebugZBuffer( m_pHView );

	if(CAppSettings::ChildStartMaximized)
	{
		WINDOWPLACEMENT wp;
		this->GetParent()->GetWindowPlacement(&wp);
		wp.showCmd = SW_SHOWMAXIMIZED;
		this->GetParent()->SetWindowPlacement(&wp);
	}

	m_pHView->SetLightCount(CAppSettings::LightCount); 

#if defined(ACIS) || defined(PARASOLID)
	m_pHView->SetViewSelectionLevel(HSelectionLevelEntity);
#else
	m_pHView->SetViewSelectionLevel(HSelectionLevelSegment);
#endif

	// do all the setup with no updates
	m_pHView->SetSuppressUpdate(false); 
 
}

/*!
  Sets up rendermode/camera/shadow for the views or split view (if any).
*/
void CSolidHoopsView::SetupViews()
{
	m_pHView->SetRenderMode(CAppSettings::RenderMode, true);
	m_pHView->SetShadowMode(CAppSettings::ShadowMode);
	m_pHView->SetOcclusionCullingMode(CAppSettings::OcclusionCulling, true);
}

void CSolidHoopsView::OnPaint()
{
	if (m_pHView->GetModel()->GetFileLoadComplete())
		CHoopsView::OnPaint();
}


void CSolidHoopsView::OnAnnotateModel() 
{
	LocalSetOperator(new HOpObjectAnnotate(m_pHView));
}

void CSolidHoopsView::OnUpdateAnnotateModel(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpObjectAnnotate"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnShaded() 
{

#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)		
		((HSolidView *)m_pHView)->DisableHiddenLine(); 
#endif // PARASOLID

	m_pHView->SetRenderMode(HRenderGouraud, true);

	m_edges = false;
	m_lights = true;
	m_bFastPrint = true;

	m_pHView->Update();
	
}

void CSolidHoopsView::OnUpdateShaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		(m_pHView->GetRenderMode() == HRenderGouraud) ||(m_pHView->GetRenderMode() == HRenderPhong)|| (m_pHView->GetRenderMode() == HRenderShaded)
		|| (m_pHView->GetRenderMode() == HRenderShadedWithLines) || (m_pHView->GetRenderMode() == HRenderGouraudWithLines))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnHiddenLineButton()
{
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)		
		((HSolidView *)m_pHView)->DisableHiddenLine(); 
	
	HConstantFrameRate *cframerate = m_pHView->GetConstantFrameRateObject();
	cframerate->Stop();	
	cframerate->Shutdown();   

	m_bFastPrint = false;

	if(CAppSettings::HiddenLineMode==FastHiddenLine)
		m_pHView->SetRenderMode(HRenderHiddenLineFast, true);
	else if(CAppSettings::HiddenLineMode==FakeHiddenLine)
		m_pHView->SetRenderMode(HRenderFakeHiddenLine, true);
	else
		m_pHView->SetRenderMode(HRenderHiddenLine, true);
	
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateHiddenLineButton(CCmdUI* pCmdUI)
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		((m_pHView->GetRenderMode() == HRenderHiddenLine) ||
		(m_pHView->GetRenderMode() == HRenderHiddenLineHOOPS) || 
		(m_pHView->GetRenderMode() == HRenderHiddenLineFast) || 
		(m_pHView->GetRenderMode() == HRenderBRepHiddenLine) || 
		(m_pHView->GetRenderMode() == HRenderBRepHiddenLineFast) ||
		(m_pHView->GetRenderMode() == HRenderFakeHiddenLine)))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeFlatshaded() 
{
	m_pHView->RenderFlat();	

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Visibility("faces = on, edges=off, lines = off");
	HC_Close_Segment();

	m_edges = false;
	m_lights = true;

	m_bFastPrint = true;

	m_pHView->Update();
}

void CSolidHoopsView::OnToolsRendermodeLOD1() 
{
	m_pHView->RenderLOD1();
	m_pHView->Update();
}

void CSolidHoopsView::OnToolsRendermodeLOD2() 
{
	m_pHView->RenderLOD2();
	m_pHView->Update();
}

void CSolidHoopsView::OnToolsRendermodeShadedWithLines() 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)		
		((HSolidView *)m_pHView)->DisableHiddenLine(); 
#endif // PARASOLID
	m_pHView->RenderGouraudWithLines();
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsRendermodeShadedWithLines(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderGouraudWithLines)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnUpdateToolsRendermodeFlatshaded(CCmdUI* pCmdUI) 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();
#endif // PARASOLID
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderFlat)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnToolsRendermodeGouraudshaded() 
{
	HSolidModel * model = (HSolidModel *)(m_pHView->GetModel());

	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();
	m_pHView->RenderGouraud();

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Visibility("faces = on");
		if (model->IsBRepGeometry())
		{
			if (m_edges)
				HC_Set_Visibility("lines = on, edges = off");
			else
				HC_Set_Visibility("lines = off, edges = off");
		} 
		else 
		{
			if (m_edges)
				HC_Set_Visibility("edges = on, lines = on");
			else
				HC_Set_Visibility("edges = off, lines = off");
		}
	HC_Close_Segment();

	m_bFastPrint = true;

	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsRendermodeGouraudshaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderGouraud)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnToolsRendermodeHiddenline() 
{

	HConstantFrameRate *cframerate = m_pHView->GetConstantFrameRateObject();
	cframerate->Stop();
	cframerate->Shutdown();

#ifdef PARASOLID	
	HSolidModel * model = (HSolidModel *)(m_pHView->GetModel());
	// do not use precise hidden line rendering if we do not have a parasolid model - Rajesh B
	if ( (model->m_bSolidData) && (!model->m_bPlainSolidModel))
	{
		HC_Open_Segment_By_Key(m_pHView->GetViewKey());
	        HC_Set_Heuristics("no hidden surfaces");
		HC_Close_Segment();
		HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
			HC_Set_Visibility("faces = off, lines = on, edges = on");
		HC_Close_Segment();

		m_bFastPrint = false;
		// Set the HOOPS Projection mode
		
		((HSolidView *)m_pHView)->EnableHiddenLine(); 

		m_pHView->SetRenderMode(HRenderHiddenLine, true);
 		m_pHView->Update();
	}
	else
#endif	//PARASOLID
// There seems to be lots of problems with ACIS hidden line stuff. So for now,
// using HOOPS inhouse hidden line algo - Rajesh B (30-Mar-01)
	{
 		m_bFastPrint = false;
 		m_pHView->SetRenderMode(HRenderHiddenLine, true);
		m_pHView->Update();
	}

}

void CSolidHoopsView::OnUpdateToolsRendermodeHiddenline(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderHiddenLine || m_pHView->GetRenderMode() == HRenderHiddenLineHOOPS 
		|| m_pHView->GetRenderMode() == HRenderHiddenLineFast)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnToolsRendermodeBRepHiddenline() 
{


	if (m_pHView->GetRenderMode() == HRenderHiddenLine)		
		((HSolidView *)m_pHView)->DisableHiddenLine(); 

// There seems to be lots of problems with ACIS hidden line stuff. So for now,
// using HOOPS inhouse hidden line algo - Rajesh B (30-Mar-01)
	{
		m_bFastPrint = false;
		m_pHView->SetRenderMode(HRenderBRepHiddenLine, true);
		m_pHView->Update();
	}
	HConstantFrameRate *cframerate = m_pHView->GetConstantFrameRateObject();
	cframerate->Stop();
	cframerate->Shutdown();

}

void CSolidHoopsView::OnUpdateToolsRendermodeBRepHiddenline(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		(m_pHView->GetRenderMode() == HRenderBRepHiddenLine ||
		 m_pHView->GetRenderMode() == HRenderBRepHiddenLineFast))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeBRepWireframe() 
{
	if (m_pHView->GetRenderMode()==HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();

	m_pHView->RenderBRepWireframe();

	m_bFastPrint = false;
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsRendermodeBRepWireframe(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderBRepWireframe)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeFakeHiddenLine() 
{
	if (m_pHView->GetRenderMode()==HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();

	m_pHView->RenderFakeHiddenLine();

	m_bFastPrint = true;
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsRendermodeFakeHiddenLine(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderFakeHiddenLine)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodePhongshaded() 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();
#endif // PARASOLID
	m_pHView->RenderPhong();

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Visibility("faces = on, edges=off, lines = off");
	HC_Close_Segment();

	m_edges = false;

	m_bFastPrint = true;

	m_pHView->Update();
	
}

void CSolidHoopsView::OnUpdateToolsRendermodePhongshaded(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderPhong)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeWireframe() 
{
	if (m_pHView->GetRenderMode()==HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();

	m_pHView->RenderWireframe();

	m_bFastPrint = false;
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsRendermodeWireframe(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderWireframe)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnToolsRendermodeTriangulation() 
{
	if (m_pHView->GetRenderMode()==HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();

	m_pHView->RenderFlat();
	m_pHView->SetRenderMode(HRenderTriangulation, true);
 
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Visibility("edges = on, lines = off, faces =on");
		HC_Set_Rendering_Options("no lighting interpolation");
    HC_Close_Segment();

//	m_edges = true;
//	m_faces = false;
//	m_lights = false;

	m_bFastPrint = true;
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsRendermodeTriangulation(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderTriangulation)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeSilhouette() 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();
#endif // PARASOLID
	m_pHView->RenderSilhouette();
	m_edges = false;
	m_bFastPrint = true;
	m_pHView->Update();
}
void CSolidHoopsView::OnUpdateToolsRendermodeSilhouette(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderSilhouette)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeGoochShaded()
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderGoochShaded)
		((HSolidView *)m_pHView)->DisableHiddenLine();
#endif // PARASOLID
	m_pHView->RenderGooch();

	m_edges = false;
	m_bFastPrint = true;

	m_pHView->Update();
}
void CSolidHoopsView::OnUpdateToolsRendermodeGoochShaded(CCmdUI* pCmdUI)
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderGoochShaded)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeWireframeWithSilhouette() 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)		
		((HSolidView *)m_pHView)->DisableHiddenLine(); 
#endif // PARASOLID
	m_pHView->RenderWireframeWithSilhouette();
	m_edges = false;
	m_bFastPrint = true;
	m_pHView->Update();
}
void CSolidHoopsView::OnUpdateToolsRendermodeWireframeWithSilhouette(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderWireframeWithSilhouette)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeShadedWireframe() 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();
#endif // PARASOLID
	m_pHView->RenderShadedWireframe();
	m_edges = false;
	m_bFastPrint = true;
	m_pHView->Update();
}
void CSolidHoopsView::OnUpdateToolsRendermodeShadedWireframe(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderShadedWireframe)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeVertices() 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();
#endif // PARASOLID
	m_pHView->RenderVertices();
	m_edges = false;
	m_bFastPrint = true;
	m_pHView->Update();
}
void CSolidHoopsView::OnUpdateToolsRendermodeVertices(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderVertices)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToolsRendermodeShadedVertices() 
{
#ifdef PARASOLID
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
		((HSolidView *)m_pHView)->DisableHiddenLine();
#endif // PARASOLID
	m_pHView->RenderShadedVertices();
	m_edges = false;
	m_bFastPrint = true;
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsRendermodeShadedVertices(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetRenderMode() == HRenderShadedVertices)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnToolsTextFontsArial() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Text_Font("name=arial.ttf");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnToolsTextFontsCave() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Text_Font("name=cave.pfa");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnToolsTextFontsRoman() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Text_Font("name = roman");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnToolsTextTransformsCharacterpositiononly() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Text_Font("transforms = character position only");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnToolsTextTransformsOff() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
	HC_Set_Text_Font("transforms = off");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnToolsTextTransformsOn() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Text_Font("transforms = on");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnTextTransforms() 
{
	char cval[MVO_BUFFER_SIZE];
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Show_One_Net_Text_Font ("transforms", cval);
		if(streq(cval, "on"))
			HC_Set_Text_Font("transforms = off");
		else
			HC_Set_Text_Font("transforms = on");
	HC_Close_Segment();
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateTextTransforms(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		char cval[MVO_BUFFER_SIZE];
		HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
			HC_Show_One_Net_Text_Font ("transforms", cval);
			if(streq(cval, "on"))
				pCmdUI->SetCheck(1);
			else
				pCmdUI->SetCheck(0);
		HC_Close_Segment();
	}
}

void CSolidHoopsView::OnCreateCuttingPlane() 
{
	if (!m_pHView->GetCuttingPlanesExist("plane1")) {
		HC_KEY key = HUtilityGeometryCreation::CreateCuttingPlane(m_pHView,"plane1");
		HUtilityGeomHandle::SetupCuttingPlaneManipulator(key, m_pHView);
		m_pHView->Update();
	}
	else {
		HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
			HC_Open_Segment("plane1");
				HUtilityGeomHandle::ClearAllHandles(0);
				if (!(GetAsyncKeyState(VK_SHIFT) & 32768))
					HC_Flush_Contents ("...", "geometry");
			HC_Close_Segment();
		HC_Close_Segment();
		m_pHView->Update();
	}

	HUtilityGeometryCreation::AdjustCuttingPlaneRendering(m_pHView);
}

void CSolidHoopsView::OnUpdateCreateCuttingPlane(CCmdUI* pCmdUI) 
{
	if(!CAppSettings::DisableEditing)
		pCmdUI->Enable (1);
	else
		pCmdUI->Enable (0);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetHandleOperator() && m_pHView->GetCuttingPlanesExist("plane1"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnModelAnnotate() 
{
	LocalSetOperator(new HOpObjectAnnotate(m_pHView));
}

void CSolidHoopsView::OnUpdateModelAnnotate(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpObjectAnnotate"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnRotate() 
{
//  the solid modeler specific rotate operator (HSOpObjectRotate) is disabled
//  for now due to problems with it

#ifdef HOOPS_ONLY
	LocalSetOperator(new HOpObjectRotate(m_pHView));	
	m_pHView->Update();
#endif // HOOPS_ONLY
}

void CSolidHoopsView::OnUpdateRotate(CCmdUI* pCmdUI) 
{
#ifdef HOOPS_ONLY
	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();
	assert(sel_set);

	if	(!CAppSettings::DisableEditing 
		 && (sel_set->GetSelectLevel() == SEGMENT_TYPE) 
		 && (sel_set->GetSize() <= 1) )
		pCmdUI->Enable (1);
	else
		pCmdUI->Enable (0);
	

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(),"HOpObjectRotate"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
#else
	// needs to be implemented solid modeler partviewer
	pCmdUI->Enable (0);	
#endif // HOOPS_ONLY
}

void CSolidHoopsView::OnSelectionDeleteselection() 
{
	m_pHView->DeleteSelectionList(true);
	m_pHView->Update();	

	if(m_pDlgSegmentBrowser && m_pDlgSegmentBrowser->IsWindowVisible())
		m_pDlgSegmentBrowser->RefreshBrowser();
	if(m_pDlgModelBrowser)
		m_pDlgModelBrowser->ValidateModelTree();
#ifndef HOOPS_ONLY
	if(m_pDlgTopologyBrowser)
		m_pDlgTopologyBrowser->ValidateTopolTree();
#endif // HOOPS_ONLY


}

void CSolidHoopsView::OnUpdateSelectionDeleteselection(CCmdUI* pCmdUI) 
{
	HSSelectionSet * sel_set = (HSSelectionSet *)(GetSolidView()->GetSelection());
#ifdef HOOPS_ONLY
	if	( sel_set->GetSize() > 0 )
		pCmdUI->Enable(true);
    else
        pCmdUI->Enable(false);
#else
	pCmdUI->Enable (0);	
#endif // HOOPS_ONLY
}


void CSolidHoopsView::OnSelectionFocus() 
{
	if(m_pHView->GetFocusOnSelection())
		m_pHView->FocusOnSelection(false);
	else 
		m_pHView->FocusOnSelection(true);
	m_pHView->Update();	

	if(m_pDlgSegmentBrowser && m_pDlgSegmentBrowser->IsWindowVisible())
		m_pDlgSegmentBrowser->RefreshBrowser();
	if(m_pDlgModelBrowser)
		m_pDlgModelBrowser->ValidateModelTree();
#ifndef HOOPS_ONLY
	if(m_pDlgTopologyBrowser)
		m_pDlgTopologyBrowser->ValidateTopolTree();
#endif // HOOPS_ONLY
}

void CSolidHoopsView::OnUpdateSelectionFocus(CCmdUI* pCmdUI) 
{
	HSSelectionSet * sel_set = (HSSelectionSet *)(GetSolidView()->GetSelection());
#ifdef HOOPS_ONLY
	if((sel_set->GetSize() > 0 || m_pHView->GetFocusOnSelection()))
	{
		pCmdUI->Enable(true);

		if (m_pHView->GetFocusOnSelection())
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
    else
#endif // HOOPS_ONLY
	{
        pCmdUI->Enable(false);
		pCmdUI->SetCheck (0);
	}
}



void CSolidHoopsView::OnViewAnimate() 
{
	float t0, t1, fsec, tsec;
	int tisec;
	TCHAR temp[MVO_BUFFER_SIZE];
	long int mem_alloc = 0;
	long int mem_used = 0;
	int animation_steps = 30;
	int total_animation_steps = 0;
	float minimum_time = 3;			//seconds

	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	CSolidHoopsFrame *pFrm = ((CSolidHoopsFrame *)AfxGetMainWnd());

	pFrm->GetStatusBar()->SetPaneText(0,H_TEXT("Collecting performance data..."));

	HC_Control_Update_By_Key(m_pHView->GetViewKey(), "redraw everything");
	HC_Update_Display();

	HC_Show_Time(&t0);

	do {
		if (!(GetAsyncKeyState(VK_SHIFT) & 32768))
			m_pHView->Animate(animation_steps, HBaseView::HAnimateScene);
		else 
			m_pHView->Animate(animation_steps, HBaseView::HAnimateScene,2);

		total_animation_steps += animation_steps;
		HC_Show_Time(&t1);
	} while(t1 - t0 < minimum_time);
	

	HC_Show_Memory_Usage (&mem_alloc, &mem_used);

	pFrm->GetStatusBar()->SetPaneText(0,H_TEXT("Collecting model data..."));
	HModelInfo* pModInfo = pDoc->GetHoopsModel()->GetHModelInfo();
	fsec = total_animation_steps/(t1-t0); 
	tsec = pModInfo->GetTotalTriangles() * fsec;
	tisec = (int)tsec;
	
	pFrm->GetStatusBar()->SetPaneText(0,H_TEXT("Ready"));
#ifndef HOOPS_QA
	_stprintf(temp, _T("Performance: %f frames per second.  %d triangles per second\n")
		      _T("Memory: %ld KB allocated. %ld KB used\n")
		      _T("Model Information:\n")
			  _T("\tSegments  - %d\n")
			  _T("\tShells    - %d\n")
			  _T("\tTriangles - %d\n")
			  _T("\tVertices  - %d\n"),
				   fsec, tisec, mem_alloc/1024, mem_used/1024,
				   pModInfo->GetTotalSegments(), pModInfo->GetTotalShell(), 
				   pModInfo->GetTotalTriangles(), pModInfo->GetTotalVertices());

	AfxMessageBox(temp);
#else

	_stprintf(temp, _T("Performance: %f frames per second.  %d triangles per second\n"), fsec, tisec);

	((CHoopsApp *)AfxGetApp())->GetCTDriver()->SetWindowText(temp);
	
#endif


}

void CSolidHoopsView::OnUpdateViewAnimate(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnUpdateSegmentBrowserButton(CCmdUI* pCmdUI)
{
}

void CSolidHoopsView::OnToolsVisibilityVertices()
{

#ifdef HOOPS_ONLY
	HSolidView * pHView = (HSolidView*) GetHoopsView();
	assert(pHView);
	pHView->SetVisibilityVertices(!pHView->GetVisibilityVertices());

	HSelectionSet * selection=pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	pHView->Update();


#endif
#if defined(ACIS) || defined(PARASOLID)
	HSolidView * pHView = GetSolidView();
	pHView->SetVisibilityMarkersOnly(!pHView->GetVisibilityMarkersOnly());
	HSelectionSet * selection=pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	m_pHView->Update();	

	if(m_pDlgTopologyBrowser && m_pDlgTopologyBrowser->IsWindowVisible())
		m_pDlgTopologyBrowser->UpdateTopolBrowserCheckboxes();
#endif // ACIS
	
}

void CSolidHoopsView::OnUpdateToolsVisibilityVertices(CCmdUI* pCmdUI)
{
#if defined(ACIS) || defined(PARASOLID)
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		GetSolidView()->GetVisibilityMarkersOnly())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
#endif
#ifdef	HOOPS_ONLY
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		GetSolidView()->GetVisibilityVertices())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
#endif
}

void CSolidHoopsView::OnToolsVisibilityHiddenlines() 
{
	if (m_hidden_lines_visible) 
	{
		m_hidden_lines_visible = false;
		
		HC_Open_Segment_By_Key(m_pHView->GetViewKey());
			HC_Set_Rendering_Options("hlro = (visibility = off)");
		HC_Close_Segment();
	}
	else 
	{
		m_hidden_lines_visible = true;
		
		HC_Open_Segment_By_Key(m_pHView->GetViewKey());
			HC_Set_Rendering_Options("hlro = (visibility = on)");
		HC_Close_Segment();	
	}

	// workaround a minor bug where a change to hlro does not set redraw flag 
	 
	HC_Open_Segment_By_Key(GetViewKey());
		HC_Control_Update(".", "redraw everything");
	HC_Close_Segment();

	HSelectionSet * selection=m_pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	m_pHView->Update();	
}

void CSolidHoopsView::OnToolsVisibilityText() 
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
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

	HSelectionSet * selection=m_pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	m_pHView->Update();	
}

void CSolidHoopsView::OnToolsVisibilityImages() 
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		if (m_images)
		{
			m_images = false;
			HC_Set_Visibility ("images = off");
		}
		else
		{
			m_images = true;
			HC_Set_Visibility ("images = on");
		}
    HC_Close_Segment ();

	HSelectionSet * selection=m_pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

    m_pHView->Update();	
}

void CSolidHoopsView::OnToolsVisibilityGrids() 
{
	HC_Open_Segment_By_Key (m_pHView->GetCuttingPlanesKey());
        if (m_grids) {
            m_grids = false;
            HC_Set_Visibility ("edges = off");

        }
        else {
            m_grids = true;
            HC_Set_Visibility ("edges = on");
        }
    HC_Close_Segment ();

	HSelectionSet * selection=m_pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();


    m_pHView->Update();
}

void CSolidHoopsView::OnToolsTransparency() 
{
	//This way is probably slower, so I've commented it out.
	/*HC_KEY sel = HUtility::SelectUnderCursor(m_pHView, m_PositionOnRightClick.x, m_PositionOnRightClick.y, false);
    sel = HUtility::GrabSegment(sel);
	HC_Open_Segment_By_Key(sel);*/

	char type[MVO_BUFFER_SIZE];
	HC_KEY key;

	HC_Show_Key_Type(m_KeyUnderCursor, type);

	if(streq(type, "segment"))
		key=m_KeyUnderCursor;
	else
		key=HC_KShow_Owner_By_Key(m_KeyUnderCursor);

	HC_Open_Segment_By_Key(key);

		float color[3];
		HC_KEY keys[1000];
		int count;

		HC_Show_Selection_Keys( &count, keys );

		HC_PShow_Net_Explicit_Color(count, keys, "faces", "transmission", &color[0], 0, 0);

		//if not transparent
		if(color[0] == 0 && color[1] == 0 && color[2] == 0)
		{
			char transparent_color[1024];
			char usertransmission[1024];

			//if transparency has been saved, then restore it and remove the user option
			HC_Show_One_Net_User_Option("HUserTransmission",usertransmission);
			if(strcmp(usertransmission, "") != 0)
			{
				sprintf(transparent_color, "faces = (transmission = %s)",usertransmission);
				HC_UnSet_One_User_Option("HUserTransmission");
			}
			else
				sprintf(transparent_color, "faces = (transmission = r=%f g=%f b=%f)",m_default_transmission,m_default_transmission,m_default_transmission);
			
			if (key!=m_KeyUnderCursor) {
				HC_Open_Geometry(m_KeyUnderCursor);
				HC_Set_Color(transparent_color);
				HC_Close_Geometry();
			}
			else
				HC_Set_Color(transparent_color);
		}
		//if transparent
		else
		{
			//if the transmission color isn't the default, then set a user option to save it
			if(color[0] != m_default_transmission && color[1] != m_default_transmission && color[2] != m_default_transmission)
			{
				char usertransmission[1024];
				sprintf(usertransmission, "HUserTransmission = r=%f g=%f b=%f", color[0], color[1], color[2]);
				HC_Set_User_Options(usertransmission);
			}

			if (key!=m_KeyUnderCursor) {
				HC_Open_Geometry(m_KeyUnderCursor);
				HC_Set_Color("faces = (transmission = black)");
				HC_Close_Geometry();
			}
			else
				HC_Set_Color("faces = (transmission = black)");
		}

	HC_Close_Segment();
	
	m_pHView->Update();
}

void CSolidHoopsView::OnViewDisplaylists() 
{
	m_pHView->SetDisplayListMode(!m_pHView->GetDisplayListMode());
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateViewDisplaylists(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetDisplayListMode())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnViewLevelofdetail() 
{
	if (m_pHView->GetLodMode()) 
		m_pHView->SetLodMode(false);
	else 
		m_pHView->SetLodMode(true);

	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateViewLevelofdetail(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetLodMode()) 
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnViewLevelofdetailoptions() 
{
	m_lod_dialog->ShowWindow(SW_SHOW); 
}

void CSolidHoopsView::OnViewPolygonhandednessLeft() 
{
	SetPolygonHandedness(HandednessSetLeft);
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateViewPolygonhandednessLeft(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetPolygonHandednessMode() == HandednessLeft)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnViewPolygonhandednessNone() 
{
	SetPolygonHandedness(HandednessSetNone);
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateViewPolygonhandednessNone(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetPolygonHandednessMode() == HandednessNone)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnViewPolygonhandednessRight() 
{
	SetPolygonHandedness(HandednessSetRight);
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateViewPolygonhandednessRight(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetPolygonHandednessMode() == HandednessRight)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnFrameRateoptions() 
{
	
}

void CSolidHoopsView::OnMeasuredistance() 
{
	LocalSetOperator(new HOpMarkupMeasure(m_pHView));
}

void CSolidHoopsView::OnUpdateMeasuredistance(CCmdUI* pCmdUI) 
{
	if (!CAppSettings::DisableEditing)
		pCmdUI->Enable (1);
	else
		pCmdUI->Enable (0);
	
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupMeasure"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnFlushHardwareResources() 
{
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Flush_Contents("....", "hardware resources");
	HC_Close_Segment();
}

void CSolidHoopsView::OnUpdateFlushHardwareResources(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (1);
}

void CSolidHoopsView::OnRelinquishMemory()
{
	HC_Relinquish_Memory();
}

void CSolidHoopsView::OnUpdateRelinquishMemory(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(1);
}


void CSolidHoopsView::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == H_TIMER_BHV_UPDATE)		//we like to temporary increase the detail level
	{										//this means of course that timer id 1 is reserved
		UpdateBhvWindows(false);

	}
	else
		CHoopsView::OnTimer(nIDEvent);
}

void CSolidHoopsView::OnZoomToSelection() 
{
#if defined(ACIS) || defined(GRANITE) || defined(HOOPS_ONLY)
	// If we are in hidden line mode, fallback to fast hidden line for the 
	// smooth transition purposes. 
	// Rajesh B (10-Apr-03)
	bool is_hiddenline = false;
	bool is_brephiddenline = false;
	if (m_pHView->GetRenderMode() == HRenderHiddenLine)
	{
		is_hiddenline = true;
		m_pHView->SetRenderMode(HRenderHiddenLineFast);
	}
	if (m_pHView->GetRenderMode() == HRenderBRepHiddenLine)
	{
		is_brephiddenline = true;
		m_pHView->SetRenderMode(HRenderBRepHiddenLineFast);
	}
#endif

    if 	(((HSolidModel *)(m_pHView->GetModel()))->m_bPlainSolidModel)
		((HSolidView *)m_pHView)->FitWorldToHOOPSSelection();
	else
		((HSolidView *)m_pHView)->FitWorldToSelection();

#if defined(ACIS) || defined(GRANITE) || defined(HOOPS_ONLY)
	if (is_hiddenline)
		m_pHView->SetRenderMode(HRenderHiddenLine);
	if (is_brephiddenline)
		m_pHView->SetRenderMode(HRenderBRepHiddenLine);
#endif	// ACIS || GRANITE

	if (m_pHView->GetRenderMode()==HRenderHiddenLine)		
		((HSolidView *)m_pHView)->UpdateHiddenLine(); 
    m_pHView->Update();
	
}

void CSolidHoopsView::OnUpdateZoomToSelection(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (0);
}
 
void CSolidHoopsView::OnFacesaslines() 
{
	HSSelectionSet* selection = (HSSelectionSet*) (m_pHView->GetSelection());
	selection->SetFacesAsLines(!selection->GetFacesAsLines());
}

void CSolidHoopsView::OnUpdateFacesaslines(CCmdUI* pCmdUI) 
{
	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidData)
		pCmdUI->Enable (0);
	else
	{
		pCmdUI->Enable (1);
		HSSelectionSet* selection = (HSSelectionSet*) (m_pHView->GetSelection());
		if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
			selection->GetFacesAsLines())
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
}

void CSolidHoopsView::OnDemoanimation() 
{
	float t0,t1;
	float time_max = 50.0;					//maximum time (s)
	float time_min = 3.0;					//minimum time (s)
	int   pausetime = 5;					//delay time when highest detail is reached 

	int idletime=0;

	float target_time;
	HConstantFrameRate *cframerate = m_pHView->GetConstantFrameRateObject();
	cframerate->ResetListPointers(); 
 	cframerate->Start();
	float old_framerate = cframerate->GetTargetFrameRate();
	cframerate->SetTargetFrameRate(time_min);
 	target_time = time_max;

 	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	cframerate->SetDetailIncMode(NoDetailChange);
	cframerate->SetDetailDecMode(AllowDetailChange);
	cframerate->SetEmergencyDetailDecrease(false);	

	cframerate->SetDeadZone(2.0);
 
  	
	HC_Show_Time(&t0);   
	for (;;) {
		HC_Show_Time(&t1);
		
		if (t1-t0 > 0.5)				//0.5 seconds delay before target framerate is 
		{								//changed by 1 second
			
			HC_Show_Time(&t0);
			if (!idletime)				
			{
				float fr = cframerate->GetTargetFrameRate();
				if (fr>target_time)
					cframerate->SetTargetFrameRate(fr-1);					
				else if (fr<target_time)
					cframerate->SetTargetFrameRate(fr+1);					
				else
				{
					if (target_time == time_max)
					{
						cframerate->SetDetailIncMode(AllowDetailChange);
						cframerate->SetDetailDecMode(NoDetailChange);
						target_time = time_min;
					}
					else
					{
						idletime=pausetime;
						cframerate->SetDetailIncMode(NoDetailChange);
						cframerate->SetDetailDecMode(AllowDetailChange);
						target_time = time_max;
					}			
				}
			}
			else
				idletime--;	
						
			MSG msg;			
			if (PeekMessage (&msg, m_hWnd, WM_MOUSEMOVE, WM_MOUSEMOVE, PM_NOREMOVE))
				break;
		}
		
		if (!idletime)
		{
			// update default light
			
			HPoint	camera;

			HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
			HC_Move_Distant_Light(m_pHView->GetDefaultLightKey(), camera.x, camera.y, camera.z);
			HC_Orbit_Camera (4.0, 0.0);

			m_pHView->Update();
		}
		
		
	}
    HC_Close_Segment ();

	cframerate->SetDeadZone(5.0);
	cframerate->SetTargetFrameRate(old_framerate);
	cframerate->SetDetailIncMode(NoDetailChange);
	cframerate->SetDetailDecMode(AllowDetailChange);	
	cframerate->SetEmergencyDetailDecrease(true);	
	cframerate->Stop();
}

void CSolidHoopsView::OnViewWindowColor() 
{
	int r=0,g=0,b=0;

	CColorDialog cd;
	cd.m_cc.Flags |=  CC_RGBINIT;
	cd.m_cc.rgbResult = RGB(r, g, b);
	
	if(IDOK == cd.DoModal())
	{
		COLORREF newColor = cd.GetColor();
		SetWindowColor(newColor, newColor);
	}

	HC_Control_Update_By_Key (m_pHView->GetViewKey(), "redraw everything");
	m_pHView->Update();
}

void CSolidHoopsView::OnInstance() 
{
#ifdef PARASOLID
	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	sel_set->DeSelectAll();
	sel_set->SetSelectLevel(PK_CLASS_instance);
 
	m_pHView->Update();

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	  HC_Set_Selectability("faces = on, lines = on, edges = off");
	HC_Close_Segment();
#endif // PARASOLID
}

void CSolidHoopsView::OnAssembly() 
{
#ifdef PARASOLID
 	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	sel_set->DeSelectAll();
	sel_set->SetSelectLevel(PK_CLASS_assembly);

	m_pHView->Update();

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	  HC_Set_Selectability("faces = on, lines = on, edges = off");
	HC_Close_Segment();
#endif // PARASOLID
#ifdef ACIS
	HSSelectionSet* sel_set = (HSSelectionSet *)m_pHView->GetSelection();

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	sel_set->DeSelectAll();
	sel_set->SetSelectLevel(KERN_INSTANCE_TYPE);

	m_pHView->Update();

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	HC_Set_Selectability("faces = on, lines = on, edges = off");
	HC_Close_Segment();
#endif

}


void CSolidHoopsView::OnUpdateAssembly(CCmdUI* pCmdUI) 
{
	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidData)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

#ifdef PARASOLID
	PK_CLASS_t class_type;
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == PK_CLASS_assembly)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
#endif // PARASOLID
#ifdef ACIS
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		KERN_CLASS_TYPEDEF class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == KERN_INSTANCE_TYPE)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
#endif
 	
}

void CSolidHoopsView::OnUpdateInstance(CCmdUI* pCmdUI) 
{
	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidData)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

#ifdef PARASOLID
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		PK_CLASS_t class_type;
		class_type = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
		if (class_type == PK_CLASS_instance)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
#endif // PARASOLID
}

void CSolidHoopsView::OnTranslate() 
{
#ifdef HOOPS_ONLY
	LocalSetOperator(new HOpObjectTranslate(m_pHView));
#else
	LocalSetOperator(new HSOpObjectTranslate(m_pHView));
#endif // HOOPS_ONLY
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateTranslate(CCmdUI* pCmdUI) 
{
	// gray out if face, edge or vertex is selected
	HSSelectionSet * sel_set = (HSSelectionSet *)GetSolidView()->GetSelection();
	KERN_CLASS_TYPEDEF sel_level = sel_set->GetSelectLevel();

#ifdef HOOPS_ONLY
	if	(!CAppSettings::DisableEditing 
		&& (sel_level == SEGMENT_TYPE) 
		&& (sel_set->GetSize() >= 0) )
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	
#else	
	if (   (sel_set->GetSize() < 1)
		|| (sel_level == KERN_FACE_TYPE)
		|| (sel_level == KERN_EDGE_TYPE)
		|| (sel_level == KERN_VERTEX_TYPE) )
	{
		pCmdUI->Enable(0);
		return;
	}
#endif // HOOPS_ONLY

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(),"HOpObjectTranslate"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnFileLoad() 
{
	CString filter = _T("");
	CString def_ext = ".hsf";

#ifdef PARASOLID
	filter = "Parasolid Part Files (*.x_t*;*.xmt_*)|*.x_t*;*.xmt_*|ParaHOOPS Stream Files (*.psf)|*.psf|";
	def_ext = ".x_t";
#endif // PARASOLID
#ifdef ACIS
	filter = "Acis Files (*.sat;*.asat)|*.sat;*.asat|AcisHOOPS Stream Files (*.asf)|*.asf|";
	def_ext = ".sat";
#endif // ACIS
#ifdef GRANITE
	filter = "ProE Files (*.prt;*.prt.*)|*.prt;*.prt.*|ProE Assemblies (*.asm;*.asm.*)|*.asm;*.asm.*|GraniteHOOPS Stream Files (*.gsf)|*.gsf|Parasolid Files (*.x_t;*.xmt_txt;x_b)|*.x_t;*.xmt_txt;*.xmb|IGES Files (*.igs)|*.igs|Acis Files (*.sat)|*.sat|STEP Files (*.stp;*.step)|*.stp;*.step|VDA Files (*.vda)|*.vda|Granite Neutral Files (*.g)|*.g|";
	def_ext = ".prt";
#endif // GRANITE

	CSolidHoopsApp::CreateAllFileTypesString(&filter, HDB::GetHIOManager()->GetInputHandlerTypes());
	filter += _T("|");

	// this adds file types that have HIO handlers and appear in ProcessFilters()
	CSolidHoopsApp::ProcessFilters(&filter, HDB::GetHIOManager()->GetInputHandlerTypes());

	filter += _T("|");

	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	CFileDialog my_dlg(TRUE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter , NULL);
	my_dlg.m_ofn.lpstrInitialDir = cur_dir;
	if (my_dlg.DoModal() == IDOK)
	{
		HSolidModel * hmodel = (HSolidModel*) m_pHView->GetModel();
		assert(hmodel);
		LoadFile( my_dlg.GetPathName(), hmodel->GetStreamFileTK());
	}
}

void CSolidHoopsView::LoadFile( LPCTSTR csFilePathName, HStreamFileToolkit* tk) 
{
	assert(tk);

	// this could take time - don't test user's patience
	CWaitCursor display_hourglass_cursor_till_we_finish_reading;

	// understand the file extension - if unknown better return
	TCHAR file_ext[MVO_BUFFER_SIZE]; 
	HUtility::FindFileNameExtension((csFilePathName), file_ext);
	if(_tcslen(file_ext) == 0) 
	{
		AfxMessageBox(_T("Error: No file extension. Could not determine input file format.\n"));
		return;
	}

	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	HSolidModel * hmodel = (HSolidModel*) m_pHView->GetModel();
	assert(hmodel);
	_tcscpy(pDoc->filename, csFilePathName);

	
//no need to flush anything	
	if (_tcsieq(file_ext, _T("bhv"))) 
	{
		HBhvBehaviorManager::ReadFromFile(hmodel, (csFilePathName ));
		return;
	}
	// we are flushing all the geometry - to avoid any problems, unselect any selected stuff.
	m_pHView->GetSelection()->DeSelectAll();

	// remove the dialog-box in the dialog bars, they will automatically update themselves later
//	H_SAFE_DELETE(m_pDlgSegmentBrowser);
#ifndef HOOPS_ONLY
//	H_SAFE_DELETE(m_pDlgTopologyBrowser);
#endif // HOOPS_ONLY
//	H_SAFE_DELETE(m_pDlgKeyframeEditor);

	m_pHView->GetModel()->SetBhvBehaviorManager(0);
	if(CAppSettings::bFlushOnLoad)
	{
		// flush all the the solid modeler entities and HOOPS Geometry
		m_pHView->Flush(true);
		HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
			HC_Flush_Contents (".", "geometry");
		HC_Close_Segment();
	}

	if (_tcsieq(file_ext, _T("hsf")) || _tcsieq(file_ext, _T(KERN_STREAM_FILE))) 
	{
	
		HBhvUtility::SetupAnimationReadFromHSF(pDoc->GetHoopsModel()->GetStreamFileTK(), pDoc->GetHoopsModel());
		pDoc->GetHoopsModel()->GetStreamFileTK()->SetOpcodeHandler (TKE_XML, pDoc->GetHoopsModel()->GetDispatchXML()->MakeCopy());

#ifndef HOOPS_ONLY
		pDoc->GetHoopsModel()->GetStreamFileTK()->SetOpcodeHandler (TKE_Comment, new TK_PSComment(hmodel));

		if (_tcsieq(file_ext, _T(KERN_STREAM_FILE)))
		{
			pDoc->m_bIsPsf = true;
			hmodel->m_bSolidModel = true;
			hmodel->m_bSolidData = true;
		}
		else
#endif 
			hmodel->m_bSolidModel = false;


		if(!CAppSettings::HsfStreaming && CAppSettings::MultiThreading==MultiThreadingFull)
		{
			StartThreadedLoading();
		}
		else
		{
		// (ideally these reinitialization stuff should be done in respective
		// classes)

		// reinitialize the doc variables 
		pDoc->m_bStreamInProgress = true;	
		pDoc->reading_mode = TK_Normal;

		_tcscpy(pDoc->filename, csFilePathName);

		// reinitialize the model variable  - setup the stream toolkit nicely
		tk->Restart();
		hmodel->SetFileLoadComplete(false);
		m_StreamedSoFar = 0;
		m_UpdatesSoFar = 0;


		if (pDoc->GetReadSimpleHsfFlag() == true )
			m_pHView->RenderFlat();

		// ask the binary file toolkit to open the file
		tk->OpenFile(pDoc->filename);
		// if we are reading in a complete stream file (hsf) then enable the framerate functionality so that the user can continually have quick interactaction with 
		// the scene as it is being streaming in and refined.  If we didn't do this here, then the user would have
		// slow interaction as the file finishes reading in, and they'd instead have to manually launch the framerate
		// dialog afterwards to get a constant framerate.
		if (pDoc->GetReadSimpleHsfFlag() == false 
			&& CAppSettings::UseFramerate 
			&& CAppSettings::CurrentFramerateMode==FramerateTarget)
			EnableFrameRate();

		hmodel->SetFileLoadComplete(false);
		hmodel->SetFirstFitComplete(false);
		// spawn a new thread to read from the file; this enables the main application thread to continue processing user
		// events, rather than wait for the whole file to be read in first
		m_bHSFVersionMismatch = false;

		m_cease = false;
		AfxBeginThread(HStreamFileReadingThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0);
		}
	}
	// read the file (HMF or XMT) into the Model Object
	else 
	{
		StartThreadedLoading();
	}
}

/*!
  Receive the MVO event HSignalSelected event here and call the appropriate handler
*/
bool CSolidHoopsView::signal_selected(int signal, void * signal_data, void *user_data)
{
	return ((CSolidHoopsView*)user_data)->OnSignalSelected();
}
/*!
  Receive the MVO event HSignalDeSelectedAll event here and call the appropriate handler
*/
bool CSolidHoopsView::signal_deselected_all(int signal, void * signal_data, void *user_data)
{
	return ((CSolidHoopsView*)user_data)->OnSignalDeSelectedAll();
}


void CSolidHoopsView::HandleSpecialSelection()
{
	if (m_bInSpecialSelection)
		return;

	unsigned int i;
	m_bInSpecialSelection = true;
 	char type[MVO_BUFFER_SIZE];
	HSolidModel *	pModel = (HSolidModel *)m_pHView->GetModel();
	if (pModel->m_pConnector && pModel->m_pPMIConnector)
	{
		HSelectionSet *selection_set = m_pHView->GetSelection();
		HC_KEY *keylist = new HC_KEY[selection_set->GetSize()];
		unsigned int size = selection_set->GetSize();
		for (i=0; i < size; i++)
			keylist[i] = selection_set->GetAt(i);

		for (i=0; i < size; i++)
		{
			HC_KEY key = keylist[i];
			HC_Show_Key_Type(key, type);
			if (strcmp(type,"segment") == 0)
			{
				HC_Open_Segment_By_Key(key);
				if (HC_Show_Existence("user options = hobject"))
				{
					HC_Show_One_User_Option("hobject", type);
					if (strcmp(type, "pmi_markup") == 0)
					{
						void *kentity = pModel->m_pConnector->GetKernelEntity(key);
						vlist_t *clist = new_vlist(malloc,free);
						if (kentity)
						{
							pModel->m_pPMIConnector->GetHoopsEntities(kentity, clist);
							START_LIST_ITERATION(HC_KEY,clist);
								selection_set->Select((HC_KEY)temp,0,0);
							END_LIST_ITERATION(clist);
						}
						delete_vlist(clist);
 					}
				}
				HC_Close_Segment();
			}
		}
		delete [] keylist;
	}
	
	m_bInSpecialSelection = false;
}


/*!
  HSignalSelected MVO event handler. Update any dialog bars we have
  \return bool
*/
bool CSolidHoopsView::OnSignalSelected()
{

	HandleSpecialSelection();

	if( m_pDlgClashBrowser )
		m_pDlgClashBrowser->CheckDisplaced();

	if( m_pDlgSegmentBrowser )
		m_pDlgSegmentBrowser->ShowSelectedItems();
	if( m_pDlgModelBrowser )
		m_pDlgModelBrowser->ShowSelectedItems();
#ifndef HOOPS_ONLY
	if( m_pDlgTopologyBrowser )
		m_pDlgTopologyBrowser->ShowSelectedItems();
#endif // HOOPS_ONLY
 

	return true;
}

/*!
  HSignalDeSelectedAll MVO event handler. Update any dialog bars we have
  \return bool
*/
bool CSolidHoopsView::OnSignalDeSelectedAll()
{
	if( m_pDlgClashBrowser )
		m_pDlgClashBrowser->CheckDisplaced();
	if( m_pDlgSegmentBrowser )
		m_pDlgSegmentBrowser->ShowSelectedItems();
	if( m_pDlgModelBrowser )
		m_pDlgModelBrowser->ShowSelectedItems();
#ifndef HOOPS_ONLY
	if( m_pDlgTopologyBrowser )
		m_pDlgTopologyBrowser->ShowSelectedItems();
#endif // HOOPS_ONLY
 

	return true;
}


LRESULT CSolidHoopsView::OnNewStreamFileBuffer(WPARAM wParam, LPARAM lParam)
{
 
    TK_Status		status;
    int				amount = lParam;
	char *			block = (char *)wParam;
	HSolidModel *	pModel = (HSolidModel *)m_pHView->GetModel();

	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	CSolidHoopsApp * app = (CSolidHoopsApp *) AfxGetApp();

	if (!app->ShuttingDown() && pDoc->reading_mode != TK_Error) {

		HStreamFileToolkit * tk = pModel->GetStreamFileTK();
		bool do_update = true;

		// if theApp->m_read_simple_hsf is TRUE, we want to only load the beginning of the file; therefore, 
		// we only parse to the pause and then read the dictionary
		m_pHView->SetGeometryChanged();
		HC_Open_Segment_By_Key(pModel->GetModelKey());
			HC_KEY	local_segment = -1;

			if (tk->GetExternalReference() &&
				!wcscmp ((wchar_t const*)tk->GetCurrentFile(), (wchar_t const*)tk->GetExternalReference())) {
				local_segment = tk->GetExternalReferenceContext();
				HC_Open_Segment_By_Key (local_segment);
			}

			if (tk->GetReadFlags() & TK_Ignore_Version) {
			    try {
					status = tk->ParseBuffer (block, amount, pDoc->reading_mode);
			    }
			    catch(...) {
					status = tk->Error( "exception caught from CSolidHoopsView::OnNewStreamFileBuffer (after attempting to ignore file version)" );
			    }
			}
			else {
				int             version;

				if ((version = tk->ParseVersion(block)) != 0) {
					if (version > TK_File_Format_Version) {
						m_bHSFVersionMismatch = true;
						tk->SetReadFlags (tk->GetReadFlags() | TK_Ignore_Version);
					}
				}
				try {
				    status = tk->ParseBuffer (block, amount, pDoc->reading_mode);
				}
				catch(...) {
				    status = tk->Error( "exception caught from CSolidHoopsView::OnNewStreamFileBuffer (after attempting to ignore file version) (2)" );
				}
			}

			//MSG msg;
			//while ( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE )); 

			// set the event to signaled state. This will allow the stream reading thread
			// to go ahead with the buffer reading - Rajesh B
			//SetEvent(m_hStreamBufferAccessEvent);


			m_StreamedSoFar+=amount;
			unsigned HLONG totalsize;
			tk->GetFileSize(totalsize);
			HBaseView::StreamProgressCallback(m_StreamedSoFar, totalsize, m_pHView);

			if (local_segment != -1)
				HC_Close_Segment();

			if (status == TK_Error) {
				if (m_bHSFVersionMismatch)
					AfxMessageBox(_T("This file was created with a newer version of the HOOPS/Stream Toolkit.\nTo view it this application's version of the toolkit will need to be updated."));
				pModel->SetFileLoadComplete(true);
				pDoc->reading_mode = TK_Error;
				m_cease = true;
				m_pHView->FlushProgressBar();

			}

			if (!app->ShuttingDown() && status == TK_Complete) {
				if (tk->GetExternalReference() &&
					!wcscmp ((wchar_t const*)tk->GetCurrentFile(), (wchar_t const*)tk->GetExternalReference()))
					tk->NextExternalReference();

				if (!tk->GetExternalReference()) {
					HC_POINTER_SIZED_INT	value = 0L;

					if (pDoc->reading_mode == TK_Normal)
						HC_Control_Update (".", "redraw everything");
					else if (pDoc->reading_mode == TK_Single) {
						EnterCriticalSection(&sweeten_lock);
						do_update = (sweeten_list.IsEmpty() != 0);
						LeaveCriticalSection(&sweeten_lock);

						if (do_update)
							HC_Control_Update (".", "redraw everything");
					}
 					pModel->SetFileLoadComplete(true, m_pHView);
					m_pHView->GetConstantFrameRateObject()->SetWatchActivity(true);
					ViewReady();

					pModel->CleanIncludes();
					// check the user value manually since we're streaming in the file, and set the appropriate model type
					// we need to open up a no name subsegment since the model was written out from MVO with this segment at 
					// the top

					pModel->UpdateModelGeometryType();
 					if (value == 3L) {
						m_pHView->RenderWireframe();
						SetFastPrint(false);
					}

				}

				pDoc->reading_mode = TK_Error;	// ignore any more message from this thread
				m_cease = true;					// tell the thread to die
			}

		HC_Close_Segment();

		if (!app->ShuttingDown() && do_update) {

#define NUMBER_OF_UPDATES_WANTED 10
			float base=0.75f, step=base;
			unsigned int i;
			//exponential decay
			if(m_UpdatesSoFar<NUMBER_OF_UPDATES_WANTED)
				for(i=1; i<NUMBER_OF_UPDATES_WANTED-m_UpdatesSoFar; ++i)
					step*=base;

			bool update_it = (step*totalsize < m_StreamedSoFar) && (m_UpdatesSoFar<NUMBER_OF_UPDATES_WANTED);	

			if (update_it) {

				m_UpdatesSoFar++;

				if (m_pHView->GetViewActive())
					m_pHView->ForceUpdate();
			}

		}

	}

	// set the event to signaled state. This will allow the stream reading thread
	// to go ahead with the buffer reading - Rajesh B
	SetEvent(m_hStreamBufferAccessEvent);

	return 0;
}

 

LRESULT CSolidHoopsView::OnReadingThreadCompleted(WPARAM wParam, LPARAM lParam)
{
	HSolidModel * pModel = (HSolidModel *)m_pHView->GetModel();
	HStreamFileToolkit * tk = pModel->GetStreamFileTK();
	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	m_pHView->SetGeometryChanged();
	if (!pModel->GetFileLoadComplete())
 			ViewReady();

#ifndef HOOPS_ONLY
	if (pModel->m_mi)
	{
		if (pModel->m_mi->m_bIsValid)
		{
			pModel->m_bSolidData = true;
			pModel->SetBRepGeometry(true);
			if (pModel->m_mi->m_bTesselatedFaces)
				((HSolidView *)m_pHView)->SetOptimizations(false,true);
 			pModel->m_bPlainSolidModel = !pModel->m_mi->m_bPSF;
			if (pModel->m_bPlainSolidModel)
				((HSolidView *)m_pHView)->InitSelection(new HSPlainSelectionSet(m_pHView));
			else
			{
				delete pModel->m_mi;
				pModel->m_mi = 0;
#ifdef PARASOLID
				((HSolidView *)m_pHView)->InitSelection(new HSParasolidSelectionSet(m_pHView));
#endif // PARASOLID
#ifdef ACIS
				((HSolidView *)m_pHView)->InitSelection(new HSAcisSelectionSet(m_pHView));
#endif // ACIS
#ifdef GRANITE
				((HSolidView *)m_pHView)->InitSelection(new HSGraniteSelectionSet(m_pHView));
#endif // GRANITE

			}
		}
		else
		{
			delete pModel->m_mi;
			pModel->m_mi = 0;
			pModel->m_bSolidData = false;
		}
		CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
		pDoc->m_bStreamInProgress = false;
	}
	
#endif // HOOPS_ONLY

	if (tk->GetExternalReference() &&
		!wcscmp ((wchar_t const*)tk->GetCurrentFile(), (wchar_t const*)tk->GetExternalReference()))
		tk->NextExternalReference();

	if (pDoc->GetReadSimpleHsfFlag())
	{
		if (!pDoc->dictionary_loaded)
		{
			pDoc->reading_mode = TK_Pause; 
			m_cease = false;

			pDoc->dictionary_loaded = true;

			// locate dictionary and pass location to new reading thread
			tk->LocateDictionary();
			AfxBeginThread(HStreamFileReadingThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0);
		}
		else if (tk->GetExternalReference()) {
			tk->CloseFile();

	        tk->OpenFile (tk->GetExternalReference());
			pDoc->reading_mode = TK_Pause; 
			m_cease = false;
			pDoc->dictionary_loaded = false;

			AfxBeginThread(HStreamFileReadingThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0);
		}
	    else 
		{
			pDoc->reading_mode = TK_Single; 
			m_cease = false;

			EnterCriticalSection(&sweeten_lock);

			// if list of items to sweeten, pull next off list, locate and launch reading thread again
			while (!sweeten_list.IsEmpty())
			{	
  				if (tk->LocateEntity(sweeten_list.RemoveHead(), 0) == TK_Normal)
				{
					AfxBeginThread(HStreamFileReadingThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0);
					break;
				}
			}

			LeaveCriticalSection(&sweeten_lock);
		}

	} 
	else
	{
		tk->CloseFile();

		if (tk->GetExternalReference() &&
	        tk->OpenFile (tk->GetExternalReference()) == TK_Normal) {
			pDoc->reading_mode = TK_Normal;
			m_cease = false;

			AfxBeginThread(HStreamFileReadingThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0);
		}
		else
		if( !m_has_initial_view )
		{    
			m_pHView->FitWorld();		// fit the camera to the scene extents
			m_pHView->CameraPositionChanged(true);
		}

	}

    m_pHView->SetZoomLimit();
	pModel->UpdateModelHandedness();
	
	m_pHView->FlushProgressBar();

	//HUtilityAnnotation::WindowResizeCallback(0, 0, m_pHView);

	// ask to rerender - because this file may or may not have brep
	m_pHView->SetRenderMode(m_pHView->GetRenderMode(), true);

	// if we have a browser dialog, update it
	if( m_pDlgSegmentBrowser )
		m_pDlgSegmentBrowser->ValidateSegmentTree();



	m_pHView->ForceUpdate();

	if (m_pDlgSegmentBrowser)
	    m_pDlgSegmentBrowser->RefreshBrowser();
	
	//this system function releases all unused memory associated with the process
	//essentially performing a garbage collection
	HANDLE h = GetCurrentProcess();
	SetProcessWorkingSetSize(h, (SIZE_T)-1, (SIZE_T)-1);
	return 0;
}



void CSolidHoopsView::OnSweeten() 
{
	int i;
	char string[MVO_BUFFER_SIZE];
	bool do_update = true;

	HSolidModel *	pModel = (HSolidModel *)m_pHView->GetModel();
	HStreamFileToolkit * tk = pModel->GetStreamFileTK();

	// launch thread for first element

   	HSSelectionSet* selection = (HSSelectionSet*) m_pHView->GetSelection();

	int list_size = selection->GetSize();

	// protect access to sweeten list using a critical section

	EnterCriticalSection(&sweeten_lock);

    for (i= 0; i < list_size; i++)
	{
		HC_KEY current_key = selection->GetAt(i);

		char type[MVO_BUFFER_SIZE];
		HC_Show_Key_Type(current_key,type);
		if (strcmp(type,"segment")==0)
		{
		HC_Open_Segment_By_Key(current_key);
		  HC_Set_Rendering_Options("lighting interpolation = (faces = on, edges = off)");
		  HC_Begin_Contents_Search("./...", "shells");
		  while (HC_Find_Contents(string, &current_key))
			sweeten_list.AddTail(current_key);
		  HC_End_Contents_Search();
		HC_Close_Segment();
		}
		else
			sweeten_list.AddTail(current_key);

	}

	while (!sweeten_list.IsEmpty())
	{
  		if (tk->LocateEntity(sweeten_list.RemoveHead(), 0) == TK_Normal)
		{
			AfxBeginThread(HStreamFileReadingThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0);
			do_update = false;
			break;
		}
	}

	LeaveCriticalSection(&sweeten_lock);

	// deselect all the items
	selection->DeSelectAll();
}

void CSolidHoopsView::OnUpdateSweeten(CCmdUI* pCmdUI) 
{
	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	
	if( !pDoc->GetReadSimpleHsfFlag() )
		pCmdUI->Enable(FALSE);
}


void CSolidHoopsView::SetWalkOperator()
{
	HBaseOperator *op = m_pHView->GetOperator();
	HOpCameraWalk *walkop = 0;
	if (op && strcmp(op->GetName(),"HOpCameraWalk") == 0)
		walkop = (HOpCameraWalk *)op; 
	else
	{
		walkop = new HOpCameraWalk(m_pHView);
		LocalSetOperator(walkop);
	}

	walkop = (HOpCameraWalk *)m_pHView->GetOperator();
	walkop->SetKeyboardWalk(CAppSettings::bWalkUseKeyboard);
	walkop->SetCollision(CAppSettings::bWalkCollision);
	walkop->SetSnapToFloor(CAppSettings::bWalkSnapToFloor);
	if (CAppSettings::bWalkAutomaticHeight)
	{
		float extent = HOpCameraWalk::CalculateExtents(m_pHView);
		walkop->SetAvatarHeight(extent/60.0f);
		CAppSettings::WalkAvatarHeight = (extent/60.0f) * 100;
	}
	else
		walkop->SetAvatarHeight(CAppSettings::WalkAvatarHeight / 10000.0f);

	walkop->SetStepHeightUp(CAppSettings::WalkStepHeightUp / 100.0f *  walkop->GetAvatarHeight());
	walkop->SetStepHeightDown(CAppSettings::WalkStepHeightDown / 100.0f *  walkop->GetAvatarHeight());

	walkop->OnWalk(0,0);
	if (m_WalkSpeed!=0.0f)
		walkop->SetSpeed(m_WalkSpeed);

	if(CAppSettings::NavigationPanel)
		walkop->ShowNavigationWindow(theApp.m_AppDirectory);
}

void CSolidHoopsView::OnWalk() 
{
	SetWalkOperator();
}

void CSolidHoopsView::OnUpdateWalk(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(),"HOpCameraWalk"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnLodLevelOriginal() 
{
	// render gouraud shaded mode for original LOD level
	m_pHView->RenderGouraud();

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Rendering_Options("lighting interpolation = on, lod =off");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateLodLevelOriginal(CCmdUI* pCmdUI) 
{
	HC_KEY keys[3];

	keys[0] = m_pHView->GetModelKey();
	keys[1] = m_pHView->GetViewKey();
	keys[2] = m_pHView->GetSceneKey();

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		char lod[MVO_BUFFER_SIZE];
		HC_PShow_One_Net_Rendering_Opti(3, keys, "lod", lod);

		if (strstr(lod, "off"))
			pCmdUI->SetCheck(1);
		else
			pCmdUI->SetCheck(0);
	}

	// disable if framerate operator is enabled
	if( m_pHView->IsFrameRateEnabled() == true )
		pCmdUI->Enable(FALSE);
}


void CSolidHoopsView::OnLodLevelLevel1() 
{
	// render in flat shaded mode for lods
	m_pHView->RenderFlat();

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Rendering_Options("no lighting interpolation, lod = on, lodo = (clamp = 1, fallback = none)");
	HC_Close_Segment();

	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateLodLevelLevel1(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		char	lod[MVO_BUFFER_SIZE], options[MVO_BUFFER_SIZE];
		HC_KEY	keys[3];

		keys[0] = m_pHView->GetModelKey();
		keys[1] = m_pHView->GetViewKey();
		keys[2] = m_pHView->GetSceneKey();

		HC_PShow_One_Net_Rendering_Opti(3, keys, "lod", lod);
		HC_PShow_One_Net_Rendering_Opti(3, keys, "lodo", options);

		char *clamp = strstr(options, "clamp");
		if( clamp != NULL && 
			strstr(options, "clamp=1") && 
			strstr(lod, "on")
		)
				pCmdUI->SetCheck(1);
			else
				pCmdUI->SetCheck(0);
	}

	// disable if framerate operator is enabled
	if( m_pHView->IsFrameRateEnabled() == true )
		pCmdUI->Enable(FALSE);
}

void CSolidHoopsView::OnLodLevelLevel2() 
{
	// render in flat shaded mode for lods
	m_pHView->RenderFlat();

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Rendering_Options("no lighting interpolation, lod = on, lodo = (clamp = 2, fallback = none)");
	HC_Close_Segment();

	m_pHView->Update();	
}


void CSolidHoopsView::OnUpdateLodLevelLevel2(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete()) {
		char	lod[MVO_BUFFER_SIZE], options[MVO_BUFFER_SIZE];
		HC_KEY	keys[3];

		keys[0] = m_pHView->GetModelKey();
		keys[1] = m_pHView->GetViewKey();
		keys[2] = m_pHView->GetSceneKey();

		HC_PShow_One_Net_Rendering_Opti(3, keys, "lod", lod);
		HC_PShow_One_Net_Rendering_Opti(3, keys, "lodo", options);

		char *clamp = strstr(options, "clamp");
		if( clamp != NULL && 
			strstr(options, "clamp=2") && 
			strstr(lod, "on")
		)
				pCmdUI->SetCheck(1);
			else
				pCmdUI->SetCheck(0);
	}

	// disable if framerate operator is enabled
	if( m_pHView->IsFrameRateEnabled() == true )
		pCmdUI->Enable(FALSE);
}


void CSolidHoopsView::EnableFrameRate(bool onoff)
{
	int steps = (CAppSettings::DynamicAdjustment ? CAppSettings::DetailSteps : 0);
	if (onoff)
		m_pHView->SetFramerateMode(FramerateTarget, CAppSettings::FramerateTime, CAppSettings::MaxThreshold, UINT2bool(CAppSettings::UseLods), steps);
	else
		m_pHView->SetFramerateMode(FramerateOff);
}

void CSolidHoopsView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (!bActivate) {
		HSOpCameraOrbit *op = (HSOpCameraOrbit *)m_pHView->GetOperator();
		if (strcmp(op->GetName(),"HOpCameraOrbit")==0)
			op->m_Angle1 = op->m_Angle2 = op->m_Angle3 = 0;

//		if( GetFirstUpdate() == true)
//			m_pHView->Update();
	}
	else {
		HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
		pBehaviorManager->SetActiveView(m_pHView);
		CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();
		frame->GetBhvToolbar()->m_wndBhvSlider.SetPos((int)pBehaviorManager->GetCurrentTickByPercentage());
#ifdef ACIS
		((HSolidModel *)m_pHView->GetModel())->SetHistoryStream();
#endif // ACIS

#ifdef INTEROP
		((HSolidModel *)m_pHView->GetModel())->GetInterOpFileIOHandler()->ShowInterOpPartBrowser();
#endif // INTEROP
	}
 		
	// pass this message to the mainframe window for updating the dialog bars
	CSolidHoopsFrame* pMainFrm = (CSolidHoopsFrame*) AfxGetMainWnd();
	if( pMainFrm )
		pMainFrm->OnActivateView(bActivate, (CSolidHoopsView*) pActivateView, (CSolidHoopsView*)pDeactiveView );

	CHoopsView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CSolidHoopsView::OnViewcube() 
{
	if (!streq(m_pHView->GetOperator()->GetName(), "HOpNavCube"))
		LocalSetOperator(new HOpNavCube(m_pHView));
}


void CSolidHoopsView::OnUpdateViewcube(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpNavCube"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnManipulateSmoothtransition() 
{
	if (m_pHView->GetSmoothTransition())
		m_pHView->SetSmoothTransition(false);
	else
		m_pHView->SetSmoothTransition(true);
}

void CSolidHoopsView::OnUpdateManipulateSmoothtransition(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetSmoothTransition())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnSaveMarkup()
{
	HMarkupManager *markup = m_pHView->GetMarkupManager();
	PresetViewNameDlg dlg;
	if(dlg.DoModal() == IDOK){
		H_WCS wcs;
		CString cs = dlg.getViewName();
		LPTSTR szData = cs.GetBuffer();
		wcs.encodedText(szData);
		cs.ReleaseBuffer();
		if(markup->GetCurrentLayerKey() != -1){
			markup->RenameLayer(markup->GetCurrentLayerKey(), (char*)H_UTF8(wcs).encodedText());
		}
		else{
			markup->DeleteLayer((char*)H_UTF8(wcs).encodedText());
			markup->OpenLayer((char*)H_UTF8(wcs).encodedText());
		}
	}
}

void CSolidHoopsView::OnEditMarkup()
{
	HMarkupManager *markup = m_pHView->GetMarkupManager();
	PresetViewEditDlg dlg(markup);
	if(dlg.DoModal() == IDOK){
		H_WCS wcs;
		CString cs = dlg.getViewName();
		LPTSTR szData = cs.GetBuffer();
		wcs.encodedText(szData);
		cs.ReleaseBuffer();
		if(wcs.length() > 0)
			markup->OpenLayer((char*)H_UTF8(wcs).encodedText());
	}
	m_pHView->Update();
}

void CSolidHoopsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	unsigned short ascii_key=0;
	BYTE keys[256];

	GetKeyboardState( keys );
	ToAscii(nChar, MapVirtualKey(nChar, 0), keys, &ascii_key, 0);

	// 0 key
	if (nChar == 48){
		//initialize stereo sep keys
		if(CAppSettings::StereoMode)
		{
			CAppSettings::StereoSeparation = 0.0f;
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
				HC_Set_Rendering_Options("stereo, stereo separation = 0.0");
			HC_Close_Segment();
			HC_Update_Display();
		}
	}

	// + key (= key)
	if (nChar == 187){
		//apply stereo mode
		char rendering_opts[128];
		char curr_sep[128];
		float separation = 0.0f;
		if(CAppSettings::StereoMode)
		{
			
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
				HC_Show_One_Rendering_Option("stereo separation", curr_sep);
				sscanf(curr_sep, "%f", &separation);
				sprintf(rendering_opts, "stereo, stereo separation = %f", separation + 0.01);
				HC_Set_Rendering_Options(rendering_opts);
			HC_Close_Segment();
			m_pHView->Update();
		}
	}

	// - key
	if (nChar == 189){
		//apply stereo mode
		char rendering_opts[128];
		char curr_sep[128];
		float separation = 0.0f;
		if(CAppSettings::StereoMode)
		{
			
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
				HC_Show_One_Rendering_Option("stereo separation", curr_sep);
				sscanf(curr_sep, "%f", &separation);
				sprintf(rendering_opts, "stereo, stereo separation = %f", separation - 0.01);
				HC_Set_Rendering_Options(rendering_opts);
			HC_Close_Segment();
			m_pHView->Update();
		}
	}

	// ] key
	if (nChar == 221){
		//apply stereo mode
		char rendering_opts[128];
		char curr_dist[128];
		float distance = 0.0f;
		if(CAppSettings::StereoMode)
		{
			
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
				HC_Show_One_Rendering_Option("stereo distance", curr_dist);
				sscanf(curr_dist, "%f", &distance);
				sprintf(rendering_opts, "stereo, stereo distance = %f", distance + 0.4);
				HC_Set_Rendering_Options(rendering_opts);
			HC_Close_Segment();
			m_pHView->Update();
		}
	}

	// [ key
	if (nChar == 219){
		//apply stereo mode
		char rendering_opts[128];
		char curr_dist[128];
		float distance = 0.0f;
		if(CAppSettings::StereoMode)
		{
			
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
				HC_Show_One_Rendering_Option("stereo distance", curr_dist);
				sscanf(curr_dist, "%f", &distance);
				sprintf(rendering_opts, "stereo, stereo distance = %f", distance - 0.4);
				HC_Set_Rendering_Options(rendering_opts);
			HC_Close_Segment();
			m_pHView->Update();
		}
	}

	// i
	if (nChar == 73){
		float w = 0.0f, h = 0.0f;
		HC_Open_Segment_By_Key(m_pHView->GetViewKey());
			HC_Show_Net_Camera_Field(&w, &h);
		HC_Close_Segment();

		char rendering_opts[128];
	

		char type[MVO_BUFFER_SIZE];
		int count, off1, off2, off3, hits = 0;
		HC_KEY key = 0;
		HPoint	awindow, world, object, avg, camera;
		avg.Set(0.0f, 0.0f, 0.0f);

		float pick_coords[] = {0.0f,0.5f,  -0.25f,0.25f,  0.0f,0.25f, 0.25f,0.25f,
			-0.5,0.0f,  -0.25f,0.0f, 0.0f,0.0f, 0.25f,0.0f,  0.5f,0.0f,
			-0.25f,-0.25f,  0.0f,-0.25f,  0.25f,-0.25f,  0.0f,-0.5f};

		for(int i = 0; i < 26; i+=2){
			HC_Open_Segment_By_Key (GetViewKey());
				HC_QSet_Selectability ("./scene/overwrite", "geometry=on");
				count = HC_Compute_Selection (".", "./scene/overwrite", "v", pick_coords[i], pick_coords[i+1]);
				HC_QUnSet_Selectability ("./scene/overwrite");
			HC_Close_Segment();
			HC_Open_Segment_By_Key (GetSceneKey());
				if (count > 0)
				{
					HC_Show_Selection_Element(&key, &off1, &off2, &off3);
					HC_Show_Selection_Original_Key (&key);
					HC_Show_Selection_Position(&awindow.x, &awindow.y, &awindow.z, &world.x, &world.y, &world.z);
					avg = avg + world;
					HC_Show_Key_Type(key, type);
					hits++;
				}
			HC_Close_Segment();
		}
		avg.x = avg.x / (float)hits;
		avg.y = avg.y / (float)hits;
		avg.z = avg.z / (float)hits;

		HC_Open_Segment_By_Key (GetSceneKey());
			HC_Show_Camera_Position (&camera.x, &camera.y, &camera.z);
		HC_Close_Segment();
		awindow = avg - camera;
		float distance = sqrt((awindow.x * awindow.x) + (awindow.y * awindow.y) + (awindow.z * awindow.z));
	

		if(CAppSettings::StereoMode)
		{
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
				sprintf(rendering_opts, "stereo, stereo distance = %f", distance * 1.0);
				HC_Set_Rendering_Options(rendering_opts);
			HC_Close_Segment();
			m_pHView->Update();
		}

	}

	if (nChar == 192){
		// ` key
		// toggle fullscreen mode
		CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();
		frame->OnViewFullScreen();
	}
	
	if( nChar == 46 && !CAppSettings::DisableEditing) //del key
		OnSelectionDeleteselection();
	else
		CHoopsView::OnKeyDown(nChar, nRepCnt, nFlags);
}


//======================================================================
//	Author :Rajesh B			Created : 3/15/2001 3:53:32 PM
//======================================================================
//	Function :CSolidHoopsView::OnEditColor
//	Description :	Edits the color of entities which are there
//					in the selection list
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsView::OnEditColor() 
{
	// get the selection list
   	HSSelectionSet* selection = (HSSelectionSet*) m_pHView->GetSelection();
	int list_size = selection->GetSize();
	if( list_size < 1 )
	{
		AfxMessageBox(_T("No entites selected"));
		return;
	}

	// get the user's color choice
	int r=0,g=0,b=0;
	CColorDialog cd;
	cd.m_cc.Flags |=  CC_RGBINIT;
	cd.m_cc.rgbResult = RGB(r, g, b);
	if( cd.DoModal() != IDOK)
		return;
	COLORREF user_col = cd.GetColor();

	r = GetRValue(user_col);
	g = GetGValue(user_col);
	b = GetBValue(user_col);


	// collect and selected keys in an and array and delselect
	// 'cause, if the selected key is a temporary segment for highlighting
	// and there is no point in changing the color of it
	HC_KEY* sel_set = new HC_KEY[list_size];
	for( int cur_sel = 0; cur_sel < list_size; cur_sel++ )
	{
		sel_set[cur_sel] = selection->GetAt(cur_sel);
	}
   	selection->DeSelectAll();
#ifdef ACIS
	KERN_CLASS_TYPEDEF e_sel_class = ((HSSelectionSet *)GetSolidView()->GetSelection())->GetSelectLevel();
#endif
    for (int i= 0; i < list_size; i++)
	{
		HC_KEY current_key = sel_set[i];
//		SetColor( current_key, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f );
		Color( current_key, "", 0, 0, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, true );

#ifdef ACIS
		ENTITY* entity = HA_Compute_Entity_Pointer(current_key, e_sel_class);
		if (entity)
		{
			rgb_color acis_user_col((double)r/255.0, (double)g/255.0, (double)b/255.0);
			outcome o = api_rh_set_entity_rgb(entity, acis_user_col );
			logical inherited = FALSE;
			logical found = FALSE;
			o = api_rh_get_entity_rgb(entity, acis_user_col, inherited, found);
			CHECK_OUTCOME(o);
		}
#endif //ACIS
	}

	if( sel_set )
	{
		delete[] sel_set;
		sel_set = NULL;
	}

	HC_Update_Display();
}


bool CSolidHoopsView::SetColor( HC_KEY key, float r, float g, float b)
{
	HC_KEY seg_key;
    char keytype[MVO_BUFFER_SIZE];
    HC_Show_Key_Type(key, keytype);
	 
    if (streq(keytype, "segment")) 
	{
		seg_key = key;
	}
	else
	{
        seg_key = HC_KShow_Owner_By_Key(key);
    }

	HC_Open_Segment_By_Key(seg_key);
		HC_Set_Color_By_Value("faces,edges,lines", "RGB", r, g, b );
	HC_Close_Segment();

	// compute the entity pointer and set it attribute

	return true;
}

void CSolidHoopsView::Color(HC_KEY key, char* seg_path, HC_KEY include_key, HC_KEY includer_key, 
							float r, float g, float b, bool recurse, bool emit_message)
{  
    char keytype[MVO_BUFFER_SIZE];
	HC_KEY seg_key;
    bool include = false;
	int i, path_len;

    HC_Show_Key_Type(key, keytype);
    if (strstr(keytype, "segment"))
	{
		seg_key = key;

		path_len = (int)strlen(seg_path);
		for (i = 0; i < path_len; i++)
		{
			if (seg_path[i] == '<')
				include = true;
		}


		if ((include) && (include_key) && (includer_key))
		{
			HC_Delete_By_Key(include_key);					// remove the original include link
			
			HC_Open_Segment_By_Key(includer_key);
			 seg_key = HC_KCopy_Segment(seg_path, "tmp");	// copy the included segment
			HC_Close_Segment();
		}
		
		HC_Open_Segment_By_Key(seg_key);
			HC_Set_Color_By_Value("faces,edges,lines", "RGB", r, g, b );

			if( recurse )
			{
				HC_KEY child;
				char child_type[MVO_BUFFER_SIZE];
				HC_Begin_Contents_Search (".", "segment, include");
				while (HC_Find_Contents (child_type, &child) )
				{
					if (strcmp(child_type,"include")==0)
					{
 						HC_KEY ikey = HC_KShow_Include_Segment(child);
						Color( ikey, "", 0, 0, r, g, b, recurse, emit_message);
					}
					else
						Color( child, "", 0, 0, r, g, b, recurse, emit_message);
				}
				HC_End_Contents_Search();
			}
		HC_Close_Segment();

    }
    else 
	{
        seg_key = HC_KShow_Owner_By_Key(key);

		HC_Open_Segment_By_Key(seg_key);
		 HC_Open_Segment("");   
		  HC_Set_Color_By_Value("faces,edges,lines", "RGB", r, g, b );
		  HC_Move_By_Key(key, ".");
		 HC_Close_Segment();
		HC_Close_Segment();	

    }
}



//======================================================================
//	Author :Rajesh B			Created : 3/20/2001 5:15:31 PM
//======================================================================
//	Function :		CSolidHoopsView::OnEditLights
//	Description :	Pops up the CEditLightDlg for add/remove of lights
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsView::OnEditLights() 
{
	CEditLightsDlg light_dlg(m_pHView);
	light_dlg.DoModal();
}

void CSolidHoopsView::OnViewCoordinatesystemLefthanded() 
{
	SetCoordinateSystemHandedness(HandednessLeft);
	m_pHView->Update();	
	
}

void CSolidHoopsView::OnViewCoordinatesystemRighthanded() 
{
	SetCoordinateSystemHandedness(HandednessRight);
	m_pHView->Update();	
	
}

void CSolidHoopsView::OnUpdateViewCoordinatesystemLefthanded(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetHandedness() == HandednessLeft)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnUpdateViewCoordinatesystemRighthanded(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetHandedness() == HandednessRight)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

static void GetSegmentShells( HC_KEY segKey, vlist_s* retShells, bool do_recurse = true )
{
    char type[MVO_BUFFER_SIZE];
    HC_KEY	key;
	HC_Open_Segment_By_Key( segKey );
		if (do_recurse) 
		{
			HC_Begin_Contents_Search (".", "segment, includes");
				while (HC_Find_Contents (type, &key) ) 
				{
					if (strstr("include", type))
					{
						HC_KEY new_key = HC_KShow_Include_Segment(key);
						GetSegmentShells( new_key, retShells, true );
					}
					else
						GetSegmentShells( key, retShells, true );
				}
		    HC_End_Contents_Search ();
		}

		/*
		 * after all of the children have been processed, process  current segment
		 *   (i.e., a post-order tree traversal)
		 */
		HC_Begin_Contents_Search (".", "shells");
			while (HC_Find_Contents (type, &key)) 
				vlist_add_last(retShells, (void*) key);
		HC_End_Contents_Search ();

	HC_Close_Segment();
}



void CSolidHoopsView::GetShells(HC_KEY key, vlist_s* retSelectedShells, bool do_recurse)
{
	char type[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(key, type);

	if( strstr(type, "shell") )
		vlist_add_last(retSelectedShells, (void*) key );
	else if	(strstr(type, "include") )
	{
		key = HC_KShow_Include_Segment(key);
		GetSegmentShells(key, retSelectedShells, do_recurse);
	}
	else if ( strstr(type, "segment") )
		GetSegmentShells(key, retSelectedShells, do_recurse);

	return;
}


void CSolidHoopsView::OnDestroy()
{
	CAppSettings::ChildStartMaximized = GetParent()->IsZoomed() != 0;


	m_cease = true;

	// StreamingThread might be waiting for this signal, free it first (if it exists)
	if( m_hStreamBufferAccessEvent != 0 )
	    SetEvent(m_hStreamBufferAccessEvent);

	while(m_hStreamBufferAccessEvent);

	CHoopsView::OnDestroy();
}

void CSolidHoopsView::OnUpdateAnimate(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnUpdateViewWindowcolor(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnUpdateZoomToExtents(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnUpdateComputeSampleData(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnUpdateFramerateoptions(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable (1);	
}


void CSolidHoopsView::OnUpdateFileLoad(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnUpdateTopolbrowser(CCmdUI* pCmdUI) 
{
#ifndef HOOPS_ONLY
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pDlgTopologyBrowser && m_pDlgTopologyBrowser->IsWindowVisible())
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
#endif
}

void CSolidHoopsView::OnUpdateModelBrowser(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pDlgModelBrowser && m_pDlgModelBrowser->IsWindowVisible())
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsView::OnUpdateEditColor(CCmdUI* pCmdUI) 
{
}

//======================================================================
//	Author :Rajesh B			Created : 3/11/2002 2:49:17 PM
//======================================================================
//	Function :		CSolidHoopsView::ExtractNURBSSurfaces
//	Description :	Extracts BSurfs from Modeller and converts them to 
//					HOOPS BSurfs
//	Return :void	-	
//	Parameters :
//			bool non_rational	-	Want non-rational surfs
//			bool trimmed	-		want trimmed surfs
//			bool use_polyline	-	use polylines as trimming curves
//	Note : DO NOT DELETE THIS FUNCTION - IT IS USED FOR QA PURPOSES
//======================================================================
void CSolidHoopsView::ExtractNURBSSurfaces(bool non_rational, bool trimmed, bool use_polyline)
{
	CString  filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";
	TCHAR def_file_ext[10] = _T(".hmf");

	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidModel)
		return;

	CFileDialog my_dlg(FALSE, def_file_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter , NULL);
	if (my_dlg.DoModal() != IDOK)
		return;

	

	HC_Open_Segment("/Include Library/Temp Trimmed NURBS Surf");
	HC_Flush_Contents(".", "everything");
#ifdef PARASOLID
	HSolidModel* pModel = (HSolidModel*) m_pHView->GetModel();
	int nb = 0;
	PK_BODY_t* bodies;
	PK_ERROR_t err = PK_PARTITION_ask_bodies(pModel->GetPartition(), &nb, &bodies);
	for( int ib = 0; ib < nb; ib++ )
	{
		int nf = 0;
		PK_FACE_t* faces;
		err = PK_BODY_ask_faces( bodies[ib], &nf, &faces);

		for( int jf = 0; jf < nf; jf++ )
		{

			PK_FACE_output_surf_trimmed_o_t trim_ops;
			PK_FACE_output_surf_trimmed_o_m(trim_ops);
			trim_ops.non_rational = (non_rational == true) ? PK_LOGICAL_true : PK_LOGICAL_false;
			trim_ops.trim_surf = PK_FACE_trim_surf_bsurf_c;
			trim_ops.want_geoms = PK_LOGICAL_false;

			PK_SURF_t              surf;
			PK_LOGICAL_t           sense;
			PK_SURF_trim_data_t    trim_data;
			err = PK_FACE_output_surf_trimmed( faces[jf],  &trim_ops,
												&surf, &sense,      
												&trim_data,  0, 0,  0 );

			HC_KEY bsurf_key = Parasolid2HoopsNurbsSurface(surf);

			if( trimmed )
				InsertTrimData(bsurf_key, surf, trim_data, use_polyline);

			if( trim_data.n_spcurves > 1 )
			{
				PK_MEMORY_free(trim_data.spcurves);
				PK_MEMORY_free(trim_data.intervals);
				PK_MEMORY_free(trim_data.trim_loop);
				PK_MEMORY_free(trim_data.trim_set);
			}

		}
		if( nf > 0 )
			PK_MEMORY_free(faces);
	}
	if( nb > 0 )
		PK_MEMORY_free(bodies);
#endif // PARASOLID
	char hmf_options[MVO_BUFFER_SIZE];
	strcpy(hmf_options, "use color names, follow cross-references");
	HC_Write_Metafile(".", H_ASCII_TEXT(my_dlg.GetPathName()), hmf_options); 
	HC_Close_Segment();

}


//======================================================================
//	Author :Rajesh B			Created : 3/11/2002 2:49:17 PM
//======================================================================
//	Function :		CSolidHoopsView::ExtractNURBSCurves
//	Description :	Extracts BCurves from Modeller and converts them to 
//					HOOPS NURBS curves
//	Return :void	-	
//	Parameters :
//			bool non_rational	-	Want non-rational surfs
//			bool trimmed	-		want trimmed surfs
//			bool use_polyline	-	use polylines as trimming curves
//	Note : DO NOT DELETE THIS FUNCTION - IT IS USED FOR QA PURPOSES
//======================================================================
void CSolidHoopsView::ExtractNURBSCurves(bool non_rational, bool cubic, double tolerance )
{
	CString  filter = "HOOPS Stream File (*.hsf)|*.hsf|HOOPS Metafile (*.hmf)|*.hmf||";
	TCHAR def_file_ext[10] = _T(".hmf");

	if (!((HSolidModel *)(m_pHView->GetModel()))->m_bSolidModel)
		return;

	CFileDialog my_dlg(FALSE, def_file_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter , NULL);
	if (my_dlg.DoModal() != IDOK)
		return;

	HC_Open_Segment("/Include Library/Temp Trimmed NURBS Curves");
	HC_Flush_Contents(".", "everything");
#ifdef PARASOLID
	HSolidModel* pModel = (HSolidModel*) m_pHView->GetModel();
	int nb = 0;
	PK_BODY_t* bodies;
	PK_ERROR_t err = PK_PARTITION_ask_bodies(pModel->GetPartition(), &nb, &bodies);
	for( int ib = 0; ib < nb; ib++ )
	{
		int ne = 0;
		PK_EDGE_t* edges;
		err = PK_BODY_ask_edges( bodies[ib], &ne, &edges);

		for( int je = 0; je < ne; je++ )
		{
			// get the curve for this edge & convert the curve to bcurve
			PK_CURVE_t edge_curve;
			PK_CLASS_t curve_class;
			PK_VECTOR_t ends[2];
			PK_INTERVAL_t range;
			PK_LOGICAL_t sense;
			err = PK_EDGE_ask_geometry( edges[je], PK_LOGICAL_true, &edge_curve,
										&curve_class, ends, &range, &sense);

			if( (err != PK_ERROR_no_errors) || (edge_curve == PK_ENTITY_null) )
				continue;

			PK_BCURVE_t b_curve;
			PK_LOGICAL_t pkl_cubic = (cubic == true) ? PK_LOGICAL_true : PK_LOGICAL_false;
			PK_LOGICAL_t pkl_non_rational = (non_rational == true) ? PK_LOGICAL_true : PK_LOGICAL_false;
			PK_LOGICAL_t pkl_exact;
			err = PK_CURVE_make_bcurve( edge_curve, range, pkl_cubic, pkl_non_rational,  tolerance, 
										 &b_curve, &pkl_exact );

			// pass this bcurve to our nurbs converting utility
			HC_KEY bcurve_key = ParasolidBCurve2HoopsNurbsCurve(b_curve, false);
		}
		if( ne > 0 )
			PK_MEMORY_free(edges);
	}
	if( nb > 0 )
		PK_MEMORY_free(bodies);
#endif // PARASOLID
	char hmf_options[MVO_BUFFER_SIZE];
	strcpy(hmf_options, "use color names, follow cross-references");
	HC_Write_Metafile(".", H_ASCII_TEXT(my_dlg.GetPathName()), hmf_options); 
	HC_Close_Segment();

}

//======================================================================
//	Author :Rajesh B			Created : 7/3/2002 2:08:56 PM
//======================================================================
//	Function :		CSolidHoopsView::ConvertFaceShellsToRegions
//	Description :	Merges all the face shells in one single shell
//					and marks each face as region within that shell
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsView::ConvertFaceShellsToRegions()
{
	CString  filter = "HOOPS Metafile (*.hmf)|*.hmf||";
	TCHAR def_file_ext[10] = _T(".hmf");

	CFileDialog my_dlg(FALSE, def_file_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter , NULL);
	if (my_dlg.DoModal() != IDOK)
		return;

	HSolidModel* pModel = (HSolidModel*) m_pHView->GetModel();

#ifndef HOOPS_ONLY
	// make sure that we have one shell per face type of configuration
	CBusyDlg *	busy = new CBusyDlg();
 	busy->Create(IDD_BUSYDLG);
	busy->ShowWindow(SW_SHOW); 
	((HSolidView *)m_pHView)->SetOptimizations(false);	
	if(m_pDlgTopologyBrowser && m_pDlgTopologyBrowser->IsWindowVisible())
		m_pDlgTopologyBrowser->UpdateTopolBrowserCheckboxes();
	delete busy;
#endif // HOOPS_ONLY

	HC_Open_Segment("/Include Library/Temp Face Regions");
	HC_Flush_Contents(".", "everything");
	if (!pModel->m_bSolidModel)
	{
		// open the model key and grab all the shells
		vlist_s* p_shells = new_vlist(malloc, free);
		GetShells(pModel->GetModelKey(), p_shells, true);
		int num_shells = vlist_count(p_shells);
		if( num_shells <= 1 )
		{
			AfxMessageBox(_T("One or less shells found. Operation failed"));
			return;
		}
		HC_KEY* shell_keys = new HC_KEY[num_shells];
		vlist_reset_cursor( p_shells );
		HC_KEY shell;
		int i = 0;
		while( shell = (HC_KEY) (HC_POINTER_SIZED_INT) vlist_peek_cursor( p_shells ) ) 
		{
			shell_keys[i] = shell;
			i++;
			vlist_advance_cursor( p_shells );
		}
#ifdef PARASOLID
		HC_KEY merged_shell = HUtility::Merge_Shells_Generate_Regions(num_shells, shell_keys, false);
#endif // PARASOLID
		delete_vlist(p_shells);
		delete[] shell_keys;

	}
	else
	{
#ifdef PARASOLID
	int nb = 0;
	PK_BODY_t* bodies;
	PK_ERROR_t err = PK_PARTITION_ask_bodies(pModel->GetPartition(), &nb, &bodies);
	for( int ib = 0; ib < nb; ib++ )
	{
		// get all the shells corresponding to each face
		int nf = 0;
		PK_FACE_t* faces;
		err = PK_BODY_ask_faces( bodies[ib], &nf, &faces);
		if( nf > 0 )
		{
			HC_KEY* face_shells = new HC_KEY[nf];
			int num_shells = 0;
			HC_KEY face_shell = -1;
			for( int jf = 0; jf < nf; jf++ )
			{
				if( HP_Compute_Geometry_Keys(faces[jf], 1, &face_shell, "faces") == 1 )
				{
					face_shells[num_shells] = face_shell;
					num_shells++;
				}
			}
			HC_KEY merged_shell = HUtility::Merge_Shells_Generate_Regions(num_shells, face_shells, false);

			delete[] face_shells;
			PK_MEMORY_free(faces);
		}
	}
	if( nb > 0 )
		PK_MEMORY_free(bodies);
#endif // PARASOLID
	}
	char hmf_options[MVO_BUFFER_SIZE];
	strcpy(hmf_options, "use color names, follow cross-references");
	HC_Write_Metafile(".", H_ASCII_TEXT(my_dlg.GetPathName()), hmf_options); 
	HC_Close_Segment();

}


void CSolidHoopsView::OnViewBackplaneculling() 
{
	m_pHView->SetBackplaneCulling(!m_pHView->GetBackplaneCulling());
	m_pHView->Update();	
}

void CSolidHoopsView::OnUpdateViewBackplaneculling(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetBackplaneCulling())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


//======================================================================
//	Author :Rajesh B			Created : 4/26/2002 3:25:34 PM
//======================================================================
//	Function :		CSolidHoopsView::SetCoordinateSystemHandedness
//	Description :	Sets the coordinate system handedness in the view
//					and in the model as well
//	Return :void	-	
//	Parameters :
//			CoordSysHandedness right_or_left	-	
//	Note : I HAVE CHANGED THE BEHAVIOR TO JUST CALL THE HBaseView function
//         WE HAVE DECIDED NOT TO EXPLICITLY SET HANDEDNESS ON MODEL
//======================================================================
void CSolidHoopsView::SetCoordinateSystemHandedness(HandednessMode right_or_left, bool emit_message )
{
	m_pHView->SetHandedness( right_or_left, emit_message );
}

//======================================================================
//	Author :Rajesh B			Created : 4/26/2002 3:26:04 PM
//======================================================================
//	Function :		CSolidHoopsView::SetWindowColor
//	Description :	Sets the window background color for this view
//	Return :void	-	
//	Parameters :
//			COLORREF new_color	-	
//			bool emit_message	-	
//	Note :
//======================================================================
void CSolidHoopsView::SetWindowColor(COLORREF new_top_color, COLORREF new_bottom_color, bool emit_message)
{
	HPoint WindowTopColor;
	WindowTopColor.Set(
		static_cast<float>(GetRValue(new_top_color))/255.0f,
		static_cast<float>(GetGValue(new_top_color))/255.0f,
		static_cast<float>(GetBValue(new_top_color))/255.0f);

	HPoint WindowBottomColor;
	WindowBottomColor.Set(
		static_cast<float>(GetRValue(new_bottom_color))/255.0f,
		static_cast<float>(GetGValue(new_bottom_color))/255.0f,
		static_cast<float>(GetBValue(new_bottom_color))/255.0f);


	m_pHView->SetWindowColor(WindowTopColor, WindowBottomColor, emit_message);
}

//======================================================================
//	Author :Rajesh B			Created : 4/26/2002 3:26:23 PM
//======================================================================
//	Function :		CSolidHoopsView::SetPolygonHandedness
//	Description :	Sets the polygon handedness for the view and model
//	Return :void	-	
//	Parameters :
//			ModelHandedness new_handedness	-	
//	Note :
//======================================================================
void CSolidHoopsView::SetPolygonHandedness(ModelHandedness new_handedness)
{
	// now onwards (9.0) we don't set the handedness just on view.
	// we do not mess up with model segment at all - Rajesh B (13-May-03)
	if( new_handedness == 	HandednessSetLeft )
		m_pHView->SetPolygonHandednessMode(HandednessLeft);
	else if( new_handedness == 	HandednessSetRight )
		m_pHView->SetPolygonHandednessMode(HandednessRight);
	else if( new_handedness == 	HandednessSetNone )
		m_pHView->SetPolygonHandednessMode(HandednessNone);
	else if( new_handedness == 	HandednessNotSet )
		;
	else
		assert(0);
}

void CSolidHoopsView::SetMarkupColor(COLORREF new_color, bool emit_message)
{
	HPoint new_mkp_color;
	new_mkp_color.Set(
		static_cast<float>(GetRValue(new_color))/255.0f,
		static_cast<float>(GetGValue(new_color))/255.0f,
		static_cast<float>(GetBValue(new_color))/255.0f);
	HC_Open_Segment_By_Key(m_pHView->GetMarkupManager()->GetMarkupKey());
 	HC_Set_Color_By_Value("everything", "RGB", new_mkp_color.x, new_mkp_color.y, new_mkp_color.z);
	HC_Close_Segment();
	m_pHView->GetMarkupManager()->SetMarkupColor(new_mkp_color);
}

void CSolidHoopsView::SetShadowColor(COLORREF new_color)
{
	HPoint new_shd_color;
	new_shd_color.Set(
		static_cast<float>(GetRValue(new_color))/255.0f,
		static_cast<float>(GetGValue(new_color))/255.0f,
		static_cast<float>(GetBValue(new_color))/255.0f);
	m_pHView->SetShadowColor(new_shd_color);
}


void CSolidHoopsView::OnRedlineRectangle() 
{
	LocalSetOperator(new HOpMarkupRectangle(m_pHView));
}

void CSolidHoopsView::OnUpdateRedlineRectangle(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupRectangle"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);	
}

void CSolidHoopsView::OnRedlineCircle() 
{
	LocalSetOperator(new HOpMarkupCircle(m_pHView));
}

void CSolidHoopsView::OnUpdateRedlineCircle(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupCircle"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnMarkupCircle() 
{
	LocalSetOperator(new HOpMarkupCircle(m_pHView));
}

void CSolidHoopsView::OnUpdateMarkupCircle(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupCircle"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnMarkupFreehand() 
{
	LocalSetOperator(new HOpMarkupFreehand(m_pHView));
}

void CSolidHoopsView::OnUpdateMarkupFreehand(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupFreehand"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnMarkupRectangle() 
{
	LocalSetOperator(new HOpMarkupRectangle(m_pHView));
}

void CSolidHoopsView::OnUpdateMarkupRectangle(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupRectangle"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnZxPlane() 
{
	m_pHView->SetViewMode(HViewBottom);
}

void CSolidHoopsView::OnUpdateZxPlane(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewZX)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnZyPlane() 
{
	m_pHView->SetViewMode(HViewRight);
}

void CSolidHoopsView::OnUpdateZyPlane(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewZY)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnYxPlane() 
{
	m_pHView->SetViewMode(HViewBack);
}

void CSolidHoopsView::OnUpdateYxPlane(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewYX)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnIsometric() 
{
	m_pHView->SetViewMode(HViewIsoFrontRightTop);
	m_pHView->Update();
}

void CSolidHoopsView::OnSEIsometric() 
{
	m_pHView->SetViewMode(HViewSEIso);
	m_pHView->Update();
}

void CSolidHoopsView::OnSWIsometric() 
{
	m_pHView->SetViewMode(HViewSWIso);
	m_pHView->Update();
}

void CSolidHoopsView::OnNEIsometric() 
{
	m_pHView->SetViewMode(HViewNEIso);
	m_pHView->Update();
}

void CSolidHoopsView::OnNWIsometric() 
{
	m_pHView->SetViewMode(HViewNWIso);
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateIsometric(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetViewMode() == HViewIso)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnMarkupAnnotate() 
{
	LocalSetOperator(new HOpMarkupPostIt(m_pHView));
}

void CSolidHoopsView::OnUpdateMarkupAnnotate(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupPostIt"))
	pCmdUI->SetCheck (1);
	else
	pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnUpdateConstantspin(CCmdUI* pCmdUI) 
{
	CSolidHoopsApp * pApp = (CSolidHoopsApp*) AfxGetApp();
	assert(pApp);

	pCmdUI->Enable(1);
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		pApp->GetConstantSpin())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnAnnotate() 
{
	LocalSetOperator(new HOpMarkupAnnotate(m_pHView));
}

void CSolidHoopsView::OnUpdateAnnotate(CCmdUI* pCmdUI) 
{
	if	(!CAppSettings::DisableEditing)
		pCmdUI->Enable (1);
	else
		pCmdUI->Enable (0);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpMarkupAnnotate"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnViewAntialiasing() 
{
	CWaitCursor display_hourglass_cursor_till_we_finish_this_long_process;
	m_pHView->RenderAntialiasing();	
}

void CSolidHoopsView::OnUpdateViewAntialiasing(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnToolsVisibilityLines()
{
	HSolidView * pHView = (HSolidView*) GetHoopsView();
	assert(pHView);
	pHView->SetVisibilityLines(!pHView->GetVisibilityLines());
	HSelectionSet * selection=pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	pHView->Update();
}

void CSolidHoopsView::OnUpdateToolsVisibilityLines(CCmdUI* pCmdUI)
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		((HSolidView*)m_pHView)->GetVisibilityLines())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);	
}

void CSolidHoopsView::RefreshSegmentBrowser()
{ 
	if(m_pDlgSegmentBrowser) 
		m_pDlgSegmentBrowser->RefreshBrowser(); 
};

CDialog * CSolidHoopsView::GetSegmentBrowserDialog()
{
	if( !m_pDlgSegmentBrowser )
 		m_pDlgSegmentBrowser = new CSegmentBrowserDlg(this, m_pHView);
	
	assert( m_pDlgSegmentBrowser );
	return m_pDlgSegmentBrowser;
}

CDialog * CSolidHoopsView::GetModelBrowserDialog()
{
	if( !m_pDlgModelBrowser )
	{
		CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
		CString pname = pDoc->GetPathName();
		TCHAR extension[MVO_BUFFER_SIZE];
		HUtility::FindFileNameExtension((pname), extension);
		m_pDlgModelBrowser = new CModelBrowserDlg(this, m_pHView, extension);
		//m_pDlgModelBrowser = new CModelBrowserDlg(this, m_pHView);
	}

	assert( m_pDlgModelBrowser );
	return m_pDlgModelBrowser;
}

CDialog * CSolidHoopsView::GetErrorBrowserDialog()
{
	if( !m_pDlgErrorBrowser )
 		m_pDlgErrorBrowser = new CErrorBrowserDlg(this, m_pHView);
	
	assert( m_pDlgErrorBrowser );
	return m_pDlgErrorBrowser;
}

CDialog * CSolidHoopsView::GetKeyframeEditorDialog(bool create)
{
    if (create){
		if( !m_pDlgKeyframeEditor ){
 			m_pDlgKeyframeEditor = new CKeyframeEditor(this, m_pHView);
	 		m_pHView->GetEventManager()->RegisterHandler((HAnimationListener *)m_pDlgKeyframeEditor, HAnimationListener::GetType(), HLISTENER_PRIORITY_HIGH);
		}
    }
	
 	return m_pDlgKeyframeEditor;
}

CDialog * CSolidHoopsView::GetClashBrowserDialog(bool create)
{
    if (create){
		if( !m_pDlgClashBrowser ){
 			m_pDlgClashBrowser = new ClashDlg(this, (HSolidView *)m_pHView);
 		}
    }
	
 	return m_pDlgClashBrowser;
}
CDialog * CSolidHoopsView::GetClashSelectDialog(bool create)
{
    if (create){
		if( !m_pDlgClashSelect ){
 			m_pDlgClashSelect = new ClashSelect(this, (HSolidView *)m_pHView);
 		}
    }
	
 	return m_pDlgClashSelect;
}


CDialog * CSolidHoopsView::GetTopologyBrowserDialog()
{
#ifndef HOOPS_ONLY
	if( !m_pDlgTopologyBrowser )
	{
		if (((HSolidModel *)(m_pHView->GetModel()))->m_bPlainSolidModel)
			m_pDlgTopologyBrowser = new CPlainTopolBrowserDlg(this,GetSolidView());
#ifdef PARASOLID
		else
			m_pDlgTopologyBrowser = new CPSTopolBrowserDlg(this,GetSolidView());
#endif // PARASOLID
#ifdef ACIS
		else
			m_pDlgTopologyBrowser = new CASTopolBrowserDlg(this,GetSolidView());
#endif // ACIS
#ifdef GRANITE
		else
			m_pDlgTopologyBrowser = new CGSTopolBrowserDlg(this,GetSolidView());
#endif // GRANITE
	}

	assert( m_pDlgTopologyBrowser );
	return m_pDlgTopologyBrowser;
#else
	AfxMessageBox(_T("Topology Browser not implemented for HOOPS_ONLY partviewer"));
	assert(0);
	return 0;
#endif // HOOPS_ONLY
}

CDialog * CSolidHoopsView::GetCMMDisplayDialog(bool create)
{
    if (create || !m_pDlgCMMDisplay){
		if( !m_pDlgCMMDisplay ){
 			m_pDlgCMMDisplay = new CCMMDisplay(this, m_pHView);
	 		m_pHView->GetModel()->GetEventManager()->RegisterHandler((HAnimationListener *)m_pDlgCMMDisplay, HAnimationListener::GetType(), HLISTENER_PRIORITY_HIGH);
		}
    }
	
 	return m_pDlgCMMDisplay;
}

CDialog * CSolidHoopsView::GetInterOpPartBrowserDialog () {
#ifdef INTEROP
	if (!m_pDlgInterOpPartBrowser)
 		m_pDlgInterOpPartBrowser = new CInterOpPartBrowserDlg(this, GetSolidView());
	
	assert(m_pDlgInterOpPartBrowser);
	return m_pDlgInterOpPartBrowser;
#else
	AfxMessageBox(_T("InterOp Part Browser requires an InterOp Part Viewer."));
	assert(0);
	return 0;
#endif // INTEROP
}

#ifdef HOOPS_ONLY
void CSolidHoopsView::OnCreateCone() 
{
    LocalSetOperator(new HOpCreateCone(m_pHView));
}
void CSolidHoopsView::OnUpdateCreateCone(CCmdUI* pCmdUI) 
{
	if	( !CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCreateCone"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnCreateCylinder() 
{
    LocalSetOperator(new HOpCreateCylinder(m_pHView));		
}

void CSolidHoopsView::OnUpdateCreateCylinder(CCmdUI* pCmdUI) 
{
	if	( !CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	
	
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCreateCylinder"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnCreateSphere() 
{
    LocalSetOperator(new HOpCreateSphere(m_pHView));		
}
void CSolidHoopsView::OnUpdateCreateSphere(CCmdUI* pCmdUI) 
{
	if	( !CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	
	
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCreateSphere"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnCreateNurbscurve() 
{
	 LocalSetOperator(new HOpCreateNurbsCurve(m_pHView));	
}

void CSolidHoopsView::OnUpdateCreateNurbscurve(CCmdUI* pCmdUI) 
{
	if	( !CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	
	
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpCreateNurbsCurve"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnClashDetection() 
{
    LocalSetOperator(new HOpObjectClash(m_pHView));
	
}

void CSolidHoopsView::OnUpdateClashDetection(CCmdUI* pCmdUI) 
{
	HSSelectionSet* sel_set = (HSSelectionSet *)GetSolidView()->GetSelection();
	assert(sel_set);
	if	( !CAppSettings::DisableEditing 
		&& (sel_set->GetSelectLevel() == SEGMENT_TYPE) 
		&& (sel_set->GetSize() >= 0) )
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	
	
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpObjectClash"))
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnViewAnimateObject() 
{
    LocalSetOperator(new HTCObjectRotate(m_pHView));	
}

void CSolidHoopsView::OnUpdateViewAnimateObject(CCmdUI* pCmdUI) 
{
}

void CSolidHoopsView::OnSegmentSelectLevel() 
{
	HSSelectionSet *selection = (HSSelectionSet *)m_pHView->GetSelection();
	if (selection->GetSelectLevel() != SEGMENT_TYPE) {
		selection->DeSelectAll();
		m_pHView->Update();	
	}
	selection->SetSelectLevel(SEGMENT_TYPE);	
	m_pHView->SetViewSelectionLevel(HSelectionLevelSegment);
	m_pHView->Update();	
}

void CSolidHoopsView::OnUpdateSegmentSelectLevel(CCmdUI* pCmdUI) 
{
	if	(m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		 ((HSSelectionSet*)m_pHView->GetSelection())->GetSelectLevel() == SEGMENT_TYPE)
		pCmdUI->SetCheck (0);
    else
        pCmdUI->SetCheck (1);
}

void CSolidHoopsView::OnSubentitySelectLevel() 
{
	HSSelectionSet *selection = (HSSelectionSet *)m_pHView->GetSelection();
	if (selection->GetSelectLevel() != SUBENTITY_TYPE) {
		selection->DeSelectAll();
		m_pHView->Update();	
	}
	selection->SetSelectLevel(SUBENTITY_TYPE);	
	m_pHView->SetViewSelectionLevel(HSelectionLevelEntity);
	m_pHView->Update();	
}

void CSolidHoopsView::OnUpdateSubentitySelectLevel(CCmdUI* pCmdUI) 
{
	if	(m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		 ((HSSelectionSet*)m_pHView->GetSelection())->GetSelectLevel() == SUBENTITY_TYPE)
		pCmdUI->SetCheck (0);
    else
        pCmdUI->SetCheck (1);	
}

void CSolidHoopsView::OnSubentityFaces()
{
	HSelectionSet *selection = (HSelectionSet *)m_pHView->GetSelection();
	
	selection->SetSubentityFaceSelection(!selection->GetSubentityFaceSelection());	
}

void CSolidHoopsView::OnSubentityEdges()
{
	HSelectionSet *selection = (HSelectionSet *)m_pHView->GetSelection();
	
	selection->SetSubentityEdgeSelection(!selection->GetSubentityEdgeSelection());	
}

void CSolidHoopsView::OnSubentityVertices()
{
	HSelectionSet *selection = (HSelectionSet *)m_pHView->GetSelection();
	
	selection->SetSubentityVertexSelection(!selection->GetSubentityVertexSelection());	
}


void CSolidHoopsView::OnEntitySelectLevel() 
{
	HSSelectionSet *selection = (HSSelectionSet *)m_pHView->GetSelection();
	if (selection->GetSelectLevel() != ENTITY_TYPE) {
		selection->DeSelectAll();
		m_pHView->Update();	
	}
	selection->SetSelectLevel(ENTITY_TYPE);	
	m_pHView->SetViewSelectionLevel(HSelectionLevelEntity);
	m_pHView->Update();	
}

void CSolidHoopsView::OnUpdateEntitySelectLevel(CCmdUI* pCmdUI) 
{
	if	(m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		 ((HSSelectionSet*)m_pHView->GetSelection())->GetSelectLevel() == ENTITY_TYPE)
		pCmdUI->SetCheck (0);
    else
        pCmdUI->SetCheck (1);
}


#endif // HOOPS_ONLY

void CSolidHoopsView::OnNcDestroy()
{
    HC_KEY viewKey = m_pHView->GetViewKey();
    if (viewKey)
    {
	    HC_Delete_By_Key (viewKey);
	    HC_Update_One_Display(m_pHView->GetDriverPath());
	    m_pHView->SetViewKey(0);
    }

    CHoopsView::OnNcDestroy();
}

void CSolidHoopsView::PostNcDestroy() 
{
	CHoopsView::PostNcDestroy();

//	pass this message to the mainframe window for updating the dialog bars
	CSolidHoopsFrame* pMainFrm = (CSolidHoopsFrame*) AfxGetMainWnd();
	if( pMainFrm )
		pMainFrm->ViewDestoryed(this);
}


void CSolidHoopsView::OnCappingPlanes() 
{
	m_pHView->SetCPGeomVisibility(m_pHView->GetCPLineVisibility(), !m_pHView->GetCPFaceVisibility());
	m_pHView->Update();	
}

void CSolidHoopsView::OnUpdateCappingPlanes(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetCPFaceVisibility() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CSolidHoopsView::OnCappingLines() 
{
	m_pHView->SetCPGeomVisibility(!m_pHView->GetCPLineVisibility(), m_pHView->GetCPFaceVisibility());
	m_pHView->Update();	
}

void CSolidHoopsView::OnUpdateCappingLines(CCmdUI* pCmdUI) 
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetCPLineVisibility() )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//======================================================================
//	Function :		CSolidHoopsView::OnViewSoftShadow
//	Description :	Toggles the shadow display and triggers appropriate 
//					call to the base view.
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsView::OnViewSoftShadow() 
{
	if (m_pHView->GetShadowMode() == HShadowNone)
		m_pHView->SetShadowMode(HShadowSoft);
	else
		m_pHView->SetShadowMode(HShadowNone);

	m_pHView->Update();
}

bool CSolidHoopsView::IsFrameRateEnabled()
{
	return m_pHView->IsFrameRateEnabled();
}
//======================================================================
//	Function :		CSolidHoopsView::OnUpdateViewSoftShadow
//	Description :	Shadows cannot be displayed in any other modes than
//					gouraud, flat or phong. The menu is grayed in other modes.
//	Return :void	-	
//	Parameters :
//			CCmdUI* pCmdUI	-	
//	Note :
//======================================================================
void CSolidHoopsView::OnUpdateViewSoftShadow(CCmdUI* pCmdUI) 
{
//	HRenderMode curr_mode = m_pHView->GetRenderMode();
//	if( (curr_mode == HRenderShaded ) || (curr_mode == HRenderGouraud) || (curr_mode == HRenderFlat) || (curr_mode == HRenderPhong) || (curr_mode == HRenderShadedWithLines) ||
//		(curr_mode == HRenderGouraudWithLines))
	pCmdUI->Enable (1);

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetShadowMode() == HShadowSoft)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);	
}

void CSolidHoopsView::OnBehaviorPlay() 
{
	HBhvBehaviorManager * pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	m_pHView->GetModel()->GetBhvBehaviorManager()->SetUpdateCamera(CAppSettings::UpdateCamera);

	if (!m_pHView->GetModel()->GetBhvBehaviorManager()->IsPlaying())
	{
  		pBehaviorManager->Continue();
		if (!m_pHView->GetAllowInteractiveShadows())
			m_pHView->SetShadowMode(HShadowNone, false);
		if (m_pHView->IsFrameRateEnabled() && CAppSettings::DisableCFR)
	 		m_pHView->GetConstantFrameRateObject()->Stop();
 		SetTimer(H_TIMER_BHV_UPDATE,1000,0);
	}
	else
	{
		pBehaviorManager->Stop();
 		KillTimer(H_TIMER_BHV_UPDATE);
		m_pHView->SetShadowMode(m_pHView->GetShadowMode());
		if (m_pHView->IsFrameRateEnabled() && CAppSettings::DisableCFR)
		{
			m_pHView->GetConstantFrameRateObject()->ResetListPointers();
			m_pHView->GetConstantFrameRateObject()->Start();
		}
 		UpdateBhvWindows(true);
	}
	m_pHView->Update();

}
void CSolidHoopsView::OnUpdateBehaviorPlay(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetModel()->GetBhvBehaviorManager()->IsPlaying())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);

	if (m_pHView->GetModel()->GetBhvBehaviorManager()->HasAnimations())
		pCmdUI->Enable (1);
	else
		pCmdUI->Enable (0);
}

void CSolidHoopsView::OnBehaviorRewind() 
{
	m_pHView->GetModel()->GetBhvBehaviorManager()->Rewind();  	
	KillTimer(H_TIMER_BHV_UPDATE);
 
	m_pHView->SetShadowMode(m_pHView->GetShadowMode());
	if (m_pHView->IsFrameRateEnabled() && CAppSettings::DisableCFR)
	{
		m_pHView->GetConstantFrameRateObject()->ResetListPointers();
		m_pHView->GetConstantFrameRateObject()->Start();
	}
	UpdateBhvWindows(true);
}


void CSolidHoopsView::OnUpdateBehaviorRewind(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetModel()->GetBhvBehaviorManager()->HasAnimations())
         pCmdUI->Enable (1);	
	else
         pCmdUI->Enable (0);	

}
class CZLevel{
public:
	CZLevel(){
		m_zstr = 0;
		m_z = 0;
	};

	explicit CZLevel(char * str){
		if(str){
			m_zstr = strdup(str);
			m_z = atof(m_zstr);
		}
		else {
			m_zstr = 0;
			m_z = 0;
		}
	};

	CZLevel(CZLevel const & rhs){
		m_z = rhs.GetZValue();
		if(rhs.GetZStr())
			m_zstr = strdup(rhs.GetZStr());
		else m_zstr = 0;
	}

	~CZLevel(){
		if(m_zstr)
			free(m_zstr);
	};

	float const GetZValue() const {
		return m_z;
	};

	char const * const GetZStr() const {
		return m_zstr;
	};

	bool const operator < (CZLevel const & rhs) const {
		return m_z < rhs.GetZValue();
	};
	
	bool const operator > (CZLevel const & rhs) const {
		return m_z > rhs.GetZValue();
	};

	bool const operator == (CZLevel const & rhs) const;
	bool const operator != (CZLevel const & rhs) const;
	CZLevel const & operator= (CZLevel const & rhs);

private:
	float m_z;
	char * m_zstr;
};

bool const CZLevel::operator == (CZLevel const & rhs) const {
	return m_z == rhs.GetZValue();
}

bool const CZLevel::operator != (CZLevel const & rhs) const {
	return m_z != rhs.GetZValue();
}

CZLevel const & CZLevel::operator = (CZLevel const & rhs) {
	m_z = rhs.GetZValue();
	if(rhs.GetZStr())
		m_zstr = strdup(rhs.GetZStr());
	else m_zstr = 0;
	return *this;
}

static int CZLevelCompare(void const * a, void const * b)
{
	CZLevel za;
	CZLevel zb;
	
	za = **(CZLevel const **)a;
	zb = **(CZLevel const **)b;

	if(za > zb)
		return 1;
	if(za < zb)
		return -1;
	return 0;
}

void CSolidHoopsView::OnCMMHScroll(float percent)
{
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());{

		int polyline_seg_count = 0;
		HC_Begin_Segment_Search("polyline");{
			HC_Show_Segment_Count(&polyline_seg_count);
		}HC_End_Segment_Search();
		
		if(polyline_seg_count){
			HC_Open_Segment("polyline");{
				HC_Begin_Segment_Search("*");{
					HC_Show_Segment_Count(&polyline_seg_count);
					CZLevel ** zlevels = new CZLevel*[polyline_seg_count];
					int zlevel_count = 0;
					char segment[1024*2];
					char * ptr;
					while(HC_Find_Segment(segment)){
						ptr = segment + strlen(segment);
						while(*(ptr-1) != '/') --ptr;
						if(!streq(ptr, "position"))
							zlevels[zlevel_count++] = new CZLevel(ptr);
					}
					qsort(zlevels, zlevel_count, sizeof(CZLevel*), CZLevelCompare);

					int i;
					for(i = 0; i < zlevel_count; ++i){
						HC_Open_Segment(zlevels[i]->GetZStr());{
							if(i / (float)(zlevel_count) < (1 - percent/100.0f) ){
								HC_Set_Visibility("off");
							} else {
								HC_Set_Visibility("on");
							}
						}HC_Close_Segment();
						delete zlevels[i];
					}
					delete [] zlevels;

				}HC_End_Segment_Search();
			}HC_Close_Segment();
			m_pHView->Update();
		}

	}HC_Close_Segment();
}

void CSolidHoopsView::OnBehaviorHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{	
	static int percentage = 0;
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
 	pBehaviorManager->ScheduleAllAnimations(true);
	switch(nSBCode)
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		
		pBehaviorManager->SetCurrentTickByPercentage((float)nPos);		
		break;
	case SB_RIGHT:
		pBehaviorManager->SetCurrentTickByPercentage((float)100);		
		break;
	case SB_LEFT:
		pBehaviorManager->SetCurrentTickByPercentage(0);		
		break;
	case SB_PAGELEFT:    // Scroll one page left.
		{  
			int curpos = max(0, (int)pBehaviorManager->GetCurrentTickByPercentage() - 20);
			pBehaviorManager->SetCurrentTickByPercentage((float)curpos);		
			
		}
		break;
	case SB_PAGERIGHT:    // Scroll one page left.
		{
			int curpos = min(100, (int)pBehaviorManager->GetCurrentTickByPercentage() + 20);
			pBehaviorManager->SetCurrentTickByPercentage((float)curpos);		
			
		}
		break;					
	}
 	pBehaviorManager->ExecuteAnimations(pBehaviorManager->GetCurrentTick(), 0);
	m_pHView->Update();
	UpdateBhvWindows(true);
	
}

void CSolidHoopsView::OnStepBack() 
{

	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
 	pBehaviorManager->ScheduleAllAnimations();

 	if (!CAppSettings::JumpToKeyframe)
		pBehaviorManager->SetCurrentTick(max(0, pBehaviorManager->GetCurrentTick()-1));	
	else
		pBehaviorManager->SetCurrentTick((float)pBehaviorManager->GetNextKeyframe((int)pBehaviorManager->GetCurrentTick(), false));
  	pBehaviorManager->ExecuteAnimations(pBehaviorManager->GetCurrentTick(), 0);
	m_pHView->Update();
	UpdateBhvWindows(true);
}

void CSolidHoopsView::OnStepForward() 
{

	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
 	pBehaviorManager->ScheduleAllAnimations();

 	if (!CAppSettings::JumpToKeyframe)
		pBehaviorManager->SetCurrentTick(pBehaviorManager->GetCurrentTick()+1);	
	else
 		pBehaviorManager->SetCurrentTick((float)pBehaviorManager->GetNextKeyframe((int)pBehaviorManager->GetCurrentTick(), true));

  	pBehaviorManager->ExecuteAnimations(pBehaviorManager->GetCurrentTick(), 0);
	m_pHView->Update();
	UpdateBhvWindows(true);
}

void CSolidHoopsView::UpdateBhvWindows(bool inv) 
{
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
		CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();
		frame->GetBhvToolbar()->m_wndBhvSlider.SetPos((int)pBehaviorManager->GetCurrentTickByPercentage());
		if (m_pDlgKeyframeEditor)
		{
			m_pDlgKeyframeEditor->UpdateButtonStates();
			m_pDlgKeyframeEditor->UpdateBhvState(inv);
		}

}


void CSolidHoopsView::SetSceneFont(CString csFontName, CString csFontSize, CString csFontUnits)
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());

		// first let's query the user's font size settings
		float size = atof(H_ASCII_TEXT(csFontSize));
		if(size<0) 
			size*=-1;

		char cfname[MVO_BUFFER_SIZE];
		sprintf (cfname, "name = \"%s\"", (const char *)H_ASCII_TEXT(csFontName));
		HC_Set_Text_Font(cfname);

		// set the font size via MVO - to propogate it to the hnet clients
		// hnet removed: do we still need to do this?
		char cfsize[MVO_BUFFER_SIZE];
		sprintf (cfsize, "%f %s", size, (const char *)H_ASCII_TEXT(csFontUnits));

		m_pHView->SetFontSize( cfsize, true );
 
	HC_Close_Segment();
}


void CSolidHoopsView::OnBehaviorContinuousPlay() 
{
	if (m_pHView->GetModel()->GetBhvBehaviorManager()->GetContinuousPlay())
		m_pHView->GetModel()->GetBhvBehaviorManager()->SetContinuousPlay(false);
	else
		m_pHView->GetModel()->GetBhvBehaviorManager()->SetContinuousPlay(true);

 	
}

void CSolidHoopsView::OnUpdateBehaviorContinuousPlay(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetModel()->GetBhvBehaviorManager()->GetContinuousPlay())
 		pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);

	if (m_pHView->GetModel()->GetBhvBehaviorManager()->HasAnimations())
         pCmdUI->Enable (1);	
	else
         pCmdUI->Enable (0);	
	
}

void CSolidHoopsView::OnUpdateStepForward(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetModel()->GetBhvBehaviorManager()->HasAnimations())
         pCmdUI->Enable (1);	
	else
         pCmdUI->Enable (0);		
}

void CSolidHoopsView::OnUpdateStepBack(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetModel()->GetBhvBehaviorManager()->HasAnimations())
         pCmdUI->Enable (1);	
	else
         pCmdUI->Enable (0);		
}

 

/*!
  Pops up dialog box to allow editing of material properties.
  The dialog box handles the rest.
*/
void CSolidHoopsView::OnMaterialProperties() 
{
    ShowStyleDialog(SW_SHOW);
}

void CSolidHoopsView::OnUpdateMaterialProperties(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (1);
}

void CSolidHoopsView::OnDisplayChanged(int xres, int yres, int depth)
{
	m_pHView->RebindView(0, H_ASCII_TEXT(CAppSettings::HoopsDriver), 0, (void *) m_hWnd, (void *)(HPALETTE)*(GetPalette()));
	return;
}


void CSolidHoopsView::OnCreateCuttingPlane2() 
{
	
	if (!m_pHView->GetCuttingPlanesExist("plane2"))
    {
		HC_KEY key = HUtilityGeometryCreation::CreateCuttingPlane(m_pHView,"plane2");
		HUtilityGeomHandle::SetupCuttingPlaneManipulator(key, m_pHView);
		m_pHView->Update();	
    }
    else
    {
		HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		HC_Open_Segment("plane2");
		HUtilityGeomHandle::ClearAllHandles(0);
		if (!(GetAsyncKeyState(VK_SHIFT) & 32768))
			HC_Flush_Contents ("...", "geometry");
		HC_Close_Segment();
		HC_Close_Segment();
		m_pHView->Update();
    }

    HUtilityGeometryCreation::AdjustCuttingPlaneRendering(m_pHView);

}

void CSolidHoopsView::OnUpdateCreateCuttingPlane2(CCmdUI* pCmdUI) 
{
	if(!CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	

	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetHandleOperator() && m_pHView->GetCuttingPlanesExist("plane2"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnCreateCuttingPlane3() 
{
	
	if (!m_pHView->GetCuttingPlanesExist("plane3"))
    {
		HC_KEY key = HUtilityGeometryCreation::CreateCuttingPlane(m_pHView,"plane3");
		HUtilityGeomHandle::SetupCuttingPlaneManipulator(key, m_pHView);
		m_pHView->Update();	
    }
    else
    {
		HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		HC_Open_Segment("plane3");
		HUtilityGeomHandle::ClearAllHandles(0);
		if (!(GetAsyncKeyState(VK_SHIFT) & 32768))
			HC_Flush_Contents ("...", "geometry");
		HC_Close_Segment();
		HC_Close_Segment();
		m_pHView->Update();
    }

    HUtilityGeometryCreation::AdjustCuttingPlaneRendering(m_pHView);

}

void CSolidHoopsView::OnUpdateCreateCuttingPlane3(CCmdUI* pCmdUI) 
{
	if(!CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);
	
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetHandleOperator() && m_pHView->GetCuttingPlanesExist("plane3"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnToolsSelect() 
{
	HSelectionSet* selection = m_pHView->GetSelection();
	if (!(GetAsyncKeyState(VK_SHIFT) & 32768) && !(GetAsyncKeyState(VK_CONTROL) & 32768))
	{
		selection->DeSelectAll();
		m_pHView->EmitDeSelectAllMessage();
	}
	
	if (GetAsyncKeyState(VK_CONTROL) & 32768)
		HUtility::SmartSelectUnderCursor(m_pHView, m_PositionOnRightClick.x, m_PositionOnRightClick.y, true, true);
	else
		HUtility::SmartSelectUnderCursor(m_pHView, m_PositionOnRightClick.x, m_PositionOnRightClick.y);
	m_pHView->Update();	
}

void CSolidHoopsView::OnToolsActivatemanipulator() 
{
	m_pHView->SetDynamicHighlighting(false);
    
	HC_KEY sel = HUtility::SelectUnderCursor(m_pHView, m_PositionOnRightClick.x, m_PositionOnRightClick.y, false);
    HUtility::UnwindIncludes(sel);

    sel = HUtility::GrabSegment(sel);    
	//    HUtilityGeomHandle::SetupManipulator(sel, m_pHView, false , false ,false);
    HLISTENER_EVENT(HObjectManipulationListener, m_pHView->GetEventManager(), SetupHandlesEvent(m_pHView, sel, false));
	
	
    m_pHView->Update();
	
}

void CSolidHoopsView::OnToolsActivatemanipulator2() 
{
	m_pHView->SetDynamicHighlighting(false);
	
	HC_KEY sel = HUtility::SelectUnderCursor(m_pHView, m_PositionOnRightClick.x, m_PositionOnRightClick.y, false);
    HUtility::UnwindIncludes(sel);

    sel = HUtility::GrabSegment(sel);    
    HLISTENER_EVENT(HObjectManipulationListener, m_pHView->GetEventManager(), SetupHandlesEvent(m_pHView, sel, true));
	
    m_pHView->Update();	
}

void CSolidHoopsView::OnToolsDeactivatemanipulator() 
{
    HC_KEY sel = HUtility::SelectUnderCursor(m_pHView, m_PositionOnRightClick.x, m_PositionOnRightClick.y, false);
    sel = HUtility::GrabSegment(sel);    
    HC_Open_Segment_By_Key(sel);
    HUtilityGeomHandle::ClearAllHandles(0);
    HC_Close_Segment();
    ((HSOpMoveHandle *)m_pHView->GetHandleOperator())->Reset();
    m_pHView->Update();	
	// TODO: Add your command handler code here
	
}

void CSolidHoopsView::OnToolsDeactivateallmanipulatos() 
{
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    HUtilityGeomHandle::ClearAllHandles(0);
    HC_Close_Segment();
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HUtilityGeomHandle::ClearAllHandles(0);
    HC_Close_Segment();
    ((HSOpMoveHandle *)m_pHView->GetHandleOperator())->Reset();
    m_pHView->Update();		
}

void CSolidHoopsView::OnToolsSnapshot() 
{
    HSubwindow subwindow;
	
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	
    HC_Open_Segment("subwindows");
    subwindow.Insert(m_PositionOnRightClick.x -0.3f, m_PositionOnRightClick.x + 0.3f, 
		m_PositionOnRightClick.y - 0.5f,m_PositionOnRightClick.y + 0.5f, SUBWINDOW_SNAPSHOT);
    HC_Close_Segment();
    HC_Close_Segment();
	
    subwindow.MakeCameraSnapshot(m_pHView);
    m_pHView->Update();
	
}

void CSolidHoopsView::OnToolsMagnifier() 
{
	HSubwindow subwindow;

	if (!m_pHView->GetHObjectManager()->GetHObject("subwindow"))
		m_pHView->GetHObjectManager()->AddHObject(new HSubwindow(m_pHView));
	
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	
    HC_Open_Segment("subwindows");
    subwindow.Insert(m_PositionOnRightClick.x -0.3f, m_PositionOnRightClick.x + 0.3f, 
		m_PositionOnRightClick.y - 0.5f,m_PositionOnRightClick.y + 0.5f, SUBWINDOW_MAGNIFIER);
    HC_Close_Segment();
    HC_Close_Segment();
	
    subwindow.MakeCameraSnapshot(m_pHView);
	m_pHView->Update();	
}

void CSolidHoopsView::OnToolsPointer() 
{
	HSubwindow subwindow;
	
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	
    HC_Open_Segment("subwindows");
    subwindow.Insert(m_PositionOnRightClick.x -0.3f, m_PositionOnRightClick.x + 0.3f, 
		m_PositionOnRightClick.y - 0.5f,m_PositionOnRightClick.y + 0.5f, SUBWINDOW_POINTER);
    HC_Close_Segment();
    HC_Close_Segment();
	
    subwindow.MakeCameraSnapshot(m_pHView);
	m_pHView->Update();		
}

void CSolidHoopsView::OnToolsSubwindowSyncFromCamera() 
{
    HSubwindow subwindow;
    bool pointerselected;
    if (subwindow.FindSubwindow(m_pHView, m_PositionOnRightClick, pointerselected))    
    {    
		subwindow.MakeCameraSnapshot(m_pHView);
		
    }
	
}

void CSolidHoopsView::OnToolsSubwindowSynctocamera() 
{
    HSubwindow subwindow;
    bool pointerselected;
    if (subwindow.FindSubwindow(m_pHView, m_PositionOnRightClick, pointerselected))    
    {   
		HCamera old_camera, new_camera;
		m_pHView->GetCamera(&old_camera);
		subwindow.SyncViewToWindow(m_pHView);	
		HUtility::ReadjustTarget(m_pHView);	   
		m_pHView->GetCamera(&new_camera);
		HC_Open_Segment_By_Key(GetSceneKey());
		HUtility::SmoothTransition(old_camera, new_camera,m_pHView);
		HC_Close_Segment();
		
    }
	
}

void CSolidHoopsView::OnToolsSubwindowFreeze() 
{
	HSubwindow subwindow;
    bool pointerselected;
    if (subwindow.FindSubwindow(m_pHView, m_PositionOnRightClick, pointerselected))    
    {    
		subwindow.ChangeType(subwindow.GetType(),0);
    }	
}

void CSolidHoopsView::OnToolsSubwindowUnfreeze() 
{
	HSubwindow subwindow;
    bool pointerselected;
    if (subwindow.FindSubwindow(m_pHView, m_PositionOnRightClick, pointerselected))    
    {    
		subwindow.ChangeType(subwindow.GetType());
    }		
}

void CSolidHoopsView::OnToolsLightsInsertlocallight() 
{
    HPoint t;
    HPoint np = m_PositionOnRightClick;
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HC_Show_Net_Camera_Target(&t.x, &t.y, &t.z);
    HC_Compute_Coordinates(".", "world", &t, "viewpoint", &t);
    HC_Compute_Coordinates(".", "local window", &np, "viewpoint", &np);
    np.z = t.z;
    HC_Compute_Coordinates(".", "viewpoint", &np, "world", &np);
    HC_Close_Segment();
	
    
	
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    HC_Open_Segment("lights");
    HLightsObject::InsertLocalLight(m_pHView, np);
    HC_Close_Segment();
    HC_Close_Segment();
    m_pHView->Update();
    
	
}

void CSolidHoopsView::OnToolsLightsInsertdistantlight() 
{
    HPoint t;
    HPoint np = m_PositionOnRightClick;
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HC_Show_Net_Camera_Target(&t.x, &t.y, &t.z);
    HC_Compute_Coordinates(".", "world", &t, "viewpoint", &t);
    HC_Compute_Coordinates(".", "local window", &np, "viewpoint", &np);
    np.z = t.z;
    HC_Compute_Coordinates(".", "viewpoint", &np, "world", &np);
    HC_Close_Segment();
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    HC_Open_Segment("lights");
    HLightsObject::InsertDistantLight(m_pHView, np);
    HC_Close_Segment();
    HC_Close_Segment();
    m_pHView->Update();
	
}

void CSolidHoopsView::OnToolsLightsInsertspotlight() 
{
    HPoint t;
    HPoint np = m_PositionOnRightClick;
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HC_Show_Net_Camera_Target(&t.x, &t.y, &t.z);
    HC_Compute_Coordinates(".", "world", &t, "viewpoint", &t);
    HC_Compute_Coordinates(".", "local window", &np, "viewpoint", &np);
    np.z = t.z;
    HC_Compute_Coordinates(".", "viewpoint", &np, "world", &np);
    HC_Close_Segment();
	
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    HC_Open_Segment("lights");
    HLightsObject::InsertSpotLight(m_pHView, np);
    HC_Close_Segment();
    HC_Close_Segment();
    m_pHView->Update();
	
}

void CSolidHoopsView::OnToolsManipulatorActivateparent() 
{
	
	HC_KEY sel = HUtility::SelectUnderCursor(m_pHView, m_PositionOnRightClick.x, m_PositionOnRightClick.y, false);
    sel = HUtility::GrabSegment(sel);    
    sel = HUtility::UserOptionExists(sel,"hashandles",0);
	
    HC_Open_Segment_By_Key(sel);
    HUtilityGeomHandle::ClearAllHandles(0);
    HC_Close_Segment();
    sel = HC_KShow_Owner_By_Key(sel);
    HLISTENER_EVENT(HObjectManipulationListener, m_pHView->GetEventManager(), SetupHandlesEvent(m_pHView, sel, false));
	
}

void CSolidHoopsView::OnToolsManipulatorCombineselected() 
{
	int	numSolidSelections, numHoopsSelections;
	HSSelectionSet* selection = 0;
	
	selection = (HSSelectionSet *)m_pHView->GetSelection();
	
	numHoopsSelections = selection->GetSize();
	numSolidSelections = selection->GetSolidListSize();
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	HC_KEY tempkey = HC_KCreate_Segment("");
	HC_Close_Segment();
	
 	for (int i=0;i<(int)selection->GetSize();i++)
		HUtility::MoveToTemp(selection->GetAt(i),tempkey);
    
	HLISTENER_EVENT(HObjectManipulationListener, m_pHView->GetEventManager(), SetupHandlesEvent(m_pHView, tempkey, false));
	
}

void CSolidHoopsView::OnViewCameraNearLimit() 
{
	CameraNearLimitDlg cnl_dlg(m_pHView);
	cnl_dlg.DoModal();
}

void CSolidHoopsView::OnToolsDeleteEntity() 
{  
    if (m_KeyUnderCursor != INVALID_KEY)
    {
		HC_KEY key; 
		key = HObjectManager::FindHObjectSegment(m_KeyUnderCursor);
		if(key == INVALID_KEY){
			key = HUtility::GrabSegment(m_KeyUnderCursor);
		}
		char status[32];
		HC_Show_Key_Status(key, status);
		if(!streq(status, "invalid")){
			HSelectionSet * selset = m_pHView->GetSelection();
			selset->DeSelect(key);
			char type[32];
			HC_Show_Key_Type(key, type);
			if(streq(type, "shell")){
				int low, high;
				HC_Show_Region_Range(key, &low, &high);
				for(; low < high; ++low){
					selset->DeSelectRegion(key, low, true);
				}
			}
			
				HC_Open_Segment_By_Key(	HUtility::GrabSegment(key));
				HUtilityGeomHandle::ClearAllHandles(0);
				HLISTENER_EVENT(HObjectManipulationListener, m_pHView->GetEventManager(), SetupHandlesEvent(m_pHView, -1, false));
				HC_Close_Segment();
		
			HC_Delete_By_Key(key);
			m_pHView->SetShadowRegenerationMode(true);
			m_pHView->Update();
		}
    }    
	m_pHView->Update();
}


void CSolidHoopsView::OnToolsSetNoteText() 
{
    if (m_KeyUnderCursor != -1)
    {
		HUtilityAnnotation note;
		note.SetNote(m_KeyUnderCursor, m_pHView);
		CTextInput textinput;
		textinput.m_InfoText = _T("Note Text:");
		if (textinput.DoModal() == IDOK)
		{
#ifdef _UNICODE
			note.SetTextWithEncoding((const unsigned short*)(const wchar_t*)H_UNICODE_TEXT(textinput.m_TextField));
#else
			note.SetText(sel, textinput.m_TextField);
#endif
			note.Resize(m_pHView->GetIncludeLinkKey(), m_pHView->GetViewKey());
			m_pHView->Update();
		}
    }
}

void CSolidHoopsView::OnToolsLightsLightGeometryOff() 
{
    HLightsObject::TurnLightsOnOff(m_pHView,false);
	
}

void CSolidHoopsView::OnToolsLightsLightGeometryOn() 
{
    HLightsObject::TurnLightsOnOff(m_pHView,true);
	
}

void CSolidHoopsView::OnToolsVisibilityMarkersOnly()
{

#ifdef HOOPS_ONLY
	HSolidView * pHView = (HSolidView*) GetHoopsView();
	assert(pHView);
	pHView->SetVisibilityMarkersOnly(!pHView->GetVisibilityMarkersOnly());
    
	HSelectionSet * selection=pHView->GetSelection();
	if(selection)
		selection->UpdateHighlighting();

	pHView->Update();


#endif
 

}

void CSolidHoopsView::OnUpdateToolsVisibilityMarkersOnly(CCmdUI* pCmdUI)
{
 
#ifdef	HOOPS_ONLY
    if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		GetSolidView()->GetVisibilityMarkersOnly())
        pCmdUI->SetCheck (1);
    else
        pCmdUI->SetCheck (0);	
#endif
}


void CSolidHoopsView::OnPolygonSelect() 
{
	LocalSetOperator(new HOpSelectPolygon(m_pHView));
}


void CSolidHoopsView::OnUpdatePolygonSelect(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpSelectPolygon"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnPolylineSelect() 
{
	LocalSetOperator(new HOpSelectPolyline(m_pHView));
}


void CSolidHoopsView::OnUpdatePolylineSelect(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		streq(m_pHView->GetOperator()->GetName(), "HOpSelectPolyline"))
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}
W3D_Image::~W3D_Image() {
    delete [] m_name;
}


// based on the format

TK_Status W3D_Image::Write (BStreamFileToolkit & tk) alter {
#ifndef BSTREAM_READONLY
    TK_Status       status = TK_Normal;

    switch (m_stage) {
        case 0: {
            if ((status = PutOpcode (tk)) != TK_Normal)
                return status;
            m_stage++;
        }   //nobreak;

        case 1: {

            if (m_name_length > 0) {
                unsigned char       byte = (unsigned char)m_name_length;
                // need handling for string > 255 ?
                if ((status = PutData (tk, byte)) != TK_Normal)
                    return status;
            }
            m_stage++;
        }   //nobreak;

        case 2: {
            if (m_name_length > 0) {
                if ((status = PutData (tk, m_name, m_name_length)) != TK_Normal)
                    return status;
            }
            m_stage++;
        }   //nobreak;

        case 3:
        {
            if ((status = PutData(tk, m_size[0])) != TK_Normal)
                return status;
            if ((status = PutData(tk, m_size[1])) != TK_Normal)
                return status;
            if ((status = PutData(tk, m_bpp)) != TK_Normal)
                return status;
            m_stage++;
            //nobreak;
        }

        case 4: {
            if (Tagging (tk))
                status = Tag (tk);

            m_stage = -1;
        }   break;

        default:
            return tk.Error();
    }

    return status;
#else
    return tk.Error (stream_readonly);
#endif
}


TK_Status W3D_Image::Read (BStreamFileToolkit & tk) alter {
    TK_Status       status = TK_Normal;

    switch (m_stage) {

        case 0: {
                unsigned char       byte;
                if ((status = GetData (tk, byte)) != TK_Normal)
                    return status;
                set_name ((int)byte);

            m_stage++;
        }   //nobreak;

        case 1: {

            if (m_name_length > 0) {
                if ((status = GetData (tk, m_name, m_name_length)) != TK_Normal)
                    return status;
            }
            m_stage++;
        }   //nobreak;

        case 2:
        {
            if ((status = GetData(tk, m_size[0])) != TK_Normal)
                return status;
            if ((status = GetData(tk, m_size[1])) != TK_Normal)
                return status;
            if ((status = GetData(tk, m_bpp)) != TK_Normal)
                return status;
            m_stage=-1;
            break;
        }

        default:
            return tk.Error();
    }

    return status;
}


TK_Status   W3D_Image::Execute (BStreamFileToolkit & tk) alter
{
    //char            format[MVO_BUFFER_SIZE];
//    int             w     = m_size[0];
  //  int             h     = m_size[1];

    {
		/*
        m_bpp = 32; // force RGBA format
        RGBA * image = _createRGBACheckerBoardImage(w,h);
        sprintf(format, "%s, local, name = %s", "rgba", m_name);

		HC_Open_Segment_By_Key(m_scene->GetTextureLibrary());
            HC_KEY imageKey = HC_KInsert_Image(0.0,0.0,0.0,format,w,h,image);
        HC_Close_Segment();
        delete image;
        m_scene->GetImageRefMap().Insert(m_name, new ImageRef(imageKey,w,h,m_bpp));
		*/
    }

	return TK_Normal;
}

void W3D_Image::Reset (void) alter {

    delete [] m_name;
    m_name = 0;

    BBaseOpcodeHandler::Reset();
}

void W3D_Image::set_name (int length) alter {
    m_name_length = length;
    delete [] m_name;
    m_name = new char [m_name_length + 1];
    m_name[m_name_length] = '\0';
}

void W3D_Image::set_name (char const * name) alter {
    if( name != 0 ) {
        set_name ((int) strlen (name));
        strcpy (m_name, name);
    }
    else {
        delete [] m_name;
        m_name = 0;
        m_name_length = 0;
    }
}



void CSolidHoopsView::OnCreateCreatetwosidedsection() 
{
	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!HUtility::SegmentExists("twosection"))
			HUtilityGeometryCreation::CreateTwoSidedSection(m_pHView);
		else
			HC_Delete_Segment("twosection");
	HC_Close_Segment();
	m_pHView->Update();
	
}


void CSolidHoopsView::OnUpdateCreateCreatetwosidedsection(CCmdUI* pCmdUI) 
{
	if(!CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	

	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!m_pHView->GetViewActive() || !m_pHView->GetModel()->GetFileLoadComplete() ||
			!HUtility::SegmentExists("twosection"))
			pCmdUI->SetCheck (0);
		else
			pCmdUI->SetCheck (1);
	HC_Close_Segment();
	// TODO: Add your command update UI handler code here
	
}

void CSolidHoopsView::OnCreateCreateSlice() 
{
	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!HUtility::SegmentExists("slice"))
			HUtilityGeometryCreation::CreateSlice(m_pHView);
		else
			HC_Delete_Segment("slice");
	HC_Close_Segment();
	m_pHView->Update();
	
}


void CSolidHoopsView::OnUpdateCreateCreateSlice(CCmdUI* pCmdUI) 
{
	if(!CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	

	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!m_pHView->GetViewActive() || !m_pHView->GetModel()->GetFileLoadComplete() ||
			!HUtility::SegmentExists("slice"))
		pCmdUI->SetCheck (0);
    else
        pCmdUI->SetCheck (1);
	HC_Close_Segment();
	// TODO: Add your command update UI handler code here
	
}


void CSolidHoopsView::OnCreateCreatethreesidedsection() 
{
	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!HUtility::SegmentExists("threesection"))
			HUtilityGeometryCreation::CreateThreeSidedSection(m_pHView);
		else
			HC_Delete_Segment("threesection");
	HC_Close_Segment();
	m_pHView->Update();
	
}

void CSolidHoopsView::OnUpdateCreateCreatethreesidedsection(CCmdUI* pCmdUI) 
{
	if(!CAppSettings::DisableEditing)
        pCmdUI->Enable (1);
    else
        pCmdUI->Enable (0);	

	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!m_pHView->GetViewActive() || !m_pHView->GetModel()->GetFileLoadComplete() ||
			!HUtility::SegmentExists("threesection"))
		pCmdUI->SetCheck (0);
    else
        pCmdUI->SetCheck (1);
	HC_Close_Segment();
	
}

void CSolidHoopsView::SetTransparency()
{
	char text[4096];
	char style[4096];
	char sorting[4096];
	char layers[4096];
	bool fast_z_sort=false;

	strcpy(style, H_ASCII_TEXT(CAppSettings::TransparencyStyle));
	strcpy(sorting, H_ASCII_TEXT(CAppSettings::TransparencySorting));
	strcpy(layers, H_ASCII_TEXT(CAppSettings::TransparencyDepthPeelingLayers));
	
	if(strstr(sorting, "z-sort"))
	{
		if(strstr(sorting, "fast"))
			fast_z_sort=true;
		sprintf(sorting, "z-sort only");
	}

 	sprintf(text,"style = %s, hsr algorithm = %s,depth peeling options=(layers= %s), depth writing = %s",
		style, sorting, layers, CAppSettings::DepthWriting == TRUE ? "on" : "off");
	m_pHView->SetTransparency(text, fast_z_sort);
	
}

void CSolidHoopsView::SetViewAxis()
{

	char text[4096];
	HVector front, top;
 	strcpy(text, H_ASCII_TEXT(CAppSettings::ViewAxis));
	sscanf(text, "%f %f %f %f %f %f", &front.x, &front.y, &front.z,
		&top.x, &top.y, &top.z);
	m_pHView->SetViewAxis(&front,  &top);
 	
}

void CSolidHoopsView::OnSelectionClosestdistance() 
{

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
	HC_Open_Segment("distanceline");
	HC_Flush_Contents(".", "everything");
	HC_Close_Segment();
	HC_Close_Segment();

	HSelectionSet* selection = m_pHView->GetSelection();

	char type[4096];
	float matrix[16];
	int size = selection->GetSize();
 	HC_KEY shellkey2, shellowner2 = -1;
	char selectability1[MVO_BUFFER_SIZE];
	strcpy(selectability1,"");
	char selectability2[MVO_BUFFER_SIZE];
	strcpy(selectability2,"");

	if (size && size <=2)
	{
		HC_KEY shellkey = selection->GetAt(0);
		HC_Show_Key_Type(shellkey, type);
		if (strcmp(type,"shell") != 0)
		{
			AfxMessageBox(_T("Distance can be calculated for shells only (use entity selection)"));
			return;
		}
		if (size == 2)
		{		
			HC_Show_Key_Type(selection->GetAt(1), type);
		
			if (strcmp(type,"shell") != 0)
			{
				AfxMessageBox(_T("Distance can be calculated for shells only (use entity selection)"));
				return;
			}
		}
		HSelectionItem *item0 = (HSelectionItem *)selection->GetSelectionItemAt(0);

		HC_Show_Key_Type(shellkey, type);
		if (strcmp(type, "shell") == 0)
		{
			HC_KEY shellowner = HC_KShow_Owner_By_Key(shellkey);
			  
			if (!selection->GetReferenceSelection() && item0->GetIncludeCount()>1)
			{
				const HC_KEY * includekeys = item0->GetIncludeKeys();
				shellowner = HC_KShow_Owner_By_Key(includekeys[1]);
			}
 				
  
			HC_Open_Segment_By_Key(shellowner);
			HC_Show_Net_Modelling_Matrix(matrix);
 			HC_Close_Segment();

			HC_Open_Segment_By_Key(shellowner);
			if (HC_Show_Existence("selectability"))
				HC_Show_Selectability(selectability1);
			HC_Set_Selectability("off");
			HC_Close_Segment();
 			int pcount,fcount;
 			HC_Show_Shell_Size(shellkey, &pcount, &fcount);
			HPoint *plist = new HPoint[pcount];
			int *flist = new int[fcount];
			HC_Show_Shell(shellkey, &pcount, plist, &fcount, flist);
 			HC_Compute_Transformed_Points(pcount, plist, matrix, plist);

			
			if (size == 2)
			{
				HSelectionItem *item1 = (HSelectionItem *)selection->GetSelectionItemAt(1);

				HC_Open_Segment_By_Key(m_pHView->GetOverwriteKey());
				HC_Set_Selectability("off");
					HC_Set_Rendering_Options("attribute lock = selectability");
				HC_Close_Segment();
				shellkey2 = selection->GetAt(1);
				
				if (!selection->GetReferenceSelection())
				{				
					shellowner2 = HC_KShow_Owner_By_Key(HC_KShow_Owner_By_Key(shellkey2));	
			
					if (item1->GetIncludeCount()>1)
					{
						const HC_KEY * includekeys = item1->GetIncludeKeys();
						shellowner2 = HC_KShow_Owner_By_Key(includekeys[1]);
						HC_Show_Segment(shellowner2, type);
					}
				}
				else
					shellowner2 = HC_KShow_Owner_By_Key(shellkey2);	

				HC_Open_Segment_By_Key(shellowner2);
				if (HC_Show_Existence("selectability"))
					HC_Show_Selectability(selectability2);
				HC_Set_Selectability("faces = on");
				HC_Set_Rendering_Options("attribute lock = selectability");
				HC_Close_Segment();
			 
  						
			}
			HC_Open_Segment_By_Key(m_pHView->GetViewKey());
			float res = HC_Compute_Selection_Distance_By_Shell("v", ".", pcount, plist, fcount, flist, "");
			HC_Close_Segment();
			delete [] plist;
			delete [] flist;			
			float d;
			int o;
			HPoint p1,p2;
			if (res < 0)
			{
				AfxMessageBox(_T("Could not calculate distance"));
				return;
			}
			HC_Show_Selection_Position(&d, &d, &d, &p1.x, &p1.y, &p1.z);
			HC_Show_Selection_Source_Element(&o, &o, &o, &p2);
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
			HC_Open_Segment("distanceline");
			HC_Set_Color("lines = (diffuse = blue), markers = light blue");
			HC_Insert_Marker(p1.x, p1.y,p1.z);
			HC_Insert_Marker(p2.x, p2.y,p2.z);
			HC_Insert_Line(p1.x,p1.y,p1.z, p2.x, p2.y, p2.z);
			HC_Set_Visibility("lines = on, markers = on");
			HC_Close_Segment();
			HC_Close_Segment();
			HC_Open_Segment_By_Key(shellowner);
			HC_UnSet_Selectability();
			if (strcmp(selectability1,"") != 0)
				HC_Set_Selectability(selectability1);
 			HC_Close_Segment();
			if (size == 2)
			{
				HC_Open_Segment_By_Key(shellowner2);
				HC_UnSet_Selectability();
				HC_UnSet_One_Rendering_Option("attribute lock = selectability");
				if (strcmp(selectability2,"") != 0)
				HC_Set_Selectability(selectability2);
 				HC_Close_Segment();
				HC_Open_Segment_By_Key(m_pHView->GetOverwriteKey());
				HC_Flush_Contents(".", "attributes");
				HC_Close_Segment();
			}
			m_pHView->Update();
		}
	}
	else
	{
		if (size == 0)
			AfxMessageBox(_T("Select one or two shells to calculate closest distance"));
		else if (size >2 )
			AfxMessageBox(_T("Too many items selected"));
	}


	
}



void CSolidHoopsView::OnUndo()
{
	m_pHView->GetUndoManager()->Undo();
}

void CSolidHoopsView::OnUpdateUndo(CCmdUI* pCmdUI)
{
	if(m_pHView->GetUndoManager()->Undo(1,true) == 0)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

}


void CSolidHoopsView::OnRedo()
{
	m_pHView->GetUndoManager()->Redo();
}

void CSolidHoopsView::OnUpdateRedo(CCmdUI* pCmdUI)
{
	if(m_pHView->GetUndoManager()->Redo(1,true) == 0)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

}


void CSolidHoopsView::OnHome()
{
	HUndoManager *umanager = m_pHView->GetUndoManager();
	umanager->Reset(m_pHView);
}

void CSolidHoopsView::OnUpdateHome(CCmdUI* pCmdUI)
{
	if(m_pHView->GetUndoManager()->Undo(1,true) == 0)
		pCmdUI->Enable (0);
	else
		pCmdUI->Enable (1);

}

void CSolidHoopsView::OnVerticalCAEToggleLegend()
{
	bool vis = Verticals::CAE::LegendVisibility(m_pHView);
	Verticals::CAE::LegendVisibility(m_pHView, !vis);
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateVerticalCAEToggleLegend(CCmdUI* pCmdUI)
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		Verticals::CAE::LegendVisibility(m_pHView))
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck (0);
}

#include "HBhvAnimation.h"

void CSolidHoopsView::Verticals::CMM::EnableCollision(HBaseView * const m_pHView, bool const onoff)
{
	((HSolidView*const)m_pHView)->SetShowCollisions(onoff);
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	vlist_s * pAnimList = pBehaviorManager->GetAnimationList();
	START_LIST_ITERATION(HBhvAnimation, pAnimList)
		HBhvTargetObject *tob = temp->GetTarget();
		tob->SetCollision(onoff);
  	END_LIST_ITERATION(pAnimList)
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());{
		HC_Open_Segment("CMMDisplay");{
			if(onoff){
				/* I'm not checking for visibility, so unconditionally set it before unsetting it. */
				HC_Set_Visibility("off");
				HC_UnSet_Visibility();
			} else {
				HC_Set_Visibility("off");
			}
		}HC_Close_Segment();
	}HC_Close_Segment();
	m_pHView->Update();
}

bool CSolidHoopsView::Verticals::CMM::EnableCollision(HBaseView * const m_pHView)
{
	static bool retval = ((HSolidView*const)m_pHView)->GetShowCollisions();
	return retval;
}

void CSolidHoopsView::Verticals::CMM::DisplayVisibility(HBaseView * const m_pHView, bool const onoff)
{
}

bool CSolidHoopsView::Verticals::CMM::DisplayVisibility(HBaseView * const m_pHView)
{
	static bool retval = false;
	//retval = !retval;
	return retval;
}

void CSolidHoopsView::Verticals::CMM::PositionVisibility(HBaseView * const m_pHView, bool const onoff)
{
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());{
		int polyline_seg_count = 0;
		HC_Begin_Segment_Search("polyline");{
			HC_Show_Segment_Count(&polyline_seg_count);
		}HC_End_Segment_Search();

		if(polyline_seg_count){
			HC_Open_Segment("polyline/position");{
				if(onoff){
					HC_Set_Visibility("on");
				}
				else {
					HC_Set_Visibility("off");
				}
			}HC_Close_Segment();
		}
	}HC_Close_Segment();
}

bool CSolidHoopsView::Verticals::CMM::PositionVisibility(HBaseView * const m_pHView)
{
	bool retval = false;
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());{
		int polyline_seg_count = 0;
		HC_Begin_Segment_Search("polyline");{
			HC_Show_Segment_Count(&polyline_seg_count);
		}HC_End_Segment_Search();

		if(polyline_seg_count){
			HC_Open_Segment("polyline/position");{
				char onoff[128] = {""};
				HC_Show_One_Net_Visibility("lines", onoff);
				if(strstr(onoff, "on")){
					retval = true;
				}
			}HC_Close_Segment();
		}
	}HC_Close_Segment();
	return retval;
}

void CSolidHoopsView::OnVerticalCMMToggleCollision()
{
	static bool retval = false;
	retval = !retval;
	Verticals::CMM::EnableCollision(m_pHView, retval);
}

void CSolidHoopsView::OnUpdateVerticalCMMToggleCollision(CCmdUI* pCmdUI)
{
	if(m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		Verticals::CMM::EnableCollision(m_pHView))
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnVerticalCMMToggleVisibility()
{
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());{

		int polyline_seg_count = 0;
		HC_Begin_Segment_Search("polyline");{
			HC_Show_Segment_Count(&polyline_seg_count);
		}HC_End_Segment_Search();
		
		if(polyline_seg_count){
			HC_Open_Segment("polyline");{
				HC_Begin_Segment_Search("*");{
					HC_Show_Segment_Count(&polyline_seg_count);
					CZLevel ** zlevels = new CZLevel*[polyline_seg_count];
					int zlevel_count = 0;
					char segment[1024*2];
					char * ptr;
					while(HC_Find_Segment(segment)){
						ptr = segment + strlen(segment);
						while(*(ptr-1) != '/') --ptr;
						if(!streq(ptr, "position"))
							zlevels[zlevel_count++] = new CZLevel(ptr);
					}
					qsort(zlevels, zlevel_count, sizeof(CZLevel*), CZLevelCompare);

					bool onoff = false;
					HC_Open_Segment(zlevels[0]->GetZStr());{
						char vis[32] = {""};
						HC_Show_One_Net_Visibility("polyline", vis);
						if(streq(vis, "on")){
							onoff = true;
						}
					}HC_Close_Segment();
					int i;
					for(i = 0; i < zlevel_count; ++i){
						HC_Open_Segment(zlevels[i]->GetZStr());{
							HC_Set_Visibility(onoff ? "off" : "on");
						}HC_Close_Segment();
						delete zlevels[i];
					}
					delete [] zlevels;

				}HC_End_Segment_Search();
			}HC_Close_Segment();
			m_pHView->Update();
		}

	}HC_Close_Segment();
}

void CSolidHoopsView::OnUpdateVerticalCMMToggleVisibility(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnVerticalCMMHidePositions()
{
	Verticals::CMM::PositionVisibility(m_pHView, !Verticals::CMM::PositionVisibility(m_pHView));
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateVerticalCMMHidePositions(CCmdUI* pCmdUI)
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		Verticals::CMM::PositionVisibility(m_pHView))
		pCmdUI->SetCheck(0);
	else
		pCmdUI->SetCheck (1);
}

void CSolidHoopsView::OnUpdateVerticalCAEColorIndex(CCmdUI* pCmdUI)
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		Verticals::CAE::IndexInterpolation(m_pHView))
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck (0);

}

void CSolidHoopsView::OnUpdateVerticalCAEColorInterpolation(CCmdUI* pCmdUI)
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		Verticals::CAE::ColorInterpolation(m_pHView))
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck (0);

}

void CSolidHoopsView::OnUpdateVerticalCAEIsolines(CCmdUI* pCmdUI)
{
	if( m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		Verticals::CAE::IsolineInterpolation(m_pHView))
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck (0);

}
void CSolidHoopsView::OnVerticalCAEMapData()
{
	Verticals::CAE::MapSelectionSet(m_pHView);
	m_pHView->Update();
}

void CSolidHoopsView::OnVerticalCAEColorIndex()
{
	bool color_indexing = Verticals::CAE::IndexInterpolation(m_pHView);
	Verticals::CAE::IndexInterpolation(m_pHView, !color_indexing);
	m_pHView->Update();
}

void CSolidHoopsView::Verticals::CAE::IndexInterpolation(HBaseView * view, bool onoff)
{
	HC_Open_Segment_By_Key(view->GetSceneKey());{
		if(onoff){
			HC_Set_Rendering_Options("color index interpolation = on");
		}
		else{
			HC_Set_Rendering_Options("no color index interpolation");
		}
	}HC_Close_Segment();
}

bool CSolidHoopsView::Verticals::CAE::IndexInterpolation(HBaseView * view)
{
	bool retval = false;
	HC_Open_Segment_By_Key(view->GetSceneKey());{
		char options[128] = {""};
		HC_Show_One_Net_Rendering_Option("color index interpolation", options);
		if(!strstr(options, "isolines") && strstr(options, "on")){
			retval = true;
		}
	}HC_Close_Segment();
	return retval;
}

void CSolidHoopsView::OnVerticalCAEColorInterpolation()
{
	bool cii = Verticals::CAE::ColorInterpolation(m_pHView);
	Verticals::CAE::ColorInterpolation(m_pHView, !cii);
	m_pHView->Update();
}

void CSolidHoopsView::Verticals::CAE::ColorInterpolation(HBaseView * view, bool onoff)
{
	HC_Open_Segment_By_Key(view->GetSceneKey());{
		if (onoff){
			HC_Set_Rendering_Options("color interpolation = on");
		}
		else{
			HC_Set_Rendering_Options("no color interpolation");
		}
	}HC_Close_Segment();	
}

bool CSolidHoopsView::Verticals::CAE::ColorInterpolation(HBaseView * view)
{
	bool retval = true;
	HC_Open_Segment_By_Key(view->GetSceneKey());{
		char options[128] = {""};
		HC_Show_One_Net_Rendering_Option("color interpolation", options);
		if(strstr(options, "isoline") || !strstr(options, "on")){
			retval = false;
		}
	}HC_Close_Segment();	
	return retval;
}

void CSolidHoopsView::OnVerticalCAEIsolines()
{
	bool isolines = Verticals::CAE::IsolineInterpolation(m_pHView);
	Verticals::CAE::IsolineInterpolation(m_pHView, !isolines);
	m_pHView->Update();
}

bool CSolidHoopsView::Verticals::CAE::IsolineInterpolation(HBaseView * view)
{
	bool retval = false;
	HC_Open_Segment_By_Key(view->GetSceneKey());{
		char options[128] = {""};
		HC_Show_One_Net_Rendering_Option("isoline options=visibility", options);
		if(strstr(options, "on")){
			retval = true;
		}
	}HC_Close_Segment();	

	return retval;
}

void CSolidHoopsView::Verticals::CAE::IsolineInterpolation(HBaseView * view, bool onoff)
{
	HC_Open_Segment_By_Key(view->GetSceneKey());{
		if(onoff){
			HC_Set_Rendering_Options ("contour options=no visibility");
			HC_Set_Rendering_Options ("isoline options=visibility");
		}
		else{
			HC_Set_Rendering_Options ("contour options=visibility");
			HC_Set_Rendering_Options ("isoline options=no visibility");
		}
	}HC_Close_Segment();
}


void CSolidHoopsView::OnVerticalCAEQuadInterpolation()
{
	Verticals::CAE::QuadInterpolateSelectionSet(m_pHView);
	m_pHView->Update();
}

#ifdef WINDOWS_SYSTEM
#include <windows.h>
#define USleep Sleep
#else
#include <unistd.h>
#define USleep usleep
#endif

#ifdef HOOPS_ONLY

static void boolean_common(int bool_type, HBaseView* view)
{
	HSelectionSet* selection = view->GetSelection();

	char type1[4096], type2[MVO_BUFFER_SIZE];
	int size = selection->GetSize();
 	HC_KEY tool, target;

	if (size && size ==2)
	{
		bool sort = selection->GetSortSelectionList();
		selection->SetSortSelectionList(true);

		target = selection->GetAt(0);
		tool = selection->GetAt(1);
		selection->SetSortSelectionList(sort);

		HC_Show_Key_Type(target, type1);
		HC_Show_Key_Type(tool, type2);

		if (!streq(type1, "shell") || !streq(type2, "shell"))
		{
			AfxMessageBox(_T("Boolean can be calculated for shells only (use entity selection)"));
			return;
		}
		
		HUtilityGeometryCreation::CreateBoolean(target, tool, bool_type);
		
		//clean up the old geometry
		selection->DeSelectAll();
		view->EmitDeSelectAllMessage();

		HC_KEY seg1, seg2;
		char first_seg_name[MVO_BUFFER_SIZE], second_seg_name[MVO_BUFFER_SIZE], 
			temp_seg_name[MVO_BUFFER_SIZE];
		int content_count;

		seg1=HC_KShow_Owner_Original_Key(target);
		seg2=HC_KShow_Owner_Original_Key(tool);
		HC_Show_Segment(seg1, first_seg_name);
		HC_Show_Segment(seg2, second_seg_name);

		//remove the original geometry
		HC_Delete_By_Key(tool);
		HC_Delete_By_Key(target);

		//delete empty segments, don't delete the model segment under any circumstances
		do
		{
			HC_Begin_Contents_Search(first_seg_name, "geometry, segments, includes");
			HC_Show_Contents_Count(&content_count);
			HC_End_Contents_Search();
			if(!content_count)
			{
				HC_Show_Owner(first_seg_name, temp_seg_name);
				HC_Delete_Segment(first_seg_name);
				strcpy(first_seg_name, temp_seg_name);
			}
		} while(!content_count && view->GetModelKey()!=HC_KCreate_Segment(first_seg_name));
		

		do
		{
			HC_Begin_Contents_Search(second_seg_name, "geometry, segments, includes");
			HC_Show_Contents_Count(&content_count);
			HC_End_Contents_Search();
			if(!content_count)
			{
				HC_Show_Owner(second_seg_name, temp_seg_name);
				HC_Delete_Segment(second_seg_name);
				strcpy(second_seg_name, temp_seg_name);
			}
		} while(!content_count && view->GetModelKey()!=HC_KCreate_Segment(second_seg_name));

		view->Update();

	}
	else
	{
		if (size == 0)
			AfxMessageBox(_T("Select one or two shells to calculate boolean"));
		else if (size >2 )
			AfxMessageBox(_T("Too many items selected"));
	}
}


void CSolidHoopsView::OnBooleantypeIntersection()
{
	boolean_common(BOOLEAN_TYPE_INTERSECT, m_pHView);
}


void CSolidHoopsView::OnBooleantypeSubtract()
{
	boolean_common(BOOLEAN_TYPE_SUBTRACT, m_pHView);
}


void CSolidHoopsView::OnBooleantypeUnion()
{
	boolean_common(BOOLEAN_TYPE_UNION, m_pHView);
}

#endif //HOOPS_ONLY

void CSolidHoopsView::OnToolsLodgeneration() 
{
	CLodPage lodgenerationdialog(GetSolidView());
	lodgenerationdialog.DoModal();
	
}

bool CSolidHoopsView::Verticals::CAE::LegendVisibility(HBaseView * const pView)
{
	bool retval = false;
	HC_Open_Segment_By_Key(pView->GetModelKey());{	
		HC_Open_Segment("legend");{
			if(HC_Show_Existence("user options = legend")){
				char toggle[10] = {""};
				HC_Show_One_User_Option("legend", toggle);
				if(streq(toggle, "on")){
					retval = true;
				}
			}
		}HC_Close_Segment();
	}HC_Close_Segment();
	return retval;
}

#ifndef countof
#	define countof(x)	(int)(sizeof(x)/sizeof(x[0]))
#endif

void CSolidHoopsView::Verticals::CAE::LegendVisibility(HBaseView * const pView, bool onoff) 
{
	HC_Open_Segment_By_Key(pView->GetModelKey());{	

		HC_Set_User_Options("cae model");

		float colors[][3] = {
			{0,0,1},   {0, 0.333333f, 1},   {0, 0.666667f, 1},
			{0,1,1},   {0, 1,  0.666667f},  {0, 1, 0.333333f},
			{0,1,0},   {0.333333f, 1, 0},   {0.666667f, 1, 0},
			{1,1,0},   {1, 0.666667f, 0},   {1, 0.333333f, 0},
			{1,0,0},{1,1,1}
		};

		HC_Set_Color_Map_By_Value( "RGB", countof(colors), colors);

		HC_Open_Segment("legend");{
			bool does_legend_exist = false;
			if(HC_Show_Existence("user options = legend")){
				does_legend_exist = true;
			}
			if(does_legend_exist == false){
				/* Set a camera so we're looking down the -z axis, up is <0,1,0> and x and y
				 * range from [-1,1].  Make sure you're in a right handed coordinate system.*/
				float position[] = {0, 0, 5}, target[] = {0, 0, 0}, up[] = {0, 1, 0};
				HC_Set_Camera(position, target, up, 3, 2, "orthographic");
				HC_Set_Handedness("right");
				
				HC_Insert_Text( 0.05, -0.15f, 0, "Sample Data");

				/* Insert a mesh and set our min and max color index to show
				 * the range of possible colors.  The mesh should be in the
				 * 4th quadrant (+x, -y) of the screen. */
				//float points[][3] = {
				//	{0.1f, -0.2f, 0},{0.05f, -0.2f, 0},
				//	{0.1f, -0.9f, 0},{0.05f, -0.9f, 0},
				//};
				HPoint * points = new HPoint[2*(countof(colors)-1)+2]; /* plus 2 for the top two points */
				for(int i = 0, i_end = 2*(countof(colors)-1) +2; i < i_end; i += 2){
					points[i +0] = HPoint(0.13f, -0.2f - (i/2) * 0.07f);
					points[i +1] = HPoint(0.05f, -0.2f - (i/2) * 0.07f);
				}

				HC_KEY pckey = HC_KInsert_Mesh(countof(colors), 2, points);

				for(int i = 0, i_end = 2*(countof(colors)-1) +2; i < i_end; i += 2){
					HC_Open_Geometry(pckey);{
						HC_Open_Vertex(i +0);{
							HC_Set_Color_By_FIndex("faces", (countof(colors)-1) - (i/2) - 0.5);
						}HC_Close_Vertex();
						HC_Open_Vertex(i +1);{
							HC_Set_Color_By_FIndex("faces", (countof(colors)-1) - (i/2) - 0.5);
						}HC_Close_Vertex();
					}HC_Close_Geometry();
					HC_Restart_Ink();
					if(i < i_end -2){
						HC_Insert_Ink(points[i +0].x, points[i +0].y, points[i +0].z);
						HC_Insert_Ink(points[i +1].x, points[i +1].y, points[i +1].z);
						HC_Insert_Ink(points[i +3].x, points[i +3].y, points[i +3].z);
						HC_Insert_Ink(points[i +2].x, points[i +2].y, points[i +2].z);
						HC_Insert_Ink(points[i +0].x, points[i +0].y, points[i +0].z);
					}
				}

				/* Insert the text. */
				for(int i = 0, i_end = countof(colors)-1; i < i_end; ++i){
					float y_value = (points[2].y - points[2*i_end].y) * (i/(float)(i_end-1)) + points[2*i_end].y;
					float label = (500) * (i/(float)(i_end-1)) + 0;
					HC_Insert_Text(0.15f, y_value, 0, H_FORMAT_TEXT("%d", (int)label));
				}
				delete [] points;

				/* Enable color and color index interpolation, and set a depth range to bring
				 * the legend to the top of the z-buffer. */
				HC_Set_Rendering_Options(
					"color index interpolation,"
					"no color interpolation,"
					"depth range = (0.0, 0.1),"
					"color index interpolation options=visibility, isoline options=no visibility");

				/* Set a reasonable font.  Set text alignment to left (horizontally) and centered (vertically).
				 * Enable the visibility of perimeter edges, disable the visibility for lights, and set apropriate
				 * colors for text and edges. */
				HC_Set_Text_Font("name = roman, size = 0.045 oru");
				HC_Set_Text_Alignment("<v");
				HC_Set_Color("text = black, lines = black");
				HC_Set_Selectability("off");

				/* Move the legend to the upper left hand corner of the window. */
				HC_Translate_Object(1.1, 0.65, 0);
			}

			if(onoff){
				HC_Set_Visibility("off, lines = on, faces = on, text = on");
				HC_UnSet_One_Rendering_Option("attribute lock");
				HC_Set_User_Options("legend = on");
			}
			else {
				HC_Set_Visibility("off");
				HC_Set_Rendering_Options("attribute lock = visibility");
				HC_Set_User_Options("legend = off");
			}
		}HC_Close_Segment();/*legend*/
	}HC_Close_Segment();
}

void CSolidHoopsView::Verticals::CAE::MapData(HC_KEY const key)
{
	HShellVertexData shell_vertex_data;
	shell_vertex_data.SetKey(key);
	HUtilityGeometryCreation::ComputeFIndexDemoData(&shell_vertex_data);
}

void CSolidHoopsView::Verticals::CAE::MapSelectionSet(HBaseView * const pView) 
{

	HSelectionSet * selset = pView->GetSelection();
	int i, count = 0;
	if(selset && (count = selset->GetSize()) > 0){	
		LegendVisibility(pView, true);
		HC_KEY * keys = new HC_KEY[count];

		for(i=0; i<count; ++i)
			keys[i] = selset->GetAt(i);

		for(i=0; i<count; ++i){
			char type[32] = {""};
			HC_Show_Key_Type(keys[i], type);
			if(streq(type, "segment")){
				HC_Open_Segment_By_Key(keys[i]);{
					HC_Begin_Contents_Search(".", "shells");{
						HC_KEY key = INVALID_KEY;
						HC_Find_Contents(type, &key);
						MapData(key);
					}HC_End_Contents_Search();
				}HC_Close_Segment();
			}
			else{
				MapData(keys[i]);
			}
		}
		delete [] keys;
		AnimateSelectionSet(pView);
	}
	else
	{
		AfxMessageBox( _T("Select at least one shell to perform mapping.\t\n"), MB_ICONINFORMATION | MB_OK );
	}


	
}
void CSolidHoopsView::Verticals::CAE::QuadInterpolateData(HC_KEY const key)
{
	// open the shell's containing segment
	HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(key));{
		MapData(key);
		HUtilityGeometryCreation::GenerateFEAShell(key, false, "bilinear");
	}HC_Close_Segment();

	// delete the original shell
	HC_Delete_By_Key(key);
}

void CSolidHoopsView::Verticals::CAE::QuadInterpolateSelectionSet(HBaseView * const pView) 
{
	LegendVisibility(pView, true);
	HSelectionSet * selset = pView->GetSelection();
	int i, selection_count = 0;
	if(selset && (selection_count = selset->GetSize()) > 0){
		HC_KEY * keys = new HC_KEY[selection_count];

		for(i=0; i<selection_count; ++i)
			keys[i] = selset->GetAt(i);
		
		selset->DeSelectAll();

		for(i=0; i<selection_count; ++i){
			char type[32] = {""};
			HC_Show_Key_Type(keys[i], type);
			if(streq(type, "segment")){
				HC_Open_Segment_By_Key(keys[i]);{
					HC_Begin_Contents_Search(".", "shells");{
						HC_KEY key = INVALID_KEY;
						HC_Find_Contents(type, &key);
						QuadInterpolateData(key);
					}HC_End_Contents_Search();
				}HC_Close_Segment();
			}
			else{
				QuadInterpolateData(keys[i]);
			}
		}
		delete [] keys;
	}
}

#include "HBhvBehaviorManager.h"
#include "HBhvInterpolator.h"
#include "HBhvTimeline.h"
#include "HBhvAnimation.h"

void CSolidHoopsView::Verticals::CAE::AnimateSelectionSet(HBaseView * const pView)
{
	LegendVisibility(pView, true);
	HSelectionSet * selset = pView->GetSelection();
	int i, j, t, selection_count = 0, geometry_count = 0;
	if(selset && (selection_count = selset->GetSize()) > 0){
		char type[32] = {""};
		for(i = 0; i < selection_count; ++i){
			HC_KEY key = selset->GetAt(i);
			HC_Show_Key_Type(key, type);
			if(streq(type, "segment")){
				HC_Open_Segment_By_Key(key);{
					HC_Begin_Contents_Search(".", "shells");{
						HC_KEY key = INVALID_KEY;
						while(HC_Find_Contents(type, &key)){
							if(key != INVALID_KEY)
								++geometry_count;
						}
					}HC_End_Contents_Search();
				}HC_Close_Segment();
			}
			else{
				++geometry_count;
			}
		}
		//HC_KEY * keys = new HC_KEY[geometry_count];
		HShellVertexData * shell_vertex_data = new HShellVertexData[geometry_count];
		for(j = 0, i = 0; i < selection_count; ++i){
			HC_KEY key = selset->GetAt(i);
			HC_Show_Key_Type(key, type);
			if(streq(type, "segment")){
				HC_Open_Segment_By_Key(key);{
					HC_Begin_Contents_Search(".", "shells");{
						key = INVALID_KEY;
						while(HC_Find_Contents(type, &key)){
							shell_vertex_data[j].SetKey(key);
							HUtilityGeometryCreation::ComputeFIndexDemoData(&shell_vertex_data[j]);
							++j;
						}
					}HC_End_Contents_Search();
				}HC_Close_Segment();
			}
			else{
				shell_vertex_data[i].SetKey(key);
				HUtilityGeometryCreation::ComputeFIndexDemoData(&shell_vertex_data[j]);
				++j;
			}
		}			
		selset->DeSelectAll();

		HBhvBehaviorManager *pBehaviorManager = pView->GetModel()->GetBhvBehaviorManager();

		for(i = 0; i < geometry_count; ++i){
			char owner[MVO_BUFFER_SIZE];
			int count = 0;
			HC_Show_Owner_By_Key(shell_vertex_data[i].GetKey(), owner);
			HC_Begin_Contents_Search(owner, "shells");{
				HC_Show_Contents_Count(&count);
			}HC_End_Contents_Search();
			/* There can only be one shell in a segment for the color interpolator */
			if(count > 1){
				static int uid = 0;
				HC_Open_Segment(H_FORMAT_TEXT("%s/CAE Anim %d", owner, uid++));
				HC_Move_By_Key(shell_vertex_data[i].GetKey(), ".");
				HC_Show_Owner_By_Key(shell_vertex_data[i].GetKey(), owner);
			}
			
			HC_KEY owner_key = HC_KCreate_Segment(owner);
			HUtility::NameSegments(owner_key, pView);

			HBhvTargetObject::CreateTargetString("SPATH", owner, owner);
			if(pBehaviorManager->FindAnimation(owner, "ColorMorph")){
				if(count > 1){
					HC_Close_Segment();
				}
				continue;
			}
			HBhvInterpolatorColorMorph *pColorSwitch = new HBhvInterpolatorColorMorph(0, "colorSwitch");
			pColorSwitch->SetUseFIndex(true);

			HBhvTimeline *pTimeline = new HBhvTimeline(0);
			for(int l = 0; l < 30; ++l){
				bool doesExist;
				pTimeline->AddKeyframe(l, doesExist);
			}
			pBehaviorManager->AddAnimation("myrotation", owner, pTimeline, pColorSwitch );

			HPoint * colors = new HPoint[shell_vertex_data[i].GetVertexCount() +30];
			for(int f = 0; f < shell_vertex_data[i].GetVertexCount() +30; ++f){
				colors[f].x = shell_vertex_data[i].GetFIndexData()[f];
			}
			for(t = 0; t < 30; ++t){
				pColorSwitch->AddMorphData(colors +t, shell_vertex_data[i].GetVertexCount(), pView->GetModel());
			}
			for(t = 0; t < 30; ++t){
				pColorSwitch->InsertDiscrete(H_FORMAT_TEXT("%d", t), t);
			}
			delete [] colors;

			if(count > 1){
				HC_Close_Segment();
			}
		}
		delete [] shell_vertex_data;
	}
}


void CSolidHoopsView::OnColorizeScan() 
{
	//m_pHView->SetColorIndexInterpolation(true);
	//m_pHView->SetColorInterpolation(true);
	bool vis = Verticals::CAE::LegendVisibility(m_pHView);
	
	if (!m_bScanColorized)
	{
		HC_Open_Segment_By_Key(m_pHView->GetModelKey());
		if (HC_Show_Existence("rendering options = attribute lock"))
			HC_UnSet_One_Rendering_Option("attribute lock");
		HC_Close_Segment();
		HVerticalUtility::ColorizePointCloud(m_pHView->GetModelKey());
		m_bScanColorized = true;
		if (!vis)
			Verticals::CAE::LegendVisibility(m_pHView, true);

	}
	else
	{
		HC_Open_Segment_By_Key(m_pHView->GetModelKey());
		HC_Set_Rendering_Options("attribute lock = color");
		HC_Set_Color_By_FIndex("vertices", 0.0);
  		HC_Close_Segment();
		m_bScanColorized = false;
		if (vis)
			Verticals::CAE::LegendVisibility(m_pHView, false);
	}
	m_pHView->Update();
}

void CSolidHoopsView::OnUpdateColorizeScan(CCmdUI* pCmdUI) 
{
	if (m_bScanColorized)
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnDummy() 
{
	;
}

void CSolidHoopsView::OnToggleSplat() 
{
	m_pHView->SetSplatRendering(!m_pHView->GetSplatRendering());
}

void CSolidHoopsView::OnUpdateToggleSplat(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetSplatRendering())
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}

void CSolidHoopsView::OnToggleSplatSymbol() 
{

	if (m_pHView->GetSplatSymbol() == SplatRound)
		m_pHView->SetSplatSymbol(SplatSquare);
	else
		m_pHView->SetSplatSymbol(SplatRound);

}

void CSolidHoopsView::OnUpdateToggleSplatSymbol(CCmdUI* pCmdUI) 
{
	if (m_pHView->GetViewActive() && m_pHView->GetModel()->GetFileLoadComplete() &&
		m_pHView->GetSplatSymbol() == SplatSquare)
		pCmdUI->SetCheck (1);
    else
		pCmdUI->SetCheck (0);
}


void CSolidHoopsView::OnMaterialSelector()
{
	HTexturePickerWindow subwindow(m_pHView,0,0);

	if (!m_pHView->GetHObjectManager()->GetHObject("subwindow"))
		m_pHView->GetHObjectManager()->AddHObject(new HTexturePickerWindow(m_pHView));
	
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
	HPoint porig, pconv;
	HC_Compute_Coordinates(".", "local window", &m_PositionOnRightClick, "local pixels", &pconv);
	HC_Close_Segment();
	
    HC_Open_Segment("HAbsoluteWindows");
    subwindow.Insert(pconv.x, 120, 400,pconv.y,"Materials",120,100);
    HC_Close_Segment();
    HC_Close_Segment();
	
 	m_pHView->Update();	

}



LRESULT CSolidHoopsView::OnThreadedLoadingCompleted(WPARAM wParam, LPARAM lParam)
{
 	HSolidModel *	pModel = (HSolidModel *)m_pHView->GetModel();
	CSolidHoopsDoc * pDoc = (CSolidHoopsDoc *)GetDocument();
	StopThreadedLoading();
	if (!using_modelling_kernel)
		pDoc->m_ProgressDlg->Output("Optimizing");

	m_has_initial_view=m_pHView->HasInitialView();
	m_pHView->GetModel()->SetFileLoadComplete(true);
	m_pHView->GetModel()->SetFirstFitComplete(true);


	m_pHView->SetGeometryChanged();

	if( !m_has_initial_view )
	{    
		m_pHView->FitWorld();		// fit the camera to the scene extents
		m_pHView->CameraPositionChanged(true);
	}

	m_pHView->SetZoomLimit();
	pModel->UpdateModelHandedness();

	m_pHView->SetRenderMode(m_pHView->GetRenderMode(), true);

	// grab the input handler for point cloud file types
	HIOUtilityPointCloud *hio_point_cloud;
	if (hio_point_cloud = (HIOUtilityPointCloud *)HDB::GetHIOManager()->GetInputHandler("pts")) {
		// grab the extension of the file we just read in
		TCHAR extension[MVO_BUFFER_SIZE];
		HUtility::FindFileNameExtension(pDoc->filename, extension);
		
		// look at the list of file types supported by the point cloud reader, see if they match the extension of the file we read in
		//   - if there is a match, we make sure to set vertex visibility on
		char const *point_cloud_types = hio_point_cloud->GetInputTypesString();
		int offset = 0;
		char point_cloud_extension[MVO_BUFFER_SIZE];
		while (HC_Parse_String(point_cloud_types, ",", offset++, point_cloud_extension)) {
			if (wcsieq(H_WCS(extension).encodedText(), H_WCS(point_cloud_extension).encodedText())) {
				HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
					HC_Set_Visibility("vertices = on");
				HC_Close_Segment();

				break;
			}
		}
	}
	
	if (m_pDlgSegmentBrowser)
	    m_pDlgSegmentBrowser->RefreshBrowser();

 	ViewReady();
 	m_pHView->ExhaustiveUpdate();

	if (!using_modelling_kernel) {
		if (pDoc->m_ProgressDlg)		
			pDoc->m_ProgressDlg->DestroyWindow();
 		delete pDoc->m_ProgressDlg;
 		pDoc->m_ProgressDlg = 0;
	}

	m_pHView->SetSuppressUpdateTick(false);

 	this->ValidateRect(0);
	//OnPaint();
	HIntRectangle rectangle; 
	HC_Control_Update_By_Key (GetViewKey(), "refresh");
	m_pHView->GetConstantFrameRateObject()->SetActivityType(GeneralActivity);

	GetIntRectangle( &rectangle );
	m_pHView->Notify( HSignalPaint, &rectangle );
	m_pHView->ResetIdleTime();
	m_pHView->GetUndoManager()->Flush();			//don't care about this initial camera change

	m_pHView->ForceUpdate();

 	if (CAppSettings::UseFramerate && CAppSettings::CurrentFramerateMode==FramerateTarget)
			EnableFrameRate();

	//this system function releases all unused memory associated with the process
	//essentially performing a garbage collection
#if 0
	HANDLE h = GetCurrentProcess();
	SetProcessWorkingSetSize(h, (SIZE_T)-1, (SIZE_T)-1);
#endif
	CSolidHoopsApp *app = static_cast<CSolidHoopsApp *>(AfxGetApp());
	app->CompleteCommandLineProcessing(this);
	return 0;
}



void CSolidHoopsView::OnClashdetectionStartclashcalculation()
{
//	((HSolidView *)m_pHView)->CalculateClashes();
	CSolidHoopsFrame* pMainFrm = (CSolidHoopsFrame*) AfxGetMainWnd();
	pMainFrm->ShowClashBrowserDialogBar(true);
	((ClashDlg *)GetClashBrowserDialog())->Init();
 		// TODO: Add your command handler code here
}

void CSolidHoopsView::OnToolsClashdetectionClashbrowser()
{
	CSolidHoopsFrame* pMainFrm = (CSolidHoopsFrame*) AfxGetMainWnd();
	pMainFrm->ShowClashBrowserDialogBar(true);
	// TODO: Add your command handler code here
}

void CSolidHoopsView::OnNextLayout()
{
	m_pLayoutLoadUtility->LoadNextLayout();
}

void CSolidHoopsView::OnUpdateNextLayout(CCmdUI* pCmdUI)
{
	if(m_pLayoutLoadUtility != 0)
	{
		if(m_pLayoutLoadUtility->IsNextAvaiable())
			pCmdUI->Enable (1);
		else
			pCmdUI->Enable (0);
	}
	else
		pCmdUI->Enable (0);
}

void CSolidHoopsView::OnPreviousLayout()
{
	m_pLayoutLoadUtility->LoadPeviousLayout();
}

void CSolidHoopsView::OnUpdatePreviousLayout(CCmdUI* pCmdUI)
{
	if(m_pLayoutLoadUtility != 0)
	{
		if(m_pLayoutLoadUtility->IsPreviousAvaiable())
			pCmdUI->Enable (1);
		else
			pCmdUI->Enable (0);
	}
	else
		pCmdUI->Enable (0);

}

void CSolidHoopsView::OnToolsShadereditor()
{
#ifdef HOOPS_ONLY

   CAdvancedMaterialDlg *pDialog = new CAdvancedMaterialDlg( m_pHView );
    
   //Check if new succeeded and we got a valid pointer to a dialog object
   if(pDialog != NULL)
   {
      BOOL ret = pDialog->Create(IDD_ADVANCED_MATERIAL_DLG ,this);
      pDialog->ShowWindow(SW_SHOW);
	  UNREFERENCED (ret);
   }

	m_pHView->Update();
#endif
}

typedef HRESULT (CALLBACK *SETDLLPROC)( void * );

static int dynamic_debug_common(int slot, void * ptr)
{
	int ret=0;

	//load the dll
	HINSTANCE kernel32 = LoadLibraryA("hoops_ddb_vc80d.dll");
	if(kernel32 && slot>=1 && slot<=5)
	{
		//find the appropriate function
		SETDLLPROC ddb_func = (SETDLLPROC) GetProcAddress (kernel32, (LPCSTR)slot);

		//call it
		if(ddb_func)
			ret=ddb_func(ptr);
		
		//free the dll
		FreeLibrary(kernel32);
	}

	return ret;
}

void CSolidHoopsView::OnDynamicExtraSlot1()
{
	dynamic_debug_common(1, m_pHView);
}

void CSolidHoopsView::OnDynamicExtraSlot2()
{
	dynamic_debug_common(2, m_pHView);
}

void CSolidHoopsView::OnDynamicExtraSlot3() 
{
	dynamic_debug_common(3, m_pHView);
}

void CSolidHoopsView::OnDynamicExtraSlot4() 
{
	dynamic_debug_common(4, m_pHView);
}
 
void CSolidHoopsView::OnDynamicExtraSlot5() 
{
	dynamic_debug_common(5, m_pHView);
}


void CSolidHoopsView::InitMaterialLibrary ()
{
	if (m_bMaterialLibraryInitialized)
		return;

	if (HDB::GetMaterialLibrary() == NULL)
		HDB::SetMaterialLibrary (new HMaterialLibrary());

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey()); {
		m_bMaterialLibraryInitialized = HDB::GetMaterialLibrary()->RegisterMaterials (CAppSettings::MaterialLibraryDirectory);
		//HDB::GetMaterialLibrary()->RegisterMaterials (H_FORMAT_TEXT ("%s\\%s", getenv("HMF_MASTER"), "materials"));
		HC_Style_Segment (HDB::GetMaterialLibrary()->GetContainerSegment());
	} HC_Close_Segment ();
	HDB::GetMaterialLibrary()->SetEnvironment ("test/environment/civic_square");

	HC_Open_Segment_By_Key (m_pHView->GetLightsKey()); {
		HC_Flush_Contents ("...", "lights");
		HC_Set_Visibility ("images=off");
		HC_Include_Segment (HDB::GetMaterialLibrary()->GetContainerSegment());
	} HC_Close_Segment ();
}


void CSolidHoopsView::OnExtraSlot1()
{
}

void CSolidHoopsView::OnExtraSlot2()
{
}

void CSolidHoopsView::OnExtraSlot3()
{
}

void CSolidHoopsView::OnExtraSlot4() 
{
}
 
void CSolidHoopsView::OnExtraSlot5() 
{
}

