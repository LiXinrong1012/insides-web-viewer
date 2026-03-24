// SimpleHQWidget.cpp - Implementation of the HOOPS/Qt class SimpleHQWidget
// 
// More about this class 
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
#undef null

// the qt/hoops base class
#include "SimpleHQWidget.h"


// hoops include
#include "hc.h"

// this is setup in main
extern HDB * m_pHDB;


#define Debug_USE_QGL_CONTEXT           0x00000080

SimpleHQWidget::SimpleHQWidget(QWidget* parent, QString const & name , QString const & filename) 
    : HQWidget( parent, name ) 
{ 


	// Create and initialize HOOPS/MVO Model and View objects 
	m_pHBaseModel = new HBaseModel(); 
	m_pHBaseModel->Init(); 

	// Initialize View object to null ; gets created in SimpleHQWidget::Init 
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
} 
  

SimpleHQWidget::~SimpleHQWidget() 
{ 
 // Destructor  

	// Clean up memory 
	if(m_pHView)        delete m_pHView; 
	if(m_pHBaseModel)   delete m_pHBaseModel; 

} 
  

void SimpleHQWidget::SetupView() 
{ 

	// set initial HOOPS/3DGS segment tree attributes for the  
	// HOOPS/MVO View Object 

	m_pHView->FitWorld();  // fit the camera to the scene extents 
	m_pHView->RenderGouraud();  // set the render mode to gouraud 

	// configure view segment  
	HC_Open_Segment_By_Key(m_pHView->GetViewKey()); 
	HC_Set_Color_By_Index("windows", 0); 
	HC_Set_Selectability("everything = off"); 
	HC_Close_Segment(); 

	// Configure scene/model segment 
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey()); 
	HC_Set_Color_By_Index("faces", 2); 
	HC_Set_Color_By_Index("text, lights", 1); 
	HC_Set_Color_By_Index("edges, lines", 1); 
	HC_Set_Color_By_Index("markers", 1); 
	HC_Set_Rendering_Options 
		("no color interpolation, no color index interpolation"); 
	HC_Set_Visibility  
		("lights = (faces = on, edges = off, markers = off), markers = off, faces=on, edges=off, lines=on, text = on"); 

	HC_Set_Selectability("everything = off, faces = on"); 
	HC_Set_Text_Font("transforms = off"); 
	HC_Close_Segment(); 

	// configure segment for temporary construction geometry 
	HC_Open_Segment_By_Key (m_pHView->GetConstructionKey()); 
	HC_Set_Heuristics("quick moves"); 
	HC_Set_Visibility("faces = off, edges = on, lines = on"); 
	HC_Close_Segment(); 


	// configure windowspace segment for quickmoves 
	HC_Open_Segment_By_Key(m_pHView->GetWindowspaceKey()); 
	HC_Set_Color_By_Index ("geometry", 3); 
	HC_Set_Color_By_Index ("window contrast", 1); 
	HC_Set_Color_By_Index ("windows", 1); 

	HC_Set_Visibility("markers=on"); 
	HC_Set_Color("markers = green, lines = green"); 
	HC_Set_Marker_Symbol("+"); 
	HC_Set_Selectability("off"); 
	HC_Close_Segment();  

} 
  

void SimpleHQWidget::Init() 
{ 
	// setup our HOOPS/MVO Base View, Selection object and current operator 
	// This must be called after SimpleHQWidget's constructor has executed 

	// create and initialize MVO HBaseView object 
#if defined(IS_OSX) && defined(USE_MDI)
	m_pHView = new HBaseView(m_pHBaseModel, NULL, NULL, NULL, GetWindowId(), GetColorMap(), GetClipOverride(), GetQGLContext()); 
#else
	m_pHView = new HBaseView(m_pHBaseModel, NULL, NULL, NULL, GetWindowId(), GetColorMap(), GetClipOverride()); 
#endif
	m_pHView->Init(); 


	// Set up the HOOPS/MVO View's HOOPS/3DGS Attributes 
	SetupView(); 

	// Set View's current Operator 
	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView)); 

	//DEBUG_STARTUP_CLEAR_BLACK = 0x00004000 clear ogl to black on init update
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options("debug = 0x00004000");

#if defined(IS_OSX) && defined(USE_MDI)
		char debug_opts[256];
		sprintf(debug_opts, "set debug = %d", Debug_USE_QGL_CONTEXT);
		HC_Set_Driver_Options(debug_opts);
#endif
	HC_Close_Segment();

	// Call the Views Update Method - initiates HOOPS/3DGS Update_Display  
	m_pHView->Update(); 

} 

void SimpleHQWidget::OnClose(){
	this->~SimpleHQWidget();
}

// load a file into our view
void SimpleHQWidget::load(QString const & in_filename)
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
void SimpleHQWidget::OnPrint()
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

void SimpleHQWidget::OnSaveFileAs()
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
void SimpleHQWidget::OnLoad()
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
  

void SimpleHQWidget::OnOrbit()  
{ 
	// Set MVO View Object current Operator to HOpCameraOrbit  

	if (m_pHView->GetCurrentOperator()) 
	delete m_pHView->GetCurrentOperator(); 

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));  

} 
  

// real time zoomer
void SimpleHQWidget::OnZoom() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoom(m_pHView));
}

// window zoomer
void SimpleHQWidget::OnZoomToWindow() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoomBox(m_pHView));
}

// resets the camera to view the world space extents of the model
void SimpleHQWidget::OnZoomToExtents() 
{
    m_pHView->ZoomToExtents();
}
  
// panner
void SimpleHQWidget::OnPan() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();
    m_pHView->SetCurrentOperator(new HOpCameraPan(m_pHView));		

}


// create sphere
void SimpleHQWidget::OnCreateSphere() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateSphere(m_pHView));		


}

// create cone
void SimpleHQWidget::OnCreateCone() 
{
    if (m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateCone(m_pHView));		


}



// create cylinder
void SimpleHQWidget::OnCreateCylinder() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();


    m_pHView->SetCurrentOperator(new HOpCreateCylinder(m_pHView));		

}
  
 
void SimpleHQWidget::OnRunMyCode() 
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
  


