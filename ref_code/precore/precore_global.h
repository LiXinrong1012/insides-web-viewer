#ifndef PRECORE_GLOBAL_H
#define PRECORE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PRECORE_LIB
# define PRECORE_EXPORT Q_DECL_EXPORT
#else
# define PRECORE_EXPORT Q_DECL_IMPORT
#endif


bool PRECORE_EXPORT init_precore_module();


#endif // PRECORE_GLOBAL_H


