#ifndef MYCENTRALWIDGET_H
#define MYCENTRALWIDGET_H

#include <QObject>
#include <QUrl>

class HelpViewer;

class MyCentralWidget : public QObject
{
	Q_OBJECT

public:
	MyCentralWidget(QObject *parent);
	~MyCentralWidget();

	void setHelpViewer(HelpViewer* viewer){_helpViewer=viewer;}

	static MyCentralWidget* instance();

	void setSource(const QUrl& url);

private:
	static MyCentralWidget* _instance;
	HelpViewer*		_helpViewer;
	
};

#endif // MYCENTRALWIDGET_H
