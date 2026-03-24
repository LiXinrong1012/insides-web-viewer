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
 
 
#include "stdafx.h"

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
#include "HBhvBehaviorManager.h"
#include "HBhvAnimation.h"
#include "HBhvInterpolator.h"
#include "HBhvTimeline.h"
#include "KeyframeEditor.h"
#include "CSolidHoopsView.h"
#include "HUndoManager.h"
#include "stdio.h"
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "hc.h"


/////////////////////////////////////////////////////////////////////////////
// HSOpMoveHandle
//
// Translate items in the selection list in direction of mouse movement
// parallel to camera target plane.
//
// Currently supports translation if item if it is a segment




HSOpMoveHandle::HSOpMoveHandle(HBaseView* view, CSolidHoopsView *WinView, bool allowSelect, int DoRepeat,int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{	
//	HC_KEY kay[1000];
	m_pHandleKey = INVALID_KEY;
	m_pObjectKey = INVALID_KEY;
	m_boxzoom = 1;
	m_bAllowSelect = allowSelect;
	m_pOwnerDialog = 0;
	m_pKeyframeEditor = (CKeyframeEditor *)WinView->GetKeyframeEditorDialog(false);
	m_pSolidHoopsView = WinView;
	m_bInitialMatrix = false;
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
//	HUtilityGeomHandle::ClearAllHandles(GetView());
 
	GetView()->Update();
}


HBaseOperator * HSOpMoveHandle::Clone()
{
	return (HBaseOperator *)new HSOpMoveHandle(GetView(), m_pSolidHoopsView);
}

void HSOpMoveHandle::Reset(HC_KEY okey)
{
	m_pHandleKey = INVALID_KEY;
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


	if (m_pHandleKey == INVALID_KEY)
	{
		if (m_bAllowSelect == false)
		{
			SetOperatorStarted(false);
			return (HOP_OK);
		}
 		HC_KEY okey = FindObject(event, m_pObjectKey, true);
		if (okey!=m_pObjectKey)
		{
			if (m_pObjectKey != INVALID_KEY)
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

					if (ghandle.IsGeomHandle(skey ) != INVALID_KEY ||  strcmp(ssegname, "cpbox") == 0)
					{
						char text[MVO_BUFFER_SIZE];
						HC_Show_Segment(skey, text);
						HC_Delete_By_Key(skey);
					}

				}
				HC_End_Contents_Search();
				HC_Close_Segment();
			}
			m_pHandleKey = INVALID_KEY;

			m_pObjectKey = okey;
 			if (m_pObjectKey != INVALID_KEY)
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
		if (!HUtility::IsModelKey(GetView()->GetModelKey(),m_pHandleKey))
			GetView()->GetConstantFrameRateObject()->SetActivityType(CuttingPlaneActivity);
		else
			GetView()->GetConstantFrameRateObject()->SetActivityType(MovementActivity);

		
 		ShowHandle(ghandle, m_pHandleKey);
		m_pObjectKey = HUtilityGeomHandle::GetMMSegment(m_pHandleKey);
		if( !GetView()->GetAllowInteractiveShadows() && (m_TempShadowMode = GetView()->GetShadowMode()) != HShadowNone )
			GetView()->SetShadowMode(HShadowNone);
		if( !GetView()->GetAllowInteractiveCutGeometry() && (m_TempCutGeometryVisibility = GetView()->GetCutGeometryVisibility()) != HCutGeometryVisibilityNone)
			GetView()->SetCutGeometryVisibility(HCutGeometryVisibilityNone);
	}
	if (m_pObjectKey != INVALID_KEY)
	{
		HC_Open_Segment_By_Key(m_pObjectKey);
			if (GetView()->GetSpritingMode())
 				HC_Set_Heuristics("quick moves = spriting");	
			HC_Set_Rendering_Options("no simple shadow");
		HC_Close_Segment();
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
 	HC_KEY ghandleKey = FindHandle(event);

	if (m_pHandleKey!=INVALID_KEY && ghandleKey != m_pHandleKey)
	{		
		ghandle.ResetHandle(m_pHandleKey);
 		GetView()->Update();
	}
 
     m_pHandleKey = ghandleKey;
  
	if (ghandleKey != INVALID_KEY)
	{
	    ret = HLISTENER_CONSUME_EVENT;
		ghandle.ShowHandle(ghandleKey,0.7f, m_pView);
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
			return INVALID_KEY;
		key = HC_KShow_Owner_By_Key(key);
	}
}
 



static bool GetAllowAnimation(HC_KEY key)
{
    char temp[4096];
    bool ret = false;
    HC_Open_Segment_By_Key (key);
	HC_Show_One_Net_User_Option("hnoani", temp);
	if (strcmp(temp,"") == 0)
	   ret = true;
	HC_Close_Segment();
    return ret; 	
}

//set the world point appropriately if it happens to lie within a screen range window
HPoint get_new_world_point(HPoint const & window_position, HPoint const & world_position, HBaseView * view)
{
	int res = 0, sr_hits = 0;
	HC_KEY * full_path_keys = 0;
	int skey_count = 0;
	char str[MVO_BUFFER_SIZE];
	float x1=-1.f, x2=1.f, y1=-1.f, y2=1.f;
	HPoint ret = world_position;

	HC_Open_Segment_By_Key(view->GetViewKey());
	{
		// We need some sort of path to properly find whether we have a screen range
		// and to compute the coordinates if we do.  Selection is the easiest way to get this.
		HViewSelectionLevel lvl = view->GetViewSelectionLevel();
		view->SetViewSelectionLevel(HSelectionLevelSegment);
		char heur[4096];
		bool heur_saved=false;
		if (HC_Show_Existence("heuristics"))
		{
			HC_Show_Heuristics(heur);
			heur_saved=true;
		}
		HC_Set_Heuristics("related selection limit = 0");
		res = HC_Compute_Selection(".",
			(view->GetSelection()->GetSubwindowPenetration() ? "" : "./scene/overwrite"), 
			"v", window_position.x, window_position.y);
		if (heur_saved)
			HC_Set_Heuristics(heur);
		view->SetViewSelectionLevel(lvl);
	}
	HC_Close_Segment();

	if(res > 0)
	{
		//get a good path for a pshow
		HC_Show_Selection_Keys_Count(&skey_count);
		skey_count += 2;  //make room for the view key and a null terminator at the end
		full_path_keys = new HC_KEY[skey_count];
		HC_Show_Selection_Original_Keys(0, full_path_keys);
		full_path_keys[skey_count-2] = view->GetViewKey();
		full_path_keys[skey_count-1] = 0;

		//find out if we have a screen range
		HC_PShow_One_Net_Rendering_Option(skey_count, full_path_keys, "screen range", str);
		sr_hits=sscanf(str, "%f, %f, %f, %f", &x1, &x2, &y1, &y2);
		
		//if so, convert to the proper window coordinates
		if (sr_hits && (x1!=-1.f || x2!=1.f || y1!=-1.f || y2!=1.f))
			HC_Compute_Coordinates_By_Path(skey_count, full_path_keys, "outer window", &window_position, "world", &ret);

		delete [] full_path_keys;
	}

	return ret;
}
 
int HSOpMoveHandle::OnLButtonDownAndMove(HEventInfo &event)
{
	if (!OperatorStarted())
		return HBaseOperator::OnLButtonDownAndMove(event);

	SetNewPoint(get_new_world_point(event.GetMouseWindowPos(), event.GetMouseWorldPos(), GetView()));
	HPoint tmp = event.GetMouseWindowPos();
	
	HC_KEY camerakey = GetView()->GetSceneKey();
		if (!HUtility::IsModelKey(GetView()->GetModelKey(),m_pHandleKey))
			GetView()->GetConstantFrameRateObject()->SetActivityType(CuttingPlaneActivity);
		else
			GetView()->GetConstantFrameRateObject()->SetActivityType(MovementActivity);

	//store modelling matrix before manipulator usage, for undo history list
	HUtilityGeomHandle ghandle;
	if(!m_bInitialMatrix)
	{
		m_bInitialMatrix = true;
		HC_KEY segkey = ghandle.GetMMSegment(m_pHandleKey);
		HC_Open_Segment_By_Key(segkey);
		{
			float seg_matrix[16];
			if (HC_Show_Existence ("modelling matrix")) 
			{
				HC_Show_Modelling_Matrix (seg_matrix);
			}
			else 
			{
				memset(seg_matrix,0,16*sizeof(float));
				seg_matrix[0] = seg_matrix[5] = seg_matrix[10] = seg_matrix[15] = 1;
			}

			HUndoItemMatrix *item = new HUndoItemMatrix(GetView(), 1, &segkey, seg_matrix);
			GetView()->GetUndoManager()->AddUndoItem(item);
		}
		HC_Close_Segment();
	}

 	if (ghandle.GetConstraintType(m_pHandleKey) == HConstrainToPlane || ghandle.GetConstraintType(m_pHandleKey) == HConstrainToRay || ghandle.GetConstraintType(m_pHandleKey) == HConstrainToViewplane)
	{

		if (ghandle.GetConstraintType(m_pHandleKey) == HConstrainToRay){
			HPoint tmp(GetNewPoint());
			ghandle.AdjustPointToRay(m_pHandleKey, tmp, camerakey, GetView());
			SetNewPoint(tmp);
		}
		ghandle.Move(m_pHandleKey, GetNewPoint(), camerakey, GetView());
	}
	else
	{
		if (ghandle.GetConstraintType(m_pHandleKey) == HConstrainToRotationVector)
		{
 			ghandle.Rotate(m_pHandleKey, (tmp.x - GetFirstPoint().x)*360.0f);
			m_rotater += (tmp.x - GetFirstPoint().x)*360.0f;
		}
		else
		{
			float sf = 1.0f - (tmp.x - GetFirstPoint().x)*5.0f;		
			ghandle.Scale(m_pHandleKey,sf,sf,sf);
		}
	}
	HLISTENER_EVENT(HObjectManipulationListener, GetView()->GetEventManager(), ObjectMovedEvent(GetView(), m_pObjectKey,0));
		if (!HUtility::IsModelKey(GetView()->GetModelKey(),m_pHandleKey))
			GetView()->GetConstantFrameRateObject()->SetActivityType(CuttingPlaneActivity);
		else
			GetView()->GetConstantFrameRateObject()->SetActivityType(MovementActivity);
	
//	if (m_pKeyframeEditor && GetAllowAnimation(m_pObjectKey))
//	    ModifyKeyframe(ghandle.GetConstraintType(m_pHandleKey));

	SetFirstPoint(tmp);

	GetView()->UpdateHighlighting();
	GetView()->SetGeometryChanged();
	GetView()->Update();

	return (HLISTENER_CONSUME_EVENT);
}


int HSOpMoveHandle::OnLButtonUp(HEventInfo &event)
{
  
    if(!OperatorStarted())
		return HBaseOperator::OnLButtonUp(event);

	if (m_pObjectKey!= INVALID_KEY)
	{	
	HC_Open_Segment_By_Key(m_pObjectKey);
			    if (HUtility::ShowOneHeuristic("quick moves")) {
					    HC_UnSet_One_Heuristic("quick moves");
				    }
				HC_Close_Segment();
	}
 	HUtilityGeomHandle ghandle;
	if (m_pKeyframeEditor && GetAllowAnimation(m_pObjectKey))
    {
		ModifyKeyframe(ghandle.GetConstraintType(m_pHandleKey));
		if (m_pKeyframeEditor->GetRecordMode())
		{		
			HBhvBehaviorManager *pBehaviorManager = GetView()->GetModel()->GetBhvBehaviorManager();
			pBehaviorManager->SetCurrentTick(pBehaviorManager->GetCurrentTick()+10);
			m_pKeyframeEditor->UpdateBhvState(true);
			m_pKeyframeEditor->PlayToTick();
		}
    }
	
	SetOperatorStarted(false);
	m_bInitialMatrix = false;
  	ResetHandle(ghandle, m_pHandleKey);
	if (m_pHandleKey != INVALID_KEY)
	{	
		if( !GetView()->GetAllowInteractiveCutGeometry() && m_TempCutGeometryVisibility != HCutGeometryVisibilityNone)
			GetView()->SetCutGeometryVisibility(m_TempCutGeometryVisibility);
		/* Drawing the shadows and cut geometry over again takes a long time, lets take them one at a time... */ 
 		GetView()->ForceUpdate();

		if( !GetView()->GetAllowInteractiveShadows() && m_TempShadowMode != HShadowNone ) 
			GetView()->SetShadowMode(m_TempShadowMode);
	}

	m_pHandleKey = INVALID_KEY;

 	GetView()->Update();

	if (m_pOwnerDialog)
		m_pOwnerDialog->Invalidate();

	return (HLISTENER_CONSUME_EVENT);
}


void HSOpMoveHandle::ModifyKeyframe(HConstrainType ct)
{
	SetupObject(m_pObjectKey);
	char targetname[MVO_BUFFER_SIZE];	
	char objectname[256];
	HBhvBehaviorManager *pBehaviorManager = GetView()->GetModel()->GetBhvBehaviorManager();
	HC_Show_Segment(m_pObjectKey, targetname);
	HBhvTargetObject::CreateTargetString("SPATH", targetname, targetname);

	sprintf(objectname, "%d", pBehaviorManager->GetFreeName());
	
	if (ct == HConstrainToScale)
	{
		HBhvAnimation *animation = pBehaviorManager->FindAnimation(targetname, "Scale");
		if (animation == 0)
		{
			HBhvInterpolatorScale *i = new HBhvInterpolatorScale(0,objectname);
			HPoint parray(1,1,1);
			i->Insert(&parray, 0);
			int tline = 0;
			HBhvTimeline *t = new HBhvTimeline(0);
			t->SetTimeline(&tline , 1);
			animation = pBehaviorManager->AddAnimation(objectname, targetname, t, i);
			animation->GetTarget()->SetPivot(-m_midpoint.x, -m_midpoint.y, -m_midpoint.z);
			
		}
		
		bool replace;
		int pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);
		float matrix[16];
		HC_Open_Segment_By_Key(m_pObjectKey);
		HUtility::ShowModellingMatrix(matrix);
		HPoint p(matrix[0], matrix[1], matrix[2]);
		float scalef = (float)HC_Compute_Vector_Length(&p);
		HC_Close_Segment();
		p.Set(scalef, scalef, scalef);
		
		if (replace)
			((HBhvInterpolatorScale *)(animation->GetInterpolator()))->Replace(p, pos);
		else
			((HBhvInterpolatorScale *)(animation->GetInterpolator()))->Insert(p, pos);
	}
	else if (ct == HConstrainToRotationVector)
	{
		HBhvAnimation *animation = pBehaviorManager->FindAnimation(targetname, "QuatRot");
		float matrix[16];
		float fquat[4];
		if (animation == 0)
		{
			HBhvInterpolatorQuatSquad *i = new HBhvInterpolatorQuatSquad(0, objectname);
			HQuat parray(0,0,0,1);
 			int tline = 0;
 	 		i->Insert(parray, 0);
 			HUtilityGeomHandle ghandle;	
  			HBhvTimeline *t = new HBhvTimeline(0);
			t->SetTimeline(&tline , 1);
			animation = pBehaviorManager->AddAnimation(objectname, targetname, t, i);
 			animation->GetTarget()->SetPivot(-m_midpoint.x, -m_midpoint.y, -m_midpoint.z);
		}

		bool replace;
		int pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);
 		HC_Open_Segment_By_Key(m_pObjectKey);
		HUtility::ShowModellingMatrix(matrix);
	 
		HUtility::MatrixToQuaternion(matrix, fquat);
		HQuat quat(fquat[0], fquat[1], fquat[2], fquat[3]);
	  
		HC_Close_Segment();

		if (replace)
			((HBhvInterpolatorQuatSquad *)(animation->GetInterpolator()))->Replace(quat, pos);
		else
			((HBhvInterpolatorQuatSquad *)(animation->GetInterpolator()))->Insert(quat, pos);
	}
	else
	{
 		HBhvAnimation *animation = m_pKeyframeEditor->GetActiveAnimation();
		if (!animation || strcmp(animation->GetInterpolator()->GetType(), "Pos") != 0 || !animation->GetTarget()->IsEqual(targetname))
		{
			animation = pBehaviorManager->FindAnimation(targetname, "Pos");
			if (animation == 0)
			{
				HBhvInterpolatorPosition *i = new HBhvInterpolatorPosition();
				HPoint parray(0,0,0);
				int tline = 0;
				i->InsertCurve(parray, 0);			
				HBhvTimeline *t = new HBhvTimeline();
				t->AddKeyframe(tline);
				animation = pBehaviorManager->AddAnimation(objectname, targetname, t, i);
				animation->GetTarget()->SetPivot(-m_midpoint.x, -m_midpoint.y, -m_midpoint.z); 	
			}
		}
		bool replace;
		int pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);
		float matrix[16];
		HC_Open_Segment_By_Key(m_pObjectKey);{
			HUtility::ShowModellingMatrix(matrix);
			HPoint p(m_midpoint), p2(0,0,0);
			HC_Compute_Transformed_Points(1, &p, matrix, &p2);
			p = p2 - p;
			
			if (replace)
				((HBhvInterpolatorPosition *)(animation->GetInterpolator()))->ReplaceCurve(p, pos);
			else
				((HBhvInterpolatorPosition *)(animation->GetInterpolator()))->InsertCurve(p, pos);
		}HC_Close_Segment();
	}
}


void HSOpMoveHandle::ModifyColorKeyframe(float t)
{
	char targetname[MVO_BUFFER_SIZE];	
	char objectname[256];
	HBhvBehaviorManager *pBehaviorManager = GetView()->GetModel()->GetBhvBehaviorManager();
	HC_Show_Segment(m_pObjectKey, targetname);
	HBhvTargetObject::CreateTargetString("SPATH", targetname, targetname);
	sprintf(objectname, "%d", pBehaviorManager->GetFreeName());

 	HBhvAnimation *animation = pBehaviorManager->FindAnimation(targetname, "Color");
	if (animation == 0)
	{
		HBhvInterpolatorColor *i = new HBhvInterpolatorColor();
		i->SetColorComponent("transmission");
		i->SetGeomType("faces, text");
		HPoint parray(1,1,1);;
 		int tline = 0;
 	 	i->Insert(parray, 0);
 		HBhvTimeline *t = new HBhvTimeline(0);
		t->SetTimeline(&tline , 1);
		animation = pBehaviorManager->AddAnimation(objectname, targetname, t, i);  	
	}

	bool replace;
	int pos = animation->GetTimeline()->AddKeyframe((int)pBehaviorManager->GetCurrentTick(), replace);
	HPoint p(t, t, t);
	if (replace)
		((HBhvInterpolatorColor *)(animation->GetInterpolator()))->Replace(p, pos);
	else
		((HBhvInterpolatorColor *)(animation->GetInterpolator()))->Insert(p, pos);
	
	if (m_pOwnerDialog)
		m_pOwnerDialog->Invalidate();

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

	HUtilityAnnotation ghandle;
	char col[256];
	HPoint resx;
	switch((int)the_char){

	case '1':
			HC_Open_Segment_By_Key(m_pObjectKey);
			HC_Set_Color("everything = (transmission = black)");
			HC_Close_Segment();
			ModifyColorKeyframe(0);
			break;

	case '2':
			HC_Open_Segment_By_Key(m_pObjectKey);
			resx.Set(0.1f, 0.1f, 0.1f);
			sprintf(col,"everything = (transmission = (r=%f g=%f b=%f))", resx.x, resx.y, resx.z);
			HC_Set_Color(col);
			HC_Close_Segment();
			ModifyColorKeyframe(0);
			break;

	case '0':
			HC_Open_Segment_By_Key(m_pObjectKey);
			HC_Set_Color("everything = (transmission = white)");
			HC_Close_Segment();
			ModifyColorKeyframe(1);
			break;

	case '5':
			HC_Open_Segment_By_Key(m_pObjectKey);
			char col[MVO_BUFFER_SIZE];
			HC_Show_Color(col);
			HC_Set_Color("everything = (transmission = grey)");
			HC_Show_Color(col);
			HC_Close_Segment();
			ModifyColorKeyframe(0.5f);
			break;

	case '9':
			HC_Open_Segment_By_Key(m_pObjectKey);
			HC_Show_Color(col);
			HC_Set_Color("everything = (transmission = light grey)");
			HC_Show_Color(col);
			HC_Close_Segment();
			ModifyColorKeyframe(0.8f);
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
	handle.ShowHandle(key, 0.7f, m_pView);
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
