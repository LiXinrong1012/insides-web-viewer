#pragma once

#include <QString>
#include <QtPlugin>
class QMainWindow;

/*!
*	This is a plug-in to add functions the Qt's main widget.
*	@author	Jerry He
*	@date	2014.8.31
*/
class INSUIPlugin
{
public:

	virtual ~INSUIPlugin(void) { }

	virtual QString getKeyname()=0;
	virtual void initUI(QMainWindow* mainWindow)=0;
};

Q_DECLARE_INTERFACE(INSUIPlugin,
	"com.jerryhe.viewer.insuiplugin/1.0");

