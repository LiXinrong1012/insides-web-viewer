#pragma once
#include "pp_xml/pp_xml_global.h"
#include "xerces_headers.h"
#include <QString>

const XMLCh * QtoX(const QString& s);
QString XtoQ(const XMLCh* x);

PP_XML_EXPORT void DX_String2Vec(const QString& str, double vec[3]);
PP_XML_EXPORT void DX_Vec2String(const double vec[3],QString &str);

class XMLDataExchange
{
public:
	XMLDataExchange(void);
	~XMLDataExchange(void);
};

