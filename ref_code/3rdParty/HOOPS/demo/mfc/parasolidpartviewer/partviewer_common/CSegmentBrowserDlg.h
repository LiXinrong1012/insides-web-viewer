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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSegmentBrowserDlg.h,v 1.66 2009-10-16 21:49:45 nathan Exp $
//

#if !defined(AFX_SegmentBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)
#define AFX_SegmentBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SegmentBrowserDlg.h : header file
//
#include "resource.h"
#include "HSolidView.h"
#include "HBaseModel.h"
#include "WindowsTreeGraph.h"
#include "vhash.h"
class CSegmentBrowserDlg;
class HBaseView;
class HoopsSegmentTree;
class WindowsTreeGraphItem;
/////////////////////////////////////////////////////////////////////////////
// CSegTreeCtrl window

class CSegTreeCtrl : public CTreeCtrl
{
 
 	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );	
 	afx_msg void OnLButtonDown( UINT, CPoint );
 	afx_msg void OnLButtonDblClk( UINT, CPoint );
 	afx_msg void OnRButtonDown( UINT, CPoint );
 	afx_msg void OnColorAttribute();
 	afx_msg void OnHeuristicAttribute();
 	afx_msg void OnVariableEdgeWeightAttribute();
 	afx_msg void OnLinePatternAttribute();
 	afx_msg void OnFacePatternAttribute();
 	afx_msg void OnMarkerSymbolAttribute();
 	afx_msg void OnEdgeWeightAttribute();
 	afx_msg void OnWindowPatternAttribute();
 	afx_msg void OnWindowAttribute();
 	afx_msg void OnVariableLineWeightAttribute();
 	afx_msg void OnLineWeightAttribute();
 	afx_msg void OnMarkerSizeAttribute();
 	afx_msg void OnConditionAttribute();
 	afx_msg void OnTextAlignmentAttribute();
 	afx_msg void OnVariableMarkerSizeAttribute();
  	afx_msg void OnSelectabilityAttribute();
 	afx_msg void OnVisibilityAttribute();
 	afx_msg void OnRenderingOptionsAttribute();
 	afx_msg void OnCameraAttribute();
 	afx_msg void OnModellingMatrixAttribute();
 	afx_msg void OnUserOptionsAttribute();
	afx_msg void OnUnicodeOptionsAttribute();

	afx_msg void OnTextFontAttribute();
 	afx_msg void OnDriverOptionsAttribute();
 	afx_msg void OnSystemOptionsAttribute();
 	afx_msg void OnShowColorAttribute();
  	afx_msg void OnShowSelectabilityAttribute();
 	afx_msg void OnShowVisibilityAttribute();
 	afx_msg void OnShowRenderingOptionsAttribute();
 	afx_msg void OnShowCameraAttribute();
 	afx_msg void OnShowModellingMatrixAttribute();
 	afx_msg void OnShowUserOptionsAttribute();
	afx_msg void OnShowUnicodeOptionsAttribute();

 	afx_msg void OnShowTextFontAttribute();
 	afx_msg void OnShowDriverOptionsAttribute();
 	afx_msg void OnShowSystemOptionsAttribute();
 	afx_msg void OnHandednessAttribute();
 	afx_msg void OnShowHandednessAttribute();
 	afx_msg void OnShowHeuristicAttribute();
 	afx_msg void OnShowSubwindowAttribute();
 	afx_msg void OnShowClipRegionAttribute();
 	afx_msg void OnShowBounding();
 	afx_msg void OnUndefineAttribute();
 	afx_msg void OnEditInPlace();
	afx_msg void OnDeleteSegment();
	afx_msg void OnFlushSegmentContents();
	afx_msg void OnOptimize();
	afx_msg void OnLoadIntoSegment();
	afx_msg void OnCreateSegment();
	afx_msg void OnActivateManipulator();
 	afx_msg void OnZoomToSegment();
	afx_msg void OnCutSegment();
	afx_msg void OnPasteSegment();
	afx_msg void OnSaveToHMF();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

		// In Granite, we have the biggest issue of smart pointers. I can't just cast 
		// the object pointers to DWORD and set the item data. To keep the KObj pointer
		// valid, I must have the reference. - Rajesh B

#ifdef GRANITE
		KObjList_ptr m_KObjTreeItems;
public:

 
	CSegTreeCtrl()
	{
		m_KObjTreeItems = KObjList::create();
	}
	virtual BOOL SetItemData( HTREEITEM item, KObj_ptr object)
	{
		assert( object );
		assert( m_KObjTreeItems );
		m_KObjTreeItems->append( object );
		
		return CTreeCtrl::SetItemData(item, (DWORD)((KObj*)object));
	}

	virtual BOOL SetItemData( HTREEITEM item, DWORD dword)
	{
		return CTreeCtrl::SetItemData(item, dword);
	}

#endif
	WindowsTreeGraphItem *m_pItemUnderCursor;
	void LoadFile( LPCTSTR csFilePathName, HStreamFileToolkit* tk);
	HFileInputResult Read(const char * FileName);
    
	void ShowText(const char *text);

	void FindItemUnderCursor(UINT nFlags, CPoint point);


};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSegmentBrowserDlg dialog

class CSegmentBrowserDlg : public CDialog, public WindowsTreeGraph
{
// Construction
public:
	CSegmentBrowserDlg(CWnd* pParent = NULL,HBaseView * View = 0);   // standard constructor
	CSegmentBrowserDlg::~CSegmentBrowserDlg();
 
//	bool HighlightSelection();
	void UpdateSegmentBrowserCheckboxes();
	HTREEITEM	m_GeometryItem;
	TVITEM		m_SelectedTreeItem;
	void  ShowSelectedItems();
	 void UpdateVisibleItems();
	void ValidateSegmentTree();
	void ValidateSegment(HC_KEY segkey);
	void RefreshBrowser();
	HoopsSegmentTree *GetHoopsSegmentTree() { return m_pHoopsSegmentTree; }
	HBaseView * GetHoopsView() { return m_pHView; }

	enum SearchScope
	{
		Error=0,
		Attribute,
		Geometry,
		Segment,
		Include,
		Style,
		SegmentReference,
		GeometryReference,
		Definition,
		Keys
	};

 // Dialog Data
	//{{AFX_DATA(CSegmentBrowserDlg)
	enum { IDD = IDD_SEGMENTBROWSER };
	CButton	m_SearchButton;
	CButton	m_TopologyBrowserSwitch;
	CButton	m_SegmentBrowserSwitch;
	CButton m_InterOpPartBrowserSwitch;
 	CListBox	m_TopInfoList;
	HTREEITEM	m_rootitem;
	bool		m_dialogactive;
	CString	m_SearchEdit;
	CString m_csSearchScope;
	SearchScope m_SearchScope;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSegmentBrowserDlg)
	public:
	 
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 	//}}AFX_VIRTUAL

// Implementation
		CImageList m_imageState;

protected:

	HoopsSegmentTree *m_pHoopsSegmentTree;

	CWnd		*m_parent;	
	CSegTreeCtrl m_Segment_tree;
	CSegTreeCtrl	m_GeometryTree;	
	HBaseView * m_pHView;
 	bool		m_bNoupdate;
	bool		m_bItemSelected;
	HC_KEY		m_baseKey;
	bool		m_blockValidation;
	HTREEITEM	InsertSegmentList(HC_KEY segkey,HTREEITEM item);
	HTREEITEM	InsertItemInTree(HC_KEY key, HTREEITEM position, CTreeCtrl *TreeCtrl);
	HTREEITEM	InsertGeometryList(HC_KEY segkey,HTREEITEM item);
	void		SetAttributeTextBox(HC_KEY key);
	void		UpdateInfoWindow(bool redraw=true);
	
//	virtual void UpdateInfoWindow(PK_ENTITY_t entity) = 0;
//	virtual void  FillItems(PK_ENTITY_t entity,HTREEITEM item) = 0;
//	bool  CheckSelection(PK_ENTITY_t entity);
	bool ShowItemExistence(HTREEITEM item);
	void ValidateSegmentTreeInternal(HTREEITEM parentitem, HC_KEY parentkey);
	HTREEITEM FindItemBySegmentKey(HC_KEY segkey, HTREEITEM item);

	 void ExpandSelection();

	int m_segmentCountMax;
	HC_KEY * m_pSegmentList;
	bool first_run;


	// Generated message map functions
	//{{AFX_MSG(CSegmentBrowserDlg)
	afx_msg void OnOK();
	afx_msg void OnCancel();
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
	afx_msg void OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSegmentBrowserCut();
	afx_msg void OnSegmentBrowserPaste();
	afx_msg void OnSegmentBrowserModifySegment();
	afx_msg void OnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeStartsegmentCombo();
	afx_msg void OnRefreshBrowser();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTopologyBrowserSwitch();
	afx_msg void OnInterOpPartBrowserSwitch();
	afx_msg void OnSearch();
	afx_msg	void OnPopulateInfo();
	afx_msg void OnUpdateBoundings();
	afx_msg	void OnSelchangeSearchScope();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SegmentBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

class CCMMDisplay : public CDialog, public HAnimationListener
{
public:
	CCMMDisplay(CWnd* pParent, HBaseView * View);   // standard constructor
	~CCMMDisplay();

	enum { IDD = IDD_CMM_DISPLAY };

	bool InsertCollision(HC_KEY const key, HPointKey const & point, int current_tick);
	void RemoveCollision(HC_KEY const key);
	void RemoveCollision(HC_KEY const key, HPointKey const & point);
	bool CollisionInTree(HC_KEY const key, HPointKey const & point);
	int ObjectCollisionEvent(HBhvTargetObject *tob);
	afx_msg void OnBnClickedCmmClearDisplay();
	afx_msg void OnListItemDblClk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//CMMTreeCtrl * m_pTree;
	//HTREEITEM m_Root;
	//CKeyTreeMap m_CollisionMap;
	HBaseView * m_pView;
	CListBox m_InfoList;

	afx_msg void OnClear();
 	afx_msg void OnClose();
	VHash<float, int> m_hash;
 
	DECLARE_MESSAGE_MAP()
};
