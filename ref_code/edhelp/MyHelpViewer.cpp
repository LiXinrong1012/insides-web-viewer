#include "MyWebHelpViewer.h"

#include <QHelpEngine>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QFile>


MyWebHelpViewer::MyWebHelpViewer(QWidget* parent,QHelpEngine* engine)
	:QWebView(parent)
	,_helpEngine(engine)
{
	setAcceptDrops(false);
	settings()->setAttribute(QWebSettings::JavaEnabled, false);
	settings()->setAttribute(QWebSettings::PluginsEnabled, false);

	setPage(new QWebPage(this));
}


MyWebHelpViewer::~MyWebHelpViewer(void)
{
}

void MyWebHelpViewer::loadPage( const QUrl &loadUrl )
{
	QString s = loadUrl.toString();
	int index = s.lastIndexOf("/")+1;

	QString htmlName =s.right(s.size()-index);
	if(htmlName=="")
		htmlName = "index.html";
	QString fullName = "D:/tsinghuaDir/INSHelp/Output/html/"+htmlName;
	this->load(QUrl(fullName));
	
}
///备用
void MyWebHelpViewer::saveSetting()
{
	QSettings setting("help","helpsetting");//随便放一个
	setting.beginGroup("helper");
	if(_outPutDir.isEmpty())
		return ;
	setting.setValue("outputhtmldir",_outPutDir);

	setting.endGroup();
}

void MyWebHelpViewer::loadSetting()
{
	QSettings setting("help","helpsetting");
	setting.beginGroup("helper");

	QString dir = setting.value("outputhtmldir").toString();
	if(dir.isEmpty())
	{
		return;
	}
	_outPutDir = dir;

	setting.endGroup();
}

void MyWebHelpViewer::setSource( const QUrl & url )
{
	QString s = url.toString();
	this->load(url);
	//this->setUrl(url);
}


//QVariant MyHelpViewer::loadResource( int type, const QUrl & url )
//{
//	if (url.scheme() == "qthelp")
//		return QVariant(_helpEngine->fileData(url));
//	else
//		return QTextBrowser::loadResource(type, url);
//	
//}
