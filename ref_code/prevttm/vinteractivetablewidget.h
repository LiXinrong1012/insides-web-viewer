#ifndef VINTERACTIVETABLEWIDGET_H
#define VINTERACTIVETABLEWIDGET_H

#include <QWidget>
namespace Ui {class VInteractiveTableWidget;};

class InteractiveTableModel;
class ResultSelectorWidget;
class QTextStream;
class SortTransposeProxyModel;

/*!
	@brief   多项交互式表格实现
	@date    2015.7.2
	@author  Jerry
*/
class VInteractiveTableWidget : public QWidget
{
	Q_OBJECT

public:
	VInteractiveTableWidget(QWidget *parent = 0);
	~VInteractiveTableWidget();

	///当结果被删除后调用
	void onResultsDeleted();

	///获得分隔符
	ResultSelectorWidget* getSelector();

	///保存状态
	bool saveMyState(QDataStream& out);

	///加载状态
	bool loadMyState(QDataStream& in);

public slots:
	///导出其文本形式
	void exportAsTxt();

	///以文本形式导出所有
	void exportAllAsTxt();

	///添加项目
	void addItems();

	///显示设置框
	void showSetting();

private:
	///写一帧
	void writeOneFrame(QTextStream& out,int rowCount,int columnCount);

	///写表头
	bool writeHeader(QTextStream& out,int rowCount,int columnCount, QList<QString>& headers,
		int& realColumnCount,int& realRowCount);

private:
	Ui::VInteractiveTableWidget *ui;

	///源model
	InteractiveTableModel* _viewModel;

	///代理model
	SortTransposeProxyModel* _proxyModel;

	///当前列
	int _currentCol;
};

#endif // VINTERACTIVETABLEWIDGET_H
