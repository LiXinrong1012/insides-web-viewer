#ifndef IMPORTTDY_GLOBAL_H
#define IMPORTTDY_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef IMPORTTDY_LIB
# define IMPORTTDY_EXPORT Q_DECL_EXPORT
#else
# define IMPORTTDY_EXPORT Q_DECL_IMPORT
#endif

#endif // IMPORTTDY_GLOBAL_H
