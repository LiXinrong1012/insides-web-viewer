#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "edui/ribbonwindow.h"

#include "edcore/console.h"

#include <QMdiArea>
#include <QFtp>
#include <QFileInfo>

namespace Ui {class MainWindow;};

class ViewerWrapper;
class MdiArea;
class ModelViewModel;

namespace INSEditor
{
	class Solution;
	class Project;
}

using INSEditor::Solution;
using INSEditor::Project;

/*!
	@brief   程序主窗口，主要框架，顶部菜单等均由此类实现
	@date    2015.6.19
	@author  Jerry
*/
class MainWindow : public RibbonWindow, public Base::ConsoleObserver
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public:
	//重写实现Console相关虚方法

	virtual void Warning(const char *str);
	/// get calles when a Message is issued
	virtual void Message(const char *str);
	/// get calles when a Error is issued
	virtual void Error  (const char *str);
	/// get calles when a Log Message is issued
	virtual void Log    (const char *str);

public slots:
	///编译模型文件
	void buidProject();

	///更新build菜单组中的菜单的可用性
	void updateIcon();

protected:
	///重写的关闭事件，关闭时查看是否需要保存等
	virtual void closeEvent(QCloseEvent* event);

	///解析自定义event
	virtual void customEvent(QEvent* event);

signals:
	///请求最近的文件改变
	void requestRecentFileChange(const QStringList& filelist);

private slots:
	///将标签显示在右侧
	void setTabPositionRight(bool state);

	///将标签显示在底侧 
	void setTabPositionBottom(bool state);

	///将标签显示在顶部
	void setTabPositionTop(bool state);

	///将标签显示在左侧
	void setTabPositionLeft(bool state);

	///打开文件槽，只是执行选择打开文件的代码，如果选择了文件则执行真正的打开
	void open();

	///保存文件关联槽，调用saveCurrFile方法
	bool save();

	///选择保存文件的位置和名称，如果合规定则调用saveFile保存
	bool saveAs();

	///新的解决方案关联槽
	void newSolution();

	///打开已存在的解决方案，通过手动选择
	void openSolution();

	///打开解决方案通过fileName
	void openSolution(const QString& fileName);

	///新工程调用槽
	void newProject();

	///打开已存在的工程
	void openProject();

	///保存所有对应槽
	void saveAll();

	///编译模型文件
	void build();

	///通过后处理打开该模型
	void pushToView();

	///格式化模型文件
	void formatCode();

	///格式化文本并导出
	void formatExport();

	///求解选中工程并显示求解框
	void showSolverDialog();

	///当解决方案创建时调用
	void onSolutionCreated(Solution* solution);

	///当解决方案关闭时调用
	void onSolutionClosed(Solution* solution);

	///当解决方案的修改状态改变时调用
	void onSolutionModificationStatusChanged(bool b);

	///响应打开文件信号的槽
	void respondOpeningFile(const QString& fileName);

	///当子窗口激活时调用
	void onSubWindowActivated ( QMdiSubWindow * win);

	///创建ins.xml文件
	void createINSFile();

	///现在用来检验是否有更新
	void onTimeout();

private:
	///保存当前文件
	bool saveCurrFile();
	
	///创建所需的action
	void createActions();

	///创建File菜单相关子项
	void createMenuFile();

	///创建大的菜单分类框，如Home ,Setting
	void createRibbon();

	///创建快速进入条，未实现
	void createQuickAccessBar();

	///创建状态条
	void createStatusBar();

	///创建查找结果窗
	void createFindResultWindow();

	///加载帮助插件
	void loadHelpPlugin();

	///加载解析插件
	void loadParsePlugin();

	// Ribbon groups

	///创建标签位置group
	void createGroupTabPosition(Qtitan::RibbonGroup* m_groupMdiTabs);

	///创建创建ins的group
	void createGroupCreateINS(Qtitan::RibbonGroup* group);

	///创建main group
	void createGroupMain(Qtitan::RibbonGroup* group);

	///创建build group
	void createGroupBuild( Qtitan::RibbonGroup* group );

	///创建 mics group
	void createGroupMics(Qtitan::RibbonGroup* group);

	///创建 windows group
	void creategroupWindows(Qtitan::RibbonGroup* group);

	///写设置内容到ini文件
	void writeSetting();

	///从ini文件中读取设置内容
	void readSetting();

	///打开上次打开的文件
	void openLastFiles();

	///写设置内容到ini文件
	void writeSettingToIni();

	///从ini文件中读取设置内容
	void readSettingFromIni();

	///加载文件fileName
	void loadFile(const QString &fileName);

	///保存文件 fileName
	bool saveFile(const QString &fileName);

	///显示日志信息
	void logMessage(const QString& mess);

	///区分是否为同一线程
	void logMessageThread(const QString& mess);

	///设置新工程等action的可用状态
	void setActionsEnabled(bool b);

	///如果解决方案已被修改，询问是否保存
	bool questionModification(Solution* solution );

	///更新最近的文件
	void updateRecentFile(const QString& newFileName);

	///获得最近文件列表
	QStringList getRecentFileList();

	///从字符串fullFileName中获得文件名
	static QString strippedName(const QString &fullFileName);

	///检测是否有程序正在进行求解，如果有询问继续求解还是直接退出
	bool questionExitSolver();

	///获得正在求解并且未完成的工程列表
	const QList<Project*>& getSolvingProjects();

	///停止求解
	void stopSolve(const QList<Project*>& proList);

	///检测是否有更新
	long checkHasUpdate(QString con);

private:
	///新的解决方案
	QAction*	_newSolution;

	///打开解决方案
	QAction*	_openSolution;

	///新建工程
	QAction*	_newProject;

	///打开现有工程
	QAction*	_openProject;

	///新建文件
	QAction*	_newFile;

	///添加已有文件
	QAction*	_addExistingFile;

	///打开文件
	QAction*	_openFile;

	///保存文件
	QAction*	_saveFile;

	///保存所有文件
	QAction*	_saveAllDocuments;

	///编译模型文件
	QAction*	_build;

	///后处理打开当前选中的工程
	QAction*	_pushToView;

	///开始求解
	QAction*	_startSimulating;

	///检测求解状态，未启用
	QAction*	_checkSolverStatus;

	///求解选项，未启用
	QAction*	_solverOptions;

	///程序设置
	QAction*	_applicationSetting;

	///开启帮助程序
	QAction*	_startHelpApplication;

	///并排显示所有打开窗口
	QAction*	_tilePage;

	///叠加显示所有打开窗口
	QAction*	_cascadePage;

	///格式化导出
	QAction*	_formatExport;

	///格式化菜单
	QMenu*		_formatMenu;

	///创建ins.xml
	QAction*	_createINSAction;

	///软件名字
	QString		_appName;

private:
	Ui::MainWindow *ui;

	///分屏管理 
	MdiArea*		_mdiArea;

	///与后处理通信类
	ViewerWrapper*	_viewerWrapper;

	///暂时用于检测更新的定时器
	QTimer*			_checkUpdateTimer;

	///用于检测更新的ftp
	QFtp*			_checkFtp;

	///最近的文件信息列表
	QList<QFileInfo> _recentFileInfoList;
};

#endif // MAINWINDOW_H
