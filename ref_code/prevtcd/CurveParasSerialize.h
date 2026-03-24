#ifndef CurveParasSerialize_H
#define CurveParasSerialize_H

#include "CustomPlotViewSetting.h"

class QDataStream;
class QDlgPlotSetting;
class CurveSettingDialog;
class QFont;
class QColor;

class CurveParasSerialize
{
public:
	CurveParasSerialize( QDlgPlotSetting* plot, CurveSettingDialog* curve, QCustomPlot* p );
	~CurveParasSerialize();

	void saveSetting(QDataStream* data);
	void loadSetting(QDataStream* data );

private:

	void	SerializeFont( QDataStream& out, QFont f );
	void	DeserializeFont( QDataStream& in, QFont& f );


	void	SerializeColor( QDataStream& out, QColor c );
	void	DeserializeColor( QDataStream& in, QColor& c );

	//plot	
	void	SerializeAxisSetting( QDataStream& out, AxisSetting a );
	void	DeserializeAxisSetting( QDataStream& in, AxisSetting& a );

	//curve
	void GetGraphInfo( QCPCurve* p, CurveSetting& settings );
	void SetGraphInfo( QCPCurve* p, CurveSetting& settings );


private:

	QDlgPlotSetting*	m_plot;
	CurveSettingDialog* m_pCurve;

	QCustomPlot*		customPlot;			
};


#endif