#ifndef ADDCUSTOMCURVEDIALOG_H
#define ADDCUSTOMCURVEDIALOG_H

#include <QDialog>
namespace Ui {class AddCustomCurveDialog;};

#include "resultselectorwidget.h"
#include "xyitemtitle.h"

/*!
	@brief   添加自定义曲线对话框
	@date    2015.7.2
	@author  Jerry
*/
class AddCustomCurveDialog : public QDialog
{
	Q_OBJECT

public:
	AddCustomCurveDialog(QWidget *parent = 0);
	~AddCustomCurveDialog();

	///设置是否为增加曲线模式
	void setIsAddMode(bool b=true ){_isAddMode = b;}

	///设置更新曲线信息
	void setUpdateCurveTitle(XYItemTitle title){_aboutUpdateCurveTitle = title;};

	///将旧的曲线的content更新到输入框中
	void updateConText();

	///获得自定义曲线对话框中的内容
	QString getCustomText();

signals:
	///添加一条曲线
	void addItem(XYItemTitle curveItem);

	///更新曲线curveItem
	void updateItem(XYItemTitle curveItem);

	///使用自定义数据
	void useCustomData();

private slots:
	///当添加按钮点击时调用
	void onAddBtnClicked();

	///当添加按钮点击时调用
	void onBtnAddClicked();

private:
	Ui::AddCustomCurveDialog *ui;

	///是否为增加曲线
	bool _isAddMode;
	
	///将要更新的曲线
	XYItemTitle _aboutUpdateCurveTitle;

	///是否使用自定义数据
	bool _isUse;
};

#endif // ADDCUSTOMCURVEDIALOG_H
