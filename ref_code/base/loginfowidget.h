#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include "base/base_global.h"
#include "Base/pre_compile.h"
#include "Base/Console.h"
#include <QWidget>

namespace Ui{class LogInfoWidget;}

namespace Base
{

class BASE_EXPORT LogInfoWidget 
	: public QWidget, public Base::ConsoleObserver
{
	Q_OBJECT

public:
	LogInfoWidget(QWidget *parent = 0);
	~LogInfoWidget();

	/// get calles when a Warning is issued
	virtual void Warning(const char *);
	/// get calles when a Message is issued
	virtual void Message(const char *);
	/// get calles when a Error is issued
	virtual void Error  (const char *);
	/// get calles when a Log Message is issued
	virtual void Log    (const char *);

	virtual const char *Name(void){return "Log information widget";}

protected:
	virtual void customEvent(QEvent* event);
	void append(const char* mess);

private:
	Ui::LogInfoWidget* ui;
};

}

#endif // INFOWIDGET_H
