//************************************************************************** //* HSF Exporter based on:
//* AscExp.cpp	- Ascii File Exporter
//* 
//* By Christer Janson
//* Kinetix Development
//*
//* January 20, 1997 CCJ Initial coding
//*
//* This module contains the DLL startup functions
//*
//* Copyright (c) 1997, All Rights Reserved. 
//***************************************************************************

#include "hsftomaxexp.h"

#include "BStream.h"
#include "BOpcodeShell.h"

#include "HUtilityXMLParser.h"

HINSTANCE hInstance;
int controlsInit = FALSE;

static BOOL showPrompts;
static BOOL exportSelected;

// Class ID. These must be unique and randomly generated!!
// If you use this as a sample project, this is the first thing
// you should change!
#define HsfExp_CLASS_ID	Class_ID(0x85548e0a, 0x4a26450d)

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved) 
{
	hInstance = hinstDLL;

	// Initialize the custom controls. This should be done only once.
	if (!controlsInit) {
		controlsInit = TRUE;
		InitCustomControls(hInstance);
		InitCommonControls();
	}
	
	return (TRUE);
}


__declspec( dllexport ) const TCHAR* LibDescription() 
{
	return GetString(IDS_LIBDESCRIPTION);
}

/// MUST CHANGE THIS NUMBER WHEN ADD NEW CLASS 
__declspec( dllexport ) int LibNumberClasses() 
{
	return 1;
}


__declspec( dllexport ) ClassDesc* LibClassDesc(int i) 
{
	switch(i) {
	case 0: return GetHsfExpDesc();
	default: return 0;
	}
}

__declspec( dllexport ) ULONG LibVersion() 
{
	return VERSION_3DSMAX;
}

// Let the plug-in register itself for deferred loading
__declspec( dllexport ) ULONG CanAutoDefer()
{
	return 1;
}

class HsfExpClassDesc:public ClassDesc {
public:
	int				IsPublic() { return 1; }
	void*			Create(BOOL loading = FALSE) { return new HsfExp; } 
	const TCHAR*	ClassName() { return GetString(IDS_HsfExp); }
	SClass_ID		SuperClassID() { return SCENE_EXPORT_CLASS_ID; } 
	Class_ID		ClassID() { return HsfExp_CLASS_ID; }
	const TCHAR*	Category() { return GetString(IDS_CATEGORY); }
};

static HsfExpClassDesc HsfExpDesc;

ClassDesc* GetHsfExpDesc()
{
	return &HsfExpDesc;
}

TCHAR *GetString(int id)
{
	static TCHAR buf[256];

	if (hInstance)
		return LoadString(hInstance, id, buf, sizeof(buf)) ? buf : NULL;

	return NULL;
}

HsfExp::HsfExp()
{
	// These are the default values that will be active when 
	// the exporter is ran the first time.
	// After the first session these options are sticky.
	bIncludeMesh = TRUE;
	bIncludeAnim = TRUE;
	bIncludeMtl =  TRUE;
	bIncludeMeshAnim =  FALSE;
	bIncludeCamLightAnim = FALSE;
	bIncludeIKJoints = FALSE;
	bIncludeNormals  =  FALSE;
	bIncludeTextureCoords = FALSE;
	bIncludeVertexColors = FALSE;
	bIncludeObjGeom = TRUE;
	bIncludeObjShape = TRUE;
	bIncludeObjCamera = TRUE;
	bIncludeObjLight = TRUE;
	bIncludeObjTextures = TRUE;
	bIncludeObjHelper = TRUE;
	bAlwaysSample = FALSE;
	bCameraAsAnimation = TRUE;
	bInactiveByDefault = FALSE;

	bConnectivityCompression = FALSE;
	bImageCompression = TRUE;
	bVertexCompression = TRUE;
	bNormalCompression = TRUE;
	bSpecForEnv = TRUE;
	bDisableEnv = FALSE;
	bFlipAxis = FALSE;
	m_VertexCompressionBits = 36;
	m_NormalCompressionBits = 24;
	m_ImageCompressionValue = 75;
	m_handedness = DEFAULT_HANDED;	


	nKeyFrameStep = 5;
	nMeshFrameStep = 5;
	nPrecision = 4;
	nStaticFrame = 0;


	m_min.x = 1000000;
	m_min.y = 1000000;
	m_min.z = 1000000;

	m_max.x = -1000000;
	m_max.y = -1000000;
	m_max.z = -1000000;
}



HsfExp::~HsfExp()
{
}

int HsfExp::ExtCount()
{
	return 1;
}

const TCHAR * HsfExp::Ext(int n)
{
	switch(n) {
	case 0:
		// This cause a static string buffer overwrite
		// return GetString(IDS_EXTENSION1);
		return _T("hsf");
	}
	return _T("");
}

const TCHAR * HsfExp::LongDesc()
{
	return GetString(IDS_LONGDESC);
}

const TCHAR * HsfExp::ShortDesc()
{
	return GetString(IDS_SHORTDESC);
}

const TCHAR * HsfExp::AuthorName() 
{
	return _T("Christer Janson");
}

const TCHAR * HsfExp::CopyrightMessage() 
{
	return GetString(IDS_COPYRIGHT);
}

const TCHAR * HsfExp::OtherMessage1() 
{
	return _T("");
}

const TCHAR * HsfExp::OtherMessage2() 
{
	return _T("");
}

unsigned int HsfExp::Version()
{
	return 100;
}

static INT_PTR CALLBACK AboutBoxDlgProc(HWND hWnd, UINT msg, 
	WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		CenterWindow(hWnd, GetParent(hWnd)); 
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hWnd, 1);
			break;
		}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}       

void HsfExp::ShowAbout(HWND hWnd)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutBoxDlgProc, 0);
}


// Dialog proc
static INT_PTR CALLBACK ExportDlgProc(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	Interval animRange;
	ISpinnerControl  *spin;

	HsfExp *exp = (HsfExp*)GetWindowLongPtr(hWnd,GWLP_USERDATA); 
	switch (msg) {
	case WM_INITDIALOG:
		exp = (HsfExp*)lParam;
		SetWindowLongPtr(hWnd,GWLP_USERDATA,lParam); 
		CenterWindow(hWnd, GetParent(hWnd)); 
		CheckDlgButton(hWnd, IDC_MESHDATA, exp->GetIncludeMesh()); 
		CheckDlgButton(hWnd, IDC_ANIMKEYS, exp->GetIncludeAnim()); 
		CheckDlgButton(hWnd, IDC_MATERIAL, exp->GetIncludeMtl());
		CheckDlgButton(hWnd, IDC_MESHANIM, exp->GetIncludeMeshAnim()); 
		CheckDlgButton(hWnd, IDC_CAMLIGHTANIM, exp->GetIncludeCamLightAnim()); 
#ifndef DESIGN_VER
		CheckDlgButton(hWnd, IDC_IKJOINTS, exp->GetIncludeIKJoints()); 
#endif // !DESIGN_VER
		CheckDlgButton(hWnd, IDC_NORMALS,  exp->GetIncludeNormals()); 
		CheckDlgButton(hWnd, IDC_TEXCOORDS,exp->GetIncludeTextureCoords()); 
		CheckDlgButton(hWnd, IDC_VERTEXCOLORS,exp->GetIncludeVertexColors()); 
		CheckDlgButton(hWnd, IDC_OBJ_GEOM,exp->GetIncludeObjGeom()); 
		CheckDlgButton(hWnd, IDC_OBJ_SHAPE,exp->GetIncludeObjShape()); 
		CheckDlgButton(hWnd, IDC_OBJ_CAMERA,exp->GetIncludeObjCamera()); 
		CheckDlgButton(hWnd, IDC_OBJ_LIGHT,exp->GetIncludeObjLight()); 
		CheckDlgButton(hWnd, IDC_OBJ_TEXTURES,exp->GetIncludeObjTextures()); 		CheckDlgButton(hWnd, IDC_OBJ_FLIPAXIS,exp->GetFlipAxis()); 
		CheckDlgButton(hWnd, IDC_OBJ_HELPER,exp->GetIncludeObjHelper());

		CheckDlgButton(hWnd, IDC_CONNECTIVITY_COMPRESSION, exp->GetConnectivityCompression()); 
		CheckDlgButton(hWnd, IDC_VERTEX_COMPRESSION, exp->GetVertexCompression()); 
		CheckDlgButton(hWnd, IDC_NORMAL_COMPRESSION, exp->GetNormalCompression()); 
		CheckDlgButton(hWnd, IDC_IMAGE_COMPRESSION, exp->GetImageCompression()); 

		CheckDlgButton(hWnd, IDC_SPECULAR_FOR_ENVIRONMENT, exp->GetSpecForEnv()); 
		CheckDlgButton(hWnd, IDC_DISABLE_ENV, exp->GetDisableEnv()); 

		CheckRadioButton(hWnd, IDC_RADIO_USEKEYS, IDC_RADIO_SAMPLE, 
			exp->GetAlwaysSample() ? IDC_RADIO_SAMPLE : IDC_RADIO_USEKEYS);

		switch(exp->GetHandedness())
		{
		case LEFT_HANDED:
			CheckRadioButton(hWnd, IDC_RADIO_LEFTHANDED, IDC_RADIO_DEFAULTHANDED, IDC_RADIO_LEFTHANDED);
			break;
		case RIGHT_HANDED:
			CheckRadioButton(hWnd, IDC_RADIO_LEFTHANDED, IDC_RADIO_DEFAULTHANDED, IDC_RADIO_RIGHTHANDED);
			break;
		case DEFAULT_HANDED:
			CheckRadioButton(hWnd, IDC_RADIO_LEFTHANDED, IDC_RADIO_DEFAULTHANDED, IDC_RADIO_DEFAULTHANDED);
			break;
		}

		CheckDlgButton(hWnd, IDC_CAMERA_AS_ANIMATIONS, exp->GetCameraAsAnimation()); 
		CheckDlgButton(hWnd, IDC_INACTIVE_BY_DEFAULT, exp->GetInactiveByDefault()); 
		
		// Setup the spinner controls for the controller key sample rate 
		spin = GetISpinner(GetDlgItem(hWnd, IDC_CONT_STEP_SPIN)); 
		spin->LinkToEdit(GetDlgItem(hWnd,IDC_CONT_STEP), EDITTYPE_INT ); 
		spin->SetLimits(1, 100, TRUE); 
		spin->SetScale(1.0f);
		spin->SetValue(exp->GetKeyFrameStep() ,FALSE);
		ReleaseISpinner(spin);

		spin = GetISpinner(GetDlgItem(hWnd, IDC_VERTEX_COMPRESSION_BITS_SPIN)); 
		spin->LinkToEdit(GetDlgItem(hWnd,IDC_VERTEX_COMPRESSION_BITS), EDITTYPE_INT ); 
		spin->SetLimits(24, 96, TRUE); 
		spin->SetScale(1.0f);
		spin->SetValue(exp->GetVertexCompressionBits() ,FALSE);
		ReleaseISpinner(spin);

		spin = GetISpinner(GetDlgItem(hWnd, IDC_NORMAL_COMPRESSION_BITS_SPIN)); 
		spin->LinkToEdit(GetDlgItem(hWnd,IDC_NORMAL_COMPRESSION_BITS), EDITTYPE_INT ); 
		spin->SetLimits(24, 96, TRUE); 
		spin->SetScale(1.0f);
		spin->SetValue(exp->GetNormalCompressionBits() ,FALSE);
		ReleaseISpinner(spin);

		spin = GetISpinner(GetDlgItem(hWnd, IDC_IMAGE_COMPRESSION_BITS_SPIN)); 
		spin->LinkToEdit(GetDlgItem(hWnd,IDC_IMAGE_COMPRESSION_BITS), EDITTYPE_INT ); 
		spin->SetLimits(5, 100, TRUE); 
		spin->SetScale(1.0f);
		spin->SetValue(exp->GetImageCompressionValue() ,FALSE);
		ReleaseISpinner(spin);


		
		// Setup the spinner controls for the mesh definition sample rate 
		spin = GetISpinner(GetDlgItem(hWnd, IDC_MESH_STEP_SPIN)); 
		spin->LinkToEdit(GetDlgItem(hWnd,IDC_MESH_STEP), EDITTYPE_INT ); 
		spin->SetLimits(1, 100, TRUE); 
		spin->SetScale(1.0f);
		spin->SetValue(exp->GetMeshFrameStep() ,FALSE);
		ReleaseISpinner(spin);

		// Setup the spinner controls for the floating point precision 
		spin = GetISpinner(GetDlgItem(hWnd, IDC_PREC_SPIN)); 
		spin->LinkToEdit(GetDlgItem(hWnd,IDC_PREC), EDITTYPE_INT ); 
		spin->SetLimits(1, 10, TRUE); 
		spin->SetScale(1.0f);
		spin->SetValue(exp->GetPrecision() ,FALSE);
		ReleaseISpinner(spin);

		// Setup the spinner control for the static frame#
		// We take the frame 0 as the default value
		animRange = exp->GetInterface()->GetAnimRange();
		spin = GetISpinner(GetDlgItem(hWnd, IDC_STATIC_FRAME_SPIN)); 
		spin->LinkToEdit(GetDlgItem(hWnd,IDC_STATIC_FRAME), EDITTYPE_INT ); 
		spin->SetLimits(animRange.Start() / GetTicksPerFrame(), animRange.End() / GetTicksPerFrame(), TRUE); 
		spin->SetScale(1.0f);
		spin->SetValue(0, FALSE);
		ReleaseISpinner(spin);

		// Enable / disable mesh options
		EnableWindow(GetDlgItem(hWnd, IDC_NORMALS), exp->GetIncludeMesh());
		EnableWindow(GetDlgItem(hWnd, IDC_TEXCOORDS), exp->GetIncludeMesh());
		EnableWindow(GetDlgItem(hWnd, IDC_VERTEXCOLORS), exp->GetIncludeMesh());

		EnableWindow(GetDlgItem(hWnd, IDC_CONNECTIVITY_COMPRESSION), true);
		EnableWindow(GetDlgItem(hWnd, IDC_VERTEX_COMPRESSION), true);
		EnableWindow(GetDlgItem(hWnd, IDC_NORMAL_COMPRESSION), true);
		EnableWindow(GetDlgItem(hWnd, IDC_SPECULAR_FOR_ENVIRONMENT),true);
		EnableWindow(GetDlgItem(hWnd, IDC_DISABLE_ENV), true);

		break;

	case CC_SPINNER_CHANGE:
		spin = (ISpinnerControl*)lParam; 
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_MESHDATA:
			// Enable / disable mesh options
			EnableWindow(GetDlgItem(hWnd, IDC_NORMALS), IsDlgButtonChecked(hWnd,
				IDC_MESHDATA));
			EnableWindow(GetDlgItem(hWnd, IDC_TEXCOORDS), IsDlgButtonChecked(hWnd,
				IDC_MESHDATA));
			EnableWindow(GetDlgItem(hWnd, IDC_VERTEXCOLORS), IsDlgButtonChecked(hWnd,
				IDC_MESHDATA));
			EnableWindow(GetDlgItem(hWnd, IDC_CONNECTIVITY_COMPRESSION), IsDlgButtonChecked(hWnd,
				IDC_CONNECTIVITY_COMPRESSION));
			EnableWindow(GetDlgItem(hWnd, IDC_VERTEX_COMPRESSION), IsDlgButtonChecked(hWnd,
				IDC_VERTEX_COMPRESSION));
			EnableWindow(GetDlgItem(hWnd, IDC_NORMAL_COMPRESSION), IsDlgButtonChecked(hWnd,
				IDC_NORMAL_COMPRESSION));
			EnableWindow(GetDlgItem(hWnd, IDC_SPECULAR_FOR_ENVIRONMENT), IsDlgButtonChecked(hWnd,
				IDC_SPECULAR_FOR_ENVIRONMENT));
			EnableWindow(GetDlgItem(hWnd, IDC_DISABLE_ENV), IsDlgButtonChecked(hWnd,
				IDC_DISABLE_ENV));

			break;
		case IDOK:
			exp->SetIncludeMesh(IsDlgButtonChecked(hWnd, IDC_MESHDATA)); 
			exp->SetIncludeAnim(IsDlgButtonChecked(hWnd, IDC_ANIMKEYS)); 
			exp->SetIncludeMtl(IsDlgButtonChecked(hWnd, IDC_MATERIAL)); 
			exp->SetIncludeMeshAnim(IsDlgButtonChecked(hWnd, IDC_MESHANIM)); 
			exp->SetIncludeCamLightAnim(IsDlgButtonChecked(hWnd, IDC_CAMLIGHTANIM)); 
#ifndef DESIGN_VER
			exp->SetIncludeIKJoints(IsDlgButtonChecked(hWnd, IDC_IKJOINTS)); 
#endif // !DESIGN_VER
			exp->SetIncludeNormals(IsDlgButtonChecked(hWnd, IDC_NORMALS));
			exp->SetIncludeTextureCoords(IsDlgButtonChecked(hWnd, IDC_TEXCOORDS)); 
			exp->SetIncludeVertexColors(IsDlgButtonChecked(hWnd, IDC_VERTEXCOLORS)); 
			exp->SetIncludeObjGeom(IsDlgButtonChecked(hWnd, IDC_OBJ_GEOM)); 
			exp->SetIncludeObjShape(IsDlgButtonChecked(hWnd, IDC_OBJ_SHAPE)); 
			exp->SetIncludeObjCamera(IsDlgButtonChecked(hWnd, IDC_OBJ_CAMERA)); 
			exp->SetIncludeObjLight(IsDlgButtonChecked(hWnd, IDC_OBJ_LIGHT)); 
			exp->SetIncludeObjTextures(IsDlgButtonChecked(hWnd, IDC_OBJ_TEXTURES)); 			exp->SetFlipAxis(IsDlgButtonChecked(hWnd, IDC_OBJ_FLIPAXIS)); 
			exp->SetIncludeObjHelper(IsDlgButtonChecked(hWnd, IDC_OBJ_HELPER));
			exp->SetAlwaysSample(IsDlgButtonChecked(hWnd, IDC_RADIO_SAMPLE));
			exp->SetCameraAsAnimation(IsDlgButtonChecked(hWnd, IDC_CAMERA_AS_ANIMATIONS));
			exp->SetInactiveByDefault(IsDlgButtonChecked(hWnd, IDC_INACTIVE_BY_DEFAULT));
			
			if (IsDlgButtonChecked(hWnd, IDC_RADIO_LEFTHANDED))
				exp->SetHandedness(LEFT_HANDED);
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO_RIGHTHANDED))
				exp->SetHandedness(RIGHT_HANDED);
			else
 				exp->SetHandedness(DEFAULT_HANDED);

			exp->SetConnectivityCompression(IsDlgButtonChecked(hWnd, IDC_CONNECTIVITY_COMPRESSION));
			exp->SetVertexCompression(IsDlgButtonChecked(hWnd, IDC_VERTEX_COMPRESSION));
			exp->SetNormalCompression(IsDlgButtonChecked(hWnd, IDC_NORMAL_COMPRESSION));
			exp->SetSpecForEnv(IsDlgButtonChecked(hWnd, IDC_SPECULAR_FOR_ENVIRONMENT));
			exp->SetDisableEnv(IsDlgButtonChecked(hWnd, IDC_DISABLE_ENV));

			spin = GetISpinner(GetDlgItem(hWnd, IDC_CONT_STEP_SPIN)); 
			exp->SetKeyFrameStep(spin->GetIVal()); 
			ReleaseISpinner(spin);

			spin = GetISpinner(GetDlgItem(hWnd, IDC_MESH_STEP_SPIN)); 
			exp->SetMeshFrameStep(spin->GetIVal());
			ReleaseISpinner(spin);

			spin = GetISpinner(GetDlgItem(hWnd, IDC_PREC_SPIN)); 
			exp->SetPrecision(spin->GetIVal());
			ReleaseISpinner(spin);
		
			spin = GetISpinner(GetDlgItem(hWnd, IDC_STATIC_FRAME_SPIN)); 
			exp->SetStaticFrame(spin->GetIVal() * GetTicksPerFrame());
			ReleaseISpinner(spin);

			spin = GetISpinner(GetDlgItem(hWnd, IDC_VERTEX_COMPRESSION_BITS_SPIN)); 
			exp->SetVertexCompressionBits(spin->GetIVal()); 
			ReleaseISpinner(spin);

			spin = GetISpinner(GetDlgItem(hWnd, IDC_NORMAL_COMPRESSION_BITS_SPIN)); 
			exp->SetNormalCompressionBits(spin->GetIVal()); 
			ReleaseISpinner(spin);

			spin = GetISpinner(GetDlgItem(hWnd, IDC_IMAGE_COMPRESSION_BITS_SPIN)); 
			exp->SetImageCompressionValue(spin->GetIVal()); 
			ReleaseISpinner(spin);

			EndDialog(hWnd, 1);
			break;
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		case ID_VISITHOOPS3D:
			exp->LoadUrl("www.hoops3d.com");
			break;
		}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}       

// Dummy function for progress bar
DWORD WINAPI fn(LPVOID arg)
{
	return(0);
}


// export the HSF object to a file

static void WriteObject(BBaseOpcodeHandler * handler, BStreamFileToolkit * tk, FILE * fp,
                        char * buffer, int size) 
{
    TK_Status status;

    // ask the toolkit to write out the object; the toolkit will write out as much as
    // the current buffer can hold
    status = handler->Write(*tk);

    // if there is still more data left to write; we have to loop through 
    // generating and writing buffers of data until we're done
    while (status == TK_Pending) 
    {
        // due to compression, preparing a new buffer might immediately fill that buffer
        // so we need an extra check to possibly export that buffer and prepare a new buffer
        while (status == TK_Pending) 
        {
            // ask the toolkit how much of the buffer is currently filled
            // this will normally be the same as the buffer size that we passed in
            int count = tk->CurrentBufferLength();

            // write the current out to our file since this example deals with 
            // exporting a file; however, instead of writing to a file, the buffer of
            // data could be sent to an application data-structure, or transmitted
            // over a network ('streamed'), etc...
            fwrite(buffer, sizeof (char), count, fp);

            // tell the toolkit where it can resume writing data; in this case, we
            // can reuse the same buffer once we're done with it
            status = tk->PrepareBuffer(buffer, size);
        }

        // ask the toolkit to continue trying to write out the object's data
        status = handler->Write(*tk);
    }
}


void HsfExp::InitializeHSFWrite(HUtilityXMLTag *bhvtag, const TCHAR *name)
{
	subsegment = 0;
	m_pStreamFileToolkit = new BStreamFileToolkit;
    int size=4096;
	mcounter = 0;
	m_imagecounter = 0;
	m_animcounter = 0;
	m_bFirstCamera = FALSE;
	m_pXML = new HUtilityXMLGenerator;
 	HUtilityXMLTag xmlt;

	m_pXML->Reset();
	bhvtag->SetTagname("Animdef");
	bhvtag->AddProperty("Name", "Test", true);
	bhvtag->AddProperty("Version", "1.0", true);
	bhvtag->AddProperty("Vendor", "TSA", true);
	bhvtag->AddPropertyInt("TicksPerSecond", 4800);
	bhvtag->AddPropertyInt("Delay", 0);
	bhvtag->SetOpen(true);
   	m_pXML->AddTag(bhvtag);

	// Open the stream
	m_Stream = _tfopen(name,_T("wb"));

 
    // tell the toolkit where to begin writing data; the size of the 'utility' buffer
    // can be anything; for this example, we use a 4k buffer
    m_pStreamFileToolkit->PrepareBuffer(m_Buffer, BUFFERSIZE);

	long flags = 0;

	if (!GetNormalCompression())
		flags |= TK_Full_Resolution_Normals;
	if (!GetVertexCompression())
		flags |= TK_Full_Resolution_Vertices;

	if (GetConnectivityCompression())
		flags |= TK_Connectivity_Compression;
 
	m_pStreamFileToolkit->SetWriteFlags(flags);
	m_pStreamFileToolkit->SetNumNormalBits(GetNormalCompressionBits());
	m_pStreamFileToolkit->SetNumVertexBits(GetVertexCompressionBits());
	m_pStreamFileToolkit->SetJpegQuality(GetImageCompressionValue());

     // create a TK_Header object and export it's associated HSF objects,
    // which include the TKE_Comment and TKE_File_Info objects
    // TK_Header automatically formats the TKE_Comment to contain file version 
    // information.  
        BBaseOpcodeHandler *handler = new TK_Header();
    WriteObject(handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
    delete handler;

   // export a TKE_Start_Compression object
    handler = new TK_Compression(TKE_Start_Compression);
    WriteObject(handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	m_imagehash = new_vhash(1,malloc, free);

	if (GetHandedness() == LEFT_HANDED || GetHandedness() == RIGHT_HANDED)
	{
	    TK_Enumerated *handedness_handler= new TK_Enumerated(TKE_Handedness);
		if (GetHandedness() == LEFT_HANDED)
			handedness_handler->SetIndex(0);
		else
			handedness_handler->SetIndex(1);

		WriteObject(handedness_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
		delete handedness_handler;
	}
	WriteOpenSegment("styles");
	WriteCloseSegment();

     TK_Referenced_Segment *style_handler = new TK_Referenced_Segment(TKE_Style_Segment);	style_handler->SetSegment("styles/textures");
	WriteOpenSegment("styles");
	WriteOpenSegment("textures");
	WriteCloseSegment();

	WriteVisibilityOff();
	WriteCloseSegment();
//    WriteObject(style_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
 


	if (GetFlipAxis())
	{
		float matrix[16] = {1,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,1};
	    TK_Matrix *matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
 		matrix_handler->SetMatrix(matrix);
	    WriteObject(matrix_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
		delete matrix_handler;
	}

//	WriteUserOptions(text);

	delete style_handler;
 

	
}
void HsfExp::EndHSFWrite(HUtilityXMLTag *bhvtag)
{
 
	m_pXML->CloseTag(bhvtag);
	m_pXML->Finalize();


    TK_XML *xml_handler= new TK_XML;
	xml_handler->SetXML(m_pXML->GetBufferSize(), m_pXML->GetBuffer());
    WriteObject(xml_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete xml_handler;

     // create a TK_Header object and export it's associated HSF objects,
    // which include the TKE_Comment and TKE_File_Info objects
    // TK_Header automatically formats the TKE_Comment to contain file version 
    // information.  
    BBaseOpcodeHandler *handler;
     // export a TKE_Stop_Compression object
    handler = new TK_Compression(TKE_Stop_Compression);
    WriteObject(handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
    delete handler;

    // export a TKE_Termination object
    handler = new TK_Terminator(TKE_Termination);
    WriteObject(handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
    delete handler;
   // ask the toolkit how much of the final buffer is filled
    int count = m_pStreamFileToolkit->CurrentBufferLength();

    // write out the final buffer
    fwrite(m_Buffer, sizeof (char), count, m_Stream);

    // close the file
    fclose(m_Stream);

	delete m_pXML;
}
void HsfExp::CreateRelativePath(char *text, char *text2){
	strcpy(text,"");
	for (int i=0;i<subsegment;i++)
		strcat(text, "../");
	strcat(text, text2);

}
void HsfExp::WriteOpenSegment(TCHAR *name)
{
    TK_Open_Segment *open_seg_handler= new TK_Open_Segment;
    open_seg_handler->SetSegment(name);
    WriteObject(open_seg_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	subsegment++;
	delete open_seg_handler;
}

void HsfExp::WriteVisibilityOff()
{
    TK_Visibility *visibility_handler= new TK_Visibility;
    visibility_handler->SetGeometry(TKO_Geo_Image);
//    visibility_handler->SetValue(TKO_Geo_Image);
    WriteObject(visibility_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete visibility_handler;
}

void HsfExp::WriteCloseSegment()
{	subsegment--;
    TK_Close_Segment *close_seg_handler= new TK_Close_Segment;
    WriteObject(close_seg_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete close_seg_handler;
}




// Start the exporter!
// This is the real entrypoint to the exporter. After the user has selected
// the filename (and he's prompted for overwrite etc.) this method is called.
int HsfExp::DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options) 
{
	// Set a global prompt display switch
	showPrompts = suppressPrompts ? FALSE : TRUE;
	exportSelected = (options & SCENE_EXPORT_SELECTED) ? TRUE : FALSE;

	// Grab the interface pointer.
	ip = i;

	// Get the options the user selected the last time
	ReadConfig();

	if(showPrompts) {
		// Prompt the user with our dialogbox, and get all the options.
		if (!DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_HsfExpORT_DLG),
			ip->GetMAXHWnd(), ExportDlgProc, (LPARAM)this)) {
			return 1;
			}
		}
	
	sprintf(szFmtStr, "%%4.%df", nPrecision);

#ifdef ASCIIOUTPUT
	char text[4096];
	strcpy(text, name);
	strcat(text, ".asc");
	// Open the stream
	pStream = _tfopen(text,_T("wt"));
	if (!pStream) {
		return 0;
	}
#endif
	
	

	// Get a total node count by traversing the scene
	// We don't really need to do this, but it doesn't take long, and
	// it is nice to have an accurate progress bar.
	nTotalNodeCount = 0;
	nCurNode = 0;
	PreProcess(ip->GetRootNode(), nTotalNodeCount);
	HUtilityXMLTag bhvtag;
	InitializeHSFWrite(&bhvtag, name);		


	// First we write out a file header with global information. 
	ExportGlobalInfo();


	// Export list of material definitions
	bSaveImages = TRUE;
	bSaveColors = TRUE;
	mcounter = 0;
	ExportMaterialList();

	int numChildren = ip->GetRootNode()->NumberOfChildren();
	
	// Call our node enumerator.
	// The nodeEnum function will recurse into itself and 
	// export each object found in the scene.
		for (int idx=0; idx<numChildren; idx++) {
		if (ip->GetCancel())
			break;
		nodeEnumCamera(ip->GetRootNode()->GetChildNode(idx), 0);
	}

// Startup the progress bar.
	ip->ProgressStart(GetString(IDS_PROGRESS_MSG), TRUE, fn, NULL);

	for (int idx=0; idx<numChildren; idx++) {
		if (ip->GetCancel())
			break;
		nodeEnum(ip->GetRootNode()->GetChildNode(idx), 0);
	}
	bSaveImages = FALSE;
	bSaveColors = FALSE;
	mcounter = 0;
	ExportMaterialList();


	// We're done. Finish the progress bar.
	ip->ProgressEnd();

#ifdef ASCIIOUTPUT
	// Close the stream
	fclose(pStream);
#endif
	EndHSFWrite(&bhvtag);

	// Write the current options to be used next time around.
	WriteConfig();

	return 1;
}

BOOL HsfExp::SupportsOptions(int ext, DWORD options) {
	assert(ext == 0);	// We only support one extension
	return(options == SCENE_EXPORT_SELECTED) ? TRUE : FALSE;
	}

// This method is the main object exporter.
// It is called once of every node in the scene. The objects are
// exported as they are encoutered.

// Before recursing into the children of a node, we will export it.
// The benefit of this is that a nodes parent is always before the
// children in the resulting file. This is desired since a child's
// transformation matrix is optionally relative to the parent.

BOOL HsfExp::nodeEnum(INode* node, int indentLevel) 
{
	if((exportSelected && node->Selected() == FALSE))
		return TREE_CONTINUE;

	nCurNode++;
	ip->ProgressUpdate((int)((float)nCurNode/nTotalNodeCount*100.0f)); 

	// Stop recursing if the user pressed Cancel 
	if (ip->GetCancel())
		return FALSE;
	TSTR indent = GetIndent(indentLevel);
	 
	// If this node is a group head, all children are 
	// members of this group. The node will be a dummy node and the node name
	// is the actualy group name.
	WriteOpenSegment(FixupName(node->GetName()));	
	
//	strcpy(xxx,FixupName(node->GetName()));
//	if (strstr(xxx, "saide_paneL"))
//		indent = indent;
	if (node->IsGroupHead()) {
  		FPRINTF(pStream,"%s%s \"%s\" {\n", indent.data(), ID_GROUP, FixupName(node->GetName())); 
		indentLevel++;
	}
	
	// Only export if exporting everything or it's selected
	if(!exportSelected || node->Selected()) {

		// The ObjectState is a 'thing' that flows down the pipeline containing
		// all information about the object. By calling EvalWorldState() we tell
		// max to eveluate the object at end of the pipeline.
		ObjectState os = node->EvalWorldState(0); 

		// The obj member of ObjectState is the actual object we will export.
		if (os.obj) {

			// We look at the super class ID to determine the type of the object.
			switch(os.obj->SuperClassID()) {
			case GEOMOBJECT_CLASS_ID: 
				if (!node->IsHidden())				
				{
				if (GetIncludeObjGeom()) ExportGeomObject(node, indentLevel); 
				}
				break;				
//			case CAMERA_CLASS_ID:
//				if (GetIncludeObjCamera()) ExportCameraObject(node, indentLevel); 
//				break;
			case LIGHT_CLASS_ID:
				if (GetIncludeObjLight()) ExportLightObject(node, indentLevel); 
				break;
			case SHAPE_CLASS_ID:
				if (GetIncludeObjShape()) ExportShapeObject(node, indentLevel); 
				break;
			case HELPER_CLASS_ID:
				if (GetIncludeObjHelper()) ExportHelperObject(node, indentLevel); 
				break;
			}
		}
	}	
	
	// For each child of this node, we recurse into ourselves 
	// until no more children are found.
	for (int c = 0; c < node->NumberOfChildren(); c++) {
		if (!nodeEnum(node->GetChildNode(c), indentLevel))
			return FALSE;
	}
	
	// If thie is true here, it is the end of the group we started above.
	if (node->IsGroupHead()) {
		FPRINTF(pStream,"%s}\n", indent.data());
		indentLevel--;
	}

	WriteCloseSegment();
	return TRUE;
}



BOOL HsfExp::nodeEnumCamera(INode* node, int indentLevel) 
{
	if(exportSelected && node->Selected() == FALSE)
		return TREE_CONTINUE;
	
 
	// Stop recursing if the user pressed Cancel 
	if (ip->GetCancel())
		return FALSE;
	
	
	 

	// Only export if exporting everything or it's selected
	if(!exportSelected || node->Selected()) {

		// The ObjectState is a 'thing' that flows down the pipeline containing
		// all information about the object. By calling EvalWorldState() we tell
		// max to eveluate the object at end of the pipeline.
		ObjectState os = node->EvalWorldState(0); 

		// The obj member of ObjectState is the actual object we will export.
		if (os.obj) {

			// We look at the super class ID to determine the type of the object.
			switch(os.obj->SuperClassID()) {
 			case CAMERA_CLASS_ID:
				WriteOpenSegment(FixupName(node->GetName()));	
				if (GetIncludeObjCamera()) ExportCameraObject(node, indentLevel); 
				WriteCloseSegment();
				break;
  			}
		}
	}	
	
	// For each child of this node, we recurse into ourselves 
	// until no more children are found.
	for (int c = 0; c < node->NumberOfChildren(); c++) {
		if (!nodeEnumCamera(node->GetChildNode(c), indentLevel))
			return FALSE;
	}
	
	 

	
	return TRUE;
}



void HsfExp::PreProcess(INode* node, int& nodeCount)
{
 	nodeCount++;
	
 
	ObjectState ostate = node->EvalWorldState(GetStaticFrame());	
	Object *obj = ostate.obj;
	if (obj)
	{
		Box3 boundingBox;
		obj->GetDeformBBox(GetStaticFrame(), boundingBox);
		Point3 min = boundingBox.Min();
		Point3 max = boundingBox.Max();
		if (min.x < m_min.x )
			m_min.x = min.x;
		if (min.y < m_min.y )
			m_min.y = min.y;
		if (min.z < m_min.z )
			m_min.z = min.z;
		if (max.x > m_max.x )
			m_max.x = max.x;
		if (max.y > m_max.y )
			m_max.y = max.y;
		if (max.z > m_max.z )
			m_max.z = max.z;

	}

 


	// Add the nodes material to out material list
	// Null entries are ignored when added...
	mtlList.AddMtl(node->GetMtl());

	// For each child of this node, we recurse into ourselves 
	// and increment the counter until no more children are found.
	for (int c = 0; c < node->NumberOfChildren(); c++) {
		PreProcess(node->GetChildNode(c), nodeCount);
	}
}

/****************************************************************************

 Configuration.
 To make all options "sticky" across sessions, the options are read and
 written to a configuration file every time the exporter is executed.

 ****************************************************************************/

TSTR HsfExp::GetCfgFilename()
{
	TSTR filename;
	
	filename += ip->GetDir(APP_PLUGCFG_DIR);
	filename += "\\";
	filename += CFGFILENAME;

	return filename;
}

// NOTE: Update anytime the CFG file changes
#define CFG_VERSION 0x06

BOOL HsfExp::ReadConfig()
{
	TSTR filename = GetCfgFilename();
	FILE* cfgStream;

	cfgStream = fopen(filename, "rb");
	if (!cfgStream)
		return FALSE;

	// First item is a file version
	int fileVersion = _getw(cfgStream);

	if (fileVersion > CFG_VERSION) {
		// Unknown version
		fclose(cfgStream);
		return FALSE;
	}

	SetIncludeMesh(fgetc(cfgStream));
	SetIncludeAnim(fgetc(cfgStream));
	SetIncludeMtl(fgetc(cfgStream));
	SetIncludeMeshAnim(fgetc(cfgStream));
	SetIncludeCamLightAnim(fgetc(cfgStream));
	SetIncludeIKJoints(fgetc(cfgStream));
	SetIncludeNormals(fgetc(cfgStream));
	SetIncludeTextureCoords(fgetc(cfgStream));
	SetIncludeObjGeom(fgetc(cfgStream));
	SetIncludeObjShape(fgetc(cfgStream));
	SetIncludeObjCamera(fgetc(cfgStream));
	SetIncludeObjLight(fgetc(cfgStream));
	SetIncludeObjHelper(fgetc(cfgStream));
	SetAlwaysSample(fgetc(cfgStream));
	SetMeshFrameStep(_getw(cfgStream));
	SetKeyFrameStep(_getw(cfgStream));

	

	// Added for version 0x02
	if (fileVersion > 0x01) {
		SetIncludeVertexColors(fgetc(cfgStream));
	}

	// Added for version 0x03
	if (fileVersion > 0x02) {
		SetPrecision(_getw(cfgStream));
	}
	if (fileVersion > 0x04) {	
	SetConnectivityCompression(fgetc(cfgStream));
  	SetVertexCompression(fgetc(cfgStream));
 	SetNormalCompression(fgetc(cfgStream));
 	SetImageCompression(fgetc(cfgStream));
// 	SetSpecForEnv(fgetc(cfgStream));
 //	SetDisableEnv(fgetc(cfgStream));

	SetVertexCompressionBits(_getw(cfgStream));
	SetNormalCompressionBits(_getw(cfgStream));
	SetImageCompressionValue(_getw(cfgStream));
	SetIncludeObjTextures(fgetc(cfgStream));
	SetHandedness(_getw(cfgStream));
	SetCameraAsAnimation(fgetc(cfgStream));
	SetInactiveByDefault(fgetc(cfgStream));

	}			if (fileVersion > 0x05) 	SetFlipAxis(fgetc(cfgStream));
	fclose(cfgStream);

	return TRUE;
}

void HsfExp::WriteConfig()
{
	TSTR filename = GetCfgFilename();
	FILE* cfgStream;

	cfgStream = fopen(filename, "wb");
	if (!cfgStream)
		return;

	// Write CFG version
	_putw(CFG_VERSION,				cfgStream);

	fputc(GetIncludeMesh(),			cfgStream);
	fputc(GetIncludeAnim(),			cfgStream);
	fputc(GetIncludeMtl(),			cfgStream);
	fputc(GetIncludeMeshAnim(),		cfgStream);
	fputc(GetIncludeCamLightAnim(),	cfgStream);
	fputc(GetIncludeIKJoints(),		cfgStream);
	fputc(GetIncludeNormals(),		cfgStream);
	fputc(GetIncludeTextureCoords(),	cfgStream);
	fputc(GetIncludeObjGeom(),		cfgStream);
	fputc(GetIncludeObjShape(),		cfgStream);
	fputc(GetIncludeObjCamera(),	cfgStream);
	fputc(GetIncludeObjLight(),		cfgStream);
	fputc(GetIncludeObjHelper(),	cfgStream);
	fputc(GetAlwaysSample(),		cfgStream);
	_putw(GetMeshFrameStep(),		cfgStream);
	_putw(GetKeyFrameStep(),		cfgStream);
	fputc(GetIncludeVertexColors(),	cfgStream);
	_putw(GetPrecision(),			cfgStream);

	fputc(GetConnectivityCompression(), cfgStream);
	fputc(GetVertexCompression(), cfgStream);
	fputc(GetNormalCompression(), cfgStream);
	fputc(GetImageCompression(), cfgStream);
//	fputc(GetSpecForEnv(), cfgStream);
//	fputc(GetDisableEnv(), cfgStream);

	_putw(GetVertexCompressionBits(),		cfgStream);
	_putw(GetNormalCompressionBits(),		cfgStream);
	_putw(GetImageCompressionValue(),		cfgStream);
	fputc(GetIncludeObjTextures(),		cfgStream);
	_putw(GetHandedness(),		cfgStream);
	fputc(GetCameraAsAnimation(),		cfgStream);
	fputc(GetInactiveByDefault(),		cfgStream);
	fputc(GetFlipAxis(),		cfgStream);
	fclose(cfgStream);
}


BOOL MtlKeeper::AddMtl(Mtl* mtl)
{
	if (!mtl) {
		return FALSE;
	}

	int numMtls = mtlTab.Count();
	for (int i=0; i<numMtls; i++) {
		if (mtlTab[i] == mtl) {
			return FALSE;
		}
	}
	mtlTab.Append(1, &mtl, 25);

	return TRUE;
}

int MtlKeeper::GetMtlID(Mtl* mtl)
{
	int numMtls = mtlTab.Count();
	for (int i=0; i<numMtls; i++) {
		if (mtlTab[i] == mtl) {
			return i;
		}
	}
	return -1;
}

int MtlKeeper::Count()
{
	return mtlTab.Count();
}

Mtl* MtlKeeper::GetMtl(int id)
{
	return mtlTab[id];
}




void HsfExp::LoadUrl (char *url)
{
        HKEY    html_owner_key        = 0;
        char *  html_owner            = 0;
        HKEY    classes_key            = 0;
        HKEY    browser_root_key    = 0;
        HKEY    browser_path_key    = 0;
        char *    browser_path        = 0;
        DWORD    value_type;
        DWORD    string_size            = 0;
		char error_message[4096];
        strcpy(error_message, "Unable to start your internet browser");

        // Try to find the exectuable of the default internet browser.
        // We do this by looking at who "owns" the ".htm" file format.
        if (ERROR_SUCCESS != RegOpenKeyEx(
                                    HKEY_LOCAL_MACHINE,            // handle of open key
                                    "software\\classes\\.htm",     // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &html_owner_key) )             // address of handle of open key
        {
			;
//			AfxMessageBox (error_message);
        }
        // Determine length of string identifying html_owner.
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                    html_owner_key,                // handle of key to query
                                    "",                            // address of name of value to query
                                    0L,                            // reserved
                                    &value_type,                   // address of buffer for value type
                                    0,                          // address of data buffer
                                    &string_size))                 // address of data buffer size
        {
			;
//			AfxMessageBox (error_message);
        }
        // then allocate space to hold it.
        else if ((html_owner = new char[string_size]) == 0)
        {
			;
			//AfxMessageBox (error_message);
        }
        // Determine html_owner
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                    html_owner_key,                // handle of key to query
                                    "",                            // address of name of value to query
                                    0L,                            // reserved
                                    &value_type,                   // address of buffer for value type
                                    (LPBYTE)html_owner,            // address of data buffer
                                    &string_size) )                // address of data buffer size
        {
			;
			//AfxMessageBox (error_message);
        }
        // Need to find executable associated with html_owner
        // We now generate a path from the html_owner string.
        else if (ERROR_SUCCESS != RegOpenKeyEx(
                                    HKEY_LOCAL_MACHINE,            // handle of open key
                                    "software\\classes",           // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &classes_key) )                // address of handle of open key
        {
			;
//			AfxMessageBox (error_message);
        }
        else if (ERROR_SUCCESS != RegOpenKeyEx(
                                    classes_key,                   // handle of open key
                                    html_owner,                    // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &browser_root_key) )           // address of handle of open key
        {
			;
//			AfxMessageBox (error_message);
        }
        else if (ERROR_SUCCESS != RegOpenKeyEx(
                                    browser_root_key,              // handle of open key
                                    "shell\\open\\command",        // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &browser_path_key) )           // address of handle of open key
        {
			;
//			AfxMessageBox (error_message);
        }
        // Determine size of browser_path
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                        browser_path_key,          // handle of key to query
                                        "",                        // address of name of value to query
                                        0L,                        // reserved
                                        &value_type,               // address of buffer for value type
                                        NULL,                      // address of data buffer
                                        &string_size))             // address of data buffer size
        {
			;
		//	AfxMessageBox (error_message);
        }
        else if ((browser_path = new char[string_size]) == 0)
        {
			;
		//	AfxMessageBox (error_message);
        }
        // determine id_string
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                        browser_path_key,          // handle of key to query
                                        "",                        // address of name of value to query
                                        0L,                        // reserved
                                        &value_type,               // address of buffer for value type
                                        (LPBYTE)browser_path,      // address of data buffer
                                        &string_size) )            // address of data buffer size
        {
			;
			//AfxMessageBox (error_message);
        }
        else
        {
            // In order for this code to be compatible with both MSIE and Netscape,
            //   we are required to use the shell\\open\\command registry key which
            //   contains some extra characters at the end of the string.  Let's
            //   replace the %1 in the string with %s representing our URL

 
			char browser_command[4096];
			strcpy(browser_command, browser_path);

			char *position = strstr(browser_command, "%1");
           

            if (!position)
            {
                // There was no percent sign for this command line,
                // so lets just assume that the URL goes on the end-of-the-line.

                // See if there is a close double-quotes, if so then put the
                // url inside them.

                if (browser_command[strlen(browser_command)-1] == '"')
				{
					char temp[4096];
					strcpy(temp, browser_command);
					temp[string_size - 1] = 0;
					strcat(temp, url);
					strcat(temp, "\"");
					strcpy(browser_command, temp);
				}
                    //browser_command = browser_command.Left(string_size - 1) + url + '"';
                else
				{
					strcat(browser_command," ");
					strcat(browser_command,url);
                    //browser_command += " " + url;
				}
            }
            else
            {
                // We found a %1 in the command string.
                // Replace it with the url
				*position = 0;
				strcat(browser_command, url);

 
                //browser_command  = browser_command.Left(position) +
                  //                 CString(url) +
                    //               browser_command.Right(browser_command.GetLength( ) - position - 2);
            }

            WinExec (browser_command, SW_SHOWNORMAL);
        }

        // We may have had errors, so only close the keys if they were actually opened.
        if (html_owner_key)      RegCloseKey (html_owner_key);
        if (classes_key)         RegCloseKey (classes_key);
        if (browser_root_key)    RegCloseKey (browser_root_key);
        if (browser_path_key)    RegCloseKey (browser_path_key);

        delete []   html_owner;
        delete []   browser_path;
}
