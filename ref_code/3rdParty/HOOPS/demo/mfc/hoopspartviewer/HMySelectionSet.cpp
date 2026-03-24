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
// $Header: /files/homes/master/cvs/hoops_master/hoopspartviewer/HMySelectionSet.cpp,v 1.10 2007-08-16 19:57:02 nathan Exp $
//

// standard includes
#include "stdafx.h"
#include "resource.h"
#include <string.h>
#include <hc.h>

#include "HSInclude.h"
#include "CSolidHoopsApp.h"
#include "CSolidHoopsFrm.h"
#include "CSolidHoopsView.h"
#include "HMySelectionSet.h"
#include "CSegmentBrowserDlg.h"

#include "htools.h"
#include "hutility.h"

extern CSolidHoopsApp theApp;

HMySelectionSet::HMySelectionSet(HBaseView* view, bool bReferenceSelection)
	:HSSelectionSet(view, bReferenceSelection)
{
	m_SelectLevel = SEGMENT_TYPE;
}


void HMySelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (!m_pView->GetEmitMessageFunction() || emit_message)	//disregard segment level setting if messsage
															//from other client			
	{
		if (!GetAllowEntitySelection()) // nonzero if NOT a segment
		{
			// the key is to a geometric entity.  If we are in segment selection mode,
			// then we need to get the key to its parent segment.

			HC_Show_Key_Type(key, keyType);

			if (!streq("segment", keyType))
			{
				char segname[MVO_BUFFER_SIZE];
				HC_KEY segkey;
				
				segkey = HC_KShow_Owner_Original_Key(key);
				HC_Show_Owner_By_Key(key, segname);

				// climb up one more level if this is the temporary highlight key
				if( IsHighlightSegment(segkey) )
				{
					segkey = HC_KShow_Owner_Original_Key(segkey);
					HC_Show_Owner_By_Key(segkey, segname);
				}
				key=segkey;
			}
		}
	}
	
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);

}


void HMySelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (!m_pView->GetEmitMessageFunction() || emit_message)	//disregard segment level setting if messsage
															//from other client			
	{
		if (m_SelectLevel == SEGMENT_TYPE) // nonzero if NOT a segment
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
	}
		
	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}


bool HMySelectionSet::IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys) const
{
	char	keyType[MVO_BUFFER_SIZE];

	if (m_SelectLevel == SEGMENT_TYPE) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.

		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
		{
			key = HC_KShow_Owner_Original_Key(key);

			// climb up one more level if this is the temporary highlight key
			if( IsHighlightSegment(key) )
				key = HC_KShow_Owner_Original_Key(key);
		}
		
	}
		
	return HSelectionSet::IsSelected(key, num_include_keys, include_keys);

}

// NOTE: This function is depricated
void HMySelectionSet::Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (!m_pView->GetEmitMessageFunction() || emit_message)	//disregard segment level setting if messsage
															//from other client			
	{
		if (m_SelectLevel == SEGMENT_TYPE) // nonzero if NOT a segment
		{
			// the key is to a geometric entity.  If we are in segment selection mode,
			// then we need to get the key to its parent segment.

			HC_Show_Key_Type(key, keyType);

			if (!streq("segment", keyType))
			{
				HC_KEY segkey = HC_KShow_Owner_By_Key(key);
				if (segkey >= 0) {
				    char segment[MVO_BUFFER_SIZE];
				    HC_Show_Owner_By_Key(key, segment);
				    // this is a little HOOPS trick to determine the internal key 3dGS
				    // uses to refer to the piece of geometry.  key will hold this value
				    HC_Open_Segment(segment);
					HC_Open_Segment("..");
						HC_KEY	renumbered = segkey;
						char scope[MVO_BUFFER_SIZE];
						HC_Show_Key_Status (segkey, scope);
						segkey = HC_KRenumber_Key (segkey, -1, "irrelevant");
						HC_Renumber_Key (segkey, renumbered, scope);
					HC_Close_Segment();
				    HC_Close_Segment();
				}

				key=segkey;
			}
		}
	}
	
	HSelectionSet::Select(key, segpath, include_key, includer_key, emit_message);

}


void HMySelectionSet::DeSelect(HC_KEY key, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (!m_pView->GetEmitMessageFunction() || emit_message)	//disregard segment level setting if messsage
															//from other client			
	{
		if (m_SelectLevel == SEGMENT_TYPE) // nonzero if NOT a segment
		{
			// the key is to a geometric entity.  If we are in segment selection mode,
			// then we need to get the key to its parent segment.

			HC_Show_Key_Type(key, keyType);

			if (!streq("segment", keyType))
				key = HC_KShow_Owner_By_Key(key);
			
		}
	}
		
	HSelectionSet::DeSelect(key, emit_message);
}

void HMySelectionSet::DeSelectAll()
{
	HSelectionSet::DeSelectAll();
	m_pView->EmitDeSelectAllMessage();
}


bool HMySelectionSet::IsSelected(HC_KEY key)
{
	return HSelectionSet::IsSelected(key);
}
void HMySelectionSet::RefreshSolidSelection()
{
	return;
}
