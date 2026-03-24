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
 * $Id: obf_tmp.txt 1.12 2010-10-06 19:16:07 jason Exp $
 */

#include "hoops.h"

#ifdef SOLARIS_SYSTEM


#include "driver.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "hversion.h"
#include "filedata.h"

#include <stdio.h>
#include <stdlib.h>


#include <sys/types.h>
#include <dirent.h>	  
#include <sys/stat.h>
#include <errno.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <ctype.h>



GLOBAL_FUNCTION void HI_Reset_Driver_Config_SS (void) {

	
	HC_Define_Driver_Config("opengl", "*", "*", "config=("
		"BAD_OVERLAY, UNDRAW_OVERLAY_FRONT_AND_BACK)");

	HC_Define_Driver_Config("opengl", "Elite-3D", "*", "config=("
		"BAD_OVERLAY, UNDRAW_OVERLAY_FRONT_AND_BACK, RESTORE_REGION_ZBUFFER_OFF)");
	
	HC_Define_Driver_Config("opengl", "Expert3D", "*", "config=("
		"BAD_OVERLAY, UNDRAW_OVERLAY_FRONT_AND_BACK)");

	/* _hoops_APPHS _hoops_PPPHS 1000 */
	HC_Define_Driver_Config("opengl", "ZFB, VIS", "*", "config=("
		"BAD_OVERLAY, UNDRAW_OVERLAY_FRONT_AND_BACK)");
	
	HC_Define_Driver_Config("opengl", "XVR", "*", "config=("
		"BAD_OVERLAY, UNDRAW_OVERLAY_FRONT_AND_BACK)");

	HC_Define_Driver_Config("opengl", "Elite-3D*", "*", "config=("
		"BAD_OVERLAY, UNDRAW_OVERLAY_FRONT_AND_BACK, BAD_SINGLE_BUFFERING)");

	if (HOOPS_WORLD->_hoops_PARPR.length != 0)
		HI_Read_Driver_Config_File();
}



GLOBAL_FUNCTION void HI_Start_System_Specific (_hoops_AIGPR *_hoops_RIGC) {
	/* _hoops_ISIRR _hoops_PCCP _hoops_RIARR _hoops_HARPR... */

	/* _hoops_RAIA _hoops_CRRGR&_hoops_AHGPH _hoops_AASA _hoops_HIS _hoops_SCH _hoops_GRS _hoops_SHH _hoops_HPPHS _hoops_CCA _hoops_IHRPR++ */
	atexit(HI_Call_Exit_Handlers);

#ifdef DYNAMIC_LOADER
			HOOPS_WORLD->_hoops_IARPR = HD_Sun_Load_Dynamic_Driver;
#endif
}


GLOBAL_FUNCTION void HI_Stop_System_Specific (void) {
	/* _hoops_CIH "_hoops_CARPR" _hoops_PPGS, _hoops_RPP _hoops_HAHH */
}

#ifdef DYNAMIC_LOADER

#include <dlfcn.h>


GLOBAL_FUNCTION Driver_Action HD_Sun_Load_Dynamic_Driver (
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

	_hoops_APRPR = (Driver_Action)(POINTER_SIZED_INT)dlsym(_hoops_RPRPR, _hoops_GPRPR);

	if (!_hoops_APRPR)
		dlclose(_hoops_RPRPR);

	return _hoops_APRPR;
}


GLOBAL_FUNCTION void HD_Sun_UnLoad_Dynamic_Driver (
	Driver_Action		_hoops_GHRPR) {

	/* _hoops_SR _hoops_CPSA _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_AA _hoops_PA _hoops_ARI, _hoops_GHAP _hoops_RHCA */
	UNREFERENCED(_hoops_GHRPR);
}

#endif /* _hoops_RHRPR */


GLOBAL_FUNCTION bool HI_Find_Application_Name (
	_hoops_HCRPR alter	*name) {
	FILE			*fp;
	char			_hoops_CSRPR[256];
	struct utsname	sys_name;

#ifdef _hoops_IPPHS
		sprintf(_hoops_CSRPR, "/bin/ps -p %d", getpid());
#else
		uname(&sys_name);
	if (sys_name.release[0] < '5') {
		sprintf(_hoops_CSRPR, "/bin/ps %d", getpid());
	}
	else {
		sprintf(_hoops_CSRPR, "/bin/ps -p %d", getpid());
	}
#endif
	if ((fp = popen(_hoops_CSRPR, "r")) == null) {
		return (false);
	}
	else if ((fgets(_hoops_CSRPR, sizeof(_hoops_CSRPR), fp) == null) ||
		(fgets(_hoops_CSRPR, sizeof(_hoops_CSRPR), fp) == null)) {
		pclose(fp);
		return (false);
	}
	else {
		char		*_hoops_HRCAR = _hoops_CSRPR,
									*_hoops_SSRPR = _hoops_CSRPR+_hoops_GGAPR(_hoops_CSRPR);
		pclose(fp);

		/* _hoops_SSS _hoops_RH _hoops_RGAPR _hoops_GGR _hoops_RH _hoops_GHIR */
		while (*_hoops_HRCAR != '\0') {
			if (*_hoops_HRCAR++ == ':') {
				break;
			}
		}

		/* _hoops_SSS _hoops_RH _hoops_SPS _hoops_RPGR */
		while (*_hoops_HRCAR != '\0') {
			if (*_hoops_HRCAR++ == ' ') {
				break;
			}
		}

		if (_hoops_HRCAR == _hoops_SSRPR) {
			return (false);
		}

		/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GGHP _hoops_HCR _hoops_AGAPR _hoops_HPS _hoops_HPGR _hoops_RH _hoops_HSPP */
		while (!isalnum(*_hoops_HRCAR) && (*_hoops_HRCAR != '_') && (*_hoops_HRCAR != '-')) {
			if (++_hoops_HRCAR == _hoops_SSRPR) {
				return (false);
			}
		}

		/* _hoops_SSS _hoops_CGHI _hoops_AGAPR _hoops_GAS; _hoops_GCIS _hoops_PGAPR _hoops_HSPP _hoops_IH /'_hoops_GRI */
		for (_hoops_SSRPR = _hoops_HRCAR;; _hoops_SSRPR++) {
			if (*_hoops_SSRPR == '/') {
				_hoops_HRCAR = _hoops_SSRPR + 1;
			}
			else if (!isalnum(*_hoops_SSRPR) && (*_hoops_SSRPR != '_') && (*_hoops_SSRPR != '-')) {
				break;
			}
		}

		if (_hoops_HRCAR == _hoops_SSRPR) {
			return (false);
		}

		/* _hoops_GHHR _hoops_RH _hoops_GSGR */
		*_hoops_SSRPR = '\0';

		/* _hoops_ASRC _hoops_SCH */
		HI_Copy_Chars_To_Name(_hoops_HRCAR, name);

		return (true);
	}
}




#define _hoops_AIIHH 1024
#define _hoops_PIIHH 1024


typedef struct _hoops_HIIHH {
	int			_hoops_IIIHH;
	int			_hoops_CIIHH;
	DIR			*_hoops_CCSAR;
	_hoops_HCRPR		name;
	_hoops_HCRPR		filter;
} _hoops_SIIHH;


#ifdef DISABLE_MUTEX

#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <siginfo.h>
#include <ucontext.h>
#include <errno.h>

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


local void _hoops_CPPHS (
	int	   _hoops_IHHPI,
	_hoops_CHHPI   _hoops_SHHPI,
	_hoops_GIHPI  *_hoops_RSHPI) {

	_hoops_PIAPR (true);
}


GLOBAL_FUNCTION bool HI_Enable_Timer_Interrupts(void) {
	struct _hoops_SRAPR		_hoops_GHAPR;
	struct _hoops_AHHPI		_hoops_GIHI;
	Time_Data				*_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;

	_hoops_GHAPR._hoops_HHAPR.tv_sec = _hoops_HIAPR/_hoops_HSPGR;
	_hoops_GHAPR._hoops_HHAPR.tv_usec = (((long)_hoops_HIAPR % (long)_hoops_HSPGR) * 1000000L) / _hoops_HSPGR;
	_hoops_GHAPR._hoops_IHAPR.tv_sec = _hoops_GHAPR._hoops_HHAPR.tv_sec;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = _hoops_GHAPR._hoops_HHAPR.tv_usec;

	_hoops_GIHI._hoops_CIHPI = _hoops_CPPHS;
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

	/* _hoops_GIAPR: _hoops_CGH _hoops_SRPA "_hoops_RHGS" _hoops_IH _hoops_RH _hoops_GHIR _hoops_SGS _hoops_SSCP _hoops_RIAPR... */

	_hoops_GHAPR._hoops_HHAPR.tv_sec = 0;
	_hoops_GHAPR._hoops_HHAPR.tv_usec = 0;
	_hoops_GHAPR._hoops_IHAPR.tv_sec = 0;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = 0;

	/*
	 * _hoops_IIAPR, _hoops_RRS _hoops_ISCP _hoops_CIAPR, _hoops_PSCR _hoops_PHIH _hoops_RH _hoops_RHGS _hoops_HARPR,
	 * _hoops_PSCR _hoops_SIAPR _hoops_RH _hoops_RHGS _hoops_CIAPR (_hoops_RPP _hoops_GII). _hoops_CAAAR'_hoops_SAAAR _hoops_RIS _hoops_ISCP
	 * _hoops_GCAPR - _hoops_RPP _hoops_RH _hoops_GCAPR _hoops_RRGPR _hoops_RCAPR, _hoops_ACAPR _hoops_ISCP
	 * _hoops_CIAPR _hoops_PCAPR'_hoops_SAAAR _hoops_IRHH _hoops_SCH _hoops_PHHR _hoops_SGGR.
	 */

	if (_hoops_CHAPR (_hoops_SHAPR, &_hoops_GHAPR, null) == -1 ||
		_hoops_AHHPI (SIGALRM, &_hoops_IAAPR->_hoops_PHHPI, null) == -1 ||
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

#endif /* _hoops_SPPHS */




