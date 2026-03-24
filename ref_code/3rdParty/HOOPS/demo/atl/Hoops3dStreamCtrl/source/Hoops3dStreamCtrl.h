//
// Copyright (c) 2002 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/Hoops3dStreamCtrl.h,v 1.113 2009-09-11 01:03:13 conor Exp $
//

#ifndef __Hoops3dStreamCTRL_H_
#define __Hoops3dStreamCTRL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "Hoops3dStream.h"
#include "HUtility.h"
#include "HBaseView.h"

#include "HStream.h"
#include "HOpcodeHandler.h"
#include "guidlist.h"
#include "Vector"
#include "Hoops3dStreamCtrlEvents.h"
using namespace std;
 
class HBaseModel;
class HCtrlView;
class HCtrlDB;
class HBaseOperator;
class CDataLoader;
class HUtilityXMLTag;

#define WM_XML_PARSING_COMPLETE WM_USER+0x100

struct IWebBrowserApp;

// msw driver options debug
#define DEBUG_NO_WINDOWS_HOOK				0x00000040
#define DEBUG_FORCE_FULL_COLOR				0x00000010
#define DEBUG_SFB_COPY_TO_CLIPBOARD			0x00004000
#define DEBUG_PRINTING_MODE					0x00040000
#define DEBUG_CLIPBOARD_MODE				0x00080000
#define DEBUG_PRINT_NOT_FRAMEBUFFER_MODE	0x00020000
#define DEBUG_PRINT_NOT_RASTER_REDUCTION	0x00200000

#define NUM_MARKUP_LAYERS					5

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

// rendering options debug
#define DEBUG_NO_PAINTERS_PANELLING		0x00000008

#define TOGGLE_OFF(x)						if(uMsg == WM_PAINT) x=0;

#define WMF             0
#define EMF             1
 

//! The CHoops3dStreamCtrl is the primary HOOPS ATL Control class.
/*!
  CHoops3dStreamCtrl encapsulates the HOOPS view as well as the HOOPS model object. 
  By subclassing from a large number of ATL template classes it also provides support 
  for serialization, embedding and other control specific features.

  The control's interface (it's public properties/methods) are doumemented in the Reference Manual entry for IHoops3dStreamCtrl 
*/
class ATL_NO_VTABLE CHoops3dStreamCtrl : 
	public CComObjectRootEx<CComSingleThreadModel>,
   	public CStockPropImpl<CHoops3dStreamCtrl, IHoops3dStreamCtrl, &IID_IHoops3dStreamCtrl, &LIBID_Hoops3dStreamLib>,
 	public CComControl<CHoops3dStreamCtrl>,
	public IPersistStreamInitImpl<CHoops3dStreamCtrl>,
	public IOleControlImpl<CHoops3dStreamCtrl>,
	public IOleObjectImpl<CHoops3dStreamCtrl>,
	public IOleInPlaceActiveObjectImpl<CHoops3dStreamCtrl>,
	public IViewObjectExImpl<CHoops3dStreamCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CHoops3dStreamCtrl>,
	public IConnectionPointContainerImpl<CHoops3dStreamCtrl>,
	public IPersistStorageImpl<CHoops3dStreamCtrl>,
	public ISpecifyPropertyPagesImpl<CHoops3dStreamCtrl>,
	public IQuickActivateImpl<CHoops3dStreamCtrl>,
	public IDataObjectImpl<CHoops3dStreamCtrl>,
	public IProvideClassInfo2Impl<&CLSID_Hoops3dStreamCtrl, &DIID__IHoops3dStreamCtrlEvents, &LIBID_Hoops3dStreamLib>,
	public IPropertyNotifySinkCP<CHoops3dStreamCtrl>,
	public IPersistPropertyBagImpl<CHoops3dStreamCtrl>,
	public CComCoClass<CHoops3dStreamCtrl, &CLSID_Hoops3dStreamCtrl>,
	public CProxy_IHoops3dStreamCtrlEvents< CHoops3dStreamCtrl >
{
public:

	CHoops3dStreamCtrl();
	~CHoops3dStreamCtrl();

	
DECLARE_PROTECT_FINAL_CONSTRUCT()
 
BEGIN_COM_MAP(CHoops3dStreamCtrl)
	COM_INTERFACE_ENTRY(IHoops3dStreamCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CHoops3dStreamCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_NULL)
 	PROP_ENTRY("Filename",1, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("Antialiasing",68, CLSID_Hoops3dStreamProperty)
  	PROP_ENTRY("FileType",33, CLSID_Hoops3dStreamProperty)
 	PROP_ENTRY("AllowMenu",69, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("HardwareAntialiasing",73, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("AxisMode",74, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("AllowEntitySelection",110, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("BhvContinuousPlay",112, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("ConfigFile",129, CLSID_Hoops3dStreamProperty)
 	PROP_ENTRY("DefaultConfigFile",146, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("Key",138, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("String1",139, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("String2",140, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("String3",141, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("Int1",142, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("SegmentDL",132, CLSID_Hoops3dStreamProperty)
   	PROP_ENTRY("DriverType",145, CLSID_Hoops3dStreamProperty)
   	PROP_ENTRY("TransparencyOptions",152, CLSID_Hoops3dStreamProperty)
 	PROP_ENTRY("AntialiasingLevel",148, CLSID_Hoops3dStreamProperty)
 	PROP_ENTRY("CullingThreshold",149, CLSID_Hoops3dStreamProperty)
 	PROP_ENTRY("MaximumThreshold",151, CLSID_Hoops3dStreamProperty)
 	PROP_ENTRY("FrameRate",150, CLSID_Hoops3dStreamProperty)
 	PROP_ENTRY("FramerateType",144, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("StaticModel",147, CLSID_Hoops3dStreamProperty)
	PROP_ENTRY("AntialiasingLevel",148, CLSID_Hoops3dStreamProperty)
  	PROP_PAGE(CLSID_Hoops3dStreamProperty)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CHoops3dStreamCtrl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IHoops3dStreamCtrlEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CHoops3dStreamCtrl)
	/*if we are drawing to screen, disable print flag (only for WM_PAINT messages!)
	 *the CHoops3dStreamCtrl::OnDraw() function will turn the flag back on
	 */
	TOGGLE_OFF(m_iPrintFlag);
	COMMAND_ID_HANDLER(ID_TOOLS_OPTIMIZEMODEL, OnToolsOptimizemodel)
		COMMAND_ID_HANDLER(ID_TOOLS_SAVEAS, OnToolsSaveas)
		CHAIN_MSG_MAP(CComControl<CHoops3dStreamCtrl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnRButtonUP)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
	COMMAND_ID_HANDLER(ID_FILEOPEN,OnFileOpen)
	COMMAND_ID_HANDLER(ID_ORBIT,OnOrbit)
	COMMAND_ID_HANDLER(ID_WINDOW_COLOR,OnWindowColor)
	COMMAND_ID_HANDLER(ID_ZOOM_DIRECT,OnZoom)
	COMMAND_ID_HANDLER(ID_PAN,OnPan)
	COMMAND_ID_HANDLER(ID_RESET,OnReset)
	COMMAND_ID_HANDLER(ID_ZOOM_WINDOW,OnZoomWindow)
	COMMAND_ID_HANDLER(ID_TOOLS_SMOOTHTRANSITION,OnSmoothTransition)
	COMMAND_ID_HANDLER(ID_TOOLS_VISIBILITY_TEXT,OnToolsVisibilityText)
	COMMAND_ID_HANDLER(ID_TOOLS_VISIBILITY_LINES,OnToolsVisibilityLines)
	COMMAND_ID_HANDLER(ID_TOOLS_VISIBILITY_FACES,OnToolsVisibilityFaces)
	COMMAND_ID_HANDLER(ID_ANNOTATE,OnAnnotate)
	COMMAND_ID_HANDLER(ID_ADDNOTE,OnAddNote)
	COMMAND_ID_HANDLER(ID_TOOLS_REDLINE,OnRedline)
	COMMAND_ID_HANDLER(ID_SMOOTH_SHADED,OnSmoothShaded)
	COMMAND_ID_HANDLER(ID_FLAT_SHADED,OnFlatShaded)
	COMMAND_ID_HANDLER(ID_WIREFRAME,OnWireframe)
	COMMAND_ID_HANDLER(ID_HIDDEN_LINE,OnHiddenLine)
	COMMAND_ID_HANDLER(ID_SHADOW_SMOOTH,OnShadowSmooth)
	COMMAND_ID_HANDLER(ID_PRINT,OnPrint)
 	COMMAND_ID_HANDLER(ID_COPY,OnCopy)
	COMMAND_ID_HANDLER(ID_ABOUT_BOX,OnAboutBox)
 
	COMMAND_ID_HANDLER(ID_BHV_PLAY,OnBhvPlay)
	COMMAND_ID_HANDLER(ID_BHV_PAUSE,OnBhvPause)
	COMMAND_ID_HANDLER(ID_BHV_REWIND,OnBhvRewind)

	MESSAGE_HANDLER(WM_TIMER, OnTimer)
 	MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
  	MESSAGE_HANDLER(WM_EXITMENULOOP, OnExitMenuLoop)
  	MESSAGE_HANDLER(WM_CHAR, OnChar)
  	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_XML_PARSING_COMPLETE, OnXMLParsingComplete)

END_MSG_MAP()

BEGIN_CATEGORY_MAP(CHoops3dStreamCtrl)
	IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
	IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
END_CATEGORY_MAP()



// IHoops3dStreamCtr


	/* Insert Functions */

	/* A wrapper for HOOPS/3dGS ::Insert_Circle */
	STDMETHOD(HATL_Insert_Circle)(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Circle_By_Radius */
	STDMETHOD(HATL_Insert_Circle_By_Radius)(float c_x, float c_y, float c_z, float radius, float n_x, float n_y, float n_z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Circular_Arc */
	STDMETHOD(HATL_Insert_Circular_Arc)(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Circular_Chord */	
	STDMETHOD(HATL_Insert_Circular_Chord)(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Circular_Wedge */	
	STDMETHOD(HATL_Insert_Circular_Wedge)(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float p3_x, float p3_y, float p3_z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Cutting_Plane */	
	STDMETHOD(HATL_Insert_Cutting_Plane)(float a, float b, float c, float d, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Cutting_Section */	
	STDMETHOD(HATL_Insert_Cutting_Section)(int count, VARIANT *planes_var, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Cylinder */	
	STDMETHOD(HATL_Insert_Cylinder)(float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z, float r, BSTR cap, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Ellipse */	
	STDMETHOD(HATL_Insert_Ellipse)(float c_x, float c_y, float c_z, float major_x, float major_y, float major_z, float minor_x, float minor_y, float minor_z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Elliptical_Arc */	
	STDMETHOD(HATL_Insert_Elliptical_Arc)(float c_x, float c_y, float c_z, float major_x, float major_y, float major_z, float minor_x, float minor_y, float minor_z, float start, float end, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Grid */	
	STDMETHOD(HATL_Insert_Grid)(BSTR type, float o_x, float o_y, float o_z, float ref1_x, float ref1_y, float ref1_z, float ref2_x, float ref2_y, float ref2_z, int count1, int count2, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Image */	
	STDMETHOD(HATL_Insert_Image)(float x, float y, float z, BSTR format, int width, int height, VARIANT *pixeldata_var, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Ink */	
	STDMETHOD(HATL_Insert_Ink)(float x, float y, float z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Line */	
	STDMETHOD(HATL_Insert_Line)(float xa, float ya, float za,float xb, float yb, float zb, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Distant_Light */	
	STDMETHOD(HATL_Insert_Distant_Light)(float di, float dj, float dk, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Local_Light */	
	STDMETHOD(HATL_Insert_Local_Light)(float x, float y, float z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Spot_Light */	
	STDMETHOD(HATL_Insert_Spot_Light)(float p_x, float p_y, float p_z, float t_x, float t_y, float t_z, BSTR list, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Marker */	
	STDMETHOD(HATL_Insert_Marker)(float x, float y, float z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Mesh */	
	STDMETHOD(HATL_Insert_Mesh)(int rows,int columns, VARIANT * points, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_NURBS_Curve */	
	STDMETHOD(HATL_Insert_NURBS_Curve)(int degree, int cpcount, VARIANT *cpoints_var, VARIANT *weights_var, VARIANT *knots_var, float start_u, float end_u, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_NURBS_Surface */
	STDMETHOD(HATL_Insert_NURBS_Surface)(int u_degree, int v_degree, int u_count, int v_count, VARIANT *points_var, VARIANT *weights_var, VARIANT *u_knots_var, VARIANT *v_knots_var, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Polycylinder */
	STDMETHOD(HATL_Insert_Polycylinder)(int pcount, VARIANT * points_var, int r_count, VARIANT *radii_var, BSTR capping, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Polygon */	
	STDMETHOD(HATL_Insert_Polygon)(int count, VARIANT *points_var, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Polyline */	
	STDMETHOD(HATL_Insert_Polyline)(int count, VARIANT *points_var, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Shell */	
	STDMETHOD(HATL_Insert_Shell)(int npoints, VARIANT * arr, int flen, VARIANT *arr2, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Shell_By_Tristrips */	
	STDMETHOD(HATL_Insert_Shell_By_Tristrips)(int pcount, VARIANT *points_var, int tlen, VARIANT *tlist_var, int flen, VARIANT *flist_var, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Shell_From_Region */	
	STDMETHOD(HATL_Insert_Shell_From_Region)(long key1, int region, BSTR options, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Sphere */	
	STDMETHOD(HATL_Insert_Sphere)( float c_x, float c_y, float c_z, float radius, float a_x, float a_y, float a_z, float o_x, float o_y, float o_z, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Text */	
	STDMETHOD(HATL_Insert_Text)(float x, float y, float z, BSTR text, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Text_With_Encoding */	
	STDMETHOD(HATL_Insert_Text_With_Encoding)(float x, float y, float z, BSTR encoding, VARIANT *text, /*[out, retval]*/long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Insert_Unicode_Text */	
	STDMETHOD(HATL_Insert_Unicode_Text)(float x, float y, float z, VARIANT *text, /*[out, retval]*/long *retkey);



	/* Misc functions */
	
	/* A wrapper for HOOPS/3dGS ::Open_Segment */	
	STDMETHOD(HATL_Open_Segment)(BSTR segment, long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Close_Segment */	
	STDMETHOD(HATL_Close_Segment)();
	
		/* A wrapper for HOOPS/3dGS ::Open_Geometry */
	STDMETHOD(HATL_Open_Geometry)(HC_KEY key);
	
		/* A wrapper for HOOPS/3dGS ::Close_Geometry */
	STDMETHOD(HATL_Close_Geometry)();
	
		/* A wrapper for HOOPS/3dGS ::Open_Face */
	STDMETHOD(HATL_Open_Face)(int offset);
	
	/* A wrapper for HOOPS/3dGS ::Close_Face */	
	STDMETHOD(HATL_Close_Face)();
	
	/* A wrapper for HOOPS/3dGS ::Open_Edge */	
	STDMETHOD(HATL_Open_Edge)(int offset1, int offset2);
	
	/* A wrapper for HOOPS/3dGS ::Close_Edge */	
	STDMETHOD(HATL_Close_Edge)();
	
	/* A wrapper for HOOPS/3dGS ::Include_Segment */	
	STDMETHOD(HATL_Include_Segment)(BSTR segment, long *retkey);
	
	/* A wrapper for HOOPS/3dGS ::Delete_By_Key */	
	STDMETHOD(HATL_Delete_By_Key)(HC_KEY key);
	
	/* A wrapper for HOOPS/3dGS ::Flush_Contents */	
	STDMETHOD(HATL_Flush_Contents)(BSTR segment, BSTR filter);



	/* Set functions */
	
	/* A wrapper for HOOPS/3dGS ::Set_Camera */	
	STDMETHOD(HATL_Set_Camera)(float p_x, float p_y, float p_z, float t_x, float t_y, float t_z, float u_x, float u_y, float u_z, float width, float height, BSTR projection);
	
	/* A wrapper for HOOPS/3dGS ::Set_Camera_By_Volume */	
	STDMETHOD(HATL_Set_Camera_By_Volume)(BSTR projection, float xmin, float xmax, float ymin, float ymax);
	
	/* A wrapper for HOOPS/3dGS ::Set_Camera_Field */	
	STDMETHOD(HATL_Set_Camera_Field)(float width, float height);
	
	/* A wrapper for HOOPS/3dGS ::Set_Camera_Near_Limit */	
	STDMETHOD(HATL_Set_Camera_Near_Limit)(float wlimit);
	
		/* A wrapper for HOOPS/3dGS ::Set_Camera_Position */
	STDMETHOD(HATL_Set_Camera_Position)(float p_x, float p_y, float p_z);
	
	/* A wrapper for HOOPS/3dGS ::Set_Camera_Projection */	
	STDMETHOD(HATL_Set_Camera_Projection)(BSTR projection);
	
		/* A wrapper for HOOPS/3dGS ::Set_Camera_Target */
	STDMETHOD(HATL_Set_Camera_Target)(float t_x, float t_y, float t_z);
	
		/* A wrapper for HOOPS/3dGS ::Set_Camera_Up_Vector */
	STDMETHOD(HATL_Set_Camera_Up_Vector)(float u_x, float u_y, float u_z);
	
		/* A wrapper for HOOPS/3dGS ::Set_Circular_Center */
	STDMETHOD(HATL_Set_Circular_Center)(float x, float y, float z);
	
		/* A wrapper for HOOPS/3dGS ::Set_Circular_Center_By_Key */
	STDMETHOD(HATL_Set_Circular_Center_By_Key)(HC_KEY key, float x, float y, float z);
	
		/* A wrapper for HOOPS/3dGS ::Set_Color */
	STDMETHOD(HATL_Set_Color)(BSTR col);
	
		/* A wrapper for HOOPS/3dGS ::Set_Color_By_FIndex */
	STDMETHOD(HATL_Set_Color_By_FIndex)(BSTR types, float findex);
	
		/* A wrapper for HOOPS/3dGS ::Set_Color_By_Index */
	STDMETHOD(HATL_Set_Color_By_Index)(BSTR types, int index);
	
		/* A wrapper for HOOPS/3dGS ::Set_Color_By_Value */
	STDMETHOD(HATL_Set_Color_By_Value)(BSTR types, BSTR colspace, float a, float b, float c);
	
		/* A wrapper for HOOPS/3dGS ::Set_Color_Map */
	STDMETHOD(HATL_Set_Color_Map)(BSTR col);
	
		/* A wrapper for HOOPS/3dGS ::Set_Color_Map_By_Value */
	STDMETHOD(HATL_Set_Color_Map_By_Value)(BSTR col, int count, VARIANT *values_var);
	
		/* A wrapper for HOOPS/3dGS ::Set_Conditions */
	STDMETHOD(HATL_Set_Conditions)(BSTR conditions);
	
		/* A wrapper for HOOPS/3dGS ::Set_Driver_Options */
	STDMETHOD(HATL_Set_Driver_Options)(BSTR driver_options);
	
		/* A wrapper for HOOPS/3dGS ::Set_Edge_Pattern */
	STDMETHOD(HATL_Set_Edge_Pattern)(BSTR pattern);
	
		/* A wrapper for HOOPS/3dGS ::Set_Edge_Weight */
	STDMETHOD(HATL_Set_Edge_Weight)(float weight);
	
		/* A wrapper for HOOPS/3dGS ::Set_Face_Pattern */
	STDMETHOD(HATL_Set_Face_Pattern)(BSTR pattern);
	
		/* A wrapper for HOOPS/3dGS ::Set_Faces */
	STDMETHOD(HATL_Set_Faces)(int first_face, int face_count);
	
		/* A wrapper for HOOPS/3dGS ::Set_Handedness */
	STDMETHOD(HATL_Set_Handedness)(BSTR handedness);
	
		/* A wrapper for HOOPS/3dGS ::Set_Heuristics */
	STDMETHOD(HATL_Set_Heuristics)(BSTR heuristics);
	
		/* A wrapper for HOOPS/3dGS ::Set_Line_Pattern */
	STDMETHOD(HATL_Set_Line_Pattern)(BSTR pattern);
	
		/* A wrapper for HOOPS/3dGS ::Set_Line_Weight */
	STDMETHOD(HATL_Set_Line_Weight)(float weight);
	
		/* A wrapper for HOOPS/3dGS ::Set_Marker_Size */
	STDMETHOD(HATL_Set_Marker_Size)(float weight);
	
		/* A wrapper for HOOPS/3dGS ::Set_Marker_Symbol */
	STDMETHOD(HATL_Set_Marker_Symbol)(BSTR symbol);
	
		/* A wrapper for HOOPS/3dGS ::Set_Modelling_Matrix */
	STDMETHOD(HATL_Set_Modelling_Matrix)(VARIANT *matrix_var);
	
	/* A wrapper for HOOPS/3dGS ::Set_Normal */
	STDMETHOD(HATL_Set_Normal)(float x, float y, float z);
	
	/* A wrapper for HOOPS/3dGS ::Set_Parameter */
	STDMETHOD(HATL_Set_Parameter)(int number, VARIANT *parameters_var);
	
	/* A wrapper for HOOPS/3dGS ::Set_Polygonal_Clip_Region */
	STDMETHOD(HATL_Set_Polygonal_Clip_Region)(int count, VARIANT *points_var, BSTR options);
		
	/* A wrapper for HOOPS/3dGS ::Set_Priority */
	STDMETHOD(HATL_Set_Priority)(HC_KEY key, long priority);
	
	/* A wrapper for HOOPS/3dGS ::Set_Region */
	STDMETHOD(HATL_Set_Region)(int region);
	
	/* A wrapper for HOOPS/3dGS ::Set_Rendering_Options */
	STDMETHOD(HATL_Set_Rendering_Options)(BSTR rendering_options);
	
	/* A wrapper for HOOPS/3dGS ::Set_Selectability */	
	STDMETHOD(HATL_Set_Selectability)(BSTR list);
	
	/* A wrapper for HOOPS/3dGS ::Set_Streaming_Mode */	
	STDMETHOD(HATL_Set_Streaming_Mode)(BSTR flag);
	
	/* A wrapper for HOOPS/3dGS ::Set_Text_Alignment */	
	STDMETHOD(HATL_Set_Text_Alignment)(BSTR locater);
	
	/* A wrapper for HOOPS/3dGS ::Set_Text_Font */	
	STDMETHOD(HATL_Set_Text_Font)(BSTR text_font);
	
	/* A wrapper for HOOPS/3dGS ::Set_Text_Path */	
	STDMETHOD(HATL_Set_Text_Path)(float x, float y, float z);
	
	/* A wrapper for HOOPS/3dGS ::Set_Text_Region */	
	STDMETHOD(HATL_Set_Text_Region)(int pCount, VARIANT *points_var, BSTR options);
	
	/* A wrapper for HOOPS/3dGS ::Set_Text_Spacing */	
	STDMETHOD(HATL_Set_Text_Spacing)(float spacing);
	
	/* A wrapper for HOOPS/3dGS ::Set_Texture_Matrix */	
	STDMETHOD(HATL_Set_Texture_Matrix)(VARIANT *matrix_var);
	
	/* A wrapper for HOOPS/3dGS ::Set_Trim_Operation */	
	STDMETHOD(HATL_Set_Trim_Operation)(int index, BSTR operation);
	
	/* A wrapper for HOOPS/3dGS ::Set_Unicode_Options */	
	STDMETHOD(HATL_Set_Unicode_Options)(VARIANT *options_var);
	
	/* A wrapper for HOOPS/3dGS ::Set_User_Index */	
	STDMETHOD(HATL_Set_User_Index)(int index, VARIANT *data_var);
	
	/* A wrapper for HOOPS/3dGS ::Set_User_Options */	
	STDMETHOD(HATL_Set_User_Options)(BSTR list);

	/* 
	  Method: ::Update_Display wrapper
 	  \return HRESULT
	*/
	STDMETHOD(Update)();

	/* A wrapper for HOOPS/3dGS ::Set_Visibility */
	STDMETHOD(HATL_Set_Visibility)(BSTR vis);

	/* A wrapper for HOOPS/3dGS ::Set_Variable_Edge_Weight */	
	STDMETHOD(HATL_Set_Variable_Edge_Weight)(BSTR weight);
	
	/* A wrapper for HOOPS/3dGS ::Set_Variable_Line_Weight */
	STDMETHOD(HATL_Set_Variable_Line_Weight)(BSTR weight);
	
	/* A wrapper for HOOPS/3dGS ::Set_Variable_Marker_Size */
	STDMETHOD(HATL_Set_Variable_Marker_Size)(BSTR weight);
	
	/* A wrapper for HOOPS/3dGS ::Set_Window */	
	STDMETHOD(HATL_Set_Window)(float left, float right, float bottom, float top);
	
	/* A wrapper for HOOPS/3dGS ::Set_Window_Frame */	
	STDMETHOD(HATL_Set_Window_Frame)(BSTR flag);
	
	/* A wrapper for HOOPS/3dGS ::Set_Window_Pattern */	
	STDMETHOD(HATL_Set_Window_Pattern)(BSTR pattern);

	
	
	/* Unset functions */

	/* A wrapper for HOOPS/3dGS ::UnSet_Camera */
	STDMETHOD(HATL_UnSet_Camera)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Color */	
	STDMETHOD(HATL_UnSet_Color)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Color_Map */	
	STDMETHOD(HATL_UnSet_Color_Map)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Driver_Options */	
	STDMETHOD(HATL_UnSet_Driver_Options)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Edge_Pattern */	
	STDMETHOD(HATL_UnSet_Edge_Pattern)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Edge_Weight */	
	STDMETHOD(HATL_UnSet_Edge_Weight)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Face_Pattern */	
	STDMETHOD(HATL_UnSet_Face_Pattern)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Handedness */	
	STDMETHOD(HATL_UnSet_Handedness)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Heuristics */	
	STDMETHOD(HATL_UnSet_Heuristics)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Line_Pattern */	
	STDMETHOD(HATL_UnSet_Line_Pattern)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Line_Weight */	
	STDMETHOD(HATL_UnSet_Line_Weight)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Marker_Size */	
	STDMETHOD(HATL_UnSet_Marker_Size)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Marker_Symbol */	
	STDMETHOD(HATL_UnSet_Marker_Symbol)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Modelling_Matrix */	
	STDMETHOD(HATL_UnSet_Modelling_Matrix)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Normal */	
	STDMETHOD(HATL_UnSet_Normal)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_Color */	
	STDMETHOD(HATL_UnSet_One_Color)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_Driver_Option */	
	STDMETHOD(HATL_UnSet_One_Driver_Option)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_Heuristic */	
	STDMETHOD(HATL_UnSet_One_Heuristic)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_Rendering_Option */	
	STDMETHOD(HATL_UnSet_One_Rendering_Option)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_Selectability */	
	STDMETHOD(HATL_UnSet_One_Selectability)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_Text_Font */	
	STDMETHOD(HATL_UnSet_One_Text_Font)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_User_Index */	
	STDMETHOD(HATL_UnSet_One_User_Index)(long which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_User_Option */	
	STDMETHOD(HATL_UnSet_One_User_Option)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_One_Visibility */	
	STDMETHOD(HATL_UnSet_One_Visibility)(BSTR which);
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Parameter */	
	STDMETHOD(HATL_UnSet_Parameter)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Rendering_Options */	
	STDMETHOD(HATL_UnSet_Rendering_Options)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Selectability */	
	STDMETHOD(HATL_UnSet_Selectability)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Streaming_Mode */
	STDMETHOD(HATL_UnSet_Streaming_Mode)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Text_Alignment */
	STDMETHOD(HATL_UnSet_Text_Alignment)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Text_Font */
	STDMETHOD(HATL_UnSet_Text_Font)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Text_Path */
	STDMETHOD(HATL_UnSet_Text_Path)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Text_Spacing */
	STDMETHOD(HATL_UnSet_Text_Spacing)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Texture_Matrix */
	STDMETHOD(HATL_UnSet_Texture_Matrix)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_User_Options */
	STDMETHOD(HATL_UnSet_User_Options)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Visibility */
	STDMETHOD(HATL_UnSet_Visibility)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Window */
	STDMETHOD(HATL_UnSet_Window)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Window_Frame */
	STDMETHOD(HATL_UnSet_Window_Frame)();
	
	/* A wrapper for HOOPS/3dGS ::UnSet_Window_Pattern */
	STDMETHOD(HATL_UnSet_Window_Pattern)();
	


	/* Define functions */
	
	/* A wrapper for HOOPS/3dGS ::Define_Alias */
	STDMETHOD(HATL_Define_Alias)(BSTR name, BSTR expansion);
	
	/* A wrapper for HOOPS/3dGS ::Define_Color_Name */
	STDMETHOD(HATL_Define_Color_Name)(BSTR name, BSTR er_name, BSTR ish_name, BSTR definition);
	
	/* A wrapper for HOOPS/3dGS ::Define_Font */
	STDMETHOD(HATL_Define_Font)(BSTR name, BSTR options, int data_length, VARIANT *data_var);
	
	/* A wrapper for HOOPS/3dGS ::Define_Glyph */
	STDMETHOD(HATL_Define_Glyph)(BSTR name, int data_size, BSTR data);
	
	/* A wrapper for HOOPS/3dGS ::Define_Line_Style */
	STDMETHOD(HATL_Define_Line_Style)(BSTR name, BSTR definition);
	
	/* A wrapper for HOOPS/3dGS ::Define_Local_Texture */
	STDMETHOD(HATL_Define_Local_Texture)(BSTR name, BSTR definition);
	
	/* A wrapper for HOOPS/3dGS ::Define_System_Options */
	STDMETHOD(HATL_Define_System_Options)(BSTR list);
	
	/* A wrapper for HOOPS/3dGS ::Define_Texture */
	STDMETHOD(HATL_Define_Texture)(BSTR name, BSTR definition);



	/* unsorted */
	
	/* A wrapper for HOOPS/3dGS ::Show_Color */
	STDMETHOD(HATL_Show_Color)(/*[out, retval]*/BSTR *color_spec);
	
	/* A wrapper for HOOPS/3dGS ::Show_Alias */
	STDMETHOD(HATL_Show_Alias)(BSTR alias, /*[out, retval]*/BSTR *expansion);
	
	/* A wrapper for HOOPS/3dGS ::Show_Button */
	STDMETHOD(HATL_Show_Button)(/*[out, retval]*/BSTR *button);
	
	/* A wrapper for HOOPS/3dGS ::Show_Button_Source */
	STDMETHOD(HATL_Show_Button_Source)();
	
	


	/* 
	  property: Indicates if Current File has Model Structure Information
	  \param pVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(get_HasModelStructureInfo)(/*[out, retval]*/ BOOL *pVal);
	/*! 
	  method: Sets Selection Color for Markers
	  \param r Red Component
	  \param g Green Component
	  \param g Blue Component
	  \param a Alpha Component
 	  \return HRESULT
	*/
	STDMETHOD(SetSelectionMarkerColor)(float r, float g, float b, float a);
	/*! 
	  method: Sets Selection Color for Edges
	  \param r Red Component
	  \param g Green Component
	  \param g Blue Component
	  \param a Alpha Component
 	  \return HRESULT
	*/
	STDMETHOD(SetSelectionEdgeColor)(float r, float g, float b, float a);
	/*! 
	  method: Sets Selection Color for Faces
	  \param r Red Component
	  \param g Green Component
	  \param g Blue Component
	  \param a Alpha Component
 	  \return HRESULT
	*/
	STDMETHOD(SetSelectionFaceColor)(float r, float g, float b, float a);
	/* 
	  property: Indicates if Smooth Transition is set
	  \param pVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(get_SmoothTransitionMode)(/*[out, retval]*/ BOOL *pVal);
	/* 
	  property: Set Smooth Transition 
	  \param pVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(put_SmoothTransitionMode)(/*[in]*/ BOOL newVal);
	/* 
	  property: Indicates if Data Navigator mode is set
	  \param pVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(get_DataNavigatorMode)(/*[out, retval]*/ BOOL *pVal);
	/* 
	  property: Indicates if undo is possible
	  \param pVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(get_UndoAvailable)(/*[out, retval]*/ BOOL *pVal);
	/* 
	  property: Indicates if redo is possible
	  \param pVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(get_RedoAvailable)(/*[out, retval]*/ BOOL *pVal);
	/* 
	  property: Sets Data Navigator Mode
	  \param newVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(put_DataNavigatorMode)(/*[in]*/ BOOL newVal);
	/* 
	  property: Sets path for configuration file
	  \param newVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(put_ConfigFile)(BSTR newVal);
	/* 
	  property: Retrieve path for configuration file
	  \param newVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(get_ConfigFile)(BSTR *newVal);
	/* 
	  property: Sets path for default configuration file
	  \param newVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(put_DefaultConfigFile)(BSTR newVal);

 	STDMETHOD(put_SegmentDL)(/*[in]*/ BOOL newVal);
  	STDMETHOD(get_SegmentDL)(/*[out, retval]*/ BOOL *pVal);

		/* 
	  property: Sets TransparencyOptions
	  \param newVal String
 	  \return HRESULT
	*/
	STDMETHOD(get_TransparencyOptions)(BSTR *newVal);
	STDMETHOD(put_TransparencyOptions)(BSTR newVal);

	/* 
	  property: Sets HOOPS driver
	  \param newVal String
 	  \return HRESULT
	*/
	STDMETHOD(get_DriverType)(BSTR *newVal);
	STDMETHOD(put_DriverType)(BSTR newVal);
	/* 
	  property: Sets Type of Framerate Mode (FramerateFixed, FramerateTarget, FramerateOff)
	  \param newVal String
 	  \return HRESULT
	*/
	STDMETHOD(put_FramerateType)(BSTR newVal);
	STDMETHOD(get_FramerateType)(BSTR *pVal);

	/* 
	  property: Sets Culling Threshold Value
	  \param newVal Integer
 	  \return HRESULT
	*/
	STDMETHOD(put_CullingThreshold)(int newVal);
	STDMETHOD(get_CullingThreshold)(int *pVal);

	/* 
	  property: Sets Maximum Threshold Value for Framerate
	  \param newVal Integer
 	  \return HRESULT
	*/
	STDMETHOD(put_MaximumThreshold)(int newVal);
	STDMETHOD(get_MaximumThreshold)(int *pVal);

	/* 
	  property: Retrieves path for default configuration file
	  \param newVal Boolean
 	  \return HRESULT
	*/
	STDMETHOD(get_DefaultConfigFile)(BSTR *newVal);
	/*! 
	  method: Show Options Dialog
  	  \return HRESULT
	*/
	STDMETHOD(ShowOptionsDialog)();

	/*! 
	  method: Retrieves full path from Index 
	  \param index Index to retrieve path from
	  \param pPath Full Path 
 	  \return HRESULT
	*/
	STDMETHOD(GetPathFromIndex)(/*[in]*/ int index, /*[out, retval]*/ BSTR *pPath);
	/*! 
	  method: Convert Key to persistent Identifier
	  \param key HOOPS key (as text string)
	  \param pIndex Persistent Index for object associated to given key
 	  \return HRESULT
	*/
	STDMETHOD(KeyToIndex)(/*[in]*/ BSTR key, /*[out, retval]*/ int* pIndex);
	/* 
	  property: Retrieves status of given cutting plane
	  \param name Name of cutting plane segment
	  \param pVal Boolean indicating if cutting plane is currently active
 	  \return HRESULT
	*/
	STDMETHOD(get_CuttingPlaneStatus)(BSTR name, /*[out, retval]*/ BOOL *pVal);
	/*! 
	  method: Activates a number of different actions which do not require additional parameters
	  \param command Command to execute
  	  \return HRESULT
	*/
	STDMETHOD(Run)(BSTR command);
	/* 
	  property: Retrieves camera projection mode
	  \param pVal Projection Mode (perspective, orthographic,etc)
  	  \return HRESULT
	*/
	STDMETHOD(get_ProjectionMode)(/*[out, retval]*/ BSTR *pVal);
	/* 
	  property: Sets camera projection mode
	  \param pVal Projection Mode (perspective, orthographic,etc)
  	  \return HRESULT
	*/
	STDMETHOD(put_ProjectionMode)(/*[in]*/ BSTR newVal);
	/* 
	  property: Sets Opengl or direct3d software rendering
	  \param newVal Boolean
  	  \return HRESULT
	*/
	STDMETHOD(put_SoftwareRendering)(/*[in]*/ BOOL newVal);
	/* 
	  property: Retrieves the current setting for software rendering
	  \param newVal Boolean
  	  \return HRESULT
	*/
	STDMETHOD(get_SoftwareRendering)(/*[out, retval]*/ BOOL *pVal);

	/*! 
	  method: Select entity by HOOPS key
	  \param key HOOPS key
  	  \return HRESULT
	*/
	STDMETHOD(Select)(BSTR key);
	/*! 
	  method: Select entity by persistent identifier
	  \param identifier Persinstent Identifier
  	  \return HRESULT
	*/
	STDMETHOD(SelectFromIdentifier)(int identifier);
	/*! 
	  method: Select entity by HOOPS segment path
	  \param path Segment Path
  	  \return HRESULT
	*/
	STDMETHOD(SelectFromPath)(BSTR path);

	/*! 
	  method: Adds valid file types (used in SaveAs and FileLoad Dialogs)
	  \param filetype File Type Extension
  	  \return HRESULT
	*/
	STDMETHOD(AddFileType)(BSTR filetype);

	/*! 
	  method: Modify given identifier by looking at its parents
	  \param oldidentifier Identifier to filter
	  \param newidentifier Identifier after filtering
  	  \return HRESULT
	*/
	STDMETHOD(FilterIdentifier)(int oldidentifier, int *newidentifier);

	/*! 
	  method: Generates model Structure XML file from specified level
	  \param level level to start XML generation from
	  \param filepath File to store xml data to
   	  \return HRESULT
	*/
	STDMETHOD(GenerateNavigationInfo)(int level, BSTR *filepath);
	/*! 
	  method: Generates model Structure XML file starting from specified path
	  \param nodepath Path to start XML generation from
	  \param filepath File to store xml data to
   	  \return HRESULT
	*/
	STDMETHOD(GenerateNavigationInfoFromNodePath)(BSTR nodepath, BSTR *filepath);

	/*! 
	  method: Shows Page Setup Print Dialog
    	  \return HRESULT
	*/
	STDMETHOD(ShowPageSetupDialog)();
	/*! 
	  method: Shows Print Dialog
    	  \return HRESULT
	*/
	STDMETHOD(ShowPrintDialog)();
	/*! 
	  method: Performs a copy to clipboard of current scene
    	  \return HRESULT
	*/

	STDMETHOD(CopyToClipboard)();
	/*! 
	  method: Shows "Save As" dialog
      \return HRESULT
	*/
	STDMETHOD(ShowFileSaveDialog)();



	/*! 
	  Method:Displays File Open Dialog Window
 	  \return HRESULT
	*/
	STDMETHOD(ShowFileOpenDialog)();

	/*! 
	  Method: Set Rendermode
	  \param rendermode Rendermode string (shaded, flat, gouraud, wireframe, hidden line)
	  \return HRESULT
	*/
	STDMETHODIMP SetRenderMode(BSTR rendermode);



	/*! 
	  Method: Show specific cutting plane
	  \param  name Name of cutting plane to show/hide
	  \param  onoff Show or hide cutting plane
 	  \return HRESULT
	*/
	STDMETHOD(ShowCuttingPlane)(BSTR name, BOOL onoff);

	/*! 
	  Method: Play Animation
 	  \return HRESULT
	*/
	STDMETHOD(BhvPlay)(); 
	/*! 
	  Method: Flush Currently Loaded Scene
 	  \return HRESULT
	*/
	STDMETHOD(FlushScene)();

	/*! 
	  Method: Pause ANimation
 	  \return HRESULT
	*/
	STDMETHOD(BhvPause)(); 
	/*! 
	  Method: Rewind Animation
 	  \return HRESULT
	*/
	STDMETHOD(BhvRewind)();

	/*! 
	  Method: open model segment
 	  \return HRESULT
	*/
	STDMETHOD(OpenModelSegment)();
	/*! 
	  Method: open scene segment
 	  \return HRESULT
	*/
	STDMETHOD(OpenSceneSegment)();

	/*! 
	  Method: Turn framerate logic on/off
	  \param onoff true = framerate on, false = framerate off
	  \return HRESULT
	*/
	STDMETHOD(SetFramerateMode)(BOOL onoff);
	/*! 
	  Method: Turn backplane culling on/off
	  \param onoff true = backplane culling on, false = backplane culling off
	  \return HRESULT
	*/
	STDMETHOD(SetBackplaneCullingMode)(BOOL onoff);
	/*! 
	  Method: Set no polygon handedness
 	  \return HRESULT
	*/
	STDMETHOD(SetPolygonHandednessNone)();
	/*! 
	  Method: Set polygon handedness right
 	  \return HRESULT
	*/
	STDMETHOD(SetPolygonHandednessRight)();
	/*! 
	  Method: set polygon handedness left
 	  \return HRESULT
	*/
	STDMETHOD(SetPolygonHandednessLeft)();
	/*! 
	  Method: antialias current scene
 	  \return HRESULT
	*/
	STDMETHOD(AntialiasScene)();
	/*! 
	  Method: Turn smooth shadow  on/off
	  \param onoff true = shadow on, false = shadow off
	  \return HRESULT
	*/
	STDMETHOD(SetShadowMode)(BOOL onoff);
	/*! 
	  Method: set orthographic projection
 	  \return HRESULT
	*/
	STDMETHOD(SetProjectionModeOrthographic)();
	/*! 
	  Method: set perpective projection
 	  \return HRESULT
	*/
	STDMETHOD(SetProjectionModePerspective)();
	/*! 
	  Method: save/restore markup layer
	  \param layernum markup layer
	  \return HRESULT
	*/
	STDMETHOD(SaveRestoreMarkup)(int layernum);
	/*! 
	  Method: set isometric camera view
 	  \return HRESULT
	*/
	STDMETHOD(SetCameraToIsometric)();
	/*! 
	  Method: set YX camera view
 	  \return HRESULT
	*/
	STDMETHOD(SetCameraToPlaneYX)();
	/*! 
	  Method: set ZY camera view
 	  \return HRESULT
	*/
	STDMETHOD(SetCameraToPlaneZY)();
	/*! 
	  Method: set ZX camera view
 	  \return HRESULT
	*/
	STDMETHOD(SetCameraToPlaneZX)();
	/*! 
	  Method: set YZ camera view
 	  \return HRESULT
	*/
	STDMETHOD(SetCameraToPlaneYZ)();
	/*! 
	  Method: set XZ camera view
 	  \return HRESULT
	*/
	STDMETHOD(SetCameraToPlaneXZ)();
	/*! 
	  Method: Set the front and up direction of the camera.
 	  \return HRESULT
	*/
	STDMETHOD(SetViewAxis)(float fx, float fy, float fz,
							float tx, float ty, float tz);	/*! 
	  Method: set XY camera view
 	  \return HRESULT
	*/
	STDMETHOD(SetCameraToPlaneXY)();
	/*! 
	  Method: insert interactive cutting plane
 	  \return HRESULT
	*/
	STDMETHOD(InsertCuttingPlane)();
	/*! 
	  Method: set hidden line render mode
 	  \return HRESULT
	*/
	STDMETHOD(SetRenderModeHiddenLine)();
	/*! 
	  Method: set wireframe render mode
 	  \return HRESULT
	*/
	STDMETHOD(SetRenderModeWireframe)();
	/*! 
	  Method: set gouraud render mode 
 	  \return HRESULT
	*/
	STDMETHOD(SetRenderModeGouraud)();
	/*! 
	  Method: set gouraud render mode with edges on
 	  \return HRESULT
	*/
	STDMETHOD(SetRenderModeGouraudWithEdges)();
	/*! 
	  Method: set flat render mode
 	  \return HRESULT
	*/
	STDMETHOD(SetRenderModeFlat)();
	/*! 
	  Method: set shaded render mode
 	  \return HRESULT
	*/
	STDMETHOD(SetRenderModeShaded)();
	/*! 
	  Method: set operator
	  \param operator_name name of operator (as defined in HOp...::GetName()
 	  \return HRESULT
	*/
	STDMETHOD(SetOperator)(BSTR operator_name);
	/*! 
	  Method: set window background colors
  	  \return HRESULT
	*/
	STDMETHOD(SetBackgroundColors)(float r_top, float g_top, float b_top, float r_bottom, float g_bottom, float b_bottom, int percent);
	
	/*! 
	  Method: set ambient color
  	  \return HRESULT
	*/
	STDMETHOD(SetAmbientColor)(float r_top, float g_top, float b_top);
 

	/* 
	  Property: Get current file type
	  \param pVal file type (either 2dmodel or 3dmodel)
	  \return HRESULT
	*/
	STDMETHOD(get_AllowMenu)(/*[out, retval]*/ BOOL *pVal);
	/* 
	  Property: Set current file type
	  \param newVal file type (either 2dmodel or 3dmodel)
	  \return HRESULT
	*/
	STDMETHOD(put_AllowMenu)(/*[in]*/ BOOL newVal);

 
	/* 
	  Property: Get current file type
	  \param pVal file type (either 2dmodel or 3dmodel)
	  \return HRESULT
	*/
	STDMETHOD(get_FileType)(/*[out, retval]*/ BSTR *pVal);
	/* 
	  Property: Set current file type
	  \param newVal file type (either 2dmodel or 3dmodel)
	  \return HRESULT
	*/
	STDMETHOD(put_FileType)(/*[in]*/ BSTR newVal);
	/* 
	  Property: Get no orbit operator flag
	  \param pVal true = no orbit operator allowed, false = orbit operator allowed
	  \return HRESULT
	*/
  	STDMETHOD(get_NoOrbit)(/*[out, retval]*/ BOOL *pVal);
	/* 
	  Property: Set no orbit operator flag
	  \param newVal true = no orbit operator allowed, false = orbit operator allowed
	  \return HRESULT
	*/
	STDMETHOD(put_NoOrbit)(/*[in]*/ BOOL newVal);

	/* 
	  Property: Get Antialiasing Flag
	  \param pVal true = use antialiasing step during constant framerate, false = no antialiasing
	  \return HRESULT
	 */
  	STDMETHOD(get_Antialiasing)(/*[out, retval]*/ BOOL *pVal);

	/* 
	  Property: Set Antialiasing Flag
	  \param newVal true = use antialiasing step during constant framerate, false = no antialiasing
	  \return HRESULT
	  */
	STDMETHOD(put_Antialiasing)(/*[in]*/ BOOL newVal);


  	STDMETHOD(get_FrameRate)(/*[out, retval]*/ float *pVal);

	/* 
	  property: Sets desired Framerate (in sec)
	  \param newVal float
 	  \return HRESULT
	*/
	STDMETHOD(put_FrameRate)(/*[in]*/ float newVal);


	/* 
	  Property: Set Hardware Antialiasing Flag
	  \param newVal true = use hardware antialiasing, false = no hardware antialiasing
	  \return HRESULT
	  */
	STDMETHOD(put_HardwareAntialiasing)(/*[in]*/ BOOL newVal);
	/* 
	  Property: Get Hardware Antialiasing Flag
	  \param pVal true = use hardware Antialiasing, false = no antialiasing
	  \return HRESULT
	 */
  	STDMETHOD(get_HardwareAntialiasing)(/*[out, retval]*/ BOOL *pVal);

	/* 
	  Property: Set Entity Selection Antialiasing Flag
	  \param newVal true = use entity selection, false = no entity selection
	  \return HRESULT
	  */
	STDMETHOD(put_AllowEntitySelection)(/*[in]*/ BOOL newVal);
	/* 
	  Property: Get Entity Selection Flag
	  \param pVal true = use entity selection, false = no entity selection
	  \return HRESULT
	 */
  	STDMETHOD(get_AllowEntitySelection)(/*[out, retval]*/ BOOL *pVal);


 
	/* 
	  Property: Sets Continues play animation setting indicating if animation should loop
	  \param newVal boolean
	  \return HRESULT
	 */
	STDMETHOD(put_BhvContinuousPlay)(/*[in]*/ BOOL newVal);
 
	/* 
	  Property: Retrieves Continues play animation setting indicating if animation should loop
	  \param newVal boolean
	  \return HRESULT
	 */
  	STDMETHOD(get_BhvContinuousPlay)(/*[out, retval]*/ BOOL *pVal);


	/* 
	  Property: Set AxisMode Flag
	  \param newVal true = display axis, false = no axis
	  \return HRESULT
	  */
	STDMETHOD(put_AxisMode)(/*[in]*/ BOOL newVal);
	/*
	  Property: Get AxisMode Flag
	  \param pVal true = Display Axis, false = no axis
	  \return HRESULT
	 */
  	STDMETHOD(get_AxisMode)(/*[out, retval]*/ BOOL *pVal);

	/* 
	  Property: Get Last Returned Key
	  \param pVal Last key that was returned by a call
	  \return HRESULT
	 */
  	STDMETHOD(get_Key)(/*[out, retval]*/ LONG *pVal);

	/* 
	  Property: Get Last Returned String
	  \param pVal Last string that was returned by a call
	  \return HRESULT
	 */
  	STDMETHOD(get_String1)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_String2)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_String3)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Int1)(/*[out, retval]*/ int *pVal);

	/* 
	  Property: Get control embed state
	  \param PVal true = will be embedded, false = will not be embedded
	  \return HRESULT
	*/
  	STDMETHOD(get_Embed)(/*[out, retval]*/ BOOL *pVal);

	/* 
	  Property: Set Segment Display Listz
	  \param newVal true = on, false = off
	  \return HRESULT
	*/

	/* 
	  Property: Set Segment Display List
	  \param newVal true = on, false = off
	  \return HRESULT
	*/
	STDMETHOD(put_AntialiasingLevel)(/*[in]*/ int newVal);
	STDMETHOD(get_AntialiasingLevel)(/*[out]*/ int *pVal);

	/* 
	  Property: Set Segment Display List
	  \param newVal true = on, false = off
	  \return HRESULT
	*/
	STDMETHOD(put_StaticModel)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_StaticModel)(/*[out]*/ BOOL *pVal);

	/* 
	  Property: Set Static Tree
	  \param newVal true = on, false = off
	  \return HRESULT
	*/
	STDMETHOD(put_Embed)(/*[in]*/ BOOL newVal);

	/* 
	  Property: Get camera parameters
	  \param pVal returns current camera position, target, up-vector, width, height as string
	  \return HRESULT
	*/
	STDMETHOD(get_CameraParameters)(/*[out, retval]*/ BSTR *pVal);
	/*! 
	  Property: Set camera parameters
	  \param px  camera position x parameter
	  \param py  camera position y parameter
	  \param pz  camera position z parameter
	  \param tx  camera target x parameter
	  \param ty  camera target y parameter
	  \param tz  camera target z parameter
	  \param ux  camera up-vector x parameter
	  \param uy  camera up-vector y parameter
	  \param uz  camera up-vector z parameter
	  \param width camera width
	  \param height  camera height
	  \return HRESULT
	*/
	STDMETHOD(SetCamera)(float px, float py, float pz, float tx, float ty, float tz, float ux, float uy, float uz, float width, float height);
	/*! 
	  Property: Fit camera to scene extents
 	  \return HRESULT
	*/
   	STDMETHOD(FitWorld)();
	/* 
	  Property: Get name of current operator
	  \param pVal operator name
	  \return HRESULT
	*/
	STDMETHOD(get_CurrentOperator)(/*[out, retval]*/ BSTR *pVal);

	/* 
	  Property: Get comma separated string listing all model structure types
	  \param pVal boolean
	  \return HRESULT
	*/
	STDMETHOD(get_ModelStructureTypeList)(/*[out, retval]*/ BSTR *pVal);

 	/*! 
	  Property: Abort download of current stream file
 	  \return HRESULT
	*/
	STDMETHOD(AbortDownload)();
	/* 
	  Property: Get size of currently downloading file
	  \param pVal file size
	  \return HRESULT
	*/
	STDMETHOD(get_DownloadDataMax)(/*[out, retval]*/ long *pVal);
	/* 
	  Property: Get amount of data already dowloaded for currently donwloading file
	  \param pVal amount of data already donwloaded
	  \return HRESULT
	*/
	STDMETHOD(get_DownloadDataReceived)(/*[out, retval]*/ long *pVal);
	/* 
	  Property: Get download in progress state
	  \param pVal true = streaming in progress, false = no streaming in progress
	  \return HRESULT
	*/
	STDMETHOD(get_DLinProgress)(/*[out, retval]*/ BOOL *pVal);






	/* 
	  Property: Get name of currently loaded file
	  \param pVal name of file
 	  \return HRESULT
	*/
 	STDMETHOD(get_Filename)(/*[out, retval]*/ BSTR *pVal);

	/* 
	  Property: Set name of file for download
	  \param newVal name of file
 	  \return HRESULT
	*/
	STDMETHOD(put_Filename)(/*[in]*/ BSTR newVal);

	/*
		Property: Sets if we flush the model before loading a new one with
		put_Filename or put_LocalFilename.
		\param newVal true if we want to flush the model (default). false if
		we want to leave the geometry in the model when loading a new model.
 		\return HRESULT
	*/
	STDMETHOD(put_FlushOnLoad)(/*[in]*/ BOOL newVal);

	/*
		Property: Gets if we flush the model before loading a new one with
		put_Filename or put_LocalFilename.
		\param newVal true if we want to flush the model (default). false if
		we want to leave the geometry in the model when loading a new model.
 		\return HRESULT
	*/
	STDMETHOD(get_FlushOnLoad)(/*[out, retval]*/ BOOL *pVal);
	
	/* 
	  Property: Sets model structure filter used to limit selection to parent entities
	  \param newVal Name of entity
 	  \return HRESULT
	*/
	STDMETHOD(put_ModelStructureFilter)(/*[in]*/ BSTR newVal);
	
	/* 
	  Property: Get State of Control in progress state
	  \param pVal true = control window is visible, false = control window is not visible
	  \return HRESULT
	*/
	STDMETHOD(get_ControlActive)(/*[out, retval]*/ BOOL *pVal);
	/* 
	  Property: Get State of Control in progress state
	  \param pVal true = control window is visible, false = control window is not visible
	  \return HRESULT
	*/
	STDMETHOD(get_IsPlaying)(/*[out, retval]*/ BOOL *pVal);

	/*! 
	  Property: Activates all animations on current dataset
  	  \return HRESULT
	*/
	STDMETHOD (BhvActivateAllAnimations)();
	/*! 
	  Property: DeActivates all animations on current dataset
  	  \return HRESULT
	*/
	STDMETHOD (BhvDeactivateAllAnimations)();
	/*! 
	  Property: Activate one animation
	  \param animationname Name of animation
	  \param allowPartial Allow partial name match in animation name
  	  \return HRESULT
	*/
	STDMETHOD (BhvActivateAnimation)(BSTR animationname, BOOL allowPartial);
	/*! 
	  Property: DeActivate one animation
	  \param animationname Name of animation
	  \param allowPartial Allow partial name match in animation name
  	  \return HRESULT
	*/
	STDMETHOD (BhvDeactivateAnimation)(BSTR animationname, BOOL allowPartial);
	/*! 
	  Property: Start one animation
	  \param animationname Name of animation
   	  \return HRESULT
	*/
	STDMETHOD (BhvStartAnimation)(BSTR animationname);
	/*! 
	  Property: Stop one animation
	  \param animationname Name of animation
   	  \return HRESULT
	*/
	STDMETHOD (BhvStopAnimation)(BSTR animationname);
	/*! 
	  Property: Rewind one animation
	  \param animationname Name of animation
   	  \return HRESULT
	*/
	STDMETHOD (BhvRewindAnimation)(BSTR animationname);
 

	/*! 
	  Method: Turn Infinite Play On/Off (looping animations will play infinitely)
	  \param onoff true = infinite play on, false = infinite play off
	  \return HRESULT
	*/
	STDMETHOD(BhvSetInfinitePlay)(BOOL onoff);
	



	/*! 
	  Reads configuration file and configures viewer settings
  	  \return HRESULT
	*/
	STDMETHOD(ConfigureFromFile)();

	/*! 
		Overloaded "Create" Function. Initializes various class members.
 	*/
	HWND Create( HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED, DWORD dwExStyle = 0, UINT nID = 0 );

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)





	/*! 
	  Message: OnDraw message handler
	  \param di drawinfo structure
 	  \return HRESULT
	*/
	HRESULT OnDraw(ATL_DRAWINFO& di);

	/*! 
	  Retrieves Individual property of configuration item
	  \param tagname Name of Tag for configuration item
 	  \param propertyname Name of Property to retrieve
	  \param result Contents of requested property
 	  \param configurationlist Optional list of configuration items (if 0 list assosicated to control is used)
	  \return Result
	*/
	bool GetConfigProperty(char *tagname, char *propertyname, char *result, vlist_s *configurationlist = 0);
	/*!
	  Retrieves XMLTag Object from tagname
	  \param tagname Name of Tag to retrieve
 	  \return HUtilityXMLTag object
	*/
	HUtilityXMLTag * GetConfigTag(char *tagname);



	/*! 
	  Read Configuration file and update configuration list
	  \param ConfigFile Configuration File to read from
	  \param ConfigurationList List of Configuration Items
	  \return Result
	*/
	bool ReadConfigFile(char *ConfigFile, struct vlist_s *ConfigurationList);


	/*! 
	  Get HCtrlView object
 	  \return HCtrlView Pointer
	*/
	HCtrlView* GetHoopsView();

	/*! 
	 Convert Wide Character String (BSTR) to Multibyte String (char)
	 \param mbstr Multibyte String (returned)
	 \param wcstr Wide Character String
	 \param count Size of Wide Character String
 	*/
	static void ConvertToChar(char *mbstr, const wchar_t *wcstr, size_t count);
	/*! 
	 Convert Multibyte String (char) to Wide Character String (BSTR)
	 \param wcstr Wide Character String (returned)
	 \param mbstr Multibyte String
	 \param count Size of Multibyte String
 	*/
	static void ConvertToBSTR(wchar_t *wcstr, const char *mbstr, size_t count)	;
	/*! 
	  Restore Camera from stored values
 	  \return true = camera has been restored, false = camera could not be restored
	*/
	bool RestoreCamera();
	/*! 
	 Set file type of currently loaded file (2d or 3d)
	  \param modeltype true = 2d model , false = 3d model
 	*/
	void Set2dModel(bool modeltype);
	/*! 
	 Enable/Disable orbit operator selectability
	 \param noorbit true = orbit operator is deselected and greyed out in right click menu, orbit operator not 
	 grayed out
 	*/
	void SetNoOrbit(bool noorbit);

	/*! 
	Returns Pointer to DataLoader 
	\return DataLoader Pointer
  	*/
	CDataLoader * GetDataLoader() { return m_pDataLoader; }

 	
	/* 
		Registry "Patch" Function that ensures IDL file gets correctly processed
   	*/
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
	{
		_ATL_REGMAP_ENTRY entries[3];
		
		
		
		wchar_t key1[256];
		wchar_t data1[256];
		wchar_t key2[256];
		wchar_t data2[256];
		
		FixGuid("CLSIDCTRLCLASS", CLSID_HOOPS3DSTREAMCTRL_CLASS, key1, data1);
		FixGuid("CLSIDTYPELIB", CLSID_HOOPS3DSTREAMCTRL_TYPELIB, key2, data2);
		
		entries[0].szKey = key1;
		entries[0].szData = data1;
		entries[1].szKey = key2;
		entries[1].szData = data2;
		entries[2].szKey = 0;
		entries[2].szData = 0;
		
		_Module.UpdateRegistryFromResource(IDR_Hoops3dStreamCTRL, 
			bRegister, entries);
		
		return 1;
	}

	
	/*! 
	 Shows the standard File-Open dialog box and returns the name of the file chosen. 
	  \param ret_filename_buff TCHAR array to receive the fully qualified file name chosen by the user
	  \param buff_size		size of the filename buffer provided
	  \param owner	window handle to the owner. Defaults to null.
	  return S_OK if succeeds
 	*/
	HRESULT ShowFileDialog(TCHAR * ret_filename_buff, unsigned int buff_size, HWND owner = 0);
	/*! 
	 Shows the standard File-Open dialog box and returns the name of the file chosen. 
	  \param ret_filename_buff TCHAR array to receive the fully qualified file name chosen by the user
	  \param buff_size		size of the filename buffer provided
	  \param owner	window handle to the owner. Defaults to null.
	  return S_OK if succeeds
 	*/
	static HRESULT ShowFileDialog2(TCHAR * ret_filename_buff, unsigned int buff_size, HWND owner = 0);

	/*! 
	 Shows the standard File-Save As dialog box and returns the name of the file chosen. 
	  \param ret_filename_buff TCHAR array to receive the fully qualified file name chosen by the user
	  \param buff_size		size of the filename buffer provided
	  \param owner	window handle to the owner. Defaults to null.
	  return S_OK if succeeds
 	*/
	static HRESULT ShowFileSaveDialog(TCHAR * ret_filename_buff, unsigned int buff_size, HWND owner = 0);

	/* XML Read Callback */
	static void *XMLCallback(HUtilityXMLTag *xt, bool open, void *m_pExtraData);
 
	/*! 
		Saves current configuration information to file
  	*/

	void SerializeConfiguration();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

 
	/* 
		Overloaded Internal Method
  	*/
	STDMETHOD(UIDeactivate)(void)
	{
		SendOnDataChange();
	 	IOleInPlaceObjectWindowlessImpl<CHoops3dStreamCtrl>::UIDeactivate();
		return S_OK;
	}


	/* 
		Overloaded Internal Method
  	*/
	STDMETHOD(InPlaceDeactivate)(void)
	{
 		SendOnDataChange();
		CComPtr<IOleInPlaceObject> pIPO;
		ControlQueryInterface(__uuidof(IOleInPlaceObject), (void**)&pIPO);
		if (pIPO)
			IOleInPlaceObjectWindowlessImpl<CHoops3dStreamCtrl>::InPlaceDeactivate();
		else
		{
			// based off of:
			// inline HRESULT CComControlBase::IOleInPlaceObject_InPlaceDeactivate(void)

			m_bInPlaceActive = FALSE;

			// if we have a window, tell it to go away.
			//
			if (m_hWndCD)
			{
				//ATLTRACE(atlTraceControls,2,_T("Destroying Window\n"));
				if (::IsWindow(m_hWndCD))
					DestroyWindow();
				m_hWndCD = NULL;
			}

			if (m_spInPlaceSite)
				m_spInPlaceSite->OnInPlaceDeactivate();
		}
		return S_OK;
	}

	STDMETHOD(Close)(DWORD dwSaveOption)
	{
		CComPtr<IOleInPlaceObject> pIPO;
		ControlQueryInterface(__uuidof(IOleInPlaceObject), (void**)&pIPO);
		if (pIPO)
			return IOleObjectImpl<CHoops3dStreamCtrl>::Close(dwSaveOption);
		else
		{
			// based off of:
			// inline HRESULT CComControlBase::IOleObject_Close(DWORD dwSaveOption)

			// handle the save flag.
			//
			if ((dwSaveOption == OLECLOSE_SAVEIFDIRTY ||
				dwSaveOption == OLECLOSE_PROMPTSAVE) && m_bRequiresSave)
			{
				if (m_spClientSite)
					m_spClientSite->SaveObject();
				SendOnSave();
			}

			m_spInPlaceSite.Release();
			m_bNegotiatedWnd = FALSE;
			m_bWndLess = FALSE;
			m_bInPlaceSiteEx = FALSE;
			m_spAdviseSink.Release();
			return S_OK;
		}
		return S_OK;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 	LRESULT OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 	LRESULT OnOrbit(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnFileOpen(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnZoom(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnPan(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnReset(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnWindowColor(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnZoomWindow(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnSmoothTransition(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnToolsVisibilityText(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnToolsVisibilityLines(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnToolsVisibilityFaces(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnAnnotate(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnAddNote(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnRedline(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnSmoothShaded(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnFlatShaded(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnWireframe(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnHiddenLine(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnShadowSmooth(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);

	LRESULT OnPrint(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
 	LRESULT OnCopy(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT OnAboutBox(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
	LRESULT	OnExitMenuLoop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 	LRESULT OnBhvPlay(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
 	LRESULT OnBhvPause(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
 	LRESULT OnBhvRewind(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled);
 	LRESULT OnXMLParsingComplete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	HRESULT IPersistStreamInit_Load(LPSTREAM pStm, const ATL_PROPMAP_ENTRY* pMap);
	HRESULT IPersistStreamInit_Save(LPSTREAM pStm, BOOL fClearDirty, const ATL_PROPMAP_ENTRY* pMap);
	
	bool				FullyQualifyUrl (char *urlname);
	bool				FullyQualifyUnicodeUrl (BSTR urlname);
	bool				BreakUrl (	const char *   urlname,
                                 char *   scheme,
                                 char *   hostname,
                                 char *   path,
                                 bool &  bIsLocalFile);
	bool				BreakUnicodeUrl (	const wchar_t *   urlname,
                                 wchar_t *  scheme,
                                 wchar_t *  hostname,
                                 wchar_t *  path,
                                 bool &  bIsLocalFile);

#endif
 
protected:

	/* 
	  Property: Set name of file for loading from local disk
	  \param newVal name of file
 	  \return HRESULT
	*/
	STDMETHOD(put_LocalFilename)(/*[in]*/ BSTR newVal);

	struct vlist_s*			m_ConfigurationList; /*!< Pointer to Configuration List*/

	HCtrlView *m_pView;							/*!< Pointer to HOOPS View Object*/
	HCtrlDB *m_pHDB;							/*!< Pointer to HOOPS Database Object*/
	HBaseModel *m_pModel;						/*!< Pointer to HOOPS Model Object*/
	CDataLoader *m_pDataLoader;					/*!< Pointer to Dataloader Class*/
	
	struct vlist_s*			m_FileTypeList;		/*!< Pointer to File Type List*/		
 
	bool				m_bMetaPrint;			/*!< Metafile Printing flag*/
	bool				m_bSoftwareRendering;	/*!< Use Software Rendering flag */
	bool				m_bFastPrint;			/*!< Fast Printing flag */
	bool				m_bUseAntialiasing;		/*!< Use Antialiasing flag */
	bool				m_bUseHardwareAntialiasing;		/*!< Use Hardware Antialiasing flag */
	int					m_MetafileType;			/*!< Metafile Type (EMF/WMF) */
	bool				m_bClipboardTruecolor;  /*!< Clipboard is truecolor */
 	BSTR				m_Filename;				/*!< name of currently loaded file */
	bool				m_bFilenameChanged;		/*!< indicates changed filename */
	bool				m_bEmbed;				/*!< indicates if control should be embedded in it's container */
	bool				m_bIs2dModel;			/*!< indicates if loaded model is 2d or 3d type*/
	bool				m_bNoOrbit;			/*!< indicates if loaded model is 2d or 3d type*/
	bool				m_bAllowMenu;			/*!< True: right click menu is enabled*/

  	void				DrawToMetafile (HWND hWnd, HDC hDC);	/*!< serialization of control data to metafile*/
	void				WriteFileToArchive (LPSTREAM pStm);	/*!< serialization of control data*/
	void				ReadFileFromArchive (LPSTREAM pStm);	/*!< deserialization of control data*/
	void				InitModel();			/*!< initial HOOPS model*/
	void  StartDownload();						/*!< download new file*/
	void OnData (CBindStatusCallback<CHoops3dStreamCtrl>* pbsc, BYTE* pBytes, DWORD dwSize); /*!< Callback for new Stream Data*/
	void LocalSetOperator(HBaseOperator * NewOperator);			/*!< change operator*/	

	bool SaveFile( LPCTSTR csFilePathName );	/*!< helper function for save a file */
	bool Print();								/*!< helper function for printing */

	bool				m_bAllowEntitySelection;		/*!< Use Entity Selection flag */
	int					m_iPrintFlag;					/*!< indicates whether printing or not */


	/*! 
	 Retrieves Point Array from Variant
	  \param varKeys Variant containing point array
	  \param array Point Array 
	  \param length	length of point array
  	*/

	void GetPointArrayFromVariant(VARIANT * varKeys, HPoint **array, int &length);
	/*! 
	 Retrieves float Array from Variant
	  \param varKeys Variant containing float array
	  \param array float array 
	  \param length	length of float array
  	*/
	void GetFloatArrayFromVariant(VARIANT * varKeys, float **array, int &length);
	/*! 
	 Retrieves byte Array from Variant
	  \param varKeys Variant containing byte array
	  \param array byte array 
	  \param length	length of byte array
  	*/
	void GetByteArrayFromVariant(VARIANT * varKeys, char **array, int &length);
	/*! 
	 Retrieves arrays of various types from variant
	  \param varKeys Variant containing float array
	  \param arrayfloat float array 
	  \param arrayint integer array 
	  \param arraychar byte array 
	  \param length	length of array
  	*/
	void GetArrayFromVariant(VARIANT * varKeys, float **arrayfloat, int **arrayint, char **arraychar, int &length);
	/*! 
	 Retrieves arrays of various types from variant
	  \param varKeys Variant containing float array
	  \param ret_array void array
	  \param arraychar char array
	  \param length	length of array
  	*/
	void GetArrayFromVariant2(VARIANT * varKeys, void **ret_array, char *type, int &length);
	/*! 
	 Retrieves integer Array from Variant
	  \param varKeys Variant containing integer array
	  \param arrayint integer array 
	  \param length	length of integer array
  	*/
	void GetIntegerArrayFromVariant(VARIANT * varKeys, int **arrayint, int &length);

	/*! 
	 Retrieves short integer Array from Variant
	  \param varKeys Variant containing short integer array
	  \param arrayshort short integer array 
	  \param length	length of short integer array
  	*/
	void GetShortArrayFromVariant(VARIANT * varKeys, short **arrayshort, int &length);



 	// MVO event handlers
	/* 
	 Selection Event
   	*/
	static bool signal_selected(int signal, void *signal_data, void *user_data);
	/* 
	 Selection handler
   	*/
	bool OnSignalSelected();

	/* 
	 Deselect All Event
   	*/
	static bool signal_deselected_all(int signal, void *signal_data, void *user_data);
	/* 
	 Deselect All handler
   	*/
	bool OnSignalDeSelectedAll();

	/* 
	 Creates and realizes a Windows palette
   	*/
	void MakePalette();


private:

	bool				m_text;
	bool				m_lines;
	bool				m_faces;
	FramerateMode		m_FramerateType;
	HPALETTE			m_pPalette;
	HC_KEY				m_activelayerkeys[NUM_MARKUP_LAYERS];
	int					m_cx, m_cy;
	HPoint				m_camPosition, m_camTarget, m_camUp;
	HPoint				m_window_top_color, m_window_bottom_color, m_ambient_color;
	float				m_camWidth, m_camHeight;
	char				m_camProjection[256];
	bool				m_bCameraRestored; 
	IWebBrowserApp *    m_pInternetExplorer;
	static void FixGuid(char *in1, char *in2, wchar_t *out1, wchar_t *out2);
	unsigned long		MapFlags( unsigned long state );
	bool				OperatorStarted();	
	bool IsVisible(char *geom);		
	bool  ContainerIsIE (void);
	bool				m_bJustCreated;
	TCHAR				stemp[4096];
	char 				ctemp[4096];
	char				m_DriverType[4096];
	char				m_TransparencyOptions[4096];
	char 				m_ConfigFile[4096];
	char 				m_DefaultConfigFile[4096];
	AxisMode			m_StoredAxisMode;
	long				m_CookieSelected;		// cookie for HSignalSelected signal subscription
	long				m_CookieDeSelectedAll;	// cookie for HSignalDeSelectedAll signal subscription
	bool				m_bContinuousPlay;
	bool				m_bFirstRun;
	bool				m_bShadowMode;
	bool				m_bDataNavigatorMode;
	HC_KEY				LastKey;				// stores the key of the last object inserted
	char				String1[4096];			// stores a return string
	char				String2[4096];			// stores a return string
	char				String3[4096];			// stores a return string
	int					Int1;					// stores a return int
	bool				m_bFlushOnLoad;
	bool				m_bFileOpenActive;
	bool				m_bSegmentDL;
	bool				m_bStaticModel;
	int					m_AntialiasingLevel;
	int					m_CullingThreshold;
	int					m_MaximumThreshold;
	float				m_FrameRate;
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	    if (!m_pView)
		    DefWindowProc(uMsg, wParam, lParam);
 		return 0;
	}
	LRESULT OnToolsOptimizemodel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnToolsSaveas(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	static HHOOK hHook;
	static bool menuActive;

	static void create_mouse_hook(HINSTANCE hinst);
	static LRESULT CALLBACK mouse_hook_callback(int code,WPARAM wParam, LPARAM lParam);	
	static void set_menu_active(bool active);
};





//!  Custom HTK_Bounding class. Used to correctly setup camera for stream file processing
class TK_Custom_Bounding : public HTK_Bounding 
{

private:

	CHoops3dStreamCtrl * m_pControl;

public:

    /*! Overloaded constructor */
	TK_Custom_Bounding(unsigned char opcode, CHoops3dStreamCtrl * pCtrl) : HTK_Bounding(opcode) { m_pControl = pCtrl; }
	
	TK_Status   Execute (BStreamFileToolkit & tk) alter;	/*!< Custom Execute Logic*/

};






#endif //__Hoops3dStreamCTRL_H_
