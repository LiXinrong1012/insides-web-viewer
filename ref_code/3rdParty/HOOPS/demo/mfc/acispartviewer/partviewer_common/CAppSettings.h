#ifndef _CAPPSETTINGS_H__INCLUDED__RAJESH_B__20020425__1224__
#define _CAPPSETTINGS_H__INCLUDED__RAJESH_B__20020425__1224__

#include "HBaseView.h"
/////////////////////////////////////////////////////////////////////////////
// CAppSettings:

// ModelHandedness
enum ModelHandedness
{
	HandednessSetLeft,
	HandednessSetRight,
	HandednessSetNone,
	HandednessNotSet
};

enum HImageOutputOptions
{
	HUseWindowSize,
	HSpecifyImageSize
};

enum HDocOutputOptions
{
	HWYSIWYG,
	HUseWholePage
};

class CAppSettings
{
public:

	static void ReadSettingsFromRegistry();
	static void WriteSettingsToRegistry();
	static void CommitAllOptions();
	static void RefreshAllOptions();
	static void ImportOptions(CString const & fname);
	static void ExportOptions(CString const & fname);
	static void CheckHoopsDriver();
	//--- Main
	static CString CompanyName;
	static CString RegOptionsSection;

	//-- Near Camera Limit
	static int NearCameraLimit;			//near camera limit *100000
	static int DefaultNearCameraLimit;  //default value
	static CString NearCameraLimitEntry; //registry location

	//-- Light Scale Factor
	static int LightScaleFactor;		 //light scale factor *100000
	static int DefaultLightScaleFactor;  //default value
	static CString LightScaleFactorEntry; //registry location

	static bool EmbedHSFThumbnail;			//hsf thumbnail image
	static bool DefaultEmbedHSFThumbnail;	//default value
	static CString EmbedHSFThumbnailEntry;	//registry location

	static bool EmbedMaterials;				//material library
	static bool DefaultEmbedMaterials;		//default value
	static CString EmbedMaterialsEntry;		//registry location

	static bool HemisphericAmbient;			//hemispheric ambient
	static bool DefaultHemisphericAmbient;  //default value
	static CString HemisphericAmbientEntry; //registry location

	static COLORREF AmbientTopColor;		// ambient color 1
	static COLORREF DefaultAmbientTopColor;	// default value
	static CString AmbientTopColorEntry;	// registry location

	static COLORREF AmbientBottomColor;			// ambient color 2
	static COLORREF DefaultAmbientBottomColor;	// default value
	static CString AmbientBottomColorEntry;		// registry location

	static bool LightFollowsCamera;			//miner's helmet
	static bool DefaultLightFollowsCamera;  //default value
	static CString LightFollowsCameraEntry; //registry location

	static CString GoochColorMap;			//the gooch color map as a string
	static CString DefaultGoochColorMap;	//default value
	static CString GoochColorMapEntry;		//registry location

	static bool UseAmbientUpVector;
	static bool DefaultUseAmbientUpVector;
	static CString UseAmbientUpVectorEntry;

	static HPoint AmbientUpVector;
	static HPoint DefaultAmbientUpVector;
	static CString AmbientUpVectorEntry;

	static float GoochWeight;
	static float DefaultGoochWeight;
	static CString GoochWeightEntry;

	static float GoochColorHigh;
	static float DefaultGoochColorHigh;
	static CString GoochColorHighEntry;

	static bool UseBloom;
	static bool DefaultUseBloom;
	static CString UseBloomEntry;
	
	static float BloomStrength;
	static float DefaultBloomStrength;
	static CString BloomStrengthEntry;
	
	static int BloomBlur;
	static int DefaultBloomBlur;
	static CString BloomBlurEntry;
	
	static HBloomShape BloomShape;
	static HBloomShape DefaultBloomShape;
	static CString BloomShapeEntry;

	static int LightCount;
	static int DefaultLightCount;
	static CString LightCountEntry;

	static COLORREF GoochColor1;			// gooch color 1
	static COLORREF DefaultGoochColor1;		// default value
	static CString GoochColor1Entry;		// registry location

	static COLORREF GoochColor2;			// gooch color 2
	static COLORREF DefaultGoochColor2;		// default value
	static CString GoochColor2Entry;		// registry location

	static COLORREF GoochColor3;			// gooch color 3
	static COLORREF DefaultGoochColor3;		// default value
	static CString GoochColor3Entry;		// registry location

	static COLORREF GoochColor4;			// gooch color 4
	static COLORREF DefaultGoochColor4;		// default value
	static CString GoochColor4Entry;		// registry location

	static COLORREF GoochColor5;			// gooch color 5
	static COLORREF DefaultGoochColor5;		// default value
	static CString GoochColor5Entry;		// registry location

	static COLORREF GoochColor6;			// gooch color 6
	static COLORREF DefaultGoochColor6;		// default value
	static CString GoochColor6Entry;		// registry location

	//-- Output Options Settings

	static int OutputWidth;
	static int DefaultOutputWidth;
	static CString OutputWidthEntry;	// registry location

	static int OutputHeight;
	static int DefaultOutputHeight;
	static CString OutputHeightEntry;	// registry location

	static float PaperWidth;				//paper width in inches *1000
	static float DefaultPaperWidth;
	static CString PaperWidthEntry;	// registry location

	static float PaperHeight;				//paper height in inches *1000
	static float DefaultPaperHeight;
	static CString PaperHeightEntry;	// registry location

	static int DPI;								// resolution for background raster pass
	static int DefaultDPI;						// default value
	static CString DPIEntry;					// registry location

	static HImageOutputOptions ImageOpt;
	static HImageOutputOptions DefaultImageOpt;
	static CString ImageOptEntry;

	static HDocOutputOptions DocOpt;
	static HDocOutputOptions DefaultDocOpt;
	static CString DocOptEntry;

	static bool ForceGrayscale;				// force grayscale output
	static bool DefaultForceGrayscale;		// default value
	static CString ForceGrayscaleEntry;			// registry location


	static bool bConserveMemory;			// print background raster pass at full resolution
	static bool DefaultbConserveMemory;		// default value
	static CString bConserveMemoryEntry;	// registry location

	static bool bUseWindowColor;			//output backround color
	static bool DefaultbUseWindowColor;		//default value
	static CString bUseWindowColorEntry;	//registry location

	//-- Geometry Settings
	
	static int Budget;								// upper boundary of number of vertices
	static int DefaultBudget;						// default value
	static CString BudgetEntry;						// registry location

	static int ContinuedBudget;						// number of additional vertices
	static int DefaultContinuedBudget;				// default value
	static CString ContinuedBudgetEntry;			// registry location

	static int MaxDeviation;						// maximum deviation in object space
	static int DefaultMaxDeviation;					// default value
	static CString MaxDeviationEntry;				// registry location

	static int MaxAngle;							// largest angle between adjacent line segments
	static int DefaultMaxAngle;						// default value
	static CString MaxAngleEntry;					// registry location

	static int MaxLength;							// greatest length of any line segment
	static int DefaultMaxLength;					// default value
	static CString MaxLengthEntry;					// registry location

	static bool bViewIndependent;					// tesselate each curve with Budget number of vertices
	static bool DefaultbViewIndependent;			// default value
	static CString bViewIndependentEntry;			// registry location

	//-- General Settings (related to Display etc.)

	static CString HoopsDriver;				// display driver (opengl, msw etc)
	static CString DefaultHoopsDriver;		// default value
	static CString HoopsDriverEntry;		// registry location

	static bool bDriverForceSoftware;			// force Hoops to choose software OpenGL
	static bool DefaultbDriverForceSoftware;	// default value
	static CString DriverForceSoftwareEntry;	// registry location


	static bool bDriverDisplayStats;			// Display Performance Statistics
	static bool DefaultbDriverDisplayStats;	// default value
	static CString DriverDisplayStatsEntry;	// registry location

	static bool bAntiAliasing;					// Anti-alias when using OGL
	static bool DefaultbAntiAliasing;			// default value
	static CString bAntiAliasingEntry;			// registry location

	static bool bDisplayAxisTriad;				// if to display axis triad window
	static bool DefaultbDisplayAxisTriad;		// default value
	static CString DisplayAxisTriadEntry;		// registry location

	static bool bBackplaneCulling;				// if to enable culling of back faces
	static bool DefaultbBackplaneCulling;		// default value
	static CString BackplaneCullingEntry;		// registry location

	static HandednessMode CoordinateSystemHandedness;			// handedness of the coordinate system
	static HandednessMode DefaultCoordinateSystemHandedness;	// default value
	static CString CoordinateSystemHandednessEntry;				// registry location

	static HRenderMode RenderMode;				// render mode (gouraud, wireframe etc)
	static HRenderMode DefaultRenderMode;		// default value
	static CString RenderModeEntry;				// registry location

	static bool DoubleBuffer;
	static bool DefaultDoubleBuffer;
	static CString DoubleBufferEntry;

	static bool StaticModel;							//use a static model
	static bool DefaultStaticModel;					// default value
	static CString StaticModelEntry;					// registry location

	static bool DisableEditing;							// disable geometry editing
	static bool DefaultDisableEditing;					// default value
	static CString DisableEditingEntry;					// registry location

	static bool LMVModel;							// disable geometry editing
	static bool DefaultLMVModel;					// default value
	static CString LMVModelEntry;					// registry location

	static bool NavigationPanel;						// enable navigation panel in walk operator
	static bool DefaultNavigationPanel;					// default value
	static CString NavigationPanelEntry;				// registry location

	static HShadowRenderingMode ShadowRenderingMode;				// render mode (gouraud, wireframe etc)
	static HShadowRenderingMode DefaultShadowRenderingMode;		// default value
	static CString ShadowRenderingEntry;				// registry location

	static CString ViewAxis;				// 
	static CString DefaultViewAxis;		// default value
	static CString ViewAxisEntry;				// registry location

	static CString TransparencyStyle;				
	static CString DefaultTransparencyStyle;		// default value
	static CString TransparencyStyleEntry;				// registry location

	static CString TransparencySorting;				
	static CString DefaultTransparencySorting;		// default value
	static CString TransparencySortingEntry;				// registry location

	static CString TransparencyDepthPeelingLayers;				
	static CString DefaultTransparencyDepthPeelingLayers;		// default value
	static CString TransparencyDepthPeelingLayersEntry;				// registry location

	static bool DepthWriting;
	static bool DefaultDepthWriting;
	static CString DepthWritingEntry;

	static int AntialiasingLevel;				
	static int DefaultAntialiasingLevel;		// default value
	static CString AntialiasingLevelEntry;				// registry location

	static ModelHandedness PolygonHandedness;				// polygon handedness (right, left, none)
	static ModelHandedness DefaultPolygonHandedness;		// default value
	static CString PolygonHandednessEntry;					// registry location

	static bool bSmoothTransition;				// if to enable smooth transition of camera
	static bool DefaultbSmoothTransition;		// default value
	static CString SmoothTransitionEntry;		// registry location

	static bool bLightScaling;				// if to enable smooth transition of camera
	static bool DefaultbLightScaling;		// default value
	static CString bLightScalingEntry;		// registry location

	static bool bWorldHandedness;				// right handed = true, left handed = false
	static bool DefaultbWorldHandedness;		// default value
	static CString WorldHandednessEntry;		// registry location

	static ProjMode ProjectionMode;				// camera project mode (ortho, perspective etc.)
	static ProjMode DefaultProjectionMode;		// default value
	static CString ProjectionModeEntry;			// registry location

	static DisplayListType DisplayList;			// use display lists
	static DisplayListType DefaultDisplayList;	// default value
	static CString DisplayListEntry;			// registry location

	static MultiThreadingType MultiThreading;	// use multi-threading
	static MultiThreadingType DefaultMultiThreading;	// default value
	static CString MultiThreadingEntry;			// registry entry

	static bool VisibilitySelection;			// use visibility based selection
	static bool DefaultVisibilitySelection;		// default value
	static CString VisibilitySelectionEntry;	// registry location

	static bool DynamicHighlighting;			// enable dynamic highlighting
	static bool DefaultDynamicHighlighting;		// default value
	static CString DynamicHighlightingEntry;	// registry location

	static bool DetailSelection;				// use detail selection
	static bool DefaultDetailSelection;			// default value
	static CString DetailSelectionEntry;		// registry location

	static bool bUseSelectBox;					// show a transparent box when selecting areas
	static bool DefaultbUseSelectBox;			// default value
	static CString bUseSelectBoxEntry;			// registry location

	static HSelectionHighlightMode HighlightMode;	// selection highlighting
	static HSelectionHighlightMode DefaultHighlightMode;	// default value
	static CString HighlightModeEntry;			// registry location
	
	static float TransparencyLevel;				// the percent of transparency in inverse transparency mode
	static float DefaultTransparencyLevel;		// default value
	static CString TransparencyLevelEntry;		// registry location

	static int RelatedSelectionLimit;			// The related selection limit.  -1 if no limit
	static int DefaultRelatedSelectionLimit;	// default value
	static CString RelatedSelectionLimitEntry;	// registry location

	static CString csRefSelType;				// quickmoves type to use with reference selection
	static CString csDefaultRefSelType;			// default value
	static CString csRefSelTypeEntry;			// registry location

	static bool TimerBasedUpdate;			    // use timer based updates
	static bool DefaultTimerBasedUpdate;		    // default value
	static CString TimerBasedUpdateEntry;		    // registry location

	static bool OcclusionCulling;			// use occlusion culling
	static bool DefaultOcclusionCulling;	// default value
	static CString OcclusionCullingEntry;			// registry location

	static int OcclusionThreshold;			//occluision culling threshold
	static int DefaultOcclusionThreshold;	// default value
	static CString OcclusionThresholdEntry; // registry location

	static bool LineAntialiasing;		 
	static bool DefaultLineAntialiasing;	// default value
	static CString LineAntialiasingEntry;			// registry location

	static bool TextAntialiasing;		 
	static bool DefaultTextAntialiasing;	// default value
	static CString TextAntialiasingEntry;			// registry location

	static bool ShowDebugMenu;		 
	static bool DefaultShowDebugMenu;	// default value
	static CString ShowDebugMenuEntry;			// registry location

	static HLRMode HiddenLineMode;			// hidden line mode
	static HLRMode DefaultHiddenLineMode;	// default value
	static CString HiddenLineModeEntry;			// registry location

	static bool Spriting;					// use display lists
	static bool DefaultSpriting;		    		// default value
	static CString SpritingEntry;			// registry location

	static bool UpdateCutGeometry;			// update cut geometry
	static bool DefaultUpdateCutGeometry;	// default value
	static CString UpdateCutGeometryEntry;	// registry location

	static bool UpdateShadows;			// Update shadows during manipulation
	static bool DefaultUpdateShadows;	  	// default value
	static CString UpdateShadowsEntry;		// registry location

	static bool StereoMode;					//use stereo mode
	static bool DefaultStereoMode;			//default value
	static CString StereoModeEntry;			//registry location

	static int StereoSeparation;			//stereo separation *10000
	static int DefaultStereoSeparation;		//default value
	static CString StereoSeparationEntry;	//registry location


	//-- Appearance Settings (color, weight etc.)
	static bool OverrideDefaultAppWindowPosition;			// override the default application main window location and size
	static bool DefaultOverrideDefaultAppWindowPosition;	// default value
	static CString OverrideDefaultAppWindowPositionEntry;	// registry location

	static CString AppWindowPosition;					// (x of upper-Left, y of upper-left, width, height) of main window
	static CString DefaultAppWindowPosition;			// default value
	static CString AppWindowPositionEntry;				// registry location

	static CString LineWeight;
	static CString DefaultLineWeight;
	static CString LineWeightEntry;

	static COLORREF WindowBackgroundTopColor;			// window background color gradient (top color)
	static COLORREF DefaultWindowBackgroundTopColor;	// default value
	static CString WindowBackgroundTopColorEntry;		// registry location

	static COLORREF FakeHLRColor;						// fake hlr color
	static COLORREF DefaultFakeHLRColor;				// default value
	static CString FakeHLRColorEntry;					// registry location

	static COLORREF WindowBackgroundBottomColor;		// window background color gradient (bottom color)
	static COLORREF DefaultWindowBackgroundBottomColor;	// default value
	static CString WindowBackgroundBottomColorEntry;	// registry location

	static COLORREF PolygonSelectionColor;				// polygon selection color
	static COLORREF DefaultPolygonSelectionColor;		// default value
	static CString PolygonSelectionColorEntry;			// registry location

	static COLORREF LineSelectionColor;					// line selection color
	static COLORREF DefaultLineSelectionColor;			// default value
	static CString LineSelectionColorEntry;				// registry location

	static COLORREF MarkerSelectionColor;				// marker selection color
	static COLORREF DefaultMarkerSelectionColor;		// default value
	static CString MarkerSelectionColorEntry;			// registry location

	static int SelectionColorTransparency;				// how much transparent should selection be made
	static int DefaultSelectionColorTransparency;		// default value
	static CString SelectionColorTransparencyEntry;		// registry location


	static COLORREF MarkupColor;		// Markup lines color
	static COLORREF DefaultMarkupColor;	// default value
	static CString MarkupColorEntry;	// registry location

	static COLORREF ShadowColor;		// Markup lines color
	static COLORREF DefaultShadowColor;	// default value
	static CString ShadowColorEntry;	// registry location

	static int GreekingLimit;			// Greeking limit * 1000 (to store float as int)
	static int DefaultGreekingLimit;	// default value
	static CString GreekingLimitEntry;	// registry location

	static int MarkupWeight;			// Markup line weight * 100 (to store float as int)
	static int DefaultMarkupWeight;		// default value
	static CString MarkupWeightEntry;	// registry location

	static int WalkAvatarHeight;			// avatar height * 100 (to store float as int)
	static int DefaultWalkAvatarHeight;		// default value
	static CString WalkAvatarHeightEntry;	// registry location

	static int WalkStepHeightUp;			// step height up * 100 (to store float as int)
	static int DefaultWalkStepHeightUp;		// default value
	static CString WalkStepHeightUpEntry;	// registry location

	static int CullingThreshold;			// pixel threshold from which objects are not drawn
	static int DefaultCullingThreshold;		// default value
	static CString CullingThresholdEntry;	// registry location

	static int CullingThresholdSet;			// pixel threshold from which objects are not drawn
	static int DefaultCullingThresholdSet;		// default value
	static CString CullingThresholdSetEntry;	// registry location

	static float FramerateTime;
	static float DefaultFramerateTime;
	static CString FramerateTimeEntry;

	static int DynamicAdjustment;			// pixel threshold from which objects are not drawn
	static int DefaultDynamicAdjustment;		// default value
	static CString DynamicAdjustmentEntry;	// registry location

	static int UseLods;						// use lods in framerate
	static int DefaultUseLods;				// default value
	static CString UseLodsEntry;			// registry location

	static FramerateMode CurrentFramerateMode;			// framerate mode
	static FramerateMode DefaultCurrentFramerateMode;	// default value
	static CString CurrentFramerateModeEntry;	// registry location

	static int MaxThreshold;				// pixel threshold below which objects are not drawn
	static int DefaultMaxThreshold;			// default value
	static CString MaxThresholdEntry;		// registry location

	static int HardCutoff;				
	static int DefaultHardCutoff;
	static CString HardCutoffEntry;
	
	static int DetailSteps;			// pixel threshold from which objects are not drawn
	static int DefaultDetailSteps;		// default value
	static CString DetailStepsEntry;	// registry location

	static bool UseFramerate;
	static bool DefaultUseFramerate;
	static CString UseFramerateEntry;

	static int WalkStepHeightDown;			// step height down * 100 (to store float as int)
	static int DefaultWalkStepHeightDown;		// default value
	static CString WalkStepHeightDownEntry;	// registry location

	static int ShadowRes;			 
	static int DefaultShadowRes;	 
	static CString ShadowResEntry;	 

	static int ShadowBlur;			 
	static int DefaultShadowBlur;	 
	static CString ShadowBlurEntry;	 

	static bool bColorInterpolation;		// color interpolation
	static bool DefaultbColorInterpolation;	// default value
	static CString ColorInterpolationEntry;	// registry location

	static bool bGrayScaleSelection;		// gray scale selection
	static bool DefaultbGrayScaleSelection;	// default value
	static CString GrayScaleSelectionEntry;	// registry location

	static bool bDisplaceSelection;		// gray scale selection
	static bool DefaultbDisplaceSelection;	// default value
	static CString DisplaceSelectionEntry;	// registry location


	static bool bWalkUseKeyboard;		// use keyboard  walk
	static bool DefaultbWalkUseKeyboard;	// default value
	static CString WalkUseKeyboardEntry;	// registry location

	static bool bWalkAutomaticHeight;		// use automatic height in  walk
	static bool DefaultbWalkAutomaticHeight;	// default value
	static CString WalkAutomaticHeightEntry;	// registry location


	static bool bWalkSnapToFloor;		// use snap to floor in walk
	static bool DefaultbWalkSnapToFloor;	// default value
	static CString WalkSnapToFloorEntry;	// registry location

	static bool bWalkCollision;		// use keyboard walk
	static bool DefaultbWalkCollision;	// default value
	static CString WalkCollisionEntry;	// registry location

	static bool bHideOverlappedText;		// toggle hiding of overlapped text
	static bool DefaultHideOverlappedText;	// default value (false)
	static CString HideOverlappedTextEntry;	// registry location

	static bool bSplatRendering;			//use splat rendering
	static bool DefaultbSplatRendering;		//default value (false)
	static CString SplatRenderingEntry;		//registry location

	static bool bFastMarkers;				//use fast markers
	static bool DefaultbFastMarkers;		//default value
	static CString FastMarkersEntry;		//registry location

	static bool bUseGreeking;			// toggle use of text greeking
	static bool DefaultbUseGreeking;	// default value (false)
	static CString UseGreekingEntry;	// registry location

	static bool bCiIsolines;			// color interpolation, isolines only
	static bool DefaultbCiIsolines;		// default value
	static CString CiIsolinesEntry;		// registry location

	static bool bCiByValue;				// color interpolation, by value
	static bool DefaultbCiByValue;		// default value
	static CString CiByValueEntry;		// registry location

	static bool bCiByColormapIndex;			// color interpolation, by colormap index
	static bool DefaultbCiByColormapIndex;	// default value
	static CString CiByColormapIndexEntry;	// registry location

	static CString FontName;				// name of the font
	static CString DefaultFontName;			// default value
	static CString FontNameEntry;			// registry location

	static CString GreekingMode;				// type of geometry drawn
	static CString DefaultGreekingMode;			// default value
	static CString GreekingModeEntry;			// registry location

	static CString GreekingUnits;				// Units associated with greeking limit
	static CString DefaultGreekingUnits;		// default value
	static CString GreekingUnitsEntry;			// registry location

	static CString FontSize;				// font size (don't know yet if it's oru or sru)
	static CString DefaultFontSize;			// default value
	static CString FontSizeEntry;			// registry location

	static CString FontUnits;				// font units
	static CString DefaultFontUnits;		// default value
	static CString FontUnitsEntry;			// registry location

	//-- Shadow Settings

	static HShadowMode ShadowMode;				// shadow mode (none, soft, hard)
	static HShadowMode DefaultShadowMode;		// default value
	static CString ShadowModeEntry;				// registry location

	static bool bShadowMap;
	static bool bDefaultShadowMap;
	static CString ShadowMapEntry;
	
	static bool bReflectionPlane;
	static bool bDefaultReflectionPlane;
	static CString ReflectionPlaneEntry;

	static float ReflectionOpacity;
	static float DefaultReflectionOpacity;
	static CString ReflectionOpacityEntry;

	static bool Jitter;
	static bool DefaultJitter;
	static CString JitterEntry;

	static int ReflectionBlur;
	static int DefaultReflectionBlur;
	static CString ReflectionBlurEntry;

	static float ReflectionHither;
	static float DefaultReflectionHither;
	static CString ReflectionHitherEntry;

	static float ReflectionYon;
	static float DefaultReflectionYon;
	static CString ReflectionYonEntry;

	static bool ReflectionUseBlur;
	static bool DefaultReflectionUseBlur;
	static CString ReflectionUseBlurEntry;

	static bool ReflectionUseAttenuation;
	static bool DefaultReflectionUseAttenuation;
	static CString ReflectionUseAttenuationEntry;

	static bool bReflectionFading;
	static bool bDefaultReflectionFading;
	static CString ReflectionFadingEntry;

	static int nSMSamples;
	static int nDefaultSMSamples;
	static CString SMSamplesEntry;

	static int nSMResolution;
	static int nDefaultSMResolution;
	static CString SMResolutionEntry;

	static float ShadowOpacity;
	static float DefaultShadowOpacity;
	static CString ShadowOpacityEntry;

	static bool ViewDependentShadowMap;
	static bool DefaultViewDependentShadowMap;
	static CString ViewDependentShadowMapEntry;

	static bool UseFastAmbient;
	static bool	DefaultUseFastAmbient;
	static CString UseFastAmbientEntry;

	static float FastAmbientStrength;
	static float DefaultFastAmbientStrength;
	static CString FastAmbientStrengthEntry;

	static bool HQAmbientOcclusion;
	static bool DefaultHQAmbientOcclusion;
	static CString HQAmbientOcclusionEntry;

	static bool UseFastSilhouette;
	static bool DefaultUseFastSilhouette;
	static CString UseFastSilhouetteEntry;

	static float FastSilhouetteTolerance;
	static float DefaultFastSilhouetteTolerance;
	static CString FastSilhouetteToleranceEntry;

	static bool HeavyExteriorSilhouette;
	static bool DefaultHeavyExteriorSilhouette;
	static CString HeavyExteriorSilhouetteEntry;

	static bool IgnoreTransparency;
	static bool DefaultIgnoreTransparency;
	static CString IgnoreTransparencyEntry;
	
	static bool UseLightVector;
	static bool DefaultUseLightVector;
	static CString UseLightVectorEntry;

	static HPoint LightVector;
	static HPoint DefaultLightVector;
	static CString LightVectorEntry;
	
	//-- File Settings (import-export options)

	static bool	bReadSimpleHsf;			// if to read simple hsf first
	static bool	DefaultbReadSimpleHsf;			// default value
	static CString	ReadSimpleHsfEntry;	// registry location

	static unsigned int HsfExportVersion;	// the hsf file version number to export
	static unsigned int DefaultHsfExportVersion;	// default value
	static CString HsfExportVersionEntry;	// registry location

	static bool	bExportTopolInfo;			// if to export topology information
	static bool	DefaultbExportTopolInfo;			// default value
	static CString	ExportTopolInfoEntry;	// registry location

	static bool	bCompressVertices;			// if to compress vertices
	static bool	DefaultbCompressVertices;			// default value
	static CString	CompressVerticesEntry;	// registry location

	static unsigned int NumVertexBits;	// number of bits allowed for storage of each vertex
	static unsigned int DefaultNumVertexBits;	// default value
	static CString NumVertexBitsEntry;	// registry location

	static bool	bCompressNormals;			// if to compress normals
	static bool	DefaultbCompressNormals;			// default value
	static CString	CompressNormalsEntry;	// registry location

	static unsigned int NumNormalBits;	// number of bits allowed for storage of each normal
	static unsigned int DefaultNumNormalBits;	// default value
	static CString NumNormalBitsEntry;	// registry location

	static bool	bCompressParameters;			// if to compress Parameters
	static bool	DefaultbCompressParameters;			// default value
	static CString	CompressParametersEntry;	// registry location

	static unsigned int NumParameterBits;	// number of bits allowed for storage of each Parameter
	static unsigned int DefaultNumParameterBits;	// default value
	static CString NumParameterBitsEntry;	// registry location

	static bool	bImportDWGXData;			// if to import DWG XData
	static bool	DefaultbImportDWGXData;			// default value
	static CString	ImportDWGXDataEntry;	// registry location

	static bool	bImportDWGviaBstream;			// if to import DWG via Bstream toolkit
	static bool	DefaultbImportDWGviaBstream;			// default value
	static CString	ImportDWGviaBstreamEntry;	// registry location

	static CString DWGDeviation;				// Facet/Curve tolerance
	static CString DefaultDWGDeviation;			// default value
	static CString DWGDeviationEntry;			// registry location

	static bool	bExportLines;			// if to export polyline data
	static bool	DefaultbExportLines;			// default value
	static CString	ExportLinesEntry;	// registry location

	static bool	bExportDictionary;			// if to export dictionary
	static bool	DefaultbExportDictionary;			// default value
	static CString	ExportDictionaryEntry;	// registry location

	static bool	bEnableInstancing;			// if to enable instancing
	static bool	DefaultbEnableInstancing;			// default value
	static CString	EnableInstancingEntry;	// registry location

	static bool	bSaveLogFile;			// if to export dictionary
	static bool	DefaultbSaveLogFile;			// default value
	static CString	SaveLogFileEntry;	// registry location

	//For DGN
   
	static bool	bIgnoreInvisibleEntities;			// if to ignore imoprt of DGN entities
	static bool	DefaultbIgnoreInvisibleEntities;			// default value
	static CString	IgnoreInvisibleEntity;	// registry location

	static CString DGNFactorForCone;				// Facet/Curve tolerance
	static CString DefaultDGNFactorForCone;			// default value
	static CString DGNFactorForConeEntry;			// registry location

	static CString DGNFactorForSmartSolids;				// Facet/Curve tolerance
	static CString DefaultDGNFactorForSmartSolids;			// default value
	static CString DGNFactorForSmartSolidsEntry;			// registry location
	//DGN

	static bool	bCompressConnectivity;			// if to compress the connectivity
	static bool	DefaultbCompressConnectivity;			// default value
	static CString	CompressConnectivityEntry;	// registry location


	static unsigned int	ModelerExportFileVer;	// the modeler file export version number
	static unsigned int	DefaultModelerExportFileVer;	// default value
	static CString ModelerExportFileVerEntry;	// registry location

	static bool EnableTristrips;				// write HSF files with tristrips
	static bool DefaultEnableTristrips;			// default value
	static CString EnableTristripsEntry;		// registry location

	static CString PartsDirectory;		// the parts directory
	static CString DefaultPartsDirectory;		// default value
	static CString PartsDirectoryEntry;	// registry location

	static CString DWGTextureDirectory;				// the texture directory
	static CString DefaultDWGTextureDirectory;		// default value
	static CString DWGTextureDirectoryEntry;		// registry location

	static CString MaterialLibraryDirectory;			// the material library directory
	static CString DefaultMaterialLibraryDirectory;		// default value
	static CString MaterialLibraryDirectoryEntry;		// registry location

	static bool	bFlushOnLoad;				// flush the model segment when loading files?
	static bool	DefaultbFlushOnLoad;		// default value
	static CString	FlushOnLoadEntry;		// registry location

	static bool	bRestoreAnnotations;				// Restore annotations when loading files?
	static bool	DefaultbRestoreAnnotations;			// default value
	static CString	RestoreAnnotationsEntry;		// registry location

	static bool	bPrcFaceEdgeVertexSelectability;				// Allow for individual selection of subbody entities
	static bool	DefaultbPrcFaceEdgeVertexSelectability;			// default value
	static CString	PrcFaceEdgeVertexSelectabilityEntry;		// registry location


	static bool HsfStreaming;				//don't open stream files via MVO?
	static bool DefaultHsfStreaming;		// default value
	static CString HsfStreamingEntry;		//registry location

	static bool LoadPVOFiles;				//don't open stream files via MVO?
	static bool DefaultLoadPVOFiles;		// default value
	static CString LoadPVOFilesEntry;		//registry location

	static bool bImportAllLayouts;				//don't open stream files via MVO?
	static bool DefaultbImportAllLayouts;		// default value
	static CString ImportAllLayoutsEntry;		//registry location

	static CString	csQuickMovesType;			//the default type of quick moves
	static CString	DefaultcsQuickMovesType;	//default value
	static CString	QuickMovesTypeEntry;		//registry location


	
	//-- Tessellation Settings 


	static bool		ShowEveryTick;
 	static bool		DefaultShowEveryTick;
	static CString	ShowEveryTickEntry;		// registry location

	static bool		ShowCollisions;
 	static bool		DefaultShowCollisions;
	static CString	ShowCollisionsEntry;		// registry location
 
	static bool		UpdateCamera;
	static bool		DefaultUpdateCamera;
	static CString	UpdateCameraEntry;		// registry location

	static bool		JumpToKeyframe;
	static bool		DefaultJumpToKeyframe;
	static CString  JumpToKeyframeEntry;		// registry location

	static bool		DisableCFR;
	static bool		DefaultDisableCFR;
	static CString  DisableCFREntry;		// registry location

	static bool		ChildStartMaximized;
	static bool		DefaultChildStartMaximized;
	static CString	ChildStartMaximizedEntry;	// registry location

};

#endif // _CAPPSETTINGS_H__INCLUDED__RAJESH_B__20020425__1224__