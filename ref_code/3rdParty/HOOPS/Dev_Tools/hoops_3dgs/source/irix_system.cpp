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
 * $Id: obf_tmp.txt 1.7 2010-10-06 19:16:07 jason Exp $
 */

#include "hoops.h"


#ifdef IRIX_SYSTEM


#include "driver.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "hversion.h"

#include <stdio.h>
#include <stdlib.h>


#define _hoops_GPHPI
#include <signal.h>
#include <siginfo.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syssgi.h> 
#include <errno.h>



GLOBAL_FUNCTION void HI_Reset_Driver_Config_SS (void) {

	HC_Define_Driver_Config("opengl", "*", "*", "config=("
		"UNDRAW_OVERLAY_FRONT_AND_BACK)");
	
	HC_Define_Driver_Config("opengl", "*", "*", "config=(BAD_SINGLE_BUFFERING)");

	HC_Define_Driver_Config("opengl", "DEFAULT", "*", "config=("
		"UNDRAW_OVERLAY_FRONT_AND_BACK)");

	/* _hoops_RPHPI _hoops_APHPI */
	HC_Define_Driver_Config("opengl", "VPRO", "*", "config=("
		"UNDRAW_OVERLAY_FRONT_AND_BACK, EYE_SPACE_DEPTH)");

	if (HOOPS_WORLD->_hoops_PARPR.length != 0)
		HI_Read_Driver_Config_File();
}




GLOBAL_FUNCTION void HI_Start_System_Specific (_hoops_AIGPR *_hoops_RIGC) {
	atexit (HI_Call_Exit_Handlers);
#ifdef _hoops_PPHPI
		_hoops_HPHPI(SIGALRM);
#endif
	signal (_hoops_IPHPI, (_hoops_CPHPI) HI_Call_Exit_Handlers);
	signal (_hoops_SPHPI, (_hoops_CPHPI) HC_Exit_Program);

#ifdef DYNAMIC_LOADER
	HOOPS_WORLD->_hoops_IARPR = HD_IRIX_Load_Dynamic_Driver;
#endif
}

GLOBAL_FUNCTION void HI_Stop_System_Specific (void) {
	/* _hoops_CIH "_hoops_CARPR" _hoops_PPGS, _hoops_RPP _hoops_HAHH */
}



#ifdef DYNAMIC_LOADER

#include <dlfcn.h>

GLOBAL_FUNCTION Driver_Action HD_IRIX_Load_Dynamic_Driver (
	char const *_hoops_HSS) {
		
	char _hoops_SARPR[1024];
	char _hoops_GPRPR[1024];
	void * _hoops_RPRPR;
	char version[20];

	Driver_Action _hoops_APRPR;

	int i=0;

	char * _hoops_PPRPR[][2] = { 
		{ "opengl",		"HD_OpenGL_Driver"},
		{ "xgl",		"HD_XGL_Driver"},
		{ "pdf",        "HD_PDF_Driver"},
		{ "qt",        "HD_QT_Driver"},
		{ "none",		"none" }
	};

	while (1) {
		if (_hoops_AGGR("none", _hoops_PPRPR[i][0]))
			return (Driver_Action)nullroutine;

		if (_hoops_AGGR (_hoops_HSS, _hoops_PPRPR[i][0])) {
			_hoops_AAHR (_hoops_PPRPR[i][1], _hoops_GPRPR);
			break;
		}

		i++;
	}

	sprintf(version,"%d",HOOPS_VERSION);

	_hoops_AAHR ("lib", _hoops_SARPR);
	_hoops_HPRPR (_hoops_HSS, _hoops_SARPR);
	_hoops_HPRPR (version, _hoops_SARPR);
	_hoops_HPRPR ("hdi.so", _hoops_SARPR);

/*
	_hoops_IPRPR("%_hoops_GRI %_hoops_GRI\_hoops_ACHP",_hoops_CPRPR, _hoops_SPRPR);
*/

	_hoops_RPRPR = dlopen(_hoops_SARPR, RTLD_NOW);

	if (!_hoops_RPRPR) 
		return (Driver_Action)nullroutine;


	_hoops_APRPR = (Driver_Action)dlsym(_hoops_RPRPR, _hoops_GPRPR);

	if (!_hoops_APRPR)
		dlclose(_hoops_RPRPR);

	return _hoops_APRPR;
}


GLOBAL_FUNCTION void HD_IRIX_UnLoad_Dynamic_Driver (
	Driver_Action		_hoops_GHRPR) {

	/* _hoops_SR _hoops_CPSA _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_AA _hoops_PA _hoops_ARI, _hoops_GHAP _hoops_RHCA */
	UNREFERENCED(_hoops_GHRPR);
}

#endif /* _hoops_RHRPR */



GLOBAL_FUNCTION bool HI_Find_Application_Name (
	_hoops_HCRPR alter	*name) {

	/* _hoops_RPSRH _hoops_RH _hoops_CCRPR'_hoops_GRI _hoops_RSIRR (_hoops_SCRPR, _hoops_RH _hoops_RGHR _hoops_RSIRR _hoops_IIGR
	 * _hoops_RH _hoops_GSRPR _hoops_CSCR), _hoops_CCPH _hoops_PSAP _hoops_RH _hoops_RSRPR _hoops_AHI,
	 * _hoops_PPR _hoops_SGH _hoops_ASRPR _hoops_PAR _hoops_PSRPR _hoops_IS _hoops_HSRPR _hoops_RH
	 * _hoops_GHPP _hoops_CRGR '_hoops_RSIRR'. _hoops_ISRPR _hoops_PPGAR, _hoops_ASRC _hoops_IHPR.
	 *
	 * _hoops_SPCA _hoops_HRGR _hoops_PCCP _hoops_PCAI _hoops_IIGR _hoops_RGR _hoops_GGR _hoops_RH _hoops_PGIHH _hoops_CSPP _hoops_IIGR _hoops_RGR _hoops_PCPH.
	 */

	char			buf[100];

	/*
	 * _hoops_PAGA: _hoops_RH _hoops_ASRC _hoops_PIRA _hoops_HII _hoops_RGR _hoops_AASA _hoops_HRGR _hoops_ISPC ("80"), _hoops_HIS
	 * _hoops_SR _hoops_SSPC _hoops_SCH, _hoops_PPR _hoops_HPSI _hoops_CCA _hoops_GHHPI[0] _hoops_RIIA.
	 */

	buf[0] = '\0';
	syssgi (_hoops_RHHPI, getpid(), buf, _hoops_GGAPR(buf) - 1);
	if (buf[0] == '\0') return false;

	buf[_hoops_GGAPR(buf) - 1] = '\0';		/* _hoops_GHGPR-_hoops_ISPR _hoops_RH _hoops_RCPHR */
	HI_Copy_Chars_To_Name (buf, name);

	return true;
}



// _hoops_HGAPR _hoops_IGAPR _hoops_CGAPR _hoops_PAAAR _hoops_SGAPR _hoops_GRAPR _hoops_RRAPR
#ifdef DISABLE_MUTEX

#include <sys/time.h>
#include <ucontext.h>

#define _hoops_HRAPR	(1 << (SIGALRM - 1))


typedef struct {
	bool			_hoops_IRAPR;
	long				_hoops_CRAPR;
	struct _hoops_SRAPR	_hoops_GAAPR;		/* _hoops_RH "_hoops_RAAPR" _hoops_AAAPR _hoops_CHR _hoops_IH */
	struct _hoops_AHHPI	_hoops_PHHPI;	/* _hoops_RH _hoops_SGH _hoops_IIGR _hoops_IHPP _hoops_PPR */
	_hoops_HHHPI			_hoops_HAAPR;		/* _hoops_GCAR _hoops_RGAR. */
}	Time_Data;


GLOBAL_FUNCTION void HI_Init_Time (void) {
	Time_Data		*_hoops_IAAPR;
	struct timeval	_hoops_CAAPR;
	struct _hoops_SAAPR tz;

	ALLOC (_hoops_IAAPR, Time_Data);
	HOOPS_WORLD->_hoops_GPAPR = (void *)_hoops_IAAPR;

	gettimeofday (&_hoops_CAAPR, &tz);

	_hoops_IAAPR->_hoops_IRAPR = false;
	_hoops_IAAPR->_hoops_CRAPR = _hoops_CAAPR.tv_sec - 1;
}


GLOBAL_FUNCTION void HI_Free_Time (void) {
	Time_Data		*_hoops_IAAPR;

	_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	FREE (_hoops_IAAPR, Time_Data);
}


GLOBAL_FUNCTION _hoops_GSPGR HI_What_Time (void) {
	Time_Data		*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	struct timeval	_hoops_CAAPR;
	struct _hoops_SAAPR tz;

	gettimeofday (&_hoops_CAAPR, &tz);
	return ((_hoops_CAAPR.tv_sec - _hoops_IAAPR->_hoops_CRAPR)*(_hoops_GSPGR)_hoops_HSPGR +
			(_hoops_CAAPR.tv_usec * (_hoops_GSPGR)_hoops_HSPGR)/1000000);
}


local void _hoops_IPAPR (
	int			_hoops_IHHPI,
	_hoops_CHHPI   *_hoops_SHHPI,
	_hoops_GIHPI  *_hoops_HASAI) {

	UNREFERENCED (_hoops_IHHPI);
	UNREFERENCED (_hoops_SHHPI);
	UNREFERENCED (_hoops_HASAI);
}


GLOBAL_FUNCTION void HI_Sleep (
	_hoops_GSPGR					_hoops_SPAPR) {
	struct _hoops_SRAPR		_hoops_GHAPR;
	struct _hoops_AHHPI		_hoops_GIHI;
	Time_Data				*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	struct _hoops_SRAPR		_hoops_GAAPR;
	struct _hoops_AHHPI			_hoops_PHHPI;
	_hoops_HHHPI			_hoops_HAAPR;

	_hoops_RIHPI (&_hoops_GIHI._hoops_AIHPI);
	_hoops_PIHPI (&_hoops_GIHI._hoops_AIHPI, SIGALRM);
	_hoops_HIHPI (_hoops_IIHPI, &_hoops_GIHI._hoops_AIHPI, &_hoops_HAAPR);

	_hoops_GHAPR._hoops_HHAPR.tv_sec = _hoops_SPAPR/_hoops_HSPGR;
	_hoops_GHAPR._hoops_HHAPR.tv_usec = (((long)_hoops_SPAPR % (long)_hoops_HSPGR) * 1000000L) / _hoops_HSPGR;
	_hoops_GHAPR._hoops_IHAPR.tv_sec = 0;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = 0;

	_hoops_GIHI._hoops_CIHPI = _hoops_IPAPR;
	_hoops_GIHI._hoops_SIHPI = false;
	if (_hoops_AHHPI (SIGALRM, &_hoops_GIHI, &_hoops_PHHPI) == -1 ||
		_hoops_CHAPR (_hoops_SHAPR, &_hoops_GHAPR, &_hoops_GAAPR) == -1) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_SETTING_TIMER,
					"Internal error on trying to set a timer");
	}
	else {
		_hoops_HHHPI	_hoops_GCHPI;

		_hoops_IAAPR->_hoops_IRAPR = true;
		_hoops_GCHPI = _hoops_HAAPR;
		_hoops_RCHPI (&_hoops_GCHPI,SIGALRM);
		if (_hoops_ACHPI (&_hoops_GCHPI) == -1 && errno != _hoops_PCHPI) {
			HE_WARNING (HEC_SYSTEM, HES_ERROR_SUSPENDING_TIMER,
						"Internal error on trying to suspend");
		}
		_hoops_IAAPR->_hoops_IRAPR = false;
	}

	/* _hoops_GIAPR: _hoops_CGH _hoops_SRPA "_hoops_RHGS" _hoops_IH _hoops_RH _hoops_GHIR _hoops_SGS _hoops_SSCP _hoops_RIAPR... */
	if (_hoops_AHHPI (SIGALRM, &_hoops_PHHPI, null) == -1 ||
		_hoops_CHAPR (_hoops_SHAPR, &_hoops_GAAPR, null) == -1) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_RESTORING_TIMER,
					"Internal error on trying to restore a timer");
	}

	/*
	 * _hoops_RPP (!_hoops_HCHPI(&_hoops_ICHPI, _hoops_CCHPI))
	 */
	_hoops_HIHPI(_hoops_SCHPI, &_hoops_HAAPR, NULL);
}


local void _hoops_GSHPI (
	int	   _hoops_IHHPI,
	_hoops_CHHPI   _hoops_SHHPI,
	_hoops_GIHPI  *_hoops_RSHPI) {

	_hoops_PIAPR (true);
	UNREFERENCED (_hoops_IHHPI);
	UNREFERENCED (_hoops_SHHPI);
	UNREFERENCED (_hoops_RSHPI);
}


GLOBAL_FUNCTION bool HI_Enable_Timer_Interrupts(void) {
	struct _hoops_SRAPR		_hoops_GHAPR;
	struct _hoops_AHHPI		_hoops_GIHI;
	Time_Data				*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;

	_hoops_GHAPR._hoops_HHAPR.tv_sec = _hoops_HIAPR/_hoops_HSPGR;
	_hoops_GHAPR._hoops_HHAPR.tv_usec = (((long)_hoops_HIAPR % (long)_hoops_HSPGR) * 1000000L) / _hoops_HSPGR;
	_hoops_GHAPR._hoops_IHAPR.tv_sec = _hoops_GHAPR._hoops_HHAPR.tv_sec;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = _hoops_GHAPR._hoops_HHAPR.tv_usec;

	_hoops_GIHI._hoops_CIHPI = _hoops_GSHPI;
	_hoops_RIHPI (&_hoops_GIHI._hoops_AIHPI);
	_hoops_PIHPI (&_hoops_GIHI._hoops_AIHPI, SIGALRM);
	_hoops_GIHI._hoops_SIHPI = false;

	_hoops_HIHPI (_hoops_SCHPI, &_hoops_GIHI._hoops_AIHPI, &_hoops_IAAPR->_hoops_HAAPR);

	if (_hoops_AHHPI (SIGALRM, &_hoops_GIHI, &_hoops_IAAPR->_hoops_PHHPI) == -1 ||
		_hoops_CHAPR (_hoops_SHAPR, &_hoops_GHAPR, &_hoops_IAAPR->_hoops_GAAPR) == -1) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_SETTING_TIMER,
					"Internal error on trying to set a timer");
	}

	_hoops_HIHPI (_hoops_SCHPI, &_hoops_IAAPR->_hoops_HAAPR, NULL);

	return (true);
}


GLOBAL_FUNCTION void HI_Disable_Timer_Interrupts(void) {
	Time_Data				*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	struct _hoops_SRAPR		_hoops_GHAPR;
	_hoops_HHHPI				_hoops_ASHPI;

	/* _hoops_GIAPR: _hoops_CGH _hoops_SRPA "_hoops_RHGS" _hoops_IH _hoops_RH _hoops_GHIR _hoops_SGS _hoops_SSCP _hoops_RIAPR... */

	_hoops_GHAPR._hoops_HHAPR.tv_sec = 0;
	_hoops_GHAPR._hoops_HHAPR.tv_usec = 0;
	_hoops_GHAPR._hoops_IHAPR.tv_sec = 0;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = 0;

	/* _hoops_HHSP _hoops_ISCP _hoops_CIAPR */
	if (_hoops_CHAPR (_hoops_SHAPR, &_hoops_GHAPR, null) == -1) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_SUSPENDING_TIMER,
					"Internal error on trying to disable a timer");
	}

	/* _hoops_IPPRH _hoops_IH _hoops_GII _hoops_RCAPR _hoops_PSHPI _hoops_IS _hoops_CHRI */
	_hoops_HSHPI (2 * (((long)_hoops_HIAPR % (long)_hoops_HSPGR) * 1000000L) / (long)_hoops_HSPGR);
	do {
		_hoops_ISHPI (&_hoops_ASHPI);
	} while (_hoops_CSHPI (&_hoops_ASHPI, SIGALRM));

	/* _hoops_PHIH _hoops_RH _hoops_CIAPR _hoops_IS _hoops_SHH _hoops_PCPA _hoops_SCH _hoops_CSAP _hoops_ARPP */
	if (_hoops_AHHPI (SIGALRM, &_hoops_IAAPR->_hoops_PHHPI, null) == -1 ||
		(_hoops_IAAPR->_hoops_GAAPR._hoops_IHAPR.tv_sec != 0 ||
		 _hoops_IAAPR->_hoops_GAAPR._hoops_IHAPR.tv_usec != 0) &&
		_hoops_CHAPR(_hoops_SHAPR, &_hoops_IAAPR->_hoops_GAAPR, null) == -1) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_RESTORING_TIMER,
					"Internal error on trying to restore a timer");
	}

	if (_hoops_CSHPI (&_hoops_IAAPR->_hoops_HAAPR, SIGALRM)) {
		_hoops_HIHPI (_hoops_SCHPI, &_hoops_IAAPR->_hoops_HAAPR, NULL);
	}
}

#endif /* _hoops_HCAPR */


#endif /* _hoops_SSHPI */





