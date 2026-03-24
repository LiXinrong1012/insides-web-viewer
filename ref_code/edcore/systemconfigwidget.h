#ifndef SYSTEMCONFIGWIDGET_H
#define SYSTEMCONFIGWIDGET_H

#include <QWidget>
namespace Ui {class SystemConfigWidget;};

/*!
	@brief   系统调协标签页界面 
	@date	 2015.6.10
	@author  Jianjun
*/
class SystemConfigWidget : public QWidget
{
	Q_OBJECT

public:
	SystemConfigWidget(QWidget *parent = 0);
	~SystemConfigWidget();

	///是否自动检测更新
	bool isAutoUpdate();

	///设置是否自动检测更新
	void setAutoUpdate(bool b);

private:
	Ui::SystemConfigWidget *ui;
};

#endif // SYSTEMCONFIGWIDGET_H
