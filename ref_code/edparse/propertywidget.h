#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include "ui_propertywidget.h"


class EntityPropertyWidget;
class ProjectPropertyWidget;

/*!
	@brief   用来显示属性的界面
	@date    2015.6.16
	@author  Jerry
*/
class PropertyWidget : public QWidget
{
	Q_OBJECT

public:
	PropertyWidget(QWidget *parent = 0);
	~PropertyWidget();

public slots:
	///当解决方案树选择的条目改变时，更改为不同的界面显示
	void onItemChanged(void* item, int itemType);

	///设置显示一个空白的界面
	void setEmptyView();

private:
	///清除所有视图内容
	void clearAllView();

private:
	Ui::PropertyWidget ui;
	QHBoxLayout* _propertyLayout;

	///文件各类的属性界面
	EntityPropertyWidget* _entityPropertyWidget;

	///工程各类的属性界面
	ProjectPropertyWidget* _projectPropertyWidget;
};

#endif // PROPERTYDIALOG_H
