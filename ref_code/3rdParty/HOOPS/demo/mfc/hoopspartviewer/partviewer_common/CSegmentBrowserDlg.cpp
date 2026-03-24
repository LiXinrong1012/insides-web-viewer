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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSegmentBrowserDlg.cpp,v 1.137 2010-03-30 22:04:50 boni Exp $
//

// SegmentBrowserDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "HSInclude.h"
#include "XMLEditorDlg.h"
#include "TreeGraph.h"
#include "WindowsTreeGraph.h"
#include "HoopsSegmentTree.h"
#include "CSegmentBrowserDlg.h"
#include "CSegmentManipulatorDlg.h"
#include "HSSelectionSet.h"
#include "HUtilityGeomHandle.h"
#include "HModelInfo.h"
#include "hc.h"
#include "HUtilityLocaleString.h"
#include "TextInput.h"
#include "CSolidHoopsFrm.h"
#include "OptimizeDialog.h"
#include "CSolidHoopsApp.h"
#include "HIOManager.h"
#include "HSolidModel.h"
#include "HBhvBehaviorManager.h"
#include "varray.h"
#include "vhash.h"
#include "CSolidHoopsFrm.h"

BEGIN_MESSAGE_MAP(CSegTreeCtrl,CTreeCtrl)
//{{AFX_MSG_MAP(CSegTreeCtrl)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_VSCROLL()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_COLOR, OnColorAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_VISIBILITY, OnVisibilityAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_SELECTABILITY, OnSelectabilityAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_RENDERINGOPTIONS, OnRenderingOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_CAMERA, OnCameraAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_MODELLING_MATRIX, OnModellingMatrixAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_USER_OPTIONS, OnUserOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_UNICODE_OPTIONS, OnUnicodeOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_TEXTFONT, OnTextFontAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_DRIVEROPTIONS, OnDriverOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_SYSTEMOPTIONS, OnSystemOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_COLOR, OnShowColorAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_VISIBILITY, OnShowVisibilityAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_SELECTABILITY, OnShowSelectabilityAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_RENDERINGOPTIONS, OnShowRenderingOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_CAMERA, OnShowCameraAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_MODELLING_MATRIX, OnShowModellingMatrixAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_USER_OPTIONS, OnShowUserOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_TEXTFONT, OnShowTextFontAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_DRIVEROPTIONS, OnShowDriverOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_SYSTEMOPTIONS, OnShowSystemOptionsAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_HANDEDNESS, OnHandednessAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWATTRIBUTE_HANDEDNESS, OnShowHandednessAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_HEURISTIC, OnHeuristicAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_VARIABLE_EDGE_WEIGHT, OnVariableEdgeWeightAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_EDGE_WEIGHT, OnEdgeWeightAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_VARIABLE_LINE_WEIGHT, OnVariableLineWeightAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_LINE_WEIGHT, OnLineWeightAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_VARIABLE_MARKER_SIZE, OnVariableMarkerSizeAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_MARKER_SIZE, OnMarkerSizeAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_CONDITION, OnConditionAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_TEXTALIGNMENT, OnTextAlignmentAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_WINDOWPATTERN, OnWindowPatternAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_WINDOW, OnWindowAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_LINEPATTERN, OnLinePatternAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_FACEPATTERN, OnFacePatternAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_ADDATTRIBUTE_MARKERSYMBOL, OnMarkerSymbolAttribute)

ON_COMMAND(ID_SEGMENTBROWSER_SHOWNETATTRIBUTE_HEURISTIC, OnShowHeuristicAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWNETATTRIBUTE_SUBWINDOW, OnShowSubwindowAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWNETATTRIBUTE_CLIPREGION, OnShowClipRegionAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_SHOWBOUNDING, OnShowBounding)
ON_COMMAND(ID_SEGMENTBROWSER_DELETESEGMENT, OnDeleteSegment)
ON_COMMAND(ID_SEGMENTBROWSER_FLUSHSEGMENT, OnFlushSegmentContents)
ON_COMMAND(ID_SEGMENTBROWSER_OPTIMIZE, OnOptimize)
ON_COMMAND(ID_SEGMENTBROWSER_LOADINTOSEGMENT, OnLoadIntoSegment)
ON_COMMAND(ID_SEGMENTBROWSER_ZOOMTOSEGMENT, OnZoomToSegment)
ON_COMMAND(ID_SEGMENTBROWSER_CUTSEGMENT, OnCutSegment)
ON_COMMAND(ID_SEGMENTBROWSER_PASTESEGMENT, OnPasteSegment)
ON_COMMAND(ID_SEGMENTBROWSER_CREATECHILDSEGMENT, OnCreateSegment)
ON_COMMAND(ID_SEGMENTBROWSER_ACTIVATEMANIPULATOR, OnActivateManipulator)
ON_COMMAND(ID_SEGMENTBROWSER_SAVETOHMF, OnSaveToHMF)
 
ON_COMMAND(ID_SEGMENTBROWSER_UNDEFINE, OnUndefineAttribute)
ON_COMMAND(ID_SEGMENTBROWSER_EDIT, OnEditInPlace)
ON_WM_KEYDOWN()
END_MESSAGE_MAP()





/////////////////////////////////////////////////////////////////////////////
// CSegTreeCtrl




/////////////////////////////////////////////////////////////////////////////
// CSegTreeCtrl message handlers

//subclassing the tree control was necessary because we need to handle the scroll events
void CSegTreeCtrl::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )

{
 	CTreeCtrl::OnVScroll( nSBCode, nPos, pScrollBar ); 
	((CSegmentBrowserDlg *)GetParent())->ShowSelectedItems();	 
}



/////////////////////////////////////////////////////////////////////////////
// CSegmentBrowserDlg dialog


CSegmentBrowserDlg::CSegmentBrowserDlg(CWnd* pParent /*=NULL*/, HBaseView * View)
: CDialog(CSegmentBrowserDlg::IDD, pParent) , WindowsTreeGraph(&m_Segment_tree, &m_TopInfoList)
{
	m_pHView = View;
	m_parent = pParent;
	m_dialogactive = false;
	m_SearchScope=Attribute;
	m_csSearchScope="Attribute";
	//	m_SelectedTreeItem = NULL;
}

CSegmentBrowserDlg::~CSegmentBrowserDlg()
{
	m_pMessageTarget = 0;
	delete m_pHoopsSegmentTree;	
}

void CSegmentBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSegmentBrowserDlg)
	DDX_Control(pDX, IDC_SEARCH, m_SearchButton);
	DDX_Control(pDX, IDC_TOPOLOGY_BROWSER_SWITCH, m_TopologyBrowserSwitch);
	DDX_Control(pDX, IDC_SEGMENT_BROWSER_SWITCH, m_SegmentBrowserSwitch);
	DDX_Control(pDX, IDC_IOP_PART_BROWSER_SWITCH, m_InterOpPartBrowserSwitch);
 	DDX_Control(pDX, IDC_LIST4, m_TopInfoList);
	DDX_Text(pDX, IDC_SEARCHEDIT, m_SearchEdit);
	DDX_CBString(pDX, IDC_COMBO_SEARCH_SCOPE, m_csSearchScope);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSegmentBrowserDlg, CDialog)
	//{{AFX_MSG_MAP(CSegmentBrowserDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, OnItemexpandingTree1)
	ON_WM_CLOSE()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE1, OnItemexpandedTree1)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE2, OnItemexpandingTree2)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE2, OnItemexpandedTree2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, OnSelchangedTree2)
	ON_BN_CLICKED(IDC_DELETE_SELECTION, OnDeleteSelection)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SEGMENTBROWSERREFRESH, OnSegmentbrowserrefresh)
	ON_BN_CLICKED(IDC_EXPANDFULLPATH, OnExpandfullpath)
	ON_BN_CLICKED(IDC_EXPAND_SELECTION, OnExpandSelection)
	ON_BN_CLICKED(IDC_POPULATE_INFO_WINDOW, OnPopulateInfo)
	ON_BN_CLICKED(IDC_VISUALIZE_BOUNDINGS, OnUpdateBoundings)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, OnEndlabeleditTree1)
	ON_BN_CLICKED(IDC_SEGMENT_BROWSER_CUT, OnSegmentBrowserCut)
	ON_BN_CLICKED(IDC_SEGMENT_BROWSER_PASTE, OnSegmentBrowserPaste)
	ON_BN_CLICKED(IDC_SEGMENT_BROWSER_MODIFY_SEGMENT, OnSegmentBrowserModifySegment)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, OnBeginlabeleditTree1)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_STARTSEGMENT_COMBO, OnSelchangeStartsegmentCombo)
	ON_BN_CLICKED(IDC_REFRESH_BROWSER, OnRefreshBrowser)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_TOPOLOGY_BROWSER_SWITCH, OnTopologyBrowserSwitch)
	ON_BN_CLICKED(IDC_IOP_PART_BROWSER_SWITCH, OnInterOpPartBrowserSwitch)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_SCOPE, OnSelchangeSearchScope)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//this function updates the selected item display (bold) in the tree control for the visible
//elements
//needs to be called whenever the selection has changed
//this is the main cause for speed problems with a large number of selections
//fix: have to think of a way to speed up the selection process...
void CSegmentBrowserDlg::ShowSelectedItems()
{
	ValidateSegmentTree();
	/*
	HSelectionSet *selection;
	int vismax = 25;
	selection = (HSelectionSet *)m_pHView->GetSelection();
	int ssize = selection->GetSize();
	HTREEITEM item = m_Segment_tree.GetFirstVisibleItem();
	int viscount=0;
	while (item)
	{
	viscount++;
	m_Segment_tree.SetItemState(item,0,TVIS_BOLD);
	int data = m_Segment_tree.GetItemData(item);
	for (int i=0;i<ssize;i++)
	{
	if (selection->GetAt(i) == data)
	{
	m_Segment_tree.SetItemState(item,TVIS_BOLD,TVIS_BOLD);
				break;
				}
				}
				if (viscount>1000)
				break;
				item = m_Segment_tree.GetNextVisibleItem(item);
				}
	*/
}

void CSegmentBrowserDlg::OnPopulateInfo()
{
	UpdateInfoWindow(true);
}

void CSegmentBrowserDlg::OnUpdateBoundings()
{
	if (m_dialogactive)
	{	
		CButton* chk = (CButton*) GetDlgItem(IDC_VISUALIZE_BOUNDINGS);
		m_pHoopsSegmentTree->ShowBoundings(chk->GetCheck() ? true : false);
		m_pHoopsSegmentTree->OnSelectionChanged(m_pHoopsSegmentTree->GetCurrentItem());
	}
}

void CSegmentBrowserDlg::UpdateInfoWindow(bool redraw)
{
	if (m_dialogactive)
	{	
		RECT lpRect;
		int cx, cy;
		CButton* chk = (CButton*) GetDlgItem(IDC_POPULATE_INFO_WINDOW);
		
		GetWindowRect(&lpRect);
		
		cx = lpRect.right-lpRect.left;
		cy = lpRect.bottom-lpRect.top;
		
		if(chk->GetCheck())
		{
			CWnd *wnd = GetDlgItem(IDC_BROWSER_FRAME);
			wnd->SetWindowPos(0, 20, 255 ,cx - 47,cy - 332,  0);   
			m_Segment_tree.SetWindowPos(0, 25, 271, cx - 58,cy - 353, 0);

			m_TopInfoList.ModifyStyle(0, WS_VISIBLE);
			if(redraw)
				m_TopInfoList.RedrawWindow();
			wnd = GetDlgItem(IDC_INFO_FRAME);
			wnd->ModifyStyle(0, WS_VISIBLE);
			if(redraw)
				wnd->RedrawWindow();

			m_pHoopsSegmentTree->ShowInfoWindow(true);
			m_pHoopsSegmentTree->OnSelectionChanged(m_pHoopsSegmentTree->GetCurrentItem());
		}

		else 
		{
			CWnd *wnd = GetDlgItem(IDC_BROWSER_FRAME);
			wnd->SetWindowPos(0, 20, 68, cx - 47,cy - 145, 0);   
			m_Segment_tree.SetWindowPos(0, 25, 85,cx - 58,cy - 167, 0);

			m_TopInfoList.ModifyStyle(WS_VISIBLE, 0);
			wnd = GetDlgItem(IDC_INFO_FRAME);
			wnd->ModifyStyle(WS_VISIBLE, 0);

			m_pHoopsSegmentTree->ShowInfoWindow(false);
		}
	}
}


//this function inserts a new item into the tree control with it's name (if available) and the tagid
HTREEITEM CSegmentBrowserDlg::InsertItemInTree(HC_KEY key, HTREEITEM position, CTreeCtrl *TreeCtrl)
{
	char text[MVO_BUFFER_SIZE];	
	int count;
	TVINSERTSTRUCT is;
	is.hParent = position;
	is.hInsertAfter=TVI_LAST;
	is.item.mask=TVIF_CHILDREN | TVIF_TEXT;
	
	HC_Show_Key_Type(key, text);
	
	if (strstr(text, "segment"))
	{
		HC_Open_Segment_By_Key(key);
		HC_Begin_Contents_Search(".","segments");
		HC_Show_Contents_Count(&count);
		HC_End_Contents_Search();
		HC_Close_Segment();
		
		if (count)
			is.item.cChildren = 1;
		else
			is.item.cChildren = 0;	
		
		HC_Show_Segment(key, text);
		HC_Parse_String(text,"/",-1,text);
	}
	else // I'm dealing with the geometry tree
	{
		char	type[MVO_BUFFER_SIZE];
		HC_Show_Key_Type(key, type);
		if (position == TVI_ROOT)
		{
			HC_Show_Key_Type(key, text);
			HC_Parse_String(text,"/",-1,text);
			is.item.cChildren = 1;
		}
		else if (strstr(type, "include"))
		{
			char location[MVO_BUFFER_SIZE];
			HC_Show_Include_Segment(key, location);
			sprintf(text, "%s", location);
			is.item.cChildren = 0;
		}
		else //(!TreeCtrl->GetParentItem(position))
		{
			sprintf(text, "%d", key);
			is.item.cChildren = 0;			
		}
	}
	

	H_TEXT label_text(text);
	is.item.pszText= (LPTSTR)(const TCHAR*)label_text; // pszText is not const - even though it is meant to be
	HTREEITEM item = TreeCtrl->InsertItem(&is);
	TreeCtrl->SetItemData(item,(DWORD)key);		
	
	return item;
}

HTREEITEM CSegmentBrowserDlg::InsertSegmentList(HC_KEY segkey, HTREEITEM item)
{
	char text[MVO_BUFFER_SIZE];	
	
	UINT state;
	if (item!=TVI_ROOT)
		state = m_Segment_tree.GetItemState(item,TVIS_EXPANDEDONCE);
	
	//	if (item == TVI_ROOT || !(state & TVIS_EXPANDEDONCE))
	{
		HTREEITEM citem = m_Segment_tree.GetChildItem(item);
		while (citem)
		{
			HTREEITEM nextitem = m_Segment_tree.GetNextSiblingItem(citem);
			m_Segment_tree.DeleteItem(citem);
			citem = nextitem;
		}
		HC_Open_Segment_By_Key(segkey);
		HC_Begin_Contents_Search(".","segments");
		HC_KEY child_key;
		while (HC_Find_Contents(text,&child_key))
		{
			if (first_run)
			{
				m_rootitem = InsertItemInTree(child_key ,item, (CTreeCtrl *)&m_Segment_tree);
				first_run = false;
			}
			else
				InsertItemInTree(child_key ,item, (CTreeCtrl *)&m_Segment_tree);
		}
		HC_End_Contents_Search();
		HC_Close_Segment();
	}
	ValidateSegmentTree();
	
	return m_rootitem;
}

BOOL CSegmentBrowserDlg::OnInitDialog() 
{
	
	CDialog::OnInitDialog();
	m_Segment_tree.SubclassDlgItem(IDC_TREE1,this);
	m_GeometryTree.SubclassDlgItem(IDC_TREE2,this);
	
	m_pHoopsSegmentTree = new HoopsSegmentTree(m_pHView, this);
	SetMessageTarget(m_pHoopsSegmentTree);
	
	m_imageState.Create( IDB_STATE, 16, 1, RGB(255,255,255) );
	m_Segment_tree.SetImageList( &(m_imageState), TVSIL_STATE );	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_STARTSEGMENT_COMBO);
	cbox->SetCurSel(0);	
	
	first_run = true;
	m_blockValidation = false;
	
	m_dialogactive=true;	
	
	m_SegmentBrowserSwitch.SetState(true);

	UpdateInfoWindow(true);

#ifdef HOOPS_ONLY
 	m_SegmentBrowserSwitch.ShowWindow(SW_HIDE);
	m_TopologyBrowserSwitch.ShowWindow(SW_HIDE);
#endif
#ifndef INTEROP
	m_InterOpPartBrowserSwitch.ShowWindow(SW_HIDE);
#endif

	/*
	m_Segment_tree.SubclassDlgItem(IDC_TREE1,this);
	m_GeometryTree.SubclassDlgItem(IDC_TREE2,this);
	
	  CDialog::OnInitDialog();
	  CString title =((CView *)m_parent)->GetDocument()->GetTitle();
	  SetWindowText("Segment Browser - "+title);
	  
		m_dialogactive=true;	
		
		  int tabs[5]={5,10,15,20,25};
		  //	m_infolist.SetTabStops(4,tabs);
		  m_TopInfoList.SetTabStops(4,tabs);
		  
			HBaseModel *model = (HBaseModel *)(m_pHView->GetModel());
			
			  m_baseKey = HC_KOpen_Segment("/");
			  HC_Close_Segment();
			  m_baseKey = model->GetModelKey();
			  InsertSegmentList(m_baseKey, TVI_ROOT);
			  
				//	if (!HighlightSelection())
				//		m_bNoupdate = true;
				
				  m_TopInfoList.ResetContent();
				  CString indent = "\t";
				  
					HModelInfo	*ModelInfo;
					ModelInfo = new HModelInfo(model->GetModelKey());
					
					  ModelInfo->ComputeModelInfo(); 
					  
						int triangle_count = ModelInfo->GetTotalTriangles();
						int polyline_count = ModelInfo->GetTotalLine() +
						ModelInfo->GetTotalPolyline() +
						ModelInfo->GetTotalCircularArc() +
						ModelInfo->GetTotalEllipticalArc();
						
						  delete ModelInfo;
						  m_TopInfoList.SetHorizontalExtent(600);
						  
							char text[MVO_BUFFER_SIZE];
							m_TopInfoList.SetHorizontalExtent(600);
							
							  sprintf(text,"%d triangles",triangle_count);
							  m_TopInfoList.AddString(indent + text);
							  sprintf(text,"%d polylines",polyline_count);
							  m_TopInfoList.AddString(indent + text);
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


/*
bool CSegmentBrowserDlg::CheckSelection(PK_ENTITY_t entity)
{
HSSelectionSet* selection;
selection = (HSSelectionSet *)m_pHView->GetSelection();
int size = selection->GetSolidListSize();
for (int i=0;i<size;i++)
{
if (selection->GetAtSolidEntity(i) == entity)
return true;
}
return false;
}

*/

void CSegmentBrowserDlg::SetAttributeTextBox(HC_KEY key)
{
/*	char text[MVO_BUFFER_SIZE];

  m_infolist.ResetContent();
  CString indent = "\t";
  
	HC_Open_Segment_By_Key(key);
	if (HC_Show_Existence("color"))
	{
	m_infolist.AddString("Explicitly set attributes:");
	
	  char temp[MVO_BUFFER_SIZE];
	  HC_Show_One_Color("faces", temp);
	  sprintf(text,"facets : %s", temp);
	  m_infolist.AddString(indent + text);
	  HC_Show_One_Color("polylines", temp);
	  sprintf(text,"curves : %s", temp);
	  m_infolist.AddString(indent + text);
	  }
	  else
	  m_infolist.AddString("No explicitly set attributes.");
	  
		HC_Close_Segment();
	*/	
}

//this function is called whenever a selection is changed in the tree control
//this could be the result of a selection/deselection in the tree control or in the view 
void CSegmentBrowserDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	WindowsTreeGraph::OnSelchanged(pNMHDR, pResult);
	return;
	
}

//called whenever the expands a subtree for the first time
void CSegmentBrowserDlg::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	WindowsTreeGraph::OnItemexpanding(pNMHDR, pResult);
	return;
	 
}

void CSegmentBrowserDlg::OnClose() 
{
	m_dialogactive=false;
	CDialog::OnClose();
}

void CSegmentBrowserDlg::OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
  	
}


void CSegmentBrowserDlg::OnItemexpandingTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	
}

void CSegmentBrowserDlg::OnItemexpandedTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
}

void CSegmentBrowserDlg::OnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	
}

HTREEITEM CSegmentBrowserDlg::InsertGeometryList(HC_KEY segkey, HTREEITEM item)
{
 	char text[MVO_BUFFER_SIZE];	
	
	UINT state = 0;
	
	if (item != TVI_ROOT)
		state = m_GeometryTree.GetItemState(item,TVIS_EXPANDEDONCE);
	
	char type[MVO_BUFFER_SIZE];
	bool new_type = true;
	
	if (item == TVI_ROOT || !(state & TVIS_EXPANDEDONCE))
	{
		HC_Open_Segment_By_Key(segkey);
		HC_Begin_Contents_Search(".","geometry, includes");
		HC_KEY geometry_key;
		while (HC_Find_Contents(text, &geometry_key))
		{
			if (!strstr(type, text))
				new_type = true;
			
			if (new_type)
			{
				strcpy(type, text);
				m_GeometryItem = InsertItemInTree(geometry_key, TVI_ROOT, (CTreeCtrl *)&m_GeometryTree);
				InsertItemInTree(geometry_key, m_GeometryItem, (CTreeCtrl *)&m_GeometryTree);
				new_type = false;
			}
			else
				InsertItemInTree(geometry_key, m_GeometryItem, (CTreeCtrl *)&m_GeometryTree);
		}
		HC_End_Contents_Search();
		HC_Close_Segment();
	}
	return m_rootitem;
}

void CSegmentBrowserDlg::OnDeleteSelection() 
{
	//	m_SelectedTreeItem.
	m_pHView->DeleteSelectionList(true);
	m_GeometryTree.DeleteAllItems();
	//UpdateVisibleItems();
	ValidateSegmentTree();
	
	//	m_Segment_tree.DeleteAllItems();	
	//	InsertSegmentList(m_pHView->GetModel()->GetModelKey(), TVI_ROOT);
	// 	m_TopInfoList.ResetContent();
	
	//	if (!HighlightSelection())
	//		m_bNoupdate = true;
	
	//	m_Segment_tree.DeleteItem();
	//	m_Segment_tree.GetFocus();
}




bool CSegmentBrowserDlg::ShowItemExistence(HTREEITEM item)
{
	bool found = false;
	HTREEITEM owneritem = m_Segment_tree.GetParentItem(item);
	if (owneritem)
	{
		HC_KEY parentkey =  m_Segment_tree.GetItemData(owneritem);
		HC_Open_Segment_By_Key(parentkey);
		HC_Begin_Contents_Search(".","segments");
		char type[MVO_BUFFER_SIZE];
		HC_KEY key;
		while (HC_Find_Contents(type, &key))
		{
			if (key == (HC_KEY)m_Segment_tree.GetItemData(item))
			{
				found = true;
				break;
			}
		}
		HC_End_Contents_Search();
		return found;
	}
	return true;
}



//this function updates the Visible item display (bold) in the tree control for the visible
//elements
//needs to be called whenever the selection has changed
//this is the main cause for speed problems with a large number of selections
//fix: have to think of a way to speed up the selection process...
void CSegmentBrowserDlg::UpdateVisibleItems()
{
	
	HSelectionSet *selection;
 	selection = (HSelectionSet *)m_pHView->GetSelection();
 	HTREEITEM item = m_Segment_tree.GetFirstVisibleItem();
	HTREEITEM newitem;
	int viscount=0;
	while (item)
	{
		viscount++;
		m_Segment_tree.SetItemState(item,0,TVIS_BOLD);
		newitem = m_Segment_tree.GetNextVisibleItem(item);
		
		if (!ShowItemExistence(item))
			m_Segment_tree.DeleteItem(item);
		//the visible items are all items from the top visible down to the last item on the list 
		//even if it is outside the window. That is why we brake processing at 25 elements
		if (viscount>25)
			break;
		item = newitem;
	}
}

HTREEITEM CSegmentBrowserDlg::FindItemBySegmentKey(HC_KEY segkey, HTREEITEM item)
{
	
	if (!item)
		return 0;
	
	item = m_Segment_tree.GetChildItem(item);
	
	while (item)
	{
		HC_KEY itemkey = m_Segment_tree.GetItemData(item);
		if (segkey == itemkey)
			return item;
		HTREEITEM found = FindItemBySegmentKey(segkey, item);
		if (found)
			return found;
		
		item = m_Segment_tree.GetNextSiblingItem(item);
	}
	return 0;
}





void CSegmentBrowserDlg::ValidateSegment(HC_KEY segkey)
{
	HTREEITEM item = FindItemBySegmentKey(segkey, TVI_ROOT);
	
	if (item)
	{
		HC_KEY itemkey = m_Segment_tree.GetItemData(item);
		if (segkey == itemkey)
		{
			HTREEITEM sibling = m_Segment_tree.GetPrevSiblingItem(item);
			char text[MVO_BUFFER_SIZE];	
			int count;
			TVINSERTSTRUCT is;
			
			is.hParent = m_Segment_tree.GetParentItem(item);
			is.hInsertAfter=sibling;
			is.item.mask=TVIF_CHILDREN | TVIF_TEXT;
			
			HC_Open_Segment_By_Key(itemkey);
			HC_Begin_Contents_Search(".","segments");
			HC_Show_Contents_Count(&count);
			HC_End_Contents_Search();
			HC_Close_Segment();
			
			if (count)
				is.item.cChildren = 1;
			else
				is.item.cChildren = 0;	
			
			HC_Show_Segment(segkey, text);
			HC_Parse_String(text,"/",-1,text);
			
			
			H_TEXT label_text(text);
			is.item.pszText= (LPTSTR)(const TCHAR*)label_text; // pszText is not const - even though it is meant to be

			m_Segment_tree.DeleteItem(item);
			item = m_Segment_tree.InsertItem(&is);
			m_Segment_tree.SetItemData(item,(DWORD)itemkey);		
		}
	}	 
}



void CSegmentBrowserDlg::ValidateSegmentTreeInternal(HTREEITEM parentItem, HC_KEY parentKey)
{
	int segmentCount;
	char type[MVO_BUFFER_SIZE];
	int i;
	HC_Open_Segment_By_Key(parentKey);
	HC_Begin_Contents_Search(".","segment");
	HC_Show_Contents_Count(&segmentCount);
	if (segmentCount > m_segmentCountMax)
	{
		delete [] m_pSegmentList;
		m_pSegmentList = new HC_KEY[segmentCount];
		segmentCount = m_segmentCountMax;
	}
	for (i=0;i<segmentCount;i++)
		HC_Find_Contents(type, &m_pSegmentList[i]);
	HC_End_Contents_Search();
	HC_Close_Segment();
	
	HTREEITEM item = m_Segment_tree.GetChildItem(parentItem);
	
	while (item)
	{
		HC_KEY itemkey = m_Segment_tree.GetItemData(item);
		bool found = false;
		for (i=0;i < segmentCount;i++)
		{
			if (m_pSegmentList[i] == itemkey)
			{
				found = true;
				m_pSegmentList[i] = 0;
				break;
			}
		}
		HTREEITEM nextItem = m_Segment_tree.GetNextSiblingItem(item);
		
		if (!found)
			m_Segment_tree.DeleteItem(item);
		item = nextItem;
	}
	
	for (i=0;i<segmentCount;i++)
	{
		if (m_pSegmentList[i] != 0)
			InsertItemInTree(m_pSegmentList[i],parentItem, (CTreeCtrl *)&m_Segment_tree);
	}
	
	
	item = m_Segment_tree.GetChildItem(parentItem);
	
	while (item)
	{
		UINT state = m_Segment_tree.GetItemState(item,TVIS_EXPANDED);
		if (state & TVIS_EXPANDED)
		{
			HC_KEY itemkey = m_Segment_tree.GetItemData(item);
			ValidateSegmentTreeInternal(item, itemkey);
		}
		item = m_Segment_tree.GetNextSiblingItem(item);
	}
}



void CSegmentBrowserDlg::ValidateSegmentTree()
{
	m_pHoopsSegmentTree->ValidateSegmentTree();
	//	m_pTreeCtrl->Invalidate(true);
	return;
	 
	
}

void CSegmentBrowserDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	CRect r;
	GetParent()->GetWindowRect(r);
//	GetParent()->MoveWindow(r.left, r.top, r.right - r.left, r.bottom - r.top, true);
   	ValidateSegmentTree();
	// TODO: Add your message handler code here
	
}


void CSegmentBrowserDlg::OnSegmentbrowserrefresh() 
{
	
	delete m_pHoopsSegmentTree;
	
	
	CButton *tbox =(CButton *)GetDlgItem(IDC_EXPANDFULLPATH);
	CString button_text;
	tbox->GetWindowText(button_text);	
	
   	if (button_text != "Standard View")
	{
		m_baseKey = HC_KOpen_Segment("/");
		HC_Close_Segment();
		tbox->SetWindowText(_T("Expanded View"));
	}
	else
	{
		HBaseModel *model = (HBaseModel *)(m_pHView->GetModel());
		m_baseKey = model->GetModelKey();
		tbox->SetWindowText(_T("Standard View"));
	}
	
	m_pHoopsSegmentTree = new HoopsSegmentTree(m_pHView, this,m_baseKey );
	SetMessageTarget(m_pHoopsSegmentTree);
	/*
	HSelectionSet* selection;
	selection = (HSelectionSet *)m_pHView->GetSelection();
	selection->DeSelectAll();
	m_blockValidation = true;
	m_Segment_tree.DeleteAllItems();
	*/
	first_run = true;
	//  	InsertSegmentList(m_baseKey, TVI_ROOT);	
	m_blockValidation = false;
	// TODO: Add your control notification handler code here 	
}

void CSegmentBrowserDlg::OnExpandfullpath() 
{
	delete m_pHoopsSegmentTree;
	
	
	CButton *tbox =(CButton *)GetDlgItem(IDC_EXPANDFULLPATH);
	CString button_text;
	tbox->GetWindowText(button_text);	
	
   	if (button_text == "Standard View")
	{
		m_baseKey = HC_KOpen_Segment("/");
		HC_Close_Segment();
		tbox->SetWindowText(_T("Expanded View"));
	}
	else
	{
		HBaseModel *model = (HBaseModel *)(m_pHView->GetModel());
		m_baseKey = model->GetModelKey();
		tbox->SetWindowText(_T("Standard View"));
	}
	
	m_pHoopsSegmentTree = new HoopsSegmentTree(m_pHView, this,m_baseKey );
	SetMessageTarget(m_pHoopsSegmentTree);
	/*
	HSelectionSet* selection;
	selection = (HSelectionSet *)m_pHView->GetSelection();
	selection->DeSelectAll();
	m_blockValidation = true;
	m_Segment_tree.DeleteAllItems();
	*/
	first_run = true;
	//  	InsertSegmentList(m_baseKey, TVI_ROOT);	
	m_blockValidation = false;
	
	
}



void CSegmentBrowserDlg::ExpandSelection()
{
	m_pHoopsSegmentTree->FindSelectedItems();
	return;
	
}













void CSegmentBrowserDlg::OnExpandSelection() 
{
	// TODO: Add your control notification handler code here
	ExpandSelection();
	
}

// This function renames the selected segment to the edited string.
void CSegmentBrowserDlg::OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	WindowsTreeGraph::OnEndlabeledit(pNMHDR, pResult);
	*pResult = true;
	return;
}

void CSegmentBrowserDlg::OnSegmentBrowserCut() 
{
	
}

void CSegmentBrowserDlg::OnSegmentBrowserPaste() 
{
	
}

void CSegmentBrowserDlg::OnSegmentBrowserModifySegment() 
{
	int				numSolidSelections, numHoopsSelections;
	HSSelectionSet* selection = 0;
	
	selection = (HSSelectionSet *)m_pHView->GetSelection();
	
	numHoopsSelections = selection->GetSize();
	numSolidSelections = selection->GetSolidListSize();
	
	HC_KEY key;
	if (numHoopsSelections == 0 || numHoopsSelections >1)
		key = m_pHView->GetModelKey();
	else
		key = selection->GetAt(0);
	selection->DeSelect(key, false); 
	
	CSegmentManipulatorDlg sm(this, key, m_pHView);
	sm.DoModal();
	
}


void CSegTreeCtrl::FindItemUnderCursor(UINT nFlags, CPoint point)
{

    m_pItemUnderCursor = 0;
	CMenu parent_menu;	
 	CRect   rect;
    CPoint  new_menu_position;
    TVITEM istate;
    
	
    // Display the menu at the mouse click position.
	
    GetWindowRect(&rect);
	
    // Transform the screen coordinate point to a window-relative point.
    new_menu_position = CPoint (rect.left + point.x, rect.top + point.y);  
    
    UINT uFlags=0;
    HTREEITEM hti = HitTest(point,&uFlags);	
    CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
    if (hti) 
    {				
 		istate.mask = TVIF_HANDLE | TVIF_PARAM;
		istate.hItem = hti;
		GetItem(&istate);		
		m_pItemUnderCursor= (WindowsTreeGraphItem *)istate.lParam;
		
    }
    else
    {
	
		m_pItemUnderCursor =  (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->GetRootItem();
    }
    
    
}

void CSegTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{   
     FindItemUnderCursor(nFlags,point);
        
    
    UINT uFlags=0;
    HTREEITEM hti = HitTest(point,&uFlags);
    if (hti)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		if( uFlags & TVHT_ONITEMSTATEICON )
		{
			owner->OnImageClicked(hti, uFlags);
						
		}

	CRect rect;		
	GetWindowRect(rect);
       if (m_pItemUnderCursor)
	    owner->GetHoopsSegmentTree()->DrawTextInInfoWindow(m_pItemUnderCursor,rect.right - rect.left);
//		((CSolidHoopsFrame *)AfxGetMainWnd())->GetStatusBar()->SetPaneText(0,H_TEXT(m_pItemUnderCursor->m_pItemText));

    }
    CTreeCtrl::OnLButtonDown(nFlags, point);


}

void CSegTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();

      FindItemUnderCursor(nFlags,point);

    if ( !(m_pItemUnderCursor->m_Flags & READONLY_OBJECT) &&
		(owner->GetHoopsSegmentTree()->IsAttribute(m_pItemUnderCursor) || owner->GetHoopsSegmentTree()->IsDefine(m_pItemUnderCursor) || owner->GetHoopsSegmentTree()->IsGeometry(m_pItemUnderCursor,"TEXT") ||
		owner->GetHoopsSegmentTree()->IsGeometry(m_pItemUnderCursor,"DISTANT LIGHT") || owner->GetHoopsSegmentTree()->IsGeometry(m_pItemUnderCursor,"LOCAL LIGHT") || 
		owner->GetHoopsSegmentTree()->IsGeometry(m_pItemUnderCursor,"SPOT LIGHT")))
	OnEditInPlace();
}

void CSegmentBrowserDlg::OnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	TVITEM treeitem = pTVDispInfo->item; 	    
	WindowsTreeGraphItem *item = (WindowsTreeGraphItem *)treeitem.lParam;
	if (item->m_pExtraData || item->m_pItemText2)   
   	    WindowsTreeGraph::OnBeginlabeledit(pNMHDR, pResult);
	else
		*pResult = true;
	
}

void CSegmentBrowserDlg::OnSize(UINT nType, int cx, int cy) 
{	
	
	CDialog::OnSize(nType, cx, cy); 
	if (cx<241)
		cx = 241;
	
	if (m_dialogactive)
	{
#ifdef INTEROP
		CButton* chk = (CButton*) GetDlgItem(IDC_POPULATE_INFO_WINDOW);
			
		m_Segment_tree.SetWindowPos(0, 0, 0, cx - 60, cy - (chk->GetCheck() ? 283 : 207), SWP_NOMOVE | SWP_NOREPOSITION);   	
		CWnd *wnd = GetDlgItem(IDC_SEGBROWSERWRAP);
		wnd->SetWindowPos(0, 0, 0, cx - 25, cy - 78, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_BROWSER_FRAME);
		wnd->SetWindowPos(0, 0, 0, cx - 48, cy - (chk->GetCheck() ? 262 : 175), SWP_NOMOVE | SWP_NOREPOSITION);   
		m_TopInfoList.SetWindowPos(0, 0, 0, cx - 60, 63, SWP_NOMOVE | SWP_NOREPOSITION);   	
		wnd = GetDlgItem(IDC_INFO_FRAME);
		wnd->SetWindowPos(0, 0, 0, cx - 48, 88, SWP_NOMOVE | SWP_NOREPOSITION);   
		CRect r;
 		m_SegmentBrowserSwitch.SetWindowPos(0, 10, cy - 65, 0, 0, SWP_NOSIZE);
 		m_TopologyBrowserSwitch.SetWindowPos(0, 130, cy - 65, 0, 0, SWP_NOSIZE);
		m_InterOpPartBrowserSwitch.SetWindowPos(0, 60, cy - 35, 0, 0, SWP_NOSIZE);

		int search_button_x = (cx-40)/2;
		int search_edit_w = search_button_x-22;
		int search_scope_w = search_edit_w-16;
		int search_scope_x = search_button_x+50;
		
		wnd = GetDlgItem(IDC_SEARCHEDIT);
 		wnd->SetWindowPos(0, 20, cy-98, search_edit_w, 20, 0);

		m_SearchButton.SetWindowPos(0, search_button_x, cy-100, 0, 0, SWP_NOSIZE);

		wnd = GetDlgItem(IDC_COMBO_SEARCH_SCOPE);
 		wnd->SetWindowPos(0, search_scope_x, cy - 98, search_scope_w, 14, 0);

#else
		CButton* chk = (CButton*) GetDlgItem(IDC_POPULATE_INFO_WINDOW);
			
		m_Segment_tree.SetWindowPos(0, 0,0,cx - 60,cy - (chk->GetCheck() ? 353 : 167), SWP_NOMOVE | SWP_NOREPOSITION);   	
		CWnd *wnd = GetDlgItem(IDC_SEGBROWSERWRAP);
		wnd->SetWindowPos(0, 0,0,cx - 30,cy - 50, SWP_NOMOVE | SWP_NOREPOSITION);   
		wnd = GetDlgItem(IDC_BROWSER_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 48,cy - (chk->GetCheck() ? 332 : 145), SWP_NOMOVE | SWP_NOREPOSITION);   
		m_TopInfoList.SetWindowPos(0, 0,0,cx - 60,163, SWP_NOMOVE | SWP_NOREPOSITION);   	
		wnd = GetDlgItem(IDC_INFO_FRAME);
		wnd->SetWindowPos(0, 0,0,cx - 48,188, SWP_NOMOVE | SWP_NOREPOSITION);   
		CRect r;
 		m_SegmentBrowserSwitch.SetWindowPos(0, 10, cy - 30, 0, 0, SWP_NOSIZE);
 		m_TopologyBrowserSwitch.SetWindowPos(0, 130, cy - 30, 0, 0, SWP_NOSIZE);

		int search_button_x = (cx-40)/2;
		int search_edit_w = search_button_x-22;
		int search_scope_w = search_edit_w-16;
		int search_scope_x = search_button_x+50;
		
		wnd = GetDlgItem(IDC_SEARCHEDIT);
 		wnd->SetWindowPos(0, 20, cy-68, search_edit_w, 20, 0);

		m_SearchButton.SetWindowPos(0, search_button_x, cy-70, 0, 0, SWP_NOSIZE);

		wnd = GetDlgItem(IDC_COMBO_SEARCH_SCOPE);
 		wnd->SetWindowPos(0, search_scope_x, cy - 68, search_scope_w, 14, 0);

#endif // INTEROP
	}
}


void CSegmentBrowserDlg::OnOK()
{
    OnSearch();
}

void CSegmentBrowserDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	
	CDialog::OnRButtonDown(nFlags, point);
}



void CSegTreeCtrl::OnColorAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"COLOR");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnShowColorAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "COLOR", text);
		ShowText(text);
    }
	
	
}

void CSegTreeCtrl::OnVisibilityAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"VISIBILITY");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnSelectabilityAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"SELECTABILITY");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnRenderingOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"RENDERING OPTIONS");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnCameraAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"CAMERA");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnModellingMatrixAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor =  (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"MODELLING MATRIX");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnUserOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"USER OPTIONS");
		OnEditInPlace();

    }
}

void CSegTreeCtrl::OnUnicodeOptionsAttribute()
{
	if (m_pItemUnderCursor)
	{
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"UNICODE OPTIONS");
		OnEditInPlace();

	}
}

void CSegTreeCtrl::OnTextFontAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"TEXT FONT");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnDriverOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"DRIVER OPTIONS");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnSystemOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"SYSTEM OPTIONS");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::ShowText(const char *text)
{
	ReleaseCapture();
	XMLEditorDlg2 my_dlg(this, (char *)text);
	my_dlg.DoModal();
	
	
}


void CSegTreeCtrl::OnShowVisibilityAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "VISIBILITY", text);
		ShowText(text);
    }
	
	
}
void CSegTreeCtrl::OnShowSelectabilityAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "SELECTABILITY", text);
		ShowText(text);
    }
	
	
}

void CSegTreeCtrl::OnShowRenderingOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "RENDERING OPTIONS", text);
		ShowText(text);
    }
	
	
}


void CSegTreeCtrl::OnShowCameraAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "CAMERA", text);
		ShowText(text);
		
		
    }
	
	
}
void CSegTreeCtrl::OnShowModellingMatrixAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "MODELLING MATRIX", text);
		ShowText(text);
    }
	
	
}

void CSegTreeCtrl::OnShowUserOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "USER OPTIONS", text);
		ShowText(text);
    }
}

void CSegTreeCtrl::OnShowUnicodeOptionsAttribute()
{
	if (m_pItemUnderCursor)
	{
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "UNICODE OPTIONS", text);
		ShowText(text);
	}
}

void CSegTreeCtrl::OnShowTextFontAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "TEXT FONT", text);
		ShowText(text);
    }
	
	
}
void CSegTreeCtrl::OnShowDriverOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "DRIVER OPTIONS", text);
		ShowText(text);
    }
	
	
}
void CSegTreeCtrl::OnShowSystemOptionsAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "SYSTEM OPTIONS", text);
		ShowText(text);
    }
	
	
}

void CSegTreeCtrl::OnHandednessAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"HANDEDNESS");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnShowHandednessAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "HANDEDNESS", text);
		ShowText(text);
    }
	
	
}


void CSegTreeCtrl::OnHeuristicAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"HEURISTICS");
		OnEditInPlace();
    }
	
	
}
void CSegTreeCtrl::OnVariableEdgeWeightAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"VARIABLE EDGE WEIGHT");
		OnEditInPlace();
    }
	
	
}
void CSegTreeCtrl::OnLinePatternAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"LINE PATTERN");
		OnEditInPlace();
    }
	
	
}
void CSegTreeCtrl::OnFacePatternAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"FACE PATTERN");
		OnEditInPlace();
    }
	
	
}

void CSegTreeCtrl::OnMarkerSymbolAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"MARKER SYMBOL");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnEdgeWeightAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"EDGE WEIGHT");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnWindowPatternAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"WINDOW PATTERN");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnWindowAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"WINDOW");
		OnEditInPlace();

    }
	
	
}
void CSegTreeCtrl::OnVariableLineWeightAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"VARIABLE LINE WEIGHT");\
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnLineWeightAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"LINE WEIGHT");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnVariableMarkerSizeAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"VARIABLE MARKER SIZE");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnMarkerSizeAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"MARKER SIZE");
		OnEditInPlace();

    }
	
	
}


void CSegTreeCtrl::OnConditionAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"CONDITION");
		OnEditInPlace();

    }
	
	
}

void CSegTreeCtrl::OnTextAlignmentAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor = (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->ExpandAttributeType(m_pItemUnderCursor,-1,"TEXT ALIGNMENT");
		OnEditInPlace();

    }
	
	
}


void CSegTreeCtrl::OnShowHeuristicAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "HEURISTICS", text);
		ShowText(text);
    }
	
	
}

void CSegTreeCtrl::OnShowSubwindowAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "WINDOW", text);
		ShowText(text);
    }
	
	
}
void CSegTreeCtrl::OnShowClipRegionAttribute()
{
    if (m_pItemUnderCursor)
    {
		char text[MVO_BUFFER_SIZE];
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->ShowNetAttribute(m_pItemUnderCursor, "CLIP REGION", text);
		ShowText(text);
    }
	
	
}

void CSegTreeCtrl::OnShowBounding()
{
    if (m_pItemUnderCursor)
    {
		HPoint min, max;
		HC_KEY key = (HC_KEY)m_pItemUnderCursor->m_pExtraData;
		HC_Open_Segment_By_Key(key);
		HC_Compute_Circumcuboid(".", &min, &max);
		HC_Close_Segment();
		char text[MVO_BUFFER_SIZE];
		sprintf(text,"Bounding: Min = %f %f %f   Max = %f %f %f",min.x, min.y, min.z, max.x, max.y, max.z);	
		ShowText(text);
    }
}



void CSegTreeCtrl::OnUndefineAttribute()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->UndefineAttribute(m_pItemUnderCursor);
		owner->GetHoopsView()->Update();
    }
	
	
}
void CSegTreeCtrl::OnEditInPlace()
{
	char text2[MVO_BIG_BUFFER_SIZE];
	char *windowtext;
	if (m_pItemUnderCursor)
	{
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		ReleaseCapture();
		if (owner->GetHoopsSegmentTree()->IsDefine(m_pItemUnderCursor))
		{		
			char name[MVO_BIG_BUFFER_SIZE];
			owner->GetHoopsSegmentTree()->GetNameAndDefinition(m_pItemUnderCursor, name, text2);
			windowtext = m_pItemUnderCursor->m_pParentItem->m_pItemText;
		}
		else
		{
			strncpy(text2,(char *)m_pItemUnderCursor->m_pItemText, MVO_BIG_BUFFER_SIZE-1);
			text2[MVO_BIG_BUFFER_SIZE-1]=0;
			owner->GetHoopsSegmentTree()->FoldAttributeText(text2, text2);
			windowtext = (char *)m_pItemUnderCursor->m_pItemText2;
		}

		XMLEditorDlg2 my_dlg(this, text2, windowtext);
		if (my_dlg.DoModal() == IDOK)
		{	
			CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();	
			owner->GetHoopsSegmentTree()->OnTextModified(m_pItemUnderCursor, H_ASCII_TEXT(my_dlg.m_richedit));
		}
	}         
}


void CSegTreeCtrl::OnDeleteSegment()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		owner->GetHoopsSegmentTree()->DeleteSegment(m_pItemUnderCursor);
    }
	
}

void CSegTreeCtrl::OnFlushSegmentContents()
{
	char text[4096]="", title[4096]="Flush Content Types";

	if (m_pItemUnderCursor)
    {
		ReleaseCapture();
 		XMLEditorDlg2 my_dlg(this, text, title);
 		if (my_dlg.DoModal() == IDOK)
		{	
			CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();	
			owner->GetHoopsSegmentTree()->FlushSegmentContents(m_pItemUnderCursor, H_ASCII_TEXT(my_dlg.m_richedit));
		}
    }    
}

// our application-specific read function
HFileInputResult CSegTreeCtrl::Read(const char * FileName) 
{   
 	
	unsigned int i;
	char extension[MVO_BUFFER_SIZE]; 
	HFileInputResult success = InputOK;
	
	extension[0]='\0';
	HC_Parse_String(FileName,".",-1,extension);
	
	/*make it lower case*/
	for(i=0; i<strlen(extension);i++)
		extension[i]=(char) tolower(extension[i]);
	
	char ext[4096];
	
	HUtility::FindFileNameExtension(FileName, ext);
	
	// find handler for type
	HInputHandler * handler = HDB::GetHIOManager()->GetInputHandler(ext);
	
	// if none found the quit
	if(!handler) return success;
	
	HC_KEY currentlyopen = HC_KOpen_Segment(".");
	HC_Close_Segment();
	
	handler->FileInputByKey(FileName, currentlyopen, 0);						
	
	
	
	return success;
}


void CSegTreeCtrl::LoadFile( LPCTSTR csFilePathName, HStreamFileToolkit* tk) 
{
	assert(tk);
	CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
	HBaseView *m_pHView = owner->GetHoopsView();

	// this could take time - don't test user's patience
	CWaitCursor display_hourglass_cursor_till_we_finish_reading;

	// understand the file extension - if unknown better return
	char file_ext[MVO_BUFFER_SIZE]; 
	HUtility::FindFileNameExtension(H_ASCII_TEXT(csFilePathName), file_ext);
	if(strlen(file_ext) == 0) 
	{
		AfxMessageBox(_T("Error: No file extension. Could not determine input file format.\n"));
		return;
	}

 
	HSolidModel * hmodel = (HSolidModel*) m_pHView->GetModel();
	assert(hmodel);

	
	
	Read(H_ASCII_TEXT(csFilePathName));

	m_pHView->EmitSegment(hmodel->GetModelKey(), true);
 	m_pHView->Update();
}



void CSegTreeCtrl::OnLoadIntoSegment()
{
	CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
	HBaseView *m_pHView = owner->GetHoopsView();

    if (m_pItemUnderCursor)
	{
		HC_Open_Segment_By_Key((HC_KEY)m_pItemUnderCursor->m_pExtraData);
		
 		CString filter = _T("");
		CString def_ext = ".hsf";
		
		CSolidHoopsApp::CreateAllFileTypesString(&filter, HDB::GetHIOManager()->GetInputHandlerTypes());
		filter += _T("|");

		// this adds file types that have HIO handlers and appear in ProcessFilters()
		CSolidHoopsApp::ProcessFilters(&filter, HDB::GetHIOManager()->GetInputHandlerTypes());
		filter += _T("|");
		
		TCHAR cur_dir[MVO_BUFFER_SIZE];
		GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
		CFileDialog my_dlg(TRUE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter , NULL);
		my_dlg.m_ofn.lpstrInitialDir = cur_dir;
		if (my_dlg.DoModal() == IDOK)
		{
			HSolidModel * hmodel = (HSolidModel*) m_pHView->GetModel();
			assert(hmodel);
			LoadFile( my_dlg.GetPathName(), hmodel->GetStreamFileTK() );
		}
		
		
		HC_Close_Segment();
	}
}

void CSegTreeCtrl::OnOptimize()
{
	CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
	HBaseView *m_pHView = owner->GetHoopsView();

    if (m_pItemUnderCursor)
    {
		ReleaseCapture();
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		
		COptimizeDialog mydialog(this);
		if (mydialog.DoModal() == IDOK)
		{

			char text[4096];
			strcpy(text,"");
			if (mydialog.m_ExpandIncludes)
				strcpy(text,"expand includes,");
			if (mydialog.m_CollapseMatrices)
				strcat(text,"collapse matrices,");
			if (mydialog.m_MergeShells )
				strcat(text,"merge shells,");
			if (mydialog.m_DiscardUserData )
				strcat(text,"discard user data,");

			switch (mydialog.m_Reorganize)
			{
			case 0:
				strcat(text,"reorganize = (color, spatial)");
				break;
			case 1:
				strcat(text,"reorganize = (spatial, color)");
				break;
			case 2:
				strcat(text,"reorganize = (color)");
				break;
			case 3:
				strcat(text,"reorganize = (spatial)");
				break; 
			}

			if (text[strlen(text)-1] == ',')
				text[strlen(text)-1] = 0;

			HC_Open_Segment_By_Key((HC_KEY)m_pItemUnderCursor->m_pExtraData);
			HC_Optimize_Segment_Tree(".",text);
			HC_Close_Segment();
			m_pHView->Update();
		owner->RefreshBrowser();

		}
		
	}
	
}


void CSegTreeCtrl::OnCutSegment()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		HBaseView *m_pHView = owner->GetHoopsView();
		
		
		HSelectionSet* selection = 0;
		
		// get ptr to selection object
		selection = (HSelectionSet *)m_pHView->GetSelection();
		HC_KEY key = (HC_KEY)m_pItemUnderCursor->m_pExtraData;
		
		if (selection->IsSelected(key,0,0))
			selection->DeSelect(key);
		HC_Open_Segment("/cutgeometry");
		HC_Flush_Contents(".", "everything");
		HC_Close_Segment();
		
 		HC_Move_By_Key(key, "/cutgeometry");
		
		TreeGraphItem * parent = m_pItemUnderCursor->m_pParentItem;
		m_pItemUnderCursor->m_pParentItem->DeleteChildItem(m_pItemUnderCursor);
		if(strstr(parent->m_pItemText, "SEGMENTS") && !parent->m_pExtraData)
			owner->GetHoopsSegmentTree()->OnItemExpanding(parent->m_pParentItem, true);
		m_pHView->Update();		
		
		m_pHView->SetGeometryChanged();
		owner->ValidateSegmentTree();
		m_pHView->Update();
		// TODO: Add your control notification handler code here		
    }
	
}

void CSegTreeCtrl::OnPasteSegment()
{
    if (m_pItemUnderCursor && HUtility::SegmentExists("/cutgeometry"))
    {
  		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		HBaseView *m_pHView = owner->GetHoopsView();
		
		HSSelectionSet* selection = 0;
		
		// get ptr to selection object
		selection = (HSSelectionSet *)m_pHView->GetSelection();
		
		HC_KEY key = (HC_KEY)m_pItemUnderCursor->m_pExtraData;
		HC_Open_Segment_By_Key(key);
 		HC_Copy_Segment("/cutgeometry/*", "./*");
		HC_Close_Segment();

		owner->GetHoopsSegmentTree()->ExpandSegmentItem(m_pItemUnderCursor, key);

		m_pHView->SetGeometryChanged();
		owner->ValidateSegmentTree();
		m_pHView->Update();	
    }
}

void CSegTreeCtrl::OnSaveToHMF()
{
    if (m_pItemUnderCursor)
    {
  	CString filter;
	CString def_ext;

    	filter = "HOOPS MetaFile File (*.hmf)|*.hmf||";
	def_ext = ".hmf";
 
	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
 	CFileDialog my_dlg(FALSE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);

	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

 
		    if (my_dlg.DoModal() == IDOK)
		{		
			HC_KEY key = (HC_KEY)m_pItemUnderCursor->m_pExtraData;
			HC_Open_Segment_By_Key(key);
			HC_Write_Metafile(".",H_ASCII_TEXT(my_dlg.GetPathName()),"follow cross-references, save state = textures");
			HC_Close_Segment();
 		
		}
		 				
    }
	
}


void CSegTreeCtrl::OnCreateSegment()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		
		HC_Open_Segment_By_Key((HC_KEY)m_pItemUnderCursor->m_pExtraData);
		HC_KEY newsegment = HC_KCreate_Segment("");
		HC_Close_Segment();
		TreeGraphItem *item = owner->GetHoopsSegmentTree()->AddSegmentItem(newsegment,m_pItemUnderCursor);
		owner->GetHoopsSegmentTree()->VerifyChildren(m_pItemUnderCursor);
		owner->GetHoopsSegmentTree()->VerifyChildren(item);
    }
	
}

void CSegTreeCtrl::OnActivateManipulator()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
        HUtilityGeomHandle::SetupManipulator((HC_KEY)m_pItemUnderCursor->m_pExtraData, owner->GetHoopsView(),0);
    }
	
}

void CSegTreeCtrl::OnZoomToSegment()
{
    if (m_pItemUnderCursor)
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		HC_KEY incl_path[1024];
		int incl_count=0;
		HC_KEY key=(HC_KEY)m_pItemUnderCursor->m_pExtraData;

		if (m_pItemUnderCursor->m_pExtraData2)
			key = (HC_KEY)m_pItemUnderCursor->m_pExtraData2;

		if(key==0 || key==INVALID_KEY)
			return;

		owner->GetHoopsSegmentTree()->GetKeyList(m_pItemUnderCursor, incl_path, incl_count, true);
		owner->GetHoopsView()->FitItemByPath(key, incl_count, incl_path);
		owner->GetHoopsView()->Update();
    }
	
}

void CSegTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
    m_pItemUnderCursor = 0;
	CMenu parent_menu;	
    CMenu * popup_menu;
	CRect   rect;
    CPoint  new_menu_position;
    TVITEM istate;
   
    // Display the menu at the mouse click position.
    GetWindowRect(&rect);

    // Transform the screen coordinate point to a window-relative point.
    new_menu_position = CPoint (rect.left + point.x, rect.top + point.y);  
    
    UINT uFlags=0;
    HTREEITEM hti = HitTest(point,&uFlags);
    if (hti)
    {
  		istate.mask = TVIF_HANDLE | TVIF_PARAM;
		istate.hItem = hti;
		GetItem(&istate);
		
		m_pItemUnderCursor= (WindowsTreeGraphItem *)istate.lParam;
    }
    else
    {
		CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
		m_pItemUnderCursor =  (WindowsTreeGraphItem *)owner->GetHoopsSegmentTree()->GetRootItem();
    }

	if((nFlags & MK_CONTROL) && m_pItemUnderCursor->m_pExtraData 
		&& (HC_KEY)m_pItemUnderCursor->m_pExtraData != INVALID_KEY)
	{
		OnZoomToSegment();
		return;
	}
	
	if(m_pItemUnderCursor->m_Flags & READONLY_OBJECT)
		return;
 
	if (!m_pItemUnderCursor->m_pExtraData || (HC_KEY)m_pItemUnderCursor->m_pExtraData == -1)
	{
	    if (m_pItemUnderCursor->m_pItemText2)
	    {
			UINT popup_menu_id = IDR_SEGMENTBROWSERPOPUP2;
			parent_menu.LoadMenu (popup_menu_id);
			popup_menu = parent_menu.GetSubMenu (0);
			popup_menu->TrackPopupMenu( TPM_LEFTALIGN, 
				new_menu_position.x, 
				new_menu_position.y, 
				(CWnd *)this);  
	    }
	}
	else
	{  	  
	    if (HUtility::IsSegmentKey((HC_KEY)m_pItemUnderCursor->m_pExtraData))
	    {	    
			UINT popup_menu_id = IDR_SEGMENTBROWSERPOPUP;
			parent_menu.LoadMenu (popup_menu_id);
			popup_menu = parent_menu.GetSubMenu (0);
			popup_menu->TrackPopupMenu( TPM_LEFTALIGN, 
			new_menu_position.x, 
			new_menu_position.y, 
			(CWnd *)this);  
	    }
	}
	
    CTreeCtrl::OnRButtonDown(nFlags, point);
}


void CSegmentBrowserDlg::OnSelchangeStartsegmentCombo() 
{
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_STARTSEGMENT_COMBO);
	int sel = cbox->GetCurSel();
	bool info_window_visible=m_pHoopsSegmentTree->InfoWindowShown();
	SetMessageTarget(0);
	delete m_pHoopsSegmentTree;
	
 	CString button_text;
	
	switch (sel)
	{
	case 0:	
		{
			HBaseModel *model = (HBaseModel *)(m_pHView->GetModel());
			m_baseKey = model->GetModelKey();
		}
		
		break;
	case 1:
		m_baseKey = m_pHView->GetViewKey();
		break;
	case 2:
		m_baseKey = HC_KOpen_Segment("/");
		HC_Close_Segment();
		break;
	}
	
	m_pHoopsSegmentTree = new HoopsSegmentTree(m_pHView, this,m_baseKey );
	SetMessageTarget(m_pHoopsSegmentTree);
	m_pHoopsSegmentTree->ShowInfoWindow(info_window_visible);
	/*
	HSelectionSet* selection;
	selection = (HSelectionSet *)m_pHView->GetSelection();
	selection->DeSelectAll();
	m_blockValidation = true;
	m_Segment_tree.DeleteAllItems();
	*/
	first_run = true;
	//  	InsertSegmentList(m_baseKey, TVI_ROOT);	
	m_blockValidation = false;
	// TODO: Add your control notification handler code here 	
	
	
}

void CSegmentBrowserDlg::OnRefreshBrowser() 
{
    OnSelchangeStartsegmentCombo();
}

void CSegmentBrowserDlg::RefreshBrowser() 
{
    OnSelchangeStartsegmentCombo();
}

void CSegmentBrowserDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSegTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    m_pItemUnderCursor = 0;
    CMenu parent_menu;	
    CRect   rect;
    CPoint  new_menu_position;
    TVITEM istate;
	
	
	// TODO: Add your message handler code here and/or call default
    if (nChar == VK_DELETE)
    {    
		
		HTREEITEM hti = GetSelectedItem();
		if (hti)
		{
			
			
			CSegmentBrowserDlg *owner = (CSegmentBrowserDlg *)GetOwner();
			istate.mask = TVIF_HANDLE | TVIF_PARAM;
			istate.hItem = hti;
			GetItem(&istate);	
			m_pItemUnderCursor= (WindowsTreeGraphItem *)istate.lParam;

			if(m_pItemUnderCursor->m_Flags & READONLY_OBJECT)
				return;
	
 			if (owner->GetHoopsSegmentTree()->IsAttribute(m_pItemUnderCursor))
			    OnUndefineAttribute();
			else
			{			
			    if (m_pItemUnderCursor->m_pExtraData && (HC_KEY)m_pItemUnderCursor->m_pExtraData != -1 &&
					(!m_pItemUnderCursor->m_pItemText2 || (m_pItemUnderCursor->m_pItemText2[0]!=STATIC_MODEL &&
					m_pItemUnderCursor->m_pItemText2[0]!=GEOMETRY_REFERENCE && 
					m_pItemUnderCursor->m_pItemText2[0]!=SEGMENT_REFERENCE)))
			    OnDeleteSegment();  
			}
		}
    }	
    CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSegmentBrowserDlg::OnCancel()
{
    ;
}


BOOL CSegmentBrowserDlg::PreTranslateMessage(MSG* pMsg)
{
	// If edit control is visible in tree view control, when you send a
	// WM_KEYDOWN message to the edit control it will dismiss the edit
	// control. When the ENTER key was sent to the edit control, the
	// parent window of the tree view control is responsible for updating
	// the item's label in TVN_ENDLABELEDIT notification code.
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		CEdit* edit = m_Segment_tree.GetEditControl();
		if (edit)
		{
            edit->SendMessage(WM_KEYDOWN, pMsg->wParam, pMsg->lParam);
            return TRUE;
		}
	}
	// CXxxx can be a CFormView, Cdialog, or CPropertyPage class.
	return CDialog::PreTranslateMessage(pMsg);
}

void CSegmentBrowserDlg::OnTopologyBrowserSwitch() 
{
	// TODO: Add your control notification handler code here
    CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();
    frame->OnSegmentbrowser();
    frame->OnTopolbrowser();
}

void CSegmentBrowserDlg::OnInterOpPartBrowserSwitch() 
{
	// TODO: Add your control notification handler code here
    CSolidHoopsFrame *frame = (CSolidHoopsFrame *)AfxGetMainWnd();
    frame->OnSegmentbrowser();
    frame->OnInterOpPartBrowser();
}
 
void CSegmentBrowserDlg::OnSearch() 
{
	UpdateData(true);
	if (m_SearchScope==Attribute)
 		GetHoopsSegmentTree()->FindInAttributes(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==Geometry)
 		GetHoopsSegmentTree()->FindInGeometry(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==Segment)
 		GetHoopsSegmentTree()->FindInSegments(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==Include)
 		GetHoopsSegmentTree()->FindInIncludes(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==Style)
 		GetHoopsSegmentTree()->FindInStyles(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==SegmentReference)
 		GetHoopsSegmentTree()->FindInSegmentReferences(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==GeometryReference)
 		GetHoopsSegmentTree()->FindInGeometryReferences(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==Definition)
 		GetHoopsSegmentTree()->FindInDefinitions(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
	else if (m_SearchScope==Keys)
 		GetHoopsSegmentTree()->FindInKeys(H_ASCII_TEXT(m_SearchEdit), GetHoopsSegmentTree()->GetCurrentItem());
}

void CSegmentBrowserDlg::OnSelchangeSearchScope()
{
	CComboBox* pSearchScopeCombo;
	pSearchScopeCombo = (CComboBox*) GetDlgItem(IDC_COMBO_SEARCH_SCOPE);
	ASSERT( pSearchScopeCombo );

	CString cur_sel;
	cur_sel.GetBuffer(pSearchScopeCombo->GetLBTextLen(pSearchScopeCombo->GetCurSel()));
	pSearchScopeCombo->GetLBText(pSearchScopeCombo->GetCurSel(), cur_sel);
	cur_sel.ReleaseBuffer();

	if(cur_sel=="Attribute")
		m_SearchScope=Attribute;
	else if(cur_sel=="Geometry")
		m_SearchScope=Geometry;
	else if(cur_sel=="Segment")
		m_SearchScope=Segment;
	else if(cur_sel=="Include")
		m_SearchScope=Include;
	else if(cur_sel=="Style")
		m_SearchScope=Style;
	else if(cur_sel=="Segment Reference")
		m_SearchScope=SegmentReference;
	else if(cur_sel=="Geometry Reference")
		m_SearchScope=GeometryReference;
	else if(cur_sel=="Definition")
		m_SearchScope=Definition;
	else if(cur_sel=="Keys")
		m_SearchScope=Keys;
	else
		m_SearchScope=Error;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/



CCMMDisplay::CCMMDisplay(CWnd* pParent /*=NULL*/, HBaseView * View)
: CDialog(CCMMDisplay::IDD, pParent)/*,m_pTree(0)*/, m_pView(View)
{

}

CCMMDisplay::~CCMMDisplay()
{

}

bool CCMMDisplay::InsertCollision(HC_KEY const key, HPointKey const & point, int current_tick)
{
	bool retval = false;
	int index = m_InfoList.GetCount();
	int not_used;
	if(m_hash.LookupItem(current_tick, &not_used) != VHASH_STATUS_SUCCESS){
		m_hash.InsertItem(current_tick, index);
		m_InfoList.InsertString(index, H_UNICODE_TEXT(H_FORMAT_TEXT("Crash! %d", current_tick)));
		m_InfoList.SetItemData(index, current_tick);
		retval = true;
	}
	return retval;
}

void CCMMDisplay::RemoveCollision(HC_KEY const key)
{
}

void CCMMDisplay::RemoveCollision(HC_KEY const key, HPointKey const & point)
{
}

bool CCMMDisplay::CollisionInTree(HC_KEY const key, HPointKey const & point)
{
	return false;
}


int CCMMDisplay::ObjectCollisionEvent(HBhvTargetObject *tob){
	float not_used, x = 0, y = 0, z = 0;
	HC_Show_Selection_Position(&not_used, &not_used, &not_used, &x, &y, &z);
	float current_tick = m_pView->GetModel()->GetBhvBehaviorManager()->GetCurrentTick();
	if(InsertCollision(tob->GetTargetKey(), HPointKey(x, y, z), (int)current_tick)){
		HC_Open_Segment_By_Key(m_pView->GetModelKey());{
			HC_Open_Segment("CMMDisplay");{
				HC_Set_Marker_Symbol("+");
				HC_Set_Selectability("off");
				HC_Set_Rendering_Options("attribute lock = selectability");
				HC_Set_Color("yellow, transmission = light grey");
				HC_Set_Rendering_Options("attribute lock = color");
				VCharArray seg_path(MVO_BUFFER_SIZE);
				HC_Show_Segment(tob->GetTargetKey(), seg_path);
				HC_Open_Segment("");{
					HPoint p(x, y, z);
					HC_Copy_Segment(seg_path, ".");
				}HC_Close_Segment();
			}HC_Close_Segment();
		}HC_Close_Segment();
	}
	return HLISTENER_PASS_EVENT;
}

void CCMMDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCMMDisplay)
	DDX_Control(pDX, IDC_CMM_LIST, m_InfoList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCMMDisplay, CDialog)
	//{{AFX_MSG_MAP(CCMMDisplay)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CMM_CLEAR_DISPLAY, CCMMDisplay::OnBnClickedCmmClearDisplay)
	ON_LBN_DBLCLK(IDC_CMM_LIST, CCMMDisplay::OnListItemDblClk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCMMDisplay::OnListItemDblClk()
{
	int cursel = m_InfoList.GetCurSel();
	int item_tick = (int)m_InfoList.GetItemData(cursel);
	m_pView->GetModel()->GetBhvBehaviorManager()->SetCurrentTick(item_tick);
 	m_pView->GetModel()->GetBhvBehaviorManager()->ScheduleAllAnimations();
  	m_pView->GetModel()->GetBhvBehaviorManager()->ExecuteAnimations(m_pView->GetModel()->GetBhvBehaviorManager()->GetCurrentTick(), 0);
	m_pView->Update();
}

void CCMMDisplay::OnBnClickedCmmClearDisplay()
{
	m_InfoList.ResetContent();
	HC_Open_Segment_By_Key(m_pView->GetModelKey());{
		/* Incase the segment doesn't exist, create it unconditionally. */
		HC_Create_Segment("CMMDisplay");
		HC_Delete_Segment("CMMDisplay");
	}HC_Close_Segment();
	m_pView->Update();
}
