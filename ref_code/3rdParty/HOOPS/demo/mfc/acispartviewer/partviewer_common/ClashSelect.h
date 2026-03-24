#pragma once
#include "afxcmn.h"

class WindowsTreeGraphItem;
class HSolidView;
class WindowsTreeGraph;
class HoopsSegmentTree;
class HSelectionSet;


class CSegSelectTreeCtrl : public CTreeCtrl
{
 
 	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );	
 	afx_msg void OnLButtonDown( UINT, CPoint );

	DECLARE_MESSAGE_MAP() 
	
public:
	void SetID(int id)
	{
		m_id = id;
	}

	int m_id;
};




// ClashSelect dialog

class ClashSelect : public CDialog
{
	DECLARE_DYNAMIC(ClashSelect)

public:
	ClashSelect(CWnd* pParent = NULL, HSolidView *view = 0);   // standard constructor
	virtual ~ClashSelect();

// Dialog Data
	enum { IDD = IDD_CLASH_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CImageList m_imageState;

 	HSolidView *m_pView;
	HoopsSegmentTree *m_pHoopsSegmentTree1;
	HoopsSegmentTree *m_pHoopsSegmentTree2;

	WindowsTreeGraph *m_pWindowsTreeGraph1;
	WindowsTreeGraph *m_pWindowsTreeGraph2;

	// Generated message map functions
	//{{AFX_MSG(ClashSelect)
	afx_msg BOOL OnInitDialog();
	afx_msg void OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandingTree2(NMHDR* pNMHDR, LRESULT* pResult);
 	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
 	afx_msg void OnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	
 

	DECLARE_MESSAGE_MAP()
public:
	void OnImageClicked(int id, HTREEITEM hti, long uFlags);
	HSelectionSet * GetSelectionSet1(); 
	HSelectionSet * GetSelectionSet2();
	CSegSelectTreeCtrl m_Select1Tree;
	CSegSelectTreeCtrl m_Select2Tree;

	void CleanTrees();
	bool m_bDialogActive;



};


