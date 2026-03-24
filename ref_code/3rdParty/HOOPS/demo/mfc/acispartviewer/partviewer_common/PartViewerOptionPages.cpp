//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/PartViewerOptionPages.cpp,v 1.264 2011-01-26 00:26:32 nathan Exp $
//


// PartViewerOptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PartViewerOptionPages.h"
#include "CAppSettings.h"

// standard include
#include <assert.h>

// HOOPS/MVO includes
#include "HBaseView.h"
#include "HBaseModel.h"
#include "HSelectionSet.h"
#include "HMarkupManager.h"
#include "HBhvBehaviorManager.h"
#include "HUtilityLocaleString.h"
#include "HOpCameraWalk.h"
#include "HIOManager.h"
#include "HUtilityGeomHandle.h"
#include "HMaterialLibrary.h"

// HOOPS/MFC includes
#include "CSolidHoopsView.h"
#include "CSolidHoopsDoc.h"
#include "HSolidView.h"

#ifdef ACIS
#include "HSInclude.h"
#endif // ACIS



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_FONT_SIZE	0
#define MAX_FONT_SIZE	300



/////////////////////////////////////////////////////////////////////////////
//  PerformanceOptionsPage
PerformanceOptionsPage::PerformanceOptionsPage(CWnd* pParent /*=NULL*/)
	: HOptionsPage(PerformanceOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(PerformanceOptionsPage)	
	//}}AFX_DATA_INIT
}

static CString FramerateModeToCString(FramerateMode mode)
{
	if(mode==FramerateFixed)
		return "Fixed Framerate";
	else
		return "Target Framerate";
}

static FramerateMode FramerateCStringToMode(CString mode)
{
	if(mode=="Fixed Framerate")
		return FramerateFixed;
	else
		return FramerateTarget;
}

void PerformanceOptionsPage::UpdateTargetFramerate() 
{
	FramerateMode mode = FramerateCStringToMode(m_Settings.m_csFramerateMode);

	if(m_Settings.m_bCullingThreshold && m_Settings.m_bUseFramerate)
		m_Settings.m_bCullingThreshold=FALSE;

	if(!m_Settings.m_bCullingThreshold && !m_Settings.m_bUseFramerate)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FRAMERATE_NONE))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_CHECK_CULLING_THRESHOLD))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHECK_FRAMERATE_MODE))->SetCheck(0);
	}

	if(m_Settings.m_bUseFramerate)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FRAMERATE_NONE))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHECK_CULLING_THRESHOLD))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHECK_FRAMERATE_MODE))->SetCheck(1);
		GetDlgItem(IDC_COMBO_FRAMERATE_MODE)->EnableWindow(1);
		GetDlgItem(IDC_TEXT_FRAMERATE_TIME)->EnableWindow(1);
		GetDlgItem(IDC_EDIT_FRAMERATE_TIME)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_FRAMERATE_TIME_SEC)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_MAX_THRESHOLD)->EnableWindow(1);
		GetDlgItem(IDC_EDIT_MAX_THRESHOLD)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_MAX_THRESHOLD_PX)->EnableWindow(1);

		if(mode==FramerateTarget)
		{
			GetDlgItem(IDC_CHECK_DYNAMIC_ADJUSTMENT)->EnableWindow(1);
			GetDlgItem(IDC_CHECK_USE_LODS)->EnableWindow(1);
			GetDlgItem(IDC_STATIC_CUTOFF)->EnableWindow(0);
			GetDlgItem(IDC_EDIT_CUTOFF)->EnableWindow(0);
			GetDlgItem(IDC_STATIC_CUTOFF_PX)->EnableWindow(0);
		}
		else
		{
			GetDlgItem(IDC_CHECK_DYNAMIC_ADJUSTMENT)->EnableWindow(0);
			GetDlgItem(IDC_CHECK_USE_LODS)->EnableWindow(0);
			GetDlgItem(IDC_STATIC_CUTOFF)->EnableWindow(1);
			GetDlgItem(IDC_EDIT_CUTOFF)->EnableWindow(1);
			GetDlgItem(IDC_STATIC_CUTOFF_PX)->EnableWindow(1);
		}

		if(m_Settings.m_bDynamicAdjustment && mode==FramerateTarget)
		{
	 		GetDlgItem(IDC_STATIC_DETAILSTEPS)->EnableWindow(1);
	 		GetDlgItem(IDC_EDIT_DETAIL_STEPS)->EnableWindow(1);
		}
		else
		{
			GetDlgItem(IDC_STATIC_DETAILSTEPS)->EnableWindow(0);
	 		GetDlgItem(IDC_EDIT_DETAIL_STEPS)->EnableWindow(0);
		}
	}
	else
	{
		GetDlgItem(IDC_COMBO_FRAMERATE_MODE)->EnableWindow(0);
		GetDlgItem(IDC_TEXT_FRAMERATE_TIME)->EnableWindow(0);
		GetDlgItem(IDC_EDIT_FRAMERATE_TIME)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_FRAMERATE_TIME_SEC)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_MAX_THRESHOLD)->EnableWindow(0);
		GetDlgItem(IDC_EDIT_MAX_THRESHOLD)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_MAX_THRESHOLD_PX)->EnableWindow(0);
 		GetDlgItem(IDC_CHECK_USE_LODS)->EnableWindow(0);
 		GetDlgItem(IDC_CHECK_DYNAMIC_ADJUSTMENT)->EnableWindow(0);
 		GetDlgItem(IDC_STATIC_DETAILSTEPS)->EnableWindow(0);
 		GetDlgItem(IDC_EDIT_DETAIL_STEPS)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_CUTOFF)->EnableWindow(0);
		GetDlgItem(IDC_EDIT_CUTOFF)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_CUTOFF_PX)->EnableWindow(0);
	}

	if (m_Settings.m_bCullingThreshold)
	{
		((CButton*)GetDlgItem(IDC_CHECK_CULLING_THRESHOLD))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO_FRAMERATE_NONE))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHECK_FRAMERATE_MODE))->SetCheck(0);
 		GetDlgItem(IDC_EDIT_CULLING_THRESHOLD)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_CULLING_THRESHOLD_PIXELS)->EnableWindow(1);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CULLING_THRESHOLD)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_CULLING_THRESHOLD_PIXELS)->EnableWindow(0);
	}	
}

void PerformanceOptionsPage::OnCheckFramerateMode() 
{
	m_Settings.m_bCullingThreshold=FALSE;
	m_Settings.m_bUseFramerate=TRUE;
	UpdateTargetFramerate();
}

void PerformanceOptionsPage::OnCheckNone() 
{
	m_Settings.m_bCullingThreshold=FALSE;
	m_Settings.m_bUseFramerate=FALSE;
	UpdateTargetFramerate();
}

void PerformanceOptionsPage::OnCheckOcclusionCulling() 
{
	UpdateOcclusionCulling();
}

void PerformanceOptionsPage::UpdateOcclusionCulling()
{
	CButton* pCi = (CButton*) GetDlgItem(IDC_CHECK_OCCLUSION_CULLING);
	CButton* pCot = (CButton*) GetDlgItem(IDC_EDIT_OCCLUSION_THRESHOLD);
	CButton* pCop = (CButton*) GetDlgItem(IDC_OCCLUSION_THRESHOLD_PIXELS);
	
 	ASSERT( pCi );
	ASSERT( pCot);
	ASSERT( pCop);
 
	if( pCi->GetCheck() == 0 )
	{
		pCot->EnableWindow(0);
		pCop->EnableWindow(0);
	}
	else
	{
		pCot->EnableWindow(1);
		pCop->EnableWindow(1);
	}
}

void PerformanceOptionsPage::UpdateStaticModel(bool force_check)
{
	if (!m_Settings.m_bStaticModel)
	{
 		GetDlgItem(IDC_DISABLE_EDITING)->EnableWindow(0);
		((CButton*)GetDlgItem(IDC_DISABLE_EDITING))->SetCheck(0);
	}
	else
	{
 		GetDlgItem(IDC_DISABLE_EDITING)->EnableWindow(1);
		if(force_check)
			((CButton*)GetDlgItem(IDC_DISABLE_EDITING))->SetCheck(1);
	}
}

void PerformanceOptionsPage::OnCheckCullingThreshold() 
{
	m_Settings.m_bCullingThreshold=TRUE;
	m_Settings.m_bUseFramerate=FALSE;
	UpdateTargetFramerate();
}

void PerformanceOptionsPage::OnCheckStaticModel()
{

	UpdateData(true);
	UpdateStaticModel(true);
}

static DisplayListType DisplayListCString2Enum(CString dl)
{
	if(dl == "Geometry")
		return DisplayListGeometry;
	else if(dl == "Segment")
		return DisplayListSegment;
	else 
		return DisplayListOff;	
}

static CString DisplayListEnum2CString(DisplayListType dl)
{
	if(dl == DisplayListGeometry)
		return "Geometry";
	else if(dl == DisplayListSegment)
		return "Segment";
	else 
		return "Off";
}

static HLRMode HLRCString2Enum(CString hlr)
{
	if(hlr == "Analytic")
		return AnalyticHiddenLine;
	else if(hlr == "Fast")
		return FastHiddenLine;
	else 
		return FakeHiddenLine;	
}

static CString HLREnum2CString(HLRMode hlr)
{
	if(hlr == AnalyticHiddenLine)
		return "Analytic";
	else if(hlr == FastHiddenLine)
		return "Fast";
	else 
		return "Fake";
}

void PerformanceOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PerformanceOptionsPage)
 	DDX_CBString(pDX, IDC_COMBO_HLR_MODE, m_Settings.m_csHLRMode);
	DDX_Check(pDX, IDC_CHECK_STATIC_MODEL, m_Settings.m_bStaticModel);
	DDX_Check(pDX, IDC_DISABLE_EDITING, m_Settings.m_bDisableEditing);
	DDX_Check(pDX, IDC_LMV_MODEL, m_Settings.m_bLMV);
 	DDX_Check(pDX, IDC_CHECK_OCCLUSION_CULLING, m_Settings.m_bOcclusionCulling);
	DDX_Text(pDX, IDC_EDIT_OCCLUSION_THRESHOLD, m_Settings.m_OcclusionThreshold);
	DDX_CBString(pDX, IDC_COMBO_DISPLAY_LISTS, m_Settings.m_csDisplayList);
	DDX_Check(pDX, IDC_CHECK_CULLING_THRESHOLD, m_Settings.m_bCullingThreshold);
	DDX_Text(pDX, IDC_EDIT_CULLING_THRESHOLD, m_Settings.m_CullingThreshold);
	DDX_Check(pDX, IDC_CHECK_FRAMERATE_MODE, m_Settings.m_bUseFramerate);
	DDX_CBString(pDX, IDC_COMBO_FRAMERATE_MODE, m_Settings.m_csFramerateMode);
	DDX_Text(pDX, IDC_EDIT_FRAMERATE_TIME, m_Settings.m_FramerateTime);
	DDV_MinMaxFloat(pDX, m_Settings.m_FramerateTime, 0.0f, 5.0f);
	DDX_Text(pDX, IDC_EDIT_MAX_THRESHOLD, m_Settings.m_MaxThreshold);
	DDX_Text(pDX, IDC_EDIT_CUTOFF, m_Settings.m_Cutoff);
	DDX_Check(pDX, IDC_CHECK_USE_LODS, m_Settings.m_bUseLods);
	DDX_Check(pDX, IDC_CHECK_DYNAMIC_ADJUSTMENT, m_Settings.m_bDynamicAdjustment);
	DDX_Text(pDX, IDC_EDIT_DETAIL_STEPS, m_Settings.m_DetailSteps);
	DDX_CBString(pDX, IDC_COMBO_MULTITHREADING, m_Settings.m_csMultiThreading);	
	DDX_Control(pDX, IDC_BUTTON_COLOR_FAKE_HLR, m_Settings.m_clrbtnFakeHLR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PerformanceOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(PerformanceOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_CHECK_FRAMERATE_MODE, OnCheckFramerateMode)
	ON_BN_CLICKED(IDC_CHECK_DYNAMIC_ADJUSTMENT, OnCheckDynamicAdjustment)	
	ON_BN_CLICKED(IDC_CHECK_USE_LODS, OnCheckFramerateMode)	
	ON_BN_CLICKED(IDC_CHECK_OCCLUSION_CULLING, OnCheckOcclusionCulling)
	ON_BN_CLICKED(IDC_CHECK_CULLING_THRESHOLD, OnCheckCullingThreshold)
	ON_BN_CLICKED(IDC_RADIO_FRAMERATE_NONE, OnCheckNone)	
	ON_BN_CLICKED(IDC_CHECK_STATIC_MODEL, OnCheckStaticModel)	
	ON_CBN_SELCHANGE(IDC_COMBO_FRAMERATE_MODE, OnClickFramerateModeMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void PerformanceOptionsPage::OnClickFramerateModeMenu()
{
	UpdateData(TRUE);
	UpdateTargetFramerate();
}

void PerformanceOptionsPage::OnCheckDynamicAdjustment()
{
	UpdateData(TRUE);
	UpdateTargetFramerate();
}

BOOL PerformanceOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();

	m_Settings.Get();
  	
 	UpdateData(FALSE);

	UpdateTargetFramerate();
	UpdateOcclusionCulling();
	UpdateStaticModel(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PerformanceOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}

// Applies the appearance related application settings to the given view
void PerformanceOptionsPage::ApplySettings()
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
	
	m_Settings.Apply(pActiveView);
	
}

void PerformanceOptionsPage::OnButtonReset() 
{
	m_Settings.Reset();
	UpdateData(FALSE);

	UpdateTargetFramerate();
	UpdateOcclusionCulling();
	UpdateStaticModel(false);
}

void PerformanceOptionsPage::OnButtonApply() 
{
	UpdateData(true);
	ApplySettings();
}


////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// AppearanceOptionsPage dialog

static int Ui2AntialiasingLevel(CString level)
{	
	if(level=="2x") 
		return 2;
	else if(level=="4x") 
		return 4;
	else if(level=="8x") 
		return 8;
	else 
	{
		// should never be here
		ASSERT(0);
		return 2;
	}
}

static CString AntialiasingLevel2Ui(int level)
{
	switch(level)
	{
	case 2:
	    return "2x";
	    break;
	case 4:
	    return "4x";
	    break;
	case 8:
	    return "8x";
	default:
	    // should never be here
	    ASSERT(0);
	    return "";
    }
}

AppearanceOptionsPage::AppearanceOptionsPage(CWnd* pParent /*=NULL*/)
	: HOptionsPage(AppearanceOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(AppearanceOptionsPage)
	m_csGreekingModeCombo = _T("Lines");
	m_csGreekingUnitsCombo = _T("px");
	m_csLineWeight = _T("2 pixels");
	m_bSplatRendering = FALSE;
	m_bHideOverlappedText = FALSE;
	m_bUseGreeking = FALSE;
	m_bCiByColopmap = FALSE;
	m_bCiIsolines = FALSE;
	m_bCiByValue = FALSE;
	m_bColorInterpolation = FALSE;
	m_fMarkupWeight = 0.1f;
	m_fGreekingLimit = 0.f;
 	m_FontSize = 0.f;
	m_found_specific_fonts = false;
	m_bLineAntialiasing = FALSE;
 	m_bTextAntialiasing = FALSE;
 	m_bAntialiasing = FALSE;
	m_csAntialiasingLevel = _T("2x");
	m_bFastMarkers = TRUE;
	//}}AFX_DATA_INIT
}


void AppearanceOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AppearanceOptionsPage)
	DDX_CBString(pDX, IDC_COMBO_GREEKING_MODE, m_csGreekingModeCombo);
	DDX_CBString(pDX, IDC_COMBO_GREEKING_UNITS, m_csGreekingUnitsCombo);
	DDX_Text(pDX, IDC_EDIT_LINE_WEIGHT, m_csLineWeight);
	DDX_Control(pDX, IDC_COMBO_FONT_NAME, m_FontNameCombo);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACKGROUND_TOP, m_clrbtnBackgroundTop);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACKGROUND_BOTTOM, m_clrbtnBackgroundBottom);
	DDX_Control(pDX, IDC_BUTTON_COLOR_MARKUP, m_clrbtnMarkup);
	DDX_Check(pDX, IDC_SPLAT_RENDERING, m_bSplatRendering);
	DDX_Check(pDX, IDC_FAST_MARKER_DRAWING, m_bFastMarkers);
	DDX_Check(pDX, IDC_CHECK_HIDE_OVERLAPPED_TEXT, m_bHideOverlappedText);
	DDX_Check(pDX, IDC_CHECK_GREEKING_LIMIT, m_bUseGreeking);
	DDX_Check(pDX, IDC_CHECK_CI_BY_COLORMAP_INDEX, m_bCiByColopmap);
	DDX_Check(pDX, IDC_CHECK_CI_ISOLINES, m_bCiIsolines);
	DDX_Check(pDX, IDC_CHECK_CI_BY_VALUE, m_bCiByValue);
	DDX_Check(pDX, IDC_CHECK_COLOR_INTERPOLATION, m_bColorInterpolation);
	DDX_Text(pDX, IDC_EDIT_MARKUP_WEIGHT, m_fMarkupWeight);
	DDX_Text(pDX, IDC_EDIT_GREEKING_LIMIT, m_fGreekingLimit);
	DDV_MinMaxFloat(pDX, m_fGreekingLimit, 0.f, 100000.f);
	DDV_MinMaxFloat(pDX, m_fMarkupWeight, 0.1f, 25.f);
	DDX_Text(pDX, IDC_EDIT_FONT_SIZE, m_FontSize);
	DDX_CBString(pDX, IDC_COMBO_FONT_UNITS, m_csFontUnitsCombo);
	DDV_MinMaxUInt(pDX, m_FontSize, MIN_FONT_SIZE, MAX_FONT_SIZE);
	DDX_Check(pDX, IDC_CHECK_ANTIALIASING_LINE, m_bLineAntialiasing);
 	DDX_Check(pDX, IDC_CHECK_ANTIALIASING_TEXT, m_bTextAntialiasing);
	DDX_Check(pDX, IDC_CHECK_ANTIALIAS, m_bAntialiasing);
	DDX_CBString(pDX, IDC_COMBO_ANTIALIASING_LEVEL, m_csAntialiasingLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AppearanceOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(AppearanceOptionsPage)
	ON_CBN_SELCHANGE(IDC_COMBO_GREEKING_MODE, OnCheckGreekingLimit)
	ON_CBN_SELCHANGE(IDC_COMBO_GREEKING_UNITS, OnCheckGreekingLimit)
	ON_BN_CLICKED(IDC_CHECK_GREEKING_LIMIT, OnCheckGreekingLimit)
	ON_BN_CLICKED(IDC_CHECK_COLOR_INTERPOLATION, OnCheckColorInterpolation)
  	ON_BN_CLICKED(IDC_CHECK_CI_ISOLINES, OnCheckCiIsolines)
	ON_BN_CLICKED(IDC_CHECK_CI_BY_VALUE, OnCheckCiByValue)
	ON_BN_CLICKED(IDC_CHECK_CI_BY_COLORMAP_INDEX, OnCheckCiByColormapIndex)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_CBN_SETFOCUS(IDC_COMBO_FONT_NAME, OnSetfocusComboFontName)
	ON_BN_CLICKED(IDC_CHECK_ANTIALIAS, OnCheckAntialias)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AppearanceOptionsPage message handlers
BOOL AppearanceOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();

	m_csLineWeight				= CAppSettings::LineWeight;

	m_clrbtnBackgroundTop.currentcolor = CAppSettings::WindowBackgroundTopColor;
	m_clrbtnBackgroundBottom.currentcolor = CAppSettings::WindowBackgroundBottomColor;

	m_bAntialiasing = bool2BOOL(CAppSettings::bAntiAliasing );
  	m_bLineAntialiasing = bool2BOOL(CAppSettings::LineAntialiasing);
  	m_bTextAntialiasing = bool2BOOL(CAppSettings::TextAntialiasing);
	m_csAntialiasingLevel = AntialiasingLevel2Ui(CAppSettings::AntialiasingLevel);
 
	m_clrbtnMarkup.currentcolor = CAppSettings::MarkupColor;

	m_csGreekingUnitsCombo = CAppSettings::GreekingUnits;
	m_csGreekingModeCombo = CAppSettings::GreekingMode;

	m_fGreekingLimit = CAppSettings::GreekingLimit/1000.0f;

	m_fMarkupWeight = CAppSettings::MarkupWeight/100.0f;
	// set the range of "markup weight" spin control
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MARKUP_WEIGHT))->SetRange(1, 25);

	m_bSplatRendering = bool2BOOL(CAppSettings::bSplatRendering);

	m_bHideOverlappedText = bool2BOOL(CAppSettings::bHideOverlappedText);
	m_bUseGreeking = bool2BOOL(CAppSettings::bUseGreeking);

	m_bCiByColopmap = bool2BOOL(CAppSettings::bCiByColormapIndex);
	m_bCiIsolines = bool2BOOL(CAppSettings::bCiIsolines);
	m_bCiByValue = bool2BOOL(CAppSettings::bCiByValue);
	m_bColorInterpolation = bool2BOOL(CAppSettings::bColorInterpolation);
	m_bFastMarkers = bool2BOOL(CAppSettings::bFastMarkers);

	PopulateFontNameCombo();
	int is_sel = m_FontNameCombo.SelectString(0, CAppSettings::FontName);
	if( is_sel == CB_ERR )
	{
	    // may be this was a specific font which we didn't discover to save time
	    PopulateFontNameCombo(true);
	    int is_sel = m_FontNameCombo.SelectString(0, CAppSettings::FontName);
	    if( is_sel == CB_ERR )
	    {
		// we tried but we couldn't (may be because of driver changed or font deleted) 
		// fall back to the default one. The registry setting will get defaulted too, but we can't help - Rajesh B (06/07/04)
		CAppSettings::FontName = CAppSettings::DefaultFontName;
		m_FontNameCombo.SelectString(0, CAppSettings::FontName);
	    }
	}
	m_FontSize = atof(H_ASCII_TEXT(CAppSettings::FontSize));
	m_csFontUnitsCombo = CAppSettings::FontUnits;

	UpdateData(FALSE);
	UpdateGreekingLimitData();
	UpdateColorInterpolationChecks();
	UpdateDriverDependentControls();
 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AppearanceOptionsPage::OnOK()
{
	
	ApplySettings();
	HOptionsPage::OnOK();
}

// Applies the appearance related application settings to the given view
void AppearanceOptionsPage::ApplySettings()
{
	bool is_changed=false;
	CAppSettings::LineWeight = m_csLineWeight;

	CAppSettings::WindowBackgroundTopColor = m_clrbtnBackgroundTop.currentcolor;
	CAppSettings::WindowBackgroundBottomColor = m_clrbtnBackgroundBottom.currentcolor;

 
	CAppSettings::MarkupColor = m_clrbtnMarkup.currentcolor;
	CAppSettings::MarkupWeight = (int) (m_fMarkupWeight*100);

	CAppSettings::bSplatRendering = BOOL2bool(m_bSplatRendering);
	CAppSettings::bFastMarkers = BOOL2bool(m_bFastMarkers);

	CAppSettings::bHideOverlappedText = BOOL2bool(m_bHideOverlappedText);
	CAppSettings::bUseGreeking = BOOL2bool(m_bUseGreeking);
	CAppSettings::GreekingLimit = (int) (m_fGreekingLimit*1000);
	CAppSettings::GreekingMode= m_csGreekingModeCombo;
	CAppSettings::GreekingUnits = m_csGreekingUnitsCombo;

	CAppSettings::bCiByColormapIndex = BOOL2bool(m_bCiByColopmap);
	CAppSettings::bCiIsolines = BOOL2bool(m_bCiIsolines);
	CAppSettings::bCiByValue = BOOL2bool(m_bCiByValue);
	CAppSettings::bColorInterpolation = BOOL2bool(m_bColorInterpolation);
	int font_sel = m_FontNameCombo.GetCurSel();
	if (font_sel != -1)	
	{
	    CAppSettings::FontName.GetBuffer(m_FontNameCombo.GetLBTextLen(font_sel));
	    m_FontNameCombo.GetLBText(m_FontNameCombo.GetCurSel(), CAppSettings::FontName);
	    CAppSettings::FontName.ReleaseBuffer();
	}
	CAppSettings::FontSize.Format(_T("%f"), m_FontSize);
	CAppSettings::FontUnits = m_csFontUnitsCombo;

	bool new_bAntialiasing = BOOL2bool(m_bAntialiasing);
    if( new_bAntialiasing != CAppSettings::bAntiAliasing )
    {
		CAppSettings::bAntiAliasing = new_bAntialiasing;
		is_changed = true;
    }
	CAppSettings::AntialiasingLevel=Ui2AntialiasingLevel(m_csAntialiasingLevel);
	CAppSettings::LineAntialiasing = BOOL2bool(m_bLineAntialiasing);
    CAppSettings::TextAntialiasing = BOOL2bool(m_bTextAntialiasing);

	// Apply these settings to the currently active view
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();

    if( pActiveView )
    {
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
			return;

		HC_Open_Segment_By_Key(pBaseView->GetViewKey()); {
			if (CAppSettings::bAntiAliasing)
				HC_Set_Driver_Options (H_FORMAT_TEXT ("anti-alias=%d", CAppSettings::AntialiasingLevel));
			else
				HC_Set_Driver_Options ("no anti-alias");
		} HC_Close_Segment ();
	    
	    HSelectionSet* pSelSet = pBaseView->GetSelection();
	    assert(pSelSet);
	    
		pBaseView->SetSuppressUpdate(true);

	    // apply the window background color
	    HPoint WindowTopColor, WindowBottomColor;
	    WindowTopColor.Set(
		static_cast<float>(GetRValue(CAppSettings::WindowBackgroundTopColor))/255.0f,
		static_cast<float>(GetGValue(CAppSettings::WindowBackgroundTopColor))/255.0f,
		static_cast<float>(GetBValue(CAppSettings::WindowBackgroundTopColor))/255.0f);
	    
	    WindowBottomColor.Set(
		static_cast<float>(GetRValue(CAppSettings::WindowBackgroundBottomColor))/255.0f,
		static_cast<float>(GetGValue(CAppSettings::WindowBackgroundBottomColor))/255.0f,
		static_cast<float>(GetBValue(CAppSettings::WindowBackgroundBottomColor))/255.0f);
	    
	    pBaseView->SetWindowColor(WindowTopColor, WindowBottomColor);
	    
 	    
	    // apply markup settings
	    HPoint MarkupColor;
	    MarkupColor.Set(
		static_cast<float>(GetRValue(CAppSettings::MarkupColor))/255.0f,
		static_cast<float>(GetGValue(CAppSettings::MarkupColor))/255.0f,
		static_cast<float>(GetBValue(CAppSettings::MarkupColor))/255.0f);
	    pActiveView->SetMarkupColor(CAppSettings::MarkupColor);
 	    pBaseView->GetMarkupManager()->SetMarkupWeight(CAppSettings::MarkupWeight/100.0f);
	    
	    pBaseView->SetColorInterpolation(CAppSettings::bCiByValue);
 	    pBaseView->SetColorIndexInterpolation(CAppSettings::bCiByColormapIndex, CAppSettings::bCiIsolines);
	    
	    // apply font settings
	    pActiveView->SetSceneFont( CAppSettings::FontName, CAppSettings::FontSize, CAppSettings::FontUnits );

		//apply hiding of overlapped text (or not)
		pBaseView->SetHideOverlappedText(CAppSettings::bHideOverlappedText);

		HC_Open_Segment_By_Key(pBaseView->GetSceneKey());
			HC_Set_Variable_Line_Weight(H_ASCII_TEXT(CAppSettings::LineWeight));
			HC_Set_Variable_Edge_Weight(H_ASCII_TEXT(CAppSettings::LineWeight));
			
			//Apply Greeking Settings
			char cGreekingSettings[2048]="no greeking limit";

			if(CAppSettings::bUseGreeking)
			{
				CString csGreekingSettings;
				CAppSettings::GreekingLimit = (int) (m_fGreekingLimit*1000);
				CAppSettings::GreekingMode= m_csGreekingModeCombo;
				CAppSettings::GreekingUnits = m_csGreekingUnitsCombo;
				
				csGreekingSettings.Format(_T("greeking mode= %s, greeking limit= %f %s"), 
					CAppSettings::GreekingMode,	CAppSettings::GreekingLimit/1000.f, 
					CAppSettings::GreekingUnits);

				strcpy(cGreekingSettings, H_ASCII_TEXT(csGreekingSettings));
			}
			HC_Set_Text_Font(cGreekingSettings);
		HC_Close_Segment();
		
		//splat rendering handling
		((HSolidView*)pBaseView)->SetSplatRendering(BOOL2bool(CAppSettings::bSplatRendering));

		pBaseView->SetFastMarkerDrawing(CAppSettings::bFastMarkers);
		
 		pBaseView->SetLineAntialiasing(CAppSettings::LineAntialiasing);
 		pBaseView->SetTextAntialiasing(CAppSettings::TextAntialiasing);
	    
	    pBaseView->SetSuppressUpdate(false);
		pBaseView->Update();
	}
}

void AppearanceOptionsPage::UpdateColorInterpolationChecks()
{
	CButton* pCi = (CButton*) GetDlgItem(IDC_CHECK_COLOR_INTERPOLATION);
	CButton* pCii = (CButton*) GetDlgItem(IDC_CHECK_CI_BY_COLORMAP_INDEX);
	CButton* pCiv = (CButton*) GetDlgItem(IDC_CHECK_CI_BY_VALUE);
	CButton* pCil = (CButton*) GetDlgItem(IDC_CHECK_CI_ISOLINES);
	ASSERT( pCi );
	ASSERT( pCii );
	ASSERT( pCiv );
	ASSERT( pCil );

	if( pCi->GetCheck() == 0 )
	{
		pCii->SetCheck(0);
		pCii->EnableWindow(0);
		pCiv->SetCheck(0);
		pCiv->EnableWindow(0);
		pCil->SetCheck(0);
		pCil->EnableWindow(0);
	}
	else
	{
		pCii->EnableWindow(1);
		pCiv->EnableWindow(1);
		if( pCii->GetCheck() == 0 )
		{
			pCil->SetCheck(0);
			pCil->EnableWindow(0);
		}
		else
			pCil->EnableWindow(1);
	}

}

void AppearanceOptionsPage::UpdateGreekingLimitData()
{
	CButton* pGrkChk = (CButton*) GetDlgItem(IDC_CHECK_GREEKING_LIMIT);
	CButton* pGrkMd =  (CButton*)GetDlgItem(IDC_COMBO_GREEKING_MODE);
	CButton* pGrkSz =  (CButton*)GetDlgItem(IDC_EDIT_GREEKING_LIMIT);
	CButton* pGrkUn =  (CButton*)GetDlgItem(IDC_COMBO_GREEKING_UNITS);

	ASSERT( pGrkChk );
	ASSERT( pGrkMd );
	ASSERT( pGrkSz );
	ASSERT( pGrkUn );

	if( pGrkChk->GetCheck() == 0 )
	{
		pGrkMd->SetCheck(0);
		pGrkMd->EnableWindow(0);
		pGrkSz->SetCheck(0);
		pGrkSz->EnableWindow(0);
		pGrkUn->SetCheck(0);
		pGrkUn->EnableWindow(0);
		GetDlgItem(IDC_GREEKING_TEXT_1)->EnableWindow(0);
		GetDlgItem(IDC_GREEKING_TEXT_2)->EnableWindow(0);
		GetDlgItem(IDC_GREEKING_TEXT_3)->EnableWindow(0);
		GetDlgItem(IDC_GREEKING_TEXT_4)->EnableWindow(0);
		GetDlgItem(IDC_GREEKING_TEXT_5)->EnableWindow(0);
	}
	else
	{
		pGrkMd->EnableWindow(1);
		pGrkSz->EnableWindow(1);
		pGrkUn->EnableWindow(1);
		GetDlgItem(IDC_GREEKING_TEXT_1)->EnableWindow(1);
		GetDlgItem(IDC_GREEKING_TEXT_2)->EnableWindow(1);
		GetDlgItem(IDC_GREEKING_TEXT_3)->EnableWindow(1);
		GetDlgItem(IDC_GREEKING_TEXT_4)->EnableWindow(1);
		GetDlgItem(IDC_GREEKING_TEXT_5)->EnableWindow(1);
	}	
}

 

void AppearanceOptionsPage::OnSetfocusComboFontName() 
{
    if( !m_found_specific_fonts)
	PopulateFontNameCombo(true);	
}

void AppearanceOptionsPage::PopulateFontNameCombo(bool specific_fonts)
{
	int fcount = 0;
    char font_name[MVO_BUFFER_SIZE];

	CWaitCursor busy_discoverying_fonts;

	// Getting font listing from HOOPS seems a big pain as of now. Fonts are per driver basis
	// so, I will have to have a view (which I may not). I will have to create a dummy 
	// one under opengl or msw driver and then query the fonts
	CString strWndClass = AfxRegisterWndClass(0);
        HWND hWND = ::CreateWindow (strWndClass, _T("fsd1"), 
		  WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		  1,1,1,1, 0, 0, AfxGetInstanceHandle(), 0);

	assert(hWND);

	HC_KEY dummy_font_seg = HC_KOpen_Segment("?driver/msw/font search dummy");

		char dr_opts[MVO_BUFFER_SIZE];
		sprintf (dr_opts, "use window id = %s%p", H_EXTRA_POINTER_FORMAT, hWND);

		// we would like to have all generic fonts at the head and then defined and finally 
		// the specifics
		HC_Begin_Font_Search(".","generic");
			HC_Show_Font_Count (&fcount);
			while (HC_Find_Font (font_name)) {
				m_FontNameCombo.AddString(H_TEXT(font_name));
		      }
		HC_End_Font_Search();

		fcount = 0;
		HC_Begin_Font_Search(".","defined ");
			HC_Show_Font_Count (&fcount);
			while (HC_Find_Font (font_name)) {
				m_FontNameCombo.AddString(H_TEXT(font_name));
		      }
		HC_End_Font_Search();

		if( specific_fonts )
		{
		    fcount = 0;
		    HC_Begin_Font_Search(".","specific");
			    HC_Show_Font_Count (&fcount);
			    while (HC_Find_Font (font_name)) {
				    m_FontNameCombo.AddString(H_TEXT(font_name));
			  }
		    HC_End_Font_Search();
		    m_found_specific_fonts = true;
		}

	HC_Close_Segment();
	HC_Delete_By_Key(dummy_font_seg);

	// Find the longest string in the combo box and set the width.
	CString str;
	CSize   sz;
	int     dx=0;
	CDC*    pDC = m_FontNameCombo.GetDC();
	for (int i=0;i < m_FontNameCombo.GetCount();i++)
	{
	   m_FontNameCombo.GetLBText( i, str );
	   sz = pDC->GetTextExtent(str);

	   if (sz.cx > dx)
		  dx = sz.cx;
	}
	m_FontNameCombo.ReleaseDC(pDC);

	// Adjust the width for the vertical scroll bar and the left and right border.
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);

	// Set the width of the list box so that every item is completely visible.
	m_FontNameCombo.SetDroppedWidth(dx);

    ::DestroyWindow(hWND);

}


void AppearanceOptionsPage::OnCheckGreekingLimit()
{
	UpdateGreekingLimitData();
}
 
void AppearanceOptionsPage::OnCheckColorInterpolation() 
{
	UpdateColorInterpolationChecks();
}

 

void AppearanceOptionsPage::OnCheckCiIsolines() 
{
	UpdateColorInterpolationChecks();
}

void AppearanceOptionsPage::OnCheckCiByValue() 
{
	UpdateColorInterpolationChecks();
}

void AppearanceOptionsPage::OnCheckCiByColormapIndex() 
{
	UpdateColorInterpolationChecks();
}


void AppearanceOptionsPage::OnButtonReset() 
{
	// restore the default values
	m_csLineWeight = CAppSettings::DefaultLineWeight;
	m_clrbtnBackgroundTop.currentcolor = CAppSettings::DefaultWindowBackgroundTopColor;
	m_clrbtnBackgroundBottom.currentcolor = CAppSettings::DefaultWindowBackgroundBottomColor;
	m_clrbtnMarkup.currentcolor = CAppSettings::DefaultMarkupColor;
	m_fMarkupWeight = CAppSettings::DefaultMarkupWeight/100.0f;
	m_bSplatRendering = CAppSettings::DefaultbSplatRendering;
	m_bFastMarkers = CAppSettings::bFastMarkers;
	m_fGreekingLimit = CAppSettings::DefaultGreekingLimit/1000.0f;
	m_bHideOverlappedText = bool2BOOL(CAppSettings::DefaultHideOverlappedText);
	m_bUseGreeking = bool2BOOL(CAppSettings::DefaultbUseGreeking);
	m_csGreekingModeCombo = CAppSettings::DefaultGreekingMode;
	m_csGreekingUnitsCombo = CAppSettings::DefaultGreekingUnits;
	m_bCiByColopmap = bool2BOOL(CAppSettings::DefaultbCiByColormapIndex);
	m_bCiIsolines = bool2BOOL(CAppSettings::DefaultbCiIsolines);
	m_bCiByValue = bool2BOOL(CAppSettings::DefaultbCiByValue);
	m_bColorInterpolation = bool2BOOL(CAppSettings::DefaultbColorInterpolation);
	m_FontNameCombo.SelectString(0, CAppSettings::DefaultFontName);
	m_FontSize = atof(H_ASCII_TEXT(CAppSettings::DefaultFontSize));
	m_csFontUnitsCombo = CAppSettings::DefaultFontUnits;
	m_bAntialiasing = bool2BOOL(CAppSettings::DefaultbAntiAliasing);
	m_bLineAntialiasing = bool2BOOL(CAppSettings::DefaultLineAntialiasing);
	m_bTextAntialiasing = bool2BOOL(CAppSettings::DefaultTextAntialiasing);
	m_csAntialiasingLevel =  AntialiasingLevel2Ui(CAppSettings::DefaultAntialiasingLevel);

	// update the dialog
	UpdateData(FALSE);
	UpdateColorInterpolationChecks();
	UpdateGreekingLimitData();
	UpdateDriverDependentControls();
 
	// the color buttons needs redraw to reflect new colors - refresh here
	RedrawWindow();
}

void AppearanceOptionsPage::OnButtonApply() 
{
	UpdateData(true);
	ApplySettings();
}

void AppearanceOptionsPage::OnCheckAntialias() 
{
	UpdateData(true);
	UpdateDriverDependentControls();
}

void AppearanceOptionsPage::UpdateDriverDependentControls() 
{
	CButton* pAAChk =  (CButton*)GetDlgItem(IDC_CHECK_ANTIALIAS);
	CButton* pAALvl =  (CButton*)GetDlgItem(IDC_COMBO_ANTIALIASING_LEVEL);

	ASSERT( pAAChk );
	ASSERT( pAALvl );
	CString cur_sel=CAppSettings::HoopsDriver;

	if( cur_sel != "opengl2" && cur_sel != "opengl" && cur_sel != "direct3d" && cur_sel != "dx9")
	{
		pAAChk->SetCheck(0);
		pAAChk->EnableWindow(0);

		pAALvl->SetCheck(0);
		pAALvl->EnableWindow(0);
	}
	else
	{
		pAAChk->EnableWindow(1);

		if (m_bAntialiasing)
		{		
			pAALvl->SetCheck(1);
			pAALvl->EnableWindow(1);
		}
		else
		{
			pAALvl->SetCheck(0);
			pAALvl->EnableWindow(0);
		}
	}
}


void GeneralOptionsPage::OnButtonImportOptions()
{
	CString filter = _T("Partviewer Options (*.pvo)|*.pvo|");
	filter += _T("All Files (*.*)|*.*|");
	CString def_ext = _T(".pvo");
	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	CFileDialog my_dlg(TRUE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter , NULL);
	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

	if (my_dlg.DoModal() == IDOK) 
	{
		CString filename;
		filename = my_dlg.GetPathName();
		CAppSettings::ImportOptions(filename);
	}	
}

void GeneralOptionsPage::OnButtonWriteToRegistry()
{
	CAppSettings::CommitAllOptions();
	CAppSettings::WriteSettingsToRegistry();
}

void GeneralOptionsPage::OnButtonExportOptions()
{
	CString filter = _T("Partviewer Options (*.pvo)|*.pvo|");
	filter += _T("All Files (*.*)|*.*|");
	CString def_ext = _T(".pvo");
	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	CFileDialog my_dlg(FALSE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);
	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

	if (my_dlg.DoModal() == IDOK) 
	{
		CString filename;
		filename = my_dlg.GetPathName();
		CAppSettings::ExportOptions(filename);
	}
}

void GeneralOptionsPage::OnCheckStereoMode()
{
	UpdateStereoMode();
}

void GeneralOptionsPage::UpdateStereoMode()
{
	CButton* pCSM = (CButton*) GetDlgItem(IDC_CHECK_STEREO);
	CButton* pESM = (CButton*)GetDlgItem(IDC_EDIT_STEREO_SEPARATION);
	ASSERT( pCSM );
	ASSERT( pESM );	

	if( pCSM->GetCheck() == 0 )
	{
		//pESM->SetCheck(0);
		pESM->EnableWindow(0);
		GetDlgItem(IDC_STEREO_TEXT)->EnableWindow(0);
		GetDlgItem(IDC_TEXT_STEREO_DEGREES)->EnableWindow(0);
	}
	else
	{
		pESM->SetCheck(1);
		pESM->EnableWindow(1);
		GetDlgItem(IDC_STEREO_TEXT)->EnableWindow(1);
		GetDlgItem(IDC_TEXT_STEREO_DEGREES)->EnableWindow(1);
	}	
}





/////////////////////////////////////////////////////////////////////////////
// GeneralOptionsPage dialog


GeneralOptionsPage::GeneralOptionsPage(CWnd* pParent /*=NULL*/)
	: HOptionsPage(GeneralOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(GeneralOptionsPage)
	m_csHoopsDriver = _T("opengl");
	m_bForceSoftware = FALSE;
	m_bDisplayStats = FALSE;
	m_bDisplayAxisTriad = TRUE;
	m_bBackplaneCulling = FALSE;
	m_csCoordSysHandedness = _T("Right Handed");
	m_csRenderMode = _T("Gouraud");
 	m_csPolygonHandedness = _T("Left");
	m_csTransparencyStyle = _T("blended");
	m_csTransparencySorting = _T("z-sort only");
	m_csTransparencyDepthPeelingLayers = _T("1");
	m_bStereoMode = FALSE;
	m_fStereoSeparation = 0.f;
	m_bDoubleBuffer = TRUE;
	m_bDepthWriting = FALSE;
	//}}AFX_DATA_INIT
}


void GeneralOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeneralOptionsPage)
	DDX_CBString(pDX, IDC_COMBO_DRIVER, m_csHoopsDriver);
	DDX_Check(pDX, IDC_CHECK_FORCE_SOFTWARE, m_bForceSoftware);
 	DDX_Check(pDX, IDC_CHECK_DISPLAY_STATS, m_bDisplayStats);
	DDX_Check(pDX, IDC_CHECK_AXIS_TRIAD, m_bDisplayAxisTriad);
	DDX_Check(pDX, IDC_CHECK_BACKPLANE_CULLING, m_bBackplaneCulling);
	DDX_CBString(pDX, IDC_COMBO_COORDINATE_SYSTEM_HANDEDNESS, m_csCoordSysHandedness);
	DDX_CBString(pDX, IDC_COMBO_DEFAULT_RENDER_MODE, m_csRenderMode);
 	DDX_CBString(pDX, IDC_COMBO_POLYGON_HANDEDNESS, m_csPolygonHandedness);
	DDX_CBString(pDX, IDC_COMBO_TRANSPARENCY_STYLE, m_csTransparencyStyle);
	DDX_CBString(pDX, IDC_COMBO_TRANSPARENCY_SORTING, m_csTransparencySorting);
	DDX_CBString(pDX, IDC_COMBO_TRANSPARENCY_LAYERS, m_csTransparencyDepthPeelingLayers);
 	DDX_Check(pDX, IDC_CHECK_STEREO, m_bStereoMode);
	DDX_Check(pDX, IDC_CHECK_DOUBLE_BUFFER, m_bDoubleBuffer);
	DDX_Check(pDX, IDC_CHECK_DEPTH_WRITING, m_bDepthWriting);
	DDX_Text(pDX, IDC_EDIT_STEREO_SEPARATION, m_fStereoSeparation);
	DDV_MinMaxFloat(pDX, m_fStereoSeparation, 0.0f, 360.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeneralOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(GeneralOptionsPage)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVER, OnSelchangeComboDriver)
	ON_CBN_SELCHANGE(IDC_COMBO_POLYGON_HANDEDNESS, OnSelchangeComboPolygonHandedness)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENCY_SORTING, OnSelchangeComboTransparencySorting)
	ON_BN_CLICKED(IDC_CHECK_STEREO, OnCheckStereoMode)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_OPTIONS, OnButtonImportOptions)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_OPTIONS, OnButtonExportOptions)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_OPTIONS, OnButtonWriteToRegistry)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static CString RenderModeEnum2CString(HRenderMode e_render_mode)
{
    switch (e_render_mode)
    {
		case HRenderWireframe:
			return "Wireframe";
		case HRenderSilhouette:
			return "Silhouette";
		case HRenderHiddenLine:
			return "Hidden Line";
		case HRenderFlat:
			return "Flat Shaded";
		case HRenderGouraud:
			return "Gouraud Shaded";
		case HRenderGouraudWithLines:
			return "Gouraud Shaded With Lines";
		case HRenderGoochShaded:
			return "Gooch Shaded";
		case HRenderPhong:
			return "Phong Shaded";
		case HRenderWireframeWithSilhouette:
			return "Wireframe Silhouette";
		case HRenderShadedWireframe:
			return "Shaded Wireframe";
		case HRenderVertices:
			return "Vertices";
		case HRenderShadedVertices:
			return "Shaded Vertices";
		case HRenderBRepHiddenLineFast:
			return "BRep Hidden Line";
		case HRenderBRepWireframe:
			return "BRep Wireframe";
		case HRenderFakeHiddenLine:
			return "Fake Hidden Line";
	}
    ASSERT(0);
	return "";
}

static HRenderMode RenderModeCString2Enum(CString cs_render_mode)
{
    if( cs_render_mode == "Wireframe")
		return HRenderWireframe;
    else if ( cs_render_mode ==  "Gouraud Shaded")
		return HRenderGouraud;
	else if ( cs_render_mode ==  "Gouraud Shaded With Lines")
		return HRenderGouraudWithLines;
    else if( cs_render_mode == "Silhouette")
		return HRenderSilhouette;
    else if( cs_render_mode == "Hidden Line")
		return HRenderHiddenLine;
    else if ( cs_render_mode == "HiddenLineHOOPS")
		return HRenderHiddenLineHOOPS;
    else if ( cs_render_mode == "HiddenLineFast")
		return HRenderHiddenLineFast;
    else if ( cs_render_mode ==  "Flat Shaded")
		return HRenderFlat;
	else if(cs_render_mode ==  "Gooch Shaded")			
		return HRenderGoochShaded;
    else if ( cs_render_mode ==  "Phong Shaded")
		return HRenderPhong;
    else if ( cs_render_mode == "Triangulation")
		return HRenderTriangulation;
	else if ( cs_render_mode == "BRep Hidden Line")
		return HRenderBRepHiddenLineFast;		
	else if ( cs_render_mode == "BRep Wireframe")
		return HRenderBRepWireframe;
	else if(cs_render_mode == "Wireframe Silhouette")
		return HRenderWireframeWithSilhouette;
	else if(cs_render_mode == "Shaded Wireframe")
		return HRenderShadedWireframe;
	else if(cs_render_mode == "Vertices")		
		return HRenderVertices;
	else if(cs_render_mode ==  "Shaded Vertices")			
		return HRenderShadedVertices;
	else if(cs_render_mode ==  "Fake Hidden Line")			
		return HRenderFakeHiddenLine;
	else
	{
		ASSERT(0);
		return HRenderGouraud;
	}
}


static CString PolygonHandednessEnum2CString(ModelHandedness e_poly_hnd)
{
	if( e_poly_hnd == HandednessSetLeft )
		return "Left";
	else if( e_poly_hnd == HandednessSetRight )
		return "Right";
	else if( e_poly_hnd == HandednessSetNone )
		return "None";
	else
	{
		// should never be here
		ASSERT(0);
		return "";
	}
}

static ModelHandedness PolygonHandednessCString2Enum(CString cs_poly_hnd)
{
	if( cs_poly_hnd == "Left" )
		return HandednessSetLeft;
	else if( cs_poly_hnd == "Right" )
		return HandednessSetRight;
	else if( cs_poly_hnd == "None" )
		return HandednessSetNone;
	else
	{
		// should never be here
		ASSERT(0);
		return HandednessSetLeft;
	}
}


static int AntialiasingLevel2Int(CString cs)
{
	if( cs == "2x" )
		return 2;
	else if( cs == "4x" )
		return 4;
	else if( cs == "8x" )
		return 8;
	else
	{
		// should never be here
		ASSERT(0);
		return 2;
	}
}
 

static HShadowRenderingMode ShadowRenderingModeCString2Enum(CString cs_shadow)
{
	if( cs_shadow == "Software" )
	{
		if(CAppSettings::HoopsDriver=="msw")
			return SoftwareShadow;
		else
			return SoftwareOpenglShadow;
	}
	else if( cs_shadow == "Hardware" )
		return HardwareShadow;
	else
	{
		// should never be here
		ASSERT(0);
		return SoftwareShadow;
	}
}


 
static CString HoopsDriverSetting2Ui(CString hoops_driver_setting)
{
	if( hoops_driver_setting == "opengl" )
		return "OpenGL";
	else if( hoops_driver_setting == "opengl2" )
		return "OpenGL 2";
	else if( hoops_driver_setting == "msw" )
		return "Win GDI";
	else if( hoops_driver_setting == "direct3d" )
		return "Direct3D";
	else if( hoops_driver_setting == "dx9" )
		return "DX9";
	else
	{
		// should never be here
		ASSERT(0);
		return "";
	}
}

static CString ShadowRenderingModeSetting2Ui(HShadowRenderingMode mode)
{
	switch(mode)
	{
	case SoftwareShadow:
	    return "Software";
	    break;
	case HardwareShadow:
	    return "Hardware";
	    break;
	case SoftwareOpenglShadow:
	    return "Software";
	default:
	    // should never be here
	    ASSERT(0);
	    return "";
	    }
	    

}

static CString HoopsDriverUi2Setting(CString hoops_driver_ui)
{
	if( hoops_driver_ui == "OpenGL" )
		return "opengl";
	else if( hoops_driver_ui == "OpenGL 2" )
		return "opengl2";
	else if( hoops_driver_ui == "Win GDI" )
		return "msw";
	else if( hoops_driver_ui == "Direct3D" )
		return "direct3d";
	else if( hoops_driver_ui == "DX9")
		return "dx9";
	else
	{
		// should never be here
		ASSERT(0);
		return "";
	}
}

/////////////////////////////////////////////////////////////////////////////
// GeneralOptionsPage message handlers
BOOL GeneralOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();

	m_csHoopsDriver = HoopsDriverSetting2Ui(CAppSettings::HoopsDriver);
 	m_bForceSoftware = bool2BOOL(CAppSettings::bDriverForceSoftware);
 	m_bDisplayStats = bool2BOOL(CAppSettings::bDriverDisplayStats);
	m_bDisplayAxisTriad = bool2BOOL(CAppSettings::bDisplayAxisTriad);
	//m_bBackplaneCulling = bool2BOOL(CAppSettings::bBackplaneCulling);
	//m_csCoordSysHandedness = (CAppSettings::CoordinateSystemHandedness == HandednessLeft) ? "Right Handed" : "Left Handed";
	//m_csPolygonHandedness = PolygonHandednessEnum2CString(CAppSettings::PolygonHandedness);
	m_bDoubleBuffer = bool2BOOL(CAppSettings::DoubleBuffer);
	m_csRenderMode = RenderModeEnum2CString(CAppSettings::RenderMode);
	m_csTransparencyStyle = CAppSettings::TransparencyStyle;
	m_csTransparencySorting = CAppSettings::TransparencySorting;
	m_csTransparencyDepthPeelingLayers = CAppSettings::TransparencyDepthPeelingLayers;
	m_bDepthWriting = CAppSettings::DepthWriting;

	//the perils of renaming options
	if(m_csTransparencySorting == "z-sort only")
		m_csTransparencySorting = "z-sort nicest";
	 
	m_bStereoMode = CAppSettings::StereoMode;
	m_fStereoSeparation = CAppSettings::StereoSeparation/10000.f;

	CComboBox* pDriverCombo;
	pDriverCombo = (CComboBox*) GetDlgItem(IDC_COMBO_DRIVER);
	ASSERT( pDriverCombo );

	if(HC_QShow_Existence("/driver/opengl", "self"))
		pDriverCombo->AddString(_T("OpenGL"));
	if(HC_QShow_Existence("/driver/opengl2", "self"))
		pDriverCombo->AddString(_T("OpenGL 2"));
	if(HC_QShow_Existence("/driver/dx9", "self"))
		pDriverCombo->AddString(_T("DX9"));
	if(HC_QShow_Existence("/driver/msw", "self"))
		pDriverCombo->AddString(_T("Win GDI"));
	pDriverCombo->SetCurSel(0);

	UpdateData(FALSE);

	UpdateDriverDependentControls();
	UpdateTransparencySorting();
	UpdateBackplaneCullingCheck();
 	UpdateStereoMode();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 

void GeneralOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}


// Applies the general settings to the given view
void GeneralOptionsPage::ApplySettings()
{
     bool is_changed = false;
    
    // Get the active view to apply the new settings
    CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
    assert(pChild);
    CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
    
    CString new_HoopsDriver = HoopsDriverUi2Setting(m_csHoopsDriver);
    if( new_HoopsDriver != CAppSettings::HoopsDriver )
    {
		CAppSettings::HoopsDriver = new_HoopsDriver;
		is_changed = true;
    }
    
    bool new_bDriverForceSoftware = BOOL2bool(m_bForceSoftware);
    if( new_bDriverForceSoftware != CAppSettings::bDriverForceSoftware )
    {
		CAppSettings::bDriverForceSoftware = new_bDriverForceSoftware;
		is_changed = true;
    }
	CAppSettings::bDriverDisplayStats = BOOL2bool(m_bDisplayStats);
    
	bool new_StereoMode=BOOL2bool(m_bStereoMode);
	if(new_StereoMode != CAppSettings::StereoMode)
	{
		CAppSettings::StereoMode = new_StereoMode;
		is_changed = true;
	}
    
    CAppSettings::TransparencyStyle = m_csTransparencyStyle;
    CAppSettings::TransparencySorting = m_csTransparencySorting;
    CAppSettings::TransparencyDepthPeelingLayers = m_csTransparencyDepthPeelingLayers;
	CAppSettings::DoubleBuffer = BOOL2bool(m_bDoubleBuffer);
	CAppSettings::RenderMode = RenderModeCString2Enum(m_csRenderMode);
    CAppSettings::bDisplayAxisTriad = BOOL2bool(m_bDisplayAxisTriad);
	CAppSettings::StereoSeparation = m_fStereoSeparation*10000.f;
	CAppSettings::DepthWriting = BOOL2bool(m_bDepthWriting);

    if( pActiveView )
    {
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}
		HSelectionSet* pSelSet = pBaseView->GetSelection();
		assert(pSelSet);
 		// NOTE: We cannot apply the driver and software ogl settings, it's too late

		pBaseView->SetSuppressUpdate(true);

		// apply axis triad
		pBaseView->SetAxisMode( ((CAppSettings::bDisplayAxisTriad) ? AxisOn : AxisOff) );
		pActiveView->AdjustAxisWindow();
		pBaseView->SetHandedness(pBaseView->GetHandedness(), true );
		if (pBaseView->GetRenderMode() == HRenderHiddenLine || pBaseView->GetRenderMode() == HRenderHiddenLineFast)
			pBaseView->SetRenderMode(pBaseView->GetRenderMode());

		HC_Open_Segment_By_Key(pBaseView->GetViewKey());
		if (CAppSettings::bDriverDisplayStats)
			HC_Set_Driver_Options("display stats, display time stats, display memory stats");
		else
			HC_Set_Driver_Options("display stats = off, display time stats=off, display memory stats=off");
		HC_Close_Segment();

		pBaseView->SetSmoothTransition(CAppSettings::bSmoothTransition);
   		pActiveView->SetTransparency();

		pBaseView->SetSuppressUpdate(false);
		pBaseView->Update();
  	}    
}

void GeneralOptionsPage::OnSelchangeComboDriver() 
{
	UpdateDriverDependentControls();
}


void GeneralOptionsPage::OnSelchangeComboPolygonHandedness() 
{
	UpdateBackplaneCullingCheck();
}


void GeneralOptionsPage::UpdateTransparencySorting() 
{
	CComboBox* pSortingCombo;
	pSortingCombo = (CComboBox*) GetDlgItem(IDC_COMBO_TRANSPARENCY_SORTING);
	ASSERT( pSortingCombo );

	CString cur_sel;
	cur_sel.GetBuffer(pSortingCombo->GetLBTextLen(pSortingCombo->GetCurSel()));
	pSortingCombo->GetLBText(pSortingCombo->GetCurSel(), cur_sel);
	cur_sel.ReleaseBuffer();

	if( cur_sel == "depth peeling")
	{
 		GetDlgItem(IDC_LAYER_TEXT)->EnableWindow(1);
		GetDlgItem(IDC_COMBO_TRANSPARENCY_LAYERS)->EnableWindow(1);
		GetDlgItem(IDC_CHECK_DEPTH_WRITING)->EnableWindow(0);
	}
	else if(cur_sel == "none" || cur_sel == "z-sort fastest" || cur_sel == "z-sort nicest")
	{
 		GetDlgItem(IDC_LAYER_TEXT)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_TRANSPARENCY_LAYERS)->EnableWindow(0);
		GetDlgItem(IDC_CHECK_DEPTH_WRITING)->EnableWindow(1);
	}
	else
	{
		GetDlgItem(IDC_LAYER_TEXT)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_TRANSPARENCY_LAYERS)->EnableWindow(0);
		GetDlgItem(IDC_CHECK_DEPTH_WRITING)->EnableWindow(0);
	}
}

void GeneralOptionsPage::UpdateDriverDependentControls() 
{
	CComboBox* pDriverCombo;
	pDriverCombo = (CComboBox*) GetDlgItem(IDC_COMBO_DRIVER);
	ASSERT( pDriverCombo );

	CString cur_sel;
	cur_sel.GetBuffer(pDriverCombo->GetLBTextLen(pDriverCombo->GetCurSel()));
	pDriverCombo->GetLBText(pDriverCombo->GetCurSel(), cur_sel);
	cur_sel.ReleaseBuffer();

	if( cur_sel != "OpenGL 2" && cur_sel != "OpenGL" && cur_sel != "Direct3D" && cur_sel != "DX9")
	{
		((CButton*)GetDlgItem(IDC_CHECK_FORCE_SOFTWARE))->SetCheck(0);
		GetDlgItem(IDC_CHECK_FORCE_SOFTWARE)->EnableWindow(0);
	}
	else
		GetDlgItem(IDC_CHECK_FORCE_SOFTWARE)->EnableWindow(1);
}



void GeneralOptionsPage::UpdateBackplaneCullingCheck() 
{
	CComboBox* pPolygonHandednessCombo;
	pPolygonHandednessCombo = (CComboBox*) GetDlgItem(IDC_COMBO_POLYGON_HANDEDNESS);
	ASSERT( pPolygonHandednessCombo );

	CString cur_sel;
	cur_sel.GetBuffer(pPolygonHandednessCombo->GetLBTextLen(pPolygonHandednessCombo->GetCurSel()));
	pPolygonHandednessCombo->GetLBText(pPolygonHandednessCombo->GetCurSel(), cur_sel);
	cur_sel.ReleaseBuffer();

	if( cur_sel == "None")
	{
		((CButton*)GetDlgItem(IDC_CHECK_BACKPLANE_CULLING))->SetCheck(0);
		GetDlgItem(IDC_CHECK_BACKPLANE_CULLING)->EnableWindow(0);
	}
	else
		GetDlgItem(IDC_CHECK_BACKPLANE_CULLING)->EnableWindow(1);
}

void GeneralOptionsPage::OnButtonApply() 
{
	UpdateData(true);
 	ApplySettings();
}


static bool GetVistaCompositing()
{
	bool compositing = false;

#if (_MSC_VER > 1200)
	BOOL is_enabled = FALSE;
	typedef HRESULT (CALLBACK *SETDLLPROC)(BOOL *);
#ifdef UNICODE
#define STRINGTYPE LPCWSTR
#else
#define STRINGTYPE LPCSTR
#endif
	HINSTANCE kernel32 = LoadLibrary((STRINGTYPE)"dwmapi.dll");
	if(kernel32)
	{
		SETDLLPROC SetDllDir = (SETDLLPROC) GetProcAddress (kernel32, (LPCSTR)"DwmIsCompositionEnabled");

		if(SetDllDir)
		{
			SetDllDir(&is_enabled);
			if(is_enabled)
				compositing=true;
		}		
	}
#endif

	return compositing;
}

void GeneralOptionsPage::OnButtonReset() 
{
	m_csHoopsDriver = HoopsDriverSetting2Ui(CAppSettings::DefaultHoopsDriver);
	m_bForceSoftware = bool2BOOL(CAppSettings::DefaultbDriverForceSoftware);
	m_bDisplayStats = bool2BOOL(CAppSettings::DefaultbDriverDisplayStats);
	m_bDisplayAxisTriad = bool2BOOL(CAppSettings::DefaultbDisplayAxisTriad);
	//m_bBackplaneCulling = bool2BOOL(CAppSettings::DefaultbBackplaneCulling);
	//m_csCoordSysHandedness = (CAppSettings::DefaultCoordinateSystemHandedness == CoordSysRightHanded) ? "Right Handed" : "Left Handed";
	//m_csPolygonHandedness = PolygonHandednessEnum2CString(CAppSettings::DefaultPolygonHandedness);
	m_bDoubleBuffer = bool2BOOL(CAppSettings::DefaultDoubleBuffer && !GetVistaCompositing());
	m_csRenderMode = RenderModeEnum2CString(CAppSettings::DefaultRenderMode);
 	
	m_csTransparencySorting = CAppSettings::DefaultTransparencySorting;
	m_csTransparencyStyle = CAppSettings::DefaultTransparencyStyle;
	m_csTransparencyDepthPeelingLayers = CAppSettings::DefaultTransparencyDepthPeelingLayers;
	m_bDepthWriting = CAppSettings::DefaultDepthWriting;
	m_bStereoMode = CAppSettings::DefaultStereoMode;
	m_fStereoSeparation = CAppSettings::DefaultStereoSeparation/10000.f;

	UpdateData(FALSE);

 	UpdateDriverDependentControls();
	UpdateTransparencySorting();
	UpdateBackplaneCullingCheck();
	UpdateStereoMode();	
}


/////////////////////////////////////////////////////////////////////////////
// HSFOptionsPage dialog

HSFOptionsPage::HSFOptionsPage(CWnd* pParent)
	: HOptionsPage(HSFOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(HSFOptionsPage)
	m_csHsfVersion = "";
	m_bReadSimpleHsf = FALSE;
	m_bStoreTopolInfo = FALSE;
	m_bStoreCompressedVertices = FALSE;
	m_NumVertexBits = 0;
	m_bStoreCompressedNormals = FALSE;
	m_NumNormalBits = 0;
	m_bStoreCompressedParameters = FALSE;
	m_NumParameterBits = 0;
	m_bEmbedThumbnail = FALSE;
	m_bStoreLines = TRUE;
	m_bStoreDictionary = FALSE;
	m_bEnableInstancing = TRUE;
	m_bSaveLogFile = FALSE;
	m_bCompressConnectivity = FALSE;
 	m_ModelerVersionNo = 0;
	m_bEnableTristrips = TRUE;
	m_bEmbedMaterials = FALSE;
	//}}AFX_DATA_INIT
}

static int ConvertVersion(const char *text)
{

		char vtext[MVO_BUFFER_SIZE]; 
		int pos=0;
		for (unsigned int i=0;i<strlen(text);i++)
		{
			if (text[i] >= '0' && text[i] <= '9')
				vtext[pos++] = text[i];
		}
		vtext[pos] = 0;
		return (atoi(vtext));
}

void HSFOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HSFOptionsPage)
	DDX_CBString(pDX, IDC_COMBO_HSF_VERSION, m_csHsfVersion);
	DDX_Control(pDX, IDC_COMBO_MODELER_VERSION, m_ModelerVersionCombo);
	DDX_Check(pDX, IDD_READSIMPLEHSF, m_bReadSimpleHsf);
	DDX_Check(pDX, IDC_STORETOPOLINFO, m_bStoreTopolInfo);
	DDX_Check(pDX, IDC_STORECOMPRESSEDNORMALS, m_bStoreCompressedNormals);
	DDX_Check(pDX, IDC_STORECOMPRESSEDPARAMETERS, m_bStoreCompressedParameters);
	DDX_Check(pDX, IDC_STORECOMPRESSEDVERTICES, m_bStoreCompressedVertices);
	DDX_Check(pDX, IDC_EMBEDTHUMBNAIL, m_bEmbedThumbnail);
	DDX_Check(pDX, IDC_STORELINES, m_bStoreLines);
	DDX_Check(pDX, IDC_STOREDICTIONARY, m_bStoreDictionary);
	DDX_Check(pDX, IDC_ENABLEINSTANCING, m_bEnableInstancing);
	DDX_Check(pDX, IDC_SAVELOGFILE, m_bSaveLogFile);
	DDX_Check(pDX, IDC_USEADVANCEDCOMPRESSION, m_bCompressConnectivity);
	DDX_Text(pDX, IDC_EDIT_NUM_NORMAL_BITS, m_NumNormalBits);
	DDV_MinMaxUInt(pDX, m_NumNormalBits, 8, 72);
	DDX_Text(pDX, IDC_EDIT_NUM_PARAMETER_BITS, m_NumParameterBits);
	DDV_MinMaxUInt(pDX, m_NumParameterBits, 8, 72);
	DDX_Text(pDX, IDC_EDIT_NUM_VERTEX_BITS, m_NumVertexBits);
	DDV_MinMaxUInt(pDX, m_NumVertexBits, 8, 72);
	DDX_Check(pDX, IDC_ENABLE_TRISTRIPS, m_bEnableTristrips);	
	DDX_Check(pDX, IDC_EMBED_MATERIALS, m_bEmbedMaterials);
	//}}AFX_DATA_MAP
	for (int i = 0; i < m_ModelerVersionCombo.GetCount(); i++)
	{
		TCHAR text[MVO_BUFFER_SIZE];
		m_ModelerVersionCombo.GetLBText(i , text);
 		if (ConvertVersion(H_ASCII_TEXT(text)) == m_ModelerVersionNo)
		{
			m_ModelerVersionCombo.SetCurSel(i);	
			break;
		}
	}
}

BEGIN_MESSAGE_MAP(HSFOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(HSFOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonApply)
	ON_CBN_SELCHANGE(IDC_COMBO_MODELER_VERSION, OnSelchangeComboModelerVersion)
	ON_BN_CLICKED(IDC_STORETOPOLINFO, OnStoretopolinfo)
	ON_BN_CLICKED(IDC_STORECOMPRESSEDNORMALS, OnStoreCompressedNormals)
	ON_BN_CLICKED(IDC_STORECOMPRESSEDPARAMETERS, OnStoreCompressedParameters)
	ON_BN_CLICKED(IDC_STORECOMPRESSEDVERTICES, OnStoreCompressedVertices)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// converts the given hsf version no to string for use in combo box
// NOTE: 0 will be returned as "Latest"
static CString HsfVersionNo2CString(int version_no)
{
    switch (version_no)
    {
	case 0:
		return "Latest";
	case 1800:
		return "v18.00";
	case 1700:
		return "v17.00";
	case 1600:
		return "v16.00";
	case 1500:
		return "v15.00";
	case 1400:
		return "v14.00";
	case 1300:
		return "v13.00";
	case 1200:
		return "v12.00";
	case 1100:
		return "v11.00";
	case 1000:
		return "v10.00";
	case 900:
		return "v9.00";
	case 800:
		return "v8.00";
	case 710:
		return "v7.10";
	case 700:
		return "v7.00";
	case 630:
		return "v6.30";
	case 105:
		return "v1.05";
	}
    ASSERT(0);
	return "";
}
static int CString2HsfVersionNo(CString cs_version_no)
{
    if( cs_version_no == "Latest")
		return 0;
	else if ( cs_version_no ==  "v18.00")
		return 1800;
	else if ( cs_version_no ==  "v17.00")
		return 1700;
	else if ( cs_version_no ==  "v16.00")
		return 1600;
	else if ( cs_version_no ==  "v15.00")
		return 1500;
	else if ( cs_version_no ==  "v14.00")
		return 1400;
    else if ( cs_version_no ==  "v13.00")
		return 1300;
    else if ( cs_version_no ==  "v12.00")
		return 1200;
    else if ( cs_version_no ==  "v11.00")
		return 1100;
    else if ( cs_version_no ==  "v10.00")
		return 1000;
    else if ( cs_version_no ==  "v9.00")
		return 900;
    else if ( cs_version_no ==  "v8.00")
		return 800;
    else if ( cs_version_no ==  "v7.10")
		return 710;
    else if ( cs_version_no ==  "v7.00")
		return 700;
    else if( cs_version_no == "v6.30")
		return 630;
    else if( cs_version_no == "v1.05")
		return 105;
	else
	{
		ASSERT(0);
		return 0;
	}
}

void HSFOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}

BOOL HSFOptionsPage::OnInitDialog()
{
	HOptionsPage::OnInitDialog();

	m_csHsfVersion				= HsfVersionNo2CString(CAppSettings::HsfExportVersion);
	m_bReadSimpleHsf			= bool2BOOL(CAppSettings::bReadSimpleHsf);
	m_bStoreTopolInfo			= bool2BOOL(CAppSettings::bExportTopolInfo);
	m_bStoreCompressedNormals	= bool2BOOL(CAppSettings::bCompressNormals);
	m_NumNormalBits				= CAppSettings::NumNormalBits;
	m_bStoreCompressedParameters	= bool2BOOL(CAppSettings::bCompressParameters);
	m_NumParameterBits				= CAppSettings::NumParameterBits;
	m_bStoreCompressedVertices	= bool2BOOL(CAppSettings::bCompressVertices);
	m_NumVertexBits				= CAppSettings::NumVertexBits;
	m_bEmbedThumbnail			= bool2BOOL(CAppSettings::EmbedHSFThumbnail);
	m_bStoreLines				= bool2BOOL(CAppSettings::bExportLines);
	m_bStoreDictionary			= bool2BOOL(CAppSettings::bExportDictionary);
	m_bEnableInstancing			= bool2BOOL(CAppSettings::bEnableInstancing);
	m_bSaveLogFile				= bool2BOOL(CAppSettings::bSaveLogFile);
	m_bCompressConnectivity		= bool2BOOL(CAppSettings::bCompressConnectivity);
	m_ModelerVersionNo			= CAppSettings::ModelerExportFileVer;
	m_bEnableTristrips			= bool2BOOL(CAppSettings::EnableTristrips);
	m_bEmbedMaterials			= bool2BOOL(CAppSettings::EmbedMaterials);
 	if (m_bStoreTopolInfo)	
	{
		m_bStoreLines = true;;
		GetDlgItem(IDC_STORELINES)->EnableWindow(0);
  	}
	else
		GetDlgItem(IDC_STORELINES)->EnableWindow(1);


#ifdef ACIS
	GetDlgItem(IDC_STORETOPOLINFO)->ShowWindow(1);
	GetDlgItem(IDC_STORELINES)->ShowWindow(1);
#endif // ACIS


	// set the range of "num bits" spin controls
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_NUM_VERTEX_BITS))->SetRange(8, 72);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_NUM_NORMAL_BITS))->SetRange(8, 72);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_NUM_PARAMETER_BITS))->SetRange(8, 72);

	UpdateData(FALSE);

	OnStoreCompressedVertices();
	OnStoreCompressedNormals();
	OnStoreCompressedParameters();

	return TRUE;
}

void HSFOptionsPage::ApplySettings()
{
	// copy all the new settings 
	CAppSettings::HsfExportVersion		= CString2HsfVersionNo(m_csHsfVersion);
	CAppSettings::bReadSimpleHsf		= BOOL2bool(m_bReadSimpleHsf);
	CAppSettings::bExportTopolInfo		= BOOL2bool(m_bStoreTopolInfo);
	CAppSettings::bCompressNormals		= BOOL2bool(m_bStoreCompressedNormals);
	CAppSettings::NumNormalBits			= m_NumNormalBits;
	CAppSettings::bCompressParameters	= BOOL2bool(m_bStoreCompressedParameters);
	CAppSettings::NumParameterBits		= m_NumParameterBits;
	CAppSettings::bCompressVertices		= BOOL2bool(m_bStoreCompressedVertices);
	CAppSettings::NumVertexBits			= m_NumVertexBits;
	CAppSettings::EmbedHSFThumbnail		= BOOL2bool(m_bEmbedThumbnail);
	CAppSettings::bExportLines			= BOOL2bool(m_bStoreLines);
	CAppSettings::bExportDictionary		= BOOL2bool(m_bStoreDictionary);
	CAppSettings::bEnableInstancing		= BOOL2bool(m_bEnableInstancing);
	CAppSettings::bSaveLogFile			= BOOL2bool(m_bSaveLogFile);
	CAppSettings::bCompressConnectivity	= BOOL2bool(m_bCompressConnectivity);
	CAppSettings::ModelerExportFileVer	= m_ModelerVersionNo;
	CAppSettings::EnableTristrips		= BOOL2bool(m_bEnableTristrips);
	CAppSettings::EmbedMaterials		= BOOL2bool(m_bEmbedMaterials);

	// Get the active view to apply any applicable settings
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
	HBaseView * pBaseView = 0;
	if( pActiveView )
	{
	    pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}
		HStreamFileToolkit * tk = pBaseView->GetModel()->GetStreamFileTK();
		if( tk && (CAppSettings::HsfExportVersion > 0) )
			tk->SetTargetVersion(CAppSettings::HsfExportVersion);
	}

	UpdateData(TRUE); 
}

void HSFOptionsPage::OnSelchangeComboModelerVersion() 
{
	TCHAR text[MVO_BUFFER_SIZE];
	m_ModelerVersionCombo.GetLBText(m_ModelerVersionCombo.GetCurSel() , text);
	m_ModelerVersionNo=ConvertVersion(H_ASCII_TEXT(text));
}

void HSFOptionsPage::OnStoretopolinfo() 
{
 
	UpdateData(true);
 	if (m_bStoreTopolInfo)	
	{
		m_bStoreLines = true;;
		GetDlgItem(IDC_STORELINES)->EnableWindow(0);
  
	}
	else
		GetDlgItem(IDC_STORELINES)->EnableWindow(1);
	
	UpdateData(false);
}

void HSFOptionsPage::OnStoreCompressedVertices() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_NUM_VERTEX_BITS)->EnableWindow(BOOL2bool(m_bStoreCompressedVertices));
	GetDlgItem(IDC_HSF_BITSPV)->EnableWindow(BOOL2bool(m_bStoreCompressedVertices));
	GetDlgItem(IDC_SPIN_NUM_VERTEX_BITS)->EnableWindow(BOOL2bool(m_bStoreCompressedVertices));
	UpdateData(FALSE);
}

void HSFOptionsPage::OnStoreCompressedNormals() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_NUM_NORMAL_BITS)->EnableWindow(BOOL2bool(m_bStoreCompressedNormals));
	GetDlgItem(IDC_HSF_BITSPN)->EnableWindow(BOOL2bool(m_bStoreCompressedNormals));
	GetDlgItem(IDC_SPIN_NUM_NORMAL_BITS)->EnableWindow(BOOL2bool(m_bStoreCompressedNormals));
	UpdateData(FALSE);
}

void HSFOptionsPage::OnStoreCompressedParameters() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_NUM_PARAMETER_BITS)->EnableWindow(BOOL2bool(m_bStoreCompressedParameters));
	GetDlgItem(IDC_HSF_BITSPP)->EnableWindow(BOOL2bool(m_bStoreCompressedParameters));
	GetDlgItem(IDC_SPIN_NUM_PARAMETER_BITS)->EnableWindow(BOOL2bool(m_bStoreCompressedParameters));
	UpdateData(FALSE);
}


void HSFOptionsPage::OnButtonApply()
{
	ApplySettings();
}

void HSFOptionsPage::OnButtonReset()
{
	m_csHsfVersion				= HsfVersionNo2CString(CAppSettings::DefaultHsfExportVersion);
	m_bReadSimpleHsf			= bool2BOOL(CAppSettings::DefaultbReadSimpleHsf);
	m_bStoreTopolInfo			= bool2BOOL(CAppSettings::DefaultbExportTopolInfo);
	m_bStoreCompressedNormals	= bool2BOOL(CAppSettings::DefaultbCompressNormals);
	m_NumNormalBits				= CAppSettings::DefaultNumNormalBits;
	m_bStoreCompressedParameters	= bool2BOOL(CAppSettings::DefaultbCompressParameters);
	m_NumParameterBits			= CAppSettings::DefaultNumParameterBits;
	m_bStoreCompressedVertices	= bool2BOOL(CAppSettings::DefaultbCompressVertices);
	m_NumVertexBits				= CAppSettings::DefaultNumVertexBits;
	m_bEmbedThumbnail			= bool2BOOL(CAppSettings::DefaultEmbedHSFThumbnail);
	m_bStoreLines				= bool2BOOL(CAppSettings::DefaultbExportLines);
	m_bStoreDictionary			= bool2BOOL(CAppSettings::DefaultbExportDictionary);
	m_bEnableInstancing			= bool2BOOL(CAppSettings::DefaultbEnableInstancing);
	m_bSaveLogFile				= bool2BOOL(CAppSettings::DefaultbSaveLogFile);
	m_bCompressConnectivity		= bool2BOOL(CAppSettings::DefaultbCompressConnectivity);
	m_ModelerVersionNo			= CAppSettings::DefaultModelerExportFileVer;
	m_bEnableTristrips			= bool2BOOL(CAppSettings::DefaultEnableTristrips);
	m_bEmbedMaterials			= bool2BOOL(CAppSettings::DefaultEmbedMaterials);

 	if (m_bStoreTopolInfo)	
	{
		m_bStoreLines = true;;
		GetDlgItem(IDC_STORELINES)->EnableWindow(0);
  	}
	else
		GetDlgItem(IDC_STORELINES)->EnableWindow(1);

	UpdateData(FALSE); 

	OnStoreCompressedVertices();
	OnStoreCompressedNormals();
	OnStoreCompressedParameters();
}




/////////////////////////////////////////////////////////////////////////////
// FileOptionsPage dialog


FileOptionsPage::FileOptionsPage(CWnd* pParent /*=NULL*/)
	: HOptionsPage(FileOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(FileOptionsPage)
	m_csPartsDir = _T("");
	m_csDWGTextureDir = _T("");
	m_csMaterialLibraryDir = _T("");
	m_bFlushOnLoad = FALSE;
	m_bRestoreAnnotations = FALSE;
	m_bPrcFaceEdgeVertexSelectability = FALSE;
	m_bImportDWGviaBstream = FALSE;
	m_DWGDeviation = 10.0;
	m_bHsfStreaming = true;
	m_bImportAllLayouts = true;

	//For DGN
	m_bIgnoreInvisibleLayer = FALSE;
	m_bIgnoreInvisibleEntities = FALSE;
	m_DGNFactorForCone = 10.0;
	m_DGNFactorForSmartSolids = 45.0;

	m_bLoadPVOFiles = TRUE;

	//}}AFX_DATA_INIT
}
void FileOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FileOptionsPage)
	DDX_Text(pDX, IDC_EDIT_PARTS_DIR, m_csPartsDir);
	DDX_Text(pDX, IDC_EDIT_DWG_TEXTURE_DIR, m_csDWGTextureDir);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_LIBRARY_DIR, m_csMaterialLibraryDir);
	DDX_Check(pDX, IDC_FLUSH_MODEL_SEGMENT_ON_LOAD, m_bFlushOnLoad);
	DDX_Check(pDX, IDC_RESTORE_ANNOTATIONS, m_bRestoreAnnotations);
	DDX_Check(pDX, IDC_PRC_FACE_EDGE_VERTEX_SELECTABILITY, m_bPrcFaceEdgeVertexSelectability);
    DDX_Check(pDX, IDC_CHECK_DWG_IMPORT_VIA_BSTREAM, m_bImportDWGviaBstream);
	DDX_Check(pDX, IDC_CHECK_DWG_IMPORT_XDATA, m_bImportDWGXData);
	DDX_Text(pDX, IDC_EDIT_DWG_FACET_CURVE_DEVIATION, m_DWGDeviation);
	DDX_Check(pDX, IDC_HSF_STREAMING, m_bHsfStreaming);
	DDX_Check(pDX, IDC_LOAD_PVO_FILES, m_bLoadPVOFiles);


//I have added following ifndefs to disable following GUI controls which are not supported for acis, parasolid and
//granite partviewer. Earlier programmers chose to add these redundant control on file dialog box and make their
// visibility off instead which also avoids the crash//Mustafa Bohari 15-Jun-09

#ifndef ACIS 
#ifndef PARASOLID 
#ifndef GRANITE

	DDX_Check(pDX, IDC_ALL_LAYOUTS, m_bImportAllLayouts);

	//For DGN
    DDX_Check(pDX, IDC_DGN_IGNORE_INVISIBLE_ENTITY, m_bIgnoreInvisibleEntities );
	DDX_Text(pDX, IDC_EDIT_DGN_CONE_FACTOR, m_DGNFactorForCone );
	DDX_Text(pDX, IDC_EDIT_DGN_SMART_SOLID_FACTOR, m_DGNFactorForSmartSolids );

#endif
#endif
#endif




	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FileOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(FileOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_PARTDIR, OnButtonPartsDir)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_DWG_TEXTUREDIR, OnButtonDWGTextureDir)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_MATERIAL_LIBRARY_DIR, OnButtonMaterialLibraryDir)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonApply)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// FileOptionsPage message handlers
BOOL FileOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();

	// initialize all the data
	m_csPartsDir						= CAppSettings::PartsDirectory;
	m_csDWGTextureDir					= CAppSettings::DWGTextureDirectory;
	m_csMaterialLibraryDir				= CAppSettings::MaterialLibraryDirectory;
	m_bFlushOnLoad						= bool2BOOL(CAppSettings::bFlushOnLoad);
	m_bRestoreAnnotations				= bool2BOOL(CAppSettings::bRestoreAnnotations);
	m_bPrcFaceEdgeVertexSelectability	= bool2BOOL(CAppSettings::bPrcFaceEdgeVertexSelectability);
    m_bImportDWGviaBstream				= bool2BOOL(CAppSettings::bImportDWGviaBstream);
	m_bImportDWGXData					= bool2BOOL(CAppSettings::bImportDWGXData);
	m_DWGDeviation						= atof(H_ASCII_TEXT(CAppSettings::DWGDeviation));
	m_bHsfStreaming						= bool2BOOL(CAppSettings::HsfStreaming);
	m_bImportAllLayouts					= bool2BOOL(CAppSettings::bImportAllLayouts);
	//For DGN
    m_bIgnoreInvisibleEntities			= bool2BOOL(CAppSettings::bIgnoreInvisibleEntities);
	m_DGNFactorForCone					= atof(H_ASCII_TEXT(CAppSettings::DGNFactorForCone));
	m_DGNFactorForSmartSolids			= atof(H_ASCII_TEXT(CAppSettings::DGNFactorForSmartSolids ));
	m_bLoadPVOFiles						= bool2BOOL(CAppSettings::LoadPVOFiles);	


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void FileOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}


void FileOptionsPage::ApplySettings()
{
	CAppSettings::bFlushOnLoad						= BOOL2bool(m_bFlushOnLoad);
	CAppSettings::bRestoreAnnotations				= BOOL2bool(m_bRestoreAnnotations);
	CAppSettings::bPrcFaceEdgeVertexSelectability	= BOOL2bool(m_bPrcFaceEdgeVertexSelectability);
    CAppSettings::bImportDWGviaBstream				= BOOL2bool(m_bImportDWGviaBstream);
	CAppSettings::bImportDWGXData					= BOOL2bool(m_bImportDWGXData);
	CAppSettings::DWGTextureDirectory				= m_csDWGTextureDir;
	if (m_csMaterialLibraryDir != CAppSettings::MaterialLibraryDirectory) {
		CAppSettings::MaterialLibraryDirectory = m_csMaterialLibraryDir;
		delete HDB::GetMaterialLibrary();
		HDB::SetMaterialLibrary(NULL);
	}
	CAppSettings::DWGDeviation.Format(_T("%.5f"),  m_DWGDeviation );
	CAppSettings::HsfStreaming						= BOOL2bool(m_bHsfStreaming);
	CAppSettings::bImportAllLayouts					= BOOL2bool(m_bImportAllLayouts);
	CAppSettings::LoadPVOFiles						= BOOL2bool(m_bLoadPVOFiles);

	//For DGN
    CAppSettings::bIgnoreInvisibleEntities				= BOOL2bool(m_bIgnoreInvisibleEntities);
	CAppSettings::DGNFactorForCone.Format(_T("%.5f"),  m_DGNFactorForCone );
	CAppSettings::DGNFactorForSmartSolids.Format(_T("%.5f"),  m_DGNFactorForSmartSolids );


	

	if( CAppSettings::PartsDirectory.CompareNoCase(m_csPartsDir) != 0 )
	{
		CAppSettings::PartsDirectory = m_csPartsDir;
		// set this as current directory, so that our File dialogs work correctly
		SetCurrentDirectory( CAppSettings::PartsDirectory );
	}


	// apply settings which are application wide
	// NOTE: most of the settings here are automatically applied since they are
	// directly used while exporting the files

 
}

void FileOptionsPage::OnButtonPartsDir()
{
	CString csDlgCaption(_T("Choose the location of Part Files..."));
	CString csDlgMsg(_T(""));
	CPathDialog dir_dlg(csDlgCaption, csDlgMsg, m_csPartsDir);
	if (dir_dlg.DoModal()==IDOK)
		m_csPartsDir = dir_dlg.GetPathName();
	UpdateData(FALSE);
}

void FileOptionsPage::OnButtonDWGTextureDir()
{
	CString csDlgCaption(_T("Choose the location of DWG Texture Files..."));
	CString csDlgMsg(_T(""));
	CPathDialog dir_dlg(csDlgCaption, csDlgMsg, m_csDWGTextureDir);
	if (dir_dlg.DoModal()==IDOK)
		m_csDWGTextureDir = dir_dlg.GetPathName();
	UpdateData(FALSE);
}

void FileOptionsPage::OnButtonMaterialLibraryDir()
{
	CString csDlgCaption(_T("Choose the location of Material Library Files..."));
	CString csDlgMsg(_T(""));
	CPathDialog dir_dlg(csDlgCaption, csDlgMsg, m_csMaterialLibraryDir);
	if (dir_dlg.DoModal()==IDOK)
		m_csMaterialLibraryDir = dir_dlg.GetPathName();
	UpdateData(FALSE);
}


void FileOptionsPage::OnButtonApply() 
{
	UpdateData(true); 
	ApplySettings();
}


void FileOptionsPage::OnButtonReset() 
{
	// reset all the data
	m_csPartsDir							= CAppSettings::DefaultPartsDirectory;
	m_csDWGTextureDir						= CAppSettings::DefaultDWGTextureDirectory;
	m_csMaterialLibraryDir					= CAppSettings::DefaultMaterialLibraryDirectory;
	m_bFlushOnLoad							= bool2BOOL(CAppSettings::DefaultbFlushOnLoad);
	m_bRestoreAnnotations					= bool2BOOL(CAppSettings::DefaultbRestoreAnnotations);
	m_bPrcFaceEdgeVertexSelectability		= bool2BOOL(CAppSettings::DefaultbPrcFaceEdgeVertexSelectability);
	m_bImportDWGviaBstream					= bool2BOOL(CAppSettings::DefaultbImportDWGviaBstream);
	m_bImportDWGXData						= bool2BOOL(CAppSettings::DefaultbImportDWGXData);
	m_bHsfStreaming							= bool2BOOL(CAppSettings::DefaultHsfStreaming);
	m_bImportAllLayouts						= bool2BOOL(CAppSettings::DefaultbImportAllLayouts);
	sscanf(H_ASCII_TEXT(CAppSettings::DefaultDWGDeviation), "%lf", &m_DWGDeviation);
	m_bLoadPVOFiles							= bool2BOOL(CAppSettings::DefaultLoadPVOFiles);

	
	//For Dgn
	m_bIgnoreInvisibleEntities				= bool2BOOL(CAppSettings::DefaultbIgnoreInvisibleEntities);
	sscanf(H_ASCII_TEXT(CAppSettings::DefaultDGNFactorForCone ), "%lf", &m_DGNFactorForCone);
	sscanf(H_ASCII_TEXT(CAppSettings::DefaultDGNFactorForSmartSolids ), "%lf", &m_DGNFactorForSmartSolids);

	
	
	

	UpdateData(FALSE);
	
}






/////////////////////////////////////////////////////////////////////////////
// InteractionOptionsPage property page

 
InteractionOptionsPage::InteractionOptionsPage(CWnd* pParent /*=NULL*/)
	: HOptionsPage(InteractionOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(InteractionOptionsPage)
	m_bWalkUseKeyboard = FALSE;
	m_bWalkCollision = FALSE;
	m_bWalkSnapToFloor = FALSE;
	m_WalkAvatarHeight = 0.0f;
	m_bWalkAutomaticHeight = FALSE;
	m_WalkStepHeightUp = 0;
	m_WalkStepHeightDown = 0;
	m_bShowEveryTick = FALSE;
	m_bShowCollisions = FALSE;
	m_bUpdateCamera = FALSE;
	m_bJumpToKeyframe = FALSE;
	m_bDisableCFR = TRUE;
 	m_bTimerBasedUpdate = TRUE;
 	m_bUpdateCutGeometry = FALSE;
	m_bSpriting = FALSE;
	m_bUpdateShadows = FALSE;
	//}}AFX_DATA_INIT
}

InteractionOptionsPage::~InteractionOptionsPage()
{
}


void InteractionOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InteractionOptionsPage)
	DDX_Check(pDX, IDC_CHECK_WALK_USE_KEYBOARD, m_bWalkUseKeyboard);
	DDX_Check(pDX, IDC_CHECK_WALK_COLLISION, m_bWalkCollision);
	DDX_Check(pDX, IDC_CHECK_WALK_SNAP_TO_FLOOR, m_bWalkSnapToFloor);
	DDX_Text(pDX, IDC_EDIT_WALK_AVATAR_HEIGHT, m_WalkAvatarHeight);
	DDX_Check(pDX, IDC_WALK_AUTOMATIC_HEIGHT, m_bWalkAutomaticHeight);
	DDX_Text(pDX, IDC_EDIT_WALK_AVATAR_STEP_HEIGHT_UP, m_WalkStepHeightUp);
	DDX_Text(pDX, IDC_EDIT_WALK_AVATAR_STEP_HEIGHT_DOWN, m_WalkStepHeightDown);
	DDX_Check(pDX, IDC_CHECK_SHOW_EVERY_TICK, m_bShowEveryTick);
	DDX_Check(pDX, IDC_CHECK_SHOW_COLLISIONS, m_bShowCollisions);
	DDX_Check(pDX, IDC_CHECK_UPDATE_CAMERA, m_bUpdateCamera);
	DDX_Check(pDX, IDC_CHECK_JUMP_TO_KEYFRAME, m_bJumpToKeyframe);
 	DDX_Check(pDX, IDC_CHECK_DISABLE_CFR, m_bDisableCFR);
 	DDX_Check(pDX, IDC_CHECK_TIMER_BASED_UPDATE, m_bTimerBasedUpdate);
	DDX_Check(pDX, IDC_CHECK_UPDATE_CUT_GEOMETRY, m_bUpdateCutGeometry);
	DDX_Check(pDX, IDC_CHECK_USE_3D_SPRITING, m_bSpriting);
	DDX_Check(pDX, IDC_CHECK_UPDATE_SHADOWS, m_bUpdateShadows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InteractionOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(InteractionOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_WALK_AUTOMATIC_HEIGHT, OnWalkAutomaticHeight)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InteractionOptionsPage message handlers
void InteractionOptionsPage::ApplySettings()
{
	CAppSettings::bWalkUseKeyboard = BOOL2bool(m_bWalkUseKeyboard);	
	CAppSettings::bWalkCollision = BOOL2bool(m_bWalkCollision);	
	CAppSettings::bWalkSnapToFloor = BOOL2bool(m_bWalkSnapToFloor);	
	CAppSettings::WalkAvatarHeight = (int) (m_WalkAvatarHeight*10000);
	CAppSettings::WalkStepHeightUp = m_WalkStepHeightUp;
	CAppSettings::WalkStepHeightDown = m_WalkStepHeightDown;
	CAppSettings::bWalkAutomaticHeight = BOOL2bool(m_bWalkAutomaticHeight);	

    CAppSettings::TimerBasedUpdate = BOOL2bool(m_bTimerBasedUpdate);
    CAppSettings::ShowEveryTick = BOOL2bool(m_bShowEveryTick);
    CAppSettings::ShowCollisions = BOOL2bool(m_bShowCollisions);
    CAppSettings::JumpToKeyframe = BOOL2bool(m_bJumpToKeyframe);
    CAppSettings::DisableCFR = BOOL2bool(m_bDisableCFR);
    CAppSettings::UpdateCamera = BOOL2bool(m_bUpdateCamera);
 
	CAppSettings::Spriting = BOOL2bool(m_bSpriting);
	CAppSettings::UpdateCutGeometry = BOOL2bool(m_bUpdateCutGeometry);
	CAppSettings::UpdateShadows = BOOL2bool(m_bUpdateShadows);

	// Get the active view to apply the new settings
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
	if (pActiveView)
	{
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}
		HSelectionSet* pSelSet = pBaseView->GetSelection();
		assert(pSelSet);
		HBaseOperator * op = pActiveView->GetSolidView()->GetOperator();

		pBaseView->SetSuppressUpdate(true);

		if(CAppSettings::UseFramerate && CAppSettings::CurrentFramerateMode==FramerateFixed)
			pBaseView->SetViewUpdateMode(Deferred);
		else
			pBaseView->SetViewUpdateMode(CAppSettings::TimerBasedUpdate ? Continuous : OnDemand);

		if (op && strcmp(op->GetName(), "HOpCameraWalk") == 0)
			pActiveView->SetWalkOperator();
	    
		pBaseView->GetModel()->GetBhvBehaviorManager()->SetRenderEveryTick(CAppSettings::ShowEveryTick);
		((HSolidView *)pBaseView)->SetShowCollisions(CAppSettings::ShowCollisions);
		pBaseView->GetModel()->GetBhvBehaviorManager()->SetUpdateCamera(CAppSettings::UpdateCamera);
		pBaseView->SetSpritingMode(CAppSettings::Spriting);
		pBaseView->SetAllowInteractiveShadows(CAppSettings::UpdateShadows);
		pBaseView->SetAllowInteractiveCutGeometry(CAppSettings::UpdateCutGeometry);
		
		pBaseView->SetSuppressUpdate(false);
		pBaseView->Update();
		
	}

}


void InteractionOptionsPage::OnOK()
{
	
	ApplySettings();
	HOptionsPage::OnOK();
}

void InteractionOptionsPage::OnButtonApply() 
{
	UpdateData(true);
	ApplySettings();
	
}


BOOL InteractionOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();
	m_bWalkUseKeyboard = bool2BOOL(CAppSettings::bWalkUseKeyboard);
	m_bWalkCollision = bool2BOOL(CAppSettings::bWalkCollision);
	m_bWalkSnapToFloor = bool2BOOL(CAppSettings::bWalkSnapToFloor);
	m_WalkAvatarHeight = CAppSettings::WalkAvatarHeight/10000.0f;
	m_bWalkAutomaticHeight = bool2BOOL(CAppSettings::bWalkAutomaticHeight);
	m_WalkStepHeightUp = CAppSettings::WalkStepHeightUp;
	m_WalkStepHeightDown = CAppSettings::WalkStepHeightDown;

	m_bTimerBasedUpdate = bool2BOOL(CAppSettings::TimerBasedUpdate);
 	m_bShowEveryTick = CAppSettings::ShowEveryTick;
	m_bShowCollisions = CAppSettings::ShowCollisions;
	m_bJumpToKeyframe = CAppSettings::JumpToKeyframe;
	m_bDisableCFR = CAppSettings::DisableCFR;
	m_bUpdateCamera = CAppSettings::UpdateCamera;
	m_bSpriting = bool2BOOL(CAppSettings::Spriting);
 	m_bUpdateCutGeometry = bool2BOOL(CAppSettings::UpdateCutGeometry);
	m_bUpdateShadows = bool2BOOL(CAppSettings::UpdateShadows);

	UpdateAutomaticHeight();
	UpdateData(FALSE);
	UpdateAvatarHeight();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void InteractionOptionsPage::OnWalkAutomaticHeight() 
{
	UpdateData(true);
	UpdateAutomaticHeight(); 
	UpdateData(false);
	UpdateAvatarHeight();
 	// TODO: Add your control notification handler code here	
}


void InteractionOptionsPage::UpdateAutomaticHeight()
{
	if (m_bWalkAutomaticHeight)
	{
		CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
		assert(pChild);
		CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
		if (pActiveView && pActiveView->GetSolidView())
		{
			float ext = HOpCameraWalk::CalculateExtents(pActiveView->GetSolidView());
			m_WalkAvatarHeight = ext/60.0f;
		}

	}
	
}

void InteractionOptionsPage::UpdateAvatarHeight()
{
	GetDlgItem(IDC_EDIT_WALK_AVATAR_HEIGHT)->EnableWindow(!BOOL2bool(m_bWalkAutomaticHeight));

}

void InteractionOptionsPage::OnButtonReset() 
{
	m_bWalkUseKeyboard = bool2BOOL(CAppSettings::DefaultbWalkUseKeyboard);
	m_bWalkCollision = bool2BOOL(CAppSettings::DefaultbWalkCollision);
	m_bWalkSnapToFloor = bool2BOOL(CAppSettings::DefaultbWalkSnapToFloor);
	m_WalkAvatarHeight = CAppSettings::DefaultWalkAvatarHeight/10000.0f;
	m_bWalkAutomaticHeight = bool2BOOL(CAppSettings::DefaultbWalkAutomaticHeight);
	m_WalkStepHeightUp = CAppSettings::DefaultWalkStepHeightUp;
	m_WalkStepHeightDown = CAppSettings::DefaultWalkStepHeightDown;
	m_bTimerBasedUpdate = bool2BOOL(CAppSettings::DefaultTimerBasedUpdate);
	m_bShowEveryTick = bool2BOOL(CAppSettings::DefaultShowEveryTick);
	m_bShowCollisions = bool2BOOL(CAppSettings::DefaultShowCollisions);
	m_bJumpToKeyframe = bool2BOOL(CAppSettings::DefaultJumpToKeyframe);
	m_bDisableCFR = bool2BOOL(CAppSettings::DefaultDisableCFR);
	m_bUpdateCamera = bool2BOOL(CAppSettings::DefaultUpdateCamera);
 	m_bUpdateCutGeometry = bool2BOOL(CAppSettings::DefaultUpdateCutGeometry);
	m_bSpriting = bool2BOOL(CAppSettings::DefaultSpriting);
	m_bUpdateShadows = bool2BOOL(CAppSettings::DefaultUpdateShadows);

	UpdateAutomaticHeight();
 
	UpdateData(FALSE);
	UpdateAvatarHeight();
	
	// TODO: Add extra initialization here
	
}



/////////////////////////////////////////////////////////////////////////////
// SelectionOptionsPage dialog


SelectionOptionsPage::SelectionOptionsPage(CWnd* pParent /*=NULL*/)
	: HOptionsPage(SelectionOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectionOptionsPage)
 	m_bGrayScaleSelection = FALSE;
 	m_bDisplaceSelection = FALSE;
  	m_nSelTransparency = 0;
	m_bVisibilitySelection = TRUE;
  	m_bDynamicHighlighting = FALSE;
	m_bDetailSelection = FALSE;
	m_bUseSelectBox = TRUE;
	m_HighlightMode = HighlightDefault;
	m_bRelatedSelectionLimit = TRUE;
	m_nRelatedSelectionLimit = 0;
	m_csRefSelType = _T("Spriting");
	m_csQuickMovesType = _T("Default");
	m_fTransparencyLevel = 0.9f;
 	//}}AFX_DATA_INIT
}


void SelectionOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectionOptionsPage)
 	DDX_Control(pDX, IDC_BUTTON_COLOR_SEL_POLYGONS, m_clrbtnSelPolygons);
	DDX_Control(pDX, IDC_BUTTON_COLOR_SEL_MARKERS, m_clrbtnSelMarkers);
	DDX_Control(pDX, IDC_BUTTON_COLOR_SEL_LINES, m_clrbtnSelLines);
	DDX_Text(pDX, IDC_EDIT_COLOR_SEL_TRANSPARENCY, m_nSelTransparency);
	DDV_MinMaxInt(pDX, m_nSelTransparency, 0, 100);
	DDX_Check(pDX, IDC_CHECK_VISIBILITY_SELECTION, m_bVisibilitySelection);
  	DDX_Check(pDX, IDC_CHECK_DYNAMIC_HIGHLIGHTING, m_bDynamicHighlighting);
	DDX_Check(pDX, IDC_CHECK_DETAIL_SELECTION, m_bDetailSelection);
	DDX_Check(pDX, IDC_CHECK_GRAYSCALE_SELECTION, m_bGrayScaleSelection);
	DDX_Check(pDX, IDC_CHECK_DISPLACE_SELECTION, m_bDisplaceSelection);
	DDX_Check(pDX, IDC_TRANSPARENT_SELECT_BOX, m_bUseSelectBox);
	DDX_Check(pDX, IDC_CHECK_RELATED_SELECTION, m_bRelatedSelectionLimit);
	DDX_Text(pDX, IDC_TEXT_RELATED_SELECTION, m_nRelatedSelectionLimit);
	DDX_CBString(pDX, IDC_REF_SEL_TYPE_COMBO, m_csRefSelType);
	DDX_CBString(pDX, IDC_QUICK_MOVES_TYPE_COMBO, m_csQuickMovesType);
	DDX_Text(pDX, IDC_TEXT_TRANSPARENCY_LEVEL, m_fTransparencyLevel);
	DDV_MinMaxFloat(pDX, m_fTransparencyLevel, 0.0f, 1.0f);
  	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectionOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(SelectionOptionsPage)
 	ON_BN_CLICKED(IDC_CHECK_GRAYSCALE_SELECTION, OnCheckGrayScaleSelection)
 	ON_BN_CLICKED(IDC_CHECK_GRAYSCALE_SELECTION, OnCheckDisplaceSelection)
  	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_CHECK_RELATED_SELECTION, OnRelatedSelection)
	ON_BN_CLICKED(IDC_NO_QUICKMOVES_HIGHLIGHTING, OnNoQuickmovesHighlighting)
	ON_BN_CLICKED(IDC_QUICKMOVES_HIGHLIGHTING, OnReferenceHighlighting)
	ON_BN_CLICKED(IDC_INVERSE_TRANSPARENCY, OnInverseTransparency)
	ON_BN_CLICKED(IDC_COLORED_INVERSE_TRANSPARENCY, OnColoredInverseTransparency)
 	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectionOptionsPage message handlers
BOOL SelectionOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();
 
	m_clrbtnSelPolygons.currentcolor = CAppSettings::PolygonSelectionColor;
	m_clrbtnSelLines.currentcolor = CAppSettings::LineSelectionColor;
	m_clrbtnSelMarkers.currentcolor = CAppSettings::MarkerSelectionColor;
	m_nSelTransparency = CAppSettings::SelectionColorTransparency;
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_COLOR_SEL_TRANSPARENCY))->SetRange(0, 100);

	m_bVisibilitySelection = bool2BOOL(CAppSettings::VisibilitySelection);
	m_bDynamicHighlighting = bool2BOOL(CAppSettings::DynamicHighlighting);
	m_bDetailSelection = bool2BOOL(CAppSettings::DetailSelection);

 	m_bGrayScaleSelection = bool2BOOL(CAppSettings::bGrayScaleSelection);
 	m_bDisplaceSelection = bool2BOOL(CAppSettings::bDisplaceSelection);
	m_bUseSelectBox = bool2BOOL(CAppSettings::bUseSelectBox);
	m_HighlightMode = CAppSettings::HighlightMode;
	m_fTransparencyLevel = CAppSettings::TransparencyLevel;

	m_bRelatedSelectionLimit = bool2BOOL(CAppSettings::RelatedSelectionLimit!=NO_RELATED_SELECTION_LIMIT);
	m_nRelatedSelectionLimit = m_bRelatedSelectionLimit ? CAppSettings::RelatedSelectionLimit : 0;

	m_csQuickMovesType = CAppSettings::csQuickMovesType;
	m_csRefSelType = CAppSettings::csRefSelType;

 	UpdateData(FALSE);

 	UpdateSelectionChecks();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SelectionOptionsPage::OnNoQuickmovesHighlighting()
{
	m_HighlightMode = HighlightDefault;
	UpdateSelectionChecks();
}

void SelectionOptionsPage::OnReferenceHighlighting()
{
	m_HighlightMode = HighlightQuickmoves;
	UpdateSelectionChecks();
}

void SelectionOptionsPage::OnInverseTransparency()
{
	m_HighlightMode = InverseTransparency;
	UpdateSelectionChecks();
}

void SelectionOptionsPage::OnColoredInverseTransparency()
{
	m_HighlightMode = ColoredInverseTransparency;
	UpdateSelectionChecks();
}

void SelectionOptionsPage::OnOK()
{
	
	ApplySettings();
	HOptionsPage::OnOK();
}

// Applies the Selection related application settings to the given view
void SelectionOptionsPage::ApplySettings()
{
	CAppSettings::PolygonSelectionColor = m_clrbtnSelPolygons.currentcolor;
	CAppSettings::LineSelectionColor = m_clrbtnSelLines.currentcolor;
	CAppSettings::MarkerSelectionColor = m_clrbtnSelMarkers.currentcolor;
	CAppSettings::SelectionColorTransparency = m_nSelTransparency;
    CAppSettings::VisibilitySelection = BOOL2bool(m_bVisibilitySelection);
    CAppSettings::DynamicHighlighting = BOOL2bool(m_bDynamicHighlighting);
	CAppSettings::DetailSelection = BOOL2bool(m_bDetailSelection);

  	CAppSettings::bGrayScaleSelection = BOOL2bool(m_bGrayScaleSelection);
  	CAppSettings::bDisplaceSelection = BOOL2bool(m_bDisplaceSelection);
	CAppSettings::bUseSelectBox = BOOL2bool(m_bUseSelectBox);
	CAppSettings::HighlightMode = m_HighlightMode;
	CAppSettings::TransparencyLevel = m_fTransparencyLevel;
	CAppSettings::RelatedSelectionLimit = m_bRelatedSelectionLimit ? 
											m_nRelatedSelectionLimit : NO_RELATED_SELECTION_LIMIT;
	
	CAppSettings::csRefSelType = m_csRefSelType;
	CAppSettings::csQuickMovesType = m_csQuickMovesType;
 
	// Apply these settings to the currently active view
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
	if( pActiveView )
	{
	    
	    HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}
	    HSelectionSet* pSelSet = pBaseView->GetSelection();
	    assert(pSelSet);
		
		pBaseView->SetSuppressUpdate(true);

		HSelectionHighlightMode old_sel_mode = pSelSet->GetHighlightMode();
		HSelectionHighlightMode new_sel_mode = CAppSettings::HighlightMode;
	    
		//these need to be done before the regular selection set
		pBaseView->GetHighlightSelection()->SetGrayScale(CAppSettings::bGrayScaleSelection);
		pBaseView->GetHighlightSelection()->SetAllowDisplacement(CAppSettings::bDisplaceSelection);
		pBaseView->SetDynamicHighlighting(CAppSettings::DynamicHighlighting);
		

		char qm_pref[MVO_BUFFER_SIZE];
		sprintf(qm_pref, "quick moves preference = %s", H_ASCII_TEXT(CAppSettings::csQuickMovesType));
		HC_Open_Segment_By_Key(pBaseView->GetViewKey());
			HC_Set_Driver_Options(qm_pref);
		HC_Close_Segment();
 	    
	    // apply the selection color
	    int sel_alpha = (int)(CAppSettings::SelectionColorTransparency*2.56f);		// settings is a %, scale it to 256
	    HPixelRGBA sel_col;
	    sel_col.Set(GetRValue(CAppSettings::PolygonSelectionColor), GetGValue(CAppSettings::PolygonSelectionColor), GetBValue(CAppSettings::PolygonSelectionColor), sel_alpha);
	    pSelSet->SetSelectionFaceColor(sel_col);
	    sel_col.Set(GetRValue(CAppSettings::LineSelectionColor), GetGValue(CAppSettings::LineSelectionColor), GetBValue(CAppSettings::LineSelectionColor), sel_alpha);
	    pSelSet->SetSelectionEdgeColor(sel_col);
	    sel_col.Set(GetRValue(CAppSettings::MarkerSelectionColor), GetGValue(CAppSettings::MarkerSelectionColor), GetBValue(CAppSettings::MarkerSelectionColor), sel_alpha);
	    pSelSet->SetSelectionMarkerColor(sel_col);
		pSelSet->SetGrayScale(CAppSettings::bGrayScaleSelection);
  		pSelSet->SetAllowDisplacement(CAppSettings::bDisplaceSelection);
		pSelSet->SetReferenceSelectionType(CAppSettings::csRefSelType == "Spriting" ? RefSelSpriting : RefSelDefault);
		if(old_sel_mode != new_sel_mode) {
			pSelSet->SetHighlightMode(new_sel_mode);
			pBaseView->GetHighlightSelection()->SetHighlightMode(new_sel_mode);
		}
		pSelSet->SetHighlightTransparency(CAppSettings::TransparencyLevel);
	    
  		pBaseView->SetSpritingMode(CAppSettings::Spriting);
		pBaseView->SetVisibilitySelectionMode(CAppSettings::VisibilitySelection);
		pBaseView->SetTransparentSelectionBoxMode(CAppSettings::bUseSelectBox);
		pBaseView->SetRelatedSelectionLimit(CAppSettings::RelatedSelectionLimit);
		pBaseView->SetDetailSelection(CAppSettings::DetailSelection);

		pBaseView->SetSuppressUpdate(false);
	    pBaseView->Update();
	}
}

 

void SelectionOptionsPage::UpdateSelectionChecks()
{
	if(m_HighlightMode == HighlightQuickmoves)
	{
		((CButton *)GetDlgItem(IDC_NO_QUICKMOVES_HIGHLIGHTING))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_QUICKMOVES_HIGHLIGHTING))->SetCheck(1);
		GetDlgItem(IDC_REF_SEL_TYPE_COMBO)->EnableWindow(1);	
		((CButton *)GetDlgItem(IDC_INVERSE_TRANSPARENCY))->SetCheck(0);
		GetDlgItem(IDC_TEXT_TRANSPARENCY_LEVEL)->EnableWindow(0);
		((CButton *)GetDlgItem(IDC_COLORED_INVERSE_TRANSPARENCY))->SetCheck(0);
	}
	else if(m_HighlightMode == HighlightDefault)
	{
		((CButton *)GetDlgItem(IDC_NO_QUICKMOVES_HIGHLIGHTING))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_QUICKMOVES_HIGHLIGHTING))->SetCheck(0);
		GetDlgItem(IDC_REF_SEL_TYPE_COMBO)->EnableWindow(0);	
		((CButton *)GetDlgItem(IDC_INVERSE_TRANSPARENCY))->SetCheck(0);
		GetDlgItem(IDC_TEXT_TRANSPARENCY_LEVEL)->EnableWindow(0);	
		((CButton *)GetDlgItem(IDC_COLORED_INVERSE_TRANSPARENCY))->SetCheck(0);
	}
	else if(m_HighlightMode == InverseTransparency)
	{
		((CButton *)GetDlgItem(IDC_NO_QUICKMOVES_HIGHLIGHTING))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_QUICKMOVES_HIGHLIGHTING))->SetCheck(0);
		GetDlgItem(IDC_REF_SEL_TYPE_COMBO)->EnableWindow(0);	
		((CButton *)GetDlgItem(IDC_INVERSE_TRANSPARENCY))->SetCheck(1);
		GetDlgItem(IDC_TEXT_TRANSPARENCY_LEVEL)->EnableWindow(1);	
		((CButton *)GetDlgItem(IDC_COLORED_INVERSE_TRANSPARENCY))->SetCheck(0);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_NO_QUICKMOVES_HIGHLIGHTING))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_QUICKMOVES_HIGHLIGHTING))->SetCheck(0);
		GetDlgItem(IDC_REF_SEL_TYPE_COMBO)->EnableWindow(0);	
		((CButton *)GetDlgItem(IDC_INVERSE_TRANSPARENCY))->SetCheck(0);
		GetDlgItem(IDC_TEXT_TRANSPARENCY_LEVEL)->EnableWindow(1);
		((CButton *)GetDlgItem(IDC_COLORED_INVERSE_TRANSPARENCY))->SetCheck(1);
	}
}

 
void SelectionOptionsPage::OnCheckGrayScaleSelection() 
{
	UpdateSelectionChecks();
}

void SelectionOptionsPage::OnCheckDisplaceSelection() 
{
	UpdateSelectionChecks();
}

void SelectionOptionsPage::OnRelatedSelection() 
{
	UpdateData();
	UpdateRelatedSelection();
}

void SelectionOptionsPage::UpdateRelatedSelection()
{

	CButton* pRelSelChk = (CButton*)GetDlgItem(IDC_CHECK_RELATED_SELECTION);
	CButton* pRelSelTxt =  (CButton*)GetDlgItem(IDC_TEXT_RELATED_SELECTION);

	ASSERT( pRelSelChk );
	ASSERT( pRelSelTxt );

	if( pRelSelChk->GetCheck() == 0 )
	{
		pRelSelTxt->SetCheck(0);
		pRelSelTxt->EnableWindow(0);
	}
	else
	{
		pRelSelTxt->EnableWindow(1);
	}	
}
 

void SelectionOptionsPage::OnButtonReset() 
{
	// restore the default values
 	m_clrbtnSelPolygons.currentcolor = CAppSettings::DefaultPolygonSelectionColor;
	m_clrbtnSelLines.currentcolor = CAppSettings::DefaultLineSelectionColor;
	m_clrbtnSelMarkers.currentcolor = CAppSettings::DefaultMarkerSelectionColor;
	m_nSelTransparency = CAppSettings::DefaultSelectionColorTransparency;
 	m_bGrayScaleSelection = bool2BOOL(CAppSettings::DefaultbGrayScaleSelection);
 	m_bDisplaceSelection = bool2BOOL(CAppSettings::DefaultbDisplaceSelection);
	m_bVisibilitySelection = bool2BOOL(CAppSettings::DefaultVisibilitySelection);
	m_bDynamicHighlighting = bool2BOOL(CAppSettings::DefaultDynamicHighlighting);
	m_bDetailSelection = bool2BOOL(CAppSettings::DefaultDetailSelection);
	m_bUseSelectBox = bool2BOOL(CAppSettings::DefaultbUseSelectBox);
	m_HighlightMode = CAppSettings::DefaultHighlightMode;
	m_fTransparencyLevel = CAppSettings::DefaultTransparencyLevel;
	m_bRelatedSelectionLimit = bool2BOOL(CAppSettings::DefaultRelatedSelectionLimit!=NO_RELATED_SELECTION_LIMIT);
	m_nRelatedSelectionLimit = m_bRelatedSelectionLimit ? CAppSettings::DefaultRelatedSelectionLimit : 0;

	m_csQuickMovesType = CAppSettings::DefaultcsQuickMovesType;
	m_csRefSelType = CAppSettings::csDefaultRefSelType;
 
	// update the dialog
	UpdateData(FALSE);
 	UpdateSelectionChecks();

	// the color buttons needs redraw to reflect new colors - refresh here
	RedrawWindow();
}

void SelectionOptionsPage::OnButtonApply() 
{
	UpdateData(true);
	ApplySettings();
}


void GeneralOptionsPage::OnSelchangeComboTransparencySorting() 
{
	UpdateTransparencySorting();	
}




/////////////////////////////////////////////////////////////////////////////
// OutputOptionsPage dialog


OutputOptionsPage::OutputOptionsPage(CWnd* pParent /*=NULL*/)
: HOptionsPage(OutputOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(OutputOptionsPage)
	m_nDPI				= 0;
	m_iWindowWidth		= 0;
	m_iWindowHeight		= 0;
	m_fPaperWidth		= 0.f;
	m_fPaperHeight		= 0.f;
	m_DocOpt			= 1;
	m_ImageOpt			= 1;
	m_bMemoryOverSpeed	= FALSE;
	m_bForceGrayscale	= FALSE;
	m_bUseWindowColor	= FALSE;
	//}}AFX_DATA_INIT
}


void OutputOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OutputOptionsPage)
	DDX_Text(pDX, IDC_EDIT_DPI, m_nDPI);
	DDV_MinMaxInt(pDX, m_nDPI, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_WINDOW_WIDTH, m_iWindowWidth);
	DDV_MinMaxFloat(pDX, m_iWindowWidth, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_WINDOW_HEIGHT, m_iWindowHeight);
	DDV_MinMaxFloat(pDX, m_iWindowHeight, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_PAPER_WIDTH, m_fPaperWidth);
	DDV_MinMaxFloat(pDX, m_fPaperWidth, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_PAPER_HEIGHT, m_fPaperHeight);
	DDV_MinMaxFloat(pDX, m_fPaperHeight, 0, 1000);
	DDX_Check(pDX, IDC_FORCE_BLACK_AND_WHITE, m_bForceGrayscale);
	DDX_Check(pDX, IDC_CONSERVE_MEMORY, m_bMemoryOverSpeed);
	DDX_Check(pDX, IDC_USE_WINDOW_COLOR, m_bUseWindowColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OutputOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(OutputOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_HOOPS_WYSIWYG, OnBnClickedRadioHoopsWYSIWYG)
	ON_BN_CLICKED(IDC_RADIO_HOOPS_WINDOW_TO_PAGE, OnBnClickedRadioHoopsWindowToPage)
	ON_BN_CLICKED(IDC_RADIO_USE_WINDOW_SIZE, OnBnClickedRadioUseWindowSize)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM_IMAGE_SIZE, OnBnClickedRadioCustomImageSize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OutputOptionsPage message handlers
BOOL OutputOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();

	m_nDPI				= CAppSettings::DPI ? CAppSettings::DPI : CAppSettings::DefaultDPI;
	m_iWindowWidth		= CAppSettings::OutputWidth;
	m_iWindowHeight		= CAppSettings::OutputHeight;
	m_fPaperWidth		= CAppSettings::PaperWidth;
	m_fPaperHeight		= CAppSettings::PaperHeight;
	m_DocOpt			= (int)CAppSettings::DocOpt;
	m_ImageOpt			= (int)CAppSettings::ImageOpt;
	m_bForceGrayscale	= bool2BOOL(CAppSettings::ForceGrayscale);
	m_bMemoryOverSpeed	= bool2BOOL(CAppSettings::bConserveMemory);
	m_bUseWindowColor	= bool2BOOL(CAppSettings::bUseWindowColor);

	SetOutputRadio();
	EnableSetPageSize(true);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void OutputOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}

// Applies the Selection related application settings to the given view
void OutputOptionsPage::ApplySettings()
{
	CAppSettings::ForceGrayscale	= BOOL2bool(m_bForceGrayscale);
	CAppSettings::bConserveMemory	= BOOL2bool(m_bMemoryOverSpeed);
	CAppSettings::bUseWindowColor	= BOOL2bool(m_bUseWindowColor);

	CAppSettings::DPI			= m_nDPI;

	/* This is in pixels. */
	CAppSettings::OutputWidth	= m_iWindowWidth;
	CAppSettings::OutputHeight	= m_iWindowHeight;

	/* This is in inches * 1000 */
	CAppSettings::PaperWidth	= m_fPaperWidth;
	CAppSettings::PaperHeight	= m_fPaperHeight;

	CAppSettings::DocOpt	= (HDocOutputOptions)m_DocOpt;
	CAppSettings::ImageOpt	= (HImageOutputOptions)m_ImageOpt;
}

void OutputOptionsPage::EnableSetWindowSize(bool value)
{
	GetDlgItem(IDC_EDIT_WINDOW_WIDTH)->EnableWindow(value);
	GetDlgItem(IDC_EDIT_WINDOW_HEIGHT)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_WINDOW_WIDTH)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_WINDOW_HEIGHT)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_PIXELS1)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_PIXELS2)->EnableWindow(value);
}

void OutputOptionsPage::EnableSetPageSize(bool value)
{
	GetDlgItem(IDC_EDIT_PAPER_WIDTH)->EnableWindow(value);
	GetDlgItem(IDC_EDIT_PAPER_HEIGHT)->EnableWindow(value);
	GetDlgItem(IDC_EDIT_DPI)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_PAPER_WIDTH)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_PAPER_HEIGHT)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_DPI)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_INCHES1)->EnableWindow(value);
	GetDlgItem(IDC_STATIC_INCHES2)->EnableWindow(value);
}

void OutputOptionsPage::SetOutputRadio()
{
	if(m_DocOpt == HWYSIWYG)
	{
		((CButton*)GetDlgItem(IDC_RADIO_HOOPS_WYSIWYG))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_HOOPS_WINDOW_TO_PAGE))->SetCheck(BST_UNCHECKED);
	}
	else if(m_DocOpt == HUseWholePage)
	{
		((CButton*)GetDlgItem(IDC_RADIO_HOOPS_WYSIWYG))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_HOOPS_WINDOW_TO_PAGE))->SetCheck(BST_CHECKED);
	}

	if(m_ImageOpt == HUseWindowSize)
	{
		((CButton*)GetDlgItem(IDC_RADIO_USE_WINDOW_SIZE))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_CUSTOM_IMAGE_SIZE))->SetCheck(BST_UNCHECKED);
		EnableSetWindowSize(false);
	}
	else if(m_ImageOpt == HSpecifyImageSize)
	{
		((CButton*)GetDlgItem(IDC_RADIO_USE_WINDOW_SIZE))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_CUSTOM_IMAGE_SIZE))->SetCheck(BST_CHECKED);
		EnableSetWindowSize(true);
	}
}

void OutputOptionsPage::OnBnClickedRadioHoopsWYSIWYG()
{
	m_DocOpt = (int)HWYSIWYG;
	SetOutputRadio();
}

void OutputOptionsPage::OnBnClickedRadioHoopsWindowToPage()
{
	m_DocOpt = (int)HUseWholePage;
	SetOutputRadio();
}

void OutputOptionsPage::OnBnClickedRadioUseWindowSize()
{
	m_ImageOpt = (int)HUseWindowSize;
	SetOutputRadio();
}

void OutputOptionsPage::OnBnClickedRadioCustomImageSize()
{
	m_ImageOpt = (int)HSpecifyImageSize;
	SetOutputRadio();
}


void OutputOptionsPage::OnButtonReset() 
{
	// restore the default values

	m_nDPI				= CAppSettings::DefaultDPI;
	m_iWindowWidth		= CAppSettings::DefaultOutputWidth;
	m_iWindowHeight		= CAppSettings::DefaultOutputHeight;
	m_fPaperWidth		= CAppSettings::DefaultPaperWidth;
	m_fPaperHeight		= CAppSettings::DefaultPaperHeight;
	m_bForceGrayscale	= bool2BOOL(CAppSettings::DefaultForceGrayscale);
	m_bMemoryOverSpeed	= bool2BOOL(CAppSettings::DefaultbConserveMemory);
	m_bUseWindowColor	= bool2BOOL(CAppSettings::DefaultbUseWindowColor);
	m_DocOpt			= (int)CAppSettings::DefaultDocOpt;
	m_ImageOpt			= (int)CAppSettings::DefaultImageOpt;

	SetOutputRadio();	

	// update the dialog
	UpdateData(FALSE);
}

void OutputOptionsPage::OnButtonApply() 
{
	UpdateData(true);
	ApplySettings();
}


/////////////////////////////////////////////////////////////////////////////
// GeometryOptionsPage dialog


GeometryOptionsPage::GeometryOptionsPage(CWnd* pParent /*=NULL*/)
: HOptionsPage(GeometryOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(GeometryOptionsPage)
	m_nBudget			=0;
	m_nContBudget		=0;
	m_fMaxDeviation		=0.f;
	m_fMaxAngle			=0.f;
	m_fMaxLength		=0.f;
	m_bViewIndependent	= TRUE;
	//}}AFX_DATA_INIT
}


void GeometryOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeometryOptionsPage)
	DDX_Text(pDX, IDC_EDIT_BUDGET, m_nBudget);
	DDV_MinMaxInt(pDX, m_nBudget, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_CONTINUED_BUDGET, m_nContBudget);
	DDV_MinMaxInt(pDX, m_nContBudget, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_DEVIATION, m_fMaxDeviation);
	DDV_MinMaxFloat(pDX, m_fMaxDeviation, 0, 100);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_ANGLE, m_fMaxAngle);
	DDV_MinMaxFloat(pDX, m_fMaxAngle, 0, 360);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_LENGTH, m_fMaxLength);
	DDV_MinMaxFloat(pDX, m_fMaxLength, 0, 1);
	DDX_Check(pDX, IDC_VIEW_INDEPENDENT, m_bViewIndependent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeometryOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(GeometryOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeometryOptionsPage message handlers
BOOL GeometryOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();

	m_nBudget			= CAppSettings::Budget;
	m_nContBudget		= CAppSettings::ContinuedBudget;
	m_fMaxDeviation		= CAppSettings::MaxDeviation/10000.f;
	m_fMaxAngle			= CAppSettings::MaxAngle/10000.f;
	m_fMaxLength		= CAppSettings::MaxLength/10000.f;
	m_bViewIndependent	= bool2BOOL(CAppSettings::bViewIndependent);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void GeometryOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}

// Applies the Selection related application settings to the given view
void GeometryOptionsPage::ApplySettings()
{
	CAppSettings::Budget			= m_nBudget;
	CAppSettings::ContinuedBudget	= m_nContBudget;
	CAppSettings::MaxDeviation		= m_fMaxDeviation*10000;
	CAppSettings::MaxAngle			= m_fMaxAngle*10000;
	CAppSettings::MaxLength			= m_fMaxLength*10000;
	CAppSettings::bViewIndependent	= BOOL2bool(m_bViewIndependent);

	char opt[4096]; 

	HCLOCALE(sprintf(opt, "general curve = (budget = %d, continued budget = %d, maximum deviation = %f, maximum angle = %f, maximum length = %f, %s view independent)", 
		m_nBudget, m_nContBudget, m_fMaxDeviation, m_fMaxAngle, m_fMaxLength, CAppSettings::bViewIndependent?"":"no"));

	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();

	if(pActiveView)
	{
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}

		pBaseView->SetSuppressUpdate(true);

		HC_Open_Segment_By_Key(pBaseView->GetSceneKey());
			HC_Set_Rendering_Options(opt);
		HC_Close_Segment();

		pBaseView->SetSuppressUpdate(false);
		pBaseView->Update();
	}
}



void GeometryOptionsPage::OnButtonReset() 
{
	// restore the default values
	m_nBudget			= CAppSettings::DefaultBudget;
	m_nContBudget		= CAppSettings::DefaultContinuedBudget;
	m_fMaxDeviation		= CAppSettings::DefaultMaxDeviation/10000.f;
	m_fMaxAngle			= CAppSettings::DefaultMaxAngle/10000.f;
	m_fMaxLength		= CAppSettings::DefaultMaxLength/10000.f;
	m_bViewIndependent	= bool2BOOL(CAppSettings::DefaultbViewIndependent);

	// update the dialog
	UpdateData(FALSE);
}

void GeometryOptionsPage::OnButtonApply() 
{
	UpdateData(true);
	ApplySettings();
}

/////////////////////////////////////////////////////////////////////////////
// EffectsOptionsPage dialog


EffectsOptionsPage::EffectsOptionsPage(CWnd* pParent /*=NULL*/)
: HOptionsPage(EffectsOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(EffectsOptionsPage)
	m_bSimpleShadows		=TRUE;
	m_bShadowMaps			=FALSE;
	m_bReflection			=FALSE;
	m_csSamples				="4";
	m_csResolution			="512";
	m_nShadowRes			= 32;
	m_nShadowBlur			= 8;
	m_csShadowRenderingMode = _T("Software");
	m_fShadowOpacity		=1.f;
	m_fReflectionOpacity	=1.f;
	m_bReflectionFading		=TRUE;
	m_bJitter				=TRUE;
	m_bUseBlur				=FALSE;
	m_nBlur					=1;
	m_bUseAttenuation		=FALSE;
	m_fHither				=0.f;
	m_fYon					=1.f;
	m_ViewDependentSMap		=TRUE;
	m_bFastAmbient			=FALSE;
	m_FastAmbientStrength	=1.0f;
	m_bFastSilhouette		=FALSE;
	m_FastSilhouetteTolerance =1.0f;
	m_bHeavyExteriorSilhouette = FALSE;
	m_bUseLightVector		= FALSE;
	m_LightVector.Set(0.0f, 0.0f, 0.0f);
	m_bIgnoreTransparency	= FALSE;
	//}}AFX_DATA_INIT
}

#include <limits>
void EffectsOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EffectsOptionsPage)
 	DDX_Check(pDX, IDC_CHECK_SHADOWS, m_bSimpleShadows);
	DDX_Check(pDX, IDC_SHADOW_MAPS, m_bShadowMaps);
	DDX_CBString(pDX, IDC_SM_RESOLUTION_COMBO, m_csResolution);
	DDX_CBString(pDX, IDC_SM_SAMPLES_COMBO, m_csSamples);
	DDX_Check(pDX, IDC_CHECK_REFLECTION_PLANE, m_bReflection);	
	DDX_Control(pDX, IDC_BUTTON_COLOR_SHADOW, m_clrbtnShadow);
	DDX_Text(pDX, IDC_EDIT_SHADOW_RES, m_nShadowRes);
	DDV_MinMaxUInt(pDX, m_nShadowRes, 32, 1024);
	DDX_Text(pDX, IDC_EDIT_SHADOW_BLUR, m_nShadowBlur);
	DDV_MinMaxUInt(pDX, m_nShadowBlur, 1, 64);
	DDX_Text(pDX, IDC_EDIT_SHADOW_OPACITY, m_fShadowOpacity);
	DDV_MinMaxFloat(pDX, m_fShadowOpacity, 0.f, 1.f);	
	DDX_CBString(pDX, IDC_COMBO_SHADOW_RENDERING_MODE, m_csShadowRenderingMode);
	DDX_Text(pDX, IDC_EDIT_REFLECTION_OPACITY, m_fReflectionOpacity);
	DDV_MinMaxFloat(pDX, m_fReflectionOpacity, 0.f, 1.f);	
	DDX_Check(pDX, IDC_CHECK_REFLECTION_FADING, m_bReflectionFading);	
	DDX_Check(pDX, IDC_SM_JITTER, m_bJitter);
	DDX_Check(pDX, IDC_REFLECTION_BLUR, m_bUseBlur);
	DDX_Text(pDX, IDC_EDIT_REFLECTION_BLUR, m_nBlur);
	DDV_MinMaxUInt(pDX, m_nBlur, 0, 100);
	DDX_Check(pDX, IDC_REFLECTION_ATTENUATION, m_bUseAttenuation);
	DDX_Text(pDX, IDC_EDIT_REFLECTION_HITHER, m_fHither);
	DDX_Text(pDX, IDC_EDIT_REFLECTION_YON, m_fYon);
	DDX_Check(pDX, IDC_SM_VIEW_DEPENDENT, m_ViewDependentSMap);
	DDX_Check(pDX, IDC_FAST_AMBIENT_OCCLUSION, m_bFastAmbient);
	DDX_Text(pDX, IDC_FAST_AMBIENT_STRENGTH, m_FastAmbientStrength);
	DDV_MinMaxFloat(pDX, m_FastAmbientStrength, 0.01f, 100.0f);	
	DDX_Check(pDX, IDC_FAST_SILHOUETTE_EDGES, m_bFastSilhouette);
	DDX_Check(pDX, IDC_HIGH_QUALITY_AMBIENT_OCCLUSION, m_bHQAmbientOcclusion);
	DDX_Text(pDX, IDC_FAST_SILHOUETTE_TOLERANCE, m_FastSilhouetteTolerance);
	DDV_MinMaxFloat(pDX, m_FastSilhouetteTolerance, 0.01f, 100.0f);	
	DDX_Check(pDX, IDC_HEAVY_EXTERIOR_SILHOUETTE, m_bHeavyExteriorSilhouette);
	DDX_Check(pDX, IDC_LIGHT_VECTOR, m_bUseLightVector);
	DDX_Text(pDX, IDC_EDIT_LIGHT_VECTOR_X_BOX, m_LightVector.x);
	DDX_Text(pDX, IDC_EDIT_LIGHT_VECTOR_Y_BOX, m_LightVector.y);
	DDX_Text(pDX, IDC_EDIT_LIGHT_VECTOR_Z_BOX, m_LightVector.z);
	DDX_Check(pDX, IDC_IGNORE_TRANSPARENCY, m_bIgnoreTransparency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EffectsOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(EffectsOptionsPage)
	ON_CBN_SELCHANGE(IDC_CHECK_REFLECTION_PLANE, OnCheckReflectionPlane)
	ON_BN_CLICKED(IDC_CHECK_REFLECTION_PLANE, OnCheckReflectionPlane)
	ON_BN_CLICKED(IDC_REFLECTION_ATTENUATION, OnCheckAttenuation)
	ON_BN_CLICKED(IDC_REFLECTION_BLUR, OnCheckUseBlur)
	ON_EN_KILLFOCUS(IDC_EDIT_REFLECTION_YON, OnChangeHitherYon)
	ON_EN_KILLFOCUS(IDC_EDIT_REFLECTION_HITHER, OnChangeHitherYon)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_FAST_AMBIENT_OCCLUSION, OnCheckFastAmbient)
	ON_BN_CLICKED(IDC_FAST_SILHOUETTE_EDGES, OnCheckFastSilhouette)
	ON_BN_CLICKED(IDC_LIGHT_VECTOR, OnCheckLightVector)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EffectsOptionsPage message handlers
BOOL EffectsOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();
	int samples, resolution;
	char str[MVO_BUFFER_SIZE];

	m_bSimpleShadows = (CAppSettings::ShadowMode == HShadowNone) ? FALSE : TRUE;
	m_bShadowMaps = bool2BOOL(CAppSettings::bShadowMap);
	m_bReflection = bool2BOOL(CAppSettings::bReflectionPlane);
	samples=CAppSettings::nSMSamples;
	itoa(samples, str, 10);
	m_csSamples = CString(str);
	resolution=CAppSettings::nSMResolution;
	itoa(resolution, str, 10);
	m_csResolution = CString(str);

	m_clrbtnShadow.currentcolor = CAppSettings::ShadowColor;
	m_nShadowRes = CAppSettings::ShadowRes;
	m_nShadowBlur = CAppSettings::ShadowBlur;
	m_fShadowOpacity = CAppSettings::ShadowOpacity;

	m_csShadowRenderingMode = ShadowRenderingModeSetting2Ui(CAppSettings::ShadowRenderingMode);

	m_fReflectionOpacity = CAppSettings::ReflectionOpacity;
	m_bReflectionFading = CAppSettings::bReflectionFading;

	m_bJitter = bool2BOOL(CAppSettings::Jitter);
	m_nBlur	= CAppSettings::ReflectionBlur;
	m_bUseBlur = bool2BOOL(CAppSettings::ReflectionUseBlur);
	m_bUseAttenuation = bool2BOOL(CAppSettings::ReflectionUseAttenuation);
	m_fHither = CAppSettings::ReflectionHither;
	m_fYon = CAppSettings::ReflectionYon;

	m_ViewDependentSMap = bool2BOOL(CAppSettings::ViewDependentShadowMap);
	m_bFastAmbient = bool2BOOL(CAppSettings::UseFastAmbient);
	m_FastAmbientStrength = CAppSettings::FastAmbientStrength;
	m_bHQAmbientOcclusion = bool2BOOL(CAppSettings::HQAmbientOcclusion);

	m_bFastSilhouette = bool2BOOL(CAppSettings::UseFastSilhouette);
	m_FastSilhouetteTolerance = CAppSettings::FastSilhouetteTolerance;
	m_bHeavyExteriorSilhouette = bool2BOOL(CAppSettings::HeavyExteriorSilhouette);

	m_bUseLightVector = bool2BOOL(CAppSettings::UseLightVector);
	m_LightVector = CAppSettings::LightVector;

	m_bIgnoreTransparency = bool2BOOL(CAppSettings::IgnoreTransparency);

	UpdateData(FALSE);

	UpdateReflectionPlaneData();
	UpdateUseBlur();
	UpdateAttenuation();
	UpdateAmbientStrength();
	UpdateSilhouetteTolerance();
	UpdateLightVector();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

}

void EffectsOptionsPage::OnCheckFastSilhouette()
{
	UpdateSilhouetteTolerance();
}

void EffectsOptionsPage::OnCheckLightVector()
{
	UpdateLightVector();
}

void EffectsOptionsPage::UpdateLightVector()
{
	CButton* plv		= (CButton*)GetDlgItem(IDC_LIGHT_VECTOR);
	CButton* px			= (CButton*)GetDlgItem(IDC_LIGHT_VECTOR_TEXT_X);
	CButton* px_box		= (CButton*)GetDlgItem(IDC_EDIT_LIGHT_VECTOR_X_BOX);
	CButton* py			= (CButton*)GetDlgItem(IDC_LIGHT_VECTOR_TEXT_Y);
	CButton* py_box		= (CButton*)GetDlgItem(IDC_EDIT_LIGHT_VECTOR_Y_BOX);
	CButton* pz			= (CButton*)GetDlgItem(IDC_LIGHT_VECTOR_TEXT_Z);
	CButton* pz_box		= (CButton*)GetDlgItem(IDC_EDIT_LIGHT_VECTOR_Z_BOX);


	ASSERT( plv );
	ASSERT( px );
	ASSERT( px_box );
	ASSERT( py );
	ASSERT( py_box );
	ASSERT( pz );
	ASSERT( pz_box );
	

	if(plv->GetCheck())
	{
		px->EnableWindow(1);
		px_box->EnableWindow(1);
		py->EnableWindow(1);
		py_box->EnableWindow(1);
		pz->EnableWindow(1);
		pz_box->EnableWindow(1);
	}
	else
	{
		px->EnableWindow(0);
		px_box->EnableWindow(0);
		py->EnableWindow(0);
		py_box->EnableWindow(0);
		pz->EnableWindow(0);
		pz_box->EnableWindow(0);
	}
}

void EffectsOptionsPage::UpdateSilhouetteTolerance()
{
	CButton* pFstSlh	= (CButton*)GetDlgItem(IDC_FAST_SILHOUETTE_EDGES);
	CButton* pSlhTxt	= (CButton*)GetDlgItem(IDC_FAST_SILHOUETTE_TEXT);
	CButton* pSlhTol	= (CButton*)GetDlgItem(IDC_FAST_SILHOUETTE_TOLERANCE);
	CButton* pCWSE		= (CButton*)GetDlgItem(IDC_HEAVY_EXTERIOR_SILHOUETTE);

	ASSERT( pFstSlh );
	ASSERT( pSlhTxt );
	ASSERT( pSlhTol );
	ASSERT( pCWSE );

	if(pFstSlh->GetCheck())
	{
		pSlhTxt->EnableWindow(1);
		pSlhTol->EnableWindow(1);
		pCWSE->EnableWindow(1);
	}
	else
	{
		pSlhTxt->EnableWindow(0);
		pSlhTol->EnableWindow(0);
		pCWSE->EnableWindow(0);
	}
}

void EffectsOptionsPage::OnCheckFastAmbient()
{
	UpdateAmbientStrength();
}

void EffectsOptionsPage::OnCheckReflectionPlane()
{
	UpdateReflectionPlaneData();
}

void EffectsOptionsPage::OnCheckAttenuation()
{
	UpdateAttenuation();
}

void EffectsOptionsPage::OnCheckUseBlur()
{
	UpdateUseBlur();
}

void EffectsOptionsPage::OnChangeHitherYon()
{
	UpdateData(TRUE);

	if(m_fYon < 0.f || m_fHither < 0.f || m_fYon <= m_fHither)
	{
		AfxMessageBox(_T("Error:\nInequality not observed.\n\n0.0 < Hither < Yon"));
	}
	
}

void EffectsOptionsPage::UpdateAmbientStrength()
{
	CButton* pFstAmb	= (CButton*)GetDlgItem(IDC_FAST_AMBIENT_OCCLUSION);
	CButton* pAmbTxt	= (CButton*)GetDlgItem(IDC_FAST_AMBIENT_TEXT);
	CButton* pAmbStr	= (CButton*)GetDlgItem(IDC_FAST_AMBIENT_STRENGTH);
	CButton* pHQAmb		= (CButton*)GetDlgItem(IDC_HIGH_QUALITY_AMBIENT_OCCLUSION);

	ASSERT( pFstAmb );
	ASSERT( pAmbTxt );
	ASSERT( pAmbStr );

	if(pFstAmb->GetCheck())
	{
		pAmbTxt->EnableWindow(1);
		pAmbStr->EnableWindow(1);
		pHQAmb->EnableWindow(1);
	}
	else
	{
		pAmbTxt->EnableWindow(0);
		pAmbStr->EnableWindow(0);
		pHQAmb->EnableWindow(0);
	}
}

void EffectsOptionsPage::UpdateReflectionPlaneData()
{
	CButton* pPlnChk	= (CButton*)GetDlgItem(IDC_CHECK_REFLECTION_PLANE);
	CButton* pOpac		= (CButton*)GetDlgItem(IDC_EDIT_REFLECTION_OPACITY);
	CButton* pFadChk	= (CButton*)GetDlgItem(IDC_CHECK_REFLECTION_FADING);
	CButton* pOpacTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_OPACITY_TEXT);
	CButton* pAttenTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_ATTENUATION);
	CButton* pHithTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_HITHER);
	CButton* pYonTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_YON);
	CButton* pHith		= (CButton*)GetDlgItem(IDC_EDIT_REFLECTION_HITHER);
	CButton* pYon		= (CButton*)GetDlgItem(IDC_EDIT_REFLECTION_YON);
	CButton* pBlur		= (CButton*)GetDlgItem(IDC_EDIT_REFLECTION_BLUR);
	CButton* pBlurTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_BLUR);


	ASSERT( pPlnChk );
	ASSERT( pOpac );
	ASSERT( pFadChk );
	ASSERT( pOpacTxt );
	ASSERT( pAttenTxt );
	ASSERT( pHithTxt );
	ASSERT( pYonTxt );
	ASSERT( pHith );
	ASSERT( pYon );
	ASSERT( pBlur );
	ASSERT( pBlurTxt );

	if( pPlnChk->GetCheck() == 0 )
	{
		pOpac->EnableWindow(0);
		pFadChk->EnableWindow(0);
		pOpacTxt->EnableWindow(0);
		pAttenTxt->EnableWindow(0);
		pHithTxt->EnableWindow(0);
		pYonTxt->EnableWindow(0);
		pHith->EnableWindow(0);
		pYon->EnableWindow(0);
		pBlur->EnableWindow(0);
		pBlurTxt->EnableWindow(0);
	}
	else
	{
		pOpac->EnableWindow(1);
		pFadChk->EnableWindow(1);
		pOpacTxt->EnableWindow(1);
		pAttenTxt->EnableWindow(1);
		if(pAttenTxt->GetCheck() == 1)
		{
			pHithTxt->EnableWindow(1);
			pYonTxt->EnableWindow(1);
			pHith->EnableWindow(1);
			pYon->EnableWindow(1);
		}
		else 
		{
			pHithTxt->EnableWindow(0);
			pYonTxt->EnableWindow(0);
			pHith->EnableWindow(0);
			pYon->EnableWindow(0);
		}
		pBlurTxt->EnableWindow(1);
		if(pBlurTxt->GetCheck() == 1)
			pBlur->EnableWindow(1);
		else 
			pBlur->EnableWindow(0);
	}	
}

void EffectsOptionsPage::UpdateAttenuation()
{
	CButton* pPlnChk	= (CButton*)GetDlgItem(IDC_CHECK_REFLECTION_PLANE);
	CButton* pAttenTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_ATTENUATION);
	CButton* pHithTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_HITHER);
	CButton* pYonTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_YON);
	CButton* pHith		= (CButton*)GetDlgItem(IDC_EDIT_REFLECTION_HITHER);
	CButton* pYon		= (CButton*)GetDlgItem(IDC_EDIT_REFLECTION_YON);

	ASSERT( pPlnChk );
	ASSERT( pAttenTxt );
	ASSERT( pHithTxt );
	ASSERT( pYonTxt );
	ASSERT( pHith );
	ASSERT( pYon );

	if( pPlnChk->GetCheck() == 0 )
		return;

	if(pAttenTxt->GetCheck() == 1)
	{
		pHithTxt->EnableWindow(1);
		pYonTxt->EnableWindow(1);
		pHith->EnableWindow(1);
		pYon->EnableWindow(1);
	}
	else 
	{
		pHithTxt->EnableWindow(0);
		pYonTxt->EnableWindow(0);
		pHith->EnableWindow(0);
		pYon->EnableWindow(0);
	}
}

void EffectsOptionsPage::UpdateUseBlur()
{
	CButton* pPlnChk	= (CButton*)GetDlgItem(IDC_CHECK_REFLECTION_PLANE);
	CButton* pBlur		= (CButton*)GetDlgItem(IDC_EDIT_REFLECTION_BLUR);
	CButton* pBlurTxt	= (CButton*)GetDlgItem(IDC_REFLECTION_BLUR);

	ASSERT( pPlnChk );
	ASSERT( pBlur );
	ASSERT( pBlurTxt );

	if( pPlnChk->GetCheck() == 0 )
		return;

	if(pBlurTxt->GetCheck() == 1)
		pBlur->EnableWindow(1);
	else 
		pBlur->EnableWindow(0);
}


void EffectsOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}

// Applies the EffectsOptionsPage related application settings to the given view
void EffectsOptionsPage::ApplySettings()
{
	int resolution, samples;
	char opt[MVO_BUFFER_SIZE];
	bool is_changed=false;
	HShadowRenderingMode old_mode;

	resolution=atoi(H_ASCII_TEXT(m_csResolution));
	samples=atoi(H_ASCII_TEXT(m_csSamples));	

	CAppSettings::ShadowMode = (m_bSimpleShadows == FALSE) ? HShadowNone : HShadowSoft;
	
	CAppSettings::bReflectionPlane = BOOL2bool(m_bReflection);

	CAppSettings::bShadowMap = BOOL2bool(m_bShadowMaps);
	CAppSettings::nSMSamples = samples;
	CAppSettings::nSMResolution = resolution;

	CAppSettings::ShadowColor = m_clrbtnShadow.currentcolor;
	CAppSettings::ShadowRes = m_nShadowRes;
	CAppSettings::ShadowBlur = m_nShadowBlur;
	CAppSettings::ShadowOpacity = m_fShadowOpacity;

	CAppSettings::ReflectionOpacity = m_fReflectionOpacity;
	CAppSettings::bReflectionFading = BOOL2bool(m_bReflectionFading);

	CAppSettings::Jitter = BOOL2bool(m_bJitter);
	CAppSettings::ReflectionBlur = m_nBlur;
	CAppSettings::ReflectionHither = m_fHither;
	CAppSettings::ReflectionYon = m_fYon;

	CAppSettings::ReflectionUseBlur = BOOL2bool(m_bUseBlur);
	CAppSettings::ReflectionUseAttenuation = BOOL2bool(m_bUseAttenuation);

	CAppSettings::ViewDependentShadowMap = BOOL2bool(m_ViewDependentSMap);
	CAppSettings::UseFastAmbient = BOOL2bool(m_bFastAmbient);
	CAppSettings::FastAmbientStrength = m_FastAmbientStrength;
	CAppSettings::HQAmbientOcclusion = BOOL2bool(m_bHQAmbientOcclusion);
	
	CAppSettings::UseFastSilhouette = BOOL2bool(m_bFastSilhouette);
	CAppSettings::FastSilhouetteTolerance = m_FastSilhouetteTolerance;
	CAppSettings::HeavyExteriorSilhouette = BOOL2bool(m_bHeavyExteriorSilhouette);

	CAppSettings::UseLightVector = BOOL2bool(m_bUseLightVector);
	CAppSettings::LightVector = m_LightVector;

	CAppSettings::IgnoreTransparency = BOOL2bool(m_bIgnoreTransparency);

	old_mode = CAppSettings::ShadowRenderingMode;
	CAppSettings::ShadowRenderingMode = ShadowRenderingModeCString2Enum(m_csShadowRenderingMode);
	if(old_mode != CAppSettings::ShadowRenderingMode)
		is_changed=true;

	// Get the active view to apply the new settings
    CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
    assert(pChild);
    CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();
    HBaseView * pBaseView = 0;
    if( pActiveView )
		pBaseView = pActiveView->GetHoopsView();

	if(!pBaseView)
	{
		return;
	}

	pBaseView->SetSuppressUpdate(true);

	HPoint old_light_vector;
	bool old_use_light_vector = pBaseView->GetShadowLightDirection(&old_light_vector);
	pBaseView->SetShadowLightDirection(CAppSettings::UseLightVector, &CAppSettings::LightVector);
	pBaseView->SetShadowIgnoresTransparency(CAppSettings::IgnoreTransparency);

	pBaseView->SetReflectionPlane(CAppSettings::bReflectionPlane, CAppSettings::ReflectionOpacity, 
		CAppSettings::bReflectionFading, CAppSettings::ReflectionUseAttenuation,
		CAppSettings::ReflectionHither, CAppSettings::ReflectionYon,
		CAppSettings::ReflectionUseBlur, CAppSettings::ReflectionBlur);

	// apply the shadow mode only if things have changed - because turning it on when it already is 
	// causes shadow to regenerate
	if( CAppSettings::ShadowMode != pBaseView->GetShadowMode() 
		|| old_use_light_vector != CAppSettings::UseLightVector
		|| (CAppSettings::UseLightVector && CAppSettings::LightVector != old_light_vector))
			pBaseView->SetShadowMode(CAppSettings::ShadowMode);

	HC_Open_Segment_By_Key (pBaseView->GetShadowMapSegmentKey()); {
		if(CAppSettings::bShadowMap)
			sprintf(opt, "shadow map=(on, resolution=%d, samples=%d, %s jitter, %s)", resolution, samples,
			(CAppSettings::Jitter ? "" : "no"), 
			(CAppSettings::ViewDependentShadowMap ? "view dependent" : "view independent"));
		else 
			sprintf(opt, "no shadow map");
		HC_Set_Rendering_Options (opt);
	} HC_Close_Segment(); 

	HC_Open_Segment_By_Key (pBaseView->GetSceneKey()); {
        if(BOOL2bool(m_bShadowMaps))
			HC_Set_Visibility ("shadows = (emitting, casting, receiving)");
		sprintf(opt, "simple shadow = (opacity = %f)", CAppSettings::ShadowOpacity);
		HC_Set_Rendering_Options (opt);
	} HC_Close_Segment(); 

	char dopt[MVO_BUFFER_SIZE];
	
	HCLOCALE(sprintf(dopt, 
		"ambient occlusion = (%s, strength = %f, quality = %s), fast silhouette edges = (%s, tolerance = %f, %s heavy exterior)",
		(CAppSettings::UseFastAmbient ? "on" : "off") , CAppSettings::FastAmbientStrength, 
		(CAppSettings::HQAmbientOcclusion ? "nicest" : "fast"),
		(CAppSettings::UseFastSilhouette ? "on" : "off"), CAppSettings::FastSilhouetteTolerance,
		(CAppSettings::HeavyExteriorSilhouette ? "" : "no")	));

	HC_Open_Segment_By_Key (pBaseView->GetViewKey());
		HC_Set_Driver_Options(dopt);
	HC_Close_Segment();

	pBaseView->SetShadowRenderingMode(CAppSettings::ShadowRenderingMode);

	HPoint ShadowColor;
    ShadowColor.Set(
	static_cast<float>(GetRValue(CAppSettings::ShadowColor))/255.0f,
	static_cast<float>(GetGValue(CAppSettings::ShadowColor))/255.0f,
	static_cast<float>(GetBValue(CAppSettings::ShadowColor))/255.0f);
    pBaseView->SetShadowColor(ShadowColor);
    pBaseView->SetShadowResolution(CAppSettings::ShadowRes);
    pBaseView->SetShadowBlurring(CAppSettings::ShadowBlur);

	pBaseView->SetSuppressUpdate(false);
	pBaseView->Update();

#ifndef HOOPS_QA
    if( is_changed )
	    AfxMessageBox(_T("Some options such as shadow rendering mode will only be effective for newly opened documents"));
#endif
}



void EffectsOptionsPage::OnButtonReset() 
{
	int samples, resolution;
	char str[MVO_BUFFER_SIZE];

	// restore the default values
	m_bSimpleShadows = (CAppSettings::DefaultShadowMode == HShadowNone) ? FALSE : TRUE;
	m_bShadowMaps = bool2BOOL(CAppSettings::bDefaultShadowMap);
	m_bReflection = bool2BOOL(CAppSettings::bDefaultReflectionPlane);
	samples=CAppSettings::nDefaultSMSamples;
	itoa(samples, str, 10);
	m_csSamples = CString(str);
	resolution=CAppSettings::nDefaultSMResolution;
	itoa(resolution, str, 10);
	m_csResolution = CString(str);
	
	m_clrbtnShadow.currentcolor = CAppSettings::DefaultShadowColor;
	m_nShadowRes = CAppSettings::DefaultShadowRes;
	m_nShadowBlur = CAppSettings::DefaultShadowBlur;
	m_fShadowOpacity = CAppSettings::DefaultShadowOpacity;

	m_csShadowRenderingMode = ShadowRenderingModeSetting2Ui(CAppSettings::DefaultShadowRenderingMode);

	m_fReflectionOpacity = CAppSettings::DefaultReflectionOpacity;
	m_bReflectionFading = bool2BOOL(CAppSettings::bDefaultReflectionFading);
	
	m_bJitter = bool2BOOL(CAppSettings::DefaultJitter);
	m_nBlur = CAppSettings::DefaultReflectionBlur;
	m_fHither = CAppSettings::DefaultReflectionHither;
	m_fYon = CAppSettings::DefaultReflectionYon;

	m_bUseAttenuation = bool2BOOL(CAppSettings::DefaultReflectionUseAttenuation);
	m_bUseBlur = bool2BOOL(CAppSettings::DefaultReflectionUseBlur);

	m_ViewDependentSMap = bool2BOOL(CAppSettings::DefaultViewDependentShadowMap);
	m_bFastAmbient = bool2BOOL(CAppSettings::DefaultUseFastAmbient);
	m_FastAmbientStrength = CAppSettings::DefaultFastAmbientStrength;
	m_bHQAmbientOcclusion = bool2BOOL(CAppSettings::DefaultHQAmbientOcclusion);

	m_bFastSilhouette = bool2BOOL(CAppSettings::DefaultUseFastSilhouette);
	m_FastSilhouetteTolerance = CAppSettings::DefaultFastSilhouetteTolerance;
	m_bHeavyExteriorSilhouette = bool2BOOL(CAppSettings::DefaultHeavyExteriorSilhouette);

	m_bUseLightVector = bool2BOOL(CAppSettings::DefaultUseLightVector);
	m_LightVector = CAppSettings::DefaultLightVector;
	m_bIgnoreTransparency = bool2BOOL(CAppSettings::DefaultIgnoreTransparency);

	// update the dialog
	UpdateData(FALSE);
	
	UpdateReflectionPlaneData();
	UpdateUseBlur();
	UpdateAttenuation();
	UpdateAmbientStrength();
	UpdateSilhouetteTolerance();
	UpdateLightVector();
}

void EffectsOptionsPage::OnButtonApply() 
{
	UpdateData(TRUE);
	ApplySettings();
}

/////////////////////////////////////////////////////////////////////////////
// LightingOptionsPage property page

LightingOptionsPage::LightingOptionsPage(CWnd* pParent)
	: HOptionsPage(LightingOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(LightingOptionsPage)
	m_bLightFollowsCamera = TRUE;
	m_bHemisphericAmbient = FALSE;
	m_bLightScaling = FALSE;
	m_fLightScaleFactor = 1.0f;
	m_AmbientUpVector.Set(0.0f, 1.0f, 0.0f);
	m_GoochWeight = 0.5f;
	m_UseAmbientUpVector = FALSE;
	m_GoochColorHigh = 2.0f;
	m_bUseBloom = FALSE;
	m_fBloomStrength = 1.0;
	m_BloomBlur = 5;
	m_csBloomShape = "Radial";
	m_csLightCount = _T("1");
	//}}AFX_DATA_INIT
}

void LightingOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EffectsOptionsPage)
	DDX_Check(pDX, IDC_HEMISPHERIC_AMBIENT, m_bHemisphericAmbient);
	DDX_Control(pDX, IDC_BUTTON_COLOR_AMBIENT_TOP, m_clrbtnAmbientTop);
	DDX_Control(pDX, IDC_BUTTON_COLOR_AMBIENT_BOTTOM, m_clrbtnAmbientBottom);
	DDX_Check(pDX, IDC_CHECK_AMBIENT_UP_VECTOR, m_UseAmbientUpVector);
	DDX_Text(pDX, IDC_EDIT_AMBIENT_UP_X, m_AmbientUpVector.x);
	DDX_Text(pDX, IDC_EDIT_AMBIENT_UP_Y, m_AmbientUpVector.y);
	DDX_Text(pDX, IDC_EDIT_AMBIENT_UP_Z, m_AmbientUpVector.z);
	DDX_Check(pDX, IDC_MINERS_HELMET, m_bLightFollowsCamera);
	DDX_Check(pDX, IDC_CHECK_LIGHT_SCALING, m_bLightScaling);
	DDX_Text(pDX, IDC_EDIT_LIGHT_SCALE_FACTOR, m_fLightScaleFactor);
	DDX_Control(pDX, IDC_BUTTON_COLOR_GOOCH_1, m_clrbtnGooch1);
	DDX_Control(pDX, IDC_BUTTON_COLOR_GOOCH_2, m_clrbtnGooch2);
	DDX_Control(pDX, IDC_BUTTON_COLOR_GOOCH_3, m_clrbtnGooch3);
	DDX_Control(pDX, IDC_BUTTON_COLOR_GOOCH_4, m_clrbtnGooch4);
	DDX_Control(pDX, IDC_BUTTON_COLOR_GOOCH_5, m_clrbtnGooch5);
	DDX_Control(pDX, IDC_BUTTON_COLOR_GOOCH_6, m_clrbtnGooch6);
	DDX_Text(pDX, IDC_EDIT_GOOCH_WEIGHT, m_GoochWeight);
	DDV_MinMaxFloat(pDX, m_GoochWeight, 0.0f, 1.0f);
	DDX_Text(pDX, IDC_EDIT_GOOCH_COLOR_HIGH, m_GoochColorHigh);
	DDV_MinMaxFloat(pDX, m_GoochColorHigh, 1.0f, 6.0f);
	DDX_Check(pDX, IDC_CHECK_BLOOM, m_bUseBloom);
	DDX_Text(pDX, IDC_BLOOM_STRENGTH_EDIT, m_fBloomStrength);
	DDV_MinMaxFloat(pDX, m_fBloomStrength, 0.0f, 10.0f);
	DDX_Text(pDX, IDC_BLOOM_BLUR_EDIT, m_BloomBlur);
	DDV_MinMaxUInt(pDX, m_BloomBlur, 1, 8);
	DDX_CBString(pDX, IDC_BLOOM_SHAPE_COMBO, m_csBloomShape);
	DDX_CBString(pDX, IDC_LIGHT_NUMBER_COMBO, m_csLightCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(LightingOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(LightingOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_CHECK_LIGHT_SCALING, OnCheckLightScaleFactor)
	ON_BN_CLICKED(IDC_HEMISPHERIC_AMBIENT, OnCheckHemisphericAmbient)
	ON_BN_CLICKED(IDC_CHECK_AMBIENT_UP_VECTOR, OnCheckHemisphericAmbient)
	ON_BN_CLICKED(IDC_CHECK_BLOOM, OnCheckBloom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString BloomShapeEnum2CString(HBloomShape shape)
{
	if(shape == RadialBloom)
		return "Radial";
	else if(shape == StarBloom)
		return "Star";
	else 
		return "";
}

HBloomShape BloomShapeCString2Enum(CString shape)
{
	if(shape == "Radial")
		return RadialBloom;
	else //if(shape == "Star")
		return StarBloom;
}

int LightCountCString2Int(CString ui)
{
	int out = 0;
	sscanf(H_ASCII_TEXT(ui), "%d", &out);
	return out;
}

CString LightCountInt2CString(int cnt)
{
	return CString(H_FORMAT_TEXT("%d", cnt));	
}

BOOL LightingOptionsPage::OnInitDialog()
{
	HOptionsPage::OnInitDialog();
	
	m_bHemisphericAmbient = bool2BOOL(CAppSettings::HemisphericAmbient);
	m_clrbtnAmbientTop.currentcolor = CAppSettings::AmbientTopColor;
	m_clrbtnAmbientBottom.currentcolor = CAppSettings::AmbientBottomColor;
	m_UseAmbientUpVector = bool2BOOL(CAppSettings::UseAmbientUpVector);
	m_AmbientUpVector = CAppSettings::AmbientUpVector;
	
	m_bLightFollowsCamera = bool2BOOL(CAppSettings::LightFollowsCamera);
	m_bLightScaling = bool2BOOL(CAppSettings::bLightScaling);
	m_fLightScaleFactor	= CAppSettings::LightScaleFactor/100000.f;
	m_csLightCount = LightCountInt2CString(CAppSettings::LightCount);
		
	m_clrbtnGooch1.currentcolor = CAppSettings::GoochColor1;
	m_clrbtnGooch2.currentcolor = CAppSettings::GoochColor2;
	m_clrbtnGooch3.currentcolor = CAppSettings::GoochColor3;
	m_clrbtnGooch4.currentcolor = CAppSettings::GoochColor4;
	m_clrbtnGooch5.currentcolor = CAppSettings::GoochColor5;
	m_clrbtnGooch6.currentcolor = CAppSettings::GoochColor6;

	m_GoochColorMap = CAppSettings::GoochColorMap;
	m_GoochWeight = CAppSettings::GoochWeight;
	m_GoochColorHigh = CAppSettings::GoochColorHigh;

	m_bUseBloom = bool2BOOL(CAppSettings::UseBloom);
	m_fBloomStrength = CAppSettings::BloomStrength;
	m_BloomBlur = CAppSettings::BloomBlur;
	m_csBloomShape = BloomShapeEnum2CString(CAppSettings::BloomShape);

	UpdateData(FALSE);
	UpdateLightScaleFactor();
	UpdateAmbientColors();
	UpdateBloom();
	
	return TRUE;
}

void LightingOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}

void LightingOptionsPage::ApplySettings()
{
	char ambient_color[MVO_BUFFER_SIZE];
	char ropt[MVO_BUFFER_SIZE];
	char gooch_color_map[MVO_BUFFER_SIZE];
	char dopt[MVO_BUFFER_SIZE];

	CAppSettings::HemisphericAmbient = BOOL2bool(m_bHemisphericAmbient);
	CAppSettings::AmbientTopColor = m_clrbtnAmbientTop.currentcolor;
	CAppSettings::AmbientBottomColor = m_clrbtnAmbientBottom.currentcolor;
	CAppSettings::UseAmbientUpVector = BOOL2bool(m_UseAmbientUpVector);
	CAppSettings::AmbientUpVector = m_AmbientUpVector;

	CAppSettings::LightFollowsCamera = BOOL2bool(m_bLightFollowsCamera);
	CAppSettings::bLightScaling = BOOL2bool(m_bLightScaling);
	CAppSettings::LightScaleFactor = m_fLightScaleFactor*100000.f;
	CAppSettings::LightCount = LightCountCString2Int(m_csLightCount);

	CAppSettings::GoochColor1 = m_clrbtnGooch1.currentcolor;
	CAppSettings::GoochColor2 = m_clrbtnGooch2.currentcolor;
	CAppSettings::GoochColor3 = m_clrbtnGooch3.currentcolor;
	CAppSettings::GoochColor4 = m_clrbtnGooch4.currentcolor;
	CAppSettings::GoochColor5 = m_clrbtnGooch5.currentcolor;
	CAppSettings::GoochColor6 = m_clrbtnGooch6.currentcolor;
	
	CAppSettings::GoochWeight = m_GoochWeight;
	CAppSettings::GoochColorHigh = m_GoochColorHigh;

	CAppSettings::UseBloom = BOOL2bool(m_bUseBloom);
	CAppSettings::BloomStrength = m_fBloomStrength;
	CAppSettings::BloomBlur = m_BloomBlur;
	CAppSettings::BloomShape = BloomShapeCString2Enum(m_csBloomShape);


	sprintf(gooch_color_map, "(R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f), (R=%f G=%f B=%f)", 
		GetRValue(CAppSettings::GoochColor1)/255.0f, 
		GetGValue(CAppSettings::GoochColor1)/255.0f,
		GetBValue(CAppSettings::GoochColor1)/255.0f,
		GetRValue(CAppSettings::GoochColor2)/255.0f, 
		GetGValue(CAppSettings::GoochColor2)/255.0f,
		GetBValue(CAppSettings::GoochColor2)/255.0f,
		GetRValue(CAppSettings::GoochColor3)/255.0f, 
		GetGValue(CAppSettings::GoochColor3)/255.0f,
		GetBValue(CAppSettings::GoochColor3)/255.0f,
		GetRValue(CAppSettings::GoochColor4)/255.0f, 
		GetGValue(CAppSettings::GoochColor4)/255.0f,
		GetBValue(CAppSettings::GoochColor4)/255.0f,
		GetRValue(CAppSettings::GoochColor5)/255.0f, 
		GetGValue(CAppSettings::GoochColor5)/255.0f,
		GetBValue(CAppSettings::GoochColor5)/255.0f,
		GetRValue(CAppSettings::GoochColor6)/255.0f, 
		GetGValue(CAppSettings::GoochColor6)/255.0f,
		GetBValue(CAppSettings::GoochColor6)/255.0f);
	CAppSettings::GoochColorMap = gooch_color_map;					

	// Get the active view to apply the new settings
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();

	if (pActiveView)
	{
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}

		pBaseView->SetSuppressUpdate(true);

		if (CAppSettings::bLightScaling)
			pBaseView->SetLightScaling(CAppSettings::LightScaleFactor/100000.0f);
		else
			pBaseView->SetLightScaling(0);

		pBaseView->SetLightFollowsCamera(CAppSettings::LightFollowsCamera);
		pBaseView->SetLightCount(CAppSettings::LightCount);

		HC_Open_Segment_By_Key(pActiveView->GetSceneKey());
			HC_Open_Segment("./overwrite/lights/gooch_color_map_segment");
				HC_Set_Color_Map(H_ASCII_TEXT(CAppSettings::GoochColorMap));
			HC_Close_Segment();
			if(CAppSettings::HemisphericAmbient)
			{
				float r1, g1, b1, r2, g2, b2;

				//darken all colors by about 75%
				r1=(GetRValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
				g1=(GetGValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
				b1=(GetBValue(CAppSettings::AmbientTopColor)>>2)/255.0f;

				r2=(GetRValue(CAppSettings::AmbientBottomColor)>>2)/255.0f;
				g2=(GetGValue(CAppSettings::AmbientBottomColor)>>2)/255.0f;
				b2=(GetBValue(CAppSettings::AmbientBottomColor)>>2)/255.0f;

				sprintf(ambient_color, "ambient up=(R=%f G=%f B=%f), ambient down=(R=%f G=%f B=%f)", 
					r1, g1, b1, r2, g2, b2);
				
				HC_Set_Color(ambient_color);
				HC_Define_System_Options("disable ambient material");

				if(CAppSettings::UseAmbientUpVector)
				{
					sprintf(ropt, "ambient up vector = (%f, %f, %f)",
					CAppSettings::AmbientUpVector.x, CAppSettings::AmbientUpVector.y, 
					CAppSettings::AmbientUpVector.z);
					HC_Set_Rendering_Options(ropt);
				}
				else
				{
					HC_Set_Rendering_Options("no ambient up vector");
				}

			}
			else
			{
				float r1, g1, b1;

				//darken all colors by about 75%
				r1=(GetRValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
				g1=(GetGValue(CAppSettings::AmbientTopColor)>>2)/255.0f;
				b1=(GetBValue(CAppSettings::AmbientTopColor)>>2)/255.0f;

				sprintf(ambient_color, "ambient=(R=%f G=%f B=%f)", r1, g1, b1);
				HC_Set_Color(ambient_color);
				HC_Set_Rendering_Options("no ambient up vector");
				HC_Define_System_Options("no disable ambient material");
			}

			HCLOCALE(sprintf(ropt, "gooch options = (diffuse weight = %f, color range=(0.0, %f), color map segment = `./overwrite/lights/gooch_color_map_segment`)",
				CAppSettings::GoochWeight, CAppSettings::GoochColorHigh));
			HC_Set_Rendering_Options(ropt);			
		HC_Close_Segment();

		sprintf(dopt, "bloom = (%s, strength=%f, blur=%d, shape=%s)", 
			(CAppSettings::UseBloom ? "on" : "off"), 
			CAppSettings::BloomStrength, 
			CAppSettings::BloomBlur,
			(CAppSettings::BloomShape == RadialBloom ? "radial" : "star")); 
		
		HC_Open_Segment_By_Key(pActiveView->GetViewKey());
			HC_Set_Driver_Options(dopt);
		HC_Close_Segment();

		pBaseView->SetSuppressUpdate(false);
		pBaseView->Update();
	}

	UpdateLightScaleFactor();
	UpdateAmbientColors();
	UpdateBloom();
}

void LightingOptionsPage::OnButtonReset()
{
	m_bHemisphericAmbient = bool2BOOL(CAppSettings::DefaultHemisphericAmbient);
	m_clrbtnAmbientTop.currentcolor = CAppSettings::DefaultAmbientTopColor;
	m_clrbtnAmbientBottom.currentcolor = CAppSettings::DefaultAmbientBottomColor;
	m_UseAmbientUpVector = bool2BOOL(CAppSettings::DefaultUseAmbientUpVector);
	m_AmbientUpVector = CAppSettings::DefaultAmbientUpVector;

	m_bLightFollowsCamera = bool2BOOL(CAppSettings::DefaultLightFollowsCamera);
	m_bLightScaling = bool2BOOL(CAppSettings::DefaultbLightScaling);
	m_fLightScaleFactor	= CAppSettings::DefaultLightScaleFactor/100000.f;
	m_csLightCount = LightCountInt2CString(CAppSettings::DefaultLightCount);
	
	m_clrbtnGooch1.currentcolor = CAppSettings::DefaultGoochColor1;
	m_clrbtnGooch2.currentcolor = CAppSettings::DefaultGoochColor2;
	m_clrbtnGooch3.currentcolor = CAppSettings::DefaultGoochColor3;
	m_clrbtnGooch4.currentcolor = CAppSettings::DefaultGoochColor4;
	m_clrbtnGooch5.currentcolor = CAppSettings::DefaultGoochColor5;
	m_clrbtnGooch6.currentcolor = CAppSettings::DefaultGoochColor6;

	m_GoochColorMap = CAppSettings::DefaultGoochColorMap;
	m_GoochWeight = CAppSettings::DefaultGoochWeight;
	m_GoochColorHigh = CAppSettings::DefaultGoochColorHigh;

	m_bUseBloom = bool2BOOL(CAppSettings::DefaultUseBloom);
	m_fBloomStrength = CAppSettings::DefaultBloomStrength;
	m_BloomBlur = CAppSettings::DefaultBloomBlur;
	m_csBloomShape = BloomShapeEnum2CString(CAppSettings::DefaultBloomShape);	

	UpdateData(FALSE);
	UpdateLightScaleFactor();
	UpdateAmbientColors();	
	UpdateBloom();

	// the color buttons needs redraw to reflect new colors - refresh here
	RedrawWindow();
}

void LightingOptionsPage::OnButtonApply()
{
	UpdateData(TRUE);
	ApplySettings();
}

void LightingOptionsPage::OnCheckHemisphericAmbient()
{
	UpdateAmbientColors();
}

void LightingOptionsPage::UpdateAmbientColors()
{
	CButton* pCHA = (CButton*)GetDlgItem(IDC_HEMISPHERIC_AMBIENT);
	CButton* pA2T = (CButton*)GetDlgItem(IDC_TEXT_AMBIENT_COLOR_2);
	CButton* pA2B = (CButton*)GetDlgItem(IDC_BUTTON_COLOR_AMBIENT_BOTTOM);

	CButton* pCAUV = (CButton*)GetDlgItem(IDC_CHECK_AMBIENT_UP_VECTOR);
	CButton* pCAUX = (CButton*)GetDlgItem(IDC_EDIT_AMBIENT_UP_X);
	CButton* pCAUY = (CButton*)GetDlgItem(IDC_EDIT_AMBIENT_UP_Y);
	CButton* pCAUZ = (CButton*)GetDlgItem(IDC_EDIT_AMBIENT_UP_Z);
	CButton* pCAUXT = (CButton*)GetDlgItem(IDC_EDIT_AMBIENT_UP_X_TXT);
	CButton* pCAUYT = (CButton*)GetDlgItem(IDC_EDIT_AMBIENT_UP_Y_TXT);
	CButton* pCAUZT = (CButton*)GetDlgItem(IDC_EDIT_AMBIENT_UP_Z_TXT);

	
	ASSERT( pCHA );
	ASSERT( pA2T );
	ASSERT( pA2B );	

	ASSERT( pCAUV );	
	ASSERT( pCAUX );	
	ASSERT( pCAUY );	
	ASSERT( pCAUZ );	
	ASSERT( pCAUXT );	
	ASSERT( pCAUYT );	
	ASSERT( pCAUZT );	

	if( pCHA->GetCheck())
	{
		pA2T->EnableWindow(1);
		pA2B->EnableWindow(1);
		pCAUV->EnableWindow(1);

		if(pCAUV->GetCheck())
		{
			pCAUX->EnableWindow(1);
			pCAUY->EnableWindow(1);
			pCAUZ->EnableWindow(1);

			pCAUXT->EnableWindow(1);
			pCAUYT->EnableWindow(1);
			pCAUZT->EnableWindow(1);
		}
		else
		{
			pCAUX->EnableWindow(0);
			pCAUY->EnableWindow(0);
			pCAUZ->EnableWindow(0);

			pCAUXT->EnableWindow(0);
			pCAUYT->EnableWindow(0);
			pCAUZT->EnableWindow(0);
		}
	}
	else
	{
		pA2T->EnableWindow(0);
		pA2B->EnableWindow(0);
		pCAUV->EnableWindow(0);

		pCAUX->EnableWindow(0);
		pCAUY->EnableWindow(0);
		pCAUZ->EnableWindow(0);

		pCAUXT->EnableWindow(0);
		pCAUYT->EnableWindow(0);
		pCAUZT->EnableWindow(0);
	}	
	
	RedrawWindow();
}

void LightingOptionsPage::OnCheckBloom()
{
	UpdateBloom();
}

void LightingOptionsPage::UpdateBloom()
{
	CButton*  pCkBloom = (CButton*) GetDlgItem(IDC_CHECK_BLOOM);
	CButton*  pStrt = (CButton*) GetDlgItem(IDC_BLOOM_STRENGTH_TEXT);
	CButton*  pStre = (CButton*) GetDlgItem(IDC_BLOOM_STRENGTH_EDIT);
	CButton*  pBlurt = (CButton*) GetDlgItem(IDC_BLOOM_BLUR_TEXT);
	CButton*  pBlure = (CButton*) GetDlgItem(IDC_BLOOM_BLUR_EDIT);
	CButton*  pShapet = (CButton*) GetDlgItem(IDC_BLOOM_SHAPE_TEXT);
	CButton*  pShapec = (CButton*) GetDlgItem(IDC_BLOOM_SHAPE_COMBO);

	ASSERT( pCkBloom );
	ASSERT( pStrt );	
	ASSERT( pStre );	
	ASSERT( pBlurt );	
	ASSERT( pBlure );	
	ASSERT( pShapet );	
	ASSERT( pShapec );	

	pStrt->EnableWindow(pCkBloom->GetCheck());
	pStre->EnableWindow(pCkBloom->GetCheck());
	pBlurt->EnableWindow(pCkBloom->GetCheck());
	pBlure->EnableWindow(pCkBloom->GetCheck());
	pShapet->EnableWindow(pCkBloom->GetCheck());
	pShapec->EnableWindow(pCkBloom->GetCheck());
}


void LightingOptionsPage::OnCheckLightScaleFactor()
{
	UpdateLightScaleFactor();
}

void LightingOptionsPage::UpdateLightScaleFactor()
{
	CButton* pCSM = (CButton*) GetDlgItem(IDC_CHECK_LIGHT_SCALING);
	CButton* pESM = (CButton*)GetDlgItem(IDC_EDIT_LIGHT_SCALE_FACTOR);
	ASSERT( pCSM );
	ASSERT( pESM );	

	if( pCSM->GetCheck() == 0 )
	{
		//pESM->SetCheck(0);
		pESM->EnableWindow(0);
		GetDlgItem(IDC_SCALE_FACTOR_TEXT)->EnableWindow(0);
	}
	else
	{
		pESM->EnableWindow(1);
		GetDlgItem(IDC_SCALE_FACTOR_TEXT)->EnableWindow(1);
	}	
}


/////////////////////////////////////////////////////////////////////////////
// CameraOptionsPage property page


CameraOptionsPage::CameraOptionsPage(CWnd* pParent /*=NULL*/)
: HOptionsPage(CameraOptionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CameraOptionsPage)
	m_bSmoothTransition = TRUE;
	m_csProjectionMode	= _T("Orthographic");
	m_fNearLimit		= 0.f;
	m_csFrontViewAxis	= _T("");
	m_csTopViewAxis		= _T("");
	m_bHandedness		= TRUE;
	m_bNavPanel			= TRUE;
	//}}AFX_DATA_INIT
}

void CameraOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	HOptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CameraOptionsPage)
	DDX_Check(pDX, IDC_CHECK_SMOOTH_TRANSITION, m_bSmoothTransition);
	DDX_CBString(pDX, IDC_COMBO_PROJECTION, m_csProjectionMode);
	DDX_Text(pDX, IDC_EDIT_CAMERA_NEAR_LIMIT, m_fNearLimit);
	DDV_MinMaxFloat(pDX, m_fNearLimit, -1.f, 1.f);
	DDX_CBString(pDX, IDC_COMBO_FRONT_VIEW_AXIS, m_csFrontViewAxis);
	DDX_CBString(pDX, IDC_COMBO_TOP_VIEW_AXIS, m_csTopViewAxis);
	DDX_Check(pDX, IDC_CHECK_NAVIGATION_PANEL, m_bNavPanel);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CameraOptionsPage, HOptionsPage)
	//{{AFX_MSG_MAP(CameraOptionsPage)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_WORLD_HANDEDNESS_RIGHT, OnClickedRadioRightHanded)
	ON_BN_CLICKED(IDC_WORLD_HANDEDNESS_LEFT, OnClickedRadioLeftHanded)
	//}}AFX_MSG_MAP
 END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CameraOptionsPage message handlers
static void GetAllViewAxis(CString axis, CString &front, CString &top)
{
	front = axis.Left(8);
	top = axis.Right(8);
}

static CString ProjectionModeEnum2CString(ProjMode proj_mode)
{
	if( proj_mode == ProjUnknown )
		return "Unknown";
	else if( proj_mode == ProjPerspective )
		return "Perspective";
	else if( proj_mode == ProjOrthographic )
		return "Orthographic";
	else if( proj_mode == ProjStretched )
		return "Stretched";
	else
	{
		// should never be here
		ASSERT(0);
		return "";
	}
}
static ProjMode ProjectionModeCString2Enum(CString proj_mode)
{
	if( proj_mode ==  "Unknown")
		return ProjUnknown;
	else if( proj_mode == "Perspective" )
		return ProjPerspective;
	else if( proj_mode ==  "Orthographic")
		return ProjOrthographic;
	else if( proj_mode ==  "Stretched")
		return ProjStretched;
	else
	{
		// should never be here
		ASSERT(0);
		return ProjOrthographic;
	}
}

void CameraOptionsPage::ApplySettings()
{
	CAppSettings::bSmoothTransition = BOOL2bool(m_bSmoothTransition);
	CAppSettings::NearCameraLimit = m_fNearLimit*100000.f;
	CAppSettings::ViewAxis = m_csFrontViewAxis + " " + m_csTopViewAxis;
	CAppSettings::bWorldHandedness = BOOL2bool(m_bHandedness);
	CAppSettings::NavigationPanel = BOOL2bool(m_bNavPanel);

	// apply this setting only if it has changed, this will avoid the loss 
	// of markup data - HBaseView->SetProjMode() causes CameraPositionChanged which 
	// vaporizes the markup data.
	ProjMode new_proj_mode = ProjectionModeCString2Enum(m_csProjectionMode);
	
	// Get the active view to apply the new settings
	CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame();
	assert(pChild);
	CSolidHoopsView* pActiveView = (CSolidHoopsView *)pChild->GetActiveView();

	if (pActiveView && pActiveView->GetSolidView())
	{
		HBaseOperator * op = pActiveView->GetSolidView()->GetOperator();
		HBaseView * pBaseView = pActiveView->GetHoopsView();
		if(!pBaseView)
		{
			return;
		}
		HSelectionSet* pSelSet = pBaseView->GetSelection();
		assert(pSelSet);

		pBaseView->SetSuppressUpdate(true);

		if (op && strcmp(op->GetName(), "HOpCameraWalk") == 0)
			pActiveView->SetWalkOperator();

		if( new_proj_mode != CAppSettings::ProjectionMode )
		{
			CAppSettings::ProjectionMode = new_proj_mode;
			if(pBaseView)
				// apply the new projection mode 
				pBaseView->SetProjMode(CAppSettings::ProjectionMode);
		}

		HC_Open_Segment_By_Key(pBaseView->GetSceneKey());
			HC_Set_Camera_Near_Limit(m_fNearLimit);
		HC_Close_Segment();

		pBaseView->SetHandedness((CAppSettings::bWorldHandedness ? HandednessRight : HandednessLeft), true);
		
		pActiveView->SetViewAxis();
		
		pBaseView->SetSuppressUpdate(false);
		pBaseView->Update();
	}

}


void CameraOptionsPage::OnOK()
{
	ApplySettings();
	HOptionsPage::OnOK();
}

void CameraOptionsPage::OnButtonApply() 
{
	UpdateData(true);
	ApplySettings();
}


BOOL CameraOptionsPage::OnInitDialog() 
{
	HOptionsPage::OnInitDialog();
	m_bSmoothTransition = bool2BOOL(CAppSettings::bSmoothTransition);
	m_csProjectionMode	= ProjectionModeEnum2CString(CAppSettings::ProjectionMode);
	m_fNearLimit		= CAppSettings::NearCameraLimit/100000.f;

	GetAllViewAxis(CAppSettings::ViewAxis, m_csFrontViewAxis, m_csTopViewAxis);
	m_bHandedness		= bool2BOOL(CAppSettings::bWorldHandedness);
	m_bNavPanel			= bool2BOOL(CAppSettings::NavigationPanel);

	SetHandednessRadio();
	UpdateData(FALSE);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CameraOptionsPage::OnButtonReset() 
{
	m_bSmoothTransition = bool2BOOL(CAppSettings::DefaultbSmoothTransition);
	m_csProjectionMode	= ProjectionModeEnum2CString(CAppSettings::DefaultProjectionMode);
	m_fNearLimit		= CAppSettings::DefaultNearCameraLimit/100000.f;
	GetAllViewAxis(CAppSettings::DefaultViewAxis, m_csFrontViewAxis, m_csTopViewAxis);
	m_bHandedness		= bool2BOOL(CAppSettings::DefaultbWorldHandedness);
	m_bNavPanel			= bool2BOOL(CAppSettings::DefaultNavigationPanel);

	SetHandednessRadio();
	UpdateData(FALSE);
}


void CameraOptionsPage::SetHandednessRadio()
{
	if(m_bHandedness)
	{
		((CButton*)GetDlgItem(IDC_WORLD_HANDEDNESS_RIGHT))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_WORLD_HANDEDNESS_LEFT))->SetCheck(BST_UNCHECKED);
		OnClickedRadioRightHanded();
	}
	else
	{
		((CButton*)GetDlgItem(IDC_WORLD_HANDEDNESS_LEFT))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_WORLD_HANDEDNESS_RIGHT))->SetCheck(BST_UNCHECKED);
		OnClickedRadioLeftHanded();
	}
}

void CameraOptionsPage::OnClickedRadioRightHanded()
{
	m_bHandedness=true;
}

void CameraOptionsPage::OnClickedRadioLeftHanded()
{
	m_bHandedness=false;
}
