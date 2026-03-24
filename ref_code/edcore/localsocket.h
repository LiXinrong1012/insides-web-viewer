#ifndef LOCALSOCKET_H
#define LOCALSOCKET_H

#include "edcore/edcore_global.h"
#include <QObject>
#include <QtNetwork>

namespace INSEditor{


/*!
	@brief  负责与后处理通讯的socket类
	@date   2015.6.5
	@author Jianjun
*/
class EDCORE_EXPORT LocalSocket : public QObject
{
	Q_OBJECT

public:
	LocalSocket(QObject *parent);
	~LocalSocket();

	///连接后处理server通过给定的strServerName
	void connectToServer(const QString &strServerName);

	///发送消息
	void sendMessage(const QString &msg);

private slots:
	///连接成功关联槽,提示连接成功
	void socketConnectedHandler();

	///连接断开关联槽,提示连接断开
	void socketDisConnectedHandler();

	///连接服务错误发生时关联槽,在控制台显示错误信息
	void socketErrorHandler(QLocalSocket::LocalSocketError error);

private:
	QLocalSocket* _socket;
};

}

#endif // LOCALSOCKET_H
