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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CModelBrowserDlg.h,v 1.6 2009-11-11 21:13:58 guido Exp $
//

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ModelBrowserDlg.h : header file
//
#include "resource.h"
#include <map>
#include <vector>
#include <string>

class CModelBrowserDlg;

/////////////////////////////////////////////////////////////////////////////
// CModelTreeCtrl window

class CModelTreeCtrl : public CTreeCtrl
{
	DECLARE_MESSAGE_MAP()
public:
 	afx_msg void OnDestroy();
protected:
	void Clean(HTREEITEM ti);
};

typedef struct _GROUP_NODE
{
	std::wstring name;
	HTREEITEM me;
}GROUP_NODE;

typedef struct _BLOCK_REF_NODE
{
	std::wstring name;
	HTREEITEM me;
}BLOCK_REF_NODE;

typedef struct _LAYER_NODE
{
	std::wstring name;
	HTREEITEM me;
	std::vector<BLOCK_REF_NODE*> blk_list;
	std::vector<GROUP_NODE*> grp_list;
}LAYER_NODE;

typedef struct _FILE_NODE
{
	std::wstring name;
	HTREEITEM me;
	HC_KEY my_segment;
	std::vector<LAYER_NODE*> lay_list;
	std::vector<GROUP_NODE*> grp_list;
}FILE_NODE;


 /////////////////////////////////////////////////////////////////////////////
// CModelBrowserDlg dialog

class CModelBrowserDlg : public CDialog
{

public:
	CModelBrowserDlg(CWnd* pParent = NULL, HBaseView * View = 0, wchar_t * extension=NULL);   // standard constructor
	~CModelBrowserDlg();
	void ShowSelectedItems();
	void ValidateModelTree();

	// Dialog Data
	enum { IDD = IDD_MODELBROWSER };

	//{{AFX_DATA(CModelBrowserDlg)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelBrowserDlg)
public:
	 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 	//}}AFX_VIRTUAL

// Implementation
protected:

	CWnd*			m_parent;	
	CModelTreeCtrl	m_model_tree;
	CString			m_properties;
	CImageList		m_image_list;

	HBaseView*		m_pHView;
	bool			m_dialogactive;
	bool			m_is_first_selection;
	HTREEITEM		m_last_selection;
	bool			m_bSuppressShowSelectedItems;
	bool build_model_tree();
	long insert_item(HC_KEY segment_key, HTREEITEM parent);
	bool update_properties_display(HQualifiedKey  *qualified_key);
	void show_if_selected(HTREEITEM item, struct vhash_s* selected_keys);
	// Generated message map functions
	//{{AFX_MSG(CModelBrowserDlg)
	virtual BOOL OnInitDialog();
	HQualifiedKey * Select(HTREEITEM item);

 	virtual afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	HC_KEY	m_IncludeTemp[128];
	int		m_IncludeCount;
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	wchar_t * m_pFileExtension;
	wchar_t * m_pCurrentFile;
	std::multimap<std::wstring, FILE_NODE*> m_tree_data;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
