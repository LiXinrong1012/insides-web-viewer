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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CAppSettings.cpp,v 1.215 2010-11-30 21:02:12 nathan Exp $
//

#include "StdAfx.h"
#include "BStream.h"
#include "CAppSettings.h"
#include "CSolidHoopsApp.h"

extern CSolidHoopsApp theApp;

void CAppSettings::ReadSettingsFromRegistry()
{
	theApp.ReadSettingsFromRegistry();
}

void CAppSettings::WriteSettingsToRegistry()
{
	theApp.WriteSettingsToRegistry();
}

void CAppSettings::CommitAllOptions()
{
	theApp.CommitAllOptions();
}

void CAppSettings::RefreshAllOptions()
{
	theApp.RefreshAllOptions();
}

void CAppSettings::ImportOptions(CString const & fname)
{
	theApp.ImportOptions(fname);
}

void CAppSettings::ExportOptions(CString const & fname)
{
	theApp.ExportOptions(fname);
}

void CAppSettings::CheckHoopsDriver()
{
	char const * drivers[] = {
		"dx9",
		"opengl",
		"opengl2",
		"msw",
	};

	/* If the our current driver isn't found, find a new one. */
	if(!HC_QShow_Existence(H_FORMAT_TEXT("/driver/%s", H_ASCII_TEXT(HoopsDriver)), "self")){
		for(int i = 0; i < 4; ++i){
			if(HC_QShow_Existence(H_FORMAT_TEXT("/driver/%s", drivers[i]), "self")){
				HoopsDriver = H_TEXT(drivers[i]);
				break;
			}
		}
	}
}

//--- Main
CString CAppSettings::CompanyName		=	"Tech Soft 3D";
CString CAppSettings::RegOptionsSection	=	"Options";

//-- Near Camera Limit
int CAppSettings::NearCameraLimit			= 0;
int CAppSettings::DefaultNearCameraLimit	= 0;
CString CAppSettings::NearCameraLimitEntry	= "Near Camera Limit";

//-- Light Scaling
int CAppSettings::LightScaleFactor			= 100000;
int CAppSettings::DefaultLightScaleFactor	= 100000;
CString CAppSettings::LightScaleFactorEntry	= "Light Scale Factor";

bool CAppSettings::EmbedHSFThumbnail			= false;			
bool CAppSettings::DefaultEmbedHSFThumbnail		= true;
CString CAppSettings::EmbedHSFThumbnailEntry	= "Embed HSF Thumbnail";

bool CAppSettings::EmbedMaterials				= false;			
bool CAppSettings::DefaultEmbedMaterials		= false;
CString CAppSettings::EmbedMaterialsEntry		= "Embed Materials";

bool CAppSettings::HemisphericAmbient			= false;			
bool CAppSettings::DefaultHemisphericAmbient	= false;
CString CAppSettings::HemisphericAmbientEntry	= "Hemispheric Ambient";

COLORREF CAppSettings::AmbientTopColor			= RGB(1.0000*255,1.0000*255, 1.0000*255);
COLORREF CAppSettings::DefaultAmbientTopColor	= RGB(1.0000*255,1.0000*255, 1.0000*255);
CString CAppSettings::AmbientTopColorEntry		= "Ambient Color 1";

COLORREF CAppSettings::AmbientBottomColor		 = RGB(1.0000*255,1.0000*255, 1.0000*255);
COLORREF CAppSettings::DefaultAmbientBottomColor = RGB(1.0000*255,1.0000*255, 1.0000*255);
CString CAppSettings::AmbientBottomColorEntry	 = "Ambient Color 2";

bool CAppSettings::LightFollowsCamera			 = true;			
bool CAppSettings::DefaultLightFollowsCamera	 = true;
CString CAppSettings::LightFollowsCameraEntry	 = "Light Follows Camera";

bool CAppSettings::UseBloom						 = false;
bool CAppSettings::DefaultUseBloom				 = false;
CString CAppSettings::UseBloomEntry				 = "Use Bloom";

float CAppSettings::BloomStrength				 = 1.0f;
float CAppSettings::DefaultBloomStrength		 = 1.0f;
CString CAppSettings::BloomStrengthEntry		 = "Bloom Strength";

int CAppSettings::BloomBlur						 = 5;
int CAppSettings::DefaultBloomBlur				 = 5;
CString CAppSettings::BloomBlurEntry			 = "Bloom Blur";

HBloomShape CAppSettings::BloomShape			 = RadialBloom;
HBloomShape CAppSettings::DefaultBloomShape		 = RadialBloom;
CString CAppSettings::BloomShapeEntry			 = "Bloom Shape";

int CAppSettings::LightCount					 = 1;
int CAppSettings::DefaultLightCount				 = 1;
CString CAppSettings::LightCountEntry			 = "Light Count";

//-- Print Options Settings

CString CAppSettings::OutputWidthEntry		= "Output Width";
CString CAppSettings::OutputHeightEntry		= "Output Height";
int CAppSettings::OutputWidth				= 1024;
int CAppSettings::OutputHeight				= 768;
int CAppSettings::DefaultOutputWidth		= 1024;
int CAppSettings::DefaultOutputHeight		= 768;

CString CAppSettings::PaperWidthEntry		= "Paper Width";
CString CAppSettings::PaperHeightEntry		= "Paper Height";
float CAppSettings::PaperWidth				= 8.500;
float CAppSettings::PaperHeight				= 11.000;
float CAppSettings::DefaultPaperWidth		= 8.500;
float CAppSettings::DefaultPaperHeight		= 11.000;

int CAppSettings::DPI						= 300;
int CAppSettings::DefaultDPI				= 300;
CString CAppSettings::DPIEntry				= "Output DPI";

HImageOutputOptions CAppSettings::ImageOpt	= HUseWindowSize;
HImageOutputOptions CAppSettings::DefaultImageOpt = HUseWindowSize;
CString CAppSettings::ImageOptEntry			= "Image Output";

HDocOutputOptions CAppSettings::DocOpt		= HWYSIWYG;
HDocOutputOptions CAppSettings::DefaultDocOpt = HWYSIWYG;
CString CAppSettings::DocOptEntry			= "Document Options";

CString CAppSettings::ForceGrayscaleEntry	= "Output Force Grayscale";
bool CAppSettings::ForceGrayscale			= false;
bool CAppSettings::DefaultForceGrayscale	= false;

CString CAppSettings::bConserveMemoryEntry	= "Print Full Resolution Image";
bool CAppSettings::bConserveMemory			= false;
bool CAppSettings::DefaultbConserveMemory	= false;

CString CAppSettings::bUseWindowColorEntry	= "Output Window Color";
bool CAppSettings::bUseWindowColor			= false;
bool CAppSettings::DefaultbUseWindowColor	= false;

//-- Geometry Settings
	
int CAppSettings::Budget					= 512;
int CAppSettings::DefaultBudget				= 512;
CString CAppSettings::BudgetEntry			= "Curve Budget";

int CAppSettings::ContinuedBudget			= 0;
int CAppSettings::DefaultContinuedBudget	= 0;
CString CAppSettings::ContinuedBudgetEntry	= "Curve Continued Budget";

int CAppSettings::MaxDeviation				= 0;
int CAppSettings::DefaultMaxDeviation		= 0;
CString CAppSettings::MaxDeviationEntry		= "Curve Maximum Deviation";

int CAppSettings::MaxAngle					= 200000;
int CAppSettings::DefaultMaxAngle			= 200000;
CString CAppSettings::MaxAngleEntry			= "Curve Maximum Angle";

int CAppSettings::MaxLength					= 1000;
int CAppSettings::DefaultMaxLength			= 1000;
CString CAppSettings::MaxLengthEntry		= "Curve Maximum Segment Length";

bool CAppSettings::bViewIndependent			= true;
bool CAppSettings::DefaultbViewIndependent	= true;
CString CAppSettings::bViewIndependentEntry	= "Curve Settings Are View Independent";


//-- General Settings (related to Display etc.)

CString CAppSettings::HoopsDriverEntry		= "Hoops Driver";
CString CAppSettings::HoopsDriver			= "dx9";
CString CAppSettings::DefaultHoopsDriver	= "dx9";

CString CAppSettings::DriverForceSoftwareEntry		= "Force Software";
bool CAppSettings::bDriverForceSoftware				= false;
bool CAppSettings::DefaultbDriverForceSoftware		= false;

CString CAppSettings::DriverDisplayStatsEntry		= "Display Stats";
bool CAppSettings::bDriverDisplayStats				= false;
bool CAppSettings::DefaultbDriverDisplayStats		= false;


CString CAppSettings::bAntiAliasingEntry			= "Anti-aliasing";
bool CAppSettings::bAntiAliasing					= true;
bool CAppSettings::DefaultbAntiAliasing				= true;
				

CString CAppSettings::DisplayAxisTriadEntry = "Axis Triad";
bool CAppSettings::bDisplayAxisTriad		= true;
bool CAppSettings::DefaultbDisplayAxisTriad	= true;

CString CAppSettings::BackplaneCullingEntry = "Backplane Culling";
bool CAppSettings::bBackplaneCulling		= false;
bool CAppSettings::DefaultbBackplaneCulling	= false;

CString CAppSettings::CoordinateSystemHandednessEntry				= "Coordinate System Handedness";
HandednessMode CAppSettings::CoordinateSystemHandedness				= HandednessRight;
HandednessMode CAppSettings::DefaultCoordinateSystemHandedness		= HandednessRight;

CString CAppSettings::ShadowRenderingEntry		= "Shadow Rendering Mode";
HShadowRenderingMode CAppSettings::ShadowRenderingMode		= SoftwareOpenglShadow;
HShadowRenderingMode CAppSettings::DefaultShadowRenderingMode	= SoftwareOpenglShadow;

CString CAppSettings::ViewAxisEntry		= "View Axis";
CString CAppSettings::ViewAxis		= " 1  0  0  0  1  0  0  0  1";
CString CAppSettings::DefaultViewAxis	= " 1  0  0  0  1  0  0  0  1";


CString CAppSettings::TransparencySortingEntry		= "Transparency Sorting";
CString CAppSettings::TransparencySorting		= "depth peeling";
CString CAppSettings::DefaultTransparencySorting	= "depth peeling";

CString CAppSettings::TransparencyDepthPeelingLayersEntry		= "Transparency Depth Peeling Layers";
CString CAppSettings::TransparencyDepthPeelingLayers		= "1";
CString CAppSettings::DefaultTransparencyDepthPeelingLayers	= "1";

bool CAppSettings::DepthWriting								= false;
bool CAppSettings::DefaultDepthWriting						= false;
CString CAppSettings::DepthWritingEntry						= "Depth Writing";

CString CAppSettings::AntialiasingLevelEntry		= "Antialiasing Level";
int CAppSettings::AntialiasingLevel		= 4;
int CAppSettings::DefaultAntialiasingLevel	= 4;


CString CAppSettings::TransparencyStyleEntry	= "Transparency Style";
CString CAppSettings::TransparencyStyle			= "blended";
CString CAppSettings::DefaultTransparencyStyle	= "blended";

	
CString CAppSettings::RenderModeEntry		= "Default Render Mode";
HRenderMode CAppSettings::RenderMode		= HRenderGouraud;
HRenderMode CAppSettings::DefaultRenderMode	= HRenderGouraud;

CString CAppSettings::PolygonHandednessEntry			= "Polygon Handedness";
ModelHandedness CAppSettings::PolygonHandedness			= HandednessSetLeft;
ModelHandedness CAppSettings::DefaultPolygonHandedness	= HandednessSetLeft;

CString CAppSettings::SmoothTransitionEntry		= "Smooth Transition";
bool CAppSettings::bSmoothTransition			= true;
bool CAppSettings::DefaultbSmoothTransition		= true;

CString CAppSettings::bLightScalingEntry		= "Light Scaling";
bool CAppSettings::bLightScaling				= true;
bool CAppSettings::DefaultbLightScaling			= true;

CString CAppSettings::GoochColorMap				= "blue, red";
CString CAppSettings::DefaultGoochColorMap		= "blue, red";
CString CAppSettings::GoochColorMapEntry		= "Gooch Color Map";

bool CAppSettings::UseAmbientUpVector			= false;
bool CAppSettings::DefaultUseAmbientUpVector	= false;
CString CAppSettings::UseAmbientUpVectorEntry	= "Use Ambient Up Vector";

HPoint CAppSettings::AmbientUpVector			= HPoint(0.0f, 1.0f, 0.0f);
HPoint CAppSettings::DefaultAmbientUpVector		= HPoint(0.0f, 1.0f, 0.0f);
CString CAppSettings::AmbientUpVectorEntry		= "Ambient Up Vector";

COLORREF CAppSettings::GoochColor1				= RGB(255.0, 105.0, 180.0);
COLORREF CAppSettings::DefaultGoochColor1		= RGB(255.0, 105.0, 180.0);
CString CAppSettings::GoochColor1Entry			= "Gooch Color 1";

COLORREF CAppSettings::GoochColor2				= RGB(60.0, 179.0, 113.0);
COLORREF CAppSettings::DefaultGoochColor2		= RGB(60.0, 179.0, 113.0);
CString CAppSettings::GoochColor2Entry			= "Gooch Color 2";

COLORREF CAppSettings::GoochColor3				= RGB(255.0, 255.0, 255.0);
COLORREF CAppSettings::DefaultGoochColor3		= RGB(255.0, 255.0, 255.0);
CString CAppSettings::GoochColor3Entry			= "Gooch Color 3";

COLORREF CAppSettings::GoochColor4				= RGB(255.0, 255.0, 255.0);
COLORREF CAppSettings::DefaultGoochColor4		= RGB(255.0, 255.0, 255.0);
CString CAppSettings::GoochColor4Entry			= "Gooch Color 4";

COLORREF CAppSettings::GoochColor5				= RGB(255.0, 255.0, 255.0);
COLORREF CAppSettings::DefaultGoochColor5		= RGB(255.0, 255.0, 255.0);
CString CAppSettings::GoochColor5Entry			= "Gooch Color 5";

COLORREF CAppSettings::GoochColor6				= RGB(255.0, 255.0, 255.0);
COLORREF CAppSettings::DefaultGoochColor6		= RGB(255.0, 255.0, 255.0);
CString CAppSettings::GoochColor6Entry			= "Gooch Color 6";

float CAppSettings::GoochWeight					= 0.5f;
float CAppSettings::DefaultGoochWeight			= 0.5f;
CString CAppSettings::GoochWeightEntry			= "Gooch Weight";

float CAppSettings::GoochColorHigh				= 2.0f;
float CAppSettings::DefaultGoochColorHigh		= 2.0f;
CString CAppSettings::GoochColorHighEntry		= "Gooch Color Count";

CString CAppSettings::WorldHandednessEntry		= "World Handedness";
bool CAppSettings::bWorldHandedness				= true;
bool CAppSettings::DefaultbWorldHandedness		= true;

CString CAppSettings::ProjectionModeEntry		= "Projection Mode";
ProjMode CAppSettings::ProjectionMode			= ProjOrthographic;
ProjMode CAppSettings::DefaultProjectionMode	= ProjOrthographic;

bool CAppSettings::StereoMode					= false;
bool CAppSettings::DefaultStereoMode			= false;
CString CAppSettings::StereoModeEntry			= "Stereo Mode";

int CAppSettings::StereoSeparation				= 30000;
int CAppSettings::DefaultStereoSeparation		= 30000;
CString CAppSettings::StereoSeparationEntry		= "Stereo Separation";



//-- Appearance Settings (color, weight etc.)
CString CAppSettings::OverrideDefaultAppWindowPositionEntry	= "Override Default Application Window Position";
bool CAppSettings::OverrideDefaultAppWindowPosition			= false;
bool CAppSettings::DefaultOverrideDefaultAppWindowPosition	= false;

CString CAppSettings::AppWindowPositionEntry				= "Application Window Pos(upper-left.x, upper-left.y, width, height)";
CString CAppSettings::AppWindowPosition						= "10,10,600,500";
CString CAppSettings::DefaultAppWindowPosition				= "10,10,600,500";

CString CAppSettings::LineWeightEntry	= "Default Line Weight";
CString CAppSettings::LineWeight	= "1 pixels";
CString CAppSettings::DefaultLineWeight	= "1 pixels";

CString CAppSettings::WindowBackgroundTopColorEntry		= "Background Top Color";
COLORREF CAppSettings::WindowBackgroundTopColor			= RGB(0.0000*255,0.501961*255, 0.501961*255);
COLORREF CAppSettings::DefaultWindowBackgroundTopColor	= RGB(0.0000*255,0.501961*255, 0.501961*255);

CString CAppSettings::FakeHLRColorEntry					= "Fake HLR Color";
COLORREF CAppSettings::FakeHLRColor						= RGB(255, 255, 255);
COLORREF CAppSettings::DefaultFakeHLRColor				= RGB(255, 255, 255);

CString CAppSettings::WindowBackgroundBottomColorEntry		= "Background Bottom Color";
COLORREF CAppSettings::WindowBackgroundBottomColor			= RGB(1.000*255, 0.984314*255, 0.941176*255);
COLORREF CAppSettings::DefaultWindowBackgroundBottomColor	= RGB(1.000*255, 0.984314*255, 0.941176*255);

CString CAppSettings::PolygonSelectionColorEntry	= "Polygon Selection Color";	
COLORREF CAppSettings::PolygonSelectionColor		= RGB(255, 249, 0);
COLORREF CAppSettings::DefaultPolygonSelectionColor	= RGB(255, 249, 0);

CString CAppSettings::LineSelectionColorEntry		= "Line Selection Color";
COLORREF CAppSettings::LineSelectionColor			= RGB(255, 249, 0);
COLORREF CAppSettings::DefaultLineSelectionColor	= RGB(255, 249, 0);

CString CAppSettings::MarkerSelectionColorEntry		= "Marker Selection Color";
COLORREF CAppSettings::MarkerSelectionColor			= RGB(255, 249, 0);
COLORREF CAppSettings::DefaultMarkerSelectionColor	= RGB(255, 249, 0);

CString CAppSettings::SelectionColorTransparencyEntry	= "Selection Color Transparency";
int CAppSettings::SelectionColorTransparency			= 0;
int CAppSettings::DefaultSelectionColorTransparency		= 0;


CString CAppSettings::MarkupColorEntry				= "Markup Color";
COLORREF CAppSettings::MarkupColor					= RGB(255, 0, 0);
COLORREF CAppSettings::DefaultMarkupColor			= RGB(255, 0, 0);

CString CAppSettings::ShadowColorEntry				= "Shadow Color";
COLORREF CAppSettings::ShadowColor					= RGB(45, 45, 45);
COLORREF CAppSettings::DefaultShadowColor			= RGB(45, 45, 45);

CString CAppSettings::GreekingLimitEntry			= "Greeking Limit";
int	CAppSettings::GreekingLimit						= 6000;	// Greeking limit * 1000 (to store float as int)
int	CAppSettings::DefaultGreekingLimit				= 6000;	// Greeking limit * 1000 (to store float as int)

CString CAppSettings::GreekingMode					= "Box";
CString CAppSettings::DefaultGreekingMode			= "Box";
CString CAppSettings::GreekingModeEntry				= "Greeking Mode";

CString CAppSettings::GreekingUnits					= "px";
CString CAppSettings::DefaultGreekingUnits			= "px";
CString CAppSettings::GreekingUnitsEntry			= "Greeking Units";

CString CAppSettings::MarkupWeightEntry				= "Markup Weight";
int	CAppSettings::MarkupWeight						= 400;	// Markup line weight * 100 (to store float as int)
int	CAppSettings::DefaultMarkupWeight				= 400;	// Markup line weight * 100 (to store float as int)


CString CAppSettings::WalkAvatarHeightEntry				= "Avatar Height";
int	CAppSettings::WalkAvatarHeight						= 200;	// avatar height * 100 (to store float as int)
int	CAppSettings::DefaultWalkAvatarHeight				= 200;	// avatar height * 100 (to store float as int)

CString CAppSettings::WalkStepHeightUpEntry				= "Step Height up";
int	CAppSettings::WalkStepHeightUp						= 20;	// avatar height * 100 (to store float as int)
int	CAppSettings::DefaultWalkStepHeightUp				= 20;	// avatar height * 100 (to store float as int)

bool CAppSettings::DoubleBuffer							= true;
bool CAppSettings::DefaultDoubleBuffer					= true;
CString CAppSettings::DoubleBufferEntry					= "Double Buffering";

CString CAppSettings::CullingThresholdEntry				= "CullingThreshold";
int	CAppSettings::CullingThreshold						= 10;
int	CAppSettings::DefaultCullingThreshold				= 10;	

CString CAppSettings::CullingThresholdSetEntry			= "CullingThresholdSet";
int	CAppSettings::CullingThresholdSet					= 1;
int	CAppSettings::DefaultCullingThresholdSet			= 1;	

float CAppSettings::FramerateTime							= 0.05f;
float CAppSettings::DefaultFramerateTime					= 0.05f;
CString CAppSettings::FramerateTimeEntry					= "Defer Time";

CString CAppSettings::DynamicAdjustmentEntry			= "Dynamic Adjustment";
int	CAppSettings::DynamicAdjustment						= 1;
int	CAppSettings::DefaultDynamicAdjustment				= 1;	

CString CAppSettings::UseLodsEntry						= "Use Lods";
int	CAppSettings::UseLods								= 0;
int	CAppSettings::DefaultUseLods						= 0;	

FramerateMode CAppSettings::CurrentFramerateMode						= FramerateFixed;
FramerateMode CAppSettings::DefaultCurrentFramerateMode				= FramerateFixed;
CString CAppSettings::CurrentFramerateModeEntry						= "Framerate Mode";

int	CAppSettings::MaxThreshold						= 100;				
int	CAppSettings::DefaultMaxThreshold				= 100;
CString	CAppSettings::MaxThresholdEntry				= "Max Threshold";

int CAppSettings::HardCutoff						= 10;
int CAppSettings::DefaultHardCutoff					= 10;
CString CAppSettings::HardCutoffEntry				= "Hard Cutoff";

CString CAppSettings::DetailStepsEntry				= "DetailSteps";
int	CAppSettings::DetailSteps						= 15;
int	CAppSettings::DefaultDetailSteps				= 15;	

bool CAppSettings::UseFramerate						= false;
bool CAppSettings::DefaultUseFramerate				= false;
CString CAppSettings::UseFramerateEntry				= "Use Framerate";

CString CAppSettings::WalkStepHeightDownEntry				= "Step Height Down";
int	CAppSettings::WalkStepHeightDown						= 80;	// avatar height * 100 (to store float as int)
int	CAppSettings::DefaultWalkStepHeightDown				= 80;	// avatar height * 100 (to store float as int)


CString CAppSettings::ShadowResEntry				= "Shadow Resolution";
int	CAppSettings::ShadowRes					= 64;	
int	CAppSettings::DefaultShadowRes				= 64;	

CString CAppSettings::ShadowBlurEntry				= "Shadow Blur";
int	CAppSettings::ShadowBlur				= 4;	
int	CAppSettings::DefaultShadowBlur				= 4;	

CString CAppSettings::DisplayListEntry				= "Display List";
DisplayListType CAppSettings::DisplayList			= DisplayListSegment;
DisplayListType CAppSettings::DefaultDisplayList	= DisplayListSegment;

MultiThreadingType CAppSettings::MultiThreading		= MultiThreadingFull;
MultiThreadingType CAppSettings::DefaultMultiThreading = MultiThreadingFull;
CString CAppSettings::MultiThreadingEntry			= "Multi-Threading";

bool CAppSettings::StaticModel						= false;							
bool CAppSettings::DefaultStaticModel				= false;					
CString CAppSettings::StaticModelEntry				= "Static Model";					

bool CAppSettings::DisableEditing					= true;							
bool CAppSettings::DefaultDisableEditing			= true;					
CString CAppSettings::DisableEditingEntry			= "Disable Geometry Editing";					

bool CAppSettings::LMVModel							= false;							
bool CAppSettings::DefaultLMVModel					= false;					
CString CAppSettings::LMVModelEntry					= "LMV Model";					

bool CAppSettings::NavigationPanel					= false;							
bool CAppSettings::DefaultNavigationPanel			= false;					
CString CAppSettings::NavigationPanelEntry			= "Navigation Panel";					

CString CAppSettings::VisibilitySelectionEntry		= "Visibility Selection";
bool CAppSettings::VisibilitySelection				= false;
#ifdef HOOPS_ONLY
bool CAppSettings::DefaultVisibilitySelection		= false;
#else
bool CAppSettings::DefaultVisibilitySelection		= true;
#endif

CString CAppSettings::DynamicHighlightingEntry		= "Dynamic Highlighting";
bool CAppSettings::DynamicHighlighting				= false;
bool CAppSettings::DefaultDynamicHighlighting		= false;

CString CAppSettings::DetailSelectionEntry			= "Detail Selection";
bool CAppSettings::DetailSelection					= false;
bool CAppSettings::DefaultDetailSelection			= false;

CString CAppSettings::bUseSelectBoxEntry			= "Transparent Select Box";
bool CAppSettings::bUseSelectBox					= true;
bool CAppSettings::DefaultbUseSelectBox				= true;

CString CAppSettings::HighlightModeEntry			= "Highlight Mode";
HSelectionHighlightMode CAppSettings::HighlightMode = HighlightQuickmoves;
HSelectionHighlightMode CAppSettings::DefaultHighlightMode = HighlightQuickmoves;

float CAppSettings::TransparencyLevel				= 0.9f;			
float CAppSettings::DefaultTransparencyLevel		= 0.9f;		
CString CAppSettings::TransparencyLevelEntry		= "Transparency Level";		

int CAppSettings::RelatedSelectionLimit				= 0;
int CAppSettings::DefaultRelatedSelectionLimit		= 0;
CString CAppSettings::RelatedSelectionLimitEntry	= "Related Selection Limit";

CString CAppSettings::csRefSelType					= "Spriting";
CString CAppSettings::csDefaultRefSelType			= "Spriting";
CString CAppSettings::csRefSelTypeEntry				= "Reference Selection Type";

CString CAppSettings::TimerBasedUpdateEntry			= "Timer Based Update";
bool CAppSettings::TimerBasedUpdate					= true;
bool CAppSettings::DefaultTimerBasedUpdate			= true;

CString CAppSettings::OcclusionCullingEntry			= "Occlusion Culling";
bool CAppSettings::OcclusionCulling					= false;
bool CAppSettings::DefaultOcclusionCulling			= false;

int CAppSettings::OcclusionThreshold			= 50;
int CAppSettings::DefaultOcclusionThreshold		= 50;
CString CAppSettings::OcclusionThresholdEntry	= "Occlusion Culling Threshold";

CString CAppSettings::LineAntialiasingEntry			= "Line Antialiasing";
bool CAppSettings::LineAntialiasing					= false;
bool CAppSettings::DefaultLineAntialiasing			= false;

CString CAppSettings::TextAntialiasingEntry			= "Text Antialiasing";
bool CAppSettings::TextAntialiasing					= false;
bool CAppSettings::DefaultTextAntialiasing			= false;

CString CAppSettings::ShowDebugMenuEntry			= "Show Debug Menu";
bool CAppSettings::ShowDebugMenu				= false;
bool CAppSettings::DefaultShowDebugMenu			= false;

CString CAppSettings::HiddenLineModeEntry		= "HLR Mode";
HLRMode CAppSettings::HiddenLineMode			= FakeHiddenLine;
HLRMode CAppSettings::DefaultHiddenLineMode		= FakeHiddenLine;

CString CAppSettings::SpritingEntry				= "Spriting";
bool CAppSettings::Spriting						= true;
bool CAppSettings::DefaultSpriting				= true;

bool CAppSettings::UpdateCutGeometry			= false;	
bool CAppSettings::DefaultUpdateCutGeometry		= false;
CString CAppSettings::UpdateCutGeometryEntry	= "Update Cut Geometry";

CString CAppSettings::UpdateShadowsEntry		= "Update Shadows";
bool CAppSettings::UpdateShadows				= true;
bool CAppSettings::DefaultUpdateShadows			= true;


CString CAppSettings::ColorInterpolationEntry			= "Color Interpolation";
bool CAppSettings::bColorInterpolation				= true;	// color interpolation
bool CAppSettings::DefaultbColorInterpolation			    =	 true;	// default value


CString CAppSettings::GrayScaleSelectionEntry			= "Gray Scale Selection";
bool CAppSettings::bGrayScaleSelection				= false;	// no gray scale selection
bool CAppSettings::DefaultbGrayScaleSelection			    =	 false;	// default value

CString CAppSettings::DisplaceSelectionEntry			= "Displace Selection";
bool CAppSettings::bDisplaceSelection					= false;	// no gray scale selection
bool CAppSettings::DefaultbDisplaceSelection			 =	 false;	// default value


CString CAppSettings::WalkUseKeyboardEntry			= "Use Keyboard Walk";
bool CAppSettings::bWalkUseKeyboard					= false;	// use keyboard walk
bool CAppSettings::DefaultbWalkUseKeyboard			  =	 false;	// default value

CString CAppSettings::WalkAutomaticHeightEntry			= "Use Automatic Height";
bool CAppSettings::bWalkAutomaticHeight					= true;	// use automatic height
bool CAppSettings::DefaultbWalkAutomaticHeight			  =	 true;	// default value

CString CAppSettings::WalkSnapToFloorEntry			= "Use Snap to floor Walk";
bool CAppSettings::bWalkSnapToFloor					= false;	// use snap to floor walk
bool CAppSettings::DefaultbWalkSnapToFloor			  =	 false;	// default value

CString CAppSettings::WalkCollisionEntry			= "Use Collision Walk";
bool CAppSettings::bWalkCollision					= false;	// use collision walk
bool CAppSettings::DefaultbWalkCollision			  =	 false;	// default value

CString CAppSettings::CiIsolinesEntry				= "Color Interpolation Isolines";
bool CAppSettings::bCiIsolines						= false;	// color interpolation, isolines only
bool CAppSettings::DefaultbCiIsolines				= false;	// default value

CString CAppSettings::CiByValueEntry				= "Color Interpolation By Value";
bool CAppSettings::bCiByValue						= true;// color interpolation, by value
bool CAppSettings::DefaultbCiByValue				= true;		// default value

CString CAppSettings::HideOverlappedTextEntry		= "Hide Overlapped Text";
bool CAppSettings::bHideOverlappedText				= false;	//hide overlapped text?
bool CAppSettings::DefaultHideOverlappedText		= false;	//default value

CString CAppSettings::SplatRenderingEntry			= "Splat Rendering";
bool CAppSettings::bSplatRendering					= false;	//use splat rendering
bool CAppSettings::DefaultbSplatRendering			= false;	//default value (false)

bool CAppSettings::bFastMarkers						= true;
bool CAppSettings::DefaultbFastMarkers				= true;
CString CAppSettings::FastMarkersEntry				= "Fast Marker Drawing";

CString CAppSettings::UseGreekingEntry				= "Use Text Greeking";
bool CAppSettings::bUseGreeking						= false;	//use text greeking
bool CAppSettings::DefaultbUseGreeking				= false;	//default value

CString CAppSettings::CiByColormapIndexEntry		= "Color Interpolation By Colormap Index";
bool CAppSettings::bCiByColormapIndex				= true;	// color interpolation, by colormap index
bool CAppSettings::DefaultbCiByColormapIndex		= true;	// default value

CString CAppSettings::FontNameEntry					= "Font Name";
CString CAppSettings::FontName						= "sans serif";
CString CAppSettings::DefaultFontName				= "sans serif";

CString CAppSettings::FontSizeEntry					= "Font Size";
CString CAppSettings::FontSize						= "14";
CString CAppSettings::DefaultFontSize				= "14";

CString CAppSettings::FontUnitsEntry				= "Font Units";
CString CAppSettings::FontUnits						= "pts";
CString CAppSettings::DefaultFontUnits				= "pts";

//-- Shadow Settings

CString CAppSettings::ShadowModeEntry				= "Shadow Mode";
HShadowMode CAppSettings::ShadowMode				= HShadowNone;
HShadowMode CAppSettings::DefaultShadowMode			= HShadowNone;

bool CAppSettings::bShadowMap						= false;
bool CAppSettings::bDefaultShadowMap				= false;
CString CAppSettings::ShadowMapEntry				= "Shadow Maps";

bool CAppSettings::bReflectionPlane					= false;
bool CAppSettings::bDefaultReflectionPlane			= false;
CString CAppSettings::ReflectionPlaneEntry			= "Reflection Plane";

float CAppSettings::ReflectionOpacity				= 0.5;
float CAppSettings::DefaultReflectionOpacity		= 0.5;
CString CAppSettings::ReflectionOpacityEntry		= "Reflection Opacity";

bool CAppSettings::bReflectionFading				= true;
bool CAppSettings::bDefaultReflectionFading			= true;
CString CAppSettings::ReflectionFadingEntry			= "Reflection Fading";

bool CAppSettings::Jitter							= false;
bool CAppSettings::DefaultJitter					= false;
CString CAppSettings::JitterEntry					= "Shadow Map Jitter";

int CAppSettings::ReflectionBlur					= 1;
int CAppSettings::DefaultReflectionBlur				= 1;
CString CAppSettings::ReflectionBlurEntry			= "Reflection Blur";

float CAppSettings::ReflectionHither				= 0.f;
float CAppSettings::DefaultReflectionHither			= 0.f;
CString CAppSettings::ReflectionHitherEntry			= "Reflection Hither";

float CAppSettings::ReflectionYon					= 1.f;
float CAppSettings::DefaultReflectionYon			= 1.f;
CString CAppSettings::ReflectionYonEntry			= "Reflection Yon";

bool CAppSettings::ReflectionUseBlur				= false;
bool CAppSettings::DefaultReflectionUseBlur			= false;
CString CAppSettings::ReflectionUseBlurEntry		= "Use Reflection Blur";

bool CAppSettings::ReflectionUseAttenuation			= false;
bool CAppSettings::DefaultReflectionUseAttenuation	= false;
CString CAppSettings::ReflectionUseAttenuationEntry	= "Use Reflection Attenuation";

int CAppSettings::nSMSamples						= 4;
int CAppSettings::nDefaultSMSamples					= 4;
CString CAppSettings::SMSamplesEntry				= "Shadow Map Samples";

int CAppSettings::nSMResolution						= 2048;
int CAppSettings::nDefaultSMResolution				= 2048;
CString CAppSettings::SMResolutionEntry				= "Shadow Map Resolution";

float CAppSettings::ShadowOpacity					= 1.f;
float CAppSettings::DefaultShadowOpacity			= 1.f;
CString CAppSettings::ShadowOpacityEntry			= "Shadow Opacity";

bool CAppSettings::ViewDependentShadowMap			= true;
bool CAppSettings::DefaultViewDependentShadowMap	= true;
CString CAppSettings::ViewDependentShadowMapEntry	= "View Dependent Shadow Maps";

bool CAppSettings::UseFastAmbient					= false;
bool CAppSettings::DefaultUseFastAmbient			= false;
CString CAppSettings::UseFastAmbientEntry			= "Ambient Occlusion";

float CAppSettings::FastAmbientStrength				= 1.0f;
float CAppSettings::DefaultFastAmbientStrength		= 1.0f;
CString CAppSettings::FastAmbientStrengthEntry		= "Ambient Occlusion Strength";

bool CAppSettings::HQAmbientOcclusion				= false;
bool CAppSettings::DefaultHQAmbientOcclusion		= false;
CString CAppSettings::HQAmbientOcclusionEntry		= "Highest Quality Ambient Occlusion";

bool CAppSettings::UseFastSilhouette				= false;
bool CAppSettings::DefaultUseFastSilhouette			= false;
CString CAppSettings::UseFastSilhouetteEntry		= "Use Fast Silhouette Edges";

float CAppSettings::FastSilhouetteTolerance			= 1.0f;
float CAppSettings::DefaultFastSilhouetteTolerance	= 1.0f;
CString CAppSettings::FastSilhouetteToleranceEntry	= "Fast Silhouette Tolerance";

bool CAppSettings::HeavyExteriorSilhouette			= false;
bool CAppSettings::DefaultHeavyExteriorSilhouette	= false;
CString CAppSettings::HeavyExteriorSilhouetteEntry = "Heavy Exterior Silhouette Edges";

bool CAppSettings::IgnoreTransparency				= false;
bool CAppSettings::DefaultIgnoreTransparency		= false;
CString CAppSettings::IgnoreTransparencyEntry		= "Shadows Ignore Transparency";

bool CAppSettings::UseLightVector					= false;
bool CAppSettings::DefaultUseLightVector			= false;
CString CAppSettings::UseLightVectorEntry			= "Use Simple Shadow Light Vector";

HPoint CAppSettings::LightVector					= HPoint (0.0f, 0.0f, 1.0f);
HPoint CAppSettings::DefaultLightVector				= HPoint (0.0f, 0.0f, 1.0f);
CString CAppSettings::LightVectorEntry				= "Simple Shadow Light Vector";

//-- File Settings (import-export options)

CString	CAppSettings::ReadSimpleHsfEntry	= "Read Simplified Hsf";
bool	CAppSettings::bReadSimpleHsf		= false;
bool	CAppSettings::DefaultbReadSimpleHsf	= false;

CString CAppSettings::HsfExportVersionEntry			= "Hsf Export Version 2";
unsigned int CAppSettings::HsfExportVersion			= 0;
unsigned int CAppSettings::DefaultHsfExportVersion	= 0;

CString	CAppSettings::ExportTopolInfoEntry		= "Export Topology Info";
bool	CAppSettings::bExportTopolInfo			= false;
bool	CAppSettings::DefaultbExportTopolInfo	= false;

CString	CAppSettings::CompressVerticesEntry		= "Compress Vertices";
bool	CAppSettings::bCompressVertices			= true;
bool	CAppSettings::DefaultbCompressVertices	= true;

CString CAppSettings::NumVertexBitsEntry		= "Bits per Vertex";
unsigned int CAppSettings::NumVertexBits		= 36;
unsigned int CAppSettings::DefaultNumVertexBits	= 36;

CString	CAppSettings::CompressNormalsEntry		= "Compress Normals";
bool	CAppSettings::bCompressNormals			= true;
bool	CAppSettings::DefaultbCompressNormals	= true;

CString CAppSettings::NumNormalBitsEntry		= "Bits per Normal";
unsigned int CAppSettings::NumNormalBits		= 24;
unsigned int CAppSettings::DefaultNumNormalBits	= 24;

CString	CAppSettings::CompressParametersEntry		= "Compress Parameters";
bool	CAppSettings::bCompressParameters			= true;
bool	CAppSettings::DefaultbCompressParameters	= true;

CString CAppSettings::NumParameterBitsEntry		= "Bits per Parameter";
unsigned int CAppSettings::NumParameterBits		= 24;
unsigned int CAppSettings::DefaultNumParameterBits	= 24;

CString	CAppSettings::DWGDeviationEntry				= "DWG Facet/Curve Deviation";    
CString	CAppSettings::DWGDeviation					= "10.0";           
CString	CAppSettings::DefaultDWGDeviation			= "10.0";    

CString	CAppSettings::ImportDWGXDataEntry		= "DWG Import XData";    
bool	CAppSettings::bImportDWGXData			= false;           
bool	CAppSettings::DefaultbImportDWGXData	= false;    

CString	CAppSettings::ImportDWGviaBstreamEntry		= "DWG Import via Bstream";    
bool	CAppSettings::bImportDWGviaBstream			= true;           
bool	CAppSettings::DefaultbImportDWGviaBstream	= true;    

//For DGN

CString	CAppSettings::IgnoreInvisibleEntity		    = "DGN option of ignoring invisible entities";    
bool	CAppSettings::bIgnoreInvisibleEntities		= false;           
bool	CAppSettings::DefaultbIgnoreInvisibleEntities	= false; 

CString	CAppSettings::DGNFactorForConeEntry			    = "DGN Factor for Cone entity";    
CString	CAppSettings::DGNFactorForCone					= "10.0";           
CString	CAppSettings::DefaultDGNFactorForCone		    = "10.0"; 

CString	CAppSettings::DGNFactorForSmartSolidsEntry	    = "DGN Factor for Smart Solids";    
CString	CAppSettings::DGNFactorForSmartSolids			= "45.0";           
CString	CAppSettings::DefaultDGNFactorForSmartSolids    = "45.0"; 

//DGN

CString	CAppSettings::ExportLinesEntry		= "Export Lines";
bool	CAppSettings::bExportLines			= true;
bool	CAppSettings::DefaultbExportLines	= true;

CString	CAppSettings::ExportDictionaryEntry		= "Export Dictionary";
bool	CAppSettings::bExportDictionary			= false;
bool	CAppSettings::DefaultbExportDictionary	= false;

CString	CAppSettings::EnableInstancingEntry	= "Enable Instancing";
bool	CAppSettings::bEnableInstancing			= true;
bool	CAppSettings::DefaultbEnableInstancing	= true;

CString	CAppSettings::SaveLogFileEntry		= "Save Log File";
bool	CAppSettings::bSaveLogFile			= false;
bool	CAppSettings::DefaultbSaveLogFile	= false;


CString	CAppSettings::CompressConnectivityEntry		= "Compress Connectivity";
bool	CAppSettings::bCompressConnectivity			= true;
bool	CAppSettings::DefaultbCompressConnectivity	= true;


CString CAppSettings::ModelerExportFileVerEntry = "Modeler Export File Version 2";
#if defined(PARASOLID)
unsigned int CAppSettings::ModelerExportFileVer			= 180;
unsigned int CAppSettings::DefaultModelerExportFileVer	= 180;
#elif defined(ACIS)
unsigned int CAppSettings::ModelerExportFileVer			= 160;
unsigned int CAppSettings::DefaultModelerExportFileVer	= 160;
#elif defined(GRANITE)
unsigned int CAppSettings::ModelerExportFileVer			= 40;
unsigned int CAppSettings::DefaultModelerExportFileVer	= 40;
#else
unsigned int CAppSettings::ModelerExportFileVer			= 0;
unsigned int CAppSettings::DefaultModelerExportFileVer	= 0;
#endif

bool CAppSettings::EnableTristrips						= true;
bool CAppSettings::DefaultEnableTristrips				= true;
CString CAppSettings::EnableTristripsEntry				= "Enable Tristrips";

CString CAppSettings::PartsDirectoryEntry	= "Parts Directory";
CString CAppSettings::PartsDirectory		= "";
CString CAppSettings::DefaultPartsDirectory	= "..\\..\\datasets";

CString CAppSettings::DWGTextureDirectoryEntry	= "DWG Texture Directory";
CString CAppSettings::DWGTextureDirectory		= ".";
CString CAppSettings::DefaultDWGTextureDirectory = ".";

CString CAppSettings::MaterialLibraryDirectoryEntry		= "Material Library Directory";
CString CAppSettings::MaterialLibraryDirectory			= "..\\..\\material_library";
CString CAppSettings::DefaultMaterialLibraryDirectory	= "..\\..\\material_library";

CString CAppSettings::FlushOnLoadEntry				= "Flush On Load";
bool CAppSettings::bFlushOnLoad						= true;	
bool CAppSettings::DefaultbFlushOnLoad				= true;	

bool CAppSettings::bRestoreAnnotations			= false;
bool CAppSettings::DefaultbRestoreAnnotations	= false;
CString	CAppSettings::RestoreAnnotationsEntry	= "Restore Annotations";

bool CAppSettings::bPrcFaceEdgeVertexSelectability	= false;
bool CAppSettings::DefaultbPrcFaceEdgeVertexSelectability	= false;
CString	CAppSettings::PrcFaceEdgeVertexSelectabilityEntry	= "PRC Face Edge Vertex Selectability";


bool CAppSettings::HsfStreaming					= false;
bool CAppSettings::DefaultHsfStreaming			= false;
CString	CAppSettings::HsfStreamingEntry			= "HSF Streaming";

bool CAppSettings::LoadPVOFiles					= true;
bool CAppSettings::DefaultLoadPVOFiles			= true;
CString CAppSettings::LoadPVOFilesEntry			= "Load PVO Files";

bool CAppSettings::bImportAllLayouts			= false;		
bool CAppSettings::DefaultbImportAllLayouts		= false;
CString CAppSettings::ImportAllLayoutsEntry     = "Import All Layouts?";

CString	CAppSettings::QuickMovesTypeEntry			= "Quick Moves Type";		
CString	CAppSettings::csQuickMovesType				= "Default";
CString	CAppSettings::DefaultcsQuickMovesType		= "Default";

#ifdef PARASOLID
CString CAppSettings::SchemaPathEntry	= "Parasolid Schema Directory";
CString CAppSettings::SchemaPath		= "";
CString CAppSettings::DefaultSchemaPath	= "..\\..\\datasets\\parasolid\\schema";

CString	CAppSettings::FlattenAssembliesEntry	= "Flatten Assemblies";
bool	CAppSettings::bFlattenAssemblies		= false;
bool	CAppSettings::DefaultbFlattenAssemblies	= false;

CString CAppSettings::BinaryX_TFilesEntry		= "Read-Write Binary X_T Files";
bool	CAppSettings::bBinaryX_TFiles			= false;
bool	CAppSettings::DefaultbBinaryX_TFiles	= false;
#endif // PARASOLID


//-- Tessellation Settings 

#ifdef PARASOLID
CString CAppSettings:: IsCurveChordTolEntry					= "Is Curve Chord Tol";	// registry location
PK_LOGICAL_t CAppSettings:: IsCurveChordTol					= PK_LOGICAL_false;				// do we have curve chord tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsCurveChordTol			= PK_LOGICAL_false;				// default value

CString CAppSettings:: IsCurveChordAngTolEntry				= "Is Curve Chord Angular Tol";	// registry location;
PK_LOGICAL_t CAppSettings:: IsCurveChordAngTol				= PK_LOGICAL_true;							// do we have curve angular tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsCurveChordAngTol		= PK_LOGICAL_true;							// default value

CString CAppSettings:: IsFacetPlaneTolEntry					= "Is Facet Plane Tol";	// default value
PK_LOGICAL_t CAppSettings:: IsFacetPlaneTol					= PK_LOGICAL_false;				// do we have facet plane tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsFacetPlaneTol			= PK_LOGICAL_false;				// registry location

CString CAppSettings:: IsFacetPlaneAngTolEntry				= "Is Facet Plane Angular Tol";		// registry location
PK_LOGICAL_t CAppSettings:: IsFacetPlaneAngTol				= PK_LOGICAL_true;								// do we have facet plane tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsFacetPlaneAngTol		= PK_LOGICAL_true;								// default value

CString CAppSettings:: IsSurfacePlaneTolEntry				= "Is Surface Plane Tol";		// registry location	
PK_LOGICAL_t CAppSettings:: IsSurfacePlaneTol				= PK_LOGICAL_false;						// do we have surface plane tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsSurfacePlaneTol		= PK_LOGICAL_false;						// default value

CString CAppSettings:: IsSurfacePlaneAngTolEntry			= "Is Surface Plane Angular Tol";	// registry location
PK_LOGICAL_t CAppSettings:: IsSurfacePlaneAngTol			= PK_LOGICAL_true;								// do we have surface plane ang. tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsSurfacePlaneAngTol		= PK_LOGICAL_true;								// default value

CString CAppSettings:: IsLineCurveChordTolEntry				= "Is Line Curve Chord Tol";	// registry location
PK_LOGICAL_t CAppSettings:: IsLineCurveChordTol				= PK_LOGICAL_true;				// do we have curve chord tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsLineCurveChordTol		= PK_LOGICAL_true;				// default value

CString CAppSettings:: IsLineCurveChordAngTolEntry			= "Is Line Curve Chord Angular Tol";	// registry location;
PK_LOGICAL_t CAppSettings:: IsLineCurveChordAngTol			= PK_LOGICAL_true;							// do we have curve angular tolerance
PK_LOGICAL_t CAppSettings:: DefaultIsLineCurveChordAngTol	= PK_LOGICAL_true;							// default value



CString CAppSettings:: CurveChordTolEntry			= "Curve Chord Tol Value";	// registry location
CString CAppSettings:: CurveChordTol				= "0.0";					//  curve chord tolerance
CString CAppSettings:: DefaultCurveChordTol			= "0.0";					// default value

CString CAppSettings:: CurveChordAngTolEntry		= "Curve Chord Angular Tol Value";	// regtry location;
CString CAppSettings:: CurveChordAngTol				= "0.6";							//  curve angular tolerance
CString CAppSettings:: DefaultCurveChordAngTol		= "0.6";							// default value

CString CAppSettings:: FacetPlaneTolEntry			= "Facet Plane Tol Value";	// regtry location
CString CAppSettings:: FacetPlaneTol				= "0.0";					// facet plane tolerance
CString CAppSettings:: DefaultFacetPlaneTol			= "0.0";					// default value

CString CAppSettings:: FacetPlaneAngTolEntry		= "Facet Plane Angular Tol Value";	// regtry location
CString CAppSettings:: FacetPlaneAngTol				= "0.01";							//  face place tolerance
CString CAppSettings:: DefaultFacetPlaneAngTol		= "0.01";							// default value

CString CAppSettings:: SurfacePlaneTolEntry			= "Surface Plane Tol Value";	// regtry location
CString CAppSettings:: SurfacePlaneTol				= "0.0";						// surface plane tolerance
CString CAppSettings:: DefaultSurfacePlaneTol		= "0.0";						// default value

CString CAppSettings::SurfacePlaneAngTolEntry		= "Surface Plane Angular Tol Value";	// regtry location
CString CAppSettings::SurfacePlaneAngTol			= "0.25";								//  surface plane ang. tolerance
CString CAppSettings::DefaultSurfacePlaneAngTol 	= "0.25";								// default value

CString CAppSettings:: LineCurveChordTolEntry		= "Line Curve Chord Tol Value";	// registry location
CString CAppSettings:: LineCurveChordTol			= "0.000344";					//  curve chord tolerance
CString CAppSettings:: DefaultLineCurveChordTol		= "0.000344";					// default value

CString CAppSettings:: LineCurveChordAngTolEntry	= "Line Curve Chord Angular Tol Value";	// regtry location;
CString CAppSettings:: LineCurveChordAngTol			= "0.39269908";							//  curve angular tolerance
CString CAppSettings:: DefaultLineCurveChordAngTol	= "0.39269908";							// default value

CString	CAppSettings::FacetMatchEntry				= "Facet Match";			// regtry location
PK_facet_match_t CAppSettings::FacetMatch			= PK_facet_match_geom_c;	//  Facet Matching
PK_facet_match_t CAppSettings::DefaultFacetMatch	= PK_facet_match_geom_c;	// default value
#endif // PARASOLID

#ifdef GRANITE
CString CAppSettings:: AngularToleranceEntry		= "Angular Tolerance";	// registry location
CString CAppSettings:: AngularTolerance				= "0.75";				// KTriangulator.AngularTolerance
CString CAppSettings:: DefaultAngularTolerance		= "0.75";				// default value

CString CAppSettings:: PlanarToleranceEntry			= "Planar Tolerance";	// registry location
CString CAppSettings:: PlanarTolerance				= "5.0";				// KTriangulator.PlanarTolerance
CString CAppSettings:: DefaultPlanarTolerance		= "5.0";				// default value

CString CAppSettings:: TessellationToleranceEntry		= "Tessellation Tolerance";	// registry location
CString CAppSettings:: TessellationTolerance			= "0.15";					// KTriangulator.TessellationTolerance
CString CAppSettings:: DefaultTessellationTolerance		= "0.15";					// default value
#endif //GRANITE

CString CAppSettings:: ShowEveryTickEntry		= "Show Every Tick";	// registry location
bool	CAppSettings::ShowEveryTick	= false;
bool	CAppSettings::DefaultShowEveryTick	= false;

CString CAppSettings:: ShowCollisionsEntry		= "Show Collisions";	// registry location
bool	CAppSettings::ShowCollisions	= false;
bool	CAppSettings::DefaultShowCollisions	= false;

CString CAppSettings:: UpdateCameraEntry		= "Update Camera";	// registry location
bool	CAppSettings::UpdateCamera	= true;
bool	CAppSettings::DefaultUpdateCamera	= true;

CString CAppSettings:: JumpToKeyframeEntry		= "Jump To Keyframe";	// registry location
bool	CAppSettings::JumpToKeyframe= false;
bool	CAppSettings::DefaultJumpToKeyframe= false;

CString CAppSettings:: DisableCFREntry		= "Disable CFR";	// registry location
bool	CAppSettings::DisableCFR = true;
bool	CAppSettings::DefaultDisableCFR= true;

CString CAppSettings:: ChildStartMaximizedEntry		= "Child Start Maximized";	// registry location
bool	CAppSettings::ChildStartMaximized = false;
bool	CAppSettings::DefaultChildStartMaximized= false;



