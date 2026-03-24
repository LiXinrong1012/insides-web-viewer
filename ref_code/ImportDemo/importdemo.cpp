#include "importdemo.h"

Q_EXPORT_PLUGIN2(iexchangefile2, ImportDemo);

QString ImportDemo::getKeyname()
{
	return "TDY_DEMO";
}

void ImportDemo::clear()
{
	return;
}

void ImportDemo::setExtraParameters( const QList<QString>& extraPara )
{
	return;
}

void ImportDemo::setFileName( const QString& fileName )
{
	return;
}

bool ImportDemo::doJob()
{
	return true;
}
