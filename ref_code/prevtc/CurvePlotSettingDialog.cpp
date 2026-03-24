#include "CurvePlotSettingDialog.h"
#include <QTreeWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QFontDialog>
#include <QColorDialog>
#include <QFont>
#include <QPixmap>
#include <QPainter>
#include <QIcon>
#include <QDialogButtonBox>
#include <QFile>
#include <QDataStream>
#include <QDir>

#include "qcustomplot/qcustomplot.h"

#include "ui_axisGeneral.h"
#include "ui_axisSetting.h"

CurvePlotSettingDialog::CurvePlotSettingDialog( QCustomPlot* p,QWidget* parent /*= 0 */ )
{
	m_pUiGeneral		= new Ui::axisGeneral;
	m_pUiLeftAxis		= new Ui::axisSetting;
	m_pUiRightAxis		= new Ui::axisSetting;
	m_pUiTopAxis		= new Ui::axisSetting;
	m_pUiBottomAxis		= new Ui::axisSetting;
	
	customPlot = p;

	setMaximumWidth( 500 );
	setMaximumHeight( 400 );

	InitUI();
}

CurvePlotSettingDialog::~CurvePlotSettingDialog()
{
	delete m_pUiGeneral;
	delete m_pUiLeftAxis;
	delete m_pUiRightAxis;
	delete m_pUiTopAxis;
	delete m_pUiBottomAxis;
}

void CurvePlotSettingDialog::InitUI()
{
	m_pParaWdgts  = new QStackedWidget;
	QDialog* pGeneral = new QDialog;
	m_pUiGeneral->setupUi( pGeneral );

	//index 1
	QWidget* pLeftWdgt = new QWidget;
	m_pUiLeftAxis->setupUi( pLeftWdgt );
	m_pUiLeftAxis->labelName->setText("Left Axis");

	//index 2
	QWidget* pBottomWdgt = new QWidget;
	m_pUiBottomAxis->setupUi( pBottomWdgt );
	m_pUiBottomAxis->labelName->setText( tr("Bottom Axis") );

	//index 3
	QWidget* pTopWdgt = new QWidget;
	m_pUiTopAxis->setupUi( pTopWdgt );
	m_pUiTopAxis->labelName->setText( tr("Top Axis") );

	//index 4
	QWidget* pRightWdgt = new QWidget;
	m_pUiRightAxis->setupUi( pRightWdgt );
	m_pUiRightAxis->labelName->setText( tr("Right Axis") );
	
	m_pParaWdgts->addWidget( pGeneral );
	m_pParaWdgts->addWidget( pBottomWdgt );
	m_pParaWdgts->addWidget( pRightWdgt );	
	m_pParaWdgts->addWidget( pTopWdgt );	
	m_pParaWdgts->addWidget( pLeftWdgt );
	
	m_pNavigation = new QTreeWidget;
	//m_pNavigation->setMaximumWidth( 130 );
	m_pNavigation->setMinimumWidth( 110 );

	m_pNavigation->setHeaderHidden( true );
	QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pNavigation );
	pItem->setText(0, tr("General") );
	m_pNavigation->addTopLevelItem( pItem );
	pItem = new QTreeWidgetItem(m_pNavigation );
	pItem->setText(0, tr("Left Axis") );
	m_pNavigation->addTopLevelItem( pItem );
	pItem = new QTreeWidgetItem(m_pNavigation );
	pItem->setText( 0, tr("Right Axis") );
	m_pNavigation->addTopLevelItem( pItem );
	pItem= new QTreeWidgetItem(m_pNavigation );
	pItem->setText( 0, tr("Top Axis") );
	m_pNavigation->addTopLevelItem( pItem );
	pItem = new QTreeWidgetItem(m_pNavigation );
	pItem->setText( 0, tr("Bottom Axis") );
	m_pNavigation->addTopLevelItem( pItem );

	QHBoxLayout* pLayout = new QHBoxLayout();
	pLayout->addWidget( m_pNavigation );
	pLayout->addWidget( m_pParaWdgts );
	
	QFrame* pFrame = new QFrame;
	pFrame->setFrameShape( QFrame::HLine );
	
	QVBoxLayout* pMainLayout = new QVBoxLayout(this);
	pMainLayout->addLayout( pLayout );
	pMainLayout->addWidget( pFrame );
	setLayout( pMainLayout );
	
//init ui
	QStringList strhorizontal, strvertical;
	strhorizontal << tr( "Left" )<< tr( "Right" )<< tr( "Center" )<< tr( "Justify" );
	strvertical << tr( "Top" )<< tr( "Bottom" )<< tr( "Center" );
	
	m_pUiGeneral->cmbLocationH->addItems( strhorizontal );
	m_pUiGeneral->cmbLocationV->addItems( strvertical );

	connect( m_pNavigation, SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ), 
		   this,SLOT( onTreeItemChanged( QTreeWidgetItem*, QTreeWidgetItem*) ) );

	//general
	connect( m_pUiGeneral->btnfont, SIGNAL( clicked() ), this, SLOT( on_btnfont_Cliked() ) );
	connect( m_pUiGeneral->btnColor, SIGNAL( clicked() ), this, SLOT( on_btnColor_Cliked() ) );
	connect( m_pUiGeneral->TextEdit, SIGNAL( textChanged( const QString&) ), this, SLOT( on_valueChanged() ) );
	connect( m_pUiGeneral->checkBoxLegend, SIGNAL( stateChanged( int ) ), this, SLOT( on_valueChanged() ) );
	connect( m_pUiGeneral->checkBoxMovtion, SIGNAL( stateChanged( int ) ), this, SLOT( on_valueChanged() ) );

	connect( m_pUiGeneral->cmbLocationH, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onActived(int) ) );
	connect( m_pUiGeneral->cmbLocationV, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onActived(int) ) );

	connect( m_pUiGeneral->cmbLocationH, SIGNAL( currentIndexChanged( int ) ), this, SLOT( on_valueChanged() ) );
	connect( m_pUiGeneral->cmbLocationV, SIGNAL( currentIndexChanged( int ) ), this, SLOT( on_valueChanged() ) );

	connect(m_pUiGeneral->legendBtnfont,SIGNAL(clicked()),this,SLOT(on_legendBtnfont_clicked()));

//axis

	//left
	connect( m_pUiLeftAxis->btnAxiscolor, SIGNAL( clicked()), this, SLOT( on_btnAxiscolor_Cliked() ) );
	connect( m_pUiLeftAxis->btnGridcolor, SIGNAL( clicked()), this, SLOT( on_btnGridcolor_Cliked() ) );
	connect( m_pUiLeftAxis->btnTitleFont, SIGNAL( clicked()), this, SLOT( on_btnTitleFont_Cliked() ) );
	connect( m_pUiLeftAxis->btnLabelColor, SIGNAL( clicked()), this, SLOT( on_btnLabelColor_Cliked() ) );
	connect( m_pUiLeftAxis->btnLabelFont, SIGNAL( clicked()), this, SLOT( on_btnLabelFont_Cliked() ) );

	connect( m_pUiLeftAxis->checkBoxGrid, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiLeftAxis->chkAxis, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiLeftAxis->checkBoxLog, SIGNAL( stateChanged( int ) ), this, SLOT( on_valueChanged() ) );
	connect( m_pUiLeftAxis->edtAxisTitle, SIGNAL(textChanged( const QString&)), this, SLOT( on_valueChanged() ) );
	connect( m_pUiLeftAxis->spinBoxPrecision, SIGNAL( valueChanged( int )), this, SLOT( on_valueChanged() ) );

	//right
	connect( m_pUiRightAxis->btnAxiscolor, SIGNAL( clicked()), this, SLOT( on_btnAxiscolor_Cliked() ) );
	connect( m_pUiRightAxis->btnGridcolor, SIGNAL( clicked()), this, SLOT( on_btnGridcolor_Cliked() ) );
	connect( m_pUiRightAxis->btnTitleFont, SIGNAL( clicked()), this, SLOT( on_btnTitleFont_Cliked() ) );
	connect( m_pUiRightAxis->btnLabelColor, SIGNAL( clicked()), this, SLOT( on_btnLabelColor_Cliked() ) );
	connect( m_pUiRightAxis->btnLabelFont, SIGNAL( clicked()), this, SLOT( on_btnLabelFont_Cliked() ) );
	
	connect( m_pUiRightAxis->checkBoxGrid, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiRightAxis->chkAxis, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiRightAxis->checkBoxLog, SIGNAL( stateChanged( int ) ), this, SLOT( on_valueChanged() ) );
	connect( m_pUiRightAxis->edtAxisTitle, SIGNAL(textChanged( const QString&)), this, SLOT( on_valueChanged() ) );
	connect( m_pUiRightAxis->spinBoxPrecision, SIGNAL( valueChanged( int )), this, SLOT( on_valueChanged() ) );

	//top
	connect( m_pUiTopAxis->btnAxiscolor, SIGNAL( clicked()), this, SLOT( on_btnAxiscolor_Cliked() ) );
	connect( m_pUiTopAxis->btnGridcolor, SIGNAL( clicked()), this, SLOT( on_btnGridcolor_Cliked() ) );
	connect( m_pUiTopAxis->btnTitleFont, SIGNAL( clicked()), this, SLOT( on_btnTitleFont_Cliked() ) );
	connect( m_pUiTopAxis->btnLabelColor, SIGNAL( clicked()), this, SLOT( on_btnLabelColor_Cliked() ) );
	connect( m_pUiTopAxis->btnLabelFont, SIGNAL( clicked()), this, SLOT( on_btnLabelFont_Cliked() ) );

	connect( m_pUiTopAxis->checkBoxGrid, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiTopAxis->chkAxis, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiTopAxis->checkBoxLog, SIGNAL( stateChanged( int ) ), this, SLOT( on_valueChanged() ) );
	connect( m_pUiTopAxis->edtAxisTitle, SIGNAL(textChanged( const QString&)), this, SLOT( on_valueChanged() ) );
	connect( m_pUiTopAxis->spinBoxPrecision, SIGNAL( valueChanged( int )), this, SLOT( on_valueChanged() ) );

	//bottom
	connect( m_pUiBottomAxis->btnAxiscolor, SIGNAL( clicked()), this, SLOT( on_btnAxiscolor_Cliked() ) );
	connect( m_pUiBottomAxis->btnGridcolor, SIGNAL( clicked()), this, SLOT( on_btnGridcolor_Cliked() ) );
	connect( m_pUiBottomAxis->btnTitleFont, SIGNAL( clicked()), this, SLOT( on_btnTitleFont_Cliked() ) );
	connect( m_pUiBottomAxis->btnLabelColor, SIGNAL( clicked()), this, SLOT( on_btnLabelColor_Cliked() ) );
	connect( m_pUiBottomAxis->btnLabelFont, SIGNAL( clicked()), this, SLOT( on_btnLabelFont_Cliked() ) );
		
	connect( m_pUiBottomAxis->checkBoxGrid, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiBottomAxis->chkAxis, SIGNAL( stateChanged( int )), this, SLOT( on_valueChanged() ) );
	connect( m_pUiBottomAxis->checkBoxLog, SIGNAL( stateChanged( int ) ), this, SLOT( on_valueChanged() ) );
	connect( m_pUiBottomAxis->edtAxisTitle, SIGNAL(textChanged( const QString&)), this, SLOT( on_valueChanged() ) );
	connect( m_pUiBottomAxis->spinBoxPrecision, SIGNAL( valueChanged( int )), this, SLOT( on_valueChanged() ) );

//	SetPlotSetting( m_settings );
}

void CurvePlotSettingDialog::Plot2Control()
{
	Plot2Setting(customPlot,m_settings);
	Setting2Control( m_settings );
}

void CurvePlotSettingDialog::Setting2Control( const CutsomPlotAxisSetting& settings )
{
	//general set para	
	m_pUiGeneral->TextEdit->setText( settings.generalSetting.strChartTitle );
	QFont f = settings.generalSetting.fontChartTitle;
	m_pUiGeneral->labelFont->setText(  f.family() + QString(",") +  QString::number(f.pointSize()) );
	m_pUiGeneral->btnColor->setIcon( CreateBtnColorIcon( settings.generalSetting.colorChartTitle ) );
	m_pUiGeneral->checkBoxLegend->setChecked( settings.generalSetting.bShowLegend );
	m_pUiGeneral->checkBoxMovtion->setChecked( settings.generalSetting.bShowMotion );

	QFont font = settings.generalSetting.fontLegendTitle;
	m_pUiGeneral->legendFontLabel->setText(font.family() + QString(",") + QString::number(font.pointSize()));

	int nHor, nVer;
	switch( settings.generalSetting.AlignLegendhorizontal )
	{
	case Qt::AlignLeft:
		nHor = 0;
		break;
	case Qt::AlignRight:
		nHor = 1;
		break;
	case Qt::AlignHCenter:
		nHor = 2;
		break;
	case Qt::AlignJustify:
		nHor = 3;
		break;
	}
	switch( settings.generalSetting.AlignLegendvertical )
	{
	case Qt::AlignTop:
		nVer = 0;
		break;
	case Qt::AlignBottom:
		nVer = 1;
		break;
	case Qt::AlignVCenter:
		nVer = 2;
		break;
	}
	_userHandle = false;
	m_pUiGeneral->cmbLocationH->setCurrentIndex( nHor );
	m_pUiGeneral->cmbLocationV->setCurrentIndex( nVer );
	_userHandle = true;

//axis set para

	//left axis
	m_pUiLeftAxis->checkBoxGrid->setChecked( settings.leftAxisSetting.bShowGrid );
	m_pUiLeftAxis->chkAxis->setChecked( settings.leftAxisSetting.bShowAxis );
	m_pUiLeftAxis->btnAxiscolor->setIcon( CreateBtnColorIcon( settings.leftAxisSetting.colorAxis ) );
	m_pUiLeftAxis->btnGridcolor->setIcon( CreateBtnColorIcon( settings.leftAxisSetting.colorGrid ) );
	m_pUiLeftAxis->edtAxisTitle->setText( settings.leftAxisSetting.strAxisTitle );
	f = settings.leftAxisSetting.fontAxisTitle;
	m_pUiLeftAxis->lblTitleFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiLeftAxis->btnLabelColor->setIcon( CreateBtnColorIcon( settings.leftAxisSetting.colorAxisLabels ) );
	f = settings.leftAxisSetting.fontAxisLabels;
	m_pUiLeftAxis->lblLabelFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiLeftAxis->spinBoxPrecision->setValue( settings.leftAxisSetting.nPrecision );
	m_pUiLeftAxis->checkBoxLog->setChecked( settings.leftAxisSetting.bUseLogarithmic );

	//right axis
	m_pUiRightAxis->checkBoxGrid->setChecked( settings.rightAxisSetting.bShowGrid );
	m_pUiRightAxis->chkAxis->setChecked( settings.rightAxisSetting.bShowAxis );
	m_pUiRightAxis->btnAxiscolor->setIcon( CreateBtnColorIcon( settings.rightAxisSetting.colorAxis ) );
	m_pUiRightAxis->btnGridcolor->setIcon( CreateBtnColorIcon( settings.rightAxisSetting.colorGrid ) );
	m_pUiRightAxis->edtAxisTitle->setText( settings.rightAxisSetting.strAxisTitle );
	f = settings.rightAxisSetting.fontAxisTitle;
	m_pUiRightAxis->lblTitleFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiRightAxis->btnLabelColor->setIcon( CreateBtnColorIcon( settings.leftAxisSetting.colorAxisLabels ) );
	f = settings.rightAxisSetting.fontAxisLabels;
	m_pUiRightAxis->lblLabelFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiRightAxis->spinBoxPrecision->setValue( settings.rightAxisSetting.nPrecision );
	m_pUiRightAxis->checkBoxLog->setChecked( settings.rightAxisSetting.bUseLogarithmic );

	//top axis
	m_pUiTopAxis->checkBoxGrid->setChecked( settings.topAxisSetting.bShowGrid );
	m_pUiTopAxis->chkAxis->setChecked( settings.topAxisSetting.bShowAxis );
	m_pUiTopAxis->btnAxiscolor->setIcon( CreateBtnColorIcon( settings.topAxisSetting.colorAxis ) );
	m_pUiTopAxis->btnGridcolor->setIcon( CreateBtnColorIcon( settings.topAxisSetting.colorGrid ) );
	m_pUiTopAxis->edtAxisTitle->setText( settings.topAxisSetting.strAxisTitle );
	f = settings.topAxisSetting.fontAxisTitle;
	m_pUiTopAxis->lblTitleFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiTopAxis->btnLabelColor->setIcon( CreateBtnColorIcon( settings.topAxisSetting.colorAxisLabels ) );
	f = settings.topAxisSetting.fontAxisLabels;
	m_pUiTopAxis->lblLabelFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiTopAxis->spinBoxPrecision->setValue( settings.topAxisSetting.nPrecision );
	m_pUiTopAxis->checkBoxLog->setChecked( settings.topAxisSetting.bUseLogarithmic );

	//bottom axis
	m_pUiBottomAxis->checkBoxGrid->setChecked( settings.bottomAxisSetting.bShowGrid );
	m_pUiBottomAxis->chkAxis->setChecked( settings.bottomAxisSetting.bShowAxis );
	m_pUiBottomAxis->btnAxiscolor->setIcon( CreateBtnColorIcon( settings.bottomAxisSetting.colorAxis ) );
	m_pUiBottomAxis->btnGridcolor->setIcon( CreateBtnColorIcon( settings.bottomAxisSetting.colorGrid ) );
	m_pUiBottomAxis->edtAxisTitle->setText( settings.bottomAxisSetting.strAxisTitle );
	f = settings.bottomAxisSetting.fontAxisTitle;
	m_pUiBottomAxis->lblTitleFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiBottomAxis->btnLabelColor->setIcon( CreateBtnColorIcon( settings.bottomAxisSetting.colorAxisLabels ) );
	f = settings.bottomAxisSetting.fontAxisLabels;
	m_pUiBottomAxis->lblLabelFont->setText( f.family() + QString( tr( "," ) ) + QString::number( f.pointSize() ) );
	m_pUiBottomAxis->spinBoxPrecision->setValue( settings.bottomAxisSetting.nPrecision );
	m_pUiBottomAxis->checkBoxLog->setChecked( settings.bottomAxisSetting.bUseLogarithmic );

	m_settings = settings;
}

void CurvePlotSettingDialog::Control2Setting( CutsomPlotAxisSetting& settings )
{
//general	
	settings.generalSetting.strChartTitle = m_pUiGeneral->TextEdit->text();
	QString testS = m_settings.generalSetting.fontChartTitle.family();
	int testInt = m_settings.generalSetting.fontChartTitle.pointSize(); 
	if(m_settings.generalSetting.fontChartTitle.family() == "SimSun" && m_settings.generalSetting.fontChartTitle.pointSize() == 9)
	{
		QFont titleFont;
		titleFont.setFamily("ºÚÌå");
		titleFont.setPointSize(20);
		settings.generalSetting.fontChartTitle = titleFont;
	}
	else
		settings.generalSetting.fontChartTitle = m_settings.generalSetting.fontChartTitle;

	settings.generalSetting.colorChartTitle = m_settings.generalSetting.colorChartTitle;

	settings.generalSetting.bShowLegend = m_pUiGeneral->checkBoxLegend->isChecked();
	settings.generalSetting.fontLegendTitle = m_settings.generalSetting.fontLegendTitle;
	int nH = m_pUiGeneral->cmbLocationH->currentIndex();
	int nV = m_pUiGeneral->cmbLocationV->currentIndex();

	switch( nH )
	{
	case 0:
		settings.generalSetting.AlignLegendhorizontal = Qt::AlignLeft;
		break;
	case 1:
		settings.generalSetting.AlignLegendhorizontal = Qt::AlignRight;
		break;
	case 2:
		settings.generalSetting.AlignLegendhorizontal = Qt::AlignHCenter;
		break;
	case 3:
		settings.generalSetting.AlignLegendhorizontal = Qt::AlignJustify;
		break;
	}

	switch( nV )
	{
	case 0:
		settings.generalSetting.AlignLegendvertical = Qt::AlignTop;
		break;
	case 1:
		settings.generalSetting.AlignLegendvertical = Qt::AlignBottom;
		break;
	case 2:
		settings.generalSetting.AlignLegendvertical = Qt::AlignVCenter;
		break;	
	}
	settings.generalSetting.bShowMotion = m_pUiGeneral->checkBoxMovtion->isChecked();

//axis

	//left
	settings.leftAxisSetting.bShowGrid = m_pUiLeftAxis->checkBoxGrid->isChecked();
	settings.leftAxisSetting.bShowAxis = m_pUiLeftAxis->chkAxis->isChecked();
	settings.leftAxisSetting.colorAxis = m_settings.leftAxisSetting.colorAxis;
	settings.leftAxisSetting.colorGrid = m_settings.leftAxisSetting.colorGrid;
	settings.leftAxisSetting.strAxisTitle = m_pUiLeftAxis->edtAxisTitle->text();
	settings.leftAxisSetting.fontAxisTitle = m_settings.leftAxisSetting.fontAxisTitle;
	settings.leftAxisSetting.colorAxisLabels = m_settings.leftAxisSetting.colorAxisLabels;
	settings.leftAxisSetting.fontAxisLabels = m_settings.leftAxisSetting.fontAxisLabels;
	settings.leftAxisSetting.nPrecision = m_settings.leftAxisSetting.nPrecision;
	settings.leftAxisSetting.bUseLogarithmic = m_pUiLeftAxis->checkBoxLog->isChecked();

	//rigth
	settings.rightAxisSetting.bShowGrid = m_pUiRightAxis->checkBoxGrid->isChecked();
	settings.rightAxisSetting.bShowAxis = m_pUiRightAxis->chkAxis->isChecked();
	settings.rightAxisSetting.colorAxis = m_settings.rightAxisSetting.colorAxis;
	settings.rightAxisSetting.colorGrid = m_settings.rightAxisSetting.colorGrid;
	settings.rightAxisSetting.strAxisTitle = m_pUiRightAxis->edtAxisTitle->text();
	settings.rightAxisSetting.fontAxisTitle = m_settings.rightAxisSetting.fontAxisTitle;
	settings.rightAxisSetting.colorAxisLabels = m_settings.rightAxisSetting.colorAxisLabels;
	settings.rightAxisSetting.fontAxisLabels = m_settings.rightAxisSetting.fontAxisLabels;
	settings.rightAxisSetting.nPrecision = m_settings.rightAxisSetting.nPrecision;
	settings.rightAxisSetting.bUseLogarithmic = m_pUiRightAxis->checkBoxLog->isChecked();

	//top
	settings.topAxisSetting.bShowGrid = m_pUiTopAxis->checkBoxGrid->isChecked();
	settings.topAxisSetting.bShowAxis = m_pUiTopAxis->chkAxis->isChecked();
	settings.topAxisSetting.colorAxis = m_settings.topAxisSetting.colorAxis;
	settings.topAxisSetting.colorGrid = m_settings.topAxisSetting.colorGrid;
	settings.topAxisSetting.strAxisTitle = m_pUiTopAxis->edtAxisTitle->text();
	settings.topAxisSetting.fontAxisTitle = m_settings.topAxisSetting.fontAxisTitle;
	settings.topAxisSetting.colorAxisLabels = m_settings.topAxisSetting.colorAxisLabels;
	settings.topAxisSetting.fontAxisLabels = m_settings.topAxisSetting.fontAxisLabels;
	settings.topAxisSetting.nPrecision = m_settings.topAxisSetting.nPrecision;
	settings.topAxisSetting.bUseLogarithmic = m_pUiTopAxis->checkBoxLog->isChecked();

	//bottom
	settings.bottomAxisSetting.bShowGrid = m_pUiBottomAxis->checkBoxGrid->isChecked();
	settings.bottomAxisSetting.bShowAxis = m_pUiBottomAxis->chkAxis->isChecked();
	settings.bottomAxisSetting.colorAxis = m_settings.bottomAxisSetting.colorAxis;
	settings.bottomAxisSetting.colorGrid = m_settings.bottomAxisSetting.colorGrid;
	settings.bottomAxisSetting.strAxisTitle = m_pUiBottomAxis->edtAxisTitle->text();
	settings.bottomAxisSetting.fontAxisTitle = m_settings.bottomAxisSetting.fontAxisTitle;
	settings.bottomAxisSetting.colorAxisLabels = m_settings.bottomAxisSetting.colorAxisLabels;
	settings.bottomAxisSetting.fontAxisLabels = m_settings.bottomAxisSetting.fontAxisLabels;
	settings.bottomAxisSetting.nPrecision = m_settings.bottomAxisSetting.nPrecision;
	settings.bottomAxisSetting.bUseLogarithmic = m_pUiBottomAxis->checkBoxLog->isChecked();
}

void CurvePlotSettingDialog::onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous )
{
	if( !current )
		return;

	int n = m_pNavigation->indexOfTopLevelItem( current );
	m_pParaWdgts->setCurrentIndex( n );
}

QIcon CurvePlotSettingDialog::CreateBtnColorIcon( QColor c )
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

void CurvePlotSettingDialog::on_btnfont_Cliked()
{
	Control2Setting( m_settings );
	bool ok;
	QFont font = QFontDialog::getFont(&ok,m_settings.generalSetting.fontChartTitle, this);
	if (ok) 
		m_settings.generalSetting.fontChartTitle = font;
	
	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::on_btnColor_Cliked()
{
	Control2Setting( m_settings );
	QColor c = QColorDialog::getColor( Qt::white, this );
	m_settings.generalSetting.colorChartTitle = c;
	
	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::on_btnAxiscolor_Cliked()
{
	Control2Setting( m_settings );
	QColor c = QColorDialog::getColor( Qt::white, this );
	int nIndex = m_pParaWdgts->currentIndex();
	switch( nIndex )
	{
	case 1:
		m_settings.bottomAxisSetting.colorAxis = c;
		
		break;
	case 2:
		m_settings.rightAxisSetting.colorAxis = c;
		break;
	case 3:
		m_settings.topAxisSetting.colorAxis = c;
		break;
	case 4:
		m_settings.leftAxisSetting.colorAxis = c;
		break;	
	}
	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::on_btnGridcolor_Cliked()
{
	Control2Setting( m_settings );
	QColor c = QColorDialog::getColor( Qt::white, this );
	int nIndex = m_pParaWdgts->currentIndex();
	switch( nIndex )
	{
	case 1:
		m_settings.bottomAxisSetting.colorGrid = c;
		
		break;
	case 2:
		m_settings.rightAxisSetting.colorGrid = c;
		break;
	case 3:
		m_settings.topAxisSetting.colorGrid = c;
		break;
	case 4:
		m_settings.leftAxisSetting.colorGrid = c;
		break;	
	}

	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::on_btnTitleFont_Cliked()
{
	Control2Setting( m_settings );
	bool ok;
	QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
	if( !ok )
		return;
	int nIndex = m_pParaWdgts->currentIndex();
	switch( nIndex )
	{
	case 1:
		m_settings.bottomAxisSetting.fontAxisTitle = font;
	
		break;
	case 2:
		m_settings.rightAxisSetting.fontAxisTitle = font;
		break;
	case 3:
		m_settings.topAxisSetting.fontAxisTitle = font;
		break;
	case 4:
		m_settings.leftAxisSetting.fontAxisTitle = font;
		break;	
	}
	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::on_btnLabelColor_Cliked()
{
	Control2Setting( m_settings );
	QColor c = QColorDialog::getColor( Qt::white, this );
	int nIndex = m_pParaWdgts->currentIndex();
	switch( nIndex )
	{
	case 1:
		m_settings.bottomAxisSetting.colorAxisLabels = c;		
		break;
	case 2:
		m_settings.rightAxisSetting.colorAxisLabels = c;
		break;
	case 3:
		m_settings.topAxisSetting.colorAxisLabels = c;
		break;
	case 4:
		m_settings.leftAxisSetting.colorAxisLabels = c;
		break;	
	}
	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::on_btnLabelFont_Cliked()
{
	Control2Setting( m_settings );
	bool ok;
	QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
	if( !ok )
		return;
	int nIndex = m_pParaWdgts->currentIndex();
	switch( nIndex )
	{
	case 1:
		m_settings.bottomAxisSetting.fontAxisLabels = font;
		
		break;
	case 2:
		m_settings.rightAxisSetting.fontAxisLabels = font;
		break;
	case 3:
		m_settings.topAxisSetting.fontAxisLabels = font;
		break;
	case 4:
		m_settings.leftAxisSetting.fontAxisLabels = font;
		break;	
	}
	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::on_btnCurveColor_Cliked()
{
}

void CurvePlotSettingDialog::on_valueChanged()
{
	CutsomPlotAxisSetting settings;
	Control2Setting( settings );
	Setting2Plot( settings,customPlot );
}

void CurvePlotSettingDialog::SetCustomPlot( QCustomPlot* plot )
{
	if( !plot )
		return;

	customPlot = plot;
	Plot2Control();
}

void CurvePlotSettingDialog::on_legendBtnfont_clicked()
{
	Control2Setting( m_settings );
	bool ok;
	
	QFont font = QFontDialog::getFont(&ok, customPlot->legend->font(), this);
	if (ok) 
		m_settings.generalSetting.fontLegendTitle = font;
	
	Setting2Control( m_settings );
	on_valueChanged();
}

void CurvePlotSettingDialog::onActived(int index)
{
	if(_userHandle)
		customPlot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipBorderAligned);	
}


