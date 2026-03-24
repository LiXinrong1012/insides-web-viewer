#ifndef ADDCURVETHREAD_H
#define ADDCURVETHREAD_H

#include <QThread>
#include <QVector>

#include "prevtc/resultselectorwidget.h"

class ResultExpressionParser;
namespace INSIDES{
	class IResultItem;
	class FlexResultItem;
}

class AddCurveThread : public QThread
{
	Q_OBJECT

public:
	AddCurveThread(int frameCount,INSIDES::IResults* results,INSIDES::IResultItem* resultItem,const CurveItemTitle& itemTitle,QObject* parent);
	AddCurveThread(int frameCount,INSIDES::IResults* results,INSIDES::FlexResultItem* flexResultItem,const CurveItemTitle& itemTitle,QObject* parent);
	AddCurveThread(int frameCount,INSIDES::IResults* results,ResultExpressionParser* parser,QObject* parent);
	~AddCurveThread();

	const QVector<double>& getXList(){return _xlist;}
	const QVector<double>& getYList(){return _ylist;}

protected:
	virtual void run();

private:
	int _frameCount;
	INSIDES::IResults*			_results;
	INSIDES::IResultItem*		_resultItem;
	INSIDES::FlexResultItem*	_flexResultItem;
	ResultExpressionParser*		_parser;
	CurveItemTitle				_itemTitle;
	QVector<double>				_xlist;
	QVector<double>				_ylist;

	int							_runType;
};

#endif // ADDCURVETHREAD_H
