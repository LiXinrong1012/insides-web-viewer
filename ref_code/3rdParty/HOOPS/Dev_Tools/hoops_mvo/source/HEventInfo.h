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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HEventInfo.h,v 1.73 2009-09-29 19:49:34 evan Exp $
//


//! Interface of the HEventInfo class
/*! \file HEventInfo.h
	Encapusulates information associated with an event
	including the type (timer, keypress or button), location
	in various coordinates systems, and mouse state
*/

#ifndef _HEVENTINFO_H
#define _HEVENTINFO_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HUtility.h"

class HBaseView;

/*! \enum HEventType 
	Defines mouse state, keyboard and timer event types
*/
enum HEventType 
{
	HE_NoEvent,        //!< No event ooccurred.

	HE_LButtonDown,    //!< The left mouse button was pressed.
	HE_LButtonUp,      //!< The left mouse button is up.
	HE_LButtonDblClk,  //!< The left mouse button was double-clicked.

	HE_MButtonDown,    //!< The middle mouse button was pressed.
	HE_MButtonUp,      //!< The middle mouse button is up.
	HE_MButtonDblClk,  //!< The middle mouse button was double-clicked.

	HE_RButtonDown,    //!< The right mouse button was pressed.
	HE_RButtonUp,      //!< The right mouse button is up.
	HE_RButtonDblClk,  //!< The right mouse button was double-clicked.

	HE_MouseMove,      //!< The mouse cursor has moved.

	HE_MouseWheel,     //!< The mouse wheel has moved.
	HE_MouseWheelUp,   //!< The mouse wheel was scrolled up.
	HE_MouseWheelDown, //!< The mouse wheel was scrolled down.
	
	HE_Timer,          //!< self-explanatory

	HE_KeyDown,        //!< A key on the keyboard was pressed.
	HE_KeyUp,          //!< A key on the keyboard was released.

	// Higher level
	HE_Selection,       //!< A general selection event.

	HE_JoyStickTranslate, //!< A 3D Translation vector from a 3D Mouse/Joystick
	HE_JoyStickRotate, //!< A set of Rotation values from a 3D Mouse/Joystick
	HE_JoyStickButton //!< A button press from a 3D Mouse/Joystick
};


//! The HEventInfo class stores and manages event information.
/*! 
  HEventInfo encapusulates information associated with an event, including the type (timer, keypress, or button),
  location in various coordinates systems, mouse state and keypress state.  This is the primary object in MVO that 
  receives event information from the user interface.
*/
class MVO_API HEventInfo 
{

public:

	/*! Constructs an HEventInfo object.
	\param view A pointer to the HBaseView object.*/
	HEventInfo(HBaseView *view); 
	
/*! \def MVO_CONTROL Any Control Key */
#define MVO_CONTROL 1<<1

/*! \def MVO_SHIFT Any Shift Key */
#define MVO_SHIFT 1<<2

/*! \def MVO_ALT Any Alt Key */
#define MVO_ALT 1<<3

/*! \def MVO_LBUTTON Left Mouse Button */
#define MVO_LBUTTON 1<<4

/*! \def MVO_MBUTTON Middle Mouse Button */
#define MVO_MBUTTON  1<<5

/*! \def MVO_RBUTTON Right Mouse Button */
#define MVO_RBUTTON 1<<6

/*! \def MVO_RIGHT_CONTROL Right Control Button */
#define MVO_RIGHT_CONTROL 1<<7

/*! \def MVO_RIGHT_SHIFT Right Shift Button */
#define MVO_RIGHT_SHIFT 1<<8

/*! \def MVO_RIGHT_ALT Right Alt Button */
#define MVO_RIGHT_ALT 1<<9

/*! \def MVO_LEFT_CONTROL Left Control Button */
#define MVO_LEFT_CONTROL 1<<10

/*! \def MVO_LEFT_SHIFT Left Shift Button */
#define MVO_LEFT_SHIFT 1<<11

/*! \def MVO_LEFT_ALT Left Alt Button */
#define MVO_LEFT_ALT 1<<12

/*! \def MVO_LEFT_ARROW Left Arrow Button */
#define MVO_LEFT_ARROW     1<<13

/*! \def MVO_UP_ARROW Up Arrow Button */
#define MVO_UP_ARROW       1<<14

/*! \def MVO_RIGHT_ARROW Right Arrow Button */
#define MVO_RIGHT_ARROW    1<<15

/*! \def MVO_DOWN_ARROW Down Arrow Button */
#define MVO_DOWN_ARROW     1<<16

/*! \def MVO_JOYSTICK_BUTTON_1 Joystick Button 1 */
#define MVO_JOYSTICK_BUTTON_1 1<<17
	
/*! \def MVO_JOYSTICK_BUTTON_2 Joystick Button 2 */
#define MVO_JOYSTICK_BUTTON_2 1<<18

/*! \def MVO_JOYSTICK_BUTTON_3 Joystick Button 3 */
#define MVO_JOYSTICK_BUTTON_3 1<<19

/*! \def MVO_JOYSTICK_BUTTON_4 Joystick Button 4 */
#define MVO_JOYSTICK_BUTTON_4 1<<20
	
/*! \def MVO_JOYSTICK_BUTTON_5 Joystick Button 5 */
#define MVO_JOYSTICK_BUTTON_5 1<<21
	
/*! \def MVO_JOYSTICK_BUTTON_6 Joystick Button 6 */
#define MVO_JOYSTICK_BUTTON_6 1<<22
	
/*! \def MVO_JOYSTICK_BUTTON_7 Joystick Button 7 */
#define MVO_JOYSTICK_BUTTON_7 1<<23
	
/*! \def MVO_JOYSTICK_BUTTON_8 Joystick Button 8 */
#define MVO_JOYSTICK_BUTTON_8 1<<24

	bool Control() const	{ return(m_flags & MVO_CONTROL) != 0; } /*!< \return True if the control key is currently depressed.*/
	bool Shift() const	{ return(m_flags & MVO_SHIFT) != 0; } /*!< \return True if the shift key is currently depressed.*/
	bool Alt() const	{ return(m_flags & MVO_ALT) != 0; } /*!< \return True if the alt key is currently depressed.*/
	bool LeftAlt() const	{ return(m_flags & MVO_LEFT_ALT) != 0; } /*!< \return True if the left alt key is depressed.*/
	bool LeftControl() const { return(m_flags & MVO_LEFT_CONTROL) != 0; } /*!< \return True if the left control key is depressed.*/
	bool LeftShift() const	{ return(m_flags & MVO_LEFT_SHIFT) != 0; } /*!< \return True if the left shift key is depressed.*/
	bool RightAlt() const	{ return(m_flags & MVO_RIGHT_ALT) != 0; } /*!< \returns True if the right alt key is depressed.*/
	bool RightControl() const { return(m_flags & MVO_RIGHT_CONTROL) != 0; } /*!< \return True if the right control key is depressed.*/
	bool RightShift() const { return(m_flags & MVO_RIGHT_SHIFT) != 0; } /*!< \return True if the right shift key is depressed.*/
	bool LButton() const	{ return(m_flags & MVO_LBUTTON) != 0; } /*!< \return True if the left mouse button is depressed.*/
	bool MButton() const	{ return(m_flags & MVO_MBUTTON) != 0; } /*!< \return True if the middle mouse button is depressed.*/
	bool RButton() const	{ return(m_flags & MVO_RBUTTON) != 0; } /*!< \return True if the right mouse button is depressed.*/
	bool LeftArrow() const	{ return(m_flags & MVO_LEFT_ARROW) != 0; } /*!< \return True if the left arrow key is depressed.*/
	bool UpArrow() const	{ return(m_flags & MVO_UP_ARROW) != 0; } /*!< \return True if the up arrow key is depressed.*/
	bool RightArrow() const	{ return(m_flags & MVO_RIGHT_ARROW) != 0; } /*!< \return True if the right arrow key is depressed.*/
	bool DownArrow() const	{ return(m_flags & MVO_DOWN_ARROW) != 0; } /*!< \return True if the down arrow key is depressed.*/

	// Get/Set routines
	HBaseView* GetView( void ) const { return m_pView; }	/*!< \return A pointer to the HBaseView object. */

	const HPoint& GetMousePixelPos( void ) const { return m_ptPixel; }		/*!< \return The mouse position in pixel coordinates. */
	const HPoint& GetMouseWindowPos( void ) const { return m_ptWindow; }		/*!< \return The mouse position in window coordinates. */
	const HPoint& GetMouseWorldPos( void ) const { return m_ptWorld; }		/*!< \return The mouse position in world coordinates. */
	const HPoint& GetMouseViewpointPos( void ) const { return m_ptViewpoint; }/*!< \return The mouse position in viewpoint (camera) coordinates. */
	const HPoint& GetJoystickRotation( void ) const { return m_ptWorld; }		/*!< \return The rotation data from the Joystick or 3D Mouse. */
	const HPoint& GetJoystickTranslation( void ) const { return m_ptWorld; }		/*!< \return The translation data from the Joystick or 3D Mouse. */
	
	/*! \return The key character associated with a keypress event. */
	unsigned int GetChar (void) const { return m_Char; };	
				
	unsigned int GetCharRepCount (void) const { return m_RepCount; }	/*!< \return The number of times the key press event was repeated. */
	unsigned int GetTimerId (void) const {return m_TimerId; }			/*!< \returns The Id number of the current timer event. */
	
	/*! 
	  \return The MVO-specific bit flags like #MVO_LBUTTON for the special key events shift, control, and Left, Middle, and Right mouse
	  buttons.
	*/
	unsigned int GetFlags( void ) const { return m_flags; }


	// EventInfo Initialization
	void SetType(HEventType NewType) { m_EventType = NewType; }	/*!< This method sets the event type on the HEventInfo object. */

	
	/*! \return The eventy type associated to this HEventInfo. */
	HEventType GetType() const { return m_EventType; }

	/*! 
		This method receives and stores mouse event information from the user interface and translates it for use 
		by HOOPS functions. 
		\param NewType The type of event.
		\param x The X coordinate of the mouse event, in window space.
		\param y The Y coordinate of the mouse event, in window space.
		\param NewFlags The bitwise MVO flags for mouse buttons, shift and control Key states.  
		For example, if both the shift key and left mouse button are depressed, pass #MVO_SHIFT|#MVO_LBUTTON.
	*/
	void SetPoint(HEventType NewType, int x, int y, unsigned int NewFlags); 
	

	/*! 
		This method receives and stores mouse event information in pixel coordinates and translates it for use by HOOPS 
		functions. 
		\param NewType The type of event.
		\param NewPoint The point in pixel coordinates.
		\param NewFlags The bitwise MVO flags for mouse buttons, shift and control Key states.  
		For example, if both the shift key and left mouse button are depressed, pass #MVO_SHIFT|#MVO_LBUTTON.
	*/
	void SetPixelPos(HEventType NewType, const HPoint& NewPoint, unsigned int NewFlags);


//for some reason this is unresolved when the csharp/c module links
	/*! 
		This method receives and stores mouse event information in window coordinates and translates it for use by HOOPS 
		functions. 
		\param NewType The type of event
		\param NewPoint The point in window coordinates.
		\param NewFlags The bitwise MVO flags for mouse buttons, shift and control Key states.  
		For example, if both the shift key and left mouse button are depressed, pass #MVO_SHIFT|#MVO_LBUTTON.
	*/
	void SetWindowPos(HEventType NewType, const HPoint& NewPoint, unsigned int NewFlags); 


	/*! 
		This method receives and stores mouse event information in world coordinates and translates it for use by HOOPS 
		functions. 
		\param NewType The type of event.
		\param NewPoint The point in world coordinates.
		\param NewFlags The bitwise MVO flags for mouse buttons, shift and control Key states.  
		For example, if both the shift key and left mouse button are depressed, pass #MVO_SHIFT|#MVO_LBUTTON.
	*/
	void SetWorldPos(HEventType NewType, const HPoint& NewPoint, unsigned int NewFlags);


	/*! 
		This method receives and stores mouse event information in viewpoint (camera) coordinates and translates it for use in by HOOPS functions. 
		\param NewType The type of event
		\param NewPoint The point in viewpoint coordinates.
		\param NewFlags The bitwise MVO flags for mouse buttons, shift and control Key states.  
		For example, if both the shift key and left mouse button are depressed, pass #MVO_SHIFT|#MVO_LBUTTON.
	*/
	void SetViewpointPos(HEventType NewType, const HPoint& NewPoint, unsigned int NewFlags);


	/*! 
		This method receives and stores key event information from the user interface.
		\param NewType The type of event. 
		\param nChar The key character that is currently depressed. 
		\param nRepCnt The number of times the event has been repeated.
		\param NewFlags The bitwise MVO flags for mouse buttons, shift and control Key states.  
		For example, if both the shift key and left mouse button are depressed, pass #MVO_SHIFT|#MVO_LBUTTON.
	*/	
	void SetKey(HEventType NewType, unsigned int nChar, unsigned int nRepCnt, unsigned int NewFlags);

	/*! 
		This method receives and stores timer event information from the user interface.
		\param NewType The type of event. 
		\param nIDEvent The timer ID number generated by the UI.
	*/
	void SetTimer(HEventType NewType, unsigned int nIDEvent);

	/*! 
		This method sets the change value in the Mouse Wheel.
		\param NewWheelDelta The new mouse wheel change value.
 	*/
	void SetMouseWheelDelta(int NewWheelDelta);

	/*! 
		This method sets the bitwise flags that indicates the state of the mouse buttons, shift and control keys.  
		\param flags The bitwise flags for mouse and key states.  For example, if both 
		the shift key and left mouse button are depressed, pass #MVO_SHIFT|#MVO_LBUTTON.
 	*/
	void SetFlags(int flags){
		m_flags = flags;
	}

	/*! 
		\return The change value of the mouse wheel position.  
 	*/
	int GetMouseWheelDelta() const { return m_WheelDelta; }

private:
	int  m_WheelDelta;
	HPoint m_ptPixel; // Mouse position in windows pixel space
	HPoint m_ptWindow; // Mouse position in HOOPS "outer window space"
	HPoint m_ptWorld; // Mouse position in HOOPS world space
	HPoint m_ptViewpoint; // Mouse position in HOOPS world space
	unsigned int m_Char; // character from keyboard event
	unsigned int m_RepCount; // number of times key press event was repeated
	unsigned int m_TimerId;	// Id number of the timer generated by the UI

	float m_time; // System time of event	
	unsigned int m_flags; // Flags indicating which mouse buttons are pressed 
			// and if the "shift" and "control" keyboard keys are pressed

	HEventType m_EventType; // Type of event
	HBaseView* m_pView; // view associated with this event
	
};


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif



