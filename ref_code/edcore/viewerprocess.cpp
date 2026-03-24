#include "viewerprocess.h"
#include "document.h"
#include "solution.h"
#include "project.h"
#include "entity.h"
#include "insviewer/socketservermessage.h"
#include <QMessageBox>
#include <QApplication>
#include <QTimer>
#include "console.h"

using namespace Base;

ViewerProcess::ViewerProcess(INSEditor::Project *parent)
	: QObject(parent)
	,_socket(this)
	,_viewer(NULL)
	,_cuState(0)
	,_showError(false)
{
	connect(&_socket, SIGNAL(connected()), this, SLOT(socketConnectedHandler()));
	connect(&_socket, SIGNAL(disconnected()), this, SLOT(socketDisConnectedHandler()));
	connect(&_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(socketErrorHandler(QLocalSocket::LocalSocketError)));
	connect(&_socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

	QString appName=INSEditor::Document::instance()->getProperties()->viewerExecutablePath;
	if(appName.isEmpty())
	{
		QMessageBox msg;
		msg.setIcon(QMessageBox::Warning);
		msg.setText("The viewer path is empty,please set it.");
		msg.exec();
		return ;
	}

	QStringList arguments;

	QUuid uuid=QUuid::createUuid();
	QString modelName=parent->getStartupEntity()->getFullFileName();
	arguments<<"\""+modelName+"\"";
//	arguments<<modelName;

	_serverName=uuid.toString();
	arguments<<"-n"<<_serverName;

	Console().Log("Start viewer, application path = %s",modelName.toStdString().c_str());
	QString tmp=arguments.join(" ");
	Console().Log("\tArguments: %s",tmp.toStdString().c_str());

	_viewer = new QProcess(this);
	connect(_viewer,SIGNAL(finished(int,QProcess::ExitStatus)),
		this,SLOT(onViewerFinished(int,QProcess::ExitStatus)));
	connect(_viewer,SIGNAL(error ( QProcess::ProcessError )),this,SLOT(onViewerError(QProcess::ProcessError)));
	_viewer->start(appName,arguments);

	QTimer::singleShot(0,this,SLOT(tryConnectViewer()));
}

ViewerProcess::~ViewerProcess()
{
}

void ViewerProcess::connectViewer( const QString &strServerName )
{
	// 服务端的serverNewConnectionHandler成员方法将被调用
	_socket.connectToServer(strServerName);
	if (!_socket.waitForConnected(10000))
	{
//		QMessageBox::warning(NULL,"Warning","Cannot connect solver.");
		return;
	}
}

void ViewerProcess::sendMessage( const ViewerSocketToServerMessage& mes )
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out<<mes;
	_socket.write(block);
	_socket.flush();
}

void ViewerProcess::socketConnectedHandler()
{
}

void ViewerProcess::socketDisConnectedHandler()
{
}

void ViewerProcess::socketErrorHandler( QLocalSocket::LocalSocketError error )
{
	QString err;
	switch (error)
	{
	case QAbstractSocket::ConnectionRefusedError:
		err = "The connection was refused by the peer (or timed out).";
		break;
	case QAbstractSocket::RemoteHostClosedError:
		err = "The remote socket closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.";
		break;
	case QAbstractSocket::HostNotFoundError:
		err = "The local socket name was not found.";
		break;
	case QAbstractSocket::SocketAccessError:
		err = "The socket operation failed because the application lacked the required privileges.";
		break;
	case QAbstractSocket::SocketResourceError:
		err = "The local system ran out of resources (e.g., too many sockets).";
		break;
	case QAbstractSocket::SocketTimeoutError:
		err = "The socket operation timed out.";
		break;
	case QAbstractSocket::DatagramTooLargeError:
		err = "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
		break;
	case QAbstractSocket::NetworkError:
		err = "An error occurred with the connection.";
		break;
	case QAbstractSocket::UnsupportedSocketOperationError:
		err = "The requested socket operation is not supported by the local operating system.";
		break;
	case QAbstractSocket::UnknownSocketError:
		err = "An unidentified error occurred.";
		break;
	}

	static bool show = false;
	if(_showError && !show)
	{
		show = true;
		QMessageBox msg;
		msg.setText(err);
		msg.exec();
	}
}

void ViewerProcess::socketReadyRead()
{
	QLocalSocket* socket=&_socket;
	QDataStream in(socket);
	ViewerServerToClientMessage mes;
	while(!in.atEnd())
	{
		in>>mes;
		processMessage(mes);
	}
}

void ViewerProcess::processMessage( const ViewerServerToClientMessage& message )
{
	ViewerServerToClientMessage msg=message;
	switch (msg.messageType)
	{
	case ViewerServerToClientMessage::IMPORTED_MODEL:
	_cuState = ViewerServerToClientMessage::IMPORTED_MODEL;
	break;
	case ViewerServerToClientMessage::IMPORTED_RESULT:
	_cuState = ViewerServerToClientMessage::IMPORTED_RESULT;
	break;
	case ViewerServerToClientMessage::IMPORTED_EIGEN:
	_cuState = ViewerServerToClientMessage::IMPORTED_EIGEN;
	break;
	}
}

void ViewerProcess::onViewerFinished( int,QProcess::ExitStatus )
{
	_viewer->deleteLater();
	_viewer = NULL;
}

void ViewerProcess::onViewerError( QProcess::ProcessError error )
{
	QString err;
	switch (error)
	{
	case QProcess::FailedToStart:
		err = "The process failed to start. Either the invoked program is missing, or you may have insufficient permissions to invoke the program.";
		break;
	case QProcess::Crashed:
		err = "The process crashed some time after starting successfully.";
		break;
	case QProcess::Timedout:
		err = "The last waitFor...() function timed out. The state of QProcess is unchanged, and you can try calling waitFor...() again.";
		break;
	case QProcess::WriteError:
		err = "An error occurred when attempting to write to the process. For example, the process may not be running, or it may have closed its input channel.";
		break;
	case QProcess::ReadError:
		err = "An error occurred when attempting to read from the process. For example, the process may not be running.";
		break;
	case QProcess::UnknownError:
		err = "An unknown error occurred. This is the default return value of error().";
		break;
	}

	QMessageBox msg;
	msg.setIcon(QMessageBox::Warning);
	msg.setText(err);
	msg.exec();
}

void ViewerProcess::tryConnectViewer()
{
	int sum = 0;
	while(!_socket.waitForConnected(30000))
	{
		sum += 30;
		Sleep(30);
		connectViewer(_serverName);
		if(sum > 10000)
		{
			QMessageBox msg;
			msg.setWindowTitle(tr("Can't Find The Viewer"));
			msg.setText(tr("Please check the path of the viewer configuration!"));
			msg.exec();
			return;
		}
	}
}
