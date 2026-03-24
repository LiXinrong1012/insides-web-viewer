#ifndef VIEWERLOCALSERVER_H
#define VIEWERLOCALSERVER_H

#include <QtNetwork/QLocalServer>
#include <QTimer>

#include "insviewer/insviewer.h"
#include "insviewer/insviewermanager.h"

class ViewerServerToClientMessage;
class ViewerSocketToServerMessage;

class ViewerLocalServer : public QLocalServer,public INSViewerManager
{
	Q_OBJECT

public:
	ViewerLocalServer(QObject *parent=0);
	~ViewerLocalServer();

	void setViewer(INSViewer* viewer){_viewer=viewer;}

	virtual void importedModel();
	virtual void importedResult();
	virtual void importedEigen();
	virtual void freshed();
	virtual void heightLight();
	virtual void log(int logType,const QString& message);
	virtual void information(const ViewerUpdateInfo* info);
private slots:
	void serverNewConnectionHandler();
	void socketReadyReadHandler();
private:
	void processMessage(const ViewerSocketToServerMessage& message);
	void sendMessage(const ViewerServerToClientMessage& message);
private:
	QLocalSocket*	_connectedClient;
	INSViewer*		_viewer;
};

#endif // VIEWERLOCALSERVER_H

