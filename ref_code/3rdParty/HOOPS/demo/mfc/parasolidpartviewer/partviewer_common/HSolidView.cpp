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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSolidView.cpp,v 1.145 2010-04-26 21:36:57 reuben Exp $
//

// HSolidView.cpp : implementation of the HSolidView class
// 

// standard includes
#include "StdAfx.h"
#include "Resource.h"
#include <assert.h>
#include <math.h>
#include "hc.h"
#include "HSInclude.h"
#include "HSUtility.h"
#include "HEventManager.h"
#include "HBhvBehaviorManager.h"
// HOOPS/MVO includes
#include "HMarkupManager.h"
#include "HSharedKey.h"
#include "HUtilityGeomHandle.h"

#include "HSolidView.h"
#include "HSolidModel.h"
#include "HSSelectionSet.h"
#include "HUtilityLocaleString.h"
#include "CSolidHoopsView.h"

#ifndef HOOPS_ONLY
#include "HSPlainSelectionSet.h"
#endif // HOOPS_ONLY

#ifdef PARASOLID
#include "hp_bridge.h"
#include "HSParasolidSelectionSet.h"
#endif // PARASOLID
#ifdef ACIS
#include "ha_bridge.h"
#include "HSAcisSelectionSet.h"
#endif // ACIS
#ifdef GRANITE
#include "hg_bridge.h"
#include "HSGraniteSelectionSet.h"
#endif // GRANITE
#ifdef HOOPS_ONLY
#include "HMySelectionSet.h"
#endif // HOOPS_ONLY

#include "EditLightsDlg.h"

#ifdef INTEROP
#include "HPMIUtility.h"
#include "InterOpFileIO.h"
#endif // INTEROP

#define MAX_BOOLEAN_TOOLS 1024
 


HSolidView::HSolidView(HBaseModel *model,
    const char * 		alias,	
    const char *		driver_type,
    const char *		instance_name,
    void *		window_handle,
    void *		colormap) : HBaseView(model, alias, driver_type, instance_name, window_handle, colormap)

{
	m_optimize_shells = false;
	m_bhidden_exists = false;
	m_pSweetenKeyList = 0;
	m_bSmoothTransition = true;	
	m_collab_mode = false;
	m_bShowCollisions = false;
	m_ClashList = 0;


#ifdef INTEROP
	m_pmi = new HPMIUtility(this);
#endif // INTEROP
}

HSolidView::~HSolidView()
{
	if (m_pSweetenKeyList)
		delete []m_pSweetenKeyList;
	ClearClashList();
	delete_vlist(m_ClashList);
#ifdef INTEROP
	delete m_pmi;
#endif // INTEROP
}


void HSolidView::InitSelection(HSSelectionSet *ss)
{
	if (m_pSelection)
		delete m_pSelection;
	m_pSelection = ss;
    m_pSelection->Init();

}
 
// app-specific init function
void HSolidView::Init()
{
	// call base's init function first to get the default HOOPS hierarchy for the view
	HBaseView::Init();
 	GetModel()->GetEventManager()->RegisterHandler((HAnimationListener *)this, HAnimationListener::GetType(), HLISTENER_PRIORITY_NORMAL);

	// create our app-specific Selection object and initialize
#ifdef PARASOLID
	m_pSelection = new HSParasolidSelectionSet(this);
#endif // PARASOLID
#ifdef ACIS
	m_pSelection = new HSAcisSelectionSet(this);
#endif // ACIS
#ifdef GRANITE
	m_pSelection = new HSGraniteSelectionSet(this);
#endif // GRANITE
#ifdef HOOPS_ONLY
	m_pSelection = new HMySelectionSet(this);
#endif // HOOPS_ONLY

    m_pSelection->Init();

	m_pMarkupManager = new HMarkupManager(this);

    // app-specific scene Defaults
    HC_Open_Segment_By_Key(m_ViewKey);
		HC_Set_Selectability("everything = off");
	HC_Close_Segment();

	// set up some scene defaults
	HC_Open_Segment_By_Key(m_SceneKey);
	  HC_Set_Rendering_Options("no color interpolation, color index interpolation");
	  HC_Set_Visibility ("lights = (faces = on, edges = off), markers = off, faces=on, edges=off, lines=off, text = on");
	HC_Close_Segment();

    // windowspace (overlay) defaults
    HC_Open_Segment_By_Key(m_WindowspaceKey);
	  HC_Set_Color_By_Index ("geometry", 3);
	  HC_Set_Color_By_Index ("window contrast", 1);
	  HC_Set_Color_By_Index ("windows", 1);
	  HC_Set_Visibility("markers=on");
	  HC_Set_Marker_Symbol("+");
	  HC_Set_Selectability("off");
    HC_Close_Segment();

    SetZoomLimit();

}



void HSolidView::DeleteSelectionList(bool emit_message)
{
	// if there is no solid model, call the base class
	HSolidModel * pModel = (HSolidModel *)GetModel();
	if ( (!pModel->m_bSolidData) || (pModel->m_bPlainSolidModel))
	{
		HBaseView::DeleteSelectionList(emit_message);
		return;
	}

	int				i, numSolidSelections, numHoopsSelections;
	char			type[MVO_BUFFER_SIZE];
	HC_KEY			tmp;
	HSSelectionSet* selection = 0;
#ifdef PARASOLID
	PK_ENTITY_t		current = 0;
#endif // PARASOLID
#ifdef ACIS
	ENTITY*			current = 0;
#endif // ACIS
#ifdef GRANITE
	KObj_ptr		current = 0;
#endif // GRANITE
	// get ptr to selection object
	selection = (HSSelectionSet *)GetSelection();

	numHoopsSelections = selection->GetSize();
	numSolidSelections = selection->GetSolidListSize();

	if (numHoopsSelections == 0)
		return;

	// loop through the list of selected HOOPS primitives, filtering
	// out the ones associated with solid model entities, and deleting
	// the non-solid model primitives directly using Delete_By_Key
	// The primitives associated with solid model entities need to be
	// deleted using the HOOPS/GM deletion functions so that the HOOPS<->GM 
	// mapping tables will remain in sync

	for (i = numHoopsSelections; i > 0; i--)
	{
		HC_KEY key = selection->GetAt(i-1);

		// if it's a HOOPS primitive that is not associated with a solid model entity,
		// deselect and delete it
#ifdef PARASOLID
		if(current = HP_Compute_TagID(key, PK_CLASS_body) <= 0 )
#endif // PARASOLID
#ifdef ACIS
		current = HA_Compute_Entity_Pointer(key, BODY_TYPE);
		if (current == 0)
#endif // ACIS
#ifdef GRANITE
		HG_Compute_Entity_Pointer(key, KERN_BODY_TYPE, current );
		if( !current )
#endif // GRANITE
		{
			selection->DeSelect(key, false); // the message emit business is done at the end
			int size;
			if (size = HUtility::IsChildOf(m_CuttingPlanesKey, key))
			{
				HC_KEY *keylist = new HC_KEY[size];
				HUtility::IsChildOf(m_CuttingPlanesKey, key, keylist);
				key = keylist[size-2];
				delete [] keylist;
			}			
			HC_Delete_By_Key(key);
		}
	}


	HC_Open_Segment_By_Key(m_CuttingPlanesKey);
		HC_Begin_Contents_Search ("...", "cutting planes");
		if (!HC_Find_Contents (type, &tmp)) 
			SetCuttingPlanesExist(false); 
		HC_End_Contents_Search ();
	HC_Close_Segment();

#ifdef CP_Intersect
    m_bUpdateCPGeom = true;
#endif
	

	// loop through the list of selected solid model entities,
	// delete the HOOPS geometry associated with each
	// and then delete the entity
	for (i = numSolidSelections; i > 0; i--)
	{
#ifdef PARASOLID
		current = selection->GetAtSolidEntity(i-1);
		if (current)
		{
			selection->DeSelectEntity(current);
			((HSolidModel*)GetModel())->DeleteParasolidEntity(current);
		}
#endif // PARASOLID

#ifdef ACIS
		current = (ENTITY*)selection->GetAtSolidEntity(i-1);
		if (current)
		{
			selection->DeSelectEntity(current);
			((HSolidModel*)GetModel())->DeleteAcisEntity(current);
		}
#endif // ACIS
#ifdef GRANITE
		current = (KObj*)selection->GetAtSolidEntity(i-1);
		if (current)
		{
			selection->DeSelectEntity(current);
			((HSolidModel*)GetModel())->DeleteGraniteEntity(current);
		}
#endif // GRANITE


	}

	if( emit_message )
		EmitDeleteSelectionListMessage();

	// Reset the HSSelectionSet and HSelectionSet lists since we've deleted all the entities that
	// were in them  (we can't DeSelect the entities because they no longer exist)
	selection->Reset();

    SetGeometryChanged();

	Update();
}



// perform a boolean operation on selected items
void HSolidView::BooleanOperation(unsigned long	operation)
{
	int			number_of_tools = 0;
#ifdef PARASOLID
	PK_BODY_t	target = 0;
	PK_BODY_t	tools[MAX_BOOLEAN_TOOLS];
#endif // PARASOLID
#ifdef ACIS
	BODY*		target = 0;
	BODY*		tools[MAX_BOOLEAN_TOOLS];
	ENTITY_LIST elist;
#endif // ACIS

	int numSelections;
	HSSelectionSet* selection = 0;

	// get ptr to selection object
	selection = (HSSelectionSet *)GetSelection();
	assert(selection);

	// get the number of selected items
	numSelections = selection->GetSolidListSize();
	number_of_tools = numSelections - 1;

	// must have at least 2 selected items for a boolean operation
	if (numSelections < 2)
		return;
#ifdef PARASOLID
	target = (PK_BODY_t)selection->GetAtSolidEntity(0);

	int j;
	for (j = 0; j < number_of_tools && number_of_tools < MAX_BOOLEAN_TOOLS; j++)
	{
		tools[j] = (PK_BODY_t)selection->GetAtSolidEntity(j+1);
	}

	// deselect all the HOOPS primitives and GM entities before deleting
	selection->DeSelectAll();

	// now blow away ALL of the geometry associated with target
	HP_Delete_Entity_Geometry(1, &target);
	HP_Delete_Entity_Geometry(number_of_tools, tools);
#endif // PARASOLID
#ifdef ACIS
	target = (BODY*)selection->GetAtSolidEntity(0);

	int j;
	for (j = 0; j < number_of_tools && number_of_tools < MAX_BOOLEAN_TOOLS; j++)
	{
		tools[j] = (BODY*)selection->GetAtSolidEntity(j+1);
		((HSolidModel*)GetModel())->RemoveAcisEntity(tools[j]);  // remove tools from list of entities in the model
	}


	// deselect all the HOOPS primitives and GM entities before deleting
	selection->DeSelectAll();

	// now blow away ALL of the geometry associated with target
	elist.add(target);
	for (j = 0; j < number_of_tools; j++)
	{
		elist.add(tools[j]);
	}
	HA_Delete_Entity_Geometry(elist);
#endif

		


    // Perform the boolean operation and render the resulting entities
	// Put each entity in a separate segment so that we can easily apply
	// transformations to separately created entities.
	// However, before rendering bodies, check if this view is in 'merge faces' mode or not, and
	// ensure tha the rendering option is set accordingly.  This is necessary because the
	// HOOPS/GM Rendering Options are procedural; they set the current state of the bridge,
	// and we need to make sure that all parts in each model object are rendered in a 
	// consistent mode
	HC_Open_Segment_By_Key(GetModelKey());
		HC_Open_Segment("");
#ifdef ACIS
		ha_rendering_options &roptions=HA_Get_Rendering_Options();
			if (m_optimize_shells)
				roptions.SetMergeFacesMode(TRUE);
			else
				roptions.SetMergeFacesMode(FALSE);


			acis_boolean(operation, target, number_of_tools, tools);
#endif // ACIS
#ifdef PARASOLID

			if (m_optimize_shells)
				HP_Set_Rendering_Options("merge faces");
			else
				HP_Set_Rendering_Options("no merge faces");

			parasolid_boolean(operation, target, number_of_tools, tools);
#endif // PARASOLID
		HC_Close_Segment();
	HC_Close_Segment();

#ifdef CP_Intersect
	m_bUpdateCPGeom = true;
#endif

    Update();	
}



void HSolidView::RegenerateBodies(void)
{
#ifdef PARASOLID
	PK_BODY_t body;
#endif // PARASOLID
#ifdef ACIS
	ENTITY* entity;
#endif // ACIS
	HC_KEY	child;
	char seg_type[MVO_BUFFER_SIZE];

 

	HC_Begin_Contents_Search (".", "segment, include");
	while (HC_Find_Contents (seg_type, &child) )
	{

		if (strcmp(seg_type,"include")==0)
		{
 			HC_KEY ikey = HC_KShow_Include_Segment(child);
			HC_Open_Segment_By_Key(ikey);
				RegenerateBodies();
			HC_Close_Segment();
		}
		else
		{

#ifdef PARASOLID
		HC_KEY body_key;
		body = HP_Compute_TagID(child, PK_CLASS_body);
		if (body > 0)
		{
			// We might be in collabration, so let the peers know we are deleting
			// something. Better way to do this will be to write a wrapper over
			// HA_Delete_xxx
			HP_Compute_Geometry_Keys(body, 1, &body_key, "bodies");
			HP_Delete_Entity_Geometry(1, &body);

			HP_Render_Entity (body);
			// We have inserted a new geometry (via HA_Render call). Let our 
			// collabrative peers know about that. 
			HP_Compute_Geometry_Keys(body, 1, &body_key, "bodies");
			continue;
		}
#endif // PARASOLID
#ifdef ACIS
		HC_KEY body_key;
		entity = HA_Compute_Entity_Pointer(child, BODY_TYPE);
		if (entity)
		{
			ENTITY_LIST elist;

			elist.add(entity);

			// We might be in collabration, so let the peers know we are deleting
			// something. Better way to do this will be to write a wrapper over
			// HA_Delete_xxx
	 		HA_Compute_Geometry_Keys(entity, 1, &body_key, "bodies");		
			HA_Delete_Entity_Geometry(elist);

			HA_Render_Entity (entity);
			// We have inserted a new geometry (via HA_Render call). Let our 
			// collabrative peers know about that. 
			HA_Compute_Geometry_Keys(entity, 1, &body_key, "bodies");
			continue;
		}
#endif // ACIS

#ifdef GRANITE
		KObj_ptr body_obj;
		HG_Compute_Entity_Pointer(child, KERN_BODY_TYPE, body_obj);
		KBody_ptr body = KBody::cast(body_obj);
		if (body)
		{
			HC_KEY body_key;
			// We might be in collabration, so let the peers know we are deleting
			// something. Better way to do this will be to write a wrapper over
			// HA_Delete_xxx
			HG_Compute_Geometry_Keys(KObj::cast(body), 1, &body_key, "bodies");
			HG_Delete_Entity_Geometry(KObj::cast(body));

			HG_Render_Entity (KObj::cast(body));
			// We have inserted a new geometry (via HA_Render call). Let our 
			// collabrative peers know about that. 
			HG_Compute_Geometry_Keys(KObj::cast(body), 1, &body_key, "bodies");
			continue;
		}
#endif // GRANITE

		HC_Open_Segment_By_Key(child);
			RegenerateBodies();
		HC_Close_Segment();
		}
	}
	HC_End_Contents_Search();
	
}

#ifndef HOOPS_ONLY
void HSolidView::SetOptimizations(bool optimize, bool no_update)
{
	if (no_update)
	{
		m_optimize_shells = optimize;
		return;
	}
		
	if (optimize != m_optimize_shells &&  GetRenderMode()!=HRenderHiddenLine)		
	{
		m_optimize_shells = optimize;

		// if optimize is true, set 'merge faces' mode so that all faces in a body will
		// be merged into a single HOOPS shell primitive; also set the select level to body
		// level if it was previously face-level, since we can no longer select on 
		// individiual faces
		KERN_CLASS_TYPEDEF class_type;

#ifdef PARASOLID
		HP_Set_Hash_Level(0);

//		PK_CLASS_t class_type;

		if (optimize)
		{
			HP_Set_Rendering_Options("merge faces");

			class_type = ((HSSelectionSet *)GetSelection())->GetSelectLevel();
			if (class_type == PK_CLASS_face)
				((HSSelectionSet *)GetSelection())->SetSelectLevel(PK_CLASS_body);
		}
		else
			HP_Set_Rendering_Options("no merge faces");
#endif // PARASOLID

#ifdef ACIS
//		int class_type;

		ha_rendering_options &roptions=HA_Get_Rendering_Options();
		if (optimize)
		{
			roptions.SetMergeFacesMode(TRUE);

			class_type = ((HSSelectionSet *)GetSelection())->GetSelectLevel();
			if (class_type == FACE_TYPE)
				((HSSelectionSet *)GetSelection())->SetSelectLevel(BODY_TYPE);
		}
		else
			roptions.SetMergeFacesMode(FALSE);
#endif // ACIS

#ifdef GRANITE
		if (optimize)
		{
			HG_Set_Rendering_Options("merge faces");

			class_type = ((HSSelectionSet *)GetSelection())->GetSelectLevel();
			if (class_type == KERN_FACE_TYPE)
				((HSSelectionSet *)GetSelection())->SetSelectLevel(KERN_BODY_TYPE);
		}
		else
			HG_Set_Rendering_Options("no merge faces");
#endif // GRANITE


		// deselect all geometry prior to regenerating the model
		GetSelection()->DeSelectAll();
	 
		HC_Open_Segment_By_Key(GetModelKey());
			RegenerateBodies();
		HC_Close_Segment();	

		// we might be in collab, ask the peers to flush all the geometries
		// of model key and retransmit them the same
		if( m_pSharedKey )
		{
			m_pSharedKey->Reset();
			EmitFlushMessage();
			EmitSegment(GetModelKey(), true);
		}

	}

}

#endif // HOOPS_ONLY



bool HSolidView::GetOptimizations(void)
{
	return m_optimize_shells;
}


  
void HSolidView::EnableHiddenLine()
{
#ifdef ACIS
	OutputDebugString(_T("Precise Hidden Line not yet implemented in ACIS Part Viewer"));
	return;
#endif

	// do not do any precise hidden line fancy if we are in a collabrative session
	if( m_collab_mode )
		return;

	// do not use precise hidden line rendering if we do not have a solid model - Rajesh B
	HSolidModel * pModel = (HSolidModel *)GetModel();
	assert(pModel);
	if ( (!pModel->m_bSolidData) || (pModel->m_bPlainSolidModel))
		return;

	m_ProjTmp=GetProjMode();
	SetProjMode(ProjOrthographic);

	HC_Open_Segment_By_Key(pModel->GetModelKey());	
		HC_Set_Visibility("everything = off");
		HC_Set_Selectability("faces = on!");
	HC_Close_Segment();
 
 	float px,py,pz,tx,ty,tz; 
 	HC_Open_Segment_By_Key(GetSceneKey());		
		HC_Show_Net_Camera_Position(&px, &py, &pz);
 		HC_Show_Net_Camera_Target(&tx, &ty, &tz);
 	HC_Close_Segment();

	char visibility[MVO_BUFFER_SIZE];
	HC_Open_Segment_By_Key(GetSceneKey());
	HC_Show_Net_Visibility(visibility);
	HC_Close_Segment();

	if (px==m_pos.x && py==m_pos.y && pz==m_pos.z && 
		tx==m_tar.x && ty==m_tar.y && tz==m_tar.z && m_bhidden_exists)
	{
		HC_Open_Segment_By_Key(pModel->GetModelKey());
			HC_Open_Segment("main");
				HC_Set_Visibility(visibility);
			HC_Close_Segment();
		HC_Close_Segment();
#ifdef PARASOLID
			HP_Set_Hash_Level(1);
#endif // PARASOLID

			((HSSelectionSet *)GetSelection())->RefreshSolidSelection(); 	
			
#ifdef PARASOLID
			HP_Set_Hash_Level(0);
#endif // PARASOLID
	}
	else 
	{	  			 
 		UpdateHiddenLine();  	
 	}

  	m_bhidden_exists=false;
}

void HSolidView::DisableHiddenLine()
{
#ifdef ACIS
	OutputDebugString(_T("Precise Hidden Line not yet implemented in ACIS Part Viewer"));
	return;
#endif

	// do not do any precise hidden line fancy if we are in a collabrative session
	if( m_collab_mode )
		return;

	HSolidModel * pModel = (HSolidModel *)GetModel();
	assert(pModel);


	// do not use precise hidden line rendering if we do not have a solid model - Rajesh B
	if ( (!pModel->m_bSolidData) || (pModel->m_bPlainSolidModel))
		return;


 	int size = 0;

	//we need to rerender all the bodies in the current partition
#ifdef PARASOLID
  	PK_BODY_t * body; 
	PK_PARTITION_ask_bodies(pModel->GetPartition(), &size,&body);
#endif // PARASOLID
#ifdef ACIS
  	ENTITY_LIST body; 
	body = pModel->GetEntityList();
	size = body.iteration_count();
#endif // ACIS

	if (size == 0)
		return;

 	SetProjMode(m_ProjTmp);
	
	HC_Open_Segment_By_Key(pModel->GetModelKey());
		HC_Open_Segment("main");
			HC_Set_Visibility("everything = off");
		HC_Close_Segment();
		HC_UnSet_Visibility();
		HC_UnSet_Selectability();
	HC_Close_Segment();

	((HSSelectionSet *)GetSelection())->RefreshSolidSelection(); 	
	m_bhidden_exists=true;
#ifdef PARASOLID
	PK_MEMORY_free(body);
#endif // PARASOLID
}

#ifdef PARASOLID
void  HSolidView::UpdateHiddenLine() 
{
	// do not do any precise hidden line fancy if we are in a collabrative session
	if( m_collab_mode )
		return;
 
	// do not use precise hidden line rendering if we do not have a solid model - Rajesh B
	HSolidModel * pModel = (HSolidModel *)GetModel();
	assert(pModel);
	if ( (!pModel->m_bSolidData) || (pModel->m_bPlainSolidModel))
		return;

 	int size = 0;
  	PK_BODY_t * body;
	char proj[MVO_BUFFER_SIZE];
	int numbodies = 0;

	//we need to rerender all the bodies in the current partition
 	int numassemblies;
	int totalbodies = 0;
	PK_ASSEMBLY_t * assemblies;
	PK_PARTITION_ask_assemblies(pModel->GetPartition(), &numassemblies,&assemblies);
	PK_ASSEMBLY_t *lassemblies = 0;
	if( numassemblies > 0 )
		lassemblies = new PK_ASSEMBLY_t[numassemblies];

	int numlassemblies = 0;
	int i;
 	for (i=0;i<numassemblies;i++)
	{
		int numref;
		PK_PART_ask_ref_instances(assemblies[i],&numref,0);
		if (!numref)
		{
			PK_ASSEMBLY_make_level_assembly(assemblies[i],&lassemblies[numlassemblies]);
			int numinstances;
 			PK_ASSEMBLY_ask_instances(lassemblies[numlassemblies],&numinstances,0);
			numlassemblies++;
			totalbodies+=numinstances;
		}
	}

	PK_MEMORY_free(assemblies);

	PK_PARTITION_ask_bodies(pModel->GetPartition(), &size,&body);
	PK_BODY_t *bodies = new PK_BODY_t[totalbodies+size];
	PK_BODY_t *bodytransforms = new PK_TRANSF_t[totalbodies+size];

	for (i=0;i<size;i++)
	{
		int numref;
		PK_PART_ask_ref_instances(body[i],&numref,0);
		if (!numref)
		{
			bodies[numbodies] = body[i];
			bodytransforms[numbodies++] = NULTAG;
		}
	}
	PK_MEMORY_free(body);


	for (i=0;i<numlassemblies;i++)
	{
 		PK_INSTANCE_t *instances;
		int numinstances;
		PK_ASSEMBLY_ask_instances(lassemblies[i],&numinstances,&instances);
		for (int j=0;j<numinstances;j++)
		{
			PK_INSTANCE_sf_t in_sf;
			PK_INSTANCE_ask(instances[j],&in_sf);
			bodies[numbodies]= in_sf.part;
			bodytransforms[numbodies++] = in_sf.transf;
		}
		PK_MEMORY_free(instances); 
	}
	
	if (size == 0)
		return;	
 
	HP_Set_Hash_Level(1);

  //this code simply blows up every body the first time the operator is executed.
//to show the different behavior of the hidden line code
/*
	if (first)
	{
		first=false;
	PK_TRANSF_t s_trf;
	PK_VECTOR_t vec;
	vec.coord[0] = 0;
	vec.coord[1] = 0;
	vec.coord[2] = 0;
	PK_TRANSF_create_equal_scale(18,vec,&s_trf);
	int n_rep;
 


	for (int i=0;i<size;i++)
		PK_BODY_transform(body[i],s_trf,0.0001,&n_rep,0,0);
 
	}

*/
  
	//first we need a view vector to calculate the rotational components of the view matrix
 	float px,py,pz,tx,ty,tz; 
 	HC_Open_Segment_By_Key(GetSceneKey());		
		HC_Show_Net_Camera_Position(&px, &py, &pz);
 		HC_Show_Net_Camera_Target(&tx, &ty, &tz);
		HC_Show_Net_Camera_Projection(proj);
	HC_Close_Segment();
	m_pos.Set(px,py,pz);
	m_tar.Set(tx,ty,tz);  	 
		
	HP_Delete_Entity_Geometry(numbodies,bodies);
	
 	PK_VECTOR1_t v;
	//we cannot use the internal HOOPS function to normalize the vector as double precision 
	//is required. We also need the vectorlength later 
 	v.coord[0]=tx-px;
	v.coord[1]=ty-py;
	v.coord[2]=tz-pz;
	
	double w = sqrt(v.coord[0] * v.coord[0] + v.coord[1] * v.coord[1] + 
		v.coord[2]*v.coord[2]);

	v.coord[0] /= w;
	v.coord[1] /= w;
	v.coord[2] /= w;
	
	
	//this PS helper function creates a suitable rotational matrix from a given vector
	PK_TRANSF_t rot_trf;
	PK_VECTOR_make_view_transf(v,&rot_trf);
	PK_TRANSF_sf_t		rot_m; 

	PK_TRANSF_ask(rot_trf,&rot_m);	
	
  	
	//in the orthogonal case only the rotational components are needed as there is no forshortening.
	if (strcmp("perspective",proj)==0)
	{
		//this calculates the perspective components of the view matrix.
		rot_m.matrix[3][0] = -w * rot_m.matrix[2][0];
		rot_m.matrix[3][1] = -w * rot_m.matrix[2][1];
		rot_m.matrix[3][2] = -w * rot_m.matrix[2][2];

		//this calculates the translational components		
		rot_m.matrix[0][3] = -(px * rot_m.matrix[0][0] + py * rot_m.matrix[0][1] + pz * rot_m.matrix[0][2]);
		rot_m.matrix[1][3] = -(px * rot_m.matrix[1][0] + py * rot_m.matrix[1][1] + pz * rot_m.matrix[1][2]);
		rot_m.matrix[2][3] = -(px * rot_m.matrix[2][0] + py * rot_m.matrix[2][1] + pz * rot_m.matrix[2][2]);
		
		//this calculates the scaling component
		rot_m.matrix[3][3]=1.0 + w * (px * rot_m.matrix[2][0] + py * rot_m.matrix[2][1] + pz * rot_m.matrix[2][2]); 
	}


	//create the PS transform from the supplied matrix
   	PK_TRANSF_t view_transf;			
 	PK_TRANSF_create(&rot_m,&view_transf);	
														 
	//temporarily set tesselation options
	//for silhouette+hidden line output
	PK_TOPOL_render_line_o_t g_lineOptions,g_lineOptionsSav;	
				
 	HP_Show_Tessellation_Options(&g_lineOptions, NULL, NULL);	
 	HP_Show_Tessellation_Options(&g_lineOptionsSav, NULL, NULL);	
  	g_lineOptions.edge = PK_render_edge_yes_c;
 	g_lineOptions.silhouette = PK_render_silhouette_yes_c;
	g_lineOptions.visibility = PK_render_vis_hid_c;
	HP_Set_Tessellation_Options(&g_lineOptions, NULL,NULL);


	char visibility[MVO_BUFFER_SIZE];
	HC_Open_Segment_By_Key(GetSceneKey());
	HC_Show_Net_Visibility(visibility);
	HC_Close_Segment();
	//rerender the bodies with the supplied view transformation
	HC_Open_Segment_By_Key(pModel->GetModelKey());	
 		HC_Open_Segment("main");
			HC_Flush_Contents(".", "everything");
			HC_Set_Visibility(visibility);
			PK_PARTITION_set_current(pModel->GetPartition());
 			HP_Render_Entities(numbodies, bodies, view_transf,bodytransforms);
 		HC_Close_Segment();
	HC_Close_Segment();
	
	//restore old tessellation settings
 	HP_Set_Tessellation_Options(&g_lineOptionsSav, NULL, NULL);
 	((HSSelectionSet *)GetSelection())->RefreshSolidSelection();

	HP_Set_Hash_Level(0);
 	 
 	delete bodies;
	delete bodytransforms;
 	PK_ENTITY_delete(numlassemblies,lassemblies);
	if( lassemblies )
		delete lassemblies;
}
#endif // PARASOLID


#ifdef ACIS

void  HSolidView::UpdateHiddenLine() 
{
	// TODO: precise hidden line implementation
	return;
}
#endif // ACIS

#ifdef GRANITE
void  HSolidView::UpdateHiddenLine() 
{
	//assert(0);	// TODO_IMPLEMENT
}
#endif // GRANITE

#ifdef HOOPS_ONLY
void  HSolidView::UpdateHiddenLine() 
{
	// No precise hidden line in HOOPS_ONLY;
	return;
}
#endif // HOOPS_ONLY



// reset the camera to view the a specific target plane
// choices are XY, XZ, and YZ planes
void HSolidView::SetViewMode (ViewMode mode)
{
	HPoint target, camera, view, light;
	HPoint to,co,uo;
	HPoint tn,cn,un;
	float widtho, heighto, widthn, heightn;
	char projection[MVO_BUFFER_SIZE];

	PrepareForCameraChange();

	HC_Open_Segment_By_Key(GetSceneKey());
	    HC_Show_Net_Camera (&co, &to, &uo, &widtho, &heighto, projection);
	HC_Close_Segment();	

	m_ViewMode = mode;

	if(mode == HViewUnknown) return;
	
	HPoint center;
	HBaseView::FitWorld(&center);

	HC_Open_Segment_By_Key(GetSceneKey());
	
	HC_Show_Net_Camera_Target (&target.x, &target.y, &target.z);
	HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);

	view.Set(	camera.x - target.x,
				camera.y - target.y,
				camera.z - target.z);


	float length;
	length = (float) HC_Compute_Vector_Length( &view);

	switch(mode){
	  
	case HViewXY:
		
		camera.Set(center.x, center.y, center.z-length);
  		HC_Set_Camera_Position(camera.x, camera.y, camera.z);
	
		HC_Set_Camera_Up_Vector(0.0, 1.0, 0.0);
		
		break;
	case HViewYX:
		
		camera.Set(center.x, center.y, center.z+length);
		HC_Set_Camera_Position(camera.x, camera.y, camera.z);
	
		HC_Set_Camera_Up_Vector(0.0, 1.0, 0.0);
		
		break;
	case HViewXZ:

		camera.Set(center.x, center.y+length, center.z);
		HC_Set_Camera_Position(camera.x, camera.y, camera.z);
		
		HC_Set_Camera_Up_Vector(0.0, 0.0, 1.0);
			 
		break;
	case HViewZX:

		camera.Set(center.x, center.y-length, center.z);
		HC_Set_Camera_Position(camera.x, camera.y, camera.z);
		
		HC_Set_Camera_Up_Vector(0.0, 0.0, 1.0);
			 
		break;
	case HViewYZ:

		camera.Set(center.x+length, center.y, center.z);
		HC_Set_Camera_Position(camera.x, camera.y, camera.z);	
		
		HC_Set_Camera_Up_Vector(0.0, 1.0, 0.0);
	
		break;
	case HViewZY:

		camera.Set(center.x-length, center.y, center.z);
		HC_Set_Camera_Position(camera.x, camera.y, camera.z);	
		
		HC_Set_Camera_Up_Vector(0.0, 1.0, 0.0);
	
		break;
	case HViewIso:
		{
			float newLen = length * 0.5774f;

			camera.Set(target.x + newLen, target.y - newLen, target.z + newLen);

			HC_Set_Camera_Position(camera.x, camera.y, camera.z); 
			HC_Set_Camera_Up_Vector(0.0, 1.0, 0.0);
		}
		break;


	default: break;
	}

	HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
 	
 	if (GetRenderMode()==HRenderHiddenLine)		
		UpdateHiddenLine(); 
	
	HC_Show_Net_Camera (&cn, &tn, &un, &widthn, &heightn, projection);

	HPoint p1,p2;
	p1.Set(cn.x-tn.x,cn.y-tn.y,cn.z-tn.z);
	p2.Set(co.x-to.x,co.y-to.y,co.z-to.z);
 	float mat[4][4];
	HUtility::ComputeVectorToVectorRotationMatrix((float *)mat,p1,p2);
  	HPoint un2;
	un2.Set(un.x,un.y,un.z);
	HC_Compute_Transformed_Points(1,&uo,(float *)mat,&un2);
   	
 	if (un2.x>0.8)
		un.Set(1,0,0);
	else if (un2.y>0.8)
		un.Set(0,1,0);
 	else if (un2.z>0.8)
		un.Set(0,0,1);
 	else if (un2.x<-0.8)
		un.Set(-1,0,0);
 	else if (un2.y<-0.8)
		un.Set(0,-1,0);
 	else if (un2.z<-0.8)
		un.Set(0,0,-1);
  		
   	HC_Set_Camera_Up_Vector(un.x, un.y, un.z);
 
	if( GetSmoothTransition() )
	{
		HUtility::SmoothTransition(co, to, uo, widtho, heighto, cn, tn, un, widthn, heightn, this);
		CameraPositionChanged(true, GetSmoothTransition());
		Update();
	}
	else
	{	
	    CameraPositionChanged(true, GetSmoothTransition());
	    Update();
	}
  
	HC_Close_Segment();

} 
 
#ifdef PARASOLID
bool HSolidView::FindBox(PK_ENTITY_t entity,PK_BOX_t *box)
{
	bool success = true;
	PK_CLASS_t eclass;
	PK_BODY_t part = PK_ENTITY_null;
	PK_ENTITY_ask_class(entity,&eclass);
	if (eclass == PK_CLASS_face)
		PK_FACE_ask_body(entity,&part);
	else if (eclass == PK_CLASS_edge)
		PK_EDGE_ask_body(entity,&part);
	else if (eclass == PK_CLASS_assembly)
		part = entity;
	else if (eclass == PK_CLASS_body)
		part = entity;
	else if (eclass == PK_CLASS_instance)
	{
		PK_INSTANCE_sf_t in_sf;
		PK_INSTANCE_ask(entity,&in_sf);
		part = in_sf.part;
		entity = part;
	}
 
 	
	PK_TOPOL_find_box(entity,box);

	int ninstances;
	PK_INSTANCE_t * instances;
	if (part != PK_ENTITY_null) {
		PK_PART_ask_ref_instances(part,&ninstances,&instances);
		if (ninstances==0)
 			return success;
 		else if (ninstances == 1)
		{
			PK_INSTANCE_sf_t in_sf;
			PK_INSTANCE_ask(instances[0],&in_sf);
			int ninstances;
			PK_PART_ask_ref_instances(in_sf.assembly,&ninstances,0);
			if (ninstances==0)
			{
 				TransposePoint((PK_VECTOR_t *)box,in_sf.transf,false);
				TransposePoint((PK_VECTOR_t *)&box->coord[3],in_sf.transf,false);
			}

		}
		else
			success = false;
		PK_MEMORY_free(instances);
	}
	return success;
}

#endif // PARASOLID

void Compute_Shell_Normal(HC_KEY skey, HPoint &tnormal)
{
	// if the key doesn't exist, normal doesn't either
	if (!HC_Show_Existence_By_Key(skey, "self"))
	{
		tnormal.Set(0,0,0);
		return;
	}

	char ktype[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(skey,ktype);
	if (strcmp(ktype,"shell")!=0)
	{
		tnormal.Set(0,0,0);
		return;
	}
	
	
	int pcount,flen;
	HC_Show_Shell_Size(skey,&pcount,&flen);
	HPoint *points = new HPoint[pcount];
	int *flist = new int[flen];

	HC_Show_Shell(skey, &pcount, points, &flen, flist);	
	int flist_pos=0;
	unsigned short numfaces=0;
 	tnormal.Set(0,0,0);
 	while (flist_pos < flen)
	{
		HPoint fpoints[1000];
		int fpcount = flist[flist_pos++];

		for (int i=0;i<fpcount;i++)
		{
			fpoints[i].Set(points[flist[flist_pos]].x,points[flist[flist_pos]].y,points[flist[flist_pos]].z);
			flist_pos++;
		}
		HPoint normal;
 		HC_Compute_Polygon_Normal(fpcount,fpoints,"right",&normal);
		tnormal.x=tnormal.x+normal.x;
		tnormal.y=tnormal.y+normal.y;
		tnormal.z=tnormal.z+normal.z;
		numfaces++;
	}
	tnormal.x/=numfaces;
	tnormal.y/=numfaces;
	tnormal.z/=numfaces;
	
	if (fabs(tnormal.x)+fabs(tnormal.y)+fabs(tnormal.z)<0.1)
		tnormal.x = tnormal.y=tnormal.z = 0;
	else
 		HC_Compute_Normalized_Vector(&tnormal,&tnormal);

	if( flist )
		delete[] flist;
	if( points )
		delete[] points;
}
 

void HSolidView::FitWorldToHOOPSSelection()
{
	FitSelection();
}

 
#ifdef HOOPS_ONLY
// reset the camera to optimally view the current selection
void HSolidView::FitWorldToSelection()
{
	// TODO_IMPLEMENT
	assert(0);
}
#endif // HOOPS_ONLY


  
#ifdef PARASOLID
// reset the camera to optimally view the current selection
void HSolidView::FitWorldToSelection()
{
	HPoint min,max;
	HPoint center;
	HPoint camera;
	HPoint target;
	HPoint viewingVector;
	HPoint diagonalVector;
	float diagonalLength;
	float tmp;

	HSSelectionSet* selection = (HSSelectionSet*) (GetSelection());
	int solid_size = selection->GetSolidListSize();

	if (!solid_size)
		return;
	PK_ENTITY_t entity = selection->GetAtSolidEntity(0);

	
	PK_BOX_t box;
	if (!FindBox(entity,&box))
		return;
//	PK_TOPOL_find_box(entity,&box);
	min.x = (float)box.coord[0];
	min.y = (float)box.coord[1];
	min.z = (float)box.coord[2];
	max.x = (float)box.coord[3];
	max.y = (float)box.coord[4];
	max.z = (float)box.coord[5];
	if (min.x > max.x) {
		tmp = min.x; min.x = max.x; max.x = tmp; }
	if (min.y > max.y) {
		tmp = min.y; min.y = max.y; max.y = tmp; }
	if (min.z > max.z) {
		tmp = min.z; min.z = max.z; max.z = tmp; }

	PK_CLASS_t eclass;
	HPoint normal;

	PK_ENTITY_ask_class(entity,&eclass);
	if (eclass == PK_CLASS_face)
	{
		PK_VERTEX_t *vertices;
		normal.Set(0,0,0);
		int nvertices;
		PK_FACE_ask_vertices(entity,&nvertices,&vertices);
		if (nvertices>2)
		{
			HPoint *p = new HPoint[nvertices];
			for (int j=0;j<nvertices;j++)
			{
				PK_POINT_t point;
				PK_VERTEX_ask_point(vertices[j],&point);
				PK_POINT_sf_t ps;
				PK_POINT_ask(point,&ps);
				p[j].Set((float)ps.position.coord[0],(float)ps.position.coord[1],(float)ps.position.coord[2]);
			}
			
			HC_Compute_Polygon_Normal(nvertices,p,"right",&normal);
			PK_MEMORY_free(vertices);
			delete p;
		}
		else
		{
			
			HC_KEY shell = selection->GetAt(0);
	 		Compute_Shell_Normal(shell,normal);
		}
	}
	
	
	
	for (int i=1;i<solid_size;i++)
	{	
		double tmp;
		PK_ENTITY_t entity = selection->GetAtSolidEntity(i);
		
		PK_BOX_t box;
		if (!FindBox(entity,&box))
			return;
		
		//order the points
		if (box.coord[0] > box.coord[3]) {
			tmp = box.coord[0]; box.coord[0] = box.coord[3]; box.coord[3] = tmp;
		}
		if (box.coord[1] > box.coord[4]) {
			tmp = box.coord[1]; box.coord[1] = box.coord[4]; box.coord[4] = tmp;
		}
		if (box.coord[2] > box.coord[5]) {
			tmp = box.coord[2]; box.coord[2] = box.coord[5]; box.coord[5] = tmp;
		}
		box.coord[0] < min.x ? min.x = (float)box.coord[0] : 0;
		box.coord[1] < min.y ? min.y = (float)box.coord[1] : 0;
		box.coord[2] < min.z ? min.z = (float)box.coord[2] : 0;
		box.coord[3] > max.x ? max.x = (float)box.coord[3] : 0;
		box.coord[4] > max.y ? max.y = (float)box.coord[4] : 0;
		box.coord[5] > max.z ? max.z = (float)box.coord[5] : 0;
	}
	
	
	HC_Open_Segment_By_Key (m_SceneKey);
	
	// compute the length of the bbox diagonal vector
	// this will be used to make the camera field a bit larger
	// to ensure that objects between the camera position and target
	// will still not get clipped (this is for perspective viewing mode)

	HPoint co,to,uo,cn,tn,un;
	float wo, ho, wn, hn;
	char proj[MVO_BUFFER_SIZE];

	HC_Show_Net_Camera(&co, &to, &uo, &wo, &ho, proj);

	diagonalVector.Set(
		max.x - min.x,
		max.y - min.y,
		max.z - min.z);

	diagonalLength = (float) sqrt(
		diagonalVector.x * diagonalVector.x +
		diagonalVector.y * diagonalVector.y +
		diagonalVector.z * diagonalVector.z);

	center.x = 0.5F * (min.x + max.x);
	center.y = 0.5F * (min.y + max.y);
	center.z = 0.5F * (min.z + max.z);

	HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
	HC_Show_Net_Camera_Target (&target.x, &target.y, &target.z);
  
	viewingVector.Set(
		target.x - camera.x,
		target.y - camera.y,
		target.z - camera.z);

	HC_Compute_Normalized_Vector (&viewingVector, &viewingVector);

	// reset camera position to lie on the viewing vector, at a distance of
	// 2.5 * diagonal length away from the center of the selection centroid
	HC_Set_Camera_Position(center.x - 2.5f * viewingVector.x * diagonalLength,
						   center.y - 2.5f * viewingVector.y * diagonalLength,
						   center.z - 2.5f * viewingVector.z * diagonalLength);

	// set the camera target to be the centroid of the selection
	HC_Set_Camera_Target (center.x, center.y, center.z);

	// set the camera field to be the diagonal length of the selections's bounding box
	HC_Set_Camera_Field (diagonalLength, diagonalLength);
	

	HC_Show_Net_Camera(&cn, &tn, &un, &wn, &hn, proj);

	if (eclass == PK_CLASS_face && !(normal.x==0 && normal.y==0 && normal.z==0))
	{
		HPoint temp1;
		temp1.Set(cn.x-tn.x,cn.y-tn.y,cn.z-tn.z);
		float length = (float)HC_Compute_Vector_Length(&temp1);
		cn.x=tn.x+normal.x*length;
		cn.y=tn.y+normal.y*length;
		cn.z=tn.z+normal.z*length;
		HC_Set_Camera_Position(cn.x,cn.y,cn.z);
		HPoint p1,p2;
		p1.Set(cn.x-tn.x,cn.y-tn.y,cn.z-tn.z);
		p2.Set(co.x-to.x,co.y-to.y,co.z-to.z);
		float mat[4][4];
		HUtility::ComputeVectorToVectorRotationMatrix((float *)mat,p1,p2);
		HPoint un2;
		un2.Set(un.x,un.y,un.z);
		HC_Compute_Transformed_Points(1,&uo,(float *)mat,&un);
		
		HC_Set_Camera_Up_Vector(un.x,un.y,un.z);
	}

	if( GetSmoothTransition() )
		HUtility::SmoothTransition(co,to,uo, wo, ho, cn,tn, un, wn, hn, this);

	HC_Close_Segment();

	CameraPositionChanged( true, GetSmoothTransition() );
}
#endif // PARASOLID

#ifdef ACIS
// reset the camera to optimally view the current selection
void HSolidView::FitWorldToSelection()
{
	HPoint min,max;
	HPoint center;
	HPoint camera;
	HPoint target;
	HPoint viewingVector;
	HPoint diagonalVector;
	float diagonalLength;
	float tmp;

	HSSelectionSet* selection = (HSSelectionSet*) (GetSelection());
	int solid_size = selection->GetSolidListSize();

	if (!solid_size)
		return;
	ENTITY* entity = (ENTITY*) selection->GetAtSolidEntity(0);
	int eclass;
	eclass = entity->identity();
	if (eclass == VERTEX_TYPE)
	{
		return;
	}
	
	SPAposition min_pt;
	SPAposition max_pt;
	ENTITY_LIST elist;
	elist.add( entity );
	outcome o = api_get_entity_box( elist, NULL, min_pt, max_pt );
	CHECK_OUTCOME(o);

	min.x = (float)min_pt.x();
	min.y = (float)min_pt.y();
	min.z = (float)min_pt.z();
	max.x = (float)max_pt.x();
	max.y = (float)max_pt.y();
	max.z = (float)max_pt.z();
	if (min.x > max.x) {
		tmp = min.x; min.x = max.x; max.x = tmp; }
	if (min.y > max.y) {
		tmp = min.y; min.y = max.y; max.y = tmp; }
	if (min.z > max.z) {
		tmp = min.z; min.z = max.z; max.z = tmp; }

	HPoint normal;

	if (eclass == FACE_TYPE)
	{
		ENTITY_LIST vertices;
		normal.Set(0,0,0);
		int nvertices;
		outcome o = api_get_vertices( entity, vertices );
		nvertices = vertices.iteration_count();
		if (nvertices>2)
		{
			HPoint *p = new HPoint[nvertices];
			for (int j=0;j<nvertices;j++)
			{
				APOINT* point = ((VERTEX*)vertices[j])->geometry();
				SPAposition ps = point->coords();
				p[j].Set((float)ps.x(),(float)ps.y(),(float)ps.z());
			}
			
			HC_Compute_Polygon_Normal(nvertices,p,"right",&normal);
			delete p;
		}
		else
		{
			
			HC_KEY shell = selection->GetAt(0);
	 		Compute_Shell_Normal(shell,normal);
		}
	}
	
	
	
	for (int i=1;i<solid_size;i++)
	{	
		ENTITY* entity = (ENTITY*) selection->GetAtSolidEntity(i);
		
		ENTITY_LIST elist;
		elist.add( entity );
		outcome o = api_get_entity_box( elist, NULL, min_pt, max_pt );
		CHECK_OUTCOME(o);
		
		min_pt.x() < min.x ? min.x = (float)min_pt.x() : 0;
		min_pt.y() < min.y ? min.y = (float)min_pt.y() : 0;
		min_pt.z() < min.z ? min.z = (float)min_pt.z() : 0;
		max_pt.x() > max.x ? max.x = (float)max_pt.x() : 0;
		max_pt.y() > max.y ? max.y = (float)max_pt.y() : 0;
		max_pt.z() > max.z ? max.z = (float)max_pt.z() : 0;
	}
	
	
	HC_Open_Segment_By_Key (m_SceneKey);
	
	// compute the length of the bbox diagonal vector
	// this will be used to make the camera field a bit larger
	// to ensure that objects between the camera position and target
	// will still not get clipped (this is for perspective viewing mode)

	HPoint co,to,uo,cn,tn,un;
	float wo, ho, wn, hn;
	char proj[MVO_BUFFER_SIZE];

	HC_Show_Net_Camera(&co, &to, &uo, &wo, &ho, proj);

	diagonalVector.Set(
		max.x - min.x,
		max.y - min.y,
		max.z - min.z);

	diagonalLength = (float) sqrt(
		diagonalVector.x * diagonalVector.x +
		diagonalVector.y * diagonalVector.y +
		diagonalVector.z * diagonalVector.z);

	center.x = 0.5F * (min.x + max.x);
	center.y = 0.5F * (min.y + max.y);
	center.z = 0.5F * (min.z + max.z);

	HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
	HC_Show_Net_Camera_Target (&target.x, &target.y, &target.z);
  
	viewingVector.Set(
		target.x - camera.x,
		target.y - camera.y,
		target.z - camera.z);

	HC_Compute_Normalized_Vector (&viewingVector, &viewingVector);

	// reset camera position to lie on the viewing vector, at a distance of
	// 2.5 * diagonal length away from the center of the selection centroid
	HC_Set_Camera_Position(center.x - 2.5f * viewingVector.x * diagonalLength,
						   center.y - 2.5f * viewingVector.y * diagonalLength,
						   center.z - 2.5f * viewingVector.z * diagonalLength);

	// set the camera target to be the centroid of the selection
	HC_Set_Camera_Target (center.x, center.y, center.z);

	// set the camera field to be the diagonal length of the selections's bounding box
	HC_Set_Camera_Field (diagonalLength, diagonalLength);

	HC_Show_Net_Camera(&cn, &tn, &un, &wn, &hn, proj);

	if (eclass == FACE_TYPE && !(normal.x==0 && normal.y==0 && normal.z==0))
	{
		HPoint temp1;
		temp1.Set(cn.x-tn.x,cn.y-tn.y,cn.z-tn.z);
		float length = (float)HC_Compute_Vector_Length(&temp1);
		cn.x=tn.x+normal.x*length;
		cn.y=tn.y+normal.y*length;
		cn.z=tn.z+normal.z*length;
		HC_Set_Camera_Position(cn.x,cn.y,cn.z);
		HPoint p1,p2;
		p1.Set(cn.x-tn.x,cn.y-tn.y,cn.z-tn.z);
		p2.Set(co.x-to.x,co.y-to.y,co.z-to.z);
		float mat[4][4];
		HUtility::ComputeVectorToVectorRotationMatrix((float *)mat,p1,p2);
		HPoint un2;
		un2.Set(un.x,un.y,un.z);
		HC_Compute_Transformed_Points(1,&uo,(float *)mat,&un);
		
		HC_Set_Camera_Up_Vector(un.x,un.y,un.z);
	}

	if( GetSmoothTransition() )
		HUtility::SmoothTransition(co,to,uo, wo, ho, cn,tn, un, wn, hn, this);

	HC_Close_Segment();

	CameraPositionChanged( true, GetSmoothTransition());
}
#endif // ACIS

#ifdef GRANITE
void HSolidView::FitWorldToSelection()
{
	HPoint min,max;
	HPoint center;
	HPoint camera;
	HPoint target;
	HPoint viewingVector;
	HPoint diagonalVector;
	float diagonalLength;
	float tmp;

	HSSelectionSet* selection = (HSSelectionSet*) (GetSelection());
	int solid_size = selection->GetSolidListSize();

	if (!solid_size)
		return;
	KERN_ENTITY entity = (KObj*) selection->GetAtSolidEntity(0);
	KERN_CLASS_TYPEDEF eclass = entity->giveRtti();
	if (eclass == KERN_VERTEX_TYPE)
		return;

	KMeasurable_ptr geom = KMeasurable::cast( entity );
	if( !entity )
	{
		assert(0);
		return;
	}

	KBox3D_ptr bbox = geom->GetBox3D();
	min.x = (float)(bbox->GetMinPoint()->get(0));
	min.y = (float)(bbox->GetMinPoint()->get(1));
	min.z = (float)(bbox->GetMinPoint()->get(2));
	max.x = (float)(bbox->GetMaxPoint()->get(0));
	max.y = (float)(bbox->GetMaxPoint()->get(1));
	max.z = (float)(bbox->GetMaxPoint()->get(2));
	if (min.x > max.x) {
		tmp = min.x; min.x = max.x; max.x = tmp; }
	if (min.y > max.y) {
		tmp = min.y; min.y = max.y; max.y = tmp; }
	if (min.z > max.z) {
		tmp = min.z; min.z = max.z; max.z = tmp; }

	HPoint normal;

	if (eclass == KERN_FACE_TYPE)
	{
		/*
		ENTITY_LIST vertices;
		normal.Set(0,0,0);
		int nvertices;
		outcome o = api_get_vertices( entity, vertices );
		nvertices = vertices.count();
		if (nvertices>2)
		{
			HPoint *p = new HPoint[nvertices];
			for (int j=0;j<nvertices;j++)
			{
				APOINT* point = ((VERTEX*)vertices[j])->geometry();
				position ps = point->coords();
				p[j].Set((float)ps.x(),(float)ps.y(),(float)ps.z());
			}
			
			HC_Compute_Polygon_Normal(nvertices,p,"right",&normal);
			delete p;
		}
		else
		*/
		{
			
			HC_KEY shell = selection->GetAt(0);
	 		Compute_Shell_Normal(shell,normal);
		}
	}
	
	
	
	for (int i=1;i<solid_size;i++)
	{	
		KERN_ENTITY entity = (KObj*) selection->GetAtSolidEntity(0);
		KMeasurable_ptr geom = KMeasurable::cast( entity );
		if( !entity )
		{
			assert(0);
			return;
		}

		KBox3D_ptr bbox = geom->GetBox3D();
		KPoint3D_ptr min_pt = bbox->GetMinPoint();
		KPoint3D_ptr max_pt = bbox->GetMaxPoint();
		
		(min_pt->get(0)) < min.x ? min.x = (float)(min_pt->get(0)) : 0;
		(min_pt->get(1)) < min.y ? min.y = (float)(min_pt->get(1)) : 0;
		(min_pt->get(2)) < min.z ? min.z = (float)(min_pt->get(2)) : 0;
		(max_pt->get(0)) > max.x ? max.x = (float)(max_pt->get(0)) : 0;
		(max_pt->get(1)) > max.y ? max.y = (float)(max_pt->get(1)) : 0;
		(max_pt->get(2)) > max.z ? max.z = (float)(max_pt->get(2)) : 0;
	}
	
	
	HC_Open_Segment_By_Key (m_SceneKey);
	
	// compute the length of the bbox diagonal vector
	// this will be used to make the camera field a bit larger
	// to ensure that objects between the camera position and target
	// will still not get clipped (this is for perspective viewing mode)

	HPoint co,to,uo,cn,tn,un;
	float wo, ho, wn, hn;
	char proj[MVO_BUFFER_SIZE];

	HC_Show_Net_Camera(&co, &to, &uo, &wo, &ho, proj);

	diagonalVector.Set(
		max.x - min.x,
		max.y - min.y,
		max.z - min.z);

	diagonalLength = (float) sqrt(
		diagonalVector.x * diagonalVector.x +
		diagonalVector.y * diagonalVector.y +
		diagonalVector.z * diagonalVector.z);

	center.x = 0.5F * (min.x + max.x);
	center.y = 0.5F * (min.y + max.y);
	center.z = 0.5F * (min.z + max.z);

	HC_Show_Net_Camera_Position (&camera.x, &camera.y, &camera.z);
	HC_Show_Net_Camera_Target (&target.x, &target.y, &target.z);
  
	viewingVector.Set(
		target.x - camera.x,
		target.y - camera.y,
		target.z - camera.z);

	HC_Compute_Normalized_Vector (&viewingVector, &viewingVector);

	// reset camera position to lie on the viewing vector, at a distance of
	// 2.5 * diagonal length away from the center of the selection centroid
	HC_Set_Camera_Position(center.x - 2.5f * viewingVector.x * diagonalLength,
						   center.y - 2.5f * viewingVector.y * diagonalLength,
						   center.z - 2.5f * viewingVector.z * diagonalLength);

	// set the camera target to be the centroid of the selection
	HC_Set_Camera_Target (center.x, center.y, center.z);

	// set the camera field to be the diagonal length of the selections's bounding box
	HC_Set_Camera_Field (diagonalLength, diagonalLength);

	HC_Show_Net_Camera(&cn, &tn, &un, &wn, &hn, proj);

	if (eclass == KERN_FACE_TYPE && !(normal.x==0 && normal.y==0 && normal.z==0))
	{
		HPoint temp1;
		temp1.Set(cn.x-tn.x,cn.y-tn.y,cn.z-tn.z);
		float length = (float)HC_Compute_Vector_Length(&temp1);
		cn.x=tn.x+normal.x*length;
		cn.y=tn.y+normal.y*length;
		cn.z=tn.z+normal.z*length;
		HC_Set_Camera_Position(cn.x,cn.y,cn.z);
		HPoint p1,p2;
		p1.Set(cn.x-tn.x,cn.y-tn.y,cn.z-tn.z);
		p2.Set(co.x-to.x,co.y-to.y,co.z-to.z);
		float mat[4][4];
		HUtility::ComputeVectorToVectorRotationMatrix((float *)mat,p1,p2);
		HPoint un2;
		un2.Set(un.x,un.y,un.z);
		HC_Compute_Transformed_Points(1,&uo,(float *)mat,&un);
		
		HC_Set_Camera_Up_Vector(un.x,un.y,un.z);
	}

	HUtility::SmoothTransition(co,to,uo, wo, ho, cn,tn, un, wn, hn, this);
	HC_Close_Segment();

	CameraPositionChanged( true, GetSmoothTransition());
}
#endif // GRANITE

#ifdef PARASOLID
PK_ENTITY_t HSolidView::Compute_Selected_Instance()
{
	char pathname[MVO_BUFFER_SIZE];
	int count;
	PK_ENTITY_t res = PK_ENTITY_null;
	HC_Show_Selection_Pathname(pathname);
//	if (strstr(pathname,"instanced entities"))

	if (strstr(pathname,"instances"))
	{
		HC_Show_Selection_Keys_Count(&count);
		HC_KEY *keys = new HC_KEY[count];
		HC_Show_Selection_Keys(&count, keys);
		for (int i=0;i<count;i++)
		{
			char type[MVO_BUFFER_SIZE];
			HC_Show_Key_Type(keys[i],type);
			if (streq(type,"include"))
			{
 				res = HP_Compute_TagID(keys[i+1], PK_CLASS_instance);
				break;
			}
 
		}
		delete keys;
	}
	return res;
}
#endif // PARASOLID


void HSolidView::SetCamera(int cameranum)
{
	HC_Open_Segment_By_Key (m_SceneKey);
	HC_Show_Net_Camera_Target (&cameras[cameranum].t.x, &cameras[cameranum].t.y, &cameras[cameranum].t.z);
	HC_Show_Net_Camera_Position (&cameras[cameranum].p.x, &cameras[cameranum].p.y, &cameras[cameranum].p.z);
	HC_Show_Net_Camera_Up_Vector (&cameras[cameranum].u.x, &cameras[cameranum].u.y, &cameras[cameranum].u.z);
	HC_Show_Net_Camera_Field(&cameras[cameranum].w,&cameras[cameranum].h);
	HC_Close_Segment();
	cameras[cameranum].active = true;
}
 
void HSolidView::MoveCamera(int cameranum)
{
	if (cameras[cameranum].active)
	{
		HC_Open_Segment_By_Key (m_SceneKey);
		HPoint co,to,uo;
		float wo, ho;
		char proj[MVO_BUFFER_SIZE];

		HC_Show_Net_Camera(&co, &to, &uo, &wo, &ho, proj);
		
		if( GetSmoothTransition() )
		{
			HUtility::SmoothTransition(co,to,uo, wo, ho, cameras[cameranum].p,cameras[cameranum].t,cameras[cameranum].u,cameras[cameranum].w, cameras[cameranum].h, this);
 			CameraPositionChanged(true, true);
		}
		else
		{
 			HC_Set_Camera_Target(cameras[cameranum].t.x,cameras[cameranum].t.y,cameras[cameranum].t.z);
 			HC_Set_Camera_Position(cameras[cameranum].p.x,cameras[cameranum].p.y,cameras[cameranum].p.z);
 			HC_Set_Camera_Up_Vector(cameras[cameranum].u.x,cameras[cameranum].u.y,cameras[cameranum].u.z);
 			CameraPositionChanged(true, false);
			Update();
		}

		HC_Close_Segment();
	}
}
 


void HSolidView::CameraPositionChanged(bool emit_message, bool smooth_camera_transition)
{

	// Let the edit class handle the task of 
	// reposition the lights which follow the camera
	CEditLightsDlg::RepositionLights( this );
	// call the base class
	HBaseView::CameraPositionChanged( emit_message, smooth_camera_transition );

}


//======================================================================
//	Function :HSolidView::FitWorld
//	Description :	Overridden FitWorld. This will always fire CameraPositionChanged
//					with emit_message and smooth_transition set to true. So, this 
//					is now defacto for partviewers
//	Return :	
//	Parameters : HPoint
//	Note :
//======================================================================
void HSolidView::FitWorld(HPoint * center_out)
{
	HBaseView::FitWorld(center_out);
}


//======================================================================
//	Function :HSolidView::SelectFromMessage
//	Description :	Overridden this particular one. We might be in body
//					level selection while our master client might want
//					us to select a face. To get away with this, here's is
//					the intuitive strategy. I overrode this function to 
//					call my_sel->SelectFromMessage rather than my_sel->Select
//	Return :void	-	
//	Parameters :
//			const char *in_data	-	
//			unsigned int data_length	-	
//	Note :
//======================================================================
void HSolidView::SelectFromMessage(const char *in_data, unsigned int data_length)
{
    char data[MVO_BUFFER_SIZE];
	int isSelect = false;
	long ident = 0;
	HC_KEY key = 0;


    memcpy(data, in_data, data_length);
    data[data_length] = '\0';
	    
    sscanf(data, "%d %d", &isSelect, &ident);

	if (m_pSharedKey && (key = m_pSharedKey->GetKeyFromIdent(ident)))
	{
		HSSelectionSet* my_sel = (HSSelectionSet*) GetSelection();
		assert( my_sel );
		if (isSelect)
			my_sel->SelectFromMessage(key, "", INVALID_KEY, INVALID_KEY);
		else
			my_sel->DeSelectFromMessage(key);

		Update();
	}
		
}

//======================================================================
//	Function :		Flush
//	Description :	Override the base Flush to remove any solid modeler
//					objects present
//	Return :void	-	
//	Parameters :
//			bool emit_message=false	-	
//	Note :
//======================================================================
void HSolidView::Flush(bool emit_message)
{
	HSolidModel* model = (HSolidModel*) GetModel();
	assert(model);
	if( model )
		model->DeleteAllEntities();

	HBaseView::Flush(emit_message);
}

void HSolidView::FlushFromMessage(const char *in_data, unsigned int data_length)
{
	HSolidModel* model = (HSolidModel*) GetModel();
	assert(model);
	if( model )
		model->DeleteAllEntities();

	HBaseView::FlushFromMessage(in_data, data_length);
}


/*!
  Sets the visibility of "lines" on the scene key
  \param on_off
*/
void HSolidView::SetVisibilityLines(bool on_off)
{
    HC_Open_Segment_By_Key (GetSceneKey());
        if (on_off) 
            HC_Set_Visibility ("lines = on");
        else 
            HC_Set_Visibility ("lines = off");
    HC_Close_Segment ();

	SetGeometryChanged();
}

/*!
  returns the current visibility settings of lines on the scene key.
  \return bool
*/
bool HSolidView::GetVisibilityLines()
{
	char cval[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key (GetSceneKey());
		HC_Show_One_Net_Visibility("lines", cval);
    HC_Close_Segment ();
	if (strstr(cval,"on"))
		return true;
	else
		return false;
}
/*!
  returns the current visibility settings of lines on the scene key.
  \return bool
*/
bool HSolidView::GetVisibilityVertices()
{
	char cval[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key (GetSceneKey());
		HC_Show_One_Net_Visibility("vertices", cval);
    HC_Close_Segment ();
	if (strstr(cval,"on"))
		return true;
	else
		return false;
}

void HSolidView::SetVisibilityVertices(bool on_off)
{
    HC_Open_Segment_By_Key (GetSceneKey());
        if (on_off) 
            HC_Set_Visibility ("vertices = on");
        else 
            HC_Set_Visibility ("vertices = off");
    HC_Close_Segment ();

	SetGeometryChanged();
}

/*!
  returns the current visibility settings of lines on the scene key.
  \return bool
*/
bool HSolidView::GetVisibilityMarkersOnly()
{
	char cval[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key (GetSceneKey());
		HC_Show_One_Net_Visibility("markers only", cval);
    HC_Close_Segment ();
	if (strstr(cval,"on"))
		return true;
	else
		return false;
}

void HSolidView::SetVisibilityMarkersOnly(bool on_off)
{
    HC_Open_Segment_By_Key (GetSceneKey());
        if (on_off) 
            HC_Set_Visibility ("markers only = on");
        else 
            HC_Set_Visibility ("markers only = off");
    HC_Close_Segment ();

	SetGeometryChanged();
}


/*!
  Sets the visibility of "edges" on the scene key
  \param on_off
*/
void HSolidView::SetVisibilityEdges(bool on_off)
{
    HC_Open_Segment_By_Key (GetSceneKey());
        if (on_off) 
            HC_Set_Visibility ("edges = on");
        else 
            HC_Set_Visibility ("edges = off");
    HC_Close_Segment ();

	SetGeometryChanged();
}

/*!
  returns the current visibility settings of edges on the scene key.
  \return bool
*/
bool HSolidView::GetVisibilityEdges()
{
	char cval[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key (GetSceneKey());
		HC_Show_One_Net_Visibility("edges", cval);
    HC_Close_Segment ();
	if (strstr(cval,"on"))
		return true;
	else
		return false;
}

/*!
  Sets the visibility of "Faces" on the scene key
  \param on_off
*/
void HSolidView::SetVisibilityFaces(bool on_off)
{
    HC_Open_Segment_By_Key (GetSceneKey());
        if (on_off) 
            HC_Set_Visibility ("Faces = on");
        else 
            HC_Set_Visibility ("Faces = off");
    HC_Close_Segment ();

	SetGeometryChanged();
}

/*!
  returns the current visibility settings of Faces on the scene key.
  \return bool
*/
bool HSolidView::GetVisibilityFaces()
{
	char cval[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key (GetSceneKey());
		HC_Show_One_Net_Visibility("Faces", cval);
    HC_Close_Segment ();
	if (strstr(cval,"on"))
		return true;
	else
		return false;
}


/*!
  Sets the visibility of "Markers" on the scene key
  \param on_off
*/
void HSolidView::SetVisibilityMarkers(bool on_off)
{
    HC_Open_Segment_By_Key (GetSceneKey());
        if (on_off) 
            HC_Set_Visibility ("Markers = on");
        else 
            HC_Set_Visibility ("Markers = off");
    HC_Close_Segment ();

	SetGeometryChanged();
}

/*!
  returns the current visibility settings of Markers on the scene key.
  \return bool
*/
bool HSolidView::GetVisibilityMarkers()
{
	char cval[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key (GetSceneKey());
		HC_Show_One_Net_Visibility("Markers", cval);
    HC_Close_Segment ();
	if (strstr(cval,"on"))
		return true;
	else
		return false;
}

void HSolidView::SetShadowMode (HShadowMode shadowMode)
{
	// in collabration, you are only allowed to switch 
	// shadow off. You are not allowed to create one.
	if( m_collab_mode && (shadowMode != HShadowNone) )
		return;
	else
		HBaseView::SetShadowMode(shadowMode);
}

int HSolidView::ObjectCollisionEvent(HBhvTargetObject *tob)
{
	if (m_bShowCollisions)
	{	
		HC_Open_Segment("?style library");
		HC_Open_Segment("collisionstyle");
		HC_Flush_Contents(".", "everything");
		HC_Style_Segment("?Style Library/mvo_highlight_style_segment");
		HC_Close_Segment();
		HC_Close_Segment();
		HC_KEY stylekey;
		char stylepath[4096];
		HC_Open_Segment_By_Key(tob->GetTargetKey());
		HC_Begin_Contents_Search(".", "styles");
		
		while (HUtility::FindContents(stylekey))
		{
			HC_Show_Style_Segment(stylekey, stylepath);
			if (strstr(stylepath, "collisionstyle"))
				HC_Delete_By_Key(stylekey);
			
		}
		HC_End_Contents_Search();
		
		HC_Style_Segment("?Style Library/collisionstyle");
		HC_Close_Segment();
	}
	
	
	return HLISTENER_PASS_EVENT;
}

int HSolidView::ObjectNoCollisionEvent(HBhvTargetObject *tob)
{
 
	HC_KEY stylekey;
	char stylepath[4096];
	HC_Open_Segment_By_Key(tob->GetTargetKey());
	HC_Begin_Contents_Search(".", "styles");

	while (HUtility::FindContents(stylekey))
	{
		HC_Show_Style_Segment(stylekey, stylepath);
		if (strstr(stylepath, "collisionstyle"))
			HC_Delete_By_Key(stylekey);

	}
	HC_End_Contents_Search();
	HC_Close_Segment();

		
	
	return HLISTENER_PASS_EVENT;
}

void HSolidView::Update () {
#ifdef INTEROP
	((HSolidModel *)GetModel())->GetInterOpFileIOHandler()->Update();
	m_pmi->Update();
#endif // INTEROP
	HBaseView::Update();
}
 

ClashItem * HSolidView::AddClash(HC_KEY k1, HC_KEY k2)
{
	ClashItem *item = new ClashItem(k1,k2);
	vlist_add_last(m_ClashList, item);
	return item;
}

void HSolidView::ClearClashList()
{
	if (m_ClashList)
	{
		START_LIST_ITERATION(ClashItem, m_ClashList)
			delete temp;
		END_LIST_ITERATION(m_ClashList);
		delete_vlist(m_ClashList);
	}
	m_ClashList = new_vlist(malloc,free);
}







void HSolidView::ClassifyClashes() 
{
	HC_Begin_Shell_Selection();
	HShellWrapper *myshell1 = 0;
	HC_KEY lastshell = -1;
	HPoint min,max;
	GetSceneExtents(min, max);
	HPoint delta;
	delta.Set((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f,
		(min.z + max.z) / 2.0f);
	float emargin = HC_Compute_Vector_Length(&delta) /5000.0f;
 	START_LIST_ITERATION(ClashItem, m_ClashList)


		float matrix[16];

		if (!temp->m_bHardClash)
		{
		if (lastshell!= temp->m_shell1)
		{
			delete myshell1;
			myshell1 = new HShellWrapper(temp->m_shell1);
			HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(temp->m_shell1));
			HC_Show_Net_Modelling_Matrix(matrix);
			HC_Close_Segment();
			HC_Compute_Transformed_Points(myshell1->m_plen, myshell1->m_Points,matrix,  myshell1->m_Points);
		}
		lastshell = temp->m_shell1;

		HShellWrapper myshell2(temp->m_shell2);
		HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(temp->m_shell2));
		HC_Show_Net_Modelling_Matrix(matrix);
		HC_Close_Segment();
		HC_Compute_Transformed_Points(myshell2.m_plen, myshell2.m_Points,matrix,  myshell2.m_Points);

		int *result2 = new int[myshell2.m_plen];
		float *result = new float[myshell2.m_plen];
		HC_Compute_Points_Inside_Shell(
			myshell2.m_plen, myshell2.m_Points,0,			
			myshell1->m_plen, myshell1->m_Points, myshell1->m_flen, myshell1->m_Flist, "tolerance = 0.00005",
			result2);
		
		HC_Compute_Points_Distance_From_Shell(
			myshell2.m_plen, myshell2.m_Points,
			emargin, 
			myshell1->m_plen, myshell1->m_Points, myshell1->m_flen, myshell1->m_Flist,"",
			result);
		bool hard = false;
		for (int i=0;i<myshell2.m_plen;i++)
		{
			if (result2[i] == -1 && result[i]<0 )
			{
				hard = true;
				break;
			}
		}
		temp->m_bHardClash = hard;

		delete [] result;
		delete [] result2;
		}

 		END_LIST_ITERATION(m_ClashList);
	HC_End_Shell_Selection();
	delete myshell1;

}

static int CZLevelCompare(void const * a, void const * b)
{
	HC_KEY za;
	HC_KEY zb;
	
	za = *(HC_KEY*)a;
	zb = *(HC_KEY*)b;

	int plen, flen;
	int plen2, flen2;
	HC_Show_Shell_Size(za, &plen, &flen);
	HC_Show_Shell_Size(zb, &plen2, &flen2);
 

	if(plen > plen2)
		return -1;
	if(plen < plen2)
		return 1;
 	return 0;
}


void HSolidView::CalculateSelectedClashes(bool doSoft, bool ExtraPrecision, HSelectionSet *tool, HSelectionSet *target)
{
	int numtools = 0;
	HC_KEY *toolshells;
	for (unsigned int i=0;i<tool->GetSize();i++)
	{
		char type[MVO_BUFFER_SIZE];
		HC_KEY key = tool->GetAt(i);
		HC_Show_Key_Type(key, type);
		if (strcmp(type, "shell") == 0)
			numtools++;
		else
		{
			HC_Open_Segment_By_Key(key);
			HC_Begin_Contents_Search("...", "shells");
			int num;
			HC_Show_Contents_Count(&num);
			HC_End_Contents_Search();
			HC_Close_Segment();
			numtools+=num;
		}
	}
	toolshells = new HC_KEY[numtools];
	numtools = 0;
	for (unsigned int i=0;i<tool->GetSize();i++)
	{
		char type[MVO_BUFFER_SIZE];
		HC_KEY key = tool->GetAt(i);
		HC_Show_Key_Type(key, type);
		if (strcmp(type, "shell") == 0)
 			toolshells[numtools++] = key;
 		else
		{
			HC_Open_Segment_By_Key(key);
			HC_Begin_Contents_Search("...", "shells");
			int num;
			HC_Show_Contents_Count(&num);
			for (int j=0;j<num;j++)
			{
				HUtility::FindContents(toolshells[numtools]);
				numtools++;
			}
			HC_End_Contents_Search();
			HC_Close_Segment();			
		}
	}

	HC_KEY tempsegmentkey = HC_KOpen_Segment("/tempcollision");
	HC_Flush_Contents(".", "everything");
	HC_Set_Selectability("faces = on");
	HC_KEY *targetowner;
	targetowner = new HC_KEY[target->GetSize()];


	for (unsigned int i=0;i<target->GetSize();i++)
	{
		float matrix[16];
		HC_KEY ownerkey = HC_KShow_Owner_By_Key(target->GetAt(i));
		targetowner[i] = ownerkey;
		HC_Open_Segment_By_Key(ownerkey);
		HC_Show_Net_Modelling_Matrix(matrix);
		HC_Close_Segment();
		HC_Open_Segment("");		
		HC_Move_By_Key(target->GetAt(i), ".");
		HC_Set_Modelling_Matrix(matrix);
		HC_Close_Segment();
	}
	HC_Close_Segment();
		

	CalculateClashes(doSoft, ExtraPrecision, tempsegmentkey, numtools, toolshells);
	delete [] toolshells;
	for (unsigned int i=0;i<target->GetSize();i++)
	{
		HC_Open_Segment_By_Key(targetowner[i]);
		HC_Move_By_Key(target->GetAt(i), ".");
		HC_Close_Segment();
	}
	HC_Delete_By_Key(tempsegmentkey);
	delete [] targetowner;

}







void HSolidView::CalculateClashes(bool doSoft, bool ExtraPrecision, HC_KEY startsegment, int shellnum, HC_KEY *shelllist) 
{
	
	int j;
	ClearClashList();

	HC_Begin_Shell_Selection();
	int snum = 0;
	float matrix[16];
	HC_KEY shellkey;
	HC_KEY *shells;
	if (shelllist)
	{
		shells = shelllist;
		snum = shellnum;
	}
	else
	{
		HC_Open_Segment_By_Key(GetModelKey());
		HC_Begin_Contents_Search("...", "shells");
		HC_Show_Contents_Count(&snum);
		shells = new HC_KEY[snum];
		snum = 0;
		while (HUtility::FindContents(shellkey))	
			shells[snum++] = shellkey;
		HC_End_Contents_Search();
		HC_Close_Segment();
	}
	qsort(shells, snum, sizeof(HC_KEY), CZLevelCompare);
	
	for (int i=0;i<snum;i++)
	{
		HShellWrapper myshell(shells[i]);
		HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(shells[i]));
		HC_Show_Net_Modelling_Matrix(matrix);
		HC_Close_Segment();
		HC_Compute_Transformed_Points(myshell.m_plen, myshell.m_Points,matrix,  myshell.m_Points);
		if (startsegment == INVALID_KEY)
			HC_Open_Segment_By_Key(GetViewKey());
		else
			HC_Open_Segment_By_Key(startsegment);
		HC_QSet_Heuristics (".", "no related selection limit" );
		int scount = HC_Compute_Selection_By_Shell("v", ".", myshell.m_plen, myshell.m_Points,
			myshell.m_flen, myshell.m_Flist);

		struct vlist_s * tempitemlist = new_vlist(malloc, free);

		for (j=0;j<scount;j++)
		{
			HC_KEY key2;
			int o1,o2,o3;
			HC_Show_Selection_Element(&key2, &o1,&o2,&o3);
			bool alreadydone = false;
			for (int k=0;k<i;k++)
			{
				if (key2 == shells[k])
				{
					alreadydone = true;
					break;
				}
			}
			if (shells[i] != key2 && !alreadydone)
			{
 				ClashItem *item = AddClash(shells[i],key2);
				vlist_add_last(tempitemlist, item);	
				if (doSoft)
					item->m_bHardClash = false;
				else
					item->m_bHardClash = true;
			}

			HC_Find_Related_Selection();
		}
 		
		if (doSoft)
		{
			scount = HC_Compute_Selection_By_Shell_With_Options("v", ".", myshell.m_plen, myshell.m_Points,
				myshell.m_flen, myshell.m_Flist,"tolerance = -1");

			for (j=0;j<scount;j++)
			{
				HC_KEY key2;
				int o1,o2,o3;
				HC_Show_Selection_Element(&key2, &o1,&o2,&o3);

				START_LIST_ITERATION(ClashItem, tempitemlist)
					if (temp->m_shell2 == key2)
						temp->m_bHardClash = true;
				END_LIST_ITERATION(tempitemlist);
				
	 
				HC_Find_Related_Selection();
			}
		}
 		HC_Close_Segment();
		
		delete_vlist(tempitemlist);
	}
	HC_End_Shell_Selection();
	if (!shelllist)
		delete [] shells;
	if (doSoft && ExtraPrecision)
		ClassifyClashes();
}


static FramerateMode FramerateCStringToMode(CString mode)
{
	if(mode=="Fixed Framerate")
		return FramerateFixed;
	else
		return FramerateTarget;
}
static HLRMode HLRCString2Enum(CString hlr)
{
	if(hlr == "Analytic")
		return AnalyticHiddenLine;
	else if(hlr == "Fast")
		return FastHiddenLine;
	else 
		return FakeHiddenLine;	
}

static DisplayListType DisplayListCString2Enum(CString dl)
{
	if(dl == "Geometry")
		return DisplayListGeometry;
	else if(dl == "Segment")
		return DisplayListSegment;
	else 
		return DisplayListOff;	
}

static CString FramerateModeToCString(FramerateMode mode)
{
	if(mode==FramerateFixed)
		return "Fixed Framerate";
	else
		return "Target Framerate";
}

static CString HLREnum2CString(HLRMode hlr)
{
	if(hlr == AnalyticHiddenLine)
		return "Analytic";
	else if(hlr == FastHiddenLine)
		return "Fast";
	else 
		return "Fake";
}
static CString DisplayListEnum2CString(DisplayListType dl)
{
	if(dl == DisplayListGeometry)
		return "Geometry";
	else if(dl == DisplayListSegment)
		return "Segment";
	else 
		return "Off";
}

static CString MultiThreadingEnum2CString(MultiThreadingType mt)
{
	if(mt == MultiThreadingFull || mt == MultiThreadingBasic)
		return "Full";
	else 
		return "Off";
}

static MultiThreadingType MultiThreadingCString2Enum(CString mt)
{
	if(mt == "Full")
		return MultiThreadingFull;
	else if(mt == "Basic")
		return MultiThreadingBasic;
	else 
		return MultiThreadingOff;	
}

PerformanceSettings::PerformanceSettings()
{
	m_MaxThreshold = 10;
	m_Cutoff = 10;
	m_DetailSteps = 5;
	m_bDynamicAdjustment = FALSE;
	m_bUseLods = FALSE;
	m_csHLRMode = _T("Fast");
	m_bStaticModel = TRUE;
	m_bDisableEditing = FALSE;
	m_bLMV = FALSE;
	m_bOcclusionCulling = FALSE;
	m_OcclusionThreshold = 50;
	m_csDisplayList = _T("Geometry");
	m_bCullingThreshold = FALSE;
	m_csFramerateMode = _T("Fixed Framerate");
	m_CullingThreshold = 10;
	m_FramerateTime = 0.01f;
	m_bUseFramerate = FALSE;
	m_csMultiThreading = _T("Off");
}
void PerformanceSettings::Apply(CSolidHoopsView *pActiveView)
{
	bool old_disable_editing = CAppSettings::DisableEditing;
	bool old_static_model = CAppSettings::StaticModel;
	bool old_lmv_setting = CAppSettings::LMVModel;
	char sysopt[MVO_BUFFER_SIZE];
	DisplayListType old_display_list = CAppSettings::DisplayList;

	CAppSettings::CullingThreshold = m_CullingThreshold;
	CAppSettings::CullingThresholdSet = BOOL2bool(m_bCullingThreshold);
	CAppSettings::UseFramerate = BOOL2bool(m_bUseFramerate);
	CAppSettings::CurrentFramerateMode = FramerateCStringToMode(m_csFramerateMode);
	CAppSettings::FramerateTime = m_FramerateTime;
	CAppSettings::MaxThreshold = m_MaxThreshold;
	CAppSettings::HardCutoff = m_Cutoff;
	CAppSettings::DetailSteps = m_DetailSteps;
	CAppSettings::DynamicAdjustment = m_bDynamicAdjustment;
	CAppSettings::UseLods = m_bUseLods;

    CAppSettings::HiddenLineMode = HLRCString2Enum(m_csHLRMode);
	CAppSettings::StaticModel = BOOL2bool(m_bStaticModel);
	CAppSettings::DisableEditing = BOOL2bool(m_bDisableEditing);
	CAppSettings::LMVModel = BOOL2bool(m_bLMV);
    CAppSettings::OcclusionCulling = BOOL2bool(m_bOcclusionCulling);
	CAppSettings::OcclusionThreshold = m_OcclusionThreshold;
	CAppSettings::DisplayList = DisplayListCString2Enum(m_csDisplayList);
	CAppSettings::MultiThreading = MultiThreadingCString2Enum(m_csMultiThreading);
	CAppSettings::FakeHLRColor = m_clrbtnFakeHLR.currentcolor;

	sprintf(sysopt, "multi-threading=%s", 
		CAppSettings::MultiThreading==MultiThreadingFull ? "full" : 
		CAppSettings::MultiThreading==MultiThreadingBasic ? "basic" : "off");
	HC_Define_System_Options(sysopt);
		
	if (pActiveView)
	{
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}
		pBaseView->SetSuppressUpdate(true);
		if(CAppSettings::UseFramerate)
		{
			pBaseView->SetFramerateMode(CAppSettings::CurrentFramerateMode, CAppSettings::FramerateTime,
				CAppSettings::MaxThreshold, CAppSettings::UseLods?true:false, CAppSettings::DetailSteps, 
				CAppSettings::HardCutoff);
			if(CAppSettings::CurrentFramerateMode==FramerateTarget)
				pBaseView->SetViewUpdateMode(CAppSettings::TimerBasedUpdate ? Continuous : OnDemand);
		}
		else if (CAppSettings::CullingThresholdSet)
		{
			pBaseView->SetFramerateMode(FramerateOff);
			pBaseView->SetCullingThreshold(CAppSettings::CullingThreshold);
		}
		else
		{
 			pBaseView->SetFramerateMode(FramerateOff);
			pBaseView->SetCullingThreshold(0);
		}

		pBaseView->SetForceFastHiddenLine(CAppSettings::HiddenLineMode==FastHiddenLine);
		//apply the display list settings
		if(CAppSettings::DisplayList == DisplayListOff)
			pBaseView->SetDisplayListMode(false);
		else 
		{
			pBaseView->SetDisplayListType(CAppSettings::DisplayList);
			pBaseView->SetDisplayListMode(true);
		}

		pBaseView->SetOcclusionCullingMode(CAppSettings::OcclusionCulling, true, 
			CAppSettings::OcclusionThreshold);

		//GetStaticModel gives us a more accurate look at what the real state of the static model is
		old_static_model=pBaseView->GetModel()->GetStaticModel();
		if(CAppSettings::StaticModel!=old_static_model)
			pBaseView->GetModel()->SetStaticModel(CAppSettings::StaticModel);

		if(old_lmv_setting != CAppSettings::LMVModel)
			pBaseView->GetModel()->SetLMVModel(CAppSettings::LMVModel);

		if(old_disable_editing!=CAppSettings::DisableEditing
			&& pActiveView->GetSegmentBrowserState())
			pActiveView->RefreshSegmentBrowser ();

		pBaseView->SetDisplayHandlesOnDblClk(!CAppSettings::DisableEditing);
		if(CAppSettings::DisableEditing && pBaseView->GetHasObjects())
			HUtilityGeomHandle::ClearAllHandles(pBaseView);
		
		HPoint FakeHLRColor;
	    FakeHLRColor.Set(
		static_cast<float>(GetRValue(CAppSettings::FakeHLRColor))/255.0f,
		static_cast<float>(GetGValue(CAppSettings::FakeHLRColor))/255.0f,
		static_cast<float>(GetBValue(CAppSettings::FakeHLRColor))/255.0f);
		pBaseView->SetFakeHLRColor(FakeHLRColor);
		pBaseView->SetSuppressUpdate(false);

		//only do an exhaustive update if the static or display list modes have changed.
		if(old_static_model!=CAppSettings::StaticModel || old_display_list!=CAppSettings::DisplayList)
			pBaseView->ExhaustiveUpdate();
		else
			pBaseView->Update();
	}
}
void PerformanceSettings::Get()
{
	m_bCullingThreshold = CAppSettings::CullingThresholdSet;
	m_CullingThreshold = CAppSettings::CullingThreshold;
	m_bUseFramerate = bool2BOOL(CAppSettings::UseFramerate);
	m_csFramerateMode = FramerateModeToCString(CAppSettings::CurrentFramerateMode);
	m_FramerateTime = CAppSettings::FramerateTime;
	m_MaxThreshold = CAppSettings::MaxThreshold;
	m_Cutoff = CAppSettings::HardCutoff;
 	m_DetailSteps = CAppSettings::DetailSteps;
 	m_bDynamicAdjustment = CAppSettings::DynamicAdjustment;
 	m_bUseLods = CAppSettings::UseLods;

	m_csHLRMode = HLREnum2CString(CAppSettings::HiddenLineMode);
	m_bStaticModel = bool2BOOL(CAppSettings::StaticModel);
	m_bDisableEditing = bool2BOOL(CAppSettings::DisableEditing);
	m_bLMV = bool2BOOL(CAppSettings::LMVModel);
	m_bOcclusionCulling = bool2BOOL(CAppSettings::OcclusionCulling);
  	m_OcclusionThreshold = CAppSettings::OcclusionThreshold;
	m_csDisplayList = DisplayListEnum2CString(CAppSettings::DisplayList);
	m_csMultiThreading = MultiThreadingEnum2CString(CAppSettings::MultiThreading);
	m_clrbtnFakeHLR.currentcolor = CAppSettings::FakeHLRColor;
}

void PerformanceSettings::Reset()
{
	m_bCullingThreshold = CAppSettings::DefaultCullingThresholdSet;
	m_CullingThreshold = CAppSettings::DefaultCullingThreshold;
	m_bUseFramerate = bool2BOOL(CAppSettings::DefaultUseFramerate);
	m_csFramerateMode = FramerateModeToCString(CAppSettings::DefaultCurrentFramerateMode);
	m_FramerateTime = CAppSettings::DefaultFramerateTime;
	m_MaxThreshold = CAppSettings::DefaultMaxThreshold;
	m_Cutoff = CAppSettings::DefaultHardCutoff;
	m_DetailSteps = CAppSettings::DefaultDetailSteps;
	m_bDynamicAdjustment = CAppSettings::DefaultDynamicAdjustment;
	m_bUseLods = CAppSettings::DefaultUseLods;

 	m_csHLRMode = HLREnum2CString(CAppSettings::DefaultHiddenLineMode);
	m_bStaticModel = bool2BOOL(CAppSettings::DefaultStaticModel);
	//as wonky as it sounds, disable editing should use the same default as static model
	m_bDisableEditing = bool2BOOL(CAppSettings::DefaultStaticModel);
	m_bLMV = bool2BOOL(CAppSettings::DefaultLMVModel);
	m_bOcclusionCulling = bool2BOOL(CAppSettings::DefaultOcclusionCulling);
	m_OcclusionThreshold = CAppSettings::DefaultOcclusionThreshold;
	m_csDisplayList = DisplayListEnum2CString(CAppSettings::DefaultDisplayList);
	m_csMultiThreading = MultiThreadingEnum2CString(CAppSettings::DefaultMultiThreading);
	m_clrbtnFakeHLR.currentcolor = CAppSettings::DefaultFakeHLRColor;
}


void PerformanceSettings::SetModeInternal(HViewerPerformance perf)
{
	Get();
	switch(perf)
	{
		case DefaultMode:
			m_bUseFramerate = FALSE;
			m_csFramerateMode = "Fixed Framerate";
			m_bCullingThreshold = TRUE;
			m_CullingThreshold = 10;
			m_csDisplayList = "Geometry";
			m_bStaticModel = FALSE;
			m_bLMV = FALSE;
		break;
		case Optimal:
			m_bUseFramerate = FALSE;
			m_csFramerateMode = "Fixed Framerate";
			m_bCullingThreshold = TRUE;
			m_CullingThreshold = 10;
			m_csDisplayList = "Segment";
			m_bStaticModel = TRUE;
			m_bLMV = TRUE;
		break;
		case SegmentLevelDisplayLists:
			m_csDisplayList = "Segment";
		break;
		case GeometryLevelDisplayLists:
			m_csDisplayList = "Geometry";
		break;
		case StaticModel:
			m_bStaticModel = TRUE;
			m_bLMV = TRUE;
		break;
		case CullingThreshold:
			m_bCullingThreshold = TRUE;
			m_bUseFramerate = FALSE;
		break;
		case FixedFramerate:
			m_bCullingThreshold = FALSE;
			m_bUseFramerate = TRUE;
			m_csFramerateMode = "Fixed Framerate";
		break;
		case TargetFramerate:
			m_bCullingThreshold = FALSE;
			m_bUseFramerate = TRUE;
			m_csFramerateMode = "Target Framerate";
		break;
	};
}

bool PerformanceSettings::Compare(PerformanceSettings &c)
{
	if (c.m_bUseFramerate == m_bUseFramerate && c.m_csFramerateMode == m_csFramerateMode &&
		c.m_bCullingThreshold == m_bCullingThreshold &&
		c.m_csDisplayList == m_csDisplayList && c.m_CullingThreshold == m_CullingThreshold && 
		c.m_bStaticModel == m_bStaticModel)		
		return true;
	else
		return false;
}
HViewerPerformance PerformanceSettings::GetCurrentSetting()
{
	PerformanceSettings s1;
	Get();
	s1.SetModeInternal(DefaultMode);
	Get();
	if (Compare(s1))
		return DefaultMode;

	s1.SetModeInternal(Optimal);
	Get();
	if (Compare(s1))
		return Optimal;

	return Custom;
}

void PerformanceSettings::SetMode(HViewerPerformance perf)
{
	SetModeInternal(perf);
	ApplyInternal();
}

void PerformanceSettings::ApplyInternal()
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
 	Apply(pActiveView);
	if (pActiveView) {
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if (pBaseView)
			pBaseView->Update();
	}
}

void PerformanceSettings::UnSet(HViewerPerformance perf)
{
	UnSetInternal(perf);
	ApplyInternal();
}

void PerformanceSettings::UnSetInternal(HViewerPerformance perf)
{
	Get();
	if(perf == SegmentLevelDisplayLists)
		m_csDisplayList = "None";
	else if(perf == GeometryLevelDisplayLists)
		m_csDisplayList = "None";
	else if(perf == StaticModel)
	{
		m_bStaticModel = FALSE;
		m_bLMV = FALSE;
	}
	else if(perf == CullingThreshold)
		m_bCullingThreshold = FALSE;
	else if(perf == FixedFramerate)
		m_bUseFramerate = FALSE;
	else if(perf == TargetFramerate)
		m_bUseFramerate = FALSE;
}

bool PerformanceSettings::Show(HViewerPerformance perf)
{
	Get();
	if(perf == SegmentLevelDisplayLists)
		return m_csDisplayList == "Segment";
	else if(perf == GeometryLevelDisplayLists)
		return m_csDisplayList == "Geometry";
	else if(perf == StaticModel)
		return m_bStaticModel == TRUE;
	else if(perf == CullingThreshold)
		return m_bCullingThreshold == TRUE;
	else if(perf == FixedFramerate)
		return (m_bUseFramerate == TRUE && m_csFramerateMode == "Fixed Framerate");
	else if(perf == TargetFramerate)
		return (m_bUseFramerate == TRUE && m_csFramerateMode == "Target Framerate");

	return false;
}

EffectSettings::EffectSettings()
{
	m_AmbientOcclusion = FALSE;
	m_Bloom = FALSE;
	m_FastSilhouetteEdges = FALSE;
	m_ReflectionPlane = FALSE;
	m_ShadowMaps = FALSE;
	m_SimpleShadows = FALSE;
}

void EffectSettings::Apply(CSolidHoopsView *pActiveView)
{
	CAppSettings::ShadowMode = (m_SimpleShadows == FALSE) ? HShadowNone : HShadowSoft;
	CAppSettings::bReflectionPlane = BOOL2bool(m_ReflectionPlane);
	CAppSettings::bShadowMap = BOOL2bool(m_ShadowMaps);
	CAppSettings::UseFastAmbient = BOOL2bool(m_AmbientOcclusion);
	CAppSettings::UseFastSilhouette = BOOL2bool(m_FastSilhouetteEdges);
	CAppSettings::UseBloom = BOOL2bool(m_Bloom);

	if (pActiveView)
	{
		char dopt[MVO_BUFFER_SIZE];
		char ropt[MVO_BUFFER_SIZE];
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}
		pBaseView->SetSuppressUpdate(true);

		HCLOCALE(sprintf(dopt, 
		"ambient occlusion = (%s, strength = %f)",
		(CAppSettings::UseFastAmbient ? "on" : "off") , CAppSettings::FastAmbientStrength) );

		if(pBaseView->GetRenderMode() != HRenderFakeHiddenLine)
			HCLOCALE(sprintf(dopt, "%s, fast silhouette edges = (%s, tolerance = %f, %s heavy exterior)",
				dopt, 
				(CAppSettings::UseFastSilhouette ? "on" : "off"), CAppSettings::FastSilhouetteTolerance,
				(CAppSettings::HeavyExteriorSilhouette ? "" : "no") ));

		
		HCLOCALE(sprintf(dopt, "%s, bloom = (%s, strength=%f, blur=%d, shape=%s)", dopt,
			(CAppSettings::UseBloom ? "on" : "off"), 
			CAppSettings::BloomStrength, 
			CAppSettings::BloomBlur,
			(CAppSettings::BloomShape == RadialBloom ? "radial" : "star") )); 

		pBaseView->SetReflectionPlane(CAppSettings::bReflectionPlane, CAppSettings::ReflectionOpacity, 
			CAppSettings::bReflectionFading, CAppSettings::ReflectionUseAttenuation,
			CAppSettings::ReflectionHither, CAppSettings::ReflectionYon,
			CAppSettings::ReflectionUseBlur, CAppSettings::ReflectionBlur);

		if( CAppSettings::ShadowMode != pBaseView->GetShadowMode() )
			pBaseView->SetShadowMode(CAppSettings::ShadowMode);
		
		HC_Open_Segment_By_Key (pBaseView->GetShadowMapSegmentKey()); {
			if(CAppSettings::bShadowMap)
				sprintf(ropt, "shadow map=(on, %s jitter, %s)", 
				(CAppSettings::Jitter ? "" : "no"), 
				(CAppSettings::ViewDependentShadowMap ? "view dependent" : "view independent"));
			else 
				sprintf(ropt, "no shadow map");

			HC_Set_Rendering_Options (ropt);
			if(BOOL2bool(m_ShadowMaps))
				HC_Set_Visibility ("shadows = (emitting, casting, receiving)");
			sprintf(ropt, "simple shadow = (opacity = %f)", CAppSettings::ShadowOpacity);
			HC_Set_Rendering_Options (ropt);
		} HC_Close_Segment(); 
		
		HC_Open_Segment_By_Key(pActiveView->GetViewKey()); {
			HC_Set_Driver_Options(dopt);
		} HC_Close_Segment();

		pBaseView->SetSuppressUpdate(false);
	}
}

void EffectSettings::Get()
{
	m_AmbientOcclusion = CAppSettings::UseFastAmbient;
	m_Bloom = CAppSettings::UseBloom;
	m_FastSilhouetteEdges = CAppSettings::UseFastSilhouette;
	m_ReflectionPlane = CAppSettings::bReflectionPlane;
	m_ShadowMaps = CAppSettings::bShadowMap;
	m_SimpleShadows = (CAppSettings::ShadowMode == HShadowNone) ? FALSE : TRUE;
}

void EffectSettings::ApplyInternal()
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
 	Apply(pActiveView);
	if (pActiveView) {
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if (pBaseView)
			pBaseView->Update();
	}
}

void EffectSettings::Set(HViewerEffects fx)
{
	SetInternal(fx);
	ApplyInternal();
}

void EffectSettings::SetInternal(HViewerEffects fx)
{
	Get();
	if(fx == None)
	{
		m_AmbientOcclusion = FALSE;
		m_Bloom = FALSE;
		m_FastSilhouetteEdges = FALSE;
		m_ReflectionPlane = FALSE;
		m_ShadowMaps = FALSE;
		m_SimpleShadows = FALSE;
	}
	else if(fx == Fancy)
	{
		m_AmbientOcclusion = TRUE;
		m_Bloom = TRUE;
		m_FastSilhouetteEdges = TRUE;
		m_ReflectionPlane = FALSE;
		m_ShadowMaps = FALSE;
		m_SimpleShadows = FALSE;
	}
	else if(fx == AmbientOcclusion)
		m_AmbientOcclusion = TRUE;
	else if(fx == Bloom)
		m_Bloom = TRUE;
	else if(fx == FastSilhouetteEdges)
		m_FastSilhouetteEdges = TRUE;
	else if(fx == ReflectionPlane)
		m_ReflectionPlane = TRUE;
	else if(fx == ShadowMaps)
		m_ShadowMaps = TRUE;
	else if(fx == SimpleShadows)
		m_SimpleShadows = TRUE;
}

void EffectSettings::UnSet(HViewerEffects fx)
{
	UnSetInternal(fx);
	ApplyInternal();
}

void EffectSettings::UnSetInternal(HViewerEffects fx)
{
	Get();
	if(fx == AmbientOcclusion)
		m_AmbientOcclusion = FALSE;
	else if(fx == Bloom)
		m_Bloom = FALSE;
	else if(fx == FastSilhouetteEdges)
		m_FastSilhouetteEdges = FALSE;
	else if(fx == ReflectionPlane)
		m_ReflectionPlane = FALSE;
	else if(fx == ShadowMaps)
		m_ShadowMaps = FALSE;
	else if(fx == SimpleShadows)
		m_SimpleShadows = FALSE;
}

bool EffectSettings::Show(HViewerEffects fx)
{
	Get();
	if(fx == None)
		return (m_AmbientOcclusion == FALSE && m_Bloom == FALSE && m_FastSilhouetteEdges == FALSE
			&&	m_ReflectionPlane == FALSE && m_ShadowMaps == FALSE &&	m_SimpleShadows == FALSE);
	else if(fx == Fancy)
		return (m_AmbientOcclusion == TRUE && m_Bloom == TRUE && m_FastSilhouetteEdges == TRUE 
			&& m_ReflectionPlane == FALSE && m_ShadowMaps == FALSE && m_SimpleShadows == FALSE);
	else if(fx == AmbientOcclusion)
		return m_AmbientOcclusion == TRUE;
	else if(fx == Bloom)
		return m_Bloom == TRUE;
	else if(fx == FastSilhouetteEdges)
		return m_FastSilhouetteEdges == TRUE;
	else if(fx == ReflectionPlane)
		return m_ReflectionPlane == TRUE;
	else if(fx == ShadowMaps)
		return m_ShadowMaps == TRUE;
	else if(fx == SimpleShadows)
		return m_SimpleShadows == TRUE;

	return false;
}



	