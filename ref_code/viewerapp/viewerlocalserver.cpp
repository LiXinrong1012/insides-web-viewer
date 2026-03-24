#include "viewerlocalserver.h"

#include "insviewer/socketservermessage.h"


#include <QtNetwork/QLocalSocket>

#include "insviewer/socketservermessage.h"
#include "viewerthread.h"

#include <iostream>
#include <QtGui/QMessageBox>
#include <QApplication>
#include <QFile>

using namespace std;

ViewerLocalServer::ViewerLocalServer(QObject *parent)
	: QLocalServer(parent)
	,_connectedClient(NULL)
	,_viewer(NULL)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(serverNewConnectionHandler()));
}

ViewerLocalServer::~ViewerLocalServer()
{

}

void ViewerLocalServer::importedModel()
{
	cout<<"imported model"<<endl;
	ViewerServerToClientMessage mess;
	mess.messageType=ViewerServerToClientMessage::IMPORTED_MODEL;
	mess.logStr = "this is a message form server";
	
	sendMessage(mess);
}

void ViewerLocalServer::importedResult()
{
	cout<<"imported result"<<endl;
	ViewerServerToClientMessage mess;
	mess.messageType=ViewerServerToClientMessage::IMPORTED_RESULT;
	sendMessage(mess);
}

void ViewerLocalServer::importedEigen()
{
	cout<<"imported eigen"<<endl;
	ViewerServerToClientMessage mess;
	mess.messageType=ViewerServerToClientMessage::IMPORTED_EIGEN;
	sendMessage(mess);
}

void ViewerLocalServer::freshed()
{
	cout<<"finished"<<endl;
	ViewerServerToClientMessage mess;
	mess.messageType=ViewerServerToClientMessage::FRESHED;
	sendMessage(mess);
}

void ViewerLocalServer::log( int logType,const QString& message )
{
	ViewerServerToClientMessage mess;
	mess.messageType=ViewerServerToClientMessage::LOG;
	mess.logType=logType;
	mess.logStr = message;
	sendMessage(mess);
}

void ViewerLocalServer::information( const ViewerUpdateInfo* info )
{
	////if(_connectedClient)
	//{
	//	ViewerServerToClientMessage message;

	//	message.messageType = ViewerServerToClientMessage::INFORMATION;
	//	message.informations["START_TIME"]=QString::number(info.startTime);
	//	message.informations["END_TIME"]=QString::number(info.endTime);
	//	message.informations["ERROR"]=QString::number(info.error);
	//	message.informations["CAL_TIME"]=QString::number(info.calTime);
	//	message.informations["CPU_TIME"]=QString::number(info.cpuTime);
	//	message.informations["REMAIN_TIME"]=QString::number(info.remainTime);
	//	message.informations["PROCESS"]=QString::number(info.process);
	//	message.informations["STEP_TIME"]=QString::number(info.stepTime);
	//	message.informations["MESSAGE"]=QString::fromStdString(info.message);

	//	//qDebug()<<message.informations.count();

	//	if(_connectedClient)
	//		sendMessage(message);
	//}
}

void ViewerLocalServer::serverNewConnectionHandler()
{
	_connectedClient=nextPendingConnection();
	connect(_connectedClient, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
	cout<<"New connection."<<endl;
}

void ViewerLocalServer::socketReadyReadHandler()
{
	QLocalSocket* socket = static_cast<QLocalSocket*>(sender());

	if (socket)
	{
		QDataStream in(socket);
		ViewerSocketToServerMessage mes;
		in>>mes;

		cout<<"Receive message ..."<<endl;
		cout<<qPrintable(mes.message)<<endl;
		processMessage(mes);
	}
}

void ViewerLocalServer::processMessage( const ViewerSocketToServerMessage& message )
{
	if(!_viewer)
		return;
	switch(message.command)
	{
	case ViewerSocketToServerMessage::UNDEFINED:
		break;
	case ViewerSocketToServerMessage::IMPORT_MODEL:
		{
			QThread* thread=new ViewerThread(NULL,_viewer,message.message);
			thread->start();
		}
		break;
	case ViewerSocketToServerMessage::IMPORT_RESULT:
		_viewer->importResult();
		break;
	case ViewerSocketToServerMessage::IMPORT_EIGEN:
		_viewer->importEigen();
		break;
	case ViewerSocketToServerMessage::FRESH:
		_viewer->fresh();
		break;
	case ViewerSocketToServerMessage::HEIGHT_LIGHT:
		_viewer->heightLight();
		break;
	case ViewerSocketToServerMessage::TERMINATE:
		qApp->exit();
	case ViewerSocketToServerMessage::CUSTOMIZEDMESSAGE:
		break;
	}
}

void ViewerLocalServer::sendMessage( const ViewerServerToClientMessage& message )
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

void ViewerLocalServer::heightLight()
{

}


