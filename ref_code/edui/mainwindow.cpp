#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

#include "basecodeeditor.h"
#include "viewerwrapper.h"
#include "mdiarea.h"
#include "edparsesingleton.h"
#include "findresultwidget.h"
#include "findresultsmanager.h"

#include "testsolverdialog.h"

#include "edhelp/moduleplugin.h"

#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"
#include "edcore/filemanager.h"
#include "edcore/solveprocess.h"

#include "inssolver/socketmessage.h"

#include "edcompile/modelparser.h"
#include "edcompile/tdytypeinfomanager.h"
#include "edcompile/insmodelformator.h"

using namespace INSEditor;

class BuildObserver : public INSEditor::Parse::CompileInfoObserver
{
	virtual void error(const INSEditor::Parse::CompileInfoItem& ErrorItem){
		FileManager::instance()->notifyUpdateOutputInfo(ErrorItem);
	}
};

class UpdateTextEvent:public QEvent
{
public:
	enum IDD{ID_UPDATE_TEXT_EVENT=1001};
	UpdateTextEvent(QString s):QEvent(QEvent::Type(ID_UPDATE_TEXT_EVENT)),_str(s){};
	QString str()const {return _str;}
private:
	QString _str;
};

static void _setActionIcon(QAction* ac,const QString& name)
{
	QIcon iconBuild;
	iconBuild.addPixmap(QPixmap(QString(":/resources/menu/%1a.png").arg(name)));
	iconBuild.addPixmap(QPixmap(QString(":/resources/menu/%1b.png").arg(name)));
	ac->setIcon(iconBuild);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent)
	: RibbonWindow(parent)
	,_viewerWrapper(NULL)
	,_checkUpdateTimer(NULL)
	,_appName(tr("INSIDES Editor"))
{
	//INSProject::instance()->createDebug();

	ui = new Ui::MainWindow();
	ui->setupUi(this);

	loadHelpPlugin();
	loadParsePlugin();

	createFindResultWindow();

	_viewerWrapper=new ViewerWrapper(this);

	_mdiArea = new MdiArea(this,_viewerWrapper);
	_mdiArea->setEDParsePlugin(EDParseSingleton::instance()->getPlugin());
	_mdiArea->setLineWidth(3);
	_mdiArea->setFrameShape(QFrame::Panel);
	_mdiArea->setFrameShadow(QFrame::Sunken);

	_mdiArea->setViewMode(QMdiArea::TabbedView);
	_mdiArea->setTabsMovable(true);
	qApp->installEventFilter(this);

	_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	setCentralWidget(_mdiArea);

	setOptions(Qtitan::RibbonStyle::Office2010Blue);
	ribbonBar()->setLogoPixmap(Qt::AlignRight,QPixmap(":/resources/menu/h000c.png"));

	createActions();
	createMenuFile();
	createRibbon();
	createQuickAccessBar();
	createStatusBar();

	_mdiArea->createRibbonBar(ribbonBar()->getPage(0));

	setWindowTitle("INSIDES Editor");
	ribbonBar()->setFrameThemeEnabled();

	connect(Document::instance(),SIGNAL(solutionCreated(Solution*)),this,SLOT(onSolutionCreated(Solution*)));

	Base::Console().AttachObserver(this);
	readSetting();
	readSettingFromIni();

	QStringList argu=QCoreApplication::arguments();
	if(argu.size()>1)
	{
		QString fileName=argu[1];
		if(QFile::exists(fileName))
			openSolution(fileName);
	}

	if(Document::instance()->getProperties()->isAutoCheckUpdate)
	{
		QString host = "112.126.65.135";
		QString user = "ins_uploader";
		QString pass = "ins123456789";
		QString dir = "app/insides";
		_checkFtp = new QFtp;
		_checkFtp->connectToHost(host,21);
		_checkFtp->login(user,pass);
		_checkFtp->cd(dir);
		_checkFtp->get("bin/version.xml");

		_checkUpdateTimer = new QTimer(this);
		connect(_checkUpdateTimer,SIGNAL(timeout()),this,SLOT(onTimeout()));
		_checkUpdateTimer->start(1000);
	}

	connect(FileManager::instance(),SIGNAL(requestOpenFile(const QString& )),this,SLOT(respondOpeningFile(const QString&)));
	connect(FileManager::instance(),SIGNAL(requestSaveFile()),this,SLOT(save()));
	connect(FileManager::instance(),SIGNAL(requestBuildProject()),this,SLOT(buidProject()));
	connect(FileManager::instance(),SIGNAL(requestUpdateIcon()),this,SLOT(updateIcon()));

	connect(_mdiArea,SIGNAL(subWindowActivated ( QMdiSubWindow * )),this,SLOT(onSubWindowActivated ( QMdiSubWindow * )));
}

void MainWindow::createFindResultWindow()
{
	/// Find result widget 1
	QDockWidget* findResultDockWidget1 = new QDockWidget(this);
	findResultDockWidget1->setObjectName(QString::fromUtf8("FindResultDockWidget1"));
	addDockWidget(Qt::BottomDockWidgetArea, findResultDockWidget1);
	findResultDockWidget1->setWindowTitle(tr("Find Results 1"));

	FindResultWidget* findResultWidget1=new FindResultWidget(this);
	findResultDockWidget1->setWidget(findResultWidget1);
	FindResultsManager::instance()->setResultDock(0,findResultDockWidget1);
	FindResultsManager::instance()->setResultWidget(0,findResultWidget1);

	/// Find result widget 2
	QDockWidget* findResultDockWidget2 = new QDockWidget(this);
	findResultDockWidget2->setObjectName(QString::fromUtf8("FindResultDockWidget2"));
	addDockWidget(Qt::BottomDockWidgetArea, findResultDockWidget2);
	findResultDockWidget2->setWindowTitle(tr("Find Results 2"));

	FindResultWidget* findResultWidget2=new FindResultWidget(this);
	findResultDockWidget2->setWidget(findResultWidget2);
	FindResultsManager::instance()->setResultDock(1,findResultDockWidget2);
	FindResultsManager::instance()->setResultWidget(1,findResultWidget2);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	//检查是否有正在求解
	bool b = questionExitSolver();
	if(!b)
	{
		event->ignore();
		return;
	}

	//检查工程是否有未保存
	Solution* solution=Document::instance()->getSolution();
	if(solution && solution->isModified())
	{
		bool ret=questionModification(solution);
		if(!ret){
			event->ignore();
			return;
		}
	}

	//检查打开的文件是否有未保存的
	QList<QMdiSubWindow*> list = _mdiArea->subWindowList();
	bool isModified = false;
	foreach(QMdiSubWindow* win,list)
	{
		BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(win->widget());
		if(!editor)
			continue ;

		if(editor->isModified())
		{
			isModified = true;
			break;
		}
	}
	if(isModified)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle(tr("INSIDES Editor"));
		msgBox.setText(tr("Do you want to save the changes?\n\n")+
			tr("Choose 'Yes' to save the current file.\n")+
			tr("Choose 'No' to  discard the changes.\n")+
			tr("Choose 'Cancel' to stop closing the window")
			);
		msgBox.setIcon(QMessageBox::Warning);

		QPushButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
		QPushButton *noButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
		QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

		msgBox.exec();

		if (msgBox.clickedButton() == yesButton)
			saveAll();
		else if(msgBox.clickedButton() == noButton)
			;
		else
		{
			event->ignore();
			return;
		}
	}

	writeSetting();
	writeSettingToIni();
	event->accept();
}

bool MainWindow::questionExitSolver()
{
	if(!Document::instance()->getSolution())
		return true;

	QList<Project*> proList = Document::instance()->getSolution()->getAllProjects();
	QList<Project*> solvingProjects;
	QStringList solvingProjectNameList;
	foreach(Project* pro,proList)
	{
		SolveProcess* process = pro->getSolveProcess();
		if(process)
		{
			if(process->getCurrentState() != SendToClientMessage::FINISHED)
				solvingProjectNameList<<pro->getProjectName();

			solvingProjects<<pro;
		}
	}

	if(solvingProjectNameList.isEmpty())
		return true;

	QMessageBox msgBox;
	msgBox.setWindowTitle(tr("INSIDES Editor"));
	msgBox.setText(QString("There are project %1 are solving or finished, sure you want to exit?\n\n").arg(solvingProjectNameList.join(" , "))+
		tr("Choose 'Yes' to exit.\n")+
		tr("Choose 'No' to  continue to solve.\n")
		);
	msgBox.setIcon(QMessageBox::Warning);

	QPushButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
	QPushButton *noButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);

	msgBox.exec();

	if(msgBox.clickedButton() == yesButton)
	{
		stopSolve(solvingProjects);
		return true;
	}
	else
		return false;
}

void MainWindow::stopSolve(const QList<Project*>& proList )
{
	foreach(Project* pro ,proList)
	{
		SolveProcess* process = pro->getSolveProcess();
		if(process)
		{
			SendToServerMessage msg;
			msg.command = SendToServerMessage::TERMINATE;
			process->sendMessage(msg);
		}
	}
}

const QList<Project*>& MainWindow::getSolvingProjects()
{
	QList<Project*> solvingProjects;
	Solution* solu = Document::instance()->getSolution();
	if(solu)
	{
		QList<Project*> proList =solu->getAllProjects();

		foreach(Project* pro,proList)
		{
			SolveProcess* process = pro->getSolveProcess();
			if(process)
				solvingProjects<<pro;
		}
	}
	
	return solvingProjects;
}

void MainWindow::createActions()
{
	QIcon iconNewSolution;
	iconNewSolution.addPixmap(QPixmap(":/resources/menu/a016-32.png"));
	iconNewSolution.addPixmap(QPixmap(":/resources/menu/a016-16.png"));
	_newSolution=new QAction(tr("&New"),this);
	_newSolution->setIcon(iconNewSolution);
	connect(_newSolution,SIGNAL(triggered()),this,SLOT(newSolution()));

	QIcon iconOpenSolution;
	iconOpenSolution.addPixmap(QPixmap(":/resources/menu/a017-32.png"));
	iconOpenSolution.addPixmap(QPixmap(":/resources/menu/a017-16.png"));
	_openSolution=new QAction(tr("&Open"),this);
	_openSolution->setIcon(iconOpenSolution);
	connect(_openSolution,SIGNAL(triggered()),this,SLOT(openSolution()));

	QIcon iconNewProject;
	iconNewProject.addPixmap(QPixmap(":/resources/menu/a002-32.png"));
	iconNewProject.addPixmap(QPixmap(":/resources/menu/a002-16.png"));
	_newProject=new QAction(tr("New"),this);
	_newProject->setIcon(iconNewProject);
	connect(_newProject,SIGNAL(triggered()),this,SLOT(newProject()));

	QIcon iconOpenProject;
	iconOpenProject.addPixmap(QPixmap(":/resources/menu/a008-32.png"));
	iconOpenProject.addPixmap(QPixmap(":/resources/menu/a008-16.png"));
	_openProject=new QAction(tr("Open"),this);
	_openProject->setIcon(iconOpenProject);
	connect(_openProject,SIGNAL(triggered()),this,SLOT(openProject()));

	_newFile=new QAction(tr("New"),this);
	QIcon iconNewFile;
	iconNewFile.addPixmap(QPixmap(":/resources/menu/h009a.png"));
	iconNewFile.addPixmap(QPixmap(":/resources/menu/h009b.png"));
	_newFile->setIcon(iconNewFile);
	connect(_newFile,SIGNAL(triggered()),this,SLOT(newFile()));

	_addExistingFile=new QAction(tr("Add existing..."),this);

	_openFile=new QAction(tr("&Open"),this);
	QIcon iconOpenFile;
	iconOpenFile.addPixmap(QPixmap(":/resources/menu/a004-16.png"));
	iconOpenFile.addPixmap(QPixmap(":/resources/menu/a004-32.png"));
	_openFile->setIcon(iconOpenFile);
	connect(_openFile,SIGNAL(triggered()),this,SLOT(open()));

	_saveFile=new QAction(tr("Save"),this);
	QIcon iconSaveFile;
	iconSaveFile.addPixmap(QPixmap(":/resources/menu/a007-32.png"));
	iconSaveFile.addPixmap(QPixmap(":/resources/menu/a007-16.png"));
	_saveFile->setIcon(iconSaveFile);
	connect(_saveFile,SIGNAL(triggered()),this,SLOT(save()));

	_saveAllDocuments=new QAction(tr("Save All"),this);
	QIcon iconSaveAllFile;
	iconSaveAllFile.addPixmap(QPixmap(":/resources/menu/a015-32.png"));
	iconSaveAllFile.addPixmap(QPixmap(":/resources/menu/a015-16.png"));
	_saveAllDocuments->setIcon(iconSaveAllFile);
	connect(_saveAllDocuments,SIGNAL(triggered()),this,SLOT(saveAll()));

	_build=new QAction(tr("Build"),this);
	QIcon iconBuild;
	iconBuild.addPixmap(QPixmap(":/resources/menu/h014a.png"));
	iconBuild.addPixmap(QPixmap(":/resources/menu/h014b.png"));
	_build->setIcon(iconBuild);
	_build->setShortcut(QKeySequence("F6"));
	connect(_build,SIGNAL(activated()),this,SLOT(build()));

	_startSimulating=new QAction(tr("Solve"),this);
	QIcon iconStartSimulating;
	iconStartSimulating.addPixmap(QPixmap(":/resources/menu/a014-32.png"));
	iconStartSimulating.addPixmap(QPixmap(":/resources/menu/a014-16.png"));
	_startSimulating->setIcon(iconStartSimulating);
	_startSimulating->setShortcut(QKeySequence("F5"));
	connect(_startSimulating,SIGNAL(activated()),this,SLOT(showSolverDialog()));

	_checkSolverStatus=new QAction(tr("Status"),this);
	_solverOptions=new QAction(tr("Options"),this);

	_pushToView=new QAction(tr("View"),this);
	QIcon iconPushToView;
	iconPushToView.addPixmap(QPixmap(":/resources/menu/a000-32.png"));
	iconPushToView.addPixmap(QPixmap(":/resources/menu/a000-16.png"));
	_pushToView->setIcon(iconPushToView);
	_pushToView->setShortcut(QKeySequence("F4"));
	connect(_pushToView,SIGNAL(activated()),this,SLOT(pushToView()));

	_applicationSetting=new QAction(tr("Settings"),this);
	QIcon iconApplicationSetting;
	iconApplicationSetting.addPixmap(QPixmap(":/resources/menu/a023-32.png"));
	iconApplicationSetting.addPixmap(QPixmap(":/resources/menu/a023-16.png"));
	_applicationSetting->setIcon(iconApplicationSetting);
	connect(_applicationSetting,SIGNAL(activated()),Document::instance(),SLOT(showApplicationSetting()));

	_createINSAction = new QAction(tr("Create ins"),this);
	QIcon createINSAction;
	createINSAction.addPixmap(QPixmap(":/resources/menu/a023-32.png"));
	createINSAction.addPixmap(QPixmap(":/resources/menu/a023-16.png"));
	_createINSAction->setIcon(createINSAction);
	connect(_createINSAction,SIGNAL(activated()),this,SLOT(createINSFile()));

	_startHelpApplication=new QAction(tr("Help"),this);
	QIcon iconStartHelpApplication;
	iconStartHelpApplication.addPixmap(QPixmap(":/resources/menu/a022-32.png"));
	iconStartHelpApplication.addPixmap(QPixmap(":/resources/menu/a022-16.png"));
	_startHelpApplication->setIcon(iconStartHelpApplication);
	connect(_startHelpApplication,SIGNAL(activated()),Document::instance(),SLOT(startHelpApplication()));
#ifdef _DEBUG
	_startHelpApplication->setEnabled(false);
#endif

	_tilePage = new QAction(tr("Tile"),this);
	QIcon tileIcon;
	tileIcon.addPixmap(QPixmap(":/resources/menu/b003-32.png"));
	tileIcon.addPixmap(QPixmap(":/resources/menu/b003-16.png"));
	_tilePage->setIcon(tileIcon);
	connect(_tilePage,SIGNAL(triggered()),_mdiArea,SLOT(tileSubWindows()));

	_cascadePage=new QAction(tr("Cascade"),this);
	QIcon cascadeIcon;
	cascadeIcon.addPixmap(QPixmap(":/resources/menu/b001-32.png"));
	cascadeIcon.addPixmap(QPixmap(":/resources/menu/b001-16.png"));
	_cascadePage->setIcon(cascadeIcon);
	connect(_cascadePage,SIGNAL(triggered()),_mdiArea,SLOT(cascadeSubWindows()));

	_formatMenu = new QMenu("Format");
	
	QIcon formatIcon;
	formatIcon.addPixmap(QPixmap(":/resources/menu/b002-32.png"));
	formatIcon.addPixmap(QPixmap(":/resources/menu/b002-16.png"));
	_formatMenu->setIcon(formatIcon);
	connect(_formatMenu->menuAction(),SIGNAL(triggered()),this,SLOT(formatCode()));
	_formatExport = new QAction(tr("Export"),this);
	connect(_formatExport,SIGNAL(triggered()),this,SLOT(formatExport()));
	_formatMenu->addAction(_formatExport);

	setActionsEnabled(false);
	_formatMenu->setEnabled(false);
	_tilePage->setEnabled(false);
	_cascadePage->setEnabled(false);
}

void MainWindow::createMenuFile()
{
	if(QAction* actionFile = ribbonBar()->addSystemButton(tr("&File"))) 
	{
		actionFile->setToolTip(tr("Click here to see everything you can do with your document"));
		actionFile->setIcon(QIcon(":/resources/menu/a000x48x48.png"));
		Qtitan::RibbonSystemPopupBar* popupBar = qobject_cast<Qtitan::RibbonSystemPopupBar*>(actionFile->menu());

		popupBar->addAction(_openSolution);
		popupBar->addAction(_newSolution);
		popupBar->addAction(_newProject);
		popupBar->addAction(_openProject);
		popupBar->addAction(_saveAllDocuments);

		if (RibbonPageSystemRecentFileList* pageRecentFile = popupBar->addPageRecentFile(tr("Recent Documents")))
		{
			pageRecentFile->setSize(9);
			//点击列表打开解决方案
			connect(pageRecentFile,SIGNAL(openRecentFile(const QString&)),
				this,SLOT(openSolution(const QString&)));
			connect(this,SIGNAL(requestRecentFileChange(const QStringList&)),
				pageRecentFile,SLOT(updateRecentFileActions(const QStringList&)));
			updateRecentFile(QString());
		}
	}
}

void MainWindow::createRibbon()
{
	if (Qtitan::RibbonPage* pageHome = ribbonBar()->addPage(tr("&Home")))
	{
		createGroupMain(pageHome->addGroup(tr("File")));
		createGroupBuild(pageHome->addGroup(tr("Build")));
		createGroupMics(pageHome->addGroup(tr("Mics")));
		creategroupWindows(pageHome->addGroup(tr("Windows")));
	}
	if(Qtitan::RibbonPage* pageSetting = ribbonBar()->addPage(tr("&Setting")))
	{
		createGroupTabPosition(pageSetting->addGroup(tr("Windows")));
		createGroupCreateINS(pageSetting->addGroup(tr("Change")));
	}
}

void MainWindow::createGroupCreateINS( Qtitan::RibbonGroup* group )
{
	group->addAction(_createINSAction,Qt::ToolButtonTextUnderIcon);
}

void MainWindow::createQuickAccessBar()
{
}

void MainWindow::createStatusBar()
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

void MainWindow::writeSetting()
{
	QSettings settings("INSIDESEDITOR", "INSIDESEDITOR");

	settings.beginGroup("state");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	settings.setValue("currentDir",QDir::current().absolutePath());
	settings.endGroup();
}

void MainWindow::writeSettingToIni()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-editor.ini", QSettings::IniFormat);

	settings.beginGroup("DIRECTORIES");
	settings.setValue("recent_files",getRecentFileList());
	settings.endGroup();

	if(Document::instance()->getSolution())
	{
		QSettings customSettings(dir +"insides-editor-custom.ini", QSettings::IniFormat);
		customSettings.beginGroup("lastState");
		customSettings.setValue("solution",Document::instance()->getSolution()->getSolutionFullName());
		QStringList list = _mdiArea->getOpenFiles();
		if(!list.isEmpty())
		{
			customSettings.setValue("openFiles",list);
			customSettings.setValue("currFile",_mdiArea->getCurrentFile(_mdiArea->currentSubWindow()));
		}
		else
		{
			customSettings.setValue("openFiles","no open files");
			customSettings.setValue("currFile","no open file");
		}
		customSettings.endGroup();
	}
}

void MainWindow::readSettingFromIni()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-editor.ini", QSettings::IniFormat);

	settings.beginGroup("DIRECTORIES");
	QStringList recentFiles = settings.value("recent_files",QStringList()).toStringList();
	foreach(const QString& s, recentFiles)
	{
		QFileInfo i(s);
		_recentFileInfoList.removeOne(i);
		_recentFileInfoList<<i;
	}
	updateRecentFile(QString());
	settings.endGroup();
}

void MainWindow::readSetting()
{
	QSettings settings("INSIDESEDITOR", "INSIDESEDITOR");

	settings.beginGroup("state");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());

	QString currDir=settings.value("currentDir").toString();
	QDir::setCurrent(currDir);

	settings.endGroup();
}

void MainWindow::openLastFiles()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-editor-custom.ini", QSettings::IniFormat);

	settings.beginGroup("lastState");
	QString lastSolution = settings.value("solution").toString();
	if(!Document::instance()->getSolution()->getSolutionFullName().compare(lastSolution,Qt::CaseInsensitive))
	{
		QStringList list = settings.value("openFiles").toStringList();
		if(list.contains("no open files"))
			return;

		if(!list.isEmpty())
		{
			foreach(QString str, list)
				_mdiArea->activateOrOpenFile(str);

			QString file = settings.value("currFile").toString();
			_mdiArea->activateOrOpenFile(file);

			BaseCodeEditor* editor = static_cast<BaseCodeEditor*>(_mdiArea->currentSubWindow()->widget());
			QString fileName = editor->getFileName();
			QList<Project*> list = Document::instance()->getSolution()->getAllProjects();
			foreach(Project* pro,list)
			{
				QList<Entity*> entityList = pro->getEntities();
				foreach(Entity* entity,entityList)
				{
					if(!entity->getFullFileName().compare(fileName,Qt::CaseInsensitive))
					{
						Document::instance()->getSolution()->setMainProject(pro);
						break;
					}
				}

				if(Document::instance()->getSolution()->getMainProject())
					break;
			}

			updateIcon();
		}
	}
}

void MainWindow::createGroupTabPosition(Qtitan::RibbonGroup* m_groupMdiTabs)
{
	//m_groupMdiTabs = pageView->addGroup(tr("Option MDI Tabs"));
	if (m_groupMdiTabs)
	{
		QRadioButton* m_posTop = new QRadioButton(tr("Position Top"));
		connect(m_posTop, SIGNAL(toggled(bool)), this, SLOT(setTabPositionTop(bool)));
		m_posTop->setChecked(true);
		m_groupMdiTabs->addWidget(m_posTop);

		QRadioButton* m_posBottom = new QRadioButton(tr("Position Bottom"));
		connect(m_posBottom, SIGNAL(toggled(bool)), this, SLOT(setTabPositionBottom(bool)));
		m_groupMdiTabs->addWidget(m_posBottom);

		QRadioButton* m_posLeft = new QRadioButton(tr("Position Left"));
		connect(m_posLeft, SIGNAL(toggled(bool)), this, SLOT(setTabPositionLeft(bool)));
		m_groupMdiTabs->addWidget(m_posLeft);

		QRadioButton* m_posRight = new QRadioButton(tr("Position Right"));
		connect(m_posRight, SIGNAL(toggled(bool)), this, SLOT(setTabPositionRight(bool)));
		m_groupMdiTabs->addWidget(m_posRight);
		//m_groupMdiTabs->setEnabled(stateWorkspace == Qt::Checked);
	}
}

void MainWindow::setTabPositionLeft(bool state)
{
	if (state)
		_mdiArea->setTabPosition(QTabWidget::West);
}

void MainWindow::setTabPositionTop(bool state)
{
	if (state)
		_mdiArea->setTabPosition(QTabWidget::North);
}

void MainWindow::setTabPositionBottom(bool state)
{
	if (state)
		_mdiArea->setTabPosition(QTabWidget::South);
}

void MainWindow::setTabPositionRight(bool state)
{
	if (state)
		_mdiArea->setTabPosition(QTabWidget::East);
}

void MainWindow::createGroupMain( Qtitan::RibbonGroup* group )
{
	group->addAction(_newSolution,Qt::ToolButtonTextUnderIcon);
	group->addAction(_openSolution,Qt::ToolButtonTextUnderIcon);

	group->addAction(_newProject,Qt::ToolButtonTextUnderIcon);
	group->addAction(_openProject,Qt::ToolButtonTextUnderIcon);

	group->addSeparator();

	group->addAction(_openFile,Qt::ToolButtonIconOnly);
	group->addAction(_saveFile,Qt::ToolButtonIconOnly);
	group->addAction(_saveAllDocuments,Qt::ToolButtonIconOnly);
}

void MainWindow::createGroupBuild( Qtitan::RibbonGroup* group )
{
	group->addAction(_pushToView,Qt::ToolButtonTextUnderIcon);

	group->addAction(_build,Qt::ToolButtonTextUnderIcon);
	group->addAction(this->_startSimulating,Qt::ToolButtonTextUnderIcon);

	_pushToView->setEnabled(false);
	_build->setEnabled(false);
	_startSimulating->setEnabled(false);
}

void MainWindow::createGroupMics( Qtitan::RibbonGroup* group )
{
	group->addAction(_formatMenu->menuAction(),Qt::ToolButtonTextUnderIcon);
	group->addAction(_applicationSetting,Qt::ToolButtonTextUnderIcon);
	group->addAction(_startHelpApplication,Qt::ToolButtonTextUnderIcon);
}

void MainWindow::creategroupWindows( Qtitan::RibbonGroup* group )
{
	group->addAction(_tilePage,Qt::ToolButtonTextUnderIcon);
	group->addAction(_cascadePage,Qt::ToolButtonTextUnderIcon);
}

void MainWindow::loadFile(const QString &fileName)
{
	QMdiSubWindow* tmp=_mdiArea->getMyWidget(fileName);
	if(tmp){
		_mdiArea->setActiveSubWindow(tmp);
		return;
	}

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	BaseCodeEditor* newEditor=new BaseCodeEditor(this);
	newEditor->setFileName(fileName);
	newEditor->setText(in.readAll());
	file.close();
	newEditor->setModified(false);
	newEditor->setWindowTitle(strippedName(fileName));
	QApplication::restoreOverrideCursor();

	_mdiArea->addMyWindow(newEditor);
//	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
	if(!_mdiArea->currentSubWindow())
		return false;
	BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(_mdiArea->activeSubWindow()->widget());
	if(!editor)
		return false;
	if(!editor->isModified())
		return true;

	editor->removeWatchFile(editor->getFileName());
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << editor->text();
	file.close();
	editor->setModified(false);
	QApplication::restoreOverrideCursor();
	statusBar()->showMessage(tr("File saved"), 2000);
	editor->addWatchFile(editor->getFileName());

	return true;
}

QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
		loadFile(fileName);
}

bool MainWindow::save()
{
	return saveCurrFile();
}

bool MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void MainWindow::newProject()
{
	if(Document::instance()->getSolution())
		Document::instance()->getSolution()->createNewProject();
}

void MainWindow::openProject()
{
	if(Document::instance()->getSolution())
		Document::instance()->getSolution()->addExistingProject();
}

void MainWindow::build()
{
	FileManager::instance()->notifyBeginBuild();
	INSEditor::Parse::ModelParser parser;
	
	BuildObserver* observer=new BuildObserver();
	parser.attachErrorObserver(observer);
	save();
	Entity* entity = Document::instance()->getSolution()->getMainProject()->getStartupEntity();
	if(!entity)
	{
		QMessageBox::warning(this,"Warning","Please set start up file!");
		return ;
	}
	INSEditor::Parse::AssemblyItem* tmp=parser.parse(entity->getFullFileName());
	INSEditor::Parse::TDYTypeInfoManager typeManager;
	typeManager.load(qApp->applicationDirPath()+"/settings/ins.xml");
	parser.compileAssemblyItem(tmp,entity->getFullFileName(),typeManager.getAllInfos());
	
	FileManager::instance()->notifyUpdateModel(tmp,entity->getFullFileName());
	FileManager::instance()->notifyExpandModelTree();
	FileManager::instance()->notifyEndBuild();
}

void MainWindow::pushToView()
{
	Project* project=Document::instance()->getSolution()->getMainProject();
	if(project)
		project->openWithViewer();
}

void MainWindow::loadHelpPlugin()
{
	QDir pluginsDir(qApp->applicationDirPath());
	//pluginsDir.cd("plugins");
	{
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("edhelp.dll"));
		QObject *plugin = pluginLoader.instance();
		if (plugin){
			ModulePlugin* modulePluginView = qobject_cast<ModulePlugin*>(plugin);
			modulePluginView->setMainWindow(this);
			modulePluginView->doJob();
		}
	}
}

void MainWindow::loadParsePlugin()
{
	EDParseSingleton* tmp=EDParseSingleton::instance();
	if(tmp->getPlugin())
		tmp->getPlugin()->initUI(this);
}

void MainWindow::Warning( const char *str )
{
	logMessageThread(str);
}

void MainWindow::Message( const char *str )
{
	logMessageThread(str);
}

void MainWindow::Error( const char *str )
{
	logMessageThread(str);
}

void MainWindow::Log( const char *str )
{
	logMessageThread(str);
}

void MainWindow::logMessageThread( const QString& mess )
{
	if(thread()==QThread::currentThread())
		logMessage(mess);
	else{
		UpdateTextEvent* e=new UpdateTextEvent(mess);
		QApplication::postEvent(this,e);
	}
}
void MainWindow::logMessage( const QString& mess )
{
	if(statusBar())
		statusBar()->showMessage(mess,2000);
}

void MainWindow::customEvent( QEvent* event )
{
	if(event->type()==UpdateTextEvent::ID_UPDATE_TEXT_EVENT)
		logMessage(((UpdateTextEvent*)event)->str());
	else
		RibbonWindow::customEvent(event);
}

void MainWindow::showSolverDialog()
{
	FileManager::instance()->notifySolveProject();
}

void MainWindow::newSolution()
{
	QString solutionRootDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
	if(solutionRootDir.isEmpty())
		return;

	QString solutionName = QInputDialog::getText(this,tr("Enter new solution name"),tr("New solution name:"));
	if (solutionName.isEmpty())
		return;

	solutionName=solutionName.trimmed();

	Document::instance()->close();

	Solution* solution=Document::instance()->createNew(solutionRootDir,solutionName);

	if(!solution)
		return;

	setActionsEnabled(true);
	updateRecentFile(solution->getSolutionFullName());
}

void MainWindow::openSolution()
{
	QString solutionName=QFileDialog::getOpenFileName(this,tr("Open Existing Solution"),
		QDir::current().absolutePath(),tr("Solution files (*.insln)"));
	if(solutionName.isEmpty())
		return;

	openSolution(solutionName); 
}

void MainWindow::openSolution( const QString& solutionName )
{
	QFileInfo a(solutionName);
	QDir::setCurrent(a.absoluteDir().absolutePath());

	QList<Project*> projects = getSolvingProjects();
	if(!projects.isEmpty())
	{
		QStringList strList ;
		foreach(Project* pro,projects)
			strList<<pro->getProjectName();
		QMessageBox msgBox;
		msgBox.setText("Multiple project is to solve.\n\n"
			"To give up and open the new solution?");
		msgBox.setIcon(QMessageBox::Warning);

		QPushButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
		QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

		msgBox.exec();

		if (msgBox.clickedButton() == yesButton)
		{
			stopSolve(projects);
			FileManager::instance()->notifyClearSolve();
		}
		else
			return;
	}

	Document::instance()->close();

	Document::instance()->open(solutionName);

	setActionsEnabled(true);
	updateRecentFile(solutionName);

	if(Document::instance()->getProperties()->isShowLastOpenedFiles)
		openLastFiles();
}

void MainWindow::saveAll()
{
	Document* doc=Document::instance();

	QList<QMdiSubWindow*> list = _mdiArea->subWindowList();

	foreach(QMdiSubWindow* tmp,list)
	{
		BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(tmp->widget());
		if(!editor)
			return ;

		editor->save();
		editor->setModified(false);
	}
	statusBar()->showMessage(tr("All file saved"), 2000);
	Document::instance()->getSolution()->save();
}

void MainWindow::setActionsEnabled( bool b )
{
	_newProject->setEnabled(b);
	_openProject->setEnabled(b);
	//_openFile->setEnabled(b);
	_saveFile->setEnabled(b);
	_saveAllDocuments->setEnabled(b);
	//_pushToView->setEnabled(b);
	//_startSimulating->setEnabled(b);
	//_build->setEnabled(b);
}

void MainWindow::onSolutionCreated( Solution* solution )
{
	if(solution)
	{
		QString fullName=solution->getSolutionFullName();
		QString title=QString("%1 (%2)").arg(_appName).arg(fullName);
		setWindowTitle(title);
		setActionsEnabled(true);
		connect(solution,SIGNAL(modificationStatusChanged(bool)),
			this,SLOT(onSolutionModificationStatusChanged(bool)));
	}
	else
	{
		setWindowTitle(_appName);
		setActionsEnabled(false);
	}
}

void MainWindow::onSolutionModificationStatusChanged( bool b )
{
	Solution* solution=Document::instance()->getSolution();
	if(solution)
	{
		QString fullName=solution->getSolutionFullName();
		QString title=QString("%1 (%2)").arg(_appName).arg(fullName);
		if(b)
			setWindowTitle(title+"*");
		else
			setWindowTitle(title);
	}
}

void MainWindow::onSolutionClosed( Solution* solution )
{
	if(solution)
		questionModification(solution);
}

bool MainWindow::questionModification(Solution* solution )
{
	if(solution->isModified())
	{
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		switch (ret) {
		case QMessageBox::Save:
			solution->save();
			break;
		case QMessageBox::Discard:
			break;
		case QMessageBox::Cancel:
			return false;
		}
	}
		
	return true;
}

void MainWindow::updateRecentFile( const QString& newFileName )
{
	if(!newFileName.isEmpty())
	{
		QFileInfo i(newFileName);
		if(_recentFileInfoList.removeOne(i));
			_recentFileInfoList.push_front(i);
	}
	emit requestRecentFileChange(getRecentFileList());
}

QStringList MainWindow::getRecentFileList()
{
	QStringList vec;
	foreach(const QFileInfo& i,_recentFileInfoList)
	{
		if(i.exists())
			vec<<i.absoluteFilePath();
	}

	return vec;
}

void MainWindow::respondOpeningFile( const QString& fileName )
{
	QFileInfo info(fileName);
	QString suf = info.suffix();
	if(suf == "ins" || suf == "tdy")
		loadFile(fileName);
}

void MainWindow::formatCode()
{
	if(!_mdiArea->currentSubWindow())
		return ;
	BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(_mdiArea->activeSubWindow()->widget());
	if(!editor)
		return ;

	INSEditor::Parse::ModelParser parser;
	QString fileName = editor->getFileName();
	if(fileName.isEmpty())
		return;
	INSEditor::Parse::AssemblyItem* tmp=parser.parseFile(editor->text(),fileName);
	INSEditor::Parse::TDYTypeInfoManager typeManager;
	typeManager.loadFromTDYTemplate(qApp->applicationDirPath()+"/settings/ins.xml");
	parser.compileAssemblyItem(tmp,typeManager.getAllInfos());

	INSEditor::Parse::INSModelFormator mator;
	mator.setIndentation(Document::instance()->getProperties()->formatIndentationValue);
	mator.setMaxLineWord(Document::instance()->getProperties()->formatLineMaxNumValue);
	QString str = mator.toString(tmp);

	QApplication::clipboard()->setText(str);

	int line,index;
	editor->getCursorPosition(&line,&index);
	editor->selectAll();
	editor->paste();
	editor->setCursorPosition(line,index);

	statusBar()->showMessage(tr("Format finished !"), 2000);
}

void MainWindow::formatExport()
{
	if(!_mdiArea->currentSubWindow())
		return ;
	BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(_mdiArea->activeSubWindow()->widget());
	if(!editor)
		return ;

	INSEditor::Parse::ModelParser parser;
	QString fileName = editor->getFileName();
	if(fileName.isEmpty())
		return;

	QString suff = QFileInfo(fileName).suffix();
	QString path = QFileInfo(fileName).path();

	INSEditor::Parse::AssemblyItem* tmp=parser.parseFile(fileName,true);
	INSEditor::Parse::TDYTypeInfoManager typeManager;
	typeManager.loadFromTDYTemplate(qApp->applicationDirPath()+"/settings/ins.xml");
	parser.compileAssemblyItem(tmp,typeManager.getAllInfos());

	INSEditor::Parse::INSModelFormator mator;
	mator.setIndentation(Document::instance()->getProperties()->formatIndentationValue);
	mator.setMaxLineWord(Document::instance()->getProperties()->formatLineMaxNumValue);
	QString str = mator.toString(tmp);
	
	QString saveName =QFileDialog::getSaveFileName(this,tr("Select save dir :"),path,"*."+suff);
	if(saveName.isEmpty())
		return;

	QFile file(saveName);
	if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
		return;

	QTextStream stream(&file);
	stream<<str;
	file.close();
	statusBar()->showMessage(tr("Export format file finished !"), 2000);
}

bool MainWindow::saveCurrFile()
{
	if(!_mdiArea->currentSubWindow())
		return false;
	BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(_mdiArea->activeSubWindow()->widget());
	if(!editor)
		return false;

	return saveFile(editor->getFileName());
}

void MainWindow::buidProject()
{
	build();
}

void MainWindow::updateIcon()
{
	if(Document::instance()->getSolution()->getMainProject())
	{
		_pushToView->setEnabled(true);
		_build->setEnabled(true);
		_startSimulating->setEnabled(true);

		if(!_mdiArea->subWindowList().isEmpty())
		{
			_formatMenu->setEnabled(true);
			_tilePage->setEnabled(true);
			_cascadePage->setEnabled(true);
		}
		else
		{
			_formatMenu->setEnabled(false);
			_tilePage->setEnabled(false);
			_cascadePage->setEnabled(false);
		}
	}
	else
	{
		_pushToView->setEnabled(false);
		_build->setEnabled(false);
		_startSimulating->setEnabled(false);

		_formatMenu->setEnabled(false);
		_tilePage->setEnabled(false);
		_cascadePage->setEnabled(false);
	}
}

void MainWindow::onSubWindowActivated( QMdiSubWindow * win )
{
	if(!win)
		return;

	BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(_mdiArea->activeSubWindow()->widget());
	if(!editor)
		return ;
	
	statusBar()->showMessage(tr("Current file : ") + editor->getFileName(),5000);
}

void MainWindow::createINSFile()
{
	INSEditor::Parse::TDYTypeInfoManager manger;
	QString str = QFileDialog::getOpenFileName(this,"Select tdy_template",qApp->applicationDirPath(),"XML File(*.xml)");
	if(str.isEmpty())
		return;

	QString fileName = QFileDialog::getSaveFileName(this,"Save Name",".","XML File(*.xml)");
	if(fileName.isEmpty())
		return;

	manger.loadFromTDYTemplate(str);
	manger.save(fileName);
}

void MainWindow::onTimeout()
{
	static int flag = 0;
	if(flag > 5)
	{
		QString str = _checkFtp->readAll();

		_checkUpdateTimer->stop();
		delete _checkUpdateTimer;
		_checkUpdateTimer = NULL;
		
		if(str.isEmpty())
		{
			this->statusBar()->showMessage("You application is latest version.",3000);
			return;
		}

		long size = checkHasUpdate(str);
		if(size == 0)
		{
			this->statusBar()->showMessage("You application is latest version.",3000);
			return;
		}

		int mb = size/1024/1024;
		if(mb == 0)
			mb =1 ;

		QMessageBox msgBox;
		msgBox.setText(tr("There are update for your software.\n\nDo you want to update it now? (size : %1 Mb").arg(mb));
		msgBox.setIcon(QMessageBox::Information);

		QPushButton *yesBtn = msgBox.addButton(tr("Yse"), QMessageBox::ActionRole);
		QPushButton *noBtn = msgBox.addButton(tr("No"), QMessageBox::ActionRole);

		msgBox.exec();

		if (msgBox.clickedButton() == yesBtn)
		{
			QProcess pro(this);
			QString dir = qApp->applicationDirPath();
			QDir tmpDir(dir);
			tmpDir.cd("..");
			dir = tmpDir.absolutePath() +"/bin/update.exe";
			QFile file(dir);
			if(!file.exists())
			{
				QMessageBox::warning(this,tr("Warning"),tr("A error occurred to the update application, update failed!"));
				return;
			}
			pro.startDetached(dir);
			qApp->quit();
		}
		else
			return;
	}

	flag ++;
}

long MainWindow::checkHasUpdate(QString con )
{
	long sum =0 ;

	QDomDocument ftpDocument;
	ftpDocument.setContent(con);
	QDomElement ftpVersionElement = ftpDocument.firstChildElement();

	QDomNodeList ftpItems = ftpVersionElement.childNodes();
	QDomElement item = ftpVersionElement.firstChildElement("item");
	QString dir = qApp->applicationDirPath();
	QDir tmpDir(dir);
	tmpDir.cd("..");
	dir = tmpDir.absolutePath()+"/";

	while(!item.isNull())
	{
		QString fileName = item.attribute("file");
		if(!fileName.compare("bin/update.exe",Qt::CaseInsensitive))
		{
			item = item.nextSiblingElement("item");
			continue;
		}

		QString size = item.attribute("size");
		QString md5 = item.attribute("id");
		
		QFile tmpFile(dir+fileName);
		if(!tmpFile.open(QIODevice::ReadOnly) && !tmpFile.exists())
			sum += size.toLong();

		QByteArray ba = QCryptographicHash::hash(tmpFile.readAll(),QCryptographicHash::Md5);
		tmpFile.close();
		QString localMd5 = ba.toHex();
		if(md5.compare(localMd5))
			sum += size.toLong();

		item = item.nextSiblingElement("item");
	}

	return sum;
}



