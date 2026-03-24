#include "CustomPlotViewSetting.h"


QDataStream& AxisGeneralSetting::save( QDataStream& out ) const
{
	const AxisGeneralSetting& generalSetting=*this;
	qint32 version=1;
	out<<version;
	// version 1
	out<<generalSetting.strChartTitle;
	out<<generalSetting.fontChartTitle;
	out<<generalSetting.fontLegendTitle;
	out<<generalSetting.colorChartTitle;

	out<<generalSetting.bShowLegend;
	out<<generalSetting.bShowMotion;
	out<<generalSetting.insetPlacement;
	out<<generalSetting.insetRectF;
	out<<(qint32)generalSetting.AlignLegendhorizontal;
	out<<(qint32)generalSetting.AlignLegendvertical;
	// end version 1

	return out;
}

QDataStream& AxisGeneralSetting::load( QDataStream& in )
{
	qint32 version;
	in>>version;
	if(version==1)
	{
		in>>strChartTitle;
		in>>fontChartTitle;
		in>>fontLegendTitle;
		in>>colorChartTitle;

		in>>bShowLegend;
		in>>bShowMotion;
		int p;
		in>>p;
		insetPlacement = (QCPLayoutInset::InsetPlacement)p;
		in>>insetRectF;
		qint32 nh,nv;
		in>>nh;
		in>>nv;
		AlignLegendhorizontal = (Qt::Alignment)nh;
		AlignLegendvertical = (Qt::Alignment)nv;
	}

	return in;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
QDataStream& AxisSetting::save( QDataStream& out ) const
{
	qint32 version=1;
	out<<version;
	// version 1
	out<<bShowGrid;
	out<<bShowAxis;
	out<<colorGrid;
	out<<colorAxis;
	out<<strAxisTitle;

	out<<fontAxisTitle;
	out<<colorAxisTitle;
	out<<fontAxisLabels;
	out<<colorAxisLabels;

	out<<nPrecision;
	out<<bUseLogarithmic;
	// end version 1
	return out;
}

QDataStream& AxisSetting::load( QDataStream& in )
{
	qint32 version;
	in>>version;
	if(version==1)
	{
		in>>bShowGrid;
		in>>bShowAxis;
		in>>colorGrid;
		in>>colorAxis;
		in>>strAxisTitle;

		in>>fontAxisTitle
			>>colorAxisTitle
			>>fontAxisLabels
			>>colorAxisLabels;
		in>>nPrecision;
		in>>bUseLogarithmic;
	}

	return in;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
QDataStream& CurveSetting::save( QDataStream& out ) const
{
	qint32 version=1;
	// version 1
	out<<version;
	out<<colorCurve;
	out<<(qint32)(nCurveWidth);
	out<<(qint32)(axisType);
	out<<(qint32)(penStyle);
	out<<(qint32)(curveLineStyle);
	out<<(qint32)(scatterShape);
	out<<shapeSize;
	// end version 1
	return out;
}

QDataStream& CurveSetting::load( QDataStream& in )
{
	qint32 version;
	in>>version;
	if(version==1)
	{
		in>>colorCurve;
		in>>nCurveWidth;
		qint32 nx,nPen,nCurve,nScatter,scatterSize;
		in>>nx;	
		in>>nPen;
		in>>nCurve;
		in>>nScatter;
		in>>scatterSize;
		axisType = (AxisType)nx;
		penStyle  =  (Qt::PenStyle)nPen;
		curveLineStyle= (QCPCurve::LineStyle)nCurve;
		scatterShape = (QCPScatterStyle::ScatterShape)nScatter;
		shapeSize = scatterSize;
	}

	return in;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
QDataStream& CutsomPlotAxisSetting::save( QDataStream& out ) const
{
	qint32 version=1;
	out<<version;
	// version 1
	generalSetting.save(out);
	leftAxisSetting.save(out);
	bottomAxisSetting.save(out);
	topAxisSetting.save(out);
	rightAxisSetting.save(out);

	out<<(qint32)curvesSetting.size();
	foreach(const CurveSetting& c, curvesSetting)
		c.save(out);
	// end version 1

	return out;
}

QDataStream& CutsomPlotAxisSetting::load( QDataStream& in )
{
	qint32 version;
	in>>version;
	if(version==1)
	{
		generalSetting.load(in);
		leftAxisSetting.load(in);
		bottomAxisSetting.load(in);
		topAxisSetting.load(in);
		rightAxisSetting.load(in);

		qint32 curveCount;
		in>>curveCount;
		for(int i=0;i<curveCount;++i){
			CurveSetting c;
			c.load(in);
			curvesSetting.push_back(c);
		}
	}

	return in;
}

void AxisSetting2Plot( QCPAxis* pAxis,const AxisSetting& settings )
{
	if( !pAxis )
		return;
	pAxis->setVisible( settings.bShowAxis );
	pAxis->setLabelFont( settings.fontAxisTitle );
	pAxis->setLabelColor( settings.colorAxisTitle );
	pAxis->setLabel( settings.strAxisTitle );

	pAxis->setTickLabelFont( settings.fontAxisLabels );
	pAxis->setTickLabelColor( settings.colorAxisLabels );
	pAxis->setBasePen( settings.colorAxis );

	if( settings.bUseLogarithmic )
		pAxis->setScaleType( QCPAxis::stLogarithmic );
	else
		pAxis->setScaleType( QCPAxis::stLinear );

	pAxis->setNumberPrecision( settings.nPrecision );
	QCPGrid* pGrid = pAxis->grid();
	if( !pGrid )
		return;
	pGrid->setVisible( settings.bShowGrid );
	pGrid->setPen( settings.colorGrid );
}

void AxisPlot2Setting(const QCPAxis* pAxis, AxisSetting& settings )
{
	if( !pAxis )
		return;
	settings.bShowAxis = pAxis->visible();
	settings.fontAxisTitle = pAxis->labelFont();
	settings.colorAxisTitle = pAxis->labelColor();
	settings.strAxisTitle = pAxis->label();

	settings.fontAxisLabels = pAxis->tickLabelFont();
	settings.colorAxisLabels = pAxis->tickLabelColor();
	settings.colorAxis = pAxis->basePen().color();

	if( pAxis->scaleType() == QCPAxis::stLogarithmic )
		settings.bUseLogarithmic = true;
	else
		settings.bUseLogarithmic = false;
	settings.nPrecision = pAxis->numberPrecision();

	QCPGrid* pGrid = pAxis->grid();
	if( !pGrid )
		return;
	settings.bShowGrid = pGrid->visible();
	settings.colorGrid = pGrid->pen().color();
} 

void Setting2Plot(const CutsomPlotAxisSetting& s,QCustomPlot* customPlot )
{
	QCPLayoutElement* pItem =	customPlot->plotLayout()->elementAt(0);
	QCPPlotTitle* pTitle = dynamic_cast<QCPPlotTitle*>(pItem);
	if( !pTitle && !s.generalSetting.strChartTitle.isEmpty())
	{
		customPlot->plotLayout()->insertRow(0);
		pTitle = new QCPPlotTitle(customPlot, s.generalSetting.strChartTitle );

		pTitle->setFont( s.generalSetting.fontChartTitle );
		pTitle->setTextColor( s.generalSetting.colorChartTitle );
		customPlot->plotLayout()->addElement(0, 0, pTitle );
	}
	else if(pTitle)
	{
		pTitle->setText( s.generalSetting.strChartTitle );
		pTitle->setTextColor( s.generalSetting.colorChartTitle );
		pTitle->setFont( s.generalSetting.fontChartTitle );
		/*if(pTitle->text().isEmpty())
		{
			int testInt = customPlot->plotLayout()->elementCount();
			bool testB = customPlot->plotLayout()->removeAt(0);
			int testInt2 = customPlot->plotLayout()->elementCount();
			customPlot->replot();
		}*/
	}
	//legend
	customPlot->legend->setVisible( s.generalSetting.bShowLegend );
	customPlot->legend->setFont(s.generalSetting.fontLegendTitle);

	int size = customPlot->legend->font().pointSize()*1.3;
	customPlot->legend->setIconSize(size,size);

	customPlot->axisRect()->insetLayout()->setInsetPlacement(0,s.generalSetting.insetPlacement);
	customPlot->axisRect()->insetLayout()->setInsetRect(0,s.generalSetting.insetRectF);

	QFont selectedFont = customPlot->legend->selectedFont();
	selectedFont.setPointSize(customPlot->legend->font().pointSize());
	customPlot->legend->setSelectedFont(selectedFont);
	customPlot->axisRect()->insetLayout()->setInsetAlignment(0, s.generalSetting.AlignLegendhorizontal|s.generalSetting.AlignLegendvertical );
	//axis
	//left
	if( customPlot->xAxis )
		AxisSetting2Plot( customPlot->xAxis, s.leftAxisSetting );
	if( customPlot->yAxis )
		AxisSetting2Plot( customPlot->yAxis, s.bottomAxisSetting );
	if( customPlot->xAxis2 )
		AxisSetting2Plot( customPlot->xAxis2, s.topAxisSetting );
	if( customPlot->yAxis2 )
		AxisSetting2Plot( customPlot->yAxis2, s.rightAxisSetting );

	//curve
	qint32 curveSize=customPlot->plottableCount();
	for( int i = 0; i < curveSize; i ++ )
	{
		if(s.curvesSetting.isEmpty())
			break;
		QCPCurve* p = dynamic_cast<QCPCurve*>(customPlot->plottable( i ));
		if( !p )
			continue;
		Setting2Curve(customPlot,p,s.curvesSetting[i%s.curvesSetting.count()] );
	}
	customPlot->replot( QCustomPlot::rpImmediate );
}

void Plot2Setting( QCustomPlot* customPlot,CutsomPlotAxisSetting& m_settings)
{
	//general
	QCPLayoutElement* pItem =	customPlot->plotLayout()->elementAt(0);
	QCPPlotTitle* pTitle = dynamic_cast<QCPPlotTitle*>(pItem);
	if( !pTitle )
	{
		m_settings.generalSetting.strChartTitle = "";
		m_settings.generalSetting.fontChartTitle = QFont();
		m_settings.generalSetting.colorChartTitle = Qt::black;

	}
	else
	{
		m_settings.generalSetting.strChartTitle = pTitle->text();
		m_settings.generalSetting.fontChartTitle = pTitle->font();
		m_settings.generalSetting.colorChartTitle = pTitle->textColor();

	}
	//legend
	m_settings.generalSetting.bShowLegend = customPlot->legend->visible();
	Qt::Alignment e = customPlot->axisRect()->insetLayout()->insetAlignment(0);
	m_settings.generalSetting.AlignLegendhorizontal = e&(~Qt::AlignVertical_Mask);
	m_settings.generalSetting.AlignLegendvertical = e&(~Qt::AlignHorizontal_Mask);

	m_settings.generalSetting.fontLegendTitle =customPlot->legend->font();

	m_settings.generalSetting.insetPlacement = customPlot->axisRect()->insetLayout()->insetPlacement(0);
	m_settings.generalSetting.insetRectF = customPlot->axisRect()->insetLayout()->insetRect(0);

	//	m_settings.generalSetting.bShowLegend = ;

	//	customPlot->legend->setVisible( s.generalSetting.bShowLegend );
	//	customPlot->axisRect()->insetLayout()->setInsetAlignment(0, s.generalSetting.AlignLegendhorizontal|s.generalSetting.AlignLegendvertical );
	//axis
	//left
	if( customPlot->xAxis )
		AxisPlot2Setting( customPlot->xAxis, m_settings.leftAxisSetting );
	if( customPlot->yAxis )
		AxisPlot2Setting( customPlot->yAxis, m_settings.bottomAxisSetting );
	if( customPlot->xAxis2 )
		AxisPlot2Setting( customPlot->xAxis2, m_settings.topAxisSetting );
	if( customPlot->yAxis2 )
		AxisPlot2Setting( customPlot->yAxis2, m_settings.rightAxisSetting );

	//curve
	qint32 curveSize=customPlot->plottableCount();
	for( int i = 0; i < curveSize; i ++ )
	{
		CurveSetting s;
		QCPCurve* p = dynamic_cast<QCPCurve*>(customPlot->plottable( i ));
		if( !p )
			continue;
		Curve2Setting( p, s );
		m_settings.curvesSetting.push_back(s);
	}
}

bool Curve2Setting(const QCPCurve* p, CurveSetting& settings )
{
	if( !p )
		return false;

	settings.colorCurve = p->pen().color();
	settings.penStyle = p->pen().style();
	settings.nCurveWidth = p->pen().width();
	//axistype
	QCPAxis* pKey = p->keyAxis();
	QCPAxis* pValue = p->valueAxis();

	if( (pKey->axisType() == QCPAxis::atLeft) &&( pValue->axisType() == QCPAxis::atBottom )  )
		settings.axisType = Axis_left_bottom;
	if( (pKey->axisType() == QCPAxis::atRight) &&( pValue->axisType() == QCPAxis::atTop ) )
		settings.axisType = Axis_top_right;

	settings.curveLineStyle = p->lineStyle();
	settings.scatterShape = p->scatterStyle().shape();
	settings.shapeSize = p->scatterStyle().size();
	return true;
}

void Setting2Curve(QCustomPlot* customPlot, QCPCurve* p, const CurveSetting& settings )
{
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