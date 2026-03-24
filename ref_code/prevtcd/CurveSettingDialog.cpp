#include "CurveSettingDialog.h"
#include "qcustomplot/qcustomplot.h"

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QFontDialog>
#include <QFont>
#include <QPixmap>
#include <QPainter>
#include <QIcon>
#include <QDialogButtonBox>
#include <QFile>
#include <QDataStream>
#include <QDir>

#include "ui_curveSetting.h"

CurveSettingDialog::CurveSettingDialog( QCustomPlot* p,QWidget* parent /*= 0 */ )
{
	m_plot = p;
	
	m_pUiCurveSetting = new Ui::curveSetting;
	InitUI();

	updateCurves();
}

CurveSettingDialog::~CurveSettingDialog()
{

}


void CurveSettingDialog::SetCurveSetting( const CurveSetting& settings )
{
	//curve setting
	m_pUiCurveSetting->btnCurveColor->setIcon( CreateBtnColorIcon( settings.colorCurve ) );
	m_pUiCurveSetting->spinBoxWidth->setValue( settings.nCurveWidth );
	m_pUiCurveSetting->cmbPenStyle->setCurrentIndex( (int)settings.penStyle );
	m_pUiCurveSetting->cmbLineStyle->setCurrentIndex( (int)settings.curveLineStyle );
	m_pUiCurveSetting->cmbScatterShape->setCurrentIndex( (int)settings.scatterShape );
	m_pUiCurveSetting->cmbaxis->setCurrentIndex( (int)settings.axisType );
	m_settings = settings;
}

void CurveSettingDialog::GetCurveSetting( CurveSetting& settings )
{
	settings.colorCurve = m_settings.colorCurve;
	settings.nCurveWidth= m_pUiCurveSetting->spinBoxWidth->value();
	settings.penStyle = (Qt::PenStyle)(m_pUiCurveSetting->cmbPenStyle->currentIndex());
	settings.curveLineStyle = (QCPCurve::LineStyle	)(m_pUiCurveSetting->cmbLineStyle->currentIndex());
	settings.scatterShape = (QCPScatterStyle::ScatterShape)(m_pUiCurveSetting->cmbScatterShape->currentIndex());
	settings.axisType = (AxisType)(m_pUiCurveSetting->cmbaxis->currentIndex());

}

void CurveSettingDialog::InitUI()
{
	QWidget* pWdgt = new QWidget;
	m_pUiCurveSetting->setupUi( pWdgt );

	m_pNavigation = new QTreeWidget;
	m_pNavigation->setMaximumWidth( 200 );
	m_pNavigation->setMinimumWidth( 100 );
	m_pNavigation->setHeaderHidden( true );	
	m_pNavigation->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	QHBoxLayout* pLayout = new QHBoxLayout();
	pLayout->addWidget( m_pNavigation );
	pLayout->addWidget( pWdgt );


	QFrame* pFrame = new QFrame;
	pFrame->setFrameShape( QFrame::HLine );

	QVBoxLayout* pMainLayout = new QVBoxLayout(this);
	pMainLayout->addLayout( pLayout );
	pMainLayout->addWidget( pFrame );
	setLayout( pMainLayout );
	

	QStringList strl,strPenstyle,strLineStyle,strScatter;
	strl << tr( "Left_bottom" )<< tr( "Top_right" );
	m_pUiCurveSetting->cmbaxis->addItems( strl );
	
	strPenstyle<< tr( "SolidLine" )<< tr( "DashLine" )<< tr( "DotLine" )<< tr( "DashDotLine" );
	strLineStyle << tr( "None" )<< tr( "Line" )<< tr( "StepLeft" )<< tr( "StepRight" )<< tr( "StepCenter" )<< tr( "Impulse" );
	strScatter<< tr( "None" )<< tr( "Dot" )<< tr( "Cross" )<< tr( "Plus" )<< tr( "Circle" )<< tr( "Disc" )<< tr( "Square" )
		<< tr( "Diamond" )<< tr( "Star" )<< tr( "Triangle" )<< tr( "TriangleInverted" )<< tr( "CrossSquare" )<< tr( "PlusSquare" )
		<< tr( "Peace" )<< tr( "Pixmap" );
	
	m_pUiCurveSetting->cmbPenStyle->addItems( strPenstyle );
	m_pUiCurveSetting->cmbLineStyle->addItems( strLineStyle );
	m_pUiCurveSetting->cmbScatterShape->addItems( strScatter );

	connect( m_pNavigation, SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ), 
		this,SLOT( onTreeItemChanged( QTreeWidgetItem*, QTreeWidgetItem*) ) );

	connect( m_pUiCurveSetting->btnCurveColor, SIGNAL( clicked()), this, SLOT( on_btnCurveColor_Cliked() ) );
	connect( m_pUiCurveSetting->spinBoxWidth, SIGNAL( valueChanged( int ) ),
			this, SLOT( on_valueChanged( ) ) );
	connect( m_pUiCurveSetting->cmbPenStyle, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( on_valueChanged( ) ) );
	connect( m_pUiCurveSetting->cmbLineStyle, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( on_valueChanged( ) ) );
	connect( m_pUiCurveSetting->cmbScatterShape, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( on_valueChanged( ) ) );
	connect( m_pUiCurveSetting->cmbaxis, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( on_valueChanged( ) ) );
	updateCurves();
}

void CurveSettingDialog::onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous )
{
	if( !current )
		return;
	int n = m_pNavigation->indexOfTopLevelItem( current );
		
	SetCurveSetting( m_listSettings.value(n) );
	on_valueChanged();
}

void CurveSettingDialog::on_btnCurveColor_Cliked()
{
	QColor c = QColorDialog::getColor( Qt::white, this );
	m_settings.colorCurve = c;
	m_pUiCurveSetting->btnCurveColor->setIcon( CreateBtnColorIcon(c) );
//	SetCurveSetting( m_settings );
	on_valueChanged();
}

void CurveSettingDialog::updateCurves()
{
	if( !m_plot )
		return;
	if( 0 == m_plot->plottableCount() )
		return;
	m_pNavigation->clear();
	m_listSettings.clear();
	QList<QTreeWidgetItem*> strlItems;
	for( int i = 0; i < m_plot->plottableCount(); i++ )
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pNavigation );
		pItem->setText(  0,m_plot->plottable( i )->name() );
		CurveSetting s;
		GetGraphInfo( (QCPCurve*)m_plot->plottable( i ),s );
		m_listSettings.append(s);
		strlItems.append( pItem );
	}
	m_pNavigation->addTopLevelItems( strlItems );
	
}

void CurveSettingDialog::GetGraphInfo( QCPCurve* p, CurveSetting& settings )
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

void CurveSettingDialog::SetGraphInfo( QCPCurve* p, CurveSetting& settings )
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
		p->setKeyAxis( m_plot->xAxis );
		p->setValueAxis( m_plot->yAxis );
		break;
	case Axis_top_right:
		p->setKeyAxis( m_plot->xAxis2 );
		p->setValueAxis( m_plot->yAxis2 );
		break;
	}
	p->setLineStyle( settings.curveLineStyle );
	p->setScatterStyle( settings.scatterShape );
}

QIcon CurveSettingDialog::CreateBtnColorIcon( QColor c )
{
	QPixmap pixmap( 16, 16 );
	QPainter painter( &pixmap );
	QBrush brush(c);
	painter.setPen( c );
	painter.setBrush( brush );
	//painter.fillRect( 0, 0, 16, 16, c );
	painter.drawEllipse( 0, 0, 16, 16 );
	return QIcon( pixmap );
}


void CurveSettingDialog::on_valueChanged( )
{
	QTreeWidgetItem* pItem = m_pNavigation->currentItem();
	int n = m_pNavigation->indexOfTopLevelItem( pItem );
	if( !m_plot )
		return;
	CurveSetting s;
	GetCurveSetting(s);
	if( m_listSettings.size() < (n+1)  )
		return;
	m_listSettings.replace(n,s);
	if( m_plot->plottable(n) )
		SetGraphInfo((QCPCurve*) m_plot->plottable(n),s );

	m_plot->replot( QCustomPlot::rpImmediate );
}

void CurveSettingDialog::SetCustomPlot( QCustomPlot* plot )
{
	if( !plot )
		return;
	m_plot = plot;
	updateCurves();
}
