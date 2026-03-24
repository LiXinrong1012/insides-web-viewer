#ifndef APPLICATIONPROPERTYDIALOG_H
#define APPLICATIONPROPERTYDIALOG_H

#include <QDialog>
#include "ui_applicationpropertydialog.h"

class DirConfigWidget;
class SolveConfigWidget;
class FormatConfigWidget;
class CustomConfigWidget;
class SystemConfigWidget;

/*!
	@brief 进行属性设置的界面类
	@date  2015.6.3
	@author Jianjun
*/
class ApplicationPropertyDialog : public QDialog
{
	Q_OBJECT

public:
	ApplicationPropertyDialog(QWidget *parent = 0);
	~ApplicationPropertyDialog();

private slots:
	///保存按钮单击事件连接槽
	void onSavePushButtonClicked();

	///点击树选项切换设置页
	void onTreeItemClicked (int row);

private:
	///隐藏所有widget
	void hideAllWidget();

private:
	Ui::ApplicationPropertyDialog ui;
	DirConfigWidget*		_dirConfigWidget;
	SolveConfigWidget*		_solveConfigWidget;
	FormatConfigWidget*		_formatConfigWidget;
	CustomConfigWidget*		_customConfigWidget;
	SystemConfigWidget*		_systemConfigWidget;

	///存储所有分类设置界面
	QList<QWidget*>			_widgetList;
};

#endif // APPLICATIONPROPERTYDIALOG_H
