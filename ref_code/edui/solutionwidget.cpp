#include "solutionwidget.h"

#include "edcore/insproject.h"

#include <QInputDialog>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

SolutionWidget::SolutionWidget(QWidget *parent)
	: QTreeWidget(parent)
{
	createActions();

	setColumnCount(1);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),
		this,SLOT(onContextMenu(const QPoint&)));
	connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
		this,SLOT(onItemDoubleClicked(QTreeWidgetItem*,int)));

	updateTree();
	connect(INSProject::instance(),SIGNAL(projectUpdated()),
		this,SLOT(updateTree()));
}

SolutionWidget::~SolutionWidget()
{

}


QTreeWidgetItem* SolutionWidget::createTreeWidgetItem(QTreeWidgetItem* treeRoot,const INSEntity* enity)
{
	QTreeWidgetItem* newChild=new QTreeWidgetItem(treeRoot,QStringList(enity->getText()));
	newChild->setData(0,Qt::UserRole,quintptr(enity));
	if(INSProject::instance()->getStartupEntity()==enity){
		QFont font;
		font.setBold(true);
		newChild->setFont(0,font);
	}

	switch(enity->getType())
	{
	case INS_FOLDER:
		newChild->setIcon(0,QIcon(":/resources/menu/h008a.png"));
		break;
	case INS_FILE:
		newChild->setIcon(0,QIcon(":/resources/menu/h005a.png"));
		break;
	case INS_PROJECT:
		newChild->setIcon(0,QIcon(":/resources/menu/h002a.png"));
		break;
	}
	return newChild;
}

void SolutionWidget::updateTreeItem(QTreeWidgetItem* treeRoot,const INSEntity* entityRoot)
{
	const INSEntity* c=entityRoot;
	for(int i=0;i<c->getChildCount();++i)
	{
		QTreeWidgetItem* newChild=createTreeWidgetItem(treeRoot,c->getChild(i));
		updateTreeItem(newChild,c->getChild(i));
	}
}

void SolutionWidget::updateTree()
{
	this->clear();
	INSProject* project=INSProject::instance();

	if(project->isEmpty())
		return;

	_visibleRootItem=new QTreeWidgetItem(this);
	_visibleRootItem->setText(0,project->getProjectName());
	_visibleRootItem->setIcon(0,QIcon(":/resources/menu/h002a.png"));

	updateTreeItem(_visibleRootItem,project->getRootEntity());

	this->insertTopLevelItem(0, _visibleRootItem);

	/*
	QTreeWidgetItem* resultRoot=new QTreeWidgetItem(this);
	resultRoot->setText(0,"Result Cases");
	this->insertTopLevelItem(0,resultRoot);
	*/

	this->expandAll();
}

void SolutionWidget::onContextMenu( const QPoint& )
{
	QMenu myMenu;
	myMenu.addAction(_newFile);
	myMenu.addAction(_addFiles);
	myMenu.addAction(_addFolder);
	myMenu.addAction(_remove);
	myMenu.addAction(_setAsStartup);

	myMenu.exec(QCursor::pos());
}

void SolutionWidget::createActions()
{
	_newFile=new QAction(tr("New file"),this);
	connect(_newFile,SIGNAL(triggered()),this,SLOT(onNewFile()));

	_addFiles=new QAction(tr("Add files"),this);
	connect(_addFiles,SIGNAL(triggered()),this,SLOT(onAddFiles()));

	_addFolder=new QAction(tr("Add folder"),this);
	connect(_addFolder,SIGNAL(triggered()),this,SLOT(onAddFolder()));

	_remove=new QAction(tr("Remove"),this);
	connect(_remove,SIGNAL(triggered()),this,SLOT(onRemove()));

	_setAsStartup=new QAction(tr("Set as startup file"),this);
	connect(_setAsStartup,SIGNAL(triggered()),this,SLOT(onSetAsStartup()));
}

void SolutionWidget::addNewEntity(INSEntity* entity)
{
	INSProject* project=INSProject::instance();
	INSEntity* parentEntity=getSelectedEntity();
	if(!parentEntity)
		project->insertEntity(project->getRootEntity(),entity);
	else
		project->insertEntity(parentEntity,entity);
}

void SolutionWidget::onAddFiles()
{
	QStringList files = QFileDialog::getOpenFileNames(
		this,
		"Select one or more files",
		"",
		"files (*.ins *.stl *.tdy)");

	if(files.size()==0)
		return;

	INSProject* project=INSProject::instance();
	QDir projectDir(project->getProjectDir());
	for(int i=0;i<files.size();++i)
	{
		QString relativeName=projectDir.relativeFilePath(files[i]);
		INSEntity *newEntity=new INSEntity(INS_FILE,relativeName,relativeName);

		addNewEntity(newEntity);
	}

	project->setModified();
}

void SolutionWidget::onAddFolder()
{
	QString folderName=QInputDialog::getText(this,"Enter folder name","Folder name:");
	if(folderName.isEmpty())
		return;

	INSProject* project=INSProject::instance();
	INSEntity *newEntity=new INSEntity(INS_FOLDER,folderName);

	addNewEntity(newEntity);

	project->setModified();
}

void SolutionWidget::onRemove()
{
	INSProject* project=INSProject::instance();
	QList<INSEntity*> selections=getSelectedEntities();

	if(selections.size()==0)
		return;

	QMessageBox msgBox;
	msgBox.setText("Choose Remove to remove files from solution.\n\n"
		"Choose Delete to permanently delete files.");
	msgBox.setIcon(QMessageBox::Warning);

	QPushButton *removeButton = msgBox.addButton(tr("Remove"), QMessageBox::ActionRole);
	QPushButton *deleteButton = msgBox.addButton(tr("Delete"), QMessageBox::ActionRole);
	QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

	msgBox.exec();

	if (msgBox.clickedButton() == cancelButton)
		return;

	if (msgBox.clickedButton() == removeButton) {
		for(int i=0;i<selections.size();++i){
			project->removeEntity(selections[i]);
		}
		updateTree();
	}
	else if(msgBox.clickedButton() == deleteButton){
		for(int i=0;i<selections.size();++i){
			project->removeEntity(selections[i]);
		}
		updateTree();
	}
}

void SolutionWidget::onNewFile()
{
	QString newFileName=QInputDialog::getText(this,"Enter new file name","New file name:");
	if(newFileName.isEmpty())
		return;

	INSProject* project=INSProject::instance();
	INSEntity *newEntity=new INSEntity(INS_FILE,newFileName+".ins",newFileName+".ins");
	addNewEntity(newEntity);

	project->setModified();
}

void SolutionWidget::onItemDoubleClicked( QTreeWidgetItem * item, int column )
{
	INSEntity* realItem=(INSEntity*)item->data(0,Qt::UserRole).toULongLong();
	if(realItem)
		emit entityDoubleClicked(realItem);
}

INSEntity* SolutionWidget::getSelectedEntity()
{
	QList<QTreeWidgetItem*> selection=this->selectedItems();
	if(selection.size()>0){
		INSEntity* entity=(INSEntity*)selection[0]->data(0,Qt::UserRole).toULongLong();
		return entity;
	}
	return NULL;
}

QList<INSEntity*> SolutionWidget::getSelectedEntities()
{
	QList<INSEntity*> re;
	QList<QTreeWidgetItem*> selection=this->selectedItems();
	for(int i=0;i<selection.size();++i){
		INSEntity* entity=(INSEntity*)selection[i]->data(0,Qt::UserRole).toULongLong();
		if(entity)
			re.push_back(entity);
	}
	return re;
}

void SolutionWidget::onSetAsStartup()
{
	INSEntity* entity=getSelectedEntity();
	if(entity->getType()==INS_FILE){
		INSProject::instance()->setStartupEntity(entity);
	}

	updateTree();
}

