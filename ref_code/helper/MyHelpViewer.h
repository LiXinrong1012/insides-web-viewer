#pragma once


#include <QTextBrowser>

class QHelpEngine;

class MyHelpViewer :
	public QTextBrowser
{
public:
	MyHelpViewer(QWidget* parent,QHelpEngine* engine);
	~MyHelpViewer(void);

	virtual QVariant	loadResource ( int type, const QUrl & name );

private:
	QHelpEngine* _helpEngine;
};

