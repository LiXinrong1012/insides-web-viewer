#pragma once

#include <QString>
#include <QList>
#include <QtCore>

class QMainWindow;

/*!
*	This is a general plugin to add functions the Qt's main widget.
*	@author	Jerry He
*	@date	2014.8.21
*/
class ModulePlugin
{
public:

	virtual ~ModulePlugin(void) { }

	virtual QString getKeyname()=0;
	virtual void setMainWindow(QMainWindow* mainWindow)=0;
	virtual void setParameters(const QList<QString>& paras)=0;
	virtual bool doJob()=0;
};

Q_DECLARE_INTERFACE(ModulePlugin,
	"com.jerryhe.editor.moduleplugin/1.0");