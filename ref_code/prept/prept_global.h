#ifndef PREPT_GLOBAL_H
#define PREPT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PREPT_LIB
# define PREPT_EXPORT Q_DECL_EXPORT
#else
# define PREPT_EXPORT Q_DECL_IMPORT
#endif

#endif // PREPT_GLOBAL_H
