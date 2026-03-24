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
 * $Id: obf_tmp.txt 1.56 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local void _hoops_SIGGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {
	Subsegment *			_hoops_GIPIA = (Subsegment *)_hoops_SRCP;
	long					priority = (long)(POINTER_SIZED_INT)info;
	_hoops_CRCP *				owner = _hoops_GIPIA->owner;
	Subsegment *			_hoops_AIGSA;

	// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_IHSIR
	HI_Create_Fast_Lookup (owner, true);
	HI_Remove_Fast_Lookup_Item (owner, true, _hoops_GIPIA);

	_hoops_GIPIA->priority = priority;

	if (_hoops_GIPIA->type == _hoops_AGRPR)
		_hoops_GIPIA->_hoops_RRHH &= ~_hoops_HPAPA;

	HI_Add_Fast_Lookup_Item (owner, true, _hoops_GIPIA);

	_hoops_AIGSA = HI_Find_Fast_Lookup_Predecessor (owner, true, _hoops_GIPIA, null);


	_hoops_CIGPR (_hoops_RIGC,_hoops_GIPIA);
	if (_hoops_AIGSA != null) {
		if ((_hoops_GIPIA->next = _hoops_AIGSA->next) != null)
			_hoops_GIPIA->next->backlink = &_hoops_GIPIA->next;
		_hoops_GIPIA->backlink = &_hoops_AIGSA->next;
		_hoops_AIGSA->next = _hoops_GIPIA;
	}
	else {
		if ((_hoops_GIPIA->next = owner->_hoops_RGRPR) != null)
			_hoops_GIPIA->next->backlink = &_hoops_GIPIA->next;
		_hoops_GIPIA->backlink = &owner->_hoops_RGRPR;
		owner->_hoops_RGRPR = _hoops_GIPIA;
	}

	if (priority != 0) {
		_hoops_GIPIA->_hoops_RRHH |= _hoops_PASIR;
		owner->_hoops_PHSI |= _hoops_GGPSA;

		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			_hoops_PGRPR const *		include = (_hoops_PGRPR const *)_hoops_GIPIA;

			if (!BIT(include->_hoops_RRHH, _hoops_HPAPA) &&
				include->_hoops_IGRPR->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_GCGGS = (_hoops_CRCP const *)include->_hoops_IGRPR;

				if (!BIT(_hoops_GCGGS->_hoops_PHSI, _hoops_SHSIR))
					owner->_hoops_PHSI |= _hoops_CCHGP;
			}
		}
		else if (_hoops_GIPIA->type == _hoops_IRCP) {	// _hoops_PHHIP _hoops_HRGR _hoops_AIAH == _hoops_HHASA
			if (!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
				owner->_hoops_PHSI |= _hoops_CCHGP;
		}
	}
	else {
		_hoops_GIPIA->_hoops_RRHH &= ~_hoops_PASIR;

		if (BIT (owner->_hoops_PHSI, _hoops_GGPSA)) {
			Subsegment const *		_hoops_SIIS = owner->_hoops_RGRPR;

			do {
				if (BIT (_hoops_SIIS->_hoops_RRHH, _hoops_PASIR))
					break;
			} while ((_hoops_SIIS = _hoops_SIIS->next) != null);

			if (_hoops_SIIS == null)
				owner->_hoops_PHSI &= ~_hoops_GGPSA;
		}
	}

	if (_hoops_GIPIA->type == _hoops_IRCP && BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_GCGSA|_hoops_RPSIR);
	else
		_hoops_SASIR (_hoops_RIGC, owner, _hoops_GGARA);
}

GLOBAL_FUNCTION void HI_Set_Priority (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				thing,
	long					priority)
{
	_hoops_ICIIR(_hoops_RIGC);

	if (thing->type == _hoops_IRCP || thing->type == _hoops_AGRPR) {
		_hoops_SIGGS (_hoops_RIGC, (_hoops_CRCP *)thing, (void *)(POINTER_SIZED_INT)priority);
	}
	else {
		Geometry *	geometry = (Geometry *)thing;

		geometry->priority = priority;
		HI_Invalidate_Segment_Display_Lists (_hoops_RIGC, geometry->owner, geometry->type, geometry, _hoops_HRRI);
		_hoops_SASIR (_hoops_RIGC, geometry->owner, _hoops_GGARA);
	}
}

HC_INTERFACE void HC_CDECL HC_Set_Priority (
	Key			key,
	long		priority) 
{
	_hoops_PAPPR context("Set_Priority");

#ifdef _hoops_IRSSH
	_hoops_IRPPR ("Priority");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Set_Priority (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", priority));
	);

	_hoops_RPPPR();

	int			offset;
	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_SISIR (context, key, &offset);

	if (thing == null || BIT (thing->_hoops_RRHH, _hoops_HGAGR))
		HE_ERROR (HEC_PRIORITY, HES_INVALID_KEY, "Key does not refer to anything valid");
	else if (thing->type == _hoops_IRCP || thing->type == _hoops_AGRPR ||
			(thing->type >= _hoops_AHRIR && thing->type <= _hoops_PHRIR)) {
		if (BIT (thing->_hoops_RRHH, _hoops_CHRIR)) {		// _hoops_SRSIR _hoops_PPR _hoops_GASIR _hoops_GPP _hoops_RH _hoops_CCAH _hoops_RASIR
			if (thing->type == _hoops_HIIP)
				thing = (_hoops_HPAH *)HI_Isolate_Line_From_Multiline (context, (_hoops_SHRIR *)thing, offset);
			else if (thing->type == _hoops_PIRS)
				thing = (_hoops_HPAH *)HI_Isolate_Marker_From_Multimarker (context, (_hoops_GRPGR *)thing, offset);
		}

		HI_Set_Priority (context, thing, priority);
	}
	else
		HE_ERROR (HEC_PRIORITY, HES_INVALID_KEY, "Key must refer to a segment, an include, or a geometry");

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Priority (
	Key			key,
	long *		priority) 
{
	_hoops_PAPPR context("Show_Priority");

#if defined(DISABLE_SHOW) || defined (_hoops_IRSSH)
	if (priority != null)
		*priority = 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Priority (); */\n");
	);

	_hoops_CSPPR();

	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_RCSSR (context, key);

	if (thing == null || BIT (thing->_hoops_RRHH, _hoops_HGAGR))
		HE_ERROR (HEC_PRIORITY, HES_INVALID_KEY, "Key does not refer to anything valid");
	else if (thing->type == _hoops_IRCP) {
		_hoops_CRCP const *	_hoops_SIIS = (_hoops_CRCP const *)thing;

		*priority = _hoops_SIIS->priority;
	}
	else if (thing->type == _hoops_AGRPR) {
		_hoops_PGRPR const *	_hoops_SIIS = (_hoops_PGRPR const *)thing;

		if (BIT(thing->_hoops_RRHH, _hoops_HPAPA))
			*priority = 0;
		else
			*priority = _hoops_SIIS->priority;
	}
	else if (thing->type >= _hoops_AHRIR && thing->type <= _hoops_PHRIR) {
		Geometry const *	geometry = (Geometry const *)thing;

		*priority = geometry->priority;
	}
	else
		HE_ERROR (HEC_PRIORITY, HES_INVALID_KEY, "Key must refer to a segment, an include, or a geometry");

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Priority_Range (
	Key				key,
	long *			low,
	long *			high) 
{
	_hoops_PAPPR context("Show_Priority_Range");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_IRSSH
	_hoops_IRPPR ("Priority");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Priority_Range (); */\n");
	);

	_hoops_CSPPR();

	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, key);

	if (_hoops_SRCP == null || BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR))
		HE_ERROR (HEC_PRIORITY, HES_INVALID_KEY, "Key does not refer to anything valid");
	else if (_hoops_SRCP->type == _hoops_IRCP) {
		LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
		HI_Show_Fast_Lookup_Priority_Range (_hoops_SRCP, low, high);
		UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
	}
	else
		HE_ERROR (HEC_PRIORITY, HES_INVALID_KEY, "Key must refer to a segment");

	_hoops_IRRPR();
#endif
#endif
}


