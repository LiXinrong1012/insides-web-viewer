#include "solutionbrowsertreewidget.h"

#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"
#include "edcore/filemanager.h"
#include "edcore/solveprocess.h"

#include "inssolver/socketmessage.h"

#include "resultstatewidget.h"
#include "solutionbrowserwidget.h"


#include <QtGui>
#include <QtXml/QDomDocument>

using namespace INSEditor;


TreeWidgetItem::TreeWidgetItem( QTreeWidgetItem * parent, int type /*= Type*/ )
	:QTreeWidgetItem(parent,type)
{
}

TreeWidgetItem::TreeWidgetItem( QTreeWidget * parent, int type /*= Type*/ ) 
	:QTreeWidgetItem(parent,type)
{
}

bool TreeWidgetItem::operator<( const QTreeWidgetItem & other ) const
{
	int type1=this->data(0,DataRole_Type).toInt();
	int type2=other.data(0,DataRole_Type).toInt();
	if(type1==type2)
		return QTreeWidgetItem(*this)<QTreeWidgetItem(other);

	return type1<type2;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SolutionBrowserTreeWidget::SolutionBrowserTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
	,_renameEditIsEdited(true)
	,_renameLineEdit(NULL)
	,_iconSolution(":/resources/menu/a016-16.png")
	,_iconProject(":/resources/menu/a001-16.png")
	,_iconEntity(":/resources/menu/a005-16.png")
	,_iconProjectFolder(":/resources/menu/a019-16.png")
	,_iconFileFolder(":/resources/menu/a018-16.png")
	,_solverManagerDialog(NULL)
	,_updateSolveStateTimer(NULL)
{
	Document* doc=Document::instance();
	connect(doc,SIGNAL(solutionClosed(Solution*)),this,SLOT(clearView()));
	connect(doc,SIGNAL(solutionCreated(Solution*)),this,SLOT(onSolutionOpened(Solution*)));

	createActions();

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onContextMenu(const QPoint&)));
	connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
		this,SLOT(onCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
	
	setAcceptDrops(true);
	setDragDropMode(QAbstractItemView::InternalMove);
	this->installEventFilter(this);
	setSelectionMode(QAbstractItemView::ExtendedSelection);

	setSortingEnabled(true);
	sortItems(0,Qt::AscendingOrder);

	//_watcher = new QFileSystemWatcher(this);
    //connect(_watcher,SIGNAL(directoryChanged( const QString & )),this,SLOT(	onDirChanged ( const QString &  )));
	connect(this,SIGNAL(itemExpanded ( QTreeWidgetItem *  )),this,SLOT(onItemCollapseStatusChanged(QTreeWidgetItem*)));
	connect(this,SIGNAL(itemCollapsed ( QTreeWidgetItem * )),this,SLOT(onItemCollapseStatusChanged(QTreeWidgetItem*)));
	connect(this,SIGNAL(itemClicked ( QTreeWidgetItem * , int  )),this,SLOT(onItemClicked(QTreeWidgetItem*,int)));

	connect(header(),SIGNAL(sectionResized(int,int,int)),this,SLOT(saveViewState()));

	connect(FileManager::instance(),SIGNAL(requestSolveProject()),this,SLOT(onSolve()));
	connect(FileManager::instance(),SIGNAL(requestClearSolve()),this,SLOT(onClearSolveDialog()));
}

SolutionBrowserTreeWidget::~SolutionBrowserTreeWidget()
{
}

void SolutionBrowserTreeWidget::clearView()
{
	if(topLevelItemCount()>0)
	{
		QTreeWidgetItem* item=takeTopLevelItem(0);
		if(item)
			delete item;
	}
}

void SolutionBrowserTreeWidget::updateView()
{
	//临时记录每个节点的展开情况
	QMap<QString,bool> isExpandedMap;
	QTreeWidgetItemIterator it(this);
	while (*it) {
		if((*it)->data(0,DataRole_Type).toUInt() == Type_SolutionFolder)
			isExpandedMap[(*it)->text(0)] = (*it)->isExpanded();
		++it;
	}

	clearView();

	INSEditor::Document* doc = INSEditor::Document::instance();
	if(!doc->getSolution())
		return;

	Solution* solution=doc->getSolution();

	_solutionRootItem=createTreeItem(this,
		tr("Solution '%1' (%2 projects)").arg(solution->getSolutionName()).arg(solution->getAllProjects().size()),
		_iconSolution,
		Type_Solution,solution,true);

	const QList<Project*>& projects=solution->getAllProjects();

	foreach(Project* p, projects)
		updateProject(p);

	this->insertTopLevelItem(0, _solutionRootItem);

	QTreeWidgetItemIterator nit(this);
	while(*nit)
	{
		if((*nit)->data(0,DataRole_Type).toInt() == Type_SolutionFolder)
			(*nit)->setExpanded(isExpandedMap[(*nit)->text(0)]);
		nit++;
	}
}

void SolutionBrowserTreeWidget::updateProject( INSEditor::Project* project )
{
	QTreeWidgetItem* oldProItem = getProjectItem(project);
	if(oldProItem)
		oldProItem->parent()->removeChild(oldProItem);

	QTreeWidgetItem* parentItem=getOrCreateFolderTreeWidgetItem(_solutionRootItem,project->getFolders());

	if(!parentItem)
		return;

	bool isExpanded=project->isExpanded();
	QTreeWidgetItem* projectItem=createTreeItem(parentItem,
		project->getProjectName(),_iconProject,
		Type_Project,project,isExpanded);

	ResultStateWidget* widget = new ResultStateWidget(this);
	if(project->hasResult())
		widget->setHasResult();
	else
		widget->setNoResult();

	this->setItemWidget(projectItem,1,widget);

	if(!project->isValid()){
		QIcon iconTmp=_iconProject.pixmap(QSize(16,16),QIcon::Disabled);
		projectItem->setIcon(0,iconTmp);
		projectItem->setText(0,QString("%1(unavailable)").arg(project->getProjectName()));
	}

	QStringList emptyFolders = project->getEmptyFolders();
	for (int i=0;i<emptyFolders.count();i++)
		createTreeItem(projectItem,emptyFolders[i],_iconFileFolder,Type_FileFolder,NULL,true);

	// update entities
	const QList<Entity*>& enties=project->getEntities();
	foreach(Entity* entity,enties)
	{
		QTreeWidgetItem* entityParentItem = getOrCreateFolderTreeWidgetItem(projectItem,entity->getFolders());

		QString fileName=entity->getFullFileName();
		QIcon systemIcon=getSystemIcon(fileName);
		
		QTreeWidgetItem* entityItem=createTreeItem(entityParentItem,entity->getName(),
			systemIcon,Type_File,entity,isExpanded);

		if(entity==project->getStartupEntity()){
			QFont font;
			font.setBold(true);
			entityItem->setFont(0,font);
		}
	}
	//_watcher->addPath(project->getDirectory());
}

void SolutionBrowserTreeWidget::updateSolveStateOnTree( QList<Project*> projects )
{
	foreach(Project* pro,projects)
	{
		if(!_solvingProjects.contains(pro))
		{
			_solvingProjects<<pro;
			QTreeWidgetItem* item = getProjectItem(pro);
			ResultStateWidget* widget = new ResultStateWidget(this);
			widget->startRunning();
			this->setItemWidget(item,1,widget);
		}
	}
	
	if(!_updateSolveStateTimer)
	{
		_updateSolveStateTimer = new QTimer(this);
		connect(_updateSolveStateTimer,SIGNAL(timeout()),this,SLOT(updateSolveState()));
		_updateSolveStateTimer->start(Document::instance()->getProperties()->treeProcessUpdateFrequency*1000);
	}
}

void SolutionBrowserTreeWidget::updateSolveState()
{
	foreach(Project* pro,_solvingProjects)
	{
		if(!pro->getSolveProcess())
			continue;
		if(_solvingProjects.isEmpty())
		{
			_updateSolveStateTimer->stop();
			_updateSolveStateTimer->deleteLater();
			_updateSolveStateTimer = NULL;
		}
		QTreeWidgetItem* item = getProjectItem(pro);
		ResultStateWidget* widget = (ResultStateWidget*)this->itemWidget(item,1);
		if(!widget)
			continue;
		widget->startRunning();
		widget->setRunningProgress(pro->getSolveProcess()->getProcess()*100);
		if(pro->getSolveProcess()->getCurrentState() == SendToClientMessage::FINISHED)
		{
			widget->endRunning();
			_solvingProjects.removeOne(pro);
			updateProject(pro);
			continue;
		}
	}
}

void SolutionBrowserTreeWidget::onSolutionOpened( Solution* solution )
{
	connect(solution,SIGNAL(projectClosed(Project*)),this,SLOT(onProjectRemoved(Project*)));
	connect(solution,SIGNAL(projectCreated(Project*)),this,SLOT(onProjectAdded(Project*)));
	updateView();
	emit tagsChanged();
	FileManager::instance()->notifyUpdateIcon();
	//_watcher->addPath(solution->getSolutionDirectory());
}

void SolutionBrowserTreeWidget::onProjectAdded( Project* project )
{
	updateProject(project);
}

void SolutionBrowserTreeWidget::onProjectRemoved( Project* project )
{
}

void SolutionBrowserTreeWidget::initHeader()
{
	setColumnCount(2);
	QTreeWidgetItem * headerItem = new QTreeWidgetItem();
	headerItem->setText(0, tr("Items"));
	headerItem->setText(1, tr("State"));
	setHeaderItem(headerItem);
	this->header()->setMovable(true);

	readViewState();

	this->header()->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this->header(),SIGNAL(customContextMenuRequested(const QPoint &)),
		this,SLOT(onCustomContextMenuRequested(QPoint)));
}

QTreeWidgetItem* SolutionBrowserTreeWidget::createTreeItem(QTreeWidgetItem* parent,const QString& text,const QIcon& icon,
	int dataType,void* p,bool expanded)
{
	QTreeWidgetItem* item=new TreeWidgetItem(parent);
	initTreeItem(item,text,icon,dataType,p,expanded);
	return item;
}

QTreeWidgetItem* SolutionBrowserTreeWidget::createTreeItem(QTreeWidget* parent,const QString& text,const QIcon& icon,
	int dataType,void* p,bool expanded)
{
	QTreeWidgetItem* item=new TreeWidgetItem(parent);
	initTreeItem(item,text,icon,dataType,p,expanded);
	return item;
}

void SolutionBrowserTreeWidget::initTreeItem(QTreeWidgetItem* item,const QString& text,const QIcon& icon,
	int dataType,void* p,bool expanded)
{
	item->setText(0,text);
	item->setIcon(0,icon);
	item->setData(0,DataRole_Type,dataType);
	item->setData(0,DataRole_PTR,quintptr(p));
	item->setExpanded(expanded);
}

QTreeWidgetItem* SolutionBrowserTreeWidget::getOrCreateFolderTreeWidgetItem(QTreeWidgetItem* rootItem,
	const QStringList& folderList,bool createUnexisted)
{
	QTreeWidgetItem* curr=rootItem;
	int tmpType=rootItem->data(0,DataRole_Type).toInt();
	int rootType=0;
	QIcon itemIcon;
	if(tmpType==Type_Project){
		rootType=Type_FileFolder;
		itemIcon=_iconFileFolder;
	}
	else if(tmpType==Type_Solution){
		rootType=Type_SolutionFolder;
		itemIcon=_iconProjectFolder;
	}
	else// error
		return NULL;

	for (int i=0;i<folderList.count();i++)
	{
		if(!curr)
			return NULL;

		int count = curr->childCount();
		int j;
		for (j=0;j<count;j++)
		{
			QTreeWidgetItem* item = curr->child(j);

			int tt=item->data(0,DataRole_Type).toInt();
			if(  ((tt==Type_SolutionFolder) ||  (tt==Type_FileFolder) )
				&& (item->text(0)==folderList[i]) )
			{
				curr = curr->child(j);
				break;
			}
		}

		if (j==count) 
		{
			if(createUnexisted){
				QTreeWidgetItem* tmpItem=createTreeItem(curr,
					folderList[i],
					itemIcon,
					rootType,
					NULL,
					true);
				curr = tmpItem;
			}
			else
				curr=NULL;
		}
	}
	return curr;
}

bool SolutionBrowserTreeWidget::deleteDirFromDisk( const QString &dirName )
{
	/*递归删除文件夹,即使里面有内容 
	 ** 
	 **dir :文件夹的名字,绝对路径和相对路径均可 
	 ** 
	 **返回值 :成功后返回true;否则返回false 
	 */  
	static QVector<QString> dirNames;
	QDir dir;
	QFileInfoList filst;
	QFileInfoList::iterator curFi;
	///初始化
	dirNames.clear();
	if(dir.exists())
		dirNames<<dirName;
	else
		return true;
	///遍历各级文件夹,并将这些文件夹中的文件删除
	for (int i=0;i<dirNames.size();i++)
	{
		dir.setPath((dirNames[i]));
		filst=dir.entryInfoList(QDir::Dirs|QDir::Files|QDir::Readable|QDir::Writable|QDir::Hidden|QDir::NoDotAndDotDot,QDir::Name);
		if (filst.size()>0)
		{
			curFi=filst.begin();
			while(curFi!=filst.end())
			{
				///遇到文件夹,则添加至文件夹列表dirs尾部
				if (curFi->isDir())
					dirNames.push_back(curFi->filePath());
				else if (curFi->isFile())
				{
					///遇到文件则删除
					if(!dir.remove(curFi->fileName()))
						return false;
				}
				curFi++;
			}
		}
	}
	for (int i=dirNames.size()-1;i>=0;--i)
	{
		dir.setPath(dirNames[i]);
		if(!dir.rmdir("."))
			return false;
	}
	return true;
}

QTreeWidgetItem* SolutionBrowserTreeWidget::getCursorItem()
{
	QPoint point=QCursor().pos();
	point=viewport()->mapFromGlobal(point);
	return itemAt(point);
}

void SolutionBrowserTreeWidget::getTypeAllItem( QTreeWidgetItem* item,int type )
{
	for (int i=0;i<item->childCount();i++)
	{
		int typeId = item->child(i)->data(0,DataRole_Type).toInt();
		if (typeId == type)
			_typeAllItem.push_back(item->child(i));
		if (item->child(i)->childCount()!=0)
			getTypeAllItem(item->child(i),type);
	}
}

void SolutionBrowserTreeWidget::createActions()
{
	_openWithViewer=new QAction(tr("View(&v)"),this);
	connect(_openWithViewer,SIGNAL(triggered()),this,SLOT(onOpenWithViewer()));

	_openResultWithViewer = new QAction(tr("Result(&r)"),this);
	connect(_openResultWithViewer,SIGNAL(triggered()),this,SLOT(onOpenResultWithViewer()));

	_buildAction = new QAction(tr("Compile"),this);
	connect(_buildAction,SIGNAL(triggered()),this,SLOT(onCompile()));

	_solveAction = new QAction(QIcon(":/resources/menu/a014-16.png"),tr("Solve(&s)"),this);
	connect(_solveAction,SIGNAL(triggered()),this,SLOT(onSolve()));

	_newProjectAction = new QAction(QIcon(":/resources/menu/a002-16.png"),tr("New Project"),this);
	connect(_newProjectAction,SIGNAL(triggered()),this,SLOT(onNewProject()));

	_copyProjectAction = new QAction(tr("Duplicate project"),this);
	connect(_copyProjectAction,SIGNAL(triggered()),this,SLOT(onCopyProject()));

	_copyFileAction = new QAction(tr("Duplicate file"),this);
	connect(_copyFileAction,SIGNAL(triggered()),this,SLOT(onCopyFile()));

	_addExistingProjectAction = new QAction(QIcon(":/resources/menu/a008-16.png"),tr("Existing Project"),this);
	connect(_addExistingProjectAction,SIGNAL(triggered()),this,SLOT(onAddProject()));

	_newProjectFolderAction = new QAction(QIcon(":/resources/menu/a010-16.png"),tr("New Solution Folder"),this);
	connect(_newProjectFolderAction,SIGNAL(triggered()),this,SLOT(onAddSolutionFolder()));

	_newItemAction = new QAction(QIcon(":/resources/menu/a005-16.png"),tr("New Item"),this);
	connect(_newItemAction,SIGNAL(triggered()),this,SLOT(onNewFile()));

	_addExistingItemsAction = new QAction(QIcon(":/resources/menu/a004-16.png"),tr("Existing Item"),this);
	connect(_addExistingItemsAction,SIGNAL(triggered()),this,SLOT(onAddFiles()));

	_newFileFolderAction=new QAction(QIcon(":/resources/menu/a009-16.png"),tr("Folder"),this);
	connect(_newFileFolderAction,SIGNAL(triggered()),this,SLOT(onAddFileFolder()));

	_addMenu = new QMenu(tr("Add"),this);

	_addMenu->addAction(_newProjectAction);
	_addMenu->addAction(_addExistingProjectAction);
	_addMenu->addAction(_newProjectFolderAction);
	_addMenu->addAction(_newItemAction);
	_addMenu->addAction(_addExistingItemsAction);
	_addMenu->addAction(_newFileFolderAction);

	_setAsStartupFileAction=new QAction(tr("Set as startup file"),this);
	connect(_setAsStartupFileAction,SIGNAL(triggered()),this,SLOT(onSetAsStartupEntity()));

	_openWithAction = new QAction(QIcon(":/resources/menu/a004-16.png"),tr("&Open with local"),this);
	connect(_openWithAction,SIGNAL(triggered()),this,SLOT(onOpenWith()));

	_openInExplorerAction = new QAction(tr("Open in explorer"),this);
	connect(_openInExplorerAction,SIGNAL(triggered()),this,SLOT(onOpenInExplorer()));

	_reloadAction=new QAction(tr("Reload"),this);
	connect(_reloadAction,SIGNAL(triggered()),this,SLOT(onReload()));

	_cutAction = new QAction(tr("Cut"),this);
	_copyAction = new QAction(tr("Copy"),this);
	_pasteAction = new QAction(tr("Paste"),this);

	_addAllFilesToSVNAction = new QAction(tr("Add to SVN"),this);
	connect(_addAllFilesToSVNAction,SIGNAL(triggered()),this,SLOT(onAddAllFilesToSVN()));

	_compareAction = new QAction(tr("Compare files"),this);
	connect(_compareAction,SIGNAL(triggered()),this,SLOT(onCompareFiles()));

	_removeAction=new QAction(QIcon(":/resources/menu/a012-16.png"),tr("Remove"),this);
	connect(_removeAction,SIGNAL(triggered()),this,SLOT(onRemove()));

	_renameAction = new QAction(tr("Rename"),this);
	_renameAction->setShortcut(QKeySequence("F2"));
	connect(_renameAction,SIGNAL(triggered()),this,SLOT(onRename()));

	_editTagAction = new QAction(QIcon(),tr("Edit Tags"),this);
	connect(_editTagAction,SIGNAL(triggered()),this,SLOT(onEditTags()));

	_exhaustionParameterAction = new QAction(tr("Parameter analysis ..."),this);
	connect(_exhaustionParameterAction,SIGNAL(triggered()),this,SLOT(showParameterAnalysisDialog()));

	_batchSolveAction = new QAction(tr("Solving jobs"),this);
	connect(_batchSolveAction,SIGNAL(triggered()),this,SLOT(showSolvingJobsDialog()));
}

Project* SolutionBrowserTreeWidget::getSelectedProject()
{
	QTreeWidgetItem* curr=getParentProjectTreeItem(currentItem());
	if(curr)
		return (Project*)curr->data(0,DataRole_PTR).toULongLong();
	return NULL;
}

Project* SolutionBrowserTreeWidget::getSelectedProject( QTreeWidgetItem* item )
{
	if(item)
		return (Project*)item->data(0,DataRole_PTR).toULongLong();
	return NULL;
}

QTreeWidgetItem* SolutionBrowserTreeWidget::getParentProjectTreeItem(QTreeWidgetItem* item)
{
	QTreeWidgetItem* curr=item;
	while(curr){
		int type=curr->data(0,DataRole_Type).toInt();
		if(type==Type_Project)
			return curr;
		curr=curr->parent();
	}
	return NULL;
}

QStringList SolutionBrowserTreeWidget::getSelectedFolder(QTreeWidgetItem* item,int folderType)
{
	QStringList folder;
	QTreeWidgetItem* curr=item;

	while(curr){
		int type=curr->data(0,DataRole_Type).toInt();
		if(type==folderType)
			folder.push_front(curr->text(0));
		else if(type==Type_Project|| type==Type_Solution)
			break;
		curr=curr->parent();
	}
	return folder;
}

QStringList SolutionBrowserTreeWidget::getSelectedFolder(int type)
{
	return getSelectedFolder(currentItem(),type);
}

Entity* SolutionBrowserTreeWidget::getSelectedEntity()
{
	QTreeWidgetItem* curr=currentItem();
	if(curr && (curr->data(0,DataRole_Type).toInt()==Type_File) )
		return (Entity*)curr->data(0,DataRole_PTR).toULongLong();

	return NULL;
}

bool SolutionBrowserTreeWidget::isCertainType( QTreeWidgetItem* item,int certainType )
{
	int type=item->data(0,DataRole_Type).toInt();
	return type==certainType;
}

void SolutionBrowserTreeWidget::onProjectFolderEditFinished()
{
	QString str = _renameLineEdit->text();
	this->removeItemWidget(_currItem,0);
	if(str.isEmpty())
		return;
	
	_typeAllItem.clear();
	getTypeAllItem(_currItem,Type_Project);
	_currItem->setText(0,str);
	foreach(QTreeWidgetItem* item,_typeAllItem)
	{
		QStringList folderList = getSelectedFolder(item->parent(),Type_SolutionFolder);
		Project* tempProject =(Project*)item->data(0,DataRole_PTR).toULongLong();
		tempProject->setFolders(folderList);
	}
}

void SolutionBrowserTreeWidget::onFileFolderEditFinished()
{
	QString str = _renameLineEdit->text();
	this->removeItemWidget(_currItem,0);
	_currItem->setText(0,str);
	if(str.isEmpty())
		return;
	
	_typeAllItem.clear();
	getTypeAllItem(_currItem,Type_File);
	_currItem->setText(0,str);
	foreach(QTreeWidgetItem* item,_typeAllItem)
	{
		QStringList folderList = getSelectedFolder(item->parent(),Type_FileFolder);
		Entity* tempEntity =(Entity*)item->data(0,DataRole_PTR).toULongLong();
		tempEntity->setFolders(folderList);
	}
}

void SolutionBrowserTreeWidget::onFileEditFinished()
{
	_renameEditIsEdited = true;

	QString str = _renameLineEdit->text();
	if(str.isEmpty() || str == _currEntity->getName())
	{
		this->removeItemWidget(_currItem,0);
		return;
	}

	//是否重名
	QList<Entity*> entityList = _currEntity->getProject()->getEntities();
	QStringList strList ;
	for (int i=0;i<entityList.count();i++)
		strList.push_back(entityList[i]->getName());

	if ( strList.contains(str,Qt::CaseInsensitive))
	{
		_renameEditIsEdited = false;
		QMessageBox::warning(this,tr("Warning"),QString("The file %1 is existing!").arg(str));
		_renameLineEdit->setText(_currEntity->getName());
		_renameLineEdit->setSelection(0,_renameLineEdit->text().size());
		_renameLineEdit->setFocus();
		return;
	}

	//文件名是否合法
	if(!isLegal(str))
	{
		QMessageBox::warning(this,tr("Warning"),QString("The file name %1 is not legal!").arg(str));
		_renameLineEdit->setSelection(0,_renameLineEdit->text().size());
		_renameLineEdit->setFocus();
		return;
	}

	this->removeItemWidget(_currItem,0);
	QFile file(_currEntity->getFullFileName());
	QString name = _currEntity->getName();
	QString fullName = _currEntity->getFullFileName();
	fullName.remove(name); 
	fullName+=str;
	_currEntity->rename(str);
	file.rename(fullName);
	file.close();
	_currItem->setText(0,str);

	QIcon systemIcon = getSystemIcon(fullName);
	_currItem->setIcon(0,systemIcon);

	Document::instance()->getSolution()->save();
}

void SolutionBrowserTreeWidget::onProjectEditFinished()
{
	_renameEditIsEdited = true;
	QString str = _renameLineEdit->text();
	if(str.isEmpty() || str == _currProject->getProjectName())
	{
		this->removeItemWidget(_currItem,0);
		return;
	}

	//是否重名
	QList<Project*> proList = Document::instance()->getSolution()->getAllProjects();
	QStringList strList ;
	for (int i=0;i<proList.count();i++)
		strList.push_back(proList[i]->getProjectName());

	if ( strList.contains(str,Qt::CaseInsensitive))
	{
		_renameEditIsEdited = false;
		QMessageBox::warning(this,tr("Warning"),QString("The project '%1' is existing!").arg(str));
		_renameLineEdit->setText(_currProject->getProjectName());
		_renameLineEdit->setSelection(0,_renameLineEdit->text().size());
		_renameLineEdit->setFocus();
		return;
	}

	//文件名是否合法
	if(!isLegal(str))
	{
		_renameEditIsEdited = false;
		QMessageBox::warning(this,tr("Warning"),QString("The project name '%1' is not legal!").arg(str));
		_renameLineEdit->setText(_currProject->getProjectName());
		_renameLineEdit->setSelection(0,_renameLineEdit->text().size());
		_renameLineEdit->setFocus();
		return;
	}
	this->removeItemWidget(_currItem,0);
	//delete _renameLineEdit;
	//_renameLineEdit = NULL;

	//判断是否有文件被打开
	QString oldDir = _currProject->getDirectory();
	QStringList list = oldDir.split("/",QString::SkipEmptyParts);
	list[list.count()-1] = str;
	QString newDir = list.join("/")+"/";
	QDir dir(oldDir);
	if(dir.rename(oldDir,newDir))
		dir.rename(newDir,oldDir);
	else
	{
		_renameEditIsEdited = false;
		QMessageBox::warning(this,tr("Warning"),tr("A file has been opened in engineering, so can't change the project name"));
		return ;
	}

	QFile file(_currProject->getProjectFileName());
	QString name = _currProject->getProjectName();
	QString fullName = _currProject->getProjectFileName();
	fullName.remove(name+".inspro"); 
	fullName+=str;
	fullName+=".inspro";
	file.rename(fullName);//改工程文件名
	file.close();

	
	dir.rename(oldDir,newDir);//改文件夹名

	_currProject->setDirectory(newDir);
	_currProject->setProjectName(str);//改内存
	
	QList<Entity*> entityList = _currProject->getEntities();
	foreach(Entity* entity, entityList)
	{
		if(!_currProject->isExternalFile(entity->getFullFileName()))
			entity->setFullFileName(newDir+entity->getName());
	}

	_currItem->setText(0,str);
	Document::instance()->getSolution()->save();
}

void SolutionBrowserTreeWidget::onDirChanged( const QString &path )
{
	///拿到PATH之后再做处理
	Document::instance()->getSolution()->save();
}

QStringList SolutionBrowserTreeWidget::getAllEmptyFolders(Project* p)
{
	QStringList folders;
	QTreeWidgetItem* projectItem;
	QTreeWidgetItemIterator it(this);
	while (*it) 
	{
		Project* pp = (Project*)(*it)->data(0,DataRole_PTR).toULongLong();
		if(pp == p)
		{
			projectItem =(*it);
			break;
		}
		++it;
	}
	for (int i=0;i<projectItem->childCount();i++)
	{
		QTreeWidgetItem* item = projectItem->child(i);
		if((item->childCount()==0) && (item->data(0,DataRole_Type).toInt() == Type_FileFolder))
			folders<<item->text(0);
	}
	return folders;
}

void SolutionBrowserTreeWidget::onCurrentItemChanged( QTreeWidgetItem * current, QTreeWidgetItem * previous )
{
	if(!current)
	{
		emit currentItemChanged(NULL,0);
		return;
	}
	
	int itemType=current->data(0,DataRole_Type).toInt();
	void* item=(void*)current->data(0,DataRole_PTR).toULongLong();
	emit currentItemChanged(item,itemType);

	Project* p = getSelectedProject(getParentProjectTreeItem(current));
	Document::instance()->getSolution()->setMainProject(p);
	FileManager::instance()->notifyUpdateIcon();
}

QIcon SolutionBrowserTreeWidget::getSystemIcon( QString fileFullName )
{
	QFileIconProvider provider;
	QIcon systemIcon=provider.icon(QFileInfo(fileFullName));
	systemIcon=systemIcon.isNull()?_iconEntity:systemIcon;
	return systemIcon;
}

void SolutionBrowserTreeWidget::onTextChanged( const QString & text )
{
	_renameEditIsEdited = true;
}

QTreeWidgetItem* SolutionBrowserTreeWidget::getProjectItem( Project* project )
{
	QTreeWidgetItemIterator it(this);
	while (*it) {
		int typeId = (*it)->data(0,DataRole_Type).toInt();
		if(typeId != Type_Project)
		{
			++it;
			continue;
		}
		if(project == (Project*)(*it)->data(0,DataRole_PTR).toULongLong())
			return (*it);
		++it;
	}
	return NULL;
}

void SolutionBrowserTreeWidget::showOrHideState()
{
	int hideCount = this->header()->hiddenSectionCount();
	if (hideCount == 1)
	{
		this->header()->showSection(1);
		this->setColumnWidth(0,150);
	}
	else
		this->header()->hideSection(1);
}

void SolutionBrowserTreeWidget::onTagsCurrentIndexChanged(int tagIndex)
{
	Solution* solution=Document::instance()->getSolution();
	QStringList allTags=solution->getTagList();
	if( (tagIndex==-1) || (tagIndex==0) || tagIndex>allTags.size() )
	{
		updateView();
		return;
	}

	QString text=allTags[tagIndex-1];
	solution->setCurrentTag(text);

	QList<Project*> proList = Document::instance()->getSolution()->getAllProjects();

	updateView();
	for (int i=0;i<proList.count();i++)
	{
		if (proList[i]->getTags().contains(text,Qt::CaseSensitive))
			updateProject(proList[i]);
		else
		{	
			QTreeWidgetItem* item = getProjectItem(proList[i]);
			if(item)
				item->parent()->removeChild(item);
		}
	}
}

void SolutionBrowserTreeWidget::onItemCollapseStatusChanged( QTreeWidgetItem * item )
{
	int typeId = item->data(0,DataRole_Type).toInt();
	if(typeId != Type_Project)
		return;

	Project* pro = (Project*)item->data(0,DataRole_PTR).toULongLong();
	pro->setIsExpanded(item->isExpanded());
}

void SolutionBrowserTreeWidget::saveViewState()
{
	QSettings setting("insides/editor","solutiontree");
	setting.beginGroup("header");
	setting.setValue("column1_width",columnWidth(0));
	setting.endGroup();
}

void SolutionBrowserTreeWidget::readViewState()
{
	QSettings setting("insides/editor","solutiontree");
	setting.beginGroup("header");
	int width = setting.value("column1_width",200).toInt();
	setColumnWidth(0,width);
	setting.endGroup();
}

bool SolutionBrowserTreeWidget::isLegal( const QString& fileName )
{
	QStringList testStr;
	testStr<<"\\"
		<<"/"
		<<":"
		<<"*"
		<<"?"
		<<"\""
		<<"<"
		<<">"
		<<"|";
	for(int i=0;i<testStr.count();i++)
	{
		if(fileName.contains(testStr[i]))
			return false;
	}
	return true;
}

void SolutionBrowserTreeWidget::onCreateProject( const QString& proName, const QString& text )
{
	Project* project = getSelectedProject();
	QString newProjectName = proName;
	if(newProjectName.isEmpty())
		return;

	///建立副本的文件夹并拷贝文件
	QString solutionDir = INSEditor::Document::instance()->getSolution()->getSolutionDirectory();
	QDir dir(solutionDir);
	dir.mkdir(newProjectName);
	dir.cd(newProjectName);
	QString newDir = dir.path()+"/";

	//将原有的inspro文件拷贝过来并修改
	QFile::copy(project->getDirectory() + project->getProjectName()+".inspro",newDir + newProjectName + ".inspro");
	QDomDocument doc;
	QFile tmpFile(newDir + newProjectName + ".inspro");
	doc.setContent(&tmpFile);
	
	QDomElement xmlroot = doc.firstChildElement();
	QDomElement editorElement = xmlroot.firstChildElement();
	QDomElement projectElement = editorElement.firstChildElement();

	QDomElement entityListElement = projectElement.firstChildElement("ENTITY_LIST");

	QDomElement fileEntity = entityListElement.firstChildElement("ENTITY");

	while(!fileEntity.isNull())
	{
		QString file = fileEntity.attribute("FILE");
		if(file.contains(".ins",Qt::CaseInsensitive) || file.contains(".tdy",Qt::CaseInsensitive))
		{
			QDomElement tmp = fileEntity.nextSiblingElement("ENTITY");
			entityListElement.removeChild(fileEntity);
			fileEntity = tmp;
		}

		fileEntity = fileEntity.nextSiblingElement("ENTITY");
	}
	
	QDomElement mainEntity = doc.createElement("ENTITY");
	mainEntity.setAttribute("FILE","main.ins");
	entityListElement.appendChild(mainEntity);

	QFile xmlFile(newDir + newProjectName + ".inspro");
	xmlFile.open(QIODevice::WriteOnly|QIODevice::Text);
	QTextStream xmlStrem(&xmlFile);
	QString tmpStr =doc.toString();;
	xmlStrem.setCodec("utf-8");
	xmlStrem<<tmpStr;
	xmlFile.close();
	
	QFile file(newDir + "main.ins");
	file.open(QIODevice::WriteOnly| QIODevice::Text);
	
	QTextStream stream(&file);
	stream<<text;
	file.close();

	QStringList folders=getSelectedFolder(currentItem()->parent(),Type_SolutionFolder);

	QString projectName = newDir+newProjectName+".inspro";
	Solution *solution = INSEditor::Document::instance()->getSolution();

	Project* newProject=Project::open(solution,projectName);
	if(newProject && !folders.isEmpty())
		newProject->setFolders(folders);

	if(newProject)
	{
		newProject->setStartupEntity(newProject->getEntityByFullFilename(newProject->getDirectory()+"main.ins"));
		solution->addProject(newProject);
	}
}

void SolutionBrowserTreeWidget::onItemClicked( QTreeWidgetItem* item,int index)
{
	return;
}





