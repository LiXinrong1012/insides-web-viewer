#ifndef IMPORTDEMO_H
#define IMPORTDEMO_H

#include "importdemo_global.h"
#include "IFileExchange.h"
#include <QObject>

class IMPORTDEMO_EXPORT ImportDemo: public QObject, public IExchangeFile2
{
	Q_OBJECT
	Q_INTERFACES(IExchangeFile2)

public:

	virtual QString getKeyname();
	virtual void clear();
	virtual void setFileName(const QString& fileName);
	virtual void setExtraParameters(const QList<QString>& extraPara);
	virtual bool doJob();

private:
	QString _fileName;
};

#endif // IMPORTDEMO_H
