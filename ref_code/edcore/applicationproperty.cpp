#include "applicationproperty.h"

#include <QSettings>
#include <QFile>
#include <QDir>
#include <QCoreApplication>

namespace INSEditor
{

void ApplicationProperty::load()
{
	QString appDir = QCoreApplication::applicationDirPath() + "/settings/";
	QSettings settings(appDir + "insides-editor.ini", QSettings::IniFormat);

	settings.beginGroup("DIR_CONFIG");
	viewerExecutablePath=settings.value("viewer_dir",QString()).toString();
	solverExecutablePath=settings.value("solver_dir",QString()).toString();
	if(solverExecutablePath.isEmpty())
	{
		QDir dir(QCoreApplication::applicationDirPath());
		dir.cd("..");
		dir.cd("solver");
		QString  tmpStr = dir.currentPath() + "/solverapp.exe";
		QFile file(tmpStr);
		if(file.exists())
			solverExecutablePath = tmpStr;
	}
	fileDiffExecutablePath=settings.value("filediff_dir",QString()).toString();
	materialLibraryPath = settings.value("material_dir",QString()).toString();
	settings.endGroup();

	settings.beginGroup("SOLVE_CONFIG");
	logsUpdateFrequency = settings.value("logs_update",2).toInt();
	treeProcessUpdateFrequency = settings.value("tree_update",2).toInt();
	maxSolveNumber = settings.value("max_solve",3).toInt();
	isShowSolverUI = settings.value("show_solver",false).toBool();
	settings.endGroup();

	settings.beginGroup("FORMAT_CONFIG");
	formatIndentationValue = settings.value("indentation",4).toInt();
	formatLineMaxNumValue = settings.value("line_max_num",0).toInt();
	settings.endGroup();

	settings.beginGroup("CUSTOM_CONFIG");
	isShowLastOpenedFiles = settings.value("show_last",true).toBool();
	isCreateModelTree = settings.value("create_model_tree",true).toBool();
	isAutoShowHelp = settings.value("auto_help",false).toBool();
	settings.endGroup();

	settings.beginGroup("AUTO_CHECK_UPDATE");
	isAutoCheckUpdate = settings.value("auto_check_update",true).toBool();
	settings.endGroup();
}

void ApplicationProperty::save()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-editor.ini", QSettings::IniFormat);

	settings.beginGroup("DIR_CONFIG");
	settings.setValue("viewer_dir", this->viewerExecutablePath);
	settings.setValue("solver_dir", this->solverExecutablePath);
	settings.setValue("filediff_dir", this->fileDiffExecutablePath);
	settings.setValue("material_dir",this->materialLibraryPath);
	settings.endGroup();

	settings.beginGroup("SOLVE_CONFIG");
	settings.setValue("logs_update",this->logsUpdateFrequency);
	settings.setValue("tree_update",this->treeProcessUpdateFrequency);
	settings.setValue("max_solve",this->maxSolveNumber);
	settings.setValue("show_solver",this->isShowSolverUI);
	settings.endGroup();

	settings.beginGroup("FORMAT_CONFIG");
	settings.setValue("indentation",this->formatIndentationValue);
	settings.setValue("line_max_num",this->formatLineMaxNumValue);
	settings.endGroup();

	settings.beginGroup("CUSTOM_CONFIG");
	settings.setValue("show_last",this->isShowLastOpenedFiles);
	settings.setValue("create_model_tree",this->isCreateModelTree);
	settings.setValue("auto_help",this->isAutoShowHelp);
	settings.endGroup();

	settings.beginGroup("AUTO_CHECK_UPDATE");
	settings.setValue("auto_check_update",this->isAutoCheckUpdate);
	settings.endGroup();
}

ApplicationProperty::ApplicationProperty()
{
	load();
}


} // end namespace INSEditor