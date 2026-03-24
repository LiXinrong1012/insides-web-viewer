#ifndef XYCURVE_H
#define XYCURVE_H

#include "qcustomplot/qcustomplot.h"

/*!
	@brief  代表一根真实绘制的数据曲线。可以被代表各种外观属性。
	@date   2015.7.3
	@author Jerry
*/
class XYCurve : public QCPCurve
{
	Q_OBJECT

public:
	explicit XYCurve(QCPAxis *keyAxis, QCPAxis *valueAxis);
	~XYCurve();

	///获得曲线所有x值
	static QVector<double> getCurveXVector(QCPAbstractPlottable* plottable);

	///获得曲线所有y值
	static QVector<double> getCurveYVector(QCPAbstractPlottable* plottable);
	
};

#endif // XYCURVE_H
