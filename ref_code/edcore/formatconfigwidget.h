#ifndef FORMATCONFIGWIDGET_H
#define FORMATCONFIGWIDGET_H

#include <QWidget>
namespace Ui {class FormatConfigWidget;};

/*!
	@brief 格式化配置界面类
	@date  2015.6.5
	@author Jianjun
*/
class FormatConfigWidget : public QWidget
{
	Q_OBJECT

public:
	FormatConfigWidget(QWidget *parent = 0);
	~FormatConfigWidget();

	///获得缩进字符数
	int getIndentationValue();

	///设置缩进字符数
	void setIndentationValue(int value);

	///获得每行最大字符数
	int getLineMaxNumValue();

	///设置每行最大字符数
	void setLineMaxNumValue(int value);

private:
	Ui::FormatConfigWidget *ui;
};

#endif // FORMATCONFIGWIDGET_H
