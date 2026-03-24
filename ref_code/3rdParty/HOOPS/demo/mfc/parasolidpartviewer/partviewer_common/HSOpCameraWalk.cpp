// HSOpCameraWalk.cpp : implementation of the HSOpCameraPan class
//

#include "stdafx.h"
 
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HSOpCameraWalk.h"
#include "HConstantFramerate.h"
#include "HTools.h"
#include "HEventInfo.h"
#include "HEventManager.h"
#include "HUtility.h"

#include "hc.h"
#include "HTManager.h"
#include "HDB.h"

#define SPEED 15.0f
/////////////////////////////////////////////////////////////////////////////
// HSOpCameraWalk
//
// Operator for walking in a scene.  
// 
//
// Left button down - initiates free viewing in all directions with mouse movement
//
// Left + Right Mouse button - movement in view direction (reversed by pressing shift)
// 


// timer callback to say walk further
bool HSOpCameraWalk::WalkTimerClbk(float request_time, float actual_time, void * user_data)
{

	HSOpCameraWalk* op = (HSOpCameraWalk*) user_data;
	op->OnWalk(request_time, actual_time);
	return true;
}

HSOpCameraWalk::HSOpCameraWalk(HBaseView* view, int DoRepeat,int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{
    
    
    m_AxisMode = HUtility::CalculateMajorAxis(view);
    m_time = HUtility::GetTime();
    
    
    //	if (!m_pWalkTimer)
    m_pWalkTimer = new HTClient( 0.01f, HTCS_PeriodicSkip, WalkTimerClbk, this );
    HDB::GetHTManager()->RegisterClient( m_pWalkTimer );
     m_max_world_extent = 0.0f;
    
    m_rotate = 0;
    m_move = 0;
    m_tilt = 0;
    m_updown = 0;
    m_strafe = 0;
    
    HPoint t,p,delta;
    
    HC_Open_Segment_By_Key(GetView()->GetSceneKey());
    HC_Show_Net_Camera_Target (&t.x, &t.y, &t.z);
    HC_Show_Net_Camera_Position (&p.x, &p.y, &p.z);
    HC_Close_Segment();
    delta.Set(t.x- p.x, t.y - p.y, t.z - p.z);
    float l1 = (float)HC_Compute_Vector_Length(&delta);
    if (m_AxisMode == 2)
	delta.Set(delta.x, delta.y, 0);
    else if (m_AxisMode == 1)
	delta.Set(0, delta.y, delta.z);
    else 
	delta.Set(delta.x, 0, delta.z);

    float l2 = (float)HC_Compute_Vector_Length(&delta);
    float deg = (float)acos(l2/l1) * (180.0f/3.1415927f);
    
    ResetPosition();
    
    switch (m_AxisMode)
    {
	case 2:
 	 p.z > t.z ? m_tilt = -deg : m_tilt = deg; 
	 break;

	case 1:
 	 p.x > t.x ? m_tilt = -deg : m_tilt = deg; 
	 break;
	case 0:
 	 p.y > t.y ? m_tilt = -deg : m_tilt = deg; 
	 break;
    }

    doOnce = false;                  
    CalculateExtents();
    
}

HSOpCameraWalk::~HSOpCameraWalk()
{
		// get rid of the timer
	if( m_pWalkTimer )
	{
		HDB::GetHTManager()->UnRegisterClient( m_pWalkTimer );
		delete m_pWalkTimer;
		m_pWalkTimer = 0;
	}
}


HBaseOperator * HSOpCameraWalk::Clone()
{
	return (HBaseOperator *)new HSOpCameraWalk(GetView());
}


 
const char * HSOpCameraWalk::GetName() { return "HOpCameraWalk"; }


void HSOpCameraWalk::CalculateExtents()
{

	HC_Open_Segment_By_Key (GetView()->GetSceneKey());		
		HC_Show_Net_Camera_Target (&target.x, &target.y, &target.z);
		HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
		HC_Show_Net_Camera_Up_Vector (&up.x, &up.y, &up.z);
	HC_Close_Segment();

	HPoint min_world_corner;
	HPoint max_world_corner;
	HPoint world_extents;

	//we determine the size of the bounding box to make an educated guess on the step interval for
	//the forward movement

	// set some defaults in case no geometry is in the scene
	min_world_corner.Set(0.1f, 0.1f, 0.1f);
	max_world_corner.Set(-0.1f, -0.1f, -0.1f);
	
	// set the max world extent for use when moving the camera
	m_max_world_extent = 0.0f;

	HC_Open_Segment_By_Key(GetView()->GetViewKey());
	  HC_Compute_Circumcuboid(".", &min_world_corner, &max_world_corner);
	HC_Close_Segment();
	float dist;

	//we also take the distance to the scene into account
	HPoint middle;
	middle.x = (min_world_corner.x + max_world_corner.x)/2;
	middle.y = (min_world_corner.y + max_world_corner.y)/2;
	middle.z = (min_world_corner.z + max_world_corner.z)/2;
	dist = (float)sqrt((middle.x-camera.x)*(middle.x-camera.x)+(middle.y-camera.y)*(middle.y-camera.y)+
		(middle.z-camera.z)*(middle.z-camera.z));

	world_extents.x = max_world_corner.x - min_world_corner.x;
 	if (world_extents.x > m_max_world_extent)
		m_max_world_extent = world_extents.x;

	world_extents.y = max_world_corner.y - min_world_corner.y;
 	if (world_extents.y > m_max_world_extent)
		m_max_world_extent = world_extents.y;

	world_extents.z = max_world_corner.z - min_world_corner.z;
 	if (world_extents.z > m_max_world_extent)
		m_max_world_extent = world_extents.z;
	if (dist>m_max_world_extent)
		m_max_world_extent = dist;

}
 
int HSOpCameraWalk::OnLButtonDown(HEventInfo &event)
{
    if (!OperatorStarted()) 
    {
		if (!doOnce)
		{
			doOnce = true;
			GetView()->GetEventManager()->UnRegisterHandler((HMouseListener *)this, HMouseListener::GetType());
   			GetView()->GetEventManager()->RegisterHandler((HMouseListener *)this, HMouseListener::GetType(), HLISTENER_PRIORITY_HIGH + 10);	    
		}
		
 		if (m_max_world_extent == 0.0f)
		{
			// world extents do not exist, don't bother moving the viewpoint.
			return -1;
		}
    }
	
	SetOperatorStarted(true);
    SetNewPoint(event.GetMouseWindowPos()); 
    SetFirstPoint(GetNewPoint());

    return (HOP_OK);
}

 

 
int HSOpCameraWalk::OnLButtonDownAndMove(HEventInfo &event)
{
	if (!OperatorStarted())
		return HBaseOperator::OnLButtonDownAndMove(event);

    SetNewPoint(event.GetMouseWindowPos());  
										
    HPoint const delta(GetNewPoint() - GetFirstPoint());
 
    if (fabs(delta.x) < 0.005f)
		m_rotate = 0;
    else
		m_rotate = delta.x;

    if (fabs(delta.y) < 0.005f)
		m_move = 0;
    else
		m_move = delta.y;

     return (HOP_OK);
}





int HSOpCameraWalk::OnLButtonUp(HEventInfo &event)
{
    if(!OperatorStarted())
		return HBaseOperator::OnLButtonUp(event);
    GetView()->CameraPositionChanged();
    SetOperatorStarted(false);
    m_rotate = 0;
    m_move = 0;
    return(HOP_READY);
}

//the timer function kills the platform independency of course...
void HSOpCameraWalk::OnWalk(float requested_time, float actual_time)
{
	static bool first = true;
	double time_diff;	
	unsigned char state[256];

	if (OperatorStarted() || m_bChange)
	{
		if (first)
		{
			m_time = HUtility::GetTime();
			first = false;
		}
		time_diff = HUtility::GetTime() - m_time;
		// bump up "time diff" in case the button just went down;
		// we don't want to wait to start moving the camera.
		if (time_diff < .01f)
			time_diff = .01f;

		m_time = HUtility::GetTime();

		HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
 			GetKeyboardState(state);
			ResetPosition();
			
			if (fabs(m_move) > 0 && OperatorStarted())
				HC_Dolly_Camera(0.0,0.0,(m_move*time_diff * m_max_world_extent/4.0f));
			
			ResetPosition();

			if (fabs(m_updown) > 0 && OperatorStarted())
				HC_Dolly_Camera(0.0,(m_updown*time_diff * m_max_world_extent/4.0f), 0.0);

			if (fabs(m_strafe) > 0 && OperatorStarted())
				HC_Dolly_Camera((-m_strafe*time_diff * m_max_world_extent/4.0f), 0.0, 0.0);

 			HC_Pan_Camera(0.0f,m_tilt);

			if (OperatorStarted())
  				HC_Pan_Camera(-m_rotate*1.5f,0);

			HC_Show_Net_Camera_Target (&target.x, &target.y, &target.z);
			HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
			HC_Show_Net_Camera_Up_Vector (&up.x, &up.y, &up.z);
		}HC_Close_Segment();

		if (OperatorStarted() || m_bChange)
		{
			m_bChange = false;
			GetView()->CameraPositionChanged();
  			GetView()->Update();
		}
	}
}
 


void HSOpCameraWalk::ResetPosition()
{
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
		HPoint t,p,u;
		HC_Show_Net_Camera_Target (&t.x, &t.y, &t.z);
		HC_Show_Net_Camera_Position (&p.x, &p.y, &p.z);
		HC_Show_Net_Camera_Up_Vector (&u.x, &u.y, &u.z);
	 
		HPoint d(t - p);
		float length = (float)HC_Compute_Vector_Length(&d);
		switch (m_AxisMode)
		{
		case 0: d.Set(d.x, 0, d.z); break;
		case 1: d.Set(0, d.y, d.z); break;
		case 2: d.Set(d.x, d.y,  0); break;
		}
		
		HC_Compute_Normalized_Vector(&d, &d);

		HC_Set_Camera_Target(p.x + length * d.x, p.y + length * d.y, p.z + length * d.z);
		switch (m_AxisMode)
		{
		case 0: HC_Set_Camera_Up_Vector(0, 1, 0); break;
		case 1: HC_Set_Camera_Up_Vector(1, 0, 0); break;
		case 2: HC_Set_Camera_Up_Vector(0, 0, 1); break;
		}
	}HC_Close_Segment();
}


void HSOpCameraWalk::Level()
{
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
		HPoint t,p;
		HC_Show_Net_Camera_Target (&t.x, &t.y, &t.z);
		HC_Show_Net_Camera_Position (&p.x, &p.y, &p.z);
		switch (m_AxisMode)
		{
			case 0: 
				HC_Set_Camera_Position(p.x, 0, p.z);
				HC_Set_Camera_Target(t.x, t.y - p.y, t.z);
				break;
			case 1: 
				HC_Set_Camera_Position(0, p.y, p.z);
				HC_Set_Camera_Target(t.x - p.x,t.y, t.z);
				break;
			case 2: 
				HC_Set_Camera_Position(p.x, p.y, 0);
				HC_Set_Camera_Target(t.x ,t.y, t.z - p.z);
				break;
		}
	}HC_Close_Segment();	
	m_rotate=0;
	m_move=0;		
}

 
int HSOpCameraWalk::OnMouseWheel(HEventInfo &event)
{
    if (!OperatorStarted())
    {
	    int tick = event.GetMouseWheelDelta();
		if (tick>0)
			m_tilt+=5;
		else
			m_tilt-=5;
		m_bChange = true;
    }

	return HLISTENER_CONSUME_EVENT;
}



int HSOpCameraWalk::OnMButtonDown(HEventInfo &event)
{
    return (OnLButtonDown(event));
}

int HSOpCameraWalk::OnMButtonDownAndMove(HEventInfo &event)
{
	if (!OperatorStarted())
		return HBaseOperator::OnMButtonDownAndMove(event);

    SetNewPoint(event.GetMouseWindowPos());  

	HPoint delta(GetNewPoint() - GetFirstPoint());

	if (fabs(delta.y) < 0.005f)
		m_updown = 0;
    else
		m_updown = delta.y;

	if (fabs(delta.x) < 0.005f)
		m_strafe = 0;
    else
		m_strafe=(delta.x);
	
	return (HOP_OK);
}


int HSOpCameraWalk::OnMButtonUp(HEventInfo &event)
{
    m_updown = 0;
    m_strafe = 0;
	GetView()->CameraPositionChanged();

    return (OnLButtonUp(event));
}
