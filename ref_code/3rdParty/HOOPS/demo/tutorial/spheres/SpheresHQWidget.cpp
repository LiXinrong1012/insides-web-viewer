// SpheresHQWidget.cpp - Implementation of the HOOPS/Qt class SpheresHQWidget
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
#include "HSpheresView.h"

#include "HModelInfo.h"
#include "HEventInfo.h"
#include "HOpCameraOrbit.h"
#include "HOpCameraZoom.h"
#include "HOpCameraZoomBox.h"
#include "HOpCameraPan.h"
#include "HOpCreateSphere.h"
#include "HOpCreateCone.h"
#include "HOpCreateCylinder.h"
#include "HOpSelectArea.h"
#include "HOpObjectRotate.h"
#include "HOpMarkupAnnotate.h"
#include "HUtility.h"
#include "HStream.h"
#include "HStreamFileToolkit.h"
#include "HIOManager.h"
#undef null

// the qt/hoops base class
#include "SpheresHQWidget.h"


// hoops include
#include "hc.h"

#include "HMyCreateSphere.h"
#include "HSpheresModel.h"
#include "HSpheresView.h"

// this is setup in main
extern HDB * m_pHDB;

HIOUtilitySpheres * SpheresHQWidget::m_pIOUtilitySpheres = 0;

SpheresHQWidget::SpheresHQWidget(QWidget* parent, const char* name , const char * filename) 
    : HQWidget( parent, name ) 
{ 


	// Create and initialize HOOPS/MVO Model and View objects 
	m_pHBaseModel = new HSpheresModel(); 
	m_pHBaseModel->Init(); 

	// Initialize View object to null ; gets created in SpheresHQWidget::Init 
	m_pHView = 0; 

	if ( !m_pIOUtilitySpheres )
	{
		m_pIOUtilitySpheres = new HIOUtilitySpheres();
		HIORegisterInputType("sph",   m_pIOUtilitySpheres);
		HIORegisterOutputType("sph",  m_pIOUtilitySpheres);
	}
	// if called with a file name we load it  
	// otherwise open an empty view 
	if(filename) 
	m_pHBaseModel->Read(filename); 

	// enable MouseMoveEvents  
	setMouseTracking(true); 

	// enable key events 
	setEnabled(true); 
	setFocusPolicy(Qt::StrongFocus);  
} 
  

SpheresHQWidget::~SpheresHQWidget() 
{ 
 // Destructor  

	// Clean up memory 
	if(m_pHView)        delete m_pHView; 
	if(m_pHBaseModel)   delete m_pHBaseModel; 

//	H_SAFE_DELETE(m_pIOUtilitySpheres);
	if(m_pIOUtilitySpheres)
	{
		delete m_pIOUtilitySpheres;
		m_pIOUtilitySpheres = 0;
	}

} 
  
void SpheresHQWidget::SetupView() 
{ 

	// set initial HOOPS/3DGS segment tree attributes for the  
	// HOOPS/MVO View Object 

	m_pHView->FitWorld();  // fit the camera to the scene extents 
	m_pHView->RenderShaded();  // set the render mode to shaded 

	// configure view segment  
	HC_Open_Segment_By_Key(m_pHView->GetViewKey()); 
		HC_Set_Color_By_Index("windows", 1); 
		HC_Set_Selectability("everything = off"); 
	HC_Close_Segment(); 

	m_pHView->SetShadowMode( HShadowSoft );	

	// Configure scene/model segment 
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey()); 
	HC_Set_Color_By_Index("faces", 2); 
	HC_Set_Color_By_Index("lights", 1); 
	HC_Set_Color_By_Index("text", 0);
	HC_Set_Color_By_Index("edges, lines", 3); 
	HC_Set_Color_By_Index("markers", 4); 
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

void SpheresHQWidget::Init() 
{ 
	// setup our HOOPS/MVO Base View, Selection object and current operator 
	// This must be called after SpheresHQWidget's constructor has executed 

	// create and initialize MVO HBaseView object 
	m_pHView = new HSpheresView(m_pHBaseModel, NULL, NULL, NULL,  
		GetWindowId(), GetColorMap(), GetClipOverride()); 

	m_pHView->Init(); 
	
	// Set up the HOOPS/MVO View's HOOPS/3DGS Attributes
	SetupView() ;

	// Set View's current Operator 
	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView)); 
	
	//DEBUG_STARTUP_CLEAR_BLACK = 0x00004000 clear ogl to black on init update
	HC_Open_Segment_By_Key(m_pHView->GetViewKey());
		HC_Set_Driver_Options("debug = 0x00004000");
	HC_Close_Segment();

	// Call the View's Update Method - initiates HOOPS/3DGS Update_Display  
	m_pHView->Update(); 
} 
  

// load a file into our view
void SpheresHQWidget::load(const char * filename)
{
	m_pHView->Flush(true);

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Flush_Contents (".", "geometry");
	HC_Close_Segment();

	char * extension = (char*)malloc(strlen(filename)+1);

	HUtility::FindFileNameExtension(filename, extension);

	HFileInputResult result;

	if (strstr("hsf", extension)) {

	    m_pHView->GetModel()->GetStreamFileTK()->Restart();

#define HSF_BUFFER_CHUNK 8192
	    char buffer[HSF_BUFFER_CHUNK];
	    int length;
	    FILE *fp;

	    fp = fopen(filename, "rb");
		
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
		result = m_pHBaseModel->Read(filename, m_pHView);
	}

	free(extension);

	if(result == InputVersionMismatch)
		QMessageBox::information( this, "Spheres\n",
		"This file was created with a newer version of the HOOPS/Stream Toolkit.\n"
		"To view it, this application will need to be updated.\n");
	else if(result == InputBadFileName)
		QMessageBox::information( this, "Spheres\n",
		"A problem occured with the file name provided.\n"
		"perhaps you don't have read permision or it is missing.\n");
	else if(result == InputNotHandled)
		QMessageBox::information( this, "Spheres\n",
		"This program doesn't have a handler for this file operation.\n");
	else if(result != InputOK)
		QMessageBox::information( this, "Spheres\n",
		"A problem occured during this file operation.\n");

	SetupView() ;

	if (m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));


	m_pHView->Update();
}
  
// print
void SpheresHQWidget::OnPrint()
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

static void ProcessFilters(QString * filters, const char * file_types) 
{

	if(strstr(file_types, "ps"))
		*filters += QString(";; Postscript (*.ps)");

	if(strstr(file_types, "pdf"))
		*filters += QString(";; PDF (*.pdf)");

	if(strstr(file_types, "hp"))
		*filters += QString(";; HPGL2 (*.hp)");

	if(strstr(file_types, "cgm"))
		*filters += QString(";; CGM (*.cgm)");

	if(strstr(file_types, "html"))
		*filters += QString(";; HOOPS 3D Stream Control (*.html)");

	if(strstr(file_types, "wrl"))
		*filters += QString(";; VRML (*.wrl)");

	if(strstr(file_types, "jpg"))
		*filters += QString(";; Jpeg (*.jpg *.jpeg)");

	if(strstr(file_types, "bmp"))
		*filters += QString(";; Bmp (*.bmp)");

	if(strstr(file_types, "png"))
		*filters += QString(";; Png (*.png)");

	if(strstr(file_types, "tif"))
		*filters += QString(";; Tiff (*.tif *.tiff)");

	if(strstr(file_types, "gif"))
		*filters += QString(";; Gif (*.gif)");

	if(strstr(file_types, "stl"))
		*filters += QString(";; Stereolithography files (*.stl)");

	if(strstr(file_types, "obj"))
		*filters += QString(";; Alias Wavefront (*.obj)");
}

static void GetExtension(const char *filter, char *extension)
{
    const char *start = strstr(filter,"(*.")+3;
    strcpy(extension, start);
    *(strstr(extension, ")")) = 0;
}

void SpheresHQWidget::OnSaveFileAs()
{
	// when using the static dialog, use double semicolons to seperate the filters 
	QString filters = QString("HOOPS Metafiles (*.hmf) ;; HOOPS Stream File (*.hsf)");
   
	ProcessFilters(&filters, HDB::GetHIOManager()->GetOutputHandlerTypes());

	QString fn2;
	QString fn = QFileDialog::getSaveFileName(
                    this,
                    "Save As",
					"",
                    filters, &fn2);

	if(fn.endsWith(")"))
		fn.chop(1);

	char filter[4096];
	char ext[4096];
	strcpy(filter, fn2.toLatin1());

	if (!fn.isEmpty())
	{
		float width = 8.5;
		float height = 11;		 
		char file_name[4096];
		
		strcpy(file_name, fn.toLatin1());

		if (strstr(file_name,"."))
		    HUtility::FindFileNameExtension(file_name, ext);
		else
		{
		    GetExtension(filter, ext);
		    strcat(file_name,".");
		    strcat(file_name,ext);
		}
		

		if (streq(ext, "tif") || streq(ext, "tiff") ||
			streq(ext, "jpg") || streq(ext, "jpeg") || 
			streq(ext, "png") || streq(ext,"bmp") ) {
			width=10.00;
			height=6.25;
		}

		HFileOutputResult result = m_pHBaseModel->Write(file_name, m_pHView, width, height);

		if(result == OutputBadFileName)
			QMessageBox::information( this, "Spheres",
			"A problem occurred with the file name provided.\n"
			"perhaps you don't have read permission or it is missing.\n");
		else if(result == OutputNotHandled)
			QMessageBox::information( this, "Spheres",
			"This program doesn't have a handler for this file operation.\n");
		else if(result != OutputOK)
			QMessageBox::information( this, "Spheres",
			"A problem occurred during this file operation.\n");
	}
}


// open a load file dialog
void SpheresHQWidget::OnLoad()
{
	QFileDialog* qfd = new QFileDialog(this, "qfd");

    // setup selection filter
    QStringList demFilters;
    demFilters.append("HOOPS Binary Stream Files (*.hsf)");
    demFilters.append("HOOPS Metafiles (*.hmf)");
    demFilters.append("VRML (*.wrl)");
    demFilters.append("Gif (*.gif)");
    demFilters.append("Stereolithography files (*.stl)");
    demFilters.append("Alias Wavefront (*.obj)");
    demFilters.append("Shperes dem files (*.sph)");


    qfd->setFilters(demFilters);

    // first get new filename
    qfd->setFileMode(QFileDialog::AnyFile);

    if (qfd->exec() == QDialog::Accepted){

		QString fname = (qfd->selectedFiles()).front();
		if (!fname.isEmpty())
			this->load(fname.toLatin1());
	}

	delete qfd;
}
  

void SpheresHQWidget::OnOrbit()  
{ 
	// Set MVO View Object current Operator to HOpCameraOrbit  

	if (m_pHView->GetCurrentOperator()) 
	delete m_pHView->GetCurrentOperator(); 

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));  

} 
  
void SpheresHQWidget::OnObjectRotate()  
{ 
	// Set MVO View Object current Operator to HOpObjectRotate 

	if (m_pHView->GetCurrentOperator()) 
	delete m_pHView->GetCurrentOperator(); 

	m_pHView->SetCurrentOperator(new HOpObjectRotate(m_pHView));  

} 

// real time zoomer
void SpheresHQWidget::OnZoom() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoom(m_pHView));
}

// window zoomer
void SpheresHQWidget::OnZoomToWindow() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoomBox(m_pHView));
}

// resets the camera to view the world space extents of the model
void SpheresHQWidget::OnZoomToExtents() 
{
    m_pHView->ZoomToExtents();
}
  
// panner
void SpheresHQWidget::OnPan() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();
    m_pHView->SetCurrentOperator(new HOpCameraPan(m_pHView));		

}


// create sphere
void SpheresHQWidget::OnCreateSphere() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HMyCreateSphere(m_pHView, 0, 1, 50));			


}

// create cone
void SpheresHQWidget::OnCreateCone() 
{
    if (m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateCone(m_pHView));		


}

// create cylinder
void SpheresHQWidget::OnCreateCylinder() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();


    m_pHView->SetCurrentOperator(new HOpCreateCylinder(m_pHView));		

}
  

// select by window
void SpheresHQWidget::OnSelectByWindow()
{
    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();
	
    m_pHView->SetCurrentOperator(new HOpSelectArea(m_pHView));		

}


// render shaded model 
void SpheresHQWidget::OnRenderModeShaded()
{
 	m_pHView->SetRenderMode(HRenderShaded, true);
	m_pHView->Update();
}

// render hiddenline model 
void SpheresHQWidget::OnRenderModeHiddenline()
{
 	m_pHView->SetRenderMode(HRenderHiddenLineFast, true);
	m_pHView->Update();
}

// render wireframe model 
void SpheresHQWidget::OnRenderModeWireframe()
{
 	m_pHView->SetRenderMode(HRenderWireframe, true);
	m_pHView->Update();
}

void SpheresHQWidget::OnChangeMaterial() 
{
    ((HSpheresView *)m_pHView)->ChangeMaterial();
}

void SpheresHQWidget::OnAnnotate() 
{
    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();
	
    m_pHView->SetCurrentOperator(new HOpMarkupAnnotate(m_pHView));		
}

void SpheresHQWidget::OnRunMyCode() 
{
	// this is a function in which developers can
	// write their own simple HOOPS functions
	QMessageBox::information( this, "Simple", "I love HOOPS!!!!");		
}


