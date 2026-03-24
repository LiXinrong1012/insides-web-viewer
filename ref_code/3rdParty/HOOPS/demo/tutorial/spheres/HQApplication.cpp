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
#include "images/rotate.xpm"
#include "images/pan.xpm"

#include "images/annotate.xpm"
#include "images/freehandmkp.xpm" 
 
#include "images/zoominter.xpm" 
#include "images/zoomtowindow.xpm"

#include "images/selectwindow.xpm" 

#include "images/gouraud.xpm" 
#include "images/hidden.xpm" 
#include "images/wire.xpm" 


#include "images/print.xpm" 
#include "images/page.xpm" 
#include "images/runmycode.xpm"

// HOOPS/Qt includes 
#include "HQApplication.h" 
#include "SpheresHQWidget.h" 
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
QPixmap * HQApplication::rotateIcon = 0;
QPixmap * HQApplication::zoomIcon = 0;
QPixmap * HQApplication::panIcon = 0;

QPixmap * HQApplication::selectwIcon = 0;

QPixmap * HQApplication::gouraudIcon = 0;
QPixmap * HQApplication::hiddenIcon = 0;
QPixmap * HQApplication::wireframeIcon = 0;

QPixmap * HQApplication::sphereIcon = 0;
QPixmap * HQApplication::coneIcon = 0;
QPixmap * HQApplication::cylinderIcon = 0;

QPixmap * HQApplication::annotateIcon = 0;
QPixmap * HQApplication::materialIcon = 0;
QPixmap * HQApplication::runmycodeIcon = 0 ;

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
	this->setWindowIconText("Spheres");
	this->setWindowTitle(QString("qt_spheres"));
	this->load(filename);
}

HQApplication::HQApplication(
	const char * filename) : QMainWindow()
{

	count++;
	this->setWindowIcon(*tsaIcon);
	this->setWindowIconText("Spheres");
	this->setWindowTitle(QString("qt_spheres"));
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
	SpheresHQWidget * my_widget = new SpheresHQWidget( qframe, "SpheresHQWidget", (const char *)0);
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
					SpheresHQWidget * my_widget = new SpheresHQWidget( qframe, "SpheresHQWidget", (const char *)fname);
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
	QMessageBox::information( this, "Spheres",
		"Spheres v1.0");

}


void HQApplication::load(const char * filename)
{

#ifdef USE_MDI
	qws = new QWorkspace( this);
	this->setCentralWidget( qws ); 

	QFrame * qframe = new QFrame(qws);
	QHBoxLayout * qlayout = new QHBoxLayout(qframe);
	qlayout->setMargin(0);
	SpheresHQWidget * my_widget = new SpheresHQWidget( qframe, "SpheresHQWidget", filename);
	qlayout->addWidget(my_widget);
	my_widget->setMinimumSize( 50, 50 ); 
	qframe->show();
	vhash_insert_item(wh, (void*)qframe,(void*)my_widget);
	qws->addWindow(qframe)->setWindowTitle(QString(filename));

#else

	// Create an HOOPS widget
	SpheresHQWidget * my_widget = new SpheresHQWidget( this, "SpheresHQWidget", filename);
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
	connect(zWindowAct, SIGNAL(triggered()), this, SLOT(MDIOnZoomToWindow()));
	tools->addAction(zWindowAct);
#else
	zExtentsAct = new QAction(*zoomextentsIcon, tr("&Zoom to Extents"), my_widget);
	connect(zExtentsAct, SIGNAL(triggered()), my_widget, SLOT(OnZoomToExtents()));
	tools->addAction(zExtentsAct);

	zWindowAct = new QAction(*zoomwindowIcon, tr("&Zoom to Window"), my_widget);
	connect(zWindowAct, SIGNAL(triggered()), my_widget, SLOT(OnZoomToWindow()));
	tools->addAction(zWindowAct);
#endif
	
	tools->addSeparator ();

#ifdef USE_MDI
	orbitAct = new QAction(*orbitIcon, tr("&Orbit"), this);
	connect(orbitAct, SIGNAL(triggered()), this, SLOT(MDIOnOrbit()));
	tools->addAction(orbitAct);

	zoomAct = new QAction(*zoomIcon, tr("&Zoom"), this);
	connect(zoomAct, SIGNAL(triggered()), this, SLOT(MDIOnZoom()));
	tools->addAction(zoomAct);

	panAct = new QAction(*panIcon, tr("&Pan"), this);
	connect(panAct, SIGNAL(triggered()), this, SLOT(MDIOnPan()));
	tools->addAction(panAct);
#else
	orbitAct = new QAction(*orbitIcon, tr("&Orbit"), my_widget);
	connect(orbitAct, SIGNAL(triggered()), my_widget, SLOT(OnOrbit()));
	tools->addAction(orbitAct);

	zoomAct = new QAction(*zoomIcon, tr("&Zoom"), my_widget);
	connect(zoomAct, SIGNAL(triggered()), my_widget, SLOT(OnZoom()));
	tools->addAction(zoomAct);

	panAct = new QAction(*panIcon, tr("&Pan"), my_widget);
	connect(panAct, SIGNAL(triggered()), my_widget, SLOT(OnPan()));
	tools->addAction(panAct);
#endif	

	tools->addSeparator ();

#ifdef USE_MDI
	selectWindowAct = new QAction(*selectwIcon, tr("&Select by Window"), this) ;
	connect(selectWindowAct, SIGNAL(triggered()), this, SLOT(MDIOnSelectByWindow())) ;
	tools->addAction(selectWindowAct) ;
#else
	selectWindowAct = new QAction(*selectwIcon, tr("&Select by Window"), my_widget) ;
	connect(selectWindowAct, SIGNAL(triggered()), my_widget, SLOT(OnSelectByWindow())) ;
	tools->addAction(selectWindowAct) ;
#endif

	tools->addSeparator ();

#ifdef USE_MDI
	gouraudAct = new QAction(*gouraudIcon, tr("&Shaded"), this) ;
	connect(gouraudAct, SIGNAL(triggered()), this, SLOT(MDIOnRenderModeShaded())) ;
	tools->addAction(gouraudAct) ;
    
    hiddenAct = new QAction(*hiddenIcon, tr("&Hidden Line"), this) ;
    connect(hiddenAct, SIGNAL(triggered()), this, SLOT(MDIOnRenderModeHiddenline())) ;
    tools->addAction(hiddenAct) ;
    
    wireframeAct = new QAction(*wireframeIcon, tr("&Wire Frame"), this) ;
    connect(wireframeAct, SIGNAL(triggered()), this, SLOT(MDIOnRenderModeWireframe())) ;
    tools->addAction(wireframeAct) ;
#else
	gouraudAct = new QAction(*gouraudIcon, tr("&Shaded"), my_widget) ;
	connect(gouraudAct, SIGNAL(triggered()), my_widget, SLOT(OnRenderModeShaded())) ;
	tools->addAction(gouraudAct) ;
    
    hiddenAct = new QAction(*hiddenIcon, tr("&Hidden Line"), my_widget) ;
    connect(hiddenAct, SIGNAL(triggered()), my_widget, SLOT(OnRenderModeHiddenline())) ;
    tools->addAction(hiddenAct) ;
    
    wireframeAct = new QAction(*wireframeIcon, tr("&Wire Frame"), my_widget) ;
    connect(wireframeAct, SIGNAL(triggered()), my_widget, SLOT(OnRenderModeWireframe())) ;
    tools->addAction(wireframeAct) ;
#endif

	tools->addSeparator ();

#ifdef USE_MDI
	sphereAct = new QAction(*sphereIcon, tr("&Create Sphere"), this);
	connect(sphereAct, SIGNAL(triggered()), this, SLOT(MDIOnCreateSphere()));
	tools->addAction(sphereAct);

	coneAct = new QAction(*coneIcon, tr("&Create Cone"), this);
	connect(coneAct, SIGNAL(triggered()), this, SLOT(MDIOnCreateCone()));
	tools->addAction(coneAct);

	cylAct = new QAction(*cylinderIcon, tr("&Create Cylinder"), this);
	connect(cylAct, SIGNAL(triggered()), this, SLOT(MDIOnCreateCylinder()));
	tools->addAction(cylAct);

	tools->addSeparator ();

	runAct = new QAction(*runmycodeIcon, tr("&Run My Code"), this);
	connect(runAct, SIGNAL(triggered()), this, SLOT(MDIOnRunMyCode()));
	tools->addAction(runAct);
#else
	sphereAct = new QAction(*sphereIcon, tr("&Create Sphere"), my_widget);
	connect(sphereAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateSphere()));
	tools->addAction(sphereAct);

	coneAct = new QAction(*coneIcon, tr("&Create Cone"), my_widget);
	connect(coneAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateCone()));
	tools->addAction(coneAct);

	cylAct = new QAction(*cylinderIcon, tr("&Create Cylinder"), my_widget);
	connect(cylAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateCylinder()));
	tools->addAction(cylAct);

	tools->addSeparator ();

	runAct = new QAction(*runmycodeIcon, tr("&Run My Code"), my_widget);
	connect(runAct, SIGNAL(triggered()), my_widget, SLOT(OnRunMyCode()));
	tools->addAction(runAct);

#endif

	tools->addSeparator ();

	materialAct = new QAction(*materialIcon, tr("&Material"), my_widget) ;
	connect(materialAct, SIGNAL(triggered()), my_widget, SLOT(OnChangeMaterial())) ;
	tools->addAction(materialAct) ;
	
	annotateAct = new QAction(*annotateIcon, tr("&Annotate"), my_widget) ;
	connect(annotateAct, SIGNAL(triggered()), my_widget, SLOT(OnAnnotate())) ;
	tools->addAction(annotateAct) ;

	this->addToolBar(tools);
    
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
	manipulate->addAction( orbitAct);
	manipulate->addAction(zoomAct);
	manipulate->addAction(panAct);
	manipulate->addAction(zWindowAct);
	manipulate->addAction(zExtentsAct);
	
	// Create menu
	QMenu *create = this->menuBar()->addMenu(tr("&Create"));
	create->addAction(sphereAct);
	create->addAction(cylAct);
	create->addAction(coneAct);
	create->addAction(runAct);
	
	QMenu *select = this->menuBar()->addMenu(tr("&Select")) ;
	select->addAction(selectWindowAct) ;
	
	QMenu *view = this->menuBar()->addMenu(tr("&View")) ;
	view->addAction(gouraudAct) ;
	view->addAction(hiddenAct) ;
	view->addAction(wireframeAct) ;
	
	QMenu *annotate = this->menuBar()->addMenu(tr("&Annotate")) ;
	annotate->addAction(annotateAct) ;

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

    rotateIcon = new QPixmap( (const char**)rotate_xpm );
	rotateIcon->setMask( rotateIcon->createHeuristicMask() );

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

    gouraudIcon = new QPixmap( (const char**)gouraud_xpm );
	gouraudIcon->setMask( gouraudIcon->createHeuristicMask() );

    hiddenIcon = new QPixmap( (const char**)hidden_xpm );
	hiddenIcon->setMask( hiddenIcon->createHeuristicMask() );

    wireframeIcon = new QPixmap( (const char**)wire_xpm );
	wireframeIcon->setMask( wireframeIcon->createHeuristicMask() );

    materialIcon = new QPixmap( (const char**)freehandmkp_xpm );
	materialIcon->setMask( materialIcon->createHeuristicMask() );

    annotateIcon = new QPixmap( (const char**)annotate_xpm );
	annotateIcon->setMask( annotateIcon->createHeuristicMask() );
	
	runmycodeIcon = new QPixmap( (const char**)runmycode_xpm );	
	runmycodeIcon->setMask( runmycodeIcon->createHeuristicMask() );
}

void HQApplication::MDIOnPrint()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
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
		SoccerHQWidget* w;
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
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
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
		SpheresHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnCreateCylinder();
	}
#endif
}

void HQApplication::MDIOnRunMyCode()
{
#if USE_MDI
	QFrame* f=(QFrame*)qws->activeWindow();
	if(f) {
		SimpleHQWidget* w;
		vhash_lookup_item(wh, (void*)f, (void**)&w); 
		if(w) w->OnRunMyCode();
	}
#endif
}

