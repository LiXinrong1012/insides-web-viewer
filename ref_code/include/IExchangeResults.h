#pragma once

#include <QString>
#include <QList>
#include <QtCore>

namespace INSIDES
{
class IResults;
}

class IExchangeResults
{
public:

	virtual ~IExchangeResults(void) { }

    virtual INSIDES::IResults* createResults()=0;
	virtual QString getKeyname()=0;
	virtual void clear()=0;
	virtual void setFileName(const QString& fileName)=0;
	virtual void setExtraParameters(const QList<QString>& extraPara)=0;
};

Q_DECLARE_INTERFACE(IExchangeResults,
	"com.jerryhe.tdypre.IExchangeResults/1.0");
