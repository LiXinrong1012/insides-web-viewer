// ClashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ClashDlg.h"
#include "HSolidView.h"
#include "HSelectionSet.h"
#include "HUtilityLocaleString.h"
#include "vlist.h"
#include "CSolidHoopsView.h"
#include "CSolidHoopsFrm.h"
#include "ClashSelect.h"
#ifndef GRANITE
#include <afxpriv.h>
#endif

// ClashDlg dialog

IMPLEMENT_DYNAMIC(ClashDlg, CDialog)

ClashDlg::ClashDlg(CWnd* pParent /*=NULL*/,HSolidView *view)
	: CDialog(ClashDlg::IDD, pParent)
{
	m_pView = view;
	m_ParentView = (CSolidHoopsView *)pParent;
	m_CurrentClashItem = 0;
	m_Color1Value.Set(1,1,1);
	m_Color2Value.Set(1,1,1);
	m_Color1ValueDefined = false;
	m_Color2ValueDefined = false;
	m_tempdisplaced1 = -1;
	m_tempdisplaced2 = -1;
	m_bDialogActive = false;


}

 

ClashDlg::~ClashDlg()
{
}

void ClashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSegmentBrowserDlg)
  	DDX_Control(pDX, IDC_CLASHLIST, m_ClashListBox);
  	DDX_Control(pDX, IDC_CLASH_LISTCTRL, m_ClashListCtrl);
	DDX_Control(pDX, IDC_CLASH1_TREECTRL, m_ClashItem1TreeCtrl);
	DDX_Control(pDX, IDC_CLASH2_TREECTRL, m_ClashItem2TreeCtrl);
	DDX_Control(pDX, IDC_SHOW_CLASH_ITEM1_CHECK, m_Highlight1);
	DDX_Control(pDX, IDC_SHOW_CLASH_ITEM2_CHECK, m_Highlight2);
	DDX_Control(pDX, IDC_WIREFRAME_ITEM1_CHECK, m_Wireframe1);
	DDX_Control(pDX, IDC_WIREFRAME_ITEM2_CHECK, m_Wireframe2);
	DDX_Control(pDX, IDC_ZOOM_TO_CLASH_CHECK, m_ZoomToClashCheck);
	DDX_Control(pDX, IDC_CALCULATE_SOFT_CLASHES_CHECK, m_CalculateSoftClashesCheck);
	DDX_Control(pDX, IDC_EXTRA_PRECISION_CHECK, m_ExtraPrecisionCheck);
 	DDX_Control(pDX, IDC_HIDEOTHERS_RADIO, m_HideOthersRadio);
	DDX_Control(pDX, IDC_DIMOTHERS_RADIO, m_DimOthersRadio);
	DDX_Control(pDX, IDC_DEFAULT_RADIO, m_DefaultRadio);
	DDX_Control(pDX, IDC_BUTTON_CLASHITEM1_COLOR, m_Color1);
	DDX_Control(pDX, IDC_BUTTON_CLASHITEM2_COLOR, m_Color2);

 	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ClashDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CLASH1_TREECTRL, &ClashDlg::OnTvnSelchangedClash1Treectrl)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_CLASH_LISTCTRL, OnColumnclickMylistctrl) 
	ON_LBN_SELCHANGE(IDC_CLASHLIST, &ClashDlg::OnLbnSelchangeClashlist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CLASH_LISTCTRL, &ClashDlg::OnLvnItemchangedClashListctrl)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_CLASH_LISTCTRL, &ClashDlg::OnLvnItemActivateClashListctrl)
	ON_BN_CLICKED(IDC_SHOW_CLASH_ITEM1_CHECK, &ClashDlg::OnBnClickedShowClashItem1Check)
	ON_BN_CLICKED(IDC_SHOW_CLASH_ITEM2_CHECK, &ClashDlg::OnBnClickedShowClashItem2Check)
	ON_BN_CLICKED(IDC_WIREFRAME_ITEM1_CHECK, &ClashDlg::OnBnClickedWireframeItem1Check)
	ON_BN_CLICKED(IDC_WIREFRAME_ITEM2_CHECK, &ClashDlg::OnBnClickedWireframeItem2Check)
	ON_BN_CLICKED(IDC_ZOOM_TO_CLASH_CHECK, &ClashDlg::OnBnClickedZoomToClashCheck)
 	ON_BN_CLICKED(IDC_SHOWALLCLASHES_BUTTON, &ClashDlg::OnBnClickedShowallclashesButton)
	ON_BN_CLICKED(IDC_SHOWSOFTCLASHES_BUTTON, &ClashDlg::OnBnClickedShowsoftclashesButton)
	ON_BN_CLICKED(IDC_SHOWHARDCLASHES_BUTTON, &ClashDlg::OnBnClickedShowhardclashesButton)
	ON_BN_CLICKED(IDC_UNHIGHLIGHT_CLASH_BUTTON, &ClashDlg::OnBnClickedUnhighlightclashButton)
	ON_BN_CLICKED(IDC_DEFAULT_RADIO, &ClashDlg::OnBnClickedDefaultRadio)
	ON_BN_CLICKED(IDC_DIMOTHERS_RADIO, &ClashDlg::OnBnClickedDimothersRadio)
	ON_BN_CLICKED(IDC_HIDEOTHERS_RADIO, &ClashDlg::OnBnClickedHideothersRadio)
	ON_BN_CLICKED(IDC_RECALCULATE_CLASH_BUTTON, &ClashDlg::OnBnClickedRecalculateClashButton)
	ON_BN_CLICKED(IDC_SELECT_CLASH_PARTICIPANTS_BUTTON, &ClashDlg::OnBnClickedSelectClashParticipants)
	ON_WM_SIZE()
 	ON_MESSAGE(WM_CLASHTHREADCOMPLETED,OnClashThreadCompleted)

END_MESSAGE_MAP()







// ClashDlg message handlers

void ClashDlg::ShowClashTreeView(CTreeCtrl *treectrl, HC_KEY shellkey)
{
	int num = 0;
	HC_KEY keypathlist[256];
	keypathlist[num++] = shellkey;
	HC_KEY currentkey = HC_KShow_Owner_By_Key(shellkey);
	while (1)
	{
		keypathlist[num++] = currentkey;
		if (currentkey == m_pView->GetModelKey())
			break;
		currentkey = HC_KShow_Owner_By_Key(currentkey);
	}
	HTREEITEM parent = 0;
	char text[4096];
	for (int i=num-1;i>=0;i--)
	{
		if (i>0)
		{
			HC_Show_Segment( keypathlist[i], text);
			HC_Parse_String(text,"/",-1,text);
		}
		else
			sprintf(text,"%d", keypathlist[i]);
 		parent = AddItem(treectrl,parent, H_UNICODE_TEXT(text));
	}
}

		
HC_KEY ClashDlg::GetSelectedEntitySegment(HC_KEY key)
{
	HC_KEY refkey;
	HC_KEY reskey = -1;

	HC_Open_Segment_By_Key(m_pView->GetSelection()->GetSelectionSegment());
 	HC_Begin_Contents_Search("...", "references");
	while (HUtility::FindContents(refkey))
	{
		HC_KEY reftokey = HC_KShow_Reference_Geometry(refkey);
		if (reftokey == key)
			reskey = HC_KShow_Owner_By_Key(refkey);
 	}
	HC_End_Contents_Search();
	HC_Close_Segment();
 	return reskey;
 }

void ClashDlg::CheckDisplaced()
{
	if (m_tempdisplaced1 != -1)
	{
		HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(HC_KShow_Owner_By_Key(m_tempdisplaced1)));		
 		HC_Move_By_Key(m_tempdisplaced1,".");
		HC_Delete_Segment("clashtemp");
 		HC_Close_Segment();
		m_tempdisplaced1 = -1;
	}
	if (m_tempdisplaced2 != -1)
	{
		HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(HC_KShow_Owner_By_Key(m_tempdisplaced2)));		
 		HC_Move_By_Key(m_tempdisplaced2,".");
		HC_Delete_Segment("clashtemp");
 		HC_Close_Segment();
		m_tempdisplaced2 = -1;
	}
}
 		



void ClashDlg::SelectClashEntities(ClashItem *ci)
{
	CheckDisplaced();
	HSelectionSet *selset = m_pView->GetSelection();
 	HC_Open_Segment("/style library/mvo_transparent_highlight_style");
			if (HC_Show_Existence("visibility"))
				HC_UnSet_Visibility();
		HC_Close_Segment();
		HC_Open_Segment_By_Key(m_pView->GetOverwriteKey());
 		HC_Open_Segment("selectionconditionincluder");
			if (HC_Show_Existence("visibility"))
				HC_UnSet_Visibility();
		HC_Close_Segment();
		HC_Close_Segment();
 	if (ci)
	{
		selset->DeSelectAll();
		HC_KEY modelkey = m_pView->GetIncludeLinkKey();
		if (m_Highlight1.GetState() & 0x003)
		{
			selset->Select(ci->m_shell1,1,&modelkey);
			if (m_Wireframe1.GetState() & 0x003)
			{
				HC_Open_Segment_By_Key(GetSelectedEntitySegment(ci->m_shell1));
				HC_Set_Visibility("faces = off, edges = on");
				HC_Set_Rendering_Options("attribute lock = visibility");
				HC_Close_Segment();
  				if (selset->GetHighlightMode()!=InverseTransparency
					|| selset->GetHighlightMode()!=ColoredInverseTransparency)
				{
					HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(ci->m_shell1));
					HC_Open_Segment("clashtemp");
					HC_Move_By_Key(ci->m_shell1,".");
					HC_Set_Visibility("off");
					HC_Close_Segment();
					HC_Close_Segment();
					m_tempdisplaced1 = ci->m_shell1;
				}
			}
			if (m_Color1ValueDefined)
			{
				HC_Open_Segment_By_Key(GetSelectedEntitySegment(ci->m_shell1));
				HC_Set_Color_By_Value("faces,edges", "rgb", m_Color1Value.x,
					m_Color1Value.y,m_Color1Value.z);
				HC_Set_Rendering_Options("attribute lock = color");
				HC_Close_Segment();
			}

		}

		if (m_Highlight2.GetState() & 0x003)
		{
			selset->Select(ci->m_shell2,1,&modelkey);

			if (m_Wireframe2.GetState() & 0x003)
			{
				HC_Open_Segment_By_Key(GetSelectedEntitySegment(ci->m_shell2));
				HC_Set_Visibility("faces = off, edges = on");
				HC_Set_Rendering_Options("attribute lock = visibility");
				HC_Close_Segment();
  				if (selset->GetHighlightMode()!=InverseTransparency
					|| selset->GetHighlightMode()!=ColoredInverseTransparency)
				{
					HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(ci->m_shell2));
					HC_Open_Segment("clashtemp");
					HC_Move_By_Key(ci->m_shell2,".");
					HC_Set_Visibility("off");
					HC_Close_Segment();
					HC_Close_Segment();
					m_tempdisplaced2 = ci->m_shell2;
				}

			}
			if (m_Color2ValueDefined)
			{
				HC_Open_Segment_By_Key(GetSelectedEntitySegment(ci->m_shell2));
				HC_Set_Color_By_Value("face,edges", "rgb", m_Color2Value.x,
					m_Color2Value.y,m_Color2Value.z);
				HC_Set_Rendering_Options("attribute lock = color");
				HC_Close_Segment();
			}

		}
 	 	HC_Open_Segment("/style library/mvo_transparent_highlight_style");
		if (m_HideOthersRadio.GetState() & 0x003)
		{
			HC_Set_Visibility("off");			
		}
		else
		{
			if (HC_Show_Existence("visibility"))
				HC_UnSet_Visibility();
		}
		HC_Close_Segment();
		HC_Open_Segment_By_Key(m_pView->GetOverwriteKey());
 		HC_Open_Segment("selectionconditionincluder");
		if (m_HideOthersRadio.GetState() & 0x003)
		{
			HC_Set_Visibility("off");			
		}
		else
		{
			if (HC_Show_Existence("visibility"))
				HC_UnSet_Visibility();
		}
		HC_Close_Segment();
		HC_Close_Segment();
 		m_pView->Update();
	}
}

void ClashDlg::OnLvnItemchangedClashListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_InInit)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
 		int index = m_ClashListCtrl.GetSelectionMark();
		index = pNMLV->iItem;
		if (index != -1 && pNMLV->uNewState)
		{
			int cnum = 0;
			ClashItem *clashitem = 0;
			CString test = m_ClashListCtrl.GetItemText(index,0);
			index = _ttoi(test);
 			START_LIST_ITERATION(ClashItem, m_pView->m_ClashList);
			
			if (cnum==index)
			{
				clashitem = temp;
				break;
			}
			cnum++;
			END_LIST_ITERATION(m_pView->m_ClashList);

  			m_ClashItem1TreeCtrl.DeleteAllItems();
			m_ClashItem2TreeCtrl.DeleteAllItems();
			ShowClashTreeView(&m_ClashItem1TreeCtrl,clashitem->m_shell1);
			ShowClashTreeView(&m_ClashItem2TreeCtrl,clashitem->m_shell2);
			SelectClashEntities(clashitem);
			m_CurrentClashItem = clashitem;
			if (m_ZoomToClashCheck.GetState() & 0x003)
				m_pView->FitSelection();		
		}
	}
	*pResult = 0;
}

void ClashDlg::OnLvnItemActivateClashListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
//	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
 	*pResult = 0;
}

void ClashDlg::OnLbnSelchangeClashlist()
{
  
}

// ClashDlg message handlers

void ClashDlg::OnTvnSelchangedClash1Treectrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}





HTREEITEM ClashDlg::AddItem(CTreeCtrl *treectrl, HTREEITEM parent, const wchar_t *text)
{
 	TVINSERTSTRUCT is;
 	is.hParent = parent;
	
 	is.hInsertAfter=TVI_FIRST;
	is.item.mask=TVIF_CHILDREN | TVIF_TEXT | TVIF_PARAM;
	is.item.cChildren = true;
	is.item.pszText=(LPWSTR)text;


	HTREEITEM ti = treectrl->InsertItem(&is);
	TVITEM pitem;
	pitem.hItem = ti;
	pitem.mask=TVIF_CHILDREN | TVIF_HANDLE;

	pitem.cChildren = true;
	treectrl->SetItem(&pitem);
	treectrl->SetItemState(ti,TVIS_EXPANDED, TVIS_EXPANDED);
	return ti;

}



BOOL ClashDlg::OnInitDialog() 
{
	
	 
	m_bDialogActive = true;
	CDialog::OnInitDialog();
 	Init();
	HSelectionSet *selection = m_pView->GetSelection();
	selection->SetAllowEntitySelection(true);	
	m_pView->SetViewSelectionLevel(HSelectionLevelEntity);
	selection->SetHighlightMode(HighlightQuickmoves);
	m_pView->Update();	

	m_Highlight1.SetCheck(BST_CHECKED);
	m_Highlight2.SetCheck(BST_CHECKED);
	m_DimOthersRadio.SetCheck(BST_CHECKED);
	m_ZoomToClashCheck.SetCheck(BST_CHECKED);
 	m_CalculateSoftClashesCheck.SetCheck(BST_CHECKED);
	m_Color1.SetParentClashDialog(this);
	m_Color2.SetParentClashDialog(this);
	GetDlgItem(IDC_COLOR1_STATIC)->EnableWindow(0);
	GetDlgItem(IDC_COLOR2_STATIC)->EnableWindow(0);
	m_Color1.currentcolor = RGB(255,255,255);
	m_Color2.currentcolor = RGB(0,0,0);
	m_Color1.Invalidate();
	m_Color2.Invalidate();
 	m_ClashListCtrl.InsertColumn(0,_T("Clash ID"),LVCFMT_LEFT,100);
 	m_ClashListCtrl.InsertColumn(1,_T("Participants"),LVCFMT_LEFT,180);
 	m_ClashListCtrl.InsertColumn(2,_T("Type"),LVCFMT_LEFT,120);
  	selection->SetHighlightMode(InverseTransparency);	  
	return true;
}



void ClashDlg::Init() 
{	
	m_InInit = true;
	int nIndex = 0;
	char text[4096];
	int cnum = 0; 
	m_ClashListCtrl.DeleteAllItems();
	if (m_pView->m_ClashList)
	{

 		START_LIST_ITERATION(ClashItem, m_pView->m_ClashList);
		sprintf(text, "%d", cnum++);
 		nIndex = m_ClashListCtrl.InsertItem(cnum,H_UNICODE_TEXT(text));
		sprintf(text, "%d %d", temp->m_shell1, temp->m_shell2);
 		m_ClashListCtrl.SetItemText(nIndex,1,H_UNICODE_TEXT(text));

		if (temp->m_bHardClash)
			m_ClashListCtrl.SetItemText(nIndex,2,_T("Hard"));
		else
			m_ClashListCtrl.SetItemText(nIndex,2,_T("Soft"));
 		m_ClashListCtrl.SetItemData(nIndex,(DWORD_PTR)temp);
		END_LIST_ITERATION(m_pView->m_ClashList);
	}
	m_InInit = false;
}
void ClashDlg::OnBnClickedShowClashItem1Check()
{
	SelectClashEntities(m_CurrentClashItem);
 }

void ClashDlg::OnBnClickedShowClashItem2Check()
{
	SelectClashEntities(m_CurrentClashItem);
}

void ClashDlg::OnBnClickedWireframeItem1Check()
{
	SelectClashEntities(m_CurrentClashItem);
 }
void ClashDlg::OnBnClickedWireframeItem2Check()
{
	SelectClashEntities(m_CurrentClashItem);
 }



void ClashDlg::OnBnClickedZoomToClashCheck()
{
 }


void ClashDlg::ColorButtonClicked(int id, float r, float g, float b, bool undefine)
{
	if (id == IDC_BUTTON_CLASHITEM1_COLOR)
	{
		m_Color1Value.Set(r,g,b);
		m_Color1ValueDefined = !undefine;
		if (undefine)
		{
		 	GetDlgItem(IDC_COLOR1_STATIC)->EnableWindow(0);
 			m_Color1.Invalidate();
		}
		else
		 	GetDlgItem(IDC_COLOR1_STATIC)->EnableWindow(1);

	
	}
	if (id == IDC_BUTTON_CLASHITEM2_COLOR)
	{
		m_Color2Value.Set(r,g,b);
		m_Color2ValueDefined = !undefine;
		if (undefine)
		{
		 	GetDlgItem(IDC_COLOR2_STATIC)->EnableWindow(0);
 			m_Color2.Invalidate();
		}
		else
		 	GetDlgItem(IDC_COLOR2_STATIC)->EnableWindow(1);
	}
 


	SelectClashEntities(m_CurrentClashItem);

}



void ClashDlg::OnBnClickedShowallclashesButton()
{
	HC_KEY lastkey1=-1, lastkey2=-1;
	HSelectionSet *selset = m_pView->GetSelection();
	selset->DeSelectAll();
	HC_KEY modelkey = m_pView->GetIncludeLinkKey();
	if (m_pView->m_ClashList)
	{
  		START_LIST_ITERATION(ClashItem, m_pView->m_ClashList);
		if (temp->m_shell1 != lastkey1)
			selset->Select(temp->m_shell1,1,&modelkey);
		if (temp->m_shell2 != lastkey2)
 			selset->Select(temp->m_shell2,1,&modelkey);
		lastkey1 = temp->m_shell1;
		lastkey2 = temp->m_shell2;
 		END_LIST_ITERATION(m_pView->m_ClashList);
	}
	m_pView->Update();
}

void ClashDlg::OnBnClickedShowsoftclashesButton()
{
	HC_KEY lastkey1=-1, lastkey2=-1;
	HSelectionSet *selset = m_pView->GetSelection();
	selset->DeSelectAll();
	HC_KEY modelkey = m_pView->GetIncludeLinkKey();
	if (m_pView->m_ClashList)
	{
  		START_LIST_ITERATION(ClashItem, m_pView->m_ClashList);
		if (!temp->m_bHardClash)
		{
			if (temp->m_shell1 != lastkey1)
				selset->Select(temp->m_shell1,1,&modelkey);
			if (temp->m_shell2 != lastkey2)
				selset->Select(temp->m_shell2,1,&modelkey);
			lastkey1 = temp->m_shell1;
			lastkey2 = temp->m_shell2;
		}
		END_LIST_ITERATION(m_pView->m_ClashList);
	}
	m_pView->Update();
}

void ClashDlg::OnBnClickedShowhardclashesButton()
{
	HC_KEY lastkey1=-1, lastkey2=-1;
	HSelectionSet *selset = m_pView->GetSelection();
	selset->DeSelectAll();
	HC_KEY modelkey = m_pView->GetIncludeLinkKey();
	if (m_pView->m_ClashList)
	{
		START_LIST_ITERATION(ClashItem, m_pView->m_ClashList);
		if (temp->m_bHardClash)
		{
			if (temp->m_shell1 != lastkey1)
				selset->Select(temp->m_shell1,1,&modelkey);
			if (temp->m_shell2 != lastkey2)
				selset->Select(temp->m_shell2,1,&modelkey);
			lastkey1 = temp->m_shell1;
			lastkey2 = temp->m_shell2;
		}
 		END_LIST_ITERATION(m_pView->m_ClashList);
	}
	m_pView->Update();
}


void ClashDlg::OnBnClickedUnhighlightclashButton()
{
	CheckDisplaced();

	HSelectionSet *selset = m_pView->GetSelection();
	selset->DeSelectAll();
	
 	HC_Open_Segment_By_Key(m_pView->GetOverwriteKey());
	HC_Open_Segment("selectionconditionincluder");
		if (HC_Show_Existence("visibility"))
			HC_UnSet_Visibility();
	HC_Close_Segment();
	HC_Close_Segment();
 	m_pView->Update();

}

void ClashDlg::OnBnClickedDefaultRadio()
{
	HSelectionSet *selection = m_pView->GetSelection();
  	selection->SetHighlightMode(HighlightQuickmoves);
 	SelectClashEntities(m_CurrentClashItem);
}
void ClashDlg::OnBnClickedDimothersRadio()
{
	HSelectionSet *selection = m_pView->GetSelection();
  	selection->SetHighlightMode(InverseTransparency);
	SelectClashEntities(m_CurrentClashItem);
}
void ClashDlg::OnBnClickedHideothersRadio()
{
	SelectClashEntities(m_CurrentClashItem);

}


void ClashDlg::OnSize(UINT nType, int cx, int cy) 
{	
	CDialog::OnSize(nType, cx, cy); 
	if (cy<265)
		cy = 265;
	if (m_bDialogActive)
	{
		CWnd *wnd = GetDlgItem(IDC_CLASH_LIST_STATIC);
		wnd->SetWindowPos(0, 0,0,cx - 140,cy - 160, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_CLASH_LISTCTRL);
		wnd->SetWindowPos(0, 0,0,cx - 165,cy - 180, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_CLASH_PARTICIPANTS_STATIC);
		wnd->SetWindowPos(0, 20,cy-145,cx-140,140, 0);   
		wnd = GetDlgItem(IDC_CLASH1_TREECTRL);
		wnd->SetWindowPos(0, 35,cy-125,(cx-140)/2-15,95, 0);   
		wnd = GetDlgItem(IDC_CLASH2_TREECTRL);
		wnd->SetWindowPos(0, 30 + (cx-140)/2,cy-125,(cx-140)/2-15,95, 0);   

		wnd = GetDlgItem(IDC_SHOW_CLASH_ITEM1_CHECK);
		wnd->SetWindowPos(0, 35,cy-25,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_SHOW_CLASH_ITEM2_CHECK);
		wnd->SetWindowPos(0, 30 + (cx-140)/2,cy-25,0,0,SWP_NOSIZE);

		wnd = GetDlgItem(IDC_WIREFRAME_ITEM1_CHECK);
		wnd->SetWindowPos(0, 105,cy-25,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_WIREFRAME_ITEM2_CHECK);
		wnd->SetWindowPos(0, 30 + (cx-140)/2+80,cy-25,0,0,SWP_NOSIZE);

		wnd = GetDlgItem(IDC_BUTTON_CLASHITEM1_COLOR);
		wnd->SetWindowPos(0, 180,cy-28,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_COLOR1_STATIC);
		wnd->SetWindowPos(0, 210,cy-25,0,0,SWP_NOSIZE);

		wnd = GetDlgItem(IDC_BUTTON_CLASHITEM2_COLOR);
		wnd->SetWindowPos(0, 30 + (cx-140)/2+155,cy-28,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_COLOR2_STATIC);
		wnd->SetWindowPos(0, 30 + (cx-140)/2+185,cy-25,0,0,SWP_NOSIZE);

		wnd = GetDlgItem(IDC_RECALCULATE_CLASH_BUTTON);
		wnd->SetWindowPos(0, cx-110,2,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_SELECT_CLASH_PARTICIPANTS_BUTTON);
		wnd->SetWindowPos(0, cx-110,28,0,0,SWP_NOSIZE);

		wnd = GetDlgItem(IDC_ZOOM_TO_CLASH_CHECK);
		wnd->SetWindowPos(0, cx-110,60,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_CALCULATE_SOFT_CLASHES_CHECK);
		wnd->SetWindowPos(0, cx-110,75,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_EXTRA_PRECISION_CHECK);
		wnd->SetWindowPos(0, cx-110,90,0,0,SWP_NOSIZE);


		wnd = GetDlgItem(IDC_DEFAULT_RADIO);
		wnd->SetWindowPos(0, cx-110,110,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_DIMOTHERS_RADIO);
		wnd->SetWindowPos(0, cx-110,125,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_HIDEOTHERS_RADIO);
		wnd->SetWindowPos(0, cx-110,140,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_STATIC_OTHERS);
		wnd->SetWindowPos(0, cx-115,80,100,70,0);
		wnd = GetDlgItem(IDC_SHOWALLCLASHES_BUTTON);
		wnd->SetWindowPos(0, cx-110,160,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_SHOWSOFTCLASHES_BUTTON);
		wnd->SetWindowPos(0, cx-110,185,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_SHOWHARDCLASHES_BUTTON);
		wnd->SetWindowPos(0, cx-110,210,0,0,SWP_NOSIZE);
		wnd = GetDlgItem(IDC_STATIC_SHOWCLASHES);
		wnd->SetWindowPos(0, cx-115,140,100,70,0);

		wnd = GetDlgItem(IDC_UNHIGHLIGHT_CLASH_BUTTON);
		wnd->SetWindowPos(0, cx-110,cy-25,0,0,SWP_NOSIZE);

	}
}




CMyListCtrl::CMyListCtrl()
{
        m_nSortColumn = -1;
        for (int i=0; i < MAXCOLUMNS; i++) m_pSortOrders[i] = -1;

}

void CMyListCtrl::PreSubclassWindow()
{
        ModifyStyle(0, LVS_REPORT);
        SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

}

static int CALLBACK CMyListCtrl_CompareFunc(LPARAM nItem1, LPARAM nItem2, LPARAM lParams)
{
        CMyListCtrl* pList = ((CMyListCtrl **) lParams)[0];
        int nSubItem = ((int *) lParams)[1];
        int nOrder = ((int *) lParams)[2];
        int nCompare = lstrcmp(pList->GetItemText(nItem1, nSubItem), pList->GetItemText(nItem2, nSubItem));
        return nOrder * nCompare;

}

static int CALLBACK CMyListCtrl_CompareFuncNum(LPARAM nItem1, LPARAM nItem2, LPARAM lParams)
{
        CMyListCtrl* pList = ((CMyListCtrl **) lParams)[0];

         int nSubItem = ((int *) lParams)[1];
        int nOrder = ((int *) lParams)[2];
		CString test(pList->GetItemText(nItem1, nSubItem));
		int a = _ttoi(test);
		CString test2(pList->GetItemText(nItem2, nSubItem));
		int b = _ttoi(test2);

        int nCompare;
		if (a>b)
			nCompare = 1;
		else if (a<b)
			nCompare = -1;
		else
			nCompare = 0;
         return nOrder * nCompare;

}

BOOL CMyListCtrl::SortItems(int nColumn, int nOrder)
{
        // if nColumn < 0 then resort with the last used column and order
        // nOrder > 0 => assending, nOrder < 0 => desending, nOrder = 0 => toggle

        if (nColumn >= 0)
        {
                m_nSortColumn = nColumn;
                m_pSortOrders[m_nSortColumn] = (nOrder != 0) ? nOrder : -m_pSortOrders[m_nSortColumn];
        }
        if (m_nSortColumn < 0) return FALSE;

        // Reset the param entry to point to the new index
        LV_ITEM lvi;
        lvi.mask = LVIF_PARAM;
        lvi.iSubItem = 0;
        for (lvi.iItem = 0; GetItem(&lvi); lvi.iItem++)
        {
                lvi.lParam = lvi.iItem;
                SetItem(&lvi);
        }
        // Set the parameters for the compare function
        long lParams[3] = {(long) this, (long) m_nSortColumn, (long) m_pSortOrders[m_nSortColumn]};
        // Sort the items
		BOOL bSorted;
		if (nColumn != 2)
	        bSorted = CListCtrl::SortItems(&CMyListCtrl_CompareFuncNum, (LPARAM) lParams);
		else		
			bSorted = CListCtrl::SortItems(&CMyListCtrl_CompareFunc, (LPARAM) lParams);
        // Ensure that selected item is visible
//        int nIndex = GetCurSel();
//        if (nIndex >= 0) EnsureVisible(nIndex, FALSE);

        return bSorted;

}



void ClashDlg::OnColumnclickMylistctrl(NMHDR* pNMHDR, LRESULT* pResult)
{
        NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

		m_ClashListCtrl.SetSelectionMark(-1);
        m_ClashListCtrl.SortItems(pNMListView->iSubItem, 0); 	
        *pResult = 0; 
}




unsigned int HClashThread(LPVOID pParam)
{
 
//	ClashDlg *dlg = (ClashDlg *)pParam;
// 	((HSolidView *)(dlg->m_pView))->CalculateClashes((m_CalculateSoftClashes.GetState() & 0x003), m_ExtraPreicison.GetState() & 0x003);
//	((CWnd *)dlg)->PostMessage(WM_CLASHTHREADCOMPLETED, 0, 0);

	return 0;
}
void ClashDlg::OnBnClickedSelectClashParticipants()
{
	CSolidHoopsFrame* pMainFrm = (CSolidHoopsFrame*) AfxGetMainWnd();
	pMainFrm->ShowClashSelectDialogBar(true);
}

void ClashDlg::OnBnClickedRecalculateClashButton()
{



	CWnd *wnd = GetDlgItem(IDC_RECALCULATE_CLASH_BUTTON);
	wnd->SetWindowText(_T("Calculating..."));
//	AfxBeginThread(HClashThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0);
	ClashSelect *selectdialog = (ClashSelect *)(m_ParentView->GetClashSelectDialog(false));
	bool done = false;
	if (selectdialog)
	{
		HSelectionSet *ss1 = selectdialog->GetSelectionSet1();
		HSelectionSet *ss2 = selectdialog->GetSelectionSet2();
		if (ss1->GetSize() || ss2->GetSize())
		{
		 	((HSolidView *)m_pView)->CalculateSelectedClashes(1 && (m_CalculateSoftClashesCheck.GetState() & 0x003), 1 && (m_ExtraPrecisionCheck.GetState() & 0x003), ss1, ss2);
			done = true;
		}

	}

	if (!done)
 		((HSolidView *)m_pView)->CalculateClashes(1 && (m_CalculateSoftClashesCheck.GetState() & 0x003), 1 && (m_ExtraPrecisionCheck.GetState() & 0x003));
	if (done)
	{
		selectdialog->CleanTrees();
		m_pView->Update();
	}
 

	Init();
	wnd->SetWindowText(_T("Find Clashes"));

 
	// TODO: Add your control notification handler code here
}
LRESULT ClashDlg::OnClashThreadCompleted(WPARAM wParam, LPARAM lParam)
{
	CWnd *wnd = GetDlgItem(IDC_RECALCULATE_CLASH_BUTTON);
	Init();
	wnd->SetWindowText(_T("Find Clashes"));
	return 0;
}


