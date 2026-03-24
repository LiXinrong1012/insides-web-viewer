#include "colorSelector.h"
#include "rgbEditForm.h"

ColorSelector::ColorSelector(const QColor& color, QWidget* parent):
	QWidget(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(5, 0, 5, 0);
	m_color = new QFrame;
	m_color->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	m_color->setFixedHeight(20);
	mainLayout->addWidget(m_color);
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	m_cp = new QColorPicker(this);
	m_cp->setFrameStyle(QFrame::Panel + QFrame::Sunken);
	layout->addWidget(m_cp);
	m_lp = new QColorLuminancePicker;
	m_lp->setFixedWidth(20);
	layout->addWidget(m_lp);
	mainLayout->addLayout(layout);
	m_rgb = new RgbEditForm;
	setColor(color);
	mainLayout->addWidget(m_rgb);
	connect(m_cp, SIGNAL(newCol(int, int)), m_lp, SLOT(setCol(int, int)));
	connect(m_lp, SIGNAL(newHsv(int, int, int)), this, SLOT(onHsvChanged(int, int, int)));
	connect(m_rgb, SIGNAL(rgbChanged(int, int, int)), this, SLOT(onRgbChanged(int, int, int)));
}

QColor ColorSelector::getColor() const
{
	int r;
	int g;
	int b;
	m_rgb->getRgb(&r, &g, &b);
	return QColor(r, g, b);
}

void ColorSelector::setColor(const QColor& color)
{
	if (color == getColor()) {
		return;
	}
	setFrameColor(color);
	int h;
	int s;
	int v;
	color.getHsv(&h, &s, &v);
	m_rgb->blockSignals(true);
	m_cp->blockSignals(true);
	m_lp->blockSignals(true);
	m_cp->setCol(h, s);
	m_lp->setCol(h, s, v);
	m_rgb->setColor(color);
	m_rgb->blockSignals(false);
	m_cp->blockSignals(false);
	m_lp->blockSignals(false);
	emit colorChanged(color);
}

void ColorSelector::setFrameColor(const QColor& color)
{
	int r;
	int g;
	int b;
	color.getRgb(&r, &g, &b);
	m_color->setStyleSheet(QString("background: rgb(%1, %2, %3)").arg(r).arg(g).arg(b));
}

void ColorSelector::onHsvChanged(int h, int s, int v)
{
	QColor color;
	color.setHsv(h, s, v);
	m_rgb->blockSignals(true);
	m_rgb->setColor(color);
	m_rgb->blockSignals(false);
	setFrameColor(color);
	emit colorChanged(color);
}

void ColorSelector::onRgbChanged(int r, int g, int b)
{
	QColor color(r, g, b);
	m_cp->blockSignals(true);
	m_lp->blockSignals(true);
	int h;
	int s;
	int v;
	color.getHsv(&h, &s, &v);
	m_cp->setCol(h, s);
	m_lp->setCol(h, s, v);
	m_cp->blockSignals(false);
	m_lp->blockSignals(false);
	setFrameColor(color);
	emit colorChanged(color);
}