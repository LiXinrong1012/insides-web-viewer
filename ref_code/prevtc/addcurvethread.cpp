#include "addcurvethread.h"
#include "base/Console.h"
#include "base/MultiProgressOperator.h"

#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"

#include "resultexpressionparser.h"

#include <QVector>

AddCurveThread::AddCurveThread(int frameCount,INSIDES::IResults* results,INSIDES::IResultItem* resultItem,const CurveItemTitle& itemTitle,QObject *parent)
	: QThread(parent)
	,_frameCount(frameCount)
	,_results(results)
	,_resultItem(resultItem)
	,_itemTitle(itemTitle)
	,_runType(0)
{

}

AddCurveThread::AddCurveThread( int frameCount,INSIDES::IResults* results,INSIDES::FlexResultItem* flexResultItem,const CurveItemTitle& itemTitle,QObject* parent )
	:QThread(parent)
	,_frameCount(frameCount)
	,_results(results)
	,_flexResultItem(flexResultItem)
	,_itemTitle(itemTitle)
	,_runType(1)
{

}

AddCurveThread::AddCurveThread( int frameCount,INSIDES::IResults* results,ResultExpressionParser* parser,QObject* parent )
	:QThread(parent)
	,_frameCount(frameCount)
	,_results(results)
	,_parser(parser)
	,_runType(2)
{

}

AddCurveThread::~AddCurveThread()
{

}

void AddCurveThread::run()
{
	Base::MultiProgressOperator::startProgress("Add Curve");
	
	int secIndex=_itemTitle.secIndex;
	int subsecIndex=_itemTitle.subsecIndex;
	int subsubsecIndex=_itemTitle.subsubsecIndex;
	int nodeElemIndex=_itemTitle.nodeElemIndex;

	if(_runType == 0)
	{
		for(int i=0;i<_frameCount;++i)
		{
			double t=_results->getTime(i);
			_resultItem->setPos(i);
			double* d=_resultItem->getData(secIndex,subsecIndex,subsubsecIndex);
			double va=d[0];

			_xlist.push_back(t);
			_ylist.push_back(va);
			Base::MultiProgressOperator::setProgress((i*100)/_frameCount);
		}
	}
	else if(_runType == 1)
	{
		for(int i=0;i<_frameCount;++i)
		{
			double t=_results->getTime(i);
			_resultItem->setPos(i);
			double* d=_flexResultItem->getNodeElemData(secIndex,subsecIndex,nodeElemIndex);
			double va=d[subsubsecIndex];

			_xlist.push_back(t);
			_ylist.push_back(va);
			Base::MultiProgressOperator::setProgress((i*100)/_frameCount);
		}
	}
	else if(_runType == 2)
	{
		for(int i=0;i<_frameCount;++i)
		{
			double t=_results->getTime(i);
			_parser->setPos(i);
			_parser->setTime(t);
			double va=_parser->eval();

			_xlist.push_back(t);
			_ylist.push_back(va);
			Base::MultiProgressOperator::setProgress((i*100)/_frameCount);
		}
	}

	Base::MultiProgressOperator::stopProgress();
}
