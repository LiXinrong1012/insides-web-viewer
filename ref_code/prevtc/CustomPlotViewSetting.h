#ifndef CustomPlotViewSetting_H
#define CustomPlotViewSetting_H

#include <Qt>
#include <QString>
#include <QFont>
#include <QColor>
#include <QDataStream>

#include "qcustomplot/qcustomplot.h"

//通用设置：
struct AxisGeneralSetting
{
	//图名
	QString	 strChartTitle;

	//字体
	QFont 	 fontChartTitle;

	//legend字体
	QFont	fontLegendTitle;

	//颜色
	QColor   colorChartTitle;

	//是否显示Legend
	bool	 bShowLegend;

	//是否显示移动值
	bool	 bShowMotion;

	//是否是系统管理legend位置
	QCPLayoutInset::InsetPlacement	 insetPlacement;

	//legend 的 rect
	QRectF		insetRectF;

	//显示位置
	Qt::Alignment	AlignLegendhorizontal;
	Qt::Alignment	AlignLegendvertical;

	///默认构造函数
	AxisGeneralSetting()
	{
		 strChartTitle		= "Chart Title";
		 fontChartTitle		= QFont( QString("Microsoft YaHei"));
		 colorChartTitle	= QColor( Qt::black );
		 bShowLegend		= false;
		 insetPlacement		= QCPLayoutInset::ipBorderAligned;
		 insetRectF			= QRectF(0.6,0.6,0.4,0.4);
		 AlignLegendhorizontal= Qt::AlignRight;
		 AlignLegendvertical  = Qt::AlignBottom;
	}

	AxisGeneralSetting& operator = ( const AxisGeneralSetting& info )
	{
		strChartTitle			= info.strChartTitle;			
		fontChartTitle			= info.fontChartTitle;			
		colorChartTitle			= info.colorChartTitle;			
		bShowLegend				= info.bShowLegend;	
		insetPlacement			= info.insetPlacement;
		insetRectF				= info.insetRectF;
		AlignLegendhorizontal	= info.AlignLegendhorizontal;	
		AlignLegendvertical		= info.AlignLegendvertical;		

		return* this;
	}

	///保存到数据流
	QDataStream& save(QDataStream& out)const;

	///从数据流中加载
	QDataStream& load(QDataStream& in);
};


/*!
	@brief   坐标轴属性类
	@date    2015.6.29
	@author  Jerry
*/
struct AxisSetting
{
	//显示坐标网格
	bool		bShowGrid;

	//网格颜色
	QColor		colorGrid;

	//显示坐标坐标
	bool		bShowAxis;

	//坐标颜色
	QColor		colorAxis;

	//坐标Title名称
	QString		strAxisTitle;

	//坐标Title字体
	QFont		fontAxisTitle;

	//坐标Title颜色
	QColor		colorAxisTitle;

	//坐标Label字体
	QFont		fontAxisLabels;

	//坐标Label颜色
	QColor		colorAxisLabels;

	//数据显示精度
	int			nPrecision;

	//是否使用对数坐标；
	bool		bUseLogarithmic;

	///构造函数，初始化相关属性变量
	AxisSetting()
	{
		bShowGrid		= false;
		colorGrid		= QColor( Qt::black );
		bShowAxis		= true;
		colorAxis		= QColor( Qt::black );
		strAxisTitle	= QString( "AxisTitle" );
		fontAxisTitle   = QFont( QString("Microsoft YaHei"));
		colorAxisTitle	= QColor( Qt::black );
		fontAxisLabels	= QFont( QString("Microsoft YaHei"));
		colorAxisLabels	= QColor( Qt::black );

		nPrecision		= 2;
		bUseLogarithmic = false;
	}

	///保存到数据流
	QDataStream& save(QDataStream& out)const;

	///从数据流中读取
	QDataStream& load(QDataStream& in);
};


enum AxisType
{
	Axis_left_bottom,	
	Axis_top_right,		
	TotoalNum
};


/*!
	@brief   曲线的属性设置类
	@date    2015.6.29
	@author  Jerry
*/
struct CurveSetting
{
	//线颜色
	QColor			colorCurve;

	//线宽
	int				nCurveWidth;

	//坐标轴
	AxisType		axisType;

	//线型
	Qt::PenStyle	penStyle;

	//QCustomplot线型
	QCPCurve::LineStyle				curveLineStyle;

	//QCustomplot点型
	QCPScatterStyle::ScatterShape	scatterShape;

	//QCustomplot点大小
	int				shapeSize;

	///默认构造函数，初始化相关变量
	CurveSetting()
	{
		colorCurve		= QColor( Qt::black );
		nCurveWidth		= 1;
		axisType		= Axis_left_bottom;
		penStyle		= Qt::SolidLine;
		curveLineStyle	= (QCPCurve::LineStyle)0;
		scatterShape	= (QCPScatterStyle::ScatterShape)4;
		shapeSize = 6;
	}

	///保存到数据流
	QDataStream& save(QDataStream& out)const;

	///从数据流中读取
	QDataStream& load(QDataStream& in);
};


/*!
	@brief   曲线视图坐标轴相关设置
	@date    2015.6.29
	@author  Jerry
*/
struct CutsomPlotAxisSetting
{
	//General
	AxisGeneralSetting generalSetting;

	// axis settings
	//x1
	AxisSetting		   leftAxisSetting;
	
	//y1
	AxisSetting		   bottomAxisSetting;
	
	//x2
	AxisSetting		   topAxisSetting;
	
	//y2
	AxisSetting		   rightAxisSetting;
	
	// Curve settings
	QList<CurveSetting> curvesSetting;
	
	///保存到数据流
	QDataStream& save(QDataStream& out)const;

	///从数据流中读取
	QDataStream& load(QDataStream& in);
};

///将setting中保存的属性应用到曲线视图
void Setting2Plot(const CutsomPlotAxisSetting& s,QCustomPlot* plot );

///将曲线视图中的属性保存到setting
void Plot2Setting(QCustomPlot* plot,CutsomPlotAxisSetting& s);

///将坐标轴的相关属性保存到setting
void AxisPlot2Setting(const QCPAxis* pAxis, AxisSetting& settings );

///将setting中的属性保存到坐标轴
void AxisSetting2Plot( QCPAxis* pAxis,const AxisSetting& settings );

///将曲线中的属性保存到setting
bool Curve2Setting(const QCPCurve* p, CurveSetting& settings );

///将setting中保存的属性更新到曲线
void Setting2Curve(QCustomPlot* customPlot, QCPCurve* p, const CurveSetting& settings );

#endif