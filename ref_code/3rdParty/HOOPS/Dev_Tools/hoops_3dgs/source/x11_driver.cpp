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
 * $Id: obf_tmp.txt 1.633 2010-12-10 03:32:35 covey Exp $
 */

#include "hoops.h"
#include "hd_proto.h"
#include "adt.h"

#ifndef X11_DRIVER

extern "C" bool HC_CDECL HD_X11_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) {
	UNREFERENCED (request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "x11");
}


extern void*
HD_Find_X11_Display(char const * const name)
{
	(void)name;
	return 0;
}

extern void
HD_Free_X11_Display(void const *display)
{
	(void)display;
}



#else

#include "database.h"
#include "driver.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "please.h"
#include "searchh.h"
#include "hversion.h"

#include "x11data.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#ifndef __cplusplus
#define c_class class
#endif


#ifdef LINUX_SYSTEM
#define caddr_t char*
#endif


#define _hoops_GRAPGR								(MOUSE_EVENTS | _hoops_RRAPGR | KEYBOARD_EVENTS)

#define _hoops_ARAPGR				0x0001	/* 1 */
#define _hoops_PRAPGR				0x0002	/* 2 */
#define _hoops_HRAPGR	0x0004	/* 4 */
#define _hoops_IRAPGR	0x0008	/* 8 */
/*		_hoops_PISH _hoops_IH _hoops_PSAIP _hoops_CRAPGR _hoops_GHGPR _hoops_RHGPR _hoops_PRGI _hoops_RPP _hoops_SRAPGR _hoops_CHR _hoops_HHPA
*/
#define _hoops_GAAPGR	0x0010	/* 16 */

#define _hoops_RAAPGR				0x0F00	/* 3840 - _hoops_PISH _hoops_IH _hoops_RH _hoops_HSPR _hoops_ICRSR */
#define _hoops_AAAPGR				0x0000	/*		  0 */
#define _hoops_PAAPGR	0x0100	/*		256 */
#define _hoops_HAAPGR				0x0200	/*		512 */
#define _hoops_IAAPGR				0x0300	/*		768 */
#define _hoops_CAAPGR				0x0400	/* 1024 */
#define _hoops_SAAPGR				0x0500	/* 1280 */
#define _hoops_GPAPGR					0x0600	/* 1536 */

/*_hoops_HPAP _hoops_IH _hoops_SACS _hoops_SGH*/
#define _hoops_PSAAH		0x00004000

/* _hoops_ARCR _hoops_PIAP _hoops_IIGR _hoops_CRGIA _hoops_IS _hoops_CHARP _hoops_IACAGR. */
#define HOOPS_ALT_MASK					0x1000	/*		4096 */
#define HOOPS_META_MASK					0x1000	/*		4096 */
#define HOOPS_SHIFT_MASK				0x2000	/*		8192 */
#define HOOPS_CTRL_MASK					0x4000	/* 16384 */

#define _hoops_RPAPGR								-1		 /* _hoops_GAR _hoops_IRS _hoops_HSGP */

#define KEYBOARD_EVENTS					(KeyPressMask | KeyReleaseMask)

#define _hoops_APAPGR								12
#define _hoops_PPAPGR								16384
#define _hoops_PGHHR					4


#define MOUSE_EVENTS					(ButtonPressMask | ButtonReleaseMask)


#if 0
#define _hoops_CIRGS
#define _hoops_HPAPGR
#define _hoops_IPAPGR
#endif

#ifdef _hoops_CIRGS
#		define _hoops_SIRGS(_hoops_RIIPC,_hoops_HIGSH) do { \
	fprintf (stderr, "X11 Sequence: %s %p\n", (_hoops_RIIPC), (void*)(_hoops_HIGSH)), fflush(stderr); \
} while (0)
#else
#		define _hoops_SIRGS(_hoops_RIIPC,_hoops_HIGSH) (void)(_hoops_RIIPC),(void)(_hoops_HIGSH)
#endif

#ifdef _hoops_HPAPGR
#		define _hoops_CPAPGR(_hoops_RIIPC, _hoops_HIGSH) do { \
	fprintf (stderr, "X11 Sequence: %s %p\n", (_hoops_RIIPC), (void*)(_hoops_HIGSH)),fflush(stderr); \
} while (0)
#else
#		define _hoops_CPAPGR(_hoops_RIIPC, _hoops_HIGSH) (void)(_hoops_RIIPC),(void)(_hoops_HIGSH)
#endif


#ifdef _hoops_IPAPGR
#		define _hoops_SPAPGR(_hoops_RIIPC,_hoops_HIGSH) do { \
	fprintf (stderr, "X11 Sequence: %s %p\n", (_hoops_RIIPC), (void*)(_hoops_HIGSH)), fflush(stderr); \
} while (0)
#else
#		define _hoops_SPAPGR(_hoops_RIIPC,_hoops_HIGSH)  (void)(_hoops_RIIPC),(void)(_hoops_HIGSH)
#endif


#define _hoops_GHAPGR(c,n)								(c |= (0x80>>(n)))
#define _hoops_RHAPGR(c,n)					(BIT((c),(0x80>>(n))))

#define _hoops_AHAPGR				0xFFFFFFFF

#define _hoops_RRAPGR					(EnterWindowMask | ExposureMask |				\
																 FocusChangeMask | LeaveWindowMask |	\
																 PointerMotionMask | StructureNotifyMask)

#define X11_CLIENT_MSB_BLUE_FIRST				0
#define X11_CLIENT_MSB_BLUE_LAST				1
#define X11_CLIENT_LSB_BLUE_FIRST				2
#define X11_CLIENT_LSB_BLUE_LAST				3

#define X11_SERVER_MSB_BLUE_FIRST				0
#define X11_SERVER_MSB_BLUE_LAST				1
#define X11_SERVER_LSB_BLUE_FIRST				2
#define X11_SERVER_LSB_BLUE_LAST				3

#define X11D(dc)				((X11Data alter *)(dc)->data)

#ifndef XK_VoidSymbol
#define XK_VoidSymbol	0xFFFFFF
#endif /* _hoops_PHAPGR */

/*
 *		_hoops_SCRAGR _hoops_SIHC _hoops_IH _hoops_GPAAC _hoops_SPHS, _hoops_GPAAC _hoops_SPHS _hoops_CHR _hoops_HHAPGR _hoops_PPR
 *		_hoops_RH _hoops_CARPC _hoops_RSIRR _hoops_HRGR _hoops_CRPPR _hoops_GAR _hoops_CGAS _hoops_HPP _hoops_ARSSA _hoops_GHCAI _hoops_RRGR.
 */
local	const	char	*_hoops_IHAPGR[128] = {
		"",																		/* 0 */
		"X_CreateWindow",										/* 1 */
		"X_ChangeWindowAttributes",						/* 2 */
		"X_GetWindowAttributes",						/* 3 */
		"X_DestroyWindow",										/* 4 */
		"X_DestroySubwindows",							/* 5 */
		"X_ChangeSaveSet",										/* 6 */
		"X_ReparentWindow",										/* 7 */
		"X_MapWindow",											/* 8 */
		"X_MapSubwindows",										/* 9 */
		"X_UnmapWindow",										/* 10 */
		"X_UnmapSubwindows",							/* 11 */
		"X_ConfigureWindow",							/* 12 */
		"X_CirculateWindow",							/* 13 */
		"X_GetGeometry",										/* 14 */
		"X_QueryTree",											/* 15 */
		"X_InternAtom",											/* 16 */
		"X_GetAtomName",										/* 17 */
		"X_ChangeProperty",										/* 18 */
		"X_DeleteProperty",										/* 19 */
		"X_GetProperty",										/* 20 */
		"X_ListProperties",										/* 21 */
		"X_SetSelectionOwner",							/* 22 */
		"X_GetSelectionOwner",							/* 23 */
		"X_ConvertSelection",							/* 24 */
		"X_SendEvent",											/* 25 */
		"X_GrabPointer",										/* 26 */
		"X_UngrabPointer",										/* 27 */
		"X_GrabButton",											/* 28 */
		"X_UngrabButton",										/* 29 */
		"X_ChangeActivePointerGrab",			/* 30 */
		"X_GrabKeyboard",										/* 31 */
		"X_UngrabKeyboard",										/* 32 */
		"X_GrabKey",											/* 33 */
		"X_UngrabKey",											/* 34 */
		"X_AllowEvents",										/* 35 */
		"X_GrabServer",											/* 36 */
		"X_UngrabServer",										/* 37 */
		"X_QueryPointer",										/* 38 */
		"X_GetMotionEvents",							/* 39 */
		"X_TranslateCoords",							/* 40 */
		"X_WarpPointer",										/* 41 */
		"X_SetInputFocus",										/* 42 */
		"X_GetInputFocus",										/* 43 */
		"X_QueryKeymap",										/* 44 */
		"X_OpenFont",											/* 45 */
		"X_CloseFont",											/* 46 */
		"X_QueryFont",											/* 47 */
		"X_QueryTextExtents",							/* 48 */
		"X_ListFonts",											/* 49 */
		"X_ListFontsWithInfo",							/* 50 */
		"X_SetFontPath",										/* 51 */
		"X_GetFontPath",										/* 52 */
		"X_CreatePixmap",										/* 53 */
		"X_FreePixmap",											/* 54 */
		"X_CreateGC",											/* 55 */
		"X_ChangeGC",											/* 56 */
		"X_CopyGC",														/* 57 */
		"X_SetDashes",											/* 58 */
		"X_SetClipRectangles",							/* 59 */
		"X_FreeGC",														/* 60 */
		"X_ClearArea",											/* 61 */
		"X_CopyArea",											/* 62 */
		"X_CopyPlane",											/* 63 */
		"X_PolyPoint",											/* 64 */
		"X_PolyLine",											/* 65 */
		"X_PolySegment",										/* 66 */
		"X_PolyRectangle",										/* 67 */
		"X_PolyArc",											/* 68 */
		"X_FillPoly",											/* 69 */
		"X_PolyFillRectangle",							/* 70 */
		"X_PolyFillArc",										/* 71 */
		"X_PutImage",											/* 72 */
		"X_GetImage",											/* 73 */
		"X_PolyText8",											/* 74 */
		"X_PolyText16",											/* 75 */
		"X_ImageText8",											/* 76 */
		"X_ImageText16",										/* 77 */
		"X_CreateColormap",										/* 78 */
		"X_FreeColormap",										/* 79 */
		"X_CopyColormapAndFree",						/* 80 */
		"X_InstallColormap",							/* 81 */
		"X_UninstallColormap",							/* 82 */
		"X_ListInstalledColormaps",						/* 83 */
		"X_AllocColor",											/* 84 */
		"X_AllocNamedColor",							/* 85 */
		"X_AllocColorCells",							/* 86 */
		"X_AllocColorPlanes",							/* 87 */
		"X_FreeColors",											/* 88 */
		"X_StoreColors",										/* 89 */
		"X_StoreNamedColor",							/* 90 */
		"X_QueryColors",										/* 91 */
		"X_LookupColor",										/* 92 */
		"X_CreateCursor",										/* 93 */
		"X_CreateGlyphCursor",							/* 94 */
		"X_FreeCursor",											/* 95 */
		"X_RecolorCursor",										/* 96 */
		"X_QueryBestSize",										/* 97 */
		"X_QueryExtension",										/* 98 */
		"X_ListExtensions",										/* 99 */
		"X_ChangeKeyboardMapping",						/* 100*/
		"X_GetKeyboardMapping",							/* 101*/
		"X_ChangeKeyboardControl",						/* 102*/
		"X_GetKeyboardControl",							/* 103*/
		"X_Bell",														/* 104*/
		"X_ChangePointerControl",						/* 105*/
		"X_GetPointerControl",							/* 106*/
		"X_SetScreenSaver",										/* 107*/
		"X_GetScreenSaver",										/* 108*/
		"X_ChangeHosts",										/* 109*/
		"X_ListHosts",											/* 110*/
		"X_SetAccessControl",							/* 111*/
		"X_SetCloseDownMode",							/* 112*/
		"X_KillClient",											/* 113*/
		"X_RotateProperties",							/* 114*/
		"X_ForceScreenSaver",							/* 115*/
		"X_SetPointerMapping",							/* 116*/
		"X_GetPointerMapping",							/* 117*/
		"X_SetModifierMapping",							/* 118*/
		"X_GetModifierMapping",							/* 119*/
		"",																		/* 120*/
		"",																		/* 121*/
		"",																		/* 122*/
		"",																		/* 123*/
		"",																		/* 124*/
		"",																		/* 125*/
		"",																		/* 126*/
		"X_NoOperation",										/* 127*/
};



/*
 *		_hoops_CHAPGR _hoops_IGI _hoops_GGR _hoops_CSSGR _hoops_GSPHR _hoops_ISHHH.  _hoops_PAGA _hoops_SGS _hoops_RH
 *		_hoops_AGR _hoops_RGCA _hoops_PSSP _hoops_RH _hoops_PAIGR _hoops_RAGA _hoops_GGR <_hoops_GPAAC/_hoops_SPCR._hoops_GGHR>.
 */
local	const	char	*_hoops_SHAPGR[6] = {
		"StaticGray",											/* 0 */
		"GrayScale",											/* 1 */
		"StaticColor",											/* 2 */
		"PseudoColor",											/* 3 */
		"TrueColor",											/* 4 */
		"DirectColor",											/* 5 */
};

#ifdef _hoops_GIAPGR
#if defined (IRIX_SYSTEM) || defined (_hoops_PPCSH) || defined (SOLARIS_SYSTEM)
				/*
				 *		_hoops_ICHHH _hoops_PSCH _hoops_IH _hoops_RH _hoops_GPAAC _hoops_GAPGGR-_hoops_RHGPR _hoops_SAIHH.
				 */
				local bool XmbufQueryExtension (
				Display			   *_hoops_HRRPC,
				int						   *_hoops_RIAPGR,
				int						   *_hoops_AIAPGR) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(_hoops_RIAPGR);
				UNREFERENCED(_hoops_AIAPGR);
				return False;
				}

				local int XmbufCreateBuffers (
				Display			   *_hoops_HRRPC,
				X_Window			   window,
				int				   count,
				int				   _hoops_PIAPGR,
				int				   _hoops_HIAPGR,
				Multibuffer				   *_hoops_IIAPGR) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(window);
				UNREFERENCED(count);
				UNREFERENCED(_hoops_PIAPGR);
				UNREFERENCED(_hoops_HIAPGR);
				UNREFERENCED(_hoops_IIAPGR);
				return 0;
				}

				local void XmbufDisplayBuffers (
				Display			   *_hoops_HRRPC,
				int				   count,
				Multibuffer				   *_hoops_AARAC,
				int				   _hoops_CIAPGR,
				int				   _hoops_SIAPGR) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(count);
				UNREFERENCED(_hoops_AARAC);
				UNREFERENCED(_hoops_CIAPGR);
				UNREFERENCED(_hoops_SIAPGR);
				return;
				}

		local void XmbufDestroyBuffers (
				Display			   *_hoops_HRRPC,
				X_Window			   window) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(window);
				return;
				}

#else /* _hoops_SSHPI || _hoops_GCAPGR || _hoops_SPPHS */

		/*
		 *		_hoops_ICHHH _hoops_PSCH _hoops_IH _hoops_RH _hoops_GPAAC _hoops_GAPGGR-_hoops_RHGPR _hoops_SAIHH.
		 */
		local bool XmbufQueryExtension (
				Display const					*_hoops_HRRPC,
				int const								*_hoops_RIAPGR,
				int const								*_hoops_AIAPGR) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(_hoops_RIAPGR);
				UNREFERENCED(_hoops_AIAPGR);
				return False;
		}

		local int XmbufCreateBuffers (
				Display const					*_hoops_HRRPC,
				X_Window									window,
				int												count,
				int												_hoops_PIAPGR,
				int												_hoops_HIAPGR,
				Multibuffer const				*_hoops_IIAPGR) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(window);
				UNREFERENCED(count);
				UNREFERENCED(_hoops_PIAPGR);
				UNREFERENCED(_hoops_HIAPGR);
				UNREFERENCED(_hoops_IIAPGR);
				return 0;
		}

		local void XmbufDisplayBuffers (
				Display const					*_hoops_HRRPC,
				int												count,
				Multibuffer const				*_hoops_AARAC,
				int												_hoops_CIAPGR,
				int												_hoops_SIAPGR) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(count);
				UNREFERENCED(_hoops_AARAC);
				UNREFERENCED(_hoops_CIAPGR);
				UNREFERENCED(_hoops_SIAPGR);
				return;
		}

		local void XmbufDestroyBuffers (
				Display const					*_hoops_HRRPC,
				X_Window									window) {

				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(window);
				return;
		}
#endif /* _hoops_SSHPI || _hoops_GCAPGR || _hoops_SPPHS */

local int XmbufGetScreenInfo(Display const *_hoops_HRRPC,
														Window window,
														int *_hoops_RCAPGR,
														int *_hoops_ACAPGR,
														int *_hoops_PCAPGR, int *_hoops_HCAPGR) {
				UNREFERENCED(_hoops_HRRPC);
				UNREFERENCED(window);
				UNREFERENCED(_hoops_RCAPGR);
				UNREFERENCED(_hoops_ACAPGR);
				UNREFERENCED(_hoops_PCAPGR);
				UNREFERENCED(_hoops_HCAPGR);
				return 0;
}


#endif /* _hoops_ICAPGR */



/****************************************************************
 ****************************************************************
												_hoops_IHRPR _hoops_ISAII _hoops_GHAP _hoops_HAICR _hoops_HAICR _hoops_GHAP _hoops_PGGIR _hoops_PHGPH
 ****************************************************************
 ****************************************************************/

#define _hoops_CCAPGR(nr, _hoops_PGPIC, _hoops_SSAC) \
		{if ((_hoops_SSAC) != (nr)->transform_rendition->_hoops_CPA) \
				_hoops_PSGAI (nr, _hoops_PGPIC, &(_hoops_SSAC));}

/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ARH _hoops_CCAH _hoops_CIHH _hoops_PRCH.
 */
local void _hoops_PSGAI (
		Net_Rendition const					&nr,
		GC									_hoops_PGPIC,
		_hoops_GARRR alter					*_hoops_SCAPGR) {
		X11Data alter									*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_HHCR const	&_hoops_IHCR = nr->transform_rendition;
		XRectangle												_hoops_GSAPGR[1];

		/* _hoops_RAP _hoops_RH _hoops_HSPH _hoops_PCSRR _hoops_IH _hoops_RH _hoops_GHGPR-_hoops_SRHR _hoops_RSAPGR _hoops_ASAPGR() _hoops_AASA */
		if (_hoops_RRRPC->_hoops_PSAPGR) {
				_hoops_RRRPC->_hoops_HSAPGR	= _hoops_AHIA (_hoops_RRRPC->_hoops_HSAPGR,	_hoops_IHCR->_hoops_AGAA.left);
				_hoops_RRRPC->_hoops_ISAPGR	= _hoops_IAAA (_hoops_RRRPC->_hoops_ISAPGR,	_hoops_IHCR->_hoops_AGAA.right);
				_hoops_RRRPC->_hoops_CSAPGR = _hoops_AHIA (_hoops_RRRPC->_hoops_CSAPGR, _hoops_IHCR->_hoops_AGAA.bottom);
				_hoops_RRRPC->_hoops_SSAPGR	= _hoops_IAAA (_hoops_RRRPC->_hoops_SSAPGR,	_hoops_IHCR->_hoops_AGAA.top);
		}

		_hoops_GSAPGR[0].x = _hoops_IHCR->_hoops_AGAA.left;
		_hoops_GSAPGR[0].y = _hoops_RRRPC->yfudge - _hoops_IHCR->_hoops_AGAA.top;
		_hoops_GSAPGR[0].width = _hoops_IHCR->_hoops_AGAA.right - _hoops_IHCR->_hoops_AGAA.left + 1;
		_hoops_GSAPGR[0].height = _hoops_IHCR->_hoops_AGAA.top - _hoops_IHCR->_hoops_AGAA.bottom + 1;


#ifdef _hoops_CIRGS
	/* _hoops_SRGAI _hoops_GGSR "_hoops_HCHAI" _hoops_HPGR _hoops_CHGC _hoops_ARR _hoops_RIR _hoops_PAAP _hoops_SSCHA/ _hoops_RHCAC'_hoops_GRI _hoops_GGR _hoops_SCH */
	if (*_hoops_SCAPGR == (_hoops_GARRR)0)
		fprintf (stderr, "X11 Sequence: DRAWING, clip is (%d x %d) @ (%d, %d) %p\n",
			 _hoops_GSAPGR[0].width, _hoops_GSAPGR[0].height, _hoops_GSAPGR[0].x, _hoops_GSAPGR[0].y, (void*)_hoops_RRRPC);
#endif

		XSetClipRectangles (_hoops_RRRPC->display, _hoops_PGPIC, 0, 0, _hoops_GSAPGR, 1, YXBanded);

		*_hoops_SCAPGR = _hoops_IHCR->_hoops_CPA;
}



/****************************************************************
 ****************************************************************
								   _hoops_IHRPR _hoops_RGGIR _hoops_ISAII _hoops_RGGIR _hoops_AHGPH	_hoops_IISGA _hoops_HRAIA _hoops_SAAAR _hoops_SAAAR _hoops_GHAP _hoops_PGGIR _hoops_PHGPH
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_PGAA **
 *
 */
local void _hoops_GGPPGR (
		Net_Rendition const & nr,
		XGCValues alter					*_hoops_RGPPGR,
		Driver_Color const	*_hoops_SHRIC,
		Driver_Color const	*_hoops_AGPPGR) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_ISC					rgb;
		int												shift = _hoops_RRRPC->_hoops_CRAPC;


		/*
		 *		_hoops_IPCP _hoops_SCPC _hoops_IH _hoops_GHGA _hoops_RH _hoops_HSPR:
		 *		_hoops_PAAS _hoops_RGSR _hoops_RH _hoops_PSHA _hoops_IH _hoops_AGRR _hoops_SGAPC _hoops_RH _hoops_PGPPGR _hoops_HAIR
		 *		_hoops_SHR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_ARP _hoops_PPR _hoops_RH _hoops_IGHP _hoops_HAIR _hoops_HRGR _hoops_RIRCP.
		 */
		{
				rgb.r = _hoops_SHRIC->_hoops_HRIR.r;
				rgb.g = _hoops_SHRIC->_hoops_HRIR.g;
				rgb.b = _hoops_SHRIC->_hoops_HRIR.b;

				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP)) {
						rgb.r ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r;
						rgb.g ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g;
						rgb.b ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.b;
				}

				if (_hoops_RRRPC->_hoops_HGPPGR)
						_hoops_RGPPGR->foreground = (_hoops_IRGCR(rgb.r) |
																((_hoops_IRGCR(rgb.g) |
																  (_hoops_IRGCR(rgb.b) << shift)) << shift));
				else
						_hoops_RGPPGR->foreground = (_hoops_IRGCR(rgb.b) |
																((_hoops_IRGCR(rgb.g) |
																  (_hoops_IRGCR(rgb.r) << shift)) << shift));
		}

		if (_hoops_AGPPGR != null) {
				rgb.r = _hoops_AGPPGR->_hoops_HRIR.r;
				rgb.g = _hoops_AGPPGR->_hoops_HRIR.g;
				rgb.b = _hoops_AGPPGR->_hoops_HRIR.b;

				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP)) {
						rgb.r ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r;
						rgb.g ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g;
						rgb.b ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.b;
				}

				if (_hoops_RRRPC->_hoops_HGPPGR)
						_hoops_RGPPGR->background = (_hoops_IRGCR(rgb.r) |
																((_hoops_IRGCR(rgb.g) |
																  (_hoops_IRGCR(rgb.b) << shift)) << shift));
				else
						_hoops_RGPPGR->background = (_hoops_IRGCR(rgb.b) |
																((_hoops_IRGCR(rgb.g) |
																  (_hoops_IRGCR(rgb.r) << shift)) << shift));
		}
}

/*
 *		** _hoops_PGAA **
 *
 */
local void _hoops_IGPPGR (
	Net_Rendition const & nr,
	XGCValues alter					*_hoops_RGPPGR,
	Driver_Color const	*_hoops_SHRIC,
	Driver_Color const	*_hoops_AGPPGR) {
	X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
	_hoops_ISC					rgb;

	{
		rgb.r = _hoops_SHRIC->_hoops_HRIR.r;
		rgb.g = _hoops_SHRIC->_hoops_HRIR.g;
		rgb.b = _hoops_SHRIC->_hoops_HRIR.b;

		if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP)) {
			rgb.r ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r;
			rgb.g ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g;
			rgb.b ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.b;
		}

		_hoops_RGPPGR->foreground =
						(((unsigned short)rgb.r >> _hoops_RRRPC->_hoops_CGPPGR) << _hoops_RRRPC->_hoops_SGPPGR) |
						(((unsigned short)rgb.g >> _hoops_RRRPC->_hoops_GRPPGR) << _hoops_RRRPC->_hoops_RRPPGR) |
						(((unsigned short)rgb.b >> _hoops_RRRPC->_hoops_ARPPGR) << _hoops_RRRPC->_hoops_PRPPGR);
	}

	if (_hoops_AGPPGR != null) {
		rgb.r = _hoops_AGPPGR->_hoops_HRIR.r;
		rgb.g = _hoops_AGPPGR->_hoops_HRIR.g;
		rgb.b = _hoops_AGPPGR->_hoops_HRIR.b;

		if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP)) {
			rgb.r ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r;
			rgb.g ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g;
			rgb.b ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.b;
		}


		_hoops_RGPPGR->background =
						(((unsigned short)rgb.r >> _hoops_RRRPC->_hoops_CGPPGR) << _hoops_RRRPC->_hoops_SGPPGR) |
						(((unsigned short)rgb.g >> _hoops_RRRPC->_hoops_GRPPGR) << _hoops_RRRPC->_hoops_RRPPGR) |
						(((unsigned short)rgb.b >> _hoops_RRRPC->_hoops_ARPPGR) << _hoops_RRRPC->_hoops_PRPPGR);
	}
}


/*
 *		** _hoops_PGAA **
 *
 */
local void _hoops_HRPPGR (
		Net_Rendition const & nr,
		XGCValues alter					*_hoops_RGPPGR,
		Driver_Color const	*_hoops_SHRIC,
		Driver_Color const	*_hoops_AGPPGR) {

		/*
		 *		_hoops_IPCP _hoops_SCPC _hoops_IH _hoops_GHGA _hoops_RH _hoops_HSPR:
		 *		_hoops_PAAS _hoops_RGSR _hoops_RH _hoops_PSHA _hoops_IH _hoops_AGRR _hoops_SGAPC _hoops_RH _hoops_PGPPGR _hoops_HAIR
		 *		_hoops_SHR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_ARP _hoops_PPR _hoops_RH _hoops_IGHP _hoops_HAIR _hoops_HRGR _hoops_RIRCP.
		 */
		{
				_hoops_RGPPGR->foreground = _hoops_SHRIC->_hoops_PIHHP;
				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP))
						_hoops_RGPPGR->foreground ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_PIHHP;
		}

		if (_hoops_AGPPGR != null) {
				_hoops_RGPPGR->background = _hoops_AGPPGR->_hoops_PIHHP;
				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP))
						_hoops_RGPPGR->background ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_PIHHP;
		}
}



/*
 *		** _hoops_PGAA **
 *
 */
local void _hoops_IRPPGR (
		Net_Rendition const & nr,
		XGCValues alter					*_hoops_RGPPGR,
		Driver_Color const	*_hoops_SHRIC,
		Driver_Color const	*_hoops_AGPPGR) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);

		/*
		 *		_hoops_IPCP _hoops_SCPC _hoops_IH _hoops_GHGA _hoops_RH _hoops_HSPR:
		 *		_hoops_PAAS _hoops_RGSR _hoops_RH _hoops_PSHA _hoops_IH _hoops_AGRR _hoops_SGAPC _hoops_RH _hoops_PGPPGR _hoops_HAIR
		 *		_hoops_SHR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_ARP _hoops_PPR _hoops_RH _hoops_IGHP _hoops_HAIR _hoops_HRGR _hoops_RIRCP.
		 */
		if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP))
				_hoops_RGPPGR->foreground = 1;
		else if (_hoops_SHRIC->_hoops_PIHHP < _hoops_AHRSP/2)
				_hoops_RGPPGR->foreground = BlackPixelOfScreen (_hoops_RRRPC->screen);
		else
				_hoops_RGPPGR->foreground = WhitePixelOfScreen (_hoops_RRRPC->screen);

		if (_hoops_AGPPGR != null) {
				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP))
						_hoops_RGPPGR->background = 1;
				else if (_hoops_AGPPGR->_hoops_PIHHP < _hoops_AHRSP/2)
						_hoops_RGPPGR->background = BlackPixelOfScreen (_hoops_RRRPC->screen);
				else
						_hoops_RGPPGR->background = WhitePixelOfScreen (_hoops_RRRPC->screen);
		}
}



/*
 *		** _hoops_PGAA **
 *
 */
local void _hoops_CRPPGR (
		Net_Rendition const & nr,
		XGCValues alter					*_hoops_RGPPGR,
		Driver_Color const	*_hoops_SHRIC,
		Driver_Color const	*_hoops_AGPPGR) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		Driver_Color const	*_hoops_GPIR;

		_hoops_GPIR = &nr->_hoops_SAIR->_hoops_GPIR;

		/*
		 *		_hoops_IPCP _hoops_SCPC _hoops_IH _hoops_GHGA _hoops_RH _hoops_HSPR:
		 *		_hoops_AGHI _hoops_PSHA _hoops_GGR _hoops_AGAH _hoops_HGIR [_hoops_RH _hoops_SRS _hoops_PGCR] _hoops_CHR _hoops_SHR _hoops_RCPGR
		 *		_hoops_PPR _hoops_RPSGA _hoops_IH _hoops_GHGA _hoops_PIHHR _hoops_CAIH [_hoops_HHCI _hoops_IHCI].
		 */
		{
				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP)) {
						_hoops_RGPPGR->foreground =
								_hoops_RRRPC->_hoops_SRPPGR[_hoops_RRRPC->_hoops_GAPPGR - 2] =
										_hoops_RRRPC->_hoops_SRPPGR[_hoops_SHRIC->_hoops_PGGCR] ^
										_hoops_RRRPC->_hoops_SRPPGR[_hoops_GPIR->_hoops_PGGCR];
				}
				else
						_hoops_RGPPGR->foreground = _hoops_RRRPC->_hoops_SRPPGR[_hoops_SHRIC->_hoops_PGGCR];
		}

		if (_hoops_AGPPGR != null) {
				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP)) {
						_hoops_RGPPGR->background =
								_hoops_RRRPC->_hoops_SRPPGR[_hoops_RRRPC->_hoops_GAPPGR - 1] =
										_hoops_RRRPC->_hoops_SRPPGR[_hoops_AGPPGR->_hoops_PGGCR] ^
										_hoops_RRRPC->_hoops_SRPPGR[_hoops_GPIR->_hoops_PGGCR];
				}
				else
						_hoops_RGPPGR->background = _hoops_RRRPC->_hoops_SRPPGR[_hoops_AGPPGR->_hoops_PGGCR];
		}
}



/****************************************************************
 ****************************************************************
										   _hoops_AHGPH _hoops_HRAIA _hoops_PGGIR _hoops_APCAR _hoops_GHAP _hoops_SAAAR _hoops_GHAP _hoops_RGGIR _hoops_PGGIR _hoops_IISGA
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ARH _hoops_RH _hoops_III _hoops_IPP.
 */
local void _hoops_AIHSC (
		Net_Rendition const & nr,
		Line_Rendition const &_hoops_HC) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		XGCValues								_hoops_RGPPGR;

		(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, &_hoops_HC->color, null);

		if (_hoops_HC->weight <= 1)
				_hoops_RGPPGR.line_width = 0;
		else
				_hoops_RGPPGR.line_width = _hoops_HC->weight;

		if (BIT(_hoops_HC->line_style->flags, LSF_SOLID))
				_hoops_RGPPGR.line_style = LineSolid;
		else {
				char				_hoops_RAPPGR[2048];
				int const *			_hoops_CAPSC;
				unsigned int		i;

				/*_hoops_ASIGA _hoops_RRP _hoops_IS _hoops_CCIH */
				_hoops_CAPSC = _hoops_HC->line_style->_hoops_GHISR[0].pattern;

				for (i=0; i<_hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR; i++) {
						if (_hoops_CAPSC[i] > 127)
								_hoops_RAPPGR[i] = 127;
						else if (_hoops_CAPSC[i] == 0)			/* _hoops_HAR _hoops_APP _hoops_GGR _hoops_GPAAC */
								_hoops_RAPPGR[i] = 1;
						else
								_hoops_RAPPGR[i] = (char)_hoops_CAPSC[i];
				}
				XSetDashes (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AAPPGR, 0,
								_hoops_RAPPGR, _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR);
				_hoops_RGPPGR.line_style = LineOnOffDash;
		}

		switch (_hoops_HC->style & LCAP_MASK) {
				case LCAP_BUTT: {
						_hoops_RGPPGR.cap_style = CapButt;
				}		break;

				case LCAP_ROUND: {
						_hoops_RGPPGR.cap_style = CapRound;
				}		break;

				case LCAP_SQUARE: {
						_hoops_RGPPGR.cap_style = CapProjecting;
				}		break;
		}

		switch (_hoops_HC->style & LJOIN_MASK) {
				case LJOIN_MITER: {
						_hoops_RGPPGR.join_style = JoinMiter;
				}		break;

				case LJOIN_ROUND: {
						_hoops_RGPPGR.join_style = JoinRound;
				}		break;

				case LJOIN_BEVEL: {
						_hoops_RGPPGR.join_style = JoinBevel;
				}		break;
		}

		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AAPPGR,
						   GCForeground | GCLineWidth | GCLineStyle | GCCapStyle | GCJoinStyle,
						   &_hoops_RGPPGR);

		_hoops_RRRPC->_hoops_SAICC = _hoops_HC->_hoops_CPA;
}


/*
 *		** _hoops_PGAA **
 *
 *		_hoops_GSRA _hoops_RH _hoops_IPSP _hoops_PAPR _hoops_HSGP
 */
local void _hoops_PAPPGR (
		char  *data,
		int		  width,
		int		  height,
		int		  _hoops_HAPPGR,
		int		  _hoops_ACHHP,
		char  *_hoops_SIRRC) {
		char  *_hoops_IAPPGR;
		int		  _hoops_CAPPGR, size, row, col;

		size = width * height;

		_hoops_IAPPGR = _hoops_SIRRC;

		for (_hoops_CAPPGR = 0; _hoops_CAPPGR < _hoops_HAPPGR; _hoops_CAPPGR++, _hoops_SIRRC++)
				*_hoops_SIRRC = 0;
		_hoops_SIRRC = _hoops_IAPPGR;

		row = 0;
		col = 0;
		if (_hoops_ACHHP == 2) {
				for (_hoops_CAPPGR = 0; _hoops_CAPPGR < size; _hoops_CAPPGR++) {
						/* _hoops_HSGR _hoops_IS _hoops_SPS _hoops_RAPSR _hoops_RPP _hoops_IHIR _hoops_PAR _hoops_RSGR _hoops_IIGR _hoops_IRS _hoops_GAGHR */
						if (!(col%8)) {
								if (col) {
										_hoops_IAPPGR++; row = 0;
								}
						}
						else {
								if (!(col%width)) {
										_hoops_IAPPGR++;
										col = 0; row = 0;
								}
						}

						if (!data[_hoops_CAPPGR])
								_hoops_GHAPGR (*_hoops_IAPPGR, row % 8);
						row++;
						col++;
				}
		}
		else {
				for (_hoops_CAPPGR = 0; _hoops_CAPPGR < size; _hoops_CAPPGR++) {
						/* _hoops_HSGR _hoops_IS _hoops_SPS _hoops_RAPSR _hoops_RPP _hoops_IHIR _hoops_PAR _hoops_RSGR _hoops_IIGR _hoops_IRS _hoops_GAGHR */
						if (!(col%8)) {
								if (col) {
										_hoops_IAPPGR++; row = 0;
								}
						}
						else {
								if (!(col%width)) {
										_hoops_IAPPGR++;
										col = 0; row = 0;
								}
						}

						if (data[_hoops_CAPPGR])
								_hoops_GHAPGR (*_hoops_IAPPGR, row % 8);
						row++;
						col++;
				}
		}
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ARH _hoops_RH _hoops_HSP _hoops_IPP.
 */
local bool _hoops_IAGGS (
		Net_Rendition const &		nr,
		Driver_Color		const  *_hoops_RSISR) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
		XGCValues								_hoops_RGPPGR;
		unsigned long					_hoops_SAPPGR;

		if (_hoops_SIGA->pattern != FP_SOLID) {
				if (_hoops_SIGA->pattern != FP_USER_DEFINED) {
						(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, &_hoops_SIGA->contrast_color, _hoops_RSISR);
						_hoops_RGPPGR.fill_style = FillOpaqueStippled;
						_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_SIGA->pattern];
						_hoops_SAPPGR = GCForeground | GCBackground | GCFillStyle | GCStipple;
				}
				else {
						int				_hoops_CAPPGR;
						int				width, height, _hoops_HAPPGR;
						char	*_hoops_IAPPGR, *data;
						Pixmap	_hoops_GPPPGR;
						char	*_hoops_PGPH, *_hoops_RPPPGR = null;
						bool _hoops_APPPGR;

						width = _hoops_SIGA->_hoops_PGPH->width;
						height= _hoops_SIGA->_hoops_PGPH->height;
						data  = (char alter *)_hoops_SIGA->_hoops_PGPH->pattern;

						if (width % 8)
								_hoops_HAPPGR = ((width / 8) + 1) * height;
						else
								_hoops_HAPPGR = (width / 8) * height;

						ALLOC_ARRAY (_hoops_PGPH, _hoops_HAPPGR, char);
						_hoops_IAPPGR = _hoops_PGPH;

						_hoops_PAPPGR (data, width, height, _hoops_HAPPGR,
														   _hoops_SIGA->_hoops_PGPH->_hoops_ACHHP, _hoops_IAPPGR);

						_hoops_APPPGR = false;

						if ((BitmapBitOrder (_hoops_RRRPC->display) == MSBFirst)
								 && (ImageByteOrder (_hoops_RRRPC->display) == MSBFirst))
								 _hoops_APPPGR = true;

						if ((BitmapBitOrder (_hoops_RRRPC->display) == LSBFirst)
								 && (ImageByteOrder (_hoops_RRRPC->display) == LSBFirst))
								 _hoops_APPPGR = true;

						if (_hoops_APPPGR) {
								ALLOC_ARRAY (_hoops_RPPPGR, _hoops_HAPPGR, char);
								for (_hoops_CAPPGR = 0; _hoops_CAPPGR < _hoops_HAPPGR; _hoops_CAPPGR++, _hoops_IAPPGR++)
										_hoops_RPPPGR[_hoops_CAPPGR] =
												HOOPS_READ_ONLY._hoops_SCHGI[_hoops_IRGCR(*_hoops_IAPPGR)];
								_hoops_IAPPGR = _hoops_RPPPGR;
						}

						if ((_hoops_GPPPGR =
								XCreateBitmapFromData (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
																				_hoops_IAPPGR, width, height)) != 0) {
								FREE_ARRAY (_hoops_PGPH, _hoops_HAPPGR, char);
								if (_hoops_APPPGR)
										FREE_ARRAY (_hoops_RPPPGR, _hoops_HAPPGR, char);
								return false;
						}

						FREE_ARRAY (_hoops_PGPH, _hoops_HAPPGR, char);
						if (_hoops_APPPGR) {
								FREE_ARRAY (_hoops_RPPPGR, _hoops_HAPPGR, char);
						}

						XSetStipple (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, _hoops_GPPPGR);
						if (_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP)
								XSetFillStyle (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, FillStippled);
						else
								XSetFillStyle (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, FillOpaqueStippled);
						if (_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP == 2)
								(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, _hoops_RSISR, &_hoops_SIGA->contrast_color);
						else
								(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, &_hoops_SIGA->contrast_color, _hoops_RSISR);
						_hoops_SAPPGR = GCForeground | GCBackground;
				}
		}
		else {
				(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, _hoops_RSISR, null);
				_hoops_RGPPGR.fill_style = FillSolid;
				_hoops_SAPPGR = GCForeground | GCFillStyle;
		}

		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, _hoops_SAPPGR, &_hoops_RGPPGR);

		_hoops_RRRPC->_hoops_HPPPGR = _hoops_SIGA->_hoops_CPA;
		return true;
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ARH _hoops_RH _hoops_HSP _hoops_IPP _hoops_IH 1 _hoops_IGRH _hoops_SGAPC.
 */
local bool _hoops_IPPPGR (
		Net_Rendition const &		nr,
		Driver_Color		const  *_hoops_RSISR) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
		XGCValues								_hoops_RGPPGR;
		_hoops_HIHHP					_hoops_PIHHP;
		unsigned long					_hoops_SAPPGR;

		UNREFERENCED(_hoops_RSISR);

		_hoops_PIHHP = _hoops_SIGA->color._hoops_PIHHP;
		if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP))
				_hoops_PIHHP ^= nr->_hoops_SAIR->_hoops_GPIR._hoops_PIHHP;

		if (_hoops_PIHHP != 0 && _hoops_PIHHP != _hoops_AHRSP) {
				/* _hoops_IGSGR _hoops_IIGR _hoops_IIGRP - _hoops_RSPH _hoops_SCH. _hoops_HGAPR _hoops_CPPPGR _hoops_SPPPGR _hoops_GHPPGR! */
				_hoops_RGPPGR.background = BlackPixelOfScreen (_hoops_RRRPC->screen);
				_hoops_RGPPGR.foreground = WhitePixelOfScreen (_hoops_RRRPC->screen);
				_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_CPRSP + _hoops_PIHHP];
				_hoops_RGPPGR.fill_style = FillOpaqueStippled;

				_hoops_SAPPGR = GCForeground | GCBackground | GCFillStyle | GCStipple;
		}
		else if (_hoops_SIGA->pattern == FP_SOLID) {
				if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP))
						_hoops_RGPPGR.foreground = 1;
				else if (_hoops_PIHHP == 0)
						_hoops_RGPPGR.foreground = BlackPixelOfScreen (_hoops_RRRPC->screen);
				else
						_hoops_RGPPGR.foreground = WhitePixelOfScreen (_hoops_RRRPC->screen);

				_hoops_RGPPGR.fill_style = FillSolid;

				_hoops_SAPPGR = GCForeground | GCFillStyle;
		}
		else {
				/* _hoops_IIPH _hoops_APRP-_hoops_PPR-_hoops_PGS */
				if (_hoops_PIHHP == 0) {
						_hoops_RGPPGR.foreground = WhitePixelOfScreen (_hoops_RRRPC->screen);
						_hoops_RGPPGR.background = BlackPixelOfScreen (_hoops_RRRPC->screen);
				}
				else {
						_hoops_RGPPGR.foreground = BlackPixelOfScreen (_hoops_RRRPC->screen);
						_hoops_RGPPGR.background = WhitePixelOfScreen (_hoops_RRRPC->screen);
				}

				_hoops_RGPPGR.fill_style = FillOpaqueStippled;
				_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_SIGA->pattern];

				_hoops_SAPPGR = GCForeground | GCBackground | GCFillStyle | GCStipple;
		}

		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, _hoops_SAPPGR, &_hoops_RGPPGR);

		_hoops_RRRPC->_hoops_HPPPGR = _hoops_SIGA->_hoops_CPA;

		return true;
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ARH _hoops_RH _hoops_HPGCR _hoops_HSP _hoops_IPP.
 */
local bool _hoops_RHPPGR (
		Net_Rendition const &		nr,
		Driver_Color		const  *_hoops_RSISR) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
		XGCValues								_hoops_RGPPGR;
		unsigned long					_hoops_SAPPGR;

		if (_hoops_SIGA->pattern != FP_USER_DEFINED) {
				(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, &_hoops_SIGA->contrast_color, _hoops_RSISR);
				_hoops_RGPPGR.fill_style = FillStippled;
				_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_SIGA->pattern];
				_hoops_SAPPGR = GCForeground | GCFillStyle | GCStipple;
				if (_hoops_RSISR != null)
						_hoops_SAPPGR |= GCBackground;
		}
		else {
				int				_hoops_CAPPGR;
				int				width, height, _hoops_HAPPGR;
				char	*_hoops_IAPPGR, *data;
				Pixmap	_hoops_GPPPGR;
				char	*_hoops_PGPH, *_hoops_RPPPGR = null;
				bool _hoops_APPPGR;

				width = _hoops_SIGA->_hoops_PGPH->width;
				height= _hoops_SIGA->_hoops_PGPH->height;
				data  = (char alter *)_hoops_SIGA->_hoops_PGPH->pattern;

				if (width % 8)
						_hoops_HAPPGR = ((width / 8) + 1) * height;
				else
						_hoops_HAPPGR = (width / 8) * height;

				ALLOC_ARRAY (_hoops_PGPH, _hoops_HAPPGR, char);
				_hoops_IAPPGR = _hoops_PGPH;

				_hoops_PAPPGR (data, width, height, _hoops_HAPPGR,
												   _hoops_SIGA->_hoops_PGPH->_hoops_ACHHP, _hoops_IAPPGR);

				_hoops_APPPGR = false;

				if ((BitmapBitOrder (_hoops_RRRPC->display) == MSBFirst)
						&& (ImageByteOrder (_hoops_RRRPC->display) == MSBFirst))
						_hoops_APPPGR = true;

				if ((BitmapBitOrder (_hoops_RRRPC->display) == LSBFirst)
						&& (ImageByteOrder (_hoops_RRRPC->display) == LSBFirst))
						_hoops_APPPGR = true;

				if (_hoops_APPPGR) {
						ALLOC_ARRAY (_hoops_RPPPGR, _hoops_HAPPGR, char);
						for (_hoops_CAPPGR = 0; _hoops_CAPPGR < _hoops_HAPPGR; _hoops_CAPPGR++, _hoops_IAPPGR++)
								_hoops_RPPPGR[_hoops_CAPPGR] =
										HOOPS_READ_ONLY._hoops_SCHGI[_hoops_IRGCR(*_hoops_IAPPGR)];
						_hoops_IAPPGR = _hoops_RPPPGR;
				}

				if ((_hoops_GPPPGR =
						 XCreateBitmapFromData (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
																		_hoops_IAPPGR, width, height)) != 0) {
						FREE_ARRAY (_hoops_PGPH, _hoops_HAPPGR, char);
						if (_hoops_APPPGR)
								FREE_ARRAY (_hoops_RPPPGR, _hoops_HAPPGR, char);
						return false;
				}

				FREE_ARRAY (_hoops_PGPH, _hoops_HAPPGR, char);
				if (_hoops_APPPGR) {
						FREE_ARRAY (_hoops_RPPPGR, _hoops_HAPPGR, char);
				}

				XSetStipple (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR, _hoops_GPPPGR);
				XSetFillStyle (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR, FillStippled);
				(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, &_hoops_SIGA->contrast_color, _hoops_RSISR);
				_hoops_SAPPGR = GCForeground | GCBackground;
		}
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR, _hoops_SAPPGR, &_hoops_RGPPGR);
		return true;
}



/****************************************************************
 ****************************************************************
								   _hoops_AHGPH _hoops_RAIGR _hoops_IISGA _hoops_SAAAR _hoops_HRAIA _hoops_AHGPH	  _hoops_AHGPH _hoops_RGGIR _hoops_GRGGR _hoops_SAAAR _hoops_GHAP _hoops_PGGIR _hoops_HRAIA _hoops_IISGA
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_RRRS _hoops_IRS _hoops_SHCA _hoops_IGRH _hoops_PPSCP _hoops_CCA _hoops_SSRR _hoops_IGRH _hoops_SIHHI
 */
local void _hoops_CCCGA (
		Net_Rendition const & nr,
		DC_Point const				*start,
		DC_Point const				*end,
		int								row_bytes,
		unsigned char const				*_hoops_GAAC) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		int								count = (int)end->x - (int)start->x + 1;
		unsigned char					_hoops_RIIGS[_hoops_HIRSP/8];
		int								width;

		_hoops_SIRGS ("draw dc direct bit raster", _hoops_RRRPC);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_HHPPGR);

		width = ((count * sizeof (char) + 7) / 8);

		if (row_bytes == 0)
				row_bytes = width;

		if (_hoops_RRRPC->_hoops_IHPPGR) {
				unsigned char alter						*_hoops_ISSPA;
				unsigned char const						*_hoops_HSGCR;

				_hoops_RRRPC->_hoops_CHPPGR->data = (char alter *)_hoops_RIIGS;
				_hoops_HSGCR = _hoops_GAAC + row_bytes;
				_hoops_ISSPA = _hoops_RIIGS;

				switch (_hoops_RRRPC->_hoops_IHPPGR) {
						case _hoops_SHPPGR: {
								_hoops_RGGA (_hoops_GAAC == _hoops_HSGCR)
										*_hoops_ISSPA++ = HOOPS_READ_ONLY._hoops_SCHGI[_hoops_IRGCR(*_hoops_GAAC++)];
						}		break;

						case _hoops_GIPPGR: {
								_hoops_RGGA (_hoops_GAAC == _hoops_HSGCR)
										*_hoops_ISSPA++ = ~*_hoops_GAAC++;
						}		break;

						case (_hoops_SHPPGR | _hoops_GIPPGR): {
								_hoops_RGGA (_hoops_GAAC == _hoops_HSGCR)
										*_hoops_ISSPA++ = HOOPS_READ_ONLY._hoops_SCHGI[_hoops_IRGCR(~*_hoops_GAAC++)];
						}		break;
				}
		}
		else
				_hoops_RRRPC->_hoops_CHPPGR->data = (char alter *)_hoops_GAAC;
		_hoops_RRRPC->_hoops_CHPPGR->width = width;
		_hoops_RRRPC->_hoops_CHPPGR->bytes_per_line = row_bytes;

		XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
						   _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_CHPPGR, 0, 0,
						   (int)start->x, _hoops_RRRPC->yfudge - (int)start->y, count, 1);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_RRRS _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_PPSCP _hoops_CCA _hoops_RH _hoops_CPCP _hoops_RRRGI.
 *		[_hoops_HAS._hoops_IAS. _hoops_SSIA _hoops_GA'_hoops_RA _hoops_HS _hoops_PSHR _hoops_CACSH]
 */
local void _hoops_RIPPGR (
		Net_Rendition const & nr,
		DC_Point const				*start,
		DC_Point const				*end,
		int								row_bytes,
		RGBAS32 const				*rasters) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		int								width = (int)end->x - (int)start->x + 1;
		int								height = (int)start->y - (int)end->y + 1;
		int								_hoops_AIPPGR = height;
		RGBAS32 alter				*_hoops_PIPPGR;
		RGBAS32 const				*_hoops_ISSPA;
		RGBAS32 const				*_hoops_HIPPGR;
		/*_hoops_RGR _hoops_CRSH _hoops_PPSCP _hoops_SAGGR _hoops_IASH _hoops_IIGR _hoops_RH _hoops_IIPPGR _hoops_RAPC _hoops_HIIC _hoops_GASAR _hoops_ISHP _hoops_RH _hoops_RRGR*/
		RGBAS32 alter				*_hoops_CIPPGR = (RGBAS32 alter *)rasters;

		_hoops_SIRGS ("draw dc mangled rgb32 rasters", _hoops_RRRPC);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_HHPPGR);

		if (row_bytes == 0)
				row_bytes = width * sizeof (RGBAS32);

		if (_hoops_RRRPC->_hoops_SIPPGR != null) {
				if (_hoops_RRRPC->_hoops_SIPPGR->bytes_per_line != row_bytes ||
						_hoops_RRRPC->_hoops_SIPPGR->height != height) {
						_hoops_RRRPC->_hoops_SIPPGR->data = null;
						XDestroyImage (_hoops_RRRPC->_hoops_SIPPGR);
						_hoops_RRRPC->_hoops_SIPPGR = null;
						FREE_ARRAY (_hoops_RRRPC->_hoops_PHGH, _hoops_RRRPC->_hoops_PASIH, RGBAS32);
				}
		}

		if (_hoops_RRRPC->_hoops_SIPPGR == null) {
				_hoops_RRRPC->_hoops_SIPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
																						 24, ZPixmap, 0, null, width,
																						 height, 32, 0);
				_hoops_RRRPC->_hoops_PASIH = width * height;
				ALLOC_ARRAY (_hoops_RRRPC->_hoops_PHGH, _hoops_RRRPC->_hoops_PASIH, RGBAS32);
		}
		_hoops_PIPPGR = _hoops_RRRPC->_hoops_PHGH;
		_hoops_RRRPC->_hoops_SIPPGR->data = (char *)_hoops_PIPPGR;
		if (_hoops_RRRPC->_hoops_GCPPGR != _hoops_RCPPGR) {
				switch (_hoops_RRRPC->_hoops_GCPPGR) {
						case _hoops_ACPPGR: {
								_hoops_RGGA (_hoops_AIPPGR-- == 0) {
										_hoops_ISSPA = _hoops_CIPPGR;
										_hoops_HIPPGR = _hoops_CIPPGR+width;
										_hoops_RGGA (_hoops_ISSPA == _hoops_HIPPGR) {
												_hoops_PIPPGR->r = _hoops_ISSPA->b;
												_hoops_PIPPGR->g = _hoops_ISSPA->g;
												_hoops_PIPPGR->b = _hoops_ISSPA->r;
												_hoops_PIPPGR->a = _hoops_ISSPA->a;
												++_hoops_PIPPGR;
												++_hoops_ISSPA;
										}
										_hoops_CIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_CIPPGR + row_bytes);
								}
						}		break;

						case _hoops_PCPPGR: {
								  _hoops_RGGA (_hoops_AIPPGR-- == 0) {
										  _hoops_ISSPA = _hoops_CIPPGR;
										  _hoops_HIPPGR = _hoops_CIPPGR+width;
										  _hoops_RGGA (_hoops_ISSPA == _hoops_HIPPGR) {
												  _hoops_PIPPGR->r = _hoops_ISSPA->a;
												  _hoops_PIPPGR->g = _hoops_ISSPA->b;
												  _hoops_PIPPGR->b = _hoops_ISSPA->g;
												  _hoops_PIPPGR->a = _hoops_ISSPA->r;
												  ++_hoops_PIPPGR;
												  ++_hoops_ISSPA;
										  }
										_hoops_CIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_CIPPGR + row_bytes);
								  }
						}		break;

						case _hoops_HCPPGR: {
								_hoops_RGGA (_hoops_AIPPGR-- == 0) {
										_hoops_ISSPA = _hoops_CIPPGR;
										_hoops_HIPPGR = _hoops_CIPPGR+width;
										_hoops_RGGA (_hoops_ISSPA == _hoops_HIPPGR) {
												_hoops_PIPPGR->r = _hoops_ISSPA->g;
												_hoops_PIPPGR->g = _hoops_ISSPA->r;
												_hoops_PIPPGR->b = _hoops_ISSPA->a;
												_hoops_PIPPGR->a = _hoops_ISSPA->b;
												++_hoops_PIPPGR;
												++_hoops_ISSPA;
										}
										_hoops_CIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_CIPPGR + row_bytes);
								}
						}		break;

						case _hoops_ICPPGR: {
								_hoops_RGGA (_hoops_AIPPGR-- == 0) {
										_hoops_ISSPA = _hoops_CIPPGR;
										_hoops_HIPPGR = _hoops_CIPPGR+width;
										_hoops_RGGA (_hoops_ISSPA == _hoops_HIPPGR) {
												_hoops_PIPPGR->r = _hoops_ISSPA->a;
												_hoops_PIPPGR->g = _hoops_ISSPA->r;
												_hoops_PIPPGR->b = _hoops_ISSPA->g;
												_hoops_PIPPGR->a = _hoops_ISSPA->b;
												++_hoops_PIPPGR;
												++_hoops_ISSPA;
										}
										_hoops_CIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_CIPPGR + row_bytes);
								}
						}		break;

						default /* _hoops_AGIR _hoops_CCPPGR */: {
								_hoops_RGGA (_hoops_AIPPGR-- == 0) {
										_hoops_ISSPA = _hoops_CIPPGR;
										_hoops_HIPPGR = _hoops_CIPPGR+width;
										_hoops_RGGA (_hoops_ISSPA == _hoops_HIPPGR) {
												_hoops_PIPPGR->r = _hoops_ISSPA->g;
												_hoops_PIPPGR->g = _hoops_ISSPA->b;
												_hoops_PIPPGR->b = _hoops_ISSPA->a;
												_hoops_PIPPGR->a = _hoops_ISSPA->r;
												++_hoops_PIPPGR;
												++_hoops_ISSPA;
										}
										_hoops_CIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_CIPPGR + row_bytes);
								}
						}		break;
				}
		}

		XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
						   _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_SIPPGR, 0, 0,
						   (int)start->x, _hoops_RRRPC->yfudge - (int)start->y, width, height);
}


/*
 *		** _hoops_SRAC **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_RRRS 24 _hoops_IGRH _hoops_HAIR _hoops_AHRH _hoops_SIHH _hoops_GII _hoops_HAIR _hoops_SIHHI.
 *		_hoops_HGI _hoops_PCPH _hoops_HRGR _hoops_PIGS _hoops_RPP _hoops_GIPR _hoops_SCPPGR _hoops_PPR _hoops_RPRGR _hoops_HS _hoops_PSHR _hoops_CACSH.
 */
local void _hoops_GSPPGR (
		Net_Rendition const & nr,
		DC_Point const		*start,
		DC_Point const		*end,
		int						row_bytes,
		RGBAS32 const		*rasters) {
		X11Data alter			*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		int						width = (int)end->x - (int)start->x + 1;
		int						height = (int)start->y - (int)end->y + 1;
		XImage alter			*_hoops_RSPPGR;

		_hoops_SIRGS ("draw dc direct rgb32 rasters", _hoops_RRRPC);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_HHPPGR);

		if (row_bytes == 0)
				row_bytes = width * sizeof (RGBAS32);

		if (height > 1) {
				if (_hoops_RRRPC->_hoops_SIPPGR != null) {
						if (_hoops_RRRPC->_hoops_SIPPGR->bytes_per_line != row_bytes ||
								_hoops_RRRPC->_hoops_SIPPGR->height != height) {
								_hoops_RRRPC->_hoops_SIPPGR->data = null;
								XDestroyImage (_hoops_RRRPC->_hoops_SIPPGR);
								_hoops_RRRPC->_hoops_SIPPGR = null;
						}
				}
				if (_hoops_RRRPC->_hoops_SIPPGR == null)
						_hoops_RRRPC->_hoops_SIPPGR = XCreateImage (_hoops_RRRPC->display,
																								 _hoops_RRRPC->visual,
																								 24, ZPixmap, 0, null,
																								 width, height, 32, 0);
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_SIPPGR;
		}
		else
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_CHPPGR;

		_hoops_RSPPGR->data = (char alter *)rasters;

		_hoops_RSPPGR->width = width;
		_hoops_RSPPGR->height = height;
		_hoops_RSPPGR->bytes_per_line = row_bytes;

		XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PHPPGR,
						   _hoops_RSPPGR, 0, 0, (int)start->x, _hoops_RRRPC->yfudge - (int)start->y,
						   width, height);
}

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_RRRS _hoops_GIACS 16 _hoops_PAR 24 _hoops_IGRH _hoops_HAIR _hoops_AHRH
 *		_hoops_ARRAR _hoops_HII _hoops_GCRSP _hoops_IS _hoops_RH _hoops_ASPPGR _hoops_RPCC
 *		_hoops_RHRRA _hoops_HHIGR'_hoops_GRI _hoops_HAR _hoops_HRAAI _hoops_ICIC _hoops_RPHR _hoops_HA.
 */
local void _hoops_PSPPGR (
		Net_Rendition const & nr,
		DC_Point const		*start,
		DC_Point const		*end,
		int						row_bytes,
		RGBAS32 const		*rasters) {
		X11Data alter			*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		int						width = (int)end->x - (int)start->x + 1;
		int						height = (int)start->y - (int)end->y + 1;
		int						_hoops_AIPPGR = height;
		RGBAS32 alter		*_hoops_PIPPGR;
		RGBAS32 const		*_hoops_ISSPA;
		RGBAS32 const		*_hoops_HIPPGR;
		/*_hoops_RGR _hoops_CRSH _hoops_PPSCP _hoops_SAGGR _hoops_IASH _hoops_IIGR _hoops_RH _hoops_IIPPGR _hoops_RAPC _hoops_HIIC _hoops_GASAR _hoops_ISHP _hoops_RH _hoops_RRGR*/
		RGBAS32 alter		*_hoops_CIPPGR = (RGBAS32 alter *)rasters;

		_hoops_SIRGS ("draw dc shifted rgb32 rasters", _hoops_RRRPC);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_HHPPGR);

		if (row_bytes == 0)
								row_bytes = width * sizeof (RGBAS32);

		/*_hoops_RGR _hoops_SAGGR _hoops_RH _hoops_SIGR _hoops_CSCR _hoops_HII _hoops_IHAH _hoops_PAR _hoops_SHS _hoops_CAS*/
		if ((height>_hoops_HSPPGR) || (width>_hoops_ISPPGR)) {
				/*_hoops_IGIR _hoops_HAR _hoops_GGR _hoops_RH _hoops_IHAH _hoops_HIS _hoops_AA _hoops_RH _hoops_GSSR _hoops_CSPPGR _hoops_CIPH*/

				if (_hoops_RRRPC->_hoops_SIPPGR != null) {
								if (_hoops_RRRPC->_hoops_SIPPGR->bytes_per_line != row_bytes ||
												_hoops_RRRPC->_hoops_SIPPGR->height != height) {
												_hoops_RRRPC->_hoops_SIPPGR->data = null;
												XDestroyImage (_hoops_RRRPC->_hoops_SIPPGR);
												_hoops_RRRPC->_hoops_SIPPGR = null;
												FREE_ARRAY (_hoops_RRRPC->_hoops_PHGH, _hoops_RRRPC->_hoops_PASIH, RGBAS32);
								}
				}

				if (_hoops_RRRPC->_hoops_SIPPGR == null) {
								if (_hoops_RRRPC->depth == 16)
												_hoops_RRRPC->_hoops_SIPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
																 16, ZPixmap, 0, null, width, height, 16, 0);
								else
												_hoops_RRRPC->_hoops_SIPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
																 24, ZPixmap, 0, null, width, height, 32, 0);


								_hoops_RRRPC->_hoops_PASIH = width * height;
								ALLOC_ARRAY (_hoops_RRRPC->_hoops_PHGH, _hoops_RRRPC->_hoops_PASIH, RGBAS32);
				}

				_hoops_PIPPGR = _hoops_RRRPC->_hoops_PHGH;
				_hoops_RRRPC->_hoops_SIPPGR->data = (char *)_hoops_PIPPGR;
		}
		else {
				/* _hoops_SR _hoops_CHR _hoops_GGR _hoops_RH _hoops_IHAH _hoops_PAR _hoops_RRP _hoops_IS _hoops_SHH*/
				if (_hoops_RRRPC->_hoops_SSPPGR[height-1][width-1] == null) {
								if (_hoops_RRRPC->depth == 16)
												_hoops_RRRPC->_hoops_SSPPGR[height-1][width-1] =
																XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
																 16, ZPixmap, 0, null, width, height, 16, 0);
								else
												_hoops_RRRPC->_hoops_SSPPGR[height-1][width-1] =
																XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
																 24, ZPixmap, 0, null, width, height, 32, 0);


								ALLOC_ARRAY (_hoops_PIPPGR, width * height, RGBAS32);
								_hoops_RRRPC->_hoops_SSPPGR[height-1][width-1]->data = (char *)_hoops_PIPPGR;
				}
				else {
								/*_hoops_IRS _hoops_IHAH _hoops_RHHR _hoops_RGR _hoops_HRGR _hoops_RRHP*/
								_hoops_PIPPGR = (RGBAS32 alter *)_hoops_RRRPC->_hoops_SSPPGR[height-1][width-1]->data;
				}
		}

		/*_hoops_HA _hoops_SR _hoops_GGHPGR _hoops_RH _hoops_AHRH*/
		if (_hoops_RRRPC->depth == 16) {
				unsigned _hoops_RGHPGR;

				while (_hoops_AIPPGR-- != 0) {
								_hoops_ISSPA = _hoops_CIPPGR;
								_hoops_HIPPGR = _hoops_CIPPGR+width;

								while (_hoops_ISSPA != _hoops_HIPPGR) {
												/*_hoops_RGR _hoops_GGSHR _hoops_IGIPR 16b_hoops_SCH _hoops_GCPRGR _hoops_CHR _hoops_RSCA _hoops_HRAAI */
#if HOOPS_BIGENDIAN
# define _hoops_AGHPGR(a)				(short)((0x00ff & ((a) >> 8)) | ((0x00ff & (a)) << 8))
#else
# define _hoops_AGHPGR(a)				(a)
#endif

												/*_hoops_SICR _hoops_RH 32b_hoops_SCH _hoops_PPSCP _hoops_IS _hoops_PHAP 16b_hoops_SCH*/
												_hoops_RGHPGR =
																(((unsigned short)_hoops_ISSPA->r >> _hoops_RRRPC->_hoops_CGPPGR)
																				<< _hoops_RRRPC->_hoops_SGPPGR) |
																(((unsigned short)_hoops_ISSPA->g >> _hoops_RRRPC->_hoops_GRPPGR)
																				<< _hoops_RRRPC->_hoops_RRPPGR) |
																(((unsigned short)_hoops_ISSPA->b >> _hoops_RRRPC->_hoops_ARPPGR)
																				<< _hoops_RRRPC->_hoops_PRPPGR);

												(*(unsigned short*)_hoops_PIPPGR) = _hoops_AGHPGR(_hoops_RGHPGR);


#undef _hoops_AGHPGR


												_hoops_PIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_PIPPGR+2);
												_hoops_ISSPA++;
								}

								_hoops_CIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_CIPPGR + row_bytes);
				}
		}
		else {
				/* 24 _hoops_IGRH _hoops_SR _hoops_GRHHR, _hoops_GHAP _hoops_GRHHR*/

				while (_hoops_AIPPGR-- != 0) {
								_hoops_ISSPA = _hoops_CIPPGR;
								_hoops_HIPPGR = _hoops_CIPPGR+width;

								while (_hoops_ISSPA != _hoops_HIPPGR) {
												*((unsigned char*)_hoops_PIPPGR+(_hoops_RRRPC->_hoops_SGPPGR>>3)) = _hoops_ISSPA->r;
												*((unsigned char*)_hoops_PIPPGR+(_hoops_RRRPC->_hoops_RRPPGR>>3)) = _hoops_ISSPA->g;
												*((unsigned char*)_hoops_PIPPGR+(_hoops_RRRPC->_hoops_PRPPGR>>3)) = _hoops_ISSPA->b;

												/*_hoops_SR _hoops_CHR _hoops_GRP _hoops_GCRSP _hoops_RIIA _hoops_IIGR _hoops_APPC _hoops_GSPR*/
												/*_hoops_HIS _hoops_CASI _hoops_GH _hoops_HRGR _hoops_PIHGR _hoops_SHS _hoops_CAS _hoops_GGR _hoops_RH _hoops_RHPP*/
												_hoops_PIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_PIPPGR+3);

												_hoops_ISSPA++;
								}

								/*_hoops_RGR _hoops_PGHPGR _hoops_CRAPH _hoops_AHAP _hoops_HRGR _hoops_PGGA _hoops_SPCR _hoops_GSSS _hoops_HGHPGR _hoops_GPP _hoops_HAPHR*/
								/*_hoops_HIS _hoops_SSIA _hoops_HS _hoops_PRGI 32b_hoops_RGCI _hoops_IGHPGR, _hoops_RGR _hoops_HRGR %4 _hoops_GPP _hoops_RH _hoops_SPS _hoops_III*/
								_hoops_PIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_PIPPGR+((_hoops_ISSPA-_hoops_CIPPGR)&0x3));

								_hoops_CIPPGR=(RGBAS32 alter*)((unsigned char*)_hoops_CIPPGR + row_bytes);
				}
		}


		if ((height>_hoops_HSPPGR) || (width>_hoops_ISPPGR)) {
				/*_hoops_CSPPGR*/
				XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
								   _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_SIPPGR, 0, 0,
								   (int)start->x, _hoops_RRRPC->yfudge - (int)start->y, width, height);
		}
		else {
				/*_hoops_PIAH*/
				XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
								   _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_SSPPGR[height-1][width-1], 0, 0,
								   (int)start->x, _hoops_RRRPC->yfudge - (int)start->y, width, height);
		}
}


/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_SHCA _hoops_CGHPGR _hoops_GPPR 8 _hoops_IGRH _hoops_AHRH.
 */
local void _hoops_GSCGA (
		Net_Rendition const & nr,
		DC_Point const				*start,
		DC_Point const				*end,
		int								row_bytes,
		unsigned char const				*rasters) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		int								width = (int)end->x - (int)start->x + 1;
		int								height = (int)start->y - (int)end->y + 1;
		XImage alter					*_hoops_RSPPGR;

		_hoops_SIRGS ("draw dc gray8 rasters", _hoops_RRRPC);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_HHPPGR);

		if (row_bytes == 0)
				row_bytes = width * sizeof (char);

		if (height > 1) {
				if (_hoops_RRRPC->_hoops_SIPPGR != null) {
						if (_hoops_RRRPC->_hoops_SIPPGR->bytes_per_line  != row_bytes ||
								_hoops_RRRPC->_hoops_SIPPGR->height != height) {
								_hoops_RRRPC->_hoops_SIPPGR->data = null;
								XDestroyImage (_hoops_RRRPC->_hoops_SIPPGR);
								_hoops_RRRPC->_hoops_SIPPGR = null;
						}
				}
				if (_hoops_RRRPC->_hoops_SIPPGR == null)
						_hoops_RRRPC->_hoops_SIPPGR = XCreateImage (_hoops_RRRPC->display,
																								 _hoops_RRRPC->visual,
																								 8, ZPixmap, 0, null,
																								 width, height, 8, row_bytes);
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_SIPPGR;
		}
		else
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_CHPPGR;

		_hoops_RSPPGR->data = (char alter *)rasters;
		_hoops_RSPPGR->width  = width;
		_hoops_RSPPGR->height = height;
		_hoops_RSPPGR->bytes_per_line = row_bytes;
		XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PHPPGR,
						   _hoops_RSPPGR,
						   0, 0, (int)start->x, _hoops_RRRPC->yfudge - (int)start->y,
						   width, height);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_SHCA _hoops_SCGH 8 _hoops_IGRH _hoops_AHRH.
 */
local void _hoops_CCCSR (
		Net_Rendition const & nr,
		DC_Point const				*start,
		DC_Point const				*end,
		int								row_bytes,
		unsigned char const				*rasters) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		int								width = (int)end->x - (int)start->x + 1;
		int								height = (int)start->y - (int)end->y + 1;
		int								_hoops_PSCIP = height;
		XImage alter					*_hoops_RSPPGR;
		unsigned char alter				*_hoops_ISSPA;
		unsigned char const				*_hoops_SCGCR;
		unsigned char const				*_hoops_HSGCR;

		_hoops_SIRGS ("draw dc mapped8 rasters", _hoops_RRRPC);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_HHPPGR);

		if (row_bytes == 0)
				row_bytes = width;

		if (height > 1) {
				if (_hoops_RRRPC->_hoops_SIPPGR != null) {
						if (_hoops_RRRPC->_hoops_SIPPGR->bytes_per_line != row_bytes ||
								_hoops_RRRPC->_hoops_SIPPGR->height != height) {
								_hoops_RRRPC->_hoops_SIPPGR->data = null;
								XDestroyImage (_hoops_RRRPC->_hoops_SIPPGR);
								_hoops_RRRPC->_hoops_SIPPGR = null;
								FREE_ARRAY (_hoops_RRRPC->_hoops_SGHPGR, _hoops_RRRPC->_hoops_GRHPGR, unsigned char);
								_hoops_RRRPC->_hoops_SGHPGR = null;
								_hoops_RRRPC->_hoops_GRHPGR = 0;
						}
				}
				if (_hoops_RRRPC->_hoops_SIPPGR == null) {
						_hoops_RRRPC->_hoops_SIPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
																								 8, ZPixmap, 0, null, width, height, 8, 0);
						_hoops_RRRPC->_hoops_GRHPGR = width*height;
						ALLOC_ARRAY (_hoops_RRRPC->_hoops_SGHPGR, _hoops_RRRPC->_hoops_GRHPGR, unsigned char);
				}
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_SIPPGR;
				_hoops_ISSPA = _hoops_RRRPC->_hoops_SGHPGR;
		}
		else {
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_CHPPGR;
				_hoops_ISSPA = _hoops_RRRPC->_hoops_RRHPGR;
		}

		_hoops_RSPPGR->data = (char alter *)_hoops_ISSPA;
		if (row_bytes != width) {
				_hoops_RGGA (height-- == 0) {
						_hoops_SCGCR = rasters;
						_hoops_HSGCR = rasters + width;
						_hoops_RGGA (_hoops_SCGCR == _hoops_HSGCR)
								*_hoops_ISSPA++ = (unsigned char)_hoops_RRRPC->_hoops_SRPPGR[*_hoops_SCGCR++];
						rasters += row_bytes;
				}
		}
		else {
				_hoops_HSGCR = rasters + width*height;
				_hoops_RGGA (rasters == _hoops_HSGCR)
						*_hoops_ISSPA++ = (unsigned char)_hoops_RRRPC->_hoops_SRPPGR[*rasters++];
		}

		XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PHPPGR,
						   _hoops_RSPPGR,
						   0, 0, (int)start->x, _hoops_RRRPC->yfudge - (int)start->y,
						   width, _hoops_PSCIP);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_SHCA _hoops_SCGH 16 _hoops_IGRH _hoops_AHRH.
 */
local void _hoops_PSCGA (
		Net_Rendition const & nr,
		DC_Point const				*start,
		DC_Point const				*end,
		int								row_bytes,
		unsigned short const			*rasters) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		int								width = (int)end->x - (int)start->x + 1;
		int								height = (int)start->y - (int)end->y + 1;
		XImage alter					*_hoops_RSPPGR;
		unsigned short alter			*_hoops_ISSPA;
		unsigned short const			*_hoops_HSGCR;

		_hoops_SIRGS ("draw dc mapped16 rasters", _hoops_RRRPC);

		if (row_bytes == 0)
				row_bytes = width * sizeof(unsigned short);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PHPPGR, _hoops_RRRPC->_hoops_HHPPGR);

		if (height > 1) {
				if (_hoops_RRRPC->_hoops_SIPPGR != null) {
						if (_hoops_RRRPC->_hoops_SIPPGR->bytes_per_line != row_bytes ||
								_hoops_RRRPC->_hoops_SIPPGR->height != height) {
								_hoops_RRRPC->_hoops_SIPPGR->data = null;
								XDestroyImage (_hoops_RRRPC->_hoops_SIPPGR);
								_hoops_RRRPC->_hoops_SIPPGR = null;
								FREE_ARRAY (_hoops_RRRPC->_hoops_ARHPGR,
														_hoops_RRRPC->_hoops_PRHPGR, unsigned short);
								_hoops_RRRPC->_hoops_ARHPGR = null;
								_hoops_RRRPC->_hoops_PRHPGR = 0;
						}
				}
				if (_hoops_RRRPC->_hoops_SIPPGR == null) {
						_hoops_RRRPC->_hoops_SIPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
																								 16, ZPixmap, 0, null, width, height, 16, row_bytes);
						_hoops_RRRPC->_hoops_PRHPGR = row_bytes*height;
						ALLOC_ARRAY (_hoops_RRRPC->_hoops_ARHPGR, _hoops_RRRPC->_hoops_PRHPGR, unsigned short);
				}
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_SIPPGR;
				_hoops_ISSPA = _hoops_RRRPC->_hoops_ARHPGR;
		}
		else {
				_hoops_RSPPGR = _hoops_RRRPC->_hoops_CHPPGR;
				_hoops_ISSPA = _hoops_RRRPC->_hoops_HRHPGR;
		}

		_hoops_RSPPGR->data = (char alter *)_hoops_ISSPA;
		_hoops_RSPPGR->width = width;
		_hoops_RSPPGR->height = height;
		_hoops_RSPPGR->bytes_per_line = row_bytes;
		_hoops_HSGCR = rasters + row_bytes * height;
		_hoops_RGGA (rasters == _hoops_HSGCR)
				*_hoops_ISSPA++ = (unsigned short)_hoops_RRRPC->_hoops_SRPPGR[*rasters++];

		XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PHPPGR,
						   _hoops_RSPPGR, 0, 0, (int)start->x, _hoops_RRRPC->yfudge - (int)start->y,
						   width, height);
}



/****************************************************************
 ****************************************************************
										 _hoops_APCAR _hoops_IHRPR	_hoops_PHGPH _hoops_HRAIA _hoops_RGGIR _hoops_RPRAR _hoops_HRAIA _hoops_SAAAR _hoops_AHGPH _hoops_GHCR
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_ISII.
 */
local void draw_dc_polyline (
		Net_Rendition const		&nr,
		int							count,
		DC_Point const			*points) {
		X11Data alter				*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		bool					_hoops_IRHPGR=false;
		_hoops_GPGGA			_hoops_CRHPGR = _hoops_RHGGA|_hoops_GPHC;

		_hoops_SIRGS ("draw dc polyline", _hoops_RRRPC);

		if (BIT(nr->_hoops_AHP->flags, _hoops_SRPI) ||
			ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ||
			ANYBIT((nr->_hoops_AHP->style&LCAP_MASK), LCAP_COMPLEX_BITS) ||
			(!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) && nr->_hoops_AHP->weight > 2)) {
				HD_Std_DC_Polyline (nr, count, points);
				return;
		}

		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			int i;
			for (i=0;i<Abs(count);i++) {
				if (Abs(points[i].x) > 32000 || Abs(points[i].y) > 32000) {
					_hoops_IRHPGR=true;
					_hoops_CRHPGR |= _hoops_PHGGA;
					break;
				}
			}
		}

		if (_hoops_IRHPGR || nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_CRHPGR);
			return;
		}


		/* _hoops_PPSI _hoops_III _hoops_IPP _hoops_GGR _hoops_RH _hoops_SRHPGR _hoops_RPP _hoops_HGAS */
		if (nr->_hoops_AHP->_hoops_CPA != _hoops_RRRPC->_hoops_SAICC)
				_hoops_AIHSC (nr, nr->_hoops_AHP);
		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_AAPPGR, _hoops_RRRPC->_hoops_GAHPGR);

		if (count > 0) {

				if (count == 2) {
						XDrawLine (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AAPPGR,
										   (short)points[0].x, _hoops_RRRPC->yfudge - (short)points[0].y,
										   (short)points[1].x, _hoops_RRRPC->yfudge - (short)points[1].y);
				}
				else {
					XPoint         *_hoops_HHPAR = _hoops_RRRPC->_hoops_RAHPGR;
					XPoint alter   *vertex;
					DC_Point const *_hoops_CGSAGR;
					int            _hoops_AAHPGR;
					bool           done = false;

					/* _hoops_IPS _hoops_RSSA _hoops_IAPR, _hoops_PAHPGR _hoops_GAR _hoops_SR _hoops_PHHR */
					vertex = _hoops_HHPAR;
					_hoops_CGSAGR = points + count;
					do {
						_hoops_AAHPGR = 0;

						do {
							vertex[_hoops_AAHPGR].x = (short)points->x;
							vertex[_hoops_AAHPGR].y = _hoops_RRRPC->yfudge - (short)points->y;
							++_hoops_AAHPGR;
							if (++points == _hoops_CGSAGR)
								done = true;
						} _hoops_RGGA (_hoops_AAHPGR == (int)_hoops_RRRPC->_hoops_RACSH || done);

						if (!done)
							--points;

						XDrawLines (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AAPPGR, _hoops_HHPAR, _hoops_AAHPGR, CoordModeOrigin);
					} _hoops_RGGA (done);
				}
		}
		else{
				int										_hoops_RRC;

				_hoops_ICHC (count, _hoops_RRC, 2);

				while (count-- > 0) {

						XDrawLine (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AAPPGR,
										   (short)points[0].x, _hoops_RRRPC->yfudge - (short)points[0].y,
										   (short)points[1].x, _hoops_RRRPC->yfudge - (short)points[1].y);

						points += _hoops_RRC;
				}
		}
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_HSSP.
 */
local void _hoops_RPCGA (
		Net_Rendition const & nr,
		int								count,
		DC_Point const				*points) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		XPoint							*_hoops_HHPAR = _hoops_RRRPC->_hoops_RAHPGR;
		XPoint alter					*vertex;
		DC_Point const				*_hoops_CGSAGR;

		_hoops_SIRGS ("draw dc polygon", _hoops_RRRPC);

		if (ANYBIT(nr->_hoops_RHP->line_style->flags, LSF_COMPLEX_ANYBITS) ||
			ANYBIT((nr->_hoops_RHP->style&LCAP_MASK), LCAP_COMPLEX_BITS) ||
			(!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) && nr->_hoops_AHP->weight > 2)) {
				HD_Std_DC_Polygon (nr, count, points);
				return;
		}
		if (nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			HD_Std_DC_Polygon (nr, count, points);
			return;
		}

		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			int i;
			for (i=0;i<Abs(count);i++) {
				if (Abs(points[i].x) > 32000 || Abs(points[i].y) > 32000) {
					HD_Std_DC_Polygon (nr, count-1, points);
					return;
				}
			}
		}

		if (nr->_hoops_IHA->_hoops_CPA != _hoops_RRRPC->_hoops_HPPPGR) {
			if (!(_hoops_RRRPC->_hoops_IAGGS (nr, &nr->_hoops_IHA->color))) {
				HD_Std_DC_Polygon (nr, count-1, points);
				return;
			}
		}
		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PPPPGR, _hoops_RRRPC->_hoops_HAHPGR);

		if (count > (int)_hoops_RRRPC->_hoops_RACSH) {
			HD_Std_DC_Polygon(nr, count, points);
			return;
		}

		/* _hoops_IPS _hoops_RSSA _hoops_IAPR, _hoops_PAHPGR _hoops_GAR _hoops_SR _hoops_PHHR */
		vertex = _hoops_HHPAR;
		_hoops_CGSAGR = points + count;
		do {
				vertex->x = (short)points->x;
				vertex->y = _hoops_RRRPC->yfudge - (short)points->y;
				++vertex;
		} _hoops_RGGA (++points == _hoops_CGSAGR);

		XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
								  _hoops_HHPAR, count-1, Complex, CoordModeOrigin);

		if (nr->_hoops_RHP->_hoops_CPA != _hoops_RRRPC->_hoops_SAICC)
				_hoops_AIHSC (nr, nr->_hoops_RHP);
		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_AAPPGR, _hoops_RRRPC->_hoops_GAHPGR);

		XDrawLines (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AAPPGR,
								_hoops_HHPAR, count, CoordModeOrigin);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_HSP.
 */
local void draw_dc_face (
		Net_Rendition const & nr,
		int						count,
		DC_Point const		*points) {
		X11Data alter			*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		XPoint					*_hoops_HHPAR = _hoops_RRRPC->_hoops_RAHPGR;
		XPoint alter			*vertex;
		DC_Point const		*_hoops_CGSAGR;
		bool				_hoops_IRHPGR=false;
		_hoops_GPGGA		_hoops_CRHPGR = _hoops_RHGGA|_hoops_GPHC;

		_hoops_SIRGS ("draw dc face", _hoops_RRRPC);

		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			int i;
			for (i=0;i<Abs(count);i++) {
				if (Abs(points[i].x) > 32000 || Abs(points[i].y) > 32000) {
					_hoops_IRHPGR=true;
					_hoops_CRHPGR |= _hoops_PHGGA;
					break;
				}
			}
		}

		if (_hoops_IRHPGR || nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			HD_Clip_DC_Face (nr, count, points, 0, _hoops_CRHPGR);
			return;
		}

		if (nr->_hoops_IHA->_hoops_CPA != _hoops_RRRPC->_hoops_HPPPGR) {
			if (!(_hoops_RRRPC->_hoops_IAGGS (nr, &nr->_hoops_IHA->color))) {
				HD_Std_DC_Face (nr, count, points);
				return;
			}
		}
		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PPPPGR, _hoops_RRRPC->_hoops_HAHPGR);

		if (count > (int)_hoops_RRRPC->_hoops_RACSH) {
			HD_Std_DC_Face(nr, count, points);
			return;
		}

		/* _hoops_IPS _hoops_RSSA _hoops_IAPR, _hoops_PAHPGR _hoops_GAR _hoops_SR _hoops_PHHR */
		vertex = _hoops_HHPAR;
		_hoops_CGSAGR = points + count;
		do {
				vertex->x = (short)points->x;
				vertex->y = _hoops_RRRPC->yfudge - (short)points->y;
				++vertex;
		} _hoops_RGGA (++points == _hoops_CGSAGR);

		XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
								  _hoops_HHPAR, count, Complex, CoordModeOrigin);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_IAHPGR.
 */
local void draw_dc_polytriangle (
		Net_Rendition const & nr,
		int								count,
		DC_Point const				*points) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		XPoint alter					*vertex = _hoops_RRRPC->_hoops_RAHPGR;
		int								_hoops_RRC;
		bool						_hoops_IRHPGR=false;
		_hoops_GPGGA				_hoops_CRHPGR = _hoops_RHGGA|_hoops_GPHC;

		_hoops_SIRGS ("draw dc polytriangle", _hoops_RRRPC);

		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			int i;
			for (i=0;i<Abs(count);i++) {
				if (Abs(points[i].x) > 32000 || Abs(points[i].y) > 32000) {
					_hoops_IRHPGR=true;
					_hoops_CRHPGR |= _hoops_PHGGA;
					break;
				}
			}
		}

		if (_hoops_IRHPGR || nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_CRHPGR);
			return;
		}

		if (nr->_hoops_IHA->_hoops_CPA != _hoops_RRRPC->_hoops_HPPPGR) {
				if (!(_hoops_RRRPC->_hoops_IAGGS (nr, &nr->_hoops_IHA->color))) {
						HD_Span_DC_Polytriangle (nr, count, points);
						return;
				}
		}
		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PPPPGR, _hoops_RRRPC->_hoops_HAHPGR);

		_hoops_ICHC (count, _hoops_RRC, 3);

		while (count-- > 0) {
				/* _hoops_IPS _hoops_RSSA _hoops_IAPR, _hoops_PAHPGR _hoops_GAR _hoops_SR _hoops_PHHR */
				vertex[0].x = (short)points[0].x;
				vertex[0].y = _hoops_RRRPC->yfudge - (short)points[0].y;
				vertex[1].x = (short)points[1].x;
				vertex[1].y = _hoops_RRRPC->yfudge - (short)points[1].y;
				vertex[2].x = (short)points[2].x;
				vertex[2].y = _hoops_RRRPC->yfudge - (short)points[2].y;

				XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
										  vertex, 3, Complex, CoordModeOrigin);

				points += _hoops_RRC;
		}
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_HPGCR _hoops_HSP.
 */
local void draw_dc_colorized_face (
		Net_Rendition const &	nr,
		int						count,
		DC_Point const		*points,
		RGBAS32	const		*color) {
		X11Data alter			*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		XPoint					*_hoops_HHPAR = _hoops_RRRPC->_hoops_RAHPGR;
		XPoint alter			*vertex;
		DC_Point const		*_hoops_CGSAGR;
		XGCValues				_hoops_RGPPGR;
		unsigned long			_hoops_SAPPGR;
		int						layer;
		int						_hoops_GCAIR=0;
		int						i;
		unsigned short alter	colors[5];
		int alter				_hoops_AHHIR[5];
		_hoops_CIGA const &	_hoops_SIGA = nr->_hoops_IHA;
		Driver_Color			_hoops_RSISR;
		DC_Point const	   *new_points;
		bool				_hoops_IRHPGR=false;
		_hoops_GPGGA		_hoops_CRHPGR = _hoops_RHGGA|_hoops_GPHC;

		_hoops_SIRGS ("draw dc colorized face", _hoops_RRRPC);

		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			for (i=0;i<Abs(count);i++) {
				if (Abs(points[i].x) > 32000 || Abs(points[i].y) > 32000) {
					_hoops_IRHPGR=true;
					_hoops_CRHPGR |= _hoops_PHGGA;
					break;
				}
			}
		}

		if (_hoops_IRHPGR || nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			HD_Clip_DC_Face (nr, count, points, color, _hoops_CRHPGR);
			return;
		}

		if (count > (int)_hoops_RRRPC->_hoops_RACSH) {
			HD_Std_DC_Colorized_Face(nr, count, points, color);
			return;
		}

		_hoops_RSISR = _hoops_SIGA->color;
		/* _hoops_IPS _hoops_RSSA _hoops_IAPR, _hoops_PAHPGR _hoops_GAR _hoops_SR _hoops_PHHR */
		vertex = _hoops_HHPAR;
		new_points = points;
		_hoops_CGSAGR = new_points + count;
		do {
		   vertex->x = (short)new_points->x;
		   vertex->y = _hoops_RRRPC->yfudge - (short)new_points->y;
		   ++vertex;
		} _hoops_RGGA (++new_points == _hoops_CGSAGR);

		for (i = 0; i < 5; i++)
				_hoops_AHHIR [i] = i;

		if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
				_hoops_RSISR._hoops_HRIR.a = color->a;
				_hoops_RSISR._hoops_HRIR.r = color->r;
				_hoops_RSISR._hoops_HRIR.g = color->g;
				_hoops_RSISR._hoops_HRIR.b = color->b;
				if (!(_hoops_RRRPC->_hoops_IAGGS (nr, &_hoops_RSISR))) {
						HD_Std_DC_Colorized_Face (nr, count, points, color);
						return;
				}
				_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PPPPGR, _hoops_RRRPC->_hoops_HAHPGR);
				XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
										  _hoops_HHPAR, count, Complex, CoordModeOrigin);
		}
		else {
				if (_hoops_SIGA->pattern == FP_USER_DEFINED &&
						_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP) {
						HD_Std_DC_Colorized_Face (nr, count, points, color);
						return;
				}
				if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
								unsigned int _hoops_CAHPGR=(unsigned int)(POINTER_SIZED_INT) color;
								_hoops_RSISR._hoops_PGGCR = (_hoops_GARSR) _hoops_CAHPGR;
				}
				else
				   _hoops_RSISR._hoops_PIHHP = (_hoops_HIHHP) (POINTER_SIZED_INT)color;

				_hoops_GCAIR = HD_Find_Dither_Pattern (nr, color,
																						  colors, _hoops_AHHIR);

				/* _hoops_AA _hoops_SRS _hoops_PGCR _hoops_PSHA _hoops_GGR _hoops_PCCP _hoops_IAAAI _hoops_SAHPGR */

				if (_hoops_GCAIR == 1) {
						_hoops_RGPPGR.fill_style = FillSolid;
						_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[0]];
						XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR,
						   GCFillStyle | GCForeground, &_hoops_RGPPGR);
				}
				else   {
						_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[1]];
						_hoops_RGPPGR.background = _hoops_RRRPC->_hoops_SRPPGR[colors[0]];
						_hoops_RGPPGR.fill_style = FillOpaqueStippled;
						_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_AHHIR[0]];
						XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR,
						   GCFillStyle | GCStipple | GCForeground | GCBackground, &_hoops_RGPPGR);
				}

				_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_AHPPGR, _hoops_RRRPC->_hoops_GPHPGR);

				XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AHPPGR,
										  _hoops_HHPAR, count, Complex, CoordModeOrigin);

				/* _hoops_AA _hoops_RCHAR _hoops_PSHA _hoops_GAR _hoops_IGHP _hoops_AHCCS _hoops_RPHPGR */
				_hoops_RGPPGR.fill_style = FillStippled;
				_hoops_SAPPGR = GCFillStyle | GCStipple | GCForeground;

				for (layer = 2; layer < _hoops_GCAIR; layer++) {
						_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[layer]];
						_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_AHHIR[layer-1]];
						XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR, _hoops_SAPPGR, &_hoops_RGPPGR);

						XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
												  _hoops_RRRPC->_hoops_AHPPGR, _hoops_HHPAR, count, Complex,
												  CoordModeOrigin);
						_hoops_SAPPGR = GCStipple | GCForeground;
				}

				if (_hoops_SIGA->pattern != FP_SOLID) {
						if (!(_hoops_RRRPC->_hoops_RHPPGR (nr, &_hoops_RSISR))) {
								HD_Std_DC_Colorized_Face (nr, count, points, color);
								return;
						}
						XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH,
												  _hoops_RRRPC->_hoops_AHPPGR, _hoops_HHPAR, count, Complex,
												  CoordModeOrigin);
		   }
		}
		_hoops_RRRPC->_hoops_HPPPGR = (_hoops_GARRR)0;
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_PRISP _hoops_PSCGR.
 */
local void draw_dc_colorized_polytriangle (
		Net_Rendition const & nr,
		int								count,
		DC_Point const				*points,
		RGBAS32		const			*_hoops_ASSPA,
		bool						single) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
		Driver_Color					_hoops_RSISR;
		XPoint alter					*vertex = _hoops_RRRPC->_hoops_RAHPGR;
		XGCValues						_hoops_RGPPGR;
		unsigned long					_hoops_SAPPGR;
		int								layer;
		int								_hoops_GCAIR=0;
		unsigned short alter			colors[5];
		int alter						_hoops_AHHIR[5];
		int								i;
		int								_hoops_RRC;
		bool						_hoops_IRHPGR=false;
		_hoops_GPGGA				_hoops_CRHPGR = _hoops_RHGGA|_hoops_GPHC;

		_hoops_SIRGS ("draw dc colorized polytriangle", _hoops_RRRPC);

		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			for (i=0;i<Abs(count);i++) {
				if (Abs(points[i].x) > 32000 || Abs(points[i].y) > 32000) {
					_hoops_IRHPGR=true;
					_hoops_CRHPGR |= _hoops_PHGGA;
					break;
				}
			}
		}

		if (_hoops_IRHPGR || nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			HD_Clip_DC_Polytriangle (nr, count, points, _hoops_ASSPA, 0, 0, 0, 0, 0, _hoops_CRHPGR|
																		(single?_hoops_RAIC:_hoops_PAIC));
			return;
		}

		_hoops_RSISR = _hoops_SIGA->color;

		for (i = 0; i < 5; i++)
				_hoops_AHHIR [i] = i;

		if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {

				_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PPPPGR, _hoops_RRRPC->_hoops_HAHPGR);

				if (single) {
						_hoops_RSISR._hoops_HRIR.a = _hoops_ASSPA->a;
						_hoops_RSISR._hoops_HRIR.r = _hoops_ASSPA->r;
						_hoops_RSISR._hoops_HRIR.g = _hoops_ASSPA->g;
						_hoops_RSISR._hoops_HRIR.b = _hoops_ASSPA->b;

						/* _hoops_RGR _hoops_III _hoops_ARH _hoops_RH _hoops_HAIR */
						if (!(_hoops_RRRPC->_hoops_IAGGS (nr, &_hoops_RSISR))) {
								HD_Span_DC_Colorized_Polytris (nr, count, points, _hoops_ASSPA, single);
								return;
						}
				}

				_hoops_ICHC (count, _hoops_RRC, 3);

				while (count-- > 0) {
						/* _hoops_IPS _hoops_RSSA _hoops_IAPR, _hoops_PAHPGR _hoops_GAR _hoops_SR _hoops_PHHR */
						vertex[0].x = (short)points[0].x;
						vertex[0].y = _hoops_RRRPC->yfudge - (short)points[0].y;
						vertex[1].x = (short)points[1].x;
						vertex[1].y = _hoops_RRRPC->yfudge - (short)points[1].y;
						vertex[2].x = (short)points[2].x;
						vertex[2].y = _hoops_RRRPC->yfudge - (short)points[2].y;

						if (!single) {
								_hoops_RSISR._hoops_HRIR.a = _hoops_ASSPA->a;
								_hoops_RSISR._hoops_HRIR.r = _hoops_ASSPA->r;
								_hoops_RSISR._hoops_HRIR.g = _hoops_ASSPA->g;
								_hoops_RSISR._hoops_HRIR.b = _hoops_ASSPA->b;

								/* _hoops_RGR _hoops_III _hoops_ARH _hoops_RH _hoops_HAIR */
								_hoops_RRRPC->_hoops_IAGGS (nr, &_hoops_RSISR);

								_hoops_ASSPA++;
						}

						XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
										  vertex, 3, Complex, CoordModeOrigin);

						points+=_hoops_RRC;
				}
		}
		else {

				if (_hoops_SIGA->pattern == FP_USER_DEFINED &&
						(_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP ||
						 !_hoops_RRRPC->_hoops_RHPPGR (nr, null))) {
						HD_Span_DC_Colorized_Polytris (nr, count, points, _hoops_ASSPA, single);
						return;
				}

				_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_AHPPGR, _hoops_RRRPC->_hoops_GPHPGR);

				_hoops_ICHC (count, _hoops_RRC, 3);

				if (single) {

						_hoops_GCAIR = HD_Find_Dither_Pattern (nr, _hoops_ASSPA, colors, _hoops_AHHIR);

						if (_hoops_GCAIR == 1) {
								_hoops_RGPPGR.fill_style = FillSolid;
								_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[0]];
								XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR,
								   GCFillStyle | GCForeground, &_hoops_RGPPGR);
						  }
						else   {
								_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[1]];
								_hoops_RGPPGR.background = _hoops_RRRPC->_hoops_SRPPGR[colors[0]];
								_hoops_RGPPGR.fill_style = FillOpaqueStippled;
								_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_AHHIR[0]];
								XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR,
								   GCFillStyle | GCStipple | GCForeground | GCBackground, &_hoops_RGPPGR);
						}
				}

				while (count-- > 0) {
						/* _hoops_IPS _hoops_RSSA _hoops_IAPR, _hoops_PAHPGR _hoops_GAR _hoops_SR _hoops_PHHR */
						vertex[0].x = (short)points[0].x;
						vertex[0].y = _hoops_RRRPC->yfudge - (short)points[0].y;
						vertex[1].x = (short)points[1].x;
						vertex[1].y = _hoops_RRRPC->yfudge - (short)points[1].y;
						vertex[2].x = (short)points[2].x;
						vertex[2].y = _hoops_RRRPC->yfudge - (short)points[2].y;

						if (!single) {

								_hoops_GCAIR = HD_Find_Dither_Pattern (nr, _hoops_ASSPA, colors, _hoops_AHHIR);

								if (_hoops_GCAIR == 1) {
										_hoops_RGPPGR.fill_style = FillSolid;
										_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[0]];
										XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR,
										   GCFillStyle | GCForeground, &_hoops_RGPPGR);
								  }
								else   {
										_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[1]];
										_hoops_RGPPGR.background = _hoops_RRRPC->_hoops_SRPPGR[colors[0]];
										_hoops_RGPPGR.fill_style = FillOpaqueStippled;
										_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_AHHIR[0]];
										XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR,
										   GCFillStyle | GCStipple | GCForeground | GCBackground, &_hoops_RGPPGR);
								}

								_hoops_ASSPA++;
						}

						XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AHPPGR,
												  vertex, 3, Complex, CoordModeOrigin);

						/* _hoops_AA _hoops_RCHAR _hoops_PSHA _hoops_GAR _hoops_IGHP _hoops_AHCCS _hoops_RPHPGR */
						_hoops_RGPPGR.fill_style = FillStippled;
						_hoops_SAPPGR = GCFillStyle | GCStipple | GCForeground;

						for (layer = 2; layer < _hoops_GCAIR; layer++) {
								_hoops_RGPPGR.foreground = _hoops_RRRPC->_hoops_SRPPGR[colors[layer]];
								_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[_hoops_AHHIR[layer-1]];
								XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR, _hoops_SAPPGR, &_hoops_RGPPGR);

								XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AHPPGR,
												vertex, 3, Complex, CoordModeOrigin);
								_hoops_SAPPGR = GCStipple | GCForeground;
						}

						if (_hoops_SIGA->pattern != FP_SOLID) {
								/* _hoops_SR _hoops_HS _hoops_AIAH _hoops_RAICR _hoops_IS _hoops_CACH _hoops_RPP _hoops_HSGP _hoops_PAH _hoops_SHH _hoops_CPHR */
								_hoops_RRRPC->_hoops_RHPPGR (nr, null);
								XFillPolygon (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AHPPGR,
												vertex, 3, Complex, CoordModeOrigin);
				   }

						points+=_hoops_RRC;
				}
		}
		_hoops_RRRPC->_hoops_HPPPGR = (_hoops_GARRR)0;
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_ARRGR.
 */
local void draw_dc_rectangle (
		Net_Rendition const & nr,
		int								left,
		int								right,
		int								bottom,
		int								top) {
		X11Data alter					*_hoops_RRRPC = X11D (nr->_hoops_SRA);

		_hoops_SIRGS ("draw dc rectangle", _hoops_RRRPC);

		if (nr->_hoops_IHA->_hoops_CPA != _hoops_RRRPC->_hoops_HPPPGR) {
				if (!(_hoops_RRRPC->_hoops_IAGGS (nr, &nr->_hoops_IHA->color))) {
						HD_Std_DC_Rectangle (nr, left, right, bottom, top);
						return;
				}
		}
		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_PPPPGR, _hoops_RRRPC->_hoops_HAHPGR);

		XFillRectangle (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
										left, _hoops_RRRPC->yfudge - top, right-left+1, top-bottom+1);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_HCPI.
 */
local void draw_dc_ellipse (
		Net_Rendition const & nr,
		DC_Point const				*where,
		DC_Point const				*radii) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);

		_hoops_SIRGS ("draw dc ellipse", _hoops_RRRPC);

		if (nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
				HD_Std_DC_Ellipse (nr, where, radii);
				return;
		}

		if (nr->_hoops_IHA->_hoops_CPA != _hoops_RRRPC->_hoops_HPPPGR) {
				if (!(_hoops_RRRPC->_hoops_IAGGS (nr, &nr->_hoops_IHA->color))) {
						HD_Std_DC_Ellipse (nr, where, radii);
						return;
				}
		}
		_hoops_CCAPGR(nr, _hoops_RRRPC->_hoops_PPPPGR, _hoops_RRRPC->_hoops_HAHPGR);

		if (_hoops_RRRPC->_hoops_APHPGR == _hoops_PPHPGR)
				/*
				 *		_hoops_IPCP _hoops_ICAPR _hoops_GPAAC _hoops_HHSPC _hoops_SSCP _hoops_IRS _hoops_RIRSC-_hoops_AH _hoops_ARPC _hoops_CCA
				 *		_hoops_HPHPGR _hoops_PIISR _hoops_CHPI - _hoops_CCPCR _hoops_SCH _hoops_IRS _hoops_RSCA.
				 */
				XFillArc (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
								  (int)where->x - (int)radii->x + 1,
								  _hoops_RRRPC->yfudge - (int)where->y - (int)radii->y + 1,
								  2*(int)radii->x + 2, 2*(int)radii->y + 2, 0, 360*64);
		else
				XFillArc (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_PPPPGR,
								  (int)where->x - (int)radii->x,
								  _hoops_RRRPC->yfudge - (int)where->y - (int)radii->y,
								  2*(int)radii->x, 2*(int)radii->y, 0, 360*64);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_RH _hoops_HHGPA _hoops_IIGR _hoops_IRS _hoops_SHCA _hoops_HCPI.
 */
local void _hoops_SCISR (
		Net_Rendition const & nr,
		DC_Point const				*where,
		DC_Point const				*radii) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);

		_hoops_SIRGS ("draw dc outline ellipse", _hoops_RRRPC);

		if (BIT(nr->_hoops_AHP->flags, _hoops_SRPI) ||
			ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ||
			ANYBIT((nr->_hoops_AHP->style&LCAP_MASK), LCAP_COMPLEX_BITS) ||
			(!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) && nr->_hoops_AHP->weight > 2)) {
				HD_Std_DC_Outline_Ellipse (nr, where, radii);
				return;
		}

		if (nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
				HD_Std_DC_Outline_Ellipse (nr, where, radii);
				return;
		}

		if (nr->_hoops_AHP->_hoops_CPA != _hoops_RRRPC->_hoops_SAICC)
				_hoops_AIHSC (nr, nr->_hoops_AHP);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_AAPPGR, _hoops_RRRPC->_hoops_GAHPGR);

		XDrawArc (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AAPPGR,
						  (int)where->x - (int)radii->x,
						  _hoops_RRRPC->yfudge - (int)where->y - (int)radii->y,
						  2*(int)radii->x, 2*(int)radii->y, 0, 360*64);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IRS _hoops_SHCA _hoops_PSCHR.
 */
local void draw_dc_polydot (
		Net_Rendition const & nr,
		int								count,
		DC_Point const				*where) {

		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		Line_Rendition const 		&_hoops_HC = nr->_hoops_AHP;

		_hoops_SIRGS ("draw dc polydot", _hoops_RRRPC);

		if (nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
				HD_Std_DC_Polydot (nr, count, where);
				return;
		}

		if (_hoops_HC->_hoops_CPA != _hoops_RRRPC->_hoops_SAICC)
				_hoops_AIHSC (nr, _hoops_HC);
		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_AAPPGR, _hoops_RRRPC->_hoops_GAHPGR);

		while (count-- > 0) {
				XDrawPoint (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_AAPPGR,
								(int)where->x, _hoops_RRRPC->yfudge - (int)where->y);
				where++;
		}
}

/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_RRRS _hoops_SHCA _hoops_CHIAR (_hoops_HGRAR _hoops_PPR/_hoops_PAR _hoops_SCRPC) _hoops_HCGR
 *		_hoops_SIHH _hoops_GII _hoops_IGRH _hoops_SIHHI.
 */
local void _hoops_IPHPGR (
		Net_Rendition const & nr,
		DC_Point const		*where,
		double					_hoops_HIC,
		int						size,
		int						_hoops_CPHPGR,
		int						_hoops_SPHPGR) {
		X11Data alter			*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
		XGCValues				_hoops_RGPPGR;
		XImage alter			*_hoops_GHHPGR;
		char const				*_hoops_AHRSH;
		char alter				*_hoops_SIRRC;
		int						row, col, bit, _hoops_IPGRP;
		int						_hoops_RHHPGR, _hoops_AHHPGR, _hoops_PHHPGR;
		int						_hoops_IPCRH, _hoops_CPCRH;
		int						width, height, _hoops_HAPPGR;

		_hoops_SIRGS ("draw dc direct transformed text", _hoops_RRRPC);

		/* _hoops_HGHGR _hoops_CCPAR */
		width = size;
		height = size;
		_hoops_HAPPGR = width * height / 8;

		/*
		 *		_hoops_SIPR _hoops_RH _hoops_HCGR _hoops_PSSCI _hoops_PIH _hoops_HII _hoops_RH _hoops_GPAAC _hoops_HHSPC.
		 */
		if ((_hoops_GHHPGR = XGetImage (_hoops_RRRPC->display, _hoops_RRRPC->bitmap, 0, 0,
																 width, height, AllPlanes, ZPixmap)) == null) {
				HE_ERROR (HEC_X11_DRIVER, HES_GETIMAGE_FOR_TEXT_FAILED,
								"X11 Driver: could not get image for drawing transformed text");
				return;
		}
		_hoops_AHRSH = _hoops_GHHPGR->data;
		_hoops_SIRRC = _hoops_RRRPC->_hoops_SIRRC;

		if (ImageByteOrder (_hoops_RRRPC->display) != MSBFirst) {
				/* _hoops_HHHPGR _hoops_RH _hoops_IGRH _hoops_CPCP */
				for (col = 0; col < _hoops_HAPPGR; col++, _hoops_AHRSH++)
						_hoops_SIRRC[col] = HOOPS_READ_ONLY._hoops_SCHGI[_hoops_IRGCR(*_hoops_AHRSH)];
				_hoops_AHRSH = _hoops_SIRRC;
				_hoops_SIRRC = _hoops_GHHPGR->data;
		}
		/* _hoops_GHPA _hoops_RH _hoops_RSIR _hoops_CHIAR _hoops_CRPR */
		SET_MEMORY(_hoops_SIRRC, _hoops_HAPPGR, 0);

		if (_hoops_HRCIR->rotation >= 45.0 && _hoops_HRCIR->rotation < 135.0) {
				/* 90 _hoops_CPSH _hoops_HCGR _hoops_ICSA */

				_hoops_RHHPGR = (height + 7) / 8;
				_hoops_AHHPGR = width - 1;
				bit = 0;

				for (row = 0; row < height; row++) {
						/* _hoops_SRPA _hoops_IH _hoops_RH _hoops_HSAIP */
						_hoops_IPGRP = int (_hoops_HIC * (_hoops_SPHPGR - row));

						for (col = 0; col < width; col++) {
								if (_hoops_RHAPGR(*_hoops_AHRSH, bit++)) {
										_hoops_GHAPGR(_hoops_SIRRC[((_hoops_AHHPGR - col - _hoops_IPGRP) * _hoops_RHHPGR) + row / 8],
												row % 8);
								}
								if (bit > 7) {
										_hoops_AHRSH++;
										bit = 0;
								}
						}
						if (bit > 0) {
								_hoops_AHRSH++;
								bit = 0;
						}
				}

				_hoops_IPCRH = (int)where->x - size + _hoops_SPHPGR;
				_hoops_CPCRH = _hoops_RRRPC->yfudge - (int)where->y - size + _hoops_CPHPGR;
		}
		else if (_hoops_HRCIR->rotation >= 135.0 && _hoops_HRCIR->rotation < 225.0) {
				/* 180 _hoops_CPSH _hoops_HCGR _hoops_ICSA */

				_hoops_RHHPGR = (width + 7) / 8;
				_hoops_PHHPGR = width - 1;
				_hoops_AHHPGR = height - 1;
				bit = 0;

				for (row = 0; row < height; row++) {
						/* _hoops_SRPA _hoops_IH _hoops_RH _hoops_HSAIP */
						_hoops_IPGRP = int (_hoops_HIC * (_hoops_SPHPGR - row));

						for (col = 0; col < width; col++) {
								if (_hoops_RHAPGR(*_hoops_AHRSH, bit++)) {
										_hoops_GHAPGR(_hoops_SIRRC[
												((_hoops_AHHPGR - row) * _hoops_RHHPGR) + (_hoops_PHHPGR - col - _hoops_IPGRP) / 8],
												(_hoops_PHHPGR - col - _hoops_IPGRP) % 8);
								}
								if (bit > 7) {
										_hoops_AHRSH++;
										bit = 0;
								}
						}
						if (bit > 0) {
								_hoops_AHRSH++;
								bit = 0;
						}
				}

				_hoops_IPCRH = (int)where->x - size + _hoops_CPHPGR;
				_hoops_CPCRH = _hoops_RRRPC->yfudge - (int)where->y - _hoops_SPHPGR;
		}
		else if (_hoops_HRCIR->rotation >= 225.0 && _hoops_HRCIR->rotation < 315.0) {
				/* 270 _hoops_CPSH _hoops_HCGR _hoops_ICSA */

				_hoops_RHHPGR = (height + 7) / 8;
				_hoops_AHHPGR = height - 1;
				bit = 0;

				for (row = 0; row < height; row++) {
						/* _hoops_SRPA _hoops_IH _hoops_RH _hoops_HSAIP */
						_hoops_IPGRP = int (_hoops_HIC * (_hoops_SPHPGR - row));

						for (col = 0; col < width; col++) {
								if (_hoops_RHAPGR(*_hoops_AHRSH, bit++)) {
										_hoops_GHAPGR(_hoops_SIRRC[((col + _hoops_IPGRP) * _hoops_RHHPGR) + (_hoops_AHHPGR - row) / 8],
												(_hoops_AHHPGR - row) % 8);
								}
								if (bit > 7) {
										_hoops_AHRSH++;
										bit = 0;
								}
						}
						if (bit > 0) {
								_hoops_AHRSH++;
								bit = 0;
						}
				}

				_hoops_IPCRH = (int)where->x - _hoops_SPHPGR;
				_hoops_CPCRH = _hoops_RRRPC->yfudge - (int)where->y - _hoops_CPHPGR;
		}
		else {
				/* 0 _hoops_CPSH _hoops_HCGR _hoops_ICSA */

				_hoops_RHHPGR = (width + 7) / 8;
				_hoops_AHHPGR = height - 1;
				bit = 0;

				for (row = 0; row < height; row++) {
						/* _hoops_SRPA _hoops_IH _hoops_RH _hoops_HSAIP */
						_hoops_IPGRP = -int (_hoops_HIC * (row - (size-_hoops_SPHPGR)));

						for (col = 0; col < width; col++) {
								if (_hoops_RHAPGR(*_hoops_AHRSH, bit++)) {
										_hoops_GHAPGR(_hoops_SIRRC[(row * _hoops_RHHPGR) + (col + _hoops_IPGRP) / 8], (col + _hoops_IPGRP) % 8);
								}
								if (bit > 7) {
										_hoops_AHRSH++;
										bit = 0;
								}
						}
						if (bit > 0) {
								_hoops_AHRSH++;
								bit = 0;
						}
				}
				_hoops_IPCRH = (int)where->x - _hoops_CPHPGR;
				_hoops_CPCRH = _hoops_RRRPC->yfudge - (int)where->y - size + _hoops_SPHPGR;
		}

		if (ImageByteOrder (_hoops_RRRPC->display) != MSBFirst) {
				_hoops_AHRSH = _hoops_SIRRC;
				_hoops_SIRRC = _hoops_RRRPC->_hoops_SIRRC;

				/* _hoops_HHHPGR _hoops_RH _hoops_IGRH _hoops_CPCP */
				for (col = 0; col < _hoops_HAPPGR; col++, _hoops_AHRSH++)
						_hoops_SIRRC[col] = HOOPS_READ_ONLY._hoops_SCHGI[_hoops_IRGCR(*_hoops_AHRSH)];
		}

		/* _hoops_APSHR _hoops_RHGS _hoops_CSCR _hoops_PIH _hoops_PPR _hoops_IPASR _hoops_CCAH _hoops_CHIAR _hoops_PIH */
		XFree ((caddr_t)_hoops_GHHPGR->data);
		_hoops_GHHPGR->data = _hoops_SIRRC;

		_hoops_RGPPGR.fill_style = FillOpaqueStippled;
		_hoops_RGPPGR.background = 0;
		_hoops_RGPPGR.foreground = 1;

		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IHHPGR,
						   GCFillStyle | GCBackground | GCForeground, &_hoops_RGPPGR);

		XPutImage (_hoops_RRRPC->display, _hoops_RRRPC->bitmap, _hoops_RRRPC->_hoops_IHHPGR,
						   _hoops_GHHPGR, 0, 0, 0, 0, width, height);

		(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, &_hoops_HRCIR->color, null);
		_hoops_RGPPGR.fill_style = FillStippled;
		_hoops_RGPPGR.stipple = _hoops_RRRPC->bitmap;
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CHHPGR,
						   GCFillStyle | GCForeground | GCStipple, &_hoops_RGPPGR);
		_hoops_RRRPC->_hoops_SHHPGR = _hoops_HRCIR->_hoops_CPA;

		_hoops_RGPPGR.ts_x_origin = _hoops_IPCRH % width;
		_hoops_RGPPGR.ts_y_origin = _hoops_CPCRH % height;

		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CHHPGR,
						   GCTileStipXOrigin | GCTileStipYOrigin, &_hoops_RGPPGR);

		_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_CHHPGR, _hoops_RRRPC->_hoops_GIHPGR);

		XFillRectangle (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_CHHPGR,
										_hoops_IPCRH, _hoops_CPCRH, width, height);

		/* _hoops_APSHR _hoops_RH _hoops_GPAAC _hoops_AARSP */
		_hoops_GHHPGR->data = null;
		XDestroyImage (_hoops_GHHPGR);
}


/* _hoops_HGI _hoops_API _hoops_HRS _hoops_PCCP _hoops_RIHPGR _hoops_IIGR _hoops_RH _hoops_GAS _hoops_IACPC, _hoops_RH _hoops_CIS
 * _hoops_PIHA _hoops_CIH _hoops_RH _hoops_GIIA _hoops_RIHPGR _hoops_CCA _hoops_SCH _hoops_HRGR _hoops_PSP _hoops_RPIP _hoops_SIGR _hoops_CCA
 * _hoops_AIHPGR() */
local XImage *
_hoops_PIHPGR (X11Data const * const _hoops_RRRPC,
		_hoops_GSRPC const * _hoops_HIHPGR,
		unsigned short _hoops_IPCSR, float xrrotation, float xrwidth)
{
	/* _hoops_IIHPGR _hoops_CHPP _hoops_RRGC _hoops_HCHSR... */
	unsigned int min_char_or_byte2 = _hoops_HIHPGR->_hoops_HSRPC->min_char_or_byte2;
	unsigned int max_char_or_byte2 = _hoops_HIHPGR->_hoops_HSRPC->max_char_or_byte2;
	unsigned int min_byte1 = _hoops_HIHPGR->_hoops_HSRPC->min_byte1;
	unsigned int max_byte1 = _hoops_HIHPGR->_hoops_HSRPC->max_byte1;
	int lbearing, rbearing, ascent, descent;
	int width, height, size, _hoops_CPHPGR, _hoops_SPHPGR;
	XChar2b _hoops_CIHPGR;
	XGCValues _hoops_RGPPGR;
	XImage *retval;
	int _hoops_SIHPGR;
	Pixmap _hoops_GCHPGR;
	GC _hoops_RCHPGR;

	/* _hoops_HGHGR _hoops_CCPAR */
	lbearing = _hoops_HIHPGR->lbearing;
	rbearing = _hoops_HIHPGR->rbearing;
	ascent = _hoops_HIHPGR->ascent;
	descent = _hoops_HIHPGR->descent;

	width = rbearing - lbearing;
	height = ascent + descent;
	size = _hoops_IAAA (width, height);
	size += (size % 32 ? 32 - (size % 32) : 32);
	_hoops_CPHPGR = 0;
	_hoops_SPHPGR = size - ascent + 1;

	_hoops_GCHPGR = XCreatePixmap (_hoops_RRRPC->display, _hoops_RRRPC->window, size, size, 1);
	_hoops_SIHPGR = size;

	/* _hoops_GHPA _hoops_RH _hoops_HCGR _hoops_PSSCI. */
	_hoops_RGPPGR.fill_style = FillSolid;
	_hoops_RGPPGR.foreground = 0;

	_hoops_RCHPGR = XCreateGC (_hoops_RRRPC->display, _hoops_GCHPGR, GCFillStyle | GCForeground, &_hoops_RGPPGR);

	/* _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_ACHPGR _hoops_GGR _hoops_RH _hoops_APAPC _hoops_AIAH, _hoops_IPS _hoops_IAPR _hoops_RH _hoops_HRCSR _hoops_HII _hoops_SGS _hoops_ACHPGR. */
	if (_hoops_RRRPC->_hoops_IHHPGR)
		XCopyGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IHHPGR, GCFont, _hoops_RCHPGR);

	XFillRectangle (_hoops_RRRPC->display, _hoops_GCHPGR, _hoops_RCHPGR, 0, 0, size, size);

	/* _hoops_GISP _hoops_RH "_hoops_GSSR" _hoops_GAS _hoops_CRGR _hoops_RH _hoops_HCGR _hoops_PSSCI _hoops_GRP _hoops_PCCP
	* _hoops_IAAAI _hoops_PCHPGR _hoops_CISA _hoops_IAHA _hoops_HIS _hoops_HCR _hoops_SIH _hoops_CHR _hoops_ARP _hoops_IS _hoops_PGI
	* 1 _hoops_PAR _hoops_AHHR.
	*/
	_hoops_RGPPGR.fill_style = FillOpaqueStippled;
	_hoops_RGPPGR.background = 0;
	_hoops_RGPPGR.foreground = 1;
	_hoops_RGPPGR.font = _hoops_HIHPGR->_hoops_HSRPC->fid;

	XChangeGC (_hoops_RRRPC->display, _hoops_RCHPGR, GCFillStyle | GCBackground | GCForeground | GCFont, &_hoops_RGPPGR);

	if (min_byte1 || max_byte1) {
		int _hoops_HCHPGR = max_char_or_byte2 - min_char_or_byte2 + 1;
		_hoops_CIHPGR.byte1 = _hoops_IPCSR / _hoops_HCHPGR + min_byte1;
		_hoops_CIHPGR.byte2 = _hoops_IPCSR % _hoops_HCHPGR + min_char_or_byte2;
	} else {
		_hoops_CIHPGR.byte1 = 0;
		_hoops_CIHPGR.byte2 = 0x00FF & _hoops_IPCSR;
	}

	/* _hoops_GISP _hoops_RH _hoops_GAS _hoops_CRGR _hoops_RH _hoops_CRAPGR
	* _hoops_SIPR _hoops_RIHPGR _hoops_HII _hoops_RH _hoops_CRAPGR _hoops_IS _hoops_ASRC _hoops_IS _hoops_RH _hoops_CIS. */
	XDrawImageString16 (_hoops_RRRPC->display, _hoops_GCHPGR, _hoops_RCHPGR, _hoops_CPHPGR, size - _hoops_SPHPGR, &_hoops_CIHPGR, 1);

	retval = XGetImage (_hoops_RRRPC->display, _hoops_GCHPGR, 0, 0, size, size, AllPlanes, ZPixmap);

	/* _hoops_SP _hoops_GH */
	XFreePixmap (_hoops_RRRPC->display, _hoops_GCHPGR);
	XFreeGC (_hoops_RRRPC->display, _hoops_RCHPGR);

	return retval;
}

/* _hoops_HGI _hoops_API _hoops_RSSAR _hoops_IRS _hoops_ICHPGR _hoops_PSSCI _hoops_IIGR _hoops_RH _hoops_GAS '_hoops_IACPC'.
 * _hoops_RAIGR _hoops_GIH _hoops_RSIRR _hoops_IH _hoops_RGR _hoops_API _hoops_SIAS _hoops_SHH _hoops_CCHPGR.  '_hoops_IACPC'
 * _hoops_HRGR _hoops_IRS _hoops_CSPGA _hoops_GAS. */
local _hoops_RAARP *
_hoops_SCHPGR (X11Data const * const _hoops_RRRPC,
		  _hoops_GSRPC const * _hoops_GSHPGR,
		  unsigned short _hoops_IPCSR, float xrrotation, float xrwidth)
{
	_hoops_RAARP *stencil;
	XImage *image;
	int _hoops_RSHPGR;

	/* _hoops_PHAA, _hoops_SRGS _hoops_RH _hoops_GAS _hoops_IS _hoops_PCCP _hoops_RIHPGR, _hoops_PSCR _hoops_RIPHR _hoops_RH _hoops_APSP
	* _hoops_GRP _hoops_RH _hoops_RIHPGR _hoops_SIHC, _hoops_CGHI, _hoops_ARAS _hoops_SPCC _hoops_HAISC _hoops_RH _hoops_APSP.
	*/
	image = _hoops_PIHPGR (_hoops_RRRPC, _hoops_GSHPGR, _hoops_IPCSR, xrrotation, xrwidth);

	if (image) {
		stencil = HI_Clone_Stencil(0);

		_hoops_RSHPGR = image->bytes_per_line * image->height;
		ALLOC_ARRAY (stencil->bitmap, _hoops_RSHPGR, unsigned char);

		stencil->id = _hoops_IPCSR;
		stencil->width = image->width;
		stencil->height = image->height;
		stencil->_hoops_HAARP = image->width + 1;
		stencil->_hoops_IAARP = 0;
		stencil->_hoops_CAARP = 0;
		stencil->_hoops_SAARP = image->height - _hoops_GSHPGR->ascent;
		stencil->_hoops_APARP = image->bytes_per_line;
		stencil->_hoops_PPARP = 1;
		stencil->rotation = 0.0f;
		stencil->width_scale = 1.0f;
		COPY_MEMORY (image->data, _hoops_RSHPGR, stencil->bitmap);

		if (ImageByteOrder (_hoops_RRRPC->display) == LSBFirst) {
			/* _hoops_HHHPGR _hoops_RH _hoops_SIH _hoops_GGR _hoops_RH _hoops_APSP _hoops_GAGHR _hoops_HPP _hoops_GAGHR. */
			int row, col, index;
			for (row = 0; row < stencil->height; ++row) {
				for (col = 0; col < stencil->_hoops_APARP; ++col) {
					index = row * stencil->_hoops_APARP + col;
					stencil->bitmap[index] = HOOPS_READ_ONLY._hoops_SCHGI[stencil->bitmap[index]];
				}
			}
		}

		XDestroyImage (image);
	} else {
		stencil = 0;
	}

	return stencil;
}

local _hoops_RAARP * _hoops_RGSSP (
	Net_Rendition const & nr,
	Font_Instance const	*instance,
	unsigned short			_hoops_IPCSR,
	int						bitmap_height,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth_scale,
	bool				antialias) {
	_hoops_GSRPC alter *_hoops_HIHPGR = (_hoops_GSRPC alter*) instance->_hoops_GAASR;
	X11Data alter *_hoops_RRRPC = X11D(nr->_hoops_SRA);

	return _hoops_SCHPGR (_hoops_RRRPC, _hoops_HIHPGR, _hoops_IPCSR, xrrotation, xrwidth_scale);
}


/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_SHCA _hoops_HCGR.
 */
local void draw_dc_text (
		Net_Rendition const & nr,
		DC_Point const				*where,
		int								count,
		Karacter const				*kstring) {
		X11Data alter					*_hoops_RRRPC = X11D(nr->_hoops_SRA);
		_hoops_IGCSR const			&_hoops_HRCIR = nr->_hoops_SISI;
		_hoops_GSRPC const			*_hoops_HIHPGR;
		_hoops_SIRGS ("draw dc text", _hoops_RRRPC);

		if (nr->transform_rendition->_hoops_HCHH != null ||
			BIT (nr->transform_rendition->flags, _hoops_CSP)) {
				HD_Clip_DC_Text (nr, where, count, kstring);
				return;
		}

		_hoops_HIHPGR = (_hoops_GSRPC const *)_hoops_HRCIR->font->_hoops_GAASR;

		if ((_hoops_HRCIR->rotation >= 45.0 && _hoops_HRCIR->rotation < 315.0) || _hoops_HRCIR->_hoops_IPGRP != 0.0f) {
				XGCValues				_hoops_RGPPGR;
				float					_hoops_GGHCR, _hoops_AGHCR, _hoops_HIC;
				int								lbearing, rbearing, ascent, descent;
				int								width, height, size, _hoops_CPHPGR, _hoops_SPHPGR;

				/*
				 *		_hoops_ASHPGR _hoops_HCGR - _hoops_HGRAR _hoops_PPR/_hoops_PAR _hoops_SCRPC.
				 *
				 *		_hoops_RAAAI _hoops_PPR/_hoops_PAR _hoops_HSAIP _hoops_HCGR _hoops_HPS _hoops_HPP _hoops_HCAPA _hoops_IRS _hoops_PSSCI
				 *		_hoops_IIGR _hoops_GRR _hoops_GAS _hoops_PPR _hoops_PSCR _hoops_IRSHR _hoops_RH _hoops_SIH _hoops_HPP _hoops_RH _hoops_IRPR
				 *		_hoops_GPGR _hoops_IIGR 90 _hoops_ASIPR _hoops_PPR/_hoops_PAR _hoops_HSAIP _hoops_RH _hoops_SIH _hoops_HPP _hoops_RH _hoops_IRPR
				 *		_hoops_PIHHS _hoops_IS _hoops_ARPR _hoops_IRS _hoops_PSSCI _hoops_IIGR _hoops_RH _hoops_HGRAR _hoops_PPR/_hoops_PAR _hoops_SCRPC _hoops_GAS.
				 */

				/* _hoops_HGHGR _hoops_CCPAR */
				lbearing = _hoops_HIHPGR->lbearing;
				rbearing = _hoops_HIHPGR->rbearing;
				ascent = _hoops_HIHPGR->ascent;
				descent = _hoops_HIHPGR->descent;

				/* _hoops_PSIH _hoops_RH _hoops_PIHHS _hoops_IIGR _hoops_RH _hoops_HSAIP */
				if (_hoops_HRCIR->_hoops_IPGRP != 0.0f) {
						_hoops_RICH (_hoops_HRCIR->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
						_hoops_HIC = _hoops_GGHCR / _hoops_AGHCR;
				}
				else
						_hoops_HIC = 0.0f;

				width = rbearing - lbearing + int (Abs(_hoops_HIC) * _hoops_IAAA(ascent, descent));
				height = ascent + descent;
				size = _hoops_IAAA(width, height);
				size += (size % 32 ? 32 - (size % 32) : 32);
				_hoops_CPHPGR = size - rbearing - (_hoops_HIC > 0.0f ? int (_hoops_HIC * _hoops_IAAA(ascent, descent)) : 0);
				_hoops_SPHPGR = size - ascent;

				if (_hoops_RRRPC->bitmap != 0) {
						if (_hoops_RRRPC->_hoops_PSHPGR != size) {
								XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->bitmap);
								_hoops_RRRPC->bitmap = 0;
								FREE_ARRAY (_hoops_RRRPC->_hoops_SIRRC,
														_hoops_RRRPC->_hoops_PSHPGR * _hoops_RRRPC->_hoops_PSHPGR / 8, char);
								_hoops_RRRPC->_hoops_PSHPGR = 0;
								XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IHHPGR);
								_hoops_RRRPC->_hoops_IHHPGR = null;
						}
				}
				if (_hoops_RRRPC->bitmap == 0) {
						_hoops_RRRPC->bitmap = XCreatePixmap (_hoops_RRRPC->display, _hoops_RRRPC->window, size, size, 1);
						_hoops_RRRPC->_hoops_PSHPGR = size;
						ALLOC_ARRAY (_hoops_RRRPC->_hoops_SIRRC, size * size / 8, char);
				}

				/*
				 *		_hoops_GHPA _hoops_RH _hoops_HCGR _hoops_PSSCI.
				 */
				_hoops_RGPPGR.fill_style = FillSolid;
				_hoops_RGPPGR.foreground = 0;
				if (_hoops_RRRPC->_hoops_IHHPGR == null)
						_hoops_RRRPC->_hoops_IHHPGR = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->bitmap,
																						GCFillStyle | GCForeground, &_hoops_RGPPGR);
				else
						XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IHHPGR,
										   GCFillStyle | GCForeground, &_hoops_RGPPGR);
				XFillRectangle (_hoops_RRRPC->display, _hoops_RRRPC->bitmap, _hoops_RRRPC->_hoops_IHHPGR,
												0, 0, size, size);

				/*
				 *		_hoops_GISP _hoops_RH "_hoops_GSSR" _hoops_GAS _hoops_CRGR _hoops_RH _hoops_HCGR _hoops_PSSCI _hoops_GRP _hoops_PCCP
				 *		_hoops_IAAAI _hoops_PCHPGR _hoops_CISA _hoops_IAHA _hoops_HIS _hoops_HCR _hoops_SIH _hoops_CHR _hoops_ARP _hoops_IS _hoops_PGI
				 *		1 _hoops_PAR _hoops_AHHR.
				 */
				_hoops_RGPPGR.fill_style = FillOpaqueStippled;
				_hoops_RGPPGR.background = 0;
				_hoops_RGPPGR.foreground = 1;
				_hoops_RGPPGR.font = _hoops_HIHPGR->_hoops_HSRPC->fid;

				XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IHHPGR,
								   GCFillStyle | GCBackground | GCForeground | GCFont, &_hoops_RGPPGR);

#if 1
				{
						unsigned int min_byte1 = _hoops_HIHPGR->_hoops_HSRPC->min_byte1;
						unsigned int max_byte1 = _hoops_HIHPGR->_hoops_HSRPC->max_byte1;
						unsigned int min_char_or_byte2 = _hoops_HIHPGR->_hoops_HSRPC->min_char_or_byte2;
						unsigned int max_char_or_byte2 = _hoops_HIHPGR->_hoops_HSRPC->max_char_or_byte2;
						int _hoops_HCHPGR = max_char_or_byte2 - min_char_or_byte2 + 1;
						XChar2b _hoops_CIHPGR;

						if (min_byte1 || max_byte1) {
								_hoops_CIHPGR.byte1 = *kstring/_hoops_HCHPGR + min_byte1;
								_hoops_CIHPGR.byte2 = *kstring%_hoops_HCHPGR + min_char_or_byte2;
						}else{
								_hoops_CIHPGR.byte1 = 0;
								_hoops_CIHPGR.byte2 = 0x00FF & *kstring;
						}

						/* _hoops_PGSA _hoops_CRGR _hoops_SCIA _hoops_RPHR _hoops_IIGR _hoops_PSSCI? */
						XDrawString16 (_hoops_RRRPC->display, _hoops_RRRPC->bitmap, _hoops_RRRPC->_hoops_IHHPGR, _hoops_CPHPGR, size-_hoops_SPHPGR, &_hoops_CIHPGR, 1);
				}
#else
				{
						/*_hoops_SIGP _hoops_HASIR _hoops_RGR*/
						char tmp = 0x00FF&*kstring;
						/* _hoops_PGSA _hoops_CRGR _hoops_SCIA _hoops_RPHR _hoops_IIGR _hoops_PSSCI? */
						XDrawString (_hoops_RRRPC->display, _hoops_RRRPC->bitmap, _hoops_RRRPC->_hoops_IHHPGR, _hoops_CPHPGR, size-_hoops_SPHPGR, &tmp, 1);
				}
#endif


				/*
				 *		_hoops_SIPR _hoops_RH _hoops_HCGR _hoops_PSSCI _hoops_PIH _hoops_HII _hoops_RH _hoops_GPAAC _hoops_HHSPC, _hoops_IRSHR
				 *		_hoops_PPR/_hoops_PAR _hoops_HSAIP _hoops_RH _hoops_SIH, _hoops_PPSI _hoops_RH _hoops_HGRAR _hoops_PPR/_hoops_PAR _hoops_SCRPC
				 *		_hoops_HCGR _hoops_PSSCI _hoops_PIH _hoops_GPP _hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_PPR _hoops_SGH _hoops_RH _hoops_HCGR
				 *		_hoops_PSSCI _hoops_GAR _hoops_IRS _hoops_GIPRC _hoops_HSGP _hoops_IS _hoops_CISA _hoops_IRS _hoops_ARRGR.
				 */
				_hoops_IPHPGR (nr, where, (double)_hoops_HIC,
																  size, _hoops_CPHPGR, _hoops_SPHPGR);
		}
		else {

				if (_hoops_HRCIR->_hoops_CPA != _hoops_RRRPC->_hoops_HSHPGR) {
						XGCValues				_hoops_RGPPGR;

						(*_hoops_RRRPC->_hoops_CSASR) (nr, &_hoops_RGPPGR, &_hoops_HRCIR->color, null);
						_hoops_RGPPGR.font = _hoops_HIHPGR->_hoops_HSRPC->fid;
						XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_ISHPGR, GCForeground | GCFont, &_hoops_RGPPGR);
						_hoops_RRRPC->_hoops_HSHPGR = _hoops_HRCIR->_hoops_CPA;
				}
				_hoops_CCAPGR (nr, _hoops_RRRPC->_hoops_ISHPGR, _hoops_RRRPC->_hoops_CSHPGR);

				/*

				_hoops_CGP _hoops_RH _hoops_SSHPGR _hoops_PPR _hoops_GGIPGR _hoops_GIIGGR _hoops_CHR _hoops_GIPR _hoops_AHHR,
				_hoops_RGIPGR _hoops_RIRSP _hoops_RH _hoops_IISGR _hoops_GAS _hoops_CIHA _hoops_ISPCA-
				_hoops_SSRSS _hoops_IS _hoops_RH _hoops_SRS _hoops_CARRA _hoops_IIGR _hoops_RH _hoops_AGIPGR _hoops_CRPR, _hoops_PPR
				_hoops_PGIPGR _hoops_RIRSP _hoops_RH _hoops_IISGR _hoops_GAS _hoops_CIHA _hoops_IIGR _hoops_RH _hoops_CGHI
				_hoops_CARRA.

				_hoops_CGP _hoops_PGI _hoops_SSHPGR _hoops_PAR _hoops_GGIPGR _hoops_CHR _hoops_RRAIA, _hoops_GIPR
				_hoops_RGIPGR _hoops_PPR _hoops_PGIPGR _hoops_CHR _hoops_CRGP _hoops_HSAR 256, _hoops_PPR _hoops_RH
				2-_hoops_RAPSR _hoops_GAS _hoops_CIHA _hoops_HSH _hoops_RSHCR _hoops_IS _hoops_RH _hoops_AGIPGR _hoops_CRPR
				_hoops_CARRA _hoops_PGGIR (_hoops_RPCPR _hoops_HII 0) _hoops_CHR:

				_hoops_HGIPGR = _hoops_PGGIR/_hoops_APCAR + _hoops_SSHPGR
				_hoops_IGIPGR = _hoops_PGGIR\_hoops_APCAR + _hoops_RGIPGR

				_hoops_CAS:

				_hoops_APCAR = _hoops_PGIPGR - _hoops_RGIPGR + 1
				/ = _hoops_HHIPR _hoops_GHAHH
				\ = _hoops_HHIPR _hoops_CGIPGR

				*/

#if 1
				{
						unsigned int min_byte1 = _hoops_HIHPGR->_hoops_HSRPC->min_byte1;
						unsigned int max_byte1 = _hoops_HIHPGR->_hoops_HSRPC->max_byte1;
						unsigned int min_char_or_byte2 = _hoops_HIHPGR->_hoops_HSRPC->min_char_or_byte2;
						unsigned int max_char_or_byte2 = _hoops_HIHPGR->_hoops_HSRPC->max_char_or_byte2;
						int _hoops_HCHPGR = max_char_or_byte2 - min_char_or_byte2 + 1;
						XChar2b _hoops_SGIPGR[1024];
						XChar2b * _hoops_CIHPGR;
						int n = 0;

						if (count>1024)
								_hoops_CIHPGR = (XChar2b*) malloc(count * sizeof(XChar2b));
						else
								_hoops_CIHPGR = _hoops_SGIPGR;

						if (min_byte1 || max_byte1) {
								while (n<count) {
										_hoops_CIHPGR[n].byte1 = kstring[n]/_hoops_HCHPGR + min_byte1;
										_hoops_CIHPGR[n].byte2 = kstring[n]%_hoops_HCHPGR + min_char_or_byte2;
										n++;
								}
						}else{
								while (n<count) {
										_hoops_CIHPGR[n].byte1 = 0;
										_hoops_CIHPGR[n].byte2 = 0x00FF & kstring[n];
										n++;
								}
						}

						XDrawString16 (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_ISHPGR,
												 (int)where->x, _hoops_RRRPC->yfudge - (int)where->y, _hoops_CIHPGR, count);

						if (_hoops_CIHPGR != _hoops_SGIPGR)
								free (_hoops_CIHPGR);
				}
#else
				{
						/*_hoops_SIGP _hoops_HASIR _hoops_RGR*/
						char * _hoops_GRIPGR = malloc (count);
						int n = 0;

						while (n<count) {
								_hoops_GRIPGR[n] = 0x00FF & kstring[n];
								n++;
						}
						XDrawString (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, _hoops_RRRPC->_hoops_ISHPGR,
												 (int)where->x, _hoops_RRRPC->yfudge - (int)where->y, (char *)_hoops_GRIPGR, count);
						free (_hoops_GRIPGR);
				}
#endif
		}
}



/****************************************************************
 ****************************************************************
								  _hoops_RGGIR _hoops_RRGGR _hoops_HRAIA _hoops_AHGPH _hoops_ISAII _hoops_RAIGR _hoops_GHCR	   _hoops_ISAII _hoops_GHAP _hoops_IISGA _hoops_SAAAR
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IIPGR.
 */
local void draw_overlay_list (
		Net_Rendition const & nr) {
		Display_Context const		*dc = nr->_hoops_SRA;
		X11Data alter					*_hoops_RRRPC = X11D(dc);
		XGCValues						_hoops_RGPPGR;

		_hoops_SIRGS ("draw overlay list", _hoops_RRRPC);

		_hoops_RGPPGR.function = GXxor;
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AAPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_ISHPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CHHPGR, GCFunction, &_hoops_RGPPGR);
		_hoops_RRRPC->_hoops_SAICC = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HPPPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HSHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_SHHPGR = (_hoops_GARRR)0;

		HD_Standard_Draw_Overlay_List (nr);

		_hoops_RGPPGR.function = GXcopy;
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AAPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_ISHPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CHHPGR, GCFunction, &_hoops_RGPPGR);
		_hoops_RRRPC->_hoops_SAICC = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HPPPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HSHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_SHHPGR = (_hoops_GARRR)0;
}

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GISP _hoops_IIPGR.
 */
local void _hoops_SCPGR (
		Net_Rendition const & nr)
{
		Display_Context const		*dc = nr->_hoops_SRA;
		X11Data alter					*_hoops_RRRPC = X11D(dc);
		XGCValues						_hoops_RGPPGR;

		_hoops_SIRGS ("draw overlay list", _hoops_RRRPC);

		_hoops_RGPPGR.function = GXxor;
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AAPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_ISHPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CHHPGR, GCFunction, &_hoops_RGPPGR);
		_hoops_RRRPC->_hoops_SAICC = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HPPPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HSHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_SHHPGR = (_hoops_GARRR)0;

		HD_Standard_UnDraw_Overlay_List (nr);

		_hoops_RGPPGR.function = GXcopy;
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AAPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_ISHPGR, GCFunction, &_hoops_RGPPGR);
		XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CHHPGR, GCFunction, &_hoops_RGPPGR);
		_hoops_RRRPC->_hoops_SAICC = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HPPPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HSHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_SHHPGR = (_hoops_GARRR)0;
}



/****************************************************************
 ****************************************************************
						  _hoops_IHRPR _hoops_RGGIR _hoops_ISAII _hoops_RGGIR _hoops_AHGPH _hoops_RPRAR _hoops_RAIGR _hoops_HAICR		 _hoops_RPRAR _hoops_RAIGR _hoops_PGGIR _hoops_RAIGR _hoops_PHGPH _hoops_HRAIA _hoops_RPRAR _hoops_HRAIA _hoops_PGGIR _hoops_SAAAR
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_RAP _hoops_SCGH _hoops_HGIR _hoops_AIRP.
 */
local void _hoops_SCCSR (
		Display_Context const		*dc,
		unsigned int					r,
		unsigned int					g,
		unsigned int					b,
		int								index) {
		X11Data alter					*_hoops_RRRPC = X11D(dc);
		XColor							_hoops_PIHGC;

#ifdef _hoops_CIRGS
		fprintf (stderr, "X11 Sequence: Color map index %d set with (R, G, B) = (%d, %d, %d) %p\n",
					 index, r, g, b, (void*)_hoops_RRRPC);
#endif

		/*
		 *		_hoops_IPCP _hoops_SCPC _hoops_SR _hoops_CHR _hoops_GHGA _hoops_RH _hoops_HSPR _hoops_IGRH _hoops_PARRH _hoops_PPR _hoops_HAPCA _hoops_CAIH
		 *		[_hoops_HAS._hoops_IAS. _hoops_ARRAR _hoops_IRS 16 _hoops_IGRH _hoops_HAIR _hoops_IS 8 _hoops_IGRH _hoops_HAIR] _hoops_HRGR _hoops_PGGA _hoops_AGAH
		 *		_hoops_RRIPGR _hoops_GH _hoops_RPP _hoops_RAGA _hoops_PA _hoops_APPR _hoops_HSAR 256.		 _hoops_IPCP _hoops_GPAAC _hoops_PSHA _hoops_IAGA
		 *		_hoops_HII 0 - 65536 _hoops_PPR _hoops_AGAH _hoops_PSHA _hoops_PHHR _hoops_HII 0 - 255.
		 */
		_hoops_PIHGC.red		 = (r<<8) | r;
		_hoops_PIHGC.green = (g<<8) | g;
		_hoops_PIHGC.blue		 = (b<<8) | b;

		if (_hoops_RRRPC->visual->c_class == StaticColor) {
				if (XAllocColor (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP, &_hoops_PIHGC))
						_hoops_RRRPC->_hoops_SRPPGR[index] = _hoops_PIHGC.pixel;
				else {
						HE_WARNING (HEC_X11_DRIVER, HES_STATICCOLOR_INDEX_FAILED,
										"X11 Driver: Unable to assign a StaticColor index");
						_hoops_RRRPC->_hoops_SRPPGR[index] = _hoops_AHAPGR;
				}
		}
		else if (dc->options._hoops_RCHSR != 0) {
				/*
				 *		_hoops_IIPP _hoops_IRS _hoops_IRIGR-_hoops_RGAR _hoops_ARIPGR _hoops_IH _hoops_RGR _hoops_HAIR _hoops_CR _hoops_RH
				 *		_hoops_IPSP _hoops_SSCP _hoops_RAGA _hoops_IHHH _hoops_IRS _hoops_HGIR _hoops_IS _hoops_SGH _hoops_PPR _hoops_SR _hoops_CHR _hoops_IRIRR
				 *		_hoops_RGR _hoops_HGIR _hoops_PPR _hoops_RGCI _hoops_PRIPGR _hoops_CCA _hoops_RII _hoops_HPHAI.
				 *
				 *		_hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS _hoops_IGI _hoops_RGR _hoops_HGIR _hoops_RARP _hoops_RRHSA.
				 *		_hoops_CGP _hoops_SR _hoops_HS, _hoops_PSCR _hoops_CIH _hoops_RH _hoops_RHGS _hoops_ARIPGR _hoops_ARPP _hoops_ASAAI _hoops_IH _hoops_IRS
				 *		_hoops_CCAH _hoops_ARIPGR.	_hoops_CGP _hoops_SR _hoops_CHR _hoops_RH _hoops_RGAR _hoops_IPSP _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_ARIPGR
				 *		_hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_GRS _hoops_CIH _hoops_SCH _hoops_PPR _hoops_SCH _hoops_GRS _hoops_SHH _hoops_HHPA _hoops_IH _hoops_RPRS
				 *		_hoops_CR _hoops_SR _hoops_PSP _hoops_RPIP _hoops_RRP _hoops_RH _hoops_HAIR _hoops_IPIH _hoops_GCSS _hoops_GGR _hoops_RH _hoops_RHGS
				 *		_hoops_ARIPGR.		_hoops_CGP _hoops_SR _hoops_CHR _hoops_HAR _hoops_RH _hoops_RGAR _hoops_IPSP _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_ARIPGR,
				 *		_hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_GRS _hoops_HAR _hoops_CIH _hoops_SCH.
				 *
				 *		_hoops_PAGA _hoops_SGS _hoops_RH _hoops_RHRIR _hoops_AASHA _hoops_IH _hoops_HAIR _hoops_SGH _hoops_SGS _hoops_IRISR _hoops_RHAP
				 *		_hoops_SSCP _hoops_RPII _hoops_APGP _hoops_GRGR.	_hoops_IRISR _hoops_GRS _hoops_PAHH _hoops_HAR _hoops_HS
				 *		_hoops_PCCP _hoops_CCCI _hoops_HIHA _hoops_IIGR _hoops_RSH _hoops_AHPH _hoops_PSHA _hoops_CHR _hoops_HHPA _hoops_GGR _hoops_RH
				 *		_hoops_HGIR _hoops_PPR _hoops_GRS _hoops_HAR _hoops_SGHHR _hoops_IS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_HGIR _hoops_RPP _hoops_RH
				 *		_hoops_SPR _hoops_RAGA _hoops_IHHH _hoops_HPP _hoops_RH _hoops_IPSP _hoops_HRGR _hoops_IHIR.  _hoops_IPCP _hoops_IPSP _hoops_SSCP _hoops_SHHA _hoops_IHIR
				 *		_hoops_CSSAR _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_RH _hoops_HGIR _hoops_SSCP _hoops_RAPR _hoops_PSHA
				 *		_hoops_HHPA _hoops_HPGR _hoops_HCR _hoops_IACH _hoops_IH _hoops_IRISR _hoops_IS _hoops_SGH.
				 */

				if (_hoops_RRRPC->_hoops_SRPPGR[index] != _hoops_AHAPGR) {
						XFreeColors (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP,
												 &_hoops_RRRPC->_hoops_SRPPGR[index], 1, 0L);
						_hoops_RRRPC->_hoops_SRPPGR[index] = _hoops_AHAPGR;
				}

				if (XAllocColor (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP, &_hoops_PIHGC))
						_hoops_RRRPC->_hoops_SRPPGR[index] = _hoops_PIHGC.pixel;
				else {
						int				i;
						double	_hoops_HRIPGR = 3*65535+1;
						int				_hoops_IRIPGR = WhitePixelOfScreen (_hoops_RRRPC->screen);
						int _hoops_CRIPGR;
						XColor _hoops_SRIPGR[256], *_hoops_GAIPGR;

						if (_hoops_RRRPC->visual->c_class == GrayScale) {
								/* _hoops_CAAA _hoops_RH _hoops_HGGPA _hoops_CRGR _hoops_IRS _hoops_RAIPGR _hoops_PAPA _hoops_IGRSP */
								int _hoops_AAIPGR = (int)((0.5*r) + (0.3*g) + (0.2*b));
								_hoops_PIHGC.red = (_hoops_AAIPGR<<8)|_hoops_AAIPGR;
								_hoops_PIHGC.green = _hoops_PIHGC.blue = _hoops_PIHGC.red;
						}

						/*
						 * _hoops_SGHPC _hoops_RHIR _hoops_HCR _hoops_AIRP _hoops_GGR _hoops_RH _hoops_HAIR _hoops_IHCRH _hoops_IS _hoops_CGIC
						 * _hoops_RH _hoops_PHRHA _hoops_HAIR _hoops_IS _hoops_CARS.  _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_IHGP _hoops_GRGHA _hoops_GIRA
						 * _hoops_RPGP.
						 */
						_hoops_GAIPGR = _hoops_SRIPGR;
						for (i = 0; i < 256; i++)
								_hoops_SRIPGR[i].pixel = (unsigned long)i;

						/* _hoops_SIPR _hoops_RH _hoops_HAIR _hoops_AIRP _hoops_SIHC _hoops_CRGR _hoops_PAIPGR */
						XQueryColors (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP, _hoops_SRIPGR, 256);

						for (i = 0; i < 256; i++, _hoops_GAIPGR++) {
								_hoops_CRIPGR = Abs((int)(_hoops_PIHGC.red - _hoops_GAIPGR->red)) +
														Abs((int)(_hoops_PIHGC.green - _hoops_GAIPGR->green)) +
														Abs((int)(_hoops_PIHGC.blue - _hoops_GAIPGR->blue));
								/* _hoops_AIHH _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_RH _hoops_PHRHA _hoops_HAIR _hoops_HIS _hoops_SGIP */
								if (_hoops_CRIPGR < _hoops_HRIPGR) {
										_hoops_HRIPGR = _hoops_CRIPGR;
										_hoops_IRIPGR = i;
								}
						}
						if (XAllocColor (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP, &_hoops_SRIPGR[_hoops_IRIPGR]))
								_hoops_RRRPC->_hoops_SRPPGR[index] = _hoops_IRIPGR;
						else
						_hoops_PHPGR (HEC_X11_DRIVER, HES_TOO_MANY_COLORS,
										"X11 Driver - Closest Color requested is a read/write color cell",
										"XAllocColor can't allocate");
				}
		}
		else {
				/*
				 *		_hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS _hoops_IGI _hoops_RGR _hoops_HGIR _hoops_RARP _hoops_RRHSA.
				 *		_hoops_CGP _hoops_SR _hoops_SIPGR'_hoops_RA, _hoops_PSCR _hoops_CCPP _hoops_IRS _hoops_CCAH _hoops_ARIPGR _hoops_IH _hoops_RGR _hoops_HAIR.
				 *		_hoops_CGP _hoops_SR _hoops_HS, _hoops_PSCR _hoops_RPRS _hoops_RH _hoops_RHGS _hoops_ARIPGR _hoops_IH _hoops_RGR _hoops_HAIR _hoops_CR
				 *		_hoops_SR _hoops_PSP _hoops_RPIP _hoops_RRP _hoops_RH _hoops_HAIR _hoops_IPIH _hoops_GCSS _hoops_GGR _hoops_RGR _hoops_ARIPGR.
				 */

				if (_hoops_RRRPC->_hoops_SRPPGR[index] == _hoops_AHAPGR) {
						unsigned long	_hoops_HAIPGR;

						if (!XAllocColorCells (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP, False,
																   &_hoops_HAIPGR, 0, &_hoops_RRRPC->_hoops_SRPPGR[index], 1)) {
								if (_hoops_RRRPC->_hoops_GPIHP != _hoops_RRRPC->_hoops_IAIPGR) {
										_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
																		   "X11 Driver - Can't allocate all the colors");
										_hoops_RRRPC->_hoops_SRPPGR[index] = 0;
								}
								else {
										/*
										 *		_hoops_SPCA _hoops_AAPR _hoops_PSP _hoops_RRI _hoops_PRIPGR _hoops_RAAP _hoops_GGR _hoops_SHIR
										 *		_hoops_HGIR.  _hoops_GISA _hoops_IRS _hoops_CCAH _hoops_HGIR _hoops_PPR _hoops_IPS _hoops_RH
										 *		_hoops_PRIPGR _hoops_SR _hoops_HS _hoops_PSPP _hoops_GGR _hoops_RH _hoops_SHIR
										 *		_hoops_HGIR _hoops_IS _hoops_RH _hoops_CCAH _hoops_HGIR _hoops_ARPP _hoops_IGGAR
										 *		_hoops_IRS _hoops_ARIPGR _hoops_IH _hoops_RH _hoops_SCGR _hoops_HAIR.
										 */
										_hoops_RRRPC->_hoops_GPIHP = XCopyColormapAndFree (_hoops_RRRPC->display,
																												  _hoops_RRRPC->_hoops_IAIPGR);

										/*
										 *		_hoops_CAIPGR _hoops_RH _hoops_HGIR _hoops_ACGP _hoops_IS _hoops_ISCP _hoops_RPPS.
										 */
										XSetWindowColormap (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRRPC->_hoops_GPIHP);
#										ifdef X11R3
												_hoops_RRRPC->_hoops_SAIPGR = _hoops_RRRPC->_hoops_GPIPGR;
												if (_hoops_RRRPC->_hoops_SAIPGR)
														XInstallColormap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP);
#										endif /* _hoops_RPIPGR */

										/*
										 *		_hoops_APIPGR _hoops_AASA _hoops_CAIR _hoops_IS _hoops_CCPP _hoops_RH
										 *		_hoops_ARIPGR _hoops_IH _hoops_RH _hoops_SCGR _hoops_HAIR.
										 */
										_hoops_RRRPC->_hoops_SRPPGR[index] = _hoops_AHAPGR;
										_hoops_SCCSR (dc, r, g, b, index);
										return;
								}
						}
				}

				/* _hoops_SAH _hoops_RH _hoops_HAIR */
				_hoops_PIHGC.flags = DoRed | DoGreen | DoBlue;
				_hoops_PIHGC.pixel = _hoops_RRRPC->_hoops_SRPPGR[index];

				XStoreColor (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP, &_hoops_PIHGC);
		}
}



/****************************************************************
 ****************************************************************
								 _hoops_RCCH _hoops_RGGIR _hoops_PGGIR _hoops_SAAAR		_hoops_RPRAR _hoops_RAIGR _hoops_PGGIR _hoops_RAIGR _hoops_PHGPH _hoops_HRAIA _hoops_RPRAR _hoops_HRAIA _hoops_PGGIR _hoops_SAAAR
 ****************************************************************
 ****************************************************************/

#define XLFD_FOUNDRY					0
#define XLFD_FAMILY								1
#define XLFD_WEIGHT								2
#define XLFD_SLANT								3
#define XLFD_SET_WIDTH					4
#define XLFD_ADD_STYLE					5
#define XLFD_PIXEL_SIZE					6
#define XLFD_POINT_SIZE					7
#define XLFD_RESOLUTION_X				8
#define XLFD_RESOLUTION_Y				9
#define XLFD_SPACING					10
#define XLFD_AVERAGE_WIDTH				11
#define XLFD_CHAR_SET					12
#define XLFD_SUB_SET					13
#define XLFD_NUM_FIELDS					14

#define XLFD_MAX_FIELD_SIZE 1024
/*
 *		** _hoops_PGAA **
 *
 */
local int _hoops_PPIPGR (
		char const		*name,
		char alter		_hoops_PSHRS[XLFD_NUM_FIELDS][XLFD_MAX_FIELD_SIZE]) {
		char alter		*fp;
		int						_hoops_HPIPGR;
		int					remaining = 0;
		int					_hoops_IPIPGR = XLFD_NUM_FIELDS - 1;

		if (name[0] == '#')
				return -1;

		_hoops_HPIPGR = XLFD_FOUNDRY;
		fp = &_hoops_PSHRS[_hoops_HPIPGR][0];
		if (*name == '-')
				++name;
		while (*name) {
				if (_hoops_HPIPGR > _hoops_IPIPGR)
						break;
				if (*name == '-') {
						*fp = '\0';
						fp = &_hoops_PSHRS[++_hoops_HPIPGR][0];
				}
				if (_hoops_HPIPGR > _hoops_IPIPGR) {
					break;
				}
				*fp++ = *name++; /* _hoops_CRRPR '-' _hoops_GAR _hoops_SRS _hoops_GSPR _hoops_GGR _hoops_SPS _hoops_PAIP */
		}
		if (_hoops_HPIPGR > _hoops_IPIPGR)
			_hoops_HPIPGR = _hoops_IPIPGR;
		else
			*fp = '\0';

		remaining = _hoops_HPIPGR;
		while (++remaining < _hoops_IPIPGR)
				_hoops_PSHRS[remaining][0] = '\0';

		return _hoops_HPIPGR;
}

/*
 *		** _hoops_PGAA **
 *
 *		_hoops_RGR _hoops_PCPH _hoops_ISPHS _hoops_RH _hoops_RPPCR _hoops_IIGR _hoops_HCR _hoops_RH _hoops_GSPIP _hoops_SGS _hoops_CHR _hoops_GSGI
 *		_hoops_SCPPGR.
 */
local void _hoops_CPIPGR (
		Display_Context alter		*dc,
		char alter * alter					*_hoops_HGPIR,
		int													_hoops_SPIPGR,
		int													_hoops_GHIPGR) {
		X11Data alter							*_hoops_RRRPC = X11D(dc);
		int														remaining = 0;
		/*
		 *		_hoops_HAPR _hoops_RHIR _hoops_HCR _hoops_RH _hoops_CPAPC _hoops_HRCSR _hoops_RPPCR _hoops_IS _hoops_PRIA _hoops_RH _hoops_ARIPR _hoops_IIGR
		 *		_hoops_RRGSP (_hoops_AIIA _hoops_HCR).
		 */
		remaining = _hoops_SPIPGR;
		while (remaining--) {
				char	_hoops_PSHRS[XLFD_NUM_FIELDS][XLFD_MAX_FIELD_SIZE];
				int				_hoops_RHIPGR;

				/*
				 *		_hoops_GPAAC _hoops_HRCSR _hoops_RPPCR _hoops_HS _hoops_GIPSR-_hoops_AHIPGR _hoops_AAAPR _hoops_PPR _hoops_IHSH _hoops_PII:
				 *		 -_hoops_PHIPGR-_hoops_HHIPGR-_hoops_IHIPGR-_hoops_HSAIP-_hoops_CHIPGR-_hoops_SHIPGR-_hoops_GIIPGR-_hoops_RIIPGR-_hoops_AIIPGR-_hoops_PIIPGR-_hoops_SGGGH-_hoops_HIIPGR-_hoops_IIIPGR
				 *		_hoops_IH _hoops_PCAI,
				 *		 -_hoops_CIIPGR-_hoops_IACH-_hoops_AICRC-_hoops_PCCIR-_hoops_GSSR--17-120-100-100-_hoops_CCAHR-84-_hoops_SIIPGR-1"
				 *
				 *		_hoops_CAS:
				 *		_hoops_CIIPGR =			_hoops_GCIPGR _hoops_SGS _hoops_RCIPGR _hoops_PPR _hoops_CARSR _hoops_RH _hoops_HRCSR
				 *		_hoops_IACH =			_hoops_HRCSR _hoops_PCRIP
				 *		_hoops_AICRC =		_hoops_HRCSR _hoops_SGCR (_hoops_ACIPGR, _hoops_AICRC)
				 *		_hoops_PCCIR =						_hoops_HSAIP (_hoops_PCCIR = _hoops_SHISR, _hoops_HAS = _hoops_PCIPGR, _hoops_GCSR = _hoops_GPPCR)
				 *		_hoops_GSSR =		_hoops_ARP _hoops_IGAA (_hoops_HRCSR'_hoops_GRI _hoops_HCIPGR _hoops_IGAA)
				 *		_hoops_GGCR _hoops_IAHA = _hoops_ICIPGR-_hoops_CCIPGR (_hoops_RPP _hoops_GPRI; _hoops_RGAR _hoops_GGR _hoops_RCSR&_hoops_GGHR-_hoops_SCIPGR)
				 *		17 =			_hoops_APPS _hoops_IIGR _hoops_RH _hoops_HRCSR _hoops_GGR _hoops_ASPA
				 *		120 =			_hoops_IGIR _hoops_IIGR _hoops_RH _hoops_HRCSR _hoops_GGR _hoops_GSIPGR _hoops_IIGR _hoops_IRS _hoops_PPSR
				 *		100 =			_hoops_IRGGA _hoops_RAAA _hoops_GGR _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH
				 *		100 =			_hoops_IRPHR _hoops_RAAA _hoops_GGR _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH
				 *		_hoops_CCAHR =						_hoops_SGGGH _hoops_GPRR (_hoops_CCAHR = _hoops_PIAHR, _hoops_SPHAI = _hoops_RSIPGR, _hoops_GSGGR = _hoops_ASIPGR)
				 *		84 =			_hoops_AASHR _hoops_IGAA _hoops_GGR _hoops_GSIPGR _hoops_IIGR _hoops_IRS _hoops_AIR
				 *		_hoops_SIIPGR-1 = _hoops_GAS _hoops_ARP (_hoops_GHAGI _hoops_HHHPP-1)
				 */
				_hoops_RHIPGR = _hoops_PPIPGR (*_hoops_HGPIR, _hoops_PSHRS);

				if (_hoops_RHIPGR < 0) {
						_hoops_HGPIR++;
						continue;
				}

				if (_hoops_RHIPGR == XLFD_NUM_FIELDS - 1) {

						char _hoops_PSIPGR[1024];
						char * _hoops_HSIPGR;
						float _hoops_ISISR;
						float _hoops_IGGGH;

						if (_hoops_AGGR (_hoops_PSHRS[XLFD_PIXEL_SIZE], "-0") &&
								_hoops_AGGR (_hoops_PSHRS[XLFD_POINT_SIZE], "-0") &&
								_hoops_AGGR (_hoops_PSHRS[XLFD_AVERAGE_WIDTH], "-0")) {

								_hoops_HSIPGR = 0;
								_hoops_ISISR = 0.0f;
								_hoops_IGGGH = 1.42f;
						}
						else {
								_hoops_HSIPGR = _hoops_PSIPGR;
								_hoops_ISISR = -1.0f;
								_hoops_IGGGH = -1.0f;

								_hoops_AAHR (_hoops_PSHRS[XLFD_FOUNDRY], _hoops_HSIPGR);
								_hoops_HPRPR (_hoops_PSHRS[XLFD_FAMILY], _hoops_HSIPGR);

								if (!_hoops_AGGR (_hoops_PSHRS[XLFD_WEIGHT], "-medium"))
										_hoops_HPRPR (_hoops_PSHRS[XLFD_WEIGHT], _hoops_HSIPGR);

								if (!_hoops_AGGR (_hoops_PSHRS[XLFD_SLANT], "-r"))
										_hoops_HPRPR (_hoops_PSHRS[XLFD_SLANT], _hoops_HSIPGR);

								if (!_hoops_AGGR (_hoops_PSHRS[XLFD_SET_WIDTH], "-normal"))
										_hoops_HPRPR (_hoops_PSHRS[XLFD_SET_WIDTH], _hoops_HSIPGR);

								if (!_hoops_AGGR (_hoops_PSHRS[XLFD_ADD_STYLE], "-"))
										_hoops_HPRPR (_hoops_PSHRS[XLFD_ADD_STYLE], _hoops_HSIPGR);

								if (!_hoops_AGGR (_hoops_PSHRS[XLFD_RESOLUTION_Y], _hoops_RRRPC->_hoops_ISIPGR))
										_hoops_HPRPR (_hoops_PSHRS[XLFD_RESOLUTION_Y], _hoops_HSIPGR);

								_hoops_HPRPR (_hoops_PSHRS[XLFD_CHAR_SET], _hoops_HSIPGR);
								_hoops_HPRPR (_hoops_PSHRS[XLFD_SUB_SET], _hoops_HSIPGR);
						}

						if (_hoops_AGGR (_hoops_PSHRS[XLFD_CHAR_SET], "-iso8859")&&
										_hoops_AGGR (_hoops_PSHRS[XLFD_SUB_SET], "-1")) {

								HD_Record_Font_With_Encoding(dc, _hoops_HSIPGR, *_hoops_HGPIR, _hoops_SSAIP, _hoops_ISISR, _hoops_IGGGH);
								HD_Mark_Font_As_Transformable (dc, *_hoops_HGPIR, _hoops_GHIPGR);
						}else
						if (_hoops_AGGR (_hoops_PSHRS[XLFD_CHAR_SET], "-iso10646") &&
										_hoops_AGGR (_hoops_PSHRS[XLFD_SUB_SET], "-1")) {

								HD_Record_Font_With_Encoding (dc, _hoops_HSIPGR, *_hoops_HGPIR, _hoops_SACSR, _hoops_ISISR, _hoops_IGGGH);
								HD_Mark_Font_As_Transformable (dc, *_hoops_HGPIR, _hoops_GHIPGR);

#if 0
						}else
						if (_hoops_AGGR (_hoops_PSHRS[XLFD_CHAR_SET], "-jisx0208.1990")) {

								HD_Record_Font_With_Encoding (dc, _hoops_HSIPGR, *_hoops_HGPIR, _hoops_RPHPH, _hoops_ISISR, _hoops_IGGGH);
								HD_Mark_Font_As_Transformable (dc, *_hoops_HGPIR, _hoops_GHIPGR);
#endif
						}else{
								/*_hoops_SIGP _hoops_RRI _hoops_CHGGS*/
								HD_Record_Font (dc, _hoops_HSIPGR, *_hoops_HGPIR, _hoops_ISISR, _hoops_IGGGH);
								HD_Mark_Font_As_Transformable (dc, *_hoops_HGPIR, _hoops_GHIPGR);
						}

				}
				else {
						char					_hoops_HSIPGR[128];
						bool				number;
						char alter				*_hoops_RPPA;
						char alter				*_hoops_PHPSH;

						/*
						 *		_hoops_GPAAC _hoops_GSPIP _hoops_HII _hoops_IARRA _hoops_HSAR _hoops_PPGGR 3 - _hoops_RHGS _hoops_RPCC _hoops_RPPCR.
						 *		_hoops_PAAS _hoops_GGSPR _hoops_RH _hoops_GSPIP _hoops_PCRIP _hoops_RPPCR _hoops_CHR _hoops_SPIP _hoops_GAR
						 *		_hoops_PCRIP-_hoops_SISR, _hoops_IH _hoops_RCHCR:_hoops_CSIPGR,_hoops_SSIPGR,_hoops_GGCPGR  _hoops_CHR _hoops_SPIP
						 *		_hoops_GAR _hoops_PCRIP _hoops_RGCPGR-_hoops_SISR, _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_HRCSR _hoops_RGCPGR _hoops_PAR _hoops_AGCPGR,
						 *		_hoops_SCH _hoops_HRGR _hoops_HSHA _hoops_GAR _hoops_IRS _hoops_HAGH _hoops_PCRIP
						 */
						number = false;
						_hoops_PHPSH = _hoops_HSIPGR;
						for (_hoops_RPPA = *_hoops_HGPIR; *_hoops_RPPA != '\0'; _hoops_RPPA++) {
								switch (*_hoops_RPPA) {
										case '0':
										case '1':
										case '2':
										case '3':
										case '4':
										case '5':
										case '6':
										case '7':
										case '8':
										case '9':
										case '-':
												number = true;
												break;

										default:
												*_hoops_PHPSH++ = *_hoops_RPPA;
												break;
								}
								if (number) {
										*_hoops_PHPSH++ = '-';
										*_hoops_PHPSH++ = 'x';
										break;
								}
						}

						if (_hoops_PHPSH[-1] == '-' || _hoops_PHPSH[-1] == '.')
								*_hoops_PHPSH++ = 'x';

						*_hoops_PHPSH = '\0';

						HD_Record_Font (dc, _hoops_HSIPGR, *_hoops_HGPIR, -1, -1);
						HD_Mark_Font_As_Transformable (dc, *_hoops_HGPIR, _hoops_GHIPGR);
				}

				_hoops_HGPIR++;
		}
}


/*
 *		** _hoops_PGAA **
 *
 *		_hoops_RGR _hoops_PCPH _hoops_ISPHS _hoops_RH _hoops_RSIRR _hoops_RH _hoops_HRCSR _hoops_HGRC
 */
local bool _hoops_PGCPGR (
	Display_Context alter		*dc,
	char const						*name) {
	X11Data alter					*_hoops_RRRPC = X11D(dc);
	char alter						* alter *_hoops_HGPIR;
	char alter						* alter *_hoops_HGCPGR;
	float							_hoops_AGACA;
	float							_hoops_PGACA;
	int								_hoops_SPIPGR = 0;
	int								_hoops_GHIPGR;

	_hoops_CPAPGR ("record basic fonts", _hoops_RRRPC);

	/*
	 * _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_SGGHA _hoops_RH _hoops_IIIGC _hoops_RHPP _hoops_RRGI _hoops_GPAAC _hoops_GPP _hoops_ICAPR,
	 * _hoops_PSCR _hoops_GRRRI _hoops_GSPIP _hoops_CHR _hoops_HAR _hoops_HHPA.
	 */
	_hoops_GHIPGR = _hoops_IAGGH;
#ifdef AIX_SYSTEM
	if (_hoops_IGGPA (dc->_hoops_PGCC.driver_type, "gl") ||
		_hoops_RRRPC->driver_type == _hoops_PPAPC)
		_hoops_GHIPGR = _hoops_CRGGH;
#endif

	/*
	 *		_hoops_HGCR _hoops_RH _hoops_RAAA _hoops_SIHC _hoops_IH _hoops_RGR _hoops_AIRI.
	 */
	_hoops_AGACA = dc->current._hoops_HAP.x;
	_hoops_PGACA = dc->current._hoops_HAP.y;

	if ((_hoops_PGACA < 35.0) || (_hoops_AGACA < 35.0))
		/* 75 _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH */
		_hoops_AAHR ("-75", _hoops_RRRPC->_hoops_ISIPGR);
	else
		/* 100 _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH */
		_hoops_AAHR ("-100", _hoops_RRRPC->_hoops_ISIPGR);

	/*
	 *		_hoops_HGCR _hoops_RH _hoops_CPAPC _hoops_HRCSR _hoops_RPPCR
	 */
	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display,name, _hoops_PPAPGR, &_hoops_SPIPGR);

	if (_hoops_HGPIR != null) {
		_hoops_HGCPGR = _hoops_HGPIR;
		_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
		XFreeFontNames (_hoops_HGCPGR);
		return true;
	}
	else
		return false;
}


/* _hoops_HGI _hoops_API _hoops_ARH _hoops_SHIR _hoops_PPR _hoops_PHIGR _hoops_GSPIP. */
local void
_hoops_IGCPGR (Display_Context alter * dc)
{
	const char * const _hoops_CGCPGR[] = {
		"-bitstream-bitstream vera sans-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-monotype-arial-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-helvetica-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-val-free serif-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-helvetica-medium-r-normal--0-0-100-100-p-0-iso10646-1",
		"-adobe-helvetica-medium-r-normal--0-0-75-75-p-0-iso10646-1",
		"-b&h-luxi sans-medium-r-normal--0-0-0-0-p-0-iso10646-1",

		"-bitstream-bitstream vera sans-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-monotype-arial-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-helvetica-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-val-free serif-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-helvetica-medium-r-normal--0-0-100-100-p-0-iso8859-1",
		"-adobe-helvetica-medium-r-normal--0-0-75-75-p-0-iso8859-1",
		"-b&h-luxi sans-medium-r-normal--0-0-0-0-p-0-iso8859-1",

		"adobe-helvetica-0-iso10646-1",
		"adobe-helvetica-100-iso10646-1",
		"adobe-helvetica-75-iso10646-1",
		"helvetica-iso10646-1",
		"adobe-helvetica-iso8859-1",
		"adobe-helvetica-100-iso8859-1",
		"adobe-helvetica-75-iso8859-1",
		"helvetica-iso8859-1",
	};
	const char * const _hoops_SGCPGR[] = {
		"-adobe-helvetica-bold-r-*-*-0-0-*-*-*-0-*-*",
		"-adobe-helvetica-bold-r-normal-*-*-*-*-*-*-*-*-*",
		"-bitstream-bitstream vera sans-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-monotype-arial-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-helvetica-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-val-free serif-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-helvetica-bold-r-normal--0-0-100-100-p-0-iso10646-1",
		"-adobe-helvetica-bold-r-normal--0-0-75-75-p-0-iso10646-1",
		"-b&h-luxi sans-bold-r-normal--0-0-0-0-p-0-iso10646-1",

		"-bitstream-bitstream vera sans-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-monotype-arial-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-helvetica-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-val-free serif-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-helvetica-bold-r-normal--0-0-100-100-p-0-iso8859-1",
		"-adobe-helvetica-bold-r-normal--0-0-75-75-p-0-iso8859-1",
		"-b&h-luxi sans-bold-r-normal--0-0-0-0-p-0-iso8859-1",

		"adobe-helvetica-0-iso10646-1",
		"adobe-helvetica-100-iso10646-1",
		"adobe-helvetica-75-iso10646-1",
		"helvetica-iso10646-1",
		"adobe-helvetica-iso8859-1",
		"adobe-helvetica-100-iso8859-1",
		"adobe-helvetica-75-iso8859-1",
		"helvetica-iso8859-1",
	};
	const char * const _hoops_GRCPGR[] = {
		"-bitstream-courier-medium-r-normal--0-0-0-0-m-0-iso10646-1",
		"-bitstream-courier 10 pitch-medium-r-normal--0-0-0-0-m-0-iso10646-1",
		"-monotype-courier new-medium-r-normal--0-0-0-0-m-0-iso10646-1",
		"-adobe-courier-medium-r-normal--0-0-0-0-m-0-iso10646-1",
		"-val-free courier-medium-r-normal--0-0-0-0-m-0-iso10646-1",
		"-adobe-courier-medium-r-normal--0-0-100-100-m-0-iso10646-1",
		"-adobe-courier-medium-r-normal--0-0-75-75-m-0-iso10646-1",
		"-b&h-luxi mono-medium-r-normal--0-0-0-0-m-0-iso10646-1",

		"-bitstream-courier-medium-r-normal--0-0-0-0-m-0-iso8859-1",
		"-bitstream-courier 10 pitch-medium-r-normal--0-0-0-0-m-0-iso8859-1",
		"-monotype-courier new-medium-r-normal--0-0-0-0-m-0-iso8859-1",
		"-adobe-courier-medium-r-normal--0-0-0-0-m-0-iso8859-1",
		"-val-free courier-medium-r-normal--0-0-0-0-m-0-iso8859-1",
		"-adobe-courier-medium-r-normal--0-0-100-100-m-0-iso8859-1",
		"-adobe-courier-medium-r-normal--0-0-75-75-m-0-iso8859-1",
		"-b&h-luxi mono-medium-r-normal--0-0-0-0-m-0-iso8859-1",

		"adobe-courier-iso10646-1",
		"adobe-courier-100-iso10646-1",
		"adobe-courier-75-iso10646-1",
		"courier-iso10646-1",
		"adobe-courier-iso8859-1",
		"adobe-courier-100-iso8859-1",
		"adobe-courier-75-iso8859-1",
		"courier-iso8859-1",
	};
	const char * const _hoops_RRCPGR[] = {
		"-bitstream-courier-bold-r-normal--0-0-0-0-m-0-iso10646-1",
		"-bitstream-courier 10 pitch-bold-r-normal--0-0-0-0-m-0-iso10646-1",
		"-monotype-courier new-bold-r-normal--0-0-0-0-m-0-iso10646-1",
		"-adobe-courier-bold-r-normal--0-0-0-0-m-0-iso10646-1",
		"-val-free courier-bold-r-normal--0-0-0-0-m-0-iso10646-1",
		"-adobe-courier-bold-r-normal--0-0-100-100-m-0-iso10646-1",
		"-adobe-courier-bold-r-normal--0-0-75-75-m-0-iso10646-1",
		"-b&h-luxi mono-bold-r-normal--0-0-0-0-m-0-iso10646-1",

		"-bitstream-courier-bold-r-normal--0-0-0-0-m-0-iso8859-1",
		"-bitstream-courier 10 pitch-bold-r-normal--0-0-0-0-m-0-iso8859-1",
		"-monotype-courier new-bold-r-normal--0-0-0-0-m-0-iso8859-1",
		"-adobe-courier-bold-r-normal--0-0-0-0-m-0-iso8859-1",
		"-val-free courier-bold-r-normal--0-0-0-0-m-0-iso8859-1",
		"-adobe-courier-bold-r-normal--0-0-100-100-m-0-iso8859-1",
		"-adobe-courier-bold-r-normal--0-0-75-75-m-0-iso8859-1",
		"-b&h-luxi mono-bold-r-normal--0-0-0-0-m-0-iso8859-1",

		"adobe-courier-iso10646-1",
		"adobe-courier-100-iso10646-1",
		"adobe-courier-75-iso10646-1",
		"courier-iso10646-1",
		"adobe-courier-iso8859-1",
		"adobe-courier-100-iso8859-1",
		"adobe-courier-75-iso8859-1",
	};
	const char * const _hoops_ARCPGR[] = {
		"-bitstream-bitstream vera serif-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-monotype-times new roman-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-times-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-val-free times-medium-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-times-medium-r-normal--0-0-100-100-p-0-iso10646-1",
		"-adobe-times-medium-r-normal--0-0-75-75-p-0-iso10646-1",
		"-b&h-luxi serif-medium-r-normal--0-0-0-0-p-0-iso10646-1",

		"-bitstream-bitstream vera serif-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-monotype-times new roman-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-times-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-val-free times-medium-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-times-medium-r-normal--0-0-100-100-p-0-iso8859-1",
		"-adobe-times-medium-r-normal--0-0-75-75-p-0-iso8859-1",
		"-b&h-luxi serif-medium-r-normal--0-0-0-0-p-0-iso8859-1",

		"adobe-times-iso10646-1",
		"adobe-times-100-iso10646-1",
		"adobe-times-75-iso10646-1",
		"times-iso10646-1",
		"adobe-times-iso8859-1",
		"adobe-times-100-iso8859-1",
		"adobe-times-75-iso8859-1",
		"times-iso8859-1",
	};
	const char * const _hoops_PRCPGR[] = {
		"-bitstream-bitstream vera serif-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-monotype-times new roman-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-times-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-val-free times-bold-r-normal--0-0-0-0-p-0-iso10646-1",
		"-adobe-times-bold-r-normal--0-0-100-100-p-0-iso10646-1",
		"-adobe-times-bold-r-normal--0-0-75-75-p-0-iso10646-1",
		"-b&h-luxi serif-bold-r-normal--0-0-0-0-p-0-iso10646-1",

		"-bitstream-bitstream vera serif-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-monotype-times new roman-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-times-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-val-free times-bold-r-normal--0-0-0-0-p-0-iso8859-1",
		"-adobe-times-bold-r-normal--0-0-100-100-p-0-iso8859-1",
		"-adobe-times-bold-r-normal--0-0-75-75-p-0-iso8859-1",
		"-b&h-luxi serif-bold-r-normal--0-0-0-0-p-0-iso8859-1",

		"adobe-times-iso10646-1",
		"adobe-times-100-iso10646-1",
		"adobe-times-75-iso10646-1",
		"times-iso10646-1",
		"adobe-times-iso8859-1",
		"adobe-times-100-iso8859-1",
		"adobe-times-75-iso8859-1",
		"times-iso8859-1",
	};
	size_t i;

	/* _hoops_AGGA _hoops_HPGGR _hoops_RH _hoops_IRISR _hoops_CHPPR _hoops_HRGSI _hoops_HRCPGR.  _hoops_SGPR _hoops_RH _hoops_GPAAC _hoops_HRCSR _hoops_PCRIP
	* _hoops_RPPCR _hoops_SGS _hoops_PSSP _hoops_RH _hoops_RHAR _hoops_CSIIR _hoops_SR _hoops_CHR _hoops_HCHAR _hoops_IH.
	* _hoops_PS _hoops_CHR _hoops_SHR _hoops_HCHAR _hoops_IH _hoops_AICRC _hoops_SGCR, _hoops_SHISR _hoops_HSAIP, _hoops_GSSR _hoops_ARP
	* _hoops_IGAA, _hoops_PPR _hoops_GHAGI _hoops_HHHPP-1 _hoops_GAS _hoops_ARP _hoops_GSPIP.
	*/

	/* _hoops_ACGR _hoops_RH _hoops_IRISR _hoops_CHPPR "_hoops_IRCPGR _hoops_CRCPGR" _hoops_HRCSR.  _hoops_PS _hoops_CHR _hoops_HCHAR _hoops_IH
	* _hoops_AHISC _hoops_GGR _hoops_RH _hoops_IRPR _hoops_RAAA _hoops_IH _hoops_RGR _hoops_AIRI.
	* _hoops_SGHPC _hoops_IAPR _hoops_RH _hoops_CRPR _hoops_IIGR _hoops_SSRR _hoops_GSPIP.  _hoops_RRHPC _hoops_SPR _hoops_HRGR _hoops_ARP, _hoops_IHSA
	* _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_HAPR.
	*/

	for (i = 0; i < sizeof(_hoops_CGCPGR)/sizeof(char*); ++i) {
		if (HD_Mark_Font_As_Generic (dc, _hoops_CGCPGR[i], GFN_SANS_SERIF)) {
			break;
		}
	}

	for (i = 0; i < sizeof(_hoops_SGCPGR)/sizeof(char*); ++i) {
		if (HD_Mark_Font_As_Generic (dc, _hoops_SGCPGR[i], _hoops_GIIGI)) {
			break;
		}
	}

	/* _hoops_ACGR _hoops_RH _hoops_IRISR _hoops_CHPPR "_hoops_SRCPGR" _hoops_HRCSR.  _hoops_PS _hoops_CHR _hoops_HCHAR _hoops_IH
	* _hoops_RHISC _hoops_GGR _hoops_RH _hoops_IRPR _hoops_RAAA _hoops_IH _hoops_RGR _hoops_AIRI.
	*/
	for (i = 0; i < sizeof(_hoops_GRCPGR)/sizeof(char*); ++i) {
		if (HD_Mark_Font_As_Generic (dc, _hoops_GRCPGR[i], GFN_TYPEWRITER)) {
			break;
		}
	}
	for (i = 0; i < sizeof(_hoops_RRCPGR)/sizeof(char*); ++i) {
		if (HD_Mark_Font_As_Generic (dc, _hoops_RRCPGR[i], _hoops_RIIGI)) {
			break;
		}
	}

	/* _hoops_ACGR _hoops_RH _hoops_IRISR _hoops_CHPPR "_hoops_RCCGI" _hoops_HRCSR.  _hoops_PS _hoops_CHR _hoops_HCHAR _hoops_IH _hoops_CCISC
	* _hoops_GGR _hoops_RH _hoops_IRPR _hoops_RAAA _hoops_IH _hoops_RGR _hoops_AIRI.
	*/
	for (i = 0; i < sizeof(_hoops_ARCPGR)/sizeof(char*); ++i) {
		if (HD_Mark_Font_As_Generic (dc, _hoops_ARCPGR[i], GFN_ROMAN)) {
			break;
		}
	}
	for (i = 0; i < sizeof(_hoops_PRCPGR)/sizeof(char*); ++i) {
		if (HD_Mark_Font_As_Generic (dc, _hoops_PRCPGR[i], _hoops_AIIGI)) {
			break;
		}
	}

#if 0
	/* _hoops_ACGR _hoops_RH _hoops_IRISR _hoops_AAACI _hoops_SGAA _hoops_HRCSR.		 _hoops_PS _hoops_CHR _hoops_HCHAR _hoops_IH _hoops_RH _hoops_HRCSR
	* _hoops_PAPR _hoops_GAR _hoops_GACPGR (_hoops_HCAGR "9x15", _hoops_RH _hoops_PSGP 9x15 _hoops_HRCSR) _hoops_GGR
	* _hoops_RH _hoops_IRPR _hoops_RAAA _hoops_IH _hoops_RGR _hoops_AIRI.
	*/
#define _hoops_RACPGR					"9x15"
	if (!HD_Mark_Font_As_System_Default (dc, _hoops_RACPGR, -1)) {
		/* _hoops_AACPGR'_hoops_RA _hoops_SSS _hoops_SCH; _hoops_HPPR _hoops_HPIH _hoops_RSIRR _hoops_IH _hoops_IRS _hoops_RPIHR _hoops_HRCSR.
		* _hoops_CGP _hoops_SR _hoops_GA'_hoops_RA _hoops_SSS _hoops_SCH _hoops_RGR _hoops_GHIR _hoops_RH _hoops_IPSP _hoops_SAGGR _hoops_RH _hoops_IRISR
		* _hoops_AGPAA-_hoops_GGR _hoops_RGCGGR _hoops_PACPGR _hoops_HRCSR _hoops_IH _hoops_AAACI _hoops_SGAA.
		*/
		(void)HD_Mark_Font_As_System_Default (dc, "fixed", -1);
	}
#endif
	return;
}


/*
 *		** _hoops_PGAA **
 *
 *		_hoops_RGR _hoops_PCPH _hoops_ISPHS _hoops_RH _hoops_RPPCR _hoops_IIGR _hoops_HCR _hoops_RH _hoops_GSPIP _hoops_HHPA _hoops_IS _hoops_RH _hoops_CPAPC
 *		_hoops_SCPPGR.
 */
local void _hoops_HACPGR (
	Display_Context alter		*dc) {
	X11Data alter					*_hoops_RRRPC = X11D(dc);
	char alter						* alter *_hoops_HGPIR;
	char alter						* alter *_hoops_HGCPGR;
	float							_hoops_AGACA;
	float							_hoops_PGACA;
	int								_hoops_SPIPGR = 0;
	int								_hoops_GHIPGR;

	_hoops_CPAPGR ("record basic fonts", _hoops_RRRPC);

	/*
	 * _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_SGGHA _hoops_RH _hoops_IIIGC _hoops_RHPP _hoops_RRGI _hoops_GPAAC _hoops_GPP _hoops_ICAPR,
	 * _hoops_PSCR _hoops_GRRRI _hoops_GSPIP _hoops_CHR _hoops_HAR _hoops_HHPA.
	 */
	_hoops_GHIPGR = _hoops_IAGGH;
#ifdef AIX_SYSTEM
	if (_hoops_IGGPA (dc->_hoops_PGCC.driver_type, "gl") ||
		_hoops_RRRPC->driver_type == _hoops_PPAPC)
		_hoops_GHIPGR = _hoops_CRGGH;
#endif

	/*
	 *		_hoops_HGCR _hoops_RH _hoops_RAAA _hoops_SIHC _hoops_IH _hoops_RGR _hoops_AIRI.
	 */
	_hoops_AGACA = dc->current._hoops_HAP.x;
	_hoops_PGACA = dc->current._hoops_HAP.y;

	if ((_hoops_PGACA < 35.0) || (_hoops_AGACA < 35.0))
		/* 75 _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH */
		_hoops_AAHR ("-75", _hoops_RRRPC->_hoops_ISIPGR);
	else
		/* 100 _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH */
		_hoops_AAHR ("-100", _hoops_RRRPC->_hoops_ISIPGR);

	/*
	 *		_hoops_HGCR _hoops_RH _hoops_CPAPC _hoops_HRCSR _hoops_RPPCR
	 */

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*monotype*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*bitstream*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*adobe*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*b&h*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*val*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*times*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*timrom*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*-cor*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*courier*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*helv*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*DEFAULT*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*fixed*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);
	XFreeFontNames (_hoops_HGCPGR);

	_hoops_IGCPGR(dc);
	return;
}


/*
 *		** _hoops_PGAA **
 *
 *		_hoops_RGR _hoops_PCPH _hoops_ISPHS _hoops_RH _hoops_RPPCR _hoops_IIGR _hoops_HCR _hoops_RH _hoops_GSPIP _hoops_HHPA _hoops_IS _hoops_RH _hoops_CPAPC
 *		_hoops_SCPPGR.
 */
local void _hoops_IACPGR (
	Display_Context alter	*dc) {
	X11Data alter				*_hoops_RRRPC = X11D(dc);
	char alter					* alter *_hoops_HGPIR;
	char alter					* alter *_hoops_HGCPGR;
	float						_hoops_AGACA;
	float						_hoops_PGACA;
	int							_hoops_SPIPGR = 0;
	int							_hoops_GHIPGR;

	_hoops_CPAPGR ("record x11 fonts", _hoops_RRRPC);

	/*
	 * _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_SGGHA _hoops_RH _hoops_IIIGC _hoops_RHPP _hoops_RRGI _hoops_GPAAC _hoops_GPP _hoops_ICAPR,
	 * _hoops_PSCR _hoops_GRRRI _hoops_GSPIP _hoops_CHR _hoops_HAR _hoops_HHPA.
	 */
	_hoops_GHIPGR = _hoops_IAGGH;
#ifdef AIX_SYSTEM
	if (_hoops_IGGPA (dc->_hoops_PGCC.driver_type, "gl") ||
		_hoops_RRRPC->driver_type == _hoops_PPAPC)
		_hoops_GHIPGR = _hoops_CRGGH;
#endif

	/*
	 *		_hoops_HGCR _hoops_RH _hoops_RAAA _hoops_SIHC _hoops_IH _hoops_RGR _hoops_AIRI.
	 */
	_hoops_AGACA = dc->current._hoops_HAP.x;
	_hoops_PGACA = dc->current._hoops_HAP.y;

	if ((_hoops_PGACA < 35.0) || (_hoops_AGACA < 35.0))
		/* 75 _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH */
		_hoops_AAHR ("-75", _hoops_RRRPC->_hoops_ISIPGR);
	else
		/* 100 _hoops_PAGAI-_hoops_RIR-_hoops_CPIHH */
		_hoops_AAHR ("-100", _hoops_RRRPC->_hoops_ISIPGR);

	/*
	 *		_hoops_HGCR _hoops_RH _hoops_CPAPC _hoops_HRCSR _hoops_RPPCR
	 */
	_hoops_HGPIR = XListFonts (_hoops_RRRPC->display, "*", _hoops_PPAPGR, &_hoops_SPIPGR);
	_hoops_HGCPGR = _hoops_HGPIR;
	_hoops_CPIPGR (dc, _hoops_HGPIR, _hoops_SPIPGR, _hoops_GHIPGR);

	XFreeFontNames (_hoops_HGCPGR);
}




/*
 *		** _hoops_SRAC **
 *
 *		_hoops_ACGR _hoops_HCR _hoops_GPAAC _hoops_GSPIP _hoops_HHPA _hoops_GPP _hoops_RH _hoops_GPAAC _hoops_HHSPC.	 _hoops_HGI _hoops_PCPH _hoops_HCPH
 *		_hoops_PGCR _hoops_RII _hoops_SICAR _hoops_HIS _hoops_SGS _hoops_RII _hoops_GRRGI _hoops_SGS _hoops_ARAS _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_GPAAC _hoops_PPR
 *		_hoops_CACPGR _hoops_IS _hoops_SGH _hoops_RH _hoops_GSPIP _hoops_HHPA _hoops_IS _hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_GHCA _hoops_AA _hoops_HIS.
 */
local void find_all_fonts (
	Display_Context alter	*dc) {
	X11Data alter				*_hoops_RRRPC = X11D(dc);

	(*_hoops_RRRPC->_hoops_IACPGR) (dc);
}

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_ACGR  _hoops_CHARP _hoops_SACPGR _hoops_GSPIP _hoops_HHPA _hoops_GPP _hoops_RH _hoops_GPAAC _hoops_HHSPC.	_hoops_HGI _hoops_PCPH _hoops_HCPH
 *		_hoops_PGCR _hoops_RII _hoops_SICAR _hoops_HIS _hoops_SGS _hoops_RII _hoops_GRRGI _hoops_SGS _hoops_ARAS _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_GPAAC _hoops_PPR
 *		_hoops_CACPGR _hoops_IS _hoops_SGH _hoops_RH _hoops_GSPIP _hoops_HHPA _hoops_IS _hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_GHCA _hoops_AA _hoops_HIS.
 */
local void _hoops_CACSR (
	Display_Context alter	*dc) {
	X11Data alter				*_hoops_RRRPC = X11D(dc);

	(*_hoops_RRRPC->_hoops_HACPGR) (dc);
}

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_ACGR  _hoops_SASI _hoops_GSPIP _hoops_HHPA _hoops_GPP _hoops_RH _hoops_GPAAC _hoops_HHSPC.  _hoops_HGI _hoops_PCPH _hoops_HCPH
 *		_hoops_PGCR _hoops_RII _hoops_SICAR _hoops_HIS _hoops_SGS _hoops_RII _hoops_GRRGI _hoops_SGS _hoops_ARAS _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_GPAAC _hoops_PPR
 *		_hoops_CACPGR _hoops_IS _hoops_SGH _hoops_RH _hoops_GSPIP _hoops_HHPA _hoops_IS _hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_GHCA _hoops_AA _hoops_HIS.
 */
local bool _hoops_AACSR (
	Display_Context alter		*dc,
	char const						*name) {
	X11Data alter					*_hoops_RRRPC = X11D(dc);
	char	const					*_hoops_GPCPGR;

	_hoops_GPCPGR = name;
	if ((*_hoops_RRRPC->_hoops_PGCPGR) (dc,_hoops_GPCPGR))
		return true;
	else
		return false;
}

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_PSISC _hoops_IRS _hoops_GAS _hoops_GSGR
 */
local bool measure_char(
	Net_Rendition const & nr,
	Font_Instance const * instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_HPSRH) {

	_hoops_GSRPC alter *_hoops_HIHPGR = (_hoops_GSRPC alter*) instance->_hoops_GAASR;
	XFontStruct alter *_hoops_RPCPGR = _hoops_HIHPGR->_hoops_HSRPC;
	unsigned int min_byte1 = _hoops_RPCPGR->min_byte1;
	unsigned int max_byte1 = _hoops_RPCPGR->max_byte1;
	unsigned int min_char_or_byte2 = _hoops_RPCPGR->min_char_or_byte2;
	unsigned int max_char_or_byte2 = _hoops_RPCPGR->max_char_or_byte2;
	int _hoops_HCHPGR = max_char_or_byte2 - min_char_or_byte2 + 1;
	XChar2b _hoops_CIHPGR;

	UNREFERENCED(nr);

	if (min_byte1 || max_byte1) {
		_hoops_CIHPGR.byte1 = _hoops_IPCSR/_hoops_HCHPGR + min_byte1;
		_hoops_CIHPGR.byte2 = _hoops_IPCSR%_hoops_HCHPGR + min_char_or_byte2;
	}else{
		_hoops_CIHPGR.byte1 = 0;
		_hoops_CIHPGR.byte2 = 0x00FF & _hoops_IPCSR;
	}

	*_hoops_GGGS = 0.0f;
	*_hoops_CPCSR = true;

	if (_hoops_CIHPGR.byte1 >= min_byte1 && _hoops_CIHPGR.byte1 <= max_byte1 &&
			_hoops_CIHPGR.byte2 >= min_char_or_byte2 && _hoops_CIHPGR.byte2 <= max_char_or_byte2) {

		if (_hoops_RPCPGR->per_char) {

			XCharStruct * _hoops_APCPGR;

			_hoops_APCPGR = &(_hoops_RPCPGR->per_char[((_hoops_CIHPGR.byte1 - min_byte1) * _hoops_HCHPGR) + (_hoops_CIHPGR.byte2 - min_char_or_byte2)]);

			if (_hoops_APCPGR->width==0 && (_hoops_APCPGR->ascent + _hoops_APCPGR->descent == 0)) return true;

			*_hoops_GGGS += _hoops_APCPGR->width;
			*_hoops_CPCSR = false;
			*_hoops_HPSRH = (void*)1;

		}else{
			/*_hoops_CIPIP _hoops_CGISR _hoops_RPP _hoops_GII _hoops_CHR _hoops_IGRIP???*/
			*_hoops_GGGS += _hoops_RPCPGR->max_bounds.rbearing - _hoops_RPCPGR->max_bounds.lbearing;
			*_hoops_CPCSR = false;
			*_hoops_HPSRH = (void*)1;
		}
	}

	return true;
}


/*
 *		** _hoops_SRAC **
 *
 *		_hoops_SSHAR _hoops_RH _hoops_HGRC _hoops_GPAAC _hoops_HHSPC _hoops_GSPIP.
 */
local void *
load_font (Display_Context const * dc,
	   char const * iname, Font_Instance alter * instance)
{
	X11Data alter *_hoops_RRRPC = X11D (dc);
	char _hoops_PSHRS[XLFD_NUM_FIELDS][XLFD_MAX_FIELD_SIZE];
	char name[256];
	XFontStruct alter *_hoops_RPCPGR;
	float _hoops_ISISR = instance->_hoops_RACSR;
	float _hoops_IGGGH = instance->_hoops_IGGGH;
	int _hoops_RHIPGR, _hoops_PPCPGR = 0;
	_hoops_RAARP *stencil;

	_hoops_CPAPGR ("load font", _hoops_RRRPC);

	/* _hoops_ASIGA _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_RSAIP _hoops_IS _hoops_HPCPGR _hoops_IRS _hoops_SCCHH _hoops_RHRRA 5/4/2006 */
	if (instance->_hoops_RACSR > 500)
		return null;

	_hoops_RHIPGR = _hoops_PPIPGR (iname, _hoops_PSHRS);
	if (_hoops_RHIPGR < 0)
		return null;


	_hoops_IPCPGR:

	if ((_hoops_RHIPGR == XLFD_NUM_FIELDS - 1) &&
		_hoops_AGGR (_hoops_PSHRS[XLFD_PIXEL_SIZE], "-0") &&
		_hoops_AGGR (_hoops_PSHRS[XLFD_POINT_SIZE], "-0") &&
		_hoops_AGGR (_hoops_PSHRS[XLFD_AVERAGE_WIDTH], "-0")) {
		/*
		* _hoops_HHIGR'_hoops_GRI _hoops_IRS _hoops_GCHCC _hoops_HRCSR, _hoops_CHIA _hoops_HPP _hoops_PCRIP.
		* _hoops_CPCPGR _hoops_RPPCR _hoops_HS _hoops_RIAGR _hoops_PAII '-' _hoops_GIGRH _hoops_GGR _hoops_HRPGS
		* _hoops_PPR _hoops_HIS _hoops_SR _hoops_PPSI _hoops_SCH _hoops_ISSC _hoops_ARI.
		*/
		_hoops_AAHR ("-", name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_FOUNDRY], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_FAMILY], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_WEIGHT], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_SLANT], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_SET_WIDTH], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_ADD_STYLE], name);
		_hoops_HPRPR (Sprintf_D (null, "-%d", (int) _hoops_ISISR), name);
		_hoops_HPRPR ("-*", name);	/* _hoops_SPCPGR */
		_hoops_HPRPR (_hoops_PSHRS[XLFD_RESOLUTION_X], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_RESOLUTION_Y], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_SPACING], name);
		_hoops_HPRPR ("-*", name);	/* _hoops_GHCPGR */
		_hoops_HPRPR (_hoops_PSHRS[XLFD_CHAR_SET], name);
		_hoops_HPRPR (_hoops_PSHRS[XLFD_SUB_SET], name);
	}
	else
		_hoops_AAHR (iname, name);


	_hoops_RPCPGR = XLoadQueryFont (_hoops_RRRPC->display, name);
	if (!_hoops_RPCPGR)
		return null;

	_hoops_GSRPC alter *_hoops_HIHPGR;
	ALLOC (_hoops_HIHPGR, _hoops_GSRPC);
	_hoops_HIHPGR->_hoops_CSSGA = null;

	/*
	 *  _hoops_PSIH _hoops_RH _hoops_HRGSI _hoops_RHCPGR _hoops_IASC _hoops_AHCRR _hoops_GRPAR
	 *  _hoops_IH _hoops_SCAAI (_hoops_CSCHA _hoops_PPR/_hoops_PAR _hoops_AHCPGR).
	 */
	_hoops_HIHPGR->_hoops_HSRPC = _hoops_RPCPGR;
	_hoops_HIHPGR->lbearing = _hoops_RPCPGR->min_bounds.lbearing;
	_hoops_HIHPGR->rbearing = _hoops_RPCPGR->max_bounds.rbearing;
	_hoops_HIHPGR->ascent = _hoops_RPCPGR->max_bounds.ascent;
	_hoops_HIHPGR->descent = _hoops_RPCPGR->max_bounds.descent;

	/* _hoops_CGP _hoops_PSSSP > 0 _hoops_PSCR _hoops_SR'_hoops_ASAR _hoops_PHCPGR _hoops_IRS _hoops_GCHCC _hoops_HRCSR. _hoops_CGP _hoops_HHCPGR < 1 _hoops_PSCR
	 * _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_SR'_hoops_RISP _hoops_IICGGR _hoops_IS _hoops_GGARP _hoops_RGR _hoops_HRCSR.  _hoops_IHCPGR _hoops_RH _hoops_HRCSR
	 * _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_HRGR _hoops_RH _hoops_RPHR _hoops_IGIR.  _hoops_CGP _hoops_SCH _hoops_GPGH'_hoops_RA, _hoops_HRHPA _hoops_RH _hoops_IGIR
	 * _hoops_PPR _hoops_GGARP _hoops_RH _hoops_HRCSR _hoops_GICS _hoops_CCA _hoops_RH _hoops_CCAH _hoops_IGIR.
	 */
	if (_hoops_ISISR > 0 && _hoops_PPCPGR < 1) {
		/* _hoops_CGP _hoops_RH _hoops_HRCSR _hoops_HRGR _hoops_AIAH _hoops_CPSA _hoops_RISA _hoops_GA'_hoops_RA _hoops_SHAC _hoops_IRCC _hoops_IS
		 * _hoops_IRHH _hoops_SCH _hoops_RRHP.
		 */
		if (_hoops_ISISR > 3) {
			++_hoops_PPCPGR;
			/* _hoops_SIPR _hoops_IRS _hoops_ICHPGR _hoops_PSSCI _hoops_IIGR _hoops_RH _hoops_RAIGR _hoops_GAS _hoops_HIS _hoops_SR _hoops_PAH _hoops_PSISC _hoops_RH _hoops_RIHRR _hoops_APPS. */
			stencil = _hoops_SCHPGR (_hoops_RRRPC, _hoops_HIHPGR, (Karacter) 'A', 0.0, 1.0);
			if (stencil) {
				int _hoops_CHCPGR, index, row, col, _hoops_SHCPGR = 0;
				for (row = 0; row < stencil->height; ++row) {
					_hoops_CHCPGR = 0;
					for (col = 0; col < stencil->_hoops_APARP; ++col) {
						index = row * stencil->_hoops_APARP + col;
						if (!_hoops_CHCPGR && stencil->bitmap[index]) {
							_hoops_CHCPGR = 1;
							++_hoops_SHCPGR;
						}
					}
				}

				HI_Cleanup_Stencil(stencil,true);

				/* _hoops_RPP _hoops_RH _hoops_GAAA _hoops_GAPA _hoops_RH _hoops_PGRR _hoops_RRAHA _hoops_HRGR _hoops_RRPAR _hoops_HSAR _hoops_RH _hoops_AAHP,
				 * _hoops_GRAS _hoops_IRS _hoops_CCAH _hoops_IGIR _hoops_PPR _hoops_HPPR _hoops_PHCPGR _hoops_IRS _hoops_CCAH _hoops_HRCSR _hoops_CCA _hoops_RH _hoops_CCAH _hoops_IGIR.
				 */
				if (pow (_hoops_ISISR - (float)_hoops_SHCPGR, 2.0f) > 2.0f /*_hoops_AAHP*/) {
					XFreeFont (_hoops_RRRPC->display, _hoops_RPCPGR);
					_hoops_ISISR = floor (2 * _hoops_ISISR - _hoops_SHCPGR + 1);
					/* _hoops_GICPGR _hoops_GH _hoops_IS _hoops_SGCSR _hoops_RH _hoops_HRCSR _hoops_GICS _hoops_CCA _hoops_ISCP _hoops_CCAH _hoops_IGIR. */
					FREE (_hoops_HIHPGR, _hoops_GSRPC);
					goto _hoops_IPCPGR;
				}
			}
		}
	}
	/* _hoops_CGP _hoops_PSSSP < 0 _hoops_PSCR _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_GRAA-_hoops_GCHCC _hoops_HRCSR. */
	else if (!_hoops_PPCPGR) {
		if (_hoops_ISISR == -1.0) {
			/* _hoops_RICPGR _hoops_PSSSP _hoops_GAR _hoops_RH _hoops_APPS _hoops_IIGR _hoops_IRS _hoops_IHHPP _hoops_RAIGR.  */
			_hoops_ISISR = 0.0;
			if ((_hoops_RPCPGR->per_char != null) && (_hoops_RPCPGR->min_char_or_byte2 <= 'A') && ('A' <= _hoops_RPCPGR->max_char_or_byte2))
				_hoops_ISISR = (float) _hoops_RPCPGR->per_char['A' - _hoops_RPCPGR->min_char_or_byte2].ascent;

			if (_hoops_ISISR <= 0.0) {
				/* _hoops_CSH _hoops_RIR-_hoops_GAS _hoops_PAR _hoops_PSP '_hoops_RAIGR'? */
				_hoops_ISISR = (float) _hoops_RPCPGR->max_bounds.ascent;
				if (_hoops_ISISR <= 0.0) {
					/*  _hoops_CSH _hoops_AICPGR? _hoops_CPPPR _hoops_PICPGR. */
					_hoops_ISISR = (float) _hoops_RPCPGR->max_bounds.descent;
					if (_hoops_ISISR <= 0.0) {
						/* _hoops_CSH _hoops_HICPGR? _hoops_SR'_hoops_GHGP _hoops_GIH _hoops_RCRP _hoops_GH. */
						_hoops_ISISR = (float) _hoops_IARGI;
					}
				}
			}
		}
		if (_hoops_IGGGH == -1.0) {
			char const *_hoops_RPPA;
			_hoops_IGGGH = 0.0;
			_hoops_RPPA = &_hoops_PSHRS[XLFD_PIXEL_SIZE][0];
			if (*_hoops_RPPA == '-')
				_hoops_RPPA++;
			while ('0' <= *_hoops_RPPA && *_hoops_RPPA <= '9')
				_hoops_IGGGH = _hoops_IGGGH * 10 + ((int) *_hoops_RPPA++ - (int) '0');

			if (_hoops_IGGGH < _hoops_ISISR) {
				_hoops_IGGGH = (float) _hoops_RPCPGR->ascent + _hoops_RPCPGR->descent;
				if (_hoops_IGGGH < _hoops_ISISR) {
					_hoops_IGGGH = (float) (_hoops_RPCPGR->max_bounds.ascent + _hoops_RPCPGR->max_bounds.descent);
					if (_hoops_IGGGH < _hoops_ISISR)
						_hoops_IGGGH = _hoops_ISISR;
				}
			}
		}
		/* _hoops_AGAH _hoops_GSSS _hoops_IHHH _hoops_IS _hoops_RIH _hoops_ISSC _hoops_PSSSP _hoops_PPR _hoops_GCISC _hoops_IH
		 * _hoops_GRAA-_hoops_GCHCC _hoops_GSPIP. */
		//_hoops_HAGAR->_hoops_PSSSP = _hoops_PSSSP;
		//_hoops_HAGAR->_hoops_GCISC = _hoops_GCISC;
	}

	return (void *) _hoops_HIHPGR;
}

/*
 * _hoops_SRAC
 */
local void HC_CDECL _hoops_SRCSR (
	Net_Rendition const		&nr,
	Font_Instance const		*instance,
	Point const				*position,
	int							count,
	Karacter const			*_hoops_IHSCP,
	Vector const				*scale) {

	_hoops_IGCSR const &	_hoops_HRCIR = nr->_hoops_SISI;

	if (_hoops_HRCIR->transform == FT_FULL || _hoops_HRCIR->rotation != 0.0f || _hoops_HRCIR->width_scale != 1.0f)
		HD_Draw_Stenciled_Font (nr,instance,position,count,_hoops_IHSCP,scale);
	else
		_hoops_RAICP (nr, (DC_Point*)position, count, _hoops_IHSCP);

}


/*
 *		** _hoops_SRAC **
 *
 *		_hoops_PHGSI _hoops_RH _hoops_HGRC _hoops_GPAAC _hoops_HHSPC _hoops_GSPIP.
 */
local void unload_font (
	Display_Context const	*dc,
	Font_Instance alter		*instance) {
	X11Data alter	*_hoops_RRRPC = X11D(dc);

	_hoops_CPAPGR("unload font", _hoops_RRRPC);

	XFreeFont (_hoops_RRRPC->display, ((_hoops_GSRPC const *)instance->_hoops_GAASR)->_hoops_HSRPC);
	FREE ((_hoops_GSRPC const *)instance->_hoops_GAASR, _hoops_GSRPC);
}


/*
 * _hoops_SRAC
 * */
local bool
snapshot(
	Net_Rendition const &  nr,
	int width,
	int height,
	unsigned char * data) {

	X11Data alter *_hoops_RRRPC = X11D(nr->_hoops_SRA);
	Int_Rectangle const * area = &nr->_hoops_SAIR->_hoops_SCIH;
	int w,h;
	int x,y;
	XImage alter *image;

	w = area->right - area->left + 1;
	h = area->top - area->bottom + 1;

	if (w*h > width*height) return false;

	XSync (_hoops_RRRPC->display, False);

	if ((image = XGetImage (
			_hoops_RRRPC->display, _hoops_RRRPC->_hoops_SRASH, 0, 0,
			width, height, AllPlanes, ZPixmap)) == null) {

			HE_ERROR (HEC_X11_DRIVER, HES_GETIMAGE_FOR_TEXT_FAILED,
							"X11 Driver: could not get image for snapshot");
			return false;
	}

	for (y=0;y<h;y++) {
		for (x=0;x<w;x++) {
			unsigned long pixel = XGetPixel(image, x, y);

			unsigned char r = (unsigned char)((pixel<<_hoops_RRRPC->_hoops_CGPPGR)>>_hoops_RRRPC->_hoops_SGPPGR);
			unsigned char g = (unsigned char)((pixel<<_hoops_RRRPC->_hoops_GRPPGR)>>_hoops_RRRPC->_hoops_RRPPGR);
			unsigned char b = (unsigned char)((pixel<<_hoops_RRRPC->_hoops_ARPPGR)>>_hoops_RRRPC->_hoops_PRPPGR);

			*data++ = r;
			*data++ = g;
			*data++ = b;
		}
	}

	XDestroyImage(image);

	return true;
}




/****************************************************************
 ****************************************************************
						 _hoops_HRAIA _hoops_RRGGR _hoops_HRAIA _hoops_PGGIR _hoops_SAAAR		  _hoops_RPRAR _hoops_RAIGR _hoops_PGGIR _hoops_RAIGR _hoops_PHGPH _hoops_HRAIA _hoops_RPRAR _hoops_HRAIA _hoops_PGGIR _hoops_SAAAR
 ****************************************************************
 ****************************************************************/

/*
 *		_hoops_SPCSI _hoops_RH _hoops_HIGPH _hoops_HIS _hoops_SGS _hoops_RH _hoops_RCPH _hoops_SPPPR _hoops_CGISR _hoops_RH _hoops_SCGR _hoops_PIAP
 *
 *		_hoops_IICPGR _hoops_HPP _hoops_CICPGR _hoops_SICPGR...
 */
local void _hoops_GCCPGR(
	Display_Context const *	dc,
	XKeyEvent *				_hoops_GSSPC) {
	char	event_string[256];

	if ((dc->options._hoops_GASSP) && (!dc->options._hoops_IRSSP)) {
		 sprintf(event_string, "%x", _hoops_GSSPC->state);
		 HI_Queue_Special_Event (dc->_hoops_RIGC, "X11:ModifierEvent", event_string);
		 _hoops_GSSPC->state &= 0xb7;
	 }
}

/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ICRRP _hoops_RH _hoops_GPAAC _hoops_CIIRH _hoops_CIIA _hoops_HII _hoops_RH _hoops_GPAAC _hoops_RCCPGR
 *		_hoops_PGRRR _hoops_HRPR.
 */
local void _hoops_ACCPGR (
	Display_Context const		*dc,
	void alter						*_hoops_PCCPGR,
	int alter						*_hoops_HCCPGR,
	void alter						*_hoops_ICCPGR) {
	XKeyEvent alter					*_hoops_GSSPC = (XKeyEvent alter *)_hoops_PCCPGR;
	Display alter					*display = (Display alter *)_hoops_ICCPGR;
	int								key;
	KeySym							keysym;
	char							string[10];
	int								_hoops_CCCPGR;
	X11Data alter					*_hoops_RRRPC = X11D(dc);

	_hoops_GCCPGR(dc, _hoops_GSSPC);
	XLookupString (_hoops_GSSPC, string, sizeof(string), &keysym, null);

		if (keysym < 256) {
				/* _hoops_GPAAC _hoops_SHIR _hoops_HRGR _hoops_GHAGI _hoops_HHHPP-1, _hoops_PII _hoops_IHHH */
				key = string[0];

				/* _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SRS _hoops_SIC _hoops_IIGR _hoops_IRS _hoops_HPSSA _hoops_ICPPR. */
				if (*_hoops_HCCPGR == _hoops_SCCPGR) {
						*_hoops_HCCPGR = key;
						return;
				}
		}
		else {
				switch (keysym) {
						case XK_F1:					key = FIRST_FUNCTION_KEY + 1;	break;
						case XK_F2:					key = FIRST_FUNCTION_KEY + 2;	break;
						case XK_F3:					key = FIRST_FUNCTION_KEY + 3;	break;
						case XK_F4:					key = FIRST_FUNCTION_KEY + 4;	break;
						case XK_F5:					key = FIRST_FUNCTION_KEY + 5;	break;
						case XK_F6:					key = FIRST_FUNCTION_KEY + 6;	break;
						case XK_F7:					key = FIRST_FUNCTION_KEY + 7;	break;
						case XK_F8:					key = FIRST_FUNCTION_KEY + 8;	break;
						case XK_F9:					key = FIRST_FUNCTION_KEY + 9;	break;
						case XK_F10:				key = FIRST_FUNCTION_KEY + 10;	break;
						case XK_F11:				key = FIRST_FUNCTION_KEY + 11;	break;
						case XK_F12:				key = FIRST_FUNCTION_KEY + 12;	break;
						case XK_F13:				key = FIRST_FUNCTION_KEY + 13;	break;
						case XK_F14:				key = FIRST_FUNCTION_KEY + 14;	break;
						case XK_F15:				key = FIRST_FUNCTION_KEY + 15;	break;
						case XK_F16:				key = FIRST_FUNCTION_KEY + 16;	break;
						case XK_F17:				key = FIRST_FUNCTION_KEY + 17;	break;
						case XK_F18:				key = FIRST_FUNCTION_KEY + 18;	break;
						case XK_F19:				key = FIRST_FUNCTION_KEY + 19;	break;
						case XK_F20:				key = FIRST_FUNCTION_KEY + 20;	break;
						case XK_F21:				key = FIRST_FUNCTION_KEY + 21;	break;
						case XK_F22:				key = FIRST_FUNCTION_KEY + 22;	break;
						case XK_F23:				key = FIRST_FUNCTION_KEY + 23;	break;
						case XK_F24:				key = FIRST_FUNCTION_KEY + 24;	break;
						case XK_F25:				key = FIRST_FUNCTION_KEY + 25;	break;
						case XK_F26:				key = FIRST_FUNCTION_KEY + 26;	break;
						case XK_F27:				key = FIRST_FUNCTION_KEY + 27;	break;
						case XK_F29:				key = FIRST_FUNCTION_KEY + 29;	break;
						case XK_F31:				key = FIRST_FUNCTION_KEY + 31;	break;
						case XK_F33:				key = FIRST_FUNCTION_KEY + 33;	break;
						case XK_F35:				key = FIRST_FUNCTION_KEY + 35;	break;

#						ifdef SOLARIS_SYSTEM
						/* _hoops_IPCP _hoops_HSPR _hoops_CHR _hoops_RGAR _hoops_ICPRA _hoops_GPP _hoops_RH _hoops_GSCPGR */
						case XK_R8:				key = UP_ARROW_KEY;				break;
						case XK_R10:			key = LEFT_ARROW_KEY;			break;
						case XK_R12:			key = RIGHT_ARROW_KEY;			break;
						case XK_R14:			key = DOWN_ARROW_KEY;			break;
#						else
						/* (_hoops_ASC _hoops_RGGHR _hoops_RSCPGR _hoops_CCA _hoops_RH _hoops_ASCPGR _hoops_RGGHR) */
						case XK_F28:			key = FIRST_FUNCTION_KEY + 28;	break;
						case XK_F30:			key = FIRST_FUNCTION_KEY + 30;	break;
						case XK_F32:			key = FIRST_FUNCTION_KEY + 32;	break;
						case XK_F34:			key = FIRST_FUNCTION_KEY + 34;	break;
#						endif /* _hoops_SPPHS */

						case XK_KP_0:
								  key = '0';
								  break;
						case XK_KP_1:
								  key = '1';
								  break;
						case XK_KP_2:
								  key = '2';
								  break;
						case XK_KP_3:
								  key = '3';
								  break;
						case XK_KP_4:
								  key = '4';
								  break;
						case XK_KP_5:
								  key = '5';
								  break;
						case XK_KP_6:
								  key = '6';
								  break;
						case XK_KP_7:
								  key = '7';
								  break;
						case XK_KP_8:
								  key = '8';
								  break;
						case XK_KP_9:
								  key = '9';
								  break;

						case XK_KP_F1:					key = FIRST_KEYPAD_KEY + 10;	break;
						case XK_KP_F2:					key = FIRST_KEYPAD_KEY + 11;	break;
						case XK_KP_F3:					key = FIRST_KEYPAD_KEY + 12;	break;
						case XK_KP_F4:					key = FIRST_KEYPAD_KEY + 13;	break;

						case XK_KP_Space:
								  key = ' ';
								  break;
						case XK_KP_Subtract:
								  key = '-';
								  break;
						case XK_KP_Separator:
								  key = ',';
								  break;
						case XK_KP_Decimal:
								  key = '.';
								  break;
						case XK_KP_Tab:
								  key = 9;
								  break;
						case XK_KP_Enter:
								  key = 13;
								  break;
						case XK_KP_Equal:
								  key = '=';
								  break;
						case XK_KP_Multiply:
								  key = '*';
								  break;
						case XK_KP_Add:
								  key = '+';
								  break;
						case XK_KP_Divide:
								  key = '/';
								  break;

						case XK_Insert:
								  key = INSERT_KEY;
								  break;
						case XK_Home:
								  key = HOME_KEY;
								  break;
						case XK_Page_Up:
								  key = PAGE_UP_KEY;
								  break;
						case XK_Page_Down:
								  key = PAGE_DOWN_KEY;
								  break;
						case XK_End:
								  key = END_KEY;
								  break;

						case XK_Left:					key = LEFT_ARROW_KEY;		break;
						case XK_Up:						key = UP_ARROW_KEY;			break;
						case XK_Right:					key = RIGHT_ARROW_KEY;		break;
						case XK_Down:					key = DOWN_ARROW_KEY;		break;

						case XK_Delete:					key = RUBOUT_KEY;			break;
						case XK_Return:					key = 13;					break;
						case XK_BackSpace:				key = 8;					break;
						case XK_Tab:					key = 9;					break;
						case XK_Escape:					key = 27;					break;
						case XK_Linefeed:				key = 10;					break;
						case XK_Clear:					key = 11;					break;
						case XK_Pause:					key = 19;					break;

						case XK_Shift_L:
						case XK_Shift_R:
						case XK_Caps_Lock:
						case XK_Shift_Lock: {
								/*
								 *		_hoops_HCGAR _hoops_SSPP _hoops_SIHH _hoops_PSCPGR _hoops_HSCPGR _hoops_CR
								 *		_hoops_RH _hoops_PARRH _hoops_CRGIA _hoops_CHR _hoops_PHRH _hoops_IS _hoops_SHH _hoops_IGI _hoops_GGR _hoops_HPSSA
								 *		_hoops_SIC _hoops_SAIGS.
								 */
								_hoops_RRRPC->_hoops_ISCPGR |= HOOPS_SHIFT_MASK;
								return;
						}

						case XK_Control_L:
						case XK_Control_R: {
								_hoops_RRRPC->_hoops_ISCPGR |= HOOPS_CTRL_MASK;
								return;
						}

						case XK_Multi_key: {
								/*
								 *		_hoops_RAP _hoops_HSCPGR _hoops_IS _hoops_CSCPGR _hoops_IS _hoops_GCAPR _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_IRS
								 *		_hoops_HPSSA _hoops_ICPPR.
								 */
								*_hoops_HCCPGR = _hoops_SCCPGR;
								return;
						}

						case XK_Meta_L: {
						  /*
								 *		_hoops_RAP _hoops_HSCPGR _hoops_IS _hoops_CSCPGR _hoops_IS _hoops_GCAPR _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_IRS
								 *		_hoops_HPSSA _hoops_ICPPR.
								 */
								*_hoops_HCCPGR = _hoops_SCCPGR;
								_hoops_RRRPC->_hoops_ISCPGR |= HOOPS_META_MASK;
								return;
						}


						case XK_Alt_L: {
								/*
								 *		_hoops_RAP _hoops_HSCPGR _hoops_IS _hoops_CSCPGR _hoops_IS _hoops_GCAPR _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_IRS
								 *		_hoops_HPSSA _hoops_ICPPR.
								 */
								*_hoops_HCCPGR = _hoops_SCCPGR;
								_hoops_RRRPC->_hoops_ISCPGR |= HOOPS_ALT_MASK;
								return;
						}

						case XK_Num_Lock: {
								_hoops_RRRPC->_hoops_SSCPGR = true;
								return;
						}

						default: {
								/*
								 *		_hoops_SRPR _hoops_SPR _hoops_IIGR _hoops_RH _hoops_GRH _hoops_CRGIA _hoops_SGS _hoops_SR _hoops_ACPA.
								 *		_hoops_RAP "_hoops_SIC" _hoops_IS _hoops_PHAPGR + 1 _hoops_HIS _hoops_SGS _hoops_SR _hoops_GRS
								 *		_hoops_ASRC _hoops_GGR _hoops_PCCP _hoops_RPP _hoops_RPGP _hoops_CAPP _hoops_ARPP _hoops_RASAI
								 *		_hoops_RH _hoops_SIC _hoops_PGRRR.
								 */
								key = XK_VoidSymbol + 1;
						}		break;
				}

				/*
				 *		_hoops_RAP _hoops_HSCPGR _hoops_IS _hoops_GGSPGR _hoops_IS _hoops_ICPPA _hoops_IRS _hoops_HPSSA _hoops_ICPPR
				 *		_hoops_RPP _hoops_SPR _hoops_CSAP _hoops_GGR _hoops_GCRPA.
				 */
				*_hoops_HCCPGR = _hoops_RGSPGR;
		}

		if (*_hoops_HCCPGR != _hoops_RGSPGR &&
				*_hoops_HCCPGR != _hoops_SCCPGR) {
				int				_hoops_AGSPGR;
				int				_hoops_PGSPGR;

				/*
				 *		_hoops_PS _hoops_HS _hoops_IRS _hoops_HPSSA _hoops_ICPPR _hoops_IIGR _hoops_PGCR _hoops_CRGIA.	 _hoops_PHAA _hoops_GHIS _hoops_RH
				 *		_hoops_PGCR _hoops_CRGIA _hoops_HIS _hoops_SGS _hoops_ISCP _hoops_RRGR _hoops_HRGR _hoops_PPIHR - _hoops_RRPS _hoops_IS _hoops_RH
				 *		_hoops_RHAR _hoops_GAHIR, _hoops_IRS _hoops_HPSSA _hoops_ICPPR _hoops_IIGR _hoops_PGCR _hoops_CRGIA _hoops_HRGR _hoops_ASAI
				 *		_hoops_AGR-_hoops_AAR.  _hoops_CPR, _hoops_ISPR _hoops_RH _hoops_AARRA _hoops_IIGR _hoops_RH
				 *		_hoops_PGCR _hoops_CRGIA _hoops_PPR _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_SPPSC _hoops_HPSSA _hoops_SIC
				 *		_hoops_AARRA, _hoops_ARP "_hoops_SIC" _hoops_IS _hoops_PHAPGR + 1 _hoops_HIS _hoops_SGS _hoops_SR _hoops_GRS
				 *		_hoops_ASRC _hoops_GGR _hoops_RH _hoops_RPP _hoops_RPGP _hoops_CAPP _hoops_ARPP _hoops_RASAI _hoops_RH _hoops_SIC _hoops_PGRRR.
				 */
				_hoops_AGSPGR = (*_hoops_HCCPGR < key) ? *_hoops_HCCPGR : key;
				_hoops_PGSPGR = (*_hoops_HCCPGR < key) ? key : *_hoops_HCCPGR;

				switch (_hoops_AGSPGR) {
						case XK_space: {
								switch (_hoops_PGSPGR) {
										case XK_space:			key = XK_nobreakspace;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_exclam: {
								switch (_hoops_PGSPGR) {
										case XK_exclam:			key = XK_exclamdown;			break;
										case XK_P:				key = XK_paragraph;				break;
										case XK_p:				key = XK_paragraph;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_quotedbl: {
								switch (_hoops_PGSPGR) {
										case XK_quotedbl:		key = XK_diaeresis;				break;
										case XK_A:				key = XK_Adiaeresis;			break;
										case XK_E:				key = XK_Ediaeresis;			break;
										case XK_I:				key = XK_Idiaeresis;			break;
										case XK_O:				key = XK_Odiaeresis;			break;
										case XK_U:				key = XK_Udiaeresis;			break;
										case XK_a:				key = XK_adiaeresis;			break;
										case XK_e:				key = XK_ediaeresis;			break;
										case XK_i:				key = XK_idiaeresis;			break;
										case XK_o:				key = XK_odiaeresis;			break;
										case XK_u:				key = XK_udiaeresis;			break;
										case XK_y:				key = XK_ydiaeresis;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_quoteright: {
								switch (_hoops_PGSPGR) {
										case XK_A:				key = XK_Aacute;				break;
										case XK_E:				key = XK_Eacute;				break;
										case XK_I:				key = XK_Iacute;				break;
										case XK_O:				key = XK_Oacute;				break;
										case XK_U:				key = XK_Uacute;				break;
										case XK_Y:				key = XK_Yacute;				break;
										case XK_a:				key = XK_aacute;				break;
										case XK_e:				key = XK_eacute;				break;
										case XK_i:				key = XK_iacute;				break;
										case XK_o:				key = XK_oacute;				break;
										case XK_u:				key = XK_uacute;				break;
										case XK_y:				key = XK_yacute;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_asterisk: {
								switch (_hoops_PGSPGR) {
										case XK_A:				key = XK_Aring;					break;
										case XK_asciicircum:	key = XK_degree;				break;
										case XK_a:				key = XK_aring;					break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_plus: {
								switch (_hoops_PGSPGR) {
										case XK_minus:			key = XK_plusminus;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_comma: {
								switch (_hoops_PGSPGR) {
										case XK_comma:			key = XK_cedilla;				break;
										case XK_minus:			key = XK_notsign;				break;
										case XK_C:				key = XK_Ccedilla;				break;
										case XK_c:				key = XK_ccedilla;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_minus: {
								switch (_hoops_PGSPGR) {
										case XK_minus:			key = XK_hyphen;				break;
										case XK_colon:			key = XK_division;				break;
										case XK_A:				key = XK_ordfeminine;			break;
										case XK_D:				key = XK_Eth;					break;
										case XK_L:				key = XK_sterling;				break;
										case XK_Y:				key = XK_yen;					break;
										case XK_asciicircum:	key = XK_macron;				break;
										case XK_a:				key = XK_ordfeminine;			break;
										case XK_d:				key = XK_eth;					break;
										case XK_l:				key = XK_sterling;				break;
										case XK_y:				key = XK_yen;					break;
										case XK_bar:			key = XK_notsign;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_period: {
								switch (_hoops_PGSPGR) {
										case XK_asciicircum:	key = XK_periodcentered;		break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_slash: {
								switch (_hoops_PGSPGR) {
										case XK_C:				key = XK_cent;					break;
										case XK_O:				key = XK_Ooblique;				break;
										case XK_c:				key = XK_cent;					break;
										case XK_o:				key = XK_oslash;				break;
										case XK_u:				key = XK_mu;					break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_0: {
								switch (_hoops_PGSPGR) {
										case XK_X:				key = XK_currency;				break;
										case XK_asciicircum:	key = XK_degree;				break;
										case XK_x:				key = XK_currency;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_1: {
								switch (_hoops_PGSPGR) {
										case XK_asciicircum:	key = XK_onesuperior;			break;
										case XK_2:				key = XK_onehalf;				break;
										case XK_4:				key = XK_onequarter;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_2: {
								switch (_hoops_PGSPGR) {
										case XK_asciicircum:	key = XK_twosuperior;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_3: {
								switch (_hoops_PGSPGR) {
										case XK_4:				key = XK_threequarters;			break;
										case XK_asciicircum:	key = XK_threesuperior;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_less: {
								switch (_hoops_PGSPGR) {
										case XK_less:			key = XK_guillemotleft;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_greater: {
								switch (_hoops_PGSPGR) {
										case XK_greater:		key = XK_guillemotright;		break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_question: {
								switch (_hoops_PGSPGR) {
										case XK_question:		key = XK_questiondown;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_A: {
								switch (_hoops_PGSPGR) {
										case XK_E:				key = XK_AE;					break;
										case XK_asciicircum:	key = XK_Acircumflex;			break;
										case XK_quoteleft:		key = XK_Agrave;				break;
										case XK_asciitilde:		key = XK_Atilde;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_C: {
								switch (_hoops_PGSPGR) {
										case XK_O:				key = XK_copyright;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_E: {
								switch (_hoops_PGSPGR) {
										case XK_asciicircum:	key = XK_Ecircumflex;			break;
										case XK_quoteleft:		key = XK_Egrave;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_H: {
								switch (_hoops_PGSPGR) {
										case XK_T:				key = XK_Thorn;					break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_I: {
								switch (_hoops_PGSPGR) {
										case XK_asciicircum:	key = XK_Icircumflex;			break;
										case XK_quoteleft:		key = XK_Igrave;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_N: {
								switch (_hoops_PGSPGR) {
										case XK_asciitilde:		key = XK_Ntilde;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_O: {
								switch (_hoops_PGSPGR) {
										case XK_R:				key = XK_registered;			break;
										case XK_S:				key = XK_section;				break;
										case XK_X:				key = XK_currency;				break;
										case XK_asciicircum:	key = XK_Ocircumflex;			break;
										case XK_underscore:		key = XK_masculine;				break;
										case XK_quoteleft:		key = XK_Ograve;				break;
										case XK_asciitilde:		key = XK_Otilde;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_P: {
								switch (_hoops_PGSPGR) {
										case XK_bar:			key = XK_Thorn;					break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_U: {
								switch (_hoops_PGSPGR) {
										case XK_asciicircum:	key = XK_Ucircumflex;			break;
										case XK_quoteleft:		key = XK_Ugrave;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_backslash: {
								switch (_hoops_PGSPGR) {
										case XK_backslash:		key = XK_acute;					break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_asciicircum: {
								switch (_hoops_PGSPGR) {
										case XK_a:				key = XK_acircumflex;			break;
										case XK_e:				key = XK_ecircumflex;			break;
										case XK_i:				key = XK_icircumflex;			break;
										case XK_o:				key = XK_ocircumflex;			break;
										case XK_u:				key = XK_ucircumflex;			break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_underscore: {
								switch (_hoops_PGSPGR) {
										case XK_o:				key = XK_masculine;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_quoteleft: {
								switch (_hoops_PGSPGR) {
										case XK_a:				key = XK_agrave;				break;
										case XK_e:				key = XK_egrave;				break;
										case XK_i:				key = XK_igrave;				break;
										case XK_o:				key = XK_ograve;				break;
										case XK_u:				key = XK_ugrave;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_a: {
								switch (_hoops_PGSPGR) {
										case XK_e:				key = XK_ae;					break;
										case XK_asciitilde:		key = XK_atilde;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_c: {
								switch (_hoops_PGSPGR) {
										case XK_o:				key = XK_copyright;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_h: {
								switch (_hoops_PGSPGR) {
										case XK_t:				key = XK_thorn;					break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_n: {
								switch (_hoops_PGSPGR) {
										case XK_asciitilde:		key = XK_ntilde;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_o: {
								switch (_hoops_PGSPGR) {
										case XK_r:				key = XK_registered;			break;
										case XK_s:				key = XK_section;				break;
										case XK_x:				key = XK_currency;				break;
										case XK_asciitilde:		key = XK_otilde;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_p: {
								switch (_hoops_PGSPGR) {
										case XK_bar:			key = XK_thorn;					break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_s: {
								switch (_hoops_PGSPGR) {
										case XK_s:				key = XK_ssharp;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_x: {
								switch (_hoops_PGSPGR) {
										case XK_x:				key = XK_multiply;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						case XK_bar: {
								switch (_hoops_PGSPGR) {
										case XK_bar:			key = XK_brokenbar;				break;
										default:				key = XK_VoidSymbol + 1;		break;
								}
						}		break;

						default: {
								/* _hoops_HAR _hoops_SPR _hoops_SR _hoops_ACPA */
								key = XK_VoidSymbol + 1;
								break;
						}
				}

				/* _hoops_HGSPGR _hoops_RH _hoops_IGSPGR _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_PCCP _hoops_AIPH _hoops_ICPPR. */
				if (key > XK_VoidSymbol) {
						XBell (display, 0);
						XFlush (display);
				}

				/* _hoops_RAP _hoops_HSCPGR _hoops_IS _hoops_GGSPGR _hoops_IS _hoops_CGSPGR _hoops_RH _hoops_HPSSA _hoops_SIC _hoops_ICPPR. */
				*_hoops_HCCPGR = _hoops_RGSPGR;
		}

		if (key > XK_VoidSymbol)
				return; /* _hoops_HHPPA, _hoops_GGHP _hoops_SGSPGR _hoops_SGGR */

		_hoops_CCCPGR = false;
		if (BIT (_hoops_GSSPC->state, Mod1Mask))
				_hoops_CCCPGR |= HOOPS_ALT_MASK;
		if (BIT (_hoops_GSSPC->state, ControlMask))
				_hoops_CCCPGR |= HOOPS_CTRL_MASK;
		if (BIT (_hoops_GSSPC->state, ShiftMask))
				_hoops_CCCPGR |= HOOPS_SHIFT_MASK;

		_hoops_SPAPGR ("queueing keystroke", _hoops_RRRPC);

		HI_Queue_Keyboard_Event ((_hoops_GGAGR alter *)dc->_hoops_GHRI, key, _hoops_CCCPGR);
}



local void _hoops_GRSPGR (
		Display_Context const		*dc,
		void alter										*_hoops_PCCPGR) {
		XKeyEvent alter							*_hoops_GSSPC = (XKeyEvent alter *)_hoops_PCCPGR;
		KeySym											keysym;
		char											string[10];
		X11Data alter							*_hoops_RRRPC = X11D(dc);

				_hoops_GCCPGR(dc, _hoops_GSSPC);
		XLookupString (_hoops_GSSPC, string, sizeof(string), &keysym, null);

		switch (keysym) {
				case XK_Shift_L:
				case XK_Shift_R:
				case XK_Caps_Lock:
				case XK_Shift_Lock: {
						_hoops_RRRPC->_hoops_ISCPGR &= ~HOOPS_SHIFT_MASK;
				}		break;

				case XK_Control_L:
				case XK_Control_R: {
						_hoops_RRRPC->_hoops_ISCPGR &= ~HOOPS_CTRL_MASK;
				}		break;

				case XK_Meta_L: {
						_hoops_RRRPC->_hoops_ISCPGR &= ~HOOPS_META_MASK;
				}		break;

				case XK_Alt_L: {
						_hoops_RRRPC->_hoops_ISCPGR &= ~HOOPS_ALT_MASK;
				}		break;

				case XK_Num_Lock: {
						_hoops_RRRPC->_hoops_SSCPGR = false;
				}		break;
		}
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ICRRP _hoops_RH _hoops_GPAAC _hoops_CIIRH _hoops_CIIA _hoops_HII _hoops_RH _hoops_GPAAC _hoops_RCCPGR
 *		_hoops_PGRRR _hoops_HRPR _hoops_IH _hoops_SPAGI _hoops_CIIA.
 *
 */

#ifdef _hoops_ICIGI

local void _hoops_RRSPGR (
		Display_Context const			*dc,
		unsigned char const						*str) {
		int														key;
		int														_hoops_CCCPGR;

		_hoops_CCCPGR = false;

		while (*str != '\0') {
				if (*str >= (unsigned char)0x81 && *str <= (unsigned char)0x9f ||
						*str >= (unsigned char)0xe0 && *str <= (unsigned char)0xfc) {
						int		   tmp;

						key = (int)(*str++) & 0xff;
						key <<= 8;
						key &= 0xff00;
						tmp = (*str++) & 0xff;
						key |= tmp;
				}
				else
						key = (int)(*str++) & 0xff;

				HI_Queue_Keyboard_Event (dc->_hoops_GHRI, key, _hoops_CCCPGR);
		}
}

#endif /* _hoops_ARSPGR */



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_IHARH _hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_IS _hoops_ACPA _hoops_AHCA _hoops_SSHGR _hoops_SGS _hoops_HAHA
 *		_hoops_RGCI _hoops_PISIR.
 *
 */
local void _hoops_PRSPGR (
		X11Data alter	*_hoops_RRRPC,
		Mask					mask) {
		X_Window					_hoops_SCAAR, *_hoops_ICHSP;
		unsigned int	_hoops_HRSPGR;

		/* _hoops_SRS _hoops_PRIA _hoops_RH _hoops_HGAI _hoops_PCIRA _hoops_IIGR _hoops_ISCP _hoops_RPPS */
		XQueryTree (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_RRRPC->_hoops_CISPC,
								&_hoops_RRRPC->_hoops_IRSPGR, &_hoops_ICHSP, &_hoops_HRSPGR);
		if (_hoops_ICHSP)
				XFree ((caddr_t)_hoops_ICHSP);

		/*
		 *		_hoops_CGP _hoops_HRCC _hoops_SSCP _hoops_CRSPGR _hoops_PCAAA _hoops_GAPA _hoops_IHHH _hoops_PPR _hoops_RH
		 *		_hoops_SRRPR _hoops_RPPS, _hoops_PRRHH _hoops_IS _hoops_SHH _hoops_SRSPGR _hoops_GPP _hoops_RPPS _hoops_AHC
		 *		_hoops_SHPH _hoops_IH _hoops_CAPR _hoops_HAH.
		 */
		_hoops_SCAAR = _hoops_RRRPC->window;
		if (_hoops_SCAAR != (X_Window)0) {
				X_Window	root;

				while (1) {
						XQueryTree (_hoops_RRRPC->display, _hoops_SCAAR, &root,
												&_hoops_SCAAR, &_hoops_ICHSP, &_hoops_HRSPGR);
						if (_hoops_ICHSP)
								XFree ((caddr_t)_hoops_ICHSP);
						if (_hoops_SCAAR == root)
								break;
						XSelectInput (_hoops_RRRPC->display, _hoops_SCAAR, mask);
				}
		}
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_SAGGR _hoops_RH _hoops_PIASR _hoops_GPAAC _hoops_RPPS _hoops_PCRR _hoops_HII _hoops_IRISR.
 */
local void _hoops_GASPGR (
		Display_Context const		*dc,
		int alter										*x,
		int alter										*y,
		unsigned int alter						*w,
		unsigned int alter						*h) {

		*x = dc->_hoops_RHPGA.left;
		*y = dc->_hoops_PGCC._hoops_PRPSR.y - 1 - dc->_hoops_RHPGA.top;
		*w = dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left + 1;
		*h = dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom + 1;
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_SAGGR _hoops_RH _hoops_RIHRR _hoops_GPAAC _hoops_RPPS _hoops_PCRR _hoops_HII _hoops_GPAAC.
 */
local void _hoops_RASPGR (
		X11Data alter			*_hoops_RRRPC,
		int alter				*_hoops_PGHGS,
		int alter				*_hoops_HGHGS,
		unsigned int alter		*_hoops_AASPGR,
		unsigned int alter		*_hoops_HPSRC) {

		int						x=0, y=0;
		unsigned int			_hoops_PASPGR, depth;
		X_Window					_hoops_HASPGR, _hoops_IASPGR, *_hoops_ICHSP;
		unsigned int			_hoops_HRSPGR;


		*_hoops_PGHGS=*_hoops_HGHGS=*_hoops_AASPGR=*_hoops_HPSRC=0;

		/* _hoops_IRHH _hoops_RCRR _hoops_RCPGR _hoops_PCRR _hoops_CHR _hoops_GGR _hoops_RGAS */
		XGetGeometry (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_HASPGR,
								  &x, &y, _hoops_AASPGR, _hoops_HPSRC, &_hoops_PASPGR, &depth);

		/* (_hoops_GHGPR-_hoops_ISPR _hoops_APAPC->_hoops_CASPGR) */
		if (0 != XQueryTree (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_RRRPC->_hoops_CISPC,
								&_hoops_RRRPC->_hoops_IRSPGR, &_hoops_ICHSP, &_hoops_HRSPGR)) {
			if (_hoops_ICHSP)
					XFree ((caddr_t)_hoops_ICHSP);

			/* _hoops_PHCH _hoops_IS _hoops_SRRPR _hoops_PCRR */
			XTranslateCoordinates (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IRSPGR,
								   _hoops_RRRPC->_hoops_CISPC, x, y, _hoops_PGHGS, _hoops_HGHGS, &_hoops_IASPGR);

		}

}




/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_SAGGR _hoops_GPAAC _hoops_SSHGR _hoops_HII _hoops_RH _hoops_GPAAC _hoops_PGRRR _hoops_GSSHR.
 */
local bool check_events (Display_Context const * dc)
{
	X11Data alter	*_hoops_RRRPC = X11D(dc);
	XEvent			_hoops_GSSPC;
	X11_Event_Info	*event;
	X11_Event_Info	*_hoops_SASPGR = null;
	bool		_hoops_GPSPGR = false;
	bool		_hoops_HPIS = false;
#ifdef AIX_SYSTEM
	X_Window		_hoops_RPSPGR, _hoops_APSPGR, *gl_children;
	int				_hoops_PPSPGR;
#endif

	if (dc->options._hoops_CRSSP)
		return false;

	if (_hoops_RRRPC->_hoops_HPSPGR)
		return false;

	_hoops_RRRPC->_hoops_HPSPGR = true;
	_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);

	if (!_hoops_RRRPC->_hoops_IPSPGR) {
		_hoops_SPAPGR ("check events", _hoops_RRRPC);
		if (!BIT(dc->flags, _hoops_GIRIP))
			_hoops_RRRPC->_hoops_IPSPGR = true;
	}

	while (QLength (_hoops_RRRPC->display) > 0 || XEventsQueued (_hoops_RRRPC->display, QueuedAfterReading) > 0) {
		Display_Context	* _hoops_CPSPGR;
		char event_string[256];

		XNextEvent (_hoops_RRRPC->display, &_hoops_GSSPC);
#ifdef AIX_SYSTEM
		if (_hoops_RRRPC->driver_type == GL_ON_X11 && _hoops_RRRPC->_hoops_SPSPGR[3] == 'G' &&
			_hoops_RRRPC->_hoops_SPSPGR[4] == 'X' && _hoops_RRRPC->_hoops_SPSPGR[5] == 'T') {

			if (_hoops_GSSPC.type == Expose) {
				XQueryTree(_hoops_RRRPC->display,_hoops_RRRPC->_hoops_RHSPC,&_hoops_RPSPGR,
						   &_hoops_APSPGR,&gl_children,(unsigned int*)&_hoops_PPSPGR);
				_hoops_CPSPGR = HD_Find_DC_From_WID (_hoops_APSPGR);
			}
			else
				_hoops_CPSPGR = HD_Find_DC_From_WID (_hoops_GSSPC.xany.window);
		}
		else
#endif
			_hoops_CPSPGR = HD_Find_DC_From_WID (_hoops_GSSPC.xany.window);

		if (_hoops_CPSPGR == null) continue; /* _hoops_PSP _hoops_RPIP _hoops_APIP */

		/* _hoops_HS _hoops_SR _hoops_GCRHA _hoops_RGR _hoops_SPR _hoops_AIAH */
		if ((event = _hoops_SASPGR) != null) do {
			if (event->dc == _hoops_CPSPGR) break;
		} _hoops_RGGA ((event = event->next) == null);

		/* _hoops_RPP _hoops_HAR, _hoops_PRIA _hoops_SCH */
		if (event == null) {
			ALLOC (event, X11_Event_Info);
			event->next = _hoops_SASPGR;
			_hoops_SASPGR = event;

			event->dc = _hoops_CPSPGR;
			event->_hoops_RRRPC = X11D(_hoops_CPSPGR);
			event->_hoops_GHSPGR = false;
			event->_hoops_RHSPGR = false;
			event->_hoops_CGRRR = false;
			event->_hoops_AHSPGR = false;
			event->_hoops_PHSPGR = 0;
			event->_hoops_HHSPGR = 0;
			event->_hoops_IHSPGR = 0;
			event->_hoops_CHSPGR = 0;
		}

		switch (_hoops_GSSPC.type) {
		case ButtonPress: {
			_hoops_SPAPGR ("button press event", event->_hoops_RRRPC);

			switch (_hoops_GSSPC.xbutton.button) {
			case Button1: event->_hoops_RRRPC->_hoops_HRRRR |= 1; break;
			case Button2: event->_hoops_RRRPC->_hoops_HRRRR |= 2; break;
			case Button3: event->_hoops_RRRPC->_hoops_HRRRR |= 4; break;
			}

			event->_hoops_RRRPC->_hoops_SCGRR = _hoops_GSSPC.xbutton.x;
			event->_hoops_RRRPC->mouse_y = event->_hoops_RRRPC->yfudge - _hoops_GSSPC.xbutton.y;
			HD_Queue_Pixel_Location_Event (event->dc,
										   event->_hoops_RRRPC->_hoops_HRRRR |
										   event->_hoops_RRRPC->_hoops_ISCPGR,
										   event->_hoops_RRRPC->_hoops_SCGRR, event->_hoops_RRRPC->mouse_y);
			event->_hoops_RRRPC->_hoops_IRRRR = true;
		}	break;

		case ButtonRelease: {
			_hoops_SPAPGR ("button release event", event->_hoops_RRRPC);

			switch (_hoops_GSSPC.xbutton.button) {
			case Button1: event->_hoops_RRRPC->_hoops_HRRRR &= ~1; break;
			case Button2: event->_hoops_RRRPC->_hoops_HRRRR &= ~2; break;
			case Button3: event->_hoops_RRRPC->_hoops_HRRRR &= ~4; break;
			}

			event->_hoops_RRRPC->_hoops_SCGRR = _hoops_GSSPC.xbutton.x;
			event->_hoops_RRRPC->mouse_y = event->_hoops_RRRPC->yfudge - _hoops_GSSPC.xbutton.y;
			HD_Queue_Pixel_Location_Event (event->dc,
										   event->_hoops_RRRPC->_hoops_HRRRR |
										   event->_hoops_RRRPC->_hoops_ISCPGR,
										   event->_hoops_RRRPC->_hoops_SCGRR, event->_hoops_RRRPC->mouse_y);
			event->_hoops_RRRPC->_hoops_IRRRR = true;
		}	break;

		case CirculateNotify: {
			_hoops_SPAPGR ("circulate notify event", event->_hoops_RRRPC);
		}	break;

		case CirculateRequest: {
			_hoops_SPAPGR ("circulate request event", event->_hoops_RRRPC);
		}	break;

		case ClientMessage: {
			Atom wm_protocols;

			_hoops_SPAPGR ("client message event", event->_hoops_RRRPC);
			wm_protocols = XInternAtom (event->_hoops_RRRPC->display, "WM_PROTOCOLS", True);

			if (_hoops_GSSPC.xclient.message_type == wm_protocols) {
				Atom		   wm_delete_window;

				wm_delete_window = XInternAtom (event->_hoops_RRRPC->display,
												"WM_DELETE_WINDOW", True);

				if (wm_delete_window == (Atom)_hoops_GSSPC.xclient.data.l[0]) {
					if (event->dc->options._hoops_GASSP && !event->dc->options._hoops_IRSSP)
						HI_Queue_Special_Event (dc->_hoops_RIGC, "X11:DeleteWindow",
							HI_Build_Special_Event_String (event_string, "X11", event->dc->_hoops_AAHSR,
								(long)event->_hoops_RRRPC->window, -1));
					else {
						HD_Kill_Driver(event->dc);
						_hoops_RRRPC->_hoops_HPSPGR = false;
						_hoops_HPIS = false;
						goto _hoops_PRSPR;
					}
				}
			}
			else {
#			ifdef _hoops_ICIGI
				char   _hoops_SHSPGR[128];

				XJp_string (&_hoops_GSSPC, _hoops_SHSPGR, 128, XJP_EUC);
				_hoops_RRSPGR (event->dc, _hoops_SHSPGR);
#			endif /* _hoops_ARSPGR */
			}
		}	break;

		case ColormapNotify: {
			_hoops_SPAPGR ("colormap notify event", event->_hoops_RRRPC);
		}	break;

		case ConfigureNotify: {
			int								x, y;
			unsigned int	width, height;

			_hoops_SPAPGR ("configure notify event", event->_hoops_RRRPC);

			/*
			 *		_hoops_SIPR _hoops_RGCI _hoops_CPAP _hoops_PPR _hoops_CRGS _hoops_IRISR.
			 *		_hoops_CCRAA-_hoops_ISPR - _hoops_GISPGR _hoops_GPGH'_hoops_RA _hoops_SHR _hoops_RPHR.
			 */

			_hoops_RASPGR (event->_hoops_RRRPC, &x, &y, &width, &height);

#			ifdef _hoops_HPAPGR
			fprintf (stderr,
					 "X11 Sequence: configure resize notify (%d x %d) @ (%d, %d) %p\n",
					 width, height, x, y, (void*)event->_hoops_RRRPC);
#			endif /* _hoops_SHRS */

			if ((event->_hoops_RRRPC->window_x != x) || (event->_hoops_RRRPC->window_y != y)) {
				_hoops_CPAPGR("position changed", event->_hoops_RRRPC);

				/*
				 *		_hoops_PGPR _hoops_AGRP _hoops_RH _hoops_APAPC _hoops_RPPS _hoops_AHC _hoops_PCRR
				 *		_hoops_RPP _hoops_GAPGH _hoops_HGIPR _hoops_HRGR _hoops_PHRH.
				 */

				if (event->dc->options._hoops_RASSP) {
					event->_hoops_RRRPC->window_x = x;
					event->_hoops_RRRPC->window_y = y;
					event->_hoops_GHSPGR = true;
				}
				else {
					event->_hoops_RHSPGR = true;
				}
			}

			if ((event->_hoops_RRRPC->window_width == width) &&
				(event->_hoops_RRRPC->window_height == height)) {
				_hoops_CPAPGR("resize not pending", event->_hoops_RRRPC);
				event->_hoops_CGRRR = false;
			}
			else {
				if (event->_hoops_RRRPC->_hoops_RISPGR) {
					_hoops_CPAPGR("resize in progress", event->_hoops_RRRPC);
					event->_hoops_RRRPC->window_width = width;
					event->_hoops_RRRPC->window_height = height;

					/* _hoops_AISPGR _hoops_CIS _hoops_RHCA */
					_hoops_RRRPC->_hoops_HPSPGR = false;
					_hoops_HPIS = true;
					goto _hoops_PRSPR;
				}
				else {
					_hoops_CPAPGR("resize confirmed", event->_hoops_RRRPC);
					event->_hoops_PHSPGR = x;
					event->_hoops_HHSPGR = y;
					event->_hoops_IHSPGR = width;
					event->_hoops_CHSPGR = height;
					event->_hoops_CGRRR = true;

					if (event->_hoops_RRRPC->driver_type == _hoops_PPAPC) {
						if (event->_hoops_RRRPC->_hoops_PHAPC)
							XResizeWindow (event->_hoops_RRRPC->display,event->_hoops_RRRPC->_hoops_RHSPC,
										   width,height);
					}

					event->_hoops_GHSPGR = false;
					event->_hoops_RHSPGR = false;
				}
			}
			if (event->dc->options._hoops_GASSP && !event->dc->options._hoops_IRSSP) {
				HI_Queue_Special_Event (dc->_hoops_RIGC,"X11:ConfigureNotify",
					HI_Build_Special_Event_String (event_string, "X11", event->dc->_hoops_AAHSR,
						(long)event->_hoops_RRRPC->window, -1));
			}
		}	break;

		case ConfigureRequest: {
			_hoops_SPAPGR ("configure request event", event->_hoops_RRRPC);
		}	break;

		case CreateNotify: {
			_hoops_SPAPGR ("create notify event", event->_hoops_RRRPC);
		}	break;

		case DestroyNotify: {
			_hoops_SPAPGR ("destroy notify event", event->_hoops_RRRPC);
		}	break;

		case EnterNotify: {
			_hoops_SPAPGR ("enter notify event", event->_hoops_RRRPC);
		}	break;

		case Expose: {
			Int_Rectangle tmp;

			_hoops_SPAPGR ("exposure event", event->_hoops_RRRPC);

#			ifdef _hoops_HPAPGR
			fprintf (stderr,
					 "X11 Sequence: exposure notify (%d x %d) @ (%d, %d) %p\n",
					 _hoops_GSSPC.xexpose.width, _hoops_GSSPC.xexpose.height,
					 _hoops_GSSPC.xexpose.x, _hoops_GSSPC.xexpose.y, (void*)event->_hoops_RRRPC);
#			endif /* _hoops_SHRS */

			tmp.left = _hoops_GSSPC.xexpose.x;
			tmp.right = _hoops_GSSPC.xexpose.x + _hoops_GSSPC.xexpose.width - 1;

#ifdef AIX_SYSTEM
			if (event->_hoops_RRRPC->driver_type == GL_ON_X11 &&
				event->_hoops_RRRPC->_hoops_SPSPGR[3] == 'G' && event->_hoops_RRRPC->_hoops_SPSPGR[4] == 'X' &&
				event->_hoops_RRRPC->_hoops_SPSPGR[5] == 'T') {
				tmp.top = event->_hoops_RRRPC->yfudge -
					(_hoops_GSSPC.xexpose.y - (1024-event->_hoops_RRRPC->yfudge+1));
				tmp.bottom = event->_hoops_RRRPC->yfudge -
					(_hoops_GSSPC.xexpose.y - (1024-event->_hoops_RRRPC->yfudge+1)) -
					_hoops_GSSPC.xexpose.height - 1;
			} else {
				tmp.top = event->_hoops_RRRPC->yfudge - _hoops_GSSPC.xexpose.y;
				tmp.bottom = event->_hoops_RRRPC->yfudge - _hoops_GSSPC.xexpose.y -
					_hoops_GSSPC.xexpose.height - 1;
			}
#else
			tmp.top = event->_hoops_RRRPC->yfudge - _hoops_GSSPC.xexpose.y;
			tmp.bottom = event->_hoops_RRRPC->yfudge - _hoops_GSSPC.xexpose.y -
				_hoops_GSSPC.xexpose.height - 1;
#endif /* _hoops_ICAPR */

			if (event->_hoops_AHSPGR) {
				if (event->_hoops_PISPGR.left > tmp.left)
					event->_hoops_PISPGR.left = tmp.left;
				if (event->_hoops_PISPGR.right < tmp.right)
					event->_hoops_PISPGR.right = tmp.right;
				if (event->_hoops_PISPGR.bottom > tmp.bottom)
					event->_hoops_PISPGR.bottom = tmp.bottom;
				if (event->_hoops_PISPGR.top < tmp.top)
					event->_hoops_PISPGR.top = tmp.top;
			} else {
				event->_hoops_PISPGR.left = tmp.left;
				event->_hoops_PISPGR.right = tmp.right;
				event->_hoops_PISPGR.bottom = tmp.bottom;
				event->_hoops_PISPGR.top = tmp.top;
				event->_hoops_AHSPGR = true;
			}
			if ((event->dc->options._hoops_GASSP) &&
				(!event->dc->options._hoops_IRSSP)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC, "X11:Expose",
					HI_Build_Special_Event_String (event_string,"X11", event->dc->_hoops_AAHSR,
						(long)event->_hoops_RRRPC->window, -1));
			}
		}	break;

		case FocusIn: {
			_hoops_SPAPGR ("focus-in event", event->_hoops_RRRPC);

#			ifdef X11R3
			if (event->_hoops_RRRPC->_hoops_HISPGR) {
				if ((event->_hoops_RRRPC->_hoops_GPIHP != event->_hoops_RRRPC->_hoops_IAIPGR) &&
					!event->_hoops_RRRPC->_hoops_SAIPGR) {
					XInstallColormap(event->_hoops_RRRPC->display, event->_hoops_RRRPC->_hoops_GPIHP);
					event->_hoops_RRRPC->_hoops_SAIPGR = true;
				}
			}
			event->_hoops_RRRPC->_hoops_GPIPGR = true;
#								endif /* _hoops_RPIPGR */
			if ((event->dc->options._hoops_GASSP) &&
				(!event->dc->options._hoops_IRSSP)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC,"X11:FocusIn",
					HI_Build_Special_Event_String (event_string, "X11", event->dc->_hoops_AAHSR,
						(long)event->_hoops_RRRPC->window, -1));
			}
		}	break;

		case FocusOut: {
			_hoops_SPAPGR ("focus-out event", event->_hoops_RRRPC);

#			ifdef X11R3
			if (event->_hoops_RRRPC->_hoops_HISPGR) {
				if ((event->_hoops_RRRPC->_hoops_GPIHP != event->_hoops_RRRPC->_hoops_IAIPGR) &&
					event->_hoops_RRRPC->_hoops_SAIPGR) {
					XUninstallColormap (event->_hoops_RRRPC->display, event->_hoops_RRRPC->_hoops_GPIHP);
					event->_hoops_RRRPC->_hoops_SAIPGR = false;
				}
			}
			event->_hoops_RRRPC->_hoops_GPIPGR = false;
#			endif /* _hoops_RPIPGR */
			if ((event->dc->options._hoops_GASSP) &&
				(!event->dc->options._hoops_IRSSP)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC,"X11:FocusOut",
					HI_Build_Special_Event_String (event_string, "X11", event->dc->_hoops_AAHSR,
						(long)event->_hoops_RRRPC->window, -1));
			}
		}	break;

		case GraphicsExpose: {
			_hoops_SPAPGR ("graphics expose event", event->_hoops_RRRPC);
		}	break;

		case GravityNotify: {
			_hoops_SPAPGR ("gravity notify event", event->_hoops_RRRPC);
		}	break;

		case KeymapNotify: {
			_hoops_SPAPGR ("keymap notify event", event->_hoops_RRRPC);
		}	break;

		case KeyPress: {
			_hoops_SPAPGR ("key press event", event->_hoops_RRRPC);
			_hoops_ACCPGR (event->dc, (void alter *)&_hoops_GSSPC,&event->_hoops_RRRPC->_hoops_HCCPGR, event->_hoops_RRRPC->display);
		}	break;

		case KeyRelease: {
			_hoops_SPAPGR ("key release event", event->_hoops_RRRPC);
			_hoops_GRSPGR (event->dc, (void alter *)&_hoops_GSSPC);
		}	break;

		case LeaveNotify: {
			_hoops_SPAPGR ("leave notify event", event->_hoops_RRRPC);
		}	break;

		case MapNotify: {
			_hoops_SPAPGR ("map notify event", event->_hoops_RRRPC);

			if ((dc->options._hoops_GASSP) &&
				(!dc->options._hoops_IRSSP) &&
				(_hoops_GSSPC.xmap.window == _hoops_RRRPC->window)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC,"X11:MapNotify",
					HI_Build_Special_Event_String (event_string, "X11", dc->_hoops_AAHSR,
						(long)_hoops_RRRPC->window, _hoops_GSSPC.type));
			}
		}	break;

		case MappingNotify: {
			_hoops_SPAPGR ("mapping notify event", event->_hoops_RRRPC);
		}	break;

		case MapRequest: {
			_hoops_SPAPGR ("map request event", event->_hoops_RRRPC);
		}	break;

		case MotionNotify: {
			_hoops_SPAPGR ("motion notify event", event->_hoops_RRRPC);

			event->_hoops_RRRPC->_hoops_SCGRR = _hoops_GSSPC.xmotion.x;
			event->_hoops_RRRPC->mouse_y = event->_hoops_RRRPC->yfudge - _hoops_GSSPC.xmotion.y;
		}	break;

		case NoExpose: {
			_hoops_SPAPGR ("no expose event", event->_hoops_RRRPC);
		}	break;

		case PropertyNotify: {
			_hoops_SPAPGR ("property notify event", event->_hoops_RRRPC);
		}	break;

		case ReparentNotify: {
			_hoops_SPAPGR ("reparent event", event->_hoops_RRRPC);

			if (!event->dc->options._hoops_CRSSP)
				_hoops_PRSPGR (event->_hoops_RRRPC, StructureNotifyMask);
			if ((event->dc->options._hoops_GASSP) &&
				(!event->dc->options._hoops_IRSSP)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC, "X11:ReparentNotify",
					HI_Build_Special_Event_String (event_string, "X11", event->dc->_hoops_AAHSR,
						(long)event->_hoops_RRRPC->window, -1));
			}
		}	break;

		case ResizeRequest: {
			_hoops_SPAPGR ("resize request event", event->_hoops_RRRPC);
		}	break;

		case SelectionClear: {
			_hoops_SPAPGR ("selection clear event", event->_hoops_RRRPC);
		}	break;

		case SelectionNotify: {
			_hoops_SPAPGR ("selection notify event", event->_hoops_RRRPC);
		}	break;

		case SelectionRequest: {
			_hoops_SPAPGR ("selection request event", event->_hoops_RRRPC);
		}	break;

		case UnmapNotify: {
			_hoops_SPAPGR ("unmap notify event", event->_hoops_RRRPC);

			if ((dc->options._hoops_GASSP) &&
				(!dc->options._hoops_IRSSP) &&
				(_hoops_GSSPC.xunmap.window == _hoops_RRRPC->window)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC,"X11:UnmapNotify",
					HI_Build_Special_Event_String (event_string, "X11", dc->_hoops_AAHSR,
						(long)_hoops_RRRPC->window, _hoops_GSSPC.type));
			}
		}	break;

		case VisibilityNotify: {
			_hoops_SPAPGR ("visibility notify event", event->_hoops_RRRPC);
		}	break;

		default: {
#ifdef _hoops_IPAPGR
			fprintf (stderr, "X11 Sequence: unknown event %d\n", _hoops_GSSPC.type);
#endif

#if defined(_hoops_IISPGR) || defined(_hoops_CISPGR)
			if (! _hoops_SISPGR(&_hoops_GSSPC, event) &&
				(event->dc->options._hoops_GASSP) &&
				(! event->dc->options._hoops_IRSSP)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC, "X11:HoopsUnknownEvent",
					HI_Build_Special_Event_String (event_string, "X11", event->dc->_hoops_AAHSR,
						(long)event->_hoops_RRRPC->window, _hoops_GSSPC.type));
			}
#else
			if ((event->dc->options._hoops_GASSP) &&
				(!event->dc->options._hoops_IRSSP)) {
				HI_Queue_Special_Event (dc->_hoops_RIGC, "X11:HoopsUnknownEvent",
					HI_Build_Special_Event_String (event_string, "X11", event->dc->_hoops_AAHSR,
						(long)event->_hoops_RRRPC->window, _hoops_GSSPC.type));
			}
#endif
		}	break;
		}/*_hoops_RSGR _hoops_CICA (_hoops_PGRRR._hoops_GPRR)*/
	}

	if ((event = _hoops_SASPGR) != null) do {
		if (event->_hoops_AHSPGR || event->_hoops_GHSPGR || event->_hoops_RHSPGR || event->_hoops_CGRRR) {
			if (!_hoops_GPSPGR) {
				_hoops_GPSPGR = true;
			}

			if (event->_hoops_AHSPGR) {
				_hoops_CPAPGR("forcing partial refresh", event->_hoops_RRRPC);

#ifdef AIX_SYSTEM
				/*
				 *		_hoops_PAAS _hoops_SGGHA _hoops_RH _hoops_IIIGC _hoops_SCHGR _hoops_IAPR _hoops_RH _hoops_GPAAC _hoops_SCHGR _hoops_GPP
				 *		_hoops_ICAPR, _hoops_IRS _hoops_SPPP _hoops_ARPC _hoops_HICP _hoops_GAPA _hoops_IIIGC _hoops_PPR _hoops_GPAAC
				 *		_hoops_PPR _hoops_IIIGC _hoops_IRHS _hoops_IS _hoops_ACPA _hoops_CGPR _hoops_PCCP _hoops_ICPIP _hoops_SSCP _hoops_RIPRGR.  _hoops_SRPAI,
				 *		_hoops_RRI _hoops_PASI, _hoops_CGPR _hoops_IRS _hoops_GGSHR _hoops_ISSC _hoops_PPR _hoops_GCSPGR _hoops_HII _hoops_GPAAC
				 *		_hoops_IS _hoops_IIIGC _hoops_SSCP _hoops_RIPRGR ... _hoops_HIH _hoops_SGS _hoops_SR _hoops_PAH'_hoops_RA _hoops_HIRAI _hoops_HIS _hoops_SR
				 *		_hoops_ARP _hoops_RGR _hoops_SGPSI _hoops_RIP.
				 *
				 *		_hoops_HGI _hoops_ICAPR _hoops_SGPSI _hoops_CGH _hoops_SHH _hoops_PARSI _hoops_IASH _hoops_IIGR _hoops_HPGR _hoops_RH
				 *		_hoops_CICIP _hoops_ASGAR.
				 */

				event->_hoops_RRRPC->_hoops_RCSPGR = true;
#endif /* _hoops_ICAPR */

				HD_Force_Partial_Refresh(event->dc, event->_hoops_PISPGR.left, event->_hoops_PISPGR.right,
										 event->_hoops_PISPGR.bottom, event->_hoops_PISPGR.top);
			}

			if (event->_hoops_CGRRR) {
				_hoops_CPAPGR("resizing subscreen", event->_hoops_RRRPC);
				if (event->_hoops_CHSPGR == 1) /* _hoops_PAAS _hoops_APPS _hoops_HRGR 1 _hoops_AGAH _hoops_ACSPGR _hoops_AGGRR = _hoops_PGRCR */
					event->_hoops_CHSPGR = 2;

				event->_hoops_RRRPC->_hoops_HCCPGR = _hoops_RGSPGR;

				HD_Resize_Subscreen (event->dc, true,
									 event->_hoops_PHSPGR,
									 event->_hoops_PHSPGR + event->_hoops_IHSPGR - 1,
									 event->dc->_hoops_PGCC._hoops_PRPSR.y - (event->_hoops_HHSPGR + event->_hoops_CHSPGR),
									 event->dc->_hoops_PGCC._hoops_PRPSR.y - 1 - event->_hoops_HHSPGR);

				event->_hoops_RRRPC->window_x = event->_hoops_PHSPGR;
				event->_hoops_RRRPC->window_y = event->_hoops_HHSPGR;
				event->_hoops_RRRPC->window_width = event->_hoops_IHSPGR;
				event->_hoops_RRRPC->window_height = event->_hoops_CHSPGR;

				if (event->_hoops_RRRPC->_hoops_PCSPGR) {
					XmbufDestroyBuffers (event->_hoops_RRRPC->display, event->_hoops_RRRPC->window);

					if (XmbufCreateBuffers (event->_hoops_RRRPC->display, event->_hoops_RRRPC->window, 2,
											MultibufferUpdateActionUntouched,
											MultibufferUpdateHintFrequent,
											event->_hoops_RRRPC->_hoops_HCSPGR) != 2) {
						HE_ERROR (HEC_X11_DRIVER, HES_CREATE_MULTIBUFFER_FAILED,
								  "X11 Driver: Could not create 2 X11 Multibuffers");
						HD_Kill_Driver (event->dc);
					}

					event->_hoops_RRRPC->_hoops_ICSPGR = 1;
					event->_hoops_RRRPC->_hoops_SRASH = event->_hoops_RRRPC->_hoops_HCSPGR[event->_hoops_RRRPC->_hoops_ICSPGR];
				}
				else if (event->_hoops_RRRPC->_hoops_CCSPGR) {
					XFreePixmap (event->_hoops_RRRPC->display, event->_hoops_RRRPC->_hoops_CCSPGR);
					event->_hoops_RRRPC->_hoops_CCSPGR = (Pixmap)0;
					event->_hoops_RRRPC->_hoops_CCSPGR = XCreatePixmap (event->_hoops_RRRPC->display,
																   event->_hoops_RRRPC->window,
																   event->_hoops_RRRPC->window_width,
																   event->_hoops_RRRPC->window_height,
																   event->_hoops_RRRPC->depth);
					event->_hoops_RRRPC->_hoops_SRASH = event->_hoops_RRRPC->_hoops_CCSPGR;
				}
			}
			else if (event->_hoops_GHSPGR) {
				_hoops_CPAPGR ("moving subscreen", event->_hoops_RRRPC);
				event->_hoops_RRRPC->_hoops_HCCPGR = _hoops_RGSPGR;
				HD_Resize_Subscreen (event->dc, true,
									 event->_hoops_RRRPC->window_x,
									 event->_hoops_RRRPC->window_x + event->_hoops_RRRPC->window_width - 1,
									 event->dc->_hoops_PGCC._hoops_PRPSR.y - (event->_hoops_RRRPC->window_y + event->_hoops_RRRPC->window_height),
									 event->dc->_hoops_PGCC._hoops_PRPSR.y - 1 - event->_hoops_RRRPC->window_y);
			}
			else if ((event->_hoops_RHSPGR) && (event->dc->options._hoops_GCHSR == 0 &&
													event->dc->options._hoops_ISPRP == 0)) {
				_hoops_CPAPGR ("moving window back", event->_hoops_RRRPC);
				_hoops_GASPGR (event->dc,
									  &(event->_hoops_RRRPC->window_x), &(event->_hoops_RRRPC->window_y),
									  &(event->_hoops_RRRPC->window_width), &(event->_hoops_RRRPC->window_height));
				XMoveWindow (event->_hoops_RRRPC->display, event->_hoops_RRRPC->window,
							 event->_hoops_RRRPC->window_x, event->_hoops_RRRPC->window_y);
			}
		}


		{
			X11_Event_Info * victim = event;

			event = event->next;
			FREE (victim, X11_Event_Info);
		}
	} _hoops_RGGA (event == null);

	if (_hoops_GPSPGR) {

		if (!BIT(dc->flags, _hoops_GIRIP) &&
			!BIT (_hoops_RSPPR(dc->_hoops_RIGC, flags), _hoops_GRSCA) &&
			!BIT (dc->_hoops_RIGC->flags, _hoops_RRSCA)) 
			/* _hoops_IAGC _hoops_IRS _hoops_CCAH _hoops_PAAP  */
			HI_Queue_Actor_Update(dc->_hoops_GHRI, false);

		_hoops_RRRPC->_hoops_HPSPGR = false;
		_hoops_HPIS = true;
	}

_hoops_PRSPR:
	_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
	_hoops_RRRPC->_hoops_HPSPGR = false;
	return _hoops_HPIS;
}


/*
 *		** _hoops_SRAC **
 *
 *		_hoops_SCSPGR _hoops_GISAP _hoops_ACAGR.
 */
local bool _hoops_HSCSP (
		Display_Context const		*dc,
		int alter										*button,
		int alter										*x,
		int alter										*y) {
		X11Data alter							*_hoops_RRRPC = X11D(dc);

		/* _hoops_GSSPGR (_hoops_CSPH, "_hoops_IAGC _hoops_ACAGR"); */

		_hoops_RRRPC->_hoops_IRRRR = false;
		check_events (dc);

		if (_hoops_RRRPC->_hoops_IRRRR)
				return false;
		else {
				*button = _hoops_RRRPC->_hoops_HRRRR;
				*x = _hoops_RRRPC->_hoops_SCGRR;
				*y = _hoops_RRRPC->mouse_y;
				return true;
		}
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_SCSPGR _hoops_CIIRH _hoops_CIIA.
 */
local bool _hoops_ISCSP (
		Display_Context const		*dc,
		int alter										*button,
		int alter										*status) {
		UNREFERENCED (button);
		UNREFERENCED (status);

		/* _hoops_GSSPGR (_hoops_CSPH, "_hoops_IAGC _hoops_CIIRH"); */

		check_events (dc);
		return false;
}


/*****************************************************************
 *****************************************************************
                   _hoops_RSSPGR _hoops_HPARR _hoops_ASSPGR _hoops_IPARR
 *****************************************************************
 *****************************************************************/

typedef
struct _hoops_PSSPGR {
	struct _hoops_PSSPGR * next;
	char * name;
	Display * display;
} _hoops_HSSPGR;


static _hoops_HSSPGR * _hoops_ISSPGR = 0;
static _hoops_HSSPGR * _hoops_CSSPGR = 0;

static void
_hoops_SSSPGR(void)
{
	_hoops_HSSPGR * d;

	while ((d=_hoops_ISSPGR)) {
		_hoops_ISSPGR = d->next;
		XCloseDisplay(d->display);
		free(d->name);
		free(d);
	}

	if (_hoops_CSSPGR) {

		HE_ERROR (HEC_X11_DRIVER, HES_X11_SYSTEM_ERROR,
			   "Shutdown with X11 display still used");

		while ((d=_hoops_CSSPGR)) {
			_hoops_CSSPGR = d->next;
			XCloseDisplay(d->display);
			free(d->name);
			free(d);
		}
	}
}



extern void*
HD_Find_X11_Display(char const * const name)
{
	_hoops_HSSPGR * d;
	_hoops_HSSPGR ** backlink;
	Display * _hoops_GGGHGR = 0;

	HOOPS_WORLD->_hoops_CIHPH = _hoops_SSSPGR;

	/* _hoops_HHCS _hoops_IS _hoops_ASRC _hoops_IRS _hoops_AIRI _hoops_GGR _hoops_RH _hoops_RGGHGR _hoops_RPP _hoops_IRS _hoops_PSSP _hoops_HRGR _hoops_GSGI */
	backlink = &_hoops_ISSPGR;
	for (d = _hoops_ISSPGR; d != 0; d = d->next) {
		if (strcmp(name, d->name) == 0) {
			*backlink = d->next;
			d->next = _hoops_CSSPGR;
			_hoops_CSSPGR = d;
			return d->display;
		}
		backlink = &d->next;
	}

	/* _hoops_IGS _hoops_IRS _hoops_CCAH _hoops_AIRI */
	_hoops_GGGHGR = XOpenDisplay(name);
	if (!_hoops_GGGHGR)
		return 0;

	/* _hoops_HHCS _hoops_IS _hoops_GGCR _hoops_RGR _hoops_AIRI _hoops_IS _hoops_RH _hoops_HSAAI _hoops_RGGHGR */
	d = (_hoops_HSSPGR*) malloc(sizeof(_hoops_HSSPGR));
	d->name = (char*)malloc(strlen(name)+1);
	_hoops_AAHR(name,d->name);
	d->display = _hoops_GGGHGR;
	d->next = _hoops_CSSPGR;
	_hoops_CSSPGR = d;

	return (void*)_hoops_GGGHGR;
}

extern void
HD_Free_X11_Display(void const *_hoops_AGGHGR)
{
	_hoops_HSSPGR * d;
	_hoops_HSSPGR ** backlink;
	Display * _hoops_GGGHGR = (Display*)_hoops_AGGHGR;

	for (d = _hoops_ISSPGR; d != 0; d = d->next) {
		if (_hoops_GGGHGR == d->display) {
			HE_ERROR (HEC_X11_DRIVER, HES_X11_SYSTEM_ERROR,
			   "Double free of X11 display");
			return;
		}
	}

	/* _hoops_HHCS _hoops_IS _hoops_ASRC _hoops_IRS _hoops_AIRI _hoops_GGR _hoops_RH _hoops_RGGHGR _hoops_RPP _hoops_IRS _hoops_PSSP _hoops_HRGR _hoops_GSGI */
	backlink = &_hoops_CSSPGR;
	for (d = _hoops_CSSPGR; d != 0; d = d->next) {
		if (_hoops_GGGHGR == d->display) {
			*backlink = d->next;
			d->next = _hoops_ISSPGR;
			_hoops_ISSPGR = d;
			return;
		}
		backlink = &d->next;
	}

	HE_ERROR (HEC_X11_DRIVER, HES_X11_SYSTEM_ERROR,
			   "Unknown X11 display freed");
}




/****************************************************************
 ****************************************************************
				  _hoops_HRAIA _hoops_AHGPH _hoops_AHGPH _hoops_RGGIR _hoops_AHGPH		   _hoops_CIPII _hoops_RAIGR _hoops_PGGIR _hoops_APCAR _hoops_ISAII _hoops_HRAIA _hoops_AHGPH _hoops_IISGA
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_PGAA **
 *
 */
local void _hoops_PGGHGR (char alter * _hoops_HGGHGR) {
	char const * _hoops_IGGHGR;

#	ifdef VMS_SYSTEM
	extern char * strerror(int _hoops_CGGHGR, ...);

	_hoops_IGGHGR = strerror (errno, vaxc$errno);
#	else /* _hoops_SGGHGR */
	/*_hoops_CPCPI*/
	_hoops_IGGHGR = strerror (errno);
#   endif /* _hoops_SGGHGR */
	Sprintf_S (_hoops_HGGHGR, "The system message was '%s'", _hoops_IGGHGR);
}




/*
 *		** _hoops_PGAA **
 *
 */
local int _hoops_GRGHGR (Display alter * display,
						 XErrorEvent alter	* err)
{
#ifdef HOOPS_DEBUG_BUILD
	char _hoops_RHCGC[MAX_ERRMSG];

#ifdef SOLARIS_SYSTEM
	int _hoops_RRGHGR = (int)err->request_code;

	/*_hoops_RGR _hoops_ARGHGR _hoops_PRGHGR _hoops_SPHS*/
	if (_hoops_RRGHGR == 89) return 0;
#endif

#ifdef AIX_SYSTEM
	int _hoops_RRGHGR = (int)err->request_code;

	/* _hoops_HRGHGR _hoops_GPRHP _hoops_IRGHGR _hoops_CRGHGR. _hoops_IIIGC _hoops_PPR _hoops_SRGHGR
	 * _hoops_GAGHGR _hoops_AAAA _hoops_IRS _hoops_RAGHGR _hoops_IH _hoops_AAGHGR _hoops_PPCIP
	 * _hoops_ICAH _hoops_IS _hoops_PAGHGR _hoops_RGR _hoops_CPRH
	 */
	if (_hoops_RRGHGR == 2) return 0;
#endif

	/* _hoops_PIP: _hoops_CGH _hoops_SHH "_hoops_SRPC _hoops_HAGHGR" _hoops_AHSAR "_hoops_SCSH" _hoops_HRGR _hoops_PCPA _hoops_IAGHGR _hoops_CPPHR */
	if (err->request_code < _hoops_GGAPR(_hoops_IHAPGR)) {
		Sprintf_SD (_hoops_RHCGC, "%s, minor code %d",
					_hoops_IHAPGR[err->request_code], err->minor_code);
		HE_ERROR2 (HEC_X11_DRIVER, HES_X11_SYSTEM_ERROR,
				   "Unexpected X11 system error in", _hoops_RHCGC);
	}
	XGetErrorText (display, (int)err->error_code, _hoops_RHCGC,
				   sizeof(_hoops_RHCGC));


	HE_ERROR2 (HEC_X11_DRIVER,
			   HES_X11_SYSTEM_ERROR,
			   "Unexpected X11 system error -",
			   _hoops_RHCGC);
#else
	UNREFERENCED(display);
	UNREFERENCED(err);
#endif

	return 0; /* _hoops_ASRC _hoops_PIRA _hoops_PPRAR */
}



/*
 *		** _hoops_PGAA **
 *
 */
local int _hoops_CAGHGR (Display alter * display)
{
	char _hoops_RHCGC[MAX_ERRMSG];

	/* _hoops_IRHH _hoops_SGH _hoops_IIGR _hoops_SAGHGR _hoops_SRS _hoops_IIGR _hoops_HCR, _hoops_ARPP _hoops_SCH _hoops_SHPH */
	_hoops_PGGHGR (_hoops_RHCGC);

	HE_ERROR2 (HEC_X11_DRIVER,
			   HES_X11_FATAL_IO_ERROR,
			   "Unexpected X11 \"fatal IO error\" -",
			   _hoops_RHCGC);

	return 0; /* _hoops_ASRC _hoops_PIRA _hoops_PPRAR */
}



/*
 *		** _hoops_PGAA **
 *
 */
local int _hoops_GPGHGR (Display alter * display,
							XErrorEvent alter * err)
{
	UNREFERENCED (display);
	UNREFERENCED (err);
	return 0; /* _hoops_ASRC _hoops_PIRA _hoops_PPRAR */
}



/*
 *		** _hoops_PGAA **
 *
 */
local int _hoops_RPGHGR (Display alter * display)
{
	UNREFERENCED (display);
	return 0; /* _hoops_ASRC _hoops_PIRA _hoops_PPRAR */
}



/****************************************************************
 ****************************************************************
			   _hoops_APCAR _hoops_HRAIA _hoops_RRGGR _hoops_GHAP _hoops_IHRPR _hoops_HRAIA	  _hoops_RPRAR _hoops_RAIGR _hoops_GHAP _hoops_PGGIR _hoops_SAAAR _hoops_HRAIA _hoops_PGGIR _hoops_RAIGR _hoops_PGGIR _hoops_IHRPR _hoops_HRAIA
 ****************************************************************
 ****************************************************************/


/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_SAGGR _hoops_RH '_hoops_AAH' _hoops_RAHRH _hoops_IH _hoops_RH '_hoops_AAH' _hoops_SHPR _hoops_HCH
 *		_hoops_IRPR _hoops_IH _hoops_RH _hoops_AIRI _hoops_PPR _hoops_SHPR _hoops_GGR _hoops_RHGHS.
 *		_hoops_PS _hoops_APGHGR _hoops_SGAPC _hoops_SRS _hoops_GPP _hoops_HCH, _hoops_PSCR _hoops_GPP _hoops_CSHGR.
 */
local void _hoops_PPGHGR		(Display_Context const		 *dc) {
	X11Data alter			*_hoops_RRRPC = X11D(dc);
	XVisualInfo				_hoops_HPGHGR, *_hoops_IPGHGR;
	int						_hoops_CPGHGR;
	int						_hoops_ACCAA = -1;


	_hoops_CPAPGR ("get best visual", _hoops_RRRPC);

	if (_hoops_RRRPC->driver_type == _hoops_PPAPC) {
		(*_hoops_RRRPC->_hoops_IAAPC)(dc);
		return;
	}

#ifdef _hoops_GIAPGR
	_hoops_RRRPC->_hoops_SPGHGR = false;
#else

		/* _hoops_RGR _hoops_HRGR _hoops_IH _hoops_GHGHGR _hoops_AIRI _hoops_IS _hoops_IPCGC*/
		/* _hoops_SCH _hoops_RHGHGR _hoops_AHGHGR _hoops_PPR _hoops_PHGHGR _hoops_GPP _hoops_HHGHGR*/
		/* _hoops_GHAP _hoops_HPCAR _hoops_RGR _hoops_ARIP _hoops_IIGR _hoops_IIH _hoops_RAHAI _hoops_IHGHGR _hoops_CHGHGR*/
		if (_hoops_RRRPC->_hoops_APHPGR == _hoops_SHGHGR)
				  _hoops_RRRPC->_hoops_SPGHGR=false;

		if (_hoops_RRRPC->_hoops_SPGHGR) {
				XVisualInfo* XvisInfo;
				int _hoops_SISAR = 0;
				int _hoops_GIGHGR = 0;
				int _hoops_RIGHGR = 0;
				int i = 0;
				XmbufBufferInfo *_hoops_ACAPGR, *_hoops_HCAPGR;
				int _hoops_RCAPGR = 0;
				int _hoops_PCAPGR = 0;



				_hoops_IPGHGR = null;

				if (!XmbufGetScreenInfo(_hoops_RRRPC->display,
										DefaultRootWindow(_hoops_RRRPC->display),
										&_hoops_RCAPGR,
										&_hoops_ACAPGR,
										&_hoops_PCAPGR, &_hoops_HCAPGR))
				{
						HE_ERROR (HEC_X11_DRIVER, HES_NO_MAPPED_VISAUL_TYPE,
										  "X11 Driver: No Mapped multibuffering Visual Type For Display!");
						HD_Kill_Driver (dc);
				}

				for (i = 0; i < _hoops_RCAPGR; i++)
				{
						if (_hoops_ACAPGR[i].depth > _hoops_SISAR)
								_hoops_SISAR = _hoops_ACAPGR[i].depth;
				}
				if (_hoops_SISAR > 24)
						_hoops_SISAR = 24;
				for (i = 0; i < _hoops_RCAPGR; i++)
				{
						if (_hoops_ACAPGR[i].depth >= _hoops_SISAR)
								_hoops_GIGHGR++;
				}
				_hoops_IPGHGR = (XVisualInfo*) calloc(_hoops_GIGHGR, sizeof(XVisualInfo));

				_hoops_RIGHGR = 0;
				for (i = 0; i < _hoops_RCAPGR; i++)
				{
						_hoops_HPGHGR.screen = DefaultScreen (_hoops_RRRPC->display);
						_hoops_HPGHGR.visualid = _hoops_ACAPGR[i].visualid;
						if (_hoops_ACAPGR[i].depth >= _hoops_SISAR)
						{
								XvisInfo = XGetVisualInfo(_hoops_RRRPC->display,
																				  VisualScreenMask | VisualIDMask,
																				  &_hoops_HPGHGR,
																				  &_hoops_CPGHGR);
								if (_hoops_CPGHGR > 0)
								{
										if (_hoops_CPGHGR > 1)
										{
												/* _hoops_SR _hoops_CGH _hoops_RGAR _hoops_HGCR 1 _hoops_RAHRH _hoops_RIR _hoops_CRSRR, _hoops_HRGR _hoops_RRHCP _hoops_GHPH */
												HE_ERROR (HEC_X11_DRIVER, HES_NO_MAPPED_VISAUL_TYPE,
																  "Internal Bug getting a visual by id");
										}

										/* _hoops_PRCHI(&_hoops_SGAPC[_hoops_AIGHGR], _hoops_PIGHGR, _hoops_GGHSP(_hoops_HIGHGR)); */
										_hoops_RSAI (XvisInfo, XVisualInfo, &_hoops_IPGHGR[_hoops_RIGHGR]);
										_hoops_RIGHGR++;
										XFree(XvisInfo);
								}
								else
								{
										_hoops_GIGHGR--;
								}
						}
				}
				if (_hoops_RIGHGR != _hoops_GIGHGR)
				{
						HE_ERROR (HEC_X11_DRIVER, HES_NO_MAPPED_VISAUL_TYPE,
										  "Internal Bug allocating array of visual information");
				}
				_hoops_CPGHGR = _hoops_GIGHGR;

				if (_hoops_ACAPGR)
						XFree(_hoops_ACAPGR);
				if (_hoops_HCAPGR)
						XFree(_hoops_HCAPGR);

								if ((_hoops_SISAR < 24) && (_hoops_SISAR != 8)) {
												/* _hoops_HHH _hoops_IHCSC _hoops_GGCA _hoops_CGPR _hoops_SR _hoops_HS _hoops_IRS _hoops_PSISI,
												 * _hoops_RII-_hoops_HSAR-24-_hoops_IGRH _hoops_SRHR, _hoops_HIS _hoops_SR'_hoops_GCPP _hoops_SRCH _hoops_SCH */
												/* *_hoops_ACAC _hoops_RGR _hoops_HRGR _hoops_PCCP _hoops_RIHSS _hoops_CGCHI _hoops_IIGHGR */
												_hoops_RRRPC->_hoops_SPGHGR = false;
												_hoops_PPGHGR(dc);
												return;
								}
		} else
#endif
		{
				_hoops_HPGHGR.screen = DefaultScreen (_hoops_RRRPC->display);
				_hoops_HPGHGR.depth = 24;
				do _hoops_IPGHGR = XGetVisualInfo (_hoops_RRRPC->display,
																		 VisualScreenMask | VisualDepthMask,
																		 &_hoops_HPGHGR,
																		 &_hoops_CPGHGR);
				_hoops_RGGA (_hoops_CPGHGR > 0 || --_hoops_HPGHGR.depth == 0);
		}

		_hoops_RGGA (_hoops_CPGHGR-- == 0)
		{
				if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
				{
						fprintf (stderr, "\nX11 Color: Visual %d is type ", _hoops_CPGHGR);
						if (_hoops_IPGHGR[_hoops_CPGHGR].c_class > 0 &&
								_hoops_IPGHGR[_hoops_CPGHGR].c_class <= _hoops_GGAPR (_hoops_SHAPGR))
								fprintf (stderr, "%s ", _hoops_SHAPGR[_hoops_IPGHGR[_hoops_CPGHGR].c_class]);
						else
								fprintf (stderr, "Unknown ");
						fprintf (stderr, "of depth %d and %d bits-per-rgb\n",
										 _hoops_IPGHGR[_hoops_CPGHGR].depth,
										 _hoops_IPGHGR[_hoops_CPGHGR].bits_per_rgb);
						fprintf (stderr, "X11 Color: The colormap size is %d and the color masks are\n",
										 _hoops_IPGHGR[_hoops_CPGHGR].colormap_size);
						fprintf (stderr, "X11 Color: red mask = %ld, green mask = %ld, and blue mask = %ld\n",
										 _hoops_IPGHGR[_hoops_CPGHGR].red_mask,
										 _hoops_IPGHGR[_hoops_CPGHGR].green_mask,
										 _hoops_IPGHGR[_hoops_CPGHGR].blue_mask);
				}

				/* _hoops_CIGHGR@_hoops_SIGHGR._hoops_CPAII
				   _hoops_GPP _hoops_CSAAI _hoops_GCGHGR 8 _hoops_RCGHGR _hoops_GPRR _hoops_IACAR _hoops_SGH _hoops_ACGHGR _hoops_RAHRH _hoops_CCA 8 _hoops_RCGHGR-_hoops_IRSIR
				   _hoops_RPP _hoops_PGCR _hoops_IHIRS _hoops_HAIR _hoops_SGAPC _hoops_SGH _hoops_SHIR
				   */

				if (_hoops_IPGHGR[_hoops_CPGHGR].depth > 8		 ||
						_hoops_RRRPC->driver_type == _hoops_PCGHGR)
				{
						switch (_hoops_IPGHGR[_hoops_CPGHGR].c_class)
						{
						case TrueColor:
								_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case DirectColor:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == PseudoColor ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticColor ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == GrayScale ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case PseudoColor:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticColor ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == GrayScale ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case StaticColor:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == GrayScale ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case GrayScale:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case StaticGray:
								if (_hoops_ACCAA == -1)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;
						}
				}
				else
				{
						switch (_hoops_IPGHGR[_hoops_CPGHGR].c_class)
						{
						case PseudoColor:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class != PseudoColor ||
										(_hoops_IPGHGR[_hoops_ACCAA].c_class == PseudoColor
										 && _hoops_IPGHGR[_hoops_ACCAA].visual != DefaultVisual(_hoops_RRRPC->display,_hoops_HPGHGR.screen)
										))
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case StaticColor:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == TrueColor ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == DirectColor ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == GrayScale ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case TrueColor:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == DirectColor ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == GrayScale ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case DirectColor:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == GrayScale ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case GrayScale:
								if (_hoops_ACCAA == -1 ||
										_hoops_IPGHGR[_hoops_ACCAA].c_class == StaticGray)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;

						case StaticGray:
								if (_hoops_ACCAA == -1)
										_hoops_ACCAA = _hoops_CPGHGR;
								break;
						}
				}
		} while (--_hoops_CPGHGR >= 0);

		if (_hoops_ACCAA != -1) {
				_hoops_RRRPC->visual = _hoops_IPGHGR[_hoops_ACCAA].visual;
				_hoops_RRRPC->depth = _hoops_IPGHGR[_hoops_ACCAA].depth;
				_hoops_RRRPC->_hoops_CRAPC = _hoops_IPGHGR[_hoops_ACCAA].bits_per_rgb;
				XFree ((caddr_t)_hoops_IPGHGR);
				if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
						fprintf (stderr, "\nX11 Color: The best visual is number %d\n", _hoops_ACCAA);
		}
		else
				HE_WARNING (HEC_X11_DRIVER, HES_USING_DEFAULT_VISUAL,
								"X11 Driver: No best visual found, using default visual");
}


/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_HCGHGR _hoops_IRS _hoops_HGIR _hoops_IS _hoops_ISCP _hoops_GPAAC _hoops_HAICP.  _hoops_RAIGR _hoops_CCAH _hoops_HGIR
 *		_hoops_GRS _hoops_SHH _hoops_SPIP _hoops_PAR _hoops_RH _hoops_SHIR _hoops_HGIR _hoops_GRS _hoops_SHH _hoops_IGI _hoops_GPGA _hoops_GPP _hoops_RH
 *		_hoops_RAHRH _hoops_SR _hoops_CHR _hoops_GRP.
 */
local void _hoops_ICGHGR (
	Display_Context const		*dc) {
	X11Data alter					*_hoops_RRRPC = X11D(dc);
	bool						_hoops_CCGHGR = false;

	_hoops_CPAPGR ("get mapped colormap", _hoops_RRRPC);

	/* _hoops_SHR _hoops_ARPR _hoops_HGIR _hoops_IH _hoops_HIHH _hoops_PSP _hoops_RPSHR _hoops_PCPA _hoops_RH _hoops_RAHRH _hoops_CSHGR... */
	/* _hoops_AA _hoops_ASAI _hoops_ARPR _hoops_SPR _hoops_IH _hoops_SGH _hoops_RPPS _hoops_RCC _hoops_CCH */
	if (_hoops_RRRPC->driver_type == _hoops_PPAPC &&
		(dc->options._hoops_GCHSR == 0 ||
			dc->options._hoops_RGHRP == _hoops_GGHRP || BIT (dc->options._hoops_IRARR, 0x00100000 /*_hoops_SCGHGR*/))) {

		_hoops_RRRPC->_hoops_GPIHP = XCreateColormap (
			_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CISPC,
			_hoops_RRRPC->visual, AllocNone);
		return;
	}

	switch (_hoops_RRRPC->visual->c_class) {
		case DirectColor: {
			/* _hoops_PCH _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_HGIR _hoops_IH _hoops_IRS _hoops_GSGHGR _hoops_RAHRH */
			_hoops_CCGHGR = true;
		} break;

		case TrueColor:
		case PseudoColor:
		case StaticColor:
		case GrayScale:
		case StaticGray: {
			if (_hoops_RRRPC->visual->c_class != DefaultVisualOfScreen (_hoops_RRRPC->screen)->c_class)
				_hoops_CCGHGR = true;
			else
				_hoops_RRRPC->_hoops_GPIHP = _hoops_RRRPC->_hoops_IAIPGR;
		} break;

		default: {
			HE_ERROR (HEC_X11_DRIVER, HES_NO_MAPPED_VISAUL_TYPE,
							  "X11 Driver: No Mapped Visual Type For Display!");
			HD_Kill_Driver (dc);
		} break;
	}

	if (_hoops_CCGHGR || (dc->options._hoops_IRARR & _hoops_RAAPGR))
		_hoops_RRRPC->_hoops_GPIHP = XCreateColormap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CISPC,
										 _hoops_RRRPC->visual, AllocNone);
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_RSSAR _hoops_IRS _hoops_RISA _hoops_GPAAC _hoops_RPGP _hoops_RPPS _hoops_IS _hoops_CGIC _hoops_AGRR
 *		_hoops_GPAAC _hoops_CPHSR _hoops_GRPAR _hoops_SGS _hoops_PAH _hoops_RGAR _hoops_SHH _hoops_GAICC _hoops_ARR _hoops_PCCP _hoops_GPAAC
 *		_hoops_RPPS _hoops_SSCP _hoops_RPII _hoops_SPIP _hoops_PPR _hoops_SCGH _hoops_GPP _hoops_RH _hoops_GPAAC _hoops_HHSPC.
 */
local void _hoops_SRAPC (
		Display_Context const		*dc) {
		X11Data alter					*_hoops_RRRPC = X11D(dc);
		XSetWindowAttributes			_hoops_RSGHGR;
		unsigned long					_hoops_ASGHGR;
		XSizeHints						_hoops_PCSPC;
		XEvent							_hoops_GSSPC;

#		define _hoops_PSGHGR						40
#		define _hoops_HSGHGR						80

		_hoops_CPAPGR ("create x11 test window", _hoops_RRRPC);

		ZERO_STRUCT(&_hoops_GSSPC, XEvent);
		ZERO_STRUCT(&_hoops_RSGHGR, XSetWindowAttributes);
		ZERO_STRUCT(&_hoops_PCSPC, XSizeHints);

		/*
		 *		_hoops_GISA _hoops_IRS _hoops_IHGP _hoops_RPGP _hoops_RPPS _hoops_IS _hoops_CGHPC _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_RPPS
		 *		_hoops_PPARI _hoops_HGPC _hoops_SGS _hoops_GRS _hoops_ISGHGR _hoops_HCR _hoops_GPAAC _hoops_SPHGR _hoops_GPP _hoops_RGR _hoops_GPAAC
		 *		_hoops_AIRI _hoops_PPR _hoops_SHPR.		 _hoops_RAP _hoops_RH _hoops_RSCS _hoops_SPSGP _hoops_IGRI _hoops_HIS _hoops_SGS _hoops_GII
		 *		_hoops_RPPS _hoops_SR _hoops_SAIP _hoops_PAH _hoops_SHH _hoops_CSGHGR _hoops_PCACR.
		 */
		_hoops_ASGHGR = CWSaveUnder | CWBackPixel | CWBorderPixel | CWBitGravity | CWOverrideRedirect;
		_hoops_RSGHGR.background_pixel = WhitePixelOfScreen (_hoops_RRRPC->screen);
		_hoops_RSGHGR.border_pixel = BlackPixelOfScreen (_hoops_RRRPC->screen);
		_hoops_RSGHGR.bit_gravity = ForgetGravity;
		_hoops_RSGHGR.override_redirect = 0; /* _hoops_SHR _hoops_HAIRC _hoops_IS _hoops_RH _hoops_RPGP _hoops_RPPS */
		_hoops_RSGHGR.save_under = True;
		if (_hoops_RRRPC->_hoops_HISPGR) {
				_hoops_ICGHGR (dc);
				_hoops_ASGHGR |= CWColormap;
				_hoops_RSGHGR.colormap = _hoops_RRRPC->_hoops_GPIHP;
		}
		_hoops_RRRPC->window = XCreateWindow (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CISPC,
										 _hoops_PSGHGR, _hoops_HSGHGR,
										 1, 1, 0, _hoops_RRRPC->depth, InputOutput,
										 _hoops_RRRPC->visual, _hoops_ASGHGR, &_hoops_RSGHGR);

		/*
		 *		_hoops_RAP _hoops_IGIR _hoops_SSGHGR _hoops_IH _hoops_RH _hoops_RPPS _hoops_PPARI.
		 */
		_hoops_PCSPC.x = _hoops_PSGHGR;
		_hoops_PCSPC.y = _hoops_HSGHGR;
		_hoops_PCSPC.width = 2;
		_hoops_PCSPC.height = 2;
		_hoops_PCSPC.flags = USPosition | USSize;

		XSetNormalHints (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_PCSPC);

		/*
		 *		_hoops_ISGP _hoops_IH _hoops_CGRSC _hoops_HIS _hoops_SR _hoops_PAH _hoops_IPPRH _hoops_IH _hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_IS
		 *		_hoops_IGRC _hoops_RPGAH _hoops_ARPP _hoops_ARPRR _hoops_IS _hoops_CSGA _hoops_RH _hoops_IGIR _hoops_IIGR
		 *		_hoops_RH _hoops_RPPS _hoops_PPARI _hoops_HGPC.
		 */
		XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, ExposureMask);
		XMapWindow (_hoops_RRRPC->display, _hoops_RRRPC->window);
		XWindowEvent (_hoops_RRRPC->display, _hoops_RRRPC->window, ExposureMask, &_hoops_GSSPC);

		/* _hoops_AGGA _hoops_CSGA _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_HGPC */
		if (_hoops_RRRPC->window != (X_Window)0) {
				X_Window					root, _hoops_HCPIH, _hoops_GGRHGR;
				int								x, y, _hoops_RGRHGR, _hoops_AGRHGR;
				unsigned int	width, height, _hoops_PASPGR, depth;

				/* _hoops_SIPR _hoops_RH _hoops_AHC _hoops_PPR _hoops_IGIR _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS */
				XGetGeometry (_hoops_RRRPC->display, _hoops_RRRPC->window, &root, &x, &y, &width,
										  &height, &_hoops_PASPGR, &depth);

				if (BIT (dc->options._hoops_IRARR, _hoops_HRAPGR))
						fprintf (stderr, "X11 Window Manager: Test Window (%d x %d) @ (%d, %d)\n",
										 width, height, x, y);

				/*
				 *		_hoops_PSIH _hoops_RH _hoops_PCRR _hoops_IIGR _hoops_RH _hoops_IHGP _hoops_RPGP _hoops_RPPS _hoops_CSCHR
				 *		_hoops_IS _hoops_RH _hoops_SRRPR _hoops_RPPS.
				 */
				XTranslateCoordinates (_hoops_RRRPC->display, _hoops_RRRPC->window, root, 0, 0,
														   &_hoops_RRRPC->_hoops_PGRHGR, &_hoops_RRRPC->_hoops_HGRHGR,
														   &_hoops_HCPIH);

				/* _hoops_SIPR _hoops_RH _hoops_AHC _hoops_PPR _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_RPSI _hoops_IIGR _hoops_ISCP _hoops_SRRPR _hoops_RPPS */
				XGetGeometry (_hoops_RRRPC->display, _hoops_HCPIH, &root, &x, &y, &width,
										  &height, &_hoops_PASPGR, &depth);

				if (BIT (dc->options._hoops_IRARR, _hoops_HRAPGR))
						fprintf (stderr, "X11 Window Manager: Root Window Child (%d x %d) @ (%d, %d)\n",
										 width, height, x, y);

				/*
				 *		_hoops_PSIH _hoops_RH _hoops_PCRR _hoops_IIGR _hoops_RH _hoops_RPSI _hoops_IIGR _hoops_RH _hoops_SRRPR _hoops_RPPS
				 *		_hoops_CSCHR _hoops_IS _hoops_RH _hoops_SRRPR _hoops_RPPS.
				 */
				XTranslateCoordinates (_hoops_RRRPC->display, _hoops_HCPIH, root, 0, 0,
														   &_hoops_RGRHGR, &_hoops_AGRHGR, &_hoops_GGRHGR);

				/*
				 *		_hoops_IGRHGR _hoops_PSAP _hoops_RH _hoops_CHAA _hoops_IIGR _hoops_RH _hoops_RPSI _hoops_IIGR _hoops_RH _hoops_SRRPR _hoops_RPPS _hoops_IS
				 *		_hoops_CGHPC _hoops_RH _hoops_CHAA _hoops_HHPPR _hoops_HPP _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_HGPC.
				 */
				_hoops_RRRPC->_hoops_PGRHGR -= _hoops_RGRHGR;
				_hoops_RRRPC->_hoops_HGRHGR -= _hoops_AGRHGR;

				/*
				 *		_hoops_ARGH _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_CGRHGR
				 *		_hoops_CCA _hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_IS _hoops_RCRP _hoops_IHHH _hoops_RH _hoops_GGSP _hoops_CHAA _hoops_HHPPR
				 *		_hoops_HPP _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_HGPC.
				 *
				 *		_hoops_HGI _hoops_HHSPR _hoops_HRGR _hoops_HAHH _hoops_PGGA _hoops_RH _hoops_SGRHGR "_hoops_GRRHGR"
				 *		_hoops_RPPS _hoops_PPARI _hoops_ISHS _hoops_IS _hoops_PRRP _hoops_RRRHGR _hoops_CCA _hoops_RH _hoops_GPAAC
				 *		_hoops_HHSPC _hoops_PPR _hoops_ARRHGR() _hoops_IS _hoops_RCRP _hoops_RH _hoops_AGSRH
				 *		_hoops_CHAA _hoops_IH _hoops_RH _hoops_PCIRA _hoops_IIGR _hoops_RH _hoops_IHGP _hoops_RPGP _hoops_RPPS.	_hoops_HGI
				 *		_hoops_RRGR _hoops_CGH _hoops_GSRS _hoops_RH _hoops_GGSP _hoops_CHAA _hoops_HHPPR _hoops_HPP _hoops_RH
				 *		_hoops_RPPS _hoops_PPARI _hoops_HGPC _hoops_IH _hoops_RII _hoops_RPPS _hoops_PRRHGR _hoops_SGS
				 *		_hoops_GACC _hoops_HS _hoops_RGR _hoops_ARPC _hoops_HIH _hoops_HIS _hoops_SGIP "_hoops_GRRHGR" _hoops_HRGR _hoops_RH _hoops_RGAR
				 *		_hoops_RPPS _hoops_PPARI _hoops_SGS _hoops_AHPP _hoops_IS _hoops_HRRHGR _hoops_RGR _hoops_ARPC.
				 */
				if (_hoops_RRRPC->_hoops_PGRHGR == _hoops_PSGHGR &&
						_hoops_RRRPC->_hoops_HGRHGR == _hoops_HSGHGR) {
						/*
						 *		_hoops_SIPR _hoops_RH _hoops_AHC _hoops_PPR _hoops_IGIR _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS.
						 */
						XGetGeometry (_hoops_RRRPC->display, _hoops_RRRPC->window, &root,
												  &x, &y, &width, &height, &_hoops_PASPGR, &depth);

						if (BIT (dc->options._hoops_IRARR, _hoops_HRAPGR))
								fprintf (stderr, "X11 Window Manager: Test Window (%d x %d) @ (%d, %d)\n",
												 width, height, x, y);

						/*
						 *		_hoops_CGP _hoops_RH _hoops_AHC _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS _hoops_HRGR (0,0),
						 *		_hoops_PSCR _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_SSCP _hoops_PPSAR _hoops_IRS _hoops_RPPS _hoops_GAPA
						 *		_hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS _hoops_PPR _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_RPPS
						 *		_hoops_PPR _hoops_SR _hoops_RRP _hoops_IS _hoops_IRRHGR _hoops_GASAR _hoops_IH _hoops_RH _hoops_CHAA _hoops_HHPPR _hoops_HPP
						 *		_hoops_RH _hoops_RPPS _hoops_PPARI _hoops_HGPC.
						 *
						 *		_hoops_CGP _hoops_RH _hoops_AHC _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS _hoops_HRGR _hoops_ASAI (0,0),
						 *		_hoops_PSCR _hoops_HRGR _hoops_RH _hoops_ACAGR _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS _hoops_CSCHR
						 *		_hoops_IS _hoops_RH _hoops_RPPS _hoops_CRRHGR _hoops_RPPS _hoops_PPR _hoops_RGR _hoops_AAAA _hoops_IHHH _hoops_RH _hoops_CHAA
						 *		_hoops_HHPPR _hoops_HPP _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_HGPC.
						 */
						if (x != 0 || y != 0) {
								_hoops_RRRPC->_hoops_PGRHGR = x;
								_hoops_RRRPC->_hoops_HGRHGR = y;
						}
						else {
								X_Window					_hoops_SCAAR, *_hoops_ICHSP;
								unsigned int	_hoops_HRSPGR;

								/*
								 *		_hoops_SIPR _hoops_RH _hoops_HGAI _hoops_PCIRA _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS.
								 */
								XQueryTree (_hoops_RRRPC->display, _hoops_RRRPC->window, &root, &_hoops_SCAAR,
														&_hoops_ICHSP, &_hoops_HRSPGR);
								if (_hoops_ICHSP)
										XFree ((caddr_t)_hoops_ICHSP);

								/*
								 *		_hoops_SIPR _hoops_RH _hoops_AHC _hoops_PPR _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_PCIRA _hoops_IIGR _hoops_ISCP _hoops_IHGP
								 *		_hoops_RPGP _hoops_RPPS.
								 */
								XGetGeometry (_hoops_RRRPC->display, _hoops_SCAAR, &root,
														  &x, &y, &width, &height, &_hoops_PASPGR, &depth);

								if (BIT (dc->options._hoops_IRARR, _hoops_HRAPGR))
										fprintf (stderr,
														 "X11 Window Manager: Parent of Test Window (%d x %d) @ (%d, %d)\n",
														 width, height, x, y);

								/*
								 *		_hoops_IPCP _hoops_AHC _hoops_IIGR _hoops_RH _hoops_PCIRA _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS
								 *		_hoops_HRGR _hoops_RH _hoops_AHC _hoops_IIGR _hoops_ISCP _hoops_IHGP _hoops_RPGP _hoops_RPPS _hoops_CSCHR _hoops_IS
								 *		_hoops_RH _hoops_RPPS _hoops_SPIP _hoops_HPP _hoops_RH _hoops_RPPS _hoops_PPARI.
								 */

								_hoops_RRRPC->_hoops_PGRHGR = x;
								_hoops_RRRPC->_hoops_HGRHGR = y;
						}
				}
		}
		else {
				HE_ERROR (HEC_X11_DRIVER, HES_CREATE_WINDOW_FAILED,
								  "X11 Driver: Unable to Create X11 Window");
				HD_Kill_Driver (dc);
		}

		if (BIT (dc->options._hoops_IRARR, _hoops_HRAPGR))
				fprintf (stderr, "X11 Window Manager: Border size = %d, Control size = %d\n",
								 _hoops_RRRPC->_hoops_PGRHGR, _hoops_RRRPC->_hoops_HGRHGR);
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_GPPIA _hoops_RH _hoops_IHGP _hoops_GPAAC _hoops_RPGP _hoops_RPPS _hoops_SGS _hoops_CSAP _hoops_HSAAI
 *		_hoops_IS _hoops_CGIC _hoops_AGRR _hoops_GPAAC _hoops_CPHSR _hoops_GRPAR _hoops_SGS _hoops_PAH _hoops_RGAR _hoops_SHH
 *		_hoops_GAICC _hoops_ARR _hoops_PCCP _hoops_GPAAC _hoops_RPPS _hoops_SSCP _hoops_RPII _hoops_SPIP _hoops_PPR _hoops_SCGH _hoops_GPP _hoops_RH _hoops_GPAAC
 *		_hoops_HHSPC.
 */
local void _hoops_AAAPC (
	Display_Context const		*dc) {
	X11Data alter					*_hoops_RRRPC = X11D(dc);

	_hoops_CPAPGR ("destroy x11 test window", _hoops_RRRPC);

	/* _hoops_SHPPR _hoops_IHGP _hoops_RPGP _hoops_RPPS */
	if (_hoops_RRRPC->window != (X_Window)0) {

		if (_hoops_RRRPC->driver_type == _hoops_PPAPC && _hoops_RRRPC->_hoops_CAAAC) {
				XFree ((caddr_t)_hoops_RRRPC->_hoops_CAAAC);
				_hoops_RRRPC->_hoops_CAAAC=0;
		}

		XDestroyWindow (_hoops_RRRPC->display, _hoops_RRRPC->window);
		_hoops_RRRPC->window = (X_Window)0;
	}
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_PARPC _hoops_RH _hoops_IHGP _hoops_GPAAC _hoops_RPGP _hoops_RPPS
 */
local void _hoops_PAAPC (
	Display_Context const		*dc) {
	X11Data alter					*_hoops_RRRPC = X11D(dc);

	_hoops_CPAPGR ("hide x11 test window", _hoops_RRRPC);

	/* _hoops_SHPPR _hoops_IHGP _hoops_RPGP _hoops_RPPS */
	if (_hoops_RRRPC->window != (X_Window)0) {

		XUnmapWindow (_hoops_RRRPC->display, _hoops_RRRPC->window);
	}
}





/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_SAGGR _hoops_RH _hoops_IRPR _hoops_GGCSI _hoops_PPSCP _hoops_API _hoops_IH _hoops_RH _hoops_GPAAC
 *		_hoops_SRRHGR _hoops_PPR _hoops_GPAAC _hoops_HHSPC _hoops_AARRA _hoops_SR _hoops_CHR _hoops_GRP.
 */
local void _hoops_GARHGR (
		Display_Context const		*dc) {
		X11Data alter					*_hoops_RRRPC = X11D(dc);
		RGBAS32						_hoops_RARHGR;
		int								_hoops_IGGAH, _hoops_AARHGR;

		_hoops_CPAPGR ("get rgb32 raster function", _hoops_RRRPC);

		/* _hoops_HGH _hoops_RH _hoops_HSAGA _hoops_IIGR _hoops_RH _hoops_GPAAC _hoops_SRRHGR */
		_hoops_RARHGR.a = 0;
		_hoops_RARHGR.b = 0;
		_hoops_RARHGR.g = 0;
		_hoops_RARHGR.r = 1;

		Integer32	test = *(Integer32 const *)&_hoops_RARHGR;

		if (HOOPS_BIGENDIAN) {
				if (BIT (test, 1)) {
						_hoops_IGGAH = X11_CLIENT_MSB_BLUE_FIRST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Client is Big-endian with Blue first\n");
				}
				else {
						_hoops_IGGAH = X11_CLIENT_MSB_BLUE_LAST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Client is Big-endian with Blue last\n");
				}
		}
		else {
				if (BIT (test, 1)) {
						_hoops_IGGAH = X11_CLIENT_LSB_BLUE_FIRST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Client is Little-endian with Blue first\n");
				}
				else {
						_hoops_IGGAH = X11_CLIENT_LSB_BLUE_LAST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Client is Little-endian with Blue last\n");
				}
		}

		/* _hoops_HGH _hoops_RH _hoops_HSAGA _hoops_IIGR _hoops_RH _hoops_GPAAC _hoops_HHSPC */
		if (ImageByteOrder (_hoops_RRRPC->display) == MSBFirst) {
				if (_hoops_RRRPC->_hoops_HGPPGR) {
						_hoops_AARHGR = X11_SERVER_MSB_BLUE_FIRST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Server is Big-endian with Blue first\n");
				}
				else {
						_hoops_AARHGR = X11_SERVER_MSB_BLUE_LAST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Server is Big-endian with Blue last\n");
				}
		}
		else {
				if (_hoops_RRRPC->_hoops_HGPPGR) {
						_hoops_AARHGR = X11_SERVER_LSB_BLUE_FIRST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Server is Little-endian with Blue first\n");
				}
				else {
						_hoops_AARHGR = X11_SERVER_LSB_BLUE_LAST;
						if (BIT (dc->options._hoops_IRARR, _hoops_PRAPGR))
								fprintf (stderr, "X11 Color: X11 Server is Little-endian with Blue last\n");
				}
		}

		switch (_hoops_IGGAH) {
				case X11_CLIENT_MSB_BLUE_FIRST: {
						switch (_hoops_AARHGR) {
								case X11_SERVER_MSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_RCPPGR;
										break;
								case X11_SERVER_MSB_BLUE_LAST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ACPPGR;
										break;
								case X11_SERVER_LSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_PCPPGR;
										break;
								case X11_SERVER_LSB_BLUE_LAST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ICPPGR;
										break;
						}
				}		break;

				case X11_CLIENT_MSB_BLUE_LAST: {
						switch (_hoops_AARHGR) {
								case X11_SERVER_MSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ACPPGR;
										break;
								case X11_SERVER_MSB_BLUE_LAST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_RCPPGR;
										break;
								case X11_SERVER_LSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ICPPGR;
										break;
								case X11_SERVER_LSB_BLUE_LAST:
										/* _hoops_HII _hoops_PARHGR _hoops_IS _hoops_HARHGR */
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_HCPPGR;
										break;
						}
				}		break;

				case X11_CLIENT_LSB_BLUE_FIRST: {
						switch (_hoops_AARHGR) {
								case X11_SERVER_MSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_PCPPGR;
										break;
								case X11_SERVER_MSB_BLUE_LAST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ICPPGR;
										break;
								case X11_SERVER_LSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_RCPPGR;
										break;
								case X11_SERVER_LSB_BLUE_LAST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ACPPGR;
										break;
						}
				}		break;

				case X11_CLIENT_LSB_BLUE_LAST: {
						switch (_hoops_AARHGR) {
								case X11_SERVER_MSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_PCPPGR;
										break;
								case X11_SERVER_MSB_BLUE_LAST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ICPPGR;
										break;
								case X11_SERVER_LSB_BLUE_FIRST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_ACPPGR;
										break;
								case X11_SERVER_LSB_BLUE_LAST:
										_hoops_RRRPC->_hoops_GCPPGR = _hoops_RCPPGR;
										break;
						}
				}		break;
		}

		if (_hoops_RRRPC->_hoops_GCPPGR == _hoops_RCPPGR)
				((Display_Context alter *)dc)->_hoops_ACPGR->draw_dc_rgb32_rasters =
						_hoops_GSPPGR;
		else
				((Display_Context alter *)dc)->_hoops_ACPGR->draw_dc_rgb32_rasters =
						_hoops_RIPPGR;
}



/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_SAGGR _hoops_GPAAC _hoops_CPHSR _hoops_SIHC.
 */
local void _hoops_PRAPC (
		Display_Context alter		*dc) {
		X11Data alter					*_hoops_RRRPC = X11D(dc);
		int								_hoops_IARHGR = 0;
		int								_hoops_CAPPGR;

		_hoops_CPAPGR ("get x11 physical info", _hoops_RRRPC);

		dc->_hoops_PGCC.flags |= _hoops_PPPGH;

		/* _hoops_RGR _hoops_RPP-_hoops_SHS _hoops_AARRA _hoops_SAGGR _hoops_RH _hoops_AAH _hoops_RAHRH _hoops_PPR _hoops_CSAP _hoops_GGR _hoops_APISR(), _hoops_HIH,
		 * _hoops_CR _hoops_RH _hoops_HIHH _hoops_RHPP _hoops_IRHS _hoops_IS _hoops_CRGS _hoops_RH _hoops_CPAPC _hoops_RHPP _hoops_SGS _hoops_SCH _hoops_SSCP _hoops_IS _hoops_AGRP _hoops_RGCI
		 * _hoops_CARHGR _hoops_HGRH _hoops_PPR _hoops_SCH _hoops_PAH _hoops_RGAR _hoops_AA _hoops_SGS _hoops_RAS _hoops_APISR _hoops_APCRR, _hoops_SR _hoops_SIGR
		 * _hoops_IS _hoops_AGGHA _hoops_RH _hoops_CARHGR _hoops_AASA _hoops_GGSR _hoops_IIGR _hoops_APISR _hoops_PPR _hoops_SR (_hoops_SARHGR _hoops_PPR _hoops_GPRHGR) _hoops_CIIHP
		 * _hoops_IS _hoops_PPSI _hoops_SCH _hoops_ARI.		_hoops_PAGA _hoops_RH _hoops_RPRHGR _hoops_PPR _hoops_GIPRC _hoops_HSGP _hoops_HAPR _hoops_GIPR _hoops_HGAP _hoops_SHPR
		 * _hoops_SIHC _hoops_PGAP _hoops_HRGR _hoops_HAR _hoops_HSSPR _hoops_CCGR _hoops_RAS _hoops_RHAC _hoops_IPASR _hoops_RH _hoops_SHPR _hoops_HIS _hoops_SSIA _hoops_GIPR _hoops_CHR _hoops_ARI _hoops_HAH.
		 */
		if (dc->options._hoops_ISPRP != 0) {
				if (_hoops_RRRPC->driver_type == X11_ONLY) {
						HE_ERROR (HEC_X11_DRIVER, HES_WRONG_DRIVER_TYPE_ON_X11,
										  "Cannot use \"use window ID 2\" with X11 driver.");
						HD_Kill_Driver (dc);
				}
		}
		if (dc->options._hoops_GCHSR != 0 &&
			dc->options._hoops_RGHRP != _hoops_GGHRP &&
			!BIT (dc->options._hoops_IRARR, 0x00100000 /*_hoops_SCGHGR*/)) {
				XWindowAttributes				_hoops_GHSPC;

				_hoops_RRRPC->window = dc->options._hoops_GCHSR;
				XGetWindowAttributes (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_GHSPC);
				_hoops_RRRPC->screen = _hoops_GHSPC.screen;
				_hoops_RRRPC->visual = _hoops_GHSPC.visual;
				_hoops_RRRPC->depth = _hoops_GHSPC.depth;
				_hoops_RRRPC->_hoops_CRAPC = _hoops_RRRPC->visual->bits_per_rgb;

				if (_hoops_RRRPC->driver_type == _hoops_PPAPC) {
						XVisualInfo _hoops_IPSPC;
						int n;

						_hoops_IPSPC.visualid = XVisualIDFromVisual (_hoops_RRRPC->visual);
						_hoops_RRRPC->_hoops_CAAAC = XGetVisualInfo (_hoops_RRRPC->display, VisualIDMask, &_hoops_IPSPC, &n);

						if (n==0) {
								_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
												"Could not find XVisualInfo for window.");
								HD_Kill_Driver (dc);
						}
				}
		}
#ifdef AIX_SYSTEM
		else if (dc->options._hoops_ISPRP != 0) {
				XWindowAttributes				_hoops_GHSPC;

				if (_hoops_RRRPC->window == 0) {
						HE_ERROR (HEC_X11_DRIVER, HES_NO_X_WINDOW_FOR_GL_WINDOW,
										  "X11 Driver: No X11 Window for GL Window");
						HD_Kill_Driver (dc);
				}
				XGetWindowAttributes (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_GHSPC);
				_hoops_RRRPC->screen = _hoops_GHSPC.screen;
				_hoops_RRRPC->visual = _hoops_GHSPC.visual;
				_hoops_RRRPC->depth = _hoops_GHSPC.depth;
				_hoops_RRRPC->_hoops_CRAPC = _hoops_RRRPC->visual->bits_per_rgb;
		}
#endif /* _hoops_ICAPR */
		else {
				XVisualInfo				_hoops_HPGHGR,
																*_hoops_IPGHGR;
				int								_hoops_CPGHGR;

				_hoops_RRRPC->window = (X_Window)0;

				/* _hoops_IH _hoops_RH _hoops_SSCPR _hoops_IIGR _hoops_GSPHR, _hoops_ASSS _hoops_ISPSP _hoops_GCPRGR _hoops_IS _hoops_HPSI _hoops_IHAGH */
				if (_hoops_RRRPC->driver_type == _hoops_PPAPC) {
						_hoops_RRRPC->first = false;
				}

				switch (dc->options._hoops_IRARR & _hoops_RAAPGR) {
						case _hoops_AAAPGR: {
								/* _hoops_PHIAR _hoops_HSSHH */
								_hoops_RRRPC->screen = DefaultScreenOfDisplay (_hoops_RRRPC->display);
								_hoops_RRRPC->visual = DefaultVisualOfScreen (_hoops_RRRPC->screen);
								_hoops_RRRPC->depth = DefaultDepthOfScreen (_hoops_RRRPC->screen);
								_hoops_RRRPC->_hoops_CRAPC = _hoops_RRRPC->visual->bits_per_rgb;

								if (BIT(dc->options._hoops_IRARR, _hoops_PRAPGR)) {
										switch (_hoops_RRRPC->visual->c_class) {
												case DirectColor:
												case TrueColor:
												case PseudoColor:
												case StaticColor:
												case GrayScale:
												case StaticGray: {
														fprintf (stderr,
																		 "X11 Color: Default visual is %s of depth %d with %d bits-per-rgb\n",
																		 _hoops_SHAPGR[_hoops_RRRPC->visual->c_class],
																		 _hoops_RRRPC->depth, _hoops_RRRPC->_hoops_CRAPC);
												}		break;

												default: {
														fprintf (stderr,
																		 "X11 Color: Unknown default visual of depth %d\n",
																		 _hoops_RRRPC->depth);
												}		break;
										}
								}

								/* _hoops_SSS _hoops_RH _hoops_AAH _hoops_RAHRH _hoops_IH _hoops_RH _hoops_HHPA _hoops_IGRH _hoops_GHC */
								_hoops_PPGHGR(dc);
						}		break;

						case _hoops_SAAPGR:
						case _hoops_CAAPGR:
						case _hoops_IAAPGR:
						case _hoops_HAAPGR:
						case _hoops_PAAPGR:
						case _hoops_GPAPGR: {
								switch (dc->options._hoops_IRARR & _hoops_RAAPGR) {
										case _hoops_SAAPGR: {
												_hoops_HPGHGR.c_class = DirectColor;
										}		break;

										case _hoops_CAAPGR: {
												_hoops_HPGHGR.c_class = TrueColor;
										}		break;

										case _hoops_IAAPGR: {
												_hoops_HPGHGR.c_class = PseudoColor;
										}		break;

										case _hoops_PAAPGR:
										case _hoops_HAAPGR:
										case _hoops_GPAPGR: {
												_hoops_HPGHGR.c_class = StaticGray;
										}		break;

										default: {
												HE_ERROR (HEC_X11_DRIVER, HES_NO_COLOR_TYPE_FOR_DISPLAY,
																  "X11 Driver: No Color Type For Display");
												HD_Kill_Driver (dc);
										}		break;
								}

								_hoops_IPGHGR = XGetVisualInfo (_hoops_RRRPC->display, VisualClassMask,
																				  &_hoops_HPGHGR, &_hoops_CPGHGR);

								if (_hoops_CPGHGR == 0) {
										_hoops_RRRPC->screen = DefaultScreenOfDisplay (_hoops_RRRPC->display);
										_hoops_RRRPC->visual = DefaultVisualOfScreen (_hoops_RRRPC->screen);

										/* _hoops_RPP _hoops_SR _hoops_GGHP _hoops_ARI _hoops_PSCR _hoops_SR _hoops_SSGRR _hoops_IH _hoops_APRHGR _hoops_IIPR _hoops_GPP _hoops_IRS _hoops_RAHRH _hoops_SGS
										 * "_hoops_SSSCP" _hoops_GCGH _hoops_SCH _hoops_RRPS _hoops_IS _hoops_SPCR.	_hoops_CPGP _hoops_SR _hoops_ACPA _hoops_SGS _hoops_HCR
										 * _hoops_HAIR _hoops_SGAPC _hoops_PAH _hoops_GCGH _hoops_SCH, _hoops_SIPIP _hoops_RH _hoops_SPCR _hoops_RIHH _hoops_PPR _hoops_RSPH
										 * _hoops_IRS _hoops_APRHGR _hoops_AIRI
										 */
										if ((dc->options._hoops_IRARR & _hoops_RAAPGR) == _hoops_GPAPGR) {
												_hoops_RRRPC->depth = DefaultDepthOfScreen (_hoops_RRRPC->screen);
												_hoops_RRRPC->_hoops_CRAPC = 1;
										}
										else
												HE_WARNING (HEC_X11_DRIVER, HES_UNAVAILABLE_VISUAL_CLASS,
																"X11 Driver: Specified visual class not available");
								}
								else {
										XVisualInfo alter		*_hoops_PPRHGR = _hoops_IPGHGR,
																										*_hoops_ACCAA = _hoops_IPGHGR,
																										*end = &_hoops_IPGHGR[_hoops_CPGHGR];

										if (_hoops_HPGHGR.c_class == PseudoColor) {
												while (++_hoops_PPRHGR != end && _hoops_ACCAA->depth != 8)
														if (_hoops_ACCAA->depth < _hoops_PPRHGR->depth)
																_hoops_ACCAA = _hoops_PPRHGR;
										}
										else {
												while (++_hoops_PPRHGR != end)
														if (_hoops_ACCAA->depth < _hoops_PPRHGR->depth)
																_hoops_ACCAA = _hoops_PPRHGR;
										}

										_hoops_RRRPC->screen = ScreenOfDisplay (_hoops_RRRPC->display, _hoops_ACCAA->screen);
										_hoops_RRRPC->visual = _hoops_ACCAA->visual;
										_hoops_RRRPC->depth = _hoops_ACCAA->depth;
										_hoops_RRRPC->_hoops_CRAPC = _hoops_ACCAA->bits_per_rgb;
										XFree ((caddr_t)_hoops_IPGHGR);
								}
						}		break;

						default: {
								HE_ERROR (HEC_X11_DRIVER, HES_NO_COLOR_TYPE_FOR_DISPLAY,
												  "X11 Driver: No Color Type For Display");
								HD_Kill_Driver (dc);
						}		break;
				}

				if (BIT(dc->options._hoops_IRARR, _hoops_PRAPGR)) {
						switch (_hoops_RRRPC->visual->c_class) {
								case DirectColor:
								case TrueColor:
								case PseudoColor:
								case StaticColor:
								case GrayScale:
								case StaticGray: {
										fprintf (stderr,
														 "X11 Color: %s visual of depth %d with %d bits-per-rgb chosen\n",
														 _hoops_SHAPGR[_hoops_RRRPC->visual->c_class], _hoops_RRRPC->depth,
														 _hoops_RRRPC->_hoops_CRAPC);
								}		break;

								default: {
										fprintf (stderr,
														 "X11 Color: Unknown visual of depth %d chosen\n",
														 _hoops_RRRPC->depth);
								}		break;
						}
				}
		}

		if ((dc->options._hoops_IRARR & _hoops_RAAPGR) == _hoops_GPAPGR) {
				_hoops_IARHGR = _hoops_RRRPC->visual->c_class;
				_hoops_RRRPC->visual->c_class = StaticGray;
		}


		_hoops_RRRPC->_hoops_CISPC = RootWindowOfScreen (_hoops_RRRPC->screen);

		/*
		 *		_hoops_RAP _hoops_CPHSR _hoops_SIHC _hoops_PPR _hoops_IPP _hoops_RGSR _hoops_SICAR _hoops_IIHA
		 *		_hoops_GPP _hoops_RH _hoops_RAHRH _hoops_GPRR.
		 */
		_hoops_RRRPC->_hoops_IAGGS = _hoops_IAGGS;
		_hoops_RRRPC->_hoops_RHPPGR = _hoops_RHPPGR;


		switch (_hoops_RRRPC->visual->c_class) {
				case TrueColor:
				case DirectColor: {
								_hoops_RRRPC->_hoops_HISPGR = true;
								_hoops_RRRPC->_hoops_IAIPGR = DefaultColormapOfScreen (_hoops_RRRPC->screen);

								_hoops_RRRPC->_hoops_HGPPGR = BIT (_hoops_RRRPC->visual->red_mask, 1);

								dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
								dc->_hoops_PGCC._hoops_APASR = 0;
								dc->_hoops_PGCC._hoops_AAPSR = 1 << _hoops_RRRPC->depth;
								dc->_hoops_PGCC._hoops_PCHSR = 1 << _hoops_RRRPC->_hoops_CRAPC;
								if (dc->_hoops_PGCC._hoops_PCHSR>256)
												dc->_hoops_PGCC._hoops_PCHSR=256;

								if (1) {
												unsigned int mask;

												_hoops_RRRPC->_hoops_SGPPGR = 0;
												_hoops_RRRPC->_hoops_RRPPGR = 0;
												_hoops_RRRPC->_hoops_PRPPGR = 0;

												_hoops_RRRPC->_hoops_CGPPGR = 8;
												_hoops_RRRPC->_hoops_GRPPGR = 8;
												_hoops_RRRPC->_hoops_ARPPGR = 8;

												if (_hoops_RRRPC->visual->red_mask) {
																for (mask = _hoops_RRRPC->visual->red_mask; !(mask&0x01); mask >>=1)
																				_hoops_RRRPC->_hoops_SGPPGR++;
																for (; mask&0x01; mask >>= 1)
																				_hoops_RRRPC->_hoops_CGPPGR--;
												}

												if (_hoops_RRRPC->visual->green_mask) {
																for (mask = _hoops_RRRPC->visual->green_mask; !(mask&0x01); mask >>=1)
																				_hoops_RRRPC->_hoops_RRPPGR++;
																for (; mask&0x01; mask >>= 1)
																				_hoops_RRRPC->_hoops_GRPPGR--;
												}

												if (_hoops_RRRPC->visual->blue_mask) {
																for (mask = _hoops_RRRPC->visual->blue_mask; !(mask&0x01); mask >>=1)
																				_hoops_RRRPC->_hoops_PRPPGR++;
																for (; mask&0x01; mask >>= 1)
																				_hoops_RRRPC->_hoops_ARPPGR--;
												}

												/*_hoops_HPRHGR _hoops_GGCSI _hoops_AHRH _hoops_RGAR _hoops_IIAH _hoops_CCA 16b_hoops_SCH _hoops_RSCA _hoops_HRAAI*/
												if (_hoops_RRRPC->depth == 16) {
																((Display_Context alter *)dc)->_hoops_ACPGR->draw_dc_rgb32_rasters = _hoops_PSPPGR;
												}
												else {
																_hoops_GARHGR (dc);
												}

												_hoops_RRRPC->_hoops_CSASR = _hoops_IGPPGR;

												/*_hoops_CCPC _hoops_IS _hoops_GGSPS _hoops_AGAH _hoops_AHCA _hoops_AGCR _hoops_IGRH _hoops_IIGR _hoops_IPRHGR*/
												/*_hoops_AAPA _hoops_PAPA _hoops_AGAH _hoops_CPRHGR _hoops_SR _hoops_CHR 24 _hoops_IGRH _hoops_PRGI _hoops_RPP 16*/
												/*_hoops_SCH _hoops_CPSA _hoops_ASSP'_hoops_RA _hoops_RPSHR _hoops_PGGA _hoops_IRISR _hoops_RGAR _hoops_CGISR*/
												/*_hoops_AHCA 24 _hoops_IGRH _hoops_ACHSR _hoops_AHRH _hoops_HIS _hoops_SAHR _hoops_CRGS _hoops_SCH*/
												/*_hoops_SPRHGR _hoops_PCPA _hoops_SR _hoops_HS _hoops_GHAII*/
												dc->_hoops_PGCC._hoops_AAPSR = 1 << 24;
												dc->_hoops_PGCC._hoops_PCHSR = 1 << 8;
								}
								else {
												/* _hoops_PHIAR _hoops_RH 32 _hoops_IGRH _hoops_PPSCP _hoops_API _hoops_IH _hoops_RGR _hoops_GPAAC _hoops_SRRHGR*/
												/*				_hoops_PPR _hoops_GPAAC _hoops_HHSPC _hoops_AARRA.*/
												_hoops_GARHGR (dc);

												_hoops_RRRPC->_hoops_CSASR = _hoops_GGPPGR;
								}
				}		break;

				case GrayScale: /* _hoops_SCGH _hoops_HSH _hoops_IIGR _hoops_IIGRP */
				case StaticColor:
				case PseudoColor: {
						_hoops_RRRPC->_hoops_HISPGR = true;
						_hoops_RRRPC->_hoops_IAIPGR = DefaultColormapOfScreen (_hoops_RRRPC->screen);

						/* _hoops_PSHA _hoops_IGPC _hoops_GRS <<8 _hoops_CRGR _hoops_GHRHGR */
						dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
						dc->_hoops_PGCC._hoops_APASR = 0;

						/* _hoops_RGR _hoops_HRGR _hoops_IH _hoops_RH _hoops_PHRPR _hoops_RHRHGR _hoops_AHRHGR */
						if (_hoops_RRRPC->_hoops_CRAPC > 16)
								_hoops_RRRPC->_hoops_CRAPC = 8;

						dc->_hoops_PGCC._hoops_AAPSR = 1 << _hoops_RRRPC->depth;

						dc->_hoops_PGCC._hoops_PCHSR = 256;

						_hoops_RRRPC->_hoops_CSASR = _hoops_CRPPGR;

						/* _hoops_ASSS _hoops_AGCR _hoops_IS _hoops_GGCA _hoops_HA _hoops_HAH */
						dc->_hoops_ACPGR->draw_dc_colorized_face = draw_dc_colorized_face;
						dc->_hoops_ACPGR->_hoops_SCCSR = _hoops_SCCSR;

						dc->_hoops_ACPGR->draw_dc_colorized_polyline = HD_Span_DC_Colorized_Polyline;
				}		break;

				case StaticGray: {
						_hoops_RRRPC->_hoops_HISPGR = true;
						_hoops_RRRPC->_hoops_IAIPGR = DefaultColormapOfScreen (_hoops_RRRPC->screen);

						dc->_hoops_PGCC._hoops_PIHSR = _hoops_RIIHP;
						dc->_hoops_PGCC._hoops_APASR = 0;

						/* _hoops_RGR _hoops_HRGR _hoops_IH _hoops_RH _hoops_PHRPR _hoops_RHRHGR _hoops_AHRHGR */
						if (_hoops_RRRPC->_hoops_CRAPC > 16)
								_hoops_RRRPC->_hoops_CRAPC = 8;

						dc->_hoops_PGCC._hoops_AAPSR = 1 << _hoops_RRRPC->depth;

						if (_hoops_RRRPC->depth == 1) {
								dc->_hoops_PGCC._hoops_PCHSR = _hoops_SPRSP;

								/* _hoops_IPP _hoops_RGSR _hoops_IH _hoops_APRP-_hoops_PPR-_hoops_PGS _hoops_RAHRH _hoops_CSSC */
								_hoops_RRRPC->_hoops_CSASR = _hoops_IRPPGR;
								_hoops_RRRPC->_hoops_IAGGS = _hoops_IPPPGR;
								_hoops_RRRPC->_hoops_RHPPGR = _hoops_RHPPGR;

								/*
								 *		_hoops_PHIAR _hoops_RH _hoops_IGRH _hoops_PPSCP _hoops_API _hoops_IH _hoops_RGR _hoops_GPAAC _hoops_HHSPC.
								 *		_hoops_PS _hoops_CHR _hoops_RAGA _hoops_RH _hoops_SIH _hoops_GGR _hoops_IRS _hoops_PHRHGR _hoops_CPCP.  _hoops_PS
								 *		_hoops_PIHA _hoops_IRRHGR _hoops_PCPA _hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_APSI _hoops_PPR _hoops_IRHH _hoops_RH
								 *		_hoops_HCHIA _hoops_RPP _hoops_HAHH.
								 */
								_hoops_RRRPC->_hoops_IHPPGR = false;
								if (BitmapBitOrder (_hoops_RRRPC->display) == MSBFirst)
										_hoops_RRRPC->_hoops_IHPPGR |= _hoops_SHPPGR;
								if (WhitePixelOfScreen (_hoops_RRRPC->screen) != 0)
										_hoops_RRRPC->_hoops_IHPPGR |= _hoops_GIPPGR;
						}
						else {
								dc->_hoops_PGCC._hoops_PCHSR = 1 << _hoops_RRRPC->_hoops_CRAPC;
								_hoops_RRRPC->_hoops_CSASR = _hoops_HRPPGR;
						}
				}		break;

				default: {
						HE_ERROR (HEC_X11_DRIVER, HES_INVALID_VISUAL_CLASS,
										  "X11 Driver: Cannot handle requested visual class");
						HD_Kill_Driver (dc);
				}		break;
		}
		if ((dc->options._hoops_IRARR & _hoops_RAAPGR) == _hoops_GPAPGR) {
				_hoops_RRRPC->visual->c_class = _hoops_IARHGR;
		}

		/* _hoops_HGI _hoops_HRGR _hoops_IH _hoops_RH _hoops_SHPR _hoops_HAR _hoops_RH _hoops_RPPS */
		dc->_hoops_PGCC._hoops_ARISR.x = 0;
		dc->_hoops_PGCC._hoops_ARISR.y = 0;
		dc->_hoops_PGCC._hoops_PRPSR.x = WidthOfScreen (_hoops_RRRPC->screen);
		dc->_hoops_PGCC._hoops_PRPSR.y = HeightOfScreen (_hoops_RRRPC->screen);

		/* _hoops_HGI _hoops_HRGR _hoops_IH _hoops_RH _hoops_SHPR _hoops_HAR _hoops_RH _hoops_RPPS */
		dc->_hoops_PGCC.extent.left = 0;
		dc->_hoops_PGCC.extent.bottom = 0;
		dc->_hoops_PGCC.extent.right = dc->_hoops_PGCC._hoops_PRPSR.x;
		dc->_hoops_PGCC.extent.top = dc->_hoops_PGCC._hoops_PRPSR.y;



		/*
		 *		_hoops_HHRHGR & _hoops_IHRHGR _hoops_HHSH _hoops_IIP _hoops_IPHR _hoops_HIS
		 *		_hoops_RGR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_SHH _hoops_IAPR-_hoops_CHRHGR _hoops_HPP _hoops_RGSR _hoops_RH _hoops_RHPP
		 *		_hoops_HCSP "_hoops_CPHSR _hoops_IGIR=(_hoops_SISR, _hoops_HAPC)".
		 */

		dc->_hoops_PGCC.size.x = WidthMMOfScreen (_hoops_RRRPC->screen) / 10.0f;
		dc->_hoops_PGCC.size.y = HeightMMOfScreen (_hoops_RRRPC->screen) / 10.0f;
		dc->_hoops_PGCC._hoops_PIPGH = false;
		dc->_hoops_PGCC.flags |= _hoops_HSHSR;
		dc->_hoops_PGCC.flags |= _hoops_SAPGH;

		dc->_hoops_PGCC._hoops_IIPGH[0] = QMoves_XOR;

		dc->_hoops_PGCC._hoops_ASHSR = XGetPointerMapping (_hoops_RRRPC->display, (unsigned char alter *)0, 0);

		dc->_hoops_PGCC.driver_type = "X11";
		dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.633 $";

		dc->_hoops_PGCC.flags &= ~_hoops_GIHSR;

				/*_hoops_IRHH _hoops_RPHPGR*/
		for (_hoops_CAPPGR = 0; _hoops_CAPPGR < TOTAL_BIT_PATTERNS; _hoops_CAPPGR++) {
				_hoops_RRRPC->stipples[_hoops_CAPPGR] = XCreateBitmapFromData (_hoops_RRRPC->display,
																  _hoops_RRRPC->_hoops_CISPC,
																  (char alter *)dc->_hoops_GRPH[_hoops_CAPPGR],
																  dc->_hoops_ASPGH,
																  dc->_hoops_ASPGH);
				if (_hoops_RRRPC->stipples[_hoops_CAPPGR] == 0)
						HE_WARNING (HEC_X11_DRIVER, HES_CREATE_STIPPLES_FAILED,
										"Unexpected X11 Failure: Unable to create stipples");
		}

		/*
		 *		_hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_GPAAC _hoops_GAPGGR-_hoops_RHGPR _hoops_SAIHH _hoops_HRGR _hoops_APP
		 *		_hoops_GPP _hoops_RGR _hoops_GPAAC _hoops_HHSPC.		 _hoops_CGP _hoops_HIS, _hoops_PSCR _hoops_SR _hoops_ARCRC "_hoops_GHGPR-_hoops_SRHR" _hoops_RRPS
		 *		_hoops_IS _hoops_IRISR.  _hoops_IPCP "_hoops_AAGAH" _hoops_RIP _hoops_AGCCA _hoops_IS _hoops_IGH _hoops_PAR _hoops_HAR
		 *		_hoops_HGISR _hoops_RRP _hoops_IS _hoops_SHH _hoops_CPHR _hoops_IS _hoops_GIPR _hoops_PSCA _hoops_HIS _hoops_GIPR _hoops_PSCA _hoops_CHR _hoops_GGSP
		 *		_hoops_IH _hoops_AGGPR _hoops_PPR/_hoops_PAR _hoops_SHRHGR _hoops_SGS _hoops_GPHCR _hoops_GPP _hoops_IRS _hoops_SASI _hoops_PAAP.
		 *		_hoops_CGP _hoops_GPAAC _hoops_GAPGGR-_hoops_RHGPR _hoops_HRGR _hoops_ASAI _hoops_APP, _hoops_PSCR _hoops_SR _hoops_GRS _hoops_AA _hoops_RSAPGR
		 *		_hoops_GHGPR-_hoops_RHGPR _hoops_PGAP _hoops_HRGR _hoops_RH _hoops_PSHR _hoops_GAR "_hoops_RSRA-_hoops_RHGPR" _hoops_IS _hoops_IRISR
		 *		_hoops_CR _hoops_RH _hoops_RPISR _hoops_HRGR _hoops_IHGS _hoops_CHCC _hoops_IS _hoops_PPGS _hoops_PGAP _hoops_HRGR _hoops_PSCR _hoops_RIRRR
		 *		_hoops_HPP _hoops_RH _hoops_GPAAC _hoops_HHSPC _hoops_IS _hoops_RH _hoops_GPAAC _hoops_RPPS.
		 */
		if (_hoops_RRRPC->_hoops_SPGHGR == true)
								dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
				else
								dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
}



/*
 *		** _hoops_PGAA **
 *		_hoops_HGI _hoops_RHPP _hoops_GPSPS _hoops_GAR _hoops_IRS _hoops_RPPS _hoops_PPARI / _hoops_HCISR _hoops_GIRHGR _hoops_IH _hoops_GPAAC. _hoops_HHIGR
 *		_hoops_GACC _hoops_RHAP _hoops_GHGPR-_hoops_RIRHGR _hoops_GAR _hoops_IRS _hoops_RPPS _hoops_PPARI _hoops_IH _hoops_RII _hoops_SPSIR, _hoops_IAS._hoops_ISHI. _hoops_IIIGC,
 *		_hoops_HIHH, _hoops_AIRHGR, _hoops_PAIAP, _hoops_PPR _hoops_PIRHGR. _hoops_RAHP _hoops_HGPP, _hoops_SCH _hoops_SSCP _hoops_AHPH _hoops_HIRHGR _hoops_IIRHGR _hoops_GGR _hoops_CSHCR
 *		_hoops_IIGR _hoops_RGCI _hoops_RGGAS. _hoops_RCPA _hoops_SRCH _hoops_PCIPR _hoops_AHCA _hoops_RAHIP _hoops_IIGR _hoops_RGSHA _hoops_PPR _hoops_CISPP,
 *		_hoops_RGR _hoops_PCPH _hoops_IGISR _hoops_GGR _hoops_SPCS _hoops_HSH _hoops_IH _hoops_CPS _hoops_CGPR _hoops_IRS _hoops_SISS _hoops_HRGR _hoops_AIS.
 *		_hoops_CIRHGR _hoops_HRGR _hoops_HAR _hoops_PCCP _hoops_RCSRR _hoops_CR _hoops_RGR _hoops_RGAR _hoops_SRIPR _hoops_ARR. _hoops_IPCP _hoops_PIH _hoops_APSAR _hoops_RPGAH
 *		_hoops_GGR _hoops_RH _hoops_PSHR _hoops_AGR _hoops_GAR _hoops_SSIA _hoops_RPGAH _hoops_GGR _hoops_APAPC._hoops_GGHR.
 */



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_CIAPI _hoops_RH _hoops_GPAAC _hoops_AIRI _hoops_ACSCC, _hoops_CGIC _hoops_RH _hoops_AAH _hoops_RAHRH _hoops_IS _hoops_SGH _hoops_RPP
 *		_hoops_RGR _hoops_HRGR _hoops_HAR _hoops_RH _hoops_SIRHGR _hoops_AGIR, _hoops_PPR _hoops_CCPP _hoops_PPR _hoops_HSPC _hoops_RH _hoops_GPAAC
 *		_hoops_SCHGR _hoops_PIH _hoops_HRPR.
 */
local bool start_device (Display_Context alter * dc) {
	int	_hoops_GCRHGR, _hoops_RCRHGR;
	X11Data alter * _hoops_RRRPC;

	ZALLOC (_hoops_RRRPC, X11Data);

	_hoops_CPAPGR ("start device", _hoops_RRRPC);


	_hoops_RRRPC->_hoops_APHPGR = _hoops_ACRHGR;

	/*_hoops_AGCR _hoops_CHR _hoops_IH _hoops_PCRHGR*/
	_hoops_RRRPC->first = true;
	_hoops_RRRPC->_hoops_PHAPC = false;
	_hoops_RRRPC->_hoops_RHSPC = (X_Window)0;

	/* _hoops_CSCR _hoops_CRPR _hoops_PIH */
	_hoops_RRRPC->_hoops_IHPPGR = _hoops_GIPPGR;
	_hoops_RRRPC->_hoops_GCPPGR = _hoops_RCPPGR;

	/* _hoops_GGRRR _hoops_SSGHGR */
	_hoops_RRRPC->_hoops_HCRHGR = _hoops_RRRPC->_hoops_ICRHGR = true;

	/* _hoops_ASSS _hoops_CCCSI _hoops_IS _hoops_PCCS _hoops_CGSI */
	_hoops_RRRPC->_hoops_CCRHGR = true;

	dc->data = (void alter *)_hoops_RRRPC;
	_hoops_RRRPC->dc = dc;

	/*
	 *		_hoops_GCAR _hoops_RH _hoops_GSSR _hoops_RIHH _hoops_PRCA -- _hoops_HIH _hoops_PIP _hoops_SGS _hoops_RH
	 *		_hoops_RIHH _hoops_IASAH _hoops_CHR _hoops_RPGGI _hoops_IIP _hoops_PIGS _hoops_HPP _hoops_PCCP _hoops_SCRHGR.
	 */
	XSetErrorHandler (_hoops_GPGHGR);
	XSetIOErrorHandler (_hoops_RPGHGR);

	/*
	 *		_hoops_GCRR _hoops_ISCP _hoops_HAII _hoops_AIRI _hoops_ACSCC.
	 */
	if (dc->_hoops_PCRSR[0] == '\0' ||
		dc->options._hoops_RGHRP == _hoops_GGHRP ||
		BIT (dc->options._hoops_IRARR, 0x00100000 /*_hoops_SCGHGR*/)) {

#	ifdef VMS_SYSTEM
		_hoops_RRRPC->display = (Display*) HD_Find_X11_Display ("DECW$DISPLAY");
#		else
		_hoops_RRRPC->display = (Display*) HD_Find_X11_Display (":0.0");
#	endif /* _hoops_SGGHGR */
	} else {
		char const	*in;
		char alter	*_hoops_PAGR;
		char			name[MAX_ERRMSG];

		in = dc->_hoops_PCRSR;
		_hoops_PAGR = name;

		while ((*in != '\0') && (*in != '+')) {
			*_hoops_PAGR++ = *in++;
		}
		*_hoops_PAGR = '\0';

		_hoops_RRRPC->display = (Display*) HD_Find_X11_Display (name);
#		ifdef _hoops_SCIGI
		if (_hoops_RRRPC->display == (Display *) null) {
			char _hoops_GSRHGR[MAX_ERRMSG];

			if (getenv("VISUALIZER_DISPLAY") != NULL) {
				strcpy(_hoops_GSRHGR, getenv("VISUALIZER_DISPLAY")) ;
				if (strstr(_hoops_GSRHGR,"0.1") != NULL)
					_hoops_RRRPC->display = (Display*)HD_Find_X11_Display ("unix:0.1");
				else
					_hoops_RRRPC->display = (Display*)HD_Find_X11_Display (_hoops_GSRHGR);
			}
		}
#		endif
	}


	/*_hoops_SR _hoops_HS _hoops_IS _hoops_HS _hoops_IRS _hoops_APIP _hoops_AIRI _hoops_IS _hoops_RACGH _hoops_RH _hoops_CHGHGR*/
	if (_hoops_RRRPC->display != (Display alter *)0) {
		if (XmbufQueryExtension (_hoops_RRRPC->display, &_hoops_GCRHGR, &_hoops_RCRHGR))
			{
				_hoops_CPAPGR ("X11 Multi-buffering supported", _hoops_RRRPC);
				_hoops_RRRPC->_hoops_SPGHGR = true;
			}
		else {
			_hoops_CPAPGR ("X11 Multi-buffering NOT supported or forcing pixmap double buffering", _hoops_RRRPC);
			_hoops_RRRPC->_hoops_SPGHGR = false;
		}

		XSetErrorHandler (_hoops_GRGHGR);
		XSetIOErrorHandler (_hoops_CAGHGR);
	}

	if (_hoops_RRRPC->display == (Display alter *)0) {
		char buf[MAX_ERRMSG];
		char const * _hoops_SSACR[5];
                H_FORMAT_TEXT _hoops_RSRHGR;

                if(getenv("DISPLAY"))
                    _hoops_RSRHGR = H_FORMAT_TEXT("      $DISPLAY is currently: \'%s\'.  Try HOOPS_PICTURE=\"x11/%s\"",
                        getenv("DISPLAY"), getenv("DISPLAY"));
                else
                    _hoops_RSRHGR = H_FORMAT_TEXT("      $DISPLAY isn't set.  Try setting DISPALY and HOOPS_PICTURE=\"x11/$DISPLAY\"");

		/* _hoops_IRHH _hoops_SGH _hoops_IIGR _hoops_SAGHGR _hoops_HHCI, _hoops_ARPP _hoops_SCH _hoops_SHPH */
		_hoops_PGGHGR (buf);
		_hoops_SSACR[1] = buf;
		/* _hoops_HA _hoops_AA _hoops_RH _hoops_ACSP */

		_hoops_SSACR[0] = Sprintf_S(null, "Unable to open X11 display for segment '%s' -", dc->_hoops_PCRSR);

#				ifdef VMS_SYSTEM
		_hoops_SSACR[2] = "Note: HOOPS_PICTURE should usually look like 'X11/DECW$DISPLAY' or";
		_hoops_SSACR[3] = "      'X11/host::DECW$DISPLAY'; for multiple windows add +nnn.";
                _hoops_SSACR[4] = _hoops_RSRHGR;
#				else /* _hoops_SGGHGR */
		_hoops_SSACR[2] = "Note: HOOPS_PICTURE should usually look like 'x11/:0.0' or";
		_hoops_SSACR[3] = "      'x11/host:display.screen'; for multiple windows add +nnn.";
                _hoops_SSACR[4] = _hoops_RSRHGR;
#				endif /* _hoops_SGGHGR */

		/* _hoops_RRI _hoops_SSHRH _hoops_HSAR _hoops_ASRHGR/2/3 _hoops_PAH _hoops_RGHH; _hoops_SGH _hoops_GPAPH */
		HI_Generate_Error (dc->_hoops_RIGC, HEC_X11_DRIVER, HES_CANNOT_OPEN_DISPLAY, 2, 5, (char const * alter *)_hoops_SSACR);

		return (false);
	}

	if (BIT (dc->options._hoops_IRARR, _hoops_ARAPGR)) {
		fprintf (stderr, "X11 Server: X11 connection invoked successfully for %s\n", dc->_hoops_PCRSR);
		fprintf (stderr, "\nX11 Server Version:\nDisplay opened on %s X%dR%d server\n\n",
				 ServerVendor (_hoops_RRRPC->display), ProtocolVersion (_hoops_RRRPC->display), VendorRelease (_hoops_RRRPC->display));
	}

	/*
	 *		_hoops_HGH _hoops_ISCP _hoops_GPAAC _hoops_HHSPC _hoops_RIAGI _hoops_RSIRR _hoops_PPR _hoops_RCSH _hoops_PHI.  _hoops_PHAA,
	 *		_hoops_ISPR _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_RGR _hoops_HRGR _hoops_GPAAC.  _hoops_CGP _hoops_HIS, _hoops_PSCR _hoops_CGIC _hoops_RH
	 *		_hoops_RIAGI _hoops_RSIRR.  _hoops_CGP _hoops_SR _hoops_AA _hoops_HAR _hoops_PGSPC _hoops_RGR _hoops_RIAGI, _hoops_PSCR _hoops_HPGGR _hoops_RGR
	 *		_hoops_GAR _hoops_PCCP _hoops_RHGC _hoops_GPAAC _hoops_HHSPC.  _hoops_CGP _hoops_SR _hoops_AA _hoops_PGSPC _hoops_RGR _hoops_RIAGI, _hoops_PSCR
	 *		_hoops_IPASR _hoops_RH _hoops_RCSH _hoops_PHI _hoops_RPP _hoops_SR _hoops_GCGH _hoops_SCH _hoops_IAII _hoops_SAHR _hoops_IPASR
	 *		_hoops_RH _hoops_RIAGI _hoops_RSIRR _hoops_SIHH _hoops_RH _hoops_RCSH _hoops_PHI.
	 */
	if (ProtocolVersion (_hoops_RRRPC->display) != 11)
		_hoops_RRRPC->_hoops_APHPGR = _hoops_PSRHGR;
	else
		_hoops_RRRPC->_hoops_APHPGR = _hoops_ACRHGR;

	/* _hoops_SIGR _hoops_IH _hoops_GHGHGR _hoops_AIRI _hoops_AHGHGR _hoops_IPHR _hoops_AARI */
	if (_hoops_GPPSA (ServerVendor (_hoops_RRRPC->display), 3, "Sil"))
		_hoops_RRRPC->_hoops_APHPGR = _hoops_SHGHGR;

	/* _hoops_RCPGR _hoops_IH _hoops_CAPCR _hoops_HSRHGR
	   _hoops_SHS _hoops_RPP (_hoops_ISRHGR (_hoops_CSRHGR (_hoops_APAPC->_hoops_AIRI), 3, "_hoops_GSCPGR"))
	   _hoops_CICA (_hoops_SSRHGR (_hoops_APAPC->_hoops_AIRI)) {
	   _hoops_AGIR 3300:	_hoops_APAPC->_hoops_GGAHGR = _hoops_RGAHGR; _hoops_IHSA;
	   _hoops_SHIR:				_hoops_APAPC->_hoops_GGAHGR = _hoops_AGAHGR; _hoops_IHSA;
	   }
	   _hoops_SHS _hoops_RPP (_hoops_ISRHGR (_hoops_CSRHGR (_hoops_APAPC->_hoops_AIRI), 8, "_hoops_GPAAC/_hoops_PGAHGR"))
	   _hoops_CICA (_hoops_SSRHGR (_hoops_APAPC->_hoops_AIRI)) {
	   _hoops_AGIR 3010:	_hoops_APAPC->_hoops_GGAHGR = _hoops_HGAHGR;				_hoops_IHSA;
	   _hoops_AGIR 3000:	_hoops_APAPC->_hoops_GGAHGR = _hoops_IGAHGR;					_hoops_IHSA;
	   _hoops_AGIR 2000:	_hoops_APAPC->_hoops_GGAHGR = _hoops_CGAHGR;					_hoops_IHSA;
	   _hoops_SHIR:				_hoops_APAPC->_hoops_GGAHGR = _hoops_SGAHGR;					_hoops_IHSA;
	   }
	   _hoops_SHS _hoops_RPP (_hoops_ISRHGR (_hoops_CSRHGR (_hoops_APAPC->_hoops_AIRI), 3, "_hoops_GRAHGR"))
	   _hoops_CICA (_hoops_SSRHGR (_hoops_APAPC->_hoops_AIRI)) {
	   _hoops_AGIR 5:				_hoops_APAPC->_hoops_GGAHGR = _hoops_RRAHGR;				_hoops_IHSA;
	   _hoops_AGIR 4:				_hoops_APAPC->_hoops_GGAHGR = _hoops_ARAHGR;				_hoops_IHSA;
	   _hoops_AGIR 3:				_hoops_APAPC->_hoops_GGAHGR = _hoops_PRAHGR;				_hoops_IHSA;
	   _hoops_AGIR 2:				_hoops_APAPC->_hoops_GGAHGR = _hoops_HRAHGR;				_hoops_IHSA;
	   _hoops_AGIR 1:				_hoops_APAPC->_hoops_GGAHGR = _hoops_IRAHGR;				_hoops_IHSA;
	   _hoops_SHIR:				_hoops_APAPC->_hoops_GGAHGR = _hoops_CRAHGR;					_hoops_IHSA;
	   }
	   _hoops_SHS _hoops_RPP (_hoops_ISRHGR (_hoops_CSRHGR (_hoops_APAPC->_hoops_AIRI), 3, "_hoops_SRAHGR"))
	   _hoops_CICA (_hoops_SSRHGR (_hoops_APAPC->_hoops_AIRI)) {
	   _hoops_AGIR 5:				_hoops_APAPC->_hoops_GGAHGR = _hoops_GAAHGR;				_hoops_IHSA;
	   _hoops_AGIR 4:				_hoops_APAPC->_hoops_GGAHGR = _hoops_RAAHGR;				_hoops_IHSA;
	   _hoops_SHIR:				_hoops_APAPC->_hoops_GGAHGR = _hoops_AAAHGR;					_hoops_IHSA;
	   }
	   _hoops_SHS _hoops_RPP (_hoops_ISRHGR (_hoops_CSRHGR (_hoops_APAPC->_hoops_AIRI), 3, "_hoops_PAAHGR"))
	   _hoops_CICA ((_hoops_RGRRR)_hoops_SSRHGR (_hoops_APAPC->_hoops_AIRI)) {
	   _hoops_AGIR 506000:	_hoops_APAPC->_hoops_GGAHGR = _hoops_HAAHGR;				_hoops_IHSA;
	   _hoops_AGIR 5:				_hoops_APAPC->_hoops_GGAHGR = _hoops_IAAHGR;				_hoops_IHSA;
	   _hoops_AGIR 4:				_hoops_APAPC->_hoops_GGAHGR = _hoops_CAAHGR;				_hoops_IHSA;
	   _hoops_AGIR 3:				_hoops_APAPC->_hoops_GGAHGR = _hoops_SAAHGR;				_hoops_IHSA;
	   _hoops_SHIR:				_hoops_APAPC->_hoops_GGAHGR = _hoops_GPAHGR;					_hoops_IHSA;
	   }
	   _hoops_SHS _hoops_RPP (_hoops_ISRHGR (_hoops_CSRHGR (_hoops_APAPC->_hoops_AIRI), 3, "_hoops_PPCAI"))
	   _hoops_CICA (_hoops_SSRHGR (_hoops_APAPC->_hoops_AIRI)) {
	   _hoops_AGIR 5:			_hoops_APAPC->_hoops_GGAHGR = _hoops_RPAHGR;				_hoops_IHSA;
	   _hoops_AGIR 4:			_hoops_APAPC->_hoops_GGAHGR = _hoops_APAHGR;				_hoops_IHSA;
	   _hoops_AGIR 3:			_hoops_APAPC->_hoops_GGAHGR = _hoops_PPAHGR;				_hoops_IHSA;
	   _hoops_SHIR:		_hoops_APAPC->_hoops_GGAHGR = _hoops_HPAHGR;					_hoops_IHSA;
	   }
	   _hoops_SHS
	   _hoops_APAPC->_hoops_GGAHGR = _hoops_IPAHGR;
	*/

	if (BIT (dc->options._hoops_IRARR, _hoops_IRAPGR))
		XSynchronize (_hoops_RRRPC->display, True);	/* (_hoops_HSRR _hoops_SCRAGR) */

	/* _hoops_GISA _hoops_RPHPGR _hoops_IH _hoops_IIPH _hoops_RSSI _hoops_PPR _hoops_SPSHH _hoops_PAIA */
	HD_Get_Bit_Patterns (dc, true);

	/* _hoops_CPHSR _hoops_SICAR */
	_hoops_RRRPC->_hoops_PRAPC = _hoops_PRAPC;
	_hoops_RRRPC->_hoops_SRAPC = _hoops_SRAPC;
	_hoops_RRRPC->_hoops_AAAPC = _hoops_AAAPC;
	_hoops_RRRPC->_hoops_PAAPC = _hoops_PAAPC;

	/* _hoops_HRCSR _hoops_SICAR */
	_hoops_RRRPC->_hoops_IACPGR = _hoops_IACPGR;
	_hoops_RRRPC->_hoops_HACPGR = _hoops_HACPGR;
	_hoops_RRRPC->_hoops_PGCPGR = _hoops_PGCPGR;

	_hoops_RRRPC->_hoops_RACSH = (XMaxRequestSize(_hoops_RRRPC->display)-3)/2;
	ALLOC_ARRAY (_hoops_RRRPC->_hoops_RAHPGR,_hoops_RRRPC->_hoops_RACSH,XPoint);
	_hoops_RRRPC->_hoops_HSAPGR = _hoops_IICIA;
	_hoops_RRRPC->_hoops_ISAPGR = -1;
	_hoops_RRRPC->_hoops_CSAPGR = _hoops_IICIA;
	_hoops_RRRPC->_hoops_SSAPGR = -1;

	_hoops_RRRPC->_hoops_GCPPGR = _hoops_RCPPGR;

	_hoops_RRRPC->_hoops_CCRHGR = true;

/* _hoops_RRAI _hoops_HPP _hoops_CPAHGR _hoops_IH _hoops_SPAHGR _hoops_GCGH */
#ifdef _hoops_CISPGR
	_hoops_GHAHGR(_hoops_RRRPC->display);
#endif

	/*
	 *		_hoops_RAP _hoops_RH _hoops_IRISR _hoops_SCHGR _hoops_GPRR _hoops_IS _hoops_RHAHGR.  _hoops_CGP _hoops_HPIH _hoops_IRISR _hoops_SCHGR
	 *		_hoops_HRGR _hoops_RCPH _hoops_IHHH, _hoops_PSCR _hoops_SGS _hoops_IRISR _hoops_SCHGR _hoops_GRS _hoops_HIAP _hoops_RGR _hoops_PSGR
	 *		_hoops_IS _hoops_RH _hoops_IRPR _hoops_PIRA.
	 */
	_hoops_RRRPC->driver_type = X11_ONLY;
	return true;
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_SIPR _hoops_CPHSR _hoops_HPHS _hoops_AHCA _hoops_RH _hoops_GPAAC _hoops_SISS.	_hoops_HGI _hoops_PCPH _hoops_HCPH
 *		_hoops_HRSP _hoops_RII _hoops_SICAR _hoops_HIS _hoops_SGS _hoops_RII _hoops_GRRGI _hoops_SGS _hoops_ARAS _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_GPAAC _hoops_PPR
 *		_hoops_IAGC _hoops_CPHSR _hoops_HPHS _hoops_AHCA _hoops_PAII _hoops_SISS _hoops_PGAP _hoops_GCA _hoops_IRS _hoops_RPPS
 *		_hoops_IS _hoops_SHH _hoops_IGS _hoops_PAH _hoops_SGH _hoops_RH _hoops_GPAAC _hoops_SCHGR'_hoops_GRI _hoops_RPGP _hoops_RPPS _hoops_IH _hoops_RGR _hoops_AHAR.
 */
local void get_physical_info (
		Display_Context alter		*dc) {
		X11Data alter							*_hoops_RRRPC = X11D(dc);

		(*_hoops_RRRPC->_hoops_PRAPC) (dc);

		if (dc->options._hoops_GCHSR == 0 && dc->options._hoops_ISPRP == 0) {
				(*_hoops_RRRPC->_hoops_SRAPC) (dc);
				(*_hoops_RRRPC->_hoops_AAAPC) (dc);
		}
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_CPCS _hoops_RH _hoops_GPAAC _hoops_AHAHGR _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_RH _hoops_SIRHGR _hoops_AGIR, _hoops_GGGR
 *		_hoops_RH _hoops_GPAAC _hoops_AIRI _hoops_ACSCC, _hoops_PPR _hoops_CIH _hoops_RH _hoops_GPAAC _hoops_SCHGR _hoops_PIH _hoops_HRPR.
 */
local void stop_device (
		Display_Context alter	*dc) {
		X11Data alter				*_hoops_RRRPC = X11D(dc);

		_hoops_CPAPGR ("stop device", _hoops_RRRPC);

		FREE_ARRAY (_hoops_RRRPC->_hoops_RAHPGR, _hoops_RRRPC->_hoops_RACSH, XPoint);
		if (_hoops_RRRPC->_hoops_CHPPGR != null) {
				_hoops_RRRPC->_hoops_CHPPGR->data = null;
				XDestroyImage (_hoops_RRRPC->_hoops_CHPPGR);
		}

		/*_hoops_HAGGR _hoops_RH _hoops_PHAHGR*/
		/*_hoops_IPIH _hoops_IGI _hoops_GGR 16b_hoops_SCH _hoops_RGAR*/
		{
			int i,j;
			for (i=0;i<_hoops_HSPPGR;i++)
				for (j=0;j<_hoops_ISPPGR;j++)
					if (_hoops_RRRPC->_hoops_SSPPGR[i][j] != null) {
						FREE_ARRAY (_hoops_RRRPC->_hoops_SSPPGR[i][j]->data, (j+1)*(i+1), RGBAS32);
						_hoops_RRRPC->_hoops_SSPPGR[i][j]->data=null;
						XDestroyImage (_hoops_RRRPC->_hoops_SSPPGR[i][j]);
					}
		}

		if (_hoops_RRRPC->_hoops_SIPPGR != null) {
				_hoops_RRRPC->_hoops_SIPPGR->data = null;
				XDestroyImage (_hoops_RRRPC->_hoops_SIPPGR);
		}

		if (_hoops_RRRPC->_hoops_PHGH != null)
				FREE_ARRAY (_hoops_RRRPC->_hoops_PHGH, _hoops_RRRPC->_hoops_PASIH, RGBAS32);

		if (_hoops_RRRPC->_hoops_SGHPGR != null)
				FREE_ARRAY (_hoops_RRRPC->_hoops_SGHPGR, _hoops_RRRPC->_hoops_GRHPGR, unsigned char);

		if (_hoops_RRRPC->_hoops_ARHPGR != null)
				FREE_ARRAY (_hoops_RRRPC->_hoops_ARHPGR, _hoops_RRRPC->_hoops_PRHPGR, unsigned short);

#		ifdef _hoops_ICIGI
				XJp_end (_hoops_RRRPC->_hoops_HHAHGR, _hoops_RRRPC->window);
				XJp_close (_hoops_RRRPC->_hoops_HHAHGR);
#		endif /* _hoops_ARSPGR */

		if (_hoops_RRRPC->_hoops_PCSPGR && _hoops_RRRPC->window != (X_Window)0)
				XmbufDestroyBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window);

		if (_hoops_RRRPC->_hoops_CCSPGR)
				XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CCSPGR);

		if (_hoops_RRRPC->bitmap) {
				XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->bitmap);
				FREE_ARRAY (_hoops_RRRPC->_hoops_SIRRC, _hoops_RRRPC->_hoops_PSHPGR * _hoops_RRRPC->_hoops_PSHPGR / 8, char);
		}

		if (_hoops_RRRPC->_hoops_IHHPGR)
				XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IHHPGR);

		if (dc->options._hoops_GCHSR == 0 && dc->options._hoops_ISPRP == 0 &&
				_hoops_RRRPC->window != (X_Window)0)
				XDestroyWindow (_hoops_RRRPC->display, _hoops_RRRPC->window);

		if (_hoops_RRRPC->driver_type == _hoops_PPAPC && _hoops_RRRPC->_hoops_CAAAC)
				XFree ((caddr_t)_hoops_RRRPC->_hoops_CAAAC);

		if (_hoops_RRRPC->display)
			HD_Free_X11_Display(_hoops_RRRPC->display);
		FREE (_hoops_RRRPC, X11Data);

		dc->data = null;
}



/****************************************************************
 ****************************************************************
								  _hoops_RGGIR _hoops_GRGGR _hoops_SAAAR _hoops_HRAIA _hoops_AHGPH		   _hoops_SRSCI _hoops_GHAP _hoops_PGGIR _hoops_APCAR _hoops_RGGIR _hoops_SRSCI
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_PGAA **
 *
 *		_hoops_HGI _hoops_PCPH _hoops_ARH _hoops_GGRRR _hoops_SSGHGR _hoops_IH _hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_PPARI _hoops_ISIIR
 *		_hoops_ISCP _hoops_GPAAC _hoops_RPPS.
 */
local void _hoops_IHAHGR (
		Display_Context const		*dc) {
		X11Data alter					*_hoops_RRRPC = X11D(dc);
		XSizeHints						_hoops_CHAHGR;

		SET_MEMORY(&_hoops_CHAHGR, sizeof(XSizeHints), 0);

		if (!dc->options._hoops_AASSP) {
				_hoops_CHAHGR.min_width = _hoops_RRRPC->window_width;
				_hoops_CHAHGR.min_height = _hoops_RRRPC->window_height;
				_hoops_CHAHGR.max_width = _hoops_RRRPC->window_width;
				_hoops_CHAHGR.max_height = _hoops_RRRPC->window_height;
				_hoops_CHAHGR.min_aspect.x = _hoops_CHAHGR.min_width;
				_hoops_CHAHGR.min_aspect.y = _hoops_CHAHGR.min_height;
				_hoops_CHAHGR.max_aspect.x = _hoops_CHAHGR.min_width;
				_hoops_CHAHGR.max_aspect.y = _hoops_CHAHGR.min_height;
		}
		else if (!dc->options._hoops_PASSP) {
				_hoops_CHAHGR.min_width = 1;
				_hoops_CHAHGR.min_height = 1;
				_hoops_CHAHGR.max_width = WidthOfScreen (_hoops_RRRPC->screen) -
						2*_hoops_RRRPC->_hoops_PGRHGR;
				_hoops_CHAHGR.max_height = HeightOfScreen (_hoops_RRRPC->screen) -
						_hoops_RRRPC->_hoops_PGRHGR - _hoops_RRRPC->_hoops_HGRHGR;
				_hoops_CHAHGR.min_aspect.x = _hoops_RRRPC->window_width;
				_hoops_CHAHGR.min_aspect.y = _hoops_RRRPC->window_height;
				_hoops_CHAHGR.max_aspect.x = _hoops_RRRPC->window_width;
				_hoops_CHAHGR.max_aspect.y = _hoops_RRRPC->window_height;
		}
		else {
				_hoops_CHAHGR.min_width = 1;
				_hoops_CHAHGR.min_height = 1;
				_hoops_CHAHGR.max_width = WidthOfScreen (_hoops_RRRPC->screen) -
						2*_hoops_RRRPC->_hoops_PGRHGR;
				_hoops_CHAHGR.max_height = HeightOfScreen (_hoops_RRRPC->screen) -
						_hoops_RRRPC->_hoops_PGRHGR - _hoops_RRRPC->_hoops_HGRHGR;
				_hoops_CHAHGR.min_aspect.x = 1;
				_hoops_CHAHGR.min_aspect.y = _hoops_CHAHGR.max_height;
				_hoops_CHAHGR.max_aspect.x = _hoops_CHAHGR.max_width;
				_hoops_CHAHGR.max_aspect.y = 1;
		}

		_hoops_CHAHGR.flags = PMinSize | PMaxSize | PAspect;

		if (((_hoops_RRRPC->_hoops_APHPGR == _hoops_PPHPGR) &&
				_hoops_AGGR (dc->_hoops_PGCC.driver_type, "GL")) ||
				BIT(dc->options.flags, _hoops_GIPRP)
			) {
				/*
				 *		_hoops_IPCP _hoops_ICAPR _hoops_GPAAC _hoops_HHSPC _hoops_CGPR _hoops_ARAS _hoops_HPP _hoops_RH _hoops_IIIGC _hoops_RHPP _hoops_PPR _hoops_RAGA
				 *		_hoops_GGRRR _hoops_SSGHGR _hoops_RIRPR _hoops_CPPPR _hoops_SSHRR. _hoops_PHGP _hoops_HSGR _hoops_IGRC _hoops_RGSR
				 *		_hoops_RH _hoops_SSGHGR...
				 */
		}
		else
				/* _hoops_HCRS _hoops_IAISR _hoops_PPR _hoops_AA _hoops_SCH. */
				XSetNormalHints (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_CHAHGR);

		_hoops_RRRPC->_hoops_ICRHGR = dc->options._hoops_AASSP;
		_hoops_RRRPC->_hoops_HCRHGR = dc->options._hoops_PASSP;
}

#ifdef _hoops_CISPGR
/*		_hoops_RRAI _hoops_HPP _hoops_CPAHGR _hoops_IH _hoops_SPAHGR _hoops_GCGH */
void _hoops_SHAHGR(Display *display, X_Window window) {
	XEventClass _hoops_GIAHGR[15];
	int rc, _hoops_RIAHGR = 0;
	X11Data alter					*_hoops_RRRPC = X11D(dc);

  _hoops_CPAPGR("select extension events", _hoops_RRRPC);

  if (_hoops_AIAHGR) {
		_hoops_PIAHGR(_hoops_AIAHGR, _hoops_HIAHGR, _hoops_GIAHGR[_hoops_RIAHGR]);
		_hoops_RIAHGR++;

		_hoops_IIAHGR(_hoops_AIAHGR, _hoops_CIAHGR, _hoops_GIAHGR[_hoops_RIAHGR]);
		_hoops_RIAHGR++;

#if 0  /* _hoops_SIAHGR _hoops_HAR _hoops_ASAS */
		_hoops_GCAHGR(_hoops_AIAHGR, _hoops_RCAHGR,
												  _hoops_GIAHGR[_hoops_RIAHGR]);
		_hoops_RIAHGR++;
		_hoops_ACAHGR(_hoops_AIAHGR, _hoops_PCAHGR,
												_hoops_GIAHGR[_hoops_RIAHGR]);
		_hoops_RIAHGR++;
		_hoops_HCAHGR(_hoops_AIAHGR, _hoops_ICAHGR,
										  _hoops_GIAHGR[_hoops_RIAHGR]);
		_hoops_RIAHGR++;
#endif
  }

  if (_hoops_RIAHGR)
		XSelectExtensionEvent(display, window, _hoops_GIAHGR, _hoops_RIAHGR);
}
#endif /* _hoops_CCAHGR */


/*
 *		** _hoops_SRAC **
 *
 *		_hoops_PIPAH _hoops_SGH _hoops_RH _hoops_RPPS _hoops_ARSAR _hoops_IS _hoops_IHHH _hoops_AIH _hoops_SIRHGR _hoops_PAR _hoops_IAGC _hoops_SPR
 *		_hoops_HII _hoops_RH _hoops_GPAAC _hoops_HHSPC.  _hoops_RAP _hoops_GH _hoops_RH _hoops_HGIR _hoops_PPR _hoops_RII _hoops_RPPS _hoops_AIRC
 *		_hoops_PPR _hoops_PPIP _hoops_RH _hoops_HCISR _hoops_IIHGC _hoops_IGI.
 */
local POINTER_SIZED_INT get_outer_window (
	Display_Context		*dc) {
	X11Data alter			*_hoops_RRRPC = X11D(dc);
	unsigned long			_hoops_ASGHGR;
	XSetWindowAttributes	_hoops_RSGHGR;
	XSizeHints				_hoops_PCSPC;
	XWMHints				_hoops_SCAHGR;
	XGCValues				_hoops_RGPPGR;
	Atom					wm_delete_window;

	_hoops_CPAPGR ("get outer window", _hoops_RRRPC);
	ZERO_STRUCT(&_hoops_SCAHGR, XWMHints);
	ZERO_STRUCT(&_hoops_PCSPC, XSizeHints);

	if (dc->options._hoops_GCHSR != 0 &&
		dc->options._hoops_RGHRP != _hoops_GGHRP &&
		!BIT (dc->options._hoops_IRARR, 0x00100000 /*_hoops_SCGHGR*/)) {
		/* _hoops_SGPR _hoops_RH _hoops_CHIA _hoops_GPAAC _hoops_RPPS _hoops_RCC */
		_hoops_RRRPC->window = dc->options._hoops_GCHSR;
		_hoops_RRRPC->_hoops_CCRHGR = true;	/* _hoops_HHSA _hoops_RHSHA _hoops_GPP _hoops_IGIR */

		_hoops_ASGHGR = CWBitGravity;
		_hoops_RSGHGR.bit_gravity = ForgetGravity;

		if (dc->options.backing_store) {
			_hoops_ASGHGR |= CWBackingStore;
			_hoops_RSGHGR.backing_store = WhenMapped;
		}

		if (_hoops_RRRPC->_hoops_HISPGR) {
			if (dc->options._hoops_RCHSR != 0)
				_hoops_RRRPC->_hoops_GPIHP = dc->options._hoops_RCHSR;
			else
				_hoops_ICGHGR(dc);
			_hoops_ASGHGR |= CWColormap;
			_hoops_RSGHGR.colormap = _hoops_RRRPC->_hoops_GPIHP;
		}

		XChangeWindowAttributes (_hoops_RRRPC->display, _hoops_RRRPC->window,
														 _hoops_ASGHGR, &_hoops_RSGHGR);

		if (dc->options._hoops_CRSSP) {
			/*
			 *		_hoops_AGAH _hoops_HRGR _hoops_HAR _hoops_CPIC _hoops_IS _hoops_RGHH _hoops_GII _hoops_CIIA.
			 *		_hoops_HGI _hoops_CGH _hoops_RGAR _hoops_SHH _hoops_PIGS _hoops_RPP _hoops_RHAC'_hoops_ASAR _hoops_GGR _hoops_SGH _hoops_RPPS _hoops_CRSRR _hoops_CCH _hoops_PPR _hoops_CHR
			 *		_hoops_CPIC _hoops_IS _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_HCR _hoops_CIIA _hoops_GSAHGR _hoops_PRGI _hoops_RPPS _hoops_PCCS, _hoops_AHI.
			 */
		}
		else if (dc->options._hoops_IRSSP)
			XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRAPGR);
		else {
			XWindowAttributes				_hoops_GHSPC;

			XGetWindowAttributes (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_GHSPC);
			if (ANYBIT (_hoops_GHSPC.all_event_masks, MOUSE_EVENTS | KEYBOARD_EVENTS)) {
				_hoops_ARGIP (HEC_X11_DRIVER, HES_ENABLE_MOUSE_KEYBOARD_EVENT,
					 "Unable to enable mouse/keyboard input events in X11 Driver -",
					 Sprintf_LD (null, "Another client already has them turned on for Window ID = %D",
							 _hoops_RRRPC->window), "(You may want to use the 'disable input' Driver Option.)");
				XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRAPGR);
			}
			else {
				XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_GRAPGR);
#ifdef _hoops_CISPGR
				_hoops_SHAHGR(_hoops_RRRPC->display, _hoops_RRRPC->window);
#endif
			}
		}

#ifdef X11R3
		_hoops_RRRPC->_hoops_SAIPGR = false;
		_hoops_RRRPC->_hoops_GPIPGR = false;			/* _hoops_CIPIP _hoops_CGISR */
#endif /* _hoops_RPIPGR */

		if (!dc->options._hoops_CRSSP)
			_hoops_PRSPGR (_hoops_RRRPC, StructureNotifyMask);

		_hoops_GASPGR (dc,
			  &_hoops_RRRPC->window_x, &_hoops_RRRPC->window_y,
			  &_hoops_RRRPC->window_width, &_hoops_RRRPC->window_height);

	}
	else {
		/*
		 *				_hoops_RSAHGR _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_SGH _hoops_RPPS _hoops_RCC _hoops_AGIR.	_hoops_AGAH _hoops_GRS _hoops_SHH _hoops_PRCA _hoops_HCR
		 *				_hoops_RH _hoops_CIIA.
		 */
		XEvent	_hoops_GSSPC;

		_hoops_GASPGR (dc,
			  &_hoops_RRRPC->window_x, &_hoops_RRRPC->window_y,
			  &_hoops_RRRPC->window_width, &_hoops_RRRPC->window_height);

		/*
		 * _hoops_IIGAA _hoops_GPAAC _hoops_RHAP _hoops_HGCR _hoops_AAH _hoops_RAHRH _hoops_SHRII _hoops_RSIH (_hoops_GGR
		 * _hoops_GRPAI) _hoops_PPR _hoops_HIHH _hoops_IRHS _hoops_SCH _hoops_GSGS _hoops_SPHR (_hoops_RAS
		 * _hoops_SCH _hoops_CGISR _hoops_RPP _hoops_SR _hoops_RRP _hoops_GHGPR _hoops_RHGPR _hoops_PAR _hoops_HAR...).
		 *
		 */
		if (_hoops_RRRPC->driver_type == _hoops_PPAPC) {
			_hoops_PPGHGR (dc);
		}

		if (!_hoops_RRRPC->_hoops_ASAHGR) {
			XEvent _hoops_PSAHGR;


			_hoops_CPAPGR ("creating new X11 window", _hoops_RRRPC);

			_hoops_ASGHGR = CWBackPixel | CWBorderPixel | CWBitGravity | CWOverrideRedirect;
			_hoops_RSGHGR.background_pixel = WhitePixelOfScreen (_hoops_RRRPC->screen);
			_hoops_RSGHGR.border_pixel = BlackPixelOfScreen (_hoops_RRRPC->screen);
			_hoops_RSGHGR.bit_gravity = ForgetGravity;
			_hoops_RSGHGR.override_redirect = !dc->options._hoops_HRSSP;

			if (dc->options.backing_store) {
					_hoops_ASGHGR |= CWBackingStore;
					_hoops_RSGHGR.backing_store = WhenMapped;
			}

			if (_hoops_RRRPC->_hoops_HISPGR) {
					_hoops_ICGHGR (dc);
					_hoops_ASGHGR |= CWColormap;
					_hoops_RSGHGR.colormap = _hoops_RRRPC->_hoops_GPIHP;
			}

			_hoops_RRRPC->_hoops_IRSPGR = _hoops_RRRPC->_hoops_CISPC;

#ifndef VMS_SYSTEM
			/*
			 *		_hoops_IGRHGR _hoops_RH _hoops_HSAHGR _hoops_PPR _hoops_ISAHGR
			 *		_hoops_HII _hoops_RH _hoops_AHC _hoops_IIGR _hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_IS _hoops_IRAA _hoops_CRGR _hoops_HIHA
			 *		_hoops_RH _hoops_IHH _hoops_CCAC _hoops_SGS _hoops_GRS _hoops_SHH _hoops_GGAPH _hoops_HPP _hoops_RH _hoops_CSAHGR _hoops_IIGR
			 *		_hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_HPP _hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_PPARI.
			 */
			if (dc->options._hoops_HRSSP) {
				_hoops_RRRPC->window_x -= _hoops_RRRPC->_hoops_PGRHGR;
				_hoops_RRRPC->window_y -= _hoops_RRRPC->_hoops_HGRHGR;
			}
#endif /* _hoops_SGGHGR */

			_hoops_RRRPC->window = XCreateWindow (_hoops_RRRPC->display,
											 _hoops_RRRPC->_hoops_IRSPGR,
											 _hoops_RRRPC->window_x, _hoops_RRRPC->window_y,
											 _hoops_RRRPC->window_width, _hoops_RRRPC->window_height,
											 0, _hoops_RRRPC->depth,
											 InputOutput, _hoops_RRRPC->visual, _hoops_ASGHGR, &_hoops_RSGHGR);

			/*
			 *		_hoops_SIPR _hoops_PCCP _hoops_SSAHGR _hoops_IH _hoops_PRCA _hoops_GGPHGR _hoops_CGPR _hoops_RH _hoops_RPPS
			 *		_hoops_PPARI _hoops_GGGR _hoops_CHSAP _hoops_HRGR _hoops_PACIA _hoops_IH _hoops_RH _hoops_RPPS.
			 */

			wm_delete_window = XInternAtom (_hoops_RRRPC->display, "WM_DELETE_WINDOW", False);
			XSetWMProtocols (_hoops_RRRPC->display, _hoops_RRRPC->window, &wm_delete_window, 1);


			/*
			 *		_hoops_RAP _hoops_IRS _hoops_RPPS _hoops_RSIRR _hoops_IH _hoops_RH _hoops_RPPS _hoops_PPARI.
			 */
			HI_Copy_Name_To_Chars ((_hoops_HCRPR alter *)&dc->options._hoops_IAPIR, _hoops_RRRPC->_hoops_IAPIR);
			_hoops_HPRPR (" ", _hoops_RRRPC->_hoops_IAPIR);
			XStoreName (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRRPC->_hoops_IAPIR);

			/*
			 *		_hoops_RAP _hoops_IGIR _hoops_SSGHGR _hoops_IH _hoops_RH _hoops_RPPS _hoops_PPARI.
			 */
			_hoops_PCSPC.x = _hoops_RRRPC->window_x;
			_hoops_PCSPC.y = _hoops_RRRPC->window_y;
			_hoops_PCSPC.width = _hoops_RRRPC->window_width;
			_hoops_PCSPC.height = _hoops_RRRPC->window_height;
			_hoops_PCSPC.flags = USPosition | USSize;

			XSetNormalHints (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_PCSPC);

			if (dc->options._hoops_CRSSP) {
				/*
				 * _hoops_IPCP _hoops_IPSP _hoops_APSI _hoops_SCH _hoops_RGR _hoops_PPRRR, _hoops_IRISP _hoops_SAGGR _hoops_SCH
				 */
			}
			else if (dc->options._hoops_IRSSP)
				XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRAPGR);
			else {
				/*
				 *		_hoops_RAP _hoops_CIIRH _hoops_CIIA _hoops_SSGHGR _hoops_IH _hoops_RH _hoops_RPPS _hoops_PPARI.
				 */
				_hoops_SCAHGR.input = True;
				_hoops_SCAHGR.flags = InputHint;
				XSetWMHints (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_SCAHGR);
				XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_GRAPGR);
#ifdef _hoops_CISPGR
				_hoops_SHAHGR (_hoops_RRRPC->display, _hoops_RRRPC->window);
#endif
			}

			if (!dc->options._hoops_IASSP) {

				XMapWindow (_hoops_RRRPC->display, _hoops_RRRPC->window);

				if (BIT(dc->options.flags, _hoops_GIPRP)) {
					_hoops_PSAHGR.type = ClientMessage;
					_hoops_PSAHGR.xclient.window = _hoops_RRRPC->window;
					_hoops_PSAHGR.xclient.message_type = XInternAtom(_hoops_RRRPC->display, "_NET_WM_STATE", False);
					_hoops_PSAHGR.xclient.format = 32;
					_hoops_PSAHGR.xclient.data.l[0] = 1;
					_hoops_PSAHGR.xclient.data.l[1] = XInternAtom(_hoops_RRRPC->display, "_NET_WM_STATE_FULLSCREEN", False);
					_hoops_PSAHGR.xclient.data.l[2] = 0;
					XSendEvent(_hoops_RRRPC->display, DefaultRootWindow(_hoops_RRRPC->display), False, SubstructureNotifyMask, &_hoops_PSAHGR);
				}
				else
					UNREFERENCED(_hoops_PSAHGR);

#ifdef _hoops_ICIGI
				{
				long	 _hoops_SAPPGR;

				_hoops_SAPPGR = XJP_PWIDTH | XJP_PHEIGHT | XJP_WIDTH |
										XJP_HEIGHT | XJP_FG | XJP_BG | XJP_BP;
				_hoops_RRRPC->_hoops_HHAHGR = XJp_open (_hoops_RRRPC->display, _hoops_RRRPC->window,
																  _hoops_SAPPGR, &(_hoops_RRRPC->values), 2);
				XJp_begin (_hoops_RRRPC->_hoops_HHAHGR, _hoops_RRRPC->window);
				}
#endif /* _hoops_ARSPGR */

				/*
				 *				_hoops_SPPRH _hoops_IH _hoops_CGSI _hoops_IS _hoops_SCRRI _hoops_ISHP _hoops_PPR _hoops_RH _hoops_IGRSC _hoops_IS _hoops_RGPHGR.
				 */
				if (!dc->options._hoops_CRSSP) {
					if (_hoops_RRRPC->driver_type == _hoops_PPAPC)
					   XWindowEvent (_hoops_RRRPC->display, _hoops_RRRPC->window, StructureNotifyMask, &_hoops_GSSPC);
					else
					   XWindowEvent (_hoops_RRRPC->display, _hoops_RRRPC->window, ExposureMask, &_hoops_GSSPC);
				}

			}

			/*
			 *		_hoops_PAGA: _hoops_HHPR _hoops_PCIRA _hoops_SSHGR _hoops_PPR _hoops_ARP _hoops_PCCS _hoops_SSGHGR _hoops_RGAR
			 *		_hoops_RAS _hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_SSCP _hoops_RPII _hoops_SCGH; _hoops_IAII _hoops_RH
			 *		_hoops_GPAAC _hoops_RPPS _hoops_AHC/_hoops_CIGS _hoops_IGIR _hoops_SSGHGR _hoops_CHR _hoops_RHPH _hoops_CCA
			 *		_hoops_ICRP _hoops_GPAAC _hoops_RPPS _hoops_PRRHGR.
			 */
			if (!dc->options._hoops_CRSSP)
					_hoops_PRSPGR (_hoops_RRRPC, StructureNotifyMask);
			_hoops_IHAHGR (dc);
		}
		else {
			_hoops_CPAPGR ("reusing X11 window", _hoops_RRRPC);

			if (_hoops_RRRPC->_hoops_HISPGR) {
				_hoops_ICGHGR (dc);
				XSetWindowColormap (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRRPC->_hoops_GPIHP);
			}

			XMoveResizeWindow (_hoops_RRRPC->display, _hoops_RRRPC->window,
							   _hoops_RRRPC->window_x - _hoops_RRRPC->_hoops_PGRHGR,
							   _hoops_RRRPC->window_y - _hoops_RRRPC->_hoops_HGRHGR,
							   _hoops_RRRPC->window_width, _hoops_RRRPC->window_height);

			/*
			 *		_hoops_RAP _hoops_IRS _hoops_RPPS _hoops_RSIRR _hoops_IH _hoops_RH _hoops_RPPS _hoops_PPARI.
			 */
			HI_Copy_Name_To_Chars ((_hoops_HCRPR alter *)&dc->options._hoops_IAPIR, _hoops_RRRPC->_hoops_IAPIR);
			_hoops_HPRPR (" ", _hoops_RRRPC->_hoops_IAPIR);
			XStoreName (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRRPC->_hoops_IAPIR);

			/*
			 *		_hoops_RAP _hoops_IGIR _hoops_SSGHGR _hoops_IH _hoops_RH _hoops_RPPS _hoops_PPARI.
			 */
			_hoops_PCSPC.x = _hoops_RRRPC->window_x;
			_hoops_PCSPC.y = _hoops_RRRPC->window_y;
			_hoops_PCSPC.width = _hoops_RRRPC->window_width;
			_hoops_PCSPC.height = _hoops_RRRPC->window_height;
			_hoops_PCSPC.flags = USPosition | USSize;

			XSetNormalHints (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_PCSPC);

			if (dc->options._hoops_CRSSP) {
					/*
					 *		_hoops_CGP _hoops_GII _hoops_PGRRR _hoops_SSCP _hoops_HHPPR _hoops_RH _hoops_RPPS _hoops_IS _hoops_SHH _hoops_ICCSI _hoops_HGPP _hoops_GAR
					 *		_hoops_PCCS, _hoops_GHGPR _hoops_RHGPR, _hoops_AHI.
					 */
			}
			else if (dc->options._hoops_IRSSP)
					XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRAPGR);
			else {
					/*
					 *		_hoops_RAP _hoops_CIIRH _hoops_CIIA _hoops_SSGHGR _hoops_IH _hoops_RH _hoops_RPPS _hoops_PPARI.
					 */
					_hoops_SCAHGR.input = True;
					_hoops_SCAHGR.flags = InputHint;
					XSetWMHints (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_SCAHGR);
					XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_GRAPGR);
#ifdef _hoops_CISPGR
					_hoops_SHAHGR (_hoops_RRRPC->display, _hoops_RRRPC->window);
#endif
			}

			if (!dc->options._hoops_CRSSP)
					_hoops_PRSPGR (_hoops_RRRPC, StructureNotifyMask);

			_hoops_IHAHGR (dc);
		}

		/*
		 * _hoops_HIRRH _hoops_GIAP _hoops_RPPS _hoops_RCC _hoops_ASRC _hoops_PIRA.
		 */
		((Display_Context alter *)dc)->current._hoops_RAPGH =	/* _hoops_HIIC _hoops_HRGR _hoops_GPRS */
				(long)_hoops_RRRPC->window;

		((Display_Context alter *)dc)->current._hoops_PAPGH = 0;

		/* _hoops_HPPP _hoops_RH _hoops_GRAHA _hoops_SSHGR */
		XSync (_hoops_RRRPC->display, False);
		check_events (dc);

#ifdef X11R3
		_hoops_RRRPC->_hoops_SAIPGR = false;
		_hoops_RRRPC->_hoops_GPIPGR = false;
#endif
	}

	/*
	 * _hoops_HIRRH _hoops_GIAP _hoops_RPPS _hoops_RCC _hoops_ASRC _hoops_PIRA.
	 */
	((Display_Context alter *)dc)->current._hoops_PAPGH = (long)_hoops_RRRPC->display;

	_hoops_RRRPC->_hoops_ASAHGR = false;

	/*
	 * _hoops_ICRPC _hoops_RGAR _hoops_AGPHGR _hoops_PGPHGR _hoops_RGR _hoops_RHPP _hoops_IH _hoops_HGGSP _hoops_PARPI. _hoops_PSPC _hoops_RH
	 * _hoops_GPAAC _hoops_RHPP _hoops_HRGR _hoops_HGPHGR _hoops_PIGS _hoops_CRSIR _hoops_IS _hoops_PGSA _hoops_PA. _hoops_RAHP _hoops_HGPP, _hoops_SR _hoops_GA'_hoops_RA
	 * _hoops_RRP _hoops_IS _hoops_RIPHR _hoops_GII _hoops_CSCR _hoops_PSCA _hoops_GHCRH _hoops_AICCI _hoops_GII _hoops_HCISR _hoops_IIHGC.
	 */
	if (_hoops_RRRPC->driver_type == _hoops_PCGHGR) {
		_hoops_RRRPC->_hoops_HISPGR = false;
		_hoops_RRRPC->_hoops_GAPPGR = 0;
		return (long)_hoops_RRRPC->window;
	}

	if (_hoops_RRRPC->_hoops_CHPPGR == null) {
		switch (_hoops_RRRPC->visual->c_class) {
			case GrayScale:
			case StaticGray: {
				if (_hoops_RRRPC->_hoops_CRAPC == 1) {
					/* _hoops_CASAS */
					_hoops_RRRPC->_hoops_CHPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
														  1, XYBitmap, 0, null,
														  _hoops_HIRSP, 1, 8, 0);
				}
				else {
					/* _hoops_IGPHGR */
					_hoops_RRRPC->_hoops_CHPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
													  8, ZPixmap, 0, null,
													  _hoops_HIRSP, 1, 8, 0);
				}
			}break;

			case DirectColor:
			case TrueColor: {
				/* _hoops_GGCSI */
				_hoops_RRRPC->_hoops_CHPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
												  24, ZPixmap, 0, null,
												  _hoops_HIRSP, 1, 32, 0);
			}break;

			case PseudoColor:
			case StaticColor: {
				if (_hoops_RRRPC->_hoops_CRAPC <= 8) {
					/* _hoops_SCGH 8 */
					_hoops_RRRPC->_hoops_CHPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
												  8, ZPixmap, 0, null,
												  _hoops_HIRSP, 1, 8, 0);
				}
				else {
					/* _hoops_CGPHGR */
					_hoops_RRRPC->_hoops_CHPPGR = XCreateImage (_hoops_RRRPC->display, _hoops_RRRPC->visual,
												  16, ZPixmap, 0, null,
												  _hoops_HIRSP, 1, 16, 0);
				}
			}break;
		}
	}

	/* _hoops_GISA _hoops_RH _hoops_SGPHGR'_hoops_GRI */
	_hoops_RGPPGR.fill_style = FillSolid;
	_hoops_RRRPC->_hoops_AAPPGR  = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->window, GCFillStyle, &_hoops_RGPPGR);
	_hoops_RRRPC->_hoops_PPPPGR  = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->window, GCFillStyle, &_hoops_RGPPGR);
	_hoops_RRRPC->_hoops_ISHPGR  = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->window, GCFillStyle, &_hoops_RGPPGR);
	_hoops_RRRPC->_hoops_PHPPGR = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->window, GCFillStyle, &_hoops_RGPPGR);
	_hoops_RRRPC->_hoops_GRPHGR  = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->window, GCFillStyle, &_hoops_RGPPGR);

	_hoops_RGPPGR.fill_style = FillStippled;
	_hoops_RRRPC->_hoops_CHHPGR = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->window, GCFillStyle, &_hoops_RGPPGR);

	_hoops_RGPPGR.stipple = _hoops_RRRPC->stipples[0];
	_hoops_RRRPC->_hoops_AHPPGR = XCreateGC (_hoops_RRRPC->display, _hoops_RRRPC->window, GCFillStyle | GCStipple, &_hoops_RGPPGR);

	if (_hoops_RRRPC->visual->c_class == PseudoColor ||
		_hoops_RRRPC->visual->c_class == StaticColor ||
		_hoops_RRRPC->visual->c_class == GrayScale) {

		unsigned long alter *_hoops_RRPHGR;

		/*
		 *		_hoops_SPCAR _hoops_IIGR _hoops_SCGH _hoops_PSHA _hoops_HRGR "_hoops_SCGR _hoops_PHI _hoops_IIGR _hoops_PSHA" +
		 *		"_hoops_SCGR _hoops_SRS _hoops_HAIR" + "_hoops_PHI _hoops_IIGR _hoops_PSHA _hoops_IGI _hoops_IH _hoops_CIPCA"
		 *		_hoops_PGAP _hoops_GGR _hoops_RH _hoops_AGIR _hoops_IIGR _hoops_ARPHGR _hoops_PPR _hoops_PRPHGR _hoops_SGAPC _hoops_HRGR
		 *		_hoops_HPGR _hoops_ICRP "2".
		 */
		_hoops_RRRPC->_hoops_GAPPGR =
				(int)(dc->current._hoops_AAPSR + dc->current._hoops_APASR + 2);
		ALLOC_ARRAY (_hoops_RRRPC->_hoops_SRPPGR, _hoops_RRRPC->_hoops_GAPPGR, unsigned long);
		_hoops_RRPHGR = _hoops_RRRPC->_hoops_SRPPGR + _hoops_RRRPC->_hoops_GAPPGR;
		do
			*--_hoops_RRPHGR = _hoops_AHAPGR;
		_hoops_RGGA (_hoops_RRPHGR == _hoops_RRRPC->_hoops_SRPPGR);
	}

	/* _hoops_RAP _hoops_GH _hoops_GHGPR-_hoops_RHGPR _hoops_RPP _hoops_HGRC. */
	if (dc->options._hoops_SRRRR && _hoops_RRRPC->_hoops_SPGHGR &&
		(_hoops_RRRPC->driver_type == _hoops_HRPHGR || _hoops_RRRPC->driver_type == X11_ONLY)) {
		/* _hoops_GISA _hoops_RH _hoops_GPAAC _hoops_GAPGGR-_hoops_PSCA _hoops_IH _hoops_GHGA _hoops_GHGPR-_hoops_RHGPR.		 */
		_hoops_CPAPGR ("X11 Multi-buffering", _hoops_RRRPC);
		if (XmbufCreateBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window, 2,
				MultibufferUpdateActionUntouched,
				MultibufferUpdateHintFrequent,
				_hoops_RRRPC->_hoops_HCSPGR) == 2) {

				_hoops_RRRPC->_hoops_ICSPGR = 1;
				_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_HCSPGR[_hoops_RRRPC->_hoops_ICSPGR];
				_hoops_RRRPC->_hoops_PCSPGR = true;
				_hoops_RRRPC->_hoops_PSAPGR = false;
				return (long)_hoops_RRRPC->window;
		}
		else {
			if (!dc->options._hoops_SRRRR || _hoops_RRRPC->driver_type != X11_ONLY) {
				_hoops_CPAPGR ("Could not create X11 Multi-Buffers", _hoops_RRRPC);
				HE_ERROR (HEC_X11_DRIVER, HES_CREATE_MULTIBUFFER_FAILED,
												  "X11 Driver: Could not create 2 X11 Multibuffers");
				HD_Kill_Driver (dc);
			}
			else {
				/* _hoops_SGP _hoops_IRPHGR _hoops_SRSH _hoops_IH _hoops_RHGC _hoops_PPCIP */
				_hoops_RRRPC->_hoops_SPGHGR = false;
				dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
				/* _hoops_RRGR _hoops_CRPHGR _hoops_HPP _hoops_RH _hoops_HSPR "_hoops_RPP" _hoops_GRS _hoops_SHH _hoops_SRPHGR */
			}
		}
	}
	if (dc->options._hoops_SRRRR &&
		!_hoops_RRRPC->_hoops_SPGHGR &&
		_hoops_RRRPC->driver_type == X11_ONLY) {

		/* _hoops_GISA _hoops_RH _hoops_GPAAC _hoops_RSAPGR _hoops_IH _hoops_GHGA _hoops_GHGPR-_hoops_RHGPR. */
		_hoops_CPAPGR ("X11 Pixmap double-buffering", _hoops_RRRPC);
		_hoops_RRRPC->_hoops_CCSPGR = XCreatePixmap (
			_hoops_RRRPC->display,
			_hoops_RRRPC->window,
			_hoops_RRRPC->window_width,
			_hoops_RRRPC->window_height,
			_hoops_RRRPC->depth);

		_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_CCSPGR;
		_hoops_RRRPC->_hoops_PCSPGR = false;
		_hoops_RRRPC->_hoops_PSAPGR = true;
	}
	else {
		_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->window;
		_hoops_RRRPC->_hoops_PCSPGR = false;
		_hoops_RRRPC->_hoops_PSAPGR = false;
	}

	return (POINTER_SIZED_INT)_hoops_RRRPC->window;
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GAPHGR _hoops_RH _hoops_GPAAC _hoops_HAICP.
 */
local void _hoops_ASCSP (
	Display_Context const	*dc) {
	X11Data alter				*_hoops_RRRPC = X11D(dc);

	HI_Copy_Name_To_Chars ((_hoops_HCRPR alter *)&dc->options._hoops_IAPIR, _hoops_RRRPC->_hoops_IAPIR);
	_hoops_HPRPR (" ", _hoops_RRRPC->_hoops_IAPIR); /* _hoops_GHSGR _hoops_IRS _hoops_GRAA-_hoops_RHPA _hoops_CRSAI */
	XStoreName (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_RRRPC->_hoops_IAPIR);
	XFlush (_hoops_RRRPC->display);
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_HICRH _hoops_RH _hoops_GPAAC _hoops_HAICP.
 */
local void _hoops_RSCSP (
	Display_Context const	*dc) {
	X11Data alter				*_hoops_RRRPC = X11D(dc);
	XSizeHints					_hoops_PCSPC;
	int							_hoops_IPCRH, _hoops_CPCRH;
	unsigned int				_hoops_PSCIP, _hoops_ASCIP;

	if (dc->options._hoops_GCHSR != 0 || dc->options._hoops_ISPRP != 0) {
		/*
		 * _hoops_IPSP _hoops_HRGR _hoops_HGSAR _hoops_IH _hoops_PHSPR _hoops_RAPHGR _hoops_SSHRH _hoops_IH
		 * _hoops_SGH _hoops_RPPS _hoops_PPR _hoops_GAPGH _hoops_GGRRR _hoops_HRGR _hoops_CHHH _hoops_IH _hoops_SGH _hoops_RPPS _hoops_RCC
		 * _hoops_HIS _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_SGH _hoops_IH _hoops_RGR _hoops_PCPH _hoops_GGR _hoops_SGH _hoops_RPPS _hoops_RCC.
		 */
		return;
	}

	/* _hoops_SICR _hoops_PCRR */
	_hoops_GASPGR (dc, &_hoops_IPCRH, &_hoops_CPCRH, &_hoops_ASCIP, &_hoops_PSCIP);

#ifdef _hoops_HPAPGR
	fprintf (stderr, "X11 Sequence: resize outer window (%d x %d) @ (%d, %d) %p\n",
					 _hoops_ASCIP, _hoops_PSCIP, _hoops_IPCRH, _hoops_CPCRH, (void*)_hoops_RRRPC);
#endif

	/* _hoops_IRHH _hoops_RCRR _hoops_SSHGR _hoops_CHR _hoops_GGR _hoops_RGAS */
	XSync (_hoops_RRRPC->display, False);
	check_events (dc);

	/* _hoops_IRHH _hoops_RCRR _hoops_RCPGR _hoops_PCRR _hoops_CHR _hoops_GGR _hoops_RGAS */
	_hoops_RASPGR (_hoops_RRRPC,
		&_hoops_RRRPC->window_x, &_hoops_RRRPC->window_y,
		&_hoops_RRRPC->window_width, &_hoops_RRRPC->window_height);

	XSync (_hoops_RRRPC->display, False);
	check_events (dc);

	if (_hoops_RRRPC->window_x != _hoops_IPCRH ||
		_hoops_RRRPC->window_y != _hoops_CPCRH ||
		_hoops_RRRPC->window_width != _hoops_ASCIP ||
		_hoops_RRRPC->window_height != _hoops_PSCIP) {
		if (_hoops_RRRPC->_hoops_APHPGR == _hoops_AAPHGR || _hoops_RRRPC->_hoops_APHPGR == _hoops_PAPHGR) {
			/*
			 * _hoops_PS _hoops_RRP _hoops_IS _hoops_AA _hoops_RGR _hoops_IH _hoops_IASPC 9.03 _hoops_RSHAC _hoops_PGGA _hoops_SSIA _hoops_HS
			 * _hoops_HGAS _hoops_RH _hoops_HGPC _hoops_ASCA _hoops_AGPGC
			 */
			_hoops_IPCRH -= _hoops_RRRPC->_hoops_PGRHGR;
			_hoops_CPCRH -= _hoops_RRRPC->_hoops_HGRHGR;
		}
		XMoveResizeWindow (_hoops_RRRPC->display, _hoops_RRRPC->window, _hoops_IPCRH, _hoops_CPCRH,
										   _hoops_ASCIP, _hoops_PSCIP);

		/* _hoops_AAPP _hoops_SGS _hoops_RH _hoops_RPPS _hoops_PPARI _hoops_CGH _hoops_IHIS _hoops_RH _hoops_RPPS (_hoops_CPCIP?) */
		_hoops_PCSPC.x = _hoops_IPCRH;
		_hoops_PCSPC.y = _hoops_CPCRH;
		_hoops_PCSPC.width = _hoops_ASCIP;
		_hoops_PCSPC.height = _hoops_PSCIP;
		_hoops_PCSPC.flags = USPosition | USSize;
		XSetNormalHints (_hoops_RRRPC->display, _hoops_RRRPC->window, &_hoops_PCSPC);

		_hoops_IHAHGR (dc);
		XSync (_hoops_RRRPC->display, False);				/* _hoops_IRHH _hoops_RCRR */
	}

	if (_hoops_RRRPC->_hoops_PCSPGR) {
		XmbufDestroyBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window);
		if (XmbufCreateBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window, 2,
								MultibufferUpdateActionUntouched,
								MultibufferUpdateHintFrequent,
								_hoops_RRRPC->_hoops_HCSPGR) != 2) {
			_hoops_CPAPGR ("Could not create X11 Multi-Buffers", _hoops_RRRPC);
			HE_ERROR (HEC_X11_DRIVER, HES_CREATE_MULTIBUFFER_FAILED,
							  "X11 Driver: Could not create 2 X11 Multibuffers");
			HD_Kill_Driver (dc);
		}
		_hoops_RRRPC->_hoops_ICSPGR = 1;
		_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_HCSPGR[_hoops_RRRPC->_hoops_ICSPGR];
	}
	else if (_hoops_RRRPC->_hoops_CCSPGR) {
		XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CCSPGR);
		_hoops_RRRPC->_hoops_CCSPGR = (Pixmap)0;
		_hoops_RRRPC->_hoops_CCSPGR = XCreatePixmap (_hoops_RRRPC->display, _hoops_RRRPC->window,
										_hoops_RRRPC->window_width, _hoops_RRRPC->window_height,
										_hoops_RRRPC->depth);
		_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_CCSPGR;
	}
	XSync (_hoops_RRRPC->display, False);

	_hoops_RRRPC->yfudge = dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom;
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GHGHR _hoops_RH _hoops_GPAAC _hoops_RPPS _hoops_IH _hoops_HSCI _hoops_HIS _hoops_SR _hoops_PAH _hoops_RPRS _hoops_SCH _hoops_PAR _hoops_ARP _hoops_RH _hoops_RPPS
 *		_hoops_RARP _hoops_GGR _hoops_RH _hoops_GPAAC _hoops_SCHGR _hoops_PIH _hoops_HRPR _hoops_IS _hoops_AHHR _hoops_GGR _hoops_RH _hoops_SIRHGR
 *		_hoops_AGIR.  _hoops_APSHR _hoops_RH _hoops_PSHA _hoops_IGI _hoops_GGR _hoops_RH _hoops_HGIR _hoops_PPR _hoops_RH _hoops_HGIR _hoops_RPP
 *		_hoops_IRPR
 */
local void free_outer_window (
	Display_Context const	*dc) {
	X11Data alter				*_hoops_RRRPC = X11D(dc);
	int							_hoops_CAPPGR;

	_hoops_CPAPGR ("free outer window", _hoops_RRRPC);

/* _hoops_GHAII: _hoops_HGI _hoops_HRGR _hoops_RHPH _hoops_IS _hoops_AA _hoops_ARI
		_hoops_RPP (!_hoops_CSPH->_hoops_AAP._hoops_HAPHGR)
				_hoops_IAPHGR (_hoops_APAPC, (_hoops_AAHAGR)_hoops_HPGSC);
*/

	/* _hoops_APSHR _hoops_RH _hoops_GPAAC _hoops_GAPGGR-_hoops_PSCA */
	if (_hoops_RRRPC->_hoops_PCSPGR) {
		XmbufDestroyBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window);
		_hoops_RRRPC->_hoops_PCSPGR = false;
	}

	/* _hoops_APSHR _hoops_RH _hoops_GPAAC _hoops_RSAPGR _hoops_IGI _hoops_IH _hoops_GHGPR-_hoops_RHGPR */
	if (_hoops_RRRPC->_hoops_CCSPGR) {
		XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CCSPGR);
		_hoops_RRRPC->_hoops_CCSPGR = (Pixmap)0;
	}

	if (_hoops_RRRPC->_hoops_CHPPGR != null) {
		_hoops_RRRPC->_hoops_CHPPGR->data = null;
		XDestroyImage (_hoops_RRRPC->_hoops_CHPPGR);
		_hoops_RRRPC->_hoops_CHPPGR = null;
	}

	if (_hoops_RRRPC->driver_type != _hoops_PCGHGR) {
		/* _hoops_APSHR _hoops_RH _hoops_SGPHGR'_hoops_GRI */
		XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AAPPGR);
		XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PPPPGR);
		XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_ISHPGR);
		XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_PHPPGR);
		XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GRPHGR);
		XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CHHPGR);
		XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_AHPPGR);

		_hoops_RRRPC->_hoops_AAPPGR  = (GC)0;
		_hoops_RRRPC->_hoops_PPPPGR  = (GC)0;
		_hoops_RRRPC->_hoops_ISHPGR  = (GC)0;
		_hoops_RRRPC->_hoops_PHPPGR = (GC)0;
		_hoops_RRRPC->_hoops_GRPHGR  = (GC)0;
		_hoops_RRRPC->_hoops_CHHPGR  = (GC)0;
		_hoops_RRRPC->_hoops_AHPPGR = (GC)0;
	}

	if (_hoops_RRRPC->_hoops_HISPGR) {

		if (dc->options._hoops_RCHSR == 0 &&
			_hoops_RRRPC->_hoops_GPIHP != _hoops_RRRPC->_hoops_IAIPGR) {
#ifdef X11R3
			if (_hoops_RRRPC->_hoops_SAIPGR)
					XUninstallColormap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP);
#endif
			XFreeColormap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GPIHP);
			_hoops_RRRPC->_hoops_GPIHP = (Colormap)0;
		}
		else if (_hoops_RRRPC->visual->c_class == PseudoColor) {
			/*
			 *		_hoops_CAPHGR _hoops_SGS _hoops_RH _hoops_SCIA 2 _hoops_PSHA _hoops_CHR _hoops_IGI _hoops_IH _hoops_IIPGR
			 *		_hoops_PPR _hoops_PSP _hoops_SAPHGR() _hoops_AASA _hoops_SSCP _hoops_RPII _hoops_IIAC _hoops_IS
			 *		_hoops_CCPP _hoops_AGCR _hoops_PSHA _hoops_HIS _hoops_SSIA _hoops_AA _hoops_HAR _hoops_RRP _hoops_IS _hoops_SHH _hoops_HGGPR
			 *		_hoops_AIH _hoops_GPPHGR().
			 */
			for (_hoops_CAPPGR = _hoops_RRRPC->_hoops_GAPPGR - 3; _hoops_CAPPGR >= 0; _hoops_CAPPGR--) {
				if (_hoops_RRRPC->_hoops_SRPPGR[_hoops_CAPPGR] != _hoops_AHAPGR) {

					XFreeColors (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IAIPGR,
							&_hoops_RRRPC->_hoops_SRPPGR[_hoops_CAPPGR], 1, 0L);
					/* _hoops_APAPC->_hoops_RPPHGR[_hoops_APPHGR] = _hoops_PPPHGR; */
				}
			}
		}

		if (_hoops_RRRPC->_hoops_SRPPGR)
				FREE_ARRAY (_hoops_RRRPC->_hoops_SRPPGR, _hoops_RRRPC->_hoops_GAPPGR, unsigned long);
	}

	if (dc->options._hoops_GCHSR == 0 && dc->options._hoops_ISPRP == 0)
		_hoops_RRRPC->_hoops_ASAHGR = true;
	else {
		if (!dc->options._hoops_CRSSP)
			XSelectInput (_hoops_RRRPC->display, _hoops_RRRPC->window, (Mask)False);
		_hoops_RRRPC->window = (X_Window)0;
	}
}



/****************************************************************
 ****************************************************************
								  _hoops_GRGGR _hoops_HAICR _hoops_APCAR _hoops_RAIGR _hoops_SAAAR _hoops_HRAIA	_hoops_IHRPR _hoops_GHCR _hoops_IHRPR _hoops_ISAII _hoops_HRAIA
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GHRAA _hoops_RH _hoops_PAAP _hoops_RCAS.
 */
local void init_update (
	Display_Context const	*dc) {
	X11Data alter				*_hoops_RRRPC = X11D(dc);

	_hoops_CPAPGR ("init update", _hoops_RRRPC);

	if (!BIT(dc->flags, _hoops_SAISR))
		return;

	/*
	 *		_hoops_ARGH _hoops_IH _hoops_HPPHGR-_hoops_PAAP _hoops_IPPHGR
	 *		(_hoops_GACC _hoops_CPHR _hoops_GGR _hoops_CPPHGR)
	 */
	_hoops_RRRPC->_hoops_IPSPGR = false;

	/*
	 *		_hoops_IPCP _hoops_HSPR _hoops_AASA _hoops_IS _hoops_SPPHGR() _hoops_HRGR _hoops_IIAC _hoops_HIS _hoops_SGS _hoops_IRISR _hoops_CGPR _hoops_IGI
	 *		_hoops_CCA _hoops_GHPHGR _hoops_GRS _hoops_CIAH _hoops_PAAP _hoops_RH _hoops_RPPS _hoops_IH _hoops_IGRSC
	 *		_hoops_SSHGR.
	 */
	if (dc->options._hoops_GCHSR != 0 || dc->options._hoops_ISPRP != 0)
		XSync (_hoops_RRRPC->display, False);

	check_events (dc);

	if ((dc->options._hoops_GCHSR || dc->options._hoops_ISPRP) && _hoops_RRRPC->_hoops_CCRHGR) {
		_hoops_CPAPGR ("request resize for initial use-window", _hoops_RRRPC);
		_hoops_RRRPC->_hoops_CCRHGR = false;

		/* _hoops_HGCR _hoops_RGCI _hoops_PCIRA (_hoops_AGSIP) */
		if (!dc->options._hoops_CRSSP)
			_hoops_PRSPGR (_hoops_RRRPC, StructureNotifyMask);

		/* _hoops_HGCR _hoops_RGCI _hoops_CPAP _hoops_PPR _hoops_CRGS _hoops_CHARP */
		_hoops_RASPGR (_hoops_RRRPC, &_hoops_RRRPC->window_x, &_hoops_RRRPC->window_y,
							   &_hoops_RRRPC->window_width, &_hoops_RRRPC->window_height);

		((Display_Context alter *)dc)->options._hoops_RASSP = true;
		((Display_Context alter *)dc)->options._hoops_AASSP = true;
		((Display_Context alter *)dc)->options._hoops_PASSP = true;
		HD_Resize_Subscreen (dc, true,
							 _hoops_RRRPC->window_x, _hoops_RRRPC->window_x + _hoops_RRRPC->window_width - 1,
							 dc->_hoops_PGCC._hoops_PRPSR.y -
							 (_hoops_RRRPC->window_y + _hoops_RRRPC->window_height),
							 dc->_hoops_PGCC._hoops_PRPSR.y - 1 - _hoops_RRRPC->window_y);

		if (_hoops_RRRPC->_hoops_PCSPGR) {

			XmbufDestroyBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window);

			if (XmbufCreateBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window, 2,
								MultibufferUpdateActionUntouched,
								MultibufferUpdateHintFrequent,
								_hoops_RRRPC->_hoops_HCSPGR) != 2) {

				HE_ERROR (HEC_X11_DRIVER, HES_CREATE_MULTIBUFFER_FAILED,
						  "X11 Driver: Could not create 2 X11 Multibuffers");

				HD_Kill_Driver(dc);
			}

			_hoops_RRRPC->_hoops_ICSPGR = 1;
			_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_HCSPGR[_hoops_RRRPC->_hoops_ICSPGR];
		}
		else if (_hoops_RRRPC->_hoops_CCSPGR) {

			XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CCSPGR);
			_hoops_RRRPC->_hoops_CCSPGR = (Pixmap)0;
			_hoops_RRRPC->_hoops_CCSPGR = XCreatePixmap (_hoops_RRRPC->display,
													_hoops_RRRPC->window,
													_hoops_RRRPC->window_width,
													_hoops_RRRPC->window_height,
													_hoops_RRRPC->depth);
			_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_CCSPGR;
		}

	}
	else
	if (dc->options._hoops_CRSSP) {
		int				x, y;
		unsigned int	width, height;

		_hoops_CPAPGR ("check if the window is resize in disable_all_input mode", _hoops_RRRPC);
		_hoops_RRRPC->_hoops_CCRHGR = false;

		/* _hoops_HGCR _hoops_RGCI _hoops_CPAP _hoops_PPR _hoops_CRGS _hoops_CHARP */
		_hoops_RASPGR (_hoops_RRRPC, &x, &y, &width, &height);

		if (x != _hoops_RRRPC->window_x || y != _hoops_RRRPC->window_y ||
			height != _hoops_RRRPC->window_height || width != _hoops_RRRPC->window_width) {

			_hoops_RRRPC->window_x = x;
			_hoops_RRRPC->window_y = y;
			_hoops_RRRPC->window_height = height;
			_hoops_RRRPC->window_width = width;

			HD_Resize_Subscreen (dc, true,
					_hoops_RRRPC->window_x, _hoops_RRRPC->window_x + _hoops_RRRPC->window_width - 1,
					dc->_hoops_PGCC._hoops_PRPSR.y - (_hoops_RRRPC->window_y + _hoops_RRRPC->window_height),
					dc->_hoops_PGCC._hoops_PRPSR.y - 1 - _hoops_RRRPC->window_y);

			if (_hoops_RRRPC->_hoops_PCSPGR) {

				XmbufDestroyBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window);

				if (XmbufCreateBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window, 2,
									MultibufferUpdateActionUntouched,
									MultibufferUpdateHintFrequent,
									_hoops_RRRPC->_hoops_HCSPGR) != 2) {

					HE_ERROR (HEC_X11_DRIVER, HES_CREATE_MULTIBUFFER_FAILED,
							  "X11 Driver: Could not create 2 X11 Multibuffers");

					HD_Kill_Driver(dc);
				}

				_hoops_RRRPC->_hoops_ICSPGR = 1;
				_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_HCSPGR[_hoops_RRRPC->_hoops_ICSPGR];
			}
			else if (_hoops_RRRPC->_hoops_CCSPGR) {

				XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CCSPGR);
				_hoops_RRRPC->_hoops_CCSPGR = (Pixmap)0;
				_hoops_RRRPC->_hoops_CCSPGR = XCreatePixmap (_hoops_RRRPC->display,
														_hoops_RRRPC->window,
														_hoops_RRRPC->window_width,
														_hoops_RRRPC->window_height,
														_hoops_RRRPC->depth);
				_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_CCSPGR;
			}
		}

		/*_hoops_RRAI _hoops_IS _hoops_PCCS _hoops_IRS _hoops_RHPHGR _hoops_ARSAR _hoops_APHSR _hoops_RPPS*/
		if (_hoops_RRRPC->driver_type == _hoops_PPAPC) {
			if (_hoops_RRRPC->_hoops_PHAPC)
				XResizeWindow(_hoops_RRRPC->display,_hoops_RRRPC->_hoops_RHSPC,
							_hoops_RRRPC->window_width,_hoops_RRRPC->window_height);
		}
	}
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_SIPR _hoops_SCGR _hoops_HPHS _hoops_AHCA _hoops_RH _hoops_GPAAC _hoops_RPPS.
 */
local void get_current_info (
		Display_Context alter		*dc) {
		X11Data alter				*_hoops_RRRPC = X11D(dc);
		int							x, y;
		unsigned int				width, height;

		_hoops_CPAPGR ("get current info", _hoops_RRRPC);

		/* _hoops_GPAAC _hoops_RGAR _hoops_AHPHGR "_hoops_RPASR" _hoops_IHGS _hoops_AHHR. */
		dc->current._hoops_APASR = 0;

		if (dc->options._hoops_GCHSR != 0 || dc->options._hoops_ISPRP != 0) {
			dc->options._hoops_RASSP = true;
			dc->options._hoops_AASSP = true;
			dc->options._hoops_PASSP = true;
			if (_hoops_RRRPC->driver_type != _hoops_PPAPC)
				dc->options._hoops_HPHRP = false;
		}
		else {
			/* _hoops_GPAAC _hoops_GCA _hoops_SGS "_hoops_HGPC" _hoops_PPR "_hoops_PHPHGR" _hoops_CHR _hoops_SHR _hoops_GIRP. */
			dc->options.border = dc->options._hoops_HRSSP;

			if (dc->options._hoops_HRSSP) {
					if (BIT (dc->options._hoops_IRARR, _hoops_HRAPGR))
							fprintf (stderr,
									 "X11 Window Manager: Left, Right, and Bottom Border = %d, Control Area = %d\n",
									 _hoops_RRRPC->_hoops_PGRHGR,
									 _hoops_RRRPC->_hoops_HGRHGR);
					HD_Allow_For_Border (dc,
										 _hoops_RRRPC->_hoops_PGRHGR,
										 _hoops_RRRPC->_hoops_PGRHGR,
										 _hoops_RRRPC->_hoops_PGRHGR,
										 _hoops_RRRPC->_hoops_HGRHGR);
			}
		}

		if (_hoops_RRRPC->display != 0 && _hoops_RRRPC->window != 0) {
				/* _hoops_IRHH _hoops_RCRR _hoops_SSHGR _hoops_CHR _hoops_GGR _hoops_RGAS */
				XSync (_hoops_RRRPC->display, False);
				if (check_events (dc))
						_hoops_RASPGR (_hoops_RRRPC, &x, &y, &width, &height);
				else {
						x = _hoops_RRRPC->window_x;
						y = _hoops_RRRPC->window_y;
						width = _hoops_RRRPC->window_width;
						height = _hoops_RRRPC->window_height;
				}

				dc->current.extent.left = (float)x;
				dc->current.extent.right = (float)x + width - 1;
				dc->current.extent.bottom =
										 (float)dc->_hoops_PGCC._hoops_PRPSR.y - (y + (int)height);
				dc->current.extent.top =
										 (float)dc->_hoops_PGCC._hoops_PRPSR.y - 1 - y;

				dc->current.extent.left -= (float)dc->current.border.left;
				dc->current.extent.right += (float)dc->current.border.right;
				dc->current.extent.bottom -= (float)dc->current.border.bottom;
				dc->current.extent.top += (float)dc->current.border.top;
		}

}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_GHRAA _hoops_RH _hoops_ASCA _hoops_IIGR _hoops_RH _hoops_RPISR.
 */
local void init_picture (
		Net_Rendition const & nr) {
		Display_Context const		*dc = nr->_hoops_SRA;
		X11Data alter				*_hoops_RRRPC = X11D(dc);

		_hoops_CPAPGR ("init picture", _hoops_RRRPC);

		/* _hoops_HHSA _hoops_HHPHGR _hoops_SICAR _hoops_IS _hoops_GSSGS _hoops_GH */
		_hoops_RRRPC->_hoops_SAICC = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HPPPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HSHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_SHHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_GAHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HAHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_CSHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_GPHPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_HHPPGR = (_hoops_GARRR)0;
		_hoops_RRRPC->_hoops_GIHPGR = (_hoops_GARRR)0;

		_hoops_RRRPC->yfudge = dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom;
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_RAGHR _hoops_RH _hoops_ASCA _hoops_IIGR _hoops_RH _hoops_RPISR.
 */
local void finish_picture (
		Net_Rendition const & nr,
		bool										swap_buffers) {
		Display_Context const		*dc = nr->_hoops_SRA;
		X11Data alter							*_hoops_RRRPC = X11D(dc);

		_hoops_CPAPGR ("finish picture", _hoops_RRRPC);

		if (_hoops_RRRPC->_hoops_APHPGR == _hoops_PPHPGR)
				/*
				 *		_hoops_HPSHR _hoops_ICAPR, _hoops_PCCP _hoops_ICPIP _hoops_SGS _hoops_SRIPR _hoops_RHSP _hoops_PCCP _hoops_PAAP _hoops_RPGGI
				 *		_hoops_HIRGR _hoops_RH _hoops_ACHGR _hoops_HCISR _hoops_RHASR _hoops_IS _hoops_HGCR *_hoops_CISS*.  _hoops_PHGP _hoops_SR
				 *		_hoops_IRHH _hoops_RCRR _hoops_IS _hoops_ISPR _hoops_IH _hoops_IHPHGR _hoops_ARPP _hoops_RGSHA _hoops_IAGA _hoops_ISSC _hoops_IS
				 *		_hoops_RH _hoops_AAPA _hoops_PAPA.  _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_HPIH _hoops_ICPIP, _hoops_RGR _hoops_GRS _hoops_IRHH
				 *		_hoops_RCRR _hoops_SGS "_hoops_CHPHGR" *_hoops_PIHAA* _hoops_CRGR _hoops_RH _hoops_ICPIP _hoops_CCAC _hoops_PGAP
				 *		_hoops_HRGR "_hoops_GGR _hoops_GCRPA".
				 */
				check_events (dc);

		if (_hoops_RRRPC->_hoops_PCSPGR && swap_buffers) {
				_hoops_CPAPGR ("Swapping X11 Multi-buffers", _hoops_RRRPC);
				XmbufDisplayBuffers (_hoops_RRRPC->display, 1, (Multibuffer*)&_hoops_RRRPC->_hoops_SRASH, 0, 0);
				_hoops_RRRPC->_hoops_ICSPGR = 1 - _hoops_RRRPC->_hoops_ICSPGR;
				_hoops_RRRPC->_hoops_SRASH = _hoops_RRRPC->_hoops_HCSPGR[_hoops_RRRPC->_hoops_ICSPGR];
		}
		else if (_hoops_RRRPC->_hoops_PSAPGR && !_hoops_IACI(dc)) {
				XGCValues				_hoops_RGPPGR;

				_hoops_CPAPGR ("Copying X11 double-buffer Pixmap", _hoops_RRRPC);
				_hoops_RGPPGR.foreground = (unsigned long)AllPlanes;
				XChangeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_GRPHGR, GCForeground, &_hoops_RGPPGR);
				XCopyArea (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CCSPGR, _hoops_RRRPC->window,
							_hoops_RRRPC->_hoops_GRPHGR, _hoops_RRRPC->_hoops_HSAPGR,
							_hoops_RRRPC->yfudge - _hoops_RRRPC->_hoops_SSAPGR,
							_hoops_RRRPC->_hoops_ISAPGR - _hoops_RRRPC->_hoops_HSAPGR + 1,
							_hoops_RRRPC->_hoops_SSAPGR - _hoops_RRRPC->_hoops_CSAPGR + 1,
							_hoops_RRRPC->_hoops_HSAPGR, _hoops_RRRPC->yfudge - _hoops_RRRPC->_hoops_SSAPGR);

				/* _hoops_GHRAA _hoops_RH _hoops_CIHH _hoops_PCSRR _hoops_IH _hoops_SPS _hoops_GHIR */
				_hoops_RRRPC->_hoops_HSAPGR = _hoops_IICIA;
				_hoops_RRRPC->_hoops_ISAPGR = -1;
				_hoops_RRRPC->_hoops_CSAPGR = _hoops_IICIA;
				_hoops_RRRPC->_hoops_SSAPGR = -1;
		}

#		ifdef AIX_SYSTEM
				/*
				 *		_hoops_GCCRR _hoops_RH _hoops_ICAPR _hoops_SGPSI _hoops_RIP _hoops_IH _hoops_IIIGC _hoops_GPP _hoops_GPAAC.		 _hoops_AIHH _hoops_RH _hoops_SRPHR
				 *		_hoops_GGR _hoops_RIIRH _hoops_IH _hoops_RH _hoops_RGSR _hoops_IIGR _hoops_RH _hoops_SGPSI _hoops_RIP _hoops_IH _hoops_GPAAC
				 *		_hoops_ICPIP _hoops_SSHGR _hoops_GGR _hoops_GCRPA.
				 */
				if (!_hoops_IACI(dc))
						_hoops_RRRPC->_hoops_RCSPGR = false;
#		endif /* _hoops_ICAPR */
}



/*
 *		** _hoops_SRAC **
 *
 *		_hoops_RAGHR _hoops_RH _hoops_PAAP _hoops_RCAS.
 */
local void finish_update (
		Display_Context const		*dc) {
		X11Data alter				*_hoops_RRRPC = X11D(dc);

		_hoops_CPAPGR ("finish update", _hoops_RRRPC);

		if (_hoops_RRRPC->_hoops_ASAHGR &&
				dc->options._hoops_GCHSR == 0 &&
				dc->options._hoops_ISPRP == 0 &&
				_hoops_RRRPC->window != (X_Window)0) {

#				ifdef _hoops_ICIGI
						XJp_end (_hoops_RRRPC->_hoops_HHAHGR, _hoops_RRRPC->window);
						XJp_close (_hoops_RRRPC->_hoops_HHAHGR);
#				endif /* _hoops_ARSPGR */

				if (_hoops_RRRPC->_hoops_PCSPGR) {
						XmbufDestroyBuffers (_hoops_RRRPC->display, _hoops_RRRPC->window);
						_hoops_RRRPC->_hoops_PCSPGR = false;
				}

				if (_hoops_RRRPC->_hoops_CCSPGR) {
						XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_CCSPGR);
						_hoops_RRRPC->_hoops_CCSPGR = (Pixmap)0;
				}

				if (_hoops_RRRPC->bitmap != 0) {
						XFreePixmap (_hoops_RRRPC->display, _hoops_RRRPC->bitmap);
						_hoops_RRRPC->bitmap = 0;
						FREE_ARRAY (_hoops_RRRPC->_hoops_SIRRC,
									_hoops_RRRPC->_hoops_PSHPGR * _hoops_RRRPC->_hoops_PSHPGR / 8, char);
						_hoops_RRRPC->_hoops_SIRRC = null;
						_hoops_RRRPC->_hoops_PSHPGR = 0;
				}

				if (_hoops_RRRPC->_hoops_IHHPGR != null) {
						XFreeGC (_hoops_RRRPC->display, _hoops_RRRPC->_hoops_IHHPGR);
						_hoops_RRRPC->_hoops_IHHPGR = null;
				}

				XDestroyWindow (_hoops_RRRPC->display, _hoops_RRRPC->window);
				_hoops_RRRPC->window = (X_Window)0;
				_hoops_RRRPC->_hoops_ASAHGR = false;
				XFlush (_hoops_RRRPC->display);
		}
		else {
				if ((_hoops_RRRPC->window != (X_Window)0) &&
						(dc->options._hoops_GCHSR == 0) &&
						(dc->options._hoops_ISPRP == 0) &&
						((_hoops_RRRPC->_hoops_ICRHGR != dc->options._hoops_AASSP) ||
						(_hoops_RRRPC->_hoops_HCRHGR != dc->options._hoops_PASSP))) {
						_hoops_IHAHGR (dc);
				}

						XFlush (_hoops_RRRPC->display);

				_hoops_RRRPC->_hoops_IPSPGR = false;
		}
}



/****************************************************************
 ****************************************************************
								_hoops_RAIGR _hoops_IHRPR _hoops_SAAAR _hoops_GHAP _hoops_RGGIR _hoops_PGGIR		   _hoops_SAAAR _hoops_RAIGR _hoops_IHAC _hoops_ISAII _hoops_HRAIA
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_SRAC _hoops_CHASR **
 *
 *		_hoops_IPCP _hoops_PCPH _hoops_IS _hoops_CISA _hoops_GGR _hoops_RH _hoops_RHPP _hoops_ACPH _hoops_GASR _hoops_SICAR
 */
local void _hoops_RSCSR (
		_hoops_APARR alter &		_hoops_RRCI) {

		_hoops_RRCI->start_device										= start_device;
		_hoops_RRCI->stop_device											= stop_device;
		_hoops_RRCI->get_physical_info							= get_physical_info;
		_hoops_RRCI->get_current_info							= get_current_info;
		_hoops_RRCI->init_update											= init_update;
		_hoops_RRCI->finish_update										= finish_update;
		_hoops_RRCI->init_picture										= init_picture;
		_hoops_RRCI->finish_picture										= finish_picture;
/* _hoops_HHHA _hoops_HIIC _hoops_GGR _hoops_HSPR _hoops_CHAAR _hoops_SHPHGR _hoops_ASRHR _hoops_AHCA _hoops_SHGGP
   _hoops_CSSC _hoops_GIPHGR _hoops_HII _hoops_RH _hoops_RGSC _hoops_SGS _hoops_SR'_hoops_RISP _hoops_HGAS _hoops_RH _hoops_CSPH _hoops_ACRGI _hoops_HII _hoops_RCIC
   _hoops_IS _hoops_GCC _hoops_GGR _hoops_ISCP _hoops_RIPHGR _hoops_API */
		_hoops_RRCI->get_outer_window							= (_hoops_RGCSP)get_outer_window;
		_hoops_RRCI->free_outer_window							= free_outer_window;
		_hoops_RRCI->_hoops_RSCSP							= _hoops_RSCSP;
		_hoops_RRCI->_hoops_ASCSP						= _hoops_ASCSP;
		_hoops_RRCI->draw_dc_colorized_face						= draw_dc_colorized_face;
		_hoops_RRCI->draw_dc_colorized_polytriangle				= draw_dc_colorized_polytriangle;
		_hoops_RRCI->draw_dc_ellipse								= draw_dc_ellipse;
		_hoops_RRCI->_hoops_SCISR						= _hoops_SCISR;
		_hoops_RRCI->draw_dc_polyline							= draw_dc_polyline;
		_hoops_RRCI->draw_dc_face								= draw_dc_face;
		_hoops_RRCI->draw_dc_polytriangle						= draw_dc_polytriangle;
		_hoops_RRCI->_hoops_RPCGA								= _hoops_RPCGA;
		_hoops_RRCI->draw_dc_rectangle							= draw_dc_rectangle;
		_hoops_RRCI->draw_dc_polydot								= draw_dc_polydot;
		_hoops_RRCI->draw_dc_text								= draw_dc_text;
		_hoops_RRCI->_hoops_SRCSR									= _hoops_SRCSR;
		_hoops_RRCI->_hoops_CCCGA							= _hoops_CCCGA;
		_hoops_RRCI->_hoops_GSCGA						= _hoops_GSCGA;
		_hoops_RRCI->_hoops_CCCSR						= _hoops_CCCSR;
		_hoops_RRCI->_hoops_PSCGA					= _hoops_PSCGA;
		_hoops_RRCI->draw_overlay_list							= draw_overlay_list;
		_hoops_RRCI->_hoops_SCPGR							= _hoops_SCPGR;
		_hoops_RRCI->_hoops_HSCSP							= _hoops_HSCSP;
		_hoops_RRCI->_hoops_ISCSP							= _hoops_ISCSP;
		_hoops_RRCI->find_all_fonts								= find_all_fonts;
		_hoops_RRCI->_hoops_CACSR							= _hoops_CACSR;
		_hoops_RRCI->_hoops_AACSR								= _hoops_AACSR;
		_hoops_RRCI->load_font									= load_font;
		_hoops_RRCI->unload_font									= unload_font;
		_hoops_RRCI->measure_char								= measure_char;
		_hoops_RRCI->snapshot									= snapshot;
		_hoops_RRCI->_hoops_RGSSP							= _hoops_RGSSP;
}



/****************************************************************
 ****************************************************************
								_hoops_APCAR _hoops_AHGPH _hoops_GHAP _hoops_RRGGR _hoops_HRAIA _hoops_AHGPH		   _hoops_IHRPR _hoops_RGGIR _hoops_PGGIR _hoops_PGGIR _hoops_HRAIA _hoops_IHRPR _hoops_SAAAR _hoops_GHAP _hoops_RGGIR _hoops_PGGIR
 ****************************************************************
 ****************************************************************/

/*
 *		** _hoops_AIPHGR **
 *
 *		_hoops_IPCP _hoops_PCPH _hoops_IS _hoops_SPGCA _hoops_RH _hoops_RHPP _hoops_IS _hoops_RH _hoops_IRISR _hoops_HCISR _hoops_HHCAC _hoops_SICAR.
 */
extern "C" bool HC_CDECL HD_X11_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}

/****************************************************************
 ****************************************************************
 ****************************************************************
 ****************************************************************/
/* _hoops_IH _hoops_SPAHGR _hoops_GCGH */

#ifdef _hoops_CISPGR

#define _hoops_PIPHGR				6


struct _hoops_HIPHGR {
  int min;
  int _hoops_RPIS;
};

static XDevice *_hoops_AIAHGR = NULL;
static _hoops_HIPHGR _hoops_IIPHGR[_hoops_PIPHGR];
static int _hoops_CIPHGR = 0;

/* _hoops_SIPHGR _hoops_IGIPR 0 _hoops_HRGR _hoops_PCCP _hoops_CHHH _hoops_PGRRR _hoops_GPRR _hoops_IH _hoops_SPCR _hoops_CPIRH
   _hoops_SAIHH _hoops_SSHGR. */
static int _hoops_HIAHGR = 0;
static int _hoops_CIAHGR = 0;
static int _hoops_RCAHGR = 0;
static int _hoops_PCAHGR = 0;
static int _hoops_ICAHGR = 0;


static void _hoops_GHAHGR(Display *display) {
  static int _hoops_GCPHGR = 0;
  XExtensionVersion *version;
  XDeviceInfoPtr _hoops_RCPHGR, device;
  XAnyClassPtr _hoops_RGCIH;
  XButtonInfoPtr b;
  XValuatorInfoPtr v;
  XAxisInfoPtr a;
  int _hoops_ACPHGR, _hoops_PCPHGR, _hoops_HCPHGR;
  int i, j, k;


  if (_hoops_GCPHGR)
		return;
  _hoops_GCPHGR = 1;

  version = XGetExtensionVersion(display, "XInputExtension");
  if (version == NULL || ((int) version) == _hoops_ICPHGR)
		return;

  XFree(version);
  _hoops_RCPHGR = XListInputDevices(display, &_hoops_ACPHGR);
  if (_hoops_RCPHGR) {
		for (i = 0; i < _hoops_ACPHGR; i++) {
		  /* _hoops_ASIGA _hoops_ASC _hoops_CHR _hoops_IPCGC _hoops_RPPCR _hoops_IH _hoops_AGCR _hoops_AGSHA;
				 _hoops_GIASI, _hoops_PSP _hoops_RIRA _hoops_HPRGR _hoops_HICP _hoops_IH _hoops_HPRGR
				 _hoops_CSSC _hoops_IIGR _hoops_SPCR _hoops_CIIA _hoops_SAIHH _hoops_AGSHA. */

		  device = &_hoops_RCPHGR[i];
		  _hoops_RGCIH = (XAnyClassPtr) device->_hoops_CCPHGR;

		  if (! _hoops_AIAHGR && !strcmp(device->name, "spaceball")) {
				v = NULL;
				b = NULL;
				for (j = 0; j < device->_hoops_SCPHGR; j++) {
				  switch (_hoops_RGCIH->c_class) {
				  case _hoops_GSPHGR:
						b = (XButtonInfoPtr) _hoops_RGCIH;
						_hoops_PCPHGR = b->_hoops_RSPHGR;
						break;
				  case _hoops_ASPHGR:
						v = (XValuatorInfoPtr) _hoops_RGCIH;
						/* _hoops_GCAAI _hoops_ISPR: _hoops_HPGR _hoops_CHGC 6 _hoops_PSPHGR? */
						if (v->_hoops_HSPHGR < _hoops_PIPHGR)
						  goto _hoops_ISPHGR;
						a = (XAxisInfoPtr) ((char *) v + sizeof(XValuatorInfo));
						for (k = 0; k < _hoops_PIPHGR; k++, a++) {
						  _hoops_IIPHGR[k].min = a->_hoops_CSPHGR;
						  _hoops_IIPHGR[k]._hoops_RPIS = a->_hoops_SSPHGR - a->_hoops_CSPHGR;
						}
						break;
				  }
				  _hoops_RGCIH = (XAnyClassPtr) ((char *) _hoops_RGCIH + _hoops_RGCIH->length);
				}
				if (v) {
				  _hoops_CPAPGR("Opening spaceball device", _hoops_RRRPC);
				  _hoops_AIAHGR = XOpenDevice(display, device->id);
				  if (_hoops_AIAHGR)
						_hoops_CIPHGR = _hoops_PCPHGR;
				}
		  _hoops_ISPHGR:;
		  }
		  XFreeDeviceList(_hoops_RCPHGR);
		}
  }
}
#endif /* _hoops_CCAHGR */


#ifdef _hoops_CISPGR
static int _hoops_SISPGR(XEvent *_hoops_GSSPC, X11_Event_Info *event) {

  if (_hoops_AIAHGR)
		{
		  char event_string[256];

		  if (_hoops_GSSPC->type == _hoops_HIAHGR)
				{
				  XDeviceMotionEvent *_hoops_GGHHGR = (XDeviceMotionEvent *) _hoops_GSSPC;
				  if (_hoops_GGHHGR->_hoops_RGHHGR == _hoops_AIAHGR->_hoops_AGHHGR)
						{
						  /* _hoops_ASIGA _hoops_HR _hoops_SGS _hoops_GC _hoops_PGHHGR _hoops_HGHHGR _hoops_SSHGR _hoops_RCPS _hoops_GGR _hoops_GAR
								 _hoops_HCR _hoops_RH _hoops_SRS 6 _hoops_HGCHA.	_hoops_HR _hoops_SRS 3 _hoops_HGCHA _hoops_CHR _hoops_SPRGGR
								 _hoops_GCCIC; _hoops_GIAP 3 _hoops_HGCHA _hoops_CHR _hoops_SPRGGR _hoops_CSCHA. */
						  if (_hoops_GGHHGR->_hoops_IGHHGR == 0 && _hoops_GGHHGR->_hoops_CGHHGR == 6)
								{
								  sprintf(event_string,"(%d,%d,%d,%d,%d,%d)",
												  _hoops_GGHHGR->_hoops_SGHHGR[0],
												  _hoops_GGHHGR->_hoops_SGHHGR[1],
												  _hoops_GGHHGR->_hoops_SGHHGR[2],
												  _hoops_GGHHGR->_hoops_SGHHGR[3],
												  _hoops_GGHHGR->_hoops_SGHHGR[4],
												  _hoops_GGHHGR->_hoops_SGHHGR[5]);
								  HI_Queue_Special_Event (null, "spaceball", event_string);
								}
						}
				  return 1;
				}

		  else if (_hoops_GSSPC->type == _hoops_CIAHGR)
				{
				  XDeviceButtonEvent *_hoops_GRHHGR = (XDeviceButtonEvent *) _hoops_GSSPC;
				  sprintf(event_string,"%d", _hoops_GRHHGR->button);
				  HI_Queue_Special_Event (null, "spacebutton", event_string);
				  return 1;
				}
#if 0  /* _hoops_HAR _hoops_APCRR _hoops_SSCHA/ _hoops_SIAHGR */
		  else if (_hoops_GSSPC->type == _hoops_RCAHGR)
				{
				  return 1;
				}
		  else if (_hoops_GSSPC->type == _hoops_PCAHGR)
				{
				  return 1;
				}
		  else if (_hoops_GSSPC->type == _hoops_ICAHGR)
				{
				  return 1;
				}
#endif
		}
  return 0;
}
#endif /* _hoops_CCAHGR */


#endif /* _hoops_RRHHGR */

