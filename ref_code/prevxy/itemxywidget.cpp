#include "itemxywidget.h"
#include "ui_itemxywidget.h"

#include <QLibrary>
#include <QFileDialog>

#include "precore/modeldocument.h"
#include "precore/FlexResultItem.h"
#include "precore/RigidResultItem.h"
#include "precore/ResultDocument.h"
#include "precore/IResultItem.h"

#include "pubbase/mimedata.h"

#include "curveplotsettingdialog.h"
#include "curvesettingdialog.h"
#include "curveparasserialize.h"
#include "customxyplot.h"
#include "xypointstracer.h"


using namespace INSIDES;

ItemXYWidget::ItemXYWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ItemXYWidget();
	ui->setupUi(this);
	ui->customPlot->setFocusPolicy(Qt::ClickFocus);

	CustomXYPlot* plot=new CustomXYPlot(this,ui->customPlot);
	_plot=plot;

	connect(ui->selector,SIGNAL(itemAdding(XYItemTitle)),this,SLOT(onItemAdding(XYItemTitle)));
	//connect(ui->selector,SIGNAL(newResultLoaded()),
	//	this,SLOT(onNewResultLoaded()));

	connect(_plot,SIGNAL(updateSelectedCurve(XYItemTitle&,bool)),this,SLOT(onUpdateSelectedCurve(XYItemTitle&,bool)));
}

ItemXYWidget::~ItemXYWidget()
{
	delete ui;
}

void ItemXYWidget::onItemAdding( XYItemTitle itemTitle )
{
	_plot->addMyCurve(itemTitle);
	if (_plot->getPointsTracer()->getPointsAction()->isChecked())
	{
		_plot->getPointsTracer()->hideAllData();
		_plot->getPointsTracer()->showAllData();
	}
}

void ItemXYWidget::onItemUpdating( XYItemTitle itemTitle )
{
	_plot->updateMyCurve(itemTitle);
	if (_plot->getPointsTracer()->getPointsAction()->isChecked())
	{
		_plot->getPointsTracer()->hideAllData();
		_plot->getPointsTracer()->showAllData();
	}
}

CustomXYPlot* ItemXYWidget::getPlot()
{
	return _plot;
}

void ItemXYWidget::hideShowTitle()
{
	if(ui->selector->isVisible())
		ui->selector->hide();
	else
		ui->selector->show();
}

void ItemXYWidget::showViewSettings()
{
	CurvePlotSettingDialog* _viewSettingDialog=new CurvePlotSettingDialog(_plot->getCustomPlot(),0);
	_viewSettingDialog->Plot2Control();
	_viewSettingDialog->show();
}

void ItemXYWidget::showCurveSetting()
{
	CurveSettingDialog* _viewSettingDialog=new CurveSettingDialog(_plot->getCustomPlot(),0);
	_viewSettingDialog->updateCurves();
	_viewSettingDialog->show();
}

void ItemXYWidget::setParentView( Base::View* view )
{
	ui->selector->setParentView(view);
}

void ItemXYWidget::saveSettingState(QDataStream& out)
{
	CurveParasSerialize aaa(_plot->getCustomPlot());
	aaa.saveSetting(&out);
}

bool ItemXYWidget::saveMyState( QDataStream& out )
{
	MimeData mimeData;
	QDataStream& streamCurve=*mimeData.startWriteCustomData("insviewer/prevxy/curvedata/1.0");
	streamCurve<<_plot->curveItemTitleList.size();
	for(size_t i=0;i<_plot->curveItemTitleList.size();++i){
		const XYItemTitle& item=_plot->curveItemTitleList[i];
		streamCurve<<item;
	}

	//QDataStream& streamState = *mimeData.startWriteCustomData("insviewer/prevxy/settingstate/1.0");
	//saveSettingState(streamState);
	QDataStream& streamState = *mimeData.startWriteCustomData("insviewer/prevxy/settingstate/2.0");
	CutsomPlotAxisSetting settings;
	Plot2Setting(_plot->getCustomPlot(),settings);
	settings.save(streamState);

	QDataStream& streamAxisRange=*mimeData.startWriteCustomData("insviewer/prevxy/axisrange/1.0");
	QCPRange range=ui->customPlot->xAxis->range();
	streamAxisRange<<range.lower<<range.upper;

	QCPRange rangey=ui->customPlot->yAxis->range();
	streamAxisRange<<rangey.lower<<rangey.upper;

	streamAxisRange<<ui->selector->isVisible();

	mimeData.stopWriteAllCustomData();
	out<<mimeData;
	return true;
}

void ItemXYWidget::loadSettingState(QDataStream& in)
{
	CurveParasSerialize aaa(_plot->getCustomPlot());
	aaa.loadSetting(&in);
}

bool ItemXYWidget::loadMyState( QDataStream& in, qint64 dataSize)
{
	MimeData mimeData;
	in>>mimeData;

	if(mimeData.hasFormat("insviewer/prevxy/curvedata/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevxy/curvedata/1.0");
		size_t s;
		(*stream)>>s;
		for(size_t i=0;i<s;++i){
			XYItemTitle item;
			(*stream)>>item;
			onItemAdding(item);
		}
	}

	if(mimeData.hasFormat("insviewer/prevxy/settingstate/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevxy/settingstate/1.0");
		loadSettingState(*stream);
	}
	else if(mimeData.hasFormat("insviewer/prevxy/settingstate/2.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevxy/settingstate/2.0");
		CutsomPlotAxisSetting settings;
		settings.load(*stream);
		Setting2Plot(settings,_plot->getCustomPlot());
	}

	if(mimeData.hasFormat("insviewer/prevxy/axisrange/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prevxy/axisrange/1.0");

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

void ItemXYWidget::onNewResultLoaded()
{
	_plot->updateAllMyCurve();
}

void ItemXYWidget::onUpdateSelectedCurve( XYItemTitle& title,bool isUpdateX )
{
	if(isUpdateX)//是否是更新X轴数据
		ui->selector->xContent(title);
	else
		ui->selector->yContent(title);
}






