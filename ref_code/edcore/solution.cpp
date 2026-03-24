#include "solution.h"
#include "project.h"
#include "entity.h"
#include "console.h"

#include <QFile>
#include <QtCore>
#include <QMessageBox>
#include <QInputDialog>
#include <QDomDocument>
#include <QFileDialog>


namespace INSEditor{

Solution* Solution::openExist( QObject* parent,const QString& solutionFilePath )
{
	QFileInfo file(solutionFilePath);
	if(!file.exists())
		return NULL;

	return new Solution(parent,solutionFilePath);
}

Solution* Solution::createNew( QObject* parent,const QString& dir, const QString& solutionName,bool createDefaultProject/*=true*/ )
{
	// 有效性验证
	QDir rootDir(dir);
	if(!rootDir.exists()){
		QString error=tr("Directory: %s does not exist.");
		Base::Console().Error(error.toStdString().c_str(),dir.toStdString().c_str());
		return NULL;
	}

	if(rootDir.exists(solutionName)){
		QMessageBox msgBox;
		QString msg=QString(tr("Directory '%1' has already existed.")).arg(solutionName);
		QString info=QString(tr("Creating solution in this directory may overwrite existing files. Do you still want to create solution here?"));
		msgBox.setText(msg);
		msgBox.setInformativeText(info);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel );
		msgBox.setDefaultButton(QMessageBox::Cancel);
		int ret = msgBox.exec();
		if(ret==QMessageBox::Cancel)
			return NULL;
	}
	else{
		if(!rootDir.mkdir(solutionName)){
			QString error=tr("Cannot create directory at: %s.");
			Base::Console().Error(error.toStdString().c_str(),dir.toStdString().c_str());
			return NULL;
		}
	}

	if(!rootDir.cd(solutionName))
		return NULL;
	
	Solution* solution=new Solution(parent);
	solution->_solutionDirectory=rootDir.path()+"/";
	solution->_name=solutionName;
	
	if(createDefaultProject){ 
		Project* defaultProject=Project::createNew(solution,rootDir.path(),solutionName);

		if(defaultProject){
			solution->_projectsList.push_back(defaultProject);
		}
	}
	solution->save();

	return solution;
}

Solution::Solution( QObject *parent,const QString& solutionName )
	: QObject(parent)
	,_mainProject(NULL)
	,_currentProject(NULL)
	,_isModified(false)
{
	if(solutionName.isEmpty())
		return;

	QDomDocument doc;
	QFile file(solutionName);
	if(file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		doc.setContent(&file);
		file.close();
	}
	QDomElement xmlroot = doc.firstChildElement();
	QDomElement easyplotElement = xmlroot.firstChildElement();
	QDomElement solutionElement = easyplotElement.firstChildElement();

	QString tmp=solutionElement.attribute("TAGS");
	_tagList=tmp.split(";",QString::SkipEmptyParts);

	QFileInfo solutionFile(solutionName);
	QDir dirRoot=solutionFile.dir();
	_solutionDirectory=dirRoot.absolutePath()+"/";
	_name=solutionFile.baseName();

	QDomElement projiectListElement = solutionElement.firstChildElement();
	QDomElement projectElement = projiectListElement.firstChildElement();
	while(!projectElement.isNull())
	{
		QString relativePath=projectElement.attribute("PATH");
		QString folders=projectElement.attribute("FOLDERS");

		QString projectName=dirRoot.absoluteFilePath(relativePath);
		Project* projectNew=Project::open(this,projectName);

		QStringList folderList=folders.split(";",QString::SkipEmptyParts);
		projectNew->setFolders(folderList);
		addProject(projectNew);
		projectElement = projectElement.nextSiblingElement();
	}
	setModified(false);
}

Solution::~Solution()
{
}

bool Solution::save()
{
	QDomDocument doc;
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ");
	doc.appendChild(instruction);
	QDomElement xmlroot = doc.createElement("INSIDES");
	doc.appendChild(xmlroot);
	QDomElement easyplotElement = doc.createElement("EDITOR");
	xmlroot.appendChild(easyplotElement);
	QDomElement solutionElement = doc.createElement("SOLUTION");
	solutionElement.setAttribute("VERSION","1.0.0");
	solutionElement.setAttribute("TAGS",_tagList.join(";"));

	easyplotElement.appendChild(solutionElement);
	QDomElement projectListElement = doc.createElement("PROJECT_LIST");
	solutionElement.appendChild(projectListElement);
	QDir dirRoot(this->getSolutionDirectory());
	foreach(Project* project,_projectsList)
	{
		QDomElement projectElement=doc.createElement("PROJECT"); 
		QString relativeDir=dirRoot.relativeFilePath(project->getDirectory());
		QString projectPath=relativeDir+"/"+project->getProjectName()+".inspro";
		projectElement.setAttribute("PATH",projectPath);
		projectElement.setAttribute("NAME",project->getProjectName());
		projectElement.setAttribute("FOLDERS",project->getFolders().join(";"));

		projectListElement.appendChild(projectElement);

		project->save();
	}

	if(!Entity::saveXMLFile(getSolutionDirectory()+_name+".insln",doc.toString())) {
		// error
	}
	setModified(false);
	return true;
}

bool Solution::removeProject( Project* project )
{
	if(!project)
		return false;

	emit projectClosed(project);

	_projectsList.removeOne(project);
	delete project;
	project = NULL;
	setModified(true);
	return true;
}

bool Solution::addProject( Project* project )
{
	this->_projectsList.push_back(project);
	emit projectCreated(project);
	setModified(true);
	return true;
}

QString Solution::getSolutionFullName()
{
	return _solutionDirectory+_name+".insln";
}

Project* Solution::createNewProject()
{
	QString newProjectName=QInputDialog::getText(0,tr("Creating New Project"),"Enter New Project Name:");
	if(newProjectName.isEmpty())
		return NULL;

	QDir dir(getSolutionDirectory());
	if(dir.exists(newProjectName)){
		int re=QMessageBox::question(0,tr("Warning"),tr("there exists a project with the same name."
			"Do you still want to create project here?"),
			QMessageBox::Yes,QMessageBox::No);
		if(re==QMessageBox::No)
			return NULL;
	}

	Project* project=Project::createNew(this,getSolutionDirectory(),newProjectName);
	if(project)
		addProject(project);
	return project;
}

Project* Solution::addExistingProject()
{
	QString projectName=QFileDialog::getOpenFileName(0, tr("Open Project File"),
		QDir::current().absolutePath(),
		tr("Project File (*.inspro)"));
	if(projectName.isEmpty())
		return NULL;

	if(getProject(projectName)){
		QMessageBox::critical(0,tr("Error"),tr("Project %1 has already added into this solution.").arg(projectName));
		return NULL;
	}

	Project* project=Project::open(this,projectName);
	if(project){
		addProject(project);
	}
	return project;
}

Project* Solution::getProject( const QString& projectName )
{
	QFileInfo a(projectName);
	foreach(Project* p, _projectsList){
		QFileInfo tmp(p->getDirectory()+p->getProjectName()+".inspro");
		if(a==tmp)
			return p;
	}
	return NULL;
}

void Solution::reload()
{
	for (int i=0;i<_projectsList.count();i++)
		_projectsList[i]->reload();
}

void Solution::setModified( bool b )
{
	if(_isModified==b)
		return;

	_isModified=b;
	emit modificationStatusChanged(b);
}

void Solution::setMainProject( Project* project )
{
	_mainProject = project;
	emit mainProjectChanged(_mainProject);
}




}