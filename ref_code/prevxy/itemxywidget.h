#ifndef ITEMXYWIDGET_H
#define ITEMXYWIDGET_H

#include <QWidget>
#include "xyitemtitle.h"

namespace Ui {class ItemXYWidget;};
namespace Base{class View;}
namespace INSIDES{
	class IResultItem;
}

class QCustomPlot;
class CustomXYPlot;
class AddCustomCurveDialog;

/*!
	@brief   曲线视图的包装界面类
	@date    2015.7.3
	@author  Jerry
*/
class ItemXYWidget : public QWidget
{
	Q_OBJECT

public:
	ItemXYWidget(QWidget *parent = 0);
	~ItemXYWidget();

	///获得曲线视图
	CustomXYPlot* getPlot();

	///设置上级view
	void setParentView(Base::View* view);

	///保存状态设置
	bool saveMyState(QDataStream& out);

	///载入状态设置
	bool loadMyState(QDataStream& in,qint64 dataSize);

public slots:
	///显示或隐藏标题
	void hideShowTitle();

	///显示视图设置对话框
	void showViewSettings();

	///显示曲线设置对话框
	void showCurveSetting();

	///保存设置状态
	void saveSettingState(QDataStream& out);

	///载入设置状态
	void loadSettingState(QDataStream& in);

	///更新选中曲线
	void onUpdateSelectedCurve(XYItemTitle& title,bool isUpdateX);

protected slots:
	///当条目添加时调用
	void onItemAdding(XYItemTitle itemTitle);

	///当条目更新时调用
	void onItemUpdating(XYItemTitle itemTitle);

	///当新的结果加载时调用 
	void onNewResultLoaded();

private:
	Ui::ItemXYWidget *ui;

	///曲线视图装饰类指针
	CustomXYPlot*	_plot;
	
	///获得相关结果条目
	INSIDES::IResultItem* getRelatedResultItem(const QString& itemname);
};

#endif // ITEMXYWIDGET_H
