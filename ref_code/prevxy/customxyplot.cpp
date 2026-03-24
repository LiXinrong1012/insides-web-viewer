#include "customxyplot.h"

#include "qcustomplot/qcustomplot.h"

#include "base/Console.h"

#include "precore/modeldocument.h"
#include "precore/FlexResultItem.h"
#include "precore/RigidResultItem.h"
#include "precore/ResultDocument.h"

#include "pubbase/mimedata.h"

#include "xyitemtitle.h"
#include "xypointstracer.h"
#include "resultexpressionparser.h"
#include "xycurve.h"
#include "curveconfigdialog.h"

#include <string>
#include <QtGui>

using namespace Base;
using namespace INSIDES;

///默认的曲线颜色配置数组
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

CustomXYPlot::CustomXYPlot(QObject *parent,QCustomPlot* plot)
	: QObject(parent)
	,_currentColorIndex(0)
	,_legendDrag(false)
{
	myResultDocument()->attachListener(this);
	
	_customPlot=plot;
	_xyPointsTracer=new XYPointsTracer(this,this);
	init();

	_configMenu = new QMenu();
	connect(_configMenu,SIGNAL(aboutToHide()),this,SLOT(onAboutToHide()));

	_updateSelectCurveXAction = new QAction("update selected curve x data",0);
	connect(_updateSelectCurveXAction,SIGNAL(triggered()),this,SLOT(updateSelectedCurve()));

	_updateSelectCurveYAction = new QAction("update selected curve y data",0);
	connect(_updateSelectCurveYAction,SIGNAL(triggered()),this,SLOT(updateSelectedCurve()));
	
	draggingLegend = false;

	connect(_customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMoveSignal(QMouseEvent*)));
	connect(_customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressSignal(QMouseEvent*)));
	connect(_customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseReleaseSignal(QMouseEvent*)));
	connect(_customPlot, SIGNAL(beforeReplot()), this, SLOT(beforeReplot()));
}

CustomXYPlot::~CustomXYPlot()
{
	myResultDocument()->disattachListener(this);
	delete _configMenu;
}

///更改曲线视图默认外观
bool CustomXYPlot::init()
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

	_customPlot->xAxis->setLabel("data-x");
	_customPlot->xAxis->setLabelFont(axisLabelFont);
	_customPlot->yAxis->setLabel("data-y");
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

	connect(_customPlot,SIGNAL(	plottableClick (QCPAbstractPlottable* , QMouseEvent* )),this,SLOT(	onPlottableClick (QCPAbstractPlottable *, QMouseEvent *)));

	// connect slot that shows a message in the status bar when a graph is clicked:
	connect(_customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));
	connect(_customPlot,SIGNAL(itemClick ( QCPAbstractItem *  , QMouseEvent *    ) ),_xyPointsTracer,SLOT(onItemClicked( QCPAbstractItem *  )));

	// setup policy and connect slot for context menu popup:
	_customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(_customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
	connect(this,SIGNAL(updateTextPosition()),_xyPointsTracer,SLOT(updateTextPosition()));

	return true;
}

void CustomXYPlot::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
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

void CustomXYPlot::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
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

void CustomXYPlot::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
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
			XYItemTitle* itemTitle=getCurveItemTitle(plItem->plottable());
			if(itemTitle)
				itemTitle->name=newName;

			_customPlot->replot();
		}
	}
}

void CustomXYPlot::selectionChanged()
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

void CustomXYPlot::mousePress()
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

void CustomXYPlot::mouseWheel()
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

void CustomXYPlot::removeSelectedGraph()
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
				curveItemTitleList.removeAt(i-1);
				break;;
			}
		}

		emit curveAboutToRemove(selected);
		_customPlot->removePlottable(selected);
	}

	if (_xyPointsTracer->isShowAllData())
	{
		_xyPointsTracer->hideAllData();
		_xyPointsTracer->showAllData();
	}

	if (_xyPointsTracer->isShowPointData())
	{
		;//	  _curvePointsTracer->hidePointData();
		//	  _curvePointsTracer->showPointData();
	}
	_customPlot->replot();
}

void CustomXYPlot::removeAllGraphs()
{
	_customPlot->clearGraphs();

	while(_customPlot->plottableCount()>0){
		emit curveAboutToRemove(_customPlot->plottable(0));
		_customPlot->removePlottable(0);
	}
	curveItemTitleList.clear();
	//  _curvePointsTracer->clearAllDatatips();
	_customPlot->replot();
	//  _curvePointsTracer->hideAllData();
}

void CustomXYPlot::contextMenuRequest(QPoint pos)
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
			menu->addAction(_updateSelectCurveXAction);
			menu->addAction(_updateSelectCurveYAction);
			menu->addAction("remove selected graph", this, SLOT(removeSelectedGraph()));
		}

		if (_customPlot->selectedGraphs().size()==0)
		{
			menu->addAction("remove all graphs", this, SLOT(removeAllGraphs()));
			if (_xyPointsTracer->isShowPointData())
			{
				if (_xyPointsTracer->isShowTenLine())
					menu->addAction("hide tenLine",_xyPointsTracer,SLOT(showOrHideTenLine()));
				else
					menu->addAction("show tenLine",_xyPointsTracer,SLOT(showOrHideTenLine()));
			}

			if (_xyPointsTracer->isShowPointData())
			{
				menu->addSeparator();

				QMenu *styleMenu = menu->addMenu("display style");
				styleMenu->addAction(_xyPointsTracer->getDatatipStyleAction());
				styleMenu->addAction(_xyPointsTracer->getWindowStyleAction());

				menu->addAction(_xyPointsTracer->getCreateNewDatatipAction());
				menu->addAction(_xyPointsTracer->getDeleteAllDatatipsAction());
				menu->addAction(_xyPointsTracer->getCopyToClipboardAction());
				menu->addAction(_xyPointsTracer->getSetDisplayFormatAction());

				menu->addSeparator();
			}

			QMenu* copyMenu = menu->addMenu("copy");
			QAction* copyXAction = copyMenu->addAction("x range",this,SLOT(copyXRange()));
			copyMenu->addAction(_xyPointsTracer->getCopyYAction());
			copyMenu->addAction(_xyPointsTracer->getCopyCurveAction());

			QMenu *pasteMenu = menu->addMenu("paste");
			QAction* pasteXAction = pasteMenu->addAction("x range",this,SLOT(pasteXRange()));
			pasteMenu->addAction(_xyPointsTracer->getPasteYAction());
			pasteMenu->addAction(_xyPointsTracer->getPasteCurveAction());

			QString mimeType = QString("application/tdypre:curveXRange");
			QString mimeYType = QString("application/tdypre:curveYRange");
			QString mimeCurveType = QString("application/tdypre:curves");
			const QMimeData* mimeData=QApplication::clipboard()->mimeData();

			if(mimeData->hasFormat(mimeType))
				pasteXAction->setEnabled(true);
			else
				pasteXAction->setEnabled(false);

			if (mimeData->hasFormat(mimeYType))
				_xyPointsTracer->getPasteYAction()->setEnabled(true);
			else
				_xyPointsTracer->getPasteYAction()->setEnabled(false);

			if (mimeData->hasFormat(mimeCurveType))
				_xyPointsTracer->getPasteCurveAction()->setEnabled(true);
			else
				_xyPointsTracer->getPasteCurveAction()->setEnabled(false);

			if(_customPlot->selectedItems().count() ==0)
				_xyPointsTracer->getCopyToClipboardAction()->setEnabled(false);
			else
				_xyPointsTracer->getCopyToClipboardAction()->setEnabled(true);

			if(_customPlot->selectedPlottables().count() ==0)
				_xyPointsTracer->getCopyCurveAction()->setEnabled(false);
			else
				_xyPointsTracer->getCopyCurveAction()->setEnabled(true);
		}
	}
	menu->popup(_customPlot->mapToGlobal(pos));
}

void CustomXYPlot::moveLegend()
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

void CustomXYPlot::graphClicked(QCPAbstractPlottable *plottable)
{
	QString str=QString("Clicked on graph '%1'.").arg(plottable->name());
	QString s = plottable->name();
	Base::Console().Log(str.toStdString().c_str());
	_xyPointsTracer->onPlottableClicked(plottable);
}

void CustomXYPlot::viewAll()
{
	_customPlot->rescaleAxes(true);
	_customPlot->replot();
}

IResultItem* CustomXYPlot::getRelatedResultItem( const QString& itemname )
{
	BaseItem* item=myDocument()->findItem(itemname);
	if(!item)
		return NULL;

	if(myResultDocument()->getResults())
		return myResultDocument()->getResults()->findResultItem(item).data();

	return NULL;
}

bool CustomXYPlot::itemTitle2Data(const QString& content,int secIndex,int subsecIndex,int subsubsecIndex,int nodeElemIndex,QVector<double>& list)
{
	IResultItem* resultItem=getRelatedResultItem(content);
	if(!resultItem)
		return false;

	int frameCount=myResultDocument()->getResults()->getFrameCount();
	if(frameCount<=0)
		return false;

	QString itemName=resultItem->connectedItem()->getKeyName();
	QString sectionName=resultItem->sectionName(secIndex);
	QString subSectionName=resultItem->subSectionName(secIndex,subsecIndex);
	QString subsubSectionName=resultItem->subsubSectionName(secIndex,subsecIndex,subsubsecIndex);
	QString indexName;

	IResults* results=myResultDocument()->getResults();

	int currentPos=results->getCurrentFrame();
	if(nodeElemIndex>=0 && secIndex!=0)
	{
		FlexResultItem* flexResultItem=(FlexResultItem*)resultItem;
		for(int i=0;i<frameCount;++i)
		{
			resultItem->setPos(i);

			double* d=flexResultItem->getNodeElemData(secIndex,subsecIndex,nodeElemIndex);
			double va=d[subsubsecIndex];

			list.push_back(va);
		}

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
		for(int i=0;i<frameCount;++i)
		{
			resultItem->setPos(i);

			double* d=resultItem->getData(secIndex,subsecIndex,subsubsecIndex);
			double va=d[0];

			list.push_back(va);
		}
	}
	resultItem->setPos(currentPos);
	return true;
}

bool CustomXYPlot::itemTitle2DataCustom( const QString& content,
	QVector<double>& list)
{
 	int frameCount=myResultDocument()->getResults()->getFrameCount();
 	if(frameCount<=0)
 		return false;
 
 	IResults* results=myResultDocument()->getResults();
 
 	int originalPos=results->getCurrentFrame();
 	std::string input=content.toStdString();
 	ResultExpressionParser parser;
 	if(!parser.setExpressionStr(input))
 		return false;
 
 	for(int i=0;i<frameCount;++i)
 	{
 		double t=results->getTime(i);
 		parser.setPos(i);
 		parser.setTime(t);
 		double va=parser.eval();
 
 		list.push_back(va);
 	}
 	parser.setPos(originalPos);

	return true;
}

void CustomXYPlot::exportAllCurves()
{
	if(curveItemTitleList.size()==0)
		return;

	QString fileName= QFileDialog::getSaveFileName(_customPlot, tr("Save File"),
		".",
		tr("dat (*.dat *.dat *.dat)"));

	if(fileName.isEmpty())
		return;

	QVector<QVector<double> > allDatas;
	QVector<QString>	titles;
		
	QCPCurve* curve=(QCPCurve*)curveItemTitleList[0].relatedPlotable;
	QCPCurveDataMap* data=curve->data();

	QVector<double> timeData;
	for(QCPCurveDataMap::Iterator b=data->begin();b!=data->end();++b)
		timeData.push_back(b->key);

	allDatas.push_back(timeData);
	titles.push_back("Time");

	for(int i=0;i<curveItemTitleList.size();++i){
		QCPCurve* curve=(QCPCurve*)curveItemTitleList[i].relatedPlotable;
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
			out<<QString("%1").arg(titles[i],20)<<"\t";
		out<<endl;

		int dataLen=allDatas[0].size();
		for(int i=0;i<dataLen;++i)
		{
			for(int j=0;j<n;++j)
				if(i<allDatas[j].size())
					out<<QString("%1").arg(allDatas[j][i],20,'e',13)<<"\t";
				else
					out<<"\t";
			out<<endl;
		}
	}
}

void CustomXYPlot::importCurves()
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
		XYItemTitle title;
		title.type=XYItemTitle::IsImported;
		title.name=titles[i];
		title.xs=allDatas[0];
		title.ys=allDatas[i];
		addMyCurve(title);
	}
}

bool CustomXYPlot::addMyCurve( const XYItemTitle& itemTitle )
{
	QVector<double> xlist,ylist;
	bool result=false;

	switch(itemTitle.type){
	case XYItemTitle::Normal:
		{
			result=itemTitle2Data(itemTitle.itemContent,itemTitle.secIndex,itemTitle.subsecIndex,itemTitle.subsubsecIndex,itemTitle.nodeElemIndex,xlist);
			if(itemTitle.yType == XYItemTitle::Custom)
				result = itemTitle2DataCustom(itemTitle.itemYContent,ylist);
			else
				result = itemTitle2Data(itemTitle.itemYContent,itemTitle.secYIndex,itemTitle.subsecYIndex,itemTitle.subsubsecYIndex,itemTitle.nodeElemYIndex,ylist);
		}
		break;
	case XYItemTitle::Custom:
		{
			result=itemTitle2DataCustom(itemTitle.itemContent,xlist);
			if(itemTitle.yType == XYItemTitle::Normal)
				result = itemTitle2Data(itemTitle.itemYContent,itemTitle.secYIndex,itemTitle.subsecYIndex,itemTitle.subsubsecYIndex,itemTitle.nodeElemYIndex,ylist);
			else
				result=itemTitle2DataCustom(itemTitle.itemYContent,ylist);
		}
		break;
	case XYItemTitle::IsImported:
		xlist=itemTitle.xs;
		ylist=itemTitle.ys;
		result=true;
		break;
	}

	if(!result){
		Console().Error("Add curve failed.");
		return false;
	}

	QCustomPlot* plot=getCustomPlot();
	QCPCurve* curve=new QCPCurve(plot->xAxis,plot->yAxis);
	curve->setData(xlist,ylist);
	curve->setName(itemTitle.name);
	
	//设置曲线的外形
	setInitialCurveProperty(curve);

	XYItemTitle tmpTitle=itemTitle;
	tmpTitle.relatedPlotable=curve;
	curveItemTitleList.push_back(tmpTitle);

	addCurveIntoPlot(curve);
	
	return true;
}

bool CustomXYPlot::updateMyCurve( const XYItemTitle& itemTitle )
{
	QVector<double> xlist,ylist;
	bool result=false;

	QCPCurve* cu = NULL;
	for (int i=0;i<curveItemTitleList.count();i++)
	{
		if(curveItemTitleList[i].relatedPlotable == itemTitle.relatedPlotable)
		{
			cu = curveItemTitleList[i].relatedPlotable;
			curveItemTitleList[i] = itemTitle;
			break;
		}
	}
	
	if(!cu)
		return false;

	switch(itemTitle.type)
	{
	case XYItemTitle::Normal:
		{
			result=itemTitle2Data(itemTitle.itemContent,itemTitle.secIndex,itemTitle.subsecIndex,itemTitle.subsubsecIndex,itemTitle.nodeElemIndex,xlist);
			if(itemTitle.yType == XYItemTitle::Custom)
				result = itemTitle2DataCustom(itemTitle.itemYContent,ylist);
			else
				result = itemTitle2Data(itemTitle.itemYContent,itemTitle.secYIndex,itemTitle.subsecYIndex,itemTitle.subsubsecYIndex,itemTitle.nodeElemYIndex,ylist);
		}
		break;
	case XYItemTitle::Custom:
		{
			result=itemTitle2DataCustom(itemTitle.itemContent,xlist);
			if(itemTitle.yType == XYItemTitle::Normal)
				result = itemTitle2Data(itemTitle.itemYContent,itemTitle.secYIndex,itemTitle.subsecYIndex,itemTitle.subsubsecYIndex,itemTitle.nodeElemYIndex,ylist);
			else
				result=itemTitle2DataCustom(itemTitle.itemYContent,ylist);
		}
		break;
	case XYItemTitle::IsImported:
		xlist=itemTitle.xs;
		ylist=itemTitle.ys;
		result=true;
		break;
	}

	if(!result)
	{
		Console().Error("Update curve failed.");
		return false;
	}
	cu->setData(xlist,ylist);

	_customPlot->replot();
	return true;
}

void CustomXYPlot::updateSelectedCurve()
{
	QList<QCPAbstractPlottable*> list = _customPlot->selectedPlottables();
	if(list.isEmpty())
		return;

	QCPCurve* cu = static_cast<QCPCurve*>(list[0]);
	XYItemTitle title;
	bool noTitle = true;
	foreach(XYItemTitle tmp ,curveItemTitleList)
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

	bool isUpdateXData=true;
	QAction* ac = (QAction*)sender();
	if(ac == _updateSelectCurveXAction)
		isUpdateXData = true;
	if(ac == _updateSelectCurveYAction)
		isUpdateXData = false;
	
	emit updateSelectedCurve(title,isUpdateXData);

	updateCurve(title,isUpdateXData);
}

bool CustomXYPlot::updateAllMyCurve()
{
	QCustomPlot* plot=getCustomPlot();
	for(size_t i=0;i<curveItemTitleList.size();++i)
	{
		if(i>=plot->plottableCount()-1)
			break;

		QVector<double> xlist,ylist;
		QString title;

		if(curveItemTitleList[i].type==XYItemTitle::IsImported)
			continue;

		switch(curveItemTitleList[i].type)
		{
		case XYItemTitle::Normal:
			{
				itemTitle2Data(curveItemTitleList[i].itemContent,curveItemTitleList[i].secIndex,curveItemTitleList[i].subsecIndex,curveItemTitleList[i].subsubsecIndex,curveItemTitleList[i].nodeElemIndex,xlist);
				if(curveItemTitleList[i].yType == XYItemTitle::Custom)
					itemTitle2DataCustom(curveItemTitleList[i].itemYContent,ylist);
				else
					itemTitle2Data(curveItemTitleList[i].itemYContent,curveItemTitleList[i].secYIndex,curveItemTitleList[i].subsecYIndex,curveItemTitleList[i].subsubsecYIndex,curveItemTitleList[i].nodeElemYIndex,ylist);
			}
			break;
		case XYItemTitle::Custom:
			{
				itemTitle2DataCustom(curveItemTitleList[i].itemContent,xlist);
				if(curveItemTitleList[i].yType == XYItemTitle::Normal)
					itemTitle2Data(curveItemTitleList[i].itemYContent,curveItemTitleList[i].secYIndex,curveItemTitleList[i].subsecYIndex,curveItemTitleList[i].subsubsecYIndex,curveItemTitleList[i].nodeElemYIndex,ylist);
				else
					itemTitle2DataCustom(curveItemTitleList[i].itemYContent,ylist);
			}
			break;
		QCPCurve* curve=static_cast<QCPCurve*>(plot->plottable(i+1));
		curve->setData(xlist,ylist);
		}
	}
	emit plotDataUpdated();
	plot->rescaleAxes();
	plot->replot();
	return true;
}

void CustomXYPlot::copyXRange()
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

void CustomXYPlot::pasteXRange()
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

void CustomXYPlot::showPointPosition()
{
	if(_xyPointsTracer->isShowPointData())
		_xyPointsTracer->hidePointData();
	else
		_xyPointsTracer->showPointData();
}

void CustomXYPlot::setInitialCurveProperty( QCPCurve* curve )
{
	int c=_currentColorIndex;
	_currentColorIndex=(_currentColorIndex+1)%color_size;
	QColor penColor=QColor(int_colors[c*3],int_colors[c*3+1],int_colors[c*3+2]);
	QPen graphPen;
	graphPen.setColor(penColor);
	graphPen.setWidth(2);
	curve->setPen(graphPen);
}

void CustomXYPlot::addCurveIntoPlot( QCPCurve* curve )
{
	getCustomPlot()->addPlottable(curve);
	
	if (curveItemTitleList.size()==1)
		getCustomPlot()->rescaleAxes();

	emit curveAdded(curve);

	getCustomPlot()->replot();
}

XYItemTitle* CustomXYPlot::getCurveItemTitle( QCPAbstractPlottable* item )
{
	for(int i=0;i<curveItemTitleList.size();++i)
	{
		XYItemTitle& c=curveItemTitleList[i];
		if(c.relatedPlotable==item)
			return &curveItemTitleList[i];
	}
	return NULL;
}

void CustomXYPlot::showExchangeDataMenu()
{
	QPoint globalPos =QCursor::pos();

	QMenu menu;

	QMenu* exportMenu = new QMenu("Export ...");
	menu.addMenu(exportMenu);

	QAction* ac=exportMenu->addAction("Export ...",this,SLOT(exportAllCurves()));
	exportMenu->addAction(ac);
	if(curveItemTitleList.size()==0)
		ac->setEnabled(false);

 	ac = exportMenu->addAction("JPEG (*.jpg;*.jpeg)");
 	connect(ac,SIGNAL(triggered()),_xyPointsTracer,SLOT(onSaveViewToFile()));
 
 	ac = exportMenu->addAction("PNG (*.png)",this,SLOT(onSaveViewToFile()));
 	connect(ac,SIGNAL(triggered()),_xyPointsTracer,SLOT(onSaveViewToFile()));
 
 	ac = exportMenu->addAction("BMP (*.bmp)",this,SLOT(onSaveViewToFile()));
 	connect(ac,SIGNAL(triggered()),_xyPointsTracer,SLOT(onSaveViewToFile()));
 
 	ac = exportMenu->addAction("PDF (*.pdf)",this,SLOT(onSaveViewToFile()));
 	connect(ac,SIGNAL(triggered()),_xyPointsTracer,SLOT(onSaveViewToFile()));
 
 	ac=menu.addAction("Import ...",this,SLOT(importCurves()));
 	menu.addAction(ac);
 
 	ac = _xyPointsTracer->getCopyViewImgAction();
 	menu.addAction(ac);

	menu.exec(globalPos);
}

void CustomXYPlot::showConfigMenu()
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
	if(!mimeData.hasFormat("insviewer/prevtc/config/id"))
		ac->setEnabled(false);

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

void CustomXYPlot::onHovered()
{
	_configMenu->setToolTip("");
	QAction* ac = (QAction*)sender();
	QString id = ac->data().toString();
	if(id.isEmpty())
		_configMenu->setToolTip(ac->text());
	else
		_configMenu->setToolTip(QString("<img src=\"%1\"/>").arg(_configDir+id+".png"));
}

bool CustomXYPlot::eventFilter( QObject * o, QEvent * e )
{
	return QObject::eventFilter(o,e);
}

void CustomXYPlot::onAboutToHide()
{
	QStringList list = _idStr.split(",",QString::SkipEmptyParts);
	foreach(QString idMap ,list)
	{
		QString id = idMap.split("|",QString::SkipEmptyParts)[0];
		QFile::remove(_configDir+id+".png");
	}
}

void CustomXYPlot::mouseMoveSignal( QMouseEvent *event )
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

void CustomXYPlot::mousePressSignal( QMouseEvent *event )
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

void CustomXYPlot::mouseReleaseSignal( QMouseEvent *event )
{
	Q_UNUSED(event)
	draggingLegend = false;
}

void CustomXYPlot::beforeReplot()
{
	if(! _customPlot->axisRect()->insetLayout()->insetPlacement(0))
		_customPlot->legend->setMaximumSize(_customPlot->legend->minimumSizeHint());
}

void CustomXYPlot::legendDragOnOrOff()
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

void CustomXYPlot::updateCurve( XYItemTitle title,bool isX )
{
	QVector<double> xlist,ylist;
	bool result=false;

	QCPCurve* cu = NULL;
	foreach(XYItemTitle tmp, curveItemTitleList)
	{
		if(tmp.relatedPlotable == title.relatedPlotable)
		{
			cu = tmp.relatedPlotable;
			break;
		}
	}
	if(!cu)
		return;
	
	if(isX)//更新X轴数据
	{
		switch(title.type)
		{
		case XYItemTitle::Normal:
			result=itemTitle2Data(title.itemContent,title.secIndex,title.subsecIndex,title.subsubsecIndex,title.nodeElemIndex,xlist);
			break;
		case XYItemTitle::Custom:
			result=itemTitle2DataCustom(title.itemContent,xlist);
			break;
		case XYItemTitle::IsImported:
			xlist=title.xs;
			result=true;
			break;
		}

		QCPCurveDataMap *data = cu->data();
		for(QCPCurveDataMap::Iterator b=data->begin();b!=data->end();++b)
			ylist.push_back(b->value);
	}
	else
	{
		switch(title.yType)
		{
		case XYItemTitle::Normal:
			result = itemTitle2Data(title.itemYContent,title.secYIndex,title.subsecYIndex,title.subsubsecYIndex,title.nodeElemYIndex,ylist);
			break;
		case XYItemTitle::Custom:
			result=itemTitle2DataCustom(title.itemYContent,ylist);
			break;
		case XYItemTitle::IsImported:
			ylist=title.ys;
			result=true;
			break;
		}

		QCPCurveDataMap *data = cu->data();
		for(QCPCurveDataMap::Iterator b=data->begin();b!=data->end();++b)
			xlist.push_back(b->key);
	}
	if(!result)
	{
		Console().Error("Update curve failed.");
		return ;
	}

	cu->setData(xlist,ylist);
	_customPlot->replot();
}

void CustomXYPlot::onResultCurrentFrameChanged()
{
	_xyPointsTracer->resultCurrentFrameChanged();
	_customPlot->replot();
}

void CustomXYPlot::showAllPosition()
{
	if (_xyPointsTracer->isShowAllData())
		_xyPointsTracer->hideAllData();
	else
		_xyPointsTracer->showAllData();
}



