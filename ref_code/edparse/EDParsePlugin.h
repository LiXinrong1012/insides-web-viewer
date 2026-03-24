#pragma once

#include <QString>
#include <QList>
#include <QtCore>

class QMainWindow;

namespace Parse{
	class FileItem;
}
class ISearchReplaceDialog;

/*!
*	This is a plug-in to add functions the Qt's main widget.
*	@author	Jerry He
*	@date	2014.8.31
*/
class EDParsePlugin
{
public:

	virtual ~EDParsePlugin(void) { }

	///获取插件名字接口
	virtual QString getKeyname()=0;

	///初始插件UI接口
	virtual void initUI(QMainWindow* mainWindow)=0;

	///获得搜索和替换对话框接口
	virtual ISearchReplaceDialog* getSearchReplaceDialog()=0;
};

Q_DECLARE_INTERFACE(EDParsePlugin,
	"com.jerryhe.editor.edparseplugin/1.0");