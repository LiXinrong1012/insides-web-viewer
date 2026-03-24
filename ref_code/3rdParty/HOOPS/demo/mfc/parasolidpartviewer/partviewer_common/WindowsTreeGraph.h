// WindowsTreeGraph.h: interface for the WindowsTreeGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWSTREEGRAPH_H__4205D8E2_7380_49CA_921F_10BB1505E06E__INCLUDED_)
#define AFX_WINDOWSTREEGRAPH_H__4205D8E2_7380_49CA_921F_10BB1505E06E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeGraph.h"
class WindowsTreeGraphItem;


class WindowsTreeGraph : public TreeGraph
{
public:
	WindowsTreeGraph(CTreeCtrl *treectrl, CListBox *infobox);
 	CTreeCtrl*m_pTreeCtrl;
	CListBox *m_pInfoBox;
	// Generated message map functions
	//{{AFX_MSG(TTTDLG)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	void OnImageClicked(HTREEITEM hti, long uFlags);
	void Flush();
	void ResetInfoContent();
	void AddInfoString(char *text);
	

 

};


class WindowsTreeGraphItem : public TreeGraphItem
{
public:
	WindowsTreeGraphItem(TreeGraphItem *parentItem, TreeGraph *parentControl, HTREEITEM item = 0) : TreeGraphItem(parentItem, parentControl)
	{
		m_TreeItem = item;
	}

 
	virtual ~WindowsTreeGraphItem();

	void SetTreeItem(HTREEITEM item)
	{
		m_TreeItem = item;
	}

	virtual TreeGraphItem * AddChildItem(const TCHAR *text, void *extradata, bool InsertLast = true);
	virtual TreeGraphItem * AddSiblingItem(TCHAR *text, void *extradata, bool InsertLast = true);

	void SetupItemStruct(TVINSERTSTRUCT &is, WindowsTreeGraphItem *parent, HTREEITEM insertafter,
						 bool children, const TCHAR *text, void *extradata);


// 	virtual void Verify();
	virtual void ModifyText(const char *text);
	virtual void DeleteChildItem(TreeGraphItem *item);
	virtual void SetHasChildren(bool hasChildren);
	virtual void SetBold(bool bold = true);
	virtual void SetSelected(bool selected = true);
	virtual void SetImage(int checked);
	virtual bool IsExpanded();
	virtual void Expand();
	virtual void UnExpand();
	virtual void EditInPlace();



	HTREEITEM m_TreeItem;
};


#endif // !defined(AFX_WINDOWSTREEGRAPH_H__4205D8E2_7380_49CA_921F_10BB1505E06E__INCLUDED_)
