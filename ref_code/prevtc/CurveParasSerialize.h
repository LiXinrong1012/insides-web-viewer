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
	@date    2015.6.26
	@author  Jerry
*/
class CurveParasSerialize
{
public:
	CurveParasSerialize(QCustomPlot* p );

	///保存配置
	void saveSetting(QDataStream* data);

	///加载配置
	void loadSetting(QDataStream* data);

private:

	//plot	

	///将轴设置保存到数据流中
	void	SerializeAxisSetting( QDataStream& out, AxisSetting a );

	///将数据流中的轴设置部分应用到轴
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