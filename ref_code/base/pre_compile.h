#define POSIX
#define FC_OS_WIN32

//std.
#include <vector>
#include <map>
#include <set>
#include <string>
#include <list>
# include <cstring>


//
#include <assert.h>
#include <iostream>


//c
#include <stdarg.h>
# include <cassert>
# include <cstdio>
# include <cstdlib>
# include <fstream>
# include <climits>
# if defined (FC_OS_LINUX) || defined(FC_OS_CYGWIN) || defined(FC_OS_MACOSX)
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# elif defined (FC_OS_WIN32)
# include <direct.h>
# include <io.h>
# include <windows.h>

#ifdef _MSC_VER
#   pragma warning( disable : 4251 )
#   pragma warning( disable : 4503 )
#   pragma warning( disable : 4275 )
#   pragma warning( disable : 4786 )  // specifier longer then 255 chars
#   pragma warning( disable : 4661 )  // no suitable definition provided for explicit
#   pragma warning( disable : 4996 )
#pragma warning(disable:4006)
#pragma warning(disable:4221)
#endif                                // template instantiation request

#include "base/base_global.h"

# endif