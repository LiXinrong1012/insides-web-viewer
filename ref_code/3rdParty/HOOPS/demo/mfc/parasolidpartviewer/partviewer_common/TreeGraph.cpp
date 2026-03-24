// TreeGraph.cpp: implementation of the TreeGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vlist.h"
#include "vhash.h"
#include "HUtilityLocaleString.h"

#include "TreeGraph.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TreeGraph::TreeGraph()
{
	m_ExtraDataHash = new_vhash(1, malloc, free);
	m_pMessageTarget = 0;
	m_pRootItem = 0;
//	m_pRootItem = new TreeGraphItem(0);
}
TreeGraph::~TreeGraph()
{
	vlist_s *templist= new_vlist(malloc, free);
	vhash_to_vlist(m_ExtraDataHash, templist, malloc);

	START_LIST_ITERATION(vlist_s, templist)
		delete_vlist(temp);
	END_LIST_ITERATION(templist);

	delete_vlist(templist);
	delete_vhash(m_ExtraDataHash);
 	delete m_pRootItem;
}

void TreeGraph::ResetInfoContent()
{
}
void TreeGraph::AddInfoString(char *text)
{
}

void TreeGraph::AddItemToHash(TreeGraphItem *item)
{
	vlist_s *list;
  	if (!(vhash_lookup_item(m_ExtraDataHash, (void *)item->m_pExtraData , (void **)&list) == VHASH_STATUS_SUCCESS))
	{
		list = new_vlist(malloc,free);
  		vhash_replace_item(m_ExtraDataHash, (void *)item->m_pExtraData , (void *)list, 0);
	}
	vlist_add_last(list,item);
}


void TreeGraph::DeleteItemFromHash(TreeGraphItem *item)
{
	vlist_s *list;
  	if ((vhash_lookup_item(m_ExtraDataHash, (void *)item->m_pExtraData , (void **)&list) == VHASH_STATUS_SUCCESS))
	{
		vlist_remove(list, item);
		if (!vlist_count(list))
		{
			delete_vlist(list);
			vhash_remove_item(m_ExtraDataHash, (void*)item->m_pExtraData,0);
		}
	}
}

struct vlist_s *TreeGraph::GetItemFromHash(void *key)
{
	vlist_s *list;
  	if (!(vhash_lookup_item(m_ExtraDataHash, key , (void **)&list) == VHASH_STATUS_SUCCESS))
	{
		return 0;
	}
	return list;
}


TreeGraphItem::TreeGraphItem(TreeGraphItem *item, TreeGraph *graphcontrol)
{
	m_pParentItem = item;
	m_ChildItemList = new_vlist( malloc, free );
	m_bExpanded = false;
	m_pItemText = 0;
	m_pItemText2 = 0;
	m_pExtraData = 0;
	m_pExtraData2 = 0;
	m_pTreeGraph = graphcontrol;
	m_bEditable = true;
	m_Flags = 0;
	m_Type = 0;
}

void TreeGraphItem::Flush()
{
	while (1)
	{
		TreeGraphItem *removed = (TreeGraphItem *)vlist_remove_first(m_ChildItemList);
		if (removed)
			delete removed;
		else
			break;
	}
	delete_vlist(m_ChildItemList);
	m_ChildItemList = 0;
	delete [] m_pItemText;
	delete [] m_pItemText2;
	if (m_pExtraData)
		m_pTreeGraph->DeleteItemFromHash(this);
}

TreeGraphItem::~TreeGraphItem()
{	
	if (m_ChildItemList)
		Flush();
}

void TreeGraphItem::SetData(const char *text, void *extradata, void *extradata2)
{
	m_pItemText = new char[strlen(text)+1];
	strcpy(m_pItemText, text);
	m_pExtraData = extradata;
	m_pExtraData2 = extradata2;
}


void TreeGraphItem::ModifyText(const char *text)
{
	if (m_pItemText)
	    delete [] m_pItemText;
 	m_pItemText = new char[strlen(text)+1];
	strcpy(m_pItemText, text);
}
void TreeGraphItem::ModifyText2(const char *text)
{
	if (m_pItemText2)
	    delete [] m_pItemText2;
 	m_pItemText2 = new char[strlen(text)+1];
	strcpy(m_pItemText2, text);
}


TreeGraphItem *TreeGraphItem::GetNextSibling()
{

	START_LIST_ITERATION(TreeGraphItem, m_pParentItem->m_ChildItemList)
		if (temp == this)
 			 return ((TreeGraphItem *)vlist_peek_cursor_next(m_pParentItem->m_ChildItemList));
	END_LIST_ITERATION(m_pParentItem->m_ChildItemList);
	return 0;
}

void TreeGraphItem::AddSiblingItem(TreeGraphItem *item)
{

	START_LIST_ITERATION(TreeGraphItem, m_pParentItem->m_ChildItemList)
		if (temp == this)
			vlist_add_after_cursor(m_pParentItem->m_ChildItemList, item);
 	END_LIST_ITERATION(m_pParentItem->m_ChildItemList);
}

void TreeGraphItem::AddChildItem(TreeGraphItem *item, bool insertlast)
{
	if (insertlast)
		vlist_add_last(m_ChildItemList, item);
	else
		vlist_add_first(m_ChildItemList, item);

	if (item->m_pExtraData)
		m_pTreeGraph->AddItemToHash(item);
//	Verify();
}
void TreeGraph::OnItemExpanding(TreeGraphItem *item, bool expand)
{
	if (m_pMessageTarget)
		m_pMessageTarget->OnItemExpanding(item, expand);
}

 
void TreeGraph::OnSelectionChanged(TreeGraphItem *item)
{
	if (m_pMessageTarget)
	    m_pMessageTarget->OnSelectionChanged(item);
}


void TreeGraph::OnImageClicked(TreeGraphItem *item) 
{
	if (m_pMessageTarget)
	    m_pMessageTarget->OnImageClicked(item);
}


void TreeGraph::OnTextModified(TreeGraphItem *item, const char * newtext)
{
	if (m_pMessageTarget)
	    m_pMessageTarget->OnTextModified(item, newtext);
}

void TreeGraph::OnBeforeTextModified(TreeGraphItem *item, const char * oldtext)
{
	if (m_pMessageTarget)
	    m_pMessageTarget->OnBeforeTextModified(item, oldtext);
}


TreeGraphItem* TreeGraphItem::AddSiblingItem(TCHAR *text, void *extradata, bool hasChildren)
{
	TreeGraphItem *item= new TreeGraphItem(m_pParentItem, m_pTreeGraph);
 	item->SetData(H_ASCII_TEXT(text), extradata);
	AddSiblingItem(item);
	return item;
}
	

TreeGraphItem* TreeGraphItem::AddChildItem(const TCHAR *text, void *extradata, bool insertlast)
{
	TreeGraphItem *item= new TreeGraphItem(this, m_pTreeGraph);
 	item->SetData(H_ASCII_TEXT(text), extradata);
	AddChildItem(item, insertlast);
	return item;
}
 			

TreeGraphItem *TreeGraphItem::GetLastChild()
{
	return ((TreeGraphItem *)vlist_peek_last(m_ChildItemList));
}
 		
 
void TreeGraphItem::DeleteChildItem(TreeGraphItem *item)
{
	if (vlist_remove(m_ChildItemList, item))
		delete item;
}
