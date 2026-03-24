#ifndef CUSTOMCONFIGWIDGET_H
#define CUSTOMCONFIGWIDGET_H

#include <QWidget>
namespace Ui {class CustomConfigWidget;};

/*!
	@brief 常规设置界面类
	@date  2015.6.3
	@author Jianjun
*/
class CustomConfigWidget : public QWidget
{
	Q_OBJECT

public:
	CustomConfigWidget(QWidget *parent = 0);
	~CustomConfigWidget();

	///是否显示上次关闭时打开的文件 
	bool isShowLastFiles();
	void setIsShowLastFiles(bool b);

	///是否需要创建模型树
	bool isCreateModelTree();
	void setIsCreateModelTree(bool b);

	///是否自动显示帮助信息
	bool isAutoShowHelp();
	void setIsAutoShowHelp(bool b);

private:
	Ui::CustomConfigWidget *ui;
};

#endif // CUSTOMCONFIGWIDGET_H
