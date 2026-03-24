#if !defined(AFX_PARTVIEWEROPTIONS_H__E645D134_0149_4302_93B0_4F427B8E1CDD__INCLUDED_)
#define AFX_PARTVIEWEROPTIONS_H__E645D134_0149_4302_93B0_4F427B8E1CDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PartViewerOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TessellationOptionsPage dialog
#include "HSolidView.h"
class CSolidHoopsView;


class SelectionOptionsPage : public HOptionsPage
{
// Construction
public:
	SelectionOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectionOptionsPage)
	enum { IDD = IDD_OPTIONS_SELECTION_PAGE };
 	CColorBtn	m_clrbtnSelPolygons;
	CColorBtn	m_clrbtnSelMarkers;
	CColorBtn	m_clrbtnSelLines;
 	BOOL	m_bGrayScaleSelection;
 	BOOL	m_bDisplaceSelection;
 	int		m_nSelTransparency;
	BOOL	m_bVisibilitySelection;
  	BOOL	m_bDynamicHighlighting;
	BOOL	m_bDetailSelection;
	BOOL	m_bUseSelectBox;
	HSelectionHighlightMode	m_HighlightMode;
	BOOL	m_bRelatedSelectionLimit;
	int		m_nRelatedSelectionLimit;
	float	m_fTransparencyLevel;
	CString	m_csRefSelType;
	CString	m_csQuickMovesType;
 	//}}AFX_DATA

	BOOL	m_found_specific_fonts;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectionOptionsPage)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectionOptionsPage)
 	afx_msg void OnCheckGrayScaleSelection();
 	afx_msg void OnCheckDisplaceSelection();
 	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
 	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

 	void UpdateSelectionChecks();
	void OnRelatedSelection();
	void UpdateRelatedSelection();
	void OnNoQuickmovesHighlighting();
	void OnReferenceHighlighting();
	void OnInverseTransparency();
	void OnColoredInverseTransparency();
};


class OutputOptionsPage : public HOptionsPage
{
	// Construction
public:
	OutputOptionsPage(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(OutputOptionsPage)
	enum { IDD = IDD_OPTIONS_OUTPUT_PAGE };
	int			m_nDPI;
	/* Window size measured in pixels. */
	float		m_iWindowWidth;
	float		m_iWindowHeight;
	/* Paper size measured in inches. */
	float		m_fPaperWidth;
	float		m_fPaperHeight;
	BOOL		m_bForceGrayscale;
	BOOL		m_bMemoryOverSpeed;	
	BOOL		m_bUseWindowColor;
	int			m_DocOpt;
	int			m_ImageOpt;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OutputOptionsPage)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

	// Implementation
protected:

	void EnableSetPageSize(bool);
	void EnableSetWindowSize(bool);

	// Generated message map functions
	//{{AFX_MSG(OutputOptionsPage)
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	afx_msg void SetOutputRadio();
	afx_msg void OnBnClickedRadioHoopsWYSIWYG();
	afx_msg void OnBnClickedRadioHoopsWindowToPage();
	afx_msg void OnBnClickedRadioUseWindowSize();
	afx_msg void OnBnClickedRadioCustomImageSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


 
class GeometryOptionsPage : public HOptionsPage
{
	// Construction
public:
	GeometryOptionsPage(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(GeometryOptionsPage)
	enum { IDD = IDD_OPTIONS_GEOMETRY_PAGE };
	int			m_nBudget;
	int			m_nContBudget;
	float		m_fMaxDeviation;
	float		m_fMaxAngle;
	float		m_fMaxLength;
	BOOL		m_bViewIndependent;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GeometryOptionsPage)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();
	

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GeometryOptionsPage)
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class EffectsOptionsPage : public HOptionsPage
{
	// Construction
public:
	EffectsOptionsPage(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(EffectsOptionsPage)
	enum { IDD = IDD_OPTIONS_EFFECTS_PAGE };
	BOOL	m_bSimpleShadows;
	BOOL	m_bShadowMaps;
	BOOL	m_bReflection;
	CString	m_csSamples;
	CString	m_csResolution;
	CColorBtn	m_clrbtnShadow;
	int		m_nShadowRes;
	int		m_nShadowBlur;
	CString	m_csShadowRenderingMode;
	float	m_fShadowOpacity;
	float	m_fReflectionOpacity;
	BOOL	m_bReflectionFading;
	BOOL	m_bJitter;
	BOOL	m_bUseBlur;
	int		m_nBlur;
	BOOL	m_bUseAttenuation;
	float	m_fHither;
	float	m_fYon;
	BOOL	m_ViewDependentSMap;
	BOOL	m_bFastAmbient;
	float	m_FastAmbientStrength;
	BOOL	m_bFastSilhouette;
	float	m_FastSilhouetteTolerance;
	BOOL	m_bHQAmbientOcclusion;
	BOOL	m_bHeavyExteriorSilhouette;
	BOOL	m_bUseLightVector;
	HPoint	m_LightVector;
	BOOL	m_bIgnoreTransparency;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EffectsOptionsPage)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EffectsOptionsPage)
	afx_msg void OnCheckFastAmbient();
	afx_msg void OnCheckReflectionPlane();
	afx_msg void OnCheckAttenuation();
	afx_msg void OnCheckUseBlur();
	afx_msg void OnChangeHitherYon();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	afx_msg void OnCheckFastSilhouette();
	afx_msg void OnCheckLightVector();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	void UpdateAmbientStrength();
	void UpdateReflectionPlaneData();
	void UpdateAttenuation();
	void UpdateSilhouetteTolerance();
	void UpdateUseBlur();
	void UpdateLightVector();
};


class LightingOptionsPage : public HOptionsPage
{
	// Construction
public:
	LightingOptionsPage(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(LightingOptionsPage)
	enum { IDD = IDD_OPTIONS_LIGHTING_PAGE };
	BOOL		m_bLightFollowsCamera;
	BOOL		m_bHemisphericAmbient;
	CColorBtn	m_clrbtnAmbientTop;
	CColorBtn	m_clrbtnAmbientBottom;
	BOOL		m_bLightScaling;	
	float		m_fLightScaleFactor;
	CString		m_GoochColorMap;
	BOOL		m_UseAmbientUpVector;
	HPoint		m_AmbientUpVector;
	CColorBtn	m_clrbtnGooch1;
	CColorBtn	m_clrbtnGooch2;
	CColorBtn	m_clrbtnGooch3;
	CColorBtn	m_clrbtnGooch4;
	CColorBtn	m_clrbtnGooch5;
	CColorBtn	m_clrbtnGooch6;
	float		m_GoochWeight;
	float		m_GoochColorHigh;
	BOOL		m_bUseBloom;
	float		m_fBloomStrength;
	UINT		m_BloomBlur;
	CString		m_csBloomShape;
	CString		m_csLightCount;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LightingOptionsPage)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();
	void UpdateLightScaleFactor();
	void UpdateAmbientColors();
	void UpdateBloom();

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LightingOptionsPage)
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	afx_msg void OnCheckLightScaleFactor();
	afx_msg void OnCheckHemisphericAmbient();	
	afx_msg void OnCheckBloom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class AppearanceOptionsPage : public HOptionsPage
{
// Construction
public:
	AppearanceOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AppearanceOptionsPage)
	enum { IDD = IDD_OPTIONS_APPEARANCE_PAGE };
	CString		m_csGreekingModeCombo;
	CString		m_csGreekingUnitsCombo;
	CString		m_csFontUnitsCombo;
	CString		m_csLineWeight;
	CComboBox	m_FontNameCombo;
	CColorBtn	m_clrbtnBackgroundTop;
	CColorBtn	m_clrbtnBackgroundBottom;
	CColorBtn	m_clrbtnMarkup;
	BOOL	m_bSplatRendering;
	BOOL	m_bHideOverlappedText;
	BOOL	m_bUseGreeking;
	BOOL	m_bCiByColopmap;
	BOOL	m_bCiIsolines;
	BOOL	m_bCiByValue;
	BOOL	m_bColorInterpolation;
	float	m_fMarkupWeight;
	float	m_fGreekingLimit;
 	float	m_FontSize;
	BOOL	m_bLineAntialiasing;
 	BOOL	m_bTextAntialiasing;
	BOOL	m_bAntialiasing;
	BOOL	m_bFastMarkers;
	CString	m_csAntialiasingLevel;
	//}}AFX_DATA

	BOOL	m_found_specific_fonts;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AppearanceOptionsPage)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AppearanceOptionsPage)
	afx_msg void OnCheckGreekingLimit();
	afx_msg void OnCheckColorInterpolation();
 	afx_msg void OnCheckCiIsolines();
	afx_msg void OnCheckCiByValue();
	afx_msg void OnCheckCiByColormapIndex();
	afx_msg void OnCheckAntialias();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	afx_msg void OnSetfocusComboFontName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void UpdateDriverDependentControls();
	void UpdateGreekingLimitData();
	void UpdateColorInterpolationChecks();
 	void PopulateFontNameCombo(bool specific_fonts = false);

public:
};


//---------------------------------------------------------------------
class CameraOptionsPage : public HOptionsPage
{
	// Construction
public:
	CameraOptionsPage(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CameraOptionsPage)
	enum { IDD = IDD_OPTIONS_CAMERA_PAGE };
	BOOL	m_bSmoothTransition;	
	CString m_csProjectionMode;
	float	m_fNearLimit;
	CString	m_csFrontViewAxis;
	CString	m_csTopViewAxis;
	BOOL	m_bHandedness;
	BOOL	m_bNavPanel;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CameraOptionsPage)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

protected:
	// Generated message map functions
	//{{AFX_MSG(CameraOptionsPage)
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	afx_msg void SetHandednessRadio();
	afx_msg void OnClickedRadioRightHanded();
	afx_msg void OnClickedRadioLeftHanded();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
};

//-----------------------------------------------------------------------




/////////////////////////////////////////////////////////////////////////////
// InteractionOptionsPage dialog

class InteractionOptionsPage : public HOptionsPage
{
 
// Construction
public:
	InteractionOptionsPage(CWnd* pParent = NULL);   // standard constructor
	~InteractionOptionsPage();

// Dialog Data
	//{{AFX_DATA(InteractionOptionsPage)
	enum { IDD = IDD_OPTIONS_INTERACTION_PAGE };
	BOOL	m_bWalkUseKeyboard;
	BOOL	m_bWalkCollision;
	BOOL	m_bWalkSnapToFloor;
	float	m_WalkAvatarHeight;
	BOOL	m_bWalkAutomaticHeight;
	UINT	m_WalkStepHeightUp;
	UINT	m_WalkStepHeightDown;
	BOOL	m_bShowEveryTick;
	BOOL	m_bShowCollisions;
	BOOL	m_bUpdateCamera;
	BOOL	m_bJumpToKeyframe;
	BOOL	m_bDisableCFR;
	BOOL	m_bAntialiasing;
	BOOL	m_bTimerBasedUpdate;
 	BOOL	m_bUpdateCutGeometry;
	BOOL	m_bSpriting;
	BOOL	m_bUpdateShadows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(InteractionOptionsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	virtual void OnOK();
	void ApplySettings();
	void UpdateAutomaticHeight();
	void UpdateAvatarHeight();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(InteractionOptionsPage)
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnWalkAutomaticHeight();
	afx_msg void OnButtonReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

class PerformanceOptionsPage : public HOptionsPage
{
// Construction
public:
	PerformanceOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PerformanceOptionsPage)
	enum { IDD = IDD_OPTIONS_PERFORMANCE_PAGE };
	PerformanceSettings m_Settings;
	
// 	BOOL	m_bUseOctree; 	
	//}}AFX_DATA

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PerformanceOptionsPage)
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReset();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnCheckFramerateMode();
	afx_msg void OnCheckNone();
	void UpdateTargetFramerate();
	afx_msg void OnCheckOcclusionCulling();
	afx_msg void OnCheckCullingThreshold();
 	afx_msg void OnCheckStaticModel();
	afx_msg void OnCheckDynamicAdjustment();
	afx_msg void OnClickFramerateModeMenu();
	//}}AFX_VIRTUAL

	void UpdateStaticModel(bool force_check);
	void UpdateOcclusionCulling();
	virtual void OnOK();
	void ApplySettings();

	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// HSFOptionsPage dialog

class HSFOptionsPage : public HOptionsPage
{
 
// Construction
public:
	HSFOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(HSFOptionsPage)
	enum { IDD = IDD_OPTIONS_HSF_PAGE };
	CString		m_csHsfVersion;
	int			m_ModelerVersionNo;
	CComboBox	m_ModelerVersionCombo;
	BOOL		m_bStoreCompressedNormals;
	UINT		m_NumNormalBits;
	BOOL		m_bStoreCompressedParameters;
	UINT		m_NumParameterBits;
	BOOL		m_bStoreCompressedVertices;
	UINT		m_NumVertexBits;
	BOOL		m_bEmbedThumbnail;
	BOOL		m_bStoreLines;
	BOOL		m_bStoreDictionary;
	BOOL		m_bEnableInstancing;
	BOOL		m_bSaveLogFile;
	BOOL		m_bCompressConnectivity;
	BOOL		m_bReadSimpleHsf;
	BOOL		m_bStoreTopolInfo;
	BOOL		m_bEnableTristrips;
	BOOL		m_bEmbedMaterials;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(HSFOptionsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	virtual void OnOK();
	void ApplySettings();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(HSFOptionsPage)
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReset();
	afx_msg void OnSelchangeComboModelerVersion();
	afx_msg void OnStoreCompressedNormals();
	afx_msg void OnStoreCompressedParameters();
	afx_msg void OnStoreCompressedVertices();
	afx_msg void OnStoretopolinfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



class GeneralOptionsPage : public HOptionsPage
{
// Construction
public:
	GeneralOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GeneralOptionsPage)
	enum { IDD = IDD_OPTIONS_GENERAL_PAGE };
	CString m_csHoopsDriver;
	BOOL	m_bForceSoftware;
	BOOL	m_bDisplayStats;
	BOOL	m_bDisplayAxisTriad;
	BOOL	m_bBackplaneCulling;
	CString	m_csCoordSysHandedness;
	CString	m_csRenderMode;
 	CString m_csPolygonHandedness;
 	CString	m_csTransparencyStyle;
	CString	m_csTransparencySorting;
	CString	m_csTransparencyDepthPeelingLayers;
	BOOL	m_bStereoMode;
	BOOL	m_bDoubleBuffer;
	float	m_fStereoSeparation;
	BOOL	m_bDepthWriting;
	//}}AFX_DATA
		
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GeneralOptionsPage)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GeneralOptionsPage)
	afx_msg void OnSelchangeComboDriver();
	afx_msg void OnSelchangeComboPolygonHandedness();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	afx_msg void OnCheckSpriting();
	afx_msg void OnSelchangeComboTransparencySorting();
	afx_msg void OnCheckStereoMode();
	afx_msg void OnButtonImportOptions();
	afx_msg void OnButtonExportOptions();
	afx_msg void OnButtonWriteToRegistry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void UpdateDriverDependentControls();
	void UpdateTransparencySorting();
	void UpdateBackplaneCullingCheck();
	
	
	void UpdateStereoMode();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


class FileOptionsPage : public HOptionsPage
{
// Construction
public:
	FileOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
#if defined(PARASOLID)
	enum { IDD = IDD_OPTIONS_FILE_PAGE_PARASOLID };
#elif defined(ACIS)
	enum { IDD = IDD_OPTIONS_FILE_PAGE_ACIS };
#elif defined(GRANITE)
	enum { IDD = IDD_OPTIONS_FILE_PAGE_GRANITE };
#else
	enum { IDD = IDD_OPTIONS_FILE_PAGE };
#endif
	//{{AFX_DATA(FileOptionsPage)
	CString	m_csPartsDir;
	CString m_csDWGTextureDir;
	CString m_csMaterialLibraryDir;

	BOOL	m_bFlushOnLoad;
	BOOL	m_bRestoreAnnotations;
	BOOL	m_bPrcFaceEdgeVertexSelectability;
	BOOL    m_bImportDWGviaBstream;
	BOOL    m_bImportDWGXData;
    double  m_DWGDeviation;
	BOOL	m_bHsfStreaming;
	BOOL    m_bImportAllLayouts;

	//For DGN
	BOOL    m_bIgnoreInvisibleLayer;
	BOOL    m_bIgnoreInvisibleEntities;
	double  m_DGNFactorForCone;
	double  m_DGNFactorForSmartSolids;
	BOOL	m_bLoadPVOFiles;


	//}}AFX_DATA
#ifdef PARASOLID
	CString	m_csSchemaPath;
	BOOL	m_bFlatten;
	BOOL	m_bUseBinaryFiles;
#endif // PARASOLID


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FileOptionsPage)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FileOptionsPage)
	afx_msg void OnButtonPartsDir();
	afx_msg void OnButtonDWGTextureDir();
	afx_msg void OnButtonMaterialLibraryDir();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
#ifdef PARASOLID
	afx_msg void OnButtonSchemaDir();
#endif // PARASOLID
	DECLARE_MESSAGE_MAP()
};


#ifdef PARASOLID

class TessellationOptionsPage : public HOptionsPage
{
// Construction
public:
	TessellationOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TessellationOptionsPage)
	enum { IDD = IDD_OPTIONS_FACE_TESSELLATION_PARASOLID };
	BOOL	m_bCurveChordAngTol;
	BOOL	m_bCurveChordTol;
	BOOL	m_bFacePlaneAngTol;
	BOOL	m_bFacetPlaneTol;
	BOOL	m_bSurfacePlaneAngTol;
	BOOL	m_bSurfacePlaneTol;
	BOOL	m_bLineCurveChordAngTol;
	BOOL	m_bLineCurveChordTol;
	double	m_CurveChordAngTol;
	double	m_CurveChordTol;
	double	m_FacetPlaneAngTol;
	double	m_FacetPlaneTol;
	double	m_SurfacePlaneAngTol;
	double	m_SurfacePlaneTol;
	double	m_LineCurveChordAngTol;
	double	m_LineCurveChordTol;
	CString	m_FacetMatch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TessellationOptionsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TessellationOptionsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckCurveChordAngTol();
	afx_msg void OnCheckCurveChordTol();
	afx_msg void OnCheckFacetPlaneAngTol();
	afx_msg void OnCheckFacetPlaneTol();
	afx_msg void OnCheckSurfacePlaneAngTol();
	afx_msg void OnCheckSurfacePlaneTol();
	afx_msg void OnCheckLineCurveChordAngTol();
	afx_msg void OnCheckLineCurveChordTol();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEditControls();

};

#endif // PARASOLID

#ifdef GRANITE

class TessellationOptionsPage : public HOptionsPage
{
// Construction
public:
	TessellationOptionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TessellationOptionsPage)
	enum { IDD = IDD_OPTIONS_TESSELLATION_GRANITE };
	double	m_angularTol;
	double	m_planarTol;
	double	m_tessellationTol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TessellationOptionsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnOK();
	void ApplySettings();

// Implementation

protected:

	// Generated message map functions
	//{{AFX_MSG(TessellationOptionsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};








//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // GRANITE

#endif // !defined(AFX_PARTVIEWEROPTIONS_H__E645D134_0149_4302_93B0_4F427B8E1CDD__INCLUDED_)

