#include "XMLDataExchange.h"
#include "pp_xml/xerces_headers.h"
#include <QStringList>

using namespace xercesc;

const XMLCh * QtoX(const QString& s) 
{ 
	return (s.utf16()); 
}
QString XtoQ(const XMLCh* x) 
{ 
	return QString::fromUtf16((const ushort*)x);
}

void DX_String2Vec( const QString& str, double vec[3] )
{
	QStringList tmp=str.split(',');
	vec[0]=tmp[0].toDouble();
	vec[1]=tmp[1].toDouble();
	vec[2]=tmp[2].toDouble();
}

void DX_Vec2String(const double vec[3],QString &str )
{
	QString re=QString("%1,%2,%3").arg(vec[0]).arg(vec[1]).arg(vec[2]);;
	str=re;
}
XMLDataExchange::XMLDataExchange(void)
{
}


XMLDataExchange::~XMLDataExchange(void)
{
}
