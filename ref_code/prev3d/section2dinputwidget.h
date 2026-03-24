#ifndef SECTION2DINPUTWIDGET_H
#define SECTION2DINPUTWIDGET_H

#include <QWidget>
namespace Ui {class Section2DInputWidget;};

class Section2DInputWidget : public QWidget
{
	Q_OBJECT

public:
	Section2DInputWidget(QWidget *parent = 0);
	~Section2DInputWidget();

private:
	Ui::Section2DInputWidget *ui;
};

#endif // SECTION2DINPUTWIDGET_H
