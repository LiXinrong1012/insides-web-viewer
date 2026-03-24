#include "windows.h"

#include "Vds_SysCalls.h"
//#include "qdir.h"
//#include "qstring.h"



void* getSharedMemoryAddress(char *memName, long memSize)
{
	void *retPtr = NULL;
	HANDLE hObject;
	//hObject=::OpenFileMapping(FILE_MAP_WRITE,0,memName);
	hObject=::CreateFileMapping((HANDLE)-1,0,PAGE_READWRITE,0,memSize,(memName));
	retPtr=(int*)::MapViewOfFile(hObject,FILE_MAP_WRITE,0,0,memSize);
	return retPtr;
}

void releaseSharedMemoryAddress(void *mem)
{
}

bool VdsSys_DeleteFile(char *lpFileName)
{
	if (DeleteFile(lpFileName))
		return true;
	else 
		return false;
}

//QString TSVPreGetRootPath()
//{
//	QString qTemp = QDir::currentPath();
//	return QDir::convertSeparators(qTemp);
//}
//
//QString TSVPreGetTempPath()
//{
//	QString qTemp = getenv("TSV_PRE_TEMP");
//	if( qTemp.isEmpty() )
//	{
//		qTemp = QDir::currentPath();
//		qTemp.append("/Temp");
//	}
//	return QDir::convertSeparators(qTemp);
