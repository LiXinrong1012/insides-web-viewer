#include "filemanager.h"
#include "edcompile/mainitem.h"

FileManager::FileManager(QObject *parent)
	: QObject(parent)
{
}

FileManager::~FileManager()
{
}

void FileManager::notifyOpenFile( const QString& fullFileName )
{
	emit requestOpenFile(fullFileName);
}

FileManager* FileManager::instance()
{
	static FileManager _manger(0);
	return &_manger;
}

void FileManager::notifyUpdateOutputInfo(const INSEditor::Parse::CompileInfoItem& item )
{
	emit requestUpdateOutputInfo(item);
}

void FileManager::notifyBeginBuild()
{
	emit requestBeginBuild();
}

void FileManager::notifyEndBuild()
{
	emit requestEndBuild();
}

void FileManager::notifyGotoPosition( const QString& fullFileName,int rowIndex,int columnIndex )
{
	emit requestGotoPosition(fullFileName,rowIndex,columnIndex);
}

void FileManager::onSaveFile()
{
	emit requestSaveFile();
}

void FileManager::notifyBuildProject()
{
	emit requestBuildProject();
}

void FileManager::notifyUpdateIcon()
{
	emit requestUpdateIcon();
}

void FileManager::notifySolveProject()
{
	emit requestSolveProject();
}

void FileManager::notifyClearSolve()
{
	emit requestClearSolve();
}

void FileManager::notifyUpdateModel(INSEditor::Parse::AssemblyItem* item,const QString& fileName)
{
	emit requestUpdateModel(item,fileName);
}

void FileManager::notifyExpandModelTree()
{
	emit requestExpandModelTree();
}

void FileManager::notifyTestOutput(QString s)
{
	emit requestTestOutput(s);
}