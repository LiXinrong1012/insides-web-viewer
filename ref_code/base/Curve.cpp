#include "Curve.h"
namespace Base
{

	XYCurve::XYCurve(void)
	{
		_type=XYCurve::SCATTER;
	}

	XYCurve::~XYCurve(void)
	{
	}

	void XYCurve::clear()
	{
		_xList.clear();
		_yList.clear();
	}

	bool XYCurve::isEmpty()
	{
		return _yList.size()==0;
	}

	bool XYCurve::isGood()
	{
		switch(_type)
		{
		case XYCurve::SCATTER:
			return _xList.size()==yList()->size();
		case XYCurve::Y_LIST:
		case XYCurve::Y_LIST_TIME:
		case XYCurve::X_LIST:
			return true;
		}
		return true;
	}

	void XYCurve::addPoint(double x,double y)
	{
		_xList.push_back(x);
		_yList.push_back(y);
	}
	void XYCurve::addX(double x)
	{
		_xList.push_back(x);
	}
	void XYCurve::addY(double y)
	{
		_yList.push_back(y);
	}




}//end namespace Base