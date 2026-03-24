#include "shapeinputlib.h"
#include "HUtility.h"
#include <HUtilityGeometryCreation.h>
#include "ShapeManager.h"
#include "DrawTool.h"
#include <cmath>
#define PI 3.1415926535898

void createMarker()
{
	HC_Open_Segment("X");
	//HC_Set_Selectability("everything");
	HC_Set_Color("line=face=blue");
	//HC_Set_Color("line contrast = face contrast = green");
	HC_Set_Rendering_Options("attribute lock = color");
	HC_Insert_Line(0,0,0,1,0,0);
	HC_Close_Segment();

	HC_Open_Segment("Y");
	//HC_Set_Selectability("everything");
	HC_Set_Color("line=face=green");
	//HC_Set_Color("line contrast = face contrast = green");
	HC_Set_Rendering_Options("attribute lock = color");
	HC_Insert_Line(0,0,0,0,1,0);
	HC_Close_Segment();

	HC_Open_Segment("Z");
	//HC_Set_Selectability("everything");
	HC_Set_Color("line=face=red");
	HC_Set_Rendering_Options("attribute lock = color");
	HC_Insert_Line(0,0,0,0,0,1);
	HC_Close_Segment();
	//HC_Insert_Text(1.1,0,0,"X");
	//HC_Insert_Text(0,1.1,0,"Y");
	//HC_Insert_Text(0,0,1.1,"Z");

	HC_Set_Rendering_Options("display lists");
}

void createBox(const ShapePara* para,const ShapeInput* input)
{
	float x=input->_paras[0]/2;
	float y=input->_paras[1]/2;
	float z=input->_paras[2]/2;
	HPoint p1,p2;
	p1.Set(-x,-y,-z);
	p2.Set(x,y,z);
	HUtilityGeometryCreation::CreateCuboid(&p1,&p2);
	//HUtility::InsertBox(&p2,&p1);
}

void createSimpleLine(const ShapePara* para,const ShapeInput* input)
{
	const ShapeInput::DataVec &vec=input->_paras;
	HC_Set_Color("line=red");
	HC_Insert_Line(vec[0],vec[1],vec[2],vec[0]+vec[3]*vec[6],vec[1]+vec[4]*vec[6],vec[2]+vec[5]*vec[6]);
}


void createHArrow(const ShapePara* para,const ShapeInput* input)
{
	float stick_length=input->_paras[0];
	float tip_length=input->_paras[1];
	float stick_radius=input->_paras[2];
	float arrow_radius=input->_paras[3];
	
	HUtility::InsertArrow(stick_length,tip_length,stick_radius,arrow_radius,
		"","red","green",6,0);
}
//InsertArrow (float stick_length, float tip_length, 
//			 float stick_radius, float arrow_radius, const char *text,
//			 const char *stick_color, const char *tip_color, int num_sides=6, float tip_falloff=0.05, bool reverse=true)


//static HC_KEY 	CreateSphere (HPoint center, float radius, int numsides, HPoint axis, HPoint ref)
void createSphere(const ShapePara* para,const ShapeInput* input)
{
	float r=input->_paras[0];
	int d=(int)para->values[0];
	HUtilityGeometryCreation::CreateSphere(HPoint(0,0,0),r,d,HPoint(0,1,0),
		HPoint(0,0,1));
}

//static HC_KEY 	CreateCylinder (HPoint center, float radius, float height, int numsides, HPoint axis, HPoint ref)
void createCylinder(const ShapePara* para,const ShapeInput* input)
{
	float r=input->_paras[0];
	float h=input->_paras[1];
	int slice=(int)para->values[0];
	HUtilityGeometryCreation::CreateCylinder(HPoint(0,0,-h/2),r,h,slice,
		HPoint(0,1,0),HPoint(0,0,1));
}

//static HC_KEY 	CreateCone (HPoint center, float radius, float height, int numsides, HPoint axis, HPoint ref)
void createCone(const ShapePara* para,const ShapeInput* input)
{
	float r=input->_paras[0];
	float h=input->_paras[1];
	int slice=(int)para->values[0];
	HUtilityGeometryCreation::CreateCone(HPoint(0,0,0),r,h,
		slice,HPoint(0,1,0),HPoint(0,0,1));

}

static void shapePara_InsertItem(ShapePara& para,int index,const string& dis,float va)
{
	para.discription[index]=dis;
	para.values[index]=va;
}

void importHoopsShapesDef()
{
	ShapeManager* shapeManager=ShapeManager::instance();
	if(!shapeManager)
		return;

	shapeManager->insertShape("Marker",createMarker);
	shapeManager->insertShape("SimpleLine",NULL,createSimpleLine);
	shapeManager->insertShape("Box",NULL,createBox);
	shapeManager->insertShape("HArrow",NULL,createHArrow);

	int defaultSliceCount=100;
	ShapePara spherePara;
	shapePara_InsertItem(spherePara,0,"sphere slice count",defaultSliceCount);
	shapeManager->insertShape("Sphere",&spherePara,createSphere);

	ShapePara cylinderPara;
	shapePara_InsertItem(cylinderPara,0,"cylinder slice count",defaultSliceCount);
	shapeManager->insertShape("Cylinder",&cylinderPara,createCylinder);

	ShapePara conePara;
	shapePara_InsertItem(conePara,0,"cone slice count",defaultSliceCount);
	shapeManager->insertShape("Cone",&conePara,createCone);
}
