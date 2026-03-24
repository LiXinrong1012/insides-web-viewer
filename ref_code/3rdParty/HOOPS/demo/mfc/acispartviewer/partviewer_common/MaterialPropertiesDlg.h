#if !defined(AFX_MATERIALPROPERTIESDLG_H__7EA88BBD_7F2D_41BD_AF4C_7F592AFF54E7__INCLUDED_)
#define AFX_MATERIALPROPERTIESDLG_H__7EA88BBD_7F2D_41BD_AF4C_7F592AFF54E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MaterialPropertiesDlg.h : header file
//
#include "HUIUtilityMFC.h"
#include "CAppSettings.h"

class HBaseView;

enum ColorMode
{
	eColor,
	eTexture
};

/////////////////////////////////////////////////////////////////////////////
// MaterialPropertiesDlg dialog

class MaterialPropertiesDlg : public CDialog
{
// Construction
public:
	MaterialPropertiesDlg(HBaseView * pHView, CWnd* pParent = NULL);   // standard constructor
	~MaterialPropertiesDlg();

	bool ValidateSelection();

// Dialog Data
	//{{AFX_DATA(MaterialPropertiesDlg)
	enum { IDD = IDD_EDIT_MATERIAL_PROPERTIES };
	CColorBtn	m_FaceColorButton;
	int			m_FaceColorMode;
	int			m_nFaceTransparency;
	CString		m_csTextureSourceFile;
	CString		m_csTextureType;
	CString		m_csTextureParamSource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MaterialPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HBaseView * m_pHView;

	bool set_face_color_mode(ColorMode new_fc_mode);
	void update_face_color_controls();
	void update_texture_controls();
	void switch_face_color_controls( bool on_off );
	void switch_face_texture_controls( bool on_off );
	bool get_face_color_specs(CString& ret_specs);
	bool get_texture(CString& retTextureName);
	bool generate_unique_name(CString& retNewName);

	HC_KEY *m_pSelectionList;
	int m_SelNum;
	bool m_bFirst;
	// Generated message map functions
	//{{AFX_MSG(MaterialPropertiesDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonBrowseTextures();
	afx_msg void OnRadioFaceColor();
	afx_msg void OnRadioFaceTexture();
	afx_msg void OnMaterialapply();
	afx_msg void OnSelchangeComboTextureType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

// CameraNearLimitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CameraNearLimitDlg dialog

class CameraNearLimitDlg : public CDialog
{
// Construction
public:
	CameraNearLimitDlg(HBaseView * pHView, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CameraNearLimitDlg)
	enum { IDD = IDD_CAMERA_NEAR_LIMIT_DLG };
	float	m_fCameraNearLimit;
	float	m_fLightScaleFactor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CameraNearLimitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HBaseView * m_pHView;

	// Generated message map functions
	//{{AFX_MSG(CameraNearLimitDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALPROPERTIESDLG_H__7EA88BBD_7F2D_41BD_AF4C_7F592AFF54E7__INCLUDED_)

