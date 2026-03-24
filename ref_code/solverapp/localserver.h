#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QtNetwork/QLocalServer>
#include <QTimer>

#include "inssolver/inssolver.h"
#include "inssolvermanager2.h"

class SendToServerMessage;
class SendToClientMessage;

/*!
	@brief 用来创建服务器，被外部连接者连接并实现消息交互的类。
	@author	Jerry He
	@date	2015.1.7
*/
class LocalServer : public QLocalServer, public INSSolverManager2
{
	Q_OBJECT

public:
	LocalServer(QObject *parent=0);
	~LocalServer();

	void setSolver(INSSolver* solver){_solver=solver;}


	virtual void started();
	virtual void paused();
	virtual void restarted();
	virtual void finished();
	virtual void log2(int logType,const QString& message);
	virtual void information2(SolverUpdateInfo2& info);


	private slots:
		void serverNewConnectionHandler();
		void socketReadyReadHandler();

private:
	void processMessage(const SendToServerMessage& message);
	void sendMessage(const SendToClientMessage& message);

private:
	QLocalSocket*	_connectedClient;
	INSSolver*		_solver;
	
};

#endif // LOCALSERVER_H
