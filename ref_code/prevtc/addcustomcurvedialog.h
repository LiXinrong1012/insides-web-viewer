#ifndef ADDCUSTOMCURVEDIALOG_H
#define ADDCUSTOMCURVEDIALOG_H

#include <QDialog>
namespace Ui {class AddCustomCurveDialog;};

#include "resultselectorwidget.h"

/*!
	@brief   自定义曲线添加对话框，支持通过公式等方式添加自定义曲线
	@date    2015.6.26
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

	///更新曲线title
	void setUpdateCurveTitle(CurveItemTitle title){_aboutUpdateCurveTitle = title;};

	///将旧的曲线的content更新到输入框中显示
	void updateConText();

signals:
	///当需要添加曲线时发送
	void addItem(CurveItemTitle curveItem);

	///当需要更新曲线时发送
	void updateItem(CurveItemTitle curveItem);

private slots:
	///当添加按钮被单击时调用
	void onAddBtnClicked();

private:
	Ui::AddCustomCurveDialog *ui;

	///是否为增加曲线模式
	bool _isAddMode;

	///将要更新的曲线
	CurveItemTitle _aboutUpdateCurveTitle;
};

#endif // ADDCUSTOMCURVEDIALOG_H
