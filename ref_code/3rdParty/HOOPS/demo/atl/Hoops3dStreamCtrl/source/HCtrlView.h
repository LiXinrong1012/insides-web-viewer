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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/HCtrlView.h,v 1.17 2009-02-06 22:09:58 guido Exp $
//

#ifndef _HCTRLVIEW_H
#define _HCTRLVIEW_H

#include "HBaseView.h"
#include "HUtilityShadow.h"


//! Color Type
typedef struct {
    unsigned char r;		/*!< red component*/
    unsigned char g;		/*!< green component*/
    unsigned char b;		/*!< blue component*/
} RGB;

  
 

//! A HOOPS/ActiveX specific implmentation of the HOOPS/MVO HBaseView class
/*! 
	HCtrlView provides additional methods to support ActiveX behaviors.  The HOOPS/MVO HBaseView class that is used
	in conjunction with HOOPS/ActiveX should be based on HCtrlView.  
*/
class HCtrlView : public HBaseView
{
    
public:
	/*! 
	  Constructor
	  \param model Pointer to HBaseMode object
 	*/
	HCtrlView           (HBaseModel * model);
	/*! 
	  Constructor	 
 	*/
	HCtrlView(HBaseModel *model,
	const char * 		alias,	
	const char *		driver_type,
	const char *		instance_name,
	void *		window_handle,
	void *		colormap);
 
	~HCtrlView()
	{
	}


	/*! 
	  General Initialization	 
 	*/	
	void    Init                (void);

	/*! 
	    Creates initial segment hierachy
 	*/	
	void    CreateViewHeirarchy (void);

	/*! 
	    Reconfigures existing view
	    \param hWnd Window Handle
	    \param hPalette Window Palette
		\param drivertype Type of Driver

 	*/	
	void	ReconfigureView (HWND hWnd, HPALETTE hPalette, char *drivertype);
	/*! 
	   Delete Driver Segment
 	*/	
	void    DeleteDriver        (void);
 
 
 
 
	/*! Smooth Transition Fit World
	*/
	void FitWorld();
	/*! Overloaded FlushFromMessage (deletes note geometry)
	*/
	void FlushFromMessage(const char *in_data, unsigned int data_length);


	/*! Bind View to null driver
	*/
 	void DetachScene();
	/*! Rebind view
	*/
	void AttachScene(void *h, char *drivertype);

	/*! Get screen extents of current view
		\param xmax extents in x direction
		\param ymax extents in y direction
	*/
	void GetWindowSize(int &xmax, int &ymax);
	/*! Initialize percentage loading progress display
 	*/
 	void CreateProgressWindow();
	/*! Clean Up Progress Window
 	*/
	void DeleteProgressWindow();
	/*! Set progress percentage
		\param num progress (in percent)
 	*/
	void SetProgressWindow(int num);

	/*! Perform smooth transition
		\param prepare true = retrieve current camera parameters, false = perform transition
 	*/
	void DoSmoothTransition(bool prepare);
	/*!  
		\return true = scene is detached, false = scene is not detached
 	*/
 	bool SceneDetached() { return m_bSceneDetached; }
 
	/*!  Overloaded Flush Scene
  	*/
	void FlushScene();
	/*!  
		\return true = operator has started, false = operator has not started
  	*/

	/*!  Set has camera flag for HSF loading
		\param hascamera true = hsf file has initial camera setting, false = hsf file has no initial camera setting
 	*/
	void SetHasCamera(bool hascamera) { m_hasCamera = hascamera; };
	/*!  
		\return true = hsf file has initial camera setting, false = hsf file has no initial camera setting
  	*/
	bool GetHasCamera() { return m_hasCamera;};

	/*!  
		\return true = ocurrent perator has been started (e.g. user is currently orbiting)
  	*/
	bool OperatorStarted();
	/*! Sets the shadow mode. Use this function to create hard/soft shadow or destroy the shadow
		\param ShadowModeType shadowMode enum to type ShadowModeType, could be NO_SHADOW, SOFT_SHADOW or HARD_SHADOW 
	*/
//	void			SetShadowMode(HShadowMode shadowMode);
 
private:
	void	ComputeShadowPlane(void);
	void    DeleteRealDriver    (void);
	void    DeleteNullDriver    (void);
	bool    m_bRealDriver;
  	bool m_bSceneDetached;
	HC_KEY m_progresskey;
 	bool	m_bBoundingBox;
	bool	m_hasCamera;
	ShadowPlaneType m_shadowPlane;

};


 






#endif _HCTRLVIEW_H
