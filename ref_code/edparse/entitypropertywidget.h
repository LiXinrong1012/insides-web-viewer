#ifndef ENTITYPROPERTYWIDGET_H
#define ENTITYPROPERTYWIDGET_H

#include <QWidget>
#include "ui_entitypropertywidget.h"

namespace INSEditor{
	class Entity;
}

/*!
	@brief   文件属性的界面
	@date    2015.6.16
	@author  Jianjun
*/
class EntityPropertyWidget : public QWidget
{
	Q_OBJECT

public:
	EntityPropertyWidget(QWidget *parent = 0);
	~EntityPropertyWidget();

	///设置显示哪个属性的entity
	void setEntity(INSEditor::Entity* entity);

private slots:
	///当是否拷贝或是log有所改变时保存最新状态
	void saveState();

private:
	Ui::EntityPropertyWidget ui;

	///当前显示属性的entity
	INSEditor::Entity* _entity;
};

#endif // ENTITYPROPERTYWIDGET_H
