// partviewer_common\AdvMtlMiscPage.cpp : implementation file
//

#include "stdafx.h"
#include "partviewer_common\AdvMtlMiscPage.h"

#include "HGlobals.h"
#include "vlist.h"
#include "vhash.h"
#include "HEventInfo.h"
#include "HBaseView.h"
#include "HModelInfo.h"
#include "HSelectionSet.h"
#
#include "AdvancedMaterialDlg.h"

// CAdvMtlMiscPage dialog

IMPLEMENT_DYNAMIC(CAdvMtlMiscPage, CPropertyPage)

CAdvMtlMiscPage::CAdvMtlMiscPage()
	: CPropertyPage(CAdvMtlMiscPage::IDD)
{
    mpDialog = 0;
}

CAdvMtlMiscPage::~CAdvMtlMiscPage()
{
}

void CAdvMtlMiscPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HAM_EDT_GROUP, mEdtGroupName);

}


BEGIN_MESSAGE_MAP(CAdvMtlMiscPage, CPropertyPage)
    ON_BN_CLICKED(IDC_CREATE_GROUP, &CAdvMtlMiscPage::OnBnClickedCreateGroup)
    ON_BN_CLICKED(IDC_CREATE_SPHERE, &CAdvMtlMiscPage::OnBnClickedCreateSphere)
    ON_WM_CTLCOLOR()
   
END_MESSAGE_MAP()


	    
    
void CAdvMtlMiscPage::SetDialog( CAdvancedMaterialDlg *  pDlg )
{
    mpDialog = pDlg;
} 
	
CAdvancedMaterialDlg * CAdvMtlMiscPage::GetDialog()
{
    return mpDialog;
}


void CAdvMtlMiscPage::OnBnClickedCreateGroup()
{
    HBaseView * pView = mpDialog->GetBaseView();

    HSelectionSet *selection = pView->GetSelection();

	if ( selection  )
	{
	    mpDialog->UpdateSelection( true );
    
        int nSelectionCount = mpDialog->GetSelectionCount();
    
        if ( nSelectionCount > 0 )
	    {
            CString strGroupName;
            mEdtGroupName.GetWindowText( strGroupName );

            HC_KEY modelKey = pView->GetModelKey();
            HC_KEY groupKey;
            
            HC_Open_Segment_By_Key( modelKey );
           
                HC_Open_Segment("Material_Groups");
                
                   groupKey = HC_KOpen_Segment( H_ASCII_TEXT (strGroupName.GetBuffer()) );
                   HC_Close_Segment();
                   
                HC_Close_Segment();
                
		    HC_Close_Segment();
	
	        for ( int i = 0; i != nSelectionCount; ++i )
	        {
	            HC_Move_By_Key_By_Key( mpDialog->GetSelectedKeys()[i] , groupKey );
		    }
		}
	}
	
    pView->SetCameraChanged();
	pView->Update();
}

void CAdvMtlMiscPage::OnBnClickedCreateSphere()
{
    char type[256];
    HC_KEY key, vkey, segkey;
    int lcount = 0;
    
    HBaseView * pView = mpDialog->GetBaseView();

    vkey = pView->GetViewKey();
    
    /* Begin a search under model and all its subsegment and include segments 
    for the segment with the names that have screw in them*/
    
    HC_Open_Segment_By_Key( vkey );
    
        HC_Begin_Contents_Search("....","lights");


        /* Recursively look through the search results */
        while(HC_Find_Contents(type,&key)) 
        {
            lcount++;
            segkey = HC_KShow_Owner_By_Key( key );
                
            HC_Open_Segment_By_Key(segkey);
                HC_Flush_Contents(".","lights" );
            HC_Close_Segment();
        }
        HC_End_Contents_Search();
    
    HC_Close_Segment();
    
    pView->SetCameraChanged();
	pView->Update();

        
  }

HBRUSH CAdvMtlMiscPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

  HBRUSH hbr;
   
    if( nCtlColor == CTLCOLOR_DLG )
    {
          if ( mpDialog->GetDialogBrush() > 0 )
              return mpDialog->GetDialogBrush();
    }
    
        
   hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);


  return hbr;
}