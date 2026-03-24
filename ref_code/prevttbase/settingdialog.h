#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
namespace Ui {class SettingDialog;};

/*!
	@brief   表格设置类，用于存储所有表格可设置项
	@date    2015.6.30
	@author  Jianjun
*/
class TableSetting
{
public:
	int doubleCount;
};

/*!
	@brief   表格设置对话框
	@date    2015.6.30
	@author  Jianjun
*/
class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	SettingDialog(TableSetting& setting,QWidget *parent = 0);
	~SettingDialog();

private slots:
	///当保存按钮被点击时调用
	void onSave();

	///当取消按钮被点击时调用
	void onCancel();

private:
	Ui::SettingDialog *ui;

	///存储当前表格设置数据结构指针
	TableSetting* _setting;
};

#endif // SETTINGDIALOG_H
