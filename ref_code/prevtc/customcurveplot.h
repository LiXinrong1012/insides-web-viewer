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

class CurvePointsTracer;
struct AxisSetting;

#include "prevtc/resultselectorwidget.h"

/*!
*	This class is a decorator for class QCustomPlot.
*	@author	Jerry He
*	@date	2014.4.2
*/
class CustomCurvePlot : public QObject, public INSIDES::IResultListener
{
	Q_OBJECT

public:
	CustomCurvePlot(QObject *parent,QCustomPlot* plot);
	~CustomCurvePlot();

	//void setCustomPlot(QCustomPlot* plot){_customPlot=plot;}
	///获得真正的QCustomPlot对象指针
	QCustomPlot* getCustomPlot()const{return _customPlot;}

	///获得CurvePointsTracer对象指针
	CurvePointsTracer* getPointsTracer()const{return _curvePointsTracer;}

	///添加曲线
	bool addMyCurve(const CurveItemTitle& itemTitle);
	

	///更新自定义曲线
	bool updateMyCurve(const CurveItemTitle& itemTitle);

	///更新所有曲线
	bool updateAllMyCurve();

	///获得Legend是否可拖动，未启用
	bool getLegendDrag()const{return _legendDrag;}

	///设置Legend是否可拖动，未启用
	void setLegendDrag(const bool b){_legendDrag = b;}

	///获得该曲线的title
	CurveItemTitle* getCurveItemTitle(QCPAbstractPlottable* item);

	///曲线title列表
	QList<CurveItemTitle>	_curveItemTitleList;

signals:
	///曲线将要被删除时发出
	void curveAboutToRemove(QCPAbstractPlottable* curve);

	///添加曲线curve
	void curveAdded(QCPAbstractPlottable* curve);

	///视图数据更新
	void plotDataUpdated();

	///更新text位置
	void updateTextPosition();

	///更新选中曲线
	void updateCurve(CurveItemTitle title);

public slots:
	/// 显示所有曲线
	void viewAll();

	/// 导出所有曲线的值到文件中
	void exportAllCurves();

	///从给定文件读取所有曲线值
	void importCurves();

	/// 显示单个点的坐标
	void showPointPosition();

	///显示动画时点坐标
	void showAllPosition();

	/// 显示数据交换菜单
	void showExchangeDataMenu();

	/// 导入或导出配置
	void showConfigMenu();

protected:
	///当结果当前帧改变时调用 
	virtual void onResultCurrentFrameChanged();

	///重写事件过滤器
	virtual bool eventFilter ( QObject * o, QEvent * e );

protected slots:
	///曲线点击时调用
	void graphClicked(QCPAbstractPlottable *plottable);

	///移动legend
	void moveLegend();

	///菜单槽
	void contextMenuRequest(QPoint pos);

	///删除所有点
	void removeAllGraphs();

	///删除选中点
	void removeSelectedGraph();

	///当鼠标中键滚动时调用 
	void mouseWheel();

	///当鼠标按下时调用
	void mousePress();

	///选择改变时调用
	void selectionChanged();

	///当标题被双击时调用
	void titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title);

	///当坐标轴Label被双击时调用
	void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);

	///当Legend被双击时调用
	void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);

	///复制x轴范围
	void copyXRange();

	///粘贴x轴范围
	void pasteXRange();

	///当鼠标悬浮时调用
	void onHovered();

	///将要隐藏时调用
	void onAboutToHide();

	///更新选中的曲线
	void updateSelectCurve();

	void testAddMyCurve();

private:
	///对当前界面进行必要初始化
	bool init();

	///添加时间曲线
	void addTimeLine();

	///获得正确的结果项
	INSIDES::IResultItem* getRelatedResultItem( const QString& itemname );

	///某项title转为数据
	bool itemTitle2Data( const CurveItemTitle& itemTitle, 
		QVector<double>& xlist,QVector<double>& ylist);

	///某项title转为自定义数据
	bool itemTitle2DataCustom( const CurveItemTitle& itemTitle, 
		QVector<double>& xlist,QVector<double>& ylist);

	///设置初始化曲线属性
	void setInitialCurveProperty(QCPCurve* curve);

	///添加曲线到视图
	void addCurveIntoPlot(QCPCurve* curve);

	///更新十字线
	void updateTimeLine();

private slots:
	///鼠标移动时信号响应
	void mouseMoveSignal(QMouseEvent *event);

	///鼠标按下时信号响应
	void mousePressSignal(QMouseEvent *event);

	///鼠标松开时信号响应
	void mouseReleaseSignal(QMouseEvent *event);

	///重画之前调用
	void beforeReplot();

	///legend拖动打开或关闭
	void legendDragOnOrOff();

private:
	QCustomPlot* _customPlot;

	//当前使用颜色值的索引
	int		_currentColorIndex;	
	
	///id号拼接成的字符串
	QString		_idStr;
	
	///配置菜单
	QMenu* _configMenu;

	///配置路径
	QString _configDir;

	///显示点数据追踪类指针
	CurvePointsTracer*	_curvePointsTracer;

	///legend是否支持拖拽
	bool _legendDrag;

	///legend是否处理拖动中
	bool draggingLegend;

	///legend拖动的起点
	QPointF dragLegendOrigin;

	///以更新的形式显示自定义曲线窗口
	QAction* _updateSelectCurveAction;

};

#endif // CUSTOMCURVEPLOT_H
