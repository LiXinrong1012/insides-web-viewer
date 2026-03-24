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
// $Header: /files/homes/master/cvs/hoops_master/parasolidpartviewer/PSTopolBrowserDlg.cpp,v 1.25 2009-08-20 19:35:26 nathan Exp $
//

// TopolBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HSInclude.h"
#include "hsselectionset.h"
#include "HSParasolidSelectionSet.h"
#include "annotatedlg.h"
#include "busydlg.h"
#include "PSTopolBrowserDlg.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef PARASOLID
#include "hp_bridge.h"
#endif
#include "csolidhoopsapp.h"
#include "csolidhoopsfrm.h"
 extern CSolidHoopsApp theApp;
 


//this function inserts a new item into the tree control with it's name (if available) and the tagid
HTREEITEM CPSTopolBrowserDlg::InsertItemInTree ( PK_ENTITY_t entity, const char *basetext, HTREEITEM position ) {
	char text[512];	
	
	TVINSERTSTRUCT is;
	is.hParent = position;
	is.hInsertAfter = TVI_LAST;
	is.item.mask = TVIF_CHILDREN | TVIF_TEXT;
	
	PK_CLASS_t eclass;
	if (entity)
	    PK_ENTITY_ask_class(entity, &eclass);
	else 
		eclass = 0;
	switch (eclass) {
	case PK_CLASS_vertex:		//vertices have no parents
	case PK_CLASS_instance:
		is.item.cChildren = 0;			
		break;
	case PK_CLASS_face:			//faces might have no edges
		int n_edges;
		PK_FACE_ask_edges(entity, &n_edges, 0);
		if (n_edges)
			is.item.cChildren = 1;	
		else
			is.item.cChildren = 0;	
		break;
	case PK_CLASS_edge:			//edges might have no vertices
		PK_VERTEX_t vertices[2];
		PK_EDGE_ask_vertices(entity, vertices);
		if (vertices[0] == PK_ENTITY_null)
			is.item.cChildren = 0;	
		else
			is.item.cChildren = 1;	
		break;
	default:
		is.item.cChildren = 1;	
	}

	if (eclass)
	    sprintf(text, "%s%d", basetext, entity);
	else
	    sprintf(text, "%s", basetext);

	if ( (m_name_attdef != PK_ENTITY_null) && eclass ) {
		int n_attr;
		PK_ATTRIB_t *attr;
		PK_ENTITY_ask_attribs(entity, m_name_attdef, &n_attr, &attr);
		if (n_attr) {
			char *descr;
			PK_ATTRIB_ask_string(attr[0], 0, &descr);
			sprintf(text, "%s%s", basetext, descr);
			PK_MEMORY_free(attr);
			PK_MEMORY_free(descr);	 
		}
	}			
	
	H_TEXT label_text(text);
	is.item.pszText = (LPTSTR)(const TCHAR*)label_text; // pszText is not const - even though it is meant to be
	HTREEITEM item = m_topol_tree.InsertItem(&is);

 	m_topol_tree.SetItemData(item, (DWORD)entity);
 	if (eclass == PK_CLASS_body)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(8), TVIS_STATEIMAGEMASK );
	else if (eclass == PK_CLASS_face)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(10), TVIS_STATEIMAGEMASK );
	else if (eclass == PK_CLASS_edge)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(11), TVIS_STATEIMAGEMASK );
	else if (eclass == PK_CLASS_vertex)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(12), TVIS_STATEIMAGEMASK );
	else if (eclass == PK_CLASS_shell)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(9), TVIS_STATEIMAGEMASK );
	else if (eclass == PK_CLASS_assembly)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(14), TVIS_STATEIMAGEMASK );
	else if (eclass == PK_CLASS_instance)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(8), TVIS_STATEIMAGEMASK );
  		
	return item;
}


//automatically highlights a selection and jumps to the right location in the tree
bool CPSTopolBrowserDlg::HighlightSelection () { 
	if (!GetSafeHwnd())
		return false;

	PK_ENTITY_t ents[10];
	HSSelectionSet *selection;

 	selection = (HSSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSolidListSize();
	if (!ssize) {
		ShowSelectedItems();
		return false;
	}


//it would be nice if we could always expand all selected entities but this can take too long 
	int start;
	if (ssize > 200)
		start = ssize - 200;
	else
		start = 0;

	int j;
	for ( j = start ; j < ssize ; j++ ) {
		//we query the hierarchy (body-face-edge) for the selection that we want to expand
 		int depth = 0;
		PK_ENTITY_t entity = selection->GetAtSolidEntity(j);
		PK_CLASS_t eclass;
		PK_INSTANCE_sf_t in_sf;
		PK_BODY_t body;
		PK_SHELL_t shells[2];
		PK_FACE_t *faces;
		PK_EDGE_t *edges;
		int n_faces, n_edges;

		PK_ENTITY_ask_class(entity, &eclass);
		switch (eclass) {
		case PK_CLASS_instance:
			depth = 1;
			ents[1] = entity;
			PK_INSTANCE_ask(entity, &in_sf);
			ents[0] = in_sf.assembly;
			break;
		case PK_CLASS_body:
		case PK_CLASS_assembly:
			depth = 0;
			ents[0] = entity;
			break;
		case PK_CLASS_face:
			depth = 2;
			ents[2] = entity;
			PK_FACE_ask_shells(entity, shells);
			if (shells[0])
				ents[1] = shells[0];
			PK_SHELL_ask_body(shells[0], &body);
			ents[0] = body;
			break;
		case PK_CLASS_edge:
			depth = 3;
			ents[3] = entity;
			PK_EDGE_ask_faces(entity, &n_faces, &faces);
			if (n_faces)
				ents[2] = faces[0];
			PK_FACE_ask_shells(faces[0], shells);
			if (shells[0])
				ents[1] = shells[0];
			PK_SHELL_ask_body(shells[0], &body);
			ents[0] = body;
			PK_MEMORY_free(faces);
			break;
		case PK_CLASS_vertex:
			depth = 3;
			ents[3] = entity;
			PK_VERTEX_ask_faces(entity, &n_faces, &faces);
			if (n_faces)
				ents[2] = faces[0];
			PK_FACE_ask_edges(faces[0], &n_edges, &edges);
			if (n_edges) {
				bool found_edge = false;
				PK_VERTEX_t vertices[2];
				int i;
				for ( i = 0 ; i < n_edges ; i++ ) {
					PK_EDGE_ask_vertices(edges[i], vertices);
					if ( vertices[0] == entity || vertices[1] == entity ) {
						found_edge = true;
						break;
					}
				}
				if (found_edge) {
					depth = 4;
					ents[4] = entity;
					ents[3] = edges[i];
					ents[2] = faces[0];
				}
			}
			PK_MEMORY_free(edges);
			PK_FACE_ask_shells(faces[0], shells);
			if (shells[0])
				ents[1] = shells[0];
			PK_SHELL_ask_body(shells[0], &body);
			ents[0] = body;
			PK_MEMORY_free(faces);
			break;
		}

		
		//now we look through the tree starting from the root item and expand the subtrees
		//as necessary until the selected item is reached
		HTREEITEM aitem = m_rootitem;
		PK_ENTITY_t result = m_topol_tree.GetItemData(aitem);
		int i;
		for ( i = 0 ; i <= depth ; i++ ) {			
			while ( result != ents[i] ) {	
				aitem = m_topol_tree.GetNextSiblingItem(aitem);
				result = m_topol_tree.GetItemData(aitem);
			}
			if (i == depth) {
				if (j == ssize - 1) {
					m_bItemSelected = true;
					m_topol_tree.SelectItem(aitem);
				}
			}			
			else {				 
				UINT state = m_topol_tree.GetItemState(aitem, TVIS_EXPANDEDONCE);
				if (!(state & TVIS_EXPANDEDONCE))
					m_topol_tree.Expand(aitem, TVE_EXPAND);

				m_topol_tree.SetItemState(aitem, TVIS_EXPANDEDONCE, TVIS_EXPANDEDONCE);
 				
				aitem = m_topol_tree.GetChildItem(aitem);
				result = m_topol_tree.GetItemData(aitem);
			}
		}	
	}
	ShowSelectedItems();

 	return true;

} 
	

	

BOOL CPSTopolBrowserDlg::OnInitDialog() 
{
	m_topol_tree.SubclassDlgItem(IDC_TREE1,this);
	
 	CTopolBrowserDlg::OnInitDialog();

	BuildTopolTree();
	m_TopologyBrowserSwitch.SetState(true);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


bool CPSTopolBrowserDlg::BuildTopolTree () {
  	CString title = ((CView *)m_parent)->GetDocument()->GetTitle();
 	SetWindowText("Topology Browser - " + title);
	m_dialogactive = true;	

	
	PK_ATTDEF_find("SDL/TYSA_NAME", &m_name_attdef);
	int tabs[5] = { 5, 10, 15, 20, 25 };
	m_infolist.SetTabStops(4, tabs);
	m_TopInfoList.SetTabStops(4, tabs);
	
	HSolidModel *model = (HSolidModel *)(m_pHView->GetModel());
	PK_PARTITION_set_current(model->GetPartition());

	PK_BODY_t *bodies;
	int n_bodies;
	PK_ERROR_t err = PK_PARTITION_ask_bodies(model->GetPartition(), &n_bodies, &bodies);
	
	PK_ASSEMBLY_t *assemblies;
	int n_assemblies;

	PK_PARTITION_ask_assemblies(model->GetPartition(), &n_assemblies, &assemblies);
	int total_num_faces = 0;

	HTREEITEM top_item = InsertItemInTree(0, H_ASCII_TEXT(title), TVI_ROOT);
	int body_num;
	for ( body_num = 0 ; body_num < n_bodies ; body_num++ ) {
		int n_faces;
		PK_BODY_ask_faces(bodies[body_num], &n_faces, 0);
		total_num_faces += n_faces;

		bool bInsert = true;
		if (!CAppSettings::bFlattenAssemblies) {
			int i;
			for ( i = 0 ; i < n_assemblies ; i++ ) {
				int n_instances;
 				PK_INSTANCE_t *instances;
 				PK_ASSEMBLY_ask_instances(assemblies[i], &n_instances, &instances);
				int j;
				for ( j = 0 ; j < n_instances ; j++ ) {
					PK_INSTANCE_sf_t in_sf;
					PK_INSTANCE_ask(instances[j], &in_sf);
					if (in_sf.part == bodies[i])
						bInsert = false;
				}
				PK_MEMORY_free(instances);
			}
		}

		HTREEITEM body_item;
		if (bInsert)
			body_item = InsertItemInTree(bodies[body_num], "Body:", top_item);

		if (body_num == 0)
			m_rootitem = body_item;
	}

	int asm_num;
 	for ( asm_num = 0 ; asm_num < n_assemblies ; asm_num++ )
 		HTREEITEM body_item = InsertItemInTree(assemblies[asm_num], "Assembly:", top_item);
 
	PK_MEMORY_free(assemblies);	
	PK_MEMORY_free(bodies);	
	
	HighlightSelection();

	m_TopInfoList.ResetContent();
	CString indent = "\t";
	
	m_TopInfoList.AddString(title + " contains:");
	char text[128];
	if (n_bodies > 1)
		sprintf(text, "%d bodies/instances", n_bodies);
	else
		sprintf(text, "%d body/instance", n_bodies); 
 	m_TopInfoList.AddString(indent + text);
	sprintf(text, "%d faces (total)", total_num_faces);
 	m_TopInfoList.AddString(indent + text);

	return true;
}
 

//update the listbox with various information on the selected entities
void CPSTopolBrowserDlg::UpdateInfoWindow(PK_ENTITY_t entity)
{
    m_infolist.ResetContent();

    if(!entity)
		return;

	PK_CLASS_t eclass;
	CString info = "Class:";
	PK_ENTITY_ask_class(entity,&eclass);
	CString indent = "\t";
	char text[128];
	switch(eclass)
	{
	case PK_CLASS_vertex:
		{
			info+="Vertex";
			m_infolist.AddString(info);
			
			
			PK_POINT_t point;
			PK_VERTEX_ask_point(entity,&point);
			if (point)
			{
			
				sprintf(text,"Geom:%d",point);
				m_infolist.AddString(indent + text);
				
				PK_POINT_sf_t pdef;
					PK_POINT_ask(point,&pdef);
				sprintf(text,"Pos: X:%g Y:%g Z:%g",pdef.position.coord[0],pdef.position.coord[1],
					pdef.position.coord[2]);
				m_infolist.AddString(indent + text);

			}
		}		
		break;
	case PK_CLASS_instance:
		{
			info+="Instance";
			m_infolist.AddString(info);
			PK_INSTANCE_sf_t in_sf;
			PK_INSTANCE_ask(entity,&in_sf);

			PK_CLASS_t eclass;
			PK_ENTITY_ask_class(in_sf.part,&eclass);
 			if (eclass == PK_CLASS_body)
				sprintf(text," References Body %d",in_sf.part);
			else
				sprintf(text,"References Assembly %d",in_sf.part);
			m_infolist.AddString(indent + text);
		}	
		break;
	case PK_CLASS_edge:
		info+="Edge";
		m_infolist.AddString(info);
		double precision;
		PK_EDGE_ask_precision(entity,&precision);
		sprintf(text,"Precision: %g",precision);
		m_infolist.AddString(H_TEXT(text));		
		break;
	case PK_CLASS_face:
		info+="Face";
		m_infolist.AddString(info);
		int nloops;
		PK_FACE_ask_loops(entity, &nloops,0);
		sprintf(text,"Number of Loops: %d",nloops);
		m_infolist.AddString(H_TEXT(text));		
		break;
	case PK_CLASS_body:
		info+="Body";
		m_infolist.AddString(info);
		PK_BODY_type_t btype;
		PK_BODY_ask_type(entity,&btype);
		info = "Type:";
		switch (btype)
		{
		case PK_BODY_type_sheet_c:
			info+="Sheet Body";
			break;
		case PK_BODY_type_solid_c:
			info+="Solid Body";
			break;
		}
		m_infolist.AddString(info);
		break;
	case PK_CLASS_shell:
		info+="Shell";
		m_infolist.AddString(info);

		break;
	}

	int n_atts;
	PK_ATTRIB_t *at = 0;
  	PK_ERROR_t err = PK_ENTITY_ask_attribs(entity, PK_ENTITY_null, &n_atts, &at);
 	sprintf(text,"Attributes:%d",n_atts);
	m_infolist.AddString(H_TEXT(text));
 	for (int i=0;i<n_atts;i++)
	{
		PK_ATTDEF_t attdef;
		PK_ATTRIB_ask_attdef(at[i],&attdef);
		PK_ATTDEF_sf_t attsf;
		PK_ATTDEF_ask(attdef,&attsf);
		m_infolist.AddString(indent + attsf.name);
		if (strcmp(attsf.name,"SDL/TYSA_NAME")==0)
		{
			char *text;
			PK_ATTRIB_ask_string(at[i],0,&text);
			m_infolist.AddString(indent+indent+text);
			PK_MEMORY_free(text);
		}
		if (strcmp(attsf.name,"SDL/TYSA_COLOUR")==0)
		{

			int nDoubles;
 			double* data;
			PK_ATTRIB_ask_doubles( at[i], 0, &nDoubles, &data );
			if (nDoubles)
			{
 				
			char text[255];
			sprintf(text,"R:%1.2g G:%1.2g B:%1.2g",data[0],data[1],data[2]);
 			m_infolist.AddString(indent+indent+text);
			PK_MEMORY_free( data );
			}
		}
		PK_MEMORY_free(attsf.name);
		PK_MEMORY_free(attsf.owner_types);
		PK_MEMORY_free(attsf.field_types);
	}
		
	if (at)
		PK_MEMORY_free(at);	
}



//this function is called whenever a selection is changed in the tree control
//this could be the result of a selection/deselection in the tree control or in the view 
void CPSTopolBrowserDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  	TVITEM itemnew = pNMTreeView->itemNew;
	PK_ENTITY_t entity = (PK_ENTITY_t)itemnew.lParam;
	HSSelectionSet* selection;
	selection = (HSParasolidSelectionSet *)m_pHView->GetSelection();
 
	PK_CLASS_t eclass;
	PK_ENTITY_ask_class(entity,&eclass);
	
	if (eclass == PK_CLASS_face && !m_facevisibility)
 	    return;

 
	//we are only updating the selection list for entities that HOOPS knows about
	if ( eclass == PK_CLASS_assembly || eclass == PK_CLASS_edge || eclass == PK_CLASS_face || 
		 eclass == PK_CLASS_body || eclass == PK_CLASS_instance || eclass == PK_CLASS_vertex )
	{	
 		if (!m_bItemSelected)		//this flag indicates that the selection event came 
		{							//directly from the tree control
			selection = (HSSelectionSet *)m_pHView->GetSelection();
 			if (!(GetAsyncKeyState(VK_SHIFT) & 32768))		
			{
 				selection->DeSelectAll();
		  		selection->Select(entity);	
			}
			else
			{
		 		if (!CheckSelection(entity))
			  		selection->Select(entity);	
				else
			  		selection->DeSelectEntity(entity);	
			}
			if (m_bAlwaysZoom)
 		 		m_parent->PostMessage(WM_COMMAND, ID_ZOOM_TO_SELECTION, 0);

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
void CPSTopolBrowserDlg::FillItems(PK_ENTITY_t entity,HTREEITEM item)
{				
	UINT state = m_topol_tree.GetItemState(item,TVIS_EXPANDEDONCE);
	
	if (!(state & TVIS_EXPANDEDONCE))
	{

		PK_CLASS_t eclass;
		CString info = "Class:";
		PK_ENTITY_ask_class(entity,&eclass);
		
		switch(eclass)
		{
		case PK_CLASS_face:
		{
			int numedges;
			PK_EDGE_t *edges;
			PK_FACE_ask_edges(entity,&numedges,&edges);
			
			for (int edgenum=0;edgenum<numedges;edgenum++)
				HTREEITEM edgeitem = InsertItemInTree(edges[edgenum],"Edge:",item);
			PK_MEMORY_free(edges);
		}					
			break;
		case PK_CLASS_edge:
		{
 			PK_VERTEX_t vertices[2];
			PK_EDGE_ask_vertices(entity,vertices);
			
			for (int vertexnum=0;vertexnum<2;vertexnum++)
			{
				if (vertices[vertexnum]!=PK_ENTITY_null)
					HTREEITEM vertexitem = InsertItemInTree(vertices[vertexnum],"Vertex:",item);
			}
	 
		}
			break;
		case PK_CLASS_body:
			
			{
				int numshells;
				PK_SHELL_t *shells;
				PK_BODY_ask_shells(entity,&numshells,&shells);
				
				for (int shellnum=0;shellnum<numshells;shellnum++)
					HTREEITEM shellitem = InsertItemInTree(shells[shellnum],"Shell:",item);
				PK_MEMORY_free(shells);
			}
			break;
		case PK_CLASS_assembly:
			
			{
				int numinstances;
				PK_INSTANCE_t *instances;
				PK_ASSEMBLY_ask_instances(entity,&numinstances,&instances);
				
				for (int instancenum=0;instancenum<numinstances;instancenum++)
					HTREEITEM instanceitem = InsertItemInTree(instances[instancenum],"Instance:",item);
				PK_MEMORY_free(instances);
			}
			break;
		case PK_CLASS_shell:
			{
				int numfaces;
				PK_FACE_t *faces;
				PK_LOGICAL_t *orientation;
				PK_SHELL_ask_oriented_faces(entity,&numfaces,&faces,&orientation);
				for (int facenum=0;facenum<numfaces;facenum++)
					HTREEITEM faceitem = InsertItemInTree(faces[facenum],"Face:",item);
				PK_MEMORY_free(faces);
				PK_MEMORY_free(orientation);
			}
			break;
		}
	}
}


void CPSTopolBrowserDlg::OnAnnotate() 
{
 
	HTREEITEM selection = m_topol_tree.GetSelectedItem();
 	PK_ENTITY_t entity = (PK_ENTITY_t)m_topol_tree.GetItemData(selection) ;
	char *descr = 0;

	if (m_name_attdef!=PK_ENTITY_null)
		{
			int n_attr;
			PK_ATTRIB_t *attr;
			PK_ENTITY_ask_attribs(entity,m_name_attdef,&n_attr,&attr);
			if (n_attr)
			{
 				PK_ATTRIB_ask_string(attr[0],0,&descr);
  				PK_MEMORY_free(attr);
			
			 
			}
					
	CAnnotateDlg dlg(0,descr);
	 
	if (dlg.DoModal()==IDOK)
	{
		PK_ATTRIB_t attr;
		PK_ATTRIB_create_empty(entity,m_name_attdef,&attr);
		PK_ERROR_t err=PK_ATTRIB_set_string(attr, 0, H_ASCII_TEXT(dlg.m_annotation));
		UpdateInfoWindow(entity);
		PK_CLASS_t eclass;
		PK_ENTITY_ask_class(entity,&eclass);
 		
		CString itext;
		switch(eclass)
		{
		case PK_CLASS_body:
			itext = "Body:";
			break;
		case PK_CLASS_face:
			itext = "Face:";
			break;
		case PK_CLASS_shell:
			itext = "Shell:";
			break;
		case PK_CLASS_edge:
			itext = "Edge:";
			break;
		case PK_CLASS_vertex:
			itext = "Vertex:";
			break;
		}
		itext += dlg.m_annotation;			
			m_topol_tree.SetItemText(selection,itext);
	 
	}
	if (descr)	
		PK_MEMORY_free(descr);
	}
	
}

 
void CPSTopolBrowserDlg::OnFacevisibility() 
{
		
		CBusyDlg *	busy = new CBusyDlg();
 		busy->Create(IDD_BUSYDLG);
		busy->ShowWindow(SW_SHOW); 
		UpdateData(TRUE);
		((HSolidView *)m_pHView)->SetOptimizations(!m_pHView->GetOptimizations());	
		delete busy;
 
	 	if (m_facevisibility)
		{
			HTREEITEM sel = m_topol_tree.GetSelectedItem();
			if(sel)
			{
				PK_ENTITY_t entity = (PK_ENTITY_t)m_topol_tree.GetItemData(sel);
				PK_CLASS_t eclass;
				PK_ENTITY_ask_class(entity,&eclass);
				if (eclass == PK_CLASS_face)
				{
					HSSelectionSet* selection;
 					selection = (HSSelectionSet *)m_pHView->GetSelection();			
					selection->DeSelectAll();
					selection->Select(entity);	
				}
			}
		}
		m_pHView->Update();
		ShowSelectedItems();			
 	
}