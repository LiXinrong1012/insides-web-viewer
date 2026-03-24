#ifndef PROPERTYDOCKWIDGET_H
#define PROPERTYDOCKWIDGET_H

#include <QDockWidget>
namespace Ui {class PropertyDockWidget;};

class PropertyWidget;

/*!
	@brief   用来显示工程或文件属性的dockWidget
	@date    2015.6.16
	@author  Jerry
*/
class PropertyDockWidget : public QDockWidget
{
	Q_OBJECT

public:
	PropertyDockWidget(QWidget *parent = 0);
	~PropertyDockWidget();
	///得到需要显示的属性界面种类（目前可为文件或工程）
	PropertyWidget* getPropertyWidget();

	///得到唯一单例指针
	static PropertyDockWidget* instance();

private:
	Ui::PropertyDockWidget *ui;
	static PropertyDockWidget* _instance;
};

#endif // PROPERTYDOCKWIDGET_H
