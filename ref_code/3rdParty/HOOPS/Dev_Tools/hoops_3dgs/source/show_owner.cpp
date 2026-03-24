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
 * $Id: obf_tmp.txt 1.48 2010-07-29 22:00:21 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HI_Not_When_LOD (void) {
	HE_ERROR (HEC_LOD, HES_INVALID_TARGET,
				"Operation not not allowed with LOD geometry items");
}


GLOBAL_FUNCTION Key HI_Show_Owner_Key_By_Key (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	bool					_hoops_AARHP,
	bool					_hoops_CISAP) 
{
	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);

	if (thing == null ||
		!((thing->type >= _hoops_AHRIR && thing->type <= _hoops_PHRIR &&
		!BIT (thing->_hoops_RRHH, _hoops_HGAGR)) ||
		(thing->type >= _hoops_IISIR && thing->type <= _hoops_IHRIR &&
		!BIT (thing->_hoops_RRHH, _hoops_HGAGR)) ||
		(thing->type == HK_STYLE &&
		!BIT (thing->_hoops_RRHH, _hoops_HGAGR)))) {

			if (_hoops_AARHP)
				HE_ERROR (HEC_OWNER, HES_INVALID_KEY, "Provided key is invalid");

			return _hoops_SHSSR;
	}

	if (thing->owner == null) {
		if (_hoops_AARHP)
			HI_Not_When_LOD ();
		return _hoops_SHSSR;
	}
	else if (thing->owner->type == _hoops_PRAIR)
		return _hoops_SHSSR;
	else if (_hoops_CISAP)
		return _hoops_AIRIR(thing->owner);
	else
		return thing->owner->key;
}



HC_INTERFACE Key HC_CDECL HC_Show_Owner (
	char const *	segname,
	char *			pathname) 
{
	_hoops_PAPPR context("Show_Owner");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return _hoops_SHSSR;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Owner () */\n");
	);

	_hoops_CSPPR();

	Key result = _hoops_SHSSR;

	_hoops_CRCP *	_hoops_SRCP;

	if ((_hoops_SRCP = HI_One_Segment_Search (context, segname, true)) != null) {

		if (_hoops_SRCP->owner->type == _hoops_PRAIR) {

			if (pathname != null)
				HI_Return_Chars (pathname, -1, "", 0);
		}
		else {

			if (pathname != null)
				HI_Return_Sprintf1 (pathname, -1, "%p", (void *)_hoops_SRCP->owner);

			result = _hoops_SRCP->owner->key;
		}
	}
	else 
		HE_ERROR (HEC_SEGMENT, HES_NONE_FOUND, "No owner found");

	_hoops_IRRPR();

	return result;
#endif
}


HC_INTERFACE Key HC_CDECL HC_Show_Owner_By_Key (
	Key			key,
	char *		pathname) 
{
	_hoops_PAPPR context("Show_Owner_By_Key");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return _hoops_SHSSR;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Owner_By_Key () */\n");
	);

	_hoops_CSPPR();

	Key result = HI_Show_Owner_Key_By_Key (context, key, true, false);

	if (result != _hoops_SHSSR){

		if (pathname != null) {
			_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_RCSSR (context, key);

			if (thing->type == HK_STRING_CURSOR)
				HE_ERROR (HEC_OWNER, HES_TEXT_OWNS_STRING_CURSOR, "The owner of a string cursor is text - it has no pathname");
			else
				HI_Return_Sprintf1 (pathname, -1, "%p", (void *)thing->owner);
		}
	}
	else {
		
		if (pathname != null)
			HI_Return_Chars (pathname, -1, "", 0);
	}

	_hoops_IRRPR();

	return result;
#endif
}



HC_INTERFACE Key HC_CDECL HC_Show_Owner_Original_Key (
	Key		key) 
{
	_hoops_PAPPR context("Show_Owner_By_Key");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return _hoops_SHSSR;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Owner_Original_Key () */\n");
	);

	_hoops_CSPPR();

	Key result = HI_Show_Owner_Key_By_Key (context, key, true, true);

	_hoops_IRRPR();

	return result;
#endif
}
