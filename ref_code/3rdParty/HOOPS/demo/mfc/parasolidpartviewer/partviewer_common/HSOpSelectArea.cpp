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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpSelectArea.cpp,v 1.20 2008-03-19 00:17:22 chad Exp $
//

// HOpSelectAperture.cpp : implementation of the HOpSelectAperture class
//

//#if STDAFX
#include "stdafx.h"
//#endif
#include "resource.h"
#include <assert.h>

#include "HSInclude.h"

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"

#include "HSOpSelectArea.h"

#include "HSolidView.h"
#include "topolbrowserdlg.h"
#include "HEventInfo.h"
#include "HSelectionSet.h"
#include "HTools.h"
#include "HSSelectionSet.h"
#include "HEventManager.h"

#include <math.h>
#include <string.h>

#include "hc.h"

/////////////////////////////////////////////////////////////////////////////
// HOpSelectAperture
//
// Operator for performing a hit test on the scene and placing hit objects in the view's
// selection list
// Mouse down - computes the selection and adds items to the selection list


HSOpSelectArea::HSOpSelectArea(HBaseView* view, int DoRepeat, int DoCapture) : HOpSelectArea(view, DoRepeat, DoCapture)
{

//	m_current_item = 0;
}

 

int HSOpSelectArea::OnLButtonUp(HEventInfo &event)
{
	int ret;
	HOpConstructRectangle::OnLButtonUp(event);

	if (!m_bRectangleExists) 
		ret = HBaseOperator::OnLButtonUp(event);
	else
	{

	HUtility::Order(&m_ptRectangle[0], &m_ptRectangle[1]);

	HSelectionSet* selection = m_pView->GetSelection();


	// Perform standard Windows explorer method of selecting and deselecting
	// using Shift and Control keys

	// If neither the Control key nor Shift key is down, deselect everything
    if (!event.Control() && !event.Shift())
		selection->DeSelectAll();

	HC_Open_Segment_By_Key(m_pView->GetOverwriteKey());
		HC_Set_Heuristics("no related selection limit, no selection sorting");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(m_pView->GetViewKey());

	  // compute the selection using the HOOPS window coordinate ofthe the pick location
		if (HC_Compute_Selection_By_Area(".","./scene/overwrite","v", 
						m_ptRectangle[0].x, m_ptRectangle[1].x, 
						m_ptRectangle[0].y, m_ptRectangle[1].y))
		{
			do	// process each item in the selection queue
			{
				HC_KEY key;
				HC_Show_Selection_Element (&key, NULL, NULL, NULL);

				// make sure we don't have an object key we should be ignoring
				HC_KEY okey = HObjectManager::FindHObjectSegment(key);
				if (okey == INVALID_KEY)
					continue;
				
				char segpath[MVO_BUFFER_SIZE];
				HC_Show_Selection_Pathname(segpath);
				
				int count;
				HC_Show_Selection_Keys_Count(&count);
				HC_KEY * keys = new HC_POINTER_SIZED_INT[count];

				HC_Show_Selection_Keys(&count, keys);
				HC_KEY include_key = keys[3];
				HC_KEY includer_key = keys[4];	

				// build up an array of include keys to pass with the selection
				HC_KEY *incl_keys	= new HC_KEY[count];
				int	incl_count		= 0;
				char skey_type[MVO_BUFFER_SIZE];
				int i;
				
				for(i = count-1; i >= 0; i--)
				{
					HC_Show_Key_Type(keys[i], skey_type);
					if(strstr(skey_type, "include"))
						incl_keys[incl_count++] = keys[i];
				}
					

				if (((HSSelectionSet *)selection)->GetSelectLevel()==KERN_INSTANCE_TYPE)
				{
					
					if (event.Shift())
					{
						// select if not selected
						if (!(selection->IsSelected(includer_key)))	
							selection->Select(key, incl_count, incl_keys, true);
//							selection->Select(key, segpath, include_key, includer_key, true);
					}
					else if (!(selection->IsSelected(includer_key)))
					{ 
						// simply select the item
						selection->Select(key, incl_count, incl_keys, true);
//						selection->Select(key, segpath, include_key, includer_key, true);
					}
				}
				else{
					// handle Shift and no_key cases
					if (event.Shift())
					{
						if (!selection->IsSelected(key))	
							selection->Select(key, incl_count, incl_keys, true);
//							selection->Select(key, segpath, include_key, includer_key, true);
					}
					else if (!selection->IsSelected(key))
					{
						selection->Select(key, incl_count, incl_keys, true);
//						selection->Select(key, segpath, include_key, includer_key, true);
					}
				}
				
				delete [] incl_keys;
				delete [] keys;
				
			} while (HC_Find_Related_Selection());

		}

	HC_Close_Segment();

	HC_Open_Segment_By_Key(m_pView->GetOverwriteKey());
		HC_UnSet_Heuristics();
    HC_Close_Segment();

	m_pView->SetGeometryChanged();
	m_pView->Update();
	ret = (HOP_READY);
	}
    return ret;
}


 
 

 

