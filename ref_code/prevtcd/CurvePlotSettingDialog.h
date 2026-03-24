#ifndef QDlgPlotSetting_H
#define QDlgPlotSetting_H

#include <QDialog>

#include "CustomPlotViewSetting.h"

class QTreeWidget;
class QTextEdit;
class QPushButton;
class QStackedWidget;
class QTreeWidgetItem;
class QIcon;
class QColor;
class QDataStream;
class QCustomPlot;

namespace Ui {
	class axisGeneral;
	class axisSetting;
	class curveSetting;
}

class QDlgPlotSetting : public QDialog
{
	Q_OBJECT
public:
	QDlgPlotSetting( QCustomPlot* p,QWidget* parent = 0 );
	~QDlgPlotSetting();

	void	SetCustomPlot( QCustomPlot* plot );
			
	void	SetPlotSetting( const CutsomPlotAxisSetting& settings );
	void	GetPlotSetting( CutsomPlotAxisSetting& settings );


	public slots:
	
		void	SetAxisSetting( QCPAxis* pAxis, AxisSetting settings );
		void	GetAxisSetting( QCPAxis* pAxis, AxisSetting& settings );
				
		void	PlotSettings( CutsomPlotAxisSetting s );

		void	UpdatePlotSetting();
				
		protected slots:
			void accept();
private:
	
	void	InitUI();
	QIcon	CreateBtnColorIcon( QColor c );

	private slots:
		void	onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous );
	//general slots
		void	on_btnfont_Cliked();
		void	on_btnColor_Cliked();
	//axis 
		void	on_btnAxiscolor_Cliked();
		void	on_btnGridcolor_Cliked();
		void	on_btnTitleFont_Cliked();
		void	on_btnLabelColor_Cliked();
		void	on_btnLabelFont_Cliked();
	//curve setting slot
		void	on_btnCurveColor_Cliked();

		void	on_valueChanged();

private:

	QTreeWidget*	m_pNavigation;

	QStackedWidget*	m_pParaWdgts;
	
	Ui::axisGeneral* m_pUiGeneral;
	Ui::axisSetting* m_pUiLeftAxis;
	Ui::axisSetting* m_pUiRightAxis;
	Ui::axisSetting* m_pUiTopAxis;
	Ui::axisSetting* m_pUiBottomAxis;
//	Ui::curveSetting*m_pUiCurveSetting;

	CutsomPlotAxisSetting m_settings;

	QCustomPlot* customPlot;
};
#endif