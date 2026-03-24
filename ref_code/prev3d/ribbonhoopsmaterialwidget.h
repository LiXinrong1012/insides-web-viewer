#ifndef RIBBONHOOPSMATERIALWIDGET_H
#define RIBBONHOOPSMATERIALWIDGET_H

#include <QObject>

class QCheckBox;
class QSlider;
class QColor;
class QAction;

namespace Qtitan
{
	class RibbonGroup;
	class PopupColorButton;
}

class RibbonHoopsMaterialWidget : public QObject
{
	Q_OBJECT

public:
	RibbonHoopsMaterialWidget(QObject *parent, Qtitan::RibbonGroup* group);
	~RibbonHoopsMaterialWidget();

private slots:
	void onUnset();
	void onUnsetAll();
	void onTransparencyChanged();
	void onColor(const QColor& color);
	void setColor();

private:
	QAction* cbFace;
	QAction* cbLine;
	QAction* cbVertex;
	QAction* cbText;
	Qtitan::PopupColorButton*	btnColor;

	QSlider*  sliderTransparency;
};

#endif // RIBBONHOOPSMATERIALWIDGET_H
