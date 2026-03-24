#include "CurveParasSerialize.h"
#include "CurveSettingDialog.h"
#include "CurvePlotSettingDialog.h"
#include "qcustomplot/qcustomplot.h"
#include <QColor>
#include <QFont>

CurveParasSerialize::CurveParasSerialize(QCustomPlot* p )
{
	customPlot	= p;
}

void CurveParasSerialize::saveSetting( QDataStream* data )
{
	//plot 
	CutsomPlotAxisSetting settings;
	Plot2Setting(customPlot,settings);
	QDataStream out;
	out.setDevice( data->device() );
	//general
	out<<settings.generalSetting.strChartTitle;
	out<<settings.generalSetting.fontChartTitle;
	out<<settings.generalSetting.fontLegendTitle;
	out<<settings.generalSetting.colorChartTitle;

	out<<settings.generalSetting.bShowLegend;
	out<<settings.generalSetting.bShowMotion;
	out<<settings.generalSetting.AlignLegendhorizontal;
	out<<settings.generalSetting.AlignLegendvertical;

	//axise
	SerializeAxisSetting( out,settings.leftAxisSetting );
	SerializeAxisSetting( out,settings.rightAxisSetting );
	SerializeAxisSetting( out,settings.topAxisSetting );
	SerializeAxisSetting( out,settings.bottomAxisSetting );

	//curve
	qint32 curveSize=customPlot->plottableCount();
	out<<curveSize;
	for( int i = 0; i < curveSize; i ++ )
	{
		CurveSetting s;
		QCPCurve* p = dynamic_cast<QCPCurve*>(customPlot->plottable( i ));
		if( !p )
			continue;
		GetGraphInfo( p, s );
		out<<s.colorCurve;
		out<<(int)(s.nCurveWidth);
		out<<(int)(s.axisType);
		out<<(int)(s.penStyle);
		out<<(int)(s.curveLineStyle);
		out<<(int)(s.scatterShape);
		out<<s.shapeSize;
	}
}

void CurveParasSerialize::loadSetting( QDataStream* data )
{
//plot
	CutsomPlotAxisSetting settings;
	QDataStream in;

	in.setDevice( data->device() );
	//general
	in>>settings.generalSetting.strChartTitle;
	in>>settings.generalSetting.fontChartTitle;
	in>>settings.generalSetting.fontLegendTitle;
	in>>settings.generalSetting.colorChartTitle;

	in>>settings.generalSetting.bShowLegend;
	in>>settings.generalSetting.bShowMotion;
	int nh,nv;
	in>>nh;
	in>>nv;
	settings.generalSetting.AlignLegendhorizontal = (Qt::Alignment)nh;
	settings.generalSetting.AlignLegendvertical = (Qt::Alignment)nv;

	//axise
	DeserializeAxisSetting( in,settings.leftAxisSetting );
	DeserializeAxisSetting( in,settings.rightAxisSetting );
	DeserializeAxisSetting( in,settings.topAxisSetting );
	DeserializeAxisSetting( in,settings.bottomAxisSetting );
	
	Setting2Plot(settings,customPlot);

	//curve
	qint32 curveSize;
	in>>curveSize;
	for( int i = 0; i < curveSize; i ++ )
	{
		CurveSetting s;

		in>>s.colorCurve;
		in>>s.nCurveWidth;
		int nx,nPen,nCurve,nScatter,scatterSize;
		in>>nx;	
		in>>nPen;
		in>>nCurve;
		in>>nScatter;
		in>>scatterSize;
		s.axisType = (AxisType)nx;
		s.penStyle  =  (Qt::PenStyle)nPen;
		s.curveLineStyle= (QCPCurve::LineStyle	)nCurve;
		s.scatterShape = (QCPScatterStyle::ScatterShape)nScatter;
		s.shapeSize = scatterSize;
		//QCPAbstractPlottable* plotable = customPlot->plottable( i );
		if(i>=customPlot->plottableCount())
			continue;

		QCPCurve* p = dynamic_cast<QCPCurve*>(customPlot->plottable( i ));
		if( p )
			SetGraphInfo( p,s );
	}
	customPlot->replot( QCustomPlot::rpImmediate );
}

void CurveParasSerialize::SerializeAxisSetting( QDataStream& out, AxisSetting a )
{
	out<<a.bShowGrid;
	out<<a.bShowAxis;
	out<<a.colorGrid;
	out<<a.colorAxis;
	out<<a.strAxisTitle;

	out<<a.fontAxisTitle;
	out<<a.colorAxisTitle;
	out<<a.fontAxisLabels;
	out<<a.colorAxisLabels;

	out<<a.nPrecision;
	out<<a.bUseLogarithmic;
}

void CurveParasSerialize::DeserializeAxisSetting( QDataStream& in, AxisSetting& a )
{
	in>>a.bShowGrid;
	in>>a.bShowAxis;
	in>>a.colorGrid
		>>a.colorAxis;
	in>>a.strAxisTitle;

	in>>a.fontAxisTitle
		>>a.colorAxisTitle
		>>a.fontAxisLabels
		>>a.colorAxisLabels;
	in>>a.nPrecision;
	in>>a.bUseLogarithmic;
}

void CurveParasSerialize::GetGraphInfo( QCPCurve* p, CurveSetting& settings )
{
	if( !p )
		return;

	settings.colorCurve = p->pen().color();
	settings.nCurveWidth = p->pen().width();
	//axistype
	QCPAxis* pKey = p->keyAxis();
	QCPAxis* pValue = p->valueAxis();

	if( (pKey->axisType() == QCPAxis::atLeft) &&( pValue->axisType() == QCPAxis::atBottom )  )
		settings.axisType = Axis_left_bottom;
	if( (pKey->axisType() == QCPAxis::atRight) &&( pValue->axisType() == QCPAxis::atTop ) )
		settings.axisType = Axis_top_right;

	settings.penStyle = p->pen().style();
	settings.curveLineStyle = p->lineStyle();
	settings.scatterShape = p->scatterStyle().shape();
	settings.shapeSize = p->scatterStyle().size();
}

void CurveParasSerialize::SetGraphInfo( QCPCurve* p, CurveSetting& settings )
{
	if( !p )
		return;
	QPen pen = p->pen();
	pen.setColor( settings.colorCurve );
	pen.setStyle( settings.penStyle );
	pen.setWidth( settings.nCurveWidth );

	p->setPen( pen );
	switch( settings.axisType )
	{
	case Axis_left_bottom:
		p->setKeyAxis( customPlot->xAxis );
		p->setValueAxis( customPlot->yAxis );
		break;
	case Axis_top_right:
		p->setKeyAxis( customPlot->xAxis2 );
		p->setValueAxis( customPlot->yAxis2 );
		break;
	}
	p->setLineStyle( settings.curveLineStyle );
	p->setScatterStyle( settings.scatterShape );
	QCPScatterStyle s = p->scatterStyle();
	s.setSize(settings.shapeSize);
	p->setScatterStyle(s);
}
