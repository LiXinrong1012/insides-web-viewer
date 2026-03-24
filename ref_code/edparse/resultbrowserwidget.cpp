#include "resultbrowserwidget.h"
#include "ui_resultbrowserwidget.h"

#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"
#include "edcore/result.h"

#include "editrichtextdialog.h"
#include <QtGui>

using namespace INSEditor;

ResultBrowserWidget::ResultBrowserWidget(QWidget *parent)
	: QWidget(parent)
	,_currentProgectName("All Projects")
	,_currentFilterProjectIndex(0)
	,_currentTagName("All Tags")
    ,_currentTagIndex(0)
{
	ui = new Ui::ResultBrowserWidget();
	ui->setupUi(this);

	createActions();

	ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->tableWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onContextMenu(const QPoint&)));

	Document* doc=Document::instance();
	connect(doc,SIGNAL(solutionClosed(Solution*)),this,SLOT(clearView()));
	connect(doc,SIGNAL(solutionCreated(Solution*)),this,SLOT(onSolutionOpened(Solution*)));
	initTags();
}

ResultBrowserWidget::~ResultBrowserWidget()
{
	delete ui;
}

void ResultBrowserWidget::onSolutionOpened( Solution* solution )
{
	connect(solution,SIGNAL(projectClosed(Project*)),this,SLOT(onProjectRemoved(Project*)));
	connect(solution,SIGNAL(projectCreated(Project*)),this,SLOT(onProjectAdded(Project*)));

	foreach(Project* project,solution->getAllProjects())
		connectProject(project);

	updateView();
}

void ResultBrowserWidget::updateView()
{
	clearView();

	Solution* solution=Document::instance()->getSolution();
	if(!solution)
		return;

	QList<Result*> resultList;

	ui->cbFilterProject->addItem("All Projects");
	QList<Project*> allProjects=solution->getAllProjects();

	ui->cbFilterProject->setCurrentIndex(_currentFilterProjectIndex);
	ui->cbFilterProject->adjustSize();

	ui->cbFilterTags->addItem("All Tags");
	for (int i=0;i<_tagActions.count();i++)
		ui->cbFilterTags->addItem(_tagActions[i]->text());
	
	ui->cbFilterTags->setCurrentIndex(_currentTagIndex);
	ui->cbFilterTags->adjustSize();

	connect(ui->cbFilterTags,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(onTagsCurrentIndexChanged(const QString&)));
	connect(ui->cbFilterTags,SIGNAL(currentIndexChanged(int)),this,SLOT(onTagsCurrentIndexChanged(int)));

	updatResultTableData(resultList);
	connect(ui->cbFilterProject,SIGNAL(currentIndexChanged ( const QString & )),this,SLOT(onFilterProjectCurrentIndexChanged ( const QString &  )));
	connect(ui->cbFilterProject,SIGNAL(currentIndexChanged( int )),this,SLOT(onFilterProjectCurrentIndexChanged( int )));
}

void ResultBrowserWidget::updatResultTableData( QList<Result*> list )
{
	//QTableWidget* tableWidget=ui->tableWidget;
	//QList<Result*> currentList;
	//int n =0;
	//if ((_currentProgectName == "All Projects")&& (_currentTagName=="All Tags"))
	//	n = list.count();
	//else if((_currentProgectName == "All Projects")&& (_currentTagName!="All Tags"))
	//{
	//	for (int i=0;i<list.count();i++)
	//	{
	//		QStringList tags = list[i]->getTags();
	//		if(tags.indexOf(_currentTagName) != -1)
	//		{
	//			currentList.push_back(list[i]);
	//			n++;
	//		}
	//	}
	//}
	//else if((_currentProgectName != "All Projects")&& (_currentTagName=="All Tags"))
	//{
	//	for (int i=0;i<list.count();i++)
	//	{
	//		if (list[i]->getProjectName()== _currentProgectName)
	//		{
	//			currentList.push_back(list[i]);
	//			n++;
	//		}
	//	}
	//}
	//else
	//{
	//	for (int i=0;i<list.count();i++)
	//	{
	//		QStringList tags = list[i]->getTags();
	//		if ((list[i]->getProjectName()== _currentProgectName) && (tags.indexOf(_currentTagName)!=-1))
	//		{
	//			currentList.push_back(list[i]);
	//			n++;
	//		}
	//	}
	//}
	//tableWidget->setRowCount(n);

	//int delta=1;
	//if ((_currentProgectName == "All Projects") &&(_currentTagName=="All Tags"))
	//{
	//	for(int i=0;i<n;++i){
	//		Result* result=list[i];
	//		QTableWidgetItem* newItem=new QTableWidgetItem(result->getName());
	//		newItem->setData(Qt::UserRole,quintptr(result));
	//		tableWidget->setItem(i,delta,newItem);
	//		tableWidget->setItem(i,delta+1,new QTableWidgetItem(result->getProjectName()));
	//		tableWidget->setItem(i,delta+2,new QTableWidgetItem(result->getCreateTimeStr()));
	//		tableWidget->setItem(i,delta+3,new QTableWidgetItem(result->getLastEditTimeStr()));
	//		tableWidget->setItem(i,delta+4,new QTableWidgetItem(result->getLog()));
	//	}
	//}
	//else
	//{
	//	for(int i=0;i<n;++i){
	//		Result* result=currentList[i];
	//		/*if(result->getProjectName() != _currentProgectName)
	//			continue;*/
	//		QTableWidgetItem* newItem=new QTableWidgetItem(result->getName());
	//		newItem->setData(Qt::UserRole,quintptr(result));
	//		tableWidget->setItem(i,delta,newItem);
	//		tableWidget->setItem(i,delta+1,new QTableWidgetItem(result->getProjectName()));
	//		tableWidget->setItem(i,delta+2,new QTableWidgetItem(result->getCreateTimeStr()));
	//		tableWidget->setItem(i,delta+3,new QTableWidgetItem(result->getLastEditTimeStr()));
	//		tableWidget->setItem(i,delta+4,new QTableWidgetItem(result->getLog()));
	//	}
	//}
	//
	//tableWidget->update();
}

void ResultBrowserWidget::clearView()
{
	QObject::disconnect ( ui->cbFilterProject,SIGNAL(currentIndexChanged ( const QString & )),this,SLOT(onFilterProjectCurrentIndexChanged ( const QString & ))) ;
	QObject::disconnect(ui->cbFilterProject,SIGNAL(currentIndexChanged( int )),this,SLOT(onFilterProjectCurrentIndexChanged(int)));

	QObject::disconnect(ui->cbFilterTags,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(onTagsCurrentIndexChanged(const QString&)));
	QObject::disconnect(ui->cbFilterTags,SIGNAL(currentIndexChanged(int)),this,SLOT(onTagsCurrentIndexChanged(int)));

	ui->cbFilterProject->clear();
	ui->cbFilterTags->clear();

	ui->tableWidget->clearContents();
}

void ResultBrowserWidget::onProjectAdded( Project* project )
{
	connectProject(project);
}

void ResultBrowserWidget::onProjectRemoved( Project* project )
{
}

void ResultBrowserWidget::onContextMenu( const QPoint& pos)
{
	initTags();
	QTableWidgetItem* clickedItem=ui->tableWidget->itemAt(pos);
	if(!clickedItem)
		return;
	int row = clickedItem->row();
	
	Result* r = (Result*)ui->tableWidget->item(row,1)->data(Qt::UserRole).toUInt();
	QStringList tags ;
	if(r)
		tags= r->getTags();

	QMenu myMenu;
	myMenu.addAction(_solveAction);
	myMenu.addAction(_openWithViewerAction);
	myMenu.addAction(_renameAction);
	myMenu.addAction(_editLogAction);
	myMenu.addAction(_backToProject);
	myMenu.addAction(_createNewProject);
	myMenu.addAction(_removeAction);

	myMenu.addAction(_newTagAction);
	QMenu* setTagMenu = new QMenu(tr("Set Tag"),this);
	for (int i=0;i<_tagActions.count();i++)
	{
		setTagMenu->addAction(_tagActions[i]);
		if(!tags.isEmpty())
		{
			if(tags.indexOf(_tagActions[i]->text()) !=-1)
				_tagActions[i]->setChecked(true);
			else
				_tagActions[i]->setChecked(false);
		}
	}
	myMenu.addMenu(setTagMenu);

	myMenu.exec(QCursor::pos());
}

void ResultBrowserWidget::connectProject(Project* project)
{
	connect(project,SIGNAL(resultAdded(Result*)),this,SLOT(updateView()));
	connect(project,SIGNAL(resultRemoved()),this,SLOT(updateView()));
}

void ResultBrowserWidget::createActions()
{
	_removeAction=new QAction(QIcon(":/resources/menu/a011-16.png"),tr("&Remove"),this);
	connect(_removeAction,SIGNAL(triggered()),this,SLOT(onRemove()));

	_openWithViewerAction=new QAction(QIcon(":/resources/menu/a001-16.png"),tr("&View"),this);
	connect(_openWithViewerAction,SIGNAL(triggered()),this,SLOT(onOpenWithViewer()));

	_solveAction=new QAction(QIcon(":/resources/menu/a014-16.png"),tr("&Solve"),this);
	connect(_solveAction,SIGNAL(triggered()),this,SLOT(onSolve()));

	_createNewProject=new QAction(QIcon(":/resources/menu/a008-16.png"),tr("&Create New Project"),this);

	_backToProject=new QAction(QIcon(":/resources/menu/a001-16.png"),tr("&Back to Project"),this);

	_renameAction=new QAction(QIcon(),tr("&Rename"),this);
	connect(_renameAction,SIGNAL(triggered()),this,SLOT(onRename()));

	_editLogAction=new QAction(QIcon(),tr("&Edit Log"),this);
	connect(_editLogAction,SIGNAL(triggered()),this,SLOT(onEditLog()));

	_openFolder=new QAction(QIcon(),tr("&Open Folder in Explorer"),this);
	connect(_openFolder,SIGNAL(triggered()),this,SLOT(onOpenWithExplorer()));

	_newTagAction = new QAction(QIcon(),tr("New Tag"),this);
	connect(_newTagAction,SIGNAL(triggered()),this,SLOT(onCreateNewTag()));
}

Result* ResultBrowserWidget::getCurrentResult()
{
	QTableWidget* tableWidget=ui->tableWidget;
	int row=tableWidget->currentRow();
	if(row<0)
		return NULL;

	Result* result=(Result*)tableWidget->item(row,1)->data(Qt::UserRole).toULongLong();
	return result;
}

void ResultBrowserWidget::onRemove()
{
	Result* result=getCurrentResult();
	if(!result)
		return;

	updateView();
}

void ResultBrowserWidget::onSolve()
{
	// get current project
	Project* currentProject=NULL;

	if(currentProject)
		currentProject->openWithSolver();
}

void ResultBrowserWidget::onOpenWithViewer()
{
	// get current project
	Project* currentProject=NULL;

	if(currentProject)
		currentProject->openWithViewer();
}

void ResultBrowserWidget::onOpenWithExplorer()
{
	Result* result=getCurrentResult();
	if(!result)
		return;
}


void ResultBrowserWidget::onEditLog()
{
	Result* result=getCurrentResult();
	if(!result)
		return;

	//QString newName=EditRichTextDialog::getText(0,tr("Edit Log"),tr("Edit log content:"),result->getLog());
	//if(newName.isEmpty())
		//return;

	//result->setLog(newName);
	updateView();
}

void ResultBrowserWidget::onFilterProjectCurrentIndexChanged( const QString & text )
{
	_currentProgectName = text;
	updateView();
}

void ResultBrowserWidget::onFilterProjectCurrentIndexChanged( int index )
{
	_currentFilterProjectIndex = index;
}

void ResultBrowserWidget::onCreateNewTag()
{
	QString tagName = QInputDialog::getText(this,tr("New Tag"),tr("New Tag Name"));
	if(tagName.isEmpty())
		return;

	QAction* tagAction = new QAction(QIcon(),tagName,this);
	connect(tagAction,SIGNAL(triggered()),this,SLOT(onSetTags()));
	_tagActions.push_back(tagAction);
}

///获得当前result条目设置tags;
void ResultBrowserWidget::onSetTags()
{
	QAction* tempTagAction = static_cast<QAction*>(sender());
	Result* result = getCurrentResult();
	QStringList tags = result->getTags();
	if (tags.indexOf(tempTagAction->text()) != -1)
	{
		tags.removeOne(tempTagAction->text());
//		tempTagAction->setChecked(false);
		result->setTags(tags);
	}
	else
	{
		tags<<tempTagAction->text();
//		tempTagAction->setChecked(true);
		result->setTags(tags);
	}	
}

void ResultBrowserWidget::initTags()
{
	_tagActions.clear();
	for (int i= 0;i<3;i++)
	{
		QAction* tempTag = new QAction("Tag "+QString::number(i),this);
		connect(tempTag,SIGNAL(triggered()),this,SLOT(onSetTags()));
		tempTag->setCheckable(true);
		_tagActions.push_back(tempTag);
	}
}

void ResultBrowserWidget::onTagsCurrentIndexChanged( const QString& text )
{
	_currentTagName = text;
	updateView();
}

void ResultBrowserWidget::onTagsCurrentIndexChanged( int index )
{
	_currentTagIndex = index;
}
