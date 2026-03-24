//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HOpCameraRelativeOrbit.cpp,v 1.16 2010-10-28 23:32:02 simon Exp $
//

// HOpCameraRelativeOrbit.cpp : implementation of the HOpCameraRelativeOrbit class
//


#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HOpCameraRelativeOrbit.h"
#include "HOpCameraOrbit.h"

#include "HTools.h"
#include "HUtility.h"
#include "hc.h"

#include <math.h>
#include <string.h>

#define ACCEL 3.0f

/////////////////////////////////////////////////////////////////////////////
// HOpCameraRelativeOrbit
//
// Operator for orbiting the scene's camera based on the user dragging the mouse
// with the left button down
//
// Left button down - find first position and bounds object with box
//
// Mouse motion while down - orbits camera based on mouse movement by mapping 
// the drag vector onto a virtual sphere and determine the corresponding orbit
// parameters
//
// Mouse up - removes object bounding box

HOpCameraRelativeOrbit::HOpCameraRelativeOrbit(HBaseView* view, int DoRepeat,int DoCapture) : HOpCameraOrbit(view, DoRepeat, DoCapture)
{

    m_bCenterSet = false;
}

HOpCameraRelativeOrbit::~HOpCameraRelativeOrbit()
{
}


HBaseOperator * HOpCameraRelativeOrbit::Clone()
{
	return (HBaseOperator *)new HOpCameraRelativeOrbit(GetView());
}


 
const char * HOpCameraRelativeOrbit::GetName() { return "HOpCameraRelativeOrbit"; }




int HOpCameraRelativeOrbit::OnLButtonDown(HEventInfo &event)
{
    float tmp,vl;
    HPoint min, max;
    
    if (!OperatorStarted()) 
		SetOperatorStarted(true);
    
    if (m_bSceneBoundingBoxVis)
    {
		// draw a bounding box
		
		HC_Open_Segment_By_Key(GetView()->GetModel()->GetModelKey());
		HC_Compute_Circumcuboid (".", &min, &max);	
		HC_Close_Segment();
		
		HC_Open_Segment_By_Key (GetView()->GetBBoxGeometryKey());
		HC_Flush_Geometry (".");
		HUtility::InsertBox (&max, &min);
		HC_Close_Segment ();
		
		GetView()->Update();
    }
    HPoint new_pos = event.GetMouseWindowPos();
    
    if (!m_bCenterSet)
    {
		int res;
		HPoint window, world;
		world.Set(0,0,0);
		HC_Open_Segment_By_Key(GetView()->GetViewKey());
			HViewSelectionLevel lvl = GetView()->GetViewSelectionLevel();
			GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
			res = HC_Compute_Selection(".", "./scene/overwrite","v", new_pos.x, new_pos.y);
			GetView()->SetViewSelectionLevel(lvl);
		HC_Close_Segment();
		// compute the selection using the HOOPS window coordinate ofthe the pick location
		if (res > 0)
		{
			do {
				HC_KEY key;
				HC_Show_Selection_Element (&key, 0, 0, 0);
				HC_Show_Selection_Position (&window.x, &window.y, &window.z, &world.x, &world.y, &world.z);			
			} while (HC_Find_Related_Selection());
		}

		if (!res)
		{
			HCamera mycamera;
			GetView()->GetCamera(&mycamera);
			world = mycamera.target;
		}
		m_ptCentroid = world;
    }
	
	// read mouse position
	SetFirstPoint(event.GetMouseWindowPos());
	if (GetView()->GetHandedness() == HandednessRight){
		HPoint tmp = GetFirstPoint();
		tmp.x = -tmp.x;
		SetFirstPoint(tmp);
	}
	HPoint wcenter;
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
		HC_Compute_Coordinates(".","world",&m_ptCentroid,"outer window",&wcenter);
		SetFirstPoint(GetFirstPoint() - wcenter);
	}HC_Close_Segment();
	
	// remember screen mouse position
	m_ptRealOld.x = GetFirstPoint().x;
	m_ptRealOld.y = GetFirstPoint().y;
	
	// map screen mouse points to sphere mouse points
	tmp = (GetFirstPoint().x * GetFirstPoint().x + GetFirstPoint().y * GetFirstPoint().y);
	vl = (float)sqrt(tmp);

	HPoint first_point = GetFirstPoint();
	if (tmp > 4.0f) 
	{
		first_point.x /= vl;
		first_point.y /= vl;
		first_point.z = 0.0;
	}
	else
		first_point.z = (float) sqrt (4.0f - tmp);
	SetFirstPoint(first_point);

	GetView()->PrepareForCameraChange();
	
	return (HOP_OK);
}




/*!
	OnLButtonDownAndMove records points as the mouse is moved, maps the points to spherical coordinates, and calculates 
	the appropriate values for HC_Orbit_Camera and HC_Roll_Camera.  It also updates the position of the default light, depending on the 
	state of SetLightFollowsCamera.   
	\param event An HEventInfo object containing information about the current event.
	\return An integer value indicating success or failure.
*/
int HOpCameraRelativeOrbit::OnLButtonDownAndMove(HEventInfo &event)
{
	HPoint axis, vtmp, m_real_new;	
	float theta, dist, tmp, vl;
 	if (!OperatorStarted()) return HBaseOperator::OnLButtonDownAndMove(event);

	GetView()->SetViewMode(HViewUnknown);
  
//	GetView()->SetHandedness(HandednessLeft);
	// read mouse position
	SetNewPoint(event.GetMouseWindowPos());
	if (GetView()->GetHandedness() == HandednessRight){
		HPoint tmp = GetNewPoint();
		tmp.x = -tmp.x;
		SetNewPoint(tmp);
	}

	HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
		HPoint wcenter;
		HC_Compute_Coordinates(".","world",&m_ptCentroid,"outer window",&wcenter);
		HPoint tmp2(GetNewPoint().x - wcenter.x,GetNewPoint().y - wcenter.y, 0);
		SetNewPoint(tmp2);
	}HC_Close_Segment();
  	
	// remember the real mouse positions
	m_real_new.x = GetNewPoint().x;
	m_real_new.y = GetNewPoint().y;

	// map screen mouse points to sphere mouse points
	tmp = GetNewPoint().x * GetNewPoint().x + GetNewPoint().y * GetNewPoint().y;
	vl = (float)sqrt(tmp);

	HPoint new_point = GetNewPoint();
 	if (tmp > 4.0f) 
	{
		new_point.x /= vl;
		new_point.y /= vl;
		new_point.z = 0.0f;
	}
	else
		new_point.z = (float)sqrt(4.0f - tmp);
	SetNewPoint(new_point);

	float rmat[4*4];
	HPoint fp2,np2,fp,np;
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
		HPoint n,m,u,t;
		t.Set(0,0,0);
 		HC_Show_Net_Camera_Position(&n.x,&n.y,&n.z);
		HC_Show_Net_Camera_Target(&m.x,&m.y,&m.z);
 		HC_Show_Net_Camera_Up_Vector(&u.x,&u.y,&u.z);

		HUtility::GetMatrixFromCamera(m,n,u,t, rmat);
	
		fp = GetFirstPoint();
		np = GetNewPoint();
  		HC_Compute_Transformed_Points(1,&fp,rmat,&fp2);
  		HC_Compute_Transformed_Points(1,&np,rmat,&np2);
	}HC_Close_Segment();

	// get the axis of rotation
	HC_Compute_Cross_Product (&fp2, &np2, &axis);
	
	// this is for screen mouse based movement
	vtmp.x = m_real_new.x - m_ptRealOld.x;
	vtmp.y = m_real_new.y - m_ptRealOld.y;
	dist = (float)sqrt(vtmp.x * vtmp.x + vtmp.y * vtmp.y) * 90.0f;
	
	if ((axis.x != 0.0 || axis.y != 0.0 || axis.z != 0)){
 
 
		HC_Compute_Normalized_Vector(&axis, &axis);

		HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
		

 			// project axis of rotation onto yz plane 
			vtmp.x = 0.0;
			vtmp.y = axis.y;
			vtmp.z = axis.z;

			// calculate angle of x orbit
			tmp = (float)HC_Compute_Dot_Product(&axis, &vtmp);
			if(fabs(tmp) > 1.001f || fabs(tmp) < 0.999f)		
				theta = (float)H_ACOS(tmp);
			else
				theta = 0.0f;

		
			if (axis.x < 0.0)
				m_Angle2= -theta * dist * ACCEL;
			else
				m_Angle2=theta * dist * ACCEL;
			
			// project axis of rotation onto xz plane 
			vtmp.x = axis.x;
			vtmp.y = 0.0;
			vtmp.z = axis.z;

			// calculate angle of y orbit
			tmp = (float)HC_Compute_Dot_Product(&axis, &vtmp);
			if (fabs(tmp) > 1.001f || fabs(tmp) < 0.999f)		
				theta = (float)H_ACOS(tmp);
			else
				theta = 0.0f;
			
			if (axis.y < 0.0)
				m_Angle1=theta * dist * ACCEL;
			else
				m_Angle1=-theta * dist * ACCEL;
		
			// project axis of rotation onto xy plane 
			vtmp.x = axis.x;
			vtmp.y = axis.y;
			vtmp.z = 0.0;

			// calculate angle of z orbit
			tmp = (float)HC_Compute_Dot_Product(&axis, &vtmp);
			if(fabs(tmp) > 1.001f || fabs(tmp) < 0.999f)		
				theta = (float)H_ACOS(tmp);
			else
				theta = 0.0f;

			if (axis.z < 0.0)
				m_Angle3=theta * dist*ACCEL;
			else
				m_Angle3=-theta * dist*ACCEL;
 
			HPoint p[4];
			float dummy;
			char text[MVO_BUFFER_SIZE];
			
			HC_Show_Net_Camera(&p[0],&p[1],&p[2],&dummy,&dummy,text);
			p[3].Set(0,0,0);
			
 			HC_Compute_Offcenter_Rotation(m_Angle2,-m_Angle1, -m_Angle3,
				m_ptCentroid.x,m_ptCentroid.y,m_ptCentroid.z,rmat);

    		HC_Compute_Transformed_Points(4,p,rmat,p);

  			p[2].Add(-p[3].x,-p[3].y,-p[3].z); 
 			
			HC_Set_Camera_Position(p[0].x,p[0].y,p[0].z);
 			HC_Set_Camera_Target(p[1].x,p[1].y,p[1].z);
 			HC_Set_Camera_Up_Vector(p[2].x,p[2].y,p[2].z);


		}HC_Close_Segment();
 		// update default light
		GetView()->CameraPositionChanged();

	}
	else
	{
		GetView()->CameraPositionChanged();
	}


	// update sphere space mouse
	SetFirstPoint(GetNewPoint());
	// update screen space mouse
	m_ptRealOld.x = m_real_new.x;
	m_ptRealOld.y = m_real_new.y;
	
	GetView()->Update();
	return (HOP_OK);
}

