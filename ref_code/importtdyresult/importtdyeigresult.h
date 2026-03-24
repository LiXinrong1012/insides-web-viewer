#ifndef IMPORTTDYRESULT_H
#define IMPORTTDYRESULT_H

#include "importtdyresult/importtdyresult_global.h"
#include "include/IExchangeResults.h"

using namespace INSIDES;

/*!
	@brief  负责导入TDY模态结果
	@date   2015.7.7
	@author Jerry
*/
class IMPORTTDYRESULT_EXPORT ImportTDYEigResult :public QObject, public IExchangeResults
{
	Q_OBJECT
		Q_INTERFACES(IExchangeResults)

public:
	ImportTDYEigResult();
	~ImportTDYEigResult();

	///创建结果
	virtual IResults* createResults();

	///获得关键字名
	virtual QString getKeyname();

	///清除所有,未实现
	virtual void clear();

	///设置文件名，未实现
	virtual void setFileName(const QString& fileName);

	///设置特别参数，未实现
	virtual void setExtraParameters(const QList<QString>& extraPara);
private:

};

#endif // IMPORTTDYRESULT_H
