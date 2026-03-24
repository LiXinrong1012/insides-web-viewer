#ifndef IMPORTTDYEXCHANGE_H
#define IMPORTTDYEXCHANGE_H

#include <QObject>
#include "include/IExchangeFile.h"

#include <QtCore/qglobal.h>

#ifdef IMPORTTDY_LIB
# define IMPORTTDY_EXPORT Q_DECL_EXPORT
#else
# define IMPORTTDY_EXPORT Q_DECL_IMPORT
#endif

#include <QString>

namespace Parse{class Assembly;}
class ImportTDYPara;
class ImportTDYImp;

class IMPORTTDY_EXPORT ImportTDYExchange : public QObject , public IExchangeFile2
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
	
	void loadTemplate();
	bool importTemplate();

	bool processAssembly(Parse::Assembly* ass,ImportTDYPara* imp);
};

#endif // IMPORTTDYEXCHANGE_H
