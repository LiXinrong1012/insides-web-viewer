#ifndef PREVTC_GLOBAL_H
#define PREVTC_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PREVTC_LIB
# define PREVTC_EXPORT Q_DECL_EXPORT
#else
# define PREVTC_EXPORT Q_DECL_IMPORT
#endif

#endif // PREVTC_GLOBAL_H
