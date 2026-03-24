#include "customcurveplot.h"

#include "qcustomplot/qcustomplot.h"

#include "base/Console.h"
#include "base/MultiProgressOperator.h"

#include "precore/modeldocument.h"
#include "precore/FlexResultItem.h"
#include "precore/RigidResultItem.h"
#include "precore/ResultDocument.h"

#include "pubbase/mimedata.h"

#include "resultexpressionparser.h"
#include "curvepointstracer.h"
#include "curve.h"
#include "curveconfigdialog.h"

#include "addcurvethread.h"

#include <QtGui>

using namespace Base;
using namespace INSIDES;

static int int_colors[]={
	0,128,255,
	255,0,0,
	0,255,0,
	0,0,255,
	255,0,255,
	0,192,192,
	231,113,8,
	255,192,255,
	255,128,255,
	//192,192,0,
	252,188,131,
	128,0,64,
	192,192,255,
	128,128,128,
	0,255,255,
	128,255,255,
};

static int color_size=15;

CustomCurvePlot::CustomCurvePlot(QObject *parent,QCustomPlot* plot)
	: QObject(parent)
	,_currentColorIndex(0)
	,_legendDrag(false)
{
	myResultDocument()->attachListener(this);
	
	_customPlot=plot;
	_curvePointsTracer=new CurvePointsTracer(this,this);
	init();

	_configMenu = new QMenu();
	connect(_configMenu,SIGNAL(aboutToHide()),this,SLOT(onAboutToHide()));

	_updateSelectCurveAction = new QAction("update select curve",0);
	bool b = connect(_updateSelectCurveAction,SIGNAL(triggered()),this,SLOT(updateSelectCurve()));
	
	draggingLegend = false;

	connect(_customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMoveSignal(QMouseEvent*)));
	connect(_customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressSignal(QMouseEvent*)));
	connect(_customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseReleaseSignal(QMouseEvent*)));
	connect(_customPlot, SIGNAL(beforeReplot()), this, SLOT(beforeReplot()));
}

CustomCurvePlot::~CustomCurvePlot()
{
	myResultDocument()->disattachListener(this);
}

///更改曲线视图默认外观
bool CustomCurvePlot::init()
{
	//_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
		QCP::iSelectLegend | QCP::iSelectPlottables);
	
	//标尺刻度上的字
	QFont axisTickFont;
	axisTickFont.setFamily("Arial");

	axisTickFont.setPointSize(12);
	_customPlot->xAxis->setTickLabelFont(axisTickFont);
	_customPlot->yAxis->setTickLabelFont(axisTickFont);

	//刻度边上的label
	QFont axisLabelFont;
	axisLabelFont.setFamily("黑体");
	axisLabelFont.setPointSize(14);

	_customPlot->xAxis->setLabel("time");
	_customPlot->xAxis->setLabelFont(axisLabelFont);
	_customPlot->yAxis->setLabel("data");
	_customPlot->yAxis->setLabelFont(axisLabelFont);

	//标题
	//QFont titleFont;
	//titleFont.setFamily("黑体");
	//titleFont.setPointSize(20);
	//QCPLayoutElement* pItem =	_customPlot->plotLayout()->elementAt(0);
	//QCPPlotTitle* pTitle = dynamic_cast<QCPPlotTitle*>(pItem);
	//
	//_customPlot->plotLayout()->insertRow(0);
	//pTitle = new QCPPlotTitle(_customPlot,"");
	//pTitle->setFont( titleFont );
	//_customPlot->plotLayout()->addElement(0, 0, pTitle );
	

	_customPlot->legend->setVisible(true);
	_customPlot->legend->installEventFilter(this);
	_customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

	QFont legendFont ;//= font();  // start out with MainWindow's font..
	legendFont.setPointSize(14); // and make a bit smaller for legend
	legendFont.setFamily("黑体");
	_customPlot->legend->setFont(legendFont);
	_customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));

	int size = legendFont.pointSize()*1.3;
	_customPlot->legend->setIconSize(size,size);

	// by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
	_customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);


	// connect slot that ties some axis selections together (especially opposite axes):
	connect(_customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
	// connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
	connect(_customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
	connect(_customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

	// make bottom and left axes transfer their ranges to top and right axes:
	//connect(_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
	//connect(_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

	// connect some interaction slots:
	connect(_customPlot, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
	connect(_customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
	connect(_customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

//	connect(_customPlot,SIGNAL(	plottableClick (QCPAbstractPlottable* , QMouseEvent* )),this,SLOT(	onPlottableClick (QCPAbstractPlottable *, QMouseEvent *)));

	// connect slot that shows a message in the status bar when a graph is clicked:
	connect(_customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));
	connect(_customPlot,SIGNAL(itemClick ( QCPAbstractItem *  , QMouseEvent *    ) ),_curvePointsTracer,SLOT(onItemClicked( QCPAbstractItem *  )));

	// setup policy and connect slot for context menu popup:
	_customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(_customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
	connect(this,SIGNAL(updateTextPosition()),_curvePointsTracer,SLOT(updateTextPosition()));

	addTimeLine();

	return true;
}

void CustomCurvePlot::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
{
  Q_UNUSED(event)
  // Set the plot title by double clicking on it
  bool ok;
  QString newTitle = QInputDialog::getText(_customPlot, 
	  "Edit plot title", "New plot title:", QLineEdit::Normal, title->text(), &ok);
  if (ok)
  {
    title->setText(newTitle);
    _customPlot->replot();
  }
}

void CustomCurvePlot::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(_customPlot, "Edit axis label", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      _customPlot->replot();
    }
  }
}

void CustomCurvePlot::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(_customPlot, "Edit graph name", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
		plItem->plottable()->setName(newName);
		CurveItemTitle* itemTitle=getCurveItemTitle(plItem->plottable());
		if(itemTitle)
			itemTitle->name=newName;

      _customPlot->replot();
    }
  }
}

void CustomCurvePlot::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.
   
   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.
   
   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */
  
  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (_customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || 
	  _customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) )
	  //||
      //_customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || _customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    _customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    //_customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (_customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) 
	  || _customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels)
      //ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
	  )
  {
    _customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    //_customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  
  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<_customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = _customPlot->graph(i);
	QPen pen = graph->selectedPen();
	pen.setWidth(graph->pen().width());
	graph->setSelectedPen(pen);
	QCPPlottableLegendItem *item = _customPlot->legend->itemWithPlottable(graph);

	// Fix bug: item can be null, by Jerry, 2014.10.13
	if (item && (item->selected() || graph->selected()))
	{
		item->setSelected(true);
		graph->setSelected(true);
	}
  }

  for (int i=0; i<_customPlot->plottableCount(); ++i)
  {
	  QCPAbstractPlottable *graph = _customPlot->plottable(i);
	  QPen pen = graph->selectedPen();
	  pen.setWidth(graph->pen().width());
	  graph->setSelectedPen(pen);
	  QCPPlottableLegendItem *item = _customPlot->legend->itemWithPlottable(graph);
	  if(!item)
		  continue;

	  if (item->selected() || graph->selected())
	  {
		  item->setSelected(true);
		  item->setSelectedFont(item->font());
		  graph->setSelected(true);
	  }
  }
}

void CustomCurvePlot::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged
    
  if (_customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    _customPlot->axisRect()->setRangeDrag(_customPlot->xAxis->orientation());
  else if (_customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    _customPlot->axisRect()->setRangeDrag(_customPlot->yAxis->orientation());
  else
    _customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void CustomCurvePlot::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed
  
  if (_customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    _customPlot->axisRect()->setRangeZoom(_customPlot->xAxis->orientation());
  else if (_customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    _customPlot->axisRect()->setRangeZoom(_customPlot->yAxis->orientation());
  else
    _customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
  emit updateTextPosition();
}


void CustomCurvePlot::removeSelectedGraph()
{
  if (_customPlot->selectedGraphs().size() > 0)
  {
    _customPlot->removeGraph(_customPlot->selectedGraphs().first());
    _customPlot->replot();
  }
  if(_customPlot->selectedPlottables().size()>0)
  {
	  QCPAbstractPlottable* selected=_customPlot->selectedPlottables().first();
	  for(int i=0;i<_customPlot->plottableCount();++i){
		  if(_customPlot->plottable(i)==selected){
			  _curveItemTitleList.removeAt(i-1);
			  break;;
		  }
	  }

	  emit curveAboutToRemove(selected);
	  _customPlot->removePlottable(selected);
  }
  
  if (_curvePointsTracer->isShowAllData())
  {
	  _curvePointsTracer->hideAllData();
	  _curvePointsTracer->showAllData();
  }
  if (_curvePointsTracer->isShowPointData())
  {
//	  _curvePointsTracer->hidePointData();
//	  _curvePointsTracer->showPointData();
  }
  _customPlot->replot();
}

void CustomCurvePlot::removeAllGraphs()
{
  _customPlot->clearGraphs();
  // 剩下时间曲线
  while(_customPlot->plottableCount()>1){
	  emit curveAboutToRemove(_customPlot->plottable(1));
	  _customPlot->removePlottable(1);
  }
  _curveItemTitleList.clear();
  _curvePointsTracer->clearAllDatatips();
  _customPlot->replot();
  _curvePointsTracer->hideAllData();
}

void CustomCurvePlot::contextMenuRequest(QPoint pos)
{
	QMenu *menu = new QMenu(_customPlot);
	menu->setAttribute(Qt::WA_DeleteOnClose);

	if (_customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
	{
		menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
		menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
		menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
		menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
		menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
		
		menu->addSeparator();
		int a = _customPlot->axisRect()->insetLayout()->insetPlacement(0);
		if(!a)
			menu->addAction("Drag Off",this,SLOT(legendDragOnOrOff()));
		else
			menu->addAction("Drag On",this,SLOT(legendDragOnOrOff()));
	} 
	else  // general context menu on graphs requested
	{
		if (_customPlot->selectedGraphs().size() > 0 || _customPlot->selectedPlottables().size()>0)
		{
			menu->addAction("remove selected graph", this, SLOT(removeSelectedGraph()));
			menu->addAction(_updateSelectCurveAction);
		}
		/*if (_customPlot->graphCount() > 0 || _customPlot->selectedPlottables().size()>0)
		menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));*/

		if (_customPlot->selectedGraphs().size()==0)
		{
			menu->addAction("remove all graphs", this, SLOT(removeAllGraphs()));
			if (_curvePointsTracer->isShowPointData())
			{
				if (_curvePointsTracer->isShowTenLine())
					menu->addAction("hide tenLine",_curvePointsTracer,SLOT(showOrHideTenLine()));
				else
					menu->addAction("show tenLine",_curvePointsTracer,SLOT(showOrHideTenLine()));
			}

			if (_curvePointsTracer->isShowPointData())
			{
				menu->addSeparator();

				QMenu *styleMenu = menu->addMenu("display style");
				styleMenu->addAction(_curvePointsTracer->getDatatipStyleAction());
				styleMenu->addAction(_curvePointsTracer->getWindowStyleAction());

				menu->addAction(_curvePointsTracer->getCreateNewDatatipAction());
				menu->addAction(_curvePointsTracer->getDeleteAllDatatipsAction());
				menu->addAction(_curvePointsTracer->getCopyToClipboardAction());
				menu->addAction(_curvePointsTracer->getSetDisplayFormatAction());

				menu->addSeparator();
			}

			QMenu* copyMenu = menu->addMenu("copy");
			QAction* copyXAction = copyMenu->addAction("x range",this,SLOT(copyXRange()));
			copyMenu->addAction(_curvePointsTracer->getCopyYAction());
			copyMenu->addAction(_curvePointsTracer->getCopyCurveAction());

			QMenu *pasteMenu = menu->addMenu("paste");
			QAction* pasteXAction = pasteMenu->addAction("x range",this,SLOT(pasteXRange()));
			pasteMenu->addAction(_curvePointsTracer->getPasteYAction());
			pasteMenu->addAction(_curvePointsTracer->getPasteCurveAction());

			QString mimeType = QString("application/tdypre:curveXRange");
			QString mimeYType = QString("application/tdypre:curveYRange");
			QString mimeCurveType = QString("application/tdypre:curves");
			const QMimeData* mimeData=QApplication::clipboard()->mimeData();

			if(mimeData->hasFormat(mimeType))
				pasteXAction->setEnabled(true);
			else
				pasteXAction->setEnabled(false);

			if (mimeData->hasFormat(mimeYType))
				_curvePointsTracer->getPasteYAction()->setEnabled(true);
			else
				_curvePointsTracer->getPasteYAction()->setEnabled(false);

			if (mimeData->hasFormat(mimeCurveType))
				_curvePointsTracer->getPasteCurveAction()->setEnabled(true);
			else
				_curvePointsTracer->getPasteCurveAction()->setEnabled(false);

			if(_customPlot->selectedItems().count() ==0)
				_curvePointsTracer->getCopyToClipboardAction()->setEnabled(false);
			else
				_curvePointsTracer->getCopyToClipboardAction()->setEnabled(true);

			if(_customPlot->selectedPlottables().count() ==0)
				_curvePointsTracer->getCopyCurveAction()->setEnabled(false);
			else
				_curvePointsTracer->getCopyCurveAction()->setEnabled(true);
		}
	}
	menu->popup(_customPlot->mapToGlobal(pos));
}

void CustomCurvePlot::moveLegend()
{
	if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
	{
		bool ok;
		int dataInt = contextAction->data().toInt(&ok);
		if (ok)
		{
			_legendDrag = false;
			_customPlot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipBorderAligned);
			_customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
			_customPlot->replot();
		}
	}
}

void CustomCurvePlot::graphClicked(QCPAbstractPlottable *plottable)
{
	QString str=QString("Clicked on graph '%1'.").arg(plottable->name());
	QString s = plottable->name();
	Base::Console().Log(str.toStdString().c_str());
	_curvePointsTracer->onPlottableClicked(plottable);
}

void CustomCurvePlot::viewAll()
{
	_customPlot->rescaleAxes(true);
	_customPlot->replot();
}

void CustomCurvePlot::onResultCurrentFrameChanged()
{
	updateTimeLine();
	_curvePointsTracer->resultCurrentFrameChanged();
	_customPlot->replot();
}

void CustomCurvePlot::addTimeLine()
{
	if(!_customPlot)
		return;

	QCPCurve* curve=new Curve(_customPlot->xAxis,_customPlot->yAxis);
	curve->setName("Time");
	QPen pen=curve->pen();
	pen.setWidth(2);
	curve->setPen(pen);
	_customPlot->addPlottable(curve);
	curve->setSelectable(false);
	curve->removeFromLegend();
}

void CustomCurvePlot::updateTimeLine()
{
	if(!_customPlot)
		return;

	if(!myResultDocument()->getResults())
		return;

	QCPAxisRect *rect=_customPlot->axisRect();
	double ymin=_customPlot->yAxis->pixelToCoord(rect->top());
	double ymax=_customPlot->yAxis->pixelToCoord(rect->bottom());
	double time=myResultDocument()->getResults()->getTime();

	QVector<double> ax,ay;
	ax.push_back(time);
	ax.push_back(time);
	ay.push_back(ymin);
	ay.push_back(ymax);
	QCPCurve* curve=(QCPCurve*)_customPlot->plottable(0);
	curve->setData(ax,ay);
}

IResultItem* CustomCurvePlot::getRelatedResultItem( const QString& itemname )
{
	BaseItem* item=myDocument()->findItem(itemname);
	if(!item)
		return NULL;

	if(myResultDocument()->getResults())
		return myResultDocument()->getResults()->findResultItem(item).data();

	return NULL;
}

bool CustomCurvePlot::itemTitle2Data(const CurveItemTitle& itemTitle,
	QVector<double>& xlist,QVector<double>& ylist)
{
	QString baseitemName=itemTitle.itemContent;
	IResultItem* resultItem=getRelatedResultItem(baseitemName);
	if(!resultItem)
		return false;

	int secIndex=itemTitle.secIndex;
	int subsecIndex=itemTitle.subsecIndex;
	int subsubsecIndex=itemTitle.subsubsecIndex;
	int nodeElemIndex=itemTitle.nodeElemIndex;

	int frameCount=myResultDocument()->getResults()->getFrameCount();
	if(!resultItem || frameCount<=0)
		return false;

	IResults* results=myResultDocument()->getResults();

	QString itemName=resultItem->connectedItem()->getKeyName();
	QString sectionName=resultItem->sectionName(secIndex);
	QString subSectionName=resultItem->subSectionName(secIndex,subsecIndex);
	QString subsubSectionName=resultItem->subsubSectionName(secIndex,subsecIndex,subsubsecIndex);
	QString indexName;

	int currentPos=results->getCurrentFrame();
	if(nodeElemIndex>=0 && secIndex!=0)
	{
		FlexResultItem* flexResultItem=(FlexResultItem*)resultItem;
		
		//循环耗时 将这个循环移到一个新的线程
		AddCurveThread thread(frameCount,results,flexResultItem,itemTitle,this);
		thread.start();
		QEventLoop loop;
		connect(&thread,SIGNAL(finished()),&loop,SLOT(quit()));
		loop.exec();
		xlist = thread.getXList();
		ylist = thread.getYList();

		QString indexLabel;
		if(secIndex==1){
			int realNodeIndex=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetNode(nodeElemIndex)->NID;
			indexLabel=QString("%1").arg(realNodeIndex);
		}
		else if(secIndex==2){
			int realNodeIndex=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh.GetElement(nodeElemIndex)->EID;
			indexLabel=QString("%1").arg(realNodeIndex);
		}
		indexName=QString("%1-%2 ").arg(secIndex==1?"Node":"Elem").arg(indexLabel);
		subsubSectionName=flexResultItem->subsubSectionName(secIndex,subsecIndex,subsubsecIndex);
	}
	else{
		//循环耗时 将这个循环移到一个新的线程
		AddCurveThread thread(frameCount,results,resultItem,itemTitle,this);
		thread.start();
		QEventLoop loop;
		connect(&thread,SIGNAL(finished()),&loop,SLOT(quit()));
		loop.exec();
		xlist = thread.getXList();
		ylist = thread.getYList();
	}
	resultItem->setPos(currentPos);
	return true;
}

bool CustomCurvePlot::itemTitle2DataCustom( const CurveItemTitle& itemTitle,
	QVector<double>& xlist,QVector<double>& ylist)
{
	//IResultItem* resultItem=getRelatedResultItem(baseitemName);
	int frameCount=myResultDocument()->getResults()->getFrameCount();
	if(frameCount<=0)
		return false;

	IResults* results=myResultDocument()->getResults();

	int originalPos=results->getCurrentFrame();
	string input=itemTitle.itemContent.toStdString();
	ResultExpressionParser parser;
	if(!parser.setExpressionStr(input))
		return false;

	//循环耗时 将这个循环移到一个新的线程
	AddCurveThread thread(frameCount,results,&parser,this);
	thread.start();
	QEventLoop loop;
	connect(&thread,SIGNAL(finished()),&loop,SLOT(quit()));
	loop.exec();
	xlist = thread.getXList();
	ylist = thread.getYList();

	parser.setPos(originalPos);

	return true;
}

void CustomCurvePlot::exportAllCurves()
{
	if(_curveItemTitleList.size()==0)
		return;

	QString fileName= QFileDialog::getSaveFileName(_customPlot, tr("Save File"),
		".",
		tr("dat (*.dat *.dat *.dat)"));

	if(fileName.isEmpty())
		return;

	QVector<QVector<double> > allDatas;
	QVector<QString>	titles;
		
	QCPCurve* curve=(QCPCurve*)_curveItemTitleList[0].relatedPlotable;
	QCPCurveDataMap* data=curve->data();

	QVector<double> timeData;
	for(QCPCurveDataMap::Iterator b=data->begin();b!=data->end();++b)
		timeData.push_back(b->key);

	allDatas.push_back(timeData);
	titles.push_back("Time");

	for(int i=0;i<_curveItemTitleList.size();++i){
		QCPCurve* curve=(QCPCurve*)_curveItemTitleList[i].relatedPlotable;
		QCPCurveDataMap* data=curve->data();

		QVector<double> doubleData;
		for(QCPCurveDataMap::Iterator b=data->begin();b!=data->end();++b)
			doubleData.push_back(b->value);
		
		allDatas.push_back(doubleData);
		titles.push_back(curve->name());
	}

	QFile dataFile(fileName);
	if (dataFile.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream out(&dataFile);

		int n=titles.size();
		for(int i=0;i<n;++i)
			out<<QString("%1").arg(titles[i],20)<<"\t ";
		out<<endl;

		int dataLen=allDatas[0].size();
		for(int i=0;i<dataLen;++i)
		{
			for(int j=0;j<n;++j)
				if(i<allDatas[j].size())
					out<<QString("%1").arg(allDatas[j][i],20,'e',13)<<"\t ";
				else
					out<<"\t ";
			out<<endl;
		}
	}
}

void CustomCurvePlot::importCurves()
{
	QString fileName= QFileDialog::getOpenFileName(_customPlot, tr("Open x-y curve-format file"),
		".",
		tr("dat (*.dat *.dat *.dat)"));

	if(fileName.isEmpty())
		return;

	QVector<QVector<double> > allDatas;
	QStringList	titles;

	QFile dataFile(fileName);
	if (!dataFile.open(QFile::ReadOnly))
		return;

	QTextStream in(&dataFile);

	QString line=in.readLine();
	titles=line.trimmed().split("\t");
	int n=titles.size();
		
	for(int i=0;i<n;++i)
		allDatas<<QVector<double>();

	while(!in.atEnd())
	{
		line=in.readLine();
		QStringList vec=line.trimmed().split("\t");
		for(int i=0;i<n;++i){
			double v=vec[i].toDouble();
			allDatas[i]<<v;
		}
	}

	for(int i=1;i<n;++i){
		CurveItemTitle title;
		title.type=CurveItemTitle::IsImported;
		title.name=titles[i];
		title.xs=allDatas[0];
		title.ys=allDatas[i];
		addMyCurve(title);
	}
}

bool CustomCurvePlot::addMyCurve( const CurveItemTitle& itemTitle )
{
	QVector<double> xlist,ylist;
	bool result=false;

	//这里放个度条

	switch(itemTitle.type){
	case CurveItemTitle::Normal:
		result=itemTitle2Data(itemTitle,xlist,ylist);
		break;
	case CurveItemTitle::Custom:
		result=itemTitle2DataCustom(itemTitle,xlist,ylist);
		break;
	case CurveItemTitle::IsImported:
		xlist=itemTitle.xs;
		ylist=itemTitle.ys;
		result=true;
		break;
	}

	if(!result){
		Base::Console().Error("Add curve failed.");
		return false;
	}

	QCPCurve* curve=new Curve(_customPlot->xAxis,_customPlot->yAxis);

	curve->setData(xlist,ylist);
	curve->setName(itemTitle.name);
	
	//设置曲线的外形
	setInitialCurveProperty(curve);

	CurveItemTitle tmpTitle=itemTitle;
	tmpTitle.relatedPlotable=curve;
	_curveItemTitleList.push_back(tmpTitle);
	addCurveIntoPlot(curve);

	return true;
}

void CustomCurvePlot::testAddMyCurve()
{
	
}

bool CustomCurvePlot::updateMyCurve( const CurveItemTitle& itemTitle )
{
	QVector<double> xlist,ylist;
	bool result=false;

	QCPCurve* cu = NULL;
	for (int i=0;i<_curveItemTitleList.count();i++)
	{
		if(_curveItemTitleList[i].relatedPlotable == itemTitle.relatedPlotable)
		{
			cu = _curveItemTitleList[i].relatedPlotable;
			_curveItemTitleList[i] = itemTitle;
			break;
		}
	}

	if(!cu)
		return false;

	switch(itemTitle.type){
	case CurveItemTitle::Normal:
		result=itemTitle2Data(itemTitle,xlist,ylist);
		break;
	case CurveItemTitle::Custom:
		result=itemTitle2DataCustom(itemTitle,xlist,ylist);
		break;
	case CurveItemTitle::IsImported:
		xlist=itemTitle.xs;
		ylist=itemTitle.ys;
		result=true;
		break;
	}

	if(!result){
		Console().Error("Update curve failed.");
		return false;
	}
	cu->setData(xlist,ylist);

	_customPlot->replot();
	return true;
}

void CustomCurvePlot::updateSelectCurve()
{
	QList<QCPAbstractPlottable*> list = _customPlot->selectedPlottables();
	if(list.isEmpty())
		return;

	QCPCurve* cu = static_cast<QCPCurve*>(list[0]);
	CurveItemTitle title;
	bool noTitle = true;
	foreach(CurveItemTitle tmp ,_curveItemTitleList)
	{
		if(tmp.relatedPlotable == cu)
		{
			title = tmp;
			noTitle = false;
			break;
		}
	}
	if(!cu || noTitle)
		return;

	emit updateCurve(title);
}

bool CustomCurvePlot::updateAllMyCurve()
{
	QCustomPlot* plot=getCustomPlot();
	for(size_t i=0;i<_curveItemTitleList.size();++i){
		if(i>=plot->plottableCount()-1)
			break;

		QVector<double> xlist,ylist;
		QString title;

		if(_curveItemTitleList[i].type==CurveItemTitle::IsImported)
			continue;

		switch(_curveItemTitleList[i].type)
		{
		case CurveItemTitle::Custom:
			itemTitle2DataCustom(_curveItemTitleList[i],xlist,ylist);
		case CurveItemTitle::Normal:
			itemTitle2Data(_curveItemTitleList[i],xlist,ylist);
		}
		QCPCurve* curve=static_cast<QCPCurve*>(plot->plottable(i+1));
		curve->setData(xlist,ylist);
	}
	emit plotDataUpdated();
	plot->rescaleAxes();
	plot->replot();
	return true;
}

void CustomCurvePlot::copyXRange()
{
	QByteArray output;
	QCPRange range =_customPlot->xAxis->range();
	QString s = QString::number(range.lower)+","+QString::number(range.upper);
	//输入    
	QDataStream out(&output,QIODevice::WriteOnly);   
	out<<s;

	QMimeData *mimeData = new QMimeData;
	QString mimeType = QString("application/tdypre:curveXRange");
	mimeData->setData(mimeType, output);

	QApplication::clipboard()->setMimeData(mimeData);
}

void CustomCurvePlot::pasteXRange()
{
	QString mimeType = QString("application/tdypre:curveXRange");
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
		_customPlot->xAxis->setRange(d1,d2);
		_customPlot->replot();
	}
}

void CustomCurvePlot::showPointPosition()
{
	if(_curvePointsTracer->isShowPointData())
		_curvePointsTracer->hidePointData();
	else
		_curvePointsTracer->showPointData();
}

void CustomCurvePlot::showAllPosition()
{
	if (_customPlot->plottableCount() == 1)
	{
		_curvePointsTracer->getPointsAction()->setChecked(false);
		return;
	}
	
	if (_curvePointsTracer->isShowAllData())
		_curvePointsTracer->hideAllData();
	else
		_curvePointsTracer->showAllData();
}

void CustomCurvePlot::setInitialCurveProperty( QCPCurve* curve )
{
	int c=_currentColorIndex;
	_currentColorIndex=(_currentColorIndex+1)%color_size;
	QColor penColor=QColor(int_colors[c*3],int_colors[c*3+1],int_colors[c*3+2]);
	QPen graphPen;
	graphPen.setColor(penColor);
	graphPen.setWidth(2);
	curve->setPen(graphPen);
}

void CustomCurvePlot::addCurveIntoPlot( QCPCurve* curve )
{
	getCustomPlot()->addPlottable(curve);
	
	if (_curveItemTitleList.size()==1)
		getCustomPlot()->rescaleAxes();

	emit curveAdded(curve);

	getCustomPlot()->replot();
}

CurveItemTitle* CustomCurvePlot::getCurveItemTitle( QCPAbstractPlottable* item )
{
	for(int i=0;i<_curveItemTitleList.size();++i)
	{
		CurveItemTitle& c=_curveItemTitleList[i];
		if(c.relatedPlotable==item)
			return &_curveItemTitleList[i];
	}
	return NULL;
}

void CustomCurvePlot::showExchangeDataMenu()
{
	QPoint globalPos =QCursor::pos();

	QMenu menu;

	QMenu* exportMenu = new QMenu("Export ...");
	menu.addMenu(exportMenu);

	QAction* ac=exportMenu->addAction("Export ...",this,SLOT(exportAllCurves()));
	exportMenu->addAction(ac);
	if(_curveItemTitleList.size()==0)
		ac->setEnabled(false);

	ac = exportMenu->addAction("JPEG (*.jpg;*.jpeg)");
	connect(ac,SIGNAL(triggered()),_curvePointsTracer,SLOT(onSaveViewToFile()));

	ac = exportMenu->addAction("PNG (*.png)",this,SLOT(onSaveViewToFile()));
	connect(ac,SIGNAL(triggered()),_curvePointsTracer,SLOT(onSaveViewToFile()));

	ac = exportMenu->addAction("BMP (*.bmp)",this,SLOT(onSaveViewToFile()));
	connect(ac,SIGNAL(triggered()),_curvePointsTracer,SLOT(onSaveViewToFile()));

	ac = exportMenu->addAction("PDF (*.pdf)",this,SLOT(onSaveViewToFile()));
	connect(ac,SIGNAL(triggered()),_curvePointsTracer,SLOT(onSaveViewToFile()));

	ac=menu.addAction("Import ...",this,SLOT(importCurves()));
	menu.addAction(ac);

	ac = _curvePointsTracer->getCopyViewImgAction();
	menu.addAction(ac);

	menu.exec(globalPos);
}

void CustomCurvePlot::showConfigMenu()
{
	QPoint globalPos =QCursor::pos();
	CurveConfigDialog dlg(_customPlot);

	_configMenu->clear();

	MimeData mimeData;
	_configDir = dlg.getConfigDir();
	mimeData.load(_configDir + "prevtc.ini");

	QAction* ac=_configMenu->addAction(tr("Edit..."),&dlg,SLOT(exec()));
	ac->setIcon(QIcon(":/resources/menu/a032x16x16.png"));
	connect(ac,SIGNAL(hovered ()),this,SLOT(onHovered ()));
	/*if(!mimeData.hasFormat("insviewer/prevtc/config/id"))
		ac->setEnabled(false);*/

	_configMenu->addAction(ac);

	ac=_configMenu->addAction(tr("Add current"),&dlg,SLOT(saveConfig()));
	ac->setIcon(QIcon(":/resources/menu/a034x16x16.png"));
	connect(ac,SIGNAL(hovered ()),this,SLOT(onHovered ()));
	_configMenu->addAction(ac);

	_configMenu->addSeparator();
	
	if(mimeData.hasFormat("insviewer/prevtc/config/id"))
	{
		QSharedPointer<QDataStream> readStream = mimeData.startReadCustomData("insviewer/prevtc/config/id");
		QString idStr;//1|ss,2|dd
		*readStream>>idStr;
		_idStr = idStr;
		QStringList list = idStr.split(",",QString::SkipEmptyParts);

		foreach(QString idMap,list)
		{
			QString displayName,id;
			id = idMap.split("|",QString::SkipEmptyParts)[0];
			displayName = idMap.split("|",QString::SkipEmptyParts)[1];
			QSharedPointer<QDataStream> stream = mimeData.startReadCustomData(QString("insviewer/prevtc/config/%1").arg(id));
			QPixmap p;
			*stream>>p;
			p.save(_configDir+id+".png");
			QAction* ac=_configMenu->addAction(displayName,&dlg,SLOT(openConfig()));
			connect(ac,SIGNAL(	hovered ()),this,SLOT(onHovered ()));
			_configMenu->addAction(ac);
			ac->setData(id);
		}
	}

	_configMenu->exec(globalPos);
}

void CustomCurvePlot::onHovered()
{
	_configMenu->setToolTip("");
	QAction* ac = (QAction*)sender();
	QString id = ac->data().toString();
	if(id.isEmpty())
		_configMenu->setToolTip(ac->text());
	else
		_configMenu->setToolTip(QString("<img src=\"%1\"/>").arg(_configDir+id+".png"));
}

bool CustomCurvePlot::eventFilter( QObject * o, QEvent * e )
{
	return QObject::eventFilter(o,e);
}

void CustomCurvePlot::onAboutToHide()
{
	QStringList list = _idStr.split(",",QString::SkipEmptyParts);
	foreach(QString idMap ,list)
	{
		QString id = idMap.split("|",QString::SkipEmptyParts)[0];
		QFile::remove(_configDir+id+".png");
	}
}

void CustomCurvePlot::mouseMoveSignal( QMouseEvent *event )
{
	if (draggingLegend)
	{
		QRectF rect = _customPlot->axisRect()->insetLayout()->insetRect(0);
		// since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
		QPointF mousePoint((event->pos().x()-_customPlot->axisRect()->left())/(double)_customPlot->axisRect()->width(),
			(event->pos().y()-_customPlot->axisRect()->top())/(double)_customPlot->axisRect()->height());
		rect.moveTopLeft(mousePoint-dragLegendOrigin);
		_customPlot->axisRect()->insetLayout()->setInsetRect(0, rect);
		_customPlot->replot();
	}
}

void CustomCurvePlot::mousePressSignal( QMouseEvent *event )
{
	if (_customPlot->legend->selectTest(event->pos(), false) > 0 )
	{
		draggingLegend = true;
		// since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
		QPointF mousePoint((event->pos().x()-_customPlot->axisRect()->left())/(double)_customPlot->axisRect()->width(),
			(event->pos().y()-_customPlot->axisRect()->top())/(double)_customPlot->axisRect()->height());
		dragLegendOrigin = mousePoint-_customPlot->axisRect()->insetLayout()->insetRect(0).topLeft();
	}
}

void CustomCurvePlot::mouseReleaseSignal( QMouseEvent *event )
{
	Q_UNUSED(event)
		draggingLegend = false;
}

void CustomCurvePlot::beforeReplot()
{
	if(! _customPlot->axisRect()->insetLayout()->insetPlacement(0))
		_customPlot->legend->setMaximumSize(_customPlot->legend->minimumSizeHint());
}

void CustomCurvePlot::legendDragOnOrOff()
{
	int a = _customPlot->axisRect()->insetLayout()->insetPlacement(0);
	if(!a)
		//开启变关闭
		_customPlot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipBorderAligned);
	else
	{
		//关闭变开启
		_customPlot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
		_customPlot->axisRect()->insetLayout()->setInsetRect(0, QRectF(0.54,(1-(_customPlot->legend->itemCount()*0.055)),0.4,0.4));
	}

	_customPlot->replot();
}



