#include "oploadtdythread.h"

#include "include/IExchangeFile.h"

#include "base/MultiProgressOperator.h"
#include "base/console.h"

#include <QtCore>
#include <QtGui>
#include <QPluginLoader>



OPLoadTDYThread::OPLoadTDYThread(QObject *parent)
	: QThread(parent)
{

}

OPLoadTDYThread::~OPLoadTDYThread()
{

}

void OPLoadTDYThread::run()
{
	Base::MultiProgressOperator::startProgress("loading .tdy file");
	IExchangeFile2*	_interface=NULL;

	QDir pluginsDir(qApp->applicationDirPath());
	pluginsDir.cd("plugins");
	{
		QPluginLoader pluginLoader1(pluginsDir.absoluteFilePath("importtdy2.dll"));
		QObject *plugin1 = pluginLoader1.instance();
		if (plugin1) 
			_interface = qobject_cast<IExchangeFile2*>(plugin1);
		else{
			QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("importtdy.dll"));
			QObject *plugin = pluginLoader.instance();
			if (plugin){
				Base::Console().Message("Old importtdy.dll used: %s",pluginLoader.errorString().toStdString().c_str());
				_interface = qobject_cast<IExchangeFile2*>(plugin);
			}
			else
				Base::Console().Error("Load importtdy.dll failed: %s",pluginLoader.errorString().toStdString().c_str());
		}

	}

	if(_interface){
		_interface->clear();
		_interface->setFileName(_fileName);
		_interface->doJob();
		_interface->clear();
	}

	Base::MultiProgressOperator::stopProgress();
	emit jobFinished();
	exec();
}
