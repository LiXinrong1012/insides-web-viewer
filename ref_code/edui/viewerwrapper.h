#ifndef VIEWERWRAPPER_H
#define VIEWERWRAPPER_H

#include <QObject>
#include <QProcess>

namespace INSEditor
{
	class LocalSocket;
}

/*!
*	The \class ViewerWrapper is used to handler communiation with 
*	the INSIDES-Viewer application.
*	@author	Jerry He
*	@date	2014.8.21
*/
/*!
	@brief  负责与后处理进行通信
	@date   2015.6.23
	@author Jerry
*/
class ViewerWrapper : public QObject
{
	Q_OBJECT

public:
	ViewerWrapper(QObject *parent);
	~ViewerWrapper();

	///更改模型文件
	void update(const QString& modelFileName);

	///高亮显示
	void highlight(const QString& itemName);

	///发送信息
	void sendMessage(const QString& message);

	///清除
	void clear();

protected slots:
	// viewer related slots
	///当后处理打开后的回调函数
	void onViewerStarted();

	///当后处理关掉后
	void onViewerFinished( int exitCode, QProcess::ExitStatus exitStatus);

	///当后处理发生错误时调用 。
	void onViewerError( QProcess::ProcessError error);

private:
	///后处理的进程保存
	QProcess*		_viewerProcess;

	///socket
	INSEditor::LocalSocket*	_localSocket;

	///后处理服务名
	QString			_viewerServerID;

	///模型文件名
	QString			_modelFileName;
	
};

#endif // VIEWERWRAPPER_H
