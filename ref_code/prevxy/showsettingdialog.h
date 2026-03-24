#ifndef SHOWSETTINGDIALOG_H
#define SHOWSETTINGDIALOG_H

#include <QDialog>
#include <QColorDialog>

#include "ui_showsettingdialog.h"

#include "xypointstracer.h"

class DataPointShowFlag;

/*!
	@brief   显示设置框
	@date    2015.7.3
	@author  Jianjun
*/
class ShowSettingDialog : public QDialog
{
	Q_OBJECT

public:
	ShowSettingDialog(XYPointsTracer *tracer,DataPointShowFlag flag,QWidget *parent = 0);
	~ShowSettingDialog();
signals:
	///改变颜色时发出
	void changeColor(QColor);

	///改变数据点显示标记时发出
	void changeDataPointShowFlag(DataPointShowFlag);

private slots:
	///当选择颜色按钮被点击时调用
	void onSelectColorPushButton();

	///当复选框被点击时调用
	void onCheckBoxClicked();

private:
	Ui::showSettingDialog ui;

	///显示点包装类指针
	XYPointsTracer* _tracer;

};

#endif // SHOWSETTINGDIALOG_H
