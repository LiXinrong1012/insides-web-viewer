#include "helper.h"

#include <QHelpEngine>
#include <QtHelp/QHelpContentWidget>
#include <QtHelp>
#include <QDockWidget>

#include "MyHelpViewer.h"

helper::helper(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);


	QString fileName="C:/Users/Jerry/AppData/Local/Trolltech/Assistant/qthelpcollection_4.8.4.qhc";
	QHelpEngine *helpEngine = new QHelpEngine(fileName, this);
	helpEngine->setupData();

	// init dock widget
	QDockWidget* contentsDockWidget = new QDockWidget(this);
	contentsDockWidget->setObjectName(QString::fromUtf8("contentsDockWidget"));
	addDockWidget(Qt::LeftDockWidgetArea, contentsDockWidget);
	contentsDockWidget->setWidget(helpEngine->contentWidget());

	QDockWidget* indexDockWidget = new QDockWidget(this);
	indexDockWidget->setObjectName(QString::fromUtf8("indexDockWidget"));
	addDockWidget(Qt::LeftDockWidgetArea, indexDockWidget);
	indexDockWidget->setWidget(helpEngine->indexWidget());


	// init central widget
	MyHelpViewer* viewer=new MyHelpViewer(this,helpEngine);
	setCentralWidget(viewer);

	connect(helpEngine->contentWidget(),
		SIGNAL(linkActivated(const QUrl &)),
		viewer, SLOT(setSource(const QUrl &)));
}

helper::~helper()
{

}
