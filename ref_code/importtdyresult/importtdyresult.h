#ifndef IMPORTTDYRESULT_H
#define IMPORTTDYRESULT_H

#include "importtdyresult/importtdyresult_global.h"
#include "include/IExchangeResults.h"

using namespace INSIDES;

/*!
	@brief  导入tdy结果
	@date   2015.7.7
	@author Jerry
*/
class IMPORTTDYRESULT_EXPORT ImportTDYResult :public QObject, public IExchangeResults
{
	Q_OBJECT
	Q_INTERFACES(IExchangeResults)

public:
	ImportTDYResult();
	~ImportTDYResult();

	///创建所有结果
	virtual IResults* createResults();

	///获得关键字名
	virtual QString getKeyname();

	///清除所有
	virtual void clear();

	///设置文件名
	virtual void setFileName(const QString& fileName);

	///设置特殊参数
	virtual void setExtraParameters(const QList<QString>& extraPara);
private:

};

#endif // IMPORTTDYRESULT_H
