#ifndef RESULTBROWSERWIDGET_H
#define RESULTBROWSERWIDGET_H

#include <QWidget>
namespace Ui {class ResultBrowserWidget;};

namespace INSEditor{
	class Solution;
	class Project;
	class Result;
}

using INSEditor::Solution;
using INSEditor::Project;
using INSEditor::Result;

/*!
	@brief   解决方案树类，像已废弃
	@date    2015.6.17
	@author  Jerry
*/
class ResultBrowserWidget : public QWidget
{
	Q_OBJECT

public:
	ResultBrowserWidget(QWidget *parent = 0);
	~ResultBrowserWidget();

public slots:
	///清理结果相关界面内容
	void clearView();

protected slots:
	///当解决方案打开后调用
	void onSolutionOpened(Solution* solution);

	///当工程添加后调用
	void onProjectAdded(Project* project);

	///当工程移除后调用
	void onProjectRemoved(Project* project);

	///右键菜单
	void onContextMenu(const QPoint&);

	///更新视图
	void updateView();

	///当菜单删除项被点击时
	void onRemove();

	///当菜单求解项被点击时
	void onSolve();

	///当菜单编辑log项被点击时
	void onEditLog();

	///当菜单在在后处理中打开项被点击时
	void onOpenWithViewer();

	///在资源管理器中打开
	void onOpenWithExplorer();

	///创建新的tag
	void onCreateNewTag();

	///当前filter中的text发生改变时调用
	void onFilterProjectCurrentIndexChanged ( const QString & text );

	///当filter index改变时调用 。
	void onFilterProjectCurrentIndexChanged ( int index );

	///当tags中的text发生改变时调用
	void onTagsCurrentIndexChanged(const QString& text);

	///当tags中的index发生改变时调用
	void onTagsCurrentIndexChanged(int index);

	///设置tags到当前结果
	void onSetTags();

private:
	///结果增加或移除时更新显示的连接
	void connectProject(Project* project);

	///初始化所有action
	void createActions();

	///获得当前结果
	Result* getCurrentResult();

	///更新结果表格数据，已弃用
	void updatResultTableData(QList<Result*> list);

	///初始化标签
	void initTags();

private:
	Ui::ResultBrowserWidget *ui;
	
	///action

	///删除
	QAction*  _removeAction;

	///在后处理打开
	QAction*  _openWithViewerAction;

	///求解
	QAction*  _solveAction;

	///创建新的工程
	QAction*  _createNewProject;
	QAction*  _backToProject;

	///重命名
	QAction*  _renameAction;

	///编辑日志
	QAction*  _editLogAction;

	///
	QAction*  _openFolder;

	///新标签
	QAction*  _newTagAction;

	///标签
	QList<QAction*> _tagActions;

	///当前显示哪个project的result
	QString	_currentProgectName;

	///project过滤表的当前index;
	int _currentFilterProjectIndex;

	///当前标签名
	QString _currentTagName;

	///当前为第几个标签
	int _currentTagIndex;

};

#endif // RESULTBROWSERWIDGET_H
