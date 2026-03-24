#ifndef PP_SPS_DRAW_TOOL_H_
#define PP_SPS_DRAW_TOOL_H_

#include "coresps/coresps_global2.h"


class CORESPS_EXPORT DrawTool
{
public:
	virtual ~DrawTool(){}
	typedef double value_type;
	virtual void insertLine(value_type *pos1,value_type* pos2)=0;
	virtual void insertLine(value_type x1,value_type y1,value_type z1,
		value_type x2,value_type y2,value_type z2)=0;
	virtual void insertPoint(value_type* pos)=0;
	virtual void insertPoint(value_type x,value_type y,value_type z)=0;

	virtual void beginLineStrip()=0;
	virtual void insertLinePoint(value_type x,value_type y,value_type z)=0;
	virtual void insertLinePoint(value_type *xyz)=0;
	virtual void endLineStrip()=0;

	virtual void insertShell(int nodeCount,const float* nodeXYZ,int faceListCount,const int* faceList)=0;

	virtual void myDebug()=0;



};



#endif