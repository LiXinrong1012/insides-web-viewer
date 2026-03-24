#include "batfilemanager.h"
#include "waittingdialog.h"

#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QTimer>
#include <QProcess>
#include <QApplication>
#include <QLabel>

#include <string>
#include <Windows.h>

BatFileManager::~BatFileManager()
{
// 	QFile::remove(_fullFileName);
// 	QFile::remove(_runFileName);
// 	QFile::remove(_logsFileName);
}

BatFileManager::BatFileManager( const QString& fullFileName,const QStringList& list ,bool run /*= true*/,bool remove /*= true*/ )
	:_fullFileName(fullFileName)
	,_entityList(list)
	,_run(run)
	,_remove(remove)
	,_finished(false)
{
}

void BatFileManager::run( )
{
	QFileInfo info(_fullFileName);

	QDir dir;
	dir.setCurrent(info.absolutePath());

	QStringList fileNameList;
	QString tmp;
	for (int i=0;i<_entityList.count();i++)
	{
		if(tmp.isEmpty())
			tmp +="svn add ";
		tmp+= _entityList[i];
		tmp+=" ";

		if(((i % 80 == 0) && (i != 0)) || (i == _entityList.count()-1) )
		{
			static int num = 0;
			num ++;
			QString fileName = QString(qApp->applicationDirPath()+"/tmp/tmpsvn%1.bat").arg(num);
			fileNameList.push_back(fileName);
			QFile file(fileName);
			file.open(QIODevice::Text|QIODevice::WriteOnly);
			QTextStream stream(&file);
			stream.setCodec("ansi");
			stream<<tmp;
			file.close();
			tmp.clear();

			std::string str("cmd /c " + fileName.toStdString());
			WinExec(str.c_str(), SW_HIDE);
			Sleep(5000);
		}
	}
}

void BatFileManager::checkFinished()
{
	QFileInfo info(_fullFileName);
	_logsFileName = info.absolutePath() + "/log.txt";
	QFile file(_logsFileName);
	file.open(QIODevice::Text|QIODevice::ReadOnly);
	QString s = file.readAll();
	if(s.contains("提交后的版本为",Qt::CaseInsensitive))
		_finished = true;
}

