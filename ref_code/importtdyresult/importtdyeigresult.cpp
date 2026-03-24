#include "importtdyeigresult.h"
#include "TDYEigResults.h"

Q_EXPORT_PLUGIN2(iexchangeresult, ImportTDYEigResult);

ImportTDYEigResult::ImportTDYEigResult()
{
}

ImportTDYEigResult::~ImportTDYEigResult()
{
}

QString ImportTDYEigResult::getKeyname()
{
	return "TDYEigResult";
}

IResults* ImportTDYEigResult::createResults()
{
	TDYEigResults* results=new TDYEigResults();
	return results;
}

void ImportTDYEigResult::clear()
{
}

void ImportTDYEigResult::setFileName( const QString& fileName )
{
}

void ImportTDYEigResult::setExtraParameters( const QList<QString>& extraPara )
{
}
