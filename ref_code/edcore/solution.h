#ifndef SOLUTION_H
#define SOLUTION_H

#include "edcore/edcore_global.h"
#include <QObject>
#include <QSharedPointer>
#include <QXmlStreamReader>
#include <QStringList>

namespace INSEditor
{
	class  Project;
	class  Entity;
	/*!
		@brief 代表整个Solution解决方案。
		@author	Jerry He
		@date	2014.10.28
		*/
	class EDCORE_EXPORT Solution : public QObject
	{
		Q_OBJECT

	public:
		/// 打开一个已经存在的Solution
		static Solution* openExist(QObject* parent,const QString& solutionFilePath);

		/// 在已知目录创建一个新的Solution
		static Solution* createNew(QObject* parent,const QString& dir, const QString& solutionName,bool createDefaultProject=true);

		/// 保存Solution到文件
		bool save();

		///重新尝试检测此文件是否有效
		void reload();

		/// 获得解决方案下的所有工程
		const QList<Project*>& getAllProjects(){return _projectsList;}

		/// 获得解决方案的名字
		QString getSolutionName(){return _name;}

		///设置解决方案的名字
		void setSolutionName(QString str){_name = str;}

		///获得解决方案所在路径
		QString getSolutionDirectory(){return _solutionDirectory;}

		///获得解决方案全名
		QString getSolutionFullName();

		/// 向解决方案添加工程
		bool addProject(Project* project);

		/// 从解决方案移除工程project
		bool removeProject(Project* project);

		/// 通过工程全名获得工程
		Project* getProject(const QString& projectFullFileName);

		/// 获得所有标记
		QStringList getTagList()const{return _tagList;}

		/// 设置标记列表 
		void setTagList(const QStringList& tagList){_tagList=tagList;}

		/// 添加一个标记
		void addTag(const QString& str){_tagList.push_back(str);}

		/// 获得当前标记
		QString getCurrentTag()const{return _currentTag;}

		/// 设置当前标记为tag
		void setCurrentTag(const QString& tag){_currentTag=tag;}

		/// 创建新的工程
		Project* createNewProject();

		/// 添加现有工程
		Project* addExistingProject();

		/// 解决方案是否已被修改
		bool isModified()const{return _isModified;}

		/// 设置解决方案是否为已修改
		void setModified(bool b);

		/// 设置解决方案的主工程为project
		void setMainProject(Project* project);

		/// 获得解决方案的主工程
		Project* getMainProject()const{return _mainProject;}

		~Solution();

signals:
		/// 工程project关闭时发出
		void projectClosed(Project* project);

		/// 工程project创建时发出
		void projectCreated(Project*project);

		/// 更改主程序为mainProject
		void mainProjectChanged(Project* mainProject);

		///是否修怍状态改变时发出
		void modificationStatusChanged(bool b);

	private:
		Solution(QObject *parent,const QString& solutionName=QString());
		Q_DISABLE_COPY(Solution);

		/// 工作目录，包含最后的/
		QString		_solutionDirectory;	

		/// 解决方案名字
		QString		_name;

		/// 工程列表
		QList<Project*> _projectsList;

		/// 当前激活工程
		Project*		_currentProject;

		/// 主工程
		Project*		_mainProject;

		/// 所有标签列表
		QStringList		_tagList;

		/// 当前标签
		QString			_currentTag;
		/// 是否修改
		bool			_isModified;
	};
}



#endif // SOLUTION_H
