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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/TopolBrowserDlg.h,v 1.23 2008-04-24 03:57:21 chad Exp $
//

#if !defined(AFX_TOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)
#define AFX_TOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopolBrowserDlg.h : header file
//
#include "resource.h"


class CTopolBrowserDlg;
class HSolidView;

/////////////////////////////////////////////////////////////////////////////
// CTopolTreeCtrl window

class CTopolTreeCtrl : public CTreeCtrl
{
 
 	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );	
	DECLARE_MESSAGE_MAP()

		// In Granite, we have the biggest issue of smart pointers. I can't just cast 
		// the object pointers to DWORD and set the item data. To keep the KObj pointer
		// valid, I must have the reference. - Rajesh B


};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTopolBrowserDlg dialog

class CTopolBrowserDlg : public CDialog
{
// Construction
public:
	CTopolBrowserDlg(CWnd* pParent = NULL,HSolidView * View = 0);

	virtual bool HighlightSelection() = 0;
	virtual void ShowSelectedItems();

	void UpdateTopolBrowserCheckboxes();
	void ValidateTopolTree();

	CImageList m_imageState;

 // Dialog Data
#ifdef ACIS
	enum { IDD = IDD_TOPOLBROWSER1 };
#endif // ACIS

	//{{AFX_DATA(CTopolBrowserDlg)
	CListBox	m_TopInfoList;
	CListBox	m_infolist;
	HTREEITEM	m_rootitem;
	bool		m_dialogactive;
	BOOL	m_facevisibility;
	BOOL	m_edgevisibility;
	BOOL	m_bAlwaysZoom;
	CButton	m_TopologyBrowserSwitch;
	CButton	m_SegmentBrowserSwitch;
	CButton m_InterOpPartBrowserSwitch;
	//}}AFX_DATA
#ifdef ACIS
	BOOL	m_vertexvisibility;
#endif // ACIS


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopolBrowserDlg)
	public:
	 
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 	//}}AFX_VIRTUAL

// Implementation
protected:

	CWnd*			m_parent;	
	CTopolTreeCtrl	m_topol_tree;	
	HSolidView*		m_pHView;
	bool			m_bItemSelected;


#ifdef ACIS
	KERN_ATTDEF	m_name_attdef;
	virtual HTREEITEM InsertItemInTree(ENTITY* entity, char* basetext, HTREEITEM position){ assert(0); return 0;}
	virtual void UpdateInfoWindow(ENTITY* entity){ assert(0); }
	virtual void  FillItems(ENTITY* entity,HTREEITEM item){ assert(0); }
	bool  CheckSelection(ENTITY* entity);
#endif // ACIS


	bool  CheckSelection(long entity);

	// this function is basically your OnInitDialog into a separate function
	// it is need so that we can rebuild the topol tree if entites are added/deleted/changed
	virtual bool BuildTopolTree() = 0;

	// Generated message map functions
	//{{AFX_MSG(CTopolBrowserDlg)
	virtual BOOL OnInitDialog() = 0;
 	virtual afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnAnnotate() = 0;
	afx_msg void OnClose();
	virtual afx_msg void OnFacevisibility() = 0;
	afx_msg void OnEdgeVisibility();
	afx_msg void OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnZoomtoselection();
	afx_msg void OnAlwaysZoom();
	afx_msg void OnSegmentBrowserSwitch();
	afx_msg void OnInterOpPartBrowserSwitch();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
#ifdef ACIS
	afx_msg void OnVertexVisibility();
#endif

	DECLARE_MESSAGE_MAP()
};




  




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)
