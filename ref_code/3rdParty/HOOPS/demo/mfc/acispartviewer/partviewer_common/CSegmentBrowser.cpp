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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSegmentBrowser.cpp,v 1.17 2009-09-10 17:56:52 conor Exp $
//

// SegmentBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HSInclude.h"
#include <assert.h>
#include "CSegmentBrowser.h"
 
#include "HSSelectionSet.h"
#include "HModelInfo.h"
#include "hc.h"
#include "vlist.h"
#include "HUtilityLocaleString.h"

 /////////////////////////////////////////////////////////////////////////////
// CSegmentBrowser dialog


CSegmentBrowser::CSegmentBrowser(CWnd* pParent, 
								CListBox* pTopInfoList, 
								CTreeCtrl* pSegTreeCtrl,
								HBaseView * View)
{
	m_pHView = View;
	m_parent = pParent;
//	m_TopInfoList = pTopInfoList;
	m_Segment_tree = pSegTreeCtrl;
//	m_dialogactive = false;
//	m_SelectedTreeItem = NULL;
}


//void CSegmentBrowser::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	//{{AFX_DATA_MAP(CSegmentBrowser)
//	DDX_Control(pDX, IDC_LIST4, m_TopInfoList);
//	//}}AFX_DATA_MAP
//}


//BEGIN_MESSAGE_MAP(CSegmentBrowser, CDialog)
//	//{{AFX_MSG_MAP(CSegmentBrowser)
//	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
//	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, OnItemexpandingTree1)
// 	ON_WM_CLOSE()
// 	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE1, OnItemexpandedTree1)
//	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE2, OnItemexpandingTree2)
//	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE2, OnItemexpandedTree2)
//	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, OnSelchangedTree2)
//	ON_BN_CLICKED(IDC_DELETE_SELECTION, OnDeleteSelection)
//	ON_WM_SHOWWINDOW()
// 	ON_BN_CLICKED(IDC_SEGMENTBROWSERREFRESH, OnSegmentbrowserrefresh)
//	ON_BN_CLICKED(IDC_EXPANDFULLPATH, OnExpandfullpath)
// 	ON_WM_DESTROY()
//	ON_BN_CLICKED(IDC_EXPAND_SELECTION, OnExpandSelection)
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()

void CSegmentBrowser::HighlightSelectedItems()
{

	HSelectionSet *selection;
 	selection = (HSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSize();

	for (int j=0;j<ssize;j++)
		HighlightSelectedItems(m_rootitem, selection->GetAt(j));
}


void CSegmentBrowser::HighlightSelectedItems(HTREEITEM hItem, HC_KEY key)
{
	if( key == (HC_KEY) m_Segment_tree->GetItemData(hItem) )
	{
		m_Segment_tree->EnsureVisible(hItem);
 		m_Segment_tree->SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
	}
	else
 		m_Segment_tree->SetItemState(hItem,0,TVIS_BOLD);

	if (m_Segment_tree->ItemHasChildren(hItem))
	{
	   HTREEITEM child_item = m_Segment_tree->GetChildItem(hItem);
	   while (child_item != NULL)
	   {
		   HighlightSelectedItems( child_item, key);
		   hItem = m_Segment_tree->GetNextSiblingItem(child_item);
	   }
	}
}

//this function updates the selected item display (bold) in the tree control for the visible
//elements
//needs to be called whenever the selection has changed
//this is the main cause for speed problems with a large number of selections
//fix: have to think of a way to speed up the selection process...
void CSegmentBrowser::ShowSelectedItems()
{

	HSelectionSet *selection;
 	selection = (HSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSize();
	HTREEITEM item = m_Segment_tree->GetFirstVisibleItem();
  	int viscount=0;
	char type[MVO_BUFFER_SIZE];
	while (item)
	{
		viscount++;
		m_Segment_tree->SetItemState(item,0,TVIS_BOLD);
		HC_KEY item_key = m_Segment_tree->GetItemData(item);

		for (int i=0;i<ssize;i++)
		{
			HC_KEY sel_key = selection->GetAt(i);
			HC_Show_Key_Type(sel_key, type);
			if (strstr(type, "shell"))
				sel_key = HC_KShow_Owner_By_Key(sel_key);

			if ( sel_key == item_key)
			{
		 		m_Segment_tree->SetItemState(item,TVIS_BOLD,TVIS_BOLD);
				break;
			}
		}
 		if (viscount>1000)
			break;
		item = m_Segment_tree->GetNextVisibleItem(item);
	}

}


//this function inserts a new item into the tree control with it's name (if available) and the tagid
HTREEITEM CSegmentBrowser::InsertItemInTree(HC_KEY key, HTREEITEM position, CTreeCtrl *TreeCtrl)
{
	char text[MVO_BUFFER_SIZE];	
	int count;
	TVINSERTSTRUCT is;
	is.hParent = position;
	is.hInsertAfter=TVI_LAST;
	is.item.mask=TVIF_CHILDREN | TVIF_TEXT;

	HC_Show_Key_Type(key, text);

	if (strstr(text, "segment"))
	{
		HC_Open_Segment_By_Key(key);
		HC_Begin_Contents_Search(".","segments");
		HC_Show_Contents_Count(&count);
		HC_End_Contents_Search();
		HC_Close_Segment();

		if (count)
 			is.item.cChildren = 1;
		else
 			is.item.cChildren = 0;	

 		HC_Show_Segment(key, text);
		HC_Parse_String(text,"/",-1,text);
	}
	else // I'm dealing with the geometry tree
	{
		char	type[MVO_BUFFER_SIZE];
		HC_Show_Key_Type(key, type);
		if (position == TVI_ROOT)
		{
 			HC_Show_Key_Type(key, text);
			HC_Parse_String(text,"/",-1,text);
			is.item.cChildren = 1;
		}
		else if (strstr(type, "include"))
		{
			char location[MVO_BUFFER_SIZE];
			HC_Show_Include_Segment(key, location);
			sprintf(text, "%s", location);
			is.item.cChildren = 0;
		}
		else //(!TreeCtrl->GetParentItem(position))
		{
			sprintf(text, "%d", key);
			is.item.cChildren = 0;			
		}
	}

	H_TEXT label_text(text);
	is.item.pszText= (LPTSTR)(const TCHAR*)label_text; // pszText is not const - even though it is meant to be
	HTREEITEM item = TreeCtrl->InsertItem(&is);

 	TreeCtrl->SetItemData(item,(DWORD)key);		

	// query the parent items state and apply
	HTREEITEM parent_item = TreeCtrl->GetParentItem( item );
	if( parent_item && (TreeCtrl->GetCheck(parent_item) == TRUE))
		TreeCtrl->SetCheck(item, TRUE);


	return item;
}

HTREEITEM CSegmentBrowser::InsertSegmentList(HC_KEY segkey, HTREEITEM item)
{
 	char text[MVO_BUFFER_SIZE];	

	UINT state;
	if (item!=TVI_ROOT)
		state = m_Segment_tree->GetItemState(item,TVIS_EXPANDEDONCE);
	
//	if (item == TVI_ROOT || !(state & TVIS_EXPANDEDONCE))
	{
		HTREEITEM citem = m_Segment_tree->GetChildItem(item);
		while (citem)
		{
			HTREEITEM nextitem = m_Segment_tree->GetNextSiblingItem(citem);
			m_Segment_tree->DeleteItem(citem);
			citem = nextitem;
		}
		HC_Open_Segment_By_Key(segkey);
		HC_Begin_Contents_Search(".","segments");
		HC_KEY child_key;
		while (HC_Find_Contents(text,&child_key))
		{
			if (first_run)
			{
				m_rootitem = InsertItemInTree(child_key ,item, (CTreeCtrl *)m_Segment_tree);
				first_run = false;
			}
			else
				InsertItemInTree(child_key ,item, (CTreeCtrl *)m_Segment_tree);
		}
		HC_End_Contents_Search();
		HC_Close_Segment();
	}
	ValidateSegmentTree();

	return m_rootitem;
}

BOOL CSegmentBrowser::OnInitDialog() 
{
	first_run = true;
	m_blockValidation = false;
//	m_Segment_tree->SubclassDlgItem(IDC_TREE1, m_parent);
//TODO	m_GeometryTree.SubclassDlgItem(IDC_TREE2,m_parent);
	
//  	CString title =((CView *)m_parent)->GetDocument()->GetTitle();
//	SetWindowText("Segment Browser - "+title);
//	m_dialogactive=true;	

	// create an image list
	CImageList* pStateImageList;
	pStateImageList = new CImageList();
	pStateImageList->Create(16, 16, ILC_MASK, 4, 4);
	// NOTE: ALL IMAGES INSERTED ARE THE SAME i.e. CHECKED ONES
	// ONCE YOU START WANTING AN "UNCHECKED" IMAGE, CREATE AN APPROPRIATE ICON AND LOAD HERE
	pStateImageList->Add(AfxGetApp()->LoadIcon(IDI_ITEM_CHECKED));
	pStateImageList->Add(AfxGetApp()->LoadIcon(IDI_ITEM_CHECKED));
	pStateImageList->Add(AfxGetApp()->LoadIcon(IDI_ITEM_CHECKED));
	m_Segment_tree->SetImageList(pStateImageList, TVSIL_STATE);

 
// 	int tabs[5]={5,10,15,20,25};
//	m_TopInfoList->SetTabStops(4,tabs);
	
	HSolidModel *model = (HSolidModel *)(m_pHView->GetModel());
   	
	m_baseKey = HC_KOpen_Segment("/");
	HC_Close_Segment();
	m_baseKey = model->GetModelKey();
  	InsertSegmentList(m_baseKey, TVI_ROOT);

//	if (!HighlightSelection())
//		m_bNoupdate = true;

//	m_TopInfoList->ResetContent();
//	CString indent = "\t";
//
//	HModelInfo	*ModelInfo;
//	ModelInfo = new HModelInfo(model->GetModelKey());
//
//	ModelInfo->ComputeModelInfo(); 
//
//	int triangle_count = ModelInfo->GetTotalTriangles();
//	int polyline_count = ModelInfo->GetTotalLine() +
//							ModelInfo->GetTotalPolyline() +
//							ModelInfo->GetTotalCircularArc() +
//							ModelInfo->GetTotalEllipticalArc();
//
//	delete ModelInfo;
// 	m_TopInfoList->SetHorizontalExtent(600);

//	char text[MVO_BUFFER_SIZE];
// 	m_TopInfoList->SetHorizontalExtent(600);

//	sprintf(text,"%d triangles",triangle_count);
// 	m_TopInfoList->AddString(indent + text);
//	sprintf(text,"%d polylines",polyline_count);
// 	m_TopInfoList->AddString(indent + text);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSegmentBrowser::SetAttributeTextBox(HC_KEY key)
{
}

//this function is called whenever a selection is changed in the tree control
//this could be the result of a selection/deselection in the tree control or in the view 
void CSegmentBrowser::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  	TVITEM itemnew = pNMTreeView->itemNew;
	HC_KEY key = (HC_KEY)itemnew.lParam;
 	m_bItemSelected = false;	
	m_bNoupdate=false;

//	//update the information box
//	m_TopInfoList->ResetContent();
//	CString indent = "\t";
//
//	HModelInfo	*ModelInfo;
//	ModelInfo = new HModelInfo(key);
//
//	ModelInfo->ComputeModelInfo(); 
//
//	int triangle_count = ModelInfo->GetTotalTriangles();
//	int text_count = ModelInfo->GetTotalText();
//	int polyline_count = ModelInfo->GetTotalLine() +
//							ModelInfo->GetTotalPolyline() +
//							ModelInfo->GetTotalCircularArc() +
//							ModelInfo->GetTotalEllipticalArc();
//	int subsegment_count = ModelInfo->GetTotalSegments();
//
//	delete ModelInfo;
//
//	char text[MVO_BUFFER_SIZE];
//
//	if (triangle_count)
//	{
//		sprintf(text,"%d triangles",triangle_count);
// 		m_TopInfoList->AddString(indent + text);
//	}
//	if (polyline_count)
//	{
//		sprintf(text,"%d polylines",polyline_count);
// 		m_TopInfoList->AddString(indent + text);
//	}
//	if (text_count)
//	{
//		sprintf(text,"%d text strings",text_count);
// 		m_TopInfoList->AddString(indent + text);
//	}
//	if (subsegment_count)
//	{
//		sprintf(text,"%d subsegments (total)",subsegment_count);
// 		m_TopInfoList->AddString(indent + text);
//	}
//
//	HC_Open_Segment_By_Key(key);
//	HC_Begin_Contents_Search(".","attributes");
//	{
//		char type[MVO_BUFFER_SIZE];
//		char text[MVO_BUFFER_SIZE];
//		HC_KEY dummy;
//		while (HC_Find_Contents(type,&dummy))
//		{
//			if (strcmp(type,"color") == 0)
//			{
//				HC_Show_Color(text);
//		 		m_TopInfoList->AddString(indent + "Color:" + text);
//			}
//		}
//	}
//	HC_End_Contents_Search();
//	HC_Close_Segment();

//	// first let's clear out the geometry tree control
//TODO	m_GeometryTree.DeleteAllItems();

	HC_Open_Segment_By_Key(key);
		if (HC_Show_Existence("geometry, includes"))
			InsertGeometryList(key, TVI_ROOT);
	HC_Close_Segment();

	// now highlight the entity
	HSSelectionSet *selection;

	selection = (HSSelectionSet *)m_pHView->GetSelection();
 
 	if (!(GetAsyncKeyState(VK_SHIFT) & 32768))		
	{
		selection->DeSelectAll();
		if (!selection->IsSelected(key))
		selection->Select(key, "", 0, 0, true);
	}
	else
	{
		if (!selection->IsSelected(key))
				selection->Select(key,"",0,0, true);	
			else
			selection->DeSelect(key, true);	
	}


	//if (!selection->IsSelected(key))
	//	selection->Select(key, "", 0, 0);

	ValidateSegmentTree();

	m_pHView->Update();
 	
 	*pResult = 0;
}

//called whenever the expands a subtree for the first time
void CSegmentBrowser::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
 	TVITEM itemnew = pNMTreeView->itemNew;
	HC_KEY key = (HC_KEY)itemnew.lParam;
 	UINT state = m_Segment_tree->GetItemState(itemnew.hItem,TVIS_EXPANDED);
	if (!(state & TVIS_EXPANDED))	
		InsertSegmentList(key,itemnew.hItem);	
	*pResult = 0;
}

void CSegmentBrowser::OnClose() 
{
	m_dialogactive=false;
//	CDialog::OnClose();
}

void CSegmentBrowser::OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	*pResult = 0;
	ShowSelectedItems();

}
   

void CSegmentBrowser::OnItemexpandingTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{ 	
	*pResult = 0;
}

void CSegmentBrowser::OnItemexpandedTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	*pResult = 0;
}

void CSegmentBrowser::OnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
/*	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  	TVITEM itemnew = pNMTreeView->itemNew;
	HC_KEY key = (HC_KEY)itemnew.lParam;
 	m_bItemSelected = false;	
	m_bNoupdate=false;

	// highlight the entity
	HSSelectionSet *selection;

	selection = (HSSelectionSet *)m_pHView->GetSelection();
	selection ->DeSelectAll();

	char	type[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(key, type);

	if (strstr(type, "include") )
		key = HC_KShow_Include_Segment(key);

	if (strstr(type, "segment") || strstr(type, "include"))
		selection->SetSelectLevel(HSSelectionSet::SegmentSelectLevel);
	else
		selection->SetSelectLevel(HSSelectionSet::EntitySelectLevel);

	if (!selection->IsSelected(key))
		selection->Select(key, "", 0, 0);

	m_pHView->Update();

	*pResult = 0;
*/}

HTREEITEM CSegmentBrowser::InsertGeometryList(HC_KEY segkey, HTREEITEM item)
{

 	char text[MVO_BUFFER_SIZE];	

//	UINT state;
//TODO	if (item != TVI_ROOT)
//		state = m_GeometryTree.GetItemState(item,TVIS_EXPANDEDONCE);
	
	char type[MVO_BUFFER_SIZE];
	bool new_type = true;

	if (item == TVI_ROOT /*|| !(state & TVIS_EXPANDEDONCE)*/)
	{
		HC_Open_Segment_By_Key(segkey);
		HC_Begin_Contents_Search(".","geometry, includes");
		HC_KEY geometry_key;
		while (HC_Find_Contents(text, &geometry_key))
		{
			if (!strstr(type, text))
				new_type = true;

			if (new_type)
			{
				strcpy(type, text);
//TODO				m_GeometryItem = InsertItemInTree(geometry_key, TVI_ROOT, (CTreeCtrl *)&m_GeometryTree);
//TODO				InsertItemInTree(geometry_key, m_GeometryItem, (CTreeCtrl *)&m_GeometryTree);
				new_type = false;
			}
//TODO			else
//TODO				InsertItemInTree(geometry_key, m_GeometryItem, (CTreeCtrl *)&m_GeometryTree);
		}
		HC_End_Contents_Search();
		HC_Close_Segment();
	}
	return m_rootitem;
	
}

void CSegmentBrowser::OnDeleteSelection() 
{
	m_pHView->DeleteSelectionList(true);
//TODO	m_GeometryTree.DeleteAllItems();
	ValidateSegmentTree();
}




bool CSegmentBrowser::ShowItemExistence(HTREEITEM item)
{
	bool found = false;
	HTREEITEM owneritem = m_Segment_tree->GetParentItem(item);
	if (owneritem)
	{
		HC_KEY parentkey =  m_Segment_tree->GetItemData(owneritem);
		HC_Open_Segment_By_Key(parentkey);
		HC_Begin_Contents_Search(".","segments");
		char type[MVO_BUFFER_SIZE];
		HC_KEY key;
		while (HC_Find_Contents(type, &key))
		{
			if (key == (HC_KEY)m_Segment_tree->GetItemData(item))
			{
				found = true;
				break;
			}
		}
		HC_End_Contents_Search();
		return found;
	}
	return true;
}




//this function updates the Visible item display (bold) in the tree control for the visible
//elements
//needs to be called whenever the selection has changed
//this is the main cause for speed problems with a large number of selections
//fix: have to think of a way to speed up the selection process...
void CSegmentBrowser::UpdateVisibleItems()
{

	HSelectionSet *selection;
  	selection = (HSelectionSet *)m_pHView->GetSelection();
 	HTREEITEM item = m_Segment_tree->GetFirstVisibleItem();
	HTREEITEM newitem;
  	int viscount=0;
	while (item)
	{
		viscount++;
		m_Segment_tree->SetItemState(item,0,TVIS_BOLD);
		newitem = m_Segment_tree->GetNextVisibleItem(item);

		if (!ShowItemExistence(item))
			m_Segment_tree->DeleteItem(item);
 //the visible items are all items from the top visible down to the last item on the list 
//even if it is outside the window. That is why we brake processing at 25 elements
		if (viscount>25)
			break;
		item = newitem;
	}
}




void CSegmentBrowser::ValidateSegmentTreeInternal(HTREEITEM parentItem, HC_KEY parentKey)
{
	int segmentCount;
	char type[MVO_BUFFER_SIZE];
	int i;
	HC_Open_Segment_By_Key(parentKey);
	HC_Begin_Contents_Search(".","segment");
	HC_Show_Contents_Count(&segmentCount);
	if (segmentCount > m_segmentCountMax)
	{
		delete [] m_pSegmentList;
		m_pSegmentList = new HC_KEY[segmentCount];
		segmentCount = m_segmentCountMax;
	}
	for (i=0;i<segmentCount;i++)
 		HC_Find_Contents(type, &m_pSegmentList[i]);
	HC_End_Contents_Search();
	HC_Close_Segment();

	HTREEITEM item = m_Segment_tree->GetChildItem(parentItem);

	while (item)
	{
		HC_KEY itemkey = m_Segment_tree->GetItemData(item);
		bool found = false;
		for (i=0;i < segmentCount;i++)
		{
			if (m_pSegmentList[i] == itemkey)
			{
				found = true;
				m_pSegmentList[i] = 0;
				break;
			}
		}
		HTREEITEM nextItem = m_Segment_tree->GetNextSiblingItem(item);

		if (!found)
			m_Segment_tree->DeleteItem(item);
		item = nextItem;
	}

	for (i=0;i<segmentCount;i++)
	{
		if (m_pSegmentList[i] != 0)
			InsertItemInTree(m_pSegmentList[i],parentItem, (CTreeCtrl *)m_Segment_tree);
	}


	item = m_Segment_tree->GetChildItem(parentItem);

	while (item)
	{
 		UINT state = m_Segment_tree->GetItemState(item,TVIS_EXPANDED);
		if (state & TVIS_EXPANDED)
		{
			HC_KEY itemkey = m_Segment_tree->GetItemData(item);
			ValidateSegmentTreeInternal(item, itemkey);
		}
		item = m_Segment_tree->GetNextSiblingItem(item);
	}
}



void CSegmentBrowser::ValidateSegmentTree()
{
	static bool is_validating = false;
	if (!m_blockValidation)
	{
		if (!is_validating)
		{
			is_validating = true;
 			m_segmentCountMax = 1000;
			m_pSegmentList = new HC_KEY[m_segmentCountMax];
			
			ValidateSegmentTreeInternal(TVI_ROOT,m_baseKey);
			delete [] m_pSegmentList;
			is_validating = false;
		}
	}
	ShowSelectedItems();
	
}

void CSegmentBrowser::OnShowWindow(BOOL bShow, UINT nStatus) 
{
//	CDialog::OnShowWindow(bShow, nStatus);
	ValidateSegmentTree();
	// TODO: Add your message handler code here
	
}

 
void CSegmentBrowser::OnSegmentbrowserrefresh() 
{
	// TODO: Add your control notification handler code here
	ValidateSegmentTree();
	
}

void CSegmentBrowser::OnExpandfullpath() 
{
/* 
 	CButton *tbox =(CButton *)GetDlgItem(IDC_EXPANDFULLPATH);
 	CString button_text;
	tbox->GetWindowText(button_text);	

   	if (button_text == "Standard View")
	{
		m_baseKey = HC_KOpen_Segment("/");
		HC_Close_Segment();
		tbox->SetWindowText("Expanded View");
	}
	else
	{
		HBaseModel *model = (HBaseModel *)(m_pHView->GetModel());
		m_baseKey = model->GetModelKey();
 		tbox->SetWindowText("Standard View");
	}


	HMySelectionSet* selection;
	selection = (HMySelectionSet *)m_pHView->GetSelection();
 	selection->DeSelectAll();
	m_blockValidation = true;
  	m_Segment_tree->DeleteAllItems();

	first_run = true;
  	InsertSegmentList(m_baseKey, TVI_ROOT);	
	m_blockValidation = false;

*/ 
}



void CSegmentBrowser::ExpandSelection()
{
	
	
//	CButton *tbox =(CButton *)GetDlgItem(IDC_EXPANDFULLPATH);
//	CString button_text;
//	tbox->GetWindowText(button_text);	
	CString button_text("Standard View");
   	if (button_text == "Standard View")
	{
		
/*NOSEL		HSSelectionSet *selection;
		selection = (HSSelectionSet *)m_pHView->GetSelection();
		
		for (unsigned int i=0;i<selection->GetSize();i++)
		{
			HC_KEY selkey = selection->GetAt(i);
			
			HC_KEY keylist[1000];
			HC_KEY ownerkey = selkey;
			int keycount = 0;
			bool found = false;
			while (ownerkey)
			{
				keylist[keycount++] = ownerkey;
				if (ownerkey == m_pHView->GetModelKey())
				{
					keycount--;
					found = true;
					break;
				}
				ownerkey = HC_KShow_Owner_By_Key(ownerkey);
			}
			
			
			if (found)
			{
				bool firstitem = true;
				
				HTREEITEM item = m_Segment_tree->GetChildItem(TVI_ROOT);
				
				for (int i=keycount-1;i>=0;i--)
				{
					while (item)
					{
						
						HC_KEY itemkey = m_Segment_tree->GetItemData(item);
						if (itemkey == keylist[i])
						{
							if (i == 0)
							{
								if (firstitem)
								{
									m_Segment_tree->EnsureVisible(item);
									firstitem = false;
								}
							}
							else
							{
								
								UINT state = m_Segment_tree->GetItemState(item,TVIS_EXPANDED);
								if (!(state & TVIS_EXPANDED))
								{
									InsertSegmentList(itemkey,item);	
									m_Segment_tree->Expand(item,TVE_EXPAND);
								}
								item = m_Segment_tree->GetChildItem(item);
								break;
							}
						}
						item = m_Segment_tree->GetNextSiblingItem(item);					
					}
				}
			}
		}
		ShowSelectedItems();
*/	}
}

void CSegmentBrowser::OnExpandSelection() 
{
	// TODO: Add your control notification handler code here
	ExpandSelection();
	
}

static void GetSegmentShells( HC_KEY segKey, vlist_s* retShells, bool do_recurse = true )
{
    char type[MVO_BUFFER_SIZE];
    HC_KEY	key;
	HC_Open_Segment_By_Key( segKey );
		if (do_recurse) 
		{
			HC_Begin_Contents_Search (".", "segment, includes");
				while (HC_Find_Contents (type, &key) ) 
				{
					if (strstr("include", type))
					{
						HC_KEY new_key = HC_KShow_Include_Segment(key);
						GetSegmentShells( new_key, retShells, true );
					}
					else
						GetSegmentShells( key, retShells, true );
				}
		    HC_End_Contents_Search ();
		}

		/*
		 * after all of the children have been processed, process  current segment
		 *   (i.e., a post-order tree traversal)
		 */
		HC_Begin_Contents_Search (".", "shells");
			while (HC_Find_Contents (type, &key)) 
				vlist_add_last(retShells, (void*) key);
		HC_End_Contents_Search ();

	HC_Close_Segment();
}



void CSegmentBrowser::GetSelectedShells(HTREEITEM item, vlist_s* retSelectedShells)
{
	HC_KEY key =  m_Segment_tree->GetItemData(item);
//	HC_KEY key = (HC_KEY)itemnew.lParam;

	char type[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(key, type);


	if( strstr(type, "shell") )
		vlist_add_last(retSelectedShells, (void*) key );
	else if	(strstr(type, "include") )
	{
		key = HC_KShow_Include_Segment(key);
		GetSegmentShells(key, retSelectedShells, true);
	}
	else if ( strstr(type, "segment") )
		GetSegmentShells(key, retSelectedShells, true);

	return;
}


HC_KEY CSegmentBrowser::GetSelection(HTREEITEM item)
{
	return m_Segment_tree->GetItemData(item);
}

void CSegmentBrowser::OnDestroy()
{
    CImageList  *pimagelist;
    pimagelist = m_Segment_tree->GetImageList(TVSIL_STATE);
    if( pimagelist )
    {
	pimagelist->DeleteImageList();
	delete pimagelist;
    }
}

void CSegmentBrowser::ItemSweetened(HTREEITEM item, bool recurse)
{
	// put a check mark
    m_Segment_tree->SetCheck(item, TRUE);

	// dehighlight the item
	HSelectionSet *selection;
	selection = (HSelectionSet *)m_pHView->GetSelection();
	assert(selection);
	HC_KEY key =  m_Segment_tree->GetItemData(item);
	if (selection->IsSelected(key))
		selection->DeSelect(key, true);	
}

void CSegmentBrowser::OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult)
{
	if( !m_Segment_tree)
		*pLResult = FALSE;

	TV_DISPINFO     *ptvinfo;
	ptvinfo = (TV_DISPINFO *)pnmhdr;
	if (ptvinfo->item.pszText != NULL)
	{
		// rename the HOOPS segment
		HC_KEY key = m_Segment_tree->GetItemData(ptvinfo->item.hItem);
	
		char type[MVO_BUFFER_SIZE];	
		HC_Show_Key_Type(key, type);
		if (strstr(type, "segment"))
		{
			char new_name[MVO_BUFFER_SIZE];
			strcpy(new_name, "../");
			strcat(new_name, H_ASCII_TEXT(ptvinfo->item.pszText));
			HC_Open_Segment_By_Key(key);
				HC_Rename_Segment(".", new_name);
			HC_Close_Segment();

			ptvinfo->item.mask = TVIF_TEXT;
			m_Segment_tree->SetItem(&ptvinfo->item);
		}

	}
	*pLResult = TRUE;
}
