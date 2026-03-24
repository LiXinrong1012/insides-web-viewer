#ifndef CustomPlotViewSetting_H
#define CustomPlotViewSetting_H

#include <Qt>
#include <QString>
#include <QFont>
#include <QColor>
#include <QDataStream>

#include "qcustomplot/qcustomplot.h"

/*!
	@brief  通用设置
	@date   2015.7.3
	@author Jerry
*/
struct AxisGeneralSetting
{
	///曲线标题名
	QString	 strChartTitle;

	///曲线标题的字体
	QFont 	 fontChartTitle;

	///曲线标题颜色
	QColor   colorChartTitle;

	///legend字体
	QFont	fontLegendTitle;

	///是否显示Legend
	bool	 bShowLegend;
	
	///是否显示移动值
	bool	 bShowMotion;

	///是否是系统管理legend位置
	QCPLayoutInset::InsetPlacement	 insetPlacement;

	///legend 的 rect
	QRectF		insetRectF;

	///水平显示位置
	Qt::Alignment	AlignLegendhorizontal;

	///竖直显示位置
	Qt::Alignment	AlignLegendvertical;

	///构造函数，将变量做必要初始化
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

	///将全部变是保存到数据流
	QDataStream& save(QDataStream& out)const;

	///从数据流中读取变量
	QDataStream& load(QDataStream& in);
};


/*!
	@brief   坐标轴设置项构造函数
	@date    2015.7.3
	@author  Jerry
*/
struct AxisSetting
{
	///是否显示坐标网格
	bool		bShowGrid;
	
	///网格颜色
	QColor		colorGrid;
	
	///是否显示坐标轴坐标
	bool		bShowAxis;
	
	///坐标轴颜色
	QColor		colorAxis;
	
	///坐标轴标题名称
	QString		strAxisTitle;
	
	///坐标轴标题字体
	QFont		fontAxisTitle;
	
	///坐标轴标题颜色
	QColor		colorAxisTitle;
	
	///坐标轴Label字体
	QFont		fontAxisLabels;
	
	///坐标轴Label颜色
	QColor		colorAxisLabels;
	
	///数据显示精度
	int			nPrecision;
	
	///是否使用对数坐标；
	bool		bUseLogarithmic;
	
	///默认构造函数，对成员变量做必要的初始化
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

	///将所有成员变量保存到数据流
	QDataStream& save(QDataStream& out)const;

	///将数据流中存储的变量值读取到变量
	QDataStream& load(QDataStream& in);
};

/*!
	@brief   用于判断显示哪些坐标轴
	@date    2015.7.3
	@author  Jerry
*/
enum AxisType
{
	///显示左侧与下侧的坐标轴
	Axis_left_bottom,	

	///显示顶部与右侧的坐标轴
	Axis_top_right,		

	///显示所有坐标轴
	TotoalNum
};

/*!
	@brief   曲线设置数据结构
	@date    2015.7.3
	@author  Jerry
*/
struct CurveSetting
{
	///曲线颜色
	QColor			colorCurve;
	
	///曲线宽度
	int				nCurveWidth;
	
	///显示什么坐标轴坐标轴
	AxisType		axisType;
	
	///线型
	Qt::PenStyle	penStyle;
	
	///QCustomplot线型
	QCPCurve::LineStyle				curveLineStyle;
	
	///QCustomplot点型
	QCPScatterStyle::ScatterShape	scatterShape;
	
	///QCustomplot点大小
	int				shapeSize;

	///默认构造函数，对成员变量进行必要初始化
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

	///将曲线设置中的变量保存到数据流
	QDataStream& save(QDataStream& out)const;

	///将数据流中保存的变量读取到界面 
	QDataStream& load(QDataStream& in);
};

/*!
	@brief   曲线视图总的设置类
	@date    2015.7.3
	@author  Jerry
*/
struct CutsomPlotAxisSetting
{
	///General
	AxisGeneralSetting generalSetting;
	// axis settings
	
	///x1
	AxisSetting		   leftAxisSetting;

	///y1
	AxisSetting		   bottomAxisSetting;

	///x2
	AxisSetting		   topAxisSetting;

	///y2
	AxisSetting		   rightAxisSetting;
	
	/// Curve settings
	QList<CurveSetting> curvesSetting;
	
	///将曲线视图设置保存到数据流
	QDataStream& save(QDataStream& out)const;

	///从数据流中读取设置项到曲线视图
	QDataStream& load(QDataStream& in);
};

///将setting中存储的设置项应用到视图界面
void Setting2Plot(const CutsomPlotAxisSetting& s,QCustomPlot* plot );

///将视图中的设置属性读取到setting保存
void Plot2Setting(QCustomPlot* plot,CutsomPlotAxisSetting& s);

///将坐标轴属性保存到setting
void AxisPlot2Setting(const QCPAxis* pAxis, AxisSetting& settings );

///将保存到setting的设置应用到视图
void AxisSetting2Plot( QCPAxis* pAxis,const AxisSetting& settings );

///将曲线的属性保存到setting
bool Curve2Setting(const QCPCurve* p, CurveSetting& settings );

///将settingk存储的属性应用到曲线
void Setting2Curve(QCustomPlot* customPlot, QCPCurve* p, const CurveSetting& settings );

#endif