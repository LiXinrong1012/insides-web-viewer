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
 * $Id: obf_tmp.txt 1.117 2010-11-18 00:59:02 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_GHHHC {
	char		_hoops_RHIA[12];
	bool		_hoops_RHHHC;
	bool		_hoops_AHHHC;
	short		value;
};

local const _hoops_GHHHC _hoops_PHHHC[] = {
	{"solid", false, false, FP_SOLID},
	{"#",  false, true, FP_CROSSHATCH},
	{"|",  false, true, FP_VERTICAL_BARS},
	{"=",  false, true, FP_HORIZONTAL_BARS},
	{"/",  false, true, FP_SLANT_RIGHT},
	{"\\", false, true, FP_SLANT_LEFT},
	{":",  false, true, FP_SQUARE_DOTS},
	{"<>", false, true, FP_DIAMONDS},
	{"[]", true,  true, FP_CHECKERBOARD},
	{"", false, false, 0}};

local const _hoops_GHHHC _hoops_HHHHC[] = {
	{"solid", false, false, FP_SOLID},
	{"clear", false, false, FP_WINDOW_TRANSPARENT},
	{"#",  false, true, FP_WINDOW_CROSSHATCH},
	{"|",  false, true, FP_WINDOW_VERTICAL_BARS},
	{"=",  false, true, FP_WINDOW_HORIZONTAL_BARS},
	{"/",  false, true, FP_WINDOW_SLANT_RIGHT},
	{"\\", false, true, FP_WINDOW_SLANT_LEFT},
	{":",  false, true, FP_WINDOW_SQUARE_DOTS},
	{"<>", false, true, FP_WINDOW_DIAMONDS},
	{"[]", true,  true, FP_WINDOW_CHECKERBOARD},
	{"n",  false, false, FP_WINDOW_GRADIENT_N},
	{"ne", false, false, FP_WINDOW_GRADIENT_NE},
	{"e",  false, false, FP_WINDOW_GRADIENT_E},
	{"se", false, false, FP_WINDOW_GRADIENT_SE},
	{"s",  false, false, FP_WINDOW_GRADIENT_S},
	{"sw", false, false, FP_WINDOW_GRADIENT_SW},
	{"w",  false, false, FP_WINDOW_GRADIENT_W},
	{"nw", false, false, FP_WINDOW_GRADIENT_NW},
	{"up",	  false, false, FP_WINDOW_GRADIENT_N},
	{"down",  false, false, FP_WINDOW_GRADIENT_S},
	{"right", false, false, FP_WINDOW_GRADIENT_E},
	{"left",  false, false, FP_WINDOW_GRADIENT_W},
	{"blend",  false, false, FP_BLEND},
	{"invisible", false, false, FP_WINDOW_TRANS_NO_ZCLEAR},
	{"", false, false, 0}};


local bool _hoops_IHHHC (
	char const *			name,
	_hoops_GHHHC const *	_hoops_HAPAR,
	long *					result,
	char const *			_hoops_SRGPH) 
{
	char const *	_hoops_CSHPP;
	char const *	_hoops_AHSCA;
	char const *	_hoops_CHHHC;


	_hoops_CHHHC = _hoops_AHSCA = name;
	while (*_hoops_AHSCA) if (*_hoops_AHSCA++ != ' ') 
		_hoops_CHHHC = _hoops_AHSCA;

	if (*name) do {
		_hoops_AHSCA = name;
		_hoops_CSHPP = &_hoops_HAPAR->_hoops_RHIA[0];
		do {
			if (*_hoops_CSHPP != _hoops_SHPCR (*_hoops_AHSCA)) goto _hoops_SHHHC;
			++_hoops_AHSCA;
		}
		while (*++_hoops_CSHPP && _hoops_AHSCA < _hoops_CHHHC);

		if (*_hoops_CSHPP) goto _hoops_SHHHC;

		if (_hoops_HAPAR->_hoops_RHHHC) while (*_hoops_AHSCA == ' ') ++_hoops_AHSCA;

		if (!_hoops_HAPAR->_hoops_AHHHC) {
			if (_hoops_AHSCA < _hoops_CHHHC) goto _hoops_SHHHC;
		}
		else {
			while (_hoops_AHSCA < _hoops_CHHHC) {
				_hoops_CSHPP = &_hoops_HAPAR->_hoops_RHIA[0];
				do {
					if (*_hoops_CSHPP != _hoops_SHPCR (*_hoops_AHSCA)) goto _hoops_SHHHC;
					++_hoops_AHSCA;
				} while (*++_hoops_CSHPP && _hoops_AHSCA < _hoops_CHHHC);

				if (_hoops_HAPAR->_hoops_RHHHC) while (*_hoops_AHSCA == ' ') ++_hoops_AHSCA;
			}
		}

		*result = _hoops_HAPAR->value;
		return true;

		_hoops_SHHHC:;
	}
	_hoops_RGGA ((++_hoops_HAPAR)->_hoops_RHIA[0] == '\0');

	HE_ERROR (HEC_PATTERN, HES_INVALID_INPUT, Sprintf_SS (null, "'%s' is not one of the choices for %s",name, _hoops_SRGPH));

	return false;
}

local Attribute *_hoops_GIHHC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_GGPIR const *	_hoops_RIHHC = (_hoops_GGPIR const *)_hoops_CPACR;
	_hoops_GGPIR alter * _hoops_AIHHC = (_hoops_GGPIR alter *)_hoops_SPACR;

	UNREFERENCED (item);
	UNREFERENCED (_hoops_RIGC);

	if (_hoops_RIHHC != null &&
		_hoops_RIHHC->value == _hoops_AIHHC->value &&
		_hoops_RIHHC->_hoops_HHCAP == _hoops_AIHHC->_hoops_HHCAP)
		return null;

	return _hoops_AIHHC;
}


local Attribute *_hoops_PIHHC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_GGPIR const *	_hoops_RIHHC = (_hoops_GGPIR *)_hoops_CPACR;
	_hoops_GGPIR alter * _hoops_AIHHC = (_hoops_GGPIR *)_hoops_SPACR;

	if (_hoops_RIHHC != null && 
		_hoops_RIHHC->value == _hoops_AIHHC->value &&
		_hoops_RIHHC->_hoops_HHCAP == _hoops_AIHHC->_hoops_HHCAP)
		return null;

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
	ASSERT(_hoops_SRCP->type == _hoops_IRCP);

	if (_hoops_AIHHC->value != FP_SOLID &&
		_hoops_AIHHC->value != FP_WINDOW_TRANSPARENT &&
		_hoops_AIHHC->value != FP_WINDOW_TRANS_NO_ZCLEAR &&
		!BIT(_hoops_SRCP->_hoops_RCGC, _hoops_IPHGP))
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_IPHGP);

	if (_hoops_AIHHC->value >= FP_WINDOW_FIRST_GRADIENT &&
		_hoops_AIHHC->value <= FP_WINDOW_LAST_GRADIENT &&
		!BIT(_hoops_SRCP->_hoops_RCGC, _hoops_ASRRA))
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASRRA);

	return _hoops_AIHHC;
}


#define _hoops_HIHHC(geom,x) (BIT (geom->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_IIHHC (geom,x) : _hoops_SASIR (geom, _hoops_RAGGA | (x)))

#define _hoops_IIHHC(geom,x)		_hoops_SASIR (geom, _hoops_GGARA | (x))


GLOBAL_FUNCTION bool HI_Set_Face_Pattern(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_GGPIR	*		_hoops_RGGCH)
{
	_hoops_ICIIR(_hoops_RIGC);

#ifdef _hoops_PGPHR
	_hoops_IRPPR ("Geometry Face Attributes");
#else

	if(!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)){
		/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HSGP _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_HSP, _hoops_HIH _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_HSP _hoops_RIP
		_hoops_CRPR _hoops_HPP _hoops_HA, _hoops_SR _hoops_RRP _hoops_SPR! */
		ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
		for(int i = 0; i < _hoops_IPRI->face_count; i++)
			_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
		_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
	}

	if (_hoops_IPRI->local_face_attributes._hoops_AHHIR == null)
		HI_Initialize_Face_Attributes (_hoops_IPRI, _hoops_HAGI);

	if (_hoops_GCRIR == _hoops_ICRIR) {

		_hoops_GIIPR *	flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);
		unsigned char *		_hoops_CRIA = &_hoops_IPRI->local_face_attributes._hoops_AHHIR[offset];

		if (BIT (*flags, _hoops_HAGI) && _hoops_RGGCH->value == *_hoops_CRIA)
			goto Release;

		if (!BIT (*flags, _hoops_HAGI)) {
			*flags |= _hoops_HAGI;
			++_hoops_IPRI->local_face_attributes._hoops_SRAPA;
		}
		*_hoops_CRIA = _hoops_RGGCH->value;
		*flags |= _hoops_IGAHR;

		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
	}
	else if (_hoops_GCRIR == _hoops_GSRIR) {	

		int const *	regions = _hoops_IPRI->local_face_attributes.regions;

		/* _hoops_HCR _hoops_RSSI _hoops_GGR _hoops_SHIR _hoops_ISPH, _hoops_IAGC _hoops_GPGH'_hoops_RA */
		if (regions == null && offset != 0)
			goto Release;			

		for (int i=0; i<_hoops_IPRI->face_count; i++) {
			if (regions == null || regions[i] == offset) {
				_hoops_GIIPR *	flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(i);
				unsigned char *		_hoops_CRIA = &_hoops_IPRI->local_face_attributes._hoops_AHHIR[i];

				if (!BIT (*flags, _hoops_HAGI) ||
					_hoops_RGGCH->value != *_hoops_CRIA) {
					if (!BIT (*flags, _hoops_HAGI)) {
						*flags |= _hoops_HAGI;
						++_hoops_IPRI->local_face_attributes._hoops_SRAPA;
					}
					*_hoops_CRIA = _hoops_RGGCH->value;
					*flags |= _hoops_IGAHR;
				}
			}
		}

		if (_hoops_IPRI->tristrips != null) {
			if (!BIT (HOOPS_WORLD->system_flags, _hoops_CSRRA))
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
			else {
				Tristrip *	ts = _hoops_IPRI->tristrips;

				do {
					if (ts->face_attributes.region == offset) {
						ts->face_attributes.pattern = _hoops_RGGCH->value;
						ts->face_attributes.flags |= _hoops_HAGI;
						ts->_hoops_CPGPR |= _hoops_GPSIR;
					}
				} while ((ts = ts->next) != null);
			}
		}

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
	}
	else
		ASSERT(0);

Release:
#endif
	return false;
}


GLOBAL_FUNCTION bool HI_Set_Face_Pattern (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GGPIR	*		_hoops_RGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_FACE_PATTERN, _hoops_GIHHC, _hoops_RGGCH);
}

HC_INTERFACE void HC_CDECL HC_Set_Face_Pattern (
	char const *		pattern) 
{
	_hoops_PAPPR context("Set_Face_Pattern");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Face_Pattern (%S);\n", pattern));
	);

	long	value;
	if (!_hoops_IHHHC (pattern, _hoops_PHHHC, &value, "Face Pattern")) 
		return;

	bool	used = false;
	_hoops_GGPIR	*	_hoops_RGGCH;
	ZALLOC (_hoops_RGGCH, _hoops_GGPIR); 
	ASSERT(value == (0x000000FF&value));
	_hoops_RGGCH->value = (unsigned char) (0xFF&value);
	_hoops_RGGCH->_hoops_HHCAP = 0;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RARPP)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			used = HI_Set_Face_Pattern(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_RGGCH);
		}
		else
			used = HI_Set_Face_Pattern(context, target, _hoops_RGGCH);

		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_RGGCH, _hoops_GGPIR); 

}

GLOBAL_FUNCTION void HI_UnSet_Face_Pattern(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR)
{
	_hoops_ICIIR(_hoops_RIGC);

#ifdef _hoops_PGPHR
	_hoops_IRPPR ("Geometry Face Attributes");
#else
	if (_hoops_GCRIR ==  _hoops_ICRIR) {

		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		_hoops_GIIPR *		flags = _hoops_CPRI->_hoops_CHHPR(offset);

		if (!BIT (*flags, _hoops_HAGI)) {
			HE_ERROR (HEC_FACE, HES_PATTERN, "No pattern set on this face");
			goto Release;
		}

		if (--_hoops_CPRI->_hoops_SRAPA == 0) {
			FREE_ARRAY (_hoops_CPRI->_hoops_AHHIR, _hoops_IPRI->face_count, unsigned char);
			_hoops_CPRI->_hoops_AHHIR = null;
		}
		else
			_hoops_CPRI->_hoops_AHHIR[offset] = 0;

		*flags &= ~_hoops_HAGI;
		*flags |= _hoops_IGAHR;

		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);

	}
	else if (_hoops_GCRIR == _hoops_GSRIR) {
	
		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		int const *				regions = _hoops_CPRI->regions;
		_hoops_GIIPR *		flags;
		bool					_hoops_SACRH = false;

		if ((flags = _hoops_CPRI->flags) == null ||
			regions == null && offset != 0) {
			HE_ERROR (HEC_REGION, HES_PATTERN, "No patterns set in this region");
			goto Release;
		}

		for (int i=0; i<_hoops_IPRI->face_count; i++) {
			if (regions == null || regions[i] == offset) {
				if (BIT (flags[i], _hoops_HAGI)) {
					flags[i] &= ~_hoops_HAGI;

					if (--_hoops_CPRI->_hoops_SRAPA == 0) {
						FREE_ARRAY (_hoops_CPRI->_hoops_AHHIR, _hoops_IPRI->face_count, unsigned char);
						_hoops_CPRI->_hoops_AHHIR = null;
					}
					else
						_hoops_CPRI->_hoops_AHHIR[i] = 0;
					_hoops_SACRH = true;
				}
			}
		}

		if (_hoops_SACRH) {
			if (_hoops_IPRI->tristrips != null) {
				Tristrip *	ts = _hoops_IPRI->tristrips;

				do if (ts->face_attributes.region == offset) {
					ts->face_attributes.flags &= ~_hoops_HAGI;
					ts->_hoops_CPGPR |= _hoops_GPSIR;
				} while ((ts = ts->next) != null);
			}

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
		}
		else
			HE_ERROR (HEC_REGION, HES_PATTERN, "No patterns set in this region");
	}
	else
		ASSERT(0);

Release:
	;
#endif
}

HC_INTERFACE void HC_CDECL HC_UnSet_Face_Pattern (void) 
{
	_hoops_PAPPR context("UnSet_Face_Pattern");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Face_Pattern ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RARPP|_hoops_GSIIR)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			HI_UnSet_Face_Pattern(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR);
		}
		else
			HI_UnSet_Attribute (context,  target, HK_FACE_PATTERN);

		_hoops_IRRPR();
	}
#endif
}

GLOBAL_FUNCTION bool HI_Set_Window_Pattern (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GGPIR	*		_hoops_RGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_WINDOW_PATTERN, _hoops_PIHHC, _hoops_RGGCH);
}


HC_INTERFACE void HC_CDECL HC_Set_Window_Pattern (
	char const *		pattern) 
{
	_hoops_PAPPR context("Set_Window_Pattern");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Window_Pattern (%S);\n", pattern));
	);

	long	value;
	if (!_hoops_IHHHC (pattern, _hoops_HHHHC, &value, "Window Pattern"))
		return;

	bool				used = false;
	_hoops_GGPIR	*	_hoops_RGGCH;
	ZALLOC (_hoops_RGGCH, _hoops_GGPIR);
	ASSERT(value == (0x000000FF&value));
	_hoops_RGGCH->value = (unsigned char) (0xFF&value);
	_hoops_RGGCH->_hoops_HHCAP = 0;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_AARPP)) != null) {
		used = HI_Set_Window_Pattern(context, target, _hoops_RGGCH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_RGGCH, _hoops_GGPIR);
}

HC_INTERFACE void HC_CDECL HC_UnSet_Window_Pattern (void) 
{
	_hoops_PAPPR context("UnSet_Window_Pattern");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Window_Pattern ();\n");
	);
	
	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_AARPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context,  target, HK_WINDOW_PATTERN);
		_hoops_IRRPR();
	}

}

#ifndef DISABLE_SHOW

local char const * _hoops_CIHHC (void) {
	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized pattern type");
	return "";
}

local void show_face_pattern (
	_hoops_IHCAP const	*_hoops_CRIA,
	char					*pattern,
	int						_hoops_RCSIH) {
	char const				*p;
	int						_hoops_RISRA;

	switch (_hoops_CRIA->value) {
		case FP_CROSSHATCH:		p = "#";		_hoops_RISRA = 1;		break;
		case FP_VERTICAL_BARS:	p = "|";		_hoops_RISRA = 1;		break;
		case FP_HORIZONTAL_BARS:p = "=";		_hoops_RISRA = 1;		break;
		case FP_SLANT_RIGHT:	p = "/";		_hoops_RISRA = 1;		break;
		case FP_SLANT_LEFT:		p = "\\";		_hoops_RISRA = 1;		break;
		case FP_DIAMONDS:		p = "<>";		_hoops_RISRA = 2;		break;
		case FP_SQUARE_DOTS:	p = ":";		_hoops_RISRA = 1;		break;
		case FP_CHECKERBOARD:	p = "[]";		_hoops_RISRA = 2;		break;
		case FP_SOLID:			p = "solid";	_hoops_RISRA = 5;		break;
		default:				p = _hoops_CIHHC();	_hoops_RISRA = 0;		break;
	}

	HI_Return_Chars (pattern, _hoops_RCSIH, p, _hoops_RISRA);
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Face_Pattern (
	char *				pattern) 
{
	_hoops_PAPPR context("Show_Face_Pattern");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Face_Pattern () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SIRPP)) != null) {

		_hoops_IHCAP *	_hoops_CRIA;
		if ((_hoops_CRIA = (_hoops_IHCAP *)HI_Find_Attribute (context, target, HK_FACE_PATTERN)) != null) {

			show_face_pattern (_hoops_CRIA, pattern, -1);
			_hoops_HPRH (_hoops_CRIA);
		}
		_hoops_IRRPR();
	}
#endif
}




#ifndef DISABLE_SHOW

local void _hoops_SIHHC (
	_hoops_CHCAP		*_hoops_CGAIP,
	char					*pattern,
	int						_hoops_RCSIH) {
	char const				*p;
	int						_hoops_RISRA;

	switch (_hoops_CGAIP->value) {
		case FP_WINDOW_CROSSHATCH:		p = "#";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_VERTICAL_BARS:	p = "|";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_HORIZONTAL_BARS: p = "=";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_SLANT_RIGHT:		p = "/";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_SLANT_LEFT:		p = "\\";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_DIAMONDS:		p = "<>";		_hoops_RISRA = 2;		break;
		case FP_WINDOW_SQUARE_DOTS:		p = ":";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_CHECKERBOARD:	p = "[]";		_hoops_RISRA = 2;		break;
		case FP_SOLID:					p = "solid";	_hoops_RISRA = 5;		break;
		case FP_WINDOW_TRANSPARENT:		p = "clear";	_hoops_RISRA = 5;		break;
		case FP_WINDOW_GRADIENT_N:		p = "n";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_GRADIENT_NE:		p = "ne";		_hoops_RISRA = 2;		break;
		case FP_WINDOW_GRADIENT_E:		p = "e";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_GRADIENT_SE:		p = "se";		_hoops_RISRA = 2;		break;
		case FP_WINDOW_GRADIENT_S:		p = "s";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_GRADIENT_SW:		p = "sw";		_hoops_RISRA = 2;		break;
		case FP_WINDOW_GRADIENT_W:		p = "w";		_hoops_RISRA = 1;		break;
		case FP_WINDOW_GRADIENT_NW:		p = "nw";		_hoops_RISRA = 2;		break;
		case FP_BLEND:					p = "blend";	_hoops_RISRA = 5;		break;
		case FP_WINDOW_TRANS_NO_ZCLEAR:	p = "invisible";_hoops_RISRA = 9;		break;
		default:						p = _hoops_CIHHC();	_hoops_RISRA = 0;		break;
	}

	HI_Return_Chars (pattern, _hoops_RCSIH, p, _hoops_RISRA);
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_Window_Pattern (
	char *			pattern) 
{
	_hoops_PAPPR context("Show_Window_Pattern");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Window_Pattern () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GCRPP)) != null) {
		_hoops_CHCAP *	_hoops_CGAIP;
		if ((_hoops_CGAIP = (_hoops_CHCAP *)HI_Find_Attribute (context, target, HK_WINDOW_PATTERN)) != null) {

			_hoops_SIHHC (_hoops_CGAIP, pattern, -1);
			_hoops_HPRH (_hoops_CGAIP);
		}
		_hoops_IRRPR();
	}
#endif
}





/*
 * _hoops_GCHHC _hoops_SRHIR
 */



#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Face_Pattern (
	int						count,
	Key const *				keys,
	char *					pattern) 
{
	_hoops_PAPPR context("PShow_Net_Face_Pattern");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Face_Pattern () */\n");
	);

	_hoops_IHCAP *	_hoops_CRIA;
	if ((_hoops_CRIA = (_hoops_IHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_SIRPP, _hoops_HRPCR, count, keys)) != null) {
		show_face_pattern (_hoops_CRIA, pattern, -1);
		_hoops_HPRH (_hoops_CRIA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);

#endif
}
#endif



#ifndef _hoops_ARPCR


HC_INTERFACE void HC_CDECL HC_PShow_Net_Window_Pattern (
	int						count,
	Key const *				keys,
	char *					pattern) 
{
	_hoops_PAPPR context("PShow_Net_Window_Pattern");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Window_Pattern () */\n");
	);

	_hoops_CHCAP *	_hoops_CGAIP;
	if ((_hoops_CGAIP = (_hoops_CHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_GCRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_SIHHC (_hoops_CGAIP, pattern, -1);
		_hoops_HPRH (_hoops_CGAIP);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);
#endif
}
#endif




