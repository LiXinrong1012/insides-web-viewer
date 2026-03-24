#pragma once

#include "base/base_global.h"

#include <QString>

namespace Base{

/*！
*	存储关于程序的基本信息。
*	@to-do:	加入真实的VersionInfo的支持。
*	@author	Jerry He
*	@date	2014.5.12
*/
class BASE_EXPORT ApplicationInfo
{
public:
	ApplicationInfo(void);
	~ApplicationInfo(void);

	QString getAppName()const;
	QString getVersion()const;
	QString getBuildTime()const;
	void setBuildTime(const char*dt,const char* t);

	QString getAppInfo()const;

private:
	QString _appName;
	QString _version;
	QString _buildTime;
	QString _x86win64;
};


}