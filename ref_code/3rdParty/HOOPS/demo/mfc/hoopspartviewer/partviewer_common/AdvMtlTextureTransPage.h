#pragma once

#include "resource.h"
class CAdvancedMaterialDlg;

// CAdvMtlTextureTransPage : Property page dialog

class CAdvMtlTextureTransPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CAdvMtlTextureTransPage)

// Constructors
public:
	CAdvMtlTextureTransPage();
	virtual ~CAdvMtlTextureTransPage();
	
	CSliderCtrl        mSldTexScale;
    CEdit              mEdtTexScale;
    CButton            mBtnActiveTextureParams;
    float                     mTextureScale;


	CAdvancedMaterialDlg * mpDialog;
	void SetDialog( CAdvancedMaterialDlg * );
	CAdvancedMaterialDlg * GetDialog();


    afx_msg void OnEnChangeHamEdtTextScale();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    
    CBrush m_brush; 

    HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


// Dialog Data
	enum { IDD = IDD_ADVMTL_TEXTURES2 };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};
