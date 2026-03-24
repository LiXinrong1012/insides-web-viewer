#include "result.h"

#include <QtCore>
#include <QDomDocument>
#include <QDomProcessingInstruction>

#include "project.h"


namespace INSEditor{

static 	QString _dateTimeFormat("yyyy/MM/dd hh:mm:ss");

//Result* Result::createNew( Project* project )
//{
//	QUuid uuid=QUuid::createUuid();
//	QString resultFolder=uuid.toString();
//	resultFolder=resultFolder.mid(1,resultFolder.size()-2);
//	QDir dir(project->getDirectory());
//
//	QString resultFolderStr=project->getOutputDirectory()+resultFolder+"/";
//	dir.mkpath(resultFolderStr);
//
//	// copy all related files.
//	QFile proFile(project->getProjectFileName());
//	proFile.copy(resultFolderStr+project->getProjectName()+".inspro");
//	QDir dstDir(resultFolderStr);
//	const QList<Entity*>& entities=project->getEntities();
//	foreach(Entity* entity,entities){
//		QString fromFile=entity->getFullFileName();
//		QFile tmpFile(fromFile);
//		QString toFile=dstDir.absoluteFilePath(entity->getName());
//		bool b=tmpFile.copy(toFile);
//		if(b){
//			QFile::FileError tmpError=tmpFile.error();
//		}
//	}
//
//	Result* result=new Result(project);
//	result->_projectName=project->getProjectName();
//	result->_directory=resultFolderStr;
//	static int currentID=1;
//	result->_name=tr("Untitled %1").arg(currentID++);
//	result->_uuid=uuid;
//	result->_createTime=QDateTime::currentDateTime();
//	result->_lastEdit=QDateTime::currentDateTime();
//	return result;
//}


Result::Result(Project* project)
	:_project(project)
{
	_createTime=QDateTime::currentDateTime();
	_lastEdit=QDateTime::currentDateTime();
}

Result::~Result()
{

}

QString Result::getCreateTimeStr() const
{
	return _createTime.toString(_dateTimeFormat);
}

void Result::setCreateTimeStr( const QString& str )
{
	_createTime=QDateTime::fromString(str,_dateTimeFormat);
}

QString Result::getLastEditTimeStr() const
{
	return _lastEdit.toString(_dateTimeFormat);
}

void Result::setLastEditTimeStr( const QString& str )
{
	_lastEdit=QDateTime::fromString(str,_dateTimeFormat);
}


}