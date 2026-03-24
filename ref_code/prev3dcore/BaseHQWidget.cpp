// BaseHQWidget.cpp - Implementation of the HOOPS/Qt class BaseHQWidget
// 
// More about this class 
#include "BaseHQWidget.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// qt includes
#include <QPrinter>
#include <QFileDialog>
#include <QLabel> 
#include <QMessageBox>
#include <QMenu> 
#include <QCursor> 
#include <QSlider>
#include <QLayout>
#include <QLineEdit>
#include <QTimer>
#include <QColorDialog>
#include <QColor>
#include <QInputDialog>
#include <QKeyEvent>

// hoops_mvo includes
#include "HDB.h"

#include "HBaseModel.h"
#include "HBaseView.h"

#include "HModelInfo.h"
#include "HEventInfo.h"
#include "HOpCameraOrbit.h"
#include "HOpCameraZoom.h"
#include "HOpCameraZoomBox.h"
#include "HOpCameraPan.h"
#include "HOpCreateSphere.h"
#include "HOpCreateCone.h"
#include "HOpCreateCylinder.h"
#include "HUtility.h"
#include "HStream.h"
#include "HStreamFileToolkit.h"
#include "HIOManager.h"
#include "HSharedKey.h"
#undef null

// the qt/hoops base class


// hoops include
#include "hc.h"


#include "base/ParametersManager.h"
#include "base/AppConfiguration.h"
#include "base/Console.h"

// this is setup in main
extern HDB * m_pHDB;

#define Debug_USE_QGL_CONTEXT           0x00000080

BaseHQWidget::BaseHQWidget(QWidget* parent, QString const & name , QString const & filename) 
    : HQWidget( parent, name ) 
	,_acOpOrbit(NULL)
	,_acOpPan(NULL)
{ 
	initParameters();

	// Create and initialize HOOPS/MVO Model and View objects 
	m_pHBaseModel = new HBaseModel(); 
	m_pHBaseModel->Init(); 

	// Initialize View object to null ; gets created in BaseHQWidget::Init 
	m_pHView = 0; 


	// if called with a file name we load it  
	// otherwise open an empty view 
	if(!filename.isEmpty()){ 
		H_UTF8 hutf8;
		hutf8.encodedText<char>(filename.toUtf8().data());
		H_WCS hwcs(hutf8);
		std::wstring stdwcs(hwcs.encodedText());

		m_pHBaseModel->Read(stdwcs.c_str()); 
	}

	// enable MouseMoveEvents  
	setMouseTracking(true); 

	// enable key events 
	setEnabled(true); 
	setFocusPolicy(Qt::StrongFocus); 


	// action group
	QAction* ac=new QAction("Orbit (&R)",this);
	ac->setIcon(QIcon(":/resources/menu/a009x16x16.png"));
	connect(ac,SIGNAL(triggered()),this,SLOT(OnOrbit()));
	ac->setChecked(true);
	ac->setCheckable(true);
	_acOpOrbit=ac;

	ac=new QAction("Pan (&T)",this);
	ac->setIcon(QIcon(":/resources/menu/a010x16x16.png"));
	connect(ac,SIGNAL(triggered()),this,SLOT(OnPan()));
	ac->setCheckable(true);
	ac->setChecked(false);
	_acOpPan=ac;
} 
  

BaseHQWidget::~BaseHQWidget() 
{ 
 // Destructor  

	// Clean up memory 
	if(m_pHView)        delete m_pHView; 
	if(m_pHBaseModel)   delete m_pHBaseModel; 

} 
  
static void _setDefaultMaterial()
{
	//HC_Set_Color("faces = (ambient = (r=0.117647 g=0.117647 b=0.117647))");
	HC_Set_Color("ambient = (r=0.117647 g=0.117647 b=0.117647)");
	//HC_Set_Color("faces = (specular = (r=0.75294 g=0.75294 b=0.75294))");
	HC_Set_Color("specular = (r=0.75294 g=0.75294 b=0.75294)");
	//HC_Set_Color("faces = (emission  = (r=0 g=0 b=0))");
	HC_Set_Color("emission  = (r=0 g=0 b=0)");

	HC_Set_Color("gloss=64");
	//_shininess = 64.0 ;
}

void BaseHQWidget::SetupView() 
{ 
	m_pHView->FitWorld();		// fit the camera to the scene extents

	m_pHView->CameraPositionChanged(true);
	//m_pHView->RenderGouraud();  // set the render mode to gouraud
	m_pHView->RenderFlat();			//Jerry, 2014.3.14
	m_pHView->SetHandedness(HandednessRight);
	m_pHView->SetForceFastHiddenLine(true);
	

	// set the gradient window background
	HPoint window_top_color(0.0000f, 0.501961f, 0.501961f);
	HPoint window_bottom_color(1.000f, 0.984314f, 0.941176f);
	const Base::ParameterItem* paraItem=Base::AppConfiguration::instance()->getParametersManager()->get("Window top color","Display");
	if(paraItem){
		QColor color1=paraItem->getVariant().value<QColor>();
		window_top_color.Set(color1.red()/255.0,color1.green()/255.0,color1.blue()/255.0);
	}
	paraItem=Base::AppConfiguration::instance()->getParametersManager()->get("Window bottom color","Display");
	if(paraItem){
		QColor color2=paraItem->getVariant().value<QColor>();
		window_bottom_color.Set(color2.red()/255.0,color2.green()/255.0,color2.blue()/255.0);
	}

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

	HC_Set_Rendering_Options("no color interpolation, color index interpolation");
	// by Jerry, 2014.5.26
	HC_Set_Rendering_Options("no lighting interpolation");

	// by Jerry, 2015.2.4
	HC_Define_System_Options("warnings=off, errors=off");


	HC_Set_Visibility ("lights = (faces = on, edges = off, markers = off), markers = off, faces=on, edges=off, lines=off, text = on");
		
	HC_Set_Visibility ("edges = on");
	HC_Set_Visibility ("line = on");
	HC_Set_Visibility ("vertex = on");
	HC_Set_Visibility ("shadow = off");

	HC_Set_Selectability("everything = off, geometry = on");
	HC_Close_Segment();

	// new segment for temporary construction geometry
	HC_Open_Segment_By_Key (m_pHView->GetConstructionKey());
	HC_Set_Heuristics("quick moves");
	HC_Set_Visibility("faces = on, edges = on, lines = on");
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
	_setDefaultMaterial();
	HC_Close_Segment();

	OnOrbit();
} 

  

void BaseHQWidget::Init() 
{ 
#ifdef PARASOLID
	m_pHView = new HSolidView(m_pHBaseModel, NULL, NULL, NULL, GetWindowId(), GetColorMap(), GetClipOverride());
#else
	m_pHView = new HBaseView(m_pHBaseModel, NULL, NULL, NULL, GetWindowId(), GetColorMap(), GetClipOverride());
#endif
	m_pHView->Init();

	// Set up the HOOPS/MVO View's HOOPS/3DGS Attributes 
	SetupView(); 


	//char driver_opts[512];
	//sprintf(driver_opts, "anti-alias=%d ", m_aa);
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
	//HC_Set_Driver_Options(driver_opts);
	HC_Set_Driver_Options("quick moves preference = default");
	HC_Set_Driver_Options("no display stats, no display time stats");
	//if(m_aa == 0) 
	//	HC_Set_Rendering_Options("anti-alias = no screen");
	//else
	//	HC_Set_Rendering_Options("anti-alias = (screen = on)");
	HC_Close_Segment();

	m_pHView->SetSmoothTransition(true);
	m_pHView->SetKeyStateCallback(HQWidget::GetKeyState);

	m_pHView->StartSharedKey();
	m_pHView->GetSharedKey()->Reset();
	m_pHView->GetSharedKey()->SetupStreamToolkit(m_pHView->GetModel()->GetStreamFileTK());

	m_pHView->SetHideOverlappedText(true);



	//((HOpCameraManipulate *)m_pHView->GetOperator())->GetOrbitOperator()->SetSceneBoundingBoxVis(m_bounding_on);

	m_pHView->SetSmoothTransition(true);


#ifndef OSX_SYSTEM
	//DEBUG_STARTUP_CLEAR_BLACK = 0x00004000 clear ogl to black on init update
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
	HC_Set_Driver_Options("debug = 0x00004000");
	HC_Close_Segment();
#endif
	//if (m_segBrowser) {
	//	((HQSegmentBrowserFrame*)m_segBrowser)->setHoopsView(GetHoopsView());
	//	((HQSegmentBrowserFrame*)m_segBrowser)->setSegmentRoot(GetHoopsModel()->GetModelKey());
	//}

	m_pHView->SetHandedness(HandednessRight);
	m_pHView->SetPolygonHandednessMode(HandednessLeft);
	m_pHView->SetCPGeomVisibility(true,true);
	m_pHView->SetColorInterpolation(true);
	m_pHView->SetColorIndexInterpolation(true, false);
	m_pHView->SetBackplaneCulling(false);
	m_pHView->SetHideOverlappedText(false);
	m_pHView->Update();
	m_pHView->SetAxisMode(AxisOn);

	if(_defaultCamera.projection[0]!='\0')
		m_pHView->SetCamera(_defaultCamera);
	else{
		HCamera camera;
		m_pHView->GetCamera(&camera);
		strcpy(camera.projection,"orthographic");
		m_pHView->SetCamera(camera);
	}

	AdjustAxisWindow();

	initContextMenu();
	m_pHView->SetViewMode(HViewXY);
} 

void BaseHQWidget::OnClose(){
	this->~BaseHQWidget();
}

// load a file into our view
void BaseHQWidget::load(QString const & in_filename)
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
		
 	    HC_Open_Segment_By_Key(m_pHView->GetModel()->GetModelKey());

		while (!feof(fp))
		{
		    length = fread(buffer,1,HSF_BUFFER_CHUNK,fp);
		    m_pHView->InsertHSFData("file", buffer, length, true);
		}

	    HC_Close_Segment();
	    
	    result = InputOK;
	    m_pHView->GetModel()->GetStreamFileTK()->Restart();

	}
	else 
	{
		result = m_pHBaseModel->Read(stdwcs.c_str(), m_pHView);
	}

	if(result == InputVersionMismatch)
		QMessageBox::information( this, "Simple\n",
		"This file was created with a newer version of the HOOPS/Stream Toolkit.\n"
		"To view it, this application will need to be updated.\n");
	else if(result == InputBadFileName)
		QMessageBox::information( this, "Simple\n",
		"A problem occured with the file name provided.\n"
		"perhaps you don't have read permision or it is missing.\n");
	else if(result == InputNotHandled)
		QMessageBox::information( this, "Simple\n",
		"This program doesn't have a handler for this file operation.\n");
	else if(result != InputOK)
		QMessageBox::information( this, "Simple\n",
		"A problem occured during this file operation.\n");
		
	SetupView();

	if (m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));


	m_pHView->Update();
}
  
// print
void BaseHQWidget::OnPrint()
{ 
	char driver_opts[MVO_BUFFER_SIZE];
	HOutputHandlerOptions* options = new HOutputHandlerOptions();

	options->m_pHBaseView = m_pHView;

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

	delete options;
}

static void GetExtension(wchar_t const * filter, wchar_t * extension)
{
	const wchar_t *start = wcsstr(filter, L"(*.")+3;
	wcscpy(extension, start);
	*(wcsstr(extension, L")")) = L'\0';
}

void BaseHQWidget::OnSaveFileAs()
{ 
	QFileDialog* qfd = new QFileDialog(this, "qfd");

    // setup selection filter
    QStringList demFilters;
    demFilters.append("HOOPS Metafiles (*.hmf)");
    demFilters.append("HOOPS Binary Stream (*.hsf)");
    demFilters.append("Tagged Image Format (*.tif)");
    demFilters.append("Postscript (*.ps)");
    demFilters.append("HPGL2 (*.hp)");
    demFilters.append("CGM (*.cgm)");
    demFilters.append("HOOPS 3D Stream Control (*.html)");
    qfd->setFilters(demFilters);

    // first get new filename
    qfd->setFileMode(QFileDialog::AnyFile);
	qfd->setAcceptMode(QFileDialog::AcceptSave);

    if (qfd->exec() == QDialog::Accepted){

		QString fn = (qfd->selectedFiles()).front();
		QString fn2 = qfd->selectedFilter();

		if (!fn.isEmpty()){
		
			int width = 0;
			int height = 0;
			wchar_t ext[100] = {L""}; 
			H_UTF8 hutf8;
			hutf8.encodedText<char>(fn.toUtf8().data());
			H_WCS hwcs(hutf8);
			std::wstring stdwcs(hwcs.encodedText());

			if (wcsrchr(stdwcs.c_str(), L'.')){
				HUtility::FindFileNameExtension(stdwcs.c_str(), ext);
			}
			else{
				H_UTF8 hutf8;
				hutf8.encodedText<char>(fn2.toUtf8().data());
				H_WCS hwcs(hutf8);
				std::wstring tmp(hwcs.encodedText());
				GetExtension(tmp.c_str(), ext);
				stdwcs = stdwcs + L"." + ext;
			}

			//TODO add this to a dialog
			if (wcseq(ext, L"tif")){
				width=640;
				height=480;
			}

			HFileOutputResult result = m_pHBaseModel->Write(stdwcs.c_str(), m_pHView, width, height);

			if(result == OutputBadFileName)
				QMessageBox::information( this, "Simple\n",
				"A problem occured with the file name provided.\n"
				"perhaps you don't have read permision or it is missing.\n");
			else if(result == OutputNotHandled)
				QMessageBox::information( this, "Simple\n",
				"This program doesn't have a handler for this file operation.\n");
			else if(result != OutputOK)
				QMessageBox::information( this, "Simple\n",
				"A problem occured during this file operation.\n");
		}
	}

	delete qfd;
}


// open a load file dialog
void BaseHQWidget::OnLoad()
{

/*
	QString fn = QFileDialog::getOpenFileName(0,"HOOPS Metafiles (*.hmf);;HOOPS Binary Stream Files (*.hsf)",this);
	if (!fn.isEmpty())
		load(fn);
*/
	QFileDialog* qfd = new QFileDialog(this, "qfd");

    // setup selection filter
    QStringList demFilters;
    demFilters.append("HOOPS Binary Stream Files (*.hsf)");
    demFilters.append("HOOPS Metafiles (*.hmf)");
    demFilters.append("VRML (*.wrl)");
    demFilters.append("Gif (*.gif)");
    demFilters.append("Stereolithography files (*.stl)");
    demFilters.append("Alias Wavefront (*.obj)");


    qfd->setFilters(demFilters);

    // first get new filename
    qfd->setFileMode(QFileDialog::ExistingFile);

    if (qfd->exec() == QDialog::Accepted){

		QString fname = (qfd->selectedFiles()).front();
		if (!fname.isEmpty()){
			this->load(fname);
		}
	}

	delete qfd;
}
  

void BaseHQWidget::OnOrbit()  
{ 
	// Set MVO View Object current Operator to HOpCameraOrbit  

	if (m_pHView->GetCurrentOperator()) 
	delete m_pHView->GetCurrentOperator(); 

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));  

	_acOpOrbit->setChecked(true);
	_acOpPan->setChecked(false);
} 
  

// real time zoomer
void BaseHQWidget::OnZoom() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoom(m_pHView));
}

// window zoomer
void BaseHQWidget::OnZoomToWindow() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoomBox(m_pHView));
}

// resets the camera to view the world space extents of the model
void BaseHQWidget::OnZoomToExtents() 
{
	if(m_pHView)
		m_pHView->ZoomToExtents();
}
  
// panner
void BaseHQWidget::OnPan() 
{
    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();
    m_pHView->SetCurrentOperator(new HOpCameraPan(m_pHView));		

	_acOpOrbit->setChecked(false);
	_acOpPan->setChecked(true);
}


// create sphere
void BaseHQWidget::OnCreateSphere() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateSphere(m_pHView));		


}

// create cone
void BaseHQWidget::OnCreateCone() 
{
    if (m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateCone(m_pHView));		


}



// create cylinder
void BaseHQWidget::OnCreateCylinder() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();


    m_pHView->SetCurrentOperator(new HOpCreateCylinder(m_pHView));		

}
  
 
void BaseHQWidget::OnRunMyCode() 
{
	// this is a function in which developers can
	// write their own simple HOOPS functions
	//QMessageBox::information( this, "Simple", "I love HOOPS!!!!");		

	HC_Open_Segment_By_Key(m_pHBaseModel->GetModelKey());

	//case 1.
	/*
	HC_Insert_Text(0.0f, 0.0f, 0.0f, "Hello World");
	HC_KEY rays_key = HC_KOpen_Segment("infinite_rays");
	HC_Insert_Infinite_Ray(0.0, 0.0, 0.0,  1.0, 0.0, 0.0);
	HC_Insert_Infinite_Ray(0.0, 1.0, 0.0,  1.0, 1.0, 0.0);
	HC_Insert_Infinite_Ray(0.0, 2.0, 0.0,  1.0, 2.0, 0.0);
	HC_Insert_Infinite_Ray(0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
	HC_Insert_Infinite_Ray(0.0, 0.0, 0.0,  0.0, 0.0, 1.0);
	HC_Close_Segment();
	*/

	//case 2.
	/*
	HC_Insert_Text(0.0f, 0.0f, 0.0f, "Hello World");
	*/

	// define the model

	HC_Open_Segment("?Include Library");

	HC_Open_Segment("Model_0");
	HC_Insert_Text(0.0f, 0.0f, 0.0f, "Hello World");
	HC_Close_Segment();
	HC_Close_Segment();

	HC_Include_Segment("?Include Library/Model_0");



	HC_Close_Segment();
	m_pHView->Update();
	
}

void BaseHQWidget::initParameters()
{
	// init some stuff 
	m_edges = false;
	m_faces = true;
	m_lines	= true;
	m_markers = false;
	m_lights = true;
	m_text = true;
	m_color_index_int = true;
	m_color_int = true;
	m_axis_on = true;
	m_bounding_on = false;
	m_light_follows = true;
	m_shadows_on = false;
	m_has_initial_view = false;
	fullscreen_on = false;
}

void BaseHQWidget::initContextMenu()
{
	_mainContextMenu=new QMenu(this);
	_mainContextMenu->clear();
	//s->setTitle("Selection Level");
	//m_->addMenu(s);
	
	initMenuVisibility();
	_mainContextMenu->addMenu(_menuVisibility);
	initMenuRenderMode();
	_mainContextMenu->addMenu(_menuRenderMode);
	initMenuViewType();
	_mainContextMenu->addMenu(_menuViewType);

	//t->setTitle("Text");
	//m->addMenu(t);
	//q->setTitle("Quickmoves Preference");
	//m->addMenu(q);
	//st->setTitle("Display Statistics");
	//m->addMenu(st);
}

void BaseHQWidget::initMenuVisibility()
{
	_menuVisibility=new QMenu(_mainContextMenu);
	_menuVisibility->setTitle("Visibility");


	QMenu *v=_menuVisibility;
	QAction *action;
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
}

void BaseHQWidget::OnRightButtonDown( QMouseEvent * e /*= 0*/ )
{
	_mainContextMenu->exec(QCursor::pos());
}

void BaseHQWidget::initMenuRenderMode()
{
	_menuRenderMode = new QMenu();
	_menuRenderMode->setTitle("Render mode");
	HRenderMode rm = m_pHView->GetRenderMode();

	QAction *action;
	QMenu* r=_menuRenderMode;

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
}
void BaseHQWidget::initMenuViewType()
{
	_menuViewType = new QMenu();
	_menuViewType->setTitle("view type");

	QAction *action;
	QMenu* r=_menuViewType;

	action = r->addAction("XY", this, SLOT(OnFrontView()));
	action = r->addAction("-XY", this, SLOT(OnBackView()));
	action = r->addAction("XZ", this, SLOT(OnTopView()));
	action = r->addAction("-XZ", this, SLOT(OnBottomView()));
	action = r->addAction("ZY", this, SLOT(OnRightView()));
	action = r->addAction("-ZY", this, SLOT(OnLeftView()));
	action = r->addAction("ISO", this, SLOT(OnIsometricView()));

	action = r->addAction("rotate +90", this, SLOT(OnRotate90View()));
	action = r->addAction("rotate ...", this, SLOT(OnRotateXView()));
}





// sets wireframe render mode
void BaseHQWidget::OnWireframe() 
{
	m_pHView->RenderWireframe();

	m_faces = false;
	m_edges = true;
	m_lines = true;
	m_lights = false;

	m_pHView->Update();
}


// sets flat-shaded render mode
void BaseHQWidget::OnFlatShaded() 
{
	m_pHView->RenderFlat();	

	m_faces = true;
	m_edges = false;
	m_lines = false;

	m_pHView->Update();
}


// sets gouraud-shaded render mode
void BaseHQWidget::OnGouraudShaded() 
{
	m_pHView->RenderGouraud();	

	m_faces = true;
	m_edges = false;
	m_lines = false;

	m_pHView->Update();
}

// sets phong-shaded render mode
void BaseHQWidget::OnPhongShaded() 
{
	m_pHView->RenderPhong();

	m_faces = true;
	m_edges = false;
	m_lines = false;

	m_pHView->Update();
}


// sets hidden-line render mode
void BaseHQWidget::OnHiddenLine() 
{
	m_pHView->SetRenderMode(HRenderHiddenLine, true);

	m_faces = true;
	m_edges = true;
	m_lines = true;
	m_lights = false;

	m_pHView->Update();
}

// sets fast hidden-line render mode
void BaseHQWidget::OnHiddenLineFast() 
{
	m_pHView->RenderHiddenLineFast();

	m_faces = true;
	m_edges = true;
	m_lines = true;
	m_lights = false;

	m_pHView->Update();
}

// sets silhouette mode
void BaseHQWidget::OnSilhouette() 
{
	m_pHView->RenderSilhouette();

	m_faces = false;
	m_edges = true;
	m_lines = true;
	m_lights = false;

	m_pHView->Update();
}

// sets wireframe-with-silhouette mode
void BaseHQWidget::OnWireframeWithSilhouette() 
{
	m_pHView->RenderWireframeWithSilhouette();

	m_faces = false;
	m_edges = true;
	m_lines = true;
	m_lights = false;

	m_pHView->Update();
}

// sets shaded wireframe render mode
void BaseHQWidget::OnShadedWireframe() 
{
	m_pHView->RenderShadedWireframe();

	m_faces = false;
	m_edges = true;
	m_lines = true;
	m_lights = true;

	m_pHView->Update();
}

// sets vertices render mode
void BaseHQWidget::OnVertices() 
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
void BaseHQWidget::OnShadedVertices() 
{
	m_pHView->RenderShadedVertices();

	m_faces = false;
	m_edges = false;
	m_lines = false;
	m_lights = true;
	m_markers = true;

	m_pHView->Update();
}


void BaseHQWidget::OnFrontView()
{
	m_pHView->SetViewMode(HViewXY);
}

void BaseHQWidget::OnBackView()
{
	m_pHView->SetViewMode(HViewYX);
}

void BaseHQWidget::OnTopView()
{
    m_pHView->SetViewMode(HViewXZ);
}

void BaseHQWidget::OnBottomView()
{
   m_pHView->SetViewMode(HViewZX);
}

void BaseHQWidget::OnLeftView()
{
   m_pHView->SetViewMode(HViewYZ);
}

void BaseHQWidget::OnRightView()
{
    m_pHView->SetViewMode(HViewZY);
}

void BaseHQWidget::OnIsometricView()
{
   m_pHView->SetViewMode(HViewIso);
}


void BaseHQWidget::RotateView( double angle )
{
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
	HC_Roll_Camera(angle);
	HC_Close_Segment();
	m_pHView->Update();
}

void BaseHQWidget::OnRotate90View()
{
	RotateView(90);
}
void BaseHQWidget::onRotateMinus90View()
{
	RotateView(-90);
}

void BaseHQWidget::OnRotateXView()
{
	bool ok;
	double ang = QInputDialog::getDouble(this, 
		"get rotation angle", "rotation angle (in degree):", 
		0, -999999, 999999,2, &ok);
	if (ok){
		RotateView(ang);
	}
}

void BaseHQWidget::LocalSetOperator( HBaseOperator * op )
{
	delete m_pHView->GetCurrentOperator();
	m_pHView->SetCurrentOperator(op);
}

void BaseHQWidget::initMenuBaseOperator()
{

}

void BaseHQWidget::keyPressEvent( QKeyEvent * event )
{
		switch(event->key())
		{
		case Qt::Key_R:
			this->OnOrbit();
			break;
		case Qt::Key_T:
			this->OnPan();
			break;
		case Qt::Key_A:
			this->OnZoomToExtents();
			break;
		}

	HQWidget::keyPressEvent(event);
}

void BaseHQWidget::saveCameraState( QDataStream* out )
{
	HCamera camera;
	GetHoopsView()->GetCamera(&camera);
	out->writeRawData((char*)&camera,sizeof(HCamera));
}

void BaseHQWidget::loadCameraState( QDataStream* in )
{
	in->readRawData((char*)&_defaultCamera,sizeof(HCamera));
	if(GetHoopsView())
		GetHoopsView()->SetCamera(_defaultCamera);
}




















