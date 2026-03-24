#ifndef ITEMCURVEWIDGET_H
#define ITEMCURVEWIDGET_H

#include <QWidget>
#include <QMessageBox>

#include "resultselectorwidget.h"

class QCustomPlot;
class CustomCurvePlot;
class AddCustomCurveDialog;

namespace Ui {class ItemCurveWidget;}
namespace Base{class View;}

/*!
	@brief   曲线视图界面类
	@date    2015.6.29
	@author  Jerry
*/
class ItemCurveWidget : public QWidget
{
	Q_OBJECT

public:
	ItemCurveWidget(QWidget *parent = 0);
	~ItemCurveWidget();

	///获得曲线视图装饰类指针
	CustomCurvePlot* getPlot();

	///设置上级view
	void setParentView(Base::View* view);

	///保存状态
	bool saveMyState(QDataStream& out);

	///加载状态
	bool loadMyState(QDataStream& in,qint64 dataSize);

public slots:
	///显示或隐藏标题
	void hideShowTitle();

	///显示视图设置
	void showViewSettings();

	///显示曲线设置
	void showCurveSetting();

	///保存设置状态
	void saveSettingState(QDataStream& out);

	///加载设置状态
	void loadSettingState(QDataStream& in);

	///显示添加自定义曲线框
	void showAddCustomCurveDialog();

	///以更新的方式打开自定义添加对话框
	void showAddCustomCurveDialogWithUpdate(CurveItemTitle title );

protected slots:
	///当项目增加时调用
	void onItemAdding(CurveItemTitle itemTitle);

	///当项目更新时调用 
	void onItemUpdating(CurveItemTitle itemTitle);

	///当新结果加载时调用
	void onNewResultLoaded();

private:
	Ui::ItemCurveWidget *ui;
	CustomCurvePlot*	_plot;
	AddCustomCurveDialog* _customCurveDialog;

	///获得结果条目，未实现
	INSIDES::IResultItem* getRelatedResultItem(const QString& itemname);
};

#endif // ITEMCURVEWIDGET_H
