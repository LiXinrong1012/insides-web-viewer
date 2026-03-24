#ifndef CurveParasSerialize_H
#define CurveParasSerialize_H

#include "CustomPlotViewSetting.h"

class QDataStream;
class CurvePlotSettingDialog;
class CurveSettingDialog;
class QFont;
class QColor;

/*!
	@brief   该类用于处理数据流与轴和曲线的存储读取关系
	@date    2015.7.2
	@author  Jerry
*/
class CurveParasSerialize
{
public:
	CurveParasSerialize(QCustomPlot* p );

	///保存设置到数据流
	void saveSetting(QDataStream* data);

	///从数据流中加载设置
	void loadSetting(QDataStream* data);

private:

	//plot	
	///将轴设置保存到数据流中
	void	SerializeAxisSetting( QDataStream& out, AxisSetting a );

	///将数据流中的设置信息应用到轴上
	void	DeserializeAxisSetting( QDataStream& in, AxisSetting& a );

	//curve
	///获得曲线的样式属性
	void GetGraphInfo( QCPCurve* p, CurveSetting& settings );

	///设置曲线的样式属性
	void SetGraphInfo( QCPCurve* p, CurveSetting& settings );

private:
	///曲线视图
	QCustomPlot*		customPlot;			
};


#endif