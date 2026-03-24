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
 * $Id: obf_tmp.txt 1.60 2010-11-18 00:59:02 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

local Attribute *_hoops_ACPPS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_SSAIR const *	_hoops_PCPPS = (_hoops_SSAIR const *)_hoops_CPACR;
	_hoops_SSAIR alter *	_hoops_HCPPS = (_hoops_SSAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_PCPPS != null &&
		_hoops_PCPPS->_hoops_HHCAP == _hoops_HCPPS->_hoops_HHCAP &&
		_hoops_RAHSR(_hoops_PCPPS->name, _hoops_HCPPS->name))
		return null;

	_hoops_HCARA(_hoops_HCPPS->name, _hoops_HCPPS->key);
	return _hoops_HCPPS;
}



#define _hoops_HIHHC(_hoops_RSPGP,geom,x) (BIT (geom->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_IIHHC (_hoops_RSPGP,geom,x) : _hoops_SASIR (_hoops_RSPGP,geom, _hoops_RAGGA | (x)))

#define _hoops_IIHHC(_hoops_RSPGP,geom,x)		_hoops_SASIR (_hoops_RSPGP,geom, _hoops_GGARA | (x))


GLOBAL_FUNCTION bool HI_Set_Vertex_Symbol(
	 _hoops_AIGPR *	_hoops_RIGC,
	 Polyhedron *			_hoops_IPRI,
	 int					offset,
	 _hoops_IPRRA				_hoops_GCRIR,
	 _hoops_SSAIR *		_hoops_SSSIH)
{
#ifdef _hoops_CSGHR
	_hoops_IRPPR ("Geometry Marker Attributes");
#else
	_hoops_ICIIR(_hoops_RIGC);

	ASSERT(_hoops_GCRIR == _hoops_SCRIR);

	if (_hoops_IPRI->local_vertex_attributes._hoops_SAHIR == null)
		HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_SIICA, 0);

	/* _hoops_APSH _hoops_PII _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_GPIA _hoops_RRPR _hoops_GPP _hoops_SAHR _hoops_SPR _hoops_GPHA, _hoops_HIS
		_hoops_SR'_hoops_GCPP _hoops_PAHH _hoops_RRP _hoops_IRS _hoops_IIRRA->_hoops_SGI _hoops_CRPR */
	if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
		ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
		for (int i = 0; i < _hoops_IPRI->point_count; i++)
			_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
		_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
	}

	Local_Vertex_Flags * flags  = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);
	unsigned char * symbol = &_hoops_IPRI->local_vertex_attributes._hoops_SAHIR[offset];

	_hoops_RPHIR * sl = HI_LVA_Symbol_Init(_hoops_IPRI, &_hoops_SSSIH->name);

	if (BIT (*flags, _hoops_SIICA) && sl->id != *symbol)
		goto _hoops_PRSPR;

	if (!BIT (*flags, _hoops_SIICA)) {
		*flags |= _hoops_SIICA;
		++_hoops_IPRI->local_vertex_attributes._hoops_AHIIC;
	}
	else {
		_hoops_RPHIR *	_hoops_GARSA = HI_LVA_Symbol_Lookup(_hoops_IPRI, *symbol);
		if (_hoops_ISAI(_hoops_GARSA) == 0)
			HI_LVA_Symbol_Delete(_hoops_IPRI, _hoops_GARSA);
	}
	_hoops_CAHS(sl);
	*symbol = sl->id;

	_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIICA;
	_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);

_hoops_PRSPR:
#endif
	return false;
}

GLOBAL_FUNCTION bool HI_Set_Marker_Symbol(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SSAIR	*		_hoops_IHAIC)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_MARKER_SYMBOL, _hoops_ACPPS, _hoops_IHAIC);
}


HC_INTERFACE void HC_CDECL HC_Set_Marker_Symbol (
	char const *			pattern)
{
	_hoops_PAPPR context("Set_Marker_Symbol");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Marker_Symbol (%S);\n", pattern));
	);

	bool				used = false;
	_hoops_SSAIR	*	_hoops_IHAIC;
	ZALLOC (_hoops_IHAIC, _hoops_SSAIR);
	HI_Canonize_Chars (pattern, &_hoops_IHAIC->name);

	if (_hoops_IHAIC->name.length == 0) {
		HE_ERROR (HEC_PATTERN, HES_INVALID_INPUT, "Marker Symbol is blank or null");
	}
	else {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_HRRPP)) != null) {
			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Vertex_Symbol (context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset,
											 _hoops_ASIIR->_hoops_GCRIR, _hoops_IHAIC);
			}
			else
				used = HI_Set_Marker_Symbol (context, target, _hoops_IHAIC);

			_hoops_IRRPR();
		}
	}

	if (!used) {
		_hoops_RGAIR(_hoops_IHAIC->name);
		FREE (_hoops_IHAIC, _hoops_SSAIR);
	}
}


GLOBAL_FUNCTION void HI_UnSet_Vertex_Symbol(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR)
{
#ifdef _hoops_CSGHR
	_hoops_IRPPR ("Geometry Marker Attributes");
#else
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(_hoops_GCRIR == _hoops_SCRIR);

	Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Local_Vertex_Flags *		flags = _hoops_SPRI->_hoops_CHHPR(offset);

	if (BIT (*flags, _hoops_SIICA)) {
		unsigned char *	symbol = &_hoops_IPRI->local_vertex_attributes._hoops_SAHIR[offset];
		_hoops_RPHIR *	sl = HI_LVA_Symbol_Lookup(_hoops_IPRI, *symbol);

		if (_hoops_ISAI(sl) == 0)
			HI_LVA_Symbol_Delete(_hoops_IPRI, sl);

		*flags &= ~_hoops_SIICA;
		_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIICA;

		if (--_hoops_SPRI->_hoops_AHIIC == 0) {
			FREE_ARRAY (_hoops_SPRI->_hoops_SAHIR, _hoops_IPRI->point_count, unsigned char);
			_hoops_SPRI->_hoops_SAHIR = null;
		}
		else
			_hoops_SPRI->_hoops_SAHIR[offset] = 0;

		if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
			_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
			FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
			_hoops_SPRI->flags = 0;
		}

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
	}
	else
		HE_ERROR (HEC_MARKER, HES_SYMBOL, "No marker symbol set on this vertex");

#endif
}

HC_INTERFACE void HC_CDECL HC_UnSet_Marker_Symbol (void) {
	_hoops_PAPPR context("UnSet_Marker_Symbol");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Marker_Symbol ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HRRPP|_hoops_GSIIR)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			HI_UnSet_Vertex_Symbol (context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset,
									_hoops_ASIIR->_hoops_GCRIR);
		}
		else
			HI_UnSet_Attribute (context, target, HK_MARKER_SYMBOL);

		_hoops_IRRPR();
	}

#endif
}




local Attribute *_hoops_ICPPS (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR)
{
	_hoops_PSAIR const *	_hoops_CCPPS = (_hoops_PSAIR const *)_hoops_CPACR;
	_hoops_PSAIR alter *	_hoops_SCPPS = (_hoops_PSAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_CCPPS != null &&
		_hoops_RAHSR(_hoops_CCPPS->line_style, _hoops_SCPPS->line_style) &&
		_hoops_RAHSR(_hoops_CCPPS->start_glyph, _hoops_SCPPS->start_glyph) &&
		_hoops_RAHSR(_hoops_CCPPS->middle_glyph, _hoops_SCPPS->middle_glyph) &&
		_hoops_RAHSR(_hoops_CCPPS->end_glyph, _hoops_SCPPS->end_glyph) &&
		_hoops_CCPPS->mask == _hoops_SCPPS->mask &&
		_hoops_CCPPS->value == _hoops_SCPPS->value)
		return null;


	if (_hoops_SCPPS->mask != 0 &&
		!ANYBIT(_hoops_SCPPS->mask, _hoops_CCCAP|_hoops_AICAP) &&
		_hoops_CCPPS && _hoops_CCPPS->line_style.length > 0) {
		/* _hoops_CAPGP _hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_PGRIP */
		ASSERT(_hoops_SCPPS->line_style.text == null);
		HI_Copy_Name(&_hoops_CCPPS->line_style, &_hoops_SCPPS->line_style);
		_hoops_SCPPS->mask |= _hoops_AICAP;
	}

	if (!BIT(_hoops_SCPPS->mask, _hoops_SICAP) &&
		_hoops_CCPPS && _hoops_CCPPS->start_glyph.length > 0) {
		ASSERT(_hoops_SCPPS->start_glyph.text == null);
		HI_Copy_Name(&_hoops_CCPPS->start_glyph, &_hoops_SCPPS->start_glyph);
	}

	if (!BIT(_hoops_SCPPS->mask, _hoops_RCCAP) &&
		!BIT(_hoops_SCPPS->value, _hoops_RCCAP) &&
		_hoops_CCPPS && _hoops_CCPPS->middle_glyph.length > 0) {
		ASSERT(_hoops_SCPPS->middle_glyph.text == null);
		HI_Copy_Name(&_hoops_CCPPS->middle_glyph, &_hoops_SCPPS->middle_glyph);
	}

	if (!ANYBIT(_hoops_SCPPS->mask, _hoops_GCCAP|_hoops_PCCAP) &&
		!ANYBIT(_hoops_SCPPS->value, _hoops_GCCAP|_hoops_PCCAP) &&
		_hoops_CCPPS && _hoops_CCPPS->end_glyph.length > 0) {
		ASSERT(_hoops_SCPPS->end_glyph.text == null);
		HI_Copy_Name(&_hoops_CCPPS->end_glyph, &_hoops_SCPPS->end_glyph);
	}

	if (_hoops_SCPPS->line_style.length > 0)
		_hoops_HCARA(_hoops_SCPPS->line_style, _hoops_SCPPS->_hoops_SCCAP);

	if (_hoops_SCPPS->start_glyph.length > 0)
		_hoops_HCARA(_hoops_SCPPS->start_glyph, _hoops_SCPPS->_hoops_GSCAP);

	if (_hoops_SCPPS->middle_glyph.length > 0)
		_hoops_HCARA(_hoops_SCPPS->middle_glyph, _hoops_SCPPS->_hoops_RSCAP);

	if (_hoops_SCPPS->end_glyph.length > 0)
		_hoops_HCARA(_hoops_SCPPS->end_glyph, _hoops_SCPPS->_hoops_ASCAP);

	return _hoops_SCPPS;
}

GLOBAL_FUNCTION bool HI_Set_Line_Pattern(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_PSAIR *	_hoops_HSAIR)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_LINE_PATTERN, _hoops_ICPPS, _hoops_HSAIR);
}



local Attribute *_hoops_GSPPS (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR)
{
	_hoops_ISAIR const *	_hoops_RSPPS = (_hoops_ISAIR const *)_hoops_CPACR;
	_hoops_ISAIR alter *	_hoops_ASPPS = (_hoops_ISAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_RSPPS != null &&
		_hoops_RSPPS->mask == _hoops_ASPPS->mask &&
		_hoops_RSPPS->value == _hoops_ASPPS->value &&
		_hoops_RAHSR(_hoops_RSPPS->line_style, _hoops_ASPPS->line_style))
		return null;

	if (_hoops_ASPPS->mask != 0 &&
		!ANYBIT(_hoops_ASPPS->mask, _hoops_CCCAP|_hoops_AICAP) &&
		_hoops_RSPPS && _hoops_RSPPS->line_style.length > 0) {
		ASSERT(_hoops_ASPPS->line_style.text == null);
		HI_Copy_Name(&_hoops_RSPPS->line_style, &_hoops_ASPPS->line_style);
		_hoops_ASPPS->mask |= _hoops_AICAP;
	}

	if (_hoops_ASPPS->line_style.length > 0)
		_hoops_HCARA(_hoops_ASPPS->line_style, _hoops_ASPPS->_hoops_SCCAP);

	return _hoops_ASPPS;
}

GLOBAL_FUNCTION bool HI_Set_Edge_Pattern (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ISAIR *	_hoops_CSAIR)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_EDGE_PATTERN, _hoops_GSPPS, _hoops_CSAIR);
}


GLOBAL_FUNCTION bool HI_Set_Edge_Pattern(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_ISAIR *	_hoops_CSAIR)
{
	_hoops_ICIIR(_hoops_RIGC);

	ASSERT(_hoops_GCRIR == _hoops_CCRIR);

#ifdef _hoops_RGIPR
	_hoops_IRPPR ("Geometry Edge Attributes");
#else
	if (_hoops_IPRI->_hoops_IHHPR._hoops_AHHIR == null)
		HI_Initialize_Edge_Attributes (_hoops_IPRI, _hoops_GPGI);

	_hoops_GHHPR * flags = &_hoops_IPRI->_hoops_IHHPR.flags[offset];
	unsigned char * _hoops_IPRSR = &_hoops_IPRI->_hoops_IHHPR._hoops_AHHIR[offset];

	_hoops_HHHIR * _hoops_IHHIR = HI_LEA_Pattern_Init(_hoops_IPRI, &_hoops_CSAIR->line_style);

	if (BIT (*flags, _hoops_GPGI) && _hoops_IHHIR->id == *_hoops_IPRSR)
		goto _hoops_PRSPR;

	if (!BIT (*flags, _hoops_GPGI)) {
		*flags |= _hoops_GPGI;
		++_hoops_IPRI->_hoops_IHHPR._hoops_SRAPA;
	}
	else {
		_hoops_HHHIR			 *_hoops_HARSA;

		_hoops_HARSA = HI_LEA_Pattern_Lookup(_hoops_IPRI, *_hoops_IPRSR);
		if (_hoops_ISAI(_hoops_HARSA) == 0)
			HI_LEA_Pattern_Delete(_hoops_IPRI, _hoops_HARSA);
	}
	_hoops_CAHS(_hoops_IHHIR);
	*_hoops_IPRSR = _hoops_IHHIR->id;

	_hoops_IPRI->_hoops_RSHPR &= ~_hoops_GPGI;
	_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);

_hoops_PRSPR:
#endif
	return false;
}

local const _hoops_IGRCR _hoops_PSPPS[] = {
	{LCAP_BUTT,					_hoops_GRRCR ("|"),			_hoops_RRRCR, 0, false},
	{LCAP_ROUND,				_hoops_GRRCR ("("),			_hoops_RRRCR, 0, false},
	{LCAP_ROUND,				_hoops_GRRCR (")"),			_hoops_RRRCR, 0, false},
	{LCAP_SQUARE,				_hoops_GRRCR ("["),			_hoops_RRRCR, 0, false},
	{LCAP_SQUARE,				_hoops_GRRCR ("]"),			_hoops_RRRCR, 0, false},
	{LCAP_TRIANGLE,				_hoops_GRRCR (">"),			_hoops_RRRCR, 0, false},
	{LCAP_TRIANGLE,				_hoops_GRRCR ("<"),			_hoops_RRRCR, 0, false},
};
local const _hoops_IGRCR _hoops_HSPPS[] = {
	{LCAP_END_BUTT,				_hoops_GRRCR ("|"),			_hoops_RRRCR, 0, false},
	{LCAP_END_ROUND,			_hoops_GRRCR ("("),			_hoops_RRRCR, 0, false},
	{LCAP_END_ROUND,			_hoops_GRRCR (")"),			_hoops_RRRCR, 0, false},
	{LCAP_END_SQUARE,			_hoops_GRRCR ("["),			_hoops_RRRCR, 0, false},
	{LCAP_END_SQUARE,			_hoops_GRRCR ("]"),			_hoops_RRRCR, 0, false},
	{LCAP_END_TRIANGLE,			_hoops_GRRCR ("<"),			_hoops_RRRCR, 0, false},
	{LCAP_END_TRIANGLE,			_hoops_GRRCR (">"),			_hoops_RRRCR, 0, false},
};
local const _hoops_IGRCR _hoops_ISPPS[] = {
	{LPAT_ROUND,				_hoops_GRRCR ("@"),			_hoops_RRRCR, 0, false},
	{LPAT_SQUARE,				_hoops_GRRCR ("#"),			_hoops_RRRCR, 0, false},
	{LPAT_TRIANGLE,				_hoops_GRRCR ("^"),			_hoops_RRRCR, 0, false},
};
local const _hoops_IGRCR _hoops_CSPPS[] = {
	{LJOIN_MITER,				_hoops_GRRCR ("<"),			_hoops_RRRCR, 0, false},
	{LJOIN_MITER,				_hoops_GRRCR (">"),			_hoops_RRRCR, 0, false},
	{LJOIN_ROUND,				_hoops_GRRCR ("("),			_hoops_RRRCR, 0, false},
	{LJOIN_ROUND,				_hoops_GRRCR (")"),			_hoops_RRRCR, 0, false},
	{LJOIN_BEVEL,				_hoops_GRRCR ("|"),			_hoops_RRRCR, 0, false},
	{LJOIN_BEVEL,				_hoops_GRRCR ("["),			_hoops_RRRCR, 0, false},
	{LJOIN_BEVEL,				_hoops_GRRCR ("]"),			_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_SSPPS = {
	_hoops_GGAPR (_hoops_PSPPS), _hoops_PSPPS,
};
local const _hoops_HPAGA _hoops_GGHPS = {
	_hoops_GGAPR (_hoops_HSPPS), _hoops_HSPPS,
};
local const _hoops_HPAGA _hoops_RGHPS = {
	_hoops_GGAPR (_hoops_ISPPS), _hoops_ISPPS,
};
local const _hoops_HPAGA _hoops_AGHPS = {
	_hoops_GGAPR (_hoops_CSPPS), _hoops_CSPPS,
};

local const _hoops_IGRCR _hoops_PGHPS[] = {
	{_hoops_AICAP,		_hoops_GRRCR ("line style"),		_hoops_ARSAP,	-999, true},
	{_hoops_PICAP,				_hoops_GRRCR ("start cap"),			_hoops_GHAGA,	1, true, &_hoops_SSPPS},
	{_hoops_PICAP,				_hoops_GRRCR ("start caps"),		_hoops_GHAGA,	1, true, &_hoops_SSPPS},
	{_hoops_PICAP,				_hoops_GRRCR ("caps"),				_hoops_GHAGA,	1, true, &_hoops_SSPPS},
	{_hoops_HICAP,			_hoops_GRRCR ("end cap"),			_hoops_GHAGA,	1, true, &_hoops_GGHPS},
	{_hoops_HICAP,			_hoops_GRRCR ("end caps"),			_hoops_GHAGA,	1, true, &_hoops_GGHPS},
	{_hoops_IICAP,			_hoops_GRRCR ("inner cap"),			_hoops_GHAGA,	1, true, &_hoops_RGHPS},
	{_hoops_IICAP,			_hoops_GRRCR ("inner caps"),		_hoops_GHAGA,	1, true, &_hoops_RGHPS},
	{_hoops_CICAP,				_hoops_GRRCR ("join"),				_hoops_GHAGA,	1, true, &_hoops_AGHPS},
	{_hoops_CICAP,				_hoops_GRRCR ("joins"),				_hoops_GHAGA,	1, true, &_hoops_AGHPS},

	{_hoops_ICCAP,		_hoops_GRRCR ("unset glyphs"),		_hoops_RRRCR,	0, false},
	{_hoops_SICAP,		_hoops_GRRCR ("start glyph"),		_hoops_ARSAP,	-999, true},
	{_hoops_RCCAP,		_hoops_GRRCR ("middle glyph"),		_hoops_ARSAP,	-999, true},
	{_hoops_GCCAP,			_hoops_GRRCR ("end glyph"),			_hoops_ARSAP,	-999, true},
	{_hoops_ACCAP,			_hoops_GRRCR ("glyphs"),			_hoops_ARSAP,	-999, true},
	{_hoops_SICAP,		_hoops_GRRCR ("start glyph arrow"),	_hoops_ARSAP,	-999, true},
	{_hoops_PCCAP,	_hoops_GRRCR ("end glyph arrow"),	_hoops_ARSAP,	-999, true},
	{_hoops_HCCAP,			_hoops_GRRCR ("arrows"),			_hoops_ARSAP,	-999, true},
};





HC_INTERFACE void HC_CDECL HC_Set_Line_Pattern_Explicit (
	char const *		pattern)
{
	_hoops_PAPPR context("Set_Line_Pattern_Explicit");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Line_Pattern_Explicit (%S);\n", pattern));
	);

	_hoops_HIACR (_hoops_CHRGI, _hoops_PGHPS);

	bool					used = false;
	_hoops_PSAIR *	_hoops_HSAIR;
	ZALLOC (_hoops_HSAIR, _hoops_PSAIR);

	Option_Value *	option_list;
	if (HI_Parse_Options (context, pattern, _hoops_CIACR (_hoops_CHRGI), &option_list, _hoops_SIACR)) {
		Option_Value *	option;

		if ((option = option_list) != null) do {
			_hoops_HSAIR->mask |= option->type->id;

			long _hoops_HGHPS=0;
			if (option->type->_hoops_RCIIR == _hoops_GHAGA && !option->_hoops_GCACR)
				_hoops_HGHPS = (*((*(((*option).value).option_list)).type)).id;

			switch (option->type->id) {
				case _hoops_ICCAP: {} break;

				case _hoops_AICAP: {
					_hoops_RGAIR(_hoops_HSAIR->line_style);
					if (!option->_hoops_GCACR)
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->line_style);
					else
						_hoops_HSAIR->mask |= _hoops_CCCAP;
				}	break;

				case _hoops_PICAP: {
					_hoops_HSAIR->value &= ~LCAP_MASK;
					if (!option->_hoops_GCACR)
						_hoops_HSAIR->value |= _hoops_HGHPS;
				}	break;

				case _hoops_HICAP: {
					_hoops_HSAIR->value &= ~LCAP_END_MASK;
					if (!option->_hoops_GCACR)
						_hoops_HSAIR->value |= _hoops_HGHPS;
				}	break;

				case _hoops_IICAP: {
					_hoops_HSAIR->value &= ~LPAT_MASK;
					if (!option->_hoops_GCACR)
						_hoops_HSAIR->value |= _hoops_HGHPS;
				}	break;

				case _hoops_CICAP: {
					_hoops_HSAIR->value &= ~LJOIN_MASK;
					if (!option->_hoops_GCACR)
						_hoops_HSAIR->value |= _hoops_HGHPS;
				}	break;

				case _hoops_SICAP: {
					_hoops_RGAIR(_hoops_HSAIR->start_glyph);
					if (!option->_hoops_GCACR)
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->start_glyph);
				}	break;

				case _hoops_RCCAP: {
					_hoops_RGAIR(_hoops_HSAIR->middle_glyph);
					if (!option->_hoops_GCACR)
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->middle_glyph);
				}	break;

				case _hoops_GCCAP: {
					_hoops_RGAIR(_hoops_HSAIR->end_glyph);
					if (!option->_hoops_GCACR)
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->end_glyph);
					_hoops_HSAIR->mask &= ~_hoops_PCCAP;
				}	break;

				case _hoops_ACCAP: {
					_hoops_RGAIR(_hoops_HSAIR->start_glyph);
					_hoops_RGAIR(_hoops_HSAIR->middle_glyph);
					_hoops_RGAIR(_hoops_HSAIR->end_glyph);
					if (!option->_hoops_GCACR) {
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->start_glyph);
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->middle_glyph);
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->end_glyph);
					}
					_hoops_HSAIR->mask &= ~_hoops_PCCAP;
				}	break;

				case _hoops_PCCAP: {
					_hoops_RGAIR(_hoops_HSAIR->end_glyph);
					if (!option->_hoops_GCACR)
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->end_glyph);
					_hoops_HSAIR->mask &= ~_hoops_GCCAP;
				}	break;

				case _hoops_HCCAP: {
					_hoops_RGAIR(_hoops_HSAIR->start_glyph);
					_hoops_RGAIR(_hoops_HSAIR->end_glyph);
					if (!option->_hoops_GCACR) {
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->start_glyph);
						HI_Copy_Name (&option->value._name[0], &_hoops_HSAIR->end_glyph);
					}
					_hoops_HSAIR->mask &= ~_hoops_GCCAP;
				}	break;

				default: {
					HE_ERROR (HEC_LINE_STYLE, HES_INVALID_OPTION, "Unknown line pattern option");
				} break;
			}
		} while ((option = option->next) != null);

		if (option_list)
			HI_Free_Option_List (context, option_list);

		/* _hoops_HSPP _hoops_RPHH _hoops_HRGR _hoops_IGHPS _hoops_IH _hoops_HSPP _hoops_RPHH _hoops_PPR _hoops_RSGR _hoops_RPHH */
		if (BIT(_hoops_HSAIR->mask, _hoops_SICAP) &&
			!BIT(_hoops_HSAIR->mask, _hoops_GCCAP) &&
			!BIT(_hoops_HSAIR->mask, _hoops_PCCAP)) {
			_hoops_HSAIR->mask |= _hoops_GCCAP;
			_hoops_RGAIR(_hoops_HSAIR->end_glyph);
			HI_Copy_Name (&_hoops_HSAIR->start_glyph, &_hoops_HSAIR->end_glyph);
		}

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_ARRPP)) != null) {
			used = HI_Set_Line_Pattern(context, target, _hoops_HSAIR);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		_hoops_RGAIR(_hoops_HSAIR->line_style);
		_hoops_RGAIR(_hoops_HSAIR->start_glyph);
		_hoops_RGAIR(_hoops_HSAIR->end_glyph);
		_hoops_RGAIR(_hoops_HSAIR->middle_glyph);
		FREE (_hoops_HSAIR, _hoops_PSAIR);
	}
}




HC_INTERFACE void HC_CDECL HC_Set_Edge_Pattern_Explicit (
	char const *		pattern)
{
	_hoops_PAPPR context("Set_Edge_Pattern_Explicit");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Edge_Pattern_Explicit (%S);\n", pattern));
	);

	_hoops_HIACR (_hoops_CHRGI, _hoops_PGHPS);

	bool					used = false;
	_hoops_ISAIR *	_hoops_CSAIR;
	ZALLOC(_hoops_CSAIR, _hoops_ISAIR);

	Option_Value *	option_list;
	if (HI_Parse_Options (context, pattern, _hoops_CIACR (_hoops_CHRGI), &option_list, _hoops_SIACR)) {
		Option_Value *	option;

		if ((option = option_list) != null) do {
			_hoops_CSAIR->mask |= option->type->id;

			long _hoops_HGHPS=0;
			if (option->type->_hoops_RCIIR == _hoops_GHAGA && !option->_hoops_GCACR)
				_hoops_HGHPS = (*((*(((*option).value).option_list)).type)).id;

			switch (option->type->id) {
				case _hoops_AICAP: {
					_hoops_RGAIR(_hoops_CSAIR->line_style);
					if (!option->_hoops_GCACR)
						HI_Copy_Name (&option->value._name[0], &_hoops_CSAIR->line_style);
					else
						_hoops_CSAIR->mask |= _hoops_CCCAP;
				}	break;

				case _hoops_IICAP: {
					_hoops_CSAIR->value &= ~LPAT_MASK;
					if (!option->_hoops_GCACR)
						_hoops_CSAIR->value |= _hoops_HGHPS;
				}	break;

				case _hoops_CICAP: {
					_hoops_CSAIR->value &= ~LJOIN_MASK;
					if (!option->_hoops_GCACR)
						_hoops_CSAIR->value |= _hoops_HGHPS;
				}	break;

				default: {
					HE_ERROR (HEC_LINE_STYLE, HES_INVALID_OPTION, "Unknown edge pattern option");
				} break;
			}
		} while ((option = option->next) != null);

		if (option_list)
			HI_Free_Option_List (context, option_list);

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_PRRPP)) != null) {
			used = HI_Set_Edge_Pattern(context, target, _hoops_CSAIR);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		_hoops_RGAIR(_hoops_CSAIR->line_style);
		FREE(_hoops_CSAIR, _hoops_ISAIR);
	}
}

HC_INTERFACE void HC_CDECL HC_Set_Line_Pattern (
	char const *		pattern)
{
	_hoops_PAPPR context("Set_Line_Pattern");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Line_Pattern (%S);\n", pattern));
	);

	bool					used = false;
	_hoops_PSAIR *	_hoops_HSAIR;
	ZALLOC(_hoops_HSAIR, _hoops_PSAIR);

	HI_Canonize_Line_Pattern(pattern, &_hoops_HSAIR->line_style, &_hoops_HSAIR->value);

	if (_hoops_HSAIR->line_style.length == 0) {
		HE_ERROR (HEC_PATTERN, HES_INVALID_INPUT, "Line Pattern is blank or null");
	}
	else {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_ARRPP)) != null) {
			used = HI_Set_Line_Pattern(context, target, _hoops_HSAIR);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		_hoops_RGAIR(_hoops_HSAIR->line_style);
		FREE (_hoops_HSAIR, _hoops_PSAIR);
	}
}


HC_INTERFACE void HC_CDECL HC_UnSet_Line_Pattern (void)
{
	_hoops_PAPPR context("UnSet_Line_Pattern");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Line_Pattern ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ARRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_LINE_PATTERN);
		_hoops_IRRPR();
	}
}




HC_INTERFACE void HC_CDECL HC_Set_Edge_Pattern (
	char const *			pattern)
{
	_hoops_PAPPR context("Set_Edge_Pattern");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Edge_Pattern (%S);\n", pattern));
	);

	bool					used = false;
	_hoops_ISAIR *	_hoops_CSAIR;
	ZALLOC (_hoops_CSAIR, _hoops_ISAIR);

	HI_Canonize_Line_Pattern(pattern, &_hoops_CSAIR->line_style, &_hoops_CSAIR->value);

	if (_hoops_CSAIR->line_style.length == 0) {
		HE_ERROR (HEC_PATTERN, HES_INVALID_INPUT, "Edge Pattern is blank or null");
	}
	else {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_PRRPP)) != null) {
			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Edge_Pattern (context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset,
											_hoops_ASIIR->_hoops_GCRIR, _hoops_CSAIR);
			}
			else
				used = HI_Set_Edge_Pattern (context, target, _hoops_CSAIR);

			_hoops_IRRPR();
		}
	}

	if (!used) {
		_hoops_RGAIR(_hoops_CSAIR->line_style);
		FREE (_hoops_CSAIR, _hoops_ISAIR);
	}
}


GLOBAL_FUNCTION void HI_UnSet_Edge_Pattern(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset)
{
	_hoops_ICIIR(_hoops_RIGC);
#ifndef DISABLE_GEOMETRY_EDIT

	_hoops_RPGHR *	lea = &_hoops_IPRI->_hoops_IHHPR;
	_hoops_GHHPR *		flags;

	if ((flags = lea->flags) == null ||
		!BIT (flags[offset], _hoops_GPGI)) {
		HE_ERROR (HEC_EDGE, HES_PATTERN, "No pattern set on this edge");
		return;
	}

	flags[offset] &= ~_hoops_GPGI;
	_hoops_IPRI->_hoops_RSHPR &= ~_hoops_GPGI;

	if (--lea->_hoops_SRAPA == 0) {
		FREE_ARRAY (lea->_hoops_AHHIR, _hoops_IPRI->_hoops_SPHA, unsigned char);
		lea->_hoops_AHHIR = null;
	}
	else
		lea->_hoops_AHHIR[offset] = 0;

	_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
#endif
}

HC_INTERFACE void HC_CDECL HC_UnSet_Edge_Pattern (void)
{
	_hoops_PAPPR context("UnSet_Edge_Pattern");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Edge_Pattern ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PRRPP|_hoops_GSIIR)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			ASSERT(_hoops_ASIIR->_hoops_GCRIR == _hoops_CCRIR);
			HI_UnSet_Edge_Pattern(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset);
		}
		else
			HI_UnSet_Attribute (context, target, HK_EDGE_PATTERN);

		_hoops_IRRPR();
	}

#endif
}





#ifndef DISABLE_SHOW
local void _hoops_CGHPS (
	_hoops_GICAP const *	_hoops_SGHPS,
	char *					pattern,
	int						_hoops_RCSIH)
{
	HI_Return_Chars (pattern, _hoops_RCSIH, _hoops_SGHPS->name.text, _hoops_SGHPS->name.length);
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_Marker_Symbol (
	char *					pattern)
{
	_hoops_PAPPR context("Show_Marker_Symbol");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Marker_Symbol () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_AIRPP)) != null) {
		_hoops_GICAP *		_hoops_SGHPS;
		if ((_hoops_SGHPS = (_hoops_GICAP *)HI_Find_Attribute (context, target, HK_MARKER_SYMBOL)) != null) {
			_hoops_CGHPS (_hoops_SGHPS, pattern, -1);
			_hoops_HPRH (_hoops_SGHPS);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Marker_Symbol (
	int						count,
	Key const *				keys,
	char *					pattern)
{
	_hoops_PAPPR context("PShow_Net_Marker_Symbol");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Marker_Symbol () */\n");
	);

	_hoops_GICAP *	_hoops_SGHPS;
	if ((_hoops_SGHPS = (_hoops_GICAP *) HI_Find_Attribute_And_Lock(context, _hoops_AIRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_CGHPS (_hoops_SGHPS, pattern, -1);
		_hoops_HPRH (_hoops_SGHPS);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);

#endif
}
#endif



#ifndef DISABLE_SHOW
local char const * _hoops_CIHHC (void) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized pattern type");
			return "";
}

local char *_hoops_GRHPS (
	_hoops_ISAIR *	_hoops_HSAIR,
	char *					_hoops_ASAPR)
{
	char *					_hoops_RRHPS = _hoops_ASAPR;
	char *					text;

	if (_hoops_HSAIR->mask == 0) {
		switch (_hoops_HSAIR->value & LCAP_START_MASK) {
			case LCAP_BUTT:							break;
			case LCAP_ROUND:		*_hoops_ASAPR++ = '(';	break;
			case LCAP_SQUARE:		*_hoops_ASAPR++ = '[';	break;
			case LCAP_TRIANGLE:		*_hoops_ASAPR++ = '<';	break;
			default:		(void)_hoops_CIHHC();			return _hoops_RRHPS;			_hoops_HHHI;
		}

		if (_hoops_HSAIR->value & LCAP_END_MASK) {
			switch (_hoops_HSAIR->value & LCAP_END_MASK) {
				case LCAP_END_BUTT:			*_hoops_ASAPR++ = '|';	break;
				case LCAP_END_ROUND:		*_hoops_ASAPR++ = '(';	break;
				case LCAP_END_SQUARE:		*_hoops_ASAPR++ = '[';	break;
				case LCAP_END_TRIANGLE:		*_hoops_ASAPR++ = '<';	break;
				default:		(void)_hoops_CIHHC();				return _hoops_RRHPS;	_hoops_HHHI;
			}
		}

		text = _hoops_HSAIR->line_style.text;
		if (text[1] == '\0') {
			/* '.' _hoops_PPR '-' _hoops_CHR _hoops_HSHA _hoops_GAR _hoops_GRH _hoops_ARAR _hoops_IS _hoops_PSSP _hoops_PAII _hoops_IRRIR _hoops_RPCC, _hoops_PRGI
			 * _hoops_PHRI _hoops_SSIA _hoops_CHR _hoops_RPPR _hoops_CPCIP */
			if (text[0] == '.')
				_hoops_ASAPR = HI_Copy_Chars ("...", _hoops_ASAPR);
			else if (text[0] == '-')
				_hoops_ASAPR = HI_Copy_Chars ("---", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars (_hoops_HSAIR->line_style.text, _hoops_ASAPR);
		}
		else
			_hoops_ASAPR = HI_Copy_Chars (_hoops_HSAIR->line_style.text, _hoops_ASAPR);

		switch (_hoops_HSAIR->value & LJOIN_MASK) {
			case LJOIN_MITER:						break;
			case LJOIN_ROUND:		*_hoops_ASAPR++ = ')';	break;
			case LJOIN_BEVEL:		*_hoops_ASAPR++ = '|';	break;

			default:		(void)_hoops_CIHHC();			return _hoops_RRHPS;			_hoops_HHHI;
		}

		switch (_hoops_HSAIR->value & LPAT_MASK) {
			case LPAT_BUTT:							break;
			case LPAT_ROUND:		*_hoops_ASAPR++ = '@';	break;
			case LPAT_SQUARE:		*_hoops_ASAPR++ = '#';	break;
			case LPAT_TRIANGLE:		*_hoops_ASAPR++ = '^';	break;

			default:		(void)_hoops_CIHHC();			return _hoops_RRHPS;			_hoops_HHHI;
		}
	}
	else {
		/* _hoops_CCAH _hoops_SHIPH _hoops_RRGR */
	}
	return _hoops_ASAPR;
}

local char *_hoops_GRHPS (
	_hoops_PSAIR *	_hoops_HSAIR,
	char *					_hoops_ASAPR)
{
	_hoops_ISAIR _hoops_CSAIR;
	ZERO_STRUCT(&_hoops_CSAIR, _hoops_ISAIR);
	_hoops_CSAIR.mask = _hoops_HSAIR->mask;
	_hoops_CSAIR.value = _hoops_HSAIR->value;
	_hoops_CSAIR.line_style.length = _hoops_HSAIR->line_style.length;
	_hoops_CSAIR.line_style.text = _hoops_HSAIR->line_style.text;
	return _hoops_GRHPS(&_hoops_CSAIR, _hoops_ASAPR);
}

#endif


GLOBAL_FUNCTION void HI_Show_Edge_Pattern_Explicit (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_ISAIR *		_hoops_CSAIR,
	char *						pattern,
	int							_hoops_RCSIH)
{
	UNREFERENCED(_hoops_RIGC);
#ifndef _hoops_RSIIH
	char							buf[4096];
	char							*p = buf;
	Integer32						mask = _hoops_CSAIR->mask;
	Integer32						value = _hoops_CSAIR->value;

	if (ANYBIT(mask, _hoops_AICAP|_hoops_CCCAP)) {
		if (BIT(mask, _hoops_CCCAP) || _hoops_CSAIR->line_style.length == 0) {
			p = HI_Copy_Chars ("no line style", p);
		}
		else {
			p = HI_Copy_Chars ("line style=", p);
			p = HI_Copy_Chars (_hoops_CSAIR->line_style.text, p);
		}
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_IICAP)) {
		int _hoops_ARHPS = value & LPAT_MASK;
		switch (_hoops_ARHPS) {
			case LPAT_ROUND:	{ p = HI_Copy_Chars ("inner cap=@",	p); } break;
			case LPAT_SQUARE:	{ p = HI_Copy_Chars ("inner cap=#",	p); } break;
			case LPAT_TRIANGLE:	{ p = HI_Copy_Chars ("inner cap=^",	p); } break;
			default:		{ p = HI_Copy_Chars ("no inner cap", p); } break;
		}
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_CICAP)) {
		p = HI_Copy_Chars ("join=", p);
		int _hoops_PRHPS = value & LJOIN_MASK;
		switch (_hoops_PRHPS) {
			case LJOIN_BEVEL:	{ p = HI_Copy_Chars ("|",	p); } break;
			case LJOIN_ROUND:	{ p = HI_Copy_Chars ("'('",	p); } break;
			case LJOIN_MITER:
			default:		{ p = HI_Copy_Chars ("<",	p); } break;
		}
		p = HI_Copy_Chars (", ", p);
	}
	p-=2;

	HI_Return_Chars (pattern, _hoops_RCSIH, buf, (int)(p - buf));
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Edge_Pattern_Explicit (
	char *					pattern)
{
	_hoops_PAPPR context("Show_Edge_Pattern_Explicit");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Edge_Pattern_Explicit () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RIRPP)) != null) {
		_hoops_ISAIR *	_hoops_CSAIR;
		if ((_hoops_CSAIR = (_hoops_ISAIR *)HI_Find_Attribute (context, target, HK_EDGE_PATTERN)) != null) {
			HI_Show_Edge_Pattern_Explicit (context, _hoops_CSAIR, pattern, -1);
			_hoops_HPRH (_hoops_CSAIR);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Edge_Pattern_Exp (
	int						count,
	Key const *				keys,
	char *					pattern)
{
	_hoops_PAPPR context("PShow_Net_Edge_Pattern_Explicit");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Edge_Pattern_Explicit () */\n");
	);

	_hoops_ISAIR *	_hoops_CSAIR;
	if ((_hoops_CSAIR = (_hoops_ISAIR *) HI_Find_Attribute_And_Lock(context, _hoops_RIRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Edge_Pattern_Explicit (context, _hoops_CSAIR, pattern, -1);
		_hoops_HPRH (_hoops_CSAIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);

#endif
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_Edge_Pattern (
	char *					pattern)
{
	_hoops_PAPPR context("Show_Edge_Pattern");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Edge_Pattern () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RIRPP)) != null) {
		_hoops_ISAIR *	_hoops_CSAIR;
		if ((_hoops_CSAIR = (_hoops_ISAIR *)HI_Find_Attribute (context, target, HK_EDGE_PATTERN)) != null) {
			char *	buf;
			ALLOC_ARRAY(buf, _hoops_CSAIR->line_style.length+32, char);

			char *	p = _hoops_GRHPS (_hoops_CSAIR, buf);

			HI_Return_Chars (pattern, -1, buf, p - buf);

			FREE_ARRAY(buf, _hoops_CSAIR->line_style.length+32, char);

			/* _hoops_PSP _hoops_CCAH _hoops_SHIPH _hoops_RRGR? */
			_hoops_HPRH (_hoops_CSAIR);
		}
		_hoops_IRRPR();
	}
#endif
}


GLOBAL_FUNCTION void HI_Show_Line_Pattern_Explicit (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_PSAIR *		_hoops_HSAIR,
	char *						pattern,
	int							_hoops_RCSIH)
{
	UNREFERENCED(_hoops_RIGC);
#ifndef _hoops_RSIIH
	char							buf[4096];
	char							*p = buf;
	Integer32						mask = _hoops_HSAIR->mask;
	Integer32						value = _hoops_HSAIR->value;

	if (BIT(mask, _hoops_ICCAP)) {
		p = HI_Copy_Chars ("unset glyphs, ", p);
	}
	if (ANYBIT(mask, _hoops_AICAP|_hoops_CCCAP)) {
		if (BIT(mask, _hoops_CCCAP) || _hoops_HSAIR->line_style.length == 0) {
			p = HI_Copy_Chars ("no line style", p);
		}
		else {
			p = HI_Copy_Chars ("line style=", p);
			p = HI_Copy_Chars (_hoops_HSAIR->line_style.text, p);
		}
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_PICAP)) {
		p = HI_Copy_Chars ("start cap=", p);
		int _hoops_HRHPS = value & LCAP_START_MASK;
		switch (_hoops_HRHPS) {
			case LCAP_ROUND:	{ p = HI_Copy_Chars ("'('",	p); } break;
			case LCAP_SQUARE:	{ p = HI_Copy_Chars ("[",	p); } break;
			case LCAP_TRIANGLE:	{ p = HI_Copy_Chars ("<",	p); } break;
			case LCAP_BUTT:
			default:		{ p = HI_Copy_Chars ("|",	p); } break;
		}
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_HICAP)) {
		p = HI_Copy_Chars ("end cap=", p);
		int _hoops_IRHPS = value & LCAP_END_MASK;
		switch (_hoops_IRHPS) {
			case LCAP_END_ROUND:	{ p = HI_Copy_Chars ("')'",	p); } break;
			case LCAP_END_SQUARE:	{ p = HI_Copy_Chars ("]",	p); } break;
			case LCAP_END_TRIANGLE:	{ p = HI_Copy_Chars (">",	p); } break;
			case LCAP_END_BUTT:
			default:			{ p = HI_Copy_Chars ("|",	p); } break;
		}
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_IICAP)) {
		int _hoops_ARHPS = value & LPAT_MASK;
		switch (_hoops_ARHPS) {
			case LPAT_ROUND:	{ p = HI_Copy_Chars ("inner cap=@",	p); } break;
			case LPAT_SQUARE:	{ p = HI_Copy_Chars ("inner cap=#",	p); } break;
			case LPAT_TRIANGLE:	{ p = HI_Copy_Chars ("inner cap=^",	p); } break;
			default:		{ p = HI_Copy_Chars ("no inner cap", p); } break;
		}
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_CICAP)) {
		p = HI_Copy_Chars ("join=", p);
		int _hoops_PRHPS = value & LJOIN_MASK;
		switch (_hoops_PRHPS) {
			case LJOIN_BEVEL:	{ p = HI_Copy_Chars ("|",	p); } break;
			case LJOIN_ROUND:	{ p = HI_Copy_Chars ("'('",	p); } break;
			case LJOIN_MITER:
			default:		{ p = HI_Copy_Chars ("<",	p); } break;
		}
		p = HI_Copy_Chars (", ", p);
	}
	if (ALLBITS(mask, _hoops_HCCAP)) {
		mask &= ~_hoops_HCCAP;
		if (_hoops_HSAIR->start_glyph.length != 0 && _hoops_HSAIR->end_glyph.length != 0) {
			if (_hoops_RAHSR(_hoops_HSAIR->start_glyph, _hoops_HSAIR->end_glyph)) {
				p = HI_Copy_Chars ("arrows=", p);
				p = HI_Copy_Chars (_hoops_HSAIR->start_glyph.text, p);
			}
			else {
				p = HI_Copy_Chars ("start glyph arrow=", p);
				p = HI_Copy_Chars (_hoops_HSAIR->start_glyph.text, p);
				p = HI_Copy_Chars (", end glyph arrow=", p);
				p = HI_Copy_Chars (_hoops_HSAIR->end_glyph.text, p);
			}
		}
		else
			p = HI_Copy_Chars ("no arrows", p);
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_PCCAP)) {
		if (_hoops_HSAIR->end_glyph.length != 0) {
			p = HI_Copy_Chars ("end glyph arrow=", p);
			p = HI_Copy_Chars (_hoops_HSAIR->end_glyph.text, p);
		}
		else
			p = HI_Copy_Chars ("no end glyph arrow", p);
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_SICAP)) {
		if (_hoops_HSAIR->start_glyph.length != 0) {
			p = HI_Copy_Chars ("start glyph=", p);
			p = HI_Copy_Chars (_hoops_HSAIR->start_glyph.text, p);
		}
		else
			p = HI_Copy_Chars ("no start glyph", p);
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_GCCAP)) {
		if (_hoops_HSAIR->end_glyph.length != 0) {
			p = HI_Copy_Chars ("end glyph=", p);
			p = HI_Copy_Chars (_hoops_HSAIR->end_glyph.text, p);
		}
		else
			p = HI_Copy_Chars ("no end glyph", p);
		p = HI_Copy_Chars (", ", p);
	}
	if (BIT(mask, _hoops_RCCAP)) {
		if (_hoops_HSAIR->middle_glyph.length != 0) {
			p = HI_Copy_Chars ("middle glyph=", p);
			p = HI_Copy_Chars (_hoops_HSAIR->middle_glyph.text, p);
		}
		else
			p = HI_Copy_Chars ("no middle glyph", p);
		p = HI_Copy_Chars (", ", p);
	}
	p-=2;

	HI_Return_Chars (pattern, _hoops_RCSIH, buf, (int)(p - buf));
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Line_Pattern_Explicit (
	char *					pattern)
{
	_hoops_PAPPR context("Show_Line_Pattern_Explicit");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Line_Pattern_Explicit () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GIRPP)) != null) {
		_hoops_PSAIR *	_hoops_HSAIR;
		if ((_hoops_HSAIR = (_hoops_PSAIR *)HI_Find_Attribute (context, target, HK_LINE_PATTERN)) != null) {
			HI_Show_Line_Pattern_Explicit (context, _hoops_HSAIR, pattern, -1);
			_hoops_HPRH (_hoops_HSAIR);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Pattern_Exp (
	int						count,
	Key const *				keys,
	char *					pattern)
{
	_hoops_PAPPR context("PShow_Net_Line_Pattern_Explicit");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Line_Pattern_Explicit () */\n");
	);

	_hoops_PSAIR *	_hoops_HSAIR;
	if ((_hoops_HSAIR = (_hoops_PSAIR *) HI_Find_Attribute_And_Lock(context, _hoops_GIRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Line_Pattern_Explicit (context, _hoops_HSAIR, pattern, -1);
		_hoops_HPRH (_hoops_HSAIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);

#endif
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Line_Pattern (
	char *					pattern)
{
	_hoops_PAPPR context("Show_Line_Pattern");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Line_Pattern () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GIRPP)) != null) {
		_hoops_PSAIR *	_hoops_HSAIR;
		if ((_hoops_HSAIR = (_hoops_PSAIR *)HI_Find_Attribute (context, target, HK_LINE_PATTERN)) != null) {
			char *	buf;
			ALLOC_ARRAY(buf, _hoops_HSAIR->line_style.length+32, char);

			char *	p = _hoops_GRHPS (_hoops_HSAIR, buf);

			HI_Return_Chars (pattern, -1, buf, p - buf);

			FREE_ARRAY(buf, _hoops_HSAIR->line_style.length+32, char);

			/* _hoops_PSP _hoops_CCAH _hoops_SHIPH _hoops_RRGR? */
			_hoops_HPRH (_hoops_HSAIR);
		}
		_hoops_IRRPR();
	}
#endif
}




#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Edge_Pattern (
	int						count,
	Key const *				keys,
	char *					pattern)
{
	_hoops_PAPPR context("PShow_Net_Edge_Pattern");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Edge_Pattern () */\n");
	);

	_hoops_ISAIR *	_hoops_CSAIR;
	if ((_hoops_CSAIR = (_hoops_ISAIR *) HI_Find_Attribute_And_Lock(context, _hoops_RIRPP, _hoops_HRPCR, count, keys)) != null) {
		char *	buf;
		ALLOC_ARRAY(buf, _hoops_CSAIR->line_style.length+32, char);

		char *	p = _hoops_GRHPS (_hoops_CSAIR, buf);

		HI_Return_Chars (pattern, -1, buf, p - buf);

		FREE_ARRAY(buf, _hoops_CSAIR->line_style.length+32, char);

		_hoops_HPRH (_hoops_CSAIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);
#endif
}
#endif


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Pattern (
	int						count,
	Key const *				keys,
	char *					pattern)
{
	_hoops_PAPPR context("PShow_Net_Line_Pattern");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Line_Pattern () */\n");
	);

	_hoops_PSAIR *	_hoops_HSAIR;
	if ((_hoops_HSAIR = (_hoops_PSAIR *) HI_Find_Attribute_And_Lock(context, _hoops_GIRPP, _hoops_HRPCR, count, keys)) != null) {
		char *	buf;

		ALLOC_ARRAY(buf, _hoops_HSAIR->line_style.length+32, char);

		char *	p = _hoops_GRHPS (_hoops_HSAIR, buf);

		HI_Return_Chars (pattern, -1, buf, p - buf);

		FREE_ARRAY(buf, _hoops_HSAIR->line_style.length+32, char);

		/* _hoops_PSP _hoops_CCAH _hoops_SHIPH _hoops_RRGR? */
		_hoops_HPRH (_hoops_HSAIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(pattern, -1, "", 0);

#endif
}
#endif



