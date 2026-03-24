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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/TopolBrowserDlg.cpp,v 1.37 2008-05-01 18:01:41 chad Exp $
//

// TopolBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include <assert.h>
#include "HSInclude.h"
#include "resource.h"
#include "HSolidView.h"
#include "HSolidModel.h"

#include "CSolidHoopsFrm.h"
#include "hsselectionset.h"
#include "TopolBrowserDlg.h"
#include "annotatedlg.h"
#include "busydlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef PARASOLID
#include "hp_bridge.h"
#endif // PARASOLID


BEGIN_MESSAGE_MAP(CTopolTreeCtrl,CTreeCtrl)
	//{{AFX_MSG_MAP(CTopolTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_VSCROLL()

 END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTopolTreeCtrl




/////////////////////////////////////////////////////////////////////////////
// CTopolTreeCtrl message handlers

//subclassing the tree control was necessary because we need to handle the scroll events
void CTopolTreeCtrl::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )

{
 	CTreeCtrl::OnVScroll( nSBCode, nPos, pScrollBar ); 
 	((CTopolBrowserDlg *)GetParent())->ShowSelectedItems();	 
}


 /////////////////////////////////////////////////////////////////////////////
// CTopolBrowserDlg dialog


CTopolBrowserDlg::CTopolBrowserDlg(CWnd* pParent /*=NULL*/, HSolidView * View)
	: CDialog(CTopolBrowserDlg::IDD, pParent)
{
	m_pHView = View;
	m_parent = pParent;
	m_dialogactive = false;
	m_bItemSelected = false;
	m_rootitem=0;
 	//{{AFX_DATA_INIT(CTopolBrowserDlg)
	m_facevisibility = !((HSolidView *)m_pHView)->GetOptimizations();
 	m_edgevisibility = FALSE;
	m_bAlwaysZoom = FALSE;
	//}}AFX_DATA_INIT

#ifdef ACIS
 	m_vertexvisibility = false;
#endif
}

BOOL CTopolBrowserDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    m_imageState.Create( IDB_STATE, 16, 1, RGB(255,255,255) );
    m_topol_tree.SetImageList( &(m_imageState), TVSIL_STATE );
#ifndef INTEROP
	m_InterOpPartBrowserSwitch.ShowWindow(SW_HIDE);
#endif // INTEROP
    return true;
}

void CTopolBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTopolBrowserDlg)
	DDX_Control(pDX, IDC_LIST4, m_TopInfoList);
	DDX_Control(pDX, IDC_LIST3, m_infolist);
	DDX_Check(pDX, IDC_FACEVISIBILITY, m_facevisibility);
	DDX_Check(pDX, IDC_EDGE_VISIBILITY, m_edgevisibility);
	DDX_Check(pDX, IDC_ALWAYS_ZOOM, m_bAlwaysZoom);
	DDX_Control(pDX, IDC_TOPOLOGY_BROWSER_SWITCH, m_TopologyBrowserSwitch);
	DDX_Control(pDX, IDC_SEGMENT_BROWSER_SWITCH, m_SegmentBrowserSwitch);
	DDX_Control(pDX, IDC_IOP_PART_BROWSER_SWITCH, m_InterOpPartBrowserSwitch);
	//}}AFX_DATA_MAP
#ifdef ACIS
	DDX_Check(pDX, IDC_VERTEX_VISIBILITY, m_vertexvisibility);
#endif
}

 

BEGIN_MESSAGE_MAP(CTopolBrowserDlg, CDialog)
//{{AFX_MSG_MAP(CTopolBrowserDlg)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, OnItemexpandingTree1)
ON_BN_CLICKED(IDC_ANNOTATE, OnAnnotate)
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_FACEVISIBILITY, OnFacevisibility)
ON_BN_CLICKED(IDC_EDGE_VISIBILITY, OnEdgeVisibility)
ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE1, OnItemexpandedTree1)
ON_BN_CLICKED(IDC_ZOOMTOSELECTION, OnZoomtoselection)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_ALWAYS_ZOOM, OnAlwaysZoom)
ON_BN_CLICKED(IDC_SEGMENT_BROWSER_SWITCH, OnSegmentBrowserSwitch)
ON_BN_CLICKED(IDC_IOP_PART_BROWSER_SWITCH, OnInterOpPartBrowserSwitch)
ON_WM_SIZE()

//}}AFX_MSG_MAP
#ifdef ACIS
	ON_BN_CLICKED(IDC_VERTEX_VISIBILITY, OnVertexVisibility)
#endif

END_MESSAGE_MAP()



  
//this function updates the selected item display (bold) in the tree control for the visible
//elements
//needs to be called whenever the selection has changed
//this is the main cause for speed problems with a large number of selections
//fix: have to think of a way to speed up the selection process...
void CTopolBrowserDlg::ShowSelectedItems()
{

	HSSelectionSet *selection;
 	selection = (HSSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSolidListSize();
	HTREEITEM item = m_topol_tree.GetFirstVisibleItem();
  	int viscount=0;
	bool somethingFound = false;
	while (item)
	{
		viscount++;
		m_topol_tree.SetItemState(item,0,TVIS_BOLD);
		int data = m_topol_tree.GetItemData(item);
		for (int i=0;i<ssize;i++)
		{
			if (selection->GetAtSolidEntity(i) == data)
			{
				somethingFound = true;
		 		m_topol_tree.SetItemState(item,TVIS_BOLD,TVIS_BOLD);
				break;
			}
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

	


#ifdef PARASOLID
bool CTopolBrowserDlg::CheckSelection(PK_ENTITY_t entity)
{
	HSSelectionSet* selection;
	selection = (HSSelectionSet *)m_pHView->GetSelection();
	int size = selection->GetSolidListSize();
	for (int i=0;i<size;i++)
	{
		if (selection->GetAtSolidEntity(i) == entity)
			return true;
	}
	return false;
}
#endif // PARASOLID

#ifdef ACIS
bool CTopolBrowserDlg::CheckSelection(KERN_ENTITY entity)
{
	HSSelectionSet* selection;
	selection = (HSSelectionSet *)m_pHView->GetSelection();
	int size = selection->GetSolidListSize();
	for (int i=0;i<size;i++)
	{
		if ( (ENTITY*)selection->GetAtSolidEntity(i) == entity)
			return true;
	}
	return false;
}
#endif // ACIS


bool CTopolBrowserDlg::CheckSelection(long entity)
{
	HSSelectionSet* selection;
	selection = (HSSelectionSet *)m_pHView->GetSelection();
	int size = selection->GetSolidListSize();
	for (int i=0;i<size;i++)
	{
		if ( (long)selection->GetAtSolidEntity(i) == entity)
			return true;
	}
	return false;
}


//this function is called whenever a selection is changed in the tree control
//this could be the result of a selection/deselection in the tree control or in the view 
void CTopolBrowserDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	NM_TREEVIEW* pNMTreeView	= (NM_TREEVIEW*)pNMHDR;
  	TVITEM itemnew				= pNMTreeView->itemNew;
  	TVITEM itemold				= pNMTreeView->itemOld;
	KERN_ENTITY entity			= (KERN_ENTITY)itemnew.lParam;
	KERN_ENTITY entity_old		= (KERN_ENTITY)itemold.lParam;
	KERN_CLASS_TYPEDEF eclass;
	KERN_CLASS_TYPEDEF eclass_old = -1;
	KERN_CLASS_TYPEDEF save_select_level;
	HSSelectionSet *selection	= (HSSelectionSet *)m_pHView->GetSelection();
	
#ifdef PARASOLID
	if( entity_old ) 
		PK_ENTITY_ask_class(entity_old,&eclass_old);
	
	PK_ENTITY_ask_class(entity,&eclass);

	if (eclass==PK_CLASS_assembly || eclass==PK_CLASS_edge || eclass==PK_CLASS_face || eclass==PK_CLASS_body || eclass == PK_CLASS_instance)
#endif // PARASOLID

#ifdef ACIS
	if(entity_old)
		eclass_old = entity_old->identity();

	eclass = entity->identity();

	if (eclass==VERTEX_TYPE|| eclass==EDGE_TYPE|| eclass==FACE_TYPE|| eclass==BODY_TYPE)
#endif // ACIS

#ifdef GRANITE
	if( entity_old )
		eclass_old = entity_old->giveRtti();

	eclass = entity->giveRtti();

	if (eclass==KERN_EDGE_TYPE|| eclass==KERN_FACE_TYPE|| eclass==KERN_BODY_TYPE)
#endif // GRANITE

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
 


//called whenever the expands a subtree for the first time
void CTopolBrowserDlg::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	// TODO: Add your control notification handler code here
 	TVITEM itemnew = pNMTreeView->itemNew;

#ifdef PARASOLID
	PK_ENTITY_t entity = (PK_ENTITY_t)itemnew.lParam;
#endif // PARASOLID
#ifdef ACIS
	ENTITY* entity = (ENTITY*)itemnew.lParam;
#endif // ACIS
#ifdef GRANITE
	KObj_ptr entity = (KObj*)itemnew.lParam;
#endif // GRANITE
	
	FillItems(entity,itemnew.hItem);
	
	*pResult = 0;

}
 

void CTopolBrowserDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_dialogactive=false;
	CDialog::OnClose();
}

void CTopolBrowserDlg::OnFacevisibility() 
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
#ifdef PARASOLID
			PK_ENTITY_t entity = (PK_ENTITY_t)m_topol_tree.GetItemData(sel);
			PK_CLASS_t eclass;
			PK_ENTITY_ask_class(entity,&eclass);
			if (eclass == PK_CLASS_face)
#endif // PARASOLID
#ifdef ACIS
			ENTITY* entity = (ENTITY*)m_topol_tree.GetItemData(sel);
			int eclass;
			eclass = entity->identity();
			if (eclass == FACE_TYPE)
#endif // ACIS
#ifdef GRANITE
			KERN_ENTITY entity = KObj::cast((KObj*)m_topol_tree.GetItemData(sel));
			assert( entity );
			KERN_CLASS_TYPEDEF eclass;
			eclass = entity->giveRtti();
			if (eclass == KERN_FACE_TYPE)
#endif // GRANITE

			{
				;
			  //  selection->Select(entity);			
			}
		}
	}
	m_pHView->Update();
	ShowSelectedItems();			

}

void CTopolBrowserDlg::OnEdgeVisibility() 
{
	UpdateData(TRUE);
	m_parent->PostMessage(WM_COMMAND,ID_TOOLS_VISIBILITY_BREP_EDGES,0);
	m_pHView->Update();		
}

#ifdef ACIS
void CTopolBrowserDlg::OnVertexVisibility() 
{
	UpdateData(TRUE);
	m_parent->PostMessage(WM_COMMAND,ID_TOOLS_VISIBILITY_VERTICES,0);
	m_pHView->Update();		
}
#endif


void CTopolBrowserDlg::OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	ShowSelectedItems();	
	*pResult = 0;
}

void CTopolBrowserDlg::UpdateTopolBrowserCheckboxes()
{ 
 		m_facevisibility = !m_pHView->GetOptimizations();

		HC_Open_Segment_By_Key (m_pHView->GetSceneKey());
		char edges[MVO_BUFFER_SIZE];
		char lines[MVO_BUFFER_SIZE];
		HC_Show_One_Visibility("edges",edges);
		HC_Show_One_Visibility("lines",lines);
		if (strcmp(edges,"off")==0 && strcmp(lines,"off")==0)
			m_edgevisibility = false;
		else
			m_edgevisibility = true;
#ifdef ACIS
		char vertices[MVO_BUFFER_SIZE];
		HC_Show_One_Visibility("markers",vertices);
		if (strcmp(vertices,"off")==0)
			m_vertexvisibility = false;
		else
			m_vertexvisibility = true;
#endif
		HC_Close_Segment();
 
		UpdateData(FALSE);
}
 
   
void CTopolBrowserDlg::OnZoomtoselection() 
{
	// TODO: Add your control notification handler code here
 	m_parent->PostMessage(WM_COMMAND,ID_ZOOM_TO_SELECTION,0);

	
}

void CTopolBrowserDlg::OnAlwaysZoom() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CTopolBrowserDlg::ValidateTopolTree()
{
	m_topol_tree.DeleteAllItems();
	BuildTopolTree();
}

void CTopolBrowserDlg::OnSegmentBrowserSwitch() 
{
	// TODO: Add your control notification handler code here
    CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();   
    frame->OnTopolbrowser();
    frame->OnSegmentbrowser();
}

void CTopolBrowserDlg::OnInterOpPartBrowserSwitch() 
{
	// TODO: Add your control notification handler code here
    CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();   
    frame->OnTopolbrowser();
    frame->OnInterOpPartBrowser();
}



void CTopolBrowserDlg::OnSize(UINT nType, int cx, int cy) 
{	
	
	CDialog::OnSize(nType, cx, cy); 
	if (cx<241)
		cx = 241;
	
	if (m_dialogactive)
	{

#ifdef INTEROP
		m_topol_tree.SetWindowPos(0, 0, 0, cx - 60, cy - 360, SWP_NOMOVE | SWP_NOREPOSITION);   	
		m_TopInfoList.SetWindowPos(0, 0, 0, cx - 60, 47, SWP_NOMOVE | SWP_NOREPOSITION);   	
		m_infolist.SetWindowPos(0, 0, 0, cx - 60, 90, SWP_NOMOVE | SWP_NOREPOSITION);   	


		CWnd *wnd = GetDlgItem(IDC_BROWSER_FRAME);
		wnd->SetWindowPos(0, 0, 0, cx - 43, cy - 335, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_SEGBROWSERWRAP);
		wnd->SetWindowPos(0, 0, 0, cx - 20, cy - 70, SWP_NOMOVE | SWP_NOREPOSITION);   

		wnd = GetDlgItem(IDC_FACEVISIBILITY);
		wnd->SetWindowPos(0, 40, cy - 175, 0, 0, SWP_NOSIZE);   
		wnd = GetDlgItem(IDC_EDGE_VISIBILITY);
		wnd->SetWindowPos(0, 40, cy - 155, 0, 0, SWP_NOSIZE);   

#ifdef ACIS 
		wnd = GetDlgItem(IDC_VERTEX_VISIBILITY);
		wnd->SetWindowPos(0, 40, cy - 135, 0, 0, SWP_NOSIZE);   

 		wnd = GetDlgItem(IDC_ALWAYS_ZOOM);
		wnd->SetWindowPos(0, 40, cy - 115, 0, 0, SWP_NOSIZE);   
		wnd = GetDlgItem(IDC_ZOOMTOSELECTION);
		wnd->SetWindowPos(0, 70, cy - 95, 0, 0, SWP_NOSIZE);   

#endif // ACIS
#ifdef PARASOLID
 		wnd = GetDlgItem(IDC_ALWAYS_ZOOM);
		wnd->SetWindowPos(0, 40, cy - 135, 0, 0, SWP_NOSIZE);   
 
		wnd = GetDlgItem(IDC_ZOOMTOSELECTION);
		wnd->SetWindowPos(0, 130, cy - 105, 0, 0, SWP_NOSIZE);   
		wnd = GetDlgItem(IDC_ANNOTATE);
		wnd->SetWindowPos(0, 30, cy - 105, 0, 0, SWP_NOSIZE);   
#endif // PARASOLID

		m_SegmentBrowserSwitch.SetWindowPos(0, 10, cy - 65, 0, 0, SWP_NOSIZE);
 		m_TopologyBrowserSwitch.SetWindowPos(0, 130, cy - 65, 0, 0, SWP_NOSIZE);
		m_InterOpPartBrowserSwitch.SetWindowPos(0, 60, cy - 35, 0, 0, SWP_NOSIZE);

#else
		m_topol_tree.SetWindowPos(0, 0,0,cx - 60,cy - 340, SWP_NOMOVE | SWP_NOREPOSITION);   	
		m_TopInfoList.SetWindowPos(0, 0,0,cx - 60,47, SWP_NOMOVE | SWP_NOREPOSITION);   	
		m_infolist.SetWindowPos(0, 0,0,cx - 60,90, SWP_NOMOVE | SWP_NOREPOSITION);   	


		CWnd *wnd = GetDlgItem(IDC_BROWSER_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 48,cy - 320, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_SEGBROWSERWRAP);
		wnd->SetWindowPos(0, 0,0,cx - 27,cy - 35, SWP_NOMOVE | SWP_NOREPOSITION);   

		wnd = GetDlgItem(IDC_FACEVISIBILITY);
		wnd->SetWindowPos(0, 40,cy-150,0,0, SWP_NOSIZE);   
		wnd = GetDlgItem(IDC_EDGE_VISIBILITY);
		wnd->SetWindowPos(0, 40,cy-130,0,0, SWP_NOSIZE);   
#ifdef ACIS 

		wnd = GetDlgItem(IDC_VERTEX_VISIBILITY);
		wnd->SetWindowPos(0, 40,cy-110,0,0, SWP_NOSIZE);   

 		wnd = GetDlgItem(IDC_ALWAYS_ZOOM);
		wnd->SetWindowPos(0, 40,cy-90,0,0, SWP_NOSIZE);   
		wnd = GetDlgItem(IDC_ZOOMTOSELECTION);
		wnd->SetWindowPos(0, 70,cy-60,0,0, SWP_NOSIZE);   

#endif // ACIS
#ifdef PARASOLID
 		wnd = GetDlgItem(IDC_ALWAYS_ZOOM);
		wnd->SetWindowPos(0, 40,cy-110,0,0, SWP_NOSIZE);   
 
		wnd = GetDlgItem(IDC_ZOOMTOSELECTION);
		wnd->SetWindowPos(0, 130,cy-80,0,0, SWP_NOSIZE);   
		wnd = GetDlgItem(IDC_ANNOTATE);
		wnd->SetWindowPos(0, 30,cy-80,0,0, SWP_NOSIZE);   
#endif // PARASOLID
#ifdef GRANITE
 		wnd = GetDlgItem(IDC_ALWAYS_ZOOM);
		wnd->SetWindowPos(0, 40,cy-110,0,0, SWP_NOSIZE);   
		wnd = GetDlgItem(IDC_ZOOMTOSELECTION);
		wnd->SetWindowPos(0, 70,cy-80,0,0, SWP_NOSIZE);   
#endif // GRANITE
 




/*		CWnd *wnd = GetDlgItem(IDC_SEGBROWSERWRAP);
		wnd->SetWindowPos(0, 0,0,cx - 30,cy - 50, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_BROWSER_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 48,cy - 210, SWP_NOMOVE | SWP_NOREPOSITION);   
		m_TopInfoList.SetWindowPos(0, 0,0,cx - 60,75, SWP_NOMOVE | SWP_NOREPOSITION);   	
		wnd = GetDlgItem(IDC_INFO_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 48,100, SWP_NOMOVE | SWP_NOREPOSITION);   
*/
  		m_SegmentBrowserSwitch.SetWindowPos(0, 10, cy-30, 0, 0, SWP_NOSIZE);
 		m_TopologyBrowserSwitch.SetWindowPos(0, 130, cy-30, 0, 0, SWP_NOSIZE);
#endif // INTEROP
	}
}
