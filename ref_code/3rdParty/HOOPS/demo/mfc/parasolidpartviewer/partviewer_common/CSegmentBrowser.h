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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSegmentBrowser.h,v 1.6 2006-08-07 20:38:55 stage Exp $
//

#if !defined(AFX_SegmentBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_RAJESH_B__)
#define AFX_SegmentBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_RAJESH_B__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SegmentBrowserDlg.h : header file
//
#include "resource.h"
#include "HBaseView.h"
#include "HSolidModel.h"

/////////////////////////////////////////////////////////////////////////////
// CSegTreeCtrl window

class CSegmentBrowser;
class HBaseView;
struct vlist_s;
/////////////////////////////////////////////////////////////////////////////
// CSegmentBrowser dialog

class CSegmentBrowser
{
// Construction
public:
	CSegmentBrowser(CWnd* pParent, CListBox* pTopInfoList, CTreeCtrl* pSegTreeCtrl, HBaseView * View = 0);   // standard constructor
	
	void UpdateSegmentBrowserCheckboxes();
	HTREEITEM	m_GeometryItem;
	TVITEM		m_SelectedTreeItem;
	void  ShowSelectedItems();
	 void UpdateVisibleItems();
	void ValidateSegmentTree();
	void HighlightSelectedItems();
	void HighlightSelectedItems(HTREEITEM hItem, HC_KEY key);


// // Dialog Data
//	//{{AFX_DATA(CSegmentBrowser)
//	enum { IDD = IDD_SEGMENTBROWSER };
//	CListBox*	m_TopInfoList;
	HTREEITEM	m_rootitem;
	bool		m_dialogactive;
//	//}}AFX_DATA

// Overrides
//	// ClassWizard generated virtual function overrides
//	//{{AFX_VIRTUAL(CSegmentBrowser)
//	public:
//	 
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
// 	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd		*m_parent;	
	CTreeCtrl*	m_Segment_tree;
//	CSegTreeCtrl	m_GeometryTree;	
	HBaseView	*m_pHView;
 	bool		m_bNoupdate;
	bool		m_bItemSelected;
	HC_KEY		m_baseKey;
	bool		m_blockValidation;
	HTREEITEM	InsertSegmentList(HC_KEY segkey,HTREEITEM item);
	HTREEITEM	InsertItemInTree(HC_KEY key, HTREEITEM position, CTreeCtrl *TreeCtrl);
	HTREEITEM	InsertGeometryList(HC_KEY segkey,HTREEITEM item);
	void		SetAttributeTextBox(HC_KEY key);
	
	bool ShowItemExistence(HTREEITEM item);
	void ValidateSegmentTreeInternal(HTREEITEM parentitem, HC_KEY parentkey);
	void ExpandSelection();

	int m_segmentCountMax;
	HC_KEY * m_pSegmentList;
	bool first_run;

public:

	void GetSelectedShells(HTREEITEM item, vlist_s* retSelectedShells);
	HC_KEY GetSelection(HTREEITEM item);

	void ItemSweetened(HTREEITEM item, bool recurse = true);

//	// Generated message map functions
//	//{{AFX_MSG(CSegmentBrowser)
	afx_msg BOOL OnInitDialog();
 	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
 	afx_msg void OnClose();
  	afx_msg void OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandingTree2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandedTree2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteSelection();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
 	afx_msg void OnSegmentbrowserrefresh();
	afx_msg void OnExpandfullpath();
	afx_msg void OnExpandSelection();
	afx_msg void OnDestroy();
	afx_msg void OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult);
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SegmentBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_RAJESH_B__)
