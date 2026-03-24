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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HOpMarkupMeasure.cpp,v 1.59 2008-10-21 21:55:07 guido Exp $
//

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HTools.h"
#include "HOpMarkupMeasure.h"
#include "HUtilityAnnotation.h"
#include "HUtilityAnnotationMeasure.h"
#include "HMarkupManager.h"
#include "HImHideOverlappedText.h"

#include "stdio.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "hc.h"


HOpMarkupMeasure::HOpMarkupMeasure(HBaseView* view, bool AddToLayer, int DoRepeat,int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{
	m_iBackgroundType = BG_QUAD;
	m_bAddToLayer = AddToLayer;
	view->SetAnnotationResize(true);
}

HOpMarkupMeasure::~HOpMarkupMeasure()
{
	EndOp();
}


HBaseOperator * HOpMarkupMeasure::Clone()
{
	return (HBaseOperator *)new HOpMarkupMeasure(GetView());
}

 
const char * HOpMarkupMeasure::GetName() { return "HOpMarkupMeasure"; }
  

int HOpMarkupMeasure::OnLButtonDown(HEventInfo &event)
{
	HPoint pos = event.GetMouseWindowPos();
	int count, dummy;
	float fdummy;

	if(OperatorStarted() && m_Annotation.GetTextLength() == 0){
		EndOp();
		HC_Delete_By_Key(m_Annotation.GetKey());
		GetView()->Update();
	}

	HC_Open_Segment_By_Key(GetView()->GetViewKey());{
		HViewSelectionLevel lvl = GetView()->GetViewSelectionLevel();
		GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
		count = HC_Compute_Selection(".", ".", "v", pos.x, pos.y);
		GetView()->SetViewSelectionLevel(lvl);
	}HC_Close_Segment();

	if(count == 0){
		EndOp();
		return HOP_CANCEL;
	} 

	HC_KEY keys[128];
	int key_path_length;
	HC_Show_Selection_Original_Keys(&key_path_length, keys);

	HC_KEY key;
	HC_Show_Selection_Element(&key, &dummy, &dummy, &dummy);
	HC_Show_Selection_Position(&fdummy, &fdummy, &fdummy,
		&pos.x, &pos.y, &pos.z);

	char type[1024];
	HC_Show_Key_Type(key, type);
	
	if(streq(type, "segment")){
		EndOp();
		return HOP_CANCEL;
	}
	
	if(HUtilityAnnotation::IsNote(key)){
		EndOp();
		return HOP_CANCEL;
	}

	EndOp();
	if(HUtilityAnnotationMeasure::IsMeasurement(key)){
		/* This create an annotation class for an existing annotation in the model */
		m_Annotation.SetNote(key, GetView());
		m_bNewNote = false;
	} else {
		/* This creates a new annotation */
		char segment[1024*4];
		HC_Show_Owner_By_Key(key, segment);
		HC_KEY seg_key = HC_KOpen_Segment(segment);{
		}HC_Close_Segment();
		m_Annotation.Insert(pos, pos,
			seg_key,
			GetView(),
			INVALID_KEY,
			m_iBackgroundType,
			true, keys, key_path_length);
		//m_Annotation.SetLineWeight(2);
		//m_Annotation.SetEdgeWeight(2);
		m_Annotation.SetText("0");
		m_bNewNote = true;
		SetFirstPoint(pos);
	}
	StartOp();
	m_Annotation.Resize(GetView()->GetIncludeLinkKey(), GetView()->GetViewKey()); 
	GetView()->Update();

	return HOP_OK;
}


int HOpMarkupMeasure::OnLButtonDownAndMove(HEventInfo &event)
{
	if(OperatorStarted()){
		if(m_bNewNote){
			/* change the point b on the measuring line. */
			int count;

			HPoint pos, win = event.GetMouseWindowPos();
			HC_Open_Segment_By_Key(GetView()->GetViewKey());{
				HViewSelectionLevel lvl = GetView()->GetViewSelectionLevel();
				GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
				count = HC_Compute_Selection(".", ".", "v", win.x, win.y);
				GetView()->SetViewSelectionLevel(lvl);
				if(count > 0){
					HC_Show_Selection_Position(&win.x, &win.y, &win.z, &pos.x, &pos.y, &pos.z);
				} else {
					pos = event.GetMouseWorldPos();
				}
			}HC_Close_Segment();
			HPoint A, tmp;
			m_Annotation.ShowTarget(A);
			tmp = pos - A;
			float length = HC_Compute_Vector_Length(&tmp);
			char length_str[64];
			sprintf(length_str, "%g", length);
			m_Annotation.SetText(length_str);
			m_Annotation.MoveText(A, pos);
		} else {
			/* Move the note (and the measuring line) and have leader lines going
			   back to point a and point b */
			HPoint pos = event.GetMouseWorldPos();
			HPoint plane_point;
			m_Annotation.ShowPosition(plane_point);
			HUtility::AdjustPositionToPlane(GetView(), pos, plane_point);
			m_Annotation.MoveText(pos);
		}
		m_Annotation.Resize(GetView()->GetIncludeLinkKey(), GetView()->GetViewKey());
		GetView()->Update();
	}
	return HOP_OK;
}

int HOpMarkupMeasure::OnRButtonDown(HEventInfo &event)
{
	EndOp();
	return HOP_OK;
}

int HOpMarkupMeasure::OnLButtonUp(HEventInfo &event)
{
	HPoint pos = event.GetMouseWindowPos();
	int count, idummy;
	float fdummy;
	HC_KEY key;

	if(!OperatorStarted())
		return(HOP_CANCEL);

	HC_Open_Segment_By_Key(GetView()->GetViewKey());{
		HViewSelectionLevel lvl = GetView()->GetViewSelectionLevel();
		GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
		count = HC_Compute_Selection(".", ".", "v", pos.x, pos.y);
		GetView()->SetViewSelectionLevel(lvl);
	}HC_Close_Segment();

	if(count == 0){
		EndOp();
		HC_Delete_By_Key(m_Annotation.GetKey());
	} else {
		OnLButtonDownAndMove(event);
		HC_Show_Selection_Element(&key, &idummy, &idummy, &idummy);
		HC_Show_Selection_Position(&fdummy, &fdummy, &fdummy,
			&pos.x, &pos.y, &pos.z);

		char type[1024];
		HC_Show_Key_Type(key, type);
		
		if(streq(type, "segment")){
			EndOp();
			HC_Delete_By_Key(m_Annotation.GetKey());
		}

		if(m_bNewNote && pos == GetFirstPoint()){
			EndOp();
			HC_Delete_By_Key(m_Annotation.GetKey());
		}
	}

	if(!OperatorStarted()){
		GetView()->Update();
	}

    return(HOP_OK);
}


int
HOpMarkupMeasure::OnKeyDown(HEventInfo &event)
{
	bool please_update = false;

	if (OperatorStarted()){

		char the_char = event.GetChar();
		
		switch((int)the_char){

		case '\r':		
			// is this a return
			if(!m_bTouchedText){
				m_bTouchedText = true;
				m_Annotation.SetText("");
			}
			m_Annotation.AddChar('\n');		
			please_update = true;
			break;
		
		case '\b':
			// erase
			if(m_Annotation.GetTextLength() > 0){
				// terminate the string one char shorter
				m_Annotation.AddChar('\b');
				m_bTouchedText = true;
			} else {
				EndOp();
				HC_Delete_By_Key(m_Annotation.GetKey());
			}
			please_update = true;
			break;

		default:{
				if(event.Control()){
					if(the_char == ' '){
						m_iBackgroundType = m_iBackgroundType == BG_NONE ? 0 : m_iBackgroundType +1;
						m_Annotation.SetBackgroundType(m_iBackgroundType);
						please_update = true;
					}
				}
				else if	((the_char >= ' ') && (the_char <= '~')) {
					if(!m_bTouchedText){
						m_bTouchedText = true;
						m_Annotation.SetText("");
					}
					m_Annotation.AddChar(the_char);		
					please_update = true;
				}

				}break;
		}//switch
	}

	if(please_update){
		if(OperatorStarted())
			m_Annotation.Resize(GetView()->GetIncludeLinkKey(), GetView()->GetViewKey());
		GetView()->Update();
	}
	
	return HOP_OK;
}


bool HOpMarkupMeasure::EndOp()
{
	bool retval = OperatorStarted();
	if(OperatorStarted()){
		SetOperatorStarted(false);
		HC_Open_Segment_By_Key(m_Annotation.GetKey());{
			HC_UnSet_One_Heuristic("quick moves");
			HC_UnSet_One_Rendering_Option("depth range");
		}HC_Close_Segment();
		m_Annotation.SetLineWeight(1);
		m_Annotation.SetEdgeWeight(1);
		m_Annotation.SetColor("lines = red, edges = red");
		GetView()->Update();
		if(m_bHideOverlappedText){
			HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
				HImHideOverlappedText::FilterOn();
			}HC_Close_Segment();
		}
	}
	return retval;
}

void HOpMarkupMeasure::StartOp()
{
	SetOperatorStarted(true);
	m_bTouchedText = false;
	m_Annotation.SetLineWeight(2);
	m_Annotation.SetEdgeWeight(2);
	m_Annotation.SetColor("lines = yellow, edges = yellow");
	HC_Open_Segment_By_Key(m_Annotation.GetKey());{
		HC_Set_Heuristics("quick moves");
	  	HC_Set_Rendering_Options("depth range=(0,0.1)");
	}HC_Close_Segment();
	
	if(m_bHideOverlappedText = HImHideOverlappedText::IsFilterOn()){
		HC_Open_Segment_By_Key(GetView()->GetSceneKey());{
			HImHideOverlappedText::FilterOff();
		}HC_Close_Segment();
	}
}
