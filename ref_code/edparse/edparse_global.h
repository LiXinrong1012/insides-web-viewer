#ifndef EDPARSE_GLOBAL_H
#define EDPARSE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EDPARSE_LIB
# define EDPARSE_EXPORT Q_DECL_EXPORT
#else
# define EDPARSE_EXPORT Q_DECL_IMPORT
#endif

#endif // EDPARSE_GLOBAL_H
