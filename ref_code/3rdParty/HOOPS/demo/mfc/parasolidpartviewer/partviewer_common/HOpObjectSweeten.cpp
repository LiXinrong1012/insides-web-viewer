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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HOpObjectSweeten.cpp,v 1.13 2006-08-07 20:38:55 stage Exp $
//

// HOpObjectSweeten.cpp : implementation of the HOpObjectSweeten class
//

//#ifdef STDAFX
#include "stdafx.h"
//#endif

#include "HSInclude.h"
#include "HBaseModel.h"
#include "HSolidView.h"
#include "HBaseOperator.h"

#include "HOpConstructRectangle.h"
#include "HOpObjectSweeten.h"

#include "HEventInfo.h"
#include "HSelectionSet.h"
#include "HTools.h"
#include "HUtility.h"

#include <math.h>
#include <hc.h>


/////////////////////////////////////////////////////////////////////////////
// HOpObjectSweeten
//
// Operator for performing a hit test on the scene using a screen-space window
// and placing hit objects in the view's selection list
// Mouse down - computes the first point of the selection window
// Mouse down and move - rubberbands a box to denote current selection window
// Mouse up - computes the area selection and adds items to the selection list
// No mouse down and move - performs an "O-snap" quickmoves highlight of closest marker edge or line segment

 
HOpObjectSweeten::HOpObjectSweeten(HBaseView* view, int DoRepeat, int DoCapture) : HOpConstructRectangle(view, DoRepeat, DoCapture, false)
{
}

HOpObjectSweeten::~HOpObjectSweeten()
{
}
   
HBaseOperator * HOpObjectSweeten::Clone()
{
	return (HBaseOperator *)new HOpObjectSweeten(m_pView);
}

const char * HOpObjectSweeten::GetName() { return "Sweeten Object"; }


int HOpObjectSweeten::OnLButtonUp(HEventInfo &event)
{
	HOpConstructRectangle::OnLButtonUp(event);

	int count;

	if (HUtility::PointsEqual(&m_ptNew, &m_ptFirst))
	{
		HC_Open_Segment_By_Key(m_pView->GetViewKey());
			HC_QSet_Heuristics("./scene/overwrite", "no related selection limit");
			count = HC_Compute_Selection(".", ".scene/overwrite", "v", m_ptFirst.x, m_ptFirst.y);
			HC_QUnSet_Heuristics("./scene/overwrite");
		HC_Close_Segment();
	}
	else
	{
		HUtility::Order(&m_ptRectangle[0], &m_ptRectangle[1]);

		HC_Open_Segment_By_Key(m_pView->GetViewKey());
			HC_QSet_Heuristics("./scene/overwrite", "no related selection limit");
			count = HC_Compute_Selection_By_Area(".","./scene/overwrite","v", 
			    m_ptRectangle[0].x, m_ptRectangle[1].x, 
			    m_ptRectangle[0].y, m_ptRectangle[1].y);
			HC_QUnSet_Heuristics("./scene/overwrite");
		HC_Close_Segment();
	}

	//now process the objects in the selection queue
	if (count)
		{
			int i = 0;
			((HSolidView *)m_pView)->m_pSweetenKeyList = new HC_KEY [count];
			do
			{
				HC_KEY key;
				int offset1, offset2, offset3;
				HC_Show_Selection_Element (&key, &offset1, &offset2, &offset3);
				((HSolidView *)m_pView)->m_pSweetenKeyList[i] = key;
				i++;		   
			} while (HC_Find_Related_Selection());
		}

	// Now stream/sweeten in the selected objects .....

	m_pView->Update();
    return(HOP_READY);
}
