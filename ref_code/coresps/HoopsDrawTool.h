#pragma once
#include "coresps/drawtool.h"

class HoopsDrawTool :
	public DrawTool
{
public:
	HoopsDrawTool(void);
	virtual ~HoopsDrawTool(void);

	virtual void insertLine(value_type *pos1,value_type* pos2);
	virtual void insertLine(value_type x1,value_type y1,value_type z1,
		value_type x2,value_type y2,value_type z2);
	virtual void insertPoint(value_type* pos);
	virtual void insertPoint(value_type x,value_type y,value_type z);


	virtual void beginLineStrip();
	virtual void insertLinePoint(value_type x,value_type y,value_type z);
	virtual void insertLinePoint(value_type *xyz);
	virtual void endLineStrip();

	virtual void insertShell(int nodeCount,const float* nodeXYZ,int faceListCount,const int* faceList);

	virtual void myDebug();
};
