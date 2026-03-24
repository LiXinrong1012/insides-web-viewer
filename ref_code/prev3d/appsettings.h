#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QColor>
#include "HBaseView.h"

/*!
*	用于存储渲染相关参数的设置
*	@author Jianjun
*	@date	2015.05.25
*/
class AppSettings : public QObject
{
public:
	static AppSettings* instance();
	///调用INIT前先设置APPPATH
	void init();
	///保存当前的设置参数
	void save();


	void setAppPath(const QString& path){_appPath = path;}
	const QString& getAppPath(){return _appPath;}

public:
	///半球的环境 ？
	bool hemisphericAmbient;
	///周围环境的顶部颜色 ？
	QColor ambientTopColor;
	///底部
	QColor ambientBottomColor;

	bool useAmbientUpVector;

	HPoint ambientUpVector;

	bool lightFollowsCamera;

	bool bLightScaling;

	int lightScaleFactor;

	int lightCount;

	QColor goochColor1;

	QColor goochColor2;

	QColor goochColor3;

	QColor goochColor4;

	QColor goochColor5;

	QColor goochColor6;

	QString goochColorMap;

	float goochWeight;

	float goochColorHigh;

	bool useBloom;

	float bloomStrength;

	int bloomBlur;

	int bloomShape;
private:
	void readSettings();
	void saveSettings();
private:
	HBaseView* _hBaseView;
	QString _appPath;
private:
	AppSettings();
	~AppSettings();
};

#endif // APPSETTINGS_H
