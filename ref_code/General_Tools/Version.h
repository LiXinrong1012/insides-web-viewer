#ifndef VERSION_H
#define VERSION_H

struct VersionInfo
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


#endif 