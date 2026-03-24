#ifndef SOLVERMANAGERDIALOG_H
#define SOLVERMANAGERDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QTimer>
#include <QTableWidgetItem>
#include <Windows.h>

#include "inssolver/inssolvermanager.h"

namespace Ui {class SolverManagerDialog;};

class INSSolver;

namespace INSEditor{
	class Project;
	class SolveProcess;
}

using INSEditor::SolveProcess;

/*!
	@brief   求解器管理对话框，负责显示求解器当前求解的各工程状态，以及对求解器进行管理
	@date    2015.6.18
	@author  Jianjun
*/
class SolverManagerDialog : public QDialog, public INSSolverManager
{
	Q_OBJECT

public:
	SolverManagerDialog(QWidget *parent = 0);
	~SolverManagerDialog();

	///供树使用

	///添加一个工程列表用于求解
	void addProjects(const QList<INSEditor::Project*>& projects);

	///添加 一个工程用于求解
	void addProject(INSEditor::Project* project);

	///求解这些工程
	void solverProject(QList<INSEditor::Project*> projectList);

	///检查某工程结果
	void checkResultFromTree(INSEditor::Project* pro);

	///INSSolverManager所留接口
	virtual void started(){}
	virtual void paused(){}
	virtual void restarted(){}
	virtual void finished(){}
	virtual void log(int a,const std::string& message){};
	virtual void information(const SolverUpdateInfo* info){};

public slots:
	///更改了求解的工程数
	void onUpdateSolveMaxNum();

private slots:
	///开始按钮单击对应槽（已弃用）
	void onStart();

	///真正直接关联按钮的槽函数
	void onPauseOrRestart();
	
	///停止求解按钮单击对应槽
	void onStop();

	///工程表对应菜单处理函数
	void showTableWidgetMenu(QPoint p);

	///已完成表格对应菜单处理函数
	void showFinishTableWidgetMenu(QPoint p);

	///项目向上移
	void onMoveUp();
	void moveUp(INSEditor::Project* project);

	///项目向下移
	void onMoveDown();
	void moveDown(INSEditor::Project* project);

	///当求解进程改变时调用
	void onSolveProcessChanged(SolveProcess* process);

	///工程列表选中改变时触发
	void onTableWidgetItemClicked(QTableWidgetItem* item);

	///已完成列表选中改变时触发
	void onFinishTableWidgetItemClicked(QTableWidgetItem* item);

	///当信息表格改变时调用
	void onInfoTabWidgetChanged(int curr);

	///更新日志内容
	void updateLog(const QString& log );

	///删除选中的或全部完成表的内容，只服务于完成表
	void removeSelected();
	void removeAll();

	///取消等待求解
	void onCancelSolve();

	///后处理打开当前求解工程
	void openWithViewer();

	///查看结果，如果模型还没有打开先打开模型
	void checkResult(INSEditor::Project* pro,bool fromTree = false);

	///本类用的查看结果槽
	void onCheckResult();

	///检测求解器是否在运行，如果为暂停或停止，接下来用后处理打开模型和结果
	void startCheckState();

protected:
	///事件过滤器重写
	virtual bool eventFilter( QObject *watched, QEvent *event );

signals:
	///更新解决方案树上求解状态
	void updateSolveProjectOnTree(INSEditor::Project* pro);

private:
	///初始化处理器
	void init();

	///得到project对应的行
	int getProjectRow(INSEditor::Project* pro);

	///获得工程表所有选中行，倒序存放
	QList<int> getSelectRows();

	///得到所有选中工程，如没有选中工程，则返回全部
	QList<INSEditor::Project*> getSelectProjects();

	///更新条目的求解状态
	void updateState(INSEditor::Project* pro,const QString& message);
	
	///开始求解第几行的工程
	void startByProject(INSEditor::Project* project);

	///更新中间的表格currTableWidget
	void updateCurrTableWidget(const double& calTime,const double& stepTime,const double& startTime,const double& endTime,const double& error);

	///通知后处理导入结果 
	void notifyViewerImportResult(INSEditor::Project* pro);

	///检测求解器状态并通过后处理
	void updateViewer(INSEditor::Project* pro);

	///初始化actions
	void createAction();

	///设置按钮的状态
	void initBtn(bool startBtnEnable,bool pauseBtnEnable,bool stopBtnEnable,const QString& pauseBtnText="Pause");
	
	///更新信息表格内容 
	void updateInfoTabWidget(SolveProcess* process);

	///当信息表格内容发生改变时调用
	void onInfoTabWidgetChanged(int curr,SolveProcess* process);

	///更新editer显示信息
	void updateEditText( QTextEdit* editer,const QString& fileName );

	///当暂停按钮点击时调用
	void onPause();

	///当重启按钮点击时调用
	void onRestart();

	///秒转为字符串，多少天，多少小时等。
	QString seconds2String( int allSeconds );

	///
	QString seconds2FriendlyString(int allSeconds);
	
	///激活已打开的后处理程序用到的回调函数 
	static BOOL CALLBACK EnumWindowsProc_viewer(HWND hwnd,LPARAM lparam);

private:
	Ui::SolverManagerDialog *ui;

	///求解工程列表
	QList<INSEditor::Project*> _solverProjectList;

	///正在求解的工程个数
	int _runningCount;

	///最大同时求解工程个数
	int _maxSolverCount;

	///后处理打开
	QAction*	_openWithViewer;

	///导入模型与结果
	QAction*	_checkResultWithViewer;

	///检测当前进度的定时器
	QTimer*		_checkStateTimer;

	///通知后处理导入结果的响应时间
	int		_time;
	
	///记录进度
	int		_checkType;

	///当前工程
	INSEditor::Project*		_currentProject;
};

#endif // SOLVERMANAGERDIALOG_H
