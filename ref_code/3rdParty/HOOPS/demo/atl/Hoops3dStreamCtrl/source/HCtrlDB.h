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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/HCtrlDB.h,v 1.5 2006-08-07 20:38:46 stage Exp $
//

// HDB.h : interface of the HDB class
// serves as a wrapper class for an instance of the HOOPS database


#ifndef _HCtrlDB_H
#define _HCtrlDB_H

#include "hc.h"
#include "hdb.h"

//! A HOOPS/ATL specific implmentation of the HOOPS/MVO HDB class
/*! 
    HCtrlDB keeps track of both number of driver instances and to generate a unique instance id for each driver
    as drivers may be created and deleted a number of times.

*/

class HCtrlDB : public HDB
{
		
public:
	/*! 
		Constructor
		\param pszDriverType HOOPS Display Driver Type
		\param pszInstanceBase HOOPS Window Instance
	 
	*/
                HCtrlDB    (const char * pszDriverType, const char * pszInstanceBase);
                HCtrlDB    (void);
               ~HCtrlDB    (void);
	/*! 
		Class Initialization	 
	*/
	void			Init ();

	/*! 
		Increment reference count
	 
	*/
    static void		AddRef      (void); 
	/*! 
		Decrement reference count
	 
	*/
    static void		ReleaseRef  (void);

	/*! 
		\return Current reference count	 
	*/
 	static int		GetRefCount() { return m_nRefCount;} 
 
    static int         m_nRefCount;            	/*!< Number of driver instances */
};

#endif

