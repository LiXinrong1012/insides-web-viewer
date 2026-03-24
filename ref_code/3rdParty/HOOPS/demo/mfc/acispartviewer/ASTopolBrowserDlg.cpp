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

// TopolBrowserDlg.cpp : implementation file
//

#include "StdAfx.h"

#include "HSInclude.h"
#include "HSSelectionSet.h"
#include "AnnotateDlg.h"
#include "BusyDlg.h"
#include "ASTopolBrowserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "CSolidHoopsApp.h"
#include "CSolidHoopsFrm.h"
#include "HSolidView.h"
#include "HSolidModel.h"
#include "HUtilityLocaleString.h"
#include "HSAcisSelectionSet.h"

extern CSolidHoopsApp theApp;

#ifdef ACIS

void CHECK_OUTCOME( const outcome& result )
{
	if( !result.ok() ) {

		char default_msg[MVO_BUFFER_SIZE];
		const char* error_string = find_err_mess( result.error_number() );
		if( (error_string == NULL ) || (*error_string == '\0')) {
			sprintf(default_msg,"%d",result.error_number());
			error_string = default_msg;
		}

		MessageBox(NULL, H_TEXT(error_string), _T("ACIS Error"),
					MB_OK|MB_ICONSTOP|MB_APPLMODAL);
	}
}
 
//this function inserts a new item into the tree control with it's name (if available) and the tagid
HTREEITEM CASTopolBrowserDlg::InsertItemInTree( ENTITY* entity, const char* basetext, HTREEITEM position)
{
	char text[MVO_BUFFER_SIZE];	
	
	TVINSERTSTRUCT is;
	is.hParent = position;
	is.hInsertAfter=TVI_LAST;
	is.item.mask=TVIF_CHILDREN | TVIF_TEXT;
	
	outcome o;
	int eclass;
	if (entity)
	{
		eclass = entity->identity();
		if( eclass == VERTEX_TYPE ) //vertices have no kids
		{
			is.item.cChildren = 0;			
		}
		else if( eclass == FACE_TYPE)	//faces might have no edges
		{
			int num_edges = 0;
			ENTITY_LIST edge_list;
			o = api_get_edges ( entity, edge_list );
			num_edges = edge_list.iteration_count();
			CHECK_OUTCOME(o);
			if (num_edges)
				is.item.cChildren = 1;	
			else
				is.item.cChildren = 0;	
		}
		else if( eclass == EDGE_TYPE)	//edges might have no vertices
		{
			int num_vtxs = 0;
			ENTITY_LIST vtx_list;
			o = api_get_vertices( entity, vtx_list );
			num_vtxs = vtx_list.iteration_count();
			CHECK_OUTCOME(o);
			if (num_vtxs)
				is.item.cChildren = 1;	
			else
				is.item.cChildren = 0;	
		}
		else
		{
			is.item.cChildren = 1;	
		}
	}
	else
		is.item.cChildren = 1;	

	if (entity)
	    sprintf(text,"%s%d",basetext,entity);
	else
	    sprintf(text,"%s",basetext);

	H_TEXT label_text(text);
	is.item.pszText= (LPTSTR)(const TCHAR*)label_text; // pszText is not const - even though it is meant to be
	HTREEITEM item = m_topol_tree.InsertItem(&is);
	m_topol_tree.SetItemData(item,(DWORD)entity);
	if (entity)
	{	
		if (eclass == ASM_ASSEMBLY_TYPE)
			m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(14), TVIS_STATEIMAGEMASK );
		else if (eclass == ASM_MODEL_REF_TYPE)
			m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(14), TVIS_STATEIMAGEMASK );
	    else if (eclass == BODY_TYPE)
			m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(8), TVIS_STATEIMAGEMASK );
	    else if (eclass == FACE_TYPE)
			m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(10), TVIS_STATEIMAGEMASK );
	    else if (eclass == EDGE_TYPE)
			m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(11), TVIS_STATEIMAGEMASK );
	    else if (eclass == VERTEX_TYPE)
			m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(12), TVIS_STATEIMAGEMASK );
	    else if (eclass == SHELL_TYPE)
			m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(9), TVIS_STATEIMAGEMASK );
	}
	return item;
}


BOOL CASTopolBrowserDlg::OnInitDialog() 
{
	m_topol_tree.SubclassDlgItem(IDC_TREE1,this);

 	CTopolBrowserDlg::OnInitDialog();
	m_TopologyBrowserSwitch.SetState(true);
#ifndef INTEROP
	m_InterOpPartBrowserSwitch.ShowWindow(SW_HIDE);
#endif

	BuildTopolTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


bool CASTopolBrowserDlg::BuildTopolTree()
{
  	CString title =((CView *)m_parent)->GetDocument()->GetTitle();
 	SetWindowText("Topology Browser - "+title);
	m_dialogactive=true;	

	int tabs[5]={5,10,15,20,25};
	m_infolist.SetTabStops(4,tabs);
	m_TopInfoList.SetTabStops(4,tabs);

	HTREEITEM topitem = InsertItemInTree(0,H_ASCII_TEXT(title),TVI_ROOT);
	
	HSolidModel * model = (HSolidModel *)(m_pHView->GetModel());

	asm_model_list models = model->GetModelList();
	if( models.iteration_count() > 0)
	{
		models.init();
		asm_model* this_model = models.next();
		while (this_model)
		{
			FillItems(this_model, topitem);
			this_model = models.next();
		}
	}
	else
	{
		int numbodies = 0;
		ENTITY_LIST bodies = model->GetEntityList();
		bodies.init();

		int totalnumfaces=0;
		ENTITY *ent=0;
		while((ent = bodies.next())!=0) 
		{
			int numfaces = 0;
			ENTITY_LIST faces;
			api_get_faces(ent, faces);
			totalnumfaces+=faces.iteration_count();
			CString ent_type(ent->type_name());
			ent_type+=" ";
			HTREEITEM bodyitem = InsertItemInTree(ent,H_ASCII_TEXT(ent_type),topitem);
			if (!m_rootitem)
				m_rootitem = bodyitem;
		}

		m_TopInfoList.ResetContent();
		CString indent = "\t";

		m_TopInfoList.AddString(title + " contains:");
		char text[MVO_BUFFER_SIZE];
		if (numbodies>1)
			sprintf(text,"%d bodies/instances",numbodies);
		else
			sprintf(text,"%d body/instance",numbodies); 
		m_TopInfoList.AddString(indent + text);
		sprintf(text,"%d faces (total)",totalnumfaces);
		m_TopInfoList.AddString(indent + text);

	}

	HighlightSelection();


	return true;
}

//automatically highlights a selection and jumps to the right location in the tree
bool CASTopolBrowserDlg::HighlightSelection()
{ 
	if( !GetSafeHwnd() )
		return false;

	ENTITY* ents[10];
	HSSelectionSet* selection;

 	selection = (HSSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSolidListSize();
	if (!ssize)
	{
		ShowSelectedItems();
		return false;
	}

	outcome o;
	//it would be nice if we could always expand all selected entities but this can take too long 
	int start;
	if (ssize>200)
		start=ssize-200;
	else
		start=0;

	for (int j=start;j<ssize;j++)
	{
		//we query the hierarchy (body-face-edge) for the selection that we want to expand
 		int depth=0;
		ENTITY* entity = (ENTITY*)selection->GetAtSolidEntity(j);
		int eclass = entity->identity();
		if( eclass == BODY_TYPE )
		{
			depth=0;
			ents[0]=entity;
		}
		else if( eclass == FACE_TYPE )
		{
			depth=2;
			ents[2]=entity;

			// get the shell for the face
			ents[1] = (ENTITY*) ((FACE *)entity)->shell();
			assert( ents[1] );

			// get the body for the face
			o = api_get_owner( entity, ents[0] );
			CHECK_OUTCOME(o);
			assert( ents[0] );
		}
		else if( eclass == EDGE_TYPE )
		{
			depth=3;
			ents[3]=entity;

			// get the face for edge
			ENTITY_LIST faces;
			o = api_get_faces( entity, faces );
			CHECK_OUTCOME(o);
			if( faces[0] )
				ents[2] = faces[0];

			// get the shell
			ENTITY* face_sh = (ENTITY*) ((FACE *)faces[0])->shell();
			if( face_sh )
				ents[1] = face_sh;
			
			// get the body for the edge
			o = api_get_owner( entity, ents[0] );
			CHECK_OUTCOME(o);
			assert( ents[0] );

		}
		else if( eclass == VERTEX_TYPE )
		{
			depth=4;
			ents[4]=entity;

			// get the edge for vertex
			ENTITY_LIST edges;
			o = api_get_edges( entity, edges);
			CHECK_OUTCOME(o);
			if( edges[0] )
				ents[3] = edges[0];

			// get the face for edge
			ENTITY_LIST faces;
			o = api_get_faces( entity, faces );
			CHECK_OUTCOME(o);
			if( faces[0] )
				ents[2] = faces[0];

			// get the shell
			ENTITY* face_sh = (ENTITY*) ((FACE *)faces[0])->shell();
			if( face_sh )
				ents[1] = face_sh;
			
			// get the body for the edge
			o = api_get_owner( entity, ents[0] );
			CHECK_OUTCOME(o);
			assert( ents[0] );

		}

		
		//now we look through the tree starting from the root item and expand the subtrees
		//as necessary until the selected item is reached
		HTREEITEM aitem=m_rootitem;
		ENTITY* result = (ENTITY*) m_topol_tree.GetItemData(aitem);
		for (int i=0;i<=depth;i++)
		{			
			while (result!=ents[i])
			{	
				aitem=m_topol_tree.GetNextSiblingItem(aitem);
				result = (ENTITY*) m_topol_tree.GetItemData(aitem);
				
				
			}
			if (i==depth) 
			{
				if (j==ssize-1)
				{
					m_bItemSelected = true;
					m_topol_tree.SelectItem(aitem);
				}
				
			}			
			else
			{				 
//				FillItems(result,aitem);
				UINT state = m_topol_tree.GetItemState(aitem,TVIS_EXPANDEDONCE); 				
				if (!(state & TVIS_EXPANDEDONCE))
					m_topol_tree.Expand(aitem,TVE_EXPAND);

				m_topol_tree.SetItemState(aitem,TVIS_EXPANDEDONCE,TVIS_EXPANDEDONCE);
 				
				aitem = m_topol_tree.GetChildItem(aitem);
				result = (ENTITY*) m_topol_tree.GetItemData(aitem);
			}
			
		}	
	 
	}
	ShowSelectedItems();

 	return true;

} 
	

//update the listbox with various information on the selected entities
void CASTopolBrowserDlg::UpdateInfoWindow(ENTITY* entity)
{
	m_infolist.ResetContent();

	int eclass;
	CString info = "Class:";
	eclass = entity->identity();
	CString indent = "\t";
	char text[MVO_BUFFER_SIZE];
	if( eclass == VERTEX_TYPE )
	{
		info+="Vertex";
		m_infolist.AddString(info);
		
		// get the point
		APOINT* point = ((VERTEX*)entity)->geometry();
		if (point)
		{
			sprintf(text,"Geom:%d",point);
			m_infolist.AddString(indent + text);
			
			SPAposition pdef = point->coords();
			sprintf(text,"Pos: X:%g Y:%g Z:%g",pdef.x(), pdef.y(), pdef.z());
			m_infolist.AddString(indent + text);
		}

	}
	else if( eclass == EDGE_TYPE )
	{
		info+="Edge";
		m_infolist.AddString(info);
		double precision;
		precision = ((EDGE*)entity)->get_tolerance();
		sprintf(text,"Precision: %g",precision);
		m_infolist.AddString(H_TEXT(text));
	}
	else if( eclass == FACE_TYPE )
	{
		info+="Face";
		m_infolist.AddString(info);
		int nloops;
		ENTITY_LIST loops;
		outcome o = api_get_loops( entity, loops );
		CHECK_OUTCOME(o);
		nloops = loops.iteration_count();
		sprintf(text,"Number of Loops: %d",nloops);
		m_infolist.AddString(H_TEXT(text));
	}
	else if(  eclass == BODY_TYPE )
	{
		info+="Body";
		m_infolist.AddString(info);
		if( is_wire_body( entity ) == TRUE )
		{
			info = "Type:";
			info+="Wire Body";
			m_infolist.AddString(info);
		}
		else if( is_solid_body( entity ) == TRUE )
		{
			// All sheet & solid bodies are considered solids in ACIS (8.0) - so let's call this 
			// just a "Body". 
			info = "Type:";
			info+="Body";
			m_infolist.AddString(info);
		}
	}
	else if(  eclass == SHELL_TYPE )
	{
		info+="Shell";
		m_infolist.AddString(info);
	}

}

bool CASTopolBrowserDlg::get_model_refs_path_for_item(HTREEITEM item, entity_handle_list& model_refs_path) 
{
	while( item != NULL )
	{
		entity_handle* eh = NULL;
		ENTITY* ent = (ENTITY*) m_topol_tree.GetItemData(item);
		if(ent && (ent->identity() == ASM_MODEL_REF_TYPE))
			model_refs_path.add(ent->handle());

		item = m_topol_tree.GetParentItem(item);
	}

	model_refs_path.reverse();
	return true;
}

//this function is called whenever a selection is changed in the tree control
//this could be the result of a selection/deselection in the tree control or in the view 
void CASTopolBrowserDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
  	NM_TREEVIEW* pNMTreeView	= (NM_TREEVIEW*)pNMHDR;
  	TVITEM itemnew				= pNMTreeView->itemNew;
  	TVITEM itemold				= pNMTreeView->itemOld;
	ENTITY* entity				= (ENTITY*)itemnew.lParam;
	ENTITY* entity_old			= (ENTITY*)itemold.lParam;;
	int eclass, eclass_old, save_select_level;

	if( entity_old )
		eclass_old = entity_old->identity();

	HSAcisSelectionSet* selection = (HSAcisSelectionSet *)m_pHView->GetSelection();

	if (!entity)
	    return;

	eclass = entity->identity();
	if (eclass == FACE_TYPE && !m_facevisibility)
 	    return;
 	    
	//we are only updating the selection list for entities that HOOPS knows about
	if ( eclass == VERTEX_TYPE || eclass == EDGE_TYPE || eclass == FACE_TYPE || eclass == BODY_TYPE )
	{	
 		if (!m_bItemSelected)		//this flag indicates that the selection event came 
		{							//directly from the tree control
			save_select_level = selection->GetSelectLevel();
			selection->SetSelectLevel(eclass);
 			if (!(GetAsyncKeyState(VK_SHIFT) & 32768))		
			{
				// set appropriate selection levels before selection/deselection
				if(entity_old)
					selection->SetSelectLevel(eclass_old);
 				selection->DeSelectAll();

				selection->SetSelectLevel(eclass);
		  		selection->Select(entity);	
			}
			else
			{
		 		if (!CheckSelection(entity))
			  		selection->Select(entity);	
				else
			  		selection->DeSelectEntity(entity);	
			}
			selection->SetSelectLevel(save_select_level);

			if (m_bAlwaysZoom)
 		 			m_parent->PostMessage(WM_COMMAND,ID_ZOOM_TO_SELECTION,0);
			else
				m_pHView->Update();
		}
	}
	else if ( eclass == ASM_ASSEMBLY_TYPE || eclass == ASM_MODEL_REF_TYPE )
	{	
		if (!m_bItemSelected)		//this flag indicates that the selection event came 
		{							//directly from the tree control
			entity_handle_list model_refs;
			component_handle* comp_handle;

			get_model_refs_path_for_item(itemnew.hItem, model_refs);
			CHECK_OUTCOME(asmi_model_get_component_handle(model_refs, comp_handle));

			save_select_level = selection->GetSelectLevel();
			selection->SetSelectLevel(eclass);
			if (!(GetAsyncKeyState(VK_SHIFT) & 32768))		
			{
				// set appropriate selection levels before selection/deselection
				if(entity_old)
					selection->SetSelectLevel(eclass_old);
				selection->DeSelectAll();

				selection->SetSelectLevel(eclass);
				selection->Select(comp_handle);
			}
			else
			{
				if (!selection->IsSelected(comp_handle))
					selection->Select(comp_handle);	
				else
					selection->DeSelectComponent(comp_handle);	
			}
			selection->SetSelectLevel(save_select_level);

			if (m_bAlwaysZoom)
				m_parent->PostMessage(WM_COMMAND,ID_ZOOM_TO_SELECTION,0);
			else
				m_pHView->Update();

		}
	}

	m_bItemSelected = false;

 	
	ShowSelectedItems();
 
	UpdateInfoWindow(entity);  

 	*pResult = 0;
}


	
//this function fills a subtree of the tree control with all it's items
void CASTopolBrowserDlg::FillItems(ENTITY* entity, HTREEITEM item)
{				
	UINT state = m_topol_tree.GetItemState(item,TVIS_EXPANDEDONCE);
	
	outcome o;
	if (!(state & TVIS_EXPANDEDONCE))
	{
		if (!entity)
		    return;
		int eclass;
		CString info = "Class:";
		eclass = entity->identity();
		
		if( eclass == FACE_TYPE )
		{
			int numedges = 0;
			ENTITY_LIST edges;
			o = api_get_edges ( entity, edges );
			numedges = edges.iteration_count();
			CHECK_OUTCOME(o);

			for (int edgenum=0; edgenum < numedges; edgenum++)
				HTREEITEM edgeitem = InsertItemInTree(edges[edgenum],"Edge:",item);
		}					
		else if( eclass == EDGE_TYPE )
		{
			int numvertices = 0;
			ENTITY_LIST vertices;
			o = api_get_vertices( entity, vertices );
			CHECK_OUTCOME(o);
			
			for( int vertexnum = 0; vertexnum < 2; vertexnum++ )
			{
				if( vertices[vertexnum] )
					HTREEITEM vertexitem = InsertItemInTree(vertices[vertexnum],"Vertex:",item);
			}
	 
		}
		else if(  eclass == BODY_TYPE )
		{
			int numshells = 0;
			ENTITY_LIST shells;
			o = api_get_shells( entity, shells);
			numshells = shells.iteration_count();
			CHECK_OUTCOME(o);
			
			for (int shellnum=0;shellnum<numshells;shellnum++)
				HTREEITEM shellitem = InsertItemInTree(shells[shellnum],"Shell:",item);
		}
		else if(  eclass == SHELL_TYPE )
		{
			int numfaces;
			ENTITY_LIST faces;
			o = api_get_faces( entity, faces);
			numfaces = faces.iteration_count();
			CHECK_OUTCOME(o);
			for (int facenum=0;facenum<numfaces;facenum++)
				HTREEITEM faceitem = InsertItemInTree(faces[facenum],"Face:",item);
		}
		else if( eclass == ASM_ASSEMBLY_TYPE )
		{
			ASM_ASSEMBLY* pasm_assembly = (ASM_ASSEMBLY*)entity;
			asm_model* owning_model;
			api_asm_assembly_get_owning_model(pasm_assembly, owning_model);
			FillItems(owning_model, item);
		}
		else if( eclass == ASM_MODEL_REF_TYPE )
		{
			ASM_MODEL_REF* model_ref = (ASM_MODEL_REF*) entity;
			entity_handle* model_ref_handle = model_ref->handle();
			asm_model* owning_model = 0;
			asmi_model_ref_get_model(model_ref_handle, owning_model);
			FillItems(owning_model, item);
		}
	}
}

void CASTopolBrowserDlg::FillItems(asm_model* p_asm_model, HTREEITEM item)
{
	if(!p_asm_model)
		return;

	// TODO: use component apis
	entity_handle_list model_refs_path;
	get_model_refs_path_for_item(item, model_refs_path);

	// insert sub-assemblies
	entity_handle_list model_ref_handles;
	asmi_model_get_model_refs(p_asm_model, model_ref_handles);
	for ( entity_handle* handle = model_ref_handles.first(); handle != NULL; handle = model_ref_handles.next() )
	{
		model_refs_path.add(handle);
		component_handle* p_comp_handle;
		CHECK_OUTCOME(asmi_model_get_component_handle(model_refs_path, p_comp_handle));

		char comp_label[MVO_BUFFER_SIZE];

		const wchar_t* comp_name = NULL;
		CHECK_OUTCOME(asmi_component_find_name(p_comp_handle, comp_name));

		if(comp_name)
		{
			sprintf(comp_label, "%s:",H_ASCII_TEXT(comp_name));
		}
		else
		{
			if(has_assembly(p_asm_model) == TRUE)
				strcpy(comp_label,"Model(Asm):");
			else
				strcpy(comp_label,"Model(Part):");
		}
		/* TODO: Handle the case where there is no component name in the file */

		ASM_MODEL_REF* model_ref = (ASM_MODEL_REF*) handle->entity_ptr();
		InsertItemInTree((ENTITY*)model_ref, comp_label, item);
		model_refs_path.remove(handle);
	}

	entity_handle_list part_ents;
	asmi_model_get_entities( p_asm_model, part_ents );
	for (entity_handle* ent_handle = part_ents.first(); 
		ent_handle != NULL; ent_handle = part_ents.next())
	{
		ENTITY* ent = ent_handle->entity_ptr();
		if(ent)
			InsertItemInTree(ent, ent->type_name(), item);
	}
}

void CASTopolBrowserDlg::InsertComponents(asm_model *pAsmModel, HTREEITEM parentNode)
{
	// Get the components of the assembly
	// Request only immediate components, in order to populate the tree
	AcisOptions* opts = NULL;
	asm_get_options gopts;
	gopts.request = ASM_IMMEDIATE;

	logical bStatus = FALSE;
	API_BEGIN
		component_handle_list ohComps_list;
	result = asmi_model_get_components( pAsmModel, ohComps_list, &gopts, opts );

	if ( bStatus = result.ok() )
	{
		// generate output list
		if (ohComps_list.iteration_count())
		{
			int idx(0);
			wchar_t buff[56];
			for (component_handle* oh = ohComps_list.first(); oh; oh = ohComps_list.next())
			{
				// We could map every item handle to every occurrence handle
				// Whenever it is selected with could go back and do something with
				// the occurrence handle

				asm_model* comp_model = NULL;
				logical is_modified = FALSE;
				result = asmi_component_get_unmodified_model( oh, comp_model, is_modified, opts );

				if ( bStatus = result.ok() )
				{
					logical isAssy = FALSE;
					result = asmi_model_has_assembly( comp_model, isAssy, opts );

					if ( isAssy )
					{
						swprintf(buff, L"sub-assembly %x <%x>", oh, comp_model);
						//HTREEITEM hItem = mTreeControl.InsertItem(buff, ILI_ASSEMBLY, ILI_ASSEMBLY, parentNode);
						HTREEITEM hItem = m_topol_tree.InsertItem(buff, parentNode);
						InsertComponents(comp_model, hItem );
					}
					else
					{
						swprintf(buff, L"part %x <%x>", oh, comp_model);
						//mTreeControl.InsertItem(buff, ILI_PART, ILI_PART, parentNode);
						m_topol_tree.InsertItem(buff, parentNode);
					}
				}
			}           
		}
	}
	API_END
}


void CASTopolBrowserDlg::OnAnnotate() 
{
	assert(!"Not yet implemented");
}


void CASTopolBrowserDlg::OnFacevisibility() 
{
	HSSelectionSet* selection;
	selection = (HSSelectionSet *)m_pHView->GetSelection();			
	selection->DeSelectAll();
	
	CBusyDlg *	busy = new CBusyDlg();
	busy->Create(IDD_BUSYDLG);
	busy->ShowWindow(SW_SHOW); 
	UpdateData(TRUE);
	((HSolidView *)m_pHView)->SetOptimizations(!m_pHView->GetOptimizations());	
	delete busy;

	m_pHView->Update();
	ShowSelectedItems();			
}

//this function updates the selected item display (bold) in the tree control for the visible
//elements
//needs to be called whenever the selection has changed
//this is the main cause for speed problems with a large number of selections
//fix: have to think of a way to speed up the selection process...
void CASTopolBrowserDlg::ShowSelectedItems()
{
	HSAcisSelectionSet *selection;
	int vismax = 25;
	selection = (HSAcisSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSolidListSize();
	HTREEITEM item = m_topol_tree.GetFirstVisibleItem();
	int viscount=0;
	bool somethingFound = false;
	while (item)
	{
		viscount++;
		m_topol_tree.SetItemState(item,0,TVIS_BOLD);
		ENTITY* pEntity = (ENTITY*) m_topol_tree.GetItemData(item);

		bool is_selected = false;
		if(pEntity)
		{
			if( pEntity->identity() == ASM_MODEL_REF_TYPE )
			{
				// this is actually a component, get the handle
				entity_handle_list model_refs;
				component_handle* comp_handle;

				get_model_refs_path_for_item(item, model_refs);
				CHECK_OUTCOME(asmi_model_get_component_handle(model_refs, comp_handle));

				is_selected = selection->IsSelected(comp_handle);
			}
			else
				is_selected = selection->IsSelected(pEntity);
		}

		if( is_selected == true)
		{
			somethingFound = true;
			m_topol_tree.SetItemState(item,TVIS_BOLD,TVIS_BOLD);
		}

		//the visible items are all items from the top visible down to the last item on the list 
		//even if it is outside the window. That is why we brake processing at 25 elements
		if (viscount>25)
			break;
		item = m_topol_tree.GetNextVisibleItem(item);
	}
	if (!somethingFound)
		m_topol_tree.SelectItem(0);
}

#endif   // ifdef ACIS
   

 

 
 
