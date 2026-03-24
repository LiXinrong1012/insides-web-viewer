
/*
* $Id: tempfile_utils.cpp,v 1.12 2010-05-06 17:02:20 reuben Exp $
*/

#include "tempfile_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _MSC_VER
#pragma warning(disable: 4996) // don't complain about standard string functions
#include <windows.h>
#include <assert.h>
#include <io.h>
#else
#include <unistd.h>
#ifndef OSX_SYSTEM
int mkstemps ( char alter * tempFileNameOut, int suffixlen ) {
	int tempFileNameOutLen = strlen(tempFileNameOut);
	char *tempFileNameCopy = new char [tempFileNameOutLen + 1];
	char *suffixCopy = new char [suffixlen + 1];
	strcpy(tempFileNameCopy, tempFileNameOut);
	strcpy(suffixCopy, tempFileNameCopy + tempFileNameOutLen - suffixlen);
	suffixCopy[suffixlen] = 0;
	tempFileNameCopy[tempFileNameOutLen - suffixlen] = 0;
	
	int fileDescriptor = mkstemp(tempFileNameCopy);
	if (fileDescriptor != -1)
		sprintf(tempFileNameOut, "%s%s", tempFileNameCopy, suffixCopy);

	delete [] tempFileNameCopy;
	delete [] suffixCopy;

	return fileDescriptor;
}
#endif
#endif

#include "utf_utils.h"

void GenerateTempFileName ( char alter * tempFileNameOut, char const * extension ) {
#ifdef _MSC_VER
	char temp_dir[_MAX_DIR];
	DWORD dir_len = 0;
	
	dir_len = GetTempPathA(_MAX_DIR, temp_dir);
	assert(dir_len != 0);	
	assert(dir_len <= _MAX_DIR);
	UINT res = 0;
	res = GetTempFileNameA(temp_dir, "HOOPS", 0, tempFileNameOut);
	assert(res != 0);
	// if extension specified, replace .tmp with user-provided value
	if (extension) {
		char *old_extension = strrchr(tempFileNameOut, '.');
		if (extension[0] == '.')
			old_extension[0] = 0;
		else
			old_extension[1] = 0;
		strcat(tempFileNameOut, extension);
	}
#else
	strcpy(tempFileNameOut, "/tmp/tmpXXXXXX");
	int ext_len = 0;
	
	if (extension) {
		if (extension[0] != '.') {
			strcat(tempFileNameOut, ".");
			ext_len += 1;
		}
		strcat(tempFileNameOut, extension);
		ext_len += strlen(extension);
	}
	else {
		strcat(tempFileNameOut, ".tmp");
		ext_len += 4;
	}
	
	int fileDescriptor = mkstemps(tempFileNameOut, ext_len);
	if (fileDescriptor == -1) {
		printf("mkstemps call failed.\nerrno: %d\t%s\n", errno, strerror(errno));
		tempFileNameOut[0] = 0;
	}
	else
		close(fileDescriptor);
#endif
}

void GenerateTempFileName ( wchar_t alter * tempFileNameOut, wchar_t const * extension ) {
#ifdef _MSC_VER
	wchar_t temp_dir[_MAX_DIR];
	DWORD dir_len = 0;
	dir_len = GetTempPathW(_MAX_DIR,  temp_dir);
	assert(dir_len != 0);	
	assert(dir_len <= _MAX_DIR);
	UINT res = 0;
	res = GetTempFileNameW(temp_dir, L"HOOPS", 0, tempFileNameOut);
	assert(res != 0);
	// if extension is specified replace .tmp with user-specified value
	if (extension) {
		wchar_t *old_extension = wcsrchr(tempFileNameOut, L'.');
		if (extension[0] == L'.')
			old_extension[0] = 0;
		else
			old_extension[1] = 0;
		wcscat(tempFileNameOut, extension);
	}
#else
	char temp_template[TEMPFILE_UTILS_BUFFER_SIZE];
	
	if (extension)
		GenerateTempFileName(temp_template, reinterpret_cast<char const *>(H_UTF8(extension).encodedText()));
	else
		GenerateTempFileName(temp_template);
	
	if (temp_template[0] == 0)
		tempFileNameOut[0] = 0;
	else
		wcscpy(tempFileNameOut, H_WCS(temp_template).encodedText());
#endif
}

#ifdef _MSC_VER
static 
void check_error()
{
#if _DEBUG
	/* Copy the error to the buffer so we can see it
	   in the debugger, otherwise do nothing with it. */
	char error_msg[100] = {""};
	strcpy(error_msg, strerror(errno));
	return;
#endif
}
#endif

FILE * GenerateTmpFilePtr ()
{
	FILE * file = 0;
#ifdef _MSC_VER
	int fd = 0;
	do {
		char fn[_MAX_DIR];
		GenerateTempFileName(fn, ".tmp");
		_unlink(fn);
		fd = _open(fn, _O_BINARY | _O_CREAT | _O_TEMPORARY | _O_EXCL | _O_RDWR, _S_IREAD | _S_IWRITE);
	}while(fd < 0 && errno == EEXIST);

	if(fd < 0){
		check_error();
		return 0;
	}

	file = _fdopen(fd, "w+b");
	if(!file){
		check_error();
		int tmp = errno;
		_close(fd);
		errno = tmp;
	}
#else
	file = tmpfile();
#endif

	return file;
}
