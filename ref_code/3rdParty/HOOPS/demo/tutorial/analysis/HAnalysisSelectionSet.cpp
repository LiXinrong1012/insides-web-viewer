// HAnalysisSelectionSet.cpp : implementation of the HPSelectionSet class
// 

#include <string.h>

#include "HAnalysisSelectionSet.h"
#include "HAnalysisModel.h"
#include "HAnalysisView.h"

#include "vlist.h"

HAnalysisSelectionSet::HAnalysisSelectionSet(HBaseView* view) : HSelectionSet(view)
{
	m_SelectLevel = HSelectEntity;
}

HAnalysisSelectionSet::~HAnalysisSelectionSet()
{
}



void HAnalysisSelectionSet::Select( HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	// if we are in 'Segment' selection mode, do some checking
	if (m_SelectLevel == HSelectSegment) 
	{
		// Get the key type 
		HC_Show_Key_Type(key, keyType);

		// if they key isn't to a segment (which means it's to an entity)
		// then we get its parent
		if (!streq("segment", keyType))
			key = HC_KShow_Owner_By_Key(key);
	}
	
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);
}



void HAnalysisSelectionSet::DeSelect( HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];
	
	// if we are in 'Segment' selection mode, do some checking
	if (m_SelectLevel == HSelectSegment) // nonzero if NOT a segment
	{
		// Get the key type 
		HC_Show_Key_Type(key, keyType);

		// if they key isn't to a segment (which means it's to an entity)
		// then we get its parent
		if (!streq("segment", keyType))
			key = HC_KShow_Owner_By_Key(key);
	}
	
	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}

void HAnalysisSelectionSet::DeSelect(HC_KEY key, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];
	
	// if we are in 'Segment' selection mode, do some checking
	if (m_SelectLevel == HSelectSegment) // nonzero if NOT a segment
	{
		// Get the key type 
		HC_Show_Key_Type(key, keyType);

		// if they key isn't to a segment (which means it's to an entity)
		// then we get its parent
		if (!streq("segment", keyType))
			key = HC_KShow_Owner_By_Key(key);
	}
	
	HSelectionSet::DeSelect(key, emit_message);
}



// If it is a call to select something from HNet message,
// by pass our selection functionality and just call the 
// vanilla Select. JUST SELECT THIS KEY!
// This is to work around the case where the master client
// is in some selection mode (face) and slave is in some (body)
void HAnalysisSelectionSet::SelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::Select( key, num_include_keys, include_keys,  emit_message);
}

//	See the Description for SelectFromMessage
void HAnalysisSelectionSet::DeSelectFromMessage( HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::DeSelect( key, num_include_keys, include_keys,  emit_message);
}
