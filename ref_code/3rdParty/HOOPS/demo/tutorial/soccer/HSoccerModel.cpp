// HSoccerModel.cpp : implementation of the HSoccerModel class
//

//#include "StdAfx.h"
//#include <afxtempl.h>
//#include "Soccer.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "hc.h"
#include "HStream.h"
#include "HOpcodeShell.h"
#include "HUtility.h"

#include "HSoccerModel.h"
#include "HTools.h"

#include "vlist.h"


void HSoccerModel::InsertFilledRectangle (
   const char	*	seg,
   float       x0,
   float       y0,
   float       x1,
   float       y1) {
   HPoint       pts[5];

   pts[0].x = x0;   pts[0].y = y0;   pts[0].z = 0.0F;
   pts[1].x = x0;   pts[1].y = y1;   pts[1].z = 0.0F;
   pts[2].x = x1;   pts[2].y = y1;   pts[2].z = 0.0F;
   pts[3].x = x1;   pts[3].y = y0;   pts[3].z = 0.0F;
   pts[4].x = x0;   pts[4].y = y0;   pts[4].z = 0.0F;

   HC_QInsert_Polygon (seg, 5, pts);
}

HSoccerModel::HSoccerModel()
{
	m_bSolidModel = false;
	SetBRepGeometry(false);
	m_pLayers = 0;
}

HSoccerModel::~HSoccerModel()
{
	// Model cleanup : delete all the HOOPS/3dGS entities associated with
	// the model, and delete/initialize the list data structure 
	DeleteAllEntities();

	delete_vlist(m_pLayers);
	m_pLayers = 0;
}


// create a scene-graph to represent a soccer field
void HSoccerModel::Init()
{
	HC_KEY seg_key, author_text_key;
	HPoint points[3], line[2];
	HPoint center;
	center.x = 0.0;
	center.y = 0.0;
	center.z = 0.0;
	line[0].Set(0.0f, -0.8f, 0.0f);
	line[1].Set(1.5f, -0.8f, 0.0f);


	HBaseModel::Init();

	m_pLayers = new_vlist(malloc, free);

	HC_Open_Segment_By_Key(GetModelKey());
	  
	  HC_Set_Line_Weight(2.0);
	  HC_Set_Edge_Weight(2.0);

	  HC_Open_Segment("title");
	    HC_Insert_Text(0.0, 0.8, 0.0, "Sample Soccer Field");
		HC_Set_Text_Alignment("*");
	  HC_Close_Segment();

	  HC_Open_Segment("author");
	    author_text_key = HC_KInsert_Text(0.8, -0.8, 0.0, "Author:  David Beckham");
	    HC_Open_Geometry(author_text_key);
		  HC_Set_Text_Region(2, line, "");
	    HC_Close_Geometry();
	  HC_Close_Segment();

	  seg_key = HC_KOpen_Segment("base_field");
	    HC_Set_Rendering_Options("depth range=(0.7,0.9)");

	    vlist_add_last(m_pLayers, (void*)seg_key);
	    HUtility::InsertRectangle(".", -0.75, -0.5, 0.75, 0.5);
	    HC_Insert_Line(0.0, 0.5, 0.0, 0.0, -0.5, 0.0);

	    bool success = HUtilityGeometryCreation::GeneratePointsOnCircle(points, center, 0.2f, HUtility::XY, 3, false);
	    if (!success)
		    return;

	    HC_Insert_Circle(&points[0], &points[1], &points[2]);

		HC_Open_Segment("text");

		  HC_Set_Text_Alignment("**");

		  HC_Insert_Line(-0.85, 0.5, 0.0, -0.85, 0.1, 0.0);
		  HC_Insert_Line(-0.85, -0.5, 0.0, -0.85, -0.1, 0.0);
		  HC_Insert_Line(-0.90, 0.5, 0.0, -0.80, 0.5, 0.0);
		  HC_Insert_Line(-0.90, -0.5, 0.0, -0.80, -0.5, 0.0);
		  HC_Insert_Text(-0.85, 0.0, 0.0, "75m");

		  HC_Insert_Line(-0.75, 0.6, 0.0, -0.1, 0.6, 0.0);
		  HC_Insert_Line(0.75, 0.6, 0.0, 0.1, 0.6, 0.0);
		  HC_Insert_Line(-0.75, 0.55, 0.0, -0.75, 0.65, 0.0);
		  HC_Insert_Line(0.75, 0.55, 0.0, 0.75, 0.65, 0.0);
		  HC_Insert_Text(0.0, 0.6, 0.0, "120m");
	    HC_Close_Segment();

	  HC_Close_Segment();

	  seg_key = HC_KOpen_Segment("penalty_areas");
	    HC_Set_Rendering_Options("depth range=(0.3,0.6)");
	    
	    vlist_add_last(m_pLayers, (void*)seg_key);
	    HSoccerModel::InsertFilledRectangle(".", -0.75f, -0.3f, -0.50f, 0.3f);
		HSoccerModel::InsertFilledRectangle(".", 0.75f, -0.3f, 0.50f, 0.3f);
		HC_Set_Visibility("faces = on");

		HC_Open_Segment("text");
		  
		  HC_Set_Text_Alignment("**");

		  HC_Insert_Line(-0.40, 0.3, 0.0, -0.40, 0.05, 0.0);
		  HC_Insert_Line(-0.40, -0.3, 0.0, -0.40, -0.05, 0.0);
		  HC_Insert_Line(-0.45, 0.3, 0.0, -0.35, 0.3, 0.0);
		  HC_Insert_Line(-0.45, -0.3, 0.0, -0.35, -0.3, 0.0);
		  HC_Insert_Text(-0.40, 0.0, 0.0, "25m");

		  HC_Insert_Line(-0.75, 0.4, 0.0, -0.70, 0.4, 0.0);
		  HC_Insert_Line(-0.50, 0.4, 0.0, -0.55, 0.4, 0.0);
		  
		  HC_Insert_Line(-0.50, 0.35, 0.0, -0.50, 0.45, 0.0);
		  HC_Insert_Text(-0.625, 0.4, 0.0, "18m");
	    HC_Close_Segment();

	  HC_Close_Segment();

	  seg_key = HC_KOpen_Segment("goals");
	    HC_Set_Rendering_Options("depth range=(0.0,0.25)");

	    vlist_add_last(m_pLayers, (void*)seg_key);
	    HSoccerModel::InsertFilledRectangle(".", -0.75f, -0.15f, -0.70f, 0.15f);
		HSoccerModel::InsertFilledRectangle(".", 0.75f, -0.15f, 0.70f, 0.15f);
		HC_Set_Visibility("faces = on");
		HC_Set_Color("faces = red");

		HC_Open_Segment("text");
		  
		  HC_Set_Text_Alignment("**");

		  HC_Insert_Line(0.85, 0.15, 0.0, 0.85, 0.05, 0.0);
		  HC_Insert_Line(0.85, -0.15, 0.0, 0.85, -0.05, 0.0);
		  HC_Insert_Line(0.80, 0.15, 0.0, 0.90, 0.15, 0.0);
		  HC_Insert_Line(0.80, -0.15, 0.0, 0.90, -0.15, 0.0);
		  HC_Insert_Text(0.85, 0.0, 0.0, "6m");
	    HC_Close_Segment();

	  HC_Close_Segment();

	HC_Close_Segment();
}

// Delete all the HOOPS/3dGS entities and data associated with the current model
void HSoccerModel::DeleteAllEntities()
{
	HBaseModel::Flush();

	delete_vlist(m_pLayers);
	m_pLayers = new_vlist(malloc, free);
}


// our application-specific read function
HFileInputResult HSoccerModel::Read(const char * FileName) 
{   
//	CWaitCursor show_hourglass_cursor_through_this_function;

	HFileInputResult success = InputOK;

	// get the file extension
	char extension[120]; 
	HUtility::FindFileNameExtension(FileName, extension);


	// read the file into the model object's model segment
    HC_Open_Segment_By_Key(m_ModelKey);	

		HC_Open_Segment("main");
			{
				// No special read - let the base class handle
				m_bSolidModel = false;
				success = HBaseModel::Read(FileName);
			}

 		HC_Close_Segment();
    HC_Close_Segment();

    return success;
}

// our application-specific write function
bool HSoccerModel::Write(const char * FileName, HBaseView * view, 
									int version, int width, int height) 
{   
//	CWaitCursor show_hourglass_cursor_through_this_function;

	bool success = true;
 
	// get the file extension
	char extension[120]; 
	HUtility::FindFileNameExtension(FileName, extension);

	{
		if(!HBaseModel::Write(FileName, view, width, height))
			success = false;
	}
 
    return success;
}




