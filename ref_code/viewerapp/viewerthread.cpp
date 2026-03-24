#include "viewerthread.h"

#include "insviewer/insviewer.h"

ViewerThread::ViewerThread(QObject *parent,INSViewer* viewer,const QString& fullFileName)
	: QThread(parent)
	,_viewer(viewer)
	,_fileName(fullFileName)
{

}

ViewerThread::~ViewerThread()
{

}

void ViewerThread::run()
{
	_viewer->importModel(_fileName);
}
