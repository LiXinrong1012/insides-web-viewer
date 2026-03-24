#pragma once


#include <QTextBrowser>
#include <QWebView>

class QHelpEngine;

class MyWebHelpViewer :
	public QWebView
{
	Q_OBJECT
public:
	MyWebHelpViewer(QWidget* parent,QHelpEngine* engine);
	~MyWebHelpViewer(void);

//	virtual QVariant	loadResource ( int type, const QUrl & name );
	public slots:
		void loadPage(const QUrl &loadUrl);
		void setSource(const QUrl & url);
		void saveSetting();
		void loadSetting();

private:
	QHelpEngine* _helpEngine;
	QString _outPutDir;
};

