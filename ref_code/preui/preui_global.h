#ifndef PREUI_GLOBAL_H
#define PREUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PREUI_LIB
# define PREUI_EXPORT Q_DECL_EXPORT
#else
# define PREUI_EXPORT Q_DECL_IMPORT
#endif


void PREUI_EXPORT init_preui();

#endif // PREUI_GLOBAL_H


