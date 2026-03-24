#include "CurveParasSerialize.h"
#include "CurveSettingDialog.h"
#include "CurvePlotSettingDialog.h"
#include "qcustomplot/qcustomplot.h"
#include <QColor>
#include <QFont>

CurveParasSerialize::CurveParasSerialize( QDlgPlotSetting* plot, CurveSettingDialog* curve,QCustomPlot* p )
{
	if( (!plot) || (!curve) ||( !p)	)
		return;
	m_plot		= plot;
	m_pCurve	= curve;
	customPlot	= p;
}

CurveParasSerialize::~CurveParasSerialize()
{

}

void CurveParasSerialize::saveSetting( QDataStream* data )
{
//plot 
	CutsomPlotAxisSetting settings;
	m_plot->UpdatePlotSetting();
	m_plot->GetPlotSetting( settings );
	QDataStream out;
	out.setDevice( data->device() );
	out.setVersion(QDataStream::Qt_4_7);
	//general
	out<<settings.generalSetting.strChartTitle;
	SerializeFont( out,settings.generalSetting.fontChartTitle );
	SerializeColor( out,settings.generalSetting.colorChartTitle );

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

	for( int i = 0; i < customPlot->plottableCount(); i ++ )
	{
		CurveSetting s;
		QCPCurve* p = dynamic_cast<QCPCurve*>(customPlot->plottable( i ));
		if( !p )
			continue;
		GetGraphInfo( p, s );
		SerializeColor( out, s.colorCurve );
		out<<(int)(s.nCurveWidth);
		out<<(int)(s.axisType);
		out<<(int)(s.penStyle);
		out<<(int)(s.curveLineStyle);
		out<<(int)(s.scatterShape);
	}

}

void CurveParasSerialize::loadSetting( QDataStream* data )
{
//plot
	CutsomPlotAxisSetting settings;
	QDataStream in;

	in.setDevice( data->device() );
	in.setVersion(QDataStream::Qt_4_7);
	//general
	in>>settings.generalSetting.strChartTitle;
	DeserializeFont( in,settings.generalSetting.fontChartTitle );
	DeserializeColor( in,settings.generalSetting.colorChartTitle );

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
	
	m_plot->PlotSettings(settings);
//curve
		
	for( int i = 0; i < customPlot->plottableCount(); i ++ )
	{
		CurveSetting s;

		DeserializeColor( in, s.colorCurve );
		in>>s.nCurveWidth;
		int nx,nPen,nCurve,nScatter;
		in>>nx;	
		in>>nPen;
		in>>nCurve;
		in>>nScatter;
		s.axisType = (AxisType)nx;
		s.penStyle  =  (Qt::PenStyle)nPen;
		s.curveLineStyle= (QCPCurve::LineStyle	)nCurve;
		s.scatterShape = (QCPScatterStyle::ScatterShape)nScatter;

		//QCPAbstractPlottable* plotable = customPlot->plottable( i );
		QCPCurve* p = dynamic_cast<QCPCurve*>(customPlot->plottable( i ));
		if( p )
			SetGraphInfo( p,s );
	}
	customPlot->replot( QCustomPlot::rpImmediate );
	
}

void CurveParasSerialize::SerializeFont( QDataStream& out, QFont f )
{
	out<< f.family();
	out<< f.pointSize();
}

void CurveParasSerialize::DeserializeFont( QDataStream& in, QFont& f )
{
	QString strFaily;
	int nPs;
	in>>strFaily;
	in>>nPs;
	f.setFamily( strFaily );
	f.setPointSize( nPs );
}

void CurveParasSerialize::SerializeColor( QDataStream& out, QColor c )
{
	out<< c.alpha();
	out<<c.red();
	out<<c.green();
	out<<c.blue();
}

void CurveParasSerialize::DeserializeColor( QDataStream& in, QColor& c )
{
	int a,r,g,b;
	in>>a;
	in>>r;
	in>>g;
	in>>b;
	c.setAlpha(a);
	c.setRed(r);
	c.setGreen(g);
	c.setBlue(b);
}


void CurveParasSerialize::SerializeAxisSetting( QDataStream& out, AxisSetting a )
{
	out<<a.bShowGrid;
	out<<a.bShowAxis;
	SerializeColor( out,a.colorGrid );
	SerializeColor( out,a.colorAxis );
	out<<a.strAxisTitle;
	SerializeFont( out,a.fontAxisTitle );
	SerializeColor( out, a.colorAxisTitle );
	SerializeFont( out,a.fontAxisLabels );
	SerializeColor( out,a.colorAxisLabels );
	out<<a.nPrecision;
	out<<a.bUseLogarithmic;
}

void CurveParasSerialize::DeserializeAxisSetting( QDataStream& in, AxisSetting& a )
{
	in>>a.bShowGrid;
	in>>a.bShowAxis;
	DeserializeColor( in,a.colorGrid );
	DeserializeColor( in,a.colorAxis );
	in>>a.strAxisTitle;
	DeserializeFont( in,a.fontAxisTitle );
	DeserializeColor( in, a.colorAxisTitle );
	DeserializeFont( in,a.fontAxisLabels );
	DeserializeColor( in,a.colorAxisLabels );
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
}
