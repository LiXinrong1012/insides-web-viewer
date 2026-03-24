#ifndef XYPOINTSTRACER_H
#define XYPOINTSTRACER_H

#include <QObject>
#include <QDialog>
#include "qcustomplot/qcustomplot.h"

class CustomXYPlot;
class QCPItemText;
class QCPItemTracer;
class QCPItemCurve;
class QCustomPlot;
class QCPGraph;
class QCPCurve;
class QCPAbstractPlottable;
class QCPAbstractItem;
class QMouseEvent;
class QAction;

/*!
	@brief   提供窗口显点模式的数据结构
	@date    2015.7.3
	@author  Jianjun
*/
class DataPointInfo
{
public:
	///x值 
	double x;

	///y值
	double y;

	///y最小值
	double min;

	///y最大值
	double max;

	///方差
	double rx;
};

/*!
	@brief  配合DataPointInfo，指明哪些数据值需要显示
	@date   2015.7.3
	@author Jianjun
*/
class DataPointShowFlag
{
public:
	///x值是否显示
	bool _xFlag;

	///y值是否显示
	bool _yFlag;

	///y最小值是否显示
	bool _minFlag;

	///y最大值是否显示 
	bool _maxFlag;

	///方差值是否显示 
	bool _rxFlag;
};

/*!
	@brief  dataTip模式类
	@date   2015.7.3
	@author Jianjuniz 
*/
class DataPointTip
{
public:
	///高亮点
	QCPGraph*				pointPositionHighlightedPoint;

	///显示的文字对象
	QCPItemText*			pointPositionText;

	///所在的曲线
	QCPAbstractPlottable*	pointPositionRelatedCurve;

	///跟踪系统对象
	QCPItemTracer*			pointPositionTracer;
};


	/*!
	*	封装跟显示点数据相关的功能。
	*	包括：
	*		1. 显示拾取点的数据值。
	*		2. 显示所有显示当前的值。
	*	
	*	@author	Wang jianjun
	*	@date	2014.10.13
	*/
class XYPointsTracer : public QObject
{
	Q_OBJECT

public:
	XYPointsTracer(QObject *parent,CustomXYPlot* plot);
	~XYPointsTracer();


	///是否处于显示单个点状态
	bool isShowPointData()const{return _showPointPositionFlag;}

	///是否显示十字线
	bool isShowTenLine()const{return _isShowTenLine;}

	///显示单个点
	void showPointData();

	///隐藏单个点
	void hidePointData();

	///是否处于显示动画中点状态
	bool isShowAllData()const{return _showAllPositionFlag;}

	///显示动画中time线所在所有点
	void showAllData();

	///隐藏动画中的所有点
	void hideAllData();

	///动画贞数改变是调用
	void resultCurrentFrameChanged();

	///单点模式下的某个点被点击的时候调用
	void onPlottableClicked( QCPAbstractPlottable *plottable);

	///得到单点action
	QAction* getPointAction(){return _pointAction;}

	///得到多点action
	QAction* getPointsAction(){return _pointsAction;}

	///得到显示方式的action
	QAction* getDatatipStyleAction(){return _datatipStyleAction;}

	///得到窗口类型action
	QAction* getWindowStyleAction(){return _windowStyleAction;}

	///获得或创建新的datatip
	QAction* getCreateNewDatatipAction(){return _createNewDatatipAction;}

	///获得删除所有dataTip 的 action
	QAction* getDeleteAllDatatipsAction(){return _deleteAllDatatipsAction;}

	///获得复制到剪切板的action
	QAction* getCopyToClipboardAction(){return _copyToClipboardAction;}

	///获得设置显示格式的action  
	QAction* getSetDisplayFormatAction(){return _setDisplayFormatAction;}

	///获得复制视图图片action
	QAction* getCopyViewImgAction(){return _copyViewToClipboard;}

	///获得复制y视图范围action
	QAction* getCopyYAction(){return _copyYAction;}

	///获得粘贴y视图范围action
	QAction* getPasteYAction(){return _pasteYAction;}

	/// 获得复制曲线action
	QAction* getCopyCurveAction(){return _copyCurveAction;}

	///获得粘贴曲线action
	QAction* getPasteCurveAction(){return _pasteCurveAction;}

	///取得text与点间距
	int getDistance(){return _distance;}
	
	///取得字体大小
	int getFontSize(){return _fontSize;}
	
	///取得当前的选中颜色
	QColor getSelectedColor(){return _selectedColor;}
	
	///取得有效小数点位
	int getVaildDouble(){return _vaildDouble;}

public slots:
	///当条目被点击时调用
	void onItemClicked(QCPAbstractItem *  item);
	
	///清除所有datatips
	void clearAllDatatips();

	///设置text与点间距
	void setDistance(int value);

	///设置字体大小
	void setFontSize(int value);
	
	///设置选中颜色
	void setSelectedColor(QColor color);
	
	///设置有效小数位
	void setVaildDouble(int value);
	
	///设置window格式下的相关信息
	void setDataPointShowFlag(DataPointShowFlag flag);

	///更新文字位置
	void updateTextPosition();

	///保存视图到文件
	void onSaveViewToFile();

protected:
	///重写事件过滤器
	bool eventFilter(QObject *obj, QEvent *event);

protected slots:
	/// 当曲线删除前调用
	void onCurveAboutToRemove(QCPAbstractPlottable* curve);

	///控制是否显示十字线
	void showOrHideTenLine();

	///设置显示方式为dataTip
	void setStyledatatip();

	///设置显示方式为窗口
	void setStyleWindow();

	///设置是否创建新点
	void setIsCreateNew(){_isNewCreateGraph = true;}

	///copy到剪切板
	void copyToClipboard();

	///显示线设置窗口
	void createDisplayFormatDialog();

	///复制y轴范围
	void copyYRange();

	///粘贴y轴范伟峰
	void pasteYRange();

	///复制曲线
	void copyCurve();

	///粘贴曲线
	void pasteCurve();

	///复制VIEW图到剪切板
	void copyViewToClipboard();

private:
	///是否已经初始化
	bool isInitialized()const{return (_customPlot!=NULL);}

	///清除点位置
	void clearPointPosition();

	///清除graph
	void clearGraph(QString graphName);

	///清除item
	void clearItem(QString itemName);

	///添加高亮点
	QCPGraph* addHighlightPoint(double x,double y);

	///更新点数据
	void updatePoint(double textX,double textY,double x,double y);

	///清除item,0为动画相关,1为单点相关,2为两者和,3为十字线
	void clearLineItem( int flag );

	///控制点的左右移动,nextPosition代表下一个位置,cu为当前线
	void movePointLeftOrRight(int nextPosition,QCPCurve* cu);

	///初始化点模式下的线
	void initClickedPoint(double textX,double textY,double x,double y);

	///是否是Datatip模式显示,false的话右下角显示窗口
	bool isDatatip()const{return _isDatatip;}

	///窗口模式显示x,y为点的实际坐标
	int showDataDialog(DataPointInfo dataPoint);

	///当创建新的datatip的时候之前数据不清除,调用initClickedPoint
	void createNewDatatip(double textX,double textY,double x,double y);

	///delete all datatips直接调用clearLineItem( int flag );

	///通过selectedGraphs得到选中点,拿数据
	void copySelectedDatatip();

	///初始textItem
	void initTextItem(QCPItemText *text,double positionX,double positionY,double showX,double showY);

	///初始tracerItem
	void initTracerItem(QCPItemTracer* tracer,QString name,QCPGraph* graph,double graphKey);

	///初始化动画下的time线所对应的所有点
	void initAllPoints(QCPGraph* graph,QCPItemTracer* tracer,QCPItemText* text,double time,qreal value);

	///得到所有graph
	QList<QCPGraph*> getGraphList(int pCount);

	///显示所有time下item
	void showAllItem(double time,int currentY);

	///得到当前x值
	double getCurrentX();

	///得到当前y值
	double getCurrentY();

	///添加十字线
	void addTenLine(double x,double y);

	///创建左与下的text框
	void addLeftBottomText(double x,double y);

	///删除选中的items
	void removeSelectedItems();

private:
	///曲线视图装饰类指针
	CustomXYPlot* _plot;

	/// 是否显示曲线点数据
	bool _showPointPositionFlag;

	///记录当前所点击的点的值是第几个
	int _pointKeyPosition;
	
	///高亮点
	QCPGraph*	_pointPositionHighlightedPoint;

	///文字显示对象
	QCPItemText*	_pointPositionText;

	///所在曲线
	QCPAbstractPlottable*	_pointPositionRelatedCurve;

	///用于追踪的对象
	QCPItemTracer* _pointPositionTracer;

	///存储所有的dataTip
	QList<DataPointTip> _dataPointTips;

	///记录是否需要添加
	bool _isNeedAdd;

	///记录当前text 距离的x值
	double _currentTextX;

	///记录当前text距离的y值
	double _currentTextY;

	///记录当关选中的text
	QCPItemText* _currentSelectedText;

	///记录是否显示动画下所有点
	bool _showAllPositionFlag;

	///记录当前被点击的曲线
	QCPCurve *_pointCu;

	///值的个数
	int _valueCount;

	///是否显示十字线与相关坐标
	bool _isShowTenLine;

	///存点击的text的文字
	QString _clickedTextString;

	///当前选中Item
	DataPointTip _currentSelectedDatatip;

	///当前选中点的x值
	double _selectedDataX;

	///当前选中点的y值
	double _selectedDataY;

	///真正的曲线视图指针
	QCustomPlot*	_customPlot;

	///右下角的窗口
	QDialog *_windowDialog;

	///记录是否传统模式显示
	bool _isDatatip;

	///是否新建点
	bool _isNewCreateGraph;

	///是否正在启用右键菜单
	bool _isRightButtonClick;

	///存十字两条线
	///十字线中的水平线
	QCPCurve* _hCurve;

	///十字线中的垂直线
	QCPCurve* _vCurve;

	///实时显示坐标的text
	QCPItemText* _currentText;

	///记录textItem到点的距离
	int _distance;

	///字体大小
	int _fontSize;

	///记录有效小数位数
	int _vaildDouble;

	///选中颜色
	QColor _selectedColor;

	///当前datapoingInfo
	DataPointInfo _currentDataPointInfo;

	///当前显示条目的标记
	DataPointShowFlag _currentDataPointInfoFlag;

	//action

	///单点模式action
	QAction* _pointAction;

	///多点模式action
	QAction* _pointsAction;

	///窗口模式显示风格action
	QAction* _windowStyleAction;

	///dataTip模式显示
	QAction* _datatipStyleAction;

	///创建新的点
	QAction* _createNewDatatipAction;
	
	///删除全部
	QAction* _deleteAllDatatipsAction;
	
	///copy去剪切板
	QAction* _copyToClipboardAction;
	
	///编辑显示格式
	QAction* _setDisplayFormatAction;
	
	///复制VIEW图到剪切板
	QAction* _copyViewToClipboard;

	///复制y轴范围action
	QAction* _copyYAction;

	///粘贴y轴范围
	QAction* _pasteYAction;

	///copy or paste curve

	///复制曲线action
	QAction* _copyCurveAction;

	///粘贴曲线action
	QAction* _pasteCurveAction;

};

#endif // XYPOINTSTRACER_H
