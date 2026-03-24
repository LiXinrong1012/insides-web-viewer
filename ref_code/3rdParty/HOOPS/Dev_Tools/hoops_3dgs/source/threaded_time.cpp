/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.13 2010-10-06 19:16:07 jason Exp $
 */

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(

#include "hoops.h"

#ifndef DISABLE_MUTEX

#include "hi_proto.h"
#include "hpserror.h"
#include "driver.h"

#if defined( WIN32_SYSTEM ) && !defined( NUTCRACKER )

DWORD _hoops_IPGRGR()
{
	static DWORD _hoops_CPGRGR = 0;
 	LARGE_INTEGER v,f;
	QueryPerformanceCounter(&v);
	QueryPerformanceFrequency(&f);
	return v.QuadPart/(f.QuadPart/1000);

}
#else
#include <sys/time.h>
#endif




typedef struct {
	unsigned long		_hoops_CRAPR;
	unsigned long		_hoops_SPGRGR;
	unsigned long		_hoops_GHGRGR;
	HThreadHandle		_hoops_RHGRGR;
	HM_Semaphore		_hoops_AHGRGR;
	volatile bool	_hoops_HCRCI;
}	Time_Data;


GLOBAL_FUNCTION void HI_Init_Time (void) {
	Time_Data		*_hoops_IAAPR;

	ZALLOC (_hoops_IAAPR, Time_Data);
	HOOPS_WORLD->_hoops_GPAPR = (void *)_hoops_IAAPR;

#if defined( WIN32_SYSTEM ) && !defined( NUTCRACKER )
	_hoops_IAAPR->_hoops_GHGRGR = _hoops_IAAPR->_hoops_SPGRGR = GetTickCount();
#else
	{
	struct timeval	_hoops_CAAPR;
	gettimeofday (&_hoops_CAAPR, 0);
	_hoops_IAAPR->_hoops_CRAPR = _hoops_CAAPR.tv_sec;
	_hoops_IAAPR->_hoops_SPGRGR = _hoops_CAAPR.tv_usec/1000;
	}
#endif

}




GLOBAL_FUNCTION void HI_Free_Time (void) {
	Time_Data	*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;

	if (_hoops_IAAPR->_hoops_RHGRGR) {
		_hoops_IAAPR->_hoops_HCRCI = true;
		HM_RELEASE_SEMAPHORE (_hoops_IAAPR->_hoops_AHGRGR, 1);
		JOIN_THREAD(_hoops_IAAPR->_hoops_RHGRGR);
		HM_DESTRUCT_SEMAPHORE(_hoops_IAAPR->_hoops_AHGRGR);
	}

	FREE (_hoops_IAAPR, Time_Data);
}

#if 0
#include <stdio.h>
#endif

GLOBAL_FUNCTION _hoops_GSPGR HI_What_Time (void) {
	Time_Data		*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	_hoops_GSPGR			_hoops_PHGRGR;
	unsigned long	_hoops_HHGRGR;
	unsigned long	_hoops_IHGRGR;
	unsigned long	_hoops_CHGRGR;

#if defined( WIN32_SYSTEM ) && !defined( NUTCRACKER )
	_hoops_CHGRGR = GetTickCount();

	if (_hoops_IAAPR->_hoops_GHGRGR > _hoops_CHGRGR) {
		_hoops_IHGRGR = _hoops_CHGRGR;
		_hoops_IAAPR->_hoops_CRAPR += (~0L-_hoops_IAAPR->_hoops_SPGRGR)/1000;
		_hoops_IAAPR->_hoops_SPGRGR=0;
	}
	else
		_hoops_IHGRGR = _hoops_CHGRGR - _hoops_IAAPR->_hoops_SPGRGR;

	_hoops_HHGRGR = _hoops_IAAPR->_hoops_CRAPR;
	_hoops_IAAPR->_hoops_GHGRGR = _hoops_CHGRGR;

	_hoops_PHGRGR = _hoops_HHGRGR*(_hoops_GSPGR)_hoops_HSPGR + _hoops_IHGRGR*(_hoops_GSPGR)_hoops_HSPGR/1000.0;

#if 0
	{
 		char        buffer[1024];
		sprintf (buffer, "%f %ld %ld\n", _hoops_PHGRGR, _hoops_HHGRGR, _hoops_IHGRGR);
		OutputDebugString (buffer);
	}
#endif

#else
	{
	struct timeval	_hoops_CAAPR;	

	gettimeofday (&_hoops_CAAPR, 0);

	_hoops_HHGRGR=_hoops_CAAPR.tv_sec - _hoops_IAAPR->_hoops_CRAPR;
	_hoops_CHGRGR = _hoops_CAAPR.tv_usec/1000;

	if (_hoops_IAAPR->_hoops_SPGRGR > _hoops_CHGRGR) {
		_hoops_HHGRGR--;
		_hoops_IHGRGR = (1000+_hoops_CHGRGR) - _hoops_IAAPR->_hoops_SPGRGR;
	}
	else
		_hoops_IHGRGR = _hoops_CHGRGR - _hoops_IAAPR->_hoops_SPGRGR;

	_hoops_PHGRGR = _hoops_HHGRGR*(_hoops_GSPGR)_hoops_HSPGR + _hoops_IHGRGR*(_hoops_GSPGR)_hoops_HSPGR/1000.0;

#if 0
	fprintf(stderr, "%ld %ld %ld %ld %ld\n", 
			_hoops_IAAPR->_hoops_CRAPR, _hoops_IAAPR->_hoops_SPGRGR, 
			_hoops_HHGRGR, _hoops_IHGRGR, _hoops_PHGRGR);
	fflush(stderr);
#endif
	}
#endif

	*HOOPS_WORLD->time_stamp=_hoops_PHGRGR;

	return _hoops_PHGRGR;
}

GLOBAL_FUNCTION void HI_Sleep(_hoops_GSPGR _hoops_SPAPR) {

	MILLI_SECOND_SLEEP(_hoops_SPAPR);

}


THREAD_FUNCTION(hoops_timer_task) {

	Time_Data	*_hoops_IAAPR = THREAD_FUNCTION_DATA(Time_Data *);

	HI_Set_Thread_Name (-1, "Hoops Timer", false);

    while (!_hoops_IAAPR->_hoops_HCRCI) {
		HM_RELEASE_SEMAPHORE (_hoops_IAAPR->_hoops_AHGRGR, 1);
		MILLI_SECOND_SLEEP(_hoops_HIAPR);
        _hoops_PIAPR (true);
		HM_WAIT_SEMAPHORE (_hoops_IAAPR->_hoops_AHGRGR);
    }

	return 0;
}


GLOBAL_FUNCTION bool HI_Enable_Timer_Interrupts (void) {

	Time_Data	*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;

    if (_hoops_IAAPR->_hoops_RHGRGR) {
		HM_RELEASE_SEMAPHORE (_hoops_IAAPR->_hoops_AHGRGR, 1);
    }
    else {
		HM_CONSTRUCT_SEMAPHORE(_hoops_IAAPR->_hoops_AHGRGR,1,0);
		_hoops_IAAPR->_hoops_HCRCI=false;
		CREATE_THREAD(_hoops_IAAPR->_hoops_RHGRGR, hoops_timer_task, _hoops_IAAPR);
    }

    return true;
}

GLOBAL_FUNCTION void HI_Disable_Timer_Interrupts (void) {

	Time_Data	*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;

	if (_hoops_IAAPR->_hoops_RHGRGR)
		HM_WAIT_SEMAPHORE (_hoops_IAAPR->_hoops_AHGRGR);

}



#endif /* _hoops_HCAPR */
