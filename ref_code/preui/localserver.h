#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "preui/preui_global.h"
#include <QObject>
#include <QtNetwork>

#include "insviewer/socketservermessage.h"


class IMessageListener
{
public:
	virtual void onMessageReceived(const ViewerSocketToServerMessage& mess)=0;
	virtual void onConnected(){}
	virtual void onDisconnected(){}
};


class PREUI_EXPORT LocalServer : public QObject
{
	Q_OBJECT

public:
	LocalServer(QObject *parent);
	~LocalServer();

	void setMessageListener(IMessageListener* listener){_messageListener=listener;}

	void runServer(const QString& serverName);

	void sendToClient(const ViewerServerToClientMessage& mes);

	private slots:
		void serverNewConnectionHandler();
		void socketReadyReadHandler();

private:
	QLocalServer*	_server;
	QLocalSocket*	_socket;
	IMessageListener* _messageListener;
};

#endif // LOCALSERVER_H
