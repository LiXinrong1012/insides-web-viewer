#include "prevtcd.h"

#include "CurveSettingDialog.h"
#include "CurvePlotSettingDialog.h"
#include "CurveParasSerialize.h"

static QCustomPlot*	_plot=0;
static QDlgPlotSetting* plotSetting=new QDlgPlotSetting(_plot,0);
static CurveSettingDialog* curveSetting=new CurveSettingDialog(_plot,0);

void setCustomPlot( QCustomPlot* plot )
{
	_plot=plot;
}

void openViewSetting()
{
	plotSetting->SetCustomPlot( _plot );
	plotSetting->UpdatePlotSetting();
	plotSetting->show();
}

void openCurveSetting()
{
	curveSetting->SetCustomPlot( _plot );
	curveSetting->updateCurves();
	curveSetting->show();
}

void saveSetting( QDataStream* data )
{	
	CurveParasSerialize serialize( plotSetting, curveSetting, _plot);
	serialize.saveSetting( data );
}

void loadSetting( QDataStream* data )
{
	CurveParasSerialize serialize( plotSetting, curveSetting, _plot);
	serialize.loadSetting( data ); 
}
