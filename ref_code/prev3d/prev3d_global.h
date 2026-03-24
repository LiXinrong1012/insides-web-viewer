#ifndef JERRY_PREV3D_GLOBAL_H
#define JERRY_PREV3D_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PREV3D_LIB
# define PREV3D_EXPORT Q_DECL_EXPORT
#else
# define PREV3D_EXPORT Q_DECL_IMPORT
#endif


class HPoint;
#ifndef HC_POINT
#define HC_POINT HPoint
#endif

#include "HTools.h"
#include "HGlobals.h" 

#include "hc.h"



#endif // JERRY_PREV3D_GLOBAL_H
