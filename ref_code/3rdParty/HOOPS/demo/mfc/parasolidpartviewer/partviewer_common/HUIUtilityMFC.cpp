// HOptionsDlg.cpp : implementation file

#include "stdafx.h"
#include "resource.h"
#include "HUIUtilityMFC.h"
#include "HUtilityLocaleString.h"
#include <io.h>
#include <afxpriv.h>    // for CDockContext in class CDockingDialogBar
#include "StyleDialog.h"
#include "ClashDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(HOptionsPage, CDialog)

HOptionsPage::HOptionsPage()
{
   ASSERT(0);
   // don't use this constructor!
}

HOptionsPage::HOptionsPage(UINT nID, CWnd *pParent /*=NULL*/)
: CDialog(nID)
{
   m_id = nID;
}

HOptionsPage::~HOptionsPage()
{
}

BEGIN_MESSAGE_MAP(HOptionsPage, CDialog)
	//{{AFX_MSG_MAP(CHTMLAppearance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void HOptionsPage::OnOK()
{
   EndDialog(IDOK);
}

void HOptionsPage::OnButtonReset()
{

}

void HOptionsPage::OnButtonApply()
{

}

void HOptionsPage::OnCancel()
{
   EndDialog(IDCANCEL);
}

BOOL HOptionsPage::PreTranslateMessage(MSG* pMsg) 
{
	// Don't let CDialog process the Escape key.
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE))
	{
		return FALSE;
	}
	
	// Don't let CDialog process the Return key, if a multi-line edit has focus
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		// Special case: if control with focus is an edit control with
		// ES_WANTRETURN style, let it handle the Return key.

		TCHAR szClass[MVO_BUFFER_SIZE];
		CWnd* pWndFocus = GetFocus();
		if (((pWndFocus = GetFocus()) != NULL) &&
			IsChild(pWndFocus) &&
			(pWndFocus->GetStyle() & ES_WANTRETURN) &&
			GetClassName(pWndFocus->m_hWnd, szClass, 10) &&
			(lstrcmpi(szClass, _T("EDIT")) == 0))
		{
			pWndFocus->SendMessage(WM_CHAR, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}

		return FALSE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// HOptionsDlg dialog


HOptionsDlg::HOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(HOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(HOptionsDlg)
	//}}AFX_DATA_INIT

   m_iCurPage = -1;
   m_pages.RemoveAll();

	m_pStartPage = NULL;

   m_csTitle = "Untitled";
}

/////////////////////////////////////////////////////////////////////////////

HOptionsDlg::~HOptionsDlg()
{
	// clean up
   for (int i=0;i<m_pages.GetSize();i++)
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(i);
      if (pPS)
         delete pPS;
   }
}

/////////////////////////////////////////////////////////////////////////////

void HOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HOptionsDlg)
	DDX_Control(pDX, IDC_PAGE_TREE, m_pageTree);
	DDX_Control(pDX, IDC_DLG_FRAME, m_boundingFrame);
	DDX_Control(pDX, IDC_CAPTION_BAR, m_captionBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(HOptionsDlg)
	ON_WM_CREATE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_PAGE_TREE, OnSelchangedPageTree)
	ON_NOTIFY(TVN_GETDISPINFO, IDC_PAGE_TREE, OnGetdispinfoPageTree)
	ON_BN_CLICKED(IDC_BUTTON_RESET_ALL, OnResetAll)
	ON_BN_CLICKED(IDC_PHELP, OnPhelp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CHANGE_PAGE, OnChangePage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HOptionsDlg message handlers

/////////////////////////////////////////////////////////////////////////////

BOOL HOptionsDlg::PreTranslateMessage(MSG* pMsg) 
{
	ASSERT(pMsg != NULL);
	ASSERT_VALID(this);
	ASSERT(m_hWnd != NULL);


	if (CWnd::PreTranslateMessage(pMsg))
      return TRUE;

   // don't translate dialog messages when 
   // application is in help mode
   CFrameWnd* pFrameWnd = GetTopLevelFrame();
   if (pFrameWnd != NULL && pFrameWnd->m_bHelpMode)
      return FALSE;

   // ensure the dialog messages will not
   // eat frame accelerators
   pFrameWnd = GetParentFrame();
   while (pFrameWnd != NULL)
   {
      if (pFrameWnd->PreTranslateMessage(pMsg))
         return TRUE;
      pFrameWnd = pFrameWnd->GetParentFrame();
   }

   return PreTranslateInput(pMsg);

}

/////////////////////////////////////////////////////////////////////////////

int HOptionsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////

BOOL HOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

   long l = GetWindowLong(m_pageTree.m_hWnd, GWL_STYLE);
#if (_MSC_VER > 1100)
   l = l | TVS_TRACKSELECT ;
#else
	//#define TVS_TRACKSELECT         0x0200
   l = l | 0x0200;
#endif
   SetWindowLong(m_pageTree.m_hWnd, GWL_STYLE, l);

   // where will the dlgs live?
   m_boundingFrame.GetWindowRect(m_frameRect);
   ScreenToClient(m_frameRect);
   m_frameRect.DeflateRect(2,2);

   SetWindowText(m_csTitle);

//	// set some styles for the pretty page indicator bar
//	m_captionBar.m_textClr     = ::GetSysColor(COLOR_3DFACE);
//	m_captionBar.m_fontWeight  = FW_BOLD;
//	m_captionBar.m_fontSize    = 14;
//	m_captionBar.m_csFontName  = "Verdana";
//	m_captionBar.SetConstantText(m_csConstantText);

	// fill the tree. we'll create the pages as we need them
   for (int i=0;i<m_pages.GetSize();i++)
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(i);
      ASSERT(pPS);
      ASSERT(pPS->pDlg);
      if (pPS)
      {
         TV_INSERTSTRUCT tvi;

         // find this node's parent...
         tvi.hParent = FindHTREEItemForDlg(pPS->pDlgParent);

         tvi.hInsertAfter = TVI_LAST;
         tvi.item.cchTextMax = 0;
         tvi.item.pszText = LPSTR_TEXTCALLBACK;
         tvi.item.lParam = (long)pPS;
         tvi.item.mask = TVIF_PARAM | TVIF_TEXT;

         HTREEITEM hTree = m_pageTree.InsertItem(&tvi);

         // keep track of the dlg's we've added (for parent selection)
         if (hTree)
         {
            DWORD dwTree = (DWORD)hTree;
            m_dlgMap.SetAt(pPS->pDlg, dwTree);
         }
      }
   }

	// start with page 0
	if (m_pStartPage==NULL)
	{
		if (ShowPage(0))
		{
			m_iCurPage = 0;   
		}
	}
	else
	{
		// find start page
		for (int i=0;i<m_pages.GetSize();i++)
		{
			pageStruct *pPS = (pageStruct *)m_pages.GetAt(i);
			ASSERT(pPS);
			if (pPS)
			{
				ASSERT(pPS->pDlg);
				if (pPS->pDlg == m_pStartPage)
				{
					ShowPage(i);
					m_iCurPage = i;
					break;
				}
			}
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////

HTREEITEM HOptionsDlg::FindHTREEItemForDlg(HOptionsPage *pParent)
{
   // if you didn't specify a parent in AddPage(...) , the
   // dialog becomes a root-level entry
	if (pParent==NULL)
	{
		return TVI_ROOT;
	}
   else
   {
      DWORD dwHTree;
      if (m_dlgMap.Lookup(pParent, dwHTree))
      {
          return (HTREEITEM)dwHTree;
      }
      else
      {
         // you have specified a parent that has not 
         // been added to the tree - can't do that.
         ASSERT(FALSE);
         return TVI_ROOT;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////

LRESULT HOptionsDlg::OnChangePage(WPARAM u, LPARAM l)
{
   if (ShowPage(u))
   {
      m_iCurPage = u;   
   }

	return 0L;
}

/////////////////////////////////////////////////////////////////////////////

bool HOptionsDlg::AddPage(HOptionsPage &dlg, const char *pCaption, HOptionsPage* pDlgParent /*=NULL*/)
{
	if (m_hWnd)
	{
		// can't add once the window has been created
		ASSERT(0);
		return false;
	}

   pageStruct *pPS = new pageStruct;
   pPS->pDlg = &dlg;
   pPS->id = dlg.GetID();
   pPS->csCaption = pCaption;
   pPS->pDlgParent = pDlgParent;

   m_pages.Add(pPS);

   return true;
}

/////////////////////////////////////////////////////////////////////////////

BOOL HOptionsDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
      return FALSE;

   cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, NULL, NULL, NULL);
   cs.style |= WS_CLIPCHILDREN;
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

bool HOptionsDlg::ShowPage(HOptionsPage * pPage)
{
   // find that page
	for (int i=0;i<m_pages.GetSize();i++)
	{
		pageStruct *pPS = (pageStruct *)m_pages.GetAt(i);
		ASSERT(pPS);
		if (pPS)
		{
			ASSERT(pPS->pDlg);
			if (pPS->pDlg == pPage)
			{
				ShowPage(i);
				m_iCurPage = i;
				return true;
			}
		}
	}

   return false;
}

/////////////////////////////////////////////////////////////////////////////

HOptionsPage * HOptionsDlg::GetPage(int iPage)
{
	if ((iPage >= 0) && (iPage < m_pages.GetSize()))
	{
		pageStruct *pPS = (pageStruct *)m_pages.GetAt(iPage);
		if (pPS && pPS->pDlg)
		{
			if (!::IsWindow(pPS->pDlg->m_hWnd))
               pPS->pDlg->Create(pPS->pDlg->GetID(), this);

			return pPS->pDlg;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////

int HOptionsDlg::GetPageCount()
{
	return m_pages.GetSize();
}

/////////////////////////////////////////////////////////////////////////////

bool HOptionsDlg::ShowPage(int iPage)
{
   m_captionBar.SetWindowText(_T(""));

	// turn off the current page
   if ((m_iCurPage >= 0) && (m_iCurPage < m_pages.GetSize()))
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(m_iCurPage);
      ASSERT(pPS);
      if (pPS)
      {
         ASSERT(pPS->pDlg);
         if (pPS->pDlg)
         {
            if (::IsWindow(pPS->pDlg->m_hWnd))
            {
               pPS->pDlg->ShowWindow(SW_HIDE);
            }
         }
      }
      else
      {
         return false;
      }
   }

	// show the new one
   if ((iPage >= 0) && (iPage < m_pages.GetSize()))
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(iPage);
      ASSERT(pPS);

      if (pPS)
      {
         ASSERT(pPS->pDlg);
         if (pPS->pDlg)
         {

			   // update caption bar
            m_captionBar.SetWindowText(pPS->csCaption);

            // if we haven't already, Create the dialog
            if (!::IsWindow(pPS->pDlg->m_hWnd))
            {
               pPS->pDlg->Create(pPS->pDlg->GetID(), this);
            }
         
            // move, show, focus
            if (::IsWindow(pPS->pDlg->m_hWnd))
            {
               pPS->pDlg->MoveWindow(m_frameRect.left, m_frameRect.top, m_frameRect.Width(), m_frameRect.Height());
               pPS->pDlg->ShowWindow(SW_SHOW);
               pPS->pDlg->SetFocus();
            }

            // change the tree

            // find this in our map
            HTREEITEM hItem = FindHTREEItemForDlg(pPS->pDlg);
            if (hItem)
            {
               // select it
               m_pageTree.SelectItem(hItem);
            }
            return true;
         }
      }
   }

   return false;
}

/////////////////////////////////////////////////////////////////////////////

void HOptionsDlg::OnOK() 
{
   // if EndOK returns true, all of the UpdateData(TRUE)'s succeeded
   if (EndOK())
   {
	   CDialog::OnOK();
   }
}

/////////////////////////////////////////////////////////////////////////////

bool HOptionsDlg::EndOK()
{
   bool bOK = true;

   HOptionsPage * pPage = NULL;

	// first, UpdateData...
   int i;
   for (i=0;i<m_pages.GetSize();i++)
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(i);
      ASSERT(pPS);
      if (pPS)
      {
         ASSERT(pPS->pDlg);
         if (pPS->pDlg)
         {
            if (::IsWindow(pPS->pDlg->m_hWnd))
            {
               if (!pPS->pDlg->UpdateData(TRUE))
               {
                  bOK = false;
                  pPage = pPS->pDlg;
                  break;
               }
            }
         }
      }
   }

   // were there any UpdateData errors?
   if ((!bOK) && (pPage!=NULL))
   {
      ShowPage(pPage);
      return false;
   }

   // tell all of the sub-dialogs "OK"
   for (i=0;i<m_pages.GetSize();i++)
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(i);
      ASSERT(pPS);
      if (pPS)
      {
         ASSERT(pPS->pDlg);
         if (pPS->pDlg)
         {
            if (::IsWindow(pPS->pDlg->m_hWnd))
            {
               pPS->pDlg->OnOK();
            }
         }
      }
   }

   return true;
}

/////////////////////////////////////////////////////////////////////////////

void HOptionsDlg::OnCancel() 
{
	// tell all of the sub-dialogs "Cancel"
   for (int i=0;i<m_pages.GetSize();i++)
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(i);
      ASSERT(pPS);
      
      if (pPS)
      {
         ASSERT(pPS->pDlg);
         if (pPS->pDlg)
         {
            if (::IsWindow(pPS->pDlg->m_hWnd))
            {
               pPS->pDlg->OnCancel();
            }
         }
      }
   }

	CDialog::OnCancel();
}


/////////////////////////////////////////////////////////////////////////////

void HOptionsDlg::EndSpecial(UINT res, bool bOk)
{
   if (bOk)
   {
      EndOK();
   }

	EndDialog(res);
}

/////////////////////////////////////////////////////////////////////////////

void HOptionsDlg::OnSelchangedPageTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

   if (pNMTreeView->itemNew.lParam)
   {
		// find out which page was selected
      int iIdx = -1;
      for (int i=0;i<m_pages.GetSize();i++)
      {
         if (m_pages.GetAt(i)==(pageStruct *)pNMTreeView->itemNew.lParam)
         {
            iIdx = i;
            break;
         }
      }

		// show that page
      if ((iIdx >= 0) && (iIdx < m_pages.GetSize()))
      {
         pageStruct *pPS = (pageStruct *)m_pages.GetAt(iIdx);
		 (void) pPS;
         if (m_iCurPage!=iIdx)
         {
				PostMessage(WM_CHANGE_PAGE, iIdx);
         }
      }
   }

	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////

void HOptionsDlg::OnGetdispinfoPageTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	// return the caption of the appropriate dialog
   if (pTVDispInfo->item.lParam)
   {
      if (pTVDispInfo->item.mask & TVIF_TEXT)
      {
         pageStruct *pPS = (pageStruct *)pTVDispInfo->item.lParam;
         _tcscpy(pTVDispInfo->item.pszText, pPS->csCaption);
      }
   }
   
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////

void HOptionsDlg::OnPhelp() 
{
	// simulate the property sheet method of sending Help (with WM_NOTIFY)
   if ((m_iCurPage >= 0) && (m_iCurPage < m_pages.GetSize()))
   {
      pageStruct *pPS = (pageStruct *)m_pages.GetAt(m_iCurPage);
      ASSERT(pPS);
      ASSERT(pPS->pDlg);
      if (pPS)
      {
         if (pPS->pDlg)
         {
            if (::IsWindow(pPS->pDlg->m_hWnd))
            {
               // help!
			      NMHDR nm;
			      nm.code=PSN_HELP;
			      nm.hwndFrom=m_hWnd;
			      nm.idFrom=HOptionsDlg::IDD;
			      pPS->pDlg->SendMessage(WM_NOTIFY, 0, (long)&nm);
            }
         }
		}
	}
}

void HOptionsDlg::OnResetAll() 
{
	int i;
	pageStruct *pPS;

	for (i=0; i<m_pages.GetSize(); ++i)
	{
		pPS = (pageStruct *)m_pages.GetAt(i);
		ASSERT(pPS);
		if (pPS)
		{
			ASSERT(pPS->pDlg);
			if (pPS->pDlg)
			{
				if (!::IsWindow(pPS->pDlg->m_hWnd))
				{
					pPS->pDlg->Create(pPS->pDlg->GetID(), this);
				}
				
				pPS->pDlg->OnButtonReset();
			}
		}
	}

}


// The color table, initialized to windows' 20 static colors

COLORREF CColorBtnDlg::colors[20] =
{
    RGB(0,0,0),
    RGB(128,0,0),
    RGB(0,128,0),
    RGB(128,128,0),
    RGB(0,0,128),
    RGB(128,0,128),
    RGB(0,128,128),
    RGB(192,192,192),
    RGB(192,220,192),
    RGB(166,202,240),
    RGB(255,251,240),
    RGB(160,160,164),
    RGB(128,128,128),
    RGB(255,0,0),
    RGB(0,255,0),
    RGB(255,255,0),
    RGB(0,0,255),
    RGB(255,0,255),
    RGB(0,255,255),
    RGB(255,255,255)
};

// MRU table. See notes for Reset()

BYTE CColorBtnDlg::used[20] =
{    
    1,3,5,7,9,11,13,15,17,19,20,18,16,14,12,10,8,6,4,2    
};

/////////////////////////////////////////////////////////////////////////////
// CColorBtn

CColorBtn::CColorBtn()
{
    m_pStyleDialog = 0;
	m_pClashDialog = 0;
    currentcolor = RGB(255,255,255);

    dlg.parent = this;   // This will allow the dialog to position itself

    // Create the pens and brushes that we'll need to draw the button

    nullpen.CreateStockObject(NULL_PEN);
    blackpen.CreateStockObject(BLACK_PEN);
    whitepen.CreateStockObject(WHITE_PEN);

    nullbrush.CreateStockObject(NULL_BRUSH);
    backbrush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
    dkgray.CreatePen(PS_SOLID,1,RGB(128,128,128));         
}


CColorBtn::~CColorBtn()
{
}


BEGIN_MESSAGE_MAP(CColorBtn, CButton)
	//{{AFX_MSG_MAP(CColorBtn)	
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorBtn message handlers


void CColorBtn::DrawItem(LPDRAWITEMSTRUCT lpd)
{
    // Draw the button

    CBrush colorbrush;

    CDC DC;

    DC.Attach(lpd->hDC);
    
    int top,left,bottom,right;

    // Store this for convinience

    top    = lpd->rcItem.top;
    left   = lpd->rcItem.left;
    bottom = lpd->rcItem.bottom;
    right  = lpd->rcItem.right;
                
    colorbrush.CreateSolidBrush(currentcolor);
    
    oldpen   = DC.SelectObject(&nullpen);
    oldbrush = DC.SelectObject(&backbrush);

    // Clear the background using the 3DFACE color.

    DC.Rectangle(&lpd->rcItem);

    // Draw the border

    if (!(lpd->itemState & ODS_SELECTED))
    {
        // Button is up

        DC.SelectObject(&blackpen);

        DC.MoveTo(left,bottom-1);
        DC.LineTo(right-1,bottom-1);
        DC.LineTo(right-1,top);

        DC.SelectObject(&dkgray);

        DC.MoveTo(left+1,bottom-2);
        DC.LineTo(right-2,bottom-2);
        DC.LineTo(right-2,top+1);

        DC.SelectObject(&whitepen);

        DC.LineTo(left+1,top+1);
        DC.LineTo(left+1,bottom-2);
        
    }
    else
    {
        // Button is down

        DC.SelectObject(&dkgray);            

        DC.MoveTo(left,bottom-1);

        DC.LineTo(left,top);
        DC.LineTo(right-1,top);

        DC.SelectObject(&whitepen);

        DC.MoveTo(right-1,top-1);

        DC.LineTo(right-1,bottom-1);
        DC.LineTo(left+1,bottom-1);

        DC.SelectObject(&blackpen);

        DC.MoveTo(left+1,bottom-2);
        DC.LineTo(left+1,top+1);
        DC.LineTo(right-2,top+1);

        // by moving this, we get the things inside the button
        // to draw themselves one pixel down and one to the right.
        // This completes the "pushed" effect

        left++;
        right++;
        bottom++;
        top++;

    }
/*
    // The division

    DC.SelectObject(&whitepen);
    
    DC.MoveTo(right-10,top+4);
    DC.LineTo(right-10,bottom-4);

    DC.SelectObject(dkgray);

    DC.MoveTo(right-11,top+4);
    DC.LineTo(right-11,bottom-4);

    // The triangle

    if (lpd->itemState & ODS_DISABLED)
        DC.SelectObject(dkgray);
    else
        DC.SelectObject(blackpen);
    
    DC.MoveTo(right-4,(bottom/2)-1);
    DC.LineTo(right-9,(bottom/2)-1);

    DC.MoveTo(right-5,(bottom/2));
    DC.LineTo(right-8,(bottom/2));

    if (lpd->itemState & ODS_DISABLED)    
    {
        DC.SetPixel(right-4,(bottom/2)-1,RGB(255,255,255));
        DC.SetPixel(right-5,(bottom/2),RGB(255,255,255));
        DC.SetPixel(right-6,(bottom/2)+1,RGB(255,255,255));
    }
    else
    {
        DC.SetPixel(right-6,(bottom/2)+1,RGB(0,0,0));
    }
*/
    if (!(lpd->itemState & ODS_DISABLED))
    {
        // The color rectangle, only if enabled

        DC.SelectObject(&colorbrush);

        DC.Rectangle(left+5,top+4,right-5,bottom-4);    
  }

    if (lpd->itemState & ODS_FOCUS)
    {
        // Draw the focus
        //
        // It would have been nice just to
        // draw a rectangle using a pen created
        // with the PS_ALTERNATE style, but
        // this is not supported by WIN95

        int i;

        for (i=left+3;i<right-4;i+=2)
        {
            DC.SetPixel(i,top+3,RGB(0,0,0));
            DC.SetPixel(i,bottom-4,RGB(0,0,0));
        }

        for (i=top+3;i<bottom-4;i+=2)
        {
            DC.SetPixel(left+3,i,RGB(0,0,0));
            DC.SetPixel(right-4,i,RGB(0,0,0));
        }       
    }
        
    DC.SelectObject(oldpen);
    DC.SelectObject(oldbrush);


    DC.Detach();    
}


void CColorBtn::OnClicked() 
{
    // When the button is clicked, show the dialog.



    
 	if (dlg.DoModal() == IDOK && !dlg.m_bUndefine)
    {
        currentcolor = CColorBtnDlg::colors[dlg.colorindex];
        InvalidateRect(NULL);
    }	

    float r,g,b;
    r = GetRValue(currentcolor)/255.0f;
    g = GetGValue(currentcolor)/255.0f;
    b = GetBValue(currentcolor)/255.0f;
    if (m_pStyleDialog)
	m_pStyleDialog->ColorButtonClicked(this->GetDlgCtrlID(), r,g,b, dlg.m_bUndefine);
    if (m_pClashDialog)
	m_pClashDialog->ColorButtonClicked(this->GetDlgCtrlID(), r,g,b, dlg.m_bUndefine);
    
}

// Store and Load use an undocumented CWinApp function

BOOL CColorBtn::Store()
{
    return (AfxGetApp()->WriteProfileBinary(_T("ColorData"), _T("ColorTable"),(LPBYTE)CColorBtnDlg::colors,sizeof(COLORREF)*20) &&
            AfxGetApp()->WriteProfileBinary(_T("ColorData"), _T("MRU"),(LPBYTE)CColorBtnDlg::used,sizeof(BYTE)*20));

}

BOOL CColorBtn::Load()
{
    BYTE *data = NULL;
    UINT size;

    // This function allocates the memory it needs

    AfxGetApp()->GetProfileBinary(_T("ColorData"), _T("ColorTable"),&data,&size);	

    if (data)
    {
        // Copy the data into our table and get rid of the buffer

        memcpy((void *)CColorBtnDlg::colors,(void *)data,size);
        free((void *)data);

        AfxGetApp()->GetProfileBinary(_T("ColorData"), _T("MRU"),&data,&size);	

        if (data)
        {
            memcpy((void *)CColorBtnDlg::used,(void *)data,size);
            free((void *)data);
            return TRUE;
        }
        
    }

    // If the loading fails, back to the defaults
    
    Reset();

    return FALSE;
}


void CColorBtn::Reset()
{
    CColorBtnDlg::colors[0]  = RGB(0,0,0);
    CColorBtnDlg::colors[1]  = RGB(128,0,0);
    CColorBtnDlg::colors[2]  = RGB(0,128,0);
    CColorBtnDlg::colors[3]  = RGB(128,128,0);
    CColorBtnDlg::colors[4]  = RGB(0,0,128);
    CColorBtnDlg::colors[5]  = RGB(128,0,128);
    CColorBtnDlg::colors[6]  = RGB(0,128,128);
    CColorBtnDlg::colors[7]  = RGB(192,192,192);
    CColorBtnDlg::colors[8]  = RGB(192,220,192);
    CColorBtnDlg::colors[9]  = RGB(166,202,240);
    CColorBtnDlg::colors[10] = RGB(255,251,240);
    CColorBtnDlg::colors[11] = RGB(160,160,164);
    CColorBtnDlg::colors[12] = RGB(128,128,128);
    CColorBtnDlg::colors[13] = RGB(255,0,0);
    CColorBtnDlg::colors[14] = RGB(0,255,0);
    CColorBtnDlg::colors[15] = RGB(255,255,0);
    CColorBtnDlg::colors[16] = RGB(0,0,255);
    CColorBtnDlg::colors[17] = RGB(255,0,255);
    CColorBtnDlg::colors[18] = RGB(0,255,255);
    CColorBtnDlg::colors[19] = RGB(255,255,255);

    // This "colorful" (no pun intended) order ensures
    // that the colors at the center of the color table
    // will get replaced first. This preserves the white
    // and black colors even if they're not used (They'll
    // get replaced last).
    
    CColorBtnDlg::used[0]= 1;
    CColorBtnDlg::used[1]= 3;
    CColorBtnDlg::used[2]= 5;
    CColorBtnDlg::used[3]= 7;
    CColorBtnDlg::used[4]= 9;
    CColorBtnDlg::used[5]= 11;
    CColorBtnDlg::used[6]= 13;
    CColorBtnDlg::used[7]= 15;
    CColorBtnDlg::used[8]= 17;
    CColorBtnDlg::used[9]= 19;
    CColorBtnDlg::used[10]= 20;
    CColorBtnDlg::used[11]= 18;
    CColorBtnDlg::used[12]= 16;
    CColorBtnDlg::used[13]= 14;
    CColorBtnDlg::used[14]= 12;
    CColorBtnDlg::used[15]= 10;
    CColorBtnDlg::used[16]= 8;
    CColorBtnDlg::used[17]= 6;
    CColorBtnDlg::used[18]= 4;
    CColorBtnDlg::used[19]= 2;
}


void CColorBtn::Serialize( CArchive& ar )
{
    if (ar.IsStoring())
    {
        ar.Write((void *)CColorBtnDlg::colors,sizeof(COLORREF)*20);
        ar.Write((void *)CColorBtnDlg::used,sizeof(BYTE)*20);
    }
    else
    {
        ar.Read((void *)CColorBtnDlg::colors,sizeof(COLORREF)*20);
        ar.Read((void *)CColorBtnDlg::used,sizeof(BYTE)*20);
    }
}




/////////////////////////////////////////////////////////////////////////////
// CColorBtnDlg dialog


CColorBtnDlg::CColorBtnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorBtnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorBtnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CColorBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorBtnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorBtnDlg, CDialog)
	//{{AFX_MSG_MAP(CColorBtnDlg)
	ON_WM_LBUTTONDOWN()	
    ON_WM_DRAWITEM()	
    ON_BN_CLICKED(IDC_OTHER, OnOther)
    ON_BN_CLICKED(5122, OnUndefine)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
    ON_COMMAND_RANGE(IDC_COLOR1,IDC_COLOR20,OnColor)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CColorBtnDlg message handlers

BOOL CColorBtnDlg::OnInitDialog() 
{
 
    CDialog::OnInitDialog();
    if (((CColorBtn *)parent)->m_pStyleDialog || ((CColorBtn *)parent)->m_pClashDialog)
    {    
	
	CButton *cbox = (CButton *)GetDlgItem(5121);
	cbox->SetWindowPos(0,0,0,22,22,SWP_NOMOVE);
	cbox->SetWindowText(_T("..."));
	cbox = (CButton *)GetDlgItem(5122);
	cbox->ShowWindow(SW_SHOW);
    }
    m_bUndefine = false; 
    RECT r,r2;
	
	parent->GetWindowRect(&r);
    
    // Move the dialog to be below the button

    SetWindowPos(NULL,r.left,r.bottom,0,0,SWP_NOSIZE|SWP_NOZORDER);

    GetWindowRect(&r2);

    // Check to see if the dialog has a portion outside the
    // screen, if so, adjust.
    
    if (r2.bottom > GetSystemMetrics(SM_CYSCREEN))
    {   
        r2.top = r.top-(r2.bottom-r2.top);        
    }

    if (r2.right > GetSystemMetrics(SM_CXSCREEN))
    {
        r2.left = GetSystemMetrics(SM_CXSCREEN) - (r2.right-r2.left);
    }

    SetWindowPos(NULL,r2.left,r2.top,0,0,SWP_NOSIZE|SWP_NOZORDER);

    // Capture the mouse, this allows the dialog to close when
    // the user clicks outside.

    // Remember that the dialog has no "close" button.

    SetCapture();
	
	return TRUE; 
}



void CColorBtnDlg::EndDialog( int nResult )
{
    ReleaseCapture();

    CDialog::EndDialog(nResult);
}


void CColorBtnDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    RECT r;

    POINT p;
    p.x = point.x;
    p.y = point.y;

    ClientToScreen(&p);

    GetWindowRect(&r);

    // The user clicked...

    if (!PtInRect(&r,p))
    {
        //  ...outside the dialog, close.

        EndDialog(IDCANCEL);
    }
    else
    {
        //  ...inside the dialog. Since this window
        //     has the mouse captured, its children
        //     get no messages. So, check to see
        //     if the click was in one of its children
        //     and tell him.

        //     If the user clicks inside the dialog
        //     but not on any of the controls,
        //     ChildWindowFromPoint returns a
        //     pointer to the dialog. In this
        //     case we do not resend the message
        //     (obviously) because it would cause
        //     a stack overflow.
        
        CWnd *child = ChildWindowFromPoint(point);

        if (child && child != this)
            child->SendMessage(WM_LBUTTONDOWN,0,0l);
    }
	
	CDialog::OnLButtonDown(nFlags, point);
}


void CColorBtnDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpd) 
{
	CDC dc;
    CPen nullpen;
    CBrush brush;
    CPen *oldpen;
    CBrush *oldbrush;

    // Draw the wells using the current color table

    nullpen.CreateStockObject(NULL_PEN);
    brush.CreateSolidBrush(colors[nIDCtl-IDC_COLOR1]);

    dc.Attach(lpd->hDC);

    oldpen = dc.SelectObject(&nullpen);
    oldbrush = dc.SelectObject(&brush);

    lpd->rcItem.right++;
    lpd->rcItem.bottom++;

    dc.Rectangle(&lpd->rcItem);

    dc.SelectObject(oldpen);
    dc.SelectObject(oldbrush);

    dc.Detach();
	
	CDialog::OnDrawItem(nIDCtl, lpd);
}


void CColorBtnDlg::OnColor(UINT id)
{

    // A well has been clicked, set the color index
    // and close.

    colorindex = id-IDC_COLOR1;
    
    int i;

    // This color is now the MRU

    for (i=0;i<20;i++)
    {
        if (used[colorindex] > used[i])
        {
            used[i]++;
        }
    }

    used[colorindex] = 1;

    EndDialog(IDOK);

}

void CColorBtnDlg::OnUndefine() 
{
    m_bUndefine = true;
    EndDialog(IDOK);

}


void CColorBtnDlg::OnOther() 
{
int i;
COLORREF newcolor;

    // The "Other" button.

    ReleaseCapture();

	CColorDialog dlg;

    dlg.m_cc.Flags |= CC_FULLOPEN;


    if (dlg.DoModal() == IDOK)
    {
        // The user clicked OK.
        // set the color and close
        
        newcolor = dlg.GetColor();            

        // Check to see if the selected color is
        // already in the table.

        colorindex = -1;

        for (i=0;i<20;i++)
        {
            if (colors[i] == newcolor)
            {
                colorindex = i;
                break;
            }
        }

        // If the color was not found,
        // replace the LRU with this color
 
        if (colorindex == -1)
        {
            for (i=0;i<20;i++)
            {
                if (used[i] == 20)
                {
                    colors[i] = newcolor;
                    colorindex = i;                                 
                    break;
                }
            }
        }

        // This is the new MRU

        for (i=0;i<20;i++)
        {
            if (used[colorindex] > used[i])
            {
                used[i]++;
            }         
        }

        used[colorindex] = 1;

        EndDialog(IDOK);

        return;
    }

    // If the user clicked "Cancel" reclaim the mouse capture.

    SetCapture();        	
}


void CColorBtnDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{

    // See notes for OnLButtonDown.
    
    CWnd *child = ChildWindowFromPoint(point,CWP_ALL);
    
    if (child && child != this)
        child->SendMessage(WM_LBUTTONDOWN,0,0l);	
	
	CDialog::OnLButtonUp(nFlags, point);
}

/*
void CColorBtn::PreSubclassWindow() 
{
	SetButtonStyle(GetButtonStyle() | BS_OWNERDRAW);
}
*/

void CColorBtn::PreSubclassWindow() 
{
	SetButtonStyle(GetButtonStyle() | BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CPathDialog dialog

#define IDC_FOLDERTREE		0x3741
#define IDC_TITLE			0x3742
#define IDC_STATUSTEXT		0x3743
#define IDC_NEW_EDIT_PATH	0x3744

// Class CDlgWnd
BEGIN_MESSAGE_MAP(CPathDialogSub, CWnd)
        ON_BN_CLICKED(IDOK, OnOK)
		ON_EN_CHANGE(IDC_NEW_EDIT_PATH, OnChangeEditPath)
END_MESSAGE_MAP()

void CPathDialogSub::OnOK()
{
	::GetWindowText(::GetDlgItem(m_hWnd, IDC_NEW_EDIT_PATH),
		m_pPathDialog->m_szPathName, MAX_PATH);

	if(CPathDialog::MakeSurePathExists(m_pPathDialog->m_szPathName)==0)
	{
		m_pPathDialog->m_bGetSuccess=TRUE;
		::EndDialog(m_pPathDialog->m_hWnd, IDOK);
	}
	else
	{
		::SetFocus(::GetDlgItem(m_hWnd, IDC_NEW_EDIT_PATH));
	}
}

void CPathDialogSub::OnChangeEditPath()
{
	::GetWindowText(::GetDlgItem(m_hWnd, IDC_NEW_EDIT_PATH),
		m_pPathDialog->m_szPathName, MAX_PATH);
	BOOL bEnableOKButton = (_tcslen(m_pPathDialog->m_szPathName)>0);
	SendMessage(BFFM_ENABLEOK, 0, bEnableOKButton);
}
/////////////////////////////////////////////////////////////////////////////
// CPathDialog dialog


CPathDialog::CPathDialog(LPCTSTR lpszCaption, 
						 LPCTSTR lpszTitle, 
						 LPCTSTR lpszInitialPath, 
						 CWnd* pParent)
{
	m_hWnd=NULL;
	m_PathDialogSub.m_pPathDialog= this;
    m_bParentDisabled = FALSE;

    // Get the true parent of the dialog
    m_pParentWnd = CWnd::GetSafeOwner(pParent);

	m_lpszCaption = lpszCaption;
	m_lpszInitialPath = lpszInitialPath;

	memset(&m_bi, 0, sizeof(BROWSEINFO) );
	m_bi.hwndOwner = (m_pParentWnd==NULL)?NULL:m_pParentWnd->GetSafeHwnd();
	m_bi.pszDisplayName = 0;
	m_bi.pidlRoot = 0;
	m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	m_bi.lpfn = BrowseCallbackProc;
	m_bi.lpszTitle = lpszTitle;
}


/////////////////////////////////////////////////////////////////////////////
// CPathDialog message handlers

CString CPathDialog::GetPathName()
{
	return CString(m_szPathName);
}

int CALLBACK CPathDialog::BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam, LPARAM pData) 
{
	CPathDialog* pDlg = (CPathDialog*)pData;

	switch(uMsg) 
	{
	case BFFM_INITIALIZED: 
		{
			RECT rc;
			HWND hEdit;
			HFONT hFont;

			pDlg->m_hWnd = hwnd;

			if(pDlg->m_lpszCaption!=NULL)
			{
				::SetWindowText(hwnd, pDlg->m_lpszCaption);
			}

			VERIFY(pDlg->m_PathDialogSub.SubclassWindow(hwnd));
			::ShowWindow(::GetDlgItem(hwnd, IDC_STATUSTEXT), SW_HIDE);
			::GetWindowRect(::GetDlgItem(hwnd, IDC_FOLDERTREE), &rc);
			rc.bottom = rc.top - 4;
			rc.top = rc.bottom - 23;
			::ScreenToClient(hwnd, (LPPOINT)&rc);
			::ScreenToClient(hwnd, ((LPPOINT)&rc)+1);
			hEdit = ::CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
				WS_CHILD|WS_TABSTOP|WS_VISIBLE|ES_AUTOHSCROLL,
				rc.left, rc.top, 
				rc.right-rc.left, rc.bottom-rc.top, 
				hwnd, NULL, NULL, NULL);
			::SetWindowLong(hEdit, GWL_ID, IDC_NEW_EDIT_PATH);
			::ShowWindow(hEdit, SW_SHOW);

			hFont = (HFONT)::SendMessage(hwnd, WM_GETFONT, 0, 0);
			::SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

			LPCTSTR lpszPath = pDlg->m_lpszInitialPath;
			TCHAR szTemp[MAX_PATH];
			if(lpszPath==NULL)
			{
				::GetCurrentDirectory(MAX_PATH, szTemp );
				lpszPath = szTemp;
			}
			// WParam is TRUE since you are passing a path.
			// It would be FALSE if you were passing a pidl.
			::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,
				(LPARAM)lpszPath);
			break;
		}
	case BFFM_SELCHANGED:
		{
			TCHAR szSelection[MAX_PATH];
			if(!::SHGetPathFromIDList((LPITEMIDLIST)lParam, szSelection) ||
				szSelection[1]!=':')
			{
				szSelection[0] = '\0';
				::SendMessage(hwnd, BFFM_ENABLEOK, 0, FALSE);
			}
			else
			{
				::SendMessage(hwnd, BFFM_ENABLEOK, 0, TRUE);
			}
			::SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szSelection);
			::SetWindowText(::GetDlgItem(hwnd, IDC_NEW_EDIT_PATH), szSelection);
			break;
		}
	default:
		break;
	}
	return 0;
}



int CPathDialog::DoModal() 
{

	/////////////////////////////////////////////////////////
	TCHAR szPathTemp[MAX_PATH];
    m_bi.lpfn = BrowseCallbackProc;  // address of callback function
    m_bi.lParam = (LPARAM)this;      // pass address of object to callback function
	m_bi.pszDisplayName = szPathTemp;

	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;

	int iResult=-1;
	if(SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
//		if((m_pParentWnd!=NULL) && m_pParentWnd->IsWindowEnabled())
//		{
//		  m_pParentWnd->EnableWindow(FALSE);
//		  m_bParentDisabled = TRUE;
//		}
		m_bGetSuccess = FALSE;
		pidl = SHBrowseForFolder(&m_bi);
		if (pidl!=NULL) 
		{
			//not need do this because OnOK function did
			//bSucceeded = SHGetPathFromIDList(pidl, m_szPathName);
			// In C++: 
			pMalloc->Free(pidl);
			//In C:
			//pMalloc->lpVtbl->Free(pMalloc,pidl);
			//pMalloc->lpVtbl->Release(pMalloc);
		}
		if(m_bGetSuccess)
		{
			iResult = IDOK;
		}
		pMalloc->Release();
	}

    if(m_bParentDisabled && (m_pParentWnd!=NULL))
	{
		m_pParentWnd->EnableWindow(TRUE);
	}
    m_bParentDisabled=FALSE;

	return iResult;
}

BOOL CPathDialog::IsFileNameValid(LPCTSTR lpFileName)
{
	if(lpFileName==NULL)
	{
		return FALSE;
	}

	int nLen = (int)_tcslen(lpFileName);
	if(nLen<=0)
	{
		return FALSE;
	}

	//check first char
	switch(lpFileName[0])
	{
	case _T('.'):
	case _T(' '):
	case _T('\t'):
		return FALSE;
	}

	//check last char
	switch(lpFileName[nLen-1])
	{
	case _T('.'):
	case _T(' '):
	case _T('\t'):
		return FALSE;
	}

	//check all
	int i=0;
	while(lpFileName[i]!=0)
	{
		switch(lpFileName[i])
		{
		case _T('\\'):
		case _T('/'):
		case _T(':'):
		case _T('*'):
		case _T('?'):
		case _T('\"'):
		case _T('<'):
		case _T('>'):
		case _T('|'):
			return FALSE;
		}
		i++;
	}


	return TRUE;
}

const TCHAR c_FolderDoesNotExist[] = 
		_T("The folder:\n\n")
		_T("%s\n\n")
		_T("does not exist. Do you want the folder to be created?");
const TCHAR c_szErrInvalidPath[] =
		_T("The folder:")
		_T("\n\n")
		_T("%s\n\n")
		_T("is invalid. Please reenter.");
const TCHAR c_szErrCreatePath[] =
		_T("The folder:")
		_T("\n\n")
		_T("%s")
		_T("\n\ncan not be created. Please double check.");

//return -1: user break;
//return 0: no error
//return 1: lpPath is invalid
//return 2: can not create lpPath
int CPathDialog::MakeSurePathExists(LPCTSTR lpPath)
{
	CString strMsg;
	int iRet = 0;
	try
	{
		//validate path
		iRet=Touch(lpPath, TRUE);
		if(iRet!=0)
		{
			throw iRet;
		}

		if(_taccess(lpPath, 0)==0)
		{
			return (int)0;
		}

		strMsg.Format(c_FolderDoesNotExist, lpPath);
		if(AfxMessageBox(strMsg, MB_YESNO|MB_ICONQUESTION) != IDYES)
		{
			return (int)-1;
		}

		//create path
		iRet=Touch(lpPath, FALSE);
		if(iRet!=0)
		{
			throw iRet; 
		}

		return 0;
	}
	catch(int nErrCode)
	{
		switch(nErrCode)
		{
		case 1:
			strMsg.Format(c_szErrInvalidPath, lpPath);
			break;
		case 2:
		default:
			strMsg.Format(c_szErrCreatePath, lpPath);
			break;
		}

		AfxMessageBox(strMsg, MB_OK|MB_ICONEXCLAMATION);

	}

	return iRet;
}

//return 0: no error
//return 1: lpPath is invalid
//return 2: lpPath can not be created(bValidate==FALSE)
int CPathDialog::Touch(LPCTSTR lpPath, BOOL bValidate)
{
	if(lpPath==NULL)
	{
		return 1;
	}

	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, lpPath);
	int nLen = (int)_tcslen(szPath);

	//path must be "x:\..."
	if( ( nLen<3 ) || 
		( ( szPath[0]<_T('A') || _T('Z')<szPath[0] ) && 
		  ( szPath[0]<_T('a') || _T('z')<szPath[0] ) ||
		( szPath[1]!=_T(':') )|| 
		( szPath[2]!=_T('\\') )
		)
	  )
	{
		return 1;
	}

	int i;
	if(nLen==3)
	{
		if(!bValidate)
		{
			if(_taccess(szPath, 0)!=0)
			{
				return 2;
			}
		}
		return 0;
	}

	i = 3;
	BOOL bLastOne=TRUE;
	LPTSTR lpCurrentName;
	while(szPath[i]!=0)
	{
		lpCurrentName = &szPath[i];
		while( (szPath[i]!=0) && (szPath[i]!=_T('\\')) )
		{
			i++;
		}

		bLastOne =(szPath[i]==0);
		szPath[i] = 0;

		if( !IsFileNameValid(lpCurrentName) )
		{
			return 1;
		}

		if(!bValidate)
		{
			CreateDirectory(szPath, NULL);
			if(_taccess(szPath, 0)!=0)
			{
				return 2;
			}
		}

		if(bLastOne)
		{
			break; //it's done
		}
		else
		{
			szPath[i] = _T('\\');
		}

		i++;
	}

	return (bLastOne?0:1);
}

//return 0: ok
//return 1: error
int CPathDialog::ConcatPath(LPTSTR lpRoot, LPCTSTR lpMorePath)
{
	if(lpRoot==NULL)
	{
		return 1;
	}

	int nLen = (int)_tcslen(lpRoot);

	if(nLen<3)
	{
		return 1;
	}

	if(lpMorePath==NULL)
	{
		return 0;
	}

	if(nLen==3)
	{
		_tcscat(lpRoot, lpMorePath);
		return 0;
	}

	_tcscat(lpRoot, _T("\\"));
	_tcscat(lpRoot, lpMorePath);

	return 0;
}



/////////////////////////////////////////////////////////////////////////////
// CDockingDialogBar

CDockingDialogBar::CDockingDialogBar() : 
m_clrBtnHilight(::GetSysColor(COLOR_BTNHILIGHT)),
m_clrBtnShadow(::GetSysColor(COLOR_BTNSHADOW))
{
    m_sizeMin = CSize(32, 32);
    m_sizeHorz = CSize(200, 200);
    m_sizeVert = CSize(200, 200);
    m_sizeFloat = CSize(200, 200);
	m_nDockBarID = AFX_IDW_DOCKBAR_LEFT;
    m_bTracking = FALSE;
    m_bInRecalcNC = FALSE;
    m_cxEdge = 6;
	m_cxBorder = 3;
	m_cxGripper = 20;
	m_cDialog = NULL;
	m_brushBkgd.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

	// Rob Wolpov 10/15/98 Added support for diagonal resizing
	m_cyBorder	 = 3;		
	m_cCaptionSize = GetSystemMetrics(SM_CYSMCAPTION);
	m_cMinWidth	 = GetSystemMetrics(SM_CXMIN);
	m_cMinHeight	 = GetSystemMetrics(SM_CYMIN);
}

CDockingDialogBar::~CDockingDialogBar()
{
}

BEGIN_MESSAGE_MAP(CDockingDialogBar, CControlBar)
    //{{AFX_MSG_MAP(CDockingDialogBar)
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_NCPAINT()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCHITTEST()
    ON_WM_NCCALCSIZE()
    ON_WM_LBUTTONDOWN()
    ON_WM_CAPTURECHANGED()
    ON_WM_LBUTTONDBLCLK()
	ON_WM_NCLBUTTONDBLCLK()
    ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockingDialogBar message handlers

void CDockingDialogBar::OnUpdateCmdUI(class CFrameWnd *pTarget, int bDisableIfNoHndler)
{
    UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

BOOL CDockingDialogBar::Create(CWnd* pParentWnd, CDialog *pDialog, CString &pTitle, UINT nID, DWORD dwStyle) 
{
    ASSERT_VALID(pParentWnd);   // must have a parent
    ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));
	
    // save the style -- AMENDED by Holger Thiele - Thankyou
    m_dwStyle = dwStyle & CBRS_ALL;

	// create the base window
    CString wndclass = AfxRegisterWndClass(CS_DBLCLKS, LoadCursor(NULL, IDC_ARROW),
        m_brushBkgd, 0);
    if (!CWnd::Create(wndclass, pTitle, dwStyle, CRect(0,0,0,0),
        pParentWnd, nID))
        return FALSE;

	// set the new dialog
	ChangeDialog(pDialog, nID);
//	// create the child dialog
//	m_cDialog = pDialog;
//	// if the dialog hasn't been fully created, create it
//	if( !m_cDialog->GetSafeHwnd() )
//		m_cDialog->Create(resourceID, this);
//
//	m_cDialog->ShowWindow(SW_SHOW);
//	// use the dialog dimensions as default base dimensions
//	CRect rc;
//	m_cDialog->GetWindowRect(rc);
//	m_sizeHorz = m_sizeVert = m_sizeFloat = rc.Size();
//	m_sizeHorz.cy += m_cxEdge + m_cxBorder;
//	m_sizeVert.cx += m_cxEdge + m_cxBorder;

// we don't want tooltips showing up if we're running the QA target
#ifdef HOOPS_QA
    EnableToolTips(false);
#endif

    return TRUE;
}

CSize CDockingDialogBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
    CRect rc;

    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rc);
    int nHorzDockBarWidth = bStretch ? 32767 : rc.Width() + 4;
    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rc);
    int nVertDockBarHeight = bStretch ? 32767 : rc.Height() + 4;

	if(IsFloating())
		return m_sizeFloat;
    else if (bHorz)
        return CSize(nHorzDockBarWidth, m_sizeHorz.cy);
    else
        return CSize(m_sizeVert.cx, nVertDockBarHeight);
}

CSize CDockingDialogBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	// Rob Wolpov 10/15/98 Added support for diagonal sizing
	if (IsFloating())
	{
		// Enable diagonal arrow cursor for resizing
		GetParent()->GetParent()->ModifyStyle(MFS_4THICKFRAME,0);
	}    
	if (dwMode & (LM_HORZDOCK | LM_VERTDOCK))
	{
		SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER |
			SWP_NOACTIVATE | SWP_FRAMECHANGED);
	 	m_pDockSite->RecalcLayout();
	    return CControlBar::CalcDynamicLayout(nLength,dwMode);
	}

    if (dwMode & LM_MRUWIDTH)
        return m_sizeFloat;

    if (dwMode & LM_COMMIT)
    {
        m_sizeFloat.cx = nLength;
        return m_sizeFloat;
    }

	// Rob Wolpov 10/15/98 Added support for diagonal sizing
	if (IsFloating())
	{
		RECT	window_rect;
		POINT	cursor_pt;
		
		GetCursorPos(&cursor_pt);
		GetParent()->GetParent()->GetWindowRect(&window_rect);
		
		switch (m_pDockContext->m_nHitTest)
		{
		case HTTOPLEFT:
			m_sizeFloat.cx = max(window_rect.right - cursor_pt.x,
				m_cMinWidth) - m_cxBorder;
			m_sizeFloat.cy = max(window_rect.bottom - m_cCaptionSize - 
				cursor_pt.y,m_cMinHeight) - 1;
			m_pDockContext->m_rectFrameDragHorz.top = min(cursor_pt.y,
				window_rect.bottom - m_cCaptionSize - m_cMinHeight) - 
				m_cyBorder;
			m_pDockContext->m_rectFrameDragHorz.left = min(cursor_pt.x,
				window_rect.right - m_cMinWidth) - 1;
			return m_sizeFloat;
			
		case HTTOPRIGHT:
			m_sizeFloat.cx = max(cursor_pt.x - window_rect.left,
				m_cMinWidth);
			m_sizeFloat.cy = max(window_rect.bottom - m_cCaptionSize - 
				cursor_pt.y,m_cMinHeight) - 1;
			m_pDockContext->m_rectFrameDragHorz.top = min(cursor_pt.y,
				window_rect.bottom - m_cCaptionSize - m_cMinHeight) - 
				m_cyBorder;
			return m_sizeFloat;
			
		case HTBOTTOMLEFT:
			m_sizeFloat.cx = max(window_rect.right - cursor_pt.x,
				m_cMinWidth) - m_cxBorder;
			m_sizeFloat.cy = max(cursor_pt.y - window_rect.top - 
				m_cCaptionSize,m_cMinHeight);
			m_pDockContext->m_rectFrameDragHorz.left = min(cursor_pt.x,
				window_rect.right - m_cMinWidth) - 1;
			return m_sizeFloat;
			
		case HTBOTTOMRIGHT:
			m_sizeFloat.cx = max(cursor_pt.x - window_rect.left,
				m_cMinWidth);
			m_sizeFloat.cy = max(cursor_pt.y - window_rect.top - 
				m_cCaptionSize,m_cMinHeight);
			return m_sizeFloat;
		}
	}
	
	if (dwMode & LM_LENGTHY)
        return CSize(m_sizeFloat.cx,
            m_sizeFloat.cy = max(m_sizeMin.cy, nLength));
    else
        return CSize(max(m_sizeMin.cx, nLength), m_sizeFloat.cy);
}

void CDockingDialogBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    CControlBar::OnWindowPosChanged(lpwndpos);

	if(!::IsWindow(m_hWnd) || m_cDialog==NULL)
		return;
	if(!::IsWindow(m_cDialog->m_hWnd))
		return;
    if (m_bInRecalcNC) 
	{
		CRect rc;
		GetClientRect(rc);
		m_cDialog->MoveWindow(rc);
		return;
	}

    // Find on which side are we docked
    UINT nDockBarID = GetParent()->GetDlgCtrlID();

    // Return if dropped at same location
    if (nDockBarID == m_nDockBarID // no docking side change
        && (lpwndpos->flags & SWP_NOSIZE) // no size change
        && ((m_dwStyle & CBRS_BORDER_ANY) != CBRS_BORDER_ANY))
        return; 

    m_nDockBarID = nDockBarID;

    // Force recalc the non-client area
    m_bInRecalcNC = TRUE;
    SetWindowPos(NULL, 0,0,0,0,
        SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
    m_bInRecalcNC = FALSE;
}

BOOL CDockingDialogBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if ((nHitTest != HTSIZE) || m_bTracking)
        return CControlBar::OnSetCursor(pWnd, nHitTest, message);

    if (IsHorz())
        SetCursor(LoadCursor(NULL, IDC_SIZENS));
    else
        SetCursor(LoadCursor(NULL, IDC_SIZEWE));
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// Mouse Handling
//
void CDockingDialogBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if (!m_bTracking)
        CControlBar::OnLButtonUp(nFlags, point);
    else
    {
        ClientToWnd(point);
        StopTracking(TRUE);
    }
}

void CDockingDialogBar::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (IsFloating() || !m_bTracking)
    {
        CControlBar::OnMouseMove(nFlags, point);
        return;
    }

    CPoint cpt = m_rectTracker.CenterPoint();

    ClientToWnd(point);

    if (IsHorz())
    {
        if (cpt.y != point.y)
        {
            OnInvertTracker(m_rectTracker);
            m_rectTracker.OffsetRect(0, point.y - cpt.y);
            OnInvertTracker(m_rectTracker);
        }
    }
    else 
    {
        if (cpt.x != point.x)
        {
            OnInvertTracker(m_rectTracker);
            m_rectTracker.OffsetRect(point.x - cpt.x, 0);
            OnInvertTracker(m_rectTracker);
        }
    }
}

void CDockingDialogBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
    // Compute the rectangle of the mobile edge
    GetWindowRect(m_rectBorder);
    m_rectBorder = CRect(0, 0, m_rectBorder.Width(), m_rectBorder.Height());
    
    DWORD dwBorderStyle = m_dwStyle | CBRS_BORDER_ANY;

    switch(m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        dwBorderStyle &= ~CBRS_BORDER_BOTTOM;
        lpncsp->rgrc[0].left += m_cxGripper;
        lpncsp->rgrc[0].bottom += -m_cxEdge;
        lpncsp->rgrc[0].top += m_cxBorder;
        lpncsp->rgrc[0].right += -m_cxBorder;
	    m_rectBorder.top = m_rectBorder.bottom - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        dwBorderStyle &= ~CBRS_BORDER_TOP;
        lpncsp->rgrc[0].left += m_cxGripper;
        lpncsp->rgrc[0].top += m_cxEdge;
        lpncsp->rgrc[0].bottom += -m_cxBorder;
        lpncsp->rgrc[0].right += -m_cxBorder;
        m_rectBorder.bottom = m_rectBorder.top + m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_LEFT:
        dwBorderStyle &= ~CBRS_BORDER_RIGHT;
        lpncsp->rgrc[0].right += -m_cxEdge;
        lpncsp->rgrc[0].left += m_cxBorder;
        lpncsp->rgrc[0].bottom += -m_cxBorder;
        lpncsp->rgrc[0].top += m_cxGripper;
        m_rectBorder.left = m_rectBorder.right - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_RIGHT:
        dwBorderStyle &= ~CBRS_BORDER_LEFT;
        lpncsp->rgrc[0].left += m_cxEdge;
        lpncsp->rgrc[0].right += -m_cxBorder;
        lpncsp->rgrc[0].bottom += -m_cxBorder;
        lpncsp->rgrc[0].top += m_cxGripper;
        m_rectBorder.right = m_rectBorder.left + m_cxEdge;
        break;
    default:
        m_rectBorder.SetRectEmpty();
        break;
    }

    SetBarStyle(dwBorderStyle);
}

void CDockingDialogBar::OnNcPaint() 
{
    EraseNonClient();

	CWindowDC dc(this);
    dc.Draw3dRect(m_rectBorder, GetSysColor(COLOR_BTNHIGHLIGHT),
                    GetSysColor(COLOR_BTNSHADOW));

	DrawGripper(dc);
	
	CRect pRect;
//	GetClientRect( &pRect );
//	InvalidateRect( &pRect, TRUE );
}

void CDockingDialogBar::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
    if (m_bTracking) return;

	if((nHitTest == HTSYSMENU) && !IsFloating())
        GetDockingFrame()->ShowControlBar(this, FALSE, FALSE);
    else if ((nHitTest == HTMINBUTTON) && !IsFloating())
        m_pDockContext->ToggleDocking();
	else if ((nHitTest == HTCAPTION) && !IsFloating() && (m_pDockBar != NULL))
    {
        // start the drag
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->StartDrag(point);
    }
    else if ((nHitTest == HTSIZE) && !IsFloating())
        StartTracking();
    else    
        CControlBar::OnNcLButtonDown(nHitTest, point);
}


#if (_MSC_VER < 1400)
UINT 
#else
LRESULT
#endif
CDockingDialogBar::OnNcHitTest(CPoint point) 
{
    if (IsFloating())
        return CControlBar::OnNcHitTest(point);

    CRect rc;
    GetWindowRect(rc);
    point.Offset(-rc.left, -rc.top);
	if(m_rectClose.PtInRect(point))
		return HTSYSMENU;
	else if (m_rectUndock.PtInRect(point))
		return HTMINBUTTON;
	else if (m_rectGripper.PtInRect(point))
		return HTCAPTION;
    else if (m_rectBorder.PtInRect(point))
        return HTSIZE;
    else
        return CControlBar::OnNcHitTest(point);
}

void CDockingDialogBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // only start dragging if clicked in "void" space
    if (m_pDockBar != NULL)
    {
        // start the drag
        ASSERT(m_pDockContext != NULL);
        ClientToScreen(&point);
        m_pDockContext->StartDrag(point);
    }
    else
    {
        CWnd::OnLButtonDown(nFlags, point);
    }
}

void CDockingDialogBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    // only toggle docking if clicked in "void" space
    if (m_pDockBar != NULL)
    {
        // toggle docking
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->ToggleDocking();
    }
    else
    {
        CWnd::OnLButtonDblClk(nFlags, point);
    }
}

void CDockingDialogBar::StartTracking()
{
    SetCapture();

    // make sure no updates are pending
    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
    m_pDockSite->LockWindowUpdate();

    m_ptOld = m_rectBorder.CenterPoint();
    m_bTracking = TRUE;
    
    m_rectTracker = m_rectBorder;
    if (!IsHorz()) m_rectTracker.bottom -= 4;

    OnInvertTracker(m_rectTracker);
}

void CDockingDialogBar::OnCaptureChanged(CWnd *pWnd) 
{
    if (m_bTracking && pWnd != this)
        StopTracking(FALSE); // cancel tracking

    CControlBar::OnCaptureChanged(pWnd);
}

void CDockingDialogBar::StopTracking(BOOL bAccept)
{
    OnInvertTracker(m_rectTracker);
    m_pDockSite->UnlockWindowUpdate();
    m_bTracking = FALSE;
    ReleaseCapture();
    
    if (!bAccept) return;

    int maxsize, minsize, newsize;
    CRect rcc;
    m_pDockSite->GetWindowRect(rcc);

    newsize = IsHorz() ? m_sizeHorz.cy : m_sizeVert.cx;
    maxsize = newsize + (IsHorz() ? rcc.Height() : rcc.Width());
    minsize = IsHorz() ? m_sizeMin.cy : m_sizeMin.cx;

    CPoint point = m_rectTracker.CenterPoint();
    switch (m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        newsize += point.y - m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        newsize += -point.y + m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_LEFT:
        newsize += point.x - m_ptOld.x; break;
    case AFX_IDW_DOCKBAR_RIGHT:
        newsize += -point.x + m_ptOld.x; break;
    }

    newsize = max(minsize, min(maxsize, newsize));

    if (IsHorz())
        m_sizeHorz.cy = newsize;
    else
        m_sizeVert.cx = newsize;

    m_pDockSite->RecalcLayout();
}

void CDockingDialogBar::OnInvertTracker(const CRect& rect)
{
    ASSERT_VALID(this);
    ASSERT(!rect.IsRectEmpty());
    ASSERT(m_bTracking);

    CRect rct = rect, rcc, rcf;
    GetWindowRect(rcc);
    m_pDockSite->GetWindowRect(rcf);

    rct.OffsetRect(rcc.left - rcf.left, rcc.top - rcf.top);
    rct.DeflateRect(1, 1);

    CDC *pDC = m_pDockSite->GetDCEx(NULL,
        DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);

    CBrush* pBrush = CDC::GetHalftoneBrush();
    HBRUSH hOldBrush = NULL;
    if (pBrush != NULL)
        hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);

    pDC->PatBlt(rct.left, rct.top, rct.Width(), rct.Height(), PATINVERT);

    if (hOldBrush != NULL)
        SelectObject(pDC->m_hDC, hOldBrush);

    m_pDockSite->ReleaseDC(pDC);
}

BOOL CDockingDialogBar::IsHorz() const
{
    return (m_nDockBarID == AFX_IDW_DOCKBAR_TOP ||
        m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM);
}

CPoint& CDockingDialogBar::ClientToWnd(CPoint& point)
{
    if (m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM)
        point.y += m_cxEdge;
    else if (m_nDockBarID == AFX_IDW_DOCKBAR_RIGHT)
        point.x += m_cxEdge;

    return point;
}

void CDockingDialogBar::DrawGripper(CDC & dc)
{
    // no gripper if floating
	if( m_dwStyle & CBRS_FLOATING )
		return;

	// -==HACK==-
	// in order to calculate the client area properly after docking,
	// the client area must be recalculated twice (I have no idea why)
	m_pDockSite->RecalcLayout();
	// -==END HACK==-

	CRect gripper;
	GetWindowRect( gripper );
	ScreenToClient( gripper );
	gripper.OffsetRect( -gripper.left, -gripper.top );
	
	if( m_dwStyle & CBRS_ORIENT_HORZ ) {
		
		// gripper at left
		m_rectGripper.top		= gripper.top + 40;
		m_rectGripper.bottom	= gripper.bottom;
		m_rectGripper.left		= gripper.left;
		m_rectGripper.right	= gripper.left + 20;

		// draw close box
		m_rectClose.left = gripper.left + 7;
		m_rectClose.right = m_rectClose.left + 12;
		m_rectClose.top = gripper.top + 10;
		m_rectClose.bottom = m_rectClose.top + 12;
		dc.DrawFrameControl(m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE);

		// draw docking toggle box
		m_rectUndock = m_rectClose;
		m_rectUndock.OffsetRect(0,13);
		dc.DrawFrameControl(m_rectUndock, DFC_CAPTION, DFCS_CAPTIONMAX);

		gripper.top += 38;
		gripper.bottom -= 10;
		gripper.left += 10;
		gripper.right = gripper.left+3;
        dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
		
		gripper.OffsetRect(4, 0);
        dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
	}
	
	else {
		
		// gripper at top
		m_rectGripper.top		= gripper.top;
		m_rectGripper.bottom	= gripper.top + 20;
		m_rectGripper.left		= gripper.left;
		m_rectGripper.right		= gripper.right - 40;

		// draw close box
		m_rectClose.right = gripper.right - 10;
		m_rectClose.left = m_rectClose.right - 11;
		m_rectClose.top = gripper.top + 7;
		m_rectClose.bottom = m_rectClose.top + 11;
		dc.DrawFrameControl(m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE);


		// draw docking toggle box
		m_rectUndock = m_rectClose;
		m_rectUndock.OffsetRect(-13,0);
		dc.DrawFrameControl(m_rectUndock, DFC_CAPTION, DFCS_CAPTIONMAX);

		gripper.right -= 38;
		gripper.left += 10;
		gripper.top += 10;
		gripper.bottom = gripper.top+3;
		dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
		
		gripper.OffsetRect(0, 4);
        dc.Draw3dRect( gripper, m_clrBtnHilight, m_clrBtnShadow );
	}

}

void CDockingDialogBar::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if ((m_pDockBar != NULL) && (nHitTest == HTCAPTION))
    {
        // toggle docking
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->ToggleDocking();
    }
    else
    {
        CWnd::OnNcLButtonDblClk(nHitTest, point);
    }
}


void CDockingDialogBar::ChangeDialog(CDialog *pDialog, UINT nID)
{
	assert(pDialog);

	// hide the existing one
	if( m_cDialog && m_cDialog->GetSafeHwnd() )
		m_cDialog->ShowWindow(SW_HIDE);

	m_cDialog = pDialog;
	// if the dialog hasn't been fully created, create it
	if( !m_cDialog->GetSafeHwnd() )
		m_cDialog->Create(nID, this);

	m_cDialog->ShowWindow(SW_SHOW);

	CRect rc;
	m_cDialog->GetWindowRect(rc);
	m_sizeHorz = m_sizeVert = m_sizeFloat = rc.Size();
	m_sizeHorz.cy += m_cxEdge + m_cxBorder;
	m_sizeVert.cx += m_cxEdge + m_cxBorder;
 	m_cDialog->ShowWindow(SW_SHOW);

 int maxsize, minsize, newsize;
    CRect rcc;
    m_pDockSite->GetWindowRect(rcc);

    newsize = IsHorz() ? m_sizeHorz.cy : m_sizeVert.cx;
    maxsize = newsize + (IsHorz() ? rcc.Height() : rcc.Width());
    minsize = IsHorz() ? m_sizeMin.cy : m_sizeMin.cx;

    CPoint point = m_rectTracker.CenterPoint();
    /*
    switch (m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        newsize += point.y - m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        newsize += -point.y + m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_LEFT:
        newsize += point.x - m_ptOld.x; break;
    case AFX_IDW_DOCKBAR_RIGHT:
        newsize += -point.x + m_ptOld.x; break;
    }
*/
    newsize = max(minsize, min(maxsize, newsize));

    if (IsHorz())
        m_sizeHorz.cy = newsize;
    else
        m_sizeVert.cx = newsize;

    m_pDockSite->RecalcLayout();
 		
		GetClientRect(rc);
		m_cDialog->MoveWindow(rc);
 
 
}


/////////////////////////////////////////////////////////////////////////////
// Button states

#define BTN_UP			0
#define BTN_DOWN		1
#define BTN_DISABLED	2

/////////////////////////////////////////////////////////////////////////////
// Helper function

BOOL IsWindow (CWnd *pWnd)
{
	if (!pWnd)
		return (FALSE);
	return ::IsWindow (pWnd->m_hWnd);
}

/////////////////////////////////////////////////////////////////////////////
// wcSliderButton

IMPLEMENT_DYNAMIC (wcSliderButton, CEdit)

wcSliderButton::wcSliderButton ( void )
{
	m_Pos				= 0;
	m_Min				= 0;
	m_Max				= 100;
	m_bButtonLeft		= FALSE;
	m_bMouseCaptured	= FALSE;
	m_nButtonState		= BTN_UP;
	m_rcButtonRect.SetRectEmpty();
}

wcSliderButton::~wcSliderButton()
{
}

BEGIN_MESSAGE_MAP(wcSliderButton, CEdit)
	//{{AFX_MSG_MAP(wcSliderButton)
	ON_WM_CHAR()
	ON_WM_DESTROY()
	ON_WM_ENABLE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCPAINT()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
    ON_MESSAGE(CSP_DELTAPOS, OnSliderDelta)
    ON_MESSAGE(CSP_CLOSEUP,  OnSliderClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// wcSliderButton message handlers

void wcSliderButton::ButtonClicked()
{
	CString Val;
	GetWindowText (Val);
	m_Pos = atoi (H_ASCII_TEXT(Val.GetBuffer(0)));
	CheckPosRange ();

	CRect Win = m_rcButtonRect;
	Win.left -= GetPosPerc()  + (m_rcButtonRect.Width());

	ClientToScreen (&Win);
	DrawButton (BTN_DOWN);
	new wcSliderPopup (CPoint(Win.left, Win.bottom), m_Pos, m_Min, m_Max, this);
}

LRESULT wcSliderButton::OnSliderDelta(WPARAM lParam, LPARAM wParam)
{
    CWnd *pParent = GetParent();
    if ( pParent ) 
		 pParent->SendMessage(CSP_DELTAPOS, lParam, (WPARAM) GetDlgCtrlID());
		
	SetPos (lParam);
    return TRUE;
}

LRESULT wcSliderButton::OnSliderClose(WPARAM lParam, LPARAM wParam)
{
	DrawButton (BTN_UP);
    CWnd *pParent = GetParent();
    if (pParent) {
        pParent->SendMessage(CSP_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
    }

    return TRUE;
}

BOOL wcSliderButton::Create(BOOL LeftBut, DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	// Create this control in any window
	BOOL bResult = CreateEx(dwExStyle, _T("EDIT"), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	if (bResult)
	{
		// call wcSliderButton::FindFolder() to initialize the internal data structures
		SetLeftButton(LeftBut);
		// Force a call to wcSliderButton::OnNcCalcSize() to calculate button size
		SetWindowPos(NULL,0,0,0,0,SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
		// set the font to the font used by the parent window
		if (pParentWnd)
			SetFont (pParentWnd->GetFont());
	}
	return bResult;
}

void wcSliderButton::DrawButton(int nButtonState)
{
	ASSERT (IsWindow(this));
	
	// if the control is disabled, ensure the button is drawn disabled
	if (GetStyle() & WS_DISABLED)
		nButtonState = BTN_DISABLED;

	// Draw the button in the specified state (Up, Down, or Disabled)
	CWindowDC DC(this);		// get the DC for drawing

	DWORD dwStyle = DFCS_SCROLLDOWN;
	if ( nButtonState == BTN_DOWN )
		 dwStyle |= DFCS_PUSHED;
	if ( nButtonState == BTN_DISABLED )
		 dwStyle |=DFCS_INACTIVE;
	DC.DrawFrameControl(&m_rcButtonRect,DFC_SCROLL,dwStyle);
	// update m_nButtonState
	m_nButtonState = nButtonState;
}

void wcSliderButton::OnEnable(BOOL bEnable) 
{
	// enables/disables the control
	CEdit::OnEnable(bEnable);
	DrawButton (bEnable ? BTN_UP : BTN_DISABLED);
}

void wcSliderButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// check for CTRL + 'period' keystroke, if found, simulate a mouse click on the button
	if ((nChar == 0xBE || nChar == VK_DECIMAL) && GetKeyState(VK_CONTROL) < 0)
		ButtonClicked();
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////////////
// Because the mouse is captured in OnNcLButtonDown(), we have to respond	//
// to WM_LBUTTONUP and WM_MOUSEMOVE messages.								//
// The m_bMouseCaptured variable is used because CEdit::OnLButtonDown()		//
// also captures the mouse, so using GetCapture() could give an invalid		//
// response.																//
//////////////////////////////////////////////////////////////////////////////

void wcSliderButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CEdit::OnLButtonUp(nFlags, point);

	// Release the mouse capture and draw the button as normal. If the
	// cursor is over the button, simulate a click by carrying
	// out the required action.
	if (m_bMouseCaptured)
	{
		ReleaseCapture();
		m_bMouseCaptured = FALSE;
		if (m_nButtonState != BTN_UP)
			DrawButton(BTN_UP);
		ClientToScreen(&point);
		if (ScreenPointInButtonRect(point))
			ButtonClicked();
	}
}

void wcSliderButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CEdit::OnMouseMove(nFlags, point);

	// presses and releases the button as the mouse is moved over and
	// off the button. we check the current button state to avoid
	// unnecessary flicker
	if (m_bMouseCaptured)
	{
		ClientToScreen(&point);
		if (ScreenPointInButtonRect(point))
		{
			if (m_nButtonState != BTN_DOWN)
				DrawButton (BTN_DOWN);
		}
		else if (m_nButtonState != BTN_UP)
			DrawButton (BTN_UP);
	}
}

void wcSliderButton::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// calculate the size of the client area and the button.
	CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);
	// set button area equal to client area of edit control
	m_rcButtonRect = lpncsp->rgrc[0];
	if (m_bButtonLeft)		// draw the button on the left side of the control
	{
		// shrink left side of client area by 80% of the height of client area
		lpncsp->rgrc[0].left += (lpncsp->rgrc[0].bottom - lpncsp->rgrc[0].top) * 8/10;
		// shrink the button so its right side is at the left side of client area
		m_rcButtonRect.right = lpncsp->rgrc[0].left;
	}
	else					// draw the button on the right side of the control
	{
		// shrink right side of client area by 80% of the height of client area
		lpncsp->rgrc[0].right -= (lpncsp->rgrc[0].bottom - lpncsp->rgrc[0].top) * 8/10;
		// shrink the button so its left side is at the right side of client area
		m_rcButtonRect.left = lpncsp->rgrc[0].right;
	}
	if (bCalcValidRects)
		// convert button coordinates from parent client coordinates to control window coordinates
		m_rcButtonRect.OffsetRect(-lpncsp->rgrc[1].left, -lpncsp->rgrc[1].top);
	m_rcButtonRect.NormalizeRect();
}

#if (_MSC_VER < 1400)
UINT 
#else
LRESULT
#endif
wcSliderButton::OnNcHitTest(CPoint point) 
{
	// If the mouse is over the button, OnNcHitTest() would normally return
	// HTNOWHERE, and we would not get any mouse messages. So we return 
	// HTBORDER to ensure we get them.
	UINT where = CEdit::OnNcHitTest(point);
	if (where == HTNOWHERE && ScreenPointInButtonRect(point))
		where = HTBORDER;
	return where;
}

void wcSliderButton::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	CEdit::OnNcLButtonDown(nHitTest, point);

	if (ScreenPointInButtonRect(point))
	{
		// Capture mouse input, set the focus to this control,
		// and draw the button as pressed
		SetCapture();
		m_bMouseCaptured = TRUE;
		SetFocus();
		DrawButton(BTN_DOWN);
	}
}

void wcSliderButton::OnNcPaint() 
{
	CEdit::OnNcPaint();				// draws the border around the control
	DrawButton (m_nButtonState);	// draw the button in its current state
}

void wcSliderButton::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	// Select all the text
	SetSel(0,-1);
}

void wcSliderButton::OnSize(UINT nType, int cx, int cy) 
{
	CEdit::OnSize(nType, cx, cy);
	// Force a recalculation of the button's size and position
	SetWindowPos (NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

BOOL wcSliderButton::ScreenPointInButtonRect(CPoint point)
{
	// Checks if the given point (in screen coordinates) is in the button rectangle
	CRect ControlRect;
	GetWindowRect(&ControlRect);

	// convert point from screen coordinates to window coordinates
	point.Offset(-ControlRect.left, -ControlRect.top);
	return m_rcButtonRect.PtInRect(point);
}

void wcSliderButton::SetLeftButton(BOOL Left)
{
	m_bButtonLeft = Left;
}

void wcSliderButton::SetPos ( int Pos )
{
	if ( Pos >= m_Min && Pos <= m_Max )
	{
		 m_Pos = Pos;
		 CString Tmp;
		 Tmp.Format (_T("%d"), m_Pos);
		 SetWindowText (Tmp);
	}
}

void wcSliderButton::CheckPosRange ( void )
{
	BOOL Change = FALSE;
	if ( m_Pos < m_Min )
	{
		 m_Pos = m_Min;
		 Change = TRUE;
	}

	if ( m_Pos > m_Max )
	{
		 m_Pos = m_Max;
		 Change = TRUE;
	}

	if ( Change )
		 SetPos (m_Pos);
}

int wcSliderButton::GetPosPerc ( void )
{
	int OffSet = 0;
	if ( m_Min < 0 )
		 OffSet = -m_Min;
	int nMin = m_Min + OffSet;
	int nMax = m_Max + OffSet;
	int Range = abs (nMax - nMin);

	return (m_Pos+OffSet) * 100 / Range;
}

void wcSliderButton::OnUpdate () 
{
	TCHAR buf[512];
	GetWindowText (buf, sizeof( buf ) / sizeof(TCHAR));

	int Value = atoi(H_ASCII_TEXT(buf));
	
	if ( Value >= m_Min &&  Value <= m_Max )
	{
		 m_Pos = Value;
		 CWnd *pParent = GetParent();
		 if ( pParent ) 
			  pParent->SendMessage(CSP_DELTAPOS, m_Pos, (WPARAM) GetDlgCtrlID());
	}
	else
		 OnBadInput();
}

void wcSliderButton::OnBadInput()
{
	MessageBeep((UINT)-1);
}

void wcSliderButton::OnChar ( UINT nChar, UINT nRepCnt, UINT nFlags ) 
{
	if ( nChar == ' ' ) 
		 return;
	int oldValue = GetPos();
	CEdit::OnChar (nChar, nRepCnt, nFlags);

	int val = IsValid();
	CString s;

	switch ( val )
	{
		case VALID:
			 s.Format (_T("%d"), GetPos());
			 break;
		case MINUS_PLUS: break;
		default:
			 SetPos (oldValue);
			 SetSel (0, -1);
			 MSG msg;
			 while (::PeekMessage(&msg, m_hWnd, WM_CHAR, WM_CHAR, PM_REMOVE));
			 break;
	}
}

int	wcSliderButton::IsValid ( void ) const
{
	CString str;
	GetWindowText(str);
	int res = VALID;
 
	if ( (str.GetLength() == 1) && ((str[0] == '+') || (str[0] == '-')) ) 
		 res = MINUS_PLUS;	

	return res;
}

/////////////////////////////////////////////////////////////////////////////
// DDV_FileEditCtrl & DDX_FileEditCtrl

void DDX_SliderButtonCtrl(CDataExchange *pDX, int nIDC, wcSliderButton &rCFEC, BOOL LeftBut)
{
	// Subclass the specified wcSliderButton class object to the edit control
	// with the ID nIDC. dwFlags is used to setup the control
	ASSERT (pDX->m_pDlgWnd->GetDlgItem(nIDC));
	if (rCFEC.m_hWnd == NULL)					// not yet subclassed
	{
		ASSERT (!pDX->m_bSaveAndValidate);
		// subclass the control to the edit control with the ID nIDC
		HWND hWnd = pDX->PrepareEditCtrl(nIDC);
		if (!rCFEC.SubclassWindow(hWnd))
		{										// failed to subclass the edit control
			ASSERT(FALSE);
			AfxThrowNotSupportedException();
		}
		// call wcSliderButton::SetFlags() to initialize the internal data structures
		rCFEC.SetLeftButton(LeftBut);
		// Force a call to wcSliderButton::OnNcCalcSize() to calculate button size
		rCFEC.SetWindowPos(NULL,0,0,0,0,SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
	}
}


#define POPUP_WID			124
#define POPUP_HGT			20
#define TRACK_LEN			100
#define POPUP_FRAMETHICK	2
#define TRI_WID				10
#define TRI_HGT				6
#define TRI_X				(10+POPUP_FRAMETHICK)
#define TRI_Y				8

/////////////////////////////////////////////////////////////////////////////
// wcSliderPopup
wcSliderPopup::wcSliderPopup()
{
    m_pParent	= NULL;
	m_Pos		= 0;
	m_OldPos	= 0;
	m_TriPos	= 0;
	m_Min		= 0;
	m_Max		= 100;
	m_Delta		= 1;
}

wcSliderPopup::wcSliderPopup ( CPoint p, int Pos, int nMin, int nMax, CWnd* pParentWnd )
{
    wcSliderPopup::Create (p, Pos, nMin, nMax, pParentWnd);
}

BOOL wcSliderPopup::Create ( CPoint p, int Pos, int nMin, int nMax, CWnd* pParentWnd )
{
    m_pParent  = pParentWnd;
	m_Min	   = nMin;
	m_Max	   = nMax;
	if ( Pos < m_Min )
		 Pos = m_Min;
	if ( Pos > m_Max )
		 Pos = m_Max;

    // Get the class name and create the window
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);
    if ( ! CWnd::CreateEx(0, szClassName, _T(""), WS_VISIBLE|WS_POPUP, 
                          p.x+(TRI_X/2)+POPUP_FRAMETHICK,
						  p.y, 
						  POPUP_WID, POPUP_HGT,
                          pParentWnd->GetSafeHwnd(), 0, NULL))
        return FALSE;

    // Capture all mouse events for the life of this window
    SetCapture ();
	SetFocus ();
	SetPos (Pos, FALSE);

    return TRUE;
}

BEGIN_MESSAGE_MAP(wcSliderPopup, CWnd)
    //{{AFX_MSG_MAP(wcSliderPopup)
	ON_WM_ERASEBKGND()
    ON_WM_NCDESTROY()
    ON_WM_LBUTTONUP()
    ON_WM_PAINT()
    ON_WM_MOUSEMOVE()
    ON_WM_KEYDOWN()
    ON_WM_QUERYNEWPALETTE()
    ON_WM_PALETTECHANGED()
	ON_WM_KILLFOCUS()
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// wcSliderPopup message handlers
BOOL wcSliderPopup::OnEraseBkgnd ( CDC* pDC ) 
{
	return TRUE;//CWnd::OnEraseBkgnd(pDC);
}

/* Auto Delete
   */
void wcSliderPopup::OnNcDestroy() 
{
    CWnd::OnNcDestroy();
    delete this;
}

void wcSliderPopup::DrawTriAt ( int Pos, BOOL Clear, BOOL DrawTrack )
{
	CRect Win;
	CClientDC dc (this);
	GetClientRect (&Win);

	CDC dcMem;
	CBitmap Layer;
	dcMem.CreateCompatibleDC (&dc);
	Layer.CreateCompatibleBitmap (&dc, Win.Width(), Win.Height());
	CBitmap* pOldBitmap = dcMem.SelectObject(&Layer);

	// Paint the background
	CBrush Bg (GetSysColor(COLOR_BTNFACE));
	CRect Rect (CPoint(0,0), CSize(Win.Width(), Win.Height()));
	dcMem.FillRect (&Rect, &Bg);

	// Create the pen
	CPen black (PS_SOLID, 1, RGB (0,0,0));
	CPen dgrey (PS_SOLID, 1, RGB (102, 102, 102));
	CPen*old = dcMem.SelectObject (&black);

	// Draw the thumb
	dcMem.MoveTo	   (TRI_X,		   TRI_Y-1);
	dcMem.LineTo	   (TRACK_LEN+TRI_X, TRI_Y-1);
	dcMem.SelectObject (&dgrey);
	dcMem.MoveTo	   (TRI_X, 6);
	dcMem.LineTo	   (TRI_X+TRACK_LEN, TRI_Y-2);
	
	int CenterBase = TRI_WID >> 1;
	int tx		   = TRI_X + Pos - CenterBase;
	int ty		   = TRI_Y;
	int ty2		   = TRI_Y + TRI_HGT;

	// Draw Shadow
	dcMem.SelectObject (&dgrey);
	dcMem.MoveTo	   (tx +1,				 ty2+1);
	dcMem.LineTo	   (tx +1 + TRI_WID,    ty2+1);
	dcMem.LineTo	   (tx +1 + CenterBase, ty+1);

	// Draw Tri
	dcMem.SelectObject (&black);
	dcMem.MoveTo	   (tx,			  ty2);
	dcMem.LineTo	   (tx + TRI_WID,    ty2);
	dcMem.LineTo	   (tx + CenterBase, ty);
	dcMem.LineTo	   (tx,			  ty2);

	// Draw the frame around the window
	dcMem.DrawEdge (Win, EDGE_RAISED, BF_RECT);	

	// Draw to Client Area
	dc.BitBlt (Win.left, Win.top, Win.Width(), Win.Height(),&dcMem, 0, 0, SRCCOPY);
		
	dcMem.SelectObject (old);
	dcMem.SelectObject (pOldBitmap);
	dcMem.DeleteDC ();
	Layer.DeleteObject();
}

void wcSliderPopup::OnPaint () 
{
    CPaintDC dc (this);

	DrawTriAt (m_TriPos, FALSE, TRUE);

	CRect Win;
	GetClientRect (&Win);
    dc.DrawEdge   (Win, EDGE_RAISED, BF_RECT);
	SetCapture    ();
}

void wcSliderPopup::OnMouseMove ( UINT nFlags, CPoint point ) 
{
    CWnd::OnMouseMove (nFlags, point);

//	if ( nFlags & MK_LBUTTON )
	{
		 CRect Win;
		 GetClientRect (&Win);

		 int tPos = point.x - TRI_WID - POPUP_FRAMETHICK;
		 if ( tPos < 0		   ) tPos = 0;
		 if ( tPos > TRACK_LEN ) tPos = TRACK_LEN;
		 m_TriPos = tPos;
		 m_Pos = TriToPos();

		 PositionChange ();
		 SetCapture ();
	}
}

void wcSliderPopup::OnLButtonUp ( UINT nFlags, CPoint point )
{    
    CWnd::OnLButtonUp(nFlags, point);

    DWORD pos = GetMessagePos();
    point = CPoint (LOWORD(pos), HIWORD(pos));

	CRect Win;
	GetClientRect (&Win);
	ClientToScreen (&Win);

	EndSliderPopup (CSP_CLOSEUP);
}

void wcSliderPopup::EndSliderPopup ( int nMessage )
{
    ReleaseCapture ();
	m_pParent->SendMessage (nMessage, (WPARAM)m_Pos, 0);
    DestroyWindow ();
}

void wcSliderPopup::OnKillFocus ( CWnd* pNewWnd )
{
	CWnd::OnKillFocus (pNewWnd);
    ReleaseCapture ();
}

 
void wcSliderPopup::OnActivateApp(BOOL bActive, DWORD hTask) 
{
 
#if (_MSC_VER == 1200)
	CWnd::OnActivateApp (bActive,  (HTASK)hTask);
#else
	CWnd::OnActivateApp (bActive,  hTask);
#endif

	if ( ! bActive )
		 EndSliderPopup (CSP_CLOSEUP);
}

void wcSliderPopup::PositionChange (void)
{
	DrawTriAt (m_TriPos, FALSE);

	// Sent message for update
	m_pParent->SendMessage (CSP_DELTAPOS, (WPARAM)m_Pos, 0);
}

// If an arrow key is pressed, then move the selection
void wcSliderPopup::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_RIGHT || nChar == VK_UP )
	{
		 if ( m_Pos < m_Max ) 
		 {
			  m_Pos += m_Delta;
			  if ( m_Pos > m_Max )
				   m_Pos = m_Max;
		 }
		 PositionChange ();
	}
	else if ( nChar == VK_LEFT || nChar == VK_DOWN )
	{
		 if ( m_Pos > m_Min ) 
		 {
			  m_Pos -= m_Delta;
			  if ( m_Pos < m_Min )
				   m_Pos = m_Min;
		 }
		 PositionChange ();
	}
    if ( nChar == VK_ESCAPE ) 
    {
         EndSliderPopup(CSP_CLOSEUP);
         return;
    }
    if ( nChar == VK_RETURN || nChar == VK_SPACE )
    {
         EndSliderPopup (CSP_CLOSEUP);
         return;
    }
    CWnd::OnKeyDown (nChar, nRepCnt, nFlags);
}

void wcSliderPopup::SetPos ( int Pos, BOOL bInvalidate/*=TRUE*/)
{
	if ( Pos >= m_Min && Pos <= m_Max )
	{
		 m_Pos = Pos;
		 m_TriPos = GetTriPos (Pos);

		 if ( bInvalidate )
			  PositionChange ();
	}
}

int wcSliderPopup::GetTriPos ( int Pos )
{
	int OffSet = 0;
	if ( m_Min < 0 )
		 OffSet = -m_Min;
	int nMin = m_Min + OffSet;
	int nMax = m_Max + OffSet;
	int Range = abs (nMax - nMin);
	Pos += OffSet;

	return (Pos * TRACK_LEN / Range);
}

int wcSliderPopup::TriToPos ( void )
{
	int OffSet = 0;
	if ( m_Min < 0 )
		 OffSet = -m_Min;
	int nMin = m_Min + OffSet;
	int nMax = m_Max + OffSet;
	int Range = abs (nMax - nMin);

	return (int)((double)m_TriPos * (double)Range / (double)TRACK_LEN +(double)m_Min);
}