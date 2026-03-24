#include "moduleplugin_help.h"


#include <QtCore>
#include <QDockWidget>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QTreeWidget>

#include "MyWebHelpViewer.h"
#include "HelpViewer.h"
#include "simplehelpviewer.h"
#include "helpenginesingleton.h"
#include "indexwindow.h"
#include "topicchooser.h"
#include "mycentralwidget.h"


Q_EXPORT_PLUGIN2(moduleplugin, ModulePluginHelp);


QString ModulePluginHelp::getKeyname()
{
	return "ModulePluginHelp";
}

void ModulePluginHelp::setMainWindow( QMainWindow* mainWindow )
{
	_mainWindow=mainWindow;
}

void ModulePluginHelp::setParameters( const QList<QString>& paras )
{
}

bool ModulePluginHelp::doJob()
{
	//QString fileName="C:/Users/Jerry/AppData/Local/Trolltech/Assistant/qthelpcollection_4.8.4.qhc";
	QString fileName="D:/Jerry/workdir/INSEditor/tools/INSHelp/insides.qhc";
	//QString fileName="D:/tsinghuaDir/INSHelp/insides.qhc";//D:/tsinghuaDir/INSHelp/insides.qhc
	QHelpEngine *helpEngine = new QHelpEngine(fileName, this);
	helpEngine->setupData();
	HelpEngineSingleton::setHelpEngine(helpEngine);

	// init dock widget
	QDockWidget* contentsDockWidget = new QDockWidget(_mainWindow);
	contentsDockWidget->setObjectName(QString::fromUtf8("contentsDockWidget"));
	_mainWindow->addDockWidget(Qt::RightDockWidgetArea, contentsDockWidget);;
	contentsDockWidget->setWidget(helpEngine->contentWidget());
	contentsDockWidget->setWindowTitle(tr("Contents"));

	QDockWidget* indexDockWidget = new QDockWidget(_mainWindow);
	IndexWindow* indexWindow=new IndexWindow(_mainWindow);
	indexWindow->setObjectName("HelpIndexWindow");
	indexDockWidget->setObjectName(QString::fromUtf8("indexDockWidget"));
	_mainWindow->addDockWidget(Qt::RightDockWidgetArea, indexDockWidget);
	//indexDockWidget->setWidget(helpEngine->indexWidget());
	indexDockWidget->setWidget(indexWindow);
	indexDockWidget->setWindowTitle(tr("Index"));
	///

	_helpSearchEngine = helpEngine->searchEngine();
	_helpSearchQueryWidget = _helpSearchEngine->queryWidget(); 
	_helpSearchResultWidget = _helpSearchEngine->resultWidget();

	
	
	_indexModel = helpEngine->indexModel();
	

	// init central widget
	QDockWidget* mainViewerDock=new QDockWidget(_mainWindow);
	mainViewerDock->setObjectName(QString::fromUtf8("mainViewerDockWidget"));
	_mainWindow->addDockWidget(Qt::BottomDockWidgetArea,mainViewerDock);
	//MyWebHelpViewer* viewer=new MyWebHelpViewer(_mainWindow,helpEngine);
	//HelpViewer* viewer=new HelpViewer(_mainWindow,helpEngine);
	HelpViewer* viewer=new HelpViewer(1,_mainWindow);
	mainViewerDock->setWidget(viewer);
	mainViewerDock->setWindowTitle(tr("Help"));
	MyCentralWidget* myCentralWidget=new MyCentralWidget(_mainWindow);
	myCentralWidget->setHelpViewer(viewer);

	connect(helpEngine->contentWidget(),
		SIGNAL(linkActivated(const QUrl &)),
		viewer, SLOT(activateMySource( const QUrl & )));



	connect(this,SIGNAL(linkActivated(const QUrl &)),
		viewer,SLOT(setSource( const QUrl &)));

	// index window
	connect(helpEngine->indexWidget(),SIGNAL(linkActivated(const QUrl&,const QString &)),
		viewer,SLOT(activateMySource( const QUrl & )));
	//connect(helpEngine->indexWidget(), SIGNAL(linkActivated(const QUrl&)), myCentralWidget, SLOT(setSource(const QUrl&)));
	connect(indexWindow, SIGNAL(linksActivated(QMap<QString,QUrl>,QString)),
		this, SLOT(showTopicChooser(QMap<QString,QUrl>,QString)));
	connect(indexWindow, SIGNAL(escapePressed()), this,
		SLOT(activateCurrentCentralWidgetTab()));



	return true;
}



void ModulePluginHelp::showTopicChooser( QMap<QString,QUrl> links,QString keyword)
{
	TopicChooser tc(_mainWindow, keyword, links);
	if (tc.exec() == QDialog::Accepted) {
		MyCentralWidget::instance()->setSource(tc.link());
	}
}

void ModulePluginHelp::activateCurrentCentralWidgetTab()
{

}



