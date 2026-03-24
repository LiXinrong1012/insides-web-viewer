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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/MyHQWidget.cpp,v 1.199 2010-10-26 18:32:15 evan Exp $
//


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>

#ifdef check
#undef check
#endif

// qt includes
#include <QtGui>
#include <QtCore>

// hoops_mvo includes
#include "HDB.h"

//Qt Driver Debug bits
#define DEBUG_USE_SCREEN_RESOLUTION		0x00000001
#define DEBUG_PRINT_DIALOG				0x00000002

#if defined(PARASOLID)
#include "HSolidModel.h"
#include "HSolidView.h"
#include "HSSelectionSet.h"
#include "HOpCreateSolidSphere.h"
#include "HOpCreateSolidCone.h"
#include "HOpCreateSolidCylinder.h"
#include "HOpCreateSweptBsplineFixed.h"
#else
#include "HBaseModel.h"
#include "HBaseView.h"
#include "HOpCreateSphere.h"
#endif

#include "HModelInfo.h"
#include "HEventInfo.h"
#include "HEventManager.h"
#include "HOpCameraManipulate.h"
#include "HOpCameraOrbit.h"
#include "HOpCameraZoom.h"
#include "HOpCameraZoomBox.h"
#include "HOpCameraPan.h"
#include "HOpCameraWalk.h"
#include "HOpCreateCone.h"
#include "HOpCreateCylinder.h"
#include "HOpCreateCuttingPlane.h"
#include "HOpCreateNurbsCurve.h"
#include "HOpSelectAperture.h"
#include "HOpSelectArea.h"
#include "HOpObjectTranslate.h"
#include "HOpObjectAnnotate.h"
#include "HOpObjectRotate.h"
#include "HOpObjectClash.h"
#include "HOpMarkupAnnotate.h"
#include "HOpMarkupFreehand.h"
#include "HOpMarkupRectangle.h"
#include "HOpMarkupCircle.h"
#include "HOpMarkupPostIt.h"
#include "HOpMarkupMeasure.h"
#include "HOpCreateNurbs3D.h"
#include "HSOpMoveHandle.h"
#include "HSharedKey.h"
#include "HConstantFrameRate.h"
#include "HUtility.h"
#include "HMarkupManager.h"
#include "HOpMoveHandle.h"
#include "HUtilityGeometryCreation.h"
#include "HUndoManager.h"

#include "HStream.h"
#include "HStreamFileToolkit.h"
#undef null

#include "HDispatchXML.h"
// my local specials
#include "HMyQuery.h"
#include "HMySelectionSet.h"

// the qt/hoops base class
#include "MyHQWidget.h"
#include "HQFrameRateDlg.h"
#include "HQSegmentTree.h"

#include "HIOManager.h"


// hoops include
#include "hc.h"

// this is setup in main
extern HDB * m_pHDB;

#include "HBhvBehaviorManager.h"
#include "HBhvUtility.h"

#include "HQApplication.h"


extern HQApplication * m_pHQApplication;

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




TK_Status TK_My_Initial_View::Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) alter
{
	HPoint pos, tar, up;
	float fieldx=0, fieldy=0;
	char proj[256];

	m_pMyWidget->GetHoopsView()->GetCamera(&pos,&tar,&up,fieldx,fieldy,proj);

	m_settings[0] = pos.x; m_settings[1] = pos.y; m_settings[2] = pos.z;
	m_settings[3] = tar.x; m_settings[4] = tar.y; m_settings[5] = tar.z;
	m_settings[6] = up.x ; m_settings[7] = up.y ; m_settings[8] = up.z;
	m_settings[9] = fieldx ; m_settings[10] = fieldy;

	switch ((int) proj[0]) {
		case 'o': m_projection = TKO_Camera_Orthographic; break;
		case 'p': m_projection = TKO_Camera_Perspective; break;
		case 's': m_projection = TKO_Camera_Stretched; break;
		default: m_projection = TKO_Camera_Stretched; break;
	}


	SetView("default");

	return TK_Normal;
}

TK_Status TK_My_Initial_View::Execute (BStreamFileToolkit & tk) alter
{
	TK_Status status=TK_Normal;

	HPoint pos, tar, up;
	float fieldx, fieldy;

	pos.Set(m_settings[0],m_settings[1],m_settings[2]);
	tar.Set(m_settings[3],m_settings[4],m_settings[5]);
	up.Set(m_settings[6],m_settings[7],m_settings[8]);
	fieldx = m_settings[9];
	fieldy = m_settings[10];

	char proj[16];

	switch ((int) m_projection) {
		case TKO_Camera_Orthographic: strcpy (proj, "o"); break;
		case TKO_Camera_Perspective: strcpy (proj, "p"); break;
		default: strcpy (proj, "s"); break;
	}


	if (!strcmp(GetView(),"default"))
	{
		m_pMyWidget->GetHoopsView()->SetCamera(pos,tar,up,fieldx,fieldy,proj);
		m_pMyWidget->GetHoopsView()->CameraPositionChanged(true);
		m_pMyWidget->SetHasInitialView(true);
	}

	return (status);
}



MyHQWidget::MyHQWidget( QWidget* parent, HQApplication* app, QString const & name , int aa, QString const & filename, 
	HQSegmentBrowserFrame *segBrowser)
		: HQWidget( parent, name , 0, aa)
{
	query_dialog = 0;
	wnd_color_picker_dlg = 0;
	lod_control=0;
	new_frame_rate_dlg = 0;
	framerateui = 0;
	FRtimer = 0;
        m_lastFile = "../../datasets/untitled.hsf";

	CreateMenus();

	//disable drag and drop file opening for now
	this->setAcceptDrops(false);

	// init some stuff 
	m_edges = false;
	m_faces = true;
	m_lines	= false;
	m_markers = false;
	m_lights = true;
	m_text = true;
	m_color_index_int = true;
	m_color_int = true;
	m_axis_on = true;
	m_bounding_on = false;
	m_light_follows = true;
	m_shadows_on = true;
	m_has_initial_view = false;
	m_aa_lines = false;
	m_aa_text = false;
	m_aa_onoff = false;
	m_aa = aa;
	fullscreen_on = false;

	m_hqapplication = app;

 	manipulate_menu=0;
	create_menu=0;
	selection_menu=0;
	view_menu=0;

	m_default_transmission = 0.7f;

#ifdef PARASOLID
	m_pHBaseModel = new HSolidModel();
#else
	m_pHBaseModel = new HBaseModel();
#endif
	m_pHBaseModel->Init();

	m_pHView = 0;

	// register our custom opcode handlers here
	m_pHBaseModel->GetStreamFileTK()->SetOpcodeHandler (TKE_View, new TK_My_Initial_View (this));
	m_pHBaseModel->GetStreamFileTK()->SetPrewalkHandler(new TK_My_Initial_View(this));
	//want to read the Autodek Image XRef Opcode
	m_pHBaseModel->GetStreamFileTK()->SetOpcodeHandler (0xE0,			    new W3D_Image);

	HBhvUtility::SetupAnimationReadFromHSF(m_pHBaseModel->GetStreamFileTK(), m_pHBaseModel);
	m_pHBaseModel->GetStreamFileTK()->SetOpcodeHandler (TKE_XML, m_pHBaseModel->GetDispatchXML()->MakeCopy());


	// if called with a file name we load it 
	// otherwise open a empty view
	// Added: Deffer the file reading until we have a view created. This is done
	// to facilitate streaming of data and displaying it immediately
	if(!filename.isEmpty()){
		deffered_filename = filename;
	}

	//this makes mouse move work
	setMouseTracking(true);

	//this make key events work
	setEnabled(true);
	setFocusPolicy(Qt::StrongFocus);
	m_pHandleOperator = 0;

	m_segBrowser = segBrowser;
}

MyHQWidget::~MyHQWidget()
{	

//printf("MyHQWidget::~MyHQWidget()\n");
	if (m_pHandleOperator)
	    delete m_pHandleOperator;

	HConstantFrameRate * constfrate = m_pHView->GetConstantFrameRateObject();
	if(constfrate){
		if(constfrate->GetActive()){
			constfrate->Stop();
			constfrate->Shutdown();
		}
	}
	
	if(query_dialog) delete query_dialog;
	if(wnd_color_picker_dlg) delete wnd_color_picker_dlg;
	if(lod_control) delete lod_control;

	if(m_pHView) delete m_pHView;
	if(m_pHBaseModel) delete m_pHBaseModel;

 	if(manipulate_menu) delete manipulate_menu;
	if(create_menu) delete create_menu;
	if(selection_menu) delete selection_menu;
	if(view_menu) delete view_menu;

	//if(framerate_dlg) delete framerate_dlg;
	if(new_frame_rate_dlg) delete new_frame_rate_dlg;
}


void MyHQWidget::dragEnterEvent(QDragEnterEvent* event){
	event->acceptProposedAction();
}

void MyHQWidget::dropEvent(QDropEvent* event){
	QString s ;
	QStringList formats = event->mimeData()->formats();

    foreach (QString format, formats){
		if(format.startsWith("text/uri-list")){
			s = event->mimeData()->data(format);
			s = s.remove("file:///"); //get rid of the file:/// at the start of the string
			s.chop(2); //remove the line feed and carriage return at the end of the string
			this->load(s);
			break;
		}
    }

	event->acceptProposedAction();
}

// set some sane defaults and need settings
void MyHQWidget::SetupView()
{
	if( !m_has_initial_view )
		m_pHView->FitWorld();		// fit the camera to the scene extents

	m_pHView->CameraPositionChanged(true);
	m_pHView->RenderGouraud();  // set the render mode to gouraud
	m_pHView->SetHandedness(HandednessRight);
	m_pHView->SetForceFastHiddenLine(true);

	// set the gradiant window background
	HPoint window_top_color(0.0000f, 0.501961f, 0.501961f);
	HPoint window_bottom_color(1.000f, 0.984314f, 0.941176f);
	m_pHView->SetWindowColor(window_top_color, window_bottom_color);

	
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Selectability("everything = off");
	HC_Close_Segment();

	m_pHView->SetShadowMode( HShadowSoft );	

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Set_Color_By_Index("faces", 2);
		HC_Set_Color_By_Index("text, lights", 1);
		HC_Set_Color_By_Index("markers", 1);
		HC_Set_Rendering_Options("color interpolation, color index interpolation, simple shadow = (resolution=64, blurring=4)");
		HC_Set_Visibility ("lights = (faces = on, edges = off, markers = off), markers = off, faces=on, edges=off, lines=off, text = on");
		HC_Set_Selectability("everything = off, geometry = on");
	HC_Close_Segment();

	// new segment for temporary construction geometry
	HC_Open_Segment_By_Key (m_pHView->GetConstructionKey());
	  HC_Set_Heuristics("quick moves");
	  HC_Set_Visibility("faces = off, edges = on, lines = on");
	HC_Close_Segment();


	// for quickmoves
	HC_Open_Segment_By_Key(m_pHView->GetWindowspaceKey());
		HC_Set_Color_By_Index ("geometry", 3);
		HC_Set_Color_By_Index ("window contrast", 1);
		HC_Set_Color_By_Index ("windows", 1);

		HC_Set_Visibility("markers=on");
		HC_Set_Color("markers = green, lines = green");
		HC_Set_Marker_Symbol("+");
		HC_Set_Selectability("off");
    HC_Close_Segment();	

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
        HC_Set_Text_Font("transforms = off");
    HC_Close_Segment();


}

void MyHQWidget::SetHasInitialView(bool has_init_view)
{
	m_has_initial_view = has_init_view;
}


// setup our base view and default operator
void MyHQWidget::Init()
{
		
#ifdef PARASOLID
	m_pHView = new HSolidView(m_pHBaseModel, NULL, NULL, NULL, GetWindowId(), GetColorMap(), GetClipOverride());
#else
	m_pHView = new HBaseView(m_pHBaseModel, NULL, NULL, NULL, GetWindowId(), GetColorMap(), GetClipOverride());
#endif
	m_pHView->Init();

	HSOpMoveHandle *handleoperator = new HSOpMoveHandle(m_pHView, this, false);
 	m_pHView->SetHandleOperator(handleoperator);
	m_pHView->GetEventManager()->RegisterHandler((HObjectManipulationListener *)handleoperator, HObjectManipulationListener::GetType(), HLISTENER_PRIORITY_NORMAL);

	char driver_opts[512];
	sprintf(driver_opts, "anti-alias=%d ", m_aa);
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options(driver_opts);
		HC_Set_Driver_Options("quick moves preference = default");
		HC_Set_Driver_Options("no display stats, no display time stats");
		if(m_aa == 0) 
			HC_Set_Rendering_Options("anti-alias = no screen");
		else
			HC_Set_Rendering_Options("anti-alias = (screen = on)");
	HC_Close_Segment();

	m_pHView->SetSmoothTransition(true);
	m_pHView->SetKeyStateCallback(HQWidget::GetKeyState);

	m_pHView->StartSharedKey();
	m_pHView->GetSharedKey()->Reset();
	m_pHView->GetSharedKey()->SetupStreamToolkit(m_pHView->GetModel()->GetStreamFileTK());

	m_pHView->SetHideOverlappedText(true);

	


#ifndef PARASOLID
	// create our app-specific Selection object and initialize
	m_pHView->SetSelection( new HMySelectionSet(m_pHView));
	(m_pHView->GetSelection())->Init();
#endif

	HPoint rgb;

	rgb.x = rgb.y = rgb.z =0.0f;
	m_pHView->SetWindowColor(rgb, true);

	SetupView();

	LocalSetOperator(new HOpCameraManipulate(m_pHView));
	((HOpCameraManipulate *)m_pHView->GetOperator())->GetOrbitOperator()->SetSceneBoundingBoxVis(m_bounding_on);

	m_pHView->SetSmoothTransition(true);
	

#ifndef OSX_SYSTEM
	//DEBUG_STARTUP_CLEAR_BLACK = 0x00004000 clear ogl to black on init update
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options("debug = 0x00004000");
	HC_Close_Segment();
#endif
	if (m_segBrowser) {
		((HQSegmentBrowserFrame*)m_segBrowser)->setHoopsView(GetHoopsView());
		((HQSegmentBrowserFrame*)m_segBrowser)->setSegmentRoot(GetHoopsModel()->GetModelKey());
	}
	
	m_pHView->SetHandedness(HandednessRight);
	m_pHView->SetPolygonHandednessMode(HandednessLeft);
	m_pHView->SetCPGeomVisibility(true,true);
	m_pHView->SetColorInterpolation(true);
	m_pHView->SetColorIndexInterpolation(true, false);
	m_pHView->SetBackplaneCulling(false);
	m_pHView->SetHideOverlappedText(false);
	m_pHView->Update();
	m_pHView->SetAxisMode(AxisOn);

	if( !deffered_filename.isEmpty() )
	{
		load(deffered_filename);
		deffered_filename.clear();
	}

	AdjustAxisWindow();
}


// load a file into our view
void MyHQWidget::load(QString const & in_filename)
{
	H_UTF8 hutf8;
	hutf8.encodedText<char>(in_filename.toUtf8().data());
	H_WCS hwcs(hutf8);
	std::wstring stdwcs(hwcs.encodedText());

	m_pHView->Flush(true);

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Flush_Contents (".", "geometry");
	HC_Close_Segment();

	wchar_t extension[100] = {L""};

	HUtility::FindFileNameExtension(stdwcs.c_str(), extension);

	HFileInputResult result;

	if (wcsstr(L"hsf", extension)) {

	    m_pHView->GetModel()->GetStreamFileTK()->Restart();

#define HSF_BUFFER_CHUNK 8192
	    char buffer[HSF_BUFFER_CHUNK];
	    int length;
	    FILE *fp;

	    fp = wfopen(stdwcs.c_str(), L"rb");
		if(fp){
			HC_Open_Segment_By_Key(m_pHView->GetModel()->GetModelKey());

			while (!feof(fp))
			{
				length = fread(buffer,1,HSF_BUFFER_CHUNK,fp);
				m_pHView->InsertHSFData("nosegment", buffer, length, true);
			}

			HC_Close_Segment();

			result = InputOK;
			m_pHView->GetModel()->SetFileLoadComplete(true);
			fclose(fp);
		}
	    m_pHView->GetModel()->GetStreamFileTK()->Restart();

	}
#ifdef PARASOLID
	else if (wcsstr(L"x_t", extension)) {

		((HSolidModel *)m_pHView->GetModel())->Read(stdwcs.c_str());
		m_pHView->EmitSegment(m_pHView->GetModel()->GetModelKey());
	}
#endif
	else if (wcsstr(L"snap", extension)) {

		LocalSetOperator(new HOpCameraManipulate(m_pHView));
		((HOpCameraManipulate *)m_pHView->GetOperator())->GetOrbitOperator()->SetSceneBoundingBoxVis(m_bounding_on);

		m_pHView->Update();

		return;

	} else {

		result = m_pHBaseModel->Read(stdwcs.c_str(), m_pHView);
	}

	if(result == InputVersionMismatch)
		QMessageBox::information( this, "Qt HOOPS Viewer\n",
		"This file was created with a newer version of the HOOPS/Stream Toolkit.\n"
		"To view it, this application will need to be updated.\n");
	else if(result == InputBadFileName)
		QMessageBox::information( this, "Qt HOOPS Viewer\n",
		"A problem occured with the file name provided.\n"
		"perhaps you don't have read permision or it is missing.\n");
	else if(result == InputNotHandled)
		QMessageBox::information( this, "Qt HOOPS Viewer\n",
		"This program doesn't have a handler for this file operation.\n");
	else if(result != InputOK)
		QMessageBox::information( this, "Qt HOOPS Viewer\n",
		"A problem occured during this file operation.\n");

	SetupView();

	LocalSetOperator(new HOpCameraManipulate(m_pHView));
	((HOpCameraManipulate *)m_pHView->GetOperator())->GetOrbitOperator()->SetSceneBoundingBoxVis(m_bounding_on);

	m_pHView->Update();
}

void MyHQWidget::ProcessFilters(QString & filters, const char * file_types) 
{

	if(strstr(file_types, "pdf"))
		filters += QString(";;PDF (*.pdf)");

	if(strstr(file_types, "hp"))
		filters += QString(";;HPGL2 (*.hp)");

	if(strstr(file_types, "cgm"))
		filters += QString(";;CGM (*.cgm)");

	if(strstr(file_types, "html"))
		filters += QString(";;HOOPS 3D Stream Control (*.html)");

	if(strstr(file_types, "wrl"))
		filters += QString(";;VRML (*.wrl)");

	if(strstr(file_types, "jpg"))
		filters += QString(";;Jpeg (*.jpg *.jpeg)");

	if(strstr(file_types, "bmp"))
		filters += QString(";;Bmp (*.bmp)");

	if(strstr(file_types, "png"))
		filters += QString(";;Png (*.png)");

	if(strstr(file_types, "tif"))
		filters += QString(";;Tiff (*.tif *.tiff)");

	if(strstr(file_types, "gif"))
		filters += QString(";;Gif (*.gif)");

	if(strstr(file_types, "stl"))
		filters += QString(";;Stereolithography files (*.stl)");

	if(strstr(file_types, "obj"))
		filters += QString(";;Alias Wavefront (*.obj)");
}


// open a load file dialog
void MyHQWidget::OnLoad()
{
	QString filters = QString(
#ifdef PARASOLID
	"Parasolid Files (*.X*T)" ";;" 
#endif
	"HOOPS Files (*.hsf *.hmf)");
   
	ProcessFilters(filters, HDB::GetHIOManager()->GetInputHandlerTypes());

	filters += QString(";;HOOPS Snapshot (*.snap)");

	QString fname = QFileDialog::getOpenFileName(
                    this,
                    "Choose a file",
					m_lastFile,
                    filters);

	if (!fname.isEmpty()){
		load(fname);
                m_lastFile = fname;
		emit load_successful();
	}
	return;
}

// clear
void MyHQWidget::OnClear()
{
	if( m_pHView->GetModel()->GetBhvBehaviorManager() ){
		if(m_pHView->GetModel()->GetBhvBehaviorManager()->IsPlaying()){
			m_pHView->GetModel()->GetBhvBehaviorManager()->Stop();
			m_pHView->GetModel()->GetBhvBehaviorManager()->DeactivateAllAnimations();
		}
	}

	LocalSetOperator(new HOpCameraManipulate(m_pHView));
	((HOpCameraManipulate *)m_pHView->GetOperator())->GetOrbitOperator()->SetSceneBoundingBoxVis(m_bounding_on);

	m_pHView->Flush(true);
	SetupView();

	m_pHView->Update();
}

void MyHQWidget::OnPrintPage(QString const & in_filename)
{
	H_UTF8 hutf8;
	hutf8.encodedText<char>(in_filename.toUtf8().data());
	H_WCS hwcs(hutf8);
	std::wstring stdwcs(hwcs.encodedText());
	m_pHBaseModel->Write(stdwcs.c_str(), m_pHView);
}

void MyHQWidget::OnPrint()
{
        HBaseView* pHView        = m_pHView;
		char driver_opts[MVO_BUFFER_SIZE];
        HOutputHandlerOptions* options = new HOutputHandlerOptions();



        options->m_pHBaseView = pHView;

        options->m_Paper_Width = 8.5;
        options->m_Paper_Height = 11;
        options->m_Window_Width = this->width();
        options->m_Window_Height = this->height();

        options->m_Image_Dpi = 300;

		sprintf (driver_opts, "debug = %d", DEBUG_PRINT_DIALOG);
		HC_QSet_Driver_Options("/driver/Qt", driver_opts); 
		ignore_update = true;
        HUtility::TwoPassPrint("/driver/Qt/printer", options);
		ignore_update = false;
        HC_Delete_Segment("/driver/Qt/printer");

        free (options);
}

static void GetExtension(wchar_t const * filter, wchar_t * extension)
{
    const wchar_t *start = wcsstr(filter, L"(*.")+3;
    wcscpy(extension, start);
    *(wcsstr(extension, L")")) = L'\0';
}

#include <iostream>

void MyHQWidget::OnSaveFileAs()
{
	// when using the static dialog, use double semicolons to seperate the filters
	QString filters = QString(tr("HOOPS Stream File (*.hsf);;HOOPS Metafile (*.hmf)"));

        ProcessFilters(filters, HDB::GetHIOManager()->GetOutputHandlerTypes());

	QString fn = QFileDialog::getSaveFileName(
                    this,
                    tr("Save As"),
			m_lastFile,
                    filters
			);

	if (!fn.isEmpty()){

		H_UTF8 hutf8;
		hutf8.encodedText<char>(fn.toUtf8().data());
		H_WCS hwcs(hutf8);
		std::wstring file_name(hwcs.encodedText());

                float width = 0, height = 0;

		if (
                        fn.endsWith("tif", Qt::CaseInsensitive) ||
                        fn.endsWith("tiff", Qt::CaseInsensitive) ||
                        fn.endsWith("jpg", Qt::CaseInsensitive) ||
                        fn.endsWith("jpeg", Qt::CaseInsensitive) ||
                        fn.endsWith("png", Qt::CaseInsensitive) ||
                        fn.endsWith("bmp", Qt::CaseInsensitive) ){
			width=10.00;
			height=6.25;
		}
                else{
                    width = 8.5;
                    height = 11;
                }

		HFileOutputResult result = m_pHBaseModel->Write(file_name.c_str(), m_pHView, 8.5, 11);

		if(result == OutputBadFileName)
			QMessageBox::information( this, "Qt HOOPS Viewer",
                        QString("An error occurred while writing to ") + fn +
			QString(".\nYou may not have write permission...\n"));
		else if(result == OutputNotHandled)
			QMessageBox::information( this, "Qt HOOPS Viewer",
                        QString("An error occurred while writing to ") + fn +
			QString(".\nThere's no output handler for this file type...\n"));
		else if(result != OutputOK)
			QMessageBox::information( this, "Qt HOOPS Viewer",
                        QString("An error occurred while writing to ") + fn +
			QString(".\n\n"));
                else
                    m_lastFile = fn;
	}

}

// perspective
void MyHQWidget::OnPerspective()
{
	m_pHView->SetProjMode(ProjPerspective);
	m_pHView->Update();
}

// orthographic
void MyHQWidget::OnOrthographic()
{
	m_pHView->SetProjMode(ProjOrthographic);
	m_pHView->Update();
}

void MyHQWidget::OnXyPlane()
{
	m_pHView->SetViewMode(HViewXY);
}

void MyHQWidget::OnXzPlane()
{
	m_pHView->SetViewMode(HViewXZ);
}

void MyHQWidget::OnYzPlane()
{
	m_pHView->SetViewMode(HViewYZ);
}

void MyHQWidget::OnApertureSelect()
{
	LocalSetOperator(new HOpSelectAperture(m_pHView));
}

void MyHQWidget::OnWindowSelect()
{
	LocalSetOperator(new HOpSelectArea(m_pHView));
}

void MyHQWidget::OnDeleteSelectionList() 
{
	m_pHView->DeleteSelectionList();
	m_pHView->EmitDeleteSelectionListMessage();
	m_pHView->Update();	
}

void MyHQWidget::OnTranslate()
{
	LocalSetOperator(new HOpObjectTranslate(m_pHView));
}

void MyHQWidget::OnWindowBackgroundColor() 
{
	if(!wnd_color_picker_dlg){
		wnd_color_picker_dlg=new HQWindowColorPickerDlg(0,this->GetHoopsView());
	}

	wnd_color_picker_dlg->hide();
	wnd_color_picker_dlg->show();
}

// sets wireframe render mode
void MyHQWidget::OnWireframe() 
{
    m_pHView->RenderWireframe();
	
    m_faces = false;
    m_edges = true;
    m_lines = true;
    m_lights = false;

    m_pHView->Update();
}


// sets flat-shaded render mode
void MyHQWidget::OnFlatShaded() 
{
    m_pHView->RenderFlat();	

    m_faces = true;
    m_edges = false;
    m_lines = false;

    m_pHView->Update();
}


// sets gouraud-shaded render mode
void MyHQWidget::OnGouraudShaded() 
{
    m_pHView->RenderGouraud();	

    m_faces = true;
    m_edges = false;
    m_lines = false;

    m_pHView->Update();
}

// sets phong-shaded render mode
void MyHQWidget::OnPhongShaded() 
{
    m_pHView->RenderPhong();

    m_faces = true;
    m_edges = false;
    m_lines = false;

    m_pHView->Update();
}


// sets hidden-line render mode
void MyHQWidget::OnHiddenLine() 
{
	m_pHView->SetRenderMode(HRenderHiddenLine, true);

    m_faces = true;
    m_edges = true;
    m_lines = true;
    m_lights = false;

    m_pHView->Update();
}

// sets fast hidden-line render mode
void MyHQWidget::OnHiddenLineFast() 
{
    m_pHView->RenderHiddenLineFast();

    m_faces = true;
    m_edges = true;
    m_lines = true;
    m_lights = false;

    m_pHView->Update();
}

// sets silhouette mode
void MyHQWidget::OnSilhouette() 
{
    m_pHView->RenderSilhouette();

    m_faces = false;
    m_edges = true;
    m_lines = true;
    m_lights = false;

    m_pHView->Update();
}

// sets wireframe-with-silhouette mode
void MyHQWidget::OnWireframeWithSilhouette() 
{
    m_pHView->RenderWireframeWithSilhouette();

    m_faces = false;
    m_edges = true;
    m_lines = true;
    m_lights = false;

    m_pHView->Update();
}

// sets shaded wireframe render mode
void MyHQWidget::OnShadedWireframe() 
{
    m_pHView->RenderShadedWireframe();

    m_faces = false;
    m_edges = true;
    m_lines = true;
    m_lights = true;

    m_pHView->Update();
}

// sets vertices render mode
void MyHQWidget::OnVertices() 
{
    m_pHView->RenderVertices();

    m_faces = false;
    m_edges = false;
    m_lines = false;
    m_lights = false;
	m_markers = true;

    m_pHView->Update();
}

// sets shaded vertices render mode
void MyHQWidget::OnShadedVertices() 
{
    m_pHView->RenderShadedVertices();

    m_faces = false;
    m_edges = false;
    m_lines = false;
    m_lights = true;
	m_markers = true;

    m_pHView->Update();
}

void MyHQWidget::OnGenerateSampleData() 
{
	HMySelectionSet *ss = (HMySelectionSet *)m_pHView->GetSelection();

	unsigned int i = 0;
	for(i = 0; i < ss->GetSize(); i++)
	{
		HC_KEY key = ss->GetAt(i);
		HShellVertexData data;
		data.SetKey(key);
		HUtilityGeometryCreation::ComputeFIndexDemoData(&data);
	}

	m_pHView->Update();	
}

void MyHQWidget::OnColorIndexInterpolation() 
{

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		if (m_color_index_int)
		{
			m_color_index_int = false;
			HC_Set_Rendering_Options("no color index interpolation");
		}
		else
		{
			m_color_index_int = true;
			HC_Set_Rendering_Options("color index interpolation");
		}
	HC_Close_Segment();

	m_pHView->Update();
}


void MyHQWidget::OnColorInterpolation() 
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


// lod on and off
void MyHQWidget::OnViewLevelOfDetail() 
{
    // toggle on off	
    if(m_pHView->GetLodMode())
		m_pHView->SetLodMode(false);
	else {
		m_pHView->SetLodMode(true);
		HC_Regenerate_LOD_By_Key(m_pHView->GetViewKey(),"");
	}

	m_pHView->Update();
}


void MyHQWidget::OnViewLevelOfDetailOptions() 
{

	if(!lod_control){

		lod_control = new QWidget;
		lod_control->setFixedSize(250,100);

		QVBoxLayout * lod_layout= new QVBoxLayout(lod_control); 

		lod_slider = new QSlider(Qt::Horizontal, lod_control);
		lod_slider->setValue(20);
		lod_slider->setGeometry(5,5,200,30);
		connect( lod_slider, SIGNAL(valueChanged(int)), this, SLOT(OnViewLevelOfDetailThreshold())); 

		lod_label = new QLabel((QWidget*) lod_control);
		lod_label->setAlignment(Qt::AlignLeft);


		lod_layout->addWidget(lod_slider);
		lod_layout->addSpacing(5);
		lod_layout->addWidget(lod_label);
		lod_layout->addSpacing(5);

		lod_layout->activate();

	}

	char t[1024];    
	sprintf(t,"LOD Threshold: %d", lod_slider->value());
	lod_label->setText(t);
	lod_label->show();
	lod_control->show();

	m_pHView->Update();
}

void MyHQWidget::OnViewLevelOfDetailThreshold() 
{
	int v = lod_slider->value();
    m_pHView->SetLodThreshold(v);

    char t[1024];    
    sprintf(t,"LOD Threshold: %d", lod_slider->value());
    lod_label->setText(t);


    m_pHView->Update();

}


// maintain frame rate
void MyHQWidget::OnViewFrameRateOptions() 
{	
#if 0
		// frame rate dialog box
	if(!framerate_dlg){
		framerate_dlg = new HQFrameRateDlg(this, "Frame Rate Options",m_pHView);
		framerate_dlg->exec();
	}
	else
		//framerate_dlg->show();
		framerate_dlg->exec();
#endif

	if(!new_frame_rate_dlg){
		framerateui = new FramerateUi::Dialog;
		new_frame_rate_dlg = new HQNewFrameRateDialog(this);
		framerateui->setupUi(new_frame_rate_dlg);
		new_frame_rate_dlg->show();
	}
	else{
		new_frame_rate_dlg->show();
	}

}

HQNewFrameRateDialog::HQNewFrameRateDialog(MyHQWidget* w){
	my_hqwidget = w;
}

void HQNewFrameRateDialog::accept(){
	HBaseView* m_pHView = my_hqwidget->GetHoopsView();

	if(my_hqwidget->framerateui->target_framerate_radio_button->isChecked()){
		if(my_hqwidget->framerateui->comboBox->currentText() == QString("Fixed Framerate"))
			m_pHView->SetFramerateMode(FramerateFixed,my_hqwidget->framerateui->target_framerate_fps_line_edit->text().toFloat(), my_hqwidget->framerateui->max_thresh_px_line_edit->text().toInt());
		else{
			m_pHView->SetViewUpdateMode(OnDemand);
			m_pHView->SetFramerateMode(FramerateTarget,my_hqwidget->framerateui->target_framerate_fps_line_edit->text().toFloat(), my_hqwidget->framerateui->max_thresh_px_line_edit->text().toInt());
		}
	}
	else if (my_hqwidget->framerateui->none_radio_button->isChecked()){
		m_pHView->SetFramerateMode(FramerateOff);
		m_pHView->SetCullingThreshold(0);
	}
	else if (my_hqwidget->framerateui->culling_thresh_radio_btn->isChecked()){
		m_pHView->SetFramerateMode(FramerateOff);
		m_pHView->SetCullingThreshold(my_hqwidget->framerateui->max_thresh_px_line_edit->text().toInt());
	}

/*
		if(CAppSettings::UseFramerate)
		{
			pBaseView->SetFramerateMode(CAppSettings::CurrentFramerateMode, CAppSettings::FramerateTime,
				CAppSettings::MaxThreshold);
			if(CAppSettings::CurrentFramerateMode==FramerateTarget)
				pBaseView->SetViewUpdateMode(CAppSettings::TimerBasedUpdate ? Continuous : OnDemand);
		}
		else if (CAppSettings::CullingThresholdSet)
		{
			pBaseView->SetFramerateMode(FramerateOff);
			pBaseView->SetCullingThreshold(CAppSettings::CullingThreshold);
		}
		else
		{
 			pBaseView->SetFramerateMode(FramerateOff);
			pBaseView->SetCullingThreshold(0);
		}

*/

	QDialog::accept();
}

void MyHQWidget::OnViewFROptsChange() 
{
#if 0
	framerate_dlg->OnFROnOff();
	framerate_dlg->OnFROnOff();

	// MVO Framerate object
	HConstantFrameRate * constfrate = m_pHView->GetConstantFrameRateObject();

	if (framerate_dlg->GetFRState()){
		
		if (!framerate_dlg->GetOpStarted()){

			framerate_dlg->SetOpStarted(true);

			// use LOD for detail reduction
			HConstFRSimpType **mlist= HConstFRSimpType::CreateList(2);						
			mlist[0] = HFrNoSimp::Create(0,1);
			mlist[1] = HFrLodThreshold::Create(0,6);				
			
			constfrate->Init(framerate_dlg->GetMinFR(), mlist, 2);   
			constfrate->SetDetailLevel(1,1);
			// forces a recalculation of the LOD's
			#if 0
			// optional precalculation for LOD settings..		
			HC_Open_Segment_By_Key(m_pHView->GetModel()->GetModelKey());	

		
 			HC_Set_Rendering_Options("lod=on, lodo=(levels=5,ratio=0.5,preprocess)");     
 			HC_Control_Update_By_Key(m_pHView->GetViewKey(),"redraw everything");	
			HC_Update_Display();
  			HC_Close_Segment();				
			#endif

			constfrate->Start();
			
			// timer code turns frame rate heuristic off when operator is done
			if (!FRtimer)
				FRtimer = new QTimer(this);
		
			FRtimer->singleShot((int)(1000.0/framerate_dlg->GetMinFR()), this, SLOT(OnFRTimerDone()));
		}
		
#if (QT_VERSION >= 200)
		if (framerate_dlg->minFR_field->isModified()){
			constfrate->SetTargetFrameRate(framerate_dlg->GetMinFR());
			framerate_dlg->minFR_field->setModified(false);
		}
#endif
			
	}	
	else
	{	
		framerate_dlg->SetOpStarted(false);
		constfrate->Stop();	
		constfrate->Shutdown();   
	}

	m_pHView->Update();
#endif
}


#if 0
static void event_checker(void)
{

}
#endif

	// timer callback. increases the detail level
void MyHQWidget::OnFRTimerDone()
{
#if 0
	HConstantFrameRate *cframerate = m_pHView->GetConstantFrameRateObject();


	if (cframerate->GetActive())
	{	
//  No longer an interface to the framerate class	
//		cframerate->SetEventCheckerCallback(event_checker);
		if (!cframerate->ViewpointHasChanged() && !cframerate->GetActivityType()){

			cframerate->IncreaseDetailTemp();	
		}
		cframerate->SetActivityType(NoActivity);
	}	
	FRtimer->singleShot((int)(1000.0/framerate_dlg->GetMinFR()), this, SLOT(OnFRTimerDone()));
#endif
}// end OnTimerDone


void MyHQWidget::OnViewDisplayLists()
{

 
	m_pHView->SetDisplayListMode(!m_pHView->GetDisplayListMode());

 
    m_pHView->Update();	
}

// real time zoomer
void MyHQWidget::OnZoom() 
{
    LocalSetOperator(new HOpCameraZoom(m_pHView));
}

// window zoomer
void MyHQWidget::OnZoomToWindow() 
{
    LocalSetOperator(new HOpCameraZoomBox(m_pHView));
}

// resets the camera to view the world space extents of the model
void MyHQWidget::OnZoomToExtents() 
{
    m_pHView->ZoomToExtents();
}

// camera orbiter
void MyHQWidget::OnOrbit() 
{
    LocalSetOperator(new HOpCameraManipulate(m_pHView));	
	((HOpCameraManipulate *)m_pHView->GetOperator())->GetOrbitOperator()->SetSceneBoundingBoxVis(m_bounding_on);
}


// walk operator
void MyHQWidget::OnWalk() 
{
    LocalSetOperator(new HOpCameraWalk(m_pHView));
}


// object rotate
void MyHQWidget::OnRotate() 
{
    LocalSetOperator(new HOpObjectRotate(m_pHView));	
	
}

void MyHQWidget::OnObjectClash() 
{
    LocalSetOperator(new HOpObjectClash(m_pHView));		
}


// panner
void MyHQWidget::OnPan() 
{
    LocalSetOperator(new HOpCameraPan(m_pHView));		
}

// resets the camera to view the world space extents of the model
void MyHQWidget::OnSmoothTransition() 
{
    if (m_pHView->GetSmoothTransition())
		m_pHView->SetSmoothTransition(false);
	else
		m_pHView->SetSmoothTransition(true);
}


// create sphere
void MyHQWidget::OnCreateSphere() 
{

#ifdef PARASOLID
    LocalSetOperator(new HOpCreateSolidSphere(m_pHView));	
#else
    LocalSetOperator(new HOpCreateSphere(m_pHView));		
#endif

}

// create cone
void MyHQWidget::OnCreateCone() 
{
#ifdef PARASOLID
    LocalSetOperator(new HOpCreateSolidCone(m_pHView));	
#else
    LocalSetOperator(new HOpCreateCone(m_pHView));		
#endif

}



// create cylinder
void MyHQWidget::OnCreateCylinder() 
{

#ifdef PARASOLID
    LocalSetOperator(new HOpCreateSolidCylinder(m_pHView));	
#else
    LocalSetOperator(new HOpCreateCylinder(m_pHView));		
#endif
}

// create cutting plane
void MyHQWidget::OnCreateCuttingPlane()
{
    if (!m_pHView->GetCuttingPlanesExist("plane1"))
    {
		m_pHandleOperator = new HOpMoveHandle(m_pHView, (false));
		m_pHView->GetEventManager()->RegisterHandler((HMouseListener *)m_pHandleOperator, HMouseListener::GetType(), HLISTENER_PRIORITY_HIGH);

		HC_KEY key = HUtilityGeometryCreation::CreateCuttingPlane(m_pHView,"plane1");
		HUtilityGeomHandle::SetupCuttingPlaneManipulator(key, m_pHView);
    }
    else
    {
		m_pHView->GetEventManager()->UnRegisterHandler((HMouseListener *)m_pHandleOperator, HMouseListener::GetType());
		delete m_pHandleOperator;
		m_pHandleOperator = 0;

 		HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
			HC_Open_Segment("plane1");
				HUtilityGeomHandle::ClearAllHandles(0);
  				//if (!(GetAsyncKeyState(VK_SHIFT) & 32768))
					HC_Flush_Contents ("...", "geometry");
			HC_Close_Segment();
		HC_Close_Segment();
    }

    m_pHView->Update();	
}

void MyHQWidget::OnCreateTwosideSection(){
	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!HUtility::SegmentExists("twosection"))
			HUtilityGeometryCreation::CreateTwoSidedSection(m_pHView);
		else
			HC_Delete_Segment("twosection");
	HC_Close_Segment();
	m_pHView->Update();
}

void MyHQWidget::OnCreateThreesideSection(){
	HC_Open_Segment_By_Key(m_pHView->GetCuttingPlanesKey());
		if (!HUtility::SegmentExists("threesection"))
			HUtilityGeometryCreation::CreateThreeSidedSection(m_pHView);
		else
			HC_Delete_Segment("threesection");
	HC_Close_Segment();
	m_pHView->Update();
}


void MyHQWidget::OnCreateNurbs3D()
{
#ifdef PARASOLID
    LocalSetOperator(new HOpCreateSweptBsplineFixed(m_pHView));
#else
    LocalSetOperator(new HOpCreateNurbs3D(m_pHView));
#endif

}


// create NURBS Curve
void MyHQWidget::OnCreateNurbsCurve()
{
	LocalSetOperator(new HOpCreateNurbsCurve(m_pHView));	
}



void MyHQWidget::OnSubtract()
{
#ifdef PARASOLID
    ((HSolidView *)m_pHView)->BooleanOperation(PK_boolean_subtract_c);
#endif
}

void MyHQWidget::OnUnion()
{
#ifdef PARASOLID
    ((HSolidView *)m_pHView)->BooleanOperation(PK_boolean_unite_c);
#endif
}

void MyHQWidget::OnIntersect()
{
#ifdef PARASOLID
    ((HSolidView *)m_pHView)->BooleanOperation(PK_boolean_intersect_c);
#endif
}



void MyHQWidget::SetQueryDialogText(char* message)
{
	query_dialog->setText(message);
}

void MyHQWidget::ShowQueryDialog()
{
	query_dialog->show();
}

void MyHQWidget::OnQuery()
{
    if (!query_dialog){
	    // make a query dialog 
	    query_dialog = new QLabel("query_dialog", (QWidget*)0, 
		Qt::Tool | Qt::WindowStaysOnTopHint);
	    query_dialog->setMargin(10); 
	    query_dialog->setFrameStyle( QFrame::WinPanel | QFrame::Raised );
    }

    LocalSetOperator(new HMyQuery(m_pHView));
    ((HMyQuery*)m_pHView->GetCurrentOperator())->SetDialogMaker(this);
}


void MyHQWidget::OnToolsVisibilityEdges()
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_edges) {
		m_edges = false;
		HC_Set_Visibility ("edges = off");
	} else {
		m_edges = true;
		HC_Set_Visibility ("edges = on");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}


void MyHQWidget::OnToolsVisibilityLines()
{

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
    if (m_lines){
        m_lines = false;
        HC_Set_Visibility ("lines = off");
    } else {
		m_lines = true;
	    HC_Set_Visibility ("lines = on");
    }
    HC_Close_Segment ();

    m_pHView->Update();
}


void MyHQWidget::OnToolsVisibilityFaces()
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_faces) {
		m_faces = false;
		HC_Set_Visibility ("faces = off");
	} else {
		m_faces = true;
		HC_Set_Visibility ("faces = on");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}


void MyHQWidget::OnToolsVisibilityLights()
{

	HC_Open_Segment_By_Key (m_pHView->GetLightsKey());
	if (m_lights) {
		m_lights = false;
		HC_Set_Visibility ("lights = off");
	}
	else {
		m_lights = true;
		HC_Set_Visibility ("lights = (faces = on, edges = off, markers = off)");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}

void MyHQWidget::OnToolsVisibilityMarkers()
{
	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	if (m_markers) {
		m_markers = false;
		HC_Set_Visibility ("markers = off");
	} else {
		m_markers = true;
		HC_Set_Visibility ("markers = on");
	}
	HC_Close_Segment ();
	m_pHView->Update();
}


void MyHQWidget::OnToolsVisibilityCuttingLines() 
{
	m_pHView->SetCPGeomVisibility(!m_pHView->GetCPLineVisibility(),m_pHView->GetCPFaceVisibility());
	m_pHView->Update();
}

void MyHQWidget::OnToolsVisibilityCuttingFaces() 
{
	m_pHView->SetCPGeomVisibility(m_pHView->GetCPLineVisibility(),!m_pHView->GetCPFaceVisibility());
	m_pHView->Update();
}




void MyHQWidget::OnToolsVisibilityAxis() 
{
	if (m_axis_on) {
		m_axis_on = false; 
		m_pHView->SetAxisMode(AxisOff);
	}else{
		m_axis_on = true;   
		m_pHView->SetAxisMode(AxisOn);
		AdjustAxisWindow();
	}

	m_pHView->Update();	
}

void MyHQWidget::OnToolsVisibilityBoundingBox() 
{

	if (m_bounding_on) {
		m_bounding_on = false; 
	}else{
		m_bounding_on = true;   
	}

	OnOrbit();
}

void MyHQWidget::OnToolsVisibilityLightFollows() 
{

	if (m_light_follows) {
		m_light_follows = false; 
	}else{
		m_light_follows = true;   
	}

	OnOrbit();

	m_pHView->Update();	
}

void MyHQWidget::OnToolsVisibilityShadows() 
{

	if (m_shadows_on) {
		m_shadows_on = false; 
		m_pHView->SetShadowMode( HShadowNone );
	}else{
		m_shadows_on = true;   
		m_pHView->SetShadowMode( HShadowSoft );	
		HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
			HC_Set_Rendering_Options( "simple shadow = (resolution=64, blurring=4)" );
		HC_Close_Segment();
	}

	m_pHView->Update();	
}



void MyHQWidget::OnToolsVisibilityCuttingPlanes() 
{
	m_pHView->SetCuttingPlanesVisibility(!m_pHView->GetCuttingPlanesVisibility());
    m_pHView->Update();
}

void MyHQWidget::OnToolsVisibilityText() 
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

    m_pHView->Update();
	
}

void MyHQWidget::OnToolsTextTransformsPosition() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
	HC_Set_Text_Font("transforms = character position only");
    HC_Close_Segment();

	m_pHView->Update();
}

void MyHQWidget::OnToolsTextTransformsOff() 
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
	HC_Set_Text_Font("transforms = off");
    HC_Close_Segment();
	m_pHView->Update();	
}

void MyHQWidget::OnToolsTextTransformsOn() 
{
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HC_Set_Text_Font("transforms = on");
    HC_Close_Segment();
    m_pHView->Update();
}

void MyHQWidget::OnToolsTextFontArial() 
{
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HC_Set_Text_Font("name = (arial, Helvetica, sans serif)");
    HC_Close_Segment();
    m_pHView->Update();	
}

void MyHQWidget::OnToolsTextFontRoman() 
{
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HC_Set_Text_Font("name = roman");
    HC_Close_Segment();
    m_pHView->Update();	
}

void MyHQWidget::OnToolsTextFontStroked() 
{
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    HC_Set_Text_Font("name = stroked");
    HC_Close_Segment();
    m_pHView->Update();	
}


void MyHQWidget::OnViewPolygonHandednessRight()
{
	m_pHView->SetPolygonHandednessMode(HandednessRight);
    m_pHView->Update();	
}

void MyHQWidget::OnViewPolygonHandednessLeft()
{
	m_pHView->SetPolygonHandednessMode(HandednessLeft);
    m_pHView->Update();	
}

void MyHQWidget::OnViewPolygonHandednessNone()
{
	m_pHView->SetPolygonHandednessMode(HandednessNone);
    m_pHView->Update();	
}


void MyHQWidget::OnViewCoordinateSystemRightHanded()
{
	m_pHView->SetHandedness(HandednessRight);
    m_pHView->Update();	
}


void MyHQWidget::OnViewCoordinateSystemLeftHanded()
{
	m_pHView->SetHandedness(HandednessLeft);
    m_pHView->Update();	
}


void MyHQWidget::OnViewBackplaneCullingOn()
{
	m_pHView->SetBackplaneCulling(true);
    m_pHView->Update();	
}

void MyHQWidget::OnViewBackplaneCullingOff()
{
	m_pHView->SetBackplaneCulling(false);
    m_pHView->Update();	
}



void MyHQWidget::OnEdgeSelectLevel()
{
#ifdef PARASOLID
	((HSSelectionSet *)m_pHView->GetSelection())->SetSelectLevel(PK_CLASS_edge);

	m_pHView->GetSelection()->DeSelectAll();
	m_pHView->Update();

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		HC_Set_Selectability("faces = off, lines = on, edges = off");
	HC_Close_Segment();
#endif
}

void MyHQWidget::OnFaceSelectLevel()
{
#ifdef PARASOLID
	((HSSelectionSet*)m_pHView->GetSelection())->SetSelectLevel(PK_CLASS_face);
	m_pHView->GetSelection()->DeSelectAll();
	m_pHView->Update();

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		HC_Set_Selectability("faces = on, lines = off, edges = off");
	HC_Close_Segment();
#endif
}

void MyHQWidget::OnBodySelectLevel()
{
#ifdef PARASOLID
	((HSSelectionSet*)m_pHView->GetSelection())->SetSelectLevel(PK_CLASS_body);

	// deselect everything first since we're changing selection level
	// and the various operators don't support mixed entity types in
	// the selection list
	m_pHView->GetSelection()->DeSelectAll();
	m_pHView->Update();

	HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
	HC_Set_Selectability("faces = on, lines = on, edges = off");
	HC_Close_Segment();
#endif
}


void MyHQWidget::OnSegmentSelectLevel()
{
	((HMySelectionSet*)m_pHView->GetSelection())->SetSelectLevel(HMySelectionSet::SegmentSelectLevel);
}

void MyHQWidget::OnEntitySelectLevel()
{
	((HMySelectionSet*)m_pHView->GetSelection())->SetSelectLevel(HMySelectionSet::EntitySelectLevel);
}


void MyHQWidget::OnRightButtonDown(QMouseEvent * e)
{

	QMenu * s = new QMenu();

#if defined(PARASOLID)
	bool sl=(((HSSelectionSet*)m_pHView->GetSelection())->GetSelectLevel() == PK_CLASS_body);
	s->setItemChecked(s->insertItem( "Body", this , SLOT(OnBodySelectLevel())), sl?true:false);

	sl = (((HSSelectionSet *)m_pHView->GetSelection())->GetSelectLevel() == PK_CLASS_edge);
	s->setItemChecked(s->insertItem( "Edge", this , SLOT(OnEdgeSelectLevel())), sl?true:false);

	sl = (((HSSelectionSet *)m_pHView->GetSelection())->GetSelectLevel() == PK_CLASS_face);
	s->setItemChecked(s->insertItem( "Face", this , SLOT(OnFaceSelectLevel())), sl?true:false);
#else
	bool sl=(((HMySelectionSet*)m_pHView->GetSelection())->GetSelectLevel() == HMySelectionSet::SegmentSelectLevel);
	QAction* action;

	action = s->addAction( "Entity", this , SLOT(OnEntitySelectLevel()));
	action->setCheckable(true);
	action->setChecked(sl?false:true);

	action = s->addAction( "Segment", this , SLOT(OnSegmentSelectLevel()));
	action->setCheckable(true);
	action->setChecked(sl?true:false);
#endif

	QMenu * v = new QMenu();

	action = v->addAction("Edges", this , SLOT(OnToolsVisibilityEdges()));
	action->setCheckable(true);
	action->setChecked(m_edges);
	
	action = v->addAction("Lines", this , SLOT(OnToolsVisibilityLines()));
	action->setCheckable(true);
	action->setChecked(m_lines);
	
	action = v->addAction("Faces", this , SLOT(OnToolsVisibilityFaces()));
	action->setCheckable(true);
	action->setChecked(m_faces);
	
	action = v->addAction("Lights", this , SLOT(OnToolsVisibilityLights()));
	action->setCheckable(true);
	action->setChecked(m_lights);
	
	action = v->addAction("Markers", this , SLOT(OnToolsVisibilityMarkers()));
	action->setCheckable(true);
	action->setChecked(m_markers);
	
	action = v->addAction("Text" , this , SLOT(OnToolsVisibilityText()));
	action->setCheckable(true);
	action->setChecked(m_text);

	v->addSeparator();
	
	action = v->addAction("Cutting Planes", this , SLOT(OnToolsVisibilityCuttingPlanes()));
	action->setCheckable(true);
	action->setChecked(m_pHView->GetCuttingPlanesVisibility());
	
	action = v->addAction("Cutting Lines", this , SLOT(OnToolsVisibilityCuttingLines()));
	action->setCheckable(true);
	action->setChecked(m_pHView->GetCPLineVisibility());
	
	action = v->addAction("Cutting Faces", this , SLOT(OnToolsVisibilityCuttingFaces()));
	action->setCheckable(true);
	action->setChecked(m_pHView->GetCPFaceVisibility());
	
	v->addSeparator();
	
	action = v->addAction("Rotation Axis",this , SLOT(OnToolsVisibilityAxis()));
	action->setCheckable(true);
	action->setChecked(m_axis_on);
	
	action = v->addAction("Bounding Box",this , SLOT(OnToolsVisibilityBoundingBox()));
	action->setCheckable(true);
	action->setChecked(m_bounding_on);
	
	action = v->addAction("Light Follows Camera",this , SLOT(OnToolsVisibilityLightFollows()));
	action->setCheckable(true);
	action->setChecked(m_light_follows);
	
	action = v->addAction("Shadows",this , SLOT(OnToolsVisibilityShadows()));
	action->setCheckable(true);
	action->setChecked(m_shadows_on);

	

	QMenu * r = new QMenu();
	HRenderMode rm = m_pHView->GetRenderMode();

	action = r->addAction("Wireframe", this, SLOT(OnWireframe()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderWireframe));
	
	action = r->addAction("Flat", this, SLOT(OnFlatShaded()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderFlat));
	
	action = r->addAction("Gouraud", this, SLOT(OnGouraudShaded()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderGouraud));
	
	action = r->addAction("Phong", this, SLOT(OnPhongShaded()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderPhong));
	
	action = r->addAction("Hidden Line", this, SLOT(OnHiddenLine()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderHiddenLine));

	action = r->addAction("Fast Hidden Line", this, SLOT(OnHiddenLineFast()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderHiddenLineFast));
	
	action = r->addAction("Silhouette", this, SLOT(OnSilhouette()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderSilhouette));

	action = r->addAction("Wireframe Silhouette", this, SLOT(OnWireframeWithSilhouette()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderWireframeWithSilhouette));

	action = r->addAction("Shaded Wireframe", this, SLOT(OnShadedWireframe()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderShadedWireframe));

	action = r->addAction("Vertices", this, SLOT(OnVertices()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderVertices));

	action = r->addAction("Shaded Vertices", this, SLOT(OnShadedVertices()));
	action->setCheckable(true);
	action->setChecked((rm==HRenderShadedVertices));

	r->addSeparator();

		QMenu * c = new QMenu();

		
		action = c->addAction("By Colormap Index", this, SLOT(OnColorInterpolation()));
		action->setCheckable(true);
		action->setChecked(m_color_int);
		
		action = c->addAction("By Value", this, SLOT(OnColorIndexInterpolation()));
		action->setCheckable(true);
		action->setChecked(m_color_index_int);
		
		c->setTitle("Color Interpolation");
		
	r->addMenu(c);


	QMenu * t = new QMenu();
	char name[256], transforms[256];
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Show_One_Text_Font("name", name);
		HC_Show_One_Text_Font("transforms", transforms);
	HC_Close_Segment();
		
		QMenu * tf = new QMenu();
		
		action = tf->addAction("Roman", this, SLOT(OnToolsTextFontRoman()));
		action->setCheckable(true);
		action->setChecked(streq("roman", name));
		
		action = tf->addAction("Arial" , this, SLOT(OnToolsTextFontArial()));
		action->setCheckable(true);
		action->setChecked(streq("(arial,helvetica,sans serif)", name));
		
		action = tf->addAction("stroked" , this, SLOT(OnToolsTextFontStroked()));
		action->setCheckable(true);
		action->setChecked(streq("stroked", name));
		
		tf->setTitle("Fonts");
	
	t->addMenu(tf);

	
	
		QMenu * tt = new QMenu();
		
		action = tt->addAction("On", this, SLOT(OnToolsTextTransformsOn()));
		action->setCheckable(true);
		action->setChecked(streq("on", transforms));

		action = tt->addAction("Off", this, SLOT(OnToolsTextTransformsOff()));
		action->setCheckable(true);
		action->setChecked(streq("off", transforms));

		action = tt->addAction("Character Positions",this, SLOT(OnToolsTextTransformsPosition()));
		action->setCheckable(true);
		action->setChecked(streq("character position only", transforms));
		
		tt->setTitle("Transforms");

	t->addMenu(tt);
	t->addSeparator();

	action = t->addAction("Hide Overlapped Text", this, SLOT(OnOverlappedText()));
	action->setCheckable(true);
	action->setChecked(m_pHView->GetHideOverlappedText());

	//quickmoves preference menu
	QMenu * q = new QMenu();

	char pref[256];
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Show_One_Driver_Option("quick moves preference", pref);
	HC_Close_Segment();

	action = q->addAction("Default", this, SLOT(OnQuickmovesDefault()));
	action->setCheckable(true);
	action->setChecked(streq("default", pref));

	action = q->addAction("Overlay", this, SLOT(OnQuickmovesOverlay()));
	action->setCheckable(true);
	action->setChecked(streq("overlay", pref));

	action = q->addAction("XOR", this, SLOT(OnQuickmovesXOR()));
	action->setCheckable(true);
	action->setChecked(streq("xor", pref));

	action = q->addAction("Spriting", this, SLOT(OnQuickmovesSpriting()));
	action->setCheckable(true);
	action->setChecked(streq("spriting", pref));


	//stats menu
	QMenu * st = new QMenu();

	char stats[256], time_stats[256];
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Show_One_Driver_Option("display stats", stats);
		HC_Show_One_Driver_Option("display time stats", time_stats);
	HC_Close_Segment();

	action = st->addAction("Display Stats", this, SLOT(OnDisplayStats()));
	action->setCheckable(true);
	action->setChecked(streq("on", stats));

	action = st->addAction("Display Time Stats", this, SLOT(OnDisplayTimeStats()));
	action->setCheckable(true);
	action->setChecked(streq("on", time_stats));

	
	m = new QMenu();
	s->setTitle("Selection Level");
	m->addMenu(s);
	v->setTitle("Visibility");
	m->addMenu(v);
	r->setTitle("Render Mode");
	m->addMenu(r);
	t->setTitle("Text");
	m->addMenu(t);
	q->setTitle("Quickmoves Preference");
	m->addMenu(q);
	st->setTitle("Display Statistics");
	m->addMenu(st);

	aa = m->addMenu("Anti-Aliasing");

	m_fullscreen = m->addAction("Fullscreen", this, SLOT(OnFullscreen()));
		m_fullscreen->setCheckable(true);
		m_fullscreen->setChecked(fullscreen_on ? true : false);

	bool enable_text_lines = true;
	char rend_opts[512];
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Show_One_Rendering_Option("anti-alias", rend_opts);
		if(strstr(rend_opts, "no screen") || strstr(rend_opts, "off"))
			enable_text_lines = true;
		else
			enable_text_lines = false;
	HC_Close_Segment();

	m_aatext = aa->addAction("Text", this, SLOT(OnAntiAliasText()));
	m_aatext->setCheckable(true);
	m_aatext->setChecked(m_aa_onoff?m_aa_text:false);
	m_aatext->setEnabled(enable_text_lines);

	m_aalines = aa->addAction("Lines + Edges", this, SLOT(OnAntiAliasLinesEdges()));
	m_aalines->setCheckable(true);
	m_aalines->setChecked(m_aa_onoff?m_aa_lines:false);
	m_aalines->setEnabled(enable_text_lines);

	//right-click selection stuff
	m_PositionOnRightClick.Set((float)e->x(), (float)e->y(), 0);
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
   
    if (m_KeyUnderCursor == -1)
    {
		action = m->addAction("Transparency", this, SLOT(OnRightClickTransparency()));
		action->setEnabled(false);
    }
    else
    {
		HC_Open_Segment_By_Key(HUtility::GrabSegment(m_KeyUnderCursor));

	    char oname[4096];
	    HC_KEY tempkey = HObjectManager::FindHObjectSegment(HUtility::GrabSegment(m_KeyUnderCursor), oname);
	    if (strcmp(oname, "note") == 0)	    	    
	    {	    
			m_KeyUnderCursor = tempkey;
	    }	     
	    

		//check to see if object is transparent in any way
		HPoint color;
		char colorspace[1024];
		HC_Show_One_Net_Color_By_Value("faces=transmission",colorspace,&color.x,&color.y,&color.z);
		
		//if the format we get back is not in rgb format, convert to rgb
		if(strcmp(colorspace,"rgb") != 0)
			HC_Compute_Color_By_Value(colorspace, &color, "rgb", &color);

		action = m->addAction("Transparency", this, SLOT(OnRightClickTransparency()));
		action->setCheckable(true);
		if(color.x == 0 && color.y == 0 && color.z == 0){  
			action->setEnabled(true);
			action->setChecked(false);
		}
		else{ 
			action->setEnabled(true);
			action->setChecked(true);
		}

	    HC_Close_Segment();

    }

	m->exec(QCursor::pos());

}

void MyHQWidget::OnOverlappedText(){
	m_pHView->SetHideOverlappedText(!(m_pHView->GetHideOverlappedText()));
}

void MyHQWidget::OnQuickmovesDefault(){
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options("quick moves preference = default");
	HC_Close_Segment();
}

void MyHQWidget::OnQuickmovesOverlay(){
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options("quick moves preference = overlay");
	HC_Close_Segment();
}

void MyHQWidget::OnQuickmovesXOR(){
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options("quick moves preference = xor");
	HC_Close_Segment();
}

void MyHQWidget::OnQuickmovesSpriting(){
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options("quick moves preference = spriting");
	HC_Close_Segment();
}

void MyHQWidget::OnDisplayStats(){
	char stats[256];
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Show_One_Driver_Option("display stats", stats);
		if(streq("on", stats))
			HC_Set_Driver_Options("no display stats");
		else
			HC_Set_Driver_Options("display stats");
	HC_Close_Segment();
}

void MyHQWidget::OnDisplayTimeStats(){
	char stats[256];
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Show_One_Driver_Option("display time stats", stats);
		if(streq("on", stats))
			HC_Set_Driver_Options("no display time stats");
		else
			HC_Set_Driver_Options("display time stats");
	HC_Close_Segment();
}

void MyHQWidget::OnRightClickTransparency(){
	HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(m_KeyUnderCursor));
		HPoint color;
		char colorspace[1024];
		HC_Show_One_Net_Color_By_Value("faces=transmission",colorspace,&color.x,&color.y,&color.z);

		//if the format we get back is not in rgb format, convert to rgb
		if(strcmp(colorspace,"rgb") != 0)
			HC_Compute_Color_By_Value(colorspace, &color, "rgb", &color);

		//if not transparent
		if(color.x == 0 && color.y == 0 && color.z == 0)
		{
			char transparent_color[1024];
			char usertransmission[1024];

			//if transparency has been saved, then restore it and remove the useroption
			HC_Show_One_Net_User_Option("HUserTransmission",usertransmission);
			if(strcmp(usertransmission, "") != 0)
			{
				sprintf(transparent_color, "faces = (transmission = %s)",usertransmission);
				HC_UnSet_One_User_Option("HUserTransmission");
			}
			else
				sprintf(transparent_color, "faces = (transmission = r=%f g=%f b=%f)",m_default_transmission,m_default_transmission,m_default_transmission);
			
			HC_Set_Color(transparent_color);
		}
		//if transparent
		else
		{
			//if the transmission color isn't the default, then set a user option to save it
			if(color.x != m_default_transmission && color.y != m_default_transmission && color.z != m_default_transmission)
			{
				char usertransmission[1024];
				sprintf(usertransmission, "HUserTransmission = r=%f g=%f b=%f", color.x, color.y, color.z);
				HC_Set_User_Options(usertransmission);
			}

			HC_Set_Color("faces = (transmission = black)");
		}

	HC_Close_Segment();
	
    m_pHView->Update();	
}

void MyHQWidget::OnAntiAliasText(){
	m_aa_text = !m_aa_text;
	m_aa_onoff = (m_aa_lines||m_aa_text)?true:false;
	m_pHView->SetTextAntialiasing(m_aa_text);
}

void MyHQWidget::OnAntiAliasLinesEdges(){
	m_aa_lines = !m_aa_lines;
	m_aa_onoff = (m_aa_lines||m_aa_text)?true:false;
	m_pHView->SetLineAntialiasing(m_aa_lines);
}

void MyHQWidget::OnAntiAliasOff(){
	m_aa_onoff = false;
	char rend_opts[512];
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Show_One_Rendering_Option("anti-alias", rend_opts);
		if(strstr(rend_opts, "no screen") || strstr(rend_opts, "off"))
			HC_Set_Rendering_Options("anti-alias = (screen = on)");
		else
			HC_Set_Rendering_Options("anti-alias = no screen");
	HC_Close_Segment();
}

void MyHQWidget::OnFullscreen(){
	if(m_fullscreen->isChecked()){
		m_hqapplication->OnFullscreen(true);
		fullscreen_on = true;
	}
	else{
		m_hqapplication->OnFullscreen(false);
		fullscreen_on = false;
	}
}

void MyHQWidget::OnMidButtonDblClk(QMouseEvent * e)
{
    
    
    HC_KEY key = -1;
    int offset1,offset2,offset3;
    
    HPoint localpixels, localwindow;
    localpixels.Set(e->x(), e->y(), 0);
    
    HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
    
    HC_Compute_Coordinates(".", "local pixels", &localpixels, "local window", &localwindow);
    HC_Close_Segment();
    HC_Open_Segment_By_Key(m_pHView->GetViewKey());
    if ( HC_Compute_Selection(".",".","v", localwindow.x, localwindow.y))
    {	
	HC_Show_Selection_Element (&key, &offset1, &offset2, &offset3);
	
    }
    HC_Close_Segment();
    
    if (key != -1)
    {
	char type[4096];
	HC_Show_Key_Type(key, type);
	if (strcmp(type,"segment") != 0)
	    key = HC_KShow_Owner_By_Key(key);
	
	m_pHView->FitSelection(key);
    }
    else
	m_pHView->FitWorld();
    
    m_pHView->Update();
    
}



void MyHQWidget::OnAnimate() 
{
	float t0, t1, fsec;
	int tsec;
	char temp[256];

	HC_Show_Time(&t0);  

	m_pHView->Animate(40);

	HC_Show_Time(&t1);

	fsec = 40.0f/(t1-t0); 
	tsec = (int) ((float)m_pHBaseModel->GetHModelInfo()->GetTotalTriangles() * fsec);
	
	sprintf(temp, "Animation: %f frames per second.  %d triangles per second", fsec, tsec);

	QMessageBox::information( this, "qthoopsview", temp);
		
}

void MyHQWidget::OnAnimateBack() 
{

	m_pHView->GetModel()->GetBhvBehaviorManager()->Rewind();

}

void MyHQWidget::OnAnimatePlayPause() 
{
	if( !m_pHView->GetModel()->GetBhvBehaviorManager() )
		return;

	if(m_pHView->GetModel()->GetBhvBehaviorManager()->IsPlaying())
		m_pHView->GetModel()->GetBhvBehaviorManager()->Stop();
	else
		m_pHView->GetModel()->GetBhvBehaviorManager()->Continue();
}


void MyHQWidget::OnAnimateStop() 
{

	m_pHView->GetModel()->GetBhvBehaviorManager()->Stop();

}


void MyHQWidget::CreateMenus()
{
	// We use Actions now.  This function should probably be renamed "CreateActions",
	// and the code where the actions are created could be moved down here.
}

void MyHQWidget::UpdateMenus()
{

	//We don't use this function any more. (QButtonGroup offers the mutual exclusion
	//features that we had implemented here before).

}
  
QMenu * MyHQWidget::GetManipulateMenu()
{
	return manipulate_menu;
}

QMenu * MyHQWidget::GetCreateMenu()
{
	return create_menu;
}

QMenu * MyHQWidget::GetSelectionMenu()
{
	return selection_menu;
}

QMenu * MyHQWidget::GetViewMenu()
{
	return view_menu ;
}

QMenu * MyHQWidget::GetToolMenu()
{
	return tools_menu;
}

void MyHQWidget::OnFrontView()
{
   m_pHView->SetViewMode(HViewXY);
}

void MyHQWidget::OnBackView()
{
   m_pHView->SetViewMode(HViewYX);
}

void MyHQWidget::OnTopView()
{
    m_pHView->SetViewMode(HViewXZ);
}

void MyHQWidget::OnBottomView()
{
   m_pHView->SetViewMode(HViewZX);
}

void MyHQWidget::OnLeftView()
{
   m_pHView->SetViewMode(HViewYZ);
}

void MyHQWidget::OnRightView()
{
    m_pHView->SetViewMode(HViewZY);
}

void MyHQWidget::OnIsometricView()
{
   m_pHView->SetViewMode(HViewIso);
}


void MyHQWidget::OnFreehandMarkup()
{
    LocalSetOperator(new HOpMarkupFreehand(m_pHView));
}

void MyHQWidget::OnRectangleMarkup()
{
    LocalSetOperator(new HOpMarkupRectangle(m_pHView));
}

void MyHQWidget::OnCircleMarkup()
{
    LocalSetOperator(new HOpMarkupCircle(m_pHView));
}

void MyHQWidget::OnTextMarkup()
{
    LocalSetOperator(new HOpMarkupPostIt(m_pHView));
}

void MyHQWidget::OnSaveMarkup1(bool save)
{
	static HC_KEY activelayerkey = -1;
	HMarkupManager *markup;	

	if (save)
	{
		if ((markup = m_pHView->GetMarkupManager()))
			activelayerkey = markup->GetCurrentLayerKey();

		// now redline information, just want to store the camera position.
		if (activelayerkey == -1)
			activelayerkey = markup->OpenLayer("");
	}
	else
	{
		if ((markup = m_pHView->GetMarkupManager()) && activelayerkey != -1)
		{
			char segpath[2048], activelayer[1024];
			HC_Show_Segment(activelayerkey, segpath);
			HC_Parse_String(segpath, "/", -1, activelayer);
			markup->OpenLayer(activelayer, true);
		}
	}
}

void MyHQWidget::OnSaveMarkup2(bool save)
{
	static HC_KEY activelayerkey = -1;
	HMarkupManager *markup;	

	if (save)
	{
		if ((markup = m_pHView->GetMarkupManager()))
			activelayerkey = markup->GetCurrentLayerKey();

		// now redline information, just want to store the camera position.
		if (activelayerkey == -1)
			activelayerkey = markup->OpenLayer("");
	}
	else
	{
		if ((markup = m_pHView->GetMarkupManager()) && activelayerkey != -1)
		{
			char segpath[2048], activelayer[1024];
			HC_Show_Segment(activelayerkey, segpath);
			HC_Parse_String(segpath, "/", -1, activelayer);
			markup->OpenLayer(activelayer, true);
		}
	}
}


void MyHQWidget::OnAnnotateModel() 
{
    LocalSetOperator(new HOpMarkupAnnotate(m_pHView));
}

void MyHQWidget::OnMeasureDistance() 
{
    LocalSetOperator(new HOpMarkupMeasure(m_pHView));
}

void MyHQWidget::OnSegmentBrowser()
{

    if (m_segBrowser->isVisible() ) {
		m_segBrowser->hide();
    }else{
		m_segBrowser->show();
		((HQSegmentBrowserFrame*)m_segBrowser)->populateTree();
    }
}

void MyHQWidget::OnUndo()
{
	m_pHView->GetUndoManager()->Undo();
	OnUpdateAll();
}

void MyHQWidget::OnUpdateUndo()
{
	if(m_pHView->GetUndoManager()->Undo(1,true) == 0)
	{
		m_hqapplication->undoAct->setEnabled(0);
	}
	else
	{
		m_hqapplication->undoAct->setEnabled(1);
	}
}

void MyHQWidget::OnRedo()
{
	m_pHView->GetUndoManager()->Redo();
	OnUpdateAll();
}

void MyHQWidget::OnUpdateRedo()
{
	if(m_pHView->GetUndoManager()->Redo(1,true) == 0)
	{
		m_hqapplication->redoAct->setEnabled(0);
	}
	else
	{
		m_hqapplication->redoAct->setEnabled(1);
	}
}

void MyHQWidget::OnHome()
{
	m_pHView->GetUndoManager()->Reset(m_pHView);
	OnUpdateAll();
}

void MyHQWidget::OnUpdateHome()
{
	if(m_pHView->GetUndoManager()->Undo(1,true) == 0)
	{
		m_hqapplication->homeAct->setEnabled(0);
	}
	else
	{
		m_hqapplication->homeAct->setEnabled(1);
	}
}

void MyHQWidget::OnUpdateAll()
{
	OnUpdateHome();
	OnUpdateUndo();
	OnUpdateRedo();
}

bool MyHQWidget::event(QEvent *ev)
{
	if( m_pHView )
	{
		OnUpdateAll();
	}
	HQWidget::event(ev);
	return true;
}

void MyHQWidget::LocalSetOperator(HBaseOperator * op){
	delete m_pHView->GetCurrentOperator();
	m_pHView->SetCurrentOperator(op);
}

// HQWindowColorPickerDlg
HQWindowColorPickerDlg::HQWindowColorPickerDlg(QWidget*p,  HBaseView * pBaseView):QDialog(p,0)
{
	mHBaseView = pBaseView;	

	// "Window Background Color" group box
	QGroupBox * top_box = new QGroupBox("Window Background Color");
		QGridLayout * margin_grid = new QGridLayout; 

	

		color1 = new QFrame(top_box);
		color1->setAutoFillBackground(true);
		color1->setFixedSize(64,32);
		color1->setFrameStyle(QFrame::Box|QFrame::Plain);
		QPushButton * top_color_button = new QPushButton("Top Color");
		top_color_button->setMinimumWidth(96);
		connect(top_color_button, SIGNAL(clicked()), this, SLOT(choose_window_top_color())); 
		

		color2 = new QFrame(top_box);
		color2->setAutoFillBackground(true);
		color2->setFixedSize(64,32);
		color2->setFrameStyle(QFrame::Box|QFrame::Plain);
		QPushButton * bottom_color_button = new QPushButton("Bottom Color");
		connect(bottom_color_button, SIGNAL(clicked()), this, SLOT(choose_window_bottom_color())); 
		bottom_color_button->setMinimumWidth(96);
		
		margin_grid->addWidget(color1, 0, 0);
		margin_grid->addWidget(top_color_button, 0, 1);
		margin_grid->addWidget(color2, 1, 0);
		margin_grid->addWidget(bottom_color_button, 1, 1);

	top_box->setLayout(margin_grid);

	// The two buttons at the bottom of the dialog
	QWidget* buttons = new QWidget;
		QHBoxLayout* button_layout = new QHBoxLayout;

		QPushButton* ok_button = new QPushButton("OK");
		connect(ok_button, SIGNAL(clicked()), this, SLOT(ok_clicked()));
		ok_button->setEnabled(true);

		QPushButton* cancel_button = new QPushButton("Cancel");
		connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel_clicked()));
		cancel_button->setEnabled(true);

		button_layout->addWidget(ok_button);
		button_layout->addWidget(cancel_button);
	buttons->setLayout(button_layout);

	QVBoxLayout* main_layout = new QVBoxLayout;
		main_layout->addWidget(top_box);
		main_layout->addWidget(buttons);
	setLayout(main_layout);
}

HQWindowColorPickerDlg::~HQWindowColorPickerDlg()
{

}

void HQWindowColorPickerDlg::showEvent(QShowEvent * e)
{
	HPoint window_top_color;
	HPoint window_bottom_color;
	mHBaseView->GetWindowColor( window_top_color, window_bottom_color );
	mWindowTopColor.setRgb( (int)(window_top_color.x * 255), (int)(window_top_color.y * 255), (int)(window_top_color.z * 255) );
	mWindowBottomColor.setRgb( (int)(window_bottom_color.x * 255),(int)(window_bottom_color.y * 255), (int)(window_bottom_color.z * 255) );

	QPalette pal1 = color1->palette();
	pal1.setColor(QPalette::Background, mWindowTopColor);
	color1->setPalette(pal1);

	QPalette pal2 = color2->palette();
	pal2.setColor(QPalette::Background, mWindowBottomColor);
	color2->setPalette(pal2);


}

void HQWindowColorPickerDlg::ok_clicked()
{
	HPoint window_top_color;
	HPoint window_bottom_color;

	window_top_color.x = mWindowTopColor.red()/255.0;
	window_top_color.y = mWindowTopColor.green()/255.0;
	window_top_color.z = mWindowTopColor.blue()/255.0;

	window_bottom_color.x = mWindowBottomColor.red()/255.0;
	window_bottom_color.y = mWindowBottomColor.green()/255.0;
	window_bottom_color.z = mWindowBottomColor.blue()/255.0;

	mHBaseView->SetWindowColor( window_top_color, window_bottom_color );
	mHBaseView->Update();

	hide();
}

void HQWindowColorPickerDlg::cancel_clicked()
{
	hide();
}


void HQWindowColorPickerDlg::choose_window_top_color()
{
	QColor c = QColorDialog::getColor(mWindowTopColor,this);
	if(c.isValid()) mWindowTopColor = c;
	QPalette p = color1->palette();
	p.setColor(QPalette::Background, mWindowTopColor);
	color1->setPalette(p);
}

void HQWindowColorPickerDlg::choose_window_bottom_color()
{
	QColor c = QColorDialog::getColor(mWindowBottomColor,this);
	if(c.isValid()) mWindowBottomColor = c;
	QPalette p = color2->palette();
	p.setColor(QPalette::Background, mWindowBottomColor);
	color2->setPalette(p);
}



// class HQToolButton
HQToolButton::HQToolButton( const QIcon & iconSet, const QString & textLabel, 
		const QString & grouptext, QObject * receiver, const char * slot, QToolBar * parent, 
		const char * name ):QToolButton( parent )
{
}

HQToolButton::~HQToolButton()
{
}

void HQToolButton::mouseReleaseEvent ( QMouseEvent * e )
{
	if( (e->button() & Qt::LeftButton) && (e->button() & Qt::SHIFT) )
		emit Released(true);
	else
		emit Released(false);

	QToolButton::mouseReleaseEvent(e);
}


