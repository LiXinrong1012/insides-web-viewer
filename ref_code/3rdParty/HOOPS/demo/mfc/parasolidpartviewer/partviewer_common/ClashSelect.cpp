// ClashSelect.cpp : implementation file
//

#include "stdafx.h"
#include "partviewer_common\resource.h"

#include "ClashSelect.h"
#include "HSolidView.h"
#include "HSelectionSet.h"
#include "WindowsTreeGraph.h"
#include "HoopsSegmentTree.h"




BEGIN_MESSAGE_MAP(CSegSelectTreeCtrl,CTreeCtrl)
//{{AFX_MSG_MAP(CSegTreeCtrl)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
ON_WM_VSCROLL()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()






// ClashSelect dialog

IMPLEMENT_DYNAMIC(ClashSelect, CDialog)

ClashSelect::ClashSelect(CWnd* pParent /*=NULL*/,HSolidView *view)
	: CDialog(ClashSelect::IDD, pParent)
{	
	m_pView = view;
	m_bDialogActive = false;
}

ClashSelect::~ClashSelect()
{
	delete (m_pHoopsSegmentTree1->GetSelectionSet());
	delete (m_pHoopsSegmentTree2->GetSelectionSet());
	
	delete m_pHoopsSegmentTree1;
	delete m_pHoopsSegmentTree2;
	delete m_pWindowsTreeGraph1;
	delete m_pWindowsTreeGraph2;
}

void ClashSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
 }


BEGIN_MESSAGE_MAP(ClashSelect, CDialog)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_CLASH1SELECT_TREECTRL, OnItemexpandingTree1)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_CLASH2SELECT_TREECTRL, OnItemexpandingTree2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CLASH1SELECT_TREECTRL, OnSelchangedTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CLASH2SELECT_TREECTRL, OnSelchangedTree2)
	ON_WM_SIZE()

END_MESSAGE_MAP()




BOOL ClashSelect::OnInitDialog() 
{
	
	m_bDialogActive = true;
	CDialog::OnInitDialog();
	m_Select1Tree.SubclassDlgItem(IDC_CLASH1SELECT_TREECTRL,this);
	m_Select2Tree.SubclassDlgItem(IDC_CLASH2SELECT_TREECTRL,this);
	m_Select1Tree.SetID(IDC_CLASH1SELECT_TREECTRL);
	m_Select2Tree.SetID(IDC_CLASH2SELECT_TREECTRL);

	HSelectionSet *newselset1 = new HSelectionSet(m_pView);
	HC_KEY newstyle1 = HC_KOpen_Segment("/newstyle1");
  	newselset1->SetHighlightStyle(newstyle1);
 	newselset1->Init();
	newselset1->SetHighlightMode(HighlightQuickmoves);
	HPixelRGBA color;
	color.Set(255,0,0,0);
 	newselset1->SetSelectionFaceColor(color);
	
	m_pWindowsTreeGraph1 = new WindowsTreeGraph(&m_Select1Tree, 0);
	
	m_pHoopsSegmentTree1 = new HoopsSegmentTree(m_pView, m_pWindowsTreeGraph1);
	m_pHoopsSegmentTree1->SetSelectionSet(newselset1);
	m_pWindowsTreeGraph1->SetMessageTarget(m_pHoopsSegmentTree1);
 

	HSelectionSet *newselset2 = new HSelectionSet(m_pView);
	HC_KEY newstyle2 = HC_KOpen_Segment("/newstyle2");
  	newselset2->SetHighlightStyle(newstyle2);
 	newselset2->Init();
	newselset2->SetHighlightMode(HighlightQuickmoves);
 	color.Set(0,0,255,0);
 	newselset2->SetSelectionFaceColor(color);


	m_pWindowsTreeGraph2 = new WindowsTreeGraph(&m_Select2Tree, 0);
	m_pHoopsSegmentTree2 = new HoopsSegmentTree(m_pView, m_pWindowsTreeGraph2);
	m_pHoopsSegmentTree2->SetSelectionSet(newselset2);
	m_pWindowsTreeGraph2->SetMessageTarget(m_pHoopsSegmentTree2);

	
	m_imageState.Create( IDB_STATE, 16, 1, RGB(255,255,255) );
	m_Select1Tree.SetImageList( &(m_imageState), TVSIL_STATE );	
	m_Select2Tree.SetImageList( &(m_imageState), TVSIL_STATE );	

	return true;
}


//called whenever the expands a subtree for the first time
void ClashSelect::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_pWindowsTreeGraph1->OnItemexpanding(pNMHDR, pResult);
	return;
	 
}
//called whenever the expands a subtree for the first time
void ClashSelect::OnItemexpandingTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_pWindowsTreeGraph2->OnItemexpanding(pNMHDR, pResult);
	return;
	 
}
void ClashSelect::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_pWindowsTreeGraph1->OnSelchanged(pNMHDR, pResult);
	return;
	
}
void ClashSelect::OnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_pWindowsTreeGraph2->OnSelchanged(pNMHDR, pResult);
	return;
	
}
void ClashSelect::OnImageClicked(int id, HTREEITEM hti, long uFlags)
{
	if (id == IDC_CLASH1SELECT_TREECTRL)
		m_pWindowsTreeGraph1->OnImageClicked(hti, uFlags);
	else
		m_pWindowsTreeGraph2->OnImageClicked(hti, uFlags);
}

HSelectionSet * ClashSelect::GetSelectionSet1()
{
	 return m_pHoopsSegmentTree1->GetSelectionSet(); 
}
HSelectionSet * ClashSelect::GetSelectionSet2()
{
	 return m_pHoopsSegmentTree2->GetSelectionSet(); 
}

void ClashSelect::CleanTrees()
{
	m_pHoopsSegmentTree1->GetSelectionSet()->DeSelectAll();
	m_pHoopsSegmentTree2->GetSelectionSet()->DeSelectAll();
	m_pHoopsSegmentTree1->ValidateSegmentTree();
	m_pHoopsSegmentTree2->ValidateSegmentTree();
}


// ClashSelect message handlers
void ClashSelect::OnSize(UINT nType, int cx, int cy) 
{	
	CDialog::OnSize(nType, cx, cy); 
	if (cy<265)
		cy = 265;
	if (m_bDialogActive)
	{
		
		CWnd *wnd = GetDlgItem(IDC_CLASH1SELECT_TREECTRL);
		wnd->SetWindowPos(0, 15,30,(cx-0)/2-15,cy-60,0);   
		wnd = GetDlgItem(IDC_CLASH2SELECT_TREECTRL);
		wnd->SetWindowPos(0, 10 + (cx-0)/2,30,(cx-0)/2-15,cy-60, 0);   
		wnd = GetDlgItem(IDC_CLASHSELECT_PARTICIPANTS_STATIC);
		wnd->SetWindowPos(0, 5, 0,cx-5,cy-15, 0);   
		wnd = GetDlgItem(IDC_CLASHSELECT_PARTICIPANTS_TOOLS_STATIC);
		wnd->SetWindowPos(0, 10, 15,(cx-0)/2-5,cy-35, 0);   
		wnd = GetDlgItem(IDC_CLASHSELECT_PARTICIPANTS_TARGETS_STATIC);
		wnd->SetWindowPos(0, 13 + (cx-0)/2-5, 15,(cx-0)/2-10,cy-35, 0);   

	}
}



void CSegSelectTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{          
    
	UINT uFlags=0;
    HTREEITEM hti = HitTest(point,&uFlags);
    if (hti)
    {
		ClashSelect *owner = (ClashSelect *)GetOwner();
		if( uFlags & TVHT_ONITEMSTATEICON )
		{
			owner->OnImageClicked(m_id, hti, uFlags);
						
		}
	}
    CTreeCtrl::OnLButtonDown(nFlags, point);


}


 



//subclassing the tree control was necessary because we need to handle the scroll events
void CSegSelectTreeCtrl::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )

{
 	CTreeCtrl::OnVScroll( nSBCode, nPos, pScrollBar ); 
//	((CSegmentBrowserDlg *)GetParent())->ShowSelectedItems();	 
}

