#ifndef VERSION_H
#define VERSION_H

#include "base/base_global.h"

namespace Base{

struct BASE_EXPORT VersionInfo
{
	int major ;
	int minor ;
	int sub  ;

	int build ;
};

#define LANGUAGE_CHINIESE

// 1.0.0.1 : 最开始的版本，创建于2013.11.7
static VersionInfo version = { 1, 0, 0, 1 } ;

void setVersion(VersionInfo ver) ;
VersionInfo getVersion(void) ;


char* getBuildStamp(void) ;

char* getApplicationName(void) ;

}

#endif 