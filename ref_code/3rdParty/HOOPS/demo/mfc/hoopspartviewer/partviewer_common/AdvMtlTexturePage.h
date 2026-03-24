#pragma once

#include "resource.h"
class CAdvancedMaterialDlg;

// CAdvMtlTexturePage dialog

class CAdvMtlTexturePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAdvMtlTexturePage)

public:

    CBrush m_brush; 

	CAdvMtlTexturePage();
	virtual ~CAdvMtlTexturePage();
	
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	

// Dialog Data
	enum { IDD = IDD_ADVMTL_TEXTURES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedGenTex();
    
    CButton mRB_PLANE_X_Y;   
    CButton mRB_PLANE_Y_Z;   
    CButton mRB_PLANE_Z_X;   
    CButton mRB_SPHERE;   
    CButton mRB_SPHERE_Y_Z;   
    CButton mRB_SPHERE_Z_X;  
    
    CAdvancedMaterialDlg * mpDialog;
    
	void SetDialog( CAdvancedMaterialDlg * );
	CAdvancedMaterialDlg * GetDialog();
 


};
