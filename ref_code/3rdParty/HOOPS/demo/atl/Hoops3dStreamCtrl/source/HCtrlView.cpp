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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/HCtrlView.cpp,v 1.25 2009-02-06 22:09:58 guido Exp $
//
 
#include "stdafx.h"

#include "HCtrlView.h"
#include "HBaseModel.h"
#include "HOpCameraOrbit.h"
#include "HSelectionSet.h"
#include "HCtrlDB.h"
#include <math.h>
#include <stdio.h>


#include "hc.h"

#define DEBUG_NO_WINDOWS_HOOK			0x00000040
#define DEBUG_16BIT_ZBUFFER		0x00200000

#define PROGRESS_WIDTH 90					 
#define PROGRESS_HEIGHT 70					 

static    HPoint co, to, uo;
static float   widtho, heighto;


/*! 
    Custom constructor.
    \param pModel A pointer to the HBaseModel object associated with this view (with this control)
	\param pDB    A pointer to the HCtrlDB object associated with this control's module
*/
HCtrlView::HCtrlView (HBaseModel * pModel)
    : HBaseView (pModel)
    , m_bRealDriver (false)
{    
 	m_bBoundingBox=false;
  	m_bSceneDetached = false;
	m_progresskey = 0;
 
}

HCtrlView::HCtrlView(HBaseModel *model,
    const char * 		alias,	
    const char *		driver_type,
	const char *		instance_name,
    void *		window_handle,
    void *		colormap) : HBaseView(model,alias,driver_type,instance_name,window_handle,colormap)
	
{
  	m_bSceneDetached = false;
	m_progresskey = 0;
}


 
void HCtrlView::DeleteNullDriver ()
{
    HC_Delete_By_Key (m_ViewKey);
    m_ViewKey = 0;
}

void HCtrlView::DeleteRealDriver ()
{
//    HCtrlDB * pDB = (HCtrlDB *)GetModel()->GetHDB();
//    pDB->DeleteDriver (m_ViewKey);
//    m_ViewKey = 0;
}


/*! Deletes the HOOPS/3dGS driver instance associated with this control */
void HCtrlView::DeleteDriver ()
{
    if (m_bRealDriver)
        DeleteRealDriver ();
    else
        DeleteNullDriver ();

    m_bRealDriver = false;
}

 
/*! Creates an initial segment hierarchy in the HOOPS/3dGS scene-graph which corresponds to a standard HOOPS/MVO view/scene */
void HCtrlView::CreateViewHeirarchy (void)
{
    // Create the view heirarchy
    HC_Open_Segment_By_Key (m_ViewKey);
         m_WindowspaceKey = HC_KCreate_Segment ("windowspace");
    HC_Close_Segment ();
    HC_Open_Segment_By_Key (m_SceneKey);
		m_AxisTriadKey = HC_KCreate_Segment("axis");

    HC_Close_Segment ();

}



/*! Sets up a driver instance which corresponds to a live window display context. 
    \param hWnd Handle to the GDI window associated with the CHoopsControl object 
    \param hPalette Handler to the palette to be used by HOOPS/3dGS for support 8-bit mode.  
	                This is only necessary when using the HOOPS MSW Driver (instead of OpenGL)
					and 8-bit displays need to be supported.
*/
void HCtrlView::ReconfigureView (HWND hWnd, HPALETTE hPalette, char *drivertype)
{
    m_bRealDriver = true;

	AttachScene((void *)hWnd, drivertype);
	CreateViewHeirarchy();


}

/*! Initializes the view object, setting up default window/geometry colors/visibilities, etc... */
void HCtrlView::Init (void)
{
	// Call base's init function first to get the default HOOPS hierarchy for the view
	HBaseView::Init ();
 
  
 	HPoint rgb;

	rgb.Set(1.0, 1.0, 1.0);
	SetWindowColor(rgb);
  	HC_Open_Segment_By_Key(GetViewKey());
	HC_Set_Rendering_Options("no technology");
	HC_Set_Driver_Options("double-buffering");
 
	HC_Begin_Font_Search(".","generic");
	HC_End_Font_Search();
 
	HC_Close_Segment();

 
	SetOperator(new HOpCameraOrbit(this));
	((HOpCameraOrbit *)GetOperator())->SetLightFollowsCamera(true);
	
	HSelectionSet *pSelection = new HSelectionSet(this);
	pSelection->Init();
	SetSelection(pSelection);
 
	HC_Open_Segment_By_Key(GetSceneKey());
	HC_Set_Visibility("edges = off, lines = off");
	// set the color of the lines, edges, markers and text to black
	HC_Set_Color_By_Index("edges, lines, text, markers", 0);
	HC_Open_Segment("notes");
	HC_Set_Text_Font("name = arial.ttf, size = 9pts");
 	HC_Close_Segment();
 	HC_Close_Segment();

	// to be consistent with all our partviewers, set the default coordinate system right handed
	SetHandedness(HandednessRight);
  


}

 




 



void HCtrlView::DoSmoothTransition(bool prepare)
{
 	char    projection[16];

	if (GetSmoothTransition())
	{
	if (prepare)
	{
		HC_Open_Segment_By_Key(GetSceneKey());
			HC_Show_Net_Camera (&co, &to, &uo, &widtho, &heighto, projection);
		HC_Close_Segment();
	}
	else
	{
		HPoint cn, tn, un;
		float   widthn, heightn;
		HC_Open_Segment_By_Key(GetSceneKey());
			HC_Show_Net_Camera (&cn, &tn, &un, &widthn, &heightn, projection);
 
	    HUtility::SmoothTransition(co, to, uo, widtho, heighto, cn, tn, un, widthn, heightn, this);
		HC_Close_Segment();

	    Update();
	}
	}
}

 
void HCtrlView::FitWorld()
{
 
	DoSmoothTransition(true);
	HBaseView::FitWorld();		
	DoSmoothTransition(false);
	CameraPositionChanged( true, GetSmoothTransition());
}

void HCtrlView::FlushFromMessage(const char *in_data, unsigned int data_length)
{
	
	HC_Open_Segment_By_Key(GetSceneKey());
	HC_Open_Segment("notes");
		HC_Flush_Contents(".","geometry, segments");
	HC_Close_Segment();
	HC_Close_Segment();
	
	HBaseView::FlushFromMessage(in_data, data_length);
	
}

 
 

void HCtrlView::SetProgressWindow(int per)
{
	
	if (m_progresskey)
	{
		char text[256];
 		sprintf(text, "%d%%", per);		
		HC_Open_Segment_By_Key(m_progresskey);
  			HC_Flush_Contents(".", "geometry");
			HC_Insert_Text(0,0,0,text);
  		HC_Close_Segment();
	}
}


void HCtrlView::CreateProgressWindow()
{
	
	HC_Open_Segment_By_Key(GetViewKey());  
	m_progresskey = HC_KOpen_Segment("progress");
 	HC_Set_Window(1.0 - 0.3,1.0, -1.0, -1.0 + 0.3);
//	HC_Set_Window_Pattern("clear");
	HC_Set_Camera_By_Volume("stretched",-1,1,-1,1);
//	HC_Set_Color("text = grey");
	HC_Set_Text_Font("name = sans serif, size = 0.4wru");
//	HC_Set_Heuristics("quick moves");
	HC_Close_Segment();
	HC_Close_Segment();
}
void HCtrlView::DeleteProgressWindow()
{
	if (m_progresskey)
	{
		HC_Delete_By_Key(m_progresskey);
		m_progresskey = 0;
	}
}


void HCtrlView::DetachScene()
{
	if (!m_bSceneDetached)
	{
		m_bSceneDetached = true;
		RebindView(0,"null",0,0,0);
	 
	}
}

void HCtrlView::AttachScene(void *hwnd, char *drivertype)
{
 		m_bSceneDetached = false;
		RebindView(0,drivertype,0,hwnd,0);
}




void HCtrlView::GetWindowSize(int &xmax, int &ymax)
{
	HC_Open_Segment_By_Key(GetViewKey());

	char data[256], temp[256];
	HC_Show_Device_Info(".","pixels",data);
	HC_Parse_String(data,",",0,temp);
	xmax = atoi(temp);
	HC_Parse_String(data,",",-1,temp);
	ymax = atoi(temp);
	HC_Close_Segment();
}
 

void HCtrlView::FlushScene()
{
	Flush(true);
	if (GetShadowMode() == HShadowNone)
		SetShadowMode(HShadowNone);
	
 
	HC_Open_Segment_By_Key(GetSceneKey());
 	HC_Control_Update (".", "compute bounding volumes");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(GetModel()->GetModelKey());
	HC_Control_Update (".", "compute bounding volumes");
	HC_Close_Segment();
			
	Update();
}
 
bool HCtrlView::OperatorStarted()
{
		HBaseOperator * op = GetCurrentOperator();
		if (op)
			return op->OperatorStarted();
		else 
			return false;
}
/*

void HCtrlView::SetShadowMode (HShadowMode shadowMode)
{
	HC_KEY shadowkey;
	switch (shadowMode)
	{
	case HShadowNone:
		if (m_ShadowMode != HShadowNone)
		{
			HC_Open_Segment_By_Key(GetSceneKey());
			HC_Delete_Segment("shadows");
			HC_Close_Segment();
		}
		break;
	case HShadowSoft:
		{
			HC_Open_Segment_By_Key(GetSceneKey()); 
			shadowkey = HC_KCreate_Segment("shadows");
			HC_Close_Segment();
			HSmoothShadow myShadow(GetModel()->GetModelKey(), shadowkey);
			ComputeShadowPlane();
			myShadow.Create(m_shadowPlane);				
		}
		break;
		
	case HShadowHard:
		{
			HC_Open_Segment_By_Key(GetSceneKey()); 
			shadowkey = HC_KCreate_Segment("shadows");
			HC_Close_Segment();
			HHardShadow myShadow(GetModel()->GetModelKey(), shadowkey);
			ComputeShadowPlane();
			myShadow.Create(m_shadowPlane);				
		}
		break;
		
	}
	m_ShadowMode = shadowMode;
}
*/

/*! Depending upon the way model is aligned, finds the most suitable of XY, YZ, XZ planes to cast the shadow */
void HCtrlView::ComputeShadowPlane(void)
{
	// get the current viewup vector
	HPoint	position, target, up;
	float	width, height;
	char    projection[16];

	HC_Open_Segment_By_Key(GetSceneKey());
		HC_Show_Net_Camera (&position, &target, &up, &width, &height, projection);
	HC_Close_Segment();

	float coeffx = (float) fabs(up.x);
	float coeffy = (float) fabs(up.y);
	float coeffz = (float) fabs(up.z);
	// I am applying the principal that for a normalized vector, the 
	// angle wrt any axes is inversely proportional to respective coefficient 
	// so, here I try to choose a plane which a closest to being perpendicular
	// to the view up direction
	if( (coeffx >= coeffy) && (coeffx >= coeffz) )
	{
		m_shadowPlane = YZ_PLANE;
		return;
	}
	else if( (coeffy >= coeffx) && (coeffy >= coeffz) )
	{
		m_shadowPlane = XZ_PLANE;
		return;
	}
	else
	{
		m_shadowPlane = XY_PLANE;
		return;
	}
	return;
}

