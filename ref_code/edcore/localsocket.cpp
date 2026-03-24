#include "localsocket.h"
#include <qdebug>

namespace INSEditor
{


LocalSocket::LocalSocket(QObject *parent)
	: QObject(parent)
{
	_socket = new QLocalSocket(this);

	QObject::connect(_socket, SIGNAL(connected()), this, SLOT(socketConnectedHandler()));
	QObject::connect(_socket, SIGNAL(disconnected()), this, SLOT(socketDisConnectedHandler()));
	QObject::connect(_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(socketErrorHandler(QLocalSocket::LocalSocketError)));
}

LocalSocket::~LocalSocket()
{
	_socket->disconnectFromServer();
	delete _socket;
}

void LocalSocket::connectToServer( const QString &strServerName )
{
	// 服务端的serverNewConnectionHandler成员方法将被调用
	_socket->connectToServer(strServerName);
	if (_socket->waitForConnected())
	{
		// TODO:
	}
}

void LocalSocket::sendMessage( const QString &msg )
{
	_socket->write(msg.toStdString().c_str());
	_socket->flush();

	// waitForReadyRead将激发信号readyRead()， 我们在
	// 与服务端创建连接时，已将readyRead()，绑定到了服务
	// 端的槽socketReadyReadHandler成员方法
	//if (!_socket->bytesAvailable())
		//_socket->waitForReadyRead();    

	//QTextStream stream(_socket);
	//QString respond = stream.readAll();

	//Console().Log("Read Data From Server: %s",respond.toStdString().c_str());
}

void LocalSocket::socketConnectedHandler()
{
	qDebug() << "connected.";
}

void LocalSocket::socketDisConnectedHandler()
{
	qDebug() << "disconnected.";
}

void LocalSocket::socketErrorHandler(QLocalSocket::LocalSocketError error )
{
	qWarning() << error;
}


}