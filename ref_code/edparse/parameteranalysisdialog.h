#ifndef EXHAUSTIONPARAMETER_H
#define EXHAUSTIONPARAMETER_H

#include <QDialog>
#include <QTableWidgetItem>
namespace Ui {class ParameterAnalysisDialog;};


namespace INSEditor{
	class Project;

	namespace Parse{
		class LineItem;
		class AssemblyItem;
	}
}

/*!
	@brief   参数分析对话框，通过给定参数的起始终止值以及增长步长，来批量建立程序
	@date    2015.6.17
	@author  Jianjun
*/
class ParameterAnalysisDialog : public QDialog
{
	Q_OBJECT

public:
	ParameterAnalysisDialog(INSEditor::Project* pro,QWidget *parent = 0);
	~ParameterAnalysisDialog();

signals:
	///创建工程信号
	void createProject(const QString& proName, const QString& text);

private slots:
	///当表格中的内容改变时调用
	void onItemChanged(QTableWidgetItem* item);

	void onItemDoubleClicked(QTableWidgetItem* item);
	void onEditingFinished();

	///当用户手动点击可用、禁用复选框时调用
	void onCheckBoxStateChanged ( int state);

	///当duplicate按钮被点击时调用
	void onDuplicateBtnClicked();

private:
	///初始化参数信息
	void initParameter();

	///处理LineItem
	void handleLineItem(INSEditor::Parse::LineItem* item);

	///添加一个parameter到表格
	void addItem(INSEditor::Parse::LineItem* item);

private:
	Ui::ParameterAnalysisDialog *ui;

	///当前所操作的Project，在构造函数时进行初始化和保存
	INSEditor::Project* _project;

	///解析模型文件得到对应的模型树
	INSEditor::Parse::AssemblyItem* _assmblyItem;

	int								_clickedRow;
	int								_clickedColumn;
};

#endif // EXHAUSTIONPARAMETER_H
