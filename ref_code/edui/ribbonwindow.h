#ifndef RIBBONWINDOW_H
#define RIBBONWINDOW_H

#include <QtitanRibbon.h>


/* RibbonWindow */
/*!
	@brief   重新实现的mainWindow
	@date    2015.6.23
	@author  Jerry
*/
class RibbonWindow : public Qtitan::RibbonMainWindow
{
	Q_OBJECT
public:
	RibbonWindow(QWidget* parent = Q_NULL);
	virtual ~RibbonWindow();

private:
	///初始化actions以及菜单等
	void createOptions();

protected Q_SLOTS:
	///关于，未实现。
	void about();

	///设置样式
	virtual void options(QAction*);

	///样式选择框？ 未实现
	void optionsDialog();

	///包含动画
	void includingAnimation(bool);

	///设置最大化显示？
	void maximizeToggle();

	///最小显示方式改变？
	void minimizationChanged(bool minimized);

	///字体设置
	void optionsFont(QAction* act);

	///一些action的可用性设置
	void setDPIToggled(bool);

	///快速访问定制菜单
	void showQuickAccessCustomizeMenu(QMenu* menu);

	///快速访问条的位置
	void switchQuickAccessBarPosition();

#ifdef Q_OS_WIN
		void frameTheme(bool);
#endif // Q_OS_WIN

protected:
	///返回当前主题
	RibbonStyle::Theme theme() const;

	///设置主题
	void setOptions(RibbonStyle::Theme themeId);

	///设置按键主题样式
	void setButtonStyleTheme(RibbonStyle::Theme themeId);

	///更新action主题
	void updateActionsTheme();

protected:
	///重写event用来处理自定义事件eventNumber
	virtual bool event(QEvent* event);

protected:
	///操作菜单
	QMenu* m_menuOptions;

	///样式action
	QActionGroup* m_styleActions;
	
	///最小化action
	QAction* m_actionRibbonMinimize;

	///最小化菜单
	QAction* m_actionRibbonMinimizeMenu;

	///默认action
	QAction* m_actionDefault;

	///正常action
	QAction* m_actionNormal;

	///最大action
	QAction* m_actionLarge;

	///扩大action
	QAction* m_actionExLarge;

	///缩小action
	QAction* m_actionShowBelowRibbon;

	///向上action
	QAction* m_actionShowAboveRibbon;

	///默认字体
	int m_defaultFont;

	///记录当前样式
	Qtitan::RibbonStyle* m_ribbonStyle;
};

#endif // RIBBONWINDOW_H
