#pragma once


#include <QTextBrowser>
#include <QTextBrowser>

class QHelpEngine;

class SimpleHelpViewer :
	public QTextBrowser
{
	Q_OBJECT
public:
	SimpleHelpViewer(QWidget* parent,QHelpEngine* engine);
	~SimpleHelpViewer(void);

	virtual QVariant	loadResource ( int type, const QUrl & name );
	public slots:

private:
	QHelpEngine* _helpEngine;
	QString _outPutDir;
};