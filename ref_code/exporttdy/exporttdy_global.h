#ifndef EXPORTTDY_GLOBAL_H
#define EXPORTTDY_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EXPORTTDY_LIB
# define EXPORTTDY_EXPORT Q_DECL_EXPORT
#else
# define EXPORTTDY_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORTTDY_GLOBAL_H
