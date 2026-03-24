#include "project.h"
#include "console.h"

#include <QDir>
#include <QMessageBox>
#include <QFileInfo>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomNodeList>
#include <QProcess>
#include <QThread>

#include <Windows.h>

#include "compileinfomanager.h"
#include "errormanager.h"

#include "document.h"
#include "applicationproperty.h"
#include "solveprocess.h"
#include "viewerprocess.h"

QList<HWND> hwndList; 
namespace INSEditor
{
	Project* Project::open( QObject* parent,const QString& projectName )
	{
		return new Project(parent,projectName);
	}

	Project* Project::createNew( QObject* parent,const QString& dir,const QString& projectName)
	{
		/// 有效性验证
		QDir rootDir(dir);
		if(!rootDir.exists()){
			QString error=tr("Directory: %s does not exist.");
			Base::Console().Error(error.toStdString().c_str(),dir.toStdString().c_str());
			return NULL;
		}

		if(rootDir.exists(projectName))
		{
			QMessageBox msgBox;
			QString msg=QString(tr("Directory '%1' has already existed.")).arg(projectName);
			QString info=QString(tr("Creating project in this directory may overwrite existing files. Do you still want to create project here?"));
			msgBox.setText(msg);
			msgBox.setInformativeText(info);
			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel );
			msgBox.setDefaultButton(QMessageBox::Cancel);
			int ret = msgBox.exec();
			if(ret==QMessageBox::Cancel)
				return NULL;
		}
		else if(!rootDir.mkdir(projectName) )
		{
			QString error=tr("Cannot create directory: %s.");
			Base::Console().Error(error.toStdString().c_str(),dir.toStdString().c_str());
			return NULL;
		}

		if(!rootDir.cd(projectName))
			return NULL;

		Project* project=new Project(parent);
		project->setDirectory(rootDir.path()+"/");
		project->setProjectName(projectName);
		project->createDefaultFolder();
		project->save();
		return project;
	}

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	Project::Project(QObject* parent)
		: QObject(parent)
		,_mainEntity(NULL)
		,_result(this)
		,_isExpand(false)
		,_isValid(true)
		,_viewerProcess(NULL)
		,_solveProcess(NULL)
		,_viewProcess(NULL)
	{
	}

	Project::Project( QObject* parent,const QString& projectName )
		:QObject(parent)
		,_mainEntity(NULL)
		,_result(this)
		,_isExpand(false)
		,_isValid(true)
		,_viewerProcess(NULL)
		,_solveProcess(NULL)
		,_viewProcess(NULL)
	{
		QFileInfo projectFile(projectName);
		QDir dir=projectFile.dir();
		_projectName=projectFile.completeBaseName();
		_directory=dir.absolutePath()+"/";

		QDomDocument document;
		QFile file(projectName);
		if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
		{
			_isValid=false;
			return;
		}

		document.setContent(&file);

		QDomElement xmlroot = document.firstChildElement();
		QDomElement editorElement = xmlroot.firstChildElement();
		QDomElement projectElement = editorElement.firstChildElement();
		this->setIncludeDirectory(projectElement.attribute("INCLUDE_DIR"));
		this->setLog(projectElement.attribute("LOG"));

		QString tags = projectElement.attribute("TAGS");
		QStringList tagList = tags.split(";",QString::SkipEmptyParts);
		this->setTags(tagList);

		QDomElement emptyFoldersElement = projectElement.firstChildElement("EMPTY_FOLDERS");
		_emptyFolders = emptyFoldersElement.attribute("FOLDERS").split(";",QString::SkipEmptyParts);

		QDomElement entityListElement = projectElement.firstChildElement("ENTITY_LIST");
		QDomElement entityElement=entityListElement.firstChildElement();
		while(!entityElement.isNull())
		{
			QString relativePath=entityElement.attribute("FILE");
			QString folders=entityElement.attribute("FOLDERS");
			QString uuidStr=entityElement.attribute("UUID");
			QString log = entityElement.attribute("LOG");
			QString entityName=dir.absoluteFilePath(relativePath);
			QString createNewOneWhenCopy = entityElement.attribute("CREATE_NEW_ONE_WHEN_COPY");

			Entity* entity=new Entity(entityName);

			QStringList folderList=folders.split(";",QString::SkipEmptyParts);
			entity->setFolders(folderList);
			entity->setLog(log);

			if(createNewOneWhenCopy == "1");
				entity->setCreateNewOneWhenCopy(true);
			if(createNewOneWhenCopy == "0")
				entity->setCreateNewOneWhenCopy(false);

			QUuid uuid(uuidStr);
			if(!uuid.isNull())
				entity->setUuid(uuid);

			addEntity(entity);

			entityElement=entityElement.nextSiblingElement();
		}
		QString mainEntityStr=projectElement.attribute("MAIN_ENTITY");
		_mainEntity=getEntity(mainEntityStr);

		readResult(projectElement);

		_isValid=true;
	}

	Project::~Project()
	{
		qDeleteAll(_entityList);
	}

	void Project::readResult(QDomElement& projectElement)
	{
		QString createTimeStr=projectElement.attribute("CREATE_TIME");
		QString lastEditTimeStr=projectElement.attribute("LAST_EDIT_TIME");
			
		Result* entity=&_result;
			
		entity->setCreateTimeStr(createTimeStr);
		entity->setLastEditTimeStr(lastEditTimeStr);
	}

	void Project::save()
	{
		if(!_isValid)
			return;

		QDomDocument doc;
		QDomProcessingInstruction instruction;
		instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ");
		doc.appendChild(instruction);
		QDomElement xmlroot = doc.createElement("INSIDES");
	    doc.appendChild(xmlroot);
		QDomElement editorElemet = doc.createElement("EDITOR");
		xmlroot.appendChild(editorElemet);
		QDir dir(getDirectory());

		QDomElement projectElement = doc.createElement("PROJECT");
		projectElement.setAttribute("INCLUDE_DIR",getIncludeDirectory());
		projectElement.setAttribute("VERSION","1.0.0");
		projectElement.setAttribute("LOG",this->getLog());
		projectElement.setAttribute("TAGS",this->getTags().join(";"));
		if(_mainEntity)
			projectElement.setAttribute("MAIN_ENTITY",_mainEntity->getUuid().toString());
		editorElemet.appendChild(projectElement);
		
		QDomElement emptyFoldersElement = doc.createElement("EMPTY_FOLDERS");
		emptyFoldersElement.setAttribute("FOLDERS",_emptyFolders.join(";"));
		projectElement.appendChild(emptyFoldersElement);

		// Entities
		QDomElement fileList = doc.createElement("ENTITY_LIST");
		foreach(Entity* entity,_entityList)
		{
			QDomElement fileEntity = doc.createElement("ENTITY");
			QString relativeDir=dir.relativeFilePath(entity->getFullFileName());
			fileEntity.setAttribute("FILE",relativeDir);
			fileEntity.setAttribute("UUID",entity->getUuid().toString());
			fileEntity.setAttribute("LOG",entity->getLog());
			fileEntity.setAttribute("FOLDERS",entity->getFolders().join(";"));
			fileEntity.setAttribute("CREATE_NEW_ONE_WHEN_COPY",entity->isCreateNewOneWhenCopy());
			fileList.appendChild(fileEntity);
		}

		projectElement.appendChild(fileList);

		// results
		saveResult(projectElement);

		if(!Entity::saveXMLFile(getDirectory()+_projectName+".inspro",doc.toString())){
			// error;
		}
	}

	void Project::saveResult(QDomElement& projectElement)
	{
		Result* result=&_result;
		projectElement.setAttribute("CREATE_TIME",result->getCreateTimeStr());
		projectElement.setAttribute("LAST_EDIT_TIME",result->getLastEditTimeStr());
	}

	bool Project::isEmpty() const
	{
		return _entityList.isEmpty();
	}

	bool Project::isValid() const
	{
		return _isValid;
	}

	void Project::createDefaultFolder()
	{
		_fileFolders<<QStringList(tr("Resource Files"))
			<<QStringList(tr("Model Files"));
	}

	void Project::addEntity(Entity* entity)
	{
		if(_entityList.contains(entity))
			return;

		_entityList.push_back(entity);
		entity->setProject(this);
		emit entityAdded(entity);
	}

	void Project::notifyEntityDoubleClicked( Entity* entity )
	{
//		emit entityDoubleClicked(entity);
	}

	void Project::removeEntity( Entity* entity )
	{
		if(!entity)
			return;

		emit entityAboutToRemove(entity);

		delete entity;
		_entityList.removeOne(entity);
	}

	Entity* Project::getEntity( const QString& uuidStr )const
	{
		QUuid uuid=QUuid(uuidStr);
		if(uuid.isNull())
			return NULL;

		foreach(Entity* e,_entityList)
			if(e->getUuid()==uuid)
				return e;
		return NULL;
	}

	Entity* Project::getEntityByFullFilename( const QString& fileName ) const
	{
		QFileInfo a(fileName);
		if(!a.exists())
			return NULL;
		
		foreach(Entity* e,_entityList)
		{
			QFileInfo tmp(e->getFullFileName());
			if(tmp==a)
				return e;
		}

		return NULL;
	}

	BOOL CALLBACK Project::EnumWindowsProc_viewer(HWND hwnd,LPARAM lparam)
	{
		char lpWinTitle[256];  
		::GetWindowTextA(hwnd,lpWinTitle,256-1);
		QString m_strTitle(lpWinTitle); 
		if(m_strTitle.contains("INSIDES viewer",Qt::CaseInsensitive)) 
			hwndList.push_back(hwnd);
		 
		return TRUE ;
	}

	BOOL CALLBACK Project::EnumWindowsProc_solver( HWND hwnd,LPARAM lparam )
	{
		char lpWinTitle[256];  
		::GetWindowTextA(hwnd,lpWinTitle,256-1);
		QString m_strTitle(lpWinTitle); 
		if(m_strTitle.contains("thudynamics.exe",Qt::CaseInsensitive)) 
			hwndList.push_back(hwnd);

		return TRUE ;
	}

	bool Project::openWithViewer()
	{
		if(!getStartupEntity())
			return false;

		QString appName=INSEditor::Document::instance()->getProperties()->viewerExecutablePath;
		if(appName.isEmpty())
		{
			appName="C:/Users/Jerry/Desktop/TDYPre/trunk/src/Win32/Release/viewer.exe";
			QFile file(appName);
			if(!file.exists())
				appName="D:/tsinghuaDir/INSViewerPlugins/src/Win32/Debug/viewer.exe";
		}

		QStringList arguments;
		QString modelName=getStartupEntity()->getFullFileName();
		arguments<<modelName;

		QFileInfo info(modelName);
		QString path=info.absolutePath();
		//QProcess::startDetached(appName,arguments,path);
		hwndList.clear();
		if(!_viewerProcess)
		{
			_viewerProcess = new QProcess;
			_viewerProcess->start(appName,arguments);//,path
			connect(_viewerProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(onViewerFinished(int,QProcess::ExitStatus)));
		}
		else
		{
			::EnumWindows(EnumWindowsProc_viewer,0) ;
			
			foreach(HWND hwnd,hwndList)
			{
				DWORD ProcessID;
				GetWindowThreadProcessId(hwnd,&ProcessID);
				if(ProcessID == _viewerProcess->pid()->dwProcessId)
				{
					if(IsIconic(hwnd))
						::ShowWindow(hwnd,SW_SHOWMAXIMIZED );
					::ShowWindow(hwnd,SW_SHOW);
					::SetForegroundWindow(hwnd);
					break;
				}
			}
		}
		return true;
	}

	bool Project::openWithSolver()
	{
		if(!getStartupEntity())
			QMessageBox::information(NULL,tr("Message"),"There's no startup file. Set startup file first.");

		QString appName=INSEditor::Document::instance()->getProperties()->solverExecutablePath;
		if(appName.isEmpty())
			appName="D:/solver/thudynamics.exe";

		QStringList arguments;
		QString modelName=getStartupEntity()->getFullFileName();
		arguments<<modelName;

		QFileInfo info(modelName);
		QString path=info.absolutePath();
		QProcess::startDetached(appName,arguments,path);
		return true;
	}

	bool Project::getStartupFile( QString& startupFile ) const
	{
		if(!getStartupEntity())
			return false;

		startupFile=getStartupEntity()->getFullFileName();
		return true;
	}

	bool Project::isExternalFile(const QString& fullFileName) const
	{
		if (fullFileName.indexOf("..") == -1)
			return false;
		else
			return true;
	}

	void Project::reload()
	{
		QDir dir(_directory);
		if(!dir.exists())
		{
			_isValid = false;
			return;
		}
		QFileInfo file(getDirectory()+_projectName+".inspro");
		if (file.exists())
		{
			_isValid = true;
			readXML();
		}
	}

	void Project::readXML( )
	{
		QDomDocument document;
		QFile file(getDirectory()+_projectName+".inspro");
		if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
		{
			_isValid=false;
			return;
		}

		document.setContent(&file);

		QDomElement xmlroot = document.firstChildElement();
		QDomElement editorElement = xmlroot.firstChildElement();
		QDomElement projectElement = editorElement.firstChildElement();
		this->setIncludeDirectory(projectElement.attribute("INCLUDE_DIR"));
		this->setLog(projectElement.attribute("LOG"));

		QDomElement emptyFoldersElement = projectElement.firstChildElement("EMPTY_FOLDERS");
		_emptyFolders = emptyFoldersElement.attribute("FOLDERS").split(";",QString::SkipEmptyParts);

		QDomElement entityListElement = projectElement.firstChildElement("ENTITY_LIST");
		QDomElement entityElement=entityListElement.firstChildElement();
		_entityList.clear();
		while(!entityElement.isNull())
		{
			QString relativePath=entityElement.attribute("FILE");
			QString folders=entityElement.attribute("FOLDERS");
			QString uuidStr=entityElement.attribute("UUID");
			QString entityName=relativePath.split("/")[relativePath.split("/").count()-1];
			QString createNewOneWhenCopy = entityElement.attribute("CREATE_NEW_ONE_WHEN_COPY");

			Entity* entity=new Entity(getDirectory() + relativePath);

			QStringList folderList=folders.split(";",QString::SkipEmptyParts);
			entity->setFolders(folderList);

			if(createNewOneWhenCopy == "1");
			entity->setCreateNewOneWhenCopy(true);
			if(createNewOneWhenCopy == "0")
				entity->setCreateNewOneWhenCopy(false);

			QUuid uuid(uuidStr);
			if(!uuid.isNull())
				entity->setUuid(uuid);

			entity->reload();
			addEntity(entity);

			entityElement=entityElement.nextSiblingElement();
		}
		QString mainEntityStr=projectElement.attribute("MAIN_ENTITY");
		_mainEntity=getEntity(mainEntityStr);

		readResult(projectElement);

		_isValid=true;
	}

	bool Project::hasResult()
	{
		if(!_isValid)
			return false;

		QDir dir(getDirectory());
		return dir.exists("result/overview.xml");
	}

	Solution* Project::getSolution()
	{
		return (Solution*)parent();
	}

	void Project::onViewerFinished( int exitCode, QProcess::ExitStatus exitStatus )
	{
		_viewerProcess->deleteLater();
		_viewerProcess = NULL;
	}

	bool Project::openWithSolver2()
	{
		// 判断是不是可以求解
		// 判断是不是正在求解

		if(_solveProcess)
			delete _solveProcess;

		_solveProcess=new SolveProcess(this);
		return true;
	}

	bool Project::openWithViewer2()
	{
		if(_viewProcess)
			delete _viewProcess;

		_viewProcess = new ViewerProcess(this);
		return true;
	}


}

