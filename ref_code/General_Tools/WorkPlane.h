// WorkPlane.h: interface for the CWorkPlane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKPLANE_H__5FB4DBE6_DD65_4005_8F4E_CDBD81FF8A9A__INCLUDED_)
#define AFX_WORKPLANE_H__5FB4DBE6_DD65_4005_8F4E_CDBD81FF8A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "global_data.h"
#include "type_def.h"
#include "Vds_Core_Def.h"

class CWorkPlane  
{
public:
	CWorkPlane();
	virtual ~CWorkPlane();

public:
	void Initail();		
	void SetCoord( LOC_COORD coord );
	void SetCoord3P( double origin[3], double point1[3], double point2[3], int type, int iopt=1 );
	void OffsetCoord( double offX, double offY, double offZ );
	void RotateCoord( double angleX, double angleY, double angleZ );		
	void GlobalToLocal( double fGlobal[3], double fLocal[3] );
	void LocalToGlobal( double fLocal[3], double fGlobal[3] );
	LOC_COORD * GetCoord()
	{
		return &m_WorkPlaneCoord;
	}
	
	SNAP_DEF * GetSnapDef()
	{
		return &m_snapdef;
	}
	void SetSnapDef(SNAP_DEF snapdef)
	{
		m_snapdef = snapdef;
	}
	void GetRange( float range[6] );
		
private:
	LOC_COORD m_WorkPlaneCoord;
	SNAP_DEF m_snapdef;	
	
};

#endif // !defined(AFX_WORKPLANE_H__5FB4DBE6_DD65_4005_8F4E_CDBD81FF8A9A__INCLUDED_)
