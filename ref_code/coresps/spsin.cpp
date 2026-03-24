#include "coresps/ShapeManager.h"
#include "coresps/DrawTool.h"
#include <cmath>

#ifndef PI
#define PI 3.1415926535898
#endif





void createQuad4(const ShapePara* para,const ShapeInput* input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	double x=input->_paras[0]/2;
	double y=input->_paras[1]/2;
	//double z=input->_paras[2]/2;

	//float points[4][3]={{-x,-y,0},{x,-y,0},{x,y,0},{-x,y}};
	float points[12]={-x,-y,0,x,-y,0,x,y,0,-x,y};
	int flist[]={4,0,1,2,3};

	drawTool->insertShell(4,(float*)points,5,flist);
}

void createTri3(const ShapePara* para, const ShapeInput * input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	float L1=input->_paras[0];
	float L2=input->_paras[1];

	float *vec=new float[9];
	vec[0]=-L1/2;
	vec[1]=vec[2]=0;
	vec[3]=L1/2;
	vec[4]=vec[5]=0;
	vec[6]=vec[8]=0;
	vec[7]=L2;

	int* faceList=new int[4];
	faceList[0]=3;
	faceList[1]=1;
	faceList[2]=2;
	faceList[3]=0;

	drawTool->insertShell(3,(float*)vec,4,faceList);

	delete []vec;
	delete []faceList;
}


void createCircleFace(const ShapePara* para, const ShapeInput * input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	float r=input->_paras[0];
	int slice=10;//(int)para->_d[0];

	int nodeCount=slice+1;
	float *nodeList=new float[nodeCount*3];

	float tmp=2*PI/slice;

	for(int i=0;i<slice;++i){
		nodeList[i*3]=cos(i*tmp)*r;
		nodeList[i*3+1]=sin(i*tmp)*r;
		nodeList[i*3+2]=0;
	}
	nodeList[slice*3]=nodeList[slice*3+1]=nodeList[slice*3+2]=0;

	int faceCount=slice;
	int* faceList=new int[faceCount*4];
	int curr=0;
	for(int i=1;i<faceCount;++i){
		faceList[curr++]=3;
		faceList[curr++]=i-1;
		faceList[curr++]=i;
		faceList[curr++]=nodeCount-1;
	}
	faceList[curr++]=3;
	faceList[curr++]=slice-1;
	faceList[curr++]=0;
	faceList[curr]=nodeCount-1;

	drawTool->insertShell(nodeCount,nodeList,faceCount*4,faceList);

	delete []nodeList;
	delete []faceList;
}

void createConvex(const ShapePara* para, const ShapeInput * input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	float top_r=input->_paras[0];
	float bottom_r=input->_paras[1];
	float height=input->_paras[2];
	int slice=(int)para->values[0];

	int nodeCount=slice*2;
	float *nodeList=new float[slice*6];

	float tmp=2*PI/slice;

	for(int i=0;i<slice;++i){
		nodeList[i*3]=cos(i*tmp)*top_r;
		nodeList[i*3+1]=sin(i*tmp)*top_r;
		nodeList[i*3+2]=height/2;

		nodeList[(i+slice)*3]=cos(i*tmp)*bottom_r;
		nodeList[(i+slice)*3+1]=sin(i*tmp)*bottom_r;
		nodeList[(i+slice)*3+2]=-height/2;
	}

	int faceListSize=(slice+1)*2+slice*5;
	int* faceList=new int[faceListSize];
	int curr=0;
	faceList[curr++]=slice;
	for(int i=0;i<slice;i++){
		faceList[curr++]=i;
	}

	faceList[curr++]=slice;
	for(int i=2*slice-1;i>=slice;i--){
		faceList[curr++]=i;
	}

	for(int i=1;i<slice;i++){
		faceList[curr++]=4;
		faceList[curr++]=i;
		faceList[curr++]=i-1;
		faceList[curr++]=i+slice-1;
		faceList[curr++]=i+slice;
	}

	faceList[curr++]=4;
	faceList[curr++]=0;
	faceList[curr++]=slice-1;
	faceList[curr++]=2*slice-1;
	faceList[curr++]=slice;

	drawTool->insertShell(nodeCount,nodeList,faceListSize,faceList);

	delete []nodeList;
	delete []faceList;
}

int _ij2index(int i,int j,int iMax,int jMax)
{
	return iMax*(j%jMax)+(i%iMax);
}
/*! Create a customized ring.
*	@para parameters of certain shape.
*	@input parameters of this type of shape.
*	@date 2013.1.16
*	@author Jerry He
*/
void createRing(const ShapePara* para, const ShapeInput * input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	float R=input->_paras[0];
	float r=input->_paras[1];
	int RSlice=(int)para->values[0];
	int rSlice=(int)para->values[1];

	int nodeCount=rSlice*RSlice;
	float *nodeList=new float[nodeCount*3];

	float deltaRRad=2*PI/RSlice;
	float deltarRad=2*PI/rSlice;
	float RRad,rRad,x,y,z,tmpY;
	int curr=0;
	int *pFaceCurr;
	int faceListSize=nodeCount*5;
	int* faceList=new int[faceListSize];

	for(int i=0;i<RSlice;++i){
		RRad=deltaRRad*i;

		for(int j=0;j<rSlice;++j)
		{
			rRad=deltarRad*j;
			z=r*sin(rRad);
			tmpY=R+r*cos(rRad);
			x=tmpY*cos(RRad);
			y=tmpY*sin(RRad);
			nodeList[curr*3]=x;
			nodeList[curr*3+1]=y;
			nodeList[curr*3+2]=z;

			pFaceCurr=&faceList[curr*5];
			pFaceCurr[0]=4;
			pFaceCurr[1]=_ij2index(j,i,rSlice,RSlice);
			pFaceCurr[2]=_ij2index(j+1,i,rSlice,RSlice);
			pFaceCurr[3]=_ij2index(j+1,i+1,rSlice,RSlice);
			pFaceCurr[4]=_ij2index(j,i+1,rSlice,RSlice);
			++curr;
		}
	}

	drawTool->insertShell(nodeCount,nodeList,faceListSize,faceList);

	delete []nodeList;
	delete []faceList;
}

void _insertHollowCylinderOneFace(int i,int j,int maxCount,int* currentFace)
{
	currentFace[0]=4;
	currentFace[1]=i;
	currentFace[2]=j;
	currentFace[3]=(j+4)%maxCount;
	currentFace[4]=(i+4)%maxCount;
}
void createHollowCylinder(const ShapePara* para, const ShapeInput* input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	float r1=input->_paras[0];
	float r2=input->_paras[1];
	float R1=input->_paras[2];
	float R2=input->_paras[3];
	float h=input->_paras[4];
	float halfH=h/2;
	int rSlice=(int)para->values[0];

	int nodeCount=rSlice*4;
	float *nodeList=new float[nodeCount*3];

	float vcos,vsin;

	float deltarRad=2*PI/rSlice;
	float rRad;
	int curr=0;
	float* currentNode;
	int everyFaceCount=5;
	int faceListSize=nodeCount*everyFaceCount;
	int* faceList=new int[faceListSize]; 

	for(int i=0;i<rSlice;++i){
		rRad=deltarRad*i;
		vcos=cos(rRad);
		vsin=sin(rRad);
		//insert all faces.
		_insertHollowCylinderOneFace(curr,curr+1,nodeCount,&faceList[curr*everyFaceCount]);
		_insertHollowCylinderOneFace(curr+1,curr+3,nodeCount,&faceList[(curr+1)*everyFaceCount]);
		_insertHollowCylinderOneFace(curr+3,curr+2,nodeCount,&faceList[(curr+2)*everyFaceCount]);
		_insertHollowCylinderOneFace(curr+2,curr,nodeCount,&faceList[(curr+3)*everyFaceCount]);

		currentNode=&(nodeList[curr*3]);
		currentNode[0]=R1*vcos;
		currentNode[1]=R1*vsin;
		currentNode[2]=-halfH;
		curr++;

		currentNode=&nodeList[curr*3];
		currentNode[0]=R2*vcos;
		currentNode[1]=R2*vsin;
		currentNode[2]=-halfH;
		curr++;

		currentNode=&nodeList[curr*3];
		currentNode[0]=r1*vcos;
		currentNode[1]=r1*vsin;
		currentNode[2]=halfH;
		curr++;

		currentNode=&nodeList[curr*3];
		currentNode[0]=r2*vcos;
		currentNode[1]=r2*vsin;
		currentNode[2]=halfH;
		curr++;
	}

	drawTool->insertShell(nodeCount,nodeList,faceListSize,faceList);

	delete []nodeList;
	delete []faceList;
}
void createSpring(const ShapePara* para, const ShapeInput * input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	float length=input->_paras[0];
	float radius=input->_paras[1];
	float pitch=input->_paras[2];
	int slice=(int)para->values[0];
	int num=length/pitch*slice;

	int nodeCount=slice*num;
	float tmp=2*PI/slice;
	DrawTool::value_type pos[3],halfLen=length/2,delta=pitch/slice;

	drawTool->beginLineStrip();

	for(int i=0;i<num;++i){
		pos[0]=cos(i*tmp)*radius;
		pos[1]=sin(i*tmp)*radius;
		pos[2]=delta*i-halfLen;

		drawTool->insertLinePoint(pos);
	}
	drawTool->endLineStrip();
}

void createArrowLine(const ShapePara* para, const ShapeInput * input)
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();

	float start_x=input->_paras[0];
	float start_y=input->_paras[1];
	float start_z=input->_paras[2];
	float vector_x=input->_paras[3];
	float vector_y=input->_paras[4];
	float vector_z=input->_paras[5];
	float linelength=input->_paras[6]*para->values[0];

	float length=(float)0.15*linelength;
	float r2l=(float)0.25;
	float radium=length*r2l;

	double line_start[3]={start_x,start_y,start_z};
	double line_end[3]={start_x+linelength*vector_x,start_y+linelength*vector_y,start_z+linelength*vector_z}; 
	drawTool->insertLine(line_start,line_end);

	if(length>linelength)
		length=linelength;

	const int slice =10;
	float tmp=(float)(2*PI/slice);
	float nodeCount=slice+1;

	float nodes[(slice+1)*3];
	float center_x=start_x+linelength*vector_x-length*vector_x;
	float center_y=start_y+linelength*vector_y-length*vector_y;
	float center_z=start_z+linelength*vector_z-length*vector_z;

	float vector1_x=(vector_y+vector_z)/(sqrt(2*vector_x*vector_x+(vector_y+vector_z)*(vector_y+vector_z)));
	float vector1_y=-vector_x/(sqrt(2*vector_x*vector_x+(vector_y+vector_z)*(vector_y+vector_z)));
	float vector1_z=-vector_x/(sqrt(2*vector_x*vector_x+(vector_y+vector_z)*(vector_y+vector_z)));

	float vector2_x=(vector_x*vector_z-vector_x*vector_y)/(sqrt((vector_x*vector_z-vector_x*vector_y)*(vector_x*vector_z-vector_x*vector_y)+(vector_z*(vector_z+vector_y)+vector_x*vector_x)*(vector_z*(vector_z+vector_y)+vector_x*vector_x)+(vector_y*(vector_y+vector_z)+vector_x*vector_x)*(vector_y*(vector_y+vector_z)+vector_x*vector_x)));
	float vector2_y=(vector_z*(vector_z+vector_y)+vector_x*vector_x)/(sqrt((vector_x*vector_z-vector_x*vector_y)*(vector_x*vector_z-vector_x*vector_y)+(vector_z*(vector_z+vector_y)+vector_x*vector_x)*(vector_z*(vector_z+vector_y)+vector_x*vector_x)+(vector_y*(vector_y+vector_z)+vector_x*vector_x)*(vector_y*(vector_y+vector_z)+vector_x*vector_x)));
	float vector2_z=-(vector_y*(vector_y+vector_z)+vector_x*vector_x)/(sqrt((vector_x*vector_z-vector_x*vector_y)*(vector_x*vector_z-vector_x*vector_y)+(vector_z*(vector_z+vector_y)+vector_x*vector_x)*(vector_z*(vector_z+vector_y)+vector_x*vector_x)+(vector_y*(vector_y+vector_z)+vector_x*vector_x)*(vector_y*(vector_y+vector_z)+vector_x*vector_x)));


	for(int i=0;i<slice;i++){
		nodes[i*3]=center_x+radium*(vector1_x*cos(tmp*i)+vector2_x*sin(tmp*i));
		nodes[i*3+1]=center_y+radium*(vector1_y*cos(tmp*i)+vector2_y*sin(tmp*i));
		nodes[i*3+2]=center_z+radium*(vector1_z*cos(tmp*i)+vector2_z*sin(tmp*i));
	}
	nodes[30]=start_x+linelength*vector_x;
	nodes[31]=start_y+linelength*vector_y;
	nodes[32]=start_z+linelength*vector_z;

	int faceCount=slice*4+11;
	int* faceList=new int[faceCount];
	int curr=0;
	faceList[curr++]=slice;
	for(int i=slice-1;i>=0;i--){
		faceList[curr++]=i;
	}

	for(int i=0;i<slice;i++){
		faceList[curr++]=3;
		faceList[curr++]=i;
		faceList[curr++]=(i+1)%slice; 
		faceList[curr++]=10;

	}

	drawTool->insertShell(nodeCount,nodes,slice*4+11,faceList);

	delete []faceList;
}

static void shapePara_InsertItem(ShapePara& para,int index,const string& dis,float va)
{
	para.discription[index]=dis;
	para.values[index]=va;
}

void importShapesCollection()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	//_shapeManager->insertShape("QUAD4",NULL,createQuad4);
	//_shapeManager->insertShape("TRI3",NULL,createTri3	);
	//_shapeManager->insertShape("CircleFace",&circleFacePara,createCircleFace);

	// For frustum.
	ShapePara createConvexPara;
	shapePara_InsertItem(createConvexPara,0,"frustum slice count",20);
	_shapeManager->insertShape("Frustum",&createConvexPara,createConvex);

	// For Spring.
	ShapePara createSpringPara;
	shapePara_InsertItem(createSpringPara,0,"spring slice count",20);
	_shapeManager->insertShape("Spring",&createSpringPara,createSpring);

	ShapePara createArrowXPara;
	shapePara_InsertItem(createArrowXPara,0,"Arrow line scale",1);
	shapePara_InsertItem(createArrowXPara,1,"Arrow para 2",10);
	shapePara_InsertItem(createArrowXPara,2,"Arrow para 3",20);
	_shapeManager->insertShape("ArrowLine",&createArrowXPara,createArrowLine); 	ShapePara createRingPara;	shapePara_InsertItem(createRingPara,0,"slice of ring radius",20);	shapePara_InsertItem(createRingPara,1,"slice of circle radius",15);	_shapeManager->insertShape("Ring",&createRingPara,createRing);	ShapePara createHollowCylinderPara;	shapePara_InsertItem(createHollowCylinderPara,0,"slice",200);	_shapeManager->insertShape("HollowCylinder",&createHollowCylinderPara,createHollowCylinder);}
