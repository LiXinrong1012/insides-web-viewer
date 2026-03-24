#ifndef VIEWERPROCESS_H
#define VIEWERPROCESS_H

#include <QObject>
#include <QtNetwork/QLocalSocket>
#include <QProcess>

#include "edcore_global.h"

class ViewerServerToClientMessage;
class ViewerSocketToServerMessage;
namespace INSEditor{
	class Project;
}

/*!
	@brief  代表一个打开模型的后处理
	@date   2015.6.10
	@author Jianjun
*/
class EDCORE_EXPORT ViewerProcess : public QObject
{
	Q_OBJECT
public:
	ViewerProcess(INSEditor::Project *parent);
	~ViewerProcess();

	/// 尝试连接后处理的server
	void connectViewer(const QString &strServerName);

	/// 发送消息给后处理
	void sendMessage(const ViewerSocketToServerMessage& mes);

	/// 获得当前状态
	int getCuState(){return _cuState;}

	/// 获得当前消息
	QString getCuMsg(){return _cuMsg;}

	/// 获得后处理进程QProcess
	QProcess*	getViewer(){return _viewer;}

private slots:
	/// 服务连接成功关联槽 可提示连接成功
	void socketConnectedHandler();

	/// 服务连接断开关联槽 可提示连接断开
	void socketDisConnectedHandler();

	/// 连接错误关联槽 显示错误信息
	void socketErrorHandler(QLocalSocket::LocalSocketError error);

	/// 有新信息关联槽
	void socketReadyRead();

	/// 后处理关闭关联槽
	void onViewerFinished(int,QProcess::ExitStatus);

	/// 当后处理错误时调用
	void onViewerError(QProcess::ProcessError error);

	/// 尝试连接后处理
	void tryConnectViewer();

private:
	/// 消息解析函数
	void processMessage(const ViewerServerToClientMessage& message);
	
private:
	QLocalSocket _socket;
	QProcess*	 _viewer;
	QString		 _serverName;
	int			_cuState;
	QString		_cuMsg;
	bool		_showError;
};

#endif // VIEWERPROCESS_H

