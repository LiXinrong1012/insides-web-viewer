#ifndef PREVOSG_GLOBAL_H
#define PREVOSG_GLOBAL_H

#include <qglobal.h>

#ifdef PREVOSG_LIB
# define PREVOSG_EXPORT Q_DECL_EXPORT
#else
# define PREVOSG_EXPORT Q_DECL_IMPORT
#endif

#endif // PREVOSG_GLOBAL_H
