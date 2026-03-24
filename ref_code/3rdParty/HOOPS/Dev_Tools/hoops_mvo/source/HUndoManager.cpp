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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HUndoManager.cpp,v 1.20 2009-07-07 23:21:14 evan Exp $
//
 
#include "HUndoManager.h"
#include "HBaseView.h"
#include <math.h>
#include "string.h"
#include "stdio.h"

#include "vhash.h"
#include "vlist.h"
#include "HEventInfo.h"

HUndoManager::HUndoManager()
{
	m_pUndoItemList = new_vlist(malloc, free);
	m_pFirstItem = new HUndoItem();
	m_pLastItem = new HUndoItem();
	m_pCurrentItem = 0;
}


HUndoManager::~HUndoManager()
{
	START_LIST_ITERATION(HUndoItem, m_pUndoItemList)
		delete temp;
	END_LIST_ITERATION(m_pUndoItemList)
	delete_vlist(m_pUndoItemList);
	delete m_pFirstItem;
	delete m_pLastItem;
}

void HUndoManager::AddUndoItem(HUndoItem *item)
{
	struct vlist_s *	deletelist;	
	deletelist = new_vlist(malloc, free);
	bool flush = false;
	if (m_pCurrentItem == m_pFirstItem)
    	{
		START_LIST_ITERATION(HUndoItem, m_pUndoItemList)
  			    vlist_add_last(deletelist, temp);
 		END_LIST_ITERATION(m_pUndoItemList)
	}
	else
	{
 	START_LIST_ITERATION(HUndoItem, m_pUndoItemList)
		if (temp == m_pCurrentItem)
		    flush = true;
		else
		{ if (flush)
 		    vlist_add_last(deletelist, temp);
		}
 	END_LIST_ITERATION(m_pUndoItemList)
	}   
	START_LIST_ITERATION(HUndoItem, deletelist)
	    vlist_remove(m_pUndoItemList, temp);
		delete temp;
	END_LIST_ITERATION(deletelist)
	
	delete_vlist(deletelist);

	vlist_add_last(m_pUndoItemList, item);
	 
	m_pCurrentItem = item;

}

int HUndoManager::Undo(int steps, bool testOnly, bool setuponly)
{
	int undosperformed = 0; 
	HUndoItem *tempitem=0;
	if (testOnly)
	    tempitem = m_pCurrentItem;

	for (int i=0;i<steps;i++)
	{
	    if (m_pCurrentItem == m_pFirstItem)
	        return undosperformed;

	   if (m_pCurrentItem == m_pLastItem)	 	    	    
		m_pCurrentItem = (HUndoItem *)vlist_peek_last(m_pUndoItemList);

	    HUndoItem *lastitem = 0;
	    START_LIST_ITERATION(HUndoItem, m_pUndoItemList)
		if (temp == m_pCurrentItem)
		    break;
		lastitem = temp;
	    END_LIST_ITERATION(m_pUndoItemList)
	    if (!lastitem)
		lastitem = m_pFirstItem;

	    if (m_pCurrentItem)
	    {
		undosperformed++;
		if (!testOnly)
		m_pCurrentItem->Undo(setuponly);
	    }
	    m_pCurrentItem = lastitem;
	}
	if (testOnly)
	    m_pCurrentItem = tempitem;
	
	return undosperformed;
}

int HUndoManager::Redo(int steps, bool testOnly, bool setuponly)
{
    int undosperformed = 0; 
    HUndoItem *tempitem = 0;
    if (testOnly)
		tempitem = m_pCurrentItem;
    
    for (int i=0;i<steps;i++)
    {
	if (m_pCurrentItem == m_pLastItem)
	    return undosperformed;
	
	HUndoItem *nextitem = 0;
	if (m_pCurrentItem == m_pFirstItem)	 		
	    m_pCurrentItem = (HUndoItem *)vlist_peek_first(m_pUndoItemList);
	else
	{
	    
	    START_LIST_ITERATION(HUndoItem, m_pUndoItemList)
		nextitem = (HUndoItem *)vlist_peek_cursor_next(m_pUndoItemList);
	    if (temp == m_pCurrentItem)
		break;
	    END_LIST_ITERATION(m_pUndoItemList)	    
		
		if (!nextitem)
		    nextitem = m_pLastItem;
		m_pCurrentItem = nextitem;
	}
	if (m_pCurrentItem && m_pCurrentItem != m_pLastItem)
	{
	    undosperformed++;
	    if (!testOnly)
		m_pCurrentItem->Redo(setuponly);
	}
	

	}
	if (testOnly)
	    m_pCurrentItem = tempitem;
	
	return undosperformed;
}

void HUndoManager::Flush()
{
	START_LIST_ITERATION(HUndoItem, m_pUndoItemList)
		delete temp;
	END_LIST_ITERATION(m_pUndoItemList)
	vlist_flush(m_pUndoItemList);
	m_pCurrentItem = 0;
}

HUndoItem * HUndoManager::Peek()
{
	return m_pCurrentItem;
}

void HUndoManager::Reset(HBaseView *view)
{
	HUndoItem *item, *saved_curr_item;
	HCamera *camera = 0;
	int i = 0, curr_index = 0, keycount = 0;
	float *matrices, *oldmatrices;

	HC_KEY *keys;
	vhash_t *table;

	//set continuous mode to prevent camera changes from updating the scene at a bad time
	ViewUpdateMode old_mode = view->GetViewUpdateMode();
	if(old_mode == OnDemand)
		view->SetViewUpdateMode(Continuous);

	//get current location of undo sequence
	saved_curr_item = Peek();

	//get maximum number of possible keys, and allocate memory for list of keys
	BeginUndoItemIteration();
	while(item = GetNextUndoItem())
	{
		//matrices might have multiple keys
		if(streq(item->GetName(),"HUndoItemMatrix"))
			keycount += ((HUndoItemMatrix *)item)->GetCount();
		else
			keycount++;
		if(item == saved_curr_item)
			break;
	}
	EndUndoItemIteration();

	keys = new HC_KEY[keycount];
	matrices = new float[keycount * 16];
	oldmatrices = new float[keycount * 16];
	table = new_vhash(keycount, malloc, free);
	
	//1st pass:
	//----------------------------------------------------//
	//iterate through entire undo list, get list of unique geometry keys and first camera setting
	//build up list of pointers to each undo object
	BeginUndoItemIteration();
	while(item = GetNextUndoItem())
	{
		if(streq(item->GetName(), "HUndoItemMatrix"))
		{
			HC_KEY *key = ((HUndoItemMatrix *)item)->GetKey();
			int count = ((HUndoItemMatrix *)item)->GetCount();

			for(i = 0; i < count; i++)
			{
				//see if key already exists in hash table; if not, then add item to table
				if(vhash_lookup_item(table, (void *)key[i], 0) != VHASH_STATUS_SUCCESS)
				{
					vhash_insert_item(table, (void *) key[i], 0);
					
					//now add to list
					keys[curr_index] = key[i];
					memcpy(&matrices[curr_index * 16], ((HUndoItemMatrix *)item)->GetMatrix(), 16*sizeof(float));
					curr_index++;
				}
			}
		}
		else if(camera == 0 && streq(item->GetName(), "HUndoItemCamera"))
		{
			camera = new HCamera();
			memcpy(camera, ((HUndoItemCamera *)item)->GetCamera(), sizeof(HCamera));
		}

		if(item == saved_curr_item)
			break;
	}
	EndUndoItemIteration();

	//apply matrices
	//----------------------------------------------------//
	//first, save the current keys/matrices, so we can restore them for the smooth transition
	for(i = 0; i < curr_index; i++)
	{
		HC_Open_Segment_By_Key(keys[i]);
			HC_Show_Modelling_Matrix(&oldmatrices[i*16]);
		HC_Close_Segment();
	}
	//save the old camera, so we can restore for smooth transition
	HCamera oldcamera;
    view->GetCamera(&oldcamera);
	
	//move undo pointer back to beginning, properly modifying the undo values along the way
	//this will bash current settings, so we'll need to restore aftewards for smooth transitions
	while(Undo(1,false,true));	


	//if smooth transitions, restore camera so can render the smooth transitions
	if(view->GetSmoothTransition())
		view->SetCamera(oldcamera);

	//pass list of geometry keys and their corresponding matrices to utility function to 
	//smoothly transition all to original positions
	if(view->GetSmoothTransition())
	{
		//if doing smooth transitions, need to restore the matrices (from before we bashed them)
		for(i = 0; i < curr_index; i++)
		{
			HC_Open_Segment_By_Key(keys[i]);
				HC_Set_Modelling_Matrix(&oldmatrices[i*16]);
			HC_Close_Segment();
		}

		HC_Open_Segment_By_Key(view->GetSceneKey());
			HShadowMode oldmode = view->GetShadowMode();
			view->SetShadowMode(HShadowNone);
			HUtility::MultiSmoothTransitions(view, curr_index, keys, matrices, camera);
			view->SetShadowMode(oldmode);
		HC_Close_Segment();

		//set final modelling matrix; this will force a shadow update
		for(i = 0; i < curr_index; i++)
		{
			HC_Open_Segment_By_Key(keys[i]);
				HC_Set_Modelling_Matrix(&matrices[i*16]);
			HC_Close_Segment();
		}
	}

	view->SetGeometryChanged();
	view->ForceUpdate();

	//now restore the original mode
	if(old_mode != view->GetViewUpdateMode())
		view->SetViewUpdateMode(OnDemand);

	if(camera)
		delete camera;
	delete [] keys;
	delete [] matrices;
	delete [] oldmatrices;
	delete_vhash(table);
}

 

void HUndoManager::BeginUndoItemIteration()
{
	m_pTempUndoItem = (HUndoItem *)vlist_peek_cursor(m_pUndoItemList);
	vlist_reset_cursor(m_pUndoItemList);
}

HUndoItem * HUndoManager::GetNextUndoItem()
{
	HUndoItem *item = (HUndoItem *)vlist_peek_cursor(m_pUndoItemList);
	vlist_advance_cursor(m_pUndoItemList);
	return item;
}

void HUndoManager::EndUndoItemIteration()
{
	START_LIST_ITERATION(HUndoItem, m_pUndoItemList)
 	if (temp == m_pTempUndoItem)
		break;
	END_LIST_ITERATION(m_pUndoItemList)	    
}

  
 

//HUndoItemCamera
HUndoItemCamera::HUndoItemCamera(HBaseView *view)
{
    m_pView = view;
    view->GetCamera(&m_Camera);
 
}


void HUndoItemCamera::Undo(bool setuponly)
{
	HCamera oldcamera;
    m_pView->GetCamera(&oldcamera);

	if(!setuponly)
	{
		if (m_pView->GetSmoothTransition())
		{
			HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HUtility::SmoothTransition(oldcamera, m_Camera, m_pView);
			HC_Close_Segment();
		}
	}

	m_pView->SetCamera(m_Camera);
    m_Camera = oldcamera;
}

void HUndoItemCamera::Redo(bool setuponly)
{
	HCamera oldcamera;
    m_pView->GetCamera(&oldcamera);

	if(!setuponly)
	{
		if (m_pView->GetSmoothTransition())
		{
			HC_Open_Segment_By_Key(m_pView->GetSceneKey());
			HUtility::SmoothTransition(oldcamera, m_Camera, m_pView);
			HC_Close_Segment();
		}
	}

	m_pView->SetCamera(m_Camera);
    m_Camera = oldcamera;
}


// HUndoItemMatrix
HUndoItemMatrix::HUndoItemMatrix(HBaseView *view, int num_items, HC_KEY *keys, float *matrices)
{
	m_pView = view;
	m_Count = num_items;

	m_SegmentKey = new HC_KEY[m_Count];
	memcpy(m_SegmentKey, keys, m_Count*sizeof(HC_KEY));
	
	m_Matrix = new float[m_Count * 16];
	memcpy(m_Matrix, matrices, m_Count * 16 * sizeof(float));
}

HUndoItemMatrix::~HUndoItemMatrix()
{ 
	if(m_Matrix) 
		delete [] m_Matrix; 

	if(m_SegmentKey)
		delete [] m_SegmentKey;
};

void HUndoItemMatrix::GetMatrix(float *matrices)
{
	memcpy(matrices, m_Matrix, m_Count * 16 * sizeof(float));
}

void HUndoItemMatrix::GetKey(HC_KEY *keys)
{
	memcpy(keys,m_SegmentKey,m_Count*sizeof(HC_KEY));
}

void HUndoItemMatrix::Undo(bool setuponly)
{
	int i = 0;
	float *oldmatrix = new float[m_Count * 16];
	
	HShadowMode oldmode;
	oldmode = m_pView->GetShadowMode();
	m_pView->SetShadowMode(HShadowNone);

	for(i = 0; i < m_Count; i++)
	{
		HC_Open_Segment_By_Key(m_SegmentKey[i]);
			HC_Show_Modelling_Matrix(&oldmatrix[i*16]);
		HC_Close_Segment();
	}

	if(!setuponly)
	{
		if (m_pView->GetSmoothTransition())
			HUtility::MultiSmoothTransitions(m_pView, m_Count, m_SegmentKey, m_Matrix);
	}

	for(i = 0; i < m_Count; i++)
	{
		HC_Open_Segment_By_Key(m_SegmentKey[i]);
		HC_Set_Modelling_Matrix(&m_Matrix[i*16]);
		HC_Close_Segment();
	}

	delete [] m_Matrix;
	m_Matrix = oldmatrix;
	m_pView->SetShadowMode(oldmode);

	if(!setuponly)
		m_pView->ForceUpdate();
}

void HUndoItemMatrix::Redo(bool setuponly)
{
	int i = 0;
	float *oldmatrix = new float[m_Count * 16];
	
	HShadowMode oldmode;
	oldmode = m_pView->GetShadowMode();
	m_pView->SetShadowMode(HShadowNone);

	for(i = 0; i < m_Count; i++)
	{
		HC_Open_Segment_By_Key(m_SegmentKey[i]);
			HC_Show_Modelling_Matrix(&oldmatrix[i*16]);
		HC_Close_Segment();
	}

	if(!setuponly)
	{
		if (m_pView->GetSmoothTransition())
			HUtility::MultiSmoothTransitions(m_pView, m_Count, m_SegmentKey, m_Matrix);
	}

	for(i = 0; i < m_Count; i++)
	{
		HC_Open_Segment_By_Key(m_SegmentKey[i]);
		HC_Set_Modelling_Matrix(&m_Matrix[i*16]);
		HC_Close_Segment();
	}

	delete [] m_Matrix;
	m_Matrix = oldmatrix;
	m_pView->SetShadowMode(oldmode);

	if(!setuponly)
		m_pView->ForceUpdate();
}
