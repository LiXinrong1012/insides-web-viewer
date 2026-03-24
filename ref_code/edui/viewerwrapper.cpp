#include "viewerwrapper.h"

#include <QtCore>
#include <QtGui>

#include "edcore/localsocket.h"

using namespace INSEditor;

ViewerWrapper::ViewerWrapper(QObject *parent)
	: QObject(parent)
	,_viewerProcess(NULL)
	,_localSocket(NULL)
{
}

ViewerWrapper::~ViewerWrapper()
{
}

void ViewerWrapper::update( const QString& modelFileName )
{
	if(!_viewerProcess){
		QString program = "D:/Jerry/WorkDir/INSViewer/trunk/src/Win32/Release/viewer.exe";
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

void ViewerWrapper::sendMessage( const QString& message )
{
	if(!_localSocket){
		_localSocket=new LocalSocket(this);
		_localSocket->connectToServer(_viewerServerID);
	}
	_localSocket->sendMessage(message);
}

void ViewerWrapper::onViewerStarted()
{
	//QMessageBox::about(0,"Viewer started.","Viewer started.");
}

void ViewerWrapper::onViewerFinished( int exitCode, QProcess::ExitStatus exitStatus )
{
	clear();
	//QMessageBox::about(0,"Viewer closed.","Viewer closed.");
}

void ViewerWrapper::onViewerError( QProcess::ProcessError error )
{
	clear();
	QMessageBox::about(0,"Viewer error.","Viewer error.");
}

void ViewerWrapper::clear()
{
	delete _viewerProcess;
	_viewerProcess=NULL;
	delete _localSocket;
	_localSocket=NULL;
	_viewerServerID=QString();
}

void ViewerWrapper::highlight( const QString& itemName )
{
	sendMessage(QString("highlight %1").arg(itemName));
}


