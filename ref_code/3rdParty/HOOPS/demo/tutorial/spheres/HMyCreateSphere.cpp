#include <math.h>
#include <stdlib.h>
#include <string.h>
 
#include "HTools.h"
#include "HBaseView.h"
#include "HEventInfo.h"
#include "HMyCreateSphere.h"
#include "HUtilityGeometryCreation.h"


HMyCreateSphere::HMyCreateSphere(HBaseView* view, int DoRepeat, int DoCapture, int NumSides) : HOpCreateSphere(view, DoRepeat, DoCapture)
{
	m_NumSides = NumSides;
}


HBaseOperator * HMyCreateSphere::Clone()
{
	return (HBaseOperator *)new HMyCreateSphere(m_pView);
}


const char * HMyCreateSphere::GetName() { return "HMyCreateSphere"; }

/////////////////////////////////////////////////////////////////////////////
// HOpCreateSphere message handlers




int HMyCreateSphere::OnLButtonUp(HEventInfo &event)
{
    // Mouse has come up 
	if(!m_bOpStarted) 
		return HBaseOperator::OnLButtonDownAndMove(event);

	m_bOpStarted = false;

	m_ptNew = event.GetMouseViewpointPos();

	HC_Open_Segment_By_Key(m_pView->GetConstructionKey());
		HC_Flush_Contents (".", "geometry");
	HC_Close_Segment();
 
    // make certain that new_point != first_point 
	if (m_ptNew.x == m_ptFirst.x && m_ptNew.y == m_ptFirst.y && m_ptNew.z == m_ptFirst.z)
	{
		m_bOpStarted = false;
		return(HOP_CANCEL);
	}

    HC_Open_Segment_By_Key(m_pView->GetSceneKey());	

		HVector pos, tar, up;		
 		HC_Show_Net_Camera_Position(&pos.x, &pos.y, &pos.z);
 		HC_Show_Net_Camera_Target(&tar.x, &tar.y, &tar.z);

		HPoint view;
		view.Set(pos.x-tar.x, pos.y-tar.y, pos.z-tar.z);
		float length = (float)HC_Compute_Vector_Length(&view);
		m_ptFirst.z = length;
		m_ptNew.z = length;

		HC_Compute_Normalized_Vector(&view, &view);
 		HC_Show_Net_Camera_Up_Vector(&up.x, &up.y, &up.z);
		HC_Compute_Normalized_Vector(&up, &up);

    HC_Close_Segment();

	// do the following woprk to make sure that the object is drawn in
	// the view plane correctly
	HC_KEY keys[2];
	keys[0] = m_pView->GetModel()->GetModelKey();
	keys[1] = m_pView->GetSceneKey();

	HC_Compute_Coordinates_By_Path(2, keys, "viewpoint",&m_ptFirst,"object",&m_ptFirst);
	HC_Compute_Coordinates_By_Path(2, keys, "viewpoint",&m_ptNew,"object",&m_ptNew);

	HVector radius_vector;
	radius_vector.Set (m_ptNew.x - m_ptFirst.x,
						 m_ptNew.y - m_ptFirst.y,
						 m_ptNew.z - m_ptFirst.z);

	m_radius = (float)HC_Compute_Vector_Length(&radius_vector);

	HC_Open_Segment_By_Key (GetView()->GetModelKey());
		HC_Open_Segment ("spheres");
			HUtilityGeometryCreation::CreateSphere(m_ptFirst, m_radius, m_NumSides, view, up);
		HC_Close_Segment();
	HC_Close_Segment();

	m_pView->SetGeometryChanged();
    m_pView->Update(); 

    return(HOP_READY);
}



