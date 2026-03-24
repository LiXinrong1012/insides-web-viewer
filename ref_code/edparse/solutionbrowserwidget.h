#ifndef SOLUTIONBROWSERWIDGET_H
#define SOLUTIONBROWSERWIDGET_H

#include <QWidget>
#include <QComboBox>
namespace Ui {class SolutionBrowserWidget;};

class SolutionBrowserTreeWidget;

/*!
	@brief   解决方案树的外层widget
	@date    2015.6.18
	@author  Jerry
*/
class SolutionBrowserWidget : public QWidget
{
	Q_OBJECT

public:
	SolutionBrowserWidget(QWidget *parent = 0);
	~SolutionBrowserWidget();

	///获得真正的解决方案树
	SolutionBrowserTreeWidget* getSolutionBrowserTreeWidget();

public slots:
	///更新标签
	void updateTags();

private:
	Ui::SolutionBrowserWidget *ui;

};

#endif // SOLUTIONBROWSERWIDGET_H
