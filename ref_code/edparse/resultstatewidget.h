#ifndef RESULTSTATEWIDGET_H
#define RESULTSTATEWIDGET_H

#include <QWidget>
#include "ui_resultstatewidget.h"

/*!
	@brief   结果状态界面类
	@date    2015.6.17
	@author  Jerry
*/
class ResultStateWidget : public QWidget
{
	Q_OBJECT

public:
	ResultStateWidget(QWidget *parent = 0);
	~ResultStateWidget();

public slots:
	///设置为没有结果状态
	void setNoResult();

	///设置为有结果状态
	void setHasResult();

	///开始计算求解
	void startRunning();

	///计算求解完成
	void endRunning();

	///设置求解进度
	void setRunningProgress(int progress);

private:
	///隐藏所有部件
	void hideAll();

private:
	Ui::ResultStateWidget ui;

};

#endif // RESULTSTATEWIDGET_H
