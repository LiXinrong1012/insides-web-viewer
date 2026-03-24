#pragma once

#include "moduleplugin.h"
#include "searchlineedit.h"

#include <QLineEdit>
#include <QListWidget>
#include <QtHelp>
#include <QKeyEvent>


class ModulePluginHelp: public QObject, public ModulePlugin
{
	Q_OBJECT
	Q_INTERFACES(ModulePlugin)

public:

	virtual ~ModulePluginHelp(void) { }

	virtual QString getKeyname();
	virtual void setMainWindow(QMainWindow* mainWindow);
	virtual void setParameters(const QList<QString>& paras);
	virtual bool doJob();

	protected slots:
		void showTopicChooser(QMap<QString,QUrl>,QString);
		void activateCurrentCentralWidgetTab();

private:
	QMainWindow* _mainWindow;
	QHelpIndexWidget* _searchIndexWidget;
	QHelpSearchEngine* _helpSearchEngine;
	QHelpSearchQueryWidget* _helpSearchQueryWidget;
	QHelpSearchResultWidget* _helpSearchResultWidget;

	QHelpIndexModel* _indexModel;
};
