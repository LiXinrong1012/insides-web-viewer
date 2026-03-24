#ifndef PROCESSWRAPPER_H
#define PROCESSWRAPPER_H

#include "edcore/edcore_global.h"
#include <QObject>
#include <QProcess>


namespace INSEditor
{
class LocalSocket;


/*!
*	The \class ProcessWrapper is used to handler communication with 
*	the INSIDES-Viewer application.
*	@author	Jerry He
*	@date	2014.8.21
*/
class EDCORE_EXPORT ProcessWrapper : public QObject
{
	Q_OBJECT

public:
	ProcessWrapper(QObject *parent);
	~ProcessWrapper();

	///通知后处理更新
	void update(const QString& modelFileName);

	///高亮
	void highlight(const QString& itemName);

	///发送消息给后处理
	void sendMessage(const QString& message);

	///清除连接相关类
	void clear();


protected slots:
	// viewer related slots
	void onViewerStarted();
	void onViewerFinished( int exitCode, QProcess::ExitStatus exitStatus);
	void onViewerError( QProcess::ProcessError error);

private:
	QProcess*		_viewerProcess;
	LocalSocket*	_localSocket;
	QString			_viewerServerID;
	QString			_modelFileName;
	
};


}	// end namespace INSEditor

#endif // PROCESSWRAPPER_H
