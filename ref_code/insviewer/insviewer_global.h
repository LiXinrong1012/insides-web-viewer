#ifndef INSVIEWER_GLOBAL_H
#define INSVIEWER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef INSVIEWER_LIB
# define INSVIEWER_EXPORT Q_DECL_EXPORT
#else
# define INSVIEWER_EXPORT Q_DECL_IMPORT
#endif

extern "C" INSVIEWER_EXPORT void* createINSViewer();

#endif // INSVIEWER_GLOBAL_H
