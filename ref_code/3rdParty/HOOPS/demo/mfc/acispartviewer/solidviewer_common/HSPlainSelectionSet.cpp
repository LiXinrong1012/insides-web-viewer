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
// $Header: /files/homes/master/cvs/hoops_master/shared/solidviewer_common/HSPlainSelectionSet.cpp,v 1.22 2007-10-16 23:19:24 stage Exp $
//

// HSSelectionSet.cpp : implementation of the HPSelectionSet class
// 
#include "stdafx.h"
#include "resource.h"
#include "HSInclude.h"

#include "HSPlainSelectionSet.h"

#include "HSolidModel.h"
#include "HSolidView.h"
#include "topolbrowserdlg.h"

#include "HBaseOperator.h"

#include "hc.h"

#include "CBinaryFileToolkit.h"
#include "vlist.h"

HSPlainSelectionSet::HSPlainSelectionSet(HBaseView* view) : HSSelectionSet(view)
{
	m_SelectLevel = KERN_BODY_TYPE;	// set default level to body
}

void HSPlainSelectionSet::RefreshSolidSelection()
{
	;
}


void HSPlainSelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HC_KEY	keys[40000];
	int		count = 0, c;

	long entity = 0;

	if (((HSolidModel *) m_pView->GetModel())->m_bSolidData != true)
	{
		char	type[MVO_BUFFER_SIZE];
		HC_KEY	segkey;

		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;

		HSelectionSet::Select(segkey, num_include_keys, include_keys, emit_message);
	}
	else
	{
		CModellerInfo* mi = ((HSolidModel *)m_pView->GetModel())->m_mi;

		entity = mi->Compute_Entity_Index(key,m_SelectLevel);

		if (entity > 0)
		{
			vlist_add_last(m_pSolidSelection, (void *)entity );
			if (m_SelectLevel == KERN_BODY_TYPE)  // && body segments is true 
				count = mi->Compute_Geometry_Keys(entity,1,keys);
			else if (m_SelectLevel == KERN_FACE_TYPE)
			{
				count = mi->Compute_Geometry_Keys(entity,40000,keys);
				if (m_bShowFacesAsLines)
				{
					int numedges;
					long *edges;
					mi->FACE_ask_edges(entity,&numedges, &edges);

					for (int edgenum=0;edgenum<numedges;edgenum++)
					{
						int ecount = mi->Compute_Geometry_Keys(edges[edgenum],40000-count,&keys[count]);
						count += ecount;
					}
				}
			}
			else if (m_SelectLevel == KERN_EDGE_TYPE)
				count = mi->Compute_Geometry_Keys(entity,40000,keys);
		}

		assert(count < 40000);

		if (count)
		{
			for (c = 0; c < count; c++)
			{
				HSelectionSet::Select(keys[c], 0, 0, emit_message);  // call base class fcn for each key
			}
		}
#ifdef PARASOLID
		HP_Set_Hash_Level(0);
#endif // PARASOLID

	}
}

void HSPlainSelectionSet::Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message)
{
	HC_KEY	keys[40000];
	int		count = 0, c;
	
	long entity = 0;
	
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidData != true)
	{
		char	type[MVO_BUFFER_SIZE];
		HC_KEY	segkey;
		
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;
		
		HSelectionSet::Select(segkey, segpath, INVALID_KEY, INVALID_KEY, emit_message);
	}
	else
	{
		CModellerInfo* mi = ((HSolidModel *)m_pView->GetModel())->m_mi;
		
		entity = mi->Compute_Entity_Index(key,m_SelectLevel);
		
		if (entity > 0)
		{
			vlist_add_last(m_pSolidSelection, (void *)entity );
			if (m_SelectLevel == KERN_BODY_TYPE)  // && body segments is true 
				count = mi->Compute_Geometry_Keys(entity,1,keys);
			else if (m_SelectLevel == KERN_FACE_TYPE)
			{
				count = mi->Compute_Geometry_Keys(entity,40000,keys);
				if (m_bShowFacesAsLines)
				{
					int numedges;
					long *edges;
					mi->FACE_ask_edges(entity,&numedges, &edges);
					
					for (int edgenum=0;edgenum<numedges;edgenum++)
					{
						int ecount = mi->Compute_Geometry_Keys(edges[edgenum],40000-count,&keys[count]);
						count += ecount;
					}
				}
			}
			else if (m_SelectLevel == KERN_EDGE_TYPE)
				count = mi->Compute_Geometry_Keys(entity,40000,keys);
		}
		
		assert(count < 40000);
		
		if (count)
		{
			for (c = 0; c < count; c++)
			{
				HSelectionSet::Select(keys[c], segpath, INVALID_KEY, INVALID_KEY, emit_message);  // call base class fcn for each key
			}
		}
#ifdef PARASOLID
		HP_Set_Hash_Level(0);
#endif // PARASOLID
		
	}
}


void HSPlainSelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HC_KEY keys[40000];
	int count = 0, c;

	if (((HSolidModel *) m_pView->GetModel())->m_bSolidData != true)
	{
		char	type[MVO_BUFFER_SIZE];
		HC_KEY	segkey;

		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;

		HSelectionSet::DeSelect(segkey, num_include_keys, include_keys, emit_message);
	}
	else
	{
		long entity = 0;
		int	 n = 0;

		CModellerInfo* mi = ((HSolidModel *)m_pView->GetModel())->m_mi;
		entity = mi->Compute_Entity_Index(key,m_SelectLevel);

		if (entity > 0)
		{
			vlist_remove( m_pSolidSelection, (void*) entity);

			if (m_SelectLevel == KERN_BODY_TYPE)  // && 'body segments is true 
				count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,1,keys);
			else if (m_SelectLevel == KERN_FACE_TYPE)
				count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,40000,keys);
			else if (m_SelectLevel == KERN_EDGE_TYPE)
				count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,40000,keys);
		}


		assert(count < 40000);

		if (count)
		{
			for (c = 0; c < count; c++)
			{
				HSelectionSet::DeSelect(keys[c], emit_message);	// call base class fcn for each key
			}
		}
		else
			HSelectionSet::DeSelect(key, emit_message);

	}

}

void HSPlainSelectionSet::DeSelect(HC_KEY key, bool emit_message )
{
	HC_KEY keys[40000];
	int count = 0, c;
	
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidData != true)
	{
		char	type[MVO_BUFFER_SIZE];
		HC_KEY	segkey;
		
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			segkey = HC_KShow_Owner_By_Key(key);
		else
			segkey = key;
		
		HSelectionSet::DeSelect(segkey, emit_message);
	}
	else
	{
		long entity = 0;
		int	 n = 0;
		
		CModellerInfo* mi = ((HSolidModel *)m_pView->GetModel())->m_mi;
		entity = mi->Compute_Entity_Index(key,m_SelectLevel);
		
		if (entity > 0)
		{
			vlist_remove( m_pSolidSelection, (void*) entity);
			
			if (m_SelectLevel == KERN_BODY_TYPE)  // && 'body segments is true 
				count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,1,keys);
			else if (m_SelectLevel == KERN_FACE_TYPE)
				count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,40000,keys);
			else if (m_SelectLevel == KERN_EDGE_TYPE)
				count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,40000,keys);
		}
		
		
		assert(count < 40000);
		
		if (count)
		{
			for (c = 0; c < count; c++)
			{
				HSelectionSet::DeSelect(keys[c], emit_message);	// call base class fcn for each key
			}
		}
		else
			HSelectionSet::DeSelect(key, emit_message);
		
	}
	
}

void HSPlainSelectionSet::DeSelectEntity(long entity, bool emit_message )
{
	HC_KEY keys[40000];
	int count = 0, c;
	int n = 0;
	
	
	if (entity > 0)
	{
		vlist_remove( m_pSolidSelection, (void*) entity);
		
		if (m_SelectLevel == KERN_BODY_TYPE)  // && 'body segments is true 
			count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,1,keys);
		else if (m_SelectLevel == KERN_FACE_TYPE)
			count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,40000,keys);
		else if (m_SelectLevel == KERN_EDGE_TYPE)
			count = ((HSolidModel *)m_pView->GetModel())->m_mi->Compute_Geometry_Keys(entity,40000,keys);
	}
	assert(count < 40000);
	
	if (count)
	{
		for (c = 0; c < count; c++)
		{
			HSelectionSet::DeSelect(keys[c], emit_message);	// call base class fcn for each key
		}
	}
}

bool HSPlainSelectionSet::IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys)
{
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true)
	{
		char	type[MVO_BUFFER_SIZE];

		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			key = HC_KShow_Owner_By_Key(key);

		return HSelectionSet::IsSelected(key, num_include_keys, include_keys);
	}
	else
	{
		if (m_SelectLevel == KERN_BODY_TYPE)  // && body segments is true
		{
			long entity = 0;
			int count;

			CModellerInfo* mi = ((HSolidModel *)m_pView->GetModel())->m_mi;
			entity = mi->Compute_Entity_Index(key,m_SelectLevel);

			if (entity > 0)
			{
				count = mi->Compute_Geometry_Keys(entity,1,&key);
				assert(count == 1);
			}
		}
		// call base class function with the computed key
		return HSelectionSet::IsSelected(key);
	}


}

bool HSPlainSelectionSet::IsSelected(HC_KEY key)
{
	if (((HSolidModel *) m_pView->GetModel())->m_bSolidModel != true)
	{
		char	type[MVO_BUFFER_SIZE];
		
		HC_Show_Key_Type(key, type);
		if (!streq(type, "segment"))
			key = HC_KShow_Owner_By_Key(key);
	}
	else
	{
		if (m_SelectLevel == KERN_BODY_TYPE)  // && body segments is true
		{
			long entity = 0;
			int count;
			
			CModellerInfo* mi = ((HSolidModel *)m_pView->GetModel())->m_mi;
			entity = mi->Compute_Entity_Index(key,m_SelectLevel);
			
			if (entity > 0)
			{
				count = mi->Compute_Geometry_Keys(entity,1,&key);
				assert(count == 1);
			}
		}
	}
	
	// call base class function with the computed key
	return HSelectionSet::IsSelected(key);
	
}

void HSPlainSelectionSet::Select(long entity, bool emit_message)
{
	HC_KEY	keys[40000];
	int		count = 0, c;
	
	
	KERN_CLASS_TYPEDEF eclass;
	
	CModellerInfo* mi = ((HSolidModel *)m_pView->GetModel())->m_mi;
	mi->ENTITY_ask_class(entity, eclass);
	
	if (entity > 0)
	{
		vlist_add_last( m_pSolidSelection, (void*)entity);
		
		
		if (eclass == KERN_BODY_TYPE)  // && body segments is true 
			count = mi->Compute_Geometry_Keys(entity,1,keys);
		
		else if (eclass == KERN_FACE_TYPE)
		{
			count = mi->Compute_Geometry_Keys(entity,40000,keys);
			
			if (m_bShowFacesAsLines)
			{
				int numedges;
				long *edges;
				mi->FACE_ask_edges(entity,&numedges, &edges);
				
				for (int edgenum=0;edgenum<numedges;edgenum++)
				{
					int ecount = mi->Compute_Geometry_Keys(edges[edgenum],40000-count,&keys[count]);
					count += ecount;
				}
				
			}
		}
		else if (eclass == KERN_EDGE_TYPE)
			count = mi->Compute_Geometry_Keys(entity,40000,keys);
	}
	
	assert(count < 40000);
	
	if (count)
	{
		for (c = 0; c < count; c++)
		{
			if (keys[c]!=0)
				HSelectionSet::Select(keys[c], "", INVALID_KEY, INVALID_KEY, emit_message);  // call base class fcn for each key
		}
	}	 
	
}


