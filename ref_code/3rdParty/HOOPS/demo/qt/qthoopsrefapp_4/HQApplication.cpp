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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HQApplication.cpp,v 1.77 2009-12-17 22:19:57 reuben Exp $
//




#include <stdlib.h>

#ifdef check
#undef check
#endif

// qt includes
#include <QtCore>
#include <QtGui>



#include "images/tsa.xpm"
#include "images/cone.xpm"
#include "images/nurbs.xpm"
#include "images/nurb3d.xpm"
#include "images/cylinder.xpm"
#include "images/fittowindow.xpm"
#include "images/folder.xpm"
#include "images/orbit.xpm"
#include "images/page.xpm"
#include "images/pan.xpm"
#include "images/print.xpm"
#include "images/select.xpm"
#include "images/selectwindow.xpm"
#include "images/sphere.xpm"
#include "images/translate.xpm"
#include "images/rotate.xpm"
#include "images/zoominter.xpm"
#include "images/walk.xpm"
#include "images/zoomtowindow.xpm"
#include "images/intersect.xpm"
#include "images/subtract.xpm"
#include "images/union.xpm"
#include "images/front.xpm"
#include "images/back.xpm"
#include "images/top.xpm"
#include "images/bottom.xpm"
#include "images/left.xpm"
#include "images/right.xpm"
#include "images/isometric.xpm"
#include "images/freehandmkp.xpm"
#include "images/rectanglemkp.xpm"
#include "images/circlemkp.xpm"
#include "images/textmkp.xpm"
#include "images/savemkp1.xpm"
#include "images/savemkp2.xpm"
#include "images/annotate.xpm"
#include "images/distance.xpm"
#include "images/cuttingplane.xpm"
#include "images/query.xpm"
#include "images/animate.xpm"
#include "images/ani_back.xpm"
#include "images/ani_play_pause.xpm"
#include "images/ani_stop.xpm"
#include "images/clashdetect.xpm"
#include "images/home.xpm"
#include "images/undo.xpm"
#include "images/redo.xpm"


#include "HQApplication.h"
#include "MyHQWidget.h"
#include "HQPrintDlg.h"
#include "HIOManager.h"

//#include "HQSegmentBrowserFrame.h"
#include "hversion.h" //HOOPS 3dgs' version header



//this is used for the global quit
QApplication * HQApplication::myparent;
int HQApplication::count;

HQPrintDlg * HQApplication::print_dlg=0;

QPixmap * HQApplication::tsaIcon = 0;
QPixmap * HQApplication::pageIcon = 0;
QPixmap * HQApplication::openIcon = 0;
QPixmap * HQApplication::printIcon = 0;
QPixmap * HQApplication::zoomextentsIcon = 0;
QPixmap * HQApplication::zoomwindowIcon = 0;
QPixmap * HQApplication::orbitIcon = 0;
QPixmap * HQApplication::zoomIcon = 0;
QPixmap * HQApplication::walkIcon = 0;
QPixmap * HQApplication::panIcon = 0;
QPixmap * HQApplication::selectIcon = 0;
QPixmap * HQApplication::selectwindowIcon = 0;
QPixmap * HQApplication::sphereIcon = 0;
QPixmap * HQApplication::coneIcon = 0;
QPixmap * HQApplication::cylinderIcon = 0;
QPixmap * HQApplication::nurbsIcon = 0;
QPixmap * HQApplication::nurb3dIcon = 0;
QPixmap * HQApplication::translateIcon = 0;
QPixmap * HQApplication::rotateIcon = 0;
QPixmap * HQApplication::subtractIcon = 0;
QPixmap * HQApplication::intersectIcon = 0;
QPixmap * HQApplication::unionIcon = 0;
QPixmap * HQApplication::frontIcon = 0;
QPixmap * HQApplication::backIcon = 0;
QPixmap * HQApplication::topIcon = 0;
QPixmap * HQApplication::bottomIcon = 0;
QPixmap * HQApplication::leftIcon = 0;
QPixmap * HQApplication::rightIcon = 0;
QPixmap * HQApplication::isoIcon = 0;
QPixmap * HQApplication::freehandmkpIcon = 0;
QPixmap * HQApplication::rectanglemkpIcon = 0;
QPixmap * HQApplication::circlemkpIcon = 0;
QPixmap * HQApplication::textmkpIcon = 0;
QPixmap * HQApplication::savemkp1Icon = 0;
QPixmap * HQApplication::savemkp2Icon = 0;
QPixmap * HQApplication::annotateIcon = 0;
QPixmap * HQApplication::distanceIcon = 0;
QPixmap * HQApplication::queryIcon = 0;
QPixmap * HQApplication::cuttingplaneIcon = 0;
QPixmap * HQApplication::animateIcon = 0;
QPixmap * HQApplication::ani_backIcon = 0;
QPixmap * HQApplication::ani_play_pauseIcon = 0;
QPixmap * HQApplication::ani_stopIcon = 0;
QPixmap * HQApplication::clashDetectIcon = 0;
QPixmap * HQApplication::homeIcon = 0;
QPixmap * HQApplication::undoIcon = 0;
QPixmap * HQApplication::redoIcon = 0;


// this should be called only once
HQApplication::HQApplication(QApplication * p, QString const & filename) : QMainWindow()
{
	myparent = p;
	count=1;
	aa_level = 0;

	CreatePixmaps();

	this->setWindowIcon(*tsaIcon);
	this->setWindowIconText("Qt HOOPS Viewer");
	this->setWindowTitle("Qt HOOPS Viewer");
	this->load(filename);
	if(!filename.isEmpty()){
		QFileInfo info(filename);
		last_directory = info.dir().path();
	}
	else last_directory = QDir::currentPath();
}

HQApplication::HQApplication(
	QString const & filename, int aa) : QMainWindow()
{
	aa_level = aa;
	count++;

	if(!filename.isEmpty()){

		this->load(filename);
		QFileInfo info(filename);
		last_directory = info.dir().path();
	}
	else
		last_directory = QDir::currentPath();

	this->setWindowIcon(*tsaIcon);
	this->setWindowIconText("Qt HOOPS Viewer");
	this->setWindowTitle("Qt HOOPS Viewer");
}

HQApplication::~HQApplication()
{
	count--;

	if (count==0) {
			
		if(print_dlg){
			print_dlg->hide();
			delete print_dlg;
		}

		QApplication::exit(0);
	}
}

void HQApplication::OnAntiAlias0x(){
	aa_level = 0;
}
void HQApplication::OnAntiAlias2x(){
	aa_level = 2;
}
void HQApplication::OnAntiAlias4x(){
	aa_level = 4;
}
void HQApplication::OnAntiAlias8x(){
	aa_level = 8;
}
void HQApplication::OnAntiAliasOff(){
	aa_level = 0;
}

void HQApplication::myclose()
{
	this->close();

	this->deleteLater();
}

// catch the X button
void HQApplication::closeEvent( QCloseEvent * )
{
	myclose();
}

// create a new empty window
void HQApplication::new_window()
{
	new HQApplication((const char *)0, this->aa_level);
}

void HQApplication::RunPrintDialog(MyHQWidget * w)
{
    if(!print_dlg)
	print_dlg = new HQPrintDlg(this);
	
    print_dlg->PrintFor(w);
}

// open a file dialog and create a new window to for it
void HQApplication::load()
{
	QString filters = QString(
#ifdef PARASOLID
	"Parasolid Files (*.X*T)" ";;"
#endif
	"HOOPS Files (*.hsf *.hmf)");

	MyHQWidget::ProcessFilters(filters, HDB::GetHIOManager()->GetInputHandlerTypes());

	QString fname = QFileDialog::getOpenFileName(
                    this,
                    "Choose a file",
					my_widget->last_file,
                    filters);

	if (!fname.isEmpty()){
		QFileInfo *info = new QFileInfo(fname);
		last_directory = info->dir().path();
		delete info;
		new HQApplication(fname, this->aa_level);
	}

	
}

// about dialog
void HQApplication::about()
{
	char tempstr[4096];
        int major, minor;

	major = HOOPS_VERSION / 100;
	minor = HOOPS_VERSION % 100;
	sprintf( tempstr, 
		"Qt HOOPS Viewer %d.%d\n"
		"Copyright (C) 1999-2006 Tech Soft 3D\n"
		"Built against version %s of Qt, from TrollTech\n"
		"\nFor information about the HOOPS 3D Application Framework\n"
		"Send email to info@techsoft3d.com or visit"
		" techsoft3d.com",
			major,
			minor,
			QT_VERSION_STR );

	QMessageBox::information( this, "about Qt HOOPS Viewer", tempstr );

}

void HQApplication::OnExtraSlot1(){
}

void HQApplication::OnExtraSlot2(){
}

void HQApplication::OnExtraSlot3(){
}

void HQApplication::OnExtraSlot4(){
}

void HQApplication::OnExtraSlot5(){
}

void HQApplication::load(QString const & filename)
{
	QSplitter *splitter = new QSplitter(this);

	// create both the segment browser and the HOOPS widget
	segBrowser = new HQSegmentBrowserFrame(splitter, this);
	my_widget = new MyHQWidget( splitter, this, "MyHQWidget", this->aa_level, filename, segBrowser);
	my_widget->setMinimumSize( 50, 50 ); 

	segBrowser->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	my_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	QList<int> list;
	list.append(200);
	list.append(800);
	splitter->setSizes(list);
	segBrowser->hide();

	this->setCentralWidget(splitter);

	// Create file menu
	QMenu *file = this->menuBar()->addMenu(tr("&File")); 


	newAct = new QAction(*pageIcon, tr("&New"), this);
	connect(newAct, SIGNAL(triggered()), this, SLOT(new_window()));
	file->addAction(newAct);

	openAct = new QAction(*openIcon, tr("&Open"), this);
	connect(openAct, SIGNAL(triggered()), this, SLOT(load()));
	file->addAction(openAct);

	loadAct = new QAction(tr("&Load"), this);
	connect(loadAct, SIGNAL(triggered()), my_widget, SLOT(OnLoad()));
	connect(my_widget, SIGNAL(load_successful()), this, SLOT(SetUpMenus())); //re-set the menus after we load a new file
	file->addAction(loadAct);

	QMenu *aaMenu = file->addMenu(tr("&Screen Anti-Alias"));

	aa0xAct = new QAction(tr("&0x"), this);
	aa0xAct->setCheckable(true);
	if(this->aa_level == 0) aa0xAct->setChecked(true);
	//connect(aa0xAct, SIGNAL(triggered()), my_widget, SLOT(OnAntiAlias0x()));
	connect(aa0xAct, SIGNAL(triggered()), this, SLOT(OnAntiAlias0x()));
	aaMenu->addAction(aa0xAct);

	aa2xAct = new QAction(tr("&2x"), this);
	aa2xAct->setCheckable(true);
	if(this->aa_level == 2) aa2xAct->setChecked(true);
	//connect(aa2xAct, SIGNAL(triggered()), my_widget, SLOT(OnAntiAlias2x()));
	connect(aa2xAct, SIGNAL(triggered()), this, SLOT(OnAntiAlias2x()));
	aaMenu->addAction(aa2xAct);

	aa4xAct = new QAction(tr("&4x"), this);
	aa4xAct->setCheckable(true);
	if(this->aa_level == 4) aa4xAct->setChecked(true);
	//connect(aa4xAct, SIGNAL(triggered()), my_widget, SLOT(OnAntiAlias4x()));
	connect(aa4xAct, SIGNAL(triggered()), this, SLOT(OnAntiAlias4x()));
	aaMenu->addAction(aa4xAct);

	aa8xAct = new QAction(tr("&8x"), this);
	aa8xAct->setCheckable(true);
	if(this->aa_level == 8) aa8xAct->setChecked(true);
	//connect(aa8xAct, SIGNAL(triggered()), my_widget, SLOT(OnAntiAlias8x()));
	connect(aa8xAct, SIGNAL(triggered()), this, SLOT(OnAntiAlias8x()));
	aaMenu->addAction(aa8xAct);

	aaMenu->addSeparator();

	aaOffAct = new QAction(tr("&Enabled"), this);
	aaOffAct->setCheckable(true);
	if(this->aa_level == 0) 
		aaOffAct->setChecked(false);
	else 
		aaOffAct->setChecked(true);
	//connect(aaOffAct, SIGNAL(triggered()), this, SLOT(OnAntiAliasOff()));
	connect(aaOffAct, SIGNAL(triggered()), my_widget, SLOT(OnAntiAliasOff()));
	aaMenu->addAction(aaOffAct);

	QActionGroup* aa_group = new QActionGroup(aaMenu);
		aa_group->addAction(aa0xAct);
		aa_group->addAction(aa2xAct);
		aa_group->addAction(aa4xAct);
		aa_group->addAction(aa8xAct);


	clearAct = new QAction(tr("&Clear"), this);
	connect(clearAct, SIGNAL(triggered()), my_widget, SLOT(OnClear()));
	file->addAction(clearAct);

	file->addSeparator();

	clientAct = new QAction(tr("&Client"), this);

	file->addSeparator();

	printAct = new QAction(*printIcon, tr("&Print"), this);
	connect(printAct, SIGNAL(triggered()), my_widget, SLOT(OnPrint()));
	file->addAction(printAct);

	saveAct = new QAction(tr("&Save"), this);
	connect(saveAct, SIGNAL(triggered()), my_widget, SLOT(OnSaveFileAs()));
	file->addAction(saveAct);

	file->addSeparator();

	closeAct = new QAction(tr("&Close"), this);
	connect(closeAct, SIGNAL(triggered()), this, SLOT(myclose()));
	file->addAction(closeAct);

	file->addSeparator();

	exitAct = new QAction(tr("&Exit"), this);
	connect(exitAct, SIGNAL(triggered()), myparent, SLOT(quit()));
	file->addAction(exitAct);



	//Manipulate menu
	QMenu *manipulate = this->menuBar()->addMenu(tr("&Manipulate"));

	orbitAct = new QAction(*orbitIcon, tr("&Orbit"), this);
	orbitAct->setCheckable(true);
	connect(orbitAct, SIGNAL(triggered()), my_widget, SLOT(OnOrbit()));
	manipulate->addAction(orbitAct);

	zoomAct = new QAction(*zoomIcon, tr("&Zoom"), this);
	zoomAct->setCheckable(true);
	connect(zoomAct, SIGNAL(triggered()), my_widget, SLOT(OnZoom()));
	manipulate->addAction(zoomAct);

	panAct = new QAction(*panIcon, tr("&Pan"), this);
	panAct->setCheckable(true);
	connect(panAct, SIGNAL(triggered()), my_widget, SLOT(OnPan()));
	manipulate->addAction(panAct);

	zWindowAct = new QAction(*zoomwindowIcon, tr("&Zoom to Window"), this);
	zWindowAct->setCheckable(true);
	connect(zWindowAct, SIGNAL(triggered()), my_widget, SLOT(OnZoomToWindow()));
	manipulate->addAction(zWindowAct);

	manipulate->addSeparator();

	zExtentsAct = new QAction(*zoomextentsIcon, tr("&Zoom to Extents"), this);
	zExtentsAct->setCheckable(true);
	connect(zExtentsAct, SIGNAL(triggered()), my_widget, SLOT(OnZoomToExtents()));
	manipulate->addAction(zExtentsAct);

	smoothTransAct = new QAction(tr("&Smooth Transition"), this);
	smoothTransAct->setCheckable(true);
	smoothTransAct->setChecked(true);
	connect(smoothTransAct, SIGNAL(triggered()), my_widget, SLOT(OnSmoothTransition()));
	manipulate->addAction(smoothTransAct);

	walkAct = new QAction(*walkIcon, tr("&Walk"), this);
	walkAct->setCheckable(true);
	connect(walkAct, SIGNAL(triggered()), my_widget, SLOT(OnWalk()));

	selectAct = new QAction(*selectIcon, tr("&Select by Single Click"), this);
	selectAct->setCheckable(true);
	connect(selectAct, SIGNAL(triggered()), my_widget, SLOT(OnApertureSelect()));

	selectWindowAct = new QAction(*selectwindowIcon, tr("&Select by Window"), this);
	selectWindowAct->setCheckable(true);
	connect(selectWindowAct, SIGNAL(triggered()), my_widget, SLOT(OnWindowSelect()));

	nurbsCurveAct = new QAction(*nurbsIcon, tr("&Create NURBS Curve"), this);
	nurbsCurveAct->setCheckable(true);
	connect(nurbsCurveAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateNurbsCurve()));

	sphereAct = new QAction(*sphereIcon, tr("&Create Sphere"), this);
	sphereAct->setCheckable(true);
	connect(sphereAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateSphere()));

	coneAct = new QAction(*coneIcon, tr("&Create Cone"), this);
	coneAct->setCheckable(true);
	connect(coneAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateCone()));

	cylinderAct = new QAction(*cylinderIcon, tr("&Create Cylinder"), this);
	cylinderAct->setCheckable(true);
	connect(cylinderAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateCylinder()));

	nurb3dAct = new QAction(*nurb3dIcon, tr("&Create NURBS Patch"), this);
	nurb3dAct->setCheckable(true);
	connect(nurb3dAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateNurbs3D()));

	translateAct = new QAction(*translateIcon, tr("&Translate"), this);
	translateAct->setCheckable(true);
	connect(translateAct, SIGNAL(triggered()), my_widget, SLOT(OnTranslate()));

	rotateAct = new QAction(*rotateIcon, tr("&Rotate"), this);
	rotateAct->setCheckable(true);
	connect(rotateAct, SIGNAL(triggered()), my_widget, SLOT(OnRotate()));

	frontAct = new QAction(*frontIcon, tr("&Front View"), this);
	connect(frontAct, SIGNAL(triggered()), my_widget, SLOT(OnFrontView()));

	backAct = new QAction(*backIcon, tr("&Back View"), this);
	connect(backAct, SIGNAL(triggered()), my_widget, SLOT(OnBackView()));

	topAct = new QAction(*topIcon, tr("&Top View"), this);
	connect(topAct, SIGNAL(triggered()), my_widget, SLOT(OnTopView()));

	bottomAct = new QAction(*bottomIcon, tr("&Bottom View"), this);
	connect(bottomAct, SIGNAL(triggered()), my_widget, SLOT(OnBottomView()));

	leftAct = new QAction(*leftIcon, tr("&Left-side View"), this);
	connect(leftAct, SIGNAL(triggered()), my_widget, SLOT(OnLeftView()));

	rightAct = new QAction(*rightIcon, tr("&Right-side View"), this);
	connect(rightAct, SIGNAL(triggered()), my_widget, SLOT(OnRightView()));

	isoAct = new QAction(*isoIcon, tr("&Isometric View"), this);
	connect(isoAct, SIGNAL(triggered()), my_widget, SLOT(OnIsometricView()));

	freehandAct = new QAction(*freehandmkpIcon, tr("&Free Hand Markup"), this);
	freehandAct->setCheckable(true);
	connect(freehandAct, SIGNAL(triggered()), my_widget, SLOT(OnFreehandMarkup()));

	rectangleAct = new QAction(*rectanglemkpIcon, tr("&Rectangular Markup"), this);
	rectangleAct->setCheckable(true);
	connect(rectangleAct, SIGNAL(triggered()), my_widget, SLOT(OnRectangleMarkup()));

	circleAct = new QAction(*circlemkpIcon, tr("&Circular Markup"), this);
	circleAct->setCheckable(true);
	connect(circleAct, SIGNAL(triggered()), my_widget, SLOT(OnCircleMarkup()));

	textAct = new QAction(*textmkpIcon, tr("&Text Markup"), this);
	textAct->setCheckable(true);
	connect(textAct, SIGNAL(triggered()), my_widget, SLOT(OnTextMarkup()));

	savemkp1Act = new QAction(*savemkp1Icon, tr("&Save Markup Data 1"), this);
	savemkp1Act->setCheckable(true);
	connect(savemkp1Act, SIGNAL(triggered(bool)), my_widget, SLOT(OnSaveMarkup1(bool)));

	savemkp2Act = new QAction(*savemkp2Icon, tr("&Save Markup Data 2"), this);
	savemkp2Act->setCheckable(true);
	connect(savemkp2Act, SIGNAL(triggered(bool)), my_widget, SLOT(OnSaveMarkup2(bool)));
	
	annotateAct = new QAction(*annotateIcon, tr("&Annotate"), this);
	annotateAct->setCheckable(true);
	connect(annotateAct, SIGNAL(triggered()), my_widget, SLOT(OnAnnotateModel()));

	distanceAct = new QAction(*distanceIcon, tr("&Measure Distance"), this);
	distanceAct->setCheckable(true);
	connect(distanceAct, SIGNAL(triggered()), my_widget, SLOT(OnMeasureDistance()));

	cuttingAct = new QAction(*cuttingplaneIcon, tr("&Cutting Plane"), this);
	cuttingAct->setCheckable(true);
	connect(cuttingAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateCuttingPlane()));

	twoSidedAct = new QAction(tr("&Two Sided Section"), this);
	twoSidedAct->setCheckable(true);
	connect(twoSidedAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateTwosideSection()));

	threeSidedAct = new QAction(tr("&Three Sided Section"), this);
	threeSidedAct->setCheckable(true);
	connect(threeSidedAct, SIGNAL(triggered()), my_widget, SLOT(OnCreateThreesideSection()));

	queryAct = new QAction(*queryIcon, tr("&Query"), this);
	queryAct->setCheckable(true);
	connect(queryAct, SIGNAL(triggered()), my_widget, SLOT(OnQuery()));

	animateAct = new QAction(*animateIcon, tr("&Animate Scene"), this);
	connect(animateAct, SIGNAL(triggered()), my_widget, SLOT(OnAnimate()));

	aniBackAct = new QAction(*ani_backIcon, tr("&Animate Back"), this);
	connect(aniBackAct, SIGNAL(triggered()), my_widget, SLOT(OnAnimateBack()));

	aniPlayPauseAct = new QAction(*ani_play_pauseIcon, tr("&Animate Play/Pause"), this);
	connect(aniPlayPauseAct, SIGNAL(triggered()), my_widget, SLOT(OnAnimatePlayPause()));

	aniStopAct = new QAction(*ani_stopIcon, tr("&Animate Stop"), this);
	connect(aniStopAct, SIGNAL(triggered()), my_widget, SLOT(OnAnimateStop()));

	//clashDetectAct = new QAction(QIcon("images/clashdetect.png"), tr("&Clash Detection"), this);
	clashDetectAct = new QAction(*clashDetectIcon, tr("&Clash Detection"), this);
	clashDetectAct->setCheckable(true);
	connect(clashDetectAct, SIGNAL(triggered()), my_widget, SLOT(OnObjectClash()));

	homeAct = new QAction(*homeIcon, tr("&Home"), this);
	connect(homeAct, SIGNAL(triggered()), my_widget, SLOT(OnHome()));

	undoAct = new QAction(*undoIcon, tr("&Undo"), this);
	connect(undoAct, SIGNAL(triggered()), my_widget, SLOT(OnUndo()));

	redoAct = new QAction(*redoIcon, tr("&Redo"), this);
	connect(redoAct, SIGNAL(triggered()), my_widget, SLOT(OnRedo()));

	//Create Menu
	QMenu *create = this->menuBar()->addMenu(tr("&Create"));
	create->addAction(sphereAct);
	create->addAction(cylinderAct);
	create->addAction(coneAct);
	create->addAction(cuttingAct);
	create->addAction(twoSidedAct);
	create->addAction(threeSidedAct);
	create->addAction(nurbsCurveAct);
	create->addAction(nurb3dAct);
	create->addSeparator();
	create->addAction(annotateAct);

	// Selection Menu
	QMenu* selection_menu = this->menuBar()->addMenu(tr("&Selection"));
	selection_menu->addAction(selectAct);
	selection_menu->addAction(selectWindowAct);
	selectAct->setCheckable(true);
	selectWindowAct->setCheckable(true);
	//QActionGroup* selection = new QActionGroup(selection_menu);
	//selection->addAction(selectAct);
	//selection->addAction(selectWindowAct);
	selection_menu->addSeparator();
	selection_menu->addAction( "Delete Selection",  my_widget, SLOT(OnDeleteSelectionList()) );
	selection_menu->addSeparator();
	selection_menu->addAction(translateAct);
	selection_menu->addAction(rotateAct);
	//selection_menu->addAction(QIcon("images/clashdetect.png"), "Clash Detection", my_widget, SLOT(OnObjectClash()) );
	selection_menu->addAction(clashDetectAct);

	// Tool menu
	QMenu *tools_menu = this->menuBar()->addMenu(tr("&Tools"));
	tools_menu->addAction( "Test Performance", my_widget, SLOT(OnAnimate()) );
	tools_menu->addAction("Query Model", my_widget, SLOT(OnQuery()));
	tools_menu->addAction("Measure Distance", my_widget, SLOT(OnMeasureDistance()));
	tools_menu->addAction( "Segment Browser",  my_widget, SLOT(OnSegmentBrowser()) );
	
	//View menu
	QMenu *view_menu = this->menuBar()->addMenu(tr("&View"));
	QActionGroup* projection = new QActionGroup(view_menu);
	orthographic_m = view_menu->addAction( "Orthographic",  my_widget, SLOT(OnOrthographic()) );
		orthographic_m->setCheckable(true);
	perspective_m = view_menu->addAction( "Perspective",  my_widget, SLOT(OnPerspective()) );
		perspective_m->setCheckable(true);
	projection->addAction(orthographic_m);
	projection->addAction(perspective_m);
	perspective_m->setChecked(true);
	
	view_menu->addSeparator();
		QMenu* hand_menu = view_menu->addMenu(tr("&Polygon Handedness"));
		right_hand = hand_menu->addAction( "Right",  my_widget, SLOT(OnViewPolygonHandednessRight()) );
		left_hand = hand_menu->addAction( "Left",  my_widget, SLOT(OnViewPolygonHandednessLeft()) );
		none_hand = hand_menu->addAction( "None",  my_widget, SLOT(OnViewPolygonHandednessNone()) );
		right_hand->setCheckable(true);
		left_hand->setCheckable(true);
		none_hand->setCheckable(true);
		QActionGroup* handedness = new QActionGroup(hand_menu);
		handedness->addAction(right_hand);
		handedness->addAction(left_hand);
		handedness->addAction(none_hand);
		left_hand->setChecked(true);
		

		QMenu* csys_menu = view_menu->addMenu(tr("&Coordinate System"));
		csys_right_m = csys_menu->addAction( "Right Handed",  my_widget, SLOT(OnViewCoordinateSystemRightHanded()) );
		csys_left_m = csys_menu->addAction( "Left Handed",  my_widget, SLOT(OnViewCoordinateSystemLeftHanded()) );
		csys_right_m->setCheckable(true);
		csys_left_m->setCheckable(true);
		QActionGroup* coord = new QActionGroup(csys_menu);
		coord->addAction(csys_right_m);
		coord->addAction(csys_left_m);
		csys_right_m->setChecked(true);
		

		QMenu* bpl_menu = view_menu->addMenu(tr("&Backplane Culling"));
		bpl_on_m = bpl_menu->addAction( "On",  my_widget, SLOT(OnViewBackplaneCullingOn()) );
		bpl_off_m = bpl_menu->addAction( "Off",  my_widget, SLOT(OnViewBackplaneCullingOff()) );
		bpl_on_m->setCheckable(true);
		bpl_off_m->setCheckable(true);
		
		QActionGroup* culling = new QActionGroup(bpl_menu);
		culling->addAction(bpl_on_m);
		culling->addAction(bpl_off_m);
		bpl_off_m->setChecked(true);
		

	display_m = view_menu->addAction( "Display Lists", my_widget, SLOT(OnViewDisplayLists()) );
	display_m->setCheckable(true);
	display_m->setChecked(true);

	segdisplaylists_m = view_menu->addAction( "Segment Level Display Lists", this, SLOT(OnSegLevDisplayLists()));
		segdisplaylists_m->setCheckable(true);
		segdisplaylists_m->setChecked(false);

	static_m = view_menu->addAction( "Static Model", this, SLOT(OnStaticModel()));
		static_m->setCheckable(true);
		static_m->setChecked(false);

	view_menu->addSeparator();
	/*
	QAction* lod_m = view_menu->addAction( "Level of Detail",  my_widget, SLOT(OnViewLevelOfDetail()) );
		lod_m->setCheckable(true);
	view_menu->addAction( "Level of Detail Options",  my_widget, SLOT(OnViewLevelOfDetailOptions()) );
	*/
		QMenu* lod_menu = view_menu->addMenu(tr("&LOD Level"));
		gen_lods = lod_menu->addAction( "Enable LODs", my_widget, SLOT(OnViewLevelOfDetail()));
		lod_zro = lod_menu->addAction( "Level 0", this, SLOT(OnViewLevelOfDetailZro()));
		lod_one = lod_menu->addAction( "Level 1", this, SLOT(OnViewLevelOfDetailOne()));
		lod_two = lod_menu->addAction( "Level 2", this, SLOT(OnViewLevelOfDetailTwo()));
		gen_lods->setCheckable(true);
		lod_zro->setCheckable(true);
		lod_one->setCheckable(true);
		lod_two->setCheckable(true);
		QActionGroup* levels = new QActionGroup(lod_menu);
		levels->addAction(lod_zro);
		levels->addAction(lod_one);
		levels->addAction(lod_two);

	view_menu->addSeparator();
	view_menu->addAction( "Frame Rate Options",  my_widget, SLOT(OnViewFrameRateOptions()) );

	view_menu->addSeparator();
	view_menu->addAction( "Compute Sample Data",  my_widget, SLOT(OnGenerateSampleData()) );
	view_menu->addSeparator();
	view_menu->addAction( "Set Window Color", my_widget, SLOT(OnWindowBackgroundColor()) );
	
	
	// Create help
	QMenu *help = this->menuBar()->addMenu(tr("&Help")); 
    help->addAction( "About", this , SLOT(about()) );

	QMenu *debug = this->menuBar()->addMenu(tr("&DEBUG"));
	debug->addAction( "Extra Slot 1", this, SLOT(OnExtraSlot1()));
	debug->addAction( "Extra Slot 2", this, SLOT(OnExtraSlot2()));
	debug->addAction( "Extra Slot 3", this, SLOT(OnExtraSlot3()));
	debug->addAction( "Extra Slot 4", this, SLOT(OnExtraSlot4()));
	debug->addAction( "Extra Slot 5", this, SLOT(OnExtraSlot5()));

    CreateToolbars();
	SetToolbarState(true);

	#ifdef OSX_SYSTEM
		/* without this stupid workaround, the toolbar buttons don't get
		 * drawn correctly.  OSX needs a resize after the show() for now */
		this->resize(1000,625);
		this->show();
		this->resize(999,625);
	#else
		this->resize(1000,625);
		this->show();
	#endif
	
}

void HQApplication::SetUpMenus(){
	//this SLOT is available so you can re-set which menus are checked when a 
	//new file gets loaded into an existing window.  But...  should the menus
	//get reset?  Depends on whether the actual HOOPS settings are getting reset as well.
	//Should all settings/menus stay the same when a new model gets loaded?  
	//Or would it be better just to call the init function again?
	//I think this function is correct for now.
	bpl_off_m->setChecked(true);
	csys_right_m->setChecked(true);
	left_hand->setChecked(true);
	perspective_m->setChecked(true);
}

void HQApplication::OnViewLevelOfDetailZro(){
	char cval[MVO_BUFFER_SIZE];
	
	sprintf(cval, "lodo =(clamp = 0)");

    HC_Open_Segment_By_Key(my_widget->GetHoopsView()->GetSceneKey());//m_SceneKey);
	 	HC_Set_Rendering_Options( cval );
    HC_Close_Segment();
}

void HQApplication::OnViewLevelOfDetailOne(){
	char cval[MVO_BUFFER_SIZE];
	
	sprintf(cval, "lodo =(clamp = 1)");

    HC_Open_Segment_By_Key(my_widget->GetHoopsView()->GetSceneKey());//m_SceneKey);
	 	HC_Set_Rendering_Options( cval );
    HC_Close_Segment();
}

void HQApplication::OnViewLevelOfDetailTwo(){
	char cval[MVO_BUFFER_SIZE];
	
	sprintf(cval, "lodo =(clamp = 2)");

    HC_Open_Segment_By_Key(my_widget->GetHoopsView()->GetSceneKey());//m_SceneKey);
	 	HC_Set_Rendering_Options( cval );
    HC_Close_Segment();
}

void HQApplication::SetToolbarState(bool is_on)
{



	if(is_on) {

#if 0
		page_button->setEnabled(true);
		open_button->setEnabled(true);
		print_button->setEnabled(true);
		zoom_extents_button->setEnabled(true);
		zoom_window_button->setEnabled(true);
		orbit_button->setEnabled(true);
		zoom_button->setEnabled(true);
		walk_button->setEnabled(true);
		pan_button->setEnabled(true);
#endif
		selectAct->setEnabled(true);
		selectWindowAct->setEnabled(true);
		sphereAct->setEnabled(true);
		coneAct->setEnabled(true);
		cylinderAct->setEnabled(true);
		nurb3dAct->setEnabled(true);
		nurbsCurveAct->setEnabled(true);
		translateAct->setEnabled(true);
		rotateAct->setEnabled(true);
		frontAct->setEnabled(true);
		backAct->setEnabled(true);
		topAct->setEnabled(true);
		bottomAct->setEnabled(true);
		leftAct->setEnabled(true);
		rightAct->setEnabled(true);
		isoAct->setEnabled(true);
		freehandAct->setEnabled(true);
		rectangleAct->setEnabled(true);
		circleAct->setEnabled(true);
		textAct->setEnabled(true);
		savemkp1Act->setEnabled(true);
		savemkp2Act->setEnabled(true);
		annotateAct->setEnabled(true);
		distanceAct->setEnabled(true);
		cuttingAct->setEnabled(true);
		queryAct->setEnabled(true); 
		animateAct->setEnabled(true);
		aniBackAct->setEnabled(true);
		aniPlayPauseAct->setEnabled(true);
		aniStopAct->setEnabled(true);
		homeAct->setEnabled(true);
		undoAct->setEnabled(true);
		redoAct->setEnabled(true);
#ifdef PARASOLID
		subtract_button->setEnabled(true);
		union_button->setEnabled(true);
		intersect_button->setEnabled(true);
#endif
	}else{

#if 0
		page_button->setEnabled(false);
		open_button->setEnabled(false);
		print_button->setEnabled(false);
		zoom_extents_button->setEnabled(false);
		zoom_window_button->setEnabled(false);
		orbit_button->setEnabled(false);
		zoom_button->setEnabled(false);
		walk_button->setEnabled(false);
		pan_button->setEnabled(false);
#endif
		selectAct->setEnabled(false);
		selectWindowAct->setEnabled(false);
		sphereAct->setEnabled(false);
		coneAct->setEnabled(false);
		cylinderAct->setEnabled(false);
		nurb3dAct->setEnabled(false);
		nurbsCurveAct->setEnabled(false);
		translateAct->setEnabled(false);
		rotateAct->setEnabled(false);
		frontAct->setEnabled(false);
		backAct->setEnabled(false);
		topAct->setEnabled(false);
		bottomAct->setEnabled(false);
		leftAct->setEnabled(false);
		rightAct->setEnabled(false);
		isoAct->setEnabled(false);
		freehandAct->setEnabled(false);
		rectangleAct->setEnabled(false);
		circleAct->setEnabled(false);
		textAct->setEnabled(false);
		savemkp1Act->setEnabled(false);
		savemkp2Act->setEnabled(false);
		annotateAct->setEnabled(false);
		distanceAct->setEnabled(false);
		cuttingAct->setEnabled(false);
		queryAct->setEnabled(false); 
		animateAct->setEnabled(false);
		aniBackAct->setEnabled(false);
		aniPlayPauseAct->setEnabled(false);
		aniStopAct->setEnabled(false);
		homeAct->setEnabled(false);
		undoAct->setEnabled(false);
		redoAct->setEnabled(false);
#ifdef PARASOLID
		subtract_button->setEnabled(false);
		union_button->setEnabled(false);
		intersect_button->setEnabled(false);
#endif
	}
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

    walkIcon = new QPixmap( (const char**)walk_xpm );
	walkIcon->setMask( walkIcon->createHeuristicMask() );

    selectIcon = new QPixmap( (const char**)select_xpm );
	selectIcon->setMask( selectIcon->createHeuristicMask() );

    selectwindowIcon = new QPixmap( (const char**)selectwindow_xpm );
	selectwindowIcon->setMask( selectwindowIcon->createHeuristicMask() );

    sphereIcon = new QPixmap( (const char**)sphere_xpm );
	sphereIcon->setMask( sphereIcon->createHeuristicMask() );

    coneIcon = new QPixmap( (const char**)cone_xpm );
	coneIcon->setMask( coneIcon->createHeuristicMask() );

    cylinderIcon = new QPixmap( (const char**)cylinder_xpm );
	cylinderIcon->setMask( cylinderIcon->createHeuristicMask() );

    nurbsIcon = new QPixmap( (const char**)nurbs_xpm );
	nurbsIcon->setMask( nurbsIcon->createHeuristicMask() );

    nurb3dIcon = new QPixmap( (const char**)nurb3d_xpm );
	nurb3dIcon->setMask( nurb3dIcon->createHeuristicMask() );

    translateIcon = new QPixmap( (const char**)translate_xpm );
	translateIcon->setMask( translateIcon->createHeuristicMask() );

    rotateIcon = new QPixmap( (const char**)rotate_xpm );
	rotateIcon->setMask( rotateIcon->createHeuristicMask() );


    subtractIcon = new QPixmap( (const char**)subtract_xpm );
	subtractIcon->setMask( subtractIcon->createHeuristicMask() );

    unionIcon = new QPixmap( (const char**)union_xpm );
	unionIcon->setMask( unionIcon->createHeuristicMask() );

    intersectIcon = new QPixmap( (const char**)intersect_xpm );
	intersectIcon->setMask( intersectIcon->createHeuristicMask() );

    frontIcon= new QPixmap( (const char**)front_xpm );
	frontIcon->setMask( frontIcon->createHeuristicMask() );

    backIcon = new QPixmap( (const char**)back_xpm );
	backIcon->setMask( backIcon->createHeuristicMask() ); 

    topIcon = new QPixmap( (const char**)top_xpm );
	topIcon->setMask( topIcon->createHeuristicMask() );

    bottomIcon = new QPixmap( (const char**)bottom_xpm );
	bottomIcon->setMask( bottomIcon->createHeuristicMask() );

    leftIcon = new QPixmap( (const char**)left_xpm );
	leftIcon->setMask( leftIcon->createHeuristicMask() );

    rightIcon = new QPixmap( (const char**)right_xpm );
	rightIcon->setMask( rightIcon->createHeuristicMask() );

    isoIcon = new QPixmap( (const char**)isometric_xpm );
	isoIcon->setMask( isoIcon->createHeuristicMask() );

    
    freehandmkpIcon= new QPixmap( (const char**)freehandmkp_xpm );
	freehandmkpIcon->setMask( freehandmkpIcon->createHeuristicMask() );

    rectanglemkpIcon = new QPixmap( (const char**)rectanglemkp_xpm );
	rectanglemkpIcon->setMask( rectanglemkpIcon->createHeuristicMask() ); 

    circlemkpIcon = new QPixmap( (const char**)circlemkp_xpm );
	circlemkpIcon->setMask( circlemkpIcon->createHeuristicMask() );

    textmkpIcon = new QPixmap( (const char**)textmkp_xpm );
	textmkpIcon->setMask( textmkpIcon->createHeuristicMask() );

    savemkp1Icon = new QPixmap( (const char**)savemkp1_xpm );
	savemkp1Icon->setMask( savemkp1Icon->createHeuristicMask() );

    savemkp2Icon = new QPixmap( (const char**)savemkp2_xpm );
	savemkp2Icon->setMask( savemkp2Icon->createHeuristicMask() );


    annotateIcon= new QPixmap( (const char**)annotate_xpm );
	annotateIcon->setMask( annotateIcon->createHeuristicMask() );

    distanceIcon= new QPixmap( (const char**)distance_xpm );
	distanceIcon->setMask( distanceIcon->createHeuristicMask() );

    cuttingplaneIcon= new QPixmap( (const char**)cuttingplane_xpm );
	cuttingplaneIcon->setMask( cuttingplaneIcon->createHeuristicMask() );

    queryIcon= new QPixmap( (const char**)query_xpm );
	queryIcon->setMask( queryIcon->createHeuristicMask() );

    animateIcon= new QPixmap( (const char**)animate_xpm );
	animateIcon->setMask( animateIcon->createHeuristicMask() );

    ani_backIcon= new QPixmap( (const char**)ani_back_xpm );
	ani_backIcon->setMask( ani_backIcon->createHeuristicMask() );

    ani_play_pauseIcon= new QPixmap( (const char**)ani_play_pause_xpm );
	ani_play_pauseIcon->setMask( ani_play_pauseIcon->createHeuristicMask() );

    ani_stopIcon= new QPixmap( (const char**)ani_stop_xpm );
	ani_stopIcon->setMask( ani_stopIcon->createHeuristicMask() );

    clashDetectIcon= new QPixmap( (const char**)clashdetect);
	clashDetectIcon->setMask( clashDetectIcon->createHeuristicMask() );

	homeIcon = new QPixmap( (const char**)home_xpm);
	homeIcon->setMask( homeIcon->createHeuristicMask() );

	undoIcon = new QPixmap( (const char**)undo_xpm);
	undoIcon->setMask( undoIcon->createHeuristicMask() );

	redoIcon = new QPixmap( (const char**)redo_xpm);
	redoIcon->setMask( redoIcon->createHeuristicMask() );
}


void HQApplication::CreateToolbars()
{
	QActionGroup* buttons = new QActionGroup(this);
	buttons->addAction(newAct);
	buttons->addAction(openAct);
	buttons->addAction(printAct);
	buttons->addAction(zExtentsAct);
	buttons->addAction(orbitAct);
	buttons->addAction(panAct);
	buttons->addAction(zoomAct);
	buttons->addAction(walkAct);
	buttons->addAction(zWindowAct);
	buttons->addAction(selectAct);
	buttons->addAction(selectWindowAct);
	buttons->addAction(nurbsCurveAct);
	buttons->addAction(sphereAct);
	buttons->addAction(coneAct);
	buttons->addAction(cylinderAct);
	buttons->addAction(nurb3dAct);
	buttons->addAction(translateAct);
	buttons->addAction(rotateAct);
	buttons->addAction(clashDetectAct);
	buttons->addAction(frontAct);
	buttons->addAction(backAct);
	buttons->addAction(topAct);
	buttons->addAction(bottomAct);
	buttons->addAction(leftAct);
	buttons->addAction(rightAct);
	buttons->addAction(isoAct);
	buttons->addAction(freehandAct);
	buttons->addAction(rectangleAct);
	buttons->addAction(circleAct);
	buttons->addAction(textAct);
	buttons->addAction(annotateAct);
	buttons->addAction(distanceAct);
	buttons->addAction(queryAct);
	buttons->addAction(animateAct);
	buttons->addAction(aniBackAct);
	buttons->addAction(aniPlayPauseAct);
	buttons->addAction(aniStopAct);
	buttons->addAction(homeAct);
	buttons->addAction(undoAct);
	buttons->addAction(redoAct);





	
	QSize s(16, 16);
	/* Create a tool bar*/
	standard_toolbar = new QToolBar( "ops", this);
	standard_toolbar->setIconSize(s);
	standard_toolbar->addAction(newAct);
	standard_toolbar->addAction(openAct);
	standard_toolbar->addAction(printAct);
	standard_toolbar->addSeparator();
	standard_toolbar->addAction(zExtentsAct);
	//standard_toolbar->addSeparator();
	standard_toolbar->addAction(orbitAct);
	standard_toolbar->addAction(panAct);
	standard_toolbar->addAction(zoomAct);
	standard_toolbar->addAction(walkAct);
	standard_toolbar->addAction(zWindowAct);
	standard_toolbar->addSeparator();
	standard_toolbar->addAction(selectAct);
	standard_toolbar->addAction(selectWindowAct);
	standard_toolbar->addSeparator();
	standard_toolbar->addAction(nurbsCurveAct);
	standard_toolbar->addSeparator();
	standard_toolbar->addAction(sphereAct);
	standard_toolbar->addAction(coneAct);
	standard_toolbar->addAction(cylinderAct);
	standard_toolbar->addAction(nurb3dAct);
	standard_toolbar->addSeparator();
	standard_toolbar->addAction(translateAct);
	standard_toolbar->addAction(rotateAct);
	standard_toolbar->addAction(clashDetectAct);
	this->addToolBar(standard_toolbar);

	this->addToolBarBreak();

	std_views_toolbar = new QToolBar( "ops_std_views", this);
	std_views_toolbar->setIconSize(s);
	std_views_toolbar->addAction(frontAct);
	std_views_toolbar->addAction(backAct);
	std_views_toolbar->addAction(topAct);
	std_views_toolbar->addAction(bottomAct);
	std_views_toolbar->addAction(leftAct);
	std_views_toolbar->addAction(rightAct);
	std_views_toolbar->addAction(isoAct);
	this->addToolBar(std_views_toolbar);

	markup_txt_toolbar = new QToolBar( "ops_markup_txt", this);
	markup_txt_toolbar->setIconSize(s);
	markup_txt_toolbar->addAction(freehandAct);
	markup_txt_toolbar->addAction(rectangleAct);
	markup_txt_toolbar->addAction(circleAct);
	markup_txt_toolbar->addAction(textAct);
	markup_txt_toolbar->addAction(savemkp1Act);
	markup_txt_toolbar->addAction(savemkp2Act);
	this->addToolBar(markup_txt_toolbar);
	
	tools_toolbar = new QToolBar( "ops_tools", this);
	tools_toolbar->setIconSize(s);
	tools_toolbar->addAction(annotateAct);
	tools_toolbar->addAction(distanceAct);
	tools_toolbar->addAction(cuttingAct);
	tools_toolbar->addAction(queryAct);
	tools_toolbar->addAction(animateAct);
	tools_toolbar->addSeparator();
	tools_toolbar->addAction(aniBackAct);
	tools_toolbar->addAction(aniPlayPauseAct);
	tools_toolbar->addAction(aniStopAct);
	this->addToolBar(tools_toolbar);

	undo_toolbar = new QToolBar( "ops_undo", this);
	undo_toolbar->setIconSize(s);
	undo_toolbar->addAction(homeAct);
	undo_toolbar->addAction(undoAct);
	undo_toolbar->addAction(redoAct);
	this->addToolBar(undo_toolbar);

	//This little workaround prevents the toolbars from writing over the 
	//menus, but at 640x400 the toolbars get pretty compressed...  it might
	//make more sense to the first time user to have it as 2 rows of toolbars
	//using the addToolBarBreak() call from above, where everything is visible at once
	/*
	this->resize(900,500);
	this->show();
	this->resize(640,400);
	*/
}

void HQApplication::OnFullscreen(bool on){
	//The checked property is already set by the time we hit
	//this slot, so the following logic is correct.
	if(on){
		standard_toolbar->hide();
		std_views_toolbar->hide();
		markup_txt_toolbar->hide();
		tools_toolbar->hide();
		undo_toolbar->hide();
		this->menuBar()->hide();
		this->showFullScreen();
	}
	else{
		standard_toolbar->show();
		std_views_toolbar->show();
		markup_txt_toolbar->show();
		tools_toolbar->show();
		undo_toolbar->show();
		this->menuBar()->show();
		this->showNormal();
	}
}

void HQApplication::OnStaticModel(){
	if(my_widget->GetHoopsModel()->GetStaticModel()){
		static_m->setChecked(false);
		my_widget->GetHoopsModel()->SetStaticModel(false);
	}
	else{
		static_m->setChecked(true);
		my_widget->GetHoopsModel()->SetStaticModel(true);
	}
}

void HQApplication::OnSegLevDisplayLists(){
	if(my_widget->GetHoopsView()->GetDisplayListType() == DisplayListGeometry){
		my_widget->GetHoopsView()->SetDisplayListType(DisplayListSegment);
		segdisplaylists_m->setChecked(true);
	}
	else {
		my_widget->GetHoopsView()->SetDisplayListType(DisplayListGeometry);
		segdisplaylists_m->setChecked(false);
	}
	if(display_m->isChecked())
			my_widget->GetHoopsView()->SetDisplayListMode(true);
}
