#ifndef CURVEPOINTSTRACER_H
#define CURVEPOINTSTRACER_H

#include <QObject>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QClipboard>
#include <QLabel>
#include <QDialog>
#include <QAction>

class CustomCurvePlot;
class QCPItemText;
class QCPItemTracer;
class QCPItemCurve;
class QCustomPlot;
class QCPGraph;
class QCPCurve;
class QCPAbstractPlottable;
class QCPAbstractItem;
class QMouseEvent;

/*!
	@brief   代表窗口模式下一个点信息数据
	@date    2015.6.26
	@author  Jianjun
*/
class DataPointInfo
{
public:
	///x坐标
	double x;

	///y坐标
	double y;

	///y坐标的最小值
	double min;

	///y坐标的最大值
	double max;

	///平方差
	double rx;
};

/*!
	@brief   代表窗口模式下哪些项需要显示
	@date    2015.6.26
	@author  Jianjun
*/
class DataPointShowFlag
{
public:
	///是否显示当前x坐标
	bool xFlag;

	///是否显示当前y坐标
	bool yFlag;

	///是否显示y最小值
	bool minFlag;

	///是否显示y最大值
	bool maxFlag;

	///是否显示平方差
	bool rxFlag;
};

/*!
	@brief   代表一个显点模式需要的信息
	@date    2015.6.26
	@author  Jianjun
*/
class DataPointTip
{
public:
	///高亮点
	QCPGraph*				pointPositionHighlightedPoint;

	///该点显示文字
	QCPItemText*			pointPositionText;

	///该点属于的曲线指针
	QCPAbstractPlottable*	pointPositionRelatedCurve;

	///点位置追踪对象
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
class CurvePointsTracer : public QObject
{
	Q_OBJECT

public:
	CurvePointsTracer(QObject *parent,CustomCurvePlot* plot);
	~CurvePointsTracer();
	
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

	///动画贞数改变时调用
	void resultCurrentFrameChanged();

	///单点模式下的某个点被点击的时候调用
	void onPlottableClicked( QCPAbstractPlottable *plottable);	

	///得到单点action
	QAction* getPointAction(){return _pointAction;}

	///得到多点action
	QAction* getPointsAction(){return _pointsAction;}

	///得到dataTip显示模式的action
	QAction* getDatatipStyleAction(){return _datatipStyleAction;}

	///获得window模式的action
	QAction* getWindowStyleAction(){return _windowStyleAction;}

	///获得创建新dataTip action
	QAction* getCreateNewDatatipAction(){return _createNewDatatipAction;}

	///获得删除所有dataTip点action
	QAction* getDeleteAllDatatipsAction(){return _deleteAllDatatipsAction;}

	///获得复制到剪切板action
	QAction* getCopyToClipboardAction(){return _copyToClipboardAction;}

	///获得设置显示格式action
	QAction* getSetDisplayFormatAction(){return _setDisplayFormatAction;}

	///获得复制视图图片action
	QAction* getCopyViewImgAction(){return _copyViewToClipboard;}

	///获得复制y轴 action
	QAction* getCopyYAction(){return _copyYAction;}

	///获得粘贴y轴action
	QAction* getPasteYAction(){return _pasteYAction;}

	/// 获得复制曲线 action
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
	///当项目被点击时
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

	///保存view到文件
	void onSaveViewToFile();

protected slots:
	/// 当曲线删除时调用
	void onCurveAboutToRemove(QCPAbstractPlottable* curve);

	///控制是否显示十字线
	void showOrHideTenLine();

	///设置显示方式
	void setStyledatatip();
	void setStyleWindow();
	///设置是否创新点
	void setIsCreateNew(){_isNewCreateGraph = true;}
	
	///copy到剪切板
	void copyToClipboard();
	///显示线设置窗口
	void createDisplayFormatDialog();

	///复制粘贴y轴
	void copyYRange();
	void pasteYRange();

	///复制曲线
	void copyCurve();

	///粘贴曲线
	void pasteCurve();

	///复制VIEW图到剪切板
	void copyViewToClipboard();

protected:
	///重写事件过虑器
	virtual bool eventFilter(QObject *obj, QEvent *event);
	
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

	///通过selectedGraphs得到选中点,拿数据
	void copySelectedDatatip();

	///初始textItem
	void initTextItem(QCPItemText *text,double positionX,double positionY,double showX,double showY);

	///初始tracerItem
	void initTracerItem(QCPItemTracer* tracer,QString name,QCPGraph* graph,double graphKey);

	///初始化动画下的time线所对应的所有点
	void initAllPoints(QCPGraph* graph,QCPItemTracer* tracer,QCPItemText* text,qreal textPosition,double time,qreal value);

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
	CustomCurvePlot* _plot;

	/// 是否显示曲线点数据
	bool _showPointPositionFlag;

	///记录当前所点击的点的值是第几个
	int _pointKeyPosition;

	///高亮点
	QCPGraph*	_pointPositionHighlightedPoint;

	///用于显示文字的text
	QCPItemText*	_pointPositionText;

	///对应的曲线指针
	QCPAbstractPlottable*	_pointPositionRelatedCurve;

	///位置信息追踪对象指针
	QCPItemTracer* _pointPositionTracer;

	///用来存储所有的dataTip点
	QList<DataPointTip> _dataPointTips;

	///记录是否需要添加
	bool _isNeedAdd;

	///记录当前text 距离的X值
	double _currentTextX;
	
	///记录当前text 距离Y值 
	double _currentTextY;

	///记录当前选中的text
	QCPItemText* _currentSelectedText;

	///记录是否显示动画下所有点
	bool _showAllPositionFlag;
	
	///记录当前选中的曲线
	QCPCurve *_pointCu;

	///记录有多少个坐标点
	int _valueCount;

	///是否显示十字线与相关坐标
	bool _isShowTenLine;

	///存点击的text的文字
	QString _clickedTextString;

	///当前选中Item
	DataPointTip _currentSelectedDatatip;
	
	///当前选中点的X坐标
	double _selectedDataX;

	///当前选中点的Y坐标
	double _selectedDataY;

	QCustomPlot*	_customPlot;

	///actions

	///单点模式action
	QAction* _pointAction;

	///多点模式action
	QAction* _pointsAction;

	///window显示风格action
	QAction* _windowStyleAction;

	///dataTip显示风格action
	QAction* _datatipStyleAction;

	///创建新的dataTip点
	QAction* _createNewDatatipAction;

	///删除全部dataTip点
	QAction* _deleteAllDatatipsAction;

	///复制到剪切板
	QAction* _copyToClipboardAction;

	///编辑显示格式
	QAction* _setDisplayFormatAction;
	
	///复制VIEW图到剪切板
	QAction* _copyViewToClipboard;
	
	///复制Y坐标 action
	QAction* _copyYAction;

	///粘贴Y坐标 action
	QAction* _pasteYAction;

	///复制曲线action
	QAction* _copyCurveAction;

	///粘贴曲线action
	QAction* _pasteCurveAction;

	///右下角的窗口
	QDialog* _windowDialog;

	///记录是否传统模式显示
	bool _isDatatip;

	///是否新建点
	bool _isNewCreateGraph;

	///是否正在启用右键菜单
	bool _isRightButtonClick;

	///存十字两条曲线
	QCPCurve* _hCurve;
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
};

#endif // CURVEPOINTSTRACER_H
