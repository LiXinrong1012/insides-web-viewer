#ifndef PREVXY_GLOBAL_H
#define PREVXY_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PREVXY_LIB
# define PREVXY_EXPORT Q_DECL_EXPORT
#else
# define PREVXY_EXPORT Q_DECL_IMPORT
#endif

#endif // PREVXY_GLOBAL_H
