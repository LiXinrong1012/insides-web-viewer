#include "HoopsDrawTool.h"

#include "coresps/coresps_global.h"

HoopsDrawTool::HoopsDrawTool(void)
{
}

HoopsDrawTool::~HoopsDrawTool(void)
{
}

void HoopsDrawTool::insertLine(value_type *pos1,value_type* pos2)
{
	HC_Insert_Line(pos1[0],pos1[1],pos1[2],
		pos2[0],pos2[1],pos2[2]);
}
void HoopsDrawTool::insertLine(value_type x1,value_type y1,value_type z1, value_type x2,value_type y2,value_type z2)
{
	HC_Insert_Line(x1,y1,z1,x2,y2,z2);
}
void HoopsDrawTool::insertPoint(value_type* pos)
{
	HC_Insert_Marker(pos[0],pos[1],pos[2]);
}
void HoopsDrawTool::insertPoint(value_type x,value_type y,value_type z)
{
	HC_Insert_Marker(x,y,z);
}


void HoopsDrawTool::beginLineStrip()
{
	HC_Restart_Ink();
}
void HoopsDrawTool::insertLinePoint(value_type x,value_type y,value_type z)
{
	HC_Insert_Ink(x,y,z);
}
void HoopsDrawTool::insertLinePoint(value_type *xyz)
{
	HC_Insert_Ink(xyz[0],xyz[1],xyz[2]);
}
void HoopsDrawTool::endLineStrip()
{
}

void HoopsDrawTool::insertShell(int nodeCount,const float* nodeXYZ,int faceListCount,const int* faceList)
{
	HC_Insert_Shell(nodeCount,(HPoint*)nodeXYZ,faceListCount,faceList);
}

void HoopsDrawTool::myDebug()
{
	HC_KEY key=HC_Insert_Line(2,0,0,2,1,0);
	HC_Open_Geometry(key);
	HC_Set_Color("red");
	HC_Close_Geometry();

	key=HC_Insert_Line(5,0,0,5,1,0);
	HC_Open_Geometry(key);
	HC_Set_Color("green");
	HC_Close_Geometry();
}