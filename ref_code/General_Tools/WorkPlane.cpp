// WorkPlane.cpp: implementation of the CWorkPlane class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "pangu_mbdyn.h"
#include "WorkPlane.h"

#include "LocalMatrix.h"
#include "vds_vectorfuncs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorkPlane::CWorkPlane()
{
	Initail();
}

CWorkPlane::~CWorkPlane()
{

}

void CWorkPlane::Initail()
{
	double origin[3]={ 0,0,0 };
	double point1[3]={ 1,0,0 };
	double point2[3]={ 0,1,0 };
	SetCoord3P(origin, point1, point2, 1);
}

void CWorkPlane::SetCoord( LOC_COORD coord )
{
	m_WorkPlaneCoord.copy(coord);
}

void CWorkPlane::SetCoord3P( double origin[3], double point1[3], double point2[3], int type, int iopt )
{
	int i;
	for( i=0; i<3; i++ )
	{
		m_WorkPlaneCoord.fOrigin[i] = origin[i];
		m_WorkPlaneCoord.fPoint1[i] = point1[i];
		m_WorkPlaneCoord.fPoint2[i] = point2[i];
	}
	m_WorkPlaneCoord.iType = type;
	float din[10] = {	0.0, 
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0};  // din[0] no use
	
	int inta = type; // referrence coordinate system is rectangle - 1, Cylindrical - 2, Spherical - 3; 
	int intb = 1; // referrence coordinate is global 
//	int iopt = 1; 
//		c*      option 1 - pt. 1 origin, pt.2 on x axis, pt. 3 on xy plane
//		c*      option 2 - pt. 1 origin, pt.2 on x axis, pt. 3 on xz plane
//		c*      option 3 - pt. 1 origin, pt.2 on y axis, pt. 3 on yz plane
//		c*      option 4 - pt. 1 origin, pt.2 on y axis, pt. 3 on xy plane
//		c*      option 5 - pt. 1 origin, pt.2 on z axis, pt. 3 on xz plane
//		c*      option 6 - pt. 1 origin, pt.2 on z axis, pt. 3 on yz plane
		
	float pt[10];
	for(i=0; i<3; i++)
	{
		pt[i+1] = origin[i];
		pt[i+4] = point1[i];
		pt[i+7] = point2[i];
	}
	float dircos[10];
	bastoloc6( inta, intb, iopt, pt, din, dircos);
	for(i=0; i<9; i++) 
	{
		m_WorkPlaneCoord.fGlobal2Loc3[i] = dircos[i+1];
	}
	float din1[10] = {	0.0, 
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0};  // din[0] no use
	bastoloc2( inta, intb, iopt, pt, din1, dircos);
	for(i=0; i<9; i++) 
	{
		m_WorkPlaneCoord.fLoc2Global3[i] = dircos[i+1];
	}
	for(i=0; i<3; i++) 
	{
		m_WorkPlaneCoord.fLocOrigin[i] = origin[i];
	}
	
}

void CWorkPlane::GlobalToLocal( double fGlobal[3], double fLocal[3] )
{
	int i,j;
	double global[3];
	for(i=0; i<3; i++)
	{
		fLocal[i] = 0;
		global[i] = fGlobal[i];
	}
	for(i=0; i<3; i++)
	{
		global[i] -= m_WorkPlaneCoord.fLocOrigin[i];
	}
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			fLocal[i] += m_WorkPlaneCoord.fGlobal2Loc3[i*3+j]*global[j];
		}
	}
}

void CWorkPlane::LocalToGlobal( double fLocal[3], double fGlobal[3] )
{
	int i,j;
	for(i=0; i<3; i++)
	{
		fGlobal[i] = 0;
	}
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			fGlobal[i] += m_WorkPlaneCoord.fLoc2Global3[i*3+j]*fLocal[j];
		}
	}
	for(i=0; i<3; i++)
	{
		fGlobal[i] += m_WorkPlaneCoord.fLocOrigin[i];
	}
}

void CWorkPlane::OffsetCoord( double offX, double offY, double offZ )
{
	m_WorkPlaneCoord.fLocOrigin[0] += offX;
	m_WorkPlaneCoord.fLocOrigin[1] += offY;
	m_WorkPlaneCoord.fLocOrigin[2] += offZ;
}

void CWorkPlane::RotateCoord( double angleX, double angleY, double angleZ )
{
	int intb=2;
	float din[10] = {	0.0, 
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0};  // din[0] no use
	int i;
//	for( i=0; i<9; i++) {
//		din[i+1] = m_WorkPlaneCoord.fLoc2Global3[i];
//	}
	float dircos[10], dinSave[10];
	double dTrans1[9], dTrans2[9];
	for( i=1; i<10; i++) {
		dinSave[i] = din[i];
	}	
	
	bastoloc1(intb, angleX, angleY, angleZ, din, dircos);
	for( i=0; i<9; i++) {
		dTrans1[i] = m_WorkPlaneCoord.fGlobal2Loc3[i];
		dTrans2[i] = dircos[i+1];
	}
	vds_matrixMultiply(3,3,dTrans1, 3, 3, dTrans2, m_WorkPlaneCoord.fGlobal2Loc3);
	
	for( i=1; i<10; i++) {
		din[i] = dinSave[i];
	}
	bastoloc5(intb, angleX, angleY, angleZ, din, dircos);
	for( i=0; i<9; i++) {
		dTrans1[i] = m_WorkPlaneCoord.fLoc2Global3[i];
		dTrans2[i] = dircos[i+1];
	}
	vds_matrixMultiply(3,3,dTrans1, 3, 3, dTrans2, m_WorkPlaneCoord.fLoc2Global3);
}

void CWorkPlane::GetRange( float range[6] )
{
	range[0] = m_WorkPlaneCoord.fLocOrigin[0] - m_snapdef.dwNum*m_snapdef.iStepX/8;
	range[1] = m_WorkPlaneCoord.fLocOrigin[1] - m_snapdef.dwNum*m_snapdef.iStepY/8;
	range[2] = m_WorkPlaneCoord.fLocOrigin[2] - m_snapdef.dwNum*m_snapdef.iStepX/8;
	range[3] = m_WorkPlaneCoord.fLocOrigin[0] + m_snapdef.dwNum*m_snapdef.iStepX/8;
	range[4] = m_WorkPlaneCoord.fLocOrigin[1] + m_snapdef.dwNum*m_snapdef.iStepY/8;
	range[5] = m_WorkPlaneCoord.fLocOrigin[2] + m_snapdef.dwNum*m_snapdef.iStepX/8;
}