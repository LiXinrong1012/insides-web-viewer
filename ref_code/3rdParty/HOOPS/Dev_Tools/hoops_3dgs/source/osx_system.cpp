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
 * $Id: obf_tmp.txt 1.16 2010-10-06 19:16:07 jason Exp $
 */

#include "hoops.h"


#ifdef OSX_SYSTEM

#define Point _hoops_SARRI
#define Style OSX_Style

#undef local
#include <CoreFoundation/CoreFoundation.h>
#define local static

#undef Point 
#undef Style

#include "driver.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "hversion.h"


#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>


GLOBAL_FUNCTION void HI_Reset_Driver_Config_SS (void) {

	HC_Define_Driver_Config("opengl2", "*", "*", "general tristrip minimum=48");

	HC_Define_Driver_Config("opengl", "*", "*", "general tristrip minimum=48");

	HC_Define_Driver_Config("opengl", "Generic", "*", "software, config=("
		"BAD_MULTILIGHT, BAD_SCISSORING), general tristrip minimum=48");

	HC_Define_Driver_Config("opengl", "*Intel*", "*", "config=("
		"BAD_VERTEX_BUFFER_OBJECT, BAD_FRAGMENT_PROGRAM, XBIT_BAD_SEPARATE_SPECULAR),"
		"general tristrip minimum=6");

	if (HOOPS_WORLD->_hoops_PARPR.length != 0)
		HI_Read_Driver_Config_File();
}



GLOBAL_FUNCTION void HI_Start_System_Specific (_hoops_AIGPR *_hoops_RIGC) {

	atexit (HI_Call_Exit_Handlers);

#ifdef DYNAMIC_LOADER
		HOOPS_WORLD->_hoops_IARPR = HD_OSX_Load_Dynamic_Driver;
#endif
}


GLOBAL_FUNCTION void HI_Stop_System_Specific (void) {
	/* _hoops_CIH "_hoops_CARPR" _hoops_PPGS, _hoops_RPP _hoops_HAHH */
}



local CFStringRef CopyPreferenceForApp_StringRef(CFStringRef key, CFStringRef _hoops_HGGCC)
{
		CFPropertyListRef item;

		item = CFPreferencesCopyAppValue(key, kCFPreferencesCurrentApplication);
		if (item && (CFStringGetTypeID() == CFGetTypeID(item)))
		{
				return (CFStringRef) item;
		}

		item = CFPreferencesCopyAppValue(key, CFSTR("com.techsoft3d.HOOPS"));
		if (item && (CFStringGetTypeID() == CFGetTypeID(item)))
		{
				return (CFStringRef) item;
		}

		if (_hoops_HGGCC)
				CFRetain(_hoops_HGGCC);

		return _hoops_HGGCC;
}


/*
	_hoops_IS _hoops_HGCR _hoops_IRS _hoops_IGGCC _hoops_AIS, _hoops_GGCR _hoops_RH _hoops_HSPR _hoops_IS _hoops_CGGCC _hoops_PPR _hoops_ARAS _hoops_ARR
		_hoops_AIRRI _hoops_SGGCC = _hoops_GRGCC("_hoops_RRGCC");
		_hoops_AIRRI _hoops_ARGCC = _hoops_GRGCC("_hoops_PRGCC");
		_hoops_HRGCC(_hoops_SGGCC, _hoops_ARGCC,_hoops_IRGCC);
		_hoops_HRGCC(_hoops_SGGCC, _hoops_ARGCC,_hoops_GRGCC("_hoops_HIHRH._hoops_CRGCC._hoops_AGAH"));
		_hoops_SRGCC(_hoops_IRGCC);
		_hoops_SRGCC(_hoops_GRGCC("_hoops_HIHRH._hoops_CRGCC._hoops_AGAH"));

*/

/*
 * _hoops_AGAH _hoops_RAIA _hoops_RGR _hoops_AASA _hoops_IS _hoops_CGHPC _hoops_HRP _hoops_IH _hoops_GII
 * _hoops_AGAH _hoops_RHI _hoops_CCPAR, _hoops_IAS._hoops_ISHI. _hoops_RRGCC.
 * _hoops_IPCP _hoops_HIGR _hoops_IIGR _hoops_HHPA _hoops_RHI _hoops_CCPAR _hoops_PHPP _hoops_GGR
 * _hoops_RH "_hoops_GAGCC-_hoops_GHIR _hoops_RAGCC _hoops_RACCI" _hoops_AAGCC _hoops_IIGR _hoops_RH
 * _hoops_AGAH _hoops_PAGCC _hoops_SSAAI.
 */
GLOBAL_FUNCTION bool HI_Show_Environment (
	char const		*which,
	_hoops_HCRPR alter	*result) 
{
	char *ptr;
	bool status = true;

	if ((ptr = getenv (which)) == null) {
		CFStringRef key, ref;
		key = CFStringCreateWithBytes(null, (const UInt8 *)which, strlen(which),	kCFStringEncodingASCII, false);
		if (key) {
			ref = CopyPreferenceForApp_StringRef(key, null);
			CFRelease(key);
			if (ref) {
					char buf[4096];
						
					/* _hoops_IIRAR _hoops_CCRRI, _hoops_HIH _hoops_SCRRI _hoops_IH _hoops_SIRRI */
					status = 
						(CFStringGetCString(ref, buf, 4096, kCFStringEncodingASCII) ||
						(CFStringGetCString(ref, buf, 4096, kCFStringEncodingUTF8)));
					if (status) {
						HI_Copy_Chars_To_Name (buf, result);
					}	
					CFRelease(ref);
					return status;
			}
			else
				return false;
		}
		else
			return false;
	}
	else {
		HI_Copy_Chars_To_Name (ptr, result);
		return true;
	}
}


#ifdef DYNAMIC_LOADER

#include <dlfcn.h>


GLOBAL_FUNCTION Driver_Action HD_OSX_Load_Dynamic_Driver (
	char const *_hoops_HSS) {
		
	char _hoops_SARPR[1024];
	char _hoops_GPRPR[1024];
	void * _hoops_RPRPR;
	char version[20];

	Driver_Action _hoops_APRPR;

	int i=0;

	char const * _hoops_PPRPR[][2] = { 
		{ "pdf",        "HD_PDF_Driver"},
		{ "qt",        	"HD_QT_Driver"},
		{ "whip2d",		"HD_Whip2D_Driver"},
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
	_hoops_HPRPR ("hdi.dylib", _hoops_SARPR);

	_hoops_RPRPR = dlopen(_hoops_SARPR, RTLD_NOW);

	if (_hoops_RPRPR == 0) {
		CFBundleRef _hoops_HAGCC = CFBundleGetMainBundle();
		CFRetain(_hoops_HAGCC);
	
		CFURLRef _hoops_IAGCC = CFBundleCopyExecutableURL(_hoops_HAGCC);
		CFRelease(_hoops_HAGCC);
	
		CFStringRef _hoops_CAGCC = CFURLCopyFileSystemPath(_hoops_IAGCC, kCFURLPOSIXPathStyle);
	
		char _hoops_SAGCC[1024];
		CFStringGetCString(_hoops_CAGCC, _hoops_SAGCC, 1024, kCFStringEncodingUTF8);
	
		CFRelease(_hoops_CAGCC);
	
		CFRelease(_hoops_IAGCC);
	
		char *_hoops_GPGCC = strrchr(_hoops_SAGCC, '/');
		*(++_hoops_GPGCC) = 0;
	
		_hoops_AAHR (_hoops_SAGCC, _hoops_SARPR);
		_hoops_HPRPR ("lib", _hoops_SARPR);
		_hoops_HPRPR (_hoops_HSS, _hoops_SARPR);
		_hoops_HPRPR (version, _hoops_SARPR);
		_hoops_HPRPR ("hdi.dylib", _hoops_SARPR);

		_hoops_RPRPR = dlopen(_hoops_SARPR, RTLD_NOW);

		if (_hoops_RPRPR == 0) {
#ifdef HOOPS_DEBUG_BUILD
			fprintf(stderr, "%s\n", dlerror());
#endif
			return (Driver_Action)nullroutine;
		}
	}

	_hoops_APRPR = (Driver_Action)dlsym(_hoops_RPRPR, _hoops_GPRPR);

	if (!_hoops_APRPR) {
#ifdef HOOPS_DEBUG_BUILD
		fprintf(stderr, "Couldn't find %s in %s\n", _hoops_GPRPR, _hoops_SARPR);
#endif
		dlclose(_hoops_RPRPR);
	}

	return _hoops_APRPR;
}


GLOBAL_FUNCTION void HD_OSX_UnLoad_Dynamic_Driver (
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
	int			__argc_value;	/* _hoops_CACH _hoops_SRSAI._hoops_GCSR */
	char alter	**__argv_value;

	/*
	 * _hoops_RPSRH _hoops_RH _hoops_CCRPR'_hoops_GRI _hoops_RSIRR (_hoops_SCRPR, _hoops_RH _hoops_RGHR _hoops_RSIRR _hoops_IIGR _hoops_RH
	 * _hoops_GSRPR _hoops_CSCR), _hoops_CCPH _hoops_PSAP _hoops_RH _hoops_RSRPR _hoops_AHI, _hoops_PPR _hoops_SGH
	 * _hoops_ASRPR() _hoops_PAR _hoops_PSRPR() _hoops_IS _hoops_HSRPR _hoops_RH
	 * _hoops_GHPP _hoops_CRGR '_hoops_RSIRR'.	_hoops_CGP _hoops_PPGAR, _hoops_ASRC _hoops_IHPR.
	 */

		/*_hoops_SIGP _hoops_HGI _hoops_RRP _hoops_IS _hoops_SHH _hoops_RPIHR _hoops_SRSAI._hoops_GCSR _hoops_HRGR _hoops_PPRGA*/
		__argc_value=0;

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

#define _hoops_GHCPI
#define __USE_POSIX199309

#include <unistd.h>

#include <time.h>
#include <sys/time.h>

#include <signal.h>
#include <sys/types.h>
#include <errno.h>

#undef __USE_POSIX199309
#undef _hoops_GHCPI

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

	ALLOC (_hoops_IAAPR, Time_Data);
	HOOPS_WORLD->_hoops_GPAPR = (void *)_hoops_IAAPR;

	gettimeofday (&_hoops_CAAPR, 0);

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

	gettimeofday (&_hoops_CAAPR, 0);
	return ((_hoops_CAAPR.tv_sec - _hoops_IAAPR->_hoops_CRAPR)*(_hoops_GSPGR)_hoops_HSPGR +
			(_hoops_CAAPR.tv_usec * (_hoops_GSPGR)_hoops_HSPGR)/1000000);
}


GLOBAL_FUNCTION void HI_Sleep(_hoops_GSPGR _hoops_SPAPR) {

	struct timespec req;	
	struct timespec _hoops_RHCPI;	

	req.tv_sec = _hoops_SPAPR/_hoops_HSPGR;
	req.tv_nsec = (((long)_hoops_SPAPR % (long)_hoops_HSPGR) * 1000000000L) / _hoops_HSPGR;

	_hoops_RHCPI.tv_sec = 0;
	_hoops_RHCPI.tv_nsec = 0;

	if (nanosleep(&req,&_hoops_RHCPI)) {
			HE_WARNING (HEC_SYSTEM, HES_ERROR_SUSPENDING_TIMER,
						"Internal error on trying to nanosleep");
	}
}


local void _hoops_RPGCC(int _hoops_IHHPI)
{
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

	_hoops_GIHI._hoops_CIHPI = _hoops_RPGCC;
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


#endif /* _hoops_ARCHH */






