// HOpCreateRectangle.cpp : implementation of the HOpCreateRectangle class
//

#include <math.h>
#include <string.h>

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HSoccerView.h"
#include "HOpConstructRectangle.h"
#include "HOpCreateRectangle.h"
#include "HTools.h"
#include "HEventInfo.h"
#include "HUtility.h"
#include "HSnapGrid.h"


HOpCreateRectangle::HOpCreateRectangle(HBaseView* view, int DoRepeat, int DoCapture) : HOpConstructRectangle(view, DoRepeat, DoCapture, false)
{
}

HOpCreateRectangle::~HOpCreateRectangle()
{
}

HBaseOperator * HOpCreateRectangle::Clone()
{
	return (HBaseOperator *)new HOpCreateRectangle(m_pView);
}



const char * HOpCreateRectangle::GetName() { return "HOpCreateRectangle"; }





int HOpCreateRectangle::OnLButtonUp(HEventInfo &event)
{
	if(!m_bOpStarted) 
		return HOpConstructRectangle::OnLButtonDownAndMove(event);

	HOpConstructRectangle::OnLButtonUp(event);

	// make certain that new_point != first_point 
	if (m_ptNew.x == m_ptFirst.x &&
		m_ptNew.y == m_ptFirst.y)
		return(HOP_CANCEL);

	// need to translate the points from window into world space
	HC_Open_Segment_By_Key (m_pView->GetSceneKey());
	  HC_Compute_Coordinates(".", "local window", &m_ptFirst, "world", &m_ptFirst);
	  HC_Compute_Coordinates(".", "local window", &m_ptNew, "world", &m_ptNew);
	HC_Close_Segment();

	// insert the rectangle into the model segment
	HC_Open_Segment_By_Key(GetView()->GetModelKey());
	  HC_Open_Segment("sample_rectangles"); 
	    HUtility::InsertRectangle (".", m_ptFirst.x, m_ptFirst.y, m_ptNew.x, m_ptNew.y);
	  HC_Close_Segment();
	HC_Close_Segment();

    m_pView->Update(); 
    m_bOpStarted = false;

    return(HOP_READY);	
}