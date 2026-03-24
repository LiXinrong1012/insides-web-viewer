#ifndef PREVTT_GLOBAL_H
#define PREVTT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PREVTT_LIB
# define PREVTT_EXPORT Q_DECL_EXPORT
#else
# define PREVTT_EXPORT Q_DECL_IMPORT
#endif

#endif // PREVTT_GLOBAL_H
