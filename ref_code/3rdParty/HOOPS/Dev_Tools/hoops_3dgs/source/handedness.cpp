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
 * $Id: obf_tmp.txt 1.59 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local Attribute *_hoops_RIGIH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_ARAIR const *		_hoops_AIGIH = (_hoops_ARAIR const *)_hoops_CPACR;
	_hoops_ARAIR alter *		_hoops_PIGIH = (_hoops_ARAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_AIGIH != null && _hoops_AIGIH->which == _hoops_PIGIH->which)
		return null;

	return _hoops_PIGIH;
}


GLOBAL_FUNCTION bool HI_Decipher_Handedness (
	char const *		_hoops_HIGIH,
	int alter *			which) 
{
	char const *	spec = _hoops_HIGIH;

	if (_hoops_SHPCR (spec[0]) == 'r') {
		if (_hoops_SHPCR (spec[1]) == 'i' &&
			_hoops_SHPCR (spec[2]) == 'g' &&
			_hoops_SHPCR (spec[3]) == 'h' &&
			_hoops_SHPCR (spec[4]) == 't') {

			spec += 5;
			while (spec[0] == ' ') ++spec;

			if (spec[0] == '\0') {
				*which = _hoops_RAACA;
				return true;
			}
		}
	}
	else {
		if (_hoops_SHPCR (spec[0]) == 'l' &&
			_hoops_SHPCR (spec[1]) == 'e' &&
			_hoops_SHPCR (spec[2]) == 'f' &&
			_hoops_SHPCR (spec[3]) == 't') {

			spec += 4;
			while (spec[0] == ' ') ++spec;

			if (spec[0] == '\0') {
				*which = _hoops_GIACA;
				return true;
			}
		}
	}

	HE_ERROR2 (HEC_HANDEDNESS, HES_INVALID_INPUT, 
		Sprintf_S (null, "'%s' is not a valid Handedness -", _hoops_HIGIH), "Should be 'right' or 'left'");

	return false;
}


GLOBAL_FUNCTION bool HI_Set_Handedness (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ARAIR *			_hoops_HRACA)		
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_HANDEDNESS, _hoops_RIGIH, _hoops_HRACA);
}


HC_INTERFACE void HC_CDECL HC_Set_Handedness (
	char const *		spec) 
{
	_hoops_PAPPR context("Set_Handedness");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Handedness (%S);\n", spec));
	);

	
	bool			used = false;
	_hoops_ARAIR *	_hoops_HRACA;
	ZALLOC (_hoops_HRACA, _hoops_ARAIR);

	if (HI_Decipher_Handedness (spec, &_hoops_HRACA->which)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_ARRPP)) != null) {
			used = HI_Set_Handedness(context, target, _hoops_HRACA);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (_hoops_HRACA, _hoops_ARAIR);
}


HC_INTERFACE void HC_CDECL HC_UnSet_Handedness (void) {
	_hoops_PAPPR context("UnSet_Handedness");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Handedness ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ARRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute(context, target, HK_HANDEDNESS);
		_hoops_IRRPR();
	}
}



HC_INTERFACE void HC_CDECL HC_Show_Handedness (
	char *		spec) 
{
	_hoops_PAPPR context("Show_Handedness");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Handedness () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GSRPP)) != null) {

		_hoops_ARAIR *	_hoops_HRACA;
		if ((_hoops_HRACA = (_hoops_ARAIR *)HI_Find_Attribute (context, target, HK_HANDEDNESS)) != null) {

			if (_hoops_HRACA->which == _hoops_RAACA)
				HI_Return_Chars (spec, -1, "right", 5);
			else
				HI_Return_Chars (spec, -1, "left", 4);

			_hoops_HPRH (_hoops_HRACA);
		}
		_hoops_IRRPR();
	}
#endif
}




#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Handedness (
	int						count,
	Key const *				keys,
	char *					spec) 
{
	_hoops_PAPPR context("PShow_Net_Handedness");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Handedness () */\n");
	);

	_hoops_ARAIR *	_hoops_HRACA;
	if ((_hoops_HRACA = (_hoops_ARAIR *) HI_Find_Attribute_And_Lock(context, _hoops_GSRPP, _hoops_HRPCR, count, keys)) != null) {
		if (_hoops_HRACA->which == _hoops_RAACA)
			HI_Return_Chars (spec, -1, "right", 5);
		else
			HI_Return_Chars (spec, -1, "left", 4);
		_hoops_HPRH (_hoops_HRACA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(spec, -1, "", 0);
#endif
}
#endif


