#include "entity.h"
#include "project.h"
#include <QtCore>

namespace INSEditor{

Entity::Entity( const QString& fullFileName )
	:_uuid(QUuid::createUuid())
	,_project(NULL)
	,_fullFileName(fullFileName)
{
	reload();
}

QString Entity::getFullFileName() const
{
	return _fullFileName;
}

Entity::~Entity()
{
}

QString Entity::getFileExt()
{
	QFileInfo info(_fullFileName);
	return info.suffix();
}

QString Entity::readFromFile()
{
	QDir dir;
	if(dir.exists(_fullFileName))
	{
		QFile file(_fullFileName);
		if (!file.open(QFile::ReadOnly))
			return QString();

		QTextStream in(&file);
		return in.readAll();
	}
	return QString();
}

bool Entity::saveXMLFile(const QString& xmlFileName,const QString& content)
{
	QFile file(xmlFileName);
	if(file.open(QIODevice::WriteOnly|QIODevice::Text))
	{
		QTextStream stream(&file);
		stream.setCodec("UTF-8");
		stream << content;
		file.close();
		return true;
	}
	return false;
}

bool Entity::rename( const QString& text )
{
	_name = text;
	QFileInfo tmp(_fullFileName);
	_fullFileName = tmp.absoluteDir().absolutePath()+"/"+_name;
	return true;
}

void Entity::reload()
{
	QFileInfo file(_fullFileName);
	_name=file.fileName();
	if(!file.exists()){
		_isValid=false;
		return;
	}
	if(!file.isWritable()){
		_isValid=false;
		return;
	}
		
	_isValid=true;
}

}