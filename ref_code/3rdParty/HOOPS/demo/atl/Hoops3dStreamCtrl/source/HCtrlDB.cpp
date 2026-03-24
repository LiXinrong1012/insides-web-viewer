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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/HCtrlDB.cpp,v 1.20 2006-08-07 20:38:46 stage Exp $
//

#include "StdAfx.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "HCtrlDB.h"

#include "hversion.h"

#ifndef _UNICODE
#define CtU(x,y)     (strcpy(y, x), y)
#define UtC(x,y)     (strcpy(y, x), y)
#define UtC2(x,y,z)     (memcpy(y, x,z), y[z] = 0, y)
#else
#define CtU(x,y)     (mbstowcs(y, x, strlen(x) + 1), y)
#define UtC(x,y)     (wcstombs(y, x, 1000), y)
#define UtC2(x,y,z)     (wcstombs(y, x, z), y[z] = 0, y)
#endif

	

int 	HCtrlDB::m_nRefCount = 0;
   
 
HCtrlDB::HCtrlDB (void)
    : HDB ()
{
 
}

HCtrlDB::HCtrlDB (const char * pszDriverType, const char * pszInstanceBase)
    : HDB ()
    
{

 
	
}

HCtrlDB::~HCtrlDB (void)
{
//    assert (m_nRefCount == 0);
}

void HCtrlDB::Init(void)
{	 
	TCHAR stemp[4096];
#ifdef INTERNAL_RELEASE_LICENSE
	HC_Define_System_Options( INTERNAL_RELEASE_LICENSE );
	HC_Define_System_Options("no warnings, no info, no errors, no fatal errors, no message limit");
#else
	HC_Define_System_Options("no message limit");
//	HC_Define_System_Options("warnings = on, no info, errors = on, no message limit");
#endif
	HC_Define_System_Options("multi-threading = full");


    HDB::Init ();

	// set the font directory
	char fontDirectory[MAX_PATH+32];
	::GetWindowsDirectory(stemp, MAX_PATH);
	UtC(stemp, fontDirectory);
	strcat(fontDirectory, "\\Fonts");
	char buf[MAX_PATH+64];
	sprintf(buf, "font directory = %s", fontDirectory);
	HC_Define_System_Options(buf);
}



/*! Increases the reference count which denotes the current number of driver instances */
void HCtrlDB::AddRef (void)
{   
    m_nRefCount++; 
}

/*! Decreases the reference count which denotes the current number of driver instances */
void HCtrlDB::ReleaseRef (void)
{
	    m_nRefCount--;
}
