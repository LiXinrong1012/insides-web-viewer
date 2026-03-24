#ifndef TESTSOLVERDIALOG_H
#define TESTSOLVERDIALOG_H

#include <QDialog>
namespace Ui {class TestSolverDialog;};

/*!
	@brief   用于测试求解器管理界面（已弃用）
	@date    2015.6.23
	@author  Jerry
*/
class TestSolverDialog : public QDialog
{
	Q_OBJECT

public:
	TestSolverDialog(QWidget *parent = 0);
	~TestSolverDialog();

private slots:
	///当连接成功后
	void onConnect();

	///当求解开始后
	void onStart();

	///当求解暂停后
	void onPause();

	///当求解重启后
	void onRestart();

private:
	Ui::TestSolverDialog *ui;
};

#endif // TESTSOLVERDIALOG_H
