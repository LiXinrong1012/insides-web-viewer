#ifndef VINTERACTIVETABLEWIDGET_H
#define VINTERACTIVETABLEWIDGET_H

#include <QWidget>
#include <QCursor>
namespace Ui {class InteractiveTableWidget;};

class SourceDataModel;
class ResultSelectorWidget;
class ExchangeModel;
class SortTransposeProxyModel;

/*!
	@brief   交互式表格实现
	@date    2015.7.1
	@author  Jerry
*/
class InteractiveTableWidget : public QWidget
{
	Q_OBJECT

public:
	InteractiveTableWidget(QWidget *parent = 0);
	~InteractiveTableWidget();

	///当结果删除后调用
	void onResultsDeleted();

	///获得选择条widget
	ResultSelectorWidget* getSelector();

	///保存状态
	bool saveMyState(QDataStream& out);

	///加载状态
	bool loadMyState(QDataStream& in, qint64 dataSize);

	///获得转制action
	QAction* getTransposeAction(){return _transposeAction;}

public slots:
	///以txt形式导出
	void exportAsTxt();

	///当选择改变时调用 
	void onSelectionChanged();

	///设置源model
	void onSetSourceModel();

	///选择行
	void onSelectRow(const QString& selectionName,int indices);

	///显示设置框
	void showSetting();

private:
	Ui::InteractiveTableWidget *ui;

	///源model
	SourceDataModel* _viewModel;

	///代理model
	SortTransposeProxyModel* _proxyModel;

	///exchangeModel
	ExchangeModel* _exchangeModel;

	///用于转变的action
	QAction* _transposeAction;

};

#endif // VINTERACTIVETABLEWIDGET_H
