// HSpheresSelectionSet.cpp : implementation of the HSpheresSelectionSet class
// 
#include <string.h>

#include "HSpheresSelectionSet.h"
#include "HSpheresModel.h"
#include "HSpheresView.h"

#include "vlist.h"

HSpheresSelectionSet::HSpheresSelectionSet(HBaseView* view) : HSelectionSet(view)
{
	m_SelectLevel = HSelectSegment;
}

HSpheresSelectionSet::~HSpheresSelectionSet()
{
}

void HSpheresSelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
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



void HSpheresSelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
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

void HSpheresSelectionSet::DeSelect(HC_KEY key, bool emit_message)
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




// If it is a call to select something from an HNet message,
// bypass our selection functionality and just call the 
// vanilla Select. JUST SELECT THIS KEY!
// This is to work around the case where the master client
// is in one selection mode (face) and slave is in another (body)

void HSpheresSelectionSet::SelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);
}


void HSpheresSelectionSet::DeSelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}


