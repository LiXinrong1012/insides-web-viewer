#include "processwrapper.h"


#include <QtCore>
#include <QtGui>

#include "localsocket.h"

namespace INSEditor{


ProcessWrapper::ProcessWrapper(QObject *parent)
	: QObject(parent)
	,_viewerProcess(NULL)
	,_localSocket(NULL)
{
}

ProcessWrapper::~ProcessWrapper()
{
}

void ProcessWrapper::update( const QString& modelFileName )
{
	if(!_viewerProcess)
	{
		QString program = "D:/Jerry/WorkDir/INSViewer/trunk/src/Win32/Release/viewer.exe";

		QFile file(program);
		if(!file.exists())
			program="D:/tsinghuaDir/INSViewerPlugins/src/Win32/Debug/viewer.exe";

		QStringList arguments;
		arguments << modelFileName;
		_viewerServerID=QUuid::createUuid().toString();

		arguments<<"-server"<<_viewerServerID;

		_viewerProcess=new QProcess(this);
		connect(_viewerProcess,SIGNAL(started()),this,SLOT(onViewerStarted()));
		connect(_viewerProcess,SIGNAL(error( QProcess::ProcessError)),this,SLOT(onViewerError(QProcess::ProcessError)));
		connect(_viewerProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(onViewerFinished(int,QProcess::ExitStatus)));
		_viewerProcess->start(program, arguments);
		_modelFileName=modelFileName;
	}
	else
		sendMessage("refresh");
}

void ProcessWrapper::sendMessage( const QString& message )
{
	if(!_localSocket){
		_localSocket=new LocalSocket(this);
		_localSocket->connectToServer(_viewerServerID);
	}
	_localSocket->sendMessage(message);
}

void ProcessWrapper::onViewerStarted()
{
//	QMessageBox::about(0,"Viewer started.","Viewer started.");
}

void ProcessWrapper::onViewerFinished( int exitCode, QProcess::ExitStatus exitStatus )
{
	clear();
//	QMessageBox::about(0,"Viewer closed.","Viewer closed.");
}

void ProcessWrapper::onViewerError( QProcess::ProcessError error )
{
	clear();
	QMessageBox::about(0,"Viewer error.","Viewer error.");
}

void ProcessWrapper::clear()
{
	delete _viewerProcess;
	_viewerProcess=NULL;
	delete _localSocket;
	_localSocket=NULL;
	_viewerServerID=QString();
}

void ProcessWrapper::highlight( const QString& itemName )
{
	sendMessage(QString("highlight %1").arg(itemName));
}


}