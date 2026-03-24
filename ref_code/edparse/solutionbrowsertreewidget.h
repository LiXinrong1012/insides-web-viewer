#ifndef SOLUTIONBROWSERTREEWIDGET_H
#define SOLUTIONBROWSERTREEWIDGET_H

#include <QTreeWidget>
#include <QComboBox>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QIcon>
#include <Windows.h>

class QAction;
class QMenu;
class PropertyDialog;
class EntityPropertyWidget;
class ProjectPropertyWidget;
class QHBoxLayout;
class QLabel;
class SolverManagerDialog;
class ViewerProcess;

namespace INSEditor{
	class Project;
	class Solution;
	class Entity;
}

using INSEditor::Solution;
using INSEditor::Project;
using INSEditor::Entity;

enum MyUserDataRole{DataRole_Type=Qt::UserRole,DataRole_PTR};

enum MyUserDataType{Type_SolutionFolder=1,Type_FileFolder,Type_Solution,Type_Project,Type_File};


/*!
	@brief   继承QTreeWidgetItem，目的更改其排序方式
	@date    2015.6.17
	@author  Jerry
*/
class TreeWidgetItem : public QTreeWidgetItem
{
public:
	TreeWidgetItem( QTreeWidgetItem * parent, int type = Type);
	TreeWidgetItem( QTreeWidget * parent, int type = Type);
	bool operator< (const QTreeWidgetItem &other) const;
};


/*!
	@brief 解决方案树
	@author	Jerry He
	@date	2014.11.1
	*/
class SolutionBrowserTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	SolutionBrowserTreeWidget(QWidget *parent);
	~SolutionBrowserTreeWidget();

	/// 设置默认头
	void initHeader();

signals:
	/// 当前选择的条目改变时发出
	void currentItemChanged(void* item,int itemType);

	/// 标签改变时发出
	void tagsChanged();

protected:
	///拖放动作结束，进行更改底层数据结构操作
	virtual void dropEvent(QDropEvent* e);

	///拖动中函数重写，其中判断某节点是否可放等。
	virtual void dragMoveEvent ( QDragMoveEvent * e);
	
	///拖动前将地址放入mime中
	virtual QMimeData * mimeData ( const QList<QTreeWidgetItem *> items ) const;

	///鼠标双击事件重写
	virtual void mouseDoubleClickEvent ( QMouseEvent * event );

	///事件过滤器重写
	virtual bool eventFilter(QObject *watched, QEvent *event);

protected slots:
	///求解槽函数
	void onSolve();

	///当前tag index改变时调用
	void onTagsCurrentIndexChanged(int tagIndex);

	///通过更改参数批量生成工程
	void onCreateProject(const QString& proName, const QString& text);

	///重置求解器窗口状态
	void onClearSolveDialog();

	///当解决方案打开时调用
	void onSolutionOpened(Solution* solution);

	///清除树中所有项
	void clearView();

	///当工程增加时调用
	void onProjectAdded(Project* project);

	///当工程被移除时调用
	void onProjectRemoved(Project* project);

	///右键菜单对应槽函数
	void onContextMenu(const QPoint&);

	///增加解决方案文件夹
	void onAddSolutionFolder();

	///添加所有文件到SVN
	void onAddAllFilesToSVN();

	///新建工程
	void onNewProject();

	///添加现有工程
	void onAddProject();

	///新建文件
	void onNewFile();

	///添加现有文件 
	void onAddFiles();

    ///添加新的文件夹
	void onAddFileFolder();
	
	///编译当前工程
	void onCompile();

	///复制工程副本
	void onCopyProject();

	///复制文件副本
	void onCopyFile();

	///通过本地默认程序来打开 
	void onOpenWith();

	///通过前处理程序来打开 
	void onOpen();

	///在资源处理器中打开其位置
	void onOpenInExplorer();

	///删除
	void onRemove();

	///重命名
	void onRename();

	///比较文件
	void onCompareFiles();

	///设置模型启动文件
	void onSetAsStartupEntity();

	///用后处理打开模型
	void onOpenWithViewer();

	///用后处理打开模型与结果
	void onOpenResultWithViewer();

	///刷新选中节点以及子节点状态
	void onReload();

	//改名

	///当工程文件夹编辑完成
	void onProjectFolderEditFinished();

	///当文件文件夹编辑完成
	void onFileFolderEditFinished();

	///当工程改名编辑完成
	void onProjectEditFinished();

	///当文件改名编辑完成
	void onFileEditFinished();

	///当文字内容改变时调用
	void onTextChanged ( const QString &  text);

	///当监控路径文件改变时调用
	void onDirChanged ( const QString &path );

	///当前树节点改变时调用 
	void onCurrentItemChanged ( QTreeWidgetItem * current, QTreeWidgetItem * previous );

	///表头右键菜单，是否启用结果状态
	void onCustomContextMenuRequested(const QPoint& point);

	///显示或隐藏结果状态
	void showOrHideState();

	///为选中工程设置标签
	void onSetTags();

	///编辑当前标签
	void onEditTags();

	///当展开item时更新project展开状态
	void onItemCollapseStatusChanged(QTreeWidgetItem * item );

	///保存解决方案树状态
	void saveViewState();

	///读取解决方案树状态
	void readViewState();

	///显示穷举parameter窗口
	void showParameterAnalysisDialog();

	///显示批量求解的窗口
	void showSolvingJobsDialog();

	///当节点被点击时
	void onItemClicked(QTreeWidgetItem* item,int index);

	///配合定时器更新界面求解状态
	void updateSolveState();
	
	void updateSolveProject(INSEditor::Project* project);

	///只是显示上传完成
	void showMessageBox();
private:
	/// 更新Project
	void updateProject(INSEditor::Project* project);

	///更新树
	void updateView();

	///判断文件名是否合法
	bool isLegal(const QString& fileName);

	///初始化相关actions
	void createActions();

	///删除硬盘上指定路径下的所有文件及文件夹（已弃用）
	bool deleteDirFromDisk(const QString &dirName);

	///获得当前光标处节点指针
	QTreeWidgetItem* getCursorItem();

	///获得选中工程
	Project* getSelectedProject();
	Project* getSelectedProject(QTreeWidgetItem* item);

	///获得节点item的父工程节点
	QTreeWidgetItem* getParentProjectTreeItem(QTreeWidgetItem* item);
	QStringList getSelectedFolder(int folderType);

	///通过工程得到对应节点
	QTreeWidgetItem* getProjectItem(Project* project);

	///item是个文件夹,把file拖到item下时通过item获得file新的文件夹列表
	QStringList getSelectedFolder(QTreeWidgetItem* item,int type);

	///获得选中的文件项
	Entity* getSelectedEntity();

	///获得所有空的文件夹
	QStringList getAllEmptyFolders(Project* p);

	///获得文件系统图标或默认图标
	QIcon getSystemIcon(QString fileFullName);

	///获取或创建前置节点
	QTreeWidgetItem* getOrCreateFolderTreeWidgetItem(QTreeWidgetItem* rootItem,const QStringList& folderList,bool createUnexisted=true);

	//右键菜单

	///当右键点击在解决方案节点上弹出的菜单
	void showContextMenuOnSolution();

	///当右键点击在工程节点上弹出的菜单
	void showContextMenuOnProject();

	///当右键点击在工程文件夹上弹出的菜单
	void showContextMenuOnProjectFolder();

	///当右键点击在文件文件夹上弹出的菜单
	void showContextMenuOnFileFolder();

	///当右键点击在文件上弹出的菜单
	void showContextMenuOnFile();

	//删除菜单

	///在工程文件夹上点击删除
	void onRemoveProjectFolder();

	///在工程上点击删除
	void onRemoveProject();

	///在文件文件夹上点击删除
	void onRemoveFileFolder();

	///在文件上点击删除
	void onRemoveFile();

	///初始化解决方案树中节点item
	void initTreeItem(QTreeWidgetItem* item,const QString& text,const QIcon& icon, int dataType,void* p,bool expanded);

	///创建节点
	QTreeWidgetItem* createTreeItem(QTreeWidgetItem* parent,const QString& text,const QIcon& icon, int dataType,void* p,bool expanded);
	QTreeWidgetItem* createTreeItem(QTreeWidget* parent,const QString& text,const QIcon& icon, int dataType,void* p,bool expanded);

	///获得item节点下所有type型节点
	void getTypeAllItem(QTreeWidgetItem* item,int type);

	///判断节点item是否为某种类型
	bool isCertainType( QTreeWidgetItem* item,int certainType );

	///将oldEntity的所有属性copy到pro工程中的newEntity中
	void copyEntity(Entity* newEntity,Entity* oldEntity,Project* pro,QTreeWidgetItem* cursorItem,bool isCopyFile);

	///更新树上的求解状态
	void updateSolveStateOnTree(QList<Project*> projects);

	///激活已打开后处理用到的回调函数
	static BOOL CALLBACK EnumWindowsProc_viewer(HWND hwnd,LPARAM lparam);

private:
	///添加文件到SVN
	QAction*	_addAllFilesToSVNAction;

	///在资源管理器中打开
	QAction*	_openInExplorerAction;

	///用后处理打开 
	QAction*	_openWithViewer;

	///用后处理打开并导入结果
	QAction*	_openResultWithViewer;

	///编译
	QAction*    _buildAction;

	///求解
	QAction*	_solveAction;

	///比较
	QAction*	_compareAction;

	///添加菜单
	QMenu*		_addMenu;

	///添加新的工程
	QAction*    _newProjectAction;

	///复制工程副本
	QAction*    _copyProjectAction;

	///复制文件
	QAction*	_copyFileAction;

	///添加已有工程
	QAction*	_addExistingProjectAction;

	///新的工程文件夹
	QAction*    _newProjectFolderAction;

	///新的文件
	QAction*	_newItemAction;

	///添加已有文件
	QAction*	_addExistingItemsAction;

	///新的文件文件夹
	QAction*	_newFileFolderAction;

	///设置启动项
	QAction*	_setAsStartupFileAction;

	///设置主工程
	QAction*	_setAsMainProjectAction;

	///用本地默认程序打开
	QAction*	_openWithAction;

	///重新加载
	QAction*	_reloadAction;

	///剪切，未使用
	QAction*	_cutAction;

	///复制，未使用
	QAction*	_copyAction;

	///粘贴，未使用
	QAction*	_pasteAction;

	///删除
	QAction*	_removeAction;

	///重命名 
	QAction*	_renameAction;

	///编辑标签
	QAction*	_editTagAction;

	///穷举参数action
	QAction*	_exhaustionParameterAction;

	///显示求解状况
	QAction*	_batchSolveAction;

	// 树相关图标
	QIcon		_iconSolution;
	QIcon		_iconProject;
	QIcon		_iconEntity;
	QIcon		_iconProjectFolder;
	QIcon		_iconFileFolder;

	///标签列表
	QList<QAction*>			_tagActions;

	///解决方案根节点 
	QTreeWidgetItem*		_solutionRootItem;

	///本地文件监视者
	QFileSystemWatcher*		_watcher;

	///配合getTypeAllItem获得某类型的所有ITEM
	QList<QTreeWidgetItem*> _typeAllItem;

	///改名输入框
	QLineEdit*				_renameLineEdit;

	///改名是否编辑完成
	bool					_renameEditIsEdited;

	///改名专用,存当前item
	QTreeWidgetItem*		_currItem;
	
	///改名专用，存当前entity
	Entity*					_currEntity;

	///改名专用，存当前project
	Project*				_currProject;

	///用来更新求解状态的计时器
	QTimer*					_updateSolveStateTimer;

	///正在求觖的所有工程
	QList<Project*>			_solvingProjects;
	
	///求解管理对话框
	SolverManagerDialog*	_solverManagerDialog;
};

#endif // SOLUTIONBROWSERTREEWIDGET_H
