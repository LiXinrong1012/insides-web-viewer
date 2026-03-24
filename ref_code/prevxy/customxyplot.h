#ifndef CUSTOMCURVEPLOT_H
#define CUSTOMCURVEPLOT_H

#include <QObject>
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>
#include <QKeyEvent>
#include "qcustomplot/qcustomplot.h"
#include "precore/ResultDocument.h"
class QCustomPlot;
class QCPAbstractPlottable;
class QCPPlotTitle;
class XYPointsTracer;
struct AxisSetting;

#include "prevtc/resultselectorwidget.h"
#include "xyitemtitle.h"

/*!
*	This class is a decorator for class QCustomPlot.
*	@author	jianjun
*	@date	2015.1.30
*/
class CustomXYPlot : public QObject, public INSIDES::IResultListener
{
	Q_OBJECT

public:
	CustomXYPlot(QObject *parent,QCustomPlot* plot);
	~CustomXYPlot();

	//void setCustomPlot(QCustomPlot* plot){_customPlot=plot;}

	///获得曲线视图指针
	QCustomPlot* getCustomPlot()const{return _customPlot;}

	///获得点追踪对象指针
	XYPointsTracer* getPointsTracer()const{return _xyPointsTracer;}

	///添加曲线通过itemTitle
	bool addMyCurve(const XYItemTitle& itemTitle);
	
	///更新自定义曲线
	bool updateMyCurve(const XYItemTitle& itemTitle);

	///更新所有曲线
	bool updateAllMyCurve();

	///Legend是否可以拖曳
	bool getLegendDrag()const{return _legendDrag;}

	///设置Legend是否可以拖曳
	void setLegendDrag(const bool b){_legendDrag = b;}

	///获得曲线的条目信息
	XYItemTitle* getCurveItemTitle(QCPAbstractPlottable* item);

public slots:
	/// 显示所有曲线
	void viewAll();

	/// 导出所有曲线的值到文件中
	void exportAllCurves();

	///导入所有曲线
	void importCurves();

	/// 显示单个点的位置坐标
	void showPointPosition();

	///显示所有点的位置坐标
	void showAllPosition();

	/// 显示数据交换菜单
	void showExchangeDataMenu();

	/// 导入或导出配置
	void showConfigMenu();

public:
	///曲线条目列表
	QList<XYItemTitle>	curveItemTitleList;

signals:
	///曲线被删除前发出
	void curveAboutToRemove(QCPAbstractPlottable* curve);

	///曲线添加后发出
	void curveAdded(QCPAbstractPlottable* curve);

	///视图数据更新时发出
	void plotDataUpdated();
	
	///更新数字位置
	void updateTextPosition();

	///更新选中曲线
	void updateSelectedCurve(XYItemTitle& title,bool isX);

protected slots:
	///曲线被点击时调用
	void graphClicked(QCPAbstractPlottable *plottable);

	///移动Legend
	void moveLegend();

	///菜单响应槽
	void contextMenuRequest(QPoint pos);

	///移除所有曲线
	void removeAllGraphs();

	///移除选中曲线
	void removeSelectedGraph();

	///鼠标中轮滚动时调用
	void mouseWheel();

	///鼠标按下时调用
	void mousePress();

	///选择改变时调用
	void selectionChanged();

	///当标题被双击时调用
	void titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title);

	///当坐标轴label被双击时调用 
	void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);

	///当Legend被双击时调用
	void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);

	///复制x轴的范围
	void copyXRange();

	///粘贴x轴的范围
	void pasteXRange();

	///当相闻覆盖时调用
	void onHovered();

	///当隐藏前调用 
	void onAboutToHide();

	///更新选中的曲线
	void updateSelectedCurve();

private slots:
	///鼠标移动信号发出
	void mouseMoveSignal(QMouseEvent *event);

	///鼠标按下信号发出
	void mousePressSignal(QMouseEvent *event);

	///相闻松开信号发出
	void mouseReleaseSignal(QMouseEvent *event);

	///在视图重绘之前调用
	void beforeReplot();

	///Legend拖曳打开或关闭
	void legendDragOnOrOff();

protected:
	///当当前结果帧数改变时调用
	virtual void onResultCurrentFrameChanged();

	///获得相关的结果条目
	INSIDES::IResultItem* getRelatedResultItem( const QString& itemname );

	///将曲线属性信息转为分别的数据
	bool itemTitle2Data( const QString& content,int secIndex,int subsecIndex,int subsubsecIndex,int nodeElemIndex,QVector<double>& list);

	///将曲线属性信息转化为自定义数据
	bool itemTitle2DataCustom( const QString& content, 
		QVector<double>& list);

	///设置初始化曲线属性
	void setInitialCurveProperty(QCPCurve* curve);

	///添加曲线到视图
	void addCurveIntoPlot(QCPCurve* curve);

	///重写事件过滤器
	virtual bool eventFilter ( QObject * o, QEvent * e );

private:
	///更新选中曲线
	void updateCurve(XYItemTitle title,bool isX);

	///对曲线视图进行必要的初始化
	bool init();
private:
	///真正的曲线视图指针
	QCustomPlot* _customPlot;

	//当前使用颜色值的索引
	int		_currentColorIndex;

	///曲线样式id字符串
	QString		_idStr;

	///配置菜单
	QMenu* _configMenu;

	///配置路径
	QString _configDir;

	///点追踪相关包装类指针
	XYPointsTracer*	_xyPointsTracer;

	///存储legend是否可拖曳
	bool _legendDrag;

	///legend是否处理拖动中
	bool draggingLegend;

	///legend拖动的起点
	QPointF dragLegendOrigin;
	
	///更新X数据
	QAction* _updateSelectCurveXAction;
	
	///更新Y数据
	QAction* _updateSelectCurveYAction;

};

#endif // CUSTOMCURVEPLOT_H
