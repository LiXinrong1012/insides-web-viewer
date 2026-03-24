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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/PlainTopolBrowserDlg.cpp,v 1.28 2007-10-16 18:59:57 stage Exp $
//

// TopolBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "HSInclude.h"

#include "hsselectionset.h"
#include "HSPlainSelectionSet.h"
#include "annotatedlg.h"
#include "busydlg.h"

#include "csolidhoopsfrm.h"
#include "csolidhoopsapp.h"
extern CSolidHoopsApp theApp;

#include "plaintopolbrowserdlg.h"
#include "CBinaryFileToolkit.h"


#include "HSolidView.h"
#include "HSolidModel.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CPlainTopolBrowserDlg, CTopolBrowserDlg)
	//{{AFX_MSG_MAP(CPlainTopolBrowserDlg)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, OnItemexpandingTree1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//called whenever the expands a subtree for the first time
void CPlainTopolBrowserDlg::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
 	TVITEM itemnew = pNMTreeView->itemNew;

	long entity = (long)itemnew.lParam;
	UINT state = m_topol_tree.GetItemState(itemnew.hItem,TVIS_EXPANDEDONCE);
	FillItems(entity,itemnew.hItem);
	
	*pResult = 0;
}

 

//this function inserts a new item into the tree control with it's name (if available) and the tagid
HTREEITEM CPlainTopolBrowserDlg::InsertItemInTree(long entity,const char* basetext,HTREEITEM position)
{
	char text[MVO_BUFFER_SIZE];	
	
	TVINSERTSTRUCT is;
	is.hParent = position;
	is.hInsertAfter=TVI_LAST;
	is.item.mask=TVIF_CHILDREN | TVIF_TEXT;

	KERN_CLASS_TYPEDEF eclass;
	model->m_mi->ENTITY_ask_class(entity, eclass);

	if( eclass == KERN_VERTEX_TYPE )
		is.item.cChildren = 0;
#ifdef PARASOLID
	else if( eclass == PK_CLASS_instance )
		is.item.cChildren = 0;			
#endif // PARASOLID
	else if( eclass == KERN_FACE_TYPE )			//faces might have no edges
	{
		int numedges;
		model->m_mi->FACE_ask_edges(entity,&numedges,0);			
		if (numedges)
			is.item.cChildren = 1;	
		else
			is.item.cChildren = 0;	
	}
	else if( eclass == KERN_EDGE_TYPE )	//edges might have no vertices
		is.item.cChildren = 0;	
	else
		is.item.cChildren = 1;	

	sprintf(text,"%s%d",basetext,entity);

	H_TEXT label_text(text);
	is.item.pszText= (LPTSTR)(const TCHAR*)label_text; // pszText is not const - even though it is meant to be
	HTREEITEM item = m_topol_tree.InsertItem(&is);

 	m_topol_tree.SetItemData(item,(DWORD)entity);
	if (eclass == KERN_BODY_TYPE)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(8), TVIS_STATEIMAGEMASK );
	else if (eclass == KERN_FACE_TYPE)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(10), TVIS_STATEIMAGEMASK );
	else if (eclass == KERN_EDGE_TYPE)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(11), TVIS_STATEIMAGEMASK );
	else if (eclass == KERN_VERTEX_TYPE)
	    m_topol_tree.SetItemState(item, INDEXTOSTATEIMAGEMASK(12), TVIS_STATEIMAGEMASK );
  	
	return item;

}

//automatically highlights a selection and jumps to the right location in the tree
bool CPlainTopolBrowserDlg::HighlightSelection()
{ 
	if( !GetSafeHwnd() )
		return false;

	long ents[10];
	HSSelectionSet* selection;

 	selection = (HSSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSolidListSize();
	if (!ssize)
	{
		ShowSelectedItems();
		return false;
	}


//it would be nice if we could always expand all selected entities but this can take too long 
	int start;
	if (ssize>200)
		start=ssize-200;
	else
		start=0;

	for (int j=start;j<ssize;j++)
	{
		//we query the hierachy (body-face-edge) for the selection that we want to expand
 		int depth=0;
		long entity = selection->GetAtSolidEntity(j);
		KERN_CLASS_TYPEDEF eclass;
 		model->m_mi->ENTITY_ask_class(entity, eclass);

		if( eclass == KERN_BODY_TYPE )
		{
			depth=0;
			ents[0]=entity;
		}
#ifdef PARASOLID
		else if( eclass == PK_CLASS_assembly )
		{
			depth=0;
			ents[0]=entity;
		}
#endif // PARASOLID
		else if( eclass == KERN_FACE_TYPE )
		{
			depth=1;
			ents[1]=entity;
 			model->m_mi->FACE_ask_body(entity,&ents[0]);
		}
		else if( eclass == KERN_EDGE_TYPE )
		{
			depth=2;
			ents[2]=entity;
			long *faces;
			int numfaces;
			model->m_mi->EDGE_ask_faces(entity,&numfaces,&faces);

			if (numfaces)
				ents[1]=faces[0];

			model->m_mi->FACE_ask_body(faces[0],&ents[0]);
			delete faces;
		}
		
		//now we look through the tree starting from the root item and expand the subtrees
		//as necessary until the selected item is reached
		HTREEITEM aitem=m_rootitem;
		long result = m_topol_tree.GetItemData(aitem);
		for (int i=0;i<=depth;i++)
		{			
			while (result!=ents[i])
			{	
				aitem=m_topol_tree.GetNextSiblingItem(aitem);
				result = m_topol_tree.GetItemData(aitem);
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
				UINT state = m_topol_tree.GetItemState(aitem,TVIS_EXPANDEDONCE); 				
				if (!(state & TVIS_EXPANDEDONCE))
					m_topol_tree.Expand(aitem,TVE_EXPAND);

				m_topol_tree.SetItemState(aitem,TVIS_EXPANDEDONCE,TVIS_EXPANDEDONCE);
 				
				aitem = m_topol_tree.GetChildItem(aitem);
				result = m_topol_tree.GetItemData(aitem);
			}
			
		}	
	 
	}
	ShowSelectedItems();

 	return true;
} 
	

BOOL CPlainTopolBrowserDlg::OnInitDialog() 
{

	m_topol_tree.SubclassDlgItem(IDC_TREE1,this);
	
 	CTopolBrowserDlg::OnInitDialog();
	m_TopologyBrowserSwitch.SetState(true);

	BuildTopolTree();
 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}


 

//update the listbox with various information on the selected entities
void CPlainTopolBrowserDlg::UpdateInfoWindow(long entity)
{

	m_infolist.ResetContent();

	KERN_CLASS_TYPEDEF eclass;
	CString info = "Class:";
//	PK_ENTITY_ask_class(entity,&eclass);
	model->m_mi->ENTITY_ask_class(entity, eclass);

	CString indent = "\t";
//	char text[MVO_BUFFER_SIZE];
	if( eclass == KERN_EDGE_TYPE )
	{
		info+="Edge";
		m_infolist.AddString(info);
	}
	else if( eclass == KERN_FACE_TYPE )
	{
		info+="Face";
		m_infolist.AddString(info);
	}
	else if( eclass == KERN_BODY_TYPE )
	{
		info+="Body";
		m_infolist.AddString(info);
	}
}

//this function is called whenever a selection is changed in the tree control
//this could be the result of a selection/deselection in the tree control or in the view 
void CPlainTopolBrowserDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{

 	NM_TREEVIEW* pNMTreeView	= (NM_TREEVIEW*)pNMHDR;
  	TVITEM itemnew				= pNMTreeView->itemNew;
  	TVITEM itemold				= pNMTreeView->itemOld;
	long entity					= (long)itemnew.lParam;
	long entity_old				= (long)itemold.lParam;
	HSSelectionSet* selection	= (HSPlainSelectionSet *)m_pHView->GetSelection();
	KERN_CLASS_TYPEDEF eclass;
	KERN_CLASS_TYPEDEF eclass_old;
	KERN_CLASS_TYPEDEF save_select_level;
 
	if( entity_old )
		model->m_mi->ENTITY_ask_class(entity_old, eclass_old);

 
	model->m_mi->ENTITY_ask_class(entity, eclass);

	if (eclass == KERN_FACE_TYPE && !m_facevisibility)
 	    return;


	//we are only updating the selection list for entities that HOOPS knows about
#ifdef PARASOLID
	if (eclass==PK_CLASS_assembly || eclass==KERN_EDGE_TYPE || eclass==KERN_FACE_TYPE || eclass==KERN_BODY_TYPE || eclass == PK_CLASS_instance)
#endif // PARASOLID
#ifdef ACIS
	if (eclass==KERN_EDGE_TYPE || eclass==KERN_FACE_TYPE || eclass==KERN_BODY_TYPE)
#endif // ACIS
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
 
	m_bItemSelected = false;

 	
	ShowSelectedItems();
 
	UpdateInfoWindow(entity);  

 	*pResult = 0;

}

//this function fills a subtree of the tree control with all it's items
void CPlainTopolBrowserDlg::FillItems(long entity,HTREEITEM item)
{				
	UINT state = m_topol_tree.GetItemState(item,TVIS_EXPANDEDONCE);
	
	if (!(state & TVIS_EXPANDEDONCE))
	{

		KERN_CLASS_TYPEDEF eclass;
		CString info = "Class:";
 		model->m_mi->ENTITY_ask_class(entity, eclass);
	
		if( eclass == KERN_FACE_TYPE )
		{
			int numedges;
			long *edges;
			model->m_mi->FACE_ask_edges(entity,&numedges, &edges);
			
			for (int edgenum=0;edgenum<numedges;edgenum++)
				HTREEITEM edgeitem = InsertItemInTree(edges[edgenum],"Edge:",item);
			delete edges;
		}				
		else if( eclass == KERN_EDGE_TYPE )
		{
 	 
		}
		else if( eclass == KERN_BODY_TYPE )
		{
			int numfaces;
			long *faces;
			model->m_mi->BODY_ask_faces(entity,&numfaces, &faces);
			
			for (int facenum=0;facenum<numfaces;facenum++)
				HTREEITEM faceitem = InsertItemInTree(faces[facenum],"Face:",item);
		}
	}

}


void CPlainTopolBrowserDlg::OnAnnotate() 
{
#ifdef ACIS
	AfxMessageBox(_T("Not yet implemented"));
	return;
#endif // ACIS
#ifdef PARASOLID
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
		KERN_CLASS_TYPEDEF eclass;
		PK_ENTITY_ask_class(entity,&eclass);
 		
		CString itext;
		switch(eclass)
		{
		case KERN_BODY_TYPE:
			itext = "Body:";
			break;
		case KERN_FACE_TYPE:
			itext = "Face:";
			break;
		case PK_CLASS_shell:
			itext = "Shell:";
			break;
		case KERN_EDGE_TYPE:
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
#endif // PARASOLID
}

 

void CPlainTopolBrowserDlg::OnFacevisibility() 
{
		CBusyDlg *	busy = new CBusyDlg();
 		busy->Create(IDD_BUSYDLG);
		busy->ShowWindow(SW_SHOW); 
		UpdateData(TRUE);

		HSSelectionSet* selection;
		selection = (HSSelectionSet *)m_pHView->GetSelection();			
		selection->DeSelectAll();

		((HSolidView *)m_pHView)->SetOptimizations(!m_pHView->GetOptimizations());	
		delete busy;
 
	 	if (m_facevisibility)
		{
			HTREEITEM sel = m_topol_tree.GetSelectedItem();
			if(sel)
			{
				long entity = (long)m_topol_tree.GetItemData(sel);
				KERN_CLASS_TYPEDEF eclass;
		 		model->m_mi->ENTITY_ask_class(entity, eclass);
				if (eclass == KERN_FACE_TYPE)
				{
					selection->Select(entity);	
				}
			}
		}
		m_pHView->Update();
		ShowSelectedItems();			
}

bool CPlainTopolBrowserDlg::BuildTopolTree()
{
  	CString title =((CView *)m_parent)->GetDocument()->GetTitle();
	SetWindowText("Topology Browser - "+title);
	m_dialogactive=true;	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_FACEVISIBILITY)->EnableWindow(0);

 	int tabs[5]={5,10,15,20,25};
	m_infolist.SetTabStops(4,tabs);
	m_TopInfoList.SetTabStops(4,tabs);
	
	model = (HSolidModel *)(m_pHView->GetModel());
 
	long* bodies;
	int numbodies;
	model->m_mi->ask_bodies(&numbodies,&bodies);

 	
	int totalnumfaces=0;
	for (int bodynum=0;bodynum<numbodies;bodynum++)
	{
		int numfaces;
		model->m_mi->BODY_ask_faces(bodies[bodynum],&numfaces,0);

		totalnumfaces+=numfaces;
		HTREEITEM bodyitem = InsertItemInTree(bodies[bodynum],"Body:",TVI_ROOT);
		if (bodynum == 0)
			m_rootitem = bodyitem;
	}
 
 	delete bodies;	
	
	HighlightSelection();

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

	return true;
}
