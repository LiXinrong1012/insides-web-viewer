#include "xycurve.h"

XYCurve::XYCurve( QCPAxis *keyAxis, QCPAxis *valueAxis )
	:QCPCurve(keyAxis,valueAxis)
{
}

XYCurve::~XYCurve()
{
}

QVector<double> XYCurve::getCurveXVector( QCPAbstractPlottable* plottable )
{
	QCPCurve *curve = qobject_cast<QCPCurve*>(plottable);
	QCPCurveDataMap *map =curve->data();
	QVector<double> xVect;
	for (QCPCurveDataMap::iterator it = map->begin();it != map->end(); it++)
		xVect.push_back(it->key);
	
	return xVect;
}

QVector<double> XYCurve::getCurveYVector( QCPAbstractPlottable* plottable )
{
	QCPCurve *curve = qobject_cast<QCPCurve*>(plottable);
	QCPCurveDataMap *map =curve->data();
	QVector<double> yVect;
	for (QCPCurveDataMap::iterator it = map->begin();it != map->end(); it++)
		yVect.push_back(it->value);
	
	return yVect;
}