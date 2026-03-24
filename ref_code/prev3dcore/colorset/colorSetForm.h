#ifndef _COLOR_SET_FORM_H_
#define _COLOR_SET_FORM_H_

#include "colorSelector.h"
#include "QColorWell.h"
#include <QDialog>

namespace INSIDES{
	class AppearanceItem;
}

using namespace INSIDES;

class SliderSpinBox : public QObject
{
	Q_OBJECT
public:
	SliderSpinBox(QSpinBox* spin, QSlider* slider, QObject* parent = NULL);
private slots:
	void onSpinValueChanged(int val);
	void onSliderValueChanged(int val);
private:
	int spinToSlider(int val) const;
	int sliderToSpin(int val) const;
private:
	QSpinBox* m_spin;
	QSlider* m_slider;
	bool m_block;
};


class ColorSetForm : public QDialog
{
	Q_OBJECT
public:
	ColorSetForm(QWidget* parent = NULL);

	void setModel(const QModelIndex& index){_modelIndex=index;}
	void setAppearance(AppearanceItem* appItem);

protected slots:
	void onUnSet();
	void onUnSetAll();

	void onGeneralFlip();
	void onColorFlip();
	void onMaterialsFlip();

	void onCurrentColorChanged();
	void onTransparancyChanged();
private:
	void init();
	void initGeneralColors();
	void initRgbColors();

	void commitChanges();
private:
	QWidget* m_operating;
	QColorWell* m_generalColor;
	ColorSelector* m_rgbColor;
	QWidget* m_materials;
	QSpinBox* m_trans;
	QDoubleSpinBox* m_para1;
	QDoubleSpinBox* m_para2;
	QCheckBox* m_point;
	QCheckBox* m_line;
	QCheckBox* m_face;
	QCheckBox* m_edge;
	QColor m_color;
	QRgb m_rgbs[48];

	QModelIndex _modelIndex;
	AppearanceItem* _appearance;
};



#endif