#if !defined(AFX_STYLEDIALOG_H__0C77B1CD_8612_43CE_B23C_5D0ADF211B39__INCLUDED_)
#define AFX_STYLEDIALOG_H__0C77B1CD_8612_43CE_B23C_5D0ADF211B39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StyleDialog.h : header file
//

#define FACES_COLOR 0
#define FRONT_COLOR 1
#define BACK_COLOR 2

/////////////////////////////////////////////////////////////////////////////
// CStyleDialog dialog
class HoopsStyle;
class HBaseView;
class MainStyleWindow;
class SelectStyleWindow;
class CImageViewer;
#include "HUIUtilityMFC.h"
#include "afxcmn.h"

class CStyleDialog : public CDialog
{
// Construction
public:
	CStyleDialog(HBaseView * view, CWnd* pParent = NULL);   // standard constructor
	CStyleDialog::~CStyleDialog();

 	void SetMainStyle(HoopsStyle *style);
	void ColorButtonClicked(int id, float x, float y ,float z, bool undefine = false);	
	void UpdateTexturePane();
	void UpdateTextureMatrixSliders();
	wcSliderButton	m_Face_Transmission_Edit;
	wcSliderButton	m_Face_Mirror_Edit;
	wcSliderButton	m_Face_Gloss_Edit;

// Dialog Data
	//{{AFX_DATA(CStyleDialog)
	enum { IDD = IDD_STYLEDIALOG };
	CComboBox	m_MarkerVisibilityC;
	CComboBox	m_LineVisibilityC;
	CComboBox	m_EdgeVisibilityC;
	CComboBox	m_FaceVisibilityC;
	CColorBtn	m_DiffuseFaceColor2;
	CEdit	m_ValueScaleMinEdit;
	CEdit	m_ValueScaleMaxEdit;
	CEdit	m_TextureScaleXEdit;
	CEdit	m_TextureScaleYEdit;
	CEdit	m_TextureScaleZEdit;

	CScrollBar	m_StyleScrollbar;
	CColorBtn	m_DiffuseLightColor;
	CColorBtn	m_SpecularLightColor;
	CColorBtn	m_TransmissionMarkerColor;
	CColorBtn	m_SpecularMarkerColor;
	CColorBtn	m_DiffuseMarkerColor;
	CColorBtn	m_TransmissionEdgeColor;
	CColorBtn	m_TransmissionLineColor;
	CColorBtn	m_SpecularLineColor;
	CColorBtn	m_DiffuseLineColor;
	CColorBtn	m_SpecularEdgeColor;
	CColorBtn	m_DiffuseEdgeColor;
	CColorBtn	m_TransmissionFaceColor;
  	CColorBtn	m_SpecularFaceColor;
  	CColorBtn	m_EmissionFaceColor;
	CStatic	m_ImageViewerWindow;
	CColorBtn	m_DiffuseFaceColor;
	CStatic	m_SelectStyleWindow;
	CStatic	m_MainStyleWindow;
	int		m_FaceVisibility;
	int		m_EdgeVisibility;
	int		m_LineVisibility;
	int		m_MarkerVisibility;
	CString	m_StyleName;
	CString	m_FaceGloss;
	CString	m_FaceTransmissionEditString;
	CString	m_FaceMirrorEditString;
	CString	m_ValueScaleMin;
	CString	m_ValueScaleMax;
	CString	m_TextureScaleX;
	CString	m_TextureScaleY;
	CString	m_TextureScaleZ;
	BOOL	m_bDownSampling;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStyleDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
        HBaseView *m_pHView;
	CString m_csTextureSourceFile;
	CString m_CurrentlySelectedTexture;
	bool generate_unique_name(CString& retNewName);
	void GatherColorData();
	void LoadImageFromDisk();
	void SetTextureMatrix(float scale, float rotation);


	void SelectTexture(CString texname);
	void UpdateParamSource(HoopsStyle *tex);
	void UpdateInterpolationFilter(HoopsStyle *tex);
	void UpdateDecimationFilter(HoopsStyle *tex);
	void UpdateLayout(HoopsStyle *tex);
	void UpdateTiling(HoopsStyle *tex);
	void UpdateBlendingMode(HoopsStyle *tex);
	void UpdateValueScale(HoopsStyle *tex);
	void UpdateDownsampling(HoopsStyle *style);

	void UpdateImageName(HoopsStyle *style);
	void UpdateStyleTextureCombos();
	void UpdateStyleTextureCombo(int id);
	void SelectStyleTexture(char *texname, int id);
	void UpdateVisibility();
	void ApplyVisibility(char *geom, char *onoff);
	void UpdateOneVisibility(char *geom, CComboBox &res);
	void UpdateWindows();
	void LoadStyleLibrary();
	void SaveStyleLibrary();
	int IsFrontCombo();
	bool CopyImages(HC_KEY image_key, CString name);
	bool MoveImages(HC_KEY image_key, CString name);
	void Color(HC_KEY key, char* seg_path, HC_KEY include_key, HC_KEY includer_key, 
				float r, float g, float b, bool recurse = false, bool emit_message = true);


	int m_bFrontBack;
	MainStyleWindow *m_SelectedStyleWindow;   
	SelectStyleWindow *m_SelectStylesWindow;   
	CImageViewer *m_ImageDisplayWindow;   

	// Generated message map functions
	//{{AFX_MSG(CStyleDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLoadImage();
	afx_msg void OnResetTextureMatrix();

	afx_msg void OnSelchangeTextureSelectorCombo();
	afx_msg void OnSelchangeParameterizationSource();
	afx_msg void OnSelchangeInterpolationFilter();
	afx_msg void OnSelchangeImageNameCombo();
	afx_msg void OnButtonDiffuseFaceColor();
	afx_msg void OnSelchangeTselectorDiffuseFaceCombo();
	afx_msg void OnSelchangeTselectorDiffuseFaceCombo2();
	afx_msg void OnSelchangeTselectorSpecularFaceCombo();
	afx_msg void OnSelchangeTselectorEnvironmentFaceCombo();
	afx_msg void OnSelchangeTselectorBumpFaceCombo();
	afx_msg void OnFaceVisibilityOn();
	afx_msg void OnFaceVisibilityOff();
	afx_msg void OnFaceVisibilityUndefined();
	afx_msg void OnEdgeVisibilityOn();
	afx_msg void OnEdgeVisibilityUndefined();
	afx_msg void OnEdgeVisibilityOff();
	afx_msg void OnLineVisibilityOff();
	afx_msg void OnLineVisibilityOn();
	afx_msg void OnLineVisibilityUndefined();
	afx_msg void OnMarkerVisibilityOff();
	afx_msg void OnMarkerVisibilityOn();
	afx_msg void OnMarkerVisibilityUndefined();
	afx_msg void OnButtonStyleSelection();
	afx_msg void OnSelchangeGeomTypeSelector();
	afx_msg void OnLoadStyles();
	afx_msg void OnSaveStyles();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNewStyle();
	afx_msg void OnCloneStyle();
	afx_msg void OnSelchangeSelectorFrontback();
	afx_msg void OnUpdateFaceGloss();
	afx_msg void OnKillfocusFaceGloss();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDeleteStyle();
	afx_msg void OnSelchangeTexLayout();
	afx_msg void OnSelchangeTexBlendingMode();
	afx_msg void OnSelchangeTexTiling();
	afx_msg void OnCloneTexture();
	afx_msg void OnChangeFaceTransmissonEdit();
	afx_msg void OnChangeFaceGloss();
	afx_msg void OnChangeFaceMirrorEdit();
	afx_msg void OnChangeValueScaleMinEdit();
	afx_msg void OnChangeValueScaleMaxEdit();
	afx_msg void OnSelchangeDecimationFilter();
	afx_msg void OnDownsamplingCheckbox();
	afx_msg void OnGetStyle();
	afx_msg void OnRenameStyle();
	afx_msg void OnDeleteImage();
	afx_msg void OnDeleteTexture();
	afx_msg void OnCloseupFaceVisibilityCombo();
	afx_msg void OnCloseupEdgeVisibilityCombo();
	afx_msg void OnCloseupLineVisibilityCombo();
	afx_msg void OnCloseupMarkerVisibilityCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeValueScaleMinEdit2();
	afx_msg void OnEnChangeValueScaleMinEdit3();
	afx_msg void OnEnChangeValueScaleMinEdit4();
	CSliderCtrl m_ScaleSlider;
	CSliderCtrl m_RotateSlider;
};




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STYLEDIALOG_H__0C77B1CD_8612_43CE_B23C_5D0ADF211B39__INCLUDED_)
