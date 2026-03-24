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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSQuery.cpp,v 1.29 2009-05-22 18:52:24 stage Exp $
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
#include "HSolidModel.h"
#include "HBaseView.h"
#include "HSolidView.h"
#include "HSUtility.h"
#include "HTools.h"
#include "HEventInfo.h"
#include "HSQuery.h"

#include "hc.h"
#include "vlist.h"

#ifndef HOOPS_ONLY
#include "CBinaryFileToolkit.h"
#endif // HOOPS_ONLY


#include <stdio.h>
#include <assert.h>
#include <math.h>


/////////////////////////////////////////////////////////////////////////////
// HSQuery

// Operator for querying model
// Mouse down - displays modeless query dialog containing and computes information 
// about the part intersected by the calculated picking ray
// Mouse motion while down - dynamically updates the dialog based on new picking ray


HSQuery::HSQuery(HBaseView* view, int DoRepeat, int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{
}
HSQuery::~HSQuery( void )
{
}
const char * HSQuery::GetName()
{
	return "Query";
}
int HSQuery::OnLButtonDown(HEventInfo &event)
{

#ifndef PARASOLID
	SetNewPoint(event.GetMouseWindowPos());
#endif

	// Mouse went down 
	int res;

	if(((HSolidModel *)(GetView()->GetModel()))->m_bSolidData)
		res = DoQuery();
	else
		res = DoQueryHoops();

	if (res)
#ifdef IS_QT
		DialogMaker->ShowQueryDialog();
#else
		m_SolidHoopsView->ShowQueryDialog(SW_SHOW);
#endif

	return (HOP_OK);
}

int HSQuery::OnLButtonUp(HEventInfo &event)
{
	return HBaseOperator::OnLButtonUp(event);
}

// normalize double precision vector in place 
void HSQuery::normalize_vector(double* vector)
{
	double length;
	length = sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
	vector[0]/=length;
	vector[1]/=length;
	vector[2]/=length;
}

// perform the query and update the dialog with the model info
bool HSQuery::DoQuery()
{
	bool retval = false;
	char QueryString[MVO_BUFFER_SIZE];
	strcpy(QueryString,"");


#ifdef ACIS
	HC_KEY key = INVALID_KEY;
	HPoint camera, target, dummy;
	int count = 0, offset1, offset2, offset3;

	HC_Open_Segment_By_Key (GetView()->GetViewKey());
		HC_QSet_Selectability ("./scene/overwrite", "geometry=on!");
		count = HC_Compute_Selection (".", "./scene/overwrite", "v", GetNewPoint().x, GetNewPoint().y);
		HC_QUnSet_Selectability ("./scene/overwrite");
	HC_Close_Segment();

	if (count == 0)
		return false;

	HC_Open_Segment_By_Key(GetView()->GetSceneKey());
		HC_Show_Net_Camera_Position(&camera.x, &camera.y, &camera.z);
		HC_Show_Selection_Position(&dummy.x, &dummy.y, &dummy.z, &target.x, &target.y, &target.z);
		HC_Show_Selection_Element(&key, &offset1, &offset2, &offset3);
	HC_Close_Segment();

	if (key == INVALID_KEY)
		return false;

	ENTITY* entity = 0;
	BODY* body = 0;
	int n_edges, n_faces;

	if (!entity)
		body = (BODY*) HA_Compute_Entity_Pointer(key, BODY_TYPE);
	if (!entity && !body) 
	{
		return false;
	}

	ENTITY_LIST edges;
	outcome o = api_get_edges(body, edges);
	CHECK_OUTCOME( o );
	n_edges = edges.iteration_count();


	ENTITY_LIST faces;
	o = api_get_faces(body, faces);
	CHECK_OUTCOME( o );
	n_faces = faces.iteration_count();

	SPAposition picking_ray_pos(camera.x, camera.y, camera.z);
	// axis MUST contain a unit vector rw
	SPAunit_vector picking_ray_dir(target.x - camera.x,
		target.y - camera.y,
		target.z - camera.z);

	int hits_wanted = 1;
	hit* hit_list;
	int num_targets = 1;
	ENTITY* target_ents[] = { body };
	o = api_raytest_ents(picking_ray_pos, picking_ray_dir, 100*SPAresabs, 
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
		// get the body id
		char_offset = sprintf(QueryString + char_offset, 
			"Picked body is %d.\n\n"
			"This body contains:\n"
			"\t%d EDGEs\n"
			"\t%d FACEs.\n\n", 
			body, n_edges, n_faces);
		char_offset = sprintf(QueryString + char_offset, 
			"Analytical coordinates of surface along picking ray:\n"
			"\tx = %#.12f\n"
			"\ty = %#.12f\n"
			"\tz = %#.12f\n",
			int_pos.x(), int_pos.y(), int_pos.z());

		delete hit_list;

		retval = true;
	}
	else {
		sprintf(QueryString, "No geometry currently under cursor.");
	}

#ifdef IS_QT
	DialogMaker->SetQueryDialogText(QueryString);
#else
	m_SolidHoopsView->SetQueryDialogText(QueryString);
#endif

#endif // ACIS


	return retval;
}


// perform the query and update the dialog with the model info
bool HSQuery::DoQueryHoops()
{
	char type[MVO_BUFFER_SIZE];
	char QueryString[MVO_BUFFER_SIZE];
	int count, off1, off2, off3;
	HC_KEY key = 0;
	HPoint	awindow, world, object;

	HC_Open_Segment_By_Key (GetView()->GetViewKey());
	HC_QSet_Selectability ("./scene/overwrite", "geometry=on");
	count = HC_Compute_Selection (".", "./scene/overwrite", "v", GetNewPoint().x, GetNewPoint().y);
	HC_QUnSet_Selectability ("./scene/overwrite");
	HC_Close_Segment();
	HC_Open_Segment_By_Key (GetView()->GetSceneKey());
	if (count > 0)
	{
		HC_Show_Selection_Element(&key, &off1, &off2, &off3);
		HC_Show_Selection_Original_Key (&key);
		HC_Show_Selection_Position(&awindow.x, &awindow.y, &awindow.z, &world.x, &world.y, &world.z);
		HC_Show_Key_Type(key, type);
	}
	else 
	{
		HPoint tmp(GetNewPoint());
		HC_Compute_Coordinates(".","local window", &tmp, "world", &world);
		sprintf(type, "N/A");
		object = world;
	}

	int char_offset = 0;

	char_offset = sprintf(QueryString+char_offset, "\n\nGeometry key: %ld\nGeometry type: %s\n\n", key, type);

	if (streq(type, "shell"))
	{
		int	face_count, vertex_count, string_size;

		HC_Show_Shell_Size(key, &vertex_count, &face_count);
		string_size = sprintf(QueryString+char_offset, "Shell consists of %d vertices \n\n", vertex_count);
		char_offset += string_size;
	}
	else if (streq(type, "mesh"))
	{
		int	width_vcount, length_vcount, vertex_count, string_size;

		HC_Show_Mesh_Size(key, &length_vcount, &width_vcount);
		vertex_count = length_vcount * width_vcount;
		string_size = sprintf(QueryString+char_offset, "Mesh consists of %d vertices \n\n", vertex_count);
		char_offset += string_size;
	}
	else if( streq( type, "marker"))
	{
		float x,y,z;
		int string_size;
		HC_Show_Marker(key, &x, &y, &z);
		string_size = sprintf(QueryString+char_offset, "Marker Coordinates:\n\n  x = %#.6f\n  y = %#.6f\n  z = %#.6f\n\n", x, y, z);
		char_offset += string_size;
	}

	char_offset = sprintf(QueryString+char_offset, "Exact coordinates of Geometry along picking ray:\n\n  x = %#.6f\n  y = %#.6f\n  z = %#.6f\n", world.x, world.y, world.z);

	m_SolidHoopsView->SetQueryDialogText(QueryString);
	HC_Close_Segment();
	return true;
}

#ifdef IS_QT
void HSQuery::SetDialogMaker(MyHQSolidWidget* bla)
{
	DialogMaker=bla;
}
#else
void HSQuery::SetSolidHoopsView(CSolidHoopsView* view)
{
	m_SolidHoopsView = view;
}
#endif


int HSQuery::OnLButtonDownAndMove(HEventInfo &event)
{

#ifndef PARASOLID
	SetNewPoint(event.GetMouseWindowPos());
#endif

	// Mouse went down 
	int res;

	if(((HSolidModel *)(GetView()->GetModel()))->m_bSolidData)
		res = DoQuery();
	else
		res = DoQueryHoops();

	if (res)
#ifdef IS_QT
		DialogMaker->ShowQueryDialog();
#else
		m_SolidHoopsView->ShowQueryDialog(SW_SHOW);
#endif
	return (HOP_OK);
}
