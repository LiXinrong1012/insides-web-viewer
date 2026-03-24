#include "colorSetForm.h"
#include "ui_colorSetForm.h"
#include "rgbEditForm.h"

#include "precore/appearance.h"

using namespace INSIDES;

SliderSpinBox::SliderSpinBox(QSpinBox* spin, QSlider* slider, QObject* parent):
	m_spin(spin),
	m_slider(slider),
	m_block(false)
{
	connect(spin, SIGNAL(valueChanged(int)), this, SLOT(onSpinValueChanged(int)));
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));
	onSpinValueChanged(m_spin->value());
}

void SliderSpinBox::onSpinValueChanged(int val)
{
	if (m_block) {
		return;
	}
	m_block = true;
	m_slider->setSliderPosition(spinToSlider(val));
	m_block = false;
}

void SliderSpinBox::onSliderValueChanged(int val)
{
	if (m_block) {
		return;
	}
	m_block = true;
	m_spin->setValue(sliderToSpin(val));
	m_block = false;
}

int SliderSpinBox::spinToSlider(int val) const
{
	double x1 = m_spin->minimum();
	double y1 = m_spin->maximum();
	int x2 = m_slider->minimum();
	int y2 = m_slider->maximum();
	if (fabs(x1 - y1) < 1.e-5) {
		return x2;
	} else {
		return (int)((double)(y2 - x2) * (val - x1) / (y1 - x1) + x2);
	}
}

int SliderSpinBox::sliderToSpin(int val) const
{
	double x1 = m_spin->minimum();
	double y1 = m_spin->maximum();
	int x2 = m_slider->minimum();
	int y2 = m_slider->maximum();
	if (x2 == y2) {
		return x1;
	} else {
		return (y1 - x1) * (double)(val - x2) / (double)(y2 - x2) + x1;
	}
}


#define ConnectPBSlot(name, slot) \
	connect(findChild<QPushButton*>(name), SIGNAL(clicked(bool)), this, SLOT(slot()))

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ColorSetForm::ColorSetForm(QWidget *parent)
	:QDialog(parent)
	,_appearance(NULL)
{
	Ui::ColorSetForm ui;;
	ui.setupUi(this);
	ConnectPBSlot("unsetPB", onUnSet);
	ConnectPBSlot("unsetAllPB", onUnSetAll);
	ConnectPBSlot("generalTitle", onGeneralFlip);
	ConnectPBSlot("rgbColorTitle", onColorFlip);
	ConnectPBSlot("materialsTitle", onMaterialsFlip);
	m_operating = findChild<QWidget*>("operatingContents");
	m_point = findChild<QCheckBox*>("pointCB");
	m_line = findChild<QCheckBox*>("lineCB");
	m_face = findChild<QCheckBox*>("faceCB");
	m_edge = findChild<QCheckBox*>("edgeCB");

	m_materials = findChild<QWidget*>("materialsContents");
	m_trans = findChild<QSpinBox*>("transSpin");
	m_para1 = findChild<QDoubleSpinBox*>("para1Spin");
	m_para2 = findChild<QDoubleSpinBox*>("para2Spin");
	new SliderSpinBox(m_trans, findChild<QSlider*>("transSlider"), this);
	connect(m_trans,SIGNAL(valueChanged(int)),this,SLOT(onTransparancyChanged()));
	//new SliderSpinBox(m_para1, findChild<QSlider*>("para1Slider"), this);
	//new SliderSpinBox(m_para2, findChild<QSlider*>("para2Slider"), this);
	init();

	m_rgbColor->setVisible(false);
}

void ColorSetForm::init()
{
	initGeneralColors();
	initRgbColors();
}

void ColorSetForm::initGeneralColors()
{
	int i = 0;
	for (int g = 0; g < 4; ++g) {
		for (int r = 0; r < 4; ++r) {
			for (int b = 0; b < 3; ++b) {
				m_rgbs[i++] = qRgb(r * 255 / 3, g * 255 / 3, b * 255 / 2);
			}
		}
	}
	QVBoxLayout* vlayout = findChild<QVBoxLayout*>("generalLayout");
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	m_generalColor = new QColorWell(this, 6, 8, m_rgbs);
	layout->addWidget(m_generalColor);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	vlayout->addLayout(layout);
	connect(m_generalColor, SIGNAL(selected(int, int)), this, SLOT(onCurrentColorChanged()));
}

void ColorSetForm::initRgbColors()
{
	QVBoxLayout* layout = findChild<QVBoxLayout*>("rgbColorLayout");
	m_rgbColor = new ColorSelector(QColor(128, 128, 128));
	layout->addWidget(m_rgbColor);
	connect(m_rgbColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(onCurrentColorChanged()));
}



void ColorSetForm::onUnSet()
{
	if(!_appearance)
		return;

	if(m_point->isChecked())
		_appearance->setUseColor(AppearanceItem::Color_Point,false);
	if(m_edge->isChecked())
		_appearance->setUseColor(AppearanceItem::Color_Edge,false);
	if(m_line->isChecked())
		_appearance->setUseColor(AppearanceItem::Color_Line,false);
	if(m_face->isChecked())
		_appearance->setUseColor(AppearanceItem::Color_Face,false);

	commitChanges();
}

void ColorSetForm::onUnSetAll()
{
	if(!_appearance)
		return;

	_appearance->setUseColorAll(false);
	commitChanges();
}


void ColorSetForm::onGeneralFlip()
{
	m_generalColor->setVisible(!m_generalColor->isVisible());
}

void ColorSetForm::onColorFlip()
{
	m_rgbColor->setVisible(!m_rgbColor->isVisible());
}

void ColorSetForm::onMaterialsFlip()
{
	m_materials->setVisible(!m_materials->isVisible());
}

static void _setOneColor(QCheckBox* checkBox,
	AppearanceItem* appItem,AppearanceItem::ColorItem t,const QColor& color)
{
	if(checkBox->isChecked()){
		appItem->setUseColor(t,true);
		appItem->setColor(t,color);
	}
}
void ColorSetForm::onCurrentColorChanged()
{
	if(!_appearance)
		return;

	QObject* obj = sender();
	if (obj == m_generalColor) {
		int row = m_generalColor->selectedRow();
		int col = m_generalColor->selectedColumn();
		m_color = m_rgbs[row + col * 6];
	} else if (obj == m_rgbColor) {
		m_color = m_rgbColor->getColor();
	}

	_setOneColor(m_face,_appearance,AppearanceItem::Color_Face,m_color);
	_setOneColor(m_edge,_appearance,AppearanceItem::Color_Edge,m_color);
	_setOneColor(m_line,_appearance,AppearanceItem::Color_Line,m_color);
	_setOneColor(m_point,_appearance,AppearanceItem::Color_Point,m_color);

	commitChanges();
}





void ColorSetForm::setAppearance( AppearanceItem* appItem )
{
	_appearance=appItem;
}

void ColorSetForm::commitChanges()
{
	if(!_modelIndex.isValid() || !_appearance)
		return;

	const_cast<QAbstractItemModel*>(_modelIndex.model())->setData(_modelIndex,
		(qlonglong)(void*)_appearance,Qt::EditRole);
}

void ColorSetForm::onTransparancyChanged()
{
	if(!_appearance)
		return;

	_appearance->setTransparency(m_trans->value()/100.0);
	commitChanges();
}
