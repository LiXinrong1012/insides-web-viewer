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
	@date    2015.7.3
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
			
	///将setting中存储的设置项显示到曲线设置界面
	void Setting2Control( const CurveSetting& settings );

	///将曲线设置界面中显示的设置项保存到settings
	void Control2Setting( CurveSetting& settings );
	
private slots:
	///当树选中条目改变时调用
	void	onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous );

	//curve setting slot
	void	on_btnCurveColor_Cliked();
	
	///当值改变时调用
	void	on_valueChanged( );

	///当向上或向下按钮点击时调用
	void    onUpDownBtnClicked();

private:
	///初始化界面
	void InitUI();

	///创建按钮的颜色图标
	QIcon	CreateBtnColorIcon( QColor c );

private:
	
	Ui::curveSetting*m_pUiCurveSetting;
	
	///导航树
	QTreeWidget*	m_pNavigation;

	///保存曲线设置的对象
	CurveSetting m_settings;

	///曲线视图
	QCustomPlot* m_plot;	

	///曲线设置的列表，保存所有曲线设置
	QList<CurveSetting> m_listSettings;

	///曲线列表，保存所有曲线
	QList<QCPCurve*>	m_curveList;
};
#endif