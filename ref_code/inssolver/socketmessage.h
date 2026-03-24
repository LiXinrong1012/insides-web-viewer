#ifndef SOCKETMESSAGE_H
#define SOCKETMESSAGE_H

#include <QString>
#include <QMap>
#include <QDataStream>


/*!
	\brief 发送给客户端的消息类。
	@author	Jerry He
	@date	2015.1.8
*/
class SendToClientMessage
{
public:
	enum MessageType{UNDEFINED=0,STARTED,PAUSED,RESTARTED,FINISHED,LOG,INFORMATION};
	qint32 version;
	qint32 messageType;
	qint32 logType;
	QString log;
	QMap<QString,QString> informations;

	SendToClientMessage():version(1),messageType(0){}

	friend QDataStream& operator << (QDataStream& out,const SendToClientMessage& message);
	friend QDataStream& operator >> (QDataStream& in,SendToClientMessage& message);
};



/*!
	\brief 发送给服务器的消息类。
	@author	Jerry He
	@date	2015.1.8
*/
class SendToServerMessage
{
public:
	enum CommandType{UNDEFINED=0,START,PAUSE,RESTART,STOP,COMPILE,TERMINATE,CUSTOMIZEDMESSAGE};
	qint32 version;
	qint32 command;
	QString message;

	SendToServerMessage():version(1),command(0){}

	friend QDataStream& operator << (QDataStream& out,const SendToServerMessage& message);
	friend QDataStream& operator >> (QDataStream& in,SendToServerMessage& message);
};

inline QDataStream& operator << (QDataStream& out,const SendToClientMessage& message)
{
	out<<message.version<<message.messageType<<message.logType<<message.log;
	out<<message.informations;
	return out;
}

inline QDataStream& operator >> (QDataStream& in,SendToClientMessage& message)
{
	in>>message.version>>message.messageType>>message.logType>>message.log>>message.informations;
	return in;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline QDataStream& operator<<( QDataStream& out,const SendToServerMessage& message )
{
	out<<message.version<<message.command<<message.message;
	return out;
}

inline QDataStream& operator >> (QDataStream& in,SendToServerMessage& message)
{
	in>>message.version>>message.command>>message.message;
	return in;
}



#endif // SOCKETMESSAGE_H
