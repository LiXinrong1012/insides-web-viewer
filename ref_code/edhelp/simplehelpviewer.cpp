#include "simplehelpviewer.h"

#include <QHelpEngine>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QFile>


SimpleHelpViewer::SimpleHelpViewer(QWidget* parent,QHelpEngine* engine)
	:QTextBrowser(parent)
	,_helpEngine(engine)
{
}


SimpleHelpViewer::~SimpleHelpViewer(void)
{
}
QVariant SimpleHelpViewer::loadResource( int type, const QUrl & url )
{
	if (url.scheme() == "qthelp")
		return QVariant(_helpEngine->fileData(url));
	else
		return QTextBrowser::loadResource(type, url);
	
}
