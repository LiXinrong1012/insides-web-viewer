#ifndef EDUI_GLOBAL_H
#define EDUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EDUI_LIB
# define EDUI_EXPORT Q_DECL_EXPORT
#else
# define EDUI_EXPORT Q_DECL_IMPORT
#endif

#endif // EDUI_GLOBAL_H
