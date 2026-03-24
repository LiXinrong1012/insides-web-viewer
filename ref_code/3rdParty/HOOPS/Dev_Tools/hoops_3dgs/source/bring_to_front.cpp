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
 * $Id: obf_tmp.txt 1.76 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local void _hoops_GRSIR (
	_hoops_AIGPR *	_hoops_RIGC,
	Geometry *				geometry,
	int						offset) {
	Geometry *				_hoops_RRSIR;

	/* (_hoops_RRRPR _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_CAGH - _hoops_PSP _hoops_GSGR _hoops_ARSIR) */
	if (geometry->owner->type != _hoops_IRCP) return; /* _hoops_RPAPR */

	if (BIT (geometry->owner->_hoops_PHSI, _hoops_PRSIR)) {
		HI_Not_When_Streamed (geometry->owner, "reorder things within it");
		return;
	}

	if (geometry->type == _hoops_HGPGR) {
		HE_WARNING (HEC_BRING_TO_FRONT, HES_INVALID_FOR_CUTTING_PLANES,
					"'Bring_To_Front' is not meaningful for cutting-planes");

		/* _hoops_PAGA: _hoops_CHPPR-_hoops_SHPPR _hoops_PPR _hoops_HRSIR-_hoops_ARCA-_hoops_IRSIR *_hoops_GARIR* _hoops_CRSIR
		 *		 _hoops_HPPA _hoops_GHC _hoops_SHR _hoops_IHGS _hoops_SRS _hoops_GGR _hoops_RH _hoops_HIGR. _hoops_HGI
		 *		 '_hoops_ASRC' _hoops_HRGR _hoops_CPSA _hoops_RGHP.
		 */
		return;
	}

	if (BIT (geometry->_hoops_RRHH, _hoops_CHRIR)) {		// _hoops_SRSIR _hoops_PPR _hoops_GASIR _hoops_GPP _hoops_RH _hoops_CCAH _hoops_RASIR
		if (geometry->type == _hoops_HIIP)
			geometry = (Geometry *)HI_Isolate_Line_From_Multiline (_hoops_RIGC, (_hoops_SHRIR *)geometry, offset);
		else if (geometry->type == _hoops_PIRS)
			geometry = (Geometry *)HI_Isolate_Marker_From_Multimarker (_hoops_RIGC, (_hoops_GRPGR *)geometry, offset);
	}

	geometry->owner->_hoops_PHSI |= _hoops_AASIR;

#if 1

	if ((_hoops_RRSIR = geometry->next) == null) {
		/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_IHIS _hoops_PA */
		geometry->_hoops_RRHH |= _hoops_PASIR;
	}
	else {
		/*_hoops_SRS _hoops_SR _hoops_HASIR _hoops_SCH _hoops_HII _hoops_RH _hoops_GASR*/
		HI_Table_Remove_Geometry (geometry);

		/*_hoops_AAAI _hoops_SCH _hoops_HII _hoops_RH _hoops_HIGR _hoops_SAHR _hoops_PII _hoops_ARPP*/
		*geometry->backlink = _hoops_RRSIR;
		_hoops_RRSIR->backlink = geometry->backlink;
	
		geometry->_hoops_RRHH |= _hoops_PASIR;

		/*_hoops_PSCR _hoops_SR _hoops_PPSI _hoops_SCH _hoops_ISSC _hoops_GGR _hoops_RH _hoops_IASIR _hoops_ICSHR*/
		HI_Table_Insert_OO_Geometry (geometry->owner, geometry);

		if (!BIT(geometry->_hoops_CPGPR, _hoops_CASIR))
			_hoops_SASIR (_hoops_RIGC, geometry, _hoops_GPSIR|_hoops_RPSIR);
	}

#else

	if ((_hoops_RRSIR = geometry->next) == null) {
		/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_IHIS _hoops_PA */
	}
	else {
		Geometry		*_hoops_APSIR;

		/* _hoops_PPSI _hoops_SCH _hoops_GGR _hoops_RH _hoops_RPHR _hoops_HGHC */

		*geometry->backlink = _hoops_RRSIR;
		_hoops_RRSIR->backlink = geometry->backlink;

		_hoops_RGGA ((_hoops_APSIR = _hoops_RRSIR->next) == null) _hoops_RRSIR = _hoops_APSIR;

/* _hoops_IAPPR _hoops_RGR _hoops_RPGP?  _hoops_PPSIR _hoops_PIHA _hoops_SHH _hoops_IRAP _hoops_RAS _hoops_RH _hoops_HPSIR _hoops_HAPR.

		_hoops_RPP ((_hoops_CPAP->_hoops_SPS = _hoops_PPSIR) != _hoops_IRAP)
			_hoops_PPSIR->_hoops_IPSIR = &_hoops_CPAP->_hoops_SPS;
*/
		geometry->next = null;

		_hoops_RRSIR->next = geometry;
		geometry->backlink = &_hoops_RRSIR->next;

		if (!BIT(geometry->_hoops_CPGPR, _hoops_CASIR))
			_hoops_SASIR (geometry, _hoops_GPSIR|_hoops_RPSIR);
	}

	/*** _hoops_CPSIR _hoops_IH _hoops_AARPR _hoops_SPSIR: "_hoops_GHSIR" _hoops_HAR _hoops_RHSIR _hoops_GGR _hoops_AHSIR ***/
#endif
}

local void _hoops_PHSIR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				segment,
	void *					info) {
	long					low, high;

	/* (_hoops_RRRPR _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_CAGH - _hoops_PSP _hoops_SRRPR _hoops_SGHC) */
	if (segment->owner->type != _hoops_IRCP)
		return; /* _hoops_RPAPR */

	if (BIT (segment->owner->_hoops_PHSI, _hoops_PRSIR)) {
		HI_Not_When_Streamed (segment->owner, "reorder things within it");
		return;
	}

	// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_IHSIR
	HI_Create_Fast_Lookup (segment->owner, true);
	HI_Show_Fast_Lookup_Priority_Range (segment->owner, &low, &high);

	if (segment->next == null) {
		if (high == 0)		/* _hoops_AIAH _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_HIGR _hoops_PPR _hoops_PSP _hoops_GRH _hoops_AGHC */
			return;
		/* _hoops_GRS _hoops_ARP _hoops_GHCP _hoops_IS _hoops_PSSP _hoops_RSGR _hoops_IIGR _hoops_HIGR */
	}
	else
		++high;			/* _hoops_RRP _hoops_IRS _hoops_CHSIR _hoops_PIRA */

	HI_Set_Priority (_hoops_RIGC, (_hoops_HPAH *)segment, high);

	if ((info != null ||
		 (segment->type == _hoops_IRCP &&
		  BIT (segment->_hoops_PHSI, _hoops_SHSIR))) &&
		segment->owner != HOOPS_WORLD->root &&
		!ANYBIT (segment->owner->_hoops_PHSI,
				 _hoops_SHSIR | _hoops_GISIR)) {
		/*
		 * _hoops_CHHA _hoops_RISIR _hoops_IS _hoops_RIPS _hoops_IIGR _hoops_GRAA-_hoops_AISIR _hoops_PISIR _hoops_IIGR _hoops_IRS _hoops_AISIR
		 * _hoops_CAGH _hoops_HISIR _hoops_IS _hoops_RIPS.
		 * _hoops_SGH _hoops_SIHC != _hoops_IRAP _hoops_IS _hoops_RIP _hoops_IS _hoops_SAS _hoops_GH _hoops_RAS _hoops_SRS _hoops_GRAA-_hoops_AISIR.
		 */
		_hoops_PHSIR (_hoops_RIGC, segment->owner, segment /* _hoops_GII _hoops_GRAA-_hoops_IRAP */);
	}
}


HC_INTERFACE void HC_CDECL HC_Bring_To_Front (
	char const *			name) {
	_hoops_PAPPR context("Bring_To_Front");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Bring_To_Front (%S);\n", name));
	);

	_hoops_RPPPR();
	HI_For_Each (context, name, true, _hoops_PHSIR, null);
	_hoops_IRRPR();
}


GLOBAL_FUNCTION void HI_Bring_To_Front (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				thing,
	int						offset) {

	if (thing->type >= _hoops_IISIR)
		_hoops_PHSIR (_hoops_RIGC, (_hoops_CRCP *)thing, null);
	else
		_hoops_GRSIR (_hoops_RIGC, (Geometry *)thing, offset);
}


GLOBAL_FUNCTION void HI_Bring_To_Front_By_Key (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key) 
{
	int						offset;
	_hoops_SIHIR *				_hoops_CISIR = (_hoops_SIHIR *)_hoops_SISIR (_hoops_RIGC, key, &offset);

	if (_hoops_CISIR == null ||
		!(_hoops_AHRIR <= _hoops_CISIR->type && _hoops_CISIR->type <= _hoops_IHRIR) ||
		BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR)) {

		HE_ERROR (HEC_BRING_TO_FRONT, HES_INVALID_KEY, "Specified key is not valid or is no longer valid");
		return;
	}

	if (_hoops_CISIR->owner == null) {
		HI_Not_When_LOD ();
		return;
	}
	else {
		_hoops_RPPPR();
		HI_Bring_To_Front (_hoops_RIGC, (_hoops_HPAH *)_hoops_CISIR, offset); 
		_hoops_IRRPR();
	}
}


HC_INTERFACE void HC_CDECL HC_Bring_To_Front_By_Key (
	Key						key) 
{
	_hoops_PAPPR context("Bring_To_Front_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Bring_To_Front_By_Key (LOOKUP (%D));\n", key));
	);

	_hoops_CSPPR();
	HI_Bring_To_Front_By_Key (context, key);
	_hoops_IRRPR();
}
