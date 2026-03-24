#pragma once



// CAdvMaterialSheet

class CAdvMaterialSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAdvMaterialSheet)

public:
	CAdvMaterialSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAdvMaterialSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CAdvMaterialSheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


