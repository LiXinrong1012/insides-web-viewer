#ifndef SHOWSETTINGDIALOG_H
#define SHOWSETTINGDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include "ui_showsettingdialog.h"
#include "curvepointstracer.h"

class DataPointShowFlag;

/*!
	@brief   显示设置对话框类
	@date    2015.6.30
	@author  Jianjun
*/
class ShowSettingDialog : public QDialog
{
	Q_OBJECT

public:
	ShowSettingDialog(CurvePointsTracer *tracer,DataPointShowFlag flag,QWidget *parent = 0);
	~ShowSettingDialog();

signals:
	///更改颜色信号
	void changeColor(QColor);

	///改变数据点的显示方式
	void changeDataPointShowFlag(DataPointShowFlag);

private slots:
	///当选择颜色按钮点击时调用
	void onSelectColorPushButton();

	///当复选框被点击时调用
	void onCheckBoxClicked();

private:
	Ui::showSettingDialog ui;

	///tracer指针
	CurvePointsTracer* _tracer;

};

#endif // SHOWSETTINGDIALOG_H
