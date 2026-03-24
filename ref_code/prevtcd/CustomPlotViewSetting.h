#ifndef CustomPlotViewSetting_H
#define CustomPlotViewSetting_H

#include <Qt>
#include <QString>
#include <QFont>
#include <QColor>

#include "qcustomplot/qcustomplot.h"

//通用设置：
struct AxisGeneralSetting
{
	//图名
	QString	 strChartTitle;
	//字体
	QFont 	 fontChartTitle;
	//颜色
	QColor   colorChartTitle;
	//是否显示Legend
	bool	 bShowLegend;
	//是否显示移动值
	bool	 bShowMotion;
	//显示位置
	Qt::Alignment	AlignLegendhorizontal;
	Qt::Alignment	AlignLegendvertical;


	AxisGeneralSetting()
	{
		 strChartTitle		= "Chart Title";
		 fontChartTitle		= QFont( QString("Microsoft YaHei"));
		 colorChartTitle	= QColor( Qt::black );
		 bShowLegend		= false;
		 AlignLegendhorizontal= Qt::AlignRight;
		 AlignLegendvertical  = Qt::AlignBottom;
	}


	AxisGeneralSetting& operator = ( const AxisGeneralSetting& info )
	{
			strChartTitle			= info.strChartTitle;			
			fontChartTitle			= info.fontChartTitle;			
			colorChartTitle			= info.colorChartTitle;			
			bShowLegend				= info.bShowLegend;				
			AlignLegendhorizontal	= info.AlignLegendhorizontal;	
			AlignLegendvertical		= info.AlignLegendvertical;		

		return* this;
	}
};


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

	AxisSetting& operator = ( const AxisSetting& info )
	{
			bShowGrid		= info.bShowGrid;		
			colorGrid		= info.colorGrid;		
			bShowAxis		= info.bShowAxis;		
			colorAxis		= info.colorAxis;		
			strAxisTitle	= info.strAxisTitle;	
			fontAxisTitle   = info.fontAxisTitle;   
			colorAxisTitle	= info.colorAxisTitle;	
			fontAxisLabels	= info.fontAxisLabels;	
			colorAxisLabels	= info.colorAxisLabels;	

			nPrecision		= info.nPrecision;		
			bUseLogarithmic	= info.bUseLogarithmic;	
		return* this;
	}
};


enum AxisType
{
	Axis_left_bottom,	
	Axis_top_right,		
	TotoalNum
};

struct CurveSetting
{
	//线颜色、
	QColor			colorCurve;
	//线宽、
	int				nCurveWidth;
	//坐标轴
	AxisType		axisType;
	//线型
	Qt::PenStyle	penStyle;
	//QCustomplot线型
	QCPCurve::LineStyle				curveLineStyle;
	//QCustomplot点型
	QCPScatterStyle::ScatterShape	scatterShape;

	CurveSetting()
	{
		colorCurve		= QColor( Qt::black );
		nCurveWidth		= 1;
		axisType		= Axis_left_bottom;
		penStyle		= Qt::SolidLine;
		curveLineStyle	= (QCPCurve::LineStyle)0;
		scatterShape	= (QCPScatterStyle::ScatterShape)4;
	}

	CurveSetting& operator = ( const CurveSetting& info )
	{
			colorCurve		= info.colorCurve;		
			nCurveWidth		= info.nCurveWidth;		
			axisType		= info.axisType;		
			penStyle		= info.penStyle;		
			curveLineStyle	= info.curveLineStyle;	
			scatterShape	= info.scatterShape	;

			return* this;
	}
};
// m_pParaWdgts->addWidget( pBottomWdgt );
// m_pParaWdgts->addWidget( pRightWdgt );	
// m_pParaWdgts->addWidget( pTopWdgt );	
// m_pParaWdgts->addWidget( pLeftWdgt );
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
	
	
	
	//curve setting
	//CurveSetting	   curveSetting;
	
	CutsomPlotAxisSetting& operator = ( const CutsomPlotAxisSetting& info )
	{
		generalSetting	= info.generalSetting;	
		leftAxisSetting	= info.leftAxisSetting;
		rightAxisSetting= info.rightAxisSetting;
		topAxisSetting	= info.topAxisSetting;
		bottomAxisSetting= info.bottomAxisSetting;


//		curveSetting	 = info.curveSetting;	 
		return* this;
	}
};
#endif