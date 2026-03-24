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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSQueryAdvanced.cpp,v 1.17 2009-05-22 18:52:24 stage Exp $
//

#include "stdafx.h"
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
#include "HSQueryAdvanced.h"

#include "hc.h"
#include "vlist.h"

#ifndef HOOPS_ONLY
#include "CBinaryFileToolkit.h"
#endif // HOOPS_ONLY


#include <stdio.h>
#include <assert.h>
#include <math.h>

#define TEMP_FACE_HIGHLIGHT		"HSQueryAdvanced_temp_face_higlight"


/////////////////////////////////////////////////////////////////////////////
// HSQueryAdvanced

// Operator for querying model
// Mouse down - displays modeless query dialog containing and computes information 
// about the part intersected by the calculated picking ray
// Mouse motion while down - dynamically updates the dialog based on new picking ray


HSQueryAdvanced::HSQueryAdvanced(HBaseView* view, int DoRepeat, int DoCapture) : HBaseOperator(view, DoRepeat, DoCapture)
{
}

HSQueryAdvanced::~HSQueryAdvanced( void )
{
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());
	if( HC_QShow_Existence( TEMP_FACE_HIGHLIGHT, "self" )) {
		HC_Delete_Segment(TEMP_FACE_HIGHLIGHT);
		GetView()->Update();
	}
	HC_Close_Segment(); 
}

const char * HSQueryAdvanced::GetName()
{
	return "QueryAdvanced";
}

int HSQueryAdvanced::OnLButtonDown(HEventInfo &event)
{

#ifndef PARASOLID
	SetNewPoint(event.GetMouseWindowPos());
#endif

	int res;

	if(((HSolidModel *)(GetView()->GetModel()))->m_bSolidData)
		res = DoQuery();
	else
		res = DoQueryHoops();

	if (res)
#ifdef IS_QT
		DialogMaker->ShowAdvancedQueryDialog();
#else
		m_SolidHoopsView->ShowAdvancedQueryDialog(SW_SHOW);
#endif

	return (HOP_OK);
}


int HSQueryAdvanced::OnLButtonUp(HEventInfo &event)
{
	return HBaseOperator::OnLButtonUp(event);
}

// normalize double precision vector in place 
void HSQueryAdvanced::normalize_vector(double* vector)
{
	double length;
	length = sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
	vector[0]/=length;
	vector[1]/=length;
	vector[2]/=length;
}


// perform the query and update the dialog with the model info
// perform the query and update the dialog with the model info
bool HSQueryAdvanced::DoQuery()
{
	bool retval = false;
	char QueryString[MVO_BUFFER_SIZE];
	strcpy(QueryString,"");


#ifdef ACIS
	HC_KEY key;
	HPoint camera, target, dummy;
	int count, offset1, offset2, offset3;

	HC_Open_Segment_By_Key (GetView()->GetViewKey());
	HC_QSet_Selectability ("./scene/overwrite", "geometry=on!");
	count = HC_Compute_Selection (".", "./scene/overwrite", "v", GetNewPoint().x, GetNewPoint().y);
	HC_QUnSet_Selectability ("./scene/overwrite");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(GetView()->GetSceneKey());
	HC_Show_Net_Camera_Position(&camera.x, &camera.y, &camera.z);

	HC_Show_Selection_Position(&dummy.x, &dummy.y, &dummy.z, &target.x, &target.y, &target.z);
	HC_Show_Selection_Element(&key, &offset1, &offset2, &offset3);
	HC_Close_Segment();

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
		hits_wanted, num_targets, target_ents, hit_list);

	if (hit_list)
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
	DialogMaker->SetAdvancedQueryDialogText(QueryString);
#else
	m_SolidHoopsView->SetQueryDialogText(QueryString);
#endif

#endif // ACIS


	return retval;
}

static void IncludeEntity(HBaseView *view, HC_KEY movekey)
{

	char color[MVO_BUFFER_SIZE];
	char segmentname[MVO_SEGMENT_PATHNAME_BUFFER];
	float matrix[16];
	float identmatrix[16];

	HC_Open_Segment_By_Key(view->GetSceneKey());
	HC_Open_Segment(TEMP_FACE_HIGHLIGHT);
	HC_KEY tempkey = HC_KCreate_Segment("osel_temp");
	HC_Close_Segment();
	HC_Close_Segment();


	HC_KEY ownerkey = HC_KShow_Owner_By_Key(movekey);
	HC_Open_Segment_By_Key(ownerkey);
	HC_Show_Segment(movekey, segmentname);
	HC_Show_Net_Color(color);
	//    HC_Show_Net_Visibility(visibility);
	HC_Show_Net_Modelling_Matrix(matrix);
	HC_Close_Segment();

	HC_Open_Segment_By_Key(tempkey);
	HC_Flush_Contents(".", "everything");
	HC_Set_Visibility("faces = off, edges = (perimeters=on), lines = off, markers = off");
	HC_Set_Color("edges = black");
	HC_Set_Rendering_Options("attribute lock = color");
	HC_Set_Edge_Weight(1.0f);
	HC_Set_Selectability("everything = off");
	HC_Compute_Identity_Matrix(identmatrix); 
	HC_Set_Modelling_Matrix(identmatrix);
	HC_Open_Segment("tempdata");
	HC_Open_Segment("");
	HC_Set_Modelling_Matrix(matrix);
	HC_Open_Segment("temp");
	HC_Include_Segment_By_Key(movekey);
	HC_Close_Segment();
	HC_Open_Segment("temp2");
	HC_Include_Segment_By_Key(movekey);
	HC_Set_Edge_Pattern("- -");
	HC_Set_Rendering_Options("depth range=(0,0.1)");    

	HC_Close_Segment();


	HUtility::CloseAllSegments(tempkey);
}


void HSQueryAdvanced::highlight_face(HC_KEY key, int o1, int o2, int o3)
{
	//HC_Show_Selection_Element(&key, &o1, &o2, &o3);
	HC_KEY skey = HUtility::GrabSegment(key);
	HUtility::UnwindIncludes(skey);

	int plen, flen;
	HPoint *points;
	int *faces;
	float matrix[16];

	HC_Show_Shell_Size(key, &plen, &flen);
	points = new HPoint[plen];
	faces = new int[flen];
	HC_Show_Shell(key, &plen, points, &flen, faces);

	HC_Open_Segment_By_Key(skey);
	HC_Show_Net_Modelling_Matrix(matrix);
	HC_Close_Segment();
	//	m_Point1 = points[o1];
	//	m_Point2 = points[o2];
	//	m_SegKey = skey;


	//	m_bFound = true;
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());
	HC_Open_Segment(TEMP_FACE_HIGHLIGHT);
	HC_Flush_Contents(".", "everything");

	HC_Set_Visibility("markers = on, lines = on");
	HC_Set_Line_Weight(2.0f);
	HC_Set_Marker_Size(0.5f);

	IncludeEntity(GetView(),skey);
	int findex =  HUtility::FindFaceByIndex(o3, faces, flen);
	HPoint *oneface = new HPoint[faces[findex] + 1];

	for (int i=0;i<faces[findex];i++)		
		oneface[i] = points[faces[findex + i + 1]];

	oneface[faces[findex]] = points[faces[findex + 1]];
	HC_Compute_Transformed_Points(faces[findex] + 1, oneface, matrix, oneface);

	HC_Open_Segment("");
	HC_Set_Rendering_Options("depth range=(0,0.1)");
	HC_Insert_Polyline(faces[findex] + 1, oneface);

	HC_Compute_Transformed_Points(1, &points[o1], matrix, &points[o1]);
	HC_Compute_Transformed_Points(1, &points[o2], matrix, &points[o2]);

	HC_Insert_Marker(points[o1].x, points[o1].y, points[o1].z);
	HC_Insert_Marker(points[o2].x, points[o2].y, points[o2].z);
	HC_Insert_Line(points[o1].x, points[o1].y,points[o1].z, points[o2].x, points[o2].y,
		points[o2].z);
	HC_Close_Segment();
	HC_Close_Segment();
	HC_Close_Segment(); 
	delete [] oneface;
	delete [] points;
	delete [] faces;
}


// perform the query and update the dialog with the model info
bool HSQueryAdvanced::DoQueryHoops()
{
	char type[MVO_BUFFER_SIZE];
	char QueryString[MVO_BUFFER_SIZE];
	int i, count, off1=0, off2=0, off3=0;
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
		//get the "non-renumbered" version of the key, so that we won't need to have its
		//  owning segment open to find it (just in case it's a local renumber)
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

	char_offset += sprintf(QueryString+char_offset, "Geometry:\r\n"); 
	char_offset += sprintf(QueryString+char_offset, "  key: %ld\r\n", key);
	char_offset += sprintf(QueryString+char_offset, "  type: %s\r\n", type);
	char_offset += sprintf(QueryString+char_offset, "-----------------------------\r\n");

	if (streq(type, "shell"))
	{
		int	face_count, vertex_count, flist_length;
		int	*flist;

		HC_Show_Shell_Size(key, &vertex_count, &face_count);
		HC_Show_Partial_Shell_Size( key, off3, 1, &flist_length );

		flist = (int *)malloc (sizeof(int) * flist_length);
		HC_Show_Partial_Shell (key, 0, 0, NULL, off3, 1, &flist_length, flist);


		char_offset += sprintf(QueryString+char_offset, "Shell:\r\n");

		char_offset += sprintf(QueryString+char_offset, " vertices: %d\r\n", vertex_count);
		char_offset += sprintf(QueryString+char_offset, " facelist length: %d\r\n", face_count);
		char_offset += sprintf(QueryString+char_offset, "------------------------------------------------------------------------------------------------------------------\r\n");

		char_offset += sprintf(QueryString+char_offset, "Face:\r\n");
		char_offset += sprintf(QueryString+char_offset, " id: %d\r\n", off3);

		HC_Open_Geometry (key);

		char_offset += sprintf(QueryString+char_offset, " vertices: %d\r\n", flist_length-1);
		for(i=1; i<flist_length; i++)
		{
			float pts[3], nml[3];
			int is_vn_explicit;

			HC_Show_Partial_Shell (key, flist[i], 1, pts, 0, 0, NULL, NULL);
			HC_Open_Vertex (flist[i]);
			is_vn_explicit = HC_Show_Existence("normal");
			HC_Show_Net_Normal (&nml[0], &nml[1], &nml[2]);
			HC_Close_Vertex ();

			char_offset += sprintf(QueryString+char_offset, "  %d (%f %f %f)%sNormal: %f %f %f\r\n", 
				flist[i], pts[0], pts[1], pts[2], ((is_vn_explicit == 0) ? " " : " x"), nml[0], nml[1], nml[2]);
		}

		float face_nml[3];
		int is_fn_explicit;
		HC_Open_Face(off3);
		is_fn_explicit = HC_Show_Existence("normal");
		HC_Show_Net_Normal (&face_nml[0], &face_nml[1], &face_nml[2]);
		char_offset += sprintf(QueryString+char_offset, " %snormal: %f %f %f\r\n", 
			((is_fn_explicit == 0) ? "" : " x"), face_nml[0], face_nml[1], face_nml[2]);
		HC_Close_Face();


		char_offset += sprintf(QueryString+char_offset, "------------------------------------------------------------------------------------------------------------------\r\n");

		char_offset += sprintf(QueryString+char_offset, "Vertex:\r\n");
		char_offset += sprintf(QueryString+char_offset, " id: %d\r\n", off1);
		HC_Open_Vertex (off1);
		if (HC_Show_Existence ("parameter")) {
			float params[128];
			int params_width;

			char_offset += sprintf(QueryString+char_offset, " parameters:\r\n", off1);
			HC_Show_Parameter (&params_width, params);
			for (i = 0 ; i < params_width - 1 ; i++) {
				char_offset += sprintf(QueryString+char_offset, "%3.2f,\t", params[i]);
				if (i % 8 == 7)
					char_offset += sprintf(QueryString+char_offset, "\r\n", params[i]);
			}
			char_offset += sprintf(QueryString+char_offset, "%3.2f\r\n", params[i]);
		}
		if (HC_Show_Existence ("normal"))
			char_offset += sprintf(QueryString+char_offset, "explicit ");
		float normal[3];
		HC_Show_Net_Normal (&normal[0], &normal[1], &normal[2]);
		char_offset += sprintf(QueryString+char_offset, "normal: %f, %f, %f\r\n", normal[0], normal[1], normal[2]);
		HC_Close_Vertex();

		char_offset += sprintf(QueryString+char_offset, "------------------------------------------------------------------------------------------------------------------\r\n");
		free(flist);
		HC_Close_Geometry();
		highlight_face(key, off1, off2, off3);
	}
	else if (streq(type, "mesh"))
	{
		int	width_vcount, length_vcount, vertex_count, string_size;

		HC_Show_Mesh_Size(key, &length_vcount, &width_vcount);
		vertex_count = length_vcount * width_vcount;
		string_size = sprintf(QueryString+char_offset, "Mesh consists of %d vertices \r\n\r\n", vertex_count);
		char_offset += string_size;
	}
	else if( streq( type, "marker"))
	{
		float x,y,z;
		int string_size;
		HC_Show_Marker(key, &x, &y, &z);
		string_size = sprintf(QueryString+char_offset, "Marker Coordinates:\r\n\r\n  x = %#.6f\r\n  y = %#.6f\r\n  z = %#.6f\r\n\r\n", x, y, z);
		char_offset += string_size;
	}

	char_offset = sprintf(QueryString+char_offset, "Exact picking coordinates:\r\n  x = %#.6f\r\n  y = %#.6f\r\n  z = %#.6f\r\n", world.x, world.y, world.z);

	m_SolidHoopsView->SetAdvancedQueryDialogText(QueryString);

	HC_Close_Segment();

	GetView()->Update();

	return true;
}


#ifdef IS_QT
void HSQueryAdvanced::SetDialogMaker(MyHQSolidWidget* bla)
{
	DialogMaker=bla;
}
#else
void HSQueryAdvanced::SetSolidHoopsView(CSolidHoopsView* view)
{
	m_SolidHoopsView = view;
}
#endif


int HSQueryAdvanced::OnLButtonDownAndMove(HEventInfo &event)
{

#ifndef PARASOLID
	SetNewPoint(event.GetMouseWindowPos());
#endif

	int res;

	if(((HSolidModel *)(GetView()->GetModel()))->m_bSolidData)
		res = DoQuery();
	else
		res = DoQueryHoops();

	if (res)
#ifdef IS_QT
		DialogMaker->ShowAdvancedQueryDialog();
#else
		m_SolidHoopsView->ShowAdvancedQueryDialog(SW_SHOW);
#endif
	return (HOP_OK);
}
