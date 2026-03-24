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
 * $Id: obf_tmp.txt 1.9 2010-10-06 19:16:07 jason Exp $
 */

#include "hoops.h"


#ifdef HPUX_SYSTEM

#include "driver.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "hversion.h"


#include <stdio.h>
#include <stdlib.h>


GLOBAL_FUNCTION void HI_Reset_Driver_Config_SS (void) {

	
	HC_Define_Driver_Config("opengl", "*", "*", "config=(BAD_SINGLE_BUFFERING, UNDRAW_OVERLAY_FRONT_AND_BACK)");

	if (HOOPS_WORLD->_hoops_PARPR.length != 0)
		HI_Read_Driver_Config_File();
}


/*
 * _hoops_HGI _hoops_PCPH _hoops_HRGR _hoops_PIGS _hoops_CGPR _hoops_AGAH _hoops_HRGR _hoops_AIS. _hoops_IGPIP _hoops_AAAA _hoops_RH
 * _hoops_PHIAH _hoops_IRS _hoops_CGGC _hoops_IS _hoops_AA _hoops_PA, _hoops_IAS._hoops_ISHI. _hoops_HGSR _hoops_RIARR _hoops_IASAH,
 * _hoops_SGS _hoops_HRGR _hoops_HAHH _hoops_IS _hoops_ARAS _hoops_AGAH _hoops_GPP _hoops_SGS _hoops_PHIAH. _hoops_PGPR _hoops_CGSI
 * _hoops_IPPAR _hoops_IS _hoops_RH _hoops_PHIAH, _hoops_HAS._hoops_IAS. _hoops_HAR _hoops_SPSIR, _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_ARI.
 */
GLOBAL_FUNCTION void HI_Start_System_Specific (_hoops_AIGPR *_hoops_RIGC) {
	/* _hoops_ISIRR _hoops_PCCP _hoops_RIARR _hoops_HARPR... */
	atexit (HI_Call_Exit_Handlers);

	/* _hoops_HRSAI "_hoops_CARPR" _hoops_PPGS, _hoops_RPP _hoops_HAHH */

#ifdef DYNAMIC_LOADER
	HOOPS_WORLD->_hoops_IARPR = HD_HPUX_Load_Dynamic_Driver;
#endif
}


/*
 * _hoops_HGI _hoops_PCPH _hoops_HRGR _hoops_PIGS _hoops_CGPR _hoops_AGAH _hoops_HRGR _hoops_AHCA _hoops_IS _hoops_SHH _hoops_CCGAI
 * _hoops_HIS _hoops_SGS _hoops_PA _hoops_CPHR _hoops_GGR _hoops_RH _hoops_HSPP _hoops_PCPH _hoops_PAH _hoops_SHH _hoops_ISSPR-_hoops_CPHR.
 */
GLOBAL_FUNCTION void HI_Stop_System_Specific (void) {
	/* _hoops_GSGHR "_hoops_CARPR" _hoops_PPGS, _hoops_RPP _hoops_HAHH */
}


#ifdef DYNAMIC_LOADER

#include <dl.h>

GLOBAL_FUNCTION Driver_Action HD_HPUX_Load_Dynamic_Driver (
	char const *_hoops_HSS) {
		
	char _hoops_SARPR[1024];
	char _hoops_GPRPR[1024];
	shl_t _hoops_RPRPR;
	char version[20];

	Driver_Action _hoops_APRPR;

	int i=0;

	char * _hoops_PPRPR[][2] = { 
		{ "opengl",		"HD_OpenGL_Driver"},
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
	_hoops_HPRPR ("hdi.sl", _hoops_SARPR);

/*
	_hoops_IPRPR("%_hoops_GRI %_hoops_GRI\_hoops_ACHP",_hoops_CPRPR, _hoops_SPRPR);
*/

	_hoops_RPRPR = shl_load(_hoops_SARPR,
				BIND_NONFATAL|BIND_IMMEDIATE|DYNAMIC_PATH|BIND_VERBOSE, 0L);

/*
_hoops_IPRPR("%_hoops_GHGP\_hoops_ACHP",_hoops_IRSAI);
*/
	if (!_hoops_RPRPR) 
		return (Driver_Action)nullroutine;

	if (shl_findsym(&_hoops_RPRPR, _hoops_GPRPR, TYPE_PROCEDURE, &_hoops_APRPR)) {
/*
_hoops_IPRPR("%_hoops_CCAHR\_hoops_ACHP", (_hoops_SRPC*)_hoops_PCPH);
*/

		shl_unload(_hoops_RPRPR);
		return (Driver_Action)nullroutine;
	}

	return _hoops_APRPR;
}


GLOBAL_FUNCTION void HD_HPUX_UnLoad_Dynamic_Driver (
	Driver_Action		_hoops_GHRPR) {

	/* _hoops_SR _hoops_CPSA _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_AA _hoops_PA _hoops_ARI, _hoops_GHAP _hoops_RHCA */
	UNREFERENCED(_hoops_GHRPR);
}

#endif /* _hoops_RHRPR */


/*
 * _hoops_AGAH _hoops_RAIA _hoops_RH _hoops_CCRPR _hoops_RSIRR _hoops_GAR _hoops_RH _hoops_RPPS _hoops_CRSAI
 * _hoops_RPP _hoops_RH _hoops_CRSAI _hoops_RHPP _hoops_HCSP _hoops_SSCP _hoops_HAR _hoops_RPII _hoops_ARP.
 */
GLOBAL_FUNCTION bool HI_Find_Application_Name (
	_hoops_HCRPR alter	*name) {
	char alter		*_hoops_CSHPP;
	char alter		*_hoops_AHSCA;
	extern		int				__argc_value;	/* _hoops_CACH _hoops_SRSAI._hoops_GCSR */
	extern		char alter		**__argv_value;

	/*
	 * _hoops_RPSRH _hoops_RH _hoops_CCRPR'_hoops_GRI _hoops_RSIRR (_hoops_SCRPR, _hoops_RH _hoops_RGHR _hoops_RSIRR _hoops_IIGR _hoops_RH
	 * _hoops_GSRPR _hoops_CSCR), _hoops_CCPH _hoops_PSAP _hoops_RH _hoops_RSRPR _hoops_AHI, _hoops_PPR _hoops_SGH
	 * _hoops_ASRPR() _hoops_PAR _hoops_PSRPR() _hoops_IS _hoops_HSRPR _hoops_RH
	 * _hoops_GHPP _hoops_CRGR '_hoops_RSIRR'.	_hoops_CGP _hoops_PPGAR, _hoops_ASRC _hoops_IHPR.
	 */

	if (__argc_value < 1) {
		return (false);
	}

	_hoops_AHSCA = _hoops_CSHPP = __argv_value[0];
	while (*_hoops_CSHPP != '\0') {
		if (*_hoops_CSHPP++ == '/') {
			_hoops_AHSCA = _hoops_CSHPP;
		}
	}
	if (*_hoops_AHSCA == '\0') {
		return (false);
	}

	HI_Copy_Chars_To_Name (_hoops_AHSCA, name);
	return (true);
}


// _hoops_HGAPR _hoops_IGAPR _hoops_CGAPR _hoops_PAAAR _hoops_SGAPR _hoops_GRAPR _hoops_RRAPR
#ifdef DISABLE_MUTEX

#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define _hoops_HRAPR	 (1 << (SIGALRM - 1))

typedef struct {
	bool			_hoops_GASAI;
	bool			_hoops_IRAPR;
	unsigned long		_hoops_CRAPR;
	struct _hoops_SRAPR	_hoops_GAAPR;		/* _hoops_RH "_hoops_RAAPR" _hoops_AAAPR _hoops_CHR _hoops_IH */
	struct sigvec		_hoops_PAAPR;		/* _hoops_RH _hoops_SGH _hoops_IIGR _hoops_IHPP _hoops_PPR */
	int					_hoops_HAAPR;		/* _hoops_GCAR _hoops_RGAR. */
} Time_Data;


/*
 * _hoops_AGAH _hoops_HCPH _hoops_RGR _hoops_HPGR _hoops_AGAH _hoops_GASCA _hoops_GHIR _hoops_HIS _hoops_PPGS _hoops_PAH _hoops_SHH
 * _hoops_PSPP _hoops_IH _hoops_ASRAH _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_GHIR.
 */
GLOBAL_FUNCTION void HI_Init_Time (void) {
	Time_Data alter *_hoops_IAAPR;
	struct timeval	_hoops_CAAPR;
	struct _hoops_SAAPR tz;

	ALLOC (_hoops_IAAPR, Time_Data);
	_hoops_IAAPR->_hoops_GASAI = false;
	_hoops_IAAPR->_hoops_IRAPR = false;
	_hoops_IAAPR->_hoops_CRAPR = (unsigned long)0;
	_hoops_IAAPR->_hoops_GAAPR._hoops_IHAPR.tv_sec = (unsigned long)0;
	_hoops_IAAPR->_hoops_GAAPR._hoops_IHAPR.tv_usec = 0L;
	_hoops_IAAPR->_hoops_GAAPR._hoops_HHAPR.tv_sec = (unsigned long)0;
	_hoops_IAAPR->_hoops_GAAPR._hoops_HHAPR.tv_usec = 0L;
	_hoops_IAAPR->_hoops_PAAPR._hoops_RHAPR = null;
	_hoops_IAAPR->_hoops_PAAPR._hoops_AHAPR = 0;
	_hoops_IAAPR->_hoops_PAAPR._hoops_PHAPR = 0;
	_hoops_IAAPR->_hoops_HAAPR = 0;
	HOOPS_WORLD->_hoops_GPAPR = (void *)_hoops_IAAPR;

	gettimeofday (&_hoops_CAAPR, &tz);

	/* _hoops_IRHH _hoops_SCH _hoops_PCGRH _hoops_IH _hoops_SCGR _hoops_PPR _hoops_HSPP _hoops_IS _hoops_SHH _hoops_RH _hoops_PSHR */
	_hoops_IAAPR->_hoops_CRAPR = _hoops_CAAPR.tv_sec - (unsigned long)1;
}


/*
 * _hoops_AGAH _hoops_HCPH _hoops_RGR _hoops_HPGR _hoops_AGAH _hoops_RCPHR _hoops_GHIR _hoops_HIS _hoops_RH _hoops_PPGS,
 * _hoops_SGS _hoops_CSAP _hoops_PSPP _hoops_IS _hoops_AA _hoops_GHIR _hoops_CGRSR, _hoops_PAH _hoops_SHH _hoops_HGGPR.
 */
GLOBAL_FUNCTION void HI_Free_Time (void) {
	Time_Data		*_hoops_IAAPR;

	_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	FREE (_hoops_IAAPR, Time_Data);
	HOOPS_WORLD->_hoops_GPAPR = null;
}


/*
 * _hoops_HGI _hoops_PCPH _hoops_HRGR _hoops_PIGS _hoops_HPP _hoops_AGAH _hoops_CGPR _hoops_RASAI _hoops_SSHGR, _hoops_IAS._hoops_ISHI.
 * _hoops_CHSAP _hoops_SSHGR, _hoops_ACAGR _hoops_SSHGR, _hoops_GRH _hoops_SSHGR, _hoops_PAR
 * _hoops_CGGGA _hoops_PPCIA.
 */
GLOBAL_FUNCTION _hoops_GSPGR HI_What_Time (void) {
	Time_Data alter *_hoops_IAAPR = (Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	struct timeval	_hoops_CAAPR;
	struct _hoops_SAAPR tz;

	gettimeofday (&_hoops_CAAPR, &tz);
	return (_hoops_GSPGR)((_hoops_CAAPR.tv_sec - _hoops_IAAPR->_hoops_CRAPR) * (_hoops_GSPGR)_hoops_HSPGR +
					 (_hoops_CAAPR.tv_usec * (_hoops_GSPGR)_hoops_HSPGR) / 1000000);
}


/*
 * _hoops_SHIR, _hoops_AA _hoops_ISAP, _hoops_GCAPR _hoops_HARPR
 */
#if 0
/*_hoops_RGR _hoops_SPASR _hoops_RH _hoops_AASAI _hoops_HSHIA _hoops_HIH _hoops_HAR _hoops_RH _hoops_IRAGP*/
local void _hoops_IPAPR (
	int						_hoops_CPAPR,
	int						code,
	struct _hoops_PASAI alter *_hoops_HASAI) {
}
#else
local void _hoops_IPAPR (int _hoops_CPAPR) {
}
#endif

/*
 * _hoops_IASAI _hoops_HRGR _hoops_PIGS _hoops_HPP _hoops_AGAH _hoops_CGPR _hoops_AGAH _hoops_HRGR _hoops_GGR _hoops_PCCP
 * _hoops_CASAI _hoops_HAPR _hoops_SASAI _hoops_SSCP _hoops_PSP _hoops_SSHGR _hoops_IS _hoops_HPPP.
 */
GLOBAL_FUNCTION void HI_Sleep (
	_hoops_GSPGR					_hoops_SPAPR) {
	struct _hoops_SRAPR		_hoops_GHAPR;
	struct sigvec			_hoops_GIHI;
	Time_Data				*_hoops_IAAPR =
											(Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	struct _hoops_SRAPR		_hoops_GAAPR;
	struct sigvec			_hoops_PAAPR;
	int						_hoops_HAAPR;

	_hoops_HAAPR = sigblock ((long)_hoops_HRAPR);

	_hoops_GIHI._hoops_RHAPR = _hoops_IPAPR;
	_hoops_GIHI._hoops_AHAPR = _hoops_HRAPR;
	_hoops_GIHI._hoops_PHAPR = 0;

	_hoops_GHAPR._hoops_HHAPR.tv_sec = (unsigned long)(_hoops_SPAPR / _hoops_HSPGR);
	_hoops_GHAPR._hoops_HHAPR.tv_usec = (long)(((long)_hoops_SPAPR % (long)_hoops_HSPGR) * 1000000L) / _hoops_HSPGR;
	_hoops_GHAPR._hoops_IHAPR.tv_sec = (unsigned long)0;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = 0L;

	_hoops_IAAPR->_hoops_GASAI = true;
	if ((_hoops_GPSAI (SIGALRM, &_hoops_GIHI, &_hoops_PAAPR) == -1) ||
		(_hoops_CHAPR (_hoops_SHAPR, &_hoops_GHAPR, &_hoops_GAAPR) == -1)) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_SETTING_TIMER,
					"Internal error on trying to set a timer");
		_hoops_IAAPR->_hoops_IRAPR = false;
	}
	else {
		_hoops_IAAPR->_hoops_IRAPR = true;
		if (_hoops_IAAPR->_hoops_GASAI)
			sigpause (_hoops_HAAPR & ~_hoops_HRAPR);
		_hoops_IAAPR->_hoops_IRAPR = false;
	}

	/* _hoops_GIAPR: _hoops_CGH _hoops_SRPA "_hoops_RHGS" _hoops_IH _hoops_RH _hoops_GHIR _hoops_SGS _hoops_SSCP _hoops_RIAPR... */
	if ((_hoops_CHAPR (_hoops_SHAPR, &_hoops_GAAPR, null) == -1) ||
		(_hoops_GPSAI (SIGALRM, &_hoops_PAAPR, null) == -1)) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_RESTORING_TIMER,
					"Internal error on trying to restore a timer");
	}
	_hoops_IAAPR->_hoops_GASAI = false;

	if (!BIT (_hoops_HAAPR, _hoops_HRAPR)) {
		(void)sigsetmask (_hoops_HAAPR);
	}
}


/*
 * _hoops_PAAS _hoops_RH _hoops_CIAPR _hoops_RPSAI, _hoops_IRS _hoops_IGRH _hoops_HRGR _hoops_ARP. _hoops_HGI _hoops_HRGR _hoops_RH _hoops_IGRH _hoops_SGS
 * _hoops_RH _hoops_AGAH _hoops_ASCA _hoops_RRGR _hoops_APSAI _hoops_HCGC.
 */
#if 0
/*_hoops_RGR _hoops_SPASR _hoops_RH _hoops_AASAI _hoops_HSHIA _hoops_HIH _hoops_HAR _hoops_RH _hoops_IRAGP*/
local void _hoops_PPSAI (
	int						_hoops_CPAPR,
	int						code,
	struct _hoops_PASAI alter *_hoops_HASAI) {
	_hoops_PIAPR (true);
}
#else
local void _hoops_PPSAI (
	int				_hoops_CPAPR) {
	_hoops_PIAPR (true);
}
#endif

/*
 * _hoops_AGAH _hoops_SSCP "_hoops_PAAP _hoops_HPSAI" _hoops_PPP _hoops_HPP _hoops_SHIR _hoops_PGAP _hoops_AGSR
 * _hoops_SGS _hoops_SSHSR _hoops_PAH _hoops_RCCS _hoops_RH _hoops_ASCA _hoops_RCAS. _hoops_HGI _hoops_HRGR _hoops_IIAC
 * _hoops_SSRR _hoops_PGGA _hoops_HPGR _hoops_AGRR _hoops_RSSA _hoops_GGR _hoops_RH _hoops_AGAH _hoops_ASCA _hoops_RCAS,
 * _hoops_AGAH _hoops_HCGC _hoops_IS _hoops_CACH _hoops_RPP _hoops_IRS _hoops_CIAPR _hoops_SSCP _hoops_IPSAI, _hoops_PPR _hoops_RPP _hoops_HIS,
 * _hoops_CPSAI _hoops_IS _hoops_CACH _hoops_RPP _hoops_GII _hoops_SSHGR _hoops_AAPR _hoops_SPSAI.
 */
GLOBAL_FUNCTION bool HI_Enable_Timer_Interrupts (void) {
	struct _hoops_SRAPR		_hoops_GHAPR;
	struct sigvec			_hoops_GIHI;
	Time_Data alter			*_hoops_IAAPR =
					(Time_Data *)HOOPS_WORLD->_hoops_GPAPR;

	_hoops_GHAPR._hoops_HHAPR.tv_sec = (unsigned long)(_hoops_HIAPR / _hoops_HSPGR);
	_hoops_GHAPR._hoops_HHAPR.tv_usec =
		(long)((((long)_hoops_HIAPR % (long)_hoops_HSPGR) * 1000000L) / _hoops_HSPGR);
	_hoops_GHAPR._hoops_IHAPR.tv_sec = _hoops_GHAPR._hoops_HHAPR.tv_sec;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = _hoops_GHAPR._hoops_HHAPR.tv_usec;

	_hoops_GIHI._hoops_RHAPR = _hoops_PPSAI;
	_hoops_GIHI._hoops_AHAPR = _hoops_HRAPR;
	_hoops_GIHI._hoops_PHAPR = 0;

	_hoops_IAAPR->_hoops_HAAPR = sigblock ((long)_hoops_HRAPR);

	if ((_hoops_GPSAI (SIGALRM, &_hoops_GIHI, &_hoops_IAAPR->_hoops_PAAPR) == -1) ||
		(_hoops_CHAPR (_hoops_SHAPR, &_hoops_GHAPR, &_hoops_IAAPR->_hoops_GAAPR) == -1)) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_SETTING_TIMER,
					"Internal error on trying to set a timer");
	}

	(void)sigsetmask (_hoops_IAAPR->_hoops_HAAPR & ~_hoops_HRAPR);

	return (true);
}


/*
 * _hoops_HRHI _hoops_HPSAI _hoops_CHR _hoops_GPP _hoops_HPP _hoops_SHIR; _hoops_HGRRA, _hoops_SSIA _hoops_PAH _hoops_SHH _hoops_GRGR
 * _hoops_HPP _hoops_RH "_hoops_PSP _hoops_PAAP _hoops_HPSAI" _hoops_RHPP _hoops_HCSP. _hoops_GPGP _hoops_PIHRA, _hoops_AGAH
 * _hoops_APCS _hoops_GHSAI _hoops_PAAP _hoops_HPSAI _hoops_CGPR _hoops_HHCI _hoops_IHCI _hoops_CHR
 * _hoops_GGR _hoops_SGH.
 */
GLOBAL_FUNCTION void HI_Disable_Timer_Interrupts (void) {
	Time_Data alter			*_hoops_IAAPR =
											(Time_Data *)HOOPS_WORLD->_hoops_GPAPR;
	struct _hoops_SRAPR		_hoops_GHAPR;

	/* _hoops_GIAPR: _hoops_CGH _hoops_SRPA "_hoops_RHGS" _hoops_IH _hoops_RH _hoops_GHIR _hoops_SGS _hoops_SSCP _hoops_RIAPR... */
	_hoops_GHAPR._hoops_HHAPR.tv_sec = (unsigned long)0;
	_hoops_GHAPR._hoops_HHAPR.tv_usec = 0L;
	_hoops_GHAPR._hoops_IHAPR.tv_sec = (unsigned long)0;
	_hoops_GHAPR._hoops_IHAPR.tv_usec = 0L;

	/*
	 * _hoops_IIAPR, _hoops_RRS _hoops_ISCP _hoops_CIAPR, _hoops_PSCR _hoops_PHIH _hoops_RH _hoops_RHGS _hoops_HARPR,
	 * _hoops_PSCR _hoops_SIAPR _hoops_RH _hoops_RHGS _hoops_CIAPR (_hoops_RPP _hoops_GII).	 _hoops_CAAAR'_hoops_SAAAR _hoops_RIS _hoops_ISCP
	 * _hoops_GCAPR - _hoops_RPP _hoops_RH _hoops_GCAPR _hoops_RRGPR _hoops_RCAPR, _hoops_ACAPR _hoops_ISCP
	 * _hoops_CIAPR _hoops_PCAPR'_hoops_SAAAR _hoops_IRHH _hoops_SCH _hoops_PHHR _hoops_SGGR.
	 */
	if ((_hoops_CHAPR (_hoops_SHAPR, &_hoops_GHAPR, null) == -1) ||
		(_hoops_GPSAI (SIGALRM, &_hoops_IAAPR->_hoops_PAAPR, null) == -1) ||
		(((_hoops_IAAPR->_hoops_GAAPR._hoops_IHAPR.tv_sec != (unsigned long)0) ||
		  (_hoops_IAAPR->_hoops_GAAPR._hoops_IHAPR.tv_usec != 0L)) &&
		  (_hoops_CHAPR (_hoops_SHAPR, &_hoops_IAAPR->_hoops_GAAPR, null) == -1))) {
		HE_WARNING (HEC_SYSTEM, HES_ERROR_RESTORING_TIMER,
					"Internal error on trying to restore a timer");
	}

	if (BIT (_hoops_IAAPR->_hoops_HAAPR, _hoops_HRAPR)) {
		sigblock ((long)_hoops_HRAPR);
	}
}

#endif /* _hoops_HCAPR */

#endif /* _hoops_RHSAI */





