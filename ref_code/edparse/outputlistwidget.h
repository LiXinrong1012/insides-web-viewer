#ifndef OUTPUTLISTWIDGET_H
#define OUTPUTLISTWIDGET_H

#include <QListWidget>
#include <QTimer>
#include <QDockWidget>

namespace Ui {class OutputListWidget;};

namespace INSEditor{
	namespace Parse{
		class CompileInfoItem;
	}
}

/*!
	@brief   负责输出编译等差生的信息的界面
	@date    2015.6.17
	@author  Jianjun
*/
class OutputListWidget : public QListWidget
{
	Q_OBJECT

public:
	OutputListWidget(QWidget *parent = 0);
	~OutputListWidget();

	///设置所在dockWidget
	void setDockWidget(QDockWidget* dockWidget){_dockWidget = dockWidget;}

private slots:
	///通过编译信息item来更新界面显示内容
	void updateOutputInfo(const INSEditor::Parse::CompileInfoItem& item);

	///开始编译，进行输出界面的显示前准备
	void onBeginBuild();

	///编译结束，进行输出界面的收尾工作
	void onEndBuild();

	///用于记录编译耗时
	void onTimeout();

	///将选中信息复制到剪切板
	void copyToClipboard();

	///界面菜单响应
	void contextMenuRequest(QPoint p);

	///清除全部内容
	void clearAll();

	///测示用信息输出槽
	void onTestOutput(QString s);
protected:
	///鼠标双击事件重写
	virtual void	mouseDoubleClickEvent ( QMouseEvent * event );
private:
	Ui::OutputListWidget *ui;
	
	///记录编译用时的定时器
	QTimer* _timer;

	///记录编译所用时间
	int		_time;

	///编译文件数
	int		_buildCount;
	
	///正在编译的文件
	QString _fileName ;

	///所属dockWidget
	QDockWidget* _dockWidget;
};

#endif // OUTPUTLISTWIDGET_H
