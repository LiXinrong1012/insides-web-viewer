

// HMyCreateSphere.h : interface of the HMyCreateSphere class
// Creates a sphere using left mouse down and drag

#ifndef _HMYCREATESPHERE_H
#define _HMYCREATESPHERE_H

#include "HTools.h"
#include "HOpCreateSphere.h"

class HMyCreateSphere : public HOpCreateSphere
{
protected:
	float m_NumSides;		/*!< Number of sides */

public:
    HMyCreateSphere (HBaseView* view, int DoRepeat=0, int DoCapture=1, int NumSides = 20);

	/*!
		\return A pointer to a character string denoting the name of the operator  'Create Sphere'
	*/
	virtual const char * GetName();  
   
	/*!
		We'll overload so that we can call HBaseView::CreateSphere with a variable
		indicating num_sides
	*/
	virtual int OnLButtonUp(HEventInfo &event); 

	HBaseOperator * Clone();  /*! returns a pointer to a copy of the operator */
};
#endif
