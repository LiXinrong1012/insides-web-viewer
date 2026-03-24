#ifndef QDlgCurveSetting_H
#define QDlgCurveSetting_H

#include <QDialog>
#include <QList>

#include "CustomPlotViewSetting.h"

class QTreeWidgetItem;
class QTreeWidget;
class QCustomPlot;
class QIcon;
class QColor;
class QDataStream;
class QCPCurve;

namespace Ui {
		class curveSetting;
}

/*!
	@brief   曲线设置对话框
	@date    2015.6.26
	@author  Jerry
*/
class CurveSettingDialog :public QDialog
{
	Q_OBJECT

public:
	CurveSettingDialog( QCustomPlot* p,QWidget* parent = 0 );
	~CurveSettingDialog();
	
	///更新所有曲线
	void updateCurves();

	///设置曲线视图
	void SetCustomPlot( QCustomPlot* plot );	
	
	///从setting到控制界面
	void Setting2Control( const CurveSetting& settings );

	///从控制界面到setting
	void Control2Setting( CurveSetting& settings );

private slots:
	///当树节点改变时调用
	void	onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous );

	//curve setting slot
	///当曲线颜色设置按钮点击时调用
	void	on_btnCurveColor_Cliked();

	///当数值发生改变时调用
	void	on_valueChanged( );

	///当向上向下按钮点击时调用
	void    onUpDownBtnClicked();

private:
	///初始化界面
	void InitUI();

	///创建颜色按钮图标
	QIcon	CreateBtnColorIcon( QColor c );
	
private:
	
	Ui::curveSetting* m_pUiCurveSetting;
	
	QTreeWidget*	m_pNavigation;

	CurveSetting m_settings;
	QCustomPlot* m_plot;	

	///曲线设置列表
	QList<CurveSetting> m_listSettings;

	///曲线列表
	QList<QCPCurve*>	m_curveList;
};
#endif