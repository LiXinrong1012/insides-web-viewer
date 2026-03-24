#include "xypointstracer.h"
#include "resultselectorwidget.h"

#include "qcustomplot/qcustomplot.h"

#include "precore/IResults.h"
#include "precore/ResultDocument.h"

#include "base/Console.h"

#include "customxyplot.h"
#include "xycurve.h"
#include "showsettingdialog.h"

#include <process.h>
#include <QFileDialog>
#include <QAction>
#include <QLabel>
#include <QApplication>
#include <QClipboard>
#include <QObject>
#include <QDesktopWidget>
#include <QVBoxLayout>

using namespace INSIDES;
using namespace Base;
using namespace std;

XYPointsTracer::XYPointsTracer(QObject *parent,CustomXYPlot* plot)
	: QObject(parent)
	,_showPointPositionFlag(false)
	,_pointPositionHighlightedPoint(NULL)
	,_pointPositionText(NULL)
	,_pointPositionRelatedCurve(NULL)

	,_showAllPositionFlag(false)
	,_hCurve(NULL)
	,_vCurve(NULL)
	,_currentText(NULL)
	,_isShowTenLine(false)
	,_isDatatip(true)
	,_windowDialog(NULL)
	,_currentSelectedDatatip()
	,_selectedDataX(0.615)
	,_selectedDataY(0.616)
	,_isNewCreateGraph(false)
	,_isNeedAdd(false)
	,_pointKeyPosition(0)
	,_distance(10)
	,_fontSize(13)
	,_vaildDouble(4)
	,_selectedColor(Qt::yellow)
	,_currentTextX(0)
	,_currentTextY(0)
	,_isRightButtonClick(false)
	,_currentSelectedText(NULL)
	,_plot(plot)
{
	_customPlot=plot->getCustomPlot();
	_customPlot->installEventFilter(this);
	_currentDataPointInfoFlag._xFlag = true;
	_currentDataPointInfoFlag._yFlag = true;
	_currentDataPointInfoFlag._maxFlag = false;
	_currentDataPointInfoFlag._minFlag = false;
	_currentDataPointInfoFlag._rxFlag = false;

	_pointAction=new QAction("Pick point",0);
	_pointAction->setIcon(QIcon(":/resources/menu/a035x16x16.png"));
	connect(_pointAction,SIGNAL(triggered()),plot,SLOT(showPointPosition()));
	_pointAction->setCheckable(true);
	_pointAction->setChecked(false);

	_pointsAction=new QAction("Show points value",0);
	_pointsAction->setIcon(QIcon(":/resources/menu/a036x16x16.png"));
	connect(_pointsAction,SIGNAL(triggered()),plot,SLOT(showAllPosition()));
	_pointsAction->setCheckable(true);
	_pointsAction->setChecked(false);

	_datatipStyleAction = new QAction("datatip",0);
	connect(_datatipStyleAction,SIGNAL(triggered()),this,SLOT(setStyledatatip()));

	_windowStyleAction = new QAction("window",0);
	connect(_windowStyleAction,SIGNAL(triggered()),this,SLOT(setStyleWindow()));

	_createNewDatatipAction = new QAction("create new datatip",0);
	connect(_createNewDatatipAction,SIGNAL(triggered()),this,SLOT(setIsCreateNew()));

	_deleteAllDatatipsAction = new QAction("delete all datatips",0);
	connect(_deleteAllDatatipsAction,SIGNAL(triggered()),this,SLOT(clearAllDatatips()));

	_copyToClipboardAction = new QAction("copy text to clipboard",0);
	connect(_copyToClipboardAction,SIGNAL(triggered()),this,SLOT(copyToClipboard()));

	_setDisplayFormatAction = new QAction("edit display format",0);
	connect(_setDisplayFormatAction,SIGNAL(triggered()),this,SLOT(createDisplayFormatDialog()));

	_copyYAction = new QAction("y range",0);
	connect(_copyYAction,SIGNAL(triggered()),this,SLOT(copyYRange()));

	_pasteYAction = new QAction("y range",0);
	connect(_pasteYAction,SIGNAL(triggered()),this,SLOT(pasteYRange()));

	_copyCurveAction = new QAction("copy selected curve",0);
	connect(_copyCurveAction,SIGNAL(triggered()),this,SLOT(copyCurve()));

	_pasteCurveAction = new QAction("paste selected curve",0);
	connect(_pasteCurveAction,SIGNAL(triggered()),this,SLOT(pasteCurve()));

	_copyViewToClipboard = new QAction("copy view image to clipboard",0);
	connect(_copyViewToClipboard,SIGNAL(triggered()),this,SLOT(copyViewToClipboard()));

	connect(plot,SIGNAL(curveAdded(QCPAbstractPlottable*)),
		this,SLOT(onCurveAdded(QCPAbstractPlottable*)));
	connect(plot,SIGNAL(curveAboutToRemove(QCPAbstractPlottable*)),
		this,SLOT(onCurveAboutToRemove(QCPAbstractPlottable*)));
	connect(plot,SIGNAL(plotDataUpdated()),this,SLOT(onPlotDataUpdated()));
	_customPlot->legend->installEventFilter(this);
}

XYPointsTracer::~XYPointsTracer()
{
}

void XYPointsTracer::showPointData()
{
	_showPointPositionFlag=true;
	_pointsAction->setChecked(false);
	hideAllData();
	clearPointPosition();
}

void XYPointsTracer::hidePointData()
{
	_showPointPositionFlag=false;
	if (_windowDialog)
		_windowDialog->close();

	clearPointPosition();
	clearLineItem(2);
	_customPlot->replot();
}

void XYPointsTracer::clearLineItem( int flag )
{
	QStringList itemList;
	switch (flag)
	{
	case 0:
		{
			clearGraph("graphItem");
			itemList<<"textItem"<<"tracerItem"<<"curveItem";
		}
		break;
	case 1:
		{
			clearGraph("pointGraph");
			itemList<<"pointText"<<"pointTracer"<<"pointArrow"<<"tenLine"<<"leftBottomText"<<"highlightedPoint";
		}
		break;
	case 2:
		{
			clearGraph("graphItem");
			clearGraph("pointGraph");
			itemList<<"pointText"<<"pointTracer"<<"pointArrow"<<"textItem"<<"tracerItem"<<"curveItem"<<"tenLine"<<"leftBottomText"<<"highlightedPoint";
		}
		break;
	case 3:
		itemList<<"tenLine"<<"leftBottomText";
		break;
	}
	for (int i=0;i<itemList.count();i++)
		clearItem(itemList[i]);

	_customPlot->replot();
}

void XYPointsTracer::clearGraph( QString graphName )
{
	for(int i=_customPlot->graphCount()-1;i>=0;i--)
	{
		QString s = _customPlot->graph(i)->name();
		if (s == graphName)
			_customPlot->removeGraph(i);
	}
}

void XYPointsTracer::clearItem( QString itemName )
{
	for(int i=_customPlot->itemCount()-1;i>=0;i--)
	{
		QString s = _customPlot->item(i)->objectName();
		if (s== itemName)
			_customPlot->removeItem(i);
	}
}

void XYPointsTracer::onPlottableClicked( QCPAbstractPlottable *plottable)
{
	///如果点击的是鼠标右键直接返回
	if(!isInitialized() || !isShowPointData() || _customPlot->selectedPlottables().count() == 0 || _isRightButtonClick)
		return;

	DataPointInfo info;
	_isNeedAdd = false;
	if (_isNewCreateGraph && isDatatip())
		_isNeedAdd = true;

	QPoint pos= QCursor::pos();
	QPoint localPos = _customPlot->mapFromGlobal(pos);//用于比对
	_pointCu = qobject_cast<QCPCurve*>(_customPlot->selectedPlottables()[0]);
	if(!_pointCu)
		return;

	QMap<double,double> points ;
	QCPCurveDataMap *data = _pointCu->data();
	for(QCPCurveDataMap::Iterator b=data->begin();b!=data->end();++b)
		points.insert(b->key,b->value);

	double x,y,maxY = -1000,minY = 1000,min = 20000.0;
	_pointKeyPosition =0;
	_valueCount=0;
	double selectX = _customPlot->xAxis->pixelToCoord(localPos.x());//当前对于曲线面中X，Y值
	double selectY = _customPlot->yAxis->pixelToCoord(localPos.y());

	for(QMap<double,double>::Iterator iter = points.begin();iter!=points.end();iter++)
	{
		double d1 = iter.key();
		double d2 = iter.value();
		double powX = qPow(selectX - d1,2);
		double powY = qPow(selectY - d2,2);
		double tmp = qSqrt(powX + powY);
		if (tmp<min)
		{
			min = tmp;
			x = d1;
			y = d2;
			_pointKeyPosition = _valueCount;
		}
		if (d2>maxY)
			maxY = d2;
		if (d2<minY)
			minY = d2;
		_valueCount++;
	}

	if ((_pointPositionHighlightedPoint == NULL || _isNeedAdd ) )
		_pointPositionHighlightedPoint=addHighlightPoint(x,y);

	double textX = x;
	double textY = y;
	double sizeX =_customPlot->xAxis->range().size();
	double sizeY = _customPlot->yAxis->range().size();
	textX += sizeX/(20-_distance);
	textY += sizeY/(20-_distance);

	info.x = x;
	info.y = y;
	info.max = maxY;
	info.min = minY;
	_selectedDataX = x;
	_selectedDataY = y;

	if (isDatatip())
	{
		if (_pointPositionText && !_isNeedAdd)
			updatePoint(textX,textY,x,y);
		else
			initClickedPoint(textX,textY,x,y);
	}
	else
		showDataDialog(info);

	_isNewCreateGraph = false;
}

void XYPointsTracer::resultCurrentFrameChanged()
{
	if(!isInitialized()|| !isShowAllData())
		return;

	int currentFrame = myResultDocument()->getResults()->getCurrentFrame();

	if (currentFrame == 0)
	{
		clearLineItem(2);
		clearLineItem(2);
		showAllItem(0,0);
		return;
	}
	else
	{
		clearLineItem(1);
		clearLineItem(1);
	}

	QList<QCPAbstractPlottable*> temCurves;
	int a = _customPlot->plottableCount();
	int b = _customPlot->graphCount();
	int pCount = a - b ; 

	for (int i =0;i<pCount;i++)
		temCurves.push_back(_customPlot->plottable(i));

	if (temCurves.count()>0)
	{
		QList<QCPCurve*> curves;
		for (int aa=0;aa<temCurves.count();aa++)
			curves.push_back((QCPCurve*)temCurves[aa]);

		QList<double> xValueList, yValueList;
		for (int i=0;i<curves.count();i++)
		{
			QCPCurveDataMap *map = curves[i]->data();
			int n=0;
			for (QCPCurveDataMap::Iterator it = map->begin();it!=map->end();it++)
			{
				if(n == currentFrame)
				{
					xValueList.push_back(it->key);
					yValueList.push_back(it->value);
					break;
				}
				n++;
			}
		}

		QList<QCPGraph*> graphList;
		graphList = getGraphList(pCount);
		for (int ii= 0;ii<yValueList.count();ii++)
		{
			QVector<double> v1,v2;
			v1.push_back(xValueList[ii]);
			v2.push_back(yValueList[ii]);
			graphList[ii]->setData(v1,v2);
			graphList[ii]->setPen(curves[ii]->pen());
			graphList[ii]->setName("graphItem");
			graphList[ii]->setPen(QPen(Qt::NoPen));

			QList<double> temPos;

			QList<QCPItemText*> textList;
			QList<QCPItemTracer*> tracerList;
			if (_customPlot->itemCount() == 0)
			{
				for (int z=0;z<pCount;z++)
				{
					QCPItemText* temText = new QCPItemText(_customPlot);
					temText->setObjectName("textItem");
					textList.push_back(temText);
					_customPlot->addItem(textList[z]);

					QCPItemTracer* temTracer = new QCPItemTracer(_customPlot);
					temTracer->setObjectName("tracerItem");
					tracerList.push_back(temTracer);
					_customPlot->addItem(tracerList[z]);
				}
			}
			else
			{
				for (int z=0;z<_customPlot->itemCount();z++)
				{
					QString s = _customPlot->item(z)->objectName();
					if (s=="textItem")
					{
						QCPItemText* temText = (QCPItemText*)_customPlot->item(z);
						textList.push_back(temText);
					}

					if (s=="tracerItem")
					{
						QCPItemTracer* temTracer = (QCPItemTracer*)_customPlot->item(z);
						tracerList.push_back(temTracer);
					}
				}
			}
			initAllPoints(graphList[ii],tracerList[ii],textList[ii],xValueList[ii],yValueList[ii]);
		}
	}
}

QList<QCPGraph*> XYPointsTracer::getGraphList( int pCount )
{
	QList<QCPGraph*> graphList;
	int num = _customPlot->graphCount();
	if (num == pCount)
	{
		for (int i=0;i<pCount;i++)
			graphList.push_back(_customPlot->graph(i));
	}
	else
	{
		for (int i=0;i<pCount;i++)
			graphList.push_back(_customPlot->addGraph());
	}
	return graphList;
}

void XYPointsTracer::clearPointPosition()
{
	if(_dataPointTips.count()!= 1)
	{
		for (int i=0;i<_dataPointTips.count();i++)
		{
			if (_dataPointTips[i].pointPositionRelatedCurve == _pointPositionRelatedCurve)
			{
				_customPlot->removeGraph(_dataPointTips[i].pointPositionHighlightedPoint);
				_customPlot->removeItem(_dataPointTips[i].pointPositionText);
				_customPlot->removeItem(_dataPointTips[i].pointPositionTracer);
				_dataPointTips.removeAt(i);
				i--;
			}
		}
	}
	if(_pointPositionHighlightedPoint){
		_customPlot->removeGraph(_pointPositionHighlightedPoint);
		_pointPositionHighlightedPoint=NULL;
	}

	_pointPositionRelatedCurve=NULL;

	if(_pointPositionText){
		_customPlot->removeItem(_pointPositionText);
		_pointPositionText=NULL;
	}
	if(_pointPositionTracer){
		_customPlot->removeItem(_pointPositionTracer);
		_pointPositionTracer=NULL;
	}
	if (_vCurve)
	{
		_customPlot->removePlottable(_vCurve);
		_vCurve = NULL;
	}
	if (_hCurve)
	{
		_customPlot->removePlottable(_hCurve);
		_hCurve = NULL;
	}
	if (_currentText)
	{
		_customPlot->removeItem(_currentText);
		_currentText = NULL;
	}
}

QCPGraph* XYPointsTracer::addHighlightPoint(double x,double y)
{
	QVector<double> vectX,vectY;
	vectX.push_back(x);
	vectY.push_back(y);

	QCPGraph *graph = _customPlot->addGraph();
	graph->setSelectable(false);
	graph->setName("highlightedPoint");
	graph->setData(vectX,vectY);
	graph->removeFromLegend();
	return graph;
}

void XYPointsTracer::onCurveAboutToRemove( QCPAbstractPlottable* curve )
{
	if(isShowPointData() && (curve==_pointPositionRelatedCurve) )
		clearPointPosition();
	else
		return;

	_customPlot->replot();
}

void XYPointsTracer::showAllData()
{
	_showAllPositionFlag = true;
	double time=myResultDocument()->getResults()->getTime();
	int currentY = myResultDocument()->getResults()->getCurrentFrame();
	showAllItem(time,currentY);
	clearPointPosition();
}

void XYPointsTracer::hideAllData()
{
	_showAllPositionFlag = false;
	clearLineItem(2);
	clearLineItem(2);
	_customPlot->replot();
}

void XYPointsTracer::showAllItem(double time,int currentFrame)
{
	if (!isInitialized())
		return ;

	_showAllPositionFlag = true;
	clearLineItem(1);
	clearLineItem(1);
	hidePointData();
	_pointAction->setChecked(false);

	QList<QCPAbstractPlottable*> temCurves;
	int a = _customPlot->plottableCount();
	int b = _customPlot->graphCount();
	int pCount = a - b ; 

	for (int i =0;i<pCount;i++)
	{
		QCPAbstractPlottable * tem = _customPlot->plottable(i);
		temCurves.push_back(tem);
	}

	if (temCurves.count()>0)
	{
		QList<QCPCurve*> curves;
		for (int aa=0;aa<temCurves.count();aa++)
			curves.push_back((QCPCurve*)temCurves[aa]);

		QList<double> xValueList, yValueList;
		for (int i=0;i<curves.count();i++)
		{
			QCPCurveDataMap *map = curves[i]->data();

			int n = 0;
			for (QCPCurveDataMap::Iterator it = map->begin();it!=map->end();it++)
			{
				if(n == currentFrame)
				{
					xValueList.push_back(it->key);
					yValueList.push_back(it->value);
					break;
				}
				n++;
			}
		}

		QList<QCPGraph*> graphList;
		graphList = getGraphList(pCount);
		for (int ii= 0;ii<yValueList.count();ii++)
		{
			QVector<double> v1,v2;
			v1.push_back(xValueList[ii]);
			v2.push_back(yValueList[ii]);
			graphList[ii]->setData(v1,v2);
			graphList[ii]->setBrush(curves[ii]->pen().color());
			graphList[ii]->setName("graphItem");
			graphList[ii]->removeFromLegend();
			graphList[ii]->setPen(QPen(Qt::NoPen));

			QList<double> temPos;
			double dou = 0;
			for (int h = 0;h<pCount;h++)
			{
				temPos.push_back(dou);
				dou += 0.1;
			}

			QList<QCPItemText*> textList;
			QList<QCPItemTracer*> tracerList;
			if (_customPlot->itemCount() == 0)
			{
				for (int z=0;z<pCount;z++)
				{
					QCPItemText* temText = new QCPItemText(_customPlot);
					temText->setObjectName("textItem");
					temText->setColor(curves[z]->pen().color());
					textList.push_back(temText);
					_customPlot->addItem(textList[z]);

					QCPItemTracer* temTracer = new QCPItemTracer(_customPlot);
					temTracer->setObjectName("tracerItem");
					temTracer->setPen(curves[z]->pen());
					temTracer->setBrush(curves[z]->pen().color());
					tracerList.push_back(temTracer);
					_customPlot->addItem(tracerList[z]);
				}
			}
			else
			{
				for (int z=0;z<_customPlot->itemCount();z++)
				{
					QString s = _customPlot->item(z)->objectName();
					if (s=="textItem")
					{
						QCPItemText* temText = (QCPItemText*)_customPlot->item(z);
						textList.push_back(temText);
					}
					if (s=="tracerItem")
					{
						QCPItemTracer* temTracer = (QCPItemTracer*)_customPlot->item(z);
						tracerList.push_back(temTracer);
					}
				}
			}
			initAllPoints(graphList[ii],tracerList[ii],textList[ii],xValueList[ii],yValueList[ii]);
		}
	}
	_customPlot->replot();
}

bool XYPointsTracer::eventFilter( QObject *obj, QEvent *event )
{
	if(!isShowPointData())
		return false;

	if ( event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if (keyEvent->key() == Qt::Key_Left)
			movePointLeftOrRight(-1,_pointCu);
		else if(keyEvent->key() == Qt::Key_Right)
			movePointLeftOrRight(1,_pointCu);
		if(keyEvent->key() == Qt::Key_Shift)
			_isNewCreateGraph = true;
		if (keyEvent->key() == Qt::Key_Delete)
			removeSelectedItems();
	}
	if (event->type() == QEvent::KeyRelease)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Shift)
			_isNewCreateGraph = false;
	}

	if (event->type() == QEvent::MouseMove)
	{
		QMouseEvent *e = static_cast<QMouseEvent*>(event);
		double x = getCurrentX();
		double y = getCurrentY();
		addTenLine(x,y);
		_customPlot->replot();
	}
	if(event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* e = static_cast<QMouseEvent*>(event);
		if (e->button() == Qt::RightButton)
			_isRightButtonClick = true;
		if(e->button() == Qt::LeftButton)
			_isRightButtonClick = false;
	}
	return false;
}

void XYPointsTracer::movePointLeftOrRight( int nextPosition,QCPCurve* cu )
{
	if(!cu || !isInitialized() || (_pointKeyPosition + nextPosition<1) || ((nextPosition+_pointKeyPosition)>_valueCount-1))
		return;

	_isNeedAdd = false;
	if ((_selectedDataX != 0.615 && _selectedDataY != 0.616))
	{
		double temX =0;
		double temY =0;
		for (int i =0;i<_customPlot->plottableCount();i++)
		{
			QCPCurve *temC = static_cast<QCPCurve*>(_customPlot->plottable(i));
			QCPCurveDataMap *temD = temC->data();
			for(QCPCurveDataMap::Iterator b = temD->begin();b!=temD->end();++b)
			{
				if (_selectedDataX == b->key && _selectedDataY == b->value)
				{
					if (nextPosition == 1)
					{
						b++;
						temX = b->key;
						temY = b->value;
						_selectedDataX = temX;
						_selectedDataY = temY;
						break;
					}
					else if (nextPosition == -1)
					{
						b--;
						temX = b->key;
						temY = b->value;
						_selectedDataX = temX;
						_selectedDataY = temY;
						break;
					}
				}
			}
		}
		if (temX == 0 && temY == 0)
			return ;
		_pointKeyPosition += nextPosition;
		double textX = temX;
		double textY = temY;
		double sizeX =_customPlot->xAxis->range().size();
		double sizeY = _customPlot->yAxis->range().size();
		textX += sizeX/(20-_distance);
		textY += sizeY/(20-_distance);
		updatePoint(textX,textY,temX,temY);
	}
	_customPlot->replot();
}

void XYPointsTracer::initClickedPoint( double textX,double textY ,double x,double y)
{
	_pointPositionText = new QCPItemText(_customPlot);
	_customPlot->addItem(_pointPositionText);
	_pointPositionText->setObjectName("pointText");
	_pointPositionText->setSelectable(true);
	_pointPositionText->setColor(_pointCu->pen().color());
	initTextItem(_pointPositionText,textX,textY,x,y);

	_pointPositionTracer = new QCPItemTracer(_customPlot);
	_customPlot->addItem(_pointPositionTracer);
	_pointPositionTracer->setPen(_pointCu->pen());
	_pointPositionTracer->setBrush(_pointCu->pen().color());
	initTracerItem(_pointPositionTracer,"pointTracer",_pointPositionHighlightedPoint,x);
	if(_customPlot->selectedPlottables().count() != 0)
		_pointPositionRelatedCurve=_customPlot->selectedPlottables()[0];

	DataPointTip temTip;
	temTip.pointPositionHighlightedPoint = _pointPositionHighlightedPoint;
	temTip.pointPositionRelatedCurve = _pointPositionRelatedCurve;
	temTip.pointPositionText = _pointPositionText;
	temTip.pointPositionTracer = _pointPositionTracer;
	if (_dataPointTips.count() == 0)
		_dataPointTips.push_back(temTip);
	else
	{
		if (_isNeedAdd)
			_dataPointTips.push_back(temTip);
		else
			_dataPointTips[_dataPointTips.count() -1] = temTip;
	}
}

void XYPointsTracer::initTracerItem(QCPItemTracer* tracer, QString name,QCPGraph* graph,double graphKey )
{
	tracer->setObjectName(name);
	tracer->setGraph(graph);
	tracer->setGraphKey(graphKey);
	tracer->setInterpolating(false);
	tracer->setStyle(QCPItemTracer::tsCircle);
	tracer->setSize(7);
}

void XYPointsTracer::initTextItem(QCPItemText *text, double positionX,double positionY,double showX,double showY )
{
	text->position->setType(QCPItemPosition::ptPlotCoords);
	text->position->setCoords(positionX,positionY);
	text->setText("x: "+QString::number(showX,'f',_vaildDouble)+"\ny: "+QString::number(showY,'f',_vaildDouble));
	text->setTextAlignment(Qt::AlignLeft);
	text->setPadding(QMargins(8, 0, 0, 0));
	text->setPen(QPen(Qt::black)); 
	text->setFont(QFont("宋体", _fontSize));
	text->setBrush(Qt::white);
}
void XYPointsTracer::updatePoint( double textX,double textY,double x,double y )
{
	QVector<qreal> xVect,yVect;
	xVect.push_back(x);
	yVect.push_back(y);
	_pointPositionHighlightedPoint->setData(xVect,yVect);

	_pointPositionText->position->setCoords(textX,textY);
	_pointPositionText->setColor(_pointCu->pen().color());
	_pointPositionText->setText("x: "+QString::number(x,'f',_vaildDouble)+"\ny: "+QString::number(y,'f',_vaildDouble));

	_pointPositionTracer->setGraph(_pointPositionHighlightedPoint);
	_pointPositionTracer->setGraphKey(x);
	_pointPositionTracer->setPen(_pointCu->pen());
	_pointPositionTracer->setBrush(_pointCu->pen().color());
	_customPlot->replot();
}

void XYPointsTracer::initAllPoints( QCPGraph* graph,QCPItemTracer* tracer,QCPItemText* text,double time,qreal value )
{
	QCPDataMap *dataMap= graph->data();
	QCPData data = dataMap->begin().value();
	double x = data.key;
	double y = data.value;
	double sizeX =_customPlot->xAxis->range().size();
	double sizeY = _customPlot->yAxis->range().size();
	x += sizeX/(20-_distance);
	y += sizeY/(20-_distance);
	initTextItem(text,x,y,time,value);
	initTracerItem(tracer,"tracerItem",graph,time);
}

double XYPointsTracer::getCurrentX()
{
	QPoint pos= QCursor::pos();
	QPoint localPos = _customPlot->mapFromGlobal(pos);//用于比对
	double selectX = _customPlot->xAxis->pixelToCoord(localPos.x());//当前X值
	return selectX;
}

double XYPointsTracer::getCurrentY()
{
	QPoint pos= QCursor::pos();
	QPoint localPos = _customPlot->mapFromGlobal(pos);//用于比对
	double selectY = _customPlot->yAxis->pixelToCoord(localPos.y());//当前X值
	return selectY;
}

void XYPointsTracer::addTenLine( double x,double y )
{
	if(!_customPlot || !isShowTenLine())
		return;

	QCPCurve* vCurve;
	if (_vCurve != NULL)
		vCurve = _vCurve;
	else
	{
		vCurve = new XYCurve(_customPlot->xAxis,_customPlot->yAxis);
		vCurve->setName("tenLine");
		_customPlot->addPlottable(vCurve);
		vCurve->setSelectable(false);
		vCurve->removeFromLegend();
		_vCurve = vCurve;
	}

	QCPAxisRect *rect=_customPlot->axisRect();
	double ymin=_customPlot->yAxis->pixelToCoord(rect->top());
	double ymax=_customPlot->yAxis->pixelToCoord(rect->bottom());

	QVector<double> ax,ay;
	ax.push_back(x);
	ax.push_back(x);
	ay.push_back(ymin);
	ay.push_back(ymax);
	vCurve->setData(ax,ay);

	QCPCurve* hCurve;
	if (_hCurve != NULL)
		hCurve = _hCurve;
	else
	{
		hCurve = new XYCurve(_customPlot->xAxis,_customPlot->yAxis);
		hCurve->setName("tenLine");
		_customPlot->addPlottable(hCurve);
		hCurve->setSelectable(false);
		hCurve->removeFromLegend();
		_hCurve = hCurve;
	}

	double xmin=_customPlot->yAxis->pixelToCoord(rect->left());
	double xmax=_customPlot->yAxis->pixelToCoord(rect->right());
	double d1 = _customPlot->xAxis->range().lower;
	double d2 = _customPlot->xAxis->range().upper;

	QVector<double> bx,by;
	bx.push_back(d1);
	bx.push_back(d2);
	by.push_back(y);
	by.push_back(y);

	hCurve->setData(bx,by);
	addLeftBottomText(x,y);
}

void XYPointsTracer::showOrHideTenLine()
{
	if (isShowTenLine())
	{
		_isShowTenLine = false;
		if (_vCurve)
		{
			_customPlot->removePlottable(_vCurve);
			_vCurve = NULL;
		}
		if (_hCurve)
		{
			_customPlot->removePlottable(_hCurve);
			_hCurve = NULL;
		}
		if (_currentText)
		{
			_customPlot->removeItem(_currentText);
			_currentText = NULL;
		}
	}
	else
		_isShowTenLine = true;
}

void XYPointsTracer::addLeftBottomText( double x,double y )
{
	QCPItemText *text;
	if (_currentText != NULL)
		text = _currentText;
	else
	{
		text = new QCPItemText(_customPlot);
		_customPlot->addItem(text);
		text->position->setType(QCPItemPosition::ptAxisRectRatio);
		text->setObjectName("leftBottomText");
		text->position->setCoords(0.9, 0.05);
		text->setBrush(Qt::white);
		text->setPen(QPen(Qt::black));
		_currentText = text;
	}
	text->setText("x: "+QString::number(x)+"\ny: "+QString::number(y));
}

void XYPointsTracer::setStyledatatip()
{
	_isDatatip = true;
	_windowDialog->deleteLater();
	_windowDialog = NULL;
	clearPointPosition();
}

void XYPointsTracer::setStyleWindow()
{
	_isDatatip = false;
	clearPointPosition();
	clearLineItem(2);
	_customPlot->replot();
}

int XYPointsTracer::showDataDialog( DataPointInfo dataPoint )
{
	_currentDataPointInfo = dataPoint;
	if (!_pointPositionTracer)
	{
		_pointPositionTracer = new QCPItemTracer(_customPlot);
		_pointPositionTracer->setObjectName("pointTracer");
		_customPlot->addItem(_pointPositionTracer);
	}

	_pointPositionTracer->setGraph(_pointPositionHighlightedPoint);
	_pointPositionTracer->setGraphKey(_currentDataPointInfo.x);
	_pointPositionTracer->setInterpolating(false);
	_pointPositionTracer->setStyle(QCPItemTracer::tsCircle);
	_pointPositionTracer->setPen(_pointCu->pen());
	_pointPositionTracer->setBrush(_pointCu->pen().color());
	_pointPositionTracer->setSize(7);
	QVector<double > x,y;
	x.push_back(_currentDataPointInfo.x);
	y.push_back(_currentDataPointInfo.y);
	_pointPositionHighlightedPoint->setData(x,y);

	QDialog *window ;
	if (_windowDialog != NULL)
		_windowDialog->deleteLater();

	window = new QDialog();
	
	_windowDialog = window;

	QVBoxLayout *layout = new QVBoxLayout();
	if (_currentDataPointInfoFlag._xFlag)
	{
		QLabel *labX = new QLabel("X: "+QString::number(dataPoint.x,'f',_vaildDouble));
		layout->addWidget(labX);
	}
	if (_currentDataPointInfoFlag._yFlag)
	{
		QLabel *labY = new QLabel("Y: "+QString::number(dataPoint.y,'f',_vaildDouble));
		layout->addWidget(labY);
	}
	if (_currentDataPointInfoFlag._maxFlag)
	{
		QLabel* labMax = new QLabel("Max: "+ QString::number(dataPoint.max,'f',_vaildDouble));
		layout->addWidget(labMax);
	}
	if (_currentDataPointInfoFlag._minFlag)
	{
		QLabel* labMin = new QLabel("Min: "+QString::number(dataPoint.min,'f',_vaildDouble));
		layout->addWidget(labMin);
	}

	window->setWindowFlags(Qt::WindowStaysOnTopHint); 
	window->setGeometry(QApplication::desktop()->width()-150,QApplication::desktop()->height()-100,0,0);
	window->setLayout(layout);
	window->show();	
	_customPlot->activateWindow();
	_customPlot->replot();
	return 1;
}

void XYPointsTracer::clearAllDatatips()
{
	clearLineItem(2);
	clearLineItem(2);
	_dataPointTips.clear();

	_pointPositionHighlightedPoint = NULL;
	_pointPositionText = NULL;
	_pointPositionRelatedCurve = NULL;
	_pointPositionTracer = NULL;
}

void XYPointsTracer::onItemClicked( QCPAbstractItem * item )
{
	///先要比对确定点击的是否为textitem
	///所有textitem刷白备用
	///这个还有问题 当只有一个时也要可以选
	if(isShowAllData())
		return;

	QCPItemText *textItem = static_cast<QCPItemText*>(item);
	_currentSelectedText = textItem;
	bool flag = false;
	int current =0;
	for(int i=0;i<_dataPointTips.count();i++)
	{
		if (textItem == _dataPointTips[i].pointPositionText)
		{
			flag = true;
			current = i;
		}
		_dataPointTips[i].pointPositionText->setBrush((Qt::white));
	}
	if (!flag)
		return ;

	QCPCurve* cu = static_cast<QCPCurve*>(_dataPointTips[current].pointPositionRelatedCurve);

	_pointPositionHighlightedPoint = _dataPointTips[current].pointPositionHighlightedPoint;
	_pointPositionText = _dataPointTips[current].pointPositionText;
	_pointPositionRelatedCurve = _dataPointTips[current].pointPositionRelatedCurve;
	_pointPositionTracer = _dataPointTips[current].pointPositionTracer;

	_currentSelectedDatatip.pointPositionHighlightedPoint = _pointPositionHighlightedPoint;
	_currentSelectedDatatip.pointPositionRelatedCurve = _pointPositionRelatedCurve;
	_currentSelectedDatatip.pointPositionText = _pointPositionText;
	_currentSelectedDatatip.pointPositionTracer = _pointPositionTracer;

	_pointCu = static_cast<QCPCurve*>(_pointPositionRelatedCurve);

	QCPDataMap *dm = _currentSelectedDatatip.pointPositionHighlightedPoint->data();
	QCPData _selectedData = dm->begin().value();
	_selectedDataX = _selectedData.key;
	_selectedDataY = _selectedData.value;

	int pos =0;
	QCPCurveDataMap* map = cu->data();
	for (QCPCurveDataMap::Iterator it = map->begin();it != map->end();it ++)
	{
		if (_selectedDataX == it->key && _selectedDataY == it->value)
			_pointKeyPosition = pos;

		pos++;
	}
	textItem->setBrush(_selectedColor);
	_clickedTextString = textItem->text();
}

void XYPointsTracer::copyToClipboard()
{
	QApplication::clipboard()->setText(_clickedTextString);
}

void XYPointsTracer::setDistance( int value )
{
	_distance = value;
	double sizeX =_customPlot->xAxis->range().size();
	double sizeY = _customPlot->yAxis->range().size();
	for (int i=0;i<_dataPointTips.count();i++)
	{
		QCPDataMap *dataMap= _dataPointTips[i].pointPositionHighlightedPoint->data();
		QCPData pDdata = dataMap->begin().value();
		double textX = pDdata.key;
		double textY = pDdata.value;

		textX += sizeX/(20-_distance);
		textY += sizeY/(20-_distance);

		_dataPointTips[i].pointPositionText->position->setCoords(textX,textY);
	}
	_customPlot->replot();
}

void XYPointsTracer::createDisplayFormatDialog()
{
	ShowSettingDialog *dialog = new ShowSettingDialog(this,_currentDataPointInfoFlag,0);
	dialog->exec();
}

void XYPointsTracer::setFontSize( int value )
{
	_fontSize = value;
	for (int i=0;i<_dataPointTips.count();i++)
	{
		QFont f = _dataPointTips[i].pointPositionText->font();
		f.setPointSize(_fontSize);
		_dataPointTips[i].pointPositionText->setFont(f);
	}
	_customPlot->replot();
}

void XYPointsTracer::setSelectedColor( QColor color )
{
	_selectedColor = color;
	for (int i=0;i<_dataPointTips.count();i++)
		_dataPointTips[i].pointPositionText->setBrush(_selectedColor);
	_customPlot->replot();
}

void XYPointsTracer::setDataPointShowFlag( DataPointShowFlag flag )
{
	_currentDataPointInfoFlag = flag;
	if (isDatatip())
		return;
	showDataDialog(_currentDataPointInfo);
}

void XYPointsTracer::copyYRange()
{
	QByteArray output;
	QCPRange range =_customPlot->yAxis->range();
	QString s = QString::number(range.lower)+","+QString::number(range.upper);  
	QDataStream out(&output,QIODevice::WriteOnly);   
	out<<s;

	QMimeData *mimeData = new QMimeData;
	QString mimeType = QString("application/tdypre:curveYRange");
	mimeData->setData(mimeType, output);

	QApplication::clipboard()->setMimeData(mimeData);
}

void XYPointsTracer::pasteYRange()
{
	QString mimeType = QString("application/tdypre:curveYRange");
	const QMimeData* mimeData=QApplication::clipboard()->mimeData();
	if(!mimeData)
		return;
	if (mimeData->hasFormat(mimeType))
	{
		QByteArray input= mimeData->data(mimeType);
		QDataStream in(&input,QIODevice::ReadOnly);   
		QString s;
		QCPRange range;  
		in>>s;
		double d1,d2;
		d1 = s.split(",")[0].toDouble();
		d2 = s.split(",")[1].toDouble();
		_customPlot->yAxis->setRange(d1,d2);
		_customPlot->replot();
	}
}

void XYPointsTracer::copyCurve()
{
	QList<QCPAbstractPlottable*> selectedList =_customPlot->selectedPlottables();
	int n=selectedList.size();
	if (n==0)
		return;

	QByteArray output;
	QDataStream out(&output,QIODevice::WriteOnly);  
	out<<getpid();

	qint64 pos=out.device()->pos();
	qint32 tmpSize=0;
	out<<tmpSize;
	for(int i=0;i<n;++i)
	{
		XYItemTitle* title=_plot->getCurveItemTitle(selectedList[i]);
		if(!title)
		{
			Base::Console().Error("No related curve item title.");
			continue;
		}

		XYItemTitle tmpTitle=*title;
		tmpTitle.xs = XYCurve::getCurveXVector(selectedList[i]);
		tmpTitle.ys = XYCurve::getCurveYVector(selectedList[i]);

		out<<tmpTitle;
		tmpSize++;
	}
	qint64 curr=out.device()->pos();
	out.device()->seek(pos);
	out<<tmpSize;
	out.device()->seek(curr);

	QMimeData *mimeData = new QMimeData;
	QString mimeType = QString("application/tdypre:curves");
	mimeData->setData(mimeType, output);

	QApplication::clipboard()->setMimeData(mimeData);
}

void XYPointsTracer::pasteCurve()
{
	QString mimeType = QString("application/tdypre:curves");
	const QMimeData* mimeData=QApplication::clipboard()->mimeData();
	if(!mimeData)
		return;

	if (mimeData->hasFormat(mimeType))
	{
		QByteArray input= mimeData->data(mimeType);

		QDataStream in(&input,QIODevice::ReadOnly);   
		XYItemTitle title;
		qint32 id =0;
		in>>id;
		int n=0;
		in>>n;
		if(n == 0)
			return;
		in>>title;
		if (id == getpid())
		{
			if(title.type!=XYItemTitle::IsImported)
			{
				title.xs.clear();
				title.ys.clear();
			}
			_plot->addMyCurve(title);
		}
		else 
		{
			title.type = XYItemTitle::IsImported;
			_plot->addMyCurve(title);
		}
		if (isShowAllData())
		{
			hideAllData();
			showAllData();
		}
		_customPlot->replot();
	}
}

void XYPointsTracer::updateTextPosition()
{
	_customPlot->replot();
	double sizeX =_customPlot->xAxis->range().size();
	double sizeY = _customPlot->yAxis->range().size();
	for (int i=0;i<_dataPointTips.count();i++)
	{
		QCPDataMap *map =_dataPointTips[i].pointPositionHighlightedPoint->data();
		double x = map->begin()->key;
		double y = map->begin()->value;
		double textX = x;
		double textY = y;
		textX += sizeX/(20-_distance);
		textY += sizeY/(20-_distance);
		_dataPointTips[i].pointPositionText->position->setCoords(textX,textY);
	}
	_customPlot->replot();
}

void XYPointsTracer::setVaildDouble( int value )
{
	_vaildDouble = value;
	if (isDatatip())
	{
		for (int i=0;i<_dataPointTips.count();i++)
		{
			QCPDataMap *map =_dataPointTips[i].pointPositionHighlightedPoint->data();
			double x = map->begin()->key;
			double y = map->begin()->value;
			_dataPointTips[i].pointPositionText->setText("X: "+QString::number(x,'f',_vaildDouble)+"\nY: "+QString::number(y,'f',_vaildDouble));
		}
	}
	else
		showDataDialog(_currentDataPointInfo);

	_customPlot->replot();
}

void XYPointsTracer::removeSelectedItems()
{
	if (_currentSelectedText==NULL)
		return;

	for (int i=0;i<_dataPointTips.count();i++)
	{
		if (_dataPointTips[i].pointPositionText == _currentSelectedText)
		{
			_customPlot->removeGraph(_dataPointTips[i].pointPositionHighlightedPoint);
			_customPlot->removeItem(_dataPointTips[i].pointPositionText);
			_customPlot->removeItem(_dataPointTips[i].pointPositionTracer);

			_dataPointTips.removeAt(i);
			break;
		}
	}
	_currentSelectedText = NULL;
	_pointPositionHighlightedPoint=NULL;
	_pointPositionText=NULL;
	_pointPositionRelatedCurve=NULL;
	_pointPositionTracer=NULL;

	_customPlot->replot();
}

void XYPointsTracer::onSaveViewToFile()
{
	QAction* ac = (QAction*)sender();
	QString acText = ac->text();
	QString saveName = QFileDialog::getSaveFileName(0,"","",acText);
	if(saveName.isEmpty())
		return;

	QFileInfo info(saveName);
	QString suffix = info.suffix();
	if(suffix == "jpg")
		_customPlot->saveJpg(saveName);
	else if(suffix == "png")
		_customPlot->savePng(saveName);
	else if(suffix == "bmp")
		_customPlot->saveBmp(saveName);
	else if(suffix == "pdf")
		_customPlot->savePdf(saveName);
}

void XYPointsTracer::copyViewToClipboard()
{
	_customPlot->savePng(qApp->applicationDirPath()+"/"+"tmpImg.png");
	QImage img;
	img.load(qApp->applicationDirPath()+"/"+"tmpImg.png");
	QApplication::clipboard()->setImage(img);
	QFile::remove(qApp->applicationDirPath()+"/"+"tmpImg.png");
}

