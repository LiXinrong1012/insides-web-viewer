// WindowsTreeGraph.cpp: implementation of the WindowsTreeGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TreeGraph.h"
#include "WindowsTreeGraph.h"
#include "HBaseView.h"
#include "HBaseModel.h"
#include "HSelectionSet.h"
#include "vlist.h"
#include "vhash.h"
#include "HUtilityLocaleString.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WindowsTreeGraph::WindowsTreeGraph(CTreeCtrl *treectrl, CListBox *infobox)  
{
		m_pTreeCtrl = treectrl;
		m_pInfoBox = infobox;
		SetRootItem(new WindowsTreeGraphItem(0, this, TVI_ROOT));

}

void WindowsTreeGraph::Flush()  
{
 	SetRootItem(new WindowsTreeGraphItem(0, this, TVI_ROOT));
}

TreeGraphItem* WindowsTreeGraphItem::AddChildItem(const TCHAR *text, void *extradata, bool insertlast)
{
	WindowsTreeGraphItem *item = new WindowsTreeGraphItem(this, m_pTreeGraph);
 	item->SetData(H_ASCII_TEXT(text), extradata);
	TVINSERTSTRUCT is;
	if (insertlast)
		SetupItemStruct(is, this, TVI_LAST, false, text, item);
	else
		SetupItemStruct(is, this, TVI_FIRST, false, text, item);

	item->SetTreeItem(((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->InsertItem(&is));
 	TreeGraphItem::AddChildItem(item, insertlast);
	return item;
	
}
TreeGraphItem* WindowsTreeGraphItem::AddSiblingItem(TCHAR *text, void *extradata, bool hasChildren)
{
	WindowsTreeGraphItem *item = new WindowsTreeGraphItem(m_pParentItem, m_pTreeGraph);
	item->SetData(H_ASCII_TEXT(text), extradata);	
	TVINSERTSTRUCT is;
	SetupItemStruct(is, ((WindowsTreeGraphItem *)m_pParentItem), this->m_TreeItem, hasChildren, text, item);

	item->SetTreeItem(((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->InsertItem(&is));
 	TreeGraphItem::AddSiblingItem(item);
	return item;
	
}


void WindowsTreeGraphItem::SetupItemStruct(TVINSERTSTRUCT &is, WindowsTreeGraphItem *parent, HTREEITEM insertafter,
											  bool children, const TCHAR *text, void *extradata)
{

	is.hParent = parent->m_TreeItem;
	
 
 	is.hInsertAfter=insertafter;
	is.item.mask=TVIF_CHILDREN | TVIF_TEXT | TVIF_PARAM;
	is.item.cChildren = children;
	is.item.lParam = (long)extradata;
	is.item.pszText=(LPTSTR)text;
}


void WindowsTreeGraphItem::SetHasChildren(bool hasChildren)
{
	TVITEM pitem;
	pitem.hItem = m_TreeItem;
	pitem.mask=TVIF_CHILDREN | TVIF_HANDLE;
//	if (vlist_peek_last(m_ChildItemList))
	if (hasChildren)
		pitem.cChildren = true;
	else
		pitem.cChildren = false;

	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItem(&pitem);
	if (!hasChildren)
	{
		START_LIST_ITERATION(TreeGraphItem, this->m_ChildItemList)
 				DeleteChildItem(temp);
		END_LIST_ITERATION(this->m_ChildItemList);
	}		

//	Verify();
}

void WindowsTreeGraphItem::SetBold(bool bold)
{
	if (bold)
		((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItemState(m_TreeItem, TVIS_BOLD, TVIS_BOLD);
	else
		((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItemState(m_TreeItem, 0, TVIS_BOLD);
	
}

void WindowsTreeGraphItem::SetSelected(bool selected)
{
	if (selected)
		((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItemState(m_TreeItem, TVIS_SELECTED, TVIS_SELECTED);
	else
		((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItemState(m_TreeItem, 0, TVIS_SELECTED);
	
}

void WindowsTreeGraphItem::SetImage(int checked)
{
/*	if (checked)
		((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetCheck(m_TreeItem, true);
	else
		((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetCheck(m_TreeItem, false);
*/

 ((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItemState(m_TreeItem, INDEXTOSTATEIMAGEMASK(checked), TVIS_STATEIMAGEMASK );
 
 	
}


void WindowsTreeGraph::OnImageClicked(HTREEITEM hti, long uFlags) 
{
	if( uFlags & TVHT_ONITEMSTATEICON )
	{
//		int iImage = m_pTreeCtrl->GetItemState( hti, TVIS_STATEIMAGEMASK )>>12;
//		m_pTreeCtrl->SetItemState( hti, INDEXTOSTATEIMAGEMASK(iImage == 1 ? 2 : 1), 
//					TVIS_STATEIMAGEMASK );
 		TVITEM istate;
		istate.mask = TVIF_HANDLE | TVIF_PARAM;
		istate.hItem = hti;
		m_pTreeCtrl->GetItem(&istate);
		TreeGraph::OnImageClicked((WindowsTreeGraphItem *)istate.lParam);
  
	}

 
}


void WindowsTreeGraph::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  	TVITEM treeitem = pNMTreeView->itemNew;
	WindowsTreeGraphItem *item2 = (WindowsTreeGraphItem *)treeitem.lParam;
	OnSelectionChanged(item2);

}

void WindowsTreeGraph::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
  	TVITEM treeitem = pTVDispInfo->item;
	WindowsTreeGraphItem *item2 = (WindowsTreeGraphItem *)treeitem.lParam;
	if (item2->m_bEditable)
 		*pResult = 0;
	else
 		*pResult = 1;
	OnBeforeTextModified(item2, H_ASCII_TEXT(treeitem.pszText));
}

void WindowsTreeGraph::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
  	TVITEM treeitem = pTVDispInfo->item;
	WindowsTreeGraphItem *item2 = (WindowsTreeGraphItem *)treeitem.lParam;
	OnTextModified(item2, H_ASCII_TEXT(treeitem.pszText));	
	*pResult = 0;
}

void WindowsTreeGraph::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
 	TVITEM treeitem = pNMTreeView->itemNew;
	WindowsTreeGraphItem *item2 = (WindowsTreeGraphItem *)treeitem.lParam;
	if (pNMTreeView->action == TVE_EXPAND)
 		OnItemExpanding(item2, true); 
 	else
		OnItemExpanding(item2, false); 
  	*pResult = 0;
}

void WindowsTreeGraphItem::ModifyText(const char *text)
{
	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItemText(m_TreeItem, H_TEXT(text));

//	TVITEM pitem;
//	pitem.hItem = m_TreeItem;
//	pitem.mask=TVIF_TEXT | TVIF_HANDLE;
 //	pitem.pszText = text;
//	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->SetItem(&pitem);
	TreeGraphItem::ModifyText(text);
}

bool WindowsTreeGraphItem::IsExpanded()
{
	if(this!=m_pTreeGraph->GetRootItem())
	{
		long state = ((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->GetItemState(m_TreeItem, TVIS_EXPANDED);

		if (state & TVIS_EXPANDED)
			return true;
		else
			return false;
	}
	else
		return true;
}

void WindowsTreeGraphItem::Expand()
{
	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->Expand(m_TreeItem, TVE_EXPAND);
 	TreeGraphItem::Expand();
}
void WindowsTreeGraphItem::UnExpand()
{
	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->Expand(m_TreeItem, TVE_COLLAPSE);
 	TreeGraphItem::UnExpand();
}

void WindowsTreeGraphItem::EditInPlace()
{
	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->EditLabel(m_TreeItem);
}


void WindowsTreeGraphItem::DeleteChildItem(TreeGraphItem *item)
{
//	delete item;
//	HTREEITEM deleteitem = ((WindowsTreeGraphItem *)item)->m_TreeItem;
//	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->DeleteItem(deleteitem);
	TreeGraphItem::DeleteChildItem(item);
}

WindowsTreeGraphItem::~WindowsTreeGraphItem()
{
	Flush();
	if (((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->m_hWnd)
	((WindowsTreeGraph *)m_pTreeGraph)->m_pTreeCtrl->DeleteItem(m_TreeItem);
}


void WindowsTreeGraph::ResetInfoContent()
{
		m_pInfoBox->ResetContent();
}


void WindowsTreeGraph::AddInfoString(char *text)
{
	m_pInfoBox->AddString(H_TEXT(text));
}


 