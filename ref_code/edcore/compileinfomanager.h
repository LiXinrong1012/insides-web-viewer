#ifndef COMPILEINFOMANAGER_H
#define COMPILEINFOMANAGER_H

#include "edcore/edcore_global.h"
#include <QObject>
#include <QSharedPointer>
#include <QMap>
#include <QMutex>

namespace Parse{
	class FileItem;
}

using Parse::FileItem;

/*!
*	用来管理所有产生的编译信息。
*	@author	Jerry He
*	@date	2014.9.4
*/
class EDCORE_EXPORT CompileInfoManager : public QObject
{
	Q_OBJECT

public:
	CompileInfoManager(QObject *parent);
	~CompileInfoManager();

	void setItem(const QString& fileName,Parse::FileItem* item);
	const Parse::FileItem* getItem(const QString& fileName);
	void clear();

signals:
	void itemUpdated(const QString& fileName,Parse::FileItem* item);

	void pSetItem(const QString& fileName,Parse::FileItem* item);
	void pClear();

private slots:
	void onPSetItem(const QString& fileName,Parse::FileItem* item);
	void onPClear();

private:
	QMap<QString,QSharedPointer<Parse::FileItem> > _dataMap;
	
};

#endif // COMPILEINFOMANAGER_H
