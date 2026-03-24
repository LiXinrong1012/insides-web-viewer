#include "appsettings.h"
#include <QApplication>
#include <QSettings>

AppSettings::AppSettings()
{
	
}

AppSettings::~AppSettings()
{
}

AppSettings* AppSettings::instance()
{
	static AppSettings settings;
	return &settings;
}

void AppSettings::readSettings()
{
	QString dir = _appPath+"/settings/";
	QSettings settings(dir +"appsettings.ini", QSettings::IniFormat);

	settings.beginGroup("LIGHT");
	hemisphericAmbient = settings.value("hemispheric_ambient",false).toBool();
	ambientTopColor.setRed(settings.value("ambient_top_color_r",255).toInt());
	ambientTopColor.setGreen(settings.value("ambient_top_color_g",255).toInt());
	ambientTopColor.setBlue(settings.value("ambient_top_color_b",255).toInt());
	ambientBottomColor.setRed(settings.value("ambient_bottom_color_r",255).toInt());
	ambientBottomColor.setGreen(settings.value("ambient_bottom_color_g",255).toInt());
	ambientBottomColor.setBlue(settings.value("ambient_bottom_color_b",255).toInt());
	useAmbientUpVector = settings.value("use_ambient_upVector",false).toBool();
	ambientUpVector.x = settings.value("ambient_up_vector_x",0.0f).toFloat();
	ambientUpVector.y = settings.value("ambient_up_vector_y",1.f).toFloat();
	ambientUpVector.z = settings.value("ambient_up_vector_z",0.0f).toFloat();

	useBloom = settings.value("use_bloom",false).toBool();
	bloomStrength = settings.value("bloom_strength",1.0f).toFloat();
	bloomBlur = settings.value("bloom_blur",5).toInt();
	bloomShape = settings.value("bloom_shape",0).toInt();

	lightFollowsCamera = settings.value("light_follows_camera",true).toBool();
	bLightScaling = settings.value("b_light_scaling",true).toBool();
	lightScaleFactor = settings.value("light_scale_factor",100000).toInt();
	lightCount = settings.value("light_count",1).toInt();

	goochColor1.setRed(settings.value("gooch_color_1_r",255).toInt());
	goochColor1.setGreen(settings.value("gooch_color_1_g",105).toInt());
	goochColor1.setBlue(settings.value("gooch_color_1_b",108).toInt());
	goochColor2.setRed(settings.value("gooch_color_2_r",60).toInt());
	goochColor2.setGreen(settings.value("gooch_color_2_g",179).toInt());
	goochColor2.setBlue(settings.value("gooch_color_2_b",113).toInt());
	goochColor3.setRed(settings.value("gooch_color_3_r",255).toInt());
	goochColor3.setGreen(settings.value("gooch_color_3_g",255).toInt());
	goochColor3.setBlue(settings.value("gooch_color_3_b",255).toInt());
	goochColor4.setRed(settings.value("gooch_color_4_r",255).toInt());
	goochColor4.setGreen(settings.value("gooch_color_4_g",255).toInt());
	goochColor4.setBlue(settings.value("gooch_color_4_b",255).toInt());
	goochColor5.setRed(settings.value("gooch_color_5_r",255).toInt());
	goochColor5.setGreen(settings.value("gooch_color_5_g",255).toInt());
	goochColor5.setBlue(settings.value("gooch_color_5_b",255).toInt());
	goochColor6.setRed(settings.value("gooch_color_6_r",255).toInt());
	goochColor6.setGreen(settings.value("gooch_color_6_g",255).toInt());
	goochColor6.setBlue(settings.value("gooch_color_6_b",255).toInt());

	goochColorMap = settings.value("gooch_color_map","blue, red").toString();
	goochWeight = settings.value("gooch_weight",0.5f).toFloat();
	goochColorHigh = settings.value("gooch_color_high",2.0f).toFloat();

	settings.endGroup();
}

void AppSettings::saveSettings()
{
	QString dir = _appPath+"/settings/";
	QSettings settings(dir +"appsettings.ini", QSettings::IniFormat);

	settings.beginGroup("LIGHT");
	settings.setValue("hemispheric_ambient",hemisphericAmbient);
	settings.setValue("ambient_top_color_r",ambientTopColor.red());
	settings.setValue("ambient_top_color_g",ambientTopColor.green());
	settings.setValue("ambient_top_color_b",ambientTopColor.blue());
	settings.setValue("ambient_bottom_color_r",ambientBottomColor.red());
	settings.setValue("ambient_bottom_color_g",ambientBottomColor.green());
	settings.setValue("ambient_bottom_color_b",ambientBottomColor.blue());
	settings.setValue("use_ambient_upVector",useAmbientUpVector);
	settings.setValue("ambient_up_vector_x",ambientUpVector.x);
	settings.setValue("ambient_up_vector_y",ambientUpVector.y);
	settings.setValue("ambient_up_vector_z",ambientUpVector.z);

	settings.setValue("use_bloom",useBloom);
	settings.setValue("bloom_strength",bloomStrength);
	settings.setValue("bloom_blur",bloomBlur);
	settings.setValue("bloom_shape",bloomShape);

	settings.setValue("light_follows_camera",lightFollowsCamera);
	settings.setValue("b_light_scaling",bLightScaling);
	settings.setValue("light_scale_factor",lightScaleFactor);
	settings.setValue("light_count",lightCount);

	settings.setValue("gooch_color_1_r",goochColor1.red());
	settings.setValue("gooch_color_1_g",goochColor1.green());
	settings.setValue("gooch_color_1_b",goochColor1.blue());
	settings.setValue("gooch_color_2_r",goochColor2.red());
	settings.setValue("gooch_color_2_g",goochColor2.green());
	settings.setValue("gooch_color_2_b",goochColor2.blue());
	settings.setValue("gooch_color_3_r",goochColor3.red());
	settings.setValue("gooch_color_3_g",goochColor3.green());
	settings.setValue("gooch_color_3_b",goochColor3.blue());
	settings.setValue("gooch_color_4_r",goochColor4.red());
	settings.setValue("gooch_color_4_g",goochColor4.green());
	settings.setValue("gooch_color_4_b",goochColor4.blue());
	settings.setValue("gooch_color_5_r",goochColor5.red());
	settings.setValue("gooch_color_5_g",goochColor5.green());
	settings.setValue("gooch_color_5_b",goochColor5.blue());
	settings.setValue("gooch_color_6_r",goochColor6.red());
	settings.setValue("gooch_color_6_g",goochColor6.green());
	settings.setValue("gooch_color_6_b",goochColor6.blue());

	settings.setValue("gooch_color_map",goochColorMap);
	settings.setValue("gooch_weight",goochWeight);
	settings.setValue("gooch_color_high",goochColorHigh);

	settings.endGroup();
}

void AppSettings::init()
{
	readSettings();
}

void AppSettings::save()
{
	saveSettings();
}
