#ifndef _COLOR_SELECTOR_H_
#define _COLOR_SELECTOR_H_

#include "QColorPicker.h"

class RgbEditForm;
class ColorSelector : public QWidget
{
	Q_OBJECT
public:
	ColorSelector(const QColor& color = QColor(), QWidget* parent = NULL);
	QColor getColor() const;
	void setColor(const QColor& color);
signals:
	void colorChanged(const QColor& color);
private slots:
	void onHsvChanged(int h, int s, int v);
	void onRgbChanged(int h, int s, int v);
private:
	void setFrameColor(const QColor& color);
private:
	QFrame* m_color;
	RgbEditForm* m_rgb;
	QColorPicker* m_cp;
	QColorLuminancePicker* m_lp;
};


#endif