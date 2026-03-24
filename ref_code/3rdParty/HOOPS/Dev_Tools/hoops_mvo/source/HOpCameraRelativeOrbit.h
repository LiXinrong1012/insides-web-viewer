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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HOpCameraRelativeOrbit.h,v 1.8 2007-11-13 22:31:16 jason Exp $
//

// HOpCameraRelativeOrbit.h : interface of the HOpCameraRelativeOrbit class
// orbits the camera of current view usual a virtual trackball
// interface

#ifndef _HOPCAMERARELATIVEORBIT_H
#define _HOPCAMERARELATIVEORBIT_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HBaseOperator.h"
#include "HOpCameraOrbit.h"


//! The HOpCameraRelativeOrbit class provides interactive orbiting of the camera around elements in the scene.
/*! 
  HOpCameraRelativeOrbit implements three mouse event methods defined on the base class and maps the event information to 
  the HOOPS routine #HC_Orbit_Camera. This operation consists of the following steps:
  <ol>
  <li>Left Button Down:				The orbit is initiated.
  <li>Left Button Down and Drag:	The camera orbits around a point.
  <li>Left Button Up:				The operation ends.
  </ol>
  More Detailed Description: see event methods. 
*/
class MVO_API HOpCameraRelativeOrbit : public HOpCameraOrbit
{
public:

	/*!
	  Constructs an HOpCameraRelativeOrbit object.
	  \param view A pointer to an HBaseView object.
	  \param DoRepeat An integer denoting whether this is a repeatable operator.  This parameter has been deprecated.
	  \param DoCapture An integer denoting whether the mouse state should be captured, which means that all mouse events 
	  should be received after a mousedown, even if it leaves the window.  This parameter has been deprecated.
	*/  	
  		HOpCameraRelativeOrbit (HBaseView* view, int DoRepeat=0, int DoCapture=1); 
	virtual ~HOpCameraRelativeOrbit();

	/*!
		\return A pointer to a character string denoting the name of the operator which is 'HOpCameraRelativeOrbit'.
	*/
	virtual const char * GetName();  

	/*!
		OnLButtonDown draws a bounding box around the scene, records the mouse position, and maps the mouse 
		position to spherical coordinates around the clicked object.  
		\param hevent An HEventInfo object containing information about the current event.
		\return An #HOperatorReturn indicating the status of the event.
	*/
	virtual int OnLButtonDown(HEventInfo &hevent);

	/*!
		OnLButtonDownAndMove records points as the mouse is moved, maps the points to spherical coordinates, and calculates 
		the appropriate values for #HC_Orbit_Camera and #HC_Roll_Camera.  It also updates the position of the default light, depending 
		on whether you have set the light to follow the camera.
		\param hevent An HEventInfo object containing information about the current event.
		\return An #HOperatorReturn indicating the status of the event.
	*/
 	virtual int OnLButtonDownAndMove(HEventInfo &hevent);
 

	/*! 
	  Creates a new operator which is a copy of the current operator.  The user is 
	  responsible for deleting the newly created operator.
	  \return A pointer to the newly created HOpCameraRelativeOrbit object.
	*/
	virtual HBaseOperator * Clone();  


	/*!
		Sets the center point for camera rotation.
 		\param c The center point for the camera rotation.
	*/
	void SetCenter(HPoint c) { m_ptCentroid = c; m_bCenterSet = true; };  
	
	/*!
		Get center point for camera rotation
 		\return The center point for the camera rotation.
	*/
	HPoint GetCenter() { return m_ptCentroid; };  


private:
 	HPoint	m_ptCentroid;
	bool	m_bCenterSet;
};

#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif



