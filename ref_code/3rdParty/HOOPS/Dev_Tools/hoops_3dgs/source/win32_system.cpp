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
 * $Id: obf_tmp.txt 1.108 2011-01-12 01:28:54 covey Exp $
 */

#ifdef _MSC_VER

#ifdef _hoops_GGHSH
#ifndef _hoops_CSAAGR
#define _hoops_CSAAGR 0x0501
#endif
#endif

#ifdef NUTCRACKER
#	include <wchar.h>
#endif
#	include <windows.h>	// _hoops_HPHR _hoops_SPR

#	ifndef _hoops_SSAAGR		// _hoops_RPGGI _hoops_CCAH _hoops_CR _hoops_SPIHS
#		define _hoops_SSAAGR
#	endif


extern "C" {
	BOOL WINAPI GDI_Polygon(_hoops_SSAAGR HDC _hoops_IIGAC, CONST POINT *_hoops_GGPAGR, _hoops_SSAAGR int _hoops_RGPAGR) {
		return Polygon (_hoops_IIGAC, _hoops_GGPAGR, _hoops_RGPAGR);
	}
	BOOL WINAPI GDI_Polyline(_hoops_SSAAGR HDC _hoops_IIGAC, CONST POINT *_hoops_GGPAGR, _hoops_SSAAGR int _hoops_RGPAGR) {
		return Polyline (_hoops_IIGAC, _hoops_GGPAGR, _hoops_RGPAGR);
	}
	BOOL WINAPI GDI_Ellipse( _hoops_SSAAGR HDC _hoops_IIGAC, _hoops_SSAAGR int left, _hoops_SSAAGR int top,  _hoops_SSAAGR int right, _hoops_SSAAGR int bottom) {
		return Ellipse (_hoops_IIGAC, left, top, right, bottom);
	}
	BOOL WINAPI GDI_Rectangle(_hoops_SSAAGR HDC _hoops_IIGAC, _hoops_SSAAGR int left, _hoops_SSAAGR int top, _hoops_SSAAGR int right, _hoops_SSAAGR int bottom) {
		return Rectangle (_hoops_IIGAC, left, top, right, bottom);
	}
}

// _hoops_PPR _hoops_HA _hoops_PIIA _hoops_RH "_hoops_RSAIP" _hoops_IH _hoops_RH _hoops_AHAR _hoops_IIGR _hoops_ISCP _hoops_HAII _hoops_CRRPR
#define	Ellipse		_hoops_GCAAGR
#define	Polyline	_hoops_RCAAGR
#define	Polygon		_hoops_ACAAGR
#define	Rectangle	_hoops_PCAAGR

#undef	RGB


#define HMUTEX_IMPLEMENT_FUNCTIONS

#include "hoops.h"
#include "driver.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "hversion.h"
#include "filedata.h"

#include "msw.h"
#include "hpspsf.h"

#include <stdio.h>
#include <stdlib.h>

#define _hoops_AGPAGR 512 * 1e6

GLOBAL_FUNCTION bool HI_Find_Application_Name (
	_hoops_HCRPR alter	*name) {

	HI_Copy_Chars_To_Name (GetCommandLine (), name);
	if (_hoops_AGGR(name->text, "?")) {
		FREE_ARRAY (name->text, name->length+1, char);
		HI_Copy_Chars_To_Name("unknown", name);
	}
	return true;
}


GLOBAL_FUNCTION void HI_Error_Exit (void) {
	MSG		_hoops_SSACR;

	PostQuitMessage (0);
	while (GetMessage (&_hoops_SSACR, NULL, 0, 0)) {
		TranslateMessage (&_hoops_SSACR);
		DispatchMessage (&_hoops_SSACR);
	}
	exit (_hoops_SSACR.wParam);
}


GLOBAL_FUNCTION void HI_Normal_Exit (void) {
	MSG		_hoops_SSACR;

	PostQuitMessage (0);
	while (GetMessage (&_hoops_SSACR, NULL, 0, 0)) {
		TranslateMessage (&_hoops_SSACR);
		DispatchMessage (&_hoops_SSACR);
	}
	exit (_hoops_SSACR.wParam);
}



/*****************************************************************************
 *****************************************************************************
				_hoops_CIPII _hoops_GCSR _hoops_PCCIR _hoops_PCCIR _hoops_HAS _hoops_RCSR _hoops_GSSAA _hoops_IAS	  _hoops_PHGPH _hoops_GSSAA _hoops_GCSR _hoops_RCSR _hoops_IRS _hoops_GSSAA	_hoops_APCAR _hoops_IRS _hoops_RA _hoops_IRS
 *****************************************************************************
 *****************************************************************************/


#ifdef _MSC_VER
#pragma warning (disable: 4073)	
#pragma init_seg(lib)
#endif

Begin_HOOPS_Namespace
	globaldata HOOPS_API _hoops_SSGCI _hoops_GGRCI = {
		NULL,		/* _hoops_PGPAGR */
		NULL,		/* _hoops_HGPAGR */
	};
End_HOOPS_Namespace;



HC_INTERFACE void HC_CDECL HC_Record_Instance_Handle (
	void const		*_hoops_PRCHH) {

	_hoops_RCSRH (_hoops_ACSRH) = (HINSTANCE) _hoops_PRCHH;

	/*
	 * _hoops_IGPAGR _hoops_GRS _hoops_SHH _hoops_IHHAH _hoops_RGAR _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_RSPHR _hoops_RIPHR.
	 * _hoops_HSRR _hoops_ASCSR, _hoops_ICAAGR (_hoops_CAPP) _hoops_GRS _hoops_AIAH _hoops_HS _hoops_ARP _hoops_SCH.
	 */
	if (_hoops_RCSRH (_hoops_HGRAH) == NULL)
		_hoops_RCSRH (_hoops_HGRAH) = (HINSTANCE) _hoops_PRCHH;
}


/*****************************************************************************
 *****************************************************************************
						_hoops_IISGA _hoops_RA _hoops_IRS _hoops_PCCIR _hoops_RA  /  _hoops_IISGA _hoops_RA _hoops_GCSR _hoops_CCAHR
 *****************************************************************************
 *****************************************************************************/


GLOBAL_FUNCTION void HI_Reset_Driver_Config_SS (void) {

	/* _hoops_AHHS _hoops_RHPP */
	HC_Define_Driver_Config("dx9", "*", "*", "");
	HC_Define_Driver_Config("dx9", "*radeon*", "*", "config=("
		"BAD_MSAA_SPRITING)");
	HC_Define_Driver_Config("dx9", "*firegl*", "*", "config=("
		"BAD_MSAA_SPRITING)");
	HC_Define_Driver_Config("dx9", "*intel*", "*", "config=("
		"BAD_MSAA_SPRITING)");
	HC_Define_Driver_Config("dx9", "*geforce*", "*", "config=("
		"BAD_MSAA_SPRITING, POINT_SPRITES_BASH_ALL)");
	HC_Define_Driver_Config("dx9", "*quadro*", "*", "config=("
		"BAD_MSAA_SPRITING, POINT_SPRITES_BASH_ALL)");

	/* _hoops_HCIAR _hoops_RHPP */
	HC_Define_Driver_Config("opengl2", "*", "*", "");

	HC_Define_Driver_Config("mgl", "*", "*", "");

	HC_Define_Driver_Config("opengl2", "*radeon*", "*", "config=("
		"BAD_MSAA_SPRITING)");
	HC_Define_Driver_Config("opengl2", "*radeon x1*", "*", "config=("
		"BAD_MSAA_SPRITING, BAD_NON_POWER_OF_2_TEXTURES)");

	HC_Define_Driver_Config("opengl2", "*FIREPRO*", "*", "config=("
		"TEXTURE_SIZE_OFF_BY_ONE)");

	HC_Define_Driver_Config("opengl2", "*GeForce*", "*", "config=("
		"BAD_GLSL4_SAMPLER_CUBE)");

	HC_Define_Driver_Config("opengl2", "*Quadro*", "*", "config=("
		"BAD_GLSL4_SAMPLER_CUBE)");


	/* _hoops_ICCI _hoops_RHPP */
	HC_Define_Driver_Config("opengl", "*", "*", "general tristrip minimum=3");
	 
	HC_Define_Driver_Config("opengl", "GDI Generic*", "*", "software, config=("
		"BAD_DISPLAY_LIST, BAD_MULTILIGHT, ALLOW_DRAWPIXEL_RESTORE,"
		"BAD_SPOTLIGHT_TEXTURE, BAD_SCISSORING, BAD_ACCUMULATION_BUFFER)");


	HC_Define_Driver_Config("opengl", "Quadro*", "*", "config=("
		"BAD_FLAT_VERTEX_ARRAYS, BAD_MSAA_ACCUMULATION_BUFFER, DELAYED_VERTEX_ARRAYS),"
		"tristrip minimum = 5, flat tristrip minimum = 5");

	HC_Define_Driver_Config("opengl", "Quadro*AGP*", "*", "config=("
		"BAD_FLAT_VERTEX_ARRAYS, BAD_MSAA_ACCUMULATION_BUFFER, DELAYED_VERTEX_ARRAYS, BAD_TEXTURE_RECTANGLE),"
		"tristrip minimum = 5, flat tristrip minimum = 5");

	HC_Define_Driver_Config("opengl", "Quadro4*", "*", "config=("
		"BAD_FLAT_VERTEX_ARRAYS, BAD_ACCUMULATION_BUFFER),"
		"tristrip minimum = 5, flat tristrip minimum = 5");

	HC_Define_Driver_Config("opengl", "GeForce*", "*", "general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "GeForce PCX 5*", "*", "config=("
		"4142_WORKAROUND, BAD_ACCUMULATION_BUFFER)");

	HC_Define_Driver_Config("opengl", "GeForce FX 5*", "*", "config=("
		"4142_WORKAROUND, BAD_ACCUMULATION_BUFFER)");

	HC_Define_Driver_Config("opengl", "GeForce FX Go5*", "*", "config=("
		"4142_WORKAROUND, BAD_ACCUMULATION_BUFFER)");

	HC_Define_Driver_Config("opengl", "GeForce4*", "*", "config=("
		"BAD_ACCUMULATION_BUFFER), general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "GeForce 88*", "*", "config=("
		"BAD_ACCUMULATION_BUFFER), general tristrip minimum=3");



	HC_Define_Driver_Config("opengl", "*FIREGL*", "*", "config=("
		"BAD_KTX, BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"UNDRAW_OVERLAY_FRONT_AND_BACK, BAD_NONDL_VERTEX_ARRAYS, LINE_PATTERN_NEEDS_BLENDING, "
		"BAD_CUT_POINTS),"
		"general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "*FIRE GL*", "*", "config=("
		"BAD_KTX, BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"UNDRAW_OVERLAY_FRONT_AND_BACK, BAD_NONDL_VERTEX_ARRAYS, LINE_PATTERN_NEEDS_BLENDING, "
		"BAD_CUT_POINTS),"
		"general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "*FIREPRO*", "*", "config=("
		"TEXTURE_SIZE_OFF_BY_ONE)");

	/* _hoops_CGPAGR _hoops_APAC _hoops_PIIHR _hoops_IS _hoops_CSPP 8 _hoops_IIGR _hoops_RH _hoops_RCGAH _hoops_SGPAGR _hoops_CGPAGR _hoops_SPSIR _hoops_SCCHH _hoops_RPP 
	   _hoops_RHAC _hoops_SGHHR _hoops_IS _hoops_SGH _hoops_RH _hoops_AAHRP _hoops_SRHR */
	HC_Define_Driver_Config("opengl", "*MOBILITY FIREGL*", "8", "config=("
		"BAD_KTX, BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, BAD_ACCUMULATION_BUFFER, "
		"UNDRAW_OVERLAY_FRONT_AND_BACK, BAD_NONDL_VERTEX_ARRAYS, LINE_PATTERN_NEEDS_BLENDING, "
		"BAD_CUT_POINTS),"
		"general tristrip minimum=3");
	
	HC_Define_Driver_Config("opengl", "*radeon*", "*", "config=("
		"BAD_MSAA_WGL_ARB_BUFFER, "
		"XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"BAD_NONDL_VERTEX_ARRAYS, "
		"LIES_ABOUT_SWAP, "
		"UNDRAW_OVERLAY_FRONT_AND_BACK, "
		"LINE_PATTERN_NEEDS_BLENDING, "
		"BAD_16BIT_ACCUMULATION_BUFFER),"
		"tristrip minimum=4,"
		"display list tristrip minimum=1000,"
		"flat tristrip minimum=4,"
		"flat display list tristrip minimum=32");

	HC_Define_Driver_Config("opengl", "*radeon x1*", "*", "config=("
		"SLOW_PEELED_LINESMOOTH, "
		"BAD_MSAA_WGL_ARB_BUFFER, "
		"BAD_NONDL_VERTEX_ARRAYS, "
		"LIES_ABOUT_SWAP, "
		"UNDRAW_OVERLAY_FRONT_AND_BACK, "
		"LINE_PATTERN_NEEDS_BLENDING, "
		"BAD_16BIT_ACCUMULATION_BUFFER, "
		"BAD_NON_POWER_OF_2_TEXTURES),"
		"tristrip minimum=4,"
		"display list tristrip minimum=1000,"
		"flat tristrip minimum=4,"
		"flat display list tristrip minimum=32");

	HC_Define_Driver_Config("opengl", "*RADEON 7*", "*", "config=("
		"BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"BAD_NONDL_VERTEX_ARRAYS, LIES_ABOUT_SWAP, PIXEL_OPERATIONS_EXPENSIVE, LINE_PATTERN_NEEDS_BLENDING, BAD_16BIT_ACCUMULATION_BUFFER),"
		"tristrip minimum=48,"
		"display list tristrip minimum=1000,"
		"flat tristrip minimum=5,"
		"flat display list tristrip minimum=32");

	HC_Define_Driver_Config("opengl", "*RADEON 8*", "*", "config=("
		"BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"BAD_NONDL_VERTEX_ARRAYS, BAD_DISPLAY_LIST, LIES_ABOUT_SWAP, UNDRAW_OVERLAY_FRONT_AND_BACK, "
		"LINE_PATTERN_NEEDS_BLENDING, BAD_16BIT_ACCUMULATION_BUFFER),"
		"tristrip minimum=48,"
		"display list tristrip minimum=1000,"
		"flat tristrip minimum=5,"
		"flat display list tristrip minimum=32");

	HC_Define_Driver_Config("opengl", "*RADEON 9600*", "*", "config=("
		"BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"BAD_NONDL_VERTEX_ARRAYS, LIES_ABOUT_SWAP, UNDRAW_OVERLAY_FRONT_AND_BACK, "
		"LINE_PATTERN_NEEDS_BLENDING, BAD_16BIT_ACCUMULATION_BUFFER),"
		"tristrip minimum=4,"
		"display list tristrip minimum=1000,"
		"flat tristrip minimum=4,"
		"flat display list tristrip minimum=32");

	HC_Define_Driver_Config("opengl", "*RADEON 9000*", "*", "config=("
		"BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"BAD_ACCUMULATION_BUFFER, BAD_NONDL_VERTEX_ARRAYS, LIES_ABOUT_SWAP, PIXEL_OPERATIONS_EXPENSIVE, "
		"BAD_PIXEL_STORE,LINE_PATTERN_NEEDS_BLENDING, BAD_16BIT_ACCUMULATION_BUFFER),"
		"tristrip minimum=48,"
		"display list tristrip minimum=1000,"
		"flat tristrip minimum=5,"
		"flat display list tristrip minimum=32");

	HC_Define_Driver_Config("opengl", "*RADEON Xpress*", "*", "config=("
		"BAD_MSAA_WGL_ARB_BUFFER, SLOW_MSAA_DEPTH_TEXTURE, XBIT_BAD_MSAA_ACCUMULATION_BUFFER, "
		"BAD_NONDL_VERTEX_ARRAYS, LIES_ABOUT_SWAP, UNDRAW_OVERLAY_FRONT_AND_BACK, "
		"BAD_PATTERNED_LINES, LINE_PATTERN_NEEDS_BLENDING, BAD_16BIT_ACCUMULATION_BUFFER),"
		"tristrip minimum=4,"
		"display list tristrip minimum=1000,"
		"flat tristrip minimum=4,"
		"flat display list tristrip minimum=32");

	HC_Define_Driver_Config("opengl", "*Intel*", "*", "config=("
		"BAD_MULTIPLE_CLIP_PLANES, BAD_WGL_ARB_BUFFER, BAD_VERTEX_BUFFER_OBJECT, BAD_FRAGMENT_PROGRAM, XBIT_BAD_SEPARATE_SPECULAR),"
		"general tristrip minimum=6");

	HC_Define_Driver_Config("opengl", "Intel 865*", "*", "config=("
		"BAD_MULTIPLE_CLIP_PLANES, UNDRAW_OVERLAY_FRONT_AND_BACK, WGL_ARB_BUFFER_1024_LIMIT, BAD_VERTEX_BUFFER_OBJECT, BAD_FRAGMENT_PROGRAM, XBIT_BAD_SEPARATE_SPECULAR),"
		"tristrip minimum=6");

	HC_Define_Driver_Config("opengl", "Intel 915*", "*", "config=("
		"BAD_MULTIPLE_CLIP_PLANES, UNDRAW_OVERLAY_FRONT_AND_BACK, WGL_ARB_BUFFER_1024_LIMIT, BAD_VERTEX_BUFFER_OBJECT, BAD_FRAGMENT_PROGRAM, XBIT_BAD_SEPARATE_SPECULAR),"
		"tristrip minimum=6");

	HC_Define_Driver_Config("opengl", "*Intel*accelerator hd*", "*", "config=("
		"BAD_ACCUMULATION_BUFFER, BAD_FRAGMENT_PROGRAM, BAD_VERTEX_BUFFER_OBJECT),"
		"general tristrip minimum=6");


	/* 
	 *					_hoops_GRPAGR _hoops_RRPAGR
	 */ 


	HC_Define_Driver_Config("opengl", "*Fire GL2*", "*", 
		"config=(BAD_KTX), general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "*FIRE GL 7800*", "*", "config=("
		"BAD_DISPLAY_LIST, LINE_PATTERN_NEEDS_BLENDING), general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "*FIREGL T2*", "*", "config=("
		"BAD_DISPLAY_LIST, LINE_PATTERN_NEEDS_BLENDING), general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "*FireGL 4000*", "*", "config=("
		"UNDRAW_OVERLAY_FRONT_AND_BACK), general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "Wildcat*", "*", "config=("
		"UNDRAW_OVERLAY_FRONT_AND_BACK, FLAT_TRISTRIP_MISMATCH),"
		"tristrip minimum=3,"
		"display list tristrip minimum=6,"
		"flat tristrip minimum=3,"
		"flat display list tristrip minimum=6");

	HC_Define_Driver_Config("opengl", "Wildcat VP*", "*", "config=("
		"BAD_PHONG, UNDRAW_OVERLAY_FRONT_AND_BACK, FLAT_TRISTRIP_MISMATCH),"
		"tristrip minimum=10,"
		"display list tristrip minimum=10,"
		"flat tristrip minimum=12,"
		"flat display list tristrip minimum=12");
	
	/* _hoops_HPIH _hoops_ARPAGR _hoops_CRGPR */
	HC_Define_Driver_Config("opengl", "wcgdrv*", "*", "config=("
		"UNDRAW_OVERLAY_FRONT_AND_BACK, FLAT_TRISTRIP_MISMATCH),"
		"tristrip minimum=3,"
		"display list tristrip minimum=6,"
		"flat tristrip minimum=3,"
		"flat display list tristrip minimum=6");

	/* _hoops_PRPAGR */
	HC_Define_Driver_Config("opengl", "GLZICD*", "*", 
		"general tristrip minimum=3");

	HC_Define_Driver_Config("opengl", "GLINT MX + GLINT Delta*", "*", "config=("
		"DOUBLE_BUFFER_SWAP_ONLY)");

	/* 3Dlab_hoops_GRI' _hoops_HRPAGR _hoops_IRPAGR */
	HC_Define_Driver_Config("opengl", "GLINT R3 PT*", "*", "config=("
		"BAD_DISPLAY_LIST, UNDRAW_OVERLAY_FRONT_AND_BACK, BAD_TRANSPARENT_POINT)");


	HC_Define_Driver_Config("opengl", "RAGE 128 M*", "*", "config=("
		"BAD_KTX),"
		"tristrip minimum=100,"
		"display list tristrip minimum=100,"
		"flat tristrip minimum=100,"
		"flat display list tristrip minimum=100");

	HC_Define_Driver_Config("opengl", "RAGE 128 M1*", "*", "config=("
		"FORCE_DEFAULT_SOFTWARE, BAD_SCISSORING)");

	HC_Define_Driver_Config("opengl", "RAGE 128 M2*", "*", "config=("
		"FORCE_DEFAULT_SOFTWARE, BAD_SCISSORING)");

	HC_Define_Driver_Config("opengl", "RAGE 128 M3*", "*", "config=("
		"FORCE_DEFAULT_SOFTWARE, BAD_SCISSORING)");

	HC_Define_Driver_Config("opengl", "RagePRO*", "*", "config=("
		"FORCE_DEFAULT_SOFTWARE, BAD_SCISSORING),"
		"tristrip minimum=100,"
		"display list tristrip minimum=100,"
		"flat tristrip minimum=100,"
		"flat display list tristrip minimum=100");

	HC_Define_Driver_Config("opengl", "Rage 128*", "*", "config=("
		"BAD_KTX, LIES_ABOUT_SWAP, BAD_PBUFFER, BAD_PATTERNED_LINES),"
		"tristrip minimum=100,"
		"display list tristrip minimum=100,"
		"flat tristrip minimum=100,"
		"flat display list tristrip minimum=100");

	HC_Define_Driver_Config("opengl", "RIVA TNT*", "*", "config=("
		"FORCE_OLD_CHOOSE_PIXEL_FORMAT)");

	HC_Define_Driver_Config("opengl", "SuperSavage*", "*", "config=("
		"FORCE_DEFAULT_SOFTWARE)");

	if (HOOPS_WORLD->_hoops_PARPR.length != 0)
		HI_Read_Driver_Config_File();
}


//_hoops_IPPHR _hoops_IIGR _hoops_CRPAGR _hoops_HRGR _hoops_GGR _hoops_SRPAGR._hoops_GGHR
//_hoops_ACGIA _hoops_PPARR _hoops_GAPAGR{ 
//	_hoops_CGSRGR _hoops_RAPAGR; 
//	_hoops_CGSRGR _hoops_AAPAGR; 
//	_hoops_CGSRGR _hoops_PAPAGR; 
//	_hoops_CGSRGR _hoops_HAPAGR; 
//	_hoops_CGSRGR _hoops_IAPAGR; 
//	_hoops_CAPAGR _hoops_SAPAGR[ 128 ]; 
//} _hoops_CRPAGR; 


local _hoops_RIRCI _hoops_GPPAGR (void) {
#ifndef _WIN32_WCE
	OSVERSIONINFO _hoops_RPPAGR;
		
	_hoops_RPPAGR.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	::GetVersionEx(&_hoops_RPPAGR);

	switch(_hoops_RPPAGR.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s: 
			return _hoops_PHRCI;

		case VER_PLATFORM_WIN32_WINDOWS:
			if(_hoops_RPPAGR.dwMinorVersion==0)
				return _hoops_GGARI;
			if(_hoops_RPPAGR.dwMinorVersion==10)  
				return _hoops_RGARI;
			if(_hoops_RPPAGR.dwMinorVersion==90)
				return _hoops_RGARI;  //_hoops_IGRC _hoops_SPHGR _hoops_CPCSI, _hoops_HIH _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_SGS _hoops_APPAGR

		default: 
		case VER_PLATFORM_WIN32_NT:
			if (_hoops_RPPAGR.dwMajorVersion > 5)
				return _hoops_GIRCI;
			if (_hoops_RPPAGR.dwMajorVersion == 5 && _hoops_RPPAGR.dwMinorVersion==1)
				return _hoops_SHRCI;  //_hoops_AHPCR _hoops_GRGP _hoops_SIHC _hoops_GGR _hoops_PPPAGR._hoops_SAPAGR);
			if(_hoops_RPPAGR.dwMajorVersion == 5 && _hoops_RPPAGR.dwMinorVersion==0)
				return _hoops_CHRCI;  //_hoops_AHPCR _hoops_GRGP _hoops_SIHC _hoops_GGR _hoops_PPPAGR._hoops_SAPAGR);
			if (_hoops_RPPAGR.dwMajorVersion <= 4) {
				if (_hoops_RPPAGR.dwMajorVersion < 3)
					HE_ERROR (HEC_START_DRIVERS, HES_PROCEDURAL_ERROR, 
						"Unexpected result during query of windows version.");
			}
	}
	return _hoops_IHRCI;
#else
	return _hoops_HHRCI;
#endif
}

local void _hoops_HPPAGR();


/*
 * _hoops_HGI _hoops_PCPH (_hoops_HIHPA _hoops_IPPAGR _hoops_RH _hoops_AGAH _hoops_CPPAGR _hoops_HPGHI)
 * _hoops_HSSIA _hoops_GHARR _hoops_PIH _hoops_PPR _hoops_SPPAGR _hoops_SCH. _hoops_IPCP _hoops_CISPP
 * _hoops_AGR _hoops_SPASR _hoops_RH _hoops_CAPHR _hoops_AGR _hoops_GGR _hoops_PICCI._hoops_GGHR.
 */
GLOBAL_FUNCTION void HI_Start_System_Specific (
	_hoops_AIGPR *_hoops_RIGC) {
	_hoops_RRPRH alter		*_hoops_IRSRA;
	HDC						_hoops_PGICI;
	_hoops_RIRCI				_hoops_SSRRI;
	int						ii;

# ifdef _M_IX86
	unsigned long			features1 = 0;
	unsigned long			features2 = 0;
	unsigned long			extended = 0;
	unsigned long			signature = 0;
	char					brand[16];				/* 12 _hoops_HGCR _hoops_PIISR _hoops_GGR _hoops_HPP _hoops_GHPAGR */

	memset (brand, 0, 16);
# endif

	_hoops_HPPAGR();

	/* _hoops_SGH _hoops_IRGH _hoops_PSGR _hoops_CR _hoops_HSRGR->_hoops_RHPAGR _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_CCRSA'_hoops_GHGP _hoops_GAPR */
	_hoops_SSRRI = _hoops_GPPAGR ();

	if (HOOPS_WORLD->_hoops_SSPGI == null) {
		ZALLOC (_hoops_IRSRA, _hoops_RRPRH);
		HOOPS_WORLD->_hoops_SSPGI = (void alter *)_hoops_IRSRA;

		PUSHNAME(_hoops_RIGC);

		_hoops_IRSRA->_hoops_SSRRI = _hoops_SSRRI;

		/* _hoops_GASH _hoops_HSRGR->_hoops_AHPAGR _hoops_PPR _hoops_HSRGR->_hoops_PHPAGR */
		if (_hoops_IRSRA->_hoops_SSRRI == _hoops_PHRCI) {
			HC_Record_Profile_Source ("HOOPS", "WIN.INI");
		}
		else {
			HC_Record_Profile_Source (null, "REGISTRY");	/* _hoops_SHIR _hoops_PAPR _hoops_GGR _hoops_HHPAGR */
		}

		POPNAME(_hoops_RIGC);
	}
	else {
		_hoops_IRSRA = (_hoops_RRPRH alter *)HOOPS_WORLD->_hoops_SSPGI;
		_hoops_IRSRA->_hoops_SSRRI = _hoops_SSRRI;
	}


# ifdef _M_IX86
	/* _hoops_CGIC _hoops_RPP _hoops_IIH _hoops_CHR _hoops_GII _hoops_SCIRH-_hoops_SASI _hoops_SGHGC _hoops_SR _hoops_SIAS _hoops_SGH */
	__asm {
		pushfd							; _hoops_IHPAGR to stack
		pop		eax						; move to EAX
		mov		ebx, eax				; save a _hoops_APCPH
		xor		eax, 0200000H			; _hoops_IRCPR bit 21
		push	eax						; move to stack
		popfd							; _hoops_CHPAGR to set _hoops_SACRH value
		pushfd							; _hoops_AACP current value
		pop		eax
		xor		eax, ebx				; is it _hoops_GIPAA _hoops_PPSHP?
		jz		Done					; no, _hoops_SHPAGR or _hoops_RSACR...

		mov		eax, 0					; request ID and limit
		cpuid
		mov		DWORD PTR [brand], ebx	; _hoops_GIPAGR id
		mov		DWORD PTR [brand+4], edx
		mov		DWORD PTR [brand+8], ecx
		test	eax, eax				; _hoops_GPCPH _hoops_IHIIR _hoops_RIPAGR for other _hoops_AIPAGR?
		jz		Done					; done if not

		mov		eax, 1					; request _hoops_PIPAGR
		cpuid
		mov		[features1], edx		; _hoops_HIPAGR _hoops_IIPAGR _hoops_PIPAGR
		mov		[features2], ecx		; _hoops_HIPAGR _hoops_CACPA _hoops_PIPAGR
		mov		[signature], eax		; _hoops_HIPAGR signature (_hoops_CIPAGR _hoops_SIPAGR)

		mov		eax, 080000000H			; _hoops_GCPAGR extended _hoops_RCPAGR _hoops_AAGHR?
		cpuid
		cmp		eax, 080000001H			; _hoops_IHIIR _hoops_HSIPA _hoops_RRCI _hoops_AHCPA the first
		jb		Done

		mov		eax, 080000001H			; request extended _hoops_PIPAGR
		cpuid
		mov		[extended], edx			; _hoops_HIPAGR extended _hoops_PIPAGR

	  Done:
	}

	/*	_hoops_ACPAGR _hoops_RCC			_hoops_PCPAGR				_hoops_PIIIS _hoops_HCPAGR _hoops_ICPAGR
		-----------------------------------------------------------------------------------------------
		_hoops_CCPAGR		_hoops_SCPAGR						_hoops_GSPAGR, _hoops_HCIAI, _hoops_SCIAI, _hoops_PHHGI
		_hoops_RSPAGR		_hoops_IRHGC							_hoops_GSPAGR, 3D_hoops_AGGA!, 3D_hoops_AGGA! _hoops_ASPAGR _hoops_ICPAGR, _hoops_GSPAGR _hoops_ICPAGR

		_hoops_PSPAGR		_hoops_HSPAGR						_hoops_GSPAGR, _hoops_ISPAGR
		_hoops_CSPAGR		_hoops_SSPAGR						_hoops_GSPAGR, 3D_hoops_AGGA!
		_hoops_GGHAGR		_hoops_RGHAGR
		_hoops_AGHAGR		_hoops_PGHAGR					_hoops_GSPAGR
		_hoops_HGHAGR		_hoops_IGHAGR
		_hoops_CGHAGR _hoops_CGHAGR _hoops_CGHAGR 		_hoops_CGHAGR
		_hoops_SGHAGR _hoops_SGHAGR _hoops_SGHAGR 		_hoops_SGHAGR
		_hoops_GRHAGR _hoops_HPP _hoops_RRHAGR		_hoops_ARHAGR _hoops_PRHAGR
	*/

	/* _hoops_ICPA _hoops_AAARR */
	if (features1 & (1ul<<23)) {
		HOOPS_WORLD->_hoops_CIIPA |= _hoops_CPHGI;

		if (features1 & (1ul<<25)) {
			/* _hoops_HCIAI _hoops_IAGHR, _hoops_HIH _hoops_GCA _hoops_RSHAC _hoops_GCGH */
			__try {
				XORPS   (XMM0, XMM0)

				/* _hoops_RPP _hoops_SR _hoops_HGCR _hoops_ARI, _hoops_SCH _hoops_PIHA _hoops_SHH _hoops_CRSH... */
				HOOPS_WORLD->_hoops_CIIPA |= _hoops_SIIPA;

				if (features1 & (1ul<<26))
					HOOPS_WORLD->_hoops_CIIPA |= _hoops_SPHGI;

				if (_hoops_AGGR (brand, "GenuineIntel")) {
					/* _hoops_SCPAGR _hoops_SASI _hoops_AAARR */
					if (features2 & (1ul<<0))
						HOOPS_WORLD->_hoops_CIIPA |= _hoops_GHHGI;
					if (features2 & (1ul<<9))
						HOOPS_WORLD->_hoops_CIIPA |= _hoops_RHHGI;
					if (features2 & (1ul<<13))
						HOOPS_WORLD->_hoops_CIIPA |= _hoops_SHHGI;
					if (features2 & (1ul<<19))
						HOOPS_WORLD->_hoops_CIIPA |= _hoops_HHHGI;
					if (features2 & (1ul<<20))
						HOOPS_WORLD->_hoops_CIIPA |= _hoops_CHHGI;
				}

				/* _hoops_PPR _hoops_PAH _hoops_SR _hoops_AGRP _hoops_SAPS _hoops_RGSHA _hoops_AAIP _hoops_SGS _hoops_GHCA _hoops_SHH _hoops_PSIGA? */
				if (features1 & (1ul<<24)) {		/* _hoops_HRHAGR/_hoops_IRHAGR _hoops_APP _hoops_HPP _hoops_SCIRH */
					unsigned char			_hoops_CRHAGR[600];	/* 512 _hoops_GCSRR _hoops_IPSH _hoops_AHSGP _hoops_GRHII */
					unsigned long *			_hoops_SRHAGR;		/* 512 _hoops_GCSRR _hoops_GRS _hoops_SHH _hoops_RGCGA */

					_hoops_SRHAGR = (unsigned long *)ALIGNED_16(_hoops_CRHAGR);
					/* _hoops_HHH _hoops_PAGRC _hoops_GA'_hoops_RA _hoops_CISA _hoops_GGR _hoops_CPS... */
					ZERO_ARRAY (_hoops_SRHAGR, 512, unsigned char);

					__asm mov	eax, dword ptr _hoops_SRHAGR
					FXSAVE		(EAX)

					HOOPS_WORLD->_hoops_RCIPA = _hoops_SRHAGR[7] &			/* _hoops_GAHAGR */
											   ((1UL <<  6) |				/* _hoops_PCIPA-_hoops_AGSH-_hoops_GHPA */
												(1UL << 11) |				/* _hoops_RAHAGR _hoops_AAHAGR */
												(1UL << 15));				/* _hoops_ACIPA _hoops_GHPA */
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) { /* _hoops_HAR _hoops_APP */ }
		}

		if (!_hoops_AGGR (brand, "GenuineIntel")) {
			/* _hoops_SHII _hoops_HPP [_hoops_ICRP?] _hoops_GRAA-_hoops_SCPAGR _hoops_PAHAGR */
			if (extended & (1ul<<31))
				HOOPS_WORLD->_hoops_CIIPA |= _hoops_GIHGI;

			if (_hoops_AGGR (brand, "AuthenticAMD")) {
				/* _hoops_IRHGC _hoops_SASI _hoops_AAARR */
				if (extended & (1ul<<30))
					HOOPS_WORLD->_hoops_CIIPA |= _hoops_RIHGI;
				if (extended & (1ul<<22))
					HOOPS_WORLD->_hoops_CIIPA |= _hoops_AIHGI;

				if (features2 & (1ul<<9))
					HOOPS_WORLD->_hoops_CIIPA |= _hoops_RHHGI;
				if (features2 & (1ul<<13))
					HOOPS_WORLD->_hoops_CIIPA |= _hoops_SHHGI;
				if (features2 & (1ul<<19))
					HOOPS_WORLD->_hoops_CIIPA |= _hoops_HHHGI;
			}
		}
	}
# endif


	/* _hoops_IIRCI _hoops_GCSP _hoops_HPP _hoops_SPGIA _hoops_IIGR _hoops_HRCRH _hoops_RHPP */
	_hoops_IRSRA->bit_patterns = (HBITMAP *) NULL;
	
	/* _hoops_APGIP */
	_hoops_IRSRA->_hoops_SIRCI =
		_hoops_IRSRA->_hoops_GCRCI = (FARPROC) 0;
	_hoops_IRSRA->_hoops_RCRCI = 0;

	_hoops_IRSRA->_hoops_ACRCI = (HANDLE) NULL;
	_hoops_IRSRA->_hoops_PCRCI = (DWORD) 0;
	_hoops_IRSRA->_hoops_HCRCI = false;

	_hoops_IRSRA->_hoops_ICRCI = (FARPROC) 0;
	_hoops_IRSRA->_hoops_CCRCI = FALSE;
	_hoops_IRSRA->_hoops_SCRCI = (HWND) 0;

	for (ii = 0; ii < 80; ii++)
		_hoops_IRSRA->_hoops_GSRCI[ii] = '\0';

	for (ii = 0; ii < 8; ii++)
		_hoops_IRSRA->_hoops_RSRCI[ii] = 0;

	/*
	 * _hoops_GPGP _hoops_AGR _hoops_IS _hoops_SRCH _hoops_IRS _hoops_AHCPR _hoops_IIGR _hoops_GRH _hoops_AGIR _hoops_RRGR _hoops_IH
	 * _hoops_SRS _hoops_CSGSR _hoops_SR _hoops_SAHR _hoops_CCPP _hoops_SPR _hoops_PPR _hoops_HS _hoops_CPHR
	 * _hoops_CCA _hoops_SCH
	 */
	_hoops_PGICI = GetDC (GetDesktopWindow ());
	_hoops_IRSRA->_hoops_ISRCI = GetDeviceCaps (_hoops_PGICI, NUMPENS);
	if (_hoops_IRSRA->_hoops_ISRCI < 1) {
		/*
		 * _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_CISRI (_hoops_HAS._hoops_IAS. -1) _hoops_GGR _hoops_PGAP _hoops_AGIR
		 * _hoops_SR _hoops_GRS _hoops_SGH _hoops_HRRPI
		 */
		_hoops_IRSRA->_hoops_ISRCI = 65535 / sizeof (_hoops_PGRCI) - 1;
	}
	if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && _hoops_IRSRA->_hoops_ISRCI > 8)
		_hoops_IRSRA->_hoops_ISRCI = 8;
	_hoops_IRSRA->_hoops_CSRCI = 0;
	_hoops_IRSRA->_hoops_SSRCI._hoops_HGRCI = NULL;
	_hoops_IRSRA->_hoops_SSRCI._hoops_IGRCI		= MAXDWORD;
	_hoops_IRSRA->_hoops_SSRCI._hoops_CGRCI		= MAXDWORD;
	_hoops_IRSRA->_hoops_SSRCI._hoops_SGRCI	= MAXDWORD;
	_hoops_IRSRA->_hoops_SSRCI._hoops_GRRCI		= NULL;
	_hoops_IRSRA->_hoops_SSRCI.line_style		= null;
	_hoops_IRSRA->_hoops_SSRCI._hoops_AGRCI		= NULL;

	/*
	 * _hoops_GPGP _hoops_AGR _hoops_IS _hoops_SRCH _hoops_IRS _hoops_AHCPR _hoops_IIGR _hoops_GRH _hoops_AGIR _hoops_RRGR _hoops_IH
	 * _hoops_SRS _hoops_IPHCI _hoops_SR _hoops_SAHR _hoops_CCPP _hoops_SPR _hoops_PPR _hoops_HS _hoops_CPHR
	 * _hoops_CCA _hoops_SCH
	 */
	_hoops_IRSRA->_hoops_GGACI = GetDeviceCaps (_hoops_PGICI, NUMBRUSHES);
	if (_hoops_IRSRA->_hoops_GGACI < 1) {
		/*
		 * _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_ASRCI (_hoops_HAS._hoops_IAS. -1) _hoops_GGR _hoops_PGAP _hoops_AGIR
		 * _hoops_SR _hoops_GRS _hoops_SGH _hoops_HRRPI
		 */
		_hoops_IRSRA->_hoops_GGACI = 65535 / sizeof(_hoops_ARRCI) - 1;
	}
	if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && _hoops_IRSRA->_hoops_GGACI > 8)
		_hoops_IRSRA->_hoops_GGACI = 8;
	_hoops_IRSRA->_hoops_RGACI					= 0;
	_hoops_IRSRA->_hoops_AGACI._hoops_PRRCI		= NULL;
	_hoops_IRSRA->_hoops_AGACI._hoops_HRRCI			= (short)-1;
	_hoops_IRSRA->_hoops_AGACI._hoops_IRRCI	= -1;
	_hoops_IRSRA->_hoops_AGACI._hoops_RARCI._hoops_GARCI = _hoops_IAASP;
	_hoops_IRSRA->_hoops_AGACI._hoops_AARCI		= _hoops_IAASP;
	_hoops_IRSRA->_hoops_AGACI._hoops_PARCI	= 0;
	_hoops_IRSRA->_hoops_AGACI._hoops_HARCI			= (HBRUSH)NULL;
	_hoops_IRSRA->_hoops_AGACI._hoops_AGRCI			= NULL;


	// _hoops_GPGP _hoops_AGR _hoops_IS _hoops_SRCH _hoops_IRS _hoops_AHCPR _hoops_IIGR _hoops_GRH _hoops_AGIR _hoops_RRGR _hoops_IH
	// _hoops_SRS _hoops_CSGSR _hoops_SR _hoops_SAHR _hoops_CCPP _hoops_SPR _hoops_PPR _hoops_HS _hoops_CPHR _hoops_CCA _hoops_SCH

	int _hoops_HIICI = GetDeviceCaps (_hoops_PGICI, LOGPIXELSY);

	HOOPS_WORLD->_hoops_CRGHP = 
		HOOPS_WORLD->_hoops_IRGHP = (float)_hoops_HIICI/96.0f;

	_hoops_IRSRA->_hoops_PGACI = GetDeviceCaps (_hoops_PGICI, NUMFONTS);
	if (_hoops_IRSRA->_hoops_PGACI < 1) {
		// _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_GSPIP (_hoops_HAS._hoops_IAS. -1) _hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR _hoops_GRS _hoops_SGH _hoops_HRRPI
		_hoops_IRSRA->_hoops_PGACI = 65535 / sizeof (_hoops_HPRCI) - 1;
	}
	if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && _hoops_IRSRA->_hoops_PGACI > 8)
		_hoops_IRSRA->_hoops_PGACI = 8;
	_hoops_IRSRA->_hoops_HGACI = 0;
	_hoops_IRSRA->_hoops_IGACI._hoops_IPRCI		= NULL;
	_hoops_IRSRA->_hoops_IGACI._hoops_CPRCI			= NULL;
	_hoops_IRSRA->_hoops_IGACI._hoops_GPRCI				= NULL;
	_hoops_IRSRA->_hoops_IGACI._hoops_CIRHH				= 0;
	_hoops_IRSRA->_hoops_IGACI._hoops_SPRCI		= 0;
	_hoops_IRSRA->_hoops_IGACI._hoops_AGRCI				= NULL;

	ReleaseDC (GetDesktopWindow (), _hoops_PGICI);


	_hoops_IRSRA->_hoops_CGACI = FALSE;

	_hoops_IRSRA->_hoops_GRACI = false;
	_hoops_IRSRA->_hoops_RRACI = false;
	_hoops_IRSRA->_hoops_SGACI = false;
	_hoops_IRSRA->d3d_hoops_class = false;

	_hoops_IRSRA->d3d_shared_data = NULL;

#ifdef _hoops_RHRCI
	_hoops_IRSRA->_hoops_CRACI = NULL;
#endif

	/*
	_hoops_HSRGR->_hoops_HAHAGR = 0;
	_hoops_HSRGR->_hoops_IAHAGR = 0;
	*/

	_hoops_IRSRA->font_list = 0;


	char _hoops_CAHAGR[MAX_PATH];
	GetWindowsDirectoryA (_hoops_CAHAGR, MAX_PATH);
	_hoops_HPRPR ("\\Fonts", _hoops_CAHAGR);
	HI_Copy_Chars_To_Name (_hoops_CAHAGR, &HOOPS_WORLD->_hoops_HAHGI);

	/* _hoops_PCPH _hoops_SGS _hoops_CGPRA _hoops_IS _hoops_GGARP _hoops_AGAH _hoops_GRRGI (*._hoops_CGGAS _hoops_GSIHH)*/
#ifdef DYNAMIC_LOADER
	HOOPS_WORLD->_hoops_IARPR = HD_Win32_Load_Dynamic_Driver;
#endif
}


GLOBAL_FUNCTION void HI_Stop_System_Specific (void) {
	_hoops_RRPRH		*_hoops_IRSRA = (_hoops_RRPRH alter *)HOOPS_WORLD->_hoops_SSPGI;

	if (_hoops_IRSRA->_hoops_IRACI != null) 
		_hoops_IRSRA->_hoops_IRACI();

	/* _hoops_SAHAGR _hoops_ISHGR */
#ifndef _WIN32_WCE
	if (_hoops_IRSRA->_hoops_SGACI) {
		UnregisterClass ("HoopsWClassMSW", _hoops_RCSRH (_hoops_ACSRH));
		_hoops_IRSRA->_hoops_SGACI = 0;
	}

	if (_hoops_IRSRA->_hoops_GRACI) {
		UnregisterClass ("HoopsWClassOGL", _hoops_RCSRH (_hoops_ACSRH));
		_hoops_IRSRA->_hoops_GRACI = 0;
	}

	if (_hoops_IRSRA->_hoops_RRACI) {
		UnregisterClass ("HoopsWClassOGL2", _hoops_RCSRH (_hoops_ACSRH));
		_hoops_IRSRA->_hoops_RRACI = 0;
	}

	if (_hoops_IRSRA->d3d_hoops_class) {
		UnregisterClass ("HoopsWClassD3D", _hoops_RCSRH (_hoops_ACSRH));
		_hoops_IRSRA->d3d_hoops_class = 0;
	}

#endif
	if (_hoops_IRSRA->_hoops_ACRCI != NULL) {
		/*
		 * _hoops_CGP _hoops_SR _hoops_HS _hoops_IRS _hoops_CIAPR _hoops_ISSSH _hoops_AIS,
		 * _hoops_SR _hoops_RIAGR _hoops_GIH _hoops_GSAGP _hoops_SCH _hoops_ISHP
		 */
		_hoops_IRSRA->_hoops_HCRCI = true;

		/* _hoops_IHPP _hoops_GPHAGR _hoops_HIS _hoops_IRISP _hoops_PAH _hoops_CIPGA */
		if (HI_Enable_Timer_Interrupts ()) {

			while (_hoops_IRSRA->_hoops_HCRCI) {
				Sleep(10); 
			}
			Sleep(10); 
		}

		CloseHandle (_hoops_IRSRA->_hoops_ACRCI);
		_hoops_IRSRA->_hoops_ACRCI=NULL;
		_hoops_IRSRA->_hoops_HCRCI=false;
	}


	/* _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_GII _hoops_HRCSR _hoops_IHAH _hoops_SR _hoops_GHCA _hoops_HS _hoops_HGSR */
	{
		_hoops_HPRCI alter   *_hoops_GHHCI;
		_hoops_HPRCI alter   *_hoops_RPHAGR;
		_hoops_PPRCI alter	   *_hoops_ISGSI;
		_hoops_PPRCI		   *_hoops_AGRCI;

		_hoops_GHHCI = _hoops_IRSRA->_hoops_IGACI._hoops_IPRCI;

		while (_hoops_GHHCI != NULL) {
			_hoops_RPHAGR = _hoops_GHHCI->_hoops_IPRCI;

			_hoops_ISGSI = _hoops_GHHCI->_hoops_AGRCI;
			while (_hoops_ISGSI != NULL) {
				/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
				_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
				_hoops_GHHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
				if (_hoops_ISGSI->_hoops_AGRCI != NULL)
						_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
							_hoops_ISGSI->_hoops_AGRCI;
				FREE (_hoops_ISGSI, _hoops_PPRCI);
				_hoops_ISGSI = _hoops_AGRCI;
			}

			DeleteObject (_hoops_GHHCI->_hoops_CPRCI);
			FREE (_hoops_GHHCI, _hoops_HPRCI);
			_hoops_GHHCI = _hoops_RPHAGR;
		}
	}

	/* _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_GII _hoops_IPHCI _hoops_IHAH _hoops_SR _hoops_GHCA _hoops_HS _hoops_HGSR */
	{
		_hoops_ARRCI alter	*_hoops_SPHCI;
		_hoops_ARRCI alter	*_hoops_RPHAGR;
		_hoops_RRRCI alter	*_hoops_ISGSI;
		_hoops_RRRCI			*_hoops_AGRCI;

		_hoops_SPHCI = _hoops_IRSRA->_hoops_AGACI._hoops_PRRCI;

		while (_hoops_SPHCI != NULL) {
			_hoops_RPHAGR = _hoops_SPHCI->_hoops_PRRCI;

			_hoops_ISGSI = _hoops_SPHCI->_hoops_AGRCI;
			while (_hoops_ISGSI != NULL) {
				/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
				_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
				_hoops_SPHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
				if (_hoops_ISGSI->_hoops_AGRCI != NULL)
						_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
							_hoops_ISGSI->_hoops_AGRCI;
				FREE (_hoops_ISGSI, _hoops_RRRCI);
				_hoops_ISGSI = _hoops_AGRCI;
			}

			DeleteObject (_hoops_SPHCI->_hoops_HARCI);
			FREE (_hoops_SPHCI, _hoops_ARRCI);
			_hoops_SPHCI = _hoops_RPHAGR;
		}
	}

	/* _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_GII _hoops_CSGSR _hoops_IHAH _hoops_SR _hoops_GHCA _hoops_HS _hoops_HGSR */
	{
		_hoops_PGRCI alter	  *_hoops_CPHCI;
		_hoops_PGRCI alter	  *_hoops_RPHAGR;
		_hoops_RGRCI alter	  *_hoops_ISGSI;
		_hoops_RGRCI			*_hoops_AGRCI;

		_hoops_CPHCI = _hoops_IRSRA->_hoops_SSRCI._hoops_HGRCI;

		while (_hoops_CPHCI != NULL) {
			_hoops_RPHAGR = _hoops_CPHCI->_hoops_HGRCI;

			_hoops_ISGSI = _hoops_CPHCI->_hoops_AGRCI;
			while (_hoops_ISGSI != NULL) {
				/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
				_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
				_hoops_CPHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
				if (_hoops_ISGSI->_hoops_AGRCI != NULL)
						_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
							_hoops_ISGSI->_hoops_AGRCI;
				FREE (_hoops_ISGSI, _hoops_RGRCI);
				_hoops_ISGSI = _hoops_AGRCI;
			}

			DeleteObject (_hoops_CPHCI->_hoops_GRRCI);

			_hoops_CPHCI->line_style = null;

			FREE (_hoops_CPHCI, _hoops_PGRCI);
			_hoops_CPHCI = _hoops_RPHAGR;
		}
	}

	/* _hoops_CPCS _hoops_RH _hoops_HSSPP _hoops_GCSP _hoops_PSSCI _hoops_PAIA */
	if (_hoops_IRSRA->bit_patterns != null) {
		int				ii;

		for (ii = 0; ii < TOTAL_BIT_PATTERNS; ii++)
			DeleteObject (_hoops_IRSRA->bit_patterns[ii]);

		FREE_ARRAY (_hoops_IRSRA->bit_patterns, TOTAL_BIT_PATTERNS, HBITMAP);
		_hoops_IRSRA->bit_patterns = null;
	}


	/*_hoops_RGR _hoops_CRRHP _hoops_RH _hoops_HRSAR _hoops_HRCSR _hoops_HIGR*/
	{
		_hoops_SGRRR * _hoops_HSSRH = _hoops_IRSRA->font_list;
		_hoops_SGRRR * _hoops_ISSRH;

		while (_hoops_HSSRH) {

			_hoops_ISSRH = _hoops_HSSRH->next;

			FREE_ARRAY (_hoops_HSSRH->name, _hoops_SSGR(_hoops_HSSRH->name) + 1, char);

			if (_hoops_HSSRH->specific)
				FREE_ARRAY (_hoops_HSSRH->specific, _hoops_SSGR(_hoops_HSSRH->specific) + 1, char);

			FREE (_hoops_HSSRH, _hoops_SGRRR);

			_hoops_HSSRH = _hoops_ISSRH;
		}

		_hoops_IRSRA->font_list = 0;
	}

	FREE (_hoops_IRSRA, _hoops_RRPRH);
	HOOPS_WORLD->_hoops_SSPGI = NULL;
}


local struct _hoops_APHAGR {
	HKEY			key;
	char const *	name;
} _hoops_PPHAGR [] = {
		{HKEY_CLASSES_ROOT,		"\\HKEY_CLASSES_ROOT\\"},
		{HKEY_CURRENT_USER,		"\\HKEY_CURRENT_USER\\"},
		{HKEY_LOCAL_MACHINE,	"\\HKEY_LOCAL_MACHINE\\"},
		{HKEY_USERS,			"\\HKEY_USERS\\"},
#ifndef _WIN32_WCE
		{HKEY_PERFORMANCE_DATA, "\\HKEY_PERFORMANCE_DATA\\"},
		{HKEY_CURRENT_CONFIG,	"\\HKEY_CURRENT_CONFIG\\"},
		{HKEY_DYN_DATA,			"\\HKEY_DYN_DATA\\"},
#endif
		{0, ""}
	};


#define	_hoops_HPHAGR		HKEY_LOCAL_MACHINE
#define	_hoops_IPHAGR				"Software\\Tech Soft 3D\\HOOPS_3DGS"

#define	_hoops_CPHAGR			HKEY_CURRENT_USER
#define	_hoops_SPHAGR				"HOOPS"


#define _hoops_GHHAGR(string)	\
			Sprintf_SD (string, "%s_%d", _hoops_IPHAGR, \
						HOOPS_VERSION / 100  +  ((HOOPS_VERSION % 100) < 50 ? 0 : 1));

HC_INTERFACE void HC_CDECL HC_Record_Profile_Source (
	char const *	section,
	char const *	filename) 
{
	/* _hoops_PAH'_hoops_RA _hoops_SHR _hoops_SGH _hoops_IISPP(), _hoops_GAR _hoops_SR _hoops_GHCA _hoops_HHGC _hoops_IS _hoops_HPPP _hoops_PCHC _hoops_AAP
	 * _hoops_ARPP _hoops_CGCGA _hoops_RH _hoops_SGCRP _hoops_CISPP
	 */
	if (HOOPS_WORLD)
		HI_Set_Name ("Record_Profile_Source");
	else {
		/* _hoops_AASC _hoops_SR _hoops_PAH _hoops_HGCR _hoops_SGGR _hoops_CCA _hoops_IH _hoops_HA */
		HI_Init_Internal_Data ();
		HOOPS_WORLD->_hoops_PGSCA->_hoops_RCSPP = "Record_Profile_Source";
	}

	_hoops_RRPRH *	_hoops_IRSRA = (_hoops_RRPRH alter *)HOOPS_WORLD->_hoops_SSPGI;

	if (_hoops_IRSRA == null) {
		ZALLOC (_hoops_IRSRA, _hoops_RRPRH);
		HOOPS_WORLD->_hoops_SSPGI = (void alter *)_hoops_IRSRA;
	}

	_hoops_AAHR (filename, _hoops_IRSRA->_hoops_PIRCI);

	if (_hoops_IGGPA (_hoops_IRSRA->_hoops_PIRCI, "REGISTRY")) {
		if (section == null) {
			_hoops_GHHAGR (_hoops_IRSRA->_hoops_AIRCI);
			_hoops_IRSRA->_hoops_HIRCI = _hoops_HPHAGR;
		}
		else {
			_hoops_AAHR (section, _hoops_IRSRA->_hoops_AIRCI);

			/* _hoops_HRGR _hoops_RH _hoops_GSGR _hoops_RHHAGR _hoops_CCA _hoops_GII _hoops_IIGR _hoops_RH _hoops_GRH _hoops_ARAR? */
			if (_hoops_IRSRA->_hoops_AIRCI[0] == '\\') {
				struct _hoops_APHAGR const *	_hoops_HCRHS = _hoops_PPHAGR;

				while (_hoops_HCRHS->key != 0) {
					int				len = _hoops_SSGR (_hoops_HCRHS->name);

					if (_hoops_GIIPP (_hoops_HCRHS->name, _hoops_IRSRA->_hoops_AIRCI, len)) {
						/* _hoops_RGR _hoops_GHASP _hoops_IPS _hoops_HRGR _hoops_ICIC */
						_hoops_AAHR (&_hoops_IRSRA->_hoops_AIRCI[len], _hoops_IRSRA->_hoops_AIRCI);
						_hoops_IRSRA->_hoops_HIRCI = _hoops_HCRHS->key;
						break;
					}
					++_hoops_HCRHS;
				}
			}

			/* _hoops_SHIR (_hoops_HAR _hoops_AHHAGR, _hoops_PAR _hoops_HAR _hoops_SPR _hoops_SR _hoops_ACPA/_hoops_GCGH) */
			if (_hoops_IRSRA->_hoops_HIRCI == 0)
				_hoops_IRSRA->_hoops_HIRCI = HKEY_CURRENT_USER;
		}
	}
	else {
		if (section == null)
			_hoops_AAHR (section, _hoops_SPHAGR);
		else
			_hoops_AAHR (section, _hoops_IRSRA->_hoops_AIRCI);
	}

	/* _hoops_PSP _hoops_SCPC _hoops_IS _hoops_AA _hoops_RGR, _hoops_GAR _hoops_SCH _hoops_HGIIC _hoops_SGCRP _hoops_GASCA, _hoops_PGAP _hoops_PAH _hoops_IPPRH
	 * _hoops_IH _hoops_RH _hoops_SPS _hoops_API, _hoops_PGAP _hoops_CGH _hoops_SHH _hoops_IRS _hoops_PHHAGR("_hoops_HHHAGR=...")

	 _hoops_IISPP ("_hoops_IHHAGR (_hoops_HRCRH _hoops_SASI)");

	 */
}


#define	_hoops_RRCRC				0
#define	_hoops_CHHAGR		1

#ifdef WIN64_SYSTEM
#	define	_hoops_SHHAGR		KEY_QUERY_VALUE | KEY_WOW64_64KEY
#	define	_hoops_GIHAGR		KEY_QUERY_VALUE | KEY_WOW64_32KEY
#else
#	define	_hoops_SHHAGR		KEY_QUERY_VALUE | KEY_WOW64_32KEY
#	define	_hoops_GIHAGR		KEY_QUERY_VALUE | KEY_WOW64_64KEY
#endif

GLOBAL_FUNCTION bool HI_Show_Environment (
	char const		*which,
	_hoops_HCRPR alter	*result) {				   
#if !defined(_WIN32_WCE) && !defined(_hoops_GGHSH)
	char			_hoops_RIHAGR[512];
	int				status = _hoops_RRCRC;
	DWORD			length;

	length = GetEnvironmentVariable (which, _hoops_RIHAGR, sizeof (_hoops_RIHAGR));

	if (length == 0) {
		_hoops_RRPRH const	*_hoops_IRSRA;

		_hoops_IRSRA = (_hoops_RRPRH alter *)HOOPS_WORLD->_hoops_SSPGI;

		if (_hoops_IGGPA (_hoops_IRSRA->_hoops_PIRCI, "REGISTRY")) {
			char			_hoops_AIHAGR[512];
			HKEY			_hoops_PIHAGR;
			DWORD			type;

			_hoops_GHHAGR (_hoops_AIHAGR);

			// _hoops_SRS _hoops_HPPR _hoops_GII _hoops_IPSP-_hoops_CHIA _hoops_CCAC, _hoops_PAR _hoops_RH [_hoops_SHIR] _hoops_CSPP-_hoops_SASI _hoops_CCAC
			if (RegOpenKeyEx (_hoops_IRSRA->_hoops_HIRCI, _hoops_IRSRA->_hoops_AIRCI, 0L, _hoops_SHHAGR, &_hoops_PIHAGR) == ERROR_SUCCESS) {}
			else if (RegOpenKeyEx (_hoops_IRSRA->_hoops_HIRCI, _hoops_IRSRA->_hoops_AIRCI, 0L, _hoops_GIHAGR, &_hoops_PIHAGR) == ERROR_SUCCESS) {}
			else if (_hoops_IRSRA->_hoops_HIRCI != _hoops_HPHAGR || !_hoops_AGGR (_hoops_IRSRA->_hoops_AIRCI, _hoops_AIHAGR)) {
				// _hoops_IPSP-_hoops_ARSAR _hoops_ACAGR _hoops_HAR _hoops_GSGI
				status = _hoops_CHHAGR;
			}
			// _hoops_SCH _hoops_CSAP _hoops_RH _hoops_SHIR _hoops_IRISR _hoops_ACAGR, _hoops_HA _hoops_HPPR _hoops_SIHH _hoops_RH _hoops_CSPP
			else if (RegOpenKeyEx (_hoops_HPHAGR, _hoops_IPHAGR, 0L, _hoops_SHHAGR, &_hoops_PIHAGR) == ERROR_SUCCESS) {}
			else if (RegOpenKeyEx (_hoops_HPHAGR, _hoops_IPHAGR, 0L, _hoops_GIHAGR, &_hoops_PIHAGR) == ERROR_SUCCESS) {}
			// _hoops_PPR _hoops_RPP _hoops_HGGC _hoops_PSP _hoops_RIRA _hoops_HPPR _hoops_RH _hoops_RHGS _hoops_HIHAGR/_hoops_AGAH _hoops_GCCPI
			else if (RegOpenKeyEx (_hoops_CPHAGR, _hoops_SPHAGR, 0L, _hoops_SHHAGR, &_hoops_PIHAGR) == ERROR_SUCCESS) {}
			else if (RegOpenKeyEx (_hoops_CPHAGR, _hoops_SPHAGR, 0L, _hoops_GIHAGR, &_hoops_PIHAGR) == ERROR_SUCCESS) {}
			// _hoops_ICCAR _hoops_PRAR...
			else
				status = _hoops_CHHAGR;

			if (status == _hoops_RRCRC) {	// _hoops_GSGI _hoops_HHH _hoops_CCAC _hoops_SGS _hoops_APSH _hoops_GHACA
				length = sizeof (_hoops_RIHAGR);
				if (RegQueryValueEx (_hoops_PIHAGR, which, NULL, &type, (LPBYTE)_hoops_RIHAGR, &length) != ERROR_SUCCESS)
					length = 0;		// _hoops_IIHAGR _hoops_CIHAGR

				RegCloseKey (_hoops_PIHAGR);
			}
		}
		else {
			length = GetPrivateProfileString (_hoops_IRSRA->_hoops_AIRCI, which, "",
											  _hoops_RIHAGR, sizeof (_hoops_RIHAGR),
											  _hoops_IRSRA->_hoops_PIRCI);
		}
	}

	if (length == 0)
		return false;
	else {
		HI_Copy_Chars_To_Name (_hoops_RIHAGR, result);
		return true;
	}
#else
		return false;
#endif
}




typedef struct {
	char const * const	*msgv;
	int					msgc;
	int					severity;
	int					category;
	int					specific;
	char const * const	*_hoops_PRSAH;
	int					_hoops_HRSAH;
	bool			_hoops_SIHAGR;
} _hoops_GCHAGR;

#define ID_MESSAGE_AREA			1003	/* ? */
#define ID_SUPPRESS_ALL_CHECK	1004	/* ? */
#define ID_SUPPRESS_ONE_CHECK	1005	/* ? */

local bool		_hoops_RCHAGR, _hoops_ACHAGR;


/*
 * _hoops_HGI _hoops_RIHH _hoops_GPSRR _hoops_PCPH _hoops_PIGS _hoops_PCHAGR, _hoops_HPP _hoops_PSCSR
 */
local BOOL APIENTRY _hoops_HCHAGR (
	HWND					handle_dialog,
	UINT					message,
	WPARAM					word_param,
	LPARAM					long_param) {

	switch (message) {
		case WM_INITDIALOG: {
			_hoops_GCHAGR const *	info = (_hoops_GCHAGR const *)long_param;
			int					ii;
			char				temp[MAX_ERRMSG];
			char				buf[MAX_ERRMSG];
			char const *		_hoops_ICHAGR = null;

			/*
			 * _hoops_HHRRH _hoops_IIGR _hoops_IRS "_hoops_CAGRH" _hoops_GGR _hoops_SPHGR 95 _hoops_SR _hoops_HS _hoops_IS _hoops_ARP _hoops_RH _hoops_HCGR _hoops_ARI
			 * _hoops_HRII _hoops_HSAR _hoops_GGR _hoops_RH _hoops_CCHAGR _hoops_GAR _hoops_RHAC _hoops_CHH _hoops_ACRR
			 */
			SendDlgItemMessage (handle_dialog, IDOK,
								WM_SETTEXT, 0, (LPARAM) "OK");

			/* _hoops_ARP _hoops_RRGAH _hoops_IIHA _hoops_GPP _hoops_RGGHP */
			switch (info->severity) {
				case 0: {
					_hoops_AAHR (" HOOPS Informational message ", temp);
					_hoops_ICHAGR = "Suppress informational messages";
				}	break;

				case 1: {
					_hoops_AAHR (" HOOPS Warning ", temp);
					_hoops_ICHAGR = "Suppress all warnings";
				}	break;

				case 2: {
					_hoops_AAHR (" HOOPS Error ", temp);
					_hoops_ICHAGR = "Suppress all errors";
				}	break;

				case 3: {
					_hoops_AAHR (" HOOPS Fatal Error ", temp);
				}	break;

				default: {
					_hoops_AAHR (" HOOPS Unknown Error ", temp);
				}
			}

			if (info->_hoops_SIHAGR) {
				SendDlgItemMessage (handle_dialog, ID_SUPPRESS_ALL_CHECK,
									WM_SETTEXT, 0, (LPARAM) _hoops_ICHAGR);
				SendDlgItemMessage (handle_dialog, ID_SUPPRESS_ONE_CHECK,
									WM_SETTEXT, 0, (LPARAM) "Suppress this message");
				if (_hoops_ACHAGR)
					SendDlgItemMessage (handle_dialog, ID_SUPPRESS_ONE_CHECK, BM_SETCHECK, BST_CHECKED, 0); 
			}

			SetWindowText (handle_dialog, temp);

			_hoops_AAHR ("", buf);

			for (ii = 0; ii < info->msgc + info->_hoops_HRSAH + 1; ii++)
				_hoops_HPRPR (" \r\n", buf);

			SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA,WM_SETTEXT, 0, (LPARAM) buf);

			switch (info->severity) {
				case 0: {
					Sprintf_DD (temp,
						"Informational message (%d/%d) from HOOPS routine ",
						info->category, info->specific);
				}	break;

				case 1: {
					Sprintf_DD (temp,
						"Warning (%d/%d) from HOOPS routine ",
						info->category, info->specific);
				}	break;

				case 2: {
					Sprintf_DD (temp,
						"Error message (%d/%d) from HOOPS routine ",
						info->category, info->specific);
				}	break;

				case 3: {
					Sprintf_DD (temp,
						"Fatal Error (%d/%d) from HOOPS routine ",
						info->category, info->specific);
				}
			}

			/* _hoops_PISPR _hoops_HCR _hoops_APGR _hoops_CRGR _hoops_IHCGP _hoops_AHCRR */
			for (ii = info->msgc; ii > 0; ii--) {
				SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA,
									EM_SETSEL, (ii + info->_hoops_HRSAH) * 3, (LONG)((ii + info->_hoops_HRSAH) * 3));
				SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA,
									EM_REPLACESEL, 0,
									(LPARAM)info->msgv[ii - 1]);
			}

			_hoops_AAHR ("\r\n", buf);

			SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA,
								EM_SETSEL, info->_hoops_HRSAH * 3,
								(LPARAM)info->_hoops_HRSAH * 3);
			SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA,
								EM_REPLACESEL, 0, (LPARAM) buf);

			_hoops_AAHR ("", buf);

			if (info->_hoops_HRSAH != 0)
			{
				for (ii = info->_hoops_HRSAH - 1; ii > 0; ii--)		
				{
					SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA,
									EM_SETSEL, ii * 3, (LPARAM)(ii * 3));
									Sprintf_S (buf,
											   "	which was called from \'%s\' -",
												info->_hoops_PRSAH[info->_hoops_HRSAH - 1 -ii]);

					SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA,
									EM_REPLACESEL, 0, (LPARAM)buf);
				}
				Sprintf_SS (buf,
						"%s \'%s\'",
						temp, info->_hoops_PRSAH[info->_hoops_HRSAH - 1]);
				SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA, EM_SETSEL, 0, (LPARAM) 0);
				SendDlgItemMessage (handle_dialog, ID_MESSAGE_AREA, EM_REPLACESEL, 0, (LPARAM) buf);
			}

			return TRUE;
		}

		case WM_COMMAND: {
			switch (word_param) {
				case IDOK:
				case IDIGNORE:
				case IDABORT: {
					EndDialog (handle_dialog, word_param);
					return TRUE;
				}

				case ID_SUPPRESS_ALL_CHECK: {
					_hoops_RCHAGR = !_hoops_RCHAGR;
					return FALSE;
				}

				case ID_SUPPRESS_ONE_CHECK: {
					_hoops_ACHAGR = !_hoops_ACHAGR;
					return FALSE;
				}

				default: {
					return FALSE;
				}
			}
		}

		default: {
			return FALSE;
		}
	}
}


/*
 * _hoops_HAPI _hoops_HRGR _hoops_RH _hoops_CGGAR _hoops_IIGR _hoops_RHRGP _hoops_AHCRR _hoops_SGS _hoops_SAGGR _hoops_SPIP. _hoops_HHIGR _hoops_SSCP:
 *	 (1) _hoops_IRS _hoops_CRSAI _hoops_SGS _hoops_SIGH _hoops_RH _hoops_RGGHP _hoops_IIGR _hoops_RH _hoops_GPSRR
 *	 (2) _hoops_IRS _hoops_GPSRR _hoops_SGS _hoops_SCHAGR _hoops_RH _hoops_RGGHP, _hoops_CSHGR _hoops_PHI, _hoops_GSHAGR
 *		 _hoops_PHI, _hoops_AASA _hoops_HPSRR, _hoops_PPR _hoops_HCGR _hoops_IIGR _hoops_RH _hoops_GPSRR
 *	 (3) _hoops_IRGGA _hoops_PPR _hoops_IRPHR _hoops_ARGAH _hoops_CRGAH
 *	 (4) _hoops_PCIPC "_hoops_GPRS" _hoops_IS _hoops_SAS _hoops_CHSAP
 *
 *	+------------------------------------------------------------------------+
 *	|							  _hoops_AGAH _hoops_IGHHH								 |
 *	+------------------------------------------------------------------------+
 *	|																		 |
 *	|  +-----------------------------------------------------------------+-+ |
 *	|  |_hoops_IGHHH (60/203) _hoops_HII _hoops_AGAH _hoops_PCPH '_hoops_IRISR _hoops_RSHAGR (_hoops_SGCRP)' - | | |
 *	|  |	_hoops_PGAP _hoops_CSAP _hoops_PIGS _hoops_HII '_hoops_ASHAGR' -						 | | |
 *	|  |																 | | |
 *	|  |_hoops_PSHAGR _hoops_AGAH _hoops_HSHAGR _hoops_HCSP _hoops_SSCP _hoops_RPII _hoops_ARP _hoops_RHIR _hoops_RH _hoops_SGH		 | | |
 *	|  |_hoops_IIGR _hoops_RH _hoops_ISHAGR _hoops_RHI _hoops_PSGR.	_hoops_HGI _hoops_SPAHR _hoops_IH		 | | |
 *	|  |_hoops_RGSR _hoops_RH _hoops_HSHAGR _hoops_HCSP _hoops_HRGR _hoops_CSHAGR _hoops_CGAPR _hoops_IH _hoops_SGCRP		 | | |
 *	|  |_hoops_CCRPR _hoops_SSHAGR.  _hoops_HSRR _hoops_GGIAGR _hoops_IIGR _hoops_GII _hoops_CCRPR	 | | |
 *	|  |_hoops_GRP _hoops_AGAH, _hoops_RHAC _hoops_RGCA _hoops_ARP _hoops_RH _hoops_HSHAGR _hoops_HCSP _hoops_GRP _hoops_RH		 | | |
 *	|  |_hoops_PHHAGR _hoops_AGAH _hoops_API, _hoops_PPR _hoops_ASAI _hoops_CCA _hoops_GII			 | | |
 *	|  |_hoops_RHI _hoops_CCPAR.	_hoops_PSHAGR _hoops_AGAH _hoops_HSHAGR _hoops_RGIAGR			 | | |
 *	|  |_hoops_PRARH _hoops_AGIAGR _hoops_RHAC _hoops_HII _hoops_PGIAGR _hoops_GGGPR _hoops_AGAH _hoops_HSHAGR		 | | |
 *	|  |_hoops_CRGIA _hoops_IS _hoops_HRCC _hoops_SIPP _hoops_RH _hoops_CPSRR _hoops_IIGR _hoops_RH _hoops_GIGR _hoops_RGIAGR.		 | | |
 *	|  |_hoops_HSRR _hoops_RRI _hoops_HPHS, _hoops_IPHIA _hoops_SHPAA _hoops_HGIAGR _hoops_IGIAGR _hoops_CGIAGR _hoops_HPGR			 +-+ |
 *	|  |1-510-434-7630.													 |_hoops_HPPC| |
 *	|  +-----------------------------------------------------------------+-+ |
 *	|  |																 |>| |
 *	|  +-----------------------------------------------------------------+-+ |
 *	|  [] _hoops_SGIAGR _hoops_GRIAGR _hoops_IIGR _hoops_RGR _hoops_GPSRR  [] _hoops_SGIAGR _hoops_GASAR _hoops_AHGSR	 |
 *	|							   +----+									 |
 *	|							   | _hoops_GPRS |									 |
 *	|							   +----+									 |
 *	+------------------------------------------------------------------------+
 */

#define	DIALOG_DATA_SIZE	sizeof(DLGTEMPLATE) + 13*sizeof(short) + \
							4 * (sizeof(DLGITEMTEMPLATE) + 5*sizeof(short))

HC_INTERFACE void HC_CDECL HC_Report_Error (
	int						category,
	int						specific,
	int						severity,
	int						msgc,
	char const * const *	msgv,
	int						_hoops_HRSAH,
	char const * const *	_hoops_PRSAH) 
{
	// _hoops_RRI _hoops_PICP _hoops_HSAR _hoops_GSSR _hoops_HRGR _hoops_RGHP _hoops_ARI _hoops_PGGA _hoops_PPSAH _hoops_PAH _hoops_SHH 
	// _hoops_GRGA _hoops_PIGS _hoops_RHSP _hoops_HIGGP _hoops_CISPP

	/* _hoops_PAH'_hoops_RA _hoops_SHR _hoops_SGH _hoops_IISPP(), _hoops_GAR _hoops_SR _hoops_GHCA _hoops_HHGC _hoops_IS _hoops_HPPP _hoops_PCHC _hoops_AAP
	 * _hoops_ARPP _hoops_CGCGA _hoops_RH _hoops_SGCRP _hoops_CISPP
	 */
	if (HOOPS_WORLD)
		HI_Set_Name ("Report_Error");
	else {
		/* _hoops_AASC _hoops_SR _hoops_PAH _hoops_HGCR _hoops_SGGR _hoops_CCA _hoops_IH _hoops_HA */
		HI_Init_Internal_Data ();
		HOOPS_WORLD->_hoops_PGSCA->_hoops_RCSPP = "Report_Error";
	}

	_hoops_RRPRH *		_hoops_IRSRA = (_hoops_RRPRH *) HOOPS_WORLD->_hoops_SSPGI;
	_hoops_CPSPP **	_hoops_ASRGR = HI_Lookup_Error_Control (&HOOPS_WORLD->_hoops_PSSPP[severity], category, specific);

	if (_hoops_IRSRA != null) {
		if (_hoops_IRSRA->_hoops_CGACI)
			return;

		_hoops_IRSRA->_hoops_CGACI = true;
	}

#ifndef _WIN32_WCE

	// _hoops_HHH _hoops_IIGR _hoops_RGR _hoops_HRGR _hoops_CPHR _hoops_IGH _hoops_SR _hoops_AA _hoops_IRS _hoops_RHRGP _hoops_PAR _hoops_HAR
	_hoops_RCHAGR = false;	// _hoops_HSPP _hoops_PSAP, _hoops_GIARC _hoops_GRR _hoops_PCIPC
	_hoops_ACHAGR = false;	// _hoops_HSPP _hoops_PSAP (_hoops_GPP _hoops_RPP "_hoops_PSIIR _hoops_ARR"), _hoops_GIARC _hoops_GRR _hoops_PCIPC
	if (_hoops_ASRGR && *_hoops_ASRGR && (*_hoops_ASRGR)->state == _hoops_ACCPP)
		_hoops_ACHAGR = true;


	if (!BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP) && !BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_IGHGI)) {
		_hoops_GCHAGR				info;
		char					_hoops_RRIAGR[DIALOG_DATA_SIZE];
		DLGTEMPLATE *			_hoops_ARIAGR;
		DLGITEMTEMPLATE *		_hoops_PRIAGR;
		LPWORD					_hoops_HRIAGR;
		HDC						_hoops_PGICI;
		int						_hoops_IRIAGR,
								_hoops_CRIAGR;
		LONG					_hoops_SRIAGR;
		int						_hoops_GAIAGR, _hoops_RGCSR;
		int						_hoops_RAIAGR, _hoops_AAIAGR;
		int						_hoops_PAIAGR, _hoops_HAIAGR;
		int						error;
		bool					_hoops_IAIAGR;

		/* _hoops_SR _hoops_PAH _hoops_ASSS _hoops_IPPS _hoops_RPP _hoops_HAR _hoops_GGHGI & _hoops_HAR _hoops_SRSAH */
		_hoops_IAIAGR = severity <= 2 && !BIT (HOOPS_WORLD->error_mask, 1<<8);

		/*
		 * _hoops_PS _hoops_RRP _hoops_IS _hoops_GRAS _hoops_RH _hoops_IGIR _hoops_PPR _hoops_CAIAGR
		 * _hoops_IIGR _hoops_RH _hoops_RIHH _hoops_AHCRR _hoops_IIHA _hoops_GPP _hoops_HHH _hoops_GHARR _hoops_HPHS
		 * _hoops_CPGP _hoops_SR _hoops_CHR _hoops_GGR _hoops_RH _hoops_RIHH _hoops_PCPH _hoops_SR _hoops_CGH _hoops_HAR
		 * _hoops_HRAR _hoops_GPP _hoops_RH _hoops_GCSS _hoops_HPHS
		 */

		_hoops_PGICI = GetDC (GetDesktopWindow());
		_hoops_IRIAGR = GetDeviceCaps (_hoops_PGICI, HORZRES);
		_hoops_CRIAGR = GetDeviceCaps (_hoops_PGICI, VERTRES);
		ReleaseDC (GetDesktopWindow(), _hoops_PGICI);

		_hoops_SRIAGR = GetDialogBaseUnits ();
		_hoops_GAIAGR = LOWORD (_hoops_SRIAGR);
		_hoops_RGCSR = HIWORD (_hoops_SRIAGR);

		/* _hoops_HHH _hoops_PHIGR _hoops_PGRR _hoops_SR _hoops_PAH _hoops_SGH _hoops_IH _hoops_CGRPR _hoops_GGR _hoops_GSGCC & _hoops_RIHCR */
		_hoops_RAIAGR = _hoops_IRIAGR * 4 / _hoops_GAIAGR;
		_hoops_AAIAGR = _hoops_CRIAGR * 8 / _hoops_RGCSR;
		_hoops_PAIAGR = _hoops_RAIAGR / 2;
		_hoops_HAIAGR = _hoops_AAIAGR / 2;


		/* _hoops_CSCS _hoops_RHRGP */
		_hoops_ARIAGR = (DLGTEMPLATE *)_hoops_RRIAGR;

		_hoops_ARIAGR->style = WS_POPUP | WS_BORDER | WS_VISIBLE | DS_SETFONT |
								 WS_CAPTION | DS_MODALFRAME | DS_SETFOREGROUND;
		_hoops_ARIAGR->dwExtendedStyle = WS_EX_DLGMODALFRAME;
		_hoops_ARIAGR->cdit = 2;
		_hoops_ARIAGR->x = _hoops_RAIAGR / 4;
		_hoops_ARIAGR->y = _hoops_AAIAGR / 4;
		_hoops_ARIAGR->cx = _hoops_PAIAGR;
		_hoops_ARIAGR->cy = _hoops_HAIAGR;
		_hoops_HRIAGR = (LPWORD)(_hoops_ARIAGR + 1);
		/* _hoops_PS _hoops_CHR _hoops_HA _hoops_PHPC _hoops_HPGR _hoops_RH "_hoops_IHH" _hoops_CCAC _hoops_IH _hoops_RGR _hoops_IGCI */
		*_hoops_HRIAGR++ = 0x0000;		/* _hoops_CSH _hoops_PAACI */
		*_hoops_HRIAGR++ = 0x0000;		/* _hoops_HHRCP _hoops_SAIAGR _hoops_HPHP _hoops_ISHGR */
		*_hoops_HRIAGR++ = 0x0000;		/* _hoops_CSH _hoops_HPSCP */
		*_hoops_HRIAGR++ = 8;
		wcscpy((wchar_t *)_hoops_HRIAGR, (const wchar_t *) L"FixedSys");
		_hoops_HRIAGR += 9;


		/* _hoops_GPRS _hoops_CHSAP */
		_hoops_PRIAGR = (DLGITEMTEMPLATE *) _hoops_HRIAGR;
		_hoops_PRIAGR->style = BS_DEFPUSHBUTTON | WS_VISIBLE |
									  WS_CHILD | WS_TABSTOP;
		_hoops_PRIAGR->dwExtendedStyle = 0;
		_hoops_PRIAGR->x = _hoops_PAIAGR / 2 - 25;
		_hoops_PRIAGR->y = _hoops_HAIAGR - 20;
		_hoops_PRIAGR->cx = 50;
		_hoops_PRIAGR->cy = 14;
		_hoops_PRIAGR->id = IDOK;
		_hoops_HRIAGR = (LPWORD)(_hoops_PRIAGR + 1);
		/* _hoops_PS _hoops_CHR _hoops_HA _hoops_PHPC _hoops_HPGR _hoops_RH "_hoops_IHH" _hoops_CCAC _hoops_IH _hoops_RGR _hoops_IGCI */
		*_hoops_HRIAGR++ = 0xFFFF;		/* _hoops_HHRCP _hoops_RPPS _hoops_GPRR _hoops_SPS */
		*_hoops_HRIAGR++ = 0x0080;		/* _hoops_HAHPH _hoops_RPPS _hoops_IAHA */
		*_hoops_HRIAGR++ = 0x0000;		/* _hoops_CSH _hoops_HPSCP */
		/* _hoops_GPIAGR _hoops_HPHS - _hoops_IGI _hoops_GGR ._hoops_AAPC */
		*_hoops_HRIAGR++ = 0;
		*_hoops_HRIAGR++ = 0x0000;		/* _hoops_ARRP _hoops_SHS */


		/* _hoops_GPSRR _hoops_HCGR _hoops_CCAC */
		_hoops_PRIAGR = (DLGITEMTEMPLATE *) _hoops_HRIAGR;
		_hoops_PRIAGR->style = ES_MULTILINE | ES_AUTOVSCROLL |
									  ES_AUTOHSCROLL | ES_READONLY |
									  WS_VISIBLE | WS_CHILD | WS_TABSTOP |
									  WS_BORDER | WS_VSCROLL | WS_HSCROLL;
		_hoops_PRIAGR->dwExtendedStyle = 0;
		_hoops_PRIAGR->x = 8;
		_hoops_PRIAGR->y = 8;
		_hoops_PRIAGR->cx = _hoops_RAIAGR / 2 - 16;
		_hoops_PRIAGR->cy = _hoops_AAIAGR / 2 - 28 - (_hoops_IAIAGR ? 24 : 14);
		_hoops_PRIAGR->id = ID_MESSAGE_AREA;
		_hoops_HRIAGR = (LPWORD)(_hoops_PRIAGR + 1);
		/* _hoops_PS _hoops_CHR _hoops_HA _hoops_PHPC _hoops_HPGR _hoops_RH "_hoops_IHH" _hoops_CCAC _hoops_IH _hoops_RGR _hoops_IGCI */
		*_hoops_HRIAGR++ = 0xFFFF;		/* _hoops_HHRCP _hoops_RPPS _hoops_GPRR _hoops_SPS */
		*_hoops_HRIAGR++ = 0x0081;		/* _hoops_RPIAGR _hoops_IAHA */
		*_hoops_HRIAGR++ = 0x0000;		/* _hoops_CSH _hoops_HPSCP */
		/* _hoops_GPIAGR _hoops_HPHS - _hoops_IGI _hoops_GGR ._hoops_AAPC */
		*_hoops_HRIAGR++ = 0;
		*_hoops_HRIAGR++ = 0x0000;		/* _hoops_ARRP _hoops_SHS */


		if (_hoops_IAIAGR) {
			/* _hoops_ARGH _hoops_AHCRR, _hoops_ASSI _hoops_RGR... */
			_hoops_ARIAGR->cdit++;
			_hoops_PRIAGR = (DLGITEMTEMPLATE *) _hoops_HRIAGR;
			_hoops_PRIAGR->style = BS_AUTOCHECKBOX | WS_VISIBLE |
										  WS_CHILD | WS_TABSTOP;
			_hoops_PRIAGR->dwExtendedStyle = 0;
			_hoops_PRIAGR->x = _hoops_PAIAGR / 4 - 75;
			_hoops_PRIAGR->y = _hoops_HAIAGR - 40;
			_hoops_PRIAGR->cx = 150;
			_hoops_PRIAGR->cy = 14;
			_hoops_PRIAGR->id = ID_SUPPRESS_ONE_CHECK;
			_hoops_HRIAGR = (LPWORD)(_hoops_PRIAGR + 1);
			/* _hoops_PS _hoops_CHR _hoops_HA _hoops_PHPC _hoops_HPGR _hoops_RH "_hoops_IHH" _hoops_CCAC _hoops_IH _hoops_RGR _hoops_IGCI */
			*_hoops_HRIAGR++ = 0xFFFF;	/* _hoops_HHRCP _hoops_RPPS _hoops_GPRR _hoops_SPS */
			*_hoops_HRIAGR++ = 0x0080;	/* _hoops_HAHPH _hoops_RPPS _hoops_IAHA */
			*_hoops_HRIAGR++ = 0x0000;	/* _hoops_CSH _hoops_HPSCP */
			/* _hoops_GPIAGR _hoops_HPHS - _hoops_IGI _hoops_GGR ._hoops_AAPC */
			*_hoops_HRIAGR++ = 0;
			*_hoops_HRIAGR++ = 0x0000;	/* _hoops_ARRP _hoops_SHS */

			/* _hoops_ARGH _hoops_AHCRR, _hoops_ASSI _hoops_GASAR... */
			_hoops_ARIAGR->cdit++;
			_hoops_PRIAGR = (DLGITEMTEMPLATE *) _hoops_HRIAGR;
			_hoops_PRIAGR->style = BS_AUTOCHECKBOX | WS_VISIBLE |
										  WS_CHILD | WS_TABSTOP;
			_hoops_PRIAGR->dwExtendedStyle = 0;
			_hoops_PRIAGR->x = 3 * _hoops_PAIAGR / 4 - 60;
			_hoops_PRIAGR->y = _hoops_HAIAGR - 40;
			_hoops_PRIAGR->cx = 150;
			_hoops_PRIAGR->cy = 14;
			_hoops_PRIAGR->id = ID_SUPPRESS_ALL_CHECK;
			_hoops_HRIAGR = (LPWORD)(_hoops_PRIAGR + 1);
			/* _hoops_PS _hoops_CHR _hoops_HA _hoops_PHPC _hoops_HPGR _hoops_RH "_hoops_IHH" _hoops_CCAC _hoops_IH _hoops_RGR _hoops_IGCI */
			*_hoops_HRIAGR++ = 0xFFFF;	/* _hoops_HHRCP _hoops_RPPS _hoops_GPRR _hoops_SPS */
			*_hoops_HRIAGR++ = 0x0080;	/* _hoops_HAHPH _hoops_RPPS _hoops_IAHA */
			*_hoops_HRIAGR++ = 0x0000;	/* _hoops_CSH _hoops_HPSCP */
			/* _hoops_GPIAGR _hoops_HPHS - _hoops_IGI _hoops_GGR ._hoops_AAPC */
			*_hoops_HRIAGR++ = 0;
			*_hoops_HRIAGR++ = 0x0000;	/* _hoops_ARRP _hoops_SHS */
		}

		 // _hoops_GSIH _hoops_PIH _hoops_HIS _hoops_SCH _hoops_GRS _hoops_SHH _hoops_HHPA _hoops_IS _hoops_APIAGR, _hoops_PGAP _hoops_PSCSR _hoops_HCPH, _hoops_HAR _hoops_IHHH
		info.severity = severity;
		info.category = category;
		info.specific = specific;
		info.msgv	  = msgv;
		info.msgc	  = msgc;
		info._hoops_PRSAH	  = _hoops_PRSAH;
		info._hoops_HRSAH	  = _hoops_HRSAH;
		info._hoops_SIHAGR = _hoops_IAIAGR;


		error = DialogBoxIndirectParam (_hoops_RCSRH (_hoops_HGRAH), _hoops_ARIAGR,
										GetFocus(), (DLGPROC)_hoops_HCHAGR, (LPARAM) &info);
		/* _hoops_CGP _hoops_SGS _hoops_SRSH _hoops_HAH, _hoops_SGH _hoops_IRS _hoops_SHIR _hoops_AHCRR */
		if (error == -1)
			error = MessageBox (GetFocus (), *msgv, "Alert From HOOPS",
								MB_OKCANCEL | MB_APPLMODAL);
		if (error == IDABORT)
			HI_Exit_Program ();
	}
	else {
		int i;
		OutputDebugString ("**** Alert From HOOPS ****\n");
		for (i = 0 ; i < msgc ; i++) {
			OutputDebugString ("  -- ");
			OutputDebugString (msgv[i]);
			OutputDebugString ("\n");
		}
	}

	if (_hoops_ASRGR) {
		if (_hoops_RCHAGR) {
			_hoops_CPSPP *	control;

			HOOPS_WORLD->error_mask |= 1 << severity;

			/* _hoops_HCR _hoops_PSAP _hoops_HPGR _hoops_RGR _hoops_PAPA, _hoops_HIS _hoops_HASIR _hoops_IGGA _hoops_GIAGR */
			while ((control = HOOPS_WORLD->_hoops_PSSPP[severity]) != null) {
				HOOPS_WORLD->_hoops_PSSPP[severity] = control->next;
				FREE (control, _hoops_CPSPP);
			}
		}
		else if (_hoops_ACHAGR) {
			if (*_hoops_ASRGR == null) {
				_hoops_CPSPP *	control;

				ZALLOC (control, _hoops_CPSPP);
				*_hoops_ASRGR = control;
				control->category = category;
				control->specific = specific;
				control->_hoops_GHSPP = _hoops_GCCPP;
			}

			(*_hoops_ASRGR)->state = _hoops_GCCPP;
		}
		else if (*_hoops_ASRGR != null) {
			/* _hoops_GRH _hoops_AGIR, _hoops_SHIR _hoops_ISPR _hoops_IH _hoops_IRS _hoops_RRHPC _hoops_GPSRR _hoops_CSAP _hoops_PPIAGR */
			if ((*_hoops_ASRGR)->state == _hoops_ACCPP)
				(*_hoops_ASRGR)->state = _hoops_RCCPP;	/* _hoops_CRGS _hoops_AGHP _hoops_IS _hoops_HIAP _hoops_RGR _hoops_SPR _hoops_GHIR */
		}
	}

	if (_hoops_IRSRA != null)
		_hoops_IRSRA->_hoops_CGACI = false;
#endif
}



typedef struct _hoops_HPIAGR {
	HANDLE		_hoops_IPIAGR;
	DWORD		_hoops_AHGSI;
#define FILE_FLAG_NOT_OVERLAPPED		0
	int			_hoops_CPIAGR;
	OVERLAPPED	*overlapped;
} Msw_Fileio;


/*
 * _hoops_HSRR _hoops_GII _hoops_PIRPR _hoops_GGR _hoops_RGR _hoops_RPHRA, _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_PCCP _hoops_RIHH, _hoops_ASRC _hoops_RCPP _hoops_CCA
 * _hoops_GII _hoops_RIHH _hoops_GPSRR _hoops_GGR '_hoops_PSHHH' _hoops_PPR '_hoops_HSHHH' _hoops_PGAP _hoops_CHR _hoops_PCARA'_hoops_GHGP _hoops_HPP _hoops_RH
 * _hoops_CIS _hoops_RAS _hoops_ISHHH _hoops_CAPR (_hoops_CSHHH _hoops_HPP _hoops_RH _hoops_RSIRR _hoops_IIGR _hoops_RH _hoops_RGHR _hoops_PPR _hoops_RH _hoops_III
 * _hoops_PHI)
 */
local void _hoops_SPIAGR (
	char const		*source,
	char const		*item,
	_hoops_HCRPR alter	*_hoops_GIHPR,
	DWORD			_hoops_AHGSI) {
	char alter		*_hoops_ASAPR;
	char			buffer[MAX_ERRMSG];

	_hoops_ASAPR = Sprintf_SD (buffer, source, item, _hoops_AHGSI);
	HI_Copy_Chars_To_Name (buffer, _hoops_GIHPR);
}

/*
 * _hoops_AHGHR _hoops_IRS _hoops_RGHR _hoops_RCSSA _hoops_PPR _hoops_IRS _hoops_RGHR _hoops_CCH (_hoops_SSHHH _hoops_PAR _hoops_GGIHH)
 * _hoops_RGIHH _hoops_RH _hoops_RGHR _hoops_PPR _hoops_HRS _hoops_IRS "_hoops_PHIGR" _hoops_RGHR _hoops_RGHH (_hoops_SRPC *).	 _hoops_SPIAR _hoops_RIHH
 * _hoops_GPSRR _hoops_HRGR _hoops_CRPPR _hoops_HPP _hoops_RH _hoops_API _hoops_PGAP _hoops_GGR _hoops_SGS _hoops_PGRRR _hoops_HRS '_hoops_RCPP'
 * _hoops_CGP '_hoops_AGIHH' _hoops_HRGR _hoops_IHPR, _hoops_PSCR _hoops_SCH _hoops_HRGR _hoops_GPRS _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_RGHR _hoops_CSPP
 * (_hoops_PGIHH _hoops_IAHA).	 _hoops_HHPC, _hoops_GII _hoops_APRS _hoops_CSPP _hoops_CGH _hoops_SHH _hoops_PGHPR, _hoops_PAR
 * _hoops_HGIHH _hoops_IS _hoops_IRS _hoops_IGIHH _hoops_RGHR _hoops_SGS _hoops_RHAP _hoops_HAR _hoops_GGR _hoops_IIGR _hoops_ACAS _hoops_GGHC _hoops_IRS _hoops_CCAH
 * _hoops_CSPP _hoops_PHI.
 */
GLOBAL_FUNCTION bool HI_Open_File (
	_hoops_HCRPR alter			*name,
	int						_hoops_CCHHH,
	void					**_hoops_CRIPH,
	bool				_hoops_SCHHH,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	Msw_Fileio alter		*_hoops_GHIAGR;

	UNREFERENCED (_hoops_SCHHH);

	if (name->length == 0) {
		HI_Copy_Chars_To_Name ("File name is blank at Open File", _hoops_GGHGA);
		HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
		return false;
	}
	else {
		HANDLE			_hoops_RHIAGR;
		_hoops_RRPRH	   *_hoops_IRSRA = (_hoops_RRPRH alter *)
										HOOPS_WORLD->_hoops_SSPGI;

		if (_hoops_IRSRA->_hoops_SSRRI == _hoops_GGARI || _hoops_IRSRA->_hoops_SSRRI == _hoops_RGARI ||
				(_hoops_RHIAGR = CreateEvent (NULL,	/* _hoops_PSP _hoops_PCAII */
										 TRUE,	/* _hoops_HHGAI _hoops_HIAP */
										 FALSE, /* _hoops_GRAA-_hoops_AHIAGR _hoops_PIAP */
										 NULL)) /* _hoops_PSP _hoops_RSIRR */
			== (HANDLE) NULL) {
			DWORD	_hoops_AHGSI;

			/* _hoops_PHIAGR _hoops_SRSH, _hoops_CACH _hoops_RCSC */
			_hoops_AHGSI = GetLastError ();
			if (_hoops_IRSRA->_hoops_SSRRI == _hoops_GGARI || _hoops_IRSRA->_hoops_SSRRI == _hoops_RGARI ||
				_hoops_AHGSI == ERROR_CALL_NOT_IMPLEMENTED) {
				/* _hoops_GHARR _hoops_PAH _hoops_HAR _hoops_ARPR _hoops_IRS _hoops_IISSA */
				ALLOC (_hoops_GHIAGR, Msw_Fileio);
				_hoops_GHIAGR->_hoops_IPIAGR = (HANDLE)NULL;
				_hoops_GHIAGR->_hoops_AHGSI = (DWORD)0;
				_hoops_GHIAGR->_hoops_CPIAGR = FILE_FLAG_NOT_OVERLAPPED;
				_hoops_GHIAGR->overlapped = NULL;
			}
			else {
				/* _hoops_HHH _hoops_RII _hoops_RIHH _hoops_HHIAGR _hoops_HPGP _hoops_SGP _hoops_IRS _hoops_IISSA */
				_hoops_SPIAGR ("Error creating FileIO %s - Error %d",
									"Event",
									_hoops_GGHGA,
									_hoops_AHGSI);
				HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
				return false;
			}
		}
		else {
			/* _hoops_PHIAGR _hoops_PGCSS, _hoops_HGSR _hoops_RH _hoops_IHIAGR _hoops_HRPR */
			ALLOC (_hoops_GHIAGR, Msw_Fileio);
			_hoops_GHIAGR->_hoops_IPIAGR = (HANDLE)NULL;
			_hoops_GHIAGR->_hoops_AHGSI = (DWORD)0;
			_hoops_GHIAGR->_hoops_CPIAGR = FILE_FLAG_OVERLAPPED;
			ALLOC (_hoops_GHIAGR->overlapped, OVERLAPPED);
			_hoops_GHIAGR->overlapped->hEvent = _hoops_RHIAGR;
			_hoops_GHIAGR->overlapped->Offset = 0;
			_hoops_GHIAGR->overlapped->OffsetHigh = 0;
		}

		switch (_hoops_CCHHH) {
			case FILE_For_Reading: {
				if ((_hoops_GHIAGR->_hoops_IPIAGR =
					 CreateFile (name->text,
								 GENERIC_READ,
								 FILE_SHARE_READ,
								 NULL,
								 OPEN_EXISTING,
								 FILE_ATTRIBUTE_NORMAL |
									 _hoops_GHIAGR->_hoops_CPIAGR |
									 FILE_FLAG_SEQUENTIAL_SCAN,
								 NULL)) == INVALID_HANDLE_VALUE) {
					_hoops_SPIAGR (
						"Unable to open file %s for reading - Error %d",
										name->text,
										_hoops_GGHGA,
										GetLastError ());
					HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
					if (_hoops_GHIAGR->overlapped != NULL) {
						CloseHandle (_hoops_GHIAGR->overlapped->hEvent);
						FREE (_hoops_GHIAGR->overlapped, OVERLAPPED);
					}
					FREE (_hoops_GHIAGR, Msw_Fileio);
					return false;
				}
			}	break;

			case FILE_For_Writing: {
				if ((_hoops_GHIAGR->_hoops_IPIAGR =
					 CreateFile (name->text,
								 GENERIC_WRITE,
								 FILE_SHARE_READ,
								 NULL,
								 CREATE_ALWAYS,
								 FILE_ATTRIBUTE_ARCHIVE |
								 /*_hoops_CHIAGR->_hoops_SHIAGR |*/
									 /*_hoops_GIIAGR |*/
									 FILE_FLAG_SEQUENTIAL_SCAN,
								 NULL)) == INVALID_HANDLE_VALUE) {
					_hoops_SPIAGR (
						"Unable to open file %s for writing - Error %d",
										name->text,
										_hoops_GGHGA,
										GetLastError ());
					HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
					if (_hoops_GHIAGR->overlapped != NULL) {
						CloseHandle (_hoops_GHIAGR->overlapped->hEvent);
						FREE (_hoops_GHIAGR->overlapped, OVERLAPPED);
					}
					FREE (_hoops_GHIAGR, Msw_Fileio);
					return false;
				}
			}	break;

			default: {
				HI_Copy_Chars_To_Name ("Illegal access mode at Open File",
									   _hoops_GGHGA);
				HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
				if (_hoops_GHIAGR->overlapped != NULL) {
					CloseHandle (_hoops_GHIAGR->overlapped->hEvent);
					FREE (_hoops_GHIAGR->overlapped, OVERLAPPED);
				}
				FREE (_hoops_GHIAGR, Msw_Fileio);
				return false;
			}
		}
	}

	*_hoops_CRIPH = (void *) _hoops_GHIAGR;
	return true;
}


/*
 * _hoops_SGIHH _hoops_RH _hoops_RGHR _hoops_PSHS _hoops_HPP '_hoops_GRIHH'.	 _hoops_GCAAA _hoops_RCPP _hoops_RPP _hoops_IIH _hoops_CSAP
 * _hoops_GII _hoops_RIHH.
 */
GLOBAL_FUNCTION bool HI_Close_File (
	void alter				*_hoops_CRIPH,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	Msw_Fileio alter		*_hoops_GHIAGR = (Msw_Fileio alter *) _hoops_CRIPH;
	bool				result;

	/* _hoops_HPCAR _hoops_CPS _hoops_IIAH _hoops_GPRS */
	HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
	HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
	result = true;

	/* _hoops_GGGR _hoops_RH _hoops_RGHR _hoops_RGHH _hoops_PPR _hoops_PAISR _hoops_ARAPH _hoops_RPP _hoops_SCH _hoops_ISHS */
	if (!CloseHandle (_hoops_GHIAGR->_hoops_IPIAGR)) {
		_hoops_SPIAGR ("Unable to close %s - Error %d",
							"file",
							_hoops_GGHGA,
							GetLastError ());
		result = false;
	}

	/* _hoops_GSAGP _hoops_ISHP _hoops_IHIAGR _hoops_PHSPR _hoops_PPR _hoops_PAISR _hoops_ARAPH _hoops_RPP _hoops_SCH _hoops_ISHS */
	if (_hoops_GHIAGR->overlapped != NULL) {
		if (!CloseHandle (_hoops_GHIAGR->overlapped->hEvent)) {
			/*
			 * _hoops_RPP _hoops_PSHHH _hoops_CSAP _hoops_AIAH _hoops_IGI _hoops_IS _hoops_CRGS _hoops_CAPR _hoops_AHCA
			 * _hoops_RH _hoops_SRSH _hoops_GGGR _hoops_RGHH _hoops_SGHHR, _hoops_SGH _hoops_HSHHH _hoops_RIIA
			 */
			if (_hoops_GGHGA->length == 0)
				_hoops_SPIAGR ("Error destroying FileIO %s - Error %d",
									"Event",
									_hoops_GGHGA,
									GetLastError ());
			else
				_hoops_SPIAGR ("Error destroying FileIO %s - Error %d",
									"Event",
									_hoops_RGHGA,
									GetLastError ());
			result = false;
		}
		FREE (_hoops_GHIAGR->overlapped, OVERLAPPED);
	}

	/* _hoops_RIHH _hoops_PAR _hoops_PSP _hoops_RIHH, _hoops_RGHR _hoops_HAS/_hoops_GCSR _hoops_PIAP _hoops_HRGR _hoops_PSP _hoops_RPIP _hoops_SIGR */
	FREE (_hoops_GHIAGR, Msw_Fileio);

	return result;
}


/*
 *	_hoops_RRIHH _hoops_GH _hoops_IS '_hoops_ARIHH' _hoops_CRGR '_hoops_SRHR' _hoops_GRP '_hoops_GRIHH' _hoops_GAR _hoops_RH _hoops_RGHR
 *	_hoops_RGHH.	 _hoops_GCAAA # _hoops_IIGR _hoops_GCSRR _hoops_IRIGR _hoops_GGR '_hoops_PRIHH'.
 *	_hoops_HRIHH _hoops_HSAR '_hoops_ARIHH' _hoops_GHCA _hoops_SHH _hoops_IRIGR _hoops_HIH _hoops_RPP '_hoops_PRIHH' _hoops_HRGR 0, _hoops_RSGR _hoops_IIGR
 *	_hoops_RGHR _hoops_HRGR _hoops_SHHA.
 *	_hoops_RRPP _hoops_GHCA _hoops_SHH _hoops_IRIHH.  _hoops_CGP _hoops_RH _hoops_SRHR _hoops_HRGR _hoops_HAR _hoops_GAPR _hoops_APIP, _hoops_RH _hoops_API
 *	_hoops_HRS '_hoops_IHPR' _hoops_HIH '_hoops_PRIHH' _hoops_HRGR '-1'.
 */
GLOBAL_FUNCTION bool HI_Read_File_Buffer (
	void alter				*_hoops_CRIPH,
	char alter				*buffer,
	int alter				*_hoops_GSHHH,
	int						_hoops_RSHHH,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	Msw_Fileio alter		*_hoops_GHIAGR = (Msw_Fileio *) _hoops_CRIPH;
	DWORD					_hoops_RIIAGR;
	bool				result;

	if (ReadFile (_hoops_GHIAGR->_hoops_IPIAGR,
				  (LPVOID *)buffer,
				  (DWORD)_hoops_RSHHH,
				  &_hoops_RIIAGR,
				  _hoops_GHIAGR->overlapped)) {
		/* _hoops_IRIGR _hoops_ASAS _hoops_AIIAGR */
		_hoops_GHIAGR->_hoops_AHGSI = NO_ERROR;
		if (_hoops_GHIAGR->overlapped != NULL)
			_hoops_GHIAGR->overlapped->Offset += _hoops_RIIAGR;
		*_hoops_GSHHH = _hoops_RIIAGR;
		HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
		result = true;
	}
	else {
		/* _hoops_RIHH _hoops_IRAPH */
		switch (_hoops_GHIAGR->_hoops_AHGSI = GetLastError()) {
			case ERROR_IO_PENDING: {
				/* _hoops_HGI _hoops_HRGR _hoops_RH _hoops_GHARR _hoops_PRPRA _hoops_IHHH _hoops_RGR _hoops_GRS _hoops_IRAA _hoops_IRS _hoops_HPGP ... */
				*_hoops_GSHHH = -1;
				HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
				result = true;
			}	break;

			case ERROR_HANDLE_EOF: {
				*_hoops_GSHHH = 0;
				HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
				result = true;
			}	break;

			case ERROR_INVALID_HANDLE: {
				*_hoops_GSHHH = 0;
				HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
				result = true;
			}	break;

			default: {
				*_hoops_GSHHH = 0;
				_hoops_SPIAGR ("I/O Error occurred while %s - Error %d",
									"reading",
									_hoops_GGHGA,
									GetLastError ());
				result = false;
			}
		}
	}

	HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
	return result;
}



/*
 *	_hoops_CRIHH '_hoops_GCSRR' _hoops_HII '_hoops_SRHR' _hoops_GRP '_hoops_GRIHH' _hoops_GAR _hoops_RH _hoops_RGHR _hoops_RGHH.
 *	_hoops_IISH _hoops_GHCA _hoops_SHH _hoops_IRIHH.
 */
GLOBAL_FUNCTION bool HI_Write_File_Buffer (
	void alter				*_hoops_CRIPH,
	char const				*buffer,
	int						_hoops_SHGGR,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	Msw_Fileio alter		*_hoops_GHIAGR = (Msw_Fileio *) _hoops_CRIPH;
	DWORD					_hoops_RIIAGR;
	bool				result;
	int						_hoops_PIIAGR;

	_hoops_PIIAGR = WriteFile (_hoops_GHIAGR->_hoops_IPIAGR,
				   (LPVOID *)buffer,
				   (DWORD)_hoops_SHGGR,
				   &_hoops_RIIAGR,NULL);
				   /*_hoops_CHIAGR->_hoops_IHIAGR);*/
/*	  _hoops_HIIAGR (_hoops_CHIAGR->_hoops_IIIAGR);*/
	if (_hoops_PIIAGR) {

		/* _hoops_GGI _hoops_ASAS _hoops_AIIAGR */
		_hoops_GHIAGR->_hoops_AHGSI = NO_ERROR;
		/*
		_hoops_RPP (_hoops_CHIAGR->_hoops_IHIAGR != _hoops_IHHAH)
			_hoops_CHIAGR->_hoops_IHIAGR->_hoops_CIIAGR += _hoops_SIIAGR;
			*/
		HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
		result = true;
	}
	else {
		/* _hoops_RIHH _hoops_IRAPH */
		switch (_hoops_GHIAGR->_hoops_AHGSI = GetLastError()) {
			case ERROR_IO_PENDING: {
				/* _hoops_GHARR _hoops_PRPRA _hoops_IHHH _hoops_RGR _hoops_GRS _hoops_IRAA _hoops_IRS _hoops_HPGP ... */
				HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
				result = true;
			}	break;

			default: {
				_hoops_SPIAGR ("I/O Error occurred while %s - Error %d",
									"writing",
									_hoops_GGHGA,
									GetLastError ());
				result = false;
			}
		}
	}

	HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
	return result;
}


/*
 * _hoops_SRIHH _hoops_SGS _hoops_GII _hoops_PSCA _hoops_IHGS _hoops_IRIGR _hoops_CHR _hoops_IHIR _hoops_PPR _hoops_GII _hoops_IHGS
 * _hoops_PHPH _hoops_CHR _hoops_RHPA (_hoops_IH '_hoops_GRIHH')
 * _hoops_HPSHR _hoops_IRS _hoops_IRIGR _hoops_CAIH, _hoops_RPP _hoops_GCSRR _hoops_HRGR _hoops_GIIA _hoops_GAR -1, _hoops_RH _hoops_PGHC '_hoops_IRIGR'
 * _hoops_CAIH _hoops_CSAP _hoops_GAIHH _hoops_PPR _hoops_RH _hoops_SRHR _hoops_CSAP _hoops_APIP _hoops_HPGR _hoops_SGS _hoops_GHIR.	 _hoops_HHPC,
 * '_hoops_GCSRR' _hoops_HRS _hoops_RH _hoops_PHI _hoops_IIGR _hoops_GCSRR _hoops_IRIGR.
 * _hoops_IPCP _hoops_API _hoops_GGR _hoops_RGR _hoops_RPHRA _hoops_CHR _hoops_HGSAR _hoops_IH _hoops_ASRAH _hoops_IHGC _hoops_IIGR _hoops_GII
 * _hoops_PIH _hoops_SIGR _hoops_GAPA _hoops_IRIGR/_hoops_GGI _hoops_PPR _hoops_CAPRH _hoops_HCPH.	'_hoops_GRIHH' _hoops_PAH _hoops_SHH
 * _hoops_IRS _hoops_CRS _hoops_IS _hoops_IRS _hoops_HRPR _hoops_PGAP _hoops_ICGI _hoops_GII _hoops_HAHH _hoops_HPHS,
 * _hoops_PSPP _hoops_RHSP _hoops_RH '_hoops_IGS' _hoops_AASA.
 */
GLOBAL_FUNCTION bool HI_Synch_File_Buffer (
	void alter				*_hoops_CRIPH,
	int alter				*_hoops_SHGGR,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	Msw_Fileio alter		*_hoops_GHIAGR = (Msw_Fileio *) _hoops_CRIPH;
	bool				result;

	if (_hoops_GHIAGR->_hoops_AHGSI == ERROR_HANDLE_EOF ||
		_hoops_GHIAGR->_hoops_AHGSI == NO_ERROR) {
		/*
		 * _hoops_RPP _hoops_SR _hoops_CHR _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_RGHR _hoops_PAR _hoops_RH _hoops_IRIGR/_hoops_GGI _hoops_IRAPH _hoops_AIIAGR
		 * _hoops_PSCR _hoops_GCIAGR _hoops_GSSS _hoops_IRS _hoops_IHPR _hoops_PPR -1 _hoops_HRII _hoops_HSAR _hoops_RH _hoops_GCSRR _hoops_IRIGR
		 */
		*_hoops_SHGGR = -1;
		HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
		result = true;
	}
	else {		  
#ifndef _WIN32_WCE
		DWORD			_hoops_RIIAGR;
		if (GetOverlappedResult (_hoops_GHIAGR->_hoops_IPIAGR, _hoops_GHIAGR->overlapped,
								 &_hoops_RIIAGR, TRUE)) {
			_hoops_GHIAGR->overlapped->Offset += _hoops_RIIAGR;
			*_hoops_SHGGR = (int) _hoops_RIIAGR;
			HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
			result = true;
		}
		else {
			/* _hoops_RIHH _hoops_IRAPH */
			switch (GetLastError ()) {
				case ERROR_HANDLE_EOF: {
					*_hoops_SHGGR = 0;
					HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
					result = true;
				}	break;

				default: {
					_hoops_SPIAGR ("I/O Error occurred while %s - Error %d",
										"syncing",
										_hoops_GGHGA,
										GetLastError ());
					result = false;
				}
			}
		}
#endif
	}

	HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
	return result;
}


typedef struct _hoops_HIIHH {
	char				_hoops_RCIAGR[MAX_PATH];
	int					_hoops_ACIAGR;
	HANDLE				_hoops_PCIAGR;
	WIN32_FIND_DATA		find_data;
#if defined NUTCRACKER
	BOOL				_hoops_HCIAGR;
#else
	bool			_hoops_HCIAGR;
#endif
} _hoops_SIIHH;


GLOBAL_FUNCTION bool HI_Open_Directory (
	_hoops_HCRPR alter			*name,
	_hoops_HCRPR const			*filter,
	int						_hoops_IIIHH,
	int						_hoops_CIIHH,
	void alter				**_hoops_PSIHH,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	_hoops_SIIHH alter	*_hoops_HIIHH;
	DWORD					_hoops_AHGSI;
	bool				result = true;
#ifdef _WIN32_WCE
		wchar_t _hoops_RCIAGR[4096];		
		WIN32_FIND_DATA _hoops_ICIAGR;
#endif
	/* _hoops_CCPP _hoops_PPR _hoops_IHPI _hoops_PIH _hoops_IH _hoops_CHHR _hoops_HSGAR */
	 ALLOC (_hoops_HIIHH, _hoops_SIIHH);
	*_hoops_PSIHH = (void *) _hoops_HIIHH;
	_hoops_HIIHH->_hoops_RCIAGR[0] = '\0';
	_hoops_HIIHH->_hoops_ACIAGR = _hoops_IIIHH & _hoops_CIIHH;
	_hoops_HIIHH->_hoops_HCIAGR = TRUE;

	/* _hoops_ARP _hoops_GH _hoops_CRAA _hoops_RSIRR _hoops_PPR _hoops_RGHR _hoops_RSIRR _hoops_HII _hoops_GRPAR */
	if (filter->length == 0)
		if (name->text[name->length-1] == '\\')
			/* _hoops_PSP _hoops_RGHR _hoops_ACISR, _hoops_CHHR _hoops_RSIRR _hoops_HCPA _hoops_CCA _hoops_IRS \ */
			Sprintf_N (_hoops_HIIHH->_hoops_RCIAGR, "%n*.*", name);
		else
			/* _hoops_PSP _hoops_RGHR _hoops_ACISR, _hoops_CHHR _hoops_RSIRR _hoops_RHAP _hoops_HAR _hoops_RSGR _hoops_CCA _hoops_IRS \ */
			Sprintf_N (_hoops_HIIHH->_hoops_RCIAGR, "%n\\*.*", name);
	else
		if (name->text[name->length-1] == '\\')
			/* _hoops_SSCP _hoops_IRS _hoops_RGHR _hoops_ACISR, _hoops_CHHR _hoops_RSIRR _hoops_RHAP _hoops_HCPA _hoops_CCA _hoops_IRS \ */
			Sprintf_NN (_hoops_HIIHH->_hoops_RCIAGR, "%n%n", name, filter);
		else
			/* _hoops_SSCP _hoops_IRS _hoops_RGHR _hoops_ACISR, _hoops_CHHR _hoops_RSIRR _hoops_RHAP _hoops_HAR _hoops_RSGR _hoops_CCA _hoops_IRS \ */
			Sprintf_NN (_hoops_HIIHH->_hoops_RCIAGR, "%n\\%n", name, filter);

	/* _hoops_GIPHR _hoops_GRP _hoops_HCR _hoops_CSSC _hoops_PPR _hoops_RGSP _hoops_SPHR */
#ifdef _WIN32_WCE
		_hoops_CCIAGR(_hoops_RCIAGR, _hoops_HIIHH->_hoops_RCIAGR, 4096);
	_hoops_HIIHH->_hoops_PCIAGR = FindFirstFile (_hoops_RCIAGR, &_hoops_HIIHH->find_data);
#else
		_hoops_HIIHH->_hoops_PCIAGR = FindFirstFile (_hoops_HIIHH->_hoops_RCIAGR, &_hoops_HIIHH->find_data);
#endif
  
	if (_hoops_HIIHH->_hoops_PCIAGR == INVALID_HANDLE_VALUE) {
		/* _hoops_CACPR _hoops_RIHH _hoops_SSCP _hoops_IRAPH - _hoops_SSS _hoops_GGSR _hoops_PCPA */
		switch (_hoops_AHGSI = GetLastError()) {
			case ERROR_FILE_NOT_FOUND: {
				/* _hoops_PCHSI _hoops_SCIAGR _hoops_SR _hoops_HS _hoops_IS _hoops_ASRC _hoops_IHPR _hoops_ARI */
				Sprintf_N (_hoops_HIIHH->_hoops_RCIAGR, "%n", filter);
				_hoops_HIIHH->_hoops_HCIAGR = false;
				result = true;
			}	break;

			case ERROR_PATH_NOT_FOUND: {
				/* _hoops_GSIAGR _hoops_RIHH _hoops_AGIR */
				char	buffer[MAX_ERRMSG];

				Sprintf_N (buffer, "Directory open of %n failed", name);
				HI_Copy_Chars_To_Name (buffer, _hoops_GGHGA);
				HI_Copy_Chars_To_Name ("Directory does not exist", _hoops_RGHGA);
				result = false;
			}	break;

			default: {
				/* _hoops_RPRIC _hoops_RIHH */
				char	buffer[MAX_ERRMSG];

				Sprintf_N (buffer, "Directory open of %n failed", name);
				HI_Copy_Chars_To_Name (buffer, _hoops_GGHGA);
				Sprintf_D (buffer, "GetLastError returned %d", _hoops_AHGSI);
				HI_Copy_Chars_To_Name (buffer, _hoops_RGHGA);
				result = false;
			}	break;
		}
	}
	else {
		if (name->text[name->length-1] == '\\')
			/* _hoops_PSP _hoops_RGHR _hoops_ACISR, _hoops_CHHR _hoops_RSIRR _hoops_HCPA _hoops_CCA _hoops_IRS \ */
			Sprintf_N (_hoops_HIIHH->_hoops_RCIAGR, "%n", name);
		else
			/* _hoops_PSP _hoops_RGHR _hoops_ACISR, _hoops_CHHR _hoops_RSIRR _hoops_RHAP _hoops_HAR _hoops_RSGR _hoops_CCA _hoops_IRS \ */
			Sprintf_N (_hoops_HIIHH->_hoops_RCIAGR, "%n\\", name);
	}
	if (!result)
		FREE (_hoops_HIIHH, _hoops_SIIHH);

	return result;
}


GLOBAL_FUNCTION bool HI_Close_Directory (
	void alter				*_hoops_PSIHH,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	_hoops_SIIHH alter	*_hoops_HIIHH =
		(_hoops_SIIHH alter *) _hoops_PSIHH;
	bool				result = true;
	DWORD					_hoops_AHGSI;

	UNREFERENCED (_hoops_RGHGA);

	/*
	 * _hoops_HHRRH _hoops_RH _hoops_SCIHH _hoops_GSSS _hoops_IRS _hoops_IHPR
	 * _hoops_ASRC _hoops_RPP _hoops_RH _hoops_CHHR _hoops_HIH _hoops_SR _hoops_PAH _hoops_HAR
	 * _hoops_SSS _hoops_RH _hoops_RGHR _hoops_GGR _hoops_RHGHS _hoops_SR _hoops_HS _hoops_IS _hoops_PPSI _hoops_RGR _hoops_RSCA _hoops_ISPR _hoops_ARI
	 */
	if (_hoops_HIIHH->_hoops_PCIAGR != INVALID_HANDLE_VALUE &&
		!FindClose (_hoops_HIIHH->_hoops_PCIAGR)) {
		char	buffer[MAX_ERRMSG];

		_hoops_AHGSI = GetLastError();
		Sprintf_S (buffer,
				   "Directory close on %s failed",
				   _hoops_HIIHH->_hoops_RCIAGR);
		Sprintf_D (buffer, "GetLastError returned %d", _hoops_AHGSI);
		HI_Copy_Chars_To_Name (buffer, _hoops_GGHGA);
		result = false;
	}
	FREE (_hoops_HIIHH, _hoops_SIIHH);

	return result;
}


GLOBAL_FUNCTION bool HI_Read_Directory (
	void alter				*_hoops_PSIHH,
	_hoops_HCRPR alter			*filename,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	_hoops_SIIHH alter	*_hoops_HIIHH =
		(_hoops_SIIHH alter *) _hoops_PSIHH;
	DWORD					_hoops_AHGSI;
	bool				result = false;
#ifdef _WIN32_WCE
		char _hoops_RSIAGR[4096];
#endif
	/*
	 * _hoops_HHRRH _hoops_RH _hoops_SCIHH _hoops_GSSS _hoops_IRS _hoops_IHPR _hoops_ASRC
	 * _hoops_RPP _hoops_RH _hoops_CHHR _hoops_HIH _hoops_SR _hoops_PAH _hoops_HAR
	 * _hoops_SSS _hoops_RH _hoops_RGHR _hoops_GGR _hoops_RHGHS _hoops_SR _hoops_HS _hoops_IS _hoops_PPSI _hoops_RGR _hoops_RSCA _hoops_ISPR _hoops_ARI
	 */
	if (_hoops_HIIHH->_hoops_HCIAGR) {
		/* _hoops_HAPR '_hoops_ASIAGR _hoops_IRS _hoops_AHCAH _hoops_PSIAGR _hoops_AAGPR */
		do {
			/* _hoops_GSSR _hoops_AGIR */
			if (BIT (_hoops_HIIHH->_hoops_ACIAGR, DIR_Select_Writeable) &&
				BIT (_hoops_HIIHH->find_data.dwFileAttributes,
					 FILE_ATTRIBUTE_READONLY))
				/* _hoops_HSSCI _hoops_HSIAGR _hoops_RGHR _hoops_PPR _hoops_RGR _hoops_SPR _hoops_HRGR _hoops_IRIGR _hoops_RGAR */
				continue;

			if (BIT (_hoops_HIIHH->_hoops_ACIAGR, DIR_Select_Directory) &&
				BIT (_hoops_HIIHH->find_data.dwFileAttributes,
					 FILE_ATTRIBUTE_DIRECTORY))
				/* _hoops_HSSCI _hoops_IRS _hoops_CHHR _hoops_PPR _hoops_RGR _hoops_SPR _hoops_HRGR _hoops_HAR */
				continue;

			if (BIT (_hoops_HIIHH->_hoops_ACIAGR, DIR_Select_Executable) &&
				!HI_CI_Wild_Equal_Strings (_hoops_HIIHH->find_data.cFileName, "*.bat") &&
				!HI_CI_Wild_Equal_Strings (_hoops_HIIHH->find_data.cFileName, "*.cmd") &&
				!HI_CI_Wild_Equal_Strings (_hoops_HIIHH->find_data.cFileName, "*.com") &&
				!HI_CI_Wild_Equal_Strings (_hoops_HIIHH->find_data.cFileName, "*.exe") &&
				!HI_CI_Wild_Equal_Strings (_hoops_HIIHH->find_data.cFileName, "*.dll") &&
				!HI_CI_Wild_Equal_Strings (_hoops_HIIHH->find_data.cFileName, "*.hdi"))
				/* _hoops_HSSCI _hoops_PCCP _hoops_GSRPR _hoops_PPR _hoops_RGR _hoops_HRGR _hoops_HAR */
				continue;
#ifdef _WIN32_WCE
				_hoops_PASRGR(_hoops_RSIAGR, _hoops_HIIHH->find_data.cFileName, 4096); //_hoops_IRHSI  
				HI_Copy_Chars_To_Name (_hoops_RSIAGR, filename);
#else
			HI_Copy_Chars_To_Name (_hoops_HIIHH->find_data.cFileName, filename);
#endif
		  
			HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
			HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
			result = true;
		} while ((_hoops_HIIHH->_hoops_HCIAGR =
				  (FindNextFile (_hoops_HIIHH->_hoops_PCIAGR,
								 &_hoops_HIIHH->find_data) == TRUE)) != 0 &&
				 !result);
	}

	if (!result) {
		/* _hoops_HAIA _hoops_RIHH _hoops_SSCP _hoops_IRAPH */
		HI_Copy_Chars_To_Name ("", filename);
		switch (_hoops_AHGSI = GetLastError()) {
			case ERROR_FILE_NOT_FOUND: {
				char	buffer[MAX_ERRMSG];

				Sprintf_S (buffer, "File %s not found", _hoops_HIIHH->_hoops_RCIAGR);
				HI_Copy_Chars_To_Name (buffer, _hoops_GGHGA);
				result = true;
			}	break;

			case ERROR_NO_MORE_FILES: {
				/*
				 * _hoops_RSGR _hoops_IIGR _hoops_CHHR
				 * _hoops_ARP _hoops_CAIAH _hoops_IS _hoops_SPCC _hoops_IIGR 0 _hoops_PPR _hoops_GHPP _hoops_IS _hoops_IHPR
				 */
				result = true;
				HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
				HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
			}	break;

			default: {
				/* _hoops_RPRIC _hoops_RIHH */
				char	buffer[MAX_ERRMSG];

				Sprintf_S (buffer,
						   "Directory read of %s failed",
						   _hoops_HIIHH->_hoops_RCIAGR);
				HI_Copy_Chars_To_Name (buffer, _hoops_GGHGA);
				Sprintf_D (buffer,
						   "GetLastError returned %d",
						   _hoops_AHGSI);
				HI_Copy_Chars_To_Name (buffer, _hoops_RGHGA);
			}	break;
		}
	}

	return result;
}


GLOBAL_FUNCTION void HI_Set_Thread_Name (int id, char const * name, bool _hoops_RIIHH) {


	if (_hoops_RIIHH) {

#if 1
		HANDLE _hoops_ISIAGR = GetCurrentThread();

		BOOL p = SetThreadPriority(_hoops_ISIAGR, THREAD_PRIORITY_HIGHEST);
		UNREFERENCED(p);
#endif

#if 0
		HANDLE _hoops_CSIAGR = GetCurrentProcess();

		DWORD _hoops_SSIAGR;
		DWORD _hoops_GGCAGR;

		if (_hoops_RGCAGR(_hoops_CSIAGR, &_hoops_SSIAGR, &_hoops_GGCAGR)) {
			
			DWORD _hoops_AGCAGR = _hoops_SSIAGR|_hoops_GGCAGR;

			for (DWORD i = 31; i >= 0; i--) { // _hoops_GPSGR
			//_hoops_IH (_hoops_CGSRGR _hoops_HAS = 0; _hoops_HAS <= 31; _hoops_HAS++) { // _hoops_ISPP
		
				DWORD shift = (1<<i);
				DWORD _hoops_PGCAGR = _hoops_AGCAGR & shift;

				if (_hoops_PGCAGR > 0) {

					if (_hoops_HGCAGR(_hoops_ISIAGR, _hoops_PGCAGR))
						break;

				}
			}
		}

#endif
	}


//#_hoops_RPP !_hoops_PAPR( _hoops_IGCAGR )
#ifdef _hoops_IIIPA
	struct _hoops_CGCAGR {
		DWORD	type;		// _hoops_PIHA _hoops_SHH 0x1000
		LPCSTR	name;		// _hoops_CRS _hoops_IS _hoops_RSIRR (_hoops_GGR _hoops_IPSP _hoops_SGCAGR _hoops_GC)
		DWORD	_hoops_GRCAGR;	// _hoops_ISSSH _hoops_RCC (-1=_hoops_CIS _hoops_ISSSH)
		DWORD	flags;		// _hoops_HPAP _hoops_IH _hoops_SACS _hoops_SGH, _hoops_PIHA _hoops_SHH _hoops_AHHR

		_hoops_CGCAGR (DWORD id, LPCSTR string) : type (0x1000), name (string), _hoops_GRCAGR (id), flags (0) {}
	};

	_hoops_CGCAGR	info ((DWORD)id, (LPCSTR)name);

	__try {
		RaiseException (0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info);
	}
	__except(EXCEPTION_CONTINUE_EXECUTION) {}
#else
	UNREFERENCED(id);
	UNREFERENCED(name);
#endif

}




#ifdef DYNAMIC_LOADER

#ifdef HOOPS_DEBUG_BUILD
#	ifndef _hoops_RRCAGR
#		define		_hoops_RRCAGR		"d"
#	endif
#else
#	ifndef _hoops_RRCAGR
#		define		_hoops_RRCAGR		""
#	endif
#endif

#ifdef WIN64_SYSTEM
#	define		_hoops_ARCAGR		"_x64"
#else
#	define		_hoops_ARCAGR		""
#endif


GLOBAL_FUNCTION Driver_Action HD_Win32_Load_Dynamic_Driver (
	char const				*_hoops_HSS) {
	char					_hoops_PRCAGR[MAX_ERRMSG];
	HINSTANCE				_hoops_HPGGH;
	char const				*_hoops_AHPRA = "";

	/*
	 * _hoops_IPCP _hoops_CSCR _hoops_RHPP _hoops_PPR _hoops_HRCAGR _hoops_SPSIR _hoops_CHR _hoops_GRH.
	 * _hoops_RCHPR _hoops_CHR _hoops_AGPAA _hoops_CRGR _hoops_RH _hoops_AGAH _hoops_GIRPR _hoops_PPR _hoops_CHR _hoops_HAR
	 * _hoops_GIAH ._hoops_SISIH _hoops_GSIHH. _hoops_CGP _hoops_SR _hoops_AA _hoops_HAR _hoops_GRH _hoops_AGIR _hoops_CAPR,
	 * _hoops_SR _hoops_GRS _hoops_HGCR _hoops_GHARR _hoops_SSHRH _hoops_PII "_hoops_CSCR._hoops_SISIH _hoops_HAR _hoops_GSGI"
	 */

	if (_hoops_AGGR (_hoops_HSS, "image") ||
		_hoops_AGGR (_hoops_HSS, "3rdparty"))
		return (Driver_Action)nullroutine;

	if (_hoops_AGGR (_hoops_HSS, "mgl"))
		_hoops_HSS = "mgl";

	if (_hoops_AGGR (_hoops_HSS, "direct3d"))
		_hoops_HSS = "dx9";

	if (_hoops_AGGR (_hoops_HSS, "dx9"))
		_hoops_AHPRA = "_";

	if (_hoops_AGGR (_hoops_HSS, "mgl"))
		_hoops_AHPRA = "_";

	if(_hoops_AGGR(_hoops_HSS, "cgm")){
		_hoops_AHPRA = "3";
	}

	sprintf (_hoops_PRCAGR, "%s%s%d%s%s.hdi", _hoops_HSS, _hoops_AHPRA, HOOPS_VERSION, _hoops_ARCAGR, _hoops_RRCAGR);

	_hoops_HPGGH = LoadLibrary (_hoops_PRCAGR);


	if (_hoops_HPGGH == NULL)
		/*
		 * _hoops_PSP _hoops_IRCAGR - _hoops_HHS _hoops_HAR _hoops_SSS _hoops_IRS _hoops_APIP _hoops_ASCSR
		 */
		return (Driver_Action)nullroutine;
	else {
		FARPROC					_hoops_APRPR;

#ifndef _WIN32_WCE
		_hoops_APRPR = GetProcAddress (_hoops_HPGGH, "HD_Driver");
#endif
		if (_hoops_APRPR == NULL) {
			/*
			 * _hoops_CRCAGR _hoops_SR _hoops_GSGI _hoops_IRS _hoops_APIP _hoops_ASCSR, _hoops_SCH _hoops_SSAS _hoops_HAR _hoops_HS _hoops_RH
			 * _hoops_RPHR _hoops_RRPR, _hoops_HIS _hoops_CSISS _hoops_SCH _hoops_PPR _hoops_HPSI _hoops_PII _hoops_RGR _hoops_IIP
			 * _hoops_RIPRGR
			 */
			FreeLibrary (_hoops_HPGGH);
			return (Driver_Action)nullroutine;
		}
#ifdef _hoops_RHRCI
		else {
			_hoops_RRPRH				*_hoops_IRSRA;
			_hoops_AHRCI		*_hoops_SRCAGR;

			/*
			 * _hoops_AIHH _hoops_RPP _hoops_RH _hoops_GIRPR _hoops_HRGR _hoops_AIAH _hoops_GGR _hoops_SGH _hoops_HPP
			 * _hoops_HPIH _hoops_HAGAR _hoops_IIGR _hoops_RH _hoops_RHPP
			 */
			_hoops_IRSRA = (_hoops_RRPRH*)HOOPS_WORLD->_hoops_SSPGI;
			if ((_hoops_SRCAGR = _hoops_IRSRA->_hoops_CRACI) != NULL)
				do {
					if (_hoops_SRCAGR->_hoops_HPGGH == _hoops_HPGGH) {
						/*
						 * _hoops_CCCAR - _hoops_GAGPR _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RPR
						 * _hoops_HIS _hoops_SR _hoops_ACPA _hoops_CGPR _hoops_IS _hoops_CIH _hoops_ISCP _hoops_HRPR
						 */
						_hoops_SRCAGR->count++;
						return (Driver_Action)_hoops_SRCAGR->_hoops_APRPR;
					}
				} while ((_hoops_SRCAGR = _hoops_SRCAGR->next) != NULL);

			/*
			 * _hoops_SRPR _hoops_GSGI - _hoops_GGCR _hoops_RH _hoops_PIH _hoops_IH _hoops_RH _hoops_CCAH _hoops_GIRPR
			 * _hoops_HPGR _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_HIGR
			 */
			ALLOC (_hoops_SRCAGR, _hoops_AHRCI);
			_hoops_SRCAGR->_hoops_HPGGH = _hoops_HPGGH;
			_hoops_SRCAGR->_hoops_APRPR = _hoops_APRPR;
			_hoops_SRCAGR->count = 1;
			_hoops_SRCAGR->backlink = &_hoops_IRSRA->_hoops_CRACI;
			if ((_hoops_SRCAGR->next = _hoops_IRSRA->_hoops_CRACI) != NULL)
				_hoops_IRSRA->_hoops_CRACI->backlink = &_hoops_SRCAGR->next;
			_hoops_IRSRA->_hoops_CRACI = _hoops_SRCAGR;
			return (Driver_Action)_hoops_APRPR;
		}
#else 
		return (Driver_Action)_hoops_APRPR;
#endif
	}
}


GLOBAL_FUNCTION void HD_W32_UnLoad_Dynamic_Driver (
	Driver_Action		_hoops_GHRPR) {
	FARPROC					_hoops_APRPR;
	_hoops_RRPRH alter		*_hoops_IRSRA;

	/*
	 * _hoops_RCPA _hoops_SRCH _hoops_SISPR _hoops_PHIAH _hoops_SASI _hoops_PIH _hoops_GGR _hoops_GACAGR._hoops_GGHR,
	 * _hoops_SR _hoops_IIAC _hoops_RH _hoops_RHPC _hoops_IRS _hoops_RHPP _hoops_ACPH _hoops_HIS _hoops_AGAH _hoops_PAH
	 * _hoops_RIH _hoops_GPCPR _hoops_PCPA _hoops_SCH _hoops_SSCP _hoops_GGR _hoops_RGCI _hoops_CAGH _hoops_PIH
	 */
	_hoops_APRPR = (FARPROC)_hoops_GHRPR;

	/*
	 * _hoops_SGCH _hoops_GH _hoops_RH _hoops_GIRPR _hoops_IS _hoops_CIH _hoops_GRP _hoops_RH _hoops_PCPH
	 * _hoops_GAR _hoops_RH _hoops_GIPHR _hoops_AGPGC
	 */
	_hoops_IRSRA = (_hoops_RRPRH*)HOOPS_WORLD->_hoops_SSPGI;
	if (!_hoops_IRSRA)
		return;

#ifdef _hoops_RHRCI
	_hoops_AHRCI alter	*_hoops_SRCAGR;
	if ((_hoops_SRCAGR = _hoops_IRSRA->_hoops_CRACI) != NULL) do {
			if (_hoops_SRCAGR->_hoops_APRPR == _hoops_APRPR) {
				/*
				 * _hoops_RAH _hoops_RH _hoops_APSHR _hoops_RCSAR _hoops_GHIR _hoops_HIS _hoops_PSCSR _hoops_GRS
				 * _hoops_AGPI _hoops_RGCI _hoops_SGCRP _hoops_RPR
				 */
				// _hoops_ASIGA _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_SISIH _hoops_GSIHH _hoops_GA'_hoops_RA _hoops_HGCR _hoops_SHRSS _hoops_CGPR 
				// _hoops_AHSHA _hoops_CHR _hoops_HGGC _hoops_SGGHA
				//_hoops_RACAGR (_hoops_AACAGR->_hoops_GIRPR);

				/*
				 * _hoops_AIHH _hoops_RPP _hoops_SR _hoops_PAH _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_ISCP _hoops_HRPR
				 * _hoops_PGAP _hoops_IIGS _hoops_RH _hoops_SIA _hoops_HII _hoops_PCPH
				 * _hoops_IS _hoops_GIRPR
				 */
				if (--_hoops_SRCAGR->count == 0) {
					if ((*_hoops_SRCAGR->backlink = _hoops_SRCAGR->next) != NULL)
						_hoops_SRCAGR->next->backlink = _hoops_SRCAGR->backlink;
					FREE (_hoops_SRCAGR, _hoops_AHRCI);
				}
				return;
			}
		} while ((_hoops_SRCAGR = _hoops_SRCAGR->next) != NULL);
#endif

}

#endif /* _hoops_RHRPR */



#if 1

#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif
#include <wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")
//#_hoops_GCIS <_hoops_PACAGR>
//_hoops_GRP _hoops_HACAGR _hoops_IACAGR;
#include <comdef.h>

typedef struct _hoops_CACAGR {
	bool	_hoops_IA;
} _hoops_SACAGR;

THREAD_FUNCTION(_hoops_GPCAGR)
{
	HRESULT _hoops_IIRHP;
	_bstr_t _hoops_RPCAGR;
	IWbemLocator *pWbemLocator = NULL;
	IWbemServices *_hoops_APCAGR = NULL;
	IWbemClassObject *pDrive = NULL;


	_hoops_IIRHP = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	_hoops_IIRHP = CoInitializeSecurity(NULL, -1, NULL, NULL,
							  RPC_C_AUTHN_LEVEL_CONNECT,
							  RPC_C_IMP_LEVEL_IMPERSONATE,
							  NULL, EOAC_NONE, 0);

	// _hoops_CAIP'_hoops_RA _hoops_ICPPA _hoops_RPP _hoops_SR _hoops_GGHP _hoops_RH "_hoops_HAH _hoops_IAH" _hoops_RIHH, _hoops_HCR _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_CISS _hoops_GAPR.
	if (_hoops_IIRHP != RPC_E_TOO_LATE && FAILED(_hoops_IIRHP))
		goto _hoops_PRSPR;

	_hoops_IIRHP = CoCreateInstance(CLSID_WbemLocator, NULL, 
						  CLSCTX_INPROC_SERVER, IID_IWbemLocator, 
						  (void**) &pWbemLocator);

	if (FAILED(_hoops_IIRHP))
		goto _hoops_PRSPR;

	_hoops_RPCAGR = L"root\\cimv2";
	_hoops_IIRHP = pWbemLocator->ConnectServer(_hoops_RPCAGR, 
			  NULL, NULL, NULL, 0, NULL, NULL, &_hoops_APCAGR);

	if (FAILED(_hoops_IIRHP))
		goto _hoops_PRSPR;

	pWbemLocator->Release();
	pWbemLocator = NULL;

	BSTR bstrPath = SysAllocString(L"Win32_VideoController.DeviceId=\"VideoController1\"");

	// *******************************************************//
	// _hoops_HGGRI _hoops_IRS _hoops_IHIR-_hoops_HAGAR _hoops_PPCAGR.
	// *******************************************************//
	_hoops_IIRHP = _hoops_APCAGR->GetObject(bstrPath, 0,0, &pDrive, 0);

	if (FAILED(_hoops_IIRHP))
		goto _hoops_PRSPR;

	// _hoops_CPIP _hoops_RH _hoops_CARA
	BSTR  bstrDriveObj;
	_hoops_IIRHP = pDrive->GetObjectText(0, &bstrDriveObj);

	BSTR bstrProp;

	int			_hoops_HPCAGR;
	VARIANT		_hoops_IPCAGR;

	// _hoops_CPCAGR _hoops_CPPHR _hoops_IS _hoops_SGH _hoops_SPCAGR (_hoops_HAR _hoops_GHCAGR) _hoops_IS _hoops_HSPC _hoops_RHCAGR _hoops_AGRGI.
	VariantInit  (&_hoops_IPCAGR);

	bstrProp = SysAllocString(L"AdapterRAM");
	_hoops_IIRHP = pDrive->Get(bstrProp, 0, &_hoops_IPCAGR, NULL, NULL);
	if (SUCCEEDED(_hoops_IIRHP))
		_hoops_HPCAGR = _hoops_IPCAGR.intVal;
	else
		_hoops_HPCAGR = 0;
	SysFreeString (bstrProp);	

	if (_hoops_HPCAGR > 0) {

		_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);

		HOOPS_WORLD->vram_size = _hoops_HPCAGR;

		if (HOOPS_WORLD->_hoops_PHARR == 2*_hoops_AGPAGR)
			HOOPS_WORLD->_hoops_PHARR = 2*_hoops_HPCAGR;

		_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);
	}

_hoops_PRSPR:

	if (pWbemLocator != NULL)
		pWbemLocator->Release();

	if (pDrive != NULL)
		pDrive->Release();

	if (_hoops_APCAGR != NULL)
		_hoops_APCAGR->Release();

	CoUninitialize();

	UNREFERENCED(_thread_data_);

	return 0;
}

local void _hoops_HPPAGR() 
{	
	HOOPS_WORLD->vram_size = _hoops_AGPAGR;
	HOOPS_WORLD->_hoops_PHARR = 2*_hoops_AGPAGR;

	HThreadHandle _hoops_AHCAGR;

	/* _hoops_AASA _hoops_PHCAGR _hoops_API _hoops_HHCAGR _hoops_IGIRR */
	CREATE_THREAD(_hoops_AHCAGR, _hoops_GPCAGR, null);	
 }

#else

local size_t _hoops_HPPAGR(size_t * _hoops_IHCAGR)
{
	
	size_t	_hoops_CHCAGR = 512 * 1e6; /* 512 _hoops_CACS */
	size_t	_hoops_SHCAGR = 512 * 1e6; /* 512 _hoops_CACS */

	if (1) {

		HKEY					_hoops_HCPPC;
		char					_hoops_GICAGR[1024];
		char *					_hoops_AGARS = null;

		bool status = true;

		/* _hoops_SRGGR _hoops_HHPA _hoops_SRHSI _hoops_PPGS _hoops_HII _hoops_RICAGR */
		/* _hoops_RH _hoops_SRS _hoops_SRGGR _hoops_SAGGR _hoops_RH _hoops_ACAGR _hoops_GGR _hoops_RICAGR _hoops_CAS _hoops_RH _hoops_SRHSI _hoops_PPGS _hoops_HRGR _hoops_GCSS */
		if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\VIDEO", 0L,	KEY_QUERY_VALUE, &_hoops_HCPPC) 
			== ERROR_SUCCESS) {

			DWORD _hoops_AICAGR;
			_hoops_AICAGR = sizeof (_hoops_GICAGR);

			RegQueryValueEx (_hoops_HCPPC, "\\Device\\Video0", NULL, NULL, 
				(LPBYTE)_hoops_GICAGR, &_hoops_AICAGR);

			_hoops_AGARS = _hoops_CISGH("System", _hoops_GICAGR);
			RegCloseKey (_hoops_HCPPC);
		}
		else 
			status = false;
		
		/* _hoops_RH _hoops_GIAP _hoops_SRGGR _hoops_IAGA _hoops_IS _hoops_RH _hoops_ACAGR (_hoops_HII _hoops_RH _hoops_SRS _hoops_SRGGR) _hoops_PPR _hoops_SAGGR _hoops_RH _hoops_PIRA */
		if (status && RegOpenKeyEx (HKEY_LOCAL_MACHINE, _hoops_AGARS, 0L, KEY_QUERY_VALUE, &_hoops_HCPPC) 
			== ERROR_SUCCESS) {
			DWORD					_hoops_AICAGR;

			_hoops_AICAGR = sizeof (_hoops_GICAGR);

			if (status && RegQueryValueEx (_hoops_HCPPC, "HardwareInformation.MemorySize", NULL, NULL,
				(LPBYTE)_hoops_GICAGR, &_hoops_AICAGR)
				== ERROR_SUCCESS) {
				_hoops_CHCAGR = _hoops_GICAGR[3] * 16 * 1048576;
				_hoops_SHCAGR = 2 * _hoops_CHCAGR;
			}
			else
				status = false;

			RegCloseKey (_hoops_HCPPC);
		}
		else 
			status = false;

	}

	if (_hoops_IHCAGR)
		*_hoops_IHCAGR = _hoops_CHCAGR;

	return _hoops_SHCAGR;
}
#endif


#if 0
/* _hoops_HGI _hoops_HRGR _hoops_IH _hoops_GHHS _hoops_RRI _hoops_SIHC _hoops_GPP _hoops_PPGS _hoops_GGGAH _hoops_GGR _hoops_RAHRH _hoops_AAHRH.  _hoops_CICR _hoops_SHH _hoops_RCRR _hoops_SGS
   _hoops_PICAGR._hoops_GGHR _hoops_HRGR _hoops_PGPAA *_hoops_APSSA* _hoops_HICAGR _hoops_GGR _hoops_HCR _hoops_RH _hoops_GSIHH _hoops_CAS _hoops_PPGS _hoops_HRGR _hoops_PSPP/_hoops_HGGPR
   _hoops_GAR _hoops_PICAGR._hoops_GGHR _hoops_IRGAI _hoops_IICAGR, _hoops_CCRSA, _hoops_CICAGR, _hoops_SICAGR _hoops_PPR _hoops_CIH. */
#		define _hoops_IPARH
#		include <crtdbg.h>
#endif


GLOBAL_FUNCTION void * HI_System_Alloc (size_t size)
{
	return malloc(size);
}

GLOBAL_FUNCTION void HI_System_Free (void *pntr)
{
	free(pntr);
}


//#_hoops_PPIP _hoops_AHIHH
#ifdef _hoops_PHIHH
#undef WIN32_LEAN_AND_MEAN
#define _hoops_HHIHH
#define _hoops_IHIHH 1
#include "dlmalloc.c"

GLOBAL_FUNCTION void HI_Set_System_Memory_Functions()
{
	HOOPS_WORLD->_hoops_RSSPP = _hoops_CHIHH;
	HOOPS_WORLD->_hoops_GSSPP = _hoops_SHIHH;
}

#else

GLOBAL_FUNCTION void HI_Set_System_Memory_Functions()
{
	HOOPS_WORLD->_hoops_RSSPP = free;
	HOOPS_WORLD->_hoops_GSSPP = malloc;
}

#endif


#if 1
#include "Psapi.h"

GLOBAL_FUNCTION void HI_System_Memory_Purge()
{

#ifdef _hoops_PHIHH
	_hoops_GIIHH(0);
#endif

	HANDLE process = NULL;

	DWORD access = PROCESS_SET_QUOTA|PROCESS_QUERY_INFORMATION/*|_hoops_GCCAGR*/;

	if((process = OpenProcess(access, FALSE, GetCurrentProcessId())) == NULL)
		return;

	EmptyWorkingSet(process);
}
#else 
GLOBAL_FUNCTION void HI_System_Memory_Purge()
{
}
#endif


#endif /* _hoops_RCCAGR (_hoops_HIHPH) */
