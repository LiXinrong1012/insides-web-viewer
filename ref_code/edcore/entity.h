#ifndef ENTITY_H
#define ENTITY_H


#include "edcore/edcore_global.h"
#include <QString>
#include <QStringList>
#include <QUuid>

namespace INSEditor
{
	class Project;
	/*!
		@brief 代表项目中的一个条目，可以是一个文件夹，或者是一个文件。
		@author	Jerry He
		@date	2014.10.28
	*/
	class EDCORE_EXPORT Entity
	{
	public:
		Entity(const QString& fullFileName);
		~Entity();

		/// 返回显示的文件名字，如 main.ins
		const QString& getName()const{return _name;}

		/// 返回文件全路径，如D:/main.ins
		QString getFullFileName()const;

		/// 设置文件全路径
		void setFullFileName(const QString& fullFileName){_fullFileName = fullFileName;}

		/// 返回条目的内容
		const QString& getContent()const{return _content;} 

		/// 设置条目的内容
		void setContent(const QString& str){_content=str;}

		/// 重命名成新的文件名
		bool rename(const QString& newFileName);

		/// 返回文件的后缀名
		QString getFileExt();

		/// 从文件中读出内容
		QString readFromFile();

		/// 返回所属的Project指标
		Project* getProject(){return _project;}

		/// 返回所属的Project指针
		const Project* getProject()const{return _project;}

		/// 设置所属的Project指针
		void setProject(Project* project){_project = project;}

		/// 返回所属的Folder数组
		const QStringList& getFolders()const{return _folders;}

		/// 设置所属的Folder数组
		void setFolders(const QStringList& folders){_folders=folders;}

		/// 返回此文件是否有效
		bool isValid()const{return _isValid;}

		/// 重新尝试检测此文件是否有效
		void reload();

		/// 返回此文件的Uuid
		const QUuid& getUuid()const{return _uuid;}

		/// 设置此文件的Uuid
		void setUuid(const QUuid& uuid){_uuid=uuid;}

		///返回此文件拷备时是否复制属性
		bool isCreateNewOneWhenCopy()const{return _createNewOneWhenCopy;}

		///设置此文件拷备时是否复制
		void setCreateNewOneWhenCopy(bool createNewOneWhenCopy){_createNewOneWhenCopy = createNewOneWhenCopy;}

		///返回此文件备注
		QString getLog()const{return _log;}

		///设置此文件备注
		void setLog(const QString& log){_log = log;}

		/// deprecated:
		static bool saveXMLFile(const QString& xmlFileName,const QString& content);

	private:
		///关联的Project
		Project*	_project;
		///是否有效
		bool			_isValid;
		///文件夹数组
		QStringList		_folders;
		///文件名
		QString			_name;
		///文件绝对路径名
		QString			_fullFileName;	
		///文件内容，临时
		QString			_content;
		///文件Uuid码
		QUuid			_uuid;
		///文件拷备时是否复制
		bool			_createNewOneWhenCopy;
		///备注
		QString			_log;

		friend class Project;
		friend class Solution;
	};
}

#endif // ENTITY_H
