#pragma once

#include <QString>
#include <QList>
#include <QtCore>


class IExchangeFile2
{
public:

	virtual ~IExchangeFile2(void) { }

	virtual QString getKeyname()=0;
	virtual void clear()=0;
	virtual void setFileName(const QString& fileName)=0;
	virtual void setExtraParameters(const QList<QString>& extraPara)=0;
	virtual bool doJob()=0;
};

Q_DECLARE_INTERFACE(IExchangeFile2,
	"com.jerryhe.tdypre.iexchangefile2/1.0");