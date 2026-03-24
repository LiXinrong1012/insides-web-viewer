#include "MyHelpViewer.h"

#include <QHelpEngine>


MyHelpViewer::MyHelpViewer(QWidget* parent,QHelpEngine* engine)
	:QTextBrowser(parent)
	,_helpEngine(engine)
{
}


MyHelpViewer::~MyHelpViewer(void)
{
}


QVariant MyHelpViewer::loadResource( int type, const QUrl & url )
{
	if (url.scheme() == "qthelp")
		return QVariant(_helpEngine->fileData(url));
	else
	{
		return QTextBrowser::loadResource(type, url);

	}
}
