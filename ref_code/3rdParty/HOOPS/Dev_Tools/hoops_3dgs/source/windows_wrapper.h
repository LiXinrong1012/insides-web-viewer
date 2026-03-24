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
 * $Id: obf_tmp.txt 1.6 2009-08-07 22:49:10 david Exp $
 */


#ifndef HOOPS_WINDOWS_WRAPPER

#ifndef NUTCRACKER
#ifdef _MSC_VER		// _hoops_RGAR _hoops_GPP _hoops_SPHGR
#	ifdef _WINDEF_	// _hoops_HIH _hoops_HAH _hoops_IAH _hoops_RPP _hoops_SPHGR._hoops_GGHR _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_PGPAA
#		error	"windows_wrapper.h  needs to be included before other headers"
#	endif


// _hoops_PSCSR._hoops_GGHR _hoops_ISCAGR _hoops_RH _hoops_HRSAR _hoops_HACAGR
// _hoops_HIS, _hoops_SRS _hoops_CSCAGR _hoops_RH _hoops_RPPCR _hoops_RIHGH _hoops_RH _hoops_HHGS
#	define	Ellipse		_hoops_GCAAGR
#	define	Polyline	_hoops_RCAAGR
#	define	Polygon		_hoops_ACAAGR
#	define	Rectangle	_hoops_PCAAGR

#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>

#	ifndef _hoops_SSAAGR		// _hoops_RPGGI _hoops_CCAH _hoops_CR _hoops_SPIHS
#		define _hoops_SSAAGR
#	endif


// _hoops_HA _hoops_CASI _hoops_GH _hoops_PPR _hoops_PPIP _hoops_RH _hoops_PIPS _hoops_PSCH _hoops_SR _hoops_GSRS _hoops_PGAP _hoops_GRS _hoops_CSCAGR _hoops_IS _hoops_RH _hoops_HPHR _hoops_ARIPR
#	undef	Ellipse
#	undef	Polyline
#	undef	Polygon
#	undef	Rectangle

#	undef	RGB
#	define	_hoops_SRASI(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

	extern "C" {
		BOOL WINAPI GDI_Polygon(_hoops_SSAAGR HDC _hoops_IIGAC, CONST POINT *_hoops_GGPAGR, _hoops_SSAAGR int _hoops_RGPAGR);
		BOOL WINAPI GDI_Polyline(_hoops_SSAAGR HDC _hoops_IIGAC, CONST POINT *_hoops_GGPAGR, _hoops_SSAAGR int _hoops_RGPAGR);
		BOOL WINAPI GDI_Ellipse( _hoops_SSAAGR HDC _hoops_IIGAC, _hoops_SSAAGR int left, _hoops_SSAAGR int top,  _hoops_SSAAGR int right, _hoops_SSAAGR int bottom);
		BOOL WINAPI GDI_Rectangle(_hoops_SSAAGR HDC _hoops_IIGAC, _hoops_SSAAGR int left, _hoops_SSAAGR int top, _hoops_SSAAGR int right, _hoops_SSAAGR int bottom);
	}


#endif	// _hoops_RCCAGR
#endif  // _hoops_IGCAGR

#define HOOPS_WINDOWS_WRAPPER
#endif

