// HAnalysisView.cpp : implementation of the HAnalysisView class
// 
// Standard includes
#include <assert.h>
#include <math.h>
#include <stdlib.h>


#include "hc.h"
#include "HUtilityGeometryCreation.h"

#include "HAnalysisView.h"
#include "HAnalysisModel.h"
#include "HAnalysisSelectionSet.h"

#include "HSharedKey.h"


HAnalysisView::HAnalysisView(HBaseModel *model,
    const char * 		alias,	
    const char *		driver_type,
    const char *		instance_name,
    void *				window_handle,
    void *				colormap,
	void *				clip_override) : HBaseView(model, alias, driver_type, instance_name, window_handle, colormap, clip_override)

{
}

HAnalysisView::~HAnalysisView()
{
}

// app-specific init function
void HAnalysisView::Init()
{
	// call base's init function first to get the default HOOPS hierarchy for the view
	HBaseView::Init();

	// create our app-specific Selection object and initialize
	m_pSelection = new HAnalysisSelectionSet(this);
    m_pSelection->Init();

}

void HAnalysisView::MapData(HC_KEY const key)
{
	HShellVertexData shell_vertex_data;
	shell_vertex_data.SetKey(key);
	HUtilityGeometryCreation::ComputeFIndexDemoData(&shell_vertex_data);
}

// Creates an artificial set of color index values and applies it to the shells in the selection list
bool HAnalysisView::MapSelectionSet()
{
	bool retval = false;
	HSelectionSet * selset = GetSelection();
	int i, count = 0;
	if(selset && (count = selset->GetSize()) > 0){
		HC_KEY * keys = new HC_KEY[count];

		for(i=0; i<count; ++i)
			keys[i] = selset->GetAt(i);
		
		selset->DeSelectAll();

		for(i=0; i<count; ++i){
			char type[32] = {""};
			HC_Show_Key_Type(keys[i], type);
			if(streq(type, "segment")){
				HC_Open_Segment_By_Key(keys[i]);{
					int search_count = 0;
					HC_Begin_Contents_Search(".", "shells, meshes");{
						HC_KEY key = INVALID_KEY;
						HC_Find_Contents(type, &key);
						retval = true;
						MapData(key);
					}HC_End_Contents_Search();
				}HC_Close_Segment();
			}
			else{
				retval = true;
				MapData(keys[i]);
			}
		}
		delete [] keys;
		SetColorIndexInterpolation(true, false);
		Update();
	}
	return retval;
}

void HAnalysisView::QuadInterpolateData(HC_KEY const key)
{
	// open the shell's containing segment
	HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(key));
	  HUtilityGeometryCreation::GenerateFEAShell(key, false, "bilinear");
    HC_Close_Segment();

	// delete the original shell
	HC_Delete_By_Key(key);
}

bool HAnalysisView::QuadInterpolateSelectionSet()
{
	bool retval = false;
	HSelectionSet * selset = GetSelection();
	int i, selection_count = 0;
	if(selset && (selection_count = selset->GetSize()) > 0){
		HC_KEY * keys = new HC_KEY[selection_count];

		for(i=0; i<selection_count; ++i)
			keys[i] = selset->GetAt(i);
		
		selset->DeSelectAll();

		for(i=0; i<selection_count; ++i){
			char type[32] = {""};
			HC_Show_Key_Type(keys[i], type);
			if(streq(type, "segment")){
				HC_Open_Segment_By_Key(keys[i]);{
					int search_count = 0;
					HC_Begin_Contents_Search(".", "shells, meshes");{
						HC_KEY key = INVALID_KEY;
						HC_Find_Contents(type, &key);
						retval = true;
						MapData(key);
						QuadInterpolateData(key);
					}HC_End_Contents_Search();
				}HC_Close_Segment();
			}
			else{
				retval = true;
				QuadInterpolateData(keys[i]);
			}
		}
		delete [] keys;
		SetColorIndexInterpolation(true, false);
		Update();
	}
	return retval;
}

bool HAnalysisView::AnimateSelectionSet()
{
	bool retval = false;
	HSelectionSet * selset = GetSelection();
	int i, selection_count = 0;
	if(selset && (selection_count = selset->GetSize()) > 0){
		HC_KEY * keys = new HC_KEY[selection_count];
		HShellVertexData * shell_vertex_data = new HShellVertexData[selection_count];
		char type[32] = {""};

		for(i=0; i<selection_count; ++i){
			keys[i] = selset->GetAt(i);
			HC_Show_Key_Type(keys[i], type);
			if(!streq(type, "segment")){
				shell_vertex_data[i].SetKey(keys[i]);
				HUtilityGeometryCreation::ComputeFIndexDemoData(&shell_vertex_data[i]);
			}
		}			
		selset->DeSelectAll();

		for ( int t=0; t<30; t++ ){
			for(i=0; i<selection_count; ++i){
				HC_Show_Key_Type(keys[i], type);
				if(streq(type, "segment")){
					HC_Open_Segment_By_Key(keys[i]);{
						int search_count = 0;
						HC_Begin_Contents_Search(".", "shells, meshes");{
							HC_KEY key = INVALID_KEY;
							HC_Show_Contents_Count(&search_count);
							HShellVertexData found_shell;
							int j=0;
							for(j; j<search_count; ++j){
								HC_Find_Contents(type, &key);
								found_shell.SetKey(key);
								HUtilityGeometryCreation::ComputeFIndexDemoData(&found_shell);
								if(found_shell.GetVertexCount() > 0){
									retval = true;
									HC_MSet_Vertex_Colors_By_FIndex(found_shell.GetKey(),
																	"faces, edges, markers",
																	0, 
																	found_shell.GetVertexCount(),
																	found_shell.GetFIndexData() +t);
								}
							}

						}HC_End_Contents_Search();
					}HC_Close_Segment();
				}
				else if(shell_vertex_data[i].GetVertexCount() > 0){
					retval = true;
					HC_MSet_Vertex_Colors_By_FIndex(shell_vertex_data[i].GetKey(),
													"faces, edges, markers",
													0, 
													shell_vertex_data[i].GetVertexCount(),
													shell_vertex_data[i].GetFIndexData() +t);
				}
			}
			Update();
			USleep(50);
		}
		delete [] shell_vertex_data;
		delete [] keys;
	}
	return retval;
}



void HAnalysisView::SetVisibilityEdges(bool on_off)
{
    HC_Open_Segment_By_Key (GetSceneKey());
        if (on_off) 
            HC_Set_Visibility ("edges = on");
        else 
            HC_Set_Visibility ("edges = off");
    HC_Close_Segment ();
}
