#include "showsettingdialog.h"

ShowSettingDialog::ShowSettingDialog(XYPointsTracer *tracer,DataPointShowFlag flag, QWidget *parent)
	: QDialog(parent)
	,_tracer(tracer)
{
	ui.setupUi(this);

	ui.distanceSpinBox->setValue(_tracer->getDistance());
	connect(ui.distanceSpinBox,SIGNAL(valueChanged ( int )),_tracer,SLOT(setDistance(int)));

	ui.fontSizeSpinBox->setValue(_tracer->getFontSize());
	connect(ui.fontSizeSpinBox,SIGNAL(valueChanged(int)),_tracer,SLOT(setFontSize(int)));

	QColor color = _tracer->getSelectedColor();
	ui.selectColorPushButton->setStyleSheet(QString("color:%1").arg(color.name()));
	connect(ui.selectColorPushButton,SIGNAL(clicked()),this,SLOT(onSelectColorPushButton()));
	connect(this,SIGNAL(changeColor(QColor)),_tracer,SLOT(setSelectedColor(QColor)));

	ui.validDoubleSpinBox->setValue(_tracer->getVaildDouble());
	connect(ui.validDoubleSpinBox,SIGNAL(valueChanged(int)),_tracer,SLOT(setVaildDouble(int)));

	ui.xCheckBox->setChecked(flag._xFlag);
	ui.yCheckBox->setChecked(flag._yFlag);
	ui.maxCheckBox->setChecked(flag._maxFlag);
	ui.minCheckBox->setChecked(flag._minFlag);
	ui.rxCheckBox->setChecked(flag._rxFlag);
	connect(this,SIGNAL(changeDataPointShowFlag(DataPointShowFlag)),_tracer,SLOT(setDataPointShowFlag(DataPointShowFlag)));
}

ShowSettingDialog::~ShowSettingDialog()
{

}

void ShowSettingDialog::onSelectColorPushButton()
{
	QColorDialog dialog;
	QColor color;
	if (dialog.exec() == QDialog::Accepted)
	{
		color = dialog.selectedColor();
	}
	else
		return;
	ui.selectColorPushButton->setStyleSheet(QString("color:%1").arg(color.name()));
	emit changeColor(color);
}

void ShowSettingDialog::onCheckBoxClicked()
{
	DataPointShowFlag flag;
	flag._xFlag = ui.xCheckBox->isChecked();
	flag._yFlag = ui.yCheckBox->isChecked();
	flag._maxFlag = ui.maxCheckBox->isChecked();
	flag._minFlag = ui.minCheckBox->isChecked();
	flag._rxFlag = ui.rxCheckBox->isChecked();

	emit changeDataPointShowFlag(flag);
}
