// AnalysisHQWidget.cpp - Implementation of the HOOPS/Qt class AnalysisHQWidget
// 
// More about this class 
//
// $Header: /files/homes/master/cvs/hoops_master/analysis/AnalysisHQWidget.cpp,v 1.5 2007-11-28 19:16:18 nathan Exp $

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
//#include "HGlobals.h"
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
#include "HUtility.h"
#include "HIOManager.h"
#undef null

#include "HStream.h"
#include "HOpcodeHandler.h"
#include "HOpcodeShell.h"


// the qt/hoops base class
#include "AnalysisHQWidget.h"
#include "HAnalysisModel.h"
#include "HAnalysisView.h"
#include "HAnalysisSelectionSet.h"


// hoops include
#include "hc.h"

// this is setup in main
extern HDB * m_pHDB;



AnalysisHQWidget::AnalysisHQWidget(QWidget* parent, const char* name , const char * filename) 
    : HQWidget( parent, name ) 
{ 
	// Create and initialize HOOPS/MVO Model and View objects 
	m_pHBaseModel = new HAnalysisModel(); 
	m_pHBaseModel->Init(); 

	// Initialize View object to null ; gets created in SoccerHQWidget::Init 
	m_pHView = 0; 

	m_bDisplayIsolines = false ;
	m_bColorInterpolation = false ;

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
  

AnalysisHQWidget::~AnalysisHQWidget() 
{ 
 // Destructor  

	// Clean up memory 
	if(m_pHView)        delete m_pHView; 
	if(m_pHBaseModel)   delete m_pHBaseModel; 

} 

void AnalysisHQWidget::Init() 
{ 
	// create and initialize MVO HBaseView object 
	m_pHView = new HAnalysisView(m_pHBaseModel, NULL, NULL, NULL, GetWindowId(), GetColorMap(), GetClipOverride()); 

	// initialize and set the default conditions viz. operator, rendermode etc.
	((HAnalysisView *)m_pHView)->Init();

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));	
	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true);
	m_pHView->RenderGouraud();  // set the render mode to gouraud


	m_pHView->FitWorld();		// fit the camera to the scene extents
	m_pHView->CameraPositionChanged();
} 
  

// load a file into our view
void AnalysisHQWidget::load(const char * filename)
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
		QMessageBox::information( this, "Analysis\n",
		"This file was created with a newer version of the HOOPS/Stream Toolkit.\n"
		"To view it, this application will need to be updated.\n");
	else if(result == InputBadFileName)
		QMessageBox::information( this, "Analysis\n",
		"A problem occurred with the file name provided.\n"
		"perhaps you don't have read permission or it is missing.\n");
	else if(result == InputNotHandled)
		QMessageBox::information( this, "Analysis\n",
		"This program doesn't have a handler for this file operation.\n");
	else if(result != InputOK)
		QMessageBox::information( this, "Analysis\n",
		"A problem occurred during this file operation.\n");

	//SetupView() ;

	if (m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));


	m_pHView->Update();
}
  
// print
void AnalysisHQWidget::OnPrint()
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

void AnalysisHQWidget::OnSaveFileAs()
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
			QMessageBox::information( this, "Analysis",
			"A problem occurred with the file name provided.\n"
			"perhaps you don't have read permission or it is missing.\n");
		else if(result == OutputNotHandled)
			QMessageBox::information( this, "Analysis",
			"This program doesn't have a handler for this file operation.\n");
		else if(result != OutputOK)
			QMessageBox::information( this, "Analysis",
			"A problem occurred during this file operation.\n");
	}
}


// open a load file dialog
void AnalysisHQWidget::OnLoad()
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


    qfd->setFilters(demFilters);

    // first get new filename
    qfd->setFileMode(QFileDialog::ExistingFile);

    if (qfd->exec() == QDialog::Accepted){

		QString fname = (qfd->selectedFiles()).front();
		if (!fname.isEmpty())
			this->load(fname.toLatin1());
	}

	delete qfd;
}
  

void AnalysisHQWidget::OnOrbit()  
{ 
	// Set MVO View Object current Operator to HOpCameraOrbit  

	if (m_pHView->GetCurrentOperator()) 
	delete m_pHView->GetCurrentOperator(); 

	m_pHView->SetCurrentOperator(new HOpCameraOrbit(m_pHView));  
	((HOpCameraOrbit *)m_pHView->GetOperator())->SetLightFollowsCamera(true) ;
} 
  

// real time zoomer
void AnalysisHQWidget::OnZoom() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoom(m_pHView));
	((HOpCameraZoom *)m_pHView->GetOperator())->SetLightFollowsCamera(true) ;
}

// window zoomer
void AnalysisHQWidget::OnZoomToWindow() 
{
	if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCameraZoomBox(m_pHView));
	((HOpCameraZoomBox *)m_pHView->GetOperator())->SetLightFollowsCamera(true) ;
}

// resets the camera to view the world space extents of the model
void AnalysisHQWidget::OnZoomToExtents() 
{
    m_pHView->ZoomToExtents();
}
  
// panner
void AnalysisHQWidget::OnPan() 
{

    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();
    m_pHView->SetCurrentOperator(new HOpCameraPan(m_pHView));		

}


// create sphere
void AnalysisHQWidget::OnCreateSphere() 
{
    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateSphere(m_pHView));		

}

// create cone
void AnalysisHQWidget::OnCreateCone() 
{
    if (m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateCone(m_pHView));		
}



// create cylinder
void AnalysisHQWidget::OnCreateCylinder() 
{
    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();

    m_pHView->SetCurrentOperator(new HOpCreateCylinder(m_pHView));		
}

// select by window
void AnalysisHQWidget::OnSelectByWindow()
{
    if (m_pHView->GetCurrentOperator())
	    delete m_pHView->GetCurrentOperator();
	
    m_pHView->SetCurrentOperator(new HOpSelectArea(m_pHView));		
}

void AnalysisHQWidget::OnDeleteSelection()
{
	m_pHView->DeleteSelectionList(true);
	m_pHView->Update();	
}

// render gouraud shaded model 
void AnalysisHQWidget::OnRenderModeGouraudShaded()
{
	m_pHView->SetRenderMode(HRenderGouraud, true);
	m_pHView->Update();
}

// render hidden line model 
void AnalysisHQWidget::OnRenderModeHiddenLine()
{
	m_pHView->SetRenderMode(HRenderHiddenLine, true);
	m_pHView->Update();
}

// render wireframe model 
void AnalysisHQWidget::OnRenderModeWireframe()
{
	m_pHView->SetRenderMode(HRenderWireframe, true);
	m_pHView->Update();
}

void AnalysisHQWidget::OnMapData()
{
	bool result = ((HAnalysisView *)m_pHView)->MapSelectionSet() ;
	if ( !result )
		QMessageBox::information(this, "Analysis", "You must first select a shell.") ;
}

void AnalysisHQWidget::OnDisplayIsolines()
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

void AnalysisHQWidget::OnColorInterpolation()
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

void AnalysisHQWidget::OnDisplayQuadInterpolate()
{
	bool result = ((HAnalysisView *)m_pHView)->QuadInterpolateSelectionSet();
	if ( !result )
		QMessageBox::information(this, "Analysis", "You must first select a shell.") ;
}

void AnalysisHQWidget::OnAnimateColormap()
{
	bool result = ((HAnalysisView *)m_pHView)->AnimateSelectionSet();
	if ( !result )
		QMessageBox::information(this, "Analysis", "Must map data to create artificial color index array first.") ;
}
