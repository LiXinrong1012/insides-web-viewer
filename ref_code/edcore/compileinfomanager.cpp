#include "compileinfomanager.h"

CompileInfoManager::CompileInfoManager(QObject *parent)
	: QObject(parent)
{
	connect(this,SIGNAL(pSetItem(const QString&,Parse::FileItem*)),
		this,SLOT(onPSetItem(const QString&,Parse::FileItem*)));
	connect(this,SIGNAL(pClear()),
		this,SLOT(onPClear()));
}

CompileInfoManager::~CompileInfoManager()
{
	_dataMap.clear();
}

void CompileInfoManager::setItem( const QString& fileName,Parse::FileItem* item )
{
	emit pSetItem(fileName,item);
}

const Parse::FileItem* CompileInfoManager::getItem( const QString& fileName )
{
	QString tmp=fileName.toUpper();
	Parse::FileItem* result=NULL;
	if(_dataMap.find(tmp)!=_dataMap.end())
		result= _dataMap[tmp].data();

	return result;
}

void CompileInfoManager::clear()
{
	emit pClear();
}

void CompileInfoManager::onPSetItem( const QString& fileName,Parse::FileItem* item )
{
	QString tmp=fileName.toUpper();
	if(tmp.isEmpty())
		return;

	_dataMap[tmp]=QSharedPointer<Parse::FileItem>(item);
	emit itemUpdated(fileName,item);
}

void CompileInfoManager::onPClear()
{
	_dataMap.clear();
	emit itemUpdated(QString(),NULL);
}
