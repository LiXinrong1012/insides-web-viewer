#include "loginfowidget.h"
#include <QThread>
#include <QCustomEvent>

#include "ui_LogInfoWidget.h"


namespace Base{


class UpdateTextEvent:public QCustomEvent
{
public:
	enum IDD{ID_UPDATE_TEXT_EVENT=1001};
	UpdateTextEvent(QString s):QCustomEvent(ID_UPDATE_TEXT_EVENT),_str(s){};
	QString str()const {return _str;}
private:
	QString _str;
};


LogInfoWidget::LogInfoWidget(QWidget *parent)
	: QWidget(parent)
{
	ui=new Ui::LogInfoWidget();
	ui->setupUi(this);

#ifndef _DEBUG
	this->bLog=false;
#endif

	Base::Console().AttachObserver(this);
}

LogInfoWidget::~LogInfoWidget()
{
	Base::Console().DetachObserver(this);
	delete ui;
}

void LogInfoWidget::customEvent(QEvent* event)
{
	//int id=event->type();
	//int id2=UpdateTextEvent::ID_UPDATE_TEXT_EVENT;
	if(event->type()==UpdateTextEvent::ID_UPDATE_TEXT_EVENT)
	{
		ui->_infoWidget->append(((UpdateTextEvent*)event)->str());
	}
}

void LogInfoWidget::append(const char* mess)
{
	if(thread()==QThread::currentThread())
		ui->_infoWidget->append(mess);
	else{
		UpdateTextEvent* e=new UpdateTextEvent(mess);
		QApplication::postEvent(this,e);
	}
}

/// get calles when a Warning is issued
void LogInfoWidget::Warning(const char *str)
{
	QString qstr=QString("<font color=blue>&lt;Warning&gt; %1</font>").arg(str);
	append(qstr);
}
/// get calles when a Message is issued
void LogInfoWidget::Message(const char *str)
{
	QString qstr=QString("<font color=green>&lt;Message&gt; %1</font>").arg(str);
	append(qstr);
}
/// get calles when a Error is issued
void LogInfoWidget::Error  (const char *str)
{
	QString qstr=QString("<font color=red>&lt;Error&gt; %1</font>").arg(str);
	append(qstr);

}
/// get calles when a Log Message is issued
void LogInfoWidget::Log    (const char *str)
{
	QString qstr=QString("<font color=black>&lt;Log&gt; %1</font>").arg(str);
	append(qstr);
}


}