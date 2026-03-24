#include "importtdyresult.h"
#include "TDYResults.h"


Q_EXPORT_PLUGIN2(iexchangeresult, ImportTDYResult);

ImportTDYResult::ImportTDYResult()
{
}

ImportTDYResult::~ImportTDYResult()
{
}

QString ImportTDYResult::getKeyname()
{
	return "TDYResult";
}

IResults* ImportTDYResult::createResults()
{
	TDYResults* results=new TDYResults();
	return results;
}

void ImportTDYResult::clear()
{
}

void ImportTDYResult::setFileName( const QString& fileName )
{
}

void ImportTDYResult::setExtraParameters( const QList<QString>& extraPara )
{
}
