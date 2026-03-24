#ifndef QDlgCurveSetting_H
#define QDlgCurveSetting_H

#include <QDialog>
#include <QList>

class QTreeWidgetItem;
class QTreeWidget;
class QCustomPlot;
class QCPGraph;
class QIcon;
class QColor;
class QDataStream;

namespace Ui {
		class curveSetting;
}

#include "CustomPlotViewSetting.h"

class CurveSettingDialog :public QDialog
{
	Q_OBJECT

public:
	CurveSettingDialog( QCustomPlot* p,QWidget* parent = 0 );
	~CurveSettingDialog();
	
	void updateCurves();
	void SetCustomPlot( QCustomPlot* plot );	
			
	void SetCurveSetting( const CurveSetting& settings );
	void GetCurveSetting( CurveSetting& settings );
	
private:

	void InitUI();


	void GetGraphInfo( QCPCurve* p, CurveSetting& settings );
	void SetGraphInfo( QCPCurve* p, CurveSetting& settings );

	QIcon	CreateBtnColorIcon( QColor c );

	private slots:
		void	onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous );
		//curve setting slot
		void	on_btnCurveColor_Cliked();
		void	on_valueChanged( );


private:
	
	Ui::curveSetting*m_pUiCurveSetting;
	
	QTreeWidget*	m_pNavigation;

	CurveSetting m_settings;
	QCustomPlot* m_plot;	

	QList<CurveSetting> m_listSettings;
};
#endif