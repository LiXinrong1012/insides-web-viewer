#ifndef EXSECSURF_GLOBAL_H
#define EXSECSURF_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EXSECSURF_LIB
# define EXSECSURF_EXPORT Q_DECL_EXPORT
#else
# define EXSECSURF_EXPORT Q_DECL_IMPORT
#endif

#endif // EXSECSURF_GLOBAL_H
