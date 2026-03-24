#ifndef RESULT_H
#define RESULT_H

#include "edcore/edcore_global.h"
#include <QString>
#include <QUuid>
#include <QDateTime>
#include <QStringList>

namespace INSEditor{

class Project;

/*!
	@brief 代表一个结果。
	@author	Jerry He
	@date	2014.10.28
	*/
class EDCORE_EXPORT Result
{
public:
	Result(Project* project);
	~Result();

	/// 刷新结果
	void reloadResult();

	/// 获得创建时间
	QDateTime getCreateTime()const{return _createTime;}

	/// 返回创建时间的字符串格式，例　2014/11/05 14:47:30
	QString getCreateTimeStr()const;

	/// 设置创建时间
	void setCreateTime(const QDateTime& t){_createTime=t;}

	/// 使用字符串格式时间设置创建时间，例　2014/11/05 14:47:30
	void setCreateTimeStr(const QString& str);

	/// 获得最后更改的时间
	QDateTime getLastEditTime()const{return _lastEdit;}

	/// 获得最后更改的时间的字符串
	QString getLastEditTimeStr()const;

	/// 设置最后更改时间
	void setLastEditTime(const QDateTime& t){_lastEdit=t;}

	/// 使用字符串格式时间设置最后更改时间
	void setLastEditTimeStr(const QString& str);

	/// 获得结果所属的Tags列表
	const QStringList& getTags()const{return _tags;}

	/// 设置结果的Tags列表
	void setTags(const QStringList& tags){_tags=tags;}

private:
	Project*	_project;

	QDateTime _createTime;

	QDateTime _lastEdit;

	QString	 _log;

	QUuid	_uuid;
	
	QStringList _tags;

	QString  _errorMessage;

};

}


#endif // RESULT_H
