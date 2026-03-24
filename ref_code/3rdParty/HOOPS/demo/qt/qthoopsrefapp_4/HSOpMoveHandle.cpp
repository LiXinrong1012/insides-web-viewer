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
 
 

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HEventManager.h"
#include "HTools.h"
#include "HSOpMoveHandle.h"
#include "HUtilityGeomHandle.h"
#include "HMarkupManager.h"
#include "HSelectionSet.h"
#include "stdio.h"
#include <math.h>
#include <string.h>
#include "hc.h"


/////////////////////////////////////////////////////////////////////////////
// HSOpMoveHandle
//
// Translate items in the selection list in direction of mouse movement
// parallel to camera target plane.
//
// Currently supports translation if item if it is a segment




HSOpMoveHandle::HSOpMoveHandle(HBaseView* view,  bool allowSelect, int DoRepeat,int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{	
//	HC_KEY kay[1000];
	m_pHandleKey = -1;
	m_pObjectKey = -1;
	m_boxzoom = 1;
	m_bAllowSelect = allowSelect;
/*
	if (allowSelect)
	{
		HC_KEY key;
		HSelectionSet *ss = view->GetSelection();
		if (ss->GetSize())
		{
			int k;
			for (k=0;k<(int)ss->GetSize();k++)
				kay[k] = ss->GetAt(k);
			key = ss->GetAt(k);
			int msize = ss->GetSize();
			for (k=0;k<msize;k++)
			{
				key = kay[k];
				char type[256];
				HC_Show_Key_Type(key, type);
				if (strcmp(type, "segment")!=0)
				{
					key = HC_KShow_Owner_By_Key(key);
				}
				
				ss->DeSelectAll(); 
				m_pObjectKey = key;
 				SetupObject(m_pObjectKey);			
				GetView()->Update();
			}
		}
	}
	*/
}

void HSOpMoveHandle::SetupObject(HC_KEY key)
{  
	HUtility::NameSegments(m_pObjectKey, GetView());
	HUtilityGeomHandle::GetCenterPoint(key, m_midpoint);

 
}


HSOpMoveHandle::~HSOpMoveHandle()
{
	HUtilityGeomHandle::ClearAllHandles(GetView());
 
	GetView()->Update();
}


HBaseOperator * HSOpMoveHandle::Clone()
{
	return (HBaseOperator *)new HSOpMoveHandle(GetView());
}

void HSOpMoveHandle::Reset(HC_KEY okey)
{
	m_pHandleKey = -1;
	m_pObjectKey = okey;

}


const char * HSOpMoveHandle::GetName() { return "HSOpMoveHandle"; }
 
/////////////////////////////////////////////////////////////////////////////
// HSOpMoveHandle message handlers



HC_KEY HSOpMoveHandle::FindHandle(HEventInfo &event)
{  
	HPoint new_pos = event.GetMouseWindowPos();
	return ( HUtilityGeomHandle::SelectHandle(GetView(), new_pos));

}
 

 


HC_KEY HSOpMoveHandle::FindObject(HEventInfo &event, HC_KEY oldkey, bool exclude)
{
	HPoint  new_pos;  
	new_pos = event.GetMouseWindowPos();
	return (HUtilityGeomHandle::SelectObject(GetView(),new_pos, oldkey, exclude));
}

 
int HSOpMoveHandle::OnLButtonDown(HEventInfo &event)
{
	HUtilityGeomHandle ghandle;
	m_rotater = 0;
	m_TempShadowMode = HShadowNone;
  
	if (!OperatorStarted()) 
		SetOperatorStarted(true);
	else return true;

	m_pHandleKey =FindHandle(event);

	if (m_pHandleKey == -1)
	{
		if (1)
		{
			SetOperatorStarted(false);
			return (HOP_OK);
		}
 		HC_KEY okey = FindObject(event, m_pObjectKey, true);
		if (okey!=m_pObjectKey)
		{
			if (m_pObjectKey != -1)
			{
				HC_Open_Segment_By_Key(m_pObjectKey);
				HC_Begin_Contents_Search(".", "segments");
				HC_KEY skey;
				char type[256];
				while (HC_Find_Contents(type, &skey))
				{
					char text[MVO_BUFFER_SIZE];
					char ssegname[MVO_BUFFER_SIZE];

						HC_Show_Segment(skey, text);
						HC_Parse_String(text, "/", -1, ssegname);

					if (ghandle.IsGeomHandle(skey )!=-1 ||  strcmp(ssegname, "cpbox") == 0)
					{
						char text[MVO_BUFFER_SIZE];
						HC_Show_Segment(skey, text);
						HC_Delete_By_Key(skey);
					}

				}
				HC_End_Contents_Search();
				HC_Close_Segment();
			}
			m_pHandleKey = -1;

			m_pObjectKey = okey;
 			if (m_pObjectKey != -1)
			{
				HUtility::NameSegments(m_pObjectKey, GetView());
				m_boxzoom = 1;
				SetupObject(m_pObjectKey);
			}

		}
		SetOperatorStarted(false);
	}
	else
	{
 		ShowHandle(ghandle, m_pHandleKey);
		m_pObjectKey = HUtilityGeomHandle::GetMMSegment(m_pHandleKey);
		if( !GetView()->GetAllowInteractiveShadows() && (m_TempShadowMode = GetView()->GetShadowMode()) != HShadowNone )
			GetView()->SetShadowMode(HShadowNone);
	}

	
	SetNewPoint(event.GetMouseWorldPos());
	SetFirstPoint(event.GetMouseWindowPos());
	
	GetView()->Update();
	
	return (HLISTENER_CONSUME_EVENT);
}


int HSOpMoveHandle::OnNoButtonDownAndMove(HEventInfo &event)
{
   	int ret = HLISTENER_PASS_EVENT;
   	HUtilityGeomHandle ghandle;

	if (m_pHandleKey!=-1)
		ghandle.ResetHandle(m_pHandleKey);
 
	HC_KEY ghandleKey = FindHandle(event);
	    m_pHandleKey = ghandleKey;

	if (ghandleKey != -1)
	{
	    ret = HLISTENER_CONSUME_EVENT;
		ghandle.ShowHandle(ghandleKey);
	    GetView()->Update();
	
 
	}	
        return (ret);

}


HC_KEY HSOpMoveHandle::IsCameraSet(HC_KEY key)
{
	while(1)
	{
		HC_Open_Segment_By_Key(key);
		int cexists = HC_Show_Existence("camera");
		HC_Close_Segment();
		if (cexists)
 			return key;
		if (key == GetView()->GetModelKey() || key == GetView()->GetViewKey())
			return -1;
		key = HC_KShow_Owner_By_Key(key);
	}
}
 



 
int HSOpMoveHandle::OnLButtonDownAndMove(HEventInfo &event)
{

	if (!OperatorStarted())
		return HBaseOperator::OnLButtonDownAndMove(event);
	SetNewPoint(event.GetMouseWorldPos());
	HPoint tmp = event.GetMouseWindowPos();

	HC_KEY camerakey = GetView()->GetSceneKey();

	HUtilityGeomHandle ghandle;
	if (ghandle.GetConstraintType(m_pHandleKey) == HConstrainToPlane || ghandle.GetConstraintType(m_pHandleKey) == HConstrainToRay || ghandle.GetConstraintType(m_pHandleKey) == HConstrainToViewplane)
	{
		if (ghandle.GetConstraintType(m_pHandleKey) == HConstrainToRay){
			HPoint new_point(GetNewPoint());
			ghandle.AdjustPointToRay(m_pHandleKey, new_point, camerakey, GetView());
			SetNewPoint(new_point);
		}

		ghandle.Move(m_pHandleKey, GetNewPoint(), camerakey, GetView());
	}
	else
	{
		if (ghandle.GetConstraintType(m_pHandleKey) == HConstrainToRotationVector)
		{
			ghandle.Rotate(m_pHandleKey, (tmp.x - GetFirstPoint().x) * 360.0f);
			m_rotater += (tmp.x - GetFirstPoint().x)*360.0f;
		}
		else
		{
			float sf = 1.0f - (tmp.x - GetFirstPoint().x)*5.0f;
			ghandle.Scale(m_pHandleKey,sf,sf,sf);
		}
	}
	HLISTENER_EVENT(HObjectManipulationListener, GetView()->GetEventManager(), ObjectMovedEvent(GetView(), m_pObjectKey,0));

	SetFirstPoint(tmp);
	GetView()->SetGeometryChanged();
	GetView()->Update();
	return (HLISTENER_CONSUME_EVENT);
}





int HSOpMoveHandle::OnLButtonUp(HEventInfo &event)
{
    if(!OperatorStarted())
		return HBaseOperator::OnLButtonUp(event);
  
	SetOperatorStarted(false);

	HUtilityGeomHandle ghandle;
  	ResetHandle(ghandle, m_pHandleKey);
	if (m_pHandleKey != INVALID_KEY)
	{	
		if(!GetView()->GetAllowInteractiveShadows() && m_TempShadowMode != HShadowNone ) 
			GetView()->SetShadowMode(m_TempShadowMode);
	}

	m_pHandleKey = INVALID_KEY;
 	GetView()->Update();

	return (HLISTENER_CONSUME_EVENT);
}



/*!
	OnKeyDown inserts annotation text near the second point in the annotation line. The text field is terminated by a 
	carriage return event.  Erase is backspace.
	\param event An HEventInfo object containing information about the current event.
	\return An integer value indicating success or failure.
*/
int HSOpMoveHandle::OnKeyDown(HEventInfo &event)
{
	if (OperatorStarted() || !m_pHandleKey) 
		return HBaseOperator::OnKeyDown(event);

	char the_char = event.GetChar();

	char col[256];
	HPoint resx;

	HUtilityAnnotation ghandle;

	switch((int)the_char){

	case '1':
			HC_Open_Segment_By_Key(m_pObjectKey);
			HC_Set_Color("everything = (transmission = black)");
			HC_Close_Segment();
			break;

	case '2':
			HC_Open_Segment_By_Key(m_pObjectKey);
 			resx.Set(0.1f, 0.1f, 0.1f);
			sprintf(col,"everything = (transmission = (r=%f g=%f b=%f))", resx.x, resx.y, resx.z);
			HC_Set_Color(col);
			HC_Close_Segment();
			break;

	case '0':
			HC_Open_Segment_By_Key(m_pObjectKey);
			HC_Set_Color("everything = (transmission = white)");
			HC_Close_Segment();
			break;

	case '5':
			HC_Open_Segment_By_Key(m_pObjectKey);
			char col[MVO_BUFFER_SIZE];
			HC_Show_Color(col);
			HC_Set_Color("everything = (transmission = grey)");
			HC_Show_Color(col);
			HC_Close_Segment();
			break;

	case '9':
			HC_Open_Segment_By_Key(m_pObjectKey);
			HC_Show_Color(col);
			HC_Set_Color("everything = (transmission = light grey)");
			HC_Show_Color(col);
			HC_Close_Segment();
			break;

	case '+':
			m_boxzoom++;
			HUtilityGeomHandle::ClearAllHandles(GetView());
			if (m_pObjectKey != INVALID_KEY)
				SetupObject(m_pObjectKey);
			m_pHandleKey = INVALID_KEY;
			GetView()->Update();
			break;

	case '-':
			m_boxzoom--;
 			HUtilityGeomHandle::ClearAllHandles(GetView());
			if (m_pObjectKey != INVALID_KEY)
				SetupObject(m_pObjectKey);
			m_pHandleKey = INVALID_KEY;
			GetView()->Update();
			break;

	default:
		break;
	}//switch
 	
 	GetView()->Update();
	return (HOP_OK);

}

void HSOpMoveHandle::ShowHandle(HUtilityGeomHandle &handle, HC_KEY key)
{
	handle.ShowHandle(key);
}

void HSOpMoveHandle::ResetHandle(HUtilityGeomHandle &handle, HC_KEY key)
{
	handle.ResetHandle(key);
}

int HSOpMoveHandle::SetupHandlesEvent(HBaseView *view, HC_KEY key, bool complex)
{
    Reset(INVALID_KEY);
    return HLISTENER_PASS_EVENT;
}
