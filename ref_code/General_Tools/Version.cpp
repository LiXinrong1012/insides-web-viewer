#include "Version.h"

void setVersion(VersionInfo ver)
{
	version = ver ;
}

VersionInfo getVersion(void)
{
	return version ;
}


char* getBuildStamp(void) 
{
	return __TIMESTAMP__  ;
}

char* getApplicationName(void) 
{
	return "EasyPlot 1.0" ;
}

