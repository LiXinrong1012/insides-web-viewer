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
 * $Id: obf_tmp.txt 1.88 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



local Attribute * _hoops_RCHHC (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR) 
{
	_hoops_AHPIR const *	_hoops_ACHHC = (_hoops_AHPIR const *)_hoops_CPACR;
	_hoops_AHPIR alter *	_hoops_PCHHC = (_hoops_AHPIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_ACHHC != null &&
		_hoops_ACHHC->data.value == _hoops_PCHHC->data.value &&
		_hoops_ACHHC->data._hoops_HHP == _hoops_PCHHC->data._hoops_HHP)
		return null;

	return _hoops_PCHHC;
}

GLOBAL_FUNCTION bool HI_Set_Line_Weight(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				target, 
	_hoops_AHPIR *		_hoops_GGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, target, HK_LINE_WEIGHT, _hoops_RCHHC, _hoops_GGGCH);
}

HC_INTERFACE void HC_CDECL HC_Set_Line_Weight (
	double					value) 
{
	_hoops_PAPPR context("Set_Line_Weight");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Set_Line_Weight (%F);\n", value));
	);

	if (value < 0.0f) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_WEIGHT, "Unreasonable (negative!) line weight");
		return;
	}

	bool				used = false;
	_hoops_AHPIR *	_hoops_GGGCH;
	ZALLOC (_hoops_GGGCH, _hoops_AHPIR);
	_hoops_GGGCH->data.value = (float)value;
	_hoops_GGGCH->data._hoops_HHP = _hoops_SHGRP;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IRRPP)) != null) {
		used = HI_Set_Line_Weight(context, target, _hoops_GGGCH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_GGGCH, _hoops_AHPIR);

}

HC_INTERFACE void HC_CDECL HC_Set_Variable_Line_Weight (
	char const *			options) 
{
	_hoops_PAPPR context("Set_Variable_Line_Weight");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Variable_Line_Weight (%S);\n", options));
	);

	bool				used = false;
	_hoops_AHPIR *	_hoops_GGGCH;
	ZALLOC (_hoops_GGGCH, _hoops_AHPIR);

	char const *	_hoops_SSACR;
	if ((_hoops_SSACR = HI_Scan_Generic_Size (context, &_hoops_GGGCH->data, options, "Variable_Line_Weight")) != null) {
		char	_hoops_SSSSI [_hoops_CGHHP];
		HE_ERROR2 (HEC_SYNTAX, HES_PARSE_STRING, Sprintf_S (_hoops_SSSSI,"Error parsing option string '%s'", options), _hoops_SSACR);
		goto _hoops_PRSPR;
	}

	if (_hoops_GGGCH->data.value < 0.0f) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_WEIGHT, "Unreasonable (negative!) line weight");
		goto _hoops_PRSPR;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IRRPP)) != null) {
		used = HI_Set_Line_Weight(context, target, _hoops_GGGCH);
		_hoops_IRRPR();
	}

_hoops_PRSPR:
	if (!used)
		FREE (_hoops_GGGCH, _hoops_AHPIR);
}


HC_INTERFACE void HC_CDECL HC_UnSet_Line_Weight (void) {
	_hoops_PAPPR context("UnSet_Line_Weight");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Line_Weight ();\n");
	);
	
	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IRRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_LINE_WEIGHT);
		_hoops_IRRPR();
	}
}




/* (_hoops_RH _hoops_HSPR _hoops_CIGR _hoops_HCHRC _hoops_HII _hoops_HCHHC) */
#define _hoops_HIHHC(_hoops_RSPGP, _hoops_ICHHC,x)	(BIT (_hoops_ICHHC->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_IIHHC (_hoops_RSPGP, _hoops_ICHHC,x) : _hoops_SASIR (_hoops_RSPGP, _hoops_ICHHC, _hoops_RAGGA | (x)))

#define _hoops_IIHHC(_hoops_RSPGP, _hoops_ICHHC,x) _hoops_SASIR (_hoops_RSPGP, _hoops_ICHHC, _hoops_GGARA | (x))



GLOBAL_FUNCTION bool HI_Set_Edge_Weight(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_AHPIR *		_hoops_GGGCH)
{
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(_hoops_GCRIR == _hoops_CCRIR);

#ifdef _hoops_RGIPR
	_hoops_IRPPR ("Geometry Edge Attributes");
#else

	if (_hoops_GGGCH->data._hoops_HHP != _hoops_SHGRP) {
		HE_ERROR (HEC_EDGE, HES_EDGE, "Variable edge weight not supported inside geometry");
		return false;
	}

	float	value = _hoops_GGGCH->data.value;

	if (_hoops_IPRI->_hoops_IHHPR.weights == null)
		HI_Initialize_Edge_Attributes (_hoops_IPRI, _hoops_SCICA);

	_hoops_GHHPR *	flags  = &_hoops_IPRI->_hoops_IHHPR.flags[offset];
	float *				weight = &_hoops_IPRI->_hoops_IHHPR.weights[offset];

	if (BIT (*flags, _hoops_SCICA) && value == *weight)
		goto Release; /* _hoops_IRAHR */

	if (!BIT (*flags, _hoops_SCICA)) {
		*flags |= _hoops_SCICA;
		++_hoops_IPRI->_hoops_IHHPR._hoops_CCHHC;
		_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
	}
	else if (value > *weight)
		_hoops_IIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
	else if (value < *weight)
		_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);

	*weight = value;

	_hoops_IPRI->_hoops_RSHPR &= ~_hoops_SCICA;

Release:
#endif
	return false;
}

GLOBAL_FUNCTION bool HI_Set_Edge_Weight (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_AHPIR *		_hoops_GGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_EDGE_WEIGHT, _hoops_RCHHC, _hoops_GGGCH);
}


HC_INTERFACE void HC_CDECL HC_Set_Edge_Weight (
	double			value) 
{
	_hoops_PAPPR context("Set_Edge_Weight");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Set_Edge_Weight (%F);\n", value));
	);

	if (value < 0.0) {
		HE_ERROR (HEC_EDGE, HES_INVALID_WEIGHT, "Unreasonable (negative!) edge weight");
		return;
	}

	bool			used = false;
	_hoops_AHPIR *	_hoops_GGGCH;
	ZALLOC (_hoops_GGGCH, _hoops_AHPIR);
	_hoops_GGGCH->data.value = (float)value;
	_hoops_GGGCH->data._hoops_HHP = _hoops_SHGRP;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CRRPP)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			used = HI_Set_Edge_Weight(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_GGGCH);
		}
		else
			used = HI_Set_Edge_Weight(context, target, _hoops_GGGCH);

		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_GGGCH, _hoops_AHPIR);
}


HC_INTERFACE void HC_CDECL HC_Set_Variable_Edge_Weight (
	char const *			options) 
{
	_hoops_PAPPR context("Set_Variable_Edge_Weight");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Variable_Edge_Weight (%S);\n", options));
	);

	bool				used = false;
	_hoops_AHPIR *	_hoops_GGGCH;
	ZALLOC (_hoops_GGGCH, _hoops_AHPIR);

	char const *	_hoops_SSACR;
	if ((_hoops_SSACR = HI_Scan_Generic_Size (context, &_hoops_GGGCH->data, options, "Variable_Edge_Weight")) != null) {
		char	_hoops_SSSSI [_hoops_CGHHP];
		HE_ERROR2 (HEC_SYNTAX, HES_PARSE_STRING, Sprintf_S (_hoops_SSSSI, "Error parsing option string '%s'", options), _hoops_SSACR);
		goto _hoops_PRSPR;
	}

	if (_hoops_GGGCH->data.value < 0.0f) {
		HE_ERROR (HEC_EDGE, HES_INVALID_WEIGHT, "Unreasonable (negative!) edge weight");
		goto _hoops_PRSPR;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CRRPP)) != null) {
		if (target->type == _hoops_CIRIR)
			HE_ERROR (HEC_EDGE, HES_EDGE, "Variable edge weight not supported inside geometry");
		else
			used = HI_Set_Edge_Weight(context, target, _hoops_GGGCH);

		_hoops_IRRPR();
	}

_hoops_PRSPR:
	if (!used)
		FREE (_hoops_GGGCH, _hoops_AHPIR);
}



GLOBAL_FUNCTION void HI_UnSet_Edge_Weight(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR)
{
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(_hoops_GCRIR == _hoops_CCRIR);

#ifdef _hoops_RGIPR
	_hoops_IRPPR ("Geometry Edge Attributes");
#else

	_hoops_RPGHR *	lea = &_hoops_IPRI->_hoops_IHHPR;
	_hoops_GHHPR *	flags;

	if ((flags = lea->flags) == null ||
		!BIT (flags[offset], _hoops_SCICA)) {
		HE_ERROR (HEC_EDGE, HES_WEIGHT, "No weight set on this edge");
	}
	else {

		flags[offset] &= ~_hoops_SCICA;
		_hoops_IPRI->_hoops_RSHPR &= ~_hoops_SCICA;

		if (--lea->_hoops_CCHHC == 0) {
			FREE_ARRAY (lea->weights, _hoops_IPRI->_hoops_SPHA, float);
			lea->weights = null;
		}
		else
			lea->weights[offset] = 0.0f;

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_Edge_Weight (void) 
{
	_hoops_PAPPR context("UnSet_Edge_Weight");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Edge_Weight ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CRRPP|_hoops_GSIIR)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			HI_UnSet_Edge_Weight(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR);
		}
		else
			HI_UnSet_Attribute (context,  target, HK_EDGE_WEIGHT);

		_hoops_IRRPR();
	}

#endif
}


GLOBAL_FUNCTION bool HI_Set_Vertex_Size(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_AHPIR *		_hoops_GGGCH)
{
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(_hoops_GCRIR == _hoops_SCRIR);

#ifdef _hoops_CSGHR
	_hoops_IRPPR ("Geometry Marker Attributes");
#else

	if (_hoops_GGGCH->data._hoops_HHP != _hoops_SHGRP) {
		HE_ERROR (HEC_MARKER, HES_MARKER, "Variable marker size not supported inside geometry");
		return false;
	}

	float	value = _hoops_GGGCH->data.value;

	if (_hoops_IPRI->local_vertex_attributes._hoops_CAHIR == null)
		HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_GCICA, 0);

	/* _hoops_APSH _hoops_PII _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HPRC _hoops_GPP _hoops_SAHR _hoops_SPR _hoops_GPHA, _hoops_HIS 
		_hoops_SR'_hoops_GCPP _hoops_PAHH _hoops_RRP _hoops_IRS _hoops_IIRRA->_hoops_SGI _hoops_CRPR */
	if(!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)){
		ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
		for(int i = 0; i < _hoops_IPRI->point_count; i++)
			_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
		_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
	}

	Local_Vertex_Flags *	flags  = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);
	float *					size = &_hoops_IPRI->local_vertex_attributes._hoops_CAHIR[offset];

	if (BIT (*flags, _hoops_GCICA) && value == *size)
		goto Release; /* _hoops_IRAHR */

	if (!BIT (*flags, _hoops_GCICA)) {
		*flags |= _hoops_GCICA;
		++_hoops_IPRI->local_vertex_attributes._hoops_SCHHC;
		_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
	}
	else if (value > *size)
		_hoops_IIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
	else if (value < *size)
		_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);

	*size = value;

	_hoops_IPRI->_hoops_AGRHR &= ~_hoops_GCICA;

Release:
#endif
	return false;
}



GLOBAL_FUNCTION bool HI_Set_Marker_Size (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_AHPIR *		_hoops_GGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_MARKER_SIZE, _hoops_RCHHC, _hoops_GGGCH);
}

HC_INTERFACE void HC_CDECL HC_Set_Marker_Size (
	double					value) 
{
	_hoops_PAPPR context("Set_Marker_Size");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Set_Marker_Size (%F);\n", value));
	);

	if (value < 0.0) {
		HE_ERROR (HEC_MARKER, HES_INVALID_WEIGHT, "Unreasonable (negative!) marker size");
		return;
	}

	bool				used = false;
	_hoops_AHPIR *	_hoops_GGGCH;
	ZALLOC (_hoops_GGGCH, _hoops_AHPIR);
	_hoops_GGGCH->data.value = (float)value;
	_hoops_GGGCH->data._hoops_HHP = _hoops_SHGRP;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SRRPP)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			used = HI_Set_Vertex_Size(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_GGGCH);
		}
		else
			used = HI_Set_Marker_Size(context, target, _hoops_GGGCH);

		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_GGGCH, _hoops_AHPIR);
}



GLOBAL_FUNCTION void HI_UnSet_Vertex_Size(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset)
{
	_hoops_ICIIR(_hoops_RIGC);

#ifdef _hoops_CSGHR
	_hoops_IRPPR ("Geometry Marker Attributes");
#else

	Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Local_Vertex_Flags *		flags = _hoops_SPRI->_hoops_CHHPR(offset);

	if (!BIT (*flags, _hoops_GCICA)) {
		HE_ERROR (HEC_MARKER, HES_SIZE, "No marker size set on this vertex");
	}
	else {

		*flags &= ~_hoops_GCICA;
		_hoops_IPRI->_hoops_AGRHR &= ~_hoops_GCICA;

		if (--_hoops_SPRI->_hoops_SCHHC == 0) {
			FREE_ARRAY (_hoops_SPRI->_hoops_CAHIR, _hoops_IPRI->point_count, float);
			_hoops_SPRI->_hoops_CAHIR = null;
		}
		else
			_hoops_SPRI->_hoops_CAHIR[offset] = 0.0f;

		if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
			_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
			FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
			_hoops_SPRI->flags = 0;
		}

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
	}

#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_Marker_Size (void) 
{
	_hoops_PAPPR context("UnSet_Marker_Size");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Marker_Size ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SRRPP|_hoops_GSIIR)) != null) {

		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			ASSERT(_hoops_ASIIR->_hoops_GCRIR == _hoops_SCRIR);
			HI_UnSet_Vertex_Size(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset);
		}
		else
			HI_UnSet_Attribute (context, target, HK_MARKER_SIZE);

		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Set_Variable_Marker_Size (
	char const *		options) 
{
	_hoops_PAPPR context("Set_Variable_Marker_Size");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Variable_Marker_Size (%S);\n", options));
	);

	bool				used = false;
	_hoops_AHPIR *	_hoops_GGGCH;
	ZALLOC (_hoops_GGGCH, _hoops_AHPIR);

	char const *	_hoops_SSACR;
	if ((_hoops_SSACR = HI_Scan_Generic_Size (context, &_hoops_GGGCH->data, options, "Variable_Marker_Size")) != null) {
		char	_hoops_SSSSI [_hoops_CGHHP];
		HE_ERROR2 (HEC_SYNTAX, HES_PARSE_STRING, Sprintf_S (_hoops_SSSSI, "Error parsing option string '%s'", options), _hoops_SSACR);
		goto _hoops_PRSPR;
	}

	if (_hoops_GGGCH->data.value < 0.0f) {
		HE_ERROR (HEC_MARKER, HES_INVALID_SIZE, "Unreasonable (negative!) marker size");
		goto _hoops_PRSPR;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SRRPP)) != null) {
		if (target->type == _hoops_CIRIR)
			HE_ERROR (HEC_MARKER, HES_MARKER, "Variable marker size not supported inside geometry");
		else
			used = HI_Set_Marker_Size(context, target, _hoops_GGGCH);

		_hoops_IRRPR();
	}

_hoops_PRSPR:
	if (!used)
		FREE (_hoops_GGGCH, _hoops_AHPIR);

}


GLOBAL_FUNCTION bool HI_Set_Text_Spacing (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_AHPIR *		_hoops_GGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_TEXT_SPACING, _hoops_RCHHC, _hoops_GGGCH);
}

HC_INTERFACE void HC_CDECL HC_Set_Text_Spacing (
	double					value) 
{
	_hoops_PAPPR context("Set_Text_Spacing");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Set_Text_Spacing (%F);\n", value));
	);

	bool				used = false;
	_hoops_AHPIR *	_hoops_GGGCH;
	ZALLOC (_hoops_GGGCH, _hoops_AHPIR);
	_hoops_GGGCH->data.value = (float)value;
	_hoops_GGGCH->data._hoops_HHP = _hoops_SHGRP;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GARPP)) != null) {
		used = HI_Set_Text_Spacing(context, target, _hoops_GGGCH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_GGGCH, _hoops_AHPIR);
}


HC_INTERFACE void HC_CDECL HC_UnSet_Text_Spacing (void) 
{
	_hoops_PAPPR context("UnSet_Text_Spacing");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Text_Spacing ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GARPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_TEXT_SPACING);
		_hoops_IRRPR();
	}
}




HC_INTERFACE void HC_CDECL HC_Show_Edge_Weight (
	float *			value) 
{
	_hoops_PAPPR context("Show_Edge_Weight");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Edge_Weight () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HIRPP)) != null) {

		_hoops_RHCAP *	_hoops_GHRSR;
		if ((_hoops_GHRSR = (_hoops_RHCAP *)HI_Find_Attribute (context, target, HK_EDGE_WEIGHT)) != null) {

			if (_hoops_GHRSR->data._hoops_HHP == _hoops_SHGRP)
				*value = _hoops_GHRSR->data.value;
			else
				*value = -1.0f;

			_hoops_HPRH (_hoops_GHRSR);
		}

		_hoops_IRRPR();
	}

#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Variable_Edge_Weight (
	char alter *			list) 
{
	_hoops_PAPPR context("Show_Variable_Edge_Weight");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Variable_Edge_Weight () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HIRPP)) != null) {

		_hoops_RHCAP *	_hoops_GHRSR;
		if ((_hoops_GHRSR = (_hoops_RHCAP *)HI_Find_Attribute (context, target, HK_EDGE_WEIGHT)) != null) {

			_hoops_GIGRP		_hoops_HHP = GSU_PIXELS;
			_hoops_HCAIR			size;

			if (_hoops_GHRSR->data._hoops_HHP != _hoops_SHGRP)
				_hoops_HHP = _hoops_GHRSR->data._hoops_HHP;

			size._hoops_HHP = _hoops_HHP;
			size.value = _hoops_GHRSR->data.value;

			HI_Format_Generic_Size_String (&size, list, -1);

			_hoops_HPRH (_hoops_GHRSR);
		}

		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Line_Weight (
	float *			value) 
{
	_hoops_PAPPR context("Show_Line_Weight ");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Line_Weight () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PIRPP)) != null) {

		_hoops_GHCAP *	line_weight;
		if ((line_weight = (_hoops_GHCAP *)HI_Find_Attribute (context, target, HK_LINE_WEIGHT)) != null) {

			if (line_weight->data._hoops_HHP != _hoops_SHGRP)
				*value = -1.0f;
			else
				*value = line_weight->data.value;

			_hoops_HPRH (line_weight);
		}

		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Variable_Line_Weight (
	char alter *			list) 
{
	_hoops_PAPPR context("Show_Variable_Line_Weight");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Variable_Line_Weight () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PIRPP)) != null) {

		_hoops_GHCAP *	line_weight;
		if ((line_weight = (_hoops_GHCAP *)HI_Find_Attribute (context, target, HK_LINE_WEIGHT)) != null) {

			_hoops_GIGRP		_hoops_HHP = GSU_PIXELS;
			_hoops_HCAIR			size;

			if (line_weight->data._hoops_HHP != _hoops_SHGRP)
				_hoops_HHP = line_weight->data._hoops_HHP;

			size._hoops_HHP = _hoops_HHP;
			size.value = line_weight->data.value;

			HI_Format_Generic_Size_String (&size, list, -1);

			_hoops_HPRH (line_weight);
		}

		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Marker_Size (
	float *			value) 
{
	_hoops_PAPPR context("Show_Marker_Size");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Marker_Size () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IIRPP)) != null) {

		_hoops_AHCAP *	_hoops_CHRSR;
		if ((_hoops_CHRSR = (_hoops_AHCAP *)HI_Find_Attribute (context, target, HK_MARKER_SIZE)) != null) {

			if (_hoops_CHRSR->data._hoops_HHP != _hoops_SHGRP)
				*value = -1.0f;
			else
				*value = _hoops_CHRSR->data.value;

			_hoops_HPRH (_hoops_CHRSR);
		}

		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Variable_Marker_Size (
	char alter *			list) 
{
	_hoops_PAPPR context("Show_Variable_Marker_Size");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Variable_Marker_Size () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IIRPP)) != null) {

		_hoops_AHCAP *	_hoops_CHRSR;
		if ((_hoops_CHRSR = (_hoops_AHCAP *)HI_Find_Attribute (context, target, HK_MARKER_SIZE)) != null) {

			_hoops_GIGRP		_hoops_HHP;
			_hoops_HCAIR			size;
			float					value = _hoops_CHRSR->data.value;

			if (_hoops_CHRSR->data._hoops_HHP != _hoops_SHGRP)
				_hoops_HHP = _hoops_CHRSR->data._hoops_HHP;
			else {
				value *= 0.03f;
				_hoops_HHP = GSU_SRU;
			}

			size._hoops_HHP = _hoops_HHP;
			size.value = value;

			HI_Format_Generic_Size_String (&size, list, -1);

			_hoops_HPRH (_hoops_CHRSR);
		}

		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Edge_Weight (
	int					count,
	Key const *			keys,
	float *				value) 
{
	_hoops_PAPPR context("PShow_Net_Edge_Weight");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Edge_Weight () */\n");
	);

	_hoops_RHCAP *	_hoops_GHRSR;
	if ((_hoops_GHRSR = (_hoops_RHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_HIRPP, _hoops_HRPCR, count, keys)) != null) {
		if (_hoops_GHRSR->data._hoops_HHP != _hoops_SHGRP)
			*value = -1.0f;
		else
			*value = _hoops_GHRSR->data.value;
		_hoops_HPRH (_hoops_GHRSR);
		_hoops_IRRPR();
	}
	else
		*value = -2.0f;
#endif
}
#endif


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Var_Edge_Weight (
	int					count,
	Key const *			keys,
	char alter *		list) 
{
	_hoops_PAPPR context("PShow_Net_Var_Edge_Weight");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Var_Edge_Weight () */\n");
	);

	_hoops_RHCAP *	_hoops_GHRSR;
	if ((_hoops_GHRSR = (_hoops_RHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_HIRPP, _hoops_HRPCR, count, keys)) != null) {
	
		_hoops_GIGRP		_hoops_HHP = GSU_PIXELS;
		_hoops_HCAIR			size;

		if (_hoops_GHRSR->data._hoops_HHP != _hoops_SHGRP)
			_hoops_HHP = _hoops_GHRSR->data._hoops_HHP;

		size._hoops_HHP = _hoops_HHP;
		size.value = _hoops_GHRSR->data.value;

		HI_Format_Generic_Size_String (&size, list, -1);

		_hoops_HPRH (_hoops_GHRSR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);

#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Weight (
	int					count,
	Key const *			keys,
	float *				value) 
{
	_hoops_PAPPR context("PShow_Net_Line_Weight ");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Line_Weight () */\n");
	);

	_hoops_GHCAP *	line_weight;
	if ((line_weight = (_hoops_GHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_PIRPP, _hoops_HRPCR, count, keys)) != null) {
		if (line_weight->data._hoops_HHP != _hoops_SHGRP)
			*value = -1.0f;
		else
			*value = line_weight->data.value;
		_hoops_HPRH (line_weight);
		_hoops_IRRPR();
	}
	else 
		*value = -2.0f;
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Var_Line_Weight (
	int					count,
	Key const *			keys,
	char alter *		list) 
{
	_hoops_PAPPR context("PShow_Net_Var_Line_Weight");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Var_Line_Weight () */\n");
	);

	_hoops_GHCAP *	line_weight;
	if ((line_weight = (_hoops_GHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_PIRPP, _hoops_HRPCR, count, keys)) != null) {

		_hoops_GIGRP		_hoops_HHP = GSU_PIXELS;
		_hoops_HCAIR			size;

		if (line_weight->data._hoops_HHP != _hoops_SHGRP)
			_hoops_HHP = line_weight->data._hoops_HHP;

		size._hoops_HHP = _hoops_HHP;
		size.value = line_weight->data.value;

		HI_Format_Generic_Size_String (&size, list, -1);

		_hoops_HPRH (line_weight);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Marker_Size (
	int						count,
	Key const *				keys,
	float *					value) 
{
	_hoops_PAPPR context("PShow_Net_Marker_Size");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Marker_Size () */\n");
	);

	_hoops_AHCAP *	_hoops_CHRSR;
	if ((_hoops_CHRSR = (_hoops_AHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_IIRPP, _hoops_HRPCR, count, keys)) != null) {
		if (_hoops_CHRSR->data._hoops_HHP != _hoops_SHGRP)
			*value = -1.0f;
		else
			*value = _hoops_CHRSR->data.value;
		_hoops_HPRH (_hoops_CHRSR);
		_hoops_IRRPR();
	}
	else
		*value = -2.0f;
#endif
}
#endif


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Var_Marker_Size (
	int						count,
	Key const *				keys,
	char alter *			list) 
{
	_hoops_PAPPR context("PShow_Net_Var_Marker_Size");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Var_Marker_Size () */\n");
	);

	_hoops_AHCAP *	_hoops_CHRSR;
	if ((_hoops_CHRSR = (_hoops_AHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_IIRPP, _hoops_HRPCR, count, keys)) != null) {

		_hoops_GIGRP	_hoops_HHP;
		_hoops_HCAIR		size;
		float				value = _hoops_CHRSR->data.value;
		if (_hoops_CHRSR->data._hoops_HHP != _hoops_SHGRP)
			_hoops_HHP = _hoops_CHRSR->data._hoops_HHP;
		else {
			value *= 0.03f;
			_hoops_HHP = GSU_SRU;
		}

		size._hoops_HHP = _hoops_HHP;
		size.value = value;

		HI_Format_Generic_Size_String (&size, list, -1);

		_hoops_HPRH (_hoops_CHRSR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);
#endif
}
#endif



/* _hoops_GSHHC _hoops_RHAP _hoops_HAR _hoops_HS _hoops_PSPA */


HC_INTERFACE void HC_CDECL HC_Show_Text_Spacing (
	float *			value) 
{
	_hoops_PAPPR context("Show_Text_Spacing");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_Spacing () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CIRPP)) != null) {

		_hoops_PHCAP *	_hoops_RSHHC;
		if ((_hoops_RSHHC = (_hoops_PHCAP *)HI_Find_Attribute (context, target, HK_TEXT_SPACING)) != null) {
			*value = _hoops_RSHHC->data.value;
			_hoops_HPRH (_hoops_RSHHC);
		}

		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Spacing (
	int					count,
	Key const *			keys,
	float *				value) 
{
	_hoops_PAPPR context("PShow_Net_Text_Spacing");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Text_Spacing () */\n");
	);

	_hoops_PHCAP *	_hoops_RSHHC;
	if ((_hoops_RSHHC = (_hoops_PHCAP *) HI_Find_Attribute_And_Lock(context, _hoops_CIRPP, _hoops_HRPCR, count, keys)) != null) {
		*value = _hoops_RSHHC->data.value;
		_hoops_HPRH (_hoops_RSHHC);
		_hoops_IRRPR();
	}
	else
		*value = 0; /* _hoops_CAGRH */

#endif
}
#endif


