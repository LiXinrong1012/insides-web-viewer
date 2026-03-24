#ifndef PP_XMLL_GLOBAL_H
#define PP_XMLL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PP_XML_LIB
# define PP_XML_EXPORT Q_DECL_EXPORT
#else
# define PP_XML_EXPORT Q_DECL_IMPORT
#endif

#define BEGIN_PP_NAMESPACE namespace pp{



#define END_PP_NAMESPACE }

#define USING_PP_NAMESPACE using namespace pp;

#endif // PP_XMLL_GLOBAL_H
