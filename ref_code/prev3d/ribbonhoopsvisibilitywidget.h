#ifndef RIBBONHOOPSVISIBILITYWIDGET_H
#define RIBBONHOOPSVISIBILITYWIDGET_H

#include <QWidget>
namespace Ui {class RibbonHoopsVisibilityWidget;};

class ViewManager;
class PreHQWidget;

class RibbonHoopsVisibilityWidget : public QWidget
{
	Q_OBJECT

public:
	RibbonHoopsVisibilityWidget(QWidget *parent = 0);
	~RibbonHoopsVisibilityWidget();

	static ViewManager* getViewManager();
	static PreHQWidget* getRenderView();

private slots:
	void controlChanged();
	void uiAllChanged();

private:
	Ui::RibbonHoopsVisibilityWidget *ui;
	bool	_disabled;

	void updateValue();



};

#endif // RIBBONHOOPSVISIBILITYWIDGET_H
