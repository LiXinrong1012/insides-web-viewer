#ifndef SOCKETSERVERMESSAGE_H
#define SOCKETSERVERMESSAGE_H

#include <QString>
#include <QMap>
#include <QDataStream>


/*!
	@brief 发送给前处理的消息类。
	@author	jianjun
	@date	2015.1.20
*/
class ViewerServerToClientMessage
{
public:

	enum MessageType{UNDEFINED=0,IMPORTED_MODEL,IMPORTED_RESULT,IMPORTED_EIGEN,FRESHED,LOG,INFORMATION};
	qint32 version;
	qint32 messageType;
	qint32 logType;
	QString logStr;
	QMap<QString,QString> informations;

	ViewerServerToClientMessage():version(1),messageType(0){}

	friend QDataStream& operator << (QDataStream& out,const ViewerServerToClientMessage& message);
	friend QDataStream& operator >> (QDataStream& in,ViewerServerToClientMessage& message);
};

inline QDataStream& operator << (QDataStream& out,const ViewerServerToClientMessage& message)
{
	out<<message.version<<message.messageType<<message.logType<<message.logStr;
	out<<message.informations;
	return out;
}

inline QDataStream& operator >> (QDataStream& in,ViewerServerToClientMessage& message)
{
	in>>message.version>>message.messageType>>message.logType>>message.logStr>>message.informations;
	return in;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*!
	@brief 发送给后处理的消息类。
	@author	jianjun
	@date	2015.1.20
*/
class ViewerSocketToServerMessage
{
public:
	enum CommandType{UNDEFINED=0,IMPORT_MODEL,IMPORT_RESULT,IMPORT_EIGEN,FRESH,HEIGHT_LIGHT,TERMINATE,CUSTOMIZEDMESSAGE};
	qint32 version;
	qint32 command;
	QMap<QString,QString> informations;

	ViewerSocketToServerMessage():version(1),command(0){}

	friend QDataStream& operator << (QDataStream& out,const ViewerSocketToServerMessage& message);
	friend QDataStream& operator >> (QDataStream& in,ViewerSocketToServerMessage& message);
};

inline QDataStream& operator<<( QDataStream& out,const ViewerSocketToServerMessage& message )
{
	out<<message.version<<message.command<<message.informations;
	return out;
}

inline QDataStream& operator >> (QDataStream& in,ViewerSocketToServerMessage& message)
{
	in>>message.version>>message.command>>message.informations;
	return in;
}



#endif // SOCKETSERVERMESSAGE_H
