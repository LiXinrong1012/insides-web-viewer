#include "localserver.h"
#include <QDebug>
#include "Base/Console.h"
#include "insviewer/socketservermessage.h"

using namespace Base;

LocalServer::LocalServer(QObject *parent)
	: QObject(parent)
	,_server(NULL)
	,_messageListener(NULL)
	,_socket(NULL)
{
	_server = new QLocalServer(this);
	QObject::connect(_server, SIGNAL(newConnection()), this, SLOT(serverNewConnectionHandler()));
}


LocalServer::~LocalServer()
{
	_server->close();
	delete _server;

}

void LocalServer::runServer( const QString& serverName )
{
	Console().Log("运行服务: %s",serverName.toStdString().c_str());

	QLocalServer::removeServer(serverName);
	bool ok = _server->listen(serverName);
	if (!ok)
	{
		// TODO:
		Console().Error("Run Server failed");
	}
}

void LocalServer::serverNewConnectionHandler()
{
	Console().Log("新连接");
	QLocalSocket* socket = _server->nextPendingConnection();
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
	QObject::connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
	_socket=socket;
}

void LocalServer::socketReadyReadHandler()
{
	QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
	if (socket)
	{
		QDataStream stream(socket);
		while(!stream.atEnd())
		{
			ViewerSocketToServerMessage mes;
			stream>>mes;
			Console().Log("Get message from Editor. Message type = %d",mes.command);

			if(_messageListener)
				_messageListener->onMessageReceived(mes);
		}
	}
}

void LocalServer::sendToClient( const ViewerServerToClientMessage& mes )
{
	Console().Log("Local Server is sending message: %d",mes.messageType);
	QByteArray bytes;
	QDataStream ss(&bytes,QIODevice::WriteOnly);
	ss<<mes;
	
	if(_socket){
		_socket->write(bytes);
		_socket->flush();
	}
}
