#include "solutionbrowsertreewidget.h"
#include <QtGui>

#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"
#include "edcore/entity.h"

using namespace INSEditor;


//更改底层数据结构
void SolutionBrowserTreeWidget::dropEvent( QDropEvent* e )
{
	QTreeWidgetItem* treeItem=getCursorItem();
	if (!treeItem)
		return;

	QTreeWidgetItem* projectItem = getParentProjectTreeItem(treeItem);

	//目标的project
	Project* pro = getSelectedProject(projectItem);

	int typeId = treeItem->data(0,DataRole_Type).toInt();
	if(typeId == Type_File){
		e->setAccepted(false);
		return;
	}

	const QMimeData* data=e->mimeData();
	if(data->hasFormat("application/inseditor/solutionbrowserdata"))
	{
		QByteArray dataArray= data->data("application/inseditor/solutionbrowserdata");
		QDataStream in(dataArray);
		int num =0;
		int dataType; 
		QVariant realData;
		in>>num;
		if(num==0)
			return;

		Project* oldProject=NULL;
		for (int i=0;i<num;i++)
		{
			in>>dataType;
			in>>realData;

			if(dataType == Type_File)
			{
				//这是旧的entity
				Entity* entity=(Entity*)realData.toULongLong();
				if(oldProject == NULL)
					oldProject = entity->getProject();

				//如果文件存在同名
				QList<Entity*> entityList = pro->getEntities();
				QStringList strList;
				for (int i=0;i<entityList.count();i++)
					strList.push_back(entityList[i]->getName());

				//是否为同一工程
				if(pro == entity->getProject())
				{
					QStringList list = getSelectedFolder(treeItem,Type_FileFolder);
					entity->setFolders(list);
				}
				else
				{
					//是否为外部文件
					if (oldProject->isExternalFile(entity->getFullFileName()))
					{
						//异工程外部文件存在，不做处理
						if(strList.contains(entity->getName(),Qt::CaseInsensitive))
						{
							e->setAccepted(false);
							updateView();
							return;
						}
						Entity *tempEntity = new Entity(entity->getFullFileName());
						copyEntity(tempEntity,entity,pro,treeItem,false);
					}
					else
					{
						bool isExist=false;
						QMessageBox msgBox;
						if(strList.contains(entity->getName(),Qt::CaseInsensitive) && pro != oldProject)
						{
							msgBox.setText(tr("The target project files already exist !<br><br><b>Copy and overwrite the original file chose 'Copy'.</b><br><br><b>Move and overwrite the original file chose 'Move'.</b>"));
							isExist = true;
						}
						else
						{
							msgBox.setText(QString("Do you want to copy file \"%1\" or move to this project.").arg(entity->getName()));
							isExist = false;
						}
						msgBox.setIcon(QMessageBox::Warning);

						QPushButton *copyButton = msgBox.addButton(tr("Copy"), QMessageBox::ActionRole);
						QPushButton *moveButton = msgBox.addButton(tr("Move"), QMessageBox::ActionRole);
						QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

						msgBox.exec();

						if (msgBox.clickedButton() == copyButton)
						{
							Entity *tempEntity = new Entity(pro->getDirectory()+entity->getName());
							copyEntity(tempEntity,entity,pro,treeItem,true);
						}
						else if(msgBox.clickedButton() == moveButton)
						{
							Entity *tempEntity = new Entity(pro->getDirectory()+entity->getName());
							copyEntity(tempEntity,entity,pro,treeItem,true);

							QFile::remove(entity->getFullFileName());
							oldProject->removeEntity(entity);
						}
						else
						{
							updateView();
							return;
						}
					}
				}
			}

			if(dataType == Type_Project)
			{
				Project* project = (Project*)realData.toULongLong();
				QStringList list;
				list = getSelectedFolder(treeItem,Type_SolutionFolder);
				project->setFolders(list); 
			}
		}
		///更新树上显示
		if ((dataType == Type_File))
		{	
			INSEditor::Document::instance()->getSolution()->save();
			if (pro == oldProject)
				updateProject(pro);
			else
			{
				updateProject(oldProject);
				updateProject(pro);
			}
		} 

		if(dataType == Type_Project)
			updateView();
	}
	QTreeWidget::dropEvent(e);
}

void SolutionBrowserTreeWidget::copyEntity( Entity* newEntity,Entity* oldEntity,Project* pro,QTreeWidgetItem* cursorItem,bool isCopyFile)
{
	QString newEntityName = newEntity->getFullFileName();
	QList<Entity*> entityList = pro->getEntities();
	foreach(Entity* entity,entityList)
	{
		if(entity->getFullFileName() == newEntityName)
		{
			QFile::remove(entity->getFullFileName());
			pro->removeEntity(entity);
		}
	}

	newEntity->setContent(oldEntity->getContent());
	newEntity->setCreateNewOneWhenCopy(oldEntity->isCreateNewOneWhenCopy());
	newEntity->setLog(oldEntity->getLog());
	newEntity->setProject(pro);
	newEntity->setUuid(oldEntity->getUuid());
	newEntity->setFolders(getSelectedFolder(cursorItem,Type_FileFolder));

	pro->addEntity(newEntity);
	
	if(isCopyFile)
		QFile::copy(oldEntity->getFullFileName(),newEntity->getFullFileName());

	newEntity->reload();
}

void SolutionBrowserTreeWidget::dragMoveEvent( QDragMoveEvent * e )
{
	QTreeWidget::dragMoveEvent(e);
	e->setAccepted(false);

	QTreeWidgetItem* treeItem=getCursorItem();
	if(!treeItem)
		return;
	int typeId = treeItem->data(0,DataRole_Type).toInt();
	const QMimeData* data=e->mimeData();
	if(!data->hasFormat("application/inseditor/solutionbrowserdata"))
		return;

	QByteArray dataArray= data->data("application/inseditor/solutionbrowserdata");
	QDataStream in(dataArray);
	int dataType,num=0; 
	QVariant realData;
	in>>num;
	if(num==0)
		return;
	for (int i=0;i<num;i++)
	{
		in>>dataType;
		in>>realData;

		if(dataType==Type_File)
		{
			QTreeWidgetItem* projectTreeItem=getParentProjectTreeItem(treeItem);
			if(!projectTreeItem)
				return;
			Project* project=getSelectedProject(projectTreeItem);
			Entity* entity=(Entity*)realData.toULongLong();


			if((entity->getProject()==project)&& (treeItem->data(0,DataRole_PTR).toULongLong()!=realData.toULongLong())&&(typeId!=Type_File))
				e->setAccepted(true);
			if ((entity->getProject() != project)&&(typeId!=Type_File))
				e->setAccepted(true);
		}

		if (dataType== Type_Project)
		{
			if( (typeId == Type_SolutionFolder) || (typeId==Type_Solution) )
				e->setAccepted(true);
		}
	}

}

//将地址放入mime中
QMimeData * SolutionBrowserTreeWidget::mimeData( const QList<QTreeWidgetItem *> items ) const
{
	if(items.size()==0)
		return NULL;

	int num =0;
	QList<QTreeWidgetItem*> itemList;
	for(int i=0;i<items.count();i++)
	{
		QTreeWidgetItem* item = items[i];
		if( (item->data(0,DataRole_Type).toInt()==Type_Solution)
			|| (item->data(0,DataRole_Type).toInt()==Type_SolutionFolder)
			|| (item->data(0,DataRole_Type).toInt()==Type_FileFolder) )
			return NULL;
		itemList.push_back(item);
		num++;
	}
	if(num==0)
		return NULL;

	QByteArray encodeData;
	int type=0;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	QMimeData* mimeData=QTreeWidget::mimeData(items);
	stream<<num;
	for (int i=0;i<itemList.count();i++)
	{
		int dataType=itemList[i]->data(0,DataRole_Type).toInt();
		stream<<dataType<<itemList[i]->data(0,DataRole_PTR);
		if(i==0)
			type=dataType;
		if(type != dataType)
			return NULL;
	}

	mimeData->setData("application/inseditor/solutionbrowserdata",encodeData);
	return mimeData;
}