#pragma once

class HSolidView;
class ClashItem;
class CSolidHoopsView;
// ClashDlg dialog
#include "HUIUtilityMFC.h"





class CMyListCtrl : public CListCtrl
{
public:
        CMyListCtrl();
        virtual ~CMyListCtrl() {};
        virtual void PreSubclassWindow();

        BOOL SortItems(int nColumn = -1, int nOrder = 1);

private:
        #define MAXCOLUMNS 32

        int             m_nSortColumn;
        int             m_pSortOrders[MAXCOLUMNS];

};


class ClashDlg : public CDialog
{
	DECLARE_DYNAMIC(ClashDlg)

public:
	ClashDlg(CWnd* pParent = NULL, HSolidView *view = 0);   // standard constructor
	virtual ~ClashDlg();
	void Init();
	void ColorButtonClicked(int id, float x, float y ,float z, bool undefine = false);	
	void CheckDisplaced();
 	HSolidView *m_pView;
	CSolidHoopsView *m_ParentView;

// Dialog Data
	enum { IDD = IDD_CLASHDLG };

protected:
 	CListBox	m_ClashListBox;
 	CMyListCtrl	m_ClashListCtrl;
	CTreeCtrl m_ClashItem1TreeCtrl;
	CTreeCtrl m_ClashItem2TreeCtrl;
	CButton m_Highlight1;
	CButton m_Highlight2;
	CButton m_Wireframe1;
	CButton m_Wireframe2;
	ClashItem *m_CurrentClashItem;
	CButton m_ZoomToClashCheck;
	CButton m_CalculateSoftClashesCheck;
	CButton m_ExtraPrecisionCheck;
 	CButton m_HideOthersRadio;
	CButton m_DefaultRadio;
	CButton m_DimOthersRadio;
 	CColorBtn	m_Color1;	 
	CColorBtn	m_Color2;	 
	HPoint m_Color1Value;
	HPoint m_Color2Value;
	bool m_Color1ValueDefined;
	bool m_Color2ValueDefined;
	HC_KEY m_tempdisplaced1;
	HC_KEY m_tempdisplaced2;
	bool m_bDialogActive;
	bool m_InInit;



 	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HTREEITEM AddItem(CTreeCtrl *treectrl, HTREEITEM parent, const wchar_t *text);
	void ShowClashTreeView(CTreeCtrl *treectrl, HC_KEY shellkey);
	void SelectClashEntities(ClashItem *ci);
	HC_KEY	GetSelectedEntitySegment(HC_KEY key);
 
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedClash1Treectrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeClashlist();
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBnClickedSelectClashParticipants();
	afx_msg void OnBnClickedShowClashItem1Check();
	afx_msg void OnBnClickedShowClashItem2Check();
	afx_msg void OnBnClickedWireframeItem1Check();
	afx_msg void OnBnClickedWireframeItem2Check();
	afx_msg void OnBnClickedZoomToClashCheck();
 	afx_msg void OnBnClickedShowallclashesButton();
	afx_msg void OnBnClickedShowsoftclashesButton();
	afx_msg void OnBnClickedShowhardclashesButton();
	afx_msg void OnBnClickedUnhighlightclashButton();
	afx_msg void OnBnClickedDefaultRadio();
	afx_msg void OnBnClickedDimothersRadio();
	afx_msg void OnBnClickedHideothersRadio();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnColumnclickMylistctrl(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg void OnLvnItemchangedClashListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateClashListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRecalculateClashButton();
	afx_msg LRESULT OnClashThreadCompleted(WPARAM wParam, LPARAM lParam);


};
