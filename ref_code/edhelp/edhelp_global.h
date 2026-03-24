#ifndef EDHELP_GLOBAL_H
#define EDHELP_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EDHELP_LIB
# define EDHELP_EXPORT Q_DECL_EXPORT
#else
# define EDHELP_EXPORT Q_DECL_IMPORT
#endif

#endif // EDHELP_GLOBAL_H
