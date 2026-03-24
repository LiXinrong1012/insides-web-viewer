#include "main_ui.h"

#include <QtGui>

#include <QtnOfficeDefines.h>
#include <QtnStyleHelpers.h>
#include <QtnRibbonStyle.h>
#include <QtnOfficePopupColorButton.h>
#include <QtnRibbonQuickAccessBar.h>
#include <QtnRibbonStatusBar.h>
#ifdef CUSTOMIZE_V4_WORK
#include <QtnRibbonCustomizationManager.h>
#endif // CUSTOMIZE_V4_WORK


#include "precore/itemlist.h"
#include "precore/precore_data.h"
#include "precore/TypeDataManager.h"
#include "precore/UAPI.h"
#include "precore/ResultDocument.h"
#include "precore/projectselector.h"

#include "base/Console.h"
#include "Base/multiviewwidget.h"
#include "Base/ViewLayoutManager.h"
#include "Base/CMDialogFactory.h"
#include "Base/activeviewobject.h"
#include "Base/AppConfiguration.h"
#include "Base/parametersmanagerwidget.h"
#include "Base/ParametersManager.h"
#include "base/ApplicationInfo.h"
#include "base/MultiProgressOperator.h"
#include "base/AppConfiguration.h"
#include "base/TreeItemPropertyManager.h"
#include "base/animationcontrolwidget.h"
#include "base/AnimationControler.h"
#include "base/ViewFactory.h"
#include "base/view.h"
#include "base/doublelineedit.h"


#include "coresps/ShapeManager.h"
#include "coresps/HoopsShapeManager.h"

#include "prept/insuiplugin.h"


#include "include/IExchangeFile.h"
#include "include/IExchangeView.h"


#include "oploadtdythread.h"
#include "optestthread.h"
#include "oploadtdyresthread.h"
#include "opsavemodelthread.h"
#include "oploadmodelthread.h"


using namespace Qtitan;
using namespace INSIDES;

main_ui::main_ui(QWidget *parent, Qt::WFlags flags,
	const QString& tdyFileName,const QString& serverName)
	: RibbonWindow(parent)
	,_importTDY(NULL)
	,_hotRibbonPage(NULL)
	,_localServer(NULL)
{

	if(!serverName.isEmpty())
	{
		Console().Log("Is initializing server: %s",serverName.toStdString().c_str());
		_localServer=new LocalServer(this);
		_localServer->runServer(serverName);
		_localServer->setMessageListener(this);
	}

	setOptions(Qtitan::RibbonStyle::Office2010Blue);
	ribbonBar()->setLogoPixmap(Qt::AlignRight,QPixmap(":/resources/menu/a000x48x48.png"));

	Base::MultiProgressOperator::setMainWindow(this);
	MulProgressDialogMapper::instance();

	initDefaultParameters();
	QString settingFileName=AppConfiguration::instance()->startupDirectory()+"settings/parameters.xml";
	AppConfiguration::instance()->getParametersManager()->loadFromFile(settingFileName);

	AppConfiguration::instance()->getParametersManager()->attach(this);


	init_precore_module();

	_document=myDocument();

	ui.setupUi(this);
	createAction();
	createMenuFile();
	createRibbon();
	createQuickAccessBar();
	createStatusBar();

	loadViewPlugins();

	setWindowTitle("INSIDES Viewer");
	ribbonBar()->setFrameThemeEnabled();


	MultiViewWidget* multiView=ui.centralWidget;
	ViewLayoutManager *layout=multiView->layoutManager();
	View* hoopsView=(View*)ViewFactory::instance()->Produce("Render View");
	if(hoopsView){
		this->installEventFilter(hoopsView);
		layout->AssignView(0,hoopsView);
		multiView->reload();
	}



	register_all_buildin_shapes();	
	load3rdPartyShapes();

	init_preui();


	TypeDataManager::instance();

	loadPlugins();
	_document->createDefault();



	loadModelTreePlugin();


	readSetting();

	if(tdyFileName.isEmpty())
		_document->reset();


	ApplicationInfo appInfo;
	appInfo.setBuildTime(__DATE__,__TIME__);
	Base::Console().Message("%s",appInfo.getAppInfo().toStdString().c_str());

	connect(ActiveViewObject::instance(),SIGNAL(activeViewChanged(View*)),
		this,SLOT(onActiveViewChanged(View*)));
	

	if(!tdyFileName.isEmpty()){
		_startupFileName=tdyFileName;
		 //QTimer::singleShot(500, this, SLOT(loadStartupFileName()));
		this->onImportTDY(tdyFileName);
	}
}

main_ui::~main_ui()
{
	AppConfiguration::instance()->getParametersManager()->disattach(this);
}

void main_ui::closeEvent(QCloseEvent* event)
{
	MultiViewWidget* multiView=ui.centralWidget;
	multiView->destroyAllViews();
	ViewLayoutManager *layout=multiView->layoutManager();
	layout->Reset();
	multiView->reload();

	writeSetting();
}


void main_ui::createActions()
{
	/*
	ui.tbTHU->setWindowTitle("THU Solver");
	ui.tbAnimationBar->setWindowTitle("Animation");
	// File toolbar
	ui.tbFile->setWindowTitle("File");
	QAction* ac=new QAction("&New",this);
	ac->setIcon(QIcon(":/resources/menu/new.png"));
	ac->setShortcut(QKeySequence("Ctrl+N"));
	connect(ac,SIGNAL(triggered()),this,SLOT(onNew()));
	ui.menu_File->addAction(ac);
	ui.tbFile->addAction(ac);


	// Import menu
	QMenu* _menuImport=new QMenu("&Import",this);
	ui.menu_File->addMenu(_menuImport);

	ac=new QAction("&THU solver (.tdy)",this);
	ac->setIcon(QIcon(":/resources/menu/open.png"));
	connect(ac,SIGNAL(triggered()),this,SLOT(onImportTDY()));
	_menuImport->addAction(ac);
	ui.tbTHU->addAction(ac);

	ac=new QAction("&Import Data",this);
	ac->setIcon(QIcon(":/resources/hoops/attributeicon.xpm"));
	connect(ac,SIGNAL(triggered()),this,SLOT(onLoadSimpleData()));
	_menuImport->addAction(ac);
	ui.tbTHU->addAction(ac);

	ac=new QAction("&Import Eigen",this);
	ac->setIcon(QIcon(":/resources/hoops/attributeicon.xpm"));
	connect(ac,SIGNAL(triggered()),this,SLOT(onLoadSimpleEigen()));
	_menuImport->addAction(ac);
	ui.tbTHU->addAction(ac);

	// Export menu
	_menuExport=new QMenu("&Export",this);
	ui.menu_File->addMenu(_menuExport);

	ac=new QAction("&THU solver (.tdy)",this);
	ac->setIcon(QIcon(":/resources/menu/save.png"));
	connect(ac,SIGNAL(triggered()),this,SLOT(onExportTDY()));
	_menuExport->addAction(ac);
	ui.tbTHU->addAction(ac);

#ifdef _DEBUG
	ac=new QAction("&Open default",this);
	ac->setIcon(QIcon(":/resources/menu/open.png"));
	connect(ac,SIGNAL(triggered()),this,SLOT(onImportTDY_Debug()));
	ui.tbTHU->addAction(ac);
#endif

	ac=ui.menu_File->addAction("Load state",this,SLOT(onLoadState()));
	ac->setIcon(QIcon(":/resources/menu/open.png"));
	ui.tbFile->addAction(ac);

	ac=ui.menu_File->addAction("Save state",this,SLOT(onSaveState()));
	ac->setIcon(QIcon(":/resources/menu/save.png"));
	ui.tbFile->addAction(ac);
	
	ac=ui.menu_File->addAction("Fresh",this,SLOT(onFreshModel()));
	ac->setIcon(QIcon(":/resources/menu/open.png"));
	ac->setShortcut(QKeySequence("F5"));
	ui.tbFile->addAction(ac);

	ac=new QAction("&Quit",this);
	ac->setIcon(QIcon(":/resources/menu/quit.png"));
	ac->setShortcut(QKeySequence("Ctrl+X"));
	connect(ac,SIGNAL(triggered()),this,SLOT(close()));
	ui.menu_File->addAction(ac);
	ui.tbFile->addAction(ac);

	
	// undo framework
	undoAction = _document->getUndoStack()->createUndoAction(this, tr("&Undo"));
	undoAction->setShortcuts(QKeySequence::Undo);
	undoAction->setIcon(QIcon(":/resources/menu/undo.png"));

	redoAction = _document->getUndoStack()->createRedoAction(this, tr("&Redo"));
	redoAction->setShortcuts(QKeySequence::Redo);
	redoAction->setIcon(QIcon(":/resources/menu/redo.png"));

	ui.tbFile->addSeparator();
	ui.tbFile->addAction(undoAction);
	ui.tbFile->addAction(redoAction);

	ac=new QAction("Edit",this);
	ac->setIcon(QIcon(":/resources/menu/gointo.png"));
	connect(ac,SIGNAL(triggered()),this->ui.modelTreeWidget->getTreeView(),SLOT(onGoInto()));
	ui.tbFile->addSeparator();
	ui.tbFile->addAction(ac);

	ac=new QAction("Out",this);
	ac->setIcon(QIcon(":/resources/menu/goout.png"));
	connect(ac,SIGNAL(triggered()),this->ui.modelTreeWidget->getTreeView(),SLOT(onGoOut()));
	ui.tbFile->addAction(ac);



	*/
	//CoutourDisplaySelectorWidget* contourWidget=new CoutourDisplaySelectorWidget(this);
	//ui.tbCreateBasic->addWidget(contourWidget);
}






void main_ui::onSave()
{
	QString fileName="D:/a.xml";
//#ifndef _DEBUG
	fileName = QFileDialog::getSaveFileName( this, "caption", ".", "xml filenames(*.xml)" ); 
//#endif

	if(!fileName.isEmpty())
	{
		bool bSaveItem=true;
		if(myResultDocument()->getResults()){
			const ParameterItem* saveItem=Base::AppConfiguration::instance()->getParametersManager()->get("SaveResult","System");
			const ParameterItem* checkSaveResult=Base::AppConfiguration::instance()->getParametersManager()->get("CheckSaveResult","System");
			bool bCheckSaveResult=true;
			if(checkSaveResult)
				bCheckSaveResult=checkSaveResult->getVariant().toBool();
			if(saveItem)
				bSaveItem=saveItem->getVariant().toBool();

			if(bCheckSaveResult){
				QMessageBox msgBox;
				msgBox.setText("You are saving the models and results...");
				msgBox.setInformativeText("Do you want to save your results?");
				msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No);
				msgBox.setDefaultButton(QMessageBox::Save);
				int ret = msgBox.exec();
				if(ret!=QMessageBox::Save)
					bSaveItem=false;
			}
		}

		OPSaveModelThread* workerThread=new OPSaveModelThread(this);
		workerThread->setFileName(fileName);
		workerThread->setSaveResult(bSaveItem);
		workerThread->start();


	}
}

void main_ui::onOpen()
{
	QString fileName="D:/a.xml";
	QString currDir=AppConfiguration::instance()->workingDirectory();
	if(!currDir.isEmpty())
		QDir::setCurrent(currDir);
//#ifndef _DEBUG
	fileName = QFileDialog::getOpenFileName( this, "caption", ".", "xml filenames(*.xml)" ); 
//#endif

	if(!fileName.isEmpty())
	{
		MultiDocuments::instance()->getActiveDocument()->load(fileName,true);
	}
	onReset();
	onFinishedLoadingRes();

}

void main_ui::readSetting()
{
	QSettings settings("TDYPre", "TDYPre");
	QPoint pos = settings.value("pos", QPoint(100, 100)).toPoint();
	QSize size = settings.value("size", QSize(600, 600)).toSize();
	//move(pos);
	//resize(size);

	settings.beginGroup("state");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());

	//ui.modelTreeWidget->restoreGeometry(settings.value("modelTreeState").toByteArray());

	QString currDir=settings.value("currentDir").toString();
	AppConfiguration::instance()->setWorkingDirectory(currDir);
	QDir::setCurrent(settings.value("currentDir").toString());
	settings.endGroup();

	TreeItemPropertyManager::instance()->loadState();
}

void main_ui::writeSetting()
{
	QSettings settings("TDYPre", "TDYPre");
	settings.setValue("pos", pos());
	settings.setValue("size", size());

	settings.beginGroup("state");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	//settings.setValue("modelTreeState",ui.modelTreeWidget->saveGeometry());

	//settings.setValue("currentDir",QDir::current().absolutePath());
	settings.setValue("currentDir",AppConfiguration::instance()->workingDirectory());
	settings.endGroup();

	QString settingFileName=AppConfiguration::instance()->startupDirectory()+"settings/parameters.xml";
	AppConfiguration::instance()->getParametersManager()->saveToFile(settingFileName);



	TreeItemPropertyManager::instance()->saveState();
}

void main_ui::onExportTDY()
{
	//_hoopsView->testMaterialSelector();
	//ExportTDY exportTDY;
	//exportTDY.doJob("D:/tdy.txt");
}

void main_ui::onImportTDY()
{
	QString fileName;
	{
		QSettings settings(qApp->applicationDirPath()+"/settings/insides-viewer.ini",QSettings::IniFormat);
		settings.beginGroup("DIRECTORIES");
		QString openTDYDir=settings.value("CURRENT_TDY_FILE","").toString();
		fileName=QFileDialog::getOpenFileName(openTDYDir,
			tr("INSIDES Model File (*.ins *.tdy)"),this);
		if(!fileName.isEmpty())
			settings.setValue("CURRENT_TDY_FILE",fileName);
		settings.endGroup();
	}

	onImportTDY(fileName);
}


void main_ui::onFreshModel()
{
	QString fileName=AppConfiguration::instance()->projectFullName();
	if(fileName.isEmpty())
		return;

	if(!_importTDY){
		Console().Error(QObject::tr("No THU-Solver import plugin."));
		return;
	}

	if(fileName.isEmpty())
		return;

	// clear existing results
	myResultDocument()->clear();

	MultiDocuments::instance()->notifyDisableUIUpdating(true);
	//ui.modelTreeWidget->setUpdatesEnabled(false);
	myDocument()->setEnableSignal(false);
	myDocument()->createDefault();


	//onCloseAllWindows();

	ActiveViewObject::instance()->setModelStatus(ActiveViewObject::MODEL_STATUS_MODEL);
	_animationControlWidget->updateUi();

	QFileInfo file(fileName);
	QString abDir=file.absoluteDir().absolutePath();
	QString name=file.fileName();

	AppConfiguration::instance()->setWorkingDirectory(abDir+"/");
	AppConfiguration::instance()->setProjectFullName(name);
	setWindowTitle(QString("INSIDES Viewer (%1)").arg(file.absoluteFilePath()));

	OPLoadTDYThread* workerThread=new OPLoadTDYThread(this);
	workerThread->setFileName(file.fileName());
	connect(workerThread,SIGNAL(jobFinished()),this,SLOT(onReset()));
	workerThread->start();
}


void main_ui::loadStartupFileName()
{
	if(!_startupFileName.isEmpty())
		onImportTDY(_startupFileName);
}

void main_ui::onImportTDY( const QString& fileName )
{
	if(!_importTDY){
		Console().Error(QObject::tr("No THU-Solver import plugin."));
		return;
	}

	if(fileName.isEmpty())
		return;

		
	ActiveViewObject::instance()->setModelStatus(ActiveViewObject::MODEL_STATUS_MODEL);

	// clear existing results
	myResultDocument()->clear();

	//ui.modelTreeWidget->setUpdatesEnabled(false);
	MultiDocuments::instance()->notifyDisableUIUpdating(true);
	myDocument()->setEnableSignal(false);
	myDocument()->createDefault();

	onCloseAllWindows();


	_animationControlWidget->updateUi();

	QFileInfo file(fileName);
	_tdyModelFile=file;
	QString abDir=file.absoluteDir().absolutePath();
	QString name=file.fileName();

	QDir::setCurrent(abDir);

	AppConfiguration::instance()->setWorkingDirectory(abDir+"/");
	AppConfiguration::instance()->setProjectFullName(name);
	setWindowTitle(QString("INSIDES Viewer (%1)").arg(file.absoluteFilePath()));

	OPLoadTDYThread* workerThread=new OPLoadTDYThread(this);
	workerThread->setFileName(file.fileName());
	connect(workerThread,SIGNAL(jobFinished()),this,SLOT(onReset()));
	workerThread->start();


}

void main_ui::onReset()
{
	Console().Log("Start onReset");
	myDocument()->setEnableSignal(true);
	myDocument()->reset();
	MultiDocuments::instance()->notifyDisableUIUpdating(false);
	Console().Log("Finished onReset");

	if(_localServer)
	{
		ViewerServerToClientMessage mes;
		mes.messageType=ViewerServerToClientMessage::IMPORTED_MODEL;
		_localServer->sendToClient(mes);
	}
}


void main_ui::onImportTDY_Debug()
{
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/mesh0509/main.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/PostTest/main.tdy";
	QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/constraints_yangcheng/main.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/mesh-output-aseembly20140520/main.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/ebeam_sample/ebeam.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/debug_res/main.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/xianshi/main.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/fenli/main.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/chelun/chelun.tdy";
	//QString fileName="c:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/amesh/main.tdy";

	onImportTDY(fileName);
}

void main_ui::onNew()
{
	onCloseAllWindows();
	ModelDocument* doc=myDocument();
	doc->createDefault();
}

void main_ui::onGoIn()
{
	MultiDocuments::instance()->getActiveDocument()->onGoInto();
}

void main_ui::onGoOut()
{
	MultiDocuments::instance()->getActiveDocument()->onGoOut();
}





void main_ui::onLoadSimpleData()
{
	myResultDocument()->setEmitMessage(false);

	OPLoadTDYResThread* loadTDYResThread=new OPLoadTDYResThread(this);
	connect(loadTDYResThread,SIGNAL(jobFinished()),
		this,SLOT(onFinishedLoadingRes()));
		
	ResultDocument* doc=myResultDocument();
	//doc->moveToThread(loadTDYResThread);
	loadTDYResThread->start();
}

void main_ui::onFinishedLoadingRes()
{
	myResultDocument()->setEmitMessage(true);
	myResultDocument()->notifyResultsLoaded(myResultDocument()->getResults());
	ActiveViewObject::instance()->animationControler()->setCurrentFrame(0);
	_animationControlWidget->updateUi();

	if(_localServer)
	{
		ViewerServerToClientMessage mes;
		mes.messageType=ViewerServerToClientMessage::IMPORTED_RESULT;
		_localServer->sendToClient(mes);
	}
}

void main_ui::loadPlugins()
{
	QDir pluginsDir(qApp->applicationDirPath());
//#if defined(Q_OS_WIN)
//	if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
//		pluginsDir.cdUp();
//#endif
	pluginsDir.cd("plugins");
	{
		QPluginLoader pluginLoader1(pluginsDir.absoluteFilePath("importtdy2.dll"));
		QObject *plugin1 = pluginLoader1.instance();
		if (plugin1) 
			_importTDY = qobject_cast<IExchangeFile2*>(plugin1);
		else
		{
			QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("importtdy.dll"));
			QObject *plugin = pluginLoader.instance();
			if (plugin){
				Console().Message("Old importtdy.dll used: %s",pluginLoader.errorString().toStdString().c_str());
				_importTDY = qobject_cast<IExchangeFile2*>(plugin);
			}
			else
				Console().Error("Load importtdy.dll failed: %s",pluginLoader.errorString().toStdString().c_str());
		}
	}
	//foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
	//	QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
	//	QObject *plugin = pluginLoader.instance();
	//	if (plugin) {
	//		IExchangeFile2* ex = qobject_cast<IExchangeFile2*>(plugin);
	//		if (ex){
	//			if(ex->getKeyname()=="TDY_DEMO"){
	//				Console().Message("Import import demo.");
	//			}
	//		}
	//	}
	//}

}

void main_ui::loadViewPlugins()
{
	QDir pluginsDir(qApp->applicationDirPath());

	pluginsDir.cd("plugins");
	{
		QString filter("prev*.dll");
		pluginsDir.setNameFilter(filter);
		foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
			QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
			QObject *plugin = pluginLoader.instance();
			if (plugin){
				IExchangeView* myView = qobject_cast<IExchangeView*>(plugin);
				myView->registerView();
				RibbonPage* page=myView->createRibbonPage(ribbonBar());
				if(page)
				{
					page->setVisible(false);
				}
			}
			else{
				Base::Console().Error("%s",pluginLoader.errorString().toLocal8Bit().constData());
			}
		}

	}
}

void main_ui::loadModelTreePlugin()
{
	QDir pluginsDir(qApp->applicationDirPath());

	{
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("prept.dll"));
		QObject *plugin = pluginLoader.instance();
			
		if (plugin){
			INSUIPlugin* uiPlugin=qobject_cast<INSUIPlugin*>(plugin);
			uiPlugin->initUI(this);
		}
	}
}

void main_ui::onConfiguration()
{
	static ParametersManagerWidget* form = NULL;
	if (!form) {
		form = new ParametersManagerWidget;
	}
	form->load(AppConfiguration::instance()->getParametersManager());
	form->show();
}

void main_ui::load3rdPartyShapes()
{
	typedef void (*F1) (ShapeManager*);
	typedef void (*F2) (void);

	QLibrary lib("spsIn.dll");
	lib.load();

	bool bloaded=lib.isLoaded();
	if(bloaded){
		F1 f1=(F1)lib.resolve("setShapeManager");
		if(f1)
			f1(HoopsShapeManager::instance());

		F2 f2=(F2)lib.resolve("importShapesCollection");
		if(f2)
			f2();
	}
}

void main_ui::onLoadSimpleEigen()
{
	//Base::ActiveViewObject::instance()->setIsEditingModel(false);
	ResultDocument* doc=myResultDocument();
	//doc->createDefaultResults();
	myResultDocument()->setEmitMessage(false);
	doc->loadTDYEigResults();
	myResultDocument()->setEmitMessage(true);
	myResultDocument()->notifyResultsLoaded(myResultDocument()->getResults());
	ActiveViewObject::instance()->animationControler()->setCurrentFrame(0);
	_animationControlWidget->updateUi();

}

void main_ui::onCloseAllWindows()
{
	MultiViewWidget* multiView=ui.centralWidget;
	multiView->destroyAllViews();
	ViewLayoutManager *layout=multiView->layoutManager();
	View* hoopsView=(View*)ViewFactory::instance()->Produce("Render View");
	layout->Reset();
	multiView->reload();
	layout->AssignView(0,hoopsView);
	multiView->reload();
}

void main_ui::initDefaultParameters()
{
	ParametersManager* paraManager=AppConfiguration::instance()->getParametersManager();
	ParametersGroup* mainPara=paraManager->addCollection("System");
	paraManager->setDefaultCollection(mainPara);
	ParameterItem item;


	item.setKeyword("SaveResult");
	item.setType(QVariant::Bool);
	item.setVariant(true);
	mainPara->set(item);

	item.setKeyword("CheckSaveResult");
	item.setVariant(false);
	mainPara->set(item);


}


void main_ui::onSaveState()
{
	QString fileName="main.layout";
	ActiveViewObject::instance()->currentViewLayoutManager()->SaveAllState(fileName);
}
void main_ui::onSaveStateAs()
{
	QString fileName = QFileDialog::getSaveFileName( this, tr("Save state as ..."), 
		".", "INSIDES layout files (*.layout)" ); 
	if(!fileName.isEmpty()){
		ActiveViewObject::instance()->currentViewLayoutManager()->SaveAllState(fileName);
	}
}

void main_ui::onLoadState()
{
	MultiViewWidget* multiView=ui.centralWidget;
	multiView->destroyAllViews();
	ViewLayoutManager *layout=multiView->layoutManager();
	layout->Reset();
	multiView->reload();

	QString fileName="main.layout";
	multiView->layoutManager()->LoadAllState(fileName);
	multiView->reload();
}
void main_ui::onLoadStateFrom()
{
	QString fileName = QFileDialog::getOpenFileName( this, tr("Load state from ..."), 
		".", "INSIDES layout files (*.layout)" ); 
	if(!fileName.isEmpty()){
		MultiViewWidget* multiView=ui.centralWidget;
		multiView->destroyAllViews();
		ViewLayoutManager *layout=multiView->layoutManager();
		layout->Reset();
		multiView->reload();

		multiView->layoutManager()->LoadAllState(fileName);
		multiView->reload();
	}
}

void main_ui::createStatusBar()
{
	Qtitan::RibbonStatusBar* statusBar = new Qtitan::RibbonStatusBar();
	setStatusBar(statusBar);

	//statusBar->addAction(tr("Page 1 of 1"));
	//statusBar->addSeparator();
	//statusBar->addAction(tr("Words: 1"));
	//statusBar->addSeparator();
	//statusBar->addAction(tr("English (U.S.)"));
	//statusBar->addSeparator();
	//statusBar->addAction(tr("Track Changes: Off"));
	//statusBar->addSeparator();
	//statusBar->addAction(tr("Insert"));

	//RibbonStatusBarSwitchGroup* switchGroup = new RibbonStatusBarSwitchGroup;
	//QList<QAction*> actions;
	//actions << m_actionPrintLayout;
	//actions << m_actionFullScreen;
	//QAction* actionWebLayout = new QAction(QIcon(":/res/smallweblayout.png"), tr("Web Layout"), this);
	//actions << actionWebLayout;
	//QAction* actionOutLine = new QAction(QIcon(":/res/smalloutline.png"), tr("Outline"), this);
	//actions << actionOutLine;
	//QAction* actionDraft = new QAction(QIcon(":/res/smalldraft.png"), tr("Draft"), this);
	//actions << actionDraft;
	//switchGroup->addActions(actions);
	//statusBar->addPermanentWidget(switchGroup);

	QToolButton* m_zoomPercentage = new QToolButton(this);
	m_zoomPercentage->setText(tr("100%"));
	m_zoomPercentage->setToolTip(tr("Zoom level. Click to open the Zoom dialog box."));
	statusBar->addPermanentWidget(m_zoomPercentage);
	QFontMetrics mt(statusBar->font());
	int minimumWidth = mt.boundingRect(QString("0000%")).width();
	m_zoomPercentage->setMinimumWidth(minimumWidth);

	Qtitan::RibbonSliderPane* sliderPane = new Qtitan::RibbonSliderPane();
	sliderPane->setScrollButtons(true);
	sliderPane->setRange(0, 200); // range
	sliderPane->setMaximumWidth(130);
	sliderPane->setSingleStep(10);
	sliderPane->setSliderPosition(100);
	statusBar->addPermanentWidget(sliderPane, 1);
	connect(sliderPane, SIGNAL(valueChanged(int)), this, SLOT(zoomSliderScroll(int)));
}

void main_ui::createRibbon()
{
	if (Qtitan::RibbonPage* pageHome = ribbonBar()->addPage(tr("&Home")))
	{
		createGroupModel(*pageHome->addGroup(tr("&Model")));
		createGroupState(*pageHome->addGroup(tr("&State")));
		createGroupAnimation(*pageHome->addGroup(tr("&Animation")));
		createGroupView(*pageHome->addGroup(tr("&View")));
	}
	if (Qtitan::RibbonPage* pageHome = ribbonBar()->addPage(tr("&3&D")))
	{
		createGroupShowHide(*pageHome->addGroup(tr("&Show/Hide")));
		createGroupSize(*pageHome->addGroup(tr("&Size")));
	}
	if (Qtitan::RibbonPage* pageHome = ribbonBar()->addPage(tr("&Tools")))
	{
		createGroupSettings(*pageHome->addGroup(tr("&Settings")));
	}
}

void main_ui::createAction()
{
	QIcon iconModel;
	iconModel.addPixmap(QPixmap(":/resources/menu/a016x16x16.png"));
	iconModel.addPixmap(QPixmap(":/resources/menu/a016x32x32.png"));
	_actionFileNewTDY=new QAction("&Model",this);
	_actionFileNewTDY->setIcon(iconModel);
	connect(_actionFileNewTDY,SIGNAL(triggered()),this,SLOT(onImportTDY()));

	_actionFileNew=new QAction("&Open",this);
	_actionFileNew->setIcon(QIcon(":/resources/menu/open.png"));
	_actionFileNew->setShortcut(QKeySequence("Ctrl+O"));
	connect(_actionFileNew,SIGNAL(triggered()),this,SLOT(onOpen()));

	_actionFileSave=new QAction("&Save",this);
	_actionFileSave->setIcon(QIcon(":/resources/menu/save.png"));
	_actionFileSave->setShortcut(QKeySequence("Ctrl+S"));
	connect(_actionFileSave,SIGNAL(triggered()),this,SLOT(onSave()));

	QIcon iconFresh;
	iconFresh.addPixmap(QPixmap(":/resources/menu/a014x16x16.png"));
	iconFresh.addPixmap(QPixmap(":/resources/menu/a014x32x32.png"));
	_actionFileFreshTDY=new QAction("&Fresh",this);
	_actionFileFreshTDY->setIcon(iconFresh);
	_actionFileFreshTDY->setShortcut(Qt::Key_F5);
	connect(_actionFileFreshTDY,SIGNAL(triggered()),this,SLOT(onFreshModel()));

	_actionFileExit=new QAction("&Exit",this);
	_actionFileExit->setIcon(QIcon(":/resources/menu/quit.png"));
	_actionFileExit->setShortcut(QKeySequence("Ctrl+X"));
	connect(_actionFileExit,SIGNAL(triggered()),this,SLOT(close()));

	QIcon iconLoadResult;
	iconLoadResult.addPixmap(QPixmap(":/resources/menu/a025x16x16.png"));
	iconLoadResult.addPixmap(QPixmap(":/resources/menu/a025x32x32.png"));
	_actionLoadTDYResult=new QAction("&Result",this);
	_actionLoadTDYResult->setIcon(iconLoadResult);
	connect(_actionLoadTDYResult,SIGNAL(triggered()),this,SLOT(onLoadSimpleData()));

	QIcon iconLoadEigen;
	iconLoadEigen.addPixmap(QPixmap(":/resources/menu/a026x16x16.png"));
	iconLoadEigen.addPixmap(QPixmap(":/resources/menu/a026x32x32.png"));
	_actionLoadTDYEig=new QAction("&Eigen",this);
	_actionLoadTDYEig->setIcon(iconLoadEigen);
	connect(_actionLoadTDYEig,SIGNAL(triggered()),this,SLOT(onLoadSimpleEigen()));

	QIcon iconSaveLayout;
	iconSaveLayout.addPixmap(QPixmap(":/resources/menu/a019x16x16.png"));
	iconSaveLayout.addPixmap(QPixmap(":/resources/menu/a019x32x32.png"));
	_actionSaveLayout=new QAction("&Save",this);
	_actionSaveLayout->setIcon(iconSaveLayout);
	connect(_actionSaveLayout,SIGNAL(triggered()),this,SLOT(onSaveState()));

	QIcon iconSaveLayoutAs;
	iconSaveLayoutAs.addPixmap(QPixmap(":/resources/menu/a019x16x16.png"));
	iconSaveLayoutAs.addPixmap(QPixmap(":/resources/menu/a019x32x32.png"));
	_actionSaveLayoutAs=new QAction("&Save As ...",this);
	_actionSaveLayoutAs->setIcon(iconSaveLayoutAs);
	connect(_actionSaveLayoutAs,SIGNAL(triggered()),this,SLOT(onSaveStateAs()));

	QIcon iconLoadLayout;
	iconLoadLayout.addPixmap(QPixmap(":/resources/menu/a017x16x16.png"));
	iconLoadLayout.addPixmap(QPixmap(":/resources/menu/a017x32x32.png"));
	_actionLoadLayout=new QAction("&Load",this);
	_actionLoadLayout->setIcon(iconLoadLayout);
	connect(_actionLoadLayout,SIGNAL(triggered()),this,SLOT(onLoadState()));

	QIcon iconLoadLayoutFrom;
	iconLoadLayoutFrom.addPixmap(QPixmap(":/resources/menu/a017x16x16.png"));
	iconLoadLayoutFrom.addPixmap(QPixmap(":/resources/menu/a017x32x32.png"));
	_actionLoadLayoutFrom=new QAction("&Load from ...",this);
	_actionLoadLayoutFrom->setIcon(iconLoadLayoutFrom);
	connect(_actionLoadLayoutFrom,SIGNAL(triggered()),this,SLOT(onLoadStateFrom()));

	QIcon iconGointo;
	iconGointo.addPixmap(QPixmap(":/resources/menu/a023x16x16.png"));
	iconGointo.addPixmap(QPixmap(":/resources/menu/a023x32x32.png"));
	_actionGoInto=new QAction("&GoIn",this);
	_actionGoInto->setIcon(iconGointo);
	connect(_actionGoInto,SIGNAL(triggered()),this,SLOT(onGoIn()));

	QIcon iconGoout;
	iconGoout.addPixmap(QPixmap(":/resources/menu/a024x16x16.png"));
	iconGoout.addPixmap(QPixmap(":/resources/menu/a024x32x32.png"));
	_actionGoOut=new QAction("&GoOut",this);
	_actionGoOut->setIcon(iconGoout);
	connect(_actionGoOut,SIGNAL(triggered()),this,SLOT(onGoOut()));


	QIcon iconParametersSetting;
	iconParametersSetting.addPixmap(QPixmap(":/resources/newmenu/h016a.png"));
	iconParametersSetting.addPixmap(QPixmap(":/resources/newmenu/h016b.png"));
	_actionEditParameters=new QAction("&Parameter",this);
	_actionEditParameters->setIcon(iconParametersSetting);
	connect(_actionEditParameters,SIGNAL(triggered()),this,SLOT(onConfiguration()));

	_actionResetModel=new QAction("&Reset",this);
	_actionResetModel->setIcon(iconParametersSetting);
	connect(_actionResetModel,SIGNAL(triggered()),this,SLOT(onReset()));

	QIcon iconFullScreen;
	iconFullScreen.addPixmap(QPixmap(":/resources/menu/a001x32x32.png"));
	iconFullScreen.addPixmap(QPixmap(":/resources/menu/a001x16x16.png"));
	_actionViewFull=new QAction("&Full",this);
	_actionViewFull->setIcon(iconFullScreen);
	_actionViewFull->setShortcut(QKeySequence("F11"));
	_actionViewFull->setCheckable(true);
	_actionViewFull->setChecked(false);
	connect(_actionViewFull,SIGNAL(triggered(bool)),this,SLOT(onViewFull(bool)));

	QIcon iconCentralLayout;
	iconCentralLayout.addPixmap(QPixmap(":/resources/menu/a002x32x32.png"));
	iconCentralLayout.addPixmap(QPixmap(":/resources/menu/a002x16x16.png"));
	_actionViewNone=new QAction("&Central",this);
	_actionViewNone->setIcon(iconCentralLayout);
	_actionViewNone->setShortcut(QKeySequence("F2"));
	_actionViewNone->setCheckable(true);
	connect(_actionViewNone,SIGNAL(triggered()),this,SLOT(onViewNone()));

	QIcon iconDraftLayout;
	iconDraftLayout.addPixmap(QPixmap(":/resources/menu/a003x32x32.png"));
	iconDraftLayout.addPixmap(QPixmap(":/resources/menu/a003x16x16.png"));
	_actionViewModel=new QAction("&Draft",this);
	_actionViewModel->setIcon(iconDraftLayout);
	_actionViewModel->setCheckable(true);
	_actionViewModel->setShortcut(QKeySequence("F3"));
	connect(_actionViewModel,SIGNAL(triggered()),this,SLOT(onViewModelTree()));

	QIcon iconAllLayout;
	iconAllLayout.addPixmap(QPixmap(":/resources/menu/a004x32x32.png"));
	iconAllLayout.addPixmap(QPixmap(":/resources/menu/a004x16x16.png"));
	_actionViewAll=new QAction("&All",this);
	_actionViewAll->setIcon(iconAllLayout);
	_actionViewAll->setCheckable(true);
	_actionViewAll->setChecked(true);
	_actionViewAll->setShortcut(QKeySequence("F4"));
	connect(_actionViewAll,SIGNAL(triggered()),this,SLOT(onViewViewAll()));
}

void main_ui::createMenuFile()
{
	//QIcon iconLogo;
	//iconLogo.addPixmap(QPixmap(":/res/file.png"));
	//iconLogo.addPixmap(QPixmap(":/res/qtitanlogo32x32.png"));
	//if(QAction* actionFile = ribbonBar()->addSystemButton(iconLogo, tr("&File"))) 
	if(QAction* actionFile = ribbonBar()->addSystemButton(tr("&File"))) 
	{
		actionFile->setToolTip(tr("Click here to see everything you can do with your document"));
		actionFile->setIcon(QIcon(":/resources/menu/a000x48x48.png"));
		Qtitan::RibbonSystemPopupBar* popupBar = qobject_cast<Qtitan::RibbonSystemPopupBar*>(actionFile->menu());

		popupBar->addAction(_actionFileNewTDY);
		popupBar->addAction(_actionFileFreshTDY);
		popupBar->addAction(_actionLoadTDYResult);
		popupBar->addAction(_actionLoadTDYEig);

		popupBar->addAction(_actionSaveLayoutAs);
		popupBar->addAction(_actionLoadLayoutFrom);

		popupBar->addAction(_actionFileExit);
		/*
		popupBar->addAction(m_actionFileNew);
		popupBar->addAction(m_actionOpenFile);
		popupBar->addAction(m_actionSaveFile);

		QAction* actionSaveAsFile = popupBar->addAction(QIcon(":/res/largeSaveAsFile.png"), tr("Save &As..."));
		actionSaveAsFile->setPriority(QAction::LowPriority);
		actionSaveAsFile->setToolTip(tr("Save As"));
		actionSaveAsFile->setStatusTip(tr("Save the active document with a new name"));
		connect(actionSaveAsFile, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

		popupBar->addSeparator();

#ifndef QT_NO_PRINTER
		QAction* actionPagePrint = new QAction(m_actionPrint->icon(), m_actionPrint->text(), this);
		popupBar->addAction(actionPagePrint);
		if (RibbonPageSystemPopup* pageSystemPopup = popupBar->addPageSystemPopup(tr("Preview and print the document"), actionPagePrint, true))
		{
			connect(actionPagePrint, SIGNAL(triggered()), m_actionPrint, SIGNAL(triggered()));
			pageSystemPopup->setMinimumWidth(296);
			pageSystemPopup->addAction(m_actionPrint);
			pageSystemPopup->addAction(m_actionPrintSetup);
			pageSystemPopup->addAction(m_actionPrintPreview);
		}
#endif
		QAction* actionPrepare = popupBar->addAction(QIcon(":/res/largePrepare.png"), tr("Pr&epare"));
		popupBar->addAction(actionPrepare);

		QAction* actionSend = popupBar->addAction(QIcon(":/res/largeSend.png"), tr("Sen&d"));
		popupBar->addAction(actionSend);
		if (RibbonPageSystemPopup* pageSystemPopup = popupBar->addPageSystemPopup(tr("Preview and print the document"), actionSend, false))
		{
			pageSystemPopup->setMinimumWidth(296);
			QAction* actionMail = pageSystemPopup->addAction(QIcon(":/res/largeMail.png"), tr("E-Mail"));
			actionMail->setToolTip(tr("Send the active document by e-mail"));
			pageSystemPopup->addAction(actionMail);

			QAction* actionIntenetFax = pageSystemPopup->addAction(QIcon(":/res/largeInternetfix.png"), tr("Intenet Fax"));
			actionIntenetFax->setToolTip(tr("Use an Internet fax service to fax the document"));
			pageSystemPopup->addAction(actionIntenetFax);
		}

		popupBar->addSeparator();
		QAction* actionClose = popupBar->addAction(QIcon(":/res/largeClose.png"), tr("&Close"));
		actionClose->setShortcut(tr("Ctrl+C"));
		actionClose->setStatusTip(tr("Exit"));
		actionClose->setEnabled(false);

		QAction* actionExit =  popupBar->addPopupBarAction(tr("Exit Sample"));
		connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

		QAction* actionOption = popupBar->addPopupBarAction(tr("Option"));
		actionOption->setEnabled(false);
		*/

		if (RibbonPageSystemRecentFileList* pageRecentFile = popupBar->addPageRecentFile(tr("Recent Documents")))
		{
			Q_UNUSED(pageRecentFile);
		}
	}
}

void main_ui::createQuickAccessBar()
{
	if (Qtitan::RibbonQuickAccessBar* quickAccessBar = ribbonBar()->quickAccessBar())
	{
		QAction* action = quickAccessBar->actionCustomizeButton();
		action->setToolTip(tr("Customize Quick Access Bar"));

		AnimationControlWidget* animationWidget=AnimationControlWidget::instance();

		QList<QAction*> animtionActions;
		animtionActions<<animationWidget->getActionStart()
			<<animationWidget->getActionPause()
			<<animationWidget->getActionStop()
			<<animationWidget->getActionPrevious()
			<<animationWidget->getActionNext();

		foreach(QAction* ac,animtionActions)
		{
			quickAccessBar->addAction(ac);
			quickAccessBar->setActionVisible(ac, true);
		}


		ribbonBar()->showQuickAccess(true);
	}
}

void main_ui::createGroupModel(Qtitan::RibbonGroup& page)
{
	page.addAction(_actionFileNewTDY,Qt::ToolButtonTextUnderIcon);
	page.addAction(_actionLoadTDYResult,Qt::ToolButtonTextUnderIcon);
	page.addAction(_actionLoadTDYEig,Qt::ToolButtonTextUnderIcon);
	page.addSeparator();
	page.addAction(_actionGoInto,Qt::ToolButtonTextUnderIcon);
	page.addAction(_actionGoOut,Qt::ToolButtonTextUnderIcon);
}

void main_ui::createGroupState(Qtitan::RibbonGroup& page)
{
	page.addAction(_actionFileFreshTDY,Qt::ToolButtonTextUnderIcon);

	QMenu* saveState=new QMenu(this);
	saveState->addAction(_actionSaveLayout);
	saveState->addAction(_actionSaveLayoutAs);
	page.addAction(_actionSaveLayout,Qt::ToolButtonTextUnderIcon,saveState);

	QMenu* loadState=new QMenu(this);
	loadState->addAction(_actionLoadLayout);
	loadState->addAction(_actionLoadLayoutFrom);
	page.addAction(_actionLoadLayout,Qt::ToolButtonTextUnderIcon,loadState);

}

void main_ui::createGroupShowHideOneItem(Qtitan::RibbonGroup& page,QCheckBox** checkBox,const QString& name,
	const char* slotName,const QString& paraName)
{
	*checkBox = new QCheckBox(name);
	QCheckBox* box=*checkBox;
	box->setToolTip(name);
	connect(box,SIGNAL(stateChanged(int)),this,slotName);
	const ParameterItem* paraItem=AppConfiguration::instance()->getParametersManager()->get(paraName,"Display");
	if(paraItem)
		box->setChecked(paraItem->getVariant().toBool());
	page.addWidget(box);
}

void main_ui::createGroupShowHide(Qtitan::RibbonGroup& page)
{
	createGroupShowHideOneItem(page,&_cbShowConstraint,
		tr("Constraint"),
		SLOT(showConstraintStateChanged(int)),
		"Show constraint");

	createGroupShowHideOneItem(page,&_cbShowMassCenter,
		tr("Mass Center"),
		SLOT(showMassCenterStateChanged(int)),
		"Show mass center");

	createGroupShowHideOneItem(page,&_cbShowInitial,
		tr("Initial"),
		SLOT(showInitialStateChanged(int)),
		"Show initial");

	createGroupShowHideOneItem(page,&_cbShowFEMMarker,
		tr("FEM Marker"),
		SLOT(showFEMMarkerStateChanged(int)),
		"Show FEM marker");

	createGroupShowHideOneItem(page,&_cbShowIMarker,
		tr("I Marker"),
		SLOT(showIMarkerStateChanged(int)),
		"ShowIMarker");
	createGroupShowHideOneItem(page,&_cbShowJMarker,
		tr("J Marker"),
		SLOT(showJMarkerStateChanged(int)),
		"ShowJMarker");
}

void main_ui::createGroupAnimation( Qtitan::RibbonGroup& page )
{
	AnimationControlWidget* w=new AnimationControlWidget(this);
	page.addWidget(w);
	_animationControlWidget=w;
}

void main_ui::createGroupSettings( Qtitan::RibbonGroup& page )
{
	page.addAction(_actionEditParameters,Qt::ToolButtonTextUnderIcon);
	page.addAction(_actionResetModel,Qt::ToolButtonTextUnderIcon);
}

void main_ui::createGroupView( Qtitan::RibbonGroup& page )
{
	page.addAction(_actionViewFull,Qt::ToolButtonTextUnderIcon);
	page.addAction(_actionViewNone,Qt::ToolButtonTextBesideIcon);
	page.addAction(_actionViewModel,Qt::ToolButtonTextBesideIcon);
	page.addAction(_actionViewAll,Qt::ToolButtonTextBesideIcon);
}

void main_ui::onViewFull(bool checked)
{
	if (checked)
	{
		_stateWindow = windowState();
		_actionViewFull->setChecked(true);
		ribbonBar()->setVisible(false);
		setWindowState(Qt::WindowFullScreen);
	}
	else
	{
		ribbonBar()->setVisible(true);
		setWindowState(_stateWindow);
		_actionViewFull->setChecked(false);
	}
}

void main_ui::onViewNone()
{
	//ui.dModelTree->setVisible(false);
	ui.dProperty->setVisible(false);
	ui.dMessage->setVisible(false);
	
	_actionViewNone->setChecked(true);
	_actionViewModel->setChecked(false);
	_actionViewAll->setChecked(false);
}

void main_ui::onViewModelTree()
{
	//ui.dModelTree->setVisible(true);
	ui.dProperty->setVisible(false);
	ui.dMessage->setVisible(false);
	_actionViewNone->setChecked(false);
	_actionViewModel->setChecked(true);
	_actionViewAll->setChecked(false);
}

void main_ui::onViewViewAll()
{
	//ui.dModelTree->setVisible(true);
	ui.dProperty->setVisible(true);
	ui.dMessage->setVisible(true);	
	_actionViewNone->setChecked(false);
	_actionViewModel->setChecked(false);
	_actionViewAll->setChecked(true);
}

void main_ui::keyPressEvent(QKeyEvent* event)
{
	Qtitan::RibbonMainWindow::keyPressEvent(event);
	if (event->key() == Qt::Key_Escape && _actionViewFull->isChecked())
		onViewFull(false);
}

static void _setShowHideParameterStatus(int b,const QString& keyword)
{
	if(b==Qt::Unchecked)
		AppConfiguration::instance()->getParametersManager()->setValue(keyword,false,"Display");
	else
		AppConfiguration::instance()->getParametersManager()->setValue(keyword,true,"Display");
}

void main_ui::showConstraintStateChanged( int b )
{
	_setShowHideParameterStatus(b,"Show constraint");
}

void main_ui::showFEMMarkerStateChanged( int b )
{
	_setShowHideParameterStatus(b,"Show FEM marker");
}

void main_ui::showMassCenterStateChanged( int b )
{
	_setShowHideParameterStatus(b,"Show mass center");
}

void main_ui::showInitialStateChanged( int b )
{
	_setShowHideParameterStatus(b,"Show initial");
}

void main_ui::showIMarkerStateChanged( int b )
{
	_setShowHideParameterStatus(b,"ShowIMarker");
}

void main_ui::showJMarkerStateChanged( int b )
{
	_setShowHideParameterStatus(b,"ShowJMarker");
}

bool main_ui::parameterChanged( Base::ParametersGroup* parameterManager, 
	const Base::ParameterItem* newParameter,const Base::ParameterItem* oldParameter )
{
	QString paraKeyName=newParameter->getKeyword();
	if(paraKeyName.compare("show constraint",Qt::CaseInsensitive)==0)
		_cbShowConstraint->setChecked(newParameter->getVariant().toBool());
	else if(paraKeyName.compare("show FEM marker",Qt::CaseInsensitive)==0)
		_cbShowFEMMarker->setChecked(newParameter->getVariant().toBool());
	else if(paraKeyName.compare("show initial",Qt::CaseInsensitive)==0)
		_cbShowInitial->setChecked(newParameter->getVariant().toBool());
	else if(paraKeyName.compare("show mass center",Qt::CaseInsensitive)==0)
		_cbShowMassCenter->setChecked(newParameter->getVariant().toBool());
	else if(paraKeyName.compare("showIMarker",Qt::CaseInsensitive)==0)
		_cbShowIMarker->setChecked(newParameter->getVariant().toBool());
	else if(paraKeyName.compare("showJMarker",Qt::CaseInsensitive)==0)
		_cbShowJMarker->setChecked(newParameter->getVariant().toBool());
	// size
	else if(paraKeyName.compare("Constraint size",Qt::CaseInsensitive)==0)
		_spinSizeContraint->setValue(newParameter->getVariant().toDouble());
	else if(paraKeyName.compare("Marker size",Qt::CaseInsensitive)==0)
		_spinSizeMarker->setValue(newParameter->getVariant().toDouble());
	else if(paraKeyName.compare("Force scale",Qt::CaseInsensitive)==0)
		_spinSizeForceScale->setValue(newParameter->getVariant().toDouble());
	else if(paraKeyName.compare("Mass center size",Qt::CaseInsensitive)==0)
		_spinSizeMassCenter->setValue(newParameter->getVariant().toDouble());
	else if(paraKeyName.compare("Shell edge size",Qt::CaseInsensitive)==0)
		_spinSizeShellEdge->setValue(newParameter->getVariant().toDouble());
	else if(paraKeyName.compare("Shell vertex size",Qt::CaseInsensitive)==0)
		_spinSizeShellVertex->setValue(newParameter->getVariant().toDouble());
	else if(paraKeyName.compare("Eigen display scale",Qt::CaseInsensitive)==0)
		_spinSizeEigenDisplayScale->setValue(newParameter->getVariant().toDouble());

	return false;
}

void main_ui::createGroupSizeOneItem(Qtitan::RibbonGroup& page,const QString& label,
	Base::DoubleLineEdit** spinBoxxx,const QString& paraName,
	const char* slotName)
{
	Base::DoubleLineEdit* spinBox = new DoubleLineEdit(this);
	*spinBoxxx=spinBox;
	spinBox->setToolTip(label);
	spinBox->setMinimumWidth(30);
	spinBox->setMaximumWidth(80);
	page.addWidget(QIcon(":/resources/menu/new.png"), label, true, spinBox);
	connect(spinBox,SIGNAL(valueChanged(double)),this,slotName);
	const ParameterItem* paraItem=AppConfiguration::instance()->getParametersManager()->get(paraName,"Display");
	if(paraItem)
		spinBox->setValue(paraItem->getVariant().toDouble());
}

void main_ui::createGroupSize( Qtitan::RibbonGroup& page )
{
	createGroupSizeOneItem(page,tr("Constraint:"),&_spinSizeContraint,"Constraint size",
		SLOT(spinSizeConstraintValueChanged(double)));
	createGroupSizeOneItem(page,tr("Marker:"),&_spinSizeMarker,"Marker size",
		SLOT(spinSizeMarkerValueChanged(double)));
	createGroupSizeOneItem(page,tr("Force Scale:"),&_spinSizeForceScale,"Force scale",
		SLOT(spinSizeForceScaleValueChanged(double)));
	createGroupSizeOneItem(page,tr("Mass Center:"),&_spinSizeMassCenter,"Mass center size",
		SLOT(spinSizeMassCenterValueChanged(double)));
	createGroupSizeOneItem(page,tr("Shell Edge:"),&_spinSizeShellEdge,"Shell edge size",
		SLOT(spinSizeShellEdgeValueChanged(double)));
	createGroupSizeOneItem(page,tr("Shell Vertex:"),&_spinSizeShellVertex,"Shell vertex size",
		SLOT(spinSizeShellVertexValueChanged(double)));
	createGroupSizeOneItem(page,tr("Eigen Scale:"),&_spinSizeEigenDisplayScale,"Eigen display scale",
		SLOT(spinSizeEigenDisplayScaleValueChanged(double)));
}

static void _setSpinSizeValue(double b,const QString& keyword)
{
	AppConfiguration::instance()->getParametersManager()->setValue(keyword,b,"Display");
}

void main_ui::spinSizeConstraintValueChanged( double v )
{
	_setSpinSizeValue(v,"Constraint size");
}

void main_ui::spinSizeMarkerValueChanged( double v )
{
	_setSpinSizeValue(v,"Marker size");
}

void main_ui::spinSizeForceScaleValueChanged( double v )
{
	_setSpinSizeValue(v,"Force scale");
}

void main_ui::spinSizeMassCenterValueChanged( double v )
{
	_setSpinSizeValue(v,"Mass center size");
}

void main_ui::spinSizeShellEdgeValueChanged( double v )
{
	_setSpinSizeValue(v,"Shell edge size");
}

void main_ui::spinSizeShellVertexValueChanged( double v )
{
	_setSpinSizeValue(v,"Shell vertex size");
}

void main_ui::spinSizeEigenDisplayScaleValueChanged( double v )
{
	_setSpinSizeValue(v,"Eigen display scale");
}

void main_ui::onActiveViewChanged( Base::View* view )
{
	if(_hotRibbonPage && (!view || (_hotRibbonPage!=view->getRibbonPage()) )){
		_hotRibbonPage->setVisible(false);
		_hotRibbonPage=NULL;
	}

	if(view && view->getRibbonPage())
	{
		view->updateRibbonPage();
		view->getRibbonPage()->setVisible(true);
		_hotRibbonPage=view->getRibbonPage();
	}
}

void main_ui::onMessageReceived( const ViewerSocketToServerMessage& mess )
{
	switch(mess.command)
	{
	case ViewerSocketToServerMessage::IMPORT_MODEL:
		{
			QString modelName=mess.informations["FILE_NAME"];
			onImportTDY(modelName);
		}
		break;
	case ViewerSocketToServerMessage::IMPORT_RESULT:
		//QString modelName=mess.informations["FILE_NAME"];
		Console().Message("Import_result");
		onLoadSimpleData();
		break;
		
	default:
		Console().Message("Unknown message: %d",mess.command);
		break;
	}
	/*
	else if(vec[0]=="highlight"){
		BaseItem* item=myDocument()->findItemWithoutFolder(vec[1]);
		if(item){
			BaseItemSelection tmp;
			tmp<<item;
			myProjectSelector()->notifySetSelection(tmp);
		}
	}
	*/
}







