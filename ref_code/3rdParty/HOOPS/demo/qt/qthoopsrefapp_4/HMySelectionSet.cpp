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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HMySelectionSet.cpp,v 1.7 2009-09-10 17:56:52 conor Exp $
//


#include "HMySelectionSet.h"
#include "HTools.h"
#include "HBaseView.h"

#include "hc.h"

#include <string.h>

HMySelectionSet::HMySelectionSet(HBaseView* view):HSelectionSet(view)
{
	m_SelectLevel = SegmentSelectLevel;
}


void HMySelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (m_SelectLevel == SegmentSelectLevel) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.

		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
		{
			char segname[MVO_BUFFER_SIZE];
			HC_KEY segkey;
			
			segkey = HC_KShow_Owner_By_Key(key);
			HC_Show_Owner_By_Key(key, segname);

			// climb up one more level if this is the temporary highlight key
			if( IsHighlightSegment(segkey) )
			{
				segkey = HC_KShow_Owner_By_Key(segkey);
				HC_Show_Owner_By_Key(segkey, segname);
			}
			key=segkey;
		}
	}
	
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);

}


void HMySelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (m_SelectLevel == SegmentSelectLevel) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.

		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
		{
			key = HC_KShow_Owner_By_Key(key);
			// climb up one more level if this is the temporary highlight key
			if( IsHighlightSegment(key) )
				key = HC_KShow_Owner_By_Key(key);
		}
		
	}

	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}


bool HMySelectionSet::IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (m_SelectLevel == SegmentSelectLevel) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.

		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
		{
			key = HC_KShow_Owner_By_Key(key);

			// climb up one more level if this is the temporary highlight key
			if( IsHighlightSegment(key) )
				key = HC_KShow_Owner_By_Key(key);
		}
		
	}
		
	return HSelectionSet::IsSelected(key, num_include_keys, include_keys);

}

// NOTE: This function is depricated
void HMySelectionSet::Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (m_SelectLevel == SegmentSelectLevel) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.
		HC_Show_Key_Type(key, keyType);
		
		if (!streq("segment", keyType))
			key = HC_KShow_Owner_By_Key(key);
	}
	
	HSelectionSet::Select(key, segpath, include_key, includer_key, emit_message);

	if (emit_message)
		m_pView->EmitSelectMessage(key,true);
}


void HMySelectionSet::DeSelect(HC_KEY key, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (m_SelectLevel == SegmentSelectLevel) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.
		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
			key = HC_KShow_Owner_By_Key(key);	
	}
	
	HSelectionSet::DeSelect(key);

 	if (emit_message)
		m_pView->EmitSelectMessage(key,false);
	
}


