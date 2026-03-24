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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsApp.cpp,v 1.386 2011-01-27 00:48:23 chad Exp $
//

// CSolidHoopsApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <errno.h>
#include "resource.h"

#include "vlist.h"

#include "HSInclude.h"

#include "CSolidHoopsApp.h"
#include "CSolidHoopsDoc.h"
#include "CSolidHoopsView.h"
#include "CSolidHoopsFrm.h"
#include "CSolidHoopsChildFrm.h"

#include "HDB.h"
#include "CTDriver.h"

#include "HOpCameraManipulate.h"
#include "HOpCameraOrbit.h"
#include "HSolidView.h"
#include "HSUtility.h" 
#include "HBhvBehaviorManager.h"
#include "HUtilityLocaleString.h"
#include "HIOUtilityPointCloud.h"

// 3dgs
#include "hversion.h"

// Options dialog
#include "HUIUtilityMFC.h"
#include "PartviewerOptionPages.h"
#include "PrintOptionsDlg.h"

// Lead Tools
#ifdef HOOPS_LEAD_TOOLS
#include "HIOUtilityLeadTools.h"
#endif


// DWG import/export
#ifdef HOOPS_DWG_IO
#include "HIOUtilityDwg.h"
#endif	// HOOPS_DWG_IO


// IV import/export
#ifdef HOOPS_IV_IO
#include "HIOUtilityIV.h"
#endif	// HOOPS_IV_IO

#ifdef HOOPS_QA
#ifndef _DEBUG
#include "script.h"
using namespace TestComplete;
#define _WIN32_DCOM 0x0400
IMPLEMENT_TESTCOMPLETE_GLOBAL_OBJECTS
#endif
#endif



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CRITICAL_SECTION sweeten_lock;


#if defined(INTEROP) || defined(ACIS)
#include "license.hxx"
#include "spa_unlock_result.hxx"
#include <direct.h>

#if defined(ACIS)
#include "entity_mgr_factory.hxx"
#include "asm_api.hxx"
#endif // Acis

#endif

/////////////////////////////////////////////////////////////////////////////
// CHoopsApp

BEGIN_MESSAGE_MAP(CSolidHoopsApp, CHoopsApp)
	//{{AFX_MSG_MAP(CSolidHoopsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_DDB_ABOUT, OnDDBAbout)
	ON_COMMAND(ID_VISIT_HOOPS3D, OnVisitHoops3d)
	ON_COMMAND(ID_LOAD_HELP, OnLoadHelp)
	ON_COMMAND(ID_CONSTANTSPIN, OnConstantspin)
	ON_UPDATE_COMMAND_UI(ID_CONSTANTSPIN, OnUpdateConstantspin)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_FILE_PRINT_OPTIONS, OnFilePrintOptions)
	ON_COMMAND(ID_PERFORMANCE_DEFAULT, OnPerformanceDefault)
	ON_UPDATE_COMMAND_UI(ID_PERFORMANCE_DEFAULT, OnUpdatePerformanceDefault)
	ON_COMMAND(ID_PERFORMANCE_HIGH, OnPerformanceHigh)
	ON_UPDATE_COMMAND_UI(ID_PERFORMANCE_HIGH, OnUpdatePerformanceHigh)
	ON_COMMAND(ID_PERFORMANCE_STATIC_MODEL, OnPerformanceStaticModel)
	ON_UPDATE_COMMAND_UI(ID_PERFORMANCE_STATIC_MODEL, OnUpdatePerformanceStaticModel)
	ON_COMMAND(ID_PERFORMANCE_SEGMENT_LEVEL_DL, OnPerformanceSegmentDisplayLists)
	ON_UPDATE_COMMAND_UI(ID_PERFORMANCE_SEGMENT_LEVEL_DL, OnUpdatePerformanceSegmentDisplayLists)
	ON_COMMAND(ID_PERFORMANCE_GEOMETRY_LEVEL_DL, OnPerformanceGeometryDisplayLists)
	ON_UPDATE_COMMAND_UI(ID_PERFORMANCE_GEOMETRY_LEVEL_DL, OnUpdatePerformanceGeometryDisplayLists)
	ON_COMMAND(ID_PERFORMANCE_FIXED_FRAMERATE, OnPerformanceFixedFramerate)
	ON_UPDATE_COMMAND_UI(ID_PERFORMANCE_FIXED_FRAMERATE, OnUpdatePerformanceFixedFramerate)
	ON_COMMAND(ID_PERFORMANCE_TARGET_FRAMERATE, OnPerformanceTargetFramerate)
	ON_UPDATE_COMMAND_UI(ID_PERFORMANCE_TARGET_FRAMERATE, OnUpdatePerformanceTargetFramerate)
	ON_COMMAND(ID_EFFECTS_NONE, OnEffectsNone)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_NONE, OnUpdateEffectsNone)
	ON_COMMAND(ID_EFFECTS_FANCY, OnEffectsFancy)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_FANCY, OnUpdateEffectsFancy)
	ON_COMMAND(ID_EFFECTS_AMBIENT_OCCLUSION, OnEffectsAmbientOcclusion)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_AMBIENT_OCCLUSION, OnUpdateEffectsAmbientOcclusion)
	ON_COMMAND(ID_EFFECTS_BLOOM, OnEffectsBloom)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_BLOOM, OnUpdateEffectsBloom)
	ON_COMMAND(ID_EFFECTS_FAST_SILHOUETTE_EDGES, OnEffectsFastSilhouetteEdges)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_FAST_SILHOUETTE_EDGES, OnUpdateEffectsFastSilhouetteEdges)
	ON_COMMAND(ID_EFFECTS_REFLECTION_PLANE, OnEffectsReflectionPlane)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_REFLECTION_PLANE, OnUpdateEffectsReflectionPlane)
	ON_COMMAND(ID_EFFECTS_SHADOW_MAPS, OnEffectsShadowMaps)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_SHADOW_MAPS, OnUpdateShadowMaps)
	ON_COMMAND(ID_EFFECTS_SIMPLE_SHADOWS, OnEffectsSimpleShadows)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_SIMPLE_SHADOWS, OnUpdateEffectsSimpleShadows)

	//}}AFX_MSG_MAP
#ifdef PARASOLID
	ON_COMMAND(ID_VISIT_PARASOLID, OnVisitParasolid)
#endif // PARASOLID
#ifdef ACIS
	ON_COMMAND(ID_VISIT_SPATIAL, OnVisitSpatial)
#endif //ACIS
#ifdef GRANITE
	ON_COMMAND(ID_VISIT_PTC, OnVisitPtc)
#endif // GRANITE


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsApp construction

#include "getopts.cpp"

static bool is_pre_vista()
{
	OSVERSIONINFO OSversion;
		
	OSversion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	::GetVersionEx(&OSversion);

	if (OSversion.dwMajorVersion > 5)
		return false;
	else 
		return true;
}		


CSolidHoopsApp::~CSolidHoopsApp()
{
	if(is_pre_vista())
		SystemParametersInfo( SPI_SETSELECTIONFADE, 0, (PVOID)m_bSelectionFadeWasEnabled, 0 );
}

CSolidHoopsApp::CSolidHoopsApp()
{
	m_bShuttingDown = false;

	// SIL: Menu fade causes problems (black updates) on ATI cards when the HOOPS client area is entirely 
	// visible and on the second monitor. Suspected driver problem. Workaround by saving setting and disabling.
	if(is_pre_vista())
	{
		SystemParametersInfo( SPI_GETSELECTIONFADE, 0, &m_bSelectionFadeWasEnabled, 0 );
		SystemParametersInfo( SPI_SETSELECTIONFADE, 0, (PVOID)FALSE, 0 );
	}
#ifdef INTERNAL_RELEASE_LICENSE
	HC_Define_System_Options( INTERNAL_RELEASE_LICENSE );
#endif   

//
// DO NOT CHANGE THE LOGIC HERE. WE WANT WARNINGS
// TO BE ON FOR DEBUG BUILDS OF THE PART VIEWER
//

#ifdef HOOPS_QA
	HC_Define_System_Options("no warnings, no info, errors=on, no message limit");
#elif defined( _DEBUG )
	HC_Define_System_Options("errors, info, no message limit");
#else
	HC_Define_System_Options("no warnings, no info, no errors, no fatal errors, no message limit");
#endif


	//this is overridden later and could be removed
	HC_Define_System_Options("multi-threading = full");

 
	HDB::EnableErrorManager();
	m_bConstantSpin = false;
	m_pCTDriver = 0;
	m_opt_dlg = 0;

#ifdef HOOPS_LEAD_TOOLS
	m_pIOUtilityLeadTools = 0;
#endif
#ifdef HOOPS_DWG_IO
	m_pIOUtilityDwg = 0;
#endif

#ifdef HOOPS_IV_IO
	m_pIOUtilityIV = 0;
#endif

	m_pCmdLineDlg = 0;
	m_pCmdLineOutputFile = 0;

	InitializeCriticalSection(&sweeten_lock);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSolidHoopsApp object

CSolidHoopsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsApp initialization


static AFX_DATA const CWnd wndTopMost;



#define UtC(x,y)     (wcstombs(y, x, wcslen(x)), y)
 

BOOL CSolidHoopsApp::InitInstance()
{
	HANDLE heaps[1025];
	DWORD nheaps = GetProcessHeaps(1024, heaps);

	for ( DWORD i = 0 ; i < nheaps ; i++ ) {
		ULONG  HeapFragValue = 2;
		HeapSetInformation(heaps[i], HeapCompatibilityInformation, &HeapFragValue, sizeof(HeapFragValue));
	}

	InitCommonControls();
	// Set the registry key 
	SetRegistryKey(CAppSettings::CompanyName);

	// read all the settings from registry
	ReadSettingsFromRegistry();

	m_pHoopsDB = new HDB;
	m_pHoopsDB->Init();

	//m_pCTDriver must be started after m_pHoopsDB is created
	m_pCTDriver = new CTDriver( 10 );
	m_pCTDriver->StartTimer();


	// set the font directory
	TCHAR fontDirectory[MAX_PATH+32];
	::GetWindowsDirectory(fontDirectory, MAX_PATH);
	_tcscat(fontDirectory, _T("\\Fonts"));
	char buf[4096];
	sprintf(buf, "font directory = (%s, .)", H_ASCII_TEXT(fontDirectory));
	sprintf(buf, "%s, multi-threading=%s", buf, 
		CAppSettings::MultiThreading==MultiThreadingFull ? "full" : 
		CAppSettings::MultiThreading==MultiThreadingBasic ? "basic" : "off");
	HC_Define_System_Options(buf);


#ifdef ACIS
	HInputHandler * handler = HDB::GetHIOManager()->GetInputHandler("hsf");
	HIORegisterInputType("asf",	handler); 
#endif // ACIS

#ifdef PARASOLID
	HInputHandler * handler = HDB::GetHIOManager()->GetInputHandler("hsf");
	HIORegisterInputType("psf",	handler); 
#endif // PARASOLID


#ifdef HOOPS_LEAD_TOOLS
	m_pIOUtilityLeadTools = new HIOUtilityLeadTools();
	HIORegisterInputType("jpeg",	m_pIOUtilityLeadTools); 
	HIORegisterInputType("jpg",		m_pIOUtilityLeadTools); 
	HIORegisterInputType("bmp",		m_pIOUtilityLeadTools); 
	HIORegisterInputType("tif",		m_pIOUtilityLeadTools); 
	HIORegisterInputType("tiff",	m_pIOUtilityLeadTools); 

	HIORegisterOutputType("jpeg",	m_pIOUtilityLeadTools); 
	HIORegisterOutputType("jpg",	m_pIOUtilityLeadTools); 
	HIORegisterOutputType("bmp",	m_pIOUtilityLeadTools); 
	HIORegisterOutputType("tif",	m_pIOUtilityLeadTools); 
	HIORegisterOutputType("tiff",	m_pIOUtilityLeadTools);
#endif

#ifdef HOOPS_DWG_IO
	m_pIOUtilityDwg = new HIOUtilityDWG();
	m_pIOUtilityDwg->RegisterInputHandlerTypes();
//	m_pIOUtilityDwg->RegisterOutputHandlerTypes();
#endif

#ifdef HOOPS_IV_IO
	m_pIOUtilityIV = new HIOUtilityIV();
	m_pIOUtilityIV->RegisterInputHandlerTypes();
//	m_pIOUtilityIV->RegisterOutputHandlerTypes();
#endif

	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
 	memset(m_AppDirectory,0,MVO_BUFFER_SIZE);	
	UtC(cur_dir, m_AppDirectory);
 
	if( _tcsclen( CAppSettings::PartsDirectory ) != 0 )
		SetCurrentDirectory(CAppSettings::PartsDirectory);

#ifdef HOOPS_QA
	const TCHAR *qa_dir;

	qa_dir = _tgetenv(_T("HMF_MASTER"));

	if (qa_dir)
		SetCurrentDirectory(qa_dir);
	else
		AfxMessageBox(_T("You are running the QA target but have not set the HMF_MASTER environment variable.  TestComplete scripts will not work correctly."), MB_ICONSTOP);

#endif

#if defined(INTEROP) || defined(ACIS)
	const char * unlock_str = NULL;

#ifdef SPATIAL_LICENSE
	unlock_str = SPATIAL_LICENSE;
#else
	unlock_str = getenv("SPATIAL_LICENSE");
#endif // SPATIAL_LICENSE

#ifdef ACIS
	//Base configuration must happen before unlocking ACIS.
	//   If not using initialize_base, then unlock must 
	//   happen after the initialize modeller 
	base_configuration base_config;
	logical ok = initialize_base( &base_config);
#endif // ACIS

	spa_unlock_result out = spa_unlock_products(unlock_str);
	if (out.get_state() == SPA_UNLOCK_FAIL) {
		wchar_t * error_msg = L"Unable to find license key for Spatial products or the provided license key is invalid.\n\n"
						  	  L"Set an environment variable of name SPATIAL_LICENSE to your license, or use a preprocessor\n"
							  L"define to store the string in SPATIAL_LICENSE.  If you don't have a license and require one\n"
							  L"contact Tech Soft 3D.\n\n"
							  L"Neither the InterOp translators nor the ACIS kernel will be available for use.";
		AfxMessageBox(error_msg, MB_ICONSTOP);
	}
#ifdef _DEBUG
	else if ( out.get_state() == SPA_UNLOCK_PASS_WARN){
		//Display warning message for Evaluation customers
		char str[256];
		sprintf(str,"%s\n This evaluation key will expire in %i days.", out.get_message_text(), out.get_num_days());		
		MessageBoxA(NULL,str, "Spatial Eval Warning" , MB_ICONWARNING );
	}
#endif // _DEBUG

#ifdef INTEROP
	char *path;
	path = getenv("PATH");
	if (path == NULL) {
		wchar_t * error_msg = L"Unable to add CATIA V5 DLLs to the path.  CATIA V5 translation will not work.";
		AfxMessageBox(error_msg, MB_ICONSTOP);
	}
	else {
		_putenv(H_FORMAT_TEXT("PATH=%s\\lib3dx\\intel_a\\code\\bin;%s", m_AppDirectory, path));
	}
#endif // INTEROP
#endif // defined(INTEROP) || defined(ACIS)

#ifdef PARASOLID


	bool has_schema = false;

	if( _tcslen( CAppSettings::SchemaPath ) != 0 )
	{
		has_schema = true;
		HP_Init(CAppSettings::SchemaPath, PK_LOGICAL_false, PK_LOGICAL_true);
	}
	else
	{
		wchar_t *schema_path;
		schema_path = _wgetenv( L"P_SCHEMA" );
		if( schema_path )
		{
			HP_Init( schema_path, PK_LOGICAL_false, PK_LOGICAL_true);
			has_schema = true;
		}
	}
	if( !has_schema )
	{
		AfxMessageBox(_T("Could not determine location of your Schema Files.\nUse the 'Tools-Options' dialog to set them correctly or define P_SCHEMA environment variable."), MB_ICONSTOP);	
		// we still wanna initialize the bridge, if not file load, 
		// user can atleast do geom creation and stuff - Rajesh B (30-May-03)
		HP_Init( "", PK_LOGICAL_false, PK_LOGICAL_true);
	}

	PK_TOPOL_facet_mesh_o_t     generation_settings;
	PK_TOPOL_facet_mesh_o_m( generation_settings );

	generation_settings.match					= CAppSettings::FacetMatch;
	generation_settings.is_curve_chord_tol		= CAppSettings::IsCurveChordTol;
	generation_settings.curve_chord_tol			= atof(H_ASCII_TEXT(CAppSettings::CurveChordTol));
	generation_settings.is_curve_chord_ang		= CAppSettings::IsCurveChordAngTol;
	generation_settings.curve_chord_ang			= atof(H_ASCII_TEXT(CAppSettings::CurveChordAngTol));
	generation_settings.is_surface_plane_tol	= CAppSettings::IsSurfacePlaneTol;
	generation_settings.surface_plane_tol		= atof(H_ASCII_TEXT(CAppSettings::SurfacePlaneTol));
	generation_settings.is_surface_plane_ang	= CAppSettings::IsSurfacePlaneAngTol;
	generation_settings.surface_plane_ang		= atof(H_ASCII_TEXT(CAppSettings::SurfacePlaneAngTol));
	generation_settings.is_facet_plane_tol		= CAppSettings::IsFacetPlaneTol;
	generation_settings.facet_plane_tol			= atof(H_ASCII_TEXT(CAppSettings::FacetPlaneTol));
	generation_settings.is_facet_plane_ang		= CAppSettings::IsFacetPlaneAngTol;
	generation_settings.facet_plane_ang			= atof(H_ASCII_TEXT(CAppSettings::FacetPlaneAngTol));

	PK_TOPOL_render_line_o_t line_opts;
	PK_TOPOL_render_line_o_m(line_opts);

	line_opts.is_curve_chord_tol	= CAppSettings::IsLineCurveChordTol;
	line_opts.curve_chord_tol		= atof(H_ASCII_TEXT(CAppSettings::LineCurveChordTol));
	line_opts.is_curve_chord_ang	= CAppSettings::IsLineCurveChordAngTol;
	line_opts.curve_chord_ang		= atof(H_ASCII_TEXT(CAppSettings::LineCurveChordAngTol));

	HP_Set_Tessellation_Options(&line_opts, 0, &generation_settings);
	HP_Set_Rendering_Options("no merge faces");

#endif // PARASOLID

#ifdef ACIS
	outcome o; 
	o = api_start_modeller(0);
	check_outcome(o);
	
	//Issue #10605: Default Entity Manager Factory no longer registered by default		
	if (get_major_version() >= 20) 
	{
		entity_mgr_factory* my_manager = new default_entity_mgr_factory();
		{
			outcome o = asmi_set_entity_mgr_factory(my_manager);
			check_outcome(o);
		}
	}

	o = api_initialize_hoops_acis_bridge();
	check_outcome(o);
	ha_rendering_options &roptions=HA_Get_Rendering_Options();
	{
		roptions.SetMergeFacesMode(TRUE);
		roptions.SetGeomPattern ("?Include Library/ACIS model geometry");
		roptions.SetPattern("entity");
	}	
#endif // ACIS


#ifdef GRANITE
	HG_Init(0);
	HG_Set_Rendering_Options("merge faces");

	// apply the applications tessellation tolerances
	KTriangulator_ptr triangulator;
	HG_Show_Triangulator(triangulator);
	triangulator->SetAngularTolerance(atof(H_ASCII_TEXT(CAppSettings::DefaultAngularTolerance)));
	triangulator->SetPlanarTolerance(atof(H_ASCII_TEXT(CAppSettings::DefaultPlanarTolerance)));
	triangulator->SetTessellationTolerance(atof(H_ASCII_TEXT(CAppSettings::DefaultTessellationTolerance)));
	HG_Set_Triangulator(triangulator);
#endif // GRANITE


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();   // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
#ifdef PARASOLID
#ifdef INTEROP
	UINT child_frm_res = IDR_HOOPSTYPE_PARASOLID_IOP;
#else
	UINT child_frm_res = IDR_HOOPSTYPE;
#endif // INTEROP
	UINT main_frm_res = IDR_MAINFRAME;
#endif // PARASOLID

#ifdef ACIS
#ifdef INTEROP
	UINT child_frm_res = IDR_HOOPSTYPE_ACIS_IOP;
#else
	UINT child_frm_res = IDR_HOOPSTYPE1;
#endif // INTEROP
	UINT main_frm_res = IDR_MAINFRAME1;
#endif // ACIS

#ifdef GRANITE
	UINT child_frm_res = IDR_HOOPSTYPE2;
	UINT main_frm_res = IDR_MAINFRAME2;
#endif // GRANITE

#ifdef HOOPS_ONLY
	UINT child_frm_res = IDR_HOOPSTYPE3;
	UINT main_frm_res = IDR_MAINFRAME3;
#endif // HOOPS_ONLY


	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		child_frm_res,
		RUNTIME_CLASS(CSolidHoopsDoc),
		RUNTIME_CLASS(CSolidHoopsChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSolidHoopsView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CHoopsFrame* pMainFrame = new CSolidHoopsFrame;
	if (!pMainFrame->LoadFrame(main_frm_res))
		return FALSE;

	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	//////////////////////////////////////////////////////
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);

// Set the initial app size to match the GUI test template's starting size.
// This ensures that all location-dependent commands will playback correctly.
// The values are designed to match the app-size that results after
// doing a 'maximize' on a 1280x1024 desktop that has the standard windows 
// toolbar at the bottom
#ifdef HOOPS_QA
	m_pMainWnd->SetWindowPos(&wndTopMost, -4, -4, 1288, 998, SWP_NOOWNERZORDER);
#endif

	pMainFrame->UpdateWindow();

	AfxInitRichEdit();

	H_UTF8 utf8_cmd_line(m_lpCmdLine);
	char *cmd_line = reinterpret_cast<char *>(const_cast<utf8_char *>(utf8_cmd_line.encodedText()));
	char *seps = " ,\t,\n,\r";
	char *argv[1024];
	int argc = 0;
	char *rest_of_cmd_line;

	VList<H_WCS *> input_file_list;
	// command line doesn't contain process name -- use generic placeholder
	argv[argc++] = "exe_name";

	bool leave_arg_in_argv = false;
	argv[argc] = strtok_s(cmd_line, seps, &rest_of_cmd_line);
	while (argv[argc] != 0) {
		if (argv[argc][0] != '-' && !leave_arg_in_argv)
			input_file_list.AddLast(new H_WCS(H_UTF8(argv[argc])));
		else {
			leave_arg_in_argv = (argv[argc][0] == '-' && !streq(argv[argc], "-h") && !streq(argv[argc], "--help")) ? true : false;
			argc++;
		}
		argv[argc] = strtok_s(0, seps, &rest_of_cmd_line);
	}

	struct options opts[] = {
		{ 1, "output", "Name of output file", "o", 1 },
		{ 0, 0, 0, 0, 0 }
	};

	bool abort = false;

	assert(m_pCmdLineOutputFile == 0);
	assert(m_pCmdLineDlg == 0);
	m_pCmdLineDlg = new CCommandLineOutputDlg();
	m_pCmdLineDlg->Create(IDD_COMMAND_LINE_OUTPUT_WINDOW);
	int c;
	char *args = 0;
	bool display_help_message = false;
	while (!display_help_message && (c = getopts(argc, argv, opts, &args, m_pCmdLineDlg)) != 0) {
		switch (c) {
			case -3: {
				// this is the help case -- just display help message, don't do any other parsing
				m_pCmdLineDlg->ShowWindow(SW_SHOW);
				display_help_message = true;
			} break;

			case -2: {
				m_pCmdLineDlg->Notice(H_FORMAT_TEXT("\n--- Unknown Option: %s ---\n\n", args));
				m_pCmdLineDlg->ShowWindow(SW_SHOW);
			} break;

			case -1: {
				m_pCmdLineDlg->Notice("\n--- Unable to allocate memory for getopts(). ---\n\n");
				m_pCmdLineDlg->ShowWindow(SW_SHOW);
				abort = true;
			} break;

			case 1: {
				if (!m_pCmdLineOutputFile)
					m_pCmdLineOutputFile = new H_WCS(H_UTF8(args));
				else {
					m_pCmdLineDlg->Notice("\n--- Can only specify one output file. ---\n\n");
					m_pCmdLineDlg->ShowWindow(SW_SHOW);
					abort = true;
				}
			} break;
		}

		if (args)
			free(args);
	}

	if (input_file_list.Count() == 0 && m_pCmdLineOutputFile) {
		m_pCmdLineDlg->Notice("\n--- Must specify an input file to generate an output file. ---\n\n");
		m_pCmdLineDlg->ShowWindow(SW_SHOW);
		abort = true;
	}
	if (input_file_list.Count() > 1 && m_pCmdLineOutputFile) {
		m_pCmdLineDlg->Notice("\n--- Can only specify *one* input file when generating an output file. ---\n\n");
		m_pCmdLineDlg->ShowWindow(SW_SHOW);
		abort = true;
	}

	if (abort)
		m_pCmdLineDlg->SetAutoQuit(true);
	else if (!display_help_message) {
		if (input_file_list.Count() == 1 && m_pCmdLineOutputFile) {
			// we don't want HSF streaming when reading in
			m_bSavedHsfStreaming = CAppSettings::HsfStreaming;
			CAppSettings::HsfStreaming = false;

			// perform the translation
			H_WCS *input_file = input_file_list.RemoveFirst();
			OpenDocumentFile(static_cast<wchar_t const *>(input_file->encodedText()));
			delete input_file;

			// we need to make sure the reading thread completes before we try to export
			//   once the reading thread completes, it will perform the export in the CompleteCommandLineProcessing function
		}
		else if (input_file_list.Count() >= 1) {
			// load the files
			H_WCS *input_file;
			while (input_file = input_file_list.RemoveFirst()) {
				OpenDocumentFile(static_cast<wchar_t const *>(input_file->encodedText()));
				delete input_file;
			}
		}
	}

	input_file_list.DeleteItems();

	return TRUE;
}

void CSolidHoopsApp::CompleteCommandLineProcessing ( CSolidHoopsView * view ) {
	if (m_pCmdLineOutputFile == 0)
		return;

	view->SaveFile(static_cast<wchar_t const *>(m_pCmdLineOutputFile->encodedText()));
	delete m_pCmdLineOutputFile;
	m_pCmdLineOutputFile = 0;

	CAppSettings::HsfStreaming = m_bSavedHsfStreaming;

	PostQuitMessage(0);
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutSolidHoopsDlg : public CDialog
{
public:
	CAboutSolidHoopsDlg();

// Dialog Data
	//{{AFX_DATA(CAboutSolidHoopsDlg)
	//}}AFX_DATA
#ifdef PARASOLID
	enum { IDD = IDD_PARASOLIDABOUTBOX };
#endif // PARASOLID
#ifdef ACIS
	enum { IDD = IDD_ACISABOUTBOX };
#endif // ACIS
#ifdef GRANITE
	enum { IDD = IDD_PTCABOUTBOX };
#endif // GRANITE
#ifdef HOOPS_ONLY
	enum { IDD = IDD_HOOPSONLYABOUTBOX };
#endif // HOOPS_ONLY

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutSolidHoopsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutSolidHoopsDlg)
	afx_msg void OnVisitHoops3d();
	//}}AFX_MSG
#ifdef PARASOLID
	afx_msg void OnVisitParasolid();
#endif // PARASOLID
#ifdef ACIS
	afx_msg void OnVisitSpatial();
#endif // ACIS
#ifdef GRANITE
	afx_msg void OnVisitPtc();
#endif // GRANITE

	DECLARE_MESSAGE_MAP()
};

CAboutSolidHoopsDlg::CAboutSolidHoopsDlg() : CDialog(CAboutSolidHoopsDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutSolidHoopsDlg)
	//}}AFX_DATA_INIT
}

void CAboutSolidHoopsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutSolidHoopsDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutSolidHoopsDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutSolidHoopsDlg)
	ON_BN_CLICKED(IDC_VISIT_HOOPS3D, OnVisitHoops3d)
	//}}AFX_MSG_MAP
#ifdef PARASOLID
	ON_BN_CLICKED(IDC_VISIT_PARASOLID, OnVisitParasolid)
#endif // PARASOLID
#ifdef ACIS
	ON_BN_CLICKED(IDC_VISIT_SPATIAL, OnVisitSpatial)
#endif // ACIS
#ifdef GRANITE
	ON_BN_CLICKED(ID_VISIT_PTC, OnVisitPtc)
#endif // GRANITE

END_MESSAGE_MAP()

// App command to run the dialog
void CSolidHoopsApp::OnAppAbout()
{
	CAboutSolidHoopsDlg aboutDlg;
	aboutDlg.DoModal();
}

class CAboutDDBDlg : public CDialog
{
public:
	CAboutDDBDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDDBDlg)
	//}}AFX_DATA
	enum { IDD = IDD_DDBABOUTDLG };
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDDBDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDDBDlg::CAboutDDBDlg() : CDialog(CAboutDDBDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDDBDlg)
	//}}AFX_DATA_INIT
}

void CAboutDDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDDBDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDDBDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDDBDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSolidHoopsApp::OnDDBAbout()
{
	CAboutDDBDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHoopsApp commands

int CSolidHoopsApp::ExitInstance() 
{
	m_bShuttingDown = true;

#ifdef HOOPS_LEAD_TOOLS
	H_SAFE_DELETE( m_pIOUtilityLeadTools );
#endif

#ifdef HOOPS_DWG_IO
	H_SAFE_DELETE(m_pIOUtilityDwg);
#endif

#ifdef HOOPS_IV_IO
	H_SAFE_DELETE(m_pIOUtilityIV);
#endif

	//m_pCTDriver must be deleted before m_pHoopsDB
	if( m_pCTDriver )
	{
		m_pCTDriver->DestroyWindow();	// ref MSDN: TN017: Destroying Window Objects
		delete m_pCTDriver;
		m_pCTDriver = 0;
	}

	if (m_pHoopsDB)
	{
		delete m_pHoopsDB;
		m_pHoopsDB = 0;

#ifdef PARASOLID
		HP_Close();
#endif // PARASOLID

#ifdef ACIS
		outcome o = api_terminate_hoops_acis_bridge();
		check_outcome(o);
		o = api_stop_modeller();
		check_outcome(o);
		terminate_base();		
#endif // ACIS

#ifdef GRANITE
		HG_Close();
#endif // GRANITE

	}

	DeleteCriticalSection(&sweeten_lock);

	WriteSettingsToRegistry();

	delete m_pCmdLineDlg;
	delete m_pCmdLineOutputFile;

	return CHoopsApp::ExitInstance();
}

void CSolidHoopsApp::LoadUrl (CString & url)
{
	HKEY    html_owner_key		= 0;
	TCHAR*	html_owner			= 0;
	HKEY    classes_key         = 0;
	HKEY    browser_root_key    = 0;
	HKEY    browser_path_key    = 0;
	TCHAR*  browser_path		= 0;
	DWORD    string_size        = 0;
	DWORD    value_type;
	CString error_message		= "Unable to start your internet browser";

	// Try to find the exectuable of the default internet browser.
	// We do this by looking at who "owns" the ".htm" file format.
	if (ERROR_SUCCESS != RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,            // handle of open key
		_T("software\\classes\\.htm"),     // address of name of subkey to open
		0L,                            // reserved
		KEY_READ,                      // security access mask
		&html_owner_key) )             // address of handle of open key
	{
		AfxMessageBox (error_message);
	}
	// Determine length of string identifying html_owner.
	else if (ERROR_SUCCESS != RegQueryValueEx(
		html_owner_key,                // handle of key to query
		_T(""),                            // address of name of value to query
		0L,                            // reserved
		&value_type,                   // address of buffer for value type
		0,                          // address of data buffer
		&string_size))                 // address of data buffer size
	{
		AfxMessageBox (error_message);
	}
	// then allocate space to hold it.
	else if ((html_owner = new TCHAR[string_size]) == 0)
	{
		AfxMessageBox (error_message);
	}
	// Determine html_owner
	else if (ERROR_SUCCESS != RegQueryValueEx(
		html_owner_key,                // handle of key to query
		_T(""),                            // address of name of value to query
		0L,                            // reserved
		&value_type,                   // address of buffer for value type
		(LPBYTE)html_owner,            // address of data buffer
		&string_size) )                // address of data buffer size
	{
		AfxMessageBox (error_message);
	}
	// Need to find executable associated with html_owner
	// We now generate a path from the html_owner string.
	else if (ERROR_SUCCESS != RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,            // handle of open key
		_T("software\\classes"),           // address of name of subkey to open
		0L,                            // reserved
		KEY_READ,                      // security access mask
		&classes_key) )                // address of handle of open key
	{
		AfxMessageBox (error_message);
	}
	else if (ERROR_SUCCESS != RegOpenKeyEx(
		classes_key,                   // handle of open key
		html_owner,                    // address of name of subkey to open
		0L,                            // reserved
		KEY_READ,                      // security access mask
		&browser_root_key) )           // address of handle of open key
	{
		AfxMessageBox (error_message);
	}
	else if (ERROR_SUCCESS != RegOpenKeyEx(
		browser_root_key,              // handle of open key
		_T("shell\\open\\command"),        // address of name of subkey to open
		0L,                            // reserved
		KEY_READ,                      // security access mask
		&browser_path_key) )           // address of handle of open key
	{
		AfxMessageBox (error_message);
	}
	// Determine size of browser_path
	else if (ERROR_SUCCESS != RegQueryValueEx(
		browser_path_key,          // handle of key to query
		_T(""),                        // address of name of value to query
		0L,                        // reserved
		&value_type,               // address of buffer for value type
		NULL,                      // address of data buffer
		&string_size))             // address of data buffer size
	{
		AfxMessageBox (error_message);
	}
	else if ((browser_path = new TCHAR[string_size]) == 0)
	{
		AfxMessageBox (error_message);
	}
	// determine id_string
	else if (ERROR_SUCCESS != RegQueryValueEx(
		browser_path_key,          // handle of key to query
		_T(""),                        // address of name of value to query
		0L,                        // reserved
		&value_type,               // address of buffer for value type
		(LPBYTE)browser_path,      // address of data buffer
		&string_size) )            // address of data buffer size
	{
		AfxMessageBox (error_message);
	}
	else
	{
		// In order for this code to be compatible with both MSIE and Netscape,
		//   we are required to use the shell\\open\\command registry key which
		//   contains some extra characters at the end of the string.  Let's
		//   replace the %1 in the string with %s representing our URL

		// Make local copy of Browser Path
		CString browser_command(browser_path);

		// Find %1 and replace it with %s in preparation for sprintf
		int position = browser_command.Find(_T("%1"));

		if (position == -1)
		{
			// There was no percent sign for this command line,
			// so lets just assume that the URL goes on the end-of-the-line.

			// See if there is a close double-quotes, if so then put the
			// url inside them.

			if (browser_command.Right(1) == '"')
				browser_command = browser_command.Left(string_size - 1) + url + '"';
			else
				browser_command += " " + url;
		}
		else
		{
			// We found a %1 in the command string.
			// Replace it with the url
			browser_command  = browser_command.Left(position) +
				CString(url) +
				browser_command.Right(browser_command.GetLength( ) - position - 2);
		}

		WinExec (H_ASCII_TEXT(browser_command), SW_SHOWNORMAL);
	}

	// We may have had errors, so only close the keys if they were actually opened.
	if (html_owner_key)      RegCloseKey (html_owner_key);
	if (classes_key)         RegCloseKey (classes_key);
	if (browser_root_key)    RegCloseKey (browser_root_key);
	if (browser_path_key)    RegCloseKey (browser_path_key);

	delete []   html_owner;
	delete []   browser_path;
}

void CSolidHoopsApp::OnVisitHoops3d() 
{
	CString	url;

	url.Format(_T("www.techsoft3d.com"));
	LoadUrl(url);	
}

void CSolidHoopsApp::OnLoadHelp() 
{
	CString location;
	GetModuleFileName( AfxGetInstanceHandle(), location.GetBuffer(MVO_BUFFER_SIZE),  MVO_BUFFER_SIZE );
	location.ReleaseBuffer();

	// this will be something like c:\Program Files\HOOPS-1100\bin\nt_i386\hoopspartviewer.exe
	// climb up two levels to get to top level hoops installation directory
	for( int i = 0; i < 3; i++)
		location = location.Left(location.ReverseFind(_T('\\')));


#ifdef PARASOLID
	location = location + _T("\\docs\\ReferenceApplications\\UsingPHPartViewer_C.html");
#endif // PARASOLID

#ifdef ACIS
	location = location + _T("\\docs\\ReferenceApplications\\UsingAHPartViewer_C.html");
#endif // ACIS

#ifdef GRANITE
	location = location + _T("\\docs\\ReferenceApplications\\UsingGHPartViewer_C.html");
#endif // GRANITE

#ifdef HOOPS_ONLY
	location = location + _T("\\docs\\ReferenceApplications\\UsingHOOPSViewDemo_C.html");
#endif // HOOPS_ONLY

	LoadUrl(location);	
}

void CAboutSolidHoopsDlg::OnVisitHoops3d() 
{
	CSolidHoopsApp	*my_app;

	my_app = (CSolidHoopsApp *) AfxGetApp();
	my_app->OnVisitHoops3d();
}

#ifdef PARASOLID
void CSolidHoopsApp::OnVisitParasolid() 
{
	CString	url;

	url.Format(_T("www.parasolid.com"));
	LoadUrl(url);	
}

void CAboutSolidHoopsDlg::OnVisitParasolid() 
{
	CSolidHoopsApp	*my_app;

	my_app = (CSolidHoopsApp *) AfxGetApp();
	my_app->OnVisitParasolid();	
}
#endif //PARASOLID

#ifdef ACIS
void CSolidHoopsApp::OnVisitSpatial() 
{
	CString	url;

	url.Format(_T("www.spatial.com"));
	LoadUrl(url);	
}

void CAboutSolidHoopsDlg::OnVisitSpatial() 
{
	CSolidHoopsApp	*my_app;

	my_app = (CSolidHoopsApp *) AfxGetApp();
	my_app->OnVisitSpatial();	
}
#endif // ACIS


#ifdef GRANITE
void CSolidHoopsApp::OnVisitPtc() 
{
	CString	url;

	url.Format(_T("www.ptc.com"));
	LoadUrl(url);	
}

void CAboutSolidHoopsDlg::OnVisitPtc() 
{
	CSolidHoopsApp	*my_app;

	my_app = (CSolidHoopsApp *) AfxGetApp();
	my_app->OnVisitPtc();	
}
#endif // GRANITE


BOOL CSolidHoopsApp::OnIdle(LONG lCount) 
{
	CHoopsApp::OnIdle(lCount);


	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CSolidHoopsFrame *)m_pMainWnd)->GetActiveFrame();	
	if (!pChild || !pChild->GetActiveView() || strcmp(pChild->GetActiveView()->GetRuntimeClass()->m_lpszClassName, "CSolidHoopsView"))
		return 0;

	CSolidHoopsView *aview = (CSolidHoopsView *)pChild->GetActiveView();	

	if (aview == 0) 
		return 0;


	HSolidView *sview = (HSolidView *)((CSolidHoopsView *)aview)->GetSolidView();

	if (sview)
	{
		HBaseOperator *opbase = sview->GetOperator();

		if (!opbase->OperatorStarted() && strcmp(opbase->GetName(),"HOpCameraManipulate")==0)
		{

			HOpCameraManipulate *op = ((HOpCameraManipulate *)opbase);
			HOpCameraOrbit *op2 = ((HOpCameraManipulate *)opbase)->GetOrbitOperator();

			if (!m_bConstantSpin || op->GetLButtonDown() || (sview->GetModel()->GetBhvBehaviorManager()->IsPlaying() && sview->GetModel()->GetBhvBehaviorManager()->GetCameraUpdated()))
			{			    
				op2->m_Angle1 = op2->m_Angle2 = op2->m_Angle3 = 0;
				return 0;
			}

#ifdef ACIS
			bool is_hiddenline = false;
			bool is_brephiddenline = false;
			if (sview->GetRenderMode() == HRenderHiddenLine)
			{
				is_hiddenline = true;
				sview->SetRenderMode(HRenderHiddenLineFast);
			}
			if (sview->GetRenderMode() == HRenderBRepHiddenLine)
			{
				is_brephiddenline = true;
				sview->SetRenderMode(HRenderBRepHiddenLineFast);
			}
#endif	//ACIS

			HC_Open_Segment_By_Key(sview->GetSceneKey());
			{
				HC_Orbit_Camera(op2->m_Angle1,op2->m_Angle2);
				HC_Roll_Camera(op2->m_Angle3);			
			}
			HC_Close_Segment();
			sview->CameraPositionChanged();
			sview->ForceUpdate();

#ifdef ACIS
			if (is_hiddenline)
			{
				is_hiddenline = false;
				sview->SetRenderMode(HRenderHiddenLine);
			}
			if (is_brephiddenline)
			{
				is_brephiddenline = false;
				sview->SetRenderMode(HRenderBRepHiddenLine);
			}
#endif	// ACIS

		}			
	}
	/* sleep for just a very short time so that we don't hog 100% of 
	* the CPU with this idle loop. */
	Sleep( 10 );
	return 1;
}

void CSolidHoopsApp::OnConstantspin() 
{
	if (m_bConstantSpin)
		m_bConstantSpin = false;
	else
		m_bConstantSpin = true;
}

void CSolidHoopsApp::OnUpdateConstantspin(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CSolidHoopsFrame *)m_pMainWnd)->GetActiveFrame();	
	assert (pChild);
	CSolidHoopsView *view = (CSolidHoopsView *)pChild->GetActiveView();	

	if (view && (strcmp (view->GetRuntimeClass()->m_lpszClassName,"CSolidHoopsView" ) ==0 ))
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}



void CSolidHoopsApp::ProcessFilters(CString * filters, const char * file_types) 
{
	if(strstr(file_types, ";hsf;"))
		*filters += CString(_T("HOOPS Stream File (*.hsf)|*.hsf|"));

	if(strstr(file_types, ";hmf;"))
		*filters += CString(_T("HOOPS Metafile (*.hmf)|*.hmf|"));

	if(strstr(file_types, ";dwf;"))
		*filters += CString(_T("Autodesk DWF/DWFx (*.dwf; *.dwfx)|*.dwf; *.dwfx|"));

	if(strstr(file_types, ";u3d;"))
		*filters += CString(_T("Universal 3D (*.u3d)|*.u3d|"));

	if(strstr(file_types, ";dwg;"))
		*filters += CString(_T("AutoCAD DWG (*.dwg)|*.dwg|"));

	if(strstr(file_types, ";jt;"))
		*filters += CString(_T("UGS JT (*.jt)|*.jt|"));

	if(strstr(file_types, ";dxf;"))
		*filters += CString(_T("AutoCAD DXF (*.dxf)|*.dxf|"));

	if(strstr(file_types, ";html;"))
		*filters += CString(_T("HOOPS 3D Stream Control (*.html)|*.html|"));

	if(strstr(file_types, ";stl;"))
		*filters += CString(_T("Stereolithography Files(*.stl)|*.stl|"));

	if(strstr(file_types, ";obj;"))
		*filters += CString(_T("Alias Wavefront (*.obj)|*.obj|"));

	if(strstr(file_types, ";ooc;"))
		*filters += CString(_T("HOOPS Out of Core (*.ooc)|*.ooc|"));

	if(strstr(file_types, ";ply;"))
		*filters += CString(_T("PLY (*.ply)|*.ply|"));

	if(strstr(file_types, ";wrl;"))
		*filters += CString(_T("VRML (*.wrl)|*.wrl|"));

	if(strstr(file_types, ";iv;"))
		*filters += CString(_T("Open Inventor (*.iv)|*.iv|"));

	if(strstr(file_types, ";pdf;"))
		*filters += CString(_T("PDF (*.pdf)|*.pdf|"));

	if(strstr(file_types, ";ps;"))
		*filters += CString(_T("Postscript (*.ps)|*.ps|"));

	if(strstr(file_types, ";hp;"))
		*filters += CString(_T("HPGL2 (*.hp)|*.hp|"));

	if(strstr(file_types, ";cgm;"))
		*filters += CString(_T("CGM (*.cgm)|*.cgm|"));

	if(strstr(file_types, ";wmf;"))
		*filters += CString(_T("WMF Windows Metafile (*.wmf)|*.wmf|"));

	if(strstr(file_types, ";emf;"))
		*filters += CString(_T("EMF Enhanced Metafile (*.emf)|*.emf|"));

	if(strstr(file_types, ";jpg;"))
		*filters += CString(_T("JPEG (*.jpg; *.jpeg)|*.jpg; *.jpeg|"));

	if(strstr(file_types, ";bmp;"))
		*filters += CString(_T("BMP (*.bmp)|*.bmp|"));

	if(strstr(file_types, ";png;"))
		*filters += CString(_T("PNG (*.png)|*.png|"));

	if(strstr(file_types, ";tif;"))
		*filters += CString(_T("TIFF (*.tif; *.tiff)|*.tif; *.tiff|"));

	if(strstr(file_types, ";gif;"))
		*filters += CString(_T("GIF (*.gif)|*.gif|"));

	if(strstr(file_types, ";dgn;"))
		*filters += CString(_T("MicroStation DGN (*.dgn)|*.dgn|"));

	if(strstr(file_types, ";skp;"))
		*filters += CString(_T("Google SketchUp (*.skp)|*.skp|"));

	if(strstr(file_types, ";step;"))
		*filters += CString(_T("STEP (*.step)|*.step|"));

	if(strstr(file_types, ";iges;"))
		*filters += CString(_T("IGES (*.iges)|*.iges|"));

	if(strstr(file_types, ";x_t;"))
		*filters += CString(_T("Parasolid (*.x_t)|*.x_t|"));
}


void CSolidHoopsApp::CreateAllFileTypesString(CString * filters, const char * file_types) 
{
	int stringLength = (int)strlen(file_types);
	char extension[MVO_BUFFER_SIZE];

	*filters += CString(_T("All Supported Files |"));

	//strings have the following form ";jpeg:tiff;hsf;hmf;"

	int lastOccurence = stringLength-2;

	for (int i = stringLength-2; i > 0; i--)
	{
		if (file_types[i] == ';')
		{
			int offset = lastOccurence - i;
			memcpy(extension, &file_types[i+1], offset);

			extension[offset] = '\0';
			*filters += CString(_T("*."));
			*filters += CString(extension);
			if (i != 1)
				*filters += CString(_T(";"));

			lastOccurence = i-1;
		}
	}
}

//======================================================================
//	Author :Rajesh B			Created : 3/26/2001 5:16:32 PM
//======================================================================
//	Function :CSolidHoopsApp::OnFileOpen
//	Description :	Overriding the base class to present our dialog
//					box allowing user to select .hsf files too
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsApp::OnFileOpen() 
{
	CString filter = _T("");
	CString def_ext = _T(".hsf");

#ifdef INTEROP
	filter  = _T("Catia V5 Files (*.CATPart;*.CATProduct;*.CATShape;*.cgr)|*.CATPart;*.CATProduct;*.CATShape;*.cgr|");
	filter += _T("Catia V4 Files (*.model;*.session;*.exp)|*.model;*.session;*.exp|");
	filter += _T("ProE Files (*.prt;*.prt.*;*.xpr;*.xpr.*;*.asm;*.asm.*;*.xas;*.xas.*)|*.prt;*.prt.*;*.xpr;*.xpr.*;*.asm;*.asm.*;*.xas;*.xas.*|");
	filter += _T("IGES Files (*.igs;*.iges)|*.igs;*.iges|");
	filter += _T("STEP Files (*.stp;*.step)|*.stp;*.step|");
	filter += _T("VDA Files(*.vda)|*.VDA|");
	filter += _T("UG Files (*.prt)|*.prt|");
	filter += _T("Inventor Files (*.ipt;*.iam)|*.ipt;*.iam|");
	filter += _T("Solidworks Files (*.sldprt;*.sldasm)|*.sldprt;*.sldasm|");
	filter += _T("Parasolid Files (*.x_t*;*.xmt_*)|*.x_t*;*.xmt_*|");
	filter += _T("Acis Files (*.sat)|*.sat|");
#ifdef ACIS
	filter += _T("AcisHOOPS Stream Files (*.asf)|*.asf|");
#endif // ACIS
#ifdef PARASOLID
	filter += _T("ParaHOOPS Stream Files (*.psf)|*.psf|");
#endif // PARASOLID

	def_ext = _T(".CATPart");
#elif PARASOLID
	filter = _T("Parasolid Part Files (*.x_t*;*.xmt_*)|*.x_t*;*.xmt_*|ParaHOOPS Stream Files (*.psf)|*.psf|");
	def_ext = _T(".x_t");
#elif ACIS
   	filter = _T("Acis Files (*.sat;*.asat)|*.sat;*.asat|AcisHOOPS Stream Files (*.asf)|*.asf|");
	def_ext = _T(".sat");
#elif GRANITE
	filter = _T("ProE Files (*.prt;*.prt.*)|*.prt;*.prt.*|ProE Assemblies (*.asm;*.asm.*)|*.asm;*.asm.*|GraniteHOOPS Stream Files (*.gsf)|*.gsf|Parasolid Files (*.x_t;*.xmt_txt;x_b)|*.x_t;*.xmt_txt;*.xmb|IGES Files (*.igs)|*.igs|Acis Files (*.sat)|*.sat|STEP Files (*.stp;*.step)|*.stp;*.step|VDA Files (*.vda)|*.vda|Granite Neutral Files (*.g)|*.g|");
	def_ext = _T(".prt");
#endif 

	CreateAllFileTypesString(&filter, HDB::GetHIOManager()->GetInputHandlerTypes());
	filter += _T("|");

	// this adds file types that have HIO handlers and appear in ProcessFilters()
	ProcessFilters(&filter, HDB::GetHIOManager()->GetInputHandlerTypes());

	filter += _T("|");

	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	CFileDialog my_dlg(TRUE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter , NULL);
	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

	if (my_dlg.DoModal() == IDOK) {
		CString pathname;
		pathname = my_dlg.GetPathName();

		OpenDocumentFile(pathname);
		int end = pathname.ReverseFind('\\');
		pathname.Truncate(end);
		SetCurrentDirectory(pathname);
	}
}


//======================================================================
//	Author :Rajesh B			Created : 4/26/2002 5:17:43 PM
//======================================================================
//	Function :		CSolidHoopsApp::OnToolsOptions
//	Description :	Pops up the Options dialog for application-wide settings
//					These settings will be remembered in the registry
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsApp::OnToolsOptions() 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CSolidHoopsFrame *)m_pMainWnd)->GetActiveFrame();	
	CSolidHoopsView *aview = 0;
	HSolidView *sview = 0;
 
	if (pChild && pChild->GetActiveView() && strcmp(pChild->GetActiveView()->GetRuntimeClass()->m_lpszClassName, "CSolidHoopsView") == 0)		 
	{
		aview = (CSolidHoopsView *)pChild->GetActiveView();	
		if (aview)
			sview = (HSolidView *)((CSolidHoopsView *)aview)->GetSolidView();

	}	

	if (sview)
		sview->GetConstantFrameRateObject()->SetDisableIncreaseTemp(true);

	m_opt_dlg = new HOptionsDlg();
	m_opt_dlg->SetTitle("Partviewer Options");

	GeneralOptionsPage gen_opts;
	m_opt_dlg->AddPage( gen_opts, "General");

	PerformanceOptionsPage perf_opts;
	m_opt_dlg->AddPage( perf_opts, "Performance");

	AppearanceOptionsPage appear_opts;
	m_opt_dlg->AddPage( appear_opts, "Appearance");

	FileOptionsPage file_opts;
	m_opt_dlg->AddPage(file_opts, "File");

	HSFOptionsPage hsf_opts;
	m_opt_dlg->AddPage(hsf_opts, "HSF");

	InteractionOptionsPage interact_opts;
	m_opt_dlg->AddPage( interact_opts, "Interaction");

	SelectionOptionsPage selection_opts;
	m_opt_dlg->AddPage( selection_opts, "Selection");

	OutputOptionsPage output_opts;
	m_opt_dlg->AddPage( output_opts, "Output");

	GeometryOptionsPage geometry_opts;
	m_opt_dlg->AddPage( geometry_opts, "Geometry");

	CameraOptionsPage camera_opts;
	m_opt_dlg->AddPage( camera_opts, "Camera");

	LightingOptionsPage lighting_opts;
	m_opt_dlg->AddPage(lighting_opts, "Lighting");	
	
	EffectsOptionsPage effects_opts;
	m_opt_dlg->AddPage( effects_opts, "Effects");

#ifdef PARASOLID
	TessellationOptionsPage face_tess_page;
	m_opt_dlg->AddPage(face_tess_page, "Tessellation");
#endif // PARASOLID

#ifdef GRANITE
	TessellationOptionsPage face_tess_page;
	m_opt_dlg->AddPage(face_tess_page, "Tessellation");
#endif // GRANITE

	m_opt_dlg->DoModal();
	if (sview)
		sview->GetConstantFrameRateObject()->SetDisableIncreaseTemp(false);
	delete m_opt_dlg;
	m_opt_dlg = 0;
}


void CSolidHoopsApp::OnFilePrintOptions() 
{
//	CPrintOptionsDlg  print_opt_dlg;

//	print_opt_dlg.DoModal();

}



void CSolidHoopsApp::OnPerformanceDefault()
{
	PerformanceSettings perf;
	perf.SetMode(DefaultMode);	
}

void CSolidHoopsApp::OnUpdatePerformanceDefault(CCmdUI *pCmdUI)
{
	PerformanceSettings perf;
	if (perf.GetCurrentSetting() == DefaultMode)
      pCmdUI->SetCheck (1);
  else
      pCmdUI->SetCheck (0);

}

void CSolidHoopsApp::OnPerformanceHigh()
{
	PerformanceSettings perf;
	perf.SetMode(Optimal);
}

void CSolidHoopsApp::OnUpdatePerformanceHigh(CCmdUI *pCmdUI)
{
	PerformanceSettings perf;
	if (perf.GetCurrentSetting() == Optimal)
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);

}

void CSolidHoopsApp::OnPerformanceStaticModel()
{
	PerformanceSettings perf;
	if (perf.Show(StaticModel))
		perf.UnSet(StaticModel);
	else
		perf.SetMode(StaticModel);
}

void CSolidHoopsApp::OnUpdatePerformanceStaticModel(CCmdUI *pCmdUI)
{
	PerformanceSettings perf;
	if (perf.Show(StaticModel))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnPerformanceSegmentDisplayLists()
{
	PerformanceSettings perf;
	if (perf.Show(SegmentLevelDisplayLists))
		perf.UnSet(SegmentLevelDisplayLists);
	else
		perf.SetMode(SegmentLevelDisplayLists);
}

void CSolidHoopsApp::OnUpdatePerformanceSegmentDisplayLists(CCmdUI *pCmdUI)
{
	PerformanceSettings perf;
	if (perf.Show(SegmentLevelDisplayLists))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnPerformanceGeometryDisplayLists()
{
	PerformanceSettings perf;
	if (perf.Show(GeometryLevelDisplayLists))
		perf.UnSet(GeometryLevelDisplayLists);
	else
		perf.SetMode(GeometryLevelDisplayLists);
}

void CSolidHoopsApp::OnUpdatePerformanceGeometryDisplayLists(CCmdUI *pCmdUI)
{
	PerformanceSettings perf;
	if (perf.Show(GeometryLevelDisplayLists))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnPerformanceFixedFramerate()
{
	PerformanceSettings perf;
	if (perf.Show(FixedFramerate))
		perf.SetMode(CullingThreshold);
	else
		perf.SetMode(FixedFramerate);
}

void CSolidHoopsApp::OnUpdatePerformanceFixedFramerate(CCmdUI *pCmdUI)
{
	PerformanceSettings perf;
	if (perf.Show(FixedFramerate))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnPerformanceTargetFramerate()
{
	PerformanceSettings perf;
	if (perf.Show(TargetFramerate))
		perf.SetMode(CullingThreshold);
	else
		perf.SetMode(TargetFramerate);
}

void CSolidHoopsApp::OnUpdatePerformanceTargetFramerate(CCmdUI *pCmdUI)
{
	PerformanceSettings perf;
	if (perf.Show(TargetFramerate))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnEffectsNone()
{
	EffectSettings fx;
	fx.Set(None);
}

void CSolidHoopsApp::OnUpdateEffectsNone(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	if (fx.Show(None))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnEffectsFancy()
{
	EffectSettings fx;
	fx.Set(Fancy);
}

void CSolidHoopsApp::OnUpdateEffectsFancy(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	if (fx.Show(Fancy))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnEffectsAmbientOcclusion()
{
	EffectSettings fx;
	if (fx.Show(AmbientOcclusion))
		fx.UnSet(AmbientOcclusion);
	else
		fx.Set(AmbientOcclusion);
}

void CSolidHoopsApp::OnUpdateEffectsAmbientOcclusion(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	if (fx.Show(AmbientOcclusion))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnEffectsBloom()
{
	EffectSettings fx;
	if (fx.Show(Bloom))
		fx.UnSet(Bloom);
	else
		fx.Set(Bloom);
}

void CSolidHoopsApp::OnUpdateEffectsBloom(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	if (fx.Show(Bloom))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnEffectsFastSilhouetteEdges()
{
	EffectSettings fx;
	if (fx.Show(FastSilhouetteEdges))
		fx.UnSet(FastSilhouetteEdges);
	else
		fx.Set(FastSilhouetteEdges);
}

void CSolidHoopsApp::OnUpdateEffectsFastSilhouetteEdges(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
	HBaseView * pBaseView = 0;
	if (pActiveView 
		&& (pBaseView = pActiveView->GetHoopsView()) != 0 
		&& pBaseView->GetRenderMode() == HRenderFakeHiddenLine)
		pCmdUI->Enable(FALSE);
	else
	{
		pCmdUI->Enable(TRUE);
		if (fx.Show(FastSilhouetteEdges))
		  pCmdUI->SetCheck (1);
		else
		  pCmdUI->SetCheck (0);
	}
}

void CSolidHoopsApp::OnEffectsReflectionPlane()
{
	EffectSettings fx;
	if (fx.Show(ReflectionPlane))
		fx.UnSet(ReflectionPlane);
	else
	fx.Set(ReflectionPlane);
}

void CSolidHoopsApp::OnUpdateEffectsReflectionPlane(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	if (fx.Show(ReflectionPlane))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnEffectsShadowMaps()
{
	EffectSettings fx;
	if (fx.Show(ShadowMaps))
		fx.UnSet(ShadowMaps);
	else
		fx.Set(ShadowMaps);
}

void CSolidHoopsApp::OnUpdateShadowMaps(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	if (fx.Show(ShadowMaps))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}

void CSolidHoopsApp::OnEffectsSimpleShadows()
{
	EffectSettings fx;
	if (fx.Show(SimpleShadows))
		fx.UnSet(SimpleShadows);
	else
		fx.Set(SimpleShadows);
}

void CSolidHoopsApp::OnUpdateEffectsSimpleShadows(CCmdUI *pCmdUI)
{
	EffectSettings fx;
	if (fx.Show(SimpleShadows))
      pCmdUI->SetCheck (1);
	else
      pCmdUI->SetCheck (0);
}


#define bool2int(true__or__false)  (true__or__false) ? 1 : 0
#define UINT2bool(__uint__val)  (__uint__val > 0) ?  true: false


//======================================================================
//	Author :Rajesh B			Created : 4/26/2002 3:19:34 PM
//======================================================================
//	Function :		CSolidHoopsApp::ReadSettingsFromRegistry
//	Description :	Read all the application settings from the regsitry
//					For the detailed description of each entry and 
//					their default values see CAppSettings class
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsApp::ReadSettingsFromRegistry()
{
	//-- Near Camera Limit
	CAppSettings::NearCameraLimit = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NearCameraLimitEntry, CAppSettings::DefaultNearCameraLimit);

	//-- Output Options Settings
	CAppSettings::DPI = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DPIEntry, CAppSettings::DefaultDPI);
	CAppSettings::ForceGrayscale = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ForceGrayscaleEntry, CAppSettings::DefaultForceGrayscale));
	CAppSettings::bConserveMemory = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bConserveMemoryEntry, CAppSettings::DefaultbConserveMemory));
	CAppSettings::DocOpt = (HDocOutputOptions)GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DocOptEntry, CAppSettings::DefaultDocOpt);
	CAppSettings::ImageOpt = (HImageOutputOptions)GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImageOptEntry, CAppSettings::DefaultImageOpt);
	CAppSettings::OutputWidth = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OutputWidthEntry, CAppSettings::DefaultOutputWidth);
	CAppSettings::OutputHeight = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OutputHeightEntry, CAppSettings::DefaultOutputHeight);
	CAppSettings::PaperWidth = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PaperWidthEntry, CAppSettings::DefaultPaperWidth*1000.f) / 1000.0f;
	CAppSettings::PaperHeight = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PaperHeightEntry, CAppSettings::DefaultPaperHeight*1000.f) / 1000.0f;
	CAppSettings::bUseWindowColor = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bUseWindowColorEntry, CAppSettings::DefaultbUseWindowColor));

	//-- Geometry Options Settings
	CAppSettings::Budget = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BudgetEntry, CAppSettings::DefaultBudget);
	CAppSettings::ContinuedBudget = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ContinuedBudgetEntry, CAppSettings::DefaultContinuedBudget);
	CAppSettings::MaxDeviation = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxDeviationEntry, CAppSettings::DefaultMaxDeviation);
	CAppSettings::MaxAngle = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxAngleEntry, CAppSettings::DefaultMaxAngle);
	CAppSettings::MaxLength = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxLengthEntry, CAppSettings::DefaultMaxLength);
	CAppSettings::bViewIndependent = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bViewIndependentEntry, CAppSettings::DefaultbViewIndependent));

	//-- General Settings
	CAppSettings::HoopsDriver = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::HoopsDriverEntry, CAppSettings::DefaultHoopsDriver);
	CAppSettings::CheckHoopsDriver(); //If HoopsDriver isn't available, this will set it to something that is available
	CAppSettings::bDriverForceSoftware = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DriverForceSoftwareEntry, CAppSettings::DefaultbDriverForceSoftware));
	CAppSettings::bDriverDisplayStats = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DriverDisplayStatsEntry, CAppSettings::DefaultbDriverDisplayStats));
	CAppSettings::bAntiAliasing = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bAntiAliasingEntry, CAppSettings::DefaultbAntiAliasing));
	CAppSettings::bDisplayAxisTriad = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisplayAxisTriadEntry, CAppSettings::DefaultbDisplayAxisTriad ));

	//CAppSettings::bBackplaneCulling = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BackplaneCullingEntry, CAppSettings::DefaultbBackplaneCulling));
	CAppSettings::CoordinateSystemHandedness = (HandednessMode) GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CoordinateSystemHandednessEntry, CAppSettings::DefaultCoordinateSystemHandedness );
	CAppSettings::RenderMode = (HRenderMode) GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::RenderModeEntry, CAppSettings::DefaultRenderMode);
	CAppSettings::ShadowRenderingMode = (HShadowRenderingMode) GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowRenderingEntry, CAppSettings::DefaultShadowRenderingMode);
	CAppSettings::ViewAxis = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::ViewAxisEntry, CAppSettings::DefaultViewAxis);
	CAppSettings::TransparencyStyle = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::TransparencyStyleEntry, CAppSettings::DefaultTransparencyStyle);
	CAppSettings::TransparencySorting = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::TransparencySortingEntry, CAppSettings::DefaultTransparencySorting);
	CAppSettings::TransparencyDepthPeelingLayers = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::TransparencyDepthPeelingLayersEntry, CAppSettings::DefaultTransparencyDepthPeelingLayers);
	CAppSettings::DepthWriting = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DepthWritingEntry, CAppSettings::DefaultDepthWriting ));
	CAppSettings::AntialiasingLevel = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AntialiasingLevelEntry, CAppSettings::DefaultAntialiasingLevel);
	CAppSettings::PolygonHandedness = (ModelHandedness) GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PolygonHandednessEntry, CAppSettings::DefaultPolygonHandedness);
	CAppSettings::bSmoothTransition = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SmoothTransitionEntry, CAppSettings::DefaultbSmoothTransition));
	CAppSettings::bWorldHandedness = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WorldHandednessEntry, CAppSettings::DefaultbWorldHandedness));
	CAppSettings::ProjectionMode = (ProjMode)GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ProjectionModeEntry, CAppSettings::DefaultProjectionMode);
	CAppSettings::DisplayList = (DisplayListType)GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisplayListEntry, CAppSettings::DefaultDisplayList);
	CAppSettings::MultiThreading = (MultiThreadingType)GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MultiThreadingEntry, CAppSettings::DefaultMultiThreading);
	CAppSettings::VisibilitySelection = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::VisibilitySelectionEntry, CAppSettings::DefaultVisibilitySelection));
	CAppSettings::DynamicHighlighting = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DynamicHighlightingEntry, CAppSettings::DefaultDynamicHighlighting));
	CAppSettings::DetailSelection = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DetailSelectionEntry, CAppSettings::DefaultDetailSelection));
	CAppSettings::TimerBasedUpdate = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::TimerBasedUpdateEntry, CAppSettings::DefaultTimerBasedUpdate));
	CAppSettings::OcclusionCulling = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OcclusionCullingEntry, CAppSettings::DefaultOcclusionCulling));
	CAppSettings::OcclusionThreshold = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OcclusionThresholdEntry, CAppSettings::DefaultOcclusionThreshold);
	CAppSettings::StaticModel = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::StaticModelEntry, CAppSettings::DefaultStaticModel));
	CAppSettings::DisableEditing = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisableEditingEntry, CAppSettings::DefaultDisableEditing));
	CAppSettings::LMVModel = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LMVModelEntry, CAppSettings::DefaultLMVModel));
	CAppSettings::LineAntialiasing = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LineAntialiasingEntry, CAppSettings::DefaultLineAntialiasing));
	CAppSettings::TextAntialiasing = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::TextAntialiasingEntry, CAppSettings::DefaultTextAntialiasing));
	CAppSettings::ShowDebugMenu = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShowDebugMenuEntry, CAppSettings::DefaultShowDebugMenu));
	CAppSettings::HiddenLineMode = (HLRMode)GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HiddenLineModeEntry, CAppSettings::DefaultHiddenLineMode);
	CAppSettings::Spriting = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SpritingEntry, CAppSettings::DefaultSpriting));
	CAppSettings::UpdateCutGeometry = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UpdateCutGeometryEntry, CAppSettings::DefaultUpdateCutGeometry));
	CAppSettings::UpdateShadows = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UpdateShadowsEntry, CAppSettings::DefaultUpdateShadows));
	CAppSettings::bUseSelectBox = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bUseSelectBoxEntry, CAppSettings::DefaultbUseSelectBox));
	CAppSettings::StereoMode = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::StereoModeEntry, CAppSettings::DefaultStereoMode));
	CAppSettings::StereoSeparation = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::StereoSeparationEntry, CAppSettings::DefaultStereoSeparation);
	CAppSettings::HighlightMode = (HSelectionHighlightMode)(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HighlightModeEntry, CAppSettings::DefaultHighlightMode));
	CAppSettings::TransparencyLevel = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::TransparencyLevelEntry, CAppSettings::DefaultTransparencyLevel*1000.f) / 1000.0f;
	CAppSettings::RelatedSelectionLimit = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::RelatedSelectionLimitEntry, CAppSettings::DefaultRelatedSelectionLimit);
	CAppSettings::DoubleBuffer = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DoubleBufferEntry, CAppSettings::DefaultDoubleBuffer));

	if(!CAppSettings::StaticModel)
		CAppSettings::DisableEditing = false;

	//-- Appearance Settings
	CAppSettings::GreekingMode= GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::GreekingModeEntry, CAppSettings::DefaultGreekingMode);
	CAppSettings::GreekingUnits= GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::GreekingUnitsEntry, CAppSettings::DefaultGreekingUnits);
	CAppSettings::OverrideDefaultAppWindowPosition = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OverrideDefaultAppWindowPositionEntry, CAppSettings::DefaultOverrideDefaultAppWindowPosition));
	CAppSettings::AppWindowPosition = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::AppWindowPositionEntry, CAppSettings::DefaultAppWindowPosition);
	CAppSettings::LineWeight = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::LineWeightEntry, CAppSettings::DefaultLineWeight);
	CAppSettings::WindowBackgroundTopColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WindowBackgroundTopColorEntry, CAppSettings::DefaultWindowBackgroundTopColor);
	CAppSettings::WindowBackgroundBottomColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WindowBackgroundBottomColorEntry, CAppSettings::DefaultWindowBackgroundBottomColor);
	CAppSettings::PolygonSelectionColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PolygonSelectionColorEntry, CAppSettings::DefaultPolygonSelectionColor);
	CAppSettings::LineSelectionColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LineSelectionColorEntry, CAppSettings::DefaultLineSelectionColor);
	CAppSettings::MarkerSelectionColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MarkerSelectionColorEntry, CAppSettings::DefaultMarkerSelectionColor);
	CAppSettings::SelectionColorTransparency = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SelectionColorTransparencyEntry, CAppSettings::DefaultSelectionColorTransparency);
	CAppSettings::MarkupColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MarkupColorEntry, CAppSettings::DefaultMarkupColor);
	CAppSettings::MarkupWeight = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MarkupWeightEntry, CAppSettings::DefaultMarkupWeight);
	CAppSettings::GreekingLimit = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GreekingLimitEntry, CAppSettings::DefaultGreekingLimit);
	CAppSettings::WalkAvatarHeight = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkAvatarHeightEntry, CAppSettings::DefaultWalkAvatarHeight);
	CAppSettings::WalkStepHeightUp = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkStepHeightUpEntry, CAppSettings::DefaultWalkStepHeightUp);
	CAppSettings::CullingThreshold = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CullingThresholdEntry, CAppSettings::DefaultCullingThreshold);
	CAppSettings::CullingThresholdSet = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CullingThresholdSetEntry, CAppSettings::DefaultCullingThresholdSet);
	CAppSettings::DynamicAdjustment = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DynamicAdjustmentEntry, CAppSettings::DefaultDynamicAdjustment);
	CAppSettings::UseLods = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseLodsEntry, CAppSettings::DefaultUseLods);
	CAppSettings::CurrentFramerateMode = (FramerateMode)GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CurrentFramerateModeEntry, (int)CAppSettings::DefaultCurrentFramerateMode);
	CAppSettings::MaxThreshold = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxThresholdEntry, CAppSettings::DefaultMaxThreshold);
	CAppSettings::HardCutoff = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HardCutoffEntry, CAppSettings::DefaultHardCutoff);
	CAppSettings::DetailSteps = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DetailStepsEntry, CAppSettings::DefaultDetailSteps);
	CAppSettings::UseFramerate = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseFramerateEntry, CAppSettings::DefaultUseFramerate));
	CAppSettings::WalkStepHeightDown = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkStepHeightDownEntry, CAppSettings::DefaultWalkStepHeightDown);
	CAppSettings::ShadowRes = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowResEntry, CAppSettings::DefaultShadowRes);
	CAppSettings::ShadowBlur = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowBlurEntry, CAppSettings::DefaultShadowBlur);
	CAppSettings::bColorInterpolation = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ColorInterpolationEntry, CAppSettings::DefaultbColorInterpolation));
	CAppSettings::bGrayScaleSelection = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GrayScaleSelectionEntry, CAppSettings::DefaultbGrayScaleSelection));
	CAppSettings::bDisplaceSelection = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisplaceSelectionEntry, CAppSettings::DefaultbDisplaceSelection));
	CAppSettings::bWalkUseKeyboard = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkUseKeyboardEntry, CAppSettings::DefaultbWalkUseKeyboard));
	CAppSettings::bWalkAutomaticHeight = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkAutomaticHeightEntry, CAppSettings::DefaultbWalkAutomaticHeight));
	CAppSettings::bWalkSnapToFloor = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkSnapToFloorEntry, CAppSettings::DefaultbWalkSnapToFloor));
	CAppSettings::bWalkCollision = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkCollisionEntry, CAppSettings::DefaultbWalkCollision));
	CAppSettings::bCiIsolines = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CiIsolinesEntry, CAppSettings::DefaultbCiIsolines));
	CAppSettings::bCiByValue = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CiByValueEntry, CAppSettings::DefaultbCiByValue));
	CAppSettings::bCiByColormapIndex = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CiByColormapIndexEntry, CAppSettings::DefaultbCiByColormapIndex));
	CAppSettings::bHideOverlappedText = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HideOverlappedTextEntry, CAppSettings::DefaultHideOverlappedText));
	CAppSettings::bSplatRendering = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SplatRenderingEntry, CAppSettings::DefaultbSplatRendering));
	CAppSettings::bFastMarkers = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FastMarkersEntry, CAppSettings::DefaultbFastMarkers));
	CAppSettings::bUseGreeking = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseGreekingEntry, CAppSettings::DefaultbUseGreeking));
	CAppSettings::FontName = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::FontNameEntry, CAppSettings::DefaultFontName);
	CAppSettings::FontSize = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::FontSizeEntry, CAppSettings::DefaultFontSize);
	CAppSettings::FontUnits = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::FontUnitsEntry, CAppSettings::DefaultFontUnits);
	CAppSettings::ShadowColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowColorEntry, CAppSettings::DefaultShadowColor);

	//-- Shadow Settings
	CAppSettings::ShadowMode = (HShadowMode) GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowModeEntry, CAppSettings::DefaultShadowMode);
	CAppSettings::bShadowMap = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowMapEntry, CAppSettings::bDefaultShadowMap));
	CAppSettings::bReflectionPlane = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionPlaneEntry, CAppSettings::bDefaultReflectionPlane));
	CAppSettings::nSMSamples = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SMSamplesEntry, CAppSettings::nDefaultSMSamples);
	CAppSettings::nSMResolution = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SMResolutionEntry, CAppSettings::nDefaultSMResolution);
	CAppSettings::ShadowOpacity = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowOpacityEntry, CAppSettings::DefaultShadowOpacity*1000.f)/1000.f;
	CAppSettings::bReflectionFading = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionFadingEntry, CAppSettings::bDefaultReflectionFading));
	CAppSettings::ReflectionOpacity = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionOpacityEntry, CAppSettings::DefaultReflectionOpacity*1000.f)/1000.f;

	//-- File Settings
	CAppSettings::EmbedHSFThumbnail = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EmbedHSFThumbnailEntry, CAppSettings::DefaultEmbedHSFThumbnail));	
	CAppSettings::bReadSimpleHsf = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReadSimpleHsfEntry, CAppSettings::DefaultbReadSimpleHsf));
	CAppSettings::HsfExportVersion = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HsfExportVersionEntry, CAppSettings::DefaultHsfExportVersion);
	CAppSettings::bExportTopolInfo = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ExportTopolInfoEntry, CAppSettings::DefaultbExportTopolInfo));
	CAppSettings::bCompressVertices = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressVerticesEntry, CAppSettings::DefaultbCompressVertices));
	CAppSettings::NumVertexBits = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NumVertexBitsEntry, CAppSettings::DefaultNumVertexBits);
	CAppSettings::bCompressNormals = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressNormalsEntry, CAppSettings::DefaultbCompressNormals));
	CAppSettings::NumNormalBits = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NumNormalBitsEntry, CAppSettings::DefaultNumNormalBits);
	CAppSettings::bCompressParameters = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressParametersEntry, CAppSettings::DefaultbCompressParameters));
	CAppSettings::NumParameterBits = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NumParameterBitsEntry, CAppSettings::DefaultNumParameterBits);
	CAppSettings::bExportLines = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ExportLinesEntry, CAppSettings::DefaultbExportLines));
	CAppSettings::bExportDictionary = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ExportDictionaryEntry, CAppSettings::DefaultbExportDictionary));
	CAppSettings::bEnableInstancing = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EnableInstancingEntry, CAppSettings::DefaultbEnableInstancing));
	CAppSettings::bSaveLogFile = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SaveLogFileEntry, CAppSettings::DefaultbSaveLogFile));
	CAppSettings::bCompressConnectivity = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressConnectivityEntry, CAppSettings::DefaultbCompressConnectivity));
	CAppSettings::ModelerExportFileVer = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ModelerExportFileVerEntry, CAppSettings::DefaultModelerExportFileVer);
	CAppSettings::PartsDirectory = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::PartsDirectoryEntry, CAppSettings::DefaultPartsDirectory);
	CAppSettings::MaterialLibraryDirectory = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::MaterialLibraryDirectoryEntry, CAppSettings::DefaultMaterialLibraryDirectory);
	CAppSettings::DWGTextureDirectory = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::DWGTextureDirectoryEntry, CAppSettings::DefaultDWGTextureDirectory);
	CAppSettings::bFlushOnLoad = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FlushOnLoadEntry, CAppSettings::DefaultbFlushOnLoad));
	CAppSettings::bRestoreAnnotations = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::RestoreAnnotationsEntry, CAppSettings::DefaultbRestoreAnnotations));
	CAppSettings::bPrcFaceEdgeVertexSelectability = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PrcFaceEdgeVertexSelectabilityEntry, CAppSettings::DefaultbPrcFaceEdgeVertexSelectability));
	CAppSettings::bImportDWGviaBstream = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImportDWGviaBstreamEntry, CAppSettings::DefaultbImportDWGviaBstream));
	CAppSettings::bImportDWGXData = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImportDWGXDataEntry, CAppSettings::DefaultbImportDWGXData));
	CAppSettings::DWGDeviation = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::DWGDeviationEntry, CAppSettings::DefaultDWGDeviation);
	CAppSettings::HsfStreaming = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HsfStreamingEntry, CAppSettings::DefaultHsfStreaming));
	CAppSettings::EnableTristrips = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EnableTristripsEntry, CAppSettings::DefaultEnableTristrips));
	CAppSettings::bImportAllLayouts = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImportAllLayoutsEntry, CAppSettings::DefaultbImportAllLayouts));
	CAppSettings::LoadPVOFiles = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LoadPVOFilesEntry, CAppSettings::DefaultLoadPVOFiles));
	CAppSettings::EmbedMaterials = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EmbedMaterialsEntry, CAppSettings::DefaultEmbedMaterials));

	//For DGN
	CAppSettings::bIgnoreInvisibleEntities = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IgnoreInvisibleEntity, CAppSettings::DefaultbIgnoreInvisibleEntities));
	CAppSettings::DGNFactorForCone = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::DGNFactorForConeEntry , CAppSettings::DefaultDGNFactorForCone);
	CAppSettings::DGNFactorForSmartSolids = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::DGNFactorForSmartSolidsEntry , CAppSettings::DefaultDGNFactorForSmartSolids );



	//-- Interaction Settings
	CAppSettings::csQuickMovesType = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::QuickMovesTypeEntry, CAppSettings::DefaultcsQuickMovesType);

	//-- Effects Settings
	CAppSettings::Jitter = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::JitterEntry, CAppSettings::DefaultJitter));
	CAppSettings::ReflectionBlur = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionBlurEntry, CAppSettings::DefaultReflectionBlur);
	CAppSettings::ReflectionHither = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionHitherEntry, CAppSettings::DefaultReflectionHither*1000.f)/1000.f;
	CAppSettings::ReflectionYon = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionYonEntry, CAppSettings::DefaultReflectionYon*1000.f)/1000.f;
	CAppSettings::ReflectionUseBlur = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionUseBlurEntry, CAppSettings::DefaultReflectionUseBlur));
	CAppSettings::ReflectionUseAttenuation = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionUseAttenuationEntry, CAppSettings::DefaultReflectionUseAttenuation));

	CAppSettings::ViewDependentShadowMap = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ViewDependentShadowMapEntry, CAppSettings::DefaultViewDependentShadowMap));
	CAppSettings::UseFastAmbient = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseFastAmbientEntry, CAppSettings::DefaultUseFastAmbient));
	CAppSettings::FastAmbientStrength = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FastAmbientStrengthEntry, CAppSettings::DefaultFastAmbientStrength*10000.0f)/10000.0f;
	CAppSettings::HQAmbientOcclusion = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HQAmbientOcclusionEntry, CAppSettings::DefaultHQAmbientOcclusion));
	CAppSettings::UseFastSilhouette = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseFastSilhouetteEntry, CAppSettings::DefaultUseFastSilhouette));
	CAppSettings::FastSilhouetteTolerance = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FastSilhouetteToleranceEntry, CAppSettings::DefaultFastSilhouetteTolerance*10000.0f)/10000.0f;
	CAppSettings::HeavyExteriorSilhouette = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HeavyExteriorSilhouetteEntry, CAppSettings::DefaultHeavyExteriorSilhouette));
	CAppSettings::IgnoreTransparency = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IgnoreTransparencyEntry, CAppSettings::DefaultIgnoreTransparency));
	CAppSettings::UseLightVector = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseLightVectorEntry, CAppSettings::DefaultUseLightVector));
	CAppSettings::LightVector.x = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightVectorEntry+" X", CAppSettings::DefaultLightVector.x*10000.0f)/10000.0f;
	CAppSettings::LightVector.y = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightVectorEntry+" Y", CAppSettings::DefaultLightVector.y*10000.0f)/10000.0f;
	CAppSettings::LightVector.z = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightVectorEntry+" Z", CAppSettings::DefaultLightVector.z*10000.0f)/10000.0f;


	//-- Selection Settings
	CAppSettings::csRefSelType = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::csRefSelTypeEntry, CAppSettings::csDefaultRefSelType);

	//-- Camera Settings
	CAppSettings::NavigationPanel = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NavigationPanelEntry, CAppSettings::DefaultNavigationPanel));

	//-- Lighting Settings
	CAppSettings::HemisphericAmbient = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HemisphericAmbientEntry, CAppSettings::DefaultHemisphericAmbient));	
	CAppSettings::AmbientTopColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientTopColorEntry, CAppSettings::DefaultAmbientTopColor);
	CAppSettings::AmbientBottomColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientBottomColorEntry, CAppSettings::DefaultAmbientBottomColor);
	CAppSettings::LightFollowsCamera = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightFollowsCameraEntry, CAppSettings::DefaultLightFollowsCamera));	
	CAppSettings::bLightScaling = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bLightScalingEntry, CAppSettings::DefaultbLightScaling));
	CAppSettings::LightScaleFactor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightScaleFactorEntry, CAppSettings::DefaultLightScaleFactor);
	CAppSettings::GoochColorMap = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::GoochColorMapEntry, CAppSettings::DefaultGoochColorMap);
	CAppSettings::UseAmbientUpVector = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseAmbientUpVectorEntry, CAppSettings::DefaultUseAmbientUpVector));
	CAppSettings::AmbientUpVector.x = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientUpVectorEntry+" X", CAppSettings::DefaultAmbientUpVector.x*10000.0f)/10000.0f;
	CAppSettings::AmbientUpVector.y = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientUpVectorEntry+" Y", CAppSettings::DefaultAmbientUpVector.y*10000.0f)/10000.0f;
	CAppSettings::AmbientUpVector.z = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientUpVectorEntry+" Z", CAppSettings::DefaultAmbientUpVector.z*10000.0f)/10000.0f;
	CAppSettings::GoochWeight = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochWeightEntry, CAppSettings::DefaultGoochWeight*10000.0f)/10000.0f;
	CAppSettings::GoochColorHigh = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColorHighEntry, CAppSettings::DefaultGoochColorHigh*10000.0f)/10000.0f;
	CAppSettings::GoochColor1 = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor1Entry, CAppSettings::DefaultGoochColor1);
	CAppSettings::GoochColor2 = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor2Entry, CAppSettings::DefaultGoochColor2);
	CAppSettings::GoochColor3 = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor3Entry, CAppSettings::DefaultGoochColor3);
	CAppSettings::GoochColor4 = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor4Entry, CAppSettings::DefaultGoochColor4);
	CAppSettings::GoochColor5 = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor5Entry, CAppSettings::DefaultGoochColor5);
	CAppSettings::GoochColor6 = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor6Entry, CAppSettings::DefaultGoochColor6);
	CAppSettings::UseBloom = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseBloomEntry, CAppSettings::DefaultUseBloom));
	CAppSettings::BloomStrength = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BloomStrengthEntry, CAppSettings::DefaultBloomStrength*10000.0f)/10000.0f;
	CAppSettings::BloomBlur = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BloomBlurEntry, CAppSettings::DefaultBloomBlur);
	CAppSettings::BloomShape = (HBloomShape) GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BloomShapeEntry, CAppSettings::DefaultBloomShape);
	CAppSettings::LightCount = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightCountEntry, CAppSettings::DefaultLightCount);

	//-- Performance Page
	CAppSettings::FramerateTime = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FramerateTimeEntry, CAppSettings::DefaultFramerateTime*10000.0f)/10000.0f;
#ifdef PARASOLID
	CAppSettings::SchemaPath = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::SchemaPathEntry, CAppSettings::DefaultSchemaPath);
	CAppSettings::bFlattenAssemblies = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FlattenAssembliesEntry, CAppSettings::DefaultbFlattenAssemblies));
	CAppSettings::bBinaryX_TFiles = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BinaryX_TFilesEntry, CAppSettings::DefaultbBinaryX_TFiles));
#endif // PARASOLID

	//-- Tessellation Settings
#ifdef PARASOLID
	CAppSettings::IsCurveChordTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsCurveChordTolEntry, CAppSettings::DefaultIsCurveChordTol);
	CAppSettings::IsCurveChordAngTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsCurveChordAngTolEntry, CAppSettings::DefaultIsCurveChordAngTol);
	CAppSettings::IsFacetPlaneTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsFacetPlaneTolEntry, CAppSettings::DefaultIsFacetPlaneTol);
	CAppSettings::IsFacetPlaneAngTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsFacetPlaneAngTolEntry, CAppSettings::DefaultIsFacetPlaneAngTol);
	CAppSettings::IsSurfacePlaneTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsSurfacePlaneTolEntry, CAppSettings::DefaultIsSurfacePlaneTol);
	CAppSettings::IsSurfacePlaneAngTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsSurfacePlaneAngTolEntry, CAppSettings::DefaultIsSurfacePlaneAngTol);
	CAppSettings::IsLineCurveChordTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsLineCurveChordTolEntry, CAppSettings::DefaultIsLineCurveChordTol);
	CAppSettings::IsLineCurveChordAngTol = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsLineCurveChordAngTolEntry, CAppSettings::DefaultIsLineCurveChordAngTol);

	CAppSettings::CurveChordTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::CurveChordTolEntry, CAppSettings::DefaultCurveChordTol);
	CAppSettings::CurveChordAngTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::CurveChordAngTolEntry, CAppSettings::DefaultCurveChordAngTol);
	CAppSettings::FacetPlaneTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::FacetPlaneTolEntry, CAppSettings::DefaultFacetPlaneTol);
	CAppSettings::FacetPlaneAngTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::FacetPlaneAngTolEntry, CAppSettings::DefaultFacetPlaneAngTol);
	CAppSettings::SurfacePlaneTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::SurfacePlaneTolEntry, CAppSettings::DefaultSurfacePlaneTol);
	CAppSettings::SurfacePlaneAngTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::SurfacePlaneAngTolEntry, CAppSettings::DefaultSurfacePlaneAngTol);
	CAppSettings::LineCurveChordTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::LineCurveChordTolEntry, CAppSettings::DefaultLineCurveChordTol);
	CAppSettings::LineCurveChordAngTol = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::LineCurveChordAngTolEntry, CAppSettings::DefaultLineCurveChordAngTol);

	CAppSettings::FacetMatch = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FacetMatchEntry, CAppSettings::DefaultFacetMatch);
#endif // PARASOLID

#ifdef GRANITE
	CAppSettings::AngularTolerance = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::AngularToleranceEntry, CAppSettings::DefaultAngularTolerance);
	CAppSettings::PlanarTolerance = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::PlanarToleranceEntry, CAppSettings::DefaultAngularTolerance);
	CAppSettings::TessellationTolerance = GetProfileString( CAppSettings::RegOptionsSection, CAppSettings::TessellationToleranceEntry, CAppSettings::DefaultTessellationTolerance);
#endif // GRANITE

	CAppSettings::ShowEveryTick = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShowEveryTickEntry, CAppSettings::DefaultShowEveryTick));
	CAppSettings::ShowCollisions = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShowCollisionsEntry, CAppSettings::DefaultShowCollisions));
	CAppSettings::UpdateCamera = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UpdateCameraEntry, CAppSettings::DefaultUpdateCamera));
	CAppSettings::JumpToKeyframe = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::JumpToKeyframeEntry, CAppSettings::DefaultJumpToKeyframe));
	CAppSettings::DisableCFR = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisableCFREntry, CAppSettings::DefaultDisableCFR));
	CAppSettings::ChildStartMaximized = UINT2bool(GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ChildStartMaximizedEntry, CAppSettings::DefaultChildStartMaximized));
	CAppSettings::FakeHLRColor = GetProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FakeHLRColorEntry, CAppSettings::DefaultFakeHLRColor);

}

//======================================================================
//	Author :Rajesh B			Created : 4/26/2002 3:20:21 PM
//======================================================================
//	Function :	CSolidHoopsApp::WriteSettingsToRegistry
//	Description :	Write all the application settings to the regsitry
//					For the detailed description of each entry and 
//					their default values see CAppSettings class
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CSolidHoopsApp::WriteSettingsToRegistry()
{
	//-- Near Camera Limit
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NearCameraLimitEntry, CAppSettings::NearCameraLimit);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightScaleFactorEntry, CAppSettings::LightScaleFactor);

	//-- Output Options Settings
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DPIEntry, CAppSettings::DPI);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ForceGrayscaleEntry, bool2int(CAppSettings::ForceGrayscale) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bConserveMemoryEntry, bool2int(CAppSettings::bConserveMemory) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DocOptEntry, CAppSettings::DocOpt );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImageOptEntry, CAppSettings::ImageOpt );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OutputWidthEntry, CAppSettings::OutputWidth);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OutputHeightEntry, CAppSettings::OutputHeight);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PaperWidthEntry, (int)(CAppSettings::PaperWidth * 1000));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PaperHeightEntry, (int)(CAppSettings::PaperHeight * 1000));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bUseWindowColorEntry, bool2int(CAppSettings::bUseWindowColor) );

	//-- Geometry Settings
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BudgetEntry, CAppSettings::Budget);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ContinuedBudgetEntry, CAppSettings::ContinuedBudget);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxDeviationEntry, CAppSettings::MaxDeviation);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxAngleEntry, CAppSettings::MaxAngle);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxLengthEntry, CAppSettings::MaxLength);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bViewIndependentEntry, CAppSettings::bViewIndependent);

	//-- General Settings
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::HoopsDriverEntry, CAppSettings::HoopsDriver);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DriverForceSoftwareEntry, bool2int(CAppSettings::bDriverForceSoftware) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DriverDisplayStatsEntry, bool2int(CAppSettings::bDriverDisplayStats) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bAntiAliasingEntry, bool2int(CAppSettings::bAntiAliasing) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisplayAxisTriadEntry, bool2int(CAppSettings::bDisplayAxisTriad) );
	//WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BackplaneCullingEntry, bool2int(CAppSettings::bBackplaneCulling) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CoordinateSystemHandednessEntry, CAppSettings::CoordinateSystemHandedness );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::RenderModeEntry, CAppSettings::RenderMode);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowRenderingEntry, CAppSettings::ShadowRenderingMode);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::ViewAxisEntry, CAppSettings::ViewAxis);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::TransparencyStyleEntry, CAppSettings::TransparencyStyle);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::TransparencySortingEntry, CAppSettings::TransparencySorting);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::TransparencyDepthPeelingLayersEntry, CAppSettings::TransparencyDepthPeelingLayers);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DepthWritingEntry, bool2int(CAppSettings::DepthWriting) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AntialiasingLevelEntry, CAppSettings::AntialiasingLevel);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PolygonHandednessEntry, CAppSettings::PolygonHandedness);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SmoothTransitionEntry, CAppSettings::bSmoothTransition);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WorldHandednessEntry, CAppSettings::bWorldHandedness);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ProjectionModeEntry, CAppSettings::ProjectionMode);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisplayListEntry, CAppSettings::DisplayList);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MultiThreadingEntry, CAppSettings::MultiThreading);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::StaticModelEntry, bool2int(CAppSettings::StaticModel) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisableEditingEntry, bool2int(CAppSettings::DisableEditing) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LMVModelEntry, bool2int(CAppSettings::LMVModel) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::VisibilitySelectionEntry, CAppSettings::VisibilitySelection);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DynamicHighlightingEntry, CAppSettings::DynamicHighlighting);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DetailSelectionEntry, CAppSettings::DetailSelection);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::TimerBasedUpdateEntry, CAppSettings::TimerBasedUpdate);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OcclusionCullingEntry, CAppSettings::OcclusionCulling);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OcclusionThresholdEntry, CAppSettings::OcclusionThreshold);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LineAntialiasingEntry, CAppSettings::LineAntialiasing);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::TextAntialiasingEntry, CAppSettings::TextAntialiasing);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HiddenLineModeEntry, CAppSettings::HiddenLineMode);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SpritingEntry, CAppSettings::Spriting);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UpdateCutGeometryEntry, CAppSettings::UpdateCutGeometry);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UpdateShadowsEntry, CAppSettings::UpdateShadows);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bUseSelectBoxEntry, CAppSettings::bUseSelectBox);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::StereoModeEntry, CAppSettings::StereoMode );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::StereoSeparationEntry, CAppSettings::StereoSeparation );	
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HighlightModeEntry, CAppSettings::HighlightMode);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::TransparencyLevelEntry, (int)(CAppSettings::TransparencyLevel*1000.f));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::RelatedSelectionLimitEntry, CAppSettings::RelatedSelectionLimit );	
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DoubleBufferEntry, bool2int(CAppSettings::DoubleBuffer) );

	//-- Appearance Settings
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::GreekingModeEntry, CAppSettings::GreekingMode);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::GreekingUnitsEntry, CAppSettings::GreekingUnits);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::OverrideDefaultAppWindowPositionEntry, bool2int(CAppSettings::OverrideDefaultAppWindowPosition) );
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::AppWindowPositionEntry, CAppSettings::AppWindowPosition);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::LineWeightEntry, CAppSettings::LineWeight);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WindowBackgroundTopColorEntry, CAppSettings::WindowBackgroundTopColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WindowBackgroundBottomColorEntry, CAppSettings::WindowBackgroundBottomColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PolygonSelectionColorEntry, CAppSettings::PolygonSelectionColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LineSelectionColorEntry, CAppSettings::LineSelectionColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MarkerSelectionColorEntry, CAppSettings::MarkerSelectionColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SelectionColorTransparencyEntry, CAppSettings::SelectionColorTransparency);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MarkupColorEntry, CAppSettings::MarkupColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MarkupWeightEntry, CAppSettings::MarkupWeight);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GreekingLimitEntry, CAppSettings::GreekingLimit);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkAvatarHeightEntry, CAppSettings::WalkAvatarHeight);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkStepHeightUpEntry, CAppSettings::WalkStepHeightUp);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CullingThresholdEntry, CAppSettings::CullingThreshold);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::MaxThresholdEntry, CAppSettings::MaxThreshold);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HardCutoffEntry, CAppSettings::HardCutoff);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CullingThresholdSetEntry, CAppSettings::CullingThresholdSet);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DynamicAdjustmentEntry, CAppSettings::DynamicAdjustment);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseLodsEntry, CAppSettings::UseLods);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CurrentFramerateModeEntry, (int)CAppSettings::CurrentFramerateMode);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DetailStepsEntry, CAppSettings::DetailSteps);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseFramerateEntry, bool2int(CAppSettings::UseFramerate) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkStepHeightDownEntry, CAppSettings::WalkStepHeightDown);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowResEntry, CAppSettings::ShadowRes);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowBlurEntry, CAppSettings::ShadowBlur);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ColorInterpolationEntry, bool2int(CAppSettings::bColorInterpolation) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GrayScaleSelectionEntry, bool2int(CAppSettings::bGrayScaleSelection) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisplaceSelectionEntry, bool2int(CAppSettings::bDisplaceSelection) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkUseKeyboardEntry, bool2int(CAppSettings::bWalkUseKeyboard) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkAutomaticHeightEntry, bool2int(CAppSettings::bWalkAutomaticHeight) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkSnapToFloorEntry, bool2int(CAppSettings::bWalkSnapToFloor) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::WalkCollisionEntry, bool2int(CAppSettings::bWalkCollision) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CiIsolinesEntry, bool2int(CAppSettings::bCiIsolines) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CiByValueEntry, bool2int(CAppSettings::bCiByValue) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CiByColormapIndexEntry, bool2int(CAppSettings::bCiByColormapIndex) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HideOverlappedTextEntry, bool2int(CAppSettings::bHideOverlappedText) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SplatRenderingEntry, bool2int(CAppSettings::bSplatRendering) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FastMarkersEntry, bool2int(CAppSettings::bFastMarkers) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseGreekingEntry, bool2int(CAppSettings::bUseGreeking) );
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::FontNameEntry, CAppSettings::FontName );
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::FontSizeEntry, CAppSettings::FontSize );
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::FontUnitsEntry, CAppSettings::FontUnits );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowColorEntry, CAppSettings::ShadowColor);

	//-- Shadow Settings
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowModeEntry, CAppSettings::ShadowMode);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowMapEntry, bool2int(CAppSettings::bShadowMap));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionPlaneEntry, bool2int(CAppSettings::bReflectionPlane));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SMSamplesEntry, CAppSettings::nSMSamples);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SMResolutionEntry, CAppSettings::nSMResolution);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShadowOpacityEntry, (int)(CAppSettings::ShadowOpacity * 1000) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionFadingEntry, bool2int(CAppSettings::bReflectionFading));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionOpacityEntry, (int)(CAppSettings::ReflectionOpacity * 1000));

	//-- File Settings
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EmbedHSFThumbnailEntry, bool2int(CAppSettings::EmbedHSFThumbnail));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReadSimpleHsfEntry, bool2int(CAppSettings::bReadSimpleHsf) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HsfExportVersionEntry, CAppSettings::HsfExportVersion);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ExportTopolInfoEntry, bool2int(CAppSettings::bExportTopolInfo) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressVerticesEntry, bool2int(CAppSettings::bCompressVertices) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NumVertexBitsEntry, CAppSettings::NumVertexBits);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressNormalsEntry, bool2int(CAppSettings::bCompressNormals) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NumNormalBitsEntry, CAppSettings::NumNormalBits);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressParametersEntry, bool2int(CAppSettings::bCompressParameters) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NumParameterBitsEntry, CAppSettings::NumParameterBits);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ExportLinesEntry, bool2int(CAppSettings::bExportLines ));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ExportDictionaryEntry, bool2int(CAppSettings::bExportDictionary) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EnableInstancingEntry, bool2int(CAppSettings::bEnableInstancing) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::SaveLogFileEntry, bool2int(CAppSettings::bSaveLogFile) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::CompressConnectivityEntry, bool2int(CAppSettings::bCompressConnectivity) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ModelerExportFileVerEntry, CAppSettings::ModelerExportFileVer);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::PartsDirectoryEntry, CAppSettings::PartsDirectory);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::DWGTextureDirectoryEntry, CAppSettings::DWGTextureDirectory);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::MaterialLibraryDirectoryEntry, CAppSettings::MaterialLibraryDirectory);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FlushOnLoadEntry, bool2int(CAppSettings::bFlushOnLoad) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::RestoreAnnotationsEntry, bool2int(CAppSettings::bRestoreAnnotations) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::PrcFaceEdgeVertexSelectabilityEntry, bool2int(CAppSettings::bPrcFaceEdgeVertexSelectability) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImportDWGviaBstreamEntry, bool2int(CAppSettings::bImportDWGviaBstream));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImportDWGXDataEntry, bool2int(CAppSettings::bImportDWGXData));
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::DWGDeviationEntry, CAppSettings::DWGDeviation);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HsfStreamingEntry, bool2int(CAppSettings::HsfStreaming));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EnableTristripsEntry, bool2int(CAppSettings::EnableTristrips));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ImportAllLayoutsEntry, bool2int(CAppSettings::bImportAllLayouts));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LoadPVOFilesEntry, bool2int(CAppSettings::LoadPVOFiles));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::EmbedMaterialsEntry, bool2int(CAppSettings::EmbedMaterials));

	//For DGN
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IgnoreInvisibleEntity, bool2int(CAppSettings::bIgnoreInvisibleEntities));
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::DGNFactorForConeEntry, CAppSettings::DGNFactorForCone);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::DGNFactorForSmartSolidsEntry, CAppSettings::DGNFactorForSmartSolids);



	//-- Interaction Settings
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::QuickMovesTypeEntry, CAppSettings::csQuickMovesType);

	//-- Effects Settings
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::JitterEntry, bool2int(CAppSettings::Jitter));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionBlurEntry, CAppSettings::ReflectionBlur);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionHitherEntry, CAppSettings::ReflectionHither*1000.f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionYonEntry, CAppSettings::ReflectionYon*1000.f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionUseBlurEntry, bool2int(CAppSettings::ReflectionUseBlur));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ReflectionUseAttenuationEntry, bool2int(CAppSettings::ReflectionUseAttenuation));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ViewDependentShadowMapEntry, bool2int(CAppSettings::ViewDependentShadowMap));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseFastAmbientEntry, bool2int(CAppSettings::UseFastAmbient));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FastAmbientStrengthEntry, CAppSettings::FastAmbientStrength*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HQAmbientOcclusionEntry, bool2int(CAppSettings::HQAmbientOcclusion));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseFastSilhouetteEntry, bool2int(CAppSettings::UseFastSilhouette));	
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FastSilhouetteToleranceEntry, CAppSettings::FastSilhouetteTolerance*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HeavyExteriorSilhouetteEntry, bool2int(CAppSettings::HeavyExteriorSilhouette));	
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IgnoreTransparencyEntry, bool2int(CAppSettings::IgnoreTransparency));	
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseLightVectorEntry, bool2int(CAppSettings::UseLightVector));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightVectorEntry+" X", CAppSettings::LightVector.x*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightVectorEntry+" Y", CAppSettings::LightVector.y*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightVectorEntry+" Z", CAppSettings::LightVector.z*10000.0f);

	//-- Selection Settings
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::csRefSelTypeEntry, CAppSettings::csRefSelType);

	//-- Camera Settings
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::NavigationPanelEntry, bool2int(CAppSettings::NavigationPanel));	

	//-- Lighting Settings
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::HemisphericAmbientEntry, bool2int(CAppSettings::HemisphericAmbient));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientTopColorEntry, CAppSettings::AmbientTopColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientBottomColorEntry, CAppSettings::AmbientBottomColor);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightFollowsCameraEntry, bool2int(CAppSettings::LightFollowsCamera));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::bLightScalingEntry, bool2int(CAppSettings::bLightScaling));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightScaleFactorEntry, CAppSettings::LightScaleFactor);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::GoochColorMapEntry, CAppSettings::GoochColorMap);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseAmbientUpVectorEntry, bool2int(CAppSettings::UseAmbientUpVector));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientUpVectorEntry+" X", CAppSettings::AmbientUpVector.x*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientUpVectorEntry+" Y", CAppSettings::AmbientUpVector.y*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::AmbientUpVectorEntry+" Z", CAppSettings::AmbientUpVector.z*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochWeightEntry, CAppSettings::GoochWeight*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColorHighEntry, CAppSettings::GoochColorHigh*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor1Entry, CAppSettings::GoochColor1);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor2Entry, CAppSettings::GoochColor2);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor3Entry, CAppSettings::GoochColor3);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor4Entry, CAppSettings::GoochColor4);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor5Entry, CAppSettings::GoochColor5);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::GoochColor6Entry, CAppSettings::GoochColor6);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::LightCountEntry, CAppSettings::LightCount);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UseBloomEntry, bool2int(CAppSettings::UseBloom));
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BloomStrengthEntry, CAppSettings::BloomStrength*10000.0f);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BloomBlurEntry, CAppSettings::BloomBlur);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BloomShapeEntry, (int)CAppSettings::BloomShape);

	//-- Performance Page
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FramerateTimeEntry, CAppSettings::FramerateTime*10000.0f);

#ifdef PARASOLID
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::SchemaPathEntry, CAppSettings::SchemaPath);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FlattenAssembliesEntry, bool2int(CAppSettings::bFlattenAssemblies) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::BinaryX_TFilesEntry, bool2int(CAppSettings::bBinaryX_TFiles) );
#endif // PARASOLID

	//-- Tessellation Settings

#ifdef PARASOLID
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsCurveChordTolEntry, CAppSettings::IsCurveChordTol);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsCurveChordAngTolEntry, CAppSettings::IsCurveChordAngTol);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsFacetPlaneTolEntry, CAppSettings::IsFacetPlaneTol);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsFacetPlaneAngTolEntry, CAppSettings::IsFacetPlaneAngTol);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsSurfacePlaneTolEntry, CAppSettings::IsSurfacePlaneTol);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsSurfacePlaneAngTolEntry, CAppSettings::IsSurfacePlaneAngTol);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsLineCurveChordTolEntry, CAppSettings::IsLineCurveChordTol);
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::IsLineCurveChordAngTolEntry, CAppSettings::IsLineCurveChordAngTol);

	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::CurveChordTolEntry, CAppSettings::CurveChordTol);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::CurveChordAngTolEntry, CAppSettings::CurveChordAngTol);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::FacetPlaneTolEntry, CAppSettings::FacetPlaneTol);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::FacetPlaneAngTolEntry, CAppSettings::FacetPlaneAngTol);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::SurfacePlaneTolEntry, CAppSettings::SurfacePlaneTol);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::SurfacePlaneAngTolEntry, CAppSettings::SurfacePlaneAngTol);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::LineCurveChordTolEntry, CAppSettings::LineCurveChordTol);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::LineCurveChordAngTolEntry, CAppSettings::LineCurveChordAngTol);

	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FacetMatchEntry, CAppSettings::FacetMatch);
#endif // PARASOLID

#ifdef GRANITE
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::AngularToleranceEntry, CAppSettings::AngularTolerance);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::PlanarToleranceEntry, CAppSettings::PlanarTolerance);
	WriteProfileString( CAppSettings::RegOptionsSection, CAppSettings::TessellationToleranceEntry, CAppSettings::TessellationTolerance);
#endif // GRANITE

	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShowEveryTickEntry, bool2int(CAppSettings::ShowEveryTick) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ShowCollisionsEntry, bool2int(CAppSettings::ShowCollisions) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::UpdateCameraEntry, bool2int(CAppSettings::UpdateCamera) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::JumpToKeyframeEntry, bool2int(CAppSettings::JumpToKeyframe) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::DisableCFREntry, bool2int(CAppSettings::DisableCFR) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::ChildStartMaximizedEntry, bool2int(CAppSettings::ChildStartMaximized) );
	WriteProfileInt( CAppSettings::RegOptionsSection, CAppSettings::FakeHLRColorEntry, CAppSettings::FakeHLRColor );
}

void CSolidHoopsApp::CommitAllOptions()
{
	if(m_opt_dlg)
	{
		HOptionsPage * opt_pg = 0;

		for(int i = 0; i<m_opt_dlg->GetPageCount(); ++i)
		{
			opt_pg = m_opt_dlg->GetPage(i);
			opt_pg->OnButtonApply();
		}
	}
}

void CSolidHoopsApp::RefreshAllOptions()
{
	if(m_opt_dlg)
	{
		HOptionsPage * opt_pg = 0;

		for(int i = 0; i<m_opt_dlg->GetPageCount(); ++i)
		{
			opt_pg = m_opt_dlg->GetPage(i);
			opt_pg->OnInitDialog();
		}
	}
}

static CString generate_reg_hive_name()
{
	CString ret = "Software\\";
	int i = 0;
	char procname[MVO_BUFFER_SIZE];
	GetModuleFileNameA(NULL, procname, MVO_BUFFER_SIZE);

	while(procname[i]!='\0') ++i;  //walk to end of string
	while(procname[i]!='.' && i>0) --i;
	procname[i] = '\0'; //remove .exe
	while(procname[i]!='\\' && procname[i]!='/' && i>0) --i; //walk back to the beginning of the name
	++i;

	ret += CAppSettings::CompanyName;
	ret += '\\';
	ret += &procname[i];
	ret += '\\';
	ret += CAppSettings::RegOptionsSection;

	return ret;
}

#define OPTION_IO_READ	1
#define OPTION_IO_WRITE	2
static int option_io_common(int read_write, CString const & fname)
{
	HKEY open_reg = 0;
	CString reghive = generate_reg_hive_name();
	int ret = 0;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, reghive, 0, KEY_ALL_ACCESS, &open_reg) == ERROR_SUCCESS)
	{
		TOKEN_PRIVILEGES priv;
		HANDLE handle = NULL;
		
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &handle);
		if(read_write == OPTION_IO_READ)
			LookupPrivilegeValue(NULL, SE_RESTORE_NAME, &priv.Privileges[0].Luid);
		else //if(read_write == OPTION_IO_WRITE)
			LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &priv.Privileges[0].Luid);			
		priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		priv.PrivilegeCount = 1;

		if(AdjustTokenPrivileges(handle, FALSE, &priv, 0, 0, 0))
		{
			LONG filestate = ERROR_SUCCESS;
			if(read_write == OPTION_IO_READ)
				filestate = RegRestoreKey(open_reg, fname, REG_FORCE_RESTORE);
			else //if(read_write == OPTION_IO_WRITE)
			{
				DeleteFile(fname);
				filestate = RegSaveKey(open_reg, fname, NULL);
				if(filestate != ERROR_SUCCESS)
					DeleteFile(fname);
			}

			if(filestate == ERROR_SUCCESS)
				ret = 1;
			else
				AfxMessageBox(_T("File I/O failed! Please ensure UAC is disabled."));
		}
		else
			AfxMessageBox(_T("Administrator privileges are required to use this feature."));
		
		CloseHandle(handle);
		RegCloseKey(open_reg);
	}
	
	return ret;
}

void CSolidHoopsApp::ImportOptions(CString const & fname)
{
	if(option_io_common(OPTION_IO_READ, fname))
	{
		ReadSettingsFromRegistry();
		RefreshAllOptions();
	}
}

void CSolidHoopsApp::ExportOptions(CString const & fname)
{
	CommitAllOptions();
	WriteSettingsToRegistry();
	option_io_common(OPTION_IO_WRITE, fname);
}

void CSolidHoopsApp::LoadFileOptions(CString const & fname)
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CSolidHoopsFrame *)m_pMainWnd)->GetActiveFrame();	
	assert (pChild);
	CSolidHoopsView *view = (CSolidHoopsView *)pChild->GetActiveView();	
	if (!view && CAppSettings::LoadPVOFiles)
	{
		char str_data[MVO_BUFFER_SIZE];
		int i=0;
		OFSTRUCT junk;
		sprintf(str_data, "%s", H_ASCII_TEXT(fname));
		while(str_data[i]!='\0') ++i;  //walk to end of string
		while(str_data[i]!='.' && i>0) --i;  //walk back to the file extension
		if(i != 0)
		{
			str_data[++i] = 'p';
			str_data[++i] = 'v';
			str_data[++i] = 'o';
			str_data[++i] = '\0';
			
			if(OpenFile(str_data, &junk, OF_EXIST) != HFILE_ERROR)
				ImportOptions(str_data);
		}
	}
}

#ifdef HOOPS_QA
#ifndef _DEBUG

int CSolidHoopsApp::Run() 
{

	try
	{
		return CHoopsApp::Run();
	}
	catch (...)
	{
		// should eventually add code here that access the TestComplete log and 
		// and writes a message indicating that an exception occurred

		var TestCompleteServ, w, s, manager;

		int state;

		// Returns TestComplete as OLE object.

		// If TestComplete is not running, GetOleObject launches it.

		TestCompleteServ = Sys["GetOleObject"]("TestComplete.Application.3");

		manager = TestCompleteServ["Manager"];

		if ((CString)manager["Project"]["FileName"] != "")
		{
			state = manager["State"];

			if (state == 3)
				TestCompleteServ["Manager"]["Log"]["Error"]("Exception occurred; have a nice day.", "", 2, 1, 0x00FFFF, 0xFF0000);

		}

		return 1;

	}
}

#endif
#endif
