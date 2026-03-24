// HSoccerSelectionSet.cpp : implementation of the HPSelectionSet class
// 

#include "Resource.h"

#include "HSoccerSelectionSet.h"
#include "HSoccerModel.h"
#include "HSoccerView.h"
#include "HSelectionItem.h"
#include "vlist.h"

HSoccerSelectionSet::HSoccerSelectionSet(HBaseView* view) : HSelectionSet(view)
{
	m_SelectLevel = HSelectSegment;
}

HSoccerSelectionSet::~HSoccerSelectionSet()
{
}

void HSoccerSelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSoccerModel *pModel = (HSoccerModel *)m_pView->GetModel();
	struct vlist_s *pLayers = pModel->GetLayerList();

	// if we are in Segment level selection, proceed with key filtering
	if (m_SelectLevel == HSelectSegment)
	{
		// if the key doesn't refer to a 'layer' segment, get it's owner (moving up the tree as necessary)
		while (!vlist_item_exists(pLayers, (void *)key) && (key != -1))
			key = HC_KShow_Owner_By_Key(key);
	}

	// Make sure we actually have a layer segment, 
	// If so, then call the base class to select, and bring the selected segment (layer) to the front	
	if (key != -1)
	{
		HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);
	}

	m_pView->Update();
}

void HSoccerSelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSoccerModel *pModel = (HSoccerModel *)m_pView->GetModel();
	struct vlist_s *pLayers = pModel->GetLayerList();

	// if we are in Segment level selection, proceed with key filtering
	if (m_SelectLevel == HSelectSegment)
	{
		// if the key doesn't refer to a segment, get it's owner (moving up the tree as necessary)
		while (!vlist_item_exists(pLayers, (void *)key) && (key != -1))
			key = HC_KShow_Owner_By_Key(key);	
	}
	
	// make sure we actually have a layer segment, and call the base class selection method to deselect the segment
	if (key != -1)
		HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);

	m_pView->Update();
}



bool HSoccerSelectionSet::IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys) const
{
	HSoccerModel *pModel = (HSoccerModel *)m_pView->GetModel();
	struct vlist_s *pLayers = pModel->GetLayerList();

	// if we are in Segment level selection, proceed with key filtering
	if (m_SelectLevel == HSelectSegment)
	{
		// if the key doesn't refer to a segment, get it's owner (moving up the tree as necessary)
		while (!vlist_item_exists(pLayers, (void *)key) && (key != -1))
			key = HC_KShow_Owner_By_Key(key);
	}
	
	if (key != -1)
		return HSelectionSet::IsSelected(key, num_include_keys, include_keys);
	else
		return false;
}


void HSoccerSelectionSet::DeSelectAll()
{
	HSoccerModel *pModel = (HSoccerModel *)m_pView->GetModel();
	struct vlist_s *pLayers = pModel->GetLayerList();

	UNREFERENCED(pLayers);

	HSelectionSet::DeSelectAll();

	m_pView->Update();
}



// If it is a call to select something from an HNet message,
// bypass our selection functionality and just call the 
// vanilla Select. JUST SELECT THIS KEY!
// This is to work around the case where the master client
// is in one selection mode (face) and slave is in another (body)

void HSoccerSelectionSet::SelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);
}


void HSoccerSelectionSet::DeSelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}


