#include "rgbEditForm.h"
#include "ui_rgbEditForm.h"

RgbEditForm::RgbEditForm(QWidget* parent):
	QWidget(parent),
	m_block(false)
{
	Ui::RgbEditForm ui;
	ui.setupUi(this);
	m_r = findChild<QSpinBox*>("redSpin");
	m_g = findChild<QSpinBox*>("greenSpin");
	m_b = findChild<QSpinBox*>("blueSpin");
	connect(m_r, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
	connect(m_g, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
	connect(m_b, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
}

void RgbEditForm::getRgb(int* r, int* g, int* b) const
{
	if (r) {
		*r = m_r->value();
	}
	if (g) {
		*g = m_g->value();
	}
	if (b) {
		*b = m_b->value();
	}
}

void RgbEditForm::setColor(const QColor& color)
{
	int r;
	int g;
	int b;
	color.getRgb(&r, &g, &b);
	setRgb(r, g, b);
}

void RgbEditForm::setRgb(int r, int g, int b)
{
	bool ch = false;
	m_block = true;
	if (r % 256 != m_r->value()) {
		ch = true;
		m_r->setValue(r % 256);
	}
	if (g % 256 != m_g->value()) {
		ch = true;
		m_g->setValue(g % 256);
	}
	if (b % 256 != m_b->value()) {
		ch = true;
		m_b->setValue(b % 256);
	}
	m_block = false;
	if (ch) {
		emit rgbChanged(m_r->value(), m_g->value(), m_b->value());
	}
}

void RgbEditForm::onValueChanged(int v)
{
	if (m_block) {
		return;
	}
	QObject* s = sender();
	if (s == m_r) {
		emit rgbChanged(v, m_g->value(), m_b->value());
	} else if (s == m_g) {
		emit rgbChanged(m_r->value(), v, m_b->value());
	} else if (s == m_b) {
		emit rgbChanged(m_r->value(), m_g->value(), v);
	}
}