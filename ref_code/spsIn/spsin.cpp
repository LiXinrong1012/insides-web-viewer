
#define  HC_KEY long

#include "coresps/ShapeManager.h"
#include "coresps/DrawTool.h"
#include <cmath>

#ifndef PI
#define PI 3.1415926535898
#endif

ShapeManager* _shapeManager;



void setShapeManager(ShapeManager* shapeManager)
{
	_shapeManager=shapeManager;
}

//矩阵和向量相乘
void transform(double mat[16], double* pt)
{
	double x = mat[0]*pt[0]+mat[1]*pt[1]+mat[2]*pt[2]+mat[3];
	double y = mat[4]*pt[0]+mat[5]*pt[1]+mat[6]*pt[2]+mat[7];
	double z = mat[8]*pt[0]+mat[9]*pt[1]+mat[10]*pt[2]+mat[11];
	//只做旋转和平移变换，不需要w
	//double w = mat[12]*pt[0]+mat[13]*pt[1]+mat[14]*pt[2]+mat[15];
	if(fabs(pt[0]) > 1 ||fabs(pt[1]) > 1||fabs(pt[2]) > 1
		||fabs(x) > 1||fabs(y) > 1||fabs(z) > 1)
	{
		int iStop = 1;
	}
	pt[0] = x;pt[1] = y;pt[2] = z;
}
void multimatrix(double matL[16], double matR[16], double* matOut)
{
	double out[16];
	out[0] = matL[0]*matR[0]+matL[1]*matR[4]+matL[2]*matR[8]+matL[3]*matR[12];
	out[1] = matL[0]*matR[1]+matL[1]*matR[5]+matL[2]*matR[9]+matL[3]*matR[13];
	out[2] = matL[0]*matR[2]+matL[1]*matR[6]+matL[2]*matR[10]+matL[3]*matR[14];
	out[3] = matL[0]*matR[3]+matL[1]*matR[7]+matL[2]*matR[11]+matL[3]*matR[15];

	out[4] = matL[4]*matR[0]+matL[5]*matR[4]+matL[6]*matR[8]+matL[7]*matR[12];
	out[5] = matL[4]*matR[1]+matL[5]*matR[5]+matL[6]*matR[9]+matL[7]*matR[13];
	out[6] = matL[4]*matR[2]+matL[5]*matR[6]+matL[6]*matR[10]+matL[7]*matR[14];
	out[7] = matL[4]*matR[3]+matL[5]*matR[7]+matL[6]*matR[11]+matL[7]*matR[15];

	out[8] = matL[8]*matR[0]+matL[9]*matR[4]+matL[10]*matR[8]+matL[11]*matR[12];
	out[9] = matL[8]*matR[1]+matL[9]*matR[5]+matL[10]*matR[9]+matL[11]*matR[13];
	out[10] = matL[8]*matR[2]+matL[9]*matR[6]+matL[10]*matR[10]+matL[11]*matR[14];
	out[11] = matL[8]*matR[3]+matL[9]*matR[7]+matL[10]*matR[11]+matL[11]*matR[15];

	out[12] = matL[12]*matR[0]+matL[13]*matR[4]+matL[14]*matR[8]+matL[15]*matR[12];
	out[13] = matL[12]*matR[1]+matL[13]*matR[5]+matL[14]*matR[9]+matL[15]*matR[13];
	out[14] = matL[12]*matR[2]+matL[13]*matR[6]+matL[14]*matR[10]+matL[15]*matR[14];
	out[15] = matL[12]*matR[3]+matL[13]*matR[7]+matL[14]*matR[11]+matL[15]*matR[15];

	for(int i = 0; i < 16; i++) matOut[i] =out[i];
}

void createFixedJointI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0.6,0},pos2[3]={0,0.6,0};
	const int count=20;
	double si;
	for(int i=0;i<count;++i){
		si=PI/2*i/count;
		pos1[0]=0.3*cos(si);
		pos1[1]=0.3*sin(si)+0.6;
		si=PI/2*(i+1)/count;
		pos2[0]=0.3*cos(si);
		pos2[1]=0.3*sin(si)+0.6;
		drawTool->insertLine(pos1,pos2);
	}


	double pos3[3]={0,0.6,0},pos4[3]={0,0.6,0};
	for(int j=0;j<count;++j){
		si=PI/2*j/count;
		pos3[0]=0.4*cos(si);
		pos3[1]=0.4*sin(si)+0.6;
		si=PI/2*(j+1)/count;
		pos4[0]=0.4*cos(si);
		pos4[1]=0.4*sin(si)+0.6;
		drawTool->insertLine(pos3,pos4);
	}

	double pos5[3]={0,0,0},pos6[3]={0,0,0};
	for(int k=0;k<count;++k){
		si=PI*k/count-PI/2;
		pos5[0]=0.18*cos(si);
		pos5[1]=0.18*sin(si);
		si=PI*(k+1)/count-PI/2;
		pos6[0]=0.18*cos(si);
		pos6[1]=0.18*sin(si);
		drawTool->insertLine(pos5,pos6);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,-0.18,0);
	drawTool->insertLinePoint(0.06,-0.42,0);
	drawTool->insertLinePoint(0,-0.42,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0.6,0);
	drawTool->insertLinePoint(0.6,0.6,0);
	drawTool->insertLinePoint(0.6,-0.6,0);
	drawTool->insertLinePoint(0,-0.6,0);
	drawTool->endLineStrip();    
}

void createFixedJointJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0.6,0},pos2[3]={0,0.6,0};
	const int count=20;
	double si;
	for(int i=0;i<count;++i){
		si=PI/2*i/count+PI/2;
		pos1[0]=0.3*cos(si);
		pos1[1]=0.3*sin(si)+0.6;
		si=PI/2*(i+1)/count+PI/2;
		pos2[0]=0.3*cos(si);
		pos2[1]=0.3*sin(si)+0.6;
		drawTool->insertLine(pos1,pos2);
	}


	double pos3[3]={0,0.6,0},pos4[3]={0,0.6,0};
	for(int j=0;j<count;++j){
		si=PI/2*j/count+PI/2;
		pos3[0]=0.4*cos(si);
		pos3[1]=0.4*sin(si)+0.6;
		si=PI/2*(j+1)/count+PI/2;
		pos4[0]=0.4*cos(si);
		pos4[1]=0.4*sin(si)+0.6;
		drawTool->insertLine(pos3,pos4);
	}

	double pos5[3]={0,0,0},pos6[3]={0,0,0};
	for(int k=0;k<count;++k){
		si=PI*k/count+PI/2;
		pos5[0]=0.18*cos(si);
		pos5[1]=0.18*sin(si);
		si=PI*(k+1)/count+PI/2;
		pos6[0]=0.18*cos(si);
		pos6[1]=0.18*sin(si);
		drawTool->insertLine(pos5,pos6);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,-0.18,0);
	drawTool->insertLinePoint(-0.06,-0.42,0);
	drawTool->insertLinePoint(0,-0.42,0);
	drawTool->endLineStrip();

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0.6,0);
	drawTool->insertLinePoint(-0.6,0.6,0);
	drawTool->insertLinePoint(-0.6,-0.6,0);
	drawTool->insertLinePoint(0,-0.6,0);
	drawTool->endLineStrip();   
}

void create_myXXXI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double po1[3]={1,0,0};
	double po2[3]={0,1,0};
	double po3[3]={-1,0,0};
	drawTool->insertLine(po1,po2);
	drawTool->insertLine(po2,po3);
	drawTool->insertLine(po3,po1);

}
void create_myXXXJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double po1[3]={1,0,0};
	double po2[3]={0,-1,0};
	double po3[3]={-1,0,0};
	drawTool->insertLine(po1,po2);
	drawTool->insertLine(po2,po3);
	drawTool->insertLine(po3,po1);

}/*


void create_myBeamForceI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double po1[3]={0,1,0};
	double po2[3]={0.35,1,0};
	double po3[3]={0.35,0.7,0};
	double po4[3]={0.1,0.7,0};
	double po5[3]={0.1,-0.7,0};
	double po6[3]={0.35,-0.7,0};
	double po7[3]={0.35,-1,0};
	double po8[3]={0,-1,0};

	drawTool->insertLine(po1,po2);
	drawTool->insertLine(po2,po3);
	drawTool->insertLine(po3,po1);

}
void create_myBeamForceJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double po1[3]={0,1,0};
	double po2[3]={-0.35,1,0};
	double po3[3]={-0.35,0.7,0};
	double po4[3]={-0.1,0.7,0};
	double po5[3]={-0.1,-0.7,0};
	double po6[3]={-0.35,-0.7,0};
	double po7[3]={-0.35,-1,0};
	double po8[3]={0,-1,0};

	drawTool->insertLine(po1,po2);
	drawTool->insertLine(po2,po3);
	drawTool->insertLine(po3,po1);

}*/
 void create_hookeI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();

	//圆柱_2个圆端面_上
	double pos_1[3]={0,0,0},pos_2[3]={0,0,0};
	double r= 0.2;
	int count = 40;
	double angle = 0;

	pos_1[0] = 0.2;pos_1[1] = 0.02; pos_1[2] = 0;
	pos_2[0] = r*cos(angle);		
	pos_2[1] = 0.02;
	pos_2[2] = r*sin(angle)+0.15;
	drawTool->insertLine(pos_1,pos_2);
	for(int i = 0; i < count; i++)
	{
		angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = 0.02;
		pos_1[2] = r*sin(angle)+0.15;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = 0.02;
		pos_2[2] = r*sin(angle)+0.15;

		drawTool->insertLine(pos_1,pos_2);
	}
	angle = PI;
	pos_1[0] = r*cos(angle);		
	pos_1[1] = 0.02;
	pos_1[2] = r*sin(angle)+0.15;
	pos_2[0] = -0.2;pos_2[1] = 0.02; pos_2[2] = 0;
	drawTool->insertLine(pos_1,pos_2);

	//圆柱_2个圆端面_下
	angle = 0;
	pos_1[0] = 0.2;pos_1[1] = -0.02; pos_1[2] = 0;
	pos_2[0] = r*cos(angle);		
	pos_2[1] = -0.02;
	pos_2[2] = r*sin(angle)+0.15;
	drawTool->insertLine(pos_1,pos_2);
	for(int i = 0; i < count; i++)
	{
		angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = -0.02;
		pos_1[2] = r*sin(angle)+0.15;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = -0.02;
		pos_2[2] = r*sin(angle)+0.15;

		drawTool->insertLine(pos_1,pos_2);
	}
	angle = PI;
	pos_1[0] = r*cos(angle);		
	pos_1[1] = -0.02;
	pos_1[2] = r*sin(angle)+0.15;
	pos_2[0] = -0.2;pos_2[1] = -0.02; pos_2[2] = 0;
	drawTool->insertLine(pos_1,pos_2);
	//圆柱_2个圆端面_端线
	pos_1[0] = -0.2;pos_1[1] = 0.02; pos_1[2] = 0;
	pos_2[0] = -0.2;pos_2[1] = -0.02; pos_2[2] = 0;
	drawTool->insertLine(pos_1,pos_2);
	pos_1[0] = 0.2;pos_1[1] = 0.02; pos_1[2] = 0;
	pos_2[0] = 0.2;pos_2[1] = -0.02; pos_2[2] = 0;
	drawTool->insertLine(pos_1,pos_2);
	//把手
	drawTool->beginLineStrip();
	pos_1[0] = 0; pos_1[1] = 0.02; pos_1[2] = 0.35;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = 0; pos_1[1] = 0.02; pos_1[2] = 0.65;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = 0; pos_1[1] = -0.02; pos_1[2] = 0.65;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = 0; pos_1[1] = -0.02; pos_1[2] = 0.35;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	drawTool->endLineStrip();
}
void create_hookeJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double angle = PI/2;//绕z转90度
	double mat1[16]={cos(angle),-sin(angle),0,0, sin(angle),cos(angle),0,0, 0,0,1,0, 0,0,0,1 };
	angle = -3*PI/4;//绕y转-135度
	double mat2[16]={cos(angle),0,sin(angle),0, 0,1,0,0, -sin(angle),0,cos(angle),0, 0,0,0,1 };
	double mat[16];
	multimatrix(mat2,mat1,mat);

	//圆柱_2个圆端面_上
	double pos_1[3]={0,0,0},pos_2[3]={0,0,0};
	double r= 0.2;
	int count = 40;
	angle = 0;

	pos_1[0] = 0.2;pos_1[1] = 0.02; pos_1[2] = 0;
	pos_2[0] = r*cos(angle);		
	pos_2[1] = 0.02;
	pos_2[2] = r*sin(angle)+0.15;
	transform(mat, pos_1);
	transform(mat, pos_2);
	drawTool->insertLine(pos_1,pos_2);
	for(int i = 0; i < count; i++)
	{
		angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = 0.02;
		pos_1[2] = r*sin(angle)+0.15;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = 0.02;
		pos_2[2] = r*sin(angle)+0.15;

		transform(mat, pos_1);
		transform(mat, pos_2);
		drawTool->insertLine(pos_1,pos_2);
	}
	angle = PI;
	pos_1[0] = r*cos(angle);		
	pos_1[1] = 0.02;
	pos_1[2] = r*sin(angle)+0.15;
	pos_2[0] = -0.2;pos_2[1] = 0.02; pos_2[2] = 0;

	transform(mat, pos_1);
	transform(mat, pos_2);
	drawTool->insertLine(pos_1,pos_2);

	//圆柱_2个圆端面_下
	angle = 0;
	pos_1[0] = 0.2;pos_1[1] = -0.02; pos_1[2] = 0;
	pos_2[0] = r*cos(angle);		
	pos_2[1] = -0.02;
	pos_2[2] = r*sin(angle)+0.15;

	transform(mat, pos_1);
	transform(mat, pos_2);
	drawTool->insertLine(pos_1,pos_2);
	for(int i = 0; i < count; i++)
	{
		angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = -0.02;
		pos_1[2] = r*sin(angle)+0.15;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = -0.02;
		pos_2[2] = r*sin(angle)+0.15;

		transform(mat, pos_1);
		transform(mat, pos_2);
		drawTool->insertLine(pos_1,pos_2);
	}
	angle = PI;
	pos_1[0] = r*cos(angle);		
	pos_1[1] = -0.02;
	pos_1[2] = r*sin(angle)+0.15;
	pos_2[0] = -0.2;pos_2[1] = -0.02; pos_2[2] = 0;

	transform(mat, pos_1);
	transform(mat, pos_2);
	drawTool->insertLine(pos_1,pos_2);
	//圆柱_2个圆端面_端线
	pos_1[0] = -0.2;pos_1[1] = 0.02; pos_1[2] = 0;
	pos_2[0] = -0.2;pos_2[1] = -0.02; pos_2[2] = 0;
	transform(mat, pos_1);
	transform(mat, pos_2);
	drawTool->insertLine(pos_1,pos_2);
	pos_1[0] = 0.2;pos_1[1] = 0.02; pos_1[2] = 0;
	pos_2[0] = 0.2;pos_2[1] = -0.02; pos_2[2] = 0;
	transform(mat, pos_1);
	transform(mat, pos_2);
	drawTool->insertLine(pos_1,pos_2);
	//把手
	drawTool->beginLineStrip();
	pos_1[0] = 0; pos_1[1] = 0.02; pos_1[2] = 0.35;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = 0; pos_1[1] = 0.02; pos_1[2] = 0.65;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = 0; pos_1[1] = -0.02; pos_1[2] = 0.65;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = 0; pos_1[1] = -0.02; pos_1[2] = 0.35;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	drawTool->endLineStrip();	
}
void create_planarI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double po1[3]={0.7,0.7,0.2};
	double po2[3]={-0.7,0.7,0.2};
	double po3[3]={-0.7,-0.7,0.2};
	double po4[3]={0.7,-0.7,0.2};

	drawTool->insertLine(po1,po2);
	drawTool->insertLine(po2,po3);
	drawTool->insertLine(po3,po4);
	drawTool->insertLine(po4,po1);

	double po5[3]={1,0,0};
	double po6[3]={-1,0,0};
	drawTool->insertLine(po5,po6);

}
void create_planarJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double po1[3]={0.7,0.7,-0.2};
	double po2[3]={-0.7,0.7,-0.2};
	double po3[3]={-0.7,-0.7,-0.2};
	double po4[3]={0.7,-0.7,-0.2};

	drawTool->insertLine(po1,po2);
	drawTool->insertLine(po2,po3);
	drawTool->insertLine(po3,po4);
	drawTool->insertLine(po4,po1);

	double po5[3]={1,0,0};
	double po6[3]={-1,0,0};
	drawTool->insertLine(po5,po6);
}

void create_cylindricalI()
{
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
}
void create_cylindricalJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	const int count=40;
	double si;
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

void create_revoluteI()
{
	//销的一半
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos_1[3]={0,0,0},pos_2[3]={0,0,0};
	//销的一半_５个圆
	int count = 20;
	double r= 0.1;
	for(int i = 0; i < 5; i++)
	{
		pos_1[2] = -1.0+(double)i/2.0;
		pos_2[2] = -1.0+(double)i/2.0;
		for(int j = 0; j < count; j++)
		{
			double angle = 2*PI/count*j;
			pos_1[0] = r*cos(angle);
			pos_1[1] = r*sin(angle);
			angle = 2*PI/count*(j+1);
			pos_2[0] = r*cos(angle);
			pos_2[1] = r*sin(angle);
			drawTool->insertLine(pos_1,pos_2);
		}
	}
	//销的一半_外框
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(1,0,-1);
	drawTool->insertLinePoint(0.1,0,-1);
	drawTool->insertLinePoint(0.1,0,1);
	drawTool->insertLinePoint(1,0,1);
	drawTool->insertLinePoint(1,0,-1);
	drawTool->endLineStrip();
	//销的一半_３个圆
	double pos[3]={0,0,0};	
	r= 0.1;
	count = 40;
	pos[0]=0.4; pos[1] = 0; pos[2]=-0.8;
	for(int i = 0; i < 40; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];
		pos_1[1] = pos[1];
		pos_1[2] = r*sin(angle)+pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = pos[1];
		pos_2[2] = r*sin(angle)+pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
	pos[0]=0.4; pos[1] = 0; pos[2]=0.8;
	for(int i = 0; i < 40; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];
		pos_1[1] = pos[1];
		pos_1[2] = r*sin(angle)+pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = pos[1];
		pos_2[2] = r*sin(angle)+pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
	pos[0]=0.8; pos[1] = 0; pos[2]=0;
	for(int i = 0; i < 40; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];
		pos_1[1] = pos[1];
		pos_1[2] = r*sin(angle)+pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = pos[1];
		pos_2[2] = r*sin(angle)+pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
}
void create_revoluteJ()
{
	create_revoluteI();

	//销的一半
	DrawTool* drawTool=_shapeManager->getDrawTool();
	
	double pos_1[3]={0,0,0},pos_2[3]={0,0,0};
	//销的一半_５个圆
	int count = 20;
	double r = 0.1;/*
	for(int i = 0; i < 5; i++)
	{
		pos_1[2] = -1.0+(double)i/2.0;
		pos_2[2] = -1.0+(double)i/2.0;
		for(int j = 0; j < count; j++)
		{
			double angle = 2*PI/count*j;
			pos_1[0] = r*cos(angle);
			pos_1[1] = r*sin(angle);
			angle = 2*PI/count*(j+1);
			pos_2[0] = r*cos(angle);
			pos_2[1] = r*sin(angle);
			drawTool->insertLine(pos_1,pos_2);
		}
	}
	//销的一半_外框
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-1,0,-1);
	drawTool->insertLinePoint(-0.1,0,-1);
	drawTool->insertLinePoint(-0.1,0,1);
	drawTool->insertLinePoint(-1,0,1);
	drawTool->insertLinePoint(-1,0,-1);
	drawTool->endLineStrip();
	//销的一半_３个圆
	double pos[3]={0,0,0};	
	r= 0.1;
	count = 40;
	pos[0]=-0.4; pos[1] = 0; pos[2]=-0.8;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];
		pos_1[1] = pos[1];
		pos_1[2] = r*sin(angle)+pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = pos[1];
		pos_2[2] = r*sin(angle)+pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
	pos[0]=-0.4; pos[1] = 0; pos[2]=0.8;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];
		pos_1[1] = pos[1];
		pos_1[2] = r*sin(angle)+pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = pos[1];
		pos_2[2] = r*sin(angle)+pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
	pos[0]=-0.8; pos[1] = 0; pos[2]=0;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];
		pos_1[1] = pos[1];
		pos_1[2] = r*sin(angle)+pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = pos[1];
		pos_2[2] = r*sin(angle)+pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
	*/
	//箭头_两个半圆
	count = 20;
	r = 0.4;
	for(int i = 0; i < count; i++)
	{
		double angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle);
		pos_1[2] = 0;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle);
		pos_2[2] = 0;
		drawTool->insertLine(pos_1,pos_2);
	}
	r = 0.6;
	for(int i = 0; i < count; i++)
	{
		double angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle);
		pos_1[2] = 0;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle);
		pos_2[2] = 0;
		drawTool->insertLine(pos_1,pos_2);
	}
	//箭头_起点线
	pos_1[0] = 0.4;
	pos_1[1] = 0;
	pos_1[2] = 0;
	pos_2[0] = 0.6;		//0.4
	pos_2[1] = 0;
	pos_2[2] = 0;	
	drawTool->insertLine(pos_1,pos_2);
	//箭头_箭头
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-0.6,0,0);
	drawTool->insertLinePoint(-0.65,0,0);
	drawTool->insertLinePoint(-0.5,-0.4,0);
	drawTool->insertLinePoint(-0.35,0,0);
	drawTool->insertLinePoint(-0.4,0,0);
	drawTool->endLineStrip();
}

void create_screwI()
{
	double pos_1[3]={0,0,0},pos_2[3]={0,0,0};
	int count= 90;
	DrawTool* drawTool=_shapeManager->getDrawTool();
	const double r = 0.4;
	//螺旋线
	for(int i = 0; i < count; i++)
	{
		double angle = i/(double)count*8*PI;
		pos_1[0] = -1+(i/(double)count)*2;
		pos_1[1] = r*cos(angle);
		pos_1[2] = r*sin(angle);
		angle = (i+1)/(double)count*8*PI;
		pos_2[0] = -1+((i+1)/(double)count)*2;
		pos_2[1] = r*cos(angle);
		pos_2[2] = r*sin(angle);
		drawTool->insertLine(pos_1,pos_2);
	}
	//两头的半圆
	count= 10;
	for(int i = 0; i < count; i++)
	{
		double angle = i/(double)count*PI-PI;
		pos_1[0] = -1;
		pos_1[1] = r*cos(angle);
		pos_1[2] = r*sin(angle);
		angle = (i+1)/(double)count*PI-PI;
		pos_2[0] = -1;
		pos_2[1] = r*cos(angle);
		pos_2[2] = r*sin(angle);
		drawTool->insertLine(pos_1,pos_2);
	}
	count= 10;
	for(int i = 0; i < count; i++)
	{
		double angle = i/(double)count*PI;
		pos_1[0] = 1;
		pos_1[1] = r*cos(angle);
		pos_1[2] = r*sin(angle);
		angle = (i+1)/(double)count*PI;
		pos_2[0] = 1;
		pos_2[1] = r*cos(angle);
		pos_2[2] = r*sin(angle);
		drawTool->insertLine(pos_1,pos_2);
	}
}
void create_screwJ()
{
	
	DrawTool* drawTool=_shapeManager->getDrawTool();

	
	//螺母
	double pos_1[3]={0,0,0},pos_2[3]={0,0,0};
	int count= 6;
	for(int i = 0; i < count; i++)
	{
		double angle = i/(double)count*2*PI;
		pos_1[0] = 0.25;
		pos_1[1] = cos(angle);
		pos_1[2] = sin(angle);
		angle = (i+1)/(double)count*2*PI;
		pos_2[0] = 0.25;
		pos_2[1] = cos(angle);
		pos_2[2] = sin(angle);
		drawTool->insertLine(pos_1,pos_2);
	}
	for(int i = 0; i < count; i++)
	{
		double angle = i/(double)count*2*PI;
		pos_1[0] = -0.25;
		pos_1[1] = cos(angle);
		pos_1[2] = sin(angle);
		angle = (i+1)/(double)count*2*PI;
		pos_2[0] = -0.25;
		pos_2[1] = cos(angle);
		pos_2[2] = sin(angle);
		drawTool->insertLine(pos_1,pos_2);
	}
	for(int i = 0; i < count; i++)
	{
		double angle = i/(double)count*2*PI;
		pos_1[0] = 0.25;
		pos_1[1] = cos(angle);
		pos_1[2] = sin(angle);
		pos_2[0] = -0.25;
		pos_2[1] = cos(angle);
		pos_2[2] = sin(angle);
		drawTool->insertLine(pos_1,pos_2);
	}
}
void create_convelI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//圆柱_2个圆端面
	double pos[3]={0,0,0};
	double pos_1[3]={0,0,0.3},pos_2[3]={0,0,0.3};
	double r= 0.07;
	int count = 40;
	pos[0] = 0; pos[1] = 0; pos[2]=0.15;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];		
		pos_1[1] = r*sin(angle)+pos[1];
		pos_1[2] = pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = r*sin(angle)+pos[1];
		pos_2[2] = pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
	pos[0] = 0; pos[1] = 0; pos[2]=0.8;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];		
		pos_1[1] = r*sin(angle)+pos[1];
		pos_1[2] = pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = r*sin(angle)+pos[1];
		pos_2[2] = pos[2];
		drawTool->insertLine(pos_1,pos_2);
	}
	//圆柱_侧面
	count = 10;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle);
		pos_1[2] = 0.8;

		pos_2[0] = r*cos(angle);
		pos_2[1] = r*sin(angle);
		pos_2[2] = 0.15;
		drawTool->insertLine(pos_1,pos_2);
	}
	//箭头，　注意圆心在(0, 0.1, 0.65处)
	//箭头_2个半圆
	double yoff = 0;
	double zoff = 0.65;
	count = 20;
	r = 0.3;
	for(int i = 0; i < count; i++)
	{
		double angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle)+yoff;
		pos_1[2] = zoff;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle)+yoff;
		pos_2[2] = zoff;
		drawTool->insertLine(pos_1,pos_2);
	}
	r = 0.4;
	for(int i = 0; i < count; i++)
	{
		double angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle)+yoff;
		pos_1[2] = zoff;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle)+yoff;
		pos_2[2] = zoff;
		drawTool->insertLine(pos_1,pos_2);
	}
	//箭头_起点线
	pos_1[0] = 0.3;
	pos_1[1] = yoff;
	pos_1[2] = zoff;
	pos_2[0] = 0.4;		//0.4
	pos_2[1] = yoff;
	pos_2[2] = zoff;	
	drawTool->insertLine(pos_1,pos_2);
	//箭头_箭头
	drawTool->beginLineStrip();
	pos_1[0] = -0.4; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.45; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.35; pos_1[1] = -0.15; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.25; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.3; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	drawTool->endLineStrip();
}
void create_convelJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double angle = 3*PI/4;//绕x转135度
	double mat[16]={1,0,0,0, 0,cos(angle),-sin(angle),0, 0,sin(angle),cos(angle),0, 0,0,0,1 };

	//圆柱_2个圆端面
	double pos[3]={0,0,0};
	double pos_1[3]={0,0,0.3},pos_2[3]={0,0,0.3};
	double r= 0.07;
	int count = 40;
	pos[0] = 0; pos[1] = 0; pos[2]=0.15;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];		
		pos_1[1] = r*sin(angle)+pos[1];
		pos_1[2] = pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = r*sin(angle)+pos[1];
		pos_2[2] = pos[2];
		transform(mat, pos_1);
		transform(mat, pos_2);
		drawTool->insertLine(pos_1,pos_2);
	}
	pos[0] = 0; pos[1] = 0; pos[2]=0.8;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle)+pos[0];		
		pos_1[1] = r*sin(angle)+pos[1];
		pos_1[2] = pos[2];
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle)+pos[0];
		pos_2[1] = r*sin(angle)+pos[1];
		pos_2[2] = pos[2];
		transform(mat, pos_1);
		transform(mat, pos_2);
		drawTool->insertLine(pos_1,pos_2);
	}
	//圆柱_侧面
	count = 10;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle);
		pos_1[2] = 0.8;

		pos_2[0] = r*cos(angle);
		pos_2[1] = r*sin(angle);
		pos_2[2] = 0.15;

		transform(mat, pos_1);
		transform(mat, pos_2);
		drawTool->insertLine(pos_1,pos_2);
	}
	//箭头，　注意圆心在(0, 0.1, 0.65处)
	//箭头_2个半圆
	double yoff = 0;
	double zoff = 0.65;
	count = 20;
	r = 0.3;
	for(int i = 0; i < count; i++)
	{
		double angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle)+yoff;
		pos_1[2] = zoff;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle)+yoff;
		pos_2[2] = zoff;

		transform(mat, pos_1);
		transform(mat, pos_2);
		drawTool->insertLine(pos_1,pos_2);
	}
	r = 0.4;
	for(int i = 0; i < count; i++)
	{
		double angle = PI/count*i;
		pos_1[0] = r*cos(angle);		
		pos_1[1] = r*sin(angle)+yoff;
		pos_1[2] = zoff;
		angle = PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle)+yoff;
		pos_2[2] = zoff;

		transform(mat, pos_1);
		transform(mat, pos_2);
		drawTool->insertLine(pos_1,pos_2);
	}
	//箭头_起点线
	pos_1[0] = 0.3;
	pos_1[1] = yoff;
	pos_1[2] = zoff;
	pos_2[0] = 0.4;		//0.4
	pos_2[1] = yoff;
	pos_2[2] = zoff;	

	transform(mat, pos_1);
	transform(mat, pos_2);
	drawTool->insertLine(pos_1,pos_2);
	//箭头_箭头
	drawTool->beginLineStrip();
	pos_1[0] = -0.4; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.45; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.35; pos_1[1] = -0.15; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.25; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	pos_1[0] = -0.3; pos_1[1] = 0; pos_1[2] = 0;
	pos_1[1] += yoff; pos_1[2] += zoff;
	transform(mat, pos_1);
	drawTool->insertLinePoint(pos_1[0], pos_1[1], pos_1[2]);
	drawTool->endLineStrip();
}
void create_sphericalI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0,-0.8},pos2[3]={0,0,-0.8};
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

	 
	double pos3[3]={0,0,-0.6},pos4[3]={0,0,-0.6};
	for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos3[0]=0.6*cos(si);
		pos3[1]=0.6*sin(si);
		si=2*PI*(j+1)/count;
		pos4[0]=0.6*cos(si);
		pos4[1]=0.6*sin(si);
		drawTool->insertLine(pos3,pos4);
	}

	double pos5[3]={0,0,-0.3},pos6[3]={0,0,-0.3};
	for(int k=0;k<=count;++k){
		si=2*PI*k/count;
		pos5[0]=0.8*cos(si);
		pos5[1]=0.8*sin(si);
		si=2*PI*(k+1)/count;
		pos6[0]=0.8*cos(si);
		pos6[1]=0.8*sin(si);
		drawTool->insertLine(pos5,pos6);
	}

	double pos7[3]={0,0,0},pos8[3]={0,0,0};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos7[0]=cos(si);
		pos7[1]=sin(si);
		si=2*PI*(i+1)/count;
		pos8[0]=cos(si);
		pos8[1]=sin(si);
		drawTool->insertLine(pos7,pos8);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0);
	drawTool->insertLinePoint(0,0,-1);
    drawTool->endLineStrip(); 

}
void create_sphericalJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	double pos1[3]={0,0,0.8},pos2[3]={0,0,0.8};
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

	 
	double pos3[3]={0,0,0.6},pos4[3]={0,0,0.6};
	for(int j=0;j<=count;++j){
		si=2*PI*j/count;
		pos3[0]=0.6*cos(si);
		pos3[1]=0.6*sin(si);
		si=2*PI*(j+1)/count;
		pos4[0]=0.6*cos(si);
		pos4[1]=0.6*sin(si);
		drawTool->insertLine(pos3,pos4);
	}

	double pos5[3]={0,0,0.3},pos6[3]={0,0,0.3};
	for(int k=0;k<=count;++k){
		si=2*PI*k/count;
		pos5[0]=0.8*cos(si);
		pos5[1]=0.8*sin(si);
		si=2*PI*(k+1)/count;
		pos6[0]=0.8*cos(si);
		pos6[1]=0.8*sin(si);
		drawTool->insertLine(pos5,pos6);
	}

	double pos7[3]={0,0,0},pos8[3]={0,0,0};
	for(int i=0;i<=count;++i){
		si=2*PI*i/count;
		pos7[0]=cos(si);
		pos7[1]=sin(si);
		si=2*PI*(i+1)/count;
		pos8[0]=cos(si);
		pos8[1]=sin(si);
		drawTool->insertLine(pos7,pos8);
	}

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0);
	drawTool->insertLinePoint(0,0,1);
    drawTool->endLineStrip();  
}

void create_translationalI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//大立方体
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
}
void create_translationalJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//小立方体
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
void create_inplaneI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//平面
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(1,1,0);
	drawTool->insertLinePoint(1,-1,0);
	drawTool->insertLinePoint(-1,-1,0);
	drawTool->insertLinePoint(-1,1,0);
	drawTool->insertLinePoint(1,1,0);
	drawTool->endLineStrip();
}
void create_inplaneJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//生成变换矩阵
	double angle = PI/4;//绕y转45度
	double mat1[16]={cos(angle),0,sin(angle),0, 0,1,0,0, -sin(angle),0,cos(angle),0, 0,0,0,1 };
	angle = -PI/12;//绕x转15度
	double mat2[16]={1,0,0,0, 0,cos(angle),-sin(angle),0, 0,sin(angle),cos(angle),0, 0,0,0,1 };
	//x轴平移-0.5
	double mat3[16]={1,0,0,-0.5, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	double mat[16];
	double temp[16];
	multimatrix(mat2,mat1,temp);
	multimatrix(mat3,temp,mat);

	//箭头	
	double pos_1[3]={0,0,0},pos_2[3]={0,0,0.9},pos_3[3]={-0.15,0,0.3},pos_4[3]={0.15,0,0.3};
	transform(mat,pos_1);
	transform(mat,pos_2);
	transform(mat,pos_3);
	transform(mat,pos_4);
	drawTool->insertLine(pos_1,pos_2);
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(pos_1[0],pos_1[1],pos_1[2]);
	drawTool->insertLinePoint(pos_3[0],pos_3[1],pos_3[2]);
	drawTool->insertLinePoint(pos_4[0],pos_4[1],pos_4[2]);
	drawTool->insertLinePoint(pos_1[0],pos_1[1],pos_1[2]);
	drawTool->endLineStrip();
}
void create_inlineI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//平面
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(1,1,0);
	drawTool->insertLinePoint(1,-1,0);
	drawTool->insertLinePoint(-1,-1,0);
	drawTool->insertLinePoint(-1,1,0);
	drawTool->insertLinePoint(1,1,0);
	drawTool->endLineStrip();
	//直线
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,1);
	drawTool->insertLinePoint(0,0,-1);
	drawTool->endLineStrip();

}
void create_inlineJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//生成变换矩阵
	double angle = PI/4;//绕y转45度
	double mat[16]={cos(angle),0,sin(angle),0, 0,1,0,0, -sin(angle),0,cos(angle),0, 0,0,0,1 };

	//箭头	
	double pos_1[3]={0,0,0},pos_2[3]={1,0,0},pos_3[3]={0.3,0,-0.15},pos_4[3]={0.3,0,0.15};
	transform(mat,pos_1);
	transform(mat,pos_2);
	transform(mat,pos_3);
	transform(mat,pos_4);
	drawTool->insertLine(pos_1,pos_2);
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(pos_1[0],pos_1[1],pos_1[2]);
	drawTool->insertLinePoint(pos_3[0],pos_3[1],pos_3[2]);
	drawTool->insertLinePoint(pos_4[0],pos_4[1],pos_4[2]);
	drawTool->insertLinePoint(pos_1[0],pos_1[1],pos_1[2]);
	drawTool->endLineStrip();
}
void create_orientationI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//平面
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(1,1,0);
	drawTool->insertLinePoint(1,-1,0);
	drawTool->insertLinePoint(-1,-1,0);
	drawTool->insertLinePoint(-1,1,0);
	drawTool->insertLinePoint(1,1,0);
	drawTool->endLineStrip();

	//坐标轴３个
	double pos_1[3]={0,0,0},pos_2[3]={0,0,1};
	pos_1[0] = 0;
	pos_1[1] = 0;
	pos_1[2] = 0;
	pos_2[0] = 0.8;
	pos_2[1] = 0;
	pos_2[2] = 0;
	drawTool->insertLine(pos_1,pos_2);
	pos_2[0] = 0;
	pos_2[1] = 0.8;
	pos_2[2] = 0;
	drawTool->insertLine(pos_1,pos_2);
	pos_2[0] = 0;
	pos_2[1] = 0;
	pos_2[2] = 0.8;
	drawTool->insertLine(pos_1,pos_2);

	//箭头3个
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0.8,0,0);
	drawTool->insertLinePoint(0.5,0.15,0);
	drawTool->insertLinePoint(0.5,-0.15,0);
	drawTool->insertLinePoint(0.8,0,0);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0.8,0);
	drawTool->insertLinePoint(0,0.5,0.15);
	drawTool->insertLinePoint(0,0.5,-0.15);
	drawTool->insertLinePoint(0,0.8,0);
	drawTool->endLineStrip();
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0.8);
	drawTool->insertLinePoint(0.15,0,0.5);
	drawTool->insertLinePoint(-0.15,0,0.5);
	drawTool->insertLinePoint(0,0,0.8);
	drawTool->endLineStrip();

}
void create_orientationJ()
{
	create_orientationI();
}

void create_parallelI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//圆
	double pos_1[3]={0,0,0},pos_2[3]={0,0,1};
	double r= 1.0;
	int count = 20;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle);
		pos_1[1] = r*sin(angle);
		pos_1[2] = 0;		
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle);
		pos_2[2] = 0;
		drawTool->insertLine(pos_1,pos_2);
	}
	//箭头_长直线
	pos_1[0] = 0;
	pos_1[1] = 0.1;
	pos_1[2] = -0.8;
	pos_2[0] = 0;
	pos_2[1] = 0.1;
	pos_2[2] = 0.8;
	drawTool->insertLine(pos_1,pos_2);

	//箭头_四边形
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0.1,-0.8);
	drawTool->insertLinePoint(0,0,-0.9);
	drawTool->insertLinePoint(0,0,-0.6);
	drawTool->insertLinePoint(0,0.1,-0.5);
	drawTool->insertLinePoint(0,0.2,-0.6);
	drawTool->insertLinePoint(0,0.2,-0.9);
	drawTool->insertLinePoint(0,0.1,-0.8);
	drawTool->endLineStrip();

	//箭头_箭头
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0.1,0.8);
	drawTool->insertLinePoint(0,0,0.64);
	drawTool->insertLinePoint(0,0.2,0.64);
	drawTool->insertLinePoint(0,0.1,0.8);
	drawTool->endLineStrip();
}
void create_parallelJ()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//圆
	double pos_1[3]={0,0,0},pos_2[3]={0,0,1};
	double r= 1.0;
	int count = 20;
	for(int i = 0; i < count; i++)
	{
		double angle = 2*PI/count*i;
		pos_1[0] = r*cos(angle);
		pos_1[1] = r*sin(angle);
		pos_1[2] = 0;		
		angle = 2*PI/count*(i+1);
		pos_2[0] = r*cos(angle);		
		pos_2[1] = r*sin(angle);
		pos_2[2] = 0;
		drawTool->insertLine(pos_1,pos_2);
	}
	//箭头_长直线
	pos_1[0] = 0;
	pos_1[1] = -0.1;
	pos_1[2] = -0.8;
	pos_2[0] = 0;
	pos_2[1] = -0.1;
	pos_2[2] = 0.8;
	drawTool->insertLine(pos_1,pos_2);

	//箭头_四边形
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,-0.1,-0.8);
	drawTool->insertLinePoint(0,0,-0.9);
	drawTool->insertLinePoint(0,0,-0.6);
	drawTool->insertLinePoint(0,-0.1,-0.5);
	drawTool->insertLinePoint(0,-0.2,-0.6);
	drawTool->insertLinePoint(0,-0.2,-0.9);
	drawTool->insertLinePoint(0,-0.1,-0.8);
	drawTool->endLineStrip();

	//箭头_箭头
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,-0.1,0.8);
	drawTool->insertLinePoint(0,0,0.64);
	drawTool->insertLinePoint(0,-0.2,0.64);
	drawTool->insertLinePoint(0,-0.1,0.8);
	drawTool->endLineStrip();
}
void create_perpendicularI()
{
	DrawTool* drawTool=_shapeManager->getDrawTool();
	//大矩形
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(-1,-1,0);
	drawTool->insertLinePoint(-1,1,0);
	drawTool->insertLinePoint(1,1,0);
	drawTool->insertLinePoint(1,-1,0);
	drawTool->insertLinePoint(-1,-1,0);
	drawTool->endLineStrip();

	//小矩形
	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,0);
	drawTool->insertLinePoint(0,0.8,0);
	drawTool->insertLinePoint(0,0.8,0.8);
	drawTool->insertLinePoint(0,0,0.8);
	drawTool->insertLinePoint(0,0,0);
	drawTool->endLineStrip();

	//箭头
	double pos_1[3]={0,0,0},pos_2[3]={0,0,1};
	drawTool->insertLine(pos_1,pos_2);

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,0,1);
	drawTool->insertLinePoint(-0.08,0,0.9);
	drawTool->insertLinePoint(0.08,0,0.9);
	drawTool->insertLinePoint(0,0,1);
	drawTool->endLineStrip();

	double pos_3[3]={0,0,0},pos_4[3]={0,1,0};
	drawTool->insertLine(pos_3,pos_4);

	drawTool->beginLineStrip();
	drawTool->insertLinePoint(0,1,0);
	drawTool->insertLinePoint(-0.08,0.9,0);
	drawTool->insertLinePoint(0.08,0.9,0);
	drawTool->insertLinePoint(0,1,0);
	drawTool->endLineStrip();
}
void create_perpendicularJ()
{
	create_perpendicularI();
}



void shapePara_InsertItem(ShapePara& para,int index,const string& dis,float va)
{
	para.discription[index]=dis;
	para.values[index]=va;
}
void importShapesCollection()
{
	_shapeManager->insertShape("FIXED.I",createFixedJointI);
	_shapeManager->insertShape("FIXED.J",createFixedJointJ);
	_shapeManager->insertShape("HOOKE.I",create_hookeI);
	//_shapeManager->insertShape("HOOKE.J",create_hookeJ);
	_shapeManager->insertShape("HOOKE.J",create_hookeI);
	//_shapeManager->insertShape("XXX.I",create_myXXXI);
	//_shapeManager->insertShape("XXX.J",create_myXXXJ);
	_shapeManager->insertShape("PLANAR.I",create_planarI);
	_shapeManager->insertShape("PLANAR.J",create_planarJ);
	_shapeManager->insertShape("CYLINDRICAL.I",create_cylindricalI);
	_shapeManager->insertShape("CYLINDRICAL.J",create_cylindricalJ);
	_shapeManager->insertShape("REVOLUTE.I",create_revoluteI);
	_shapeManager->insertShape("REVOLUTE.J",create_revoluteJ);
	_shapeManager->insertShape("SCREW.I",create_screwI);
	_shapeManager->insertShape("SCREW.J",create_screwJ);
	_shapeManager->insertShape("CONVEL.I",create_convelI);
	_shapeManager->insertShape("CONVEL.J",create_convelJ);
	_shapeManager->insertShape("SPHERICAL.I",create_sphericalI);
	_shapeManager->insertShape("SPHERICAL.J",create_sphericalJ);
	_shapeManager->insertShape("TRANSLATIONAL.I",create_translationalI);
	_shapeManager->insertShape("TRANSLATIONAL.J",create_translationalJ);
	_shapeManager->insertShape("INPLANE.I",create_inplaneI);
	_shapeManager->insertShape("INPLANE.J",create_inplaneJ);
	_shapeManager->insertShape("INLINE.I",create_inlineI);
	_shapeManager->insertShape("INLINE.J",create_inlineJ);
	_shapeManager->insertShape("ORIENTATION.I",create_orientationI);
	_shapeManager->insertShape("ORIENTATION.J",create_orientationJ);
	_shapeManager->insertShape("PARALLEL.I",create_parallelI);
	_shapeManager->insertShape("PARALLEL.J",create_parallelJ);	
	_shapeManager->insertShape("PERPENDICULAR.I",create_perpendicularI);
	_shapeManager->insertShape("PERPENDICULAR.J",create_perpendicularJ);

}

