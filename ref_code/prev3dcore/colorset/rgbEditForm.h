#ifndef _RGB_EDIT_FORM_
#define _RGB_EDIT_FORM_

#include <QtGui>

class RgbEditForm : public QWidget
{
	Q_OBJECT
public:
	RgbEditForm(QWidget* parent = NULL);
	void getRgb(int* r, int* g, int* b) const;
public slots:
	void setColor(const QColor& color);
	void setRgb(int r, int g, int b);
signals:
	void rgbChanged(int r, int g, int b);
private slots:
	void onValueChanged(int v);
private:
	bool m_block;
	QSpinBox* m_r;
	QSpinBox* m_g;
	QSpinBox* m_b;
};


#endif