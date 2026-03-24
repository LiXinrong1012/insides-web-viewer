#include "edparse.h"

#include <QtCore>
#include <QSettings>
#include <QtGui/QMessageBox>
#include <QtGui>
#include <QDockWidget>
#include <QMainWindow>
#include <QListWidget>
#include <QTreeView>

#include "modelviewmodel.h"
#include "searchkeywidget.h"
#include "outputlistwidget.h"
#include "searchkeywidget.h"

#include "edcore/errormanager.h"
#include "edcore/filemanager.h"

/// 解决方案树
#include "solutionbrowsertreewidget.h"
#include "solutionbrowserwidget.h"

/// 属性
#include "propertydockwidget.h"
#include "propertywidget.h"

/// 结果树
#include "resultbrowserwidget.h"

Q_EXPORT_PLUGIN2(edparseplugin, EDParse);

EDParse::EDParse()
{	
}

EDParse::~EDParse()
{
}

QString EDParse::getKeyname()
{
	return "EDParsePlugin";
}

void EDParse::initUI( QMainWindow* mainWindow )
{
	_mainWindow=mainWindow;
	
	/// Solution Browser
	QDockWidget* solutionBrowserDockWidget=new QDockWidget(_mainWindow);
	solutionBrowserDockWidget->setObjectName(QString::fromUtf8("solutionBrowserDockWidget"));
	mainWindow->addDockWidget(Qt::LeftDockWidgetArea,solutionBrowserDockWidget);
	solutionBrowserDockWidget->setWindowTitle(tr("Solution Browser"));

	SolutionBrowserWidget* solutionBrowserWidget=new SolutionBrowserWidget(mainWindow);
	solutionBrowserDockWidget->setWidget(solutionBrowserWidget);


	/// Properties Widget
	PropertyDockWidget* propertyDockWidget=new PropertyDockWidget(_mainWindow);
	propertyDockWidget->setObjectName(QString::fromUtf8("propertiesDockWidget"));
	mainWindow->addDockWidget(Qt::RightDockWidgetArea,propertyDockWidget);
	connect(solutionBrowserWidget->getSolutionBrowserTreeWidget(),
		SIGNAL(currentItemChanged(void*,int)),
		propertyDockWidget->getPropertyWidget(),
		SLOT(onItemChanged(void*,int)));

	//QWidget* lTitleBar = resultBrowserDockWidget->titleBarWidget();
	//QWidget* lEmptyWidget = new QWidget();
	//resultBrowserDockWidget->setTitleBarWidget(lEmptyWidget);
	//delete lTitleBar;


	/// Model Tree
	QDockWidget* modelViewDockWidget = new QDockWidget(_mainWindow);
	modelViewDockWidget->setObjectName(QString::fromUtf8("modelViewDockWidget"));
	mainWindow->addDockWidget(Qt::RightDockWidgetArea, modelViewDockWidget);
	modelViewDockWidget->setWindowTitle(tr("Model"));

	_modelTreeView=new QTreeView(mainWindow);
	_modelTreeView->setHeaderHidden(true);
	modelViewDockWidget->setWidget(_modelTreeView);

	ModelViewModel* model=new ModelViewModel(mainWindow);
	_modelTreeView->setModel(model);
	connect(FileManager::instance(),SIGNAL(requestUpdateModel(INSEditor::Parse::AssemblyItem*,const QString&)),model,SLOT(onEntityActivated(INSEditor::Parse::AssemblyItem*,const QString&)));
	connect(_modelTreeView->selectionModel(),SIGNAL(currentChanged(const QModelIndex&,const QModelIndex)),
		model,SLOT(onModelItemClicked(const QModelIndex&)));
	connect(FileManager::instance(),SIGNAL(requestExpandModelTree()),this,SLOT(onExpandModelTree()));
	

	//build widget
	QDockWidget* buildDockWidget = new QDockWidget(_mainWindow);
	buildDockWidget->setObjectName(QString::fromUtf8("buildDockWidget"));
	mainWindow->addDockWidget(Qt::BottomDockWidgetArea, buildDockWidget);
	buildDockWidget->setWindowTitle(tr("Build"));

	_outputListWidget=new OutputListWidget(mainWindow);
	_outputListWidget->setSpacing(3);
	_outputListWidget->setDockWidget(buildDockWidget);
	buildDockWidget->setWidget(_outputListWidget);

	//error
	/*
	QDockWidget* errorDockWidget = new QDockWidget(_mainWindow);
	errorDockWidget->setObjectName(QString::fromUtf8("errorDockWidget"));
	mainWindow->addDockWidget(Qt::BottomDockWidgetArea,errorDockWidget);
	errorDockWidget->setWindowTitle(tr("Error"));

	_errorProxyModel = new QSortFilterProxyModel(mainWindow);
	_errorTableModel=new ErrorTableModel(mainWindow);
	_errorProxyModel->setSourceModel(_errorTableModel);
	_errorTableModel->setProxyModel(_errorProxyModel);
	
	_errorTableView=new QTableView(mainWindow);
	_errorTableView->setSelectionMode( QAbstractItemView::SingleSelection );
	_errorTableView->setSelectionBehavior ( QAbstractItemView::SelectRows); 
	_errorTableView->setMouseTracking(true);
	_errorTableView->setSortingEnabled(true);
	
	errorDockWidget->setWidget(_errorTableView);
	_errorTableView->setModel(_errorProxyModel);
	

	connect(_errorTableView,SIGNAL(doubleClicked(QModelIndex)),_errorTableModel,SLOT(showErrorMessage(QModelIndex)));
	connect(myProject()->getErrorItemManager(),SIGNAL(changed()),_errorTableModel,SLOT(onErrorListUpdated()));

	connect(_errorTableView,SIGNAL(clicked( const QModelIndex &)),this,SLOT(saveSetting( const QModelIndex &)));
	*/

	//connect(myProject(),SIGNAL(projectLoaded()),this,SLOT(onProjectLoaded()));

	// init search & replace dialog
	_searchReplaceDialog=new SearchKeyWidget(_mainWindow);

	loadSetting();
}

void EDParse::onProjectLoaded()
{
	//CompileAllFileWorker *worker = new CompileAllFileWorker;
	//QThread *workerThread = new QThread(this);

	//connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
	//connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
	//worker->moveToThread(workerThread);

	//workerThread->start();
}

void EDParse::onProjectItemAdded()
{
}

//保存errorTable位置
void EDParse::saveSetting( const QModelIndex & index)
{
}

void EDParse::loadSetting()
{
}

ISearchReplaceDialog* EDParse::getSearchReplaceDialog()
{
	return _searchReplaceDialog;
}

void EDParse::onExpandModelTree()
{
	_modelTreeView->expand(_modelTreeView->indexAt(QPoint(0,0)));
}
