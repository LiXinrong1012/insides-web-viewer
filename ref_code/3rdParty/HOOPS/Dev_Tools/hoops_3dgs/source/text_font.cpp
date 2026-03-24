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
 * $Id: obf_tmp.txt 1.162.2.1 2011-01-25 19:53:29 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "searchh.h"
#include "please.h"

local const _hoops_IGRCR _hoops_SPPGGR[] = {
	{FT_FULL,				_hoops_GRRCR ("on"),							_hoops_RRRCR, 0, false},
	{FT_FULL,				_hoops_GRRCR ("full"),							_hoops_RRRCR, 0, false},
	{FT_NONE,				_hoops_GRRCR ("off"),							_hoops_RRRCR, 0, false},
	{FT_NONE,				_hoops_GRRCR ("none"),							_hoops_RRRCR, 0, false},
	{FT_POSITION_ONLY,		_hoops_GRRCR ("character position only"),		_hoops_RRRCR, 0, false},
	{FT_POSITION_ADJUSTED,	_hoops_GRRCR ("character position adjusted"),	_hoops_RRRCR, 0, false},

	/* _hoops_PHSSA _hoops_IH _hoops_SGCRP _hoops_SGH _hoops_RGAR */
	{FT_POSITION_ONLY,		_hoops_GRRCR ("cpo"), 							_hoops_RRRCR, 0, false},
	{FT_POSITION_ADJUSTED,	_hoops_GRRCR ("cpa"), 							_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_GHPGGR = {
	_hoops_GGAPR (_hoops_SPPGGR),
	_hoops_SPPGGR,
};

local const _hoops_IGRCR _hoops_AHSIA[] = {
	{GSU_PERCENT,		_hoops_GRRCR ("%"),				_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("px"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pxl"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixel"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixels"),		_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pt"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pts"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("point"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("points"),		_hoops_RRRCR, 0, false},
	{GSU_SRU,			_hoops_GRRCR ("sru"),			_hoops_RRRCR, 0, false},
	{GSU_WRU,			_hoops_GRRCR ("wru"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("wsu"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("world"),			_hoops_RRRCR, 0, false},
	{GSU_ORU,			_hoops_GRRCR ("oru"),			_hoops_RRRCR, 0, false},
};

/* _hoops_GIGHR: _hoops_IGIR _hoops_GHCA _hoops_HAR _hoops_SHH "%", _hoops_HIS _hoops_HSGR _hoops_SRS _hoops_RARP _hoops_GGR _hoops_GASR */
local const _hoops_HPAGA _hoops_PHSIA = {
	_hoops_GGAPR (_hoops_AHSIA) - 1,
	&_hoops_AHSIA[1],
};

/* _hoops_AAHP _hoops_PPR _hoops_RHPGGR _hoops_SHI _hoops_PAH _hoops_SGH "%" */
local const _hoops_HPAGA _hoops_AHPGGR = {
	_hoops_GGAPR (_hoops_AHSIA),
	_hoops_AHSIA,
};


local const _hoops_HPAGA _hoops_PHPGGR = {
	_hoops_GGAPR (_hoops_AHSIA),
	_hoops_AHSIA,
};

local const _hoops_IGRCR _hoops_HHPGGR[] = {
	{true,		_hoops_GRRCR ("deg"),					_hoops_RRRCR, 0, false},
	{true,		_hoops_GRRCR ("degree"),				_hoops_RRRCR, 0, false},
	{true,		_hoops_GRRCR ("degrees"),				_hoops_RRRCR, 0, false},
	{false,		_hoops_GRRCR (""),						_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_IHPGGR = {
	_hoops_GGAPR (_hoops_HHPGGR),
	_hoops_HHPGGR,
};


local const _hoops_IGRCR _hoops_CHPGGR[] = {
	{_hoops_HGHAP,		_hoops_GRRCR ("none"),				_hoops_RRRCR, 0, false},
	{_hoops_HGHAP,		_hoops_GRRCR ("off"),				_hoops_RRRCR, 0, false},
	{_hoops_HGHAP,		_hoops_GRRCR ("no"),				_hoops_RRRCR, 0, false},
	{_hoops_HGHAP,		_hoops_GRRCR ("false"),				_hoops_RRRCR, 0, false},

	{_hoops_IGHAP,		_hoops_GRRCR ("lines"),				_hoops_RRRCR, 0, false},
	{_hoops_IGHAP,		_hoops_GRRCR ("on"),				_hoops_RRRCR, 0, false},
	{_hoops_IGHAP,		_hoops_GRRCR ("yes"),				_hoops_RRRCR, 0, false},
	{_hoops_IGHAP,		_hoops_GRRCR ("true"),				_hoops_RRRCR, 0, false},

	{_hoops_CGHAP,		_hoops_GRRCR ("box"),				_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_SHPGGR = {
	_hoops_GGAPR (_hoops_CHPGGR),
	_hoops_CHPGGR,
};


#define	_hoops_GIPGGR	(-1)
#define	_hoops_RIPGGR	(-2)
#define	_hoops_AIPGGR	(-3)

local const _hoops_IGRCR _hoops_PIPGGR[] = {
	{_hoops_RSPAP,		_hoops_GRRCR ("default"),	_hoops_RRRCR, 0, false},
	{_hoops_ASPAP,			_hoops_GRRCR ("driver"),	_hoops_RRRCR, 0, false},
	{_hoops_PSPAP,		_hoops_GRRCR ("truetype"),	_hoops_RRRCR, 0, false},
	{_hoops_HSPAP,		_hoops_GRRCR ("defined"),	_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_HIPGGR = {
	_hoops_GGAPR (_hoops_PIPGGR),
	_hoops_PIPGGR,
};

local const _hoops_IGRCR _hoops_IIPGGR[] = {
	{_hoops_RSPAP,		_hoops_GRRCR ("default"),	_hoops_RRRCR, 0, false},
	{_hoops_ASPAP,			_hoops_GRRCR ("driver"),	_hoops_RRRCR, 0, false},
	{_hoops_PSPAP,		_hoops_GRRCR ("truetype"),	_hoops_RRRCR, 0, false},
	{_hoops_HSPAP,		_hoops_GRRCR ("defined"),	_hoops_RRRCR, 0, false},

	{_hoops_GIPGGR,	_hoops_GRRCR ("smaller"),	_hoops_GHAGA, 1, false, &_hoops_HIPGGR},
	{_hoops_RIPGGR,		_hoops_GRRCR ("larger"),	_hoops_GHAGA, 1, false, &_hoops_HIPGGR},
	{_hoops_AIPGGR,		_hoops_GRRCR ("cutoff"),	_hoops_CIGHA, 1, true, &_hoops_PHSIA},
};

local const _hoops_HPAGA _hoops_CIPGGR = {
	_hoops_GGAPR (_hoops_IIPGGR),
	_hoops_IIPGGR,
};


local const _hoops_IGRCR _hoops_SIPGGR[] = {
	{_hoops_GRHRP,			_hoops_GRRCR ("default"),	_hoops_RRRCR, 0, false},
	{_hoops_GRHRP,			_hoops_GRRCR ("driver"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("bitmap"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("bitmaps"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("raster"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("rasters"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("outline"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("outlines"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("vector"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("vectors"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("area"),		_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("areas"),		_hoops_RRRCR, 0, false},
	{_hoops_RRHRP,	_hoops_GRRCR ("exterior"),  _hoops_RRRCR, 0, false},
	{_hoops_RRHRP,	_hoops_GRRCR ("exteriors"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_GCPGGR = {
	_hoops_GGAPR (_hoops_SIPGGR),
	_hoops_SIPGGR,
};

local const _hoops_IGRCR _hoops_RCPGGR[] = {
	{_hoops_GRHRP,			_hoops_GRRCR ("default"),	_hoops_RRRCR, 0, false},
	{_hoops_GRHRP,			_hoops_GRRCR ("driver"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("bitmap"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("bitmaps"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("raster"),	_hoops_RRRCR, 0, false},
	{_hoops_CGHRP,				_hoops_GRRCR ("rasters"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("outline"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("outlines"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("vector"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("vectors"),	_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("area"),		_hoops_RRRCR, 0, false},
	{_hoops_SGHRP,			_hoops_GRRCR ("areas"),		_hoops_RRRCR, 0, false},
	{_hoops_RRHRP,	_hoops_GRRCR ("exterior"),  _hoops_RRRCR, 0, false},
	{_hoops_RRHRP,	_hoops_GRRCR ("exteriors"), _hoops_RRRCR, 0, false},

	{_hoops_GIPGGR,			_hoops_GRRCR ("smaller"),	_hoops_GHAGA, 1, false, &_hoops_GCPGGR},
	{_hoops_RIPGGR,				_hoops_GRRCR ("larger"),	_hoops_GHAGA, 1, false, &_hoops_GCPGGR},
	{_hoops_AIPGGR,				_hoops_GRRCR ("cutoff"),	_hoops_CIGHA, 1, true, &_hoops_PHSIA},
};

local const _hoops_HPAGA _hoops_ACPGGR = {
	_hoops_GGAPR (_hoops_RCPGGR),
	_hoops_RCPGGR,
};



local const _hoops_IGRCR _hoops_PCPGGR[] = {
	{_hoops_GPPAP,			_hoops_GRRCR ("name"),			 	_hoops_PRRCR, -9999, false},
	{_hoops_RPPAP,			_hoops_GRRCR ("size"),			 	_hoops_CIGHA, 1, false, &_hoops_PHSIA},
	{_hoops_APPAP, _hoops_GRRCR ("size tolerance"), 	_hoops_CIGHA, 1, true, &_hoops_AHPGGR},
	{_hoops_GHPAP, _hoops_GRRCR ("greeking limit"), 	_hoops_CIGHA, 1, true, &_hoops_PHSIA},
	{_hoops_IIPAP,	_hoops_GRRCR ("greeking mode"),	 	_hoops_GHAGA,  1, true, &_hoops_SHPGGR},
	{_hoops_PPPAP,		_hoops_GRRCR ("transform"),		 	_hoops_GHAGA, -1, true, &_hoops_GHPGGR},
	{_hoops_PPPAP,		_hoops_GRRCR ("transforms"),	 	_hoops_GHAGA, -1, true, &_hoops_GHPGGR},
	{_hoops_HPPAP,		_hoops_GRRCR ("rotation"),		 	_hoops_PRRCR, 1, true},
	{_hoops_IPPAP,	_hoops_GRRCR ("width scale"),	 	_hoops_SPPCR, 1, true},
	{_hoops_RHPAP,	_hoops_GRRCR ("line spacing"),	 	_hoops_SPPCR, 1, false},
	{_hoops_CPPAP,	_hoops_GRRCR ("extra space"),	 	_hoops_CIGHA, 1, true, &_hoops_PHSIA},
	{_hoops_SPPAP,			_hoops_GRRCR ("slant"),			 	_hoops_CIGHA, 1, true, &_hoops_IHPGGR},

	{_hoops_AHPAP,	_hoops_GRRCR ("even spacing"),	 	_hoops_RRSAP, 0, true},
	{_hoops_GIPAP,_hoops_GRRCR ("uniform spacing"),	_hoops_RRSAP, 0, true},
	{_hoops_PHPAP,		_hoops_GRRCR ("outline"),		 	_hoops_RRSAP, 0, true},
	{_hoops_PHPAP,		_hoops_GRRCR ("exteriors"),			_hoops_RRSAP, 0, true},
	{_hoops_PHPAP,		_hoops_GRRCR ("exterior"),			_hoops_RRSAP, 0, true},
	{_hoops_HHPAP,		_hoops_GRRCR ("underline"),		 	_hoops_RRSAP, 0, true},
	{_hoops_IHPAP,	_hoops_GRRCR ("strikethrough"),	 	_hoops_RRSAP, 0, true},
	{_hoops_IHPAP,	_hoops_GRRCR ("strike through"), 	_hoops_RRSAP, 0, true},
	{_hoops_IHPAP,	_hoops_GRRCR ("strike-through"), 	_hoops_RRSAP, 0, true},
	{_hoops_CHPAP,		_hoops_GRRCR ("overline"),		 	_hoops_RRSAP, 0, true},
	{_hoops_RIPAP,		_hoops_GRRCR ("fill edges"),	 	_hoops_RRSAP, 0, true},
	{_hoops_RIPAP,		_hoops_GRRCR ("filledges"),		 	_hoops_RRSAP, 0, true},
	{_hoops_AIPAP,			_hoops_GRRCR ("bold"),			 	_hoops_RRSAP, 0, true},
	{_hoops_PIPAP,			_hoops_GRRCR ("italic"),		 	_hoops_RRSAP, 0, true},
	{_hoops_HIPAP,		_hoops_GRRCR ("renderer"),		 	_hoops_GHAGA, -9, false, &_hoops_CIPGGR},
	{_hoops_CIPAP,		_hoops_GRRCR ("preference"),	 	_hoops_GHAGA, -9, false, &_hoops_ACPGGR},
	{_hoops_CIPAP,		_hoops_GRRCR ("text preference"),	_hoops_GHAGA, -9, false, &_hoops_ACPGGR},
};


local const _hoops_IGRCR _hoops_HCPGGR[] = {
	{true,		_hoops_GRRCR ("fixed"),			_hoops_RRRCR, 0, false},
	{false,		_hoops_GRRCR (""),				_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_ICPGGR = {
	_hoops_GGAPR (_hoops_HCPGGR),
	_hoops_HCPGGR,
};


#define _hoops_CCPGGR	-1
local const _hoops_IGRCR _hoops_SCPGGR[] = {
	{_hoops_GAGRP,				_hoops_GRRCR ("name"),			_hoops_PRRCR, -9999, false},
	{_hoops_RAGRP,				_hoops_GRRCR ("size"),			_hoops_CIGHA, 1, false, &_hoops_AHPGGR},
	{_hoops_AAGRP,	_hoops_GRRCR ("vertical offset"),_hoops_CIGHA, 1, true, &_hoops_AHPGGR},
	{_hoops_APGRP,	_hoops_GRRCR ("horizontal offset"),_hoops_CIGHA, 1, true, &_hoops_AHPGGR},
	{_hoops_IAGRP,				_hoops_GRRCR ("slant"),			_hoops_SPPCR, 1, true},
	{_hoops_CAGRP,		_hoops_GRRCR ("width scale"),	_hoops_SPPCR, 1, true},
	{_hoops_SAGRP,			_hoops_GRRCR ("rotation"),		_hoops_CIGHA, 1, true, &_hoops_ICPGGR},
	{_hoops_RPGRP,				_hoops_GRRCR ("color"),			_hoops_ARSAP, 1, true},
	{_hoops_PAGRP,			_hoops_GRRCR ("omitted"),		_hoops_RRSAP, 0, true},
	{_hoops_HAGRP,			_hoops_GRRCR ("invisible"),		_hoops_RRSAP, 0, true},
	{_hoops_CCPGGR,				_hoops_GRRCR ("all"),			_hoops_RRSAP, 0, false},
	{_hoops_CCPGGR,				_hoops_GRRCR ("everything"),	_hoops_RRSAP, 0, false},
};



GLOBAL_FUNCTION bool HI_Names_All_Equal (
	_hoops_AAPIR *		a,
	_hoops_AAPIR *		b) {

	while (a != null) {
		if (b == null) return false;

		if (a->key == b->key)
			if (!_hoops_RAHSR (a->name, b->name))
				return false;

		a = a->next;
		b = b->next;
	}

	return (b == null);
}

GLOBAL_FUNCTION bool HI_Font_Names_All_Equal (
	_hoops_IGPIR *		a,
	_hoops_IGPIR *		b) {

	while (a != null) {
		if (b == null) return false;

		if (a->_hoops_SSSGP != b->_hoops_SSSGP) return false;

		if (a->_hoops_SSSGP == GFN_SPECIFIED)
			if (!_hoops_RAHSR (a->specified, b->specified))
				return false;

		a = a->next;
		b = b->next;
	}

	return (b == null);
}

GLOBAL_FUNCTION void HI_Free_Font_Names (
	_hoops_IGPIR *		name) {
	_hoops_IGPIR *		next;

	do {
		next = name->next;
		if (name->_hoops_SSSGP == GFN_SPECIFIED) _hoops_RGAIR (name->specified);
		FREE (name, _hoops_IGPIR);
	} while ((name = next) != null);
}


local Attribute * _hoops_GSPGGR (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR) 
{
	_hoops_AGPIR const *	_hoops_RSPGGR = (_hoops_AGPIR const *)_hoops_CPACR;
	_hoops_AGPIR alter *	_hoops_ASPGGR = (_hoops_AGPIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_RSPGGR != null &&

		(_hoops_ASPGGR->_hoops_HAICA == _hoops_RSPGGR->_hoops_HAICA &&
		 _hoops_ASPGGR->_hoops_CPGRP == _hoops_RSPGGR->_hoops_CPGRP) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_RPPAP) ||
		 (_hoops_ASPGGR->_hoops_GHGRP == _hoops_RSPGGR->_hoops_GHGRP &&
		  _hoops_ASPGGR->size == _hoops_RSPGGR->size)) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_APPAP) ||
		 (_hoops_ASPGGR->_hoops_SSPAP == _hoops_RSPGGR->_hoops_SSPAP &&
		  _hoops_ASPGGR->_hoops_ACPAP == _hoops_RSPGGR->_hoops_ACPAP)) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_PPPAP) ||
		 _hoops_ASPGGR->transform == _hoops_RSPGGR->transform) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_HPPAP) ||
		 _hoops_ASPGGR->rotation == _hoops_RSPGGR->rotation) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_IPPAP) ||
		 _hoops_ASPGGR->width_scale == _hoops_RSPGGR->width_scale) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_RHPAP) ||
		 _hoops_ASPGGR->_hoops_ICPAP == _hoops_RSPGGR->_hoops_ICPAP) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_SPPAP) ||
		 _hoops_ASPGGR->_hoops_IPGRP == _hoops_RSPGGR->_hoops_IPGRP) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_CPPAP) ||
		 (_hoops_ASPGGR->_hoops_GGHAP == _hoops_RSPGGR->_hoops_GGHAP &&
		  _hoops_ASPGGR->_hoops_PCPAP == _hoops_RSPGGR->_hoops_PCPAP)) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_GHPAP) ||
		 (_hoops_ASPGGR->_hoops_RGHAP == _hoops_RSPGGR->_hoops_RGHAP &&
		  _hoops_ASPGGR->_hoops_HCPAP == _hoops_RSPGGR->_hoops_HCPAP)) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_IIPAP) ||
		 _hoops_ASPGGR->_hoops_SGHAP == _hoops_RSPGGR->_hoops_SGHAP) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_HIPAP) ||
		 _hoops_ASPGGR->_hoops_ISPAP[0] == _hoops_RSPGGR->_hoops_ISPAP[0] &&
		 _hoops_ASPGGR->_hoops_ISPAP[1] == _hoops_RSPGGR->_hoops_ISPAP[1] &&
		 _hoops_ASPGGR->_hoops_CCPAP == _hoops_RSPGGR->_hoops_CCPAP &&
		 _hoops_ASPGGR->_hoops_AGHAP == _hoops_RSPGGR->_hoops_AGHAP) &&

		(!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_CIPAP) ||
		 _hoops_ASPGGR->_hoops_CSPAP[0] == _hoops_RSPGGR->_hoops_CSPAP[0] &&
		 _hoops_ASPGGR->_hoops_CSPAP[1] == _hoops_RSPGGR->_hoops_CSPAP[1] &&
		 _hoops_ASPGGR->_hoops_SCPAP == _hoops_RSPGGR->_hoops_SCPAP &&
		 _hoops_ASPGGR->_hoops_PGHAP == _hoops_RSPGGR->_hoops_PGHAP) &&

		(_hoops_ASPGGR->_hoops_HGPIR == null ||
		 HI_Font_Names_All_Equal (_hoops_ASPGGR->_hoops_HGPIR, _hoops_RSPGGR->_hoops_HGPIR)))
		return null;
	

	if (_hoops_RSPGGR != null) {
		/* _hoops_HASC _hoops_PSPGGR _hoops_GGR _hoops_CCA _hoops_HSPGGR */

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_RPPAP)) {
			_hoops_ASPGGR->_hoops_GHGRP = _hoops_RSPGGR->_hoops_GHGRP;
			_hoops_ASPGGR->size = _hoops_RSPGGR->size;
		}

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_APPAP)) {
			_hoops_ASPGGR->_hoops_SSPAP = _hoops_RSPGGR->_hoops_SSPAP;
			_hoops_ASPGGR->_hoops_ACPAP = _hoops_RSPGGR->_hoops_ACPAP;
		}

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_PPPAP)) 
			_hoops_ASPGGR->transform = _hoops_RSPGGR->transform;

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_HPPAP))
			_hoops_ASPGGR->rotation = _hoops_RSPGGR->rotation;

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_IPPAP))
			_hoops_ASPGGR->width_scale = _hoops_RSPGGR->width_scale;

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_RHPAP))
			_hoops_ASPGGR->_hoops_ICPAP = _hoops_RSPGGR->_hoops_ICPAP;

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_CPPAP)) {
			_hoops_ASPGGR->_hoops_GGHAP = _hoops_RSPGGR->_hoops_GGHAP;
			_hoops_ASPGGR->_hoops_PCPAP = _hoops_RSPGGR->_hoops_PCPAP;
		}

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_GHPAP)) {
			_hoops_ASPGGR->_hoops_RGHAP = _hoops_RSPGGR->_hoops_RGHAP;
			_hoops_ASPGGR->_hoops_HCPAP = _hoops_RSPGGR->_hoops_HCPAP;
		}

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_IIPAP))
			_hoops_ASPGGR->_hoops_SGHAP = _hoops_RSPGGR->_hoops_SGHAP;

		if (!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_SPPAP))
			_hoops_ASPGGR->_hoops_IPGRP = _hoops_RSPGGR->_hoops_IPGRP;

		if (BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_HPPAP) &&
			!BIT(_hoops_ASPGGR->_hoops_HAICA, _hoops_SHPAP)) {

			_hoops_ASPGGR->_hoops_CPGRP |= _hoops_RSPGGR->_hoops_CPGRP & ~_hoops_ASPGGR->_hoops_HAICA;
			_hoops_ASPGGR->_hoops_HAICA |= _hoops_RSPGGR->_hoops_HAICA;
			
			_hoops_ASPGGR->_hoops_CPGRP &= ~_hoops_SHPAP;
			_hoops_ASPGGR->_hoops_HAICA &= ~_hoops_SHPAP;
		}
		else {
			_hoops_ASPGGR->_hoops_CPGRP |= _hoops_RSPGGR->_hoops_CPGRP & ~_hoops_ASPGGR->_hoops_HAICA;
			_hoops_ASPGGR->_hoops_HAICA |= _hoops_RSPGGR->_hoops_HAICA;
		}

		if (_hoops_ASPGGR->_hoops_ISPAP[0] == -1)
			_hoops_ASPGGR->_hoops_ISPAP[0] = _hoops_RSPGGR->_hoops_ISPAP[0];
		if (_hoops_ASPGGR->_hoops_ISPAP[1] == -1)
			_hoops_ASPGGR->_hoops_ISPAP[1] = _hoops_RSPGGR->_hoops_ISPAP[1];

		if (_hoops_ASPGGR->_hoops_AGHAP == _hoops_SHGRP) {
			_hoops_ASPGGR->_hoops_CCPAP = _hoops_RSPGGR->_hoops_CCPAP;
			_hoops_ASPGGR->_hoops_AGHAP = _hoops_RSPGGR->_hoops_AGHAP;
		}

		if (_hoops_ASPGGR->_hoops_CSPAP[0] == -1)
			_hoops_ASPGGR->_hoops_CSPAP[0] = _hoops_RSPGGR->_hoops_CSPAP[0];
		if (_hoops_ASPGGR->_hoops_CSPAP[1] == -1)
			_hoops_ASPGGR->_hoops_CSPAP[1] = _hoops_RSPGGR->_hoops_CSPAP[1];

		if (_hoops_ASPGGR->_hoops_PGHAP == _hoops_SHGRP) {
			_hoops_ASPGGR->_hoops_SCPAP = _hoops_RSPGGR->_hoops_SCPAP;
			_hoops_ASPGGR->_hoops_PGHAP = _hoops_RSPGGR->_hoops_PGHAP;
		}

		if (_hoops_ASPGGR->_hoops_HGPIR == null && _hoops_RSPGGR->_hoops_HGPIR != null)
			_hoops_ASPGGR->_hoops_HGPIR = HI_Copy_Font_Names (_hoops_RSPGGR->_hoops_HGPIR);
	}

	if (BIT(_hoops_ASPGGR->_hoops_HAICA & _hoops_ASPGGR->_hoops_CPGRP, _hoops_AIPAP)){
		_hoops_IGPIR *	_hoops_PAGR = _hoops_ASPGGR->_hoops_HGPIR;
		while (_hoops_PAGR != null) {
			if (_hoops_PAGR->_hoops_SSSGP == GFN_SANS_SERIF) 
				_hoops_PAGR->_hoops_SSSGP = _hoops_GIIGI;
			if (_hoops_PAGR->_hoops_SSSGP == GFN_TYPEWRITER) 
				_hoops_PAGR->_hoops_SSSGP = _hoops_RIIGI;
			if (_hoops_PAGR->_hoops_SSSGP == GFN_ROMAN) 
				_hoops_PAGR->_hoops_SSSGP = _hoops_AIIGI;
			_hoops_PAGR = _hoops_PAGR->next;
		}
	}

	return _hoops_ASPGGR;
}




local _hoops_SRHSR system_default = _hoops_GRRCR("system default");
local _hoops_SRHSR sans_serif = _hoops_GRRCR ("sans serif");
local _hoops_SRHSR typewriter = _hoops_GRRCR ("typewriter");
local _hoops_SRHSR roman = _hoops_GRRCR ("roman");
local _hoops_SRHSR stroked = _hoops_GRRCR ("stroked");

local bool _hoops_ISPGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	_hoops_AGPIR &				_hoops_CAICA) 
{

	/* _hoops_ARP _hoops_CIGS _hoops_HSH */
	ZERO_STRUCT (&_hoops_CAICA, _hoops_AGPIR);
	_hoops_CAICA._hoops_ISPAP[0] = _hoops_CAICA._hoops_ISPAP[1] = -1;
	_hoops_CAICA._hoops_CSPAP[0] = _hoops_CAICA._hoops_CSPAP[1] = -1;

	_hoops_HIACR (_hoops_CAPPP, _hoops_PCPGGR);

	Option_Value *	option_list;

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_CAPPP), &option_list, _hoops_SIACR)) 
		return false;

	Option_Value *	option;
	bool	error = false;

	if ((option = option_list) != null) do {
		_hoops_SAPAP	which = (_hoops_SAPAP)option->type->id;

		_hoops_CAICA._hoops_HAICA |= which;
		if (option->_hoops_GCACR)
			_hoops_CAICA._hoops_CPGRP &= ~which;
		else
			_hoops_CAICA._hoops_CPGRP |= which;

		switch (option->type->id) {
			case _hoops_GPPAP: {
				_hoops_HCRPR *			name = &option->value._name[0];
				int				count = option->_hoops_AIPCR;
				_hoops_IGPIR **	_hoops_PISGH = &_hoops_CAICA._hoops_HGPIR;

				/* _hoops_RPP _hoops_RH _hoops_IPSP _hoops_ASGPH "_hoops_CSPGGR" _hoops_RRPC... */
				if (_hoops_CAICA._hoops_HGPIR != null) {
					HI_Free_Font_Names (_hoops_CAICA._hoops_HGPIR);
					_hoops_CAICA._hoops_HGPIR = null;
				}

				if (count == 0) {		/* _hoops_PAH _hoops_RGR _hoops_SGIPR _hoops_IHPS? */
					HE_ERROR (HEC_TEXT, HES_NULL_INPUT, "At least one value must be specified for 'Names'");
					error = true;
				}
				else do {
					_hoops_IGPIR *		_hoops_PAGR;

					ZALLOC (_hoops_PAGR, _hoops_IGPIR);
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
						error = true;
						_hoops_PAGR->_hoops_SSSGP = GFN_STROKED;		/* (_hoops_PA) */
					}
					else {
						_hoops_PAGR->_hoops_SSSGP = GFN_SPECIFIED;

						/*** _hoops_SRAI _hoops_RH _hoops_RSIRR _hoops_HRII _hoops_HSAR _hoops_IPS _hoops_SCH ***/
						_hoops_PAGR->specified.length = name->length;
						_hoops_PAGR->specified.text = name->text;
						name->length = 0;
					}

					++name;
				} while (--count > 0);

				*_hoops_PISGH = null;
			}	break;

			case _hoops_RPPAP: {
				_hoops_CAICA.size = option->value._hoops_RRRHA[0].value;
				_hoops_CAICA._hoops_GHGRP = (_hoops_SPGRP)option->value._hoops_RRRHA[0]._hoops_HHP;
				if (_hoops_CAICA.size < 0.0f) {
					HE_ERROR (HEC_TEXT, HES_INVALID_SIZE, "Character size must be positive");
					error = true;
				}
			}	break;

			case _hoops_APPAP: {
				if (option->_hoops_GCACR) {
					_hoops_CAICA._hoops_ACPAP = 0.0f;
					_hoops_CAICA._hoops_SSPAP = GSU_POINTS;
				}
				else {
					_hoops_CAICA._hoops_ACPAP = option->value._hoops_RRRHA[0].value;
					_hoops_CAICA._hoops_SSPAP = (_hoops_SPGRP)option->value._hoops_RRRHA[0]._hoops_HHP;
					if (_hoops_CAICA._hoops_ACPAP < 0.0f) {
						HE_ERROR (HEC_TEXT, HES_INVALID_SIZE, "Character size tolerance must be non-negative");
						error = true;
					}
				}
			}	break;

			case _hoops_CPPAP: {
				if (option->_hoops_GCACR) {
					_hoops_CAICA._hoops_PCPAP = 0.0f;
					_hoops_CAICA._hoops_GGHAP = GSU_POINTS;
				}
				else {
					_hoops_CAICA._hoops_PCPAP = option->value._hoops_RRRHA[0].value;
					_hoops_CAICA._hoops_GGHAP = (_hoops_SPGRP) option->value._hoops_RRRHA[0]._hoops_HHP;
				}
			}	break;

			case _hoops_GHPAP: {
				if (option->_hoops_GCACR) {
					_hoops_CAICA._hoops_HCPAP = 0.0f;
					_hoops_CAICA._hoops_RGHAP = GSU_POINTS;
				}
				else {
					_hoops_CAICA._hoops_HCPAP = option->value._hoops_RRRHA[0].value;
					_hoops_CAICA._hoops_RGHAP = (_hoops_SPGRP) option->value._hoops_RRRHA[0]._hoops_HHP;
				}
			}	break;

			case _hoops_IIPAP: {
				if (option->_hoops_GCACR)
					_hoops_CAICA._hoops_SGHAP = _hoops_HGHAP;
				else if (option->_hoops_AIPCR == 0)
					_hoops_CAICA._hoops_SGHAP = _hoops_IGHAP;
				else
					_hoops_CAICA._hoops_SGHAP = option->value.option_list->type->id;
			}	break;

			case _hoops_HPPAP: {
				if (option->_hoops_GCACR) {
					_hoops_CAICA.rotation = 0.0f;
				}
				else {
					_hoops_HCRPR			*name = &option->value._name[0];

					if (name->length == 11 &&
						name->text[0]  == 'f' &&
						name->text[1]  == 'o' &&
						name->text[2]  == 'l' &&
						name->text[3]  == 'l' &&
						name->text[4]  == 'o' &&
						name->text[5]  == 'w' &&
						(name->text[6] == ' ' ||
						 name->text[6] == '-')&&
						name->text[7]  == 'p' &&
						name->text[8]  == 'a' &&
						name->text[9]  == 't' &&
						name->text[10] == 'h') {

						_hoops_CAICA._hoops_HAICA |= _hoops_SHPAP;
						_hoops_CAICA._hoops_CPGRP |= _hoops_SHPAP;
					}
					else {		/* _hoops_HPPR _hoops_IH _hoops_IRS _hoops_AIIC */
						char			*_hoops_RPPA = name->text;
						float			value;

						if (HI_Scan_Float (_hoops_RIGC, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) != null) {
							HE_ERROR2 (HEC_TEXT, HES_SYNTAX_ERROR,
									   Sprintf_S (null, "Error parsing rotation value '%s' -", name),
									   "should be either 'follow path' or an angle");
							error = true;
						}
						else {
							if (value > 1e7f || value < -1e7f) {
								HE_WARNING (HEC_TEXT, HES_BAD_ANGLE,"The angle is too extreme");
								value = 0.0f;
							}
							else if (value < 0.0f) {
								int _hoops_SSPGGR = (int)(-value / 360.0f + 1);
								value += 360.0f * _hoops_SSPGGR;
							}
							else {
								int _hoops_SSPGGR = (int)(value / 360.0f);
								value -= 360.0f * _hoops_SSPGGR;
							}
							_hoops_CAICA.rotation = value;
						}
					}
				}
			}	break;

			case _hoops_IPPAP: {
				if (option->_hoops_GCACR) {
					_hoops_CAICA.width_scale = 1.0f;
				}
				else {
					_hoops_CAICA.width_scale = option->value._hoops_PIPCR[0];
#if 0
					if (_hoops_CAICA.width_scale <= 0.0f) {
						HE_ERROR (HEC_TEXT, HES_BAD_TEXT_SCALE_FACTOR, "Character width scale factor must be positive");
						error = true;
					}
#endif
				}
			}	break;

			case _hoops_RHPAP: {
				_hoops_CAICA._hoops_ICPAP = option->value._hoops_PIPCR[0];
			}	break;

			case _hoops_SPPAP: {
				if (option->_hoops_GCACR) {
					_hoops_CAICA._hoops_IPGRP = 0.0f;
				}
				else {
					_hoops_CAICA._hoops_IPGRP = option->value._hoops_RRRHA[0].value;
					if (Abs (_hoops_CAICA._hoops_IPGRP) > 85.0f) {
						HE_ERROR (HEC_TEXT, HES_BAD_ANGLE, "Slant angle is unreasonable");
						error = true;
					}
				}
			}	break;

			case _hoops_PPPAP: {
				if (option->_hoops_GCACR)
					_hoops_CAICA.transform = FT_NONE;
				else if (option->_hoops_AIPCR == 0)
					_hoops_CAICA.transform = FT_FULL;
				else
					_hoops_CAICA.transform =(_hoops_GSPAP)option->value.option_list[0].type->id;
			}	break;

			case _hoops_HIPAP: {
				Option_Value		*_hoops_AHSAA = option->value.option_list;

				if (_hoops_AHSAA == null) {
					HE_ERROR (HEC_TEXT, HES_NULL_INPUT, "At least one value must be specified for 'renderer'");
					error = true;
				}
				else do {
					switch (_hoops_AHSAA->type->id) {
						case _hoops_AIPGGR:
							if (_hoops_AHSAA->_hoops_GCACR) {
								_hoops_CAICA._hoops_CCPAP = 0.0f;
								_hoops_CAICA._hoops_AGHAP = GSU_POINTS;
							}
							else {
								_hoops_CAICA._hoops_CCPAP = _hoops_AHSAA->value._hoops_RRRHA[0].value;
								_hoops_CAICA._hoops_AGHAP = _hoops_AHSAA->value._hoops_RRRHA[0]._hoops_HHP;
							}
							break;

						case _hoops_GIPGGR:
							_hoops_CAICA._hoops_ISPAP[0] = (_hoops_GSPAP)_hoops_AHSAA->value.option_list->type->id;
							break;
						case _hoops_RIPGGR:
							_hoops_CAICA._hoops_ISPAP[1] = (_hoops_GSPAP)_hoops_AHSAA->value.option_list->type->id;
							break;

						default:
							_hoops_CAICA._hoops_ISPAP[0] =
								_hoops_CAICA._hoops_ISPAP[1] =
									(_hoops_GSPAP)_hoops_AHSAA->type->id;
					}
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}	break;

			case _hoops_CIPAP: {
				Option_Value *	_hoops_AHSAA = option->value.option_list;

				if (_hoops_AHSAA == null) {
					HE_ERROR (HEC_TEXT, HES_NULL_INPUT, "At least one value must be specified for 'preference'");
					error = true;
				}
				else do {
					switch (_hoops_AHSAA->type->id) {
						case _hoops_AIPGGR:
							if (_hoops_AHSAA->_hoops_GCACR) {
								_hoops_CAICA._hoops_SCPAP = 0.0f;
								_hoops_CAICA._hoops_PGHAP = GSU_POINTS;
							}
							else {
								_hoops_CAICA._hoops_SCPAP = _hoops_AHSAA->value._hoops_RRRHA[0].value;
								_hoops_CAICA._hoops_PGHAP = _hoops_AHSAA->value._hoops_RRRHA[0]._hoops_HHP;
							}
							break;

						case _hoops_GIPGGR:
							_hoops_CAICA._hoops_CSPAP[0] = (_hoops_RCPAP)_hoops_AHSAA->value.option_list->type->id;
							break;
						case _hoops_RIPGGR:
							_hoops_CAICA._hoops_CSPAP[1] = (_hoops_RCPAP)_hoops_AHSAA->value.option_list->type->id;
							break;

						default:
							_hoops_CAICA._hoops_CSPAP[0] =
								_hoops_CAICA._hoops_CSPAP[1] =
									(_hoops_RCPAP)_hoops_AHSAA->type->id;
					}
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}	break;

			case _hoops_AIPAP:{

				_hoops_IGPIR *	_hoops_PAGR = _hoops_CAICA._hoops_HGPIR;

				/* _hoops_RPP _hoops_RH _hoops_IPSP _hoops_ASGPH "_hoops_CSPGGR" _hoops_RRPC... */
				if (!option->_hoops_GCACR){
					while ( _hoops_PAGR  != null) {
		
						if (_hoops_PAGR->_hoops_SSSGP == GFN_SANS_SERIF) 
							_hoops_PAGR->_hoops_SSSGP = _hoops_GIIGI;
						if (_hoops_PAGR->_hoops_SSSGP == GFN_TYPEWRITER) 
							_hoops_PAGR->_hoops_SSSGP = _hoops_RIIGI;
						if (_hoops_PAGR->_hoops_SSSGP == GFN_ROMAN) 
							_hoops_PAGR->_hoops_SSSGP = _hoops_AIIGI;
						
						_hoops_PAGR = _hoops_PAGR->next;
					}
				}
			} break;

			case _hoops_AHPAP:
			case _hoops_GIPAP:
			case _hoops_PHPAP:
			case _hoops_HHPAP:
			case _hoops_IHPAP:
			case _hoops_RIPAP:
			case _hoops_CHPAP: 
			case _hoops_PIPAP:{
				  /* _hoops_AGCR _hoops_CHR _hoops_SAHR _hoops_IPARS _hoops_HSH */
			} break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Font option lookup");
				error = true;
			}
		}
	} while (!error && (option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	if (error) {

		if (_hoops_CAICA._hoops_HGPIR != null) {
			HI_Free_Font_Names (_hoops_CAICA._hoops_HGPIR);
			_hoops_CAICA._hoops_HGPIR = null;
		}

		return false;
	}

	return true;
}


GLOBAL_FUNCTION bool HI_Set_Text_Font (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item, 
	_hoops_AGPIR *					_hoops_CAICA)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_TEXT_FONT, _hoops_GSPGGR, _hoops_CAICA);
}

GLOBAL_FUNCTION bool HI_Unset_Text_Font (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item, 
	_hoops_AGPIR *					_hoops_CAICA)
{
	/* _hoops_RRGRA */
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(_hoops_CAICA);
	return false;
}


HC_INTERFACE void HC_CDECL HC_Set_Text_Font (
	char const *		list) 
{
	_hoops_PAPPR context("Set_Text_Font");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Text_Font (%S);\n", list));
	);

	bool		used = false;
	_hoops_AGPIR *	_hoops_CAICA;
	ZALLOC (_hoops_CAICA, _hoops_AGPIR);

	if (_hoops_ISPGGR (context, list, *_hoops_CAICA)) {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_SARPP)) != null) {
			used = HI_Set_Text_Font (context, target, _hoops_CAICA);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		if (_hoops_CAICA->_hoops_HGPIR != null)
			HI_Free_Font_Names (_hoops_CAICA->_hoops_HGPIR);
		FREE (_hoops_CAICA, _hoops_AGPIR);
	}

}


HC_INTERFACE void HC_CDECL HC_UnSet_Text_Font (void) 
{
	_hoops_PAPPR context("UnSet_Text_Font");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Text_Font ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SARPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context,  target, HK_TEXT_FONT);
		_hoops_IRRPR();
	}
}



HC_INTERFACE void HC_CDECL HC_MSet_Character_Attributes (
	Key					key, 
	int 				offset, 
	int 				count, 
	char const *		list) 
{
	_hoops_PAPPR context("MSet_Character_Attributes");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "MSet_Character_Attributes(LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d,", offset, count));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", list));
	);

	_hoops_HIACR (_hoops_RHRGI, _hoops_SCPGGR);


	Option_Value *		option_list;
	Option_Value *		option;
	bool				error = false;
	_hoops_HIHIR			_hoops_APHCR;

	if (!HI_Parse_Options (context, list, _hoops_CIACR (_hoops_RHRGI),
						   &option_list, _hoops_SIACR)) return;

	_hoops_RPPPR();

	_hoops_HACC * text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || 
		text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_KEY, "Key does not refer to valid text");
		goto Release;
	}

	if (count < 0) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	if (offset < 0) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET, "Offset is negative");
		goto Release;
	}

	if (count == 0) 
		goto Release;  /* _hoops_CPRSH */

	if (text->count < offset + count) {
		char            buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET,
			Sprintf_D (null, "Text only has %d characters -", text->count),
			Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
		goto Release;
	}

	/* _hoops_ARP _hoops_CIGS _hoops_HSH */
	ZERO_STRUCT (&_hoops_APHCR, _hoops_HIHIR);

	if ((option = option_list) != null) do {
		_hoops_SAPAP	which = (_hoops_SAPAP)option->type->id;

		_hoops_APHCR._hoops_HAICA |= which;
		if (option->_hoops_GCACR)
			_hoops_APHCR._hoops_CPGRP &= ~which;
		else
			_hoops_APHCR._hoops_CPGRP |= which;

		switch (option->type->id) {
			case _hoops_GAGRP: {
				_hoops_HCRPR *			name = &option->value._name[0];
				int				_hoops_GGHGGR = option->_hoops_AIPCR;
				_hoops_IGPIR **	_hoops_PISGH = &_hoops_APHCR._hoops_HGPIR;

				/* _hoops_RPP _hoops_RH _hoops_IPSP _hoops_ASGPH "_hoops_CSPGGR" _hoops_RRPC... */
				if (_hoops_APHCR._hoops_HGPIR != null) {
					HI_Free_Font_Names (_hoops_APHCR._hoops_HGPIR);
					_hoops_APHCR._hoops_HGPIR = null;
				}

				if (BIT(_hoops_APHCR._hoops_CPGRP, _hoops_GAGRP)) {
					if (_hoops_GGHGGR == 0) {		/* _hoops_PAH _hoops_RGR _hoops_SGIPR _hoops_IHPS? */
						HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_NULL_INPUT,
								  "At least one value must be specified for 'Names'");
						error = true;
					}
					else do {
						_hoops_IGPIR *		_hoops_PAGR;

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
							HE_ERROR (HEC_TEXT, HES_NULL_INPUT,
									  "Font names can't be blank/null");
							error = true;
							_hoops_PAGR->_hoops_SSSGP = GFN_STROKED;		/* (_hoops_PA) */
						}
						else {
							_hoops_PAGR->_hoops_SSSGP = GFN_SPECIFIED;

							/*** _hoops_SRAI _hoops_RH _hoops_RSIRR _hoops_HRII _hoops_HSAR _hoops_IPS _hoops_SCH ***/
							_hoops_PAGR->specified.length = name->length;
							_hoops_PAGR->specified.text = name->text;
							name->length = 0;
						}

						++name;
					} while (--_hoops_GGHGGR > 0);
				}

				*_hoops_PISGH = null;
			}	break;

			case _hoops_RAGRP: {
				if (BIT(_hoops_APHCR._hoops_CPGRP, _hoops_RAGRP)) {
					_hoops_APHCR.size = option->value._hoops_RRRHA[0].value;
					_hoops_APHCR._hoops_GHGRP = (_hoops_SPGRP)
										   option->value._hoops_RRRHA[0]._hoops_HHP;
					if (_hoops_APHCR.size <= 0.0f) {
						HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_SIZE,
								  "Character size must be positive");
						error = true;
					}
				}
			}	break;

			case _hoops_AAGRP: {
				if (BIT(_hoops_APHCR._hoops_CPGRP, _hoops_AAGRP)) {
					_hoops_APHCR._hoops_HPGRP = option->value._hoops_RRRHA[0].value;
					_hoops_APHCR._hoops_RHGRP = (_hoops_SPGRP)
										   option->value._hoops_RRRHA[0]._hoops_HHP;
				}
			}	break;

			case _hoops_APGRP: {
				if (BIT(_hoops_APHCR._hoops_CPGRP, _hoops_APGRP)) {
					_hoops_APHCR._hoops_PPGRP = option->value._hoops_RRRHA[0].value;
					_hoops_APHCR._hoops_AHGRP = (_hoops_SPGRP)
										   option->value._hoops_RRRHA[0]._hoops_HHP;
				}
			}	break;

			case _hoops_IAGRP: {
				if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_IAGRP)) {
					_hoops_APHCR._hoops_CPGRP |= _hoops_IAGRP;
					_hoops_APHCR._hoops_IPGRP = 0.0f;
				}
				else
					_hoops_APHCR._hoops_IPGRP = option->value._hoops_PIPCR[0];
			}	break;

			case _hoops_CAGRP: {
				if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_CAGRP)) {
					_hoops_APHCR._hoops_CPGRP |= _hoops_CAGRP;
					_hoops_APHCR.width_scale = 1.0f;
				}
				else
					_hoops_APHCR.width_scale = option->value._hoops_PIPCR[0];
			}	break;

			case _hoops_SAGRP: {
				if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_SAGRP)) {
					_hoops_APHCR.rotation = 0.0f;
					_hoops_APHCR._hoops_HAICA |= _hoops_GPGRP;
					_hoops_APHCR._hoops_CPGRP |= _hoops_SAGRP;
				}
				else {
					_hoops_APHCR.rotation = option->value._hoops_RRRHA[0].value;
					if (option->value._hoops_RRRHA[0]._hoops_HHP) {
						_hoops_APHCR._hoops_HAICA |= _hoops_GPGRP;
					}
				}
			}	break;

			case _hoops_RPGRP: {
				Named_Material			_hoops_GGPRA;

				ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
				if (!HI_Evaluate_Color (context, &option->value._name[0], &_hoops_GGPRA, 0, false)) {
					/* (_hoops_RIHH _hoops_AIAH _hoops_CRPPR) */
					HI_Free_Material_Names (&_hoops_GGPRA, 1);
					return;
				}

				/* _hoops_HGI _hoops_RRGR _hoops_IHCI _hoops_RH _hoops_APIR/_hoops_HH _hoops_IPPHR _hoops_SGS _hoops_CSAP
				** _hoops_CRPRA _hoops_GGSR _hoops_CRGR _hoops_SRPRA _hoops_IAPR _hoops_IS _hoops_RH _hoops_GCRRA _hoops_HRPR.
				*/
				if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
					_hoops_GGPRA._hoops_SCA != null) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */
					/* _hoops_RIHH */
					HI_Free_Material_Names (&_hoops_GGPRA, 1);
					return;
				}

				HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_APHCR.color);
				HI_Free_Material_Names (&_hoops_GGPRA, 1);
			}	break;

			case _hoops_PAGRP:
			case _hoops_HAGRP: {
				  /* _hoops_AGCR _hoops_CHR _hoops_SAHR _hoops_IPARS _hoops_HSH */
			} break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Character attribute option lookup");
				error = true;
			}
		}
	} _hoops_RGGA (error || (option = option->next) == null);

	HI_Free_Option_List (context, option_list);

	if (!error) {
		bool	_hoops_CCCIR = false;

		if (!text->_hoops_PIHIR)
			ZALLOC_ARRAY(text->_hoops_PIHIR, text->count, _hoops_HIHIR);

		for (int i = offset; i < offset+count; i++) {
			_hoops_HIHIR *	_hoops_RGHGGR = &text->_hoops_PIHIR[i];
			bool			_hoops_AGHGGR = false;

			if (_hoops_RGHGGR->_hoops_HAICA != 0)
				_hoops_AGHGGR = true; 

			if ((_hoops_APHCR._hoops_HAICA == _hoops_RGHGGR->_hoops_HAICA &&
				 _hoops_APHCR._hoops_CPGRP == _hoops_RGHGGR->_hoops_CPGRP) &&

				(!BIT(_hoops_APHCR._hoops_HAICA, _hoops_RPPAP) ||
				  _hoops_APHCR._hoops_GHGRP == _hoops_RGHGGR->_hoops_GHGRP &&
				  _hoops_APHCR.size == _hoops_RGHGGR->size) &&

				(!BIT(_hoops_APHCR._hoops_HAICA, _hoops_AAGRP) ||
				  _hoops_APHCR._hoops_RHGRP == _hoops_RGHGGR->_hoops_RHGRP &&
				  _hoops_APHCR._hoops_HPGRP == _hoops_RGHGGR->_hoops_HPGRP) &&

				(!BIT(_hoops_APHCR._hoops_HAICA, _hoops_APGRP) ||
				  _hoops_APHCR._hoops_AHGRP == _hoops_RGHGGR->_hoops_AHGRP &&
				  _hoops_APHCR._hoops_PPGRP == _hoops_RGHGGR->_hoops_PPGRP) &&

				(!BIT(_hoops_APHCR._hoops_HAICA, _hoops_IAGRP) || _hoops_APHCR._hoops_IPGRP == _hoops_RGHGGR->_hoops_IPGRP) &&
				(!BIT(_hoops_APHCR._hoops_HAICA, _hoops_SAGRP) || _hoops_APHCR.rotation == _hoops_RGHGGR->rotation) &&
				(!BIT(_hoops_APHCR._hoops_HAICA, _hoops_CAGRP) || _hoops_APHCR.width_scale == _hoops_RGHGGR->width_scale) &&
				(!BIT(_hoops_APHCR._hoops_HAICA, _hoops_RPGRP) || _hoops_APHCR.color == _hoops_RGHGGR->color) &&

				(_hoops_APHCR._hoops_HGPIR == null ||
				 HI_Font_Names_All_Equal (_hoops_APHCR._hoops_HGPIR, _hoops_RGHGGR->_hoops_HGPIR))) {
				/*_hoops_ISAP _hoops_HGAS*/;
			}
			else {
				_hoops_RGHGGR->_hoops_HAICA |= _hoops_APHCR._hoops_HAICA;
				_hoops_RGHGGR->_hoops_CPGRP |= _hoops_APHCR._hoops_CPGRP;

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_GAGRP)) {
					if (_hoops_RGHGGR->_hoops_HGPIR != null) {
						HI_Free_Font_Names(_hoops_RGHGGR->_hoops_HGPIR);
						_hoops_RGHGGR->_hoops_HGPIR = null;
					}

					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_GAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_GAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_GAGRP;
					}
					else {
						/* _hoops_IPS _hoops_CCAH _hoops_RPPCR */
						_hoops_RGHGGR->_hoops_HGPIR = HI_Copy_Font_Names(_hoops_APHCR._hoops_HGPIR);
					}
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_RAGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_RAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_RAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_RAGRP;
					}
					else {
						_hoops_RGHGGR->_hoops_GHGRP = _hoops_APHCR._hoops_GHGRP;
						_hoops_RGHGGR->size = _hoops_APHCR.size;	
					}
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_AAGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_AAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_AAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_AAGRP;
					}
					else {
						_hoops_RGHGGR->_hoops_RHGRP = _hoops_APHCR._hoops_RHGRP;
						_hoops_RGHGGR->_hoops_HPGRP = _hoops_APHCR._hoops_HPGRP;
					}
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_APGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_APGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_APGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_APGRP;
					}
					else {
						_hoops_RGHGGR->_hoops_AHGRP = _hoops_APHCR._hoops_AHGRP;
						_hoops_RGHGGR->_hoops_PPGRP = _hoops_APHCR._hoops_PPGRP;
					}
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_RPGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_RPGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_RPGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_RPGRP;
					}
					else
						_hoops_RGHGGR->color = _hoops_APHCR.color;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_IAGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_IAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_IAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_IAGRP;
					}
					else
						_hoops_RGHGGR->_hoops_IPGRP = _hoops_APHCR._hoops_IPGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_CAGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_CAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_CAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_CAGRP;
					}
					else
						_hoops_RGHGGR->width_scale = _hoops_APHCR.width_scale;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_SAGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_SAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_SAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_SAGRP;
					}
					else
						_hoops_RGHGGR->rotation = _hoops_APHCR.rotation;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_PAGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_PAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_PAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_PAGRP;
					}
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_HAGRP)) {
					if (!BIT(_hoops_APHCR._hoops_CPGRP, _hoops_HAGRP)) {
						_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_HAGRP;
						_hoops_RGHGGR->_hoops_CPGRP &= ~_hoops_HAGRP;
					}
				}
				/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
				_hoops_CCCIR = true;
			}

			if (_hoops_RGHGGR->_hoops_HAICA != 0 && !_hoops_AGHGGR)
				text->_hoops_PHGRP++;
			
			if (_hoops_RGHGGR->_hoops_HAICA == 0 && _hoops_AGHGGR)
				text->_hoops_PHGRP--;
			
		}

		if (_hoops_CCCIR)
			_hoops_SASIR (context, text, _hoops_GPSIR|_hoops_RPSIR);

		/* _hoops_HRGR _hoops_CPS _hoops_IPPRA */
		if (text->_hoops_PHGRP == 0) {
			FREE_ARRAY(text->_hoops_PIHIR, text->count, _hoops_HIHIR);
			text->_hoops_PIHIR = null;
		}
	}
		
	if (_hoops_APHCR._hoops_HGPIR != null)
		HI_Free_Font_Names(_hoops_APHCR._hoops_HGPIR);

Release:
	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Character_Attributes (
	Key 				key, 
	int 				offset, 
	int 				count, 
	char const *		list) 
{
	_hoops_PAPPR context("HC_MUnSet_Character_Attributes");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Character_Attributes(LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d,", offset, count));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", list));
	);

	_hoops_HIACR (_hoops_RHRGI, _hoops_SCPGGR);

	Option_Value *		option_list;
	Option_Value *		option;
	bool				error = false;
	_hoops_HIHIR			_hoops_APHCR;

	if (!HI_Parse_Options (context, list, _hoops_CIACR (_hoops_RHRGI),
						   &option_list, _hoops_CGPCR)) return;

	_hoops_RPPPR();

	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || 
		text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_KEY,"Key does not refer to valid text");
		goto Release;
	}

	if (count < 0) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	if (offset < 0) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET, "Offset is negative");
		goto Release;
	}

	if (count == 0) 
		goto Release;  /* _hoops_CPRSH */

	if (text->count < offset + count) {
		char            buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET,
			Sprintf_D (null,"Text only has %d characters -", text->count),
			Sprintf_DD (buf,"can't change %d of them at offset %d",count, offset));
		goto Release;
	}

	if (text->_hoops_PIHIR == null) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT,"Text has no character attributes");
		goto Release;
	}
	

	/* _hoops_ARP _hoops_CIGS _hoops_HSH */
	ZERO_STRUCT (&_hoops_APHCR, _hoops_HIHIR);

	if ((option = option_list) != null) do {
		_hoops_SAPAP		which = (_hoops_SAPAP)option->type->id;

		_hoops_APHCR._hoops_HAICA |= which;
		_hoops_APHCR._hoops_CPGRP |= which;

		switch (option->type->id) {
			case _hoops_CCPGGR: {
				_hoops_APHCR._hoops_CPGRP = 
					_hoops_APHCR._hoops_HAICA = 
						_hoops_GAGRP|_hoops_RAGRP|_hoops_AAGRP|_hoops_APGRP|_hoops_IAGRP|
						_hoops_PAGRP|_hoops_HAGRP|_hoops_CAGRP|_hoops_SAGRP|_hoops_RPGRP;
			} break;

			case _hoops_GAGRP:
			case _hoops_RAGRP:
			case _hoops_AAGRP:
			case _hoops_APGRP:
			case _hoops_IAGRP:
			case _hoops_CAGRP:
			case _hoops_SAGRP:
			case _hoops_RPGRP:
			case _hoops_PAGRP:
			case _hoops_HAGRP: {
				  /* _hoops_AGCR _hoops_CHR _hoops_SAHR _hoops_IPARS _hoops_HSH */
			} break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Character attribute option lookup");
				error = true;
			}
		}
	} while (!error && (option = option->next) != null);

	HI_Free_Option_List (context, option_list);

	if (!error) {
		bool		_hoops_CCCIR = false;

		for (int i = offset; i < offset+count; i++) {
			_hoops_HIHIR *		_hoops_RGHGGR = &text->_hoops_PIHIR[i];
			bool				_hoops_AGHGGR = false;

			if (_hoops_RGHGGR->_hoops_HAICA != 0)
				_hoops_AGHGGR = true; 

			if ((_hoops_RGHGGR->_hoops_HAICA&_hoops_APHCR._hoops_HAICA) == 0) {
				/*_hoops_ISAP _hoops_HGAS*/;
			}
			else {
				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_GAGRP)) {
					if (_hoops_RGHGGR->_hoops_HGPIR != null) {
						HI_Free_Font_Names(_hoops_RGHGGR->_hoops_HGPIR);
						_hoops_RGHGGR->_hoops_HGPIR = null;
					}
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_GAGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_RAGRP)) {
					_hoops_RGHGGR->_hoops_GHGRP = 0;
					_hoops_RGHGGR->size = 0.0f;	
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_RAGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_AAGRP)) {
					_hoops_RGHGGR->_hoops_RHGRP = 0;
					_hoops_RGHGGR->_hoops_HPGRP = 0.0f;	
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_AAGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_APGRP)) {
					_hoops_RGHGGR->_hoops_AHGRP = 0;
					_hoops_RGHGGR->_hoops_PPGRP = 0.0f;	
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_APGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_IAGRP)) {
					_hoops_RGHGGR->_hoops_IPGRP = 0.0f;
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_IAGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_CAGRP)) {
					_hoops_RGHGGR->width_scale = 0.0f;
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_CAGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_SAGRP)) {
					_hoops_RGHGGR->rotation = 0.0f;
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_SAGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_RPGRP)) {
					_hoops_RGHGGR->color = _hoops_GPSR::_hoops_RPSR;
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_RPGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_PAGRP)) {
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_PAGRP;
				}

				if (BIT(_hoops_APHCR._hoops_HAICA, _hoops_HAGRP)) {
					_hoops_RGHGGR->_hoops_HAICA &= ~_hoops_HAGRP;
				}

				/* _hoops_HPCAR _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
				_hoops_CCCIR=true;
			}

			if (_hoops_RGHGGR->_hoops_HAICA == 0 && _hoops_AGHGGR)
				text->_hoops_PHGRP--;	
		}

		if (_hoops_CCCIR)
			_hoops_SASIR (context, text, _hoops_GPSIR|_hoops_RPSIR);

		/* _hoops_HRGR _hoops_CPS _hoops_IPPRA */
		if (text->_hoops_PHGRP == 0) {
			FREE_ARRAY(text->_hoops_PIHIR, text->count, _hoops_HIHIR);
			text->_hoops_PIHIR = null;
		}
	}

Release:
	_hoops_IRRPR();
}



#ifdef DISABLE_SHOW
#	ifdef DISABLE_METAFILE
#		define	_hoops_PGHGGR
#	endif
#endif

#ifndef _hoops_PGHGGR

/* _hoops_CACH _hoops_CHGRP._hoops_GSGGR */
extern char const *_hoops_GHIHH[];


/* _hoops_HGAPR _hoops_CHASR _hoops_RGCA _hoops_ARAGP _hoops_HCSGH _hoops_ICSGH _hoops_CCSGH _hoops_GGR _hoops_CHARP._hoops_GGHR */
local const char		_hoops_SCSGH[][16] = {
	"??",				/* (_hoops_HGHGGR) */
	"??",				/* (_hoops_GSSGH) */
	"system default",
	"sans serif",
	"typewriter",
	"roman",
	"stroked",
	"sans serif",
	"typewriter",
	"roman",
};

local	const char				_hoops_SSACR[] =
					"Return string won't fit in provided space";
#endif


GLOBAL_FUNCTION void HI_Show_Text_Font (
	_hoops_AGPIR			*_hoops_CAICA,
	char					*result,
	int						_hoops_RIAGA) {
#ifndef _hoops_PGHGGR
	char					*_hoops_ASAPR = result;
	char					*_hoops_PSAPR;

	if (_hoops_RIAGA == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_RIAGA;			/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

	if (_hoops_CAICA->_hoops_HGPIR != null) {
		_hoops_IGPIR	*_hoops_CAGRA = _hoops_CAICA->_hoops_HGPIR;

		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR,
						  (_hoops_CAGRA->next != null) ? "name=(" : "name=",
						  null);

		do {
			if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&_hoops_CAGRA->specified);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
		}
		_hoops_RGGA ((_hoops_CAGRA = _hoops_CAGRA->next) == null);

		if (_hoops_ASAPR != null) {
			if (_hoops_CAICA->_hoops_HGPIR->next != null) {	/* _hoops_RRP _hoops_IRS) _hoops_GGR _hoops_RH _hoops_SRHR */
				if (_hoops_ASAPR == _hoops_PSAPR) _hoops_ASAPR = null; /* _hoops_PPPPR'_hoops_RA _hoops_SIHRR */
				else {
					_hoops_ASAPR[-1] = ')';
					*_hoops_ASAPR++ = ',';
				}
			}
		}
	}

	
	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_RPPAP)) {
		if (_hoops_CAICA->_hoops_GHGRP != _hoops_SHGRP) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "size=%f", (void *)&_hoops_CAICA->size);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_GHGRP]);
		}
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_APPAP)) {
		if (_hoops_CAICA->_hoops_SSPAP != _hoops_SHGRP) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "size tolerance=%f", (void *)&_hoops_CAICA->_hoops_ACPAP);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_SSPAP]);
		}
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_PPPAP)) {
		switch (_hoops_CAICA->transform) {
			case FT_FULL: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "transforms,", null);
			}	break;

			case FT_NONE: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no transforms,", null);
			}	break;

			case FT_POSITION_ONLY: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "transforms=character position only,",
									null);
			}	break;

			case FT_POSITION_ADJUSTED: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "transforms=character position adjusted,",
									null);
			}	break;

			case FT_NOT_VALID:
					break;
		}
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_HPPAP)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_SHPAP)) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "rotation=follow path,", null);
		}
		else {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "rotation=%f,",
						  (void *)&_hoops_CAICA->rotation);
		}
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_IPPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "width scale=%f,",
						  (void *)&_hoops_CAICA->width_scale);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_SPPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "slant=%f degrees,",
						  (void *)&_hoops_CAICA->_hoops_IPGRP);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_PHPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_PHPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_HHPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_HHPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "underline,", null);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_IHPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_IHPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "strikethrough,", null);
	}
	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_RIPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_RIPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "fill edges,", null);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_CHPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_CHPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "overline,", null);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_AIPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_AIPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bold,", null);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_PIPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_PIPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "italic,", null);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_HIPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "renderer=", null);
		if (_hoops_CAICA->_hoops_ISPAP[0] == _hoops_CAICA->_hoops_ISPAP[1] &&
			_hoops_CAICA->_hoops_AGHAP == _hoops_SHGRP) {
			switch (_hoops_CAICA->_hoops_ISPAP[0]) {
				case _hoops_RSPAP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
				}	break;
				case _hoops_ASPAP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver,", null);
				}	break;
				case _hoops_PSPAP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "truetype,", null);
				}	break;
				case _hoops_HSPAP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "defined,", null);
				}	break;
			}
		}
		else {
			int		count = 0;

			if (_hoops_CAICA->_hoops_ISPAP[0] == _hoops_CAICA->_hoops_ISPAP[1] &&
				_hoops_CAICA->_hoops_ISPAP[0] != -1)
				++count;
			else {
				if (_hoops_CAICA->_hoops_ISPAP[0] != -1)
					++count;
				if (_hoops_CAICA->_hoops_ISPAP[1] != -1)
					++count;
			}
			if (_hoops_CAICA->_hoops_AGHAP != _hoops_SHGRP)
				++count;

			if (count > 1)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(", null);

			if (_hoops_CAICA->_hoops_ISPAP[0] == _hoops_CAICA->_hoops_ISPAP[1]) {
				switch (_hoops_CAICA->_hoops_ISPAP[0]) {
					case _hoops_RSPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
					}	break;
					case _hoops_ASPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver,", null);
					}	break;
					case _hoops_PSPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "truetype,", null);
					}	break;
					case _hoops_HSPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "defined,", null);
					}	break;
				}
			}
			else {
				if (_hoops_CAICA->_hoops_ISPAP[0] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "smaller=", null);
					switch (_hoops_CAICA->_hoops_ISPAP[0]) {
						case _hoops_RSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_ASPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver,", null);
						}	break;
						case _hoops_PSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "truetype,", null);
						}	break;
						case _hoops_HSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "defined,", null);
						}	break;
					}
				}
				if (_hoops_CAICA->_hoops_ISPAP[1] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "larger=", null);
					switch (_hoops_CAICA->_hoops_ISPAP[1]) {
						case _hoops_RSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_ASPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver,", null);
						}	break;
						case _hoops_PSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "truetype,", null);
						}	break;
						case _hoops_HSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "defined,", null);
						}	break;
					}
				}
			}
			if (_hoops_CAICA->_hoops_AGHAP != _hoops_SHGRP) {
				if (_hoops_CAICA->_hoops_CCPAP == 0.0f) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no cutoff,", null);
				}
				else {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "cutoff=%f", (void *)&_hoops_CAICA->_hoops_CCPAP);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_AGHAP]);
				}
			}

			if (_hoops_ASAPR != null)
				--_hoops_ASAPR;	/* _hoops_HASIR _hoops_HACH , */
			if (count > 1)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ")", null);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
		}
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_CIPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "preference=", null);
		if (_hoops_CAICA->_hoops_CSPAP[0] == _hoops_CAICA->_hoops_CSPAP[1] &&
			_hoops_CAICA->_hoops_PGHAP == _hoops_SHGRP) {
			switch (_hoops_CAICA->_hoops_CSPAP[0]) {
				case _hoops_GRHRP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
				}	break;
				case _hoops_CGHRP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bitmap,", null);
				}	break;
				case _hoops_SGHRP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
				}	break;
				case _hoops_RRHRP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "exterior,", null);
				}	break;
			}
		}
		else {
			int		count = 0;

			if (_hoops_CAICA->_hoops_CSPAP[0] == _hoops_CAICA->_hoops_CSPAP[1] &&
				_hoops_CAICA->_hoops_CSPAP[0] != -1)
				++count;
			else {
				if (_hoops_CAICA->_hoops_CSPAP[0] != -1)
					++count;
				if (_hoops_CAICA->_hoops_CSPAP[1] != -1)
					++count;
			}
			if (_hoops_CAICA->_hoops_PGHAP != _hoops_SHGRP)
				++count;

			if (count > 1)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(", null);

			if (_hoops_CAICA->_hoops_CSPAP[0] == _hoops_CAICA->_hoops_CSPAP[1]) {
				switch (_hoops_CAICA->_hoops_CSPAP[0]) {
					case _hoops_GRHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
					}	break;
					case _hoops_CGHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bitmap,", null);
					}	break;
					case _hoops_SGHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
					}	break;
					case _hoops_RRHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "exterior,", null);
					}	break;
				}
			}
			else {
				if (_hoops_CAICA->_hoops_CSPAP[0] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "smaller=", null);
					switch (_hoops_CAICA->_hoops_CSPAP[0]) {
						case _hoops_GRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_CGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bitmap,", null);
						}	break;
						case _hoops_SGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
						}	break;
						case _hoops_RRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "exterior,", null);
						}	break;
					}
				}
				if (_hoops_CAICA->_hoops_CSPAP[1] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "larger=", null);
					switch (_hoops_CAICA->_hoops_CSPAP[1]) {
						case _hoops_GRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_CGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bitmap,", null);
						}	break;
						case _hoops_SGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
						}	break;
						case _hoops_RRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "exterior,", null);
						}	break;
					}
				}
			}
			if (_hoops_CAICA->_hoops_PGHAP != _hoops_SHGRP) {
				if (_hoops_CAICA->_hoops_SCPAP == 0.0f) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no cutoff,", null);
				}
				else {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "cutoff=%f", (void *)&_hoops_CAICA->_hoops_SCPAP);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_PGHAP]);
				}
			}

			if (_hoops_ASAPR != null)
				--_hoops_ASAPR;	/* _hoops_HASIR _hoops_HACH , */
			if (count > 1)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ")", null);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
		}
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_GIPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_GIPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "uniform spacing,", null);
	}

#if 0
	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_AHPAP)) {
		if (!BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_AHPAP))
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "even spacing,", null);
	}
#endif

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_CPPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "extra space=%f", (void *)&_hoops_CAICA->_hoops_PCPAP);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_GGHAP]);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_GHPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "greeking limit=%f", (void *)&_hoops_CAICA->_hoops_HCPAP);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_RGHAP]);
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_IIPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "greeking mode=", null);
		switch (_hoops_CAICA->_hoops_SGHAP) {
			case _hoops_HGHAP: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "none,", null);
			}	break;
			case _hoops_IGHAP: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "lines,", null);
			}	break;
			case _hoops_CGHAP: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "box,", null);
			}	break;
		}
	}

	if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_RHPAP)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "line spacing=%f,",
						  (void *)&_hoops_CAICA->_hoops_ICPAP);
	}

	if (_hoops_ASAPR != null) {
		if (_hoops_ASAPR > result) --_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

		if (_hoops_RIAGA == -1) {	/* _hoops_IHRPR _hoops_IAHA _hoops_SRHR */
			if (_hoops_ASAPR == _hoops_PSAPR)
				_hoops_ASAPR = null;		/* _hoops_PPPPR'_hoops_RA _hoops_SIHRR */
			else
				*_hoops_ASAPR = '\0';
		}
		else					/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA _hoops_SRHR */
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';
	}

	if (_hoops_ASAPR == null)
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR); /* _hoops_SARS'_hoops_RA _hoops_SIHRR */
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Text_Font (
	char *			result) 
{
	_hoops_PAPPR context("Show_Text_Font");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_Font () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ICRPP)) != null) {

		_hoops_AGPIR *	_hoops_CAICA;
		if ((_hoops_CAICA = (_hoops_AGPIR *)HI_Find_Attribute (context, target, HK_TEXT_FONT)) != null) {
			HI_Show_Text_Font (_hoops_CAICA, result, -1);
			_hoops_HPRH (_hoops_CAICA);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Font (
	int					count,
	Key const *			keys,
	char *				result) 
{
	_hoops_PAPPR context("PShow_Net_Text_Font");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Text_Font () */\n");
	);

	_hoops_AGPIR *	_hoops_CAICA;
	if ((_hoops_CAICA = (_hoops_AGPIR *) HI_Find_Attribute_And_Lock(context, _hoops_ICRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Text_Font (_hoops_CAICA, result, -1);
		_hoops_HPRH (_hoops_CAICA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(result, -1, "", 0);
	
#endif
}

#endif



#ifndef DISABLE_SHOW

local _hoops_SRHSR	nname			= _hoops_GRRCR ("name");
local _hoops_SRHSR	nsize			= _hoops_GRRCR ("size");
local _hoops_SRHSR	_hoops_IGHGGR		= _hoops_GRRCR ("size tolerance");
local _hoops_SRHSR	_hoops_CGHGGR			= _hoops_GRRCR ("transform");
local _hoops_SRHSR	_hoops_SGHGGR			= _hoops_GRRCR ("transforms");
local _hoops_SRHSR	_hoops_GRHGGR			= _hoops_GRRCR ("rotation");
local _hoops_SRHSR	_hoops_RRHGGR			= _hoops_GRRCR ("width scale");
local _hoops_SRHSR	_hoops_ARHGGR			= _hoops_GRRCR ("slant");
local _hoops_SRHSR	_hoops_PRHGGR			= _hoops_GRRCR ("extra space");
local _hoops_SRHSR	_hoops_HRHGGR			= _hoops_GRRCR ("greeking limit");
local _hoops_SRHSR	_hoops_IRHGGR			= _hoops_GRRCR ("greeking mode");
local _hoops_SRHSR	_hoops_CRHGGR			= _hoops_GRRCR ("line spacing");
#if 0
local _hoops_SRHSR	_hoops_SRHGGR			= _hoops_GRRCR ("even spacing");
#endif
local _hoops_SRHSR	_hoops_GAHGGR		= _hoops_GRRCR ("uniform spacing");
local _hoops_SRHSR	_hoops_RAHGGR		= _hoops_GRRCR ("outline");
local _hoops_SRHSR	_hoops_AAHGGR		= _hoops_GRRCR ("underline");
local _hoops_SRHSR	_hoops_PAHGGR	= _hoops_GRRCR ("strikethrough");
local _hoops_SRHSR	_hoops_HAHGGR = _hoops_GRRCR ("fill edges");
local _hoops_SRHSR	_hoops_IAHGGR	= _hoops_GRRCR ("strike-through");
local _hoops_SRHSR	_hoops_CAHGGR	= _hoops_GRRCR ("strike through");
local _hoops_SRHSR	_hoops_SAHGGR		= _hoops_GRRCR ("overline");
local _hoops_SRHSR	_hoops_GPHGGR			= _hoops_GRRCR ("bold");
local _hoops_SRHSR	_hoops_RPHGGR			= _hoops_GRRCR ("italic");
local _hoops_SRHSR	_hoops_APHGGR		= _hoops_GRRCR ("renderer");
local _hoops_SRHSR	_hoops_PPHGGR		= _hoops_GRRCR ("preference");
local _hoops_SRHSR	_hoops_HPHGGR	= _hoops_GRRCR ("ptext reference");


local void _hoops_IPHGGR (
	_hoops_AGPIR			*_hoops_CAICA,
	char const				*which,
	char					*result,
	int						_hoops_RIAGA) {
	_hoops_HCRPR					_hoops_AHGHP;
	char					*_hoops_ASAPR = result;
	char					*_hoops_PSAPR;

	if (_hoops_RIAGA == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_RIAGA;			/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

	HI_Canonize_Chars (which, &_hoops_AHGHP);

	if (_hoops_RAHSR (_hoops_AHGHP, nname)) {
		if (_hoops_CAICA->_hoops_HGPIR != null) {
			_hoops_IGPIR	*_hoops_CAGRA = _hoops_CAICA->_hoops_HGPIR;

			if (_hoops_CAGRA->next != null) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(", null);

			do {
				if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
					if (_hoops_CAICA->_hoops_HGPIR->next != null)
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&_hoops_CAGRA->specified);
					else
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n,", (void *)&_hoops_CAGRA->specified);
				else
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
			}
			_hoops_RGGA ((_hoops_CAGRA = _hoops_CAGRA->next) == null);

			if (_hoops_ASAPR != null) {
				if (_hoops_CAICA->_hoops_HGPIR->next != null)
					_hoops_ASAPR[-1] = ')';
				else
					--_hoops_ASAPR;
			}
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, nsize)) {
		if (_hoops_CAICA->_hoops_GHGRP != _hoops_SHGRP) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_CAICA->size);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_GHGRP]);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_IGHGGR)) {
		if (_hoops_CAICA->_hoops_SSPAP != _hoops_SHGRP) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_CAICA->_hoops_ACPAP);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_SSPAP]);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_CGHGGR) || _hoops_RAHSR (_hoops_AHGHP, _hoops_SGHGGR)) {
		switch (_hoops_CAICA->transform) {
			case FT_FULL: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			}	break;

			case FT_NONE: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
			}	break;

			case FT_POSITION_ONLY: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "character position only", null);
			}	break;

			case FT_POSITION_ADJUSTED: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "character position adjusted", null);
			}	break;
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_GRHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_HPPAP)) {
			if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_SHPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "follow path", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_CAICA->rotation);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_RRHGGR)) {
		if (BIT(_hoops_CAICA->_hoops_HAICA, _hoops_IPPAP)) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f",
										(void *)&_hoops_CAICA->width_scale);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_CRHGGR)) {
		if (BIT(_hoops_CAICA->_hoops_HAICA, _hoops_RHPAP)) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f",
									(void *)&_hoops_CAICA->_hoops_ICPAP);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_ARHGGR)) {
		if (BIT(_hoops_CAICA->_hoops_HAICA, _hoops_SPPAP)) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f degrees",
										(void *)&_hoops_CAICA->_hoops_IPGRP);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_GAHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_GIPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_GIPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
#if 0
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_SRHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_AHPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_AHPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
#endif
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_RAHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_PHPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_PHPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_AAHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_HHPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_HHPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_PAHGGR) ||
			 _hoops_RAHSR (_hoops_AHGHP, _hoops_IAHGGR) ||
			 _hoops_RAHSR (_hoops_AHGHP, _hoops_CAHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_IHPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_IHPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_HAHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_RIPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_RIPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_SAHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_CHPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_CHPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_GPHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_AIPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_AIPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_RPHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_PIPAP)) {
			if (BIT (_hoops_CAICA->_hoops_CPGRP, _hoops_PIPAP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_APHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_HIPAP)) {
			if (_hoops_CAICA->_hoops_ISPAP[0] == _hoops_CAICA->_hoops_ISPAP[1] &&
				_hoops_CAICA->_hoops_AGHAP == _hoops_SHGRP) {
				switch (_hoops_CAICA->_hoops_ISPAP[0]) {
					case _hoops_RSPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default", null);
					}	break;
					case _hoops_ASPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver", null);
					}	break;
					case _hoops_PSPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "truetype", null);
					}	break;
					case _hoops_HSPAP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "defined", null);
					}	break;
				}
			}
			else {
				if (_hoops_CAICA->_hoops_ISPAP[0] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "smaller=", null);
					switch (_hoops_CAICA->_hoops_ISPAP[0]) {
						case _hoops_RSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_ASPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver,", null);
						}	break;
						case _hoops_PSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "truetype,", null);
						}	break;
						case _hoops_HSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "defined,", null);
						}	break;
					}
				}
				if (_hoops_CAICA->_hoops_ISPAP[1] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "larger=", null);
					switch (_hoops_CAICA->_hoops_ISPAP[1]) {
						case _hoops_RSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_ASPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver,", null);
						}	break;
						case _hoops_PSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "truetype,", null);
						}	break;
						case _hoops_HSPAP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "defined,", null);
						}	break;
					}
				}
				if (_hoops_CAICA->_hoops_AGHAP != _hoops_SHGRP) {
					if (_hoops_CAICA->_hoops_CCPAP == 0.0f) {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no cutoff,", null);
					}
					else {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "cutoff=%f", (void *)&_hoops_CAICA->_hoops_CCPAP);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_AGHAP]);
					}
				}

				if (_hoops_ASAPR != null)
					--_hoops_ASAPR;	/* _hoops_HASIR _hoops_HACH _hoops_RRCIR */
			}
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_PPHGGR) || _hoops_RAHSR (_hoops_AHGHP, _hoops_HPHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_CIPAP)) {
			if (_hoops_CAICA->_hoops_CSPAP[0] == _hoops_CAICA->_hoops_CSPAP[1] &&
				_hoops_CAICA->_hoops_PGHAP == _hoops_SHGRP) {
				switch (_hoops_CAICA->_hoops_CSPAP[0]) {
					case _hoops_GRHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
					}	break;
					case _hoops_CGHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bitmap,", null);
					}	break;
					case _hoops_SGHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
					}	break;
					case _hoops_RRHRP: {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "exterior,", null);
					}	break;
				}
			}
			else {
				if (_hoops_CAICA->_hoops_CSPAP[0] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "smaller=", null);
					switch (_hoops_CAICA->_hoops_CSPAP[0]) {
						case _hoops_GRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_CGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bitmap,", null);
						}	break;
						case _hoops_SGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
						}	break;
						case _hoops_RRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "exterior,", null);
						}	break;
					}
				}
				if (_hoops_CAICA->_hoops_CSPAP[1] != -1) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "larger=", null);
					switch (_hoops_CAICA->_hoops_CSPAP[1]) {
						case _hoops_GRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "default,", null);
						}	break;
						case _hoops_CGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bitmap,", null);
						}	break;
						case _hoops_SGHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "outline,", null);
						}	break;
						case _hoops_RRHRP: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "exterior,", null);
						}	break;
					}
				}
				if (_hoops_CAICA->_hoops_PGHAP != _hoops_SHGRP) {
					if (_hoops_CAICA->_hoops_SCPAP == 0.0f) {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no cutoff,", null);
					}
					else {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "cutoff=%f", (void *)&_hoops_CAICA->_hoops_SCPAP);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_PGHAP]);
					}
				}
			}

			if (_hoops_ASAPR != null)
				--_hoops_ASAPR;	/* _hoops_HASIR _hoops_HACH _hoops_RRCIR */
		}
	}
	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_PRHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_CPPAP)) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_CAICA->_hoops_PCPAP);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_GGHAP]);
		}
	}

	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_HRHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_GHPAP)) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_CAICA->_hoops_HCPAP);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", (void *)_hoops_GHIHH[(int)_hoops_CAICA->_hoops_RGHAP]);
		}
	}

	else if (_hoops_RAHSR (_hoops_AHGHP, _hoops_IRHGGR)) {
		if (BIT (_hoops_CAICA->_hoops_HAICA, _hoops_IIPAP)) {
			switch (_hoops_CAICA->_hoops_SGHAP) {
				case _hoops_HGHAP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "none", null);
				}	break;
				case _hoops_IGHAP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "lines", null);
				}	break;
				case _hoops_CGHAP: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "box", null);
				}	break;
			}
		}
	}

	else {
		HE_ERROR (HEC_TEXT, HES_INVALID_OPTION,
				  Sprintf_S (null, "'%s' is an unrecognized text font option", which));
	}

	_hoops_RGAIR (_hoops_AHGHP);

	if (_hoops_ASAPR == result)
		HE_ERROR (HEC_TEXT, HES_NO_LOCAL_SETTING,
				  Sprintf_SP (null, "'%s' has no setting in '%p'", which, _hoops_CAICA->owner));

	if (_hoops_ASAPR != null) {
		if (_hoops_RIAGA == -1) {	/* _hoops_IHRPR _hoops_IAHA _hoops_SRHR */
			if (_hoops_ASAPR == _hoops_PSAPR)
				_hoops_ASAPR = null;		/* _hoops_PPPPR'_hoops_RA _hoops_SIHRR */
			else
				*_hoops_ASAPR = '\0';
		}
		else					/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA _hoops_SRHR */
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';
	}

	if (_hoops_ASAPR == null)
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR); /* _hoops_SARS'_hoops_RA _hoops_SIHRR */
}
#endif




HC_INTERFACE void HC_CDECL HC_Show_One_Text_Font (
	char const *		which,
	char *				result) 
{
	_hoops_PAPPR context("Show_One_Text_Font");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Text_Font () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ICRPP)) != null) {

		_hoops_AGPIR *		_hoops_CAICA;
		if ((_hoops_CAICA = (_hoops_AGPIR *)HI_Find_Attribute (context, target, HK_TEXT_FONT)) != null) {
			_hoops_IPHGGR (_hoops_CAICA, which, result, -1);
			_hoops_HPRH (_hoops_CAICA);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Text_Font (
	int					count,
	Key const *			keys,
	char const *		which,
	char *				result) 
{
	_hoops_PAPPR context("PShow_One_Net_Text_Font");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Text_Font () */\n");
	);

	_hoops_AGPIR *	_hoops_CAICA;
	if ((_hoops_CAICA = (_hoops_AGPIR *) HI_Find_Attribute_And_Lock(context, _hoops_ICRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_IPHGGR (_hoops_CAICA, which, result, -1);
		_hoops_HPRH (_hoops_CAICA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(result, -1, "", 0);
#endif
}


#endif




HC_INTERFACE void HC_CDECL HC_MShow_Character_Attributes(
	Key			key, 
	int			offset, 
	int			count, 
	char *		result) 
{
	_hoops_PAPPR context("HC_MShow_Character_Attributes");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Character_Attributes () */\n");
	);


	if (result == null) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT, "Need result string");
		return;
	}

	_hoops_CSPPR();

	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || 
		text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_KEY, "Key does not refer to valid text");
	}
	else if (text->_hoops_PIHIR == null) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT, "Text has no character attributes");
	}
	else if (count < 0) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT, "Count is negative");
	}
	else if (offset < 0) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET, "Offset is negative");
	}
	else if (count == 0) {
		/* _hoops_CPRSH */
	}
	else if (text->count < offset + count) {
		char            buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET,
			Sprintf_D (null, "Text only has %d characters -", text->count),
			Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
	}
	else {

		char *		_hoops_ASAPR = result;
		char *		_hoops_PSAPR;

		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;

		for (int i = offset; i < offset+count; i++) {
			_hoops_HIHIR *		_hoops_RGHGGR = &text->_hoops_PIHIR[i];

			if (count > 1)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(", null);

			if (_hoops_RGHGGR->_hoops_HAICA != 0) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_GAGRP)) {
					if (_hoops_RGHGGR->_hoops_HGPIR != null) {
						_hoops_IGPIR	*_hoops_CAGRA = _hoops_RGHGGR->_hoops_HGPIR;

						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, (_hoops_CAGRA->next != null) ? "name=(" : "name=", null);

						do {
							if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&_hoops_CAGRA->specified);
							else
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
						} while ((_hoops_CAGRA = _hoops_CAGRA->next) != null);

						if (_hoops_ASAPR != null) {
							if (_hoops_RGHGGR->_hoops_HGPIR->next != null) {	/* _hoops_RRP _hoops_IRS) _hoops_GGR _hoops_RH _hoops_SRHR */

								if (_hoops_ASAPR == _hoops_PSAPR) 
									_hoops_ASAPR = null; /* _hoops_PPPPR'_hoops_RA _hoops_SIHRR */
								else {
									_hoops_ASAPR[-1] = ')';
									*_hoops_ASAPR++ = ',';
								}
							}
						}
					}
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_RAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "size=%f", (void *)&_hoops_RGHGGR->size);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_RGHGGR->_hoops_GHGRP]);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_AAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "vertical offset=%f", (void *)&_hoops_RGHGGR->_hoops_HPGRP);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_RGHGGR->_hoops_RHGRP]);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_APGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "horizontal offset=%f", (void *)&_hoops_RGHGGR->_hoops_PPGRP);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s,", (void *)_hoops_GHIHH[(int)_hoops_RGHGGR->_hoops_AHGRP]);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_IAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "slant=%f,", (void *)&_hoops_RGHGGR->_hoops_IPGRP);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_CAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "width scale=%f,", (void *)&_hoops_RGHGGR->width_scale);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_SAGRP)) {
					if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_GPGRP))
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "rotation=%f fixed,", (void *)&_hoops_RGHGGR->rotation);
					else
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "rotation=%f,", (void *)&_hoops_RGHGGR->rotation);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_RPGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "color=R=%f ", (void *)&_hoops_RGHGGR->color.red);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR,       "G=%f ", (void *)&_hoops_RGHGGR->color.green);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR,       "B=%f,", (void *)&_hoops_RGHGGR->color.blue);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_PAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "omitted,", null);
				}

				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_HAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "invisible,", null);
				}

				if (_hoops_ASAPR != null) {
					if (_hoops_ASAPR > result) --_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

					if (_hoops_ASAPR == _hoops_PSAPR)
						_hoops_ASAPR = null;		/* _hoops_PPPPR'_hoops_RA _hoops_SIHRR */
					else
						*_hoops_ASAPR = '\0';
				}

			}

			if (count > 1) {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ")", null);
				*_hoops_ASAPR = '\0';

				if (i < offset+count-1)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ", ", null);
			}
		}

		if (_hoops_ASAPR == null)
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR); /* _hoops_SARS'_hoops_RA _hoops_SIHRR */
	}

	_hoops_IRRPR();
#endif
}





HC_INTERFACE void HC_CDECL HC_Show_One_Character_Attribute (
	Key				key, 
	int				offset, 
	char const *	which, 
	char *			result) 
{
	_hoops_PAPPR context("HC_Show_One_Character_Attribut");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Character_Attribut () */\n");
	);

	if (result == null) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT, "Need result string");
		return;
	}

	Option_Value *		option_list = null;
	Option_Value *		option = null;

	_hoops_CSPPR();

	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || 
		text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_KEY, "Key does not refer to valid text");
	}
	else if (text->_hoops_PIHIR == null) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_COUNT, "Text has no character attributes");
	}
	else if (offset < 0) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET, "Offset is negative");
	}
	else if (text->count < offset) {
		char            buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_OFFSET,
			Sprintf_D (null, "Text only has %d characters -", text->count),
			Sprintf_D (buf, "can't show one them at offset %d", offset));
	}
	else if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_RHRGI),
		&option_list, _hoops_CGPCR|_hoops_PAPCA)) {
		/* _hoops_RIHH _hoops_PIIRH */
	} else {

		char *	_hoops_ASAPR = result;
		char *	_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		

		if ((option = option_list) != null) {
			_hoops_SAPAP	_hoops_CPHGGR = (_hoops_SAPAP)option->type->id;
			
			_hoops_HIHIR	*_hoops_RGHGGR = &text->_hoops_PIHIR[offset];

			if (BIT(_hoops_CPHGGR, _hoops_GAGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_GAGRP)) {
					if (_hoops_RGHGGR->_hoops_HGPIR != null) {
						_hoops_IGPIR	*_hoops_CAGRA = _hoops_RGHGGR->_hoops_HGPIR;

						do {
							if (_hoops_CAGRA->_hoops_SSSGP == GFN_SPECIFIED)
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&_hoops_CAGRA->specified);
							else
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s,", (void *)_hoops_SCSGH[_hoops_CAGRA->_hoops_SSSGP]);
						}
						_hoops_RGGA ((_hoops_CAGRA = _hoops_CAGRA->next) == null);
						--_hoops_ASAPR;
					}
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_RAGRP)) {			
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_RAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_RGHGGR->size);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", (void *)_hoops_GHIHH[(int)_hoops_RGHGGR->_hoops_GHGRP]);
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_AAGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_AAGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_RGHGGR->_hoops_HPGRP);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", (void *)_hoops_GHIHH[(int)_hoops_RGHGGR->_hoops_RHGRP]);
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_APGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_APGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_RGHGGR->_hoops_PPGRP);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", (void *)_hoops_GHIHH[(int)_hoops_RGHGGR->_hoops_AHGRP]);
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_IAGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_IAGRP)) {
					if (BIT(_hoops_RGHGGR->_hoops_CPGRP, _hoops_IAGRP))
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_RGHGGR->_hoops_IPGRP);
					else
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_CAGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_CAGRP)) {
					if (BIT(_hoops_RGHGGR->_hoops_CPGRP, _hoops_CAGRP))
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_RGHGGR->width_scale);
					else
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_SAGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_SAGRP)) {
					if (BIT(_hoops_RGHGGR->_hoops_CPGRP, _hoops_SAGRP))
						if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_GPGRP))
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f fixed", (void *)&_hoops_RGHGGR->rotation);
						else
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", (void *)&_hoops_RGHGGR->rotation);
					else
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "off", null);
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_RPGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_RPGRP)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "R=%f ", (void *)&_hoops_RGHGGR->color.red);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "G=%f ", (void *)&_hoops_RGHGGR->color.green);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "B=%f",  (void *)&_hoops_RGHGGR->color.blue);
				}
			}

			if (BIT(_hoops_CPHGGR, _hoops_PAGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_PAGRP))
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			}

			if (BIT(_hoops_CPHGGR, _hoops_HAGRP)) {
				if (BIT(_hoops_RGHGGR->_hoops_HAICA, _hoops_HAGRP))
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "on", null);
			}
			
			*_hoops_ASAPR = '\0';
		}

		HI_Free_Option_List (context, option_list);
	}

	_hoops_IRRPR();
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Character_Attribute_Cou (
	Key			key, 
	int *		count) 
{
	_hoops_PAPPR context("HC_Show_Character_Attribute_Count");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Character_Attribute_Count () */\n");
	);

	_hoops_CSPPR();

	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || 
		text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CHARACTER_ATTRIBUTE, HES_INVALID_KEY, "Key does not refer to valid text");
	}
	else
		*count = text->_hoops_PHGRP;

	_hoops_IRRPR();
#endif
}

GLOBAL_FUNCTION _hoops_IGPIR * HI_Copy_Font_Names (
	_hoops_IGPIR const      *in) {
	_hoops_IGPIR            *_hoops_SCGGGR;
	_hoops_IGPIR            **_hoops_PISGH = &_hoops_SCGGGR;

	_hoops_RGGA (in == null) {
		_hoops_IGPIR    *_hoops_PAGR;

		ALLOC (_hoops_PAGR, _hoops_IGPIR);
		*_hoops_PISGH = _hoops_PAGR;
		_hoops_PISGH = &_hoops_PAGR->next;
		if ((_hoops_PAGR->_hoops_SSSGP = in->_hoops_SSSGP) == GFN_SPECIFIED)
			HI_Copy_Name (&in->specified, &_hoops_PAGR->specified);
		else
			_hoops_PAGR->specified.length = 0;

		in = in->next;
	}

	*_hoops_PISGH = null;
	return _hoops_SCGGGR;
}




#ifndef DISABLE_SEARCH

#define _hoops_SPHGGR		0
#define _hoops_GHHGGR	1
#define _hoops_RHHGGR	2
#define _hoops_AHHGGR		3

local const _hoops_IGRCR _hoops_PHHGGR[] = {
	{_hoops_SPHGGR,		_hoops_GRRCR ("generic"), _hoops_RRRCR, 0, true},
	{_hoops_GHHGGR,		_hoops_GRRCR ("specific"), _hoops_RRRCR, 0, true},
	{_hoops_RHHGGR,		_hoops_GRRCR ("families"), _hoops_RRRCR, 0, true},
	{_hoops_RHHGGR,		_hoops_GRRCR ("family"), _hoops_RRRCR, 0, true},
	{_hoops_AHHGGR,		_hoops_GRRCR ("defined"), _hoops_RRRCR, 0, true},
};

#endif


HC_INTERFACE void HC_CDECL HC_Begin_Font_Search (
	char const *			display,
	char const *			filter) 
{
	_hoops_PAPPR context("Begin_Font_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Font_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_SSPPR *			_hoops_GGHPR;
	_hoops_RCHIH		_hoops_ACHIH;
	Option_Value *			option_list;
	Option_Value *			option;

	/* _hoops_GGCR _hoops_GIPHR _hoops_RGSPR _hoops_SRS _hoops_HIS _hoops_ACGR/_hoops_HCSH _hoops_HRGR _hoops_IHRI _hoops_PRGI _hoops_CCA _hoops_AHCI _hoops_CIIA */
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_HHPGI;
	context->_hoops_HHPGI = _hoops_GGHPR;

	_hoops_HIACR (_hoops_GIRGI, _hoops_PHHGGR);

	if (!HI_Parse_Options (context, filter, _hoops_CIACR (_hoops_GIRGI), &option_list, _hoops_SIACR))
		return;

	_hoops_ACHIH._hoops_RRRSC = false;
	_hoops_ACHIH._hoops_ARRSC = false;
	_hoops_ACHIH._hoops_PRRSC = false;
	_hoops_ACHIH._hoops_HRRSC = false;

	if ((option = option_list) != null) do {
		switch (option->type->id) {
			case _hoops_SPHGGR:	_hoops_ACHIH._hoops_RRRSC  = !option->_hoops_GCACR;	break;
			case _hoops_GHHGGR:	_hoops_ACHIH._hoops_ARRSC = !option->_hoops_GCACR;	break;
			case _hoops_RHHGGR:	_hoops_ACHIH._hoops_PRRSC = !option->_hoops_GCACR;	break;
			case _hoops_AHHGGR:	_hoops_ACHIH._hoops_HRRSC  = !option->_hoops_GCACR;	break;
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (context, option_list);

	if (!_hoops_ACHIH._hoops_RRRSC && !_hoops_ACHIH._hoops_ARRSC && !_hoops_ACHIH._hoops_PRRSC && !_hoops_ACHIH._hoops_HRRSC) {
		HE_WARNING (HEC_TEXT, HES_NULL_INPUT, "'filter' value is blank - nothing requested");
		return;
	}

#ifndef DISABLE_DEFINED_FONTS
	if (_hoops_ACHIH._hoops_HRRSC) {
		_hoops_PGIIR *			font;
		_hoops_AGHPR *	node;

		_hoops_CSPPR();
		_hoops_PGIIR **	_hoops_GPPIR = _hoops_RSPPR(context, _hoops_SPPGI);
		if (_hoops_GPPIR == null) {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Font hash table missing");
			_hoops_IRRPR();
			return;
		}

		int count = _hoops_GPRGI;
		do {
			if ((font = *_hoops_GPPIR) != null) do {
				ZALLOC (node, _hoops_AGHPR);
				node->next = _hoops_GGHPR->list;
				_hoops_GGHPR->list = node;
				node->item = (_hoops_HPAH *)font;
				_hoops_PRRH (font);
				++_hoops_GGHPR->count;
			} while ((font = font->next) != null);
			++_hoops_GPPIR;
		} while (--count > 0);
		_hoops_IRRPR();
	}
#endif

	if (_hoops_ACHIH._hoops_RRRSC || _hoops_ACHIH._hoops_ARRSC || _hoops_ACHIH._hoops_PRRSC) {

		_hoops_CSPPR();
		_hoops_GGAGR *	_hoops_GHRI = HI_Force_Find_Driver (context, display);
		/* _hoops_RPP _hoops_RHPP _hoops_HRGR _hoops_CRHPH (_hoops_IAS._hoops_ISHI. _hoops_IGRIP _hoops_SISIH), _hoops_IIH'_hoops_GRI _hoops_ISAP _hoops_IS _hoops_AA _hoops_ARI */
		if (_hoops_GHRI != null) {

			if (_hoops_HISAA (context, _hoops_GHRI, _hoops_SAGSC, &_hoops_ACHIH)) {
				_hoops_GGHPR->count += _hoops_ACHIH.count;
				_hoops_GGHPR->_hoops_IASRS = _hoops_ACHIH.count;
				_hoops_GGHPR->_hoops_HGPIR = _hoops_ACHIH._hoops_HGPIR;
				_hoops_GGHPR->_hoops_HASRS = _hoops_GHRI;
				_hoops_PRRH (_hoops_GHRI);
			}
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE bool HC_CDECL HC_Find_Font (
	char *					name) 
{
	_hoops_PAPPR context("Find_Font");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Font () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_HHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_TEXT, HES_INACTIVE_SEARCH, "No font search is active");
		return false;
	}

	/* _hoops_SRS _hoops_HPPR _hoops_IH _hoops_GII _hoops_PAPR _hoops_GSPIP */
	_hoops_AGHPR *	list;
	while ((list = _hoops_GGHPR->list) != null) {
		_hoops_PGIIR *	font = (_hoops_PGIIR *)list->item;

		context->_hoops_HHPGI->list = list->next;
		FREE (list, _hoops_AGHPR);

		if (BIT (font->_hoops_RRHH, _hoops_HGAGR)) 
			_hoops_HPRH (font);
		else {
			HI_Return_Chars (name, -1, font->name.text, font->name.length);
			_hoops_HPRH (font);
			return true;
		}
	}

	/* _hoops_HA _hoops_HPPR _hoops_IH _hoops_RHPP _hoops_GSPIP */
	if (_hoops_GGHPR->next == _hoops_GGHPR->_hoops_IASRS ||
		_hoops_GGHPR->_hoops_HASRS == null ||
		!BIT (_hoops_GGHPR->_hoops_HASRS->_hoops_CGPIR, _hoops_GCSHA)) {
			/* _hoops_HHPPA, _hoops_SCH'_hoops_GRI _hoops_CPHR; _hoops_SHH _hoops_AGAPR & _hoops_CASI _hoops_GH _hoops_RSIH */
			if (_hoops_GGHPR->_hoops_HASRS != null) {
				_hoops_HPRH (_hoops_GGHPR->_hoops_HASRS);
				_hoops_GGHPR->_hoops_HASRS = null;
			}
			if (_hoops_GGHPR->_hoops_IASRS > 0) {
				FREE_ARRAY (_hoops_GGHPR->_hoops_HGPIR, _hoops_GGHPR->_hoops_IASRS, _hoops_HCRPR);
				_hoops_GGHPR->_hoops_IASRS = _hoops_GGHPR->next = 0;
			}
			return false;
	}

	HI_Return_Chars (name, -1, _hoops_GGHPR->_hoops_HGPIR[_hoops_GGHPR->next].text, _hoops_GGHPR->_hoops_HGPIR[_hoops_GGHPR->next].length);

	if (++_hoops_GGHPR->next == _hoops_GGHPR->_hoops_IASRS) {
		/* _hoops_SCH'_hoops_GRI _hoops_CPHR; _hoops_SHH _hoops_AGAPR & _hoops_CASI _hoops_GH _hoops_RSIH */
		if (_hoops_GGHPR->_hoops_HASRS != null) {
			_hoops_HPRH (_hoops_GGHPR->_hoops_HASRS);
			_hoops_GGHPR->_hoops_HASRS = null;
		}
		if (_hoops_GGHPR->_hoops_IASRS > 0) {
			FREE_ARRAY (_hoops_GGHPR->_hoops_HGPIR, _hoops_GGHPR->_hoops_IASRS, _hoops_HCRPR);
			_hoops_GGHPR->_hoops_IASRS = _hoops_GGHPR->next = 0;
		}
	}

	return true;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Font_Count (
	int *	count) 
{
	_hoops_PAPPR context("Show_Font_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Font_Count () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_HHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_TEXT, HES_INACTIVE_SEARCH, "No font search is active");
		return;
	}

	*count = _hoops_GGHPR->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Font_Search (void) 
{
	_hoops_PAPPR context("End_Font_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Font_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_HHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_TEXT, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	if (_hoops_GGHPR->_hoops_HASRS != null) 
		_hoops_HPRH (_hoops_GGHPR->_hoops_HASRS);

	if (_hoops_GGHPR->_hoops_IASRS > 0)
		FREE_ARRAY (_hoops_GGHPR->_hoops_HGPIR, _hoops_GGHPR->_hoops_IASRS, _hoops_HCRPR);

	context->_hoops_HHPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}




GLOBAL_FUNCTION _hoops_PGIIR ** HI_Look_Up_Font (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	int						length) {
	int						_hoops_SCPPR;
	char const *			_hoops_RPPA;
	char const *			_hoops_GSPPR;
	_hoops_PGIIR ** _hoops_HHHGGR, *_hoops_PSRGA;
	int _hoops_GCAH = 0;
	
	// _hoops_ASIGA _hoops_IHHGGR _hoops_HIIA
	if (!_hoops_RIGC)
		_hoops_IIRIR (_hoops_RIGC);

	if (length <= 0) 
		return null;

	if ((_hoops_HHHGGR = _hoops_RSPPR(_hoops_RIGC, _hoops_SPPGI)) == null) {
		ZALLOC_ARRAY (_hoops_HHHGGR, _hoops_GPRGI, _hoops_PGIIR *);
		_hoops_RSPPR(_hoops_RIGC, _hoops_SPPGI) = _hoops_HHHGGR;
	}

	_hoops_RPPA = name;
	_hoops_SCPPR = length;
	do {
		_hoops_GCAH += _hoops_SHPCR (*_hoops_RPPA);
		++_hoops_RPPA;
	} _hoops_RGGA (--_hoops_SCPPR == 0);

	/*** _hoops_PGCR'_hoops_GRI _hoops_HSPPR _hoops_RGAR! ***/
	_hoops_HHHGGR += _hoops_GCAH & (_hoops_GPRGI - 1);

	_hoops_RGGA ((_hoops_PSRGA = *_hoops_HHHGGR) == null) {
		if (_hoops_PSRGA->name.length == length) {
			_hoops_SCPPR = length;
			_hoops_RPPA = name;
			_hoops_GSPPR = _hoops_PSRGA->name.text;
			while (_hoops_SHPCR (*_hoops_RPPA) == _hoops_SHPCR (*_hoops_GSPPR)) {
				if (--_hoops_SCPPR == 0) return _hoops_HHHGGR;
				++_hoops_RPPA;
				++_hoops_GSPPR;
			}
		}

		_hoops_HHHGGR = &_hoops_PSRGA->next;
	}

	return _hoops_HHHGGR;
}







local Attribute *_hoops_CHHGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_GGPIR const *	_hoops_RIHHC = (_hoops_GGPIR const *)_hoops_CPACR;
	_hoops_GGPIR alter *	_hoops_AIHHC = (_hoops_GGPIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_RIHHC != null &&
		_hoops_RIHHC->value == _hoops_AIHHC->value &&
		_hoops_RIHHC->_hoops_HHCAP == _hoops_AIHHC->_hoops_HHCAP)
		return null;

	if (_hoops_AIHHC->value != TALIGN_UNDEFINED)
		;// _hoops_ISAP
	else if (_hoops_RIHHC != null)
		_hoops_AIHHC->value = _hoops_RIHHC->value;
	else
		_hoops_AIHHC->value = TALIGN_CENTER;

	if (_hoops_AIHHC->_hoops_HHCAP != TJUST_UNDEFINED)
		;// _hoops_ISAP
	else if (_hoops_RIHHC != null)
		_hoops_AIHHC->_hoops_HHCAP = _hoops_RIHHC->_hoops_HHCAP;
	else
		_hoops_AIHHC->_hoops_HHCAP = TJUST_LEFT;

	return _hoops_AIHHC;
}


local bool _hoops_SHHGGR (
	char const *		name,
	long *				value,
	long *				_hoops_HHCAP,
	char const *		_hoops_SRGPH) 
{
	char const *		_hoops_CSHPP = name;
	char				_hoops_PHPCA;
	int					_hoops_PRRIP = TALIGN_UNDEFINED;
	int					_hoops_HRRIP = TJUST_UNDEFINED;
	int					_hoops_GAGCR = TALIGN_UNDEFINED;
	int					_hoops_CHPSP = TALIGN_UNDEFINED;
	int					_hoops_GIHGGR = 0;
	bool				_hoops_SSRP = false;

	while ((_hoops_PHPCA = *_hoops_CSHPP++) != '\0') switch (_hoops_PHPCA) {
		case '.': {
			_hoops_SSRP = true;
		}	break;

		case '*': {
			++_hoops_GIHGGR;
		}	break;

		case '<': {
			_hoops_GAGCR = TALIGN_LEFT;
		}	break;

		case '>': {
			_hoops_GAGCR = TALIGN_RIGHT;
		}	break;

		case 'V': case 'v': {
			_hoops_CHPSP = TALIGN_LOWER;
		}	break;

		case '^': {
			_hoops_CHPSP = TALIGN_UPPER;
		}	break;


		case '[': {
			_hoops_HRRIP = TJUST_LEFT;
		}	break;

		case '|': {
			_hoops_HRRIP = TJUST_CENTER;
		}	break;

		case ']': {
			_hoops_HRRIP = TJUST_RIGHT;
		}	break;


		case ' ': break;


		default: {
			HE_ERROR (HEC_PATTERN, HES_INVALID_INPUT, Sprintf_SS (null, "'%s' is not one of the choices for %s", name, _hoops_SRGPH));
			return false;
		}	_hoops_HHHI;
	}

	if (_hoops_SSRP) {
		_hoops_PRRIP = TALIGN_INSERTION_POINT;

		if (_hoops_GIHGGR == 0) {									// _hoops_PA _hoops_HAR _hoops_HHHA _hoops_HRGR _hoops_GSSC/_hoops_RAAP
			if (_hoops_CHPSP != TALIGN_UNDEFINED)
				_hoops_PRRIP |= _hoops_CHPSP;
			else
				_hoops_PRRIP |= TALIGN_LOWER;

			if (_hoops_GAGCR != TALIGN_UNDEFINED)
				_hoops_PRRIP |= _hoops_GAGCR;
			else
				_hoops_PRRIP |= TALIGN_LEFT;
		}
		else if (_hoops_GIHGGR == 1) {								// _hoops_PGSH _hoops_IAGA _hoops_IS _hoops_RH _hoops_CPASR _hoops_HAGA
			if (_hoops_CHPSP != TALIGN_UNDEFINED)
				_hoops_PRRIP |= _hoops_CHPSP;						// -- _hoops_HIS * _hoops_HRGR _hoops_GPP _hoops_IRGGA
			else if (_hoops_GAGCR != TALIGN_UNDEFINED)
				_hoops_PRRIP |= _hoops_GAGCR;					// -- _hoops_HIS * _hoops_HRGR _hoops_GPP _hoops_IRPHR
			else
				_hoops_PRRIP |= TALIGN_LOWER;					// _hoops_HIH .* _hoops_HSHA _hoops_GAR .*_hoops_HPPC
		}
		else {
			// ".**" -- _hoops_AIAH _hoops_ARP!
		}
	}
	else {
		if (_hoops_GAGCR != TALIGN_UNDEFINED || _hoops_CHPSP != TALIGN_UNDEFINED) {
			_hoops_PRRIP = TALIGN_CENTER;
			if (_hoops_CHPSP != TALIGN_UNDEFINED)
				_hoops_PRRIP |= _hoops_CHPSP;
			if (_hoops_GAGCR != TALIGN_UNDEFINED)
				_hoops_PRRIP |= _hoops_GAGCR;
		}
	}


	*value = _hoops_PRRIP;
	*_hoops_HHCAP = _hoops_HRRIP;

	return true;
}


GLOBAL_FUNCTION bool HI_Set_Text_Alignment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GGPIR	*		_hoops_RGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_TEXT_ALIGNMENT, _hoops_CHHGGR, _hoops_RGGCH);
}


HC_INTERFACE void HC_CDECL HC_Set_Text_Alignment (
	char const *		pattern) 
{
	_hoops_PAPPR context("Set_Text_Alignment");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Text_Alignment (%S);\n", pattern));
	);

	long	value;
	long	_hoops_HHCAP;

	if (!_hoops_SHHGGR (pattern, &value, &_hoops_HHCAP, "Text Alignment")) 
		return;

	bool				used = false;
	_hoops_GGPIR *	_hoops_RGGCH;
	ZALLOC (_hoops_RGGCH, _hoops_GGPIR);
	ASSERT(value == (0x000000FF&value));
	ASSERT(_hoops_HHCAP == (0x000000FF&_hoops_HHCAP));
	_hoops_RGGCH->value = (unsigned char) (0xFF&value);
	_hoops_RGGCH->_hoops_HHCAP = (unsigned char) (0xFF&_hoops_HHCAP);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PARPP)) != null) {
		used = HI_Set_Text_Alignment(context, target, _hoops_RGGCH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_RGGCH, _hoops_GGPIR);

}


HC_INTERFACE void HC_CDECL HC_UnSet_Text_Alignment (void) {
	_hoops_PAPPR context("UnSet_Text_Alignment");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Text_Alignment ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PARPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_TEXT_ALIGNMENT);
		_hoops_IRRPR();
	}
}


local char const * _hoops_CIHHC (void) {
	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized pattern type");
	return "";
}

GLOBAL_FUNCTION void HI_Show_Text_Alignment (
	_hoops_SHCAP *		_hoops_RIHGGR,
	char *					pattern,
	int						_hoops_RCSIH) 
{
	char					buffer[8];
	char					*p = buffer;

#ifndef DISABLE_SHOW
	if (BIT (_hoops_RIHGGR->value, TALIGN_INSERTION_POINT))
		*p++ = '.';

	switch (_hoops_RIHGGR->value & TALIGN_HORIZONTAL_MASK) {
		case TALIGN_LEFT:			*p++ = '<';				break;
		case TALIGN_CENTER:			*p++ = '*';				break;
		case TALIGN_RIGHT:			*p++ = '>';				break;
		default:					_hoops_CIHHC();		return; _hoops_HHHI;
	}
	switch (_hoops_RIHGGR->value & TALIGN_VERTICAL_MASK) {
		case TALIGN_LOWER:			*p++ = 'v';				break;
		case TALIGN_CENTER:			*p++ = '*';				break;
		case TALIGN_UPPER:			*p++ = '^';				break;
		default:					_hoops_CIHHC();		return; _hoops_HHHI;
	}

#ifndef MINITAB
	switch (_hoops_RIHGGR->_hoops_HHCAP) {
		case TJUST_LEFT:			*p++ = '[';				break;
		case TJUST_CENTER:			*p++ = '|';				break;
		case TJUST_RIGHT:			*p++ = ']';				break;
		default:					_hoops_CIHHC();		return; _hoops_HHHI;
	}
#endif

	HI_Return_Chars (pattern, _hoops_RCSIH, buffer, p - buffer);
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Text_Alignment (
	char *				pattern) 
{
	_hoops_PAPPR context("Show_Text_Alignment");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_Alignment () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RCRPP)) != null) {

		_hoops_SHCAP *	_hoops_RIHGGR;
		if ((_hoops_RIHGGR = (_hoops_SHCAP *)HI_Find_Attribute (context, target, HK_TEXT_ALIGNMENT)) != null) {

			HI_Show_Text_Alignment (_hoops_RIHGGR, pattern, -1);
			_hoops_HPRH (_hoops_RIHGGR);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Alignment (
	int						count,
	Key const *				keys,
	char *					pattern) 
{
	_hoops_PAPPR context("PShow_Net_Text_Alignment");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Text_Alignment () */\n");
	);

	_hoops_SHCAP *	_hoops_RIHGGR;
	if ((_hoops_RIHGGR = (_hoops_SHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_RCRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Text_Alignment (_hoops_RIHGGR, pattern, -1);
		_hoops_HPRH (_hoops_RIHGGR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);

#endif
}
#endif



local Attribute * _hoops_AIHGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_RGPIR const *		_hoops_PIHGGR = (_hoops_RGPIR const *)_hoops_CPACR;
	_hoops_RGPIR alter *		_hoops_HIHGGR = (_hoops_RGPIR alter *)_hoops_SPACR;


	if (_hoops_PIHGGR != null &&
		_hoops_PIHGGR->value.x == _hoops_HIHGGR->value.x &&
		_hoops_PIHGGR->value.y == _hoops_HIHGGR->value.y &&
		_hoops_PIHGGR->value.z == _hoops_HIHGGR->value.z)
		return null;

	if (_hoops_HIHGGR->value.z != 0.0f) {
		_hoops_HIHGGR->_hoops_RRHH |= _hoops_RSPCR;

		_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
		ASSERT(_hoops_SRCP->type == _hoops_IRCP);

		if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR)) 
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}

	return _hoops_HIHGGR;
}

GLOBAL_FUNCTION bool HI_Set_Text_Path ( 
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RGPIR *				_hoops_HGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_TEXT_PATH, _hoops_AIHGGR, _hoops_HGGCH);
}

HC_INTERFACE void HC_CDECL HC_Set_Text_Path (
	double			x,
	double			y,
	double			z) 
{
	_hoops_PAPPR context("Set_Text_Path");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Text_Path (%F, %F, ", x, y));
	HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	bool		used = false;
	_hoops_RGPIR *	_hoops_HGGCH;
	ZALLOC (_hoops_HGGCH, _hoops_RGPIR);
	_hoops_HGGCH->value.x = (float)x;
	_hoops_HGGCH->value.y = (float)y;
	_hoops_HGGCH->value.z = (float)z;

	if (!HI_Normalize (&_hoops_HGGCH->value)) {
		HE_ERROR (HEC_TEXT, HES_BAD_TEXT_PATH, "Text path is all zeroes");
	}
	else {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_HARPP)) != null) {
			used = HI_Set_Text_Path(context, target, _hoops_HGGCH);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (_hoops_HGGCH, _hoops_RGPIR);
}


HC_INTERFACE void HC_CDECL HC_UnSet_Text_Path (void) 
{
	_hoops_PAPPR context("UnSet_Text_Path");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Text_Path ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HARPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_TEXT_PATH);
		_hoops_IRRPR();
	}
}


HC_INTERFACE void HC_CDECL HC_Show_Text_Path (
	float *				x,
	float *				y,
	float *				z) 
{
	_hoops_PAPPR context("Show_Text_Path");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_Path () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ACRPP)) != null) {

		_hoops_RGPIR *	_hoops_HGGCH;
		if ((_hoops_HGGCH = (_hoops_RGPIR *)HI_Find_Attribute (context, target, HK_TEXT_PATH)) != null) {

			*x = _hoops_HGGCH->value.x;
			*y = _hoops_HGGCH->value.y;
			*z = _hoops_HGGCH->value.z;

			_hoops_HPRH (_hoops_HGGCH);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Path (
	int					count,
	Key const *			keys,
	float *				x,
	float *				y,
	float *				z) 
{
	_hoops_PAPPR context("PShow_Net_Text_Path");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Text_Path () */\n");
	);

	_hoops_RGPIR *	_hoops_HGGCH;
	if ((_hoops_HGGCH = (_hoops_RGPIR *) HI_Find_Attribute_And_Lock(context, _hoops_ACRPP, _hoops_HRPCR, count, keys)) != null) {
		*x = _hoops_HGGCH->value.x;
		*y = _hoops_HGGCH->value.y;
		*z = _hoops_HGGCH->value.z;

		_hoops_HPRH (_hoops_HGGCH);
		_hoops_IRRPR();
	}
	else
		*x=*y=*z=0;
#endif
}
#endif



