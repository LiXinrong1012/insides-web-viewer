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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HMyQuery.cpp,v 1.6 2008-02-06 04:22:37 jason Exp $
//



#include <math.h>
#include <stdio.h>
#include <string.h>

#include "MyHQWidget.h"
#include "HMyQuery.h"

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HEventInfo.h"
#include "HTools.h"

#include "hc.h"


/////////////////////////////////////////////////////////////////////////////
// HMyQuery

// Operator for querying model
// Mouse down - displays modeless query dialog containing and computes information 
// about the part intersected by the calculated picking ray
// Mouse motion while down - dynamically updates the dialog based on new picking ray


HMyQuery::HMyQuery(HBaseView* view, int DoRepeat, int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{
}

HMyQuery::~HMyQuery( void )
{
}

void HMyQuery::GetName(char *name)
{
	strcpy(name,"Query");
}

int HMyQuery::OnLButtonDown(HEventInfo &event)
{
	// Mouse went down 

    SetNewPoint(event.GetMouseWindowPos());

	if (DoQuery())
		DialogMaker->ShowQueryDialog();
    return (HOP_OK);
}

int HMyQuery::OnLButtonUp(HEventInfo &event)
{
	return HBaseOperator::OnLButtonUp(event);
}



// perform the query and update the dialog with the model info
bool HMyQuery::DoQuery()
{
	char save_selection[512], type[64], path[512];
	char QueryString[1024];
	int count, off1, off2, off3;
	HC_KEY key = 0;
	bool ls = false;
	HPoint	awindow, camera, object;

	HC_Open_Segment_By_Key (GetView()->GetSceneKey());


	// save selection settings if locally set
	if (HC_Show_Existence("selectability")){
		HC_Show_Selectability (save_selection);
		ls = true;
	}

	HC_Set_Selectability ("geometry=on");


	if ((count = HC_Compute_Selection (GetView()->GetDriverPath(), ".", "v", GetNewPoint().x, GetNewPoint().y)) > 0)
	{
	
		HC_Show_Selection_Element(&key, &off1, &off2, &off3);
		HC_Show_Selection_Position(&awindow.x, &awindow.y, &awindow.z, &camera.x, &camera.y, &camera.z);
		HC_Show_Selection_Pathname(path);
		HC_Show_Key_Type(key, type);

		HC_Compute_Coordinates(path, "world", &camera, "object", &object);
	}
	else 
	{
		HPoint new_point(GetNewPoint());
		HC_Compute_Coordinates(".","local window", &new_point, "world", &camera);
		sprintf(type, "N/A");
		object = camera;
	}
	

	int char_offset = 0;
	char_offset = sprintf(QueryString+char_offset,
		"Geometry key: %ld\n"
		"Geometry type: %s\n"
		"\n",
		key, type);
	char_offset = sprintf(QueryString+char_offset,
		"Coordinates of pick location:\n"
		"\n"
		"\tWindow Space:\n"
		"\tx = %g\n"
		"\ty = %g\n"
		"\tz = %g\n\n"
		"\tWorld Space:\n"
		"\tx = %g\n"
		"\ty = %g\n"
		"\tz = %g\n\n"
		"\tObject Space:\n"
		"\tx = %g\n"
		"\ty = %g\n"
		"\tz = %g\n",
		GetNewPoint().x, GetNewPoint().y, GetNewPoint().z,
		camera.x, camera.y, camera.z,
		object.x, object.y, object.z);

	DialogMaker->SetQueryDialogText(QueryString);


	//restore selection settings
	if (ls)
		HC_Set_Selectability(save_selection);
	else
		HC_UnSet_Selectability();
	
	HC_Close_Segment();

	return true;
}

void HMyQuery::SetDialogMaker(MyHQWidget* bla)
{
	DialogMaker=bla;	
}

int HMyQuery::OnMouseMove(HEventInfo &event)
{
    //  Mouse is down and has moved  
	if (!event.LButton())
		return HBaseOperator::OnMouseMove(event);
  	 
    SetNewPoint(event.GetMouseWindowPos());

	if (DoQuery())
		DialogMaker->ShowQueryDialog();

	return (HOP_OK);
}



