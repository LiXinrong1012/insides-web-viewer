#ifndef SOLUTIONPROPERTYWIDGET_H
#define SOLUTIONPROPERTYWIDGET_H

#include <QWidget>
namespace Ui {class SolutionPropertyWidget;};

/*!
	@brief  用来显示解决方案的属性，暂时未启用
	@date   2015.6.16
	@author Jianjun
*/
class SolutionPropertyWidget : public QWidget
{
	Q_OBJECT

public:
	SolutionPropertyWidget(QWidget *parent = 0);
	~SolutionPropertyWidget();

private:
	Ui::SolutionPropertyWidget *ui;
};

#endif // SOLUTIONPROPERTYWIDGET_H
