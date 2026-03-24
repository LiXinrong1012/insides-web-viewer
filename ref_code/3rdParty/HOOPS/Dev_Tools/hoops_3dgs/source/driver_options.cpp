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
 * $Id: obf_tmp.txt 1.196 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "adt.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"




struct _hoops_SHCGH {
	int *		clear;
	int *		set;
	int			_hoops_GICGH, _hoops_RICGH;
};

local const _hoops_IGRCR _hoops_AICGH[] = {
	{_hoops_PRHRP,		_hoops_GRRCR ("off"), _hoops_RRRCR, 0, false},
	{_hoops_PRHRP,		_hoops_GRRCR ("no"), _hoops_RRRCR, 0, false},
	{_hoops_PRHRP,		_hoops_GRRCR ("false"), _hoops_RRRCR, 0, false},
	{_hoops_HRHRP,		_hoops_GRRCR ("on"), _hoops_RRRCR, 0, false},
	{_hoops_HRHRP,		_hoops_GRRCR ("yes"), _hoops_RRRCR, 0, false},
	{_hoops_HRHRP,		_hoops_GRRCR ("true"), _hoops_RRRCR, 0, false},
	{_hoops_IRHRP,	_hoops_GRRCR ("all"), _hoops_RRRCR, 0, false},
	{_hoops_IRHRP,	_hoops_GRRCR ("everything"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_PICGH = {
	_hoops_GGAPR (_hoops_AICGH),
	_hoops_AICGH,
};


local const _hoops_IGRCR _hoops_HICGH[] = {
	{_hoops_RSPRP,		_hoops_GRRCR ("default"), _hoops_RRRCR, 0, false},
	{_hoops_ASPRP,		_hoops_GRRCR ("off"), _hoops_RRRCR, 0, false},
	{_hoops_PSPRP,			_hoops_GRRCR ("on"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_IICGH = {
	_hoops_GGAPR (_hoops_HICGH),
	_hoops_HICGH,
};


local const _hoops_IGRCR _hoops_CICGH[] = {
	{_hoops_SCPRP,	_hoops_GRRCR ("unrestricted"), _hoops_RRRCR, 0, false},
	{_hoops_CCPRP,			_hoops_GRRCR ("on"), _hoops_RRRCR, 0, false},
	{_hoops_CCPRP,			_hoops_GRRCR ("yes"), _hoops_RRRCR, 0, false},
	{_hoops_CCPRP,			_hoops_GRRCR ("true"), _hoops_RRRCR, 0, false},
	{_hoops_ICPRP,			_hoops_GRRCR ("off"), _hoops_RRRCR, 0, false},
	{_hoops_ICPRP,			_hoops_GRRCR ("no"), _hoops_RRRCR, 0, false},
	{_hoops_ICPRP,			_hoops_GRRCR ("false"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_SICGH = {
	_hoops_GGAPR (_hoops_CICGH),
	_hoops_CICGH,
};



local const _hoops_IGRCR _hoops_GCCGH[] = {
	{_hoops_HGHRP,	_hoops_GRRCR ("environment"), _hoops_RRRCR, 0, false},
	{Drivo_Landscape_ON,			_hoops_GRRCR ("on"), _hoops_RRRCR, 0, false},
	{Drivo_Landscape_ON,			_hoops_GRRCR ("yes"), _hoops_RRRCR, 0, false},
	{Drivo_Landscape_ON,			_hoops_GRRCR ("true"), _hoops_RRRCR, 0, false},
	{_hoops_PGHRP,			_hoops_GRRCR ("off"), _hoops_RRRCR, 0, false},
	{_hoops_PGHRP,			_hoops_GRRCR ("no"), _hoops_RRRCR, 0, false},
	{_hoops_PGHRP,			_hoops_GRRCR ("false"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RCCGH = {
	_hoops_GGAPR (_hoops_GCCGH),
	_hoops_GCCGH,
};


local const _hoops_IGRCR _hoops_ACCGH[] = {
	{_hoops_GRHRP,		_hoops_GRRCR ("default"), _hoops_RRRCR, 0, false},
	{_hoops_CGHRP,			_hoops_GRRCR ("bitmap"), _hoops_RRRCR, 0, false},
	{_hoops_CGHRP,			_hoops_GRRCR ("bitmaps"), _hoops_RRRCR, 0, false},
	{_hoops_CGHRP,			_hoops_GRRCR ("raster"), _hoops_RRRCR, 0, false},
	{_hoops_CGHRP,			_hoops_GRRCR ("rasters"), _hoops_RRRCR, 0, false},
	{_hoops_SGHRP,		_hoops_GRRCR ("outline"), _hoops_RRRCR, 0, false},
	{_hoops_SGHRP,		_hoops_GRRCR ("outlines"), _hoops_RRRCR, 0, false},
	{_hoops_SGHRP,		_hoops_GRRCR ("vector"), _hoops_RRRCR, 0, false},
	{_hoops_SGHRP,		_hoops_GRRCR ("vectors"), _hoops_RRRCR, 0, false},
	{_hoops_SGHRP,		_hoops_GRRCR ("area"), _hoops_RRRCR, 0, false},
	{_hoops_SGHRP,		_hoops_GRRCR ("areas"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_PCCGH = {
	_hoops_GGAPR (_hoops_ACCGH),
	_hoops_ACCGH,
};


local const _hoops_IGRCR _hoops_HCCGH[] = {
	{_hoops_SRHRP,		_hoops_GRRCR ("default"), _hoops_RRRCR, 0, false},
	{_hoops_GAHRP,			_hoops_GRRCR ("xor"), _hoops_RRRCR, 0, false},
	{_hoops_RAHRP,		_hoops_GRRCR ("overlay"), _hoops_RRRCR, 0, false},
	{_hoops_RAHRP,		_hoops_GRRCR ("blt"), _hoops_RRRCR, 0, false},
	{_hoops_RAHRP,		_hoops_GRRCR ("blit"), _hoops_RRRCR, 0, false},
	{_hoops_PAHRP,		_hoops_GRRCR ("sprite"), _hoops_RRRCR, 0, false},
	{_hoops_PAHRP,		_hoops_GRRCR ("spriting"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_ICCGH = {
	_hoops_GGAPR (_hoops_HCCGH),
	_hoops_HCCGH,
};

local const _hoops_IGRCR _hoops_CCCGH[] = {
	{Drivo_VERTEX_SPOTLIGHT,		_hoops_GRRCR ("vertex"), _hoops_RRRCR, 0, false},
	{0,								_hoops_GRRCR ("pixel"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_SCCGH = {
	_hoops_GGAPR (_hoops_CCCGH),
	_hoops_CCCGH,
};


local const _hoops_IGRCR _hoops_GSCGH[] = {
	{_hoops_CAHRP,		_hoops_GRRCR ("software"), _hoops_RRRCR, 0, false},
	{_hoops_SAHRP,		_hoops_GRRCR ("hardware"), _hoops_RRRCR, 0, false},
	{_hoops_GPHRP,		_hoops_GRRCR ("image"), _hoops_RRRCR, 0, false},
	{_hoops_RPHRP,			_hoops_GRRCR ("opengl"), _hoops_RRRCR, 0, false},
	{_hoops_RPHRP,			_hoops_GRRCR ("ogl"), _hoops_RRRCR, 0, false},
	{_hoops_APHRP,		_hoops_GRRCR ("soft opengl"), _hoops_RRRCR, 0, false},
	{_hoops_APHRP,		_hoops_GRRCR ("soft ogl"), _hoops_RRRCR, 0, false},
	{_hoops_APHRP,		_hoops_GRRCR ("software opengl"), _hoops_RRRCR, 0, false},
	{_hoops_APHRP,		_hoops_GRRCR ("opengl software"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RSCGH = {
	_hoops_GGAPR (_hoops_GSCGH),
	_hoops_GSCGH,
};


local const _hoops_IGRCR _hoops_ASCGH[] = {
	{false,		_hoops_GRRCR (""),		_hoops_RRRCR, 0, false},
	{true,		_hoops_GRRCR ("%"),		_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_PSCGH = {
	_hoops_GGAPR (_hoops_ASCGH),		_hoops_ASCGH,
};

local const _hoops_IGRCR _hoops_HSCGH[] = {
	{_hoops_RIPRP,		_hoops_GRRCR ("fast"),		_hoops_RRRCR, 0, false},
	{_hoops_RIPRP,		_hoops_GRRCR ("fastest"),	_hoops_RRRCR, 0, false},
	{0,									_hoops_GRRCR ("nice"),		_hoops_RRRCR, 0, false},
	{0,									_hoops_GRRCR ("nicest"),	_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_ISCGH = {
	_hoops_GGAPR (_hoops_HSCGH),			_hoops_HSCGH,
};


local const _hoops_IGRCR _hoops_CSCGH[] = {
	{_hoops_AIPRP,		_hoops_GRRCR ("on"),		_hoops_RRRCR, 0, false},
	{0,									_hoops_GRRCR ("off"),		_hoops_RRRCR, 0, false},
	{_hoops_CPHRP,		_hoops_GRRCR ("tolerance"),	_hoops_SPPCR, 1, false},
	{_hoops_SPHRP,	_hoops_GRRCR ("heavy exterior"),	_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_SSCGH = {
	_hoops_GGAPR (_hoops_CSCGH),			_hoops_CSCGH,
};

local const _hoops_IGRCR _hoops_GGSGH[] = {
	{_hoops_IHHRP,			_hoops_GRRCR ("nice"),		_hoops_RRRCR, 0, false},
	{_hoops_IHHRP,			_hoops_GRRCR ("nicest"),	_hoops_RRRCR, 0, false},
	{_hoops_CHHRP,			_hoops_GRRCR ("fast"),		_hoops_RRRCR, 0, false},
	{_hoops_CHHRP,			_hoops_GRRCR ("fastest"),	_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_RGSGH = {
	_hoops_GGAPR (_hoops_GGSGH),		_hoops_GGSGH,
};

local const _hoops_IGRCR _hoops_AGSGH[] = {
	{_hoops_PIPRP,			_hoops_GRRCR ("on"),		_hoops_RRRCR, 0, false},
	{0,										_hoops_GRRCR ("off"),		_hoops_RRRCR, 0, false},
	{_hoops_HHHRP,		_hoops_GRRCR ("strength"), _hoops_SPPCR, 1, false},
	{_hoops_SHHRP,	_hoops_GRRCR ("quality"),	_hoops_GHAGA, 1, false, &_hoops_RGSGH},
};
local const _hoops_HPAGA _hoops_PGSGH = {
	_hoops_GGAPR (_hoops_AGSGH),			_hoops_AGSGH,
};


local const _hoops_IGRCR _hoops_HGSGH[] = {
	{_hoops_CGSH,				_hoops_GRRCR ("star"),		_hoops_RRRCR, 0, false},
	{_hoops_CIHRP,			_hoops_GRRCR ("radial"),	_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_IGSGH = {
	_hoops_GGAPR (_hoops_HGSGH),		_hoops_HGSGH,
};

local const _hoops_IGRCR _hoops_CGSGH[] = {
	{_hoops_HIPRP,						_hoops_GRRCR ("on"),		_hoops_RRRCR, 0, false},
	{0,									_hoops_GRRCR ("off"),		_hoops_RRRCR, 0, false},
	{_hoops_HIHRP,				_hoops_GRRCR ("strength"),	_hoops_SPPCR, 1, false},
	{_hoops_IIHRP,			_hoops_GRRCR ("blur"),		_hoops_APRCA, 1, false},
	{_hoops_SIHRP,				_hoops_GRRCR ("shape"),		_hoops_GHAGA, 1, false, &_hoops_IGSGH},
};
local const _hoops_HPAGA _hoops_SGSGH = {
	_hoops_GGAPR (_hoops_CGSGH),			_hoops_CGSGH,
};

local const _hoops_IGRCR _hoops_GRSGH[] = {
	{_hoops_IIPRP,			_hoops_GRRCR ("on"),		_hoops_RRRCR, 0, false},
	{0,								_hoops_GRRCR ("off"),		_hoops_RRRCR, 0, false},
	{_hoops_PCHRP,		_hoops_GRRCR ("near"),		_hoops_SPPCR, 1, false},
	{_hoops_HCHRP,		_hoops_GRRCR ("far"),		_hoops_SPPCR, 1, false},
	{_hoops_ICHRP,	_hoops_GRRCR ("strength"),	_hoops_SPPCR, 1, false},
};
local const _hoops_HPAGA _hoops_RRSGH = {
	_hoops_GGAPR (_hoops_GRSGH),	_hoops_GRSGH,
};


local const _hoops_IGRCR _hoops_ARSGH[] = {
	{_hoops_SSPRP,				_hoops_GRRCR ("default"),		_hoops_IRSAP, 1, false},
	{_hoops_SSPRP,				_hoops_GRRCR ("window"),		_hoops_IRSAP, 1, false},
	{_hoops_GGHRP,			_hoops_GRRCR ("image"),			_hoops_IRSAP, 1, false},
	{_hoops_GGHRP,			_hoops_GRRCR ("image key"),		_hoops_IRSAP, 1, false},
};
local const _hoops_HPAGA _hoops_PRSGH = {
	_hoops_GGAPR (_hoops_ARSGH),	_hoops_ARSGH,
};



#define	_hoops_HRSGH	(-1)
#define _hoops_IRSGH		(-2)

local const _hoops_IGRCR _hoops_CRSGH[] = {
	{(Integer32)_hoops_CAPRP,				_hoops_GRRCR ("backing store"),				_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_SAPRP,						_hoops_GRRCR ("border"),					_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_GPPRP,					_hoops_GRRCR ("control area"),				_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_ICARP,						_hoops_GRRCR ("debug"),						_hoops_APRCA, -999, true},
	{(Integer32)_hoops_HRSGH,					_hoops_GRRCR ("clear debug"),				_hoops_APRCA, -999, false},
	{(Integer32)_hoops_IRSGH,					_hoops_GRRCR ("set debug"),					_hoops_APRCA, -999, false},
	{(Integer32)_hoops_RPPRP,				_hoops_GRRCR ("double-buffering"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_RPPRP,				_hoops_GRRCR ("double buffering"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_SCARP,					_hoops_GRRCR ("first color"),				_hoops_APRCA, 1, true},
	{(Integer32)_hoops_GSARP,					_hoops_GRRCR ("fixed colors"),				_hoops_APRCA, -3, true},
	{(Integer32)_hoops_APPRP,		_hoops_GRRCR ("force black-and-white"), 	_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_APPRP,		_hoops_GRRCR ("force black and white"), 	_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_HHPRP,				_hoops_GRRCR ("force gray scale"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_HHPRP,				_hoops_GRRCR ("force grey scale"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_HHPRP,				_hoops_GRRCR ("force grayscale"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_HHPRP,				_hoops_GRRCR ("force greyscale"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_IHPRP,				_hoops_GRRCR ("display stats"),				_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_IHPRP,				_hoops_GRRCR ("display statistics"), 		_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_CHPRP,			_hoops_GRRCR ("display time stats"), 		_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_CHPRP,			_hoops_GRRCR ("display time statistics"),	_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_SHPRP,			_hoops_GRRCR ("display memory stats"),		_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_SHPRP,			_hoops_GRRCR ("display memory statistics"), _hoops_RRRCR, 0, true},
	{(Integer32)_hoops_PPPRP,				_hoops_GRRCR ("gamma correction"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_ASARP,				_hoops_GRRCR ("light scaling"),				_hoops_SPPCR, 1, true},
	{(Integer32)_hoops_HSARP,			_hoops_GRRCR ("locater transform"), 		_hoops_SPPCR, 6, true},
	{(Integer32)_hoops_ISARP,				_hoops_GRRCR ("number of colors"),			_hoops_APRCA, 1, true},
	{(Integer32)_hoops_CSARP,					_hoops_GRRCR ("pen speed"),					_hoops_SPPCR, 1, true},
	{(Integer32)_hoops_SSARP,				_hoops_GRRCR ("physical size"),				_hoops_SPPCR, 2, true},
	{(Integer32)_hoops_GGPRP,			_hoops_GRRCR ("selection proximity"),		_hoops_SPPCR, 1, true},
	{(Integer32)_hoops_GHPRP,				_hoops_GRRCR ("special events"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_RGPRP,					_hoops_GRRCR ("subscreen"),					_hoops_SPPCR, 4, true},
	{(Integer32)_hoops_HPPRP,			_hoops_GRRCR ("subscreen creating"),		_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_IPPRP,				_hoops_GRRCR ("subscreen moving"),			_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_CPPRP,			_hoops_GRRCR ("subscreen resizing"),		_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_SPPRP,			_hoops_GRRCR ("subscreen stretching"),		_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_AGPRP,						_hoops_GRRCR ("title"),						_hoops_PRRCR, -1, true},
	{(Integer32)_hoops_CRPRP,				_hoops_GRRCR ("fallback font"),				_hoops_PRRCR, -9999, true},
	{(Integer32)_hoops_CRPRP,				_hoops_GRRCR ("fallback fonts"),			_hoops_PRRCR, -9999, true},
	{(Integer32)_hoops_AAPRP,					_hoops_GRRCR ("font table"),	    		_hoops_PRRCR, -9999, true},
	{(Integer32)_hoops_IGPRP,				_hoops_GRRCR ("use window id"),				_hoops_HASAP,
																				1, true, &_hoops_PRSGH},
	{(Integer32)_hoops_CGPRP,				_hoops_GRRCR ("use window id2"),			_hoops_IRSAP, 1, true},
	{(Integer32)_hoops_CGPRP,				_hoops_GRRCR ("use window id 2"),			_hoops_IRSAP, 1, true},
	{(Integer32)_hoops_HGPRP,				_hoops_GRRCR ("use colormap id"),			_hoops_IRSAP, 1, true},
	{(Integer32)_hoops_PRPRP,			_hoops_GRRCR ("use clip override"), 		_hoops_IRSAP, 1, true},
	{(Integer32)_hoops_SGPRP,					_hoops_GRRCR ("write mask"),				_hoops_APRCA, 1, true},
	{(Integer32)_hoops_GRPRP,				_hoops_GRRCR ("output format"),				_hoops_PRRCR, -9999, true},
	{(Integer32)_hoops_RRPRP,			_hoops_GRRCR ("hardcopy resolution"),		_hoops_APRCA, 1, true},
	{(Integer32)_hoops_SIPRP,						_hoops_GRRCR ("isolated"),					_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_RHPRP,				_hoops_GRRCR ("stereo"),					_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_SRPRP,			_hoops_GRRCR ("anti-alias"),				_hoops_PRRCR, -1, true},
	{(Integer32)_hoops_SRPRP,			_hoops_GRRCR ("anti-aliasing"),				_hoops_PRRCR, -1, true},
	{(Integer32)_hoops_SRPRP,			_hoops_GRRCR ("anti alias"),				_hoops_PRRCR, -1, true},
	{(Integer32)_hoops_SRPRP,			_hoops_GRRCR ("anti aliasing"),				_hoops_PRRCR, -1, true},
	{(Integer32)_hoops_SRPRP,			_hoops_GRRCR ("antialias"),					_hoops_PRRCR, -1, true},
	{(Integer32)_hoops_SRPRP,			_hoops_GRRCR ("antialiasing"),				_hoops_PRRCR, -1, true},
	{(Integer32)_hoops_AHPRP,			_hoops_GRRCR ("stencil"),					_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_PHPRP,			_hoops_GRRCR ("absolute line weight"),		_hoops_RRRCR, 0, true},

	{(Integer32)_hoops_PSARP,			_hoops_GRRCR ("color consolidation"),		_hoops_CIGHA,
																				1, true, &_hoops_PSCGH},
	{(Integer32)_hoops_CCARP,				_hoops_GRRCR ("disable input"),				_hoops_GHAGA,
																				-1, true, &_hoops_PICGH},
	{(Integer32)_hoops_RSARP,		_hoops_GRRCR ("landscape orientation"),		_hoops_GHAGA,
																				-1, true, &_hoops_RCCGH},
	{(Integer32)_hoops_PGPRP,			_hoops_GRRCR ("update interrupts"),			_hoops_GHAGA,
																				-1, true, &_hoops_SICGH},
	{(Integer32)_hoops_ARPRP,				_hoops_GRRCR ("text preference"),			_hoops_GHAGA,
																				1, true, &_hoops_PCCGH},
	{(Integer32)_hoops_HRPRP,			_hoops_GRRCR ("quick moves preference"),	_hoops_GHAGA,
																				-5, true, &_hoops_ICCGH},
	{(Integer32)_hoops_HRPRP,			_hoops_GRRCR ("quickmoves preference"),		_hoops_GHAGA,
																				-5, true, &_hoops_ICCGH},
	{(Integer32)_hoops_HRPRP,			_hoops_GRRCR ("qmoves preference"),			_hoops_GHAGA,
																				-5, true, &_hoops_ICCGH},
	{(Integer32)_hoops_IRPRP,			_hoops_GRRCR ("shadow preference"),			_hoops_GHAGA,
																				1, true, &_hoops_RSCGH},
	{(Integer32)Drivo_VERTEX_SPOTLIGHT,				_hoops_GRRCR ("spotlight preference"),		_hoops_GHAGA,
																				1, false, &_hoops_SCCGH},
	{(Integer32)Drivo_VERTEX_SPOTLIGHT,				_hoops_GRRCR ("spotlight interpolation"),	_hoops_GHAGA,
																				1, false, &_hoops_SCCGH},

	{(Integer32)_hoops_GAPRP,					_hoops_GRRCR ("exit update"),				_hoops_PRRCR, 1, true},
	{(Integer32)_hoops_PAPRP,				_hoops_GRRCR ("exit update data"),			_hoops_PRRCR, 1, true},

	{(Integer32)_hoops_RAPRP,	_hoops_GRRCR ("display interrupted update"), _hoops_GHAGA,
																				1, true, &_hoops_IICGH},
	{(Integer32)_hoops_GIPRP,					_hoops_GRRCR("fullscreen"),					_hoops_RRRCR, 0, true},

	{(Integer32)_hoops_RIPRP,		_hoops_GRRCR ("marker drawing"),			_hoops_GHAGA,
																				1, false, &_hoops_ISCGH},
	{(Integer32)_hoops_AIPRP,		_hoops_GRRCR ("fast silhouette edges"),		_hoops_GHAGA,
																				-99, true, &_hoops_SSCGH},
	{(Integer32)_hoops_AIPRP,		_hoops_GRRCR ("fast silhouettes"),			_hoops_GHAGA,
																				-99, true, &_hoops_SSCGH},
	{(Integer32)_hoops_PIPRP,		_hoops_GRRCR ("ambient occlusion"),			_hoops_GHAGA,
																				-99, true, &_hoops_PGSGH},
	{(Integer32)_hoops_HIPRP,						_hoops_GRRCR ("bloom"),						_hoops_GHAGA,
																				-99, true, &_hoops_SGSGH},
	{(Integer32)_hoops_IIPRP,				_hoops_GRRCR ("depth of field"),			_hoops_GHAGA,
																				-99, true, &_hoops_RRSGH},

	{(Integer32)_hoops_CIPRP,					_hoops_GRRCR ("gpu resident"),				_hoops_RRSAP, 0, true},
};




local Attribute *_hoops_SRSGH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_GAPIR const *	_hoops_GASGH = (_hoops_GAPIR const *)_hoops_CPACR;
	_hoops_GAPIR alter *	_hoops_RASGH = (_hoops_GAPIR alter *)_hoops_SPACR;
	
	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_GASGH != null) {
		/* _hoops_IGPP _hoops_GGR _hoops_RH _hoops_AASGH _hoops_HSH _hoops_SGS _hoops_AAPR _hoops_HAR _hoops_PASGH _hoops_HPP _hoops_IRS _hoops_HASGH _hoops_PIRA. */

		_hoops_RASGH->_hoops_IAPRP |= (_hoops_GASGH->_hoops_IAPRP & ~_hoops_RASGH->_hoops_HAICA);
		_hoops_RASGH->_hoops_HAICA |= _hoops_GASGH->_hoops_HAICA;


		if (!BIT (_hoops_RASGH->_hoops_AHHRP.mask, _hoops_CPHRP)) {
			_hoops_RASGH->_hoops_AHHRP._hoops_GAHP = _hoops_GASGH->_hoops_AHHRP._hoops_GAHP;
		}
		_hoops_RASGH->_hoops_AHHRP.value |= (_hoops_GASGH->_hoops_AHHRP.value & ~_hoops_RASGH->_hoops_AHHRP.mask);
		_hoops_RASGH->_hoops_AHHRP.mask |= _hoops_GASGH->_hoops_AHHRP.mask;


		if (!BIT (_hoops_RASGH->_hoops_AIHRP.mask, _hoops_HHHRP)) {
			_hoops_RASGH->_hoops_AIHRP._hoops_GIGP = _hoops_GASGH->_hoops_AIHRP._hoops_GIGP;
		}
		_hoops_RASGH->_hoops_AIHRP.value |= (_hoops_GASGH->_hoops_AIHRP.value & ~_hoops_RASGH->_hoops_AIHRP.mask);
		_hoops_RASGH->_hoops_AIHRP.mask |= _hoops_GASGH->_hoops_AIHRP.mask;


		if (!BIT (_hoops_RASGH->_hoops_RGSH.mask, _hoops_HIHRP))
			_hoops_RASGH->_hoops_RGSH._hoops_SHGP = _hoops_GASGH->_hoops_RGSH._hoops_SHGP;
		if (!BIT (_hoops_RASGH->_hoops_RGSH.mask, _hoops_IIHRP))
			_hoops_RASGH->_hoops_RGSH._hoops_HGGGR = _hoops_GASGH->_hoops_RGSH._hoops_HGGGR;
		_hoops_RASGH->_hoops_RGSH.value |= (_hoops_GASGH->_hoops_RGSH.value & ~_hoops_RASGH->_hoops_RGSH.mask);
		_hoops_RASGH->_hoops_RGSH.mask |= _hoops_GASGH->_hoops_RGSH.mask;

		if (!BIT (_hoops_RASGH->_hoops_ASHRP.mask, _hoops_PCHRP))
			_hoops_RASGH->_hoops_ASHRP._hoops_GSHRP = _hoops_GASGH->_hoops_ASHRP._hoops_GSHRP;
		if (!BIT (_hoops_RASGH->_hoops_ASHRP.mask, _hoops_HCHRP))
			_hoops_RASGH->_hoops_ASHRP._hoops_RSHRP = _hoops_GASGH->_hoops_ASHRP._hoops_RSHRP;
		if (!BIT (_hoops_RASGH->_hoops_ASHRP.mask, _hoops_ICHRP))
			_hoops_RASGH->_hoops_ASHRP._hoops_SHGP = _hoops_GASGH->_hoops_ASHRP._hoops_SHGP;
		_hoops_RASGH->_hoops_ASHRP.value |= (_hoops_GASGH->_hoops_ASHRP.value & ~_hoops_RASGH->_hoops_ASHRP.mask);
		_hoops_RASGH->_hoops_ASHRP.mask |= _hoops_GASGH->_hoops_ASHRP.mask;


		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_ICARP)) {
			_hoops_RASGH->_hoops_APPIR = _hoops_GASGH->_hoops_APPIR;
			_hoops_RASGH->_hoops_RPPIR = _hoops_GASGH->_hoops_RPPIR;
			((_hoops_GAPIR alter *)_hoops_GASGH)->_hoops_RPPIR = null;		/* _hoops_SRAI _hoops_SCH */
			_hoops_RASGH->_hoops_IRARR = _hoops_GASGH->_hoops_IRARR;
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_SCARP))
			_hoops_RASGH->_hoops_APASR = _hoops_GASGH->_hoops_APASR;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_GSARP)) {
			_hoops_RASGH->_hoops_GCPRP[0] = _hoops_GASGH->_hoops_GCPRP[0];
			_hoops_RASGH->_hoops_GCPRP[1] = _hoops_GASGH->_hoops_GCPRP[1];
			_hoops_RASGH->_hoops_GCPRP[2] = _hoops_GASGH->_hoops_GCPRP[2];
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_ASARP))
			_hoops_RASGH->_hoops_RCPRP = _hoops_GASGH->_hoops_RCPRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_PSARP))
			_hoops_RASGH->_hoops_ACPRP = _hoops_GASGH->_hoops_ACPRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_HSARP)) {
			_hoops_RASGH->_hoops_PCPRP[0][0] = _hoops_GASGH->_hoops_PCPRP[0][0];
			_hoops_RASGH->_hoops_PCPRP[0][1] = _hoops_GASGH->_hoops_PCPRP[0][1];
			_hoops_RASGH->_hoops_PCPRP[1][0] = _hoops_GASGH->_hoops_PCPRP[1][0];
			_hoops_RASGH->_hoops_PCPRP[1][1] = _hoops_GASGH->_hoops_PCPRP[1][1];
			_hoops_RASGH->_hoops_PCPRP[2][0] = _hoops_GASGH->_hoops_PCPRP[2][0];
			_hoops_RASGH->_hoops_PCPRP[2][1] = _hoops_GASGH->_hoops_PCPRP[2][1];
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_ISARP))
			_hoops_RASGH->_hoops_AAPSR = _hoops_GASGH->_hoops_AAPSR;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_CSARP))
			_hoops_RASGH->_hoops_GSHSR = _hoops_GASGH->_hoops_GSHSR;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_SSARP)) {
			_hoops_RASGH->_hoops_SPHSR.x = _hoops_GASGH->_hoops_SPHSR.x;
			_hoops_RASGH->_hoops_SPHSR.y = _hoops_GASGH->_hoops_SPHSR.y;
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_GGPRP))
			_hoops_RASGH->_hoops_SHSHA = _hoops_GASGH->_hoops_SHSHA;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_RGPRP)) {
			_hoops_RASGH->_hoops_HCPRP = _hoops_GASGH->_hoops_HCPRP;
			_hoops_RASGH->_hoops_HPHRP = _hoops_GASGH->_hoops_HPHRP;
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_AGPRP))
			HI_Copy_Name (&_hoops_GASGH->_hoops_IAPIR, &_hoops_RASGH->_hoops_IAPIR);

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_SRPRP))
			_hoops_RASGH->_hoops_AIPGA = _hoops_GASGH->_hoops_AIPGA;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_CRPRP)) {
			/* _hoops_SRAI _hoops_RH _hoops_RHGS _hoops_HIGR */
			_hoops_RASGH->_hoops_SAPIR = _hoops_GASGH->_hoops_SAPIR;
			((_hoops_GAPIR alter *)_hoops_GASGH)->_hoops_SAPIR = null;
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_AAPRP)) {
			/* _hoops_SRAI _hoops_RH _hoops_RHGS _hoops_HIGR */
			_hoops_RASGH->_hoops_GPPIR = _hoops_GASGH->_hoops_GPPIR;
			((_hoops_GAPIR alter *)_hoops_GASGH)->_hoops_GPPIR = null;
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_GAPRP)) {
			_hoops_RASGH->_hoops_PPPIR = _hoops_GASGH->_hoops_PPPIR;
			if (_hoops_RASGH->_hoops_PPPIR != null)
				_hoops_PRRH (_hoops_RASGH->_hoops_PPPIR);
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_PAPRP))
			_hoops_RASGH->_hoops_HSHRP = _hoops_GASGH->_hoops_HSHRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_GRPRP))
			_hoops_RASGH->_hoops_HAPIR = HI_Copy_Name_List (_hoops_GASGH->_hoops_HAPIR);

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_CCARP))
			_hoops_RASGH->_hoops_CRHRP = _hoops_GASGH->_hoops_CRHRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_RSARP))
			_hoops_RASGH->_hoops_IGHRP = _hoops_GASGH->_hoops_IGHRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_ARPRP))
			_hoops_RASGH->_hoops_ARHRP = _hoops_GASGH->_hoops_ARHRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_HRPRP))
			_hoops_AIGA (_hoops_GASGH->_hoops_IAHRP, _hoops_HAHRP, int, _hoops_RASGH->_hoops_IAHRP);

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_IRPRP))
			_hoops_RASGH->_hoops_PPHRP = _hoops_GASGH->_hoops_PPHRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_RAPRP))
			_hoops_RASGH->_hoops_HSPRP = _hoops_GASGH->_hoops_HSPRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_PGPRP))
			_hoops_RASGH->_hoops_GSPRP = _hoops_GASGH->_hoops_GSPRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_HGPRP))
			_hoops_RASGH->_hoops_RCHSR = _hoops_GASGH->_hoops_RCHSR;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_IGPRP)) {
			_hoops_RASGH->_hoops_GCHSR = _hoops_GASGH->_hoops_GCHSR;
			_hoops_RASGH->_hoops_RGHRP = _hoops_GASGH->_hoops_RGHRP;
		}

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_CGPRP))
			_hoops_RASGH->_hoops_ISPRP = _hoops_GASGH->_hoops_ISPRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_PRPRP))
			_hoops_RASGH->_hoops_CSPRP = _hoops_GASGH->_hoops_CSPRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_SGPRP))
			_hoops_RASGH->_hoops_AGHRP = _hoops_GASGH->_hoops_AGHRP;

		if (!BIT (_hoops_RASGH->_hoops_IAICA, _hoops_RRPRP))
			_hoops_RASGH->_hoops_GHHSR = _hoops_GASGH->_hoops_GHHSR;


		_hoops_RASGH->_hoops_HCARP |= (_hoops_GASGH->_hoops_HCARP & ~_hoops_RASGH->_hoops_IAICA);
		_hoops_RASGH->_hoops_IAICA |= _hoops_GASGH->_hoops_IAICA;
	}

	if (_hoops_RASGH->_hoops_PSHRP != null) {
		_hoops_SHCGH *	_hoops_IASGH = (_hoops_SHCGH *)_hoops_RASGH->_hoops_PSHRP;

		if (_hoops_IASGH->_hoops_GICGH > 0) {
			_hoops_HSIAA (_hoops_RASGH->_hoops_RPPIR, _hoops_IASGH->clear,
				_hoops_AHIA (_hoops_IASGH->_hoops_GICGH, _hoops_RASGH->_hoops_APPIR) * sizeof (int));
		}

		if (_hoops_IASGH->_hoops_RICGH > 0) {
			if (_hoops_IASGH->_hoops_RICGH > _hoops_RASGH->_hoops_APPIR) {
				int *	_hoops_CASGH = _hoops_RASGH->_hoops_RPPIR;

				ZALLOC_ARRAY (_hoops_RASGH->_hoops_RPPIR, _hoops_IASGH->_hoops_RICGH, int);
				if (_hoops_RASGH->_hoops_APPIR > 0) {
					_hoops_AIGA (_hoops_CASGH, _hoops_RASGH->_hoops_APPIR, int, _hoops_RASGH->_hoops_RPPIR);
					FREE_ARRAY (_hoops_CASGH, _hoops_RASGH->_hoops_APPIR, int);
				}
				_hoops_RASGH->_hoops_APPIR = _hoops_IASGH->_hoops_RICGH;
			}
			_hoops_ISIAA (_hoops_RASGH->_hoops_RPPIR, _hoops_IASGH->set, _hoops_IASGH->_hoops_RICGH * sizeof(int));
		}

		_hoops_RASGH->_hoops_IAICA |= _hoops_ICARP;
		_hoops_RASGH->_hoops_HCARP |= _hoops_ICARP;

		if (_hoops_IASGH->_hoops_GICGH > 0)
			FREE_ARRAY (_hoops_IASGH->clear, _hoops_IASGH->_hoops_GICGH, int);
		if (_hoops_IASGH->_hoops_RICGH > 0)
			FREE_ARRAY (_hoops_IASGH->set, _hoops_IASGH->_hoops_RICGH, int);

		FREE (_hoops_IASGH, _hoops_SHCGH);

		_hoops_RASGH->_hoops_PSHRP = null;	/* _hoops_HAR _hoops_GCPRA */
	}

	return _hoops_RASGH;
}


local int _hoops_SASGH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const *			name)
{
	const char *_hoops_RPPA = name->text;
	int _hoops_HAGR;

	if (_hoops_SHPCR (_hoops_RPPA[0]) == 'o') {
		if (_hoops_SHPCR (_hoops_RPPA[1]) == 'f' &&
			_hoops_SHPCR (_hoops_RPPA[2]) == 'f')
			return 0;
		else if (_hoops_SHPCR (_hoops_RPPA[1]) == 'n')
			return -1;

		_hoops_PHPGR (HEC_DRIVER, HES_SYNTAX_ERROR, "syntax error in 'anti alias' driver option setting:", name->text);
		return 0;
	}
	else {
		HI_Scan_Integer (_hoops_RIGC, &_hoops_RPPA, _hoops_RPPA+name->length, &_hoops_HAGR);

		if (_hoops_RPPA == name->text || *_hoops_RPPA != '\0') {
			_hoops_PHPGR (HEC_DRIVER, HES_SYNTAX_ERROR, "syntax error in 'anti alias' driver option setting:", name->text);
			return 0;
		}

		return _hoops_HAGR;
	}
}


local _hoops_SRHSR system_default = _hoops_GRRCR("system default");
local _hoops_SRHSR sans_serif = _hoops_GRRCR ("sans serif");
local _hoops_SRHSR typewriter = _hoops_GRRCR ("typewriter");
local _hoops_SRHSR roman = _hoops_GRRCR ("roman");
local _hoops_SRHSR stroked = _hoops_GRRCR ("stroked");


local void _hoops_GPSGH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GAPIR *		_hoops_PAICA)
{
	UNREFERENCED(_hoops_RIGC);

	if (_hoops_PAICA->_hoops_SAPIR)
		HI_Free_Font_Names (_hoops_PAICA->_hoops_SAPIR);

	if (_hoops_PAICA->_hoops_GPPIR)
		HI_Free_Font_Names (_hoops_PAICA->_hoops_GPPIR);

	_hoops_RGAIR (_hoops_PAICA->_hoops_IAPIR);

	if (_hoops_PAICA->_hoops_HAPIR)
		HI_Free_Name_List(_hoops_PAICA->_hoops_HAPIR);

	if (_hoops_PAICA->_hoops_PPPIR)
		_hoops_HPRH (_hoops_PAICA->_hoops_PPPIR);

	if (_hoops_PAICA->_hoops_PSHRP != null) {
		_hoops_SHCGH *	_hoops_IASGH = (_hoops_SHCGH *)_hoops_PAICA->_hoops_PSHRP;

		if (_hoops_IASGH->_hoops_GICGH > 0)
			FREE_ARRAY (_hoops_IASGH->clear, _hoops_IASGH->_hoops_GICGH, int);
		if (_hoops_IASGH->_hoops_RICGH > 0)
			FREE_ARRAY (_hoops_IASGH->set, _hoops_IASGH->_hoops_RICGH, int);

		FREE (_hoops_IASGH, _hoops_SHCGH);
	}

}


local bool _hoops_RPSGH (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	_hoops_GAPIR &		_hoops_APHCR) 
{

	ZERO_STRUCT (&_hoops_APHCR, _hoops_GAPIR);
	_hoops_APHCR._hoops_HPHRP = true;
	_hoops_APHCR._hoops_GHHSR = 75;

	_hoops_HIACR (_hoops_AAPPP, _hoops_CRSGH);

	Option_Value *	option_list;
	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_AAPPP), &option_list, _hoops_SIACR)) 
		return false;

	
	_hoops_SHCGH *	_hoops_IASGH = null;
	
	Option_Value *	option;

	if ((option = option_list) != null) do {

		_hoops_PCARP	mask = option->type->id;

		if (mask == _hoops_HRSGH) {

			if (_hoops_IASGH == null)
				ZALLOC (_hoops_IASGH, _hoops_SHCGH);

			/* _hoops_PSSSR _hoops_IH _hoops_RRI _hoops_PSCR _hoops_SPR _hoops_ACISR? */
			if (_hoops_IASGH->clear != null) {
				FREE_ARRAY (_hoops_IASGH->clear, _hoops_IASGH->_hoops_GICGH, int);
				_hoops_IASGH->clear = null;
			}

			_hoops_IASGH->_hoops_GICGH = option->_hoops_AIPCR;
			if (_hoops_IASGH->_hoops_GICGH > 0) {
				ALLOC_ARRAY (_hoops_IASGH->clear, _hoops_IASGH->_hoops_GICGH, int);
				_hoops_AIGA (option->value._hoops_RIARA, _hoops_IASGH->_hoops_GICGH, int, _hoops_IASGH->clear);
			}
			_hoops_APHCR._hoops_PSHRP = _hoops_IASGH;
		}
		else if (mask == _hoops_IRSGH) {

			if (_hoops_IASGH == null)
				ZALLOC (_hoops_IASGH, _hoops_SHCGH);

			/* _hoops_PSSSR _hoops_IH _hoops_RRI _hoops_PSCR _hoops_SPR _hoops_ACISR? */
			if (_hoops_IASGH->set != null) {
				FREE_ARRAY (_hoops_IASGH->set, _hoops_IASGH->_hoops_RICGH, int);
				_hoops_IASGH->set = null;
			}

			_hoops_IASGH->_hoops_RICGH = option->_hoops_AIPCR;
			if (_hoops_IASGH->_hoops_RICGH > 0) {
				ALLOC_ARRAY (_hoops_IASGH->set, _hoops_IASGH->_hoops_RICGH, int);
				_hoops_AIGA (option->value._hoops_RIARA, _hoops_IASGH->_hoops_RICGH, int, _hoops_IASGH->set);
			}
			_hoops_APHCR._hoops_PSHRP = _hoops_IASGH;
		}
		else if (BIT (mask, _hoops_HAPRP)) {
			_hoops_APHCR._hoops_HAICA |= mask;
			_hoops_APHCR._hoops_IAPRP &= ~mask;
			if (option->_hoops_GCACR) {
				switch (mask) {
					case _hoops_AIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_AIPRP;
						_hoops_APHCR._hoops_AHHRP.mask |= _hoops_IPHRP;
						_hoops_APHCR._hoops_AHHRP.value &= ~_hoops_IPHRP;
					} break;
					case _hoops_PIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_PIPRP;
						_hoops_APHCR._hoops_AIHRP.mask |= _hoops_PHHRP;
						_hoops_APHCR._hoops_AIHRP.value &= ~_hoops_PHHRP;
					} break;
					case _hoops_HIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_HIPRP;
						_hoops_APHCR._hoops_RGSH.mask |= _hoops_PIHRP;
						_hoops_APHCR._hoops_RGSH.value &= ~_hoops_PIHRP;
					} break;
					case _hoops_IIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_IIPRP;
						_hoops_APHCR._hoops_ASHRP.mask |= _hoops_ACHRP;
						_hoops_APHCR._hoops_ASHRP.value &= ~_hoops_ACHRP;
					} break;
				}
			}
			else {
				switch (mask) {
					// _hoops_APSGH, _hoops_PPSGH
					// _hoops_HPSGH, _hoops_IPSGH, _hoops_CPSGH
					// _hoops_PPR _hoops_SPSGH _hoops_RRP _hoops_GRH _hoops_GHSGH _hoops_PGGA _hoops_PAII _hoops_RHSGH
					// _hoops_CCHGR _hoops_HRGR _hoops_IRS _hoops_AHSGH _hoops_GAPA _hoops_CPHP _hoops_RII _hoops_HSAR _hoops_SAHR "_hoops_GPP" _hoops_PAR "_hoops_PSAP".
					case Drivo_VERTEX_SPOTLIGHT: {
						_hoops_APHCR._hoops_IAPRP |= (int)option->value.option_list->type->id;
					} break;
					case _hoops_RIPRP: {
						_hoops_APHCR._hoops_IAPRP |= (int)option->value.option_list->type->id;
					} break;
					case _hoops_AIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_AIPRP;
						if (option->_hoops_AIPCR) {
							Option_Value *_hoops_PHSGH = option->value.option_list;
							do {
								if (_hoops_PHSGH->type->id == _hoops_AIPRP ||
									_hoops_PHSGH->type->id == 0) {
									_hoops_APHCR._hoops_AHHRP.mask |= _hoops_IPHRP;
									if (!_hoops_PHSGH->_hoops_GCACR && _hoops_PHSGH->type->id != 0)
										_hoops_APHCR._hoops_AHHRP.value |= _hoops_IPHRP;
								}
								else {
									_hoops_APHCR._hoops_AHHRP.mask |= _hoops_PHSGH->type->id;
									if (!_hoops_PHSGH->_hoops_GCACR) {
										_hoops_APHCR._hoops_AHHRP.value |= _hoops_PHSGH->type->id;
										switch (_hoops_PHSGH->type->id) {
											case _hoops_CPHRP:
												_hoops_APHCR._hoops_AHHRP._hoops_GAHP = _hoops_PHSGH->value._hoops_PIPCR[0];
												break;
											case _hoops_SPHRP:
												break;
										}
									}
								}
							} while ((_hoops_PHSGH = _hoops_PHSGH->next) != null);
						}
						else {
							_hoops_APHCR._hoops_AHHRP.mask |= _hoops_IPHRP;
							if (!option->_hoops_GCACR)
								_hoops_APHCR._hoops_AHHRP.value |= _hoops_IPHRP;
						}
					} break;
					case _hoops_PIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_PIPRP;
						if (option->_hoops_AIPCR) {
							Option_Value *_hoops_PHSGH = option->value.option_list;
							do {
								if (_hoops_PHSGH->type->id == _hoops_PIPRP ||
									_hoops_PHSGH->type->id == 0) {
									_hoops_APHCR._hoops_AIHRP.mask |= _hoops_PHHRP;
									if (!_hoops_PHSGH->_hoops_GCACR && _hoops_PHSGH->type->id != 0)
										_hoops_APHCR._hoops_AIHRP.value |= _hoops_PHHRP;
								}
								else {
									_hoops_APHCR._hoops_AIHRP.mask |= _hoops_PHSGH->type->id;
									if (!_hoops_PHSGH->_hoops_GCACR) {
										_hoops_APHCR._hoops_AIHRP.value |= _hoops_PHSGH->type->id;
										switch (_hoops_PHSGH->type->id) {
											case _hoops_HHHRP:
												_hoops_APHCR._hoops_AIHRP._hoops_GIGP = _hoops_PHSGH->value._hoops_PIPCR[0];
												break;
											case _hoops_SHHRP: {
												Option_Value *_hoops_HHSGH = _hoops_PHSGH->value.option_list;
												_hoops_APHCR._hoops_AIHRP.value &= ~_hoops_SHHRP;
												_hoops_APHCR._hoops_AIHRP.value |= _hoops_HHSGH->type->id;
											} break;
										}
									}
								}
							} while ((_hoops_PHSGH = _hoops_PHSGH->next) != null);
						}
						else {
							_hoops_APHCR._hoops_AIHRP.mask |= _hoops_PHHRP;
							if (!option->_hoops_GCACR)
								_hoops_APHCR._hoops_AIHRP.value |= _hoops_PHHRP;
						}
					} break;

					case _hoops_HIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_HIPRP;
						if (option->_hoops_AIPCR) {
							Option_Value *_hoops_PHSGH = option->value.option_list;
							do {
								if (_hoops_PHSGH->type->id == _hoops_HIPRP ||
									_hoops_PHSGH->type->id == 0) {
									_hoops_APHCR._hoops_RGSH.mask |= _hoops_PIHRP;
									if (!_hoops_PHSGH->_hoops_GCACR && _hoops_PHSGH->type->id != 0)
										_hoops_APHCR._hoops_RGSH.value |= _hoops_PIHRP;
								}
								else {
									_hoops_APHCR._hoops_RGSH.mask |= _hoops_PHSGH->type->id;
									if (!_hoops_PHSGH->_hoops_GCACR) {
										_hoops_APHCR._hoops_RGSH.value |= _hoops_PHSGH->type->id;
										switch (_hoops_PHSGH->type->id) {
											case _hoops_HIHRP:
												if (_hoops_PHSGH->value._hoops_PIPCR[0] > 10 ||
													_hoops_PHSGH->value._hoops_PIPCR[0] < 0) {
													HE_ERROR (HEC_DRIVER, HES_INVALID_RANGE,
														"Bloom 'strength' must be between 0 and 10");
													_hoops_APHCR._hoops_RGSH.mask &= _hoops_HIHRP;
												}
												else
													_hoops_APHCR._hoops_RGSH._hoops_SHGP = _hoops_PHSGH->value._hoops_PIPCR[0];
												break;
											case _hoops_IIHRP:
												if (_hoops_PHSGH->value._hoops_RIARA[0] > 8 ||
													_hoops_PHSGH->value._hoops_RIARA[0] < 1) {
													HE_ERROR (HEC_DRIVER, HES_INVALID_RANGE,
														"Bloom 'blur' must be between 1 and 8");
													_hoops_APHCR._hoops_RGSH.mask &= _hoops_IIHRP;
												}
												else
													_hoops_APHCR._hoops_RGSH._hoops_HGGGR = _hoops_PHSGH->value._hoops_RIARA[0];
												break;
											case _hoops_SIHRP: {
												Option_Value *_hoops_HHSGH = _hoops_PHSGH->value.option_list;
												_hoops_APHCR._hoops_RGSH.value &= ~_hoops_SIHRP;
												_hoops_APHCR._hoops_RGSH.value |= _hoops_HHSGH->type->id;
											} break;
										}
									}
								}
							} while ((_hoops_PHSGH = _hoops_PHSGH->next) != null);
						}
						else {
							_hoops_APHCR._hoops_RGSH.mask |= _hoops_PIHRP;
							if (!option->_hoops_GCACR)
								_hoops_APHCR._hoops_RGSH.value |= _hoops_PIHRP;
						}
					} break;

					case _hoops_IIPRP: {
						_hoops_APHCR._hoops_IAPRP |= _hoops_IIPRP;
						if (option->_hoops_AIPCR) {
							Option_Value *_hoops_PHSGH = option->value.option_list;
							do {
								if (_hoops_PHSGH->type->id == _hoops_IIPRP ||
									_hoops_PHSGH->type->id == 0) {
									_hoops_APHCR._hoops_ASHRP.mask |= _hoops_ACHRP;
									if (!_hoops_PHSGH->_hoops_GCACR && _hoops_PHSGH->type->id != 0)
										_hoops_APHCR._hoops_ASHRP.value |= _hoops_ACHRP;
								}
								else {
									_hoops_APHCR._hoops_ASHRP.mask |= _hoops_PHSGH->type->id;
									if (!_hoops_PHSGH->_hoops_GCACR) {
										_hoops_APHCR._hoops_ASHRP.value |= _hoops_PHSGH->type->id;
										switch (_hoops_PHSGH->type->id) {
											case _hoops_PCHRP:
												_hoops_APHCR._hoops_ASHRP._hoops_GSHRP= _hoops_PHSGH->value._hoops_PIPCR[0];
												break;

											case _hoops_HCHRP:
												_hoops_APHCR._hoops_ASHRP._hoops_RSHRP= _hoops_PHSGH->value._hoops_PIPCR[0];
												break;

											case _hoops_ICHRP:
												if (_hoops_PHSGH->value._hoops_PIPCR[0] > 10 ||
													_hoops_PHSGH->value._hoops_PIPCR[0] < 0) {
													HE_ERROR (HEC_DRIVER, HES_INVALID_RANGE,
														"Depth of field 'strength' must be between 0 and 10");
													_hoops_APHCR._hoops_ASHRP.mask &= _hoops_ICHRP;
												}
												else
													_hoops_APHCR._hoops_ASHRP._hoops_SHGP = _hoops_PHSGH->value._hoops_PIPCR[0];
												break;
										}
									}
								}
							} while ((_hoops_PHSGH = _hoops_PHSGH->next) != null);
						}
						else {
							_hoops_APHCR._hoops_ASHRP.mask |= _hoops_ACHRP;
							if (!option->_hoops_GCACR)
								_hoops_APHCR._hoops_ASHRP.value |= _hoops_ACHRP;
						}
					} break;

					default: {
						_hoops_APHCR._hoops_IAPRP |= mask;
					}
				}
			}
			/* _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_RH _hoops_CASH _hoops_IGRH _hoops_IH _hoops_IHSGH _hoops_PPR _hoops_CHSGH _hoops_SHSGH _hoops_SCAC _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH
			 * _hoops_SRCH _hoops_RCPP _hoops_GISGH _hoops_CGPR _hoops_SR _hoops_RPGP _hoops_IH _hoops_IGGA _hoops_SGI _hoops_GRP _hoops_RH _hoops_IRRC() _hoops_RIGR */
			_hoops_APHCR._hoops_HAICA &= ~_hoops_HAPRP;
			_hoops_APHCR._hoops_IAPRP  &= ~_hoops_HAPRP;
		}
		else {
			_hoops_APHCR._hoops_IAICA |= mask;
			if (option->_hoops_GCACR)
				_hoops_APHCR._hoops_HCARP &= ~mask;
			else
				_hoops_APHCR._hoops_HCARP |= mask;

			if (!option->_hoops_GCACR) switch (mask) {
			  case _hoops_ICARP: {
				  int				count;

				  /* _hoops_PSSSR _hoops_IH _hoops_RRI _hoops_PSCR _hoops_SPR _hoops_ACISR... */
				  if (_hoops_APHCR._hoops_RPPIR != null) {
					  FREE_ARRAY (_hoops_APHCR._hoops_RPPIR, _hoops_APHCR._hoops_APPIR, int);
					  _hoops_APHCR._hoops_RPPIR = null;
				  }

				  _hoops_APHCR._hoops_APPIR = count = option->_hoops_AIPCR;
				  if (count == 0)
					  _hoops_APHCR._hoops_IRARR = 0;
				  else {
					  ALLOC_ARRAY (_hoops_APHCR._hoops_RPPIR, count, int);
					  _hoops_AIGA (option->value._hoops_RIARA, count, int, _hoops_APHCR._hoops_RPPIR);
					  _hoops_APHCR._hoops_IRARR = _hoops_APHCR._hoops_RPPIR[0];
				  }
			  }	  break;

			  case _hoops_SCARP: {
				  _hoops_APHCR._hoops_APASR = option->value._hoops_RIARA[0];
				  if (_hoops_APHCR._hoops_APASR < 0) {
					  HE_ERROR (HEC_DRIVER, HES_BAD_FIRST_COLOR,"A 'first color' can't be negative");
					  goto FAILED;
				  }
			  }	  break;

			  case _hoops_GSARP: {
				  if (option->_hoops_AIPCR == 1) {
					  _hoops_APHCR._hoops_GCPRP[0] = option->value._hoops_RIARA[0];
					  _hoops_APHCR._hoops_GCPRP[1] = 0;
					  _hoops_APHCR._hoops_GCPRP[2] = 0;
					  if (_hoops_APHCR._hoops_GCPRP[0] < 8 && _hoops_APHCR._hoops_GCPRP[0] != 0) {
						  HE_ERROR2 (HEC_DRIVER, HES_BAD_FIXED_COLORS_SPEC,
									 "A single-valued specification of 'fixed colors'",
									 "must be at least 8 if not zero");
						  goto FAILED;
					  }
				  }
				  else if (option->_hoops_AIPCR == 3) {
					  _hoops_APHCR._hoops_GCPRP[0] = option->value._hoops_RIARA[0];
					  _hoops_APHCR._hoops_GCPRP[1] = option->value._hoops_RIARA[1];
					  _hoops_APHCR._hoops_GCPRP[2] = option->value._hoops_RIARA[2];
					  if (_hoops_APHCR._hoops_GCPRP[0] < 2 ||
						  _hoops_APHCR._hoops_GCPRP[1] < 2 ||
						  _hoops_APHCR._hoops_GCPRP[2] < 2) {
						  HE_ERROR2 (HEC_DRIVER, HES_BAD_FIXED_COLORS_SPEC,
									 "A multiple-valued specification of 'fixed colors'",
									"must be all at least 2");
						  goto FAILED;
					  }
				  }
				  else {
					  HE_ERROR (HEC_DRIVER, HES_BAD_FIXED_COLORS_SPEC,
						  "'Fixed colors' requires a single number, or a triplet of numbers");
					  goto FAILED;
				  }
			  }	  break;

			  case _hoops_ASARP: {
				  _hoops_APHCR._hoops_RCPRP = option->value._hoops_PIPCR[0];
			  }	  break;

			  case _hoops_PSARP: {
				  float	_hoops_RISGH = option->value._hoops_RRRHA[0].value;

				  if (_hoops_RISGH < 0.0f) {
					  _hoops_PHPGR (HEC_DRIVER, HES_BAD_COLOR_CONSOLIDATION,
								   "'Color consolidation' requires a number greater than one",
								   "or a non-negative percentage");
					  _hoops_APHCR._hoops_IAICA &= ~mask;
				  }
				  else {
					  if (option->value._hoops_RRRHA[0]._hoops_HHP) {
						  /* _hoops_CHIA _hoops_CCA % */
						  _hoops_APHCR._hoops_ACPRP = 0.01f * _hoops_RISGH;
					  }
					  else {
						  /* _hoops_CHIA _hoops_SSCHA/_hoops_GCSR _hoops_IRS % -- _hoops_IRHS _hoops_AISGH */
						  if (_hoops_RISGH < 1.0f) {
							  _hoops_PHPGR (HEC_DRIVER, HES_BAD_COLOR_CONSOLIDATION,
										   "'Color consolidation' requires a number greater than one",
										   "or a non-negative percentage");
							  _hoops_APHCR._hoops_IAICA &= ~mask;
						  }
						  else
							  _hoops_APHCR._hoops_ACPRP = 1.0f / _hoops_RISGH;
					  }
				  }
			  }	  break;

			  case _hoops_HSARP: {
				  _hoops_APHCR._hoops_PCPRP[0][0] = option->value._hoops_PIPCR[0];
				  _hoops_APHCR._hoops_PCPRP[0][1] = option->value._hoops_PIPCR[1];
				  _hoops_APHCR._hoops_PCPRP[1][0] = option->value._hoops_PIPCR[2];
				  _hoops_APHCR._hoops_PCPRP[1][1] = option->value._hoops_PIPCR[3];
				  _hoops_APHCR._hoops_PCPRP[2][0] = option->value._hoops_PIPCR[4];
				  _hoops_APHCR._hoops_PCPRP[2][1] = option->value._hoops_PIPCR[5];
			  }	  break;

			  case _hoops_ISARP: {
				  _hoops_APHCR._hoops_AAPSR = option->value._hoops_RIARA[0];

				  if (_hoops_APHCR._hoops_AAPSR < 8 &&
					  _hoops_APHCR._hoops_AAPSR != 0) {
					  HE_ERROR (HEC_DRIVER, HES_BAD_NUMBER_OF_COLORS,
						  "'Number of colors' must be at least 8 if not zero");
					  goto FAILED;
				  }
			  }	  break;

			  case _hoops_CSARP: {
				  _hoops_APHCR._hoops_GSHSR = option->value._hoops_PIPCR[0];

				  if (_hoops_APHCR._hoops_GSHSR <= 0.0f) {
					  HE_ERROR (HEC_DRIVER, HES_BAD_PEN_SPEED,"'Pen speed' must be positive");
					  goto FAILED;
				  }
			  }	  break;

			  case _hoops_SSARP: {
				  _hoops_APHCR._hoops_SPHSR.x = option->value._hoops_PIPCR[0];
				  _hoops_APHCR._hoops_SPHSR.y = option->value._hoops_PIPCR[1];

				  if (_hoops_APHCR._hoops_SPHSR.x <= 0.0f ||
					  _hoops_APHCR._hoops_SPHSR.y <= 0.0f) {
					  HE_ERROR (HEC_DRIVER, HES_BAD_PHYSICAL_SIZE,"'Physical size' must be positive");
					  goto FAILED;
				  }
			  }	  break;

			  case _hoops_GGPRP: {
				  _hoops_APHCR._hoops_SHSHA = option->value._hoops_PIPCR[0];

				  if (_hoops_APHCR._hoops_SHSHA < 0.0f) {
					  HE_ERROR (HEC_DRIVER, HES_BAD_SELECTION_PROXIMITY,"'Selection proximity' may not be negative");
					  goto FAILED;
				  }
			  }	  break;

			  case _hoops_RGPRP: {
				  _hoops_APHCR._hoops_HCPRP.left = option->value._hoops_PIPCR[0];
				  _hoops_APHCR._hoops_HCPRP.right = option->value._hoops_PIPCR[1];
				  _hoops_APHCR._hoops_HCPRP.bottom = option->value._hoops_PIPCR[2];
				  _hoops_APHCR._hoops_HCPRP.top = option->value._hoops_PIPCR[3];
			  }	  break;

			  case _hoops_AGPRP: {
				  if (option->_hoops_AIPCR == 1)
					HI_Copy_Name (&option->value._name[0], &_hoops_APHCR._hoops_IAPIR);
			  }	  break;

			  case _hoops_SRPRP: {
				  if (option->_hoops_AIPCR == 1) {
					  _hoops_APHCR._hoops_AIPGA = _hoops_SASGH(_hoops_RIGC, &option->value._name[0]);
				  }
				  else
					  _hoops_APHCR._hoops_AIPGA = -1;
			  }	  break;

			  case _hoops_GRPRP: {
					_hoops_HCRPR *			name = &option->value._name[0];
					int				count = option->_hoops_AIPCR;
					_hoops_AAPIR **	_hoops_PISGH = &_hoops_APHCR._hoops_HAPIR;

					if (count == 0) {	/* _hoops_PAH _hoops_RGR _hoops_SGIPR _hoops_IHPS? */
						HE_ERROR (HEC_TEXT, HES_NULL_INPUT, "At least one value must be specified for 'output format'");
					}
					else do {
						_hoops_AAPIR *	_hoops_PAGR;
						ALLOC (_hoops_PAGR, _hoops_AAPIR);
						*_hoops_PISGH = _hoops_PAGR;
						_hoops_PISGH = &_hoops_PAGR->next;
						_hoops_PAGR->name.length = 0; /* _hoops_SAHR _hoops_GGR _hoops_AGIR */

						/*** _hoops_SRAI _hoops_RH _hoops_RSIRR _hoops_HRII _hoops_HSAR _hoops_IPS _hoops_SCH ***/
						_hoops_PAGR->name.length = name->length;
						_hoops_PAGR->name.text = name->text;
						name->length = 0;

						++name;
					}
					_hoops_RGGA (--count == 0);

					*_hoops_PISGH = null;
			  }	  break;

			  case _hoops_CRPRP: {
					_hoops_HCRPR *			name = &option->value._name[0];
					int				count = option->_hoops_AIPCR;
					_hoops_IGPIR **	_hoops_PISGH = &_hoops_APHCR._hoops_SAPIR;

					if (count == 0) {	/* _hoops_PAH _hoops_RGR _hoops_SGIPR _hoops_IHPS? */
						HE_ERROR (HEC_TEXT, HES_NULL_INPUT,"At least one value must be specified for 'fallback fonts'");
					}
					else do {
						_hoops_IGPIR *	_hoops_PAGR;
						ALLOC (_hoops_PAGR, _hoops_IGPIR);

						*_hoops_PISGH = _hoops_PAGR;
						_hoops_PISGH = &_hoops_PAGR->next;
						_hoops_PAGR->specified.length = 0; /* _hoops_SAHR _hoops_GGR _hoops_AGIR */

						if (_hoops_RAHSR (*name, system_default)) {
							_hoops_PAGR->_hoops_SSSGP = GFN_SYSTEM_DEFAULT;
						}
						else if (_hoops_RAHSR (*name, sans_serif)) {
							_hoops_PAGR->_hoops_SSSGP = GFN_SANS_SERIF;
						}
						else if (_hoops_RAHSR (*name, typewriter)) {
							_hoops_PAGR->_hoops_SSSGP = GFN_TYPEWRITER;
						}
						else if (_hoops_RAHSR (*name, roman)) {
							_hoops_PAGR->_hoops_SSSGP = GFN_ROMAN;
						}
						else if (_hoops_RAHSR (*name, stroked)) {
							_hoops_PAGR->_hoops_SSSGP = GFN_STROKED;
						}
						else if (name->length == 0) {
							HE_ERROR (HEC_TEXT, HES_NULL_INPUT, "Font names can't be blank/null");
							_hoops_PAGR->_hoops_SSSGP = GFN_STROKED; /* (_hoops_PA) */
						}
						else {
							_hoops_PAGR->_hoops_SSSGP = GFN_SPECIFIED;

							/*** _hoops_SRAI _hoops_RH _hoops_RSIRR _hoops_HRII _hoops_HSAR _hoops_IPS _hoops_SCH ***/
							_hoops_PAGR->specified.length = name->length;
							_hoops_PAGR->specified.text = name->text;
							name->length = 0;
						}

						++name;
					}
					_hoops_RGGA (--count == 0);

					*_hoops_PISGH = null;
			  }	  break;


			  case _hoops_AAPRP: {
					_hoops_HCRPR *			name = &option->value._name[0];
					int				count = option->_hoops_AIPCR;
					_hoops_IGPIR **	_hoops_PISGH = &_hoops_APHCR._hoops_GPPIR;

					if (count == 0) {	/* _hoops_PAH _hoops_RGR _hoops_SGIPR _hoops_IHPS? */
						HE_ERROR (HEC_TEXT, HES_NULL_INPUT, "At least one value must be specified for 'font table'");
					}
					else do {
						_hoops_IGPIR	*_hoops_PAGR;

						ALLOC (_hoops_PAGR, _hoops_IGPIR);
						*_hoops_PISGH = _hoops_PAGR;
						_hoops_PISGH = &_hoops_PAGR->next;
						_hoops_PAGR->specified.length = 0; /* _hoops_SAHR _hoops_GGR _hoops_AGIR */

						_hoops_PAGR->_hoops_SSSGP = GFN_SPECIFIED;

						/*** _hoops_SRAI _hoops_RH _hoops_RSIRR _hoops_HRII _hoops_HSAR _hoops_IPS _hoops_SCH ***/
						_hoops_PAGR->specified.length = name->length;
						_hoops_PAGR->specified.text = name->text;
						name->length = 0;

						++name;
					}
					_hoops_RGGA (--count == 0);

					*_hoops_PISGH = null;
			  }	  break;


			  case _hoops_GAPRP: {
#ifndef DISABLE_CALLBACKS
				_hoops_HCHIR		*_hoops_IGPCR;

				if ((_hoops_IGPCR = *HI_Look_Up_Callback_Name (_hoops_RIGC,
									option->value._name[0].text,
									option->value._name[0].length)) != null) {

					_hoops_APHCR._hoops_PPPIR = _hoops_IGPCR;
					_hoops_PRRH (_hoops_IGPCR);
				}
				else {
					HE_ERROR (HEC_HOOPS_SYSTEM, HES_CALLBACK,
						Sprintf_N (null, "Exit Update '%n' is not a defined callback", option->value._name));
				}
#endif
			  }	break;

			  case _hoops_PAPRP: {
				_hoops_HCRPR *		name = &option->value._name[0];
				char *		_hoops_RPPA = name->text;
				POINTER_SIZED_INT		value;

				if (HI_Scan_Ptr (_hoops_RIGC, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) == null)
					_hoops_APHCR._hoops_HSHRP = (void*)value;
				else
					HE_ERROR (HEC_HOOPS_SYSTEM, HES_INVALID_ADDRESS_POINTER,
							  Sprintf_N (null, "Exit Update Data '%n' is not a pointer value", name));
			  } break;

			  case _hoops_CCARP: {
				  if (option->_hoops_AIPCR == 0)
					  _hoops_APHCR._hoops_CRHRP = _hoops_HRHRP;
				  else
					  _hoops_APHCR._hoops_CRHRP = (int)option->value.option_list->type->id;

				  if (_hoops_APHCR._hoops_CRHRP == _hoops_PRHRP)
					_hoops_APHCR._hoops_HCARP &= ~mask;	/* _hoops_CPSA '_hoops_PSP _hoops_HHSP _hoops_CIIA' */
			  }	  break;

			  case _hoops_RSARP: {
				  if (option->_hoops_AIPCR == 0)
					  _hoops_APHCR._hoops_IGHRP = Drivo_Landscape_ON;
				  else
					  _hoops_APHCR._hoops_IGHRP = (int)option->value.option_list->type->id;
				  if (_hoops_APHCR._hoops_IGHRP == _hoops_PGHRP)
					_hoops_APHCR._hoops_HCARP &= ~mask;	/* _hoops_CPSA '_hoops_PSP _hoops_HISGH' */
			  }	  break;

			  case _hoops_ARPRP: {
				  _hoops_APHCR._hoops_ARHRP = (int)option->value.option_list->type->id;
			  }	  break;

			  case _hoops_HRPRP: {
				  int i = 0;
				  Option_Value *_hoops_IISGH = option->value.option_list;

				  while (_hoops_IISGH) {
					  _hoops_APHCR._hoops_IAHRP[i++] = _hoops_IISGH->type->id;
					  _hoops_IISGH = _hoops_IISGH->next;
				  }
				  while (i < _hoops_HAHRP) {
					  _hoops_APHCR._hoops_IAHRP[i++] = _hoops_SRHRP;
				  }
			  }	  break;

			  case _hoops_IRPRP: {
				  _hoops_APHCR._hoops_PPHRP = (int)option->value.option_list->type->id;
			  }	  break;

			  case _hoops_RAPRP: {
				  if (option->_hoops_AIPCR == 0)
					  _hoops_APHCR._hoops_HSPRP = _hoops_RSPRP;
				  else
					  _hoops_APHCR._hoops_HSPRP = (int)option->value.option_list->type->id;
			  }	  break;

			  case _hoops_PGPRP: {
				  if (option->_hoops_AIPCR == 0)
					  _hoops_APHCR._hoops_GSPRP = _hoops_CCPRP;
				  else
					  _hoops_APHCR._hoops_GSPRP = (int)option->value.option_list->type->id;
			  }	  break;

			  case _hoops_HGPRP: {
				  _hoops_APHCR._hoops_RCHSR = option->value._hoops_CGSAP[0];
			  }	  break;

			  case _hoops_IGPRP: {
				if (option->_hoops_SGSAP == _hoops_IRSAP) {
					_hoops_APHCR._hoops_GCHSR = option->value._hoops_CGSAP[0];
					_hoops_APHCR._hoops_RGHRP = _hoops_SSPRP;
				}
				else {
					Option_Value *		_hoops_CHAGA = option->value.option_list;

					_hoops_APHCR._hoops_GCHSR = _hoops_CHAGA->value._hoops_CGSAP[0];
					_hoops_APHCR._hoops_RGHRP = _hoops_CHAGA->type->id;
				}
			  }	  break;

			  case _hoops_CGPRP: {
				  _hoops_APHCR._hoops_ISPRP = option->value._hoops_CGSAP[0];
			  }	  break;

			  case _hoops_PRPRP: {
				  _hoops_APHCR._hoops_CSPRP = option->value._hoops_CGSAP[0];
			  }	  break;

			  case _hoops_SGPRP: {
				  _hoops_APHCR._hoops_AGHRP = option->value._hoops_RIARA[0];
			  }	  break;

			  case _hoops_RRPRP: {
				  _hoops_APHCR._hoops_GHHSR = option->value._hoops_RIARA[0];
			  }	  break;
			}
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;

FAILED:
	HI_Free_Option_List (_hoops_RIGC, option_list);
	return false;
}



GLOBAL_FUNCTION bool HI_Set_Driver_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_GAPIR *		_hoops_PAICA)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_DRIVER_OPTIONS, _hoops_SRSGH, _hoops_PAICA);
}

GLOBAL_FUNCTION bool HI_Unset_Driver_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_GAPIR *		_hoops_PAICA)
{
	/* _hoops_RRGRA */
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(_hoops_PAICA);
	return false;
}

HC_INTERFACE void HC_CDECL HC_Set_Driver_Options (
	char const *		list)
{
	_hoops_PAPPR context("Set_Driver_Options");

	CODE_GENERATION (
		const char * token = _hoops_CISGH("use window id", list);
		const char * test = _hoops_CISGH("no use window id", list);

		if (token != null && test == null) {
			char _hoops_SISGH[4096];
			char * _hoops_GCSGH = &_hoops_SISGH[0];
			char * _hoops_RCSGH = (char *)list;

			while (_hoops_RCSGH != token)
				*_hoops_GCSGH++ = *_hoops_RCSGH++;
			while (*_hoops_RCSGH != ',')
				_hoops_RCSGH++;
			_hoops_RCSGH++;
			_hoops_AAHR(_hoops_RCSGH, _hoops_GCSGH);

			HI_Dump_Code (Sprintf_S (null, "HC_Set_Driver_Options (%S);\n", _hoops_SISGH));
		}
		else {
			HI_Dump_Code (Sprintf_S (null, "HC_Set_Driver_Options (%S);\n", list));
		}
	);

	bool				used = false;
	_hoops_GAPIR *	_hoops_PAICA;
	ZALLOC (_hoops_PAICA, _hoops_GAPIR);

	if (_hoops_RPSGH (context, list, *_hoops_PAICA)) {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_GPRPP)) != null) {
			used = HI_Set_Driver_Options (context, target, _hoops_PAICA);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		_hoops_GPSGH(context, _hoops_PAICA); 
		FREE (_hoops_PAICA, _hoops_GAPIR);
	}
}



HC_INTERFACE void HC_CDECL HC_UnSet_Driver_Options (void) 
{
	_hoops_PAPPR context("UnSet_Driver_Options");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Driver_Options ();\n");
	);
	
	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GPRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_DRIVER_OPTIONS);
		_hoops_IRRPR();
	}
}



#ifndef DISABLE_SHOW

local const struct _hoops_ACSGH {
	_hoops_PCARP				mask;
	_hoops_SRHSR				name;
}		_hoops_PCSGH[] = {
	{_hoops_CAPRP,					_hoops_GRRCR ("backing store")},
	{_hoops_SAPRP,							_hoops_GRRCR ("border")},
	{_hoops_GPPRP,					_hoops_GRRCR ("control area")},
	{_hoops_ICARP,							_hoops_GRRCR ("debug")},
	{_hoops_CCARP,					_hoops_GRRCR ("disable input")},
	{_hoops_RPPRP,				_hoops_GRRCR ("double-buffering")},
	{_hoops_RPPRP,				_hoops_GRRCR ("double buffering")},
	{_hoops_SCARP,						_hoops_GRRCR ("first color")},
	{_hoops_GSARP,					_hoops_GRRCR ("fixed colors")},
	{_hoops_APPRP,			_hoops_GRRCR ("force black-and-white")},
	{_hoops_APPRP,			_hoops_GRRCR ("force black and white")},
	{_hoops_HHPRP,					_hoops_GRRCR ("force greyscale")},
	{_hoops_HHPRP,					_hoops_GRRCR ("force grayscale")},
	{_hoops_HHPRP,					_hoops_GRRCR ("force grey scale")},
	{_hoops_HHPRP,					_hoops_GRRCR ("force gray scale")},
	{_hoops_IHPRP,					_hoops_GRRCR ("display stats")},
	{_hoops_IHPRP,					_hoops_GRRCR ("display statistics")},
	{_hoops_CHPRP,				_hoops_GRRCR ("display time stats")},
	{_hoops_CHPRP,				_hoops_GRRCR ("display time statistics")},
	{_hoops_SHPRP,			_hoops_GRRCR ("display memory stats")},
	{_hoops_SHPRP,			_hoops_GRRCR ("display memory statistics")},
	{_hoops_RAPRP,		_hoops_GRRCR ("display interrupted update")},
	{_hoops_GAPRP,						_hoops_GRRCR ("exit update")},
	{_hoops_PPPRP,				_hoops_GRRCR ("gamma correction")},
	{_hoops_RSARP,			_hoops_GRRCR ("landscape orientation")},
	{_hoops_ARPRP,					_hoops_GRRCR ("text preference")},
	{_hoops_HRPRP,				_hoops_GRRCR ("quick moves preference")},
	{_hoops_IRPRP,				_hoops_GRRCR ("shadow preference")},
	{_hoops_ASARP,					_hoops_GRRCR ("light scaling")},
	{_hoops_PSARP,				_hoops_GRRCR ("color consolidation")},
	{_hoops_HSARP,				_hoops_GRRCR ("locater transform")},
	{_hoops_ISARP,				_hoops_GRRCR ("number of colors")},
	{_hoops_CSARP,						_hoops_GRRCR ("pen speed")},
	{_hoops_SSARP,					_hoops_GRRCR ("physical size")},
	{_hoops_GGPRP,				_hoops_GRRCR ("selection proximity")},
	{_hoops_GHPRP,					_hoops_GRRCR ("special events")},
	{_hoops_RGPRP,						_hoops_GRRCR ("subscreen")},
	{_hoops_HPPRP,				_hoops_GRRCR ("subscreen creating")},
	{_hoops_IPPRP,				_hoops_GRRCR ("subscreen moving")},
	{_hoops_CPPRP,				_hoops_GRRCR ("subscreen resizing")},
	{_hoops_SPPRP,			_hoops_GRRCR ("subscreen stretching")},
	{_hoops_AGPRP,							_hoops_GRRCR ("title")},
	{_hoops_CRPRP,					_hoops_GRRCR ("fallback font")},
	{_hoops_CRPRP,					_hoops_GRRCR ("fallback fonts")},
	{_hoops_AAPRP,						_hoops_GRRCR ("font table")},
	{_hoops_GRPRP,					_hoops_GRRCR ("output format")},
	{_hoops_PGPRP,				_hoops_GRRCR ("update interrupts")},
	{_hoops_HGPRP,					_hoops_GRRCR ("use colormap id")},
	{_hoops_IGPRP,					_hoops_GRRCR ("use window id")},
	{_hoops_CGPRP,					_hoops_GRRCR ("use window id 2")},
	{_hoops_SGPRP,						_hoops_GRRCR ("write mask")},
	{_hoops_RRPRP,				_hoops_GRRCR ("hardcopy resolution")},
	{_hoops_RHPRP,				_hoops_GRRCR ("stereo")},
	{_hoops_SRPRP,			_hoops_GRRCR ("anti-alias")},
	{_hoops_SRPRP,			_hoops_GRRCR ("anti-aliasing")},
	{_hoops_SRPRP,			_hoops_GRRCR ("anti alias")},
	{_hoops_SRPRP,			_hoops_GRRCR ("anti aliasing")},
	{_hoops_SRPRP,			_hoops_GRRCR ("antialias")},
	{_hoops_SRPRP,			_hoops_GRRCR ("antialiasing")},
	{_hoops_AHPRP,				_hoops_GRRCR ("stencil")},
	{_hoops_PHPRP,			_hoops_GRRCR ("absolute line weight")},
	{_hoops_SIPRP,						_hoops_GRRCR ("isolated")},
	{Drivo_VERTEX_SPOTLIGHT,				_hoops_GRRCR ("spotlight interpolation")},
	{Drivo_VERTEX_SPOTLIGHT,				_hoops_GRRCR ("spotlight preference")},
	{_hoops_GIPRP,						_hoops_GRRCR ("fullscreen")},
	{_hoops_RIPRP,			_hoops_GRRCR ("marker drawing")},
	{_hoops_AIPRP,			_hoops_GRRCR ("fast silhouette edges")},
	{_hoops_PIPRP,			_hoops_GRRCR ("ambient occlusion")},
	{_hoops_HIPRP,							_hoops_GRRCR ("bloom")},
	{_hoops_IIPRP,					_hoops_GRRCR ("depth of field")},
	{_hoops_PAPRP,				_hoops_GRRCR ("exit update data")},
	{false, _hoops_PCGSA}};
#endif

	/* _hoops_HGAPR _hoops_CHASR _hoops_RGCA _hoops_ARAGP _hoops_HCSGH _hoops_ICSGH _hoops_CCSGH _hoops_GGR _hoops_CHARP._hoops_GGHR */
local const char		_hoops_SCSGH[][16] = {
	"??",				/* (_hoops_GSSGH) */
	"system default",
	"sans serif",
	"typewriter",
	"roman",
	"stroked",
};


#define _hoops_RSSGH(_hoops_ASSGH,	 _hoops_PSSGH, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {			\
			if (_hoops_HSSGH == null)											\
				_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);			\
			_hoops_ISSGH = HI_Sprintf1 (p, pe,"%f,", &_hoops_PSSGH);					\
		} while (0)


local char * _hoops_SSSGH (
	_hoops_GAPIR const *		_hoops_GGGRH,
	Option_Value const *		option,
	char *						p,
	char const *				pe)
{
	_hoops_RHHRP mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_GGGRH->_hoops_AHHRP.mask, _hoops_IPHRP)) {
		if (BIT (_hoops_GGGRH->_hoops_AHHRP.value, _hoops_IPHRP))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_GGGRH->_hoops_AHHRP.mask, _hoops_SPHRP)) {
		if (BIT (_hoops_GGGRH->_hoops_AHHRP.value, _hoops_SPHRP))
			p = HI_Copy_Chars ("heavy exterior,", p);
		else
			p = HI_Copy_Chars ("no heavy exterior,", p);
	}

	if (BIT (mask & _hoops_GGGRH->_hoops_AHHRP.mask, _hoops_CPHRP))
		_hoops_RSSGH ("tolerance", _hoops_GGGRH->_hoops_AHHRP._hoops_GAHP, option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


local char * _hoops_RGGRH (
	_hoops_GAPIR const *		_hoops_GGGRH,
	Option_Value const *		option,
	char *						p,
	char const *				pe)
{
	_hoops_RIHRP mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_GGGRH->_hoops_AIHRP.mask, _hoops_PHHRP)) {
		if (BIT (_hoops_GGGRH->_hoops_AIHRP.value, _hoops_PHHRP))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_GGGRH->_hoops_AIHRP.mask, _hoops_HHHRP))
		_hoops_RSSGH ("strength", _hoops_GGGRH->_hoops_AIHRP._hoops_GIGP, option, p, pe);

	if (ANYBIT (mask & _hoops_GGGRH->_hoops_AIHRP.mask, _hoops_SHHRP))
		if (BIT (_hoops_GGGRH->_hoops_AIHRP.value, _hoops_IHHRP))
			p = HI_Copy_Chars ("quality=nice,", p);
		else
			p = HI_Copy_Chars ("quality=fast,", p);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


local char * _hoops_AGGRH (
	_hoops_GAPIR const *		_hoops_GGGRH,
	Option_Value const *		option,
	char *						p,
	char const *				pe)
{
	_hoops_RCHRP mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_GGGRH->_hoops_RGSH.mask, _hoops_PIHRP)) {
		if (BIT (_hoops_GGGRH->_hoops_RGSH.value, _hoops_PIHRP))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_GGGRH->_hoops_RGSH.mask, _hoops_HIHRP))
		_hoops_RSSGH ("strength",
					 _hoops_GGGRH->_hoops_RGSH._hoops_SHGP,
					 option, p, pe);

	if (BIT (mask & _hoops_GGGRH->_hoops_RGSH.mask, _hoops_IIHRP))
		p = HI_Sprintf1 (p, pe, "blur=%d,", (void *)&_hoops_GGGRH->_hoops_RGSH._hoops_HGGGR);

	if (ANYBIT (mask & _hoops_GGGRH->_hoops_RGSH.mask, _hoops_SIHRP)) {
		if (BIT (_hoops_GGGRH->_hoops_RGSH.value, _hoops_CGSH))
			p = HI_Copy_Chars ("shape=star,", p);
		else
			p = HI_Copy_Chars ("shape=radial,", p);
		ASSERT (ANYBIT (_hoops_GGGRH->_hoops_RGSH.value, _hoops_SIHRP)); //_hoops_RPP _hoops_HAR _hoops_PGSH, _hoops_PSCR _hoops_CGH _hoops_SHH _hoops_GHARP
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


local char * _hoops_PGGRH (
	_hoops_GAPIR const *		_hoops_GGGRH,
	Option_Value const *		option,
	char *						p,
	char const *				pe)
{
	_hoops_SCHRP mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_GGGRH->_hoops_ASHRP.mask, _hoops_ACHRP)) {
		if (BIT (_hoops_GGGRH->_hoops_ASHRP.value, _hoops_ACHRP))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_GGGRH->_hoops_ASHRP.mask, _hoops_PCHRP))
		_hoops_RSSGH ("near", _hoops_GGGRH->_hoops_ASHRP._hoops_GSHRP, option, p, pe);

	if (BIT (mask & _hoops_GGGRH->_hoops_ASHRP.mask, _hoops_HCHRP))
		_hoops_RSSGH ("far", _hoops_GGGRH->_hoops_ASHRP._hoops_RSHRP, option, p, pe);

	if (BIT (mask & _hoops_GGGRH->_hoops_ASHRP.mask, _hoops_ICHRP))
		_hoops_RSSGH ("strength", _hoops_GGGRH->_hoops_ASHRP._hoops_SHGP, option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


GLOBAL_FUNCTION void HI_Show_Driver_Options (
	_hoops_GAPIR				*_hoops_PAICA,
	char						*list,
	int							_hoops_GGCIR)
{
#ifndef DISABLE_SHOW
	char						buf[4096];
	char						*_hoops_ASAPR = buf;
	char						*be = buf+_hoops_GGAPR(buf)-1;
	const struct _hoops_ACSGH	*_hoops_HGGRH = _hoops_PCSGH;
	_hoops_PCARP					_hoops_HAICA;
	_hoops_PCARP					_hoops_IAICA;
	int							_hoops_IGGRH;
	int							_hoops_HISCA;

	_hoops_HAICA = _hoops_PAICA->_hoops_HAICA;
	_hoops_IAICA = _hoops_PAICA->_hoops_IAICA;

	if (_hoops_HAICA != 0 || _hoops_IAICA != 0) {
		do if (BIT (_hoops_HGGRH->mask, _hoops_HAPRP)) {
			_hoops_PCARP			_hoops_CGGRH = _hoops_HGGRH->mask & ~_hoops_HAPRP;

			if (BIT (_hoops_HAICA, _hoops_CGGRH)) {
				_hoops_HAICA &= ~_hoops_CGGRH;	/* _hoops_RGAR _hoops_PCHRA _hoops_SPR _hoops_SGGRH _hoops_GRGRH */

				switch (_hoops_HGGRH->mask) {
					case Drivo_VERTEX_SPOTLIGHT: {
						_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
						if (BIT(_hoops_PAICA->_hoops_IAPRP,Drivo_VERTEX_SPOTLIGHT))
							_hoops_ASAPR = HI_Copy_Chars ("=vertex", _hoops_ASAPR);
						else
							_hoops_ASAPR = HI_Copy_Chars ("=pixel", _hoops_ASAPR);
					} break;
					case _hoops_RIPRP: {
						_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
						if (BIT(_hoops_PAICA->_hoops_IAPRP,_hoops_RIPRP))
							_hoops_ASAPR = HI_Copy_Chars ("=fastest", _hoops_ASAPR);
						else
							_hoops_ASAPR = HI_Copy_Chars ("=nicest", _hoops_ASAPR);
					}  break;
					case _hoops_AIPRP: {
						if (!BIT(_hoops_PAICA->_hoops_IAPRP,_hoops_AIPRP)) {
							_hoops_ASAPR = HI_Copy_Chars ("no fast silhouette edges", _hoops_ASAPR);
						}
						else {
							_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
							_hoops_IGGRH = _hoops_RIII (_hoops_PAICA->_hoops_AHHRP.mask);
							_hoops_HISCA = ANYBIT (_hoops_PAICA->_hoops_AHHRP.mask, ~_hoops_IGGRH);
							*_hoops_ASAPR++ = '=';
							if (_hoops_HISCA) *_hoops_ASAPR++ = '(';
							_hoops_ASAPR = _hoops_SSSGH (_hoops_PAICA, null, _hoops_ASAPR, be);
							if (_hoops_HISCA) *_hoops_ASAPR++ = ')';
						}
					} break;
					case _hoops_PIPRP: {
						if (!BIT(_hoops_PAICA->_hoops_IAPRP,_hoops_PIPRP)) {
							_hoops_ASAPR = HI_Copy_Chars ("no ambient occlusion", _hoops_ASAPR);
						}
						else {
							_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
							if (_hoops_PAICA->_hoops_RGSH.mask == _hoops_SHHRP) {
								//_hoops_IRHS _hoops_GRH _hoops_GHSGH _hoops_PGGA _hoops_SCH'_hoops_GRI _hoops_SPR _hoops_HCSP _hoops_CCA 2 _hoops_SIH
								_hoops_HISCA = false;
							}
							else {
								_hoops_IGGRH = _hoops_RIII (_hoops_PAICA->_hoops_AIHRP.mask);
								_hoops_HISCA = ANYBIT (_hoops_PAICA->_hoops_AIHRP.mask, ~_hoops_IGGRH);
							}
							*_hoops_ASAPR++ = '=';
							if (_hoops_HISCA) *_hoops_ASAPR++ = '(';
							_hoops_ASAPR = _hoops_RGGRH (_hoops_PAICA, null, _hoops_ASAPR, be);
							if (_hoops_HISCA) *_hoops_ASAPR++ = ')';
						}
					} break;
					case _hoops_HIPRP: {
						if (!BIT(_hoops_PAICA->_hoops_IAPRP,_hoops_HIPRP)) {
							_hoops_ASAPR = HI_Copy_Chars ("no bloom", _hoops_ASAPR);
						}
						else {
							_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
							if (_hoops_PAICA->_hoops_RGSH.mask == _hoops_SIHRP) {
								//_hoops_IRHS _hoops_GRH _hoops_GHSGH _hoops_PGGA _hoops_SCH'_hoops_GRI _hoops_SPR _hoops_HCSP _hoops_CCA 2 _hoops_SIH
								_hoops_HISCA = false;
							}
							else {
								_hoops_IGGRH = _hoops_RIII (_hoops_PAICA->_hoops_RGSH.mask);
								_hoops_HISCA = ANYBIT (_hoops_PAICA->_hoops_RGSH.mask, ~_hoops_IGGRH);
							}
							*_hoops_ASAPR++ = '=';
							if (_hoops_HISCA) *_hoops_ASAPR++ = '(';
							_hoops_ASAPR = _hoops_AGGRH (_hoops_PAICA, null, _hoops_ASAPR, be);
							if (_hoops_HISCA) *_hoops_ASAPR++ = ')';
						}
					} break;
					case _hoops_IIPRP: {
						if (!BIT(_hoops_PAICA->_hoops_IAPRP,_hoops_IIPRP)) {
							_hoops_ASAPR = HI_Copy_Chars ("no depth of field", _hoops_ASAPR);
						}
						else {
							_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
							_hoops_IGGRH = _hoops_RIII (_hoops_PAICA->_hoops_ASHRP.mask);
							_hoops_HISCA = ANYBIT (_hoops_PAICA->_hoops_ASHRP.mask, ~_hoops_IGGRH);
							*_hoops_ASAPR++ = '=';
							if (_hoops_HISCA) *_hoops_ASAPR++ = '(';
							_hoops_ASAPR = _hoops_PGGRH (_hoops_PAICA, null, _hoops_ASAPR, be);
							if (_hoops_HISCA) *_hoops_ASAPR++ = ')';
						}
					} break;

					default: {
						if (!BIT (_hoops_PAICA->_hoops_IAPRP, _hoops_CGGRH)) {
							*_hoops_ASAPR++ = 'n';
							*_hoops_ASAPR++ = 'o';
							*_hoops_ASAPR++ = ' ';
						}
						_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
					}
				}
				*_hoops_ASAPR++ = ',';
			}
		}
		else if (BIT (_hoops_IAICA, _hoops_HGGRH->mask)) {
			_hoops_IAICA &= ~_hoops_HGGRH->mask;	/* _hoops_RGAR _hoops_PCHRA _hoops_SPR _hoops_SGGRH _hoops_GRGRH */

			if (!BIT (_hoops_PAICA->_hoops_HCARP, _hoops_HGGRH->mask)) {
				*_hoops_ASAPR++ = 'n';
				*_hoops_ASAPR++ = 'o';
				*_hoops_ASAPR++ = ' ';

				_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);
			}
			else {
				_hoops_ASAPR = HI_Copy_Chars (_hoops_HGGRH->name.text, _hoops_ASAPR);

				switch (_hoops_HGGRH->mask) {
					case _hoops_ICARP: {
						if (_hoops_PAICA->_hoops_APPIR > 0) {
							int		count = _hoops_PAICA->_hoops_APPIR;
							int		*_hoops_HAGR = _hoops_PAICA->_hoops_RPPIR;

							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=", null);
							if (_hoops_PAICA->_hoops_APPIR > 1)
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "(", null);
							while (count-- > 0) {
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)_hoops_HAGR++);
								if (count > 0) /* _hoops_RRI... */
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, ",", null);
							}
							if (_hoops_PAICA->_hoops_APPIR > 1)
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, ")", null);
						}
					}	break;

					case _hoops_CCARP: {
						if (_hoops_PAICA->_hoops_CRHRP == _hoops_IRHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=all", _hoops_ASAPR);
					}	break;

					case _hoops_SCARP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%d", (void *)&_hoops_PAICA->_hoops_APASR);
					}	break;

					case _hoops_GSARP: {
						if (_hoops_PAICA->_hoops_GCPRP[1] == 0 &&
							_hoops_PAICA->_hoops_GCPRP[2] == 0)
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%d", (void *)&_hoops_PAICA->_hoops_GCPRP[0]);
						else {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=(%d,", (void *)&_hoops_PAICA->_hoops_GCPRP[0]);
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d,",	 (void *)&_hoops_PAICA->_hoops_GCPRP[1]);
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d)",	 (void *)&_hoops_PAICA->_hoops_GCPRP[2]);
						}
					}	break;

					case _hoops_RSARP: {
						if (_hoops_PAICA->_hoops_IGHRP == _hoops_HGHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=environment", _hoops_ASAPR);
					}	break;

					case _hoops_ARPRP: {
						if (_hoops_PAICA->_hoops_ARHRP == _hoops_GRHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=default", _hoops_ASAPR);
						else if (_hoops_PAICA->_hoops_ARHRP == _hoops_CGHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=bitmap", _hoops_ASAPR);
						else if (_hoops_PAICA->_hoops_ARHRP == _hoops_SGHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=outline", _hoops_ASAPR);
					}	break;

					case _hoops_HRPRP: {
						int i;

						_hoops_ASAPR = HI_Copy_Chars ("=", _hoops_ASAPR);
						if (_hoops_PAICA->_hoops_IAHRP[0] == _hoops_SRHRP)
							_hoops_ASAPR = HI_Copy_Chars ("default", _hoops_ASAPR);
						else {
							if (_hoops_PAICA->_hoops_IAHRP[1] != _hoops_SRHRP)
								_hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);  /* _hoops_GPGR _hoops_HSH _hoops_HGAP _hoops_CGS */
							for (i = 0; _hoops_PAICA->_hoops_IAHRP[i] != _hoops_SRHRP; i++) {
								if (_hoops_PAICA->_hoops_IAHRP[i] == _hoops_GAHRP)
									_hoops_ASAPR = HI_Copy_Chars ("xor,", _hoops_ASAPR);
								else if (_hoops_PAICA->_hoops_IAHRP[i] == _hoops_RAHRP)
									_hoops_ASAPR = HI_Copy_Chars ("overlay,", _hoops_ASAPR);
								else if (_hoops_PAICA->_hoops_IAHRP[i] == _hoops_PAHRP)
									_hoops_ASAPR = HI_Copy_Chars ("spriting,", _hoops_ASAPR);
							}
							_hoops_ASAPR--;  /* _hoops_PCHIA _hoops_RH _hoops_CGHI ',' */
							if (_hoops_PAICA->_hoops_IAHRP[1] != _hoops_SRHRP)
								_hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);  /* _hoops_GPGR _hoops_HSH _hoops_HGAP _hoops_CGS */
						}
					 }	break;

					case _hoops_IRPRP: {
						if (_hoops_PAICA->_hoops_PPHRP == _hoops_CAHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=software", _hoops_ASAPR);
						else if (_hoops_PAICA->_hoops_PPHRP == _hoops_SAHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=hardware", _hoops_ASAPR);
						else if (_hoops_PAICA->_hoops_PPHRP == _hoops_GPHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=image", _hoops_ASAPR);
						else if (_hoops_PAICA->_hoops_PPHRP == _hoops_RPHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=opengl", _hoops_ASAPR);
						else if (_hoops_PAICA->_hoops_PPHRP == _hoops_APHRP)
							_hoops_ASAPR = HI_Copy_Chars ("=soft opengl", _hoops_ASAPR);
					}	break;

					case _hoops_RAPRP: {
						if (_hoops_PAICA->_hoops_HSPRP == _hoops_ASPRP)
							_hoops_ASAPR = HI_Copy_Chars ("=off", _hoops_ASAPR);
						else if (_hoops_PAICA->_hoops_HSPRP == _hoops_PSPRP)
							_hoops_ASAPR = HI_Copy_Chars ("=on", _hoops_ASAPR);
					}	break;

					case _hoops_ASARP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%f", (void *)&_hoops_PAICA->_hoops_RCPRP);
					}	break;

					case _hoops_PSARP: {
						float	_hoops_RISGH = 100.0f * _hoops_PAICA->_hoops_ACPRP;
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%f%%", (void *)&_hoops_RISGH);
													}	  break;

					case _hoops_HSARP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=(%f,",(void *)&_hoops_PAICA->_hoops_PCPRP[0][0]);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,",	(void *)&_hoops_PAICA->_hoops_PCPRP[0][1]);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,",	(void *)&_hoops_PAICA->_hoops_PCPRP[1][0]);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,",	(void *)&_hoops_PAICA->_hoops_PCPRP[1][1]);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,",	(void *)&_hoops_PAICA->_hoops_PCPRP[2][0]);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f)",	(void *)&_hoops_PAICA->_hoops_PCPRP[2][1]);
					}	break;

					case _hoops_ISARP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%d", (void *)&_hoops_PAICA->_hoops_AAPSR);
					}	break;

					case _hoops_CSARP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%f", (void *)&_hoops_PAICA->_hoops_GSHSR);
					}	break;

					case _hoops_SSARP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=(%f,", (void *)&_hoops_PAICA->_hoops_SPHSR.x);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f)", (void *)&_hoops_PAICA->_hoops_SPHSR.y);
					}	break;

					case _hoops_GGPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%f", (void *)&_hoops_PAICA->_hoops_SHSHA);
					}	break;

					case _hoops_RGPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=(%f,", (void *)&_hoops_PAICA->_hoops_HCPRP.left);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,", (void *)&_hoops_PAICA->_hoops_HCPRP.right);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,", (void *)&_hoops_PAICA->_hoops_HCPRP.bottom);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f)", (void *)&_hoops_PAICA->_hoops_HCPRP.top);
					}	break;

					case _hoops_AGPRP: {
						if (_hoops_PAICA->_hoops_IAPIR.length > 0)
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%N", (void *)&_hoops_PAICA->_hoops_IAPIR);
					}	break;

					case _hoops_SRPRP: {
						if (_hoops_PAICA->_hoops_AIPGA > 0)
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%d", (void *)&_hoops_PAICA->_hoops_AIPGA);
					}	break;

					case _hoops_CRPRP: {
						if (_hoops_PAICA->_hoops_SAPIR != null) {
							_hoops_IGPIR	*_hoops_CAGRA = _hoops_PAICA->_hoops_SAPIR;

							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be,
								(_hoops_CAGRA->next != null) ? "=(" : "=",
								null);

							do {
								if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%qn,", (void *)&_hoops_CAGRA->specified);
								else
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
							}
							_hoops_RGGA ((_hoops_CAGRA = _hoops_CAGRA->next) == null);

							if (_hoops_ASAPR != null) {
								_hoops_ASAPR--;

								if (_hoops_PAICA->_hoops_SAPIR->next != null) {
									*_hoops_ASAPR++ = ')';
								}
							}
						}
					}	break;

					case _hoops_AAPRP: {
						if (_hoops_PAICA->_hoops_GPPIR != null) {
							_hoops_IGPIR	*_hoops_CAGRA = _hoops_PAICA->_hoops_GPPIR;

							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be,
								(_hoops_CAGRA->next != null) ? "=(" : "=",
								null);

							do {
								if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%qn,", (void *)&_hoops_CAGRA->specified);
								else
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
							}
							_hoops_RGGA ((_hoops_CAGRA = _hoops_CAGRA->next) == null);

							if (_hoops_ASAPR != null) {
								_hoops_ASAPR--;

								if (_hoops_PAICA->_hoops_GPPIR->next != null) {
									*_hoops_ASAPR++ = ')';
								}
							}
						}
					}	break;

					case _hoops_GRPRP: {
						if (_hoops_PAICA->_hoops_HAPIR != null) {
							_hoops_AAPIR	*_hoops_CAGRA = _hoops_PAICA->_hoops_HAPIR;

							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be,
								(_hoops_CAGRA->next != null) ? "=(" : "=",
								null);

							do {
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%N", (void *)&_hoops_CAGRA->name);
							}
							_hoops_RGGA ((_hoops_CAGRA = _hoops_CAGRA->next) == null);

							if (_hoops_ASAPR != null) {
								_hoops_ASAPR--;

								if (_hoops_PAICA->_hoops_HAPIR->next != null) {
									*_hoops_ASAPR++ = ')';
								}
							}
						}
					}	break;

					case _hoops_PGPRP: {
						if (_hoops_PAICA->_hoops_GSPRP == _hoops_SCPRP)
							_hoops_ASAPR = HI_Copy_Chars ("=unrestricted", _hoops_ASAPR);
					}	break;

					case _hoops_HGPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=0x%X", (void *)&_hoops_PAICA->_hoops_RCHSR);
					}	break;

					case _hoops_IGPRP: {
						if (_hoops_PAICA->_hoops_RGHRP == _hoops_SSPRP)
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=0x%X", (void *)&_hoops_PAICA->_hoops_GCHSR);
						else
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=image key=0x%X", (void *)&_hoops_PAICA->_hoops_GCHSR);
					}	break;

					case _hoops_CGPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=0x%X", (void *)&_hoops_PAICA->_hoops_ISPRP);
					}	break;

					case _hoops_GAPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%n", (void *)&_hoops_PAICA->_hoops_PPPIR->name);
					}	break;

					case _hoops_PAPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=0x%X", (void *)&_hoops_PAICA->_hoops_HSHRP);
					}	break;

					case _hoops_PRPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=0x%X", (void *)&_hoops_PAICA->_hoops_CSPRP);
					}	break;

					case _hoops_SGPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%d", (void *)&_hoops_PAICA->_hoops_AGHRP);
					}	break;

					case _hoops_RRPRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "=%d", (void *)&_hoops_PAICA->_hoops_GHHSR);
					}	break;
				}
			}

			if (_hoops_ASAPR == null) {
				HE_ERROR2 (HEC_MEMORY, HES_BUFFER_OVERFLOW, "Unable to format driver options -","internal buffer overflow");
				return;
			}

			*_hoops_ASAPR++ = ',';
		} _hoops_RGGA (!(++_hoops_HGGRH)->mask);

		--_hoops_ASAPR; /* _hoops_HASIR _hoops_GRCIR "," */
	}

	HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
#endif
}


#ifndef DISABLE_SHOW

local _hoops_PCARP _hoops_RRGRH (
	char const *					_hoops_ARGRH) {
	const struct _hoops_ACSGH *		_hoops_HGGRH = _hoops_PCSGH;
	_hoops_HCRPR							_hoops_PRGRH;

	HI_Canonize_Chars (_hoops_ARGRH, &_hoops_PRGRH);

	_hoops_RGGA (_hoops_RAHSR (_hoops_PRGRH, _hoops_HGGRH->name)) if ((++_hoops_HGGRH)->mask == false) {
		HE_ERROR (HEC_DRIVER, HES_INVALID_OPTION,
				  Sprintf_S (null, "'%s' is not the name of any known driver option", _hoops_ARGRH));
		break;
	}

	_hoops_RGAIR (_hoops_PRGRH);

	return _hoops_HGGRH->mask;
}


local void _hoops_HRGRH (
	_hoops_GAPIR *		_hoops_PAICA,
	char const *			_hoops_ARGRH,
	char *					list,
	int						_hoops_GGCIR) {
	_hoops_PCARP				mask;
	char					buf[2048];
	char *					_hoops_ASAPR = buf;
	char *					be = buf+_hoops_GGAPR (buf)-1;

	if ((mask = _hoops_RRGRH (_hoops_ARGRH)) == false)
		return;

	if (BIT (mask, _hoops_HAPRP)) {
		mask &= ~_hoops_HAPRP;

		if (!BIT (_hoops_PAICA->_hoops_HAICA, mask)) {
			HE_ERROR (HEC_DRIVER, HES_NO_LOCAL_SETTING,
					  Sprintf_SP (null, "'%s' has no setting in '%p'", _hoops_ARGRH, _hoops_PAICA->owner));
			return;
		}

		switch (mask|_hoops_HAPRP) {
			case Drivo_VERTEX_SPOTLIGHT: {
				if (BIT (_hoops_PAICA->_hoops_IAPRP, mask))
					HI_Return_Chars (list, _hoops_GGCIR, "vertex", 6);
				else
					HI_Return_Chars (list, _hoops_GGCIR, "pixel", 5);
			} break;

			case _hoops_RIPRP: {
				if (BIT (_hoops_PAICA->_hoops_IAPRP, mask))
					HI_Return_Chars (list, _hoops_GGCIR, "fastest", 7);
				else
					HI_Return_Chars (list, _hoops_GGCIR, "nicest", 6);
			} break;

			case _hoops_AIPRP: {
				_hoops_ASAPR = _hoops_SSSGH (_hoops_PAICA, null, _hoops_ASAPR, be);
				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
			} break;

			case _hoops_PIPRP: {
				_hoops_ASAPR = _hoops_RGGRH (_hoops_PAICA, null, _hoops_ASAPR, be);
				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
			} break;

			case _hoops_HIPRP: {
				_hoops_ASAPR = _hoops_AGGRH (_hoops_PAICA, null, _hoops_ASAPR, be);
				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
			} break;

			case _hoops_IIPRP: {
				_hoops_ASAPR = _hoops_PGGRH (_hoops_PAICA, null, _hoops_ASAPR, be);
				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
			} break;

			default:
				if (!BIT (_hoops_PAICA->_hoops_IAPRP, mask))
					HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
				else
					HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
		}
	}
	else if (!BIT (_hoops_PAICA->_hoops_IAICA, mask)) {
		HE_ERROR (HEC_DRIVER, HES_NO_LOCAL_SETTING,
				  Sprintf_SP (null, "'%s' has no setting in '%p'", _hoops_ARGRH, _hoops_PAICA->owner));
		return;
	}
	else if (mask == _hoops_ICARP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		int		count = _hoops_PAICA->_hoops_APPIR;
		int		*_hoops_HAGR = _hoops_PAICA->_hoops_RPPIR;

		while (count-- > 0) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)_hoops_HAGR++);
			if (count > 0) /* _hoops_RRI... */
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, ",", null);
		}
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_SCARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)&_hoops_PAICA->_hoops_APASR);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_GSARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_GCPRP[1] == 0 &&
			_hoops_PAICA->_hoops_GCPRP[2] == 0)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)&_hoops_PAICA->_hoops_GCPRP[0]);
		else {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "(%d,",  (void *)&_hoops_PAICA->_hoops_GCPRP[0]);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d,",   (void *)&_hoops_PAICA->_hoops_GCPRP[1]);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d)",   (void *)&_hoops_PAICA->_hoops_GCPRP[2]);
		}
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_ASARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f", (void *)&_hoops_PAICA->_hoops_RCPRP);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_PSARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		float	_hoops_RISGH = 100.0f * _hoops_PAICA->_hoops_ACPRP;
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f%%", (void *)&_hoops_RISGH);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_HSARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "(%d,", (void *)&_hoops_PAICA->_hoops_PCPRP[0][0]);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d,",  (void *)&_hoops_PAICA->_hoops_PCPRP[0][1]);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d,",  (void *)&_hoops_PAICA->_hoops_PCPRP[1][0]);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d,",  (void *)&_hoops_PAICA->_hoops_PCPRP[1][1]);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d,",  (void *)&_hoops_PAICA->_hoops_PCPRP[2][0]);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d)",  (void *)&_hoops_PAICA->_hoops_PCPRP[2][1]);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_ISARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)&_hoops_PAICA->_hoops_AAPSR);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_CSARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f", (void *)&_hoops_PAICA->_hoops_GSHSR);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_SSARP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "(%f,", (void *)&_hoops_PAICA->_hoops_SPHSR.x);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f)", (void *)&_hoops_PAICA->_hoops_SPHSR.y);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_GGPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f", (void *)&_hoops_PAICA->_hoops_SHSHA);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_RGPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "(%f,", (void *)&_hoops_PAICA->_hoops_HCPRP.left);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,", (void *)&_hoops_PAICA->_hoops_HCPRP.right);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f,", (void *)&_hoops_PAICA->_hoops_HCPRP.bottom);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%f)", (void *)&_hoops_PAICA->_hoops_HCPRP.top);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_AGPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_IAPIR.length > 0)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%N", (void *)&_hoops_PAICA->_hoops_IAPIR);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_SRPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_AIPGA > 0) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)&_hoops_PAICA->_hoops_AIPGA);
			HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
		}
		else
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	}
	else if (mask == _hoops_CRPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_SAPIR != null) {
			_hoops_IGPIR	*_hoops_CAGRA = _hoops_PAICA->_hoops_SAPIR;

			do {
				if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%qn,", (void *)&_hoops_CAGRA->specified);
				else
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
			} while ((_hoops_CAGRA = _hoops_CAGRA->next) != null);

			if (_hoops_ASAPR != null)
				_hoops_ASAPR[-1] = '\0';
		}

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_AAPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_GPPIR != null) {
			_hoops_IGPIR	*_hoops_CAGRA = _hoops_PAICA->_hoops_GPPIR;

			do {
				if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%qn,", (void *)&_hoops_CAGRA->specified);
				else
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
			} while ((_hoops_CAGRA = _hoops_CAGRA->next) != null);

			if (_hoops_ASAPR != null)
				_hoops_ASAPR[-1] = '\0';
		}

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_GRPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_HAPIR != null) {
			_hoops_AAPIR	*_hoops_CAGRA = _hoops_PAICA->_hoops_HAPIR;

			do {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%N", (void *)&_hoops_CAGRA->name);
				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
			} while ((_hoops_CAGRA = _hoops_CAGRA->next) != null);

			if (_hoops_ASAPR != null)
				_hoops_ASAPR[-1] = '\0';
		}

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_PGPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask) &&
			 _hoops_PAICA->_hoops_GSPRP == _hoops_SCPRP) {
		HI_Return_Chars (list, _hoops_GGCIR, "unrestricted", 12);
	}
	else if (mask == _hoops_HGPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "0x%X", (void *)&_hoops_PAICA->_hoops_RCHSR);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_IGPRP && BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_RGHRP == _hoops_SSPRP)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "0x%X", (void *)&_hoops_PAICA->_hoops_GCHSR);
		else
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "image key=0x%X", (void *)&_hoops_PAICA->_hoops_GCHSR);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_CGPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "0x%X", (void *)&_hoops_PAICA->_hoops_ISPRP);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_GAPRP &&
		BIT (_hoops_PAICA->_hoops_HCARP, mask)) {

		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%n", (void *)&_hoops_PAICA->_hoops_PPPIR->name);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_PAPRP &&
		BIT (_hoops_PAICA->_hoops_HCARP, mask)) {

		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "0x%X", (void *)&_hoops_PAICA->_hoops_HSHRP);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_PRPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "0x%X", (void *)&_hoops_PAICA->_hoops_CSPRP);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_SGPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)&_hoops_PAICA->_hoops_AGHRP);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (mask == _hoops_RSARP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask) &&
			 _hoops_PAICA->_hoops_IGHRP == _hoops_HGHRP)
		HI_Return_Chars (list, _hoops_GGCIR, "environment", 11);
	else if (mask == _hoops_ARPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_ARHRP == _hoops_GRHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "default", 7);
		else if (_hoops_PAICA->_hoops_ARHRP == _hoops_CGHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "bitmap",  6);
		else if (_hoops_PAICA->_hoops_ARHRP == _hoops_SGHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "outline", 7);
	}
	else if (mask == _hoops_HRPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_IAHRP[0] == _hoops_SRHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "default", 7);
		else {
			char *_hoops_IRGRH = _hoops_ASAPR;
			int i;
			if (_hoops_PAICA->_hoops_IAHRP[1] != _hoops_SRHRP)
				_hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);  /* _hoops_GPGR _hoops_HSH _hoops_HGAP _hoops_CGS */
			for (i = 0; _hoops_PAICA->_hoops_IAHRP[i] != _hoops_SRHRP; i++) {
				if (_hoops_PAICA->_hoops_IAHRP[i] == _hoops_GAHRP)
					_hoops_ASAPR = HI_Copy_Chars ("xor,", _hoops_ASAPR);
				else if (_hoops_PAICA->_hoops_IAHRP[i] == _hoops_RAHRP)
					_hoops_ASAPR = HI_Copy_Chars ("overlay,", _hoops_ASAPR);
				else if (_hoops_PAICA->_hoops_IAHRP[i] == _hoops_PAHRP)
					_hoops_ASAPR = HI_Copy_Chars ("spriting,", _hoops_ASAPR);
			}
			_hoops_ASAPR--;  /* _hoops_PCHIA _hoops_RH _hoops_CGHI ',' */
			if (_hoops_PAICA->_hoops_IAHRP[1] != _hoops_SRHRP)
				_hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);  /* _hoops_GPGR _hoops_HSH _hoops_HGAP _hoops_CGS */
			HI_Return_Chars (list, _hoops_GGCIR, _hoops_IRGRH, _hoops_ASAPR-_hoops_IRGRH);
		}
	}
	else if (mask == _hoops_IRPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_PPHRP == _hoops_CAHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "software",	 8);
		else if (_hoops_PAICA->_hoops_PPHRP == _hoops_SAHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "hardware", 8);
		else if (_hoops_PAICA->_hoops_PPHRP == _hoops_GPHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "image", 5);
		else if (_hoops_PAICA->_hoops_PPHRP == _hoops_RPHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "opengl", 6);
		else if (_hoops_PAICA->_hoops_PPHRP == _hoops_APHRP)
			HI_Return_Chars (list, _hoops_GGCIR, "soft opengl", 11);
	}
	else if (mask == _hoops_RAPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		if (_hoops_PAICA->_hoops_HSPRP == _hoops_ASPRP)
			HI_Return_Chars (list, _hoops_GGCIR, "off",	 3);
		else if (_hoops_PAICA->_hoops_HSPRP == _hoops_PSPRP)
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	}
	else if (mask == _hoops_CCARP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask) &&
			 _hoops_PAICA->_hoops_CRHRP == _hoops_IRHRP)
		HI_Return_Chars (list, _hoops_GGCIR, "all", 11);
	else if (mask == _hoops_RRPRP &&
			 BIT (_hoops_PAICA->_hoops_HCARP, mask)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, be, "%d", (void *)&_hoops_PAICA->_hoops_GHHSR);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
	}
	else {
		if (!BIT (_hoops_PAICA->_hoops_HCARP, mask))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	}
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Driver_Options (
	char *		options)
{
	_hoops_PAPPR context("Show_Driver_Options");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Driver_Options () */\n");
	);


	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CCRPP)) != null) {

		_hoops_GAPIR *	_hoops_PAICA;
		if ((_hoops_PAICA = (_hoops_GAPIR *)HI_Find_Attribute (context, target, HK_DRIVER_OPTIONS)) != null) {
			HI_Show_Driver_Options (_hoops_PAICA, options, -1);
			_hoops_HPRH (_hoops_PAICA);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Driver_Options (
	int					count,
	Key const *			keys,
	char *				options)
{
	_hoops_PAPPR context("PShow_Net_Driver_Options");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Driver_Options () */\n");
	);

	_hoops_GAPIR *	_hoops_PAICA;
	if ((_hoops_PAICA = (_hoops_GAPIR *) HI_Find_Attribute_And_Lock(context, _hoops_CCRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Driver_Options (_hoops_PAICA, options, -1);
		_hoops_HPRH (_hoops_PAICA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(options, -1, "", 0);

#endif
}


#endif


/****/
HC_INTERFACE void HC_CDECL HC_Show_One_Driver_Option (
	char const *			_hoops_CRGRH,
	char *					options)
{
	_hoops_PAPPR context("Show_One_Driver_Options");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Driver_Options () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CCRPP)) != null) {

		_hoops_GAPIR *	_hoops_PAICA;
		if ((_hoops_PAICA = (_hoops_GAPIR *)HI_Find_Attribute (context, target, HK_DRIVER_OPTIONS)) != null) {
			_hoops_HRGRH (_hoops_PAICA, _hoops_CRGRH, options, -1);
			_hoops_HPRH (_hoops_PAICA);
		}
		_hoops_IRRPR();
	}
#endif
}





#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Driver_Option (
	int						count,
	Key const *				keys,
	char const *			_hoops_CRGRH,
	char *					options)
{
	_hoops_PAPPR context("PShow_One_Net_Driver_Options");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Driver_Options () */\n");
	);

	_hoops_GAPIR *	_hoops_PAICA;
	if ((_hoops_PAICA = (_hoops_GAPIR *) HI_Find_Attribute_And_Lock(context, _hoops_CCRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_HRGRH (_hoops_PAICA, _hoops_CRGRH, options, -1);
		_hoops_HPRH (_hoops_PAICA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(options, -1, "", 0);

#endif
}

#endif

