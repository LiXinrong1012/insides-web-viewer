#include "modeltreewidget.h"
#include "ui_modeltreewidget.h"

#include "modelsearchtablemodel.h"

#include <QtGui>

#include "treeheadermodificationdialog.h"

#include "mtsearchengine/mtsearchengine.h"
#include "mtsearchengine/imodelsearchtoolbar.h"

using namespace INSIDES;

ModelTreeWidget::ModelTreeWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ModelTreeWidget();
	ui->setupUi(this);

	ui->tableView->horizontalHeader()->setVisible(false);
	connect(ui->treeView->header(),SIGNAL(sectionResized (int, int, int)),
		this,SLOT(onTreeSectionResized(int,int,int)));
	

	QDir pluginsDir(qApp->applicationDirPath());

	{
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("mtsearchengine.dll"));
		QObject *plugin = pluginLoader.instance();

		if (plugin){
			MTSearchEngine* uiPlugin=qobject_cast<MTSearchEngine*>(plugin);
			IModelSearchToolbar* toolbar=uiPlugin->newSearchToolbar(this);
			if(toolbar){
				ui->titleLayout->addWidget(toolbar);
				ModelSearchTableModel* aModel=(ModelSearchTableModel*)ui->tableView->model();
				connect(toolbar,SIGNAL(reqUpdate(const QList<BaseItem*>&)),
					this,SLOT(updateSearchResult(const QList<BaseItem*>&)));
			}
		}
	}

	/*
	connect(ui->btnSearch,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
	connect(ui->cbSearchText,SIGNAL(activated(int)),
		this,SLOT(onEnterClicked()));

	connect(this,SIGNAL(showSearchOptionClicked()),
		this,SLOT(showSearchOptions()));
	connect(this,SIGNAL(searchOptionChanged(const QString&)),
		this,SLOT(onSearchKeywordChanged(const QString&)));
		*/

	connect(ui->btnSort,SIGNAL(clicked()),this,SLOT(onSort()));
	connect(ui->btnHeaders,SIGNAL(clicked()),this,SLOT(onShowHeaderSettings()));

	ui->tableView->hide();
}

ModelTreeWidget::~ModelTreeWidget()
{
	delete ui;
}


QTreeView* ModelTreeWidget::getTreeView()
{
	return ui->treeView;
}


void ModelTreeWidget::onTreeSectionResized( int logicalIndex,int oldSize,int newSize )
{
	ui->tableView->horizontalHeader()->resizeSection(logicalIndex,newSize);
}

void ModelTreeWidget::onSort()
{
	//ui->treeView->setSortingEnabled(true);
}

void ModelTreeWidget::onShowHeaderSettings()
{
	TreeHeaderModificationDialog dlg(this,(ComTreeModel*)ui->treeView->model());
	dlg.exec();
}

void ModelTreeWidget::updateSearchResult( const QList<BaseItem*>& vec )
{
	QAbstractItemModel* tmpModel=ui->tableView->model();
	if(tmpModel){
		ModelSearchTableModel* aModel=(ModelSearchTableModel*)tmpModel;
		aModel->updateSearchResult(vec);

		if(!ui->tableView->isVisible())
			ui->tableView->show();
	}
}
