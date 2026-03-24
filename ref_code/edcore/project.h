#ifndef PROJECT_H
#define PROJECT_H


#include "edcore/edcore_global.h"
#include <QObject>
#include <QStringList>
#include <QProcess>
#include <Windows.h>
#include "entity.h"
#include "includeheaders.h"
#include "result.h"


class QDomDocument;
class QDomElement;
class ViewerProcess;

namespace INSEditor
{
	class SolveProcess;

	/*!
		@brief  代表一个工程对象
		@date   2015.6.8
		@author Jerry
	*/
	class EDCORE_EXPORT Project : public QObject
	{
		Q_OBJECT
	public:
		/// 打开一个已有的项目
		static Project* open(QObject* parent,const QString& projectName);

		/// 创建一个项目
		static Project* createNew(QObject* parent,const QString& dir,const QString& projectName);

		~Project();

		/// 保存工程内容
		void save();

		/// 工程是否为空
		bool isEmpty()const;

		/// 工程是否有效
		bool isValid()const;

		/// 是否有计算结果
		bool hasResult();

		///是否为外部文件
		bool isExternalFile(const QString& fullFileName)const;

		///后处理打开
		bool openWithViewer();
		bool openWithViewer2();

		/// 进行求解
		bool openWithSolver();
		bool openWithSolver2();

		///获取求解器求解指针 
		SolveProcess* getSolveProcess(){return _solveProcess;}

		///清空求解器求解指针，删除后调用
		void clearSolveProcess(){_solveProcess = NULL;}

		///获取后处理工程类指针
		ViewerProcess* getViewProcess(){return _viewProcess;}

		///清空后处理工程类指针
		void clearViewProcess(){_viewProcess = NULL;}

		///重新尝试检测此文件是否有效
		void reload();

		/// getters and setters

		///文件夹
		const QStringList& getFolders()const{return _folders;}
		void setFolders(const QStringList& f){_folders=f;}

		///空文件夹
		const QStringList& getEmptyFolders()const{return _emptyFolders;}
		void setEmptyFolders(const QStringList& f){_emptyFolders=f;}

		///获得工程下的所有子项
		const QList<Entity*>& getEntities()const{return _entityList;}

		///获得工程下的启动项
		Entity* getStartupEntity(){return _mainEntity;}
		const Entity* getStartupEntity()const {return _mainEntity;}

		///设置该工程的启动项
		void setStartupEntity(Entity* entity){_mainEntity=entity;}

		///工程所在路径
		QString getDirectory()const{return _directory;}
		void setDirectory(const QString& str){_directory=str;}

		///工程名
		QString getProjectName()const{return _projectName;}
		void setProjectName(const QString& str){_projectName=str;}

		///获得工程文件名
		QString getProjectFileName()const{return _directory+_projectName+".inspro";}

		///备注
		QString getLog()const {return _log;}
		void setLog(const QString& log){_log = log;}

		///标签
		QStringList getTags()const{return _tags;}
		void setTags(const QStringList& tags){_tags = tags;}

		/// 尝试获得结果的启动文件，获取成功返回true
		bool getStartupFile(QString& startupFile)const;

		///工程包含路径
		QString getIncludeDirectory()const {return _includeDirectory;}
		void setIncludeDirectory(QString dir){_includeDirectory = dir;}

		///添加工程子项
		void addEntity(Entity* entity);

		///移除工程子项
		void removeEntity(Entity* entity);

		///改名
		void rename(Entity* entity,const QString& newName);

		///获得该工程所属解决方案
		Solution* getSolution();

		///通过uuid获得相应子项
		Entity* getEntity(const QString& uuid)const;

		///通过子项的全名获得子项
		Entity* getEntityByFullFilename(const QString& fileName)const;

		///获得工程对应结果
		const Result* getResult()const{return &_result;}
		Result* getResult(){return &_result;}

		///是否为外部工程
		bool isExpanded()const{return _isExpand;}

		///设置记录其为外部工程
		void setIsExpanded(bool expand){_isExpand = expand;}
		
		///设置工程已被修改
		void setModified();

		/// Notifications

		///通知子项被双击，已废弃
		void notifyEntityDoubleClicked(Entity* entity);

		///通知子项被激活，已废弃
		void notifyEntityActivated(Entity* entity);

		///通知定位到某文件的rowIndex行columnIndex列，已废弃
		void notifyGotoPosition(const QString& fullFileName,int rowIndex,int columnIndex);

signals:
		/// 当新的条目加入后触发
		void entityAdded(Entity* entity);

		///子项移除之前调用
		void entityAboutToRemove(Entity* entity);

		///子项改名之前调用
		void entityAboutToRename(Entity* entity,const QString& newName);

		///结果添加后调用
		void resultAdded(Result* result);

		///结果移除之前调用
		void resultAboutToRemove(Result* result);

		///结果移除后调用
		void resultRemoved();

		/// 当条目被双击时
		void entityDoubleClicked(Entity* entity);

		/// 当条目被显示时激活
		void entityActivated(Entity* entity);

		///定位到文件具体位置，已废弃
		void gotoPosition(const QString& fullFileName,int rowIndex,int columnIndex);

	private slots:
		///viewer或solver的process被启动的程序被关掉时触发
		void onViewerFinished(int exitCode, QProcess::ExitStatus exitStatus);

	private:
		/// 工程被包含的文件夹，为空时位于根目录下
		QStringList _folders;

		///tags
		QStringList _tags;

		///用于保存工程下的空文件夹
		QStringList _emptyFolders;

		/// 工程的工作目录，带最后的/
		QString		_directory;
		
		/// 工程名字, example: footmodel
		QString		_projectName;	

		///　条目列表
		QList<Entity*>  _entityList;

		///启动条目
		Entity*		_mainEntity;	

		///包含目录
		QString _includeDirectory;

		///是否展开
		bool _isExpand;

		///文件夹
		QList<QStringList>	_fileFolders;

		///包含管理类
		IncludeHeaders	_includeHeaders;

		///是否有效
		bool		_isValid;

		///结果
		Result		_result;

		///工程备注
		QString		_log;
		
		/// 关联的后处理程序
		QProcess*	_viewerProcess;

		/// 关联的求解器Process
		SolveProcess*	_solveProcess;

		///关联的后处理Process
		ViewerProcess*	_viewProcess;

	private:
		Project(QObject *parent);
		Project(QObject* parent,const QString& projectName);
		Q_DISABLE_COPY(Project);

		///创建默认的文件夹
		void createDefaultFolder();

		///保存结果
		void saveResult(QDomElement& projectElement);

		///读取结果
		void readResult(QDomElement& projectElement);

		///读取xml文件 
		void readXML();

		///查找viewer是否已启动的回调函数
		static BOOL CALLBACK EnumWindowsProc_viewer(HWND hwnd,LPARAM lparam);

		///查找solver是否已启动的回调函数
		static BOOL CALLBACK EnumWindowsProc_solver(HWND hwnd,LPARAM lparam);

	};
}



#endif // PROJECT_H
