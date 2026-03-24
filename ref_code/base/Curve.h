#pragma once
#include "pre_compile.h"
#include "base/base_global.h"
using namespace std;

namespace Base
{

	/** 
	*@brief: this class used to store a curve's data.
	*@author: Jerry 
	*@date:	2011-1-4
	*/
	class BASE_EXPORT XYCurve
	{
	public:
		/**
		*Curve's type.
		*@li SCATTER: scatter curve.
		*@li X_LIST: curve has a list of x data.
		*@li Y_LIST: curve has a list of y data.
		*@li Y_LIST_TIME: do not have x datas, and will use time as x datas.
		*/
		enum Type{SCATTER=0,X_LIST,Y_LIST,Y_LIST_TIME};
	public:
		XYCurve(void);
		~XYCurve(void);

		void clear();
		bool isEmpty();
		bool isGood();

		void addPoint(double x,double y);
		void addX(double x);
		void addY(double y);

		const vector<double>* xList(){return &_xList;}
		const vector<double>* yList(){return &_yList;}

		void setType(Type type){_type=type;}
		/**
		*	The default Type is SCATTER.
		*/
		Type getType(){return _type;}

	protected:
		vector<double>	_xList;
		vector<double>	_yList;
		Type		_type;

	};

}//end namespace Base.