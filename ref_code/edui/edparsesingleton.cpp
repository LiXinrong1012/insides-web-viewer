#include "edparsesingleton.h"

EDParseSingleton::EDParseSingleton()
	:_plugin(NULL)
{
}

EDParseSingleton::~EDParseSingleton()
{
}

EDParseSingleton* EDParseSingleton::instance()
{
	static EDParseSingleton _instance;
	if(!_instance._plugin){
		QDir pluginsDir(qApp->applicationDirPath());
		{
			QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("edparse.dll"));
			QObject *plugin = pluginLoader.instance();
			if (plugin){
				EDParsePlugin* modulePluginView = qobject_cast<EDParsePlugin*>(plugin);
				_instance._plugin=modulePluginView;
			}
		}
	}
	return &_instance;
}
