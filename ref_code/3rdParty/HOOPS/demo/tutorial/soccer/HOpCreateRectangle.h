// HOpCreateRectangle.h : interface of the HOpCreateRectangle class, derived from HOpConstructRectangle

#ifndef _HOpCreateRectangle_H
#define _HOpCreateRectangle_H

#include "HTools.h"
#include "HOpConstructRectangle.h" 

//! The HOpCreateRectangle class inserts a 2D rectangle into the model segment.
/*! 
  HOpCreateRectangle reimplements one of the mouse methods defined on the base class and maps the event information
  to operator routines. See the event method for a more detailed description
*/  
class HOpCreateRectangle : public HOpConstructRectangle
{
public:
	/*! constructor */
    HOpCreateRectangle(HBaseView* view, int DoRepeat=0, int DoCapture=1);
	~HOpCreateRectangle();

	/*!
		\return A pointer to a character string denoting the name of the operator  'Create Rectangle'
	*/
	virtual const char * GetName();  

	/*!
		Takes the construction rectangle information and inserts a rectangle into the model segment
		\param event An HEventInfo object containing information about the current event.
		\return A value indicating the result of the event handling.
	*/
    virtual int OnLButtonUp(HEventInfo &event);  
	
	HBaseOperator * Clone();  /*! returns a pointer to a copy of the operator */
};
#endif	// _HOpCreateRectangle_H