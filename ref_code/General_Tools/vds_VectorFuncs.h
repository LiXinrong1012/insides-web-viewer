#ifndef _VDS_VECTOR_FUNCS_
#define  _VDS_VECTOR_FUNCS_

#include <math.h>
#include <float.h>
#include "vds_datatypes.h"
#include "vds_constants.h"

#define ZERO_TOL .000001
#define ZERO_TOL_BIG .001

inline double vds_vectDistance(VDOUBLE *v1,VDOUBLE *v2)
{
	double res[3];
	res[0] = v2[0] - v1[0];
	res[1] = v2[1] - v1[1];
	res[2] = v2[2] - v1[2];

	return sqrt(res[0]*res[0] + res[1]*res[1] + res[2]*res[2]);
}


inline void vds_vectDiff(VDOUBLE *v1,VDOUBLE *v2,VDOUBLE *res)
{
	res[0] = v2[0] - v1[0];
	res[1] = v2[1] - v1[1];
	res[2] = v2[2] - v1[2];
}

inline void vds_vectAssign(VDOUBLE *v1, VDOUBLE *v2)
{
	v1[0] = v2[0];
	v1[1] = v2[1];
	v1[2] = v2[2];
}

inline VFLOAT vds_vectMagnitude(VFLOAT *v)
{
	return (VFLOAT)sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}


inline VDOUBLE vds_vectMagnitude(VDOUBLE *v)
{
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}


inline void vds_vectNormalize(VDOUBLE *v)
{
	VDOUBLE mag = vds_vectMagnitude(v);

	if(mag <= 0)
		return;
	v[0] = v[0]/mag;
	v[1] = v[1]/mag;
	v[2] = v[2]/mag;
}

inline void vds_vectNormalize(VFLOAT *v)
{
	VFLOAT mag = vds_vectMagnitude(v);

	if(mag <= 0)
		return;
	v[0] = v[0]/mag;
	v[1] = v[1]/mag;
	v[2] = v[2]/mag;
}



inline void vds_vectAdd(VDOUBLE *v1, VDOUBLE *v2 , VDOUBLE *res)
{
	res[0] = v1[0] + v2[0];
	res[1] = v1[1] + v2[1];
	res[2] = v1[2] + v2[2];
}

inline void vds_vectScale(VDOUBLE *v1, VDOUBLE mag)
{
	v1[0] = v1[0] * mag;
	v1[1] = v1[1] * mag;
	v1[2] = v1[2] * mag;
}


inline VDOUBLE vds_vectDotProduct(VDOUBLE *v1,VDOUBLE *v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] ;
}

inline void vds_vectCrossProduct(VDOUBLE *v1,VDOUBLE *v2, VDOUBLE *res)
{
	res[0] = v1[1]*v2[2] - v1[2]*v2[1];
	res[1] = v1[2]*v2[0] - v1[0]*v2[2];
	res[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

inline VDOUBLE vds_vectAngle(VDOUBLE *v1,VDOUBLE *v2)
{
	double dotVal = vds_vectDotProduct(v1,v2);

	double vectMag1, vectMag2;
	
	vectMag1 = vds_vectMagnitude(v1);
	vectMag2 = vds_vectMagnitude(v2);

	if(vectMag1<=0)
		vectMag1 = DBL_MIN;

	if(vectMag2<=0)
		vectMag2 = DBL_MIN;

	dotVal = dotVal/(vectMag1*vectMag2);


	if(dotVal>1)
		dotVal = 1;
	else if(dotVal<-1)
		dotVal = -1;

	double ang;
	ang = acos(dotVal)*180/3.141592654;

	return ang;
}

inline VDOUBLE vds_vectAngle_From3Points(VDOUBLE *v1,VDOUBLE *v2, VDOUBLE *v3)
{

	double vect1[3],vect2[3];

	vds_vectDiff(v2,v1,vect1);
	vds_vectDiff(v2,v3,vect2);

	double dotVal = vds_vectDotProduct(vect1,vect2);

	double vectMag1, vectMag2;
	
	vectMag1 = vds_vectMagnitude(vect1);
	vectMag2 = vds_vectMagnitude(vect2);

	if(vectMag1<=0)
		vectMag1 = DBL_MIN;

	if(vectMag2<=0)
		vectMag2 = DBL_MIN;

	dotVal = dotVal/(vectMag1*vectMag2);


	if(dotVal>1)
		dotVal = 1;
	else if(dotVal<-1)
		dotVal = -1;

	double ang;
	ang = acos(dotVal)*180/3.141592654;

	return ang;
}

inline void vds_vectNormal(VDOUBLE *v1,VDOUBLE *v2, VDOUBLE* res)
{
	vds_vectCrossProduct(v1,v2,res);
	vds_vectNormalize(res);
}

inline void vds_vectTriNormal(VDOUBLE *vXYZ1,VDOUBLE *vXYZ2,VDOUBLE *vXYZ3, VDOUBLE* res)
{
	VDOUBLE v1[3],v2[3];
	
	vds_vectDiff(vXYZ1,vXYZ2,v1);
	vds_vectNormalize(v1);
	vds_vectDiff(vXYZ1,vXYZ3,v2);
	vds_vectNormalize(v2);

	vds_vectCrossProduct(v1,v2,res);
	vds_vectNormalize(res);
}


inline double vds_vectArea(VDOUBLE *v1,VDOUBLE *v2, VDOUBLE *v3)
{
	double vect1[3],vect2[3],normal[3];

	vds_vectDiff(v1, v2, vect1) ;
	vds_vectDiff(v1, v3, vect2) ;

	vds_vectCrossProduct(vect1, vect2, normal) ;
    return vds_vectMagnitude( normal) ;
}

inline void FindPointInTriEdgeByAngle(double *pt1,double *pt2,double *pt3,double rotAngle,double *retPt,double *ptParam=NULL)
{
	double vect1[3],vect2[3];
	double angA,angB,angC, lenA,lenB;

	angB = rotAngle;

	vds_vectDiff(pt2,pt1,vect1);
	vds_vectDiff(pt2,pt3,vect2);

	lenA = vds_vectMagnitude(vect1);

	angC = vds_vectAngle(vect1,vect2);
	angA = 180 - angB - angC;

	lenB = (sin((angB*3.141592654)/180)*lenA)/sin((angA*3.141592654)/180);

	if(ptParam)
	{
		double totLen = vds_vectMagnitude(vect2);
		if(totLen)
			*ptParam = lenB/totLen;
		else
			*ptParam=0;
	}
	
	vds_vectNormalize(vect2);
	vds_vectScale(vect2,lenB);
	vds_vectAdd(pt2,vect2,retPt);
}

inline bool vds_isPointOnPlane(double *srcPt ,double *planePt1, double *planePt2, double *planePt3,double distTol)
{
	double vect1[3], vect2[3], vect3[3];
	double planeNormal[3];

	vds_vectDiff(planePt1, planePt2, vect1);
	vds_vectDiff(planePt1, planePt3, vect2);
	vds_vectCrossProduct(vect1, vect2, planeNormal);

	double thisDistTol;

	thisDistTol = distTol;
	if(thisDistTol<0)
		thisDistTol = vds_vectMagnitude(planeNormal)/1000;

	vds_vectNormalize(planeNormal) ;

	vds_vectDiff(planePt1, srcPt, vect3);
	double dist = fabs(vds_vectDotProduct(vect3, planeNormal));

	if(dist < thisDistTol)
		return true;
	else
		return false;
}


inline bool vds_ProjectPointOnPlane(double *srcPt ,double *planePt1, double *planePt2, double *planePt3,double *projPt )
{
	double vect1[3], vect2[3], vect3[3];
	double planeNormal[3];

	vds_vectDiff(planePt1, planePt2, vect1);
	vds_vectDiff(planePt1, planePt3, vect2);
	vds_vectCrossProduct(vect1, vect2, planeNormal);
	vds_vectNormalize(planeNormal) ;

	vds_vectDiff(planePt1, srcPt, vect3);
	double dist = vds_vectDotProduct(vect3, planeNormal);

    vds_vectScale(planeNormal, -dist ) ;
	vds_vectAdd( srcPt, planeNormal, projPt ) ;

	return true;
}


inline bool vds_ProjectPointOnLine(double *srcPt, double *linePt1, double *linePt2, double &s,double &dist, double *projPt)
{
	double mag, diffVect1[3],diffVect2[3];

	vds_vectDiff(linePt1,linePt2,diffVect1);
    mag  = vds_vectMagnitude(diffVect1);
    if( mag == 0 ) 
        return false ;
	vds_vectNormalize(diffVect1);

	vds_vectDiff(linePt1,srcPt,diffVect2);

    s = vds_vectDotProduct(diffVect1,diffVect2) / mag ;

	vds_vectNormalize(diffVect1);
	vds_vectScale(diffVect1,s*mag);
	vds_vectAssign(projPt,linePt1);
	vds_vectAdd(projPt,diffVect1,projPt);
	dist = vds_vectDistance(srcPt,projPt);
	return true ;
}


inline bool  vds_calcBCC(double *srcPt, double *triPt1, double *triPt2, double *triPt3,double *bccPt)
{
	double vect1[3], vect2[3], normal1[3], normal2[3], area ;
	
	vds_vectDiff(triPt1, triPt2, vect1) ;
	vds_vectDiff(triPt1, triPt3, vect2) ;

	vds_vectCrossProduct(vect1, vect2, normal1) ;
    area = vds_vectMagnitude( normal1) ;
	vds_vectNormalize(normal1);

    if( area < DBL_MIN ) 
	{
		bccPt[0] =0,bccPt[1]=1,bccPt[2]=0;
		return false;
    }
		
	vds_vectDiff(triPt1, triPt2, vect1) ;
	vds_vectDiff(triPt1, srcPt, vect2) ;
	vds_vectCrossProduct(vect1, vect2, normal2) ;
	
	bccPt[0] = vds_vectDotProduct(normal1, normal2) / ( area ) ;

	vds_vectDiff(triPt2, triPt3, vect1) ;
	vds_vectDiff(triPt2, srcPt, vect2) ;
	vds_vectCrossProduct(vect1, vect2, normal2) ;
	
	bccPt[1] = vds_vectDotProduct(normal1, normal2) / ( area ) ;

	vds_vectDiff(triPt3, triPt1, vect1) ;
	vds_vectDiff(triPt3, srcPt, vect2) ;
	vds_vectCrossProduct(vect1, vect2, normal2) ;
	
	bccPt[2] = vds_vectDotProduct(normal1, normal2) / ( area ) ;

	return true ;
}



inline bool vds_isPointOnTriangle( double *srcPt, double triPt1[3],double triPt2[3],double triPt3[3], double distTol)
{ 

	if(distTol<0)
		distTol = .001;


	double triArea = vds_vectArea(triPt1,triPt2,triPt3);
	if(triArea==0)
		return false;

	double totArea=0;

	totArea += vds_vectArea(triPt1,triPt2,srcPt);
	totArea += vds_vectArea(triPt2,triPt3,srcPt);
	totArea += vds_vectArea(triPt3,triPt1,srcPt);


	if((totArea/triArea)>1+distTol)
		return false;
	else
		return true;	 
}



/*
	ptCode - This code tells where the point lies inside tri

	0 - Completely inside tri
	1 -  near triPt1
	2 -  near triPt2
	3 -  near triPt3
	4 -  near triEdge1
	5 -  near triEdge2
	6 -  near triEdge3
*/

inline bool vds_projectPointOnTriangle( double *srcPt, double triPt1[3],double triPt2[3],double triPt3[3],
       int &ptCode, double projPt[3], double tol = ZERO_TOL)
{ 

	ptCode = 0;

	if(!vds_ProjectPointOnPlane( srcPt,triPt1, triPt2, triPt3, projPt ))
		return false;

	double bccPt[3];
	if(!vds_calcBCC(projPt, triPt1, triPt2, triPt3, bccPt)) 
		return false ;

	double s, dist;
	
	if(bccPt[0] < -ZERO_TOL)
	{
		if(!vds_ProjectPointOnLine(srcPt,triPt1,triPt2,s,dist,projPt))
			return false;
		if(s>=1)
		{
			projPt[0] = triPt2[0];
			projPt[1] = triPt2[1];
			projPt[2] = triPt2[2];
			ptCode = 2;
		}
		else if(s<=0)
		{
			projPt[0] = triPt1[0];
			projPt[1] = triPt1[1];
			projPt[2] = triPt1[2];
			ptCode = 1;
		}
		else
			ptCode = 4;
	}	
	else if(bccPt[1] < -ZERO_TOL)
	{
		if(!vds_ProjectPointOnLine(srcPt,triPt2,triPt3,s,dist,projPt))
			return false;
		if(s>=1)
		{
			projPt[0] = triPt3[0];
			projPt[1] = triPt3[1];
			projPt[2] = triPt3[2];
			ptCode = 3;
		}
		else if(s<=0)
		{
			projPt[0] = triPt2[0];
			projPt[1] = triPt2[1];
			projPt[2] = triPt2[2];
			ptCode = 2;
		}
		else
			ptCode = 5;
	}
	else if(bccPt[2] < -ZERO_TOL)
	{
		if(!vds_ProjectPointOnLine(srcPt,triPt3,triPt1,s,dist,projPt))
			return false;
		if(s>=1)
		{
			projPt[0] = triPt1[0];
			projPt[1] = triPt1[1];
			projPt[2] = triPt1[2];
			ptCode = 1;
		}
		else if(s<=0)
		{
			projPt[0] = triPt3[0];
			projPt[1] = triPt3[1];
			projPt[2] = triPt3[2];
			ptCode = 3;
		}
		else
			ptCode = 6;
	}
	else if( bccPt[0] > 1.0 - tol ) 
		ptCode = 3;
	else if( bccPt[1] > 1.0 - tol ) 
		ptCode = 1;
	else if( bccPt[2] > 1.0 - tol ) 
		ptCode = 2;
	else if( bccPt[0] < tol ) 
		ptCode = 4;
	else if( bccPt[1] < tol ) 
		ptCode = 5;
	else if( bccPt[2] < tol ) 
		ptCode = 6;
	return true;	 
}


inline double vds_TetVolume(double *pt1, double *pt2, double *pt3, double *pt4)
{

	double vect1[3], vect2[3], vect3[3], planeNorm[3], vol;
	
	vds_vectDiff(pt1, pt2, vect1);
	vds_vectDiff(pt1, pt3, vect2);
	vds_vectDiff(pt1, pt4, vect3);

	vds_vectCrossProduct(vect1, vect2, planeNorm);

	vol = vds_vectDotProduct(planeNorm, vect3);

	if(vol<0)
		return -vol;
	else
		return vol;

}


inline bool vds_ProjectPointOnBoundLine(double *srcPt, double *linePt1, double *linePt2, double *projPt)
{
	double s,dist;

	vds_ProjectPointOnLine(srcPt,linePt1,linePt2,s,dist,projPt);

	if(s>=1)
	{
		projPt[0] = linePt2[0];
		projPt[1] = linePt2[1];
		projPt[2] = linePt2[2];
	}
	else if(s<=0)
	{
		projPt[0] = linePt1[0];
		projPt[1] = linePt1[1];
		projPt[2] = linePt1[2];
	}

	return true ;
}

inline bool vds_FindPlaneLineIntersection_M1(double *linePt1, double *linePt2, double *planePt1, 
							 double *planePt2, double *planePt3, double *retPt, double *param)
{

	double vect1[3], vect2[3], planeNormal[3];
	*param = 0;

	vds_vectDiff(planePt1, planePt2, vect1);
	vds_vectDiff(planePt1, planePt3, vect2);
	

	vds_vectCrossProduct(vect1, vect2, planeNormal);
	vds_vectNormalize(planeNormal);

	vds_vectDiff(linePt1, planePt1, vect1);
	vds_vectDiff(linePt1, linePt2, vect2);

	double dotVal1,dotVal2;

	dotVal1 = vds_vectDotProduct(planeNormal, vect1);
	dotVal2 = vds_vectDotProduct(planeNormal, vect2);

	if (fabs(dotVal2) <= DBL_MIN)
		return false;

	*param = dotVal1 / dotVal2;

	for (int i = 0; i < 3; i++)
		retPt[i] = linePt1[i] + (*param) * (linePt2[i] - linePt1[i]);

	return true;
}


inline bool vds_FindPlaneLineIntersection_M2(double *linePt1, double *linePt2, double *planePt, 
							 double *planeNormal,double *retPt, double *param)
{

	double vect1[3], vect2[3];
	*param = 0;

	vds_vectDiff(linePt1, planePt, vect1);
	vds_vectDiff(linePt1, linePt2, vect2);

	double dotVal1,dotVal2;

	dotVal1 = vds_vectDotProduct(planeNormal, vect1);
	dotVal2 = vds_vectDotProduct(planeNormal, vect2);

	if (fabs(dotVal2) <= DBL_MIN)
		return false;

	*param = dotVal1 / dotVal2;

	for (int i = 0; i < 3; i++)
		retPt[i] = linePt1[i] + (*param) * (linePt2[i] - linePt1[i]);

	return true;
}

/*
  Return Value:
	true - Lines are crossing and found the distance
	false - Lines are parallel 
*/

inline bool vds_FindLineLineDistance(double *linePt1, double *linePt2, double *linePt3, double *linePt4,
									  double *lineIntersectParam1, double *lineIntersectParam2, double *shortDist,double *shortPoint1, double *shortPoint2)
{
	double diffVect1[3],diffVect2[3],diffVect3[3];

	double dotP1,dotP2,dotP3,dotP4,dotP5;
	double par1, par2;
	double equ1, equ2;

	vds_vectDiff(linePt1, linePt2, diffVect1);
	vds_vectDiff(linePt3, linePt4, diffVect2);
	vds_vectDiff(linePt1, linePt3, diffVect3);
		
	
	dotP1 = vds_vectDotProduct(diffVect1, diffVect1);
	dotP2 = vds_vectDotProduct(diffVect1, diffVect2);
	dotP4 = vds_vectDotProduct(diffVect1, diffVect3);
	
	dotP3 = vds_vectDotProduct(diffVect2, diffVect2);
	dotP5 = vds_vectDotProduct(diffVect2, diffVect3);

	equ1 = dotP2 * dotP2 - dotP1 * dotP3 ;
	equ2 = equ1 / (dotP1 * dotP3);

	double absProd2 = fabs(equ2);

	if(ZERO_TOL > absProd2 ) 
		return false;

	par1 = (dotP2 * dotP5 - dotP3 * dotP4) / equ1;
	par2 = (dotP1 * dotP5 - dotP2 * dotP4) / equ1;

	if(lineIntersectParam1 != NULL) 
		*lineIntersectParam1 = par1;
	
	if(lineIntersectParam2 != NULL) 
		*lineIntersectParam2 = par2;

	  // Get the shortest points on the 2 lines


	double mag;
	mag = vds_vectMagnitude(diffVect1);

	vds_vectNormalize(diffVect1);
	vds_vectScale(diffVect1,par1*mag);
	vds_vectAssign(shortPoint1,linePt1);
	vds_vectAdd(shortPoint1,diffVect1,shortPoint1);


	mag = vds_vectMagnitude(diffVect2);

	vds_vectNormalize(diffVect2);
	vds_vectScale(diffVect2,par2*mag);
	vds_vectAssign(shortPoint2,linePt3);
	vds_vectAdd(shortPoint2,diffVect2,shortPoint2);

	*shortDist = vds_vectDistance(shortPoint1, shortPoint2) ;

	return true;
}


/* 
	true - not parallel, all return values are valid
	false = parallel, only short dist is valid
  
*/

inline bool vds_FindTwoBoundedLinesDistance(double *linePt1, double *linePt2, double *linePt3, double *linePt4,double *shortDist,double *shortPoint1, double *shortPoint2)
{
	double lineParam1,lineParam2;

	if(!vds_FindLineLineDistance(linePt1,linePt2,linePt3,linePt4, &lineParam1,&lineParam2,shortDist,shortPoint1,shortPoint2))
	{

		double dist;
		double projPt[3];
		vds_ProjectPointOnBoundLine(linePt1,linePt3,linePt4,projPt);
		dist = vds_vectDistance(linePt1,projPt);

		*shortDist = dist;
		vds_vectAssign(shortPoint1, linePt1);
		vds_vectAssign(shortPoint2, projPt);

		vds_ProjectPointOnBoundLine(linePt2,linePt3,linePt4,projPt);
		dist = vds_vectDistance(linePt2,projPt);

		if(dist < *shortDist)
		{
			*shortDist = dist;
			vds_vectAssign(shortPoint1, linePt2);
			vds_vectAssign(shortPoint2, projPt);
		}


		vds_ProjectPointOnBoundLine(linePt3,linePt1,linePt2,projPt);
		dist = vds_vectDistance(linePt3,projPt);

		if(dist < *shortDist)
		{
			*shortDist = dist;
			vds_vectAssign(shortPoint1, projPt);
			vds_vectAssign(shortPoint2, linePt3);
		}

		vds_ProjectPointOnBoundLine(linePt4,linePt1,linePt2,projPt);
		dist = vds_vectDistance(linePt4,projPt);

		if(dist < *shortDist)
		{
			*shortDist = dist;
			vds_vectAssign(shortPoint1, projPt);
			vds_vectAssign(shortPoint2, linePt4);
		}

		return false;

	}
	else
	{
		
		if(!((lineParam1>=0 && lineParam1<=1) && 
			(lineParam2>=0 && lineParam2<=1)))
		{
			if(lineParam1>=1)
				vds_vectAssign(shortPoint1,linePt2);
			else if(lineParam1<=0) 
				vds_vectAssign(shortPoint1,linePt1);

			if(lineParam2>=1)
				vds_vectAssign(shortPoint2,linePt4);
			else if(lineParam2<=0) 
				vds_vectAssign(shortPoint2,linePt3);
		
			*shortDist = vds_vectDistance(shortPoint1,shortPoint2);
		}
		return true;
	}

	return false;
}


inline bool vds_FindLineTriIntersection(double *linePt1, double *linePt2, double *triPt1, 
							 double *triPt2, double *triPt3, double tol)
{

	if(vds_isPointOnPlane(linePt1,triPt1,triPt2,triPt3,tol) && 
		vds_isPointOnPlane(linePt2,triPt1,triPt2,triPt3,tol))
	{
		//ToDO
		if(vds_isPointOnTriangle(linePt1,triPt1,triPt2,triPt3,tol)
			|| vds_isPointOnTriangle(linePt2,triPt1,triPt2,triPt3,tol))
			return true;
		else
		{
			double lineTol;
			lineTol = (vds_vectDistance(linePt1,linePt2))*tol;

			double dist , shortDist, shortPoint1[3], shortPoint2[3];
			vds_FindTwoBoundedLinesDistance(linePt1,linePt2, triPt1,triPt2,&dist,shortPoint1,shortPoint2);
			shortDist = dist;

			vds_FindTwoBoundedLinesDistance(linePt1,linePt2, triPt2,triPt3,&dist,shortPoint1,shortPoint2);

			if(dist<shortDist)
				shortDist = dist;

			vds_FindTwoBoundedLinesDistance(linePt1,linePt2, triPt3,triPt1,&dist,shortPoint1,shortPoint2);
			
			if(dist<shortDist)
				shortDist = dist;

			if(shortDist<lineTol)
				return true;
			else
				return false;

		}
	}
	else
	{
		double retPt[3],param;

		if(!vds_FindPlaneLineIntersection_M1(linePt1,linePt2,triPt1,triPt2,triPt3,retPt,&param))
			return false;

		if(param>(1.0 + tol) || param<-tol)
			return false;

		
		if(vds_isPointOnTriangle( retPt, triPt1,triPt2,triPt3,tol))
			return true;
		else
			return false;
	}
}

inline bool vds_FindBoundedLineTriDistance(double *linePt1, double *linePt2, double *triPt1, double *triPt2, double *triPt3, 
										   double &distance, double *linePt, double *triPt)
{
	bool bDone = false;
//	int ptCode;
	double retPt[3], projPt1[3], projPt2[3], param;

	if(vds_FindPlaneLineIntersection_M1(linePt1,linePt2,triPt1,triPt2,triPt3,retPt,&param))
	{
		if(vds_isPointOnTriangle( retPt, triPt1,triPt2,triPt3,-1))
		{
			distance = 0;
			vds_vectAssign(triPt, retPt);

			vds_vectAssign(linePt, retPt);
			if(param <= 0) vds_vectAssign(linePt, linePt1);
			else if(param >= 1) vds_vectAssign(linePt, linePt2);
			
			distance = vds_vectDistance(linePt, triPt);
			bDone = true;
		}
	}
	
	if(!bDone)
	{
		vds_ProjectPointOnPlane(linePt1, triPt1, triPt2, triPt3, projPt1);
		vds_ProjectPointOnPlane(linePt2, triPt1, triPt2, triPt3, projPt2);
			
		if(vds_isPointOnTriangle(projPt1,triPt1,triPt2,triPt3,-1))
		{
			vds_vectAssign(linePt, linePt1);
			vds_vectAssign(triPt, projPt1);

			distance = vds_vectDistance(linePt, triPt);
		}
		else if(vds_isPointOnTriangle(projPt2,triPt1,triPt2,triPt3,-1))
		{
			vds_vectAssign(linePt, linePt2);
			vds_vectAssign(triPt, projPt2);

			distance = vds_vectDistance(linePt, triPt);
		}
		else
		{
			double dist , shortDist, shortPoint1[3], shortPoint2[3];
			
			vds_FindTwoBoundedLinesDistance(linePt1,linePt2, triPt1,triPt2,&dist,shortPoint1,shortPoint2);
			shortDist = dist;
			vds_vectAssign(linePt, shortPoint1);
			vds_vectAssign(triPt, shortPoint2);

			vds_FindTwoBoundedLinesDistance(linePt1,linePt2, triPt2,triPt3,&dist,shortPoint1,shortPoint2);

			if(dist < shortDist)
			{
				shortDist = dist;
				vds_vectAssign(linePt, shortPoint1);
				vds_vectAssign(triPt, shortPoint2);
			}

			vds_FindTwoBoundedLinesDistance(linePt1,linePt2, triPt3,triPt1,&dist,shortPoint1,shortPoint2);
			
			if(dist < shortDist)
			{
				shortDist = dist;
				vds_vectAssign(linePt, shortPoint1);
				vds_vectAssign(triPt, shortPoint2);
			}

			distance = vds_vectDistance(linePt, triPt);
		}
	}

	return true;
}



inline bool vds_FindTriTriIntersection(double *firstTPt1, double *firstTPt2,  double *firstTPt3,
									   double *secondTPt1, double *secondTPt2,  double *secondTPt3, double tol)
{

	if(vds_FindLineTriIntersection(firstTPt1,firstTPt2,secondTPt1, secondTPt2,secondTPt3,tol))
		return true;
	else if(vds_FindLineTriIntersection(firstTPt2,firstTPt3,secondTPt1, secondTPt2,secondTPt3,tol))
		return true;
	else if(vds_FindLineTriIntersection(firstTPt3,firstTPt1,secondTPt1, secondTPt2,secondTPt3,tol))
		return true;
	else if(vds_FindLineTriIntersection(secondTPt1,secondTPt2,firstTPt1, firstTPt2,firstTPt3,tol))
		return true;
	else if(vds_FindLineTriIntersection(secondTPt2,secondTPt3,firstTPt1, firstTPt2,firstTPt3,tol))
		return true;
	else if(vds_FindLineTriIntersection(secondTPt3,secondTPt1,firstTPt1, firstTPt2,firstTPt3,tol))
		return true;

	return false;
}

inline bool vds_FindTriTriIntersection_Sharing2Nodes(double *commonTPt1, double *commonTPt2,  double *OppTPt1,
									   double *OppTPt2, double angleTol)
{

	double vect1[3], vect2[3], normal1[3],normal2[3];

	vds_vectDiff(commonTPt1,OppTPt1,vect1);
	vds_vectNormalize(vect1);

	vds_vectDiff(commonTPt1,commonTPt2,vect2);
	vds_vectNormalize(vect2);

	vds_vectCrossProduct(vect1,vect2,normal1);
	vds_vectNormalize(normal1);



	vds_vectDiff(commonTPt1,commonTPt2,vect1);
	vds_vectNormalize(vect1);

	vds_vectDiff(commonTPt1,OppTPt2,vect2);
	vds_vectNormalize(vect2);


	vds_vectCrossProduct(vect1,vect2,normal2);
	vds_vectNormalize(normal2);



	if(vds_vectMagnitude(normal1)<=ZERO_TOL || vds_vectMagnitude(normal2)<=ZERO_TOL
			|| vds_vectAngle(normal1,normal2)>(180-angleTol))
		return true;
	else
		return false;


}


inline bool vds_FindTriTriIntersection_Sharing1Node(double *commonTPt, double *firstTPt1,  double *firstTPt2,
									   double *secondTPt1,double *secondTPt2, double tol)
{

	if(vds_FindLineTriIntersection(firstTPt1,firstTPt2,secondTPt1, secondTPt2,commonTPt,tol))
		return true;
	else if(vds_FindLineTriIntersection(secondTPt1,secondTPt2,firstTPt1, firstTPt2,commonTPt,tol))
		return true;

	return false;
}






static void Create3dView_TransMatrix(double modelMat[16], double projMat[16], int viewport[4], double transMatrix[16] ) 
{

    double projModelMultMatrix[16] ;



    projModelMultMatrix[0] = projMat[0]*modelMat[0] + projMat[4]*modelMat[1] + projMat[8] *modelMat[2];
    projModelMultMatrix[1] = projMat[1]*modelMat[0] + projMat[5]*modelMat[1] + projMat[9] *modelMat[2];
    projModelMultMatrix[2] = projMat[2]*modelMat[0] + projMat[6]*modelMat[1] + projMat[10]*modelMat[2];
   
    

    projModelMultMatrix[4] = projMat[0]*modelMat[4] + projMat[4]*modelMat[5] + projMat[8] *modelMat[6];
    projModelMultMatrix[5] = projMat[1]*modelMat[4] + projMat[5]*modelMat[5] + projMat[9] *modelMat[6];
    projModelMultMatrix[6] = projMat[2]*modelMat[4] + projMat[6]*modelMat[5] + projMat[10]*modelMat[6];
    
    

    projModelMultMatrix[8]  = projMat[0]*modelMat[8] + projMat[4]*modelMat[9] + projMat[8] *modelMat[10];
    projModelMultMatrix[9]  = projMat[1]*modelMat[8] + projMat[5]*modelMat[9] + projMat[9] *modelMat[10];
    projModelMultMatrix[10] = projMat[2]*modelMat[8] + projMat[6]*modelMat[9] + projMat[10]*modelMat[10];
    
    

    projModelMultMatrix[12] = projMat[0]*modelMat[12] + projMat[4]*modelMat[13] + projMat[8] *modelMat[14] + projMat[12]*modelMat[15] ;
    projModelMultMatrix[13] = projMat[1]*modelMat[12] + projMat[5]*modelMat[13] + projMat[9] *modelMat[14] + projMat[13]*modelMat[15] ;
    projModelMultMatrix[14] = projMat[2]*modelMat[12] + projMat[6]*modelMat[13] + projMat[10]*modelMat[14] + projMat[14]*modelMat[15] ;
    

	projModelMultMatrix[3]  = 0.0 ;
	projModelMultMatrix[7]  = 0.0 ;
	projModelMultMatrix[11] = 0.0 ;
	projModelMultMatrix[15] = 1.0 ;

    double vWidth =  (double)(viewport[2] - viewport[0])/(double)2.0;
    double vHeight =  (double)(viewport[3] - viewport[1])/(double)2.0;

    transMatrix[0] = vWidth * projModelMultMatrix[0] ;
    transMatrix[1] = vHeight * projModelMultMatrix[1] ;
    transMatrix[2] = projModelMultMatrix[2]/2.0 ;


    transMatrix[4] = vWidth * projModelMultMatrix[4] ;
    transMatrix[5] = vHeight * projModelMultMatrix[5] ;
    transMatrix[6] = projModelMultMatrix[6]/2.0 ;
    

    transMatrix[8]  = vWidth * projModelMultMatrix[8] ;
    transMatrix[9]  = vHeight * projModelMultMatrix[9] ;
    transMatrix[10] = projModelMultMatrix[10]/2.0 ;


    transMatrix[12] = vWidth * projModelMultMatrix[12] + viewport[0] + vWidth ;
    transMatrix[13] = vHeight * projModelMultMatrix[13] + viewport[1] + vHeight ;
    transMatrix[14] = (projModelMultMatrix[14]/2.0) + 0.5 ;

	transMatrix[11] = 0.0;
	transMatrix[7]  = 0.0;
	transMatrix[3]  = 0.0;
    transMatrix[15] = 1.0;
}


inline double FindRadius_From3Points(double *ptXYZ1,double *ptXYZ2, double *ptXYZ3)
{

	double len1,len2,len3;
	
	len1 = vds_vectDistance(ptXYZ1,ptXYZ2);
	len2 = vds_vectDistance(ptXYZ1,ptXYZ3);
	len3 = vds_vectDistance(ptXYZ2,ptXYZ3);

	double pMeter;
	pMeter = (len1 + len2 + len3)/2;

	double area,radius;
	area = sqrt(pMeter * (pMeter - len1) * (pMeter - len2) * (pMeter - len3));

	if(area!=0)
		radius = (len1 * len2 * len3) / (4 * area);
	else
		radius = DBL_MAX;

	return radius;
}

inline void RotatePoint_AboutXAxis(double *dSrcPt,double *dTransPt,double dRotAngle)
{
	double dTheta = dRotAngle*3.141592/180;
	
	dTransPt[1] = dSrcPt[1]*cos(dTheta) + dSrcPt[2]*sin(dTheta);
	dTransPt[2] = dSrcPt[2]*cos(dTheta) - dSrcPt[1]*sin(dTheta);
	dTransPt[0] = dSrcPt[0];
}

inline void RotatePoint_AboutYAxis(double *dSrcPt,double *dTransPt,double dRotAngle)
{
	double dTheta = dRotAngle*3.141592/180;
	
	dTransPt[0] = dSrcPt[0]*cos(dTheta) - dSrcPt[2]*sin(dTheta);
	dTransPt[2] = dSrcPt[2]*cos(dTheta) + dSrcPt[0]*sin(dTheta);
	dTransPt[1] = dSrcPt[1];
}

inline void RotatePoint_AboutZAxis(double *dSrcPt,double *dTransPt,double dRotAngle)
{
	double dTheta = dRotAngle*3.141592/180;
	
	dTransPt[0] = dSrcPt[0]*cos(dTheta) + dSrcPt[1]*sin(dTheta);
	dTransPt[1] = dSrcPt[1]*cos(dTheta) - dSrcPt[0]*sin(dTheta);
	dTransPt[2] = dSrcPt[2];
}

inline void RotatePoint_ByAxis(double *dSrcPt,double *dTransPt,double dRotAngle,double dRotAxis[3],double dRotCenter[3], bool bRightHanded)
{
	double dRotationMatrix[4][4];

	 /* formula

	 tX2 + c	tXY + sZ	tXZ - sY	0
 
	 tXY-sZ		tY2 + c		tYZ + sX	0
 
	 tXY + sY	tYZ - sX	tZ2 + c		0
 
	 0			0			0			1
 
	Where c = cos (theta), s = sin (theta), t = 1-cos (theta), and <X,Y,Z> is the unit vector representing the arbitary axis
	*/

	double t,c,s;
	t = 1-cos((dRotAngle*VDS_PI)/180);
	c = cos((dRotAngle*VDS_PI)/180);
	s = sin((dRotAngle*VDS_PI)/180);

	double X= dRotAxis[0],Y= dRotAxis[1],Z= dRotAxis[2];

	if(bRightHanded)
	{
		dRotationMatrix[0][0] = t*X*X + c;
		dRotationMatrix[0][1] = t*X*Y + s*Z;
		dRotationMatrix[0][2] = t*X*Z - s*Y;
		dRotationMatrix[0][3] = 0;

		dRotationMatrix[1][0] = t*X*Y-s*Z;
		dRotationMatrix[1][1] = t*Y*Y + c;
		dRotationMatrix[1][2] = t*Y*Z + s*X;
		dRotationMatrix[1][3] = 0;

		dRotationMatrix[2][0] = t*X*Y + s*Y;
		dRotationMatrix[2][1] = t*Y*Z - s*X;
		dRotationMatrix[2][2] = t*Z*Z + c;
		dRotationMatrix[2][3] = 0;


		dRotationMatrix[3][0] = 0;
		dRotationMatrix[3][1] = 0;
		dRotationMatrix[3][2] = 0;
		dRotationMatrix[3][3] = 1;
	}
	else
	{
		dRotationMatrix[0][0] = t*X*X + c;
		dRotationMatrix[0][1] = t*X*Y - s*Z;
		dRotationMatrix[0][2] = t*X*Z + s*Y;
		dRotationMatrix[0][3] = 0;

		dRotationMatrix[1][0] = t*X*Y +s*Z;
		dRotationMatrix[1][1] = t*Y*Y + c;
		dRotationMatrix[1][2] = t*Y*Z - s*X;
		dRotationMatrix[1][3] = 0;

		dRotationMatrix[2][0] = t*X*Y - s*Y;
		dRotationMatrix[2][1] = t*Y*Z + s*X;
		dRotationMatrix[2][2] = t*Z*Z + c;
		dRotationMatrix[2][3] = 0;


		dRotationMatrix[3][0] = 0;
		dRotationMatrix[3][1] = 0;
		dRotationMatrix[3][2] = 0;
		dRotationMatrix[3][3] = 1;
	}

	double tempPt[3];
	int i;
	for(i=0;i<3;i++)
		tempPt[i] = dSrcPt[i]-dRotCenter[i];

	for(i=0;i<3;i++)
	{
		dTransPt[i] = dRotationMatrix[0][i]*tempPt[0] + dRotationMatrix[1][i]*tempPt[1] + dRotationMatrix[2][i] *tempPt[2] + dRotationMatrix[3][i] ;
		dTransPt[i]+= dRotCenter[i];
	}

}
 
inline bool Find_Triangle_CircumCenter(double *triPt1,double *triPt2,double *triPt3,double *retCenter,double *retRadius)
{

	if(retRadius)
		*retRadius =0;

	double planeNormal[3];

	if(vds_vectArea(triPt1,triPt2,triPt3)==0)
		return false;

	vds_vectTriNormal(triPt1,triPt2,triPt3,planeNormal);

	
	double midPt1[3],midPt2[3];

	int i;

	for(i=0;i<3;i++)
	{
		midPt1[i] = (triPt2[i]+triPt1[i])/2;
		midPt2[i] = (triPt2[i]+triPt3[i])/2;
	}

	double perpPt1[3],perpPt2[3];
	

	RotatePoint_ByAxis(triPt2,perpPt1,90,planeNormal,midPt1,true);
	RotatePoint_ByAxis(triPt2,perpPt2,90,planeNormal,midPt2,false);


	double s1,s2,minDist,intersectPt1[3],intersectPt2[3];

	if(!vds_FindLineLineDistance(midPt1,perpPt1,midPt2,perpPt2,&s1,&s2,&minDist,intersectPt1,intersectPt2))
		return false;

	if(retCenter)
		vds_vectAssign(retCenter,intersectPt1);
	
	if(retRadius)
		*retRadius = vds_vectDistance(triPt1,intersectPt1);

	return true;

}

inline double vds_matrixDeterminent(int order, double *matrix)
{
	double mag = 0;

	if(order < 1)
	{
		mag = 0;
	}
	else if(order == 1)
	{
		mag = matrix[0];
	}
	else if(order == 2)
	{
		mag = matrix[0] * matrix[3] - matrix[1] * matrix[2]; 
	}
	else if(order == 3)
	{
		mag = matrix[0] * (matrix[4] * matrix[8] - matrix[5] * matrix[7]) -
			  matrix[1] * (matrix[3] * matrix[8] - matrix[5] * matrix[6]) +
			  matrix[2] * (matrix[3] * matrix[7] - matrix[4] * matrix[6]);
	}
	else
	{
		mag = 0;
	}

	return mag;
}

inline void vds_matrixMultiply(int r1, int c1, double *inMatrix1, int r2, int c2, double *inMatrix2, double *outMatrix)
{
	int r = 0, c = 0, k = 0, n = 0;
	double value = 0;

	if(c1 != r2)
	  return;

	n = 0;

	for(r = 0; r < r1; r++)
	{
		for(c = 0; c < c2; c++)
		{
			value = 0;

			for(k = 0; k < c1; k++)
			{
				value += inMatrix1[r * c1 + k] * inMatrix2[k * c2 + c];
			}

			outMatrix[n++] = value;
		}
	}
}

inline void vds_matrixInverse(int order, double *inMatrix, double *outMatrix)
{
	double det = 0, invDet = 0;

	if(order < 1)
	  return;

	det = vds_matrixDeterminent(order, inMatrix);

	if(det == 0)
	  return;

	invDet = 1/det;

	if(order == 1)
	{
		outMatrix[0] = invDet;
	}
	if(order == 2)
	{
		outMatrix[0] =  inMatrix[3] * invDet;
		outMatrix[1] = -inMatrix[1] * invDet;
		outMatrix[2] = -inMatrix[2] * invDet;
		outMatrix[3] =  inMatrix[0] * invDet;
	}
	else if(order == 3)
	{
		outMatrix[0] = (inMatrix[4] * inMatrix[8] - inMatrix[5] * inMatrix[7]) * invDet;
		outMatrix[1] = (inMatrix[2] * inMatrix[7] - inMatrix[1] * inMatrix[8]) * invDet;
		outMatrix[2] = (inMatrix[1] * inMatrix[5] - inMatrix[2] * inMatrix[4]) * invDet;
		outMatrix[3] = (inMatrix[5] * inMatrix[6] - inMatrix[3] * inMatrix[8]) * invDet;
		outMatrix[4] = (inMatrix[0] * inMatrix[8] - inMatrix[2] * inMatrix[6]) * invDet;
		outMatrix[5] = (inMatrix[2] * inMatrix[3] - inMatrix[0] * inMatrix[5]) * invDet;
		outMatrix[6] = (inMatrix[3] * inMatrix[7] - inMatrix[4] * inMatrix[6]) * invDet;
		outMatrix[7] = (inMatrix[1] * inMatrix[6] - inMatrix[0] * inMatrix[7]) * invDet;
		outMatrix[8] = (inMatrix[0] * inMatrix[4] - inMatrix[1] * inMatrix[3]) * invDet;
	}
	else
	{
	}
}

inline void vds_getRotationMatrix(double *axis, double angle, double *rotMatrix)
{
	double newAxisX[3], newAxisY[3], newAxisZ[3];
	double rMatrixX[9], transCoordMatrix[9], invTransCoordMatrix[9], tempMatrix[9];
	double angle_radian = 0;

	angle_radian = angle * VDS_PI / 180;

	newAxisX[0] = axis[0];
	newAxisX[1] = axis[1];
	newAxisX[2] = axis[2];

	if(newAxisX[0] >= newAxisX[1] && newAxisX[0] >= newAxisX[2])
	{
		newAxisY[0] = -(newAxisX[1] + newAxisX[2]);
		newAxisY[1] = newAxisX[0];
		newAxisY[2] = newAxisX[0];
	}
	else if(newAxisX[1] >= newAxisX[0] && newAxisX[1] >= newAxisX[2])
	{
		newAxisY[0] = newAxisX[1];
		newAxisY[1] = -(newAxisX[0] + newAxisX[2]);
		newAxisY[2] = newAxisX[1];
	}
	else
	{
		newAxisY[0] = newAxisX[2];
		newAxisY[1] = newAxisX[2];
		newAxisY[2] = -(newAxisX[0] + newAxisX[1]);
	}

	vds_vectCrossProduct(newAxisX, newAxisY, newAxisZ);

	vds_vectNormalize(newAxisX);
	vds_vectNormalize(newAxisY);
	vds_vectNormalize(newAxisZ);

	rMatrixX[0] = 1;
	rMatrixX[1] = 0;
	rMatrixX[2] = 0;
	rMatrixX[3] = 0;
	rMatrixX[4] = cos(angle_radian);
	rMatrixX[5] = sin(angle_radian);
	rMatrixX[6] = 0;
	rMatrixX[7] = -sin(angle_radian);
	rMatrixX[8] = cos(angle_radian);

	transCoordMatrix[0] = newAxisX[0];
	transCoordMatrix[1] = newAxisY[0];
	transCoordMatrix[2] = newAxisZ[0];
	transCoordMatrix[3] = newAxisX[1];
	transCoordMatrix[4] = newAxisY[1];
	transCoordMatrix[5] = newAxisZ[1];
	transCoordMatrix[6] = newAxisX[2];
	transCoordMatrix[7] = newAxisY[2];
	transCoordMatrix[8] = newAxisZ[2];
	
	vds_matrixInverse(3, transCoordMatrix, invTransCoordMatrix);

	double tempMatrix1[9];
	vds_matrixMultiply(3, 3, transCoordMatrix, 3, 3, invTransCoordMatrix, tempMatrix1);

	vds_matrixMultiply(3, 3, transCoordMatrix, 3, 3, rMatrixX, tempMatrix);
	vds_matrixMultiply(3, 3, tempMatrix, 3, 3, invTransCoordMatrix, rotMatrix);
}

inline void RotatePoint_ByAxis_1(double *dSrcPt,double *dTransPt,double dRotAngle,double dRotAxis[3],double dRotCenter[3], bool bRightHanded)
{
	double rotMatrix[9], pt[3];

	pt[0] = dSrcPt[0];
	pt[1] = dSrcPt[1];
	pt[2] = dSrcPt[2];

	pt[0] -= dRotCenter[0];
	pt[1] -= dRotCenter[1];
	pt[2] -= dRotCenter[2];

	vds_getRotationMatrix(dRotAxis, dRotAngle, rotMatrix);

	dTransPt[0] = rotMatrix[0] * pt[0] + rotMatrix[3] * pt[1] + rotMatrix[6] * pt[2];
	dTransPt[1] = rotMatrix[1] * pt[0] + rotMatrix[4] * pt[1] + rotMatrix[7] * pt[2];
	dTransPt[2] = rotMatrix[2] * pt[0] + rotMatrix[5] * pt[1] + rotMatrix[8] * pt[2];

	dTransPt[0] += dRotCenter[0];
	dTransPt[1] += dRotCenter[1];
	dTransPt[2] += dRotCenter[2];
}

inline bool vds_CircumCenterOfTriangle(double *triPt1, double *triPt2, double *triPt3, double *circumCenter, double *radius)
{
	int i = 0;
	double matrix[9], matrix2[3], topMatrix[9];
	double center[3] = {0, 0, 0};
	double x2x1, y2y1, z2z1, x3x1, y3y1, z3z1;
	double x1y1z1, x2y2z2, x3y3z3, v1, v2, v3;
	double topMag = 0, bottomMag = 0;

	x2x1 = triPt2[0] - triPt1[0];
	y2y1 = triPt2[1] - triPt1[1];
	z2z1 = triPt2[2] - triPt1[2];

	x3x1 = triPt3[0] - triPt1[0];
	y3y1 = triPt3[1] - triPt1[1];
	z3z1 = triPt3[2] - triPt1[2];

	x1y1z1 = triPt1[0] * triPt1[0] + triPt1[1] * triPt1[1] + triPt1[2] * triPt1[2];
	x2y2z2 = triPt2[0] * triPt2[0] + triPt2[1] * triPt2[1] + triPt2[2] * triPt2[2];
	x3y3z3 = triPt3[0] * triPt3[0] + triPt3[1] * triPt3[1] + triPt3[2] * triPt3[2];

	v1 = y2y1 * z3z1 - y3y1 * z2z1;
	v2 = x2x1 * z3z1 - x3x1 * z2z1;
	v3 = x2x1 * y3y1 - x3x1 * y2y1;

	matrix[0] = 2 * x2x1;
	matrix[1] = 2 * y2y1;
	matrix[2] = 2 * z2z1;
	matrix[3] = 2 * x3x1;
	matrix[4] = 2 * y3y1;
	matrix[5] = 2 * z3z1;
	matrix[6] = v1;
	matrix[7] = v2;
	matrix[8] = v3;

	matrix2[0] = x2y2z2 - x1y1z1;
	matrix2[1] = x3y3z3 - x1y1z1;
	matrix2[2] = triPt1[0] * v1 - triPt1[1] * v2 + triPt1[2] * v3;

	bottomMag = vds_matrixDeterminent(3, matrix);
	if(bottomMag == 0.0)
	  return false;

	for(i = 0; i < 9; i++)
	  topMatrix[i] = matrix[i];

	topMatrix[0] = matrix2[0];
	topMatrix[3] = matrix2[1];
	topMatrix[6] = matrix2[2];

	topMag = vds_matrixDeterminent(3, topMatrix);
	center[0] = topMag/bottomMag;

	for(i = 0; i < 9; i++)
	  topMatrix[i] = matrix[i];

	topMatrix[1] = matrix2[0];
	topMatrix[3] = matrix2[1];
	topMatrix[7] = matrix2[2];

	topMag = vds_matrixDeterminent(3, topMatrix);
	center[1] = topMag/bottomMag;

	for(i = 0; i < 9; i++)
	  topMatrix[i] = matrix[i];

	topMatrix[2] = matrix2[0];
	topMatrix[5] = matrix2[1];
	topMatrix[8] = matrix2[2];

	topMag = vds_matrixDeterminent(3, topMatrix);
	center[2] = topMag/bottomMag;

	if(circumCenter != NULL)
	{
		circumCenter[0] = center[0];
		circumCenter[1] = center[1];
		circumCenter[2] = center[2];
	}

	if(radius != NULL)
	  *radius = vds_vectDistance(center, triPt1);
}

inline double vds_PlanePointDistance(double *pt, double *planePt1, double *planePt2, double *planePt3)
{
	double dist = DBL_MAX, projPt[3];
	
	vds_ProjectPointOnPlane(pt, planePt1, planePt2, planePt3, projPt);
	dist = vds_vectDistance(pt, projPt);

	return dist;
}

inline void getMatrixFromOuler(double * matrix, double * ouler)
{
	matrix[0] = (ouler[0]*ouler[0] + ouler[1]*ouler[1] - 0.5) * 2.0;
	matrix[1] = (ouler[1]*ouler[2] + ouler[0]*ouler[3] ) * 2.0;
	matrix[2] = (ouler[1]*ouler[3] - ouler[0]*ouler[2] ) * 2.0;
	matrix[3] = 0.0;
	
	matrix[4] = (ouler[1]*ouler[2] - ouler[0]*ouler[3] ) * 2.0;
	matrix[5] = (ouler[0]*ouler[0] + ouler[2]*ouler[2] - 0.5) * 2.0;
	matrix[6] = (ouler[2]*ouler[3] + ouler[0]*ouler[1] ) * 2.0;
	matrix[7] = 0.0;

	matrix[8] = (ouler[1]*ouler[3] + ouler[0]*ouler[2] ) * 2.0;
	matrix[9] = (ouler[2]*ouler[3] - ouler[0]*ouler[1] ) * 2.0;
	matrix[10] = (ouler[0]*ouler[0] + ouler[3]*ouler[3] - 0.5) * 2.0;
	matrix[11] = 0.0;

	matrix[12] = 0.0;
	matrix[13] = 0.0;
	matrix[14] = 0.0;
	matrix[15] = 1.0;
}

#endif