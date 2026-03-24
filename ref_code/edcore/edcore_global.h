#ifndef EDCORE_GLOBAL_H
#define EDCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EDCORE_LIB
# define EDCORE_EXPORT Q_DECL_EXPORT
#else
# define EDCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // EDCORE_GLOBAL_H
