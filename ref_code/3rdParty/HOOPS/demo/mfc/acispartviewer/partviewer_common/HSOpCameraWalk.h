// HOpCameraPan.h : interface of the HOpCameraPan class
// pans the camera of current view

#ifndef _HSOPCAMERAWALK_H
#define _HSOPCAMERAWALK_H

#include "HTools.h"
#include "HBaseOperator.h"
class HTClient;

class    HSOpCameraWalk : public HBaseOperator
{
public:
    HSOpCameraWalk(HBaseView* view, int DoRepeat=0, int DoCapture=1);
	~HSOpCameraWalk();

 	const char * GetName();

    int OnLButtonDown (HEventInfo &event);
	int OnLButtonDownAndMove(HEventInfo &event);
    int OnLButtonUp (HEventInfo &event);

	void SetLightFollowsCamera(bool follow){m_LightFollowsCamera = follow;};
	bool GetLightFollowsCamera(){return m_LightFollowsCamera;};
 // 	int	 OnRButtonDownAndMove(HEventInfo &event);
	int OnMouseWheel(HEventInfo &event);
	int OnMButtonDown(HEventInfo &event);
	int OnMButtonDownAndMove(HEventInfo &event);
	int OnMButtonUp(HEventInfo &event); 	
	void ResetPosition();
	void Level();
 
	HBaseOperator * Clone();
	HTClient*			m_pWalkTimer;
	void	 OnWalk(float requested_time, float actual_time); 
	void CalculateExtents();
 
	static bool WalkTimerClbk(float request_time, float actual_time, void * user_data);

private:
	bool	m_LightFollowsCamera;
	HPoint camera,target, up;
 	float		m_time;
	unsigned	m_timer;
	double		m_max_world_extent;
	float		m_alpha;
	float		m_beta;
	float		m_rotate, m_move, m_tilt, m_updown, m_strafe;
	bool m_walkmode;
	int m_AxisMode;
	bool m_bChange;
	bool doOnce;
    
	
};

#endif
