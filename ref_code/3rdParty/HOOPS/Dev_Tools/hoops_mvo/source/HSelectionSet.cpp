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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HSelectionSet.cpp,v 1.223 2010-11-16 02:09:36 nathan Exp $
//

// HAreaSelect.cpp : implementation of the HAreaSelect class
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HTools.h"

#include "HSelectionSet.h"
#include "HBaseView.h"
#include "HUtility.h"
#include "HUtilityAnnotation.h"
#include "HSelectionItem.h"
#include "HBaseModel.h"
#include "HPShowCache.h"

#include "vlist.h"
#include "vhash.h"

#define MVO_HIGHLIGHT_STYLE_SEGMENT	"?Style Library/mvo_highlight_style_segment"
#define MVO_TRANSPARENCY_HIGHLIGHT_SEGMENT	"?Style Library/mvo_transparent_highlight_style"
#define MVO_REFERENCE_SELECTION_SEGMENT "overwrite/selection_segment"

class HSelList: public VList<HSelectionItem *>
{
};


class HSelHash: public VHash<HC_KEY, HSelectionItem *>
{
public:
	HSelList * GetItemList()
	{
		PairList * pl=GetPairList();
		HSelList * il=new HSelList;
		int i, max=(int)pl->Count();

		for(i=0; i<max; ++i)
			il->AddLast(pl->NthItem(i)->Item());

		delete pl;
		return il;
	}

	void Flush()
	{
		MapFunction(flush_selection_map, 0);
		VHash<HC_KEY, HSelectionItem *>::Flush();
	}
private:
	static void flush_selection_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
	{
		item->UnHighlight();
		delete item;
	}
};

/////////////////////////////////////////////////////////////////////////////
// HSelectionSet
//
// Stores a list of selected HOOPS geometric primitives or segments for a view.  
// Supports adding, removing, removing all, and inquiring if and item is already 
// selected
// 
// An item being selected implies that it will be highlighted
//
// object could be easily extended to support control of highlight mode and style
// (for example, color/lineweight, boundingbox/color_change/2d_quickmove box

HSelectionSet::HSelectionSet(HBaseView* view, bool bReferenceSelection)
{
    m_pSelItemsList = 0;
	m_selected_hash = new HSelHash;
	m_list_last_updated = -1.f;
	m_hash_last_updated = -1.f;
	m_pHighlightSegsHash = new_vhash(1,malloc,free);;
	m_pView = view;
	m_selectedFaceColor.Set(255, 249, 0, 0);
	m_selectedEdgeColor.Set(255, 249, 0, 0);
	m_selectedCutFaceColor.Set(255, 249, 0, 0);
	m_selectedCutEdgeColor.Set(255, 249, 0, 0);
	m_selectedMarkerColor.Set(255, 249, 0, 0);
	m_fselectedEdgeWeight = -1.0;
	m_fselectedMarkerSize = -1.0;
 	m_bSubwindowPenetration = false;
	m_selection_level = HSelectSegment;
	m_bForceGrayScale = false;
	m_bAllowDisplacement = false;
	m_HighlightMode = bReferenceSelection ? HighlightQuickmoves : HighlightDefault;
	m_SelectionSegment = INVALID_KEY;
	m_TransparencyStyle = INVALID_KEY;
	m_fTransmission = 0.9f;
	m_pshow_cache = 0;
	m_quickmoves_type = RefSelSpriting;
	m_bHighlightRegionEdges = true;
	m_bHighlightAnnotations = true;
	m_bHighlightRegionEdgesAutoVisibility = AllEdges;
	m_bHighlightRegionFacesAutoVisibility = FacesUnmodified;
	m_bSortSelectionList = false;
	HC_Open_Segment(MVO_HIGHLIGHT_STYLE_SEGMENT);
	m_keyHighlightStyle = HC_KCreate_Segment("");
	HC_Close_Segment();
	m_subentity_face = true;
	m_subentity_edge = true;
	m_subentity_vertex = true;
	m_bNotify = true;
}


HSelectionSet::~HSelectionSet(void)
{
	DeSelectAll();
	delete m_selected_hash;
	delete m_pSelItemsList;
	if (m_SelectionSegment != INVALID_KEY)
		HC_Delete_By_Key(m_SelectionSegment);
	delete_vhash(m_pHighlightSegsHash);
}


void HSelectionSet::RegisterHighlightSeg(HC_KEY seg_key)
{
	vhash_insert(m_pHighlightSegsHash, (void*)seg_key, (void*)1);
}

void HSelectionSet::UnRegisterHighlightSeg(HC_KEY seg_key)
{
	vhash_remove(m_pHighlightSegsHash, (void*)seg_key);
}

void HSelectionSet::Init()
{
	UpdateHighlightStyle();
}

void HSelectionSet::ToggleHighlightStyle()
{
	if(GetHighlightMode()==HighlightDefault)
		SetHighlightMode(HighlightQuickmoves);
	else if(GetHighlightMode()==HighlightQuickmoves)
		SetHighlightMode(HighlightDefault);
}

bool HSelectionSet::GetIsSelection(HC_KEY key)
{
	int i=0;
	
	while(key!=0 && key!=INVALID_KEY && i<4)
	{
		if(key==GetSelectionSegment())
			return true;
		key=HC_KShow_Owner_Original_Key(key);
		++i;
	}
	
	return false;
}

void HSelectionSet::UpdateHighlightStyle()
{
	if(m_HighlightMode==InverseTransparency || m_HighlightMode==ColoredInverseTransparency)
	{
		HC_Open_Segment_By_Key(m_keyHighlightStyle);
			HC_Flush_Contents(".", "everything");
			HC_Set_Color("faces=transmission=black");
			HC_Set_Rendering_Options("no force gray scale, attribute lock=color=(faces= no transmission)");
			HC_Set_Heuristics("culling = (no maximum extent)");

			if(m_HighlightMode==ColoredInverseTransparency)
			{
				HC_Set_Color_By_Value ("geometry", "rgb", (float)m_selectedFaceColor.r()/255.0,
					(float)m_selectedFaceColor.g()/255.0,  
					(float)m_selectedFaceColor.b()/255.0); 
			
				HC_Set_Color_By_Value ("edges,lines", "rgb", (float)m_selectedEdgeColor.r()/255.0,
					(float)m_selectedEdgeColor.g()/255.0,
					(float)m_selectedEdgeColor.b()/255.0); 
				
				HC_Set_Color_By_Value ("markers", "rgb", (float)m_selectedMarkerColor.r()/255.0,
					(float)m_selectedMarkerColor.g()/255.0,
					(float)m_selectedMarkerColor.b()/255.0); 
				
				HC_Set_Color_By_Value ("cut edges", "rgb", (float)m_selectedCutEdgeColor.r()/255.0,
					(float)m_selectedCutEdgeColor.g()/255.0,
					(float)m_selectedCutEdgeColor.b()/255.0); 
				HC_Set_Color_By_Value ("cut faces", "rgb", (float)m_selectedCutFaceColor.r()/255.0,
					(float)m_selectedCutFaceColor.g()/255.0,
					(float)m_selectedCutFaceColor.b()/255.0);
			}
		HC_Close_Segment();

		HC_Open_Segment(MVO_TRANSPARENCY_HIGHLIGHT_SEGMENT);
			HC_Set_Rendering_Options("attribute lock=(visibility=edges,color=(faces=transmission))");
			HC_Set_Visibility("no edges");
		HC_Close_Segment();
	}
	else
	{
		HC_Open_Segment_By_Key(m_keyHighlightStyle);
			if (HC_Show_Existence("rendering options"))
				HC_UnSet_Rendering_Options();

			if (m_bForceGrayScale)
				HC_Set_Rendering_Options("no force gray scale");

			if (m_bAllowDisplacement)
				HC_Set_Rendering_Options("general displacement = -8");

			if(!m_bHighlightAnnotations)
				HC_Set_Conditions("disable_annotation_highlighting");

			HC_Set_Rendering_Options("image tint = yellow");
			
			HC_Set_Color_By_Value ("geometry", "rgb", (float)m_selectedFaceColor.r()/255.0,
				(float)m_selectedFaceColor.g()/255.0,  
				(float)m_selectedFaceColor.b()/255.0); 
			
			HC_Set_Color_By_Value ("edges,lines", "rgb", (float)m_selectedEdgeColor.r()/255.0,
				(float)m_selectedEdgeColor.g()/255.0,
				(float)m_selectedEdgeColor.b()/255.0); 
			
			HC_Set_Color_By_Value ("markers", "rgb", (float)m_selectedMarkerColor.r()/255.0,
				(float)m_selectedMarkerColor.g()/255.0,
				(float)m_selectedMarkerColor.b()/255.0); 
			
			HC_Set_Color_By_Value ("cut edges", "rgb", (float)m_selectedCutEdgeColor.r()/255.0,
				(float)m_selectedCutEdgeColor.g()/255.0,
				(float)m_selectedCutEdgeColor.b()/255.0); 
			HC_Set_Color_By_Value ("cut faces", "rgb", (float)m_selectedCutFaceColor.r()/255.0,
				(float)m_selectedCutFaceColor.g()/255.0,
				(float)m_selectedCutFaceColor.b()/255.0);

			HC_Set_Rendering_Options("attribute lock = color = (on, faces = no transmission)");
			HC_Set_Heuristics("culling = (no maximum extent)");

			if(m_HighlightMode==HighlightDefault)
			{
				if (m_selectedFaceColor.a() != 0) 
				{
					char color[MVO_BUFFER_SIZE];
					HCLOCALE(sprintf(color, "geometry = (transmission=(R=%1.4f G=%1.4f B=%1.4f))", 
						(float)m_selectedFaceColor.a()/255.0,  (float)m_selectedFaceColor.a()/255.0,  (float)m_selectedFaceColor.a()/255.0));
					HC_Set_Color(color);
				}
				else
				{
					if(HC_Show_Existence("color=geometry=transmission"))
						HC_UnSet_One_Color("geometry=transmission");
				}

				if (m_selectedEdgeColor.a() != 0) 
				{
					char color[MVO_BUFFER_SIZE];
					HCLOCALE(sprintf(color, "edges = (transmission=(R=%1.4f G=%1.4f B=%1.4f)), lines = (transmission=(R=%1.4f G=%1.4f B=%1.4f))", 
						(float)m_selectedEdgeColor.a()/255.0,  (float)m_selectedEdgeColor.a()/255.0,  (float)m_selectedEdgeColor.a()/255.0,
						(float)m_selectedEdgeColor.a()/255.0,  (float)m_selectedEdgeColor.a()/255.0,  (float)m_selectedEdgeColor.a()/255.0));
					HC_Set_Color(color);
				}
				else
				{
					if(HC_Show_Existence("color=edges=transmission"))
						HC_UnSet_One_Color("edges=transmission");
					if(HC_Show_Existence("color=lines=transmission"))
						HC_UnSet_One_Color("lines=transmission");
				}

				if (m_selectedMarkerColor.a() != 0) 
				{
					char color[MVO_BUFFER_SIZE];
					HCLOCALE(sprintf(color, "markers = (transmission=(R=%1.4f G=%1.4f B=%1.4f))", 
						(float)m_selectedMarkerColor.a()/255.0,  (float)m_selectedMarkerColor.a()/255.0,  (float)m_selectedMarkerColor.a()/255.0));
					HC_Set_Color(color);
				}
				else
				{
					if(HC_Show_Existence("color=markers=transmission"))
						HC_UnSet_One_Color("markers=transmission");
				}

				if (m_fselectedEdgeWeight >= 0.0f)
				{
					HC_Set_Edge_Weight(m_fselectedEdgeWeight);
					HC_Set_Line_Weight(m_fselectedEdgeWeight);
					HC_Set_Rendering_Options("attribute lock = (edge weight, line weight)");
				}
				else {
					HC_UnSet_One_Rendering_Option("attribute lock = edge weight");
					HC_UnSet_One_Rendering_Option("attribute lock = line weight");
				}
			
				if (m_fselectedMarkerSize >= 0.0f)
				{
					HC_Set_Marker_Size(m_fselectedMarkerSize);
					HC_Set_Rendering_Options("attribute lock = marker size");
				}
				else
					HC_UnSet_One_Rendering_Option("attribute lock = marker size");
			}
		HC_Close_Segment();
	}

	//reference selection
	if (m_pView->GetSceneKey() == INVALID_KEY)
		return;

	char heur[MVO_BUFFER_SIZE];

	sprintf(heur, "quick moves = %s, concave polygons", 
		(m_HighlightMode==InverseTransparency 
		|| m_HighlightMode==ColoredInverseTransparency ) ? "off" : 
		(m_quickmoves_type==RefSelSpriting ? "spriting" : "on"));
	

	if (m_SelectionSegment == INVALID_KEY)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Open_Segment(MVO_REFERENCE_SELECTION_SEGMENT);
				m_SelectionSegment = HC_KCreate_Segment("");
			HC_Close_Segment();
		HC_Close_Segment();
	}
 
	HC_Open_Segment_By_Key(m_SelectionSegment);
		HC_Set_Selectability("off");
		HC_Set_Heuristics(heur);
		HC_Set_Visibility("no shadows");
		HC_Set_Rendering_Options("general displacement = -4, no simple shadow, attribute lock=(visibility=(shadows))");
		if (!HC_Show_Existence("style"))
			HC_Style_Segment_By_Key(m_keyHighlightStyle);
 	HC_Close_Segment();	
}

void HSelectionSet::SetReferenceSelectionType(HRefSelType type)
{
	m_quickmoves_type=type;
	
	if (m_SelectionSegment == INVALID_KEY || !GetReferenceSelection())
		return;
	
	HC_Open_Segment_By_Key(m_SelectionSegment);
		if (type == RefSelSpriting)
			HC_Set_Heuristics("quick moves = spriting");
		else
			HC_Set_Heuristics("quick moves = on");
	HC_Close_Segment();
}


static int time_comparison(const void * a, const void * b)
{
	float delta=(*(HSelectionItem **)a)->GetTimeStamp() - (*(HSelectionItem **)b)->GetTimeStamp();

	if(delta<0.0f) return -1;
	else if(delta==0.0f) return 0;
	else return 1;	
}

HSelList * HSelectionSet::GetSelectionList() 
{
	if(m_list_last_updated<0.f || (m_list_last_updated != m_hash_last_updated) ||
		m_selected_hash->Count() != m_pSelItemsList->Count())
	{
		if(m_pSelItemsList)
			 delete m_pSelItemsList;
		m_pSelItemsList=m_selected_hash->GetItemList();
		m_list_last_updated=m_hash_last_updated;

		if(m_bSortSelectionList)
		{
			int i, list_size=m_pSelItemsList->Count();
			HSelectionItem ** sel_array = new HSelectionItem * [list_size];

			m_pSelItemsList->ItemsToArray(sel_array);

			qsort((void **)sel_array, list_size, sizeof(void *), time_comparison);

			m_pSelItemsList->Flush();

			for(i=0; i<list_size; ++i)
				m_pSelItemsList->AddLast(sel_array[i]);

			delete [] sel_array;
		}
	}
	return m_pSelItemsList; 
}

HC_KEY HSelectionSet::GetAt(unsigned int index)
{
	//updates the list if necessary
	if (!GetSelectionList() || m_pSelItemsList->Count()<=index)
		return INVALID_KEY;

	HSelectionItem *selectionitem = m_pSelItemsList->NthItem(index);
	if (!selectionitem)
		return INVALID_KEY;
	else
		return (selectionitem->GetKey());
}

const HSelectionItem * HSelectionSet::GetSelectionItemAt(unsigned int index)
{
	//updates the list if necessary
	if (!GetSelectionList() || m_pSelItemsList->Count()<=index)
		return 0;

	return m_pSelItemsList->NthItem(index);
}

const HSelectionItem * HSelectionSet::GetSelectionItem(HC_KEY key)
{
	HSelectionItem * tmp;

	if (VHASH_STATUS_SUCCESS == m_selected_hash->LookupItem(key, (HSelectionItem **)&tmp))
		return tmp;
	else
		return 0;
}

unsigned int HSelectionSet::GetSize() const
{
	return m_selected_hash->Count();
}


void HSelectionSet::Reset()
{
	m_selected_hash->Flush();
	HC_Show_Time(&m_hash_last_updated);

	if (m_pSelItemsList)
	{
		//we trust the hash to properly delete all the items in the list
		delete m_pSelItemsList;
		m_pSelItemsList = 0;
		m_list_last_updated = -1.f;
	}

	UpdateTransparency();

	// notify the event to view
	m_pView->Notify(HSignalDeSelectedAll, this);

	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("no force gray scale");
		HC_Close_Segment();
	}
}

void HSelectionSet::SelectSubentity(HC_KEY key, int num_include_keys, HC_KEY * include_keys, 
		int count, const int * faces, const int * vertex1, const int * vertex2, bool emit_message)
{
	if (GetSelectionLevel() == HSelectSubentity)
	{
		char	keyType[MVO_BUFFER_SIZE];	
		m_pView->SetShadowRegenerationToggle();	

 		HC_Show_Key_Type(key, keyType);
		if(!streq(keyType, "shell") && !streq(keyType, "mesh"))
			return;

		// add the selection item
		HSubentitySelItem * new_sel = new HSubentitySelItem(key, this, num_include_keys, include_keys, 
			m_subentity_face ? count : 0, m_subentity_face ? faces : 0, 
			m_subentity_edge||m_subentity_vertex ? count : 0, 
			m_subentity_edge||m_subentity_vertex ? vertex1 : 0, 
			m_subentity_edge ? vertex2 : 0, 
			m_subentity_face, m_subentity_vertex, m_subentity_edge,	true);
		new_sel->Highlight();
		m_selected_hash->InsertItem(new_sel->GetKey(), new_sel);
		HC_Show_Time(&m_hash_last_updated);

		// announce
		if (emit_message)
			m_pView->EmitSelectMessage(key, true);
	}
	else {
		if (!IsSelected(key, num_include_keys, include_keys))
			Select(key, num_include_keys, include_keys, emit_message);
	}

	// notify the event to view
	if (m_bNotify)
		m_pView->Notify(HSignalSelected, this);
		
}

void HSelectionSet::SelectRegion(HShellObject const & oShell, int num_include_keys, HC_KEY * include_keys, int region, bool emit_message)
{
	if (GetAllowRegionSelection()){
		char	keyType[MVO_BUFFER_SIZE];	
		HC_KEY * old_include_keys=0;
		m_pView->SetShadowRegenerationToggle();	

 		HC_Show_Key_Type(oShell.GetKey(), keyType);
		if (strcmp(keyType, "shell") != 0)
			return;

		if (GetReferenceSelection() && include_keys[0]!=m_pView->GetViewKey())
		{
			HC_KEY view_key = m_pView->GetViewKey();
			HC_KEY * seg_path = new HC_KEY[num_include_keys+1];
			int i;

			seg_path[0]=view_key;
			for(i=0; i<num_include_keys; ++i)
				seg_path[i+1] = include_keys[i];

			num_include_keys++;
			old_include_keys = include_keys;
			include_keys = seg_path;
		}

		// add the selection item
		HRegionSelItem * new_sel = new HRegionSelItem(oShell, this, num_include_keys, include_keys, region);
		new_sel->Highlight();
		m_selected_hash->InsertItem(new_sel->GetKey(), new_sel);
		HC_Show_Time(&m_hash_last_updated);

		if (GetReferenceSelection())
		{
			delete [] include_keys;
			include_keys = old_include_keys;
		}

		// announce
		if (emit_message)
			m_pView->EmitSelectMessage(oShell.GetKey(),true);
	}
	else {
		if (!IsSelected(oShell.GetKey(), num_include_keys, include_keys))
			Select(oShell.GetKey(), num_include_keys, include_keys, emit_message);
	}

	// notify the event to view
	if (m_bNotify)
		m_pView->Notify(HSignalSelected, this);
}

void HSelectionSet::ensure_is_segment(HC_KEY &key) const
{	
	char keyType[MVO_BUFFER_SIZE];

	HC_Show_Key_Type(key, keyType);	

	if (!streq("segment", keyType))
	{		
		HC_KEY segkey = HC_KShow_Owner_By_Key(key);		

		// climb up one more level if this is the temporary highlight key
		if (IsHighlightSegment(segkey))		
			segkey = HC_KShow_Owner_By_Key(segkey);			
		
		key = segkey;		
	}		
}

void HSelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	m_pView->SetShadowRegenerationToggle();	

	if (GetSelectionLevel()==HSelectSegment)	
		ensure_is_segment(key);

	//conditional highlighting doesn't handle repeated selection items well.
	if(m_HighlightMode == HighlightDefault && IsSelected(key, num_include_keys, include_keys))
		return;
	
	UpdateTransparency(true);

	// add the selection item
	HSmartSelItem * new_sel = new HSmartSelItem(key, this, num_include_keys, include_keys);
	new_sel->SetHighlightMode(m_HighlightMode);
	new_sel->Highlight();
	HC_Show_Time(&m_hash_last_updated);
	new_sel->SetTimeStamp(m_hash_last_updated);
	m_selected_hash->InsertItem(new_sel->GetKey(), new_sel);

	// announce
	if (emit_message)
		m_pView->EmitSelectMessage(key,true);

	UpdateTransparency();
	
	// notify the event to view
	if (m_bNotify)
		m_pView->Notify(HSignalSelected, this);
	
	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("force gray scale");
		HC_Close_Segment();
	}
}

void HSelectionSet::Select(HSelectionItem * new_sel, bool emit_message)
{
	m_pView->SetShadowRegenerationToggle();	

	UpdateTransparency(true);

	new_sel->Highlight();
	HC_Show_Time(&m_hash_last_updated);
	new_sel->SetTimeStamp(m_hash_last_updated);
	m_selected_hash->InsertItem(new_sel->GetKey(), new_sel);

	// announce
	if (emit_message)
		m_pView->EmitSelectMessage(new_sel->GetKey(),true);

	UpdateTransparency();
	
	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("force gray scale");
		HC_Close_Segment();
	}

	// notify the event to view
	if (m_bNotify)
		m_pView->Notify(HSignalSelected, this);
}

void HSelectionSet::DeSelect(HSelectionItem * remove_sel, bool emit_message)
{
	HC_KEY key = remove_sel->GetKey();

	m_pView->SetShadowRegenerationToggle();	

	HSelectionItem * tmp;	
	for(int i=0; ; ++i)
	{
		if (VHASH_STATUS_SUCCESS != 
			m_selected_hash->LookupNthItem(key, i, (HSelectionItem **)&tmp))
			break;
		
		if (tmp == remove_sel)
		{
			tmp->UnHighlight();
			m_selected_hash->RemoveNthItem(key, i, (HSelectionItem **)&tmp);
			delete tmp;
			HC_Show_Time(&m_hash_last_updated);
			break;
		}
	}
		
	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("no force gray scale");
		HC_Close_Segment();
	}

	UpdateTransparency();
	// notify the event to view
	m_pView->Notify(HSignalDeSelectedOne, this);
}

void HSelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HC_KEY * old_include_keys=0;

	if (GetSelectionLevel()==HSelectSegment)	
		ensure_is_segment(key);	

	m_pView->SetShadowRegenerationToggle();	

	if (GetReferenceSelection() && include_keys[0]!=m_pView->GetViewKey())
	{
		HC_KEY view_key = m_pView->GetViewKey();
		HC_KEY * seg_path = new HC_KEY[num_include_keys+1];
		int i;

		seg_path[0]=view_key;
		for(i=0; i<num_include_keys; ++i)
			seg_path[i+1] = include_keys[i];

		num_include_keys++;
		old_include_keys = include_keys;
		include_keys = seg_path;
	}

	//create a temporary item
	//should this be a HSelectionItem?
	HSmartSelItem remove_sel(key, this, num_include_keys, include_keys);

	if (GetReferenceSelection() && old_include_keys)
	{
		delete [] include_keys;
		include_keys = old_include_keys;
	}

	HSmartSelItem * tmp;
	int i;
	for(i=0; ; ++i)
	{
		if (VHASH_STATUS_SUCCESS != 
			m_selected_hash->LookupNthItem(remove_sel.GetKey(), i, (HSelectionItem **)&tmp))
			break;
		
		if (tmp->Equals(&remove_sel))
		{
			tmp->UnHighlight();
			m_selected_hash->RemoveNthItem(key, i, (HSelectionItem **)&tmp);
			delete tmp;
			HC_Show_Time(&m_hash_last_updated);
			if(GetSelectionLevel() != HSelectSubentity)
				break;
		}
	}
		
	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("no force gray scale");
		HC_Close_Segment();
	}

	UpdateTransparency();
	// notify the event to view
	m_pView->Notify(HSignalDeSelectedOne, this);
}

void HSelectionSet::DeSelectRegion(HShellObject const & oShell, int num_include_keys, HC_KEY * include_keys, int region, bool emit_message)
{
	HC_KEY * old_include_keys=0;
	
	m_pView->SetShadowRegenerationToggle();	

	if (GetReferenceSelection() && include_keys[0]!=m_pView->GetViewKey())
	{
		HC_KEY view_key = m_pView->GetViewKey();
		HC_KEY * seg_path = new HC_KEY[num_include_keys+1];
		int i;

		seg_path[0]=view_key;
		for(i=0; i<num_include_keys; ++i)
			seg_path[i+1] = include_keys[i];

		num_include_keys++;
		old_include_keys = include_keys;
		include_keys = seg_path;
	}

	// create a temporary selection item to find a match in the list
	HRegionSelItem remove_sel(oShell.GetKey(), this, num_include_keys, include_keys, region);

	if (GetReferenceSelection())
	{
		delete [] include_keys;
		include_keys = old_include_keys;
	}

	HRegionSelItem * tmp;
	int i;
	//find the selected region and de-select it
	for(i=0; ; ++i)
	{
		if (VHASH_STATUS_SUCCESS != 
			m_selected_hash->LookupNthItem(remove_sel.GetKey(), i, (HSelectionItem **)&tmp))
			break;
		
		if (tmp->Equals(&remove_sel))
		{
			tmp->UnHighlight();
			m_selected_hash->RemoveNthItem(remove_sel.GetKey(), i, (HSelectionItem **)&tmp);
			delete tmp;
			HC_Show_Time(&m_hash_last_updated);
			break;
		}
	}

	// notify the event to view
	m_pView->Notify(HSignalDeSelectedOne, this);
}

void HSelectionSet::DeSelectRegion(HShellObject const & oShell, int region, bool emit_message)
{
	m_pView->SetShadowRegenerationToggle();	

	HRegionSelItem * tmp;
	int i;
	//find the selected region and de-select it
	for(i=0; ; ++i)
	{
		if (VHASH_STATUS_SUCCESS != 
			m_selected_hash->LookupNthItem(oShell.GetKey(), i, (HSelectionItem **)&tmp))
			break;
		
		if (tmp->GetRegion() == region)
		{
			tmp->UnHighlight();
			m_selected_hash->RemoveNthItem(oShell.GetKey(), i, (HSelectionItem **)&tmp);
			delete tmp;
			HC_Show_Time(&m_hash_last_updated);
			break;
		}
	}

	// notify the event to view
	m_pView->Notify(HSignalDeSelectedOne, this);
}

void HSelectionSet::Select(HC_KEY key, const char* seg_path, HC_KEY include_key, HC_KEY includer_key, bool emit_message)
{  	
	m_pView->SetShadowRegenerationToggle();	
	
	if (GetSelectionLevel()==HSelectSegment)
		ensure_is_segment(key);

	// add the selection item
	HOldSelItem * new_sel = new HOldSelItem(key, this, seg_path, include_key, includer_key);
	new_sel->Highlight();
	m_selected_hash->InsertItem(key, new_sel);
	HC_Show_Time(&m_hash_last_updated);

	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("force gray scale");
		HC_Close_Segment();
	}

	// announce
	if (emit_message)
		m_pView->EmitSelectMessage(key,true);

	// notify the event to view
	if (m_bNotify)
		m_pView->Notify(HSignalSelected, this);
}



void HSelectionSet::DeSelect(HC_KEY key, bool emit_message)
{
	m_pView->SetShadowRegenerationToggle();	

	if (GetSelectionLevel()==HSelectSegment)	
		ensure_is_segment(key);	

	HSelectionItem * tmp;
	m_selected_hash->RemoveItem(key, &tmp);
	if(tmp)
	{
		tmp->UnHighlight();
		delete tmp;
		HC_Show_Time(&m_hash_last_updated);
	}
	
	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("no force gray scale");
		HC_Close_Segment();
	}

	UpdateTransparency(); 

	// notify the event to view
	m_pView->Notify(HSignalDeSelectedOne, this);
}


void HSelectionSet::DeSelectAll()
{
	Reset();

	if (m_bForceGrayScale)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("no force gray scale");
		HC_Close_Segment();
	}
	
	// notify the event to view
	m_pView->Notify(HSignalDeSelectedAll, this);
}


bool HSelectionSet::is_selected(HC_KEY key) const
{
	if (GetSelectionLevel()==HSelectSegment)	
		ensure_is_segment(key);	
	
	if(m_selected_hash->Lookup(key))
		return true;
	else 
		return false;	
}

bool HSelectionSet::IsSelected(HC_KEY key) const
{
	return is_selected(key);
}

bool HSelectionSet::IsSelected(const HSelectionItem * item) const
{
	HC_KEY key = item->GetKey();
	HSelectionItem * tmp;	

	for(int i=0; ; ++i)
	{
		if (VHASH_STATUS_SUCCESS != 
			m_selected_hash->LookupNthItem(key, i, (HSelectionItem **)&tmp))
			break;
		
		if (tmp == item)
			return true;
	}
		
	return false;
}

bool HSelectionSet::IsSelected(HC_KEY key, int num_include_keys, const HC_KEY * include_keys) const
{
	if (GetSelectionLevel()==HSelectSegment)	
		ensure_is_segment(key);	

	if (GetReferenceSelection())
	{
		HC_KEY * seg_path = new HC_KEY[++num_include_keys];
		int i;
		bool ret=false;

		seg_path[0]=m_pView->GetViewKey();
		for(i=0; i<num_include_keys-1; ++i)
			seg_path[i+1] = include_keys[i];

		//create a temporary item
		HSmartSelItem remove_sel(key, (HSelectionSet *)this, num_include_keys, seg_path);

		HSmartSelItem * tmp;
		i=0;
		do
		{
			if (VHASH_STATUS_SUCCESS != 
				m_selected_hash->LookupNthItem(key, i++, (HSelectionItem **)&tmp))
				break;
			
			if (tmp->Equals(&remove_sel))
			{
				ret=true;
				break;
			}
		}while(tmp);

		delete [] seg_path;
		return ret;
	}
	else
	{
		// figure out what condition might have been set
		return HSmartSelItem::IsHighlighted(key, this, num_include_keys, include_keys);
	}
}

bool HSelectionSet::IsRegionSelected(HC_KEY key, int num_include_keys, const HC_KEY * include_keys, int region) const
{
	if (GetReferenceSelection())
	{
		HC_KEY * seg_path = new HC_KEY[++num_include_keys];
		int i;
		bool ret=false;

		seg_path[0]=m_pView->GetViewKey();
		for(i=0; i<num_include_keys-1; ++i)
			seg_path[i+1] = include_keys[i];

		//create a temporary item
		HRegionSelItem remove_sel(key, (HSelectionSet *)this, num_include_keys, seg_path, region);

		HRegionSelItem * tmp;
		i=0;
		do
		{
			if (VHASH_STATUS_SUCCESS != 
				m_selected_hash->LookupNthItem(key, i++, (HSelectionItem **)&tmp))
				break;

			if (tmp->Equals(&remove_sel))
			{
				ret=true;
				break;
			}
		}while(tmp);

		delete [] seg_path;
		return ret;
	}
	else
	{
		return HSmartSelItem::IsRegionHighlighted(key, this, num_include_keys, include_keys, region);
	}	
}


bool HSelectionSet::IsHighlightSegment(HC_KEY segment_key) const
{
	if (vhash_lookup(m_pHighlightSegsHash,(void*)segment_key))
		return true;
	else
		return false;
}

static vhash_map_return_t delete_selection_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
{
	HBaseModel * pHModel = (HBaseModel *) user_data;
	
	item->UnHighlight();

	if (pHModel->GetModelKey() == item->GetKey())
		pHModel->Flush();
	else if(!streq(item->GetName(), "HRegionSelItem"))
		item->Delete();

	delete item;

	return VHASH_MAP_RETURN_DELETE;
}

bool HSelectionSet::DeleteSelection(bool emit_message)
{
	HBaseModel * pHModel = m_pView->GetModel();

	m_selected_hash->MapFunctionWithReturn(delete_selection_map, pHModel);

	Reset();
	
	if (emit_message)
		m_pView->EmitDeleteSelectionListMessage();

	return true;
}

class HSelItemList : public VList <HSelectionItem *> {};

class HDI_Passthrough
{
public:
	HDI_Passthrough():incl_key(0), incl_count(0), incl_dep_count(0), incl_dep(0), new_dep(0){};

	HC_KEY * incl_key;
	int incl_count;
	int * incl_dep_count;
	HC_KEY * incl_dep;
	HC_KEY * new_dep;	
	HSelItemList * patch_list;
};

static void query_include_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
{
	assert(user_data);

	int * incl_dep_count=((HDI_Passthrough *)user_data)->incl_dep_count;
	HC_KEY * incl_dep=((HDI_Passthrough *)user_data)->incl_dep;
	int incl_count=((HDI_Passthrough *)user_data)->incl_count;
	HC_KEY * incl_keys=((HDI_Passthrough *)user_data)->incl_key;
	int i;
	bool changed=false;

	for(i=0; i<incl_count; ++i)
	{
		if (item->QueryIncludeDependency(incl_keys[i], incl_dep[(*incl_dep_count)]))
		{
			++(*incl_dep_count);
			changed=true;
		}
	}

	if(changed)
		item->UnHighlight();

}

static int update_include_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
{
	assert(user_data);

	int * incl_dep_count=((HDI_Passthrough *)user_data)->incl_dep_count;
	HC_KEY * incl_dep=((HDI_Passthrough *)user_data)->incl_dep;
	HC_KEY * new_dep=((HDI_Passthrough *)user_data)->new_dep;
	int incl_count=((HDI_Passthrough *)user_data)->incl_count;
	HC_KEY * incl_keys=((HDI_Passthrough *)user_data)->incl_key;
	HSelItemList * patch_list=((HDI_Passthrough *)user_data)->patch_list;
	int i, j;
	bool changed=false;

	//bail if there's nothing to do
	if((*incl_dep_count) == 0)
		return VHASH_MAP_RETURN_CONTINUE;

	for(i=0; i<incl_count; ++i)
	{
		for(j=0; j<(*incl_dep_count); ++j)
			if(item->UpdateIncludeDependency(incl_keys[i], incl_dep[j], new_dep[j]))
				changed=true;
	}

	if(changed)
	{
		patch_list->AddLast(item);
		item->Highlight();
		return VHASH_MAP_RETURN_DELETE;
	}
	else
		return VHASH_MAP_RETURN_CONTINUE;
}

bool HSelectionSet::DeInstance(unsigned int index)
{
	return 	DeInstance((HSelectionItem *)GetSelectionItemAt(index));
}

static void patch_hash(HSelHash * selection_hash, HSelItemList * patch_list)
{
	HSelectionItem * item;

	selection_hash->Resize(selection_hash->Count());

	while(item=patch_list->RemoveFirst())
		selection_hash->InsertItem(item->GetKey(), item);
}

bool HSelectionSet::DeInstance(HSelectionItem * sel_item)
{
	// if nothing is still selected, can't de-instance
	if (GetSize() < 1)
		return false;

	// If this is not instanced, then we have nothing to do
	if (!sel_item->IsInstanced())
		return true;

	int mod = GetReferenceSelection() ? 2 : 1;
	int key_cnt = sel_item->GetIncludeCount();
	int i, j, k, pt_inc_cnt=0, incl_key_cnt=(key_cnt-mod);
	HC_KEY * pt_incl_keys = new HC_KEY[incl_key_cnt];
	HC_KEY * pt_inc = new HC_KEY[incl_key_cnt*GetSize()];
	HC_KEY * pt_new = new HC_KEY[incl_key_cnt*GetSize()];
	HC_KEY * local_pt_new = new HC_KEY[incl_key_cnt*GetSize()];
	HC_KEY * include_keys = new HC_KEY[key_cnt]; 
	HDI_Passthrough pt;

	memcpy(include_keys, sel_item->GetIncludeKeys(), key_cnt*sizeof(HC_KEY));

	memcpy(pt_incl_keys, &include_keys[mod], incl_key_cnt*sizeof(HC_KEY));
	if(include_keys[incl_key_cnt-1] == INVALID_KEY)
		--incl_key_cnt;

	pt.incl_key=pt_incl_keys;
	pt.incl_count=incl_key_cnt;
	pt.incl_dep_count=&pt_inc_cnt;
	pt.incl_dep=pt_inc;
	pt.new_dep=pt_new;
	pt.patch_list=new HSelItemList;

	m_selected_hash->MapFunction(query_include_map, &pt);

	// remove each include link from the selection item
	// the first one is model include, skip it
	// in reference selection, the first one is the view, second is the model
	for(i=mod; i<key_cnt; ++i)
	{
		HC_KEY include_key = include_keys[i];	
		HC_KEY includer_key;
		char included_seg[MVO_BUFFER_SIZE];
		
		for(j=0; j<pt_inc_cnt; ++j)
			local_pt_new[j]=INVALID_KEY;
	
		includer_key = HC_KShow_Owner_Original_Key(include_key);
		HC_Show_Include_Segment(include_key, included_seg);

		// copy the included segment
		HC_Open_Segment_By_Key(includer_key);
			HC_Copy_Segment_With_Mapping(included_seg, "*", pt_inc_cnt, pt_inc, local_pt_new);
		HC_Close_Segment();

		//since HC_Copy_Segment_With_Mapping will bash old values, we need a local array
		for(j=0; j<pt_inc_cnt; ++j)
		{
			if(local_pt_new[j]!=INVALID_KEY)
				pt_new[j]=local_pt_new[j];
		}

		//patch up include list if we've changed the key of some includes
		for(j=i+1; j<key_cnt; ++j)
		{
			for(k=0; k<pt_inc_cnt; ++k)
			{
				if(include_keys[j]==pt_inc[k] && local_pt_new[k]!=INVALID_KEY)
				{
					include_keys[j]=local_pt_new[k];
					pt_new[k]=INVALID_KEY;
				}
			}
		}
		
		// kill the include link
		HC_Delete_By_Key(include_key);
	}
	
	m_selected_hash->MapFunctionWithReturn(update_include_map, &pt);

	patch_hash(m_selected_hash, pt.patch_list);

	delete [] include_keys;
	delete [] pt_inc;
	delete [] local_pt_new;
	delete [] pt_new;
	delete [] pt_incl_keys;
	delete pt.patch_list;
	
	return true;
}

void HSelectionSet::SetSubwindowPenetration(bool allow) 
{ 
	m_bSubwindowPenetration = allow;
}	

void HSelectionSet::SetSelectionLevel(HSelectLevel level)
{	
	m_selection_level = level;	
}

void HSelectionSet::SetAllowEntitySelection(bool allow) 
{ 
	if (allow)
		m_selection_level = HSelectEntity;
	else
		if (m_selection_level == HSelectEntity)
			m_selection_level = HSelectSegment;
}	

void HSelectionSet::SetAllowSubentitySelection(bool allow) 
{ 
	if (allow)
		m_selection_level = HSelectSubentity;
	else
		if (m_selection_level == HSelectSubentity)
			m_selection_level = HSelectSegment;
}	

void HSelectionSet::SetAllowRegionSelection(bool allow) 
{
	DeSelectAll();
	if (allow)
		m_selection_level = HSelectRegion;
	else
		if (m_selection_level == HSelectRegion)
			m_selection_level = HSelectSegment;
}	


void HSelectionSet::SetGrayScale(bool grayScale)
{
	m_bForceGrayScale = grayScale; 
	if (!m_bForceGrayScale)
	{
 		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("no force gray scale");
		HC_Close_Segment();
	}
	else
	{
		if (GetSize())
		{		
 			HC_Open_Segment_By_Key(m_pView->GetSceneKey());
				HC_Set_Rendering_Options("force gray scale");
			HC_Close_Segment();
		}

	}
	UpdateHighlightStyle();
}

static void cleanup_pshow_cache(HPShowCache * item, HC_KEY key, void const * const user_data)
{
	if(item)
		delete item;
	item=0;
}


void HSelectionSet::FlushPShowCache()
{ 
	if(!m_pshow_cache)
		return;
	
	m_pshow_cache->MapFunction(cleanup_pshow_cache, 0);

	delete m_pshow_cache;
	m_pshow_cache=0;
}



static void update_highlighting_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
{
	((HSmartSelItem*)item)->UnHighlight();
	((HSmartSelItem*)item)->Highlight();
}

void HSelectionSet::UpdateHighlighting()
{
	if(!GetReferenceSelection())
		return;

	UpdateTransparency(true);
	m_selected_hash->MapFunction(update_highlighting_map, 0);
	UpdateTransparency();

}


static void unhighlight_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
{
	((HSmartSelItem*)item)->UnHighlight();
}

static void highlight_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
{
	if(user_data)
		((HSmartSelItem*)item)->SetHighlightMode(*(HSelectionHighlightMode *)user_data);
	((HSmartSelItem*)item)->Highlight();
}


void HSelectionSet::SetHighlightMode(HSelectionHighlightMode m)
{
	m_selected_hash->MapFunction(unhighlight_map, 0);
	UpdateTransparency(true);

	m_HighlightMode = m;
	UpdateHighlightStyle();

	m_selected_hash->MapFunction(highlight_map, &m_HighlightMode);
	
	UpdateTransparency();

	if (m_bForceGrayScale && GetSize()>0)
	{
		HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HC_Set_Rendering_Options("force gray scale");
		HC_Close_Segment();
	}
}

void HSelectionSet::SetHighlightTransparency(float trans)
{
	if(trans>1.0f) trans = 1.0f;
	else if(trans<0.0f) trans = 0.0f;

	m_fTransmission = trans;

	UpdateTransparency();	
}

void HSelectionSet::UpdateTransparency(bool force_flush)
{
	if(m_HighlightMode==InverseTransparency || m_HighlightMode==ColoredInverseTransparency)
	{
		if(GetSize()>0 && !force_flush)
		{
			char color[MVO_BUFFER_SIZE];
			HCLOCALE(sprintf(color, "faces=transmission=(R=%f G=%f B=%f)", m_fTransmission, m_fTransmission, m_fTransmission));

			HC_Open_Segment(MVO_TRANSPARENCY_HIGHLIGHT_SEGMENT);
				HC_Set_Color(color);
			HC_Close_Segment();

			HC_KEY model_owner = HC_KShow_Owner_Original_Key(m_pView->GetIncludeLinkKey());
			if(m_TransparencyStyle==INVALID_KEY && !HC_Show_Existence_By_Key(model_owner, "style"))
			{
				HC_Open_Segment_By_Key(model_owner);
					m_TransparencyStyle=HC_KStyle_Segment(MVO_TRANSPARENCY_HIGHLIGHT_SEGMENT);
				HC_Close_Segment();
			}
		}
		else
		{
			if(m_TransparencyStyle!=INVALID_KEY)
			{
				HC_Delete_By_Key(m_TransparencyStyle);
				m_TransparencyStyle=INVALID_KEY;
			}
		}
	}

}

class HSB_Passthrough
{
public:
	HSB_Passthrough(HPoint * in_min, HPoint * in_max) : min(in_min), max(in_max), initialized(false) {};
	HSB_Passthrough() : min(0), max(0), initialized(false) {};

	bool initialized;
	HPoint * min;
	HPoint * max;
};

static HPoint min_point(int count, HPoint const * list)
{
	if(count == 0)
		return HPoint(0,0,0);
	HPoint min = list[0];
	for(int i=1; i<count; ++i)
	{
		if(list[i].x < min.x) min.x = list[i].x;
		if(list[i].y < min.y) min.y = list[i].y;
		if(list[i].z < min.z) min.z = list[i].z;
	}
	return min;
}

static HPoint max_point(int count, HPoint const * list)
{
	if(count == 0)
		return HPoint(0,0,0);
	HPoint max = list[0];
	for(int i=1; i<count; ++i)
	{
		if(list[i].x > max.x) max.x = list[i].x;
		if(list[i].y > max.y) max.y = list[i].y;
		if(list[i].z > max.z) max.z = list[i].z;
	}
	return max;
}

static void get_bounding_map(HSelectionItem * item, HC_KEY key, void const * const user_data)
{
	HSmartSelItem * smart_item = (HSmartSelItem *)item;
	HSB_Passthrough * pt = (HSB_Passthrough *)user_data;
	HPoint min = *pt->min;
	HPoint max = *pt->max;
	char type[MVO_BUFFER_SIZE], bounding_info[MVO_BUFFER_SIZE];
	float matrix[16];
	int incl_count = smart_item->GetIncludeCount(), path_count = incl_count+2;
	HC_KEY seg_key, * incl_path, * path;

	HC_Show_Key_Type(key, type);

	//only consider types that could have a bounding
	if(!streq(type, "segment") && !streq(type, "reference")
		&& !streq(type, "shell") && !streq(type, "mesh"))
		return;

	//set up path for a pshow
	if(streq(type, "segment"))
		seg_key = key;
	else
		seg_key = HC_KShow_Owner_Original_Key(key);
	incl_path = new HC_KEY[incl_count];
	path = new HC_KEY[path_count];
	smart_item->GetIncludeKeys(incl_path);
	path[0]=seg_key;
	for(int i=1; i<incl_count; ++i)
		path[i]=incl_path[incl_count-i];
	path[path_count-2] = HC_KShow_Owner_Original_Key(path[path_count-3]);
	path[path_count-1] = INVALID_KEY;

	HC_Show_Bounding_Info_By_Key(key, bounding_info);

	// if we're looking at a reference, try the referee
	while (streq(bounding_info, "") && streq(type, "reference")) 
	{
		int count;
		HC_Show_Reference_Keys_Count (key, &count);
		if (count == 1) 
		{
			key = HC_KShow_Reference_Geometry(key);
			//only consider types that could have a bounding
			HC_Show_Key_Type(key, type);
			if(!streq(type, "segment") && !streq(type, "reference")
				&& !streq(type, "shell") && !streq(type, "mesh"))
				goto Cleanup;
			HC_Show_Bounding_Info_By_Key(key, bounding_info);
		}
		else
			goto Cleanup;
	}
	
	//figure out whether we have bounding info at all
	if(bounding_info[0]!='\0')
	{
		HPoint pts[2], bbox[8];
		HC_PShow_Net_Modelling_Matrix(path_count, path, matrix);
		
		//get the bounding box
		if(strstr(bounding_info, "sphere"))
		{
			float radius;
			HPoint center;

			HC_Show_Bounding_Sphere_By_Key(key, &center, &radius);

			pts[0].x = center.x - radius;		pts[0].y = center.y - radius;		pts[0].z = center.z - radius;
			pts[1].x = center.x + radius;		pts[1].y = center.y + radius;		pts[1].z = center.z + radius;
		}
		else if(strstr(bounding_info, "cuboid"))
			HC_Show_Bounding_Cuboid_By_Key(key, &pts[0], &pts[1]);

		bbox[0].x=pts[0].x;	bbox[0].y=pts[0].y;	bbox[0].z=pts[0].z;
		bbox[1].x=pts[0].x;	bbox[1].y=pts[0].y;	bbox[1].z=pts[1].z;
		bbox[2].x=pts[1].x;	bbox[2].y=pts[0].y;	bbox[2].z=pts[1].z;
		bbox[3].x=pts[1].x;	bbox[3].y=pts[0].y;	bbox[3].z=pts[0].z;
		bbox[4].x=pts[0].x;	bbox[4].y=pts[1].y;	bbox[4].z=pts[0].z;
		bbox[5].x=pts[0].x;	bbox[5].y=pts[1].y;	bbox[5].z=pts[1].z;
		bbox[6].x=pts[1].x;	bbox[6].y=pts[1].y;	bbox[6].z=pts[1].z;
		bbox[7].x=pts[1].x;	bbox[7].y=pts[1].y;	bbox[7].z=pts[0].z;
		
		HC_Compute_Transformed_Points(8, bbox, matrix, bbox);

		pts[0] = min_point(8, bbox);
		pts[1] = max_point(8, bbox);

		//merge it in
		if(pt->initialized)
		{
			if(pts[0].x < min.x) min.x = pts[0].x;
			if(pts[0].y < min.y) min.y = pts[0].y;
			if(pts[0].z < min.z) min.z = pts[0].z;
			if(pts[1].x > max.x) max.x = pts[1].x;
			if(pts[1].y > max.y) max.y = pts[1].y;
			if(pts[1].z > max.z) max.z = pts[1].z;
		}
		else
		{
			min = pts[0];
			max = pts[1];
			pt->initialized = true;
		}

		*pt->min = min;
		*pt->max = max;
	}

Cleanup:
	delete [] path;
	delete [] incl_path;
}

void HSelectionSet::GetSelectionBounding(HPoint * minimum, HPoint * maximum) const
{
	HSB_Passthrough pt(minimum, maximum);
	m_selected_hash->MapFunction(get_bounding_map, &pt);
}




