#ifndef PROJECTPROPERTYWIDGET_H
#define PROJECTPROPERTYWIDGET_H

#include <QWidget>
#include "ui_projectpropertywidget.h"

namespace INSEditor{
	class Project;
}

/*!
	@brief   工程属性显示界面
	@date    2015.6.16
	@author  Jianjun
*/
class ProjectPropertyWidget : public QWidget
{
	Q_OBJECT

public:
	ProjectPropertyWidget(QWidget *parent = 0);
	~ProjectPropertyWidget();

	///设置需要显示属性的工程
	void setProject(INSEditor::Project* project);

private slots:
	///当属性有所改变时保存当前状态
	void saveState();

private:
	Ui::ProjectPropertyWidget ui;

	///记录当前显示的工程
	INSEditor::Project* _project;
};

#endif // PROJECTPROPERTYWIDGET_H
