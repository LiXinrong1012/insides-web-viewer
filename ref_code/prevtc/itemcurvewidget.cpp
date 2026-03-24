#include "itemcurvewidget.h"
#include "ui_itemcurvewidget.h"

#include <QLibrary>
#include <QFileDialog>

#include "precore/modeldocument.h"
#include "precore/FlexResultItem.h"
#include "precore/RigidResultItem.h"
#include "precore/ResultDocument.h"

#include "pubbase/mimedata.h"

#include "customcurveplot.h"
#include "curvepointstracer.h"
#include "CurvePlotSettingDialog.h"
#include "CurveSettingDialog.h"
#include "CurveParasSerialize.h"
#include "addcustomcurvedialog.h"

using namespace INSIDES;

ItemCurveWidget::ItemCurveWidget(QWidget *parent)
	: QWidget(parent)
	,_customCurveDialog(NULL)
{
	ui = new Ui::ItemCurveWidget();
	ui->setupUi(this);
	ui->customPlot->setFocusPolicy(Qt::ClickFocus);

	CustomCurvePlot* plot=new CustomCurvePlot(this,ui->customPlot);
	_plot=plot;

	//connect(ui->selector,SIGNAL(itemAdding(QVector<double>&,QVector<double>&,const QString&)),
		//this,SLOT(onItemAdding(QVector<double>&,QVector<double>&,const QString&)));
	connect(ui->selector,SIGNAL(itemAdding(CurveItemTitle)),
		this,SLOT(onItemAdding(CurveItemTitle)));
	connect(ui->selector,SIGNAL(newResultLoaded()),
		this,SLOT(onNewResultLoaded()));

	connect(_plot,SIGNAL(updateCurve(CurveItemTitle)),this,SLOT(showAddCustomCurveDialogWithUpdate(CurveItemTitle)));
}

ItemCurveWidget::~ItemCurveWidget()
{
	delete ui;
}

void ItemCurveWidget::onItemAdding( CurveItemTitle itemTitle )
{
	_plot->addMyCurve(itemTitle);
	if (_plot->getPointsTracer()->getPointsAction()->isChecked())
	{
		_plot->getPointsTracer()->hideAllData();
		_plot->getPointsTracer()->showAllData();
	}
	
}

void ItemCurveWidget::onItemUpdating( CurveItemTitle itemTitle )
{
	_plot->updateMyCurve(itemTitle);
	if (_plot->getPointsTracer()->getPointsAction()->isChecked())
	{
		_plot->getPointsTracer()->hideAllData();
		_plot->getPointsTracer()->showAllData();
	}
}

CustomCurvePlot* ItemCurveWidget::getPlot()
{
	return _plot;
}

void ItemCurveWidget::hideShowTitle()
{
	if(ui->selector->isVisible())
		ui->selector->hide();
	else
		ui->selector->show();
}

void ItemCurveWidget::showViewSettings()
{
	CurvePlotSettingDialog* _viewSettingDialog=new CurvePlotSettingDialog(_plot->getCustomPlot(),0);
	_viewSettingDialog->Plot2Control();
	_viewSettingDialog->show();
}

void ItemCurveWidget::showCurveSetting()
{
	CurveSettingDialog* _viewSettingDialog=new CurveSettingDialog(_plot->getCustomPlot(),0);
	_viewSettingDialog->updateCurves();
	_viewSettingDialog->show();
}

void ItemCurveWidget::setParentView( Base::View* view )
{
	ui->selector->setParentView(view);
}

void ItemCurveWidget::saveSettingState(QDataStream& out)
{
	CurveParasSerialize aaa(_plot->getCustomPlot());
	aaa.saveSetting(&out);
}

bool ItemCurveWidget::saveMyState( QDataStream& out )
{
	MimeData mimeData;
	QDataStream& streamCurve=*mimeData.startWriteCustomData("insviewer/prevtc/curvedata/1.0");
	streamCurve<<_plot->_curveItemTitleList.size();
	for(size_t i=0;i<_plot->_curveItemTitleList.size();++i){
		const CurveItemTitle& item=_plot->_curveItemTitleList[i];
		streamCurve<<item;
	}

	//QDataStream& streamState = *mimeData.startWriteCustomData("insviewer/prevtc/settingstate/1.0");
	//saveSettingState(streamState);
	QDataStream& streamState = *mimeData.startWriteCustomData("insviewer/prevtc/settingstate/2.0");
	CutsomPlotAxisSetting settings;
	Plot2Setting(_plot->getCustomPlot(),settings);
	settings.save(streamState);

	QDataStream& streamAxisRange=*mimeData.startWriteCustomData("insviewer/prevtc/axisrange/1.0");
	QCPRange range=ui->customPlot->xAxis->range();
	streamAxisRange<<range.lower<<range.upper;

	QCPRange rangey=ui->customPlot->yAxis->range();
	streamAxisRange<<rangey.lower<<rangey.upper;

	streamAxisRange<<ui->selector->isVisible();

	mimeData.stopWriteAllCustomData();
	out<<mimeData;
	return true;
}

void ItemCurveWidget::loadSettingState(QDataStream& in)
{
	CurveParasSerialize aaa(_plot->getCustomPlot());
	aaa.loadSetting(&in);
}

bool ItemCurveWidget::loadMyState( QDataStream& in, qint64 dataSize)
{
	MimeData mimeData;
	in>>mimeData;

	if(mimeData.hasFormat("insviewer/prevtc/curvedata/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevtc/curvedata/1.0");
		size_t s;
		(*stream)>>s;
		for(size_t i=0;i<s;++i){
			CurveItemTitle item;
			(*stream)>>item;
			onItemAdding(item);
		}
	}

	if(mimeData.hasFormat("insviewer/prevtc/settingstate/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevtc/settingstate/1.0");
		loadSettingState(*stream);
	}
	else if(mimeData.hasFormat("insviewer/prevtc/settingstate/2.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevtc/settingstate/2.0");
		CutsomPlotAxisSetting settings;
		settings.load(*stream);
		Setting2Plot(settings,_plot->getCustomPlot());
	}

	if(mimeData.hasFormat("insviewer/prevtc/axisrange/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevtc/axisrange/1.0");

		double a1,a2;
		(*stream)>>a1>>a2;
		QCPRange range(a1,a2);

		ui->customPlot->xAxis->setRange(range);
		ui->customPlot->replot();

		double a3,a4;
		(*stream)>>a3>>a4;
		QCPRange rangey(a3,a4);
		ui->customPlot->yAxis->setRange(rangey);
		ui->customPlot->replot();

		bool v;
		(*stream)>>v;
		ui->selector->setVisible(v);
	}

	return true;
}

void ItemCurveWidget::onNewResultLoaded()
{
	_plot->updateAllMyCurve();
}

void ItemCurveWidget::showAddCustomCurveDialog()
{
	if(!_customCurveDialog){
		_customCurveDialog=new AddCustomCurveDialog(this);
		connect(_customCurveDialog,SIGNAL(addItem(CurveItemTitle)),this,SLOT(onItemAdding(CurveItemTitle)));
		connect(_customCurveDialog,SIGNAL(updateItem(CurveItemTitle)),this,SLOT(onItemUpdating(CurveItemTitle)));
		_customCurveDialog->setWindowFlags(_customCurveDialog->windowFlags()|Qt::WindowStaysOnTopHint); 
	}
	_customCurveDialog->setIsAddMode(true);
	_customCurveDialog->show();
}

void ItemCurveWidget::showAddCustomCurveDialogWithUpdate(CurveItemTitle title)
{
	if(!_customCurveDialog){
		_customCurveDialog=new AddCustomCurveDialog(this);
		connect(_customCurveDialog,SIGNAL(addItem(CurveItemTitle)),this,SLOT(onItemAdding(CurveItemTitle)));
		connect(_customCurveDialog,SIGNAL(updateItem(CurveItemTitle)),this,SLOT(onItemUpdating(CurveItemTitle)));
		_customCurveDialog->setWindowFlags(_customCurveDialog->windowFlags()|Qt::WindowStaysOnTopHint); 
	}
	_customCurveDialog->setIsAddMode(false);
	_customCurveDialog->setUpdateCurveTitle(title);
	_customCurveDialog->updateConText();

	_customCurveDialog->show();
}





