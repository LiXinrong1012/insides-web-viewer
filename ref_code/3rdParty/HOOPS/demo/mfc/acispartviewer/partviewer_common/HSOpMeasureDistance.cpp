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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpMeasureDistance.cpp,v 1.25 2009-06-19 00:31:18 thomas Exp $
//



//#ifndef IS_QT
//#ifdef STDAFX 
#include "stdafx.h"
//#endif
//#endif

#include "HSInclude.h"

#ifdef IS_QT
#include "MyHQSolidWidget.h"
#else
#include "CSolidHoopsView.h"
#endif

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HSolidView.h"
#include "HSolidModel.h"
#include "HSUtility.h"
#include "HTools.h"
#include "HEventInfo.h"
 
#include "hc.h"
#include "HSOpMeasureDistance.h"
#include "CBinaryFileToolkit.h"

#include <stdio.h>
#include <assert.h>
#include <math.h>


/////////////////////////////////////////////////////////////////////////////
// HSQuery

// Operator for querying model
// Mouse down - displays modeless query dialog containing and computes information 
// about the part intersected by the calculated picking ray
// Mouse motion while down - dynamically updates the dialog based on new picking ray


HSOpMeasureDistance::HSOpMeasureDistance(HBaseView* view, int DoRepeat, int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{
}
 
HSOpMeasureDistance::~HSOpMeasureDistance( void )
{
}

const char * HSOpMeasureDistance::GetName()
{
	return "Measure Distance";
}

int HSOpMeasureDistance::OnLButtonDown(HEventInfo &event)
{
	// Mouse went down 

	m_ptNew = event.GetMouseWindowPos();

 
	int res;
	if (((HSolidModel *)(m_pView->GetModel()))->m_bPlainSolidModel)
		res = DoQueryPlain(true);
	else
		res = DoQuery(true);

	if (res)
	{

	HC_Open_Segment_By_Key(m_pView->GetWindowspaceKey());
	
		if (!m_bOpStarted) 
		{
			m_bOpStarted = true;
			m_lPolyline = HC_KInsert_Ink(m_ptNew.x, m_ptNew.y, m_ptNew.z);
		}
		else
			HC_Insert_Ink(m_ptNew.x, m_ptNew.y, m_ptNew.z);
			
	HC_Close_Segment();
		
	m_ptLast.x = m_ptNew.x;
	m_ptLast.y = m_ptNew.y;
	m_ptLast.z = m_ptNew.z;
    
#ifdef IS_QT
		DialogMaker->ShowQueryDialog();
#else
		m_SolidHoopsView->ShowQueryDialog(SW_SHOW);
#endif
	}
	else
		m_bOpStarted = false;
    return (HOP_OK);
}

int HSOpMeasureDistance::OnLButtonUp(HEventInfo &event)
{

	if (!m_bOpStarted) 
	    return HBaseOperator::OnLButtonUp(event);

 

	// Pack the Operators Polyline point array and count
 

	// Clean up HOOPS segment tree
	HC_Open_Segment_By_Key(m_pView->GetWindowspaceKey());	
	    HC_Flush_Segment(".");  	 		
            HC_Open_Segment ("line");
                HC_Flush_Segment(".");
            HC_Close_Segment();
	HC_Close_Segment ();

	// Update view and reset OpStarted Flag
	m_pView->Update();
	m_bOpStarted = false;
//	m_SolidHoopsView->ShowQueryDialog(SW_HIDE);

	return(HOP_READY);

}


int HSOpMeasureDistance::OnLButtonDownAndMove(HEventInfo &event)
{
     //  Mouse is down and has moved  
 	 
	if (m_bOpStarted)
	{
     m_ptNew = event.GetMouseWindowPos();

 
    HC_Open_Segment_By_Key(m_pView->GetWindowspaceKey());
		HC_Open_Segment ("line");
 			HC_Flush_Segment(".");
			HC_Insert_Line(m_ptLast.x, m_ptLast.y, m_ptLast.z, 
						   m_ptNew.x,  m_ptNew.y,  m_ptNew.z);
		HC_Close_Segment();
	HC_Close_Segment();

    m_pView->Update();
	int res;
	if (((HSolidModel *)(m_pView->GetModel()))->m_bPlainSolidModel)
		res = DoQueryPlain();
	else
		res = DoQuery();

	if (res)
#ifdef IS_QT
		DialogMaker->ShowQueryDialog();
#else
		m_SolidHoopsView->ShowQueryDialog(SW_SHOW);
#endif
    return (HOP_OK);
	}
	return (HOP_OK);
}  

// normalize double precision vector in place 
void HSOpMeasureDistance::normalize_vector(double* vector)
{
	double length;
	length = sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
	vector[0]/=length;
	vector[1]/=length;
	vector[2]/=length;
}




// perform the query and update the dialog with the model info
bool HSOpMeasureDistance::DoQueryPlain(bool first)
{
	bool retval = false;
	char QueryString[MVO_BUFFER_SIZE];

	HPoint dummy,target, camera;
	HPoint dist;
	int count;

	HC_Open_Segment_By_Key (m_pView->GetViewKey());
		HC_QSet_Selectability ("./scene/overwrite", "geometry=on!" );
		count = HC_Compute_Selection (".", "./scene/overwrite", "v",
												m_ptNew.x, m_ptNew.y);
		HC_QUnSet_Selectability ("./scene/overwrite");
	HC_Close_Segment();
	HC_Open_Segment_By_Key (m_pView->GetSceneKey());
		for(;;) // dummy loop just so we can use "break" mechanism to jump to end
		{ 
			HC_KEY key;
 			int edgecount, facecount;


			#ifndef PARASOLID
 					long body=0;
			#endif

			HC_Show_Selection_Position(
				&dummy.x, &dummy.y, &dummy.z, 
				&target.x, &target.y, &target.z);

			if (first)
			{
				
				first_pick2.x = target.x;
				first_pick2.y = target.y;
				first_pick2.z = target.z;
			}
			dist.x = target.x - first_pick2.x;
			dist.y = target.y - first_pick2.y;
			dist.z = target.z - first_pick2.z;
 			float length=(float)sqrt(dist.x*dist.x+dist.y*dist.y+dist.z*dist.z);

			HC_Show_Selection_Element(&key, NULL, NULL, NULL);
			HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);

			body = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Entity_Index(key,KERN_BODY_TYPE);

			if  (body <=0) 
			{
				retval = false;
				break;
			}

 			((HSolidModel *)m_pView->GetModel())->m_mi->BODY_ask_faces(body,&facecount,0);
			int edgenum;
			edgecount=0;
			for (int j=0;j<facecount;j++)
			{
 				((HSolidModel *)m_pView->GetModel())->m_mi->FACE_ask_edges(body,&edgenum,0);
				edgecount+=edgenum;
			}

			{
				int char_offset = 0;
 				char_offset = sprintf(QueryString+char_offset, "Picked body TagID is %d.\n\nThis body contains:\n   %d PK_edges and \n   %d PK_faces.\n\n", body, edgecount, facecount);
				char_offset += sprintf(QueryString+char_offset, "Coordinates of surface along picking ray:\n   x = %#.12f\n   y = %#.12f\n   z = %#.12f\n",
					target.x,target.y,target.z);
				char_offset = sprintf(QueryString+char_offset, "Distance:\n%#.12f\n",length);

 				retval = true;
				m_SolidHoopsView->SetQueryDialogText(QueryString);
				break;
			}
		}
	HC_Close_Segment();

	return retval;
}


// perform the query and update the dialog with the model info
bool HSOpMeasureDistance::DoQuery(bool first)
{
	bool retval = false;


	char QueryString[MVO_BUFFER_SIZE];
	HPoint dummy,target, camera;
	int count;

	HC_Open_Segment_By_Key (m_pView->GetViewKey());
		HC_QSet_Selectability ( "./scene/overwrite", "geometry=on!");
		count = HC_Compute_Selection (m_pView->GetDriverPath(), ".", "v",
												m_ptNew.x, m_ptNew.y);
		HC_QUnSet_Selectability ( "./scene/overwrite");
	HC_Close_Segment();
	HC_Open_Segment_By_Key (m_pView->GetSceneKey());
		for(;;) // dummy loop just so we can use "break" mechanism to jump to end
		{ 
			HC_KEY key;
			int edgecount, facecount;
			int offset1, offset2, offset3;
			HC_Show_Selection_Position(
				&dummy.x, &dummy.y, &dummy.z, 
				&target.x, &target.y, &target.z);
			HC_Show_Selection_Element(&key, &offset1, &offset2, &offset3);

	#ifdef ACIS
			ENTITY* entity = 0;
			BODY* body = 0;
			if (!entity)
				body = (BODY*) HA_Compute_Entity_Pointer(key, BODY_TYPE);
			if (!entity && !body) 
			{
				retval = false;
				break;
			}

			ENTITY_LIST edges;
			outcome o = api_get_edges(body, edges);
			CHECK_OUTCOME( o );
			edgecount = edges.iteration_count();

			ENTITY_LIST faces;
			o = api_get_faces( body, faces);
			CHECK_OUTCOME( o );
			facecount = faces.iteration_count();

			HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
			SPAposition picking_ray_pos( camera.x, camera.y, camera.z );
			// axis MUST contain a unit vector rw
			SPAunit_vector picking_ray_dir( ( target.x - camera.x),
										 ( target.y - camera.y),
										 ( target.z - camera.z) );

			int hits_wanted = 1;
			hit* hit_list;
			int num_targets = 1;
			ENTITY* target_ents[] = { body };
			o = api_raytest_ents(  picking_ray_pos, picking_ray_dir, 100*SPAresabs, 
								   hits_wanted, num_targets, target_ents, hit_list );

			if( hit_list )
			{
				// compute the 3D coordinate where the ray hits the body
				// This seems trivial but it was almost like looking for the needle
				// in haystack to find how to do it in ACIS. - Rajesh B (29-Mar-01)
				double scale = 1.;
				if (body->transform() != NULL)
						scale = body->transform()->transform().scaling();
				SPAposition int_pos = picking_ray_pos + (picking_ray_dir * hit_list[0].ray_param * scale);

				int char_offset = 0;

				if (first)
				{
					first_pick[0]=int_pos.x();
					first_pick[1]=int_pos.y();
					first_pick[2]=int_pos.z();
				}
				double dist[3];
				dist[0]=int_pos.x()-first_pick[0];
				dist[1]=int_pos.y()-first_pick[1];
				dist[2]=int_pos.z()-first_pick[2];
				double length=sqrt(dist[0]*dist[0]+dist[1]*dist[1]+dist[2]*dist[2]);
				char_offset = sprintf(QueryString+char_offset, "Picked body is %d.\n\nThis body contains:\n   %d EDGEs and \n   %d FACEs.\n\n", body, edgecount, facecount);
				char_offset += sprintf(QueryString+char_offset, "Analytical coordinates of surface along picking ray:\n   x = %#.12f\n   y = %#.12f\n   z = %#.12f\n",
																int_pos.x(), int_pos.y(), int_pos.z() );
				char_offset = sprintf(QueryString+char_offset, "Distance:\n%#.12f\n",length);

	#ifdef IS_QT
				DialogMaker->SetQueryDialogText(QueryString);
	#else
				m_SolidHoopsView->SetQueryDialogText(QueryString);
	#endif
				delete hit_list;

				retval = true;
				break;
			}
			retval = false;
			break;
	#endif // ACIS


		}
	HC_Close_Segment();
	return retval;
}


#ifdef IS_QT
void HSOpMeasureDistance::SetDialogMaker(MyHQSolidWidget* bla)
{
	DialogMaker=bla;
}
#else
void HSOpMeasureDistance::SetSolidHoopsView(CSolidHoopsView* view)
{
	m_SolidHoopsView = view;
}
#endif


