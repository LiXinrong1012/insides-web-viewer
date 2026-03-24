#pragma once
#include "resource.h"

class CAdvancedMaterialDlg;

// CAdvMtlMiscPage dialog

class CAdvMtlMiscPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAdvMtlMiscPage)

public:
	CAdvMtlMiscPage();
	virtual ~CAdvMtlMiscPage();
	
	void SetDialog( CAdvancedMaterialDlg * );
	CAdvancedMaterialDlg * GetDialog();
	
	CBrush m_brush; 

    HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


// Dialog Data
	enum { IDD = IDD_ADVMTL_MISC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	    
    CAdvancedMaterialDlg * mpDialog;
    CEdit   mEdtGroupName;



	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCreateGroup();
    afx_msg void OnBnClickedCreateSphere();
};
