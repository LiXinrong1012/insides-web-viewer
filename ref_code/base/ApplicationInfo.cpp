#include "ApplicationInfo.h"

#include <QtCore>

namespace Base
{

ApplicationInfo::ApplicationInfo(void)
	:_appName("INSIDES Viewer")
	,_version("1.0.0")
{
	_buildTime=QString("%1 %2").arg(__DATE__).arg(__TIME__);

#ifdef _WIN32
	_x86win64="Windows 32 bit OS";
#else
	_x86win64="Windows 64 bit OS";
#endif
}


ApplicationInfo::~ApplicationInfo(void)
{
}

void ApplicationInfo::setBuildTime( const char* dt,const char* t )
{
	_buildTime=QString("%1 %2")
		.arg(t)
		.arg(dt)
		;
}

QString Base::ApplicationInfo::getAppName() const
{
	return _appName;
}

QString Base::ApplicationInfo::getVersion() const
{
	return _version;
}

QString Base::ApplicationInfo::getBuildTime() const
{
	return _buildTime;
}

QString Base::ApplicationInfo::getAppInfo() const
{
	return QString("<font color=red>%1 %2 </font>( built on %3 for %4 )").arg(_appName).arg(_version).arg(_buildTime)
		.arg(_x86win64);
}



}