// HSoccerView.cpp : implementation of the HSoccerView class
// 

// Standard includes
// #include "StdAfx.h"
#include "Resource.h"
#include <assert.h>
#include <math.h>
#include "hc.h"

#include "HSoccerView.h"
#include "HSoccerModel.h"
#include "HSoccerSelectionSet.h"
#include "HSelectionItem.h"

#include "HSharedKey.h"

#include "HUtility.h"

#include "HSnapGrid.h"
#include "vlist.h"


HSoccerView::HSoccerView(HBaseModel *model,
    const char * 		alias,	
    const char *		driver_type,
    const char *		instance_name,
    void *				window_handle,
    void *				colormap,
	void *				clip_override) : HBaseView(model, alias, driver_type, instance_name, window_handle, colormap, clip_override)

{
	m_pSnapGrid = 0;
	m_bSnap = false;
}

HSoccerView::~HSoccerView()	
{
	H_SAFE_DELETE(m_pSelection);
	H_SAFE_DELETE(m_pSnapGrid);
}


// app-specific init function
void HSoccerView::Init()
{
	HPoint origin, ref1, ref2;
	bool success = false;

	origin.Set(0.0f, 0.0f, 0.0f);
	ref1.Set(0.05f, 0.0f, 0.0f);
	ref2.Set(0.0f, 0.05f, 0.0f);

	// call base's init function first to get the default HOOPS hierarchy for the view
	HBaseView::Init();

	// create our app-specific Selection object and initialize
	m_pSelection = new HSoccerSelectionSet(this);
    m_pSelection->Init();

	// create and init the grid object
	m_pSnapGrid = new HSnapGrid(this);
	success = m_pSnapGrid->Create(&origin, &ref1, &ref2);

	if (success)
	{
		HC_Open_Segment_By_Key(m_pSnapGrid->GetGridSegment());
	      HC_Set_Rendering_Options("depth range=(0.95,1.0)" );
		  HC_Set_Color("edges = light gray");
		HC_Close_Segment();
	}

	// TODO: Add your initialization here
	// set up some scene defaults
	HC_Open_Segment_By_Key(m_SceneKey);
	  HC_Set_Color("edges = blue");
	  HC_Set_Text_Font("name = arial.ttf, size = .05 oru");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(m_WindowspaceKey);
	  HC_Set_Color("edges = lines = red");
	  HC_Set_Edge_Weight(2.0);
	  HC_Set_Line_Weight(2.0);
	HC_Close_Segment();
}

// do some view-dependent text work
// this code assumes that the 'transforms' option of HC_Set_Text_Font is set to 'off'
void HSoccerView::ProcessText()
{
	float xfrac, yfrac;

	HPoint win_ref_pt, obj_ref_pt;

	HC_KEY keys[2];
    keys[0] = GetModelKey();
    keys[1] = m_SceneKey;

	// call Update() so that the Compute fcns below have all the info they need to work properly
	Update();

	HC_Open_Segment_By_Key(GetModelKey());
	  HC_Open_Segment("title");

	    // calculate the extents of the title text
	    HC_Compute_Text_Extent_By_Path(2, keys, "Sample Soccer Field", &xfrac, &yfrac);

		win_ref_pt.x = xfrac*1.1;
		win_ref_pt.y = yfrac*1.1;
		win_ref_pt.z = 0.0;

		// convert the coordinates into object space
		HC_Compute_Coordinates_By_Path(2, keys, "outer window", &win_ref_pt, "object", &obj_ref_pt);
 
		// base the border rectangle off of the object space coordinates computed above
		HUtility::InsertRectangle(".", -obj_ref_pt.x, 0.8 + obj_ref_pt.y, obj_ref_pt.x, .8 - obj_ref_pt.y);

	  HC_Close_Segment();
    HC_Close_Segment();
}


void HSoccerView::DeleteLayers()
{
	HSelectionItem * iSel;

	HSoccerModel *pModel = (HSoccerModel *)GetModel();

	HSoccerSelectionSet *pSelection = (HSoccerSelectionSet *)GetSelection();

	pSelection->DeleteSelection();

	// update the view
	Update();
}



