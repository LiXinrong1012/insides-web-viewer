#ifndef IMPORTTDYEXCHANGE_H
#define IMPORTTDYEXCHANGE_H

#include <QObject>
#include "../include/IExchangeFile.h"

#include <QtCore/qglobal.h>
#include "../edcompile/tdytypeinfomanager.h"

#ifdef IMPORTTDY_LIB
# define IMPORTTDY_EXPORT Q_DECL_EXPORT
#else
# define IMPORTTDY_EXPORT Q_DECL_IMPORT
#endif

#include <QString>

namespace INSEditor {
namespace Parse{
	class TDYTypeInfoManager;
}
}
class ImportTDYPara;
class ImportTDYImp;

/*!
	@brief  TDY文件导入数据转换
	@date   2015.7.3
	@author Jerry
*/
class IMPORTTDY_EXPORT ImportTDYExchange : public QObject , public IExchangeFile2
{
	Q_OBJECT
	Q_INTERFACES(IExchangeFile2)

public:
	///获得关键名
	virtual QString getKeyname();

	///全部清除
	virtual void clear();

	///设置文件名字
	virtual void setFileName(const QString& fileName);

	///设置特别参数？ 未实现
	virtual void setExtraParameters(const QList<QString>& extraPara);

	///开始工作
	virtual bool doJob();

private:
	///用来保存文件名字
	QString _fileName;

	///tdy条目信息管理程序
	INSEditor::Parse::TDYTypeInfoManager _typeInfoManager;
};

#endif // IMPORTTDYEXCHANGE_H
