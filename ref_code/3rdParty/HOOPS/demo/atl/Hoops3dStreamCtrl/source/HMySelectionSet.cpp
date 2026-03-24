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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/HMySelectionSet.cpp,v 1.3 2006-08-07 20:38:46 stage Exp $
//
#include "stdafx.h"

#include "HCtrlView.h"
#include "Hoops3dStream.h"
#include "HMySelectionSet.h"
#include "HBaseModel.h"
#include "DataLoader.h"
#include <hc.h>

#include "htools.h"
#include "hutility.h"

 
HMySelectionSet::HMySelectionSet(HBaseView* view, CDataLoader *dataloader):HSelectionSet(view)
{
	m_pDataLoader = dataloader;
//	m_SelectLevel = SEGMENT_TYPE;
	strcpy(m_ModelStructureFilter,"");
}


void HMySelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{

	int index;
	if (m_pView->GetModel()->GetStreamFileTK()->KeyToIndex(key, index) != TK_NotFound)
	{
	    int newindex = m_pDataLoader->FilterIdentifier(index, m_ModelStructureFilter);
	    HC_KEY newkey;
	    if (m_pView->GetModel()->GetStreamFileTK()->IndexToKey(newindex, newkey) != TK_NotFound)
	    {
		key = newkey;

	    }
	}
	    

	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);

}

void HMySelectionSet::SelectDirect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{	    
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);

}

 