#include "AppConfiguration.h"

#include "ParametersManager.h"

namespace Base{

class AppConfiguration::Internals
{
public:
	QString startupDirectory;
	QString workingDirectory;
	QString solverDirectory;
	QString projectName;
	ParametersManager	_parameterManager;

	Internals()
	{

	}
};

AppConfiguration::AppConfiguration(void)
{
	_internals=new AppConfiguration::Internals();
}


AppConfiguration::~AppConfiguration(void)
{
	delete _internals;
}

QString AppConfiguration::startupDirectory() const
{
	return _internals->startupDirectory;
}

void AppConfiguration::setStartupDirectory( const QString& str )
{
	_internals->startupDirectory=str;
}

QString AppConfiguration::workingDirectory() const
{
	return _internals->workingDirectory;
}

void AppConfiguration::setWorkingDirectory( const QString& str )
{
	_internals->workingDirectory=str;
}

QString AppConfiguration::getSolverDirectory() const
{
	const ParameterItem* item= getParametersManager()->get("SolverDir","System");
	if(item)
		return item->getVariant().toString();
	return QString();
}

void AppConfiguration::setSolverDirectory( const QString& str )
{

}

ParametersManager* AppConfiguration::getParametersManager()
{
	return &_internals->_parameterManager;
}

const ParametersManager* AppConfiguration::getParametersManager() const
{
	return &_internals->_parameterManager;
}

QString AppConfiguration::projectFullName() const
{
	return _internals->projectName;
}

void AppConfiguration::setProjectFullName( const QString& str )
{
	_internals->projectName=str;
}



AppConfiguration* Base::AppConfiguration::instance()
{
	static AppConfiguration _instance;
	return &_instance;
}

}	//end namespace Base