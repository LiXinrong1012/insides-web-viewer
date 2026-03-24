#ifndef POSTCORE_GLOBAL_H
#define POSTCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef POSTCORE_LIB
# define POSTCORE_EXPORT Q_DECL_EXPORT
#else
# define POSTCORE_EXPORT Q_DECL_IMPORT
#endif


bool POSTCORE_EXPORT init_postcore_module();


#endif // POSTCORE_GLOBAL_H



