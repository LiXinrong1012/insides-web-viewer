// partviewer_common\AdvMaterialSheet.cpp : implementation file
//

#include "stdafx.h"
#include "partviewer_common\AdvMaterialSheet.h"
#include "partviewer_common\AdvancedMaterialDlg.h"


// CAdvMaterialSheet

IMPLEMENT_DYNAMIC(CAdvMaterialSheet, CPropertySheet)

CAdvMaterialSheet::CAdvMaterialSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CAdvMaterialSheet::CAdvMaterialSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CAdvMaterialSheet::~CAdvMaterialSheet()
{
}


BEGIN_MESSAGE_MAP(CAdvMaterialSheet, CPropertySheet)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAdvMaterialSheet message handlers

BOOL CAdvMaterialSheet::OnInitDialog()
{

   ModifyStyleEx (0, WS_EX_CONTROLPARENT);
    return CPropertySheet::OnInitDialog();
  
}

HBRUSH CAdvMaterialSheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

   CWnd * pOwner = GetSafeOwner();
   CAdvancedMaterialDlg * pAMS = ( CAdvancedMaterialDlg * ) pOwner;
      
    HBRUSH hbr;
   
    if( nCtlColor == CTLCOLOR_DLG )
    {
          if ( pAMS->GetDialogBrush() > 0 )
              return pAMS->GetDialogBrush();
    }
    
   hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor );
  
    return hbr;
}