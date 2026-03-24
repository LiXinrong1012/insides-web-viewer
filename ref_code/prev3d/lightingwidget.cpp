#include "lightingwidget.h"
#include "ui_lightingwidget.h"
#include "appsettings.h"

#include <QMessageBox>
#include <QColorDialog>

#include "HTools.h"

LightingWidget::LightingWidget(QWidget *parent)
	: QWidget(parent)
	,_hBaseView(NULL)
{
	ui = new Ui::LightingWidget();
	ui->setupUi(this);
	ui->color1Frame->installEventFilter(this);
	ui->color2frame->installEventFilter(this);

	ui->lightFrame1->installEventFilter(this);
	ui->lightFrame2->installEventFilter(this);
	ui->lightFrame3->installEventFilter(this);
	ui->lightFrame4->installEventFilter(this);
	ui->lightFrame5->installEventFilter(this);
	ui->lightFrame6->installEventFilter(this);
	
	updateItemsEnable();

	connect(ui->applyPushButton,SIGNAL(clicked()),this,SLOT(onApplyPushButtonClicked()));
	connect(ui->resetPushButton,SIGNAL(clicked()),this,SLOT(onResetBtnClicked()));

	connect(ui->lightScalingCheckBox,SIGNAL(stateChanged(int)),this,SLOT(onAmbientCheckBoxStateChanged()));
	connect(ui->hemisphericAmbientCheckBox,SIGNAL(stateChanged(int)),this,SLOT(onAmbientCheckBoxStateChanged()));
	connect(ui->upVectorCheckBox,SIGNAL(stateChanged(int)),this,SLOT(onAmbientCheckBoxStateChanged()));
	connect(ui->bloomCheckBox,SIGNAL(stateChanged(int)),this,SLOT(onAmbientCheckBoxStateChanged()));
}

LightingWidget::~LightingWidget()
{
	delete ui;
}
void LightingWidget::onResetBtnClicked()
{
	int a = _hBaseView->GetLightCount();
}

void LightingWidget::updateLightingWidget()
{
	AppSettings* settings = AppSettings::instance();
	ui->hemisphericAmbientCheckBox->setChecked(settings->hemisphericAmbient);
	QPalette p = ui->color1Frame->palette();
	p.setColor(QPalette::Background,settings->ambientTopColor);
	ui->color1Frame->setPalette(p);
	p = ui->color2frame->palette();
	p.setColor(QPalette::Background,settings->ambientBottomColor);
	ui->color2frame->setPalette(p);
	ui->upVectorCheckBox->setChecked(settings->useAmbientUpVector);
	ui->xLineEdit->setText(QString("%1").arg(settings->ambientUpVector.x));
	ui->yLineEdit->setText(QString("%1").arg(settings->ambientUpVector.y));
	ui->zLineEdit->setText(QString("%1").arg(settings->ambientUpVector.z));

	ui->bloomCheckBox->setChecked(settings->useBloom);
	ui->strengthLineEdit->setText(QString("%1").arg(settings->bloomStrength));
	ui->blurLineEdit->setText(QString("%1").arg(settings->bloomBlur));
	ui->radialComboBox->setCurrentItem(settings->bloomShape);

	ui->lightFollowsCameraCheckBox->setChecked(settings->lightFollowsCamera);
	ui->lightScalingCheckBox->setChecked(settings->bLightScaling);
	ui->scaleFactorLineEdit->setText(QString("%1").arg(settings->lightScaleFactor/100000));
	ui->lightsComboBox->setCurrentItem(settings->lightCount);

	p = ui->lightFrame1->palette();
	p.setColor(QPalette::Background, settings->goochColor1);
	ui->lightFrame1->setPalette(p);
	p = ui->lightFrame2->palette();
	p.setColor(QPalette::Background, settings->goochColor2);
	ui->lightFrame2->setPalette(p);
	p = ui->lightFrame3->palette();
	p.setColor(QPalette::Background, settings->goochColor3);
	ui->lightFrame3->setPalette(p);
	p = ui->lightFrame4->palette();
	p.setColor(QPalette::Background, settings->goochColor4);
	ui->lightFrame4->setPalette(p);
	p = ui->lightFrame5->palette();
	p.setColor(QPalette::Background, settings->goochColor5);
	ui->lightFrame5->setPalette(p);
	p = ui->lightFrame6->palette();
	p.setColor(QPalette::Background, settings->goochColor6);
	ui->lightFrame6->setPalette(p);

	ui->diffuseWeightLineEdit->setText(QString("%1").arg(settings->goochWeight));
	ui->numberOfColorLineEdit->setText(QString("%1").arg(settings->goochColorHigh));
}

void LightingWidget::onApplyPushButtonClicked()
{
	bool flag = true;
	ui->xLineEdit->text().toFloat(&flag);
	if(!flag)
	{
		QMessageBox::warning(this,"Warning","Please input a number!");
		ui->xLineEdit->setFocus();
		ui->xLineEdit->selectAll();
		return;
	}
	ui->yLineEdit->text().toFloat(&flag);
	if(!flag)
	{
		QMessageBox::warning(this,"Warning","Please input a number!");
		ui->yLineEdit->setFocus();
		ui->yLineEdit->selectAll();
		return;
	}
	ui->zLineEdit->text().toFloat(&flag);
	if(!flag)
	{
		QMessageBox::warning(this,"Warning","Please input a number!");
		ui->zLineEdit->setFocus();
		ui->zLineEdit->selectAll();
		return;
	}
	AppSettings* settings = AppSettings::instance();
	settings->hemisphericAmbient = ui->hemisphericAmbientCheckBox->isChecked();
	QPalette p = ui->color1Frame->palette();
	settings->ambientTopColor = p.color(QPalette::Background);
	p = ui->color2frame->palette();
	settings->ambientBottomColor = p.color(QPalette::Background);
	settings->useAmbientUpVector = ui->upVectorCheckBox->isChecked();
	settings->ambientUpVector.x = ui->xLineEdit->text().toFloat();
	settings->ambientUpVector.y = ui->yLineEdit->text().toFloat();
	settings->ambientUpVector.z = ui->zLineEdit->text().toFloat();

	settings->useBloom = ui->bloomCheckBox->isChecked();
	settings->bloomStrength = ui->strengthLineEdit->text().toFloat();
	settings->bloomBlur = ui->blurLineEdit->text().toInt();
	settings->bloomShape = ui->radialComboBox->currentIndex();

	settings->lightFollowsCamera = ui->lightFollowsCameraCheckBox->isChecked();
	settings->bLightScaling = ui->lightScalingCheckBox->isChecked();
	settings->lightScaleFactor = ui->scaleFactorLineEdit->text().toInt()*100000;
	settings->lightCount = ui->lightsComboBox->currentText().toInt();

	p = ui->lightFrame1->palette();
	settings->goochColor1 = p.color(QPalette::Background);
	p = ui->lightFrame2->palette();
	settings->goochColor2 = p.color(QPalette::Background);
	p = ui->lightFrame3->palette();
	settings->goochColor3 = p.color(QPalette::Background);
	p = ui->lightFrame4->palette();
	settings->goochColor4 = p.color(QPalette::Background);
	p = ui->lightFrame5->palette();
	settings->goochColor5 = p.color(QPalette::Background);
	p = ui->lightFrame6->palette();
	settings->goochColor6 = p.color(QPalette::Background);

	char goochColorMap[MVO_BUFFER_SIZE];

	sprintf(goochColorMap, "(R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f)", 
		settings->goochColor1.red()/255.0f, 
		settings->goochColor1.green()/255.0f,
		settings->goochColor1.blue()/255.0f,
		settings->goochColor2.red()/255.0f, 
		settings->goochColor2.green()/255.0f,
		settings->goochColor2.blue()/255.0f,
		settings->goochColor3.red()/255.0f, 
		settings->goochColor3.green()/255.0f,
		settings->goochColor3.blue()/255.0f,
		settings->goochColor4.red()/255.0f, 
		settings->goochColor4.green()/255.0f,
		settings->goochColor4.blue()/255.0f,
		settings->goochColor5.red()/255.0f, 
		settings->goochColor5.green()/255.0f,
		settings->goochColor5.blue()/255.0f,
		settings->goochColor6.red()/255.0f, 
		settings->goochColor6.green()/255.0f,
		settings->goochColor6.blue()/255.0f);
	settings->goochColorMap = goochColorMap;	

	settings->goochWeight = ui->diffuseWeightLineEdit->text().toFloat();
	settings->goochColorHigh = ui->numberOfColorLineEdit->text().toFloat();

	updateHoopsLights();
	settings->save();
}

void LightingWidget::updateItemsEnable()
{
	if (ui->hemisphericAmbientCheckBox->isChecked())
	{
		ui->label_2->setEnabled(true);
		ui->color2frame->setEnabled(true);
		ui->upVectorCheckBox->setEnabled(true);
		if(ui->upVectorCheckBox->isChecked())
		{
			ui->label_3->setEnabled(true);
			ui->label_4->setEnabled(true);
			ui->label_5->setEnabled(true);
			ui->xLineEdit->setEnabled(true);
			ui->yLineEdit->setEnabled(true);
			ui->zLineEdit->setEnabled(true);
		}
		else
		{
			ui->label_3->setEnabled(false);
			ui->label_4->setEnabled(false);
			ui->label_5->setEnabled(false);
			ui->xLineEdit->setEnabled(false);
			ui->yLineEdit->setEnabled(false);
			ui->zLineEdit->setEnabled(false);
		}
	}
	else
	{
		ui->label_2->setEnabled(false);
		ui->color2frame->setEnabled(false);
		ui->upVectorCheckBox->setEnabled(false);
		ui->label_3->setEnabled(false);
		ui->label_4->setEnabled(false);
		ui->label_5->setEnabled(false);
		ui->xLineEdit->setEnabled(false);
		ui->yLineEdit->setEnabled(false);
		ui->zLineEdit->setEnabled(false);
	}

	if(ui->bloomCheckBox->isChecked())
	{
		ui->label_6->setEnabled(true);
		ui->strengthLineEdit->setEnabled(true);
		ui->label_7->setEnabled(true);
		ui->blurLineEdit->setEnabled(true);
		ui->label_8->setEnabled(true);
		ui->radialComboBox->setEnabled(true);
	}
	else
	{
		ui->label_6->setEnabled(false);
		ui->strengthLineEdit->setEnabled(false);
		ui->label_7->setEnabled(false);
		ui->blurLineEdit->setEnabled(false);
		ui->label_8->setEnabled(false);
		ui->radialComboBox->setEnabled(false);
	}

	if (ui->lightScalingCheckBox->isChecked())
	{
		ui->label_9->setEnabled(true);
		ui->scaleFactorLineEdit->setEnabled(true);
	}
	else
	{
		ui->label_9->setEnabled(false);
		ui->scaleFactorLineEdit->setEnabled(false);
	}
}

void LightingWidget::onAmbientCheckBoxStateChanged()
{
	updateItemsEnable();
}

void LightingWidget::updateHoopsLights()
{
	char ambientColor[MVO_BUFFER_SIZE];
	char ropt[MVO_BUFFER_SIZE];
	char dopt[MVO_BUFFER_SIZE];
	if (_hBaseView)
	{
		_hBaseView->SetSuppressUpdate(true);
		AppSettings* settings = AppSettings::instance();
		if (settings->bLightScaling)
			_hBaseView->SetLightScaling(settings->lightScaleFactor/100000.0f);
		else
			_hBaseView->SetLightScaling(0);

		_hBaseView->SetLightFollowsCamera(settings->lightFollowsCamera);
		_hBaseView->SetLightCount(settings->lightCount);

		HC_Open_Segment_By_Key(_hBaseView->GetSceneKey());
			HC_Open_Segment("./overwrite/lights/gooch_color_map_segment");
				HC_Set_Color_Map(H_ASCII_TEXT(settings->goochColorMap));
			HC_Close_Segment();
	
			if(settings->hemisphericAmbient)
			{
				float r1, g1, b1, r2, g2, b2;

				//darken all colors by about 75%
				r1 = (((settings->ambientTopColor).red())/255.0f)*0.24705882;
				g1 = ((settings->ambientTopColor).green()/255.0f)*0.24705882;
				b1=((settings->ambientTopColor).blue()/255.0f)*0.24705882;

				r2=(((settings->ambientBottomColor).red())/255.0f)*0.24705882;
				g2=(((settings->ambientBottomColor).green())/255.0f)*0.24705882;
				b2=(((settings->ambientBottomColor).blue())/255.0f)*0.24705882;

				sprintf(ambientColor, "ambient up=(R=%f G=%f B=%f), ambient down=(r=%f g=%f b=%f),gloss=30.0", 
					r1, g1, b1, r2, g2, b2);

				HC_Set_Color(ambientColor);
				HC_Define_System_Options("disable ambient material");

				if(settings->useAmbientUpVector)
				{
					sprintf(ropt, "ambient up vector = (%f, %f, %f)",settings->ambientUpVector.x,settings->ambientUpVector.y,settings->ambientUpVector.z);
					HC_Set_Rendering_Options(ropt);
				}
				else
					HC_Set_Rendering_Options("no ambient up vector");
			}
			else
			{
				float r1, g1, b1;

				//darken all colors by about 75%
				r1=((settings->ambientTopColor).red())/255.0f;
				g1=((settings->ambientTopColor).green())/255.0f;
				b1=((settings->ambientTopColor).blue())/255.0f;

				sprintf(ambientColor, "ambient=(R=%f G=%f B=%f)", r1, g1, b1);
				HC_Set_Color(ambientColor);
				HC_Set_Rendering_Options("no ambient up vector");
				HC_Define_System_Options("no disable ambient material");
			}

			HCLOCALE(sprintf(ropt, "gooch options = (diffuse weight = %f, color range=(0.0, %f), color map segment = `./overwrite/lights/gooch_color_map_segment`)",
				settings->goochWeight, settings->goochColorHigh));
			HC_Set_Rendering_Options(ropt);			
		HC_Close_Segment();

		sprintf(dopt, "bloom = (%s, strength=%f, blur=%d, shape=%s)", 
			(settings->useBloom ? "on" : "off"), 
			settings->bloomStrength, 
			settings->bloomBlur,
			(settings->bloomShape == RadialBloom ? "radial" : "star")); 
		HC_Open_Segment_By_Key(_hBaseView->GetViewKey());
			HC_Set_Driver_Options(dopt);
		HC_Close_Segment();
		_hBaseView->SetSuppressUpdate(false);
		_hBaseView->Update();
	}
	_hBaseView->Update();
	updateItemsEnable();
}

bool LightingWidget::eventFilter( QObject * watched, QEvent * event )
{
	if(event->type() == QEvent::MouseButtonDblClick)
	{
		if(watched == ui->color1Frame)
			onColor1FrameDoubleClicked();
		else if(watched == ui->color2frame)
			onColor2FrameDoubleClicked();
		else if(watched == ui->lightFrame1)
			onLightFrame1DoubleClicked();
		else if(watched == ui->lightFrame2)
			onLightFrame2DoubleClicked();
		else if(watched == ui->lightFrame3)
			onLightFrame3DoubleClicked();
		else if(watched == ui->lightFrame4)
			onLightFrame4DoubleClicked();
		else if(watched == ui->lightFrame5)
			onLightFrame5DoubleClicked();
		else if(watched == ui->lightFrame6)
			onLightFrame6DoubleClicked();
	}

	return QWidget::eventFilter(watched,event);
}

void LightingWidget::onColor1FrameDoubleClicked()
{
	QPalette p = ui->color1Frame->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->color1Frame->setPalette(p);
	}
}

void LightingWidget::onColor2FrameDoubleClicked()
{
	QPalette p = ui->color2frame->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->color2frame->setPalette(p);
	}
}

void LightingWidget::onLightFrame1DoubleClicked()
{
	QPalette p = ui->lightFrame1->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->lightFrame1->setPalette(p);
	}
}

void LightingWidget::onLightFrame2DoubleClicked()
{
	QPalette p = ui->lightFrame2->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->lightFrame2->setPalette(p);
	}
}

void LightingWidget::onLightFrame3DoubleClicked()
{
	QPalette p = ui->lightFrame3->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->lightFrame3->setPalette(p);
	}
}

void LightingWidget::onLightFrame4DoubleClicked()
{
	QPalette p = ui->lightFrame4->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->lightFrame4->setPalette(p);
	}
}

void LightingWidget::onLightFrame5DoubleClicked()
{
	QPalette p = ui->lightFrame5->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->lightFrame5->setPalette(p);
	}
}

void LightingWidget::onLightFrame6DoubleClicked()
{
	QPalette p = ui->lightFrame6->palette();
	QColor color = QColorDialog::getColor(p.color(QPalette::Background),this);
	if(color.isValid())
	{
		p.setColor(QPalette::Background, color);
		ui->lightFrame6->setPalette(p);
	}
}


