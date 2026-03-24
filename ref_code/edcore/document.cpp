#include "document.h"
#include "project.h"
#include "solution.h"

#include <QDir>
#include <QProcess>
#include <QApplication>

#include "applicationpropertydialog.h"


namespace INSEditor{

Document* Document::_instance=NULL;

Document* Document::instance()
{
	if(!_instance)
		_instance=new Document(0);
	return _instance;
}

void Document::destruct()
{
	if(_instance)
		delete _instance;
	_instance=NULL;
}
Document::Document(QObject *parent)
	: QObject(parent)
	,_properties(new ApplicationProperty())
{
}

Document::~Document()
{
	delete _properties;
	close();
}

Solution* Document::open( const QString& solutionName )
{
	Solution* solution=INSEditor::Solution::openExist(this,solutionName);
	if(!solution)
		return NULL;

	_solution=SolutionPtr(solution);
	emit solutionCreated(solution);
	return getSolution();
}

Solution* Document::createNew( const QString& dir,const QString& solutionName )
{
	Solution* solution=Solution::createNew(this,dir,solutionName);
	if(!solution)
		return NULL;

	_solution=SolutionPtr(solution);
	emit solutionCreated(solution);
	return getSolution();
}

void Document::close()
{
	emit solutionClosed(_solution.data());
	_solution.clear();
}

void Document::setProperties( ApplicationProperty* ap )
{
	if(ap==_properties)
		return;

	delete _properties;
	_properties = ap;
}

void Document::showApplicationSetting()
{
	ApplicationPropertyDialog* dlg = new ApplicationPropertyDialog(NULL);
	dlg->setAttribute(Qt::WA_DeleteOnClose,true);
	dlg->show();
}

void Document::startHelpApplication()
{
	QDir dir(qApp->applicationDirPath());
	QString appName=dir.absoluteFilePath("assistant.exe");
	QString helpFile;
	if(dir.exists("insides.qhc"))
		helpFile=dir.absoluteFilePath("insides.qhc");
	else
		helpFile=dir.absoluteFilePath("../doc/insides.qhc");
	
	QStringList arguments;

	arguments<<"-collectionFile"<<helpFile;
	arguments<<"-showUrl"<<"qthelp://org.doxygen.project/doc/index.html";
	QProcess::startDetached(appName,arguments);
}

void Document::requestSolveProcessUpdate( SolveProcess* process )
{
	emit solveProcessChanged(process);
}


}//end namespace INSEditor