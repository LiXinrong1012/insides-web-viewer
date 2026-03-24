// HQApplication.cpp - Implementation of the HQApplication class 

#include <stdlib.h>


// qt includes
#include <QApplication>
#include <QCoreApplication>
#include <QPoint>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QPixmap>
#include <QBitmap>
#include <QToolBar>
#include <QToolButton>
#include <QMainWindow>
#include <QMessageBox> 
#include <QSplitter>
#include <QLayout> 
#include <QHBoxLayout> 
#include <QWorkspace>
#include <QFrame>
#include <QLayout>

// location of the image files for menubar icons 
#include "images/tsa.xpm" 
#include "images/cone.xpm" 
#include "images/cylinder.xpm" 
#include "images/sphere.xpm" 
#include "images/fittowindow.xpm" 
#include "images/folder.xpm" 
#include "images/orbit.xpm" 
#include "images/pan.xpm" 
#include "images/zoominter.xpm" 
#include "images/zoomtowindow.xpm"
#include "images/selectwindow.xpm" 
#include "images/print.xpm" 
#include "images/page.xpm"
#include "images/gouraud.xpm"
#include "images/hidden.xpm"
#include "images/wire.xpm"
#include "images/mapdata.xpm"
#include "images/isolines.xpm"
#include "images/colorinterp.xpm"
#include "images/quadmesh.xpm"
#include "images/animate.xpm"

// HOOPS/Qt includes 
#include "HQApplication.h" 
#include "AnalysisHQWidget.h" 
#include "HQDeleter.h" 

#include "vhash.h"

// Global HQDeleter object; defined in main.cpp 
extern HQDeleter * deleter; 


//this is used for the global quit
QApplication * HQApplication::myparent;
int HQApplication::count;

QPixmap * HQApplication::tsaIcon = 0;
QPixmap * HQApplication::pageIcon = 0;
QPixmap * HQApplication::openIcon = 0;
QPixmap * HQApplication::printIcon = 0;
QPixmap * HQApplication::zoomextentsIcon = 0;
QPixmap * HQApplication::zoomwindowIcon = 0;
QPixmap * HQApplication::orbitIcon = 0;
QPixmap * HQApplication::zoomIcon = 0;
QPixmap * HQApplication::panIcon = 0;
QPixmap * HQApplication::selectwIcon = 0;
QPixmap * HQApplication::sphereIcon = 0;
QPixmap * HQApplication::coneIcon = 0;
QPixmap * HQApplication::cylinderIcon = 0;
QPixmap * HQApplication::gouraudIcon = 0;
QPixmap * HQApplication::hiddenIcon = 0;
QPixmap * HQApplication::wireframeIcon = 0;
QPixmap * HQApplication::mapDataIcon = 0;
QPixmap * HQApplication::isolinesIcon = 0;
QPixmap * HQApplication::colorInterpIcon = 0;
QPixmap * HQApplication::quadInterpIcon = 0;
QPixmap * HQApplication::animateIcon = 0;



// this should be called only once
HQApplication::HQApplication(QApplication * p, const char * filename) : QMainWindow()
{
	myparent = p;
	count=1;
	
#if USE_MDI
	wh = new_vhash(16,malloc,free);
#endif

	CreatePixmaps();

	this->setWindowIcon(*tsaIcon);
	this->setWindowIconText("Analysis");
	this->setWindowTitle(QString("qt_analysis"));
	this->load(filename);
}

HQApplication::HQApplication(
	const char * filename) : QMainWindow()
{
	count++;
	this->setWindowIcon(*tsaIcon);
	this->setWindowIconText("Analysis");
	this->setWindowTitle(QString("qt_analysis"));
	this->load(filename);
}

HQApplication::~HQApplication()
{

#if USE_MDI
	delete_vhash(wh);
#endif

	count--;
	
	if (count==0) {			

		QApplication::exit(0);
	}
}


void HQApplication::myclose() 
{ 
	// This method uses the HQDelete object to schedule the deletion of  
	// the HQApplication "this" pointer for after the Qt Signal/Slot  
	// processor has completed unwinding. 

	this->hide(); 

	deleter->deleteLater(this); 
} 


void HQApplication::closeEvent( QCloseEvent * ) 
{ 
	// catch the X button 
	myclose(); 
} 


void HQApplication::new_window() 
{ 
	// create a new HQApplication object without loading a file 
#ifdef USE_MDI
	QFrame * qframe = new QFrame(qws);
	QHBoxLayout * qlayout = new QHBoxLayout(qframe);
	qlayout->setMargin(0);
	AnalysisHQWidget * my_widget = new AnalysisHQWidget( qframe, "AnalysisHQWidget", (const char *)0);
	qlayout->addWidget(my_widget);
	my_widget->setMinimumSize( 150, 150 ); 
	vhash_insert_item(wh, (void*)qframe,(void*)my_widget);
	qws->addWindow(qframe);
	qframe->show();
#else
	new HQApplication((const char *)0); 
#endif
} 


// open a file dialog and create a new window to for it
void HQApplication::load()
{
	QFileDialog* qfd = new QFileDialog(this, QString::null);

	// setup selection filter
	QStringList demFilters;
	
	demFilters.append("HOOPS Stream Files (*.hsf)");
	demFilters.append("HOOPS Metafiles (*.hmf)");
	
	qfd->setFilters(demFilters);
	
	// first get new filename
	qfd->setFileMode(QFileDialog::ExistingFile);
	
	if (qfd->exec() == QDialog::Accepted){
	
		QStringList fnames = qfd->selectedFiles();
		QString fname = QString(fnames.first());
		if (!fname.isEmpty())
#ifdef USE_MDI
		{
			QFrame * qframe = new QFrame(qws);
			qframe->SetWindowTitle(QString(fname));
			QHBoxLayout * qlayout = new QHBoxLayout(qframe);
			qlayout->setMargin(0);
			AnalysisHQWidget * my_widget = new AnalysisHQWidget( qframe, "AnalysisHQWidget", (const char *)fname);
			qlayout->addWidget(my_widget);
			my_widget->setMinimumSize( 50, 50 ); 
			qframe->show();
			vhash_insert_item(wh, (void*)qframe,(void*)my_widget);
			qws->addWindow(qframe);
		}
#else
			new HQApplication((const char *)(fname.toAscii()));
#endif
	}

	delete qfd;
}




// about dialog
void HQApplication::about()
{
	QMessageBox::information( this, "Analysis",
		"Analysis Version 1.0");

}


void HQApplication::load(const char * filename)
{

#ifdef USE_MDI
	qws = new QWorkspace( this);
	this->setCentralWidget( qws ); 

	QFrame * qframe = new QFrame(qws);
	QHBoxLayout * qlayout = new QHBoxLayout(qframe);
	qlayout->setMargin(0);
	AnalysisHQWidget * my_widget = new AnalysisHQWidget( qframe, "AnalysisHQWidget", filename);
	qlayout->addWidget(my_widget);
	my_widget->setMinimumSize( 50, 50 ); 
	qframe->show();
	vhash_insert_item(wh, (void*)qframe,(void*)my_widget);
	qws->addWindow(qframe)->setWindowTitle(QString(filename));

#else

	// Create an HOOPS widget
	AnalysisHQWidget * my_widget = new AnalysisHQWidget( this, "AnalysisHQWidget", filename);
	my_widget->setMinimumSize( 50, 50 ); 

	this->setCentralWidget( my_widget ); 

#endif

	/* Create a tool bar*/
	tools = new QToolBar( "ops", this );


	newAct = new QAction(*pageIcon, tr("&New Window"), this);
	connect(newAct, SIGNAL(triggered()), this, SLOT(new_window()));
	tools->addAction(newAct);

	openAct = new QAction(*openIcon, tr("&Open File"), this);
	connect(openAct, SIGNAL(triggered()), this, SLOT(load()));
	tools->addAction(openAct);
	
#ifdef USE_MDI
	printAct = new QAction(*printIcon, tr("&Print"), this);
	connect(printAct, SIGNAL(triggered()), this, SLOT(MDIOnPrint()));
	tools->addAction(printAct);
#else
	printAct = new QAction(*printIcon, tr("&Print"), my_widget);
	connect(printAct, SIGNAL(triggered()), my_widget, SLOT(OnPrint()));
	tools->addAction(printAct);
#endif

	tools->addSeparator ();

#ifdef USE_MDI
	zExtentsAct = new QAction(*zoomextentsIcon, tr("&Zoom to Extents"), this);
	connect(zExtentsAct, SIGNAL(triggered()), this, SLOT(MDIOnZoomToExtents()));
	tools->addAction(zExtentsAct);

	zWindowAct = new QAction(*zoomwindowIcon, tr("&Zoom to Window"), this);
	//zWindowAct->setCheckable(true) ;
	connect(zWindowAct, SIGNAL(triggered()), this, SLOT(MDIOnZoomToWindow()));
	tools->addAction(zWindowAct);
#else
	zExtentsAct = new QAction(*zoomextentsIcon, tr("&Zoom to Extents"), my_widget);
	connect(zExtentsAct, SIGNAL(triggered()), my_widget, SLOT(OnZoomToExtents()));
	tools->addAction(zExtentsAct);

	zWindowAct = new QAction(*zoomwindowIcon, tr("&Zoom to Window"), my_widget);
	//zWindowAct->setCheckable(true) ;
	connect(zWindowAct, SIGNAL(triggered()), my_widget, SLOT(OnZoomToWindow()));
	tools->addAction(zWindowAct);
#endif
	
	tools->addSeparator ();

#ifdef USE_MDI
	orbitAct = new QAction(*orbitIcon, tr("&Orbit"), this);
	//orbitAct->setCheckable(true) ;
	connect(orbitAct, SIGNAL(triggered()), this, SLOT(MDIOnOrbit()));
	tools->addAction(orbitAct);

	zoomAct = new QAction(*zoomIcon, tr("&Zoom"), this);
	//zoomAct->setCheckable(true) ;
	connect(zoomAct, SIGNAL(triggered()), this, SLOT(MDIOnZoom()));
	tools->addAction(zoomAct);

	panAct = new QAction(*panIcon, tr("&Pan"), this);
	//panAct->setCheckable(true) ;
	connect(panAct, SIGNAL(triggered()), this, SLOT(MDIOnPan()));
	tools->addAction(panAct);
#else
	orbitAct = new QAction(*orbitIcon, tr("&Orbit"), my_widget);
	//orbitAct->setCheckable(true) ;
	connect(orbitAct, SIGNAL(triggered()), my_widget, SLOT(OnOrbit()));
	tools->addAction(orbitAct);

	zoomAct = new QAction(*zoomIcon, tr("&Zoom"), my_widget);
	//zoomAct->setCheckable(true) ;
	connect(zoomAct, SIGNAL(triggered()), my_widget, SLOT(OnZoom()));
	tools->addAction(zoomAct);

	panAct = new QAction(*panIcon, tr("&Pan"), my_widget);
	//panAct->setCheckable(true) ;
	connect(panAct, SIGNAL(triggered()), my_widget, SLOT(OnPan()));
	tools->addAction(panAct);
#endif	

	tools->addSeparator ();

#ifdef USE_MDI
	selectWindowAct = new QAction(*selectwIcon, tr("&Select by Window"), this) ;
	//selectWindowAct->setCheckable(true) ;
	connect(selectWindowAct, SIGNAL(triggered()), this, SLOT(MDIOnSelectByWindow())) ;
	tools->addAction(selectWindowAct) ;
#else
	selectWindowAct = new QAction(*selectwIcon, tr("&Select by Window"), my_widget) ;
	//selectWindowAct->setCheckable(true) ;
	connect(selectWindowAct, SIGNAL(triggered()), my_widget, SLOT(OnSelectByWindow())) ;
	tools->addAction(selectWindowAct) ;
#endif

	tools->addSeparator ();

#ifdef USE_MDI
	sphereAct = new QAction(*sphereIcon, tr("&Create Sphere"), this);
	//sphereAct->setCheckable(true) ;
	connect(sphereAct, SIGNAL(triggered()), this, SLOT(MDIOnCreateSphere()));
	tools->addAction(sphereAct);

	coneAct = new QAction(*coneIcon, tr("&Create Cone"), this);
	//coneAct->setCheckable(true) ;
	connect(coneAct, SIGNAL(triggered()), this, SLOT(MDIOnCreateCone()));
	tools->addAction(coneAct);

	cylAct = new QAction(*cylinderIcon, tr("&Create Cylinder"), this);
	//cylAct->setCheckable(true) ;
	connect(cylAct, SIGNAL(triggered()), this, SLOT(MDIOnCreateCylinder()));
	tools->addAction(cylAct);
#else
	sphereAct = new QAction(*sphereIcon, tr("&Create Sphere"), my_widget);
	//sphereAct->setCheckable(true) ;
	connect(sphereAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateSphere()));
	tools->addAction(sphereAct);

	coneAct = new QAction(*coneIcon, tr("&Create Cone"), my_widget);
	//coneAct->setCheckable(true) ;
	connect(coneAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateCone()));
	tools->addAction(coneAct);

	cylAct = new QAction(*cylinderIcon, tr("&Create Cylinder"), my_widget);
	//cylAct->setCheckable(true) ;
	connect(cylAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateCylinder()));
	tools->addAction(cylAct);
#endif

	tools->addSeparator ();

	gouraudAct = new QAction(*gouraudIcon, tr("Gouraud Shaded Render Mode"), my_widget) ;
	//gouraudAct->setCheckable(true) ;
	connect(gouraudAct, SIGNAL(triggered()), my_widget, SLOT(OnRenderModeGouraudShaded())) ;
	tools->addAction(gouraudAct) ;

	hiddenAct = new QAction(*hiddenIcon, tr("Hidden Line Render Mode"), my_widget) ;
	//hiddenAct->setCheckable(true) ;
	connect(hiddenAct, SIGNAL(triggered()), my_widget, SLOT(OnRenderModeHiddenLine())) ;
	tools->addAction(hiddenAct) ;

	wireframeAct = new QAction(*wireframeIcon, tr("Wireframe Render Mode"), my_widget) ;
	//wireframeAct->setCheckable(true) ;
	connect(wireframeAct, SIGNAL(triggered()), my_widget, SLOT(OnRenderModeWireframe())) ;
	tools->addAction(wireframeAct) ;

	tools->addSeparator ();

	mapDataAct = new QAction(*mapDataIcon, tr("Map Data"), my_widget) ;
	connect(mapDataAct, SIGNAL(triggered()), my_widget, SLOT(OnMapData())) ;
	tools->addAction(mapDataAct) ;

	isolinesAct = new QAction(*isolinesIcon, tr("Isolines"), my_widget) ;
	isolinesAct->setCheckable(true) ;
	connect(isolinesAct, SIGNAL(triggered()), my_widget, SLOT(OnDisplayIsolines())) ;
	tools->addAction(isolinesAct) ;

	colorInterpAct = new QAction(*colorInterpIcon, tr("Color Interpolation"), my_widget) ;
	colorInterpAct->setCheckable(true) ;
	connect(colorInterpAct, SIGNAL(triggered()), my_widget, SLOT(OnColorInterpolation())) ;
	tools->addAction(colorInterpAct) ;

	quadInterpAct = new QAction(*quadInterpIcon, tr("Quad Mesh Interpolation"), my_widget) ;
	connect(quadInterpAct, SIGNAL(triggered()), my_widget, SLOT(OnDisplayQuadInterpolate())) ;
	tools->addAction(quadInterpAct) ;

	animateAct = new QAction(*animateIcon, tr("Animate"), my_widget) ;
	connect(animateAct, SIGNAL(triggered()), my_widget, SLOT(OnAnimateColormap())) ;
	tools->addAction(animateAct) ;

	this->addToolBar(tools);

	deleteSelectionAct = new QAction(tr("Delete Selection"), my_widget) ;
	connect(deleteSelectionAct, SIGNAL(triggered()), my_widget, SLOT(OnDeleteSelection())) ;


	// File menu
	QMenu *file = this->menuBar()->addMenu(tr("&File"));
	file->addAction( "New", this, SLOT(new_window()));
	file->addAction( "Open", this, SLOT(load()));
	file->addSeparator();

	file->addAction( "Print", my_widget, SLOT(OnPrint())); 
	file->addAction( "Save", my_widget, SLOT(OnSaveFileAs())); 

	file->addSeparator();
	file->addAction( "Close", this, SLOT(myclose()), Qt::CTRL+Qt::Key_C ); 
	file->addSeparator();
	file->addAction( "Exit", myparent, SLOT(quit()), Qt::CTRL+Qt::Key_Q );
	
#ifndef USE_MDI
	// Manipulate menu
	
	QMenu *manipulate = this->menuBar()->addMenu(tr("&Manipulate"));
	manipulate->addAction(orbitAct);
	manipulate->addAction(zoomAct);
	manipulate->addAction(panAct);
	manipulate->addAction(zWindowAct);
	manipulate->addAction(zExtentsAct);
	
	// Create menu
	QMenu *create = this->menuBar()->addMenu(tr("&Create"));
	create->addAction(sphereAct);
	create->addAction(cylAct);
	create->addAction(coneAct);

	QMenu *select = this->menuBar()->addMenu(tr("&Select")) ;
	select->addAction(selectWindowAct) ;
	select->addAction(deleteSelectionAct) ;

#endif

	// Help menu
	QMenu *help = this->menuBar()->addMenu(tr("&Help"));
	help->addAction( "About", this , SLOT(about()) );
	

	this->resize(640,400);
	this->show();
}

void HQApplication::CreatePixmaps()
{

	tsaIcon = new QPixmap( (const char**)tsa_xpm );
	tsaIcon->setMask( tsaIcon->createHeuristicMask() );
	
	pageIcon = new QPixmap( (const char**)page_xpm );
	pageIcon->setMask( pageIcon->createHeuristicMask() );
	
	openIcon = new QPixmap( (const char**)folder_xpm );
	openIcon->setMask( openIcon->createHeuristicMask() );
	
	printIcon = new QPixmap( (const char**)print_xpm );
	printIcon->setMask( printIcon->createHeuristicMask() );
	
	zoomextentsIcon = new QPixmap( (const char**) fittowindow_xpm );
	zoomextentsIcon->setMask( zoomextentsIcon->createHeuristicMask() );

	zoomwindowIcon = new QPixmap( (const char**)zoomtowindow_xpm);
	zoomwindowIcon->setMask( zoomwindowIcon->createHeuristicMask() );

	orbitIcon = new QPixmap( (const char**)orbit_xpm );
	orbitIcon->setMask( orbitIcon->createHeuristicMask() );

	zoomIcon = new QPixmap( (const char**)zoominter_xpm );
	zoomIcon->setMask( zoomIcon->createHeuristicMask() );

	panIcon = new QPixmap( (const char**)pan_xpm );
	panIcon->setMask( panIcon->createHeuristicMask() );

	selectwIcon = new QPixmap( (const char**)selectwindow_xpm );
	selectwIcon->setMask( selectwIcon->createHeuristicMask() );

	sphereIcon = new QPixmap( (const char**)sphere_xpm );
	sphereIcon->setMask( sphereIcon->createHeuristicMask() );

	coneIcon = new QPixmap( (const char**)cone_xpm );
	coneIcon->setMask( coneIcon->createHeuristicMask() );

	cylinderIcon = new QPixmap( (const char**)cylinder_xpm );
	cylinderIcon->setMask( cylinderIcon->createHeuristicMask() );

	gouraudIcon = new QPixmap( (const char **)gouraud_xpm );
	gouraudIcon->setMask( gouraudIcon->createHeuristicMask() );

	hiddenIcon = new QPixmap( (const char **)hidden_xpm );
	hiddenIcon->setMask( hiddenIcon->createHeuristicMask() );

	wireframeIcon = new QPixmap( (const char **)wire_xpm );
	wireframeIcon->setMask( wireframeIcon->createHeuristicMask() );

	mapDataIcon = new QPixmap( (const char **)mapdata_xpm );
	mapDataIcon->setMask( mapDataIcon->createHeuristicMask() );

	isolinesIcon = new QPixmap( (const char **)isolines_xpm );
	isolinesIcon->setMask( isolinesIcon->createHeuristicMask() );

	colorInterpIcon = new QPixmap( (const char **)colorinterp_xpm );
	colorInterpIcon->setMask( colorInterpIcon->createHeuristicMask() );

	quadInterpIcon = new QPixmap( (const char **)quadmesh_xpm );
	quadInterpIcon->setMask( quadInterpIcon->createHeuristicMask() );

	animateIcon = new QPixmap( (const char **)animate_xpm );
	animateIcon->setMask( animateIcon->createHeuristicMask() );
}

void HQApplication::MDIOnPrint()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnPrint();
	}
#endif
}

void HQApplication::MDIOnSaveFileAs()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnSaveFileAs();
	}
#endif
}

void HQApplication::MDIOnZoomToExtents()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnZoomToExtents();
	}
#endif
}

void HQApplication::MDIOnZoomToWindow()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnZoomToWindow();
	}
#endif
}

void HQApplication::MDIOnOrbit()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnOrbit();
	}
#endif
}

void HQApplication::MDIOnZoom()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnZoom();
	}
#endif
}

void HQApplication::MDIOnPan()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnPan();
	}
#endif
}

void HQApplication::MDIOnSelectByWindow()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnSelectByWindow();
	}
#endif
}

void HQApplication::MDIOnCreateSphere()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnCreateSphere();
	}
#endif
}

void HQApplication::MDIOnCreateCone()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnCreateCone();
	}
#endif
}

void HQApplication::MDIOnCreateCylinder()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		AnalysisHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnCreateCylinder();
	}
#endif
}


