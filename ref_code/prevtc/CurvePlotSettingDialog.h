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

/*!
	@breef   曲线设置对话框
	@date    2015.6.26
	@author  Jianjun
*/
class CurvePlotSettingDialog : public QDialog
{
	Q_OBJECT
public:
	CurvePlotSettingDialog( QCustomPlot* p,QWidget* parent = 0 );
	~CurvePlotSettingDialog();

	///将曲线视图的状态先转存到setting，再设置到该设置界面
	void	SetCustomPlot( QCustomPlot* plot );
			
	///将setting中的存储项设置到该设置界面
	void	Setting2Control( const CutsomPlotAxisSetting& settings );

	///将该设置界面中的状态存储到setting
	void	Control2Setting( CutsomPlotAxisSetting& settings );

	///将曲线视图的状态转存到setting,再设置到该设置界面
	void	Plot2Control();

private slots:
	///当树节点改变时调用
	void	onTreeItemChanged( QTreeWidgetItem* current, QTreeWidgetItem* previous );
	//general slots
	///当字体设置按钮点击时调用 
	void	on_btnfont_Cliked();

	///当颜色设置按钮点击时调用
	void	on_btnColor_Cliked();

	///当legend字体设置按钮点击时调用 
	void	on_legendBtnfont_clicked();
	//axis 

	///当坐标轴颜色设置按钮点击时调用
	void	on_btnAxiscolor_Cliked();

	///当网格颜色设置按钮点击时调用
	void	on_btnGridcolor_Cliked();

	///当标题字体设置按钮点击时调用
	void	on_btnTitleFont_Cliked();

	///当坐标轴标签字颜色更改按钮点击时调用
	void	on_btnLabelColor_Cliked();

	///当坐标轴标签字体更改按钮点击时调用
	void	on_btnLabelFont_Cliked();

	//curve setting slot

	///当曲线颜色更改按钮点击时调用，未实现
	void	on_btnCurveColor_Cliked();

	///当值改变时调用
	void	on_valueChanged();

	///激活index项
	void	onActived(int index);
	
private:
	///初始化界面
	void	InitUI();

	///通过给定颜色c创建按钮颜色图标
	QIcon	CreateBtnColorIcon( QColor c );

private:

	QTreeWidget*	m_pNavigation;

	QStackedWidget*	m_pParaWdgts;
	
	///普通设置界面
	Ui::axisGeneral* m_pUiGeneral;

	///左坐标轴设置界面
	Ui::axisSetting* m_pUiLeftAxis;

	///右坐标轴设置界面
	Ui::axisSetting* m_pUiRightAxis;

	///上坐标轴设置界面
	Ui::axisSetting* m_pUiTopAxis;

	///下坐标轴设置界面
	Ui::axisSetting* m_pUiBottomAxis;

//	Ui::curveSetting*m_pUiCurveSetting;

	///保存所有设置参数
	CutsomPlotAxisSetting m_settings;

	///曲线视图
	QCustomPlot* customPlot;

	///是否用户操作
	bool _userHandle;
};
#endif