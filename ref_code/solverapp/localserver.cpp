#include "localserver.h"

#include <QtNetwork/QLocalSocket>

#include "inssolver/socketmessage.h"
#include "solverthread.h"

#include <iostream>
#include <QMessageBox>
#include <QApplication>

using namespace std;

LocalServer::LocalServer(QObject *parent)
	: QLocalServer(parent)
	,_connectedClient(NULL)
	,_solver(NULL)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(serverNewConnectionHandler()));
}

LocalServer::~LocalServer()
{

}


void LocalServer::serverNewConnectionHandler()
{
	_connectedClient=nextPendingConnection();
	connect(_connectedClient, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
	cout<<"New connection."<<endl;
}


void LocalServer::socketReadyReadHandler()
{
	QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
	if (socket)
	{
		QDataStream in(socket);
		SendToServerMessage mes;
		in>>mes;

		cout<<"Receive message ..."<<endl;
		cout<<qPrintable(mes.message)<<endl;
		processMessage(mes);
	}
	// 返回到客户端的void sendMessage方法，m_socket->waitForReadyRead()之后的操作
}

void LocalServer::started()
{
	cout<<"started"<<endl;
	SendToClientMessage mess;
	mess.messageType=SendToClientMessage::STARTED;
	sendMessage(mess);
}

void LocalServer::paused()
{
	cout<<"paused"<<endl;
	SendToClientMessage mess;
	mess.messageType=SendToClientMessage::PAUSED;
	sendMessage(mess);
}

void LocalServer::restarted()
{
	cout<<"restarted"<<endl;
	SendToClientMessage mess;
	mess.messageType=SendToClientMessage::RESTARTED;
	sendMessage(mess);
}

void LocalServer::finished()
{
	cout<<"finished"<<endl;
	SendToClientMessage mess;
	mess.messageType=SendToClientMessage::FINISHED;
	sendMessage(mess);
	
}

void LocalServer::log2( int logType,const QString& message )
{
	SendToClientMessage mess;
	mess.messageType=SendToClientMessage::LOG;
	mess.logType=logType;
	mess.log = message;
	sendMessage(mess);
}

void LocalServer::information2(SolverUpdateInfo2& info )
{
	//if(_connectedClient)
	{
		SendToClientMessage message;
		
		message.messageType = SendToClientMessage::INFORMATION;
		message.informations["START_TIME"]=QString::number(info.startTime);
		message.informations["END_TIME"]=QString::number(info.endTime);
		message.informations["ERROR"]=QString::number(info.error);
		message.informations["CAL_TIME"]=QString::number(info.calTime);
		message.informations["CPU_TIME"]=QString::number(info.cpuTime);
		message.informations["REMAIN_TIME"]=QString::number(info.remainTime);
		message.informations["PROCESS"]=QString::number(info.process);
		message.informations["STEP_TIME"]=QString::number(info.stepTime);
		message.informations["MESSAGE"]=QString::fromStdString(info.message);
		
		//qDebug()<<message.informations.count();

		if(_connectedClient)
			sendMessage(message);
	}

}

void LocalServer::processMessage( const SendToServerMessage& message )
{
	if(!_solver)
		return;
	switch(message.command)
	{
	case SendToServerMessage::START:
		{
			QThread* thread=new SolverThread(NULL,_solver);
			thread->start();
		}
		break;
	case SendToServerMessage::PAUSE:
		_solver->pause();	
		break;
	case SendToServerMessage::RESTART:
		_solver->restart();
		break;
	case SendToServerMessage::STOP:
		_solver->stop();
		break;
	case SendToServerMessage::COMPILE:
		break;
	case SendToServerMessage::TERMINATE:
		qApp->exit();
	}
}

void LocalServer::sendMessage( const SendToClientMessage& message )
{
	if(_connectedClient)
	{
		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out<<message;
		_connectedClient->write(block);
		_connectedClient->flush();
	}
}


