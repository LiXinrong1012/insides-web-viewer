#ifndef  _VDS_SYSCALLS_H_
#define  _VDS_SYSCALLS_H_

//class QString;

void* getSharedMemoryAddress(char *memName, long memSize);
void releaseSharedMemoryAddress(void *mem);

bool VdsSys_DeleteFile(char *lpFileName);

//QString TSVPreGetRootPath();
//QString TSVPreGetTempPath();

#endif