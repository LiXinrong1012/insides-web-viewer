#include "shapeinputlib.h"
#include "ShapeManager.h"
#include "DrawTool.h"
#include <cmath>
#define PI 3.1415926535898



void createSForceTranslation()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,-1);
	drawTool->insertLinePoint(0,0.3,-0.8);
	drawTool->insertLinePoint(0,0.2,-0.8);
	drawTool->insertLinePoint(0,0.2,0.8);
	drawTool->insertLinePoint(0,0.3,0.8);
	drawTool->insertLinePoint(0,0,1);
	drawTool->endLineStrip();

}


void createCircle()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0,0},pos2[3]={0,0,0};
	const int count=40;
	double si;
	for(int i=0;i<=count;++i){
		si=PI*2*i/count;
		pos1[0]=cos(si);
		pos1[1]=sin(si);
		si=PI*2*(i+1)/count;
		pos2[0]=cos(si);
		pos2[1]=sin(si);
		drawTool->insertLine(pos1,pos2);
	}
}

void createSquare()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(1,1,0);
	drawTool->insertLinePoint(1,-1,0);
	drawTool->insertLinePoint(-1,-1,0);
	drawTool->insertLinePoint(-1,1,0);
	drawTool->insertLinePoint(1,1,0);
	drawTool->endLineStrip();
}



void createDebug()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->myDebug();
}

void createConForce()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.5,0,0);
	drawTool->insertLinePoint(0,0.5,0);
	drawTool->insertLinePoint(-0.5,0,0);
	drawTool->insertLinePoint(0,-0.5,0);
	drawTool->insertLinePoint(0.5,0,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0.05,1.0);
	drawTool->insertLinePoint(0,-0.05,1.0);
	drawTool->insertLinePoint(0,-0.05,0.1);
	drawTool->insertLinePoint(0,-0.1,0.1);
	drawTool->insertLinePoint(0,0,0);
	drawTool->insertLinePoint(0,0.1,0.1);
	drawTool->insertLinePoint(0,0.05,0.1);
	drawTool->insertLinePoint(0,0.05,1.0);
	drawTool->endLineStrip();
}



void createFixedJoint()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0.6,0},pos2[3]={0,0.6,0};
	const int count=40;
	double si;
	for(int i=0;i<=count;++i){
		si=PI*i/count;
		pos1[0]=0.3*cos(si);
		pos1[1]=0.3*sin(si)+0.6;
		si=PI*(i+1)/count;
		pos2[0]=0.3*cos(si);
		pos2[1]=0.3*sin(si)+0.6;
		drawTool->insertLine(pos1,pos2);
	}

	 
	double pos3[3]={0,0.6,0},pos4[3]={0,0.6,0};
	for(int j=0;j<=count;++j){
		si=PI*j/count;
		pos3[0]=0.4*cos(si);
		pos3[1]=0.4*sin(si)+0.6;
		si=PI*(j+1)/count;
		pos4[0]=0.4*cos(si);
		pos4[1]=0.4*sin(si)+0.6;
		drawTool->insertLine(pos3,pos4);
	}

	double pos5[3]={0,0,0},pos6[3]={0,0,0};
	for(int k=0;k<=count;++k){
		si=PI*2*k/count;
		pos5[0]=0.18*cos(si);
		pos5[1]=0.18*sin(si);
		si=PI*2*(k+1)/count;
		pos6[0]=0.18*cos(si);
		pos6[1]=0.18*sin(si);
		drawTool->insertLine(pos5,pos6);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,-0.18,0);
	drawTool->insertLinePoint(-0.06,-0.42,0);
	drawTool->insertLinePoint(0.06,-0.42,0);
	drawTool->insertLinePoint(0,-0.18,0);
	drawTool->endLineStrip();
	 
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.6,0.6,0);
	drawTool->insertLinePoint(0.6,-0.6,0);
	drawTool->insertLinePoint(-0.6,-0.6,0);
	drawTool->insertLinePoint(-0.6,0.6,0);
	drawTool->insertLinePoint(0.6,0.6,0);
	drawTool->endLineStrip();    
}
//glBegin(GL_LINE_LOOP);
//glVertex3d(1*_scale,0,0);
//glVertex3d(0,1*_scale,0);
//glVertex3d(-1*_scale,0,0);
//glVertex3d(0,-1*_scale,0);
//glEnd();

//glBegin(GL_LINE_LOOP);
//glVertex3d(0,0.05*_scale,1.0*_scale);
//glVertex3d(0,-0.05*_scale,1.0*_scale);
//glVertex3d(0,-0.05*_scale,0.1*_scale);
//glVertex3d(0,-0.1*_scale,0.1*_scale);
//glVertex3d(0,0,0);
//glVertex3d(0,-0.1*_scale,0.1*_scale);
//glVertex3d(0,0.05*_scale,0.1*_scale);
//
//glEnd();
void createSphericalJoint()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={-0.8,0,0},pos2[3]={-0.8,0,0};
	const int count=40;
	double si;
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos1[1]=0.3*cos(si);
		pos1[2]=0.3*sin(si);
		si=2*PI*(i+1)/count;
		pos2[1]=0.3*cos(si);
		pos2[2]=0.3*sin(si);
		drawTool->insertLine(pos1,pos2);
	}

	 
	double pos3[3]={-0.6,0,0},pos4[3]={-0.6,0,0};
	for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos3[1]=0.6*cos(si);
		pos3[2]=0.6*sin(si);
		si=2*PI*(j+1)/count;
		pos4[1]=0.6*cos(si);
		pos4[2]=0.6*sin(si);
		drawTool->insertLine(pos3,pos4);
	}

	double pos5[3]={-0.3,0,0},pos6[3]={-0.3,0,0};
	for(int k=0;k<=count;++k){
		si=2*PI*k/count;
		pos5[1]=0.8*cos(si);
		pos5[2]=0.8*sin(si);
		si=2*PI*(k+1)/count;
		pos6[1]=0.8*cos(si);
		pos6[2]=0.8*sin(si);
		drawTool->insertLine(pos5,pos6);
	}

	double pos7[3]={0,0,0},pos8[3]={0,0,0};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos7[1]=cos(si);
		pos7[2]=sin(si);
		si=2*PI*(i+1)/count;
		pos8[1]=cos(si);
		pos8[2]=sin(si);
		drawTool->insertLine(pos7,pos8);
	}

	double pos_1[3]={0.3,0,0},pos_2[3]={0.3,0,0};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos_1[1]=0.8*cos(si);
		pos_1[2]=0.8*sin(si);
		si=2*PI*(i+1)/count;
		pos_2[1]=0.8*cos(si);
		pos_2[2]=0.8*sin(si);
		drawTool->insertLine(pos_1,pos_2);
	}

	 
	double pos_3[3]={0.6,0,0},pos_4[3]={0.6,0,0};
	for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_3[1]=0.6*cos(si);
		pos_3[2]=0.6*sin(si);
		si=2*PI*(j+1)/count;
		pos_4[1]=0.6*cos(si);
		pos_4[2]=0.6*sin(si);
		drawTool->insertLine(pos_3,pos_4);
	}

	double pos_5[3]={0.8,0,0},pos_6[3]={0.8,0,0};
	for(int k=0;k<=count;++k){
		si=2*PI*2*k/count;
		pos_5[1]=0.3*cos(si);
		pos_5[2]=0.3*sin(si);
		si=2*PI*2*(k+1)/count;
		pos_6[1]=0.3*cos(si);
		pos_6[2]=0.3*sin(si);
		drawTool->insertLine(pos_5,pos_6);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-1,0,0);
	drawTool->insertLinePoint(1,0,0);
    drawTool->endLineStrip();
 
    
}

void createTranslationalsForce()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,1);
	drawTool->insertLinePoint(0,0.375,0.75);
	drawTool->insertLinePoint(0,0.25,0.75);
	drawTool->insertLinePoint(0,0.25,-0.75);
	drawTool->insertLinePoint(0,0.375,-0.75);
	drawTool->insertLinePoint(0,0,-1);
	drawTool->insertLinePoint(0,-0.375,-0.75);
	drawTool->insertLinePoint(0,-0.25,-0.75);
	drawTool->insertLinePoint(0,-0.25,0.75);
	drawTool->insertLinePoint(0,-0.375,0.75);
	drawTool->insertLinePoint(0,0,1);
	drawTool->endLineStrip();
}

void createRotationalsForce()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0,0},pos2[3]={0,0,0};
	const int count=40;
	double si;
	for(int i=0;i<=count;++i){
		si=PI*i/count;
		pos1[0]=0.25*cos(si);
		pos1[1]=0.25*sin(si);
		si=PI*(i+1)/count;
		pos2[0]=0.25*cos(si);
		pos2[1]=0.25*sin(si);
		drawTool->insertLine(pos1,pos2);
	}

	 
	double pos3[3]={0,0,0},pos4[3]={0,0,0};

	for(int j=0;j<=count;++j){
		si=PI*j/count;
		pos3[0]=0.75*cos(si);
		pos3[1]=0.75*sin(si);
		si=PI*(j+1)/count;
		pos4[0]=0.75*cos(si);
		pos4[1]=0.75*sin(si);
		drawTool->insertLine(pos3,pos4);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,0,0);
	drawTool->insertLinePoint(0.125,0,0);
	drawTool->insertLinePoint(0.5,-0.375,0);
	drawTool->insertLinePoint(0.875,0,0);
	drawTool->insertLinePoint(0.75,0,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.25,0,0);
	drawTool->insertLinePoint(-0.125,0,0);
	drawTool->insertLinePoint(-0.5,-0.375,0);
	drawTool->insertLinePoint(-0.875,0,0);
	drawTool->insertLinePoint(-0.75,0,0);
	drawTool->endLineStrip();
}
void createBeamForce()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.1,-0.7,0);
	drawTool->insertLinePoint(0.3,-0.7,0);
	drawTool->insertLinePoint(0.3,-1,0);
	drawTool->insertLinePoint(-0.3,-1,0);
	drawTool->insertLinePoint(-0.3,-0.7,0);
	drawTool->insertLinePoint(-0.1,-0.7,0);
	drawTool->insertLinePoint(-0.1,0.7,0);
	drawTool->insertLinePoint(-0.3,0.7,0);
	drawTool->insertLinePoint(-0.3,1,0);
	drawTool->insertLinePoint(0.3,1,0);
	drawTool->insertLinePoint(0.3,0.7,0);
	drawTool->insertLinePoint(0.1,0.7,0);
	drawTool->insertLinePoint(0.1,-0.7,0);
	drawTool->endLineStrip();
}

void createBushing()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
    double pos1[3]={0,0,1},pos2[3]={0,0,1};
	const int count=40;
	double si;
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos1[0]=0.8*cos(si);
		pos1[1]=0.6*sin(si);
		si=2*PI*(i+1)/count;
		pos2[0]=0.8*cos(si);
		pos2[1]=0.6*sin(si);
		drawTool->insertLine(pos1,pos2);
	}

    double pos3[3]={0,0,-1},pos4[3]={0,0,-1};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos3[0]=0.8*cos(si);
		pos3[1]=0.6*sin(si);
		si=2*PI*(i+1)/count;
		pos4[0]=0.8*cos(si);
		pos4[1]=0.6*sin(si);
		drawTool->insertLine(pos3,pos4);
	}
	
	double pos5[3]={0,0,-1},pos6[3]={0,0,1};
	for(int i=0;i<=15;++i){
		si=2*PI*i/10;
		pos5[0]=0.8*cos(si);
		pos5[1]=0.6*sin(si);
		pos6[0]=0.8*cos(si);
		pos6[1]=0.6*sin(si);
		drawTool->insertLine(pos5,pos6);
	}
}

void createCylindricalJoint()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
    double pos1[3]={0,0,1},pos2[3]={0,0,1};
	const int count=40;
	double si;
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos1[0]=0.3*cos(si);
		pos1[1]=0.3*sin(si);
		si=2*PI*(i+1)/count;
		pos2[0]=0.3*cos(si);
		pos2[1]=0.3*sin(si);
		drawTool->insertLine(pos1,pos2);
	}


    double pos3[3]={0,0,-1},pos4[3]={0,0,-1};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos3[0]=0.3*cos(si);
		pos3[1]=0.3*sin(si);
		si=2*PI*(i+1)/count;
		pos4[0]=0.3*cos(si);
		pos4[1]=0.3*sin(si);
		drawTool->insertLine(pos3,pos4);
	}

	double posa[3]={0,0,-0.3},posb[3]={0,0,-0.3};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		posa[0]=0.3*cos(si);
		posa[1]=0.3*sin(si);
		si=2*PI*(i+1)/count;
		posb[0]=0.3*cos(si);
		posb[1]=0.3*sin(si);
		drawTool->insertLine(posa,posb);
	}

	double posc[3]={0,0,0.3},posd[3]={0,0,0.3};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		posc[0]=0.3*cos(si);
		posc[1]=0.3*sin(si);
		si=2*PI*(i+1)/count;
		posd[0]=0.3*cos(si);
		posd[1]=0.3*sin(si);
		drawTool->insertLine(posc,posd);
	}
	
	double pos5[3]={0,0,-1},pos6[3]={0,0,1};
	for(int i=0;i<=15;++i){
		si=2*PI*i/10;
		pos5[0]=0.3*cos(si);
		pos5[1]=0.3*sin(si);
		pos6[0]=0.3*cos(si);
		pos6[1]=0.3*sin(si);
		drawTool->insertLine(pos5,pos6);
	}

	double pos_1[3]={0,0,0.3},pos_2[3]={0,0,0.3};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos_1[0]=0.6*cos(si);
		pos_1[1]=0.6*sin(si);
		si=2*PI*(i+1)/count;
		pos_2[0]=0.6*cos(si);
		pos_2[1]=0.6*sin(si);
		drawTool->insertLine(pos_1,pos_2);
	}

    double pos_3[3]={0,0,-0.3},pos_4[3]={0,0,-0.3};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos_3[0]=0.6*cos(si);
		pos_3[1]=0.6*sin(si);
		si=2*PI*(i+1)/count;
		pos_4[0]=0.6*cos(si);
		pos_4[1]=0.6*sin(si);
		drawTool->insertLine(pos_3,pos_4);
	}
	
	double pos_5[3]={0,0,-0.3},pos_6[3]={0,0,0.3};
	for(int i=0;i<=15;++i){
		si=2*PI*i/10;
		pos_5[0]=0.6*cos(si);
		pos_5[1]=0.6*sin(si);
		pos_6[0]=0.6*cos(si);
		pos_6[1]=0.6*sin(si);
		drawTool->insertLine(pos_5,pos_6);
	}
}



void createPlanarJoint()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.6,0.6,0.2);
	drawTool->insertLinePoint(0.6,-0.6,0.2);
	drawTool->insertLinePoint(-0.6,-0.6,0.2);
	drawTool->insertLinePoint(-0.6,0.6,0.2);
	drawTool->insertLinePoint(0.6,0.6,0.2);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.6,0.6,-0.2);
	drawTool->insertLinePoint(0.6,-0.6,-0.2);
	drawTool->insertLinePoint(-0.6,-0.6,-0.2);
	drawTool->insertLinePoint(-0.6,0.6,-0.2);
	drawTool->insertLinePoint(0.6,0.6,-0.2);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(1,0,0);
	drawTool->insertLinePoint(-1,0,0);
    drawTool->endLineStrip();
}

void createTranslationalJoint()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.5,0.5,0.5);
	drawTool->insertLinePoint(0.5,-0.5,0.5);
	drawTool->insertLinePoint(-0.5,-0.5,0.5);
	drawTool->insertLinePoint(-0.5,0.5,0.5);
	drawTool->insertLinePoint(0.5,0.5,0.5);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.5,0.5,-0.5);
	drawTool->insertLinePoint(0.5,-0.5,-0.5);
	drawTool->insertLinePoint(-0.5,-0.5,-0.5);
	drawTool->insertLinePoint(-0.5,0.5,-0.5);
	drawTool->insertLinePoint(0.5,0.5,-0.5);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.5,0.5,0.5);
	drawTool->insertLinePoint(0.5,0.5,-0.5);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.5,-0.5,0.5);
	drawTool->insertLinePoint(0.5,-0.5,-0.5);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.5,-0.5,0.5);
	drawTool->insertLinePoint(-0.5,-0.5,-0.5);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.5,0.5,0.5);
	drawTool->insertLinePoint(-0.5,0.5,-0.5);
	drawTool->endLineStrip();

	///小立方体
	drawTool->beginLineStrip();
    drawTool->insertLinePoint(0.25,0.25,1);
	drawTool->insertLinePoint(-0.25,0.25,1);
	drawTool->insertLinePoint(-0.25,-0.25,1);
	drawTool->insertLinePoint(0.25,-0.25,1);
	drawTool->insertLinePoint(0.25,0.25,1);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,0.25,-1);
	drawTool->insertLinePoint(-0.25,0.25,-1);
	drawTool->insertLinePoint(-0.25,-0.25,-1);
	drawTool->insertLinePoint(0.25,-0.25,-1);
	drawTool->insertLinePoint(0.25,0.25,-1);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,0.25,1);
	drawTool->insertLinePoint(0.25,0.25,-1);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.25,0.25,1);
	drawTool->insertLinePoint(-0.25,0.25,-1);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.25,-0.25,1);
	drawTool->insertLinePoint(-0.25,-0.25,-1);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,-0.25,1);
	drawTool->insertLinePoint(0.25,-0.25,-1);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,0.25,0.4);
	drawTool->insertLinePoint(-0.25,0.25,0.4);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.25,0.25,0.4);
	drawTool->insertLinePoint(-0.25,-0.25,0.4);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.25,-0.25,0.4);
	drawTool->insertLinePoint(0.25,-0.25,0.4);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,-0.25,0.4);
	drawTool->insertLinePoint(0.25,0.25,0.4);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,0.25,-0.4);
	drawTool->insertLinePoint(-0.25,0.25,-0.4);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.25,0.25,-0.4);
	drawTool->insertLinePoint(-0.25,-0.25,-0.4);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.25,-0.25,-0.4);
	drawTool->insertLinePoint(0.25,-0.25,-0.4);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.25,-0.25,-0.4);
	drawTool->insertLinePoint(0.25,0.25,-0.4);
	drawTool->endLineStrip();
}


void createEsxeRevolutJoint()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0,0},pos2[3]={0,0,0};
	const int count=40;
	double si;
	for(int i=0;i<=count;++i){
		si=PI*i/count;
		pos1[0]=0.6*cos(si);
		pos1[1]=0.6*sin(si);
		si=PI*(i+1)/count;
		pos2[0]=0.6*cos(si);
		pos2[1]=0.6*sin(si);
		drawTool->insertLine(pos1,pos2);
	}

	 
	double pos3[3]={0,0,0},pos4[3]={0,0,0};
    for(int j=0;j<=count;++j){
		si=PI*j/count;
		pos3[0]=0.3*cos(si);
		pos3[1]=0.3*sin(si);
		si=PI*(j+1)/count;
		pos4[0]=0.3*cos(si);
		pos4[1]=0.3*sin(si);
		drawTool->insertLine(pos3,pos4);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.6,0,0);
	drawTool->insertLinePoint(0.3,0,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.6,0,0);
	drawTool->insertLinePoint(-0.65,0,0);
	drawTool->insertLinePoint(-0.5,-0.4,0);
	drawTool->insertLinePoint(-0.25,0,0);
	drawTool->insertLinePoint(-0.3,0,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(1,0,1);
	drawTool->insertLinePoint(1,0,-1);
	drawTool->insertLinePoint(0.1,0,-1);
	drawTool->insertLinePoint(0.1,0,1);
	drawTool->insertLinePoint(1,0,1);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-1,0,1);
	drawTool->insertLinePoint(-1,0,-1);
	drawTool->insertLinePoint(-0.1,0,-1);
	drawTool->insertLinePoint(-0.1,0,1);
	drawTool->insertLinePoint(-1,0,1);
	drawTool->endLineStrip();

	double posa[3]={0,0,0},posb[3]={0,0,0};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		posa[0]=0.1*cos(si);
		posa[1]=0.1*sin(si);
		si=2*PI*(j+1)/count;
		posb[0]=0.1*cos(si);
		posb[1]=0.1*sin(si);
		drawTool->insertLine(posa,posb);
	}


	double posc[3]={0,0,0.5},posd[3]={0,0,0.5};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		posc[0]=0.1*cos(si);
		posc[1]=0.1*sin(si);
		si=2*PI*(j+1)/count;
		posd[0]=0.1*cos(si);
		posd[1]=0.1*sin(si);
		drawTool->insertLine(posc,posd);
	}

	double pose[3]={0,0,1},posf[3]={0,0,1};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pose[0]=0.1*cos(si);
		pose[1]=0.1*sin(si);
		si=2*PI*(j+1)/count;
		posf[0]=0.1*cos(si);
		posf[1]=0.1*sin(si);
		drawTool->insertLine(pose,posf);
	}

	double pos_c[3]={0,0,-1},pos_d[3]={0,0,-1};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_c[0]=0.1*cos(si);
		pos_c[1]=0.1*sin(si);
		si=2*PI*(j+1)/count;
		pos_d[0]=0.1*cos(si);
		pos_d[1]=0.1*sin(si);
		drawTool->insertLine(pos_c,pos_d);
	}

	double pos_e[3]={0,0,-0.5},pos_f[3]={0,0,-0.5};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_e[0]=0.1*cos(si);
		pos_e[1]=0.1*sin(si);
		si=2*PI*(j+1)/count;
		pos_f[0]=0.1*cos(si);
		pos_f[1]=0.1*sin(si);
		drawTool->insertLine(pos_e,pos_f);
	}

	double pos_11[3]={0.4,0,0.8},pos_12[3]={0.4,0,0.8};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_11[0]=0.1*cos(si)+0.4;
		pos_11[2]=0.1*sin(si)+0.8;
		si=2*PI*(j+1)/count;
		pos_12[0]=0.1*cos(si)+0.4;
		pos_12[2]=0.1*sin(si)+0.8;
		drawTool->insertLine(pos_11,pos_12);
	}

	double pos_13[3]={-0.4,0,0.8},pos_14[3]={-0.4,0,0.8};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_13[0]=0.1*cos(si)-0.4;
		pos_13[2]=0.1*sin(si)+0.8;
		si=2*PI*(j+1)/count;
		pos_14[0]=0.1*cos(si)-0.4;
		pos_14[2]=0.1*sin(si)+0.8;
		drawTool->insertLine(pos_13,pos_14);
	}

	double pos_15[3]={-0.4,0,-0.8},pos_16[3]={-0.4,0,-0.8};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_15[0]=0.1*cos(si)-0.4;
		pos_15[2]=0.1*sin(si)-0.8;
		si=2*PI*(j+1)/count;
		pos_16[0]=0.1*cos(si)-0.4;
		pos_16[2]=0.1*sin(si)-0.8;
		drawTool->insertLine(pos_15,pos_16);
	}

	double pos_17[3]={0.4,0,-0.8},pos_18[3]={0.4,0,-0.8};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_17[0]=0.1*cos(si)+0.4;
		pos_17[2]=0.1*sin(si)-0.8;
		si=2*PI*(j+1)/count;
		pos_18[0]=0.1*cos(si)+0.4;
		pos_18[2]=0.1*sin(si)-0.8;
		drawTool->insertLine(pos_17,pos_18);
	}

	double pos_1a[3]={0.8,0,0},pos_1b[3]={0.8,0,0};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_1a[0]=0.1*cos(si)+0.8;
		pos_1a[2]=0.1*sin(si);
		si=2*PI*(j+1)/count;
		pos_1b[0]=0.1*cos(si)+0.8;
		pos_1b[2]=0.1*sin(si);
		drawTool->insertLine(pos_1a,pos_1b);
	}

	double pos_1c[3]={-0.8,0,0},pos_1d[3]={-0.8,0,0};
    for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos_1c[0]=0.1*cos(si)-0.8;
		pos_1c[2]=0.1*sin(si);
		si=2*PI*(j+1)/count;
		pos_1d[0]=0.1*cos(si)-0.8;
		pos_1d[2]=0.1*sin(si);
		drawTool->insertLine(pos_1c,pos_1d);
	}
}

void createContactForce()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	DrawTool* drawTool=_shapeManager->getDrawTool();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.8,0,0);
	drawTool->insertLinePoint(0,0.8,0);
	drawTool->insertLinePoint(-0.8,0,0);
	drawTool->insertLinePoint(0,-0.8,0);
	drawTool->insertLinePoint(0.8,0,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0.9);
	drawTool->insertLinePoint(0.125,0.125,1);
	drawTool->insertLinePoint(0.125,0.125,0.125);
	drawTool->insertLinePoint(0.175,0.175,0.125);
	drawTool->insertLinePoint(0,0,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0.9);
	drawTool->insertLinePoint(0.125,-0.125,1);
	drawTool->insertLinePoint(0.125,-0.125,0.125);
	drawTool->insertLinePoint(0.175,-0.175,0.125);
	drawTool->insertLinePoint(0,0,0);

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0.9);
	drawTool->insertLinePoint(-0.125,-0.125,1);
	drawTool->insertLinePoint(-0.125,-0.125,0.125);
	drawTool->insertLinePoint(-0.175,-0.175,0.125);
	drawTool->insertLinePoint(0,0,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0.9);
	drawTool->insertLinePoint(-0.125,0.125,1);
	drawTool->insertLinePoint(-0.125,0.125,0.125);
	drawTool->insertLinePoint(-0.175,0.175,0.125);
	drawTool->insertLinePoint(0,0,0);
	drawTool->endLineStrip();
}


void importSimpleShapesDef()
{
	ShapeManager* _shapeManager=ShapeManager::instance();
	_shapeManager->insertShape("Circle",createCircle);
	_shapeManager->insertShape("Square",createSquare);
	//_shapeManager->insertShape("Marker",createMarker);
	_shapeManager->insertShape("Debug",createConForce);
	_shapeManager->insertShape("sForceTranslation",createSForceTranslation);

	_shapeManager->insertShape("Fixed Joint",createFixedJoint);
	_shapeManager->insertShape("Spherical Joint",createSphericalJoint);    
	_shapeManager->insertShape("Translational sForce",createTranslationalsForce);
	_shapeManager->insertShape("Rotational sForce",createRotationalsForce);
	_shapeManager->insertShape("Beam Force",createBeamForce);
	_shapeManager->insertShape("Bushing",createBushing);
	_shapeManager->insertShape("Planar Joint",createPlanarJoint);
	_shapeManager->insertShape("Cylindrical Joint",createCylindricalJoint);
	_shapeManager->insertShape("Translational Joint",createTranslationalJoint);
	_shapeManager->insertShape("Revolute Joint",createEsxeRevolutJoint);
	_shapeManager->insertShape("Contact Force",createContactForce);
	
//	_shapeManager->insertShape("Debug",createDebug);
}
