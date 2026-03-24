#ifndef PREVTCD_H
#define PREVTCD_H

#include <QDataStream>

class QCustomPlot;

#ifndef PREVTCD_LIB
#define PREVTCD_EXPORT __declspec(dllimport) 
#else
#define PREVTCD_EXPORT __declspec(dllexport) 
#endif


extern "C" {
	PREVTCD_EXPORT void setCustomPlot(QCustomPlot* plot);
	PREVTCD_EXPORT void openViewSetting();
	PREVTCD_EXPORT void openCurveSetting();
	PREVTCD_EXPORT void saveSetting(QDataStream* data);
	PREVTCD_EXPORT void loadSetting(QDataStream* data);
};




#endif // PREVTCD_H
