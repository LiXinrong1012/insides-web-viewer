#include "prept.h"

#include <QtGui>
#include "modeltreewidget.h"

#include "precore/modeldocument.h"
#include "comtreemodel.h"

#include "selectionwidget.h"

using namespace INSIDES;

Q_EXPORT_PLUGIN2(insuiplugin, PREPUIPlugin);


PREPUIPlugin::PREPUIPlugin()
{

}

PREPUIPlugin::~PREPUIPlugin()
{

}

QString PREPUIPlugin::getKeyname()
{
	return "PREPUIPlugin";
}

void PREPUIPlugin::initUI( QMainWindow* mainWindow )
{
	bool loadModelTree(true),loadSelection(false);
	QString filename=qApp->applicationDirPath()+"/settings/insides-viewer.ini";
	QFile info(filename);
	if(info.exists()){
		QSettings settings(info.fileName(),QSettings::IniFormat);
		settings.beginGroup("UI");
		loadModelTree=settings.value("MODEL_TREE",true).toBool();
		loadSelection=settings.value("SELECTION_WIDGET",false).toBool();
		settings.endGroup();
	}
	// 模型树
	if(loadModelTree)
	{
		QDockWidget* modelDockWidget = new QDockWidget(mainWindow);
		modelDockWidget->setObjectName(QString::fromUtf8("modelTreeDockWidget"));
		mainWindow->addDockWidget(Qt::LeftDockWidgetArea, modelDockWidget);
		modelDockWidget->setWindowTitle(tr("Model"));

		ModelTreeWidget* modelTreeWidget=new ModelTreeWidget(mainWindow);
		_modelTreeWidget=modelTreeWidget;
		modelDockWidget->setWidget(modelTreeWidget);

		ModelDocument* doc=myDocument();
		ComTreeModel* model=new ComTreeModel(mainWindow);
		QTreeView* view=modelTreeWidget->getTreeView();

		modelTreeWidget->getTreeView()->setModel(model);
		connect(model,SIGNAL(structChanged()),view,SLOT(onStructChanged()));

		connect(MultiDocuments::instance(),SIGNAL(disableUIUpdating(bool)),
			this,SLOT(onDisableUIUpdating(bool)));
	}

	/// 选择信息树
	if(loadSelection)
	{
		QDockWidget* selectionDockWidget = new QDockWidget(mainWindow);
		selectionDockWidget->setObjectName(QString::fromUtf8("selectionDockWidget"));
		mainWindow->addDockWidget(Qt::RightDockWidgetArea, selectionDockWidget);
		selectionDockWidget->setWindowTitle(tr("Selections"));

		SelectionWidget* selectionWidget=new SelectionWidget(mainWindow);
		selectionDockWidget->setWidget(selectionWidget);
	}
}

void PREPUIPlugin::onDisableUIUpdating( bool b )
{
	_modelTreeWidget->setUpdatesEnabled(!b);
	_modelTreeWidget->getTreeView()->setUpdatesEnabled(!b);
}
