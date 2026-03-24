// AdvMtlTextureTransPage.cpp : implementation file
//

#include "stdafx.h"
#include "HGlobals.h"
#include "vlist.h"
#include "vhash.h"
#include "HEventInfo.h"
#include "HBaseView.h"
#include "HModelInfo.h"
#include "HSelectionSet.h"
#include "AdvancedMaterialDlg.h"
#include "partviewer_common\AdvMtlTextureTransPage.h"

inline int doubleToLogSlider( double dvar )
{
   
    double lVal = log10( dvar ); 
    
    double e = ( lVal + 1 ) * 25;
    
    int sliderVal = (int) e;
    
    return sliderVal;
    
}

// CAdvMtlTextureTransPage dialog

IMPLEMENT_DYNAMIC(CAdvMtlTextureTransPage, CPropertyPage)

CAdvMtlTextureTransPage::CAdvMtlTextureTransPage()
	: CPropertyPage(CAdvMtlTextureTransPage::IDD)
{
    mpDialog = 0;
    mTextureScale = 1.0;

}

CAdvMtlTextureTransPage::~CAdvMtlTextureTransPage()
{
}

void CAdvMtlTextureTransPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HAM_TEX_SCALE_SLD, mSldTexScale);
    DDX_Control(pDX, IDC_HAM_EDT_TEXT_SCALE, mEdtTexScale);
    DDX_Control(pDX, IDC_CHECK_ACTIVE_TEX, mBtnActiveTextureParams);


}


BEGIN_MESSAGE_MAP(CAdvMtlTextureTransPage, CPropertyPage )
	ON_EN_CHANGE( IDC_HAM_EDT_TEXT_SCALE, &CAdvMtlTextureTransPage::OnEnChangeHamEdtTextScale )
    ON_WM_HSCROLL()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAdvMtlTextureTransPage message handlers

void CAdvMtlTextureTransPage::SetDialog( CAdvancedMaterialDlg *  pDlg )
{
    mpDialog = pDlg;
} 
	
CAdvancedMaterialDlg * CAdvMtlTextureTransPage::GetDialog()
{
    return mpDialog;
}

void CAdvMtlTextureTransPage::OnEnChangeHamEdtTextScale()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    CString strVal;
    mEdtTexScale.GetWindowText( strVal );
    double dvar;
    _stscanf(strVal, _T("%lf"), &dvar);

    mTextureScale = dvar;
    
    // map value into scroll range
    
    int sliderVal =  doubleToLogSlider( dvar ); 
    mSldTexScale.SetPos( sliderVal );
    
}

void CAdvMtlTextureTransPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    int nSliderPos;
    CString sText;

    nSliderPos = mSldTexScale.GetPos();
    
    float logVal =  powf(10.0,  ( nSliderPos  / 25.0 - 1 ) );
    
    
    sText.Format( _T("%g"), logVal );

    mEdtTexScale.SetWindowText(sText);
    
    mTextureScale = logVal;
    
    if ( mBtnActiveTextureParams.GetCheck() == BST_CHECKED )
        mpDialog->ApplyTextureParameters( mTextureScale, mTextureScale );

    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CAdvMtlTextureTransPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

	mTextureScale = 1;
	mSldTexScale.SetBuddy( &mEdtTexScale, FALSE );
	mSldTexScale.SetRange( 0,100, FALSE );
	
	mSldTexScale.SetTic( 0 );
	mSldTexScale.SetTic( doubleToLogSlider( 1.0 ) );
	mSldTexScale.SetTic( doubleToLogSlider( 10.0 ) );
	mSldTexScale.SetTic( doubleToLogSlider( 100.0 ) );
	mSldTexScale.SetTic( 100 );

	mEdtTexScale.SetWindowText( _T("1") );

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAdvMtlTextureTransPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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