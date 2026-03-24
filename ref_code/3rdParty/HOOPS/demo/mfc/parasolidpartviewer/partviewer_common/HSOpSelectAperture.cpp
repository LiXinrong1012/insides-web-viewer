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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpSelectAperture.cpp,v 1.27 2007-11-08 00:50:09 chad Exp $
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
#include "HSolidModel.h"

#include "HSOpSelectAperture.h"

#include "HSolidView.h"
#include "topolbrowserdlg.h"
#include "HEventInfo.h"
#include "HSelectionSet.h"
#include "HTools.h"
#include "HSSelectionSet.h"

#include <math.h>
#include <string.h>

#include "hc.h"

/////////////////////////////////////////////////////////////////////////////
// HOpSelectAperture
//
// Operator for performing a hit test on the scene and placing hit objects in the view's
// selection list
// Mouse down - computes the selection and adds items to the selection list


HSOpSelectAperture::HSOpSelectAperture(HBaseView* view, int DoRepeat, int DoCapture) : HOpSelectAperture(view, DoRepeat, DoCapture)
{
//	m_current_item = 0;
}

 

int HSOpSelectAperture::DoLButtonDown(HEventInfo &event)
{
	HPoint  new_pos;
    int		res; //, count, offset1, offset2, offset3;
//    char	segpath[MVO_SEGMENT_PATHNAME_BUFFER];
//	HC_KEY  *keys = 0, key, include_key, includer_key;
//	HC_KEY  key;

	// Mouse went down; find the selected items

	HC_Open_Segment_By_Key(m_pView->GetConstructionKey());
		HC_Flush_Contents (".", "geometry");
	HC_Close_Segment();

    HSelectionSet* selection = m_pView->GetSelection();

	new_pos = event.GetMouseWindowPos();

	// perform standard Windows explorer method of selecting and deselecting
	// using Shift and Control keys

	// if neither the Control key nor Shift key is down, deselect everything
    if (!event.Control() && !event.Shift())
		selection->DeSelectAll();

	HC_Open_Segment_By_Key(m_pView->GetViewKey());
	// compute the selection using the HOOPS window coordinate ofthe the pick location
	if ((res = HC_Compute_Selection(".","./scene/overwrite","v", new_pos.x, new_pos.y)) > 0)
	{
		do	// process each item in the selection queue
		{
			HC_KEY key;
			HC_Show_Selection_Element (&key, NULL, NULL, NULL);
			
			char segpath[MVO_BUFFER_SIZE];
			HC_Show_Selection_Pathname(segpath);
			
			int count;
			HC_Show_Selection_Keys_Count(&count);
			HC_KEY * keys = new HC_KEY[count];

			HC_Show_Selection_Original_Keys(&count, keys);
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

				
			// if you ever decide to pass just the array of include keys, then
			// please make sure you update the HSAcisSelectionSet Select, DeSelect and IsSelected
			// functions, because they are expecting all keys in the path - Rajesh B (19-Mar-07)
#ifdef PARASOLID
			if (((HSSelectionSet *)selection)->GetSelectLevel()==KERN_INSTANCE_TYPE)
			{
				if (event.Control())
				{
					// if selected, deselect, else select
					if (selection->IsSelected(includer_key))
						selection->DeSelect(includer_key);
					else
						selection->Select(key, segpath, include_key, includer_key, true);
				}
				else if (event.Shift())
				{
					// select if not selected
					if (!(selection->IsSelected(includer_key)))	
						selection->Select(key, segpath, include_key, includer_key, true);
				}
				else if (!(selection->IsSelected(includer_key)))
				{ 
					// simply select the item
					selection->Select(key, segpath, include_key, includer_key, true);
				}
			}
			else
#endif // PARASOLID
			{
				// handle control, shift and no_key cases
				if (event.Control())
				{
					// if selected, deselect, else select
					if (selection->IsSelected(key, incl_count,incl_keys))
						selection->DeSelect(key, incl_count, incl_keys);
					else
						selection->Select(key, incl_count, incl_keys, true);
				}
				else if (event.Shift())
				{
					// select if not selected
					if (!(selection->IsSelected(key, incl_count, incl_keys)))	
						selection->Select(key, incl_count, incl_keys, true);
				}
				else if (!(selection->IsSelected(key, incl_count, incl_keys)))
				{ 
					// simply select the item
					selection->Select(key, incl_count, incl_keys, true);
				}
			}
			

			delete [] incl_keys;
			delete [] keys;
			
		} while (HC_Find_Related_Selection());
	}
	HC_Close_Segment();
   

    m_pView->Update();	// update the scene to reflect the new highlight attributes
						// of the selected items
    return(HOP_READY);
}

int HSOpSelectAperture::OnLButtonDown(HEventInfo &event)
{
	int result;

 	if (((HSolidModel *)(m_pView->GetModel()))->m_bSolidData != true)
	{
		result = HOpSelectAperture::OnLButtonDown(event);
	}
	else
	{
		HSSelectionSet* selection = (HSSelectionSet *)m_pView->GetSelection();

		if (m_pView->GetRenderMode() == HRenderHiddenLine && (selection->GetSelectLevel()!=KERN_FACE_TYPE))
		{
			HC_Open_Segment_By_Key(m_pView->GetModel()->GetModelKey());
			HC_Open_Segment("main_temp");
			HC_Set_Selectability("faces=off");
			HC_Close_Segment();
			HC_Close_Segment();
			
			result=DoLButtonDown(event);
			
			HC_Open_Segment_By_Key(m_pView->GetModel()->GetModelKey());
			HC_Open_Segment("main_temp");
			HC_Set_Selectability("faces=on!");
			HC_Close_Segment();
			HC_Close_Segment();
		}
		else
			result = DoLButtonDown(event);
	}
	return result;
}
