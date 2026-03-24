// HSpheresView.cpp : implementation of the HSpheresView class
// 

// Standard includes

#include <assert.h>
#include <math.h>
#include "hc.h"

#include "HSpheresView.h"
#include "HSpheresModel.h"
#include "HSpheresSelectionSet.h"

#include "HSharedKey.h"
#include "HMarkupManager.h"


HSpheresView::HSpheresView(HBaseModel *model,
    const char * 		alias,	
    const char *		driver_type,
    const char *		instance_name,
    void *				window_handle,
    void *				colormap,
	void *				clip_override) : HBaseView(model, alias, driver_type, instance_name, window_handle, colormap, clip_override)

{
}

HSpheresView::~HSpheresView()
{
	H_SAFE_DELETE(m_pSelection);
}


// app-specific init function
void HSpheresView::Init()
{
	HPoint color;

	color.Set(0.0, 1.0, 0.0);

	// call base's init function first to get the default HOOPS hierarchy for the view
	HBaseView::Init();

	HMarkupManager * mgr = GetMarkupManager();
		
	HC_Open_Segment_By_Key(mgr->GetMarkupKey());
	  //HC_Set_Color("text = green, lines = red, faces = light blue");
	  //HC_Set_Rendering_Options("attribute lock = color");
    HC_Close_Segment();

	// create our app-specific Selection object and initialize
	m_pSelection = new HSpheresSelectionSet(this);
    m_pSelection->Init();

	// add custom initialization code here
	HC_Open_Segment_By_Key(m_ViewKey);
	  HC_Set_Rendering_Options("hlro = (visibility = on, pattern = 4)");
	  HC_Set_Color("text = red, lines = blue");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(m_SceneKey);
	  HC_Set_Text_Font("size = .02 oru, transforms = on, name = arial.ttf");
	  HC_Insert_Text(0.0, -0.1, 0.0, "text1");
	  HC_Insert_Text(0.0, 0.0, 0.0, "text2");
	  HC_Insert_Text(0.0, 0.1, 0.0, "text3");
	HC_Close_Segment();

	//SetHideOverlappedText(true);

}

void HSpheresView::ChangeMaterial()
{
	HSpheresSelectionSet * selection = (HSpheresSelectionSet*)GetSelection();

	while( selection->GetSize() > 0 )
	{
		HC_KEY key = selection->GetAt(0);

		// DeSelect the item first
		selection->DeSelect(key);

		// open up the segment and set the new color
		HC_Open_Segment_By_Key(key);
		  HC_Set_Color_By_Value("faces", "RGB", 0.0, 0.0, 1.0);
		  HC_Set_Color("faces = (transmission = gray)");
		HC_Close_Segment();
	}

	// redraw the scene to reflect the attributes changes
	Update();
}



