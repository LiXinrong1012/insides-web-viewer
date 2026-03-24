#ifndef FINDRESULTSMANAGER_H
#define FINDRESULTSMANAGER_H

class QDockWidget;
class FindResultWidget;

/*!
	@brief   负责查找结果的管理
	@date    2015.6.19
	@author  Jerry
*/
class FindResultsManager
{
public:
	///获得本工程的唯一指针
	static FindResultsManager* instance();

	///获得放置查找结果widget的dockWidget by index
	QDockWidget* getResultDock(int index);

	///设置第index的dockWidget
	void setResultDock(int index,QDockWidget* w);

	///获得查找结果widget by index
	FindResultWidget* getResultWidget(int index);

	///设置第index的查找结果widget
	void setResultWidget(int index,FindResultWidget* w);

private:
	FindResultsManager();
	~FindResultsManager();

private:
	///存放查找结果widget的dockWidget
	QDockWidget* _findResultDock1;
	QDockWidget* _findResultDock2;
	
	///用于显示查找结果的widget
	FindResultWidget*	_findResultWidget1;
	FindResultWidget*	_findResultWidget2;

};

#endif // FINDRESULTSMANAGER_H
