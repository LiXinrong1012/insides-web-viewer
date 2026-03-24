#ifndef VIEWERTHREAD_H
#define VIEWERTHREAD_H

#include <QThread>

class INSViewer;
class ViewerThread : public QThread
{
	Q_OBJECT

public:
	ViewerThread(QObject *parent,INSViewer* viewer,const QString& fullFileName);
	~ViewerThread();

	void run();
private:
	INSViewer* _viewer;
	QString _fileName;
};

#endif // VIEWERTHREAD_H
