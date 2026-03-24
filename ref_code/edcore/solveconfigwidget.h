#ifndef SOLVECONFIGWIDGET_H
#define SOLVECONFIGWIDGET_H

#include <QWidget>
namespace Ui {class SolveConfigWidget;};

/*!
	@brief   求解器设置界面
	@date    2015.6.9
	@author  Jianjun
*/
class SolveConfigWidget : public QWidget
{
	Q_OBJECT

public:
	SolveConfigWidget(QWidget *parent = 0);
	~SolveConfigWidget();

	///获得日志更新时间间隔
	int getLogsSpinBoxValue();

	///设置日志更新时间间隔
	void setLogsSpinBoxValue(int value);

	/// 获得解决方案树的更新间隔时间
	int getTreeSpinBoxValue();

	/// 设置解决方案树的更新间隔时间
	void setTreeSpinBoxValue(int value);

	/// 获得一次最大求解工程数
	int getMaxSolveNumber();

	/// 设置一次最大求解工程数
	void setMaxSolveNumber(int value);

	///是否显示求解器界面
	bool isShowSolver();

	/// 设置是否显示求解器界面
	void setIsShowSolver(bool b );

private:
	Ui::SolveConfigWidget *ui;
};

#endif // SOLVECONFIGWIDGET_H
