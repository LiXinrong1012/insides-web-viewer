#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include "edcore/edcore_global.h"
#include <QObject>
#include <QMap>
#include <QList>


namespace Parse
{
	/*!
		@brief 错误条目类
		@author Jerry He
		@date   2015.6.5
	*/
	class EDCORE_EXPORT ErrorItem
	{
	public:
		///错误所在文件名
		QString	fileName;

		///错误所在行号
		int		lineIndex;

		///错误所在列号
		int		columnIndex;

		///错误ID
		int		errorID;

		///错误信息
		QString errorInfo;

		///可能的解决办法
		QString possibleSolution;

		///将本条错误转换为字符串
		QString toString()const;
	};



	/*!
	*	用来管理所有的错误条目列表。
	*	@author	Jerry He
	*	@date	2014.9.4
	*/
	class EDCORE_EXPORT ErrorItemManager: public QObject
	{
		Q_OBJECT

	public:
		ErrorItemManager(QObject* parent);
		~ErrorItemManager();

		/// 如果添加成功
		void add(const ErrorItem& errorItem);

		/// 清除所有错误条目
		void clear();
		void clear(const QString& fileName);

		/// 返回当前错误条目数目
		int count()const{return _errorList.size();}

		///返回指定的错误条目通过给定的index
		const ErrorItem* item(int index){return _errorList[index];}

	signals:
		void changed();

		void pAdd(const ErrorItem& errorItem);
		void pClear();
		void pClear(const QString& fileName);

	private slots:
		void onPAdd(const ErrorItem& errorItem);
		void onPClear();
		void onPClear(const QString& fileName);

	private:
		QMap<QString,ErrorItem*> _errorMap;
		QList<ErrorItem*>		_errorList;
	};

}

#endif // ERRORMANAGER_H
