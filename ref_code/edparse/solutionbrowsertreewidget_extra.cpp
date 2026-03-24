#include "solutionbrowsertreewidget.h"  

#include "edcore/document.h"
#include "edcore/project.h"
#include "edcore/solution.h"
#include "edcore/filemanager.h"
#include "edcore/viewerprocess.h"

#include "parameteranalysisdialog.h"
#include "solvermanagerdialog.h"
#include "tagmanagedialog.h"
#include "batfilemanager.h"

#include "insviewer/socketservermessage.h"

#include <QUuid>
#include <QtGui>
#include <QtCore>
#include <QFileInfoList>

#include <Windows.h>

QList<HWND> hwndList; 
void SolutionBrowserTreeWidget::onAddFileFolder()
{
	QTreeWidgetItem* curr=currentItem();
	if(!isCertainType(curr,Type_Project) && !isCertainType(curr,Type_FileFolder))
		return;

	QString folderName=QInputDialog::getText(this,tr("New Solution Folder"),
		tr("Enter new solution folder name:"));
	if(folderName.isEmpty())
		return;

	QStringList currentFileFolder=getSelectedFolder(Type_FileFolder);
	QTreeWidgetItem* currentFolderItem=curr;
	QTreeWidgetItem* currentProjectItem=getParentProjectTreeItem(curr);
	Project* project = getSelectedProject();

	if(!currentFileFolder.isEmpty())
		currentFolderItem=getOrCreateFolderTreeWidgetItem(currentProjectItem,currentFileFolder);

	QStringList tmpTestExist;
	tmpTestExist<<currentFileFolder<<folderName;
	if(getOrCreateFolderTreeWidgetItem(currentProjectItem,tmpTestExist,false)){
		QMessageBox::warning(0,tr("Error"),tr("There already have an existed folder with the same name."));
		return;
	}

	getOrCreateFolderTreeWidgetItem(currentProjectItem,tmpTestExist,true);
	/////
	QList<Project*> pList = INSEditor::Document::instance()->getSolution()->getAllProjects();
	for (int i=0;i<pList.count();i++)
		pList[i]->setEmptyFolders(getAllEmptyFolders(pList[i]));
}

void SolutionBrowserTreeWidget::onAddSolutionFolder()
{
	QTreeWidgetItem* curr=currentItem();
	if(!isCertainType(curr,Type_Solution) && !isCertainType(curr,Type_SolutionFolder))
		return;

	QString folderName=QInputDialog::getText(this,tr("New Solution Folder"),
		tr("Enter new solution folder name:"));
	if(folderName.isEmpty())
		return;

	QStringList currentSolutionFolder=getSelectedFolder(Type_SolutionFolder);
	QTreeWidgetItem* currentFolderItem=curr;
	if(!currentSolutionFolder.isEmpty())
		currentFolderItem=getOrCreateFolderTreeWidgetItem(_solutionRootItem,currentSolutionFolder);

	QStringList tmpTestExist;
	tmpTestExist<<currentSolutionFolder<<folderName;
	if(getOrCreateFolderTreeWidgetItem(_solutionRootItem,tmpTestExist,false)){
		QMessageBox::warning(0,tr("Error"),tr("There already have an existed folder with the same name."));
		return;
	}

	getOrCreateFolderTreeWidgetItem(_solutionRootItem,tmpTestExist,true);
}

void SolutionBrowserTreeWidget::onContextMenu( const QPoint& pos)
{
	QTreeWidgetItem* clickItem=itemAt(pos);
	if(!clickItem)
		return;

	int type=clickItem->data(0,DataRole_Type).toInt();
	switch(type)
	{
	case Type_Solution:
		showContextMenuOnSolution();
		break;
	case Type_SolutionFolder:
		showContextMenuOnProjectFolder();
		break;
	case  Type_Project:
		showContextMenuOnProject();
		break;
	case  Type_FileFolder:
		showContextMenuOnProjectFolder();
		break;
	case  Type_File:
		showContextMenuOnFile();
		break;
	default:
		;
	}
}

void SolutionBrowserTreeWidget::showContextMenuOnSolution()
{
	QMenu myMenu;
	_addMenu->clear();
	
	_addMenu->addAction(_newProjectAction);
	_addMenu->addAction(_addExistingProjectAction);
	_addMenu->addAction(_newProjectFolderAction);
	
	myMenu.addMenu(_addMenu);
	myMenu.addAction(_pasteAction);
	myMenu.addAction(_addAllFilesToSVNAction);
	myMenu.addAction(_reloadAction);

	myMenu.exec(QCursor::pos());
}

void SolutionBrowserTreeWidget::showContextMenuOnProject()
{
	Project* project = (Project*)currentItem()->data(0,DataRole_PTR).toULongLong();
	QList<QTreeWidgetItem*>itemList = this->selectedItems();
	QList<Project*> proList;
	foreach(QTreeWidgetItem* item,itemList)
	{
		if(item->data(0,DataRole_Type).toInt()== Type_Project)
			proList.push_back((Project*)item->data(0,DataRole_PTR).toULongLong());
	}
	QMenu myMenu;
	QMenu* setTagMenu = new QMenu(tr("Set Tag"));
	if(project->isValid())
	{
		QStringList tags = proList[0]->getTags();
		
		myMenu.addAction(_buildAction);
		myMenu.addAction(_solveAction);
		myMenu.addAction(_openWithViewer);
		myMenu.addAction(_openResultWithViewer);

		myMenu.addAction(_openInExplorerAction);
		_addMenu->clear();

		_addMenu->addAction(_newItemAction);
		_addMenu->addAction(_addExistingItemsAction);
		_addMenu->addAction(_newFileFolderAction);

		myMenu.addMenu(_addMenu);
		myMenu.addAction(_copyProjectAction);
		myMenu.addAction(_exhaustionParameterAction);
		myMenu.addAction(_batchSolveAction);

		myMenu.addAction(_renameAction);
		myMenu.addAction(_removeAction);
		myMenu.addAction(_reloadAction);
		myMenu.addAction(_addAllFilesToSVNAction);

		QStringList allTags=project->getSolution()->getTagList();
		if(allTags.size())
		{
			foreach(QString tag,allTags)
			{
				QAction* tmpAction=setTagMenu->addAction(tag,this,SLOT(onSetTags()));
				tmpAction->setCheckable(true);
				if(tags.contains(tag))
					tmpAction->setChecked(true);
				else
					tmpAction->setChecked(false);
			}
			
			myMenu.addMenu(setTagMenu);
		}
		myMenu.addAction(_editTagAction);
	}
	else
	{
		myMenu.addAction(_removeAction);
		myMenu.addAction(_reloadAction);
	}
	myMenu.exec(QCursor::pos());
	delete setTagMenu;
}

void SolutionBrowserTreeWidget::showContextMenuOnProjectFolder()
{
	QMenu myMenu;
	_addMenu->clear();

	_addMenu->addAction(_newProjectAction);
	_addMenu->addAction(_addExistingProjectAction);
	_addMenu->addAction(_newProjectFolderAction);

	myMenu.addMenu(_addMenu);
	myMenu.addAction(_pasteAction);
	myMenu.addAction(_removeAction);
	myMenu.addAction(_renameAction);
	myMenu.addAction(_addAllFilesToSVNAction);

	myMenu.exec(QCursor::pos());
}

void SolutionBrowserTreeWidget::showContextMenuOnFileFolder()
{
	QMenu myMenu;
	_addMenu->clear();

	_addMenu->addAction(_newItemAction);
	_addMenu->addAction(_addExistingItemsAction);
	_addMenu->addAction(_newFileFolderAction);

	myMenu.addMenu(_addMenu);
	//myMenu.addAction(_copyAction);
	//myMenu.addAction(_cutAction);
	//myMenu.addAction(_pasteAction);
	myMenu.addAction(_removeAction);
	myMenu.addAction(_renameAction);
	myMenu.addAction(_addAllFilesToSVNAction);

	myMenu.exec(QCursor::pos());
}

void SolutionBrowserTreeWidget::showContextMenuOnFile()
{
	QMenu myMenu;
	Entity* currentEntity = (Entity*)currentItem()->data(0,DataRole_PTR).toULongLong();
	if(currentEntity->isValid())
	{
		myMenu.addAction(_openWithAction);
		myMenu.addAction(_openInExplorerAction);
		myMenu.addAction(_compareAction);
		myMenu.addAction(_openWithViewer);
		myMenu.addAction(_buildAction);
		_addMenu->clear();

		//myMenu.addAction(_copyAction);
		//myMenu.addAction(_cutAction);
		//myMenu.addAction(_pasteAction);
		myMenu.addAction(_setAsStartupFileAction);
		myMenu.addAction(_renameAction);
		myMenu.addAction(_removeAction);
		myMenu.addAction(_reloadAction);
		myMenu.addAction(_copyFileAction);
		myMenu.addAction(_addAllFilesToSVNAction);

		myMenu.exec(QCursor::pos());
	}
	else
	{
		myMenu.addAction(_removeAction);
		myMenu.addAction(_reloadAction);

		myMenu.exec(QCursor::pos());
	}
}

void SolutionBrowserTreeWidget::onRemove()
{
	QList<QTreeWidgetItem*> itemList=this->selectedItems();
	if(itemList.count()==0)
		return;
	int typeId = itemList[0]->data(0,DataRole_Type).toInt();
	for (int i=0;i<itemList.count();i++)
	{
		if(typeId != itemList[i]->data(0,DataRole_Type).toInt())
			return;
	}
	switch (typeId)
	{
	case Type_SolutionFolder:
		onRemoveProjectFolder();
		break;
	case Type_FileFolder:
		onRemoveFileFolder();
		break;
	case Type_Project:
		onRemoveProject();
		break;
	case Type_File:
		onRemoveFile();
		break;
	}
}

void SolutionBrowserTreeWidget::onRemoveProjectFolder()
{
	QString delFolder = currentItem()->text(0);

	Solution *solution = INSEditor::Document::instance()->getSolution();
	QList<Project*> projectList = solution->getAllProjects();
	for (int i=0;i<projectList.count();i++)
	{
		QStringList tempFolders = projectList[i]->getFolders();
		if (tempFolders.indexOf(delFolder) != -1)
		{
			tempFolders.removeOne(delFolder);
			projectList[i]->setFolders(tempFolders);
		}
	}
	updateView();
}

void SolutionBrowserTreeWidget::onRemoveFileFolder()
{
	QString folder = currentItem()->text(0);
	Project* project = getSelectedProject();
	QTreeWidgetItem* projectTreeItem = getParentProjectTreeItem(currentItem());
	if (!project || folder.isEmpty())
		return;
	QMessageBox msgBox;
	msgBox.setText(tr("Choose Remove to remove folder from project.\n\n"));
	msgBox.setIcon(QMessageBox::Warning);

	QPushButton *removeButton = msgBox.addButton(tr("Remove"), QMessageBox::ActionRole);
	QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

	msgBox.exec();

	if(msgBox.clickedButton() == removeButton)
	{
		if(currentItem()->childCount()==0)
		{
			QStringList list = project->getEmptyFolders();
			list.removeOne(folder);
			project->setEmptyFolders(list);
		}
		else
		{
			QList<Entity*> entityList = project->getEntities();
			foreach(Entity* entity ,entityList)
			{
				QStringList folders = entity->getFolders();
				folders.removeOne(folder);
				entity->setFolders(folders);
			}
		}
	}
	else
		return

	updateProject(project);
}


bool DeleteDirectory(const QString &path) 
{ 
	if (path.isEmpty()) 
		return false;

	QDir dir(path); 
	if(!dir.exists()) 
		return true;

	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); 
	QFileInfoList fileList = dir.entryInfoList(); 
	foreach (QFileInfo fi, fileList) 
	{ 
		if (fi.isFile()) 
			fi.dir().remove(fi.fileName()); 
		else 
			DeleteDirectory(fi.absoluteFilePath()); 
	} 

	return dir.rmpath(dir.absolutePath()); 
}

void SolutionBrowserTreeWidget::onRemoveProject()
{
	QList<Project*> projectList;
	QList<QTreeWidgetItem*> itemList = this->selectedItems();
	for (int i=0;i<itemList.count();i++)
	{
		Project* project = (Project*)itemList[i]->data(0,DataRole_PTR).toULongLong();
		projectList.push_back(project);
	}

	QMessageBox msgBox;
	msgBox.setText(tr("Choose Remove to remove project from solution.<br><br><b>Choose Delete to permanently delete this project.</b>"));
	msgBox.setIcon(QMessageBox::Warning);
	
	QPushButton *removeButton = msgBox.addButton(tr("Remove"), QMessageBox::ActionRole);
	QPushButton *deleteButton = msgBox.addButton(tr("Delete"), QMessageBox::ActionRole);
	QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

	msgBox.exec();

	if (msgBox.clickedButton() == removeButton)
	{
		for (int i=0;i<projectList.count();i++)
			INSEditor::Document::instance()->getSolution()->removeProject(projectList[i]);
	}
	else if(msgBox.clickedButton()== deleteButton)
	{
		for(int i=0;i<projectList.count();i++)
		{
			QString s = projectList[i]->getDirectory();
			INSEditor::Document::instance()->getSolution()->removeProject(projectList[i]);
			DeleteDirectory(s);
			//deleteDirFromDisk(s);
		}
	}
	else
		return;

	INSEditor::Document::instance()->getSolution()->save();
	updateView();
}

void SolutionBrowserTreeWidget::onRemoveFile()
{
	QList<QTreeWidgetItem*> itemList = this->selectedItems();
	QList<Entity*> selectedEntityList;
	for(int i=0;i<itemList.count();i++)
	{
		Entity* entity = (Entity*)itemList[i]->data(0,DataRole_PTR).toULongLong();
		selectedEntityList.push_back(entity);
	}

	Project* selectedProject = getSelectedProject();
	QTreeWidgetItem* projectTreeItem = getParentProjectTreeItem(currentItem());
	if(selectedEntityList.isEmpty())
		return;

	QMessageBox msgBox;
	msgBox.setText(tr("Choose Remove to remove file from project.\n\n")+
		tr("Choose Delete to permanently delete this file."));
	msgBox.setIcon(QMessageBox::Warning);

	QPushButton *removeButton = msgBox.addButton(tr("Remove"), QMessageBox::ActionRole);
	QPushButton *deleteButton = msgBox.addButton(tr("Delete"), QMessageBox::ActionRole);
	QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

	msgBox.exec();

	if (msgBox.clickedButton()==removeButton)
	{
		for (int i=0;i<selectedEntityList.count();i++)
			selectedProject->removeEntity(selectedEntityList[i]);
	}
	else if(msgBox.clickedButton()==deleteButton)
	{
		for(int i=0;i<selectedEntityList.count();i++)
		{
			QString s = selectedEntityList[i]->getFullFileName();
			selectedProject->removeEntity(selectedEntityList[i]);
			QFile::remove(s);
		}
	}
	else
		return;

	updateProject(selectedProject);

	INSEditor::Document::instance()->getSolution()->save();
}

void SolutionBrowserTreeWidget::mouseDoubleClickEvent( QMouseEvent * event )
{
	Entity* entity = getSelectedEntity();
	if(!entity)
		return QTreeWidget::mouseDoubleClickEvent(event);
	
	onOpen();
	FileManager::instance()->notifyUpdateIcon();
}

void SolutionBrowserTreeWidget::onRename()
{
	int typeId = this->currentItem()->data(0,DataRole_Type).toInt();
	
	QStringList folderList = getSelectedFolder(Type_FileFolder);
	QStringList solutionFolder = getSelectedFolder(Type_SolutionFolder);
	Entity* entity = getSelectedEntity();
	Project* project = getSelectedProject(currentItem());
	if(folderList.isEmpty() && solutionFolder.isEmpty() && !entity && !project)
		return;

	_currItem = currentItem();
	_renameLineEdit = new QLineEdit(_currItem->text(0),this);
	_renameLineEdit->installEventFilter(this);
	_renameLineEdit->setFocus();
	_renameLineEdit->setSelection(0,_renameLineEdit->text().size());
	_renameLineEdit->setStyleSheet("selection-color: yellow;");
	this->setItemWidget(_currItem,0,_renameLineEdit);
	connect(_renameLineEdit,SIGNAL(textChanged ( const QString &  )),this,SLOT(onTextChanged ( const QString &  )));

	_renameEditIsEdited = true;

	if (typeId==Type_FileFolder)
		connect(_renameLineEdit,SIGNAL(returnPressed()),this,SLOT(onFileFolderEditFinished()));
	else if(typeId == Type_SolutionFolder)
		connect(_renameLineEdit,SIGNAL(returnPressed()),this,SLOT(onProjectFolderEditFinished()));
	else if(typeId == Type_Project)
	{
		_currProject = getSelectedProject(currentItem());
		connect(_renameLineEdit,SIGNAL(returnPressed()),this,SLOT(onProjectEditFinished()));
	}
	else if (typeId== Type_File)
	{
		_currEntity = getSelectedEntity();
		connect(_renameLineEdit,SIGNAL(returnPressed()),this,SLOT(onFileEditFinished()));
	}
	else 
		return;
}

void SolutionBrowserTreeWidget::onCompile()
{
	FileManager::instance()->notifyBuildProject();
}

void SolutionBrowserTreeWidget::onOpenWith()
{
	Entity* entity=getSelectedEntity();
	if(!entity)
		return;

	QString fullName=entity->getFullFileName();
	//	_watcher->addPath(fullName);
	QString path = QString("file:///") + fullName;
	bool is_open = QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}

void SolutionBrowserTreeWidget::onOpen()
{
	Entity* entity=getSelectedEntity();
	QTreeWidgetItem* item = getCursorItem();
	if(!entity || !item)
		return;

	QString fullName=entity->getFullFileName();
	QFileInfo info(fullName);
	QString suf = info.suffix();
	if(suf.compare("ins",Qt::CaseInsensitive) == 0 || suf.compare("tdy",Qt::CaseInsensitive) == 0)
		FileManager::instance()->notifyOpenFile(fullName);
	else
		onOpenWith();
}

void SolutionBrowserTreeWidget::onReload()
{
	int typeId = currentItem()->data(0,DataRole_Type).toInt();
	switch (typeId)
	{
	case Type_Solution:
		{
			INSEditor::Document::instance()->getSolution()->reload();
			QList<Project*> proList = INSEditor::Document::instance()->getSolution()->getAllProjects();
			for (int i=0;i<proList.count();i++)
				updateProject(proList[i]);
		}
		break;
	case Type_Project:
		{
			Project* pro = (Project*)currentItem()->data(0,DataRole_PTR).toULongLong();
			pro->reload();
			updateProject(pro);
		}
		break;
	case Type_File:
		{
			Entity* entity = (Entity*)currentItem()->data(0,DataRole_PTR).toULongLong();
			entity->reload();
			Project* pro = entity->getProject();
			updateProject(pro);
		}
		break;
	}
}
///文件一键添加到SVN
void SolutionBrowserTreeWidget::onAddAllFilesToSVN()
{
	QTreeWidgetItem* cuItem = currentItem();
	int typeId = cuItem->data(0,DataRole_Type).toInt();

	QMessageBox msgBox;
	msgBox.setText("Are you sure add selected files to SVN");
	msgBox.setIcon(QMessageBox::Warning);

	QPushButton *submitButton = msgBox.addButton(tr("Add"), QMessageBox::ActionRole);
	QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

	msgBox.exec();

	if (msgBox.clickedButton() == submitButton)
	{
		QString logsText;

		QStringList entityFullNameList;
		QString arguments;
		switch (typeId)
		{
		case Type_File:
			{
				//多选多个文件
				QList<QTreeWidgetItem*> items = this->selectedItems();

				QString dirStr = getSelectedProject()->getDirectory();
				arguments = "svn add ";

				//添加命令
				foreach(QTreeWidgetItem* item,items)
				{
					int tmpTypeId = item->data(0,DataRole_Type).toInt();
					if(typeId == Type_File)
					{
						Entity* tmpEntity = (Entity*)item->data(0,DataRole_PTR).toULongLong();
						if(!tmpEntity)
							continue;

						arguments +=QString("\"%1\" ").arg(tmpEntity->getFullFileName()) ;
						entityFullNameList<<QString("\"%1\" ").arg(tmpEntity->getFullFileName()) ;
					}
				}
				arguments += QString("\n svn commit -m \"%1\" ").arg(logsText);
			}
			break;
		case Type_FileFolder:
			{
				Project* pro = getSelectedProject();
				QString text = currentItem()->text(0);
				QList<Entity*> entityList = pro->getEntities();
				QString dirStr = getSelectedProject()->getDirectory();

				//添加命令
				arguments = "svn add ";
				foreach(Entity* tmp,entityList)
				{
					if(tmp->getFolders().contains(text,Qt::CaseInsensitive))
						arguments += QString("\"%1\" ").arg(tmp->getFullFileName());
				}
			}
			break;
		case Type_Project:
			{
				QList<QTreeWidgetItem*> list = this->selectedItems();
				QList<Project*> proList ;
				foreach(QTreeWidgetItem* item,list)
				{
					int typeId = item->data(0,DataRole_Type).toInt();
					if(typeId == Type_Project)
						proList<<(Project*)item->data(0,DataRole_PTR).toULongLong();
				}

				arguments = "svn add ";
				entityFullNameList << QString("\"%1\" ").arg(logsText);
				foreach(Project* pro,proList)
				{
					arguments += QString("\"%1\" --depth empty ").arg(pro->getDirectory());
					entityFullNameList<<QString("\"%1\" --depth empty ").arg(pro->getDirectory());

					arguments += QString("\"%1\" ").arg(pro->getProjectFileName());
					entityFullNameList<<QString("\"%1\" ").arg(pro->getProjectFileName());

					QList<Entity*> entityList = pro->getEntities();
					foreach(Entity* tmp,entityList)
					{
						arguments += QString("\"%1\" ").arg(tmp->getFullFileName()) ;
						entityFullNameList<<QString("\"%1\" ").arg(tmp->getFullFileName());
					}
				}
			}
			break;
		case Type_Solution:
			{
				QString dirStr = INSEditor::Document::instance()->getSolution()->getSolutionDirectory();
				arguments = QString("svn add \"%1\" --depth empty ").arg(INSEditor::Document::instance()->getSolution()->getSolutionDirectory());
				entityFullNameList<<QString("%1 --depth empty ").arg(INSEditor::Document::instance()->getSolution()->getSolutionDirectory());

				arguments += QString("\"%1\" ").arg(INSEditor::Document::instance()->getSolution()->getSolutionFullName());
				entityFullNameList<<QString("\"%1\" ").arg(INSEditor::Document::instance()->getSolution()->getSolutionFullName());

				QList<Project*> projects = INSEditor::Document::instance()->getSolution()->getAllProjects();
				foreach(Project* pro,projects)
				{
					arguments += QString("\"%1\" --depth empty ").arg(pro->getDirectory());
					entityFullNameList<<QString("\"%1\" --depth empty ").arg(pro->getDirectory());

					arguments += QString("\"%1\" ").arg(pro->getProjectFileName());
					entityFullNameList<<QString("\"%1\" ").arg(pro->getProjectFileName());

					QList<Entity*> entityList = pro->getEntities();
					foreach(Entity* tmp,entityList)
					{
						arguments += QString("\"%1\" ").arg(tmp->getFullFileName()) ;
						entityFullNameList<<QString("\"%1\" ").arg(tmp->getFullFileName());
					}
				}
			}
			break;
		case Type_SolutionFolder:
			{
				QString text = currentItem()->text(0);
				QList<Project*> projects = INSEditor::Document::instance()->getSolution()->getAllProjects();
				arguments = "svn add ";
				entityFullNameList << QString("\"%1\" ").arg(logsText);
				foreach(Project* pro,projects)
				{
					if(pro->getFolders().contains(text,Qt::CaseInsensitive))
					{
						arguments += QString("\"%1\" --depth empty ").arg(pro->getDirectory());
						entityFullNameList<<QString("\"%1\" --depth empty ").arg(pro->getDirectory());

						arguments += QString("\"%1\" ").arg(pro->getProjectFileName());
						entityFullNameList<<QString("\"%1\" ").arg(pro->getProjectFileName());

						QList<Entity*> entityList = pro->getEntities();
						foreach(Entity* tmp,entityList)
						{
							arguments += QString("\"%1\" ").arg(tmp->getFullFileName()) ;
							entityFullNameList<<QString("\"%1\" ").arg(tmp->getFullFileName());
						}
					}
				}
			}
			break;
		}

		QDir dir;
		dir.setCurrent(qApp->applicationDirPath());
		dir.mkdir("tmp");
		QThread* thread = new BatFileManager(qApp->applicationDirPath()+"/tmp/tmpsvn.bat",entityFullNameList);
		connect(thread,SIGNAL(finished()),this,SLOT(showMessageBox()));
		thread->start();
	}
	else
		return;
}

void SolutionBrowserTreeWidget::showMessageBox()
{
	Sleep(2000);
	QMessageBox::information(0,"Add Finish","Add finish !");

	updateView();
}

void SolutionBrowserTreeWidget::onSetAsStartupEntity()
{
	Entity* entity=getSelectedEntity();
	Project* project=getSelectedProject();
	if(!entity || !project)
		return;

	project->setStartupEntity(entity);
	updateProject(project);
}

void SolutionBrowserTreeWidget::onOpenInExplorer()
{
	int typeId = currentItem()->data(0,DataRole_Type).toInt();
	if(typeId == Type_File)
	{
		Entity* entity=(Entity*)currentItem()->data(0,DataRole_PTR).toULongLong();
		QString fullName=entity->getFullFileName();

		QProcess *process = new QProcess;
		QStringList strList;
		fullName.replace("/","\\");
		strList<<"/select," << "/select," + fullName;
		process->start("Explorer", strList);
	}
	else
	{
		Project* project = (Project*)currentItem()->data(0,DataRole_PTR).toULongLong();
		QString fullName = project->getDirectory();
		QDesktopServices::openUrl(fullName);
	}
}

///比较选中的文件
void SolutionBrowserTreeWidget::onCompareFiles()
{
	INSEditor::ApplicationProperty* pros=INSEditor::Document::instance()->getProperties();
	QString appName;
	if(pros)
		appName=pros->fileDiffExecutablePath;
	if(appName.isEmpty()){
		QDir dir(qApp->applicationDirPath());
		appName=dir.absoluteFilePath("winDiff.exe");
	}

	// get names
	QStringList arguments;
	QList<QTreeWidgetItem*> itemList = this->selectedItems();
	foreach(QTreeWidgetItem* item,selectedItems())
	{
		if(isCertainType(item,Type_File))
		{
			Entity* entity = (Entity*)item->data(0,DataRole_PTR).toULongLong();
			arguments<<entity->getFullFileName();
		}
		if(arguments.size()==2)
			break;
	}

	QFileInfo info(arguments[0]);
	QString path=info.absolutePath();

	if(appName.endsWith("gvim.exe",Qt::CaseInsensitive))
		arguments.push_front("-d");

	QProcess::startDetached(appName,arguments,path);
}

void SolutionBrowserTreeWidget::onNewFile()
{
	Project* project=getSelectedProject();
	if(!project)
		return;

	QString fileName=QInputDialog::getText(0,tr("New File"),tr("Enter New File Name:"));
	if(fileName.isEmpty())
		return;

	QString fileFullname=project->getDirectory()+fileName;
	Entity* oldOne=project->getEntityByFullFilename(fileFullname);
	if(oldOne)
	{
		QMessageBox::warning(this,tr("Warning"),
			tr("The file cannot be created because there already exist one with the same name."));
		return;
	}

	QFile file(fileFullname);
	file.open(QFile::WriteOnly);
	file.close();

	QStringList fileFolder=getSelectedFolder(Type_FileFolder);
	Entity* entity=new Entity(project->getDirectory()+fileName);
	entity->setFolders(fileFolder);
	project->addEntity(entity);
	updateProject(project);

	QList<Project*> pList = INSEditor::Document::instance()->getSolution()->getAllProjects();
	for (int i=0;i<pList.count();i++)
		pList[i]->setEmptyFolders(getAllEmptyFolders(pList[i]));
}

void SolutionBrowserTreeWidget::onCopyFile()
{
	Entity* entity = (Entity*)currentItem()->data(0,DataRole_PTR).toULongLong();
	Project* pro = entity->getProject();
	QString newFullFileName;
	int num =1;
	while(true)
	{
		QFileInfo info(entity->getFullFileName());
		QString path = info.path();
		QString ext = info.suffix();
		QString name = info.baseName();
		QString newFullName = path +"/"+name+QString("(%1)").arg(num)+"."+ext;
		QFileInfo newFileInfo(newFullName);
		if (newFileInfo.exists())
			num++;
		else
		{
			newFullFileName = newFullName;
			break;
		}
	}

	Entity* newEntity = new Entity(newFullFileName);
	copyEntity(newEntity,entity,pro,currentItem(),true);
	updateProject(pro);

	INSEditor::Document::instance()->getSolution()->save();
}
void SolutionBrowserTreeWidget::onNewProject()
{
	QStringList folders=getSelectedFolder(Type_SolutionFolder);
	if(INSEditor::Document::instance()->getSolution()){
		Project* newProject=INSEditor::Document::instance()->getSolution()->createNewProject();
		if(newProject && !folders.isEmpty()){
			newProject->setFolders(folders);
			updateProject(newProject);
		}

		updateView();
	}
}

void SolutionBrowserTreeWidget::onAddProject()
{
	QStringList folders=getSelectedFolder(Type_SolutionFolder);
	if(INSEditor::Document::instance()->getSolution()){
		Project* newProject=INSEditor::Document::instance()->getSolution()->addExistingProject();
		if(newProject && !folders.isEmpty()){
			newProject->setFolders(folders);
			updateProject(newProject);
		}

		updateView();
	}
}

void SolutionBrowserTreeWidget::onAddFiles()
{
	Project* currentProject=getSelectedProject();
	if(!currentProject)
		return;

	QStringList files = QFileDialog::getOpenFileNames(
		this, tr("Select Files"),currentProject->getDirectory(), 
		"INSIDES Files (*.ins *.stl *.tdy);;  All Files (*.*)");

	for(int i=0;i<files.size();++i)
	{
		QFileInfo info(files[i]);
		QString ext=info.suffix();

		if( !ext.compare("inspro",Qt::CaseInsensitive) ||!ext.compare("insln",Qt::CaseInsensitive) )
			continue;

		Entity* oldOne=currentProject->getEntityByFullFilename(files[i]);
		if(!oldOne)
		{
			Entity* entity=new Entity(info.absoluteFilePath());
			currentProject->addEntity(entity);
		}
	}

	updateProject(currentProject);
}

///复制工程副本
void SolutionBrowserTreeWidget::onCopyProject()
{
	Project* project = getSelectedProject();
	QString newProjectName = QInputDialog::getText(this,tr("Duplicate Project"),
		tr("Enter the new project name: "),QLineEdit::Normal,project->getProjectName());
	if(newProjectName.isEmpty())
		return;

	QDir proDir(project->getDirectory());
	QStringList list = proDir.entryList(QDir::Files);
	///建立副本的文件夹并拷贝文件
	QString solutionDir = INSEditor::Document::instance()->getSolution()->getSolutionDirectory();
	QDir dir(solutionDir);
	dir.mkdir(newProjectName);
	dir.cd(newProjectName);
	QString newDir = dir.path()+"/";

	QStringList projectEntityList;
	for (int i=0;i<project->getEntities().count();i++)
	{
		QString s = project->getEntities()[i]->getName();
		projectEntityList.push_back(s);
	}
	for (int i=0;i<list.count();i++)
	{
		QFileInfo info(list[i]);
		QString ext = info.suffix();
		if (!ext.compare("inspro",Qt::CaseInsensitive))
			QFile::copy(project->getDirectory()+list[i],newDir+list[i]);
		else
		{
			if(projectEntityList.indexOf(list[i])!= -1)
				QFile::copy(project->getDirectory()+list[i],newDir+list[i]);
		}
	}

	QFile file(newDir + project->getProjectName()+".inspro");
	file.rename(newDir+newProjectName+".inspro");

	QStringList folders=getSelectedFolder(currentItem()->parent(),Type_SolutionFolder);

	QString projectName = newDir+newProjectName+".inspro";
	Solution *solution = INSEditor::Document::instance()->getSolution();

	if(solution->getProject(projectName))
	{
		QMessageBox::critical(0,tr("Error"),tr("Project %1 has already added into this solution.").arg(projectName));
		return;
	}

	Project* newProject=Project::open(solution,projectName);
	if(newProject && !folders.isEmpty())
		newProject->setFolders(folders);

	if(newProject)
		solution->addProject(newProject);

	updateView();
}

///获得当前result条目设置tags;
void SolutionBrowserTreeWidget::onSetTags()
{
	QAction* tempTagAction = static_cast<QAction*>(sender());
	QString newTagName=tempTagAction->text();
	bool tagStatus=tempTagAction->isChecked();
	if(this->selectedItems().count() == 1)
	{
		Project* project = (Project*)currentItem()->data(0,DataRole_PTR).toULongLong();
		if(!tempTagAction || !project)
			return;

		QStringList tags = project->getTags();

		if(tagStatus)
			tags<<newTagName;
		else
			tags.removeAll(newTagName);

		project->setTags(tags);
	}
	else
	{
		QList<QTreeWidgetItem*> itemList = this->selectedItems();
		QList<Project*> proList ;
		foreach(QTreeWidgetItem* item,itemList)
		{
			if(item->data(0,DataRole_Type).toInt() == Type_Project)
				proList.push_back((Project*)item->data(0,DataRole_PTR).toULongLong());
		}
		QStringList tags = proList[0]->getTags();

		if(tagStatus)
			tags<<newTagName;
		else
			tags.removeAll(newTagName);

		foreach(Project* pro,proList)
			pro->setTags(tags);
	}
	
	emit tagsChanged();
}

void SolutionBrowserTreeWidget::onEditTags()
{
	TagManageDialog dlg;
	dlg.exec();
	emit tagsChanged();
}

void SolutionBrowserTreeWidget::onCustomContextMenuRequested( const QPoint& point )
{
	QMenu* menu = new QMenu(this);
	QAction* action = new QAction(menu);

	int hideCount = this->header()->hiddenSectionCount();
	if(hideCount == 1)
		action->setText(tr("Show State"));
	else
		action->setText(tr("Hide State"));

	menu->addAction(action);
	connect(action,SIGNAL(triggered()),this,SLOT(showOrHideState()));
	menu->exec(QCursor::pos());
}


BOOL CALLBACK SolutionBrowserTreeWidget::EnumWindowsProc_viewer(HWND hwnd,LPARAM lparam)
{
	char lpWinTitle[256];  
	::GetWindowTextA(hwnd,lpWinTitle,256-1);
	QString m_strTitle(lpWinTitle); 
	if(m_strTitle.contains("INSIDES viewer",Qt::CaseInsensitive)) 
		hwndList.push_back(hwnd);

	return TRUE ;
}

void SolutionBrowserTreeWidget::onOpenWithViewer()
{
	Project* project=getSelectedProject();
	if(!project)
		return;
	if(!project->getStartupEntity())
	{
		QMessageBox::warning(this,"Warning","Please set start up file !");
		return;
	}

	if(project->getViewProcess())
	{
		//关掉了
		if(!project->getViewProcess()->getViewer())
			project->openWithViewer2();
		else
		{
			::EnumWindows(EnumWindowsProc_viewer,0) ;
			
			foreach(HWND hwnd,hwndList)
			{
				DWORD ProcessID;
				GetWindowThreadProcessId(hwnd,&ProcessID);
				if(ProcessID == project->getViewProcess()->getViewer()->pid()->dwProcessId)
				{
					if(IsIconic(hwnd))
						::ShowWindow(hwnd,SW_SHOWMAXIMIZED );
					::ShowWindow(hwnd,SW_SHOW);
					::SetForegroundWindow(hwnd);
					break;
				}
			}
		}
	}
	else
		project->openWithViewer2();

	ViewerSocketToServerMessage msg;
	msg.command = ViewerSocketToServerMessage::IMPORT_MODEL;
	msg.informations["FILE_NAME"] = project->getStartupEntity()->getFullFileName();
	project->getViewProcess()->sendMessage(msg);
}

void SolutionBrowserTreeWidget::onOpenResultWithViewer()
{
	Project* pro = getSelectedProject();
	if(!pro->hasResult())
	{
		QMessageBox::warning(this,"No Result",QString("The project %1 no result , please solve it").arg(pro->getProjectName()));
		return;
	}
	if(pro)
	{
		if(!_solverManagerDialog)
			_solverManagerDialog = new SolverManagerDialog;
		onOpenWithViewer();
		_solverManagerDialog->checkResultFromTree(pro);
	}
}

bool SolutionBrowserTreeWidget::eventFilter( QObject *watched, QEvent *event )
{
	static int lastKey = 0;
	if (watched == this)
	{
		if (event->type() == QEvent::DragEnter) 
		{
			QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);
			dee->acceptProposedAction();
			return true;
		}
		else if (event->type() == QEvent::Drop) 
		{
			QDropEvent *de = dynamic_cast<QDropEvent *>(event);
			QList<QUrl> urls = de->mimeData()->urls();
			if (urls.isEmpty())
				return true;

			QString path = urls.first().toLocalFile();
			if (!path.isEmpty())
			{
				INSEditor::Document::instance()->open(path);
				updateView();
			}
			return true;
		}
	}
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		lastKey = keyEvent->key();
		if(keyEvent->key() == Qt::Key_Delete)
		{
			if(watched != _renameLineEdit)
				onRemove();
		}
		if(keyEvent->key() == Qt::Key_F2)
		{
			int typeId = currentItem()->data(0,DataRole_Type).toInt();
			if(typeId == Type_File || typeId == Type_FileFolder || typeId == Type_Project || typeId == Type_SolutionFolder)
				onRename();
		}
	}
	if (watched == _renameLineEdit)
	{
		if (event->type() == QEvent::FocusOut /*&& (lastKey != Qt::Key_Enter && lastKey != Qt::Key_Return)*/)
		{
			int typeId = _currItem->data(0,DataRole_Type).toInt();
			if(typeId==Type_SolutionFolder)
				onProjectFolderEditFinished();
			else if (typeId == Type_FileFolder)
				onFileFolderEditFinished();
			else if (typeId == Type_File && _renameEditIsEdited)
				onFileEditFinished();
			else if(typeId == Type_Project && _renameEditIsEdited)
				onProjectEditFinished();
		}
	}
	return QWidget::eventFilter(watched, event);
}

void SolutionBrowserTreeWidget::showParameterAnalysisDialog()
{
	Project* pro = (Project*)this->currentItem()->data(0,DataRole_PTR).toULongLong();
	if(!pro)
		return;

	ParameterAnalysisDialog dlg(pro,this);
	connect(&dlg,SIGNAL(createProject(const QString& , const QString& )),this,SLOT(onCreateProject(const QString&,const QString&)));
	dlg.exec();
	updateView();
}

void SolutionBrowserTreeWidget::showSolvingJobsDialog()
{
	if(!_solverManagerDialog)
	{
		_solverManagerDialog=new SolverManagerDialog(this);
		connect(_solverManagerDialog,SIGNAL(updateSolveProjectOnTree(Project*)),this,SLOT(updateSolveProject(Project*)));
	}
	_solverManagerDialog->show();
}

void SolutionBrowserTreeWidget::onSolve()
{
	QString str = INSEditor::Document::instance()->getProperties()->solverExecutablePath;
	if(str.isEmpty())
	{
		QMessageBox::warning(this,tr("Can't Find The Solver"),tr("Please check the path of the solver configuration!"));
		return;
	}

	QList<QTreeWidgetItem*> list = this->selectedItems();
	QList<Project*> projects;
	foreach(QTreeWidgetItem* item,list)
	{
		int typeId = item->data(0,DataRole_Type).toInt();
		if(typeId == Type_Project)
		{
			Project* pro = (Project*)item->data(0,DataRole_PTR).toULongLong();
			projects.push_back(pro);
		}
		else if(typeId == Type_File || typeId == Type_FileFolder)
		{
			QTreeWidgetItem* tmp = getParentProjectTreeItem(item);
			if(tmp)
			{
				Project* p = (Project*)tmp->data(0,DataRole_PTR).toULongLong();
				projects.push_back(p);
			}
		}
	}

	//是否点了no
	bool flag = false;
	
	foreach(Project* p ,projects)
	{
		if(p->hasResult())
		{
			QMessageBox msgBox;
			msgBox.setText(tr("The result of %1 already exists ,whether or not to solver").arg(p->getProjectName()));
			msgBox.setIcon(QMessageBox::Warning);

			QPushButton *yesBtn = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
			QPushButton *noBtn = msgBox.addButton(tr("No"), QMessageBox::ActionRole);

			msgBox.exec();

			if (msgBox.clickedButton() == yesBtn)
				continue;
			else
			{
				flag = true;
				projects.removeOne(p);
			}
		}
	}
	if(projects.isEmpty() && !flag)
	{
		Project* tmp = INSEditor::Document::instance()->getSolution()->getMainProject();
		if(tmp)
			projects<<tmp;
	}
	if(projects.isEmpty())
		return;

	if(!_solverManagerDialog)
	{
		_solverManagerDialog=new SolverManagerDialog(this);
		connect(_solverManagerDialog,SIGNAL(updateSolveProjectOnTree(INSEditor::Project*)),this,SLOT(updateSolveProject(INSEditor::Project*)));
	}
	_solverManagerDialog->solverProject(projects);
	_solverManagerDialog->show();
	updateSolveStateOnTree(projects);
}

void SolutionBrowserTreeWidget::updateSolveProject( INSEditor::Project* project )
{
	updateProject(project);
}

void SolutionBrowserTreeWidget::onClearSolveDialog()
{
	if(_solverManagerDialog)
	{
		_solverManagerDialog->close();
		_solverManagerDialog->deleteLater();
		_solverManagerDialog = NULL;
	}
}