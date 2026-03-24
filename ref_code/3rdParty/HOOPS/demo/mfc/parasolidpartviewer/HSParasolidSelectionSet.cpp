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
// $Header: /files/homes/master/cvs/hoops_master/parasolidpartviewer/HSParasolidSelectionSet.cpp,v 1.32 2009-09-25 00:43:49 nathan Exp $
//

// HSSelectionSet.cpp : implementation of the HPSelectionSet class
// 
#include "stdafx.h"
#include "resource.h"
#include "HSInclude.h"
#include <assert.h>

#include "topolbrowserdlg.h"
#include "HSParasolidSelectionSet.h"

#include "HSolidModel.h"
#include "HSolidView.h"

#include "HBaseOperator.h"

#include "hc.h"

#ifdef PARASOLID
#include "hp_bridge.h"
#endif

#ifdef ACIS
#include "ha_bridge.h"

// Required to use ENTITY class
#include "kernel/kerndata/data/entity.hxx"

// Required to use constant  FACE_TYPE
#include "kernel/kerndata/top/face.hxx"

// Required to use constant  EDGE_TYPE
#include "kernel/kerndata/top/edge.hxx"

// Required to use constant  BODY_TYPE
#include "kernel/kerndata/top/body.hxx"
#endif

#include <assert.h>
#include "vlist.h"




HSParasolidSelectionSet::HSParasolidSelectionSet ( HBaseView* view ) 
	: HSSelectionSet(view) 
{
 	m_SelectLevel = PK_CLASS_body;	// set default level to instance
	SetAllowEntitySelection(true);  // use entity selection
}

void HSParasolidSelectionSet::RefreshSolidSelection () {
	PK_ENTITY_t entities[40000];
	HC_KEY	keys[40000];
	int count;
	int size = vlist_count(m_pSolidSelection);
	int i;

	for ( i = 0 ; i < size ; i++ )
		entities[i] = (PK_ENTITY_t)vlist_nth_item(m_pSolidSelection, i);
	DeSelectAll();
	
	
	for ( i = 0 ; i < size ; i++ ) {
		vlist_add_last(m_pSolidSelection, (void*)entities[i]);
		
		PK_CLASS_t eclass;
		PK_ENTITY_ask_class(entities[i], &eclass);
		
		if (eclass == PK_CLASS_body)  // && 'body segments is true 
			count = HP_Compute_Geometry_Keys(entities[i], 1, keys, "bodies");
		else if (eclass == PK_CLASS_face) {
			count = HP_Compute_Geometry_Keys(entities[i], 40000, keys, "faces");
			if ( m_bShowFacesAsLines || HP_Get_Hash_Level() == 1 ) {	
				HC_KEY	keys[1000];
				PK_EDGE_t *edges;
				int n_edges;
				PK_FACE_ask_edges(entities[i], &n_edges, &edges);
				int j;
				for ( j = 0 ; j < n_edges ; j++ ) {
					int count = HP_Compute_Geometry_Keys(edges[j], 1000, keys, "edges");
					int c;
					for ( c = 0 ; c < count ; c++ )
						HSelectionSet::Select(keys[c], 0, NULL, true);  // call base class fcn for each key
				}
				PK_MEMORY_free(edges);
			}
		}
		
		else if (eclass == PK_CLASS_edge)
			count = HP_Compute_Geometry_Keys(entities[i], 40000, keys, "edges");
		else if (eclass == PK_CLASS_vertex)
			count = HP_Compute_Geometry_Keys(entities[i], 40000, keys, "vertices");

		int c;
		for ( c = 0 ; c < count ; c++ )
			HSelectionSet::Select(keys[c], 0, NULL, true);  // call base class fcn for each key
	}
}




void HSParasolidSelectionSet::Select ( HC_KEY key, int num_include_keys, HC_KEY *include_keys, 
									   bool emit_message ) {
	HC_KEY	keys[40000];
	int		count = 0, c;
	
	PK_ENTITY_t	entity = 0;
	
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true) {
		char	type[64];
		HC_KEY	segkey;
		
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;
		
		//HSelectionSet::Select(segkey, segpath, INVALID_KEY, INVALID_KEY, emit_message);
		HSelectionSet::Select(segkey, 0, 0, emit_message);
	}
	else {
		if ( m_pView->GetRenderMode() == HRenderHiddenLine && m_SelectLevel == PK_CLASS_face ) {
			HP_Set_Hash_Level(0);			 
			
			entity = HP_Compute_TagID(key, PK_CLASS_face);
			
			if (entity > 0) {
				vlist_add_last(m_pSolidSelection, (void*)entity);
				HP_Set_Hash_Level(1);			 
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
				
				for ( c = 0 ; c < count ; c++ )
					HSelectionSet::Select(keys[c], 0, NULL, emit_message);  // call base class fcn for each key
				
				PK_EDGE_t *edges;
				int n_edges;
				PK_FACE_ask_edges(entity, &n_edges, &edges);
				int i;
				for ( i = 0 ; i < n_edges ; i++ ) {
					count = HP_Compute_Geometry_Keys(edges[i], 40000, keys, "edges");
					for ( c = 0 ; c < count ; c++ )
						HSelectionSet::Select(keys[c], 0, NULL, emit_message);  // call base class fcn for each key
				}
				HP_Set_Hash_Level(0);
				PK_MEMORY_free(edges);
			}			 			
		}
		else {
			if (m_pView->GetRenderMode() == HRenderHiddenLine)
				HP_Set_Hash_Level(1);		

			char buffer[MVO_SMALL_BUFFER_SIZE],
				 merge_faces[4];
			HC_Show_Key_Type(key, buffer);
			HP_Show_One_Rendering_Option("merge faces", merge_faces);
			if ( streq(buffer, "shell") && streq(merge_faces, "on") ) {
				char *seg_name = new char [MVO_SEGMENT_PATHNAME_BUFFER];
				HC_Show_Owner_By_Key(key, seg_name);
				key = HC_KCreate_Segment(seg_name);
				HC_Show_Owner_By_Key(key, seg_name);
				key = HC_KCreate_Segment(seg_name);
				delete[] seg_name;
			}

			entity = HP_Compute_TagID(key, m_SelectLevel);
			
			if ( m_SelectLevel == PK_CLASS_instance || m_SelectLevel == PK_CLASS_assembly ) {
				HC_KEY includer_key = HC_KShow_Owner_By_Key(include_keys[0]);
				PK_INSTANCE_t instance = HP_Compute_TagID(includer_key, PK_CLASS_instance);
				
				if (instance) {
					if (m_SelectLevel == PK_CLASS_assembly) {
						PK_INSTANCE_sf_t in_sf;
						PK_INSTANCE_ask(instance,&in_sf);
						entity = in_sf.assembly;
					}
					else
						entity=instance;
				}
			}
			
			
			if (entity > 0) {
				vlist_add_last(m_pSolidSelection, (void*)entity);
				if (m_SelectLevel == PK_CLASS_instance)  // && body segments is true 
				{
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "instances");
				}
				else if (m_SelectLevel == PK_CLASS_assembly)  // && body segments is true 
				{
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "assemblies");
				}
				else if (m_SelectLevel == PK_CLASS_body)  // && body segments is true 
					count = HP_Compute_Geometry_Keys(entity, 1, keys, "bodies");
				else if (m_SelectLevel == PK_CLASS_face) {
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "faces");
					if (m_bShowFacesAsLines) {
						PK_EDGE_t *edges;
						int n_edges;
						PK_FACE_ask_edges(entity, &n_edges, &edges);
						int i;
						for ( i = 0 ; i < n_edges ; i++ ) {
							int ecount = HP_Compute_Geometry_Keys(edges[i], 40000-count, &keys[count], "edges");
							count += ecount;
						}
						PK_MEMORY_free(edges);
						
					}
				}
				else if (m_SelectLevel == PK_CLASS_edge)
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
				else if (m_SelectLevel == PK_CLASS_vertex)
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "vertices");
			}		 			
			assert(count < 40000);
			
			if (count) {
				for ( c = 0 ; c < count ; c++ ) {
					HSelectionSet::Select(keys[c], num_include_keys, include_keys, emit_message);  // call base class fcn for each key
				}
			}
			else if (entity == 0)
				// if there is no modeler entity corresponding to this key here, let base class handle
				// this is added here so that we are able to select cutting planes, notes etc. in modeler partviewer 
				// Rajesh B (2-May-03)
				HSelectionSet::Select(key, num_include_keys, include_keys, emit_message );
			
			HP_Set_Hash_Level(0);
		}
	}
}


void HSParasolidSelectionSet::Select ( HC_KEY key, const char *segpath, HC_KEY include_key, 
									   HC_KEY includer_key, bool emit_message ) {
	HC_KEY	keys[40000];
	int		count = 0, c;
	
	PK_ENTITY_t	entity = 0;
	
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true) {
		char	type[64];
		HC_KEY	segkey;
		
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;
		
		HSelectionSet::Select(segkey, segpath, INVALID_KEY, INVALID_KEY, emit_message);
	}
	else {
		if ( m_pView->GetRenderMode() == HRenderHiddenLine && m_SelectLevel == PK_CLASS_face ) {
			HP_Set_Hash_Level(0);			 
			
			entity = HP_Compute_TagID(key, PK_CLASS_face);
			
			if (entity > 0) {
				vlist_add_last(m_pSolidSelection, (void*)entity);
				HP_Set_Hash_Level(1);			 
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
				
				for ( c = 0 ; c < count ; c++ )
					HSelectionSet::Select(keys[c], 0, NULL, emit_message);  // call base class fcn for each key
				
				PK_EDGE_t *edges;
				int n_edges;
				PK_FACE_ask_edges(entity, &n_edges, &edges);
				int i;
				for ( i = 0 ; i < n_edges ; i++ ) {
					count = HP_Compute_Geometry_Keys(edges[i], 40000, keys, "edges");
					for ( c = 0 ; c < count ; c++ )
						HSelectionSet::Select(keys[c], 0, NULL, emit_message);  // call base class fcn for each key
				}
				HP_Set_Hash_Level(0);
				PK_MEMORY_free(edges);
			}			 			
		}
		else {
			if (m_pView->GetRenderMode() == HRenderHiddenLine)
				HP_Set_Hash_Level(1);	

			char buffer[MVO_SMALL_BUFFER_SIZE],
				merge_faces[4];
			HC_Show_Key_Type(key, buffer);
			HP_Show_One_Rendering_Option("merge faces", merge_faces);
			if ( streq(buffer, "shell") && streq(merge_faces, "on") ) {
				char *seg_name = new char [MVO_SEGMENT_PATHNAME_BUFFER];
				HC_Show_Owner_By_Key(key, seg_name);
				key = HC_KCreate_Segment(seg_name);
				HC_Show_Owner_By_Key(key, seg_name);
				key = HC_KCreate_Segment(seg_name);
				delete[] seg_name;
			}
			
			entity = HP_Compute_TagID(key, m_SelectLevel);
			
			if ( m_SelectLevel == PK_CLASS_instance || m_SelectLevel == PK_CLASS_assembly ) {
				PK_INSTANCE_t instance = HP_Compute_TagID(includer_key, PK_CLASS_instance);
				
				if (instance) {
					if (m_SelectLevel == PK_CLASS_assembly) {
						PK_INSTANCE_sf_t in_sf;
						PK_INSTANCE_ask(instance,&in_sf);
						entity = in_sf.assembly;
					}
					else
						entity = instance;
				}
			}
			
			
			if (entity > 0) {
				vlist_add_last(m_pSolidSelection, (void*)entity);
				if (m_SelectLevel == PK_CLASS_instance)  // && body segments is true 
				{
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "instances");
				}
				else if (m_SelectLevel == PK_CLASS_assembly)  // && body segments is true 
				{
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "assemblies");
				}
				else if (m_SelectLevel == PK_CLASS_body)  // && body segments is true 
					count = HP_Compute_Geometry_Keys(entity, 1, keys, "bodies");
				else if (m_SelectLevel == PK_CLASS_face) {
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "faces");
					if (m_bShowFacesAsLines) {
						PK_EDGE_t *edges;
						int n_edges;
						PK_FACE_ask_edges(entity, &n_edges, &edges);
						int i;
						for ( i = 0 ; i < n_edges ; i++ ) {
							int ecount = HP_Compute_Geometry_Keys(edges[i], 40000-count, &keys[count], "edges");
							count += ecount;
						}
						PK_MEMORY_free(edges);
						
					}
				}
				else if (m_SelectLevel == PK_CLASS_edge)
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
				else if (m_SelectLevel == PK_CLASS_vertex)
					count = HP_Compute_Geometry_Keys(entity, 40000, keys, "vertices");
			}		 			
			assert(count < 40000);
			
			if (count) {
				for ( c = 0 ; c < count ; c++ ) {
					HSelectionSet::Select(keys[c], 0, NULL,  emit_message);  // call base class fcn for each key
				}
			}
			else if (entity == 0)
				// if there is no modeler entity corresponding to this key here, let base class handle
				// this is added here so that we are able to select cutting planes, notes etc. in modeler partviewer 
				// Rajesh B (2-May-03)
				HSelectionSet::Select(key, 1, &include_key,  emit_message );
			
			HP_Set_Hash_Level(0);
		}
	}
}



void HSParasolidSelectionSet::DeSelect ( HC_KEY key, int num_include_keys, HC_KEY *include_keys, 
										 bool emit_message ) {
	HC_KEY keys[40000];
	int count = 0, c;
	
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true) {
		char	type[64];
		HC_KEY	segkey;
		
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;
		
		HSelectionSet::DeSelect(key, 0, NULL, emit_message);
	}
	else {
		PK_ENTITY_t	entity = 0;
		int			n = 0;
		
		entity = HP_Compute_TagID(key, m_SelectLevel);
		
		if (entity > 0) {
			vlist_remove(m_pSolidSelection, (void*) entity);
			
			if (m_SelectLevel == PK_CLASS_body)  // && 'body segments is true 
				count = HP_Compute_Geometry_Keys(entity, 1, keys, "bodies");
			else if (m_SelectLevel == PK_CLASS_face)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "faces");
			else if (m_SelectLevel == PK_CLASS_edge)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
			else if (m_SelectLevel == PK_CLASS_vertex)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "vertices");
		}
		
		assert(count < 40000);
		
		if (count) {
			for ( c = 0 ; c < count ; c++ ) {
				HSelectionSet::DeSelect(keys[c], emit_message);	// call base class fcn for each key
			}
		}
		else
			HSelectionSet::DeSelect(key, emit_message);
		
	}
}


void HSParasolidSelectionSet::DeSelect ( HC_KEY key, bool emit_message ) {
	HC_KEY keys[40000];
	int count = 0, c;
	
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true) {
		char	type[64];
		HC_KEY	segkey;
		
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;
		
		HSelectionSet::DeSelect(segkey, emit_message);
	}
	else {
		PK_ENTITY_t	entity = 0;
		int			n = 0;
		
		entity = HP_Compute_TagID(key, m_SelectLevel);
		
		if (entity > 0) {
			vlist_remove(m_pSolidSelection, (void*) entity);
			
			if (m_SelectLevel == PK_CLASS_body)  // && 'body segments is true 
				count = HP_Compute_Geometry_Keys(entity, 1, keys, "bodies");
			else if (m_SelectLevel == PK_CLASS_face)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "faces");
			else if (m_SelectLevel == PK_CLASS_edge)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
			else if (m_SelectLevel == PK_CLASS_vertex)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "vertices");
		}
		
		assert(count < 40000);
		
		if (count) {
			for ( c = 0 ; c < count ; c++ ) {
				HSelectionSet::DeSelect(keys[c], emit_message);	// call base class fcn for each key
			}
		}
		else
			HSelectionSet::DeSelect(key, emit_message);
		
	}
}

void HSParasolidSelectionSet::DeSelectEntity ( PK_ENTITY_t entity, bool emit_message ) {
	HC_KEY keys[40000];
	int count = 0, c;
	int n = 0;
	
	if (entity > 0) {
		vlist_remove( m_pSolidSelection, (void*) entity);
		
		if (m_SelectLevel == PK_CLASS_body)  // && 'body segments is true 
			count = HP_Compute_Geometry_Keys(entity, 1, keys, "bodies");
		else if (m_SelectLevel == PK_CLASS_face)
			count = HP_Compute_Geometry_Keys(entity, 40000, keys, "faces");
		else if (m_SelectLevel == PK_CLASS_edge)
			count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
		else if (m_SelectLevel == PK_CLASS_vertex)
			count = HP_Compute_Geometry_Keys(entity, 40000, keys, "vertices");
	}
	
	assert(count < 40000);
	
	if (count) {
		for ( c = 0 ; c < count ; c++ ) {
			HSelectionSet::DeSelect(keys[c], emit_message);	// call base class fcn for each key
		}
	}
}


bool HSParasolidSelectionSet::IsSelected(HC_KEY key, int num_include_keys, const HC_KEY * include_keys) const
{
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true) {
		char	type[MVO_BUFFER_SIZE];
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			key = HC_KShow_Owner_By_Key(key);
	}
	else {
		if (m_SelectLevel == PK_CLASS_body)  // && body segments is true
		{
			PK_ENTITY_t entity = 0;
			int count;
			
			entity = HP_Compute_TagID(key, m_SelectLevel);
			
			if (entity > 0)
			{
				count = HP_Compute_Geometry_Keys(entity, 1, &key, "bodies");
				assert(count == 1);
			}
		}
		if (m_SelectLevel == PK_CLASS_instance)  // && body segments is true
		{
			PK_ENTITY_t entity = 0;
			int count;
			
			entity = HP_Compute_TagID(key, m_SelectLevel);
			
			if (entity > 0)
			{
				count = HP_Compute_Geometry_Keys(entity, 1, &key, "instances");
				assert(count == 1);
			}
		}
		
	}
	// call base class function with the computed key
	return HSelectionSet::IsSelected(key);
}

bool HSParasolidSelectionSet::IsSelected ( HC_KEY key ) {
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true) {
		char	type[MVO_BUFFER_SIZE];
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			key = HC_KShow_Owner_By_Key(key);
	}
	else {
		if (m_SelectLevel == PK_CLASS_body)  // && body segments is true
		{
			PK_ENTITY_t entity = 0;
			int count;
			
			entity = HP_Compute_TagID(key, m_SelectLevel);
			
			if (entity > 0)
			{
				count = HP_Compute_Geometry_Keys(entity, 1, &key, "bodies");
				assert(count == 1);
			}
		}
		if (m_SelectLevel == PK_CLASS_instance)  // && body segments is true
		{
			PK_ENTITY_t entity = 0;
			int count;
			
			entity = HP_Compute_TagID(key, m_SelectLevel);
			
			if (entity > 0)
			{
				count = HP_Compute_Geometry_Keys(entity, 1, &key, "instances");
				assert(count == 1);
			}
		}
		
	}
	// call base class function with the computed key
	return HSelectionSet::IsSelected(key);
}

void HSParasolidSelectionSet::Select ( PK_ENTITY_t entity, bool emit_message ) {
	HC_KEY	keys[40000];
	int		count = 0, c;
	PK_CLASS_t eclass;	
	
	PK_ENTITY_ask_class(entity, &eclass);
	
	if ( m_pView->GetRenderMode() == HRenderHiddenLine && eclass == PK_CLASS_face ) {
		HP_Set_Hash_Level(0);			 
		
		if (entity > 0) {
			vlist_add_last( m_pSolidSelection, (void*)entity);
			HP_Set_Hash_Level(1);			 
			count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
			
			for (c = 0; c < count; c++)
				HSelectionSet::Select(keys[c], 0, NULL, emit_message);  // call base class fcn for each key
			
			PK_EDGE_t *edges;
			int n_edges;
			PK_FACE_ask_edges(entity, &n_edges, &edges);
			int i;
			for ( i = 0 ; i < n_edges ; i++ ) {
				count = HP_Compute_Geometry_Keys(edges[i], 40000, keys, "edges");
				for ( c = 0 ; c < count ; c++ )
					HSelectionSet::Select(keys[c], 0, NULL, emit_message);  // call base class fcn for each key
			}
			HP_Set_Hash_Level(0);
			PK_MEMORY_free(edges);
		}			 			
	}
	else {
		if (m_pView->GetRenderMode() == HRenderHiddenLine)
			HP_Set_Hash_Level(1);		
		PK_CLASS_t eclass;
		PK_ENTITY_ask_class(entity, &eclass);
		
		if (entity > 0) {
			vlist_add_last( m_pSolidSelection, (void*)entity);
			if (eclass == PK_CLASS_assembly)  // && body segments is true 
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "assemblies");
			else if (eclass == PK_CLASS_instance)  // && body segments is true 
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "instances");
			else if (eclass == PK_CLASS_body)  // && body segments is true 
				count = HP_Compute_Geometry_Keys(entity, 1, keys, "bodies");
			else if (eclass == PK_CLASS_face) {
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "faces");
				if (m_bShowFacesAsLines) {
					PK_EDGE_t *edges;
					int n_edges;
					PK_FACE_ask_edges(entity, &n_edges, &edges);
					int i;
					for ( i = 0 ; i < n_edges ; i++ ) {
						int ecount = HP_Compute_Geometry_Keys(edges[i], 40000-count, &keys[count], "edges");
						count += ecount;
					}
					PK_MEMORY_free(edges);
				}
			}			
			else if (eclass == PK_CLASS_edge)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "edges");
			else if (eclass == PK_CLASS_vertex)
				count = HP_Compute_Geometry_Keys(entity, 40000, keys, "vertices");
		}
		
		assert(count < 40000);
		
		if (count) {
			for ( c = 0 ; c < count ; c++ ) {
				if(keys[c] != INVALID_KEY && HC_Show_Existence_By_Key(keys[c], "self") )
					HSelectionSet::Select(keys[c], "", INVALID_KEY, INVALID_KEY, emit_message);  // call base class fcn for each key
			}
		}
		HP_Set_Hash_Level(0);
	}
}
