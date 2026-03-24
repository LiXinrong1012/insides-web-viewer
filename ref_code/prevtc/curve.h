#ifndef CURVE_H
#define CURVE_H

#include "qcustomplot/qcustomplot.h"

/*! 
	@brief   代表一根真实绘制的数据曲线,可以被代表各种外观属性。
	@date    2015.6.26
	@author  Jerry
*/
class Curve : public QCPCurve
{
	Q_OBJECT

public:
	explicit Curve(QCPAxis *keyAxis, QCPAxis *valueAxis);
	~Curve();

	///获得所有X点
	static QVector<double> getCurveXVector(QCPAbstractPlottable* plottable);

	///获得所有Y点
	static QVector<double> getCurveYVector(QCPAbstractPlottable* plottable);

private:
	
};

#endif // CURVE_H
