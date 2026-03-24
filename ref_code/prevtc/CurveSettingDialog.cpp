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

#include "base/Console.h"
#include "ui_curveSetting.h"

#include "curve.h"

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

void CurveSettingDialog::Setting2Control( const CurveSetting& settings )
{
	//curve setting
	m_pUiCurveSetting->btnCurveColor->setIcon( CreateBtnColorIcon( settings.colorCurve ) );
	m_pUiCurveSetting->spinBoxWidth->setValue( settings.nCurveWidth );
	m_pUiCurveSetting->cmbPenStyle->setCurrentIndex( (int)settings.penStyle );
	m_pUiCurveSetting->cmbLineStyle->setCurrentIndex( (int)settings.curveLineStyle );
	m_pUiCurveSetting->cmbScatterShape->setCurrentIndex( (int)settings.scatterShape );
	m_pUiCurveSetting->cmbaxis->setCurrentIndex( (int)settings.axisType );
	m_pUiCurveSetting->spinBoxShapeWidth->setValue(settings.shapeSize);
	m_settings = settings;
}

void CurveSettingDialog::Control2Setting( CurveSetting& settings )
{
	settings.colorCurve = m_settings.colorCurve;
	settings.nCurveWidth= m_pUiCurveSetting->spinBoxWidth->value();
	settings.penStyle = (Qt::PenStyle)(m_pUiCurveSetting->cmbPenStyle->currentIndex());
	settings.curveLineStyle = (QCPCurve::LineStyle	)(m_pUiCurveSetting->cmbLineStyle->currentIndex());
	settings.scatterShape = (QCPScatterStyle::ScatterShape)(m_pUiCurveSetting->cmbScatterShape->currentIndex());
	settings.axisType = (AxisType)(m_pUiCurveSetting->cmbaxis->currentIndex());
	settings.shapeSize = m_pUiCurveSetting->spinBoxShapeWidth->value();
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
	
	QPushButton* upBtn = new QPushButton("Up");
	connect(upBtn,SIGNAL(clicked()),this,SLOT(onUpDownBtnClicked()));
	QPushButton* downBtn = new QPushButton("Down");
	connect(downBtn,SIGNAL(clicked()),this,SLOT(onUpDownBtnClicked()));

	QHBoxLayout* btnLayout = new QHBoxLayout();
	btnLayout->addWidget(upBtn);
	btnLayout->addWidget(downBtn);

	QVBoxLayout* leftLayout = new QVBoxLayout();
	leftLayout->addWidget(m_pNavigation);
	leftLayout->addLayout(btnLayout);

	//条目选择树和详情窗口
	QHBoxLayout* pLayout = new QHBoxLayout();
	pLayout->addLayout( leftLayout );
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
	
	strPenstyle<<tr("NoPen")
		<<tr( "SolidLine" )<< tr( "DashLine" )
		<< tr( "DotLine" )<< tr( "DashDotLine" )
		<<tr("DashDotDotLine");
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

	connect(m_pUiCurveSetting->spinBoxShapeWidth,SIGNAL(valueChanged ( int )),this,SLOT(on_valueChanged()));
}

void CurveSettingDialog::onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous )
{
	if( !current )
		return;
	int n = m_pNavigation->indexOfTopLevelItem( current );
		
	Setting2Control( m_listSettings.value(n) );
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
		Curve* curve=qobject_cast<Curve*>(m_plot->plottable(i));
		
		if(curve){
			QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pNavigation );
			pItem->setText(  0,curve->name() );
			CurveSetting s;
			Curve2Setting(curve,s );
			m_listSettings.append(s);
			m_curveList.append(curve);
			strlItems.append( pItem );
		}
	}
	m_pNavigation->addTopLevelItems( strlItems );
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
	int curveIndex = m_pNavigation->indexOfTopLevelItem( pItem );
	if(!m_plot || curveIndex>=m_listSettings.size()){
		Base::Console().Error("Curve setting error.");
		return;
	}

	CurveSetting s;
	Control2Setting(s);
	m_listSettings.replace(curveIndex,s);
	Setting2Curve(m_plot,m_curveList[curveIndex],s );

	m_plot->replot( QCustomPlot::rpImmediate );
}

void CurveSettingDialog::SetCustomPlot( QCustomPlot* plot )
{
	if( !plot )
		return;

	m_plot = plot;
	updateCurves();
}

void CurveSettingDialog::onUpDownBtnClicked()
{
	return;
	QTreeWidgetItem* curr = m_pNavigation->currentItem();
	if(!curr)
		return;

	QList<QCPAbstractPlottable*> list;
	for (int i=0;i<m_plot->plottableCount();i++)
		if(m_plot->plottable(i)->name() != "Time")
		list<<m_plot->plottable(i);
	
	QPushButton* btn = (QPushButton*)sender();
	if(btn->text().contains("Up"))
	{
		for(int i=0;i<list.count();i++)
		{
			if(list[i]->name() == curr->text(0))
			{
				if(i==0)
					return;
				QCPAbstractPlottable* tmp = list[i];
				list[i] = list[i-1];
				list[i-1] = tmp;
			}
		}
		for(int i=0;i<list.count();i++)
		{
			QCPCurve* cu = new QCPCurve(m_plot->xAxis,m_plot->yAxis);
			QCPCurve* c = qobject_cast<QCPCurve*>(list[i]);

			cu->setData(c->data());
			cu->setName(c->name());
			cu->setPen(c->pen());
			cu->setSelectable(c->selectable());
			m_plot->removePlottable(c);
			m_plot->addPlottable(cu);
		}
	}
	updateCurves();
}


